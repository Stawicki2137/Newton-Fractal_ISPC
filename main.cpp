#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image_io.h"
#include "newton_ispc.h"

void usage(char ** argv) {
    std::cout << "Usage: " << argv[0] << " [n]" << std::endl;
}

int main(int argc, char **argv)
{
    int width  = 1655;
    int height = 1655;

    float x0 = -2.0f;
    float x1 =  2.0f;
    float y0 = -2.0f;
    float y1 =  2.0f;

    int   maxIterations = 50;
    float eps           = 1e-3f;

    int n = 5;
    if (argc == 2) {
        n = std::atoi(argv[1]);
        if (n < 2) {
            std::cerr << "Error: degree must be >= 2\n";
            usage(argv);
            return 1;
        }
    } else if (argc > 2) {
        usage(argv);
        return 1;
    }

    int *buf = new int[width * height];
    ispc::newton_fractal_ispc(x0, y0, x1, y1,
                        width, height,
                        maxIterations,
                        n, eps,
                        buf);

    writePPM(buf, width, height, n, maxIterations,
             "newton-ispc.ppm");

    delete[] buf;
    return 0;
}

