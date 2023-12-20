#include "canopen.h"
#include <stdlib.h>
#include <string.h>
#include <helpers.h>

int ecu_parser_find_canopen_service(ecu_parser_canopen_frame_details_t frame_details, ecu_parser_canopen_service_t *service)
{

    if (frame_details.function_code == ECU_PARSER_CANOPEN_SERVICE_HEARTBEAT ||
        ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO1 ||
        ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO2 ||
        ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO3 ||
        ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO4 ||
        ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO1 ||
        ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO2 ||
        ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO3 ||
        ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO4 ||
        ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_SDO ||
        ECU_PARSER_CANOPEN_SERVICE_RECEIVE_SDO)
    {
        *service = frame_details.function_code;
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
int ecu_parser_get_canopen_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_canopen_frame_details_t *frame_details)
{
    frame_details->cob_id = raw_data.identifier;
    frame_details->function_code = (raw_data.identifier >> 7);
    frame_details->node_id = (raw_data.identifier & 0x7F);
    memcpy(frame_details->data_bytes, &raw_data.data[0], 8);
    return EXIT_SUCCESS;
}
int ecu_parser_check_canopen_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_canopen_frame_details_t *frame_details)
{

    if (ecu_parser_check_identifier_type(raw_data.identifier) == ECU_PARSER_IDENTIFIER_TYPE_STANDARD)
    {
        ecu_parser_canopen_frame_details_t canopen_frame_detail;
        if (ecu_parser_get_canopen_frame_details(raw_data, &canopen_frame_detail))
            return EXIT_FAILURE;

        if (
            (canopen_frame_detail.cob_id >= 0x181 && canopen_frame_detail.cob_id <= 0x1FF) ||
            (canopen_frame_detail.cob_id >= 0x201 && canopen_frame_detail.cob_id <= 0x27F) ||
            (canopen_frame_detail.cob_id >= 0x281 && canopen_frame_detail.cob_id <= 0x2FF) ||
            (canopen_frame_detail.cob_id >= 0x301 && canopen_frame_detail.cob_id <= 0x37F) ||
            (canopen_frame_detail.cob_id >= 0x381 && canopen_frame_detail.cob_id <= 0x3FF) ||
            (canopen_frame_detail.cob_id >= 0x401 && canopen_frame_detail.cob_id <= 0x47F) ||
            (canopen_frame_detail.cob_id >= 0x481 && canopen_frame_detail.cob_id <= 0x4FF) ||
            (canopen_frame_detail.cob_id >= 0x501 && canopen_frame_detail.cob_id <= 0x57F) ||
            (canopen_frame_detail.cob_id >= 0x581 && canopen_frame_detail.cob_id <= 0x5FF) ||
            (canopen_frame_detail.cob_id >= 0x601 && canopen_frame_detail.cob_id <= 0x67F) ||
            (canopen_frame_detail.cob_id >= 0x701 && canopen_frame_detail.cob_id <= 0x7FF) ||
            (canopen_frame_detail.cob_id >= 0x081 && canopen_frame_detail.cob_id <= 0x0FF) ||
            (canopen_frame_detail.cob_id == 0x080) ||
            (canopen_frame_detail.cob_id == 0x100) ||
            (canopen_frame_detail.cob_id == 0x000))

        {
            *frame_details = canopen_frame_detail;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}
