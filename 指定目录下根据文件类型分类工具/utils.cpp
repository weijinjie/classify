#include <string.h>

#include "config.h"
#include "utils.h"

/**
*	strEndWith�ж��ַ����Ƿ���ĳ���ַ�����β
*	�Ƿ���1���񷵻�0
*/
int strEndWith(const char* strSrc, const char* endStr)
{
	int strSrc_len = strlen(strSrc);
	int endStr_len = strlen(endStr);

	/*	printf("Content-Type: text/html\n\n");
	printf("strSrc_len = %d\n", strSrc_len);
	printf("endStr_len = %d\n", endStr_len);
	*/
	if (memcmp((char*)(strSrc + strSrc_len - endStr_len), endStr, endStr_len) == 0) {

		return 1;
	}

	return 0;
}

/**
* ��ȡ�ļ�����
**/
short get_file_type(const char *fileName)
{
	int i = 0;

	for (i = 0; i < sFTCount; i++) {

		if (strEndWith(fileName, searchFileType[i]) == 1) {
			return i;
		}
	}

	if (i = sFTCount - 1)
		return -1;
	else 
		return -1;
}