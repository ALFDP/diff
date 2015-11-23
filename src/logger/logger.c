#include "logger.h"
#pragma warning (disable : 4996)

/**

Defines the functions that will produce the application's logs.

@author Aurélien DUVAL

**/

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

/**

    Writes a log in the specified log file if its level is greater or equal than the specified level

    @param log The log string to add to the log file
    @param level The level of the log you want to write

    @return An error code which says if the log was written or not

**/
unsigned char logWrite(const char *log, unsigned char level)
{
    LoggerConfig config = getLoggerConfig();
    if(level >= config.level)
    {
        fprintf(config.file, log);
        return 0;
    }

    return 1;
}

/**

    Quits the logger process. At exit callback.

**/
void logQuit()
{
    LoggerConfig config = getLoggerConfig();

    if(config.file != NULL)
    {
        fclose(config.file);
    }
}

/**

    Returns the logger configuration

    @return The logger configuration
**/
LoggerConfig getLoggerConfig()
{
    return getLoggerConfig(NULL);
}

/**

    Returns the new logger configuration. Modifies the old one if the parameter is not NULL.

    @param newConf The new configuration value.

    @return The new logger configuration

**/
LoggerConfig setLoggerConfig(LoggerConfig *newConf)
{
    static LoggerConfig config;

    if(newConf != NULL)
    {
        config = *newConf;
    }

    return config;
}

/**

    Builds the logger configuration by parsing the default configuration file.

    @return The parsed logger configuration.

**/
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

/**

    Checks if a given string is contained in a given array.

    @param str The string to search
    @param array The string array which compose the test
    @param arraySize The size of the given array

    @return The first index of the matching result

**/
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

/**

    Parses the correct loggers'configuration parameter to the correct element

    @param config The configuration structure to parse
    @param value The value to parse in the structure
    @param index The index which refers to the destination of the value.

**/
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
