#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef enum ApplicationLayerProtocol
{
    J1939_APPLICATION_LAYER_PROTOCOL,
    CANOPEN_APPLICATION_LAYER_PROTOCOL,
    OBD2_APPLICATION_LAYER_PROTOCOL,
    UDS_APPLICATION_LAYER_PROTOCOL,
    LIN_APPLICATION_LAYER_PROTOCOL,
    NMEA2000_APPLICATION_LAYER_PROTOCOL,
    ISOBUS_APPLICATION_LAYER_PROTOCOL
} ApplicationLayerProtocol;

typedef enum IdentifierType
{
    StandardIdentifierType,
    ExtendedIdentifierType,
} IdentifierType;

ApplicationLayerProtocol find_protocol(uint32_t identifier, unsigned char *data, int dataSize);
void parse_protocol(uint32_t identifier, unsigned char *data, int dataSize, ApplicationLayerProtocol protocol);
IdentifierType ckeck_identifier_type(uint32_t identifier);
#endif // ECU_PARSER_H