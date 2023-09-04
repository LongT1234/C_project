#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <all.h>
void *W_Fun(void *a);
void *W_Fun1(void *a);
void *W_Fun2(void *a);
void *mypasswd(void*a);
char * Printf_time(void);
void ZERO(void);
int fd = 0;
struct SER C2SKEY;
struct CLI Printf;

int main()
{
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    printf("fd = %d\n",fd);
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12345);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(fd,(struct sockaddr *)(&ser_addr),sizeof(struct sockaddr));
    if(res == -1)
    {
        perror("connect");
        return -1;
    }
    char w_buf[100] = {0};
    char name[20]={0};
    char passwd[20]={0};
    int id;
    int num;
    int type ;
    int ID;
    int tmp=0;
                    // 1.注册类型：‘Z’  
                    // 2.登陆类型：‘D’
                    // 3.销户类型：‘X’ 
                    // 4.群聊类型：‘Q’    
                    // 5.私聊类型：‘S’ 
                    // 6.查看聊天记录：‘A’
    while(1)
    {
        stat:
        
        printf("有账号请登陆，没有账号先注册再登陆\n");
        printf("登陆(2),注册(1),退出(0)\n");
       
        scanf("%d",&type);
        getchar();
        system("clear");
        C2SKEY.type=type;
       int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);
       if(ret==-1)
       {
        perror("send");
        return -1;
       }
       perror("send");
        

  
        if(type==0)
        {
            printf("已退出\n");
            return 0 ;
            
        }

          if(type==1)
        {
           
           
        
        recv(fd,&C2SKEY,sizeof(C2SKEY),0);
         printf("请输入想要的昵称\n");
            scanf("%s",name);
            getchar(); 
            strcpy(C2SKEY.name,name);
        send(fd,&C2SKEY,sizeof(C2SKEY),0);    
        printf("注册成功\n");    
        printf("您的账号为：%d\n",C2SKEY.ID);
        printf("您的账号昵称为：%s\n",C2SKEY.name);
        printf("您的账号密码为：%s\n",C2SKEY.passwd);
       
        }
        
        else if(type==2)
        {
          while (1)
          {
             printf("请输入登陆账号\n");
            scanf("%d",&C2SKEY.ID);
            getchar();
            printf("请输入登陆账号密码\n");
            scanf("%s",C2SKEY.passwd);
            getchar();
             system("clear");
           
     int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);
       if(ret==-1)
       {
        perror("send");
        return -1;
       }
     
       recv(fd,&C2SKEY,sizeof(C2SKEY),0);
       
        if((strcmp(C2SKEY.feedback,"您的密码或账号错误")==0)||(strcmp(C2SKEY.feedback,"账号已登陆")==0)||(strcmp(C2SKEY.feedback,"用户不存在请重新登陆")==0))
       {
         printf("%s\n",C2SKEY.feedback);
         goto stat;
        
       
       }
       if(strcmp(C2SKEY.feedback,"登录成功")==0)
      {

         printf("登陆成功\n");
        s_loop:
         
         printf("\033[31;40m3.销户类型\n7.聊天室\n6.查看聊天记录\n8.修改密码\n0.退出登陆\n\033[0m");
         scanf("%d",& num);
         getchar();
          system("clear");
       C2SKEY.type=num;
         if(num==0)
         {
            send(fd,&C2SKEY,sizeof(C2SKEY),0);
           break;
         }
           
           if(num==6)
           {
            int ft;
            int flog=0;
              //  send(fd,&C2SKEY,sizeof(C2SKEY),0);
              ft =open("1.txt",O_RDWR);
                      if(ft == -1)
                    {
                        perror("open");
                        return -1;
                    }
                     //lseek( fd,0, SEEK_END);
                     
                    while(read(ft,&Printf,sizeof(Printf))!=0)
                    {                     
                        if(flog!=0)
                        {
                           
                            printf("%s:%s\n%s\n",Printf.time,Printf.name ,Printf.r_buf);
                           
                        }
                        flog++;               
                    }
                    
                     close(ft); 
                    // ZERO();

                      printf("打印完成\n"); 
            
            goto s_loop;
           }
         if(num==8)
         {
               C2SKEY.type=num;
            pthread_t id;
            
    pthread_create(&id,NULL,mypasswd,NULL); //创建副线程 
                    while(1)
                    {

                        recv(fd,&C2SKEY,sizeof(C2SKEY),0);
                       
                        printf("buf1:%s\n",C2SKEY.buf);
                        if(strcmp(C2SKEY.buf,"成功")==0)
                        {
                           goto stat;  
                        }
                         if(strcmp(C2SKEY.buf,"失败")==0)
                        {
                            printf("密码修改失败\n");

                           
                        }

                       
                     
                    }

            
         }
         if(num==3)
         {
            send(fd,&C2SKEY,sizeof(C2SKEY),0);
            printf("请输入销户账号\n");
            scanf("%d",&C2SKEY.ID);
            getchar();
            printf("请输入销户账号密码\n");
            scanf("%s",C2SKEY.passwd);
            getchar();
             system("clear");
     int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);
       if(ret==-1)
       {
        perror("send");
        return -1;
       }
       perror("send");
       sleep(1);
       recv(fd,&C2SKEY,sizeof(C2SKEY),0);
            if(strcmp(C2SKEY.feedback,"注销成功")==0)
            {
                printf("销户成功\n");
                goto stat;
            }          
         }
         if(num==7)
         {
            printf("\033[5;31;40m欢迎进入KK聊天室\n\033[0m");
            pthread_t id;
            pthread_create(&id,NULL,W_Fun2,NULL); //创建副线程
                    
                    while(1)
                    {
                      
                        recv(fd,&C2SKEY,sizeof(C2SKEY),0);
                         
                        printf("%s",C2SKEY.time);
                      
                         if (C2SKEY.online!=0)   //在线
                       {

                       
                        // if(ADM==C2SKEY.adm)   //管理员
                        // {
                        //     memset(C2SKEY.buf,0,100);
                        //     strcpy(C2SKEY.buf,"管理员");
                           
                        //     printf("%s:%s (%s)(%s)\n",C2SKEY.name,C2SKEY.r_buf,C2SKEY.buf,C2SKEY.w_buf);
                        
                        // }
                        // else   //非管理员
                        // {
                         
                         if(strcmp(C2SKEY.r_buf,"quit")==0)

                         {
                           strcpy(C2SKEY.r_buf,"已退出群聊") ;
                            
                            
                         } 
                             if(strcmp(C2SKEY.r_buf,"Q")==0)

                         {
                            memset(C2SKEY.r_buf,0,sizeof(C2SKEY.r_buf));
                            goto s_loop;
                         }
                         //printf("%s:%s (%s)\n",C2SKEY.name,C2SKEY.r_buf,C2SKEY.w_buf);
                         printf("%s:%s  \033[31;40m(%s)\033[0m\n",C2SKEY.name,C2SKEY.r_buf,C2SKEY.w_buf);
                        
                        // }
                     
                        
                         
                           // }
                            
                        

                        
                       }
                        else
                        {
                             printf("%s \n",C2SKEY.r_buf);
                        }
                
                        
                       

                       
                    } 

            }
         }
       
          }
          
          
      }


      
       printf("send成功\n");
      
     
}
         
    return 0;
}




