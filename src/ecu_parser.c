#include "ecu_parser.h"

application_layer_protocol_t find_protocol(uint32_t identifier, uint8_t *data, size_t data_size)
{

    // Based on ISO 15765-4
    if ((identifier == 0x7DF) || ((identifier >= 0x7E0) && (identifier <= 0x7EF)))
    {
    }

    return APPLICATION_LAYER_PROTOCOL_UNKNOWN;
}

void parse_protocol(uint32_t identifier, uint8_t *data, size_t data_size, application_layer_protocol_t protocol)
{
    printf("Parsing protocol...\n");
}

identifier_type_t ckeck_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? IDENTIFIER_TYPE_STANDARD : IDENTIFIER_TYPE_EXTENDED;
}

int get_obd_frame_details(uint32_t identifier, uint8_t *data, size_t data_size, obd2_frame_details_t *frame_details)
{
    // Based on ISO 15031-5
    if (data_size < 4)
    {
        return EXIT_FAILURE;
    }
    frame_details->identifier = identifier;
    frame_details->length = data[0];
    frame_details->mode = data[1];
    frame_details->pid = data[2];
    memcpy(frame_details->data_bytes, &data[3], data_size - 3);
    return EXIT_SUCCESS;
}
