// Virtually infine snake

// Header Files
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
#include<conio.h>
#include<string.h>

// Macro List
#define LIFE 3
#define MAX 300
#define MIN 5
#define SIZE 20

// Structures
struct RECT
{
	int x[2],y[2];
};
struct SNAKE
{
	RECT r[MAX];								// Snake Body
	char dir;									// Direction of head
	char name[20];
	int dead;									// =1 if dead else =0
	int life;									// number of lives
	int kill;									// no of mice killed
	int level;
	int len;
	int diff;									// Difficulty level
	int move;									// numebr of moves (4 bonus)
	int type;								// type (bounded and unbounded
	RECT m;											// Mouse
	RECT bon;									// Bonus
}*s;
struct score
{
	int score;
	char name[20];
	char level[8];
	int day,mon,year;
};

// FUNCTION PROTOTYPE LIST
void disp(int x);								// Diplays The Snake | color   =1 =>draw, =2 =>erase
void makesnk();									// Allocates Memory for SNAKE and intialises
int maxx();										// Returns Max x-co-ordinate
int maxy();										// Returns Max y-co-ordinate
int min();										// Returns Min x,y-co-ordinate
void show(RECT *r);								// Displays a RECT
void gen();										// Generates Mouse
void print(int color);							// Prints info like level,life and kills | color=1->show, =0->erase
void next();									// Takes the next step in accordance with the direction
void ckill();									// Checks if the mouse is killed if yes then modifies length,etc
int check();									// Checks if the next step will result in death
void move();									// Makes various checks and Makes the Snake appear to move
void clear();									// Clears Screen
void initsnk();									// Initialises Snake after death
void score();									// Displayes High Scores
// FUNCTIONs
void print(int color)
{
	char ki[4],lev[2],li[2];
	li[0]=s->life+'0';
	li[1]='\0';
	lev[0]=s->level+'0';
	lev[1]='\0' ;
	ki[2]=s->kill%10+'0';
	ki[1]=(s->kill/10)%10+'0';
	ki[0]=((s->kill/10)/10)%10+'0';
	ki[3]='\0';
	if(color){
		setcolor(GREEN);
	}
	else{
		setcolor(BLACK);
	}
	outtextxy(getmaxx()-100,80,li);
	outtextxy(getmaxx()-100,100,ki);
	outtextxy(getmaxx()-100,120,lev);
}

void clear(int x)			// Clears Screen
{
	int i,j,a,b;
	if(!x){
		a=b=x;
	}
	else
	{
		a=3;
		b=4;
	}
	for(i=(maxx()+min())/2;i>=min();i--)
	{
		for(j=i;j<=(maxx()+min())/2;j++)
		{
			putpixel(j,j-i+min(),a);
			putpixel(maxx()+min()-j,maxx()-j+i,a);
			putpixel(j-i+min(),maxx()+min()-j,a);
			putpixel(maxx()-j+i,j,a);
			putpixel(i,j,b);
			putpixel(j,maxx()+min()-i,b);
			putpixel(maxx()+min()-i,maxx()+min()-j,b);
			putpixel(maxx()+min()-j,i,b);
		}
	}
}

int maxy()
{
	return((getmaxy()/SIZE-(s->diff-1)*2)*SIZE);
}
int maxx()
{
	return(maxy());
}
int min()
{
	return(SIZE+(s->diff-1)*SIZE*4);
}

void show(RECT r)
{
	rectangle(r.x[0]+SIZE/10,r.y[0]+SIZE/10,r.x[1]-SIZE/10,r.y[1]-SIZE/10);
}



