#include "common.h"



int Menu(void);
void OpenAccount(void);
int WithDraw ();
int Query();
int Dele();
void Deposit();
 int remittance ();
int c2smsgid,s2cmsgid;
int buf[2000]={0};
int main()
{
    printf("客户端已启动\n");
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

    while(1)
    {
        switch (Menu())
        {
        case 1:
            OpenAccount();
        break;
        case 2:
          
             Dele();
        break;
        case 3:
              Query();
        break;
        case 4:
              WithDraw ();
        break;
        case 5:
             Deposit();
        break;
        case 6:
              remittance ();
        break;
        case 7:
            return 0;
        break;
        default:
            printf("输入错误请重新输入\n");
        break;
        }
    }
}

int Menu(void)
{
    int num = 0;
    printf("1.开户\n");
    printf("2.销户\n");
    printf("3.查询\n");
    printf("4.取款\n");
    printf("5.存款\n");
    printf("6.转账\n");
    printf("7.退出\n");
    printf("请选择功能\n");
    scanf("%d",&num);
    getchar();
    system("clear");
    return num;
}

void OpenAccount(void)
{

    struct C2SMSG w_buf;
    struct S2SMSG r_buf;
    printf("请输入姓名\n");
    scanf("%s",w_buf.data.name);
    getchar();
     system("clear");
    printf("请输入密码\n");
    scanf("%s",w_buf.data.passwd);
    getchar();
     system("clear");
    printf("请输入金额\n");
    scanf("%f",&w_buf.data.money);
     system("clear");
    w_buf.type = OPEN;
    w_buf.data.pid = getpid();
    msgsnd(c2smsgid,&w_buf,sizeof(struct C2SMSG)-sizeof(long),0);
    getchar();
    msgrcv(s2cmsgid,&r_buf,sizeof( struct S2SMSG)-sizeof(long),getpid(),0);
    if(!strcmp(r_buf.info,"开户成功"))
    {
        printf("开户成功\n");
        printf("账号：%d\n",r_buf.id);
    }
}

int Query()
{

     struct C2SMSG r_buf;
     struct S2SMSG w_buf;
     char arr[20];
     char mypasswd[20];
      int id ;
     printf("请输入需要查询的账号\n");
     scanf("%d",&id);
     getchar();
     system("clear");
     sprintf(arr,"%d.txt",id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
      }
      else
      {
     printf("该账号存在\n");
     read(fd,&r_buf,sizeof(r_buf));
     for(int i=3;i>0;i--)
     { 
        printf("请输入密码\n");
        scanf("%s",mypasswd);
        getchar();
        system("clear");
        if(strcmp(mypasswd,r_buf.data.passwd)!=0)
        {
            if((i-1)==0)
            {
                printf("卡号以冻结，请回柜台解冻\n");
                break;
            }
            printf("密码错误，您还有%d次机会\n",i-1);
            
            continue;
        }
        else
        {
            printf("密码正确\n");
            r_buf.type =QUERY;
             msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
               printf("卡号为：%d\n",r_buf.data.id);
               printf("姓名为：%s\n",r_buf.data.name);
               printf("账户余额为：%.2f\n",r_buf.data.money);

            break;
        }
       

     }
    
     
      }
    
      close(fd);

return 0 ;

}

void Deposit()
{
     struct C2SMSG r_buf;
     struct S2SMSG w_buf;
     char arr[20];
     char mypasswd[20];
      int id ;
      float mymoney;
     printf("请输入需要存款的账号\n");
     scanf("%d",&id);
     getchar();
     system("clear");
     sprintf(arr,"%d.txt",id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
      }
      else
      {
     printf("该账号存在\n");
     read(fd,&r_buf,sizeof(r_buf));
     for(int i=3;i>0;i--)
     { 
        printf("请输入密码\n");
        scanf("%s",mypasswd);
        getchar();
        system("clear");
        if(strcmp(mypasswd,r_buf.data.passwd)!=0)
        {
            if((i-1)==0)
            {
                printf("卡号以冻结，请回柜台解冻\n");
                break;
            }
             printf("密码错误，您还有%d次机会\n",i-1);
            continue;
        }
        else
        {
            printf("密码正确\n");
             printf("账户余额为：%.2f\n",r_buf.data.money);
            printf("请输入需要存款金额\n");
            scanf("%f",&mymoney);
            getchar();
            system("clear");
            r_buf.data.money=r_buf.data.money+mymoney;
           // w_buf.money=r_buf.data.money;
            //write(fd,&r_buf,sizeof(r_buf));
            r_buf.type=DEPO;
            msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
                 printf("账户余额为：%.2f\n",r_buf.data.money);
           
            printf("存款成功\n");
            break;
        }

     }
     
      }
    
      close(fd);

}
//取款
 int WithDraw ()
 {
 struct C2SMSG r_buf;
     struct S2SMSG w_buf;
     char arr[20];
     char mypasswd[20];
      int id ;
      char c;
      float mymoney,tmp;
       printf("请输入需要取款的账号\n");
     scanf("%d",&id);
     getchar();
     system("clear");
     sprintf(arr,"%d.txt",id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
      }
      else
      {
    read(fd,&r_buf,sizeof(r_buf));
     for(int i=3;i>0;i--)
     { 
        printf("请输入密码\n");
        scanf("%s",mypasswd);
        getchar();
        system("clear");
        if(strcmp(mypasswd,r_buf.data.passwd)!=0)
        {
            if((i-1)==0)
            {
                printf("卡号以冻结，请回柜台解冻\n");
                break;
            }
            printf("密码错误\n");
            
            continue;
        }
        else
        { 
            printf("密码正确\n");
            printf("账户当前余额为：%.2f\n",r_buf.data.money);
           for(int i=0;i<3;i++)
            { 
                
            printf("请输入需要取款金额\n");
            scanf("%f",&mymoney);
            getchar();
            printf("取款金额是否确定(Y \\ N)\n"); 
             scanf("%c",&c);
            getchar(); 
            system("clear");
          if(c=='y'||c=='Y')
          {
           tmp = r_buf.data.money-mymoney;
     
            if(tmp>=0)
                {      
                r_buf.data.money=r_buf.data.money-mymoney;

                break;
                     
                }
                     
            else
            {
                  printf("账户当前余额为：%.2f\n",r_buf.data.money);
                 printf("余额不足，请重新输入\n");
              
            }
             

          }
          else
          {
             printf("成功退出\n");
          return  0 ;
          }
         
          }
           
           // w_buf.money=r_buf.data.money;
           r_buf.type=WITH;
            msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);

           printf("账户余额为：%.2f\n",r_buf.data.money);
            printf("取款款成功\n");
            break;
        

     }
     }
     
      }
