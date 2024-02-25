#ifndef FUZZYFINDER_BITONIC_SORT_H
#define FUZZYFINDER_BITONIC_SORT_H

#include <stdlib.h>
#include <util.h>

#define ASCENDING 0
#define DESCENDING 1

void bitonic_sort(StringScore *seq, ulong length);

#endif //FUZZYFINDER_BITONIC_SORT_H
