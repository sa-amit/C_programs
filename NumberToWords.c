# include <stdio.h>
/* 18-7-2002 */

void word1(char []);


void word1_(char num[], int flag)                 	/* function to convert numbers less than  one crore into words */
{                                                       /*flag used to avoid first letter after the `crore' part to be capital in case number has more than 7 digits */
	short int i, c, pos, temp, init, tag2=0, tag3=0;
	for(pos=0; num[pos] != '\0' ; pos++)        	/*counting number of digits (upto the point, if present)*/
	{
		if(num[pos]=='.')
		{
			if(pos==0)                      /* if point lies at initial position, add zero initially and shift all characters towards right*/
			{                                         /* Note : above check could have been done in function main  also */
				for(i=strlen(num); i>=0; i--)
					num[i+1]=num[i];
				num[0]='0';             /* pos++; statement could have been added after "num[pos]='0';" so that first digit after the point is checked in next loop*/
			}                               /* pos++; is not essential because of check "if(pos==0)" */
			break;                          /* Break from 'for' loop */
		}
	}
	pos--;
	if(flag==0) init=pos;
	else init=7;                                    /*pos will never be 7 */
	for(i=0; i<=pos/2; i++)
	{	     					/*arranging digits in reverse order (upto the point, if present) inside the array*/
		temp=num[i];                      	/*so that lower position is at lower subscript of array*/
		num[i]=num[pos-i];
		num[pos-i]=temp;
	}
	for( ; pos>=0 ; pos--)                       /*last position has null character*/
	{
		if(pos==1 || pos==4 || pos==6)
		{

			if(pos!=init)
			{
				if(num[pos]-'0'==2) printf(" twenty");
				if(num[pos]-'0'==3) printf(" thirty");
				if(num[pos]-'0'==4) printf(" forty");
				if(num[pos]-'0'==5) printf(" fifty");
				if(num[pos]-'0'==6) printf(" sixty");
				if(num[pos]-'0'==7) printf(" seventy");
				if(num[pos]-'0'==8) printf(" eighty");
				if(num[pos]-'0'==9) printf(" ninety");
			}
			if(pos==init)
			{
				if(num[pos]-'0'==2) printf(" Twenty");
				if(num[pos]-'0'==3) printf(" Thirty");
				if(num[pos]-'0'==4) printf(" Forty");
				if(num[pos]-'0'==5) printf(" Fifty");
				if(num[pos]-'0'==6) printf(" Sixty");
				if(num[pos]-'0'==7) printf(" Seventy");
				if(num[pos]-'0'==8) printf(" Eighty");
				if(num[pos]-'0'==9) printf(" Ninety");
			}
			if(num[pos]-'0'==1)
			{
				pos--;			  /*check next position*/
				if(pos!=init-1)
				{
					if(num[pos]-'0'==0) printf(" ten");
					if(num[pos]-'0'==1) printf(" eleven");
					if(num[pos]-'0'==2) printf(" twelve");
					if(num[pos]-'0'==3) printf(" thirteen");
					if(num[pos]-'0'==4) printf(" fourteen");
					if(num[pos]-'0'==5) printf(" fifteen");
					if(num[pos]-'0'==6) printf(" sixteen");
					if(num[pos]-'0'==7) printf(" seventeen");
					if(num[pos]-'0'==8) printf(" eighteen");
					if(num[pos]-'0'==9) printf(" nineteen");
				}
				if(pos==init-1)
				{
					if(num[pos]-'0'==0) printf(" Ten");
					if(num[pos]-'0'==1) printf(" Eleven");
					if(num[pos]-'0'==2) printf(" Twelve");
					if(num[pos]-'0'==3) printf(" Thirteen");
					if(num[pos]-'0'==4) printf(" Fourteen");
					if(num[pos]-'0'==5) printf(" Fifteen");
					if(num[pos]-'0'==6) printf(" Sixteen");
					if(num[pos]-'0'==7) printf(" Seventeen");
					if(num[pos]-'0'==8) printf(" Eighteen");
					if(num[pos]-'0'==9) printf(" Nineteen");
				}
			}
			else pos--;      				/*if current digit is not 1 and digit at next lower place is zero*/
		}
		if(pos==0 || pos==2 || pos==3 || pos==5)
		{
			if(num[pos+1]-'0' != 1  || pos==2)
			{
				if(pos!=init)
				{
					if(num[pos]-'0'==1) printf(" one");
					if(num[pos]-'0'==2) printf(" two");
					if(num[pos]-'0'==3) printf(" three");
					if(num[pos]-'0'==4) printf(" four");
					if(num[pos]-'0'==5) printf(" five");
					if(num[pos]-'0'==6) printf(" six");
					if(num[pos]-'0'==7) printf(" seven");
					if(num[pos]-'0'==8) printf(" eight");
					if(num[pos]-'0'==9) printf(" nine");
				}
				if(pos==init)
				{
					if(num[pos]-'0'==1) printf(" One");
					if(num[pos]-'0'==2) printf(" Two");
					if(num[pos]-'0'==3) printf(" Three");
					if(num[pos]-'0'==4) printf(" Four");
					if(num[pos]-'0'==5) printf(" Five");
					if(num[pos]-'0'==6) printf(" Six");
					if(num[pos]-'0'==7) printf(" Seven");
					if(num[pos]-'0'==8) printf(" Eight");
					if(num[pos]-'0'==9) printf(" Nine");
				}
			}
		}                                                                                  /*if either of two places for which the*/
		if((num[pos+1]-'0' || num[pos]-'0') && pos==5)
		{
			printf(" lakh");
			tag3=1;
		}    	   					/*suffix stands for has non zero value then print the suffix */
		if((num[pos+1]-'0' || num[pos]-'0') && pos==3)
		{
			printf(" thousand");
			tag2=1;
		}      						/* tags used for problem "one lakh,, four hundred and three only."*/
		if(num[pos]-'0' && pos==2)  printf(" hundred");   	     	   /* num[pos]-'0' should have non zero value */
		if(pos==2)
			if(num[0]-'0'!= 0 || num[1]-'0' != 0)                    	   /* check whether last two digits are non zero*/
				printf (" and");
		for(c=0, i=pos-1; i>=0; i--)
			if(num[i]-'0'==0) c++;                           /*if all following digits are zero, then break*/
		if(c==pos) break;
		for(c=0, i=pos-1; i>=2; i--)
			if(num[i]-'0'==0) c++;
		if(c!=pos-2)                                           /* To correct "one thousand, and one" type of problem*/
			if((tag2 && pos==3) || (tag3 && pos==5)) printf(",");     /* print comma after suffix only if following digits are not all zero */
	}
	for(c=0, i=0, temp=0; i<strlen(num); i++)
	{
		if(num[i]=='.')
		{
			temp=1;
			c=i;
		}
	}
	if(temp)
	{
		for(temp=0, i=c+1; i<strlen(num); i++)           /* if some digits are there after the point */
			if(num[i]!='0') temp=1;
		if(temp)
		{
			printf("  point ");
			for(pos=c+1; pos<strlen(num); pos++)
			{
				if(num[pos]-'0'==0) printf(" zero");
				if(num[pos]-'0'==1) printf(" one");
				if(num[pos]-'0'==2) printf(" two");
				if(num[pos]-'0'==3) printf(" three");
				if(num[pos]-'0'==4) printf(" four");
				if(num[pos]-'0'==5) printf(" five");
				if(num[pos]-'0'==6) printf(" six");
				if(num[pos]-'0'==7) printf(" seven");
				if(num[pos]-'0'==8) printf(" eight");
				if(num[pos]-'0'==9) printf(" nine");
			}
		}
	}
	return;
}
						      /* Improvements*/	  /*>Done> Accepts numbers in the range of 10 raised to 12 and less than 10 raised to -12 */
									  /*>Done> Upper case for first letter of first word.*/
									  /*>Done> No other letter except the first one is in upper case even in multi crore numbers */
