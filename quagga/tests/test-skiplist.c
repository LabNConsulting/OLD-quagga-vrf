/*
 * Skip List impementation based on code from William Pugh.
 * ftp://ftp.cs.umd.edu/pub/skipLists/
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/skiplist.h"

struct thread_master *master;

static uintptr_t
scramble(int i)
{
    uintptr_t	result;

    result = (i & 0xff) << 24;
    result |= (i >> 8);

    return result;
}

#define sampleSize 65536
static int
skiplist_test(void) {
    struct skiplist *l;
    register int i,k;
    void *keys[sampleSize];
    void *v;

    l= skiplist_new(SKIPLIST_FLAG_ALLOW_DUPLICATES, NULL, NULL);

    printf("%s: skiplist_new returned %p\n", __func__, l);

    for (i=0; i < 4; i++) {

	for (k=0; k < sampleSize; k++) {
	    if (!(k%1000)) {
		printf("%s: (%d:%d)\n", __func__, i, k);
	    }
	    keys[k] = (void *)scramble(k);
	    if (skiplist_insert(l, keys[k], keys[k])) {
		printf("error in insert #%d,#%d\n",i,k);
		return 1;
	    }
	}

	printf("%s: inserts done\n", __func__);

        for (k=0; k < sampleSize; k++) {

	    if (!(k % 1000))
		printf("[%d:%d]\n", i, k);
	    if (skiplist_search(l, keys[k], &v)) {
		printf("error in search #%d,#%d\n",i,k);
		return 1;
	    }

	    if (v != keys[k]) {
		printf("search returned wrong value\n");
		return 1;
	    }
	}



        for (k=0; k < sampleSize; k++) {

	    if (!(k % 1000))
		printf("<%d:%d>\n", i, k);
	    if (skiplist_delete(l, keys[k], keys[k])) {
		printf("error in delete\n");
		return 1;
	    }
	    keys[k] = (void *)scramble(k ^ 0xf0f0f0f0);
	    if (skiplist_insert(l, keys[k], keys[k])) {
		printf("error in insert #%d,#%d\n",i,k);
		return 1;
	    }
	}

        for (k=0; k < sampleSize; k++) {

	    if (!(k % 1000))
		printf("{%d:%d}\n", i, k);
	    if (skiplist_delete_first(l)) {
		printf("error in delete_first\n");
		return 1;
	    }
	}
    }

    skiplist_free(l);

    return 0;
}

int
main(void)
{
    return skiplist_test();
}
