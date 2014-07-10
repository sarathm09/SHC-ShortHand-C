#include<stdio.h>
#include<dir.h>
#include<string.h>

void main(int argc,char *argv[])
{
FILE *f1,*f2;
char c,s[20],code[50000];
int len=0,i;
sprintf(s,"../version_files/bkp/%s_%s.bak",argv[1]);
f1=fopen(s,"r");
f2=fopen(argv[2],"w");
while(!feof(f1))
{	
	fscanf(f1,"%c",&code[len++]);
}
for(i=0;i<len-1;i++)
	fprintf(f2,"%c",code[i]);
}	