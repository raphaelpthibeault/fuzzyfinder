#ifndef FUZZYFINDER_DAMARAU_LEVENSHTEIN_H
#define FUZZYFINDER_DAMARAU_LEVENSHTEIN_H

#include <util.h>

ulong dam_lev(const char *string1, const char *string2,
              int transposition_cost, int substitution_cost,
              int insertion_cost, int deletion_cost);

#endif //FUZZYFINDER_DAMARAU_LEVENSHTEIN_H
