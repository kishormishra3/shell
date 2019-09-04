#include<iostream>
using namespace std;
typedef struct trie
{
	trie *child[26];
	bool isEnd;
	trie()
	{
		for(int i=0;i<26;i++)
		{
			child[i]=NULL;
		}
		isEnd=false;
	}
}trie;
void insert(trie *root,string key)
{
	trie *curr=root;
	for(int i=0;i<key.length();i++)
	{
		if(curr->child[key[i]]==NULL)
		curr->child[key[i]]=new trie();
		curr=crr->child[key[i]];
	}
	curr->isEnd=true;
}
int main()
{
	
