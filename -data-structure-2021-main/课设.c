#include<stdio.h>
#include<stdlib.h>
#define maxsize 16
#include<string.h>

#define MaxVertexNum 100
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

#define VertexMax 20 //��󶥵���Ϊ20
#define MaxInt 32767 //��ʾ�������
#define Infinity 2000//��ʾ����� 
#define MAXVEX 15 
#define key 15                 //keyΪ������� 
int shortest[15][15];         //����ȫ�ֱ����洢��С·�� 
int pathh[15][15];            //����洢·�� 
int d[30];
int qwe=0;
int visited[30];

void print2(int a)
{
	if(a==1)
	printf("�����  "); 
	if(a==2)
	printf("��ɽ¥  "); 
	if(a==3)
	printf("ͼ���  "); 
	if(a==4)
	printf("����¥  "); 
	if(a==5)
	printf("��ʳ��  "); 
	if(a==6)
	printf("ѧ������E��  ");
	if(a==7)
	printf("��һ��  ");
	if(a==8)
	printf("���˹�  ");
	if(a==9)
	printf("��ɽ�˶���  ");
	if(a==10)
	printf("������  ");
	if(a==11)
	printf("÷԰  "); 
	if(a==12)
	printf("ѧԷ¥  "); 
	if(a==13)
	printf("��ɽ�ٳ���  "); 
	if(a==14)
	printf("����  "); 
	if(a==15)
	printf("����¥  "); 
 } 

//����һ����ӡ���մ�ѧ��15���ر���Ӻ������ú������Ե�ȡͬ�ļ��еĵر�txt����ӡ��������char��ʽ��ӡ��Ҫ��ȡ���֣�txt������ANSI��ʽ���롣 
void print()
{
	FILE *fp1;
	fp1=fopen("���մ�ѧ�ر�.txt","r");
	fp1=fopen("���մ�ѧ�ر�.txt","rb");
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
//���ǳ�ʼ���Ӻ�������ȡͬ�ļ����µĹ���·��txt����txtӦ��-1 ��ͷ�������ļ���Ϊ�ջ�ͷ��Ϊ-1�������ĵ�Ϊ�ղ�д�뿪ͷ���-1�� 
void chushihua()
{
	FILE *fp;
	fp=fopen("����·��.txt","r");
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
     	fp=fopen("����·��.txt","w");
    	fprintf(fp,"-1 ");
	}
	else ;

	fclose(fp);
}
//����վ���ѯ�Ӻ��������Ӻ�����ȡ����·���ļ�������������飬�������У���������ͳ����Ҫ��ѯ��վ�㣬ÿ����һ��-1������·��žͼ�һ�������·��ͳ�ơ� 
void  site()
{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	int bus[240];
	FILE *fp1;
	int i,t=0;
    fp1=fopen("����·��.txt","r");
    for(i=0;i<240;i++)
    bus[i]=0;
    for(i=0;i<240;i++)
    fscanf(fp1,"%d",&bus[i]);
    int m=1;
    int search;
    printf("��Ҫ��ѯ��վ���ǣ�"); 
    scanf("%d",&search);system("cls");
    printf("**********************************************************\n");
    printf("Ϊ����ѯ����վ��ͨ��������·:"); 
    for(i=0;i<240;i++)
    {
    	if(bus[i]==-1&&bus[i+1]!=0) 
		m++;
    	if(bus[i]==search)
		{
		printf(" %d���� ",m-1);
		t++;
	    }
	}
	if(t==0) 
	printf("û����·ͨ��վ�㣡");
	printf("\n");
    fclose(fp1);
}



//���ǽṹ��Ķ��壬���ǽ�����Ҫ�������·������ȡ�� 
typedef int VertexType; //ÿ��������������Ϊ�ַ��� 

typedef struct
{
	VertexType Vertex[VertexMax];//��Ŷ���Ԫ�ص�һά���� 
	int AdjMatrix[VertexMax][VertexMax];//�ڽӾ����ά���� 
	int vexnum,arcnum;//ͼ�Ķ������ͱ���  
}MGraph;
//���ǲ����Ӻ������ú������Բ���Ԫ��v��һά���� Vertex[] �е��±꣬�������±꣬�����±����Ǿͷ���ȷ��λ�á� 
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
//�����ڽӾ��󹹽��Ӻ������ú������Թ���һ���ڽӾ��󣬴�ͬ�ļ��еĵر���ļ������ļ�����·����·�����ȴ�С�����������ڽӾ��� 
void CreateDN(MGraph *G) 
{
	int i,j;
	//1.���붥�����ͱ��� 

	G->vexnum=15; 

	G->arcnum=36;

	//2.���붥��Ԫ�� 
	for(i=0;i<15;i++)
	G->Vertex[i]=i+1;

	//3.�����ʼ��
	for(i=0;i<G->vexnum;i++) 
	 for(j=0;j<G->vexnum;j++)
	    {
	    	G->AdjMatrix[i][j]=MaxInt;
		}
	
	 //4.�����ڽӾ���
	 int n,m;
	 VertexType v1,v2;
	 int w;//v1->v2��Ȩֵ 
	 FILE *fp1;
	 fp1=fopen("���մ�ѧ�ر��.txt","r");

	 for(i=0;i<G->arcnum;i++)
	 {
	 	
	 	fscanf(fp1," %d%d%d",&v1,&v2,&w);//w��·�����ȡ� 
	 	n=LocateVex(G,v1); //��ȡv1����Ӧ����Vertex�����е����� 
	 	m=LocateVex(G,v2); //��ȡv2����Ӧ����Vertex�����е�����
	 	
	 	if(n==-1||m==-1)
		 {
		 	printf("NO This Vertex!\n");
		 	return;
		  } 
	
	   G->AdjMatrix[n][m]=w;
	 }
	 fclose(fp1);
}

