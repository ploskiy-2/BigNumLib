#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <bignum.h>

static void remove_leading_zero(bignum_t *ap);
static void bignum_add_zero(bignum_t *ap, uint8_t t);
static void bignum_subtract(bignum_t **a, bignum_t *b);
static void bignum_shl(bignum_t *x, size_t offset);
static bignum_t *helper_sub_bignum(bignum_t *ap1, bignum_t *ap2);

void bignum_free(bignum_t *ap)
{
    if (ap)
    {
        free(ap->digits);
        free(ap);
    }
    return;
}

bignum_t *bignum_zero()
{
    bignum_t *ap = malloc(sizeof(*ap));
    ap->sign = zero;
    ap->len = 1;
    ap->digits = malloc(sizeof(char)); 
    if (!ap || !ap->digits)
    {
        bignum_free(ap);
        return NULL;
    }
    ap->digits[0] = 0;
    return ap;
}

bignum_t *from_str_to_bignum (char *str)    
{
    if (!str)
    {
        return NULL;
    }

    int8_t sign = pos;
    int len = strlen(str);
    
    if (*str=='-')
    {
        sign = neg;
        str++;
        len--;
    }
    else if (*str=='0' && len==1)
    {
        return bignum_zero();
    }
    else if(*str=='+')
    {
        sign = pos;
        str++;
        len--;
    }
    while ((len>0) && *str=='0')
    {
        str++;
        len--;
    }
    
    if (len==0)
    {
        return bignum_zero();
    }
        
    bignum_t *ap = malloc(sizeof(*ap));
    ap->digits = calloc(len,sizeof(char));  
    if (!ap || !ap->digits)
    {
        bignum_free(ap);
        return NULL;
    }
    ap->sign = sign;
    int ch_cnt = 0;
    for (size_t i=0; i<len; i++){
        char t = str[len-1-i];
        /*we want from "123SAKOD123 --> 123123"*/
        if (isdigit(t))
        {
            ap->digits[ch_cnt] = t-'0';
            ch_cnt++;
        }
    }
    ap->len = ch_cnt;
    return ap;
}

char *from_bignum_to_str(bignum_t *ap){
    if (!ap)
    {
        return NULL;
    }

    sign_t sign = ap->sign;
    unsigned int len = ap->len;

    if (sign==zero && len==1)
    {
        char *res = calloc(2, sizeof(char));
        if (!res)
        {
            return NULL;
        }
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    char *str = calloc(len+2,sizeof(char));
    if (!str)
    {
        return NULL;
    }

    if (sign==neg)
    {
        *str = '-';
    }
    
    else if(sign==pos)
    {
        *str = '+';
    }

    for (size_t i=1; i<=len; i++)
    {
        str[i] = ap->digits[len-i] + '0';       
    }

    str[len+1] = '\0';

    if (sign==pos)
    {
        memmove(str, str + 1, strlen(str));
    }
    return str;
}

static void bignum_add_zero(bignum_t *ap, uint8_t t) {
    if (!ap) {
        return;
    }
    ap->digits = realloc(ap->digits, sizeof(char) * (ap->len + t));
    memset(ap->digits + ap->len, 0, t);

    ap->len += t;
    return;
}

bignum_t *sum_bignum(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2)
    {
        return NULL;
    }
    sign_t sign = pos;
    int car = 0;
    int dig, digit_sum;

    if ((ap1->sign + ap2->sign == 2*neg) || ((ap1->sign * ap2->sign == zero) && (ap1->sign + ap2->sign == neg))) 
    {
        sign = neg;
    }
    if ((ap1->sign==zero)&&(ap2->sign==zero))
    {
        sign = zero;
    }
    if ((ap1->sign==neg)&&(ap2->sign==pos))
    {
        bignum_t *ap3 = copy_bignum(ap1);
        ap3->sign = pos;
        bignum_t *ap4 = sub_bignum(ap2,ap3);
        bignum_free(ap3);
        return ap4;
    }
    if ((ap1->sign==pos)&&(ap2->sign==neg))
    {
        bignum_t *ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t *ap4 = sub_bignum(ap1,ap3);
        bignum_free(ap3);
        return ap4;
    }

    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;
    unsigned int len = (len1 > len2) ? len1 : len2;

    bignum_add_zero(ap1,len-len1);
    bignum_add_zero(ap2,len-len2);

    bignum_t *ap = malloc(sizeof(*ap));
    if (!ap)
    {
        bignum_free(ap);
        return NULL;
    }
    ap->digits = calloc(len+1,sizeof(char));
    if (!ap->digits)
    {
        bignum_free(ap);
        return NULL;
    }

    for (size_t i=0; i<len; i++)
    {
        digit_sum = car;
        digit_sum  += (ap1->digits[i]) + (ap2->digits[i]);
        dig = digit_sum % 10; 
        car = digit_sum / 10;

        ap->digits[i] = dig;      
    }
    if (car > 0) 
    { 
        ap->digits[len] = car; 
        len++;  
    }
    ap->sign = sign;
    ap->len = len;
    
    return ap;
}

