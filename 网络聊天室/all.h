
#ifndef _ALL_H_
#define _ALL_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <mysql/mysql.h> 
#include <sys/select.h> 
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#define ADM  20230911 //管理员ID
struct CLI{
    char name[20];//用户名
    char passwd[20];//用户密码
    int ID;//用户账号
    int type;//消息类型 -- 判断
    char feedback[50];//反馈信息
    int online;//在线状态
    char r_buf[100];//写入的消息
    char w_buf[100];//群发还是私法
    int s_ID;//聊天对象的ID
    int adm;//管理员标志
    char buf[100];//管理员标志
    char adm_type ; //管理员消息类型
    char time[100];
};

struct SER{
    char name[20];//用户名
    char passwd[20];//用户密码
    int ID;//用户账号
    int type;//消息类型 -- 判断
    char feedback[50];//反馈信息
    int online;//在线状态
    char r_buf[100];//写入的消息
    char w_buf[100];//群发还是私法
    int s_ID;//聊天对象的ID
    int adm;//管理员标志
    char buf[100];//管理员标志
    char adm_type ; //管理员消息类型
    char time[100];
};


#endif