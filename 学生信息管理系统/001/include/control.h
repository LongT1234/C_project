#ifndef _CONTROL_H_
#define _CONTROL_H_


extern int count  ;

struct stu
{

   char name[200];
    long id ;    
    float score;
    
};


int  exit_stu(void);                               //退出
 int seek_stu(struct stu seek[]) ;                  //查找
 int add_stu(struct stu id[]);                      //增加
 int sort_stu(struct stu sort[]) ;                               //排序
 int modify_stu(struct stu modiy[]) ;               //修改
 int menu (void);
 int print_stu (struct stu print[]);  
 int delete_stu(struct stu delet[]);                              //删除

#endif

      
