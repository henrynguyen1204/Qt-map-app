import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Current Location Map with MQTT"

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    PositionSource {
        id: positionSource
        active: true
        updateInterval: 5000
        onPositionChanged: {
            console.log("Lat:", position.coordinate.latitude, "Lon:", position.coordinate.longitude);
            view.center = position.coordinate;
        }
    }

    MapView {
        id: view
        anchors.fill: parent
        map.plugin: mapPlugin
        map.center: positionSource.position.coordinate 
        map.zoomLevel: 15

        MapQuickItem {
            id: userMarker
            parent: view.map
            coordinate: positionSource.position.coordinate
            sourceItem: Rectangle {
                width: 14; height: 14
                color: "#e41e25"
                border.width: 2; border.color: "white"
                radius: 7
            }
            anchorPoint: Qt.point(7, 7)
        }
        MapQuickItem {
            id: gpsMarker
            parent: view.map
            coordinate: QtPositioning.coordinate(mqttClient.latitude, mqttClient.longitude)
            sourceItem: Rectangle {
                width: 14
                height: 14
                color: "#e41e25"
                border.width: 2
                border.color: "white"
                radius: 7
            }
            anchorPoint: Qt.point(7, 7)
            opacity: 1.0
        }
    }

    // Kết nối MQTT khi ứng dụng chạy
    Component.onCompleted: {
        mqttClient.connectToBroker("broker.emqx.io", 1883, "project1/test1");
    }

    // Theo dõi thay đổi từ MQTT
    Connections {
        target: mqttClient
        function onCoordinateChanged() {
            view.map.center = QtPositioning.coordinate(mqttClient.latitude, mqttClient.longitude);
        }
    }

}
