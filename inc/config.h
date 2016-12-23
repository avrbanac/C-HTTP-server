/*
 * CONFIG.H
 * ========
 * 
 * Interface to configuration values for simple HTTPSERV.
 *
 * File:   config.h
 * Author: avrbanac
 *
 * Created on March 14, 2016, 9:40 AM
 */

#ifndef AV_CONFIG_H
#define AV_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define STR_SIZE_CONF_VALUE (256)
#define DEFAULT_CONF        "config.ini"
#define CONF_REQ            (12)

typedef struct Configuration {
    char APP_VERSION[STR_SIZE_CONF_VALUE];
    char APP_VER_BUILD[STR_SIZE_CONF_VALUE];
    char SCRIPT_NAME[STR_SIZE_CONF_VALUE];
    char SCRIPT_PATH[STR_SIZE_CONF_VALUE];
    char EXECUTABLE_PATH[STR_SIZE_CONF_VALUE];
    char SERVER_ROOT[STR_SIZE_CONF_VALUE];
    char ACTION_CMD[STR_SIZE_CONF_VALUE];
    char ACTION_RUN[STR_SIZE_CONF_VALUE];
    int PORT, STR_SIZE_L, STR_SIZE_M, STR_SIZE_S;
} Config;

/*  Global structure in which all the configuration will be  */
Config config;

/*  Function that populates required configuration structure  */
int PopulateConf (char *filename);

/*  Helper function to remove comments from config file  */
char * RmComment(char *buffer);

/*  Helper function to trim string by creating new one  */
size_t TrimWhiteSpace(char *out, size_t len, const char *str);


#ifdef __cplusplus
}
#endif

#endif /* AV_CONFIG_H */
