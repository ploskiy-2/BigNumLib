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


MU_TEST(test_mult_by_zero)
{
    bignum_t *a = from_str_to_bignum("124562164");
    bignum_t *b = from_str_to_bignum("0");
    bignum_t *c = from_str_to_bignum("-124562164");

    bignum_t *mult1 = mult_bignum(a, b);
    bignum_t *mult2 = mult_bignum(b,c);
    
    bignum_t *actual = from_str_to_bignum("0"); 

    mu_assert_string_eq("0", from_bignum_to_str(mult1));
    mu_check(is_equal_bignum(actual,mult1));

    mu_assert_string_eq("0", from_bignum_to_str(mult2));
    mu_check(is_equal_bignum(actual,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual);
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

    mu_assert_string_eq("75", from_bignum_to_str(mult1));
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("60", from_bignum_to_str(mult2));
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
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

    mu_assert_string_eq("-203447104", from_bignum_to_str(mult1));
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("-1516247424", from_bignum_to_str(mult2));
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
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

    mu_assert_string_eq("2455718582661869875228766171253950765", from_bignum_to_str(mult1));
    mu_check(is_equal_bignum(actual1,mult1));

    mu_assert_string_eq("560084036219316741156080028368422104485764994", from_bignum_to_str(mult2));
    mu_check(is_equal_bignum(actual2,mult2));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(mult1);
    bignum_free(mult2);
    bignum_free(actual1);
    bignum_free(actual2);
}

MU_TEST_SUITE(suite_mul)
{
    MU_RUN_TEST(test_mult_by_zero);
    MU_RUN_TEST(test_mult_pospos);
    MU_RUN_TEST(test_mult_posneg);
    MU_RUN_TEST(test_mult_negneg);

}
MU_TEST(test_div_by_zero)
{
    bignum_t *a = from_str_to_bignum("-114621646214612465");
    bignum_t *b = from_str_to_bignum("165165123123153");
    bignum_t *c = from_str_to_bignum("0");

    bignum_t *div1 = div_bignum(a,c);
    bignum_t *div2 = div_bignum(b,c);
    
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

    bignum_t *div1 = div_bignum(a,b);
    bignum_t *div2 = div_bignum(a,c);

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
MU_TEST(test_div_est_q1)
{
    bignum_t *a = from_str_to_bignum("2356");
    bignum_t *b = from_str_to_bignum("395");
    bignum_t *c = from_str_to_bignum("7");

    bignum_t *q = est_q(a,b);
 
    mu_assert_string_eq("7", from_bignum_to_str(q));
    mu_check(is_equal_bignum(q,c));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(q);
}
MU_TEST(test_div_est_q2)
{
    bignum_t *a = from_str_to_bignum("9446124561246124321");
    bignum_t *b = from_str_to_bignum("76521765");
    bignum_t *c = from_str_to_bignum("13");

    bignum_t *q = est_q(a,b);
 
    mu_assert_string_eq("13", from_bignum_to_str(q));
    mu_check(is_equal_bignum(q,c));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(q);
}
MU_TEST(test_div_norm_q1)
{
    bignum_t *a = from_str_to_bignum("192");
    bignum_t *b = from_str_to_bignum("29");
    bignum_t *c = from_str_to_bignum("7");

    bignum_t *q = norm_q(a,b);
 
    mu_assert_string_eq("7", from_bignum_to_str(q));
    mu_check(is_equal_bignum(q,c));

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    bignum_free(q);
}
MU_TEST(test_div_pospos2)
{
    bignum_t *a = from_str_to_bignum("125");
    bignum_t *b = from_str_to_bignum("25");
    bignum_t *c = from_str_to_bignum("-25");

    bignum_t *div1 = div_bignum(a,b);
    bignum_t *div2 = div_bignum(a,c);

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

    bignum_t *div1 = div_bignum(a,b);
    bignum_t *div2 = div_bignum(a,c);

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

    bignum_t *div1 = div_bignum(a,b);
    bignum_t *div2 = div_bignum(a,c);

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
    MU_RUN_TEST(test_div_est_q1);
    MU_RUN_TEST(test_div_est_q2);
    MU_RUN_TEST(test_div_norm_q1);
    MU_RUN_TEST(test_div_pospos2);
    MU_RUN_TEST(test_div_pospos3);
    MU_RUN_TEST(test_div_pospos4);
}
int main(int argc, char *argv[])
{
    
    MU_RUN_SUITE(suite_str);
    MU_RUN_SUITE(suite_sum);
    MU_RUN_SUITE(suite_sub);
    MU_RUN_SUITE(suite_mul);
    MU_RUN_SUITE(suite_div);
    MU_REPORT();


    return MU_EXIT_CODE;
}