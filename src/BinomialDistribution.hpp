#pragma once

#include <iostream>


class BinomialDistribution {

public:
	double binomialDist;

	double cumulativeL;	
	double cumulativeLeq;	
	double cumulativeG;	
	double cumulativeGeq;	

	int n;		// tries
	int k;		// successses
	double p;	// probability

public:
	BinomialDistribution(int k, int n, double p) : n(n), k(k), p(p) {}
	
	void Run();
	void Simulate(int count = 10e6);

	friend std::ostream& operator<<(std::ostream&os, const BinomialDistribution& be);

private:
	double calculatePMF(int k) const;
	double calculateCDF(int k) const;

	int binomialCoeff(int n, int k) const;	


};