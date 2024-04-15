/* |  expression evaluator |  17, 18 and 19 October 2002 | */

#include <stdio.h>
#include <math.h>
#include <alloc.h>
#define MAX 50
#define ESC 0x1b
#define F1 59
#define SIZE 8

void replace(char *str, int start, int num, char *new)    /* positions are actual array subscripts */
{

	int i, j;
	while(num!=0)
	{
		for(j=start; j<strlen(str); j++)
			str[j]=str[j+1];
		num--;
	}
	for(j=0; j<strlen(new); j++)
	{
		for(i=strlen(str); i>=start; i--)
			str[i+1]=str[i];
		i++;
		str[i]=new[j];
		start++;
	}
	return;
}

int interpret( char *num, double **arr, int *size, char *str )
{
	int i, j, tag, flag, pos;
	char ch[3]={'\0', '\0', '\0'};
	*size=SIZE;
	*arr=(double *)calloc(*size, sizeof(double));
	for(i=0; i<MAX ; i++)
		str[i]='\0';
	for(i=0; i<strlen(num); i++)
	{
		if(num[i]=='-')
		{
			if((!(num[i-1]==')' || isdigit(num[i-1])) || i==0) && (isalpha(num[i+1]) || num[i+1]=='('))
			{
				replace(num, i+1, 0, "1*");
				i+=2;
			}
		}
	}
	i=j=tag=0;
	while(num[tag]!='\0')
	{
		if(isdigit(num[tag]) || num[tag]=='.')
		{
			if(i>=30)
			{
				printf("\n Too  many  numbers.");
				return 0;
			}
			if(i==*size)
			{
				(*size)++;
				(*arr)=(double *)realloc((*arr), (*size)*sizeof(double));
				(*arr)[*size-1]=0;              // assigning zero to newly added block or element
			}
			for(flag=0, pos=0, str[j++]=i+'0' ; isdigit(num[tag]) || num[tag]=='.'; tag++)
			{
				if(num[tag]=='.')
				{
					flag=1;
					tag++;
				}
				if(!isdigit(num[tag])) break;
				if(flag==0)
					(*arr)[i]=(*arr)[i]*10+(num[tag]-'0');
				else
					(*arr)[i]+=((double)(num[tag]-'0'))/pow10(++pos);
			}
			i++;
		}
		else str[j++]=num[tag++];
		if(num[tag-1]=='\0') break;
	}
	/*  Not reqd. : replacing ln, it etc with single character equivalents */
	for(i=0; i<strlen(str);  i++)
	{
		if(str[i]=='-')
		{
			if((!(str[i-1]==')' || (str[i-1] >= '0' && str[i-1] <= '0'+ *size)) || i==0) && (str[i+1] >= '0' && str[i+1] <= '0'+ *size))             // since no alphabetic operator  associate towards left only, eg. num1®k - num2
			{                                                                                                          // and  a -sign after a bracket would surely indicate a negative  quantity
				(*arr)[str[i+1]-'0']=-(*arr)[str[i+1]-'0'];
				ch[0]=str[i+1];
				ch[1]='\0';
				replace(str, i, 2, ch);
				i++;
			}
		}
	}
	/* Not reqd. : finding unknown characters */
	return 1;
}

void decode(char ch)
{
	switch(ch)
	{
		case 's': cprintf("sin "); break;
		case 'c': cprintf("cos "); break;
		case 't': cprintf("tan "); break;
		case 'e': cprintf("exp "); break;
		case 'p': cprintf("ypx "); break;
		case 'u': cprintf("urt "); break;
		case 'd': cprintf("log "); break;
		case 'l': cprintf("ln "); break;
		case 'q': cprintf("isin "); break;
		case 'a': cprintf("icos "); break;
		case 'r': cprintf("itan "); break;
		default : cprintf("%c ", ch);
	}
}

