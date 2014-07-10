#include<stdio.h>
#include<ctype.h>
#include<dir.h>
FILE *f;
void detect(char s[])
	{
	
	FILE *f1,*f2,*f3,*f4;
	char word[10000];
	int arr[10],array[20],i,sizel=0;
	int a,b,c;
	mkdir("out");
	f1=fopen(s,"r");
	f2=fopen("out/int.txt","w");
	f3=fopen("out/float.txt","w");
	f4=fopen("out/char.txt","w");
	i=0;
	while(!feof(f1))
		fscanf(f1,"%c",&word[sizel++]);
	for(i=1;i<sizel;i++)
		{
		restart:
		if(!isalpha(word[i-1])&&word[i]=='i'&&word[i+1]=='n'&&word[i+2]=='t'&&word[i+3]==' ')
			{
			i+=3;
			while(word[i]!=';')
				{
				if(word[i]==','||word[i]=='=')
					{
					fprintf(f2,"\n");
					if(word[i]!='=') i++;
					}
				if(word[i]==' ')
					i++;
				if(word[i]=='=')
					{
					while(word[i]!=',')
						{
						if(word[i]==';')
							{
							fprintf(f2,"\n");
							goto restart;
							}
						i++;
						}
					i++;
					}
				fprintf(f2,"%c",word[i++]);
				}
			fprintf(f2,"\n");
			}
		if(!isalpha(word[i-1])&&word[i]=='f'&&word[i+1]=='l'&&word[i+2]=='o'&&word[i+3]=='a'&&word[i+4]=='t'&&word[i+5]==' ')
			{
			i+=5;
			while(word[i]!=';')
				{
				if(word[i]==','||word[i]=='=')
					{
					fprintf(f3,"\n");
					if(word[i]!='=') i++;
					}
				if(word[i]==' ')
					i++;
				if(word[i]=='=')
					{
					while(word[i]!=',')
						{
						if(word[i]==';')
							{
							fprintf(f3,"\n");
							goto restart;
							}
						i++;
						}
					i++;
					}
				fprintf(f3,"%c",word[i++]);
				}
			fprintf(f3,"\n");
			}
		if(!isalpha(word[i-1])&&word[i]=='c'&&word[i+1]=='h'&&word[i+2]=='a'&&word[i+3]=='r'&&word[i+4]==' ')
			{
			i+=4;
			while(word[i]!=';')
				{
				if(word[i]==','||word[i]=='=')
					{
					fprintf(f4,"\n");
					if(word[i]!='=') i++;
					}
				if(word[i]==' ')
					i++;
				if(word[i]=='=')
					{
					while(word[i]!=',')
						{
						if(word[i]==';')
							{
							fprintf(f4,"\n");
							goto restart;
							}
						i++;
						}
					i++;
					}
				fprintf(f4,"%c",word[i++]);
				}
			fprintf(f4,"\n");
			}
		}	
		fcloseall();
	}
	int isArray(char s[]) 
	{
	int l=strlen(s),i,index=0;
	for(i=0;i<l;i++)
		{
		index=0;
		if(s[i]=='[')
			while(isalnum(s[++i]))
				index=index*10+s[i]-48;
		}
		return index;
	}

void value()
{
	FILE *f1,*f2,*f3;
	int index,i;
	char word[10000],t[10];
	f1=fopen("out/int.txt","r");
	f=fopen("code/test","w");
	//printf("\nvoid test()\n\t{\n");
	fprintf(f,"#define test {\\\n");
	while(!feof(f1))
		{
		fscanf(f1,"%s",word);
		if(feof(f1))
			break;
		index=isArray(word);
		if(index<1)
			fprintf(f,"\tprintf(\"\\n%s = %%d\",%s);\\\n",word,word);
		else 
			{
			for(i=0;word[i]!='[';i++)
				t[i]=word[i];
			t[i]='\0';
			fprintf(f,"\tfor(i=0;i<%d;i++)\\\n\t\tprintf(\"\\n%s = %%d\",%s[i]);\\\n",index,t,t);
			}
		}
	f2=fopen("out/char.txt","r");
	while(!feof(f2))
		{
		fscanf(f2,"%s",word);
		if(feof(f2))
			break;
		index=isArray(word);
		if(index<1)
			fprintf(f,"\tprintf(\"\\n%s = %%c\",%s);\\\n",word,word);
		else 
			{
			for(i=0;word[i]!='[';i++);
			word[i]='\0';
			
				t[i]=word[i];
				fprintf(f,"\tfor(i=0;i<%d;i++)\\\n\t\tprintf(\"\\n%s = %%c\",%s[i]);\\\n",index,t,word);
			}
		}
	f3=fopen("out/float.txt","r");
	while(!feof(f3))
		{
		fscanf(f3,"%s",word);
		if(feof(f3))
			break;
		index=isArray(word);
		if(index<1)
			fprintf(f,"\tprintf(\"\\n%s = %%f\",%s);\\\n",word,word);
		else 
			{
			for(i=0;word[i]!='[';i++)
			t[i]='\0';
			
				t[i]=word[i];
				fprintf(f,"\t\tfor(i=0;i<%d;i++)\\\n\t\tprintf(\"\\n%s = %%f\",%s[i]);\\\n",index,t,t);
			}
		}
	fprintf(f,"\tgetch();\\\n\t}");
	//printf("\n\t}");
}
void main(int argc, char *argv[])
{
detect(argv[1]);
value();
}
