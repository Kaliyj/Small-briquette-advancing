#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "tools.h"



int Key = 0;     //临时存放输入的id
char Psw[20];    //临时存放输入的密码

//显示内容并延时
void msg_show(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}

//按任意键继续
void anykey_continue(void)
{
	puts("-------按任意键继续--------");
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	getch();
}


// 主界面
int interface(void)
{
	system("clear");
	printf("--欢迎登录宁树教务管理系统--\n");
	printf("-- 按任意键登陆-按下q退出 --\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	switch(getch())
	{
		case 'q': return 7; //按q退出
		default: break;//否则输入账号和密码
	}
	printf("请输入账号：");
	if(1 != scanf("%d",&Key))
	{
		Key = -1;
		return 0;
	}
	printf("请输入密码：");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	secretword(Psw); //隐藏密码
}

//隐藏密码
void secretword(char keye[])
{
	unsigned char c;
	int i=0;//记录输入密码的个数
	while((c=getch())!='\n')//按下回车退出循环，否则获取键值
	{
		if(i<20 && isprint(c)) //判断密码是否小于20位并检查所传的字符是否可以打印
		{
			keye[i]=c;//密码一个一个存入数组
			i++;
			putchar('*');//打印一个*
		}
		else if(i>0 && c==127) //判断密码是否大于0位并按下删除键
		{
			i--;//密码个数减1
			putchar('\b'); //向前移动一位
			putchar(' '); //打印空格
			putchar('\b'); //再向前移动一位
		}
	}
	printf("\n");
	keye[i]='\0'; //最后输入'\0'
}

void open_f(void)//打开、解密文件
{
	FILE* stuf = fopen("student.txt","r");//只读打开学生文件
	FILE* teaf = fopen("teacher.txt","r");//只读打开教师文件
	FILE* admf = fopen("admin.txt","r");//只读打开校长文件
	stu = calloc(sizeof(Student),NUM);//申请学生堆内存
	tea = calloc(sizeof(Teacher),NUM);//申请老师堆内存
	int a=0,b=0;//
	//读取学生文件到内存
	while(fscanf(stuf,"%d %s %s %s %f %f %f %hhd %hhd ",&stu[a].id,stu[a].name,stu[a].sex,stu[a].passwd,&stu[a].chinese,&stu[a].math,&stu[a].english,&stu[a].flag,&stu[a].state) && stu[a].id) a++;
	//读取老师文件到内存
	while(fscanf(teaf,"%d %s %s %s %hhd %hhd ",&tea[b].id,tea[b].name,tea[b].sex,tea[b].passwd,&tea[b].flag,&tea[b].state) && tea[b].id) b++;
	//读取校长文件到内存
	fscanf(admf,"%d %s ",&adm.id,adm.passwd);
	for(int i=0;i<NUM;i++)//对学生密码进行解密
	{
		if(stu[i].id)
		{
			for(int j=0;j<strlen(stu[i].passwd);j++)
			{
				stu[i].passwd[j] = stu[i].passwd[j]-10-strlen(stu[i].passwd);	
			}
		}
		else break;
	}
	for(int i=0;i<NUM;i++)//对教师密码进行解密
	{
		if(tea[i].id)
		{
			for(int j=0;j<strlen(tea[i].passwd);j++)
			{
				tea[i].passwd[j] = tea[i].passwd[j]-10-strlen(tea[i].passwd);	
			}
		}
		else break;
	}
	for(int i=0;i<strlen(adm.passwd);i++)//对校长密码进行解密
	{
		adm.passwd[i] = adm.passwd[i]-10-strlen(adm.passwd);	
	}
	fclose(stuf);//关闭对应文件
	stuf = NULL;
	fclose(admf);
	admf = NULL;
	fclose(teaf);
	teaf = NULL;
}

void save_f(void)
{
	FILE* stuf = fopen("student.txt","w");//清空写入打开各自文件
	FILE* teaf = fopen("teacher.txt","w");
	FILE* admf = fopen("admin.txt","w");
	int c=0,d=0;
	for(int i=0;i<NUM;i++)//对学生密码进行加密
	{
		if(stu[i].id)
		{
			for(int j=0;j<strlen(stu[i].passwd);j++)
			{
				stu[i].passwd[j] = stu[i].passwd[j]+10+strlen(stu[i].passwd);	
			}
		}
		else break;
	}
	for(int i=0;i<NUM;i++)//对教师密码进行加密
	{
		if(tea[i].id)
		{
			for(int j=0;j<strlen(tea[i].passwd);j++)
			{
				tea[i].passwd[j] = tea[i].passwd[j]+10+strlen(tea[i].passwd);	
			}
		}
		else break;
	}
	for(int i=0;i<strlen(adm.passwd);i++)//对校长密码进行加密
	{
		adm.passwd[i] = adm.passwd[i]+10+strlen(adm.passwd);	
	}
	//将内存写入文件
	while(stu[c].id && fprintf(stuf,"%d %s %s %s %f %f %f %hhd %hhd \n",stu[c].id,stu[c].name,stu[c].sex,stu[c].passwd,stu[c].chinese,stu[c].math,stu[c].english,stu[c].flag,stu[c].state)) c++;
	while(tea[d].id && fprintf(teaf,"%d %s %s %s %hhd %hhd \n",tea[d].id,tea[d].name,tea[d].sex,tea[d].passwd,tea[d].flag,tea[d].state)) d++;
	fprintf(admf,"%d %s ",adm.id,adm.passwd);
	free(stu);//释放堆内存
	free(tea);
	fclose(stuf);//关闭各自文件
	stuf = NULL;
	fclose(admf);
	admf = NULL;
	fclose(teaf);
	teaf = NULL;
}

