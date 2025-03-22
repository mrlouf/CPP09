/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:50 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 19:42:54 by nponchon         ###   ########.fr       */
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

void PmergeMe::getContainers(char **av, std::vector<int> &v, std::list<int> &l) {
	for (unsigned int i = 0; av[i]; i++) {
		
		std::string input = av[i];
		std::stringstream ss(input);
		int integer;

		if (!(ss >> integer) || !(ss.eof()))
			throw std::runtime_error("Error: invalid input '" + input + "'");
		else if (integer < 0)
			throw std::runtime_error("Error: unsupported negative integer '" + input + "'");

		v.push_back(integer);
		l.push_back(integer);

	}
}

void PmergeMe::flatten(const std::pair<int, int> &element, std::vector<int> &result) {
	result.push_back(element.first);
    if (element.first != element.second) {
        result.push_back(element.second);
    }
}

void PmergeMe::flatten(const std::pair<std::pair<int, int>, std::pair<int, int> > &element, std::vector<int> &result) {
	flatten(element.first, result);
	flatten(element.second, result);
}

void PmergeMe::flatten(const std::pair<int, int> &element, std::list<int> &result) {
	result.push_back(element.first);
	if (element.first != element.second) {
		result.push_back(element.second);
	}
}

void PmergeMe::flatten(const std::pair<std::pair<int, int>, std::pair<int, int> > &element, std::list<int> &result) {
	flatten(element.first, result);
	flatten(element.second, result);
}

void PmergeMe::processInput(char **av) {

	std::vector<int>	vector;
	std::list<int>		list;

	getContainers(av, vector, list);
	
	std::cout << "Before:	"; printContainer(vector);

	std::clock_t vectorStartTime = std::clock();
	vector = recursiveVectorMerge(vector);
	std::clock_t vectorEndTime = std::clock();

	std::clock_t listStartTime = std::clock();
	list = recursiveListMerge(list);
	std::clock_t listEndTime = std::clock();

	std::cout << "After:	"; printContainer(list);

	double elapsedVector = double(vectorEndTime - vectorStartTime) / CLOCKS_PER_SEC * 1000000;
	double elapsedList = double(listEndTime - listStartTime) / CLOCKS_PER_SEC * 1000000;
	//std::cout << std::fixed;
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector:	" << elapsedVector << " us" << std::endl;
	std::cout << "Time to process a range of " << list.size() << " elements with std::list:	" << elapsedList << " us" << std::endl;

}