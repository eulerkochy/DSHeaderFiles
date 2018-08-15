#include <bits/stdc++.h>
using namespace std;


int hf(int x,int H)
{
	return (x%H);
}

void search1(int ht1[],int key,int H)
{
	cout<<"Searching in hash table 1\n";
	int idx=hf(key,H);
	time_t start=clock();
	int count=0;
	while (ht1[idx]!=key || ht1[idx]==-2)
	{
		idx=(idx+1)%H;
		count++;
		if (count==H)
			break;
	}
	if (count==H)
		cout<<"Search Unsucessful!\n";
	else
		cout<<"Search successful\n";
	time_t end=clock();
	cout<<"The time taken is "<<(-start+end)/double(CLOCKS_PER_SEC/1000)<<"ms \n";
}

bool _search1(int ht1[],int key,int H)
{
	int idx=hf(key,H);
	int count=0;
	while (ht1[idx]!=key || ht1[idx]==-2)
	{
		idx=(idx+1)%H;
		count++;
		if (count==H)
			{
				break;
			}
	}
	if (count==H)
		return false;
	else
		return true;
}

void search2(int ht2[],int key,int H)
{
	cout<<"Searching in hash table 2\n";
	int idx=hf(key,H);
	time_t start=clock();
	int count=0;
	while (ht2[idx]!=key || ht2[idx]==-2)
	{
		count++;
		idx=(idx+(count)*(count))%H;
		
		if (count==H)
			break;
	}
	if (count==H)
		cout<<"Search Unsucessful!\n";
	else
		cout<<"Search successful\n";
	time_t end=clock();
	cout<<"The time taken is "<<(-start+end)/double(CLOCKS_PER_SEC/1000)<<"ms \n";
}

bool _search2(int ht2[],int key,int H)
{
	int idx=hf(key,H);
	int count=0;
	while (ht2[idx]!=key || ht2[idx]==-2)
	{
		count++;
		idx=(idx+(count)*(count))%H;
		
		if (count==H)
			break;
	}
	if (count==H)
		return false;
	else
		return true;
}

void delete1(int ht1[],int key,int H)
{
	if (_search1(ht1,key,H))
	{
		int idx=hf(key,H);
		while (ht1[idx]!=key)
		{
			idx=(idx+1)%H;
		}
		ht1[idx]=-2;
	}
	else
		cout<<key<<" doesn't exist in the hash table\n";
}

void delete2(int ht2[],int key,int H)
{
	if (_search2(ht2,key,H))
	{
		int idx=hf(key,H);
		int c=0;
		while (ht2[idx]!=key)
		{
			c++;
			idx=(idx+c*c)%H;
		}
		ht2[idx]=-2;
	}
	else
		cout<<key<<" doesn't exist in the hash table\n";
}


int main(int argc, char const *argv[])
{
	srand(time(0));
	int H;
	cin>>H; // size of hash table

	int ht1[H];//uses linear probing
	int ht2[H];//uses quadratic probing
	
	for (int i = 0; i < H; ++i)
	{
		ht1[i]=-1;
		ht2[i]=-1;
	}
	int c1=0,c2=0;
	for (int i = 0; i < H/2; ++i)
	{
		/* code */
		int key=1+rand()%100;
		cout<<key<<" ";

		//linear probing
		int idx=hf(key,H);
		int c=0;
		while (ht1[idx]!=-1)
			{
				idx=(idx+1)%H;
				c++;
			}
		c1+=c;
		cout<<"--"<<c;
		ht1[idx]=key;

		//quadratic probing 
		idx=hf(key,H);
		c=0;
		while (ht2[idx]!=-1)
		{
			c++;
			idx=(idx+(c*c))%H;
		}
		ht2[idx]=key;
		cout<<"--"<<c;
		c2+=c;
		cout<<"\n";
	}
	cout<<"\n";
	double val1=(1.0*c1)/H,val2=(1.0*c2)/H;

	cout<<"Linear probing avg collision :: "<<val1<<"\n";
	cout<<"Quadratic probing avg collision :: "<<val2<<"\n";

	cout<<"Hash table 1\n";
	for (int i = 0; i < H; ++i)
	{
		/* code */
		cout<<ht1[i]<<" ";
	}
	cout<<"\n";

	cout<<"Hash table 2\n";
	for (int i = 0; i < H; ++i)
	{
		/* code */
		cout<<ht2[i]<<" ";
	}
	cout<<"\n";

	int key;
	cout<<"Enter a number to be searched :: ";
	cin>>key;

	cout<<"\n";
	search1(ht1,key,H);

	cout<<"\n";
	search2(ht2,key,H);

	cout<<"Enter a number to be deleted :: ";
	cin>>key;
	//Assume key is in the hash table
	delete1(ht1,key,H);
	delete2(ht2,key,H);

	cout<<"Enter a number to be searched :: ";
	cin>>key;

	cout<<"\n";
	search1(ht1,key,H);

	cout<<"\n";
	search2(ht2,key,H);

	return 0;
}