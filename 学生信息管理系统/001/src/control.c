#include <stdio.h>
#include <control.h>




 int menu (void)
  {
     
      printf("*******1.增加信息*******\n");
      printf("*******2.删减信息*******\n");
      printf("*******3.修改信息*******\n");
      printf("*******4.查找信息*******\n");
      printf("*******5.打印全部信息****\n");
      printf("*******6.排序信息*******\n");
      printf("*******0.退出信息*******\n");
    
    return 0 ;

  }
  
/*
功能：添加学生个人信息（学号 姓名 成绩）
参数：     结构体地址
返回值：   错误输入返回0
          添加成功返回1
*/

int add_stu(struct stu add[])
{
 
  long id;
   printf("请输入添加学生姓名\n");
   scanf ("%s",add [count].name);
   getchar();
   printf("请输入添加学生学号\n");
   scanf ("%ld",&id);
   getchar();
   for(int i=1;i<count; i++)
   {
   if(add[i].id==id)
   {
       printf("该学生%ld已经存在，请重新输入\n",id);
       return 0 ;
   }
   }
   add[count].id=id;
    printf("请输入添加学生成绩\n");
   scanf ("%f",&add[count].score);
   getchar();
   count++;
    printf("以输入%d名学生\n",count);
    printf("序号\t\t学号\t\t名字\t\t成绩\n");
    
      for(int i=0;i<(count); i++)
      {
       
    printf("%d\t\t%ld\t\t%s\t\t%.2f\n",i+1,add[i].id,add[i].name,add[i].score); 

      }
  
   return 1;
}
/*
    功能：删减学生个人信息
    参数： 结构体地址
    返回值： 成功返回1 不成功返回0

*/

int delete_stu(struct stu delet[])
{
    int i ;
    long id;
    char s;
  printf("请输入需要删减的学生的学号\n");
  scanf("%ld",&id);
  getchar();
  for( i =0;i<count;i++)
  {
          if(delet[i].id == id)
          {
            printf("您删除的学生信息如下：\n");
            printf("序号\t\t学号\t\t姓名\t\t成绩\n");
            printf("%d\t\t%ld\t\t%s\t\t%.2f\n",i+1,delet[i].id,delet[i].name,delet[i].score); 
  printf("请确认是（y）否（n）删除\n"); 
  scanf("%c",&s);
  getchar();
  if(s=='n')
  {
    return 0 ;
  }
  else if(s=='y')
  {
      for(i=i;i<count ; i++)
      {
    /*
        delete[i].id = delete[i+1].id;
      strcpy ( (delete[i].name) ,(delete[i+1].name));
        delete[i].score = delete[i+1].score;
       // printf("%d\t%d\t%s\t%f\n",i,delete[i].id,delete[i].name,delete[i].score); 
*/
            delet[i] = delet[i+1];
      }
      printf("删除成功\n");
      count--;
        return 1 ;
  }

  }      
  }          
                printf ("您输入的学号不存在，重新输入\n");
                  return 0 ;
}
/*
   功能：修改学生个人信息
   参数：结构体地址
   返回值：成功返回1
*/
int modify_stu(struct stu modiy[])

{
 
 long id;
 int i,j,m ;

 printf("请输入需要修改的学生学号\n");  
  scanf("%ld",&id);
  getchar();
 
    for( i =0;i<count;i++)
  {     
        if(id==modiy[i].id)
          {
            printf("您修改的学生信息如下：\n");
            printf("序号\t\t学号\t\t姓名\t\t成绩\n");
          printf("%d\t\t%ld\t\t%s\t\t%f\n",i+1,modiy[i].id,modiy[i].name,modiy[i].score);
          
          
          while(1)
          {
          printf("请选择需要修改的内容：\n");
          printf("1 姓名\n");
          printf("2 学号\n");
          printf("3 成绩\n");
          scanf("%d",&m);
          if(m == 1)
          {
          printf("请输入修改学生姓名\n");
          scanf ("%s",modiy[i].name);
          getchar();
          break ;
          }
          else if(m == 2)
          {
          printf("请输入修改学生学号\n");
          scanf ("%ld",&id);
          getchar();
          for( j=0;j<count; j++)
          {
            if(modiy[j].id==id)
          {
          modiy[i].id=id; 
          }
          else
          printf("该学生%ld已经不存在，请重新输入\n",id);                   
        
        break ;
        }
          } 
            else if (m == 3)
            {
          printf("请输入添加学生成绩\n");
          scanf ("%f",&modiy[i].score);
          getchar();
          break ;
          }
          else 
          {
            printf("输入错误重新输入\n");

            break ;
          }
          }
          }
          }
          printf("序号\t\t学号\t\t姓名\t\t成绩\n");
          printf("%d\t\t%ld\t\t%s\t\t%f\n",i,modiy[i-1].id,modiy[i-1].name,modiy[i-1].score); 
          printf("添加成功\n");
          
          
          
             return 1;      
         //else if (id!=modiy[i].id)
         printf("学号不存在，请重新输入\n");
           //break ;
         return 0;
  

}
/*
    功能：打印所以学生信息
    参数：结构体地址
    返回值 ：成功打印返回0
*/
  int print_stu (struct stu print[])
  {
    int p ,i;
    struct stu tmp;
    char name[]={0};
    int flage = 0;
    float a,b,c;
    printf("您打印所以的学生信息如下：\n");
    printf("序号\t\t学号\t\t姓名\t\t成绩\n");
    
    for(int i =0;i<count;i++)
  {          
      printf("%d\t\t%ld\t\t%s\t\t%.2f\n",i+1,print[i].id,print[i].name,print[i].score); 

  }

    printf("请输入打印的方式：\n");
    printf ("(1)成绩区间打印\n(2)退出\n");
    scanf("%d",&p);
    for ( int j = 0 ; j<count-1 ;j++)
        {
        for(i=0 ;i<count-1-j;i++)
        {
            if(print[i].score <print[i+1].score)    
              {
              /*  
                  tmp[i].id =print[i].id;
                  print[i] .id= print[i+1].id;
                  print[i+1].id=tmp[i].id;
                  tmp[i].score =print[i].score;
                  print[i] .score= print[i+1].score;
                  print[i+1].score=tmp[i].score;
                strcpy (tmp[i].name,print [i].name);
                strcpy(print[i].name, print[i+1].name);
                strcpy (print[i+1].name,tmp[i].name);
               */
                  tmp = print[i];
                  print[i] = print[i+1];
                  print[i+1] = tmp;
                
              }            
        }
        }
    if(p == 1)
    {
      printf("请输入需要打印的分数区间（xx-xx）(60-80)\n");
      scanf("%f-%f",&a,&b);
      
      if(a>b)
      {
        c = b;
        b = a;
        a = c;
      }        
    printf("序号\t\t学号\t\t姓名\t\t成绩\n");
      for (i=0;i<count ; i++)
      {
        if(print[i].score>=a&&print[i].score<=b)
        {
          flage++;
        printf("%d\t\t%ld\t\t%s\t\t%.2f\n",flage,print[i].id,print[i].name,print[i].score); 
        }
      }
      flage = 0;
    }
    if(p == 3)
    {
        printf("请输入需要打印的姓名\n");
        scanf("%s",name);
        printf("序号\t\t学号\t\t姓名\t\t成绩\n");
        
        
        for(i=0;i<=count;i++)
        {
          if (i==count )
            {
          printf ("学生不存在，重新输入\n");
            break ;
            }  
                    
          else if(*name==*(print[i].name))

          {            
          flage++;
          printf("%d\t\t%ld\t\t%s\t\t%.2f\n",flage,print[i].id,print[i].name,print[i].score);
            
          } 
        }
                                
        
        
    }
    
    
return 0 ;
}

