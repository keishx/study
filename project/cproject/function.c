#include<string.h>
#include"include.h"
#include"file.h"
#include"function.h"

//保存
void save_t(tea *head)
{
//	tea	*head=(tea *)malloc(sizeof(tea));
		//stu *head=(stu *)malloc(sizeof(stu));
	
	int flag=1;
	while(flag)
	{
		char ch='0';
		printf("1--保存\n"
				"2--不保存\n"
				"请输入你的选择：");
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch)
		{
			case '1':
				writefile_t(head);
				printf("保存成功！\n");
				flag=0;
				break;
			case '2':
				flag=0;
				break;
			default:
				flag=1;
				printf("your choose is error");
		}

	}
}
//学生保存
void save_s(stu *head)
{
	int flag=1;
	while(flag)
	{
		char ch='0';
		printf("1--保存\n"
				"2--不保存\n"
				"请输入你的选择：");
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch)
		{
			case '1':
				writefile_s(head);
				printf("保存成功！\n");
				flag=0;
				break;
			case '2':
				flag=0;
				break;
			default:
				flag=1;
				printf("your choose is error");
		}

	}
}
//添加学生
void addstudent()
{
	stu *head=readfile_s();
	stu *l=head;
	stu *temp=(stu*)malloc(sizeof(stu));
	if(temp==NULL)
	{
		printf("fail\n");
		return;
	}
	temp->next=NULL;
	//依次输入信息
	printf("input student id:");
	scanf("%d",&temp->sdata.id);
	while(getchar()!='\n');

	//判断id是否与已有id相同
	while(l->next!=NULL)
	{
		if(l->next->sdata.id==temp->sdata.id)
		{
			printf("id已存在！\n"
					"按回车键退出\n");
			while(getchar()!='\n');
			return;
		}
			l=l->next;
	}
	
	printf("input student name:");
	Mygets(temp->sdata.name,NAME_LEN);
	
	printf("input student passwd:");
	Mygets(temp->sdata.pwd,PASSWD_LEN);
	
	printf("input student math score:");
	scanf("%f",&temp->sdata.math);
	while(getchar()!='\n');
	
	printf("input student chinese score:");
	scanf("%f",&temp->sdata.chinese);
	while(getchar()!='\n');
	//头插法放入链表中
	if(head->next!=NULL)
	{
		temp->sdata.sum=temp->sdata.math+temp->sdata.chinese;
		temp->next=head->next;
		head->next=temp;
	}
	else
	{
		temp->sdata.sum=temp->sdata.math+temp->sdata.chinese;
		head->next=temp;
	}
	save_s(head);
	//将链表写入文件存储起来
	return;
}
//添加教师信息
void addteacher()
{
	//将已有信息读出，存储在链表中
	tea *head=readfile_t();
	tea *l=head;
	tea *temp=(tea*)malloc(sizeof(tea));
	if(temp==NULL)
	{
		printf("fail\n");
		return;
	}
	temp->next=NULL;
	//输入信息
	printf("input teacher id:");
	scanf("%d",&temp->tdata.id);
	while(getchar()!='\n');
	//判断id是否与已有id相同
	while(l->next!=NULL)
	{
		if(l->next->tdata.id==temp->tdata.id)
		{
			printf("id已存在！\n"
					"按回车键退出\n");
			while(getchar()!='\n');
			return;
		}
			l=l->next;
	}

	printf("input teacher name:");
	Mygets(temp->tdata.name,NAME_LEN);
	
	printf("input teacher passwd:");
	Mygets(temp->tdata.pwd,PASSWD_LEN);
	
	printf("input teacher's job:");
	Mygets(temp->tdata.job,JOB_LEN);

	
	
	//头插
	if(head->next!=NULL)
	{
		temp->next=head->next;
		head->next=temp;
	}
	else
	{
		head->next=temp;
	}
	save_t(head);
	//存储
	//writefile_t(head);
	return;
}
//打印学生信息
void print_s()
{
	stu *head=readfile_s();
	if(head->next==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t密码\t数学\t语文\t总分\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.pwd,head->next->sdata.math,head->next->sdata.chinese,head->next->sdata.sum);
		head=head->next;
	}
	printf("\n");
	return;
}
//打印学生数学信息
void print_m()
{
	stu *head=readfile_s();
	if(head->next==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t数学\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math);
		head=head->next;
	}
	printf("\n");
	return;
}
//打印学生语文信息
void print_c()
{
	stu *head=readfile_s();
	if(head->next==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t语文\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.chinese);
		head=head->next;
	}
	printf("\n");
	return;
}
//打印教师信息
void print_t()
{
	tea *head=readfile_t();
	if(head->next==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("工号\t姓名\t密码\t职务\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%s\t%s\n",head->next->tdata.id,head->next->tdata.name,head->next->tdata.pwd,head->next->tdata.job);
		head=head->next;
	}
	printf("\n");
	return;
}

