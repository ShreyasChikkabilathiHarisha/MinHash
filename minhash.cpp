#include "minhash.hpp"

using namespace std;

template <typename T>
CountEstimator<T>::CountEstimator(T& object, std::list<long> hash_list, int n, long max_prime, int ksize, std::string input_file_name, char save_kmers, bool rev_comp)
{
	if(n == 0)
	{
		cout<<"n=0 exception\n";
		exit(0);
	}
	if(ksize == 0)
	{
		cout<<"ksize=0 exception\n";
		exit(0);
	}
	if((ksize % 2) == 0)
	{
		cout<<"Due to an issue with khmer, only odd ksizes are allowed\n";
		exit(0);
	}
	this->ksize = ksize;
	this->hash_list = hash_list;
	// get a prime to use for hashing
	long p = get_prime_lt_x(max_prime);
	this->p = p;
	// initialize sketch to size n
	this->_mins.assign(n,p);
	// initialize the corresponding counts
	this->_counts.assign(n,0);
	// initialize the list of kmers used, if appropriate
	if(save_kmers == 'y')
	{
		this->_kmers.assign(n,"");
	}
	else
	{
		this->_kmers.clear();
	}
	// Initialize file name (if appropriate)
	this->_input_file_name = input_file_name;
	if(this->_input_file_name != NULL)
	{
		this->parse_file(rev_comp=rev_comp);
	}
	// Optional container for the true number of k-mers in the genome used to populate the sketch
	this->_true_num_kmers = 0;

}

template <typename T>
void CountEstimator<T>::parse_file(bool rev_comp)
{
	/* opens a file and populates the CountEstimator with it */

}

template <typename T>
void CountEstimator<T>::down_sample(long h)
{
	/* This will down-sample a sketch to have exactly h elements
        :param h: number of elements you wish to save
        :return: None */
	std::list<long> temp1 ;
	std::list<long> temp2 ;
	std::list<long> temp3 ;
	std::list<long>::iterator it1 =this->_mins.begin();
	std::list<long>::iterator it2 =this->_counts.begin();
	std::list<long>::iterator it3 =this->_kmers.begin();
	for(int i=0; i<h; i++)
	{
		temp1.push_back(*it1);
		it1++;
		temp2.push_back(*it2);
		it2++;
		temp3.push_back(*it3);
		it3++;
	}
	this->_mins = temp1;
	this->_counts = temp2;
	this->_kmers = temp3;
}

template <typename T>
void CountEstimator<T>::add()
{

}

template <typename T>
void CountEstimator<T>::add_sequence()
{

}

template <typename T>
void CountEstimator<T>::jaccard_count()
{

}

template <typename T>
void CountEstimator<T>::common_count()
{

}

template <typename T>
void CountEstimator<T>::common()
{

}

template <typename T>
void CountEstimator<T>::_truncate()
{

}

template <typename T>
void CountEstimator<T>::_export()
{

}

template <typename T>
void CountEstimator<T>::count_vector()
{

}

template <typename T>
void CountEstimator<T>::jaccard_vector()
{

}

bool is_prime(int number)
{
	if(number < 2)
	{
		return false;
	}
	if(number == 2)
	{
		return true;
	}
	if((number % 2) == 0)
	{
		return false;
	}
	for(int i =3; i<(int(pow(number,0.5))+1); i+=2)
	{
		if((number%i) == 0)
		{
			return false;
		}
	}
	return true;
}

long get_prime_lt_x(long target)
{
	if(target == 1)
	{
		return 1;
	}
	int i = int(target);
	if( (i%2) == 0 )
	{
		i -= 1;
	}
	while(i > 0)
	{
		if(is_prime(i))
		{
			return i;
		}
		i -=2;
	}
	if(i <= 0)
	{
		cout<<"unable to find a prime number < "<< target <<endl;
		exit(0);
	}
}

int main()
{
    cout<<"success\n";

    return 0;
}
