#include "pru.h"

void configurePRU(pruIo *io, uint8_t numChannels) {
  if (io->Errr) {
    printf("Initialization failed (%s)\n", io->Errr);
  }

  if (pruio_config(io, 1, 0x1FE, 0, 4)) {
    printf("Configuration failed (%s)\n", io->Errr);
  }

  /* Configure 6 channels of data measurement, AIN-1 thru AIN-6 */
  for (uint8_t i = 0; i < numChannels; i++) {
    if (pruio_adc_setStep(io, (i + 10), (i + 1), 0, 0, 0)) {
      printf("AIN-%d configuration failed with error message %s", i, io->Errr);
    }
  }
}
