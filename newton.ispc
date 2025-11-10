
static inline int newton(float z_re, float z_im,
                         uniform int n,
                         uniform int maxIter,
                         uniform float eps)
{

    for (int iter = 0; iter < maxIter; ++iter) {

        float znRe = 1.0f;
        float znIm = 0.0f;

        float prevRe = 1.0f;
        float prevIm = 0.0f;

        for (uniform int k = 0; k < n; ++k) {
            float tRe = znRe * z_re - znIm * z_im;
            float tIm = znRe * z_im + znIm * z_re;

            prevRe = znRe;
            prevIm = znIm;
            znRe = tRe;
            znIm = tIm;
        }

        // f(z) = z^n - 1
        float fRe = znRe - 1.0f;
        float fIm = znIm;

        // f'(z) = n * z^{n-1}
        float fpRe = (float)n * prevRe;
        float fpIm = (float)n * prevIm;

        float denom = fpRe * fpRe + fpIm * fpIm;
        if (denom == 0.0f)
            break;

        // z_{k+1} = z_k - f(z_k)/f'(z_k)
        float qRe = (fRe * fpRe + fIm * fpIm) / denom;
        float qIm = (fIm * fpRe - fRe * fpIm) / denom;

        z_re -= qRe;
        z_im -= qIm;

        float bestDist2 = 1e9f;
        int   bestIdx   = -1;

        for (uniform int k = 0; k < n; ++k) {
            float angle = 2.0f * 3.1415926535f * (float)k / (float)n;
            float rRe   = cos(angle);
            float rIm   = sin(angle);

            float dRe = z_re - rRe;
            float dIm = z_im - rIm;
            float dist2 = dRe * dRe + dIm * dIm;

            if (dist2 < bestDist2) {
                bestDist2 = dist2;
                bestIdx   = k;
            }
        }

        if (bestDist2 < eps * eps) {
            int packed = (bestIdx << 16) | (iter & 0xFFFF);
            return packed;
        }
    }

    return -1;
}

export void newton_fractal_ispc(uniform float x0, uniform float y0,
                                uniform float x1, uniform float y1,
                                uniform int   width,
                                uniform int   height,
                                uniform int   maxIterations,
                                uniform int   n,
                                uniform float eps,
                                uniform int   output[])
{
    float dx = (x1 - x0) / (float)width;
    float dy = (y1 - y0) / (float)height;

    for (uniform int j = 0; j < height; ++j) {
        foreach (i = 0 ... width) {
            float x = x0 + (float)i * dx;
            float y = y0 + (float)j * dy;

            int index = j * width + i;
            output[index] = newton(x, y, n, maxIterations, eps);
        }
    }
}
