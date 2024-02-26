#include <fuzzy.h>
#include <wrapper.h>
#include <string.h>
#include <bitonic_sort.h>
#include <omp.h>


ulong next_power_of_2(ulong n) {
    if (n == 0) {
        return 1;
    }
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32; // Assuming a 64-bit architecture
    return n + 1;
}

char **fuzzy_search(const char *query, const char **list, size_t list_len, size_t *result_len,
                          int transposition_cost, int substitution_cost, int insertion_cost, int deletion_cost,
                          double threshold) {
    StringScore *temp_result;
    ALLOC_ARRAY(temp_result, list_len);

    ulong count = 0;


#pragma omp parallel
    {
        #pragma omp for
        for (ulong i = 0; i < list_len; ++i) {
            ulong dl = dam_lev(query, list[i], transposition_cost, substitution_cost, insertion_cost, deletion_cost);
            ulong max_length = strlen(query) > strlen(list[i]) ? strlen(query) : strlen(list[i]);
            double score = 1 - (double) dl / (double)max_length;
            if (score >= threshold) {
                #pragma omp critical
                {
                    temp_result[count].str = (char *) list[i];
                    temp_result[count].score = score;
                    count++;
                }
            }
        }
    }

    ulong padded_length = next_power_of_2(count);
    StringScore *result = Realloc(temp_result, st_mult(padded_length, sizeof(StringScore)));
    for (ulong i = count; i < padded_length; ++i) {
        result[i].str = NULL;
        result[i].score = -1; // similar to negative infinity since scores are between 0 and 1
    }

    bitonic_sort(result, padded_length);

    char **ret;
    ALLOC_ARRAY(ret, count);
    for (ulong i = 0; i < count; ++i) {
        ret[i] = result[i].str;
    }

    *result_len = count;
    FREE_AND_NULL(result);

    return ret;
}
