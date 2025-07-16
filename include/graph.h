// 图结构
#include <bits/stdc++.h>
using namespace std;

// 邻接表实现的图结构
class Graph {
public:
    // 存储相邻节点及边的权重
    struct Edge {
        int to;
        int weight;

        // 构造函数，应该写在结构体内部
        Edge(int to, int weight) {
            this->to = to;
            this->weight = weight;
        }
    };
private:
    // 邻接表
    vector<vector<Edge>> graph;

public: 
    // 构造函数，初始化图的节点数
    Graph(int n) {
        graph.resize(n);
    }

    // 添加边
    void addEdge(int from, int to, int weight) {
        graph[from].push_back(Edge(to, weight));
    }

    // 删除边
    void removeEdge(int from, int to) {
        for (auto it = graph[from].begin(); it!= graph[from].end(); it++) {
            if (it->to == to) {
                graph[from].erase(it);
                break;
            }
        }
    }

    // 查，返回一条边的权重
    int getEdgeWeight(int from, int to) {
        for (auto it = graph[from].begin(); it!= graph[from].end(); it++) {
            if (it->to == to) {
                return it->weight;
            }
        return -1; // 没有找到边
        }
    }

    // 查，返回某个节点的所有邻居节点
    const vector<Edge>& getNeighbors(int from) {
        return graph[from];
    }
};

// 邻接矩阵实现的图结构
class Graph {
public:
    // 存储相邻节点及边的权重
    struct Edge {
        int to;
        int weight;

        // 构造函数，应该写在结构体内部
        Edge(int to, int weight) {
            this->to = to;
            this->weight = weight;
        }
    };
private:
    // 邻接矩阵
    vector<vector<int>> graph;

public: 
    // 构造函数，初始化图的节点数
    Graph(int n) {
        graph.resize(n, vector<int>(n, 0));
    }

    // 添加边
    void addEdge(int from, int to, int weight) {
        graph[from][to] = weight;
    }

    // 删除边
    void removeEdge(int from, int to) {
        graph[from][to] = 0;
    }

    // 查，判断两个节点是否相邻
    bool isAdjacent(int from, int to) {
        return graph[from][to] != 0;
    }

    // 查，返回一条边的权重
    int getEdgeWeight(int from, int to) {
        return graph[from][to];
    }

    // 查，返回某个节点的所有邻居节点
    vector<Edge> getNeighbors(int from) {
        vector<Edge> neighbors;
        for (int i = 0; i < graph[from].size(); i++) {
            if (graph[from][i] != 0) {
                neighbors.push_back(Edge(i, graph[from][i]));
            }
        }
        return neighbors;
    }
};

        