//#include <stdio.h>
//#include <stdlib.h>
//
//#define TOTAL_MEMORY 640
//
//// --- 结构体定义 ---
//typedef struct SubArea {
//    int start_addr;       // 分区的起始地址
//    int size;             // 分区的大小
//    struct SubArea* next; // 指向下一个空闲分区的指针
//} SubArea;
//
//// --- 全局变量 ---
//// job_addr数组：用于“记住”每个作业被分配到了哪个地址。
//// 例如 job_addr[1] = 130 表示作业1存放在地址130处。
//// 如果值为 -1，表示该作业当前不在内存中。
//int job_addr[10];
//
//// free_head：空闲分区链表的头指针，永远指向第一个空闲块。
//SubArea* free_head = NULL;
//
//// --- 基础操作 ---
//
//// 初始化/重置环境
//void init() {
//    // 清空链表
//    SubArea* p = free_head;
//    while (p != NULL) {
//        SubArea* temp = p;
//        p = p->next;
//        free(temp);
//    }
//    // 重置作业地址记录
//    for (int i = 0; i < 10; i++) job_addr[i] = -1;
//
//    // 创建初始空闲块
//    free_head = (SubArea*)malloc(sizeof(SubArea));
//    free_head->start_addr = 0;
//    free_head->size = TOTAL_MEMORY;
//    free_head->next = NULL;
//}
//
//// 打印当前空闲链表
//void print_free_list() {
//    SubArea* p = free_head;
//    printf("   -> 空闲链表: ");
//    if (p == NULL) printf("无 (内存全满)");
//    while (p != NULL) {
//        printf("[地址:%d, 大小:%d] ", p->start_addr, p->size);
//        if (p->next != NULL) printf("-> ");
//        p = p->next;
//    }
//    printf("\n");
//}
//
//// --- 核心算法 ---
//
//// 首次适应分配 (First Fit)
//int alloc_FF(int size) {
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    while (p != NULL) {
//        if (p->size >= size) { // 找到第一个能放下的
//            int addr = p->start_addr;
//            if (p->size == size) { // 刚好填满
//                if (prev == NULL) free_head = p->next;
//                else prev->next = p->next;
//                free(p);
//            }
//            else { // 切割
//                p->start_addr += size;
//                p->size -= size;
//            }
//            return addr;
//        }
//        prev = p;
//        p = p->next;
//    }
//    return -1; // 分配失败
//}
//
//// 最佳适应分配 (Best Fit)
//int alloc_BF(int size) {
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    SubArea* best_p = NULL;
//    SubArea* best_prev = NULL;
//    int min_diff = TOTAL_MEMORY + 1;
//
//    // 遍历所有块寻找最合适的
//    while (p != NULL) {
//        if (p->size >= size) {
//            int diff = p->size - size;
//            if (diff < min_diff) {
//                min_diff = diff;
//                best_p = p;
//                best_prev = prev;
//            }
//        }
//        prev = p;
//        p = p->next;
//    }
//
//    if (best_p != NULL) {
//        int addr = best_p->start_addr;
//        if (best_p->size == size) {
//            if (best_prev == NULL) free_head = best_p->next;
//            else best_prev->next = best_p->next;
//            free(best_p);
//        }
//        else {
//            best_p->start_addr += size;
//            best_p->size -= size;
//        }
//        return addr;
//    }
//    return -1;
//}
//
//// 回收内存 (通用)
//void free_mem(int addr, int size) {
//    if (addr == -1) {
//        printf("   [错误] 无法回收，因为之前的分配失败了。\n");
//        return;
//    }
//
//    SubArea* new_node = (SubArea*)malloc(sizeof(SubArea));
//    new_node->start_addr = addr;
//    new_node->size = size;
//    new_node->next = NULL;
//
//    // 1. 寻找插入位置 (按地址排序)
//    if (free_head == NULL) {
//        free_head = new_node;
//        return;
//    }
//
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    while (p != NULL && p->start_addr < addr) {
//        prev = p;
//        p = p->next;
//    }
//
//    // 插入
//    if (prev == NULL) {
//        new_node->next = free_head;
//        free_head = new_node;
//    }
//    else {
//        new_node->next = p;
//        prev->next = new_node;
//    }
//
//    // 2. 合并操作 (向后合并)
//    if (new_node->next != NULL &&
//        new_node->start_addr + new_node->size == new_node->next->start_addr) {
//        SubArea* temp = new_node->next;
//        new_node->size += temp->size;
//        new_node->next = temp->next;
//        free(temp);
//    }
//
//    // 3. 合并操作 (向前合并)
//    // 注意：此时 prev 指向 new_node 的前驱
//    if (prev != NULL &&
//        prev->start_addr + prev->size == prev->next->start_addr) { // prev->next 就是 new_node
//        SubArea* temp = prev->next;
//        prev->size += temp->size;
//        prev->next = temp->next;
//        free(temp);
//    }
//}
//
//// --- 模拟控制 ---
//
//void run_step_alloc(int step, int job_id, int size, int alg_type) {
//    printf("Step %d: [作业%d] 申请 %dKB -> ", step, job_id, size);
//    int addr = (alg_type == 1) ? alloc_FF(size) : alloc_BF(size);
//
//    if (addr != -1) {
//        job_addr[job_id] = addr; // 记录地址以便后续回收
//        printf("成功 (地址: %d)\n", addr);
//    }
//    else {
//        printf("失败 (内存不足)\n");
//    }
//    print_free_list();
//}
//
//void run_step_free(int step, int job_id, int size) {
//    printf("Step %d: [作业%d] 释放 %dKB -> ", step, job_id, size);
//    free_mem(job_addr[job_id], size);
//    printf("完成\n");
//    print_free_list();
//    job_addr[job_id] = -1; // 标记为已回收
//}
//
//void run_simulation(int alg_type) {
//    init();
//    printf("\n======================================================\n");
//    if (alg_type == 1) printf("       算法演示: 首次适应算法 (First Fit)\n");
//    else               printf("       算法演示: 最佳适应算法 (Best Fit)\n");
//    printf("======================================================\n");
//    print_free_list();
//    printf("------------------------------------------------------\n");
//
//    // 按照题目要求的序列执行
//    run_step_alloc(1, 1, 130, alg_type);
//    run_step_alloc(2, 2, 60, alg_type);
//    run_step_alloc(3, 3, 100, alg_type);
//    run_step_free(4, 2, 60);
//    run_step_alloc(5, 4, 200, alg_type);
//    run_step_free(6, 3, 100);
//    run_step_free(7, 1, 130);
//    run_step_alloc(8, 5, 140, alg_type); // *** 关键分歧点 ***
//    run_step_alloc(9, 6, 60, alg_type);
//    run_step_alloc(10, 7, 50, alg_type);
//    run_step_free(11, 6, 60);
//}
//
//int main() {
//    run_simulation(1); // 运行首次适应
//    run_simulation(2); // 运行最佳适应
//    return 0;
//}