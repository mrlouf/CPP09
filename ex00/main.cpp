/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:51:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/19 17:16:45 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Usage: ./btc <input.txt>" << std::endl;
		return 1;
	}

	try {
		// Memo: ofstream to write, ifstream to read
		std::ifstream input(av[1], std::ios::in);
		if (!input.is_open()) 
			throw std::runtime_error("Error opening the input file");

		BitcoinExchange::processInput(input);
		
		input.close();
	}

	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
