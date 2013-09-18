#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<malloc.h>
typedef struct Point Point;
struct Point
{
	int xco,yco;
	Point *next;
};
Point *head=NULL,*tail=NULL;
int boundary=WHITE;
void FloodFill();
void Enqueue(int a,int b);
Point * Dequeue();
void DoTheNeeded(int a,int b);
int IsPresent(int a,int b);
void main()
{
	int x[10],y[10],nedges;
	int gd=DETECT,gm,count,xin,yin,bg=4;
	printf("\nEnter the number of edges you will like to have in your polygon");
	scanf("%d",&nedges);
	for(;nedges<=2;)
	{
		printf("\nPlease enter the correct number of edges");
		scanf("%d",&nedges);
	}
	for(count=0;count<nedges;count++)
	{
		printf("\nEnter the x co-ordinate of the %d vertex",count+1);
		scanf("%d",&x[count]);
		printf("\nEnter the y co-ordinate of the %d vextex",count+1);
		scanf("%d",&y[count]);
	}
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	for(count=0;count<nedges;count++)
	{
		line(x[count],y[count],x[(count+1)%nedges],y[(count+1)%nedges]);
	}
	FloodFill();
	printf("\nEnd of process");
	getch();
}
void FloodFill()
{
	int xin,yin,current,bg=4,count=0;
	Point *Consider;
	printf("\nEnter the x-cordinate of internal point of the polygon");
	scanf("\n%d",&xin);
	printf("\nEnter the y-cordinate of internal point of the polygon");
	scanf("\n%d",&yin);
	do
	{
		if(head==NULL)
		{
			DoTheNeeded(xin,yin);
			putpixel(xin,yin,bg);
		}
		else
		{
			Consider=Dequeue();
			DoTheNeeded(Consider->xco,Consider->yco);
			putpixel(Consider->xco,Consider->yco,bg);
			free(Consider);
		}
		count++;
	}while(head!=NULL);
}
void DoTheNeeded(int x,int y)
{
	if(getpixel(x-1,y)==boundary /*|| getpixel(x-1,y+1)==boundary|| getpixel(x-1,y-1)==boundary*/ || getpixel(x,y+1)==boundary || getpixel(x,y-1)==boundary/*|| getpixel(x+1,y+1)==boundary || getpixel(x+1,y-1)==boundary*/ ||getpixel(x+1,y)==boundary)
	{
		return;
	}
	if(getpixel(x-1,y)!=boundary)
	{
		if(IsPresent(x-1,y))
		Enqueue(x-1,y);
	}
	/*if(getpixel(x-1,y+1)!=boundary)
	{
		if(IsPresent(x-1,y+1))
		Enqueue(x-1,y+1);
	}
	if(getpixel(x-1,y-1)!=boundary)
	{
		if(IsPresent(x-1,y-1))
		Enqueue(x-1,y-1);
	}*/
	if(getpixel(x,y+1)!=boundary)
	{
		if(IsPresent(x,y+1))
		Enqueue(x,y+1);
	}
	if(getpixel(x,y-1)!=boundary)
	{
		if(IsPresent(x,y-1))
		Enqueue(x,y-1);
	}
	/*if(getpixel(x+1,y+1)!=boundary)
	{
		if(IsPresent(x+1,y+1))
		Enqueue(x+1,y+1);
	}*/
	if(getpixel(x+1,y)!=boundary)
	{
		if(IsPresent(x+1,y))
		Enqueue(x+1,y);
	}
	/*if(getpixel(x+1,y-1)!=boundary)
	{
		if(IsPresent(x+1,y-1))
		Enqueue(x+1,y-1);
	}*/
}
void Enqueue(int a,int b)
{
	Point *Raw;
	Raw=(Point*)malloc(sizeof(Point));
	if(Raw==NULL)
		printf("\nMemory could not be allocated");
	if(head==NULL)
	{
		head=Raw;
		tail=head;
	}
	else
	{
		tail->next=Raw;
		tail=tail->next;
	}
	tail->xco=a;
	tail->yco=b;
	tail->next=NULL;
}
Point* Dequeue()
{
	Point *re;
	re=head;
	head=head->next;
	return re;
}
int IsPresent(int a,int b)
{
	Point *check;
	for(check=head;check!=NULL;check=check->next)
	{
		if(a==check->xco && b==check->yco)
		{
			return 0;
		}
	}
	return 1;
}