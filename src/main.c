#include "../include/libpruio/src/pruio.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  const uint8_t numChannels = 2;
  const uint32_t numSamples = 25000;
  uint16_t dataArray[numSamples][numChannels];

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

  struct timeval  tv1, tv2;
  gettimeofday(&tv1, NULL);
  // Data capture routine
  for (int i = 0; i < numSamples; i++) {
    for (int j = 0; j < numChannels; j++) {
      dataArray[i][j] = io->Adc->Value[j + 1];
    }
    usleep(10);
  }
  gettimeofday(&tv2, NULL);

  printf ("Total time to capture %d samples was %f seconds\n",
          numSamples,
          (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
          (double) (tv2.tv_sec - tv1.tv_sec));

  FILE *datafile = fopen("output.txt", "w+");
  // Data dumping routine
  for (int i = 0; i < numSamples; i++) {
    fprintf(datafile, "%d,", i);
    for (int j = 0; j < (numChannels - 1); j++) {
      fprintf(datafile, "%d,", dataArray[i][j]);
    }
    // We do the last one separately to avoid a trailing comma/add a newline
    fprintf(datafile, "%d\n", dataArray[i][numChannels - 1]);
  }

  fclose(datafile);
  pruio_destroy(io);

  return 0;
}
