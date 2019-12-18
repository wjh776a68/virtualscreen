/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is an header file using in drawing simply shape and words in console.
 * This file is belong to Lanin project, you can find the latest progress in https://github.com/wjh776a68  
*/


#ifndef _VIRTUALSCREEN_
#define _VIRTUALSCREEN_
#pragma once

#ifndef _INC_STDIO
#include<stdio.h>
#endif

#ifndef _INC_STDLIB
#include<stdlib.h>
#endif

#ifndef int2char_const
#define int2char_const 90000
#endif





typedef struct  {
	int *_SP;
	int _WIDTH;
	int _HEIGHT;
}_SPvar,DRAW;

int char2int(char);
int int2char(char);
int axis2array(DRAW *&,int,int);

DRAW* drawstart(int, int);
void drawclose(DRAW *);
void drawclean(DRAW *&);

void addpixel(DRAW *&,int, int,int);
void addpixels(DRAW*&,int,int,int);
void addpixelc(DRAW *&,int, int,char);
void addline(DRAW *&,int,int,int,int);

void drawchar(DRAW *&);
void draw(DRAW *&);
void drawsmart(DRAW *&);
void drawint(DRAW *&);









/******************************
function: make char could live with normal int
input: char
output: int
******************************/ 
int char2int(char x)
{
	return x+int2char_const;
}

/******************************
function: make char lived with normal int recover to char
input: int
output: char
******************************/ 
char int2char(int x)
{
	return x-int2char_const;
}

/******************************
function: change a pixel of the drawing area. with int variety (0-9)
input: the DRAW pointer,the x ,y the value using int encode
output: void
error: print out : error:illegal screen range
******************************/
void addpixel(DRAW *&_SP,int _WIDTH, int _HEIGHT,int value)
{
	//printf("%d %d::",_SP->_WIDTH,_SP->_HEIGHT) ;
	if ((_SP->_WIDTH) * (_HEIGHT) + _WIDTH < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		*(_SP->_SP + (_SP->_WIDTH) * (_HEIGHT) + _WIDTH) = value;

	}
	else
	{
		printf("\nerror:illegal screen range\n");
	}
}

/******************************
function: change a pixel of the drawing area. with int variety (auto adjust length)
input: the DRAW pointer,the x ,y the value using int encode
output: void
error: print out : error:illegal screen range
******************************/
void addpixels(DRAW*& _SP, int _WIDTH, int _HEIGHT, int value)
{
	int length = 0;
	int decade = 10;
	while (decade <= value)
	{
		length++;
		decade *= 10;
	}

	while (length >= 0)
	{
		if ((_SP->_WIDTH) * (_HEIGHT)+_WIDTH+length < (_SP->_WIDTH) * (_SP->_HEIGHT))
		{
			*(_SP->_SP + (_SP->_WIDTH) * (_HEIGHT)+_WIDTH+length) = value%10;
			

		}
		else
		{
			printf("\nerror:illegal screen range\n");
		}
		length--;
		value /= 10;
	}
	


}


/******************************
function: change a pixel of the drawing area. with char variety
input: the DRAW pointer,the x ,y the value using int encode
output: void
error: print out : error:illegal screen range
******************************/
void addpixelc(DRAW *&_SP,int _WIDTH, int _HEIGHT,char value)
{
	//printf("%d %d::",_SP->_WIDTH,_SP->_HEIGHT) ;
	if ((_SP->_WIDTH) * (_HEIGHT ) + _WIDTH < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		*(_SP->_SP + (_SP->_WIDTH) * (_HEIGHT ) + _WIDTH) = char2int(value);

	}
	else
	{
		printf("\nerror:illegal screen range\n");
	}
}

/******************************
function: show the drawing area ,with ascii encode
input: the DRAW pointer
output: void
******************************/
void drawchar(DRAW *&_SP)
{
	int i=0;

	while (i < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		printf("%c", int2char(*((_SP->_SP) + i)));
		if ((i+1) % (_SP->_WIDTH) == 0)
			printf("\n");
		i++;
	}
}





/******************************
function: show the drawing area ,with smart encode (maybe show error when int number bigger than int2char_const), using drawchar or drawint to avoid this error. 
input: the DRAW pointer
output: void
******************************/
void drawsmart(DRAW *&_SP)
{
	int i=0;
	while (i < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		
			
		if(*((_SP->_SP) + i)>=int2char_const)//==char2int('/') || *((_SP->_SP) + i)==char2int('\\') || *((_SP->_SP) + i)==char2int('|') || *((_SP->_SP) + i)==char2int('-'))// || (*((_SP->_SP) + i)<='z'&&*((_SP->_SP) + i)>='a') || (*((_SP->_SP) + i)<='Z'&&*((_SP->_SP) + i)>='A'))
		{
			//printf("%d", *((_SP->_SP) + i));	
			printf("%c", int2char(*((_SP->_SP) + i)));	
		}
		else if(*((_SP->_SP) + i)!=char2int(' '))
			printf("%d", *((_SP->_SP) + i));	
		else
			printf(" ");
		if ((i+1) % (_SP->_WIDTH) == 0)
			printf("\n");
		i++;
	}
}


