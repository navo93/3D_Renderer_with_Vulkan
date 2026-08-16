#include "CubeTextureSet.hpp"
#include <array>
#include <stdexcept>

CubeTextureSet CubeTextureSet::loadFromDirectory(const std::string &directory) {
  static const std::array<std::string, 6> filenames = {
      "Texturelabs_Brick_141M.jpg", "Texturelabs_Wood_169M.jpg",
      "Texturelabs_Stone_138M.jpg", "Texturelabs_Fabric_187M.jpg",
      "Texturelabs_Wood_134M.jpg", "Texturelabs_Wood_145M.jpg"};

  CubeTextureSet set{};
  set.images.reserve(filenames.size());
  for (const auto &filename : filenames) {
    set.images.push_back(ImageLoader::loadRgba(directory + "/" + filename));
  }

  set.width = set.images[0].width;
  set.height = set.images[0].height;
  set.channels = 4;
  for (const auto &image : set.images) {
    if (image.channels != 4) {
      throw std::runtime_error("Cube texture did not load as RGBA");
    }
    if (image.width <= 0 || image.height <= 0) {
      throw std::runtime_error("Cube texture has invalid dimensions");
    }
  }
  return set;
}
