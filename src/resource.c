/*
 * RESOURCE.C
 * ==========
 *
 * Implementation of functions for returning a resource / starting an action.
 * 
 * File:   resource.c
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:42 AM
 */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "../inc/resource.h"
#include "../inc/reqhead.h"
#include "../inc/helper.h"
#include "../inc/config.h"

/*  Returns a resource  */
int ReturnResource(int conn, int resource, struct ReqInfo *reqInfo) {

    char c;
    int  i;

    while ((i = read(resource, &c, 1))) {
    	if (i < 0) ErrorQuit("Error reading from file.");
    	if (write(conn, &c, 1) < 1) ErrorQuit("Error sending file.");
    }

    return 0;
}

/*  Tries to open a resource. The calling function can use
    the return value to check for success, and then examine
    errno to determine the cause of failure if neceesary.    */
int CheckResource(struct ReqInfo *reqInfo, int *isAction, char *args) {
    int i;

    /*  Resource name can contain urlencoded
	data, so clean it up just in case.    */
    CleanURL(reqInfo->resource);

    /*  If we are in 'CMD' mode  */
    if (StartsWith(reqInfo->resource, config.ACTION_CMD) == 1) {
        *isAction = 1;

        strcpy(args, SubStr(reqInfo->resource, config.ACTION_CMD));
        RmTrash(args);
        
        /*  we need to return something else than negative value  */
        return 0;
    }
    /*  If we are in 'RUN' mode  */
    else if (StartsWith(reqInfo->resource, config.ACTION_RUN) == 1) {
        *isAction = 2;
        
        strcpy(args, SubStr(reqInfo->resource, config.ACTION_RUN));
        RmTrash(args);
        
        /*  we need to return something else than negative value  */
        return 0;
    }
    else {
        /*  Concatenate resource name to server root, and try to open  */
        strcat(config.SERVER_ROOT, reqInfo->resource);
        return open(config.SERVER_ROOT, O_RDONLY);
    }
}

/*  Returns an error message  */
int ReturnErrorMsg(int conn, struct ReqInfo * reqInfo) {
    
    char buffer[config.STR_SIZE_S];

    sprintf(buffer, "<HTML>\n<HEAD>\n<TITLE>Server Error %d</TITLE>\n"
	            "</HEAD>\n\n", reqInfo->status);
    WriteLine(conn, buffer, strlen(buffer));

    sprintf(buffer, "<BODY>\n<H1>Server Error %d</H1>\n", reqInfo->status);
    WriteLine(conn, buffer, strlen(buffer));

    sprintf(buffer, "<P>The request could not be completed.</P>\n"
	            "</BODY>\n</HTML>\n");
    WriteLine(conn, buffer, strlen(buffer));

    return 0;
}

int ReturnActionMsg(int mode, int conn, char *command) {
    char buffer[config.STR_SIZE_S];

    char actionMode[10];
    
    strcpy(actionMode,"Error");
    if (mode == 1) strcpy(actionMode,"CMD");
    if (mode == 2) strcpy(actionMode,"RUN");
    
    sprintf(buffer, "<HTML>\n<HEAD>\n<TITLE>Server Action with mode: %s</TITLE>\n"
                "</HEAD>\n\n", actionMode);
    WriteLine(conn, buffer, strlen(buffer));

    sprintf(buffer, "<BODY>\n<H1>Server Action with mode: %s</H1>\n", actionMode);
    WriteLine(conn, buffer, strlen(buffer));

    sprintf(buffer, "<P>Request starting with %s or %s redirected as action [/with/args]:<br/>%s</P>\n"
                "</BODY>\n</HTML>\n", config.ACTION_CMD, config.ACTION_RUN,command);
    WriteLine(conn, buffer, strlen(buffer));

    return 0;
}
