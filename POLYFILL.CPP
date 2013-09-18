#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
typedef struct edge EDGE;

void PolyFill();
void CreateActiveEdgeList(int a);
int IsAActiveEdge(int a,int b);
void SortActiveEdgeList();

struct edge
{
	int ymin,ymax;
	float slope,xval;
}EdgeList[10],ActiveEdgeList[10];
int x[10],y[10],nedges,ActiveEdges;
void main()
{
	int gd=DETECT,gm,count,a,b;
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
	PolyFill();
	getch();
	closegraph();
}
void PolyFill()
{
	int count,count1,a,b;
	float temp;
	for(count=0;count<nedges;count++)
	{
		if(y[count]<y[(count+1)%nedges])
		{
			EdgeList[count].ymin=y[count];
			EdgeList[count].ymax=y[(count+1)%nedges];
			EdgeList[count].xval=x[count];
		}
		else if(y[(count+1)%nedges]<=y[count])
		{
			EdgeList[count].ymin=y[(count+1)%nedges];
			EdgeList[count].ymax=y[count];
			EdgeList[count].xval=x[(count+1)%nedges];
		}
		if(y[count]-y[(count+1)%nedges]!=0)
		{
			temp=x[count]-x[(count+1)%nedges];
			temp=temp/(y[count]-y[(count+1)%nedges]);
			EdgeList[count].slope=temp;
		}
		else
		{
			EdgeList[count].slope=65535;
		}
	}
	for(count=0;count<nedges;count++)
	{
		if(count==0)
		{
			a=EdgeList[count].ymin;
			b=EdgeList[count].ymax;
		}
		else
		{
			if(EdgeList[count].ymin<a)
				a=EdgeList[count].ymin;
			if(EdgeList[count].ymax>b)
				b=EdgeList[count].ymax;
		}
	}
	for(count=0;count<=480;count++)
	{
		CreateActiveEdgeList(count);
		SortActiveEdgeList();
		for(count1=0;count1<ActiveEdges/2;count1++)
		{
			line(ActiveEdgeList[count1*2].xval,count,ActiveEdgeList[count1*2+1].xval,count);
			delay(10);
		}
	}
}
void CreateActiveEdgeList(int a)
{
	int count,test;
	float temp;
	ActiveEdges=0;
	for(count=0;count<nedges;count++)
	{
		if(EdgeList[count].slope==65535)
			continue;
		test=IsAActiveEdge(count,a);
		if(test==-1)
			continue;
		else
		{
			temp=EdgeList[count].xval;
			temp=temp+EdgeList[count].slope*(a-EdgeList[count].ymin);
			ActiveEdgeList[ActiveEdges].xval=temp;
			ActiveEdges++;
		}
	}
}
int IsAActiveEdge(int n,int a)
{
	if(a<=EdgeList[n].ymax && a>EdgeList[n].ymin)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
void SortActiveEdgeList()
{
	int i,j;
	float temp;
	for(i=0;i<ActiveEdges;i++)
	{
		for(j=0;j<ActiveEdges-1-i;j++)
		{
			if(ActiveEdgeList[j].xval>ActiveEdgeList[j+1].xval)
			{
				temp=ActiveEdgeList[j].xval;
				ActiveEdgeList[j].xval=ActiveEdgeList[j+1].xval;
				ActiveEdgeList[j+1].xval=temp;
			}
		}
	}
}