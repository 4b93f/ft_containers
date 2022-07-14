/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:49:40 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 10:56:10 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "header.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
			typedef Container container_type;
            typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
            typedef typename Container::reference reference;
            typedef typename Container::const_reference const_reference;

            explicit stack(const container_type & ctnr = container_type()): c(ctnr)
            {

            }
            stack & operator=(const stack & other)
            {
                c = other.c;
                return *this;
            }
            size_type size() const 
            { 
                return (this->c.size()); 
            }
            bool empty() const
            {
                if (this->c.empty())
                    return true;
                return false;
            }
            ~stack()
			{
                
            }
            reference top()
            { 
                return (this->c.back());
            }
            const_reference top() const
            { 
                return (this->c.back()); 
            }
            void push(const value_type & value)
            { 
                this->c.push_back(value);
            }
            void pop()
            {
                this->c.pop_back(); 
            }
        protected:
            container_type c;
            size_type m_size;
    };
    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c == rhs.c);
    }
    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c != rhs.c);
    }
    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c < rhs.c);
    }
    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c <= rhs.c);
    }
    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c > rhs.c);
    }
    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return (lhs.c >= rhs.c);
    }
}

#endif