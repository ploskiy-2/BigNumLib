#include <bignum.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_leading_zero(bignum_t* ap);
// add zeroes to the top for useful subtraction
static void bignum_add_zero(bignum_t* ap, uint8_t t);
static void bignum_subtract(bignum_t** a, bignum_t* b);
static void bignum_shift(bignum_t* x);
static bignum_t* helper_sub_bignum(bignum_t* ap1, bignum_t* ap2);
static bignum_t* helper_div_bignum(bignum_t* ap1, bignum_t* ap2);
static bignum_t* helper_sum_bignum(bignum_t* ap1, bignum_t* ap2);
static bignum_t* create_bignum_size(size_t size);
static sign_t define_sign_sum(bignum_t* ap1, bignum_t* ap2);

void bignum_free(bignum_t* ap)
{
    if (ap) {
        free(ap->digits);
        free(ap);
    }
    return;
}

bignum_t* bignum_zero()
{
    bignum_t* ap = malloc(sizeof(*ap));
    ap->sign = zero;
    ap->len = 1;
    ap->digits = calloc(1, sizeof(*ap->digits));
    if (!ap || !ap->digits) {
        bignum_free(ap);
        return NULL;
    }
    return ap;
}

bignum_t* from_str_to_bignum(char* str)
{
    if (!str) {
        return NULL;
    }

    sign_t sign = pos;
    size_t len = strlen(str);

    if (*str == '-') {
        sign = neg;
        str++;
        len--;
    } else if (*str == '0' && len == 1) {
        return bignum_zero();
    } else if (*str == '+') {
        sign = pos;
        str++;
        len--;
    }
    while ((len > 0) && *str == '0') {
        str++;
        len--;
    }

    if (len == 0) {
        return bignum_zero();
    }

    bignum_t* ap = malloc(sizeof(*ap));
    if (!ap) {
        return NULL;
    }
    ap->digits = calloc(len, sizeof(*ap->digits));
    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }
    ap->sign = sign;

    int char_cnt = 0;
    for (size_t i = 0; i < len; i++) {
        char t = str[len - 1 - i];
        /*we want from "123SAKOD123 --> 123123"*/
        if (isdigit(t)) {
            ap->digits[char_cnt] = t - '0';
            char_cnt++;
        }
    }
    ap->len = char_cnt;
    return ap;
}

char* from_bignum_to_str(bignum_t* ap)
{
    if (!ap) {
        return NULL;
    }

    sign_t sign = ap->sign;
    size_t len = ap->len;

    if (sign == zero && len == 1) {
        char* res = calloc(2, sizeof(char));
        if (!res) {
            return NULL;
        }
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    char* str = calloc(len + 2, sizeof(*str));
    if (!str) {
        return NULL;
    }

    int offset = 0;
    if (sign == neg) {
        *str = '-';
        offset = 1;
    }

    for (size_t i = 0; i < len; i++) {
        str[i + offset] = ap->digits[len - i - 1] + '0';
    }
    str[len + offset] = '\0';
    return str;
}

static void bignum_add_zero(bignum_t* ap, uint8_t t)
{
    if (!ap) {
        return;
    }
    ap->digits = realloc(ap->digits, sizeof(*ap->digits) * (ap->len + t));
    memset(ap->digits + ap->len, 0, t);
    ap->len += t;
    return;
}

bool is_equal_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }
    if (ap1->sign != ap2->sign) {
        return false;
    }
    if (ap1->len != ap2->len) {
        return false;
    }
    for (size_t i = 0; i < ap1->len; i++) {
        if (ap1->digits[i] != ap2->digits[i]) {
            return false;
        }
    }
    return true;
}

int compare_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if ((ap1->len) < (ap2->len)) {
        return -1;
    } else if ((ap1->len) > (ap2->len)) {
        return 1;
    } else {
        for (size_t i = 0; i < ap1->len; i++) {
            if ((ap1->digits[ap1->len - 1 - i]) < (ap2->digits[ap2->len - 1 - i])) {
                return -1;
            } else if ((ap1->digits[ap1->len - 1 - i]) > (ap2->digits[ap2->len - 1 - i])) {
                return 1;
            }
        }
    }
    return 0;
}

static void remove_leading_zero(bignum_t* ap)
{
    if (!ap) {
        return;
    }
    size_t old_len = ap->len;
    size_t new_len = old_len;

    while (new_len > 1 && ap->digits[new_len - 1] == 0) {
        new_len--;
    }

    if (new_len != old_len) {
        ap->digits = realloc(ap->digits, sizeof(*ap->digits) * new_len);
        if (!ap->digits) {
            bignum_free(ap);
            return;
        }
        ap->len = new_len;
    }

    if (new_len == 1 && ap->digits[0] == 0) {
        ap->sign = zero;
    }
}

