/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:58:12 by shyrno            #+#    #+#             */
/*   Updated: 2021/12/24 19:04:30 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vector.hpp"
#include <map>

template<class T>
struct btree 
{
	T content;
	btree* left;
	btree* right;
    btree(T x)
    {
        this->content = x;
        this->left = NULL;
        this->right = NULL;
    }
};

template<class T>
class bst
{
    public:
        bst();
        bst(T x)
        {
            tree = new btree<T>(x);
        }
        ~bst()
        {
            
        }
        btree<T>* Insert(T x)
        {
            btree<T> *tmp;

            tmp = tree;
            while (tmp)
            {
                if (x > tmp->content)
                {
                    if (!tmp->right)
                    {
                        tmp->right = new btree<T>(x);
                        break;
                    }
                    tmp = tmp->right;
                }
                else
                {
                    if (!tmp->left)
                    {
                        tmp->left = new btree<T>(x);
                        break;
                    }
                    tmp = tmp->left;
                }
            }
            return tmp;
        }

        btree<T>* _erased(btree<T>* node, T x)
        {
            btree<T>* tmp;
            
            if (x < node->content)
                node->left = _erased(node->left, x);
            else if (x > node->content)
                node->right = _erased(node->right, x);
            else
            {
                if (!node->left && !node->right)
                    return NULL;
                else if (node->left == NULL)
                {
                    tmp = node->right;
                    free(node);
                    return tmp;
                }
                else if (node->right == NULL)
                {
                    tmp = node->left;
                    free(node);
                    return tmp;
                }
                else
                {
                    tmp = node->right;
                    while (tmp && tmp->left)
                        tmp = tmp->left;
                    node->content = tmp->content;
                    node->right = _erased(node->right, tmp->content);
                }
            }
            return node;
        }
        void erase(T x)
        {
            btree<T> *node;

            node = tree;
            _erased(node, x);
        }
        void inorder(btree<T>* root)
        {
            if (!root) 
            {
                return;
            }
            inorder(root->left);
            std::cout << "inorder == " << root->content.first << " " << root->content.second << std::endl;
            inorder(root->right);
        }
        btree<T>* tree;
};

int main()
{
    std::map<int, std::string> mappy;
    
    mappy.insert({0 ,"cookie"});
    mappy.insert({1 ,"co"});
    mappy.insert({2 ,"lo"});
    mappy.insert({-1 ,"pd"});
    std::map<int, std::string>::iterator it(mappy.begin());
    std::map<int, std::string>::iterator ite(mappy.end());
    while(it != ite)
    {
        std::cout << it->first << std::endl;
        it++;
    }
    return (0);
}