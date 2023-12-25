#include<stdio.h>
#include<stdlib.h>
#define maxsize 16
#include<string.h>

#define MaxVertexNum 100
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

#define VertexMax 20 //最大顶点数为20
#define MaxInt 32767 //表示最大整数
#define Infinity 2000//表示无穷大 
#define MAXVEX 15 
#define key 15                 //key为顶点个数 
int shortest[15][15];         //定义全局变量存储最小路径 
int pathh[15][15];            //定义存储路径 
int d[30];
int qwe=0;
int visited[30];

void print2(int a)
{
	if(a==1)
	printf("五棵松  "); 
	if(a==2)
	printf("三山楼  "); 
	if(a==3)
	printf("图书馆  "); 
	if(a==4)
	printf("京江楼  "); 
	if(a==5)
	printf("六食堂  "); 
	if(a==6)
	printf("学生宿舍E区  ");
	if(a==7)
	printf("新一区  ");
	if(a==8)
	printf("勤人谷  ");
	if(a==9)
	printf("东山运动场  ");
	if(a==10)
	printf("体育馆  ");
	if(a==11)
	printf("梅园  "); 
	if(a==12)
	printf("学苑楼  "); 
	if(a==13)
	printf("西山操场南  "); 
	if(a==14)
	printf("礼堂  "); 
	if(a==15)
	printf("三江楼  "); 
 } 

//这是一个打印江苏大学共15个地标的子函数，该函数可以调取同文件夹的地标txt并打印。汉字以char形式打印，要读取汉字，txt必须以ANSI格式编码。 
void print()
{
	FILE *fp1;
	fp1=fopen("江苏大学地标.txt","r");
	fp1=fopen("江苏大学地标.txt","rb");
	int i;
	char nam[15][100];
	int num[15];
	for(i=0;i<15;i++)
	{
		fscanf(fp1,"%d",&num[i]);
		fscanf(fp1,"%s",&nam[i]);
	}
    
    for(i=0;i<15;i++)
    {
    	printf("                  "); 
    	printf("%d    ",num[i]);
    	printf("%s",nam[i]);    
		printf("                       \n");
	}
	fclose(fp1); 
 } 
//这是初始化子函数，读取同文件夹下的公交路线txt（该txt应以-1 开头），若文件夹为空或开头不为-1，则令文档为空并写入开头标记-1。 
void chushihua()
{
	FILE *fp;
	fp=fopen("公交路线.txt","r");
	int sch[240];
	int i;
	for(i=0;i<240;i++)
	{
		sch[i]=0;
	}

	for(i=0;i<240;i++)
	{
		fscanf(fp,"%d",&sch[i]);
	}
	if(sch[0]!=-1)
	{
     	fp=fopen("公交路线.txt","w");
    	fprintf(fp,"-1 ");
	}
	else ;

	fclose(fp);
}
//这是站点查询子函数，该子函数读取公交路线文件并将其计入数组，在数组中，函数可以统计你要查询的站点，每出现一次-1公交线路序号就加一以完成线路的统计。 
void  site()
{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	int bus[240];
	FILE *fp1;
	int i,t=0;
    fp1=fopen("公交路线.txt","r");
    for(i=0;i<240;i++)
    bus[i]=0;
    for(i=0;i<240;i++)
    fscanf(fp1,"%d",&bus[i]);
    int m=1;
    int search;
    printf("你要查询的站点是："); 
    scanf("%d",&search);system("cls");
    printf("**********************************************************\n");
    printf("为您查询到该站点通过以下线路:"); 
    for(i=0;i<240;i++)
    {
    	if(bus[i]==-1&&bus[i+1]!=0) 
		m++;
    	if(bus[i]==search)
		{
		printf(" %d号线 ",m-1);
		t++;
	    }
	}
	if(t==0) 
	printf("没有线路通过站点！");
	printf("\n");
    fclose(fp1);
}



//这是结构体的定义，我们接下来要进行最短路径的求取。 
typedef int VertexType; //每个顶点数据类型为字符型 

typedef struct
{
	VertexType Vertex[VertexMax];//存放顶点元素的一维数组 
	int AdjMatrix[VertexMax][VertexMax];//邻接矩阵二维数组 
	int vexnum,arcnum;//图的顶点数和边数  
}MGraph;
//这是查找子函数，该函数可以查找元素v在一维数组 Vertex[] 中的下标，并返回下标，返回下标我们就方便确定位置。 
int LocateVex(MGraph *G,VertexType v)
{
	int i;
	
	for(i=0;i<G->vexnum;i++)
	{
		if(v==G->Vertex[i])
		{
			return i; 
		} 
	 } 
	 
	 printf("No Such Vertex!\n");
	 return -1;
}
//这是邻接矩阵构建子函数，该函数可以构建一个邻接矩阵，打开同文件夹的地标表文件（该文件存有路径及路径长度大小），并计入邻接矩阵。 
void CreateDN(MGraph *G) 
{
	int i,j;
	//1.输入顶点数和边数 

	G->vexnum=15; 

	G->arcnum=36;

	//2.输入顶点元素 
	for(i=0;i<15;i++)
	G->Vertex[i]=i+1;

	//3.矩阵初始化
	for(i=0;i<G->vexnum;i++) 
	 for(j=0;j<G->vexnum;j++)
	    {
	    	G->AdjMatrix[i][j]=MaxInt;
		}
	
	 //4.构建邻接矩阵
	 int n,m;
	 VertexType v1,v2;
	 int w;//v1->v2的权值 
	 FILE *fp1;
	 fp1=fopen("江苏大学地标表.txt","r");

	 for(i=0;i<G->arcnum;i++)
	 {
	 	
	 	fscanf(fp1," %d%d%d",&v1,&v2,&w);//w是路径长度。 
	 	n=LocateVex(G,v1); //获取v1所对应的在Vertex数组中的坐标 
	 	m=LocateVex(G,v2); //获取v2所对应的在Vertex数组中的坐标
	 	
	 	if(n==-1||m==-1)
		 {
		 	printf("NO This Vertex!\n");
		 	return;
		  } 
	
	   G->AdjMatrix[n][m]=w;
	 }
	 fclose(fp1);
}

