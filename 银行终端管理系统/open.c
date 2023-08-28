#include "common.h"

int c2smsgid,s2cmsgid;
int Account(void);
void Save(struct C2SMSG r_buf);
int count=0,buf[2000]={0};

int main()
{
    
	printf("服务器开户功能启动成功\n");
	//访问消息队列
	s2cmsgid=msgget(S2CKEY,IPC_CREAT|0644); if(s2cmsgid == -1) {
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
        msgrcv(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),OPEN,0);
        printf("姓名：%s\n",r_buf.data.name);
        printf("密码：%s\n",r_buf.data.passwd);
        printf("金额：%.2f\n",r_buf.data.money);
        printf("pid：%d\n",r_buf.data.pid);
        w_buf.type = r_buf.data.pid;
        w_buf.id = Account();
        w_buf.money=r_buf.data.money;
        r_buf.data.id = w_buf.id;
        if(w_buf.id == -1)
        {
            strcpy(w_buf.info,"开户失败");
        }
        else
        {
            strcpy(w_buf.info,"开户成功");
            Save(r_buf);
        }
        msgsnd(s2cmsgid,&w_buf,sizeof( struct S2SMSG)-sizeof(long),0);
        printf("开户成功\n");
    }
    return 0;
}

int Account(void)//保证银行卡号不重复
{

  
    int id = 20230816;
    int fd =open("account.txt",O_RDWR|O_CREAT,0644);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    read(fd,&id,sizeof(int));
    printf("id1 = %d\n",id);
    id++;
    lseek(fd,0,0);
    write(fd,&id,sizeof(int));
    close(fd);
    return id;
}

void Save(struct C2SMSG r_buf)
{
    char filename[100];
    sprintf(filename,"%d.txt",r_buf.data.id);
    int fd = open(filename,O_WRONLY|O_CREAT,0644);
    write(fd,&r_buf,sizeof(r_buf));
    close(fd);
}
