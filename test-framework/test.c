#include "unity.h"
#include "../src/ecu_parser.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_check_identifier_type()
{
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE_STANDARD, ckeck_identifier_type(0x700));
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE_EXTENDED, ckeck_identifier_type(0xCF00400));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_check_identifier_type);

    UNITY_END();

    return 0;
}
