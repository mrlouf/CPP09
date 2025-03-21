/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 17:49:30 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// `shuf -i 1-100000 -n 3000 | tr '\n' ' '`

int	main(int ac, char **av)
{
	if (ac <= 2) {
		std::cout << "Usage: ./PmergeMe <sequence of positive integers>" << std::endl;
		return 1;
	}

	try {
		PmergeMe::processInput(++av);
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
