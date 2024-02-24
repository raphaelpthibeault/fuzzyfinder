#ifndef FUZZYFINDER_FUZZYSEARCH_H
#define FUZZYFINDER_FUZZYSEARCH_H

int dam_lev(const char *string1, const char *string2,
            int transposition_cost, int substitution_cost,
            int insertion_cost, int deletion_cost);

#endif //FUZZYFINDER_FUZZYSEARCH_H
