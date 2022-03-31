#include<iostream>
#include<fstream>

double convertStrToDouble(const char *str) {
    size_t i = 0;
    double output = 0;
    bool addDecimal = false;
    double decimalIndex = 10;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            i++;
            addDecimal = true;
            continue;
        }

        if (addDecimal) {
            output = output + (double) (str[i] - '0') / decimalIndex;
            decimalIndex *= 10;
        } else
            output = output * 10 + (int) (str[i]) - '0';

        i++;

    }
    return output;

}

size_t getFileSize(std::fstream &file) {
    size_t currentPosition = file.tellg();

    file.seekg(0, std::ios::end);
    size_t result = file.tellg();
    file.seekg(currentPosition);
    return result;
}

size_t getLength(const char *str) {
    size_t counter = 0;
    while (str[counter] != '\0')
        counter++;
    return counter;
}

bool isPrefix(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        i++;

    }
    return str1[i] == '\0';
}

int getEndOfStringIndex(const char *str1,
                        const char *str2) { //if str1 not in -1 else the index of the last char of str1 in str2
    size_t i = 0;
    while (str1[i] != '\0') {
        if (isPrefix(str1 + i, str2))
            return i + getLength(str1);
        i++;
    }
    return -1;
}