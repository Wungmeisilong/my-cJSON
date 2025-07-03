# my-cJSON

实现顺序建议

- 先写结构体和基础内存管理（如 cJSON、cJSON_Hooks、cJSON_InitHooks、cJSON_New_Item、cJSON_Delete）。
- 再写字符串处理、数字解析等基础工具函数（如 cJSON_strdup、cJSON_strcasecmp、parse_number）。
- 然后实现 JSON 解析相关（parse_value、parse_object、parse_array、parse_string）。
- 最后实现 JSON 生成（print_value、print_object、print_array、print_string）。