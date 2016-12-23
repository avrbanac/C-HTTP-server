/*
 * REQHEAD.H
 * =========
 *
 * Interface to functions for manipulating HTTP request headers.
 * 
 * File:   reqhead.h
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:48 AM
 */

#ifndef REQHEAD_H
#define REQHEAD_H

#ifdef __cplusplus
extern "C" {
#endif

/*  User-defined data types  */
enum Req_Method { GET, HEAD, UNSUPPORTED };
enum Req_Type   { SIMPLE, FULL };

struct ReqInfo {
    enum Req_Method method;
    enum Req_Type   type;
    char *referer, *useragent, *resource;
    int  status;
};

/*  Function prototypes  */
int     ParseHTTPHeader (char * buffer, struct ReqInfo *reqInfo);
int     GetRequest      (int conn, struct ReqInfo *reqInfo);
void    InitReqInfo     (struct ReqInfo *reqInfo);
void    FreeReqInfo     (struct ReqInfo *reqInfo);


#ifdef __cplusplus
}
#endif

#endif /* REQHEAD_H */

