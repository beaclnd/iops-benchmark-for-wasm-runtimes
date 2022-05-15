#include "stdio.h"
#include <sys/time.h>
#include <stdlib.h>
#define Export __attribute__((visibility("default")))

Export
void get_iops(long long count, long long v1, long long v2, long long v3, long long v4) {
	long long value = 0;
	struct timeval t1, t2;

	gettimeofday(&t1, NULL);
	for (long long i = 0; i < count; i++) {
		value += v1;
		value -= v2;
		value *= v3;
		value /= v4;
	}
	gettimeofday(&t2, NULL);
	long long cost = (t2.tv_sec * 1000 + t2.tv_usec / 1000) - (t1.tv_sec * 1000 + t1.tv_usec / 1000);
	printf("for long long, %lld times integer operations, cost %lldms\n", count, cost);
	if (cost == 0) {
		printf("Please give me a big enough count\n");
		return;
	}
	float iops = (float)(4 * count / cost) * 1000;
	printf("for long long, integer operations per second: %f\n", iops);
	// Use the value variable to avoid optimizing the entire loop
	printf("--------------------------------------------------------------------[%d]\n", (int)value & 1);
}
