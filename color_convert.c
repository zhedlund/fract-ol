
#include <stdio.h>

void color_converter(int hex)
{
    int r;
    double g;
    double b;

    r = ((hex >> 16) & 0xFF) / 255.0; // Extract the RR byte
    g = ((hex >> 8) & 0xFF) / 255.0; // Extract the GG byte
    b = ((hex) & 0xFF) / 255.0; // Extract the BB byte
}

int main()
{
    int *hex = 563241;
    printf("%d", color_converter(hex));
}