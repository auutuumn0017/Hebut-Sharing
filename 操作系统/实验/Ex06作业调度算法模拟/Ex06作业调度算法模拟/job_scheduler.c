#define _CRT_SECURE_NO_WARNINGS
#include "job_scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

// 全局变量的定义（与头文件中的 extern 声明对应）
job jobs[MAXJOB];
int quantity = 0;

// 初始化作业序列
void initial_jobs() {
    int i;
    for (i = 0; i < MAXJOB; i++) {
        jobs[i].number = 0;
        jobs[i].reach_time = 0;
        jobs[i].need_time = 0;
        jobs[i].privilege = 0;
        jobs[i].excellent = 0.0f;
        jobs[i].start_time = 0;
        jobs[i].wait_time = 0;
        jobs[i].visited = 0;
        jobs[i].isreached = false;
    }
    quantity = 0;
}

// 读取作业数据
void readJobdata() {
    FILE* fp;
    char fname[20];
    int i;

    printf("please input job data file name: ");
    scanf("%s", fname);

    if ((fp = fopen(fname, "r")) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%d %d %d %d", &jobs[quantity].number, &jobs[quantity].reach_time, &jobs[quantity].need_time, &jobs[quantity].privilege) == 4) {
        quantity++;
    }

    printf("\nOutput the original job data:\n");
    printf("---------------------------------------------------------------------\n");
    printf("\tjobID\treachtime\tneedtime\tprivilege\n");
    for (i = 0; i < quantity; i++) {
        printf("\t%-8d\t%-8d\t%-8d\t%-8d\n", jobs[i].number, jobs[i].reach_time, jobs[i].need_time, jobs[i].privilege);
    }
    printf("---------------------------------------------------------------------\n");

    fclose(fp);
}

// 重置全部作业信息
void reset_jinfo() {
    int i;
    for (i = 0; i < quantity; i++) {
        jobs[i].start_time = 0;
        jobs[i].wait_time = 0;
        jobs[i].visited = 0;
        jobs[i].isreached = false;
        jobs[i].excellent = 0.0f;
    }
}

// 查找当前已到达未执行的最短作业
int findminjob(int current_time) {
    int minloc = -1;
    for (int i = 0; i < quantity; i++) {
        if (jobs[i].reach_time <= current_time && jobs[i].visited == 0) {
            if (minloc == -1 || jobs[i].need_time < jobs[minloc].need_time) {
                minloc = i;
            }
        }
    }
    return minloc;
}

// 查找最早到达且未执行的作业
int findrearlyjob() {
    int earlyloc = -1;
    for (int i = 0; i < quantity; i++) {
        if (jobs[i].visited == 0) {
            if (earlyloc == -1 || jobs[i].reach_time < jobs[earlyloc].reach_time) {
                earlyloc = i;
            }
        }
    }
    return earlyloc;
}

// 查找优先权最高且已到达未执行的作业
int findhighest_privilege(int current_time) {
    int privloc = -1;
    for (int i = 0; i < quantity; i++) {
        if (jobs[i].reach_time <= current_time && jobs[i].visited == 0) {
            if (privloc == -1 || jobs[i].privilege < jobs[privloc].privilege) {
                privloc = i;
            }
        }
    }
    return privloc;
}

// 更新所有作业的isreached状态
void update_isreached(int current_time) {
    for (int i = 0; i < quantity; i++) {
        if (jobs[i].reach_time <= current_time) {
            jobs[i].isreached = true;
        }
    }
}

// ====================================================================
// 以下是四种调度算法的实现
// ====================================================================

// 先来先服务算法
void FCFS() {
    int current_time = 0;
    int loc;
    int total_wait_time = 0;
    int total_round_time = 0;

    printf("\n\n===== FCFS Algorithm =====\n");
    printf("------------------------------------------------------------------------\n");
    printf("\tjobID\treachtime\tstarttime\twaittime\troundtime\n");

    loc = findrearlyjob();
    current_time = jobs[loc].reach_time;

    for (int i = 0; i < quantity; i++) {
        jobs[loc].start_time = current_time;
        jobs[loc].wait_time = current_time - jobs[loc].reach_time;
        int round_time = jobs[loc].wait_time + jobs[loc].need_time;

        printf("\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n",
            jobs[loc].number, jobs[loc].reach_time, jobs[loc].start_time,
            jobs[loc].wait_time, round_time);

        jobs[loc].visited = 1;
        current_time += jobs[loc].need_time;
        total_wait_time += jobs[loc].wait_time;
        total_round_time += round_time;

        loc = findrearlyjob();
    }

    printf("------------------------------------------------------------------------\n");
    printf("Total Waiting Time: %-8d Total Turnaround Time: %-8d\n", total_wait_time, total_round_time);
    printf("Average Waiting Time: %4.2f Average Turnaround Time: %4.2f\n",
        (float)total_wait_time / quantity, (float)total_round_time / quantity);
}
// 短作业优先调度算法
void SJF() {
    int current_time = 0;
    int loc;
    int total_wait_time = 0;
    int total_round_time = 0;
    int completed = 0; // 记录已完成的作业数

    printf("\n\n===== SJF Algorithm =====\n");
    printf("------------------------------------------------------------------------\n");
    printf("\tjobID\treachtime\tstarttime\twaittime\troundtime\n");
    printf("------------------------------------------------------------------------\n");

    // 使用 while 循环，直到所有作业都完成
    while (completed < quantity) {
        // 1. 查找当前已到达且未执行的作业中，执行时间最短的那个
        loc = findminjob(current_time);

        // 2. 如果找到了要执行的作业
        if (loc != -1) {
            jobs[loc].start_time = current_time;
            jobs[loc].wait_time = current_time - jobs[loc].reach_time;
            int round_time = jobs[loc].wait_time + jobs[loc].need_time;

            printf("\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n",
                jobs[loc].number, jobs[loc].reach_time, jobs[loc].start_time,
                jobs[loc].wait_time, round_time);

            // 更新状态
            jobs[loc].visited = 1;
            completed++;
            current_time += jobs[loc].need_time; // 时间跳转到作业完成时
            total_wait_time += jobs[loc].wait_time;
            total_round_time += round_time;
        }
        else {
            // 3. 如果没找到（系统空闲），时间向前推进1个单位
            current_time++;
        }
    }

    printf("------------------------------------------------------------------------\n");
    printf("Total Waiting Time: %-8d Total Turnaround Time: %-8d\n", total_wait_time, total_round_time);
    printf("Average Waiting Time: %4.2f Average Turnaround Time: %4.2f\n",
        (float)total_wait_time / quantity, (float)total_round_time / quantity);
}

