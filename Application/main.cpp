#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "contactsmodel.h"
#include <QDebug>
#include "clientmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    net::ConnectionArgumentsParser parser {*QCoreApplication::instance()};
    ClientManager::instance().setConnectionSettings(parser);
    ContactsModel::registerMe("Contacts");

    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
