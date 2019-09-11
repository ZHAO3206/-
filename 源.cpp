#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;
#define SIZE 10
//顺序表
#if 0
typedef struct Sqlist
{
	int elem[SIZE];
	int length;
}Sqlist;

//初始化
void InitSqlist(Sqlist *psq)
{
	assert(psq != nullptr);
	if (psq == nullptr)
	{
		return;
	}
	psq->length = 0;
}

//判满  不扩容
bool Full(Sqlist *psq)
{
	if (psq->length == SIZE)
	{
		return true;
	}
	return false;
}

//插入，并向后移动元素
bool Insert(Sqlist* psq, int pos, int val)
{
	if (pos<0 || pos>psq->length)
	{
		return false;
	}
	if (Full(psq))
	{
		return false;
	}
	for (int i = psq->length-1; i >= pos; --i)
	{
		psq->elem[i + 1] = psq->elem[i];
	}
	psq->elem[pos] = val;
	psq->length++;
	return true;
}

//查找key值,并返回下标
int Search(Sqlist* psq, int key)
{

	for (int i = 0; i < psq->length; ++i)
	{
		if (psq->elem[i] == key)
		return i;
	}
	return -1;
}

//删除pos位置的值,用*rtv返回其值
bool DeletePos(Sqlist* psq, int pos, int* rtv)
{
	if (pos<0 || pos>psq->length - 1)
	{
		return false;
	}
	if (rtv != nullptr)
	{
		*rtv = psq->elem[pos];
	}
	//删除，之后向前移动元素
	for (int i = pos;i < psq->length - 1; ++i)
	{
		psq->elem[i] = psq->elem[i + 1];
	}
	psq->length--;
	return true;
}

//删除一个key值
bool Delete(Sqlist* psq, int key)
{
	int index = Search(psq, key);
	if (index < 0)
	{
		return false;
	}
	return DeletePos(psq, index, nullptr);
}

//得到pos位置的值,用* rtv返回
bool Getelem(Sqlist* psq, int pos, int* rtv)
{
	if (pos <0 || pos>psq->length - 1)
	{
		return false;
	}
	if (rtv != nullptr)
	{
		*rtv = psq->elem[pos];
	}
	return true;
}
//获得表有效长
int Getlength(Sqlist* psq)
{
	return psq->length;
}

//清空表
void Clear(Sqlist* psq)
{
	psq->length = 0;
}

//摧毁表
void Destroy(Sqlist* psq)
{
	Clear(psq);//未动态开辟
}

//打印
void Show(Sqlist* psq)
{
	for (int i = 0; i < psq->length; ++i)
	{
		printf("%d ", psq->elem[i]);
	}
	printf("\n");
}

int main()
{
	Sqlist sq;
	InitSqlist(&sq);
	for (int i = 0; i < 8; ++i)
	{
		Insert(&sq, i, i);
	}
	Show(&sq);

	Insert(&sq, 5, 20);
	Show(&sq);

	printf("%d\n", Search(&sq, 5));

	int tmp = 0;
	DeletePos(&sq, 4, &tmp);
	printf("%d\n", tmp);
	Show(&sq);

	Delete(&sq, 6);
	Show(&sq);

	Getelem(&sq, 6, &tmp);
	printf("%d\n", tmp);
	
	printf("%d\n", Getlength(&sq));

	//Clear(&sq);
	//Show(&sq);


	return 0;
}

#endif

//动态开辟顺序表
#if 0
typedef struct DSqlist
{
	int* elem;
	int usedsize;
	int size;
}DSqlist;

//初始化
void InitDSqlist(DSqlist* psq)
{
	assert(psq != nullptr);
	psq->elem = (int*)malloc(SIZE*sizeof(int));//初始化一个空的线性表
	assert(psq->elem != NULL);
	psq->usedsize = 0;
	psq->size = SIZE;//分配给空表的存储容量
}

bool Full(DSqlist* psq)
{
	return psq->usedsize == psq->size;
}

//二倍扩容
void Inc(DSqlist* psq)
{
	//可能会发生内存泄漏
	psq->elem = (int*)realloc(psq->elem, psq->size * 2 * sizeof(int));
	assert(psq->elem != nullptr);
	psq->size *= 2;
}

//在pos位置插入val的值
bool Insert(DSqlist* psq, int pos, int val)
{
	if (Full(psq))
	{
		Inc(psq);
	}
	if (pos<0 || pos>psq->usedsize)
	{
		return false;
	}
	for (int i = psq->usedsize-1; i >= pos;--i)
	{
		psq->elem[i+1] = psq->elem[i];
	}
	psq->elem[pos] = val;
	psq->usedsize++;
	return true;
}

