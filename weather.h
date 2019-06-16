#ifndef WEATHER_H
#define WEATHER_H
#include "weatherdata.h"
#include <QDateTime>
struct Weather
{
    weatherData weatherData;
    QString date;
    QString time;
};

#endif // WEATHER_H
