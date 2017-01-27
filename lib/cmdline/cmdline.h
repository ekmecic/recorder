#pragma once
#include "../../include/argparse/argparse.h"

/*
  parseArguments - Parses command line arguments and saves them to
                   variables used by the program.

  Inputs:
  1. argc and argv - The actual command line arguments.
  2. numMeasurements, numChannels, waitTime - The variables that are set
     through the command line.
     Note that they are passed by reference.

  Output:
    numMeasurements, numChannels and waitTime are modified in the function.
*/
void parseArguments(int argc, const char *argv[], uint32_t *numMeasurements,
                    uint8_t *numChannels, uint32_t *waitTime);
