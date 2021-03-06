#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkedList.h"


typedef struct _SingleLinkedListInfo{//链表信息	
	int listLength;	//链表的长度 
	SingleLinkedList* list;	//链表的首地址
	SingleLinkListNode* cursor;	//游标
	SingleLinkListNode* last;//链表最后一个元素的地址
}SingleLinkedListInfo;

/******************************************************************************************************/

SingleLinkedList* singleLinkedList_Create()
{
	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)malloc(sizeof(SingleLinkedListInfo));
	if (ulli == NULL) return NULL;

	ulli->listLength = 0;
	ulli->list = NULL;

	return ulli;
}

/******************************************************************************************************/

void singleLinkedList_Destroy(SingleLinkedList** list)
{
	if (list == NULL) return;

	if (*list != NULL) {
		free(*list);
		*list = NULL;
	}
}

void singleLinkedList_Clear(SingleLinkedList* list, FreeBack fb)
{
	if (list == NULL) return;

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;

	//遍历链表
	SingleLinkListNode* info = NULL;
	while ((info = (SingleLinkListNode *)singleLinkedList_GetNext(list)) != NULL)
	{
		fb(info);
	}

	ulli->listLength = 0;
	ulli->list = NULL;	
	ulli->last = NULL;
	ulli->cursor = NULL;
}

/******************************************************************************************************/

int singleLinkedList_Length(SingleLinkedList* list)
{
	if (list == NULL) return -1;	//非法参数

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	return ulli->listLength;
}

/******************************************************************************************************/

int singleLinkedList_AddBack(SingleLinkedList* list, SingleLinkListNode* node) {

	if (list == NULL || node == NULL) return -1;

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	//SingleLinkListNode *ulln = (SingleLinkListNode *)(ulli->list);

	if (ulli->listLength == 0) {
		node->next = NULL;
		ulli->list = node;
		ulli->cursor = node;//游标初始化
		ulli->last = node;
		(ulli->listLength)++;
		return 0;
	}

	node->next = NULL;
	ulli->last->next = node;
	ulli->last = node;
	(ulli->listLength)++;

	return 0;
}

/******************************************************************************************************/

int singleLinkedList_Insert(SingleLinkedList* list, SingleLinkListNode* node, int pos)
{
	if (list == NULL || node == NULL || pos < 0) return -1;

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	if (pos > ulli->listLength) return -2;	//不能在孤岛位置插入

	//完成插入//
	SingleLinkListNode *ulln = (SingleLinkListNode *)(ulli->list);
	
	if (pos == 0) {	//头节点的情况
		node->next = ulln;
		ulli->list = node;
		ulli->cursor = node;//游标初始化
		ulli->last = node;
		ulli->listLength++;
		return 0;
	}

	SingleLinkListNode *preP = ulln;	//两个辅助指针，一前一后挖链表
	SingleLinkListNode *currP = ulln->next;
	int currPos = 1;
	while (preP != NULL) {

		//if (preP == node || currP == node) {
		//	return -3;	//插入的元素地址与原始的元素地址相同，说明是用户的错误操作！！！
		//}

		if (currPos == pos) {	//找到位置
			//开始交换
			preP->next = node;
			if (currPos == ulli->listLength) {
				node->next = NULL;		//说明插到了最后一个节点后面 
				ulli->last = node;
			}
			else {
				node->next = currP;
			}

			ulli->listLength++;	//链表长度增加
			break;
		}

		preP = currP;
		currP = currP->next;	//移动两个辅助指针
		currPos++;
	}

	return 0;
}

/******************************************************************************************************/

SingleLinkListNode* singleLinkedList_Get(SingleLinkedList* list, int pos)
{
	if (list == NULL || pos < 0) return NULL;	//非法参数

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	if (pos >= ulli->listLength) return NULL;
	SingleLinkListNode *ulln = (SingleLinkListNode *)(ulli->list);

	SingleLinkListNode *currP = ulln;
	int currPos = 0;
	for (int i = 0;i < pos;i++) {
		currP = currP->next;
		currPos++;
	}
	
	return currP;
}

/******************************************************************************************************/

SingleLinkListNode* singleLinkedList_GetNext(SingleLinkedList* list) {

	if (list == NULL) return NULL;	//非法参数

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	SingleLinkListNode *ulln = (SingleLinkListNode *)(ulli->cursor);

	if (ulli->cursor == NULL) return NULL;
	ulli->cursor = ulli->cursor->next;

	return ulln;
}

/******************************************************************************************************/

int singleLinkedList_Rewind(SingleLinkedList* list) {

	if (list == NULL) return -1;	//非法参数

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;

	ulli->cursor = (SingleLinkListNode *)(ulli->list);
	return 0;
}

/******************************************************************************************************/

SingleLinkListNode* singleLinkedList_Delete(SingleLinkedList* list, int pos)
{
	if (list == NULL || pos < 0) return NULL;	//非法参数

	SingleLinkedListInfo *ulli = (SingleLinkedListInfo *)list;
	if (pos >= ulli->listLength) return NULL;
	SingleLinkListNode *ulln = (SingleLinkListNode *)(ulli->list);

	SingleLinkListNode *preP = ulln;
	SingleLinkListNode *currP = ulln->next;
	SingleLinkListNode *nextP = ulln->next->next;	//三个辅助指针挖链表

	if (pos == 0) {	//删除头节点
		ulli->list = preP->next;
		ulli->listLength--;	//减少长度
		return (SingleLinkListNode *)ulli->list;
	}

	int currPos = 1;
	while (currP != NULL) {

		if (currPos == pos) {	//找到了删除点
			if (currPos == ulli->listLength - 1) {
				preP->next = NULL;	//删除的是最后一个节点
				ulli->last = preP;
			}
			else {
				preP->next = nextP;
				currP = NULL;
			}

			ulli->listLength--;	//减少长度
			break;
		}
		
		preP = currP;
		currP = nextP;
		if (nextP == NULL) return NULL;	//保险措施
		nextP = nextP->next;
		currPos++;
	}

	return nextP;
}