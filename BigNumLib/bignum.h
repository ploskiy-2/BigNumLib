#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    neg = -1,
    zero = 0,
    pos = 1
} sign_t;

typedef struct {
    sign_t sign;
    int len;
    char *digits;
} bignum_t;

/*Convert from string to bignum*/
bignum_t *from_str_to_bignum (char *str);

char *from_bignum_to_str(bignum_t *ap);

/* Free an allocated memory. */
void bignum_free(bignum_t *ap);

/* Create a zero */
bignum_t *bignum_zero();

/* Sum of two bignum*/
bignum_t *sum_bignum(bignum_t *ap1, bignum_t *ap2);

/* Check equality of two bignum*/
bool is_equal_bignum(bignum_t *ap1, bignum_t *ap2);

/* Sub of two bignum*/
bignum_t *sub_bignum(bignum_t *ap1, bignum_t *ap2);

/* Create mirror bignum */
bignum_t *copy_bignum(bignum_t *ap);

/*-1 means |ap1| < |ap2|*/
/*1 means |ap1| > |ap2|*/
/*0 means |ap1| = |ap2|*/
int compare_bignum(bignum_t *ap1, bignum_t *ap2);

/* Mult of two bignum*/
bignum_t *mult_bignum(bignum_t *ap1, bignum_t *ap2);

/* Div of two bignum*/
bignum_t *div_bignum(bignum_t *ap1, bignum_t *ap2);

/* MOD for two bignum */
bignum_t *mod_bignum(bignum_t *ap1, bignum_t *ap2);

