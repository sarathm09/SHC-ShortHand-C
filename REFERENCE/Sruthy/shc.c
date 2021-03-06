#include<process.h>
#include<stdio.h>
#include<ctype.h>
#include<dir.h>
void main(int argc, char *argv[]){
	FILE *key_index,*sh_code,*output_file,*temp,*function_file,*autov,*autovbat;
	char keywords[30][20],user_code[50000],filename[20],c,key_temp[20],*autovstr,*shloc;
	int i,j,k,f,num_of_keywords=0,length_of_keyword[20],size_of_usercode=0,num_of_quotes=0,write_function=0,autovint=0;
	printf("\n\n\t\t\tShortHandConverter (shc) v1.0\n\n\t\tStarting conversion engine...\n\n");
	if(argc<2){
		printf("\n\n\t\tERROR, please specify the input SH code\n\t\t\tCommand Aborted!!!\n ");
		exit(1);
		}
	printf("\n\t\tOpening input ShortHandCode (%s)...",argv[1]);
	sh_code=fopen(argv[1],"r");
	if(sh_code==NULL){
		printf("\n\n\t\tERROR 404, FILE NOT FOUND!!!\n\t\tCommand Aborted!!!\n ");
		exit(1);
		}
	printf("\n\t\tShortHandCode (%s) obtained, started processing...",argv[1]);
	autov=fopen("autoversion","r");
	fscanf(autov,"%d",&autovint);
	if(autovint==1){
		printf("\n\t\tPreparing autoversion files...");
		autovbat=fopen("autov.bat","w");
		sprintf(autovstr,"@echo off\nautoversion %s",argv[1]);
		fprintf(autovbat,autovstr);
		system("autov.bat");
		printf("\n\t\tAuto versioning completed.\n");
		remove("autov.bat");
	}
	mkdir("../output");
	key_index=fopen("dictionary.keywords","r");
	strcpy(filename,"../output/");
	strcat(filename,argv[1]);
	output_file=fopen(filename,"w");



	temp=fopen("temp","w");
	while(!feof(key_index)){
		fscanf(key_index,"%s\n",keywords[num_of_keywords++]);
		}
	for(i=0;i<num_of_keywords+1;i++)
		length_of_keyword[i]=strlen(keywords[i]);
	while(!feof(sh_code))
		fscanf(sh_code,"%c",&user_code[size_of_usercode++]);	


	for(i=1;i<size_of_usercode;i++){
		if(user_code[i]=='/'&&user_code[i+1]=='/'){
			while(user_code[i++]!='\n');
		}		
		if(user_code[i]=='/'&&user_code[i+1]=='*'){
			while(1){
				if(user_code[i]=='*'&&user_code[i+1]=='/')
					break;
				i++;
				}
		}
		if(user_code[i]=='"')
			num_of_quotes++;
		if(num_of_quotes%2==0){
				if(isalpha(user_code[i])&&!(isalpha(user_code[i-1]))){



					for(j=0;j<num_of_keywords;j++){
						f=1;
						for(k=0;k<length_of_keyword[j];k++){
							if(user_code[i+k]!=keywords[j][k]){
								f=0;
								break;
							}
						}
						if(f==1){
							fprintf(temp,"%s\n",keywords[j]);
							keywords[j][0]=keywords[j][1]=keywords[j][2]='*';
						}
					}
				}
			}		
		}


	fclose(temp);
	temp=fopen("temp","r");
	num_of_keywords=-1;
	while(!feof(temp)){
		fscanf(temp,"%s\n",key_temp);
		if(strlen(key_temp)>2)
			strcpy(keywords[++num_of_keywords],key_temp);
		}
	fprintf(output_file,"\n\n\t\t/*\t\t\t Code generated by ShortHand Converter\t\t\t*\n\t\t *\t\t\tA Project By Sruthy, Swetha and Thumssy\t\t\t*/\n\n\n");



	for(j=0;j<size_of_usercode-1;j++){
		if(write_function==1){
			for(i=0;i<=num_of_keywords;i++){
				strcpy(filename,"code/");
				strcat(filename,keywords[i]);
				function_file=fopen(filename,"r");
				fprintf(output_file,"\n//Start of %s() \n\n",keywords[i]);
				while(!feof(function_file)){
					fscanf(function_file,"%c",&c);
					if(!feof(function_file)){
						fprintf(output_file,"%c",c);
						}
					}
				fprintf(output_file,"\n//End of %s() \n\n",keywords[i]);
				fclose(function_file);
				
				}
				write_function=-1;
				j--;
			}
		else{
			if((user_code[j]==' '&&user_code[j+1]!='#'&&write_function==0)||(user_code[j]=='\n'&&user_code[j+1]!='#'&&write_function==0)||(user_code[j]=='\t'&&user_code[j+1]!='#'&&write_function==0)){
				write_function=1;
				}
			fprintf(output_file,"%c",user_code[j]);
			}
		}

		
	fcloseall();
	remove("temp");
	printf("\n\t\tSucess!!! converted code present in output directory.\n\n\t\t\t\tThank You!!!\n");
	system("openOutput.bat");
	}