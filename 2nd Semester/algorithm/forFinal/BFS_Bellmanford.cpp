#include <iostream>
#include <list>
#include <set>
#include <vector>
using namespace std; 

#define INF 2147483647

class Graph{
	int V;		
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
    vector<int> dist(V,INF);
    dist[src]=0;

    for(int j=0; j<3; j++){
        for(int u=0; u<V; u++){
            list<pair<int, int>>::iterator i;
            for(i=adj[u].begin(); i!=adj[u].end(); ++i){
                int v=(*i).first;
                int weight=(*i).second;

                if(dist[u]!= INF && dist[v]>dist[u]+weight){
                    dist[v]=dist[u]+weight;
                }
            }
        }
        for(int i=0; i<V; ++i)
		cout<<i<<" t t "<<dist[i]<<endl;
    }
    for(int u=0; u<V; u++){
        list<pair<int, int>> ::iterator i;
        for(i=adj[u].begin(); i!=adj[u].end(); ++i){
            int v=(*i).first;
            int weight=(*i).second;

            if(dist[u]!=INF && dist[v] > dist[u]+weight){
                cout << "NEGATIVE CYCLE"<<endl;
                return;
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
	g.addEdge(0,1,-4);
	g.addEdge(1,0,1);
	g.addEdge(1,2,2);
	g.addEdge(1,3,2);
	g.addEdge(2,0,-4);
	g.addEdge(2,1,2);
	g.addEdge(2,3,8);
	g.addEdge(3,1,3);
	g.addEdge(3,2,8);
	g.addEdge(3,4,9);
	g.addEdge(4,3,9);

	g.shortestPath(0);
}