/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : http.h
*  Version       : Initial Draft
*  Author        : mi
*  Created       : 2020/4/28
*  Last Modified :
*  Description   : http.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created file
*
******************************************************************************/
#ifndef __HTTP_H__
#define __HTTP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "linklist.h"
#include <stdlib.h>

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define HTTP_PORT 90
#define HTTP_SERVER "192.168.32.130"

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/

/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

static int http_send( db_ldata_pt pdata, void * sendbuffer );
void init_http( db_list_pt plist );
static u32 init_http_node( db_ldata_pt pdata );
static void register_http_method( db_list_pt plist, void * pdata );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HTTP_H__ */
