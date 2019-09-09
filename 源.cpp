#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;
#define SIZE 10
//˳���
#if 0
typedef struct Sqlist
{
	int elem[SIZE];
	int length;
}Sqlist;

//��ʼ��
void InitSqlist(Sqlist *psq)
{
	assert(psq != nullptr);
	if (psq == nullptr)
	{
		return;
	}
	psq->length = 0;
}

//����  ������
bool Full(Sqlist *psq)
{
	if (psq->length == SIZE)
	{
		return true;
	}
	return false;
}

//���룬������ƶ�Ԫ��
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

//����keyֵ,�������±�
int Search(Sqlist* psq, int key)
{

	for (int i = 0; i < psq->length; ++i)
	{
		if (psq->elem[i] == key)
		return i;
	}
	return -1;
}

//ɾ��posλ�õ�ֵ,��*rtv������ֵ
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
	//ɾ����֮����ǰ�ƶ�Ԫ��
	for (int i = pos;i < psq->length - 1; ++i)
	{
		psq->elem[i] = psq->elem[i + 1];
	}
	psq->length--;
	return true;
}

//ɾ��һ��keyֵ
bool Delete(Sqlist* psq, int key)
{
	int index = Search(psq, key);
	if (index < 0)
	{
		return false;
	}
	return DeletePos(psq, index, nullptr);
}

//�õ�posλ�õ�ֵ,��* rtv����
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
//��ñ���Ч��
int Getlength(Sqlist* psq)
{
	return psq->length;
}

//��ձ�
void Clear(Sqlist* psq)
{
	psq->length = 0;
}

//�ݻٱ�
void Destroy(Sqlist* psq)
{
	Clear(psq);//δ��̬����
}

//��ӡ
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

//��̬����˳���
#if 0
typedef struct DSqlist
{
	int* elem;
	int usedsize;
	int size;
}DSqlist;

//��ʼ��
void InitDSqlist(DSqlist* psq)
{
	assert(psq != nullptr);
	psq->elem = (int*)malloc(sizeof(int));//��ʼ��һ���յ����Ա�
	assert(psq->elem != NULL);
	psq->usedsize = 0;
	psq->size = SIZE;//������ձ�Ĵ洢����
}

bool Full(DSqlist* psq)
{
	return psq->usedsize == psq->size;
}

//��������
void Inc(DSqlist* psq)
{
	//remalloc()�ڴ˴��������ڴ�й©��������ݲ���ɹ�
	psq->elem = (int*)realloc(psq->elem, psq->size * 2 * sizeof(int));
	assert(psq->elem != nullptr);
	psq->size *= 2;
}

//��posλ�ò���val��ֵ
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

//����keyֵ
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

//ɾ��posλ�õ�ֵ
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

//ɾ��һ��keyֵ
bool Delete(DSqlist* psq, int pos, int key)
{
	pos = Search(psq, key);
	if (pos < 0)
	{
		return false;
	}
	return DeletePos(psq, pos, nullptr);
}

//�õ�posλ�õ�ֵ
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
//�ڴ�й© ��Ҫ�ֶ��ͷ�
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

//�������
#if 0
typedef struct Node
{
	int data;
	Node* next;
}Node;

//��ʼ��������
void InitList(Node* pl)
{
	assert(pl != nullptr);
	pl->next = nullptr;
}

//������Ҫ�õ�һ���ڵ㣬�ٽ��в���
Node* GetNode(int val)
{
	Node* q = (Node*)malloc(sizeof(Node));
	assert(q != nullptr);
	q->data = val;
	q->next = nullptr;
	return q;
}

//ͷ�巨
void Insert_head(Node* pl, int val)
{
	assert(pl != nullptr);
	Node* q = GetNode(val);
	q->next = pl->next;
	pl->next = q;
}

//β�巨
bool Insert_tail(Node* pl, int val)
{
	Node* cur = pl;//ָ��ͷ�ڵ�
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	Node* q = GetNode(val);
	cur->next = q;
	return true;
}

//����key��ǰ��
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

//ɾ��key������
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

//�Ƿ�Ϊ��
bool Empty(Node* pl)
{
	if (pl == nullptr || pl->next == nullptr)
	{
		return true;
	}
	return false;
}

//�ݻٺ���������ж�̬�����ڴ�Ļ���
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


//�õ�������ĳ���
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

//��ӡ������
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

//ѭ��������
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
	CLNode* cur = plist;//ָ��ͷ�ڵ�
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

//ѭ��˫����
#if 0
typedef struct DNode
{
	int data;
	DNode* pri;
	DNode* next;
}DNode, * DList;

//��ʼ��
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
//ͷ�巨
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

//β�巨
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

//����key��ǰ��
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

//ɾ��key������
bool Delete(DList plist, int key)
{
	DNode* p = Search_pre(plist, key);
	if (p == nullptr)
	{
		return false;
	}
	DNode* pDel = p->next;//ɾ���Ľڵ�
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

