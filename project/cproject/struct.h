#ifndef	STRUCT_H
#define	STRUCT_H

#include"Macro.h"
typedef struct tmessage
{
	int id;
	char name[NAME_LEN];
	char pwd[PASSWD_LEN];
	char job[JOB_LEN];
	char left_w[W_LEN];
	int	 resign;//判断是否辞职，辞职为1
	int  agree;//是否同意辞职，同意为1
}tea_m;

typedef struct teacher
{
	struct tmessage tdata;
	struct teacher	*next;
}tea;

typedef struct smessage
{
	int id;
	char name[NAME_LEN];
	char pwd[PASSWD_LEN];
	float math;
	float chinese;
	float sum;//总分
}stu_m;

typedef struct student
{
	struct smessage sdata;
	struct student	*next;
}stu;

#endif
