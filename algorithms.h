//
// Created by HKQ on 2020/2/8.
//

#ifndef KEY_POINT_POWER_CORE_ALGORITHMS_H
#define KEY_POINT_POWER_CORE_ALGORITHMS_H

#include "database.h"

void get_key_point_power_core(node_id keyPoint, int k, const IndexTree &tree, bitset<MAX_NODE_COUNT> &out) {
    out.reset();
    BEGIN_LOG_TIME(ans)
    int cur_node = tree.node2Index[keyPoint];
    for (cur_node = tree.nodeList[cur_node].father; cur_node != -1; cur_node = tree.nodeList[cur_node].father) {
        out.set(tree.nodeList[cur_node].begin);
        for (auto &item : tree.nodeList[cur_node].nodeList)
            out.set(item);
    }
    END_LOG_TIME(ans, "Get Answer of keyPoint = " + to_string(keyPoint) + ", k = " + to_string(k));
}

bool build_k_core(int k, node_id n, Graph &graph) {
    queue<node_id> q;
    bitset<MAX_NODE_COUNT> visit;
    for (node_id i = 0; i < n; ++i) {
        if (graph.nodeDeleted.test(i)) {
            visit.set(i);
        } else if (graph.deg[i] < k) {
            q.push(i);
            visit.set(i);
        }
    }
    while (!q.empty()) {
        node_id cur = q.front();
        q.pop();
        graph.nodeDeleted.set(cur);
        for (edge_id i = graph.head[cur]; i != -1; i = graph.edge[i].next) {
            node_id next = graph.edge[i].to;
            graph.deg[next]--;
            if (!visit.test(next) && graph.deg[next] < k) {
                q.push(next);
                visit.set(next);
            }
        }
    }
    for (node_id i = 0; i < n; ++i) {
        if (visit.test(i))
            continue;
        return true;
    }
    return false;
}

void build_k_core_tree(int k, node_id n, Graph &graph, IndexTree &tree) {
    node_id min_id = 0;
    bitset<MAX_NODE_COUNT> nodeDeleted(graph.nodeDeleted);
    bitset<MAX_NODE_COUNT> visit(nodeDeleted);
    vector<int> deg(graph.deg);
    vector<Graph::Edge> &edge = graph.edge;
    while (true) {
        while (min_id < n && nodeDeleted.test(min_id))
            min_id++;
        if (min_id >= n)
            break;
        queue<node_id> q;
        q.push(min_id);
        visit.set(min_id);
        tree.addNode(min_id);
        while (!q.empty()) {
            node_id cur = q.front();
            q.pop();
            nodeDeleted.set(cur);
            tree.addDeletedNode(cur);
            for (edge_id i = graph.head[cur]; i != -1; i = edge[i].next) {
                node_id next = edge[i].to;
                deg[next]--;
                if (!visit.test(next) && deg[next] < k) {
                    q.push(next);
                    visit.set(next);
                }
            }
        }
        min_id++;
    }
//    cout << "Graph is disassembled to " << setw(10) << tree.tot << " part" << endl;
    map<node_id, int> part_pool;
    UnionFindSet UFS;
    UFS.init(n);
    BEGIN_CLOCK(link, tree.tot)
    for (int i = tree.tot; i >= 0; --i) {
        int cur_head = tree.nodeList[i].begin;
        for (edge_id j = graph.head[cur_head]; j != -1; j = edge[j].next)
            UFS.unite(cur_head, edge[j].to);
        for (auto &item : tree.nodeList[i].nodeList) {
            for (edge_id j = graph.head[item]; j != -1; j = edge[j].next)
                UFS.unite(item, edge[j].to);
        }
        node_id cur_father = UFS.finds(cur_head);
        auto iter = part_pool.begin();
        while (iter != part_pool.end()) {
            if (UFS.finds(iter->first) == cur_father) {
                tree.link(iter->second, i);
                auto tmp = iter;
                iter++;
                part_pool.erase(tmp);
            } else {
                iter++;
            }
        }
        part_pool.insert({cur_head, i});
        TRIGGER_CLOCK(link, tree.tot - i + 1, 100000)
    }
}

void solve(int n, Graph &graph, vector<IndexTree> &trees) {
    BEGIN_LOG_TIME(solve)
    int k = 2;
    while (build_k_core(k, n, graph)) {
        trees.emplace_back();
        trees.back().init(n);
        BEGIN_LOG_TIME(round)
        build_k_core_tree(k, n, graph, trees.back());
        END_LOG_TIME(round, "Build " + to_string(k) + "-Tree")
        k++;
    }
    END_LOG_TIME(solve, "Build Forest")
}

void solve(int n, Graph &graph, IndexTree *tree) {
    BEGIN_LOG_TIME(solve)
    int k = 2;
    while (build_k_core(k, n, graph)) {
//        trees.emplace_back();
//        trees.back().init(n);
        tree = new IndexTree();
        tree->init(n);
        BEGIN_LOG_TIME(round)
        build_k_core_tree(k, n, graph, *tree);
        END_LOG_TIME(round, "Build " + to_string(k) + "-Tree")
        default_random_engine e(time(nullptr));
        uniform_int_distribution<unsigned> u(0, n);
        auto dice = bind(u, e);
        bitset<MAX_NODE_COUNT> out;
        for (int i = 0; i < 10; ++i) {
            int cur = dice();
            while (graph.nodeDeleted.test(cur)) {
                cur = dice();
            }
            get_key_point_power_core(cur, k, *tree, out);
        }
        k++;
        delete tree;
    }
    END_LOG_TIME(solve, "Build Forest")
}

#endif //KEY_POINT_POWER_CORE_ALGORITHMS_H
