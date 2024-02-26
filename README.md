# Fuzzy Search
A fuzzy finding library using an implementation of the Damerau-Levenshtein distance to measure edit distance between strings.
## Usage
Usage depends on how you link the library. First, you need to include the library in your source code.
If you are using CMake, you can link the library using the following commands:
```cmake
# CMakeLists.txt
# replace path/to/ with the actual path to the library
include_directories( path/to/fuzzysearch ) 
```
If you are using a Makefile, you can link the library using the following commands:
```makefile
# Makefile
# replace path/to/ with the actual path to the library
CFLAGS = -I path/to/fuzzysearch
```
If you are just using a compiler, add this to your command line arguments or to your compileflags.txt:
```bash
# replace path/to/ with the actual path to the library
-I path/to/fuzzysearch
```

Now, you can use the library in your source code. You will want to include the fuzzysearch.h file. 
You will then call the fuzzy_search function with the string you want to search for, the list of strings you want to search through,
the threshold comparison percentage, and the weights you want to use for the different operations.
Note: Similarity score is 1 - (edit distance / max_length of the two strings compared)
```c
#include <stdlib.h>
#include <fuzzysearch.h>

int main() {
    // setup
    size_t *result_len, list_len = 2;
    char *search = "hello";
    char *list[] = {"hello", "world};
    double threshold = 0.5; 
    
    // fuzzy search ; assuming we want even weights for all operations
    // returns a sorted list (in descending order) of strings according to their similarity scores
    char **result = fuzzy_search(search, 
                                        list, 
                                        list_len, 
                                        result_len,
                                        1, // transposition cost
                                        1, // substitution cost
                                        1, // insertion cost
                                        1, // deletion cost
                                        threshold);

}
```
