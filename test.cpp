//
// Created by lemito on 6/17/24.
//



#include <iostream>

int main(void){
    int* test = new int;

    *test = 10;

    int second = 10;
    int & surname = second;

    int* addres_second = &second;

    surname = 15;

    std::cout << surname << "\n";
    std::cout << second << "\n";
    delete(test);


    std::cout << "Qq\n";

    return 0;
}