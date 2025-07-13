#ifndef POISSON_BINOMIAL_DISTRIBUTION_HEADER
#define POISSON_BINOMIAL_DISTRIBUTION_HEADER

#include <vector>
#include <format>

class PoissonBinomialDistribution
{
public:
	int k;

	double binomial_dist{};

	double cumulative_l{};
	double cumulative_leq{};
	double cumulative_g{};
	double cumulative_geq{};

public:
	PoissonBinomialDistribution(int k) : k(k)
	{
	}
	bool AddExperiment(int n, double p);

	bool Run();

private:
	double calculate_PMF(int k) const;
	double calculate_CDF(int k) const;

	bool validate() const;

private:
std::vector<double> m_experiments;


};


template<>
struct std::formatter<PoissonBinomialDistribution> 
{
 	constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

	auto format(const PoissonBinomialDistribution& obj, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), ""
		"  [Binomial probability:   P(X={0:})] - {1:.6f} ({2:>6.2f}%)\n"
		"  [Cumulative probability: P(X<{0:})] - {3:.6f} ({4:>6.2f}%)\n"
		"  [Cumulative probability: P(X≤{0:})] - {5:.6f} ({6:>6.2f}%)\n"
		"  [Cumulative probability: P(X>{0:})] - {7:.6f} ({8:>6.2f}%)\n"
		"  [Cumulative probability: P(X≥{0:})] - {9:.6f} ({10:>6.2f}%)",
		obj.k,
		obj.binomial_dist,	
		obj.binomial_dist * 100,
		obj.cumulative_l,	
		obj.cumulative_l * 100,
		obj.cumulative_leq,	
		obj.cumulative_leq * 100,
		obj.cumulative_g,	
		obj.cumulative_g * 100,
		obj.cumulative_geq,	
		obj.cumulative_geq * 100
		);
	}
};

#endif