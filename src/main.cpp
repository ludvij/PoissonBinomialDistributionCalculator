#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

#include "PoissonBinomialDistribution.hpp"

#include "ludutils/lud_parse.hpp"


bool createExperiment(PoissonBinomialDistribution& pbd, const std::string_view strN, const std::string_view strP)
{
	auto n = Lud::is_num<int>(strN);
	auto p = Lud::is_num<double>(strP);
	if (!n)
	{
		std::cout << "Tries must be integer number\n";
		return false;
	}
	if (!p)
	{
		std::cout << "Tries must be real number\n";
		return false;
	}

	return pbd.AddExperiment(n.value(), p.value());
}


int main(int argc, char** argv)
{
	// input format validation
	if (argc < 3)
	{
		std::cout << "Usage: " << argv[0] << " Successes, [tries, probability]...\n";
		return 0;
	}
	auto k = Lud::is_num<int>(argv[1]);
	if (!k)
	{
		std::cout << "Successes must be integer number\n";
		return 0;
	}
	else if (( argc - 2 ) % 2 != 0)
	{
		std::cout << "Can not input incomplete experiment\n";
		return 0;
	}
	int experimentsNum = ( argc - 2 ) / 2;
	if (k < 0)
	{
		std::cout << "Tries can not be negative\n";
		return 0;
	}
	PoissonBinomialDistribution pbd(k.value());

	for (int i = 0; i < experimentsNum; i++)
	{
		if (!createExperiment(pbd, argv[2 + i * 2], argv[3 + i * 2]))
		{
			std::cout << "experiment: [" << argv[2 + i * 2] << ", " << argv[3 + i * 2] << "] is invalid\n";
			return 0;
		}
	}


	if (!pbd.Run())
	{
		std::cout << "Incorrect experiment set\n";
		return 0;
	}
	std::cout << pbd << std::endl;


	return 0;
}