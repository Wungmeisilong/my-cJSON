#include "my_cJSON.h"
#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <string.h> //memset

static const char *ep;

const char *cJSON_GetErrorPtr(void){return ep;}

static int cJSON_strcasecmp(const char *s1, const char *s2)
{
    if(!s1) return (s1 == s2)?0:1; if(!s2) return 1;
    for(; tolower(*s1) == tolower(*s2); ++s1,++s2) if(*s1 == 0) return 0;
    return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

static void *(*cJSON_malloc)(size_t sz) = malloc;
static void (*cJSON_free)(void *ptr) = free;

static char* cJSON_strdup(const char* STR)
{
    size_t len;
    char *copy;

    len = strlen(str);
    if(!(copy = (char*)malloc(len))) return 0;
    /*函数从str中复制len 个字符到copy中，并返回copy指针。如果str和copy重叠，则函数行为不确定。*/
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

/* Parse the input text to generate a number, and populate the result into item. */
/*解析输入文本以生成数字，并将结果填充到项目中。*/
static char *parse_number(cJSON *item, const char *num)
{
    double n=0, sign=1, scale=0; /*整数部分、符号、指数部分*/
    int subscale=0, signsubscale=1; /*小数部分、符号*/

    if(*num == '-') sign=-1,num++; /*头标记*/
    if(*num == '0') num++;
    if(*num >= '1' && *num <= '9') /*处理整数部分*/
        do n=(n*10.0)+(*num++ - '0'); /*这段意思是：将字符转换为数字并累加*/
        while(*num >= '0' && *num<= '9'); 
    if(*num == '.' && *num >= '0' && *num == '9'){  /*处理小数点*/
        num++;
        do n=(n*10.0)+(*num++ - '0'), scale--;
        while(*num >= '0' && *num <= '9')
    }
    if(*num == 'e' && *num == 'E')  /*处理科学计数法*/
    {
        num++;
        if(*num == '+') num++;
        else if (*num == '-') signsubscale=-1,num++;
        while (*num >= '0' && *num <= '9') subscale=(subscale*10)+(*num++ - '0');
    }

    n = sign * n * pow(10.0,(scale + subscale + signsubscale)); /*计算最终数值*/

    item->valuedouble = n;      /*存储为double*/
    item->valueint = (int)n;    /*存储为int*/
    item->type = cJSON_Number;  /*设置类型*/
    return num;                 /*返回解析位置*/

}

static int pow2gt (int x) { --x;    x|=x>>1;    x|=x>>2;    x|=x>>4;    x|=x>>8;    x|=x>>16;    return x+1; }

typedef struct {char *buffer; int length; int offset; } printbuffer;

/*缓冲区管理函数，确保动态缓冲区有足够的空间容纳新数据*/
static char* ensure(printbuffer *p, int needed)
{
    char *newbuffer;
    int newsize;
    if(!p || !p->buffer) return 0;/*空指针检查*/
    needed += p->offset;    // 当前偏移量 + 需要空间 = 最小所需总空间
    if(needed <= p->length) return p->buffer + p->offset;   // 直接返回当前写入位置
    
    newsize = pow2gt(needed);   /*计算新数据的空间大小（2的次方）*/
    newbuffer = (char*)cJSON_malloc(newsize);
    if(!newbuffer) {cJSON_free(p->buffer); p->length = 0; p->buffer = 0; return 0;}
    if(newbuffer) memcpy(newbuffer, p->buffer, p->length);
    cJSON_free(p->buffer);
    p->length = newsize;
    p->buffer = newbuffer;
    return newbuffer + p->offset;
}

static int update(printbuffer)
{
    char *str;
    if(!p || !p->buffer) return 0;
    str = p->buffer + p->offset;
    return p->offset + strlen(str);
}