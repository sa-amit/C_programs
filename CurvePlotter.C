#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 60
#define ESC 0x1b
#define MAXZ 6
//Gauss Normal distribution -> 5*exp(-.5*pow((z-3)/.97, 2))/(sqrt(2*3.1416)*.97), z
// (z/2-2)*cos(5*z), (log(z*z)-3)*(z-1.5)/z
#define SCREEN_SIZE 15
#define CF .85

float cx=0, cy=0, oneunit;
int centre=1, mx, my;

void main()
{
	void clstr(short int, short int);
	float xpoint(float x);
	float ypoint(float y);
	int mode, driver=DETECT;
	char msg[MAX], val[10];
	int show=1, intval=0, maxtime=1000, temp=0, bound=5000, wrt=0, flagx=0, flagy=0, grid=1;
	float fltval=0, I_y_dx0=0;
	float i, x, y, px, py, n=1, a=-6, b=6, step=.005 , z=-5, max=-1000, min=1000, xmax=-1000, xmin=1000;
	float factor=.25, onecm, kx, ky, x_, y_, dx=0, dy=0, dy_dx, Ix=0, Iy=0, I_y_dx=0, m=0;
	float arrx[10], arry[10];
	void simplify(char *, float *);
	void replace(char *str, int start, int num, char *new);
	void getinput(char *);
	void refresh(void);
	float value_(char [], float [], float );      // string = simplified string, arr = values, z = variable
	char YFZ[MAX], XGZ[MAX];
	refresh();
	printf("\n\n");
	cprintf(" Enter parametric eqns Џ ");
	printf("\n\n");
	cprintf(" y = ");
	getinput(YFZ);
	cprintf(" x = ");
	getinput(XGZ);
	cprintf("\n\n Check Settings ? [ no=0, yes=1 ] : ");
	temp=getch();
	if(temp-'0'==1)
	{
		do {
		clrscr();
		printf("\n y = ");
		puts(YFZ);
		printf("\n\n x = ");
		puts(XGZ);
		flagy=0;
		gotoxy(2, 8+flagy++); cprintf("0.> Show grid [%d]", grid);
		gotoxy(2, 8+flagy++); cprintf("1.> Centre of coordinates [%.1g %.1g]", cx, cy);
		gotoxy(2, 8+flagy++); cprintf("2.> Lower limit [%.1g]", a);
		gotoxy(2, 8+flagy++); cprintf("3.> Upper limit [%.1g]", b);
		gotoxy(2, 8+flagy++); cprintf("4.> Number of units in one centimetre [%g]", factor);
		gotoxy(2, 8+flagy++); cprintf("8.> Step size (increment in z per step) [%g]", step);
		gotoxy(2, 8+flagy++); cprintf("6.> Plot derivative and integral curves [%d]", show);
		gotoxy(2, 8+flagy++); cprintf("7.> Initial value of integral (at z=a) [%g]", I_y_dx0);
		gotoxy(2, 8+flagy++); cprintf("8.> Plot curve very slowly [%d]", wrt);
		gotoxy(2, 8+flagy++); cprintf("9.> Upper bound on values of x and y [%d]", bound);
		gotoxy(2, 8+flagy++); cprintf("X.> Exit settings and start plotting");
		clstr(8+2+flagy, 3);
		do
		{
		gotoxy(2, 8+1+flagy); cprintf(" Enter option : ");
		if((temp=getch())!='\r') putch(temp);
		}while(temp=='\r');
		if(temp-'0'>=0 && temp-'0'<=9)
		{
		gotoxy(2, 8+3+flagy); cprintf(" Enter new value : ");
		temp=temp-'0';
		if(temp!=1)
		{
		for(intval=0; ; intval++)
		{
			if((val[intval]=getch())!='\r')
				putch(val[intval]);
			else break;
		}
		}
		else scanf("%f %f", &cx, &cy);
		gotoxy(wherey()-1);
		val[intval]='\0';
		if(temp==0 || temp==6 || temp==8 || temp==9)
		{
			intval=atoi(val);
			switch(temp)
			{
				case 0 : if(intval==0 || intval==1) grid=intval; break;
				case 6 : if(intval==0 || intval==1) show=intval; break;
				case 8 : if(intval==0 || intval==1) wrt=intval; break;
				case 9 : bound=intval; break;
			}
		}
		else
		{
			fltval=atof(val);
			switch(temp)
			{
				case 2 : a=fltval; break;
				case 3 : b=fltval; break;
				case 4 : factor=fltval; break;
				case 5 : step=fltval; break;
				case 7 : I_y_dx0=fltval; break;
				default : cprintf(" Wrong choice");
			}
		}
		}
		} while('X'!=toupper(temp));
	}
	simplify(XGZ, arrx);
	simplify(YFZ, arry);
	initgraph(&driver,&mode,"c:\\bgi");
	my=getmaxy();
	mx=getmaxx();
	onecm =	mx / (cos(atan(.75))*SCREEN_SIZE*2.54);
	oneunit = onecm / factor ;	    /* oneunit = ( onecm / factor ) pixels  */
	setbkcolor(0);
	setcolor(15);
	settextstyle(2, 0, 0);
	kx = textwidth("A");
	ky = textheight("A");
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	sprintf(msg, "(%g,%g)", cx, cy);
	if(centre==1)
	{
		outtextxy(mx/2+2, my/2+2, msg);
		line(0, my/2, mx, my/2);             // coordinate axes
		line(mx/2, 0, mx/2, my);
		for(i=mx/2; i<=mx; i+=oneunit)
		{
			if(grid!=1) line(i, my/2-1, i, my/2+1);
			if(grid==1) line(i, 0, i, my);
		}
		for(i=mx/2; i>=0; i-=oneunit)
		{
			if(grid!=1) line(i, my/2-1, i, my/2+1);
			if(grid==1) line(i, 0, i, my);
		}
		for(i=my/2; i<=my; i+=oneunit)
		{
			if(grid!=1)line(mx/2-1, i, mx/2+1, i);
			if(grid==1) line(0, i, mx, i);
		}
		for(i=my/2; i>=0; i-=oneunit)
		{
			if(grid!=1) line(mx/2-1, i, mx/2+1, i);
			if(grid==1) line(0, i, mx, i);
		}
	}
	else
	{
		outtextxy(3, my-3, msg);
		line(0, my, mx, my);
		line(0, my, 0 , 0);
		for(i=2; i<=mx; i+=oneunit)
		{
			if(grid!=1) line(i, my, i, my-2);
			if(grid==1) line(i, my, i, 0);
		}
		for(i=2; i<=my; i+=oneunit)
		{
			if(grid!=1) line(0, my-i, 2, my-i);
			if(grid==1) line(0, my-i, mx, my-i);
		}
	}
	// a=cx-(mx/2)/oneunit;    // now initial value of z (i.e. 'a') is left end of screen, if x=z
	I_y_dx=I_y_dx0  ;
	z = a-step;                 // initialisation of y_ and x_
	y_ = value_(YFZ, arry, z);
	x_ = value_(XGZ, arrx, z);
	xmax=xmin=x_;
	sprintf(msg, "( %.2g, %.2g)", x_, y_);
	outtextxy(xpoint(x_), ypoint(y_), msg);
	for(flagx=0, flagy=0, i=0, z=a;  ; z+=step)
	{
		y = value_(YFZ, arry, z);
		x = value_(XGZ, arrx, z);
		dy_dx = (y-y_)/(x-x_);
		if( dy_dx > -.5 && dy_dx < .5)
		{
			if(max<y) { max=y; xmax=x; }
			if(min>y) { min=y; xmin=x; }
		}
		// if(y==0) { zero++; yzero[c1++]=y; }
		// if(y>100000 && y_<y/100)  { pole++; ypole[c2++]=y; }
		I_y_dx  = I_y_dx + y*(x-x_);
		px=xpoint(x);
		py=ypoint(y);
		if(flagx==0 || flagy==0)
		{
			if((x-cx>-.01 && x-cx<.01) || (y-cy>-.01 && y-cy<.01))
			{
				if((x-cx>-.01 && x-cx<.01) && !(y-cy>-.1 && y-cy<.1))
				{
					flagx=1;
					sprintf(msg, "%.2g", y);
					setcolor(BLACK);
					outtextxy(px+1, py-2, "лллллллл");
					setcolor(WHITE);
					outtextxy(px+1, py-2, msg);
				}
				else if((y-cy>-.01 && y-cy<.01) && !(x-cx>-.1 && x-cx<.1))
				{
					flagy=1;
					sprintf(msg, "%.2g", x);
					setcolor(BLACK);
					outtextxy(px+1, py-2, "лллллллл");
					setcolor(WHITE);
					outtextxy(px+1, py-2, msg);
				}
			}
		}
		if(x>.5 || x<-.5) flagx=0;
		if(y>.5 || y<-.5) flagy=0;
		if(kbhit())
		{
			if(getch()==ESC)
			{
				outtextxy(1, 5*ky, "User break");
				break;
			}
			else
			{
				setcolor(MAGENTA);        		// Draw tangent
				m=atan(dy_dx);
				moveto(px, py);
				linerel(40*cos(m), -40*sin(m));
				setcolor(WHITE);
				outtextxy(75*kx, 51*ky, "Press any key to continue..");
				getch();
				setcolor(BLACK);
				outtextxy(75*kx, 51*ky, "ллллллллллллллллллллллллллллллллллллллллл");
				outtextxy(75*kx, 51*ky+2, "ллллллллллллллллллллллллллллллллллллллллл");
				moveto(px, py);
				linerel(40*cos(m), -40*sin(m));
				setcolor(WHITE);
			}
		}
		y_=y;                                  // store the values of y and x for next loop of calculations
		x_=x;
		textcolor(WHITE);
		if(show==1)
		{
			gotoxy(1, 1);
			cprintf("| z=%4.2g ", z);
			cprintf("| x=%6.2f , y=%6.2f ", x, y);
			cprintf("| dy/dx=%7.2g ", dy_dx);
			cprintf("| I y dx = %7.2g |       ", I_y_dx);
		}
		if(wrt==1) delay((int)(step*1000*CF/n));
		if(y>bound || x>bound) { i++; continue; }
		if((int)z%2==0)
		{
			if(y*oneunit > my/2 || y*oneunit < -my/2 || x*oneunit > mx/2 || x*oneunit < -mx/2) i++;
			if(i >= 10000) { outtextxy(1, 5*ky, "Break due to too many points being outside the viewable area"); break; }
			if((z-a)/n >= maxtime) { outtextxy(1, 5*ky, "Break at the end of time limit "); break; }
			if(z >= b) { outtextxy(1, 5*ky, "Break at the upper limit"); break; }
		}
		putpixel(px, py, 14);
		putpixel(px, ypoint(dy_dx), LIGHTGREEN);
		putpixel(px, ypoint(I_y_dx), LIGHTBLUE);
	}
	sprintf(msg, "( %.2g, %.2g)", x, y);
	outtextxy(xpoint(x), ypoint(y), msg);
	if(x>xmax) xmax=x;
	if(x<xmin) xmin=x;
	sprintf(msg, "Local maxima is %.3g at %.3g", max, xmax);
	outtextxy(1, 6*ky, msg);
	sprintf(msg, "Local minima is %.3g at %.3g", min, xmin);
	outtextxy(1, 7*ky, msg);
	sprintf(msg, "Integral along the curve within the limits a=%g to b=%g is %.4g", a, b, I_y_dx);
	outtextxy(1, 9*ky, msg);
	sprintf(msg, " ( assuming initial value %g at lower limit of z )", I_y_dx0);
	outtextxy(1, 10*ky, msg);
	outtextxy(1, 12*ky, " Developed by Amit Saxena; 2nd yr BSc Engg(electrical); RNo 014003");
	outtextxy(1, 13*ky, " < mail2amitsaxena@yahoo.com >");
	getch();
	closegraph();
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
	printf("\n %d.> ", tag);
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]>='0' && str[i]<='0'+size)
			cprintf("%lg ", arr[str[i]-'0']);
		else decode(str[i]);
	}
}

