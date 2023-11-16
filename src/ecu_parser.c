#include "ecu_parser.h"

ApplicationLayerProtocol find_protocol(uint32_t identifier, unsigned char *data, int dataSize)
{
    printf("Finding protocol with identifier: %u and data: ", identifier);
    for (int i = 0; i < dataSize; ++i)
    {
        printf("%02u ", data[i]);
    }
    printf("\n");

    return APPLICATION_LAYER_PROTOCOL_OBD2;
}

void parse_protocol(uint32_t identifier, unsigned char *data, int dataSize, ApplicationLayerProtocol protocol)
{
    printf("Parsing protocol...\n");
}

IdentifierType ckeck_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? IDENTIFIER_TYPE_STANDARD : IDENTIFIER_TYPE_EXTENDED;
}
