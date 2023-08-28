#include "stdio.h"
#include "string.h"
/**
 * 学生信息管理系统
 * 增
 * 删
 * 改
 * 查
 * 排序
 * 插入
 * 退出
 * 打印所有
*/

#define MAX_SIZE  10

struct stu
{
    int id;//学号
    char name[12];//姓名
    float score;//成绩
};
//定义枚举类型
enum  opt
{
    //规定，第一个是ADD_INFO，最后一个是EXIT
    ADD_INFO,DELETE_INFO,CHANGE_INFO,SEARCH_INFO,SORT_INFO,
    INSERT_INFO,PRINT_ALL,EXIT
};

//计数
unsigned int count = 0;

enum  opt menu(void);


int add_info(struct stu s[]);
int search_info(struct stu s[]);
int delete_info(struct stu s[]);
int sort_info(struct stu s[]);
int change_info(struct stu s[]);
int insert_info(struct stu s[]);
int print_all_info(struct stu s[]);


int Check_stu_id(int id,struct stu s[]);

int main(int argc, char const *argv[])
{
    enum  opt x;
    //定义函数指针数组
    int (*p[])(struct stu s[]) = 
    {
        add_info,        //0
        delete_info,     //1
        change_info,     //2
        search_info,     //3
        sort_info,       //4
        insert_info,     //5
        print_all_info   //6
    };
    char *opt_name[] = 
    {
        "add_info",        //0
        "delete_info",     //1
        "change_info",     //2
        "search_info",    //3
        "sort_info",       //4
        "insert_info",     //5
        "print_all_info"   //6
    };



    struct stu stu_info[MAX_SIZE] = 
    {
        {3,"zhang三",3},
        {6,"6",33},
        {10,"zhang三",3333},
        {88,"li斯",66},
        {23,"li四",78},
        {9,"li龙",99},
        {101,"xiao红",101}
    };
    count = 7;
    while(1)
    {
        x = menu();
        if(x == EXIT)
            return 0;
        //根据菜单函数的返回值，调用不同的函数。
        printf("%s %s\n",
            opt_name[x],
            p[x](stu_info)?"成功":"失败");   
    }
    return 0;
}



/*
int main(int argc, char const *argv[])
{
    enum  opt x;
    struct stu stu_info[MAX_SIZE] = 
    {
        {3,"zhang三",3},
        {6,"6",33},
        {10,"zhang三",3333},
        {88,"li斯",66},
        {23,"li四",78},
        {9,"li龙",99},
        {101,"xiao红",101}
    };
    count = 7;
    printf("sizeof(enum  opt) = %ld\n",sizeof(enum  opt));
    printf("sizeof(x) = %ld\n",sizeof(x));
    while(1)
    {
        x = menu();
        switch(x)
        {
            case ADD_INFO: 
                if(add_info(stu_info))
                    printf("添加成功\n");
                else
                    printf("添加失败\n");
            break;
            case SEARCH_INFO: 
                if(search_info(stu_info))
                    printf("查询成功\n");
                else
                    printf("查询失败\n");
                break;
            case DELETE_INFO: 
                if(delete_info(stu_info))
                    printf("删除成功\n");
                else
                    printf("删除失败\n");
                break;
            case SORT_INFO: 
            if(sort_info(stu_info))
                    printf("排序成功\n");
                else
                    printf("排序失败\n");
            break;
            case PRINT_ALL: 
            if(print_all_info(stu_info))
                    printf("查看所有信息成功\n");
                else
                    printf("查看所有信息失败\n");
            break;
            case CHANGE_INFO: 
            if(change_info(stu_info))
                    printf("修改成功\n");
                else
                    printf("修改失败\n");
            break;
            case INSERT_INFO: 
            if(insert_info(stu_info))
                    printf("插入成功\n");
                else
                    printf("插入失败\n");
            break;
            case EXIT:  printf("程序即将结束\n");return 0;
        }
    }
    return 0;
}
*/

