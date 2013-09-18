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
}rect[2],linepts[2],todraw[2];
char list[2][10]={'l','e','f','t','m','o','s','t','\0','\0','r','i','g','h','t','m','o','s','t','\0'};
unsigned char code;
void AssignCode();
char pow(char a,char b);
void main()
{
	int count;
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
	AssignCode();
	printf("code=%d      %d      %d    %d     %d",code,code&15,code>>4,code,(code&15)&(code>>4));
	if(((code&15)&(code>>4))==0)
	{
		printf("\n Need to process");
	}
	else
	{
		printf("\n No need");
	}
	getch();
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