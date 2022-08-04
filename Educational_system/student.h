#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

//学生界面
int menu(void);
//学生系统
int stu_sys(void);
//修改学生自己的密码
void mod_passwd(void);
//首次登录修改密码
void first_sign_in(const char* Key);
//查询成绩
void View_grades(void);
//查看学生个人信息
void View_personal_information(void);
//判断密码是否正确
bool s_psw(void);

#endif//STUDENT_H
