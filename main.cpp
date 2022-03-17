
// #include <vector>
#include "vector.hpp"
#include <string>
#include <vector>
#include <iostream>

// template<class Iter>
// class iteratoratoratorator
// {
//     public:
//         typedef typename Iter::data_type    itertype;
//         std::vector a;

// };

using namespace std;

 
void print_container(vector<std::string>& vec) 
{
    for(vector<std::string>::iterator i = vec.begin(); i != vec.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';
}

int main()
{
    //std::cout << "hello"<< std::endl;
    std::string arr[] = {"hello", "hello1", "hello2", "hello3", "hello4", "hello5", "hello6"};
    //std::cout << a.size() << std::endl;
    vector<std::string> vec (arr, arr + 6);
    print_container(vec);
    vector<std::string>::iterator a = vec.erase(vec.begin() + 4, vec.begin() + 7);
    std::cout << *a << std::endl;
    print_container(vec);

    // i =  1 + i;
    // std::cout << *i << std::endl;

    

    // vector<int>::iterator i2(arr + 5);
    // vector<int> a(i1, i2 + 5);
    // std::cout << *(a.begin()) << std::endl;
    // i = 2 + i;
    // i = 1 - i;
    // std::cout << *i << std::endl;

    
}
