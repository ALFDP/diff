#include "logger.h"

/**

Initializes the logger process

@return Error code of the initialization

**/
unsigned char logInit()
{
    const char *logFilePath = "logger.inf";
    FILE* configFile = fopen(logFilePath, "r");
    LoggerConfig config = {0xff, NULL};

    if(configFile == NULL)
    {
        fprintf(stderr, "Logger's config file not found at %s. Applying default configuration style.", logFilePath);
        config.file = stderr;
    }

    else
    {
        config = buildLoggerConfig(configFile);
    }

    setLoggerConfig(&config);

    atexit(logQuit);

    return 0x00;
}

unsigned char logWrite(const char *log, unsigned char level)
{
    LoggerConfig config = getLoggerConfig();
    if(level > config.level)
    {
        fprintf(config.file, log);
        return 0;
    }

    return 1;
}

void logQuit()
{
    LoggerConfig config = getLoggerConfig();

    if(config.file != NULL)
    {
        fclose(config.file);
    }
}

LoggerConfig getLoggerConfig()
{
    return getLoggerConfig(NULL);
}

LoggerConfig setLoggerConfig(LoggerConfig *old)
{
    static LoggerConfig config;

    if(old != NULL)
    {
        config = *old;
    }

    return config;
}

LoggerConfig buildLoggerConfig(FILE *configFile)
{
    char buff[CONFIG_BUFF_SIZE] = "";
    char *buffPointer = NULL;
    const char *instr[CONFIG_INSTR_ARRAY_SIZE] = {"logLevel", "logFile"};
    LoggerConfig config;

    while(!feof(configFile))
    {
        fgets(buff, CONFIG_BUFF_SIZE, configFile);
        if((buffPointer = strchr(buff, '=')) != NULL)
        {
            *buffPointer = '\0';
            buffPointer++;
            LoggerConfigRoutingProc(&config, buffPointer, inArray(buffPointer, instr, CONFIG_INSTR_ARRAY_SIZE));
        }
        else
        {
            fprintf(stderr, "Warning : \"%s\" line could not be parsed !", buff);
        }
    }

    return config;
}

unsigned int inArray(const char *str, const char **array, unsigned int arraySize)
{
    register unsigned int i;

    for(i = 0 ; i < arraySize ; i++)
    {
        if(!stricmp(str, array[i]))
        {
            return i;
        }
    }

    return i;
}

void LoggerConfigRoutingProc(LoggerConfig *config, const char *value, unsigned int index)
{
    switch(index)
    {
        case 0:
            config->level = atoi(value);
            break;
        case 1:
            config->file = config->file!=NULL?config->file:fopen(value, "w");
            break;
        default :
            fprintf(stderr, "Warning : Trying to parse unknown logger's configuration command !");

    }
}
