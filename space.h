#ifndef SPACE_H
#define SPACE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <qqml.h>

// User libraries
#include <string>
#include <vector>
#include <ctime>

namespace space {
    // Class for space dimensions
    // .. Currently assume box-like spaces with length-width-height
    class Dimensions : public QObject {
        Q_OBJECT
        Q_PROPERTY(float length READ GetLength WRITE SetLength NOTIFY LengthChanged)
        Q_PROPERTY(float width READ GetWidth WRITE SetWidth NOTIFY WidthChanged)
        Q_PROPERTY(float height READ GetHeight WRITE SetHeight NOTIFY HeightChanged)
        Q_PROPERTY(float area READ GetArea NOTIFY AreaChanged)
        Q_PROPERTY(float aspectRatio READ GetAspectRatio NOTIFY AspectRatioChanged)
    signals:
        void LengthChanged();
        void WidthChanged();
        void HeightChanged();
        void AreaChanged();
        void AspectRatioChanged();
    private:
        float length = 0, width = 0, height = 0;
        float area = 0, aspectRatio = 0;
        void UpdateAAR();
    public:
        // Constructors & destructors
        explicit Dimensions(QObject *parent = nullptr) {}
        explicit Dimensions(float p_length, float p_width, float p_height, QObject *parent = nullptr);
        virtual ~Dimensions() {}

        // Setters
        void SetLength(float p_length);
        void SetWidth(float p_width);
        void SetHeight(float p_height);
        void SetDimensions(float p_length, float p_width, float p_height);

        // Getters
        float GetLength() const { return length; }
        float GetWidth() const { return width; }
        float GetHeight() const { return height; }
        float GetArea() const { return area; }
        float GetAspectRatio() const { return aspectRatio; }
    };

    // Class for seatings
    class Seating : public QObject {
        Q_OBJECT
        Q_PROPERTY(unsigned int numberOfSeats READ GetNumberOfSeats WRITE SetNumberOfSeats NOTIFY NumberOfSeatsChanged)
        Q_PROPERTY(bool slanted READ IsSlanted WRITE IsSlanted NOTIFY SlantedChanged)
        Q_PROPERTY(bool surround READ IsSurround WRITE IsSurround NOTIFY SurroundChanged)
        Q_PROPERTY(bool comfy READ IsComfy WRITE IsComfy NOTIFY ComfyChanged)
    signals:
        void NumberOfSeatsChanged();
        void SlantedChanged();
        void SurroundChanged();
        void ComfyChanged();
    private:
        unsigned int numberOfSeats = 0;
        // For slanted seating (conference halls, theater, cinema, ...)
        bool slanted = false;
        // For surround seating configs (theater, music events, ...)
        bool surround = false;
        // For if the chairs are not cheap plastic
        bool comfy = true;
    public:
        // Constructors & destructors
        explicit Seating(QObject *parent = nullptr) : QObject(parent) {}
        explicit Seating(unsigned int p_numberOfSeats,
                         bool p_slanted = false,
                         bool p_surround = false,
                         bool p_comfy = false,
                         QObject *parent = nullptr);
        virtual ~Seating() {}

        // Setters
        void SetNumberOfSeats(unsigned int p_numberOfSeats);
        // Setters using overload
        void IsSlanted(bool p_slanted);
        void IsSurround(bool p_surround);
        void IsComfy(bool p_comfy);

        // Getters
        bool IsSlanted() const { return slanted; }
        bool IsSurround() const { return surround; }
        bool IsComfy() const { return comfy; }
        unsigned int GetNumberOfSeats() const { return numberOfSeats; }
    };

    // Class for available times
    // .. Assume accomodative spaces: working all day
    class Time : public QObject {
        Q_OBJECT
        Q_PROPERTY(double dirhamsPerHour READ GetDirhamsPerHour WRITE SetDirhamsPerHour NOTIFY DirhamsPerHourChanged)
        Q_PROPERTY(time_t originTime READ GetOriginTime)
        Q_PROPERTY(QVector<unsigned long long> times READ GetTimes NOTIFY TimesChanged)
    signals:
        void DirhamsPerHourChanged();
        void TimesChanged();
    private:
        time_t originTime;
        // Using a list of unsigned long long integers
        // .. to keep track of allocated time
        // .. Each bit corresponds to 1 hour
        // .. More long longs added based on scheduler
        // .. 64 bits per each corresponding to 2.67 days
        QVector<unsigned long long> times;
        // Price per hour
        double dirhamsPerHour = 0;
    public:
        Time(QObject *parent = nullptr);
        Time(double p_dirhamsPerHour, QObject *parent = nullptr);
        Time(double p_dirhamsPerHour, const time_t& p_originTime, QObject *parent = nullptr);
        virtual ~Time() {}
        // Setters
        void SetDirhamsPerHour(double p_dirhamsPerHour);
        // Getters
        double GetDirhamsPerHour() const { return dirhamsPerHour; }
        time_t GetOriginTime() const { return originTime; }
        QVector<unsigned long long> GetTimes() const { return times; }

