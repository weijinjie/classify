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
		printf("��������: classify srcPath destPath");
		exit(1);
	}

	//printf("srcPath: %s\ndestPath: %s\n", args[1], args[2]);
	//exit(1);

	int ret = 0;

	SingleLinkedList* fileList = singleLinkedList_Create();
	if (fileList == NULL) {
		cout << "������ʧ��!" << endl;
		exit(1);
	}

	//string path("E:\\Workspace");
	formatFileToList(args[1], fileList, 0);	//�����ʼ�����

	ret = classifyFile(args[2], fileList);

	//�ͷŽڵ�
	//freeFileInfoList(fileList);
	FreeBack fb = freeBack;
	singleLinkedList_Clear(fileList,fb);

	//�ͷ����� 
	singleLinkedList_Destroy(&fileList);

	return 0;
}