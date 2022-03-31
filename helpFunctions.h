#include<iostream>
#include <fstream>

double convertStrToDouble(const char *str);

size_t getFileSize(std::fstream &file);

size_t getLength(const char *str);

bool isPrefix(const char *str1, const char *str2);

int getEndOfStringIndex(const char *str1, const char *str2);