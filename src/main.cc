#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/vec.h"
#include "../include/color.h"

int
main() {
  const int width = 800;
  const int height = 800;
  std::vector<uint8_t> buffer;

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      float r = i / (float) width;
      float g = j / (float) height;
      float b = 0.3f;

      color pixel_color = color(r, g, b);
      write_pixel_png(buffer, pixel_color);
    }
  }

  stbi_write_png("image.png", width, height, 3, buffer.data(), width * 3);

  return 0;
}