return 0 ;
    
     
      }
    

//转账
 int remittance ()
 {
      struct C2SMSG r_buf;
      struct C2SMSG r_buf1;
     struct S2SMSG w_buf;
     char arr[20],arr1[20];
     char mypasswd[20];
      int id,id2;
      float mymoney;
     printf("请输入转账的账号\n");
     scanf("%d",&id);
     getchar();
     system("clear");
     sprintf(arr,"%d.txt",id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
      }
      else
      {
     printf("该账号存在\n");
     read(fd,&r_buf,sizeof(r_buf));
     for(int i=3;i>0;i--)
     { 
        printf("请输入密码\n");
        scanf("%s",mypasswd);
        getchar();
        system("clear");
        if(strcmp(mypasswd,r_buf.data.passwd)!=0)
        {
            if((i-1)==0)
            {
                printf("卡号以冻结，请回柜台解冻\n");
                break;
            }
            printf("密码错误\n");
            
            continue;
        }
        else
        {
            printf("密码正确\n");
             printf("账户余额为：%.2f\n",r_buf.data.money);
             for(int i=0;i<3;i++)
             {
               printf("请输入需要转向的账号\n");
            scanf("%d",&id2);
            getchar();
            system("clear");
            sprintf(arr1,"%d.txt",id2);
            int ft =open(arr1,O_RDWR,0644);
            if(ft==-1)
            { 
                printf("该账号不存在,重新输入\n");
                continue;
            }
            else
            {
                for(int i=0;i<3;i++)
                {
             printf("请输入需要转账金额\n");
            scanf("%f",&mymoney);
            getchar();
            system("clear");
            
            read(ft,&r_buf1,sizeof(r_buf1));
            r_buf.data.money=r_buf.data.money-mymoney;

            r_buf1.data.money=r_buf1.data.money+mymoney;
           w_buf.money=r_buf.data.money;
            write(fd,&r_buf,sizeof(r_buf));
           if(r_buf.data.money<0)
           {
            printf("余额不足，重新输入\n");

           }
           else
           {
             printf("转账账户余额为：%.2f\n",r_buf.data.money);
              printf("账户余额为：%.2f\n",r_buf1.data.money);
            printf("存款成功\n");
                close(fd);
                r_buf1.type=Renittance;
                r_buf.type=Renittance;
            msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
            msgsnd(c2smsgid,&r_buf1,sizeof(struct C2SMSG)-sizeof(long),0);
           return 0 ;
           }
            
            }
            
            }
             
            }
        }


     }
    
      }
 }


int Dele()
{

     struct C2SMSG r_buf;
     struct S2SMSG w_buf;
     char arr[20];
     char mypasswd[20];
      int id ;
     printf("请输入需要消除的账号\n");
     scanf("%d",&id);
     getchar();
     system("clear");
     sprintf(arr,"%d.txt",id);
    int fd =open(arr,O_RDWR,0644);
    if(fd==-1)
     { 
         printf("该账号不存在\n");
      }
      else
      {
     printf("该账号存在\n");
     read(fd,&r_buf,sizeof(r_buf));
     for(int i=3;i>0;i--)
     { 
        printf("请输入密码\n");
        scanf("%s",mypasswd);
        getchar();
        system("clear");
        if(strcmp(mypasswd,r_buf.data.passwd)!=0)
        {
            if((i-1)==0)
            {
                printf("卡号以冻结，请回柜台解冻\n");
                break;
            }
            printf("密码错误，您还有%d次机会\n",i-1);
            
            continue;
        }
        else
        {
            printf("密码正确\n");
            r_buf.type = DEL;
             msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
               printf("账户余额为：%.2f\n",r_buf.data.money);
               if(r_buf.data.money!=0)
               {
                 printf("取出账户%.2f元\n",r_buf.data.money);
                 r_buf.data.money = 0;
             
            
                msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
                return 0 ;
               }
               else{

                   
                     printf("销户成功\n");
                     msgsnd(c2smsgid,&r_buf,sizeof(struct C2SMSG)-sizeof(long),0);
                     return 0 ;
               }
               
            break;
        }
       

     }
    
     
      }
    
      close(fd);

return 0 ;



}
