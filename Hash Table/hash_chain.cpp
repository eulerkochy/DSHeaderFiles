#include <bits/stdc++.h>
using namespace std;

struct ht
{
	int data;
	ht *next;
};

int hf(int key, int H)
{
	return (key%H);
}

void print_hash_table(ht *hash_table[],int H)
{
	for (int i = 0; i < H; ++i)
	{
		/* code */
		cout<<i<<" :: ";

		if (hash_table[i]!=NULL)
		{
			ht *t=hash_table[i];
			while (t->next!=NULL)
			{
				cout<<t->data<<" <--> ";
				t=t->next;
			}
			cout<<t->data;
		}
		cout<<"\n";
	}
}

bool search(ht *hash_table[],int H,int key)
{
	int idx=hf(key,H);
	ht *t=hash_table[idx];
	while (t!=NULL)
	{
		if (t->data==key)
			break;
		t=t->next;
	}
	if (t==NULL)
		return false;
	else
		return true;
}

void delete_ht(ht *hash_table[],int H,int key)
{
	int idx=hf(key,H);
	ht *p=hash_table[idx],*q=NULL;
	while (p!=NULL)
	{
		if (p->data==key)
		{
			ht *tmp=p;
			p=p->next;
			if (q!=NULL)
				q->next=p;
			else
				hash_table[idx]=p;
			free(tmp);
		}
		else
		{
			q=p;
			p=p->next;
		}
	}
}

int main()
{

	srand(time(0));
	int H;
	cin>>H;

	ht *hash_table[H];

	for (int i = 0; i < H; ++i)
	{
		/* code */
		hash_table[i]=NULL;
	}

	for (int i=0;i<2*H;i++)
	{
		int key=1+rand()%100;

		ht *t=new ht();
		t->data=key;
		t->next=NULL;

		int idx=hf(key,H);

		if (hash_table[idx]==NULL)
			hash_table[idx]=t;
		else
		{
			t->next=hash_table[idx];
			hash_table[idx]=t;
		}
	}

	cout<<"Hash table (Chaining) \n";
	print_hash_table(hash_table,H);

	int x;
	cout<<"Enter a number to be searched :: ";
	cin>>x;
	if (search(hash_table,H,x))
		cout<<"Search successful\n";
	else
		cout<<"Search unsuccessful\n";

	cout<<"Enter a number to be deleted :: ";
	cin>>x;
	delete_ht(hash_table,H,x);

	cout<<"Hash Table after the delete operation\n";
	print_hash_table(hash_table,H);


}