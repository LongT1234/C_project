#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"control.h"
 


void menu (void)
{
 
      printf("*******1.增加信息*******\n");
      printf("*******2.删减信息*******\n");
      printf("*******3.修改信息*******\n");
      printf("*******4.查找信息*******\n");
      printf("*******5.打印全部信息****\n");
      printf("*******6.排序信息*******\n");
      printf("*******0.退出信息*******\n");


}

 /**
  *   功能：添加新的链表节点
  *   参数：无
  *   返回值：成功返回新开辟链表节点的地址 地址类型为 struct link *
  *          失败返回NULL
  * 
 */
struct link *create_link_node()
{
     struct link* pnew = (struct link*)malloc(sizeof(struct link));   //手动开辟链表空间
   if(pnew==NULL)
   {
      return NULL;
   }
   bzero(pnew , sizeof(struct link));    //链表初始化
   pnew ->pnext = NULL ;
   return pnew ;
}
//退出
int  exit_stu(void)                              
{
    return 0;
    printf ("退出\n");
}
//删除

 /**
  *   功能：删除学生信息
  *   参数：链表首地址
  *   返回值：成功返回1
  *          失败返回0
  * 
 */
 int delete_stu(struct link *head)                              
 {
    long id ;
    int num ;
     struct link * ptmp=NULL;
     struct link * pdel=NULL;
     printf("请输入需要删除的学生学号\n");
     scanf("%ld",&id);
     getchar;
     ptmp = head;       
     while((ptmp->pnext)!=NULL)
     { 
      pdel = ptmp->pnext; 
       if(pdel->s.id==id)
       { 
        
        printf("需要删除的学生信息如下\n");
        printf("学号\t\t姓名\t\t性别\t\t分数\n");
            //printf("%ld\t\t",pdel->s.id);
             printf("%ld\t\t",ptmp->s.id);
            printf("%s\t\t%s\t\t%.2f\n",pdel ->s.name,pdel->s.nex,pdel->s.score);
            printf("是否确定删除(1/0)");
            scanf("%d",&num);
            getchar();         
            if(num==0)
            {
              printf("已退出\n");
              return 0 ;
            }
            else if (num==1)
            {
                ptmp->pnext = pdel->pnext;
                free(pdel);
                printf("删除成功\n");
                return 1 ;
            }
       }
       ptmp=ptmp->pnext;
      
      

     }
     printf("没有找到需要删除的学生\n");
     return 0 ;

 } 
 //查找

 /**
  *   功能：查找学生信息
  *   参数：链表首地址
  *   返回值：成功返回1
  *          失败返回0
  * 
 */
 int seek_stu(struct link *head)                
 { 
   int num ;
   long id;
   char name[20]={0};
   printf("1 按学号查找 \n2 按姓名查找 \n3 退出 \n");
   scanf("%d",&num);
   struct link * ptmp = NULL ;
   ptmp = head->pnext ;       
    
     if(num == 1)
     {
        printf("请输入学号\n");
      scanf("%ld",&id);
      while(ptmp!=NULL)
    {    
        if(ptmp->s.id==id)
          {
            printf("您需要打印的学生信息如下\n");
            printf("学号\t\t姓名\t\t性别\t\t分数\n");
            printf("%ld\t\t",ptmp->s.id);
            printf("%s\t\t%s\t\t%.2f\n",ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
            return 1 ;
          }
          ptmp = ptmp->pnext; 
            
     }
      printf("没有您需要查找的学生信息\n");
           return 0 ;
    }
  
        if (num == 2)
      {   
         printf("请输入姓名\n");
         scanf("%s",name);       
         while(ptmp!=NULL)
        {
         
         if(strcmp(ptmp->s.name,name)==0)
         {  
          printf("您需要查找的学生信息如下\n");
            printf("学号\t\t姓名\t\t性别\t\t分数\n");
            printf("%ld\t\t%s\t\t%s\t\t%.2f\n",ptmp->s.id,ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
           
           return 1 ;
         }
          ptmp = ptmp->pnext;       
      }
     printf("没有您需要查找的学生信息\n");
           return 0 ;
      
    }
       printf("成功退出\n");
        return 0 ;
      
      
      
    }
  
  
 

 /**
  *   功能：添加学生信息
  *   参数：链表首地址
  *   返回值：成功返回1
  *          失败返回0
  * 
 */
 int add_stu(struct link *head)                     
 {  
   int id ,flag=0;
    struct link* ptmp = NULL;
   printf ("请输入需要增加的学生学号\n");
    scanf("%d",&id);
    getchar();
    ptmp = head ;
    while(ptmp->pnext!=NULL)
    {
       if(ptmp->s.id==id)
       {
         printf("学生以存在,添加失败\n");
         return 0 ;
       }
       ptmp = ptmp->pnext;
    }
 
    struct link*pnew = create_link_node();
    if(pnew == NULL)
    {
          printf("空间开辟失败\n");
          return 0;
    }
    ptmp->pnext=pnew;
    pnew->s.id = id;
    
    printf ("请输入需要增加的学生姓名\n");
    scanf("%s",pnew->s.name);
    getchar();
    printf ("请输入需要增加的学生性别\n");
    scanf("%s",pnew->s.nex);
    getchar();
    printf ("请输入需要增加的学生分数\n");
    scanf("%f",&pnew->s.score);
    getchar();
    printf("序号\t\t学号\t\t姓名\t\t性别\t\t分数\n");
     ptmp = head->pnext ;
    while (ptmp!=NULL)
    {
      flag++;
      printf("%d\t\t%ld\t\t%s\t\t%s\t\t%.2f\n",flag,ptmp->s.id,ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
       ptmp = ptmp->pnext;
    }
     return 1 ;
 }
 //排序
int sort_stu(struct link *head)                               
{
    printf("排序\n");
    int num ;
    struct link * ptmp=NULL;     
    int i ,j ,flag = 0,count= 0;
    printf("请输入需要任何排序\n");
    printf("1按学号排序\n2按分数排列\n");
    scanf("%d",&num);
    ptmp=head->pnext;
    while(ptmp!=NULL)
    {

      count++;
      ptmp=ptmp->pnext;

    }
    if(num == 1)
    {
      struct link * ps=create_link_node();
      ptmp=head->pnext;
       for(i=0;i<count-1;i++) 
       {
        for(j=0;j<count-1;j++)
        {
         if( (ptmp->s.id)>(ptmp->pnext->s.id))
         {
           ps->s=  ptmp->s;
           ptmp->s= ptmp->pnext->s;
           ptmp->pnext->s = ps->s ;
         }

          ptmp=ptmp->pnext;
        }
         
      ptmp=head;
       } 
    }
    
    else if(num == 2)
    {
      struct link * ps=create_link_node();
      ptmp=head->pnext;
       for(i=0;i<count-1;i++) 
       {
        for(j=0;j<count-1;j++)
        {
         if( (ptmp->s.score)>(ptmp->pnext->s.score))
         {
           ps->s=  ptmp->s;
           ptmp->s= ptmp->pnext->s;
           ptmp->pnext->s = ps->s ;
         }

          ptmp=ptmp->pnext;
        }
         
      ptmp=head;
       } 
    
    }
       printf("序号\t\t分数\t\t姓名\t\t性别\t\t学号\n");
       ptmp = head->pnext ;
    while (ptmp!=NULL)
    {
      flag++;
 printf("%d\t\t%.2f\t\t%s\t\t%s\t\t%ld\n",flag,ptmp->s.score,ptmp ->s.name,ptmp->s.nex,ptmp->s.id);
       ptmp = ptmp->pnext;
    }


   // printf("%d\n",i);
}
//修改
/**
  *   功能：修改学生信息
  *   参数：链表首地址
  *   返回值：成功返回1
  *          失败返回0
  * 
 */

 int modify_stu(struct link *head)                
 {
  long id ;
  int  s ;
   struct link * ptmp = NULL;
     ptmp = head->pnext ;           
        printf("请输入学号\n");
      scanf("%ld",&id);
      getchar();
      while(ptmp!=NULL)
    {    
        if(ptmp->s.id==id)
          {
            printf("您需要修改的学生信息如下\n");
            printf("学号\t\t姓名\t\t性别\t\t分数\n");
            printf("%ld\t\t",ptmp->s.id);
            printf("%s\t\t%s\t\t%.2f\n",ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
            printf("请输入修改的内容\n");
            printf("1成绩修改\n2姓名修改\n3性别修改\n4全部修改\n");
            scanf("%d",&s);
            getchar();
            if(s==1)
            {
                 printf("请输入修改的成绩\n");
                 scanf("%f",&ptmp->s.score);  
                 printf("修改成功\n") ;   
                              
            }
           else if(s==2)
            {
                 printf("请输入修改的姓名\n");
                 scanf("%s",ptmp->s.name);  
                 printf("修改成功\n") ; 
                                    
            }
            else if(s==3)
            {
                 printf("请输入修改的性别\n");
                 scanf("%s",ptmp->s.nex); 
                printf("修改成功\n") ;
                      
            }
            else if(s==4)
            {
                 printf("请输入修改的学号\n");
                 scanf("%ld",&ptmp->s.id); 
                 printf("请输入修改的成绩\n");
                 scanf("%f",&ptmp->s.score); 
                 printf("请输入修改的姓名\n");
                 scanf("%s",ptmp->s.name); 
                 printf("请输入修改的性别\n");
                 scanf("%s",ptmp->s.nex); 
                 printf("修改成功\n") ; 
                    
            }
            else
            {
              printf("已退出\n");
                   return 0 ;
            }  
            printf("您修改后的学生信息如下\n");
            printf("学号\t\t姓名\t\t性别\t\t分数\n");
            printf("%ld\t\t",ptmp->s.id);
            printf("%s\t\t%s\t\t%.2f\n",ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
            return 1 ;
               
          } 
           
        
          ptmp = ptmp->pnext; 
            
     }
     

      printf("没有您需要修改的学生信息\n");
           return 0 ;   
 }
 //打印名单
 int print_stu (struct link *head)             
 {
  int flag=0;
  struct link *ptmp =NULL;
  printf("序号\t\t学号\t\t姓名\t\t性别\t\t分数\n");
     ptmp = head->pnext ;
    while (ptmp!=NULL)
    {
      flag++;
      printf("%d\t\t%ld\t\t%s\t\t%s\t\t%.2f\n",flag,ptmp->s.id,ptmp ->s.name,ptmp->s.nex,ptmp->s.score);
       ptmp = ptmp->pnext;
    }
   return 0;
 }