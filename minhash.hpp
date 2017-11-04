#include <iostream>
#include <string>
#include <list>

template <typename T >
class CountEstimator
{
private:
	int n;
	double _max_prime = 9999999999971.;
	int _ksize = 0;
	std::string _input_file_name = NULL;
	char _save_kmers = 'n';
	std::list<long> _hash_list ;
	bool _rev_comp=false;

public:
	CountEstimator(T& object, int n, double max_prime, int ksize, std::string input_file_name, char save_kmers, std::list<long> hash_list, bool rev_comp);
	void parse_file();
	void down_sample();
	void add();
	void add_sequence();
	void jaccard_count();
	void jaccard();
	void common_count();
	void common();
	void _truncate();
	void _export();
	void count_vector();
	void jaccard_vector();

};

int main();
