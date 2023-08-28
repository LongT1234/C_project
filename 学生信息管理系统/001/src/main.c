#include <stdio.h>
#include <string.h>
#include "control.h"

int count =0 ;
int main(void )
{
    struct stu stu_info[100] = {0};
    int i;
    
    while(1)
    {
    menu();
    printf("请输入需要执行的操作\n");
    scanf("%d", &i);
    switch (i)
    {
            case 1 :   add_stu(stu_info);break;
            case 2 :   delete_stu(stu_info); break;
            case 3 :   modify_stu(stu_info); break;
            case 4 :   seek_stu(stu_info); break;
            case 5 :   print_stu(stu_info);break;
            case 6 :   sort_stu(stu_info);break;
            case 0 :   exit_stu();return 0 ;
            default :  
                    printf("输入错误,请重新输入\n");return 0 ;
            
     }
    }
    return 0;
}
