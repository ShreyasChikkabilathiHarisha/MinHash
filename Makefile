COMPILER         = -g++
#COMPILER        = -clang
OPTIMIZATION_OPT = -O3
OPTIONS          = -pedantic-errors -ansi -Wall -Wextra -Werror -Wno-long-long $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++ -lm

BUILD_LIST+=basicWorkflow

all: $(BUILD_LIST) minhash 

$(BUILD_LIST) : %: %.cpp bloom_filter.hpp
	$(COMPILER) -std=c++11  -o $@ $@.cpp $(LINKER_OPT)

minhash : 
	$(COMPILER) -std=c++11 -o $@ $@.cpp 

clean:
	rm -f $(BUILD_LIST) minhash core *.o *.bak *stackdump *#

#
# The End !
#