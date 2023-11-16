#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef enum ApplicationLayerProtocol
{
    APPLICATION_LAYER_PROTOCOL_J1939,
    APPLICATION_LAYER_PROTOCOL_CANOPEN,
    APPLICATION_LAYER_PROTOCOL_OBD2,
    APPLICATION_LAYER_PROTOCOL_UDS,
    APPLICATION_LAYER_PROTOCOL_LIN,
    APPLICATION_LAYER_PROTOCOL_NMEA2000,
    APPLICATION_LAYER_PROTOCOL_ISOBUS
} ApplicationLayerProtocol;

typedef enum IdentifierType
{
    IDENTIFIER_TYPE_STANDARD,
    IDENTIFIER_TYPE_EXTENDED,
} IdentifierType;

ApplicationLayerProtocol find_protocol(uint32_t identifier, unsigned char *data, int dataSize);
void parse_protocol(uint32_t identifier, unsigned char *data, int dataSize, ApplicationLayerProtocol protocol);
IdentifierType ckeck_identifier_type(uint32_t identifier);
#endif // ECU_PARSER_H