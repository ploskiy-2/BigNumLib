#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include <bignum.h>

char *str_without_lead_zero (char *str, uint8_t len){
    int i = 0;
    while (i < len && str[i] == '0') {
        i++;
    }
    for (int j = 0; i + j < len; j++) {
        str[j] = str[i + j];
    }
    str[len - i] = '\0';
    return str;
}

void bignum_free(bignum_t *ap){
    if (ap){
        free(ap->digits);
        free(ap);
    }
}

bignum_t *bignum_zero(){
    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        bignum_free(ap);
        return NULL;
    }
    ap->sign = zero;
    ap->len = 1;
    ap->digits = malloc(2*sizeof(char)); 
    if (!ap->digits) {
        bignum_free(ap);
        return NULL; 
    }
    ap->digits[0] = '0';
    ap->digits[1] = '\0';
    return ap;

}

bignum_t *from_str_to_bignum (char *str){
    if (!str || strlen(str)==0){
        return NULL;
    }

    bignum_t *ap = malloc(sizeof(bignum_t));
    if (!ap){
        return NULL;
    }

    int8_t sign;
    unsigned int len = strlen(str);

    if (*str=='-'){
        sign = neg;
        str++;
        len--;}
    else if (*str=='0' && len==1){
        return bignum_zero();}
    else if(*str=='+'){
        sign = pos;
        str++;
        len--;
        }
    char *new_str = str_without_lead_zero(str, len);
    len = strlen(new_str);

    if (len==0){
        return bignum_zero();}
   
    ap->digits = malloc((len+1) * sizeof(char));

    if (!ap || !ap->digits || !len) {
        bignum_free(ap);
        free(new_str);
        return NULL;
    }

    int ch_cnt = 0;
    for (int i=0; i<len; i++){
        char t = new_str[len-1-i];
        /*we want from "123SAKOD123 --> 123123"*/
        if (isdigit(t)){
            ap->digits[ch_cnt] = t;
            ch_cnt++;
        }
    }
    ap->digits[ch_cnt] = '\0';
    ap->len = ch_cnt;
    if (!sign){
        sign=pos;
    }
    ap->sign = sign; 

    free(new_str);
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
        bignum_free(ap);
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
        free(str);
        return NULL;
    }

    if (sign==neg){
        str[0]='-';
    }
    else if(sign==pos){
        str[0]='+';
    }

    for (int i=1; i<=len; i++){
        str[i] = ap->digits[len-i];       
    }

    str[len+1] = '\0';
    bignum_free(ap);

    if (sign==pos){
        return str_without_plus(str);
    }
    return str;
}