//这是最短路径求解子函数，依次遍历。 
void displayPath(int dist[],int path[],MGraph *G,VertexType start,VertexType final)
{
	int i,k,j=0;
	int temp[VertexMax];//临时数组 
	VertexType target;//目标地点 
	int loc=0; 
	
	for(i=0;i<VertexMax;i++)
	temp[i]=-1;
	
    printf("**********************************************************\n");
	 
    print();
    printf("**********************************************************\n");
	//最短路径 
	for(i=0;i<G->vexnum;i++)
	{
		loc=i;//i每加一就对loc重置一遍。 
		j=0;
		while(loc!=-1)
    	{//将loc计入数组以统计遍历过的地址。 
    		temp[j]=loc;
    		loc=path[loc];
    		j++;
		}
		
		if(j-1==0&&G->Vertex[temp[j-1]]==start)//如果当前地址到起点是最短的，那么就可以输出当前点。 
			{
				if(final==0||final==i+1)
				{//合法的话就输出起点终点以便让用户看到。 
				
				printf("\t");
				printf("始发：%d 终到：%d\n\t%d为起始点!",start,G->Vertex[i],G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else if(j-1==0&&G->Vertex[temp[j-1]]!=start) 
			{//不合法的话就弹出警告。
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("始发：%d 终到：%d\n\t%d不可达%d",start,G->Vertex[i],start,G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else
			{//如果是终点那么就可以结束循环了。 
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("始发：%d 终到：%d  \n",start,G->Vertex[i]);
				int clever=j-1;
				printf("\t");
				printf("最优线路："); 
				for(j=j-1;j>=0;j--)
				{
					if(j!=clever)printf("->");
					printf("%d",G->Vertex[temp[j]]);
				}
				printf("(总路程长度:%d)",dist[i]);	 printf("\n"); 
			    }
			    
			}
	    for(k=0;k<20;k++)
	    temp[k]=-1;
	}
}
//找最近路径的子函数，不断调用此子函数以找到最短路径。 
int FindMinDist(int dist[],int s[],int vexnum) 
{
	int i;
	int loc;
	int min=MaxInt+1;
	for(i=0;i<vexnum;i++)
	{
		if(s[i]==0)//只对s[i]=0的顶点进行查找 
		{
			if(dist[i]<min)//如果找到的路径比当前遍历过的最近路径还近，就替换它直到最短。 
			{
				min=dist[i];
				loc=i;
			}
		}
	}
	return loc;//返回dist中最小元素的下标 
}

//下面是输出两点之间全部路径的子函数。我们先建立存放地址的结构体。 
 typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numNodes;
	int numEdges;
}Mgraph;
Mgraph G;
//建立图的子函数，将起点，终点都存入G.arc里，便于直观查看。 
int initgraph()
{
	int i,j;
	for(i=0;i<=15;i++)
	  for(j=0;j<=15;j++)
	  G.arc[i][j]=Infinity;
	  for(i=0;i<=15;i++)
	    G.arc[i][i]=0;
	  FILE *fp;
	  int m;
	  fp=fopen("地标缓冲表.txt","r") ;
	  for(m=0;m<32662;m++)
	  fscanf(fp,"%d%d%d",&i,&j,&G.arc[i][j]);
	  fclose(fp);
	    return ;	  
}

//打印每一条路径的子函数，每遍历到一个点，就接着往下找没有遍历过的点找到终点为止，然后返回最初一个拥有两个以上可以继续遍历的点，继续遍历直到完成所有遍历。 
int path(int m,int n,int k);

//输出所有路径的主程序，通过这个函数，我们可以输入起止位置并调用path子函数完成所有路径的遍历。
//注意：本函数不完善没法输出相邻两点作为起止点的路径，原因我找到了是因为下一个点作为终点的时候会自动返回上一个点无法输出。 
int allpath()
{	int k,i,j,m,n;
printf("**********************************************************\n");
print();
printf("**********************************************************\n");
	printf("请输入您想要查询的两个地标的编号：");
	scanf("%d%d",&m,&n);
	if(m>=0&&m<=15&&n>=0&&n<=15)
	{d[0]=m;//存储路径起点m（int d[]数组是全局变量） 
	for(k=0;k<15;k++)//全部顶点访问标志初值设为0 
	  visited[k]=0;printf("**********************************************************\n");printf("\n");
	visited[m]=1;//第m个顶点访问标志设置为1 
	path(m,n,0);   	
    }  
	 else
	 {
	 	printf("**********************************************************\n");
	 	printf("                          输入有误                        \n");
	 }                                           //调用程序。k=1，对应起点d[1]==m。k为d[]数组下标 
	return 1;
}




//打印每一条路径的子函数，每遍历到一个点，就接着往下找没有遍历过的点找到终点为止，然后返回最初一个拥有两个以上可以继续遍历的点，继续遍历直到完成所有遍历。 
int path(int m,int n,int k)
{	int s,t,time=0;                                                //t用于存放路径上下一个顶点对应的d[]数组元素的下标 
	t=k+1;	

	
	if(d[k]==n&&k<16)                                                 //若d[k]是终点n且地点个数<=16,则输出该路径 
	{	for(s=0;s<k;s++)                                             //计算路径长度 
	    {    	 
	    	time=time+G.arc[d[s]][d[s+1]];
		} 
		                                              //打印路径长度小于定长的路径 
		{	for(s=0;s<k;s++)                                         //输出该路径。s=0时为起点m 
	        {
	    	   printf("%d->",d[s]);
		    } 
	        printf("%d  ",d[s]);  
			printf("（时间花费%d分钟）",time/50);                                   //输出最后一个地点（即顶点n的序号，此时s==k）	
            printf("\n\n");
		}
	} 
	else
	{	s=1;
		while(s<=15)//从第m个顶点，试探所有顶点是否有路径 
		{	if((G.arc[d[k]][s]<Infinity)&&(visited[s]==0))//顶点m到顶点s有边(权值不为无穷大)，且未被访问 
			{	visited[s]=1;
				d[k+1]=s;//存储顶点编号 
				path(m,n,t);
				visited[s]=0;//将找到的路径上顶点的访问标志重新设置为0，以用于试探新的路径 
			}
			s++;//试探从下一个顶点s开始是否有到终点的路径 
		}
	}	
} 

//调取程序的子函数，用处不是很大也可以分开调取。 
int allpathtest()
{
	initgraph();
	allpath();
	return 0;
 } 
 
//这是迪杰斯特拉算法的子函数 
void ShortestPath_Dijkstra(MGraph *G,VertexType start,VertexType final)
{
	int i,j,num;
	int loc;
	int min;
	int dist[VertexMax];//最短路径长度数组 
	int path[VertexMax];//最短路径数组 
	int s[VertexMax];//代表集合S（1代表该顶点已处理，属于集合S；0代表该顶点未处理，不属于集合S，属于集合V-S） 
	
	//1.初始化dist和path数组 
	loc=LocateVex(G,start);//获取源点的下标位置 
	for(i=0;i<G->vexnum;i++)
	{
		dist[i]=G->AdjMatrix[loc][i];
		
		if(dist[i]!=MaxInt)
		{
			path[i]=loc;//标记存入i 
		}
		else
		{
			path[i]=-1;
		}	  
	} 
    
    //2.初始化S数组（s数组：代表集合S，1代表该元素属于集合S(已处理的顶点)，0该元素不属于集合S(未处理的顶点)） 
    for(i=0;i<G->vexnum;i++)
	{
		s[i]=0;
	} 
	s[loc]=1;//代表起始点(源点)以处理完毕 
	num=1;
	
	while(num<G->vexnum)
	{
		min=FindMinDist(dist,s,G->vexnum);//在dist数组中查找其对应s[i]=0，即未处理的最小值元素 
		s[min]=1;//将找到的最短边所对应的的顶点加入集合S
		
		for(i=0;i<G->vexnum;i++)//加入新的顶点后，更新dist和path数组 
		{
			if((s[i]==0)&&(dist[i]>dist[min]+G->AdjMatrix[min][i]))
			{
				dist[i]=dist[min]+G->AdjMatrix[min][i];
				path[i]=min;//min->i
			}
		}
	    num++;	
	} 
    displayPath(dist,path,G,start,final);//展示dist数组、path数组及最短路径 
    
} 


//找最短路径，下面的子函数应该都讲过了。 
void zuiduanlujing() 
{
	
	MGraph G;
	VertexType start,final;
	
	CreateDN(&G);
	printf("**********************************************************\n");
    print();
	printf("**********************************************************\n");
	printf("输入起始点："); 
	scanf(" %d",&start);
	printf("**********************************************************\n");
	printf("输入终到点："); 
	scanf(" %d",&final);
    system("cls");
	ShortestPath_Dijkstra(&G,start,final);
	
	 
}

//五棵松始发到全部地址的最短路径，求最短路径的变种，把起点改成五棵松就行。 
void wkssf() 
{
	
	MGraph G;
	VertexType start,final;
	
	CreateDN(&G);
	start=1; 
	final=0;
	ShortestPath_Dijkstra(&G,start,final);
	
	 
}


//增加公交线路子函数，因为公交可以跳站，所以默认全图联通，可任意编辑合法站点。 
void addline() 
{
	FILE *fp1;
	fp1=fopen("公交路线.txt","a+");
	int i,site;
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("输入公交路线（以输入-1作为结束）：");
	for(i=0;i<15;i++)
	{
		scanf("%d",&site);
		if(site>15||site<-1)
	    { 
		printf("**********************************************************\n");
		printf("            *          输入有误          *               \n");
		break;
		}
	    else if(site==-1) 
		{
		fprintf(fp1,"-1 ");//-1表示输入结束。 
		break;
		}
		else fprintf(fp1," %d ",site);//循环输入站点。 
	} system("cls");
	printf("**********************************************************\n");
	printf("            *          程序完成          *               \n");
	fclose(fp1);
}

//辅助子函数，用于将数组写入文件，没啥用。 
void help(int bus[])
{
	  int i;
	  FILE *fp1;
	   fp1=fopen("公交路线.txt","w");
       for(i=0;i<240;i++)
       if(bus[i]!=0&&bus[i]!=-2)//换种思路，0为空，不输出0就行了 。 
       fprintf(fp1,"%d ",bus[i]);
       fclose(fp1);
       
}

//修改线路子函数，原理就是直接把文件导入数组，改数组数据然后再写入文件。 
void changeexist()
{   
       printf("**********************************************************\n");
	   printf("您想要修改的线路是：");
	   int changeline;
	   scanf("%d",&changeline);system("cls");
	   int bus[240];
       FILE *fp1;
       fp1=fopen("公交路线.txt","r");
	   int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//空数据默认为0以避免输出时输出地址影响观感。 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//将文件里的数据导入数组。
       n=0;
       
       
       for(i=0;i<140;i++)
       {
       	if(bus[i]==-1)
       	n++;
       	if(n==changeline)
       	{
       	   break;	
		}
	   }
	   
	   
	   int bus2[15]={0};
	   int remem=i+1;
	   int k=0;
       for(j=i+1;bus[j]!=-1;j++)
       	{
		   bus2[k]=bus[j];
		   k++;
	    }
	    
	    
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	    printf("线路%d通过以下站点：",changeline);
	    for(i=0;bus2[i]!=0;i++)
	    {
	    	print2(bus2[i]);
		}
		printf("\n");
	printf("**********************************************************\n");
	printf("                        您想要                           \n");
	printf("                      1	 替换站点                           \n");
	printf("                      2	 删除站点                           \n");
	printf("                      3	 删除线路                           \n");
	printf("                      4	 退出程序                           \n"); 
	printf("**********************************************************\n");
	printf("输入操作序号：");
	int donum;
	scanf("%d",&donum);system("cls");
	if(donum==1)
	{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("您想要替换掉的站点为：");
	int wantchan,afterchan;
	scanf("%d",&wantchan); 
	printf("**********************************************************\n");
	printf("替换后的站点为：");
	scanf("%d",&afterchan); system("cls");
	if(afterchan>15||afterchan<1||wantchan>15||wantchan<1) goto loop;
	for(i=0;i<15;i++)
	{
		if(bus2[i]==wantchan)
		bus2[i]=afterchan;
	} 
	
	
	k=0;
       for(j=remem;bus2[k]!=0;j++)
       	{
		   bus[j]=bus2[k];
		   k++;
	    }
	printf("**********************************************************\n");
	printf("            *          变更成功          *               \n");
	help(bus); 
	}
	
	else if(donum==2)
	{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("您想要删除掉的站点为：");
	int wantchan,afterchan;
	scanf("%d",&wantchan); system("cls");
	if(wantchan>15||wantchan<1) goto loop;
	afterchan=-2; 
	for(i=0;i<15;i++)
	{
		if(bus2[i]==wantchan)
		bus2[i]=afterchan;
	} 
	
	
	k=0;
       for(j=remem;bus2[k]!=0;j++)
       	{
		   bus[j]=bus2[k];
		   k++;
		}
	printf("**********************************************************\n");
	printf("            *          变更成功          *               \n");
	help(bus); 
    }
    
    
	else if(donum==3)
	{
		
		
		 for(j=remem;bus[j]!=-1;j++)
       	{
		   bus[j]=0;
	    }
	    bus[remem-1]=0;
	    printf("**********************************************************\n");
	    printf("            *          变更成功          *               \n");
	    help(bus); 
		
	 } 
	
	else if(donum==4)
	exit(0);
	else 
	{
	loop:
	printf("**********************************************************\n");
	printf("            *          输入有误          *               \n");
    }
    
       
	   fclose(fp1);	 
}

//删除站点子函数，将文件里的数据导入数组并将要删除的站点变成零，在写入数组的时候不将它写入，它就被删掉了。 
void deletesite() 
{
       int bus[240];
       FILE *fp1;
       fp1=fopen("公交路线.txt","r");
       int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//空数据默认为0以避免输出时输出地址影响观感。 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//将文件里的数据导入数组。 
       int deletesite;
       fp1=fopen("公交路线.txt","w");
    printf("**********************************************************\n");
	print();
       printf("**********************************************************\n你要删除的站点为：");
       scanf("%d",&deletesite);system("cls");
       if(deletesite<=15&&deletesite>0)  
	   { 
		printf("**********************************************************\n");
		printf("            *          删除成功          *               \n");
	   } 
       if(deletesite>15||deletesite<=0)  
	   { 
		printf("**********************************************************\n");
		printf("            *          输入有误          *               \n");
	   } 
       for(i=0;i<240;i++)
       {
       	if(bus[i]==deletesite)
       	bus[i]=0;//将要删除的站点置空。 
	   }
	   for(i=0;i<240;i++)
       if(bus[i]!=0)
       fprintf(fp1,"%d ",bus[i]);
	   fclose(fp1);	 
}

//下一站增站法。 找到要增加站点的下一站，在前面加上它。 
void nextsta(int bus[],int creatsite)
{
	start:
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");  
	printf("该站点下一站为：");
	int next;
	scanf("%d",&next);system("cls");//先给出增加站点的下一站（next节点）。 
	if(next>15||next<0)
	{
	printf("**********************************************************\n"); 
	printf("            *          输入有误          *               \n");
	goto start;
    }
    int i,j;
    for(i=0;i<240;i++)
	{
		if(bus[i]==next)//找到我们输入的下一站。 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//将下一站之后的站数据全部后移。 
			}
			bus[i]=creatsite;//要增加的站点赋给i。 
			i++;
		}
	 } 


    FILE *fp1;
    fp1=fopen("公交路线.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) //同理，0为空，若原线路有该站点将不写入文件。 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);	
}
//上一站增站法。 原理同上。
void frontsta(int bus[],int creatsite) 
{
	start:
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");  
	printf("该站点上一站为：");
    int front;
    scanf("%d",&front);system("cls");
  	if(front>15||front<0)  
	{
	printf("**********************************************************\n");
	printf("            *          输入有误          *               \n");
	goto start;
    }
    int i,j;
    
    for(i=1;i<240;i++)
	{
		if(bus[i-1]==front)//找到我们输入的上一站。 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//将上一站之后的站数据全部后移。 
			}
			bus[i]=creatsite;//要增加的站点赋给i。 
			i++;
		}
	 } 
    
    
    
	FILE *fp1;
    fp1=fopen("公交路线.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);
		
}
//两端增站法。原理同上。 
void betweensta(int bus[],int creatsite)
{
	start:
	printf("**********************************************************\n");
    print();
	printf("**********************************************************\n"); 
	int front,next; 
	printf("该站点上一站为：");
	scanf("%d",&front);
	printf("**********************************************************\n");
	printf("该站点下一站为：");
	scanf("%d",&next);system("cls");
	if(front>15||front<0||next>15||next<0)  
	{
	printf("**********************************************************\n");
	printf("            *          输入有误          *               \n");
	goto start;
    }
    int i,j;
	
	for(i=1;i<240;i++)
	{
		if(bus[i-1]==front&&bus[i]==next)//找到我们输入的上一站和下一站。 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//将上一站之后的站数据全部后移。 
			}
			bus[i]=creatsite;//要增加的站点赋给i。 
			i++;
		}
	 } 
    
    
    
	FILE *fp1;
    fp1=fopen("公交路线.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);
	
	
}

