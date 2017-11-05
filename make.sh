rm ./vegeta.out
echo "********** Compiling ***********"
g++ minhash.cpp -o vegeta.out
g++ --std=c++11 bloom_filter_for_CH.cpp -o bloom_filter_for_CH
echo "********** executing ***********"
./vegeta.out
