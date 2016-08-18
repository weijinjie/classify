#include <iostream>   
#include <string>   
#include <io.h>  

#include "init.h"
#include "file.h"
#include "Destructor .h"

using namespace std;

int main(int argsLen, char* args[], char* env[])
{

	if (argsLen != 3) {
		printf("参数错误: classify srcPath destPath");
		exit(1);
	}

	//printf("srcPath: %s\ndestPath: %s\n", args[1], args[2]);
	//exit(1);

	int ret = 0;

	SingleLinkedList* fileList = singleLinkedList_Create();
	if (fileList == NULL) {
		cout << "链表创建失败!" << endl;
		exit(1);
	}

	//string path("E:\\Workspace");
	formatFileToList(args[1], fileList, 0);	//链表初始化完成

	ret = classifyFile(args[2], fileList);

	//释放节点
	//freeFileInfoList(fileList);
	FreeBack fb = freeBack;
	singleLinkedList_Clear(fileList,fb);

	//释放链表 
	singleLinkedList_Destroy(&fileList);

	return 0;
}