void main()                                                               /*>Done> Stops scanning the number if any non digit character except <,> or <blank>  is encountered*/
{                                                                         /*>Done> Does not print ".. point zero zero .." if only zeroes are there after the point or if no digit is there after the point.*/
	char number[25], ch;                                              /*>Done> Prints "Zero point ..." even if number starts with only a point.*/
	clrscr();                                                         /*>Done> Provision for values with decimal point.*/
	printf("\n\t\t\t\t..In words..");                                 /*>Done> Option of repeating the program.*/
	repeat:                                                           /*>Done> Accepts numbers with commas and white space between digits.*/
	do {                                                              /*>Done> Warns if there are more than one decimal points, and deletes the second point*/
	printf("\n\n * Enter number : ");
	scanf("\n");
	scanf("%[1234567890,. ]", number);
	word1(number);
	printf("\n\n ¨ Do you want to repeat ? (y/n) : ");
	scanf("\n");
	ch=getchar();
	   }	while(ch=='y' || ch=='Y');
	printf("\n\n * Goodbye!");
	getch();
}

void word1(char num[])
{
	char cr[10];
	short int c, pos, tag, flag;
	void word1_(char [], int);
	for(flag=0, tag=0, pos=0; tag<strlen(num); tag++)
	{                                                      /* Deleting white space and commas from the number */
		if(num[tag]=='.')
		{
			if(pos==0) pos=1;
			else
			{
				printf("\n\n   Error!   More than one decimal point '.' ");
				num[tag]=' ';
			}
		}
		if(num[tag]==',' || num[tag]==' ')
		{
			for(c=tag; c<strlen(num)-1; c++)
				num[c]=num[c+1];
			num[strlen(num)-1]='\0';               /* Reducing the elements of num by one, by converting the last ch. into null ch. */
			tag--;                                 /* Decreasing i so that checking starts from new character in the place of old one */
		}
	}
	for(pos=0; num[pos] != '\0' ; pos++)        	       /*Counting number of digits*/
		if(num[pos]=='.') break;
	pos--;
	printf("\n\n ¯ ");
	tag=0;
	while(num[tag]=='0')
		tag++;
	if(tag==pos+1 && pos<=6) printf(" Zero");
	if(pos>6)                                                            /* To allow numbers greater than 9 digits */
	{                                                                    /*Note : Number is stored from left to right i.e. highest position has lowest subscript (zero) */
		for(c=0 ; pos-6 > 0 ; pos--)                                 /* After reversal in function 'word' order is reversed*/
		{
			cr[c]=num[0];
			c++;
			for(tag=0; tag<strlen(num); tag++)
				num[tag]=num[tag+1];
		}
		cr[c]='\0';
		word1_(cr, flag);
		printf(" crore");
		flag=1;
		for(c=0, tag=0; c<=pos-2; c++)            	             /* Put a comma after crore if any of the digits except the last two in 'num' are non zero */
			if(num[c] != '0') tag=1;
		if (tag) printf(", ");
	}
	word1_(num, flag);
	printf(" only.");
	return;
}



