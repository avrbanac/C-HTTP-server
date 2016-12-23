/*
 * RESPHEAD.H
 * ==========
 * 
 * Interface for HTTP reponse header functions.
 * 
 * File:   resphead.h
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:35 AM
 */

#ifndef AV_RESPHEAD_H
#define AV_RESPHEAD_H

#ifdef __cplusplus
extern "C" {
#endif

/*  For struct to be defined  */
#include "reqhead.h"
/*  Function prototypes  */
int OutputHTTPHeaders(int conn, struct ReqInfo *reqInfo);

#ifdef __cplusplus
}
#endif

#endif /* AV_RESPHEAD_H */

