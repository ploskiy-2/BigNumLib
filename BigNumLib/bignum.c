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

    ap->digits = malloc(len * sizeof(char));    

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
    char *new_str = malloc((len-1)*sizeof(char));
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

    char *str = malloc((len+2)*sizeof(char));

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

bignum_t *sum_bignum(bignum_t *ap1, bignum_t *ap2){
    if(!ap1 || !ap2){
        return NULL;
    }
    unsigned int len = ap1->len;
    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        bignum_free(ap);
        return NULL;
    }
    
    ap->digits = malloc((len)*sizeof(char));
    if(!ap->digits){
        bignum_free(ap);
        return NULL;
    }
    int car = 0;
    int dig = 0;
    for (int i=0; i<len; i++){
        dig = (ap1->digits[i]+ap2->digits[i] + car)%10; 
        car = dig/10;
    }
    ap->sign = pos;
    
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