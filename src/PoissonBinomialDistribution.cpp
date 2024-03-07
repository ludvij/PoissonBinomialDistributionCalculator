#include "PoissonBinomialDistribution.hpp"
#include "RandomNumberGenerator.hpp"

#include <math.h>
#include <complex>
#include <iomanip>

constexpr double M_PI = 3.14159265358979323846;

bool PoissonBinomialDistribution::AddExperiment(const int n, const double p) 
{
	if (n <= 0 || p < 0 || p > 1) 
		return false;

	for (int i = 0; i < n; i++) {
		experiments.push_back(p);
	}
	return true;
}

bool PoissonBinomialDistribution::Run()
{
	if (!validate()) return false;
	binomialDist = calculatePMF(k);

	cumulativeL = calcualteCDF(k);
	cumulativeLeq = cumulativeL + binomialDist;
	cumulativeG = 1 - cumulativeLeq;
	cumulativeGeq = 1 - cumulativeL;

	return true;
}

bool PoissonBinomialDistribution::Simulate(const int count)
{
	if (!validate()) return false;

	for (int i = 0; i < count; i++) {
		int successes = 0;
		for (const auto& p : experiments) {
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

	return true;
}

// C = e^(2 * M_PI * i / (n + 1)) 
// C = cos(2 * M_PI / (n + 1)) + i * sin(2 * M_PI / (n + 1))
double PoissonBinomialDistribution::calculatePMF(int k) const
{
	const int n = experiments.size();
	const double inp1 = 1.0/(n+1.0);

	const double realPart = cos(2.0 * M_PI * inp1);
	const double imagPart = sin(2.0 * M_PI * inp1);
	const std::complex<double> C(realPart, imagPart);
	// std::complex<double> C(0, 1);
	// C = exp(2.0 * C * M_PI * inp1);

	std::complex<double> summationRes(0,0);
	// Summation
	for (int l = 0; l <= n; l++)
	{
		std::complex<double> Cpmlk(0,0);
		Cpmlk = pow(C, - l * k);
		
		for (int m = 0; m < n; m++) {
			double pm = experiments[m];
			std::complex<double> Cpl(0,0);
			Cpl = pow(C, l);
			Cpmlk *= (1.0 + (Cpl - 1.0)*pm);
		}
		summationRes += Cpmlk;
	}
	
	return summationRes.real() * inp1;
}

bool PoissonBinomialDistribution::validate() const 
{
	return k >= 0 
		&& experiments.size() > 0 
		&& experiments.size() >= static_cast<size_t>(k);
}

double PoissonBinomialDistribution::calcualteCDF(int k) const
{
	std::complex<double> accumulated(0,0);
	for (int i = 0; i < k; i++) {
		accumulated += calculatePMF(i);
	}

	return accumulated.real();
}

std::ostream& operator<<(std::ostream&os, const PoissonBinomialDistribution& obj)
{
	os << "Poisson Binomial Distibution\n";
	std::ios oldState(nullptr);
	oldState.copyfmt(os);
	os << std::fixed << std::setprecision(4);

	os << "  [Binomial probability:   P(X=" << obj.k << ")] - " << obj.binomialDist << "\n";
	os << "  [Cumulative probability: P(X<" << obj.k << ")] - " << obj.cumulativeL << "\n";
	os << "  [Cumulative probability: P(X≤" << obj.k << ")] - " << obj.cumulativeLeq << "\n";
	os << "  [Cumulative probability: P(X>" << obj.k << ")] - " << obj.cumulativeG << "\n";
	os << "  [Cumulative probability: P(X≥" << obj.k << ")] - " << obj.cumulativeGeq << "\n";

	os.copyfmt(oldState);

	return os;
}