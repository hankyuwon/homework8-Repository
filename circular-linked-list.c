#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // Node 구조체
	int key;
	struct Node* llink; // left 에 있는 node의 주소 저장하는 포인터
	struct Node* rlink; // right 에 있는 node의 주소 저장하는 포인터
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL; // headnode라는 listNode 구조체 포인터 생성 및 NULL 가리킴

	printf("----------[hankyuone]-----------[2019037002]------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { // 처음 실행할 때 listNode 메모리 동적 할당

	if(*h != NULL) 
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode)); // listNode의 첫 부분을 가리키는 h 메모리 할당
	(*h)->rlink = *h; // 초기값들로 의미 없음
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){ // list 메모리 해제

	if(h->rlink == h) // h의 rlink가 가리키는 값이 h 이면 메모리 해제
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink; // listNode의 첫 부분을 p로 불러옴

	listNode* prev = NULL; // 메모리 해제와 node 이동을 위해 prev라는 구조체 포인터 생성
	while(p != NULL && p != h) { // p 가 NULL을 가리키거나 처음부분으로 돌아오기 전까지
		prev = p; // prev에 p를 넣고
		p = p->rlink; // p는 다음 node로 이동
		free(prev); // prev 메모리 해제
	}
	free(h); // h 메모리 해제
	return 0;
}



void printList(listNode* h) { // listNode 출력
	int i = 0;
	listNode* p; // listNode의 첫 부분 찾기 위해 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // listNode가 비어있을 시
		printf("Nothing to print....\n"); // Nothing to print 출력
		return;
	}

	p = h->rlink; // p는 listNode의 첫 부분

	while(p != NULL && p != h) { // listNode의 node를 하나씩 증가시킬때 node가 NULL을 가리키거나 처음으로 돌아오면 반복문 탈출
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // 다음 node로 이동
		i++;
	}
	printf("  items = %d\n", i);

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // head node의 llink, head, rlink 주소 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // listNode 의 각 node들의 llink, node, rlink 주소 출력
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) { // listNode의 마지막에 node 삽입

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 메모리 동적 할당
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) // listNode 가 비어있는 경우
	{
		h->rlink = node; // h의 오른쪽과 왼쪽은 node가 됨
		h->llink = node;
		node->rlink = h; // node의 오른쪽과 왼쪽도 h가 됨
		node->llink = h;
	} else { // listNode 가 비어있지 않은 경우
		h->llink->rlink = node; // h->llink 는 함수 실행 이전 listNode의 맨 마지막 node. 이 node의 rlink가 새로 삽입되는 node가 됨
		node->llink = h->llink; // node의 llink는 (h->llink= 함수 실행 이전 listNode의 마지막 node)가 된다.
		h->llink = node; // h의 llink는 이제 listNode의 새로운 마지막 node인 node가 된다.
		node->rlink = h; // node의 rlink는 처음으로 돌아가 h가 된다.
	}

	return 1;
}

int deleteLast(listNode* h) { // listNode의 마지막 node 삭제

	if (h->llink == h || h == NULL) // listNode 가 비어있을 때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; // listNode의 마지막 node를 nodetoremove로 선언

	nodetoremove->llink->rlink = h; // nodetoremove 의 전 node의 rlink를 h로 바꿈 (마지막에서 두번째를 h와 연결)
	h->llink = nodetoremove->llink; // h의 llink를 nodetoremove의 llink로 바꿈 (마지막에서 두번째를 h와 연결 동일)

	free(nodetoremove); // 메모리 해제

	return 1;
}

int insertFirst(listNode* h, int key) { // listNode의 첫 부분에 node 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 구조제 포인터 메모리 할당
	node->key = key; // 입력값을 node구조체의 key에 넣어줌
	node->rlink = NULL;
	node->llink = NULL;

	// 기존 listNode의 h와 첫번째 node 사이에 insertFirst함수를 통해 입력되는 node를 끼워주는 작업
	node->rlink = h->rlink; // node->rlink 는 기존의 listNode의 첫 node(h->rlink)
	h->rlink->llink = node; // (h->rlink) 기존 listNode의 첫 node의 llink 는 node
	node->llink = h; // node->llink 는 h
	h->rlink = node; // h->rlink는 node


	return 1;
}

int deleteFirst(listNode* h) { // listNode의 첫 부분에 있는 node 삭제

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; // listNode의 첫 부분 nodetoremove로 선언

	nodetoremove->rlink->llink = h; // (nodetoremove->rlink) listNode의 두번째 node -> llink 는 h
	h->rlink = nodetoremove->rlink; // h->rlink 는 nodetoremove->rlink

	free(nodetoremove); // nodetoremove 메모리 해제

	return 1;

}

int invertList(listNode* h) { // listNode 역순으로 재배치


	if(h->rlink == h || h == NULL) { // listNode가 비어있을 시
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; // listNode의 첫부분을 n, 역순으로 재배치 하기 위해 trail과 middle 구조체 포인터 선언
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink; // h->llink를 h->rlink로 재배치

	while(n != NULL && n != h){ // listNode를 역순으로 재배치
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}


int insertNode(listNode* h, int key) { // listNode에 입력된 key값보다 큰값 바로 앞에 삽입

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 구조체 포인터 생성, 메모리 동적 할당
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h) // listNode가 비어있을 시
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink; // listNode의 첫 노드를 n으로 선언

	while(n != NULL && n != h) { // n이 NULL이거나 h가 아닐때, 즉 처음으로 돌아오기 전까지 반복
		if(n->key >= key) { // 입력된 key값이랑 listNode안의 node 내의 key값 비교
			if(n == h->rlink) { // 입력된 key 값이 더 작을때, n이 listNode의 첫번째 node 일때
				insertFirst(h, key); // insertFirst 함수로 바로 삽입
			} else { // n이 listNode의 첫 node가 아닐 때
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink; // listNode의 다음 node로 이동해가면서 비교
	}

	insertLast(h, key); // 모든 key의 비교가 끝났음에도 불구하고 입력된 key값이 더 클 때 insertLast함수를 통해 마지막에 삽입
	return 0;
}

int deleteNode(listNode* h, int key) { // listNode 내에 입력된 key값을 찾고 삭제

	if (h->rlink == h || h == NULL) // listNode가 비어있을 시
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; // listNode의 첫 node를 n으로 선언

	while(n != NULL && n != h) { // listNode의 마지막 부분까지 증가
		if(n->key == key) { // 입력된 key값이 n의 key값일 때
			if(n == h->rlink) { // n이 listNode의 첫 node일 때
				deleteFirst(h); // deleteFirst함수를 이용하여 삭제
			} else if (n->rlink == h){ // n이 listNode의 마지막 node일 때
				deleteLast(h); // deleteLast함수를 이용하여 삭제
			} else {
				n->llink->rlink = n->rlink; // n의 왼쪽 node의 rlink는 n의 rlink
				n->rlink->llink = n->llink; // n의 오른쪽 node의 llink는 n의 llink
				free(n); // 메모리 해제
			}
			return 0;
		}

		n = n->rlink; // 다음 node로 이동하면서 찾음
	}

	printf("cannot find the node for key = %d\n", key); // 모든 node를 돌아봤지만 찾지 못하였을때 출력
	return 0;
}