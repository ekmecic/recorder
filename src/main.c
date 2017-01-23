#include "../lib/cmdline/cmdline.h"
#include "../lib/pru/pru.h"
#include "../lib/util/util.h"

#include <stdint.h>
#include <time.h>

int main(int argc, const char **argv) {
  uint32_t numSamples = 0;
  uint8_t numChannels = 0;
  uint16_t waitTime = 0;

  parseArguments(argc, argv, &numSamples, &numChannels, &waitTime);
  // Create our arrays that hold the sampled data and timestamps
  uint16_t **dataArray = makeArray16(numSamples, numChannels);
  uint64_t **timestampArray = makeArray64(numSamples, numChannels);

  // Configure the PRU and timestamps
  pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0);
  configurePRU(io, numChannels);
  struct timespec time;
  // Data capture routine
  for (uint32_t i = 0; i < numSamples; i++) {
    for (uint8_t j = 0; j <= numChannels; j++) {
      // Get the data from the PRU/ADC and save it to the data array
      dataArray[i][j] = io->Adc->Value[j];
      // Get a timestamp and save it to the timestamp array
      clock_gettime(CLOCK_REALTIME, &time);
      *timestampArray[i] = (int64_t)(time.tv_sec) * (int64_t)1000000000 +
                           (int64_t)(time.tv_nsec);
    }
  }

  // Copy all of the data from the arrays to a file
  saveData(dataArray, timestampArray, numSamples, numChannels);

  // Destroy the PRU object and free up the memory used by the arrays
  pruio_destroy(io);
  free(dataArray);
  free(timestampArray);

  return 0;
}
