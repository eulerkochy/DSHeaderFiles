#include <bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	char color;	   // 'r' for red and 'b' for black
	struct node *l,*r,*p; //left, right, parent

	node (int data){
		this->data=data;
		this->l=this->r=this->p=NULL;
	}
};

class RBT
{
private:
	node *root;
protected:
	void left_rotate(node *&root, node *&x);
	void right_rotate(node *&root,node *&x);
	void fix_violation(node *&root,node *&x);	
public:
	RBT(){
		root=NULL;
	}
	void inorder();
	void levelorder();
	void insert(int n);
	void search(int n);
};

node *BSTinsert(node *root,node *t)
{
	if (root==NULL)
		return t;

	if (root->data < t->data)
	{
		root->r=BSTinsert(root->r,t);
		root->r->p=root;
	}

	else if (root->data > t->data)
	{
		root->l=BSTinsert(root->l,t);
		root->l->p=root;
	}

	return root;
}

void _inorder(node *root)
{
	if (root==NULL)
		return;
	_inorder(root->l);
	cout<<root->data<<" ";
	_inorder(root->r);
}

void RBT::left_rotate(node *&root, node *&x)
{
	node *y=x->r;
	x->r=y->l;
	y->l->p=x;
	y->p=x->p;
	if (x->p==NULL)
		root=y;
	else
	{
		if (x==x->p->l)
		{
			x->p->l=y;
		}
		else
		{
			x->p->r=y;
		}
	}
	x->p=y;
	y->l=x;
}

void RBT::right_rotate(node *&root, node *&x)
{
	node *y=x->l;
	x->l=y->r;
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
	x->p=y;
	y->r=x;
}

void RBT::fix_violation(node *&root,node *&t)
{
	node *parent=NULL;
	node *g_parent=NULL;
	while ((t!=root)&&(t->p->color=='r')&&(t->color=='r'))
	{
		parent=t->p;
		g_parent=parent->p;
		if (parent==g_parent->l)
		{
			//case 1: uncle is red
			node *uncle=g_parent->r;
			if (uncle!=NULL && uncle->color=='r')
			{
				g_parent->color='r';
				uncle->color='b';
				parent->color='b';
				t=g_parent;
			}
			else
			{
				if (t==parent->r)
				{
					left_rotate(root,parent);
					t=parent;
					parent=t->p;
				}
				right_rotate(root,g_parent);
				swap(parent->color,g_parent->color);
				t=parent;
			}
		}
		else
		{
			node *uncle=g_parent->l;
			if (uncle!=NULL && uncle->color=='r')
			{
				g_parent->color='r';
				uncle->color='b';
				parent->color='b';
				t=g_parent;
			}
			else
			{
				if (t==parent->l)
				{
					right_rotate(root,parent);
					t=parent;
					parent=t->p;
				}
				left_rotate(root,g_parent);
				swap(parent->color,g_parent->color);
				t=parent;
			}
		}
	}
}


void RBT::insert(int n)
{
	node *t=new node(n);
	root=BSTinsert(root,t);
	fix_violation(root,t);
}

void RBT::inorder()
{
	_inorder(root);
	cout<<"\n";
}

void RBT::levelorder()
{
	if (root==NULL)
		return;
	queue<node *> q;
	q.push(root);
	while (!q.empty())
	{
		node *x=q.front();
		cout<<x->data<<" ";
		q.pop();
		if (x->l!=NULL)
			q.push(x->l);
		if (x->r!=NULL)
			q.push(x->r);
	}
	cout<<"\n";
}

void RBT::search(int n)
{
	if (root==NULL)
	{	
		cout<<"RB Tree is empty\n";
		return;
	}
	node *t=root;
	bool found=false;

	while (t!=NULL)
	{
		if(t->data < n)
			t=t->r;
		else if (t->data > n)
			t=t->l;
		else
		{
			found=true;
			break;
		}
	}		
	if (found)
		cout<<n<<" is in the RB Tree\n";
	else
		cout<<n<<" is not in the RB Tree\n";
}

int main()
{
	srand(time(0));
	RBT tree;
	cout<<"Enter the number of nodes ::";
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		tree.insert(1+rand()%100);
	}
	cout << "Inoder Traversal of Created Tree\n";
	tree.inorder();

	cout<<"LevelOrder Traversal of the created tree\n ";
	tree.levelorder();

	cout<<"Enter a number to be searched :: ";
	cin>>n;
	tree.search(n);
	return 0;
}