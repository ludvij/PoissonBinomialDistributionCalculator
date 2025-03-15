#ifndef POISSON_BINOMIAL_DISTRIBUTION_HEADER
#define POISSON_BINOMIAL_DISTRIBUTION_HEADER

#include <iostream>
#include <vector>

class PoissonBinomialDistribution
{
public:
	double binomial_dist{};

	double cumulative_l{};
	double cumulative_leq{};
	double cumulative_g{};
	double cumulative_geq{};

public:
	PoissonBinomialDistribution(int k) : m_k(k)
	{
	}
	bool AddExperiment(int n, double p);

	bool Run();

	friend std::ostream& operator <<(std::ostream& os, const PoissonBinomialDistribution& obj);

private:
	double calculate_PMF(int k) const;
	double calculate_CDF(int k) const;

	bool validate() const;

private:
	std::vector<double> m_experiments;

	int m_k;

};

#endif