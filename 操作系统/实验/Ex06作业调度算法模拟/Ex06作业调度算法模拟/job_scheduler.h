#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include <stdbool.h>
#include <limits.h> 

// 最大作业数量
#define MAXJOB 50

// 作业的数据结构
typedef struct node {
    int number;      // 作业号
    int reach_time;  // 作业抵达时间
    int need_time;   // 作业的执行时间
    int privilege;   // 作业优先权
    float excellent; // 响应比
    int start_time;  // 作业开始时间
    int wait_time;   // 等待时间
    int visited;     // 作业是否被访问过
    bool isreached;  // 作业是否抵达
} job;

// 全局作业数组和数量（extern 声明，表示在其他文件中定义）
extern job jobs[MAXJOB];
extern int quantity;

// 辅助函数声明
void initial_jobs();
void readJobdata();
void reset_jinfo();
int findminjob(int current_time);
int findrearlyjob();
int findhighest_privilege(int current_time);
void update_isreached(int current_time);

// 调度算法函数声明
void FCFS();
void SJF();
void HRRF();
void HPF();

#endif // JOB_SCHEDULER_H