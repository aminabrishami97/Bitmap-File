#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct
{
	char BMPSIGNATURE[2];/*Starts from Offset 0x00 and ends at Offset 0x01 BM*/
	unsigned long int BMPSIZE; /*Starts from Offset 0x02*/
	unsigned long int BitmapDataOffset; /*Offset Where Bitmap DATA begins and the Value is 54*/
	unsigned long int BMPNUMOFDIBHEADER; /*Starts from Offset 0x0E the Value is 40*/
	unsigned long int BMPWIDTH;/*Starts from Offset 0x12*/
    unsigned long int BMPHEIGHT;/*Starts from Offset 0x16*/
	short int BMPNUMOFPLANES; /*Starts from Offset 0x1A* the value is 1*/
	short int BMPCOLORDEPTH; /*Starts from Offset 0x1C* the Value is 24*/
	short int PPM;
}BITMAP;

typedef struct
{
	char RED;
	char GREEN;
	char BLUE;
	
}RGB;

int main()
{
	int WIDTH=1024;
	int HEIGHT=640;
	unsigned long int Area;
	Area=WIDTH*HEIGHT;
	RGB Data[Area];
	BITMAP BMP;
	for(unsigned int y=0;y<HEIGHT;y++)
	{
		for(unsigned int x=0;x<WIDTH;x++)
		{
			Data[y*WIDTH + x].BLUE=0;
			Data[y*WIDTH + x].GREEN=0;
			Data[y*WIDTH + x].RED=0;
		}
	}
	for(unsigned int y=100;y<HEIGHT-100;y++)
	{
		for(unsigned int x=100;x<WIDTH-100;x++)
		{
			Data[y*WIDTH + x].BLUE=255;
			Data[y*WIDTH + x].GREEN=0;
			Data[y*WIDTH + x].RED=0;
		}
	}
	
	
unsigned long int unused=0;
unsigned long int Filesize;
Filesize=54 + 4*Area;
FILE *BM;
BM=fopen("Mybmp.bmp","wb");
BMP.BMPSIGNATURE[0]='B';
BMP.BMPSIGNATURE[1]='M';
BMP.BMPSIZE=Filesize;
BMP.BitmapDataOffset=54;
BMP.BMPNUMOFDIBHEADER=40;
BMP.BMPWIDTH=WIDTH;
BMP.BMPHEIGHT=HEIGHT;
BMP.BMPNUMOFPLANES=1;
BMP.BMPCOLORDEPTH=24;
BMP.PPM=0;
fwrite(&BMP.BMPSIGNATURE[0],1,1,BM);
fwrite(&BMP.BMPSIGNATURE[1],1,1,BM);
fwrite(&BMP.BMPSIZE,1,sizeof(unsigned long int),BM);
fwrite(&unused,1,sizeof(unsigned long int),BM);
fwrite(&BMP.BitmapDataOffset,1,sizeof(unsigned long int),BM);
fwrite(&BMP.BMPNUMOFDIBHEADER,1,sizeof(unsigned long int),BM);
fwrite(&BMP.BMPWIDTH,1,sizeof(unsigned long int),BM);
fwrite(&BMP.BMPHEIGHT,1,sizeof(unsigned long int),BM);
fwrite(&BMP.BMPNUMOFPLANES,1,sizeof(short int),BM);
fwrite(&BMP.BMPCOLORDEPTH,1,sizeof(short int),BM);
for(int i=1;i<=24;i++)putc(0,BM);
for(unsigned int y=0;y<HEIGHT;y++)
{
	for(unsigned int x=0;x<WIDTH;x++)
	{
		putc(Data[y*WIDTH + x].BLUE,BM);
		putc(Data[y*WIDTH + x].GREEN,BM);
		putc(Data[y*WIDTH + x].RED,BM);
		
		
	}
}
fclose(BM);
return 0;	
}