bool is_equal_bignum(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }
    if (ap1->sign != ap2->sign){
        return false;
    }
    if (ap1->len != ap2->len){
        return false;
    }
    for (size_t i=0;i<ap1->len;i++){
        if (ap1->digits[i] != ap2->digits[i]){
            return false;
        }
    }
    return true;
}

int compare_bignum(bignum_t *ap1, bignum_t *ap2) {
    int res = 0;
    if ((ap1->len) < (ap2->len)) {
        res = -1;
    } 
    else if ((ap1->len) > (ap2->len)) {
        res = 1;
    } 
    else {
        for (size_t i = 0; i < ap1->len; i++) {
            if ((ap1->digits[ap1->len - 1 - i]) < (ap2->digits[ap2->len - 1 - i])) {
                res = -1;
                break;
            } 
            else if ((ap1->digits[ap1->len - 1 - i]) > (ap2->digits[ap2->len - 1 - i])) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

bignum_t *copy_bignum(bignum_t *ap)
{
    if (!ap)
    {
        return NULL;
    }
    bignum_t *new_ap = malloc(sizeof(*new_ap));
    if (!new_ap)
    {
        bignum_free(new_ap);
        return NULL;
    }
    new_ap->sign = ap->sign;
    new_ap->len = ap->len;
    new_ap->digits = calloc(ap->len,sizeof(char));
    if (!new_ap->digits)
    {
        bignum_free(new_ap);
        return NULL;
    }
    for (size_t i = 0; i < ap->len; i++)
    {
        new_ap->digits[i] = ap->digits[i];
    }
    return new_ap;
}


bignum_t *sub_bignum(bignum_t *ap1, bignum_t *ap2)
{
    bignum_t *ap3 = copy_bignum(ap2);
    bignum_t *ap4 = helper_sub_bignum(ap1,ap3);
    bignum_free(ap3);
    return ap4;   
}

bignum_t *helper_sub_bignum(bignum_t *ap1, bignum_t *ap2)
{
    if(!ap1 || !ap2)
    {
        return NULL;
    }

    sign_t sign;

    /*a - (-b) = a+b */
    if (ap1->sign==pos && ap2->sign==neg)
    {
        bignum_t *ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t *ap4 = sum_bignum(ap1,ap3);
        bignum_free(ap3);
        return ap4;
    }

    /*-a - (-b) = -a+b */
    if (ap1->sign==neg && ap2->sign==neg)
    {
        bignum_t *r = copy_bignum(ap2);
        r->sign = pos;
        bignum_t *ap4 = sum_bignum(ap1,r);
        bignum_free(r);
        return ap4;
    }

    /*-a - (b)= -(a+b)   */
    if (ap1->sign==neg && ap2->sign==pos)
    {
        bignum_t *r = copy_bignum(ap1);
        r->sign = pos;
        bignum_t *ap3 = sum_bignum(r,ap2);
        ap3->sign = neg;
        bignum_free(r);
        return ap3;
    }

    /*want to subtract a lower number from a higher*/
    if (compare_bignum(ap1,ap2)==-1)
    {
        bignum_t *r = sub_bignum(ap2,ap1);
        if ((ap1->sign + ap2->sign == 2*pos) || (ap1->sign==zero && ap2->sign==pos))
        {
            r->sign = neg;
        }
        else if ((ap1->sign==zero && ap2->sign==neg))
        {
            r->sign = pos;
        }
        return r;
    }
    else
    {
        sign = ap1->sign;
    }
    /*assume |ap1| always more than |ap2| */
    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;
    unsigned int len = len1;

    bignum_add_zero(ap1,len-len1);
    bignum_add_zero(ap2,len-len2);

    bignum_t *ap = malloc(sizeof(*ap));
    if (!ap)
    {
        bignum_free(ap);
        return NULL;
    }
    ap->digits = calloc(len,sizeof(char));
    if (!ap->digits)
    {
        bignum_free(ap);
        return NULL;
    }
    int borrow = 0;
    int digit_sub ;

    for (size_t i=0; i<len; i++)
    {
        digit_sub  = (ap1->digits[i]) - (ap2->digits[i]) - borrow;
        if (digit_sub<0)
        {
            digit_sub+=10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        ap->digits[i] = digit_sub;      
    }

    ap->sign = sign;
    ap->len = len;
    remove_leading_zero(ap);
    return ap;
}

static void remove_leading_zero(bignum_t *ap)
{
    char* tmp;
    size_t old_len, new_len;

    old_len = new_len = ap->len;

    while ((new_len > 1) && (ap->digits[new_len - 1] == 0))
    {
        --new_len;
    }

    if (new_len != old_len) {
        tmp = realloc(ap->digits, sizeof(char) * new_len);
        if (!tmp) {
        return;
        }
        ap->digits = tmp;
        ap->len = new_len;
    }

    if ((new_len == 1) && (*ap->digits == 0))
    {
        ap->sign = zero;
    }
    return;
}

bignum_t *mult_bignum(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }
    int car,mul;
    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;
    bignum_t *ap = malloc(sizeof(*ap));
    ap->sign = ap1->sign * ap2->sign;
    char *tmp = calloc(len1+len2,sizeof(char));
    if (!ap || !tmp)
    {
        free(ap);
        free(tmp);
        return NULL;
    }

    ap->digits = tmp;
    ap->len = len1+len2;

    for (size_t i=0; i<len1; i++)
    {
        car = 0;
        for (size_t j=0; j<len2; j++)
        {
            mul = ap1->digits[i] * ap2->digits[j] + car + tmp[i+j];
            tmp[i+j] = mul % 10 ;
            car = mul / 10;
        }
        tmp[i+len2] += car; 
    }
    remove_leading_zero(ap);

    return ap;
}

bignum_t *div_bignum(bignum_t *ap1, bignum_t *ap2) {
    if (!ap1 || !ap2) return NULL;
    if (ap2->sign == zero) return NULL;
    if (compare_bignum(ap1, ap2) == -1 || ap1->sign == zero) {
        return bignum_zero();
    }
    if (ap2->sign == neg)
    {
        bignum_t *ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        bignum_t *ap4 = div_bignum(ap1,ap3);
        ap4->sign = ap1->sign * ap2->sign;
        bignum_free(ap3);
        return ap4;
    }
    bignum_t *quotient = bignum_zero();
    if (!quotient) return NULL;
    quotient->len = ap1->len;
    quotient->digits = calloc(quotient->len, sizeof(char));
    if (!quotient->digits) {
        bignum_free(quotient);
        return NULL;
    }

    bignum_t *current = bignum_zero();
    if (!current) {
        bignum_free(quotient);
        return NULL;
    }
    current->digits = calloc(ap1->len + 1, sizeof(char)); // Allocate enough space for shifts
    if (!current->digits)
    {
        bignum_free(current);
        bignum_free(quotient);
        return NULL;
    }
    current->len = 0;
    current->sign = pos;

    for (int i = ap1->len - 1; i >= 0; i--)
    {
        bignum_shl(current,1);

        current->digits[0] = ap1->digits[i];
        current->len++;

        remove_leading_zero(current);

        int count = 0;
        while (compare_bignum(current, ap2) >= 0) 
        {
            bignum_subtract(&current,ap2);
            count++;
        }
        quotient->digits[i] = count;
    }

    quotient->sign = ap1->sign * ap2->sign;
    remove_leading_zero(quotient);
    bignum_free(current);
    return quotient;
}


static void bignum_subtract(bignum_t **a, bignum_t *b)
{
    bignum_t *old;
    old = *a;
    *a = sub_bignum(*a, b);
    bignum_free(old);
}

bignum_t *mod_bignum(bignum_t *ap1, bignum_t *ap2)
{
    if (!ap1 || !ap2)
    {
        return NULL;
    }
    bignum_t *q = div_bignum(ap1,ap2);
    bignum_t *c = mult_bignum(ap2,q);
    bignum_t *r = sub_bignum(ap1,c);
    bignum_free(q);
    bignum_free(c);
    return r;
}


static void bignum_shl(bignum_t *x, size_t offset)
{
    if (x == NULL || offset == 0)
        return ;

    uint8_t *old = x->digits;
    uint8_t *tmp = calloc(x->len + offset, sizeof(*x->digits));
    if (tmp == NULL)
        return ;

    memcpy(tmp + offset, old, x->len);
    x->digits = tmp;
    x->len += offset;

    free(old);

    return ;
}