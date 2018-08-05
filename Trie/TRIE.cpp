#include <bits/stdc++.h>
using namespace std;

struct trie
{
	trie *child[26];
	bool eow;
};

trie *newNode()
{
	trie *t=new trie();
	for (int i=0;i<26;i++)
	{
		t->child[i]=NULL;
	}
	t->eow=false;
	return t;
}

trie *insert(trie *root, string x)
{
	trie *t=root;
	for (int i=0;i<x.length();i++)
	{
		if (t->child[x[i]-'a']==NULL)
			t->child[x[i]-'a']=newNode();
		t=t->child[x[i]-'a'];
	}
	t->eow=true;
	return root;
}

bool search(trie *root,string x)
{
	trie *t=root;
	for (int i=0;i<x.length();i++)
	{
		int id=x[i]-'a';
		if (t->child[id]==NULL)
			return false;
		else
		{
			t=t->child[id];
		}
	}
	return t->eow;
}

void traverse(trie *root, string &s)
{
	if (root->eow)
		{
			cout<<s<<"\n";
			return;
		}

	for (int i=0;i<26;i++)
	{
		if (root->child[i]!=NULL)
		{
			s.push_back('a'+i);
			traverse(root->child[i],s);
			s.pop_back();
		}
	}
}

void hasPrefix(trie *root, string s)
{
	trie *t=root;
	for (int i=0;i<s.length();i++)
	{
		int id=s[i]-'a';
		if (t->child[id]==NULL)
		{
			cout<<s<<" is not a prefix in any of the strings\n";
			return;
		}
		t=t->child[id];
	}
	string tmp=s;
	traverse(t,tmp);
}

int main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter the number of words :: ";
	cin>>n;
	string s;
	trie *root=newNode();
	cout<<"\nEnter the words\n";
	for (int i=0;i<n;i++)
	{
		cin>>s;
		root=insert(root,s);
	}
	
	cout<<"\nWords in lexographic order\n";
	string tmp="";
	traverse(root,tmp);

	cout<<"\nEnter the string to be searched :: ";
	cin>>s;
	if (search(root,s))
		cout<<"\nPresent\n";
	else
		cout<<"\nAbsent\n";

	cout<<"\nEnter a prefix to be queried for :: ";
	cin>>s;
	hasPrefix(root,s);
	cout<<"\n";


	return 0;
}