//调取增站的子函数。 
void addsite()
{
	   int bus[240];
       FILE *fp1;
       fp1=fopen("公交路线.txt","r");
       int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);
	   fclose(fp1);
	   int creatsite;
	   start:
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");   
	   printf("你要增加的站点为：");
       scanf("%d",&creatsite); system("cls");
       printf("**********************************************************\n\n");
       printf("            *      1  该站点有下一站    *                \n");
       printf("            *      2  该站点有上一站    *                \n");
       printf("            *      3 该站点在两站之间   *                \n");
	   printf("            *      4 我不想添加站点了   *                \n\n"); 
       printf("**********************************************************\n");
       printf("请选择站点插入方式：");
	   int choose1;
	   scanf("%d",&choose1);system("cls");
	   if(choose1==1)
	   nextsta(bus,creatsite);
	   else if(choose1==2)
	   frontsta(bus,creatsite);
	   else if(choose1==3)
	   betweensta(bus,creatsite);
	   else if(choose1==4) 
	   {
	   printf("**********************************************************\n");
	   printf("            *     正试图返回主菜单       *                \n");
       }
	   else goto start; 
	   
}
//管理员端页面。 
void administrator()
{ 
//UI设计
	printf("**********************************************************\n\n");
	printf("            *       管理员用户 你好      *               \n");
	printf("            *       1  新增公交线路      *              \n");
	printf("            *       2  修改已有线路      *              \n");
	printf("            *       3  删除已有站点      *              \n");
	printf("            *       4  增加公交站点      *              \n");
	printf("            *       5   返回上一级       *              \n\n");
	printf("**********************************************************\n");;
	int cho1;
	printf("请输入选项序号：");scanf("%d",&cho1);system("cls");
	if(cho1==1)
	addline();
	else if(cho1==2)
	changeexist();
	else if(cho1==3)
	deletesite();
	else if(cho1==4)
	addsite();
	else if(cho1==5)
	;
	else
    {
    printf("**********************************************************\n");
	printf("            *       您的输入不合法       *               \n");
    }
    printf("            *          增加成功          *               \n");
 }
