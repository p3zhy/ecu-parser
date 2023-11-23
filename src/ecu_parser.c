#include "ecu_parser.h"

int ecu_parser_find_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_protocol_info_t *protocol_info)
{
    if (ecu_parser_check_identifier_type(raw_data.identifier) == ECU_PARSER_IDENTIFIER_TYPE_STANDARD)
    {
        // Based on ISO 15765-4
        if ((raw_data.identifier == 0x7DF) || ((raw_data.identifier >= 0x7E0) && (raw_data.identifier <= 0x7EF)))
        {
            ecu_parser_obd2_frame_details_t obd2_frame_detail;
            if (ecu_parser_get_obd2_frame_details(raw_data, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2;
                protocol_info->protocol_details = (ecu_parser_protocol_details_t){.obd2_details = obd2_frame_detail};
                return EXIT_SUCCESS;
            }
            ecu_parser_uds_frame_details_t uds_frame_detail;
            if (ecu_parser_get_uds_frame_details(raw_data, &uds_frame_detail))
                return EXIT_FAILURE;

            if ((uds_frame_detail.service_id <= 0x3E && uds_frame_detail.service_id >= 0x10) || (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) ||
                (uds_frame_detail.service_id <= 0x88 && uds_frame_detail.service_id >= 0x83) || (uds_frame_detail.service_id <= 0xC8 && uds_frame_detail.service_id >= 0xC3) ||
                (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) || (uds_frame_detail.service_id == 0x7F))
            {
                protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS;
                protocol_info->protocol_details = (ecu_parser_protocol_details_t){.uds_details = uds_frame_detail};
                return EXIT_SUCCESS;
            }
        }
    }
    else
    {
        if ((raw_data.identifier == 0x18DB33F1) || ((raw_data.identifier >= 0x18DAF100) && (raw_data.identifier <= 0x18DAF1FF)))
        {
            ecu_parser_obd2_frame_details_t obd2_frame_detail;
            if (ecu_parser_get_obd2_frame_details(raw_data, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_OBD2;
                protocol_info->protocol_details = (ecu_parser_protocol_details_t){.obd2_details = obd2_frame_detail};
                return EXIT_SUCCESS;
            }

            ecu_parser_uds_frame_details_t uds_frame_detail;
            if (ecu_parser_get_uds_frame_details(raw_data, &uds_frame_detail))
                return EXIT_FAILURE;

            if ((uds_frame_detail.service_id <= 0x3E && uds_frame_detail.service_id >= 0x10) || (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) ||
                (uds_frame_detail.service_id <= 0x88 && uds_frame_detail.service_id >= 0x83) || (uds_frame_detail.service_id <= 0xC8 && uds_frame_detail.service_id >= 0xC3) ||
                (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) || (uds_frame_detail.service_id == 0x7F))
            {
                protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_UDS;
                protocol_info->protocol_details = (ecu_parser_protocol_details_t){.uds_details = uds_frame_detail};
                return EXIT_SUCCESS;
            }
        }
    }

    protocol_info->protocol_name = ECU_PARSER_PROTOCOL_NAME_UNKNOWN;
    protocol_info->protocol_details = (ecu_parser_protocol_details_t){};
    return EXIT_SUCCESS;
}

ecu_parser_identifier_type_t ecu_parser_check_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? ECU_PARSER_IDENTIFIER_TYPE_STANDARD : ECU_PARSER_IDENTIFIER_TYPE_EXTENDED;
}

int ecu_parser_get_obd2_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_obd2_frame_details_t *frame_details)
{
    frame_details->identifier = raw_data.identifier;
    frame_details->length = raw_data.data[0];
    frame_details->mode = raw_data.data[1];
    frame_details->pid = raw_data.data[2];
    memcpy(frame_details->data_bytes, &raw_data.data[3], 5);
    return EXIT_SUCCESS;
}

int ecu_parser_get_uds_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_uds_frame_details_t *frame_details)
{
    frame_details->identifier = raw_data.identifier;
    frame_details->protocol_control_information = raw_data.data[0];
    frame_details->service_id = raw_data.data[1];
    frame_details->sub_function = raw_data.data[2];
    memcpy(frame_details->data_bytes, &raw_data.data[3], 5);
    return EXIT_SUCCESS;
}