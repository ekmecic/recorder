#include "util.h"

// The makeArray functions create 16/64bit arrays where the data and timestamps
// are stored. It's up to the caller to free them.
uint16_t **makeArray16(const uint32_t numSamples, const uint32_t numChannels) {
  uint16_t **array = (uint16_t **)malloc(numSamples * sizeof(uint16_t *));
  for (uint32_t i = 0; i < numSamples; i++) {
    array[i] = (uint16_t *)malloc(numChannels * sizeof(uint16_t));
  }
  return array;
}
uint64_t **makeArray64(const uint32_t numSamples, const uint32_t numChannels) {
  uint64_t **array = (uint64_t **)malloc(numSamples * sizeof(uint64_t *));
  for (uint32_t i = 0; i < numSamples; i++) {
    array[i] = (uint64_t *)malloc(numChannels * sizeof(uint64_t));
  }
  return array;
}

void saveData(uint16_t **dataArray, uint64_t **timestampArray,
              const uint32_t numSamples, const uint8_t numChannels) {
  FILE *datafile = fopen("output.txt", "w+");
  uint64_t initTime = *timestampArray[0];
  for (uint32_t i = 0; i < numSamples; i++) {
    // Make timestamps relative to program init
    fprintf(datafile, "%llu,", *timestampArray[i] - initTime);
    // Send the data to the text file
    for (int j = 0; j < numChannels; j++) {
      fprintf(datafile, "%d,", dataArray[i][j]);
    }
    // We do the last one separately to avoid a trailing comma/add a newline
    fprintf(datafile, "%d\n", dataArray[i][numChannels - 1]);
  }
  // Close the file once we're done with it
  fclose(datafile);
}
