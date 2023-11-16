#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

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

ApplicationLayerProtocol findProtocol(uint32_t id, unsigned char *data, int dataSize);
void parseProtocol(uint32_t id, unsigned char *data, int dataSize, ApplicationLayerProtocol protocol);

#endif // ECU_PARSER_H