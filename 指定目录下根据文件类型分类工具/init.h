/**
 *	��ʼ���ļ�
 *	��ʼ������
 *
 */
#include <iostream>   
#include <string>   
#include <io.h> 

#include "SingleLinkedList.h"

using namespace std;


#ifndef _WJJ_INIT_HEAD
#define _WJJ_INIT_HEAD

typedef struct _FileListNode{
	int id;
	short fileType;
	char* fileName;
	char* filePath;
}FileListNode;

/*
	���ļ��ṹ��ʽ����������*/
void formatFileToList(string path, SingleLinkedList* list, int layer);

#endif // !_WJJ_INIT_HEAD