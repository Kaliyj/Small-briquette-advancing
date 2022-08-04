#ifndef ADMIN_H
#define ADMIN_H

//界面
int admin_menu(void);
//选择功能
int admin_sys(void);
//判断密码是否正确
bool a_psw(void);
//首次登陆强制修改密码
void ad_first_sign_in(const char* Key);
//修改自己的密码
void reset_sign(void);
//重置教师密码
void reset_t_sign(void);
//添加老师
void add_t(void);
//添加教师
void add_onet(void);
//批量添加老师
void add_manyt(void);
//删除教师
void del_t(void);
//复工教师
void re_t(void);
//修改老师信息
void mod_t(void);
//显示所有在职教师
void show_t(void);
//显示所有离职教师
void show_leave(void);




#endif//ADMIN_H
