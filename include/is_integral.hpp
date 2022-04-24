/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:55:56 by shyrno            #+#    #+#             */
/*   Updated: 2021/11/29 00:12:28 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft
{
	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};
	template<>
	struct is_integral<bool>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const bool>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<int>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const int>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const unsigned int>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<long long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const long long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<unsigned long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const unsigned long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<unsigned long long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const unsigned long long>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<short>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<unsigned short>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const unsigned short>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<char>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const char>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const unsigned char>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<float>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const float>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<double>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const double>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<long double>
	{
		static const bool value = true;
	};
	template<>
	struct is_integral<const long double>
	{
		static const bool value = true;
	};

}
#endif