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
        avl_tree()
        {
            _root = nullptr;
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
            if(!_root)
            {
                _root = new node(c, NULL);
                return;
            }
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

        template <typename K>
        bool contains(K key)
        {
            node *tmp = _root;
            while(tmp)
            {
                if(key == tmp->_value.first)
                    return true;
                if(key < tmp->_value.first)
                    tmp = tmp->_left;
                else if(key > tmp->_value.first)
                    tmp = tmp->_right;
            }
            return false;
        }
        template <typename K>
        void delete_value(node *n,const K &key)
        {
            node *tmp = _root;
            if(!tmp || !contains(key))
                return;
            // in case there is no elements but the root
            if(_root->_value.first == key && !_root->_left && !_root->_right)
            {
                delete _root;
                _root = NULL;
                return;
            }
            while (tmp)
            {
                if(key > tmp->_value.first)
                    tmp = tmp->_right;
                else if(key < tmp->_value.first)
                    tmp = tmp->_left;
                else
                {
                    if(tmp->_left)
                        delete_left(tmp);
                    else
                        delete_right(tmp);
                    return;
                }
            }
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
    private:


            void balance_tree(node *n)
            {
                while(n)
                {
                    balance_node(n);
                    n = n->_parent;
                }
            }
            void delete_left(node *tmp)
            {
                node *to_replace = tmp->_left;
                while(to_replace->_right)
                    to_replace = to_replace->_right;
                tmp->_value = to_replace->_value;
                if(to_replace->_left)
                {
                    to_replace->_value = to_replace->_left->_value;
                    delete to_replace->_left;
                    to_replace->_left = nullptr;
                    balance_tree(to_replace);
                }
                else
                {
                    if(to_replace->_parent->_left == to_replace)
                        to_replace->_parent->_left = nullptr;
                    else if(to_replace->_parent->_right == to_replace)
                        to_replace->_parent->_right = nullptr;
                    balance_tree(to_replace->_parent);
                    delete to_replace;
                }
            }
            void delete_right(node *tmp)
            {
                node *to_replace = tmp;
                if(tmp->_right)
                    to_replace = tmp->_right;
                while(to_replace->_left)
                    to_replace = to_replace->_left;
                tmp->_value = to_replace->_value;
                if(to_replace->_right)
                {
                    to_replace->_value = to_replace->_right->_value;
                    delete to_replace->_right;
                    to_replace->_right = nullptr;
                    balance_tree(to_replace);
                }
                else
                {
                    if(to_replace->_parent->_left == to_replace)
                        to_replace->_parent->_left = nullptr;
                    else if(to_replace->_parent->_right == to_replace)
                        to_replace->_parent->_right = nullptr;
                    balance_tree(to_replace->_parent);
                    delete to_replace;
                }
            }       
};

// template <typename T>
// class avl_tree
// {
//     typedef typename T::first key;
    
//     private:
//         avl_tree<T> *_root;
// };

#endif