//�������·������Ӻ��������α����� 
void displayPath(int dist[],int path[],MGraph *G,VertexType start,VertexType final)
{
	int i,k,j=0;
	int temp[VertexMax];//��ʱ���� 
	VertexType target;//Ŀ��ص� 
	int loc=0; 
	
	for(i=0;i<VertexMax;i++)
	temp[i]=-1;
	
    printf("**********************************************************\n");
	 
    print();
    printf("**********************************************************\n");
	//���·�� 
	for(i=0;i<G->vexnum;i++)
	{
		loc=i;//iÿ��һ�Ͷ�loc����һ�顣 
		j=0;
		while(loc!=-1)
    	{//��loc����������ͳ�Ʊ������ĵ�ַ�� 
    		temp[j]=loc;
    		loc=path[loc];
    		j++;
		}
		
		if(j-1==0&&G->Vertex[temp[j-1]]==start)//�����ǰ��ַ���������̵ģ���ô�Ϳ��������ǰ�㡣 
			{
				if(final==0||final==i+1)
				{//�Ϸ��Ļ����������յ��Ա����û������� 
				
				printf("\t");
				printf("ʼ����%d �յ���%d\n\t%dΪ��ʼ��!",start,G->Vertex[i],G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else if(j-1==0&&G->Vertex[temp[j-1]]!=start) 
			{//���Ϸ��Ļ��͵������档
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("ʼ����%d �յ���%d\n\t%d���ɴ�%d",start,G->Vertex[i],start,G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else
			{//������յ���ô�Ϳ��Խ���ѭ���ˡ� 
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("ʼ����%d �յ���%d  \n",start,G->Vertex[i]);
				int clever=j-1;
				printf("\t");
				printf("������·��"); 
				for(j=j-1;j>=0;j--)
				{
					if(j!=clever)printf("->");
					printf("%d",G->Vertex[temp[j]]);
				}
				printf("(��·�̳���:%d)",dist[i]);	 printf("\n"); 
			    }
			    
			}
	    for(k=0;k<20;k++)
	    temp[k]=-1;
	}
}
//�����·�����Ӻ��������ϵ��ô��Ӻ������ҵ����·���� 
int FindMinDist(int dist[],int s[],int vexnum) 
{
	int i;
	int loc;
	int min=MaxInt+1;
	for(i=0;i<vexnum;i++)
	{
		if(s[i]==0)//ֻ��s[i]=0�Ķ�����в��� 
		{
			if(dist[i]<min)//����ҵ���·���ȵ�ǰ�����������·�����������滻��ֱ����̡� 
			{
				min=dist[i];
				loc=i;
			}
		}
	}
	return loc;//����dist����СԪ�ص��±� 
}

//�������������֮��ȫ��·�����Ӻ����������Ƚ�����ŵ�ַ�Ľṹ�塣 
 typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numNodes;
	int numEdges;
}Mgraph;
Mgraph G;
//����ͼ���Ӻ���������㣬�յ㶼����G.arc�����ֱ�۲鿴�� 
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
	  fp=fopen("�ر껺���.txt","r") ;
	  for(m=0;m<32662;m++)
	  fscanf(fp,"%d%d%d",&i,&j,&G.arc[i][j]);
	  fclose(fp);
	    return ;	  
}

//��ӡÿһ��·�����Ӻ�����ÿ������һ���㣬�ͽ���������û�б������ĵ��ҵ��յ�Ϊֹ��Ȼ�󷵻����һ��ӵ���������Ͽ��Լ��������ĵ㣬��������ֱ��������б����� 
int path(int m,int n,int k);

//�������·����������ͨ��������������ǿ���������ֹλ�ò�����path�Ӻ����������·���ı�����
//ע�⣺������������û���������������Ϊ��ֹ���·����ԭ�����ҵ�������Ϊ��һ������Ϊ�յ��ʱ����Զ�������һ�����޷������ 
int allpath()
{	int k,i,j,m,n;
printf("**********************************************************\n");
print();
printf("**********************************************************\n");
	printf("����������Ҫ��ѯ�������ر�ı�ţ�");
	scanf("%d%d",&m,&n);
	if(m>=0&&m<=15&&n>=0&&n<=15)
	{d[0]=m;//�洢·�����m��int d[]������ȫ�ֱ����� 
	for(k=0;k<15;k++)//ȫ��������ʱ�־��ֵ��Ϊ0 
	  visited[k]=0;printf("**********************************************************\n");printf("\n");
	visited[m]=1;//��m��������ʱ�־����Ϊ1 
	path(m,n,0);   	
    }  
	 else
	 {
	 	printf("**********************************************************\n");
	 	printf("                          ��������                        \n");
	 }                                           //���ó���k=1����Ӧ���d[1]==m��kΪd[]�����±� 
	return 1;
}




//��ӡÿһ��·�����Ӻ�����ÿ������һ���㣬�ͽ���������û�б������ĵ��ҵ��յ�Ϊֹ��Ȼ�󷵻����һ��ӵ���������Ͽ��Լ��������ĵ㣬��������ֱ��������б����� 
int path(int m,int n,int k)
{	int s,t,time=0;                                                //t���ڴ��·������һ�������Ӧ��d[]����Ԫ�ص��±� 
	t=k+1;	

	
	if(d[k]==n&&k<16)                                                 //��d[k]���յ�n�ҵص����<=16,�������·�� 
	{	for(s=0;s<k;s++)                                             //����·������ 
	    {    	 
	    	time=time+G.arc[d[s]][d[s+1]];
		} 
		                                              //��ӡ·������С�ڶ�����·�� 
		{	for(s=0;s<k;s++)                                         //�����·����s=0ʱΪ���m 
	        {
	    	   printf("%d->",d[s]);
		    } 
	        printf("%d  ",d[s]);  
			printf("��ʱ�仨��%d���ӣ�",time/50);                                   //������һ���ص㣨������n����ţ���ʱs==k��	
            printf("\n\n");
		}
	} 
	else
	{	s=1;
		while(s<=15)//�ӵ�m�����㣬��̽���ж����Ƿ���·�� 
		{	if((G.arc[d[k]][s]<Infinity)&&(visited[s]==0))//����m������s�б�(Ȩֵ��Ϊ�����)����δ������ 
			{	visited[s]=1;
				d[k+1]=s;//�洢������ 
				path(m,n,t);
				visited[s]=0;//���ҵ���·���϶���ķ��ʱ�־��������Ϊ0����������̽�µ�·�� 
			}
			s++;//��̽����һ������s��ʼ�Ƿ��е��յ��·�� 
		}
	}	
} 

//��ȡ������Ӻ������ô����Ǻܴ�Ҳ���Էֿ���ȡ�� 
int allpathtest()
{
	initgraph();
	allpath();
	return 0;
 } 
 
//���ǵϽ�˹�����㷨���Ӻ��� 
void ShortestPath_Dijkstra(MGraph *G,VertexType start,VertexType final)
{
	int i,j,num;
	int loc;
	int min;
	int dist[VertexMax];//���·���������� 
	int path[VertexMax];//���·������ 
	int s[VertexMax];//������S��1����ö����Ѵ������ڼ���S��0����ö���δ���������ڼ���S�����ڼ���V-S�� 
	
	//1.��ʼ��dist��path���� 
	loc=LocateVex(G,start);//��ȡԴ����±�λ�� 
	for(i=0;i<G->vexnum;i++)
	{
		dist[i]=G->AdjMatrix[loc][i];
		
		if(dist[i]!=MaxInt)
		{
			path[i]=loc;//��Ǵ���i 
		}
		else
		{
			path[i]=-1;
		}	  
	} 
    
    //2.��ʼ��S���飨s���飺������S��1�����Ԫ�����ڼ���S(�Ѵ���Ķ���)��0��Ԫ�ز����ڼ���S(δ����Ķ���)�� 
    for(i=0;i<G->vexnum;i++)
	{
		s[i]=0;
	} 
	s[loc]=1;//������ʼ��(Դ��)�Դ������ 
	num=1;
	
	while(num<G->vexnum)
	{
		min=FindMinDist(dist,s,G->vexnum);//��dist�����в������Ӧs[i]=0����δ�������СֵԪ�� 
		s[min]=1;//���ҵ�����̱�����Ӧ�ĵĶ�����뼯��S
		
		for(i=0;i<G->vexnum;i++)//�����µĶ���󣬸���dist��path���� 
		{
			if((s[i]==0)&&(dist[i]>dist[min]+G->AdjMatrix[min][i]))
			{
				dist[i]=dist[min]+G->AdjMatrix[min][i];
				path[i]=min;//min->i
			}
		}
	    num++;	
	} 
    displayPath(dist,path,G,start,final);//չʾdist���顢path���鼰���·�� 
    
} 


//�����·����������Ӻ���Ӧ�ö������ˡ� 
void zuiduanlujing() 
{
	
	MGraph G;
	VertexType start,final;
	
	CreateDN(&G);
	printf("**********************************************************\n");
    print();
	printf("**********************************************************\n");
	printf("������ʼ�㣺"); 
	scanf(" %d",&start);
	printf("**********************************************************\n");
	printf("�����յ��㣺"); 
	scanf(" %d",&final);
    system("cls");
	ShortestPath_Dijkstra(&G,start,final);
	
	 
}

//�����ʼ����ȫ����ַ�����·���������·���ı��֣������ĳ�����ɾ��С� 
void wkssf() 
{
	
	MGraph G;
	VertexType start,final;
	
	CreateDN(&G);
	start=1; 
	final=0;
	ShortestPath_Dijkstra(&G,start,final);
	
	 
}


//���ӹ�����·�Ӻ�������Ϊ����������վ������Ĭ��ȫͼ��ͨ��������༭�Ϸ�վ�㡣 
void addline() 
{
	FILE *fp1;
	fp1=fopen("����·��.txt","a+");
	int i,site;
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("���빫��·�ߣ�������-1��Ϊ��������");
	for(i=0;i<15;i++)
	{
		scanf("%d",&site);
		if(site>15||site<-1)
	    { 
		printf("**********************************************************\n");
		printf("            *          ��������          *               \n");
		break;
		}
	    else if(site==-1) 
		{
		fprintf(fp1,"-1 ");//-1��ʾ��������� 
		break;
		}
		else fprintf(fp1," %d ",site);//ѭ������վ�㡣 
	} system("cls");
	printf("**********************************************************\n");
	printf("            *          �������          *               \n");
	fclose(fp1);
}

//�����Ӻ��������ڽ�����д���ļ���ûɶ�á� 
void help(int bus[])
{
	  int i;
	  FILE *fp1;
	   fp1=fopen("����·��.txt","w");
       for(i=0;i<240;i++)
       if(bus[i]!=0&&bus[i]!=-2)//����˼·��0Ϊ�գ������0������ �� 
       fprintf(fp1,"%d ",bus[i]);
       fclose(fp1);
       
}

//�޸���·�Ӻ�����ԭ�����ֱ�Ӱ��ļ��������飬����������Ȼ����д���ļ��� 
void changeexist()
{   
       printf("**********************************************************\n");
	   printf("����Ҫ�޸ĵ���·�ǣ�");
	   int changeline;
	   scanf("%d",&changeline);system("cls");
	   int bus[240];
       FILE *fp1;
       fp1=fopen("����·��.txt","r");
	   int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//������Ĭ��Ϊ0�Ա������ʱ�����ַӰ��۸С� 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//���ļ�������ݵ������顣
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
	    printf("��·%dͨ������վ�㣺",changeline);
	    for(i=0;bus2[i]!=0;i++)
	    {
	    	print2(bus2[i]);
		}
		printf("\n");
	printf("**********************************************************\n");
	printf("                        ����Ҫ                           \n");
	printf("                      1	 �滻վ��                           \n");
	printf("                      2	 ɾ��վ��                           \n");
	printf("                      3	 ɾ����·                           \n");
	printf("                      4	 �˳�����                           \n"); 
	printf("**********************************************************\n");
	printf("���������ţ�");
	int donum;
	scanf("%d",&donum);system("cls");
	if(donum==1)
	{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("����Ҫ�滻����վ��Ϊ��");
	int wantchan,afterchan;
	scanf("%d",&wantchan); 
	printf("**********************************************************\n");
	printf("�滻���վ��Ϊ��");
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
	printf("            *          ����ɹ�          *               \n");
	help(bus); 
	}
	
	else if(donum==2)
	{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	printf("����Ҫɾ������վ��Ϊ��");
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
	printf("            *          ����ɹ�          *               \n");
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
	    printf("            *          ����ɹ�          *               \n");
	    help(bus); 
		
	 } 
	
	else if(donum==4)
	exit(0);
	else 
	{
	loop:
	printf("**********************************************************\n");
	printf("            *          ��������          *               \n");
    }
    
       
	   fclose(fp1);	 
}

//ɾ��վ���Ӻ��������ļ�������ݵ������鲢��Ҫɾ����վ�����㣬��д�������ʱ�򲻽���д�룬���ͱ�ɾ���ˡ� 
void deletesite() 
{
       int bus[240];
       FILE *fp1;
       fp1=fopen("����·��.txt","r");
       int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//������Ĭ��Ϊ0�Ա������ʱ�����ַӰ��۸С� 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//���ļ�������ݵ������顣 
       int deletesite;
       fp1=fopen("����·��.txt","w");
    printf("**********************************************************\n");
	print();
       printf("**********************************************************\n��Ҫɾ����վ��Ϊ��");
       scanf("%d",&deletesite);system("cls");
       if(deletesite<=15&&deletesite>0)  
	   { 
		printf("**********************************************************\n");
		printf("            *          ɾ���ɹ�          *               \n");
	   } 
       if(deletesite>15||deletesite<=0)  
	   { 
		printf("**********************************************************\n");
		printf("            *          ��������          *               \n");
	   } 
       for(i=0;i<240;i++)
       {
       	if(bus[i]==deletesite)
       	bus[i]=0;//��Ҫɾ����վ���ÿա� 
	   }
	   for(i=0;i<240;i++)
       if(bus[i]!=0)
       fprintf(fp1,"%d ",bus[i]);
	   fclose(fp1);	 
}

//��һվ��վ���� �ҵ�Ҫ����վ�����һվ����ǰ��������� 
void nextsta(int bus[],int creatsite)
{
	start:
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");  
	printf("��վ����һվΪ��");
	int next;
	scanf("%d",&next);system("cls");//�ȸ�������վ�����һվ��next�ڵ㣩�� 
	if(next>15||next<0)
	{
	printf("**********************************************************\n"); 
	printf("            *          ��������          *               \n");
	goto start;
    }
    int i,j;
    for(i=0;i<240;i++)
	{
		if(bus[i]==next)//�ҵ������������һվ�� 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//����һվ֮���վ����ȫ�����ơ� 
			}
			bus[i]=creatsite;//Ҫ���ӵ�վ�㸳��i�� 
			i++;
		}
	 } 


    FILE *fp1;
    fp1=fopen("����·��.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) //ͬ��0Ϊ�գ���ԭ��·�и�վ�㽫��д���ļ��� 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);	
}
//��һվ��վ���� ԭ��ͬ�ϡ�
void frontsta(int bus[],int creatsite) 
{
	start:
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");  
	printf("��վ����һվΪ��");
    int front;
    scanf("%d",&front);system("cls");
  	if(front>15||front<0)  
	{
	printf("**********************************************************\n");
	printf("            *          ��������          *               \n");
	goto start;
    }
    int i,j;
    
    for(i=1;i<240;i++)
	{
		if(bus[i-1]==front)//�ҵ������������һվ�� 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//����һվ֮���վ����ȫ�����ơ� 
			}
			bus[i]=creatsite;//Ҫ���ӵ�վ�㸳��i�� 
			i++;
		}
	 } 
    
    
    
	FILE *fp1;
    fp1=fopen("����·��.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);
		
}
//������վ����ԭ��ͬ�ϡ� 
void betweensta(int bus[],int creatsite)
{
	start:
	printf("**********************************************************\n");
    print();
	printf("**********************************************************\n"); 
	int front,next; 
	printf("��վ����һվΪ��");
	scanf("%d",&front);
	printf("**********************************************************\n");
	printf("��վ����һվΪ��");
	scanf("%d",&next);system("cls");
	if(front>15||front<0||next>15||next<0)  
	{
	printf("**********************************************************\n");
	printf("            *          ��������          *               \n");
	goto start;
    }
    int i,j;
	
	for(i=1;i<240;i++)
	{
		if(bus[i-1]==front&&bus[i]==next)//�ҵ������������һվ����һվ�� 
		{
			for(j=239;j>=i;j--)
			{
				bus[j+1]=bus[j];//����һվ֮���վ����ȫ�����ơ� 
			}
			bus[i]=creatsite;//Ҫ���ӵ�վ�㸳��i�� 
			i++;
		}
	 } 
    
    
    
	FILE *fp1;
    fp1=fopen("����·��.txt","w");
    for(i=0;i<240;i++)
    if(bus[i]!=0&&bus[i]!=bus[i+1]) 
    fprintf(fp1,"%d ",bus[i]);
	fclose(fp1);
	
	
}

