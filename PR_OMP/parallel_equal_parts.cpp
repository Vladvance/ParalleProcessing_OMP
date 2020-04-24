#include<stdint.h>
#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<string>
#include<vector>

#define OMP_NUM_OF_THREADS 4
using namespace std;

//DIVIDE RANGE TO EQUAL PARTS AND DITRIBUTE THEM BETWEEN THREADS


int main(int argc, char** argv) {

	uint64_t partial_counts[OMP_NUM_OF_THREADS];

	long long start = stoll(argv[1]); 
	long long end = stoll(argv[2]);
	long long part_size = (end - start + 1) / OMP_NUM_OF_THREADS;
	vector<vector <long long> > global_primes;
	if (start <= 2 && end >= 2) global_primes[0].push_back(2L);

#pragma omp parallel num_threads(OMP_NUM_OF_THREADS)
	{
		int id = omp_get_thread_num();
		vector <long long> local_primes;
		long long local_start = start + part_size * id;
		if (local_start % 2 == 0) {
			local_start++;
		}
		long long local_end = (id == OMP_NUM_OF_THREADS - 1) ? end : local_start + part_size;

		for (long long i = local_start; i <= local_end; i += 2) {
			bool is_prime = true;
			long long end = sqrt((double)i);
			for (long long j = 3; j <= end; j += 2) {
				if ((i % j) == 0) {
					is_prime = false;
					break;
				}
			}
			if (is_prime) global_primes[i] = local_primes;
		}
	}
	int primes_count = 0;
	for (auto&& i : global_primes) {
		primes_count += i.size();
	}

	printf("\nPrimes found: %9lld <= %lld\n", primes_count, end - start + 1);                                                   //   :--
}