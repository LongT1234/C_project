#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"control.h"
int save_info (struct link *head)
{
    struct link* ptmp = NULL;   //手动开辟链表空间
   FILE*fp= fopen("./output/save_info.txt","w");
   if(fp==NULL)
   {
    perror("fopen");
    return -1;
   }
   ptmp=head->pnext;
   while (ptmp!=NULL)
   {

    fprintf(fp,"%ld\t\t%s\t\t%s\t\t%.2f\n",
                         ptmp->s.id,
                         ptmp ->s.name,
                         ptmp->s.nex,
                         ptmp->s.score);
    ptmp=ptmp->pnext;
   }
   fclose(fp);
   return 0 ;
  

}


int read_info(struct link *head)
{  
    
   struct link*pnew = NULL;
   struct link*ptmp = NULL;
    //打开文件
    FILE *fp = fopen("./output/save_info.txt","r");
    if(fp == NULL)
    {
        perror("fopen");
        return -1;
    }
    do
    {
        //先创建链表节点
        pnew =  create_link_node();
        if(pnew == NULL)
        {
            printf("创建链表节点失败\n");
            return -1;
        }
        //读取数据
        fscanf(fp,"%ld\t\t%s\t\t%s\t\t%f\n",
                        &pnew->s.id,
                         pnew ->s.name,
                         pnew->s.nex,
                         &pnew->s.score);
        // fread(&pnew->s,sizeof(pnew->s),1,fp);
        //添加到链表里边-->尾插法
        ptmp = head;
        while(ptmp->pnext != NULL)
            ptmp = ptmp->pnext;
        ptmp->pnext = pnew;
        if(fgetc(fp) == EOF)
            break;
        else    
            fseek(fp,-1,SEEK_CUR);
    }while(!feof(fp));
    fclose(fp);
    return 0;

}


