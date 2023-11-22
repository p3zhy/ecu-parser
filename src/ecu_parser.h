#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    PROTOCOL_NAME_J1939,
    PROTOCOL_NAME_CANOPEN,
    PROTOCOL_NAME_OBD2,
    PROTOCOL_NAME_UDS,
    PROTOCOL_NAME_LIN,
    PROTOCOL_NAME_NMEA2000,
    PROTOCOL_NAME_ISOBUS,
    PROTOCOL_NAME_UNKNOWN
} protocol_name_t;

typedef struct
{
    uint32_t identifier;
    uint8_t length;
    uint8_t mode;
    uint8_t pid;
    uint8_t data_bytes[5];
} obd2_frame_details_t;

typedef struct
{
    uint32_t identifier;
    uint8_t protocol_control_information;
    uint8_t service_id;
    uint8_t sub_function;
    uint8_t data_bytes[5];
} uds_frame_details_t;

typedef union
{
    obd2_frame_details_t obd2_details;
    uds_frame_details_t uds_details;
} protocol_details_t;

typedef enum
{
    IDENTIFIER_TYPE_STANDARD,
    IDENTIFIER_TYPE_EXTENDED,
} identifier_type_t;

typedef struct
{
    uint8_t start_bit;
    uint8_t length;
    float scale;
    uint64_t offset;
    float min_value;
    float max_value;
} parser_details_t;

typedef struct
{
    protocol_name_t protocol_name;
    protocol_details_t protocol_details;
} protocol_info_t;

int find_protocol(uint32_t identifier, const uint8_t *data, size_t data_size, protocol_info_t *protocol_info);
int parse_protocol(uint32_t identifier, const uint8_t *data, size_t data_size, protocol_info_t protocol_info, parser_details_t parser_details);
identifier_type_t check_identifier_type(uint32_t identifier);
int get_obd2_frame_details(uint32_t identifier, const uint8_t *data, size_t data_size, obd2_frame_details_t *frame_details);
int get_uds_frame_details(uint32_t identifier, const uint8_t *data, size_t data_size, uds_frame_details_t *frame_details);

#endif // ECU_PARSER_H