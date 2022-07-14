/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:57:46 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 11:36:09 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "header.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "utils.hpp"

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
            vector() // Default constructor
            {
                container = NULL;
                m_size = 0;
                m_capacity = 0;
                m_alloc = Allocator();
            }
            explicit vector(const Allocator & alloc) // Constructor with an allocator
            {
                container = NULL;
                m_size = 0;
                m_capacity = 0;
                m_alloc = alloc;
            }
            explicit vector(size_type n, const value_type & val = value_type(), const Allocator & alloc = Allocator()) // Fill Constructor
            {
                container = NULL;
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
                m_capacity = _getLenght(first, last);
                container = m_alloc.allocate(m_capacity);
                for(InputIterator it = first; it != last; it++)
                {
                    m_alloc.construct(container + m_size, *it);
                    m_size++;
                }
            }
            vector & operator=(const vector & other) // Assignation constructor with another vector
			{
                if (*this == other)
					return (*this);
                this->_destroy_container();
                this->m_alloc = other.m_alloc;
                this->m_size = other.m_size;
                this->m_capacity = other.m_capacity;
                this->container = NULL;
				if (m_capacity)
                    this->container = m_alloc.allocate(m_capacity);
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.construct(container + i, other.container[i]);
				return (*this);
			}
            vector(const vector & other) // Constructor with another vector
            {
                this->m_alloc = other.m_alloc;
                this->m_size = other.m_size;
                this->m_capacity = other.m_size;
                this->container = NULL;
                if (m_capacity)
                    this->container = m_alloc.allocate(m_capacity);
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.construct(container + i, other.container[i]);
            }
            ~vector() // Destructor
            {
                if (m_capacity != 0)
                {
                    this->clear();
                    m_alloc.deallocate(container, m_capacity);
                }
            }
            template <class Iterator> // getlenght between 2 iterator
            size_type _getLenght(Iterator first, Iterator last)
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
            void push_back(const value_type & val) // Push at the end 
            {
                if (m_size >= m_capacity)
                {
                    int empty = 0;
                    if (m_capacity == 0)
                        empty++;
                    m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
                    pointer tmp;
                    tmp = m_alloc.allocate(m_capacity);
                    for(size_type i = 0; i < m_size; i++)
                        m_alloc.construct(tmp + i, container[i]);
                    if (!empty)
                        _destroy_container();
                    container = tmp;
                }
                m_alloc.construct(container + m_size, val);
                m_size++;
            }
            bool empty() const // is container empty ?
            {   
                if (this->m_size == 0)
                    return true;
                return false;
            }
            void pop_back() // Remove the last element
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
            void reserve(size_type n) // Reserve n place in the vector
            {
                if (n > max_size())
                    throw std::length_error("vector::reserve");
                if (n > m_capacity)
                    _realloc(n);
            }
            void resize(size_type count, value_type value = value_type()) // Resize the vector to vector[n] max
            {
                if (count < m_size)
                {
                    for(size_type i = 0; i < m_size - count; i++)
						m_alloc.destroy(container + m_size - i - 1);
					m_size = count;
                }
                else
                {
                    _realloc(_getCapacity(count));
                    for(size_type i = 0; i < count - m_size; i++)
                        m_alloc.construct(container + m_size + i, value);
                    m_size = count;
                }
            }
            reference front() // get the 1st element
            {
                return container[0];
            }
            const_reference front() const
            {
                return container[0];
            }
            reference back() // get the last element
            {
                return container[m_size - 1];
            }
            const_reference back() const
            {
                return container[m_size - 1];
            }
            pointer data() // get the container
			{
				return (container);
			}
	        const_pointer data() const
			{
				return (container);
			}
            reference operator[](size_type pos) // get the element at vector[pos]
            {
                return container[pos];
            }
            const_reference operator[](size_type pos) const
            {
                return container[pos];
            }
            reference at(size_type pos) // get the element at vector[pos] but with verification
            {
                if (pos > m_size)
                {
                    std::stringstream ss;
                    ss << "vector::_M_range_check: __n (which is " << pos << ")" << " >= this->size() (which is " << this->m_size << ")";
                    throw std::out_of_range(ss.str());
                }
                else
                    return (container[pos]);
            }
            const_reference at(size_type pos) const
            {
                if (pos > m_size)
                {
                    std::stringstream ss;
                    ss << "vector::_M_range_check: __n (which is " << pos << ")" << " >= this->size() (which is " << this->m_size << ")";
                    throw std::out_of_range(ss.str());
                }
                return (container[pos]);
            };
            void clear() // clear the container
            {
                for(size_type i = 0; i < m_size; i++)
                    m_alloc.destroy(container + i);
                m_size = 0;
            }
            void swap(vector & other) // swap element between 2 vector
            {
                allocator_type tmp_alloc = other.m_alloc;
                size_type tmp_size = other.m_size;
			    size_type tmp_capacity = other.m_capacity;
			    pointer tmp_container = other.container;

                other.m_alloc = m_alloc;
                other.m_size = m_size;
                other.m_capacity = m_capacity;
                other.container = container;
                this->m_alloc = tmp_alloc;
                this->m_size = tmp_size;
                this->m_capacity = tmp_capacity;
                this->container = tmp_container;
            }
            iterator begin() // get an iterator to the first element
            {
                return iterator(container);
            }
            const_iterator begin() const
            {
                return const_iterator(container);
            }
            reverse_iterator rbegin() // get a reverse iterator to the first element
			{
				return reverse_iterator(end());
			}
            const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
            iterator end() // get an iterator to the last element
            {
                return iterator(container + m_size);
            }
            const_iterator end() const
            {
                return const_iterator(container + m_size);
            }
            reverse_iterator rend() // get a reverse iterator to the last element
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}
            void assign(size_type count, const value_type & value) // Assign container
            {
                this->container = m_alloc.allocate(_getCapacity(count));
                m_capacity = _getCapacity(count);
                for(size_type i = 0; i < count; i++)
                    m_alloc.construct(container + i, value);
                m_size = count;
            }
            template< class InputIt >
            void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
            {
                size_type lenght = _getLenght(first, last);
                this->container = m_alloc.allocate(_getCapacity(lenght));
                m_capacity = _getCapacity(lenght);
                for(size_type i = 0; i < lenght; i++)
                {
                    m_alloc.construct(container + i, *first);
                    first++;
                }
                m_size = lenght;
            }
            iterator insert(iterator pos, const value_type & value) // insert an element at vector[pos]
            {
                size_type index = pos._ptr - container;
                if (m_size + 1  > m_capacity)
				    container = realloc(container, _getCapacity(m_capacity + 1));
                for (size_type i = m_size; i > index; i--)
                {
                    m_alloc.destroy(container + i);
				    m_alloc.construct(container + i, container[i - 1]);
                }
                m_alloc.destroy(container + index);
                m_alloc.construct(container + index, value);
                m_size++;
                return iterator(container + index);
            }
            void insert(iterator pos, size_type count, const value_type & value) // insert n element at vector[iterator]
            {
                if (count == 0)
                    return;
                size_type index = pos._ptr - container;
                if (m_size + count > m_capacity)
                {
                    if (m_size * 2 > m_size + count)
                        container = realloc(container, m_capacity * 2);
                    else
                        container = realloc(container, (m_capacity + count));
                }
                for (size_type i = m_size; i > index; i--)
				    m_alloc.construct(container + i + count - 1, container[i - 1]);
                for (size_type i = index; i < count + index; i++)
				    m_alloc.construct(container + i, value);
                m_size += count;
            }
            template <class InputIterator>
            void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
            {
                size_type index = pos._ptr - container;
                size_type lenght = _getLenght(first, last);
                if (m_size + lenght > m_capacity)
                    container = realloc(container, _getCapacity(m_capacity + lenght));
                for (size_type i = m_size; i > index; i--)
                {
                    if (lenght + i - 1 < m_size)
                        m_alloc.destroy(container + i + lenght - 1);
				    m_alloc.construct(container + i + lenght - 1, container[i - 1]);
                }
                
                size_type i = index;
                while (first != last)
                {
                    if (lenght + i - 1 < m_size)
                        m_alloc.destroy(container + i);
                    m_alloc.construct(container + i, *first);
                    i++;
                    first++;
                }
                m_size += lenght;
            }
            pointer realloc(T *rea, size_type n) // reallocing the vector
            {
                pointer tmp = NULL;
                if (n > 0)
                    tmp = m_alloc.allocate(n);
                for (size_type i = 0; i < m_size; i++) 
                    m_alloc.construct(tmp + i, rea[i]);
                for(size_type i = 0; i < m_size; i++)
					m_alloc.destroy(rea + i);
				if(m_capacity)
					m_alloc.deallocate(rea, m_capacity);
				rea = NULL;
                m_capacity = n;
                return tmp;
            }
            size_type _getCapacity(size_type size)
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
                pointer tmp = NULL;
                if (n > 0)
                    tmp = m_alloc.allocate(_getCapacity(n));
                else
                    return;
                for (size_type i = 0; i < m_size; i++) 
                    m_alloc.construct(tmp + i, container[i]);
                _destroy_container();
                m_capacity = n;
                container = tmp;
		    }
            void _destroy_container()
            {
                if (container && m_capacity != 0)
                {
                    for(size_type i = 0; i < m_size; i++)
                        m_alloc.destroy(container + i);
                    if (m_capacity)
                        m_alloc.deallocate(container, m_capacity);
                    container = NULL;
                }
            }  
            iterator erase(iterator pos) // delete an element at vector[iterator]
            {
                size_type start = pos._ptr - container;
                m_alloc.destroy(pos._ptr);
                m_size--;
                for (size_type i = start; i < m_size; i++)
                {
                    m_alloc.construct(container + i, container[i + 1]);
                    m_alloc.destroy(container + i + 1);
                }
                return iterator(container + start);
            }
            iterator erase(iterator first, iterator last) // delete a list of element from the vector
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
                    m_alloc.destroy(container + shift_index);
                    shift_index++;
                }
                m_size -= lenght;
                return iterator(container + start);
            }
            allocator_type get_allocator() const // get the allocator_type
            {
                return m_alloc;
            }
            
        private:
            pointer container;
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
    bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        if (lhs.size() == rhs.size())
            return true;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    // template <class T, class Alloc>
    // bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if (!(lhs == rhs))
    //         return true;
    //     return false;
    // }
    // template <class T, class Alloc>
    // bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
    //         return true;
    //     return false;
    // }
    // template <class T, class Alloc>
    // bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if (lhs < rhs || lhs == rhs)
    //         return true;
    //     return false;
    // }
    // template <class T, class Alloc>
    // bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if (!(lhs <= rhs))
    //         return true;
    //     return false;
    // }
    // template <class T, class Alloc>
    // bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if (lhs > rhs || lhs == rhs)
    //         return true;
    //     return false;
    // }
}
#endif
