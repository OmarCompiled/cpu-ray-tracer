#ifndef CPURAYTRACER_INCLUDE_CAMERA_H_
#define CPURAYTRACER_INCLUDE_CAMERA_H_

class Camera {
  public:
    void
    render(std::vector<uint8_t>& buffer, const HittableList& world) {
      initialize();

      for(int scanline = 0; scanline < imageHeight_; scanline++) {
        for(int pixel = 0; pixel < imageWidth_; pixel++) {
          Vec3 pixelCenter   = firstPixel_ + (pixel * pixelDeltaU_) + (scanline * pixelDeltaV_);
          Vec3 rayDirection  = pixelCenter - position_;
          Ray ray {position_, rayDirection};
          Color pixelColor = rayColor(ray, world);
          writePixelToBufferPNG(buffer, pixelColor);
        }
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
    setImageWidth(int value) {
      imageWidth_ = value; 
    }

    void
    setAspectRatio(float value) {
      aspectRatio_ = value;
    }

  private:
    float aspectRatio_ = 1.0f;
    int   imageWidth_  = 100;
    int   imageHeight_;
    Vec3  position_;
    Vec3  firstPixel_;
    Vec3  pixelDeltaU_;
    Vec3  pixelDeltaV_;

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
      }

    Color
    rayColor(const Ray& ray, const HittableList& world) {
      HitRecord hitRecord;
      if(world.hit(ray, Interval(0, math::infinity()), hitRecord)) {
        return 0.5f * (hitRecord.normal + Vec3(1.0f));
      }  

      float a = 0.5f * (ray.direction().normalized().y() + 1.0f); // -1.0f - 1.0f --> 0.0f - 1.0f
      return (1.0f - a)*Color(1.0f) + a*Color(0.5f, 0.7f, 1.0f); 
    }
};

#endif
