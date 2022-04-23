#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QString>
#include <qqml.h>

// User libraries
#include "space.cpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <string>

std::vector<Space::Space> GetRandomizedSpaces(int n){
    std::vector<Space::Space> returnObjects;
    std::srand(time(NULL));
    for (int i = 0; i < n; i++) {
        returnObjects.push_back(
            Space::Space(
                i,                                      // ID
                "Space" + std::to_string(i),           // name
                Space::Dimensions(
                    rand() % 90 + 10,                   // length
                    rand() % 45 + 5,                    // width
                    rand() % 10 + 2                     // height
                ),
                Space::Seating(
                    rand() % 490 + 10,                  // number of seats
                    (bool)(rand() % 2),                 // slanted?
                    (bool)(rand() % 2),                 // surround?
                    (bool)(rand() % 2)                  // comfy?
                ),
                rand() % 990 + 10,                      // number of people
                rand() % 9900 + 100,                    // price
                (bool)(rand() % 2),                     // outdoor?
                (bool)(rand() % 2),                     // catering?
                (bool)(rand() % 2),                     // naturalLight?
                (bool)(rand() % 2),                     // sound?
                (bool)(rand() % 2),                     // projector?
                (bool)(rand() % 2)                      // camera?
            )
        );
        returnObjects.back().AddReview("Very bad, not good", rand() % 5);
        returnObjects.back().AddReview("Okay ish", rand() % 5);
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

//    QList<QObject *> dataList = {
//        new SpaceQt("Item 1", "red"),
//        new SpaceQt("Item 2", "green"),
//        new SpaceQt("Item 3", "blue"),
//        new SpaceQt("Item 4", "yellow")
//    };
    // Space::QSeating sit;
    // Space::QDimensions dim;

    std::vector<Space::Space> randomSpaces = GetRandomizedSpaces(20);
    for (Space::Space space: randomSpaces) {
        std::cout << "ID: " << space.GetID() << "\nName: " << space.GetName() << "\nArea: " << space.dims.GetArea() << " m^2" << std::endl;
        for (std::string i: space.GetReviews()) {
            std::cout << i << std::endl;
        }
        std::cout << "Review: " << space.GetReviewScore() << std::endl << std::endl;
    }
    return app.exec();
}
