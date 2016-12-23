/*
 * MAIN.C (HTTPSERV.C)
 * ===================
 * 
 * This is a small lightweight HTTP server, intended for deployment on Motorola
 * STB. Since version 4.4 Motorola VIP1003 SW tends to freeze after client code
 * upgrade, I needed a way to kill process from JS and this seemed as a good way
 * to do it.
 * Some ideas and code snippets I found on Internet.. particulary usefull was 
 * webserver written by Paul Griffiths (1999). I built my solution around Paul's
 * example changing and fixing some parts.. 
 */

/* 
 * File:    main.c
 * Author:  avrbanac
 * Version: 20160314.0914
 *
 * Created on March 14, 2016, 8:48 AM
 */

#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <sys/wait.h>         /*  for waitpid()             */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/helper.h"
#include "inc/servreq.h"
#include "inc/config.h"

/*
 * Point of entry - init jobs etc...
 */
int main(int argc, char** argv) {
    
    int    listener, connection;
    pid_t  pid;
    struct sockaddr_in servAddr;
    int    confRet;
    
    if (argc > 1) confRet = PopulateConf(argv[1]);
    else confRet = PopulateConf(DEFAULT_CONF);
    if (confRet < 0) ErrorQuit("Problem with reading configuration file!!!");
    
    /*  Create socket  */
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0) ErrorQuit("Couldn't create listening socket.");
    
    /*  Init socket address structure  */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port        = htons(config.PORT);
    
    /*  Assign socket address to socket  */ 
    if (bind(listener, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) ErrorQuit("Couldn't bind listening socket.");
    
     /*  Try to make it a listening connection  */
    if (listen(listener, config.STR_SIZE_L) <0 ) ErrorQuit("Call to listen failed.");
    
    while (1) {
    	/*  Wait for connection  */
    	if ((connection = accept(listener, NULL, NULL)) < 0) ErrorQuit("Error calling accept()");

    	/*  Fork to child in order to service connection  */
    	if ((pid = fork()) == 0) {

    	    /*  This is a body of a child process, so
    		need to close socket and service request  */
    	    if ( close(listener) < 0 )
    		ErrorQuit("Error closing listening socket in child.");
    	    
    	    ServiceRequest(connection);

    	    /*  This child process is done, close connection  */
    	    if (close(connection) < 0)
    		ErrorQuit("Error closing connection socket.");
    	    exit(EXIT_SUCCESS);
    	}

    	/*  This is parent process, here we need to close 
            the connected socket, clean up child processes,
    	    and go back for a new connection.  */
    	if (close(connection) < 0) ErrorQuit("Error closing connection socket in parent.");

    	waitpid(-1, NULL, WNOHANG);
    }

    /*  ERROR???  */
    return (EXIT_SUCCESS);
}

