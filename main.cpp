
// #include <vector>
// #include "vector.hpp"
#include <string>
#include <vector>
#include <iterator>
#include <iostream>

// template<class Iter>
// class iteratoratoratorator
// {
//     public:
//         typedef typename Iter::data_type    itertype;
//         std::vector a;

// };

using namespace std;

 
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
  vector<int> first;

  int myints[] = {1776,7,4};
  first.assign (myints,myints+3);  

  vector<int>::reverse_iterator rit = vector<int>::reverse_iterator(first.begin());
  cout << *(rit.base()) << endl;


//   it=first.begin()+1;

//   second.assign (it,first.end()-1); // the 5 central values of first

//   int myints[] = {1776,7,4};
//   third.assign (myints,myints+3);   // assigning from array.

//     print_container(first);
//     first.assign (20, 5);
//     print_container(first); 

  return 0;
}