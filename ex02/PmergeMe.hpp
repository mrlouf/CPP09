/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:45 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 19:45:49 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <string>
# include <iostream>
# include <vector>
# include <list>
# include <sstream>
# include <ctime>
# include <iomanip>
# include <utility>
# include <algorithm>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);

		static void getContainers(char **av, std::vector<int> &v, std::list<int> &l);
		
		template <typename Container>
		static void printContainer(const Container &container)
		{
			for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << std::endl;
		}

// ---- Vectors ---- //

		template <typename T>
		static std::vector<std::pair<T, T> > createAndSortVectorPairs(const std::vector<T> &elements) {
			std::vector<std::pair<T, T> > pairs;
		
			for (size_t i = 0; i < elements.size(); i += 2) {
				if (i + 1 < elements.size()) {
					std::pair<T, T> p = std::make_pair(elements[i], elements[i + 1]);
					if (p.first > p.second)
						std::swap(p.first, p.second);
					pairs.push_back(p);
				}
			}
			return pairs;
		}

		template <typename T>
		static std::vector<int> recursiveVectorMerge(std::vector<T> &elements) {
			if (elements.size() == 1) {
				std::vector<int> result;
				flatten(elements[0], result);
				return result;
			}
	
			std::vector<std::pair<T, T> > pairs = createAndSortVectorPairs(elements);
		
			std::vector<T> nextLevelElements;
			for (size_t i = 0; i < pairs.size(); ++i)
				nextLevelElements.push_back(pairs[i].second);

			T oddElement;
			bool hasOddElement = (elements.size() % 2 != 0);
			if (hasOddElement)
				oddElement = elements.back();

			std::vector<int> mergedResult = recursiveVectorMerge(nextLevelElements);

			for (size_t i = 0; i < pairs.size(); ++i)
				mergedResult.push_back(pairs[i].first);

			if (hasOddElement)
				mergedResult.push_back(oddElement);

			std::sort(mergedResult.begin(), mergedResult.end());
		
			return mergedResult;
		}

		template <typename T>
		static void flatten(const T &element, std::vector<int> &result) {
			result.push_back(element);
		}
		
		static void flatten(const std::pair<int, int> &element, std::vector<int> &result);
		static void flatten(const std::pair<std::pair<int, int>, std::pair<int, int> > &element, std::vector<int> &result);

// ---- Lists ---- //

		template <typename T>
		static std::list<std::pair<T, T> > createAndSortListPairs(const std::list<T> &elements) {
			std::list<std::pair<T, T> > pairs;
		
			typename std::list<T>::const_iterator it = elements.begin();
			while (it != elements.end()) {
				T first = *it;
				++it;
		
				if (it != elements.end()) {
					T second = *it;
					++it;
		
					// Create a pair and sort it
					if (first > second) {
						std::swap(first, second);
					}
					pairs.push_back(std::make_pair(first, second));
				}
			}
		
			return pairs;
		}

		template <typename T>
		static std::list<int> recursiveListMerge(std::list<T> &elements) {
			// Base case: If there's only one element, flatten it and return
			if (elements.size() == 1) {
				std::list<int> result;
				flatten(elements.front(), result);
				return result;
			}
		
			// Step 1: Create and sort pairs
			std::list<std::pair<T, T> > pairs = createAndSortListPairs(elements);
		
			// Step 2: Extract the larger elements from each pair for the next level
			std::list<T> nextLevelElements;
			for (typename std::list<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
				nextLevelElements.push_back(it->second); // Use the larger element
			}
		
			// Handle the odd element (if any)
			T oddElement;
			bool hasOddElement = (elements.size() % 2 != 0);
			if (hasOddElement) {
				oddElement = elements.back();
			}
		
			// Step 3: Recursively merge the next level
			std::list<int> mergedResult = recursiveListMerge(nextLevelElements);
		
			// Step 4: Merge the smaller elements into the result
			for (typename std::list<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
				mergedResult.push_back(it->first); // Add the smaller element
			}
		
			// Add the odd element back to the result
			if (hasOddElement) {
				mergedResult.push_back(oddElement);
			}
		
			// Step 5: Sort the final result
			mergedResult.sort();
		
			return mergedResult;
		}

		template <typename T>
		static void flatten(const T &element, std::list<int> &result) {
			result.push_back(element);
		}
		
		static void flatten(const std::pair<int, int> &element, std::list<int> &result);
		
		static void flatten(const std::pair<std::pair<int, int>, std::pair<int, int> > &element, std::list<int> &result);

		public:
		~PmergeMe();

		static void processInput(char **av);
};

#endif
