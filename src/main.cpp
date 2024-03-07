#include <iostream>
#include <vector>
#include <sstream>

#include "PoissonBinomialDistribution.hpp"


bool isInt(const std::string& str)
{
	std::stringstream iss(str);
	int f;
	iss >> f;
	return iss.eof() && !iss.fail();
}

bool isFloat(const std::string& str)
{
	std::stringstream iss(str);
	float f;
	iss >> f;
	return iss.eof() && !iss.fail();
}

bool createExperiment(PoissonBinomialDistribution& pbd, const std::string& strN, const std::string& strP)
{
	if (!isInt(strN)) {
		std::cout << "Tries must be integer number\n";
		return false;
	} else if (!isFloat(strP)) {
		std::cout << "Tries must be real number\n";
		return false;
	}

	int n = std::stoi(strN);
	double p = std::stod(strP);

	return pbd.AddExperiment(n, p);

}


int main(int argc, char** argv)
{
	// input format validation
	if (argc < 5) {
		std::cout << "Usage: [c|s]," << argv[0] << " Succeses, [tries, probability]...\n";
		return 0;
	}
	std::string config(argv[1]);
	if (config != "c" && config != "s") {
		std::cout << "Invalid configuration\n";
		return 0;
	} else if (!isInt(argv[2])) {
		std::cout << "Successes must be integer number\n";
		return 0;
	} else if ((argc - 3) % 2 != 0) {
		std::cout << "Can not input incomplete experiment\n";
		return 0;
	}
	int k = std::stoi(argv[2]);
	int experimentsNum = (argc - 3) / 2;
	if (k < 0) {
		std::cout << "Tries can not be negative\n";
		return 0;
	}
	PoissonBinomialDistribution pbd(k);

	for (int i = 0; i < experimentsNum; i++) {
		if (!createExperiment(pbd, argv[3 + i*2], argv[4 + i*2])) {
			std::cout << "experiment: [" << argv[3 + i*2] << ", " << argv[4 + i*2] << "] is invalid\n";
			return 0;
		}
	} 

	
	if (config == "c") {
		if (!pbd.Run()) {
			std::cout << "Incorrect experiment set\n";
			return 0;
		}
	} else if (config == "s") {
		if (!pbd.Simulate()) {
			std::cout << "Incorrect experiment set\n";
			return 0;
		}
	}

	std::cout << pbd << std::endl;


	return 0;
}