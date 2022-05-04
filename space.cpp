#include <QObject>
#include <QVector>
#include <QString>
#include <qqml.h>

// User libraries
#include "space.h"
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

// Bitwise helpers
// https://stackoverflow.com/questions/62689/bitwise-indexing-in-c
#define GetBit(var, bit) ((var & (1 << bit)) != 0) // Returns true / false if bit is set
#define SetBit(var, bit) (var |= (1 << bit))
#define ClearBit(var, bit) (var &= ~(1 << bit))
#define FlipBit(var, bit) (var ^= (1 << bit))

// Namespace for class objects
namespace space {
    // Class for space dimensions
    // .. Currently assume box-like spaces with length-width-height
    void Dimensions::UpdateAAR() {
        area = length * width;
        // Check for zero before division
        if (width * length != 0) {
            aspectRatio = (length > width) ? (length / width) : (width / length);
        } else aspectRatio = 0;
    }
    // Constructors & destructors
    Dimensions::Dimensions(float p_length, float p_width, float p_height, QObject *parent) : QObject(parent) {
        length = p_length;
        width = p_width;
        height = p_height;
        UpdateAAR();
    }
    // Setters
    void Dimensions::SetLength(float p_length) {
        length = p_length;
        UpdateAAR();
        emit LengthChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }
    void Dimensions::SetWidth(float p_width){
        width = p_width;
        UpdateAAR();
        emit WidthChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }
    void Dimensions::SetHeight(float p_height) {
        height = p_height;
        emit HeightChanged();
    }
    void Dimensions::SetDimensions(float p_length, float p_width, float p_height) {
        length = p_length;
        width = p_width;
        height = p_height;
        emit LengthChanged();
        emit WidthChanged();
        emit HeightChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }

    // Class for seatings
    // Constructors & destructors
    Seating::Seating(unsigned int p_numberOfSeats,
                     bool p_slanted,
                     bool p_surround,
                     bool p_comfy,
                     QObject *parent) : QObject(parent) {
        numberOfSeats = p_numberOfSeats;
        slanted = p_slanted;
        surround = p_surround;
        comfy = p_comfy;
    }
    // Setters
    void Seating::SetNumberOfSeats(unsigned int p_numberOfSeats) {
        numberOfSeats = p_numberOfSeats;
        emit NumberOfSeatsChanged();
    }
    // Setters using overload
    void Seating::IsSlanted(bool p_slanted) {
        slanted = p_slanted;
        emit SlantedChanged();
    }
    void Seating::IsSurround(bool p_surround) {
       surround = p_surround;
        emit SurroundChanged();
    }
    void Seating::IsComfy(bool p_comfy) {
        comfy = p_comfy;
        emit SurroundChanged();
    }

    // Class for available times
    // .. Assume accomodative spaces: working all day
    Time::Time(QObject *parent) : QObject(parent) {
        originTime = time(NULL);
        dirhamsPerHour = 0;
    }
    Time::Time(double p_dirhamsPerHour, QObject *parent) : QObject(parent) {
        originTime = time(NULL);
        // Round up to next hour
        originTime += (86400 - originTime % 86400);
        dirhamsPerHour = p_dirhamsPerHour;
    }
    Time::Time(double p_dirhamsPerHour, const time_t& p_originTime, QObject *parent) : QObject(parent) {
        originTime = p_originTime + (86400 - p_originTime % 86400);
        dirhamsPerHour = p_dirhamsPerHour;
    }
    // Setters
    void Time::SetDirhamsPerHour(double p_dirhamsPerHour) {
        dirhamsPerHour = p_dirhamsPerHour;
        emit DirhamsPerHourChanged();
    }
    // Function to reserve
    // .. param price to return the price
    bool Time::AddReservation(const time_t& p_startTime, const time_t& p_endTime, double& price) {
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
        emit TimesChanged();
        return true;
    }
    // Function to remove reservations
    bool Time::RemoveReservation(const time_t& p_startTime, const time_t& p_endTime) {
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
        emit TimesChanged();
        return true;
    }
}
