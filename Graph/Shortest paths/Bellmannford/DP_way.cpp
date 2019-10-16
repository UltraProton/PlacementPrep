/*

http://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf


 */

#include<bits/stdc++.h>

using namespace std;

class edge{
    public:
    int u;
    int v;
    int wt;
    edge(int u,int v, int wt);
};

class Graph{
    public:
    int V;
    vector<edge> edge_list;
    vector<int> parent;
    vector<int> dist;
    Graph(int n_vertices);
    void add_edge(int u, int v,int wt);
    void relax(edge e);
    bool BellMann_Ford(int src);
};

int main(int argc, char const *argv[])
{
    Graph g(5);

    g.add_edge(0,1,6);
    g.add_edge(0,2,7);
    g.add_edge(1,2,8);
    g.add_edge(1,3,5);
    g.add_edge(1,4,-4);
    g.add_edge(2,3,-3);
    g.add_edge(2,4,9);
    g.add_edge(3,1,-2);
    g.add_edge(4,3,7);
    g.add_edge(4,0,2);

    cout<< g.BellMann_Ford(0)<<endl;

    return 0;
}

Graph :: Graph(int n_vertices){
    V=n_vertices;
}

void Graph :: add_edge(int u, int v, int wt){
    edge_list.emplace_back(edge(u,v,wt));
}

void Graph :: relax(edge e){
    if(dist[e.v] > dist[e.u]+ e.wt){
        dist[e.v]= dist[e.u] + e.wt;
        parent[e.v]= e.u;
    }
}


bool Graph :: BellMann_Ford(int src){
    parent= vector<int>(V,-1);
    dist= vector<int> (V,INT_MAX);
    dist[src]=0;

    // * iterate |G.V|-1 times 
    for(int i=1;i<V;i++){ // ! O(V)
        // * For each edge in the edge list relax it
        for(auto e:edge_list){  // ! O(E) 
        // ? Here the edge (u,v) is not relaxed until we have u.d != infinity or distance of v.d is less than what we would acheive
        // ? after relaxing the edge 
            if(dist[e.u] != INT_MAX && dist[e.v] > dist[e.u]+ e.wt){ //* If the distance of u(src) is already INT_MAX then we can't
                                                                    //* find the shortest path to any vertex v(dest) adjacent to u of 
                                                                    //* the edge (u,v) so no point of relaxing it at this point of 
                                      //* instance
                //* Otherwise we can relax the edge e
                relax(e);
            }
        }
    }

    // * If we still we have an edge where the shortest distance to a vertex v is greater than the shortest distance of
    // * of an adjacent vertex u plus the edge weight w between v and u then there is a negative weight cycle present
    // * in the graph which is reachable from the source and it signifies that we won't be able to find the shortest 
    // * path between each vertex 
    for(auto e: edge_list){ // ! O(E)
        if(dist[e.v] > dist[e.u] + e.wt){
            return false;
        }
    }

    int i=0;
    for(int i=0;i<V;i++){
        cout<<i<<","<<parent[i]<<","<<dist[i]<<endl;
    }

    return true;
}

// ! Overall time complexity : O(V.E)

edge :: edge(int u, int v, int wt){
    this->u=u;
    this->v=v;
    this->wt=wt;
}

