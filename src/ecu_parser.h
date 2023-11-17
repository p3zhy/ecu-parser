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
    APPLICATION_LAYER_PROTOCOL_J1939,
    APPLICATION_LAYER_PROTOCOL_CANOPEN,
    APPLICATION_LAYER_PROTOCOL_OBD2,
    APPLICATION_LAYER_PROTOCOL_UDS,
    APPLICATION_LAYER_PROTOCOL_LIN,
    APPLICATION_LAYER_PROTOCOL_NMEA2000,
    APPLICATION_LAYER_PROTOCOL_ISOBUS,
    APPLICATION_LAYER_PROTOCOL_UNKNOWN
} application_layer_protocol_t;

typedef struct
{
    uint32_t identifier;
    uint8_t length;
    uint8_t mode;
    uint8_t pid;
    uint8_t data_bytes[5];
} obd2_frame_details_t;

typedef enum
{
    IDENTIFIER_TYPE_STANDARD,
    IDENTIFIER_TYPE_EXTENDED,
} identifier_type_t;

int find_protocol(uint32_t identifier, uint8_t *data, size_t data_size, application_layer_protocol_t *protocol);
void parse_protocol(uint32_t identifier, uint8_t *data, size_t data_size, application_layer_protocol_t protocol);
identifier_type_t ckeck_identifier_type(uint32_t identifier);
int get_obd_frame_details(uint32_t identifier, uint8_t *data, size_t data_size, obd2_frame_details_t *frame_details);

#endif // ECU_PARSER_H