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

inline void progressLog(size_t count, size_t max_count, double start, double end) {
    string left(count * 100 / max_count, '#'), right(100 - count * 100 / max_count, ' ');
    cerr << setw(10) << count * 100.0 / max_count << "% [" << left << right << "] Cost: " << setw(10)<< (end - start) / CLOCKS_PER_SEC << 's' << endl;
}

// 将下面两个宏定义放置在需要计算时间的代码片段前后，会自动运行时间
#define BEGIN_LOG_TIME(name)                                        double start_time_logger_for_##name = clock();
#define END_LOG_TIME(name, str)                                     {double end_time_logger_for_##name = clock();\
                                                                    logRunTime(start_time_logger_for_##name, end_time_logger_for_##name, str);}
#define BEGIN_CLOCK(name, total)                                    double start_time_clock_for_##name = clock();\
                                                                    size_t start_total_clock_for_##name = (total);\
                                                                    size_t per_total_clock_for_##name = (total) / 100 + 1;
#define TRIGGER_CLOCK(name, cur, trigger)                           double end_time_clock_for_##name = clock();\
                                                                    if (start_total_clock_for_##name >= ((trigger) * 10) && !((cur) % per_total_clock_for_##name))\
                                                                    progressLog((cur) / per_total_clock_for_##name, 100, start_time_clock_for_##name, end_time_clock_for_##name);\
                                                                    else if (start_total_clock_for_##name >= (trigger) && !((cur) % (per_total_clock_for_##name * 10)))\
                                                                    progressLog((cur) / (per_total_clock_for_##name * 10), 10, start_time_clock_for_##name, end_time_clock_for_##name);

#endif //KEY_POINT_POWER_CORE_DEFINES_H
