#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<dir.h>

int np=0,maxx,maxy,nPolyType[5]={0,0,0,0,0},ttx,tty;
char pname[30],*gen_fname,tempfname[20];


struct ppty{
    int ptype,cords[2],border;
}p[100],curr;

int ncords=0,nf[5000][4];


void mouseposi(int *x,int *y,int *c){
    union REGS in,out;
    in.x.ax=01;
    int86(0x33,&in,&out);
    in.x.ax=03;
    int86(0x33,&in,&out);
    *x=out.x.cx;
    *y=out.x.dx;
    *c=out.x.bx;
}

void drscreen(){
	void display();
	void menu();
	void freehand();
	void showGrid(int x, int y,int drawing);
	int x,y,cl,tx,ty,r,fh=0;
	char c,buffer[50];
	while(c!='`')
	    {
	    cleardevice();
	    display();
	    if(nPolyType[4]>0)
			freehand();
	    mouseposi(&x,&y,&cl);
	    showGrid(x,y,0);
	    switch(curr.ptype)
	    {
	    case 1:
		if(cl){
			tx=x;ty=y;
			while(cl)
				{
				cleardevice();
				display();
				if(nPolyType[4]>0)
					freehand();
				setcolor(curr.border);
				mouseposi(&x,&y,&cl);
				setcolor(12);
				showGrid(tx,ty,1);
				setcolor(curr.border);
				rectangle(tx,ty,x,y);
				sprintf(buffer,"(%d,%d)",tx,ty);
				outtextxy(tx-10,ty-10,buffer);
				sprintf(buffer,"(%d,%d)",x,y);
				outtextxy(x,y-5,buffer);
				delay(30);
				}
			p[np+1].cords[0]=tx;
			p[np+1].cords[1]=ty;
			p[np].cords[0]=x;
			p[np].cords[1]=y;
			p[np].ptype=p[np+1].ptype=curr.ptype;
			p[np].border=p[np+1].border=curr.border;
			p[np+1].ptype=p[np].ptype=1;
			np+=2;
			nPolyType[1]++;
			setcolor(15);
			}
		break;
	    case 2:
		if(cl){
			tx=x;ty=y;
			while(cl)
				{
				cleardevice();
				display();
				if(nPolyType[4]>0)
					freehand();
				setcolor(12);
				showGrid(x,y,1);
				setcolor(curr.border);
				mouseposi(&x,&y,&cl);
				r=sqrt(pow((x-tx),2)+pow((y-ty),2));
				circle(tx,ty,r);
				sprintf(buffer,"(%d,%d)",tx,ty);
				outtextxy(tx,ty,buffer);
				sprintf(buffer,"radius : %d",r);
				outtextxy(x+5,ty,buffer);
				delay(30);
				}
			p[np+1].cords[0]=tx;
			p[np+1].cords[1]=ty;
			p[np].cords[0]=p[np].cords[1]=r;
			p[np].ptype=p[np+1].ptype=curr.ptype;
			p[np].border=p[np+1].border=curr.border;
			np+=2;
			nPolyType[2]++;
			setcolor(15);
			}
		break;
	    case 3:
		if(cl){
			tx=x;ty=y;
			while(cl)
				{
				cleardevice();
				display();
				if(nPolyType[4]>0)
					freehand();
				setcolor(12);
				showGrid(tx,ty,1);
				setcolor(curr.border);
				mouseposi(&x,&y,&cl);
				line(tx,ty,x,y);
				sprintf(buffer,"(%d,%d)",tx,ty);
				outtextxy(tx-10,ty-10,buffer);
				sprintf(buffer,"(%d,%d)",x,y);
				outtextxy(x,y+15,buffer);
				delay(30);
				}
			p[np+1].cords[0]=tx;
			p[np+1].cords[1]=ty;
			p[np].cords[0]=x;
			p[np].cords[1]=y;
			p[np].ptype=p[np+1].ptype=curr.ptype;
			p[np].border=p[np+1].border=curr.border;
			np+=2;
			nPolyType[3]++;
			setcolor(15);
			}
		break;
	    case 4:
		nf[ncords][2]=1;
		fh=0;
		ttx=x;tty=y;
		while(cl)
			{
			cleardevice();
			display();
			freehand();
			tx=x;ty=y;
			fh=1;
			mouseposi(&x,&y,&cl);
			if(x!=tx||y!=ty){
				ncords++;
				nf[ncords][0]=x;
				nf[ncords][1]=y;
				nf[ncords][2]=0;
				nf[ncords][3]=curr.border;
				tx=x;
				ty=y;
				}
			sprintf(buffer,"(%d,%d)",ttx,tty);
			outtextxy(ttx-10,tty-10,buffer);
			sprintf(buffer,"(%d,%d)",nf[ncords][0],nf[ncords][1]);
			outtextxy(nf[ncords][0]-10,nf[ncords][1]-10,buffer);
			delay(20);
			}
		if(fh)
			nPolyType[4]++;
		break;

	    }
	    if(kbhit()){
		c=getch();
		if(c=='m')
			menu();
		else if(c=='`')
			exit(0);
		}
	    delay(70);
	 }
       exit(0);
    }

