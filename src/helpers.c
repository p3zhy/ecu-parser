#include "helpers.h"
ecu_parser_identifier_type_t ecu_parser_check_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? ECU_PARSER_IDENTIFIER_TYPE_STANDARD : ECU_PARSER_IDENTIFIER_TYPE_EXTENDED;
}

