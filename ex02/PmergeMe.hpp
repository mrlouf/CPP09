/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:33:45 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/24 15:08:49 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <string>
# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <ctime>
# include <iomanip>
# include <utility>
# include <algorithm>
# include <cmath>

class PmergeMe {
	private:

		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);

		// get the containers
		static void getVector(char **av, std::vector<int> &v);
		static void getDeque(char **av, std::deque<int> &d);

		// checkers for sorted containers
		static bool isVectorSorted(const std::vector<int> &vec);
		static bool isDequeSorted(const std::deque<int> &deq);

		static void printInput(char **av);
		template <typename Container>
		static void printContainer(const Container &container)
		{
			for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << std::endl;
		}

		static int getJacobsthal(int n);

		// utils functions for both vectors and deques
		template <typename T>
		static T next(T it, size_t steps) {
			std::advance(it, steps);
			return it;
		}
		template <typename T>
		static bool comparePairs(T lv, T rv) {
			if (lv == T() || rv == T())
				return false;
			return *lv < *rv;
		}
		template <typename T>
		static void swapPair(T it, int pairSize)
		{
			T start = next(it, -pairSize + 1);
			T end = next(start, pairSize);
			while (start != end)
			{
				std::iter_swap(start, next(start, pairSize));
				start++;
			}
		}

// ---- Vectors ---- //

		template <typename T>
		static void sortVector(std::vector<T> &v, int pairSize) {

			typedef typename std::vector<T>::iterator Iterator;

			int nbrPairs = static_cast<int>(v.size()) / pairSize;
			if (nbrPairs < 2)
				return ;
				
			bool isOdd = nbrPairs % 2 == 1;

			Iterator start = v.begin();
			Iterator last = next(v.begin(), pairSize * nbrPairs);
			Iterator end = next(last, -(isOdd * pairSize));

			// Form pairs of 2, then 4, then 8, etc.
			// until pairSize > v.size() / 2, swap if necessary.
			// Ignore odd elements if any.
			int jump = 2 * pairSize;
			for (Iterator it = start; it != end; std::advance(it, jump))
			{
				Iterator currentPair = next(it, pairSize - 1);
				Iterator nextPair = next(it, pairSize * 2 - 1);
				if (comparePairs(nextPair, currentPair))
					swapPair(currentPair, pairSize);
			}
			
			// recursive call to get all pairs formed and sorted
			sortVector(v, pairSize * 2);
		
			// at this point, we start inserting the pairs into
			// the main and the pend vectors
			std::vector<Iterator> main;
			std::vector<Iterator> pend;

			// insert a1 and b1 into main
			main.insert(main.end(), next(v.begin(), pairSize - 1));
			main.insert(main.end(), next(v.begin(), pairSize * 2 - 1));

			// insert remaining bX into main and aX into pend
			for (int i = 4; i <= nbrPairs; i += 2)
			{
				pend.insert(pend.end(), next(v.begin(), pairSize * (i - 1) - 1));
				main.insert(main.end(), next(v.begin(), pairSize * i - 1));
			}
			if (isOdd)
				pend.insert(pend.end(), next(end, pairSize - 1));
			
			int prevJacobsthal = getJacobsthal(1);
			int insertedNumbers = 0;

			/* This is where Jacobsthal numbers do their magic:
			each element in pend is inserted into main at the position of 
			the Jacobsthal number that corresponds to the difference between
			the current and previous Jacobsthal numbers.
			The offset is used to avoid inserting elements at the end of the main vector.
			The loop breaks when the difference between the current and previous
			Jacobsthal numbers is greater than the size of the pend vector. */
			for (int k = 2;; k++)
			{
				int currJacobsthal = getJacobsthal(k);
				int jacobsthalDiff = currJacobsthal - prevJacobsthal;
				int offset = 0;
				if (jacobsthalDiff > static_cast<int>(pend.size()))
					break;
				int nbrTimes = jacobsthalDiff;
				typename std::vector<Iterator>::iterator pendIt = next(pend.begin(), jacobsthalDiff - 1);
				typename std::vector<Iterator>::iterator boundIt =
					next(main.begin(), currJacobsthal + insertedNumbers);
				if (boundIt > main.end())
					boundIt = main.end();
				while (nbrTimes)
				{
					typename std::vector<Iterator>::iterator idx =
						std::upper_bound(main.begin(), boundIt, *pendIt, comparePairs<Iterator>);
					typename std::vector<Iterator>::iterator inserted = main.insert(idx, *pendIt);
					nbrTimes--;
					pendIt = pend.erase(pendIt);
					std::advance(pendIt, -1);
					offset += (inserted - main.begin()) == currJacobsthal + insertedNumbers;
					boundIt = next(main.begin(), currJacobsthal + insertedNumbers - offset);
				}
				prevJacobsthal = currJacobsthal;
				insertedNumbers += jacobsthalDiff;
				offset = 0;
			}

			for (ssize_t i = pend.size(); i > 0; i--)
			{
				typename std::vector<Iterator>::iterator currPend =
					next(pend.begin(), (i));
				typename std::vector<Iterator>::iterator currBound =
					next(main.begin(), main.size() - pend.size() + i + isOdd);
				
				//	get iterators back in bound to avoid segfaults
				if (currPend < pend.begin())
					currPend = pend.begin();
				else if (currPend >= pend.end())
					currPend = next(pend.end(), -1);
				if (currBound < main.begin())
					currBound = main.begin();
				else if (currBound > main.end())
					currBound = main.end();
				
				// !Careful to keep the iterators in bound!
				typename std::vector<Iterator>::iterator idx =
					std::upper_bound(main.begin(), currBound, *currPend, comparePairs<Iterator>);
								
				main.insert(idx, *currPend);
			}
		
			std::vector<int> copy;
			copy.reserve(v.size());
			for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); it++)
			{
				for (int i = 0; i < pairSize; i++)
				{
					Iterator pairStart = *it;
					std::advance(pairStart, -pairSize + i + 1);
					copy.insert(copy.end(), *pairStart);
				}
			}

			Iterator containerIt = v.begin();
			std::vector<int>::iterator copyIt = copy.begin();
			while (copyIt != copy.end())
			{
				*containerIt = *copyIt;
				containerIt++;
				copyIt++;
			}

		}
	

