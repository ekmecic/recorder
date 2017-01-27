#include "util.h"

uint16_t **makeArray16(uint32_t numRows, uint32_t numCols) {
  uint16_t **array = (uint16_t **)malloc(numRows * sizeof(uint16_t *));
  for (uint32_t i = 0; i < numRows; i++) {
    array[i] = (uint16_t *)malloc((numCols + 1) * sizeof(uint16_t));
  }
  return array;
}

uint64_t *makeArray64(uint32_t numMeasurements) {
  uint64_t *array = (uint64_t *)malloc(sizeof(uint64_t) * numMeasurements);
  return array;
}

char *getFilenameString() {
  char *filenameString = malloc(100);
  // Set up the time structs and get a timestamp
  time_t timer;
  struct tm *tm;
  time(&timer);
  tm = localtime(&timer);
  // Format the time in the way we want and return it
  strftime(filenameString, 100, "%Y-%m-%d_%H:%M:%S_results.csv", tm);
  return filenameString;
}

void saveData(uint16_t **dataArray, uint64_t *timestampArray,
              uint32_t numMeasurements, uint8_t numChannels) {
  char *filenameString = getFilenameString();
  FILE *dataFile = fopen(filenameString, "w+");
  free(filenameString);

  uint64_t initTime = timestampArray[0];
  for (uint32_t i = 0; i < numMeasurements; i++) {
    // Make timestamps relative to program init
    fprintf(dataFile, "%llu,", timestampArray[i] - initTime);
    // Copy the data to the text file
    for (int j = 1; j < numChannels; j++) {
      fprintf(dataFile, "%d,", dataArray[i][j]);
    }
    // We do the last one separately to avoid a trailing comma/add a newline
    fprintf(dataFile, "%d\n", dataArray[i][numChannels]);
  }
  // Close the file once we're done with it
  fclose(dataFile);
}
