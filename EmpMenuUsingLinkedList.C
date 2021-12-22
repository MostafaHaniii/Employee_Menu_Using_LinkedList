#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "string.h"



#define UP				0x48
#define DOWN			0x50
#define HOME			0x47
#define END				0x4F
#define	ENTER			0xD
#define ESCAPE			0x1B
#define NORMAL_ATTR		0x0E
#define HILIGHT_ATTR	0xEE
#define NEW				0
#define DISPLAY			1
#define EXIT			2
#define SEARCH			3
#define DELETE			4
#define	INSERT			5
#define SORT			6

int j=0;


void dummy(float * a){

	float b =*a;
	dummy(&b);
}


typedef struct node
{
	int code;
	char name[10];
	float salary;
	float deduction;
	float bonus;
	struct node * next;
	struct node * prev;

}node;


typedef struct linkedList
{
	node * start;
	node * end;

}linkedList;


void sort(struct linkedList * LL);
struct node * create (void);
void appendNode(struct node * tmp,struct linkedList * LL);
struct node * searchNodeID(struct linkedList LL ,int key);
struct node * searchNodeName(struct linkedList LL,char * key);
int deleteNode (struct  linkedList *LL , int key);
void insertNode (struct linkedList * LL,struct node * ptr);
void printList(struct linkedList LL);


void main (void)

{
	 struct node * node;
	 struct linkedList LL;
	 char Menu[8][10] = {{"New"},{"Display"},{"Exit"},{"Search"},{"Delete"},{"Insert"}};
	 int t = 0;
	 int row = 5;
	 int col = 5;
	 int pos = 0;
	 int i ;
	 char ch;
	 char Kname[10];
	 int  dkey;
	 LL.start = LL.end = NULL;
	 do
	 {
		clrscr();

		for(i=0; i<7; i++)
		{
			gotoxy(col,row);
			if(i==pos)
			{
				textattr(HILIGHT_ATTR);
				cprintf("%s\n",Menu[i]);
				textattr(NORMAL_ATTR);
			}
			else
			{
				textattr(NORMAL_ATTR);
				cprintf("%s\n",Menu[i]);
			}
			row+=2;
		}
		row = 5;
		flushall();
		ch = getch();
			switch(ch)
		{
			case NULL	 : ch = getch();

			switch (ch)
			{
				case UP :
					if(pos == 0)
					{
						pos = 6;
					}
					else
					{
						pos--;
					}
					break;

				case DOWN :
					if(pos == 6)
					{
						pos = 0;
					}
					else
					{
						pos++;
					}
					break;
				case HOME:
					pos = 0;
					break;
				case END:
					pos = 6;
					break;
			}
			break;

			case ENTER	 :

				if(pos == NEW)
				{
				   int i;
				   clrscr();
				   //gotoxy(10,10);
				   node = create();
					   if(node == NULL)
				   {
					   clrscr();
					   printf("no space in heap");
					   getch();
				   }
				   else
				   {
					   appendNode(node,&LL);
				   }
				   getch();
				}
				else if(pos == DISPLAY)
				{
					int i;
					clrscr();
					printList(LL);
					getch();
				}
				else if(pos == EXIT)
				{
					clrscr();
					gotoxy(10,10);
					t = 1;
				}
				else if(pos == SEARCH)
				{
					clrscr();
					printf("Enter the name you want to search for :");
					flushall();
					scanf("%s",Kname);
					node = searchNodeName(LL,Kname);
					if(node == NULL)
					{
						printf("Name not found\n");
					}
					else
					{
						printf("Name found ----> %s",node->name);
					}

					getch();
				}
				else if(pos == DELETE)
				{
					clrscr();
					printf("Enter ID you want to delete: ");
					flushall();
					scanf("%d",&dkey);
					if(deleteNode(&LL,dkey) == 1)
					{
						printf("Item Deleted\n");
						//getch();
					}
					else
					{
						printf("Item Not Deleted\n");
					}
					getch();
				}
				else if(pos == INSERT)
				{
					clrscr();
					node = create();
					if(node == NULL)
					{
						printf("No space in heap");
					}
					else
					{
						insertNode(&LL,node);
					}
					getch();
				}
				  break;

			case ESCAPE	 : t = 1; break;
		}

	 }while(!t);
}

void printList(struct linkedList LL)
{
	printf("\n*************************************************************\n");
	while(LL.start != NULL)
	{
		printf("||Name : %10s ||Code : %2d||Net Salary = %2.2f||",LL.start->name,LL.start->code,(LL.start->salary+LL.start->bonus-LL.start->deduction));
		LL.start = LL.start->next;
		printf("\n");
	}
	printf("\n*************************************************************\n");
}

struct node * create (void)

{
	node * tmp;

	tmp = (struct node *) malloc(sizeof(struct node));

