/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 04:58:44 by shyrno            #+#    #+#             */
/*   Updated: 2022/04/25 00:02:01 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include "iterator.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include "iostream"
#include <memory>
#include <algorithm>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Compare key_compare;
            typedef btree<value_type> btree;
            typedef Alloc allocator_type;
            typedef T* pointer;
            typedef T const * const_pointer;
            typedef T& reference;
            typedef T const & const_reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef mapIterator<value_type> iterator;
            typedef mapConstIterator<value_type> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
            typedef reverse_iterator<iterator> reverse_iterator;
            class value_compare: std::binary_function<value_type, value_type, bool>
            {  
                protected:
                    Compare comp;
                public:
                    value_compare(Compare c): comp(c)
                    {
                            
                    }
                    bool operator()(const value_type& lhs, const value_type& rhs) const
                    {
                        return comp(lhs.first, rhs.first);
                    }
            };
            map()
            {
                //std::cout << "[STEP 1]\n";
                this->comp = key_compare();
                m_alloc = Alloc();
                root = NULL;
                m_size = 0;
                tree = new_node(ft::make_pair(key_type(), mapped_type()));
                _end = tree;
            }
            map(const map& x)
            {
                m_alloc = x.m_alloc;
                m_size = x.m_size;
                comp = x.comp;
                o_alloc = x.o_alloc;
                root = NULL;
                tree = new_node(ft::make_pair(key_type(), mapped_type()));
                
                for (const_iterator it = x.begin(); it != x.end(); it++)
                    insert(*it);
            }
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                //std::cout << "[STEP 1]\n";
                this->comp = comp;
                this->m_alloc = alloc;
                root = NULL;
                m_size = 0;
                m_alloc = Alloc();
                tree = new_node(ft::make_pair(key_type(), mapped_type()));
                _end = tree;
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }
            ~map()
            {
                if (tree)
                    clear();
            }
            map & operator=(const map & other)
            {
                clear();
                m_alloc = other.m_alloc;
                m_size = 0;
                tree = other.tree;
				const_iterator it = other.begin();
				const_iterator ite = other.end();
				while(it != ite)
				{
					this->insert(*it);
					it++;
				}
				return (*this);
            }
            allocator_type get_allocator() const
            {
                return m_alloc;
            }
            bool empty() const
            {
                if (m_size == 0)
                    return true;
                return false;
            }
            size_type size() const
            {
                return m_size;
            }
            iterator insert(iterator position, const value_type & val)
            {
                std::cout << "insert" << std::endl;
                (void)position;
                (void)val;
            }
            ft::pair<iterator, bool> insert(const value_type& val)
            {

                btree *tmp;

                tmp = tree;
                while (tmp != NULL)
                {
                    if (!root)
                    {
                        tmp = new_node(val);
                        tmp->daddy = NULL;
                        tmp->left = NULL;
                        tmp->right = NULL;
                        
                        root = tmp;
                        tree = tmp;
                        m_size++;
                        _end = tree->right;
                        return ft::make_pair(iterator(tmp), 1); 
                    }
                    if (val.first < tmp->content.first)
                    {
                        if (!tmp->left)
                        {
                            tmp->left = new_node(val);
                            tmp->left->daddy = tmp;
                            tmp->left->left = NULL;
                            tmp->left->right = NULL;
                            m_size++;
                            //_end = max_value(tree)->right;
                            return ft::make_pair(iterator(tmp->left), 1);
                        }
                        tmp = tmp->left;
                    }
                    else
                    {
                        if (!tmp->right)
                        {
                            tmp->right = new_node(val);
                            tmp->right->daddy = tmp;
                            tmp->right->left = NULL;
                            tmp->right->right = NULL;
                            m_size++;
                            _end = max_value(root)->right;
                            return ft::make_pair(iterator(tmp->right), 1);
                        }
                        tmp = tmp->right;
                    }
                }
                return ft::make_pair(iterator(tmp), 0);
            }
            template <class InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
                std::cout << "insert" << std::endl;
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }
            mapped_type& operator[] (const key_type& k)
            {
                btree *nodders;

                nodders = tree;
                iterator it = find(k);
				if (it == _end)
				    insert(ft::make_pair(k, T()));      
				it = find(k);
                return it.ptr->content.second;
            }

            btree *modCheck(btree *node, const key_type& k) const
            {
                if (!node || !node->content.first)
                    return NULL;
                else if (node->content.first == k)
                    return node;
                else if (node->left)
                    return modCheck(node->left, k);
                else
                    return modCheck(node->right, k);
            }
            size_type erase(const key_type & k)
            {
                btree *node;

                node = tree;
                _erase(node, k);
                return 1;
            }
            void erase(iterator position)
            {
                btree *node;

                node = tree;
                _erase(node, position.ptr->content.first);
            }
            void erase(iterator first, iterator last)
            {
                btree *node;

                node = tree;
                while (first != last)
                {
                    _erase(node, first.ptr->content.first);
                    first++;
                }
            }
            btree *_erase(btree * node, const key_type & k)
            {
                btree *tmp;
                
                if (k < node->content.first)
                    node->left = _erase(node->left, k);
                else if (k > node->content.first)
                        node->right = _erase(node->right, k);
                else
                {
                    if (!node->left && !node->right)
                        return NULL;
                    else if (node->left == NULL)
                    {
                        tmp = node->right;
                        m_alloc.destroy(&node->content);
			            o_alloc.deallocate(node, 1);
                        return tmp;
                    }
                    else if (node->right == NULL)
                    {
                        tmp = node->left;
                        m_alloc.destroy(&node->content);
			            o_alloc.deallocate(node, 1);
                        return tmp;
                    }
                    else
                    {
                        tmp = node->right;
                        while (tmp && tmp->left)
                            tmp = tmp->left;
                        // m_alloc.destroy(&node->content);
			            // o_alloc.deallocate(node, 1);
                        m_alloc.construct(&node->content, tmp->content);
                        node->right = _erase(node->right, tmp->content.first);
                        m_size--;
                    }
                }
                return node;
            }
            iterator begin()
            {
                return iterator(min_value(tree));
            }
            const_iterator begin() const
            {
                return const_iterator(min_value(tree));
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());    
            }
            iterator end()
            {
                return iterator(_end);
            }
            const_iterator end() const
            {
                return const_iterator(_end);
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
            void clear()
            {
                clear_tree(tree);
                root = NULL;
                tree = new_node(ft::make_pair(key_type(), mapped_type()));;
                _end = tree;
            }
            void clear_tree(btree *node)
            {
                if (node->left)
                    clear_tree(node->left);
                if (node->right)
                    clear_tree(node->right);
                m_alloc.destroy(&node->content);
                o_alloc.deallocate(node, 1);
                m_size = 0;
            }
            btree *new_node(const value_type & val)
            {
                btree *new_node = o_alloc.allocate(1);

                m_alloc.construct(&new_node->content, val);
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->daddy = NULL;
                return new_node;
            }
            void inorder(btree* root)
            {
                if (!root)
                    return;
                inorder(root->left);
                std::cout << "inorder == " << root->content.first << " " << root->content.second << std::endl;
                inorder(root->right);
            }
            size_type max_size() const
            {
                return o_alloc.max_size();
            }
            key_compare key_comp() const
            {
                return comp;
            }
            value_compare value_comp() const
            {
                return value_compare(comp);
            }
            size_type count(const key_type& k) const
            {
                if (find(k)->first == k)
                    return 1;
                return 0;
            }
            iterator find(const Key & key)
            {
                iterator it = begin();

                while (it != end() && it->first != key)
                    it++;
                return it;
            }
            const_iterator find(const Key & key) const
            {
                const_iterator it = begin();

                while (it != end() && it->first != key)
                    it++;
                return it;
            }
            iterator lower_bound(const key_type& key)
            {
                iterator it = begin();
                iterator ite = end();
                while(it != ite)
                {
                    if(!comp(it->first, key))
                        return (it--);
                    it++;
                }
                return (it);
            }
            const_iterator lower_bound(const key_type& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while(it != ite)
                {
                    if(!comp(it->first, key))
                        return (it--);
                    it++;
                }
                return (it);
            }
            iterator upper_bound( const key_type & key )
			{
				iterator it = begin();
				iterator ite = end();
				while(it != ite)
				{
					if(comp(key, it->first))
						return (it--);
					it++;
				}
				return (it);
			}
			const_iterator upper_bound( const key_type & key ) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while(it != ite)
				{
					if(comp(key, it->first))
						return (it--);
					it++;
				}
				return (it);
			}
            ft::pair<iterator,iterator> equal_range(const key_type & k)
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }
            ft::pair<const_iterator,const_iterator> equal_range(const key_type & k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }
            void swap(map & x)
            {
                allocator_type t_alloc = x.m_alloc;
                size_type t_size = x.m_size;
                btree *t_tree = x.tree;
                btree *t_root = x.root;
                Compare t_comp = x.comp;
                typename Alloc::template rebind<btree>::other t_o_alloc = x.o_alloc;


                x.m_alloc = m_alloc;
                x.m_size = m_size;
                x.tree = tree;
                x.root = root;
                x.comp = comp;
                x.o_alloc = o_alloc;
                
                m_alloc = t_alloc; 
                m_size = t_size;
                tree = t_tree;
                root = t_root;
                comp = t_comp;
                o_alloc = t_o_alloc;
            }
            allocator_type m_alloc;
            size_type m_size;
            btree *tree;
            btree *root;
            btree* _end;
            Compare comp;
            typename Alloc::template rebind<btree>::other o_alloc;
            private:
    };
    // template< class Key, class T, class Compare, class Alloc >
	// bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
	// 	if (lhs.size() != rhs.size())
	// 		return false;
	// 	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	// }
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
    //     if (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs.size() == rhs.size())
	// 	    return false;
    //     return true;
	// }
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
    //     (void)lhs;
    //     (void)rhs;
	// 	//return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	// }
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
	// 	return (lhs == rhs || lhs < rhs);
	// }
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
	// 	return !(lhs <= rhs);
	// }
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    // {
	// 	return !(lhs < rhs);
	// }
}

#endif