void showGrid(int x, int y, int drawing){
	int i,j,c,tx,ty;
	if(drawing==1){
		mouseposi(&tx,&ty,&c);
		setcolor(3);
		if(abs(getmaxx()-tx-x)<2){
			setlinestyle(DASHED_LINE,1,1);
			line(tx,0,tx,getmaxy());
			line(getmaxx()-x,0,getmaxx()-x,getmaxy());
			}
		if(abs(getmaxy()-ty-y)<2){
			setlinestyle(DASHED_LINE,1,1);
			line(0,ty,getmaxx(),ty);
			line(0,getmaxy()-y,getmaxx(),getmaxy()-y);
			}
		}
	mouseposi(&x,&y,&c);
	if((np>0||(np==0&&c!=0))&&(x!=0&&y!=0&&x!=getmaxx()&&y!=getmaxy())){
		for(i=0;i<=np;i++){
			if(p[i].ptype!=4){
			if(abs(getmaxx()-p[i].cords[0]-x)<2||abs(p[i].cords[0]-x)<2){
				setlinestyle(DASHED_LINE,1,1);
				line(x,0,x,getmaxy());
				line(getmaxx()-x,0,getmaxx()-x,getmaxy());
			}
			if(abs(getmaxy()-p[i].cords[1]-y)<2||abs(p[i].cords[1]-y)<2){
				setlinestyle(DASHED_LINE,1,1);
				line(0,y,getmaxx(),y);
				line(0,getmaxy()-y,getmaxx(),getmaxy()-y);
			}
			}
		setlinestyle(SOLID_LINE,1,1);
		}
	}
	if(x==getmaxx()/2){
		setcolor(14);
		setlinestyle(DASHED_LINE,1,1);
		line(x,0,x,getmaxy());
		}
	if(y==getmaxy()/2){
		setcolor(14);
		setlinestyle(DASHED_LINE,1,1);
		line(0,y,getmaxx(),y);
		}
}

void freehand(){
	int i=0;
	char buffer[50];
	while(i<ncords){

	setcolor(nf[i][3]);
	if(nf[i][2]==0&&nf[i+1][2]==0)
		line(nf[i][0],nf[i][1],nf[i+1][0],nf[i+1][1]);
		i++;
	}


	}

void display(){
int i=np-1,buffer[50],x,y,c;
while(i>0)
	{
	setcolor(p[i].border);
	switch(p[i].ptype)
	{
		case 1:
		 rectangle(p[i].cords[0],p[i].cords[1],p[i-1].cords[0],p[i-1].cords[1]);
		 i-=2;
		 break;
		case 2:
		 circle(p[i].cords[0],p[i].cords[1],p[i-1].cords[0]);
		 i-=2;
		 break;
		case 3:
		 line(p[i].cords[0],p[i].cords[1],p[i-1].cords[0],p[i-1].cords[1]);
		 i-=2;
		 break;
	}
	}
mouseposi(&x,&y,&c);
setcolor(12);
showGrid(x,y,0);
setcolor(15);
}

