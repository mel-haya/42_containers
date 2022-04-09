#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template<bool,typename T>
	struct enable_if{};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


	template <bool is_integral, typename T>
	struct is_integral_base {
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_t : public is_integral_base<false, bool> {};

	template <>
		struct is_integral_t<bool> : public is_integral_base<true, bool> {};

	template <>
		struct is_integral_t<char> : public is_integral_base<true, char> {};

	template <>
		struct is_integral_t<signed char> : public is_integral_base<true, signed char> {};

	template <>
		struct is_integral_t<short int> : public is_integral_base<true, short int> {};
		
	template <>
		struct is_integral_t<int> : public is_integral_base<true, int> {};

	template <>
		struct is_integral_t<long int> : public is_integral_base<true, long int> {};

	template <>
		struct is_integral_t<long long int> : public is_integral_base<true, long long int> {};

	template <>
		struct is_integral_t<unsigned char> : public is_integral_base<true, unsigned char> {};

	template <>
		struct is_integral_t<unsigned short int> : public is_integral_base<true, unsigned short int> {};

	template <>
		struct is_integral_t<unsigned int> : public is_integral_base<true, unsigned int> {};

	template <>
		struct is_integral_t<unsigned long int> : public is_integral_base<true, unsigned long int> {};
		
	template <>
		struct is_integral_t<unsigned long long int> : public is_integral_base<true, unsigned long long int> {};

	template <typename T>
		struct is_integral : public is_integral_t<T> {};

	template<class It1, class It2>
	bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
			++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class It1, class It2, class Compare>
	bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2, Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
			++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class It1, class It2>
	bool equal(It1 first1, It1 last1, It2 first2, It2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1) {
			if (*first1 != *first2)
				return false;
			++first2;
		}
		return (first1 == last1) && (first2 == last2);
	}

	template<class T1,class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;
		first_type	first;
		second_type	second;

		pair():first(),second(){}
		pair( const T1& x, const T2& y ): first(x),second(y){}
		template< class U1, class U2 >
		pair( const pair<T1, T2>& p ): first(p.first),second(p.second){}
		pair( const pair& p )
		{
			*this = p;
		}
		pair& operator=( const pair& other )
		{
			if(this != &other)
			{
				this->first = other.first;
				this->second = other.second;
			}
			return *this;
		}
	};
	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u )
	{
		return (ft::pair<T1, T2>(t, u));
	}
	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first == rhs.first) && (lhs.second == rhs.second); }
	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return !(lhs == rhs);}
	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return ((lhs.first < rhs.first) || (lhs.second < rhs.second)); }
	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){ return !(rhs < lhs); }
	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){ return (rhs < lhs); }
	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){ return !(lhs < rhs); }
};


#endif