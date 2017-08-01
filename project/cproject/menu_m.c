#include"include.h"
#include"function.h"
#include"file.h"

void manager_menu() 
{
	agree();
	while(1)
	{	
		system("clear");

		printf(
				"\t\t**********************************************\n"
				"\t\t\t *^_^*欢迎进入管理员界面*^_^* \n\n"
				"\t\t\t\t1--录入教师信息			\n"
				"\t\t\t\t2--修改教师信息			\n"
				"\t\t\t\t3--查看教师信息			\n"
				"\t\t\t\t4--删除教师信息			\n"
				"\t\t\t\t5--注销				\n\n"
				"\t\t**********************************************\n");

		printf("请输入你的选择：");
		char ch='0';
		int  id=0;
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch){
			//教师信息的录入（工号，姓名，职务，科目，留言板块，辞职是否成功的标志位）
			case '1':
				addteacher();
		break;
			//修改教师信息
			case '2':
				update_t();
				break;
	
			//查看教师信息
			case '3':
				print_t();
				break;
			case '4':
			//删除教师信息
				printf("请输入要删除的id:");
				scanf("%d",&id);
				while(getchar()!='\n');
				delete_t(id);
				break;
			//注销，返回登录界面
			case '5':
				return ;
		}
		printf("按回车键继续\n");
		while(getchar()!='\n');
	}
}

