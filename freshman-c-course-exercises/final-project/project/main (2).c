#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#define STRING_LEN 80//��������ַ�������
#define STU_NUM 30//�������ѧ����
#define SCORE_NUM 6//������࿼�Կ�Ŀ
#define TYPE_NUM 5//����ɼ��ȼ���
typedef struct student
{
    long num;//һ��ѧ����ѧ��
    char name[STRING_LEN];//һ��ѧ��������
    float score[SCORE_NUM];//һ��ѧ����SCORE_NUM��ѧ�Ƶĳɼ�
    float sum;//һ��ѧ�����ܳɼ�
    float aver;//һ��ѧ���ĸ���ƽ���ɼ�
    char record_type[10];//�ж��Ƿ�Ϊ��Ӽ�¼��ɾ����¼
} STU;
typedef struct node
{
    int ival;
} NodeType;
typedef struct stack
{
    NodeType data[SCORE_NUM];
    int top;//����ջ��
} STACK;

void StartAmendmentFile(void);
int Menu(void);
int Judge(void);
void ReadScore(STU stu[],int stu_num,int score_num);
void CalculateByCourse(STU stu[],int stu_num,int score_num);
void CalculateByStudent(STU stu[],int stu_num,int score_num);
int Calculate(STU stu[],int i,int score_num);
void SumAndAver(STU stu[],int stu_num,int score_num);
void Push(STACK *stack,NodeType data);
NodeType Pop(STACK *stack);
NodeType OpInt(int d1,int d2);
NodeType Opdata(NodeType *d1,NodeType *d2);
void SortByScore(STU stu[],int stu_num,int score_num,int (*compare)(float a,float b));
int Descending(float a,float b);
int Ascending(float a,float b);
void SwapFloat(float *x,float *y);
void SwapLong(long *x,long *y);
void SwapString(char x[],char y[]);
void PrintScore(STU stu[],int stu_num,int score_num);
void SortByNum(STU stu[],int stu_num,int score_num);
void SortByName(STU stu[],int stu_num,int score_num);
int SearchByNum(STU stu[],int stu_num,int score_num);
void SearchByName(STU stu[],int stu_num,int score_num);
void FuzzySearch(STU stu[],int stu_num,int score_num);
void StatisticAnalysis(STU stu[],int stu_num,int score_num);
void WriteToFile(STU stu[],int stu_num,int score_num);
void ReadFromFile(STU stu[],int *stu_num,int *score_num);
int AddStudent(STU stu[],int stu_num,int score_num,STU note[],int record);
int DeleteStudent(STU stu[],int stu_num,int score_num,STU note[],int record);
void ViewRecords(STU note[],int *record,int *score_num,int record_copy,int score_num_copy);
void PrintAmendment(STU note[],int record_copy,int score_num_copy);

