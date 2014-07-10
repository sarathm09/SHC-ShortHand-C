#include<stdio.h>
#include<string.h>
#include<process.h>

void printError(){
	printf("\n\tError,set auto version using the syntax setautoversion on/off\n");
	exit(0);
}

void main(int argc,char *argv[])
{
void printError();
FILE *f1;
if(argc<2||argc>2){
	printError();
}
if(strcmp(argv[1],"on")==0){
	printf("\n\tAuto version has been set \n");
	f1=fopen("autoversion","w");
	fprintf(f1,"1");
}
else if(strcmp(argv[1],"off")==0){
	printf("\n\tAuto version has been unset \n");
	f1=fopen("autoversion","w");
	fprintf(f1,"0");
}
else
	printError();
}