
#ifndef PHP_PGF_DECODE_H
#define PHP_PGF_DECODE_H

#include <string>

#include "PGFimage.h"
#include "PGFstream.h"

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


#ifdef HAVE_PGF_TO_PNG
#include "lodepng.h"

std::string pgf_decode_to_png(const std::string& input, int level);
std::string pgf_decode_to_png(const std::string& input);
#endif


#endif /* PHP_PGF_DECODE_H */