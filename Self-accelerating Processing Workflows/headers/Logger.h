#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Logger {

public:
    static void open(const string& logFile);
    static void close();
    // write message
    static void write(const string& message);
    static bool isOpen();
    static void clearLogs(const string& logFile);
private:
    Logger();
    ofstream fileStream;
    //Logger instance (singleton)
    static Logger instance;
};