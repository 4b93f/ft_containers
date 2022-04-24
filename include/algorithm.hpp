/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 05:37:03 by shyrno            #+#    #+#             */
/*   Updated: 2022/01/11 19:31:50 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        (void)last2;
        while (first1 != last1)
        {
            if (first1 != first2)
                return false;
            first1++;
            first2++;
        }
        return true;
    }
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2 == last2 || *first2<*first1) 
                return false;
            else if (*first1<*first2) 
                return true;
            ++first1; 
            ++first2;
        }
        return (first2 != last2);
    }
};


#endif