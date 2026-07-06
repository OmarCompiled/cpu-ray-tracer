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
#include "../include/material.h"
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
  camera.setMaxRayDepth(100);

  auto coralDiffuseMaterial = std::make_shared<material::Metal>(Color(1.0f, 0.5f, 0.3f), 0);
  auto groundMaterial       = std::make_shared<material::Lambertian>(Color(0.3f, 1.0f, 0.4f));

  auto sphere1      = std::make_shared<Sphere>(Vec3(0.0f, -1.0f, -5.0f), 1.0f, coralDiffuseMaterial);
  auto sphere2      = std::make_shared<Sphere>(Vec3(0.0f,  1.0f, -5.0f), 1.0f, coralDiffuseMaterial);
  auto groundSphere = std::make_shared<Sphere>(Vec3(0.0f, -102.0f, -5.0f), 100.0f, groundMaterial);

  HittableList world;
  world.add(sphere1);
  world.add(sphere2);
  world.add(groundSphere);
  
  camera.render(world);
  for(std::thread& t : camera.threads) {
    t.join();
  }

  stbi_write_png("image.png", camera.getImageWidth(), camera.getImageHeight(), 4, camera.buffer, camera.getImageWidth() * 4);

  return 0;
}
