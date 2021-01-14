#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>

#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/qbluetoothdeviceinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothuuid.h>
#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothsocket.h>
#include <QBluetoothSocket>
#include <QtCore/qobject.h>

#include "C:\Source\QT\QTGITREPO\s5\src\FcAir\fcairstats.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

class ChatServer;
class ChatClient;

class bluetooth: public QObject
{

    Q_OBJECT
    bool searching;
    bool cltCnt;
    bool btconnected;

    int adapterFromUserSelection() const;
    int currentAdapterIndex = 0;

    FcAirStats * statsList;

    ChatServer *server;
    QList<ChatClient *> clients;
    QList<QBluetoothHostInfo> localAdapters;

    QString localName;
    QList<QBluetoothDeviceInfo> deviceList;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothSocket *socket;
public:
    explicit bluetooth(QObject *parent = nullptr);
    ~bluetooth();
    //void run();

    QString mes;
    void addStats(FcAirStats *);
    QString &getOutStream();

public slots:
    void run();

signals:

    void inbox(const QString &result);
    void sendForceCommand(const QString &result);
    void sendMessage(const QString &message);

    void sleep(unsigned long);

    void socketErrorOccurred(const QString &errorString);
    void connected(const QString &name);

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void deviceDiscovered();

    void showMessage(const QString &sender, const QString &message);

    void clientConnected(const QString &name);
    void clientDisconnected(const QString &name);
    void clientDisconnected();
    void connected();
    void reactOnSocketError(const QString &error);

    void newAdapterSelected();

    void onSocketErrorOccurred(QBluetoothSocket::SocketError);
};

#endif // BLUETOOTH_H
