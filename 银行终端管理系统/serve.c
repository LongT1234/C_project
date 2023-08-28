
#include "common.h"

int c2smsgid,s2cmsgid;

struct INFOR{
    char path[200];//可执行文件的路径
    char xname[20];//可执行文件的文件名
    pid_t pid;//子进程pid
};

struct INFOR infor[]={ {"/home/long/桌面/linux_常用命令/银行终端管理系统/open", "open"},
                        {"/home/long/桌面/linux_常用命令/银行终端管理系统/Deposit", "Deposit"},
                        {"/home/long/桌面/linux_常用命令/银行终端管理系统/Query", "Query"},
                        {"/home/long/桌面/linux_常用命令/银行终端管理系统/WithDraw", "WithDraw"},
                        {"/home/long/桌面/linux_常用命令/银行终端管理系统/remittance", "remittance"},
                        {"/home/long/桌面/linux_常用命令/银行终端管理系统/Dele", "Dele"}};

void stop(int a)
{
    for(int i=0;i<sizeof(infor)/sizeof(infor[0]);i++)
    {
        kill(infor[i].pid,9);
    }
    msgctl(c2smsgid,IPC_RMID,NULL);
    msgctl(s2cmsgid,IPC_RMID,NULL);
    exit(0);
}

int main()
{
      printf("按ctrl+c退出服务器\n");
    signal(2,stop);
    //创建消息队列
    s2cmsgid=msgget(S2CKEY,IPC_CREAT|0644);
    if(s2cmsgid == -1)
    {
        perror("msgget");
        return -1;
    }
    c2smsgid=msgget(C2SKEY,IPC_CREAT|0644);
    if(c2smsgid == -1)
    {
        perror("msgget");
        return -1;
    }
    for(int i=0;i<sizeof(infor)/sizeof(infor[0]);i++)
    {
        infor[i].pid = fork();
        if(infor[i].pid == 0)
        {
            execl(infor[i].path,infor[i].xname,NULL);
        }
    }

    while(1);
}