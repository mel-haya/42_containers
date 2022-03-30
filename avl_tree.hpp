#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>

template <typename T>
class avl_tree
{
    public:
        typedef T                   value_type;

        avl_tree():_value(), _left(nullptr), _right(nullptr), _parent(nullptr) {}
        avl_tree(value_type c):_value(c), _left(nullptr), _right(nullptr), _parent(nullptr){}
        ~avl_tree(){}
        avl_tree(const avl_tree& c){*this = c;}
        avl_tree& operator=(const avl_tree& c)
        {
            if(this != &c)
            {
                this->_value = c._value;
                this->_left = c._left;
                this->_right = c._right;
                this->_parent = c._parent;
            }
            return *this;
        }

        void insert_value(const value_type &c)
        {
            if(c.first == _value.first)
                return;
            if(c.first > _value.first)
            {
                if(_right)
                    _right->insert_value(c);
                else
                    _right = new avl_tree(c);
            }
            else if(c.first < _value.first)
            {
                if(_left)
                    _left->insert_value(c);
                else
                    _left = new avl_tree(c);
            }
            balance_node();         
        }

        void erase_value(const value_type::first_type &key)
        {
            if(c.first == _value.first)
                return;
            if(c.first > _value.first)
            {
                if(_right)
                    _right->insert_value(c);
                else
                    _right = new avl_tree(c);
            }
            else if(c.first < _value.first)
            {
                if(_left)
                    _left->insert_value(c);
                else
                    _left = new avl_tree(c);
            }
            balance_node();         
        }



        int balance_factor()
        {
            int left = (_left) ? _left->balance_factor() : -1;
            int right = (_right) ? _right->balance_factor() : -1;
            return (left - right);
        }

        void rotate_left()
        {
            avl_tree *tmp = new avl_tree(*this);
            avl_tree *tmp2 = nullptr;
            if(_right->_left)
                tmp2 = _right->_left;
            *this = *_right;
            _left = tmp;
            _left->_right = tmp2;
        }

        void rotate_right()
        {
            avl_tree *tmp = new avl_tree(*this);
            avl_tree *tmp2 = nullptr;
            if(_left->_right)
                tmp2 = _left->_right;
            *this = *_left;
            _right = tmp;
            _right->_left = tmp2;
        }

        void balance_node()
        {
            int balance = balance_factor();
            if(balance > 1)
            {
                if( _left->balance_factor() < 0)
                    _left->rotate_left();
                rotate_right();
            }
            else if (balance < -1)
            {
                if( _right->balance_factor() > 0)
                    _right->rotate_right();
                rotate_left();
            }
        }

        void print_tree()
        {
            std::cout << _value << std::endl;
            if(_left)
            {
                std::cout <<"- L : ";
                _left->print_tree();
            }
            if(_right)
            {
                std::cout << "- R : ";
                _right->print_tree();
            }
            std::cout << std::endl;
        }

    private:
        value_type _value;
        avl_tree *_left;
        avl_tree *_right;
        avl_tree *_parent;      
};

// template <typename T>
// class avl_tree
// {
//     typedef typename T::first key;
    
//     private:
//         avl_tree<T> *_root;
// };

#endif