/******************************
function: same function as drawsmart
input: the DRAW pointer
output: void
******************************/
void draw(DRAW *&_SP)
{
	drawsmart(_SP);
}



/******************************
function: show the drawing area ,with int encode
input: the _SPvar pointer
output: void
******************************/
void drawint(DRAW *&_SP)
{
	int i=0;
	while (i < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		printf("%d ", (int)*((_SP->_SP) + i));
		if ((i+1) % (_SP->_WIDTH) == 0)
			printf("\n");
		i++;
	}
}

/******************************
function: tranform (x,y) to array element's label ,with int encode
input: the _SPvar pointer, (x,y)
output: label
error: (x,y) is too big for this area
******************************/
int axis2array(DRAW *&_SP,int x,int y)
{
	if(y*x<((_SP->_WIDTH)*(_SP->_HEIGHT)))
		return (_SP->_WIDTH)*(y)+x;
	else
		printf("\nerror:(%d,%d) is too big for this area\n",x,y);
	return -1;
}
/******************************
function: clean the drawing area ,make it blank
input: the _SPvar pointer
output: void
******************************/
void drawclean(DRAW *&_SP)
{
	int i = 0;
	//printf("cleandraw %d %d");
	while (i < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		*((_SP->_SP) + i) = char2int(' ');
	
		i++;
	}
}

/******************************
function: draw a line using '/' or '\' or '|' or '-' or '.',make it straight
input: the _SPvar pointer start point x,y ; end point x,y
output: void
error: (x1,y1) overflow; (x2,y2) overflow;
******************************/
void addline(DRAW *&_SP,int x1,int y1,int x2,int y2)
{
	int i = 0,tmp;
	float k,b;
	int fillchar;	
	//printf("cleandraw %d %d");
	if (x1*y1 < (_SP->_WIDTH) * (_SP->_HEIGHT) && x2*y2 < (_SP->_WIDTH) * (_SP->_HEIGHT))
	{
		if(x1==x2)
		{
			if(y1>y2)
			{
				//tmp=x1;
				//x1=x2;
				//x2=tmp;
				tmp=y1;
				y1=y2;
				y2=tmp;
			}
			
			if((x1-x2)==0 && (y1-y2)==0)
				fillchar=char2int('.');
			else if((x1-x2)==0)
				fillchar=char2int('|');
			for(i=y1;i<=y2;i++)
			{
				*((_SP->_SP) + axis2array(_SP,x1,i))=(int)fillchar;
			}
			
		}
		else
		{
			if(x1>x2)
			{
				tmp=x1;
				x1=x2;
				x2=tmp;
				tmp=y1;
				y1=y2;
				y2=tmp;
			}
	
			if((x1-x2)*(y1-y2)<0)
				fillchar=char2int('/');
			else if((x1-x2)*(y1-y2)>0)
				fillchar=char2int('\\');		
			else if((y1-y2)==0)
				fillchar=char2int('-');
				//printf("%d",fillchar);
			for(i=x1;i<=x2;i++)
			{
				k=(float)(y1-y2)/(x1-x2);
				b=(float)(y2*x1-y1*x2)/(x1-x2);
				*((_SP->_SP) + axis2array(_SP,i,k*i+b)) = (int)fillchar;
				//i++;
			}
		}
		
		
		
		
	}
	else
	{
		if(x1*y1 > (_SP->_WIDTH) * (_SP->_HEIGHT))
			printf("\nError:Start point :(%d,%d) overflow\n",x1,y1);
		if(x2*y2 > (_SP->_WIDTH) * (_SP->_HEIGHT))
			printf("\nError:End point :(%d,%d) overflow\n",x2,y2);
	}
}

/*******************************
function: inital and optimize the size of a painting-paper
input : _WIDTH, _HEIGHT (the argument of the painting range)
output: an _SPvar pointer with the arguments of the painting-paper
*******************************/
DRAW* drawstart(int _WIDTH, int _HEIGHT)
{
	int *screen = (int*)malloc(_WIDTH * _HEIGHT*sizeof(int));
	DRAW* _SP = (DRAW*)malloc(sizeof(DRAW));
	_SP->_SP = screen;	
	_SP->_WIDTH = _WIDTH;
	_SP->_HEIGHT = _HEIGHT;
	drawclean(_SP);
	return _SP;
}

/*******************************
function: close a painting-paper
input : the DRAW pointer
output: void
*******************************/
void drawclose(DRAW *_SP)
{	
	free(_SP->_SP);	
	free(_SP);
}

#endif
