#ifndef ECU_PARSER_H
#define ECU_PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
void findProtocol(uint32_t id, unsigned char *data, int dataSize);
void parseProtocol();

#endif // ECU_PARSER_H