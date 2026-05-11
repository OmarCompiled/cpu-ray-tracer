#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/vec.h"
#include "../include/color.h"
#include "../include/ray.h"

float aspect_ratio  = 16.0f / 9.0f;
int width           = 800;
int height          = (int)(width / aspect_ratio);
height = (height > 1) ? height : 1;

float focal_length    = 1.0f;
float viewport_height = 2.0f;
float viewport_width  = viewport_height * (float(width)/height); // since aspect_ratio is ideal not actual

vec3 camera_position {0.0f, 0.0f, 0.0f};

int
main() {
  std::vector<uint8_t> buffer; // uint8_t necessary for stb_image_write functions.

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      color pixel_color = {
       i / (float)width,
       j / (float)height, 
       0.0f
      };

      write_pixel_png(buffer, pixel_color);
    }
  }

  stbi_write_png("image.png", width, height, 3, buffer.data(), width * 3);

  return 0;
}
