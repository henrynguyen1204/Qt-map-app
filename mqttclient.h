#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>

class MQTTClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(double latitude READ latitude NOTIFY coordinateChanged)
    Q_PROPERTY(double longitude READ longitude NOTIFY coordinateChanged)

public:
    explicit MQTTClient(QObject *parent = nullptr);

    double latitude() const { return m_latitude; }
    double longitude() const { return m_longitude; }

    Q_INVOKABLE void connectToBroker(const QString &host, quint16 port, const QString &topic);

signals:
    void coordinateChanged();

private slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient m_client;
    double m_latitude = 0.0;
    double m_longitude = 0.0;
};

#endif // MQTTCLIENT_H
