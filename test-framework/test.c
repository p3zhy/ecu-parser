#include "unity.h"
#include "../inc/ecu_parser.h"
#include "../inc/obd2.h"
#include "../inc/uds.h"
#include "../inc/helpers.h"
#include "../inc/j1939.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ecu_parser_check_identifier_type()
{
    TEST_ASSERT_EQUAL_INT(ECU_PARSER_IDENTIFIER_TYPE_STANDARD, ecu_parser_check_identifier_type(0x700));
    TEST_ASSERT_EQUAL_INT(ECU_PARSER_IDENTIFIER_TYPE_EXTENDED, ecu_parser_check_identifier_type(0xCF00400));
}

void test_ecu_parser_get_obd2_frame_details_successfully()
{
    ecu_parser_obd2_frame_details_t expected = {0x7E8, 0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA};
    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x7E8,
                                                                   .data = {0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA}};
    ecu_parser_obd2_frame_details_t actual;
    int result = ecu_parser_get_obd2_frame_details(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(actual.data_bytes, expected.data_bytes, 5);
    TEST_ASSERT_EQUAL_UINT8(actual.length, expected.length);
    TEST_ASSERT_EQUAL_UINT8(actual.mode, expected.mode);
    TEST_ASSERT_EQUAL_UINT8(actual.pid, expected.pid);
    TEST_ASSERT_EQUAL_UINT32(actual.identifier, expected.identifier);
}

void test_ecu_parser_find_protocol_obd2_successfully()
{

    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x7E8,
                                                                   .data = {0x03, 0x41, 0x0D, 0x32, 0xAA, 0xAA, 0xAA, 0xAA}};

    ecu_parser_protocol_info_t actual = {
        .protocol_details.obd2_details = {0}};

    ecu_parser_protocol_info_t expected = {
        .protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2,
        .protocol_details.obd2_details = {
            .identifier = 0x7E8,
            .length = 0x03,
            .mode = 0x41,
            .pid = 0x0D,
            .data_bytes = {0x32, 0xAA, 0xAA, 0xAA, 0xAA}}};

    int result = ecu_parser_find_protocol(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(expected.protocol_name, actual.protocol_name);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.obd2_details.pid, actual.protocol_details.obd2_details.pid);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.obd2_details.identifier, actual.protocol_details.obd2_details.identifier);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.obd2_details.length, actual.protocol_details.obd2_details.length);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected.protocol_details.obd2_details.data_bytes, actual.protocol_details.obd2_details.data_bytes, 5);
}

void test_ecu_parser_get_uds_frame_details_successfully()
{
    ecu_parser_uds_frame_details_t expected = {0x7EC, 0x03, 0x7F, 0x22, 0x13};
    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x7EC,
                                                                   .data = {0x03, 0x7F, 0x22, 0x13}};
    ecu_parser_uds_frame_details_t actual;
    int result = ecu_parser_get_uds_frame_details(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_UINT8(actual.service_id, expected.service_id);
    TEST_ASSERT_EQUAL_UINT8(actual.sub_function, expected.sub_function);
    TEST_ASSERT_EQUAL_UINT8(actual.protocol_control_information, expected.protocol_control_information);
    TEST_ASSERT_EQUAL_UINT32(actual.identifier, expected.identifier);
}

void test_ecu_parser_find_protocol_uds_successfully()
{

    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x7E8,
                                                                   .data = {0x03, 0x7F, 0x22, 0x13, 0xAA, 0xAA, 0xAA, 0xAA}};
    ecu_parser_protocol_info_t actual = {
        .protocol_details.uds_details = {0}};

    ecu_parser_protocol_info_t expected = {
        .protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS,
        .protocol_details.uds_details = {
            .identifier = 0x7E8,
            .protocol_control_information = 0x03,
            .service_id = 0x7F,
            .sub_function = 0x22,
            .data_bytes = {0x13, 0xAA, 0xAA, 0xAA, 0xAA}}};

    int result = ecu_parser_find_protocol(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(expected.protocol_name, actual.protocol_name);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.uds_details.protocol_control_information, actual.protocol_details.uds_details.protocol_control_information);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.uds_details.identifier, actual.protocol_details.uds_details.identifier);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.uds_details.service_id, actual.protocol_details.uds_details.service_id);
    TEST_ASSERT_EQUAL_INT(expected.protocol_details.uds_details.sub_function, actual.protocol_details.uds_details.sub_function);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected.protocol_details.uds_details.data_bytes, actual.protocol_details.uds_details.data_bytes, 5);
}

void test_ecu_parser_find_protocol_unsuccessfully()
{

    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0xff};

    ecu_parser_protocol_info_t actual;

    int result = ecu_parser_find_protocol(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}

