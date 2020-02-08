//
// Created by HKQ on 2020/2/8.
//

#ifndef KEY_POINT_POWER_CORE_DATABASE_H
#define KEY_POINT_POWER_CORE_DATABASE_H

#include "defines.h"

struct Graph {
    struct Edge {
        int to, next;
    };
    vector<Edge> edge;
    vector<edge_id> head;
    bitset<MAX_NODE_COUNT> nodeDeleted;
    vector<int> deg;
    int tot{};

    void init(node_id n, edge_id m) {
        edge.resize(m * 2);
        head.resize(n, -1);
        deg.resize(n, 0);
        nodeDeleted.reset();
        tot = 0;
    }

    void addEdge(node_id u, node_id v) {
        edge[tot].to = v;
        edge[tot].next = head[u];
        head[u] = tot++;
        deg[u]++;

        edge[tot].to = u;
        edge[tot].next = head[v];
        head[v] = tot++;
        deg[v]++;
    }
};

struct UnionFindSet {
    vector<node_id> f;

    void init(node_id n) {
        f.resize(n);
        for (int i = 0; i < n; ++i)
            f[i] = i;
    }

    void unite(node_id x, node_id y) {
        node_id rx = finds(x);
        node_id ry = finds(y);
        if (rx != ry)
            f[rx] = ry;
    }

    node_id finds(node_id x) {
        return x == f[x] ? x : f[x] = finds(f[x]);
    }
};

struct IndexTree {
    struct Node {
        node_id begin;
        vector<node_id> nodeList;
        int father;
        vector<int> children;

        explicit Node(node_id be) : begin(be), father(-1) {}
    };

    vector<Node> nodeList;
    int tot;
    vector<int> node2Index;

    void init(int n) {
        tot = -1;
        node2Index.resize(n, -1);
    }

    inline void link(int from, int to) {
        nodeList[from].father = to;
        nodeList[to].children.push_back(from);
    }

    void addNode(node_id begin) {
        nodeList.emplace_back(begin);
        node2Index[begin] = ++tot;
    }

    void addDeletedNode(node_id node) {
        nodeList[tot].nodeList.push_back(node);
        node2Index[node] = tot;
    }

    IndexTree() : tot(-1) {}
};

#endif //KEY_POINT_POWER_CORE_DATABASE_H
