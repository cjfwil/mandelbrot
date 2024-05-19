#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

char is_convergent_julia(float x, float y)
{
    float xp = x;
    float yp = y;
    int max_iterations = 1;
    
    for (int i = 0; i < max_iterations; ++i) {
        float newXp = (xp*xp - yp*yp) + x;        
        yp = (2*xp*yp) + y;
        xp = newXp;

        if (xp*xp + yp*yp > 4) {
            char grey = (i/(float)max_iterations) * 0xff;
            return(grey);
        }
    }
    return (0);
}

char is_convergent(float x, float y)
{
    float xp = 0;
    float yp = 0;
    int max_iterations = 64;
    
    for (int i = 0; i < max_iterations; ++i) {
        float newXp = (xp*xp - yp*yp) + x;        
        yp = (2*xp*yp) + y;
        xp = newXp;

        if (xp*xp + yp*yp > 4) {            
            char grey = (1.0f-i/(float)max_iterations) * 0xff;
            return(grey);
        }
    }
    return (0);
}

int main(void)
{
    int w = 512;
    int h = 512;
    char *data = (char *)malloc(w * h);
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            float scale = 2.5f;
            float xf = ((x-w/2.0f)/w - 0.2f) * (w/(float)h);
            float yf = (y-h/2.0f)/h;
            data[x + y * w] = is_convergent(xf*scale, yf*scale);
        }
    }
    stbi_write_bmp("mandelbrot.bmp", w, h, 1, data);
    return (0);
}