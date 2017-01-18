#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t **makeArray16(const uint32_t numRows, const uint32_t numCols);
uint64_t **makeArray64(const uint32_t numRows, const uint32_t numCols);
void saveData(uint16_t **dataArray, uint64_t **timestampArray,
              const uint32_t numSamples, const uint8_t numChannels);
