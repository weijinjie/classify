#include <stdio.h>
#include <stdlib.h>
#include "process.h"


/**
 *	���½�����
 */
int updateProcessBar(int currentListPos, int listLen,int barLen) {


	int stepNode = listLen / barLen;

	if(currentListPos % stepNode == 0)
	{
		printf("=");
	}

	return 0;
}
