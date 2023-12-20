#include "ecu_parser.h"

int ecu_parser_find_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_protocol_info_t *protocol_info)
{

    if (!ecu_parser_check_obd2_protocol(raw_data, &protocol_info->protocol_details.obd2_details))
    {
        protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2;
        return EXIT_SUCCESS;
    }

    if (!ecu_parser_check_uds_protocol(raw_data, &protocol_info->protocol_details.uds_details))
    {
        protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS;
        return EXIT_SUCCESS;
    }

    if (!ecu_parser_check_j1939_protocol(raw_data, &protocol_info->protocol_details.j1939_details))
    {
        protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_J1939;
        return EXIT_SUCCESS;
    }

    if (!ecu_parser_check_canopen_protocol(raw_data, &protocol_info->protocol_details.canopen_details))
    {
        protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_CANOPEN;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int ecu_parser_find_service(ecu_parser_protocol_info_t protocol_info, ecu_parser_service_t *ecu_parser_service)
{

    switch (protocol_info.protocol_name)
    {
    case ECU_PARSER_PROTOCOL_NAME_OBD2:
        if (!ecu_parser_find_obd2_service(protocol_info.protocol_details.obd2_details, &ecu_parser_service->obd2_service))
            return EXIT_SUCCESS;
        break;
    case ECU_PARSER_PROTOCOL_NAME_UDS:
        if (!ecu_parser_find_uds_service(protocol_info.protocol_details.uds_details, &ecu_parser_service->uds_service))
            return EXIT_SUCCESS;
        break;

    case ECU_PARSER_PROTOCOL_NAME_J1939:
        if (!ecu_parser_find_j1939_service(protocol_info.protocol_details.j1939_details, &ecu_parser_service->j1939_service))
            return EXIT_SUCCESS;
        break;

    case ECU_PARSER_PROTOCOL_NAME_CANOPEN:
        if (!ecu_parser_find_canopen_service(protocol_info.protocol_details.canopen_details, &ecu_parser_service->canopen_service))
            return EXIT_SUCCESS;
        break;
    }
    return EXIT_FAILURE;
}

int ecu_parser_find_parameter(ecu_parser_raw_data_t raw_data, ecu_parser_parameter_details_t parameter_details, ecu_parser_byte_order_t byte_order, float *value)
{

    if ((parameter_details.start_bit + parameter_details.length > 64) | (parameter_details.start_bit < 1))
    {
        return EXIT_FAILURE;
    }

    size_t start_byte = parameter_details.start_bit / 8;
    size_t start_bit_within_byte = parameter_details.start_bit % 8;
    size_t length_in_bytes = (size_t)ceilf((float)parameter_details.length / 8.0);

    uint8_t extracted_bytes[length_in_bytes];

    for (size_t i = 0; i < length_in_bytes; i++)
    {
        extracted_bytes[i] = raw_data.data[start_byte + i];
    }

    if (byte_order == ECU_PARSER_BYTE_ORDER_LITTLE_ENDIAN)
    {

        for (int i = 0; i < length_in_bytes / 2; i++)
        {
            int temp = extracted_bytes[i];
            extracted_bytes[i] = extracted_bytes[length_in_bytes - i - 1];
            extracted_bytes[length_in_bytes - i - 1] = temp;
        }
    }

    uint64_t raw_value = 0;
    for (size_t i = 0; i < length_in_bytes; i++)
    {
        raw_value = (raw_value << 8) | extracted_bytes[i];
    }

    // Shift the raw value to eliminate unwanted bits on the right
    raw_value >>= start_bit_within_byte;

    // Mask out any remaining unwanted bits on the left
    raw_value &= ((uint64_t)1 << parameter_details.length) - 1;

    float scaled_value = (raw_value * parameter_details.scale) + parameter_details.offset;

    if (scaled_value < parameter_details.min_value)
    {
        *value = parameter_details.min_value;
    }
    else if (scaled_value > parameter_details.max_value)
    {
        *value = parameter_details.max_value;
    }
    else
    {
        *value = scaled_value;
    }

    return EXIT_SUCCESS;
}