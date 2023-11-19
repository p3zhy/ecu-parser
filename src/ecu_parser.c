#include "ecu_parser.h"

int find_protocol(uint32_t identifier, uint8_t *data, size_t data_size, application_layer_protocol_t *protocol)
{

    if (ckeck_identifier_type(identifier) == IDENTIFIER_TYPE_STANDARD)
    {
        // Based on ISO 15765-4
        if ((identifier == 0x7DF) || ((identifier >= 0x7E0) && (identifier <= 0x7EF)))
        {
            obd2_frame_details_t obd2_frame_detail;
            if (get_obd2_frame_details(identifier, data, data_size, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                *protocol = APPLICATION_LAYER_PROTOCOL_OBD2;
                return EXIT_SUCCESS;
            }
        }
    }
    else
    {
        if ((identifier == 0x18DB33F1) || ((identifier >= 0x18DAF100) && (identifier <= 0x18DAF1FF)))
        {
            obd2_frame_details_t obd2_frame_detail;
            if (get_obd2_frame_details(identifier, data, data_size, &obd2_frame_detail))
                return EXIT_FAILURE;
            if ((obd2_frame_detail.mode <= 0x0A && obd2_frame_detail.mode >= 0x01) || (obd2_frame_detail.mode <= 0x4A && obd2_frame_detail.mode >= 0x41))
            {
                *protocol = APPLICATION_LAYER_PROTOCOL_OBD2;
                return EXIT_SUCCESS;
            }
        }
    }
    *protocol = APPLICATION_LAYER_PROTOCOL_UNKNOWN;
    return EXIT_SUCCESS;
}

void parse_protocol(uint32_t identifier, uint8_t *data, size_t data_size, application_layer_protocol_t protocol)
{
    printf("Parsing protocol...\n");
}

identifier_type_t ckeck_identifier_type(uint32_t identifier)
{

    return (identifier <= 0x7FF) ? IDENTIFIER_TYPE_STANDARD : IDENTIFIER_TYPE_EXTENDED;
}

int get_obd2_frame_details(uint32_t identifier, uint8_t *data, size_t data_size, obd2_frame_details_t *frame_details)
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

int get_uds_frame_details(uint32_t identifier, uint8_t *data, size_t data_size, uds_frame_details_t *frame_details)
{

    if (data_size < 4)
    {
        return EXIT_FAILURE;
    }

    frame_details->identifier = identifier;
    frame_details->protocol_control_information = data[0];
    frame_details->service_id = data[1];
    frame_details->sub_function = data[2];
    memcpy(frame_details->data_bytes, &data[3], data_size - 3);
    return EXIT_SUCCESS;
}