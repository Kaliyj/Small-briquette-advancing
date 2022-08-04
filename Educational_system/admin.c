#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getch.h>
#include "admin.h"
#include "teacher.h"
#include "tools.h"


int admin_menu(void)
{
	system("clear"); //清屏
	puts("校长您好");
	// 打印校长系统界面
	puts("-------------------------");
	puts("-- 1,修改密码          --");
	puts("-- 2,重置教师密码      --");
	puts("-- 3,添加教师          --");
	puts("-- 4,删除教师          --");
	puts("-- 5,复工教师          --");
	puts("-- 6,显示所有在职教师  --");
	puts("-- 7,显示所有离职教师  --");
	puts("-- 8,修改老师信息      --");
	puts("-- q,退出系统          --");
	puts("-------------------------");
	printf("请输入命令：");
	char num=getch(); //num接按键的值
	return num;// 返回按键的值
}

//校长操作系统
int admin_sys(void)
{
	switch(admin_menu()) //案件的值作为条件
	{
		case '1': reset_sign();  	break; //按1进入修改密码界面
		case '2': reset_t_sign();  	break; //按2进入重置老师密码界面
		case '3': add_t(); 			break; //按3进入添加老师界面
		case '4': del_t();		  	break; //按4进入删除老师界面
		case '5': re_t();		  	break; //按5进入复工老师界面
		case '6': show_t(); 		break; //按6显示所有在职教师
		case '7': show_leave(); 	break; //按7显示所有离职教师
		case '8': mod_t();          break; //按8显示修改老师界面
		case 'q': return 7;                //按q退出系统
	}
}

//判断密码是否正确
bool a_psw(void)
{
	if(0 == strcmp(Psw,adm.passwd)) //判断密码是否一致
	{
		msg_show("登陆成功\n",1.5);
		return true; //正确返回"真"
	}
	else
	{	
		msg_show("密码错误\n",1.5);
		return false; //错误返回"假"
	}
}

