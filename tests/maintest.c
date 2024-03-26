#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "bignum.h"
#include "minunit.h"
MU_TEST(test_str_neg1)
{
    char *str = "-12345";
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);
  
    mu_check(ap->sign == neg);
    mu_check(ap->len == (strlen(str)-1));    
    mu_assert_string_eq(str, new_str);

    bignum_free(ap);
    free(new_str);
}
MU_TEST(test_str_neg2)
{
    char str[] = "-124652131512135461235613345";
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->sign == neg);
    mu_check(ap->len == (strlen(str)-1));
    mu_assert_string_eq(str, new_str);

    bignum_free(ap);
    free(new_str);
}
MU_TEST(test_str_neg3)
{
    char str[] = "-100000000000000000000000000000000000000000000000000000";
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);
    
    mu_check(ap->sign == neg);
    mu_check(ap->len == (strlen(str)-1));
    mu_assert_string_eq(str, new_str);

    bignum_free(ap);
    free(new_str);
}

MU_TEST(test_str_zero1)
{
    char str[] = "0";
    int8_t sign = zero;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == 1);
    mu_check(ap->sign == sign);
    mu_assert_string_eq(str, new_str);

    bignum_free(ap);
    free(new_str);
}

MU_TEST(test_str_zero2)
{
    char str[] = "0000000000000000000000000000000000";
    int8_t sign = zero;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == 1);
    mu_check(ap->sign == sign);
    mu_assert_string_eq("0", new_str);

    bignum_free(ap);
    free(new_str);
}
MU_TEST(test_str_zero3)
{
    char str[] = "-0000000000000000000000000000000000";
    int8_t sign = zero;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == 1);
    mu_check(ap->sign == sign);
    mu_assert_string_eq("0", new_str);

    bignum_free(ap);
    free(new_str);
}


MU_TEST(test_str_pos1)
{
    char str[] = "+1235456456213532156123513214";
    int8_t sign = pos;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == (strlen(str)-1));
    mu_check(ap->sign == sign);
    mu_assert_string_eq(str_without_plus(str), new_str);

    bignum_free(ap);
    free(new_str);
}

MU_TEST(test_str_pos2)
{
    char str[] = "+000";
    int8_t sign = zero;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == 1);
    mu_check(ap->sign == sign);
    mu_assert_string_eq("0", new_str);

    bignum_free(ap);
    free(new_str);
}

MU_TEST(test_str_pos3)
{
    char str[] = "1426521456124651246512465142323425641246124311243124145234523462";
    int8_t sign = pos;
    bignum_t *ap = from_str_to_bignum(str);
    char *new_str = from_bignum_to_str(ap);

    mu_check(ap->len == strlen(str));
    mu_check(ap->sign == sign);
    mu_assert_string_eq(str, new_str);

    bignum_free(ap);
    free(new_str);
}


MU_TEST_SUITE(suite_str)
{
    MU_RUN_TEST(test_str_neg1);
    MU_RUN_TEST(test_str_neg2);
    MU_RUN_TEST(test_str_neg3);
    MU_RUN_TEST(test_str_zero1);
    MU_RUN_TEST(test_str_zero2);
    MU_RUN_TEST(test_str_zero3);
    MU_RUN_TEST(test_str_pos1);
    MU_RUN_TEST(test_str_pos2);
    MU_RUN_TEST(test_str_pos3);
}

MU_TEST(test_sum_pospos1)
{
    bignum_t *a = from_str_to_bignum("123");
    bignum_t *b = from_str_to_bignum("123");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("246");
    
    mu_assert_string_eq("246", from_bignum_to_str(sum_left));
    mu_assert_string_eq("246", from_bignum_to_str(sum_right));

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));


    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_pospos2)
{
    bignum_t *a = from_str_to_bignum("95");
    bignum_t *b = from_str_to_bignum("10");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("105");
    
    mu_assert_string_eq("105", from_bignum_to_str(sum_left));
    mu_assert_string_eq("105", from_bignum_to_str(sum_right));

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_pospos3)
{
    bignum_t *a = from_str_to_bignum("1412461246142162462152165123156");
    bignum_t *b = from_str_to_bignum("2929912492146616154545461345444");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("4342373738288778616697626468600");
    
    mu_assert_string_eq("4342373738288778616697626468600", from_bignum_to_str(sum_left));
    mu_assert_string_eq("4342373738288778616697626468600", from_bignum_to_str(sum_right));

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_poszer1)
{
    bignum_t *a = from_str_to_bignum("000000");
    bignum_t *b = from_str_to_bignum("0");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("0");
    
    mu_assert_string_eq("0", from_bignum_to_str(sum_left));
    mu_assert_string_eq("0", from_bignum_to_str(sum_right));

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_poszer2)
{
    bignum_t *a = from_str_to_bignum("132156123");
    bignum_t *b = from_str_to_bignum("0000000000000000");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("132156123");
    
    mu_assert_string_eq("132156123", from_bignum_to_str(sum_left));
    mu_assert_string_eq("132156123", from_bignum_to_str(sum_right));
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}
MU_TEST(test_sum_negneg1)
{
    bignum_t *a = from_str_to_bignum("-123");
    bignum_t *b = from_str_to_bignum("-123");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-246");
    
    mu_assert_string_eq("-246", from_bignum_to_str(sum_left));
    mu_assert_string_eq("-246", from_bignum_to_str(sum_right));
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_negneg2)
{
    bignum_t *a = from_str_to_bignum("-95");
    bignum_t *b = from_str_to_bignum("-10");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-105");
    
    mu_assert_string_eq("-105", from_bignum_to_str(sum_left));
    mu_assert_string_eq("-105", from_bignum_to_str(sum_right));
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}

