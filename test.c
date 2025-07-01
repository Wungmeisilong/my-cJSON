#include <stdio.h>
#include "my_cJSON.h"

int main()
{
    /*内存管理测试用例*/
    cJSON *item = cJSON_New_Item();
    if (item) {
        printf("cJSON_New_Item() 分配成功\n");
    } else {
        printf("cJSON_New_Item() 分配失败\n");
    }

    cJSON_Delete(item);
    printf("cJSON_Delete() 释放成功\n");
    return 0;
}