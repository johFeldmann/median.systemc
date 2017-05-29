// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>


#ifndef MEDIAN_MOD_H
#define MEDIAN_MOD_H 

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES
  
#include "systemc.h"

#include <tlm.h>
#include "tlm_utils/simple_initiator_socket.h"

// Module implementing Median Filter
SC_MODULE(median_module)
{
  sc_in<bool> clk;

  // Module Interface
  sc_out<bool>  finish;  // indicates that operation is finished

  // Interface to Image Memory
  tlm_utils::simple_initiator_socket<median_module> socket;

  // Image Dimensions
  static const unsigned int width  = 100;
  static const unsigned int height = 100;

  void do_median(); // main function of median filter

  // helper function for sorting
  void CompareExchange(uint8_t* data);
  void Sort(uint8_t* data);

  // helper functions for reading/writing from/to memory (this is only a hint, you are free to remove these)
  unsigned char read_pixel(unsigned int x, unsigned int y);
  void write_pixel(unsigned char val, unsigned int x, unsigned int y);

  SC_CTOR(median_module) : socket("socket")  // Construct and name socket
  {
      SC_THREAD(do_median);
      sensitive << clk.pos();
  }
};

#endif // MEDIAN_MOD_H
