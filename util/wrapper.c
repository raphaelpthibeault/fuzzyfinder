#include <wrapper.h>
#include <error_handling.h>

/* static function declarations */
static void check_memory_limit(size_t size);

/* HEADER FUNCTIONS */
void *Malloc(size_t size) {
    void *ret;
    check_memory_limit(size);

    ret = malloc(size);
    if (!ret && !size) {
        ret = malloc(1);
    }
    if (!ret) {
        unix_error("Malloc error");
    }

#ifdef MALLOC_POISON // for debugging
    memset(ret, 0xA5, size);
#endif
    return ret;

}

void *Alloc_array(void **ptr, size_t size, size_t elem_size) {
    *ptr = Malloc(st_mult(size, elem_size)); // abort on overflow
    return *ptr;
}

void *Realloc(void *ptr, size_t size) {
    void *ret;
    check_memory_limit(size);

    ret = realloc(ptr, size);
    if (!ret && !size) {
        ret = malloc(1);
    }
    if (!ret) {
        unix_error("Realloc error");
    }
    return ret;
}

/* STATIC FUNCTIONS */
static void check_memory_limit(size_t size) {
    ulong max_memory = 1024 * 1024 * 1024; // 1GB ; completely arbitrary and subject to change
    if (size > max_memory) {
        unix_error("Memory limit exceeded");
    }
}