//修改教师信息
void update_t()
{
	int  ch;
	int flag=0;
	printf("input teacher id you want to update:");
	scanf("%d",&ch);
	while(getchar()!='\n');
	tea *l=readfile_t();
	tea *head=l;
	while(l->next!=NULL)
	{
		if(l->next->tdata.id==ch)
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
			printf("no message\n");
			return;
		}
		else
		{
			printf("the message of this teacher is:\n");
			printf("工号\t姓名\t密码\t职务\n");
		//	printf("123");
			printf("%3d\t%s\t%s\t%s\n",l->next->tdata.id,l->next->tdata.name,l->next->tdata.pwd,l->next->tdata.job);
			printf("请输入更改信息：\n");
			printf("name:\n");
			scanf("%s",l->next->tdata.name);
			while(getchar()!='\n');
			printf("passwd:\n");
			scanf("%s",l->next->tdata.pwd);
			while(getchar()!='\n');
			printf("job:\n");
			scanf("%s",l->next->tdata.job);
			while(getchar()!='\n');

			save_t(head);

		}
		return;
}
//修改学生信息
void update_s()
{
	int  ch;
	int flag=0;
	printf("input student id you want to update:");
	scanf("%d",&ch);
	while(getchar()!='\n');
	stu *l=readfile_s();
	stu *head=l;
	while(l->next!=NULL)
	{
		if(l->next->sdata.id==ch)
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
			printf("no message\n");
			return;
		}
		else
		{
			printf("the message of this student is:\n");
			printf("学号\t姓名\t密码\t数学\t语文\n");
		//	printf("123");
			printf("%d\t%s\t%s\n",l->next->sdata.id,l->next->sdata.name,l->next->sdata.pwd);
			printf("请输入更改信息：\n");
			printf("name:\n");
			scanf("%s",l->next->sdata.name);
			while(getchar()!='\n');
			printf("passwd:\n");
			scanf("%s",l->next->sdata.pwd);
			while(getchar()!='\n');
			printf("math score:\n");
			scanf("%f",&l->next->sdata.math);
			while(getchar()!='\n');
			printf("chinese score:\n");
			scanf("%f",&l->next->sdata.chinese);
			while(getchar()!='\n');
			l->next->sdata.sum=l->next->sdata.math+l->next->sdata.chinese;
			save_s(head);

		}
		return;
}
//修改学生数学成绩
void update_m()
{
	int  ch;
	int flag=0;
	printf("input student id you want to update:");
	scanf("%d",&ch);
	while(getchar()!='\n');
	stu *l=readfile_s();
	stu *head=l;
	while(l->next!=NULL)
	{
		if(l->next->sdata.id==ch)
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
			printf("no message\n");
			return;
		}
		else
		{
			printf("the message of this student is:\n");
			printf("学号\t姓名\t数学\n");
			printf("%d\t%s\t%f\n",l->next->sdata.id,l->next->sdata.name,l->next->sdata.math);
			printf("请输入更改信息：\n");
			printf("math score:\n");
			scanf("%f",&l->next->sdata.math);
			while(getchar()!='\n');
			save_s(head);

		}
		return;
}
//修改学生语文成绩
void update_c()
{
	int  ch;
	int flag=0;
	printf("input student id you want to update:");
	scanf("%d",&ch);
	while(getchar()!='\n');
	stu *l=readfile_s();
	stu *head=l;
	while(l->next!=NULL)
	{
		if(l->next->sdata.id==ch)
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
			printf("no message\n");
			return;
		}
		else
		{
			printf("the message of this student is:\n");
			printf("学号\t姓名\t语文\n");
			printf("%d\t%s\t%f\n",l->next->sdata.id,l->next->sdata.name,l->next->sdata.chinese);
			printf("请输入更改信息：\n");
			printf("chinese score:\n");
			scanf("%f",&l->next->sdata.chinese);
			while(getchar()!='\n');
			save_s(head);

		}
		return;
}
//教师修改登录密码
void chang_t(char *passwd)
{
	tea *l=readfile_t();
	tea *head=l;
	char inpasswd[PASSWD_LEN]={'\0'};
	printf("请输入原密码：");
	Mygets(inpasswd,PASSWD_LEN);
	if(strcmp(inpasswd,passwd)==0)
	{
		while(1)
		{
			char temp1[PASSWD_LEN]={'\0'};
			char temp2[PASSWD_LEN]={'\0'};
			printf("请输入你要更改的密码：");
			Mygets(temp1,PASSWD_LEN);
			printf("请再次输入你要更改的密码：");
			Mygets(temp2,PASSWD_LEN);
			if(strcmp(temp1,temp2)==0&&strcmp(passwd,temp1)!=0)
			{
				while(l->next!=NULL)
				{
					if(strcmp(l->next->tdata.pwd,passwd)==0)
					{
						strcpy(l->next->tdata.pwd,temp1);
						printf("修改密码成功！\n");
						writefile_t(head);
						return;
					}
					else
					{
						l=l->next;
					}
				}

			}
			else if(strcmp(passwd,temp1)==0)
			{
				printf("新密码不能与原密码一致\n");
			}
			else
			{
				printf("两次密码输入不一致，请重新修改！\n");
			}
		}	
	}
	else
	{
		printf("密码输入错误，退出更改\n");
	}

}
//学生修改登录密码
void chang_s(char *passwd)
{
	stu *l=readfile_s();
	stu *head=l;
	char inpasswd[PASSWD_LEN]={'\0'};
	printf("请输入原密码：");
	Mygets(inpasswd,PASSWD_LEN);
	if(strcmp(inpasswd,passwd)==0)
	{
		while(1)
		{
			char temp1[PASSWD_LEN]={'\0'};
			char temp2[PASSWD_LEN]={'\0'};
			printf("请输入你要更改的密码：");
			Mygets(temp1,PASSWD_LEN);
			printf("请再次输入你要更改的密码：");
			Mygets(temp2,PASSWD_LEN);
			if(strcmp(temp1,temp2)==0&&strcmp(passwd,temp1)!=0)
			{
				while(l->next!=NULL)
				{
					if(strcmp(l->next->sdata.pwd,passwd)==0)
					{
						strcpy(l->next->sdata.pwd,temp1);
						printf("修改密码成功！\n");
						writefile_s(head);
						return;
					}
					else
					{
						l=l->next;
					}
				}

			}
			else if(strcmp(passwd,temp1)==0)
			{
				printf("新密码不能与原密码一致\n");
			}
			else
			{
				printf("两次密码输入不一致，请重新修改！\n");
			}
		}	
	}
	else
	{
		printf("密码输入错误，退出更改\n");
	}

}
//学生分数排名
void sort_s()
{
	stu *head=readfile_s();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	stu *p1=head->next;
	stu *high;
	stu *p2;

	stu *temp=(stu *)malloc(sizeof(stu));
	temp->next=NULL;

	while(p1!=NULL)
	{
		high=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(high->sdata.sum<p2->sdata.sum)
			{
				high=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(high!=p1)
		{
			temp->sdata=high->sdata;
			high->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	int i=1;
	printf("学号\t姓名\t数学\t语文\t总分\t排名\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%d\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,head->next->sdata.chinese,head->next->sdata.sum,i++);
		head=head->next;
	}
		
}
//学生数学分数排名
void sort_m()
{
	stu *head=readfile_s();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	stu *p1=head->next;
	stu *high;
	stu *p2;

	stu *temp=(stu *)malloc(sizeof(stu));
	temp->next=NULL;

	while(p1!=NULL)
	{
		high=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(high->sdata.math<p2->sdata.math)
			{
				high=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(high!=p1)
		{
			temp->sdata=high->sdata;
			high->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	int i=1;
	printf("学号\t姓名\t数学\t排名\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%d\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,i++);
		head=head->next;
	}
		
}
//学生语文分数排名
void sort_c()
{
	stu *head=readfile_s();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	stu *p1=head->next;
	stu *high;
	stu *p2;

	stu *temp=(stu *)malloc(sizeof(stu));
	temp->next=NULL;

	while(p1!=NULL)
	{
		high=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(high->sdata.chinese<p2->sdata.chinese)
			{
				high=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(high!=p1)
		{
			temp->sdata=high->sdata;
			high->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	int i=1;
	printf("学号\t姓名\t语文\t排名\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%d\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.chinese,i++);
		head=head->next;
	}
		
}
//学生id排名
void sort_id()
{
	stu *head=readfile_s();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	stu *p1=head->next;
	stu *low;
	stu *p2;

	stu *temp=(stu *)malloc(sizeof(stu));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->sdata.id>p2->sdata.id)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(low!=p1)
		{
			temp->sdata=low->sdata;
			low->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	printf("学号\t姓名\t数学\t语文\t总分\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,head->next->sdata.chinese,head->next->sdata.sum);
		head=head->next;
	}
		
}
//学生查看个人信息
void person(int id)
{
	stu *l=readfile_s();
	while(l->next->sdata.id!=id)
	{
		l=l->next;
	}
//排名	
	stu *head=readfile_s();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	stu *p1=head->next;
	stu *high;
	stu *p2;

	stu *temp=(stu *)malloc(sizeof(stu));
	temp->next=NULL;

	while(p1!=NULL)
	{
		high=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(high->sdata.sum<p2->sdata.sum)
			{
				high=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(high!=p1)
		{
			temp->sdata=high->sdata;
			high->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}

	int i=1;
	printf("学号\t姓名\t数学\t语文\t总分\t排名\n");
	while(head->next!=NULL)
	{
		if(head->next->sdata.id==id)
		{
			printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%d\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,head->next->sdata.chinese,head->next->sdata.sum,i);
			break;
		}
		else
		{
			i++;
			head=head->next;
		}
	}
}
//删除学生信息
void delete_s()
{
	stu *head=readfile_s();
	stu *l=head;
	stu *p=NULL;
	int id=0;
	int flag=0;
	printf("input id you want to delete:");
	scanf("%d",&id);
	while(getchar()!='\n');
	while(head->next!=NULL)
	{
		if(head->next->sdata.id==id)
		{
			flag=1;
			p=head->next;
			head->next=head->next->next;
			break;
		}
		else
		{
			flag=0;
			head=head->next;
		}
	}
	if(flag==0)
	{
		printf("没有该用户\n");
	}
	free(p),p=NULL;
	save_s(l);
}
//删除教师信息
void delete_t(int id)
{
	tea *head=readfile_t();
	tea *l=head;
	tea *p=NULL;
	while(head->next!=NULL)
	{
		if(head->next->tdata.id==id)
		{
			p=head->next;
			head->next=head->next->next;
			break;
		}
		else
		{
			head=head->next;
		}
	}
	free(p),p=NULL;
	save_t(l);
}
//辞职
void resign(int id)
{
	tea *l=readfile_t();
	tea *head=l;
	//找到这个老师所在的结构体
	while(l->next!=NULL)
	{
		if(l->next->tdata.id==id)
		{
			break;
		}
		else
		{
			l=l->next;
		}
	}
	char ch='0';
	printf("您确定选择辞职吗\n"
			"y--yes\n"
			"n--no\n"
			"please input your choose:");
	scanf("%c",&ch);
	while(getchar()!='\n');
	switch(ch)
	{
		case 'y':
			l->next->tdata.resign=1;
			break;
		case 'n':
			return;
	}
	writefile_t(head);
}
//是否同意辞职
void agree()
{
	tea *l=readfile_t();
	tea *head=l;
	char a='0';
	while(l->next!=NULL)
	{
		if(l->next->tdata.resign==1)
		{
			printf("%s老师申请辞职，是否同意\n",l->next->tdata.name);
			printf("1--同意\n"
					"2--不同意\n");
			scanf("%c",&a);
			while(getchar()!='\n');
			switch(a)
			{
				case '1':
					l->next->tdata.agree=1;
					l->next->tdata.resign=0;
					break;
				case '2':
					l->next->tdata.agree=0;
					l->next->tdata.resign=2;
					break;
			}
		}
		else
		{
			l=l->next;
		}
				
	}
	writefile_t(head);
}
//判断职务
int job(int id)
{
	tea *l=readfile_t();
	char b[JOB_LEN]={"head"};
	char m[JOB_LEN]={"math"};
	char c[JOB_LEN]={"chinese"};
	while(l->next->tdata.id!=id)
	{
		l=l->next;
	}
	if(strcmp(l->next->tdata.job,b)==0)
	{
		return 1;
	}
	else if(strcmp(l->next->tdata.job,m)==0)
	{
		return 2;
	}
	else if(strcmp(l->next->tdata.job,c)==0)
	{
		return 3;
	}

	else 
		return -1;
	
}
//留言
void left_w()
{
	tea *head=readfile_t();
	tea *l=head;
	char name[NAME_LEN]={'\0'};
	int flag=0;
	printf("请输入你要留言的教师姓名:");
	scanf("%s",name);
	while(getchar()!='\n');
	while(head->next!=NULL)
	{
		if(strcmp(head->next->tdata.name,name)==0)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
			head=head->next;
		}
	}
	if(flag==0)
	{
		printf("该教师不存在\n");
		return;
	}
	char word[W_LEN]={'\0'};
	printf("对%s老师留言：\n",head->next->tdata.name);
	Mygets(word,W_LEN);
	char ab[3]={"\n"};

	strcat(word,ab);
	strcat(head->next->tdata.left_w,word);
	save_t(l);
}
//查看留言
void left_l(int id)
{
	tea *head=readfile_t();
	while(head->next->tdata.id!=id)
	{
		head=head->next;
	}
	printf("%s\n",head->next->tdata.left_w);
}





