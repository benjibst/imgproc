#include "gaussian.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void generate_gaussian_kernel(float *kernel, unsigned size, float sigma)
{
    //float (*kernel_2d)[size] = (float(*)[size])kernel;
    if(size % 2 == 0)
    {
        fprintf(stderr, "Kernel size must be odd\n");
        exit(1);
    }
    unsigned mid = size / 2;
    float stddev2 = 2*sigma*sigma;
    float one_over_pistddev2 = 1/(M_PI*stddev2);
    int x,y;
    float element;
    float sum = 0;
    for (int r = 0; r < mid; r++)
    {
        y = r - mid;
        for(int c = 0; c < mid; c++)
        {
            x = c-mid;
            element = one_over_pistddev2 * exp(-(x*x + y*y)/(stddev2));
            kernel[c + r*size] = element;
            kernel[size - c - 1 + r*size] = element;
            kernel[c + (size - r - 1)*size] = element;
            kernel[size - c - 1 + (size - r - 1)*size] = element;
            sum += 4*element;
        }
    }
    for (int i = 0; i < mid; ++i) {
        x = i - mid;
        element = one_over_pistddev2 * exp(-(x*x)/(stddev2));
        kernel[i + mid*size] = element;
        kernel[mid + i*size] = element;
        kernel[(size-1-i) + mid*size] = element;
        kernel[mid + mid*size] = element;
        sum += 4*element;
    }
    kernel[mid + mid*size] = one_over_pistddev2;
    sum+=one_over_pistddev2;
    for (int r = 0; r < size; r++)
    {
        for(int c = 0; c < size; c++)
        {
            kernel[c + r*size] /= sum;
        }
    }
}