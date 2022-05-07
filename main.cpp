#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QString>
#include <qqml.h>

// User libraries
#include "space.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <string>

QVector<space::Space*> GetRandomizedSpaces(int n){
    QVector<space::Space*> returnObjects;
    std::srand(time(NULL));
    for (int i = 0; i < n; i++) {
        returnObjects.push_back(
            new space::Space{
                i,                                      // ID
                QString::fromStdString("Space"          // name
                    + std::to_string(i)),

                                                        // For dimensions
                rand() % 90 + 10,                       // length
                rand() % 45 + 5,                        // width
                rand() % 10 + 2,                        // height

                rand() % 990 + 10,                      // number of people

                                                        // For seats
                rand() % 490 + 10,                      // number of seats
                (bool)(rand() % 2),                     // slanted?
                (bool)(rand() % 2),                     // surround?
                (bool)(rand() % 2),                     // comfy?

                                                        // For timer
                rand() % 9900 + 100,                    // price

                (bool)(rand() % 2),                     // outdoor?
                (bool)(rand() % 2),                     // catering?
                (bool)(rand() % 2),                     // naturalLight?
                (bool)(rand() % 2),                     // artificialLight?
                (bool)(rand() % 2),                     // sound?
                (bool)(rand() % 2),                     // projector?
                (bool)(rand() % 2)                      // camera?
            }
        );
        returnObjects.back()->GetReview().AddReview("Very bad, not good", rand() % 5);
        returnObjects.back()->GetReview().AddReview("Okay ish", rand() % 5);
    }
    return returnObjects;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QVector<space::Space*> randomSpaces = GetRandomizedSpaces(20);
    for (auto space_ptr = randomSpaces.begin(); space_ptr != randomSpaces.end(); space_ptr++) {
        std::cout << "ID: " << (*space_ptr)->GetID() << "\nName: " << (*space_ptr)->GetName().toStdString() << "\nArea: " << (*space_ptr)->GetDims().GetArea() << " m^2" << std::endl;
        for (QString i: (*space_ptr)->GetReview().GetReviews()) {
            std::cout << i.toStdString() << std::endl;
        }
        std::cout << "Review score: " << (*space_ptr)->GetReview().GetReviewScore() << std::endl << std::endl;
    }
    return app.exec();
}
