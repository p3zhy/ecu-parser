#ifndef ECU_PARSER_TYPES_H
#define ECU_PARSER_TYPES_H
#include <stdint.h>

typedef struct
{
    uint32_t identifier;
    uint8_t data[8];
} ecu_parser_raw_data_t;
#endif