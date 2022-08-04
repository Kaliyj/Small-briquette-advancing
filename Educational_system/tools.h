#ifndef TOOLS_H
#define TOOLS_H

#define NUM 500//总人数

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__);
#else
	#define debug(...)
#endif

typedef struct Student
{
	int id;//学号
	char name[20];//姓名
	char sex[4];//性别
	char passwd[20];//密码
	float chinese;//语文
	float math;//数学
	float english;//英语
	char flag;//账号状态
	char state;//在校状态
}Student;

Student* stu;

typedef struct Teacher
{
	int id;//工号
	char name[20];//姓名
	char sex[4];//性别
	char passwd[20];//密码
	char flag;//账号状态
	char state;//在职状态
}Teacher;

Teacher* tea;

typedef struct Admin
{
	char passwd[20];//密码
	int id;//账号
}Admin;

Admin adm;

extern FILE* stuf;//学生文件
extern FILE* teaf;//教师文件
extern FILE* admf;//校长文件

extern int Key;//接账号
extern char Psw[20];//接密码


void msg_show(const char* msg,float sec);//延时显示
void anykey_continue(void);//任意键继续
int interface(void);//登陆主界面
void open_f(void);//文件解密、打开
void save_f(void);//文件加密、保存
void secretword(char keye[]);//密码不显示

#endif//TOOLS_H
