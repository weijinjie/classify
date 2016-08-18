#include <Windows.h>

#include "init.h"
#include "utils.h"
#include "file.h"
#include "SingleLinkedList.h"
#include "process.h"

/**
*	�ļ�����
*/
int copyFile(char *src, char *dst)//Ч�ʵ͡����Ըĳɶ��߳�
	{
		FILE *fp1, *fp2;
		int c; 
		errno_t err = fopen_s(&fp1,src, "rb");
		err = fopen_s(&fp2, dst, "wb");//���ļ�
		if (fp1 == NULL || fp2 == NULL)//������
		{
			printf("open file failed\n");
			if (fp1) fclose(fp1);
			if (fp2) fclose(fp2);
		}

		while ((c = fgetc(fp1)) != EOF)//���ֽ�
			fputc(c, fp2); //д����
		fclose(fp1);//�ر��ļ�
		fclose(fp2);

		return 0;
	}

/**
* �����ļ��У�����ļ��в����ھʹ���������������
*/
int createDir(const char* destPath, const char* dirName) {

	char newDir[4096] = { 0 };
	sprintf_s(newDir, 4096, "%s/%s", destPath, dirName);//ƴ��Ŀ¼	// E://tmp//.txt//
	int status;

	//printf("%s\n", newDir);

	if ((_access((const char*)newDir, 0)) == -1)	//�ж�Ŀ¼�Ƿ����
	{
		// Ŀ¼�����ڴ���
		
		char* szStr = newDir;	//��newDirת���ɿ��ַ�����WCHAR
		WCHAR wszClassName[4096];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));

		//#include <Windows.h>
		//wszClassName = E://tmp//.txt//
		status = CreateDirectory(wszClassName, NULL); //�����ļ��У�E://tmp//.txt//
		
		if (!status)
			return -1;
	}

	return status;
}

/**
*	�ļ�����
*/
int classifyFile(const char* destPath, SingleLinkedList* fileList) {//���̸߳���

	//���������ж�Ŀ��Ŀ¼�Ƿ����
	FileListNode* info = NULL;
	
	char*  classifyName = NULL;
	char newPath[4096] = { 0 };
	int ret = 0;
	int currListPos = 0;
	int listLen = singleLinkedList_Length(fileList);
	double currentBarPos = 0;
	int barLen = 50;

	singleLinkedList_Rewind(fileList);	//��ʼ�������α�
	//��������list
	while ((info = (FileListNode *)singleLinkedList_GetNext(fileList)) != NULL)
	{
		int id = info->id;
		char* fileName = info->fileName;
		char* filePath = info->filePath;
		short type = info->fileType;

		if (type == -1) {
			classifyName = "others";
		}else{
			//printf("%d\n", info->fileType);
			classifyName = searchFileType[type];
		}		
		sprintf_s(newPath, 4096, "%s/%s/%s", (char*)destPath, classifyName, fileName);

		//filePath��E:\Workspace\123\123.txt
		//newPath�� E:\tmp\.txt\123.txt

		//destPath: E:\tmp 
		//classifyName: .txt
		ret = createDir(destPath, classifyName);	//�ж�Ŀ��·���Ƿ����,���ڲ������������ھʹ���
		if (ret == -1) {
			printf("�����ļ���ʧ��\n");
			return ret;
		}

		//�����ļ�
		ret = copyFile(filePath, newPath);	//�����ļ�

		updateProcessBar(currListPos, listLen, barLen);
	
		currListPos++;

	}

	printf("\n������ļ�������%d\n", listLen);
	printf("�������...\n");

	return ret;
}