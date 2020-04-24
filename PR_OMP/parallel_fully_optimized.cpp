#include<stdint.h>
#include<stdio.h>
#include<math.h>
#include<omp.h>

#define OMP_NUM_OF_THREADS 4

int main2(int argc, char** argv) {

	uint64_t partial_counts[OMP_NUM_OF_THREADS];
	long long start, end, total_count = 0;
	scanf("%llu%llu", &start, &end);
	if (start % 2 == 0)
	{
		if (start == 2) total_count = 1;
		start++;
	}

#pragma omp parallel num_threads(OMP_NUM_OF_THREADS)
	{
		int        id = omp_get_thread_num();
		int        local_count = 0;

		for (long long i = (start + (2 * id)); i < end; i += (2 * OMP_NUM_OF_THREADS))
		{
			bool is_prime = true;
			long long end = sqrt((double)i);
			for (long long j = 3; j <= end; j += 2) {
				if ((i % j) == 0) {
					is_prime = false; 
					break;
				}
			}
			if (is_prime) local_count++;
		}
		partial_counts[id] = local_count;
	}

	for (int thread_id = 0; thread_id < OMP_NUM_OF_THREADS; thread_id++) {
		total_count += partial_counts[thread_id];
	}
	printf("\nPrimes found: %9lld <= %lld\n", total_count, end-start+1);                                                   //   :--
}