void generate(char *s){
	FILE *f,*fp,*f1,*f2;
	int np=0,ncords=0,nf[5000][4],nPolyType[5]={0,0,0,0,0};
	int pr,i=0,j=0,k,npt,ncor=0,totimg,typenum,border,x1,x2,y1,y2,r;
	char type[20],id[3],fname[20],msg[20],pname[20],c;
	f=fopen(s,"r");
	f1=fopen("start","r");
	f2=fopen("end","r");
	fscanf(f,"<project name=\' %s \' num_of_imgs=\' %d \'>",pname,&totimg);
	sprintf(fname,"%s/%s_gen.c",pname,pname);
	fp=fopen(fname,"w");
	while(!feof(f1)){
		fscanf(f1,"%c",&c);
		if(feof(f2))
			break;
		fprintf(fp,"%c",c);
		}
	fprintf(fp,"\nvoid init()\n\t{");
	fprintf(fp,"\n\tstrcpy(pname,\"%s\");\n\ttotimg=%d;\n",pname,totimg);
	while(i<totimg)
		{
		fprintf(fp,"\n\t");
		fscanf(f,"\n\t<image>");
		fscanf(f,"\n\t\t<type> %s </type>",type);
		fscanf(f,"\n\t\t<typenum> %d </typenum>",&typenum);
		fscanf(f,"\n\t\t<id> %s </id>",id);
		fscanf(f,"\n\t\t<border> %d </border>",&border);
		fprintf(fp,"strcpy(p[%d].type,\"%s\");\n\tp[%d].ptype=%d;\n\tstrcpy(p[%d].id,\"%s\");\n\tp[%d].border=%d;\n\t",i,type,i,typenum,i,id,i,border);
		switch(typenum)
			{
			case 1:
			case 3:
				fscanf(f,"\n\t\t<cords>");
				fscanf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",&x1,&y1);
				fscanf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",&x2,&y2);
				fscanf(f,"\n\t\t</cords>");
				fscanf(f,"\n\t</image>");
				fprintf(fp,"p[%d].x1=%d;\t\tp[%d].x2=%d;\n\tp[%d].y1=%d;\t\tp[%d].y2=%d;\n\t",i,x1,i,x2,i,y1,i,y2);
				fprintf(fp,"p[%d].start=0;\n\tp[%d].stop=0;\n\tp[%d].mover=0;\tp[%d].mclick=0;\n\t",i,i,i,i);
			break;
			case 2:
				fscanf(f,"\n\t\t<cords>");
				fscanf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",&x1,&y1);
				fscanf(f,"\n\t\t\t<r> ( %d ) </r>",&r);
				fscanf(f,"\n\t\t</cords>");
				fscanf(f,"\n\t</image>");
				fprintf(fp,"p[%d].x1=%d;\tp[%d].y1=%d;\n\tp[%d].r=%d;\n\t",i,x1,i,y1,i,r);
				fprintf(fp,"p[%d].start=0;\n\tp[%d].stop=0;\n\tp[%d].mover=0;\tp[%d].mclick=0;\n\t",i,i,i,i);
			break;
			case 4:
				fscanf(f,"\n\t\t<ncords> %d </ncords>",&ncor);
				fprintf(fp,"p[%d].start=%d;\n\tp[%d].stop=%d;\n\t",i,j,i,j+ncor-1);
				fscanf(f,"\n\t\t<cords>");
				k=0;
				while(k<ncor){
					fscanf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",&x1,&y1);
					fprintf(fp,"nf[%d][0]=%d;\t\tnf[%d][1]=%d;\n\t",j,x1,j,y1);
					k++;j++;
					}
				fscanf(f,"\n\t\t</cords>");
				fscanf(f,"\n\t</image>");
				fprintf(fp,"p[%d].mover=0;\tp[%d].mclick=0;\n\t",i,i,i,i);
			break;
			}

		i++;
		}
	fscanf(f,"\n</project>");
	fclose(f);
	fprintf(fp,"}\n");
	while(!feof(f2)){
		fscanf(f2,"%c",&c);
		if(feof(f2))
			break;
		fprintf(fp,"%c",c);
		}
	fcloseall();
	}


