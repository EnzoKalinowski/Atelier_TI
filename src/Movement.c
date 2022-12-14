#include "Movement.h"

void ** Vecteur (byte **imgT, byte **imgTplusUn, int *x, int *y, long nrl, long nrh, long ncl, long nch){
	int **tabaccu = imatrix0 (nrl, nrh, ncl, nch);
	int X = (nrl-nrh)/2;
	int Y = (ncl-nch)/2;
	int xplus =0;
	int yplus =0;
	//printf("avant la lecture des image et l'insertion dans la table d'accumulation\n");
	for (int i= nrl; i< nrh; i++){
		for(int j= ncl; j<nch; j++){
			if(imgT[i][j]==255){
				//printf("1ER IF\n");
				int vect = 1000;	
				for (int iplus= nrl; iplus< nrh; iplus++){
					for(int jplus= ncl; jplus<nch; jplus++){
						if(imgTplusUn[iplus][jplus]==255){
							//printf("2ND IF\n");
							//printf("iplus = %d/%d, jplus = %d/%d \n",iplus,nrh,jplus,nch);
							int vectcalcule = abs(iplus-i)+(jplus-j);
							//printf("APRES VECTCALCULE!!!\n");
							if (vectcalcule<vect){
								//printf("3EME IF\n");
								vect = vectcalcule;
								xplus = iplus;
								yplus = jplus;
							}
						}
					}
				}
			}
			//printf("Avant de remplir tabaccu\n");
			tabaccu[xplus][yplus] ++; 
			//printf("Apres avoir rempli tabaccu\n");
		}
	}
	//printf("apres avoir rempli la table d'accumulation\n");
	int maxaccu = 0;
	for (int i= nrl; i< nrh; i++){
		for(int j= ncl; j<nch; j++){
			if (tabaccu[i][j]>maxaccu){
				maxaccu = tabaccu[i][j];
				xplus = i;
				yplus = j;
			}
			//printf("%d",tabaccu[i][j]);
		}
		//printf("\n");
	}
	//printf("apres avoir recupere le vecteur\n");
	x = &xplus;
	y = &yplus;
	//printf("fin de la fonction \n");
	free_imatrix (tabaccu, nrl, nrh, ncl, nch);
}