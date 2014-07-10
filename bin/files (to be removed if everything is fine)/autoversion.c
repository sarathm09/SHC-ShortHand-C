#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<process.h>
#include<dir.h>
#include<time.h>


void main(int argc, char *argv[]){
	FILE *in,*out,*l;
	char code[50000],filename[20];
	int len=0,i,nauto=0;
	char *c_time_string;
	time_t seconds,current_time;
	seconds = time (NULL);
	in=fopen(argv[1],"r");
	mkdir("../version_files/auto");
	current_time=time(NULL);
	c_time_string=ctime(&current_time);
	sprintf(filename,"../version_files/auto/%s_%d.bak",argv[1],seconds/600);
	out=fopen(filename,"w");
	l=fopen("../version_files/auto/log.txt","a");
	fprintf(l,"Program name : %s \t Time : %s\n",filename,c_time_string);
	while(!feof(in))
			fscanf(in,"%c",&code[len++]);	
	fprintf(out,"\t//Start of Header...\n\n\t\t//Program name : %s\n\t\t//Version number : %s\n\t\t//Version Name : Auto_%s\n\n\t//End of Header...\n",argv[1],c_time_string,c_time_string);
	for(i=0;i<len-1;i++)
		fprintf(out,"%c",code[i]);
	}
