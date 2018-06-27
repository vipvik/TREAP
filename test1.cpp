//#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long int $;
class node
{
    public:
    $  val;
    $  siz;
    $  pri;
    $  sum;
    $  lazy;
    $  mn;
    bool rev;
    node *left;
    node *right;
    node($  key)
    {
        val=key;
        siz=1;
        lazy=0;
        sum=key;
        pri=rand();
      //  srand(time(NULL));
        mn=key;
        rev=false;
        left=NULL;
        right=NULL;
    }
};
typedef node* pnode;
$  size(pnode tree)
{
    return (tree?tree->siz:0);
}
void update(pnode &tree)
{
   if(tree)
   {
       tree->siz=size(tree->left)+size(tree->right)+1;
   }
}
$  minimum($  a,$  b)
{
    return a>b?b:a;
}
void swap(pnode &a,pnode &b)
{
    pnode c=a;
    a=b;
    b=c;
}
void push(pnode &tree)
{
    if(tree&&tree->rev)
    {
        tree->rev=false;
        swap(tree->left,tree->right);
        if(tree->left)tree->left->rev ^= true;
        if(tree->right)tree->right->rev ^= true;
    }
}
void lazy(pnode &tree)
{
    if(!tree||!tree->lazy)return;
    tree->val+=tree->lazy;
    tree->sum+=(tree->lazy)*(size(tree));
    tree->mn+=(tree->lazy)*(size(tree));
    if(tree->left)tree->left->lazy+=tree->lazy;
    if(tree->right)tree->right->lazy+=tree->lazy;
    tree->lazy=0;
}
void reset(pnode &tree)
{
    if(tree)
    {
        tree->sum=tree->val;
        tree->mn=tree->val;
    }
}
void combine(pnode &tree,pnode l,pnode r)
{
    if(!l||!r)
    {
        tree=l?l:r;return;
    }
    tree->sum=l->sum+r->sum;
    tree->mn=minimum(l->mn,r->mn);
}
void operation(pnode &tree)
{
    if(!tree)return;
    reset(tree);
    push(tree->left);push(tree->right);lazy(tree->left);lazy(tree->right);
    combine(tree,tree->left,tree);
    combine(tree,tree,tree->right);
}
void split(pnode tree,pnode &l,pnode &r,$  key,$  lcount)
{
     push(tree); lazy(tree);
    if(!tree)
    {
        l=NULL;
        r=NULL;
    }

    else if(lcount+1+size(tree->left)==key)
    {
        l=tree;
        r=tree->right;
        tree->right=NULL;
    }
    else if(lcount+1+size(tree->left)<key)
    {
        split(tree->right,tree->right,r,key,lcount+1+size(tree->left));
        l=tree;
    }
    else
    {
       split(tree->left,l,tree->left,key,lcount);
        r=tree;
    }
    update(tree);
    operation(tree);
}

void merge(pnode &tree,pnode l,pnode r)
{
    push(l);push(r);lazy(l);lazy(r);
    if(!l||!r)
    {
        tree=l?l:r;
    }
    else if(l->pri>r->pri)
    {
        merge(l->right,l->right,r);
        tree=l;
    }
    else
    {
        merge(r->left,l,r->left);
        tree=r;
    }
    update(tree);
    operation(tree);
}


pnode root=NULL;
void insert($  key)
{
    merge(root,root,new node(key));
}
void joinfirst($  l,$  r)
{
   pnode temp1=NULL;
   pnode temp2=NULL;
   pnode temp3=NULL;
   pnode temp4=NULL;
   split(root,temp1,temp2,r,0);
   split(temp1,temp3,temp4,l-1,0);
   merge(root,temp4,temp3);
   merge(root,root,temp2);
}
void joinsecond($  l,$  r)
{
   pnode temp1=NULL;
   pnode temp2=NULL;
   pnode temp3=NULL;
   pnode temp4=NULL;
   split(root,temp1,temp2,r,0);
   split(temp1,temp3,temp4,l-1,0);
   merge(root,temp3,temp2);
   merge(root,root,temp4);
}

