#include "ImageLoader.hpp"
#include <stdexcept>
#include <utility>

LoadedImage::~LoadedImage() {
  if (pixels) {
    stbi_image_free(pixels);
  }
}

LoadedImage::LoadedImage(LoadedImage &&other) noexcept
    : width(other.width), height(other.height), channels(other.channels),
      pixels(std::exchange(other.pixels, nullptr)) {}

LoadedImage &LoadedImage::operator=(LoadedImage &&other) noexcept {
    //to check if the object is assigned to itself
  if (this != &other) {
    if (this->pixels) {
      stbi_image_free(this->pixels);
    }
    this->width = other.width;
    this->height = other.height;
    this->channels = other.channels;
    this->pixels = std::exchange(other.pixels, nullptr);
  }
  return *this;
}

LoadedFloatImage::~LoadedFloatImage() {
  if (pixels) {
    stbi_image_free(pixels);
  }
}

LoadedFloatImage::LoadedFloatImage(LoadedFloatImage &&other) noexcept
    : width(other.width), height(other.height), channels(other.channels),
      pixels(std::exchange(other.pixels, nullptr)) {}

LoadedFloatImage &
LoadedFloatImage::operator=(LoadedFloatImage &&other) noexcept {
  if (this != &other) {
    if (this->pixels) {
      stbi_image_free(this->pixels);
    }
    this->width = other.width;
    this->height = other.height;
    this->channels = other.channels;
    this->pixels = std::exchange(other.pixels, nullptr);
  }
  return *this;
}

//this functions returns the LoadImage struct which contains handle to the pixels in the ram to a specific image<jpeg or png>
LoadedImage ImageLoader::loadRgba(const std::string &path) {
  LoadedImage image{};
  image.pixels =
      stbi_load(path.c_str(), &image.width, &image.height, &image.channels,
                STBI_rgb_alpha);
  if (!image.pixels) {
    throw std::runtime_error("Failed to load image: " + path);
  }
  image.channels = 4;
  return image;
}

//this functions returns the LoadFloatImage struct which contains handle to the pixels in the ram to a specific image<hdr>
LoadedFloatImage ImageLoader::loadFloat(const std::string &path) {
  LoadedFloatImage image{};
  image.pixels =
      stbi_loadf(path.c_str(), &image.width, &image.height, &image.channels, 0);
  if (!image.pixels) {
    throw std::runtime_error("Failed to load float image: " + path);
  }
  return image;
}
