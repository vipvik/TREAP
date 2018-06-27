#include <iostream>

//#include <cstdio>

using namespace std;
typedef long long int $ ;
struct node
{
    public:
    $    val;
    $    siz;
    $    pri;
    $    max_sum;
    $    total_sum;
    $    pref_sum;
    $    suff_sum;
    node *left;
    node *right;
    node($    key)
    {
        val=key;
        siz=1;
        pri=rand();
        max_sum=key;
        total_sum=key;
        pref_sum=key;
        suff_sum=key;
        left=NULL;
        right=NULL;
    }
};
typedef node* pnode;
$    size(pnode tree)
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
$    maxi($    a,$    b)
{
    return a<b?b:a;
}
$  maximum($  a,$  b,$  c)
{
    return(maxi(maxi(a,b),c));
}

void reset(pnode &tree)
{
    if(tree)
    {
        tree->max_sum=tree->val;
        tree->total_sum=tree->val;
        tree->pref_sum=tree->val;
        tree->suff_sum=tree->val;
    }
}
void combine(pnode &tree,pnode l,pnode r)
{
if(!l||!r)
    {
        tree=l?l:r;return;
    }
    tree->max_sum=maximum(l->max_sum,r->max_sum,(l->suff_sum+r->pref_sum));

    tree->total_sum=(l->total_sum+r->total_sum);

    tree->pref_sum=maximum(l->pref_sum,l->total_sum,l->total_sum+r->pref_sum);

    tree->suff_sum=maximum(r->suff_sum,r->total_sum,r->total_sum+l->suff_sum);

}
void operation(pnode &tree)
{
    if(!tree)return;
    reset(tree);

     combine(tree,tree->left,tree);
    combine(tree,tree,tree->right);

}
void split(pnode tree,pnode &l,pnode &r,$    key,$    lcount)
{

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

void insert($  x)
{
    merge(root,root,new node(x));
}
$  MAX_SUM($  x,$  y)
{
    pnode temp1=NULL;
    pnode temp2=NULL;
    pnode temp3=NULL;
    pnode temp4=NULL;
    split(root,temp1,temp2,y,0);
    split(temp1,temp3,temp4,x-1,0);
    $  ma=temp4->max_sum;
    merge(root,temp3,temp4);
    merge(root,root,temp2);
    return ma;
}
void UPDATE(int x,int y)
{
    pnode temp1=NULL;
    pnode temp2=NULL;
    pnode temp3=NULL;
    pnode temp4=NULL;
    split(root,temp1,temp2,x-1,0);
    split(temp2,temp3,temp4,1,0);
    temp3->val=y;
    merge(root,temp1,temp3);
    merge(root,root,temp4);
}
void inorder(pnode tree)
{
    if(tree)
    {
        inorder(tree->left);
        cout<<tree->max_sum<<" "<<tree->total_sum<<" "<<tree->pref_sum<<" "<<tree->suff_sum<<endl;
        inorder(tree->right);
    }
}
int main()
{
   $   n;
   cin>>n;
  // scanf("%d",&n);
   $  ii;
   for($  i=1;i<=n;++i)
   {
       cin>>ii;
      // scanf("%d",&ii);
       insert(ii);
   }cout<<MAX_SUM(1,3)<<endl;
   $  m;cin>>m;
   while(m--)
   {
    $  x,y,type;
    cin>>type;
     cin>>x>>y;
     // scanf("%d%d",&x,&y);
     if(type==1)
      cout<<MAX_SUM(x,y)<<endl;
       //printf("%d\n",MAX_SUM(x,y));
       else
        UPDATE(x,y);

   }
   inorder(root);
   return 0;
}
