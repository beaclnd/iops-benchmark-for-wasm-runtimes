#include "stdio.h"
#include <sys/time.h>
#include <stdlib.h>
#include "iops.h"
#define Export __attribute__((visibility("default")))

const char* spaces1 = "                                     ";
const char* spaces2 = "                 ";
const char* spaces3 = "                       ";

Export
void get_iops_for_long_long(long long count, long long v1, long long v2, long long v3, long long v4) {
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
	if (cost == 0) {
		printf("Please give me a big enough count\n");
		return;
	}
	float iops = (float)(4 * count / cost) * 1000;
	// Use the value variable to avoid optimizing the entire loop
	printf("%slong long%s%lld%s%lld%s%.2f [%d]\n", spaces1, spaces2, count, spaces2, cost, spaces2, iops, (int)value & 1);
}

Export
void get_iops_for_int(long long count, int v1, int v2, int v3, int v4) {
	int value = 0;
	struct timeval t1, t2;

	gettimeofday(&t1, NULL);
	for (int i = 0; i < count; i++) {
		value += v1;
		value -= v2;
		value *= v3;
		value /= v4;
	}
	gettimeofday(&t2, NULL);
	long long cost = (t2.tv_sec * 1000 + t2.tv_usec / 1000) - (t1.tv_sec * 1000 + t1.tv_usec / 1000);
	if (cost == 0) {
		printf("Please give me a big enough count\n");
		return;
	}
	float iops = (float)(4 * count / cost) * 1000;
	// Use the value variable to avoid optimizing the entire loop
	printf("%sint%s%lld%s%lld%s%.2f [%d]\n", spaces1, spaces3, count, spaces2, cost, spaces2, iops, value & 1);
}

// Must contains a start function for runing on nodejs with wasi feature
#ifdef WITHSTART
Export
void _start() {}
#endif