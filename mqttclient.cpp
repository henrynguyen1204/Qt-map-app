#include "mqttclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

MQTTClient::MQTTClient(QObject *parent) : QObject(parent) {
    connect(&m_client, &QMqttClient::messageReceived, this, &MQTTClient::onMessageReceived);
}

void MQTTClient::connectToBroker(const QString &host, quint16 port, const QString &topic) {
    m_client.setHostname(host);
    m_client.setPort(port);
    m_client.connectToHost();

    connect(&m_client, &QMqttClient::connected, this, [this, topic]() {
        qDebug() << "Connected to MQTT Broker";
        m_client.subscribe(topic, 0);
    });
}

void MQTTClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic) {
    Q_UNUSED(topic)

    QJsonDocument doc = QJsonDocument::fromJson(message);
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    if (obj.contains("lat") && obj.contains("lon")) {
        double lat = obj["lat"].toDouble();
        double lon = obj["lon"].toDouble();

        if (lat != m_latitude || lon != m_longitude) {
            m_latitude = lat;
            m_longitude = lon;
            emit coordinateChanged();
        }
    }
}

