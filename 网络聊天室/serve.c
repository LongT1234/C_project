#include <all.h>

int reg_cli(int fd);
int off_cli(int fd);
int on_cli(int fd);
int all_chat_f(int fd);
int Private_Chat_f(int fd);
int off_line_f(int fd);
int Account(void);
char *Printf_time(void);
void ZERO(void);
int passwd(int fd);
struct SER S2CKEY;
struct CLI Printf;
int c_fd[50] = {0};

int count = 0;
char my_adm[20] = {0};
int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    perror("socket");
    int val = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1)
    {
        perror("bind");
        return -1;
    }
    perror("bind");

    int ren = listen(sockfd, 50);
    if (ren == -1)
    {
        perror("listen");
        return -1;
    }

    int maxfd;
    maxfd = sockfd;
    fd_set readset, baskupset;
    FD_ZERO(&baskupset);
    FD_SET(sockfd, &baskupset);
    struct sockaddr_in c_addr;
    socklen_t len = sizeof(c_addr);

    char buf[255] = {0};
    char w_buf[1024] = {0};
    char sql[255] = {0};
    char aaa[1024] = {0};
    char myfd[255] = {0};
    char myid[255] = {0};
    char num[255] = {0};
    char s[255] = {0};
    char rw_buf[100] = {0};
    struct SER S2CKEY;
    char **a;

    while (1)
    {
       
        readset = baskupset;
        int res = select(maxfd + 1, &readset, NULL, NULL, NULL);

        // if(res>0)   //判断是否异动

        // 连接套接字异动，有连接请求
        if (FD_ISSET(sockfd, &readset))
        {

            c_fd[count] = accept(sockfd, (struct sockaddr *)&c_addr, &len);
            if (maxfd < c_fd[count])
            {
                maxfd = c_fd[count];
            }
            FD_SET(c_fd[count], &baskupset);
            count++;
            if (res == 1)
            {
                continue;
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("服务器启动\n");
            if (FD_ISSET(c_fd[i], &readset)) // c_fd[i]发生异动，（c_fd[i]发消息了）
            {
                 
        
                // memset(S2CKEY.r_buf,0,sizeof(S2CKEY.r_buf));

                int rcv = recv(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);
                printf("接收成功rcv\n");

                if (rcv > 0)

                {

                    // if ((S2CKEY.type == 9)) // 管理员权限
                    // {
                    //     MYSQL *con = mysql_init(NULL);

                    //     con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
                    //     if (con == NULL)
                    //     {
                    //         printf("连接失败\n");
                    //         return -1;
                    //     }
                    //     printf("连接成功\n");

                    //     if (S2CKEY.adm_type == 'T') // 踢人
                    //     {

                    //         memset(sql, 0, sizeof(sql));
                    //         sprintf(sql, "select* from QQdata where name=%s", S2CKEY.name);

                    //         int res = mysql_query(con, sql);
                    //         MYSQL_RES *t = mysql_store_result(con);
                    //         a = mysql_fetch_row(t);

                    //         S2CKEY.adm_type = 'K';
                    //         memset(sql, 0, sizeof(sql));
                    //         for (size_t i = 0; i < count; i++)
                    //         {

                    //             memset(sql, 0, sizeof(sql));
                    //             sprintf(sql, "%d", c_fd[i]);
                    //             if (strcmp(sql, a[4]) == 0)
                    //             {
                    //                 send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);
                    //             }
                    //         }
                    //         memset(sql, 0, sizeof(sql));
                    //         sprintf(sql, "update QQdata set 群聊=0 where name=%s;", S2CKEY.name);
                    //     }
                    // }

                    if ((S2CKEY.type == 5)) // 私聊
                    {

                        char m_adm[100]={0};
                          MYSQL *con = mysql_init(NULL);

                            con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
                            if (con == NULL)
                            {
                                printf("连接失败\n");
                                return -1;
                            }
                            printf("连接成功\n");
                            
                            memset(sql, 0, sizeof(sql));
                            
                            // sprintf(sql, "select* from QQdata where ID=%d", S2CKEY.ID);
                            
                            //   int res = mysql_query(con, sql);
                            // MYSQL_RES *t = mysql_store_result(con);
                            // if (res != 0)
                            // {
                            //     printf("添加表格内容失败\n");
                            //     return -1;
                            // }
                        if (strcmp(S2CKEY.r_buf, "quit") == 0)
                        {

                            send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);

                            //break;
                        }
                           
                                if (strcmp(S2CKEY.r_buf, "Q") == 0)
                        {


                            send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);

                            //break;
                        }
                        else
                        {
                             memset(sql, 0, sizeof(sql));

                            sprintf(sql, "select* from QQdata where ID=%d", S2CKEY.ID);

                             res = mysql_query(con, sql);
                             
                            MYSQL_RES * t = mysql_store_result(con);
                            if (res != 0)
                            {
                                printf("添加表格内容失败\n");
                                return -1;
                            }
                            
                                 a = mysql_fetch_row(t);
                                 if(a[1]!=NULL)
                                 {
                                    memset(myid, 0, sizeof(myid));
                            memset(num, 0, sizeof(num));
                            memset(myfd, 0, sizeof(myfd));

                            sprintf(myid, "%d", S2CKEY.ID);
                            sprintf(num, "1");

                            printf("a[3]:%s\n", a[3]);
                            printf("a[4]:%s\n", a[4]);

                            for (int j = 0; j < count; j++)
                            {
                                sprintf(myfd, "%d", c_fd[j]);

                                if ((strcmp(a[3], "1") == 0) && (strcmp(a[4], myfd) == 0))
                                {
                                    int ft = open("1.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
                                    if (ft == -1)
                                    {
                                        perror("open");
                                        return -1;
                                    }
                                    memset(aaa, 0, sizeof(aaa));
                                    sprintf(aaa, "select* from QQdata where cfd=%d", c_fd[i]);
                                    mysql_query(con, aaa); // 寻找数据
                                    MYSQL_RES *t = mysql_store_result(con);
                                    char **a = mysql_fetch_row(t);
                                    memset(aaa, 0, sizeof(aaa));
                                    sprintf(aaa, "%s", a[0]);
                                    strcpy(S2CKEY.name, aaa);
                                    strcpy(S2CKEY.time, Printf_time());        // 时间
                                    send(c_fd[j], &S2CKEY, sizeof(S2CKEY), 0); // 发送

                                    printf("r_buf:%s\n", S2CKEY.r_buf);
                                    // read(ft,S2CKEY.r_buf,sizeof(S2CKEY.r_buf));
                                    // lseek(ft,0,0);
                                    write(ft, &S2CKEY, sizeof(S2CKEY));
                                    write(ft, &S2CKEY, sizeof(S2CKEY));
                                    close(ft);
                                }

                            }
                                 }
                                 
                        }
                    
                           
                                 
                            
                            
                           

                        

                            


                        
                        
                    }
                    if ((S2CKEY.type == 4)) // 群聊
                    {
                     if (strcmp(S2CKEY.r_buf, "quit") == 0)
                        {

                            send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);

                            //break;
                        }

                        if (strcmp(S2CKEY.r_buf,"Q") == 0)
                        {

                            send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);

                           // break;
                        }
                        else
                        {
                            MYSQL *con = mysql_init(NULL);                                                 // 初始化数据库核心结构体
                       
                        con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0); // 将用户套接字改为-1,在线状态改为0
                       
                            // if(strcmp(a[7],"0")==0)//已踢出群聊
                            // {
                            //     S2CKEY.adm_type=='K';
                            //     send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0); // 发送
                            // }
                            // else
                            // {
                               memset(aaa, 0, sizeof(aaa));
                        sprintf(aaa, "select* from QQdata where cfd=%d", c_fd[i]);

                        mysql_query(con, aaa); // 寻找数据
                       MYSQL_RES * t = mysql_store_result(con);
                       char ** a = mysql_fetch_row(t);
                        memset(aaa, 0, sizeof(aaa));
                        sprintf(aaa, "%s", a[0]);
                        strcpy(S2CKEY.time, Printf_time()); // 时间
                        

                        for (int j = 0; j < count; j++)
                        {
                            if (j != i) // 除自己外发送信息
                            {

                                strcpy(S2CKEY.name, aaa);
                                memset(aaa, 0, sizeof(aaa));
                              
                                printf("count:%s\n", S2CKEY.r_buf);
                                printf("r_buf:%s\n", S2CKEY.r_buf);
                                
                                printf("S2CKEY.adm:%d\n",S2CKEY.adm);

                                send(c_fd[j], &S2CKEY, sizeof(S2CKEY), 0);
                            }
                        }

                        int fd = open("1.txt", O_RDWR | O_APPEND, 0644);
                        if (fd == -1)
                        {
                            perror("open");
                            return -1;
                        }

                        printf("adm1 %s\n", S2CKEY.r_buf);
                        strcpy(S2CKEY.time, Printf_time()); // 时间
                        write(fd, &S2CKEY, sizeof(S2CKEY));

                        close(fd); 
                           // }
                        }

                        
                        
                    }
                }

                if (S2CKEY.type==0||(rcv == 0)) // 下线
                {
                    char X_name[20] = {0};
                    MYSQL *con = mysql_init(NULL);                                                 // 初始化数据库核心结构体
                    con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0); // 将用户套接字改为-1,在线状态改为0
                    memset(aaa, 0, sizeof(aaa));
                    sprintf(aaa, "select* from QQdata where cfd=%d", c_fd[i]);

                    mysql_query(con, aaa); // 寻找数据
                    MYSQL_RES *t = mysql_store_result(con);
                    char **a = mysql_fetch_row(t);
                    sprintf(X_name, "%s", a[0]);
                    S2CKEY.online = 0;
                    memset(aaa, 0, sizeof(aaa));
                    send(c_fd[i], &S2CKEY, sizeof(S2CKEY), 0);
                    sprintf(aaa, "update QQdata set online=0, cfd=0 where cfd=%d", c_fd[i]);
                    mysql_query(con, aaa); // 将套接字保存在数据库中
                    strcpy(S2CKEY.name, X_name);
                    sprintf(S2CKEY.r_buf, "%s已下线\n", S2CKEY.name);

                    printf("count1:%d\n", count);

                    for (int j = 0; j < count; j++)
                    {
                        if (j != i) // 除自己外发送信息
                        {

                            printf("%d客户端下线\n", c_fd[i]);
                            S2CKEY.online = 0;

                            strcpy(S2CKEY.time, Printf_time()); // 时间

                            send(c_fd[j], &S2CKEY, sizeof(S2CKEY), 0);
                            
                            FD_CLR(c_fd[i], &baskupset);
                        }

                        if (count == 1)
                        {
                            S2CKEY.online = 0;
                            memset(aaa, 0, sizeof(aaa));
                            send(c_fd[j], &S2CKEY, sizeof(S2CKEY), 0);
                            sprintf(aaa, "update QQdata set online=0, cfd=0 where cfd=%d", c_fd[i]);
                            mysql_query(con, aaa); // 将套接字保存在数据库中
                            FD_CLR(c_fd[i], &baskupset);
                        }
                    }
                    for (int k = i; k < count - 1; k++)
                    {
                        c_fd[k] = c_fd[k + 1];
                    }
                    count--;
                }
                else
                {

                    switch (S2CKEY.type)
                    {

                    case 1:
                        reg_cli(c_fd[i]);
                        break;
                    case 2:
                        on_cli(c_fd[i]);
                        break;
                    case 3:
                        off_cli(c_fd[i]);
                        break;
                    case 4:
                        printf("进入群聊\n");
                        break;
                    case 5:
                        printf("进入私聊\n");
                        break;
                    case 6:
                        off_line_f(c_fd[i]);
                        break;
                    case 8:
                        passwd(c_fd[i]);
                        break;

                    default:
                        printf("ERR\n");
                    }
                }
            }
          
        }
    }

    return 0;
}

