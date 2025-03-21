/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:45 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 19:21:57 by nponchon         ###   ########.fr       */
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
		static void printContainer(std::vector<int> &v);

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
	
		static void sortList(std::list<int> &l);

		public:
		~PmergeMe();

		static void processInput(char **av);
};

#endif
