#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "space.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Space::Space space;
    space.AddReview("Very bad, not good", 1);
    space.AddReview("Okay ish", 3.5);
    for (std::string i: space.GetReviews()) {
        std::cout << i << std::endl;
    }
    return app.exec();
}
