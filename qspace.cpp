#include <QObject>
#include <QString>
#include <qqml.h>

// User libraries
#include "space.cpp"
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

// Bitwise helpers
// https://stackoverflow.com/questions/62689/bitwise-indexing-in-c
#define GetBit(var, bit) ((var & (1 << bit)) != 0) // Returns true / false if bit is set
#define SetBit(var, bit) (var |= (1 << bit))
#define ClearBit(var, bit) (var &= ~(1 << bit))
#define FlipBit(var, bit) (var ^= (1 << bit))

// Qt wrapper for Space classes
namespace Space {
    // Class for space dimensions
    // .. Currently assume box-like spaces with length-width-height
    class QDimensions : public QObject {
        Q_OBJECT
        Q_PROPERTY(float QLength READ QLength WRITE setQLength NOTIFY QLengthChanged)
        Q_PROPERTY(float QWidth READ QWidth WRITE setQWidth NOTIFY QWidthChanged)
        Q_PROPERTY(float QHeight READ QHeight WRITE setQHeight NOTIFY QHeightChanged)
        Q_PROPERTY(float QArea READ QArea WRITE setQArea NOTIFY QAreaChanged)
        Q_PROPERTY(float QAspectRatio READ QAspectRatio WRITE setQAspectRatio NOTIFY QAspectRatioChanged)
    signals:
        void QLengthChanged();
        void QWidthChanged();
        void QHeightChanged();
        void QAreaChanged();
        void QAspectRatioChanged();
    private:
        Dimensions* dims_ref;
    public:
        explicit QDimensions(Dimensions* p_dims_ref = nullptr, QObject *parent = nullptr) : QObject(parent) {
            dims_ref = p_dims_ref;
        }
        virtual ~QDimensions() {}
        // Setters
        void setQLength(float p_length) {
            dims_ref->SetLength(p_length);
            emit QLengthChanged();
            emit QAreaChanged();
            emit QAspectRatioChanged();
        }
        void setQWidth(float p_width) {
            dims_ref->SetWidth(p_width);
            emit QWidthChanged();
            emit QAreaChanged();
            emit QAspectRatioChanged();
        }
        void setQHeight(float p_height) {
            dims_ref->SetHeight(p_height);
            emit QHeightChanged();
        }
        void setQDimensions(float p_length, float p_width, float p_height) {
            dims_ref->SetDimensions(p_length, p_width, p_height);
            emit QLengthChanged();
            emit QWidthChanged();
            emit QAreaChanged();
            emit QAspectRatioChanged();
        }

        // Getters
        float QLength() { return dims_ref->GetLength(); }
        float QWidth() { return dims_ref->GetWidth(); }
        float QHeight() { return dims_ref->GetHeight(); }
        float QArea() { return dims_ref->GetArea(); }
        float QAspectRatio() { return dims_ref->GetAspectRatio(); }
    };

    // Class for seatings
    class QSeating : public QObject {
        Q_OBJECT
        Q_PROPERTY(unsigned int QNumberOfSeats READ QNumberOfSeats WRITE setQNumberOfSeats NOTIFY QNumberOfSeatsChanged)
        Q_PROPERTY(bool QSlanted READ QSlanted WRITE setQSlanted NOTIFY QSlantedChanged)
        Q_PROPERTY(bool QSurround READ QSurround WRITE setQSurround NOTIFY QSurroundChanged)
        Q_PROPERTY(bool QComfy READ QComfy WRITE setQComfy NOTIFY QComfyChanged)
    signals:
        void QNumberOfSeatsChanged();
        void QSlantedChanged();
        void QSurroundChanged();
        void QComfyChanged();
    private:
        Seating* seats_ref;
    public:
        explicit QSeating(Seating* p_seats_ref = nullptr, QObject *parent = nullptr) : QObject(parent) {
            seats_ref = p_seats_ref;
        }
        virtual ~QSeating() {}
        // Setters
        void setQNumberOfSeats(unsigned int p_numberOfSeats) {
            seats_ref->SetNumberOfSeats(p_numberOfSeats);
            emit QNumberOfSeatsChanged();
        }
        // Setters using overload
        void IsSlanted(bool p_slanted) {
            seats_ref->IsSlanted(p_slanted);
            emit QSlantedChanged();
        }
        void IsSurround(bool p_surround) {
            seats_ref->IsSurround(p_surround);
            emit QSurroundChanged();
        }
        void IsComfy(bool p_comfy) {
            seats_ref->IsComfy(p_comfy);
            emit QSurroundChanged();
        }

