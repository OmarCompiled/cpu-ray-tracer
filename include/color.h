#ifndef CPURAYTRACER_INCLUDE_COLOR_H_
#define CPURAYTRACER_INCLUDE_COLOR_H_

#include <vector>

#include "../include/vec.h"
#include "../include/interval.h"

using Color = Vec3;

void
writePixelToBufferPNG(uint8_t* buffer, size_t index, const Color& pixel_color) {
  Interval intensity(0.0f, 0.999f);
  uint8_t r_byte = (uint8_t)(256 * intensity.clamp(pixel_color.x()));
  uint8_t g_byte = (uint8_t)(255 * intensity.clamp(pixel_color.y()));
  uint8_t b_byte = (uint8_t)(255 * intensity.clamp(pixel_color.z()));
  uint8_t a_byte = 255;

  buffer[index++] = r_byte;
  buffer[index++] = g_byte;
  buffer[index++] = b_byte;
  buffer[index]   = a_byte;
} 

#endif