//查找key值
int Search(DSqlist* psq, int key)
{
	for (int pos = 0; pos < psq->usedsize - 1; ++pos)
	{
		if (psq->elem[pos] == key)
		{
			return pos;
		}
	}
}

//删除pos位置的值
bool DeletePos(DSqlist* psq, int pos, int* rtv)
{
	if (pos<0 || pos>psq->usedsize - 1)
	{
		return false;
	}
	if (rtv != nullptr)
	{
		*rtv = psq->elem[pos];
	}
	for (int i = pos; i < psq->usedsize; ++i)
	{
		psq->elem[i] = psq->elem[i + 1];
	}
	psq->usedsize--;
	return true;
}

//删除一个key值
bool Delete(DSqlist* psq, int pos, int key)
{
	pos = Search(psq, key);
	if (pos < 0)
	{
		return false;
	}
	return DeletePos(psq, pos, nullptr);
}

//得到pos位置的值
bool Getelem(DSqlist* psq, int pos, int* rtv)
{
	if (pos<0 || pos>psq->usedsize-1)
	{
		return false;
	}
	if (rtv != nullptr)
	{
		*rtv = psq->elem[pos];
	}
	return true;
}


int GetLength(DSqlist* psq)
{
	return psq->usedsize;
}
/*
void Clear(DSqlist* psq);
*/
//内存泄漏 需要手动释放
void Destroy(DSqlist* psq)
{
	free(psq->elem);
	psq->elem = nullptr;
	psq->usedsize = 0;
	psq->size = 0;
}

void Show(DSqlist* psq)
{
	for (int i = 0; i < psq->usedsize;++i)
	{
		printf("%d ", psq->elem[i]);
	}
	printf("\n");
}

int main()
{
	DSqlist dsq;
	InitDSqlist(&dsq);
	for (int i = 0; i < 8; ++i)
	{
		Insert(&dsq, i, i);
	}
	Show(&dsq);
	Insert(&dsq, 5, 20);

	Show(&dsq);
	printf("%d\n", Search(&dsq, 20));

	int tmp = 0;
	DeletePos(&dsq, 5, &tmp);
	Show(&dsq);

	Delete(&dsq, NULL, 2);
	Show(&dsq);
	printf("%d\n", GetLength(&dsq));

	printf("%d\n", Getelem(&dsq, 3, &tmp));

	return 0;
}
#endif // 1

//链表操作
#if 0
typedef struct Node
{
	int data;
	Node* next;
}Node;

//初始化单链表
void InitList(Node* pl)
{
	assert(pl != nullptr);
	pl->next = nullptr;
}

//首先需要得到一个节点，再进行插入
Node* GetNode(int val)
{
	Node* q = (Node*)malloc(sizeof(Node));
	assert(q != nullptr);
	q->data = val;
	q->next = nullptr;
	return q;
}

//头插法
void Insert_head(Node* pl, int val)
{
	assert(pl != nullptr);
	Node* q = GetNode(val);
	q->next = pl->next;
	pl->next = q;
}

//尾插法
bool Insert_tail(Node* pl, int val)
{
	Node* cur = pl;//指向头节点
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	Node* q = GetNode(val);
	cur->next = q;
	return true;
}

