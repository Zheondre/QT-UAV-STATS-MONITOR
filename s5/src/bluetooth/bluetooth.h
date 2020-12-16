#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>

#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/qbluetoothdeviceinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothuuid.h>
#include <QBluetoothSocket>


#include <QtCore/qobject.h>

#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothsocket.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)


class ChatServer;
class ChatClient;

class bluetooth: public QObject
{

    Q_OBJECT

    int adapterFromUserSelection() const;
    int currentAdapterIndex = 0;

    ChatServer *server;
    QList<ChatClient *> clients;
    QList<QBluetoothHostInfo> localAdapters;

    QString localName;
    QList<QBluetoothDeviceInfo> deviceList;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothSocket *socket;
public:
    explicit bluetooth(QObject *parent = nullptr);

signals:

    void inbox(const QString &result);
    void sendForceCommand(const QString &result);

    void sendMessage(const QString &message);
    void socketErrorOccurred(const QString &errorString);
    void connected(const QString &name);

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void deviceDiscovered();

    void connectClicked();
    void sendClicked();

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
