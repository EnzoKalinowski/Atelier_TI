#ifndef __TRACKING_H__
#define __TRACKING_H__

#include <stdio.h>
#include <stdlib.h>

#include "./NRC/def.h"
#include "./NRC/nrio.h"
#include "./NRC/nrarith.h"
#include "./NRC/nralloc.h"


double ** create_gaussian_filter(float sigma, int size);
double ** harris(byte **I, double** filter, int filter_size, float lambda, long nrl, long nrh, long ncl, long nch);
byte ** convolve(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch);
double ** gradient_direction_interest_points(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch);


#endif // __TRACKING_H__