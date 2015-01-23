#include<iostream>
using namespace std; 
int cost[10][10],dist[10];
void bellman(int,int);
 int n,v=1,u,i,j,k,a,d,m;
int main()
{
	cout<<"enter the no. of nodes\n";
	cin>>n;
	cout<<"enter the source node\n";
	cin>>v;
	cout<<"enter the destination node\n";
	cin>>d;
	cout<<"enter the cost( enter 1000 if no direct path exist) ";
	for(int m=1;m<=n;m++)
	{	
	cout<<m<<"           ";
	
	}
	for( i=1;i<=n;i++)	
	{
	cout<<"\n"<<i;
	for(a=1;a<=n;a++)	
	{
	cin>>cost[i][a];
	}
	}
	bellman( v, n);
	return 0;
}
   void bellman(int v,int n)
{
	for( j=1;j<=n;j++)
	{
		dist[j]=cost[v][j];
		
	}

     for( k=2;k<=n-1;k++)
  {
     for( u=1;u<=n;u++)	  
     {
	for( i=1;i<=n;i++)     
	{
		
	  while(u!=v&&cost[u][i]!=1000&&cost[u][i]!=0)
	  {
		  if(dist[u]>(dist[i]+cost[i][u]))
		  {
			  dist[u]=dist[i]+cost[i][u];
		  }
		  else
			  break;
	  }
	}
     }
  }

     cout<<"distance of source to destination is:"<<dist[d];
}		
	
