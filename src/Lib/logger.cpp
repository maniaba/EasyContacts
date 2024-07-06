#include "logger.h"

Logger::Logger()
{
    logFile.setFileName("error.log");
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Ne mogu otvoriti log fajl za pisanje.";
    }
}

Logger::~Logger()
{
    if (logFile.isOpen()) {
        logFile.close();
    }
}

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::logError(const QString &message)
{
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        out << timestamp << " - ERROR: " << message << "\n";
    } else {
        qDebug() << "Log fajl nije otvoren.";
    }
}
