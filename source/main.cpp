//
// Created by hattonjd on 5/3/2023.
//
#include <HugeInt.h>
#include <iostream>

int main()
{
    HugeInt lrgNum("999999999999999999");
    HugeInt lrgNum2("1");

    HugeInt res = lrgNum + lrgNum2;

    std::cout << res << std::endl;
    return 0;
}