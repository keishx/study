#include<stdio.h>
 int main()
{
    char a='+',b='\0';
	float num1=0,num2=0,re=0;
	printf("请输入你要计算的式子：");
	scanf("%f%c%f%c",&num1,&a,&num2,&b);
	getchar();
			ji(num1,a,num2);
	while(b!='=')
	{			scanf("%c%f",&a,&num2);
			ji(re,a,num2);}
		
			
	if(b=='=')		printf("得数：%f\n",re);
			return 0;
	}


float ji(float num1,char a,float num2)
{	float re;
	if(a=='+')
	re=num1+num2;
	else if(a=='-')
	re=num1-num2;
	else if(a=='*')
	re=num1*num2;
	else if(a=='/')
	re=num1/num2;
	return re;
	}
								                                                                              
							                           
