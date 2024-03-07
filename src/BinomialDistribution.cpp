#include "BinomialDistribution.hpp"
#include "RandomNumberGenerator.hpp"

#include <iostream>
#include <iomanip>
#include <math.h>




std::ostream& operator<<(std::ostream&os, const BinomialDistribution& be)
{
	os << "Experiment ["<<be.k<<" successes, "<<be.n<<" tries, "<<be.p<<" probability]\n";
	std::ios oldState(nullptr);
	oldState.copyfmt(os);
	os << std::fixed << std::setprecision(3);

	os << "  [Binomial probability:   P(X=" << be.k << ")] - " << be.binomialDist << "\n";
	os << "  [Cumulative probability: P(X<" << be.k << ")] - " << be.cumulativeL << "\n";
	os << "  [Cumulative probability: P(X≤" << be.k << ")] - " << be.cumulativeLeq << "\n";
	os << "  [Cumulative probability: P(X>" << be.k << ")] - " << be.cumulativeG << "\n";
	os << "  [Cumulative probability: P(X≥" << be.k << ")] - " << be.cumulativeGeq << "\n";

	os.copyfmt(oldState);

	return os;
}

void BinomialDistribution::Run()
{
	binomialDist = calculatePMF(k);

	cumulativeL = calculateCDF(k);
	cumulativeLeq = cumulativeL + binomialDist;
	cumulativeG = 1 - cumulativeLeq;
	cumulativeGeq = 1 - cumulativeL;

}

int BinomialDistribution::binomialCoeff(int n, int k) const
{
	double res = 1;
	for (int i = 1; i <= k; i++) {
		res = res * (n - k + i) / i;
	}
	return (int)(res + 0.01);
}

double BinomialDistribution::calculatePMF(int k) const
{
	return binomialCoeff(n, k) * pow(p, k) * pow(1 - p, n - k);
}

double BinomialDistribution::calculateCDF(int k) const
{
	double accumulated = 0;
	for (int i = 0; i < k; i++) {
		accumulated += calculatePMF(i);
	}
	return accumulated;
}



void BinomialDistribution::Simulate(int count)
{
	for (int i = 0; i < count; i++) {
		int successes = 0;
		for (int _ = 0; _ < n; _++) {
			double chance = RandomGenerator::Get().NextDouble();
			if (chance < p) successes++;
		}
		if (successes < k) {
			cumulativeL++;
			cumulativeLeq++;
		} else if (successes == k) {
			binomialDist++;
			cumulativeLeq++;
			cumulativeGeq++;
		} else if (successes > k) {
			cumulativeG++;
			cumulativeGeq++;
		}
	}

	cumulativeL /= count;
	cumulativeLeq /= count;
	cumulativeG /= count;
	cumulativeGeq /= count;

	binomialDist /= count;

}
