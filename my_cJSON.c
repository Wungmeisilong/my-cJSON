#include "my_cJSON.h"
#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <string.h> //memset

static const char *ep;

const char *cJSON_GetErrorPtr(void) {return ep;};

static char cJSON_strcasecmp(const char *s1,const char *s2)
{
    if(!s1) return (s1==s2)?0:1; if(!s2) return 1;
    for(; tolower(*s1) == tolobwer(*s2); ++s1,++s2) if(*s1 == 0) return 0;
    return tolower(*(const unsigned char *)s1) -tolower(*(const unsigned char *)s2);
}

static void *(*cJSON_malloc)(size_t sz) = malloc;
static void (*cJSON_free)(void *ptr) = free;

static char *cJSON_strdup(const char* str)
{
    size_t len;
    char* copy;

    len = strlen(str) + 1;
    if(!(copy = (char*)malloc(len))) return 0;
    memcpy(copy,str,len);
    return copy;
}

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
        next = c->next;
        if
    }
}
/* Parser core - when encountering text, process appropriately. */
static const char *parse_value(cJSON *item,const char *value)
{

}


/* Parse an object - create a new root, and populate. */
/*解析一个对象 - 创建一个新的根，并填充。*/
cJSON *cJSON_parseWithOpts(const char *value,const char **return_parse_end, int require_unll_treminated)
{
    const char *end = 0;
    cJSON *c = cJSON_New_Item();
    eq = 0;
    if(!c) return 0;
    end = parse_value(c,skip(value))
}

cJSON *cJSON_print(const char *value){ return cJSON_parseWithOpts(value,0,0); }
