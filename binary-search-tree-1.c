#include <stdio.h>
#include <stdlib.h>

typedef struct node { /* struct Node에 타입이 다른 데이터들을 그룹화 */
	int key; /* key를 int형으로 선언 */
	struct node *left; /* 구조체 Node포인터 left를 선언 */ /* 위에서 typedef struct로 선언을 해주지 않았기에 struct를 써줘야함 */
	struct node *right; /* 구조체 Node포인터 right를 선언 */ /* 위에서 typedef struct로 선언을 해주지 않았기에 struct를 써줘야함 */
} Node; /* 구조체 호출용 이름 */

int initializeBST(Node** h); /* binary-search-tree를 초기화하는 함수 선언 */

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; /* command를 char형으로 선언 */
	int key; /* key를 int형으로 선언 */
	Node* head = NULL; /* Node포인터 head를 빈공간으로 지정 */
	Node* ptr = NULL;	/* temp */

	printf("[----- [Choi Suzy]  [2021024135] -----]\n");

	do{
		printf("\n\n"); /* print */
		printf("----------------------------------------------------------------\n"); /* print */
		printf("                   Binary Search Tree #1                        \n"); /* print */
		printf("----------------------------------------------------------------\n"); /* print */
		printf(" Initialize BST       = z                                       \n"); /* print */
		printf(" Insert Node          = n      Delete Leaf Node             = d \n"); /* print */
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n"); /* print */
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n"); /* print */
		printf(" Postorder Traversal  = t      Quit                         = q\n"); /* print */
		printf("----------------------------------------------------------------\n"); /* print */
 
		printf("Command = "); /* print */
		scanf(" %c", &command); /* char형 command를 입력자에게 입력받음 */

		switch(command) { /* command가 ~이면 조건문 */
		case 'z': case 'Z': /* command가 z나 Z면 */
			initializeBST(&head); /* initializeBST 함수 실행 */
			break; /* 조건식을 빠져나옴 */
		case 'q': case 'Q': /* command가 q나 Q이면 */
			freeBST(head); /* freeBST 함수 실행 */
			break; /* 조건식을 빠져나옴 */
		case 'n': case 'N': /* command가 n이나 N이면 */
			printf("Your Key = "); /* print */
			scanf("%d", &key); /* int형 key를 입력자에게 입력받음 */
			insert(head, key); /* insert 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'd': case 'D': /* command가 d나 D이면 */
			printf("Your Key = "); /* print */
			scanf("%d", &key); /* int형 key를 입력자에게 입력받음 */
			deleteLeafNode(head, key); /* deleteLeafNode함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'f': case 'F': /* command가 f나 F면 */
			printf("Your Key = "); /* print */
			scanf("%d", &key); /* int형 key를 입력자에게 입력받음 */
			ptr = searchIterative(head, key); /* searchIterative 함수 호출해서 ptr에 넣음 */
			if(ptr != NULL) /* ptr이 null이 아니라면 */
				printf("\n node [%d] found at %p\n", ptr->key, ptr); /* print */
			else /* ptr이 null이라면 */
				printf("\n Cannot find the node [%d]\n", key); /* print */
			break; /* 조건식을 빠져나옴 */
		case 's': case 'S': /* command가 s나 S면 */
			printf("Your Key = "); /* print */
			scanf("%d", &key); /* int형 key를 입력자에게 입력받음 */
			ptr = searchRecursive(head->left, key); /* searchRecursive 함수 호출해서 ptr에 넣음 */
			if(ptr != NULL) /* ptr이 null이 아니라면 */
				printf("\n node [%d] found at %p\n", ptr->key, ptr); /* print */
			else /* ptr이 null이라면 */
				printf("\n Cannot find the node [%d]\n", key); /* print */
			break; /* 조건식을 빠져나옴 */

		case 'i': case 'I': /* command가 i나 I면 */
			inorderTraversal(head->left); /* inorderTraversal 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'p': case 'P': /* command가 p나 P면 */
			preorderTraversal(head->left); /* preorderTraversal 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 't': case 'T': /* command가 t나 T면 */
			postorderTraversal(head->left); /* postorderTraversal 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		default: /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* print */
			break; /* 조건식을 빠져나옴 */
		}

	}while(command != 'q' && command != 'Q'); /* command가 q가 아니고 Q가 아니라면 do루프 계속 돎 */

	return 1; /* 1을 반환함 */
}

