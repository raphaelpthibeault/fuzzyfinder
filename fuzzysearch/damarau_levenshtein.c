#include <damarau_levenshtein.h>
#include <string.h>
#include <wrapper.h>

/*
 * A function to calculate the Damarau-Levenshtein distance between two strings.
 * The Damarau-Levenshtein distance between two strings is the minimum number of operations (insertions, deletions,
 * substitutions, and transpositions) required to transform one string into the other.
 * https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
 * This is an implementation of the true Damarau-Levenshtein distance, which includes transposition.
 * Realize we only need to keep the last thee rows of the dynanmic programming table
 * */
ulong dam_lev(const char *string1, const char *string2,
            int transposition_cost, int substitution_cost,
            int insertion_cost, int deletion_cost) {

    ulong len1 = strlen(string1), len2 = strlen(string2);
    ulong *row0, *row1, *row2;
    ulong i, j;

    ALLOC_ARRAY(row0, len2 + 1);
    ALLOC_ARRAY(row1, len2 + 1);
    ALLOC_ARRAY(row2, len2 + 1);

    for (j = 0; j <= len2; ++j) {
        row1[j] = j * insertion_cost;
    }

    for (i = 0; i < len1; ++i) {
        ulong *temp;

        row2[0] = (i + 1) * deletion_cost;
        for (j = 0; j < len2; ++j) {
            // substitution
            row2[j + 1] = row1[j] + substitution_cost * (string1[i] != string2[j]);
            // transposition
            if (i > 0 && j > 0 &&
                string1[i] == string2[j - 1] && string1[i - 1] == string2[j] &&
                row2[j + 1] > row0[j - 1] + transposition_cost) {
                row2[j + 1] = row0[j - 1] + transposition_cost;
            }
            // deletion
            if (row2[j + 1] > row1[j + 1] + deletion_cost) {
                row2[j + 1] = row1[j + 1] + deletion_cost;
            }
            // insertion
            if (row2[j + 1] > row2[j] + insertion_cost) {
                row2[j + 1] = row2[j] + insertion_cost;
            }
        }

        temp = row0;
        row0 = row1;
        row1 = row2;
        row2 = temp;
    }

    i = row1[len2];
    FREE_AND_NULL(row0);
    FREE_AND_NULL(row1);
    FREE_AND_NULL(row2);

    return i;
}
