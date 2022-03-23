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
};
#endif