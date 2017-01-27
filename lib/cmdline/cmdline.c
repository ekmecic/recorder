#include "cmdline.h"

static const char *const usage[] = {
    "recorder [options] [[--] args]", NULL,
};

void parseArguments(int argc, const char *argv[], uint32_t *numMeasurements,
                    uint8_t *numChannels, uint32_t *waitTime) {
  uint32_t _numMeasurements = 0;
  uint8_t _numChannels = 0;
  uint32_t _waitTime = 0;

  // The flags that the program provides
  struct argparse_option options[] = {
      // clang-format off
      OPT_HELP(),
      OPT_GROUP("Basic options:"),
      OPT_INTEGER('m', "measurements", &_numMeasurements, "Number of measurements"),
      OPT_INTEGER('c', "channels", &_numChannels, "Number of channels"),
      OPT_INTEGER('w', "waittime", &_waitTime, "How much to delay measuerments"),
      OPT_END(),
      // clang-format on
  };

  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);

  // The description of the program that is printed when a user uses the
  // --help argument
  argparse_describe(
      &argparse,
      "\nrecorder records analog data on pins AIN-1-AIN6 at very fast speeds.",
      "\nMore information:"
      "\n    Wait time delays the measuring by <int> microseconds. If you don't"
      "\n    supply an argument the program will run as fast as possible."
      "\n    Channels is a mandatory argument which selects how many analog"
      "\n    input pins will be read."
      "\n    Measurements is a mandatory argument which selects how many"
      "\n    measurements are taken. Try not to go over a few million"
      "\n    or the BBB will run out of RAM.");
  argc = argparse_parse(&argparse, argc, argv);

  // Dumb sanity checks to make sure the inputs are valid
  if (_numMeasurements == 0 && numChannels == 0 && _waitTime == 0) {
    printf("ERROR: No arguments supplied. Use the --help flag for help."
           "Exiting now.\n");
    exit(-1);
  }
  // 20000000 as the max number of measurements is arbitrary, but increasing
  // it may cause the BBB to run out of memory during execution so be warned
  if (_numMeasurements < 1 || _numMeasurements > 10000000) {
    printf("ERROR: Invalid number of measurements selected. Exiting now.\n");
    exit(-1);
  }
  if (_numChannels > 7 || _numChannels < 1) {
    printf("ERROR: Malformed channel selection. Exiting now.\n");
    exit(-1);
  }
  (*numMeasurements) = _numMeasurements;
  (*numChannels) = _numChannels;
  (*waitTime) = _waitTime;
}
