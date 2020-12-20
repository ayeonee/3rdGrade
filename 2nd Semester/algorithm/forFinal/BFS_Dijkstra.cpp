#include <iostream>
#include <list>
#include <set>
#include <vector>
using namespace std; 

#define INF 2147483647

class Graph{
	int V;		//vertex 갯수
	list<pair<int, int>> *adj;	
public : 
	Graph(int V);		
	void addEdge(int u, int v, int w);
	void shortestPath(int s);
};

Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<pair<int,int>>[V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[v].push_back(make_pair(u,w)); 
	adj[u].push_back(make_pair(v,w));
}

void Graph::shortestPath(int src){
	set<pair<int, int>> setds;		//first에 d[], second에 v, d[v]=출발점에서 v라는 노드까지 가는데 필요한 현재까지 발견된 가장 짧은 거리
	vector<int> dist(V,INF);
	
	setds.insert(make_pair(0,src));
	dist[src]=0;

	while(!setds.empty()){
		pair<int, int>tmp=*(setds.begin());
		setds.erase(setds.begin());
		int u=tmp.second;

		list<pair<int, int>>::iterator i;
		for(i=adj[u].begin(); i!=adj[u].end(); ++i){
			int v=(*i).first;
			int weight=(*i).second;

			if(dist[v]>dist[u]+weight){
				if(dist[v]!=INF)
					setds.erase(setds.find(make_pair(dist[v],v)));
				dist[v]=dist[u]+weight;
				setds.insert(make_pair(dist[v],v));
			}
		}
	}
	cout<<"vertex distance from source"<<endl;
	for(int i=0; i<V; ++i)
		cout<<i<<" t t "<<dist[i]<<endl;
}

int main(){
	Graph g(5);
	g.addEdge(0,1,1);
	g.addEdge(1,2,1);
	g.addEdge(2,3,4);
	g.addEdge(1,4,22);
	g.addEdge(3,4,20);
	g.addEdge(0,4,25);

	g.shortestPath(0);
}