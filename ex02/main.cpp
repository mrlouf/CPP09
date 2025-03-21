/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 13:41:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac <= 2) {
		std::cout << "Usage: ./PmergeMe <sequence of positive integers>" << std::endl;
		return 1;
	}

	PmergeMe::processInput(++av);

	return 0;
}
