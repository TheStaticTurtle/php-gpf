
#ifndef PHP_PGF_DECODE_H
#define PHP_PGF_DECODE_H

#include <string>
#include <stdexcept>

#include "PGFimage.h"
#include "PGFstream.h"
#include "PGFtypes.h"

#include "lodepng.h"

struct rgba_image {
    uint8_t* data;
    uint32_t width;
    uint32_t height;
    uint8_t byte_per_pixel;
    
    size_t size() const { return width * height * byte_per_pixel; }
    size_t pitch() const { return width * byte_per_pixel; }
    void allocate() { data = (uint8_t*)malloc(width * height * byte_per_pixel); }
};

rgba_image pgf_decode_to_rgba(const std::string& input, int level);
rgba_image pgf_decode_to_rgba(const std::string& input);

std::string pgf_decode_to_png(const std::string& input, int level);
std::string pgf_decode_to_png(const std::string& input);


#endif /* PHP_PGF_DECODE_H */