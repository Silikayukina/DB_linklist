/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : http.c
*  Version       : Initial Draft
*  Author        : mi
*  Created       : 2020/4/28
*  Last Modified :
*  Description   : http send file
*  Function List :
*
*       1.                http_send
*       2.                init_http
*       3.                init_http_node
*       4.                register_http_method
*
*  History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include"http.h"
/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
 
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/

/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/


/*****************************************************************************
*   Prototype    : init_http_node
*   Description  : init http function
*   Input        : db_ldata_pt pdata
*   Output       : None
*   Return Value : static u32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created function
*
*****************************************************************************/
static u32 init_http_node( db_ldata_pt pdata )
{
    if ((pdata->sock_fd = socket(AF_INET,SOCK_STREAM, 0)) < 0 ) 
    {
        printf("socket create error!\n");
        exit(0);
    }
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(HTTP_PORT);
    if (inet_pton(AF_INET, HTTP_SERVER, &servaddr.sin_addr) <= 0 )
    {
        printf("net_pton error!\n");
        exit(0);
    }
    if (connect(pdata->sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error!\n");
        exit(0);
    }
    return 0;
}


/*****************************************************************************
*   Prototype    : http_send
*   Description  : send http data
*   Input        : db_ldata_pt pdata
*                  void * sendbuffer
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created function
*
*****************************************************************************/
static int http_send( db_ldata_pt pdata, void * sendbuffer )
{
    u8 *length=(u8  *)malloc(128);
    int len = strlen(sendbuffer);
    sprintf(length, "%d", len);
    u8 * http_data = (u8*)malloc(len+1024);
    memset(http_data, 0, len+1024);
    strcat(http_data, "POST /webservices/qqOnlineWebService.asmx/qqCheckOnline HTTP/1.1\r\n");
    strcat(http_data, "Host: www.webxml.com.cn\r\n");
    strcat(http_data, "Content-Type: application/x-www-form-urlencoded\r\n");
    strcat(http_data, "Content-Length: ");
    strcat(http_data, length);
    strcat(http_data, "\r\n");
    strcat(http_data, sendbuffer);
    strcat(http_data, "\r\n\r\n");
    printf("%s\n",http_data);  

    int ret = write(pdata->sock_fd,http_data,strlen(http_data));
    if(ret<0)
    {
        printf("send error:%d result:%s'\n",errno, strerror(errno));
        exit(0);
    }
    else
    {
        printf("send success,send length :%d \n",ret);
    }
    free(length);
    free(http_data);
    length = NULL;
    http_data = NULL;
    return ret;
}

static db_ldata_t http_node={
    .id =HTTP,
    .flag=INUSE,
    .Init=init_http_node,
    .SendFunction=http_send,
};


/*****************************************************************************
*   Prototype    : register_http_method
*   Description  : register http send node
*   Input        : db_list_pt plist
*                  void * pdata
*   Output       : None
*   Return Value : static void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created function
*
*****************************************************************************/
static void register_http_method( db_list_pt plist, void * pdata )
{
    if(plist==NULL || pdata==NULL)
    {
        errno=EINVAL;
        return;
    }
    __db_list_insert_before(&plist,0,pdata);
}


/*****************************************************************************
*   Prototype    : init_http
*   Description  : init http send function
*   Input        : db_list_pt plist
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/4/28
*           Author       : mi
*           Modification : Created function
*
*****************************************************************************/
void init_http( db_list_pt plist )
{
    register_http_method( plist, (void *)&http_node);
}
