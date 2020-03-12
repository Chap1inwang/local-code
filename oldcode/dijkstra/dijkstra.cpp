#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;


void dijkstra(int n,int s,vector<vector<int>> G,vector<bool>& vis,vector<int>& d,vector<int>& pre){

	//n:n个节点
	//s：起点
	//G：图
	//vis：记录该结点是否访问过
	//d：记录s到其他点的最短距离
	//pre：记录路径中v的前驱节点
	
	fill(vis.begin(),vis.end(),false);
	fill(d.begin(),d.end(),INT_MAX);
	d[s]=0;
	for(int i=0;i<n;++i){
		pre[i]=i;
	}
	for(int i=0;i<n;++i){
		int u=-1;
		int MIN=INT_MAX;
		for(int j=0;j<n;++j){
			if(!vis[j]&&d[j]<MIN){
				u=j;
				MIN=d[j];
			}
		}
		if(u==-1){
			return;
		}
		vis[u]=true;
		for(int v=0;v<n;++v){
			if((!vis[v])&&G[u][v]!=INT_MAX&&d[u]+G[u][v]<d[v]){
				d[v]=d[u]+G[u][v];
				pre[v]=u;
			}
		}
	}
}

void DFSPrint(int s,int v,vector<int> pre){
	if(v==s){
		cout<<s<<" ";
		return;
	}
	DFSPrint(s,pre[v],pre);
	cout<<v<<" ";
}


int main()
{
    int n = 6;
    /*邻接矩阵*/
    vector<vector<int>> G = {{  0,  4,INT_MAX,INT_MAX,  1,  2},
                             {  4,  0,  6,INT_MAX,INT_MAX,  3},
                             {INT_MAX,  6,  0,  6,INT_MAX,  5},
                             {INT_MAX,INT_MAX,  6,  0,  4,  5},
                             {  1,INT_MAX,INT_MAX,  4,  0,  3},
                             {  2,  3,  5,  5,  3,  0}};
    vector<bool> vis(n);
    vector<int> d(n);
    vector<int> pre(n);
 
    dijkstra(n, 0, G, vis, d, pre);
 
    for (size_t i = 0; i < d.size(); ++i)
    {
        cout << "the shortest path " << i << " is: " << d[i] << endl;
    }
    cout << endl;
 
    // v = 2: 0->5->2  cost = 2 + 5 = 7
    // v = 3: 0->4->3  cost = 1 + 4 = 5
    int v = 2;
    DFSPrint(0, v, pre);
    cout << endl << "cost = " << d[v] << endl;
 
    return 0;
}
