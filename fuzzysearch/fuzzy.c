#include <fuzzy.h>
#include <wrapper.h>
#include <string.h>

int compare_similarity(const void *a, const void *b) {
    double diff = ((StringScore *)b)->score - ((StringScore *)a)->score;
    return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}

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

    qsort(result, *result_len, sizeof(StringScore), compare_similarity);

    return result;
}
