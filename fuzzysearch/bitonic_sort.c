#include <omp.h>
#include <bitonic_sort.h>

void swap(double *a, double *b);
void bitonic_sort_rec(double *seq, int start, int length, int flag);
void bitonic_merge(double *seq, int start, int length, int flag);
void bitonic_compare_and_swap(double *seq, int i, int j, int flag);


void bitonic_sort(double *seq, int length) {
    omp_set_max_active_levels(3); // arbitrary level and subject to change
    int num_threads = omp_get_max_threads();

#pragma omp parallel num_threads(num_threads)
    {
        #pragma omp single // only the master thread executes this
        bitonic_sort_rec(seq, 0, length, DESCENDING);
    }
}

void bitonic_sort_rec(double *seq, int start, int length, int flag) {
    if (length > 1)  {
        int k = length / 2;
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

void bitonic_merge(double *seq, int start, int length, int flag) {
    if (length > 1) {
        int k = length / 2;

        for (int i = start; i < start + k; ++i) {
            bitonic_compare_and_swap(seq, i, i + k, flag);
        }

        bitonic_merge(seq, start, k, flag);
        bitonic_merge(seq, start + k, k, flag);
    }
}

void bitonic_compare_and_swap(double *seq, int i, int j, int flag) {
    if ((flag == ASCENDING && seq[i] > seq[j]) ||
        (flag == DESCENDING && seq[i] < seq[j])) {
        swap(&seq[i], &seq[j]);
    }
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
