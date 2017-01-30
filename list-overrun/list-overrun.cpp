// Juliet CWE476_NULL_Pointer_Dereference__char_73b.cpp
// Structure: list-overrun

#include <list>

void good(std::list<char *> dataList)
{
    // Tool C FP: Buffer Overrun. This code reads past the end of the buffer pointed to by dataList.back()...
    // Tool B FP: none
    // Tool A FP: none
    char * data = dataList.back();
}

int main(void)
{
    char * str = "Good";

    std::list<char *> dataList;
    dataList.push_back(str);

    good(dataList);
    return 0;
}