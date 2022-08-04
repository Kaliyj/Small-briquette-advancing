#ifndef TEACHER_H
#define TEACHER_H

#include <stdbool.h>


void tea_menu(void);//显示教师菜单
int tea_sys(void);//教师系统函数
bool t_psw(void);//教师密码判断
void change(void);//教师修改密码
void s_add(void);//添加学生主函数
void sfac_add(void);//添加学生成绩主函数
void s_del(void);//使学生离校函数
void s_mod(void);//修改学生信息函数
void s_find(void);//查看特定学生函数
void s_show(void);//显示在校学生
void mods_passwd(void);//重置学生密码
void outs_show(void);//显示离校学生
void add_one(void);//单个添加学生
void add_many(void);//批量添加学生
void adds(void);//单个添加学生成绩
void adds_many(void);//批量添加学生成绩
void find_name(void);//根据学生姓名查看学生信息
void find_id(void);//根据学生ID查看学生信息
void tfirst_sign_in(const char* Key);//判断教师密码是否为初始密码
void recovery(void);//离校学生归校

#endif//TEACHER_H
