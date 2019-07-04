#ifndef WEATHER_H
#define WEATHER_H

#include "weatherdata.h"

#include <QDateTime>

struct Weather
{
    weatherData weatherData;
    QDate date;
    QTime time;
};

#endif // WEATHER_H
