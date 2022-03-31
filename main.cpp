#include <iostream>
#include "Student.h"
#include "helpFunctions.h"

int main() {
    const size_t LEN = 1024;
    std::cout << "Enter a file path:" << std::endl;
    char path[LEN];
    std::cout << '>';
    std::cin >> path;
    std::fstream file(path, std::ios::in);
    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 0;
    }

    bool openedEntry = false;
    auto *student = new Student();
    StudentCollection collection{};
    collection.count = 0;
    collection.students = new Student[getFileSize(file) / 172]; //each student is at most 172 bytes long
    int lastIndex;


    while (!file.eof()) {
        char line[LEN];
        file.getline(line, LEN);
        lastIndex = 0;
        if (!openedEntry)
            lastIndex = getEndOfStringIndex("<student>", line);
        size_t lineLength = getLength(line);

        if (lastIndex == -1)
            continue;
        openedEntry = true;
        for (size_t i = lastIndex; i < lineLength; i++) {
            if (line[i] != '<')
                continue;
            if (line[i] == '<' && line[i + 1] == '\\') {
                continue;
            }
            size_t j = i + 1, index = 0;
            char field[7];
            while (line[j] != '>') {
                field[index] = line[j];
                j++;
                index++;
            }
            field[index] = '\0';
            j++;
            char data[25];
            index = 0;
            while (line[j] != '<' && line[j] != '\0') {
                data[index] = line[j];
                j++;
                index++;
            }
            data[index] = '\0';
            if (field[0] != '\0' && data[0] != '\0') {
                student->setField(field, data);

                openedEntry = true;
            }
        }
        if (student->isDataValid() && getEndOfStringIndex("<\\student>", line) != -1) {
            collection.students[collection.count] = *student;
            collection.count++;
            openedEntry = false;
            student = new Student();
        }
    }
    file.close();

    char input[LEN];

    while (!isPrefix("save", input)) {
        std::cout << ">";
        std::cin.getline(input, LEN);

        int index = getEndOfStringIndex("edit", input);
        if (index != -1) {
            int fn = 0;
            char field[7];
            char value[25];
            int space_counter = 0;
            size_t counter = 0;
            size_t len = getLength(input);
            for (int i = index + 1; i < len; i++) {
                if (input[i] == ' ') {
                    if (space_counter == 1)
                        field[counter] = '\0';
                    counter = 0;
                    space_counter++;
                    continue;
                }
                if (space_counter == 0) {
                    fn = fn * 10 + (input[i] - '0');
                } else if (space_counter == 1) {
                    field[counter] = input[i];
                    counter++;
                } else if (space_counter == 2) {
                    value[counter] = input[i];
                    counter++;
                }
            }
            value[counter] = '\0';
            Student &edited_student = collection.getStudentRecord(fn);
            edited_student.setField(field, value);
        }

        if (isPrefix("print", input)) {
            int fn = 0;
            size_t counter = 0;
            size_t len = getLength(input);
            for (int i = 6; i < len; i++) {
                if (input[i] == ' ') {
                    break;
                }
                fn = fn * 10 + (input[i] - '0');
            }
            Student &edited_student = collection.getStudentRecord(fn);
            edited_student.print();
        }

        if (isPrefix("sort", input)) {
            size_t counter = 0;
            size_t len = getLength(input);
            char field[7];
            for (int i = 5; i < len; i++) {
                if (input[i] == ' ') {
                    break;
                }
                field[counter] = input[i];
                counter++;
            }
            field[counter] = '\0';
            collection.sort(field);
        }

    }

    std::fstream writeFile(path, std::ios::trunc | std::ios::out);
    if (!writeFile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 0;
    }
    for (int i = 0; i < collection.count; ++i) {
        writeFile << "<student>" << std::endl;
        writeFile << '\t' << "<fn>" << collection.students[i].getFacultyNumber() << "<\\fn>" << std::endl;
        writeFile << '\t' << "<name>" << collection.students[i].getName() << "<\\name>" << std::endl;
        writeFile << '\t' << "<grade>" << collection.students[i].getGrade() << "<\\grade>" << std::endl;
        writeFile << '\t' << "<email>" << collection.students[i].getEmail() << "<\\email>" << std::endl;
        writeFile << '\t' << "<age>" << collection.students[i].getAge() << "<\\age>" << std::endl;
        if (collection.students[i].getGender() == 1)
            writeFile << '\t' << "<gender>Male<\\gender>" << std::endl;
        if (collection.students[i].getGender() == 2)
            writeFile << '\t' << "<gender>Female<\\gender>" << std::endl;
        writeFile << "<\\student>" << std::endl;
        writeFile << std::endl;
    }
    writeFile.close();
    delete[] collection.students;

    return 0;
}
