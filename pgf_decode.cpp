
#include "pgf_decode.hpp"

rgba_image pgf_decode_to_rgba(const std::string& input, int level) {
    int channel_map[] = {2, 1, 0, 3};  // hardcode to RGBA channels
    
    auto* pgf_stream = new CPGFMemoryStream((UINT8*)input.c_str(), input.size());
    auto* pgf_image = new CPGFImage();
    pgf_image->Open(pgf_stream);
    pgf_image->Read(level);
    
    rgba_image img {
            nullptr,
            pgf_image->Width(level),
            pgf_image->Height(level),
            4
    };
    img.allocate();
    
    pgf_image->GetBitmap(img.pitch(), img.data, 8 * img.byte_per_pixel, channel_map);
    
    return img;
}
rgba_image pgf_decode_to_rgba(const std::string& input) { return pgf_decode_to_rgba(input, 0); }

std::string pgf_decode_to_png(const std::string& input, int level) {
    auto rgba_image = pgf_decode_to_rgba(input, level);
    
    uint8_t* output;
    size_t output_size;
    
    auto error = lodepng_encode32(&output, &output_size, rgba_image.data, rgba_image.width, rgba_image.height);
    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
    }
    
    return std::string{(char*)output, output_size};
}
std::string pgf_decode_to_png(const std::string& input) { return pgf_decode_to_png(input, 0); }
