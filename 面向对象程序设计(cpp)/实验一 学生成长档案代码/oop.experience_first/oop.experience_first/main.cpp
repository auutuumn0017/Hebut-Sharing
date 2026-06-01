#include <iostream>
#include <vector>
#include "Student development file.h"
using namespace std;

float Grade::total_grade[MAX_COURSES] = { 0 };
int Grade::stu_count = 0;

void displayMenu() {
    cout << endl;
    cout << "==== 学生信息管理系统 ====" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 显示所有学生信息" << endl;
    cout << "3. 查看具体科目的平均分" << endl;
    cout << "0. 退出" << endl;
    cout << "请选择操作: ";
}

void displayAllProfiles(const vector<Profile>& profiles) {
    if (profiles.empty()) {
        cout << "暂无学生信息。" << endl;
        return;
    }

    cout << "学生信息列表：" << endl;
    for (const auto& profile : profiles) {
        cout << profile;  
    }
}

int main() {
    int stuCount = 0;
    int stu_n;

    cout << "请输入你要登记的学生总数: ";
    cin >> stu_n;

    vector<Profile> profiles;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:  // 添加学生
            if (stuCount < stu_n) {
                cout << "请输入第" << (stuCount + 1) << "个学生的信息:" << endl;

                string id, name;
                int age, grade;

                // 捕获学号输入异常
                try {
                    cout << "学号 姓名 年龄 年级: ";
                    cin >> id >> name >> age >> grade;

                    // 检查学号是否大于25000
                    if (stoi(id) > 25000) {
                        throw InvalidIDException("学号不能大于25000！");
                    }

                    // 创建学生对象
                    Student student(id, name, age, grade);

                    // 成绩输入
                    float ma, ds, oop;
                    cout << "请输入数学、数据结构、C++成绩: ";
                    cin >> ma >> ds >> oop;
                    Grade grades;
                    grades.add("Mathematics", ma);
                    grades.add("Data Structure", ds);
                    grades.add("Object Oriented Programming", oop);

                    // 能力输入
                    Ability abilities;
                    int n;
                    cout << "请输入该学生的能力数与能力名称:" << endl;
                    cin >> n;
                    string ability;
                    for (int j = 0; j < n; j++) {
                        cin >> ability;
                        abilities.add(ability);
                    }

                    profiles.push_back(Profile(student, grades, abilities));
                    stuCount++;
                    cout << "学生信息添加成功!" << endl;
                }
                catch (const InvalidIDException& e) {
                    cout << "输入错误: " << e.what() << endl;
                }
                catch (const exception& e) {
                    cout << "发生异常: " << e.what() << endl;
                }
            }
            else {
                cout << "学生数量已满，无法添加新学生!" << endl;
            }
            break;

        case 2:  // 显示所有学生信息
            displayAllProfiles(profiles);
            break;

        case 3:  // 查看具体科目的平均分
            Grade::average_class();
            break;

        case 0:  // 退出
            cout << "退出系统。" << endl;
            return 0;

        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
    }
}