//线路查询子函数，将文件数据导入数组在数组中查找相应位置线路通过的站点。 
void chaxun1()
{
	   printf("**********************************************************\n");
	   printf("您想要查询的线路是：");
	   int cxline;
	   scanf("%d",&cxline);system("cls");
	   int bus[240];
       FILE *fp1;
       fp1=fopen("公交路线.txt","r");
	   int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//空数据默认为0以避免输出时输出地址影响观感。 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//将文件里的数据导入数组。
       n=0;
       
       
       for(i=0;i<140;i++)
       {
       	if(bus[i]==-1)
       	n++;
       	if(n==cxline)
       	{
       	   break;	
		}
	   }
	   
	   
	   int bus2[15]={0};
	   int remem=i+1;
	   int k=0;
       for(j=i+1;bus[j]!=-1;j++)
       	{
		   bus2[k]=bus[j];
		   k++;
	    }
	    
	    
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	    printf("线路%d通过以下站点：",cxline);
	    for(i=0;bus2[i]!=0;i++)
	    {
	    	print2(bus2[i]);
		}
		printf("\n");
		fclose(fp1);
}
//查询所有线路的子函数，比上面的函数更简单，直接把所有线路输出一遍。 
void chaxun2()
{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	int bus[240];
	FILE *fp1;
	int i;
    fp1=fopen("公交路线.txt","r");
    for(i=0;i<240;i++)
    bus[i]=0;
    for(i=0;i<240;i++)
    fscanf(fp1,"%d",&bus[i]);
    int m=1;
    for(i=0;i<240;i++)
    {
    	if(bus[i]==-1&&bus[i+1]!=0) 
		{
		printf("\n%d号线：",m);
		m++;
		}
    	else if(bus[i]!=0&&bus[i+1]!=0)
		print2(bus[i]);
		else 
		{
			printf("\n\n");
			break;
		}
	}
	fclose(fp1);
}