int main(int argc,char *argv[])
{
    int stu_num;//ѧ����
    int score_num;//ѧ����
    int order=17;//�������ָ��
    int judge,find=0,find_file=0,find_input=0,record=0,record_copy,score_num_copy,add=0,del=0;
    STU stu[STU_NUM],note[STU_NUM];
    PlaySound(TEXT("2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);//��������
    system("pause");
    printf("\n\t\t\tWelcome to the Student Achievement Management System!\n");
    printf("\n\t\t\tTip: Please enter numbers or letters.\n");
    printf("\nPlease input student number(stu_num<=%d):",STU_NUM);
    stu_num=Judge();
    StartAmendmentFile();
    while(stu_num>STU_NUM)
    {
        printf("Please enter a valid command:");
        stu_num=Judge();
    }
    printf("Please input course number(score_num<=%d):",SCORE_NUM);
    score_num=Judge();
    while(score_num>SCORE_NUM)
    {
        printf("Please enter a valid command:");
        score_num=Judge();
    }
    while(order!=0)
    {
        order=Menu();
        while(order>16)
        {
            printf("Please enter a valid command:");
            order=Judge();
        }
        switch(order)
        {
        case 1:
            if(find_input==1)
            {
                printf("You can only use the first function once!\n");
                break;
            }
            ReadScore(stu,stu_num,score_num);
            find_input=1;
            break;
        case 2:
            if(find_input==1)
                CalculateByCourse(stu,stu_num,score_num);
            else
                printf("Please input record first");
            break;
        case 3:
            if(find_input==1)
            {
                CalculateByStudent(stu,stu_num,score_num);
                find=1;
            }
            else
                printf("Please input record first");
            break;
        case 4:
            if(find_input==1)
            {
                if(find==0)
                {
                    SumAndAver(stu,stu_num,score_num);
                }
                SortByScore(stu,stu_num,score_num,Descending);
                printf("\nSort in descending order by score:\n");
                PrintScore(stu,stu_num,score_num);
            }
            else
                printf("Please input record first");
            break;
        case 5:
            if(find_input==1)
            {
                if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            SortByScore(stu,stu_num,score_num,Ascending);
            printf("\nSort in ascending order by score:\n");
            PrintScore(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 6:
            if(find_input==1)
            {
                 if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            SortByNum(stu,stu_num,score_num);
            printf("\nSort in ascending order by number:\n");
            PrintScore(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 7:
            if(find_input==1)
            {
                  if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            SortByName(stu,stu_num,score_num);
            printf("\nSort in dictionary order by name:\n");
            PrintScore(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 8:
            if(find_input==1)
            {
                if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            SearchByNum(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 9:
            if(find_input==1)
            {
                 if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            printf("Do you want to use fuzzy query?\n");
            printf("Please input 1(Yes) or any other digit(No).\n");
            judge=Judge();
            if(judge==1)
            {
                FuzzySearch(stu,stu_num,score_num);
            }
            else
            {
                SearchByName(stu,stu_num,score_num);
            }
            }
             else
                printf("Please input record first");

            break;
        case 10:
            if(find_input==1)
            {
                 StatisticAnalysis(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 11:
            if(find_input==1)
            {
                   if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            PrintScore(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 12:
            if(find_input==1)
            {
                if(find==0)
            {
                SumAndAver(stu,stu_num,score_num);
            }
            find_file=1;
            WriteToFile(stu,stu_num,score_num);
            }
             else
                printf("Please input record first");

            break;
        case 13:
            if(find_input==1)
            {
                 if(find_file==0)
            {
                printf("Please use the twelfth function first!\n");
            }
            else
            {
                ReadFromFile(stu,&stu_num,&score_num);
                PrintScore(stu,stu_num,score_num);
            }
            }
             else
                printf("Please input record first");

            break;
        case 14:
            if(find_input==1)
            {
                  if(stu_num<STU_NUM)
            {
                add=stu_num;
                stu_num=AddStudent(stu,stu_num,score_num,note,record);
                add=stu_num-add;
                record=record+add;
            }
            else
            {
                printf("The number of student cannot be greater than %d !\n",stu_num);
            }
            }
             else
                printf("Please input record first");

            break;
        case 15:
            if(find_input==1)
            {
                 del=stu_num;
            stu_num=DeleteStudent(stu,stu_num,score_num,note,record);
            del=del-stu_num;
            record=record+del;
            }
             else
                printf("Please input record first");
            break;
        case 16:
            if(find_input==1)
            {
                if(record==0)
            {
                printf("\nThere is no amendment record yet.\n");
            }
            else
            {
                record_copy=record;
                score_num_copy=score_num;
                ViewRecords(note,&record,&score_num,record_copy,score_num_copy);
            }
            }
             else
                printf("Please input record first");

            break;
        case 0:
            printf("Thank you for your use!\n");
            exit(0);
        }
        printf("\nDo you want to use other functions?\n");
        printf("Please input 1(Yes) or any other digit(No).\n");
        judge=Judge();
        if(judge!=1)
        {
            order=0;
        }
    }
    printf("Thank you for your use!\n");
    return 0;
}
void StartAmendmentFile(void)
{
    FILE *fp;
    if((fp=fopen("amendment_record.txt","w"))==NULL)
    {
        printf("Failure to open amendment_record.txt!\n");
        exit(0);
    }
    fclose(fp);
}
int Menu(void)//��ӡ���˵�������ָ��
{
    int order;//orderΪ�û�����ĺϷ�ָ��
    printf("\t\t\t----------------------------------------------------------\n");
    printf("\t\t\t   Welcome to the Student Achievement Management System\n");
    printf("\t\t\t-----------------------------------------------------------\n");
    printf("\t\t\t1.Input record\n");
    printf("\t\t\t2.Calculate total and average score of every course\n");
    printf("\t\t\t3.Calculate total and average score of every student\n");
    printf("\t\t\t4.Sort in descending order by total score of every student\n");
    printf("\t\t\t5.Sort in ascending order by total score of every student\n");
    printf("\t\t\t6.Sort in ascending order by number\n");
    printf("\t\t\t7.Sort in dictionary order by name\n");
    printf("\t\t\t8.Search by number\n");
    printf("\t\t\t9.Search by name\n");
    printf("\t\t\t10.Statistic analysis for every course\n");
    printf("\t\t\t11.List record\n");
    printf("\t\t\t12.Write to a file\n");
    printf("\t\t\t13.Read from a file\n");
    printf("\t\t\t14.Add student information\n");
    printf("\t\t\t15.Delete student information\n");
    printf("\t\t\t16.View the modification records\n");
    printf("\t\t\t0.Exit\n");
    printf("\t\t\t----------------------------------------------------------\n");
    printf("\n");
    printf("Please enter your choice:\n");
    order=Judge();
    return order;
}
//����û��������ݵ���Ч��
int Judge(void)
{
    char input[STRING_LEN];//inputΪ���ַ��Ͷ����ָ��
    int order=0;//�Ϸ�ָ��//���Ϸ���ָ��ת��Ϊorder
    int i;
    scanf("%s",input);
    //����û��������ݵ���Ч��
    for(i=0; i<strlen(input); i++)
    {
        if(!isdigit(input[i]))
        {
            i=-1;
            printf("Please enter a valid command:\n");
            scanf("%s",input);
        }
    }
    //���Ϸ���ָ��ת��Ϊorder
    for(i=0; i<strlen(input); i++)
    {
        order=order*10+(input[i]-'0');
    }
    return order;
}
//¼��ÿ��ѧ����ѧ�š������͸��ƿ��Գɼ�
void ReadScore(STU stu[],int stu_num,int score_num)
{
    int i,j;
    for(i=0; i<stu_num; i++)
    {
        printf("Please input student%d's ID, name and score(integer):\n",i+1);
        scanf("%ld %s",&stu[i].num,stu[i].name);
        for(j=0; j<score_num; j++)
        {
            scanf("%f",&stu[i].score[j]);
            while(stu[i].score[j]>100||stu[i].score[j]<0)
            {
                printf("Please enter a valid digit:");
                scanf("%f",&stu[i].score[j]);
            }
        }
    }
}
//����ÿ�ſγ̵��ֺܷ�ƽ����
void CalculateByCourse(STU stu[],int stu_num,int score_num)
{
    int i,j;
    float score_sum[SCORE_NUM],score_aver[SCORE_NUM];
    for(j=0; j<score_num; j++)
    {
        score_sum[j]=0;
        for(i=0; i<stu_num; i++)
        {
            score_sum[j]=score_sum[j]+stu[i].score[j];
        }
        score_aver[j]=(float)score_sum[j]/stu_num;
        printf("course%d: summation=%.1f, average=%.1f\n",j+1,(float)score_sum[j],score_aver[j]);
    }
}
//����ÿ��ѧ�����ֺܷ�ƽ����
void CalculateByStudent(STU stu[],int stu_num,int score_num)
{
    int i;
    for(i=0; i<stu_num; i++)
    {
        stu[i].sum=Calculate(stu,i,score_num);
        stu[i].aver=(float)stu[i].sum/score_num;
        printf("student%d: summation=%.1f, average=%.1f\n",i+1,(float)stu[i].sum,stu[i].aver);
    }
}
//��ջ���
int Calculate(STU stu[],int i,int score_num)
{
    NodeType d1,d2,d3;
    STACK stack;
    int t;
    stack.top=0;//��ʼ��ջ��
    for(t=0; t<score_num; t++)
    {
        d1.ival=stu[i].score[t];
        Push(&stack,d1);
    }
    for(t=0; t<score_num-1; t++)
    {
        d1=Pop(&stack);
        d2=Pop(&stack);
        d3=Opdata(&d1,&d2);
        Push(&stack,d3);
    }
    d3=Pop(&stack);
    return d3.ival;
}
void SumAndAver(STU stu[],int stu_num,int score_num)
{
    int i,j;
    for(i=0; i<stu_num; i++)
    {
        stu[i].sum=0;
        for(j=0; j<score_num; j++)
        {
            stu[i].sum=stu[i].sum+stu[i].score[j];
        }
        stu[i].aver=(float)stu[i].sum/score_num;
    }
}
//������dataѹ��ջ��
void Push(STACK *stack,NodeType data)
{
    memcpy(&stack->data[stack->top],&data,sizeof(NodeType));
    stack->top=stack->top+1;
}
//����ջ�����ݲ�����
NodeType Pop(STACK *stack)
{
    stack->top=stack->top-1;
    return stack->data[stack->top];
}
//��ֵ���
NodeType OpInt(int d1,int d2)
{
    NodeType d3;
    d3.ival=d1+d2;
    return d3;
}
//��d1,d2ִ�мӷ����㣬�����ؼ�����
NodeType Opdata(NodeType *d1,NodeType *d2)
{
    NodeType d3;
    d3=OpInt(d1->ival,d2->ival);
    return d3;
}
//��ѡ�񷨽�����sum��Ԫ��ֵ���Ӹߵ��ͻ�ӵ͵�������(��������
void SortByScore(STU stu[],int stu_num,int score_num,int (*compare)(float a,float b))
{
    int i,j,k,t;
    for(i=0; i<stu_num-1; i++)
    {
        k=i;
        for(j=i+1; j<stu_num; j++)
        {
            if((*compare)(stu[j].sum,stu[k].sum))
            {
                k=j;
            }
        }
        if(k!=i)
        {
            //�������пγ̵ĳɼ�
            for(t=0; t<score_num; t++)
            {
                SwapFloat(&stu[k].score[t],&stu[i].score[t]);
            }
            SwapFloat(&stu[k].sum,&stu[i].sum);//�����ܷ�
            SwapFloat(&stu[k].aver,&stu[i].aver);//����ƽ����
            SwapLong(&stu[k].num,&stu[i].num);//����ѧ��
            SwapString(stu[k].name,stu[i].name);//��������
        }
    }
}
//��������
int Descending(float a,float b)
{
    return a>b;//��a>b�򽻻�
}
//��������
int Ascending(float a,float b)
{
    return a<b;//��a<b�򽻻�
}
//���������ȸ���������
void SwapFloat(float *x,float *y)
{
    float temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
//��������������
void SwapLong(long *x,long *y)
{
    long temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
//�����ַ���
void SwapString(char x[],char y[])
{
    char temp[STRING_LEN];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}
//��ӡѧ����Ϣ
void PrintScore(STU stu[],int stu_num,int score_num)
{
    int i,j;
    for(i=0; i<stu_num; i++)
    {
        stu[i].sum=0;
        printf("number: %ld\n",stu[i].num);
        printf("name:%s\n",stu[i].name);
        for(j=0; j<score_num; j++)
        {
            stu[i].sum=stu[i].sum+stu[i].score[j];
            printf("score%d:%.0f\n",j+1,stu[i].score[j]);
        }
        stu[i].aver=(float)stu[i].sum/score_num;
        printf("summation:%.1f\n",(float)stu[i].sum);
        printf("average:%.1f\n",stu[i].aver);
    }
}
//��ѡ�񷨰�ѧ����С�����ų��ɼ�
void SortByNum(STU stu[],int stu_num,int score_num)
{
    int i,j,k,t;
    for(i=0; i<stu_num-1; i++)
    {
        k=i;
        for(j=i+1; j<stu_num; j++)
        {
            if(stu[j].num<stu[k].num)
            {
                k=j;
            }
        }
        if(k!=i)
        {
            //�������пγ̵ĳɼ�
            for(t=0; t<score_num; t++)
            {
                SwapFloat(&stu[k].score[t],&stu[i].score[t]);
            }
            SwapFloat(&stu[k].sum,&stu[i].sum);//�����ܷ�
            SwapFloat(&stu[k].aver,&stu[i].aver);//����ƽ����
            SwapLong(&stu[k].num,&stu[i].num);//����ѧ��
            SwapString(stu[k].name,stu[i].name);//��������
        }
    }
}
//���������ֵ�˳���ų��ɼ���
void SortByName(STU stu[],int stu_num,int score_num)
{
    int i,j,t;
    for(i=0; i<stu_num-1; i++)
    {
        for(j=i+1; j<stu_num; j++)
        {
            if(strcmp(stu[j].name,stu[i].name)<0)
            {
                //�������пγ̳ɼ�
                for(t=0; t<score_num; t++)
                {
                    SwapFloat(&stu[i].score[t],&stu[i].score[t]);
                }
                SwapFloat(&stu[i].sum,&stu[i].sum);//�����ܷ�
                SwapFloat(&stu[i].aver,&stu[i].aver);//����ƽ����
                SwapLong(&stu[i].num,&stu[i].num);//����ѧ��
                SwapString(stu[i].name,stu[i].name);//��������
            }
        }
    }
}
//��ѧ�Ų�ѯѧ���������俼�Գɼ�
int SearchByNum(STU stu[],int stu_num,int score_num)
{
    long number;
    int i,j,find=0;
    printf("\nPlease input the number you want to search:");
    number=Judge();
    for(i=0; i<stu_num; i++)
    {
        if(stu[i].num==number)
        {
            find=1;
            printf("number: %ld\n",stu[i].num);
            printf("name:%s\n",stu[i].name);
            for(j=0; j<score_num; j++)
            {
                printf("score%d:%.0f\n",j+1,stu[i].score[j]);
            }
            printf("summation:%.0f\n",stu[i].sum);
            printf("average:%.0f\n",stu[i].aver);
            return i;
        }
    }
    if(find==0)
    {
        printf("\nNot found!\n");
        return -1;
    }
    else
        return 0;//�˴������Ч����Ҫ��Ϊ��ʹ������������з���ֵ����ֹ����
}
//��������ѯѧ���������俼�Գɼ�
void SearchByName(STU stu[],int stu_num,int score_num)
{
    char input[STRING_LEN];
    int i,j;
    int find=0;
    printf("\nPlease input the name you want to search:\n");
    scanf("%s",input);
    for(i=0; i<stu_num; i++)
    {
        if(strcmp(stu[i].name,input)==0)
        {
            find=1;
            printf("number: %ld\n",stu[i].num);
            printf("name:%s\n",stu[i].name);
            for(j=0; j<score_num; j++)
            {
                printf("score%d:%.0f\n",j+1,stu[i].score[j]);
            }
            printf("summation:%.0f\n",stu[i].sum);
            printf("average:%.0f\n",stu[i].aver);
        }
    }
    if(find==0)
    {
        printf("\nNot found!\n");
    }
}
//ģ����ѯ
void FuzzySearch(STU stu[],int stu_num,int score_num)
{
    char input[STRING_LEN];
    char *res;
    int i,j,n;
    int find=0;
    printf("\nPlease input the key word you want to search:\n");
    scanf("%s",input);
    for(i=0; i<stu_num; i++)
    {
        res=memchr(stu[i].name,input[0],strlen(stu[i].name));
        if(res==NULL)
        {
            continue;
        }
        while(1)
        {
            n=memcmp(res,input,strlen(input)-1);
            if(n!=0)
            {
                if(strlen(res)<=strlen(input))
                {
                    break;
                }
                else
                {
                    //����Ҫ���ҵĵ�һ���ַ������и�
                    res=memchr(res+1,input[0],strlen(res));
                    if(res==NULL)
                    {
                        break;
                    }
                }
            }
            else
            {
                find=1;
                printf("number: %ld\n",stu[i].num);
                printf("name:%s\n",stu[i].name);
                for(j=0; j<score_num; j++)
                {
                    printf("score%d:%.0f\n",j+1,stu[i].score[j]);
                }
                printf("summation:%.0f\n",stu[i].sum);
                printf("average:%.0f\n",stu[i].aver);
                break;
            }
        }
    }
    if(find==0)
    {
        printf("\nNot found!\n");
    }
}
//��ÿ�ſγ̷���ͳ����������ռ�ٷֱ�
void StatisticAnalysis(STU stu[],int stu_num,int score_num)
{
    int i,j,type[TYPE_NUM];
    float persentage[TYPE_NUM];
    for(j=0; j<score_num; j++)
    {
        memset(type,0,sizeof(type));
        memset(persentage,0,sizeof(persentage));
        printf("\nFor course %d:\n",j+1);
        for(i=0; i<stu_num; i++)
        {
            if(stu[i].score[j]>=0&&stu[i].score[j]<60)
            {
                type[0]++;
            }
            else if(stu[i].score[j]>=60&&stu[i].score[j]<70)
            {
                type[1]++;
            }
            else if(stu[i].score[j]>=70&&stu[i].score[j]<80)
            {
                type[2]++;
            }
            else if(stu[i].score[j]>=80&&stu[i].score[j]<90)
            {
                type[3]++;
            }
            else if(stu[i].score[j]>=90&&stu[i].score[j]<=100)
            {
                type[4]++;
            }
        }
        for(i=0; i<TYPE_NUM; i++)
        {
            persentage[i]=((float)type[i]/stu_num)*100;
        }
        printf("Failed:    %d\t%.2f%%\n",type[0],persentage[0]);
        printf("Passing:   %d\t%.2f%%\n",type[1],persentage[1]);
        printf("Moderate:  %d\t%.2f%%\n",type[2],persentage[2]);
        printf("Good:      %d\t%.2f%%\n",type[3],persentage[3]);
        printf("Excellent: %d\t%.2f%%\n",type[4],persentage[4]);
    }
}
//��ѧ����Ϣд���ļ�
void WriteToFile(STU stu[],int stu_num,int score_num)
{
    FILE *fp;
    int i,j;

    fprintf(fp,"%10d%10d",stu_num,score_num);//д��ѧ��������γ�����
    for(i=0; i<stu_num; i++)
    {
        fprintf(fp,"%10ld",stu[i].num);//д��ѧ��
        fprintf(fp,"%10s",stu[i].name);//д������
        //д����Ƴɼ�
        for(j=0; j<score_num; j++)
        {
            fprintf(fp,"%10.0f",stu[i].score[j]);
        }
        fprintf(fp,"%10.0f",stu[i].sum);//д���ܳɼ�
        fprintf(fp,"%10.1f",stu[i].aver);//д��ƽ���ɼ�
    }
    fclose(fp);
}
//���ļ��ж���ÿ��ѧ������Ϣ����ʾ
void ReadFromFile(STU stu[],int *stu_num,int *score_num)
{
    FILE *fp;
    int i,j;
    if((fp=fopen("student.txt","r"))==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp,"%10d%10d",stu_num,score_num);
    for(i=0; i<*stu_num; i++)
    {
        fscanf(fp,"%10ld",&stu[i].num);
        fscanf(fp,"%s",stu[i].name);
        for(j=0; j<*score_num; j++)
        {
            fscanf(fp,"%f",&stu[i].score[j]);
        }
        fscanf(fp,"%f%f",&stu[i].sum,&stu[i].aver);
    }
    fclose(fp);
}
//���ѧ����Ϣ��д���ļ�
int AddStudent(STU stu[],int stu_num,int score_num,STU note[],int record)
{
    FILE *fp;
    int find=1,j,judge;
    char str[10]= {"Addition"};
    while(find)
    {
        strcpy(note[record].record_type,str);
        printf("Please input the stuent's ID, name and score(integer):\n");
        scanf("%ld %s",&stu[stu_num].num,stu[stu_num].name);
        note[record].num=stu[stu_num].num;
        strcpy(note[record].name,stu[stu_num].name);
        for(j=0; j<score_num; j++)
        {
            scanf("%f",&stu[stu_num].score[j]);
            while(stu[stu_num].score[j]>100||stu[stu_num].score[j]<0)
            {
                printf("Please enter a valid digit:");
                scanf("%f",&stu[stu_num].score[j]);
            }
            note[record].score[j]=stu[stu_num].score[j];
        }
        SumAndAver(note,record,score_num);
        if((fp=fopen("amendment_record.txt","a"))==NULL)
        {
            printf("Failure to open amendment_record.txt!\n");
            exit(0);
        }
        fprintf(fp,"%10s",note[record].record_type);
        fprintf(fp,"%10ld",note[record].num);//д��ѧ��
        fprintf(fp,"%10s",note[record].name);//д������
        //д����Ƴɼ�
        for(j=0; j<score_num; j++)
        {
            fprintf(fp,"%10.0f",note[record].score[j]);
        }
        fprintf(fp,"%10.0f",note[record].sum);//д���ܳɼ�
        fprintf(fp,"%10.1f",note[record].aver);//д��ƽ���ɼ�
        fclose(fp);
        stu_num++;
        record++;
        printf("Do you want to add another student?\n");
        printf("Please input 1(Yes) or any other digit(No).\n");
        judge=Judge();
        if(judge!=1)
        {
            find=0;
        }
    }
    return stu_num;
}
//ɾ��ѧ����Ϣ��д���ļ�
int DeleteStudent(STU stu[],int stu_num,int score_num,STU note[],int record)
{
    FILE *fp;
    int i,j,judge,number=-1;
    char str[10]= {"Deletion"};
    SumAndAver(stu,stu_num,score_num);
    while(1)
    {
        if(stu_num==0)
        {
            printf("The number of students cannot be less than zero.\n");
            return stu_num;
        }
        number=SearchByNum(stu,stu_num,score_num);
        if(number==-1)
        {
            printf("Do you want to input another ID?\n");
            printf("Please input 1(Yes) or any other digit(No).\n");
            judge=Judge();
            if(judge!=1)
            {
                return stu_num;
            }
        }
        stu_num--;
        record++;
        strcpy(note[record].record_type,str);
        note[record].num=stu[number].num;
        strcpy(note[record].name,stu[number].name);
        for(j=0; j<score_num; j++)
        {
            note[record].score[j]=stu[number].score[j];
        }
        for(i=number; i<stu_num; i++)
        {
            stu[i]=stu[i+1];
        }
        if((fp=fopen("amendment_record.txt","a"))==NULL)
        {
            printf("Failure to open amendment_record.txt!\n");
            exit(0);
        }
        fprintf(fp,"%10s",note[record].record_type);
        fprintf(fp,"%10ld",note[record].num);//д��ѧ��
        fprintf(fp,"%10s",note[record].name);//д������
        //д����Ƴɼ�
        for(j=0; j<score_num; j++)
        {
            fprintf(fp,"%10.0f",note[record].score[j]);
        }
        fprintf(fp,"%10.0f",note[record].sum);//д���ܳɼ�
        fprintf(fp,"%10.1f",note[record].aver);//д��ƽ���ɼ�
        fclose(fp);
        printf("Do you want to delete another student?\n");
        printf("Please input 1(Yes) or any other digit(No).\n");
        judge=Judge();
        if(judge!=1)
        {
            return stu_num;
        }
    }
    return stu_num;
}
//�鿴�޸ļ�¼
void ViewRecords(STU note[],int *record,int *score_num,int record_copy,int score_num_copy)
{
    FILE *fp;
    int i,j;
    if((fp=fopen("amendment_record.txt","r"))==NULL)
    {
        printf("Failure to open amendment_record.txt!\n");
        exit(0);
    }
    for(i=0; i<record_copy; i++)
    {
        fscanf(fp,"%s",note[i].record_type);
        fscanf(fp,"%10ld",&note[i].num);
        fscanf(fp,"%s",note[i].name);
        for(j=0; j<*score_num; j++)
        {
            fscanf(fp,"%f",&note[i].score[j]);
        }
        fscanf(fp,"%f%f",&note[i].sum,&note[i].aver);
    }
    fclose(fp);
    PrintAmendment(note,record_copy,score_num_copy);
}
//��ӡ�޸���Ϣ
void PrintAmendment(STU note[],int record_copy,int score_num_copy)
{
    int i,j;
    for(i=0; i<record_copy; i++)
    {
        note[i].sum=0;
        printf("\n%s Record:\n",note[i].record_type);
        printf("number: %ld\n",note[i].num);
        printf("name:%s\n",note[i].name);
        for(j=0; j<score_num_copy; j++)
        {
            note[i].sum=note[i].sum+note[i].score[j];
            printf("score%d:%.0f\n",j+1,note[i].score[j]);
        }
        note[i].aver=(float)note[i].sum/score_num_copy;
        printf("summation:%.0f\n",(float)note[i].sum);
        printf("average:%.1f\n",note[i].aver);
    }
}
