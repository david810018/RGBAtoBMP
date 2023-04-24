/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/24/2023 05:31:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPFileHeader;

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int colorsImportant;
} BMPInfoHeader;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
} RGBA;

int main() {
    int width = 512;
    int height = 512;
    RGBA *imageData = (RGBA*) malloc(width * height * sizeof(RGBA));
    // Initialize imageData with RGBA image information
    
    BMPFileHeader fileHeader = {
        .type = 0x4D42,
        .size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height * 4,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader)
    };
    
    BMPInfoHeader infoHeader = {
        .size = sizeof(BMPInfoHeader),
        .width = width,
        .height = height,
        .planes = 1,
        .bitsPerPixel = 32,
        .compression = 0,
        .imageSize = width * height * 4,
        .xPixelsPerMeter = 0,
        .yPixelsPerMeter = 0,
        .colorsUsed = 0,
        .colorsImportant = 0
    };
    
    FILE *fp = fopen("output.bmp", "wb");
    if (!fp) {
        printf("Failed to open file\n");
        return 1;
    }
    
    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, fp);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, fp);
    
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            RGBA *pixel = &imageData[y * width + x];
            fwrite(&pixel->blue, 1, 1, fp);
            fwrite(&pixel->green, 1, 1, fp);
            fwrite(&pixel->red, 1, 1, fp);
            fwrite(&pixel->alpha, 1, 1, fp);
        }
    }
    
    fclose(fp);
    free(imageData);
    
    return 0;
}
