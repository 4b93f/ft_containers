/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:58:40 by shyrno            #+#    #+#             */
/*   Updated: 2022/04/03 19:18:28 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

//fonctionne pas
    // start = map.lower_bound(2);
    // end = map.lower_bound(6);
    // std::cout << end->first << std::endl;
    // ft::map<int, std::string> copy(start, end)


    // verification de doublon, quand key == 0


//size
template<typename T>
void print_container(ft::vector<T> & container)
{
    for(size_t i = 0; i < container.size(); i++)
        std::cout << "Container[" << i << "] = " <<container[i] << " " << std::endl;
    std::cout << std::endl;
}

template<typename T>
void state(ft::vector<T> & x)
{
    std::cout << "<-------------------->" << std::endl;
    std::cout << "[ACTUAL STATE]" << std::endl;
    std::cout << "Container content : " << std::endl;
    print_container(x);
    std::cout << "Size : " << x.size() << std::endl;
    std::cout << "Capacity : " << x.capacity() << std::endl;
    std::cout << "Empty ? : " << x.empty() << std::endl;
    
    std::cout << "<-------------------->" << std::endl << std::endl;
}

// int main()
// {
//     ft::vector<int> foo;
//     ft::vector<int>::const_iterator it_foo = foo.begin();

//     std::cout << "<FT TEST>" << std::endl;
    // {
    //     std::cout << "[Starting with an empty Default constructor] ! " << std::endl << std::endl;
    //     ft::vector<int> vec;
    //     state(vec);
    // }

    // {
    //     std::cout << "Now with another constructor ! " << std::endl;
    //     //ft::vector<int> vec(7, 100);
    //     //state(vec);
    // }
    // {
    //     std::cout << "[CLASSIC USAGE] ! " << std::endl << std::endl;
    //     ft::vector<int> vec;
    //     std::cout << "<Adding some value> ... " << std::endl;
        
    //     vec.push_back(1);
    //     vec.push_back(3);
    //     vec.push_back(4);
    //     vec.push_back(-1);
    //     state(vec);
        
    //     std::cout << "<Now we pop the last value ...>" << std::endl;

    //     vec.pop_back();
    //     state(vec);

    //     std::cout << "<And again ...>" << std::endl;
        
    //     vec.pop_back();
    //     state(vec);
    // }
    // {
    //     std::cout << "[MAX_SIZE TEST] ! " << std::endl << std::endl;
    //     ft::vector<int> vec;
        
    //     std::cout << "Vec max_size possible : " << vec.max_size() << std::endl;
        
    //     std::cout << "<Adding some value> ... " << std::endl;

    //     vec.push_back(1);
    //     vec.push_back(-9);
    //     vec.push_back(77777);
    //     vec.push_back(42);

    //     std::cout << "vec max_size possible : " << vec.max_size() << std::endl;
    // }
    //return 0;
    // std::map<std::string, int> map;
    // map.insert(std::pair<std::string, int>("cookie", 1));
    // start = map.begin();
    // std::cout << start->second <<std::endl;
//}

// int		main(void)
// {
// 	ft::stack<int> ctnr;

// 	ctnr.push(21);
// 	ctnr.push(42);
// 	ctnr.push(1337);
// 	ctnr.push(19);
// 	ctnr.push(0);
// 	ctnr.push(183792);

// 	ft::stack<int> stck(ctnr);
// 	ft::stack<int> stck2(ctnr);

//     std::cout << "!" << std::endl;
//     if (stck == stck2)
//         std::cout << "NANI" << std::endl;
    
#include <list>
//typedef std::map<T1, T2>::value_type T3;
int main()
{
    //std::list<T3> lst;
    ft::map<char, int> map;

    map['a'] = 6;
    map['b'] = 12;
    map.inorder(map.tree);
    // test.lower_bound(1)->second = 2;
    // std::cout << test.size() << std::endl;
	// test.upper_bound(7)->second = 842;
    return 0;
}