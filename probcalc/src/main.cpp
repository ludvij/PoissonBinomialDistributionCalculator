#include <optional>
#include <string_view>
#include <vector>
#include <print>

#include "PoissonBinomialDistribution.hpp"

#include "ludutils/lud_parse.hpp"


static std::optional<double> parse_probability(const std::string_view str_p)
{
	// double form 0.0...
	auto num_form = Lud::is_num<double>(str_p);
	if (num_form) return num_form;
	// fractional form x/y
	auto frac_form = Lud::is_fraction<double>(str_p);
	if (frac_form) return frac_form;
	// percentage form x%
	auto percent_form = Lud::is_percentage<double>(str_p);
	if (percent_form) return percent_form;
	
	std::println("could not detect probability number format");
	return false;
}


bool createExperiment(PoissonBinomialDistribution& pbd, const std::string_view str_n, const std::string_view str_p)
{
	auto n = Lud::is_num<int>(str_n);
	auto p = parse_probability(str_p);
	if (!n)
	{
		std::println("Tries must be an integer number");
		return false;
	}
	if (!p)
	{
		std::println("probability must be real number");
		return false;
	}

	return pbd.AddExperiment(n.value(), p.value());
}


int main(int argc, char** argv)
{
	// input format validation
	if (argc < 3)
	{
		std::println("Usage: {} Successes, [tries, probability]...", argv[0]);
		return 0;
	}
	auto k = Lud::is_num<int>(argv[1]);
	if (!k)
	{
		std::println("Successes must be integer number");
		return 0;
	}
	else if (( argc - 2 ) % 2 != 0)
	{
		std::println("Can not input incomplete experiment");
		return 0;
	}
	int experimentsNum = ( argc - 2 ) / 2;
	if (k < 0)
	{
		std::println("Tries can not be negative");
		return 0;
	}
	PoissonBinomialDistribution pbd(k.value());

	for (int i = 0; i < experimentsNum; i++)
	{
		if (!createExperiment(pbd, argv[2 + i * 2], argv[3 + i * 2]))
		{
			std::println("experiment: [{}, {}] is invalid", argv[2 + i * 2], argv[3 + i * 2]);
			return 0;
		}
	}


	if (!pbd.Run())
	{
		std::println("Incorrect experiment set");
		return 0;
	}
	std::println("Poisson Binomial Distribution\n{}", pbd);


	return 0;
}