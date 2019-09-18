#pragma once
#include "ssconfig.hpp"
#include "stadfx.h"
template<typename T>
bool writeDebug(std::ofstream &deg, string const &str, vector<T> const &v_val) {
	deg << str;
	for (auto & it : v_val)
	{
		deg << " " << it;
	}
	deg << endl;
	return false;
};

template<typename T>
bool writeDebug(std::ofstream &deg, string const &str, T const &v_val)
{
	deg << str;
	deg << " " << v_val << endl;
	return false;
}
/*

*/
template<typename T>
std::ostream& operator<<(std::ostream &out, vector<T> &obj)
{
	for (size_t i = 0; i < obj.size(); i++)
	{
		out << " " << obj[i];
	}
	return out;
}