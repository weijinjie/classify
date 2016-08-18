#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "SingleLinkedList.h"

#ifndef _WJJ_DESTRUCTOR_HEAD
#define _WJJ_DESTRUCTOR_HEAD


/*释放节点*/
int freeFileInfoList(SingleLinkedList* list);

/*释放的回调函数*/
void freeBack(SingleLinkListNode* list);

#endif // !_WJJ_DESTRUCTOR_HEAD