bignum_t* copy_bignum(bignum_t* ap)
{
    if (!ap) {
        return NULL;
    }

    bignum_t* new_ap = malloc(sizeof(*new_ap));
    if (!new_ap) {
        return NULL;
    }
    new_ap->sign = ap->sign;
    new_ap->len = ap->len;
    new_ap->digits = calloc(ap->len, sizeof(*ap->digits));
    if (!new_ap->digits) {
        bignum_free(new_ap);
        return NULL;
    }
    memcpy(new_ap->digits, ap->digits, ap->len * sizeof(*ap->digits));
    return new_ap;
}

static sign_t define_sign_sum(bignum_t* ap1, bignum_t* ap2)
{
    if ((ap1->sign + ap2->sign == 2 * neg) || (ap1->sign + ap2->sign == neg)) {
        return neg;
    }
    if ((ap1->sign == zero) && (ap2->sign == zero)) {
        return zero;
    }
    return pos;
}

bignum_t* sum_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if ((ap1->sign == neg) && (ap2->sign == pos)) {
        bignum_t* ap3 = copy_bignum(ap1);
        ap3->sign = pos;
        bignum_t* ap4 = sub_bignum(ap2, ap3);
        bignum_free(ap3);
        return ap4;
    }
    if ((ap1->sign == pos) && (ap2->sign == neg)) {
        bignum_t* ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t* ap4 = sub_bignum(ap1, ap3);
        bignum_free(ap3);
        return ap4;
    }

    size_t len1 = ap1->len;
    size_t len2 = ap2->len;
    size_t len = (len1 > len2) ? len1 : len2;

    bignum_t* ap4 = copy_bignum(ap1);
    bignum_t* ap5 = copy_bignum(ap2);

    bignum_add_zero(ap4, len - len1);
    bignum_add_zero(ap5, len - len2);
    bignum_t* ap6 = helper_sum_bignum(ap4, ap5);

    bignum_free(ap4);
    bignum_free(ap5);
    return ap6;
}

static bignum_t* helper_sum_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }
    int car = 0;
    int dig, digit_sum;
    size_t len = ap1->len;
    bignum_t* ap = malloc(sizeof(*ap));
    if (!ap) {
        return NULL;
    }
    ap->digits = calloc(len + 1, sizeof(*ap->digits));
    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        digit_sum = car;
        digit_sum += (ap1->digits[i]) + (ap2->digits[i]);
        dig = digit_sum % 10;
        car = digit_sum / 10;
        ap->digits[i] = dig;
    }

    if (car > 0) {
        ap->digits[len] = car;
        len++;
    }
    ap->sign = define_sign_sum(ap1, ap2);
    ap->len = len;

    return ap;
}

bignum_t* sub_bignum(bignum_t* ap1, bignum_t* ap2)
{
    bignum_t* ap3 = copy_bignum(ap2);
    bignum_t* ap4 = copy_bignum(ap1);
    bignum_t* ap5 = helper_sub_bignum(ap4, ap3);
    bignum_free(ap3);
    bignum_free(ap4);
    return ap5;
}

static bignum_t* helper_sub_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }

    sign_t sign;
    int borrow = 0;
    int digit_sub;

    /*a - (-b) = a+b */
    if (ap1->sign == pos && ap2->sign == neg) {
        bignum_t* ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t* ap4 = sum_bignum(ap1, ap3);
        bignum_free(ap3);
        return ap4;
    }

    /*-a - (-b) = -a+b */
    if (ap1->sign + ap2->sign == 2 * neg) {
        bignum_t* r = copy_bignum(ap2);
        r->sign = pos;
        bignum_t* ap4 = sum_bignum(ap1, r);
        bignum_free(r);
        return ap4;
    }

    /*-a - b= -(a+b)   */
    if (ap1->sign == neg && ap2->sign == pos) {
        bignum_t* r = copy_bignum(ap1);
        r->sign = pos;
        bignum_t* ap3 = sum_bignum(r, ap2);
        ap3->sign = neg;
        bignum_free(r);
        return ap3;
    }

    /*want to subtract a lower number from a higher*/
    if (compare_bignum(ap1, ap2) == -1) {
        bignum_t* r = sub_bignum(ap2, ap1);
        if ((ap1->sign + ap2->sign == 2 * pos) || (ap1->sign + ap2->sign == pos)) {
            r->sign = neg;
        } else if ((ap1->sign + ap2->sign == neg)) {
            r->sign = pos;
        }
        return r;
    } else {
        sign = ap1->sign;
    }

    /*assume |ap1| always more than |ap2| */
    size_t len1 = ap1->len;
    size_t len2 = ap2->len;
    size_t len = len1;

    bignum_add_zero(ap1, len - len1);
    bignum_add_zero(ap2, len - len2);

    bignum_t* ap = malloc(sizeof(*ap));
    if (!ap) {
        return NULL;
    }

    ap->digits = calloc(len, sizeof(*ap->digits));
    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        digit_sub = (ap1->digits[i]) - (ap2->digits[i]) - borrow;
        if (digit_sub < 0) {
            digit_sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        ap->digits[i] = digit_sub;
    }

    ap->sign = sign;
    ap->len = len;

    remove_leading_zero(ap);
    return ap;
}

