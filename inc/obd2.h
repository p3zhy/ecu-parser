#ifndef ECU_PARSER_OBD2_H
#define ECU_PARSER_OBD2_H
#include "types.h"
typedef enum
{
    ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA = 0x01,
    ECU_PARSER_OBD2_SERVICE_SHOW_STORED_DIAGNOSTIC_TROUBLE_CODES = 0x03,
} ecu_parser_obd2_service_t;

typedef struct
{
    uint32_t identifier;
    uint8_t length;
    uint8_t mode;
    uint8_t pid;
    uint8_t data_bytes[5];
} ecu_parser_obd2_frame_details_t;

int ecu_parser_find_obd2_service(ecu_parser_obd2_frame_details_t frame_details, ecu_parser_obd2_service_t *service);
int ecu_parser_get_obd2_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_obd2_frame_details_t *frame_details);

#endif