void inorder(pnode tree)
{
    if(tree)
    {
         push(tree);
        lazy(tree);

        inorder(tree->left);
        cout<<tree->val<<" ";
        inorder(tree->right);
    }

}
$  mini(pnode tree)
{
    if(tree->left)
    {
        return mini(tree->left);
    }
    return tree->val;
}
$  maxi(pnode tree)
{
    if(tree->right)
    {
        return maxi(tree->right);
    }
    return tree->val;
}
$  GETSUM($  l,$  r)
{
   pnode temp1=NULL;
   pnode temp2=NULL;
   pnode temp3=NULL;
   pnode temp4=NULL;
   split(root,temp1,temp2,r,0);
   split(temp1,temp3,temp4,l-1,0);
   $  sum=temp4->sum;
   merge(root,temp3,temp4);
   merge(root,root,temp2);
   return sum;
}
$  GETMIN($  l,$  r)
{
   pnode temp1=NULL;
   pnode temp2=NULL;
   pnode temp3=NULL;
   pnode temp4=NULL;
   split(root,temp1,temp2,r,0);
   split(temp1,temp3,temp4,l-1,0);
   $  mi=temp4->mn;
   merge(root,temp3,temp4);
   merge(root,root,temp2);
   return mi;
}
void UPDATE_RANGE($  l,$  r,$  diff)
{
   pnode temp1=NULL;
   pnode temp2=NULL;
   pnode temp3=NULL;
   pnode temp4=NULL;
   split(root,temp1,temp2,r,0);
   split(temp1,temp3,temp4,l-1,0);
   temp4->lazy+=diff;
   merge(root,temp3,temp4);
   merge(root,root,temp2);
}
void REVERSE_TREE(pnode tree)
{
    tree->rev ^= true;
}
void REVERSE_RANGE($  l,$  r)
{
    pnode temp1=NULL;
    pnode temp2=NULL;
    pnode temp3=NULL;
    pnode temp4=NULL;
    split(root,temp1,temp2,r,0);
    split(temp1,temp3,temp4,l-1,0);
    temp4->rev ^= true;
    merge(temp3,temp3,temp4);
    merge(root,temp3,temp2);
}
void REVOLVE($  l,$  r,$  k)
{
    $  len=r-l+1;
    k=k%len;
    pnode temp1=NULL;
    pnode temp2=NULL;
    pnode temp3=NULL;
    pnode temp4=NULL;
    pnode temp5=NULL;
    pnode temp6=NULL;
    split(root,temp1,temp2,r,0);
    split(temp1,temp3,temp4,l-1,0);
    split(temp4,temp5,temp6,len-k,0);
    merge(temp4,temp6,temp5);
    merge(root,temp3,temp4);
    merge(root,root,temp2);
}
void INSERT($  i,$  P)
{
    pnode temp1=NULL;
    pnode temp2=NULL;
    split(root,temp1,temp2,i-1,0);
    pnode temp3=new node(P);
    merge(root,temp1,temp3);
    merge(root,root,temp2);
}
void DELETE($  i)
{
    pnode temp1=NULL;
    pnode temp2=NULL;
    pnode temp3=NULL;
    pnode temp4=NULL;
    split(root,temp1,temp2,i-1,0);
    split(temp2,temp3,temp4,1,0);
    merge(root,temp1,temp4);
}
$  abs($  a){return a>0?a:-a;}
int main()
{
    $  n,m;cin>>n;
    $  ini,i;
    for(i=0;i<n;++i)
    {
        cin>>ini;
        insert(ini);
    }
   // inorder(root);cout<<endl;
    cin>>m;
    string s;
    $  x,y,D,k,P;
    while(m--)
    {
       cin>>s;
       if(s[0]=='A')
       {
          cin>>x>>y>>D;
          UPDATE_RANGE(x,y,D);
          //inorder(root);cout<<endl;
       }
       else if(s[0]=='R'&&s[3]=='E')
       {
          cin>>x>>y;
          REVERSE_RANGE(x,y);
          //inorder(root);cout<<endl;
       }
       else if(s[0]=='R'&&s[3]=='O')
       {
         cin>>x>>y>>k;
         REVOLVE(x,y,k);
        // inorder(root);cout<<endl;
       }
       else if(s[0]=='I')
       {
         cin>>x>>P;
         INSERT(x+1,P);
        // inorder(root);cout<<endl;
       }
       else if(s[0]=='D')
       {
         cin>>x;
         DELETE(x);
       //  inorder(root);cout<<endl;
       }
       else if(s[0]=='M')
       {
         cin>>x>>y;
         cout<<GETMIN(x,y)<<endl;
        // inorder(root);cout<<endl;
       }
       else if(s[0]=='S')
       {
         cin>>x>>y;
         cout<<GETSUM(x,y)<<endl;
       //  inorder(root);cout<<endl;
       }
    }


    return 0;
}
