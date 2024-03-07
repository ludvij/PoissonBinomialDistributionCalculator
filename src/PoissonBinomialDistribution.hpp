#pragma once

#include <vector>
#include <iostream>

class PoissonBinomialDistribution {
public:
	double binomialDist;

	double cumulativeL;
	double cumulativeLeq;
	double cumulativeG;
	double cumulativeGeq;

public:
	PoissonBinomialDistribution(int k) : k(k) {}
	bool AddExperiment(int n, double p);

	bool Run();
	bool Simulate(int count=10e6);

	friend std::ostream& operator <<(std::ostream& os, const PoissonBinomialDistribution& obj);

private:
	double calculatePMF(int k) const;
	double calcualteCDF(int k) const;

	bool validate() const;

private:
	std::vector<double> experiments;

	int k;

};