#pragma once
#include "../../include/argparse/argparse.h"

static const char *const usage[] = {
    "recorder [options] [[--] args]", NULL,
};

void parseArguments(int argc, const char *argv[], uint32_t *numSamples,
                    uint8_t *numChannels, uint16_t *waitTime) {

  uint32_t _numSamples = 0;
  uint8_t _numChannels = 0;
  uint16_t _waitTime = 0;

  struct argparse_option options[] = {
      OPT_HELP(),
      OPT_GROUP("Basic options:"),
      OPT_INTEGER('s', "samples", &_numSamples, "Number of samples"),
      OPT_INTEGER('c', "channels", &_numChannels, "Number of channels"),
      OPT_INTEGER('w', "waittime", &_waitTime, "How much to delay samples"),
      OPT_END(),
  };

  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(
      &argparse,
      "\nrecorder records analog data on pins AIN-1-AIN6 at very fast speeds.",
      "\nMore information:"
      "\n    Wait time delays the sampling by <int> microseconds. If you don't "
      "\n    supply an argument the program will run as fast as possible. "
      "\n    Channels is a mandatory argument which selects how many analog"
      "\n    input pins will be read."
      "\n    Samples is a mandatory argument which selects how many samples"
      "\n    are taken. Try not to go over a few million or the BBB will"
      "\n    run out of RAM.");
  argc = argparse_parse(&argparse, argc, argv);

  if (_numSamples < 1 || _numSamples >= 20000000) {
    printf("ERROR: Invalid number of samples selected. Exiting now.\n");
    exit(-1);
  }
  if (_numChannels > 6 || _numChannels < 1) {
    printf("ERROR: Malformed channel selection. Exiting now.\n");
    exit(-1);
  }
  (*numSamples) = _numSamples;
  (*numChannels) = _numChannels;
  (*waitTime) = _waitTime;
}
