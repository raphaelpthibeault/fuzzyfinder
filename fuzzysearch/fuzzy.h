#ifndef FUZZYFINDER_FUZZY_H
#define FUZZYFINDER_FUZZY_H

#include <stdlib.h>
#include <damarau_levenshtein.h>
#include <util.h>

StringScore *fuzzy_search(const char *query, const char **list, size_t list_len, size_t *result_len,
                          int transposition_cost, int substitution_cost, int insertion_cost, int deletion_cost,
                          double threshold);



#endif //FUZZYFINDER_FUZZY_H
