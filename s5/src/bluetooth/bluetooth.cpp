#include "bluetooth.h"
#include "remoteselector.h"
#include "chatserver.h"
#include "chatclient.h"

#include <QtCore/qdebug.h>

#include <QtCore/qmetaobject.h>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif
//4+ 2 + 2 + 2 + 6
//static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8"); // 16 byte uuid
static const QLatin1String serviceUuid("e0cbf06c-cd8b-4647-bb8a-263b43f0f974"); // ballard laptop #6977 GUID

#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
//static const QLatin1String reverseUuid("00001101-0000-1000-8000-00805F9B34FB");
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
#else
        if (ulp.contains(QBluetoothUuid(serviceUuid))){
#endif
        //if( device.address().toString()== "50:76:AF:31:11:5D"){ //ballard laptop //"04:D3:95:BC:DE:E0" motorola remote
        //if( device.address().toString()== "A8:86:DD::95::F5::CF"){ // ubuntu
        //if(!socket){
            socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

            connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&bluetooth::connected));
            //connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
            connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
                    this, &bluetooth::onSocketErrorOccurred);

#ifdef Q_OS_ANDROID
            socket->connectToService(device.address(), QBluetoothUuid(reverseUuid), QIODevice::ReadWrite);
#else
            socket->connectToService(device.address(), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
#endif
            //socket->connectToService(device.address(), QBluetoothUuid(QBluetoothUuid::Rfcomm), QIODevice::ReadWrite);
            //socket->connectToService(device.address(), 1, QIODevice::ReadWrite );

            qDebug() <<socket->state();
            qDebug() << socket->errorString();
        }
}

void bluetooth::deviceDiscovered()
{
    deviceList = discoveryAgent->discoveredDevices(); // keeps returning null
}


bluetooth::bluetooth(QObject *parent) : QObject(parent){

#ifdef Q_OS_ANDROID
    localAdapters = QBluetoothLocalDevice::allDevices();


    QBluetoothLocalDevice adapter(localAdapters.at(0).address());
    adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

    //! [Get local device name]
    localName = QBluetoothLocalDevice().name();
    //! [Get local device name]

    // Create a discovery agent and connect to its signals
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
    this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    //connect(discoveryAgent, SIGNAL(finished()), this, SLOT(deviceDiscovered()));

    // Start a discovery
    discoveryAgent->start();
#else

    server = new ChatServer(this);
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

#endif
#if false
    //discoveryAgent->discoveredDevices();
    /////////////////////////////////////////////////////
   // const  QBluetoothAddress  address("04:D3:95:BC:DE:E0");
    const  QBluetoothAddress  address("A8:86:DD::95::F5::CF");
    //discoveryAgent = new QBluetoothDeviceDiscoveryAgent(address);

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&bluetooth::connected));
    //connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            this, &bluetooth::onSocketErrorOccurred);

    //socket->connectToService(address, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    socket->connectToService(address,  QBluetoothUuid(QBluetoothUuid::Rfcomm), QIODevice::ReadWrite);

    //qDebug() <<socket->state();
    //qDebug() << socket->errorString();
/*
    connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&bluetooth::connected));
    //connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            this, &bluetooth::onSocketErrorOccurred);
*/
#endif
#if false
QString localDeviceName;
QBluetoothLocalDevice localDevice;
    // Read local device name
    localDeviceName = localDevice.name();

    // Make it visible to others
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);


    // Get connected devices
    //QList<QBluetoothAddress> remotes;
    //remotes = localDevice.connectedDevices();
#endif
////////////////////////////////////////////
#if false
    localAdapters = QBluetoothLocalDevice::allDevices();
    if (localAdapters.count() < 2) {
        //ui->localAdapterBox->setVisible(false);
    } else {
        //we ignore more than two adapters
        //ui->localAdapterBox->setVisible(true);
        //ui->firstAdapter->setText(tr("Default (%1)", "%1 = Bluetooth address").
          //                        arg(localAdapters.at(0).address().toString()));
        //ui->secondAdapter->setText(localAdapters.at(1).address().toString());
        //ui->firstAdapter->setChecked(true);
        //connect(ui->firstAdapter, &QRadioButton::clicked, this, &Chat::newAdapterSelected);
        //connect(ui->secondAdapter, &QRadioButton::clicked, this, &Chat::newAdapterSelected);
        QBluetoothLocalDevice adapter(localAdapters.at(0).address());
        adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }

 #endif
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

//! [connected]
/*
void bluetooth::connected(const QString &name)
{
    qDebug() << "Connected";
    //ui->chat->insertPlainText(QString::fromLatin1("Joined chat with %1.\n").arg(name));
}*/
//! [connected]

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

//! [Connect to remote service]
void bluetooth::connectClicked()
{
    //ui->connectButton->setEnabled(false);

    // scan for services
    const QBluetoothAddress adapter = localAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           localAdapters.at(currentAdapterIndex).address();

    RemoteSelector remoteSelector(adapter);
#ifdef Q_OS_ANDROID
   // if (QtAndroid::androidSdkVersion() >= 23)
        //remoteSelector.startDiscovery(QBluetoothUuid(reverseUuid));
    //else
        remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
#else
   remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
#endif
bool cSet = false ;

while(!cSet){
  if(remoteSelector.serviceReady()){
        QBluetoothServiceInfo service = remoteSelector.service();

        qDebug() << "Connecting to service 2" << service.serviceName()
                 << "on" << service.device().name();

        // Create client
        qDebug() << "Going to create client";
        ChatClient *client = new ChatClient(this);
qDebug() << "Connecting...";

        connect(client, &ChatClient::messageReceived,
                this, &bluetooth::showMessage);
        connect(client, &ChatClient::disconnected,
                this, QOverload<>::of(&bluetooth::clientDisconnected));
        //connect(client, QOverload<const QString &>::of(&ChatClient::connected),
                //this, &bluetooth::connected);
        //connect(client, QOverload<>::of(&ChatClient::connected),
          //      this, &bluetooth::connected);
        connect(client, &ChatClient::socketErrorOccurred,
                this, &bluetooth::reactOnSocketError);
        connect(this, &bluetooth::sendMessage, client, &ChatClient::sendMessage);
qDebug() << "Start client";
        client->startClient(service);

        clients.append(client);
        cSet = true;
    }
}


    //ui->connectButton->setEnabled(true);
}
//! [Connect to remote service]
//!
//! //! [sendClicked]
void bluetooth::sendClicked()
{
    emit sendMessage("Hello World");
}
//! [sendClicked]


//! [showMessage]
void bluetooth::showMessage(const QString &sender, const QString &message)
{

    qDebug() << "Message Recieved: " << message;
    //ui->chat->insertPlainText(Q <<String::fromLatin1("%1: %2\n").arg(sender, message));
    qDebug()<<sender << " "  << message;
    //ui->chat->ensureCursorVisible();
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

