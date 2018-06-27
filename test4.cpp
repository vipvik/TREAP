//LAZY PROPAGATION

#include<bits/stdc++.h>
using namespace std;
#define MAX 10000

int tree[MAX]={0};
int lazy[MAX]={0};

int min(int a,int b){return a>b?b:a;}
int midV(int ss,int se){return (ss+(se-ss)/2);}

void UpdateRangeUntil(int ss,int se,int us,int ue,int diff,int si)
{
   if(lazy[si]!=0)
   {
       tree[si]+=(se-ss+1)*lazy[si];
       if(ss!=se)
       {
           lazy[2*si+1]+=lazy[si];
           lazy[2*si+2]+=lazy[si];
       }
       lazy[si]=0;
   }

   if(se<ss||us>se||ue<ss)
    return;
   if(us<=ss&&ue>=se)
   {
       tree[si]+=(se-ss+1)*diff;
       if(ss!=se)
       {
           lazy[2*si+1]+=diff;
           lazy[2*si+2]+=diff;
       }
       return;
   }
   int mid=midV(ss,se);
   UpdateRangeUntil(ss,mid,us,ue,diff,2*si+1);
   UpdateRangeUntil(mid+1,se,us,ue,diff,2*si+2);
   tree[si]=tree[2*si+1]+tree[2*si+2];
}
void UpdateRange(int us,int ue,int diff,int n)
{
    if(us<0||ue>n-1)
    {
        cout<<"Wrong Index"<<endl;return;
    }
    UpdateRangeUntil(0,n-1,us,ue,diff,0);
}

int getSumUntil(int ss,int se,int qs,int qe,int si)
{
    if(lazy[si]!=0)
    {
        tree[si]+=(se-ss+1)*lazy[si];
       if(ss!=se)
       {
           lazy[2*si+1]+=lazy[si];
           lazy[2*si+2]+=lazy[si];
       }
       lazy[si]=0;
    }
    if(ss>se||qs>se||qe<ss)return 0;
    if(ss>=qs&&qe>=se)return tree[si];

    int mid=midV(ss,se);
    return getSumUntil(ss,mid,qs,qe,2*si+1)+getSumUntil(mid+1,se,qs,qe,2*si+2);
}
int getSum(int qs,int qe,int n)
{
    if(qs<0||qe>n-1||qs>qe)
    {
        cout<<"Invalid Range"<<endl;
        return -1;
    }
    return getSumUntil(0,n-1,qs,qe,0);
}

void constructUntil(int *A,int ss,int se,int si)
{
    if(ss>se)return;
    if(ss==se)
    {
        tree[si]=A[ss];
        return;
    }
    int mid=midV(ss,se);
    constructUntil(A,ss,mid,2*si+1);
    constructUntil(A,mid+1,se,2*si+2);
    tree[si]=tree[2*si+1]+tree[2*si+2];
}
void construct(int *A,int n)
{
    constructUntil(A,0,n-1,0);
}

int main()
{
     int arr[] = {1, 3, 5, 7, 9, 11};
     int n=6;
     construct(arr,n);
     cout<<getSum(1,3,n)<<endl;
     UpdateRange(1,5,10,n);
     cout<<getSum(1,3,n)<<endl;
     cout<<getSum(1,4,n)<<endl;
     return 0;
}
