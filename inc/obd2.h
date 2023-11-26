#ifndef ECU_PARSER_OBD2_H
#define ECU_PARSER_OBD2_H
#include "types.h"
typedef enum
{
    ECU_PARSER_OBD2_SERVICE_SHOW_CURRENT_DATA = 1,
    ECU_PARSER_OBD2_SERVICE_SHOW_FREEZ_FRAME_DATA,
    ECU_PARSER_OBD2_SERVICE_SHOW_STORED_DIAGNOSTIC_TROUBLE_CODES,
    ECU_PARSER_OBD2_SERVICE_CLEAR_DIAGNOSTIC_TROUBLE_CODES_AND_STORED_VALUES,
    ECU_PARSER_OBD2_SERVICE_TEST_RESULTS_OXYGEN_SENSOR_MONITORING,
    ECU_PARSER_OBD2_SERVICE_TEST_RESULTS_OTHER_COMPONENT_SYSTEM_MONITORING,
    ECU_PARSER_OBD2_SERVICE_SHOW_PENDING_DIAGNOSTIC_TROUBLE_CODES,
    ECU_PARSER_OBD2_SERVICE_CONTROL_OPERATION_OF_ON_BOARD_COMPONENT,
    ECU_PARSER_OBD2_SERVICE_REQUEST_VEHICLE_INFORMATION,
    ECU_PARSER_OBD2_SERVICE_PERMANENT_DIAGNOSTIC_TROUBLE_CODES,
} ecu_parser_obd2_service;

typedef struct
{
    uint32_t identifier;
    uint8_t length;
    uint8_t mode;
    uint8_t pid;
    uint8_t data_bytes[5];
} ecu_parser_obd2_frame_details_t;

int ecu_parser_find_obd2_service(ecu_parser_obd2_frame_details_t frame_details);
int ecu_parser_get_obd2_frame_details(ecu_parser_raw_data_t raw_data, ecu_parser_obd2_frame_details_t *frame_details);

#endif