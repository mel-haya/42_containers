#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>

template <typename T>
struct avl_node
{
    typedef T                   value_type;
    value_type _value;
    avl_node *_left;
    avl_node *_right;
    avl_node *_parent;
    avl_node():_value(), _left(nullptr), _right(nullptr), _parent(nullptr){}
    avl_node(value_type c, avl_node *parent):_value(c), _left(nullptr), _right(nullptr), _parent(parent){}
};

template <typename T>
class avl_tree
{
    public:
        typedef T                   value_type;
        typedef avl_node<T>         node;
        avl_tree():_root(){}
        avl_tree(value_type c)
        {
            _root = new node(c , NULL);

        }
        ~avl_tree(){}
        avl_tree(const avl_tree& c){*this = c;}
        avl_tree& operator=(const avl_tree& c)
        {
            if(this != &c)
                this->_root = c._root;
            return *this;
        }

        void insert_value(node *n,const value_type &c)
        {
            if(c.first == n->_value.first)
                return;
            if(c.first > n->_value.first)
            {
                if(n->_right)
                    insert_value(n->_right, c);
                else
                    n->_right = new node(c, n);
            }
            else if(c.first < n->_value.first)
            {
                if(n->_left)
                    insert_value(n->_left, c);
                else
                    n->_left = new node(c, n);
            }
            balance_node(n);         
        }

        void rotate_left(node *n)
        {
            node *new_root = n->_right;
            n->_right = new_root->_left;
            new_root->_left = n;
            if(n == _root)
            {
                _root = new_root;
                _root->_parent = NULL;
            }
            else
            {
                if(n->_parent->_left == n)
                    n->_parent->_left = new_root;
                else if(n->_parent->_right == n)
                    n->_parent->_right = new_root;
                new_root->_parent = n->_parent;
            }
            n->_parent = new_root;
        }

        void rotate_right(node *n)
        {
            node *new_root = n->_left;
            n->_left = new_root->_right;
            new_root->_right = n;
            if(n == _root)
            {
                _root = new_root;
                _root->_parent = NULL;
            }
            else
            {
                if(n->_parent->_left == n)
                    n->_parent->_left = new_root;
                else if(n->_parent->_right == n)
                    n->_parent->_right = new_root;
                new_root->_parent = n->_parent;
            }
            n->_parent = new_root;
        }

        void balance_node(node *n)
        {
            int balance = balance_factor(n);
            if(balance > 1)
            {
                if( balance_factor(n->_left) < 0)
                    rotate_left(n->_left);
                rotate_right(n);
            }
            else if (balance < -1)
            {
                if( balance_factor(n->_right) > 0)
                    rotate_right(n->_right);
                rotate_left(n);
            }
        }

        int Height(node *root) const {
            int height = 0;
            if( root ) {
                int left  = Height(root->_left);
                int right = Height(root->_right);
                height = 1 + ((left > right) ? left : right) ;
            }
            return height;
        }

        int balance_factor(node *n)
        {
            if(n)
                return (Height(n->_left) - Height(n->_right));
            return (0);
        }

        node *_root;     
};

// template <typename T>
// class avl_tree
// {
//     typedef typename T::first key;
    
//     private:
//         avl_tree<T> *_root;
// };

#endif