//修改老师信息
void mod_t(void)
{
	system("clear");
	printf("请输入要修改教师的工号：");
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
	int num;
	if(1 != scanf("%d",&num))
	{
		msg_show("工号错误\n",1.5);
		return;
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	for(int i=0;i<NUM;i++)
	{
		if(num == tea[i].id)
		{
			printf("工号:%d 姓名:%s 性别:%s\n",tea[i].id,tea[i].name,tea[i].sex);
			printf("请输入新的姓名:");
			scanf("%18s",tea[i].name);
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
			printf("请输入新的性别:");
			scanf("%3s",tea[i].sex);
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
			msg_show("修改成功\n",1.5);
			return;
		}
	}
	msg_show("该工号不存在\n",1.5);
}

//首次登录强制修改密码
void ad_first_sign_in(const char* Key)
{
	char arr[20]={}; //临时存放输入的密码
	if(0 == strcmp(Key,"000000"))
	{
	 	printf("密码为初始密码，请输入要修改的密码:");
		stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
		for(;;)
		{
			secretword(arr); //调用隐藏密码的函数
			if(0 == strcmp(arr,"000000"))
			{
				msg_show("新密码不能为初始密码，请重新输入:",1);	
			}
			else
			{
				strcpy(adm.passwd,arr); //拷贝密码
				msg_show("已修改,请牢记您的密码\n",1.5);
				break;
			}
		}
 	}
}

//重置自己的密码
void reset_sign(void)
{
	system("clear"); //清屏
	char arr[20]={}; //临时存放输入的密码
	printf("请输入新密码\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
	secretword(arr); //调用隐藏密码的函数
	strcpy(adm.passwd,arr); //拷贝密码
	msg_show("已修改,请牢记您的密码",1.5);
	return;
}
//重置教师密码
void reset_t_sign(void)
{
	system("clear"); //清屏
	int sp; //临时存放输入的工号
	printf("请输入教师的工号:");
	if(1 != scanf("%d",&sp))
	{
		msg_show("工号错误\n",1.5);
		return;
	}
	for(int i=0;i<NUM;i++)
	{
		if(sp == tea[i].id)
		{
			system("clear");
			printf("-----------------\n");
			printf("---1、重置密码---\n");
			printf("---2、解锁状态---\n");
			printf("--q、返回上一级--\n");
			printf("-----------------\n");
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
			
			switch(getch())
			{
				case '1':
					strcpy(tea[i].passwd,"000000"); //初始化密码为"000000"
					tea[i].flag=3; //初始化flag为3
					msg_show("重置成功",1.5);
					break;

				case '2':
					tea[i].flag=3; //初始化flag为3
					msg_show("解锁成功",1.5);
					break;

				case 'q': break;
			}
			return;
		}
	}
}

//添加老师界面
void add_t(void)
{
	system("clear");
	printf("-----------------\n");
	printf("-1、单个添加老师-\n");
	printf("-2、批量添加老师-\n");
	printf("-q、返回上一级  -\n");
	printf("-----------------\n");

	switch(getch())
	{
		case '1': add_onet(); break; //按1单个添加老师
		case '2': add_manyt(); break; //按2批量添加老师
		case 'q': return; //按q退出
	}
}

//添加单个教师
void add_onet(void)
{
	system("clear");
	int i=0;
	while(tea[i].id)
	{
		i++;
	}
	printf("请输入老师的姓名（工号会自动生成）：");
	scanf("%18s",tea[i].name);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
	printf("请输入老师的性别（工号会自动生成）：");
	scanf("%3s",tea[i].sex);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
	tea[i].id=500001+i; //生成工号
	strcpy(tea[i].passwd,"000000"); //初始化密码
	tea[i].flag = 3; //初始化密码状态
	tea[i].state = 2; //初始化在校状态
	msg_show("添加成功",1.5);
}

//批量添加教师
void add_manyt(void)
{
	system("clear");
	char list[50]={};//接住文件名的数组 
	printf("请输入文件名称\n");
	scanf("%49s",list);
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清除缓冲区
	FILE* add = fopen(list,"r");//打开教师信息文件
	if(NULL == add)//如果不存在、报错
	{
		perror("fopen");
		return;
	}
	int i = 0;
	while(fscanf(add,"%s %s ",tea[i].name,tea[i].sex) && 1<strlen(tea[i].name))//写入文件到内存
	{
		tea[i].id = i+500001;//生成工号
		tea[i].flag = 3;//账号状态
		tea[i].state = 2;//在职状态
		strcpy(tea[i].passwd,"000000");//初始密码
		i++;
	}
	msg_show("导入成功！\n",1.5);
	fclose(add);//关闭文件
	add = NULL;
}

//显示在职教师
void show_t(void)
{
	system("clear");
	printf("在职教师\n");
	for(int i=0;i<NUM;i++)
	{
		if(tea[i].id && 1 != tea[i].state) //判断教师的工号和在校状态
		{
			printf("name=%s sex=%s id=%d\n",tea[i].name,tea[i].sex,tea[i].id);
		}
	}
	anykey_continue();
}

//删除老师
void del_t(void)
{
	system("clear");
	int ON1 = 0,ON2 = 0;//零时存放工号的两个变量
	//两次输入工号确定
	printf("请输入要退休的老师工号:");
	if(1 != scanf("%d",&ON1))
	{
		msg_show("该工号不存在\n",1.5);
		return;
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	for(int i=0;i<NUM;i++)
	{
		if(ON1 == tea[i].id && 1 == tea[i].state)	
		{
			msg_show("该教师已退休\n",1.5);
			return;
		}
	}
	if(500000 < ON1 && 1000000 > ON1)
	{
		printf("请再次输入要退休的老师工号:");
		scanf("%d",&ON2);
	}
	else
	{
		msg_show("工号错误，请重新输入...\n",1.5);	
		return;
	}
	for(int i=0;i<NUM;i++)
	{
		if(ON1 == ON2 && ON1 == tea[i].id)
		//判断两次输入的工号的是否一致并遍历找到和该工号一样的老师
		{
			tea[i].state=1;//在校状态置1
			msg_show("已退休\n",1.5);
			return;
		}
	}
	msg_show("操作失败，两次工号不同，请稍后再试...\n",1.5);
}

//复工老师
void re_t(void)
{
	system("clear");
	int ON1 = 0,ON2 = 0;
	printf("请输入要复工的老师工号:");
	if(1 != scanf("%d",&ON1))
	{
		msg_show("工号不正确",1.5);
		return;
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end; //清空缓冲区
	if(500000 < ON1 && 1000000 > ON1)
	{
		printf("请再次输入要退休的老师工号:");
		scanf("%d",&ON2);
	}
	else
	{
		msg_show("工号错误，请重新输入...\n",1.5);	
		return;
	}
	for(int i=0;i<NUM;i++)
	{
		if(ON1 == ON2 && ON1 == tea[i].id) 
		//判断两次输入的工号的是否一致并遍历找到和该工号一样的老师
		{
			tea[i].state=2; //在校状态置0
			msg_show("已复工\n",1.5);
			return;
		}
	}
	msg_show("操作失败，两次工号不同，请稍后再试...\n",1.5);
}

//显示离职老师
void show_leave(void)
{
	system("clear");
	printf("离职教师\n");
	for(int i=0;i<NUM;i++)
	{
		if(1==tea[i].state) //判断在校状态
		{
			printf("name=%s sex=%s id=%d\n",tea[i].name,tea[i].sex,tea[i].id);
		}
	}
	anykey_continue();
}
