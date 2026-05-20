#include <vector>
#include <array>
#include <cstdint>
#include <memory>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/utilities.h"
#include "../include/vec.h"
#include "../include/color.h"
#include "../include/ray.h"
#include "../include/interval.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/camera.h"

int
main() {
  //NOTE: have to redesign buffering from vector to array
  Camera camera;
  camera.setImageWidth(1920);
  camera.setAspectRatio(16.0f / 9.0f);
  camera.setAntiAliasingSamplesPerPixel(10);
  camera.setMultiThreading();

  HittableList world;
  world.add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.3f));
  world.add(std::make_shared<Sphere>(Vec3(0,-100.3,-1), 100));
  
  camera.render(world);
  for(std::thread& t : camera.threads) {
    t.join();
  }

  stbi_write_png("image.png", camera.getImageWidth(), camera.getImageHeight(), 3, camera.buffer, camera.getImageWidth() * 3);

  return 0;
}
