#include "ecu_parser.h"

ApplicationLayerProtocol findProtocol(uint32_t id, unsigned char *data, int dataSize)
{
    printf("Finding protocol with id: %u and data: ", id);
    for (int i = 0; i < dataSize; ++i)
    {
        printf("%02u ", data[i]);
    }
    printf("\n");
    return OBD2_APPLICATION_LAYER_PROTOCOL;
}

void parseProtocol(uint32_t id, unsigned char *data, int dataSize, ApplicationLayerProtocol protocol)
{
    printf("Parsing protocol...\n");
}