enum  opt menu(void)
{
    enum  opt num;
    printf("\033[31m");
    printf("%d.增加信息\n",ADD_INFO);
    printf("%d.删除信息\n",DELETE_INFO);
    printf("%d.修改信息\n",CHANGE_INFO);
    printf("%d.查询信息\n",SEARCH_INFO);
    printf("%d.排序信息\n",SORT_INFO);
    printf("%d.插入信息\n",INSERT_INFO);
    printf("%d.查看所有信息\n",PRINT_ALL);
    printf("%d.退出系统\n",EXIT);
    printf("请输入要执行的操作(%d~%d)\n",ADD_INFO,EXIT);
    printf("\033[0m");
    scanf("%d",(int *)&num);
    getchar();
    //错误控制

    return num;
}

//添加信息  1    0
int add_info(struct stu s[])
{
    int id;
    printf("函数%s被调用\n",__FUNCTION__);
    //判断空间是否满了
    if(count >= MAX_SIZE)
    {
        printf("系统空间不足，请联系管理员扩容\n");
        return 0;
    }

    //读取信息 存储信息
    printf("请输入要添加学生的学号\n");
    scanf("%d",&id);
    getchar();
    
    if(Check_stu_id(id,s) != -1)
    {
        printf("学号为%d的学生已存在\n",id);
        return 0;
    }
    s[count].id = id;
    printf("请输入要添加学生的姓名\n");
    scanf("%s",s[count].name);
    getchar();
    printf("请输入要添加学生的成绩\n");
    scanf("%f",&s[count].score);
    getchar();

    //更新计数
    count++;
    return 1;
}

int print_all_info(struct stu s[])
{
    int i;
    printf("函数%s被调用\n",__FUNCTION__);
    printf("系统内部总共有%d名学生，详细信息如下\n",count);
    for(i=0;i<MAX_SIZE;i++)
    {
        // printf("s[%d].name[0]=%x\n",i,s[i].name[0]);
        printf("%d\t%s\t%.2f\n",s[i].id,s[i].name,s[i].score);
    }
    return 1;
}


//根据学号判断学生是否存在
//不存在返回-1，存在返回下标
int Check_stu_id(int id,struct stu s[])
{
    int i = 0;
    for(i=0;i<count;i++)
    {
        if(id == s[i].id)
            return i;
    }
    return -1;
}

//查询
int search_info(struct stu s[])
{
    int id;
    int ret;
    int num;
    char name[32] = {0};
    int i = 0;
    int flag;
    enum select
    {
        ID=1,NAME,QUIT
    };

    printf("%d.按学号查询\n%d.按姓名查询\n%d.退出查询\n",ID,NAME,QUIT);
    printf("请输入具体的查询依据\n");
    scanf("%d",&num);
    getchar();
    if(num == 1)
    {
        printf("请输入要查询的学号\n");
        scanf("%d",&id);
        getchar();
        ret = Check_stu_id(id,s);
        if(ret == -1)
        {
            printf("您要查询的学生不存在\n");
            return 0;
        }
        printf("ret = %d\n",ret);
        printf("您要查询的学生信息如下：\n");
        printf("学号:%d\t姓名：%s\t成绩：%.2f\n",
                s[ret].id,
                s[ret].name,
                s[ret].score);
    }
    else if(num == 2)
    {
        printf("请输入要查询的姓名\n");
        scanf("%s",name);
        getchar();
        printf("您要查询的学生信息如下：\n");
        flag = 0;
        for(i=0;i<count;i++)
        {
            if(strcmp(s[i].name,name) == 0)
            {
                printf("学号:%d\t姓名：%s\t成绩：%.2f\n",
                        s[i].id,
                        s[i].name,
                        s[i].score);
                flag = 1;
            }
            
        }
        if(flag == 0)
        {
            printf("查无此人\n");
            return 0;
        }
    }
    return 1;
}
//删除
int delete_info(struct stu s[])
{
    int id,del_pos;
    int i;
    if(count ==0)
    {
        printf("系统内没有信息，请先添加\n");
        return 0;
    }
    printf("请输入要删除的学号\n");
    scanf("%d",&id);
    getchar();
    del_pos = Check_stu_id(id,s);
    if(del_pos == -1)
    {
        printf("您要删除的学生不存在\n");
        return 0;
    }
    printf("del_pos = %d\n",del_pos);
    printf("您要删除的学生信息如下：\n");
    printf("学号:%d\t姓名：%s\t成绩：%.2f\n",
            s[del_pos].id,
            s[del_pos].name,
            s[del_pos].score);
        // 3        6
    for(i=del_pos;i<count-1;i++)
    {
        s[i] = s[i+1];
    }
    s[count-1].id = 0;
    s[count-1].score = 0;
    strcpy(s[count-1].name," ");

    count--;
    return 1;
}