void save(){
	FILE *f;
	int pr=nPolyType[1]+nPolyType[2]+nPolyType[3];
	int i,j,idnum[4]={0},npt,ncor=0,c;
	char type[20],id[3],fname[20],msg[20];
	mkdir(pname);
	sprintf(fname,"%s/%s.xml",pname,pname);
	f=fopen(fname,"w");
	strcpy(gen_fname,fname);
	fprintf(f,"<project name=\' %s \' num_of_imgs=\' %d \'>",pname,(pr+nPolyType[4]));
	for(i=0;i<(pr+pr);i++)
		{
		switch(p[i].ptype)
			{
			case 1:
			fprintf(f,"\n\t<image>");
			fprintf(f,"\n\t\t<type> rectangle </type>");
			fprintf(f,"\n\t\t<typenum> 1 </typenum>");
			fprintf(f,"\n\t\t<id> r%d </id>",idnum[p[i].ptype]++);
			fprintf(f,"\n\t\t<border> %d </border>",p[i+1].border);
			fprintf(f,"\n\t\t<cords>");
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",p[i+1].cords[0],p[i+1].cords[1]);
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",p[i].cords[0],p[i].cords[1]);
			fprintf(f,"\n\t\t</cords>");
			fprintf(f,"\n\t</image>");
			break;
			case 2:
			fprintf(f,"\n\t<image>");
			fprintf(f,"\n\t\t<type> circle </type>");
			fprintf(f,"\n\t\t<typenum> 2 </typenum>");
			fprintf(f,"\n\t\t<id> c%d </id>",idnum[p[i].ptype]++);
			fprintf(f,"\n\t\t<border> %d </border>",p[i+1].border);
			fprintf(f,"\n\t\t<cords>");
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",p[i+1].cords[0],p[i+1].cords[1]);
			fprintf(f,"\n\t\t\t<r> ( %d ) </r>",p[i].cords[0]);
			fprintf(f,"\n\t\t</cords>");
			fprintf(f,"\n\t</image>");
			break;
			case 3:
			fprintf(f,"\n\t<image>");
			fprintf(f,"\n\t\t<type> line </type>");
			fprintf(f,"\n\t\t<typenum> %d </typenum>",p[i].ptype);
			fprintf(f,"\n\t\t<id> l%d </id>",idnum[p[i].ptype]++);
			fprintf(f,"\n\t\t<border> %d </border>",p[i+1].border);
			fprintf(f,"\n\t\t<cords>");
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",p[i+1].cords[0],p[i+1].cords[1]);
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",p[i].cords[0],p[i].cords[1]);
			fprintf(f,"\n\t\t</cords>");
			fprintf(f,"\n\t</image>");
			break;
			}
			i++;
		}
	if(nPolyType[4]>0){
	i=1;
	npt=0;
	while(i<ncords){
		j=i;
		ncor=0;
		while(nf[j][2]!=1)
			{j++;ncor++;}
		fprintf(f,"\n\t<image>");
		fprintf(f,"\n\t\t<type> freehand </type>");
		fprintf(f,"\n\t\t<typenum> 4 </typenum>");
		fprintf(f,"\n\t\t<id> f%d </id>",npt);
		fprintf(f,"\n\t\t<border> %d </border>",nf[i][3]);
		fprintf(f,"\n\t\t<ncords> %d </ncords>",ncor);
		fprintf(f,"\n\t\t<cords>");
		while(nf[i][2]!=1)
			{
			fprintf(f,"\n\t\t\t<xy> ( %d,%d ) </xy>",nf[i][0],nf[i][1]);
			i+=1;
			}
		fprintf(f,"\n\t\t</cords>");
		fprintf(f,"\n\t</image>");
		i++;
		npt++;
		}
		}
	fprintf(f,"\n</project>");
	fclose(f);
	fclose(f);
	sprintf(msg,"Details saved to %s.",fname);
	outtextxy(maxx/2-130,10,msg);
	delay(1000);
       //	c=getch();
       //	if(c=='`')
 //		exit(0);
}

void menu(){
	char temp[2],c;
	int i,col=1;
	setfillstyle(1,15);

	//OUTER RECTANGLES FOR R,C,L,F, SAVE AND GEN
	setcolor(15);
	rectangle(10,maxy-27,35,maxy-5);
	rectangle(37,maxy-27,62,maxy-5);
	rectangle(64,maxy-27,89,maxy-5);
	rectangle(91,maxy-27,116,maxy-5);

	//Rectangle for DELETE
	rectangle(457,maxy-27,513,maxy-5);
	//Rectangles for save and generate
	rectangle(515,maxy-27,553,maxy-5);
	rectangle(555,maxy-27,625,maxy-5);

	//INNER RECTANGLES FOR R,C,L,F, SAVE AND GEN
	setcolor(10);
	outtextxy(12,maxy-20,"r");
	outtextxy(39,maxy-20,"c");
	outtextxy(66,maxy-20,"l");
	outtextxy(93,maxy-20,"f");

	//SHAPES
	setcolor(15);
	rectangle(22,maxy-25,33,maxy-7);

	circle(55,maxy-17,5);
	line(76,maxy-10,85,maxy-22);

	line(110,maxy-22,103,maxy-21);
	line(110,maxy-21,101,maxy-19);
	line(110,maxy-19,100,maxy-17);
	line(110,maxy-16,102,maxy-15);
	line(110,maxy-15,95,maxy-12);
	line(110,maxy-11,98,maxy-19);
	line(110,maxy-11,96,maxy-10);

	setcolor(10);
	outtextxy(462,maxy-20,"D");
	outtextxy(519,maxy-20,"S");
	outtextxy(558,maxy-20,"G");
	setcolor(15);
	outtextxy(470,maxy-20,"ELETE");
	outtextxy(526,maxy-20,"AVE");
	outtextxy(567,maxy-20,"ENERATE");


	for(i=150;i<400;)
	    {
	    setcolor(15);
	    rectangle(i-3,maxy-27,i+14,maxy-5);
	    setcolor(col);
	    rectangle(i,maxy-24,i+11,maxy-8);
	    if(col<10)
		    sprintf(temp,"%d",col);
	    else
		    sprintf(temp,"%c",(col+107));
	    outtextxy(i+2,maxy-20,temp);
	    col++;
	    i+=17;
	    }
	c=getch();
	if(c!='m'||c!='M')
	    cleardevice();
	switch(c){
	    case '1':curr.border=1;
			break;
	    case '2':curr.border=2;
			break;
	    case '3':curr.border=3;
			break;
	    case '4':curr.border=4;
			break;
	    case '5':curr.border=5;
			break;
	    case '6':curr.border=6;
			break;
	    case '7':curr.border=7;
			break;
	    case '8':curr.border=8;
			break;
	    case '9':curr.border=9;
			break;
	    case 'u':curr.border=10;
			break;
	    case 'v':curr.border=11;
			break;
	    case 'w':curr.border=12;
			break;
	    case 'x':curr.border=13;
			break;
	    case 'y':curr.border=14;
			break;
	    case 'z':curr.border=15;
			break;
	    case 'r':curr.ptype=1;
			break;
	    case 'c':curr.ptype=2;
			break;
	    case 'l':curr.ptype=3;
			break;
	    case 'f':curr.ptype=4;
			break;
	    case 'd':if(curr.ptype==4)
			{
			if(ncords>0)
				ncords-=5;
			else
				nPolyType[4]--;
			}
		     else
			np-=2;
			break;
	    case 's':save();
			break;
	    case 'g':
				save();
				generate(gen_fname);
			break;
	    }

	}


