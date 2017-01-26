#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  makeArray16 - Creates a heap-allocated array of 16-bit integers
                of size numRows x numCols.

  Inputs:
    1. numRows - The number of rows the array will have, typically
                 the number of samples to be taken.
    2. numCols - The number of columns the array will have, typically
                 the number of channels to be measured.

  Output:
    A heap-allocated array of 16-bit integers meant to store the
    ADC values for each sampled channel.
 */
uint16_t **makeArray16(uint32_t numRows, uint32_t numCols);

/*
  makeArray64 - Creates a heap-allocated array of 64-bit integers
                of size numRows x numCols.
                Ideally we'd have combine the 16- and 64-bit arrays
                into one, but the timestamps are in nanoseconds and don't
                fit into 16-bit integers.
  Inputs:
    1. numRows - The number of rows the array will have, typically
                 the number of samples to be taken.
    2. numCols - The number of columns the array will have, typically
                 just 1.

  Output:
    A heap-allocated array of 64-bit integers meant to store the
    timestamps for each sampling event.
 */
uint64_t **makeArray64(uint32_t numRows, uint32_t numCols);

/*
  getFilenameString - Creates a name for the CSV output file based
                      on the date/time of the recording.

  Inputs:
    None.

  Outputs:
    A 100 byte long string with the filename to be used for the output
    CSV file.
    It's the responsibility of the caller to free the allocated memory.
    Example: "1969-12-31_01:01:01_results.csv"
 */
char *getFilenameString();

/*
  saveData - Creates a file and dumps all of the recorded data
             to it in CSV format.
  Inputs:
    1. dataArray - The 16-bit array that holds the ADC values.
    2. timestampArray - The 64-bit array that holds the timestamps.
    3. numSamples - Number of samples taken.
    4. numChannels - Number of channels sampled.

  Outputs:
    A CSV file in the same directory as the executable containing
    timestamped ADC data from all of the sampled channels.
 */
void saveData(uint16_t **dataArray, uint64_t **timestampArray,
              uint32_t numSamples, uint8_t numChannels);
