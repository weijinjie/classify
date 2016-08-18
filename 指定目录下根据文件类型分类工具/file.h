#include "SingleLinkedList.h"
#include "config.h"
#include "utils.h"

#ifndef _WJJ_FILE_HEAD
#define _WJJ_FILE_HEAD

/**
  *	�ļ�����
  */
int copyFile(const char* srcPath, const char* destPath);

/**
  * �����ļ��У�����ļ��в����ھʹ���������������
  */
int createDir(const char* destPath, const char* dirName);

/**
  *	�ļ�����
  */
int classifyFile(const char* destPath, SingleLinkedList* fileInfoList);


#endif	//!_WJJ_FILE_HEAD