        // Function to reserve
        // .. param price to return the price
        Q_INVOKABLE bool AddReservation(const time_t& p_startTime, const time_t& p_endTime, double& price);
        // Function to remove reservations
        Q_INVOKABLE bool RemoveReservation(const time_t& p_startTime, const time_t& p_endTime);
    };

    // Class for reviews
    class Review: public QObject {
        Q_OBJECT
        Q_PROPERTY(float score READ GetReviewScore NOTIFY ScoreChanged)
        Q_PROPERTY(unsigned int numberOfReviews READ GetNumberOfReviews NOTIFY NumberOfReviewsChanged)
        Q_PROPERTY(bool reviewed READ IsReviewed NOTIFY ReviewedChanged)
        Q_PROPERTY(QVector<QString> reviews READ GetReviews NOTIFY ReviewsChanged)
    signals:
        void ScoreChanged();
        void NumberOfReviewsChanged();
        void ReviewedChanged();
        void ReviewsChanged();
    private:
        // .. Constrained to 0 to 5
        float score = 0;
        unsigned int numberOfReviews = 0;
        bool reviewed = false;
        QVector<QString> reviews;
    public:
        // Constructors & destructors
        explicit Review(float p_score = 0, QObject* parent = nullptr) : QObject(parent) {
            score = p_score;
        }
        virtual ~Review() {}

        // Setters
        // Add a review
        Q_INVOKABLE void AddReview(const QString& p_review, float p_score) {
            reviewed = true;
            reviews.push_back(p_review);
            score = (score * numberOfReviews + p_score) / (++numberOfReviews);
            emit ReviewsChanged();
            emit ReviewedChanged();
        }

        // Getters
        float GetReviewScore() const { return score; }
        QVector<QString> GetReviews() const { return reviews; }
        unsigned int GetNumberOfReviews() const { return numberOfReviews; }
        bool IsReviewed() const { return reviewed; }
    };

    // Class for each discrete space
    class Space : public QObject {
        Q_OBJECT
        Q_PROPERTY(unsigned int ID READ GetID WRITE SetID NOTIFY IDChanged)
        Q_PROPERTY(QString name READ GetName WRITE Rename NOTIFY NameChanged)
        Q_PROPERTY(unsigned int numberOfPeople READ GetNumberOfPeople WRITE SetNumberOfPeople NOTIFY NumberOfPeopleChanged)
        Q_PROPERTY(bool outdoor READ IsOutdoor WRITE IsOutdoor NOTIFY OutdoorChanged)
        Q_PROPERTY(bool catering READ IsCatering WRITE IsCatering NOTIFY CateringChanged)
        Q_PROPERTY(bool naturalLight READ IsNaturalLight WRITE IsNaturalLight NOTIFY NaturalLightChanged)
        Q_PROPERTY(bool artificialLight READ IsArtificialLight WRITE IsArtificialLight NOTIFY ArtificialLightChanged)
        Q_PROPERTY(bool projector READ IsProjector WRITE IsProjector NOTIFY ProjectorChanged)
        Q_PROPERTY(bool sound READ IsSound WRITE IsSound NOTIFY SoundChanged)
        Q_PROPERTY(bool cameras READ IsCameras WRITE IsCameras NOTIFY CamerasChanged)
        // Q_PROPERTY(double dirhamsPerHour READ GetDirhamsPerHour WRITE SetDirhamsPerHour NOTIFY DirhamsPerHourChanged)
        // Q_PROPERTY(QVector<QString> tags READ GetTags NOTIFY TagsChanged)

        Q_PROPERTY(Dimensions* dims MEMBER m_dims NOTIFY DimsChanged)
        Q_PROPERTY(Seating* seats MEMBER m_seats NOTIFY SeatsChanged)
        Q_PROPERTY(Time* timer MEMBER m_timer NOTIFY TimerChanged)
        Q_PROPERTY(Review* review MEMBER m_review NOTIFY ReviewChanged)
    signals:
        void IDChanged();
        void NameChanged();
        void NumberOfPeopleChanged();
        void OutdoorChanged();
        void CateringChanged();
        void NaturalLightChanged();
        void ArtificialLightChanged();
        void ProjectorChanged();
        void SoundChanged();
        void CamerasChanged();
        void DirhamsPerHourChanged();
        void TagsChanged();

        void DimsChanged();
        void SeatsChanged();
        void TimerChanged();
        void ReviewChanged();
    private:
        unsigned int ID;
        QString name;
        Dimensions* m_dims;

        // Event-specific characteristics
        // .. Accomodation
        unsigned int numberOfPeople = 0;
        Seating* m_seats;
        bool outdoor = false;
        bool catering = false;

        // .. Design
        // .. .. Lighting
        bool naturalLight = false;
        bool artificialLight = true;
        bool projector = true;
        // .. .. Sound system
        bool sound = true;
        // .. .. Camera system
        bool cameras = true;