int initializeBST(Node** h) { /* binary-search-tree를 초기화하는 함수 정의 */

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) /* 포인터 headNode가 NULL이 아니면 */
		freeBST(*h); /* 할당된 메모리를 모두 해제시키는 freeBST 함수 호출 */

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); /* Node크기만큼을 동적할당한 Node포인터를 포인터h에 넣음 */
	(*h)->left = NULL;	/* root */ /* 포인터h의 left부분을 빈공간으로 만듦 */
	(*h)->right = *h; /* 포인터h의 right부분에 포인터h를 넣음 */
	(*h)->key = -9999; /* 포인터h의 key부분에 -9999를 넣음 */
	return 1; /* 1를 반환함 */
}

void inorderTraversal(Node* ptr) /* 중위순회하는 함수 정의 */
{
	if(ptr) { /* ptr이 ~라면 */
		inorderTraversal(ptr->left); /* inorderTraversal 함수 호출*/
		printf(" [%d] ", ptr->key); /* print */
		inorderTraversal(ptr->right); /* inorderTraversal 함수 호출*/
	}
}

void preorderTraversal(Node* ptr) /* 전위순회하는 함수 정의 */
{
	if(ptr) { /* ptr이 ~라면 */
		printf(" [%d] ", ptr->key); /* print */
		preorderTraversal(ptr->left); /* preorderTraversal 함수 호출*/
		preorderTraversal(ptr->right); /* preorderTraversal 함수 호출*/
	}
}

void postorderTraversal(Node* ptr) /* 후위순회하는 함수 정의 */
{
	if(ptr) { /* ptr이 ~라면 */
		postorderTraversal(ptr->left); /* postorderTraversal 함수 호출*/
		postorderTraversal(ptr->right); /* postorderTraversal 함수 호출*/
		printf(" [%d] ", ptr->key); /* print */
	}
}


int insert(Node* head, int key) /* 트리에 노드를 삽입하는 함수 정의 */
{
	Node* newNode = (Node*)malloc(sizeof(Node)); /* Node크기만큼을 동적할당한 Node포인터를 Node포인터 newNode에 넣음 */
	newNode->key = key; /* newNode의 key부분에 key값을 넣음 */
	newNode->left = NULL; /* newNode의 left부분을 빈공간으로 만듦 */
	newNode->right = NULL; /* newNode의 right부분을 빈공간으로 만듦 */

	if (head->left == NULL) { /* head의 left부분이 빈공간이라면 */
		head->left = newNode; /* newNode를 head의 left부분에 넣음 */
		return 1; /* 1을 반환함 */
	}

	/* head->left is the root */
	Node* ptr = head->left; /* head의 left부분을 Node포인터 ptr에 넣음 */
	Node* parentNode = NULL; /* Node포인터 parentNode를 빈공간으로 만듦 */
	while(ptr != NULL) { /* ptr이 null이 아니라면 */

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; /* ptr의 key부분이 key라면 1을 반환함 */

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; /* parentNode에 ptr을 넣음 */

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) /* ptr의 key부분이 key보다 작다면 */
			ptr = ptr->right; /* ptr에 ptr의 right부분을 넣음 */
		else /* ptr의 key부분이 key보다 작지 않다면 */
			ptr = ptr->left; /* ptr에 ptr의 left부분을 넣음 */
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) /* parentNode의 key부분이 key보다 크다면 */
		parentNode->left = newNode; /* parentNode의 left부분에 newNode를 넣음 */
	else /* ptr의 key부분이 key라보다 크지 않다면 */
		parentNode->right = newNode; /* parentNode의 right부분에 newNode를 넣음 */
	return 1; /* 1을 반환함 */
}

