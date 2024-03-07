#pragma once
#include <random>

class RandomGenerator {
public:
	static RandomGenerator& Get()
	{
		static RandomGenerator instance;
		return instance;
	}

	double NextDouble()
	{
		return dist(rng);
	}

	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator& operator=(const RandomGenerator&) = delete;

private:
	RandomGenerator()
	{
		rng = std::mt19937_64(dev());
		dist = std::uniform_real_distribution<double>(0.0,1.0);
	}

private:
	std::random_device dev;
	std::mt19937_64 rng;
	std::uniform_real_distribution<double> dist;

};