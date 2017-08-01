#include<string.h>
#include"include.h"
#include"menu_m.h"
#include"file.h"

void login(char a)
{
	char name_M[4]={"xqq"};
	char passwd_M[4]={"123"};
	char inname[NAME_LEN]={'\0'};
	char inpasswd[PASSWD_LEN]={'\0'};
	int flag=0;

	printf("请输入用户名:\n");
	Mygets(inname,NAME_LEN);
	printf("请输入密码\n");
	Mygets(inpasswd,PASSWD_LEN);
	
	if(a=='m')
	{
		if(strcmp(name_M,inname)!=0||strcmp(passwd_M,inpasswd)!=0)
		{
			printf("登录失败，请重新登录\n");
			printf("按下回车键继续");//待改善
			while(getchar()!='\n');
		}
		else
		{
			manager_menu();
		}
	}
	else if(a=='t')
	{
		tea *l=readfile_t();
		//找到登录用户的所在信息
		while(l->next!=NULL)
		{
			if(strcmp(l->next->tdata.name,inname)==0)
			{
				flag=1;
				break;
			}
			else
			{
				flag=2;
				l=l->next;
			}
		}
		//找不到该用户名
		if(flag==2)
		{
			printf("没有该用户\n");
			return ;
		}
		else
		{
			if(strcmp(l->next->tdata.name,inname)!=0||strcmp(l->next->tdata.pwd,inpasswd))
			{
				printf("登录失败，请重新登录\n");
				printf("按下回车键继续");
				while(getchar()!='\n');
			}
			else
			{
				teacher_menu(l->next->tdata.pwd,l->next->tdata.id);
			}
		}

	}
	else if(a=='s')
	{
		stu *l=readfile_s();
		while(l->next!=NULL)
		{
			if(strcmp(l->next->sdata.name,inname)==0)
			{
				flag=1;
				break;
			}
			else
			{
				flag=2;
				l=l->next;
			}
		}
		if(flag==2)
		{
			printf("没有该用户\n");
			return ;
		}
		else
		{
			if(strcmp(l->next->sdata.name,inname)!=0||strcmp(l->next->sdata.pwd,inpasswd))
			{
				printf("登录失败，请重新登录\n");
				printf("按下回车键继续");
				while(getchar()!='\n');
			}
			else
			{
				student_menu(l->next->sdata.pwd,l->next->sdata.id);
			}
		}

	}
}