void showstep(double *arr, char *str, int size, int tag)
{
	int i;
	printf("\n");
	cprintf(" %d.> ", tag);
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]>='0' && str[i]<='0'+size)
			cprintf("%lg ", arr[str[i]-'0']);
		else decode(str[i]);
	}
}

double mem=0;
void value(double *arr, char *str, int size, int step)
{
	int i, temp, flag;
	int count, tag=0;
	char ch[3]={'\0', '\0', '\0'};
	count=0;
	while(strlen(str)>1)
	{
	count++;
	if(count>=20)     // safety precaution
	{
		printf("\n Syntax error.");
		return;
	}
	for(i=0; str[i]!=')' && str[i]!='\0'; i++);
	for(temp=i ; str[temp]!='(' && temp>=0; temp--);
	for(i=temp+1, flag=0; str[i]!=')' && str[i]!='\0'; i++)
	{
		if(str[i]=='X' && (str[i-1] >= '0' && str[i-1] <= '0'+size) && (str[i+1] >= '0' && str[i+1] <= '0'+size))
		{
			arr[str[i+1]-'0']=arr[str[i-1]-'0']*pow10(arr[str[i+1]-'0']);
			ch[0]=str[i+1];
			ch[1]='\0';
			replace(str, i-1, 3, ch);
			//if((str[temp]=='(' && str[temp+2]==')') || strlen(str)==1) break;
			i=temp;
		}
	}
	for(i=temp+1, flag=0; str[i]!=')' && str[i]!='\0'; i++)
	{
		if(str[i]>='a' && str[i]<='z' || str[i]=='X')
		{
			if((str[i+1] >= '0' && str[i+1] <= '0'+size))
			{
			switch(str[i])
				{
					case 'e':
						arr[str[i+1]-'0']=exp(arr[str[i+1]-'0']);
						break;
					case 'u':
						arr[str[i+1]-'0']=sqrt(arr[str[i+1]-'0']);
						break;
					case 'l':
						arr[str[i+1]-'0']=log(arr[str[i+1]-'0']);
						break;
					case 'd' :
						arr[str[i+1]-'0']=log10(arr[str[i+1]-'0']);
						break;
					case 's' :
						arr[str[i+1]-'0']=sin(arr[str[i+1]-'0']);
						break;
					case 'c' :
						arr[str[i+1]-'0']=cos(arr[str[i+1]-'0']);
						break;
					case 't' :
						arr[str[i+1]-'0']=tan(arr[str[i+1]-'0']);
						break;
					case 'p' :
						if((str[i-1] >= '0' && str[i-1] <= '0'+size))
						{
						arr[str[i+1]-'0']=pow(arr[str[i-1]-'0'], arr[str[i+1]-'0']);
						flag=1;
						}
						break;
					case 'X' :
						if((str[i-1] >= '0' && str[i-1] <= '0'+size))
						{
						arr[str[i+1]-'0']=arr[str[i-1]-'0']*pow10(arr[str[i+1]-'0']);
						flag=1;
						}
						break;
					case 'a' :
						arr[str[i+1]-'0']=acos(arr[str[i+1]-'0']);
						break;
					case 'q' :
						arr[str[i+1]-'0']=asin(arr[str[i+1]-'0']);
						break;
					case 'r' :
						arr[str[i+1]-'0']=atan(arr[str[i+1]-'0']);
						break;
					default :
						flag=2;
						break;

				}
			ch[0]=str[i+1];
			ch[1]='\0';
			if(flag==0) replace(str, i, 2, ch);
			if(flag==1) replace(str, i-1, 3, ch);
			//if((str[temp]=='(' && str[temp+2]==')') || strlen(str)==1) break;
			i=temp;
			flag=0;
			if(step==1) showstep(arr, str, size, ++tag);
		}
		}
	}
	for(i=temp+1, flag=0; str[i]!=')' && str[i]!='\0'; i++)
	{
		if(str[i]=='*' || str[i]=='/')
		{
			if((str[i-1] >= '0' && str[i-1] <= '0'+size) &&  (str[i+1] >= '0' && str[i+1] <= '0'+size))
			{
				switch(str[i])
				{
					case '*' :
						arr[str[i+1]-'0']=arr[str[i-1]-'0'] * arr[str[i+1]-'0'];
						break;
					case '/' :
						arr[str[i+1]-'0']=arr[str[i-1]-'0'] / arr[str[i+1]-'0'];
						break;
					default :
						flag=1;
						break;
				}
				ch[0]=str[i+1];
				ch[1]='\0';
				if(flag==0) replace(str, i-1, 3, ch);
				//if((str[temp]=='(' && str[temp+2]==')') || strlen(str)==1) break;
				i=temp;    // since it will be incremented before condition check
				flag=0;
				if(step==1) showstep(arr, str, size, ++tag);
			}
		}
	}
	for(i=temp+1, flag=0; str[i]!=')' && str[i]!='\0'; i++)
	{
		if(str[i]=='+' || str[i]=='-')
		{
		     if((str[i-1] >= '0' && str[i-1] <= '0'+size) &&  (str[i+1] >= '0' && str[i+1] <= '0'+size))
		     {
		     switch(str[i])
		     {
				case '+' :
					arr[str[i+1]-'0']=arr[str[i-1]-'0'] + arr[str[i+1]-'0'];
					break;
				case '-' :
					arr[str[i+1]-'0']=arr[str[i-1]-'0'] - arr[str[i+1]-'0'];
					break;
				default:
					flag=1;
					break;
			}
			ch[0]=str[i+1];
			ch[1]='\0';
			if(flag==0) replace(str, i-1, 3, ch);
			//if((str[temp]=='(' && str[temp+2]==')') || strlen(str)==1) break;
			i=temp;
			flag=0;
			if(step==1) showstep(arr, str, size, ++tag);
		     }
		}
	}
	if(str[temp]=='('  &&  temp>=0)
	{
		if((str[temp+1] >= '0' && str[temp+1] <= '0'+size) && str[temp+2]==')')
		{
			for(i=temp; i<strlen(str); i++)
				str[i]=str[i+1];
			for(i=temp; str[i]!=')'; i++);
			for(; i<strlen(str); i++)
				str[i]=str[i+1];
		}
	}
	}
	if(strlen(str)==1)
	{
		if(step==1) printf("\n\n");
		cprintf(" Answer >>  %.10lg", arr[str[0]-'0']);
		if((ch[0]=getch())=='m' || ch[0]=='M')
			mem=arr[str[0]-'0'];
	}
	return;
}

