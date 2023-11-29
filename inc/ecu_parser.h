#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include "types.h"
#include "obd2.h"
#include "uds.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef enum
{
    ECU_PARSER_PROTOCOL_NAME_J1939,
    ECU_PARSER_PROTOCOL_NAME_CANOPEN,
    ECU_PARSER_PROTOCOL_NAME_OBD2,
    ECU_PARSER_PROTOCOL_NAME_UDS,
    ECU_PARSER_PROTOCOL_NAME_LIN,
    ECU_PARSER_PROTOCOL_NAME_NMEA2000,
    ECU_PARSER_PROTOCOL_NAME_ISOBUS,
    ECU_PARSER_PROTOCOL_NAME_UNKNOWN
} ecu_parser_protocol_name_t;

typedef enum
{
    ECU_PARSER_IDENTIFIER_TYPE_STANDARD,
    ECU_PARSER_IDENTIFIER_TYPE_EXTENDED,
} ecu_parser_identifier_type_t;

typedef union
{
    ecu_parser_obd2_frame_details_t obd2_details;
    ecu_parser_uds_frame_details_t uds_details;
} ecu_parser_protocol_details_t;

// typedef struct
// {
//     uint8_t start_bit;
//     uint8_t length;
//     float scale;
//     uint64_t offset;
//     float min_value;
//     float max_value;
// } parser_details_t;

typedef struct
{
    ecu_parser_protocol_name_t protocol_name;
    ecu_parser_protocol_details_t protocol_details;
} ecu_parser_protocol_info_t;

typedef union
{
    ecu_parser_obd2_service_t obd2_service;
    ecu_parser_uds_service_t uds_service;
} ecu_parser_service_t;

int ecu_parser_find_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_protocol_info_t *protocol_info);
int ecu_parser_find_service(ecu_parser_protocol_info_t protocol_info, ecu_parser_service_t *ecu_parser_service);
ecu_parser_identifier_type_t ecu_parser_check_identifier_type(uint32_t identifier);

#endif // ECU_PARSER_H