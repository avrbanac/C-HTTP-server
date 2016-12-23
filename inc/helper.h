/* 
 * HELPER.H
 * ========
 * 
 * Interface to helper functions for simple HTTP server.
 * 
 * File:   helper.h
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:56 AM
 */

#ifndef HELPER_H
#define HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

/*  for ssize_t data type  */   
#include <unistd.h>
    
/*  Function prototypes  */
void    ErrorQuit	(char const * msg);
char *  Trim      	(char *buffer);
int     StrUpper  	(char *buffer);
void    CleanURL  	(char *buffer);
ssize_t ReadLine  	(int sockd, void *vptr, size_t maxlen);
ssize_t WriteLine 	(int sockd, const void *vptr, size_t n);
int 	StartsWith	(const char *haystack, const char *needle);
char *  SubStr 		(const char *haystack, const char *needle);
void	StrCharReplace  (char *haystack, char needle, char pin);
char *  RmTrash		(char *buffer);

#ifdef __cplusplus
}
#endif

#endif /* HELPER_H */

