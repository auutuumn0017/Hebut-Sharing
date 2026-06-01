#include "job_scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

int main() {
    // 初始化作业序列（清空数据）
    initial_jobs();

    // 读取作业数据（从 jobs.txt 文件）
    readJobdata();


    // 依次执行四种调度算法
    FCFS();         // 先来先服务
    reset_jinfo();  // 重置作业状态，为下一个算法做准备

    SJF();// 短作业优先
    reset_jinfo();

    HRRF();// 高响应比优先
    reset_jinfo();

    HPF();          // 优先权高者优先
    reset_jinfo();


    printf("\n");
    system("pause");
    return 0;
}
