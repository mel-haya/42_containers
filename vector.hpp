#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include "iterator_traits.hpp"
#include "utils.hpp"
#include <stdexcept>


namespace ft{
	template<typename T>
	class vectorIter
	{
		public:
			typedef T															iterator_type;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::reference			reference;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef value_type const* const_pointerType;
			typedef value_type const& const_referenceType;
			vectorIter(): _ptr(nullptr) {}
			~vectorIter(){}
			vectorIter( const vectorIter &rhs ): _ptr(rhs._ptr) {};
			vectorIter(pointer ptr) : _ptr(ptr){}
			vectorIter& operator++()
			{
				_ptr++;
				return *this;
			}

			vectorIter& operator++(int)
			{
				vectorIter &i = *this;
				++(*this);
				return i;
			}

			vectorIter& operator--()
			{
				_ptr--;
				return *this;
			}

			vectorIter& operator--(int)
			{
				vectorIter &i = *this;
				--(*this);
				return i;
			}

			vectorIter &operator+=(int value) {
				this->_ptr += value;
				return (*this);
			}

			vectorIter &operator-=(int value) {
				this->_ptr -= value;
				return (*this);
			}

			vectorIter &operator=(const vectorIter& i)
			{
				if(this != &i)
					this->_ptr = i._ptr;
				return *this;
			}
			difference_type operator+( const vectorIter &rhs) const {return _ptr + rhs._ptr;};
			difference_type operator-( const vectorIter &rhs) const {return _ptr - rhs._ptr;};
			vectorIter operator-(int value) const {return (_ptr - value);}
			vectorIter operator+(int value) const {return (_ptr + value);}
			reference operator*() {return (*_ptr);}
			reference operator[](difference_type index){return *(_ptr + index);}
			pointer operator->(){return _ptr;}
			const_referenceType operator*()const{return (*_ptr);}
			const_referenceType operator[](difference_type index) const{return *(_ptr + index);}
			const_pointerType operator->() const{return _ptr;}
			bool operator==(vectorIter const &other) const {return (this->_ptr == other._ptr);}
			bool operator!=(vectorIter const &other) const {return (this->_ptr != other._ptr);}
			bool operator<(vectorIter const &other) const {return (this->_ptr < other._ptr);}
			bool operator<=(vectorIter const &other) const {return (this->_ptr <= other._ptr);}
			bool operator>(vectorIter const &other) const {return (this->_ptr > other._ptr);}
			bool operator>=(vectorIter const &other) const {return (this->_ptr >= other._ptr);}

		private:
			pointer _ptr;
	};
	template<typename Tp>
	vectorIter<Tp> operator+(typename vectorIter<Tp>::difference_type n, vectorIter<Tp>& i){return (i + n);}
	//TODO check the std behaviour
	template<typename Tp>
	vectorIter<Tp> operator-(typename vectorIter<Tp>::difference_type n, vectorIter<Tp>& i){return (i - n);}




	template<typename T, typename _Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T                                        value_type;
			typedef _Alloc                               	allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef vectorIter<pointer>                  	iterator;
			/*To Do:    implement iterator later.
				[...]
			*/
		vector (const allocator_type& alloc = allocator_type()): _Allocator(alloc) {
			_Data = nullptr;
			_size = 0;
			_capacity = 0;
		}

		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _Allocator(alloc){
				_size = n;
				_capacity = n;
				_Data	= _Allocator.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_Allocator.construct(&_Data[i], val);
		}

		template <class Iter>
		vector (Iter first, Iter last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type* = NULL)
		:_Allocator(alloc)
		{
			difference_type n = std::distance(first, last);
			_Data = _Allocator.allocate(n);
			_capacity = n;
			_size = n;
			for (difference_type i = 0; i < _size; i++)
					_Allocator.construct(&_Data[i], *first++);

		}

		vector (const vector& x) {*this = x;}


		//TODO after assign and insert;
		// vector& operator=(const vector& c)
		// {
		// 	if(this != &c)
		// 	{
		// 		_Allocator.desallocate(_Data);
		// 		_Alloca
		// 	}
		// } 

		allocator_type get_allocator() const
		{
			return _Allocator;
		}

		size_type size()
		{
			return _size;
		}

		size_type capacity()
		{
			return _capacity;
		}

		iterator begin()
		{
			return iterator(_Data);
		}

		iterator end()
		{
			return iterator(_Data + _size);
		}

		void clear()
		{
			for(size_type i = 0; i < _size; i++)
				_Allocator.destroy(_Data + i);
			_size = 0;
		}

		void reserve( size_type new_cap )
		{
			if(new_cap > _Allocator.max_size())
				throw std::length_error("Vector :");
			if( new_cap > _capacity)
			{
				pointer tmp = _Allocator.allocate(new_cap);
				for(int i = 0; i < _size; i++)
				{
					_Allocator.construct(tmp + i, _Data[i]);
					_Allocator.destroy(_Data + i);
				}
				_Allocator.deallocate(_Data, _capacity);
				_capacity = new_cap;
				_Data = tmp;
			}
		}

		iterator erase (iterator position){
            iterator ret = position;
			_Allocator.destroy(&(*position));
            for(; position != end() - 1 ; position++)
				_Allocator.construct(&(*position), *(position + 1));
            _size--;
            return (ret);
        }

		iterator erase( iterator first, iterator last )
		{
			iterator ret = first;
			difference_type n = std::distance(first, last);
            for(; last != end() ; last++)
			{
				_Allocator.destroy(&(*first));
				_Allocator.construct(&(*first), *(last));
				first++;
			}
            _size = _size - n;
            return (ret);
		}

		void resize( size_type count, value_type value = value_type());


		reference operator[] (size_type n) { return (*(_Data + n)); }

		private:		
			allocator_type	_Allocator;
			pointer			_Data;
			size_type		_size;
			size_type		_capacity;
	};
}

#endif