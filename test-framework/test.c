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
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE_STANDARD, check_identifier_type(0x700));
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE_EXTENDED, check_identifier_type(0xCF00400));
}

void test_get_obd2_frame_details_successfully()
{
    obd2_frame_details_t expected = {0x7E8, 0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA};
    uint8_t input_data[] = {0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA};
    uint32_t input_identifier = 0x7E8;
    obd2_frame_details_t actual;
    int result = get_obd2_frame_details(input_identifier, input_data, 8, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(actual.data_bytes, expected.data_bytes, 5);
    TEST_ASSERT_EQUAL_UINT8(actual.length, expected.length);
    TEST_ASSERT_EQUAL_UINT8(actual.mode, expected.mode);
    TEST_ASSERT_EQUAL_UINT8(actual.pid, expected.pid);
    TEST_ASSERT_EQUAL_UINT32(actual.identifier, expected.identifier);
}

void test_get_obd2_frame_details_unsuccessfully()
{
    uint8_t input_data[] = {0x03, 0x41, 0x0D};
    uint32_t input_identifier = 0x7E8;
    obd2_frame_details_t actual;
    int result = get_obd2_frame_details(input_identifier, input_data, 3, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}

void test_find_protocol_obd2_successfully()
{

    uint8_t input_data[] = {0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA};
    uint32_t input_identifier = 0x7E8;
    application_layer_protocol_t actual = APPLICATION_LAYER_PROTOCOL_UNKNOWN;
    application_layer_protocol_t expected = APPLICATION_LAYER_PROTOCOL_OBD2;
    int result = find_protocol(input_identifier, input_data, 8, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_get_uds_frame_details_successfully()
{
    uds_frame_details_t expected = {0x7EC, 0x03, 0x7F, 0x22, 0x13};
    uint8_t input_data[] = {0x03, 0x7F, 0x22, 0x13};
    uint32_t input_identifier = 0x7EC;
    uds_frame_details_t actual;
    int result = get_uds_frame_details(input_identifier, input_data, 4, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_UINT8(actual.service_id, expected.service_id);
    TEST_ASSERT_EQUAL_UINT8(actual.sub_function, expected.sub_function);
    TEST_ASSERT_EQUAL_UINT8(actual.protocol_control_information, expected.protocol_control_information);
    TEST_ASSERT_EQUAL_UINT32(actual.identifier, expected.identifier);
}

void test_get_uds_frame_details_unsuccessfully()
{

    uint8_t input_data[] = {0x03, 0x7F, 0x22};
    uint32_t input_identifier = 0x7EC;
    uds_frame_details_t actual;
    int result = get_uds_frame_details(input_identifier, input_data, 3, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}

void test_find_protocol_uds_successfully()
{

    uint8_t input_data[] = {0x03, 0x7F, 0x22, 0x13};
    uint32_t input_identifier = 0x7E8;
    application_layer_protocol_t actual = APPLICATION_LAYER_PROTOCOL_UNKNOWN;
    application_layer_protocol_t expected = APPLICATION_LAYER_PROTOCOL_UDS;
    int result = find_protocol(input_identifier, input_data, 8, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_check_identifier_type);
    RUN_TEST(test_get_obd2_frame_details_successfully);
    RUN_TEST(test_get_obd2_frame_details_unsuccessfully);
    RUN_TEST(test_find_protocol_obd2_successfully);
    RUN_TEST(test_get_uds_frame_details_successfully);
    RUN_TEST(test_get_uds_frame_details_unsuccessfully);
    RUN_TEST(test_find_protocol_uds_successfully);

    UNITY_END();

    return 0;
}
