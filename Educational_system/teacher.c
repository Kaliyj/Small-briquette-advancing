#include <getch.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "teacher.h"
#include "student.h"
#include "tools.h"


void tea_menu(void)//教师系统菜单显示
{
	system("clear");
	printf(" 老师你好\n");
	printf("-----------------------\n");	
	printf("--  1,添加学生       --\n");	
	printf("--  2,添加学生成绩   --\n");	
	printf("--  3,学生退学       --\n");	
	printf("--  4,修改学生信息   --\n");	
	printf("--  5,查找学生       --\n");	
	printf("--  6,显示在校学生   --\n");	
	printf("--  7,显示退学学生   --\n");	
	printf("--  8,重置学生密码   --\n");	
	printf("--  9,修改密码       --\n");
	printf("--  0,恢复退学学生   --\n");
	printf("--  q,退出当前账号   --\n");	
	printf("-----------------------\n");	
}

int tea_sys(void)//教师系统键值
{	
	tea_menu();	
	switch(getch())
	{
		case '1': s_add(); break;//添加学生
		case '2': sfac_add(); break;//添加学生成绩
		case '3': s_del(); break;//删除学生
		case '4': s_mod(); break;//修改学生信息
		case '5': s_find(); break;//查看学生信息
		case '6': s_show(); break;//显示在校学生
		case '7': outs_show(); break;//显示退学学生
		case '8': mods_passwd(); break;//重置学生密码
		case '9': change(); break;//修改密码
		case '0': recovery(); break;//恢复退学
		case 'q': return 7;//退出教师系统
		}
}

bool t_psw(void)//判断教师密码是否一致,以及账号是否锁定
{
	for(int i=0;i<NUM;i++)
	{
		if(tea[i].id == Key)//遍历寻找ID相同的下标
		{
			if(0 == tea[i].flag)//判断与ID下标相同的账号状态
			{
				msg_show("账号已锁定,请找校长解锁\n",1.5);
				return false;
			}
			else if(0 == strcmp(tea[i].passwd,Psw))//比较密码是否一致
			{
				tea[i].flag = 3;
				msg_show("登陆成功\n",1.5);
				return true;//返回登陆成功
			}
			else
			{
				tea[i].flag--;//密码错误，状态改变
				printf("密码错误,还剩%d次\n",tea[i].flag);
				sleep(1);
				return false;
			}
		}
	}
	msg_show("账号不存在",1.5);
	return false;
}

void s_add(void)//添加学生
{
	system("clear");
	printf("------------------\n");
	printf("--1,录入单个学生--\n");
	printf("--2,文件录入学生--\n");
	printf("--q,返回上一级  --\n");
	printf("------------------\n");
	switch(getch())
	{
		case '1': add_one();  break;//单个添加学生
		case '2': add_many(); break;//批量添加学生
		case 'q': return;
	}
}
void sfac_add(void)//录入学生成绩
{
	system("clear");
	printf("----------------------\n");
	printf("--1,录入单个学生成绩--\n");
	printf("--2,文件录入学生成绩--\n");
	printf("--q,返回上一级      --\n");
	printf("----------------------\n");
	switch(getch())
	{
		case '1': adds(); break;//单个录入成绩
		case '2': adds_many(); break;//批量录入学生
		case 'q': return;
	}

}