void *W_Fun2(void *a)
{

    int type;
    char buf[100]={0};
    char buf1[100]={0};
    char name[20]={0};
  
    char C;

   while (1)
   {
   
    
   
     printf("\033[31;40m4进入群聊\n5进入私聊\n\033[0m");
    // if(ADM==C2SKEY.ID)
    // {
    //     printf("\033[31;40m9进入管理员权限\n\033[0m");
    //     C2SKEY.adm=ADM;
       
    // }
     if(ADM!=C2SKEY.ID)
    {
        
        C2SKEY.adm=0;
       
    }

    scanf("%d",&type);
    getchar();
    system("clear");
   strcpy(C2SKEY.time,Printf_time());
    if(type==9)
    {
        printf("T踢出群聊\nK禁言\nS解禁\n");
        scanf("%c",&C);
        getchar();
        system("clear");
        if (C=='T')
        {
        printf("请输入踢出群聊姓名\n");
        scanf("%s",name);
        getchar();
        system("clear");
        }
        if(C=='K')
        {
           
        printf("请输入禁言姓名\n");
        scanf("%s",name);
        getchar();
        system("clear");

        }
        if(C=='S')
        {
           
        printf("请输入解禁姓名\n");
        scanf("%s",name);
        getchar();
        system("clear");

        }
        strcpy(C2SKEY.name,name);
        C2SKEY.adm_type=C;
        int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);
            if(ret==-1)
            {
            perror("send");
            return (void *)-1;
            }
   
     

    }
     if(type==4)
         {
      
        printf("群发\n退出(quit)\n");
        char w_buf[100] = {0};
        while(1)
        {
            printf("请输入要写入的内容：\n");
            scanf("%s",buf);
            getchar();
             strcpy(C2SKEY.r_buf,buf);
            strcpy(C2SKEY.w_buf,"群聊信息") ;
             C2SKEY.type=type;
            
            if(strcmp(C2SKEY.r_buf,"quit")==0)
            {
                send(fd,&C2SKEY,sizeof(C2SKEY),0);
                 
                break;
                
            }
          

            if(strcmp(C2SKEY.r_buf,"Q")==0)
            {
                send(fd,&C2SKEY,sizeof(C2SKEY),0);
                
                 return (void*)0;
            }
            else
            {
            int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);
            if(ret==-1)
            {
            perror("send");
            return (void *)-1;
            }
            
            }    
            
        } 
                
    }
     if(type==5)    //私聊
         {
            printf("私聊\n退出(quit)\n");
        char w_buf[100] = {0};
        int ID; 
            printf("请输入私聊账号\n");
            scanf("%d",&ID);
            getchar();
        while(1)
        {      
            printf("请输入要写入的内容：\n");
            scanf("%s",buf1);
            getchar();
           strcpy(C2SKEY.r_buf,buf1);

            if(strcmp(C2SKEY.r_buf,"quit")==0)
             {
                send(fd,&C2SKEY,sizeof(C2SKEY),0);
              
                  break;
               
             }
              
             if(strcmp(C2SKEY.r_buf,"Q")==0)
            {
                send(fd,&C2SKEY,sizeof(C2SKEY),0);
               
                 return (void*)0;
            }
            C2SKEY.ID =ID;
            strcpy(C2SKEY.w_buf,"私聊信息") ;
            C2SKEY.type=type;
            int ret= send(fd,&C2SKEY,sizeof(C2SKEY),0);

            if(ret==-1)
            {
                perror("send");
                return (void *)-1;
            }
        
        }
         }
   }

    return (void *)0;
} 

