/**
 * ===========================================================
 *
 * 版权 : 魏金杰 版权所有(c)2016
 *
 * 作者 : 魏金杰
 *
 * 版本 : 1.0
 *
 * 描述 : 链式存储线性表---单向链表
 *		  使用此线性表需要将链表节点包含到具体的结构体对象中
 *		  支持编译成64位程序
 *		  注意不能添加地址相同的元素(会导致链表混乱)
 *
 *
 * 修订历史 :
 *
 *
 * ===========================================================
 **/

#ifndef _FENG_SINGLE_LINKED_LIST_
#define _FENG_SINGLE_LINKED_LIST_

	#ifdef __cplusplus
	extern "C" {
	#endif // __cplusplus

		/************************************/
		typedef void SingleLinkedList;
		typedef struct _SingleLinkListNode
		{
			struct _SingleLinkListNode* next;
		}SingleLinkListNode;
		typedef void(*FreeBack)(SingleLinkListNode* Snode);
		/************************************/

		/*
			创建并且返回一个单向链表的头*/
		SingleLinkedList* singleLinkedList_Create();

		/*
			销毁一个单向链表*/
		void singleLinkedList_Destroy(SingleLinkedList** list);

		/*
			将一个单向链表list中的所有元素清空, 单向链表首地址会被置空(元素的内存不会释放)，长度为归0
			fb就是回掉函数的指针*/
		void singleLinkedList_Clear(SingleLinkedList* list, FreeBack fb);

		/*
			返回一个单向链表list中的所有元素个数
			返回值小于0标明异常*/
		int singleLinkedList_Length(SingleLinkedList* list);

		/*
			向链表尾部添加一个节点(此添加方法要比SingleLinkedList_Insert快的多)*/
		int singleLinkedList_AddBack(SingleLinkedList* list, SingleLinkListNode* node);

		/*
			向一个单向链表list的pos位置处插入新元素node
			不能在孤岛位置插入,成功返回0，失败返回错误码*/
		int singleLinkedList_Insert(SingleLinkedList* list, SingleLinkListNode* node, int pos);

		/*
			获取一个单向链表list的pos位置处的元素
			失败返回NULL*/
		SingleLinkListNode* singleLinkedList_Get(SingleLinkedList* list, int pos);

		/*
			获取一个单向链表list的下一个元素，从0开始
			失败或获取完毕,返回NULL*/
		SingleLinkListNode* singleLinkedList_GetNext(SingleLinkedList* list);

		/*
			将游标移动到0位置，SingleLinkedList_GetNext又会从0开始
			失败返回NULL*/
		int singleLinkedList_Rewind(SingleLinkedList* list);

		/*
			删除一个单向链表list的pos位置处的元素  注意：如果返回值为NULL可能是失败也可能是删除了最后一个节点*/
		SingleLinkListNode* singleLinkedList_Delete(SingleLinkedList* list, int pos);

	#ifdef __cplusplus	
		}
	#endif // __cplusplus

#endif // !_FENG_SINGLE_LINKED_LIST_