void s_del(void)//退学学生
{
	system("clear");
	int no=0,no2=0;//接住两次学号
	printf("请输入要离校的学生学号：");
	if(1 != scanf("%d",&no))
	{
		msg_show("学号不正确",1.5);
		return;
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	for(int i=0;i<NUM;i++)
	{
		if(no == stu[i].id && 1 == stu[i].state )//判断学号学生状态
		{
			msg_show("该学生已离校\n",1.5);
			return;
		}
		else if(no == stu[i].id)
		{
			printf("请再次输入要离校学生的学号：");//输入两次确定退学
			scanf("%d",&no2);
			if(no == no2 && no == stu[i].id)
			{
				stu[i].state=1;//在校状态
				msg_show("离校办理成功\n",1.5);
				return;
			}
		}
	}
	msg_show("取消退学,两次学号输入不同，或学号不存在\n",1.5);
}

void s_mod(void)//修改学生信息
{
	system("clear");
	printf("--------------------\n");
	printf("--1，修改学生信息 --\n");
	printf("--2，修改学生成绩 --\n");
	printf("--q，返回上一级   --\n");
	printf("--------------------\n");
	int no;//接住学号
	switch(getch())
	{
		case '1':
			system("clear");
			printf("请输入要修改学生的学号：");
			if(1 != scanf("%d",&no))
			{
				msg_show("输入有误，请确认",1.5);
				return;
			}
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
			for(int i=0;i<NUM;i++)
			{
				if(no == stu[i].id)//通过ID确定学生信息下标
				{
					printf("学号:%06d 姓名:%s 性别:%s\n",stu[i].id,stu[i].name,stu[i].sex);//显示学生当前状态
					printf("请输入新的姓名；");
					scanf("%18s",stu[i].name);//修改信息
					stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
					printf("请输入新的性别；");
					scanf("%3s",stu[i].sex);//修改信息
					stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
					msg_show("修改成功\n",1.5);
					return;
				}
			}
			msg_show("该学号不存在\n",1.5);
			break;
		case '2':
			system("clear");
			printf("请输入要修改学生的学号：");
			if(1 != scanf("%d",&no))
			{
				msg_show("输入有误，请确认",1.5);
				return;
			}
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
			for(int i=0;i<NUM;i++)
			{
				if(no == stu[i].id)//通过ID确定学生信息下标
				{
					float C=0,M=0,E=0;//接住成绩
					printf("学号:%06d 语文:%.2f 数学:%.2f 英语:%.2f\n",stu[i].id,stu[i].chinese,stu[i].math,stu[i].english);//显示当前学生状态
					printf("请输入新的成绩（语文、数学、英语(百分制)）；");
					if(3 != scanf("%f %f %f",&C,&M,&E))//判断成绩是否合法
					{
						msg_show("输入数据有误，请检查",1.5);
						return;
					}
					else if(100 < C || C < 0 || M < 0 || 100 < M || 100 < E || E < 0)
					{
						msg_show("输入数据有误，请检查",1.5);
						return;
					}
					stu[i].chinese = C;
					stu[i].math = M;
					stu[i].english = E;
					msg_show("修改成功\n",1.5);
					return;
				}
			}
			msg_show("该学号不存在",1.5);
			break;
		case 'q': return;
	}
}

void s_find(void)//查看学生信息
{
	system("clear");
	printf("------------------\n");
	printf("--1，姓名查询   --\n");
	printf("--2，学号查询   --\n");
	printf("--q，返回上一级 --\n");
	printf("------------------\n");
	switch(getch())
	{
		case '1': find_name(); break;//通过姓名
		case '2': find_id(); break;//通过学号
		case 'q': return;
	}
}

void s_show(void)//显示在校学生
{
	system("clear");
	printf("在校学生\n");
	for(int i=0;i<NUM;i++)
	{
		if(stu[i].id && stu[i].state!=1)//根据学号与在校状态显示在校学生
		{
			printf("学号:%06d 姓名:%s 性别:%s 语文:%.2f 数学:%.2f 英语:%.2f\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].chinese,stu[i].math,stu[i].english);//显示信息
		}
	}
	anykey_continue();
}

void outs_show(void)
{
	system("clear");
	printf("离校学生\n");
	for(int i=0;i<NUM;i++)
	{
		if(1 == stu[i].state)//根据在校状态显示离校学生
		{	
			printf("学号:%06d 姓名:%s 性别:%s\n",stu[i].id,stu[i].name,stu[i].sex);
		}
	}
	anykey_continue();
}

void mods_passwd(void)//重置、解锁学生账号
{
	system("clear");
	printf("-----------------\n");
	printf("-- 1,解锁密码  --\n");
	printf("-- 2,重置密码  --\n");
	printf("-- 3,返回上一级--\n");
	printf("-----------------\n");
	int no;//接住查询学号
	switch(getch())
	{
		case '1':
			printf("请输入要重置密码学生的学号：");
			if(1 != scanf("%d",&no))
			{
				msg_show("学号有误，请检查",1.5);
				return;
			}
			for(int i=0;i<NUM;i++)
			{
				if(no == stu[i].id)//根据学号重置密码
				{
					stu[i].flag=3;
					msg_show("解锁成功\n",1.5);
					return;
				}
			}
			msg_show("学号不存在",1.5);
			break;
		case '2':
			printf("请输入要重置密码学生的学号：");
			if(1 != scanf("%d",&no))
			{
				msg_show("学号有误，请检查",1.5);
				return;
			}
			for(int i=0;i<NUM;i++)
			{
				if(no == stu[i].id)//根据学号重置密码
				{
					stu[i].flag=3;
					strcpy(stu[i].passwd,"000000");
					msg_show("重置成功\n",1.5);
					return;
				}
			}
			msg_show("学号不存在",1.5);
			break;
		case 'q': return;
	}
}

void add_one(void)
{
	system("clear");
	int i =0;
	char sex[256]={};
	while(stu[i].id)//寻找可以插入学生的下标
	{
		i++;
	}
	printf("请输入学生姓名:");
	scanf("%18s",stu[i].name);//录入信息
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	printf("请输入学生性别：");
	scanf("%3s",stu[i].sex);//录入信息
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	stu[i].id = i+1;//学号分配
	stu[i].flag = 3;//账号状态分配
	strcpy(stu[i].passwd,"000000");//初始密码分配
	stu[i].state = 2;//在校状态分配
	msg_show("添加成功",1.5);
}

void add_many(void)
{
	system("clear");
	printf("---------------\n");
	printf("--1,覆盖导入 --\n");
	printf("--2,追加导入 --\n");
	printf("---------------\n");
	int i=0;
	switch(getch())
	{
		case '1':	break;
		case '2':	
			while(stu[i].id) i++;
			break;
	}
	char list[50]={};
	printf("请输入添加学生的文件路径\n");
	scanf("%49s",list);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	FILE* add = fopen(list,"r");//打开学生信息单
	if(NULL == add)
	{
		msg_show("文件不存在\n",1.5);
		return;
	}
	while(fscanf(add,"%s %s ",stu[i].name,stu[i].sex) && 1<strlen(stu[i].name))//录入学生信息
	{
		stu[i].id = i+1;//学号分配
		stu[i].flag = 3;//账号状态分配
		strcpy(stu[i].passwd,"000000");//初始密码分配
		stu[i].state = 2;//在校状态分配
		i++;
	}
	msg_show("导入成功\n",1.5);
	fclose(add);
}

void change(void)//修改教师密码
{
	system("clear");
	char new[20]={};
	for(int i=0;i<NUM;i++)
	{
		if(tea[i].id == Key)//根据id找寻下标
		{
			printf("请输入新密码：");
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			secretword(new);
			strcpy(tea[i].passwd,new);//新密码赋值
			msg_show("修改成功,请牢记密码",1.5);
		}
	}
}

void recovery(void)//恢复离校学生
{
	system("clear");
	int rec=0;
	printf("请输入要复学学生学号:");
	scanf("%d",&rec);
	for(int i=0;i<NUM;i++)
	{
		if(stu[i].id == rec && 1 == stu[i].state)//根据ID与在校状态寻找下标
		{
			stu[i].state = 2;
			msg_show("复学成功\n",1.5);
			return;
		}
	}
	msg_show("该学号不存在，或者该学号学生在校\n",1.5);

}

void adds(void)//添加单个学生成绩
{
	system("clear");
	int sn=0;
	float Ch,Ma,En;//接住成绩
	printf("请输入学生学号来添加成绩：");
	scanf("%d",&sn);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	for(int i=0;i<NUM;i++)
	{
		if(sn == stu[i].id && stu[i].id)//根据学号寻找下标
		{
			printf("请输入该学生的成绩（语文/数学/英语）：");
			if(3 != scanf("%f %f %f",&Ch,&Ma,&En))
			{
				msg_show("数据有误，请检查",1.5);
				return;
			}
			else if(100 < Ch || Ch < 0 || Ma < 0 || 100 < Ma || 100 < En || En < 0)
			{
				msg_show("输入数据有误，请检查",1.5);
				return;
			}
			stu[i].chinese = Ch;//添加成绩
			stu[i].math = Ma;
			stu[i].english = En;
			msg_show("添加成功\n",1.5);
			return;
		}
	}
	msg_show("学号不正确\n",1.5);
}

void adds_many(void)//批量导入学生成绩
{
	system("clear");
	char report[50]={};//接住文件名
	printf("请输入学生成绩的文件路径：");
	scanf("%49s",report);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	FILE* fac = fopen(report,"r");
	if(NULL == fac)
	{
		msg_show("文件不存在\n",1.5);
		return;
	}
	int i=0,a=0,Ch=0,Ma=0,En=0,j=0;//定义几个变量用来寻找下标，接住ID、接住成绩、判断终点
	while(fscanf(fac,"%d %d %d %d ",&a,&Ch,&Ma,&En) && j<NUM)//寻找下标
	{
		if(a == stu[i].id)//根据学号给对应学生添加成绩
		{
			stu[i].chinese = Ch;
			stu[i].math = Ma;
			stu[i].english = En;
		}
		i++;
		j++;
	}
	msg_show("导入成功",1.5);
	fclose(fac);//关闭添加文件
}
			
void find_name(void)//根据学生姓名查询学生信息
{			
	system("clear");
	char s_n[20]={};//接住学生姓名
	printf("请输入要查询学生的姓名：");
	scanf("%19s",s_n);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	int n=0;//计数
	for(int i=0;i<NUM;i++)
	{
		if(stu[i].id && 0 == strcmp(s_n,stu[i].name))//根据姓名、ID、在校状态查找下标
		{
			printf("学号:%06d 姓名:%s 性别:%s 语文:%.2f 数学:%.2f 英语:%.2f\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].chinese,stu[i].math,stu[i].english);//显示信息
			n++;
		}
	}
	if(0 == n)
	{
		printf("姓名不存在\n");	
	}
	anykey_continue();
}
			
void find_id(void)//根据学生姓名查询学生信息
{					
	system("clear");
	int no;//接住学生学号
	printf("请输入要查询学生的学号：");
	if(1 != scanf("%d",&no))
	{
		msg_show("学号错误\n",1.5);
		return;
	}
	for(int i=0;i<NUM;i++)
	{
		if(no == stu[i].id)
		{
			printf("学号:%06d 姓名:%s 性别:%s 语文:%.2f 数学:%.2f 英语:%.2f\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].chinese,stu[i].math,stu[i].english);//显示信息
			anykey_continue();
			return;
		}
	}
	printf("学号不存在\n");
	anykey_continue();
}


void tfirst_sign_in(const char* key)//判断密码是否是初始密码
{
	char arr[20]={};//接输入的密码
	if(0 == strcmp(key,"000000"))//判断密码是否为初始密码
	{
		printf("密码为初始密码,请输入要修改的密码：");
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		for(;;)
		{
			secretword(arr);//获取密码
			if(0 == strcmp(arr,"000000"))
			{
				msg_show("新密码不能初始密码，请重新输入：",1);	
			}
			else
			{
				for(int i=0;i<NUM;i++)
				{
					if(Key == tea[i].id)//寻找下标
					{
						strcpy(tea[i].passwd,arr);	
						msg_show("修改成功,请牢记密码\n",1.5);
						break;
					}
				}
				break;
			}
		}
	}
	else
		return;
}