void clstr(short int init_row, short int rows)
{
	int j;
	gotoxy(1, init_row);
	for(j=0; j<79*rows; j++)
		printf(" ");
	gotoxy(1, init_row);
	return;
}

void help()
{
	textcolor(13);
	gotoxy(2, 22); cprintf("|  ( , ) ð Brackets  | R ð replay last   | M ð store(at Ans display)/recall|");
	gotoxy(2, 23); cprintf("| <enter> ð  Input   | + , - , * , / (I) | e ð exp (P) | u ð underroot (P) |");
	gotoxy(2, 24); cprintf("|  s , c , t  ð sine etc.    (P)    |  p  ð power (I)  | X ð *10 power (I) |");
	gotoxy(2, 25); cprintf("| is, ic, it  ð inverse sine etc.(P)|  lo ð log10 (P)  | ln ð ln (P)       |");
}

void refresh(int hlp)
{
	clrscr();
	textbackground(0);
	textcolor(15);
	gotoxy(2, 1); cprintf("w ð Steps [ %s ]", "On ");
	gotoxy(67,1); cprintf("F1  ð  Help");
	textcolor(14);
	gotoxy(20, 3);
	cputs("ð ñ ü *  Super  Calculator  * ó ö ¬");
	gotoxy(30, 5);
	cputs("Enter 0 to exit");
	// cprintf("\n\n ¯ ");
	if(hlp==1)  help();
	gotoxy(1, 6);
	textbackground(0);
	textcolor(13);
}

