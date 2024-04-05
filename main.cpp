#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "voxelitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<VoxelItem>("VoxelViewer", 1, 0, "VoxelItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
