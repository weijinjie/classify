#include "SingleLinkedList.h"
#include "config.h"
#include "utils.h"

#ifndef _WJJ_FILE_HEAD
#define _WJJ_FILE_HEAD

/**
  *	文件拷贝
  */
int copyFile(const char* srcPath, const char* destPath);

/**
  * 创建文件夹，如果文件夹不存在就创建，否则不做处理
  */
int createDir(const char* destPath, const char* dirName);

/**
  *	文件分类
  */
int classifyFile(const char* destPath, SingleLinkedList* fileInfoList);


#endif	//!_WJJ_FILE_HEAD