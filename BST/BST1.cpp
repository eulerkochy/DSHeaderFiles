#include <bits/stdc++.h>
using namespace std;
typedef uintptr_t un;

struct node{
	int data;
	node *left,*right,*parent;
};

node *newNode(int data)
{
	node *t=new node();
	t->data=data;
	t->left=t->right=t->parent=NULL;
	return t;
}

node *insert(node *curr,int data)
{
	if (curr==NULL)
		return newNode(data);
	if (curr->data < data) // right contains <
	{
		curr->right=insert(curr->right,data);
		curr->right->parent=curr;
	}
	else // left contains >=
	{
		curr->left=insert(curr->left,data);
		curr->left->parent=curr;
	} 
		
	return (curr);
}

void inorder(node *t)
{
	if (t==NULL)
		return;
	inorder(t->left);
	cout<<t->data<<" ";
	inorder(t->right);
}

void iter_inorder(node *root)
{
	stack<node *> s;
	node *curr=root;
	while (curr!=NULL || !s.empty())
	{
		while (curr!=NULL)
		{
			s.push(curr);
			curr=curr->left;
		}
		curr=s.top();
		cout<<curr->data<<" ";
		s.pop();
		curr=curr->right;
	}
}

void preorder(node *t)
{
	if (t==NULL)
		return;
	cout<<t->data<<" ";
	preorder(t->left);
	preorder(t->right);
}

void iter_postorder(node *t)
{
	stack<node *> s;
	node *curr=t;
	while (curr->left!=NULL || curr->right!=NULL || !s.empty())
	{
		while (curr->left!=NULL)
		{
			s.push(curr->left);
			curr=curr->left;
		}
		curr=s.top();
		while (curr->right!=NULL)
		{
			s.push(curr->right);
			curr=curr->right;
		}
		curr=s.top();
		cout<<curr->data<<" ";
		s.pop();
	}
}

void postorder(node *t)
{
	if (t==NULL)
		return;
	postorder(t->left);
	postorder(t->right);
	cout<<t->data<<" ";
}

void inorder2(node *t)
{
	if (t==NULL)
		return;
	inorder2(t->right);
	cout<<t->data<<" ";
	inorder2(t->left);
}

void level_order(node *t)
{
	queue<node *> q;
	if (t!=NULL)
		q.push(t);
	while (!q.empty())
	{
		node *tmp=q.front();
		cout<<tmp->data<<" ";
		if (tmp->left!=NULL)
			q.push(tmp->left);
		if (tmp->right!=NULL)
			q.push(tmp->right);
		q.pop();
	}
	cout<<endl;	
}

int findmax(node *t)
{
	if (t->right==NULL)
		return t->data;
	return findmax(t->right);
}

int findmin(node *t)
{
	if (t->left==NULL)
		return t->data;
	return findmin(t->left);
}

bool search(node *t,int x)
{
	while (t!=NULL)
	{
		if (t->data > x)
			t=t->left;
		else if (t->data < x)
			t=t->right;
		else
			return true;
	}
	return false;
}

node *_search(node *t,int x) // returns the node with value x
{
	if (t->data==x)
		return t;
	if (t==NULL)
		return NULL;
	if (t->data < x)
		return _search(t->right,x);
	else
		return _search(t->left,x);	
}

int no_of_leaf(node *t)
{	
	if (t==NULL)
		return 0;
	if (t->left==NULL && t->right==NULL)
		return 1;
	return no_of_leaf(t->left)+no_of_leaf(t->right);
}

node *findminnode(node *t)
{
	node *curr=t;
	while (curr->left!=NULL)
		curr=curr->left;
	return curr;
}

node *findmaxnode(node *t)
{
	node *curr=t;
	while (curr->right!=NULL)
		curr=curr->right;
	return curr;
}

node *tree_successor(node *x)
{
	if (x->right!=NULL)
	{
		return findminnode(x->right);
	}
	else
	{
		node *y=x->parent;
		while (y!=NULL && x==y->right)
		{
			x=y;
			y=y->parent;
		}
		return y;
	}
}

