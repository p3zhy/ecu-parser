#ifndef ECU_PARSER_TYPES_H
#define ECU_PARSER_TYPES_H
#include <stdint.h>

typedef struct
{
    uint32_t identifier;
    uint8_t data[8];
} ecu_parser_raw_data_t;

typedef enum
{
    ECU_PARSER_IDENTIFIER_TYPE_STANDARD,
    ECU_PARSER_IDENTIFIER_TYPE_EXTENDED,
} ecu_parser_identifier_type_t;

#endif