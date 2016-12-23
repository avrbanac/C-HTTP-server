/*
 * RESOURCE.H
 * ==========
 *
 * Interface to functions for returning a resource / starting an action.
 * 
 * File:   resource.h
 * Author: avrbanac
 *
 * Created on March 14, 2016, 10:39 AM
 */

#ifndef AV_RESOURCE_H
#define AV_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

/*  Needed for struct ReqInfo  */
#include "reqhead.h"

/*  Function prototypes  */
int ReturnResource (int conn, int resource, struct ReqInfo *reqInfo);
int CheckResource (struct ReqInfo *reqInfo, int *isAction, char *args);
int ReturnErrorMsg (int conn, struct ReqInfo *reqInfo);
int ReturnActionMsg (int mode, int conn, char *command);

#ifdef __cplusplus
}
#endif

#endif /* AV_RESOURCE_H */

