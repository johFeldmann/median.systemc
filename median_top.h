// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#ifndef MEDIAN_TOP_H
#define MEDIAN_TOP_H   
// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

#include <tlm.h>
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include "median_module.h"
#include "memory.h"

// Toplevel Module of Median-Filter and Image-Memory
SC_MODULE(median_top)
{

  // TODO: Define the module here (For Interface refer to Interface Definitions/Bindings in main.cpp and median_tb.h)

  // constructor function
  void init();

public:
  SC_CTOR(median_top)
    {
    init();
  }
};

#endif // MEDIAN_TOP_H