//排序
int sort_info(struct stu s[])
{

    int i,j;
    struct stu t;
    for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-1-i;j++)
        {
            // if(s[j].name[0] > s[j+1].name[0])
            if(s[j].id > s[j+1].id)
            {
                t = s[j];
                s[j] = s[j+1];
                s[j+1] = t;
            }
        }
    }
    return 1;
}


//修改信息   成功返回1，失败返回0
int change_info(struct stu s[])
{
    int id;
    int change_pos;
    char ch;
    printf("请输入要修改的学号\n");
    scanf("%d",&id);
    getchar();
    change_pos = Check_stu_id(id,s);
    if(change_pos == -1)
    {
        printf("您要修改的学生不存在\n");
        return 0;
    }
    printf("change_pos = %d\n",change_pos);
    printf("您要修改的学生信息如下：\n");
    printf("学号:%d\t姓名：%s\t成绩：%.2f\n",
            s[change_pos].id,
            s[change_pos].name,
            s[change_pos].score);
    printf("是否要修改该生信息y/n\n");
    //scanf("%c",&ch);
    ch = getchar();//读取我们需要的字符  Y/N
    getchar();//读取回车
    if(ch == 'n' || ch == 'N')
        return 0;
    
    printf("请输入修改之后的学号\n");
    scanf("%d",&id);
    getchar();
    if(Check_stu_id(id,s) != -1)
    {
        printf("学号为%d的学生存在\n",id);
        return 0;
    }
    s[change_pos].id = id;

    printf("请输入修改之后学生的姓名\n");
    scanf("%s",s[change_pos].name);
    getchar();
    printf("请输入修改之后学生的成绩\n");
    scanf("%f",&s[change_pos].score);
    getchar();
    return 1;
}
//插入信息
int insert_info(struct stu s[])
{
    int id;
    int insert_pos;
    int i;
    //判断空间是否满了
    if(count >= MAX_SIZE)
    {
        printf("系统空间不足，请联系管理员扩容\n");
        return 0;
    }

    printf("请输入要插入的位置(以学号标记位置)\n");
    scanf("%d",&id);
    getchar();
    //找位置
    insert_pos = Check_stu_id(id,s);
    if(insert_pos == -1)
    {
        printf("您要插入的位置不存在\n");
        return 0;
    }
    printf("insert_pos = %d\n",insert_pos);

    printf("请输入要插入的学号\n");
    scanf("%d",&id);
    getchar();
    if(Check_stu_id(id,s) != -1)
    {
        printf("学号为%d的学生存在\n",id);
        return 0;
    }

    //要插入的学生学号不存在，移动数据，腾位置
    for(i=count-1;i>=insert_pos;i--)
    {
        s[i+1] = s[i];
    }
    //插入数据
    s[insert_pos].id = id;
    printf("请输入要插入学生的姓名\n");
    scanf("%s",s[insert_pos].name);
    getchar();
    printf("请输入要插入学生的成绩\n");
    scanf("%f",&s[insert_pos].score);
    getchar();
    count++;
    return 1;
}



