#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    neg = -1,
    zero = 0,
    pos = 1
}sign_t;

typedef struct {
    sign_t sign;
    int len;
    char *digits;
} bignum_t;

/*Convert from string to bignum*/
bignum_t *from_str_to_bignum (char *str);

char *from_bignum_to_str(bignum_t *ap);

/*Remove leading zeroes*/
char *str_without_lead_zero (char *str);

/* Free an allocated memory. */
void bignum_free(bignum_t *ap);

/* Create a zero */
bignum_t *bignum_zero ();

/* Remove plus*/
char *str_without_plus(char *str);

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

void remove_leading_zero_from_dig(bignum_t *ap);

/* Mult of two bignum*/
bignum_t *mult_bignum(bignum_t *ap1, bignum_t *ap2);

/* Div of two bignum*/
bignum_t *div_bignum(bignum_t *ap1, bignum_t *ap2);

/*Estimating the quotient digit*/
/*We have an N digit denominator and an N+1 digit numerator 
 to "zero out" the low digits: keep top two from the numerator, and top one from the denominator. */
 bignum_t *est_q(bignum_t *ap1, bignum_t *ap2);

 bignum_t *norm_q(bignum_t *ap1, bignum_t *ap2);

 /*Div by single digit*/
 bignum_t *div_bignum_by_sin_dig(bignum_t *ap1, bignum_t *ap2);