int deleteLeafNode(Node* head, int key) /* 키를 위해 있는 leaf 노드 삭제하는 함수 정의 */
{
	if (head == NULL) { /* head가 빈공간이라면 */
		printf("\n Nothing to delete!!\n"); /* print */
		return -1; /* -1을 반환함 */
	}

	if (head->left == NULL) {  /* head의 left부분이 빈공간이라면 */
		printf("\n Nothing to delete!!\n"); /* print */
		return -1; /* -1을 반환함 */
	}

	/* head->left is the root */
	Node* ptr = head->left; /* Node포인터 ptr에 head의 left부분을 넣음 */


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; /* Node포인터 parentNode에 head를 넣음 */

	while(ptr != NULL) { /* ptr이 빈공간이라면*/
			if(ptr->key == key) { /* ptr의 key부분이 key라면 */
			if(ptr->left == NULL && ptr->right == NULL) { /* prt의 left부분과 right부분이 둘 다 빈공간이라면 */

				/* root node case */
				if(parentNode == head) /* parentNode가 head와 같다면 */
					head->left = NULL; /* head의 left부분을 빈공간으로 만듦 */

				/* left node case or right case*/
				if(parentNode->left == ptr) /* parentNode의 left부분이 ptr과 같다면 */
					parentNode->left = NULL; /* parentNode의 left부분을 빈공간으로 만듦 */
				else
					parentNode->right = NULL; /* parentNode의 right부분을 빈공간으로 만듦 */

				free(ptr); /* ptr을 free시킴 */
			}
			else { 
				printf("the node [%d] is not a leaf \n", ptr->key); /* print */
			}
			return 1; /* 1을 반환함 */
		}
	}

		/* keep the parent node */
		parentNode = ptr; /* parentNode에 ptr을 넣음 */

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) /* ptr의 key부분이 key보다 작다면 */
			ptr = ptr->right; /* ptr에 ptr의 right부분을 넣음 */
		else /* ptr의 key부분이 key보다 작지 않다면 */
			ptr = ptr->left; /* ptr에 ptr의 left부분을 넣음 */


	}

	printf("Cannot find the node for key [%d]\n ", key); /* print */

	return 1;  /* 1을 반환함 */
}

Node* searchRecursive(Node* ptr, int key) /* 노드를 순회해서 탐색하는 함수 정의 */
{
	if(ptr == NULL) /* ptr이 빈공간이라면 */
		return NULL; /* 빈공간을 반환함 */

	if(ptr->key < key) /* ptr의 key부분이 key보다 작다면 */
		ptr = searchRecursive(ptr->right, key); /* searchRecursive 함수를 실행해서 ptr에 넣음 */
	else if(ptr->key > key) /* ptr의 key부분이 key보다 크다면 */
		ptr = searchRecursive(ptr->left, key); /* searchRecursive 함수를 실행해서 ptr에 넣음 */

	/* if ptr->key == key */
	return ptr; /* ptr을 반환함 */
 
}
Node* searchIterative(Node* head, int key) /* 노드를 순회하지않고 탐색하는 함수 정의 */
{
	/* root node */
	Node* ptr = head->left; /* Node포인터 ptr에 head의 left부분을 넣음 */

	while(ptr != NULL) /* ptr이 빈공간이 아니라면 */
	{
		if(ptr->key == key) /* ptr의 key부분이 key와 같다면 */
			return ptr; /* ptr을 반환함 */

		if(ptr->key < key) /* ptr의 key부분이 key보다 작다면 */
			ptr = ptr->right; /* ptr에 ptr의 right부분을 넣음 */
		else /* ptr의 key부분이 key보다 작지 않다면 */
			ptr = ptr->left; /* ptr에 ptr의 left부분을 넣음 */
	}

	return NULL; /* 빈공간을 반환함 */
}

void freeNode(Node* ptr) /* 노드를 해제하는 함수 정의 */
{
	if(ptr) { /* ptr이 ~라면 */
		freeNode(ptr->left); /* freeNode 함수 실행 */
		freeNode(ptr->right); /* freeNode 함수 실행 */
		free(ptr); /* ptr을 free시킴 */
	}
}

int freeBST(Node* head) /* 트리에 할당된 모든 메모리를 해제하는 함수 정의 */
{

	if(head->left == head) /* head의 left 부분이 head라면 */
	{
		free(head); /* head를 free시킴 */
		return 1; /* 1을 반환함 */
	}

	Node* p = head->left; /* head의 left부분을 Node포인터 p에 넣음 */

	freeNode(p); /* freeNode 함수 실행 */

	free(head); /* head를 free시킴 */
	return 1; /* 1을 반환함 */
}