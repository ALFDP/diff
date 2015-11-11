#ifndef LOGGER_H

    #define LOGGER_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #define CONFIG_BUFF_SIZE 256
    #define CONFIG_INSTR_ARRAY_SIZE 2

    typedef struct
    {
        unsigned char level;
        FILE* file;
    } LoggerConfig;

    unsigned char logInit();
    unsigned char logWrite(const char *log, unsigned char level);
    void logQuit();

    LoggerConfig getLoggerConfig();
    LoggerConfig setLoggerConfig(LoggerConfig *newConf);
    LoggerConfig buildLoggerConfig(FILE *configFile);

    unsigned int inArray(const char *str, const char **array, unsigned int arraySize);
    void LoggerConfigRoutingProc(LoggerConfig *config, const char *value, unsigned int index);

    enum {TRACE = 0, INFO = 1, DEBUG = 2, WARNING = 3, ERROR = 4, FATAL = 5};

#endif // LOGGER_H
