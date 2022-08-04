#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getch.h>
#include "student.h" 
#include "tools.h"

//学生系统界面
int menu(void)
{
	system("clear");      //清屏
	//打印学生系统界面
	puts("***欢迎使用学生教务系统***");
	puts("*1、查询成绩             *");
	puts("*2、修改密码             *");
	puts("*3、查看个人信息         *");
	puts("*4、退出当前账号         *");
	puts("**************************");
	printf("请输入指令：");
	char cmd = getch();   //获取按键的值
	return cmd;           //返回按键的值
}

int stu_sys(void)
{
	switch(menu())        //将返回的按键的值作为条件
	{
		case '1': View_grades(); break;	  //按1进入查询成绩界面
		case '2': mod_passwd(); break;	  //按2进入修改密码界面
		case '3': View_personal_information(); break;
		//按3进入查看个人信息界面
		case '4': return 7;      //按4退出当前账号
	}
}

//首次登录强制修改密码
void first_sign_in(const char* key)
{
	char arr[20]={};
	if(0 == strcmp(key,"000000"))  //判断是否是首次登录
	{
		printf("密码为初始化密码，请输入要修改的密码:");
		stdin->_IO_read_ptr = stdin->_IO_read_end;   //清除缓冲区
		for(;;)
		{
			secretword(arr);
			//调用隐藏密码的函数并将输入的新密码存入arr数组
			if(0 == strcmp(arr,"000000"))
			{
				msg_show("新密码不能为初始密码，请重新输入:",1);	
			}
			else
			{
				for(int i=0;i<NUM;i++)  //遍历学生id
				{
					if(Key == stu[i].id)  //判断是否与输入的id相同
					{
						strcpy(stu[i].passwd,arr);	
						//将新密码拷贝到存放当前学生的密码结构体中
						break; //完成修改跳出for循环
					}
				}
				break;
			}
		}
		msg_show("已修改，请牢记您的密码\n",1.5); //显示""中的内容，并延时1.5秒
	}
}

//学生修改自己的密码
void mod_passwd(void)
{
	system("clear");  //清屏
	char arr[20]={};
	for(int i=0;i<NUM;i++)  //遍历学生的id
	{
		if(Key == stu[i].id)  //判断是否与输入的id相同
		{
			printf("请输入新密码：");
			stdin->_IO_read_ptr = stdin->_IO_read_end; //清楚缓冲区
			secretword(arr); 
			//调用隐藏密码的函数，并将输入的新密码存入arr数组
			strcpy(stu[i].passwd,arr); 
			//将新密码拷贝到存放当前学生的密码结构体中
			msg_show("修改成功,请牢记您的密码\n",2); 
			//显示""中的内容并延时2秒
			return;  //完成修改退出修改密码系统
		}
	}
	msg_show("系统正在升级，请稍后再试...\n",1); // 显示""中的内容并延时1秒
}

