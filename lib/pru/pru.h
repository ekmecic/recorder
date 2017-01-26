#pragma once
#include "../../include/libpruio/src/pruio.h"
#include <stdint.h>
#include <stdio.h>

/*
  configurePRU - Initialize and set up the PRU and ADC.
  Inputs:
    1. pruIO - PRU object provided by libpruio.
    2. numChannels - The number of channels that are being sampled.
 */
void configurePRU(pruIo *io, uint8_t numChannels);
