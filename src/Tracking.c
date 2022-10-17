#include "Tracking.h"

double ** create_gaussian_filter(float sigma, int size)
{
	double **G=dmatrix(0,size-1,0,size-1);
	float x,y;
	double sum=0;
	
	for (int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			x=i-size/2;
			y=j-size/2;
			G[i][j]=exp(- (pow(x,2)+pow(y,2))/(2*pow(sigma,2)) )/(2*PI*pow(sigma,2));
			sum+=G[i][j];
		}
	}
	printf("Gaussian filter :\n");
	for (int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			G[i][j]/=sum;
			printf("%lf ",G[i][j]);

		}
		printf("\n");
	}

	return G;
}

double ** harris(byte **I, double** filter, int filter_size, float lambda, long nrl, long nrh, long ncl, long nch)
{
	double ** C;
	double ** Ix;
	double ** Iy;
	double Ix_square, Iy_square, IxIy;

	int max=filter_size/2;

	C= dmatrix(nrl, nrh, ncl, nch);
	Ix= dmatrix(nrl,nrh,ncl,nch);
	Iy= dmatrix(nrl,nrh,ncl,nch);

	sobel(I,Ix,Iy,nrl,nrh,ncl,nch);

	for (int x=nrl+max; x<=nrh-max; x++)
		{
			for(int y=ncl+max; y<=nch-max; y++)
			{
				Ix_square=0;
				Iy_square=0;
				IxIy=0;
				
				for (int i=-max;i<=max;i++)
				{
					for(int j=-max;j<=max;j++)
					{
						Ix_square+= filter[i+max][j+max]*pow(Ix[x+i][y+j],2);
						Iy_square+= filter[i+max][j+max]*pow(Iy[x+i][y+j],2);
						IxIy+= filter[i+max][j+max]*(Ix[x+i][y+j]*Iy[x+i][y+j]);
					}
				}
				C[x][y]=(Ix_square*Iy_square)-(IxIy)-(lambda*pow(Ix_square+Iy_square,2));
			}
		}

	free_dmatrix(Ix,nrl, nrh, ncl, nch);
	free_dmatrix(Iy,nrl, nrh, ncl, nch);
	return C;
}

double ** gradient_direction_interest_points(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch)
{
	double ** C;
	double ** Ix;
	double ** Iy;
	double Ix_square,Ix_square_filtered, Iy_square,Iy_square_filtered, IxIy, IxIy_filtered;

	int max=filter_size/2;
	double GradFilter[3][3]={ {1,1,1},{1,0,1},{1,1,1} };

	C= dmatrix(nrl, nrh, ncl, nch);
	Ix=dmatrix(nrl,nrh,ncl,nch);
	Iy=dmatrix(nrl,nrh,ncl,nch);

	sobel(I,Ix,Iy,nrl,nrh,ncl,nch);

	for (int x=nrl+max; x<nrh-max; x++)
		{
			for(int y=ncl+max; y<nch-max; y++)
			{
				Ix_square=0;
				Ix_square_filtered=0;
				Iy_square=0;
				Iy_square_filtered=0;
				IxIy=0;
				IxIy_filtered=0;
				
				for (int i=-max;i<=max;i++)
				{
					for(int j=-max;j<=max;j++)
					{
						Ix_square+= pow(Ix[x+i][y+j],2);
						Ix_square_filtered+= GradFilter[i+max][j+max]*pow(Ix[x+i][y+j],2);
						Iy_square+= pow(Iy[x+i][y+j],2);
						Iy_square_filtered+= GradFilter[i+max][j+max]*pow(Iy[x+i][y+j],2);
						IxIy+=Ix[x+i][y+j]*Iy[x+i][y+j];
						IxIy_filtered+= GradFilter[i+max][j+max]*Ix[x+i][y+j]*Iy[x+i][y+j];
					}
				}

				C[x][y]=(Ix_square*Iy_square_filtered)+(Iy_square*Ix_square_filtered)-(2*IxIy*IxIy_filtered);
			}
		}

	free_dmatrix(Ix,nrl, nrh, ncl, nch);
	free_dmatrix(Iy,nrl, nrh, ncl, nch);
	return C;
}

byte ** convolve(byte **I, double** filter, int filter_size, long nrl, long nrh, long ncl, long nch)
{	
	byte ** out;
	out=bmatrix(nrl,nrh,ncl,nch);

	double ** C;
	C= dmatrix(nrl, nrh, ncl, nch);
	int max=filter_size/2;

	for (int x=nrl+max; x<nrh-max; x++)
			{
				for(int y=ncl+max; y<nch-max; y++)
				{
					
					for (int i=-max;i<=max;i++)
					{
						for(int j=-max;j<=max;j++)
						{
							C[x][y]+= filter[i+max][j+max]*I[x+i][y+i];					
						}
					}
				}
			}

	double max_C=max_dmatrix(C,nrl, nrh, ncl, nch);
	printf("%f\n",max_C);
	for (int i=nrl; i<=nrh; i++)
	{
		for(int j=ncl; j<=nch; j++)
		{
			out[i][j]=(C[i][j]*255)/max_C;
		}
	}
	free_dmatrix(C, nrl, nrh, ncl, nch);
	return out;
}
