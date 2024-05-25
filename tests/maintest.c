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
    mu_assert_string_eq("1235456456213532156123513214", new_str);

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
    sign_t sign = pos;
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
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    
    mu_assert_string_eq("246", s1);
    mu_assert_string_eq("246", s2);

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));


    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_pospos2)
{
    bignum_t *a = from_str_to_bignum("95");
    bignum_t *b = from_str_to_bignum("10");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("105");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    mu_assert_string_eq("105", s1);
    mu_assert_string_eq("105", s2);

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_pospos3)
{
    bignum_t *a = from_str_to_bignum("1412461246142162462152165123156");
    bignum_t *b = from_str_to_bignum("2929912492146616154545461345444");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("4342373738288778616697626468600");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    
    mu_assert_string_eq("4342373738288778616697626468600", s1);
    mu_assert_string_eq("4342373738288778616697626468600", s2);

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_poszer1)
{
    bignum_t *a = from_str_to_bignum("000000");
    bignum_t *b = from_str_to_bignum("0");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("0");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    
    mu_assert_string_eq("0", s1);
    mu_assert_string_eq("0", s2);

    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_poszer2)
{
    bignum_t *a = from_str_to_bignum("132156123");
    bignum_t *b = from_str_to_bignum("0000000000000000");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("132156123");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    mu_assert_string_eq("132156123", s1);
    mu_assert_string_eq("132156123", s2);
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_negneg1)
{
    bignum_t *a = from_str_to_bignum("-123");
    bignum_t *b = from_str_to_bignum("-123");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-246");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    mu_assert_string_eq("-246", s1);
    mu_assert_string_eq("-246", s2);
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_negneg2)
{
    bignum_t *a = from_str_to_bignum("-95");
    bignum_t *b = from_str_to_bignum("-10");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-105");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    
    mu_assert_string_eq("-105", s1);
    mu_assert_string_eq("-105", s2);
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_negneg3)
{
    bignum_t *a = from_str_to_bignum("-1412461246142162462152165123156");
    bignum_t *b = from_str_to_bignum("-2929912492146616154545461345444");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-4342373738288778616697626468600");
    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);
    
    mu_assert_string_eq("-4342373738288778616697626468600", s1);
    mu_assert_string_eq("-4342373738288778616697626468600", s2);
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sum_negzer1)
{
    bignum_t *a = from_str_to_bignum("-132156123");
    bignum_t *b = from_str_to_bignum("0000000000000000");

    bignum_t *sum_left = sum_bignum(a, b);
    bignum_t *sum_right = sum_bignum(b, a);

    bignum_t *actual = from_str_to_bignum("-132156123");

    char *s1 = from_bignum_to_str(sum_left);
    char *s2 = from_bignum_to_str(sum_right);

    mu_assert_string_eq("-132156123", s1);
    mu_assert_string_eq("-132156123", s2);
    mu_check(is_equal_bignum(actual,sum_left));
    mu_check(is_equal_bignum(actual,sum_right));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sum_left);
    bignum_free(sum_right);
    bignum_free(actual);
    free(s1);
    free(s2);
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
    char *s = from_bignum_to_str(sub);
    mu_assert_string_eq("354", s);
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
    free(s);
}

MU_TEST(test_sub_poszer)
{
    bignum_t *a = from_str_to_bignum("465");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *sub = sub_bignum(a, b);
    bignum_t *actual = from_str_to_bignum("465"); 

    char *s = from_bignum_to_str(sub);
    mu_assert_string_eq("465", s);
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
    free(s);
}

MU_TEST(test_sub_negzer)
{
    bignum_t *a = from_str_to_bignum("-465");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *sub = sub_bignum(a, b);
    bignum_t *actual = from_str_to_bignum("-465"); 

    char *s = from_bignum_to_str(sub);

    mu_assert_string_eq("-465", s);
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
    free(s);
}

MU_TEST(test_sub_pospos2)
{
    bignum_t *a = from_str_to_bignum("456");
    bignum_t *b = from_str_to_bignum("450");
    bignum_t *sub = sub_bignum(a, b);

    bignum_t *actual = from_str_to_bignum("6"); 

    char *s1 = from_bignum_to_str(sub);

    mu_assert_string_eq("6", s1);
    mu_check(is_equal_bignum(actual,sub));
    bignum_free(a);
    bignum_free(b);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
}

