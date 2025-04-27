#ifndef GIF_H
#define GIF_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Define these macros to hook into a custom memory allocator
#ifndef GIF_TEMP_MALLOC
#include <stdlib.h>
#define GIF_TEMP_MALLOC malloc
#endif

#ifndef GIF_TEMP_FREE
#include <stdlib.h>
#define GIF_TEMP_FREE free
#endif

#ifndef GIF_MALLOC
#include <stdlib.h>
#define GIF_MALLOC malloc
#endif

#ifndef GIF_FREE
#include <stdlib.h>
#define GIF_FREE free
#endif

const int kGifTransIndex = 0;

typedef struct
{
    int bitDepth;
    uint8_t r[256];
    uint8_t g[256];
    uint8_t b[256];
    uint8_t treeSplitElt[256];
    uint8_t treeSplit[256];
} GifPalette;

typedef struct
{
    uint32_t chunkIndex;
    uint8_t chunk[256];
    uint8_t bitIndex;
    uint8_t byte;
    uint8_t padding[2];
} GifBitStatus;

typedef struct
{
    FILE *f;
    uint8_t *oldImage;
    bool firstFrame;
    uint8_t padding[7];
} GifWriter;

// Function declarations
int GifIMax(int l, int r);
int GifIMin(int l, int r);
int GifIAbs(int i);

void GifGetClosestPaletteColor(GifPalette *pPal, int r, int g, int b, int *bestInd, int *bestDiff, int treeRoot);
void GifSwapPixels(uint8_t *image, int pixA, int pixB);
int GifPartition(uint8_t *image, const int left, const int right, const int elt, int pivotValue);
void GifPartitionByMedian(uint8_t *image, int left, int right, int com, int neededCenter);
int GifPartitionByMean(uint8_t *image, int left, int right, int com, int neededMean);
void GifSplitPalette(uint8_t *image, int numPixels, int treeNode, int treeLevel, bool buildForDither, GifPalette *pal);
int GifPickChangedPixels(const uint8_t *lastFrame, uint8_t *frame, int numPixels);
void GifMakePalette(const uint8_t *lastFrame, const uint8_t *nextFrame, uint32_t width, uint32_t height, int bitDepth, bool buildForDither, GifPalette *pPal);
void GifDitherImage(const uint8_t *lastFrame, const uint8_t *nextFrame, uint8_t *outFrame, uint32_t width, uint32_t height, GifPalette *pPal);
void GifThresholdImage(const uint8_t *lastFrame, const uint8_t *nextFrame, uint8_t *outFrame, uint32_t width, uint32_t height, GifPalette *pPal);

void GifWriteBit(GifBitStatus *stat, uint32_t bit);
void GifWriteChunk(FILE *f, GifBitStatus *stat);
void GifWriteCode(FILE *f, GifBitStatus *stat, uint32_t code, uint32_t length);
void GifWritePalette(const GifPalette *pPal, FILE *f);
void GifWriteLzwImage(FILE *f, uint8_t *image, uint32_t left, uint32_t top, uint32_t width, uint32_t height, uint32_t delay, GifPalette *pPal);

bool GifBegin(GifWriter *writer, const char *filename, uint32_t width, uint32_t height, uint32_t delay, int32_t bitDepth, bool dither);
bool GifWriteFrame(GifWriter *writer, const uint8_t *image, uint32_t width, uint32_t height, uint32_t delay, int bitDepth, bool dither);
bool GifEnd(GifWriter *writer);

#endif // GIF_H