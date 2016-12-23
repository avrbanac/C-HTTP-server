/*
 * RESPHEAD.C
 * ==========
 * 
 * Implementation of HTTP reponse header functions.
 * 
 * File:   config.c
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:34 AM
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../inc/helper.h"
#include "../inc/resphead.h"
#include "../inc/config.h"

/*  Outputs HTTP response headers  */
int OutputHTTPHeaders(int conn, struct ReqInfo *reqInfo) {

    char buffer[config.STR_SIZE_S];

    sprintf(buffer, "HTTP/1.0 %d OK\r\n", reqInfo->status);
    WriteLine(conn, buffer, strlen(buffer));

    sprintf(buffer, "Server: Iskon CMD Server v%s\r\n", config.APP_VERSION);
    WriteLine(conn, buffer, strlen(buffer));

    WriteLine(conn, "Content-Type: text/html\r\n", 25);
    WriteLine(conn, "\r\n", 2);

    return 0;
}