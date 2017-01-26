#pragma once
#include "../../include/argparse/argparse.h"

static const char *const usage[] = {
    "recorder [options] [[--] args]", NULL,
};
/*
  parseArguments - Parses command line arguments and saves them to
                   variables used by the program.

  Inputs:
  1. argc and argv - The actual command line arguments.
  2. numSamples, numChannels, waitTime - The variables that are set
     through the command line.
     Note that they are passed by reference.

  Output:
    numSamples, numChannels and waitTime are modified in the function.
*/
void parseArguments(int argc, const char *argv[], uint32_t *numSamples,
                    uint8_t *numChannels, uint16_t *waitTime);
