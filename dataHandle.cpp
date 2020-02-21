//
// Created by HKQ on 2020/2/2.
//

#include <bits/stdc++.h>

using namespace std;

const int lenth = 4;

union data {
    char s[lenth];
    int d;
};

void edge2bin(char *file_name) {
    ifstream inFile(file_name + string(".edge"), ios::in | ios::binary);
    ofstream outFile(file_name + string(".bin"), ios::out | ios::binary);
    data a{};
    while (inFile >> a.d) {
        outFile.write(a.s, sizeof(char) * lenth);
    }
    inFile.close();
    outFile.flush();
    outFile.close();
}

void bin2edge(char *file_name) {
    ifstream inFile(file_name + string(".bin"), ios::in | ios::binary);
    ofstream outFile(file_name + string(".edge"), ios::out);
    data a{};
    bool ret = true;
    while (inFile.read(a.s, lenth)) {
        outFile << a.d << (ret ? " " : "\n");
        ret = !ret;
    }
    inFile.close();
    outFile.flush();
    outFile.close();
}

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
        inFile.read(_a.s, lenth);
        d = _a.d;
        return *this;
    }

    // NOLINTNEXTLINE
    operator void *() const {
        return inFile.fail() ? (void*)nullptr : (void*)1;
    }
};

int main(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        char *file_name = *(argv + i);
        edge2bin(file_name);
//        bin2edge(file_name);
//        int k;
//        bool ret = false;
//        binRead bin(file_name + string(".bin"));
//        while(bin >> k) {
//            cout << k << (ret ? "\n" : " ");
//            ret = !ret;
//        }
    }
}
