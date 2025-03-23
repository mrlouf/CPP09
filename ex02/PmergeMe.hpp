/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:45 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/23 22:21:13 by nponchon         ###   ########.fr       */
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
		static T next(T it, int steps) {
			std::advance(it, steps);
			return it;
		}
		
		template <typename T>
		static bool comparePairs(T lv, T rv) {
			// PmergeMe::nbr_of_comps++;
			return *lv < *rv;
		}

		template <typename T>
		static void swapPair(T it, int pair_level)
		{
			T start = next(it, -pair_level + 1);
			T end = next(start, pair_level);
			while (start != end)
			{
				std::iter_swap(start, next(start, pair_level));
				start++;
			}
		}

		template <typename T>
		static void sortVector(std::vector<T> &v, int pairSize) {

			typedef typename std::vector<T>::iterator Iterator;

			int nbrPairs = static_cast<int>(v.size()) / pairSize;
			if (nbrPairs < 2)
				return ;
				
			bool isOdd = nbrPairs % 2 == 1;

			Iterator start = v.begin();
			Iterator last = next(v.begin(), pairSize * (nbrPairs));
			Iterator end = next(last, -(isOdd * pairSize));

			int jump = 2 * pairSize;
			for (Iterator it = start; it != end; std::advance(it, jump))
			{
				Iterator currentPair = next(it, pairSize - 1);
				Iterator nextPair = next(it, pairSize * 2 - 1);
				if (comparePairs(nextPair, currentPair))
					swapPair(currentPair, pairSize);

				std::cout << "[";
				for (Iterator itc = currentPair - (pairSize - 1); itc != currentPair + 1; ++itc)
					std::cout << *itc << (itc != currentPair ? ", " : "");
				std::cout << "][";
				for (Iterator itn = nextPair - (pairSize - 1); itn != nextPair + 1; ++itn)
					std::cout << *itn << (itn != nextPair ? ", " : "");
				std::cout << "]";

			}
			std::cout << std::endl;
			sortVector(v, pairSize * 2);
		
		}
	

// ---- Lists ---- //

		template <typename T>
		static void sortList(std::list<T> &l) {
			(void)l;
			return ;
		}

		public:
		~PmergeMe();

		static void processInput(char **av);
};

#endif
