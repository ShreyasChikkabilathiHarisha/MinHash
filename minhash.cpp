#include "minhash.hpp"

using namespace std;

CountEstimator::CountEstimator()
{
	cout<<"CountEstimator::CountEstimator - Default"<<endl;
}

CountEstimator::CountEstimator(std::list<long> hash_list, int n, long max_prime, int ksize, std::string input_file_name, char save_kmers, bool rev_comp)
{
	cout<<"CountEstimator::CountEstimator - Begin"<<endl;
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
	this->input_file_name = input_file_name;
	if(this->input_file_name != "\0")
	{
		this->parse_file(rev_comp=rev_comp);
	}
	// Optional container for the true number of k-mers in the genome used to populate the sketch
	this->_true_num_kmers = 0;
	cout<<"CountEstimator::CountEstimator - end"<<endl;
}

//template <typename T>
void CountEstimator::parse_file(bool rev_comp)
{
	/* opens a file and populates the CountEstimator with it */

}

//template <typename T>
void CountEstimator::down_sample(long h)
{
	/* This will down-sample a sketch to have exactly h elements
        :param h: number of elements you wish to save
        :return: None */
	std::list<long> temp1 ;
	std::list<long> temp2 ;
	std::list<string> temp3 ;
	std::list<long>::iterator it1 =this->_mins.begin();
	std::list<long>::iterator it2 =this->_counts.begin();
	std::list<std::string>::iterator it3 =this->_kmers.begin();
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

void CountEstimator::add(std::string kmer, bool rev_comp)
{
	cout<<"CountEstimator::add - begin"<<endl;
	/* Add kmer into sketch, keeping sketch sorted, update counts accordingly */
	_mins = this->_mins;
	_counts = this->_counts;
	_kmers = this->_kmers;
	uint64_t h;
	if(rev_comp)
	{
		uint64_t h1 = MurmurHash64A(&kmer,ksize,ksize); // Have to check the 2nd and 3rd arguments of murmurHash function call
		uint64_t h2 = MurmurHash64A(&kmer,ksize,ksize); // have to implement "h2 = khmer.hash_murmur3(khmer.reverse_complement(kmer))"
		h=(h1<h2)?h1:h2;
		if(h == h2)
		{
			// kmer = khmer.reverse_complement(kmer)
		}
	}
	else
	{
		h = MurmurHash64A(&kmer,ksize,ksize);
	}
	h = h % this->p;
	if(!this->hash_list.empty())
	{
		bool flag = false;
		for(std::list<long>::iterator it =this->hash_list.begin(); it!=this->hash_list.end(); it++)
		{
			if(h==*it)
			{
				flag = true;
				break;
			}
		}
		if(flag==false)
		{
			return;
		}
	}
	if(h>=*(_mins.end()))
	{
		return;
	}
	// bisect function
	long i=0;
	bool foundIndex = false;
	for(std::list<long>::iterator it =this->_mins.begin(); it!=this->_mins.end(); it++)
	{
			if(h==*it)
			{
				foundIndex = true;
				break;
			}
			i++;
	}
	std::list<long>::iterator it4 =this->_mins.begin();
	std::list<long>::iterator it5 =this->_counts.begin();
	std::list<std::string>::iterator it6 =this->_kmers.begin();
	if(foundIndex == true)
	{
		for(long q=0; q<i;q++)
		{
			it4++;
			it5++;
			it6++;
		}
		(*it4) +=1;
		return;
	}
	else    // otherwise insert h, initialize counts to 1, and insert kmer if necessary
	{
		_mins.insert(it4, h);
		_mins.pop_back();
		_counts.insert(it5, 1);
		_counts.pop_back();
		if(!_kmers.empty())
		{
			_kmers.insert(it6,kmer);
			_kmers.pop_back();
		}
		return;
	}
	cout<<"CountEstimator::add - end"<<endl;
}

//template <typename T>
void CountEstimator::add_sequence(std::string seq, bool rev_comp)
{
	cout<<"CountEstimator::add_sequence - Begin"<<endl;
	/* Sanitize and add a sequence to the sketch. */
	std::transform(seq.begin(), seq.end(), seq.begin(), std::ptr_fun<int, int>(std::toupper));
	for (std::string::size_type l = 0; l < seq.length(); ++l)
    {
        if(seq[l] != 'A' && seq[l] != 'C' && seq[l] != 'T' && seq[l] != 'G')
        {
            seq[l] = 'G';
        }
    }
	string temp = "                              ";
	int i=0;
	while(seq[i+this->ksize-1]!='\0')
	{
		for(int j=i;j<(i+this->ksize);j++)
		{
			temp[j-i] = seq[j];
		}
		add(temp,rev_comp);
		i++;
	}
//	for(std::list<string>::iterator it =this->_kmers.begin(); it!=this->_kmers.end(); it++)
//        {
//		cout<<*it<<endl;
//	}
	cout<<"CountEstimator::add_sequence - end"<<endl;
}

//template <typename T>
void CountEstimator::jaccard_count()
{

}

//template <typename T>
void CountEstimator::common_count()
{

}

//template <typename T>
void CountEstimator::common()
{

}

//template <typename T>
void CountEstimator::_truncate()
{

}

//template <typename T>
void CountEstimator::_export()
{

}

//template <typename T>
void CountEstimator::count_vector()
{

}

//template <typename T>
void CountEstimator::jaccard_vector()
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
	for(int j =3; j<(int(pow(number,0.5))+1); j+=2)
	{
		if((number%j) == 0)
		{
			return false;
		}
	}
	return true;
}

long get_prime_lt_x(long t)
{
	if(t == 1)
	{
		return 1;
	}
	int i = int(t);
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
		cout<<"unable to find a prime number < "<< t <<endl;
		exit(0);
	}
}

//typedef unsigned __int64 uint64_t;

// 64-bit hash for 64-bit platforms
uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed )
{
	const uint64_t m = 0xc6a4a7935bd1e995;
	const int r = 47;
	uint64_t h = seed ^ (len * m);
	const uint64_t * data = (const uint64_t *)key;
	const uint64_t * end = data + (len/8);
	while(data != end)
	{
		uint64_t k = *data++;
		k *= m; 
		k ^= k >> r; 
		k *= m;
		h ^= k;
		h *= m; 
	}
	const unsigned char * data2 = (const unsigned char*)data;
	switch(len & 7)
	{
	case 7: h ^= uint64_t(data2[6]) << 48;
	case 6: h ^= uint64_t(data2[5]) << 40;
	case 5: h ^= uint64_t(data2[4]) << 32;
	case 4: h ^= uint64_t(data2[3]) << 24;
	case 3: h ^= uint64_t(data2[2]) << 16;
	case 2: h ^= uint64_t(data2[1]) << 8;
	case 1: h ^= uint64_t(data2[0]);
	        h *= m;
	};
	h ^= h >> r;
	h *= m;
	h ^= h >> r;
	return h;
}
/*
int main()
{
    cout<<"success\n";
    std::string p = "abcdefghijklmnopqrstuvwxyz";
    uint64_t h = MurmurHash64A(&p,11,11);
    cout<<"murmur : "<<h<<endl;
    std::list<long> hash_list;
    CountEstimator ch(hash_list, 5000, 9999999999971, 11, "", 'y', false);
    ch.add_sequence(p, false);
    return 0;
}
*/
