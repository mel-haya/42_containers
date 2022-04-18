#ifndef MAP_HPP
#define MAP_HPP
#include  <functional>
#include "avl_tree.hpp"
#include "iterator_traits.hpp"

namespace ft
{

	template<typename T>
	class mapIter
	{
		private:
        	typedef		mapIter<const T>                        const_iterator;
			typedef		avl_node<T>					node;
  		public:
        	typedef iterator_traits< iterator<std::bidirectional_iterator_tag, T> > iterator_traits;
			typedef T											iterator_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::iterator_category	iterator_category;
			typedef value_type const*							const_pointerType;
			typedef value_type const&							const_referenceType;
			mapIter(): _root(nullptr), _curr(nullptr) {}
			~mapIter(){}
			mapIter(const mapIter &rhs )
			{
				*this = rhs;
			}
			//mapIter(pointer ptr) : _ptr(ptr){}
			mapIter(node *root, node *curr):_root(root),_curr(curr){}
			operator const_iterator() const { return  const_iterator(this->_curr, this->_root); }
			mapIter& operator++()
			{
				_curr = successor(_curr);
				return *this;
			}

			mapIter operator++(int)
			{
				mapIter tmp = *this;
				++(*this);
				return tmp;
			}

			mapIter& operator--()
			{
				_curr = predecessor(_curr);
				return *this;
			}

			mapIter operator--(int)
			{
				mapIter tmp = *this;
				--(*this);
				return tmp;
			}
			
			mapIter &operator=(const mapIter& i)
			{
				if(this != &i)
				{
					this->_root = i._root;
					this->_curr = i._curr;
				}
				return *this;
			}
			reference operator*() {return (_curr->_value);}
			pointer operator->(){return &(_curr->_value);}
			const_referenceType operator*()const{return (_curr->_value);}
			const_pointerType operator->() const{return &(_curr->_value);}
		
			node *successor(node *x)
			{
				if(x->_right)
					return x->_right->min();
				node *y = x->_parent;
				while(y && x == y->_right)
				{
					x = y;
					y = y->_parent;
				}
				return y;
			}

			node *predecessor(node *x)
			{
				if(!x)
					return _root->max();
				if(x->_left)
					return x->_left->max();
				node *y = x->_parent;
				while(y && x == y->_left)
				{
					x = y;
					y = y->_parent;
				}
				return y;
			}

		private:
			node	*_root;
			node	*_curr;
	};

	template<class Key,class T,class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
			public:
				typedef Key					key_type;
				typedef T					mapped_type;
				typedef ft::pair<const key_type,mapped_type> value_type;
				typedef Compare				key_compare;
				typedef Allocator				allocator_type;
				typedef value_type&			reference;
				typedef const value_type&	const_reference;
				typedef value_type*			pointer;
				typedef const value_type*	const_pointer;
				typedef mapIter<value_type> iterator;
				typedef mapIter<const value_type> const_iterator;
				// typedef reverse_iterator<const_iterator> const_reverse_iterator;
				// typedef reverse_iterator<iterator>		reverse_iterator;
				typedef ptrdiff_t			difference_type;
				typedef size_t				size_type;
				bool insert(value_type& value )
				{
					return _root.insert_value(value);
				}
				bool insert( iterator hint, const value_type& value )
				{
					return _root.insert_value(value);
				}
				template< class InputIt >
				void insert( InputIt first, InputIt last )
				{
					for(; first!=last; first++)
						_root.insert_value(*first);
				}
				
				template <typename R>
				void   print(avl_node<R> *root, int space)
				{
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

				iterator begin()
				{
					return iterator(_root._root, _root._root->min());
				}

				const_iterator begin() const { return const_iterator(_root._root, _root._root->min());};

				iterator end()
				{
					return iterator(_root._root, nullptr);
				}

				void print()
				{
					print(_root._root,8);
				}
			private:
				avl_tree<value_type> _root;
	};
};

#endif