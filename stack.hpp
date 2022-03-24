#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{

    template<class T,class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef	T		            value_type;
            typedef Container	        container_type;
            typedef	size_t		        size_type;
            typedef value_type&         reference;
            typedef value_type const&   const_reference;
            explicit stack( const Container& cont = Container() ): c(cont){}
            stack( const stack& other ): c(other.c){}
            ~stack(){}
            stack& operator=( const stack& other )
            {
                if(this != &other)
                    c = other.c;
                return *this;
            }
            reference top(){ return c.back();}
            const_reference top() const{ return c.back();}
            bool empty() const{ return c.empty();}
            size_type size() const{ return c.size();}
            void push( const value_type& value ){c.push_back(value);}
            void pop(){c.pop_back();}

            friend bool operator==( const stack& lhs, const stack& rhs ){ return lhs.c == rhs.c;}
            friend bool operator!=( const stack& lhs, const stack& rhs ){ return lhs.c != rhs.c;}
            friend bool operator<( const stack& lhs, const stack& rhs ){return lhs.c < rhs.c;}
            friend bool operator<=( const stack& lhs, const stack& rhs ){return lhs.c <= rhs.c;}
            friend bool operator>( const stack& lhs, const stack& rhs ){return lhs.c > rhs.c;}
            friend bool operator>=( const stack& lhs, const stack& rhs ){return lhs.c >= rhs.c;}

        private:
            container_type		c;
    };
}

#endif