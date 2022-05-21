/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:04:27 by shyrno            #+#    #+#             */
/*   Updated: 2022/05/19 20:01:03 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "utils.hpp"
#include <cstddef>

namespace ft
{
    template < class T >
	struct mapConstIterator;
	template < class T >
	struct vectorConstIterator;
    struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    struct contiguous_iterator_tag: public random_access_iterator_tag { };
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
    struct iterator 
    {
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
    template <class Iter>
    struct iterator_traits
    {   
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };
    template< class T >
	struct vectorIterator : public ft::iterator<ft::random_access_iterator_tag, T, std::ptrdiff_t , T*, T&> 
    {
        public:
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ft::random_access_iterator_tag iterator_category;
            vectorIterator()
            {

            }
            vectorIterator(T *ptr)
            {
                //std::cout << "creation\n";
                _ptr = ptr;
            }
            vectorIterator& operator=(const vectorIterator & rhs)
            {
                _ptr = rhs._ptr;
			    return *this;
            }
            virtual ~vectorIterator()
            {
                
            }
            difference_type operator-(const vectorIterator & rhs)
            {
                return this->_ptr - rhs._ptr;
            }
            pointer operator->() const
            {
                return _ptr;
            }
            reference operator*() const
            {
                return *_ptr;
            }
            reference operator[](difference_type n) const 
            {
			    return _ptr[n];
		    }
            vectorIterator& operator++() 
            {
                _ptr++;
                return *this;
		    }
            vectorIterator operator++(int) 
            {
                vectorIterator tmp = *this;
                _ptr++;
                return tmp;
            }
            vectorIterator operator+(difference_type n)
            {
                return vectorIterator(_ptr + n);
            }
            friend vectorIterator operator+(difference_type nbr, vectorIterator rhs)
            {
                return vectorIterator(nbr + rhs._ptr);
            }
            vectorIterator operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }
            vectorIterator& operator--() 
            {
                _ptr--;
                return *this;
            }
            vectorIterator operator--(int)
            {
                vectorIterator tmp = *this;
                _ptr--;
                return tmp;
            }
            vectorIterator operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }
            vectorIterator operator-(difference_type n)
            {
                return vectorIterator(_ptr - n);
            }
            bool operator==(const vectorIterator & rhs) const
			{
				if(this->_ptr == rhs._ptr)
					return (1);
				return (0);
			}
			bool operator==(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr == rhs._ptr)
					return (1);
				return (0);
			}
			bool operator!=(const vectorIterator & rhs) const
			{
				if(this->_ptr != rhs._ptr)
					return (1);
				return (0);
			}
			bool operator!=(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr != rhs._ptr)
					return (1);
				return (0);
			}
			bool operator>=(const vectorIterator & rhs) const
			{
				if(this->_ptr >= rhs._ptr)
					return (1);
				return (0);
			}
			bool operator>=(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr >= rhs._ptr)
					return (1);
				return (0);
			}
			bool operator<=(const vectorIterator & rhs) const
			{
				if(this->_ptr <= rhs._ptr)
					return (1);
				return (0);
			}
			bool operator<=(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr <= rhs._ptr)
					return (1);
				return (0);
			}
			bool operator<(const vectorIterator & rhs) const
			{
				if(this->_ptr < rhs._ptr)
					return (1);
				return (0);
			}
			bool operator<(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr < rhs._ptr)
					return (1);
				return (0);
			}
			bool operator>(const vectorIterator & rhs) const
			{
				if(this->_ptr > rhs._ptr)
					return (1);
				return (0);
			}
			bool operator>(const vectorConstIterator<T> & rhs) const
			{
				if(this->_ptr > rhs._ptr)
					return (1);
				return (0);
			}
            T* _ptr;
        private:
    };
    template< class T >
	struct vectorConstIterator : public ft::iterator<ft::random_access_iterator_tag, T, std::ptrdiff_t , T*, T&> 
    {
        public:
            typedef  std::ptrdiff_t difference_type;
            typedef const T value_type;
            typedef const T* pointer;
            typedef const T& reference;
            typedef ft::random_access_iterator_tag iterator_category;
            vectorConstIterator()
            {

            }
            vectorConstIterator(T *ptr)
            {
                //std::cout << "1" << std::endl;
                _ptr = ptr;
            }
            vectorConstIterator(const vectorConstIterator & src): _ptr(src._ptr)
            { 
                //std::cout << "2" << std::endl;
            }
            vectorConstIterator(const vectorIterator<T> & src): _ptr(src._ptr)
            { 
                //std::cout << "3" << std::endl;
            }
            vectorConstIterator& operator=(const vectorConstIterator & rhs)
            {
                _ptr = rhs._ptr;
			    return *this;
            }
            virtual ~vectorConstIterator()
            {
                
            }
            difference_type operator-(const vectorConstIterator & rhs) const
            {
                return this->_ptr - rhs._ptr;
            }
            difference_type operator-(const vectorConstIterator<T> & rhs)
            {
                return this->_ptr - rhs._ptr;
            }
            
            pointer operator->() const
            {
                return _ptr;
            }
            reference operator*() const
            {
                return *_ptr;
            }
            reference operator[](difference_type n) const 
            {
			    return *(_ptr + n);
		    }
            vectorConstIterator& operator++() 
            {
                _ptr++;
                return *this;
		    }
            vectorConstIterator operator++(int) 
            {
                vectorConstIterator tmp = *this;
                _ptr++;
                return tmp;
            }
            vectorConstIterator operator+(difference_type n) const
            {
                return vectorConstIterator(_ptr + n);
            }
            vectorConstIterator operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }
            vectorConstIterator operator+(difference_type n) 
            {
                return vectorConstIterator(_ptr + n);
            }
            friend vectorConstIterator operator+(difference_type nbr, vectorConstIterator & rhs) 
            {
                return vectorConstIterator(rhs._ptr + nbr);
            }
            vectorConstIterator& operator--() 
            {
                _ptr--;
                return *this;
            }
            vectorConstIterator operator--(int)
            {
                vectorConstIterator tmp = *this;
                _ptr--;
                return tmp;
            }
            vectorConstIterator operator-(difference_type n) const
            {
                return vectorConstIterator(_ptr - n);
            }
            vectorConstIterator operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }
            bool operator==(const vectorConstIterator & lhs) const 
            {
                if (this->_ptr == lhs._ptr)
                    return true;
                return false;
		    }
		    bool operator!=(const vectorConstIterator & lhs) const
            {
			    if (this->_ptr != lhs._ptr)
                    return true;
                return false;
		    }
            bool operator<(const vectorConstIterator & lhs) const 
            {
                if (this->_ptr < lhs._ptr)
                    return true;
                return false;
		    }
            bool operator<=(const vectorConstIterator & lhs) const 
            {
                if (this->_ptr <= lhs._ptr)
                    return true;
                return false;
		    }
		    bool operator>(const vectorConstIterator & lhs) const
            {
			    if (this->_ptr > lhs._ptr)
                    return true;
                return false;
		    }
		    bool operator>=(const vectorConstIterator & lhs) const
            {
			    if (this->_ptr >= lhs._ptr)
                    return true;
                return false;
		    }
            T* _ptr;
        private:
    };
    template <class Iterator> 
    struct reverse_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
            reverse_iterator(): _iter(NULL)
            {
                
            }
            explicit reverse_iterator (iterator_type it): _iter(it)
            {
                
            }
            template <class U>
            reverse_iterator (const reverse_iterator<U> & rev_it): _iter(rev_it.base())
            {

            }
            // template <class U>
            // reverse_iterator& operator=( const reverse_iterator<U>& other ) 
            // {
            //     _iter = other.base();
            //     return *this;
		    // }
            iterator_type base() const
            {
                return _iter;
            }
            reference operator*() const
            {
                Iterator tmp = _iter;
                return *--tmp;
            }
            pointer operator->() const
            {
                return &(operator*());
            }
            reference operator[](difference_type n) const
			{
                return (base()[(-n) - 1]);
			}
            reverse_iterator& operator++()
            {
                _iter--;
                return *this;
            }
            reverse_iterator& operator--()
            {
                _iter++;
                return *this;
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                _iter--;
                return tmp;
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                _iter++;
                return tmp;
            }
            reverse_iterator operator+(difference_type n) const 
            {
			    return reverse_iterator(base() - n);
		    }
		    reverse_iterator operator-(difference_type n) const 
            {
			    return reverse_iterator(base() + n);
		    }
            template <class U>
            difference_type operator-(const reverse_iterator<U> & x) const 
            {
			    return (this->base() - x.base()) * -1; 
		    }
		    reverse_iterator& operator+=(difference_type n) 
            {
			    _iter -= n;
			    return *this;
		    }
		    reverse_iterator& operator-=(difference_type n)
            {
			    _iter += n;
			    return *this;
		    }
        protected:
            Iterator _iter;
    };
    template< class T >
    struct mapIterator : public ft::iterator<bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef btree<T> btree;
            typedef ft::bidirectional_iterator_tag iterator_category;
            mapIterator(): ptr(NULL)
            {
                
            }
            mapIterator(btree *node)
            {
                ptr = node;
            }
            mapIterator & operator=(const mapIterator & rhs)
            {
                ptr = rhs.ptr;
                return *this;
            }
            virtual ~mapIterator()
            {
                
            }
            mapIterator(const mapIterator & src)
            {
                ptr = src.ptr;
            }
            bool operator==(const mapIterator & rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            bool operator!=(const mapIterator & rhs) const
            {
                return this->ptr != rhs.ptr;
            }
            reference operator*() const
            {
                return ptr->content;
            }
            pointer operator->() const
            {
                return &ptr->content;
            }
            mapIterator & operator++()
            {
                ptr = find_next(ptr);
                return *this;
            }
            mapIterator operator++(int)
            {
                mapIterator tmp = *this;
                operator++();
                return tmp;
            }
            mapIterator & operator--()
            {
                ptr = find_prev(ptr);
                return *this;
            }
            mapIterator operator--(int)
            {
                mapIterator tmp = *this;
                operator--();
                return tmp;
            }
            btree* ptr;
    };
    template< class T >
    struct mapConstIterator : public iterator<bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            typedef std::ptrdiff_t difference_type;
            typedef const T value_type;
            typedef const T* pointer;
            typedef const T& reference;
            typedef btree<T> btree;
            typedef ft::bidirectional_iterator_tag iterator_category;
            mapConstIterator(): ptr(NULL)
            {
                
            }
            mapConstIterator(btree *node)
            {
                ptr = node;
            }
            mapConstIterator(const mapConstIterator & src): ptr(src.ptr)
            {
                
            }
            mapConstIterator(const mapIterator<T> & src): ptr(src.ptr)
            { 
                
            }
            mapConstIterator & operator=(const mapConstIterator & rhs)
            {
                ptr = rhs.ptr;
                return *this;
            }
            virtual ~mapConstIterator()
            {
                
            }
            bool operator==(const mapConstIterator & rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            bool operator!=(const mapConstIterator & rhs) const
            {
                return this->ptr != rhs.ptr;
            }
            reference operator*() const
            {
                return ptr->content;
            }
            pointer operator->() const
            {
                return &ptr->content;
            }
            mapConstIterator & operator++()
            {
                ptr = find_next(ptr);
                return *this;
            }
            mapConstIterator operator++(int)
            {
                mapConstIterator tmp = *this;
                operator++();
                return tmp;
            }
            mapConstIterator & operator--()
            {
                ptr = find_prev(ptr);
                return *this;
            }
            mapConstIterator operator--(int)
            {
                mapConstIterator tmp = *this;
                operator--();
                return tmp;
            }
            btree* ptr;
    };
    template< class Iterator1, class Iterator2 >
	    bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
        {
		    return (lhs.base() == rhs.base());
	    }
        template< class Iterator1, class Iterator2 >
        bool operator!=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs)
        {
            return (lhs.base() != rhs.base());
        }
        template< class Iterator1, class Iterator2 >
        bool operator<(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) 
        {
            return (lhs.base() > rhs.base());
        }
        template< class Iterator1, class Iterator2 >
        bool operator<=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) 
        {
            return (lhs.base() >= rhs.base());
        }
        template< class Iterator1, class Iterator2 >
        bool operator>(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs)
        {
            return (lhs.base() < rhs.base());
        }
        template< class Iterator1, class Iterator2 >
        bool operator>=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs)
        {
            return (lhs.base() <= rhs.base());
        }

        template< class Iter >
        reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
        {
            return reverse_iterator<Iter>(it.base() - n);
        }

        template< class Iterator >
        typename reverse_iterator<Iterator>::difference_type
        operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
        {
            return rhs.base() - lhs.base();
        }
}

#endif