void gen()
{
	int i,j,a,flag=0;
	while(!flag)
	{
		a=clock()*100;
		flag=1;
		i=((a*rand())%(getmaxx()/SIZE))*SIZE;
		j=((a*rand())%(getmaxy()/SIZE))*SIZE;
		for(a=0;a<s->len;a++){
			if(i==s->r[a].x[0] && j==s->r[a].y[0]){
				flag=0;
			}
			else if(j<min() || i<min() ||j>maxy()-SIZE||i>maxx()-SIZE){
				flag=0;
			}
		}
	}
	s->m.x[0]=i;s->m.y[0]=j;s->m.x[1]=i+SIZE;s->m.y[1]=j+SIZE;
	flag=0;
	if(s->kill%15==0 && s->kill!=0 && s->move>20)
	{
		while(!flag)
		{
			a=clock()*100;
			flag=1;
			i=((a*rand())%(getmaxx()/SIZE))*SIZE;
			j=((a*rand())%(getmaxy()/SIZE))*SIZE;
			for(a=0;a<s->len;a++){
				if((i==s->r[a].x[0] && j==s->r[a].y[0])||(i==s->m.x[0]&&j==s->m.y[0])){
					flag=0;
				}
				else if(j<min() || i<min() ||j>maxy()-SIZE||i>maxx()-SIZE){
					flag=0;
				}
			}
			s->move=0;
		}
		s->bon.x[0]=i;s->bon.y[0]=j;s->bon.x[1]=i+SIZE;s->bon.y[1]=j+SIZE;
	}
}


void ckill()
{
	if(s->bon.x[0]==s->r[0].x[0] && s->bon.y[0]==s->r[0].y[0] && s->move<21)
	{
		print(0);
		s->kill=s->kill+5;
		if(s->kill%15<4){
			s->move=21;
		}
		print(1);
	}
	if(s->m.x[0]==s->r[0].x[0] && s->m.y[0]==s->r[0].y[0])
	{
		print(0);
		s->kill++;
		s->len++;
		if(s->len%15==0)
		{
			disp(0);
			print(0);
			s->level++;
			print(1);
		}
		print(1);
		gen();
	}
}



int check()
{
	int a,b,i;
	a=s->r[0].x[0];
	b=s->r[0].y[0];
	switch (s->dir)
	{
	case 'u':
		b=b-SIZE;
		for(i=1;i<s->len;i++){
			if(s->r[i].x[0] == a && s->r[i].y[0] == b)
			{s->dead=1;return 0;}
		}
		break;
	case 'd':
		b=b+SIZE;
		for(i=1;i<s->len;i++){
			if(s->r[i].x[0] == a && s->r[i].y[0] == b)
			{s->dead=1;return 0;}
		}
		break;
	case 'l':
		a=a-SIZE;
		for(i=1;i<s->len;i++){
			if(s->r[i].x[0] == a && s->r[i].y[0] == b)
			{s->dead=1;return 0;}
		}
		break;
	case 'r':
		a=a+SIZE;
		for(i=1;i<s->len;i++){
			if(s->r[i].x[0] == a && s->r[i].y[0] == b)
			{s->dead=1;return 0;}
		}
		break;
	}
	return 1;
}

void next()
{
	int i,j;
	for(i=s->len-2;i>=0;i--){
		s->r[i+1]=(s->r[i]);
	}
	s->move++;
	switch (s->dir)
	{
	case 'u':
		if(check())
		{
			if(s->r[0].y[0] < min()+SIZE)
			{
				if(s->type!=2){
					s->dead=1;
				}
				else
				{
					s->r[0].y[0]=maxy();
					s->r[0].y[1]=maxy()+SIZE;
				}
			}
			s->r[0].y[0]-=SIZE;
			s->r[0].y[1]-=SIZE;
		}
		else
		{
			s->dead=1;
		}

		break;
	case 'd':
		if(check())
		{
			if(s->r[0].y[0]>maxy()-2*SIZE)
			{
				if(s->type!=2){
					s->dead=1;
				}
				else
				{
					s->r[0].y[0]=min()-SIZE;
					s->r[0].y[1]=min();
				}
			}
			s->r[0].y[0]+=SIZE;
			s->r[0].y[1]+=SIZE;
		}
		else
		{
			s->dead=1;
		}

		break;
	case 'l':
		if(check())
		{
			if(s->r[0].x[0] < min()+SIZE)
			{
				if(s->type!=2){
					s->dead=1;
				}
				else
				{
					s->r[0].x[0]=maxx();
					s->r[0].x[1]=maxx()+SIZE;
				}
			}
			s->r[0].x[0]-=SIZE;
			s->r[0].x[1]-=SIZE;
		}
		else
		{
			s->dead=1;
		}

		break;
	case 'r':
		if(check())
		{
			if(s->r[0].x[0] >maxx()-2*SIZE)
			{
				if(s->type!=2){
					s->dead=1;
				}
				else
				{
					s->r[0].x[0]=min()-SIZE;
					s->r[0].x[1]=min();
				}
			}
			s->r[0].x[0]+=SIZE;
			s->r[0].x[1]+=SIZE;
		}
		else
		{
			s->dead=1;
		}
		break;
	}
	if(s->dead){
		outtextxy(240,200,"DEAD!!");
	}
}


