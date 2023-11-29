#ifndef ECU_PARSER_UDS_H
#define ECU_PARSER_UDS_H
#include "types.h"

typedef enum
{
    ECU_PARSER_UDS_SERVICE_READ_DTC_INFORMATION = 0x19,
    ECU_PARSER_UDS_SERVICE_READ_DATA_BY_IDENTIFIER = 0x22,

} ecu_parser_uds_service_t;

typedef struct
{
    uint32_t identifier;
    uint8_t protocol_control_information;
    uint8_t service_id;
    uint8_t sub_function;
    uint8_t data_bytes[5];
} ecu_parser_uds_frame_details_t;
int ecu_parser_get_uds_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_uds_frame_details_t *frame_details);
int ecu_parser_find_uds_service(ecu_parser_uds_frame_details_t frame_details, ecu_parser_uds_service_t *service);
#endif