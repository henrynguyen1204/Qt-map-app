#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mqttclient.h"
#include <QQmlContext>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MQTTClient mqttClient;
    engine.rootContext()->setContextProperty("mqttClient", &mqttClient);

    engine.load(QUrl(QStringLiteral("file:///D:/projects/qt/untitled3/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
