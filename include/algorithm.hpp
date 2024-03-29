/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 05:37:03 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 11:17:39 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
namespace ft
{
    template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
    {
		while(first1 != last1 && first2 != last2)
        {
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 == last2;
	}
	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2, BinaryPredicate p ) {
		while(first1 != last1 && first2 != last2) {
			if (!p(*first1, *first2))
				return false;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 == last2;
	}
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2,
                                Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
};


#endif