//将行形式的公交路线文件转化为有头节点和尾节点的表形式，行变表。 
void hangbianbiao()
{
	
	   int bus[240];
       FILE *fp1;
       fp1=fopen("公交路线.txt","r");
       int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//空数据默认为0以避免输出时输出地址影响观感。 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//将文件里的数据导入数组。
	   int busplus[240][3];
	   for(i=0;i<240;i++)
	   for(j=0;j<2;j++)
	   busplus[i][j]=0;
	   for(i=0;i<240;i++)
	   busplus[i][2]=5;
	   j=0;
	   for(i=0;i<240;i++)
	   {
	   	   if(bus[i]!=-1&&bus[i]!=0&&bus[i+1]!=-1&&bus[i+1]!=0)
	   	   {
	   	   	  busplus[j][0]=bus[i];
	   	   	  busplus[j][1]=bus[i+1];
	   	   	  j++;
			  }
		} 
		
		for(i=0;i<240;i++)
		for(j=0;j<2;j++)
		{
			if(busplus[i][j]==0)
			busplus[i][2]=0;
		}
		fp1=fopen("公交表.txt","w");
		
		for(i=0;i<240;i++)
		{
		
		for(j=0;j<3;j++)
		{
			if(busplus[i][j]!=0)
			fprintf(fp1,"%d  ",busplus[i][j]);
		}
		fprintf(fp1,"\n");
	}
	fclose(fp1);
}
//将变成表的公交线路与学校地图表作对比，如果两点之间有公交，则可以自动坐公交。 
void duibi()
{
	FILE *fp01;
    fp01=fopen("江苏大学地标表.txt","r");
    FILE *fp02;
    fp02=fopen("公交表.txt","r");
    int dibiao[240][3];
	int gongjiao[240][3];
	int i,j;
	for(i=0;i<240;i++)
	for(j=0;j<3;j++)
	{
		dibiao[i][j]=0;
		gongjiao[i][j]=0;
	 } 
	for(i=0;i<240;i++)
	for(j=0;j<3;j++)
	{
		fscanf(fp01,"%d",&dibiao[i][j]);
	
	 } 
	 for(i=0;i<240;i++)
	for(j=0;j<3;j++)
	{
		fscanf(fp02,"%d",&gongjiao[i][j]);
	
	 } 

for(i=0;i<240;i++)
for(j=0;j<240;j++)
{
	if(i!=j&&gongjiao[i][0]==gongjiao[j][0]&&gongjiao[i][1]==gongjiao[j][1])
	{
	gongjiao[i][0]=0;
	gongjiao[i][1]=0;
	gongjiao[i][2]=1;}
}


	 for(i=0;i<240;i++)
	 for(j=0;j<240;j++)
	 {
	 	if((dibiao[i][0]==gongjiao[j][0]&&dibiao[i][1]==gongjiao[j][1])&&(dibiao[i][0]!=0&&gongjiao[j][0]!=0))
	 	dibiao[i][2]=(dibiao[i][2]/gongjiao[j][2]);
	 	else dibiao[i][2]==dibiao[i][2];
	 }
	 
	 FILE *fp03;
	 fp03=fopen("地标缓冲表.txt","w+");
	 for (i=0;i<240;i++)
	{
	  for(j=0;j<3;j++)
	 {
	 	if(dibiao[i][j]!=0)
	 	fprintf(fp03,"%d ",dibiao[i][j]);
	 }
	 fprintf(fp03,"\n");
	 }
	 fclose(fp01);
	 fclose(fp02);
	 fclose(fp03);
}
//以有公交线路的地图再次寻找最短路径（两点之间有公交就相当于两点之间变短） 
void CreateDN2(MGraph *G) 
{
	int i,j;
	//1.输入顶点数和边数 

	G->vexnum=15; 

	G->arcnum=36;

	//2.输入顶点元素 
	for(i=0;i<15;i++)
	G->Vertex[i]=i+1;

	//3.矩阵初始化
	for(i=0;i<G->vexnum;i++) 
	 for(j=0;j<G->vexnum;j++)
	    {
	    	G->AdjMatrix[i][j]=MaxInt;
		}
	
	 //4.构建邻接矩阵
	 int n,m;
	 VertexType v1,v2;
	 int w;//v1->v2的权值 
	 FILE *fp1;
	 fp1=fopen("地标缓冲表.txt","r");

	 for(i=0;i<G->arcnum;i++)
	 {
	 	
	 	fscanf(fp1," %d%d%d",&v1,&v2,&w);
	 	n=LocateVex(G,v1); //获取v1所对应的在Vertex数组中的坐标 
	 	m=LocateVex(G,v2); //获取v2所对应的在Vertex数组中的坐标
	 	
	 	if(n==-1||m==-1)
		 {
		 	printf("NO This Vertex!\n");
		 	return;
		  } 
	
	   G->AdjMatrix[n][m]=w;
	 }
	 fclose(fp1);
}
void displayPath2(int dist[],int path[],MGraph *G,VertexType start,VertexType final);

