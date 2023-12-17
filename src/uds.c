#include "uds.h"
#include <stdlib.h>
#include <string.h>

int ecu_parser_get_uds_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_uds_frame_details_t *frame_details)
{
    frame_details->identifier = raw_data.identifier;
    frame_details->protocol_control_information = raw_data.data[0];
    frame_details->service_id = raw_data.data[1];
    frame_details->sub_function = raw_data.data[2];
    memcpy(frame_details->data_bytes, &raw_data.data[3], 5);
    return EXIT_SUCCESS;
}

int ecu_parser_find_uds_service(ecu_parser_uds_frame_details_t frame_details, ecu_parser_uds_service_t *service)
{
    uint8_t service_id = frame_details.service_id;
    if (service_id == ECU_PARSER_UDS_SERVICE_READ_DTC_INFORMATION || service_id == ECU_PARSER_UDS_SERVICE_READ_DATA_BY_IDENTIFIER)
    {
        *service = service_id;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int ecu_parser_check_uds_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_uds_frame_details_t *frame_details)
{
    if ((raw_data.identifier == 0x7DF) || ((raw_data.identifier >= 0x7E0) && (raw_data.identifier <= 0x7EF)) || (raw_data.identifier == 0x18DB33F1) || ((raw_data.identifier >= 0x18DAF100) && (raw_data.identifier <= 0x18DAF1FF)))
    {
        ecu_parser_uds_frame_details_t uds_frame_detail;
        if (ecu_parser_get_uds_frame_details(raw_data, &uds_frame_detail))
            return EXIT_FAILURE;
        if ((uds_frame_detail.service_id <= 0x3E && uds_frame_detail.service_id >= 0x10) || (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) ||
            (uds_frame_detail.service_id <= 0x88 && uds_frame_detail.service_id >= 0x83) || (uds_frame_detail.service_id <= 0xC8 && uds_frame_detail.service_id >= 0xC3) ||
            (uds_frame_detail.service_id <= 0x7E && uds_frame_detail.service_id >= 0x50) || (uds_frame_detail.service_id == 0x7F))
        {
            *frame_details = uds_frame_detail;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}