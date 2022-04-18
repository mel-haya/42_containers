#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>
#include <memory>

template <typename T>
struct avl_node
{
    typedef T                   value_type;
    value_type _value;
    avl_node *_left;
    avl_node *_right;
    avl_node *_parent;
    avl_node():_value(), _left(nullptr), _right(nullptr), _parent(nullptr){}
    avl_node	*min()
	{
        avl_node *tmp = this;
		while(tmp->_left)
			tmp = tmp->_left;
		return (tmp);
	}

	avl_node	*max()
	{
        avl_node *tmp = this;
		while(tmp->_right)
			tmp = tmp->_right;
		return (tmp);
	}
};

template <typename T>
class avl_tree
{
    public:
        typedef T                   value_type;
        typedef avl_node<T>         node;
        typedef std::allocator<node>   allocator_type;
        typedef typename allocator_type::template rebind<value_type>::other allocator_type2;
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
 
        node *insert_value(node *n,const value_type &c)
        {
            if(!_root)
            {
                _root = new_node(c, nullptr);
                return _root;
            }
            if( n == _root && contains(c.first))
                return nullptr;
			while(1)
			{
				if(n->_right && c.first > n->_value.first)
					n = n->_right;
				else if(n->_left && c.first < n->_value.first)
					n = n->_left;
				else
					break;
			}
			if(c.first > n->_value.first)
			{
				n->_right = new_node(c, n);
				balance_tree(n);
				return n->_right;
			}
			else if(c.first < n->_value.first)
			{
				n->_left = new_node(c, n);
				balance_tree(n);
				return n->_left;
			}
			return nullptr;
        }

        node *insert_value(const value_type &c)
        {
            return insert_value(_root, c);
        }

        template <typename K>
        node *contains(K key)
        {
            node *tmp = _root;
            while(tmp)
            {
                if(key == tmp->_value.first)
                    return tmp;
                if(key < tmp->_value.first)
                    tmp = tmp->_left;
                else if(key > tmp->_value.first)
                    tmp = tmp->_right;
            }
            return nullptr;
        }
        template <typename K>
        void delete_value(const K &key)
        {
            node *tmp = _root;
            if(!tmp || !contains(key))
                return;
            // in case there is no elements but the root
            if(_root->_value.first == key && !_root->_left && !_root->_right)
            {
                _alloc.deallocate(_root, 1) ;
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
            allocator_type _alloc;
            allocator_type2	allocator2; 
            node *new_node(value_type c, node *parent)
            {
                node *ret = _alloc.allocate(1);
                allocator2.construct(&ret->_value, c);
                ret->_parent = parent;
                ret->_left = nullptr;
                ret->_right = nullptr;
                return ret;
            }

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
                    _alloc.deallocate (to_replace->_left, 1);
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
                    _alloc.deallocate (to_replace, 1);
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
                    _alloc.deallocate (to_replace->_right, 1);
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
                    _alloc.deallocate (to_replace, 1);
                }
            }       
};

// template <typename T>
// class avl_tree
// {
//     typedef typename T::first key;
    
//     private:
//         avl_tree<T> *_root;
// };˘

#endif