	if(tmp == NULL)
	{
		return NULL;			/*No memory in heap section*/
	}
	tmp->next = tmp->prev = NULL;
	printf("Enter The Data : \n");
	flushall();
	printf("Enter Name :");
	scanf("%s",tmp->name);
	printf("Enter code : ");
	scanf("%d",&tmp->code);
	printf("Basic Salary : ");
	scanf("%f",&tmp->salary);
	printf("Bonus : ");
	scanf("%f",&tmp->bonus);
	printf("Deduction : ");
	scanf("%f",&tmp->deduction);
	return tmp;
}

void appendNode(struct node * tmp,struct linkedList * LL)
{
	if(LL->start == NULL)	/*Empty List*/
	{
		LL->start = LL->end = tmp;
	}
	else
	{
		tmp->prev = LL->end;
		LL->end->next	= tmp;
		LL->end = tmp;
	}
}

struct node * searchNodeName(struct linkedList LL,char * key)
{
	struct node * tmp = LL.start;
	if(LL.start == NULL)		/*Empty List*/
	{
		return NULL;
	}
	else
	{
		while(tmp != NULL && strcmp(key,tmp->name) != 0)
		{
			tmp = tmp->next;
		}
	}
	return tmp;
}

struct node * searchNodeID(struct linkedList LL ,int key)
{
	struct node * tmp = LL.start;
	if(LL.start == NULL)		/*Empty List*/
	{
		return NULL;
	}
	else
	{
		while(tmp != NULL && tmp->code != key)
		{
			tmp = tmp->next;
		}
	}
	return tmp;
}



int deleteNode (struct  linkedList * LL , int key)
{
	struct node * tmp1;
	if(LL->start == NULL)		/*Empty List*/
	{
		return 0;
	}
	else
	{
		tmp1 = searchNodeID(*LL,key);
		if(tmp1 ==NULL)
		{
			return 0;
		}
		else
		{
			if(tmp1 == LL->start && tmp1 == LL->end)	//Only one Node
			{
				LL->start = LL->end = NULL;
				free(tmp1);
			}
			else
			{
				if(tmp1 == LL->start)					//First Node
				{
					LL->start = LL->start->next;
					LL->start->prev = NULL;
					free(tmp1);
				}
				else if(tmp1 == LL->end)				//Last Node
				{
					LL->end = LL->end->prev;
					LL->end->next = NULL;
					free(tmp1);
				}
				else
				{										//General Node
					tmp1->prev->next = tmp1->next;
					tmp1->next->prev = tmp1->prev;
					free(tmp1);
				}
			}
		}
		return 1;
	}
}

void insertNode (struct linkedList * LL,struct  node * ptr)
{
	struct node * tmp = LL->start;

	while(tmp != NULL && strcmp(ptr->name,tmp->name)>0)
	{
		tmp = tmp->next;
	}
	if(tmp == NULL)
	{
		appendNode(ptr,LL);
	}
	else if(tmp == LL->start)
	{
		tmp->prev = ptr;
		ptr->next = tmp;
		ptr->prev = NULL;
		LL->start = ptr;
	}
	else
	{
		tmp->prev->next = ptr;
		ptr->prev = tmp->prev;
		ptr->next = tmp;
		tmp->prev = ptr;
	}
}


void sort(struct linkedList * LL)
{
   int i;
   struct node * tempEmp;
   struct node * tmp = LL->start;
   i=0;
   if(tmp == NULL)	//Empty List
   {
		return;
   }
   while(!i)
   {
		i=1;
		while(tmp != NULL)
		{
			if(strcmp(tmp->name,tmp->next->name) > 0)
			{
				//tempEmp->name = tmp->name;
				strcpy(tempEmp->name , tmp->name);
				tempEmp->salary = tmp->salary;
				tempEmp->bonus	= tmp->bonus;
				tempEmp->deduction = tmp->deduction;
				tempEmp->code = tmp->code;
				tempEmp->next = tmp->next;
				tempEmp->prev = tmp->prev;

				//tmp->name = tmp->next->name;
				strcpy(tmp->name,tmp->next->name);
				tmp->salary = tmp->next->salary;
				tmp->bonus = tmp->next->bonus;
				tmp->deduction = tmp->next->deduction;
				tmp->code = tmp->next->code;
				tmp->next = tmp->next->next;
				tmp->prev = tmp->next->prev;

				//tmp->next->name = tempEmp->name;
				strcpy(tmp->next->name,tempEmp->name);
				tmp->next->salary = tempEmp->salary;
				tmp->next->bonus = tempEmp->bonus;
				tmp->next->deduction = tempEmp->deduction;
				tmp->next->code = tempEmp->code;
				tmp->next->next = tempEmp->next;
				tmp->next->prev = tempEmp->prev;
				i=0;
			}
			tmp = tmp->next;
		}
   }
}



