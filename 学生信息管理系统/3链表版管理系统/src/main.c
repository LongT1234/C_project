#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"control.h"

int main()
{
  int i ;
   struct link* phead = (struct link*)malloc(sizeof(struct link));   //手动开辟链表空间
   if(phead==NULL)
   {
    printf("创建链表头创建失败\n");
      return 0;
   }
   printf("创建成功\n");
   bzero(phead , sizeof(struct link));    //链表初始化
   phead ->pnext = NULL ;
     while(1)
    {
    menu();
    printf("请输入需要执行的操作\n");
    scanf("%d", &i);
    getchar();
    system("clear");
    switch (i)
    {
            case 1 :   add_stu(phead);break;
            case 2 :   delete_stu(phead); break;
            case 3 :   modify_stu(phead); break;
            case 4 :   seek_stu(phead); break;
            case 5 :   print_stu(phead);break;
            case 6 :   sort_stu(phead);break;
            case 0 :   exit_stu();return 0 ;
            default :  
                    printf("输入错误,请重新输入\n");
                    return 0 ;
            
     }
    }
    return 0;
}