bignum_t* mult_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }
    int car, mul;
    size_t len1 = ap1->len;
    size_t len2 = ap2->len;
    bignum_t* ap = malloc(sizeof(*ap));
    if (!ap) {
        return NULL;
    }
    ap->sign = ap1->sign * ap2->sign;

    ap->digits = calloc(len1 + len2, sizeof(*ap->digits));
    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }

    ap->len = len1 + len2;

    for (size_t i = 0; i < len1; i++) {
        car = 0;
        for (size_t j = 0; j < len2; j++) {
            mul = ap1->digits[i] * ap2->digits[j] + car + ap->digits[i + j];
            ap->digits[i + j] = mul % 10;
            car = mul / 10;
        }
        ap->digits[i + len2] += car;
    }
    remove_leading_zero(ap);
    return ap;
}

static void bignum_subtract(bignum_t** a, bignum_t* b)
{
    bignum_t* prev;
    prev = *a;
    *a = sub_bignum(*a, b);
    bignum_free(prev);
}

bignum_t* div_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (ap2->sign == zero) {
        return NULL;
    }

    if (compare_bignum(ap1, ap2) == -1 || ap1->sign == zero) {
        return bignum_zero();
    }
    if (ap2->sign + ap1->sign == 2*neg)
    {
        bignum_t* ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t* ap4 = helper_div_bignum(ap1, ap3);
        ap4->sign = ap1->sign * ap2->sign;
        bignum_free(ap3);
        return sum_bignum(ap4, from_str_to_bignum("1"));
    }
    if (ap2->sign == pos && ap1->sign == neg)
    {
        bignum_t* ap4 = helper_div_bignum(ap1, ap2);
        ap4->sign = ap1->sign * ap2->sign;
        if (is_equal_bignum(ap1, mult_bignum(ap4, ap2))){
            return ap4;
        }
        return sub_bignum(ap4, from_str_to_bignum("1"));
    }
    if (ap2->sign == neg) {
        bignum_t* ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t* ap4 = helper_div_bignum(ap1, ap3);
        ap4->sign = ap1->sign * ap2->sign;
        bignum_free(ap3);
        return ap4;
    }
    return helper_div_bignum(ap1, ap2);
}

static bignum_t* helper_div_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }

    bignum_t* quotient = create_bignum_size(ap1->len);
    if (!quotient) {
        return NULL;
    }
    bignum_t* current = create_bignum_size(ap1->len);
    if (!current) {
        bignum_free(quotient);
        return NULL;
    }
    current->len = 0;
    current->sign = pos;

    for (size_t i = 0; i < ap1->len; i++) {
        bignum_shift(current);

        current->digits[0] = ap1->digits[ap1->len - i - 1];
        current->len++;
        remove_leading_zero(current);

        int count = 0;
        while (compare_bignum(current, ap2) >= 0) {
            bignum_subtract(&current, ap2);
            count++;
        }
        quotient->digits[ap1->len - i - 1] = count;
    }

    quotient->sign = ap1->sign * ap2->sign;
    remove_leading_zero(quotient);
    bignum_free(current);
    return quotient;
}

static bignum_t* create_bignum_size(size_t size)
{
    bignum_t* ap = malloc(sizeof(*ap));
    if (!ap) {
        return NULL;
    }
    ap->sign = pos;
    ap->len = size;
    ap->digits = calloc(size + 1, sizeof(*ap->digits));
    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }
    return ap;
}

static void bignum_shift(bignum_t* ap)
{
    if (!ap) {
        return;
    }
    uint8_t* old = ap->digits;
    uint8_t* tmp = calloc(ap->len + 2, sizeof(*ap->digits));
    if (!tmp) {
        return;
    }
    memcpy(tmp + 1, old, ap->len);
    ap->digits = tmp;
    ap->len += 1;
    free(old);
    return;
}

bignum_t* mod_bignum(bignum_t* ap1, bignum_t* ap2)
{
    if (!ap1 || !ap2) {
        return NULL;
    }
    bignum_t* q = div_bignum(ap1, ap2);
    bignum_t* c = mult_bignum(ap2, q);
    bignum_t* r = sub_bignum(ap1, c);
    bignum_free(q);
    bignum_free(c);
    return r;
}