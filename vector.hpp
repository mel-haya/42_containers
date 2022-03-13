
#include <iostream>
#include <vector>

template<typename vector>
class vectorIter
{
	public:
		typedef typename vector::pointer valueType;
		typedef valueType* pointerType;
		typedef valueType& referenceType;
		typedef valueType const* const_pointerType;
		typedef valueType const&  const_referenceType;
		vectorIter(pointerType ptr) : _ptr(ptr){}
		vectorIter& operator++()
		{
			_ptr++;
			return *this;
		}

		vectorIter& operator++()
		{
			vectorIter i = *this;
			++(*this);
			return i;
		}

		vectorIter& operator--()
		{
			_ptr--;
			return *this;
		}

		vectorIter& operator--()
		{
			vectorIter i = *this;
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

		referenceType operator*() {return (*this->p);}
		referenceType operator[](int index){return *(_ptr + index);}
		pointerType operator->(){return _ptr;}
		const_referenceType operator*() const{return (*this->p);}
		const_referenceType operator[] const(int index){return *(_ptr + index);}
		const_pointerType operator->() const{return _ptr;}

		bool operator==(vectorIter const &other) const {return (this->_ptr == other._ptr);}
		bool operator!=(vectorIter const &other) const {return (this->_ptr != other._ptr);}
		bool operator<(vectorIter const &other) const {return (this->_ptr < other._ptr);}
		bool operator<=(vectorIter const &other) const {return (this->_ptr <= other._ptr);}
		bool operator>(vectorIter const &other) const {return (this->_ptr > other._ptr);}
		bool operator>=(vectorIter const &other) const {return (this->_ptr >= other._ptr);}

	private:
		pointerType _ptr
};







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
		typedef vectorIter<vector<T>>                     iterator;
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

	vector (const vector& x) {*this = x;}

	// vector& operator=(const vector& c)
	// {
	// 	if(this != &c)
	// 	{
	// 		_Allocator.desa
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

	reference operator[] (size_type n) { return (*(_Data + n)); }

    private:		
		allocator_type	_Allocator;
		pointer			_Data;
		size_type		_size;
		size_type		_capacity;
};