void disp(int color)
{
	int i,j;
	print(1);
	setcolor(MAGENTA);
	show(s->m);
	if(s->move<21 && color){
		setcolor(WHITE);
	}
	else{
		setcolor(BLACK);
	}
	show(s->bon);
	setcolor(BROWN);
	rectangle(min(),min(),maxx(),maxy());
	setcolor(GREEN);
	outtextxy(getmaxx()-150,80,"LIFE :");
	outtextxy(getmaxx()-150,100,"KILLS:");
	outtextxy(getmaxx()-150,120,"LEVEL:");
	if(color)
	{
		setcolor(RED);
		if(!s->dead){
			show(s->r[0]);
		}
		else{
			outtextxy(240,200,"DEAD!!");
		}
		setcolor(BLUE);
		for(i=1;i<s->len-1;i++){
			show(s->r[i]);
		}
		setcolor(GREEN);
		show(s->r[i]);
	}
	else
	{
		setcolor(BLACK);
		for(i=0;i<s->len;i++){
			show(s->r[i]);
		}
	}
}


void move()
{
	int j;
	disp(1);
	ckill();
	if(s->level<9){
		j=120-10*(s->level-1);
	}
	else{
		j=40;}
	delay(j);
	disp(0);
	next();
}

void score()
{
	FILE *fp;
	int i=0,j,scr,rank,day,mon,year;
	char nam[30],xyz[20],level[8];
	struct	score sc[10];
	struct date d2;
	getdate(&d2);
	clrscr();
	for(j=0;j<10;j++)
	{
		strcpy(sc[j].name,"");
		strcpy(sc[j].level,"-");
		sc[j].score=0;
		sc[j].mon=0;
		sc[j].day=0;
		sc[j].year=0;
	}
	printf("\n%s,your score was : %d",s->name,s->kill);
	fp=fopen("snkscore.dat","a+");
	fputs(s->name,fp);
	fprintf(fp,"\t%3d\t%2d\t%2d\t%04d",s->kill,d2.da_day,d2.da_mon,d2.da_year);
	if(s->diff==1){
		fprintf(fp,"\t%s\n","Easy");}
	else if(s->diff==2){
		fprintf(fp,"\t%s\n","Medium");}
	else if(s->diff==3){
		fprintf(fp,"\t%s\n","Hard");}
	printf("\n\n%8s%20s\t%6s%12s\t%7s \n","RANK","NAME","SCORE","DATE","Level");
	for(i=0;i<64;i++){
		printf("-");}
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%s%d%d%d%d%s",nam,&scr,&day,&mon,&year,level);
		if(scr>=sc[9].score && !feof(fp))
		{
			for(j=9;scr>=sc[j-1].score&&j>0;j--)
			{
				strcpy(sc[j].name,sc[j-1].name);
				strcpy(sc[j].level,sc[j-1].level);
				sc[j].score=sc[j-1].score;
				sc[j].year=sc[j-1].year;
				sc[j].day=sc[j-1].day;
				sc[j].mon=sc[j-1].mon;
			}
			sc[j].score=scr;
			strcpy(sc[j].name,nam);
			strcpy(sc[j].level,level);
			sc[j].year=year;
			sc[j].day=day;
			sc[j].mon=mon;
		}
	}
	for(i=0;i<10;i++){
		printf("\n%8d%20s\t%3d\t%02d\\%02d\\%04d\t%7s",i+1,sc[i].name,sc[i].score,sc[i].day,sc[i].mon,sc[i].year,sc[i].level);}
	getch();
	fclose(fp);
}

