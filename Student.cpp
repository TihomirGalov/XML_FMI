#include<iostream>
#include "Student.h"
#include "helpFunctions.h"


void Student::setName(const char *newName) {
    size_t i = 0;
    while (newName[i] != '\0') {
        this->name[i] = newName[i];
        i++;
    }
    if (i > 24) {
        this->name[0] = '\0';
        std::cout << "Name is too long!" << std::endl;
        return;
    }
    this->name[i] = '\0';
}

void Student::setFacultyNumber(const int newFacultyNumber) {
    this->facultyNumber = newFacultyNumber;
}

void Student::setAge(const int newAge) {
    if (newAge < 15 || newAge > 65) {
        std::cout << "Invalid age!" << std::endl;
        return;
    }
    this->age = newAge;
}

void Student::setGender(Gender newGender) {
    this->gender = newGender;
}

void Student::setEmail(const char *newEmail) {
    size_t i = 0;
    bool hasAt = false;
    char oldEmail[25];

    while (newEmail[i] != '\0') {
        if (newEmail[i] == '@')
            hasAt = true;
        oldEmail[i] = this->email[i];
        this->email[i] = newEmail[i];
        i++;

    }
    if (i > 24 || !hasAt) {
        i = 0;
        while (oldEmail[i] != '\0') {
            this->email[i] = oldEmail[i];
            i++;
        }
        std::cout << "Email is invalid!" << std::endl;
        return;
    }
    this->email[i] = '\0';
}

void Student::setGrade(const double newGrade) {
    if (newGrade < 2.00 || newGrade > 6.00) {
        std::cout << "Invalid grade!" << std::endl;
        return;
    }
    this->grade = newGrade;
}

void Student::setField(const char *field, const char *newValue) {
    if (isPrefix(field, "name")) {
        setName(newValue);
    } else if (isPrefix(field, "fn")) {
        setFacultyNumber(atoi(newValue));
    } else if (isPrefix(field, "age")) {
        setAge(atoi(newValue));
    } else if (isPrefix(field, "gender")) {
        if (isPrefix("Male", newValue))
            setGender(Male);
        else
            setGender(Female);
    } else if (isPrefix(field, "email")) {
        setEmail(newValue);
    } else if (isPrefix(field, "grade")) {
        setGrade(convertStrToDouble(newValue));
    }
}

bool Student::isDataValid() const {
    return name[0] != '\0' && facultyNumber > 0 && age > 0 && email[0] != '\0' && grade > 1.99 && grade < 7.00 &&
           (gender == Male || gender == Female);
}

char *Student::getName() {
    return this->name;
}

int Student::getFacultyNumber() const {
    return this->facultyNumber;
}

int Student::getAge() const {
    return this->age;
}

Gender Student::getGender() const {
    return this->gender;
}

char *Student::getEmail() {
    return this->email;
}

double Student::getGrade() const {
    return this->grade;
}

void Student::print() {
    std::cout << "--------Start-------" << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "FN: " << this->getFacultyNumber() << std::endl;
    std::cout << "Age: " << this->getAge() << std::endl;
    std::cout << "Gender: " << this->getGender() << std::endl;
    std::cout << "Email: " << this->getEmail() << std::endl;
    std::cout << "Grade: " << this->getGrade() << std::endl;
    std::cout << "---------End-------" << std::endl;
}

Student &StudentCollection::getStudentRecord(int fac_num) const {
    for (int i = 0; i < count; i++) {
        if (students[i].getFacultyNumber() == fac_num)
            return students[i];
    }
}

void StudentCollection::sort(char *field) {
    bool name = false, fn = false, gender = false, email = false, grade = false, age = false;
    if (isPrefix(field, "name")) {
        name = true;
    } else if (isPrefix(field, "fn")) {
        fn = true;
    } else if (isPrefix(field, "grade")) {
        grade = true;
    } else if (isPrefix(field, "gender")) {
        gender = true;
    } else if (isPrefix(field, "email")) {
        email = true;
    } else if (isPrefix(field, "age")) {
        age = true;
    }
    if (fn || gender || age) {
        int values[count];

        for (int i = 0; i < count; i++) {
            if (fn) values[i] = students[i].getFacultyNumber();
            if (gender) values[i] = students[i].getGender();
            if (grade) values[i] = students[i].getGrade();
            if (age) values[i] = students[i].getAge();
        }

        for (int i = 0; i < count; i++) {
            int min = i;
            for (int j = i + 1; j < count; j++) {
                if (values[j] < values[min])
                    min = j;
            }
            Student temp = students[i];
            students[i] = students[min];
            students[min] = temp;
            int tempVal = values[i];
            values[i] = values[min];
            values[min] = tempVal;
        }
    } else if(email || name) {
        char *values[count];

        for (int i = 0; i < count; i++) {
            if (email) values[i] = students[i].getEmail();
            if (name) values[i] = students[i].getName();
        }

        for (int i = 0; i < count; i++) {
            int min = i;
            for (int j = i + 1; j < count; j++) {
                if (strcmp(values[j], values[min]) < 0)
                    min = j;
            }
            Student temp = students[i];
            students[i] = students[min];
            students[min] = temp;
            char *tempVal = values[i];
            values[i] = values[min];
            values[min] = tempVal;
        }
    } else if(grade) {
        for (int i = 0; i < count; i++) {
            int min = i;
            for (int j = i + 1; j < count; j++) {
                if (students[j].getGrade() < students[min].getGrade())
                    min = j;
            }
            Student temp = students[i];
            students[i] = students[min];
            students[min] = temp;
        }
    }
}