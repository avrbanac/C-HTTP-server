/* 
 * HELPER.C
 * ========
 * 
 * Implementation of helper functions for simple HTTP server.
 * 
 * File:   helper.c
 * Author: avrbanac
 *
 * Created on March 14, 2016, 11:15 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "../inc/helper.h"

/*  Prints an error message and quits  */
void ErrorQuit(char const *msg) {
    fprintf(stderr, "WEBSERV: %s\n", msg);
    exit(EXIT_FAILURE);
}

/*  Read a line from a socket  */
ssize_t ReadLine(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(sockd, &c, 1)) == 1) {
            *buffer++ = c;
            if (c == '\n') break;
        }
        else if (rc == 0) {
            if (n == 1) return 0;
            else break;
        }
        else {
            if (errno == EINTR) continue;
            ErrorQuit("Error in ReadLine()");
        }
    }

    *buffer = 0;
    return n;
}

/*  Write a line to a socket  */
ssize_t WriteLine(int sockd, const void *vptr, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    const char *buffer;

    buffer = vptr;
    nleft  = n;

    while (nleft > 0) {
	if ((nwritten = write(sockd, buffer, nleft)) <= 0) {
            if (errno == EINTR) nwritten = 0;
            else ErrorQuit("Error in WriteLine()");
	}
	nleft  -= nwritten;
	buffer += nwritten;
    }

    return n;
}

/*  Removes trailing whitespace from a string  */
char * Trim(char *buffer) {
    char *end;

    // Trim leading space
    while(isspace(*buffer)) buffer++;

    // All spaces???
    if(*buffer == 0) return buffer;

    // Trim trailing space
    end = buffer + strlen(buffer) - 1;
    while (end > buffer && isspace(*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return buffer;
}

/*  Converts a string to upper-case  */
int StrUpper(char *buffer) {
    while (*buffer) {
	*buffer = toupper(*buffer);
	++buffer;
    }

    return 0;
}

/*  Cleans up url-encoded string  */	
void CleanURL(char * buffer) {
    char asciinum[3] = {0};
    int i = 0, c;
    
    while ( buffer[i] ) {
        if ( buffer[i] == '+' ) buffer[i] = ' ';
	else if ( buffer[i] == '%' ) {
            asciinum[0] = buffer[i+1];
            asciinum[1] = buffer[i+2];
            buffer[i] = strtol(asciinum, NULL, 16);
            c = i+1;
            do {
                buffer[c] = buffer[c+2];
            } while ( buffer[2+(c++)] );
        }
        ++i;
    }
}

/*  Checks if string (haystack) starts with substring (needle)  */
int StartsWith(const char *haystack, const char *needle) {
    if(strncmp(haystack, needle, strlen(needle)) == 0) return 1;
    return 0;
}

/*  Remove substring (needle) from string (haystack)  */
char * SubStr (const char *haystack, const char *needle) {
    return (char*)haystack + strlen(needle);
}

/*  Replace char (needle) with another char (pin) in string (haystack)  */
void StrCharReplace (char *haystack, char needle, char pin) {
	int i = 0;

	while (haystack[i] != '\0') {
		if (haystack[i] == needle) haystack[i] = pin;
		i++;
	}
}

char * RmTrash(char *buffer) {
    int i;
    for (i=0; i<strlen(buffer); i++) {
        if (isspace(buffer[i])) break;
    }
  
    buffer[i] = '\0';
    return buffer;
}     