void main()
{
	int temp;
	int gm,gd=DETECT,i,count,re,diff=1;
	s=(SNAKE *)malloc(sizeof(SNAKE));
	clrscr();
	fflush(stdin);
	printf("\n\n\n\n\n\tThis is the classic and ever so famous snake game....\nWe, Have made this game using C programming......\nUse arrow keys and eat as many mice as you can till you are out of ur lives\nYou lose life either by colliding with the snake or the wall\nYou get 3 lives initially\nAfter every 15 mice ur snake eats,you get an opportunity to eat a bonus mongoose which is worth 5 mice\n\nPress 'x' to exit at any time during game\n\n\nSO enjoy.....and dont forget to boast of ur high scores  ;)");
	getch();
	clrscr();
	printf("\nPlease Enter Your First Name : ");
	scanf("%s",s->name);
	do{
		printf("\nSelect Type \n1. Bounded\t\t2. Unbounded : ");
		flushall();
		scanf("%d",&s->type);
	}while(s->type>2 || s->type<1);
	do{
		flushall();
		printf("\nSelect Difficulty \n1. Easy\t\t2. Med\t\t3. Hard : ");
		scanf("%d",&diff);
	}while(diff>3 || diff<1);
	initgraph (&gd, &gm, "");
	print(0);
	s->life=LIFE;
	s->kill=0;
	s->level=1;
	s->diff=diff;
	print(1);
	while(s->life)
	{
		s->dead=0;
		s->move=21;
		s->dir='l';
		s->len=MIN;
		//	s->hold=0;
		for(i=0;i<s->len;i++)
		{
			s->r[i].x[0]=maxx()-SIZE*(s->len-i);
			s->r[i].y[0]=maxy()-SIZE;
			s->r[i].x[1]=s->r[i].x[0]+SIZE;
			s->r[i].y[1]=s->r[i].y[0]+SIZE;
		}
		gen();
		outtextxy(min()+2,min()+2,"Press Enter key to Start");
		getch();
		clear(1);
		clear(0);
		disp(1);
		temp=75;
		re=1;
		fflush(stdin);
		while(!s->dead)
		{
			switch(temp)
			{
			case 75: if(s->dir!='r'){ s->dir='l';count++;}  break;
			case 72: if(s->dir!='d'){ s->dir='u';count++;}  break;
			case 77: if(s->dir!='l'){ s->dir='r';count++;}  break;
			case 80: if(s->dir!='u'){ s->dir='d';count++;}  break;
			}
			fflush(stdin);
			while((!kbhit() && !s->dead)||count!=0)
			{
				move();
				count=0;
			}
			if((!s->dead)&&(!count || re))
			{
				re=0;
				temp=getch();
			}
			if(temp=='x')
			{
				s->dead=1;
				s->life=1;
			}
		}
		disp(1);
		getch();
		print(0);
		s->life--;
	}
	clear(1);
	clear(0);
	setcolor(YELLOW);
	fflush(stdin);
	getch();
	outtextxy(240,220,"GAME OVER !!!");
	print(1);
	getch();
	closegraph();
	score();
	printf("\nPlay Again ?? (NO=n,YES=y) " );
	flushall();
	count=getch();
	if(count!='n' && count!='N')
	{
		main();
		exit(1);
	}
	printf("\n\n\n\t\tTHANK YOU VERY MUCH PLAYING THIS GAME\n\n\n\t\t\t--Jugal Thakkar, http://jugal.me/");
	getch();
}