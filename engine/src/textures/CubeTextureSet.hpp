/*
this file shall contain a struct that will hold all the textures,that is to be applied to the cubes

*/
#pragma once
#include "ImageLoader.hpp"
#include <string>
#include <vector>

struct CubeTextureSet {
  std::vector<LoadedImage> images;
  //--------------------------------
  //these widht,height are to standardise the width and height,beacuse the actual textures can be of different width and height
  int width{0};
  int height{0};
  int channels{0};
  //---------------------------------------`

  static CubeTextureSet loadFromDirectory(const std::string &directory);//this functions returns the CubeTextureSEt object with all the
  //textures needed that i will apply to the cube's 6 faces
};
