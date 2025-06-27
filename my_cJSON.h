#ifndef MY_CJSON_H
#define MY_CJSON_H

#ifdef __cplusplus
extern "C"
{
#endif

/*cJSON Types: */
#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

#include <stddef.h> // for size_t

/*cJSON结构体*/
typedef struct cJSON
{
    struct cJSON *next,*prev;//next/prev是链表指针
    struct cJSON *child;//child是子节点指针
    int type; //类型

    char *valuestring; //字符串值
    int valueint; //整数值
    double valuedouble; //浮点值

    char *string; //字符串名称
} cJSON;

typedef struct cJSON_Hooks //内存分配钩子
{
    void *(*malloc_fn)(size_t sz); //这是一个函数指针，malloc_fn指向一个函数，该函数接受一个size_t类型的参数并返回一个void指针
                                    //该函数用于分配内存，通常是malloc或类似的函数,如果没有提供自定义的分配函数，则使用默认的malloc函数
    void (*free_fn)(void *ptr); //释放函数
} cJSON_Hooks;

/* Supply malloc, realloc and free functions to cJSON */
/*通过cJSON_InitHooks函数来设置内存分配钩子*/
extern void cJSON_InitHooks(cJSON_Hooks* hooks);

/* Supply a block of JSON, and this returns a cJSON object you can interrogate. Call cJSON_Delete when finished. */
/*提供一个JSON字符串，返回一个cJSON对象，可以对其进行查询。完成后调用cJSON_Delete释放内存*/
extern cJSON *cJSON_Parse(const char *value);
/* Render a cJSON entity to text for transfer/storage. Free the char* when finished. */
/*将cJSON对象渲染为文本格式以进行传输或存储。完成后释放返回的char*内存*/
extern char *cJSON_Print(cJSON *item);
/* Render a cJSON entity to text for transfer/storage without any formatting. Free the char* when finished. */
/*将cJSON对象渲染为未格式化的文本格式以进行传输或存储。完成后释放返回的char*内存*/
extern char *PrintUnformatted(cJSON *item);
/* Render a cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
/*使用缓冲策略将cJSON对象渲染为文本格式。prebuffer是对最终大小的猜测，猜测得好可以减少重新分配。fmt=0表示未格式化，=1表示格式化*/
extern char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt);
#ifdef __cplusplus
}
#endif


#endif
