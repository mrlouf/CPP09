/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:52 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/20 14:17:33 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char** av) {
	if (ac != 2) {
		std::cerr << "Usage: ./RPN <arithmetic expression>" << std::endl;
		return 1;
	}
	
	try {
		std::string input = av[1];
		RPN::processInput(input);
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}