void test_ecu_parser_find_obd2_service_successfully()
{
    ecu_parser_obd2_service_t service;
    ecu_parser_obd2_frame_details_t frame_details = {.mode = 0x01};
    int result = ecu_parser_find_obd2_service(frame_details, &service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(service, ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA);
}
void test_ecu_parser_find_uds_service_successfully()
{
    ecu_parser_uds_service_t service;
    ecu_parser_uds_frame_details_t frame_details = {.service_id = 0x22};
    int result = ecu_parser_find_uds_service(frame_details, &service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(service, ECU_PARSER_UDS_SERVICE_READ_DATA_BY_IDENTIFIER);
}

void test_ecu_parser_find_obd2_service_unsuccessfully()
{
    ecu_parser_obd2_service_t service;
    ecu_parser_obd2_frame_details_t frame_details = {.mode = 0x22};
    int result = ecu_parser_find_obd2_service(frame_details, &service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}
void test_ecu_parser_find_uds_service_unsuccessfully()
{
    ecu_parser_uds_service_t service;
    ecu_parser_uds_frame_details_t frame_details = {.service_id = 0x1};
    int result = ecu_parser_find_uds_service(frame_details, &service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}

void test_ecu_parser_find_service_obd2_successfully()
{
    ecu_parser_service_t ecu_parser_service;
    ecu_parser_protocol_info_t protocol_info = {.protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2, .protocol_details.obd2_details.mode = 0x01};
    int result = ecu_parser_find_service(protocol_info, &ecu_parser_service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(ecu_parser_service.obd2_service, ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA);
}
void test_ecu_parser_find_service_uds_successfully()
{

    ecu_parser_service_t ecu_parser_service;
    ecu_parser_protocol_info_t protocol_info = {.protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS, .protocol_details.uds_details.service_id = 0x22};
    int result = ecu_parser_find_service(protocol_info, &ecu_parser_service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(ecu_parser_service.uds_service, ECU_PARSER_UDS_SERVICE_READ_DATA_BY_IDENTIFIER);
}

void test_ecu_parser_find_service_obd2_unsuccessfully()
{
    ecu_parser_service_t ecu_parser_service;
    ecu_parser_protocol_info_t protocol_info = {.protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2, .protocol_details.obd2_details.mode = 0x33};
    int result = ecu_parser_find_service(protocol_info, &ecu_parser_service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}
void test_ecu_parser_find_service_uds_unsuccessfully()
{

    ecu_parser_service_t ecu_parser_service;
    ecu_parser_protocol_info_t protocol_info = {.protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS, .protocol_details.uds_details.service_id = 0x1};
    int result = ecu_parser_find_service(protocol_info, &ecu_parser_service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_FAILURE);
}

void test_ecu_parser_find_parameter_little_endian_order()
{
    ecu_parser_raw_data_t raw_data = {
        .identifier = 0x0CF00401,
        .data = {0xFF, 0xFF, 0xFF, 0x68, 0x13, 0xFF, 0xFF, 0xFF}};

    ecu_parser_parameter_details_t parameter_details = {
        .start_bit = 24,
        .length = 16,
        .scale = 0.125,
        .offset = 0,
        .min_value = 0.0,
        .max_value = 8031.875};

    ecu_parser_byte_order_t byte_order = ECU_PARSER_BYTE_ORDER_LITTLE_ENDIAN;

    float value;
    int result = ecu_parser_find_parameter(raw_data, parameter_details, byte_order, &value);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_FLOAT(value, 621.0);
}

void test_ecu_parser_find_parameter_big_endian_order()
{
    ecu_parser_raw_data_t raw_data = {
        .identifier = 0x0CF00401,
        .data = {0xFF, 0xFF, 0xFF, 0x13, 0x68, 0xFF, 0xFF, 0xFF}};

    ecu_parser_parameter_details_t parameter_details = {
        .start_bit = 24,
        .length = 16,
        .scale = 0.125,
        .offset = 0,
        .min_value = 0.0,
        .max_value = 8031.875};

    ecu_parser_byte_order_t byte_order = ECU_PARSER_BYTE_ORDER_BIG_ENDIAN;

    float value;
    int result = ecu_parser_find_parameter(raw_data, parameter_details, byte_order, &value);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_FLOAT(621.0, value);
}

void test_ecu_parser_find_parameter_length_lower_than_8()
{
    ecu_parser_raw_data_t raw_data = {
        .identifier = 0x0CF00401,
        .data = {0xFF, 0xFF, 0xFF, 0x27, 0xFF, 0xFF, 0xFF, 0xFF}};

    ecu_parser_parameter_details_t parameter_details = {
        .start_bit = 24,
        .length = 3,
        .scale = 1.0,
        .offset = 0,
        .min_value = 0.0,
        .max_value = 10000};

    ecu_parser_byte_order_t byte_order = ECU_PARSER_BYTE_ORDER_LITTLE_ENDIAN;

    float value;
    int result = ecu_parser_find_parameter(raw_data, parameter_details, byte_order, &value);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_FLOAT(value, 7.0);
}

void test_ecu_parser_get_j1939_frame_details_successfully()
{
    ecu_parser_j1939_frame_details_t expected = {
        .pgn = 61444,
        .data_bytes = {0xFF, 0xFF, 0xFF, 0x68, 0x13, 0xFF, 0xFF, 0xFF}};

    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x0CF00401, .data = {0xFF, 0xFF, 0xFF, 0x68, 0x13, 0xFF, 0xFF, 0xFF}};
    ecu_parser_j1939_frame_details_t actual;
    int result = ecu_parser_get_j1939_frame_details(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(actual.data_bytes, expected.data_bytes, 8);
    TEST_ASSERT_EQUAL_UINT32(actual.pgn, expected.pgn);
}

void test_ecu_parser_find_protocol_j1939_successfully()
{

    ecu_parser_raw_data_t input_raw_data = (ecu_parser_raw_data_t){.identifier = 0x0CF00401,
                                                                   .data = {0xFF, 0xFF, 0xFF, 0x68, 0x13, 0xFF, 0xFF, 0xFF}};

    ecu_parser_protocol_info_t actual = {
        .protocol_details.j1939_details = {0}};

    ecu_parser_protocol_info_t expected = {
        .protocol_name = ECU_PARSER_PROTOCOL_NAME_J1939,
        .protocol_details.j1939_details = {
            .pgn = 61444,
            .data_bytes = {0xFF, 0xFF, 0xFF, 0x68, 0x13, 0xFF, 0xFF, 0xFF}}};

    int result = ecu_parser_find_protocol(input_raw_data, &actual);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(expected.protocol_name, actual.protocol_name);
    TEST_ASSERT_EQUAL_UINT32(expected.protocol_details.j1939_details.pgn, actual.protocol_details.j1939_details.pgn);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected.protocol_details.j1939_details.data_bytes, actual.protocol_details.j1939_details.data_bytes, 8);
}

void test_ecu_parser_find_service_j1939_successfully()
{
    ecu_parser_service_t ecu_parser_service;
    ecu_parser_protocol_info_t protocol_info = {.protocol_name = ECU_PARSER_PROTOCOL_NAME_J1939, .protocol_details.j1939_details.pgn = 0x0CF00401};
    int result = ecu_parser_find_service(protocol_info, &ecu_parser_service);
    TEST_ASSERT_EQUAL_INT(result, EXIT_SUCCESS);
    TEST_ASSERT_EQUAL_INT(ecu_parser_service.j1939_service, ECU_PARSER_J1939_SERVICE_NORMAL_PGNS);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_ecu_parser_check_identifier_type);
    RUN_TEST(test_ecu_parser_get_obd2_frame_details_successfully);
    RUN_TEST(test_ecu_parser_find_protocol_obd2_successfully);
    RUN_TEST(test_ecu_parser_find_protocol_unsuccessfully);
    RUN_TEST(test_ecu_parser_get_uds_frame_details_successfully);
    RUN_TEST(test_ecu_parser_find_protocol_uds_successfully);
    RUN_TEST(test_ecu_parser_find_obd2_service_successfully);
    RUN_TEST(test_ecu_parser_find_uds_service_successfully);
    RUN_TEST(test_ecu_parser_find_obd2_service_unsuccessfully);
    RUN_TEST(test_ecu_parser_find_uds_service_unsuccessfully);
    RUN_TEST(test_ecu_parser_find_service_obd2_successfully);
    RUN_TEST(test_ecu_parser_find_service_uds_successfully);
    RUN_TEST(test_ecu_parser_find_service_obd2_unsuccessfully);
    RUN_TEST(test_ecu_parser_find_service_uds_unsuccessfully);
    RUN_TEST(test_ecu_parser_find_parameter_little_endian_order);
    RUN_TEST(test_ecu_parser_find_parameter_big_endian_order);
    RUN_TEST(test_ecu_parser_find_parameter_length_lower_than_8);
    RUN_TEST(test_ecu_parser_get_j1939_frame_details_successfully);
    RUN_TEST(test_ecu_parser_find_protocol_j1939_successfully);
    RUN_TEST(test_ecu_parser_find_service_j1939_successfully);

    UNITY_END();

    return 0;
}
