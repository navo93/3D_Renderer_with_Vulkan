/*

i will be using the stb_image.h standard library for taking image from the disk and uploading it to the ram of the cpu
*/
#pragma once
#include "stb_image.h"
#include <string>

//the LoadImage function shall take in the normal jpeg or png images from the disk and put it into the Ram
struct LoadedImage {
  int width{0};
  int height{0};
  int channels{0};
  stbi_uc *pixels{nullptr}; //pointer to the raw pixels in the ram

  ~LoadedImage();
  LoadedImage() = default; //no initial constructor and destructors and initiated here

  //disabling any copy constructors
  LoadedImage(const LoadedImage &) = delete;
  LoadedImage &operator=(const LoadedImage &) = delete;

  //enabling the move oerations
  LoadedImage(LoadedImage &&other) noexcept;
  LoadedImage &operator=(LoadedImage &&other) noexcept;
};


//this functions will load the 4k,hdr images from the disk to the cpu ram
struct LoadedFloatImage {
  int width{0};
  int height{0};
  int channels{0};

  float *pixels{nullptr}; //pointer to the pixel data on the cpu

  ~LoadedFloatImage();
  LoadedFloatImage() = default;

  //disabling copy constructors
  LoadedFloatImage(const LoadedFloatImage &) = delete;
  LoadedFloatImage &operator=(const LoadedFloatImage &) = delete;

//enabling move operations
  LoadedFloatImage(LoadedFloatImage &&other) noexcept;
  LoadedFloatImage &operator=(LoadedFloatImage &&other) noexcept;
};


//this calss shall contain the functions that will get the pixels from the disk to the ram

class ImageLoader {
public:
  static LoadedImage loadRgba(const std::string &path);
  static LoadedFloatImage loadFloat(const std::string &path);
};
