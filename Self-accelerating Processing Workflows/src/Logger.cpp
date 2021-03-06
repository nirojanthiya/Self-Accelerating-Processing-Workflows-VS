#include "Logger.h"

Logger Logger::instance;

Logger::Logger() {}

void Logger::open(const string& logFile) {
    instance.fileStream.open(logFile.c_str(), ios::app);
}
void Logger::close() {
    instance.fileStream.close();
}
void Logger::write(const string& message) {
    ostream& stream = instance.fileStream;
    stream << message;
}

void Logger::clearLogs(const string& logFile) {
    if (Logger::isOpen()) {
        Logger::close();
    }
    instance.fileStream.open(logFile.c_str());
    ostream& stream = instance.fileStream;
    stream << "";
}
bool Logger::isOpen() {
    return instance.fileStream.is_open();
}