void* mypasswd(void*a)
{

    char mypwd[20]={0};
    char mypwd1[20]={0};
    int pwd;
    char buf[20]={0};

     while (1)
     {
        printf("请输入旧密码\n");
        memset(C2SKEY.passwd,0,20);
       
            scanf("%d",&pwd);
            getchar();
            system("clear");
            sprintf(buf,"%d",pwd);
            strcpy(C2SKEY.passwd,buf);
            
          send(fd,&C2SKEY,sizeof(C2SKEY),0);
        
          sleep(2);

         printf("buf:%s\n",C2SKEY.buf);
         while(1)
         {
             if(strcmp(C2SKEY.buf,"OK")==0)
         {
             printf("请输入新密码\n");
            scanf("%s",mypwd1);
            getchar();
             printf("请确定新密码\n");
            scanf("%s",mypwd);
            getchar();
            system("clear");
            if(strcmp(mypwd1,mypwd)==0)
            {
                strcpy(C2SKEY.passwd,mypwd);

          send(fd,&C2SKEY,sizeof(C2SKEY),0); 
              return (void* )0;
            }
            else{

                printf("密码不一致\n");

            }

            
         }
         else
         {
            break;
         }
         }
        
            
     }
     return (void* )0;
           

}
char * Printf_time(void)
{
        time_t t= time(NULL);
        char * timep=ctime(&t);
        printf("%s",timep);
        return timep ;
}

void ZERO(void)
{
    memset(C2SKEY.buf, 0, sizeof(C2SKEY.buf));
    memset(C2SKEY.r_buf, 0, sizeof(C2SKEY.r_buf));
    memset(C2SKEY.passwd, 0, sizeof(C2SKEY.passwd));
    memset(C2SKEY.time, 0, sizeof(C2SKEY.time));
    memset(C2SKEY.name, 0, sizeof(C2SKEY.name));
    memset(C2SKEY.w_buf, 0, sizeof(C2SKEY.w_buf));
}