        // Getters
        bool IsSlanted() { return seats_ref->IsSlanted(); }
        bool IsSurround() { return seats_ref->IsSurround(); }
        bool IsComfy() {return seats_ref->IsComfy(); }
        unsigned int GetNumberOfSeats() { return seats_ref->GetNumberOfSeats(); }
    };

    // Class for available times
    // .. Assume accomodative spaces: working all day
    class QTime {
    private:
        time_t originTime;
        // Using a list of unsigned long long integers
        // .. to keep track of allocated time
        // .. Each bit corresponds to 1 hour
        // .. More long longs added based on scheduler
        // .. 64 bits per each corresponding to 2.67 days
        std::vector<unsigned long long> times;
        // Price per hour
        double dirhamsPerHour = 0;
    public:
        QTime() {
            originTime = time(NULL);
            dirhamsPerHour = 0;
        }
        QTime(double p_dirhamsPerHour){
            originTime = time(NULL);
            // Round up to next hour
            originTime += (86400 - originTime % 86400);
            dirhamsPerHour = p_dirhamsPerHour;
        }
        QTime(double p_dirhamsPerHour, const time_t& p_originTime) {
            originTime = p_originTime + (86400 - p_originTime % 86400);
            dirhamsPerHour = p_dirhamsPerHour;
        }
        // Function to reserve
        // .. param price to return the price
        bool AddReservation(const time_t& p_startTime, const time_t& p_endTime, double& price) {
            // Initialize price
            price = 0;
            // Get hours difference between startTime, endTime and originTime
            // .. Hour is tracked from beginning o'clock -> floor is used here
            unsigned long startHours = (unsigned long)std::floor(std::difftime(p_startTime, originTime) / (60 * 60));
            unsigned long endHours = (unsigned long)std::floor(std::difftime(p_endTime, originTime) / (60 * 60));
            // Invalid reservation
            if (endHours < startHours or startHours < 0) return false;
            if (times.size() < endHours / 64)
                while (times.size() <= endHours / 64) times.push_back(0);
            // Check if any hour in the reservation is booked
            if (startHours / 64 == endHours / 64) {
                for (unsigned long i = startHours % 64; i <= endHours % 64; i++)
                    if GetBit(times[startHours / 64], i)
                        // Time is occupied
                        return false;
            } else {
                for (unsigned long i = startHours % 64; i < 64; i++)
                    if GetBit(times[startHours / 64], i)
                        // Time is occupied
                        return false;
                unsigned long j = startHours / 64;
                while (j != endHours / 64) {
                    for (unsigned long i = 0; i < 64; i++)
                        if GetBit(times[startHours / 64], i)
                            // Time is occupied
                            return false;
                    j++;
                }
                for (unsigned long i = 0; i <= endHours % 64; i++)
                    if GetBit(times[endHours / 64], i)
                        // Time is occupied
                        return false;
            }
            // If not, proceed to select the hours
            if (startHours / 64 == endHours / 64) {
                for (unsigned long i = startHours % 64; i <= endHours % 64; i++)
                    SetBit(times[startHours / 64], i);
            } else {
                for (unsigned long i = startHours % 64; i < 64; i++)
                    SetBit(times[startHours / 64], i);
                unsigned long j = startHours / 64;
                while (j != endHours / 64) {
                    times[startHours / 64] = ~0;
                    j++;
                }
                for (unsigned long i = 0; i <= endHours % 64; i++)
                    SetBit(times[endHours / 64], i);
            }
            price = dirhamsPerHour * (endHours - startHours + 1);
        }
        // Function to remove reservations
        bool RemoveReservation(const time_t& p_startTime, const time_t& p_endTime) {
            // Get hours difference between startTime, endTime and originTime
            // .. Hour is tracked from beginning o'clock -> floor is used here
            unsigned long startHours = (unsigned long)std::floor(std::difftime(p_startTime, originTime) / (60 * 60));
            unsigned long endHours = (unsigned long)std::floor(std::difftime(p_endTime, originTime) / (60 * 60));
            // Invalid reservation
            if (endHours < startHours or startHours < 0) return false;
            if (times.size() < endHours / 64)
                while (times.size() <= endHours / 64) times.push_back(0);
            // Directly clear the hours
            if (startHours / 64 == endHours / 64) {
                for (unsigned long i = startHours % 64; i <= endHours % 64; i++)
                    ClearBit(times[startHours / 64], i);
            } else {
                for (unsigned long i = startHours % 64; i < 64; i++)
                    ClearBit(times[startHours / 64], i);
                unsigned long j = startHours / 64;
                while (j != endHours / 64) {
                    times[startHours / 64] = 0;
                    j++;
                }
                for (unsigned long i = 0; i <= endHours % 64; i++)
                    ClearBit(times[endHours / 64], i);
            }
        }
    };

