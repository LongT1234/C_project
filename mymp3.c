#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <glob.h>
#include <sys/types.h>
#include <signal.h>

glob_t mp3 = {0};
int i = 0;
pid_t pid = 0;

void Clean_Fun(void)
{
    int a = waitpid(pid,NULL,WNOHANG);
    if(a == 0)
    {
        kill(pid,9);
    }
    system("stty echo");
    system("echo -e \"\033[?25h\"");
}

void Fun(int sig)
{
    int a = 0;
    int b = 0;
    a = waitpid(pid,&b,WNOHANG);
    if(a == pid)
    {
        if(WIFEXITED(b))
        {
            i++;
            if(i==mp3.gl_pathc)
                i=0;
        }
        pid = fork();
        if(pid == 0)
        {
            execlp("mpg123","mpg123",mp3.gl_pathv[i],NULL);
        }
    }
}

int main()
{
    atexit(Clean_Fun);
    signal(17,Fun);
    glob("/home/zsy/0810/目录操作文件属性作业/*.mp3",0,NULL,&mp3);
    for(i=0;i<mp3.gl_pathc;i++)
    {
        printf("%s\n",mp3.gl_pathv[i]);
    }
    i=0;
    pid = fork();
    if(pid == 0)
    {
        execlp("mpg123","mpg123",mp3.gl_pathv[i],NULL);
    }
    if(pid > 0)
    {
        char ch = 0;
        while(1)
        {
            printf("Q:退出 W:上一曲 N:下一曲 S:播放 X:暂停\n");
            scanf("%c",&ch);
            getchar();
            switch (ch)
            {
            case 'Q':
                signal(17,SIG_IGN);
                return 0;
            break;
            case 'W':
                i--;
                if(i<0)
                    i=mp3.gl_pathc-1;
                kill(pid,9);
            break;
            case 'N':
                i++;
                if(i==mp3.gl_pathc)
                    i=0;
                kill(pid,9);
            break;
            case 'S':
                kill(pid,18);
            break;
            case 'X':
                kill(pid,19);
            break;
            }
        }
    }
    return 0;
}