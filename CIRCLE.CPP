#include<stdio.h>
#include<graphics.h>
#include<conio.h>
void BresenhamCircle(int a,int b,int c);
void MidPointCircle(int a,int b,int c);
void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	BresenhamCircle(320,240,40);
	MidPointCircle(320,240,80);
	getch();
	closegraph();
}
void BresenhamCircle(int xco,int yco,int radius)
{
	int x,y,p;
	for(x=0,y=radius;x<=y;x++)
	{
		putpixel(x+xco,y+yco,15);
		putpixel(xco-x,y+yco,15);
		putpixel(x+xco,yco-y,15);
		putpixel(xco-x,yco-y,15);
		putpixel(y+xco,x+yco,15);
		putpixel(xco-y,x+yco,15);
		putpixel(y+xco,yco-x,15);
		putpixel(xco-y,yco-x,15);
		if(x==0)
		{
			p=3-2*radius;
		}
		else
		{
			if(p>0)
			{
				p=p+4*(x-y)+10;
			}
			else
			{
				p=p+4*x+6;
			}
		}
		if(p>0)
		{
			y--;
		}
	}
}
void MidPointCircle(int xco,int yco,int radius)
{
	int x,y,p;
	for(x=0,y=radius;x<=y;x++)
	{
		putpixel(x+xco,y+yco,15);
		putpixel(xco-x,y+yco,15);
		putpixel(x+xco,yco-y,15);
		putpixel(xco-x,yco-y,15);
		putpixel(y+xco,x+yco,15);
		putpixel(xco-y,x+yco,15);
		putpixel(y+xco,yco-x,15);
		putpixel(xco-y,yco-x,15);
		if(x==0)
		{
			p=1-radius;
		}
		else
		{
			if(p>0)
			{
				p=p+2*x-2*(y-1)+3;
			}
			else
			{
				p=p+2*x+3;
			}
		}
		if(p>0)
		{
			y--;
		}
	}
}