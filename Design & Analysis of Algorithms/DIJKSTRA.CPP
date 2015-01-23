#include<iostream.h>
#include<iomanip.h>
void dijkstras(int,int);
float cost[10][10];
int n;
void main()
{
 int v,d;
 cout<<"enter the number of nodes in the network"<<endl;
 cin>>n;
 cout<<"enter the cost matrix(please enter 1000 if no direct path exists)"<<endl<<"    ";
 for(int i=1;i<=n;i++)
  cout<<i<<"        ";
  cout<<endl;
 for(i=1;i<=n;i++)
 {
  cout<<i;
  for(int j=1;j<=n;j++)
    cin>>cost[i][j];
 }
 cout<<"enter the source node number"<<endl;
 cin>>v;
 cout<<"enter the destination node number"<<endl;
 cin>>d;
 dijkstras(v,d);
}
void dijkstras(int v,int d)
{
 float a[10],s[10];
 int min=1000,u;
 for(int i=1;i<=n;i++)
 {
  s[i]=0;
  a[i]=cost[v][i];
 }
 s[v]=1;
 a[v]=0.0;
 for(int k=2;k<n;k++)
 {
  min=1000;
  for(int i=1;i<=n;i++)
  {
   if((min>=a[i])&&(s[i]==0))
   {
    min=a[i];
    u=i;
    }

  }
  s[u]=1;

  for(i=1;i<=n;i++)
  {
  if(cost[u][i]!=1000&&s[i]==0)
   if(a[i]>a[u]+cost[u][i])


    a[i]=a[u]+cost[u][i];

  }
 }
   cout<<endl<<"cost from node "<<v<<"to node "<<d<<"is "<<a[d];
}








