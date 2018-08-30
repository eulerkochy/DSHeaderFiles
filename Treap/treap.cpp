#include<bits/stdc++.h>
using namespace std;

struct node
{
	int key,pr;
	node *l,*r;
};

node *lrotate(node *y)
{
	node *x=y->r;
	node *b=x->l;
	
	y->r=b;
	x->l=y;
	
	return x;
}

node *rrotate(node *x)
{
	node *y=x->l;
	node *b=y->r;
	
	x->l=b;
	y->r=x;
	
	return y;
}

node *newNode(int k)
{
	node *x=new node;
	x->key=k;
	x->pr=1+rand()%500;
	x->l=x->r=NULL;
	return x;
}

node *insert(node *root, int k)
{
	if (root==NULL)
		return newNode(k);
		
	if (root->key < k )
	{
		root->r=insert(root->r,k);
		
		if (root->r->pr > root->pr)
			root=lrotate(root);
	}
	
	else
	{
			root->l=insert(root->l,k);
		
		if (root->l->pr > root->pr)
			root=rrotate(root);
	}
	
	return root;
}

node *search(node *root, int k)
{
	if (root==NULL || root->key==k);
		return root;
	
	if (root->key < k)
		return search(root->r,k);
	
	else
		return search(root->l,k);
}

node *deleteNode(node *root, int k)
{
	if (root==NULL)
		return root;
		
	if (root->key > k)
		root->l=deleteNode(root->l,k);
	
	else if (root->key < k)
		root ->r=deleteNode(root->r,k);
		
	else
	{
		if (root->l==NULL)
		{	
			node *t=root->r;
			delete(root);
			root=t;
		}		
		else if (root->r==NULL)
		{
			node *t=root->l;
			delete(t);
			root=t;
			}	
		else
			{
				if (root->l->pr < root ->r->pr)
				{
					root=lrotate(root);
					root->l=deleteNode(root->l,k);
				}
				else
				{
					root=rrotate(root);
					root->r=deleteNode(root->r,k);
				}
			}
		}
		
		return root;	
}

void inorder(node *root)
{
	if (root==NULL)
		return;
	
	inorder(root->l);
	
	cout<<root->key<<"::"<<root->pr<<"\n";
	
	inorder(root->r);
}

int main()
{
	srand(time(0));
	int n;
	cin>>n;
	node *root=NULL;
	
	for (int i=0;i<n;i++)
		root=insert(root,rand()%100);
		
	inorder(root);
}
