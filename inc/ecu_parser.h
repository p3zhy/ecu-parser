#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include "types.h"
#include "obd2.h"
#include "uds.h"
#include "j1939.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef enum
{
    ECU_PARSER_PROTOCOL_NAME_J1939,
    ECU_PARSER_PROTOCOL_NAME_CANOPEN,
    ECU_PARSER_PROTOCOL_NAME_OBD2,
    ECU_PARSER_PROTOCOL_NAME_UDS,
    ECU_PARSER_PROTOCOL_NAME_LIN,
    ECU_PARSER_PROTOCOL_NAME_NMEA2000,
    ECU_PARSER_PROTOCOL_NAME_ISOBUS,
} ecu_parser_protocol_name_t;

typedef union
{
    ecu_parser_obd2_frame_details_t obd2_details;
    ecu_parser_uds_frame_details_t uds_details;
    ecu_parser_j1939_frame_details_t j1939_details;
} ecu_parser_protocol_details_t;

typedef enum
{
    ECU_PARSER_BYTE_ORDER_LITTLE_ENDIAN,
    ECU_PARSER_BYTE_ORDER_BIG_ENDIAN
} ecu_parser_byte_order_t;

typedef struct
{
    size_t start_bit;
    size_t length;
    float scale;
    uint64_t offset;
    float min_value;
    float max_value;

} ecu_parser_parameter_details_t;

typedef struct
{
    ecu_parser_protocol_name_t protocol_name;
    ecu_parser_protocol_details_t protocol_details;
} ecu_parser_protocol_info_t;

typedef union
{
    ecu_parser_obd2_service_t obd2_service;
    ecu_parser_uds_service_t uds_service;
    ecu_parser_j1939_service_t j1939_service;
} ecu_parser_service_t;

int ecu_parser_find_protocol(ecu_parser_raw_data_t raw_data, ecu_parser_protocol_info_t *protocol_info);
int ecu_parser_find_service(ecu_parser_protocol_info_t protocol_info, ecu_parser_service_t *ecu_parser_service);
int ecu_parser_find_parameter(ecu_parser_raw_data_t raw_data, ecu_parser_parameter_details_t parameter_details, ecu_parser_byte_order_t byte_order, float *value);

#endif // ECU_PARSER_H