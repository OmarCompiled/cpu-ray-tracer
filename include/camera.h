#ifndef CPURAYTRACER_INCLUDE_CAMERA_H_
#define CPURAYTRACER_INCLUDE_CAMERA_H_

#include <vector>
#include <thread>

#include "../include/utilities.h"

enum AntialiasingSamplingType {
  SQUARE,
};

class Camera {
  public:
    uint8_t* buffer = new uint8_t[10];
    std::vector<std::thread> threads;

    void
    render(const HittableList& world) {
      if(multiThread_) {
        renderMultiThreaded(world);
      } else {
        renderSingleThreaded(world);
      }
    }     

    int
    getImageHeight() const {
        return imageHeight_;
      }

    int
    getImageWidth() const {
        return imageWidth_;
      }

    void
    setImageWidth(int imageWidth) {
        imageWidth_ = imageWidth; 
      }

    void
    setAspectRatio(float aspectRatio) {
        aspectRatio_ = aspectRatio;
      }
    
    void
    setAntiAliasingSamplesPerPixel(int samples) {
      samplesPerPixel_ = samples;
      pixelSampleScale_ = 1.0f / samples;
    }

    void
    setAntiAliasingSamplingType(AntialiasingSamplingType samplingType) {
      samplingType_ = samplingType;
    }

    void
    setMultiThreading(bool state = true) {
      multiThread_ = state;
    }

    void
    setMaxRayDepth(int depth) {
      maxRayDepth_ = depth;
    }

    ~Camera() {
      delete[] buffer;
    }

  private:
    float aspectRatio_ = 1.0f;
    int   imageWidth_  = 100;
    int   imageHeight_;
    Vec3  position_;
    Vec3  firstPixel_;
    Vec3  pixelDeltaU_;
    Vec3  pixelDeltaV_;
    int   samplesPerPixel_ = 1;
    int   maxRayDepth_ = 10;
    float pixelSampleScale_ = 1.0f / samplesPerPixel_;
    AntialiasingSamplingType samplingType_ = SQUARE;
    bool  multiThread_ = false;

    void
    initialize() {
        imageHeight_ = (int)(imageWidth_ / aspectRatio_);
        imageHeight_ = imageHeight_ < 1 ? 1 : imageHeight_;

        position_ = Vec3(0.0f, 0.0f, 0.0f);

        float focalLength    = 1.0f;
        float viewportHeight = 2.0f;
        float viewportWidth  = viewportHeight * (float(imageWidth_)/imageHeight_); // since aspect_ratio is ideal not actual

        //NOTE: Right-handed coordinates in use
        Vec3 viewportU {viewportWidth, 0.0f, 0.0f};
        Vec3 viewportV {0.0f, -viewportHeight, 0.0f}; // using screen coordinates; y top --> bottom
        Vec3 viewportOrigin   = position_ - Vec3(0.0f, 0.0f, focalLength) - viewportU/2 - viewportV/2;

        pixelDeltaU_      = viewportU / imageWidth_;
        pixelDeltaV_      = viewportV / imageHeight_;
        firstPixel_       = viewportOrigin + 0.5 * (pixelDeltaU_ + pixelDeltaV_);
        
        delete[] buffer;
        buffer = new uint8_t[imageWidth_ * imageHeight_ * 4];
    }

    Ray
    getRay(int pixel, int scanline) {
      Vec3 offset = sampleSquare(); 
      Vec3 pixelSample = firstPixel_ + ((pixel + offset.x()) * pixelDeltaU_) + ((scanline + offset.y()) * pixelDeltaV_);
      return Ray(position_, pixelSample - position_);
    }

    Vec3
    sampleSquare() {
      return Vec3(math::random() - 0.5f, math::random() - 0.5f, 0.0f);
    }

    Color
    rayColor(const Ray& ray, int depth, const HittableList& world) {
        if(depth <= 0) {
          return Color(0.0f);
        }

        HitRecord hitRecord;
        if(world.hit(ray, Interval(0.001f, math::infinity()), hitRecord)) {
          Vec3 direction = hitRecord.normal + vector::utilities::randomUnitVector();
          return 0.5f * rayColor(Ray(hitRecord.point, direction), --depth, world);
        }  

        float a = 0.5f * (ray.direction().normalized().y() + 1.0f); // -1.0f - 1.0f --> 0.0f - 1.0f
        return (1.0f - a)*Color(1.0f) + a*Color(0.5f, 0.7f, 1.0f); 
    }

    void
    renderSingleThreaded(const HittableList& world) {
      initialize();

      for(int scanline = 0; scanline < imageHeight_; scanline++) {
        for(int pixel = 0; pixel < imageWidth_; pixel++) {
          int pixelIndex = (pixel + scanline * imageWidth_) * (ImageFormat::PNG::RGBA);
          Color pixelColor {0.0f};
          for(int sample = 0; sample < samplesPerPixel_; sample++) {
            Ray ray = getRay(pixel, scanline);
            pixelColor += rayColor(ray, maxRayDepth_, world);
          }
          writePixelToBufferPNG(buffer, pixelIndex, pixelSampleScale_ *  pixelColor);
        }
      }          
    }

    void
    renderMultiThreaded(const HittableList& world) {
      initialize();

      for(int scanline = 0; scanline < imageHeight_; scanline++) {
        threads.emplace_back([&, scanline]() {
          for(int pixel = 0; pixel < imageWidth_; pixel++) {
            int pixelIndex = (pixel + scanline * imageWidth_) * (ImageFormat::PNG::RGBA);
            Color pixelColor {0.0f};
            for(int sample = 0; sample < samplesPerPixel_; sample++) {
              Ray ray = getRay(pixel, scanline);
              pixelColor += rayColor(ray, maxRayDepth_, world);
            }
            writePixelToBufferPNG(buffer, pixelIndex, pixelSampleScale_ *  pixelColor);
          }
        });
      }          
    }
};

#endif
