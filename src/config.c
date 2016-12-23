/*
 * CONFIG.C
 * ========
 * 
 * Implementation of configuration read functionality for HTTPSERV.
 * 
 * File:   config.c
 * Author: avrbanac
 *
 * Created on March 14, 2016, 9:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../inc/config.h"

/**
 * PopulateConf function opens filename with configuratin and parses it
 * 
 * @param filename string contains name of the configuration string
 * @return int status
 */
int PopulateConf (char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return -1;
    
    char line[STR_SIZE_CONF_VALUE];
    char trimLine[STR_SIZE_CONF_VALUE];
    char token[STR_SIZE_CONF_VALUE];
    char key[STR_SIZE_CONF_VALUE];
    char value[STR_SIZE_CONF_VALUE];
    char *start, *end, *ptr;
    
    int confCounter = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        /* note that fgets don't strip the terminating \n, checking its
        presence would allow to handle lines longer that sizeof(line) */
        
        RmComment (line);
        TrimWhiteSpace(trimLine,sizeof(line),line);

        if (strlen(trimLine)< 3) continue;
        
        // Token will point to the part before the =
        strcpy(token, strtok(trimLine, "="));
        TrimWhiteSpace(key,sizeof(token),token);

        // Token will point to the part after the =
        strcpy(token, strtok(NULL, "="));
        TrimWhiteSpace(value,sizeof(token),token);

        
        if (value[0] == '"') {
            start = value + 1;
            end = value + strlen(value) - 1;
            *end = 0;
            strcpy(value,start);
        }

        // Since there is no switch case with strings and no templating :P
        if (!strcmp(key,"APP_VERSION")) {
            strcpy(config.APP_VERSION,value);
            confCounter++;
        }
        else if (!strcmp(key,"APP_VER_BUILD")) {
            strcpy(config.APP_VER_BUILD,value);
            confCounter++;
        }
        else if (!strcmp(key,"PORT")) {
            config.PORT = strtol(value,&ptr,10);
            confCounter++;
        }
        else if (!strcmp(key,"SCRIPT_NAME")) {
            strcpy(config.SCRIPT_NAME,value);
            confCounter++;
        }
        else if (!strcmp(key,"SCRIPT_PATH")) {
            strcpy(config.SCRIPT_PATH,value);
            confCounter++;
        }
        else if (!strcmp(key,"EXECUTABLE_PATH")) {
            strcpy(config.EXECUTABLE_PATH,value);
            confCounter++;
        }
        else if (!strcmp(key,"SERVER_ROOT")) {
            strcpy(config.SERVER_ROOT,value);
            confCounter++;
        }
        else if (!strcmp(key,"ACTION_CMD")) {
            strcpy(config.ACTION_CMD,value);
            confCounter++;
        }
        else if (!strcmp(key,"ACTION_RUN")) {
            strcpy(config.ACTION_RUN,value);
            confCounter++;
        }
        else if (!strcmp(key,"STR_SIZE_L")) {
            config.STR_SIZE_L = strtol(value,&ptr,10);
            confCounter++;
        }
        else if (!strcmp(key,"STR_SIZE_M")) {
            config.STR_SIZE_M = strtol(value,&ptr,10);
            confCounter++;
        }
        else if (!strcmp(key,"STR_SIZE_S")) {
            config.STR_SIZE_S = strtol(value,&ptr,10);
            confCounter++;
        }
        // Else do nothing with it (we skip additional configuration key/value pairs)
        
        if (confCounter == CONF_REQ) {
            fclose(file);
            return 0;
        }

    }

    fclose(file);
    return -1;
}

/**
 * RmComment function removes everything from buffered line after #/;
 * 
 * @param buffer line to be checked for comments
 * @return char* buffer
 */
char * RmComment(char *buffer) {
  int i;
  for (i=0; i<strlen(buffer); i++) {
    if ((buffer[i] == '#') || (buffer[i] == ';')) break;
  }

  buffer[i] = '\0';
  return buffer;
}     

/**
 * TrimWhiteSpace function removes whitespaces before and after buffered string
 * 
 * @param out pointer to new string
 * @param len size of input string
 * @param str input buffer string
 * @return size of new string
 */
size_t TrimWhiteSpace(char *out, size_t len, const char *str) {
    if(len == 0) return 0;
 
    const char *end;
    size_t out_size;
 
    // Trim leading space
    while(isspace(*str)) str++;
 
    // all spaces ???
    if(*str == 0) {   
        *out = 0;
        return 1;
    } 
 
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    end++;
 
    // Set output size to minimum of trimmed string length and buffer size minus 1
    out_size = (end - str) < len-1 ? (end - str) : len-1;
 
    // Copy trimmed string and add null terminator
    memcpy(out, str, out_size);
    out[out_size] = 0;
 
    return out_size;
}