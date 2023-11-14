#include "ecu_parser.h"


void findProtocol(uint32_t id, unsigned char *data, int dataSize) {
    printf("Finding protocol with id: %u and data: ", id);
    for (int i = 0; i < dataSize; ++i) {
        printf("%02u ", data[i]);
    }
    printf("\n");
}

void parseProtocol() {
    printf("Parsing protocol...\n");
}