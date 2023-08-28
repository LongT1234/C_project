#include "common.h"

int c2smsgid,s2cmsgid;
int Account(void);
void Save(struct C2SMSG r_buf);
int count=0,buf[2000]={0};

int main()
{
    float mymoney;
    printf("服务器查询功能启动成功\n");
    //访问消息队列
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
    struct C2SMSG r_buf;//接受客户端开户信息
   struct S2SMSG w_buf;//给客户端返回操作结果
    while(1)
    {
        msgrcv(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),QUERY,0);
        printf("姓名：%s\n",r_buf.data.name);
        printf("密码：%s\n",r_buf.data.passwd);
        printf("余额：%.2f\n",r_buf.data.money);
        printf("pid：%d\n",r_buf.data.pid);
       
        w_buf.type = r_buf.data.pid;
        w_buf.money=r_buf.data.money;
        msgsnd(s2cmsgid,&w_buf,sizeof( struct S2SMSG)-sizeof(long),0);

        printf("查询成功\n");
    }
    return 0;
}
