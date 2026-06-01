//#include <stdio.h>
//#include <stdlib.h>
//
//#define TOTAL_MEMORY 640
//
//typedef struct SubArea {
//    int start_addr;
//    int size;
//    struct SubArea* next;
//} SubArea;
//
//SubArea* free_head = NULL;
//
//// --- 基础功能函数 (保持不变) ---
//
//void init_memory() {
//    // 清理之前的链表（防止内存泄漏）
//    SubArea* p = free_head;
//    while (p != NULL) {
//        SubArea* temp = p;
//        p = p->next;
//        free(temp);
//    }
//
//    // 初始化新的
//    free_head = (SubArea*)malloc(sizeof(SubArea));
//    free_head->start_addr = 0;
//    free_head->size = TOTAL_MEMORY;
//    free_head->next = NULL;
//}
//
//void print_memory() {
//    SubArea* p = free_head;
//    if (p == NULL) {
//        printf("    [当前状态]: 内存全满，无空闲区\n");
//    }
//    else {
//        printf("    [当前空闲链表]: ");
//        while (p != NULL) {
//            printf("| 地址:%d 大小:%d | -> ", p->start_addr, p->size);
//            p = p->next;
//        }
//        printf("NULL\n");
//    }
//}
//
//// 简单的分配辅助函数（用于构建环境，不打印多余信息）
//void internal_alloc(int request_size) {
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    while (p != NULL) {
//        if (p->size >= request_size) {
//            if (p->size == request_size) {
//                if (prev == NULL) free_head = p->next;
//                else prev->next = p->next;
//                free(p);
//            }
//            else {
//                p->start_addr += request_size;
//                p->size -= request_size;
//            }
//            return;
//        }
//        prev = p;
//        p = p->next;
//    }
//}
//
//// 核心算法：首次适应
//int alloc_first_fit(int request_size) {
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    while (p != NULL) {
//        if (p->size >= request_size) {
//            int addr = p->start_addr;
//            if (p->size == request_size) {
//                if (prev == NULL) free_head = p->next;
//                else prev->next = p->next;
//                free(p);
//            }
//            else {
//                p->start_addr += request_size;
//                p->size -= request_size;
//            }
//            return addr;
//        }
//        prev = p;
//        p = p->next;
//    }
//    return -1;
//}
//
//// 核心算法：最佳适应
//int alloc_best_fit(int request_size) {
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    SubArea* best_p = NULL;
//    SubArea* best_prev = NULL;
//    int min_diff = TOTAL_MEMORY + 1;
//
//    while (p != NULL) {
//        if (p->size >= request_size) {
//            int diff = p->size - request_size;
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
//        if (best_p->size == request_size) {
//            if (best_prev == NULL) free_head = best_p->next;
//            else best_prev->next = best_p->next;
//            free(best_p);
//        }
//        else {
//            best_p->start_addr += request_size;
//            best_p->size -= request_size;
//        }
//        return addr;
//    }
//    return -1;
//}
//
//// 核心算法：回收
//void free_memory(int start_addr, int size) {
//    SubArea* new_node = (SubArea*)malloc(sizeof(SubArea));
//    new_node->start_addr = start_addr;
//    new_node->size = size;
//    new_node->next = NULL;
//
//    if (free_head == NULL) {
//        free_head = new_node;
//        return;
//    }
//
//    SubArea* p = free_head;
//    SubArea* prev = NULL;
//    while (p != NULL && p->start_addr < start_addr) {
//        prev = p;
//        p = p->next;
//    }
//
//    if (prev == NULL) {
//        new_node->next = free_head;
//        free_head = new_node;
//    }
//    else {
//        new_node->next = p;
//        prev->next = new_node;
//    }
//
//    // 合并逻辑略微简化，因为此演示场景主要测试分配
//    // 但为了严谨，保留向后合并
//    if (new_node->next != NULL &&
//        new_node->start_addr + new_node->size == new_node->next->start_addr) {
//        SubArea* temp = new_node->next;
//        new_node->size += temp->size;
//        new_node->next = temp->next;
//        free(temp);
//    }
//}
//
//// --- 自动化测试构建函数 ---
//
//void build_test_environment() {
//    init_memory();
//    // 1. 先填满内存
//    // 分配 300 (0-300)
//    internal_alloc(300);
//    // 分配 100 (300-400) -> 这个将保留为占用，把前后隔开
//    internal_alloc(100);
//    // 分配 150 (400-550)
//    internal_alloc(150);
//    // 分配 90 (550-640)
//    internal_alloc(90);
//
//    // 此时内存全满。
//
//    // 2. 挖洞（模拟回收）
//    // 回收 0-300 (造出第一个大洞)
//    free_memory(0, 300);
//    // 回收 400-550 (造出第二个小洞)
//    free_memory(400, 150);
//
//    printf("\n>>> 环境构建完成 (有两个空闲区: 300KB 和 150KB) <<<\n");
//    print_memory();
//}
//
//int main() {
//    int addr;
//
//    printf("============================================\n");
//    printf("      动态分区分配算法对比演示\n");
//    printf("============================================\n");
//
//    // -------------------------------------------------
//    // 测试 1：首次适应算法
//    // -------------------------------------------------
//    printf("\n\n=== 测试场景 1: 首次适应算法 (First Fit) ===\n");
//    build_test_environment(); // 重置并构建环境
//
//    printf("\n[操作]: 请求分配 100KB ...\n");
//    addr = alloc_first_fit(100);
//
//    printf("[结果]: 分配到的起始地址为: %d\n", addr);
//    printf("[分析]: 300KB的空闲块就在开头，够大，所以它直接占用了地址 0。\n");
//    print_memory();
//
//    // -------------------------------------------------
//    // 测试 2：最佳适应算法
//    // -------------------------------------------------
//    printf("\n\n\n=== 测试场景 2: 最佳适应算法 (Best Fit) ===\n");
//    build_test_environment(); // 重置并构建完全一样的环境
//
//    printf("\n[操作]: 请求分配 100KB ...\n");
//    addr = alloc_best_fit(100);
//
//    printf("[结果]: 分配到的起始地址为: %d\n", addr);
//    printf("[分析]: 虽然地址0有300KB，但算法发现地址400的150KB\n");
//    printf("       更接近需求(只浪费50KB)，所以跳过大块，选择了小块。\n");
//    print_memory();
//
//    printf("\n============================================\n");
//    printf("演示结束。按任意键退出。\n");
//    getchar();
//    return 0;
//}