#include <Windows.h>

#include "init.h"
#include "utils.h"
#include "file.h"
#include "SingleLinkedList.h"
#include "process.h"

/**
*	文件拷贝
*/
int copyFile(char *src, char *dst)//效率低。可以改成多线程
	{
		FILE *fp1, *fp2;
		int c; 
		errno_t err = fopen_s(&fp1,src, "rb");
		err = fopen_s(&fp2, dst, "wb");//打开文件
		if (fp1 == NULL || fp2 == NULL)//错误处理
		{
			printf("open file failed\n");
			if (fp1) fclose(fp1);
			if (fp2) fclose(fp2);
		}

		while ((c = fgetc(fp1)) != EOF)//读字节
			fputc(c, fp2); //写数据
		fclose(fp1);//关闭文件
		fclose(fp2);

		return 0;
	}

/**
* 创建文件夹，如果文件夹不存在就创建，否则不做处理
*/
int createDir(const char* destPath, const char* dirName) {

	char newDir[4096] = { 0 };
	sprintf_s(newDir, 4096, "%s/%s", destPath, dirName);//拼接目录	// E://tmp//.txt//
	int status;

	//printf("%s\n", newDir);

	if ((_access((const char*)newDir, 0)) == -1)	//判断目录是否存在
	{
		// 目录不存在创建
		
		char* szStr = newDir;	//将newDir转换成宽字符类型WCHAR
		WCHAR wszClassName[4096];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));

		//#include <Windows.h>
		//wszClassName = E://tmp//.txt//
		status = CreateDirectory(wszClassName, NULL); //创建文件夹，E://tmp//.txt//
		
		if (!status)
			return -1;
	}

	return status;
}

/**
*	文件分类
*/
int classifyFile(const char* destPath, SingleLinkedList* fileList) {//多线程更改

	//在这里先判断目标目录是否存在
	FileListNode* info = NULL;
	
	char*  classifyName = NULL;
	char newPath[4096] = { 0 };
	int ret = 0;
	int currListPos = 0;
	int listLen = singleLinkedList_Length(fileList);
	double currentBarPos = 0;
	int barLen = 50;

	singleLinkedList_Rewind(fileList);	//初始化链表游标
	//遍历整个list
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

		//filePath：E:\Workspace\123\123.txt
		//newPath： E:\tmp\.txt\123.txt

		//destPath: E:\tmp 
		//classifyName: .txt
		ret = createDir(destPath, classifyName);	//判断目标路径是否存在,存在不做处理，不存在就创建
		if (ret == -1) {
			printf("创建文件夹失败\n");
			return ret;
		}

		//拷贝文件
		ret = copyFile(filePath, newPath);	//拷贝文件

		updateProcessBar(currListPos, listLen, barLen);
	
		currListPos++;

	}

	printf("\n分类的文件总数：%d\n", listLen);
	printf("分类完成...\n");

	return ret;
}