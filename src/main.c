#include "../lib/cmdline/cmdline.h"
#include "../lib/pru/pru.h"
#include "../lib/util/util.h"

#include <stdint.h>
#include <time.h>
#include <unistd.h>

int main(int argc, const char **argv) {
  uint32_t numMeasurements = 0;
  uint8_t numChannels = 0;
  uint32_t waitTime = 0; // Time to wait between cycles in microsecs

  parseArguments(argc, argv, &numMeasurements, &numChannels, &waitTime);
  // Create our arrays that hold the sampled data and timestamps
  uint16_t **dataArray = makeArray16(numMeasurements, numChannels);
  uint64_t *timestampArray = makeArray64(numMeasurements);

  // Configure the PRU and timestamps
  pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0);
  configurePRU(io, numChannels);
  struct timespec time;
  // Data capture routine
  for (uint32_t i = 0; i < numMeasurements; i++) {
    for (uint8_t j = 0; j <= numChannels; j++) {
      // Get the data from the PRU/ADC and save it to the data array
      dataArray[i][j] = io->Adc->Value[j];
      // Get a timestamp and save it to the timestamp array
      clock_gettime(CLOCK_REALTIME, &time);
      timestampArray[i] = (int64_t)(time.tv_sec) * (int64_t)1000000000 +
                           (int64_t)(time.tv_nsec);
    }
    // Wait between cycles for waitTime usecs if the user wants to
    if (waitTime != 0) {
      usleep(waitTime);
    }
  }

  // Copy all of the data from the arrays to a file
  saveData(dataArray, timestampArray, numMeasurements, numChannels);

  // Destroy the PRU object and free up the memory used by the arrays
  pruio_destroy(io);
  free(dataArray);
  free(timestampArray);

  return 0;
}
