/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:20:40 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 11:23:18 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP
#include "utils.hpp"

namespace ft
{
    
template <class T1, class T2>
    struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;
            pair()
            {
                first = first_type();
                second = second_type();
            }
            template<class U, class V>
            pair(const pair<U,V> & pr)
            {
                first = pr.first;
                second = second.second;
            }
            template<class U, class V>
            pair(pair<U,V> & pr)
            {
                first = pr.first;
                second = second.second;
            }
            pair(const first_type & x, const second_type & y)
            {
                first = x;
                second = y;
            }
            pair & operator=(const pair & other)
            {
                first = other.first;
                second = other.second;
                return (*this);
            }     
            first_type first;
            second_type second;
        private:
    };
    template< class type1, class type2 >
    ft::pair<type1,type2> make_pair(type1 t, type2 u)
    {
        return pair<type1, type2>(t, u);
    }     
    // template< class T1, class T2 >
    // bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     return lhs.first == rhs.first && lhs.second == rhs.second;
    // }
    // template< class T1, class T2 >
    // bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     return (!(lhs == rhs));
    // }
    // template< class T1, class T2 >
    // bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     if (lhs.first < rhs.first)
    //         return true;
    //     if (rhs.first < lhs.first)
    //         return false;
    //     if (lhs.second < rhs.second)
    //         return true;
    //     else
    //         return false;
    // }
    // template< class T1, class T2 >
    // bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     return (!(rhs< lhs));
    // }
    // template< class T1, class T2 >
    // bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     return rhs < lhs;
    // }
    // template< class T1, class T2 >
    // bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    // {
    //     return (!(lhs < rhs));
    // }
}

#endif