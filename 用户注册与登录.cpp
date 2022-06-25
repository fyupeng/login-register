#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct USER_node
{
	char name[20];
	char password[20]; 
	struct USER_node *next;
} USER_USER_Node,*USER_Link;
USER_Link head;
int user_number();
int user_limit();
int create_user();
int identify_user();
USER_Link ReadFromFile_user();
void clearUSER_Link(USER_Link head);
int remove_user_password(); 
int clear_user(char user_name[],char user_password[]);
int delete_user(char user_name[],char user_password[]);
int unique_user(char user_name[]);
int delete_user_prime();
int main()
{
	char ch;  	
	create_user();
	printf("欢迎使用！");
	ch=getchar();
	return 0;
}
int user_number()
{
	USER_Link p,q;
	int number=0;
	q=ReadFromFile_user();//申请了堆内存，必须人工清理内存   1 
	p=q->next;
	while(p!=NULL)
	{
		number++;
		p=p->next;
	}
	clearUSER_Link(q);                                           //1
	return number; 
}
int user_limit()
{
	int number=0;
	number=user_number();
	printf("目前有%d位用户，允许新创建%d位用户\n",number,3-number);
	return number;
} 
int create_user()
{
	char ch;
	char user_name[20];
	char user_password[20];
	char user_password_[20];
	int flag=0,sign=0,number=0,i,select=2;
	USER_Link p;
	FILE *fp=NULL;
	fp=fopen("student.txt","r"); //打开失败表明文本未创建,用"r"只是用来判断是否有文本创建
	if(fp==NULL)
	{
		printf("当前无用户，为您创建新用户\n");
	}
	fp=fopen("student.txt","a"); //追加方式使用"a" 
	number=user_limit();		
		do{
			    printf("1.创建新用户\n2.登录账户\n3.修改密码\n4.注销账户\n0,退出！\n请选择：");
			    scanf("%d",&select);
		    	switch(select)
				{
					case 1:				if(number==3)
					                    {
											printf("用户名已达到3位，无法创建,请登录\n");
											flag=2; 
										}
					            while(flag==0)
								{
									flag=1;
									do
									{										 
										printf("请输入用户名："); //将用户名和密码写入字符数组中 
										scanf("%s",user_name);
										fflush(stdin);
										printf("请输入密码：");
										scanf("%s",user_password);
										fflush(stdin);
										printf("请再次输入密码：");
										scanf("%s",user_password_);
										fflush(stdin);
										flag=unique_user(user_name);	
									}while(flag==0);			
									if(strcmp(user_password,user_password_)!=0)
									{
										printf("密码不一致！\n");
										flag=0; 
									}			
									for(i=0;user_name[i]!='\0';i++)
									{
										if((user_name[i]<'a'||user_name[i]>'z')&&(user_name[i]<'A'||user_name[i]>'Z')&&(user_name[i]<'0'||user_name[i]>'9'))
										{
											printf("不能含有'_',汉字等特殊符号，允许数字、字母混合。\n\n");
											printf("请重新输入！\n"); 
											flag=0;
											break;				 
										}
									}
									if(flag==1)
									{
								        fprintf(fp,"%s\t",user_name);  //将字符数组中的用户名和密码写入文本中 
    									fprintf(fp,"%s",user_password);
										fputc('\n',fp);
										fflush(stdin);
										fclose(fp);
										printf("创建成功！");
										printf("你的账户已生效，请妥善保管\n");
										printf("用户名：%s\n",user_name);
										printf("密码：%s\n",user_password);				
									} 
								 
								}
					case 2:	identify_user();break;
					case 3: remove_user_password();flag=0;break;
					case 4:     do
							    {
							    	printf("请输入账户用户名：");
									scanf("%s",&user_name);
									fflush(stdin); 
									printf("请输入密码:");
									scanf("%s",&user_password);
									fflush(stdin);
								    delete_user_prime(); //必须在申请之前，否则在注销失败时就会遗留内存没有清理 
									head=ReadFromFile_user();  //申请了堆内存，必须人工清理内存   1
									p=head->next;
									while(p!=NULL)
									{
										if(strcmp(p->name,user_name)==0&&strcmp(p->password,user_password)==0)
										{
											printf("验证成功！\n");
											flag=1;
											sign=1;
											break; 
										}
										p=p->next;
									}
									
									clearUSER_Link(head); //这一步非常重要，没有这一步，将会浪费很多内存 
									
									if(flag==0)
								    {
										printf("验证失败,请重新验证\n"); 
									}
								
								}while(sign!=1);
					            delete_user(user_name,user_password);
								flag=0;break;
		    		case 0:	printf("已退出！\n");ch=getchar();exit(0);
				    default : printf("输入错误！请重新输入！\n");break;
				}
		  }while(select!=1&&select!=2&&select!=0);


		 
	return 0;
}
int identify_user() //中括号内为要输入的用户名和密码，用于验证用户 
{
	char a;
	char user_name[20];
	char user_password[20];
	USER_Link p;
	int sign=0;
	FILE *fp=NULL;
	fp=fopen("student.txt","r");
	if(fp==NULL)
	{
		printf("读取失败！"); 
	}
	printf("登录界面----------\n"); 
	printf("请输入用户名：");
	scanf("%s",user_name);
	printf("请输入密码：");
	scanf("%s",user_password); 
	head=ReadFromFile_user();//申请了堆内存，必须人工清理内存   1 
	p=head->next;
	while(p!=NULL)
	{
		if(strcmp(user_name,p->name)==0&&strcmp(user_password,p->password)==0)
		{
			printf("验证成功！\n");
			sign=1;
			break; 
		}
		p=p->next;
	}
	clearUSER_Link(head);                                          //1 
	if(fscanf(fp,"%c",&a)==EOF)
	{
		printf("目前无账户！\n");
		fclose(fp);
		exit(1); 
	}
	if(sign==0&&fscanf(fp,"%c",&a)!=EOF)
	{
		printf("用户名或密码错误！");
		fclose(fp);
		exit(1);
	}
	fclose(fp);	
	return 0;
}
USER_Link ReadFromFile_user() //读取文本中的账号密码，连接账户验证的前一步 
{
	USER_Link q,p,rear;
	FILE *fp=NULL;
	char a[20];
	head=(USER_Link)malloc(sizeof(USER_USER_Node));
	head->next=NULL;

	fp=fopen("student.txt","r");
	if(fp==NULL)
	{
		printf("文件打开失败！\n");
		clearUSER_Link(head);
		exit(1);
	}
	rear=head;	
	while(fscanf(fp,"%s",a)!=EOF)
	{
		q=(USER_Link)malloc(sizeof(USER_USER_Node));
		q->next=NULL;
		strcpy(q->name,a);
		fscanf(fp,"%s",&(q->password));
		rear->next=q;
		rear=rear->next; 
	}
	fclose(fp);
	//printf("读取成功！\n");  //表明链表意境存储了文本中的数据 
	p=head->next;
    return head;
}
void clearUSER_Link(USER_Link head)
{
	USER_Link p;
	while(head!=NULL)
	{
		p=head;
		head=head->next;
		free(p);
	}
}
int remove_user_password()
{
	char user_name[20],user_password[20];
	int flag=0,sign=0;
    USER_Link head,p;
    do
    {
    	printf("请输入账户用户名：");
		scanf("%s",&user_name);
		fflush(stdin); 
		printf("请输入密码:");
		scanf("%s",&user_password);
		fflush(stdin);
		head=ReadFromFile_user();  //申请了堆内存，必须人工清理内存   1
		p=head->next;
		while(p!=NULL)
		{
			if(strcmp(p->name,user_name)==0&&strcmp(p->password,user_password)==0)
			{
				printf("验证成功！\n");
				flag=1;
				sign=1;
				clearUSER_Link(head); //到这里只是清理了一遍               1
				break; 
			}
			p=p->next;
		}
		
		clearUSER_Link(head); //这一步非常重要，没有这一步，将会浪费很多内存 
		
		if(flag==0)
	    {
			printf("验证失败,请重新验证\n"); 
		}
	
	}while(sign!=1);
	//只有flag=1和sign=1,结束内外循环，即验证成功 
	clear_user(user_name,user_password);
	printf("请输入新密码：");
	scanf("%s",&user_password);
	fflush(stdin);
	FILE *fp=NULL;
	fp=fopen("student.txt","r");
	if(fp==NULL)
	{
		printf("文件打开失败！");
		exit(1); 
	}
	fclose(fp);
	fp=fopen("student.txt","a");
	fprintf(fp,"%s\t",user_name);
	fprintf(fp,"%s",user_password);
	fputc('\n',fp);
	fclose(fp);
    printf("密码修改成功！\n");
	return 0; 
}
int clear_user(char user_name[],char user_password[])
{
	FILE *fp=NULL;
	USER_Link head,p;
	head=ReadFromFile_user();//申请了堆内存，必须人工清理内存   1 
	p=head->next;
	fp=fopen("student.txt","r");
	if(fp==NULL)
	{
		printf("文件打开失败！");
		clearUSER_Link(head);                                        //1
		exit(1); 
	}
	fclose(fp);
	fp=fopen("student.txt","w");
	while(p!=NULL)
	{
		if(strcmp(p->name,user_name)!=0)
		{			
	    	fprintf(fp,"%s\t",p->name);
			fprintf(fp,"%s",p->password);
			fputc('\n',fp);
			fflush(stdin);		
		}
		p=p->next;
	}
	fclose(fp);	
	clearUSER_Link(head);                                            //1
}
int delete_user(char user_name[],char user_password[])  //与函数clear_user(char user_name,char user_password) 中的两个字符串是同一个 
{
	char a[20];
	FILE *fp=NULL;	
	fp=fopen("student.txt","r");
	if(fscanf(fp,"%s",a)==EOF)
	{
	printf("不存在该用户，注销失败！\n");
	fclose(fp);
	return 0; 
	}
	clear_user(user_name,user_password);
	printf("账户注销成功！\n");
	fclose(fp);
	return 0;
}
int unique_user(char user_name[])
{
	USER_Link head,p;
	char a[20];
	int flag=1;
	head=ReadFromFile_user();//申请了堆内存，必须人工清理内存    1
	p=head->next;
	FILE *fp=NULL;
	fp=fopen("student.txt","r");
	if(fscanf(fp,"%s",a)!=EOF);
	{
		while(p!=NULL)
		{
			if(strcmp(p->name,user_name)==0)      //输入的用户名与读取链表中的用户名逐一对比 
			{
				printf("该账户已注册\n");
				flag=0; 
			}
			p=p->next;
		} 
	}
	fclose(fp);
	clearUSER_Link(head);                                      //1
	return flag; 
}
int delete_user_prime()
{
	char a[20];
	FILE *fp=NULL;	
	fp=fopen("student.txt","r");
	if(fscanf(fp,"%s",a)==EOF)
	{
	printf("不存在该用户，注销失败！\n");
	fclose(fp);
	exit(1); 
	}
	fclose(fp);
    return 0;
}
