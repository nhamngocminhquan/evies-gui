#include <QObject>
#include <QVector>
#include <QString>
#include <qqml.h>

// User libraries
#include "space.cpp"
#include <string>
#include <vector>
#include <ctime>

// Qt wrapper for Space classes
namespace Space {
    // Class for space dimensions
    // .. Currently assume box-like spaces with length-width-height
    class QDimensions : public QObject {
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
        Dimensions* dims_ref;
    public:
        explicit QDimensions(Dimensions* p_dims_ref = nullptr, QObject *parent = nullptr);
        virtual ~QDimensions() {}
        // Setters
        void SetLength(float p_length);
        void SetWidth(float p_width);
        void SetHeight(float p_height);
        void SetDimensions(float p_length, float p_width, float p_height);

        // Getters
        float GetLength() { return dims_ref->GetLength(); }
        float GetWidth() { return dims_ref->GetWidth(); }
        float GetHeight() { return dims_ref->GetHeight(); }
        float GetArea() { return dims_ref->GetArea(); }
        float GetAspectRatio() { return dims_ref->GetAspectRatio(); }
    };

    // Class for seatings
    class QSeating : public QObject {
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
        Seating* seats_ref;
    public:
        explicit QSeating(Seating* p_seats_ref = nullptr, QObject *parent = nullptr);
        virtual ~QSeating() {}
        // Setters
        void SetNumberOfSeats(unsigned int p_numberOfSeats);
        // Setters using overload
        void IsSlanted(bool p_slanted);
        void IsSurround(bool p_surround);
        void IsComfy(bool p_comfy);

        // Getters
        bool IsSlanted() { return seats_ref->IsSlanted(); }
        bool IsSurround() { return seats_ref->IsSurround(); }
        bool IsComfy() {return seats_ref->IsComfy(); }
        unsigned int GetNumberOfSeats() { return seats_ref->GetNumberOfSeats(); }
    };

    // Class for available times
    // .. Assume accomodative spaces: working all day
    class QTime : public QObject {
        Q_OBJECT
        Q_PROPERTY(double dirhamsPerHour READ GetDirhamsPerHour WRITE SetDirhamsPerHour NOTIFY DirhamsPerHourChanged)
        Q_PROPERTY(time_t originTime READ GetOriginTime)
        Q_PROPERTY(QVector<unsigned long long> times READ GetTimes NOTIFY TimesChanged)
    signals:
        void DirhamsPerHourChanged();
        void TimesChanged();
    private:
        Time* timer_ref;
    public:
        QTime(Time* p_timer_ref = nullptr, QObject *parent = nullptr);
        virtual ~QTime() {}
        // Setters
        void SetDirhamsPerHour(double p_dirhamsPerHour);
        // Getters
        double GetDirhamsPerHour() { return timer_ref->GetDirhamsPerHour(); }
        time_t GetOriginTime() { return timer_ref->GetOriginTime(); }
        QVector<unsigned long long> GetTimes() { return QVector<unsigned long long>::fromStdVector(timer_ref->GetTimes()); }

        // Function to reserve
        // .. param price to return the price
        Q_INVOKABLE bool AddReservation(const time_t& p_startTime, const time_t& p_endTime, double& price);
        // Function to remove reservations
        Q_INVOKABLE bool RemoveReservation(const time_t& p_startTime, const time_t& p_endTime);
    };

    // Class for each discrete space
    class QSpace : public QObject{
        Q_OBJECT
        Q_PROPERTY(unsigned int ID READ GetID WRITE SetID NOTIFY IDChanged)
        Q_PROPERTY(QString name READ GetName WRITE Rename NOTIFY NameChanged)
        // Q_PROPERTY(unsigned int numberOfPeople READ GetNumberOfPeople WRITE SetNumberOfPeople NOTIFY NumberOfPeopleChanged)
        Q_PROPERTY(bool outdoor READ IsOutdoor WRITE IsOutdoor NOTIFY OutdoorChanged)
        Q_PROPERTY(bool catering READ IsCatering WRITE IsCatering NOTIFY CateringChanged)
        Q_PROPERTY(bool naturalLight READ IsNaturalLight WRITE IsNaturalLight NOTIFY NaturalLightChanged)
        Q_PROPERTY(bool artificialLight READ IsArtificialLight WRITE IsArtificialLight NOTIFY ArtificialLightChanged)
        Q_PROPERTY(bool projector READ IsProjector WRITE IsProjector NOTIFY ProjectorChanged)
        Q_PROPERTY(bool sound READ IsSound WRITE IsSound NOTIFY SoundChanged)
        Q_PROPERTY(bool cameras READ IsCameras WRITE IsCameras NOTIFY CamerasChanged)
        // Q_PROPERTY(double dirhamsPerHour READ GetDirhamsPerHour WRITE SetDirhamsPerHour NOTIFY DirhamsPerHourChanged)
        Q_PROPERTY(float score READ GetReviewScore NOTIFY ScoreChanged)
        Q_PROPERTY(unsigned int numberOfReviews READ GetNumberOfReviews NOTIFY NumberOfReviewsChanged)
        Q_PROPERTY(bool reviewed READ IsReviewed NOTIFY ReviewedChanged)
        Q_PROPERTY(QVector<QString> reviews READ GetReviews NOTIFY ReviewsChanged)
        // Q_PROPERTY(QVector<QString> tags READ GetTags NOTIFY TagsChanged)

