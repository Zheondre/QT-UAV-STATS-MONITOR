#include "bluetooth.h"
#include "remoteselector.h"
#include "chatserver.h"
#include "chatclient.h"

#include <QtCore/qdebug.h>
#include <QtCore/qmetaobject.h>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

static const QLatin1String serviceUuid("e0cbf06c-cd8b-4647-bb8a-263b43f0f974"); // ballard laptop #6977 GUID
#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
#endif

void bluetooth::connected()
{
    //emit connected(socket->peerName());
    qDebug() <<socket->state();
    qDebug() << socket->errorString();
    qDebug() <<"Sockect Connected to "<< socket->localName() << " " << socket->localAddress() << " " << socket->localPort();
    qDebug() << "Peer " << socket->peerName() << " " << socket->peerAddress() << " " << socket->peerPort() ;
    socket->write("Hello World");
}

void bluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    QList<QBluetoothUuid> ulp = device.serviceUuids();

    if(ulp.count() > 0 )
#ifdef Q_OS_ANDROID
        if (ulp.contains(QBluetoothUuid(reverseUuid))){
            //test
            if( device.address().toString()== "50:76:AF:31:11:5D"){//ballard laptop 6977
                int x = 0;
            }
#else
        if (ulp.contains(QBluetoothUuid(serviceUuid))){
#endif
            socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

            connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&bluetooth::connected));
            //connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
            connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
                    this, &bluetooth::onSocketErrorOccurred);


            connect(server, &ChatServer::messageReceived,
                    this,  &bluetooth::showMessage);
            connect(this, &bluetooth::sendMessage, server, &ChatServer::sendMessage);

#ifdef Q_OS_ANDROID
            socket->connectToService(device.address(), QBluetoothUuid(reverseUuid), QIODevice::ReadWrite);
#else
            socket->connectToService(device.address(), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
#endif
            qDebug() <<socket->state();
            qDebug() << socket->errorString();
        }
}

void bluetooth::deviceDiscovered()
{
    deviceList = discoveryAgent->discoveredDevices(); // keeps returning null
}


bluetooth::bluetooth(QObject *parent) : QObject(parent){

    //bluetooth::bluetooth(QObject *parent) : QThread(parent){
        searching = false;
        cltCnt = false;
        //remoteSelector = nullptr;

        localAdapters = QBluetoothLocalDevice::allDevices();
#ifdef Q_OS_ANDROID
        QBluetoothLocalDevice adapter(localAdapters.at(0).address());
        adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
#endif
        server = new ChatServer(this);

        //QButton *button =
        //connect(, onclick, this, run);

        connect(server, QOverload<const QString &>::of(&ChatServer::clientConnected),
                this, &bluetooth::clientConnected);
        connect(server, QOverload<const QString &>::of(&ChatServer::clientDisconnected),
                this,  QOverload<const QString &>::of(&bluetooth::clientDisconnected));
        connect(server, &ChatServer::messageReceived,
                this,  &bluetooth::showMessage);
        connect(this, &bluetooth::sendMessage, server, &ChatServer::sendMessage);

        server->startServer();
        //! [Create Chat Server]

        //! [Get local device name]
        localName = QBluetoothLocalDevice().name();
        //! [Get local device name]

}

bluetooth::~bluetooth()
{
    //mutex.lock();
    //abort = true;
    //condition.wakeOne();
    //mutex.unlock();

   // wait();
}

