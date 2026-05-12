#pragma once

#include <vector>

#include "vec.h"

using color = vec3;

void write_pixel_png(std::vector<uint8_t>& buffer, const color& pixel_color) {
  int r_byte = (int) (255.999f * pixel_color.x());
  int g_byte = (int) (255.999f * pixel_color.y());
  int b_byte = (int) (255.999f * pixel_color.z());
  
  buffer.push_back(r_byte);
  buffer.push_back(g_byte);
  buffer.push_back(b_byte);
} 
