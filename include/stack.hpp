/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:49:40 by shyrno            #+#    #+#             */
/*   Updated: 2022/05/22 15:39:50 by chly-huc         ###   ########.fr       */
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
            typedef T				value_type;
			typedef Container		container_type;
			typedef size_t	size_type;

            explicit stack(const container_type & ctnr = container_type()): c(ctnr)
            {

            }
            stack &operator=(const stack & other)
            {
                
                c = other.c;
                m_size = other.m_size;
                return *this;
                
            }
            size_type size() const 
            { 
                return (this->c.size()); 
            }
            bool empty () const
            {
                if (this->c.empty())
                    return true;
                return false;
            }
            virtual ~stack()
			{
                // if (this->c.empty())
                //     this->c.clear();
            }
            value_type& top()
            { 
                return (this->c.back());
            }
            const value_type & top() const
            { 
                return (this->c.back()); 
            }
            void push(const value_type & val)
            { 
                this->c.push_back(val);
            }
            void pop()
            {
                this->c.pop_back(); 
            }
            friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c == rhs.c)
                    return (true);
                return (false);  
            }
            friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c != rhs.c)
                    return (true);
                return (false); 
            }
            friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c < rhs.c)
                    return (true);
                return (false); 
            }
            friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c <= rhs.c)
                    return (true);
                return (false); 
            }
            friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c > rhs.c)
                    return (true);
                return (false); 
            }
            friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                if (lhs.c >= rhs.c)
                    return (true);
                return (false); 
            }
        protected:
            container_type c;
            size_type m_size;
    };
}

#endif