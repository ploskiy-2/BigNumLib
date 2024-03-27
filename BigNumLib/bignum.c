#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include <bignum.h>

void bignum_free(bignum_t *ap){
    if (ap){
        free(ap->digits);
        free(ap);
    }
    return;
}

bignum_t *bignum_zero(){
    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        bignum_free(ap);
        return NULL;
    }
    ap->sign = zero;
    ap->len = 1;
    ap->digits = malloc(sizeof(char)); 
    if (!ap->digits) {
        bignum_free(ap);
        return NULL; 
    }
    ap->digits[0] = '0'-'0';
    return ap;

}

bignum_t *from_str_to_bignum (char *str){
    if (!str || strlen(str)==0){
        return NULL;
    }

    int8_t sign = pos;
    int len = strlen(str);
    
    if (*str=='-'){
        sign = neg;
        str++;
        len--;}
    else if (*str=='0' && len==1){
        return bignum_zero();}
    else if(*str=='+'){
        sign = pos;
        str++;
        len--;}
    while ((len>0) && *str=='0'){
        str++;
        len--;
    }
    
    if (len==0){
        return bignum_zero();}
        
    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }

    ap->digits = calloc(len,sizeof(char));    

    if (!ap->digits) {
        bignum_free(ap);
        return NULL;
    }
    ap->sign = sign;
    int ch_cnt = 0;
    for (int i=0; i<len; i++){
        char t = str[len-1-i];
        /*we want from "123SAKOD123 --> 123123"*/
        if (isdigit(t)){
            ap->digits[ch_cnt] = t-'0';
            ch_cnt++;
        }
    }
    ap->len = ch_cnt;

    return ap;
}

char *str_without_plus(char *str){
    int j = 0;
    int len=strlen(str);
    char *new_str = calloc(len-1,sizeof(char));
    if (!new_str){
        return NULL;
    }
    for (int i=1; i<len+1;i++){
        new_str[j]=str[i];
        j++;
    }
    return new_str;
}

