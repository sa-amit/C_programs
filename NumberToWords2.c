# include <stdio.h>
/* 18-7-2002 */

void word(char num[20])                 		/* function to convert numbers less than  one trillion into words */
{
	short int i, c, pos, init, temp, tag1=0, tag2=0, tag3=0;
	for(pos=0; num[pos] != '\0' ; pos++)        	/* counting number of digits (upto the point, if present)*/
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
	init=pos;
	for(i=0; i<=pos/2; i++)
	{	     					/*arranging digits in reverse order (upto the point, if present) inside the array*/
		temp=num[i];                      	/*so that lower position is at lower subscript of array*/
		num[i]=num[pos-i];
		num[pos-i]=temp;
	}
	for( ; pos>=0 ; pos--)                       	/*last position has null character*/
	{
		if(pos==1 || pos==4 || pos==7 || pos==10)
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
				pos--;			  			/*check next position*/
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
		if(pos==0 || pos==2 || pos==3 || pos==5 || pos==6 || pos==8 || pos==9 || pos==11)
		{
			if(num[pos+1]-'0' != 1  || pos%3==2)
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
				if(num[pos]!='0' && pos%3==2)
				{
					printf(" hundred");
					if(num[pos-1] != '0' || num[pos-2] != '0')
						printf(" and");
				}
				if(pos==2 && num[2]=='0' && (num[1]!='0' || num[0]!='0')) printf(" and");
			}
		}                                                                                  /*if any of three places for which the*/
		if(pos%3==0)                                                                       /*suffix stands for has non zero value then print the suffix */
		{                                                                            	   /* tags used for problem "one lakh,, four hundred and three only."*/
			if((num[pos+2]-'0' || num[pos+1]-'0' || num[pos]-'0') && pos==3)
			{
				printf(" thousand");
				tag1=1;
			}
			if((num[pos+2]-'0' || num[pos+1]-'0' || num[pos]-'0') && pos==6)
			{
				printf(" million");
				tag2=1;
			}
			if((num[pos+2]-'0' || num[pos+1]-'0' || num[pos]-'0') && pos==9)
			{
				printf(" billion");
				tag3=1;
			}
		}								   	/* num[pos]-'0' should have non zero value */
		for(c=0, i=pos; i>=0; i--)
			if(num[i]-'0'==0) c++;                           	   	/*if <<not required>> (one preceding digit | since pos--; in case of 'twenty',  'thirty' etc. printing block will never allow pos to be in middle of triplet having same suffix when control reaches here), present digit and all following digits are zero, then break*/
		if(c==pos+1) break;  							/*checking for last two preceding digits to be non zero is not required since is pos%3==0, suffix would already have been printed*/
		for(c=0, i=pos-1; i>=2; i--)
			if(num[i]-'0'==0) c++;
		if(c!=pos-2)                                           			/* To correct "one thousand, and one" type of problem*/
			if((tag1 && pos==3) || (tag2 && pos==6) || (tag3 && pos==9))
				printf(",");   						/* print comma after suffix only if following digits are not all zero */
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
	return;
}

						      /* Improvements*/	  /*>Done> Accepts numbers in the range of 10 raised to 12 and less than 10 raised to -12 */
									  /*>Done> No other letter except the first one is capital even in multi crore numbers */
void main()                                                               /*>Done> Stops scanning the number if any non digit character except `,' or ` ' is encountered*/
{                                                                         /*>Done> Prints ".. point zero zero .." even if only zeroes are there after the point*/
	char num[30];                                             	  /*>Done> Prints "Zero point ..." even if number starts with only a point*/
	short int c, pos, tag;						  /*>Done> Upper case for first letter of first word*/
	clrscr();                                                         /*>Done> Provision for values with decimal point*/
	printf("\n\t\t\t\t..In words..");
	printf("\n\n * Enter number : ");                                 /*> Not Done>Option of repeating the program*/
	scanf("%[1234567890,. ]", num);                                   /*>Done> Accepts numbers with commas and white space between digits*/
	for(tag=0, pos=0; tag<strlen(num); tag++)                         /*>Done> Warns if there are more than one decimal points, and deletes the second point*/
	{                                                                 /*>Done> If no digit is there after the point, does not print the word "point" */
		if(num[tag]=='.')
		{
			if(pos==0) pos=1;
			else
			{
				printf("\n\n   Error!   More than one decimal point `.' ");
				num[tag]=' ';
			}
		}
		if(num[tag]==',' || num[tag]==' ')
		{
			for(c=tag; c<strlen(num)-1; c++)
				num[c]=num[c+1];
			num[strlen(num)-1]='\0';               /* reducing the elements of num by one, by converting the last ch. into null ch. */
			tag--;                                 /* decreasing i so that checking starts from new character in the place of old one */
		}
	}
	for(pos=0; num[pos] != '\0' ; pos++)        	      /*counting number of digits*/
		if(num[pos]=='.') break;
	pos--;
	printf("\n\n ¯ ");
	c=0;
	while(num[c]=='0')
		c++;
	if (c==pos+1) printf(" Zero");
	word(num);
	printf(" only.");
	getch();
}



