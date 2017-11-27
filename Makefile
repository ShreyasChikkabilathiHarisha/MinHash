COMPILER         = -g++
# COMPILER        = -clang
OPTIMIZATION_OPT = -O3
# OPTIONS          = -pedantic-errors -ansi -Wall -Wextra -Werror -Wno-long-long $(OPTIMIZATION_OPT) -std=c++11
LINKER_OPT       = -L/usr/lib -lstdc++ -lm

# BUILD_LIST+=basicWorkflow
# all: $(BUILD_LIST) minhash 
# $(BUILD_LIST) : %: %.cpp bloom_filter.hpp
	# $(COMPILER) -std=c++11  -o $@ $@.cpp $(LINKER_OPT)

.PHONY: all
all : minhash.o basicworkflow

basicworkflow: 
	$(COMPILER) $(OPTIONS) -o $@ $@.cpp bloom_filter.hpp minhash.o

minhash.o: 
	$(COMPILER) $(OPTIONS) -c minhash.cpp

containmentminhash.o:
	$(COMPILER) $(OPTIONS) -std=c++ -c containmentminhash.cpp

minhash:
	$(COMPILER) $(OPTIONS) -D_TEST_ $@.cpp -o $@

containmentminhash:
	$(COMPILER) $(OPTIONS) -D_TEST_ $@.cpp -o $@


createVirusesMinHashSketches:
	$(COMPILER) $(OPTIONS) $@.cpp -o $@ -lstdc++fs -lpthread



.PHOHY: clean
clean:
	rm -f minhash containmentminhash basicworkflow core *.o *.bak *stackdump *#


#
# The End !
#