#include <iostream>
#include <string>
#include <stdexcept>
  
using namespace std;

const int MAX_COURSES = 5;
const int MAX_SKILLS = 5;
const int MAX_STUDENT = 5;

class Person {
protected:
    string name;
    int age;

public:
    Person() : name("无名"), age(0) {}
    Person(string nm, int a) : name(nm), age(a) {}

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << "name: " << p.name << endl
            << "age: " << p.age << endl;
        return os;
    }
};

class Student : public Person {
private:
    string studentID;
    int grade;

public:
    Student() : studentID("未知"), grade(0) {}
    Student(string id, string nm, int a, int g) : Person(nm, a), studentID(id), grade(g) {}

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "--基本信息--" << endl
            << "studentID: " << s.studentID << endl;
        os << static_cast<const Person&>(s);  // 调用Person的输出流运算符
        os << "grade: " << s.grade << endl << endl;
        return os;
    }
};

class Grade {
private:
    string courses[MAX_COURSES];
    float grades[MAX_COURSES];
    int count = 0;
    float sum = 0;
    static float total_grade[MAX_STUDENT];
    static int stu_count;

public:
    Grade() : count(0) {}

    void add(string course, float grade) {
        if (count < MAX_COURSES) {
            courses[count] = course;
            grades[count] = grade;
            sum += grade;
            total_grade[count] += grades[count];
            count++;
            stu_count++;
        }
    }

    static void average_class() {
        cout << endl << "Class Grade:" << endl << "--每门课程的平均分--" << endl;
        for (int i = 0; i < 3; i++) {
            if (stu_count > 0) {
                cout << "课程" << (i + 1) << "的平均分: " << (total_grade[i] / (stu_count / 3)) << endl;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Grade& g) {
        os << "--成绩单--" << endl;
        for (int i = 0; i < g.count; i++) {
            os << g.courses[i] << ": " << g.grades[i] << endl;
        }
        os << "average: " << (g.sum / g.count) << endl << endl;
        return os;
    }
};

class Ability {
private:
    string skills[MAX_SKILLS];
    int count;

public:
    Ability() : count(0) {}

    void add(string skill) {
        if (count < MAX_SKILLS) {
            skills[count] = skill;
            count++;
        }
    }

    friend ostream& operator<<(ostream& os, const Ability& a) {
        os << "--能力--" << endl;
        for (int i = 0; i < a.count; i++) {
            os << a.skills[i] << endl;
        }
        return os;
    }
};

class Profile {
private:
    Student student;
    Grade grades;
    Ability abilities;

public:
    Profile() : student(), grades(), abilities() {}
    Profile(Student s, Grade g, Ability a) : student(s), grades(g), abilities(a) {}

    friend ostream& operator<<(ostream& os, const Profile& p) {
        os << "Student Growth Profile:" << endl;
        os << p.student;     
        os << p.grades;      
        os << p.abilities;   
        return os;
    }
};

class InvalidIDException : public runtime_error {
public:
    InvalidIDException(const string& msg) : runtime_error(msg) {}
};
