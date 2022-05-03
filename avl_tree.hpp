#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
struct avl_node
{
    typedef T                   value_type;
    value_type  _value;
    avl_node    *_left;
    avl_node    *_right;
    avl_node    *_parent;
    size_t      height;
    long       bf;  
    avl_node():_value(), _left(nullptr), _right(nullptr), _parent(nullptr){}
    avl_node	*min()
	{
        avl_node *tmp = this;
        if(!tmp)
            return nullptr;
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

template <typename T, typename compare>
class avl_tree
{
    public:
        typedef T                   	value_type;
        typedef avl_node<T>         	node;
        typedef std::allocator<node>	allocator_type;
        typedef compare             	key_compare;
        typedef typename allocator_type::template rebind<value_type>::other allocator_type2;
        typedef typename value_type::first_type	key_type;
        avl_tree():_root(nullptr), _comp(), len(0){}
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
            node *tmp;
            if(!_root)
            {
                _root = new_node(c, nullptr);
                return _root;
            }
            // if( n == _root && contains(c.first))
            //     return nullptr;
			while(1)
			{
				if(n->_right && _comp(n->_value.first, c.first))
					n = n->_right;
				else if(n->_left && _comp(c.first, n->_value.first))
					n = n->_left;
				else
					break;
			}
			if(_comp(n->_value.first, c.first))
			{
				n->_right = new_node(c, n);
                tmp = n->_right;
                updateHeight(n);
				balance_tree(n);
				return tmp;
			}
			else if(_comp(c.first, n->_value.first))
			{
				n->_left = new_node(c, n);
                tmp = n->_left;
                updateHeight(n->_left);
				balance_tree(n);
				return tmp;
			}
			return nullptr;
        }

        node *insert_value(const value_type &c)
        {
            len++;
            return insert_value(_root, c);
        }

        template <typename K>
        node *contains(K key) const
        {
            node *tmp = _root;
            while(tmp)
            {
                if(key == tmp->_value.first)
                    return tmp;
                if(_comp(key, tmp->_value.first))
                    tmp = tmp->_left;
                else if(_comp(tmp->_value.first, key))
                    tmp = tmp->_right;
            }
            return nullptr;
        }
        template <typename K>
        int delete_value(const K &key)
        {
            node *tmp = _root;
            len--;
            if(!tmp || !contains(key))
                return 0;
            // in case there is no elements but the root
            if(_root->_value.first == key && !_root->_left && !_root->_right)
            {
                _alloc.deallocate(_root, 1) ;
                _root = NULL;
                return 1;
            }
            while (tmp)
            {
                if(_comp(tmp->_value.first, key))
                    tmp = tmp->_right;
                else if(_comp(key, tmp->_value.first)) 
                    tmp = tmp->_left;
                else
                {
                    if(tmp->_left)
                        delete_left(tmp);
                    else
                        delete_right(tmp);
                    return 1;
                }
            }
            return 1;
        }

        void rotate_left(node *n)
        {
            node *new_root = n->_right;
            n->_right = new_root->_left;
            if(n->_right)
                n->_right->_parent = n;
            new_root->_left = n;
            if(!n->_parent)
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
            updateHeight(new_root->_left);
            //updateHeight(new_root);
        }

        void rotate_right(node *n)
        {
            node *new_root = n->_left;
            n->_left = new_root->_right;
            if(n->_left)
                n->_left->_parent = n;
            new_root->_right = n;
            if(!n->_parent)
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
            updateHeight(new_root->_right);
            //updateHeight(new_root);
        }

        void balance_node(node *n)
        {
            //int balance = balance_factor(n);
            if(n->bf > 2)
            {
                if( n->_left->bf < 1)
                    rotate_left(n->_left);
                rotate_right(n);
            }
            else if (n->bf < -2)
            {
                if( n->_right->bf > 1)
                    rotate_right(n->_right);
                rotate_left(n);
            }
        }

        int height(node *root) const {
            if (root == NULL)
                return 0;
            return root->height;
        }

        int balance_factor(node *n)
        {
            return (height(n->_left) - height(n->_right));
        }

        void updateHeight(node *n)
        {
            while(n)
            {
                n->height = 1 + std::max(height(n->_right), height(n->_left));
                n->bf = height(n->_left) - height(n->_right);
                n = n->_parent;
            }
        }

        node *getRoot() const {return _root;}
        void purge() {_root = nullptr;}

        void DeleteAVL(node* n) 
        {
            if( n ) {
                len = 0;
                DeleteAVL( n->_left );
                DeleteAVL( n->_right );
                _alloc.deallocate(n, 1);
            }
        }

        size_t max_size() const
        {
            return _alloc.max_size();
        }

        size_t size() const
        {
            return len;
        }

		node *findSuccesser(node *root, key_type k) const
		{
            node *successor = nullptr;
            while(root)
            {
                if(_comp(k, root->_value.first))
                {
                    successor = root;
                    root = root->_left;
                }
                else if(!_comp(k, root->_value.first))
                    root = root->_right;
            }
            return successor;
		}
        void swap(avl_tree &other)
        {
            std::swap(_root, other._root);
            std::swap(len, other.len);
            
        }
    private:
        node *_root;
        allocator_type _alloc;
        allocator_type2	allocator2;
        key_compare _comp;
        size_t len;
        node *new_node(value_type c, node *parent)
        {
            node *ret = _alloc.allocate(1);
            allocator2.construct(&ret->_value, c);
            ret->_parent = parent;
            ret->_left = nullptr;
            ret->_right = nullptr;
            ret->height = 0;
            ret->bf = 1;
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
            //tmp->_value = to_replace->_value;
            allocator2.construct(&tmp->_value, to_replace->_value);
            if(to_replace->_left)
            {
                //to_replace->_value = to_replace->_left->_value;
                allocator2.construct(&to_replace->_value, to_replace->_left->_value);
                _alloc.deallocate (to_replace->_left, 1);
                to_replace->_left = nullptr;
                updateHeight(to_replace);
                balance_tree(to_replace);
            }
            else
            {
                if(to_replace->_parent->_left == to_replace)
                    to_replace->_parent->_left = nullptr;
                else if(to_replace->_parent->_right == to_replace)
                    to_replace->_parent->_right = nullptr;
                updateHeight(to_replace->_parent);
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
            updateHeight(to_replace);
            allocator2.construct(&tmp->_value, to_replace->_value);
            if(to_replace->_right)
            {
                //to_replace->_value = to_replace->_right->_value;
                allocator2.construct(&to_replace->_value, to_replace->_right->_value);
                _alloc.deallocate (to_replace->_right, 1);
                to_replace->_right = nullptr;
                updateHeight(to_replace);
                balance_tree(to_replace);
            }
            else
            {
                if(to_replace->_parent->_left == to_replace)
                    to_replace->_parent->_left = nullptr;
                else if(to_replace->_parent->_right == to_replace)
                    to_replace->_parent->_right = nullptr;
                updateHeight(to_replace->_parent);
                balance_tree(to_replace->_parent);
                _alloc.deallocate (to_replace, 1);
            }
        }
};

template <typename T, typename compare>
void swap(avl_tree<T, compare> &rhs, avl_tree<T, compare> &lhs)
{
    rhs.swap(lhs);
}
// template <typename T>
// class avl_tree
// {
//     typedef typename T::first key;
    
//     private:
//         avl_tree<T> *_root;
// };˘

#endif