#include <QObject>
#include <QString>
#include <qqml.h>

// User libraries
#include "qspace.h"
#include <string>
#include <vector>
#include <ctime>

// Qt wrapper for Space classes
namespace Space {
    // Class for space dimensions
    // .. Currently assume box-like spaces with length-width-height
    QDimensions::QDimensions(Dimensions* p_dims_ref, QObject *parent) : QObject(parent) {
        dims_ref = p_dims_ref;
    }
    // Setters
    void QDimensions::SetLength(float p_length) {
        dims_ref->SetLength(p_length);
        emit LengthChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }
    void QDimensions::SetWidth(float p_width) {
        dims_ref->SetWidth(p_width);
        emit WidthChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }
    void QDimensions::SetHeight(float p_height) {
        dims_ref->SetHeight(p_height);
        emit HeightChanged();
    }
    void QDimensions::SetDimensions(float p_length, float p_width, float p_height) {
        dims_ref->SetDimensions(p_length, p_width, p_height);
        emit LengthChanged();
        emit WidthChanged();
        emit AreaChanged();
        emit AspectRatioChanged();
    }

    // Class for seatings
    QSeating::QSeating(Seating* p_seats_ref, QObject *parent) : QObject(parent) {
        seats_ref = p_seats_ref;
    }
    // Setters
    void QSeating::SetNumberOfSeats(unsigned int p_numberOfSeats) {
        seats_ref->SetNumberOfSeats(p_numberOfSeats);
        emit NumberOfSeatsChanged();
    }
    // Setters using overload
    void QSeating::IsSlanted(bool p_slanted) {
        seats_ref->IsSlanted(p_slanted);
        emit SlantedChanged();
    }
    void QSeating::IsSurround(bool p_surround) {
        seats_ref->IsSurround(p_surround);
        emit SurroundChanged();
    }
    void QSeating::IsComfy(bool p_comfy) {
        seats_ref->IsComfy(p_comfy);
        emit SurroundChanged();
    }

    // Class for available times
    // .. Assume accomodative spaces: working all day
    QTime::QTime(Time* p_timer_ref, QObject *parent) : QObject(parent) {
        timer_ref = p_timer_ref;
    }
    // Setters
    void QTime::SetDirhamsPerHour(double p_dirhamsPerHour) {
        timer_ref->SetDirhamsPerHour(p_dirhamsPerHour);
        emit DirhamsPerHourChanged();
    }
    // Function to reserve
    // .. param price to return the price
    bool QTime::AddReservation(const time_t& p_startTime, const time_t& p_endTime, double& price) {
        bool success = timer_ref->AddReservation(p_startTime, p_endTime, price);
        if (success) emit TimesChanged();
        return success;
    }
    // Function to remove reservations
    bool QTime::RemoveReservation(const time_t& p_startTime, const time_t& p_endTime) {
        bool success = timer_ref->RemoveReservation(p_startTime, p_endTime);
        if (success) emit TimesChanged();
        return success;
    }
}