//查找key的前驱
Node* Search_pre(Node* pl, int key)
{
	Node* cur = pl;
	while (cur->next != pl)
	{
		if (cur->next->data == key)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

//删除key这个结点
bool Delete(Node* pl, int key)
{
	Node* cur = Search_pre(pl, key);
	if (cur == nullptr)
	{
		return false;
	}
	Node* pDel = cur->next;
	cur->next = pDel->next;
	free(pDel);
	pDel = nullptr;
	return true;
}

//是否为空
bool Empty(Node* pl)
{
	if (pl == nullptr || pl->next == nullptr)
	{
		return true;
	}
	return false;
}

//摧毁函数（如果有动态开辟内存的话）
void Destroy(Node* pl)
{
	Node* pDel = nullptr;
	while (pl->next != nullptr)
	{
		pDel = pl->next;
		pl->next = pDel->next;
		free(pDel);
		pDel = nullptr;
	}
}


//得到单链表的长度
int GetLength(Node* pl)
{
	int count = 0;
	Node* p = pl->next;
	while (p != nullptr)
	{
		count++;
		p = p->next;
	}
	return count;
}

//打印单链表
void Show(Node* pl)
{
	Node* p = pl->next;
	for (; p != nullptr; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}
int main()
{
	Node hj;
	InitList(&hj);
	/*for (int i = 0; i < 10; ++i)
	{
		Insert_head(&hj, i);
	}
	Show(&hj);
	*/

	for (int i = 0; i < 10; ++i)
	{
		Insert_tail(&hj, i);
	}
	Show(&hj);

	cout<<Search_pre(&hj, 5)<<" ";
	printf("\n");

	Delete(&hj, 3);
	Show(&hj);
	
	return 0;
}
#endif

//循环单链表
#if 0
typedef struct CLNode
{
	int data;
	CLNode* next;
}CLNode;
void InitCLNode(CLNode* plist)
{
	assert(plist != nullptr);
	if (plist == nullptr)
	{
		return;
	}
	plist->next = plist;
}
CLNode* GetNode(int val)
{
	CLNode* pGet = (CLNode*)malloc(sizeof(CLNode));
	assert(pGet != nullptr);
	pGet->data = val;
	pGet->next = pGet;
	return pGet;
}
bool Insert_head(CLNode* plist, int val)
{
	CLNode* pGet = GetNode(val);
	pGet->next = plist->next;
	plist->next = pGet;
	return true;
}
bool Insert_tail(CLNode* plist, int val)
{
	CLNode* cur = plist;//指向头节点
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	CLNode* pGet = GetNode(val);
	pGet->next = cur->next;
	cur->next = pGet;
	return true;
}
CLNode* Search_pre(CLNode* plist, int key)
{
	CLNode* p = plist;
	while (p->next != plist)
	{
		if (p->next->data == key)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}
bool Delete(CLNode* plist, int key)
{
	CLNode* p = Search_pre(plist, key);
	if (p == nullptr)
	{
		return false;
	}
	CLNode* pDel = p->next;
	p->next = pDel->next;
	free(pDel);
	pDel = nullptr;
	return true;
}
bool Empty(CLNode* plist)
{
	if (plist->next == nullptr || plist == nullptr)
	{
		return true;
	}
	return false;
}
void Destroy(CLNode* plist)
{
	CLNode* pDel = nullptr;
	while (plist->next != plist)
	{
		pDel = plist->next;
		plist->next = pDel->next;
		free(pDel);
		pDel = nullptr;
	}
}
int GetLength(CLNode* plist)
{
	int count = 0;
	CLNode* p = plist->next;
	while (p != plist)
	{
		count++;
		p = p->next;
	}
	return count;
}
void Show(CLNode* plist)
{
	CLNode* p = plist->next;
	while (p != plist)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

#endif // 1

//循环双链表
#if 0
typedef struct DNode
{
	int data;
	DNode* pri;
	DNode* next;
}DNode, * DList;

//初始化
void InitDList(DList plist)
{
	assert(plist != nullptr);
	plist->next = nullptr;
	plist->pri = nullptr;
}

DNode* GetNode(int val)
{
	DNode* pGet = (DNode*)malloc(sizeof(DNode));
	assert(pGet != nullptr);
	pGet->data = val;
	pGet->next = pGet;
	return pGet;
}
//头插法
bool Insert_head(DList plist, int val)
{
	DNode* pGet = GetNode(val);
	pGet->next = plist->next;
	pGet->pri = plist;
	plist->next = pGet;
	if (pGet->next != nullptr)
	{
		plist->next->pri = pGet;
	}
	return true;
}

//尾插法
bool Insert_tail(DList plist, int val)
{
	DNode* p = plist;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	DNode* pGet = GetNode(val);
	p->next = pGet;
	pGet->pri = p;
	return true;
}

//查找key的前驱
DNode* Search_pre(DList plist, int key)
{
	DNode* p = plist;
	for (;p->next != nullptr; p = p->next)
	{
		if (p->next->data == key)
		{
			return p;
		}
	}
	return NULL;
}

//删除key这个结点
bool Delete(DList plist, int key)
{
	DNode* p = Search_pre(plist, key);
	if (p == nullptr)
	{
		return false;
	}
	DNode* pDel = p->next;//删除的节点
	p->next = pDel->next;
	if (pDel->next != nullptr)
	{
		pDel->next->pri = p;
	}
	free(pDel);
	pDel = nullptr;
	return true;
}
bool Empty(DList plist)
{
	if (plist->next == nullptr)
	{
		return true;
	}
	return false;
}
void Destroy(DList plist)
{
	DNode* pDel = nullptr;
	while (plist->next != nullptr)
	{
		pDel = plist->next;
		plist->next = pDel->next;
		free(pDel);
		pDel = nullptr;
	}
}
int GetLength(DList plist)
{
	int count = 0;
	DNode* p = plist->next;
	while (p != nullptr)
	{
		count++;
		p = p->next;
	}
	return count;
}
void Show(DList plist)
{
	DNode* p = plist->next;
	for (;p != nullptr; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}
#endif // 1

