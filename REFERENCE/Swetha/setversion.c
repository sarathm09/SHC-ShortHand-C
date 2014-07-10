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
	if(argc<3){
		printf("Pleave provide filename and version code.");
		exit(0);
	}
	in=fopen(argv[1],"r");
	mkdir("../version_files/bkp");
	current_time=time(NULL);
	c_time_string=ctime(&current_time);
	sprintf(filename,"../version_files/bkp/%s_%s.bak",argv[1],argv[2]);
	out=fopen(filename,"w");
	l=fopen("../version_files/bkp/log.txt","a");
	fprintf(l,"Program name : %s \t Time : %s\n",filename,c_time_string);
	while(!feof(in))
			fscanf(in,"%c",&code[len++]);	
	fprintf(out,"\t//Start of Header...\n\n\t\t//Program name : %s\n\t\t//Version number : %s\n\n\t//End of Header...\n",argv[1],argv[2]);
	for(i=0;i<len-1;i++)
		fprintf(out,"%c",code[i]);
	system("openVersions.bat");
	}
