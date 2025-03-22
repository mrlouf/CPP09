/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:49:47 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/21 14:32:02 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<unsigned int, float> BitcoinExchange::_data;

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	(void)other;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	(void)other;
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}


void	BitcoinExchange::isInputEmpty(std::ifstream &input)
{
	if (input.peek() == std::ifstream::traits_type::eof())
	{
		input.close();
		throw std::runtime_error("Input file is empty");
	}
	return ;
}

std::map<unsigned int, float> &BitcoinExchange::loadDataSet() {

	static std::map<unsigned int, float> data;

	std::ifstream dataset("data.csv", std::ios::in);
	if (!dataset.is_open())
		throw std::runtime_error("Error opening data.csv");

	std::string line;

	std::getline(dataset, line); // skip first line in .csv

	while (std::getline(dataset, line))
	{
		std::string keyStr = line.substr(0, line.find(','));
		keyStr.erase(std::remove(keyStr.begin(), keyStr.end(), '-'), keyStr.end());
		unsigned int key = static_cast<unsigned int>(std::atol(keyStr.c_str()));

		std::string valueStr = line.substr(line.find(',') + 1);
		float value = static_cast<float>(std::atof(valueStr.c_str()));

		data.insert(std::pair<unsigned int, float>(key, value));
	}

	dataset.close();
	
	return data;
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::stringstream y, m, d;
	y << date.substr(0, 4);
	m << date.substr(5, 2);
	d << date.substr(8, 2);

	unsigned int year, month, day;
	y >> year; m >> month; d >> day; 

	if (year < 2009 || year > 2025 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// check for leap years
	if (month == 2 && day > 28) {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
			return day == 29;
		return false;
	}

	// check for months with 30 days
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	return true;
}

ValidResult BitcoinExchange::validateValue(const std::string &valueStr)
{
	char *end;
	float value = std::strtof(valueStr.c_str(), &end);

	if (*end != '\0')
		return BAD_INPUT;

	if (value < 0)
		return VALUE_UNDERFLOW;
	else if (value > 1000)
		return VALUE_OVERFLOW;

	return VALID;
}

void	BitcoinExchange::processInput(std::ifstream &input)
{
	isInputEmpty(input);
	_data = loadDataSet();

	// std::map<unsigned int, float>::const_iterator it;
	// for (it = _data.begin(); it != _data.end(); ++it) {
	// 	std::cout << "key: " << it->first << " value: " << it->second << std::endl;
	// }
	// std::string line;
	// while (std::getline(input, line))
	// {
	// 	std::cout << line << std::endl;
	// }

	std::string line;
	while (std::getline(input, line))
	{
		if (line == "date | value") {
			std::cout << line << std::endl;
			continue;
		}

		size_t delimiterPos = line.find('|');
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Error: Bad input => \'" << line << "\'" << std::endl;
			continue;
		}

		std::string dateStr = line.substr(0, delimiterPos - 1);  // trim spaces
		std::string valueStr = line.substr(delimiterPos + 2); // trim spaces

		if (!isValidDate(dateStr))
		{
			std::cerr << "Error: Bad input => " << line << std::endl;
			continue;
		}

		// convert date from string to unsigned int
		std::string dateStrCpy = dateStr;
		dateStrCpy.erase(std::remove(dateStrCpy.begin(), dateStrCpy.end(), '-'), dateStrCpy.end());
		unsigned int dateUint = static_cast<unsigned int>(atol(dateStrCpy.c_str()));

		ValidResult result = validateValue(valueStr);
		
		std::map<unsigned int, float>::const_iterator it; // initialise iterator outside of switch scope
		
		switch (result)
		{
		case VALID:
			
			it = _data.lower_bound(dateUint);

			if (it != _data.end() && it->first == dateUint)	// if exact date found
			{
				float exchangeRate = it->second;
				float value = std::strtof(valueStr.c_str(), NULL);
				std::cout << dateStr << " => " << value << " = " << value * exchangeRate << std::endl;
			}
			else
			{
				if (it != _data.begin())	// if not found, use the previous date
					--it;
				else {
					std::cerr << "Error: Bad input => " << line << std::endl;
					continue;
				}
				float exchangeRate = it->second;
				float value = std::strtof(valueStr.c_str(), NULL);
				std::cout << dateStr << " => " << value << " = " << value * exchangeRate << std::endl;
			}
			break;

		case BAD_INPUT:
			std::cerr << "Error: Bad input => " << line << std::endl;
			break;

		case VALUE_UNDERFLOW:
			std::cerr << "Error: Value too low => " << valueStr << std::endl;
			break;
			
		case VALUE_OVERFLOW:
			std::cerr << "Error: Value too high => " << valueStr << std::endl;
			break;
		}
	}
}