#include <fuzzy.h>
#include <wrapper.h>
#include <string.h>
#include <bitonic_sort.h>

StringScore *fuzzy_search(const char *query, const char **list, size_t list_len, size_t *result_len,
                          int transposition_cost, int substitution_cost, int insertion_cost, int deletion_cost,
                          double threshold) {
    StringScore *temp_result;
    ALLOC_ARRAY(temp_result, list_len);

    ulong count = 0;
    for (ulong i = 0; i < list_len; ++i) {
        ulong dl = dam_lev(query, list[i], transposition_cost, substitution_cost, insertion_cost, deletion_cost);
        ulong max_length = strlen(query) > strlen(list[i]) ? strlen(query) : strlen(list[i]);
        double score = 1 - (double) dl / (double)max_length;
        if (score >= threshold) {
            temp_result[count].str = (char *) list[i];
            temp_result[count].score = score;
            count++;
        }
    }

    *result_len = count;
    StringScore *result;
    ALLOC_ARRAY(result, count);
    memcpy(result, temp_result, count * sizeof(StringScore));
    FREE_AND_NULL(temp_result);

    bitonic_sort(result, *result_len);

    return result;
}
