#include "../include/libpruio/src/pruio.h"
#include "stdio.h"
#include <stdint.h>
#include <unistd.h>

int main() {
  pruIo *io =
      pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1); //! create new driver structure

  if (io->Errr) {
    printf("initialisation failed (%s)\n", io->Errr);
  }

  if (pruio_config(io, 1, 0x1FE, 0, 4)) {
    printf("config failed (%s)\n", io->Errr);
  }

  FILE *datafile = fopen("output.dat", "w+");
  uint32_t i = 0;
  while (i < 2000) {
    fprintf(datafile, "%d,%d,%d,%d\n", i,
            io->Adc->Value[0],
            io->Adc->Value[1],
            io->Adc->Value[2]
            );
    i += 1;
    usleep(500);
  }

  fclose(datafile);
  pruio_destroy(io);

  return 0;
}
