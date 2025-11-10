//
// Created by mateusz2137 on 11/10/25.
//

#include "image_io.h"
// image_io.cpp
#include "image_io.h"
#include <cmath>
#include <algorithm>

void writePPM(int *buf, int width, int height,
              int n, int maxIterations,
              const char *fn)
{
    FILE *fp = std::fopen(fn, "wb");
    if (!fp) {
        std::printf("Couldn't open a file '%s'\n", fn);
        std::exit(-1);
    }

    std::fprintf(fp, "P6\n");
    std::fprintf(fp, "%d %d\n", width, height);
    std::fprintf(fp, "255\n");

    const float PI = 3.1415926535f;

    for (int i = 0; i < width * height; ++i) {
        int packed = buf[i];

        unsigned char r = 0, g = 0, b = 0;

        if (packed >= 0) {
            int rootIndex = packed >> 16;
            int iter      = packed & 0xFFFF;

            float h = (n > 0) ? (float)rootIndex / (float)n : 0.0f;

            float rc = 0.5f + 0.5f * std::cos(2.0f * PI * (h + 0.0f));
            float gc = 0.5f + 0.5f * std::cos(2.0f * PI * (h - 1.0f / 3.0f));
            float bc = 0.5f + 0.5f * std::cos(2.0f * PI * (h - 2.0f / 3.0f));

            float brightness = 1.0f - (float)iter / (float)maxIterations;
            brightness = std::clamp(brightness, 0.0f, 1.0f);

            float Rf = rc * brightness;
            float Gf = gc * brightness;
            float Bf = bc * brightness;

            r = (unsigned char)std::clamp(Rf * 255.0f, 0.0f, 255.0f);
            g = (unsigned char)std::clamp(Gf * 255.0f, 0.0f, 255.0f);
            b = (unsigned char)std::clamp(Bf * 255.0f, 0.0f, 255.0f);
        }

        std::fputc(r, fp);
        std::fputc(g, fp);
        std::fputc(b, fp);
    }

    std::fclose(fp);
    std::printf("Wrote image file %s\n", fn);
}