// ---- Lists ---- //

		template <typename T>
		static void sortDeque(std::deque<T> &d, int pairSize) {
			typedef typename std::deque<T>::iterator Iterator;

			int nbrPairs = static_cast<int>(d.size()) / pairSize;
			if (nbrPairs < 2)
				return ;
				
			bool isOdd = nbrPairs % 2 == 1;

			Iterator start = d.begin();
			Iterator last = next(d.begin(), pairSize * nbrPairs);
			Iterator end = next(last, -(isOdd * pairSize));

			// Form pairs of 2, then 4, then 8, etc.
			// until pairSize > v.size() / 2, swap if necessary.
			// Ignore odd elements if any.
			int jump = 2 * pairSize;
			for (Iterator it = start; it != end; std::advance(it, jump))
			{
				Iterator currentPair = next(it, pairSize - 1);
				Iterator nextPair = next(it, pairSize * 2 - 1);
				if (comparePairs(nextPair, currentPair))
					swapPair(currentPair, pairSize);
			}
			
			// recursive call to get all pairs formed and sorted
			sortDeque(d, pairSize * 2);
		
			// at this point, we start inserting the pairs into
			// the main and the pend deque
			std::deque<Iterator> main;
			std::deque<Iterator> pend;

			// insert a1 and b1 into main
			main.insert(main.end(), next(d.begin(), pairSize - 1));
			main.insert(main.end(), next(d.begin(), pairSize * 2 - 1));

			// insert remaining bX into main and aX into pend
			for (int i = 4; i <= nbrPairs; i += 2)
			{
				pend.insert(pend.end(), next(d.begin(), pairSize * (i - 1) - 1));
				main.insert(main.end(), next(d.begin(), pairSize * i - 1));
			}
			if (isOdd)
				pend.insert(pend.end(), next(end, pairSize - 1));
			
			int prevJacobsthal = getJacobsthal(1);
			int insertedNumbers = 0;

			/* This is where Jacobsthal numbers do their magic:
			each element in pend is inserted into main at the position of 
			the Jacobsthal number that corresponds to the difference between
			the current and previous Jacobsthal numbers.
			The offset is used to avoid inserting elements at the end of the main vector.
			The loop breaks when the difference between the current and previous
			Jacobsthal numbers is greater than the size of the pend vector. */
			for (int k = 2;; k++)
			{
				int currJacobsthal = getJacobsthal(k);
				int jacobsthalDiff = currJacobsthal - prevJacobsthal;
				int offset = 0;
				if (jacobsthalDiff > static_cast<int>(pend.size()))
					break;
				int nbrTimes = jacobsthalDiff;
				typename std::deque<Iterator>::iterator pendIt = next(pend.begin(), jacobsthalDiff - 1);
				typename std::deque<Iterator>::iterator boundIt =
					next(main.begin(), currJacobsthal + insertedNumbers);
				if (boundIt > main.end())
					boundIt = main.end();
				while (nbrTimes)
				{
					typename std::deque<Iterator>::iterator idx =
						std::upper_bound(main.begin(), boundIt, *pendIt, comparePairs<Iterator>);
					typename std::deque<Iterator>::iterator inserted = main.insert(idx, *pendIt);
					nbrTimes--;
					pendIt = pend.erase(pendIt);
					std::advance(pendIt, -1);
					offset += (inserted - main.begin()) == currJacobsthal + insertedNumbers;
					boundIt = next(main.begin(), currJacobsthal + insertedNumbers - offset);
				}
				prevJacobsthal = currJacobsthal;
				insertedNumbers += jacobsthalDiff;
				offset = 0;
			}

			for (ssize_t i = pend.size(); i > 0; i--)
			{
				typename std::deque<Iterator>::iterator currPend =
					next(pend.begin(), (i));
				typename std::deque<Iterator>::iterator currBound =
					next(main.begin(), main.size() - pend.size() + i + isOdd);
				
				//	get iterators back in bound to avoid segfaults
				if (currPend < pend.begin())
					currPend = pend.begin();
				else if (currPend >= pend.end())
					currPend = next(pend.end(), -1);
				if (currBound < main.begin())
					currBound = main.begin();
				else if (currBound > main.end())
					currBound = main.end();
				
				// !Careful to keep the iterators in bound!
				typename std::deque<Iterator>::iterator idx =
					std::upper_bound(main.begin(), currBound, *currPend, comparePairs<Iterator>);
								
				main.insert(idx, *currPend);
			}
		
			std::deque<int> copy;
			// std::deque doesn't have a reserve method
			// as the allocation is done automatically
			for (typename std::deque<Iterator>::iterator it = main.begin(); it != main.end(); it++)
			{
				for (int i = 0; i < pairSize; i++)
				{
					Iterator pairStart = *it;
					std::advance(pairStart, -pairSize + i + 1);
					copy.insert(copy.end(), *pairStart);
				}
			}

			Iterator containerIt = d.begin();
			std::deque<int>::iterator copyIt = copy.begin();
			while (copyIt != copy.end())
			{
				*containerIt = *copyIt;
				containerIt++;
				copyIt++;
			}
		}

		public:
		~PmergeMe();

		static void processInput(char **av);
};

#endif
