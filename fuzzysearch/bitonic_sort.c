#include <omp.h>
#include <bitonic_sort.h>

void bitonic_sort_rec(StringScore *seq, ulong start, ulong length, int flag);
void bitonic_merge(StringScore *seq, ulong start, ulong length, int flag);
void bitonic_compare_and_swap(StringScore *seq, ulong i, ulong j, int flag);
void swap(StringScore *a, StringScore *b);

void bitonic_sort(StringScore *seq, ulong length) {
    omp_set_max_active_levels(3); // Arbitrary level and subject to change
    int num_threads = omp_get_max_threads();

#pragma omp parallel num_threads(num_threads)
    {
#pragma omp single // only the master thread executes this
        bitonic_sort_rec(seq, 0, length, DESCENDING);
    }
}

void bitonic_sort_rec(StringScore *seq, ulong start, ulong length, int flag) {
    if (length > 1) {
        ulong k = length / 2;
#pragma omp parallel sections
        {
#pragma omp section
            bitonic_sort_rec(seq, start, k, flag);
#pragma omp section
            bitonic_sort_rec(seq, start + k, k, flag == ASCENDING ? DESCENDING : ASCENDING);
        }

        bitonic_merge(seq, start, length, flag);
    }
}

void bitonic_merge(StringScore *seq, ulong start, ulong length, int flag) {
    if (length > 1) {
        ulong k = length / 2;

        for (ulong i = start; i < start + k; ++i) {
            bitonic_compare_and_swap(seq, i, i + k, flag);
        }

        bitonic_merge(seq, start, k, flag);
        bitonic_merge(seq, start + k, k, flag);
    }
}

void bitonic_compare_and_swap(StringScore *seq, ulong i, ulong j, int flag) {
    if ((flag == ASCENDING && seq[i].score > seq[j].score) ||
        (flag == DESCENDING && seq[i].score < seq[j].score)) {
        swap(&seq[i], &seq[j]);
    }
}

void swap(StringScore *a, StringScore *b) {
    StringScore temp = *a;
    *a = *b;
    *b = temp;
}

