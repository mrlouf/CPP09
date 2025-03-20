/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:49:43 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/20 16:00:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <stdexcept>
# include <string>
# include <map>
# include <fstream>
# include <cstdlib>
# include <algorithm>
# include <ctime>

enum ValidResult {
	VALID,
	BAD_INPUT,
	VALUE_UNDERFLOW,
	VALUE_OVERFLOW
};

class BitcoinExchange {
	private:
		static std::map<unsigned int, float> _data;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		static ValidResult validateValue(const std::string &valueStr);
		static void isInputEmpty(std::ifstream &input);
		static std::map<unsigned int, float>	&loadDataSet();
		static bool isValidDate(const std::string &date);

	public:
		static void processInput(std::ifstream &input);
};

#endif
