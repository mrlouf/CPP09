/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:49:47 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/19 19:30:16 by nponchon         ###   ########.fr       */
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
		unsigned int key = static_cast<unsigned int>(atol(keyStr.c_str()));
		std::string valueStr = line.substr(line.find(',') + 1);
		float value = static_cast<float>(std::atof(valueStr.c_str()));
		data.insert(std::pair<unsigned int, float>(key, value));
	}

	dataset.close();
	
	return data;
}

/*
	This function checks for a valid date format YYYY-MM-DD.
	It excludes basic wrong formats such as months over 12, or days over 31.
	Technically, it allows wrong formats like XXXX-02-31, but the scope of the program
	is not to parse a calender. I do not want to go down the rabbit hole of 
	accounting for leap years and all the likes.
*/
bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
		if (i == 5 && date[i] > '1') // invalid month format
			return false;
		if (i == 6 && date[i - 1] == '1' && date[i] > '2') // invalid month format
			return false;
		if (i == 8 && date[i] > '3') // invalid day format
			return false;
		if (i == 9 && date[i - 1] == '3' && date[i] > '1') // invalid day format
			return false;
	}
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
		size_t delimiterPos = line.find('|');
		if (delimiterPos == std::string::npos)
		{
			std::cout << "Error: Bad input => \'" << line << "\'" << std::endl;
			continue;
		}

		std::string dateStr = line.substr(0, delimiterPos - 1);  // trim spaces
		std::string valueStr = line.substr(delimiterPos + 2); // trim spaces

		if (!isValidDate(dateStr))
		{
			std::cout << "Error: Bad input => " << line << std::endl;
			continue;
		}

		// convert date from string to unsigned int
		dateStr.erase(std::remove(dateStr.begin(), dateStr.end(), '-'), dateStr.end());
		unsigned int dateUint = static_cast<unsigned int>(atol(dateStr.c_str()));

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
				float exchangeRate = it->second;
				float value = std::strtof(valueStr.c_str(), NULL);
				std::cout << dateStr << " => " << value << " = " << value * exchangeRate << std::endl;
			}
			break;

		case BAD_INPUT:
			std::cout << "Error: Bad input => " << line << std::endl;
			break;

		case VALUE_UNDERFLOW:
			std::cout << "Error: Value too low => " << valueStr << std::endl;
			break;
			
		case VALUE_OVERFLOW:
			std::cout << "Error: Value too high => " << valueStr << std::endl;
			break;
		}
	}
}