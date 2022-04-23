#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator_traits.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <algorithm>


namespace ft{

	// random access iterator
	template<typename T>
	class vectorIter
	{
		private:
        	typedef    vectorIter<const T>                        const_iterator;
  		public:
        	typedef iterator_traits< iterator<std::random_access_iterator_tag, T> > iterator_traits;
			typedef T											iterator_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::iterator_category	iterator_category;
			typedef value_type const* const_pointerType;
			typedef value_type const& const_referenceType;
			vectorIter(): _ptr(nullptr) {}
			~vectorIter(){}
			vectorIter( const vectorIter &rhs ): _ptr(rhs._ptr) {};
			vectorIter(pointer ptr) : _ptr(ptr){}
			operator const_iterator() const { return  const_iterator(this->_ptr); }

			vectorIter& operator++()
			{
				this->_ptr++;
				return *this;
			}

			vectorIter operator++(int)
			{
				vectorIter tmp = *this;
				++(this->_ptr);
				return tmp;
			}

			vectorIter& operator--()
			{
				this->_ptr--;
				return *this;
			}

			vectorIter operator--(int)
			{
				vectorIter tmp = *this;
				--(this->_ptr);
				return tmp;
			}

			vectorIter &operator+=(difference_type value) {
				this->_ptr += value;
				return (*this);
			}

			vectorIter &operator-=(difference_type value) {
				this->_ptr -= value;
				return (*this);
			}

			vectorIter &operator=(const vectorIter& i)
			{
				if(this != &i)
					this->_ptr = i._ptr;
				return *this;
			}
			difference_type operator-( const vectorIter &rhs) const {return _ptr - rhs._ptr;};
			vectorIter operator-(difference_type value) const {return (_ptr - value);}
			vectorIter operator+(difference_type value) const {return (_ptr + value);}
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
	template<typename Tp>
	vectorIter<Tp> operator-(typename vectorIter<Tp>::difference_type n, vectorIter<Tp>& i){return (i - n);}

	// reverse iterator
	template <class iter>
    class reverse_iterator 
	{
		private:
			iter _it;
		public:
			typedef iter										iterator_type;
            typedef typename iterator_type::iterator_category	iterator_category;
            typedef typename iterator_type::value_type      	value_type;
            typedef typename iterator_type::difference_type     difference_type;
            typedef typename iterator_type::pointer     		pointer;
            typedef typename iterator_type::reference   		reference;

			reverse_iterator(): _it(nullptr) {}
			~reverse_iterator(){}
			reverse_iterator( const reverse_iterator &rhs ): _it(rhs._it) {};
			reverse_iterator(iterator_type _base) : _it(_base){}
			iterator_type base() const{return _it;}
			// operator const_iterator() const { return  const_iterator(this->_ptr); }

			reverse_iterator operator+ (difference_type n) const {return (_it - n);}
			reverse_iterator operator- (difference_type n) const {return (_it + n);}

			reverse_iterator& operator++()
			{
				(this->_it)--;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator i = *this;
				++(*this);
				return i;
			}

			reverse_iterator& operator--()
			{
				_it++;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator i = *this;
				--(*this);
				return i;
			}

			reverse_iterator& operator+=(difference_type value) {
				this->_it -= value;
				return (*this);
			}

			reverse_iterator& operator-=(difference_type value) {
				this->_it += value;
				return (*this);
			}

			template <class Iter>
			reverse_iterator& operator= (const reverse_iterator<Iter>& i)
			{
				this->_it = i.base();
				return *this;
			}
			reference operator*() const
			{
				iterator_type copy = _it;
				return (*(--copy));
			}
			pointer operator->() const
			{
				return &(operator*());
			}
			
			reference operator[](difference_type index)
			{
				return *(_it - index - 1);
			}
	};

