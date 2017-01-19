#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t **makeArray16(uint32_t numRows, uint32_t numCols);
uint64_t **makeArray64(uint32_t numRows, uint32_t numCols);
void saveData(uint16_t **dataArray, uint64_t **timestampArray,
              uint32_t numSamples, uint8_t numChannels);
