#include "Destructor .h"

int freeFileInfoList(SingleLinkedList* list)
{

	if (list == NULL)
		return -1;

	//±éÀúÕû¸ölist
	FileListNode* info = NULL;
	while ((info = (FileListNode *)singleLinkedList_GetNext(list)) != NULL)
	{
		if (info != NULL) {

			if (info->fileName != NULL)
				free(info->fileName);
			if (info->filePath != NULL)
				free(info->filePath);

			free(info);
		}
	}


}

void freeBack(SingleLinkListNode* Sinfo) {

	if (Sinfo == NULL)
		return;

	FileListNode* info = (FileListNode*)Sinfo;

	if (info != NULL) {

		if (info->fileName != NULL)
			free(info->fileName);
		if (info->filePath != NULL)
			free(info->filePath);

		free(info);
	}
}