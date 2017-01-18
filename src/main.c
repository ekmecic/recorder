#include "../include/libpruio/src/pruio.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 1
#endif

int main() {
  const uint8_t numChannels = 3;
  const uint32_t numSamples = 10000000;

  int rows = numSamples;
  int columns = numChannels;
  uint16_t **dataArray = (uint16_t **)malloc(rows * sizeof(uint16_t *));
  for (int i = 0; i < rows; i++) {
    dataArray[i] = (uint16_t *)malloc(columns * sizeof(uint16_t));
  }
  uint64_t **timestampArray = (uint64_t **)malloc(rows * sizeof(uint64_t *));
  for (int i = 0; i < rows; i++) {
    timestampArray[i] = (uint64_t *)malloc(columns * sizeof(uint64_t));
  }

  pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0);
  if (io->Errr) {
    printf("Initialization failed (%s)\n", io->Errr);
  }

  if (pruio_config(io, 1, 0x1FE, 0, 4)) {
    printf("Configuration failed failed (%s)\n", io->Errr);
  }

  // Configure 6 channels of data measurement, AIN-1 thru AIN-6
  for (int i = 0; i < (numChannels - 1); i++) {
    if (pruio_adc_setStep(io, (i + 10), i, 0, 0, 0)) {
      printf("AIN-%d configuration failed with error message %s", i, io->Errr);
    }
  }
  struct timespec time;

  // Data capture routine
  for (uint32_t i = 0; i < numSamples; i++) {
    for (uint8_t j = 1; j < numChannels; j++) {
      clock_gettime(CLOCK_REALTIME, &time);
      *timestampArray[i] = (int64_t)(time.tv_sec) * (int64_t)1000000000 + (int64_t)(time.tv_nsec);
      dataArray[i][j] = io->Adc->Value[j];
    }
  }

  FILE *datafile = fopen("output.txt", "w+");
  // Data dumping routine
  uint64_t initTime = *timestampArray[0];
  for (uint32_t i = 0; i < numSamples; i++) {
    // Subtract the init time from the timestamp to get timestamps relative to program init
    fprintf(datafile, "%llu,", *timestampArray[i] - initTime);
    for (int j = 0; j < numChannels; j++) {
      fprintf(datafile, "%d,", dataArray[i][j]);
    }
    // We do the last one separately to avoid a trailing comma/add a newline
    fprintf(datafile, "%d\n", dataArray[i][numChannels - 1]);
  }

  fclose(datafile);
  pruio_destroy(io);
  free(dataArray);
  free(timestampArray);

  return 0;
}
