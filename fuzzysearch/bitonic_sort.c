#include <omp.h>
#include <bitonic_sort.h>
#include <error_handling.h>

void swap(double *a, double *b);
void bitonic_sort_par(int start, int length, double *seq, int flag, int sub_size);
void bitonic_sort_seq(int start, int length, double *seq, int flag);


void bitonic_sort(double *seq, int length) {
    int sub_size, num_threads, i, j, flag;

    num_threads = omp_get_max_threads();

    if (length < num_threads * 2) {
        app_error("Length of a bitonic sequence must be at least twice the number of threads\n");
        return;
    }

    sub_size = length / num_threads;

    // make the sequence bitonic
    for (i = 2; i <= sub_size; i *= 2) {
#pragma omp parallel for shared(i, seq) private(j, flag)
        for (j = 0; j < length; j += i) {
            if ((j / i) % 2 == 0) {
                flag = ASCENDING;
            } else {
                flag = DESCENDING;
            }
            bitonic_sort_seq(j, i, seq, flag);
        }
    }

    // sort the sequence
    for (i = 2; i <= num_threads; i *= 2) {
        for (j = 0; j < num_threads; j += i) {
            if ((j / i) % 2 == 0) {
                flag = ASCENDING;
            } else {
                flag = DESCENDING;
            }
            bitonic_sort_par(j * sub_size, i * sub_size, seq, flag, sub_size);
        }
#pragma omp parallel for shared(j)
        for (j = 0; j < num_threads; ++j) {
            if (j < i) {
                flag = ASCENDING;
            } else {
                flag = DESCENDING;
            }
            bitonic_sort_seq(j * sub_size, sub_size, seq, flag);
        }
    }
}

void bitonic_sort_par(int start, int length, double *seq, int flag, int sub_size) {
    int i, split_length;

    if (length == 1) {
        return;
    }

    if (length % 2 != 0) {
        app_error("Length of a bitonic sequence must be a power of 2\n");
        exit(1);
    }

    split_length = length / 2;

#pragma omp parallel for shared(seq, flag, start, split_length) private(i)
    for (i = start; i < start + split_length; ++i) {
        if (flag == ASCENDING) {
            if (seq[i] > seq[i + split_length]) {
                swap(&seq[i], &seq[i + split_length]);
            }
        } else {
            if (seq[i] < seq[i + split_length]) {
                swap(&seq[i], &seq[i + split_length]);
            }
        }
    }

    if (split_length > sub_size) {
        bitonic_sort_par(start, split_length, seq, flag, sub_size);
        bitonic_sort_par(start + split_length, split_length, seq, flag, sub_size);
    }

}

void bitonic_sort_seq(int start, int length, double *seq, int flag) {
    int i, split_length;

    if (length == 1) {
        return;
    }

    if (length % 2 != 0) {
        app_error("Length of a bitonic sequence must be a power of 2\n");
        exit(1);
    }

    split_length = length / 2;

    for (i = start; i < start + split_length; ++i) {
        if (flag == ASCENDING) {
            if (seq[i] > seq[i + split_length]) {
                swap(&seq[i], &seq[i + split_length]);
            }
        } else {
            if (seq[i] < seq[i + split_length]) {
                swap(&seq[i], &seq[i + split_length]);
            }
        }
    }

    bitonic_sort_seq(start, split_length, seq, flag);
    bitonic_sort_seq(start + split_length, split_length, seq, flag);

}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
