/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:50 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/24 14:37:22 by nponchon         ###   ########.fr       */
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

int PmergeMe::getJacobsthal(int n) {
    return static_cast<int>(round((pow(2, n + 1) + pow(-1, n)) / 3)); 
}

void PmergeMe::getVector(char **av, std::vector<int> &v) {
	for (unsigned int i = 0; av[i]; i++) {
		
		std::string input = av[i];
		std::stringstream ss(input);
		int integer;

		if (!(ss >> integer) || !(ss.eof()))
			throw std::runtime_error("Error: invalid input '" + input + "'");
		else if (integer < 0)
			throw std::runtime_error("Error: unsupported negative integer '" + input + "'");

		v.push_back(integer);

	}
}

void PmergeMe::getDeque(char **av, std::deque<int> &d) {
	for (unsigned int i = 0; av[i]; i++) {
		
		std::string input = av[i];
		std::stringstream ss(input);
		int integer;

		if (!(ss >> integer) || !(ss.eof()))
			throw std::runtime_error("Error: invalid input '" + input + "'");
		else if (integer < 0)
			throw std::runtime_error("Error: unsupported negative integer '" + input + "'");

		d.push_back(integer);

	}
}

bool PmergeMe::isVectorSorted(const std::vector<int> &vec)
{
	for (size_t i = 1; i < vec.size(); ++i)
	{
		if (vec[i - 1] > vec[i])
			return false;
	}
	return true;
}

bool PmergeMe::isDequeSorted(const std::deque<int> &lst)
{
	std::deque<int>::const_iterator it = lst.begin();
	std::deque<int>::const_iterator nextIt = it;
	++nextIt;

	while (nextIt != lst.end())
	{
		if (*it > *nextIt)
			return false;
		++it;
		++nextIt;
	}
	return true;
}

void PmergeMe::processInput(char **av) {

	std::vector<int>	vector;
	std::deque<int>		deque;

	// std::cout << "Before:	"; printContainer(vector);

	std::clock_t vectorStartTime = std::clock();
	getVector(av, vector);
	sortVector(vector, 1);
	std::clock_t vectorEndTime = std::clock();

	if (!isVectorSorted(vector))
		throw std::runtime_error("Error: vector is not sorted correctly.");

	std::clock_t listStartTime = std::clock();
	getDeque(av, deque);
	sortDeque(deque, 1);
	std::clock_t listEndTime = std::clock();

	if (!isDequeSorted(deque))
		throw std::runtime_error("Error: deque is not sorted correctly.");

	std::cout << "After:	"; printContainer(vector);

	double elapsedVector = double(vectorEndTime - vectorStartTime) / CLOCKS_PER_SEC * 1000000;
	double elapsedList = double(listEndTime - listStartTime) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector:	" << elapsedVector << " us" << std::endl;
	std::cout << "Time to process a range of " << deque.size() << " elements with std::list:	" << elapsedList << " us" << std::endl;

}