
// #include <vector>
// #include "vector.hpp"
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include "avl_tree.hpp"
#include "utils.hpp"


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
template <typename T>
void   print(avl_node<T> *root, int space) {
            if (root == NULL)
                return;
            space += 8;
            print(root->_right, space);
            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << root->_value.first << std::endl;
            print(root->_left, space);
}

int main ()
{

  ft::pair<int, int> a = ft::make_pair(50,21);
  ft::pair<int, int> b = ft::make_pair(25,19);
  ft::pair<int, int> c = ft::make_pair(35,22);
  // ft::pair<int, int> d = ft::make_pair(57,23);
  // ft::pair<int, int> e = ft::make_pair(16,18);
  // ft::pair<int, int> f = ft::make_pair(17,18);
  // ft::pair<int, int> g = ft::make_pair(10,18);
  // ft::pair<int, int> h = ft::make_pair(11,18);
  // ft::pair<int, int> i = ft::make_pair(9,18);
  // ft::pair<int, int> j = ft::make_pair(8,18);
  // ft::pair<int, int> k = ft::make_pair(7,18);


  avl_tree<ft::pair<int, int> > t(a);
  t.insert_value(t._root,b);
  t.insert_value(t._root,c);
  // t.insert_value(t._root,d);
  // t.insert_value(t._root,e);
  // t.insert_value(t._root,f);
  // t.insert_value(t._root,g);
  // t.insert_value(t._root,h);
  // t.insert_value(t._root,i);
  // t.insert_value(t._root,j);
  // t.insert_value(t._root,k);

  print(t._root,4);
  // t.rotate_left();
  // t.rotate_right();

  return 0;
}
