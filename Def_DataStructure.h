
#define INIT_LIST_SIZE 10
#define LISTINCREMENT  2

typedef struct
{
	ElemType *elem;
	int length;
	int listsize;
}SqList;