/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:01:10 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/20 16:57:45 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<int>	RPN::_stack;

RPN::RPN() {}
RPN::RPN(const RPN &r) {
	(void)r;
}
RPN &RPN::operator=(const RPN &r) {
	(void)r;
	return *this;
}
RPN::~RPN() {}

void RPN::processInput(std::string &input) {
	
	if (input.empty())
		throw std::runtime_error("Error: empty input");

	int res = 0;

	

}
