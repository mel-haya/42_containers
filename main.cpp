
// #include <vector>
// #include "vector.hpp"
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include "avl_tree.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <map>


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

// int main ()
// {

//   ft::pair<int, int> a = ft::make_pair(50,21);
//   ft::pair<int, int> b = ft::make_pair(25,19);
//   ft::pair<int, int> c = ft::make_pair(35,22);
//   ft::pair<int, int> d = ft::make_pair(57,23);
//   ft::pair<int, int> e = ft::make_pair(16,18);
//   ft::pair<int, int> f = ft::make_pair(17,18);
//   ft::pair<int, int> g = ft::make_pair(10,18);
//   ft::pair<int, int> h = ft::make_pair(11,18);
//   ft::pair<int, int> i = ft::make_pair(9,18);
//   ft::pair<int, int> j = ft::make_pair(8,18);
//   ft::pair<int, int> k = ft::make_pair(7,18);



//   avl_tree<ft::pair<int, int> > t;
//   t.insert_value(t._root,a);
//   t.insert_value(t._root,b);
//   t.insert_value(t._root,c);
//   t.insert_value(t._root,d);
//   t.insert_value(t._root,e);
//   t.insert_value(t._root,f);
//   t.insert_value(t._root,g);
//   t.insert_value(t._root,h);
//   t.insert_value(t._root,i);
//   t.insert_value(t._root,j);
//   t.insert_value(t._root,k);
//   t.delete_value(7);
//   t.delete_value(10);
//   t.delete_value(8);

//   print(t._root,4);
//   // t.rotate_left();
//   // t.rotate_right();

//   return 0;
// }
typedef std::pair<const int,int> value_type;

int main (){

    value_type a = value_type(10,5);
    value_type b = value_type(20,10);
    value_type c = value_type(30,92);
    value_type d = value_type(40,10);
    value_type e = value_type(50,90);
    value_type f = value_type(60,33);
    value_type g = value_type(70,33);
    std::vector<value_type> v;

    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    v.push_back(f);
    v.push_back(g);
    ft::map<int, int> m1(v.begin(), v.end());
    //m1.erase('e');
    //ft::map<int, int>::iterator it = m1.begin();
    //std::cout << it->first << std::endl;

    std::cout << m1.lower_bound(19)->first << std::endl;
    m1.print();
    
    //ft::map<char, int>::iterator it = m1.begin();
    // for(;it != m1.end(); it++)
    //     std::cout << it->first << std::endl;
    // for(ft::map<char, int>::iterator it = m1.begin(); it != m1.end(); it++)
    //     std::cout << it->first << std::endl;
    //m1.print();
    //m1.erase('d');
    // const ft::map<char, int>::const_iterator it = m1.find('c');

        // std::cout << it->first << std::endl;

    // ft::map<char, int>::iterator it = m1.begin();
    // for(int i = 0; i < 3; i++)
    //     it++;
    // m1.erase(m1.begin(), it);
    //m1.print();
    //std::cout << m1.size() << std::endl;

    //it++;
    //const ft::map<char, int> m2(m1);
    //m1.print();
    // std::cout << m1['c'] << std::endl;
    //m1['b'] = 5;

    //std::cout << it->first << std::endl;
    
    
    return 0;
}