MU_TEST(test_sub_1)
{
    bignum_t *a = from_str_to_bignum("12354");
    bignum_t *b = from_str_to_bignum("460");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("11894"); 
    bignum_t *actual2 = from_str_to_bignum("-11894"); 

    char *s1 = from_bignum_to_str(sub);
    char *s2 = from_bignum_to_str(sub2);

    mu_assert_string_eq("11894", s1);
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-11894", s2);
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sub_2)
{
    bignum_t *a = from_str_to_bignum("1000");
    bignum_t *b = from_str_to_bignum("1000");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("0"); 
    bignum_t *actual2 = from_str_to_bignum("0"); 
    char *s1 = from_bignum_to_str(sub);
    char *s2 = from_bignum_to_str(sub2);

    mu_assert_string_eq("0", s1);
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("0", s2);
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sub_3)
{
    bignum_t *a = from_str_to_bignum("-125");
    bignum_t *b = from_str_to_bignum("-13513212315");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b, a);
    
    bignum_t *actual = from_str_to_bignum("13513212190"); 
    bignum_t *actual2 = from_str_to_bignum("-13513212190"); 

    char *s1 = from_bignum_to_str(sub);
    char *s2 = from_bignum_to_str(sub2);

    mu_assert_string_eq("13513212190", s1);
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-13513212190", s2);
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sub_4)
{
    bignum_t *a = from_str_to_bignum("-125");
    bignum_t *b = from_str_to_bignum("456");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("-581"); 
    bignum_t *actual2 = from_str_to_bignum("581"); 

    char *s1 = from_bignum_to_str(sub);
    char *s2 = from_bignum_to_str(sub2);

    mu_assert_string_eq("-581", s1);
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("581", s2);
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
    free(s2);
}

