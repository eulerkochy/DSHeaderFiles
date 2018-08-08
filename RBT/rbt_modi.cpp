#include <bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	char color;
	node *l,*r,*p;
};

node *newNode(int n)
{
	node *t=new node();
	t->data=n;
	t->l=t->r=t->p=NULL;
	return t;
}

node *insert(node *root,node *t)
{
	if (root==NULL)
		return t;

	if (root->data < t->data)
	{
		root->r=insert(root->r,t);
		root->r->p=root;
	}
	else 
	{
		root->l=insert(root->l,t);
		root->l->p=root;
	}
	return root;	
}

void left_rotate(node *&root,node *&x)
{
	node *y=x->r;
	x->r=y->l;
	if (y->l!=NULL)
		y->l->p=x;
	y->p=x->p;
	if (x->p==NULL)
		root=y;
	else
	{
		if (x==x->p->l)
			x->p->l=y;
		else
			x->p->r=y;
	}
	y->l=x;
	x->p=y;
}

void right_rotate(node *&root, node *&x)
{
	node *y=x->l;
	x->l=y->r;
	if (y->r!=NULL)
		y->r->p=x;
	y->p=x->p;
	if (x->p==NULL)
		root=y;
	else
	{
		if (x==x->p->l)
			x->p->l=y;
		else
			x->p->r=y;
	}
	y->r=x;
	x->p=y;
}

void fix_violation(node *&root,node *&x)
{
	node *parent=NULL;
	node *g_parent=NULL;
	while ((x!=root)&&(x->p->color=='r')&&(x->color=='r'))
	{
		parent=x->p;
		g_parent=parent->p;

		if (parent==g_parent->l)
		{
			node *uncle=g_parent->r;
			if (uncle->color=='r')
			{
				uncle->color=parent->color='b';
				g_parent->color='r';
				x=g_parent;
			}
			else
			{
				if (x==parent->r)
				{
					left_rotate(root,parent);
					x=parent;
					parent=x->p;
				}
				right_rotate(root,g_parent);
				swap(parent->color,g_parent->color);
				x=parent;
			}
		}
		else
		{
			node *uncle=g_parent->l;
			if (uncle->color=='r')
			{
				uncle->color=parent->color='b';
				g_parent->color='r';
				x=g_parent;
			}
			else
			{
				if (x==parent->l)
				{
					right_rotate(root,parent);
					x=parent;
					parent=x->p;
				}
				left_rotate(root,g_parent);
				swap(parent->color,g_parent->color);
				x=parent;
			}
		}
	}
}

void rb_insert(node *&root,int n)
{
	node *t=newNode(n);
	root=insert(root,t);
	fix_violation(root,t);
}

void inorder(node *root)
{
	if (root==NULL)
		return;
	inorder(root->l);
	cout<<root->data<<" ";
	inorder(root->r);

}

int main(int argc, char const *argv[])
{
	srand(time(0));
	node *root=NULL;
	cout<<"Enter the number of nodes ::";
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		rb_insert(root,1+rand()%100);
	}
	cout << "Inoder Traversal of Created Tree\n";
	inorder(root);
	cout<<"\n";
	return 0;
}