float xpoint(float x)
{
	float px;
	px=centre*mx/2+(x-cx)*oneunit;
	if(px-(int)px > .55 ) px=(int)px+1;
	else px=(int)px;
	return px;
}

float ypoint(float y)
{
	float py;
	py=my-centre*my/2-(y-cy)*oneunit;
	if(py-(int)py > .55 ) py=(int)py+1;
	else py=(int)py;
	return py;
}


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

void simplify(char *input, float *arr)
{
	char *input_, temp[10];
	int c1, c2, tag, i;
	input_=(char *)malloc(MAX*sizeof(char));
	if(input_==NULL) { cprintf(" Insufficient memory");  exit(0);  }
	for(i=0; i<10; i++)
		arr[i]=0;
	for(i=0; i<strlen(input); i++)
	{                                                      /* Deleting white space and commas from the number */
		if(input[i]==' ')
		{
			for(tag=i; tag<strlen(input)-1; tag++)
				input[tag]=input[tag+1];
			input[strlen(input)-1]='\0';               /* Reducing the elements of num by one, by converting the last ch. into null ch. */
			i--;                                       /* Decreasing i so that checking starts from new character in the place of old one */
		}
	}
	for(i=0; i<strlen(input); i++)
	{
		if(input[i]=='-')
		{
			if((!(input[i-1]==')' || isdigit(input[i-1])) || i==0) && (isalpha(input[i+1]) || input[i+1]=='(') && input[i+1]!='z')
			{
				replace(input, i+1, 0, "1*");
				i+=2;
			}
		}
	}
	for(c1=0, c2=MAXZ, tag=0, i=0; i<=strlen(input); )
	{
		if(isdigit(input[i]) || input[i]=='.')
		{
			while(isdigit(input[i]) || input[i]=='.')
				temp[c1++]=input[i++];
			temp[c1]='\0';
			c1=0;
			input_[tag++]=c2+'0';
			arr[c2++]=atof(temp);
		}
		else
			input_[tag++]=input[i++];
	}
	for(i=0, tag=0; i<strlen(input_); i++)
	{
		if(input_[i]=='z')
			input_[i]='0'+tag++;
	}
	for(i=0; i<strlen(input_);  i++)
	{
		if(input_[i]=='-')
		{
			if((!(input_[i-1]==')' || (input_[i-1] >= '0' && input_[i-1] <= '9')) || i==0) && (input_[i+1] >= '0' && input_[i+1] <= '9'))             // since no alphabetic operator  associate towards left only, eg. num1Ўk - num2
			{                                                                                                          // and  a -sign after a bracket would surely indicate a negative  quantity
				arr[input_[i+1]-'0']=-arr[input_[i+1]-'0'];
				temp[0]=input_[i+1];
				temp[1]='\0';
				replace(input_, i, 2, temp);
				i++;
			}
		}
	}
	strcpy(input, input_);
	free(input_);
	if(tag==0) cprintf("Error!  No parameter [ z ] found");
	if(tag>=MAXZ) cprintf("Too many z");
}

