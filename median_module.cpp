// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "median_module.h"

void median_module::do_median()
{
    unsigned char pixel[3][3];
    unsigned buffer[width-2][height-2];

    // Simple median
    for(int i = 0; i < width - 2; i++)
    {
        for(int j = 0; j < height - 2; j++)
        {
            // Read 3x3 pixel
            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    pixel[x][y] = read_pixel(i+x,j+y);
                }
            }

            // Sort pixel
            Sort(&pixel[0][0]);

            // Write back buffer
            write_pixel(pixel[1][1], i+1, j+1);

            // Write to buffer
            buffer[i][j] = pixel[1][1];
        }
    }

    for(int i = 0; i < width - 2; i++)
    {
        for(int j = 0; j < height - 2; j++)
        {
            // Write back buffer
            write_pixel(buffer[i][j], i+1, j+1);
        }
    }

    // Filtering done
    finish.write(true);

} // do_median()

unsigned char median_module::read_pixel(unsigned int x, unsigned int y)
{
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10, SC_NS);

    unsigned char pixel;

    trans->set_command(tlm::TLM_READ_COMMAND);
    trans->set_address(x*height+y);//x+width*y);
    trans->set_data_length(1);
    trans->set_streaming_width(4);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans->set_data_ptr(&pixel);

    socket->b_transport(*trans, delay );

    return pixel;
}

void median_module::write_pixel(unsigned char val, unsigned int x, unsigned int y)
{
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10, SC_NS);

    trans->set_command(tlm::TLM_WRITE_COMMAND);
    trans->set_address(x*height+y);//x+width*y);
    trans->set_data_length(1);
    trans->set_streaming_width(4);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans->set_data_ptr(&val);

    socket->b_transport(*trans, delay );
}

void median_module::CompareExchange(uint8_t* data)
{
    if(data[0] > data[1])
    {
        uint8_t temp = data[0];
        data[0] = data[1];
        data[1] = temp;
    }
}

void median_module::Sort(uint8_t* data)
{
    for(int i = 0; i < 5; i++)
    {
        CompareExchange(&data[0]);
        CompareExchange(&data[2]);
        CompareExchange(&data[4]);
        CompareExchange(&data[6]);

        CompareExchange(&data[1]);
        CompareExchange(&data[3]);
        CompareExchange(&data[5]);
        CompareExchange(&data[7]);
    }
}