void bluetooth::run(){

    const QBluetoothAddress adapter = localAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           localAdapters.at(0).address();

    //remoteSelector = new RemoteSelector(adapter);
    //adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    RemoteSelector remoteSelector(adapter);

  //  forever{
        // scan for services
        if((!cltCnt)){

            if(!searching){
#ifdef Q_OS_ANDROID
                if (QtAndroid::androidSdkVersion() >= 23)
                    remoteSelector.startDiscovery(QBluetoothUuid(reverseUuid));
                else
                    remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
#else
                 remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
#endif
                searching = true;
            }

            if(remoteSelector.serviceReady()){//make thread wait or block thread here
                QBluetoothServiceInfo service = remoteSelector.service();

                qDebug() << "Connecting to service 2" << service.serviceName()
                         << "on" << service.device().name();

                ChatClient *client = new ChatClient(this);
                qDebug() << "Connecting...";

                connect(client, &ChatClient::inbox, this, &bluetooth::inbox);
                connect(client, &ChatClient::disconnected, this, QOverload<>::of(&bluetooth::clientDisconnected));
                // connect(client, QOverload<const QString &>::of(&ChatClient::connected),
                 //       this, &bluetooth::connected);
                //connect(client, QOverload<>::of(&ChatClient::connected),
                 //       this, &bluetooth::connected);
                connect(client, &ChatClient::socketErrorOccurred, this, &bluetooth::reactOnSocketError);
                connect(this, &bluetooth::sendMessage, client, &ChatClient::sendMessage);

                 client->startClient(service);
                 clients.append(client);
                 searching = false;
               //  return;///TEMP
            }
        } else {
         //connected and desktop send out messages once a secoond
#define TEST
#ifdef Q_OS_WIN || Q_OS_LINUX
    #ifdef TEST
    mes = "$PCRL,$FCAIRSTA,";

    //for(auto i: statsList) {
    for(auto j : statsList->getStatItems()){
        //mes += QString::number(j->m_nValue) +", ";
        mes += QString::number(rand() %100 ) +", ";
    }
    //}
    mes += "END<<";

    #endif
     if(clients.at(0))
        clients.at(0)->sendMessage(mes);
     else {
         cltCnt = false;
         searching = false;
     }
#endif
        }

        //sleep(1);
    //}
}

//! [clientConnected clientDisconnected]
void bluetooth::clientConnected(const QString &name)
{
    qDebug() <<"%1 has joined chat.\n";
}

void bluetooth::clientDisconnected(const QString &name)
{
    qDebug() << "Client Disconnected";
}
//! [clientConnected clientDisconnected]

void bluetooth::newAdapterSelected()
{
    const int newAdapterIndex = adapterFromUserSelection();
    if (currentAdapterIndex != newAdapterIndex) {
        server->stopServer();
        currentAdapterIndex = newAdapterIndex;
        const QBluetoothHostInfo info = localAdapters.at(currentAdapterIndex);
        QBluetoothLocalDevice adapter(info.address());
        adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        server->startServer(info.address());
        localName = info.name();
    }
}

int bluetooth::adapterFromUserSelection() const
{
    int result = 0;
    QBluetoothAddress newAdapter = localAdapters.at(0).address();

//if (ui->secondAdapter->isChecked()) {
        newAdapter = localAdapters.at(1).address();
        result = 1;
  //}
    return result;
}

void bluetooth::reactOnSocketError(const QString &error)
{qDebug() << "Socket Error";
    //ui->chat->insertPlainText(error);
}

//! [clientDisconnected]

void bluetooth::clientDisconnected()
{
    ChatClient *client = qobject_cast<ChatClient *>(sender());
    if (client) {
        clients.removeOne(client);
        client->deleteLater();
    }
}
//! [clientDisconnected]


//! [showMessage]
void bluetooth::showMessage(const QString &sender, const QString &message)
{

    qDebug() << "Message Recieved: " << message;
    //ui->chat->insertPlainText(Q <<String::fromLatin1("%1: %2\n").arg(sender, message));
    qDebug()<<sender << " "  << message;
    //ui->chat->ensureCursorVisible();
//copies message
    //TEMP might need semaphore
        //mes = m;
}
//! [showMessage]
//!
 void bluetooth::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    if (error == QBluetoothSocket::NoSocketError)
        return;

    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QString errorString = socket->peerName() + QLatin1Char(' ')
            + metaEnum.valueToKey(error) + QLatin1String(" occurred");

    emit socketErrorOccurred(errorString);
}


 void bluetooth::addStats(FcAirStats *s){
 //statsList.append(s);
     statsList = s;
 }