	template <class iterator_type>
	bool operator== (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() == rhs.base());}
	template <class iterator_type>
	bool operator!= (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() != rhs.base());}
	template <class iterator_type>
	bool operator<  (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() > rhs.base());}
	template <class iterator_type>
	bool operator<= (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() >= rhs.base());}
	template <class iterator_type>
	bool operator>  (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() < rhs.base());}
	template <class iterator_type>
	bool operator>= (const reverse_iterator<iterator_type>& lhs, const reverse_iterator<iterator_type>& rhs) {return (lhs.base() <= rhs.base());}
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& i){return (i + n);}
	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return std::distance(lhs.base(), rhs.base());}


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
			typedef vectorIter<value_type>                  iterator;
			typedef vectorIter<const value_type> 			const_iterator;
			typedef reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef reverse_iterator<iterator> 				reverse_iterator;
		vector (const allocator_type& alloc = allocator_type()): _Allocator(alloc) {
			_Data = nullptr;
			_size = 0;
			_capacity = 0;
		}

		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		:_Allocator(alloc) ,  _Data(0) , _size(0), _capacity(0)
		{
			assign(n,val);
		}
		template <class Iter>
		vector (Iter first, Iter last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type* = NULL)
		:_Allocator(alloc) , _Data(0) , _size(0) ,_capacity(0)
		{
			assign(first,last);
		}
		vector (const vector& x): _Allocator(allocator_type()), _Data(0), _size(0), _capacity(0) {*this = x;}
		~vector()
		{
			clear();
			_Allocator.deallocate(_Data, _capacity);
		}

		vector& operator=(const vector& c)
		{
			assign(c.begin(),c.end());
			return *this;
		}

		reverse_iterator rbegin(void){ return reverse_iterator(end());}
		const_reverse_iterator rbegin(void) const{ return const_reverse_iterator(end());}
		reverse_iterator rend(void){ return reverse_iterator(begin());}
		const_reverse_iterator rend(void) const{ return const_reverse_iterator(begin()); }
		allocator_type get_allocator() const{return _Allocator;}
		size_type size() const{return _size;}
		size_type capacity(){return _capacity;}
		pointer data(){return _Data;}
		iterator begin(){return _Data;}
		const_iterator begin() const { return const_iterator(_Data);};
		iterator end(){return _Data + _size;}
		const_iterator end() const{return const_iterator(_Data + _size);}
		bool empty() const{return (_size == 0);}
		size_type max_size() const{return _Allocator.max_size();}
		reference front(){ return *_Data;}
		const_reference front() const{ return *_Data;}
		reference back(){ return *(_Data + _size - 1);}
		const_reference back() const{ return *(_Data + _size - 1);}

		reference at( size_type pos )
		{
			if(pos > _size)
				throw std::out_of_range("vector :");
			return *(_Data + pos);
		}
		const_reference at( size_type pos ) const
		{
			if(pos > _size)
				throw std::out_of_range("vector :");
			return *(_Data + pos);
		}
		void clear()
		{
			if(!_capacity || !_size)
				return;
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
				for(size_type i = 0; i < _size; i++)
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
			erase( position, position + 1);
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
			for(; first != end(); first++)
				_Allocator.destroy(&(*first));
            _size = _size - n;
            return (ret);
		}

		void resize( size_type count, value_type value = value_type())
		{
			if(count == _size)
				return;
			if(count < _size)
				erase(begin() + count, end());
			else if (count > _size)
			{
				if (count > _capacity)
					reserve((_capacity * 2 > count) ? _capacity * 2 : count);
				for(iterator i = end(); i < begin() + count ;i++)
					_Allocator.construct(&(*i), value);
				_size = count; 
			}		
		}

		void insert( iterator pos, size_type count, const T& value )
		{
			if(!count)
				return;
			// if(pos > end())
			// 	std::cout << *pos;
			difference_type dif = std::distance(begin(), pos);
			if (_size + count > _capacity)
					reserve((_capacity * 2 > _capacity + count) ? _capacity * 2 : _capacity + count);
			iterator i = end() + count - 1;
			for(; i != begin() + dif + count - 1  ; i--)
				_Allocator.construct(&(*i), *(i - count));
			for(; i != begin() + dif - 1 ; i--)
				_Allocator.construct(&(*i), value);
			_size+= count;
		}

		iterator insert( iterator pos, const T& value )
		{
			difference_type dif = std::distance(begin(), pos);
			insert(pos, 1, value);	
			return begin() + dif;
		}


		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last ,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		{
			if(pos > end())
			{
				std::cout << *pos << "boom";
			}
			difference_type dif = std::distance(begin(), pos);
			difference_type count = std::distance(first, last);
			if (_size + count > _capacity)
					reserve((_capacity * 2 > _capacity + count) ? _capacity * 2 : _capacity + count);
			iterator i = end() + count - 1;
			for(; i != begin() + dif + count - 1  ; i--)
				_Allocator.construct(&(*i), *(i - count));
			for(; i != begin() + dif - 1 ; i--)
			{
				_Allocator.construct(&(*i), *(last - 1));
				last--;
			}
			_size+= count;
		}

		void push_back( const_reference value )
		{
			insert( end() , value);
		}
		void pop_back()
		{
			erase(end() - 1);
		}

		void swap( vector& other )
		{
			if(*this == other)
				return;
			allocator_type	tmp_Allocator = _Allocator;
			pointer			tmp_Data = _Data;
			size_type		tmp_size = _size;
			size_type		tmp_capacity = _capacity;

			_Allocator = other._Allocator;
			_Data = other._Data;
			_size = other._size;
			_capacity = other._capacity;

			other._Allocator = tmp_Allocator;
			other._Data = tmp_Data;
			other._size = tmp_size;
			other._capacity = tmp_capacity;

		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			if(n > _capacity)
				reserve(n);
			insert(begin(), n,val);
		}

		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type n = std::distance(first, last);
			clear();
			if(n > _capacity)
				reserve(n);
			insert(begin(), first, last);
		}



		reference operator[] (size_type n) { return (*(_Data + n)); }
		const_reference operator[] (size_type n) const { return (*(_Data + n)); }
		private:		
			allocator_type	_Allocator;
			pointer			_Data;
			size_type		_size;
			size_type		_capacity;
	};

	template< class T, typename _Alloc>
	bool operator==( const vector<T,_Alloc>& lhs, const vector<T,_Alloc>& rhs ){ return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template< class T, typename _Alloc>
	bool operator!=( const vector<T,_Alloc>& lhs,const vector<T,_Alloc>& rhs ) {return (!(lhs == rhs));}
	template< class T, typename _Alloc>
	bool operator<( const vector<T,_Alloc>& lhs, const vector<T,_Alloc>& rhs ) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
	template< class T, typename _Alloc>
	bool operator>( const vector<T,_Alloc>& lhs, const vector<T,_Alloc>& rhs ) {return rhs < lhs;}
	template< class T, typename _Alloc>
	bool operator>=( const vector<T,_Alloc>& lhs, const vector<T,_Alloc>& rhs ) {return !(lhs < rhs);}
	template< class T, typename _Alloc>
	bool operator<=( const vector<T,_Alloc>& lhs, const vector<T,_Alloc>& rhs ) {return !(rhs < lhs);}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
	{
		x.swap(y);
	}

}

#endif