#include "obd2.h"
#include <stdlib.h>
#include <string.h>
int ecu_parser_find_obd2_service(ecu_parser_obd2_frame_details_t frame_details)
{
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
