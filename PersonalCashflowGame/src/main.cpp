#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFont>

#include "controllers/GameController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Application metadata
    QCoreApplication::setApplicationName("Personal Cashflow Game");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setOrganizationName("CashflowGame");

    // Set application font
    QFont appFont = QFont("Segoe UI", 10);
    app.setFont(appFont);

    // Create the game controller
    GameController controller;
    if (!controller.initialize()) {
        qWarning() << "Failed to initialize game controller";
        return 1;
    }

    // Set up QML engine
    QQmlApplicationEngine engine;

    // Expose controller to QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("gameController", &controller);

    // Register QML types
    qmlRegisterType<GameController>("GameController", 1, 0, "GameController");

    // Load main QML file
    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    });

    engine.load(url);

    return app.exec();
}
