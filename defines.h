//
// Created by HKQ on 2020/2/8.
//

#ifndef KEY_POINT_POWER_CORE_DEFINES_H
#define KEY_POINT_POWER_CORE_DEFINES_H

#include <bits/stdc++.h>

using namespace std;

typedef int node_id;
typedef int edge_id;

const int MAX_NODE_COUNT = 1200000;
const int MAX_EDGE_COUNT = 3000000;

const int NODE_NULL = -1;
const int EDGE_NULL = -1;

inline void logRunTime(double start, double end, const string &function_name) {
    cout << "******\t" << setw(30) << function_name << " Runtime is: " << setw(10) << (end - start) / CLOCKS_PER_SEC
         << "s\t\t\t\t\t----Time Log" << endl;
}

// 将下面两个宏定义放置在需要计算时间的代码片段前后，会自动运行时间
#define BEGIN_LOG_TIME(name)                                        double start_time_logger_for_##name = clock();
#define END_LOG_TIME(name, str)                                     {double end_time_logger_for_##name = clock();\
                                                                    logRunTime(start_time_logger_for_##name, end_time_logger_for_##name, str);}

#endif //KEY_POINT_POWER_CORE_DEFINES_H
