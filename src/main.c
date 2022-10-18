#include <stdio.h>
#include <stdlib.h>
#include "Movement.h"
#include "Tracking.h"

int main(){

    int x, y =0;
    float sigma = 0.5;
    int size = 3;
    long nrl, nrh, ncl, nch;
    printf("On cree le filtre\n");
    double** filter = create_gaussian_filter(sigma, size);
    
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            printf("%f ",filter[i][j]);
        }
        printf("\n");
    }
    //on ouvre les deux images;
    printf("On ouvre les deux Images\n");
    printf("On ouvre la premiere Image\n");
    rgb8 **ImgT = LoadPPM_rgb8matrix("../droite.ppm", &nrl, &nrh, &ncl, &nch);
    printf("On a ouvert la premiere img\n");
    printf("On ouvre la seconde Image\n");
    rgb8 **ImgTPlusUn = LoadPPM_rgb8matrix("../gauche.ppm", &nrl, &nrh, &ncl, &nch);
    printf("On a ouvert la seconde img\n");
    byte **ImgTGris;
    ImgTGris=bmatrix(nrl, nrh, ncl, nch);
    printf("On convertis la premire image en nuance de gris \n");
    //convert_rgb8_to_byte(rgb8 **I, byte **B, long nrl, long nrh, long ncl, long nch);
    convert_rgb8_to_byte(ImgT, ImgTGris, nrl, nrh, ncl, nch);
    byte **ImgTPlusUnGris;
    ImgTPlusUnGris=bmatrix(nrl, nrh, ncl, nch);

    printf("On convertis la seconde image en nuance de gris \n");
    convert_rgb8_to_byte(ImgTPlusUn, ImgTPlusUnGris, nrl, nrh, ncl, nch);


    int filter_size = size;
    float lambda = sigma;
    
    printf("On appel Harris sur la premiere Img \n");
    double ** ImgTHarris = harris(ImgTGris, filter, filter_size, lambda, nrl, nrh, ncl, nch);
    printf("On appel Harris sur la seconde Img \n");
    double ** ImgTPlusUnHarris =harris(ImgTPlusUnGris, filter, filter_size, lambda, nrl, nrh, ncl, nch);

    //void convert_dmatrix_bmatrix(double **D, byte **B, long nrl, long nrh, long ncl, long nch)
    printf("On converti la premiere Img \n");
    convert_dmatrix_bmatrix(ImgTHarris, ImgTGris, nrl, nrh, ncl, nch);
    printf("On converti la seconde Img \n");
    convert_dmatrix_bmatrix(ImgTPlusUnHarris, ImgTPlusUnGris, nrl, nrh, ncl, nch);


    //void binarize(byte **I, byte **B, int treshold, long nrl, long nrh, long ncl, long nch)


    //Vecteur (double **imgT, double **imgTplusUn, int *x, int *y, long nrl, long nrh, long ncl, long nch)
    printf("On calcul le vecteur \n");
    Vecteur (ImgTGris, ImgTPlusUnGris, &x, &y, nrl, nrh, ncl, nch);
    //printf("x = %p, y = %p.",*x,*y);
    printf("x = %d, y = %d.",x,y);
    printf("FIN !!! \n");

    // TODO libérer la mémoire !

    return 0;
}