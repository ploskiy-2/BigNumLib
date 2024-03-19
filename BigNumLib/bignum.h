#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    neg = -1,
    zero = 0,
    pos = 1
}sign_t;

typedef struct {
    sign_t sign;
    unsigned int len;
    char *digits;
} bignum_t;

/*Convert from string to bignum*/
bignum_t *from_str_to_bignum (char *str);

char *from_bignum_to_str(bignum_t *ap);

/*Remove leading zeroes*/
char *str_without_lead_zero (char *str, uint8_t len);

/* Free an allocated memory. */
void bignum_free(bignum_t *ap);

/* Create a zero */
bignum_t *bignum_zero ();