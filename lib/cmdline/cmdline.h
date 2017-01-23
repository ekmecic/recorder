#pragma once
#include "../../include/argparse/argparse.h"

static const char *const usage[] = {
    "recorder [options] [[--] args]", NULL,
};

void parseArguments(int argc, const char *argv[], uint32_t *numSamples,
                    uint8_t *numChannels, uint16_t *waitTime);
