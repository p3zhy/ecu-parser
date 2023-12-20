#ifndef ECU_PARSER_CANOPEN_H
#define ECU_PARSER_CANOPEN_H
#include "types.h"
typedef enum
{
    ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO1 = 0b0011,
    ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO2 = 0b0101,
    ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO3 = 0b0111,
    ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_PDO4 = 0b1001,
    ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO1 = 0b0100,
    ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO2 = 0b0110,
    ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO3 = 0b1000,
    ECU_PARSER_CANOPEN_SERVICE_RECEIVE_PDO4 = 0b1010,
    ECU_PARSER_CANOPEN_SERVICE_RECEIVE_SDO = 0b1100,
    ECU_PARSER_CANOPEN_SERVICE_TRANSMIT_SDO = 0b1011,
    ECU_PARSER_CANOPEN_SERVICE_HEARTBEAT = 0b1110,
} ecu_parser_canopen_service_t;

typedef struct
{
    uint32_t cob_id;
    uint32_t function_code;
    uint32_t node_id;
    uint8_t data_bytes[8];
} ecu_parser_canopen_frame_details_t;

int ecu_parser_find_canopen_service(ecu_parser_canopen_frame_details_t frame_details, ecu_parser_canopen_service_t *service);
int ecu_parser_get_canopen_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_canopen_frame_details_t *frame_details);
int ecu_parser_check_canopen_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_canopen_frame_details_t *frame_details);

#endif