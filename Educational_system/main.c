#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tools.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"

int main(int argc,const char* argv[])
{
	open_f();//打开文件，文件写入到内存，解密文件
	for(;;)
	{
		if(7 == interface()) //登录首界面
		{
			break;	
		}
		if(0 == Key) //校长id
		{
			if(a_psw()) //密码判断
			{
				ad_first_sign_in(Psw); //是否首次登录
				for(;;)
				{
					if(7 == admin_sys()) //退出系统的返回值判断
					{
						break;	
					}
				}
			}
		}
		else if(0 < Key && 500000 > Key) //学生id
		{
			if(s_psw()) //密码判断
			{
				first_sign_in(Psw);//是否首次登录
				for(;;)
				{
					if(7 == stu_sys())//退出系统的返回值判断
					{
						break;	
					}
					
				}
			}
		}
		else if(500000 < Key && 1000000 >Key)//老师id
		{
			if(t_psw())//密码判断
			{
				tfirst_sign_in(Psw);//是否首次登录
				for(;;)
				{
					if(7 == tea_sys())//退出系统的返回值判断
					{
						break;	
					}
				}
			}
		}
		else //id不在范围内
		{
			msg_show("用户名不合法(应为纯数字)或错误，请重试...\n",1);
		}
	}
	save_f();//打开文件、写入文件、加密文件
	return 0;
}
