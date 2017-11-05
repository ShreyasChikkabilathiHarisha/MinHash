COMPILER         = -g++
#COMPILER        = -clang
OPTIMIZATION_OPT = -O3
OPTIONS          = -pedantic-errors -ansi -Wall -Wextra -Werror -Wno-long-long $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++ -lm

BUILD_LIST+=basicWorkflow

all: $(BUILD_LIST)

$(BUILD_LIST) : %: %.cpp bloom_filter.hpp
	$(COMPILER) $(OPTIONS) -o $@ $@.cpp $(LINKER_OPT)

clean:
	rm -f $(BUILD_LIST) core *.o *.bak *stackdump *#

#
# The End !
#