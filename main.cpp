
// #include <vector>
// #include "vector.hpp"
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include "avl_tree.hpp"

// template<class Iter>
// class iteratoratoratorator
// {
//     public:
//         typedef typename Iter::data_type    itertype;
//         std::vector a;

// };

// using namespace std;

 
// void print_container(vector<int>& vec) 
// {
//     std::cout << "capacity :" << vec.capacity() << " size : " << vec.size() << std::endl;
//     for(vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
//         std::cout << *i << ' ';
//     std::cout << '\n';
// }

// int main()
// {
//     //std::cout << "hello"<< std::endl;
    // ft::vector<std::string> v1(10, "string1");
    // ft::vector<std::string> v2(10, "string2");
    // v1 = v2;
    // print_container(v1);

    // // vector<std::string> vec1(5, "42");
    // print_container(v2);


    //vec.resize(5,"hello");
    // print_container(vec);
    //std::cout << vec.capacity() << std::endl;
    //vec.resize(15,"world");
    //print_container(vec);
    // std::cout << vec.capacity() << std::endl;
    // vec.insert(vec.end(), arr + 7 , arr + 9);
    // vector<std::string>::const_iterator i = vec.begin();
    
    // std::cout << *i << std::endl;
    // print_container(vec);
    // std::cout << vec.capacity() << std::endl;
    //vec.erase(vec.begin() + 2 , vec.end());
    //std::cout << vec.capacity() << std::endl;

    // i =  1 + i;
    // std::cout << *i << std::endl;

    

    // vector<int>::iterator i2(arr + 5);
    // vector<int> a(i1, i2 + 5);
    // std::cout << *(a.begin()) << std::endl;
    // i = 2 + i;
    // i = 1 - i;
    // std::cout << *i << std::endl;

    
// }

// vector assign
// #include <iostream>
// #include <vector>

int main ()
{
  avl_node<int> t(5);
  t.insert_value(2);
  t.insert_value(12);
  t.insert_value(10);
  t.insert_value(20);

  t.print_tree();
  t.rotate_left();
  t.rotate_right();
  t.print_tree();

  return 0;
}
