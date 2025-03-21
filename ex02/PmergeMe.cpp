/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:50 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 14:06:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) {
	(void)other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::processInput(char **av) {

// check for positive integers only

	std::cout << "Before:";
	for (unsigned int i = 0; av[i]; i++) {
		std::cout << ' ' << av[i];
	}
	std::cout << std::endl;

// sort sequence in container 1
// sort sequence in container 2

	std::cout << "After:";
	for (unsigned int i = 0; av[i]; i++) {
		std::cout << ' ' << av[i];
	}
	std::cout << std::endl;
}