#ifndef ECU_PARSER_J1939_H
#define ECU_PARSER_J1939_H
#include "types.h"
typedef enum
{
    ECU_PARSER_J1939_SERVICE_NORMAL_PGNS,
    ECU_PARSER_J1939_SERVICE_ACTIVE_DIAGNOSTIC_TROUBLE_CODES = 65226,
    ECU_PARSER_J1939_SERVICE_PREVIOUSLY_ACTIVE_DIAGNOSTIC_TROUBLE_CODES = 65227,
} ecu_parser_j1939_service_t;

typedef struct
{
    uint32_t pgn;
    uint8_t data_bytes[8];
} ecu_parser_j1939_frame_details_t;

int ecu_parser_find_j1939_service(ecu_parser_j1939_frame_details_t frame_details, ecu_parser_j1939_service_t *service);
int ecu_parser_get_j1939_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_j1939_frame_details_t *frame_details);
int ecu_parser_check_j1939_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_j1939_frame_details_t *frame_details);

#endif