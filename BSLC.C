#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define LEFT 1
#define RIGHT 2
#define BELOW 4
#define ABOVE 8
typedef struct coef coef;
struct coef
{
	int x,y;
}rect[2],linepts[2],vp[2];

char list[2][10]={'l','e','f','t','m','o','s','t','\0','\0','r','i','g','h','t','m','o','s','t','\0'};
unsigned char code;

void AssignCode();
char pow(char a,char b);
int Between(int a,int b,int c);
void CSLC();

void main()
{
	int count;
	int gd=DETECT,gm;
	for(count=0;count<2;count++)
	{
		printf("Enter the %s point\'s x-cordinate",list[count]);
		scanf("%d",&rect[count].x);
		printf("Enter the %s point\'s y-cordinate",list[count]);
		scanf("%d",&rect[count].y);
	}
	for(count=0;count<2;count++)
	{
		printf("Enter the %d point\'s x-cordinate of the line",count+1);
		scanf("%d",&linepts[count].x);
		printf("Enter the %s point\'s y-cordinate",count+1);
		scanf("%d",&linepts[count].y);
	}
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	AssignCode();
	if(((code&15)&(code>>4))==0)
	{
		CSLC();
	}
	else
	{
		printf("\n No need");
	}
	getch();
	closegraph();
}
void CSLC()
{
	int count=0,vpcount=0,vertical=0,horizontal=0,xin,yin;
	float m,im;
	if(code==0)
	{
		line(linepts[0].x,linepts[0].y,linepts[1].x,linepts[1].y);
		return;
	}
	else
	{
		if(linepts[0].x==linepts[1].x)
		{
			vertical=1;
			im=0;
		}
		else if(linepts[0].y==linepts[1].y)
		{
			horizontal=1;
			m=0;
		}
		else
		{
			m=(linepts[0].y-linepts[1].y)/(linepts[0].x-linepts[1].x);
			im=1/m;
		}
		for(count=0;count<2 &&vpcount<1;count++)
		{
			if(Between(linepts[count].x,rect[0].x,rect[1].x) && Between(linepts[count].y,rect[0].y,rect[1].y))
			{
				vp[vpcount].x=linepts[count].x;
				vp[vpcount].y=linepts[count].y;
				vpcount++;
			}
		}
		for(count=0;count<2 && vpcount<2;count++)
		{
			if(vertical==0)
			{
				xin=rect[count].x;
				yin=linepts[0].y+m*(xin-linepts[0].x);
			}
			if(Between(xin,rect[0].x,rect[1].x) && Between(yin,rect[0].y,rect[1].y))
			{
				vp[vpcount].x=xin;
				vp[vpcount].y=yin;
				vpcount++;
			}
			if(vpcount==2)
				break;
			if(horizontal==0)
			{
				yin=rect[count].y;
				xin=linepts[0].x+im*(yin-linepts[0].y);
			}
			if(Between(xin,rect[0].x,rect[1].x) && Between(yin,rect[0].y,rect[1].y))
			{
				vp[vpcount].x=xin;
				vp[vpcount].y=yin;
				vpcount++;
			}
		}
		if(vpcount==0)
		{
			return;
		}
		else
		{
			line(vp[0].x,vp[0].y,vp[1].x,vp[1].y);
		}
	}
}
int Between(int a,int b,int c)
{
	if((a<=b && a>=c)||(a>=b && a<=c))
	{
		return 1;
	}
	return 0;
}
void AssignCode()
{
	int count,inc;
	code=0;
	for(count=0;count<2;count++)
	{
		if(linepts[count].x<rect[0].x)
		{
			code=code+pow(16,count)*LEFT;
		}
		else if(linepts[count].x>rect[1].x)
		{
			code=code+pow(16,count)*RIGHT;
		}
		if(linepts[count].y<rect[0].y)
		{
			code=code+pow(16,count)*BELOW;
		}
		else if(linepts[count].y>rect[1].y)
		{
			code=code+pow(16,count)*ABOVE;
		}
	}
	line(rect[0].x,rect[0].y,rect[1].x,rect[0].y);
	line(rect[1].x,rect[1].y,rect[1].x,rect[0].y);
	line(rect[1].x,rect[1].y,rect[0].x,rect[1].y);
	line(rect[0].x,rect[0].y,rect[0].x,rect[1].y);
}
char pow(char a,char b)
{
	char res=1,count;
	for(count=0;count<b;count++)
	{
		res=res*a;
	}
	return res;
}