int Account(void) // 保证银行卡号不重复
{

    int id = 20230828;
    int fd = open("account.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }
    read(fd, &id, sizeof(int));
    printf("id1 = %d\n", id);
    id++;
    lseek(fd, 0, 0);
    write(fd, &id, sizeof(int));
    close(fd);
    return id;
}

int reg_cli(int fd) // 注册
{

    printf("注册成功\n");
    char buf[20] = {"12345"};
    char sql[1024] = {0};
    // recv(fd,&S2CKEY,sizeof(S2CKEY),0);
    while (1)
    {

        S2CKEY.ID = Account();
        strcpy(S2CKEY.passwd, buf);
        int ret = send(fd, &S2CKEY, sizeof(S2CKEY), 0);
        if (ret == -1)
        {
            perror("send");
            return -1;
        }
        recv(fd, &S2CKEY, sizeof(S2CKEY), 0);
        MYSQL *con = mysql_init(NULL);
        int value = 0; // 数据库序号
        con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
        if (con == NULL)
        {
            printf("连接失败\n");
            return -1;
        }

        sprintf(sql, "INSERT INTO QQdata values('%s','%d','%s','0','%d','0','1','1')", S2CKEY.name, S2CKEY.ID, S2CKEY.passwd, fd);

        int res = mysql_query(con, sql); // 添加到数据库

        if (res != 0)
        {
            printf("添加表格内容失败\n");
            return -1;
        }

        break;
        printf("添加表格内容成功\n");
    }

    return 0;
}
int on_cli(int fd) // 登陆
{
    char buf[100] = {0};
    char arr[100] = {0};
    char myadm[100] = {0};
    int row = 0;
    int column = 0;
    MYSQL *con;
    char **a;
    int flog = 0;

   
        printf("登陆\n");
        int rcv = recv(fd, &S2CKEY, sizeof(S2CKEY), 0);
        if (rcv == -1)
        {
            perror("recv");
            return -1;
        }
        perror("recv");

        printf("接收成功\n");

        // 连接数据库
        con = mysql_init(NULL);
        con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
        if (con == NULL)
        {
            printf("连接失败\n");
            return -1;
        }

        // 执行SQL语句，获取表格中的内容。

        // sprintf(buf,"select * from QQdata");
        sprintf(buf, "select* from QQdata ");
        int res = mysql_query(con, buf);
        MYSQL_RES *t = mysql_store_result(con);

        column = mysql_num_fields(t);
        row = mysql_num_rows(t);

        if (row = 0)
        {
            strcpy(S2CKEY.feedback, "用户不存在请重新登陆\n");
            return -1;
        }
         

        while ((a = mysql_fetch_row(t)))
        {

            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%d", S2CKEY.ID);
            printf("passwd%s\n", S2CKEY.passwd);
            printf("ID%d\n", S2CKEY.ID);

            if ((!strcmp(buf, a[1])) && (!strcmp(S2CKEY.passwd, a[2])))
            {
                if(strcmp(a[3],"1")==0)
                {
                   strcpy(S2CKEY.feedback, "账号已登陆\n");
                    send(fd, &S2CKEY, sizeof(S2CKEY), 0);
                }
                else
                {
                     printf("%s\n%s\n", a[2], a[1]);
                memset(S2CKEY.feedback, 0, sizeof(S2CKEY.feedback)); 
                strcpy(S2CKEY.feedback, "登录成功");
                //sprintf(S2CKEY.feedback,"登录成功");
                strcpy(S2CKEY.name, a[0]);
                 memset(my_adm, 0, sizeof(my_adm));
                S2CKEY.online = 1;
                sprintf(arr, "update QQdata set online=%d, cfd=%d where ID=%d", S2CKEY.online, fd, S2CKEY.ID);
                // sprintf(arr,"INSERT INTO QQdata values('%s','%d','%s','1','%d')",S2CKEY.name,S2CKEY.ID,S2CKEY.passwd,fd);
                mysql_query(con, arr); // 将套接字保存在数据库中
                int ret = send(fd, &S2CKEY, sizeof(S2CKEY), 0);
               
                if (ret == -1)
                {
                    perror("send");

                    return -1;
                }
                  printf("登陆成功\n");

                 
                }
                
                printf("账号已登陆\n");
              
              
                return 0;
            }
        }
                S2CKEY.online = 0;
                sprintf(arr, "update QQdata set online=%d, cfd=%d where ID=%d", S2CKEY.online, fd, S2CKEY.ID);
                // sprintf(arr,"INSERT INTO QQdata values('%s','%d','%s','1','%d')",S2CKEY.name,S2CKEY.ID,S2CKEY.passwd,fd);
                mysql_query(con, arr); // 将套接字保存在数据库中
       mysql_close(con);
               printf("登陆失败\n");
        strcpy(S2CKEY.feedback, "您的密码或账号错误");
        send(fd, &S2CKEY, sizeof(S2CKEY), 0);
    
     
    

    // 关闭连接

    return 0;
}
int off_cli(int fd) // 注销
{
    char buf[100] = {0};
    char arr[100] = {0};
    int row = 0;
    int column = 0;
    MYSQL *con;
    char **a;
    int flog = 0;

    while (1)
    {

        int rcv = recv(fd, &S2CKEY, sizeof(S2CKEY), 0);
        if (rcv == -1)
        {
            perror("recv");
            return -1;
        }
        perror("recv");

        printf("接收成功\n");
        printf("passwd%s\n", S2CKEY.passwd);
        printf("ID%d\n", S2CKEY.ID);
        // 连接数据库
        con = mysql_init(NULL);
        con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
        if (con == NULL)
        {
            printf("连接失败\n");
            return -1;
        }

        // 执行SQL语句，获取表格中的内容。

        // sprintf(buf,"select * from QQdata");
        sprintf(buf, "select* from QQdata ");
        int res = mysql_query(con, buf);
        MYSQL_RES *t = mysql_store_result(con);

        column = mysql_num_fields(t);
        row = mysql_num_rows(t);

        if (row = 0)
        {
            strcpy(S2CKEY.feedback, "用户不存在请重新登陆\n");
            return -1;
        }
        printf("1send\n");

        while ((a = mysql_fetch_row(t)))
        {

            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%d", S2CKEY.ID);
            if ((!strcmp(buf, a[1])) && (!strcmp(S2CKEY.passwd, a[2])))
            {
                printf("%s\n%s\n", a[2], a[1]);
                sprintf(arr, "delete from QQdata where ID=%d", S2CKEY.ID);
                mysql_query(con, arr);
                strcpy(S2CKEY.feedback, "注销成功");
                int ret = send(fd, &S2CKEY, sizeof(S2CKEY), 0);
                if (ret == -1)
                {
                    perror("send");
                    return -1;
                }
                flog = 1;
                break;
            }
        }

        strcpy(S2CKEY.feedback, "注销失败");
        break;
    }

    // 关闭连接
    mysql_close(con);
    printf("注销成功\n");
    return 0;
}

int off_line_f(int fd)
{
    // int flog = 0;
    // printf("查看聊天记录成功\n");
    // fd = open("1.txt", O_RDWR | O_APPEND, 0644);
    // if (fd == -1)
    // {
    //     perror("open");
    //     return -1;
    // }
    // // lseek( fd,0, SEEK_END);

    // while (read(fd, &Printf, sizeof(Printf)) != 0)
    // {
    //     if (flog != 0)
    //     {

    //         printf("%s:%s\n%s\n", Printf.name, Printf.r_buf, Printf.time);
            
    //     }
    //     flog++;
    // }
    // Printf.type = 6;
    // send(fd, &Printf, sizeof(Printf), 0);
    // close(fd);
    printf("打印完成\n");

    return 0;
}

char *Printf_time(void)
{
    time_t t = time(NULL);
    char *timep = ctime(&t);
    printf("%s", timep);
    return timep;
}

int passwd(int fd)
{
    char buf[255] = {0};
    // 连接数据库
    MYSQL *con = mysql_init(NULL);
    con = mysql_real_connect(con, "localhost", "root", "1", "QQdata", 0, NULL, 0);
    if (con == NULL)
    {
        printf("连接失败\n");
        return -1;
    }

    // 执行SQL语句，获取表格中的内容。

    // sprintf(buf,"select * from QQdata");
    sprintf(buf, "select* from QQdata where cfd=%d", fd);
    int res = mysql_query(con, buf);
    MYSQL_RES *t = mysql_store_result(con);
    char **a = mysql_fetch_row(t);
    // recv(fd,&S2CKEY,sizeof(S2CKEY),0);
    printf("pwd:%s\n", S2CKEY.passwd);

    if (!strcmp(a[2], S2CKEY.passwd))
    {
        printf("2");

        strcpy(S2CKEY.buf, "OK");
        strcpy(S2CKEY.time, Printf_time());
        printf("buf:%s\n", S2CKEY.buf);
        int ret = send(fd, &S2CKEY, sizeof(S2CKEY), 0);
        if (ret == -1)
        {
            perror("send");
            return -1;
        }
        ZERO();
        recv(fd, &S2CKEY, sizeof(S2CKEY), 0);
        printf("修改成功\n");

        memset(buf, 0, 255);
        S2CKEY.online = 0;
        sprintf(buf, "update QQdata set passwd=%s,online=%d where cfd=%d ", S2CKEY.passwd,S2CKEY.online,fd);
        mysql_query(con, buf);
        strcpy(S2CKEY.buf, "成功");
        printf("buf:%s\n", S2CKEY.buf);

        send(fd, &S2CKEY, sizeof(S2CKEY), 0);
        return 0;
    }
    strcpy(S2CKEY.buf, "失败");
    printf("修改失败\n");
    send(fd, &S2CKEY, sizeof(S2CKEY), 0);

    return 0;
}

void ZERO(void)
{
    memset(S2CKEY.buf, 0, sizeof(S2CKEY.buf));
    memset(S2CKEY.r_buf, 0, sizeof(S2CKEY.r_buf));
    memset(S2CKEY.passwd, 0, sizeof(S2CKEY.passwd));
    memset(S2CKEY.time, 0, sizeof(S2CKEY.time));
    memset(S2CKEY.name, 0, sizeof(S2CKEY.name));
    memset(S2CKEY.w_buf, 0, sizeof(S2CKEY.w_buf));
}