        // .. Available times
        double dirhamsPerHour;
        Time* m_timer;

        // For reviews
        // .. Constrained to 0 to 5
        Review* m_review;

        // Miscellaneous tags
        QVector<QString> tags;
    public:
        // Needs to be pointers as QML takes ownership
//        Dimensions* m_dims;
//        Seating* m_seats;
//        Time* m_timer;
//        Review* m_review;
        // Constructors & destructors
        Space(QObject *parent = nullptr) : QObject(parent) {
            m_dims = nullptr;
            m_seats = nullptr;
            m_timer = nullptr;
        }
        // Creating a new space
        Space(
            unsigned int p_ID,
            QString p_name,

            // For dimensions
            float p_length, float p_width, float p_height,
            unsigned int p_numberOfPeople,

            // For seats
            unsigned int p_numberOfSeats, bool p_slanted, bool p_surround, bool p_comfy,

            // For timer
            double p_dirhamsPerHour,

            // Optional
            bool p_outdoor = false,
            bool p_catering = false,
            bool p_naturalLight = false,
            bool p_artificialLight = true,
            bool p_projector = true,
            bool p_sound = true,
            bool p_cameras = true,
            QObject *parent = nullptr) : QObject(parent) {

            // Manual work
            ID = p_ID;
            name = p_name;
            // Use built-in copy constructor
//            dims = p_dims;
//            seats = p_seats;
            numberOfPeople = p_numberOfPeople;
            dirhamsPerHour = p_dirhamsPerHour;
            // Set current time as origin time
//            timer = Time(p_dirhamsPerHour);
            outdoor = p_outdoor;
            catering = p_catering;
            naturalLight = p_naturalLight;
            artificialLight = p_artificialLight;
            projector = p_projector;
            sound = p_sound;
            cameras = p_cameras;

            m_dims = new Dimensions(p_length, p_width, p_height);
            m_seats = new Seating(p_numberOfSeats, p_slanted, p_surround, p_comfy);
            m_timer = new Time(dirhamsPerHour);
            m_review = new Review();
        }
        // Destructor
        virtual ~Space() {
            delete m_dims;
            delete m_seats;
            delete m_timer;
        }

        // Setters
        void Rename(const QString& p_name) {
            name = p_name;
            emit NameChanged();
        }
        void SetID(unsigned int p_ID) {
            ID = p_ID;
            emit IDChanged();
        }
        void SetNumberOfPeople(int p_numberOfPeople) {
            numberOfPeople = p_numberOfPeople;
            emit NumberOfPeopleChanged();
        }
        // Setters using overload
        void IsOutdoor(bool p_outdoor) {
            outdoor = p_outdoor;
            emit OutdoorChanged();
        }
        void IsCatering(bool p_catering) {
            catering = p_catering;
            emit CateringChanged();
        }
        void IsNaturalLight(bool p_naturalLight) {
            naturalLight = p_naturalLight;
            emit NaturalLightChanged();
        }
        void IsArtificialLight(bool p_artificialLight) {
            artificialLight = p_artificialLight;
            emit ArtificialLightChanged();
        }
        void IsProjector(bool p_projector) {
            projector = p_projector;
            emit ProjectorChanged();
        }
        void IsSound(bool p_sound) {
            sound = p_sound;
            emit SoundChanged();
        }
        void IsCameras(bool p_cameras) {
            cameras = p_cameras;
            emit CamerasChanged();
        }

        // Getters
        QString GetName() const { return name; }
        unsigned int GetID() const { return ID; }
        int GetNumberOfPeople() const { return numberOfPeople; }
        bool IsOutdoor() const { return outdoor; }
        bool IsCatering() const { return catering; }
        bool IsNaturalLight() const { return naturalLight; }
        bool IsArtificialLight() const { return artificialLight; }
        bool IsProjector() const { return projector; }
        bool IsSound() const { return sound; }
        bool IsCameras() const { return cameras; }

        Dimensions& GetDims() const { return *m_dims; }
        Seating& GetSeats() const { return *m_seats; }
        Time& GetTimer() const { return *m_timer; }
        Review& GetReview() const { return *m_review; }
    };

    // Class to manage spaces
    // (running backbone of the application)
    class SpaceManager : public QObject {
    private:
        QVector<space::Space*> spaces;
    public:
        // Constructors & destructors
        explicit SpaceManager(QObject* parent = nullptr) : QObject(parent) {}
        virtual ~SpaceManager(){}

        // Testing purposes
        void GetRandomizedSpaces(int n){
            spaces = QVector<space::Space*>{};
            std::srand(time(NULL));
            for (int i = 0; i < n; i++) {
                spaces.push_back(
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
                spaces.back()->GetReview().AddReview("Very bad, not good", rand() % 5);
                spaces.back()->GetReview().AddReview("Okay ish", rand() % 5);
            }
        }
    };
}

#endif // SPACE_H
