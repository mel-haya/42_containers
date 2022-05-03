
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

int main()
{
    ft::vector<int>myvec1;
    for (int i = 1; i <= 10 ; i++)
        myvec1.push_back(i);

    ft::vector<int>::reverse_iterator revIt1 = myvec1.rbegin();
    ft::vector<int>::reverse_iterator revIt2 = myvec1.rbegin() + 1;
    std::cout << revIt1 - revIt1 << std::endl;

    // std::vector<int>myvec1;
    // for (int i = 1; i <= 10 ; i++)
    //     myvec1.push_back(i);

    // std::vector<int>::reverse_iterator revIt1 = myvec1.rbegin();
    // std::vector<int>::reverse_iterator revIt2 = myvec1.rbegin() + 1;
    // std::cout << revIt1 - revIt1 << std::endl;
}