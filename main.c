#include"linklist.h"
#include"tcp.h"
#include"http.h"

void *inuse_to_send(db_ldata_pt pdata);

/*****************************************************************************
*   Prototype    : main
*   Description  : main
*   Input        : int argc
*                  char * argv[]
*   Output       : None
*   Return Value : int
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
int main( int argc, char * argv[] )
{
    db_list_pt list_head=db_list_create();
    init_http(list_head);
    init_tcp(list_head);
    __db_list_travel(list_head,inuse_to_send);
}


void *inuse_to_send(db_ldata_pt pdata)

{
    int ret=0 ; 
    if(pdata->flag==INUSE)
    {
       pdata->Init(pdata);
       ret=pdata->SendFunction(pdata,"hello world");
       printf("Inuse type: %d send success",pdata->id);
    }
    return 0;
}


