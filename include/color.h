#ifndef CPURAYTRACER_INCLUDE_COLOR_H_
#define CPURAYTRACER_INCLUDE_COLOR_H_

#include <vector>

#include "../include/vec.h"
#include "../include/interval.h"

using Color = Vec3;

inline float
linearToGamma(float linearComponent) {
  if(linearComponent > 0.0f) {
    return std::pow(linearComponent, 1.0f/2.2f);
  }

  return 0.0f;
}

void
writePixelToBufferPNG(uint8_t* buffer, size_t index, const Color& pixelColor) {
  float r = pixelColor.x();
  float g = pixelColor.y();
  float b = pixelColor.z();

  r = linearToGamma(r);
  g = linearToGamma(g);
  b = linearToGamma(b);

  Interval intensity(0.0f, 0.999f);
  uint8_t r_byte = (uint8_t)(256 * intensity.clamp(r));
  uint8_t g_byte = (uint8_t)(255 * intensity.clamp(g));
  uint8_t b_byte = (uint8_t)(255 * intensity.clamp(b));
  uint8_t a_byte = 255;

  buffer[index++] = r_byte;
  buffer[index++] = g_byte;
  buffer[index++] = b_byte;
  buffer[index]   = a_byte;
} 

#endif