//��ȡ��վ���Ӻ����� 
void addsite()
{
	   int bus[240];
       FILE *fp1;
       fp1=fopen("����·��.txt","r");
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
	   printf("��Ҫ���ӵ�վ��Ϊ��");
       scanf("%d",&creatsite); system("cls");
       printf("**********************************************************\n\n");
       printf("            *      1  ��վ������һվ    *                \n");
       printf("            *      2  ��վ������һվ    *                \n");
       printf("            *      3 ��վ������վ֮��   *                \n");
	   printf("            *      4 �Ҳ������վ����   *                \n\n"); 
       printf("**********************************************************\n");
       printf("��ѡ��վ����뷽ʽ��");
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
	   printf("            *     ����ͼ�������˵�       *                \n");
       }
	   else goto start; 
	   
}
//����Ա��ҳ�档 
void administrator()
{ 
//UI���
	printf("**********************************************************\n\n");
	printf("            *       ����Ա�û� ���      *               \n");
	printf("            *       1  ����������·      *              \n");
	printf("            *       2  �޸�������·      *              \n");
	printf("            *       3  ɾ������վ��      *              \n");
	printf("            *       4  ���ӹ���վ��      *              \n");
	printf("            *       5   ������һ��       *              \n\n");
	printf("**********************************************************\n");;
	int cho1;
	printf("������ѡ����ţ�");scanf("%d",&cho1);system("cls");
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
	printf("            *       �������벻�Ϸ�       *               \n");
    }
    printf("            *          ���ӳɹ�          *               \n");
 }
