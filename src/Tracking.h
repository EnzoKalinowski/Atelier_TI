#ifndef __TRACKING_H__
#define __TRACKING_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./NRC/def.h"
#include "./NRC/nrio.h"
#include "./NRC/nrarith.h"
#include "./NRC/nralloc.h"

/**
 * @brief Create a gaussian filter object
 * 
 * @param sigma filtering degree
 * @param size filter dimensions (sizexsize)
 * @return double** 
 */
double ** create_gaussian_filter(float sigma, int size);

/**
 * @brief Reveal point of interest in a image using Harris method
 * 
 * @param I Image 
 * @param filter 
 * @param filter_size filter dimensions (sizexsize)
 * @param lambda 
 * @param nrl 
 * @param nrh 
 * @param ncl 
 * @param nch 
 * @return double** 
 */
double ** harris(byte **I, double** filter, int filter_size, float lambda, long nrl, long nrh, long ncl, long nch);

/**
 * @brief convolve an image with a filter
 * 
 * @param I Image
 * @param filter 
 * @param filter_size filter dimensions (sizexsize)
 * @param nrl 
 * @param nrh 
 * @param ncl 
 * @param nch 
 * @return byte** 
 */
byte ** convolve(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch);

/**
 * @brief @brief Reveal point of interest in a image using gradient direction method
 * 
 * @param I Image
 * @param filter 
 * @param filter_size filter dimensions (sizexsize)
 * @param nrl 
 * @param nrh 
 * @param ncl 
 * @param nch 
 * @return double** 
 */
double ** gradient_direction_interest_points(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch);

/**
 * @brief image gradient
 * 
 * @param I 
 * @param Ix horizontal gradient
 * @param Iy vertical gradient
 * @param nrl 
 * @param nrh 
 * @param ncl 
 * @param nch 
 */
void sobel(byte **I, double **Ix, double **Iy, long nrl, long nrh, long ncl, long nch);

/**
 * @brief binarize an image
 * 
 * @param I input Image
 * @param B output Image
 * @param treshold 
 * @param nrl 
 * @param nrh 
 * @param ncl 
 * @param nch 
 */
void binarize(byte **I, byte **B, int treshold, long nrl, long nrh, long ncl, long nch);


#endif // __TRACKING_H__