/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtQml/QQmlListProperty>

#include <QtPositioning/QGeoPositionInfoSource>

class WeatherData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString dayOfWeek READ dayOfWeek WRITE setDayOfWeek NOTIFY dataChanged)
    Q_PROPERTY(QString weatherIcon READ weatherIcon WRITE setWeatherIcon NOTIFY dataChanged)
    Q_PROPERTY(QString weatherDescription READ weatherDescription WRITE setWeatherDescription NOTIFY dataChanged)
    Q_PROPERTY(int temperature READ temperature WRITE setTemperature NOTIFY dataChanged)

public:
    explicit WeatherData(QObject *parent = 0);
    WeatherData(const WeatherData &other);

    QString dayOfWeek() const;
    QString weatherIcon() const;
    QString weatherDescription() const;
    int temperature() const;

    void setDayOfWeek(const QString &value);
    void setWeatherIcon(const QString &value);
    void setWeatherDescription(const QString &value);
    void setTemperature(int value);

signals:
    void dataChanged();

private:
    QString m_dayOfWeek;
    QString m_weather;
    QString m_weatherDescription;
    int m_temperature;
};

Q_DECLARE_METATYPE(WeatherData)

class WeatherModelPrivate;
class WeatherModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ready READ ready NOTIFY readyChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(WeatherData *weather READ weather NOTIFY weatherChanged)
    Q_PROPERTY(QGeoCoordinate geoCoordinate READ geoCoordinate WRITE setGeoCoordinate NOTIFY geoCoordinateChanged)
    Q_PROPERTY(QQmlListProperty<WeatherData> forecast READ forecast NOTIFY weatherChanged)

public:
    explicit WeatherModel(QObject *parent = 0);
    ~WeatherModel();

    bool ready() const;

    bool active() const;
    void setActive( bool stt );

    void hadError(bool tryAgain);

    void setGeoCoordinate( const QGeoCoordinate & coo );
    QGeoCoordinate geoCoordinate() const;

    WeatherData *weather() const;
    QQmlListProperty<WeatherData> forecast() const;

public slots:
    void refreshWeather();

    void start();
    void stop();

private slots:
    // these would have QNetworkReply* params but for the signalmapper
    void handleWeatherNetworkData(QObject *networkReply);
    void handleForecastNetworkData(QObject *networkReply);

signals:
    void readyChanged();
    void weatherChanged();
    void activeChanged();
    void geoCoordinateChanged();

private:
    WeatherModelPrivate *d;

};

#endif // WEATHERMODEL_H