    // Class for each discrete space
    class QSpace {
    private:
        unsigned int ID;
        std::string name;
    public:
        Dimensions dims;
    private:

        // Event-specific characteristics
        // .. Accomodation
        unsigned int numberOfPeople = 0;
        Seating seats;
    private:
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
    public:
        Time timer;
    private:

        // For reviews
        // .. Constrained to 0 to 5
        float score = 0;
        unsigned int numberOfReviews = 0;
        bool beenReviewed = false;
        std::vector<std::string> reviews;

        // Miscellaneous tags
        std::vector<std::string> tags;
    public:
        QSpace() {
            ID = 0;
            name = "";
            dims = Dimensions();
            seats = Seating();
            timer = Time();
        }
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
            float p_score = 0) {

            // Manual work
            ID = p_ID;
            name = p_name;
            // Use built-in copy constructor
            dims = p_dims;
            seats = p_seats;
            numberOfPeople = p_numberOfPeople;
            dirhamsPerHour = p_dirhamsPerHour;
            // Set current time as origin time
            timer = Time(p_dirhamsPerHour);
            outdoor = p_outdoor;
            catering = p_catering;
            naturalLight = p_naturalLight;
            artificialLight = p_artificialLight;
            projector = p_projector;
            sound = p_sound;
            cameras = p_cameras;
            score = p_score;
        }

        // Setters
        void Rename(const std::string& p_name) {
            name = p_name;
        }
        void SetID(unsigned int p_ID) {
            ID = p_ID;
        }
        void AddReview(const std::string& p_review, float p_score) {
            reviews.push_back(p_review);
            score = (score * numberOfReviews + p_score) / (++numberOfReviews);
        }
        // Setters using overload
        bool IsOutdoor() { return outdoor; }
        bool IsCatering() { return catering; }
        bool IsNaturalLight() { return naturalLight; }
        bool IsArtificialLight() { return artificialLight; }
        bool IsProjector() { return projector; }
        bool IsSound() { return sound; }
        bool IsCameras() { return cameras; }

        // Getters
        std::string GetName() { return name; }
        unsigned int GetID() { return ID; }
        float GetReviewScore() { return score; }
        std::vector<std::string> GetReviews() { return reviews; }
        void IsOutdoor(bool p_outdoor) { outdoor = p_outdoor; }
        void IsCatering(bool p_catering) { catering = p_catering; }
        void IsNaturalLight(bool p_naturalLight) { naturalLight = p_naturalLight; }
        void IsArtificialLight(bool p_artificialLight) { artificialLight = p_artificialLight; }
        void IsProjector(bool p_projector) { projector = p_projector; }
        void IsSound(bool p_sound) { sound = p_sound; }
        void IsCameras(bool p_cameras) { cameras = p_cameras; }
    };

    // Class for groups of spaces in the same location (superspace)
    // .. Managed by space-managers
    class QSuperSpace {
    private:
        unsigned long ID;
        std::string name;
        double latitude, longitude;

        // Spaces available in superspace
        std::vector<Space> spaces;

        // Internal spaces characteristics
        unsigned long maxNumberOfPeople = 0;
        // .. Portion of full capacity space can host parking
        float parkingCapacity = 1.0;
    public:
        QSuperSpace(){}
        QSuperSpace(unsigned long p_ID, const std::string& p_name, double p_longitude, double p_latitude) {
            ID = p_ID;
            name = p_name;
            longitude = p_longitude;
            latitude = p_latitude;
        }

    };
}
