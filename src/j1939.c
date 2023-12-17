#include "j1939.h"
#include <stdlib.h>
#include <string.h>
#include <helpers.h>

int ecu_parser_find_j1939_service(ecu_parser_j1939_frame_details_t frame_details, ecu_parser_j1939_service_t *service)
{

    switch (frame_details.pgn)
    {
    case ECU_PARSER_J1939_SERVICE_PREVIOUSLY_ACTIVE_DIAGNOSTIC_TROUBLE_CODES:
    case ECU_PARSER_J1939_SERVICE_ACTIVE_DIAGNOSTIC_TROUBLE_CODES:
        *service = frame_details.pgn;
        break;

    default:
        *service = ECU_PARSER_J1939_SERVICE_NORMAL_PGNS;
        break;
    }

    return EXIT_SUCCESS;
}
int ecu_parser_get_j1939_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_j1939_frame_details_t *frame_details)
{
    frame_details->pgn = (raw_data.identifier >> 8) & 0x3FFFF;
    memcpy(frame_details->data_bytes, &raw_data.data[0], 8);
    return EXIT_SUCCESS;
}
int ecu_parser_check_j1939_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_j1939_frame_details_t *frame_details)
{

    if (ecu_parser_check_identifier_type(raw_data.identifier) == ECU_PARSER_IDENTIFIER_TYPE_EXTENDED)
    {
        ecu_parser_j1939_frame_details_t j1939_frame_detail;
        if (ecu_parser_get_j1939_frame_details(raw_data, &j1939_frame_detail))
            return EXIT_FAILURE;

        if ((j1939_frame_detail.pgn >= 0xf000 && j1939_frame_detail.pgn <= 0xffff) || (j1939_frame_detail.pgn >= 0x1f000 && j1939_frame_detail.pgn <= 0x1ffff))
        {
            *frame_details = j1939_frame_detail;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}