// 查看个人信息
void View_personal_information(void)
{
	system("clear");
	for(int i=0;i<NUM;i++) //遍历学生的id
	{
		if(Key  == stu[i].id) //判断是否与输入的id相同
		{
			printf("学号：%06d 姓名：%s 性别：%s 语文：%.2f分 数学：%.2f分 英语：%.2f分\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].chinese,stu[i].math,stu[i].english); 
			anykey_continue();
			return;  //查询成功退出查看个人信息界面
		}
	}
	msg_show("系统正在升级，请稍后再试...\n",1); // 显示""中的内容并延时1秒
}

// 判断密码是否正确，密码输错三次账号冻结
bool s_psw(void)
{
	for(int i=0;i<NUM;i++)
	{
		if(stu[i].id == Key)//找到和输入的账号一致的学生		
		{
			if(0 == stu[i].flag) //判断该学生的状态
			{
				msg_show("账号已锁定,请找老师解锁\n",1.5);
				return false; //锁定就返回"假"
			}
			else if(0 == strcmp(Psw,stu[i].passwd))
			{
				stu[i].flag = 3; //登录成功就把状态置3
				msg_show("登陆成功\n",1.5);
				return true; //成功就返回真
			}
			else //状态正常但密码错误
			{
				stu[i].flag--; //次数减1
				printf("密码错误,还剩%d次\n",stu[i].flag);
				sleep(1);//延时一秒
				return false; //返回假
			}
		}
	}
	msg_show("账号不存在",1.5);
	return false;
}

// 查询成绩
void View_grades(void)
{
	system("clear");                    //清屏
	msg_show("语文成绩排名\n",1);         //显示"..."，延时1秒
	Student* STU = calloc(sizeof(Student),NUM);	// 申请一个排序时用的内存
	memcpy(STU,stu,sizeof(Student)*NUM); //内存拷贝
	Student t={}; //定义一个新的空结构体
	int i,j,us_rank,cnt=0,cnnt=0;//cnt存放有效人数,cnnt存放总人数
	double sum = 0;
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		//判断该结构体是否存放性别和学号是否不为0
		{
			for(j=0;j<NUM-1;j++)
			{
				if(STU[j].chinese<STU[j+1].chinese)
				//判断是否小于等于后一个成绩
				{
					// 交换
					t=STU[j];
					STU[j]=STU[j+1];
					STU[j+1]=t;
				}
			}
		}
	}
	int k=0;
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			printf("  %d: %.2f  \n",i+1-k,STU[i].chinese); 
			//打印第i+1个名的成绩
			sum += STU[i].chinese;// 求和
			cnt++;//有效人数加1
		}
		else k++;
	}
	k=0;
	float max_chinese; //最大值
	float min_chinese; //最小值
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			max_chinese	= STU[i].chinese; //最大值
			break;
		}
	}
	for(i=0;i<NUM;i++)
	{
		if(STU[i].id)
		{
			cnnt++;	
		}
		else break;
	}
	for(i=cnnt;i>0;i--)
	{
		if(2 == STU[i-1].state)
		{
			min_chinese = STU[i-1].chinese; //最小值
			break;
		}
	}
	double avg_chinese = sum/cnt; //平均值
	printf("最高分为：%.2f\n",max_chinese);
	printf("最低分为：%.2f\n",min_chinese);
	printf("平均分为：%.2lf\n",avg_chinese);
	for(i=0;i<NUM;i++) //遍历
	{
		if(Key == STU[i].id) 
		{
			if(2 == STU[i].state)
			{
				printf("我的排名：%d\n",i-k);
				break; //退出此次for循环
			}
			else
			{
				k++;
				printf("我的排名：无\n");
			}
		}
	}
	k=0;
	anykey_continue(); //按任意键继续
	sum =0,cnt=0; //把总分和有效个数初始化为0

	system("clear"); //清屏
	msg_show("数学成绩排名\n",1);//显示""内容并延时1秒
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)//判断该结构体是否存放性别和学号是否不为0
		{
			for(j=0;j<NUM-1;j++)
			{
				if(STU[j].math<STU[j+1].math)//判断是否小于等于后一个成绩
				{
					t=STU[j];
					STU[j]=STU[j+1];
					STU[j+1]=t;
				}
			}
		}
	}
    for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			printf("  %d: %.2f  \n",i+1-k,STU[i].math);//打印第i+1个名的成绩
			sum += STU[i].math;// 求和
			cnt++;//有效人数加1
		}
		else k++;
	}
	k = 0;
	float max_math;
	float min_math;
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			max_math = STU[i].math; //最大值
			break;
		}
	}
	for(i=0;i<NUM;i++)
	{
		if(STU[i].id)
		{
			cnnt++;
		}
		else break;
	}
	for(i=cnnt;i>0;i--)
	{
		if(2 == STU[i-1].state)
		{
			min_math = STU[i-1].math; //最小值
			break;
		}
	}
	double avg_math = sum/cnt;
	printf("最高分为：%.2f\n",max_math);
	printf("最低分为：%.2f\n",min_math);
	printf("平均分为：%.2lf\n",avg_math);
	for(i=0;i<NUM;i++)//遍历
	{
		if(Key == STU[i].id)
		{
			if(2 == STU[i].state)
			{
				printf("我的排名：%d\n",i-k);
				break;
			}
			else
			{
				k++;
				printf("我的排名：无\n");
			}
		}
	}
	k = 0;
	anykey_continue();
	sum =0,cnt=0;

	system("clear"); //清屏
	msg_show("英语成绩排名\n",1);
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)//判断该结构体是否存放性别和学号是否不为0
		{
			for(j=0;j<NUM-1;j++)
			{
				if(STU[j].english<STU[j+1].english)//判断是否小于等于后一个成绩
				{
					t=STU[j];
					STU[j]=STU[j+1];
					STU[j+1]=t;
				}
			}
		}
	}
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			printf("  %d: %.2f  \n",i+1-k,STU[i].english);//打印第i+1个名的成绩
			sum += STU[i].english;// 求和
			cnt++;//有效人数加1
		}
		else k++;
	}
	k = 0;
	float max_english;
	float min_english;
	for(i=0;i<NUM;i++)
	{
		if(2 == STU[i].state)
		{
			max_english = STU[i].english; //最大值
			break;
		}
	}
	for(i=0;i<NUM;i++)
	{
		if(STU[i].id)
		{
			cnnt++;
		}
		else break;
	}
	for(i=cnnt;i>0;i--)
	{
		if(2 == STU[i-1].state)
		{
			min_english = STU[i-1].english; //最小值
			break;
		}
	}
	double avg_english = sum/cnt;
	printf("最高分为：%.2f\n",max_english);
	printf("最低分为：%.2f\n",min_english);
	printf("平均分为：%.2lf\n",avg_english);
	for(i=0;i<NUM;i++) //遍历
	{
		if(Key == STU[i].id) 
		{
			if(2 == STU[i].state)
			{
				printf("我的排名：%d\n",i-k);
				break; //退出此次for循环
			}
			else
			{
				k++;
				printf("我的排名：无\n");
			}
		}
	}
	k=0;
	anykey_continue();//按任意键继续
	free(STU); // 释放内存
	STU = NULL;// 将其置空
}
