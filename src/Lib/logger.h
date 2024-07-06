#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

class Logger
{
public:
    static Logger& instance();
    void logError(const QString &message);

    QFile logFile;

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

};

#endif // LOGGER_H
