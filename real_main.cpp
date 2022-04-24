/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 22:49:25 by shyrno            #+#    #+#             */
/*   Updated: 2021/12/29 23:31:39 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <deque>
#include <stack>
#include <vector>
#include <map>
#include <stdlib.h>

template<typename T>
void print_container(std::vector<T> & container)
{
    for(size_t i = 0; i < container.size(); i++)
        std::cout << container[i] << " " << std::endl;
    std::cout << std::endl;
}

template<typename T>
void state(std::vector<T> & x)
{
    std::cout << "<-------------------->" << std::endl;
    std::cout << "[ACTUAL STATE]" << std::endl;
    std::cout << "Container content : ";
    print_container(x);
    std::cout << "Size : " << x.size() << std::endl;
    std::cout << "Capacity : " << x.capacity() << std::endl;
    std::cout << "Empty ? : " << x.empty() << std::endl;
    std::cout << "<-------------------->" << std::endl << std::endl;
}

int main()
{
    std::cout << std::endl << "<STD TEST>" << std::endl;
    {
        std::cout << "Starting with an empty Default constructor ! " << std::endl;
        std::vector<int> vec;
        state(vec);
    }

    {
        std::cout << "Now with another constructor ! " << std::endl;
        std::vector<int> vec(7, 100);
        state(vec);
    }
    // std::map<std::string, int> map;
    // map.insert(std::pair<std::string, int>("cookie", 1));
    // start = map.begin();
    // std::cout << start->second <<std::endl;
}