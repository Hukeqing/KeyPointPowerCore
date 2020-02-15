#include "algorithms.h"

const int dataLen = 4;

union data {
    char s[dataLen];
    int d;
};

struct binRead {
    string fileName;
    data _a{};
    ifstream inFile;

    explicit binRead(string f) : fileName(std::move(f)) {
        inFile.open(fileName, ios::in | ios::binary);
    }

    ~binRead() {
        inFile.close();
    }

    void close() {
        inFile.close();
    }

    binRead &operator>>(int &d) {
        inFile.read(_a.s, dataLen);
        d = _a.d;
        return *this;
    }
    // NOLINTNEXTLINE
    operator void *() const {
        return inFile.fail() ? (void*)nullptr : (void*)1;
    }
};


int main(int argc, char **argv) {
    binRead bin(*(argv + 1) + string(".bin"));
    freopen(*(argv + 2), "w", stdout);
    cout << "Data name: " << *(argv + 1) << endl;
    node_id n;
    edge_id m;
    bin >> n >> m;
    Graph graph;
    graph.init(n, m);
    BEGIN_LOG_TIME(read)
    for (int i = 0; i < m; ++i) {
        node_id u, v;
        bin >> u >> v;
        graph.addEdge(u, v);
    }
    END_LOG_TIME(read, "Read Data")
    bin.close();
    IndexTree *tree = nullptr;
    solve(n, graph, tree);
//    vector<IndexTree> Forest;
//    solve(n, graph, Forest);
//    node_id keyPoint;
//    int k;
//    bitset<MAX_NODE_COUNT> ans;
//    while(cin >> keyPoint >> k)
//        get_key_point_power_core(keyPoint, k, Forest, ans);
}