char *from_bignum_to_str(bignum_t *ap){
    if (!ap){
        return NULL;
    }

    int8_t sign = ap->sign;
    unsigned int len = ap->len;

    if (sign==zero && len==1){
        char *res = malloc(2*sizeof(char));
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    char *str = calloc(len+2,sizeof(char));

    if (!str){
        return NULL;
    }

    if (sign==neg){
        *str = '-';
    }
    else if(sign==pos){
        *str = '+';
    }

    for (int i=1; i<=len; i++){
        str[i] = ap->digits[len-i] + '0';       
    }

    str[len+1] = '\0';

    if (sign==pos){
        return str_without_plus(str);
    }
    return str;
}
void bignum_add_zero(bignum_t *ap, uint8_t t) {
    if (!ap) {
        return;
    }
    ap->digits = realloc(ap->digits, sizeof(char) * (ap->len + t));
    memset(ap->digits + ap->len, 0, t);

    ap->len += t;
    return;
}
bignum_t *sum_bignum(bignum_t *ap1, bignum_t *ap2){
    if(!ap1 || !ap2){
        return NULL;
    }
    int8_t sign = pos;

    if (((ap1->sign==neg)&&(ap2->sign==neg))||((ap1->sign==neg)||(ap2->sign==neg))&&((ap1->sign==zero)||(ap2->sign==zero)) ){
        sign=neg;
    }
    if ((ap1->sign==zero)&&(ap2->sign==zero)){
        sign=zero;
    }
    if ((ap1->sign==neg)&&(ap2->sign==pos)){
        bignum_t *ap3 = copy_bignum(ap1);
        ap3->sign = pos;
        return sub_bignum(ap2,ap3);
    }
    if ((ap1->sign==pos)&&(ap2->sign==neg)){
        bignum_t *ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        return sub_bignum(ap1,ap3);
    }

    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;
    unsigned int len = (len1 > len2) ? len1 : len2;

    bignum_add_zero(ap1,len-len1);
    bignum_add_zero(ap2,len-len2);

    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }

    ap->digits = calloc(len+1,sizeof(char));
    if(!ap->digits){
        return NULL;
    }

    int car = 0;
    int dig;
    int digit_sum ;

    for (int i=0; i<len; i++){
        digit_sum = car;
        digit_sum  += (ap1->digits[i]) + (ap2->digits[i]);
        dig = digit_sum%10; 
        car = digit_sum/10;

        ap->digits[i] = dig;      
    }
    if (car > 0) { 
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
    for (int i=0;i<ap1->len;i++){
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
        for (int i = 0; i < ap1->len; i++) {
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

bignum_t *copy_bignum(bignum_t *ap){
    if (!ap){
        return NULL;
    }
    bignum_t *new_ap = malloc(sizeof(bignum_t));
    new_ap->sign = ap->sign;
    new_ap->len = ap->len;
    new_ap->digits = calloc(ap->len,sizeof(char));
    if (!new_ap->digits || !ap->digits){
        return NULL;
    }
    for (int i = 0; i < ap->len; i++) {
        new_ap->digits[i] = ap->digits[i];
    }
    return new_ap;
}

bignum_t *sub_bignum(bignum_t *ap1, bignum_t *ap2){
    if(!ap1 || !ap2){
        return NULL;
    }
    int8_t sign;

    /*a - (-b) = a+b */
    if (ap1->sign==pos && ap2->sign==neg){
        bignum_t *ap3 = copy_bignum(ap2);
        ap3->sign = pos;
        return sum_bignum(ap1,ap3);
    }

    /*-a - (-b) = -a+b */
    if (ap1->sign==neg && ap2->sign==neg){
        bignum_t *r = copy_bignum(ap2);
        r->sign = pos;
        return sum_bignum(ap1,r);}

    /*-a - (b)= -(a+b)   */
    if (ap1->sign==neg && ap2->sign==pos){
        bignum_t *r = copy_bignum(ap1);
        r->sign = pos;
        bignum_t *ap3 = sum_bignum(r,ap2);
        ap3->sign = neg;
        return ap3;
    }

    /*want to subtract a lower number from a higher*/
    if (compare_bignum(ap1,ap2)==-1){
        bignum_t *r = sub_bignum(ap2,ap1);
        if((ap1->sign==ap2->sign && ap2->sign==pos) || (ap1->sign==zero && ap2->sign==pos) ){
        r->sign = neg;}
        else if ((ap1->sign==zero && ap2->sign==neg)){
            r->sign = pos;
        }
        return r;

    }
    else{
        sign = ap1->sign;
    }
    /*assume |ap1| always more than |ap2| */
    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;
    unsigned int len = len1;

    bignum_add_zero(ap1,len-len1);
    bignum_add_zero(ap2,len-len2);

    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }

    ap->digits = calloc(len,sizeof(char));
    if(!ap->digits){
        return NULL;
    }

    int borrow = 0;
    int digit_sub ;

    for (int i=0; i<len; i++){
        digit_sub  = (ap1->digits[i]) - (ap2->digits[i]) - borrow;
        if (digit_sub<0){
            digit_sub+=10;
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        ap->digits[i] = digit_sub;      
    }

    ap->sign = sign;
    ap->len = len;


    remove_leading_zero_from_dig(ap);

    return ap;
}

void remove_leading_zero_from_dig(bignum_t *ap){
    char* tmp;
    size_t old_len, new_len;

    old_len = new_len = ap->len;

    while ((new_len > 1) && (ap->digits[new_len - 1] == 0)) {
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

    if ((new_len == 1) && (*ap->digits == 0)) {
        ap->sign = zero;
    }
    return;
}

bignum_t *mult_bignum(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }

    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }

    ap->sign = ap1->sign * ap2->sign;

    unsigned int len1 = ap1->len;
    unsigned int len2 = ap2->len;


    char *tmp = calloc(len1+len2,sizeof(char));
    if (!tmp){
        return NULL;
    }

    ap->digits = tmp;
    ap->len = len1+len2;
    int car;
    int mul;

    for (int i=0; i<len1; i++){
        car = 0;
        for (int j=0; j<len2; j++){
            mul = ap1->digits[i] * ap2->digits[j] + car + tmp[i+j];
            tmp[i+j] = mul % 10 ;
            car = mul / 10;
        }
        tmp[i+len2] += car; 
    }
    remove_leading_zero_from_dig(ap);

    return ap;
}

bignum_t *div_bignum(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }
    /*forbid div by zero*/
    if (is_equal_bignum(ap2,bignum_zero())){
        return NULL;
    }
    /*if ap2 is a single digit*/
    if (ap2->len==1 && ap2->digits[0]==1){
        bignum_t *r = copy_bignum(ap1);
        r->sign = ap1->sign * ap2->sign;
        return r;
    }

    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }
    ap->sign = ap1->sign * ap2->sign;


    return bignum_zero();

}

bignum_t *est_q(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }
    int res_q = (ap1->digits[ap1->len - 1]*10 + ap1->digits[ap1->len - 2])/ap2->digits[ap2->len - 1];
    char *s_res_q[2];
    sprintf(s_res_q, "%d", res_q);
    return from_str_to_bignum(s_res_q);
 }

bignum_t *norm_q(bignum_t *ap1, bignum_t *ap2){
    if (!ap1 || !ap2){
        return NULL;
    }
    bignum_t *tw = from_str_to_bignum("2");
    if (ap2->digits[ap2->len - 1]<5){
    bignum_t *n = mult_bignum(ap1,tw);
    bignum_t *v = mult_bignum(ap2,tw);
    return est_q(n,v);
    }
    return est_q(ap1,ap2);

 }