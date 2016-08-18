#include <stdio.h>
#include <stdlib.h>


#ifndef _FF_UTILS_HEAD
#define _FF_UTILS_HEAD


/**
*	strEndWith判断字符串是否以某个字符串结尾
*	是返回1，否返回0
*/
int strEndWith(const char* strSrc, const char* endStr);

/**
* 获取文件类型
**/
short get_file_type(const char *fileName);



#endif //!_FF_UTILS_HEAD
