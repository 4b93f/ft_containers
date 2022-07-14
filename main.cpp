/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:58:40 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/14 11:41:38 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"
#include <sys/time.h>

template <class T>
void	print(ACCESS::vector<ACCESS::vector<T> >& lst)
{
	for (typename ACCESS::vector<ACCESS::vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename ACCESS::vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void	print(ACCESS::vector<T>& lst)
{
	for (typename ACCESS::vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}
class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template <class T>
void	print_vector(ACCESS::vector<T> &test)
{
	typename ACCESS::vector<T>::iterator		beg = test.begin();
	typename ACCESS::vector<T>::iterator		end = test.end();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename ACCESS::vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void	push_pop_back_tests(void)
{
	//std::cout << std::endl << "PUSH BACK & POP BACK TESTS" << std::endl;
	ACCESS::vector<T> test;

	//std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(i);
		//if (!(i % 10) && i != 0)
		//std::cout << test.size() << ": " << test.capacity() << " - ";
			//std::cout << std::endl;
	}
	//print_vector<T>(test);
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	//print_vector<T>(test);
}

template <class T>
void	resize_tests(void)
{
	std::cout << std::endl << "RESIZE TESTS" << std::endl;
	ACCESS::vector<T> test(12, 12);

	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
}

template <class T>
void	insert_tests()
{
	std::cout << std::endl << "INSERT TESTS" << std::endl;
	ACCESS::vector<T> test(1, 1);
	ACCESS::vector<T> test2(5, 5);

	print_vector<T>(test);
	test.insert(test.begin(), 200, 12);
	print_vector<T>(test);
	test.insert(test.begin() + 12, 200, 30);
	print_vector<T>(test);
	test.insert(test.end(), 12, 50);
	print_vector<T>(test);
	test.insert(test.end() - 1, 0, 60);
	print_vector<T>(test);
	test.insert(test.end() - 1, 1, 70);
	print_vector<T>(test);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<T>(test);
}

template <class T>
void	reserve_tests(void)
{
	std::cout << std::endl << "RESERVE TESTS" << std::endl;
	ACCESS::vector<T> test(65, 7);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(66);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(128);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(1023);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(10252);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	try
	{
		test.reserve(test.max_size() + 1);
	}
	catch(std::length_error &le)
	{
		std::cout << "length error" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	print_vector<T>(test);
}

template <class T>
void	copy_swap_tests(void)
{
	std::cout << std::endl << "COPY && SWAP TESTS" << std::endl;
	ACCESS::vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	print_vector<T>(test);
	ACCESS::vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	print_vector<T>(test_copy);
	ACCESS::vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print_vector<T>(test_range);
	test_copy.swap(test);
	print_vector<T>(test);
	print_vector<T>(test_copy);
	test_copy.swap(test_range);
	print_vector<T>(test_range);
	print_vector<T>(test_copy);
	test.swap(test_copy);
	print_vector<T>(test);
	print_vector<T>(test_copy);
}

template <class T>
void	reverse_it_tests(void)
{
	std::cout << std::endl << "REVERSE IT TESTS" << std::endl;
	ACCESS::vector<T> test;
	for (size_t i = 0; i < 12; i++) { test.push_back(i); }
	typename ACCESS::vector<T>::reverse_iterator		revbeg = test.rbegin();
	for (typename ACCESS::vector<T>::reverse_iterator it = revbeg; it != test.rend(); it++)
	{
		std::cout << *it << " ";
		if (!((revbeg - it) % 10) && it != revbeg)
			std::cout << std::endl;
	}
	std::cout << *(test.rbegin() + 2) << std::endl;
	std::cout << *(test.rend() - 8) << std::endl;
	std::cout << (test.rbegin() == revbeg) << std::endl;
	revbeg++;
	std::cout << *revbeg << std::endl;
	std::cout << (test.rbegin() == test.rend()) << std::endl;
	std::cout << (test.rbegin() <= test.rbegin()) << std::endl;
	std::cout << (test.rbegin() < test.rend()) << std::endl;
	std::cout << (test.rbegin() >= test.rend()) << std::endl;
	revbeg += 3;
	std::cout << *revbeg << std::endl;
	std::cout << std::endl;
}

template <class T>
void	erase_clear_tests(void)
{
	std::cout << std::endl << "ERASE && CLEAR TESTS" << std::endl;
	ACCESS::vector<T> test(31, 12);
	test.erase(test.begin(), test.begin() + 5);
	print_vector<T>(test);
	test.erase(test.begin() + 12, test.begin() + 16);
	print_vector<T>(test);
	test.clear();
	print_vector<T>(test);
}

void	max_size_tests(void)
{
	std::cout << std::endl << "MAX SIZE TESTS" << std::endl;
	ACCESS::vector<int> test(31, 12);
	ACCESS::vector<std::string> test2;
	ACCESS::vector<long long int> test3;
	ACCESS::vector<Awesome> test4;
	ACCESS::vector<unsigned int> test5(12, 340);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
}

void fat_as_fuck()
{
	int i = -1;
	ACCESS::vector<int> test;
	srand(time(0));
	while(++i < 10000)
		test.push_back(rand());
	print_vector(test);
	return ;
}
using namespace std::chrono;

int main()
{
	ft::vector<std::string> lol(10, "xd");

	ft::vector<std::string>::iterator it(lol.begin());
	ft::vector<std::string>::iterator ite(lol.end());
	
	ite--;
	std::cout << it - ite << std::endl;
	struct timeval begin, end;
    gettimeofday(&begin, 0);
	push_pop_back_tests<int>();
	resize_tests<int>();
	insert_tests<int>();
	reserve_tests<int>();
	copy_swap_tests<int>();
	reverse_it_tests<int>();
	erase_clear_tests<int>();
	max_size_tests();
	push_pop_back_tests<Awesome>();
	resize_tests<int>();
	insert_tests<Awesome>();
	reserve_tests<Awesome>();
	copy_swap_tests<Awesome>();
	reverse_it_tests<Awesome>();
	erase_clear_tests<Awesome>();
	fat_as_fuck();
	gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("Time measured: %.10f seconds.\n", elapsed);
}

//#include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }