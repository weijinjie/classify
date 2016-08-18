#pragma warning(disable : 4996)

#include <iostream>   
#include <string>   
#include <io.h> 

#include "utils.h"
#include "init.h"
#include "SingleLinkedList.h"


using namespace std;

/*
	将文件结构格式化到链表中*/
void formatFileToList(string path, SingleLinkedList* list, int layer)//这个函数可以改成多线程的
{
	struct _finddata_t filefind;
	string curr = path + "\\*.*";// 修改此处改变搜索条件  
	string buffer;
	int done = 0, handle, ret = 0;
	int len = 0;
	if ((handle = _findfirst(curr.c_str(), &filefind)) != -1)
	{
		while (!(done = _findnext(handle, &filefind)))
		{
			if (strcmp(filefind.name, "..") == 0)
				continue;
			//for (i = 0; i <layer; i++)
				//printf("\t");
			if ((_A_SUBDIR == filefind.attrib))              // 是目录  
			{
				//printf("[Dir]:\t%s\n", filefind.name);
				curr = path + "\\" + filefind.name;
				formatFileToList(curr, list, layer + 1);                  // 递归遍历子目录  
			}
			else
			{
				//printf("[File]:\t%s\n", filefind.name);
				//创建一个节点,开辟内存
				FileListNode* info = (FileListNode*)malloc(sizeof(FileListNode));
				info->fileName = (char*)calloc(4096, 1);
				info->filePath = (char*)calloc(4096, 1);

				info->id = singleLinkedList_Length(list);	//编号id

				buffer = filefind.name;		//赋值文件名
				len = buffer.length();
				buffer.copy(info->fileName, len, 0);
				*(info->fileName + len) = '\0';

				buffer =  path + "/" + filefind.name;//赋值文件路径
				//cout << buffer << endl;
				len = buffer.length();
				buffer.copy(info->filePath, len, 0);
				*(info->filePath + len) = '\0';

				info->fileType = get_file_type(info->fileName);//赋值文件类型
				
				if (info->fileType == -1)	//可以减少复制次数
					continue;

				//将节点添加到链表中
				ret = singleLinkedList_AddBack(list, (SingleLinkListNode*)info);
				if (ret != 0) {
					printf("error: %s [%d]", __FILE__, __LINE__);
					exit(1);
				}
			}
		}
		_findclose(handle);
	}
}



