#include "PoissonBinomialDistribution.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <iomanip>


bool PoissonBinomialDistribution::AddExperiment(const int n, const double p)
{
	if (n <= 0 || p < 0 || p > 1)
		return false;

	for (int i = 0; i < n; i++)
	{
		m_experiments.push_back(p);
	}
	return true;
}

bool PoissonBinomialDistribution::Run()
{
	if (!validate()) return false;
	binomial_dist = calculate_PMF(m_k);

	cumulative_l = calculate_CDF(m_k);
	cumulative_leq = cumulative_l + binomial_dist;
	cumulative_g = 1 - cumulative_leq;
	cumulative_geq = 1 - cumulative_l;

	return true;
}


// C = e^(2 * M_PI * i / (n + 1)) 
// C = cos(2 * M_PI / (n + 1)) + i * sin(2 * M_PI / (n + 1))
double PoissonBinomialDistribution::calculate_PMF(int k) const
{
	const int n = (int)m_experiments.size();
	const double inp1 = 1.0 / ( n + 1.0 );

	const double real_part = cos(2.0 * M_PI * inp1);
	const double imag_part = sin(2.0 * M_PI * inp1);
	const std::complex<double> C(real_part, imag_part);
	// std::complex<double> C(0, 1);
	// C = exp(2.0 * C * M_PI * inp1);

	std::complex<double> summation_res(0, 0);
	// Summation
	for (int l = 0; l <= n; l++)
	{
		std::complex<double> Cpmlk(0, 0);
		Cpmlk = pow(C, -l * k);

		for (int m = 0; m < n; m++)
		{
			double pm = m_experiments[m];
			std::complex<double> Cpl(0, 0);
			Cpl = pow(C, l);
			Cpmlk *= ( 1.0 + ( Cpl - 1.0 ) * pm );
		}
		summation_res += Cpmlk;
	}

	return summation_res.real() * inp1;
}

bool PoissonBinomialDistribution::validate() const
{
	return m_k >= 0
		&& m_experiments.size() > 0
		&& m_experiments.size() >= static_cast<size_t>( m_k );
}

double PoissonBinomialDistribution::calculate_CDF(int k) const
{
	std::complex<double> accumulated(0, 0);
	for (int i = 0; i < k; i++)
	{
		accumulated += calculate_PMF(i);
	}

	return accumulated.real();
}

std::ostream& operator<<(std::ostream& os, const PoissonBinomialDistribution& obj)
{
	os << "Poisson Binomial Distribution\n";
	std::ios old_state(nullptr);
	old_state.copyfmt(os);
	os << std::fixed << std::setprecision(4);

	os << "  [Binomial probability:   P(X=" << obj.m_k << ")] - " << obj.binomial_dist << "\n";
	os << "  [Cumulative probability: P(X<" << obj.m_k << ")] - " << obj.cumulative_l << "\n";
	os << "  [Cumulative probability: P(X≤" << obj.m_k << ")] - " << obj.cumulative_leq << "\n";
	os << "  [Cumulative probability: P(X>" << obj.m_k << ")] - " << obj.cumulative_g << "\n";
	os << "  [Cumulative probability: P(X≥" << obj.m_k << ")] - " << obj.cumulative_geq << "\n";

	os.copyfmt(old_state);

	return os;
}