#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<graphics.h>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 3
#define TOP 4
typedef struct Point Point;
struct Point
{
	int x,y;
	Point *Next;
};
Point *vertices[2],rect[2],*last[2],*current;
char nvertices,Direction[4];
char list[2][10]={'l','e','f','t','m','o','s','t','\0','\0','r','i','g','h','t','m','o','s','t','\0'};

void AddVertex(float x,float y,int count);
char AssignCode(char a);
void SHPC();
void FindIntersection(char a);
int xin,yin;
void main()
{
	int gd=DETECT,gm,count;
	int x,y;
	Direction[0]=LEFT;
	Direction[1]=RIGHT;
	Direction[2]=BOTTOM;
	Direction[3]=TOP;
	for(count=0;count<2;count++)
	{
		printf("Enter the %s point\'s x-cordinate",list[count]);
		scanf("%d",&rect[count].x);
		printf("Enter the %s point\'s y-cordinate",list[count]);
		scanf("%d",&rect[count].y);
		rect[count].Next=NULL;
	}
	printf("\nEnter the number of vertices you will like to have in the polygon");
	scanf("%d",&nvertices);
	for(count=0;count<nvertices;count++)
	{
		printf("\nEnter the x-cordiante of the %d vertex",count+1);
		scanf("%d",&x);
		printf("\nEnter the y-cordiante of the %d vertex",count+1);
		scanf("%d",&y);
		AddVertex(x,y,0);
	}
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	current=vertices[0];
	line(rect[0].x,rect[0].y,rect[0].x,rect[1].y);
	line(rect[0].x,rect[1].y,rect[1].x,rect[1].y);
	line(rect[1].x,rect[1].y,rect[1].x,rect[0].y);
	line(rect[1].x,rect[0].x,rect[0].x,rect[0].y);
	do
	{
		line(current->x,current->y,current->Next->x,current->Next->y);
		current=current->Next;
	}while(current!=vertices[0]);
	getch();
	cleardevice();
	SHPC();
	cleardevice();
	current=vertices[0];
    do
	{
		line(current->x,current->y,current->Next->x,current->Next->y);
		current=current->Next;
	}while(current!=vertices[0]);
	getch();
	closegraph();
	getch();
}
void SHPC()
{
	int count=0;
	char code;
	for(count=0;count<4;count++)
	{
		current=vertices[0];
		do
		{
			code=AssignCode(Direction[count]);
			switch(code)
			{
			case 0:
				break;
			case 1:
				FindIntersection(Direction[count]);
				AddVertex(xin,yin,1);
				break;
			case 2:
				FindIntersection(Direction[count]);
				AddVertex(xin,yin,1);
				AddVertex(current->Next->x,current->Next->y,1);
				break;
			case 3:
				AddVertex(current->Next->x,current->Next->y,1);
				break;
			}
			current=current->Next;
		}while(current!=vertices[0]);
		vertices[0]=vertices[1];
		vertices[1]=NULL;
		current=vertices[0];
		getch();
		cleardevice();
		printf("Status after %d clip",count+1);
		line(rect[0].x,rect[0].y,rect[0].x,rect[1].y);
		line(rect[0].x,rect[1].y,rect[1].x,rect[1].y);
		line(rect[1].x,rect[1].y,rect[1].x,rect[0].y);
		line(rect[1].x,rect[0].x,rect[0].x,rect[0].y);
		do
		{
			line(current->x,current->y,current->Next->x,current->Next->y);
			current=current->Next;
		}while(current!=vertices[0]);
		getch();
	}
}
char AssignCode(char a)
{
	char code=0;
	switch(a)
	{
	case LEFT:
		if(current->x<rect[0].x)
			code=code+0;
		else
			code=code+1;
		if(current->Next->x<rect[0].x)
			code=code+0;
		else
			code=code+2;
		break;
	case RIGHT:
		if(current->x>rect[1].x)
			code=code+0;
		else
			code=code+1;
		if(current->Next->x>rect[1].x)
			code=code+0;
		else
			code=code+2;
		break;
	case BOTTOM:
		if(current->y<rect[0].y)
			code=code+0;
		else
			code=code+1;
		if(current->Next->y<rect[0].y)
			code=code+0;
		else
			code=code+2;
		break;
	case TOP:
		if(current->y>rect[1].y)
			code=code+0;
		else
			code=code+1;
		if(current->Next->y>rect[1].y)
			code=code+0;
		else
			code=code+2;
		break;
	}
	return code;
}
void AddVertex(float x,float y,int count)
{
	Point *New;
	if(vertices[count]==NULL)
	{
		vertices[count]=(Point*)malloc(sizeof(Point));
		vertices[count]->Next=vertices[count];
		vertices[count]->x=x;
		vertices[count]->y=y;
		last[count]=vertices[count];
	}
	else
	{
		New=(Point*)malloc(sizeof(Point));
		New->x=x;
		New->y=y;
		New->Next=vertices[count];
		last[count]->Next=New;
		last[count]=New;
	}
}
void FindIntersection(char a)
{
	float slope,islope;
	int horizontal,vertical;
	if(current->x==current->Next->x)
	{
		horizontal=1;
		slope=0;
	}
	else if(current->y==current->Next->y)
	{
		vertical=1;
		islope=0;
	}
	else
	{
		slope=(float)(current->y-current->Next->y)/(current->x-current->Next->x);
		islope=1/slope;
	}
	switch(a)
	{
	case LEFT:
		xin=rect[0].x;
		yin=slope*(xin-current->x)+current->y;
		break;
	case RIGHT:
		xin=rect[1].x;
		yin=slope*(xin-current->x)+current->y;
		break;
	case BOTTOM:
		yin=rect[0].y;
		xin=islope*(yin-current->y)+current->x;
		break;
	case TOP:
		yin=rect[1].y;
		xin=islope*(yin-current->y)+current->x;
		break;
	}
}