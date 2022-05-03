#ifndef MAP_HPP
#define MAP_HPP
#include  <functional>
#include "avl_tree.hpp"
#include "iterator_traits.hpp"
#include "utils.hpp"
#include "vector.hpp"

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
			mapIter(node *root, node *curr):_root(root),_curr(curr){}
			operator const_iterator() const { return  const_iterator(reinterpret_cast<avl_node<const value_type>*>(_root), reinterpret_cast<avl_node<const value_type>*>(_curr)); }
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
				if(x == _root->max())
					return nullptr;
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
			friend bool operator==(const mapIter  &lhs, const mapIter &rhs){
				return (lhs._curr == rhs._curr);
			}

			friend bool operator!=(const mapIter  &lhs, const mapIter &rhs)
			{
				return !(lhs == rhs);
			}
			node *get_curr(){return _curr;}
		private:
			node	*_root;
			node	*_curr;
	};

	template<class Key,class T,class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
			public:
				typedef Key					key_type;
				typedef T					mapped_type;
				typedef ft::pair<const Key, T> value_type;
				typedef Compare				key_compare;
				typedef Allocator				allocator_type;
				typedef value_type&			reference;
				typedef const value_type&	const_reference;
				typedef value_type*			pointer;
				typedef const value_type*	const_pointer;
				typedef mapIter<value_type> iterator;
				typedef mapIter<const value_type> const_iterator;
				typedef reverse_iterator<const_iterator> const_reverse_iterator;
				typedef reverse_iterator<iterator>		reverse_iterator;
				typedef ptrdiff_t			difference_type;
				typedef size_t				size_type;

				class value_compare
				{
					friend class map;
					typedef bool				result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					protected:
						Compare comp;
						value_compare (Compare c) : comp(c) {}
					public:
						bool operator()( const value_type& lhs, const value_type& rhs ) const
						{
							return comp(lhs.first, rhs.first);
						}
				};

				explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator() )
				:_comp(comp), _allocator(alloc){};
				template< class InputIt >
				map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
				:_comp(comp), _allocator(alloc)
				{
					insert(first, last);
				}

				map( const map& other )
				{
					*this = other;
				}
				~map()
				{
					_root.DeleteAVL(_root.getRoot());
				}

				allocator_type get_allocator() const
				{
					return _allocator;
				}

				map& operator=( const map& other )
				{
					if(this != &other)
					{
						_allocator = other._allocator;
						_comp = other._comp;
						clear();
						if(other.size())
							insert(other.begin(), other.end());
					}
					return *this;
				}

				T& at( const Key& key )
				{
					avl_node<value_type> *ret = _root.contains(key);
					if(!ret)
						throw std::out_of_range("ft::map ");
					return ret->_value.second;
				}


				const T& at( const Key& key ) const
				{
					avl_node<value_type> *ret = _root.contains(key);
					if(!ret)
						throw std::out_of_range("ft::map ");
					return ret->_value.second;
				}

				T&  operator[]( const Key& key )
				{
					return insert(ft::make_pair(key, mapped_type())).first->second;
				}

				size_type size() const{return _root.size();}
				bool empty() const {return !_root.size();}
				size_type max_size() const{ return _root.max_size();}

				ft::pair<iterator, bool> insert( const value_type& value )
				{
					avl_node<value_type> *ret = _root.contains(value.first);
					if(ret)
						return ft::make_pair(iterator(_root.getRoot(),ret), false);
					ret = _root.insert_value(value);
					return ft::make_pair(iterator(_root.getRoot(), ret), true);
				}
				iterator insert( iterator hint, const value_type& value )
				{
					(void)hint;
					return insert(value).first;
				}
				template< class InputIt >
				void insert( InputIt first, InputIt last )
				{
					for(; first != last; first++)
						insert(ft::make_pair(first->first, first->second));
				}

				void clear()
				{
					_root.DeleteAVL(_root.getRoot());
					_root.purge();
				}

				size_type erase( const Key& key )
				{
					return _root.delete_value(key);
				}

				void erase( iterator pos ){ erase((*pos).first); }

				void erase( iterator first, iterator last )
				{
					ft::vector<key_type> keys;
					for(;first!=last; first++)
						keys.push_back(first->first);
					typename ft::vector<key_type>::iterator end = keys.end();
					for(typename ft::vector<key_type>::iterator it = keys.begin();it != end; ++it)
						erase(*it);
				}

				size_type count( const Key& key ) const
				{
					if(_root.contains(key))
						return 1;
					return 0;
				}

				iterator find( const Key& key )
				{
					avl_node<value_type> *found = _root.contains(key);
					if(found)
						return iterator(_root.getRoot(), found);
					return end();
				}
				const_iterator find( const Key& key ) const
				{
					avl_node<value_type> *found = _root.contains(key);
					if(found)
						return iterator(_root.getRoot(), found);
					return end();
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
					if(root->_parent)
						std::cout << "parent = " << root->_parent->_value.first;
					std::cout << " value = " << root->_value.first  << std::endl;
					print(root->_left, space);
				}

				iterator begin(){ return iterator(_root.getRoot(), _root.getRoot()->min());}

				const_iterator begin() const { return iterator(_root.getRoot(), _root.getRoot()->min());}

				iterator end() { return iterator(_root.getRoot(), nullptr);}

				const_iterator end() const { return iterator(_root.getRoot(), nullptr);}
				reverse_iterator rbegin() { return reverse_iterator(end()); }
				const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
				reverse_iterator	rend(void){ return reverse_iterator(begin());}
				const_reverse_iterator	rend(void) const{ return const_reverse_iterator(begin());}
				key_compare key_comp() const{ return _comp;}
				void print()
				{
					print(_root.getRoot(),8);
				}

				iterator lower_bound( const Key& key )
				{
					iterator ret = find(key);
					if(ret.get_curr())
						return ret;
					return iterator(_root.getRoot(), _root.findSuccesser(_root.getRoot(),key));
				}

				const_iterator lower_bound( const Key& key ) const
				{
					const_iterator ret = find(key);
					if(ret.get_curr())
						return ret;
					return iterator(_root.getRoot(), _root.findSuccesser(_root.getRoot(),key));
				}

				iterator upper_bound( const Key& key )
				{
					return iterator(_root.getRoot(), _root.findSuccesser(_root.getRoot(),key));
				}

				const_iterator upper_bound( const Key& key ) const
				{
					return iterator(_root.getRoot(), _root.findSuccesser(_root.getRoot(),key));
				}

				ft::pair<iterator,iterator> equal_range( const Key& key )
				{
					//ft::pair<iterator,iterator> ret = ft::pair<iterator,iterator>(lower_bound(key), upper_bound(key)); 
					return ft::pair<iterator,iterator>(lower_bound(key), upper_bound(key));
				}

				ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
				{
					return ft::pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));
				}

				void swap( map& other )
				{
					_root.swap(other._root);
					std::swap(_allocator, other._allocator);
					std::swap(_comp, other._comp);
				}

				value_compare value_comp() const
				{
					value_compare comp(key_comp());
					return comp;
				}

				// iterator upper_bound( const Key& key )
				// {
				// 	iterator it = lower_bound(key);
				// 	if (_root(conta))
				// }

				

			private:
				avl_tree<value_type, key_compare>	_root;
				Compare								_comp;
				Allocator							_allocator;
	};
};

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
{
	rhs.swap(lhs);
}

#endif
