# PoissonBinomialDistributionCalculator
A probability calculator
## Usage
probabilityCalculator c|s successes [tries probability,]

multiple experiments can be chained, an experiment is a set of tries and probabilities, i.e  
probabilityCalculator c 1 13 .5 5 .32  
This will calculate the probability to get 1 success of 13 tries with 50% and 4 tries with 32%

**modes**:
- In **c** mode it calculates the result using _math_
- In **s** mode it simulates the result
