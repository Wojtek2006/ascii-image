#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../inc/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../inc/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../inc/stb_image_resize2.h"


int main(void) {
 
    char ASCII_CHARS[] = {'@', '%', '#', '*', '+', '=', '-', ':', '.', '`'};


    // LOAD IMAGE
    int width, height, channels;
    unsigned char *img = stbi_load("img/linux.png", &width, &height, &channels, 0);

    if (img == NULL) {
        printf("Image not loaded");
    }
    printf("Image loaded with size %dpx on %dpx with %d channels\n", width, height, channels);

    size_t img_size = width * height * channels;

    // RESIZE IMAGE
    int resized_w = 120;
    // float ratio = width/height;
    int resized_h = 60;

    unsigned char *res_img = (unsigned char *)malloc(resized_w * resized_h * channels);

    stbir_resize_uint8_linear(img, width, height, width * channels, res_img, resized_w, resized_h, resized_w * channels, STBIR_RGB);

    size_t res_img_size = resized_w * resized_h * channels;

    // TURN TO GRAYSCALE
    // Grayscale has one or two channels depending
    // on occurence of alpha channel on colored image
    int gray_scale_channels = channels == 4 ? 2 : 1;

    size_t gray_img_size = resized_w * resized_h * gray_scale_channels;

    unsigned char *gray_img = (unsigned char *)malloc(gray_img_size);

    for (unsigned char *p = res_img, *pg = gray_img; p != res_img + res_img_size; p += channels, pg += gray_scale_channels) {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
        if (gray_scale_channels == 4) {
            *(pg + 1) = *(p + 3);
        }
    }

    // stbi_write_jpg("grey_planet.jpg", resized_w, resized_h, );

    char ascii_image = {};
    int curr_pixel = 1;

    for (unsigned char *p = gray_img; p != gray_img + gray_img_size; p += gray_scale_channels, curr_pixel++) {
        if (curr_pixel % (resized_w) == 0) {
            std::cout << std::endl;
        }

        int index = *p / 26;
        std::cout << ASCII_CHARS[index];
    }

    stbi_image_free(img);

    return 0;
}