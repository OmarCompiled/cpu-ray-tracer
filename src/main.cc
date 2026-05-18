#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/utilities.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/camera.h"

int
main() {
  std::vector<uint8_t> buffer; // uint8_t necessary for stb_image_write functions.

  HittableList world;
  world.add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.3f));
  world.add(std::make_shared<Sphere>(Vec3(0,-100.3,-1), 100));
  
  Camera camera;
  camera.setImageWidth(4096);
  camera.setAspectRatio(16.0f / 9.0f);
  camera.render(buffer, world);

  stbi_write_png("image.png", camera.getImageWidth(), camera.getImageHeight(), 3, buffer.data(), camera.getImageWidth()* 3);

  return 0;
}