void newpoly(){
    char temp[20];
    cleardevice();
    outtextxy(270,130,"New Project");
    outtextxy(245,150,"GRAPHICS GENERATOR");
    line(230,160,400,160);
    line(230,162,400,162);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    rectangle(7,7,getmaxx()-7,getmaxy()-7);
    outtextxy(175,258,"Enter Project Name : ");
    scanf("%s",pname);
    sprintf(temp,"Starting project %s...",pname);
    outtextxy(220,300,temp);
	delay(1000);
    curr.border=15;
    curr.ptype=1;
    drscreen();

}

void genscreen(){
    char temp[20];
    void stscreen();
    cleardevice();
    outtextxy(245,150,"GRAPHICS GENERATOR");
    line(230,160,400,160);
    line(230,162,400,162);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t");
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    rectangle(7,7,getmaxx()-7,getmaxy()-7);
    outtextxy(175,258,"Enter the name of the XML : ");
    scanf("%s",pname);
    generate(pname);
    cleardevice();
    outtextxy(100,30,"Code generated... Press enter to continue");
    getch();
    cleardevice();
    stscreen();
    }

void stscreen(){

    int x,y,c;
    char sel;
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    rectangle(7,7,getmaxx()-7,getmaxy()-7);
    rectangle(120,120,getmaxx()-120,180);
    rectangle(120,190,getmaxx()/2-1,getmaxy()-100);
    rectangle(getmaxx()/2+1,190,getmaxx()-120,getmaxy()-100);
    rectangle(120,getmaxy()-70,getmaxx()-120,getmaxy()-90);

    outtextxy(280,130,"ShortHand");
    outtextxy(245,150,"GRAPHICS GENERATOR");
    line(230,160,400,160);
    line(230,162,400,162);

    line(172,216,260,216);
    outtextxy(175,220,"CREATE NEW");
    line(172,231,260,231);

    outtextxy(145,260,"Start from scratch,");
    outtextxy(135,275,"draw polygons and then");
    outtextxy(165,290,"generate code");
    outtextxy(180,330,"Press \"n\"");

    line(345,216,490,216);
    outtextxy(350,220,"GENERATE FROM XML");
    line(345,231,490,231);

    outtextxy(340,260,"Use an earlier saved");
    outtextxy(340,275,"POLYGON XML file and");
    outtextxy(365,290,"Generate C code");
    outtextxy(380,330,"Press \"g\"");

    setfillstyle(10, getmaxcolor());
    outtextxy(155,395,"Press 'n' or 'g' to continue, 'q' to quit");
    while(sel!='n'||sel!='g')
    {
    if(sel=='n'){
	bar(125,getmaxy()-110,getmaxx()/2-5,getmaxy()-120);
    delay(1000);
	newpoly();
	}
    else if(sel=='g'){
	bar(getmaxx()/2+5,getmaxy()-110,getmaxx()-125,getmaxy()-120);
	delay(1000);
	genscreen();
	}
    sel=getch();
    if(sel=='q')
	exit(0);
    }

}

void main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"c:\\TurboC3\\BGI");
    maxx=getmaxx();
    maxy=getmaxy();
    stscreen();
    drscreen();
    getch();
}