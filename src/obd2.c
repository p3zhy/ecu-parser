#include "obd2.h"
#include <stdlib.h>
#include <string.h>
#include <helpers.h>

#define ECU_PARSER_FUNCTIONAL_REQUEST_STANDARD 0x7DF
#define ECU_PARSER_PHYSICAL_REQUEST_1_STANDARD 0x7E0
#define ECU_PARSER_PHYSICAL_RESPONSE_8_STANDARD 0x7EF
#define ECU_PARSER_FUNCTIONAL_REQUEST_EXTENDED 0x18DB33F1
#define ECU_PARSER_PHYSICAL_REQUEST_1_EXTENDED 0x18DA01F1
#define ECU_PARSER_PHYSICAL_RESPONSE_8_EXTENDED 0x18DAF108

int ecu_parser_get_obd2_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_obd2_frame_details_t *frame_details)
{
    frame_details->identifier = raw_data.identifier;
    frame_details->length = raw_data.data[0];
    frame_details->mode = raw_data.data[1];
    frame_details->pid = raw_data.data[2];
    memcpy(frame_details->data_bytes, &raw_data.data[3], 5);
    return EXIT_SUCCESS;
}

int ecu_parser_find_obd2_service(ecu_parser_obd2_frame_details_t frame_details, ecu_parser_obd2_service_t *service)
{
    uint8_t mode = frame_details.mode;
    if (mode == ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA || mode == ECU_PARSER_OBD2_SERVICE_SHOW_STORED_DIAGNOSTIC_TROUBLE_CODES)
    {
        *service = mode;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int ecu_parser_check_obd2_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_obd2_frame_details_t *frame_details)
{

    if ((raw_data.identifier == ECU_PARSER_FUNCTIONAL_REQUEST_STANDARD) ||
        ((raw_data.identifier >= ECU_PARSER_PHYSICAL_REQUEST_1_STANDARD) && (raw_data.identifier <= ECU_PARSER_PHYSICAL_RESPONSE_8_STANDARD)) ||
        (raw_data.identifier == ECU_PARSER_FUNCTIONAL_REQUEST_EXTENDED) ||
        ((raw_data.identifier >= ECU_PARSER_PHYSICAL_RESPONSE_8_EXTENDED) && (raw_data.identifier <= ECU_PARSER_PHYSICAL_REQUEST_1_EXTENDED)))
    {
        ecu_parser_obd2_frame_details_t obd2_frame_detail;
        if (ecu_parser_get_obd2_frame_details(raw_data, &obd2_frame_detail))
            return EXIT_FAILURE;
        if ((obd2_frame_detail.mode <= ECU_PARSER_OBD2_SERVICE_PERMANENET_DIAGNOSTIC_TROUBLE_CODES && obd2_frame_detail.mode >= ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA) ||
            (obd2_frame_detail.mode <= (ECU_PARSER_OBD2_SERVICE_PERMANENET_DIAGNOSTIC_TROUBLE_CODES + 0x40) && (obd2_frame_detail.mode >= ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA + 0x40)))
        {
            *frame_details = obd2_frame_detail;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}