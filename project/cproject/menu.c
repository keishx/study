#include"include.h"
#include"login.h"
#include"menu.h"

void menu()
{
	char ch='0';
	while(1)
	{	
		system("clear");
		//登录
		printf(
				"\t\t**********************************************\n"
				"\t\t\t *^_^*欢迎进入管理系统*^_^* \n\n"
				"\t\t\t\t1--管理员\n"
				"\t\t\t\t2--教师\n"
				"\t\t\t\t3--学生\n"
				"\t\t\t\tq--退出\n"
				"\t\t**********************************************\n");
		printf("请选择你要登录的用户：");
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch)
		{
			case '1':
				//管理员
				manager();
				break;
			case '2':
				//教师
				teacher();
				break;
			case '3':
				//学生
				student();
				break;
			case 'q':
				//退出
				return;
		}
		printf("按回车键继续\n");
		while(getchar()!='\n');
	}	
}

void manager()
{
	//定义管理员姓名与密码
	char a='m';
	//判断登录是否成功
	login(a);
}

void teacher()
{
	char a='t';
	login(a);
}

void student()
{
	char a='s';
	login(a);
}
