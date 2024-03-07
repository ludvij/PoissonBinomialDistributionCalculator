CC := g++
FLAGS := -Werror -Wall -Wextra -std=c++20 -O3

OUT = ProbabilityCalculator.exe

ODIR = obj
SDIR = src


all: $(OUT)


$(OUT): $(ODIR)/main.o $(ODIR)/PoissonBinomialDistribution.o #obj/BinomialDistribution.o
	$(CC) -o $(OUT) $(FLAGS) $^



$(ODIR)/main.o: $(SDIR)/main.cpp
	$(CC) -o $@ -c $(FLAGS) $<

# obj/BinomialDistribution.o: src/BinomialDistribution.cpp src/BinomialDistribution.hpp
# 	$(CC) -o $@ -c $(FLAGS) $<

$(ODIR)/PoissonBinomialDistribution.o: $(SDIR)/PoissonBinomialDistribution.cpp $(SDIR)/PoissonBinomialDistribution.hpp
	$(CC) -o $@ -c $(FLAGS) $<


.phony: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)