#include "my_cJSON.h"
#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <string.h> //memset

static void *(*cJSON_malloc)(size_t sz) = malloc;
static void (*cJSON_free)(void *ptr) = free;

void cJSON_InitHooks(cJSON_Hooks* hooks)
{
    if(!hooks)
    {
        cJSON_malloc = malloc;
        cJSON_free = free;
        return;
    }

    cJSON_malloc = (hooks->malloc_fn) ? hooks->malloc_fn : malloc;
    cJSON_free = (hooks->free_fn) ? hooks->free_fn : free;
}

/* Internal constructor. */
/*内部构造函数*/
static cJSON *cJSON_New_Item(void){
    /*申请cJSON大小的空间*/
    cJSON* node = (cJSON*)cJSON_malloc(sizeof(cJSON));
    /*memset是将node指向的地址初始化为0，并返回node给指针；
    常用于将一段内存初始化为某个值。*/
    if(node) memset(node,0,sizeof(cJSON));
    return node;
}

/* Delete a cJSON structure. */
void cJSON_Delete(cJSON *c)
{
    cJSON *next;
    while(c)
    {
        next = c->next; //保存下一个节点的指针
        if(!(c->type&cJSON_IsReference) && c->child) cJSON_Delete(c->child);
        if(!(c->type&cJSON_IsReference) && c->valuestring) cJSON_free(c->valuestring);
        if(!(c->type&cJSON_IsReference) && c->string) cJSON_free(c->string);
        cJSON_free(c);
        c = next; //继续遍历下一个节点    
    }
}
