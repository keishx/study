#include"include.h"

void writefile_s(stu *head)
{
	if(head==NULL)
	{
		printf("no message to save\n");
		return;
	}
	FILE *fp;
		fp=fopen("student.txt","w");

	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(stu),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}
void writefile_t(tea *head)
{
	if(head==NULL)
	{
		printf("no message to save\n");
		return;
	}
	FILE *fp;
		fp=fopen("teacher.txt","w");

	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(tea),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}


stu *readfile_s()
{
	FILE *fp;
	fp=fopen("student.txt","r");
	stu *temp=(stu*)malloc(sizeof(stu));
	stu *head=(stu*)malloc(sizeof(stu));
	head->next=NULL;
	while(fread(temp,sizeof(stu),1,fp)>0)
	{
		temp->next=head->next;
		head->next=temp;
		temp=NULL;
		temp=(stu*)malloc(sizeof(stu));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
	
}

tea *readfile_t()
{
	FILE *fp;
	fp=fopen("teacher.txt","r");
	if(fp==NULL)
	{
		printf("xxxx\n");
	}
	tea *temp=(tea*)malloc(sizeof(tea));
	tea *head=(tea*)malloc(sizeof(tea));
	head->next=NULL;
	while(fread(temp,sizeof(tea),1,fp)>0)
	{
		temp->next=head->next;
		head->next=temp;
		temp=NULL;
		temp=(tea*)malloc(sizeof(tea));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
}