typedef int VertexType; 
void ShortestPath_Dijkstra2(MGraph *G,VertexType start,VertexType final)
{
	int i,j,num;
	int loc;
	int min;
	int dist[VertexMax];//最短路径长度数组 
	int path[VertexMax];//最短路径数组 
	int s[VertexMax];//代表集合S（1代表该顶点已处理，属于集合S；0代表该顶点未处理，不属于集合S，属于集合V-S） 
	
	//1.初始化dist和path数组                             //1079-1093行代码没啥用，我抄的以前自己写过的代码，为了避免程序不能运行就没删。 
	loc=LocateVex(G,start);//获取源点的下标位置 
	for(i=0;i<G->vexnum;i++)
	{
		dist[i]=G->AdjMatrix[loc][i];
		
		if(dist[i]!=MaxInt)
		{
			path[i]=loc;
		}
		else
		{
			path[i]=-1;
		}	  
	} 
    
    //2.初始化S数组（s数组：代表集合S，1代表该元素属于集合S(已处理的顶点)，0该元素不属于集合S(未处理的顶点)） 
    for(i=0;i<G->vexnum;i++)
	{
		s[i]=0;
	} 
	s[loc]=1;//代表起始点(源点)以处理完毕 
	num=1;
	
	while(num<G->vexnum)
	{
		min=FindMinDist(dist,s,G->vexnum);//在dist数组中查找其对应s[i]=0，即未处理的最小值元素 
		s[min]=1;//将找到的最短边所对应的的顶点加入集合S
		
		for(i=0;i<G->vexnum;i++)//加入新的顶点后，更新dist和path数组 
		{
			if((s[i]==0)&&(dist[i]>dist[min]+G->AdjMatrix[min][i]))
			{
				dist[i]=dist[min]+G->AdjMatrix[min][i];
				path[i]=min;//min->i
			}
		}
	    num++;	
	} 
    displayPath2(dist,path,G,start,final);//展示dist数组、path数组及最短路径 
    
} 
//寻找最短路径的子函数，上面已经讲过。 
void displayPath2(int dist[],int path[],MGraph *G,VertexType start,VertexType final)
{
	int i,k,j=0;
	int temp[VertexMax];//临时数组 
	VertexType target;//目标地点 
	int loc=0; 
	
	for(i=0;i<VertexMax;i++)
	temp[i]=-1;
	
    printf("**********************************************************\n");
	 //最短路径 
    print();
    printf("**********************************************************\n");
	for(i=0;i<G->vexnum;i++)
	{
		loc=i;
		j=0;
		while(loc!=-1)
    	{
    		temp[j]=loc;
    		loc=path[loc];
    		j++;
		}
		
		if(j-1==0&&G->Vertex[temp[j-1]]==start)
			{
				if(final==0||final==i+1)
				{
				
				printf("\t");
				printf("始发：%d 终到：%d\n\t%d为起始点!",start,G->Vertex[i],G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else if(j-1==0&&G->Vertex[temp[j-1]]!=start)
			{
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("始发：%d 终到：%d\n\t%d不可达%d",start,G->Vertex[i],start,G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else
			{
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("始发：%d 终到：%d  \n",start,G->Vertex[i]);
				int clever=j-1;
				printf("\t");
				printf("最优线路："); 
				for(j=j-1;j>=0;j--)
				{
					if(j!=clever)printf("->");
					printf("%d",G->Vertex[temp[j]]);
				}
				printf("(总路程时间:%.2f分钟)",((float)dist[i])/50);	 printf("\n");
			    }
			    
			}
	    for(k=0;k<20;k++)
	    temp[k]=-1;
	}
}
//最短路径。 
void zuiduanlujing2() 
{
	
	MGraph G;//写的最短路径其实是求最小时间，为减轻工作量用的最短路径的源码。 
	VertexType start,final;
	
	CreateDN2(&G);
	printf("**********************************************************\n");
    print();printf("**********************************************************\n");
	printf("输入起始点："); 
	scanf(" %d",&start);
	printf("**********************************************************\n");
	printf("输入终到点："); 
	scanf(" %d",&final);
    system("cls");
	ShortestPath_Dijkstra2(&G,start,final);
	
	 
}
//最短路径。 
void zuiduan2()
{
	hangbianbiao();
	duibi();
	zuiduanlujing2();
 } 
//查询公交表有几行的子函数，便于确定有几条弧，以便确定有无环线。 
int hangshu()
{
	FILE *fp;
	fp=fopen("公交表.txt","r");
	int a[240];int i;
	for(i=0;i<240;i++)
	a[i]=0 ;
	for(i=0;i<240;i++)
	fscanf(fp,"%d",&a[i]);
	for(i=0;i<240;i++)
	{
	if(a[i]==0)
    break;
	}
	int m;m=i/3;
	return m;
	fclose(fp);
}

//创建结构体以存储公交路径。 
typedef int Boolean;
typedef int VertexType1;
Boolean visit[MaxVertexNum];
typedef struct node
{
    int adjvex;//弧 
    struct node *next;//下一个节点 
}EdgeNode;

typedef struct
{
    VertexType1 vertex;
    EdgeNode *firstedge;//头节点 
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];

typedef struct
{
    AdjList adjlist;
    int n,e;//弧和节点个数 
}ALGraph;

int FindVertex(ALGraph *G ,int e,int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        if(G->adjlist[i].vertex==e)
        {
            return i;
        }
    }
    return -1;
}
void create(ALGraph *G)			//创建邻接表
{
    int i,j,k,w,v;
    EdgeNode *s;

    G->n=15;//共有15个节点。 
    
	
    G->e=hangshu();//共有【读取行数】个弧 。 
    for(i=0;i<G->n;i++)
    {

        
        fflush(stdin);
        G->adjlist[i].vertex=i+1;
        G->adjlist[i].firstedge=NULL;
    }
    FILE *fp2;
    fp2=fopen("公交表.txt","r");
    int num;
    for(k=0;k<G->e;k++)
    {
        
        fscanf(fp2,"%d%d%d",&i,&j,&num);
        i=FindVertex(G,i,G->n);
        j=FindVertex(G,j,G->n);//读入表中数据。 
        if(i==-1||j==-1)
        {
            
            
            fscanf(fp2,"%d%d%d",&i,&j,&num);
            i=FindVertex(G,i,G->n);
            j=FindVertex(G,j,G->n);//读入表中数据。 
        }
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=(j);
        s->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=s;//找到下一个节点。 
    }
    fclose(fp2); 
}
//用的拓扑排序的代码，该代码可以判断环线。 
void TopoSort(ALGraph *G,int n)
{
    int i,j,k,top,m=0;
    EdgeNode *p;
    int *d=(int *)malloc(n*sizeof(int));		
    for(i=0;i<n;i++)		//初始化数组
    {
        d[i]=0;
    }
    for(i=0;i<n;i++)		//统计各个顶点的入度情况，并把他们填入数组里面
    {
        p=G->adjlist[i].firstedge;
        while(p!=NULL)
        {
            j=p->adjvex;
            d[j]++;
            p=p->next;
        }
    }
    top=-1;
    for(i=0;i<n;i++)			//先找出里面入度是0的顶点
    {
        if(d[i]==0)
        {
            d[i]=top;
            top=i;
        }
    }

    while(top!=-1)
    {
        j=top;	
        top=d[top];
     		
        m++;		//统计顶点
        p=G->adjlist[j].firstedge;
        while(p)
        {
            k=p->adjvex;		//相连接的顶点
            d[k]--;		//相连接的顶点入度减1
            if(d[k]==0)		//如果发现入度为0的新顶点，从该顶点出发
            {
                d[k]=top;
                top=k;
            }
            p=p->next;
        }

    }
    printf("**********************************************************\n");
    if(m<n) printf("                     校内公交有环线！\n");
    else printf("                       校内公交没有环线！\n") ; 
    free(d);
}

//判断环线的子函数。 
void panduanhuanxian()
{
	hangbianbiao();
    ALGraph *G=(ALGraph *)malloc(sizeof(ALGraph));
    EdgeNode *p;
    create(G);
    int i;

    for(i=0;i<G->n;i++)
    {
        p=G->adjlist[i].firstedge;
        while(p!=NULL)
        {
           
            p=p->next;
        }
  
    }
    TopoSort(G,G->n);
 } 
 













int initgraph22()
{
	int i,j;
	for(i=0;i<=15;i++)
	  for(j=0;j<=15;j++)
	  G.arc[i][j]=Infinity;
	  for(i=0;i<=15;i++)
	    G.arc[i][i]=0;
	  FILE *fp;
	  int m;
	  fp=fopen("地标缓冲表.txt","r") ;
	  for(m=0;m<32662;m++)
	  fscanf(fp,"%d%d%d",&i,&j,&G.arc[i][j]);
	  fclose(fp);
	    return ;	  
}


void huanchengzhan()
{
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("公交路线.txt","r");
	fp2=fopen("换乘表.txt","w");
	fprintf(fp2," ");
	fp2=fopen("换乘表.txt","w");
	int hcb[240]={0};
	int i;
	for(i=0;i<240;i++)
	{
		fscanf(fp1,"%d",&hcb[i]);
	}
	int hcb2[240]={0};
	for(i=0;i<240;i++)
	{
		hcb2[i]=hcb[i];
	}

	int j;
	int hcb3[240]={0};
	int k=0;
	for(i=0;i<240;i++)
	for(j=0;j<240;j++)
	{
		if(i==j) j++;
		if(hcb[i]==hcb2[j]&&hcb[i]!=0&&hcb[i]!=-1)
		{
		hcb3[k]=hcb[i];
		k++;
		}
 
	}
	for(i=0;i<240;i++)
	for(j=0;j<240;j++)
	{
		if(hcb3[i]==hcb3[j]&&i!=j)
		hcb3[i]=0;
	}
    for(i=0;i<240;i++)
    {
    	if(hcb3[i]!=0)
    	fprintf(fp2,"%d  ",hcb3[i]);
	}
	fclose(fp1);
	fclose(fp2);
}






//打印每一条路径的子函数，每遍历到一个点，就接着往下找没有遍历过的点找到终点为止，然后返回最初一个拥有两个以上可以继续遍历的点，继续遍历直到完成所有遍历。 
int path22(int m,int n,int k);

//输出所有路径的主程序，通过这个函数，我们可以输入起止位置并调用path子函数完成所有路径的遍历。
//注意：本函数不完善没法输出相邻两点作为起止点的路径，原因我找到了是因为下一个点作为终点的时候会自动返回上一个点无法输出。 
int allpath22()
{	int k,i,j,m,n;
printf("**********************************************************\n");
print();
printf("**********************************************************\n");
	printf("请输入您想要查询的两个地标的编号：");
	scanf("%d%d",&m,&n);
	if(m>=0&&m<=15&&n>=0&&n<=15)
	{d[0]=m;//存储路径起点m（int d[]数组是全局变量） 
	for(k=0;k<15;k++)//全部顶点访问标志初值设为0 
	  visited[k]=0;printf("**********************************************************\n");printf("\n");
	visited[m]=1;//第m个顶点访问标志设置为1 
	path22(m,n,0);   	
    }  
	 else
	 {
	 	printf("**********************************************************\n");
	 	printf("                          输入有误                        \n");
	 }                                           //调用程序。k=1，对应起点d[1]==m。k为d[]数组下标 
	return 1;
}




//打印每一条路径的子函数，每遍历到一个点，就接着往下找没有遍历过的点找到终点为止，然后返回最初一个拥有两个以上可以继续遍历的点，继续遍历直到完成所有遍历。 
int path22(int m,int n,int k)
{	int s,t,time=0;                                                //t用于存放路径上下一个顶点对应的d[]数组元素的下标 
	t=k+1;	
    FILE *fp;int i;
    fp=fopen("换乘表.txt","r");
	int hcb[240]={0};
	for(i=0;i<240;i++)
	{
		fscanf(fp,"%d",&hcb[i]);
	}
	int temp=0;
	if(d[k]==n&&k<16)                                                 //若d[k]是终点n且地点个数<=16,则输出该路径 
	{	for(s=0;s<k;s++)                                             //计算路径长度 
	    {    	 
	    	time=time+G.arc[d[s]][d[s+1]];
		} 
		                                              //打印路径长度小于定长的路径 
		{	for(s=0;s<k;s++)                                         //输出该路径。s=0时为起点m 
	        {
	    	   printf("%d->",d[s]);
	    	   for(i=0;i<240;i++)
	    	   {
			   if(d[s]==hcb[i])
			   {
			   temp++;break;}
		       }
		    } 
	        printf("%d  ",d[s]);  
			printf("（时间花费%d分钟,共换乘%d次）",time/50,temp);                                   //输出最后一个地点（即顶点n的序号，此时s==k）	
            printf("\n\n");
		}
	} 
	else
	{	s=1;
		while(s<=15)//从第m个顶点，试探所有顶点是否有路径 
		{	if((G.arc[d[k]][s]<Infinity)&&(visited[s]==0))//顶点m到顶点s有边(权值不为无穷大)，且未被访问 
			{	visited[s]=1;
				d[k+1]=s;//存储顶点编号 
				path22(m,n,t);
				visited[s]=0;//将找到的路径上顶点的访问标志重新设置为0，以用于试探新的路径 
			}
			s++;//试探从下一个顶点s开始是否有到终点的路径 
		}
	}	
} 

//调取程序的子函数，用处不是很大也可以分开调取。 
int allpathtest22()
{
	huanchengzhan();
	initgraph22();
	allpath22();
	return 0;
 } 
 





















void student()
{
    start: 
//UI设计
	printf("**********************************************************\n\n");
	printf("            *        学生用户 你好       *               \n");
	printf("            *       1  查询公交线路      *              \n");
	printf("            *       2  规划公交线路      *              \n");
	printf("            *       3  规划最优线路      *              \n");
	printf("            *       4  判断校内环线      *              \n");
	printf("            *       5   返回上一级       *              \n\n");
	printf("**********************************************************\n");
    int cho1,cho2;
	printf("请输入选项序号：");scanf("%d",&cho1);system("cls");
	if(cho1==1)
	{
		printf("**********************************************************\n\n");
		printf("            *       1  查询指定线路      *              \n");
	    printf("            *       2  查询线路列表      *              \n");
	    printf("            *       3  查询过站线路      *              \n\n");
	    printf("**********************************************************\n");
	     printf("请输入选项序号：");scanf("%d",&cho2);system("cls");
	     if(cho2==1) 
		 chaxun1();
		 else if(cho2==2)
		 chaxun2();
		 else if(cho2==3)
		 site();
		 else goto start;
	}
	else if(cho1==2)
	allpathtest();
	else if(cho1==3)
	{
      	printf("**********************************************************\n\n");
		printf("            *       1  步行最短距离      *              \n");
	    printf("            *       2  公交最短距离      *              \n");
	    printf("            *       3  换乘次数最少      *              \n");
	    printf("            *       4  从五棵松始发      *              \n\n");
	    printf("**********************************************************\n");
	     printf("请输入选项序号：");scanf("%d",&cho2);system("cls");
	     if(cho2==1)
	     zuiduanlujing();
	     else if(cho2==2)
	     zuiduanlujing2();
	     else if(cho2==3)
		 allpathtest22(); 
	     else if(cho2==4)
	     wkssf();
    }
    if(cho1==4)
    panduanhuanxian();
	else; 
}




    
void mainmenu()
{
	start:
//UI设计 
	printf("**********************************************************\n\n");
	printf("            *这是江苏大学线路问询交互系统*              \n"); 
	printf("**********************************************************\n");
	printf("           请注意，本系统并未经过详细维护\n         请尽量输入合法范围内的数字避免程序崩溃。\n");
	chushihua();
	printf("**********************************************************\n");
	printf("            *         1  管理员端        *              \n"); 
	printf("            *         2   学生端         *              \n"); 
	printf("            *         3  退出程序        *              \n");
	printf("            *      输入数字以进行选单    *              \n\n"); 
	printf("**********************************************************\n"); 
//选择系统代码部分	
	int cho1,cho2;
	printf("请输入选项序号：");scanf("%d",&cho1);system("cls");
	if(cho1==1)
	{
	administrator(); 
//返回菜单 
	printf("**********************************************************\n\n");
	printf("            *  用户你好 这是一个返回菜单 *               \n");
	printf("            *       输入0返回主菜单      *               \n");
	printf("            *     输入其他字符退出程序   *               \n\n");
	printf("**********************************************************\n");
	printf("请输入选项序号：");scanf("%d",&cho2);system("cls");
	if(cho2==0)   goto start;
	else          exit(0);
    }
	else if(cho1==2)
	{
	student();
//返回菜单 
	printf("**********************************************************\n\n");
	printf("            *  用户你好 这是一个返回菜单 *               \n");
	printf("            *       输入0返回主菜单      *               \n");
	printf("            *     输入其他字符退出程序   *               \n\n");
	printf("**********************************************************\n");
	printf("请输入选项序号：");scanf("%d",&cho2);system("cls");
	if(cho2==0)   goto start;
	else          exit(0);
    }
	else if(cho1==3)
    exit(0);
    else if(cho1==14)
	{
    printf("**********************************************************\n");
	printf("            *   Copyright infringement   *               \n");
	printf("            *   作者：孙家扬   by  JSU   *               \n");
	goto start;
    } 
	else 
	{
	printf("**********************************************************\n");
	printf("            *您的输入有误  自动返回主菜单*               \n");
	goto start;
	}
}




int main()
{
	mainmenu();
}
