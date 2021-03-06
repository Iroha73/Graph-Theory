#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
    int src,dest,weight=0;
};

class Graph{
    public:
        int V,E;
        vector<vector<pair<int,int>>> adjList;
        unordered_map<int,int> parent;

        Graph(int,int);
        void udirGraph(vector<Edge>);
        void dirGraph(vector<Edge>);
        void printGraph();
        void DFS(int,int);
        void BFS(int);

};

Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
}

void Graph::udirGraph(vector<Edge> edges){
    adjList.resize(V);
    for(auto edge:edges){
        adjList.at(edge.src).emplace_back(edge.dest,edge.weight);
        adjList.at(edge.dest).emplace_back(edge.src,edge.weight);
    }
    for(int i=0;i<V;i++){
        sort(adjList[i].begin(),adjList[i].end());
    }
}

void Graph::dirGraph(vector<Edge> edges){
    adjList.resize(V);
    for(auto edge:edges){
        adjList.at(edge.src).emplace_back(edge.dest,edge.weight);
    }
    for(int i=0;i<V;i++){
        sort(adjList[i].begin(),adjList[i].end());
    }
}

void Graph::printGraph(){
    for(int i=0;i<V;++i){
        cout << i << " -> ";
        for(auto x:adjList[i]){
            cout << "(" << x.first << "," << x.second << ") ";
        }
        cout << endl;
    }
}

void Graph::DFS(int start,int flag =1){
    if(flag) {parent.clear();}
    cout << start << " ";
    parent.emplace(start,NULL);
    for(auto x : adjList[start]){
        if(parent.find(x.first) == parent.end()){
            parent.emplace(x.first,start);
            DFS(x.first,0);
        }
    }
}

void Graph::BFS(int start){
    parent.clear();
    unordered_map<int,int> height;
    height.emplace(start,0);
    parent.emplace(start,NULL);

    vector<int> sameLevel,next; int i=1;
    sameLevel.emplace_back(start);

    while(!sameLevel.empty()){
        next.clear();
        for(auto u: sameLevel){
            for(auto v : adjList[u]){
                if(height.find(v.first) == parent.end() && v.second>0){
                    parent.emplace(v.first,u);
                    height.emplace(v.first,i);
                    next.push_back(v.first);
                }
            }
        }
        sameLevel = next; ++i;
    }
        parent.erase(start);
        /*unordered_map<int, int>::iterator itr;
        for (itr = parent.begin(); itr != parent.end(); ++itr) {
            cout << itr->first << " - " << itr->second << endl;
        }
        cout << endl;*/
}

#endif