MU_TEST(test_sum_negneg3)
{
    bignum_t *a = from_str_to_bignum("-1412461246142162462152165123156");
    bignum_t *b = from_str_to_bignum("-2929912492146616154545461345444");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-4342373738288778616697626468600");
    
    mu_assert_string_eq("-4342373738288778616697626468600", from_bignum_to_str(sum_left));
    mu_assert_string_eq("-4342373738288778616697626468600", from_bignum_to_str(sum_right));
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}
MU_TEST(test_sum_negzer1)
{
    bignum_t *a = from_str_to_bignum("-132156123");
    bignum_t *b = from_str_to_bignum("0000000000000000");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-132156123");
    
    mu_assert_string_eq("-132156123", from_bignum_to_str(sum_left));
    mu_assert_string_eq("-132156123", from_bignum_to_str(sum_right));
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
}
MU_TEST_SUITE(suite_sum)
{
    /*here test sum for:
    pos + pos
    zero + pos
    neg + neg
    */
    MU_RUN_TEST(test_sum_pospos1);
    MU_RUN_TEST(test_sum_pospos2);
    MU_RUN_TEST(test_sum_pospos3);
    MU_RUN_TEST(test_sum_poszer1);
    MU_RUN_TEST(test_sum_poszer2);
    MU_RUN_TEST(test_sum_negneg1);
    MU_RUN_TEST(test_sum_negneg2);
    MU_RUN_TEST(test_sum_negneg3);
    MU_RUN_TEST(test_sum_negzer1);
}

MU_TEST(test_sub_pospos1)
{
    bignum_t *a = from_str_to_bignum("465");
    bignum_t *b = from_str_to_bignum("111");
    bignum_t *sub = sub_bignum(a, b);
    bignum_t *actual = from_str_to_bignum("354"); 

    mu_assert_string_eq("354", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_poszer)
{
    bignum_t *a = from_str_to_bignum("465");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *sub = sub_bignum(a, b);
    bignum_t *actual = from_str_to_bignum("465"); 

    mu_assert_string_eq("465", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_negzer)
{
    bignum_t *a = from_str_to_bignum("-465");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *sub = sub_bignum(a, b);
    bignum_t *actual = from_str_to_bignum("-465"); 

    mu_assert_string_eq("-465", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_pospos2)
{
    bignum_t *a = from_str_to_bignum("456");
    bignum_t *b = from_str_to_bignum("450");
    bignum_t *sub = sub_bignum(a, b);

    bignum_t *actual = from_str_to_bignum("6"); 

    mu_assert_string_eq("6", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_1)
{
    bignum_t *a = from_str_to_bignum("12354");
    bignum_t *b = from_str_to_bignum("460");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("11894"); 
    bignum_t *actual2 = from_str_to_bignum("-11894"); 

    mu_assert_string_eq("11894", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-11894", from_bignum_to_str(sub2));
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_2)
{
    bignum_t *a = from_str_to_bignum("1000");
    bignum_t *b = from_str_to_bignum("1000");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("0"); 
    bignum_t *actual2 = from_str_to_bignum("0"); 

    mu_assert_string_eq("0", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("0", from_bignum_to_str(sub2));
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_3)
{
    bignum_t *a = from_str_to_bignum("-125");
    bignum_t *b = from_str_to_bignum("-13513212315");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("13513212190"); 
    bignum_t *actual2 = from_str_to_bignum("-13513212190"); 

    mu_assert_string_eq("13513212190", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-13513212190", from_bignum_to_str(sub2));
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST(test_sub_4)
{
    bignum_t *a = from_str_to_bignum("-125");
    bignum_t *b = from_str_to_bignum("456");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("-581"); 
    bignum_t *actual2 = from_str_to_bignum("581"); 

    mu_assert_string_eq("-581", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("581", from_bignum_to_str(sub2));
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
}


MU_TEST(test_sub_5)
{
    bignum_t *a = from_str_to_bignum("0");
    bignum_t *b = from_str_to_bignum("-99");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("99"); 
    bignum_t *actual2 = from_str_to_bignum("-99"); 

    mu_assert_string_eq("99", from_bignum_to_str(sub));
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-99", from_bignum_to_str(sub2));
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
}

MU_TEST_SUITE(suite_sub)
{
    MU_RUN_TEST(test_sub_pospos1);
    MU_RUN_TEST(test_sub_poszer);
    MU_RUN_TEST(test_sub_negzer);
    MU_RUN_TEST(test_sub_pospos2);
    MU_RUN_TEST(test_sub_1);
    MU_RUN_TEST(test_sub_2);
    MU_RUN_TEST(test_sub_3);
    MU_RUN_TEST(test_sub_4);
    MU_RUN_TEST(test_sub_5);
}


int main(int argc, char *argv[])
{
    
    MU_RUN_SUITE(suite_str);
    MU_RUN_SUITE(suite_sum);
    MU_RUN_SUITE(suite_sub);
    MU_REPORT();


    return MU_EXIT_CODE;
}