// 高响应比优先算法
void HRRF() {
    int current_time = 0;
    int total_wait_time = 0;
    int total_round_time = 0;
    int completed = 0;

    printf("\n\n===== HRRF Algorithm =====\n");
    printf("------------------------------------------------------------------------\n");
    printf("\tjobID\treachtime\tstarttime\twaittime\troundtime\tresponse_ratio\n");
    printf("------------------------------------------------------------------------\n");

    while (completed < quantity) {
        float max_ratio = -1.0f; // 使用float以获得更高精度
        int selected_index = -1;

        // 遍历所有作业，找到响应比最高的那个
        for (int i = 0; i < quantity; i++) {
            // 作业未被执行，且已经到达
            if (jobs[i].visited == 0 && jobs[i].reach_time <= current_time) {
                float wait_time = current_time - jobs[i].reach_time;
                // 计算响应比: 1 + (等待时间 / 服务时间)
                float ratio = 1.0f + (wait_time / (float)jobs[i].need_time);
                // 如果找到响应比更高的作业，则更新
                if (ratio > max_ratio) {
                    max_ratio = ratio;
                    selected_index = i;
                }
            }
        }

        // 如果没有找到可执行的作业（即所有到达的作业都已完成）
        if (selected_index == -1) {
            current_time++; // 时间片向前推进一格
            continue;
        }

        // 计算并更新被选中作业的信息
        jobs[selected_index].start_time = current_time;
        jobs[selected_index].wait_time = current_time - jobs[selected_index].reach_time;
        jobs[selected_index].excellent = max_ratio; // 记录响应比
        jobs[selected_index].visited = 1; // 标记为已执行
        completed++;

        // 打印作业信息
        int round_time = jobs[selected_index].wait_time + jobs[selected_index].need_time;
        printf("\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\t%-8.2f\n",
            jobs[selected_index].number, jobs[selected_index].reach_time, jobs[selected_index].start_time,
            jobs[selected_index].wait_time, round_time, jobs[selected_index].excellent);

        // 更新系统当前时间，并累加总时间
        current_time += jobs[selected_index].need_time;
        total_wait_time += jobs[selected_index].wait_time;
        total_round_time += round_time;
    }

    // 打印统计信息
    printf("------------------------------------------------------------------------\n");
    printf("Total Waiting Time: %-8d Total Turnaround Time: %-8d\n", total_wait_time, total_round_time);
    printf("Average Waiting Time: %4.2f Average Turnaround Time: %4.2f\n",
        (float)total_wait_time / quantity, (float)total_round_time / quantity);
}

// 优先权高者优先算法
void HPF() {
    int current_time = 0;
    int loc;
    int total_wait_time = 0;
    int total_round_time = 0;

    printf("\n\n===== HPF Algorithm =====\n");
    printf("------------------------------------------------------------------------\n");
    printf("\tjobID\treachtime\tstarttime\twaittime\troundtime\tpriority\n");

    for (int i = 0; i < quantity; i++) {
        // 找到当前已到达且优先级最高的作业
        loc = findhighest_privilege(current_time);

        if (loc == -1) {
            // 如果没有已到达的作业，快进时间到下一个作业的到达时间
            int next_time = 100000;
            for (int j = 0; j < quantity; j++) {
                if (jobs[j].visited == 0 && jobs[j].reach_time < next_time) {
                    next_time = jobs[j].reach_time;
                }
            }
            current_time = next_time;
            loc = findhighest_privilege(current_time);
        }

        jobs[loc].start_time = current_time;
        jobs[loc].wait_time = current_time - jobs[loc].reach_time;
        int round_time = jobs[loc].wait_time + jobs[loc].need_time;

        printf("\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n",
            jobs[loc].number, jobs[loc].reach_time, jobs[loc].start_time,
            jobs[loc].wait_time, round_time, jobs[loc].privilege);

        jobs[loc].visited = 1;
        current_time += jobs[loc].need_time;
        total_wait_time += jobs[loc].wait_time;
        total_round_time += round_time;
    }

    printf("------------------------------------------------------------------------\n");
    printf("Total Waiting Time: %-8d Total Turnaround Time: %-8d\n", total_wait_time, total_round_time);
    printf("Average Waiting Time: %4.2f Average Turnaround Time: %4.2f\n",
        (float)total_wait_time / quantity, (float)total_round_time / quantity);
}