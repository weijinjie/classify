#pragma warning(disable : 4996)

#include <iostream>   
#include <string>   
#include <io.h> 

#include "utils.h"
#include "init.h"
#include "SingleLinkedList.h"


using namespace std;

/*
	���ļ��ṹ��ʽ����������*/
void formatFileToList(string path, SingleLinkedList* list, int layer)//����������Ըĳɶ��̵߳�
{
	struct _finddata_t filefind;
	string curr = path + "\\*.*";// �޸Ĵ˴��ı���������  
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
			if ((_A_SUBDIR == filefind.attrib))              // ��Ŀ¼  
			{
				//printf("[Dir]:\t%s\n", filefind.name);
				curr = path + "\\" + filefind.name;
				formatFileToList(curr, list, layer + 1);                  // �ݹ������Ŀ¼  
			}
			else
			{
				//printf("[File]:\t%s\n", filefind.name);
				//����һ���ڵ�,�����ڴ�
				FileListNode* info = (FileListNode*)malloc(sizeof(FileListNode));
				info->fileName = (char*)calloc(4096, 1);
				info->filePath = (char*)calloc(4096, 1);

				info->id = singleLinkedList_Length(list);	//���id

				buffer = filefind.name;		//��ֵ�ļ���
				len = buffer.length();
				buffer.copy(info->fileName, len, 0);
				*(info->fileName + len) = '\0';

				buffer =  path + "/" + filefind.name;//��ֵ�ļ�·��
				//cout << buffer << endl;
				len = buffer.length();
				buffer.copy(info->filePath, len, 0);
				*(info->filePath + len) = '\0';

				info->fileType = get_file_type(info->fileName);//��ֵ�ļ�����
				
				if (info->fileType == -1)	//���Լ��ٸ��ƴ���
					continue;

				//���ڵ���ӵ�������
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