/*
    功能：查找学生信息
    参数：结构体地址
    返回值：存在返回1
          不存在返回0


*/
int seek_stu(struct stu seek[])
{
    long id ;
  printf("请输入需要查找的学生学号\n");
  scanf("%ld",&id);
  getchar();
  for(int i =0;i<count;i++)
  {
          if(id==seek[i].id)
          {
            printf("您查找的学生信息如下：\n");
            printf("序号\t学号\t姓名\t成绩\n");
            printf("%d\t%ld\t%s\t%f\n",i+1,seek[i].id,seek[i].name,seek[i].score); 
            return 1;
                  
          }
      
  }
              printf("该学生不存在\n");
              return 0 ;
  
}

/*

    功能：按学号排序（1）按分数排序（2）
    参数：结构体地址
    返回值： 按学号排序（1）返回0
            按分数排序（2）返回1
*/

int sort_stu(struct stu sort[])   
{
  int a ,i;
  struct stu tmp ;
  
printf("请输入需要排列的顺序：按学号排序（1）按分数排序（2）\n");
scanf("%d",&a);
getchar ();
    if (a==1)
    {
        for ( int j = 0 ; j<count-1 ;j++)
        {
        for(i=0 ;i<count-1-j;i++)
        {
            if(sort[i].id >sort[i+1].id)    
              {
                  
                  /*tmp[i].id =sort[i].id;
                  sort[i] .id= sort[i+1].id;
                  sort[i+1].id=tmp[i].id;
                  tmp[i].score =sort[i].score;
                  sort[i] .score= sort[i+1].score;
                  sort[i+1].score=tmp[i].score;
                strcpy (tmp[i].name,sort [i].name);
                strcpy(sort[i].name, sort[i+1].name);
                strcpy (sort[i+1].name,tmp[i].name);
                */
                tmp = sort[i];
                  sort[i] = sort[i+1];
                  sort[i+1] = tmp;
                
              }            
        }
        }
        
        printf("序号\t\t学号\t\t姓名\t\t分数\n");
        for(i=0;i<count ;i++)
        {
          
          printf("%d\t\t%ld\t\t%s\t\t%.2f\n",i+1,sort[i].id,sort[i].name,sort[i].score);
        }
        return 0 ;
    }
      if(a==2)
      {
          for ( int j = 0 ; j<count-1 ;j++)
        {
        for(i=0 ;i<count-1-j;i++)
        {
            if(sort[i].score >sort[i+1].score)    
              {
                /*
                  tmp[i].id =sort[i].id;
                  sort[i] .id= sort[i+1].id;
                  sort[i+1].id=tmp[i].id;
                  tmp[i].score =sort[i].score;
                  sort[i] .score= sort[i+1].score;
                  sort[i+1].score=tmp[i].score;
                strcpy (tmp[i].name,sort [i].name);
                strcpy(sort[i].name, sort[i+1].name);
                strcpy (sort[i+1].name,tmp[i].name);
                */
               tmp = sort[i];
                  sort[i] = sort[i+1];
                  sort[i+1] = tmp;
              }            
        }
        }
        
        printf("序号\t\t分数\t\t姓名\t\t学号\n");
        for(i=0;i<count ;i++)
        {
          
          printf("%d\t\t%.2f\t\t%s\t\t%ld\n",i+1,sort[i].score,sort[i].name,sort[i].id);
        }
      }
      return 1;
    }


/*
  功能：退出学生信息管理系统
  参数：无
  返回值：0


*/
  int exit_stu(void)
  {

  printf("即将退出学生管理系统\n");

return 0 ;
    
  }
