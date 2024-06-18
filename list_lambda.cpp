#include <iostream>
#include <list>

// Считаем, что список и итераторы у нас есть, но для экономии времени я буду использовать С++ и std::list
// и этот метод ленивый -- все числа из списка просто превращаются в int, а дальше происходит обычная операция

int main()
{
    std::list<int> numbers{ 2 };
    numbers.push_back(5);

    std::cout << "[ ";
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter){
        std::cout << *iter << " ";
    }
    std::cout << "]";
    std::cout << std::endl;

    int8_t lambda = 4;
    int32_t res = 0;
    int32_t mult = 1;
    for (auto iter = --numbers.end(); ; --iter)
    {
        res += *iter * mult;
        mult*=10;
        if (iter == numbers.begin()) break;
    }
    std::cout << res*lambda << std::endl;

}