float value_(char *str, float *arr, float z)
{
	float arr_[10];
	int i, temp, flag, count;
	char str_[MAX];
	char ch[3]={'\0', '\0', '\0'};
	count=0;
	for(i=0; i<MAXZ; i++)
		arr[i]=z;
	for(i=0; i<10; i++)
		arr_[i]=arr[i];
	for(i=0; i<MAX; i++)
	str_[i]=str[i];
	while(strlen(str_) > 1)
	{
	count++;
	if(count>=15)     // safety precaution
	{
		printf("\n Syntax error.");
		exit(0);
	}
	for(i=0; str_[i]!=')' && str_[i]!='\0'; i++);
	for(temp=i ; str_[temp]!='(' && temp>=0; temp--);
	for(i=temp+1, flag=0; str_[i]!=')' && str_[i]!='\0'; i++)
	{
		if(str_[i]=='E' && (str_[i-1] >= '0' && str_[i-1] <= '9') && (str_[i+1] >= '0' && str_[i+1] <= '9'))
		{
			arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0']*pow10(arr_[str_[i+1]-'0']);
			ch[0]=str_[i+1];
			ch[1]='\0';
			replace(str_, i-1, 3, ch);
			//if((str_[temp]=='(' && str_[temp+2]==')') || strlen(str_)==1) break;
			i=temp;
		}
	}
	for(i=temp+1, flag=0; str_[i]!=')' && str_[i]!='\0'; i++)
	{
		if(str_[i]>='a' && str_[i]<='y' || str_[i]=='E')
		{
			if((str_[i+1] >= '0' && str_[i+1] <= '9'))
			{
			switch(str_[i])
				{
					case 'u':
						if(arr_[str_[i+1]-'0']>0)
						arr_[str_[i+1]-'0']=sqrt(arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0']=20000;
						break;
					case 'l':
						if(arr_[str_[i+1]-'0']>0)
						arr_[str_[i+1]-'0']=log(arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0']=20000;
						break;
					case 'd' :
						if(arr_[str_[i+1]-'0']>0)
						arr_[str_[i+1]-'0']=log10(arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0']=20000;
						break;
					case 's' :
						arr_[str_[i+1]-'0']=sin(arr_[str_[i+1]-'0']);
						break;
					case 'c' :
						arr_[str_[i+1]-'0']=cos(arr_[str_[i+1]-'0']);
						break;
					case 't' :
						arr_[str_[i+1]-'0']=tan(arr_[str_[i+1]-'0']);
						break;
					case 'p' :
						if((str_[i-1] >= '0' && str_[i-1] <= '9'))
						{
						if(!(arr_[str_[i-1]-'0']<0 && arr_[str_[i+1]-'0']<0))
						arr_[str_[i+1]-'0']=pow(arr_[str_[i-1]-'0'], arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0']=20000;
						flag=1;
						}
						break;
					case 'e' :
						arr_[str_[i+1]-'0']=exp(arr_[str_[i+1]-'0']);
						break;
					case 'E' :
						if((str_[i-1] >= '0' && str_[i-1] <= '9'))
						{
						arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0']*pow10(arr_[str_[i+1]-'0']);
						flag=1;
						}
						break;
					case 'a' :
						if(arr_[str_[i+1]-'0']>-1 && arr_[str_[i+1]-'0']<1)
						arr_[str_[i+1]-'0']=acos(arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0'] = 20000;         // arbitrary large number
						break;
					case 'q' :
						if(arr_[str_[i+1]-'0']>-1 && arr_[str_[i+1]-'0']<1)
						arr_[str_[i+1]-'0']=asin(arr_[str_[i+1]-'0']);
						else arr_[str_[i+1]-'0'] = 20000;
						break;
					case 'r' :
						arr_[str_[i+1]-'0']=atan(arr_[str_[i+1]-'0']);
						break;
					default :
						flag=2;
						break;

			}
			ch[0]=str_[i+1];
			ch[1]='\0';
			if(flag==0) replace(str_, i, 2, ch);
			if(flag==1) replace(str_, i-1, 3, ch);
			//if((str_[temp]=='(' && str_[temp+2]==')') || strlen(str_)==1) break;
			i=temp;
			flag=0;
		}
		}
	}
	for(i=temp+1, flag=0; str_[i]!=')' && str_[i]!='\0'; i++)
	{
		if(str_[i]=='*' || str_[i]=='/')
		{
			if((str_[i-1] >= '0' && str_[i-1] <= '9') &&  (str_[i+1] >= '0' && str_[i+1] <= '9'))
			{
				switch(str_[i])
				{
					case '*' :
						arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0'] * arr_[str_[i+1]-'0'];
						break;
					case '/' :
						if(arr_[str_[i+1]-'0']!=0)
						arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0'] / arr_[str_[i+1]-'0'];
						else arr_[str_[i+1]-'0']=20000;
						break;
					default :
						flag=1;
						break;
				}
				ch[0]=str_[i+1];
				ch[1]='\0';
				if(flag==0) replace(str_, i-1, 3, ch);
				//if((str_[temp]=='(' && str_[temp+2]==')') || strlen(str_)==1) break;
				i=temp;    // since it will be incremented before condition check
				flag=0;
			}
		}
	}
	for(i=temp+1, flag=0; str_[i]!=')' && str_[i]!='\0'; i++)
	{
		if(str_[i]=='+' || str_[i]=='-')
		{
		     if((str_[i-1] >= '0' && str_[i-1] <= '9') &&  (str_[i+1] >= '0' && str_[i+1] <= '9'))
		     {
		     switch(str_[i])
		     {
				case '+' :
					arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0'] + arr_[str_[i+1]-'0'];
					break;
				case '-' :
					arr_[str_[i+1]-'0']=arr_[str_[i-1]-'0'] - arr_[str_[i+1]-'0'];
					break;
				default:
					flag=1;
					break;
			}
			ch[0]=str_[i+1];
			ch[1]='\0';
			if(flag==0) replace(str_, i-1, 3, ch);
			//if((str_[temp]=='(' && str_[temp+2]==')') || strlen(str_)==1) break;
			i=temp;
			flag=0;
		     }
		}
	}
	if(str_[temp]=='('  &&  temp>=0)
	{
		if((str_[temp+1] >= '0' && str_[temp+1] <= '9') && str_[temp+2]==')')
		{
			for(i=temp; i<strlen(str_); i++)
				str_[i]=str_[i+1];
			for(i=temp; str_[i]!=')'; i++);
			for(; i<strlen(str_); i++)
				str_[i]=str_[i+1];
		}
	}
	}
	if(strlen(str_)==1)
	{
		count=0;
		return (arr_[str_[0]-'0']);
	}
	return 0;
}

void refresh(void)
{
	clrscr();
	textbackground(0);
	textcolor(14);
	gotoxy(24, 3);
	cputs("їїї   Curve   Plotter   їїї");
	gotoxy(30, 4);
	cputs("Enter 0 to exit");
	// gotoxy(2, 24);
	// printf("p : power ; 1 p 2     X : power of 10 ; 1 X 2      s , c , t : sine etc. ; s 1");
	// printf("\n is, ic, it : inverse sine etc.     lo : log 10 ; lo 1     ln : ln e ; ln 1");
	textbackground(0);
	textcolor(13);
}

void getinput(char *num)
{
	int i, flag[MAX], c, brkt, size;
	char ch;
	void hlp(void);
	for(i=0; i<MAX ;i++)
	{
		num[i]=getch();
		if((num[i]>='0' && num[i]<='9') || num[i]=='z' || num[i]=='l' || num[i]=='i' || num[i]=='+' || num[i]=='-' || num[i]=='*' || num[i]=='/' || num[i]=='(' || num[i]==')' || num[i]=='s' || num[i]=='c' || num[i]=='t' || num[i]=='e' || num[i]=='p' || num[i]=='u' || num[i]=='X' || num[i]=='.' || num[i]==' ' || num[i]=='\r' || num[i]=='\b' || num[i]=='<' || num[i]=='>')
		{
			if(num[i]=='\r') break;
			if(num[i]=='s' || num[i]=='c' || num[i]=='t' || num[i]=='u' || num[i]=='e' || num[i]=='p')
			{
				flag[i]=3;  // three character long names
				switch(num[i])
				{
					case 's': cprintf("sin"); break;
					case 'c': cprintf("cos"); break;
					case 't': cprintf("tan"); break;
					case 'e': cprintf("exp"); break;
					case 'p': cprintf("ypx"); break;
					case 'u': cprintf("urt"); break;
				}
			}
			else if(num[i]=='l')
			{
				flag[i]=2;
				putch(num[i]);
				ch=getch();
				switch(ch)
				{
					case 'g' : putch(ch); num[i]='d'; break;
					case 'n' : putch(ch); num[i]='l'; break;
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
					case 's' : cprintf("sin"); num[i]='q'; break;
					case 'c' : cprintf("cos"); num[i]='a'; break;
					case 't' : cprintf("tan"); num[i]='r'; break;
					default  : printf("\b \b"); num[i]=num[i-1]; i--; break;
				}
			}
			else if(num[i]=='\b')
			{
				if(i>0)
				{
					for(c=0; c<flag[i-1]; c++)
						printf("\b \b");
					i-=2;
				}
				else i = -1;
			}
			else if(num[i]=='<')
			{
				// c = i-1;
				// for(brkt=0; brkt<flag[c] ;brkt++)
				// 	printf("\b");



			}
			else if(num[i]=='>')
			{

			}
			else { flag[i]=1; putch(num[i]); }
		}
		else if(num[i]==59) { i--; hlp(); refresh(); }
		else { printf("\a"); i--; }
	}
	num[i]='\0';
	printf("\n");
}

void hlp()
{
	// void helptxt(void);
	char ch='z';
	clrscr();
	// helptxt();
	_setcursortype(0);
	gotoxy( 24, 6);
	// cprintf((grid==1) ? "\aOn " : "Off");
	while(ch!=ESC)
	{
		ch='\0';
		ch=getch();
		if(ch=='G')
		{
			// grid *= -1;
			gotoxy( 24, 6);
			// cprintf((grid==1) ? "\aOn " : "Off");
		}
	}
	clrscr();
	_setcursortype(2);
	fflush(0);
	return;
}

void clstr(short int init_row, short int rows)
{
	int j;
	gotoxy(1, init_row);
	for(j=0; j<80*rows; j++)
		printf(" ");
	gotoxy(1, init_row);
	return;
}
