/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:57:46 by shyrno            #+#    #+#             */
/*   Updated: 2022/05/19 20:02:27 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <cstddef>
#include <tgmath.h>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "utils.hpp"
#include <cstring>
#include <sstream>
#include <cmath>
#include <limits>

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T const * const_pointer;
            typedef T& reference;
            typedef T const & const_reference;
            typedef Allocator allocator_type;
            typedef vectorIterator<T> iterator;
            typedef vectorConstIterator<T> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
            typedef reverse_iterator<iterator> reverse_iterator;
            explicit vector(const allocator_type& alloc = allocator_type())
            {
                (void)alloc;
                m_size = 0;
                m_capacity = 0;
            }
            explicit vector(size_type n, const value_type & val = value_type(), const allocator_type& alloc = allocator_type())
            {
                m_alloc = alloc;
                m_size = n;
                m_capacity = n;
                this->assign(n, val);
            }
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const Allocator & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
            {
                m_alloc = alloc;
                m_size = 0;
                m_capacity = getLenght(first, last);
                container = m_alloc.allocate(m_capacity);
                for(InputIterator it = first; it != last; it++)
                {
                    m_alloc.construct(container + m_size, *it);
                    m_size++;
                }
            }
            vector& operator=(const vector & x )
			{
				this->container = x.container;
                this->m_size = x.m_size;
                this->m_capacity = x.m_capacity;
				if (m_capacity)
                    this->container = m_alloc.allocate(m_capacity);
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.construct(container + i, x.container[i]);
				return (*this);
			}
            vector(const vector & x) // Copy
            {
                this->container = x.container;
                this->m_size = x.m_size;
                this->m_capacity = x.m_capacity;
                m_alloc = x.m_alloc;
                if (m_capacity)
                    this->container = m_alloc.allocate(m_capacity);
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.construct(container + i, x.container[i]);
            }
            ~vector() // Destructor
            {
                if (m_capacity != 0)
                {
                    this->clear();
                    m_alloc.deallocate(container, m_capacity);
                }
            }
            template <class Iterator>
            size_type getLenght(Iterator first, Iterator last)
            {
                size_type ret = 0;
                Iterator it = first;
                while(it != last)
                {
                    it++;
                    ret++;
                }
                return ret;
            }
            size_type capacity() const // Capacity of container
            {
                return m_capacity;
            }
            void push_back(const value_type& val) // Push at the end 
            {
                if (m_size >= m_capacity)
                {
                    int empty = 0;
                    if (m_capacity == 0)
                        empty++;
                    m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
                    T* tmp;
                    tmp = m_alloc.allocate(m_capacity);
                    for(size_type i = 0; i < m_size; i++)
                        m_alloc.construct(tmp + i, container[i]);
                    if (!empty)
                        destroy_container();
                    container = tmp;
                }
                m_alloc.construct(container + m_size, val);
                m_size++;
            }
            bool empty() const // is container empty
            {   
                if (this->m_size == 0)
                    return true;
                return false;
            }
            void pop_back()
            {
                m_size--;
                m_alloc.destroy(container + m_size);  
            }
            size_type max_size() const
            {
                return (m_alloc.max_size());
            }
            size_type size() const // Size of container
            {
                return m_size;
            }
            void reserve(size_type n) // Reserve place (Missing lengt_error exception if n > max_capacity)
            {
                if (n > max_size())
                    std::cout << "Error, N is hella too big" << std::endl;
                if (n > m_capacity)
                    _realloc(n);
            }
            void resize(size_type n, value_type val = value_type())
            {
                if (n < m_size)
                {
                    for(size_type i = 0; i < m_size - n; i++)
						m_alloc.destroy(container + m_size - i - 1);
					m_size = n;
                }
                else
                {
                    _realloc(n);
                    for(size_type i = 0; i < n - m_size; i++)
                        m_alloc.construct(container + m_size + i, val);
                    m_size = n;
                }
            }
            reference front()
            {
                return container[0];
            }
            const_reference front() const
            {
                return container[0];
            }
            reference back()
            {
                return container[m_size - 1];
            }
            const_reference back() const
            {
                return container[m_size - 1];
            }
            reference operator[](size_type n)
            {
                return container[n];
            }
            const_reference operator[](size_type n) const
            {
                return container[n];
            }
            reference at(size_type n)
            {
                if (n > m_size)
                {
                    std::stringstream ss;
                    ss << "vector::_M_range_check: __n (which is " << n << ")" << " >= this->size() (which is " << this->m_size << ")";
                    throw std::out_of_range(ss.str());
                }
                else
                    return (container[n]);
            }
            const_reference at(size_type n) const
            {
                if (n > m_size)
                {
                    std::stringstream ss;
                    ss << "vector::_M_range_check: __n (which is " << n << ")" << " >= this->size() (which is " << this->m_size << ")";
                    throw std::out_of_range(ss.str());
                }
                return (container[n]);
            };
            void clear()
            {
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.destroy(container + i);
                m_size = 0;
                m_capacity = 0;
            }
            void swap(vector& x)
            {
                allocator_type tmp_alloc = x.m_alloc;
                size_type tmp_size = x.m_size;
			    size_type tmp_capacity = x.m_capacity;
			    pointer tmp_container = x.container;

                x.m_alloc = m_alloc;
                x.m_size = m_size;
                x.m_capacity = m_capacity;
                x.container = container;
                this->m_alloc = tmp_alloc;
                this->m_size = tmp_size;
                this->m_capacity = tmp_capacity;
                this->container = tmp_container;
            }
            iterator begin()
            {
                return iterator(container);
            }
            const_iterator begin() const
            {
                return const_iterator(container);
            }
            iterator end()
            {
                return iterator(container + m_size);
            }
            const_iterator end() const
            {
                return const_iterator(container + m_size);
            }
            const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
            reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
            reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}
            void assign(size_type n, const value_type & val) // Assign container )
            {
                this->container = m_alloc.allocate(getCapacity(n));
                m_capacity = getCapacity(n);
                for(size_type i = 0; i < n; i++)
                    m_alloc.construct(container + i, val);
                m_size = n;
            }
            template< class InputIt >
            void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
            {
                size_type lenght = getLenght(first, last);
                this->container = m_alloc.allocate(getCapacity(lenght));
                m_capacity = getCapacity(lenght);
                for(size_type i = 0; i < lenght; i++)
                {
                    m_alloc.construct(container + i, *first);
                    first++;
                }
                
                m_size = lenght;
            }
            iterator insert(iterator position, const value_type& val)
            {
                size_type index = position._ptr - container;
                if (m_size + 1> m_capacity)
				    _realloc(m_size + 1);
                for (size_type i = m_size; i > index; i--)
                {
                    m_alloc.destroy(container + i);
				    m_alloc.construct(container + i, container[i - 1]);
                }
                m_alloc.destroy(container + index);
                m_alloc.construct(container + index, val);
                m_size++;
                return iterator(container + index);
            }
            void insert(iterator position, size_type n, const value_type& val)
            {
                size_type index = position._ptr - container;
                if (m_size + n > m_capacity)
                    _realloc(m_size + n);
                for (size_type i = m_size; i > index; i--)
				    m_alloc.construct(container + i + n - 1, container[i - 1]);
                for (size_type i = index; i < n + index; i++)
				    m_alloc.construct(container + i, val);
                m_size += n;
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
            {
                size_type index = position._ptr - container;
                size_type lenght = getLenght(first, last);
                (void)last;
                (void)first;
                (void)position;
                (void)index;
                (void)lenght;
                if (m_size + lenght > m_capacity)
                    _realloc(m_size + lenght);
                for (size_type i = m_size; i > index; i--)
                {
                    m_alloc.destroy(container + i + lenght - 1);
				    m_alloc.construct(container + i + lenght - 1, container[i - 1]);
                }
                //std::cout << "first == " << *first << std::endl;
                size_type i = index;
                while (first != last)
                {
                    m_alloc.destroy(container + i);
                    m_alloc.construct(container + i, *first);
                    i++;
                    first++;
                }
                m_size += lenght;
            }
            size_type getCapacity(size_type size)
            {
                if (size > m_capacity && size < (m_capacity * 2))
                    return (m_capacity * 2);
                else if (size > m_capacity && size >= (m_capacity * 2))
                    return (size);
                else
                    return(m_capacity);
            }
            void _realloc(size_type n)
            {
                pointer tmp;
                if (n > 0)
                    tmp = m_alloc.allocate(getCapacity(n));
                else
                    return;
                for (size_type i = 0; i < m_size; i++) 
                    m_alloc.construct(tmp + i, container[i]);
                destroy_container();
                m_capacity = getCapacity(n);
                container = tmp;
		    }
            void destroy_container()
            {
                if (container && m_capacity != 0)
                {
                    for(size_type i = 0; i < m_size; i++)
                        m_alloc.destroy(container + i);
                    m_alloc.deallocate(container, m_capacity);
                }
            }  
            iterator erase(iterator position)
            {
                size_type start = position._ptr - container;
                m_alloc.destroy(position._ptr);
                m_size--;
                for (size_type i = start; i < m_size; i++)
                {
                    m_alloc.construct(container + i, container[i + 1]);
                    m_alloc.destroy(container + i + 1);
                }
                return iterator(container + start);
            }
            iterator erase(iterator first, iterator last)
            {
                size_type lenght = 0;
                for(iterator it = first; it != last; it++)
				    lenght++;
                size_type start = first._ptr - container;
                size_type shift_index = last._ptr - container;
                for (size_type i = 0; i < lenght; i++)
                    m_alloc.destroy(first._ptr + i);
                for (size_type i = start; i < m_size - lenght; i++)
                {
                    m_alloc.construct(container + i, container[shift_index]);
                    m_alloc.destroy(container + shift_index + 1);
                    shift_index++;
                }
                m_size -= lenght;
                return iterator(container + start);
            }
            allocator_type get_allocator() const
            {
                return m_alloc;
            }
            
        private:
            T* container;
            size_type m_size;
            size_type m_capacity; 
            allocator_type m_alloc;
    };
    
    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    }
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() == rhs.size())
            return true;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (!(lhs == rhs))
            return true;
        return false;
    }
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
            return true;
        return false;
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs < rhs || lhs == rhs)
            return true;
        return false;
    }
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (!(lhs <= rhs))
            return true;
        return false;
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return true;
        return false;
    }
}
#endif
