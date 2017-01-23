#include "util.h"

// The makeArray functions create 16/64bit arrays where the data and timestamps
// are stored. It's up to the caller to free them.
uint16_t **makeArray16(uint32_t numSamples, uint32_t numChannels) {
  uint16_t **array = (uint16_t **)malloc(numSamples * sizeof(uint16_t *));
  for (uint32_t i = 0; i < numSamples; i++) {
    array[i] = (uint16_t *)malloc((numChannels + 1) * sizeof(uint16_t));
  }
  return array;
}
uint64_t **makeArray64(uint32_t numSamples, uint32_t numChannels) {
  uint64_t **array = (uint64_t **)malloc(numSamples * sizeof(uint64_t *));
  for (uint32_t i = 0; i < numSamples; i++) {
    array[i] = (uint64_t *)malloc((numChannels + 1) * sizeof(uint64_t));
  }
  return array;
}

char *getFilenameString() {
  char *filenameString = malloc(100);
  time_t timer;
  struct tm *tm;
  time(&timer);
  tm = localtime(&timer);
  strftime(filenameString, 100, "%Y-%m-%d_%H:%M:%S_results.csv", tm);
  return filenameString;
}

void saveData(uint16_t **dataArray, uint64_t **timestampArray,
              uint32_t numSamples, uint8_t numChannels) {
  /* FILE *dataFile = fopen("output.txt", "w+"); */
  char *filenameString = getFilenameString();
  FILE *dataFile = fopen(filenameString, "w+");
  free(filenameString);

  uint64_t initTime = *timestampArray[0];
  for (uint32_t i = 0; i < numSamples; i++) {
    // Make timestamps relative to program init
    fprintf(dataFile, "%llu,", *timestampArray[i] - initTime);
    // Send the data to the text file
    for (int j = 1; j < numChannels; j++) {
      fprintf(dataFile, "%d,", dataArray[i][j]);
    }
    // We do the last one separately to avoid a trailing comma/add a newline
    fprintf(dataFile, "%d\n", dataArray[i][numChannels]);
  }
  // Close the file once we're done with it
  fclose(dataFile);
}
