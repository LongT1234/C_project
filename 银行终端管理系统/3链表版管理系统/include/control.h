#ifndef _CONTROL_H_
#define _CONTROL_H_
/*
enum opt
{
   add_stu,delete_stu,modify_stu,seek_stu,print_stu,sort_stu,exit_stu

};
*/
  struct stu
{

    char name[200];       //姓名
    long id ;            //学号
    float score;         //分数
    char nex [200];           //性别
};

struct link
{
     struct stu s;
    struct link*pnext;
     
};
void menu (void);
struct link *create_link_node();
 int add_stu(struct link *head) ;
int sort_stu(struct link *head);                               
 int modify_stu(struct link *head)  ;              
 int print_stu (struct link *head) ;            
 int delete_stu(struct link *head) ;                             
 int seek_stu(struct link *head) ;   
 int exit_stu(void);             
#endif // _CONTROL_H_