MU_TEST(test_sub_5)
{
    bignum_t *a = from_str_to_bignum("0");
    bignum_t *b = from_str_to_bignum("-99");

    bignum_t *sub = sub_bignum(a, b);
    bignum_t *sub2 = sub_bignum(b,a);
    
    bignum_t *actual = from_str_to_bignum("99"); 
    bignum_t *actual2 = from_str_to_bignum("-99"); 

    char *s1 = from_bignum_to_str(sub);
    char *s2 = from_bignum_to_str(sub2);

    mu_assert_string_eq("99", s1);
    mu_check(is_equal_bignum(actual,sub));

    mu_assert_string_eq("-99", s2);
    mu_check(is_equal_bignum(actual2,sub2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(sub2);
    bignum_free(actual2);
    bignum_free(sub);
    bignum_free(actual);
    free(s1);
    free(s2);
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

MU_TEST(test_mult_by_zero)
{
    bignum_t *a = from_str_to_bignum("124562164");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *c = from_str_to_bignum("-124562164");

    bignum_t *mult1 = mult_bignum(a, b);
    bignum_t *mult2 = mult_bignum(b,c);
    
    bignum_t *actual = from_str_to_bignum("0"); 
    char *m1 = from_bignum_to_str(mult1);
    char *m2 = from_bignum_to_str(mult2);

    mu_assert_string_eq("0", m1);
    mu_check(is_equal_bignum(actual,mult1));

    mu_assert_string_eq("0", m2);
    mu_check(is_equal_bignum(actual,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual);
    free(m1);
    free(m2);
}

MU_TEST(test_mult_pospos)
{
    bignum_t *a = from_str_to_bignum("15");
    bignum_t *b = from_str_to_bignum("5");
    bignum_t *c = from_str_to_bignum("12");

    bignum_t *mult1 = mult_bignum(a, b);
    bignum_t *mult2 = mult_bignum(b,c);
    
    bignum_t *actual1 = from_str_to_bignum("75"); 
    bignum_t *actual2 = from_str_to_bignum("60"); 

    char *m1 = from_bignum_to_str(mult1);
    char *m2 = from_bignum_to_str(mult2);

    mu_assert_string_eq("75", m1);
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("60", m2);
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
    free(m1);
    free(m2);
}

MU_TEST(test_mult_posneg)
{
    bignum_t *a = from_str_to_bignum("1652");
    bignum_t *b = from_str_to_bignum("-123152");
    bignum_t *c = from_str_to_bignum("12312");

    bignum_t *mult1 = mult_bignum(a, b);
    bignum_t *mult2 = mult_bignum(b,c);
    
    bignum_t *actual1 = from_str_to_bignum("-203447104"); 
    bignum_t *actual2 = from_str_to_bignum("-1516247424"); 

    char *m1 = from_bignum_to_str(mult1);
    char *m2 = from_bignum_to_str(mult2);

    mu_assert_string_eq("-203447104", m1);
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("-1516247424", m2);
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
    free(m1);
    free(m2);
}

MU_TEST(test_mult_negneg)
{
    bignum_t *a = from_str_to_bignum("-114621646214612465");
    bignum_t *b = from_str_to_bignum("-21424562146524154621");
    bignum_t *c = from_str_to_bignum("-26142146214651243142134314");

    bignum_t *mult1 = mult_bignum(a, b);
    bignum_t *mult2 = mult_bignum(b,c);
    
    bignum_t *actual1 = from_str_to_bignum("2455718582661869875228766171253950765"); 
    bignum_t *actual2 = from_str_to_bignum("560084036219316741156080028368422104485764994");

    char *m1 =  from_bignum_to_str(mult1);
    char *m2 =  from_bignum_to_str(mult2);

    mu_assert_string_eq("2455718582661869875228766171253950765", m1);
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("560084036219316741156080028368422104485764994",m2);
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
    free(m1);
    free(m2);
}

MU_TEST_SUITE(suite_mul)
{
    MU_RUN_TEST(test_mult_by_zero);
    MU_RUN_TEST(test_mult_pospos);
    MU_RUN_TEST(test_mult_posneg);
    MU_RUN_TEST(test_mult_negneg);
}
/*
MU_TEST(test_div_by_zero)
{
    bignum_t *a = from_str_to_bignum("-114621646214612465");
    bignum_t *b = from_str_to_bignum("165165123123153");
    bignum_t *c = from_str_to_bignum("0");

    bignum_t *div1 = div_bignum_long(a,c);
    bignum_t *div2 = div_bignum_long(b,c);
    
    mu_assert_string_eq(NULL, from_bignum_to_str(div1));
    mu_check(NULL==div1);

    mu_assert_string_eq(NULL, from_bignum_to_str(div2));
    mu_check(NULL==div2);

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(div1);
    bignum_free(div2);
}

MU_TEST(test_div_pospos1)
{
    bignum_t *a = from_str_to_bignum("111");
    bignum_t *b = from_str_to_bignum("9");
    bignum_t *c = from_str_to_bignum("-9");

    bignum_t *div1 = div_bignum_long(a,b);
    bignum_t *div2 = div_bignum_long(a,c);

    bignum_t *actual1 = from_str_to_bignum("12");
    bignum_t *actual2 = from_str_to_bignum("-12");
    
    mu_assert_string_eq("12", from_bignum_to_str(div1));
    mu_check(is_equal_bignum(actual1,div1));

    mu_assert_string_eq("-12", from_bignum_to_str(div2));
    mu_check(is_equal_bignum(actual2,div2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(div1);
    bignum_free(div2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST(test_div_pospos2)
{
    bignum_t *a = from_str_to_bignum("125");
    bignum_t *b = from_str_to_bignum("25");
    bignum_t *c = from_str_to_bignum("-25");

    bignum_t *div1 = div_bignum_long(a,b);
    bignum_t *div2 = div_bignum_long(a,c);

    bignum_t *actual1 = from_str_to_bignum("5");
    bignum_t *actual2 = from_str_to_bignum("-5");
    
    mu_assert_string_eq("5", from_bignum_to_str(div1));
    mu_check(is_equal_bignum(actual1,div1));

    mu_assert_string_eq("-5", from_bignum_to_str(div2));
    mu_check(is_equal_bignum(actual2,div2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(div1);
    bignum_free(div2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST(test_div_pospos3)
{
    bignum_t *a = from_str_to_bignum("16515612156123162");
    bignum_t *b = from_str_to_bignum("51612231");
    bignum_t *c = from_str_to_bignum("-51612231");

    bignum_t *div1 = div_bignum_long(a,b);
    bignum_t *div2 = div_bignum_long(a,c);

    bignum_t *actual1 = from_str_to_bignum("319994153");
    bignum_t *actual2 = from_str_to_bignum("-319994153");
    
    mu_assert_string_eq("319994153", from_bignum_to_str(div1));
    mu_check(is_equal_bignum(actual1,div1));

    mu_assert_string_eq("-319994153", from_bignum_to_str(div2));
    mu_check(is_equal_bignum(actual2,div2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(div1);
    bignum_free(div2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST(test_div_pospos4)
{
    bignum_t *a = from_str_to_bignum("10000000000000000000000000000");
    bignum_t *b = from_str_to_bignum("10");
    bignum_t *c = from_str_to_bignum("-15");

    bignum_t *div1 = div_bignum_long(a,b);
    bignum_t *div2 = div_bignum_long(a,c);

    bignum_t *actual1 = from_str_to_bignum("1000000000000000000000000000");
    bignum_t *actual2 = from_str_to_bignum("-666666666666666666666666666");
    
    mu_assert_string_eq("1000000000000000000000000000", from_bignum_to_str(div1));
    mu_check(is_equal_bignum(actual1,div1));

    mu_assert_string_eq("-666666666666666666666666666", from_bignum_to_str(div2));
    mu_check(is_equal_bignum(actual2,div2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(div1);
    bignum_free(div2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST_SUITE(suite_div)
{
    MU_RUN_TEST(test_div_by_zero);
    MU_RUN_TEST(test_div_pospos1);
    MU_RUN_TEST(test_div_pospos2);
    MU_RUN_TEST(test_div_pospos3);
    MU_RUN_TEST(test_div_pospos4);
}
MU_TEST(test_mod_pospos)
{
    bignum_t *a = from_str_to_bignum("15623");
    bignum_t *b = from_str_to_bignum("465");
    bignum_t *c = from_str_to_bignum("12");

    bignum_t *mod1 = mod_bignum(a,b);
    bignum_t *mod2 = mod_bignum(a,c);

    bignum_t *actual1 = from_str_to_bignum("278");
    bignum_t *actual2 = from_str_to_bignum("11");
    
    mu_assert_string_eq("278", from_bignum_to_str(mod1));
    mu_check(is_equal_bignum(actual1,mod1));

    mu_assert_string_eq("11", from_bignum_to_str(mod2));
    mu_check(is_equal_bignum(actual2,mod2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mod1);
    bignum_free(mod2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST(test_mod_posneg)
{
    bignum_t *a = from_str_to_bignum("15623");
    bignum_t *b = from_str_to_bignum("-465");
    bignum_t *c = from_str_to_bignum("-12");

    bignum_t *mod1 = mod_bignum(a,b);
    bignum_t *mod2 = mod_bignum(a,c);

    bignum_t *actual1 = from_str_to_bignum("278");
    bignum_t *actual2 = from_str_to_bignum("11");
    
    mu_assert_string_eq("278", from_bignum_to_str(mod1));
    mu_check(is_equal_bignum(actual1,mod1));

    mu_assert_string_eq("11", from_bignum_to_str(mod2));
    mu_check(is_equal_bignum(actual2,mod2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mod1);
    bignum_free(mod2);
    bignum_free(actual1);
    bignum_free(actual2);
}
MU_TEST_SUITE(suite_mod)
{
    MU_RUN_TEST(test_mod_pospos);
    MU_RUN_TEST(test_mod_posneg);

}
*/
int main(int argc, char *argv[])
{
    
    MU_RUN_SUITE(suite_str);
    MU_RUN_SUITE(suite_sum);
    MU_RUN_SUITE(suite_sub);
    MU_RUN_SUITE(suite_mul);
    /*MU_RUN_SUITE(suite_div);
    MU_RUN_SUITE(suite_mod);*/
    MU_REPORT();


    return MU_EXIT_CODE;
}