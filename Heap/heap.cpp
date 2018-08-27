#include<bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1000

int lchild(int i)
{
	return 2*i;
}

int rchild(int i)
{
	return 2*i+1;
}

int parent(int i)
{
	return (i/2);
}

void insert(int h[],int &n,int x)//heapify UP
{
	h[++n]=x;
	int i=n;
	while(i>1 && h[parent(i)]<h[i])  
	{
		swap(h[parent(i)],h[i]);
		i=parent(i);
	}	
}

int findmax(int h[])
{
	return h[1];
}

void heapify_down(int h[],int n,int i)
{
	int l=lchild(i),r=rchild(i),mi=i;
	if (l<=n && h[l]>h[mi])
		mi=l;
	if (r<=n && h[r]>h[mi])
		mi=r;
	
	if (mi!=i)
	{
		swap(h[i],h[mi]);
		heapify_down(h,n,mi);
	}
}

void extractmax(int h[],int &n)
{
	h[1]=h[n--];
	heapify_down(h,n,1);
}

void printarr(int h[],int n)
{
	for (int i=1;i<=n;i++)
		cout<<h[i]<<" ";
	cout<<"\n";
}

void buildmaxheap(int A[],int n)
{
	for (int i=n/2;i>0;i--)
	{
		heapify_down(A,n,i);
	}
}

void heapsort(int A[],int n)
{
	for (int i=n-1;i>0;i--)
	{
		swap(A[1],A[i+1]);
		heapify_down(A,i,1);
	}
}

int main()
{
	srand(time(0));
	int h[MAX_SIZE];
	int n,x,size=0;
	cin>>n;
	int A[n+1];
	cout<<"UNHEAPED NUMBERS\n";
	for (int i=0;i<n;i++)
	{
		x=1+rand()%100;
		A[i+1]=x;
		cout<<x<<" ";
		insert(h,size,x);
	}
	cout<<"\n";
	
	cout<<"HEAPED NUMBERS\n";
	printarr(h,size);
	
	cout<<"MAX HEAP\n";
	buildmaxheap(A,n);
	printarr(A,n);
	
	
	cout<<"THE NUMBERS IN DECREASING ORDER\n";
	for (int i=n;i>0;i--)
	{
		cout<<findmax(h)<<" ";
		extractmax(h,size); 
	}
	cout<<"\n";
	
	heapsort(A,n);
	cout<<"THE NUMBERS IN INCREASING ORDER\n";
	printarr(A,n);
	
}



