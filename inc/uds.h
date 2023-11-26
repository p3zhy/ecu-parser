#ifndef ECU_PARSER_UDS_H
#define ECU_PARSER_UDS_H
#include "types.h"

typedef struct
{
    uint32_t identifier;
    uint8_t protocol_control_information;
    uint8_t service_id;
    uint8_t sub_function;
    uint8_t data_bytes[5];
} ecu_parser_uds_frame_details_t;
int ecu_parser_get_uds_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_uds_frame_details_t *frame_details);

#endif