void main()
{
	double *arr;
	int i, c, brkt, tag, size, steps=1, flag[MAX];
	int zzz=0, maxrow=23, hlp=-1, dec, sign;
	char ch, num[MAX], temp[2]; //="(12.3)-(2p(ln(4-2.1*(6+2.1)/(3*4)))/2)*3-2"; //="(7.3*((2+ln(31.6-2*8))/4)-s2)";
	char str[MAX], prev[MAX], prev_[MAX]; //="(1+(t1-10*9.8/(10*c1)p2)*(t1-10*9.8/(10*c1)p2))p1.5/(9.8/(10*c1)p2)";
	char *number;
	refresh(hlp);
	for(i=0; i<3; i++) prev[0]='\0';
	while(1) {
	if(zzz==40) { printf("\n Please run the program again."); break; }
	for(i=0; i<MAX; i++)
	{
		num[i]='\0';
		prev[i]='\0';
	}
	if(wherey() >= maxrow) { refresh(hlp); }
	fflush(0);
	printf("\n\n");
	cprintf(" ¯ ");
	zzz++;
	for(i=0; i<MAX ;i++)
	{
		num[i]=getch();
		if((num[i]>='0' && num[i]<='9') || num[i]=='l' || num[i]=='l' || num[i]=='i' || num[i]=='+' || num[i]=='-' || num[i]=='*' || num[i]=='/' || num[i]=='(' || num[i]==')' || num[i]=='s' || num[i]=='c' || num[i]=='t' || num[i]=='e' || num[i]=='p' || num[i]=='u' || num[i]=='X' || num[i]=='.' || num[i]==' ' || num[i]=='\r' || num[i]=='\b' || num[i]=='<' || num[i]=='>')
		{
			if(num[i]=='\r') break;
			if(num[i]=='s' || num[i]=='c' || num[i]=='t' || num[i]=='u' || num[i]=='e' || num[i]=='p')
			{
				flag[i]=3;  // three character long names
				switch(num[i])
				{
					case 's': cprintf("sin"); strcat(prev, "sin"); break;
					case 'c': cprintf("cos"); strcat(prev, "cos"); break;
					case 't': cprintf("tan"); strcat(prev, "tan"); break;
					case 'e': cprintf("exp"); strcat(prev, "exp"); break;
					case 'p': cprintf("ypx"); strcat(prev, "ypx"); break;
					case 'u': cprintf("urt"); strcat(prev, "urt"); break;
				}
			}
			else if(num[i]=='l')
			{
				putch(num[i]);
				ch=getch();
				switch(ch)
				{
					case 'o' : flag[i]=3; cprintf("og"); num[i]='d'; strcat(prev, "log"); break;
					case 'n' : flag[i]=2; putch(ch); num[i]='l'; strcat(prev, "ln"); break;
					default  : printf("\b \b"); num[i]=num[i-1]; i--; break;
				}
			}
			else if(num[i]=='i')
			{
				flag[i]=4;
				putch(num[i]);
				ch=getch();
				switch(ch)
				{
					case 's' : cprintf("sin"); num[i]='q'; strcat(prev, "isin"); break;
					case 'c' : cprintf("cos"); num[i]='a'; strcat(prev, "icos"); break;
					case 't' : cprintf("tan"); num[i]='r'; strcat(prev, "itan"); break;
					default  : cprintf("\b \b"); num[i]=num[i-1]; i--; break;
				}
			}
			else if(num[i]=='\b')
			{
				if(i>0)
				{
					for(brkt=0; brkt<flag[i-1]; brkt++)
						printf("\b \b");
					prev[strlen(prev)-flag[i-1]] = '\0';
					i-=2;
				}
				else i = -1;
			}
			else if(num[i]=='<')
			{
				// size = i-1;
				// for(brkt=0; brkt<flag[size] ;brkt++)
				// 	printf("\b");



			}
			else if(num[i]=='>')
			{

			}
			else { flag[i]=1; putch(num[i]); temp[0]=num[i]; temp[1]='\0'; strcat(prev, temp); }
		}
		else if(num[i]=='r' || num[i]=='R') { i--; brkt=wherex(); size=wherey(); hlp=-1;  clstr(21, 5); maxrow=23; gotoxy(2, 24); cprintf("%s", prev_); gotoxy(brkt, size);}
		else if(num[i]=='w' || num[i]=='W') { i--; brkt=wherex(); size=wherey(); steps*=-1; gotoxy(2, 1); textcolor(15); cprintf("w ð Steps [ %s ]", (steps==1) ? "\aOn " : "Off"); textcolor(13); gotoxy(brkt, size);}
		else if(num[i]=='m' || num[i]=='M') {if(mem!=0){ size=i; number=fcvt(mem, 6, &dec, &sign); if(sign==1) { flag[i]=1; num[i++]='-';} for(brkt=0, size=0; brkt<strlen(number); brkt++) { flag[i]=1; num[i++]=number[brkt]; if(brkt==dec-1) { flag[i]=1; num[i++]='.'; } } for(brkt=size; brkt<i; brkt++) { putch(num[brkt]); temp[0]=num[brkt]; temp[1]='\0'; strcat(prev, temp);} } else i--;}
		else if(num[i]==F1) { i--; brkt=wherex(); size=wherey();  hlp*=-1; if(hlp==1) { maxrow=21; help(); } else {  clstr(21, 5); maxrow=23; } gotoxy(brkt, size);}
		else { printf("\a"); i--; }
	}
	if(num[0]=='\r')  { gotoxy(4, wherey()-2); continue; }
	num[i]='\0';
	for(i=0; i<=strlen(prev); i++) prev_[i]=prev[i];
	printf("\n");
	if(strlen(num) > MAX)
	{
		printf("\n Too long..");
		continue;
	}
	for(i=0, brkt=0; i<strlen(num); i++)
	{
		if(num[i]=='(') brkt++;
		if(num[i]==')') brkt--;
		if(num[i]==',' || num[i]==' ')
		{
			for(c=i; c<strlen(num); c++)
				num[c]=num[c+1];
			i--;
		}
	}
	if(num[0]=='0' && num[1]=='\0')
	{
		clrscr();
		puts("\n   Developed by Amit Saxena,");
		puts("   Student, second yr., BSc Engg (Electrical), Roll no 014003");
		puts("   Engineering faculty, Dayalbagh Educational Instt, Agra");
		puts("\n   For suggestions or queries >> mail2amitsaxena@yahoo.com");
		getch();
		textcolor(7);
		break;
	}
	if (brkt!=0)
	{
		printf(" Unbalanced brackets ! ");
		continue;
	}
	for(i=0; i<MAX; i++)          // i initial was -1, not 0 ??
		str[i]='\0';
	tag = interpret(num, &arr, &size, str);
	if(tag==1) value(arr, str, size, steps);
	free (arr);
	}
}

void helptxt(void)
{
	FILE  *ptr;
	char  ch;
	textcolor(10);
	gotoxy(35,1); cprintf("H  E  L  P \n\n");
	textcolor(14);
	clrscr();
	ptr=fopen("hlp_calc.txt", "r");
	if(ptr==NULL)
	{
		printf("Unable to open help file ");
		return;
	}
	while((ch=fgetc(ptr))!=EOF)
		putch(ch);
	return;
}


void hlp(int steps)
{
	void helptxt(void);
	char ch='z';
	clrscr();
	helptxt();
	_setcursortype(0);
	gotoxy( 24, 6);
	cprintf((steps==1) ? "\aOn " : "Off");
	while(ch!=ESC)
	{
		ch='\0';
		ch=getch();
		if(ch=='S')
		{
			steps *= -1;
			gotoxy( 24, 6);
			cprintf((steps==1) ? "\aOn " : "Off");
		}
	}
	clrscr();
	_setcursortype(2);
	fflush(0);
	return;
}

