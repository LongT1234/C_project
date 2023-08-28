#include "common.h"
int c2smsgid, s2cmsgid;
void Save(struct C2SMSG r_buf);
int main()
{
 struct C2SMSG r_buf;
     struct S2SMSG w_buf;
     char arr[20];
 
      printf("服务器取款功能启动成功\n");
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
      while (1)
      {
        
     msgrcv(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),WITH,0);
      printf("姓名：%s\n",r_buf.data.name);
        printf("密码：%s\n",r_buf.data.passwd);
        printf("金额：%.2f\n",r_buf.data.money);
         printf("id：%d\n",r_buf.data.id);
        printf("pid：%d\n",r_buf.data.pid);
        w_buf.type = r_buf.data.pid;
         w_buf.money=r_buf.data.money;
     sprintf(arr,"%d.txt",r_buf.data.id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
         return -1;
      }
      else
      {
      Save(r_buf);
           msgsnd(s2cmsgid,&r_buf,sizeof( struct S2SMSG)-sizeof(long),0);
           printf("账户余额：%.2f\n",r_buf.data.money);
            printf("取款成功\n");
            
        }

     }
    return 0 ;

}
void Save(struct C2SMSG r_buf)
{
    char filename[100];
    sprintf(filename,"%d.txt",r_buf.data.id);
    int fd = open(filename,O_WRONLY|O_CREAT,0644);
    write(fd,&r_buf,sizeof(r_buf));
    close(fd);
}