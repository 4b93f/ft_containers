/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:11:12 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 11:44:25 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <stdlib.h>
#include <iostream>
#include <string>

namespace ft
{
    template<class T>
    struct btree 
    {
        public:
            T content;
            btree* left;
            btree* right;
            btree* daddy;
            #ifdef __linux__
			    int trick_for_size;
		    #endif
            btree(): right(NULL), left(NULL), daddy(NULL)
            {
                
            }
            btree(T x): content(x), daddy(NULL), right(NULL), left(NULL)
            {
      
            }
    };
    template<class T>
    btree<T>* min_value(btree<T>* node)
    {
		btree<T>* tmp = node;
		while(tmp->left)
			tmp = tmp->left;
		return tmp;
	}
    
    template<class T>
    btree<T>* find_next(btree<T>* node)
    {
        if (node->right)
            return min_value(node->right);
        btree<T> *tmp = node->daddy;
        while (tmp && node == tmp->right)
        {
            node = tmp;
            tmp = tmp->daddy;
        }
        return tmp;
    }


    template<class T>
    btree<T>* find_prev(btree<T>* node)
    {
        if (!node)
            return NULL;
        if (node->left)
            return max_value(node->left);
        btree<T> *tmp = node->daddy;
        while (tmp && node == tmp->left
        {
            node = tmp;
            tmp = tmp->daddy;
        }
        return tmp;
    }
    template<class T>
    btree<T>* max_value(btree<T>* node)
    {
        btree<T>* tmp = node;
		while(tmp && tmp->right)
			tmp = tmp->right;
		return tmp;
    }
}

#endif