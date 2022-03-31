#include <iostream>
#include <cstring>

enum Gender {
    Male = 1,
    Female = 2,
};


class Student {
public:

    void setName(const char *newName);

    void setFacultyNumber(const int newFacultyNumber);

    void setAge(const int newAge);

    void setGender(Gender newGender);

    void setEmail(const char *newEmail);

    void setGrade(const double newGrade);

    void setField(const char *field, const char *newValue);

    bool isDataValid() const;

    char *getName();

    int getFacultyNumber() const;

    int getAge() const;

    Gender getGender() const;

    char *getEmail();

    double getGrade() const;

    void print();

private:
    char name[25];
    int facultyNumber;
    int age;
    Gender gender;
    char email[25];
    double grade;

};

struct StudentCollection {
    Student *students;
    size_t count;

    Student &getStudentRecord(int fac_num) const;

    void sort(char *field);
};
