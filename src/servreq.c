/*
 * SERVREQ.C
 * =========
 * 
 * Implementation of service request function.
 * 
 * File:   config.c
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:20 AM
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/helper.h"
#include "../inc/reqhead.h"
#include "../inc/resphead.h"
#include "../inc/resource.h"
#include "../inc/servreq.h"
#include "../inc/config.h"

/*  Service a HTTP request  */
int ServiceRequest(int conn) {
    
    struct ReqInfo  reqInfo;
    int             resource = 0;
    int             isAction = 0;

    char    arguments[config.STR_SIZE_M];
    char    *args = arguments;
    char    command[config.STR_SIZE_L];

    InitReqInfo(&reqInfo);
 
    /*  Get HTTP request  */
    if (GetRequest(conn, &reqInfo) < 0) return -1;

    /*  Check if resource exists, whether we have permission
	to access it, and update status code accordingly. */
    if (reqInfo.status == 200)
    	if ((resource = CheckResource(&reqInfo, &isAction, args)) < 0) {
    	    if (errno == EACCES) reqInfo.status = 401;
    	    else reqInfo.status = 404;
    	}

    /*  It is not request for resource, it is 'CMD' action  */
    if (isAction > 0) {
        /*  Replace all '/'' with ' ' in arguments string  */
        StrCharReplace(args,'/',' ');

        /*  Make command string  */
        if (isAction == 1) {
            strcat(strcat(strcat(strcpy(command,config.SCRIPT_PATH),config.SCRIPT_NAME), " "), args);
        }
        else if (isAction == 2) {
            strcat(strcpy(command,config.EXECUTABLE_PATH),args);
        }
        else ReturnErrorMsg(conn, &reqInfo);
        system(command);

        /*  Output HTTP response headers if we have a full request  */
        if (reqInfo.type == FULL) OutputHTTPHeaders(conn, &reqInfo);
        ReturnActionMsg(isAction, conn, command);
    }
    else {
        /*  Output HTTP response headers if we have a full request  */
        if (reqInfo.type == FULL) OutputHTTPHeaders(conn, &reqInfo);

        /*  Service the HTTP request  */
        if (reqInfo.status == 200) {
        	if (ReturnResource(conn, resource, &reqInfo)) ErrorQuit("Something wrong returning resource.");
        }
        else ReturnErrorMsg(conn, &reqInfo);

        if ((resource > 0) && (close(resource) < 0)) ErrorQuit("Error closing resource.");
    }
    
    FreeReqInfo(&reqInfo);
    return 0;
}