        Q_PROPERTY(QDimensions* dims MEMBER m_dims NOTIFY DimsChanged)
        Q_PROPERTY(QSeating* seats MEMBER m_seats NOTIFY SeatsChanged)
        Q_PROPERTY(QTime* timer MEMBER m_timer NOTIFY TimerChanged)
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
        void ScoreChanged();
        void NumberOfReviewsChanged();
        void ReviewedChanged();
        void ReviewsChanged();
        void TagsChanged();
        void DimsChanged();
        void SeatsChanged();
        void TimerChanged();
    private:
        Space* space_ref;
        bool wasCreated;
    public:
        QDimensions* m_dims;
        QSeating* m_seats;
        QTime* m_timer;
        // Creating a new space
        QSpace(unsigned int p_ID,
            std::string p_name,
            const Dimensions& p_dims,
            const Seating& p_seats,
            unsigned int p_numberOfPeople,
            double p_dirhamsPerHour,

            // Optional
            bool p_outdoor = false,
            bool p_catering = false,
            bool p_naturalLight = false,
            bool p_artificialLight = true,
            bool p_projector = true,
            bool p_sound = true,
            bool p_cameras = true,
            float p_score = 0,
            QObject *parent = nullptr) : QObject(parent) {

            space_ref = new Space(
                p_ID,
                p_name,
                p_dims,
                p_seats,
                p_numberOfPeople,
                p_dirhamsPerHour,
                p_outdoor,
                p_catering,
                p_naturalLight,
                p_artificialLight,
                p_projector,
                p_sound,
                p_cameras,
                p_score
            );
            m_dims = new QDimensions(&(space_ref->dims));
            m_seats = new QSeating(&(space_ref->seats));
            m_timer = new QTime(&(space_ref->timer));
            emit IDChanged();
            emit NameChanged();
            emit NumberOfPeopleChanged();
            emit OutdoorChanged();
            emit CateringChanged();
            emit NaturalLightChanged();
            emit ArtificialLightChanged();
            emit ProjectorChanged();
            emit SoundChanged();
            emit CamerasChanged();
            emit DirhamsPerHourChanged();
            emit ScoreChanged();
            emit NumberOfReviewsChanged();
            emit ReviewedChanged();
            emit ReviewsChanged();
            emit TagsChanged();
            emit DimsChanged();
            emit SeatsChanged();
            emit TimerChanged();

            wasCreated = true;
        }
        // Adapting an existing space
        QSpace(Space& p_space) {
            space_ref = &p_space;
            m_dims = new QDimensions(&(space_ref->dims));
            m_seats = new QSeating(&(space_ref->seats));
            m_timer = new QTime(&(space_ref->timer));
            wasCreated = false;
        }
        // Destructor
         ~QSpace() {
            delete m_dims;
            delete m_seats;
            delete m_timer;
            if (wasCreated)
                delete space_ref;
         }

        // Setters
        void Rename(const QString& p_name) {
            space_ref->Rename(p_name.toStdString());
            emit NameChanged();
        }
        void SetID(unsigned int p_ID) {
            space_ref->SetID(p_ID);
            emit IDChanged();
        }
        Q_INVOKABLE void AddReview(const std::string& p_review, float p_score) {
            space_ref->AddReview(p_review, p_score);
            emit ReviewsChanged();
            emit ReviewedChanged();
        }
        // Setters using overload
        void IsOutdoor(bool p_outdoor) { space_ref->IsOutdoor(p_outdoor); }
        void IsCatering(bool p_catering) { space_ref->IsCatering(p_catering); }
        void IsNaturalLight(bool p_naturalLight) { space_ref->IsNaturalLight(p_naturalLight); }
        void IsArtificialLight(bool p_artificialLight) { space_ref->IsArtificialLight(p_artificialLight); }
        void IsProjector(bool p_projector) { IsProjector(p_projector); }
        void IsSound(bool p_sound) { IsSound(p_sound); }
        void IsCameras(bool p_cameras) { IsCameras(p_cameras); }

        // Getters
        QString GetName() { return QString::fromStdString(space_ref->GetName()); }
        unsigned int GetID() { return space_ref->GetID(); }
        float GetReviewScore() { return space_ref->GetReviewScore(); }
        QVector<QString> GetReviews() {
            // https://stackoverflow.com/questions/68771545/convert-vectorstring-to-qvectorqstring
            QVector<QString> tmp_reviews;
            for (std::string v: space_ref->GetReviews()) {
                tmp_reviews.append(QString::fromStdString(v));
            }
            // std::transform(space_ref->GetReviews().begin(), space_ref->GetReviews().end(),
            //                std::back_inserter(tmp_reviews),
            //                [](const std::string &v){ return QString::fromStdString(v); });
            return tmp_reviews;
        }
        unsigned int GetNumberOfReviews() { return space_ref->GetNumberOfReviews(); }
        bool IsOutdoor() { return space_ref->IsOutdoor(); }
        bool IsCatering() { return space_ref->IsCatering(); }
        bool IsNaturalLight() { return space_ref->IsNaturalLight(); }
        bool IsArtificialLight() { return space_ref->IsArtificialLight(); }
        bool IsProjector() { return space_ref->IsProjector(); }
        bool IsSound() { return space_ref->IsSound(); }
        bool IsCameras() { return space_ref->IsCameras(); }
        bool IsReviewed() { return space_ref->IsReviewed(); }
    };
}