//��·��ѯ�Ӻ��������ļ����ݵ��������������в�����Ӧλ����·ͨ����վ�㡣 
void chaxun1()
{
	   printf("**********************************************************\n");
	   printf("����Ҫ��ѯ����·�ǣ�");
	   int cxline;
	   scanf("%d",&cxline);system("cls");
	   int bus[240];
       FILE *fp1;
       fp1=fopen("����·��.txt","r");
	   int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//������Ĭ��Ϊ0�Ա������ʱ�����ַӰ��۸С� 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//���ļ�������ݵ������顣
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
	    printf("��·%dͨ������վ�㣺",cxline);
	    for(i=0;bus2[i]!=0;i++)
	    {
	    	print2(bus2[i]);
		}
		printf("\n");
		fclose(fp1);
}
//��ѯ������·���Ӻ�����������ĺ������򵥣�ֱ�Ӱ�������·���һ�顣 
void chaxun2()
{
	printf("**********************************************************\n");
	print();
	printf("**********************************************************\n");
	int bus[240];
	FILE *fp1;
	int i;
    fp1=fopen("����·��.txt","r");
    for(i=0;i<240;i++)
    bus[i]=0;
    for(i=0;i<240;i++)
    fscanf(fp1,"%d",&bus[i]);
    int m=1;
    for(i=0;i<240;i++)
    {
    	if(bus[i]==-1&&bus[i+1]!=0) 
		{
		printf("\n%d���ߣ�",m);
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

//������ʽ�Ĺ���·���ļ�ת��Ϊ��ͷ�ڵ��β�ڵ�ı���ʽ���б�� 
void hangbianbiao()
{
	
	   int bus[240];
       FILE *fp1;
       fp1=fopen("����·��.txt","r");
       int n,i,j;
       for(i=0;i<240;i++)
       bus[i]=0;//������Ĭ��Ϊ0�Ա������ʱ�����ַӰ��۸С� 
       for(i=0;i<240;i++)
       fscanf(fp1,"%d",&bus[i]);//���ļ�������ݵ������顣
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
		fp1=fopen("������.txt","w");
		
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
//����ɱ�Ĺ�����·��ѧУ��ͼ�����Աȣ��������֮���й�����������Զ��������� 
void duibi()
{
	FILE *fp01;
    fp01=fopen("���մ�ѧ�ر��.txt","r");
    FILE *fp02;
    fp02=fopen("������.txt","r");
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
	 fp03=fopen("�ر껺���.txt","w+");
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
//���й�����·�ĵ�ͼ�ٴ�Ѱ�����·��������֮���й������൱������֮���̣� 
void CreateDN2(MGraph *G) 
{
	int i,j;
	//1.���붥�����ͱ��� 

	G->vexnum=15; 

	G->arcnum=36;

	//2.���붥��Ԫ�� 
	for(i=0;i<15;i++)
	G->Vertex[i]=i+1;

	//3.�����ʼ��
	for(i=0;i<G->vexnum;i++) 
	 for(j=0;j<G->vexnum;j++)
	    {
	    	G->AdjMatrix[i][j]=MaxInt;
		}
	
	 //4.�����ڽӾ���
	 int n,m;
	 VertexType v1,v2;
	 int w;//v1->v2��Ȩֵ 
	 FILE *fp1;
	 fp1=fopen("�ر껺���.txt","r");

	 for(i=0;i<G->arcnum;i++)
	 {
	 	
	 	fscanf(fp1," %d%d%d",&v1,&v2,&w);
	 	n=LocateVex(G,v1); //��ȡv1����Ӧ����Vertex�����е����� 
	 	m=LocateVex(G,v2); //��ȡv2����Ӧ����Vertex�����е�����
	 	
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
	int dist[VertexMax];//���·���������� 
	int path[VertexMax];//���·������ 
	int s[VertexMax];//������S��1����ö����Ѵ������ڼ���S��0����ö���δ���������ڼ���S�����ڼ���V-S�� 
	
	//1.��ʼ��dist��path����                             //1079-1093�д���ûɶ�ã��ҳ�����ǰ�Լ�д���Ĵ��룬Ϊ�˱�����������о�ûɾ�� 
	loc=LocateVex(G,start);//��ȡԴ����±�λ�� 
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
    
    //2.��ʼ��S���飨s���飺������S��1�����Ԫ�����ڼ���S(�Ѵ���Ķ���)��0��Ԫ�ز����ڼ���S(δ����Ķ���)�� 
    for(i=0;i<G->vexnum;i++)
	{
		s[i]=0;
	} 
	s[loc]=1;//������ʼ��(Դ��)�Դ������ 
	num=1;
	
	while(num<G->vexnum)
	{
		min=FindMinDist(dist,s,G->vexnum);//��dist�����в������Ӧs[i]=0����δ�������СֵԪ�� 
		s[min]=1;//���ҵ�����̱�����Ӧ�ĵĶ�����뼯��S
		
		for(i=0;i<G->vexnum;i++)//�����µĶ���󣬸���dist��path���� 
		{
			if((s[i]==0)&&(dist[i]>dist[min]+G->AdjMatrix[min][i]))
			{
				dist[i]=dist[min]+G->AdjMatrix[min][i];
				path[i]=min;//min->i
			}
		}
	    num++;	
	} 
    displayPath2(dist,path,G,start,final);//չʾdist���顢path���鼰���·�� 
    
} 
//Ѱ�����·�����Ӻ����������Ѿ������� 
void displayPath2(int dist[],int path[],MGraph *G,VertexType start,VertexType final)
{
	int i,k,j=0;
	int temp[VertexMax];//��ʱ���� 
	VertexType target;//Ŀ��ص� 
	int loc=0; 
	
	for(i=0;i<VertexMax;i++)
	temp[i]=-1;
	
    printf("**********************************************************\n");
	 //���·�� 
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
				printf("ʼ����%d �յ���%d\n\t%dΪ��ʼ��!",start,G->Vertex[i],G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else if(j-1==0&&G->Vertex[temp[j-1]]!=start)
			{
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("ʼ����%d �յ���%d\n\t%d���ɴ�%d",start,G->Vertex[i],start,G->Vertex[temp[j-1]]);	 printf("\n"); 
			    }
			}
			else
			{
				if(final==0||final==i+1)
				{
				printf("\t");
				printf("ʼ����%d �յ���%d  \n",start,G->Vertex[i]);
				int clever=j-1;
				printf("\t");
				printf("������·��"); 
				for(j=j-1;j>=0;j--)
				{
					if(j!=clever)printf("->");
					printf("%d",G->Vertex[temp[j]]);
				}
				printf("(��·��ʱ��:%.2f����)",((float)dist[i])/50);	 printf("\n");
			    }
			    
			}
	    for(k=0;k<20;k++)
	    temp[k]=-1;
	}
}
//���·���� 
void zuiduanlujing2() 
{
	
	MGraph G;//д�����·����ʵ������Сʱ�䣬Ϊ���Ṥ�����õ����·����Դ�롣 
	VertexType start,final;
	
	CreateDN2(&G);
	printf("**********************************************************\n");
    print();printf("**********************************************************\n");
	printf("������ʼ�㣺"); 
	scanf(" %d",&start);
	printf("**********************************************************\n");
	printf("�����յ��㣺"); 
	scanf(" %d",&final);
    system("cls");
	ShortestPath_Dijkstra2(&G,start,final);
	
	 
}
//���·���� 
void zuiduan2()
{
	hangbianbiao();
	duibi();
	zuiduanlujing2();
 } 
//��ѯ�������м��е��Ӻ���������ȷ���м��������Ա�ȷ�����޻��ߡ� 
int hangshu()
{
	FILE *fp;
	fp=fopen("������.txt","r");
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

//�����ṹ���Դ洢����·���� 
typedef int Boolean;
typedef int VertexType1;
Boolean visit[MaxVertexNum];
typedef struct node
{
    int adjvex;//�� 
    struct node *next;//��һ���ڵ� 
}EdgeNode;

typedef struct
{
    VertexType1 vertex;
    EdgeNode *firstedge;//ͷ�ڵ� 
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];

typedef struct
{
    AdjList adjlist;
    int n,e;//���ͽڵ���� 
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
void create(ALGraph *G)			//�����ڽӱ�
{
    int i,j,k,w,v;
    EdgeNode *s;

    G->n=15;//����15���ڵ㡣 
    
	
    G->e=hangshu();//���С���ȡ���������� �� 
    for(i=0;i<G->n;i++)
    {

        
        fflush(stdin);
        G->adjlist[i].vertex=i+1;
        G->adjlist[i].firstedge=NULL;
    }
    FILE *fp2;
    fp2=fopen("������.txt","r");
    int num;
    for(k=0;k<G->e;k++)
    {
        
        fscanf(fp2,"%d%d%d",&i,&j,&num);
        i=FindVertex(G,i,G->n);
        j=FindVertex(G,j,G->n);//����������ݡ� 
        if(i==-1||j==-1)
        {
            
            
            fscanf(fp2,"%d%d%d",&i,&j,&num);
            i=FindVertex(G,i,G->n);
            j=FindVertex(G,j,G->n);//����������ݡ� 
        }
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=(j);
        s->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=s;//�ҵ���һ���ڵ㡣 
    }
    fclose(fp2); 
}
//�õ���������Ĵ��룬�ô�������жϻ��ߡ� 
void TopoSort(ALGraph *G,int n)
{
    int i,j,k,top,m=0;
    EdgeNode *p;
    int *d=(int *)malloc(n*sizeof(int));		
    for(i=0;i<n;i++)		//��ʼ������
    {
        d[i]=0;
    }
    for(i=0;i<n;i++)		//ͳ�Ƹ������������������������������������
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
    for(i=0;i<n;i++)			//���ҳ����������0�Ķ���
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
     		
        m++;		//ͳ�ƶ���
        p=G->adjlist[j].firstedge;
        while(p)
        {
            k=p->adjvex;		//�����ӵĶ���
            d[k]--;		//�����ӵĶ�����ȼ�1
            if(d[k]==0)		//����������Ϊ0���¶��㣬�Ӹö������
            {
                d[k]=top;
                top=k;
            }
            p=p->next;
        }

    }
    printf("**********************************************************\n");
    if(m<n) printf("                     У�ڹ����л��ߣ�\n");
    else printf("                       У�ڹ���û�л��ߣ�\n") ; 
    free(d);
}

//�жϻ��ߵ��Ӻ����� 
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
	  fp=fopen("�ر껺���.txt","r") ;
	  for(m=0;m<32662;m++)
	  fscanf(fp,"%d%d%d",&i,&j,&G.arc[i][j]);
	  fclose(fp);
	    return ;	  
}


void huanchengzhan()
{
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("����·��.txt","r");
	fp2=fopen("���˱�.txt","w");
	fprintf(fp2," ");
	fp2=fopen("���˱�.txt","w");
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






//��ӡÿһ��·�����Ӻ�����ÿ������һ���㣬�ͽ���������û�б������ĵ��ҵ��յ�Ϊֹ��Ȼ�󷵻����һ��ӵ���������Ͽ��Լ��������ĵ㣬��������ֱ��������б����� 
int path22(int m,int n,int k);

//�������·����������ͨ��������������ǿ���������ֹλ�ò�����path�Ӻ����������·���ı�����
//ע�⣺������������û���������������Ϊ��ֹ���·����ԭ�����ҵ�������Ϊ��һ������Ϊ�յ��ʱ����Զ�������һ�����޷������ 
int allpath22()
{	int k,i,j,m,n;
printf("**********************************************************\n");
print();
printf("**********************************************************\n");
	printf("����������Ҫ��ѯ�������ر�ı�ţ�");
	scanf("%d%d",&m,&n);
	if(m>=0&&m<=15&&n>=0&&n<=15)
	{d[0]=m;//�洢·�����m��int d[]������ȫ�ֱ����� 
	for(k=0;k<15;k++)//ȫ��������ʱ�־��ֵ��Ϊ0 
	  visited[k]=0;printf("**********************************************************\n");printf("\n");
	visited[m]=1;//��m��������ʱ�־����Ϊ1 
	path22(m,n,0);   	
    }  
	 else
	 {
	 	printf("**********************************************************\n");
	 	printf("                          ��������                        \n");
	 }                                           //���ó���k=1����Ӧ���d[1]==m��kΪd[]�����±� 
	return 1;
}




//��ӡÿһ��·�����Ӻ�����ÿ������һ���㣬�ͽ���������û�б������ĵ��ҵ��յ�Ϊֹ��Ȼ�󷵻����һ��ӵ���������Ͽ��Լ��������ĵ㣬��������ֱ��������б����� 
int path22(int m,int n,int k)
{	int s,t,time=0;                                                //t���ڴ��·������һ�������Ӧ��d[]����Ԫ�ص��±� 
	t=k+1;	
    FILE *fp;int i;
    fp=fopen("���˱�.txt","r");
	int hcb[240]={0};
	for(i=0;i<240;i++)
	{
		fscanf(fp,"%d",&hcb[i]);
	}
	int temp=0;
	if(d[k]==n&&k<16)                                                 //��d[k]���յ�n�ҵص����<=16,�������·�� 
	{	for(s=0;s<k;s++)                                             //����·������ 
	    {    	 
	    	time=time+G.arc[d[s]][d[s+1]];
		} 
		                                              //��ӡ·������С�ڶ�����·�� 
		{	for(s=0;s<k;s++)                                         //�����·����s=0ʱΪ���m 
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
			printf("��ʱ�仨��%d����,������%d�Σ�",time/50,temp);                                   //������һ���ص㣨������n����ţ���ʱs==k��	
            printf("\n\n");
		}
	} 
	else
	{	s=1;
		while(s<=15)//�ӵ�m�����㣬��̽���ж����Ƿ���·�� 
		{	if((G.arc[d[k]][s]<Infinity)&&(visited[s]==0))//����m������s�б�(Ȩֵ��Ϊ�����)����δ������ 
			{	visited[s]=1;
				d[k+1]=s;//�洢������ 
				path22(m,n,t);
				visited[s]=0;//���ҵ���·���϶���ķ��ʱ�־��������Ϊ0����������̽�µ�·�� 
			}
			s++;//��̽����һ������s��ʼ�Ƿ��е��յ��·�� 
		}
	}	
} 

//��ȡ������Ӻ������ô����Ǻܴ�Ҳ���Էֿ���ȡ�� 
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
//UI���
	printf("**********************************************************\n\n");
	printf("            *        ѧ���û� ���       *               \n");
	printf("            *       1  ��ѯ������·      *              \n");
	printf("            *       2  �滮������·      *              \n");
	printf("            *       3  �滮������·      *              \n");
	printf("            *       4  �ж�У�ڻ���      *              \n");
	printf("            *       5   ������һ��       *              \n\n");
	printf("**********************************************************\n");
    int cho1,cho2;
	printf("������ѡ����ţ�");scanf("%d",&cho1);system("cls");
	if(cho1==1)
	{
		printf("**********************************************************\n\n");
		printf("            *       1  ��ѯָ����·      *              \n");
	    printf("            *       2  ��ѯ��·�б�      *              \n");
	    printf("            *       3  ��ѯ��վ��·      *              \n\n");
	    printf("**********************************************************\n");
	     printf("������ѡ����ţ�");scanf("%d",&cho2);system("cls");
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
		printf("            *       1  ������̾���      *              \n");
	    printf("            *       2  ������̾���      *              \n");
	    printf("            *       3  ���˴�������      *              \n");
	    printf("            *       4  �������ʼ��      *              \n\n");
	    printf("**********************************************************\n");
	     printf("������ѡ����ţ�");scanf("%d",&cho2);system("cls");
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
//UI��� 
	printf("**********************************************************\n\n");
	printf("            *���ǽ��մ�ѧ��·��ѯ����ϵͳ*              \n"); 
	printf("**********************************************************\n");
	printf("           ��ע�⣬��ϵͳ��δ������ϸά��\n         �뾡������Ϸ���Χ�ڵ����ֱ�����������\n");
	chushihua();
	printf("**********************************************************\n");
	printf("            *         1  ����Ա��        *              \n"); 
	printf("            *         2   ѧ����         *              \n"); 
	printf("            *         3  �˳�����        *              \n");
	printf("            *      ���������Խ���ѡ��    *              \n\n"); 
	printf("**********************************************************\n"); 
//ѡ��ϵͳ���벿��	
	int cho1,cho2;
	printf("������ѡ����ţ�");scanf("%d",&cho1);system("cls");
	if(cho1==1)
	{
	administrator(); 
//���ز˵� 
	printf("**********************************************************\n\n");
	printf("            *  �û���� ����һ�����ز˵� *               \n");
	printf("            *       ����0�������˵�      *               \n");
	printf("            *     ���������ַ��˳�����   *               \n\n");
	printf("**********************************************************\n");
	printf("������ѡ����ţ�");scanf("%d",&cho2);system("cls");
	if(cho2==0)   goto start;
	else          exit(0);
    }
	else if(cho1==2)
	{
	student();
//���ز˵� 
	printf("**********************************************************\n\n");
	printf("            *  �û���� ����һ�����ز˵� *               \n");
	printf("            *       ����0�������˵�      *               \n");
	printf("            *     ���������ַ��˳�����   *               \n\n");
	printf("**********************************************************\n");
	printf("������ѡ����ţ�");scanf("%d",&cho2);system("cls");
	if(cho2==0)   goto start;
	else          exit(0);
    }
	else if(cho1==3)
    exit(0);
    else if(cho1==14)
	{
    printf("**********************************************************\n");
	printf("            *   Copyright infringement   *               \n");
	printf("            *   ���ߣ������   by  JSU   *               \n");
	goto start;
    } 
	else 
	{
	printf("**********************************************************\n");
	printf("            *������������  �Զ��������˵�*               \n");
	goto start;
	}
}




int main()
{
	mainmenu();
}
