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
    }
    return EXIT_FAILURE;
}