node *tree_predecessor(node *x)
{
	if (x->left!=NULL)
	{
		return findmaxnode(x->left);
	}
	else
	{
		node *y=x->parent;
		while (y!=NULL && x==y->left)
		{
			x=y;
			y=y->parent;
		}
		return y;
	}
}
/*
The Cormen way

void delete_node(node *root,node *z)
{
	node *y,*x;
	if (z->left==NULL || z->right==NULL)
		y=z;
	else 
		y=tree_successor(z);
	if (y->left!=NULL)
		x=y->left;
	else
		x=y->right;
	if (x!=NULL)
		x->parent=y->parent;
	if (y->parent==NULL)
		root=x;
	else if (y==y->parent->left)
		y->parent->left=x;
	else
		y->parent->right=x;
	if (y!=z)
	{
		z->data=y->data;
	}
	free(y);
}*/

void morris_traversal(node *root)
{
	node *curr=root;
	while (curr!=NULL)
	{
		if (curr->left==NULL)
		{
			cout<<curr->data<<" ";
			curr=curr->right;
		}
		else
		{
			node *pre;
			pre = curr->left;
      		while (pre->right != NULL && pre->right != curr)
        		pre = pre->right;
			if (pre->right==NULL)
			{
				pre->right=curr;
				curr=curr->left;
			}
			else
			{
				pre->right=NULL;
				cout<<curr->data<<" ";
				curr=curr->right;
			}
		}
	}
	cout<<endl;
}

node *delete_node(node *root, int key)
{
	if (root==NULL)
		return root;

	if (key < root->data)
		root->left=delete_node(root->left,key);
	else if (key > root->data)
		root->right=delete_node(root->right,key);
	else
	{
		//Case 1: No children
		if (root->left==NULL && root->right==NULL)
		{
			free(root);
			root=NULL;
		}

		//Case 2: One children
		else if (root->left==NULL)
		{
			node *temp=root;
			root=root->right;
			free(temp);
		}
		else if (root->right==NULL)
		{
			node *temp=root;
			root=root->left;
			free(temp);
		}

		// Case 3: Two children -->There are two approaches. I'll describe these as I write.
		else
		{
			//Approach 1: Finding the maximum of the left subtree
			node *temp=findmaxnode(root->left);
			root->data=temp->data;
			root->left=delete_node(root->left,temp->data); 

			//Approach 2: Finding the minimum of the right subtree
			/*
			node *temp=findminnode(root->right);
			root->data=temp->data;
			root->right=delete_node(root->right,temp->data);
			*/
		}
	}
	return root;
}

int main()
{
	srand(time(0));
	node *root=NULL;
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		root=insert(root,-50+rand()%101);
	}
	cout<<"Increasing order\n";
	inorder(root);
	cout<<endl;
	cout<<"Inorder traversal using stacks :\n";
	iter_inorder(root);
	cout<<endl;
	cout<<"Decreasing order\n";
	inorder2(root);
	cout<<endl;
	cout<<"Preorder\n";
	preorder(root);
	cout<<endl;
	cout<<"Postorder\n";
	postorder(root);
	cout<<endl;
	cout<<"Levelorder\n";
	level_order(root);
	cout<<"Morris Inorder Traversal\n";
	morris_traversal(root);
	cout<<"Max: "<<findmax(root)<<endl;
	cout<<"Min: "<<findmin(root)<<endl;
	cout<<"No. of leave nodes : "<<no_of_leaf(root)<<endl;

	int y;
	cout<<"Enter a value to be searched :: ";
	cin>>y;
	if (search(root,y))
		cout<<y<<" is in BST\n";
	else
		cout<<y<<" is not in BST\n";
	
	cout<<"Enter a value in BST :: ";
	int x;
	cin>>x;

	if (x==findmax(root))
		cout<<x<<" is the maximum. There is no successor!"<<endl;
	else
		cout<<"Successor of "<<x<<" is "<<tree_successor(_search(root,x))->data<<endl;
	
	if (x==findmin(root))
		cout<<x<<" is the minimum. There is no predecessor!"<<endl;
	else
		cout<<"Predecessor of "<<x<<" is "<<tree_predecessor(_search(root,x))->data<<endl;

	cout<<"Enter a value to deleted in BST :: ";
	cin>>x;
	delete_node(root,x);
	cout<<"BST after deletion"<<endl;
	iter_inorder(root);
	cout<<endl;

}
