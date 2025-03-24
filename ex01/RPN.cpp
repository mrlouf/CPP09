/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:01:10 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/24 16:05:41 by nponchon         ###   ########.fr       */
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

	// use stringstream to split and tokenise instead of manual parsing
	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
		if (std::isdigit(token[0])) {
			int i = atoi(token.c_str());
			if (i > 9)
				throw std::runtime_error("Error: unsupported operand '" + token + "'");
			_stack.push(i);
		} else if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (_stack.size() < 2) {
				throw std::runtime_error("Error: insufficient operands");
			}

			// Important rule for RPN, especially division and substraction:
			// when popping two operands, the first popped is the RIGHT-HAND operand
			// while the second popped is the LEFT-HAND operand.
			// [2, 2, 4]: for operator '-', it means 2 - 4, NOT 4 - 2
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();

			if (token == "+") {
				_stack.push(a + b);
			} else if (token == "-") {
				_stack.push(a - b);
			} else if (token == "*") {
				_stack.push(a * b);
			} else if (token == "/") {
				if (b == 0) {
					throw std::runtime_error("Error: division by zero");
				}
				_stack.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error: invalid token '" + token + "'");
	}

	// a valid RPN expression has n-1 operators, where n is the number of operands
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid RPN expression");

	// print final result
	std::cout << _stack.top() << std::endl;

}
