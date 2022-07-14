/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 04:58:44 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 10:45:14 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include "header.hpp"
#include "pair.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef Compare key_compare;
            typedef btree<value_type> btree;
            typedef Alloc allocator_type;
            typedef T* pointer;
            typedef T const * const_pointer;
            typedef T& reference;
            typedef T const & const_reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef ft::mapIterator<value_type> iterator;
            typedef ft::mapConstIterator<value_type> const_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
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
            map() // Default constructor
            {
                _init_constructor(Compare(), Alloc());
            }
            explicit map(const Compare & comp, const Alloc & alloc) // Default with comp and alloc
            {
                _init_constructor(comp, alloc);
            }
            map(const map & other) // Copy default with another map
            {
                _init_constructor(other.comp, other.m_alloc);
                m_alloc = other.m_alloc;
                comp = other.comp;
                o_alloc = other.o_alloc;
                
                for (const_iterator it = other.begin(); it != other.end(); it++)
                    insert(*it);
            }
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const Compare & comp = Compare(), const Alloc & alloc = Alloc()) // Constructor with a list of element
            {
                _init_constructor(comp, alloc);
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }
            ~map() // Destructor
            {
                clear();
            }
            map & operator=(const map & other) // Assignation operator with another map
            {
                clear();
                _init_constructor(other.comp, other.m_alloc);
                o_alloc = other.o_alloc;
                
				const_iterator it = other.begin();
				const_iterator ite = other.end();
				while(it != ite)
				{
					this->insert(*it);
					it++;
				}
				return (*this);
            }
            void _init_constructor(const Compare &comp, const Alloc &alloc) // create map
            {
                this->comp = comp;
                this->m_alloc = alloc;
                this->root = _new_node(ft::make_pair(key_type(), mapped_type()));
                this->last_insert = NULL;
                this->_end = root;
                m_size = 0;
            }
            allocator_type get_allocator() const // get the allocator_type
            {
                return m_alloc;
            }
            bool empty() const // is the map empty ? 
            {
                if (m_size == 0)
                    return true;
                return false;
            }
            size_type size() const // size of map
            {
                return m_size;
            }
            iterator insert(iterator hint, const value_type & value) // insert a value in the map
            {
                (void)hint;
                btree *tmp;
                bool end_change = 0;
                
                iterator it = find(value.first);
                if (it != _end)
                    return it;
                tmp = root;
                while (tmp != NULL)
                {   
                    if (!last_insert)
                    {
                        tmp = _new_node(value);
                        tmp->daddy = NULL;
                        tmp->left = NULL;
                        tmp->right = _end;
                        
                        root = tmp;
                        last_insert = root;
                        m_size++;
                        _end->daddy = tmp;
                        return iterator(tmp);
                    }
                    if (value.first < tmp->content.first)
                    {
                        if (!tmp->left)
                        {
                            tmp->left = _new_node(value);
                            tmp->left->daddy = tmp;
                            tmp->left->left = NULL;
                            tmp->left->right = NULL;
                            m_size++;
                            return iterator(tmp->left);
                        }
                        tmp = tmp->left;
                    }
                    else
                    {
                        if (!tmp->right || tmp->right == _end)
                        {
                            if (_end == tmp->right)
                                end_change = 1;
                            tmp->right = _new_node(value);
                            tmp->right->daddy = tmp;
                            tmp->right->left = NULL;
                            tmp->right->right = NULL;
                            m_size++;        
                            if (end_change == 1)
                            {
                                tmp->right->right = _end;
                                _end->daddy = tmp->right;
                            }
                            return iterator(tmp->right);
                        }
                        tmp = tmp->right;
                    }
                }
                return iterator(tmp);
            }
            ft::pair<iterator, bool> insert(const value_type& value)
            {
                btree *tmp;
                bool end_change = 0;
                
                tmp = root;
                iterator it = find(value.first);
                if (it != _end)
                    return ft::make_pair(it, 0);
                while (tmp != NULL)
                {
                    if (!last_insert)
                    {
                        tmp = _new_node(value);
                        tmp->daddy = NULL;
                        tmp->left = NULL;
                        tmp->right = _end;
                        
                        root = tmp;
                        last_insert = root;
                        m_size++;
                        _end->daddy = tmp;
                        return ft::make_pair(iterator(tmp), 1); 
                    }
                    if (comp(value.first, tmp->content.first))
                    {
                        if (!tmp->left)
                        {
                            tmp->left = _new_node(value);
                            tmp->left->daddy = tmp;
                            tmp->left->left = NULL;
                            tmp->left->right = NULL;
                            m_size++;
                            return ft::make_pair(iterator(tmp->left), 1);
                        }
                        tmp = tmp->left;
                    }
                    else
                    {
                        if (!tmp->right || tmp->right == _end)
                        {
                            if (_end == tmp->right)
                                end_change = 1;
                            tmp->right = _new_node(value);
                            tmp->right->daddy = tmp;
                            tmp->right->left = NULL;
                            tmp->right->right = NULL;
                            m_size++;        
                            if (end_change == 1)
                            {
                                tmp->right->right = _end;
                                _end->daddy = tmp->right;
                            }
                            return ft::make_pair(iterator(tmp->right), 1);
                        }
                        tmp = tmp->right;
                    }
                }
                return ft::make_pair(iterator(tmp), 0);
            }
            template <class InputIterator>
            void insert(InputIterator first, InputIterator last) // insert a list of element in the map
            {
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }
            reference at(const Key & key) // get vector[key] if exist
            {
                const_iterator it = begin();
                const_iterator ite = end();

                while (it != ite)
                {
                    if (it.ptr->content.first == key)
                        return (it.ptr->content.second);
                    it++;
                }
                throw std::out_of_range("map::at");
            }
            const_reference at (const Key & key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();

                while (it != ite)
                {
                    if (it.ptr->content.first == key)
                        return (it.ptr->content.second);
                    it++;
                }
                throw std::out_of_range("map::at");
            }
            mapped_type & operator[] (const Key & key) // get vector[key], if not exist, create it
            {
                btree *nodders;

                nodders = root;
                iterator it = find(key);
				if (it == _end)
				    insert(ft::make_pair(key, T()));      
				it = find(key);
                return it.ptr->content.second;
            }
            void erase(iterator pos) // erase vector[pos] element with an iterator
            {
                btree *node;

                node = root;
                if (!root)
                    return;
                erase(pos.ptr->content.first);
            }
            void erase(iterator first, iterator last) // erase a list of element
            {
                btree *node;

                node = root;
                if (!root)
                    return;
                iterator copy = first;
                while (first != last)
                    erase((first++).ptr->content.first);
            }
            size_type erase(const Key & k) // erase vector[k] element
            {
                btree *node;
                size_type size = m_size;

                node = root;
                if (root)
                    _erase(node, k);
                if (size != m_size)
                    return 1;
                return 0;
            }
            btree *_erase(btree * node, const key_type & k)
            {
                btree *tmp;
                if (!node)
                    return NULL;
                if (k == node->content.first && node == root && !node->left)
                {
                    if (node->left)
                        node = node->left;
                    else
                        node = node->right;
                    _free_node(root);
                    root = node;
                    return node;
                }
                if (comp(k, node->content.first))
                    node->left = _erase(node->left, k);
                else if (comp(node->content.first, k))
                    node->right = _erase(node->right, k);
                else
                {
                    if (!node->left && !node->right)
                    {
                        _free_node(node);
                        return NULL;
                    }
                    else if (node->left == NULL)
                    {
                        tmp = node->right;
                        node->right->daddy = node->daddy;
                        _free_node(node);
                        return tmp;
                    }
                    else if (node->right == NULL)
                    {
                        tmp = node->left;
                        node->left->daddy = node->daddy;
                        _free_node(node);
                        return tmp;
                    }
                    else
                    {
                        tmp = node->right;
                        while (tmp && tmp->left)
                            tmp = tmp->left;
                        m_alloc.construct(&node->content, tmp->content);
                        node->right = _erase(node->right, tmp->content.first);
                    }
                }
                return node;
            }
            iterator begin() // an iterator to the 1st element
            {
                return iterator(min_value(root));
            }
            const_iterator begin() const
            {
                return const_iterator(min_value(root));
            }
            reverse_iterator rbegin() // a reverse iterator to the 1st element
            {
                return reverse_iterator(end());    
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());    
            }
            iterator end() // and iterator to the last element
            {
                return iterator(_end);
            }
            const_iterator end() const
            {
                return const_iterator(_end);
            }
            reverse_iterator rend() // a reverse iterator to the 1st element
            {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
            void clear() // clear the map
            {
                if (root)
                    _clear_tree(root);
                root = NULL;
                root = _new_node(ft::make_pair(key_type(), mapped_type()));;
                _end = root;
            }
            void _clear_tree(btree *node)
            {
                if (node->left)
                    _clear_tree(node->left);
                if (node->right)
                    _clear_tree(node->right);
                m_alloc.destroy(&node->content);
                o_alloc.deallocate(node, 1);
                m_size = 0;
            }
            void _free_node(btree *node)
			{
                m_size--;
				if(node == NULL)
					return;
				m_alloc.destroy(&node->content);
				o_alloc.deallocate(node, 1);
			}
            btree * _new_node(const value_type & val)
            {
                btree *n_node = o_alloc.allocate(1);

                m_alloc.construct(&n_node->content, val);
                n_node->left = NULL;
                n_node->right = NULL;
                n_node->daddy = NULL;
                return _new_node;
            }
            void _inorder(btree* root)
            {
                if (!root)
                    return;
                _inorder(root->left);
                std::cout << "inorder == " << root->content.first << " " << root->content.second << std::endl;
                _inorder(root->right);
            }
            size_type max_size() const // get the max size
            {
                return o_alloc.max_size();
            }
            key_compare key_comp() const // get the comp
            {
                return comp;
            }
            value_compare value_comp() const // get the fonction value_comp
            {
                return value_compare(comp);
            }
            size_type count(const Key & k) const // get the number of vector[key] existing in the map
            {
                if (find(k)->first == k)
                    return 1;
                return 0;
            }
            iterator find(const Key & key) // get an iterator to map[key]
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
            iterator lower_bound(const Key & key)
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
            const_iterator lower_bound(const Key & key) const
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
            iterator upper_bound( const Key & key)
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
			const_iterator upper_bound( const Key & key) const
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
            ft::pair<iterator,iterator> equal_range(const Key & k)
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }
            ft::pair<const_iterator,const_iterator> equal_range(const Key & k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }
            void swap(map & other) // swap value between map
            {
                allocator_type t_alloc = other.m_alloc;
                size_type t_size = other.m_size;
                btree *t_root = other.root;
                btree *t_end = other._end;
                btree *last_insert = other.last_insert;
                Compare t_comp = other.comp;
                
                typename Alloc::template rebind<btree>::other t_o_alloc = other.o_alloc;
                
                other.m_alloc = m_alloc;
                other.m_size = m_size;
                other.root = root;
                other.last_insert = last_insert;
                other.comp = comp;
                other.o_alloc = o_alloc;
                other._end = _end;
                
                m_alloc = t_alloc; 
                m_size = t_size;
                root = t_root;
                comp = t_comp;
                o_alloc = t_o_alloc;
                _end = t_end;
                
            }
            allocator_type m_alloc;
            size_type m_size;
            btree *last_insert;
            btree *root;
            btree* _end;
            Compare comp;
            typename Alloc::template rebind<btree>::other o_alloc;
            private:
    };
    template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
    template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
        if (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs.size() == rhs.size())
		    return false;
        return true;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
		return (lhs == rhs || lhs < rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
		return !(lhs <= rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
    {
		return !(lhs < rhs);
	}
}

#endif