void teacher_menu(char *passwd,int id)
{
	while(1)
	{
		system("clear");
		tea *l=readfile_t();
		tea *head=l;
		char a='0';
		int k=job(id);
		while(l->next->tdata.id!=id)
		{
			l=l->next;
		}
		//辞职提交是否被同意
		if(l->next->tdata.agree==1)
		{
			printf("您的辞职申请已同意，此次为最后一次登录\n");
			printf("按任意键退出登录\n");
			getchar();
			delete_t(id);
			return;
		}
	
		if(k==1)
		{
			while(1)
			{
				system("clear");
				printf("\t\t**********************************************\n"
						"\t\t\t *^_^*欢迎进入班主任界面*^_^* \n\n"
						"\t\t\t\t1--录入学生信息\n"
						"\t\t\t\t2--修改学生信息\n"
						"\t\t\t\t3--查看学生信息\n"
						"\t\t\t\t4--删除学生信息\n"
						"\t\t\t\t5--查看排名\n"
						"\t\t\t\t6--修改登录密码\n"
						"\t\t\t\t7--辞职\n"
						"\t\t\t\t8--查看留言\n"
						"\t\t\t\t9--注销\n\n"
						"\t\t**********************************************\n");
				printf("请输入你的选择：");
				char ch='0';
				char p='0';
				tea *l=readfile_t();
				scanf("%c",&ch);
				while(getchar()!='\n');
				switch(ch)
				{	//显示辞职请求信息，申请同意，只能登录最后一次，删除该教师信息，保存信息
					case '1':
					//录入学生信息
						addstudent();
						break;
					case '2':
						update_s();
						break;
					case '3':
					//查看学生信息
						print_s();
						//按姓名查看的函数
						break;
					case '4':
					//删除学生信息
						delete_s();
						break;
						//保存
					case '5':
					//查看排名
						printf("1--查看学号排名\n"
								"2--查看成绩排名\n"
								"请输入你的选择：");
						scanf("%c",&p);
						while(getchar()!='\n');
						//学号排序
						if(p=='1')
							sort_id();
						//学号排序
						else if(p=='2')
							sort_s();
						break;
					case '6':
					//修改自己的登录密码
						chang_t(passwd);
						break;
					case '7':
					//辞职
						while(l->next->tdata.id!=id)
						{
							l=l->next;
						}
						if(l->next->tdata.resign==1)
						{
							printf("您的辞职申请正在审核中，请等待\n");
						}
						else if(l->next->tdata.resign==2)
						{
							printf("您的辞职申请未被同意\n");
						}
						else
						{		
							resign(id);
						}
						break;
					case '8':
						left_l(id);
						break;
					case '9':
						return;
				}		//注销（返回登录界面）
				printf("按回车键继续\n");
				while(getchar()!='\n');
			}			
		}
		else if(k==2)
		{
			system("clear");
			printf("\t\t**********************************************\n"
					"\t\t\t *^_^*欢迎进入教师界面*^_^* \n\n"
					"\t\t\t\t1--查看学生数学分数\n"
					"\t\t\t\t2--修改学生数学分数\n"
					"\t\t\t\t3--查看学生数学成绩排名\n"
					"\t\t\t\t4--修改登录密码\n"
					"\t\t\t\t5--辞职\n"
					"\t\t\t\t6--查看留言\n"
					"\t\t\t\t7--注销\n"
					"\t\t**********************************************\n");
			printf("请输入你的选择：");
	
			char ch='0';
			char p='0';
			tea *l=readfile_t();
			scanf("%c",&ch);
			while(getchar()!='\n');
			switch(ch)
				{	//显示辞职请求信息，申请同意，只能登录最后一次，删除该教师信息，保存信息
					case '1':
						print_m();
						break;
					case '2':
						update_m();
						break;
					case '3':
						sort_m();
						break;
					case '4':
						chang_t(passwd);
						break;
					case '5':
					//辞职
						while(l->next->tdata.id!=id)
						{
							l=l->next;
						}
						if(l->next->tdata.resign==1)
						{
							printf("您的辞职申请正在审核中，请等待\n");
						}
						else if(l->next->tdata.resign==2)
						{
							printf("您的辞职申请未被同意\n");
						}
						else
						{		
							resign(id);
						}
						break;
					case '6':
						left_l(id);
						break;
					case '7':
						return;
				}	
						
				printf("按回车键继续\n");
				while(getchar()!='\n');
		}
		else if(k==3)
		{
			system("clear");
			printf("\t\t**********************************************\n"
					"\t\t\t *^_^*欢迎进入教师界面*^_^* \n\n"
					"\t\t\t\t1--查看学生语文分数\n"
					"\t\t\t\t2--修改学生语文分数\n"
					"\t\t\t\t3--查看学生语文成绩排名\n"
					"\t\t\t\t4--修改登录密码\n"
					"\t\t\t\t5--辞职\n"
					"\t\t\t\t6--查看留言\n"
					"\t\t\t\t7--注销\n"
					"\t\t**********************************************\n");
			printf(	"请输入你的选择：");
	
			char ch='0';
			char p='0';
			tea *l=readfile_t();
			scanf("%c",&ch);
			while(getchar()!='\n');
			switch(ch)
				{	//显示辞职请求信息，申请同意，只能登录最后一次，删除该教师信息，保存信息
					case '1':
						print_c();
						break;
					case '2':
						update_c();
						break;
					case '3':
						sort_c();
						break;
					case '4':
						chang_t(passwd);
						break;
					case '5':
					//辞职
						while(l->next->tdata.id!=id)
						{
							l=l->next;
						}
						if(l->next->tdata.resign==1)
						{
							printf("您的辞职申请正在审核中，请等待\n");
						}
						else if(l->next->tdata.resign==2)
						{
							printf("您的辞职申请未被同意\n");
						}
						else
						{		
							resign(id);
						}
						break;
					case '6':
						left_l(id);
						break;
					case '7':
						return;
				}	
				printf("按回车键继续\n");
				while(getchar()!='\n');
		}				
	}
}	
void student_menu(char *passwd,int id)
{
	while(1)
	{
		system("clear");
		printf("\t\t**********************************************\n"
				"\t\t\t *^_^*欢迎进入学生界面*^_^* \n\n"
				"\t\t\t\t1--查看成绩\n"
				"\t\t\t\t2--修改密码\n"
				"\t\t\t\t3--留言\n"
				"\t\t\t\t4--注销\n"
				"\t\t**********************************************\n");
		printf("请输入你的选择：");
		char ch='0';
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch)
		{
			case '1':
				person(id);
				break;
		//查看自己的信息（总分排名）
			case '2':
		//修改自己的登录密码
				chang_s(passwd);
				break;
			case '3':
			//给老师留言功能
				left_w();
				break;
			case '4':
			//注销
				return;
		}
		printf("按回车键继续\n");
		while(getchar()!='\n');

	}
}
