#include<iostream>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include<stdio.h> 
#include <windows.h>

#define MAX 10000
#define INF 10000000 
#define E 0.000000001  // ������� 
#define L 20000    // �������� 
#define AT 0.999   // ����ϵ�� 
#define T 1       // ��ʼ�¶� 
using namespace std; 

struct element{     //������������ݽṹ 
	int data;  // ���� 
	int index;  // ��� 
};

int tsp(int d[][MAX], int n, double e,int l,double at,double t,int s0[]);  //����ģ���˻��㷨������·�� 
int cmp(const void *a,const void *b); //�������� 
void rand_of_n(int a[],int n);  //���� 1-n ��������в��浽 a[] ��
int random(int m,int n);
int dis[MAX][MAX];   // d[i][j] ��ʾ�ͻ�i���ͻ�j�ľ��룬0 ��ʾ��ʼ�� 

void rand_of_n(int a[],int n){
	int i;
	struct element ele[MAX];
	srand((int)time(0));  // ��ʼ����������� 
	for(i=0;i<n;i++){
		ele[i].data=rand();  // �������һ���� 
		ele[i].index=i+1;
	}
	qsort(ele,n,sizeof(ele[0]),cmp);  //���� 
	for(i=0;i<n;i++){
		a[i]=ele[i].index;
	}
}

int random(int m,int n){   //����m-n�������
	int a;
	double x=(double)rand()/RAND_MAX;
	a=(int)(x*(n-m)+0.5)+m;
	return a;
}	

int cmp(const void *a,const void *b){   // ��������
	return((struct element*)a)->data - ((struct element*)b)->data;
}


int tsp(int d[][MAX], int n, double e,int l,double at,double t,int s0[]){
	int i,j,s[MAX],sum,temp;
	sum=INF; 
	for(i=0;i<1000;i++){  //�������ؿ��巽��������ʼ��
		rand_of_n(&s[1],n);
		s[0]=0; s[n+1]=0;  //��һ�������һ����Ϊ��ʼ�� 
		temp=0;
		for(j=0;j<=n;j++)
			temp=temp+d[s[j]][s[j+1]];
		if(temp<sum){
			for(j=0;j<=n+1;j++)
				s0[j]=s[j];
			sum=temp;
		} 
	}
	
	for(i=0;i<l;i++){    //�˻���� 
		int c1,c2;
		c1=random(1,n);
		c2=random(1,n);
		if(c1>c2){
			int temp=c2; c2=c1; c1=temp;
		} 
		if(c1==c2)
			continue;
		int df=d[s0[c1-1]][s0[c2]] + d[s0[c1]][s0[c2+1]] - d[s0[c1-1]][s0[c1]] - d[s0[c2]][s0[c2+1]]; //������ۺ���
		if(df<0){  //����׼��
			while(c1<c2){ 
				int temp=s0[c2]; s0[c2]=s0[c1]; s0[c1]=temp;
				c1++;
				c2--;
			}
			
			sum=sum+df;
		} 
		else if(exp(-df/t)>((double)rand()/RAND_MAX)){
			while(c1<c2){
				int temp=s0[c2]; s0[c2]=s0[c1]; s0[c1]=temp;
				c1++;
				c2--;
			}

			sum=sum+df;
		}
		t=t*at;
		if(t<e)
			break;
	}
	return sum;
}



int main(){
    DWORD start, stop;
    int i,j;
	int n; 
	cout<<"����ģʽ�������� Ȼ������س�,���� 10 �س�"<<endl;
    cin>>n;
	start = GetTickCount();//����ʼʱ��  
	for(i=0;i<n;i++)     // ����������� 1-100
		for(j=i;j<n;j++)
			if(i==j)
				dis[i][j]=0;
			else
				dis[i][j]=dis[j][i]=random(1,100); 
	FILE*fp = fopen("ģ���˻��㷨-�����������.txt","w");  // ����������ļ��� 
	for(i=0;i<n;i++){  
		for(j=0;j<n;j++)
			fprintf(fp,"%d ",dis[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp); 
	int sum,sum0,s0[MAX]; 
	sum0=0;   //˳�����ʱ��·�� 
	for(i=0;i<n;i++)
		sum0=sum0+dis[i][i+1];
	sum0=sum0+dis[n][0];
	sum=tsp(dis,n, E,L,AT,T,s0);
	fp = fopen("ģ���˻��㷨-�������.txt","w");  //����������ļ���
	for(i=1;i<=n;i++)
		fprintf(fp,"%d ",s0[i]);
	fclose(fp); 

	cout<<endl; 	
	cout<<"Ϊ�˷���鿴�����ݺͽ���������ļ���"<<endl; 	
	cout<<"<<<<�ڽӾ��󱣴����ļ� ģ���˻��㷨-�����������.txt ��"<<endl<<"<<<<����˳�򱣴����ļ� ģ���˻��㷨-�������.txt ��"<<endl; 
	cout<<endl;
	
	printf("ģ��ڵ���� %d\n", n);
	stop = GetTickCount();//�������ʱ�� 
    printf("����ʱ��: %lld ms\n", stop - start);
    
    system("pause");
	return 0; 
}

