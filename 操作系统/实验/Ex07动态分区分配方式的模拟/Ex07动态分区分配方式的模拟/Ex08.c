#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define VM_PAGE 7     // 虚页数量
#define PM_PAGE 4     // 物理页数量
#define TOTAL_INSERT 18 // 测试页面访问序列长度

// 页表项数据结构
typedef struct {
    int vmn;    // 虚页号
    int pmn;    // 实页号
    int exist;  // 是否在内存中
    int time;   // 时间戳(不同算法含义不同)
} vpage_item;

vpage_item page_table[VM_PAGE];  // 页表
vpage_item* ppage_bitmap[PM_PAGE]; // 物理页位图
int vpage_arr[TOTAL_INSERT] = { 1,2,3,4,2,6,2,1,2,3,7,6,3,2,1,2,3,6 }; // 测试序列

// 初始化数据
void init_data() {
    for (int i = 0; i < VM_PAGE; i++) {
        page_table[i].vmn = i + 1;  // 虚页号从1开始
        page_table[i].pmn = -1;     // 初始时不在内存中
        page_table[i].exist = 0;
        page_table[i].time = -1;
    }
    for (int i = 0; i < PM_PAGE; i++) {
        ppage_bitmap[i] = NULL;    // 初始时物理页都为空
    }
}

// FIFO页面置换算法
void FIFO() {
    init_data();
    int k = 0;                   // 已使用的物理页数量
    int missing_page_count = 0;   // 缺页次数
    int current_time = 0;         // 当前时间

    for (int i = 0; i < TOTAL_INSERT; i++) {
        int vpage = vpage_arr[i]; // 当前访问的虚页

        if (page_table[vpage - 1].exist == 0) { // 页面不在内存中
            missing_page_count++;

            if (k < PM_PAGE) {   // 还有空闲物理页
                ppage_bitmap[k] = &page_table[vpage - 1];
                ppage_bitmap[k]->exist = 1;
                ppage_bitmap[k]->pmn = k;
                ppage_bitmap[k]->time = current_time;
                k++;
            }
            else {              // 需要置换
                // 找出最早进入的页面
                int min_time = ppage_bitmap[0]->time;
                int replace_idx = 0;

                for (int j = 1; j < PM_PAGE; j++) {
                    if (ppage_bitmap[j]->time < min_time) {
                        min_time = ppage_bitmap[j]->time;
                        replace_idx = j;
                    }
                }

                // 置换页面
                ppage_bitmap[replace_idx]->exist = 0;
                ppage_bitmap[replace_idx] = &page_table[vpage - 1];
                ppage_bitmap[replace_idx]->exist = 1;
                ppage_bitmap[replace_idx]->pmn = replace_idx;
                ppage_bitmap[replace_idx]->time = current_time;
            }
        }
        current_time++;
    }

    printf("FIFO算法:\n");
    printf("缺页次数: %d\t缺页率: %.2f%%\n",
        missing_page_count, (float)missing_page_count / TOTAL_INSERT * 100);
    printf("置换次数: %d\t置换率: %.2f%%\n\n",
        missing_page_count - PM_PAGE, (float)(missing_page_count - PM_PAGE) / TOTAL_INSERT * 100);
}

// LRU页面置换算法(zuijinzuijiuweishiyong)
void LRU() {
    init_data();
    int k = 0;
    int missing_page_count = 0;
    int current_time = 0;

    for (int i = 0; i < TOTAL_INSERT; i++) {
        int vpage = vpage_arr[i];

        if (page_table[vpage - 1].exist == 1) { // 页面在内存中，更新访问时间
            page_table[vpage - 1].time = current_time;
        }
        else {                              // 页面不在内存中
            missing_page_count++;

            if (k < PM_PAGE) {   // 还有空闲物理页
                ppage_bitmap[k] = &page_table[vpage - 1];
                ppage_bitmap[k]->exist = 1;
                ppage_bitmap[k]->pmn = k;
                ppage_bitmap[k]->time = current_time;
                k++;
            }
            else {              // 需要置换
                // 找出最近最久未使用的页面
                int min_time = ppage_bitmap[0]->time;
                int replace_idx = 0;

                for (int j = 1; j < PM_PAGE; j++) {
                    if (ppage_bitmap[j]->time < min_time) {
                        min_time = ppage_bitmap[j]->time;
                        replace_idx = j;
                    }
                }

                // 置换页面
                ppage_bitmap[replace_idx]->exist = 0;
                ppage_bitmap[replace_idx] = &page_table[vpage - 1];
                ppage_bitmap[replace_idx]->exist = 1;
                ppage_bitmap[replace_idx]->pmn = replace_idx;
                ppage_bitmap[replace_idx]->time = current_time;
            }
        }
        current_time++;
    }

    printf("LRU算法:\n");
    printf("缺页次数: %d\t缺页率: %.2f%%\n",
        missing_page_count, (float)missing_page_count / TOTAL_INSERT * 100);
    printf("置换次数: %d\t置换率: %.2f%%\n\n",
        missing_page_count - PM_PAGE, (float)(missing_page_count - PM_PAGE) / TOTAL_INSERT * 100);
}

// OPT页面置换算法
void OPT() {
    init_data();
    int k = 0;
    int missing_page_count = 0;

    for (int i = 0; i < TOTAL_INSERT; i++) {
        int vpage = vpage_arr[i];

        if (page_table[vpage - 1].exist == 0) { // 页面不在内存中
            missing_page_count++;

            if (k < PM_PAGE) {   // 还有空闲物理页
                ppage_bitmap[k] = &page_table[vpage - 1];
                ppage_bitmap[k]->exist = 1;
                ppage_bitmap[k]->pmn = k;
                k++;
            }
            else {              // 需要置换
                // 找出将来最长时间不被访问的页面
                int farthest = -1;
                int replace_idx = 0;

                for (int j = 0; j < PM_PAGE; j++) {
                    int l;
                    for (l = i + 1; l < TOTAL_INSERT; l++) {
                        if (vpage_arr[l] == ppage_bitmap[j]->vmn) {
                            break;
                        }
                    }

                    if (l == TOTAL_INSERT) { // 不会再被访问
                        replace_idx = j;
                        break;
                    }
                    else if (l > farthest) {
                        farthest = l;
                        replace_idx = j;
                    }
                }

                // 置换页面
                ppage_bitmap[replace_idx]->exist = 0;
                ppage_bitmap[replace_idx] = &page_table[vpage - 1];
                ppage_bitmap[replace_idx]->exist = 1;
                ppage_bitmap[replace_idx]->pmn = replace_idx;
            }
        }
    }

    printf("OPT算法:\n");
    printf("缺页次数: %d\t缺页率: %.2f%%\n",
        missing_page_count, (float)missing_page_count / TOTAL_INSERT * 100);
    printf("置换次数: %d\t置换率: %.2f%%\n\n",
        missing_page_count - PM_PAGE, (float)(missing_page_count - PM_PAGE) / TOTAL_INSERT * 100);
}

int main() {
    int choice;

    printf("页面置换算法模拟程序\n");
    printf("1. FIFO算法\n");
    printf("2. LRU算法\n");
    printf("3. OPT算法\n");
    printf("0. 退出\n");

    do {
        printf("\n请选择算法(1-3): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            FIFO();
            break;
        case 2:
            LRU();
            break;
        case 3:
            OPT();
            break;
        case 0:
            printf("程序退出\n");
            break;
        default:
            printf("无效选择!\n");
        }
    } while (choice != 0);

    return 0;
}
