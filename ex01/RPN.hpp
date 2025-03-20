/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:01:06 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/20 14:39:41 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <iostream>
# include <stack>

enum ArithmeticOperator {
	SUBSTRACTION,
	ADDITION,
	MULTIPLICATION,
	DIVISION
};

class RPN {
	private:
		static std::stack<int>	_stack;
		static int				_res;

		RPN();
		RPN(const RPN &r);
		RPN &operator=(const RPN &r);

		static void getStack(std::string &input);
	public:
		~RPN();

		static void processInput(std::string &input);
};

#endif
