#include "ecu_parser.h"

int find_protocol(uint32_t identifier, const uint8_t *data, size_t data_size, protocol_info_t *protocol_info)
{

    if (check_identifier_type(identifier) == IDENTIFIER_TYPE_STANDARD)
    {
        // Based on ISO 15765-4
        if ((identifier == 0x7DF) || ((identifier >= 0x7E0) && (identifier <= 0x7EF)))
        {
            obd2_frame_details_t obd2_frame_detail;
            if (get_obd2_frame_details(identifier, data, data_size, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                protocol_info->protocol_name = PROTOCOL_NAME_OBD2;
                protocol_info->protocol_details = (protocol_details_t){.obd2_details = obd2_frame_detail};
                return EXIT_SUCCESS;
            }
            uds_frame_details_t uds_frame_detail;
            if (get_uds_frame_details(identifier, data, data_size, &uds_frame_detail))
                return EXIT_FAILURE;

            if ((uds_frame_detail.service_id <= 0x3E && uds_frame_detail.service_id >= 0x10) || (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) ||
                (uds_frame_detail.service_id <= 0x88 && uds_frame_detail.service_id >= 0x83) || (uds_frame_detail.service_id <= 0xC8 && uds_frame_detail.service_id >= 0xC3) ||
                (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) || (uds_frame_detail.service_id == 0x7F))
            {
                protocol_info->protocol_name = PROTOCOL_NAME_UDS;
                protocol_info->protocol_details = (protocol_details_t){.uds_details = uds_frame_detail};
                return EXIT_SUCCESS;
            }
        }
    }
    else
    {
        if ((identifier == 0x18DB33F1) || ((identifier >= 0x18DAF100) && (identifier <= 0x18DAF1FF)))
        {
            obd2_frame_details_t obd2_frame_detail;
            if (get_obd2_frame_details(identifier, data, data_size, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                protocol_info->protocol_name = PROTOCOL_NAME_OBD2;
                protocol_info->protocol_details = (protocol_details_t){.obd2_details = obd2_frame_detail};
                return EXIT_SUCCESS;
            }

            uds_frame_details_t uds_frame_detail;
            if (get_uds_frame_details(identifier, data, data_size, &uds_frame_detail))
                return EXIT_FAILURE;

            if ((uds_frame_detail.service_id <= 0x3E && uds_frame_detail.service_id >= 0x10) || (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) ||
                (uds_frame_detail.service_id <= 0x88 && uds_frame_detail.service_id >= 0x83) || (uds_frame_detail.service_id <= 0xC8 && uds_frame_detail.service_id >= 0xC3) ||
                (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) || (uds_frame_detail.service_id == 0x7F))
            {
                protocol_info->protocol_name = PROTOCOL_NAME_UDS;
                protocol_info->protocol_details = (protocol_details_t){.uds_details = uds_frame_detail};
                return EXIT_SUCCESS;
            }
        }
    }

    protocol_info->protocol_name = PROTOCOL_NAME_UNKNOWN;
    protocol_info->protocol_details = (protocol_details_t){};
    return EXIT_SUCCESS;
}
int parse_protocol(uint32_t identifier, const uint8_t *data, size_t data_size, protocol_info_t protocol_info, parser_details_t parser_details)
{
    printf("Parsing protocol...\n");
    switch (protocol_info.protocol_name)
    {
    case PROTOCOL_NAME_OBD2:

        break;
    case PROTOCOL_NAME_UDS:
        break;
    default:
        break;
    }
}

identifier_type_t check_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? IDENTIFIER_TYPE_STANDARD : IDENTIFIER_TYPE_EXTENDED;
}

int get_obd2_frame_details(uint32_t identifier, const uint8_t *data, size_t data_size, obd2_frame_details_t *frame_details)
{
    // Based on ISO 15031-5
    if (data_size < 4)
    {
        return EXIT_FAILURE;
    }
    frame_details->identifier = identifier;
    frame_details->length = data[0];
    frame_details->mode = data[1];
    frame_details->pid = data[2];
    memcpy(frame_details->data_bytes, &data[3], data_size - 3);
    return EXIT_SUCCESS;
}

int get_uds_frame_details(uint32_t identifier, const uint8_t *data, size_t data_size, uds_frame_details_t *frame_details)
{

    if (data_size < 4)
    {
        return EXIT_FAILURE;
    }

    frame_details->identifier = identifier;
    frame_details->protocol_control_information = data[0];
    frame_details->service_id = data[1];
    frame_details->sub_function = data[2];
    memcpy(frame_details->data_bytes, &data[3], data_size - 3);
    return EXIT_SUCCESS;
}