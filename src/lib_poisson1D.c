/**********************************************/
/* lib_poisson1D.c                            */
/* Numerical library developed to solve 1D    */ 
/* Poisson problem (Heat equation)            */
/**********************************************/
#include "lib_poisson1D.h"

void set_GB_operator_colMajor_poisson1D(double* AB, int *lab, int *la, int *kv) {
    //structure matrice a bande pour le stockage en memoire par colonne

    // initialisation des éléments de AB a 0
    for (int i = 0; i < (*lab) * (*la); i++) {
        AB[i] = 0.0;
    }

    // l espacement de la grille 
    double h = 1.0 / (*la + 1); 

    // Remplissage de la matrice tridiagonal
    for (int i = 0; i < *la; i++) {
        // Remplissage de la diagonale inferieur
        if (i > 0) {
            AB[(*kv - 1) + i * (*lab)] = 1.0 / (h * h);    // 1/h²
            // Pour chaque ligne i de la matrice, sauf la première, 
        }

        // diagonale principale
        AB[(*kv) + i * (*lab)] = -2.0 / (h * h); // -2/h²

        // diagonale supeieure 
        if (i < (*la) - 1) {
            AB[(*kv + 1) + i * (*lab)] = 1.0 / (h * h); // 1/h²
        }
    }
}

void set_GB_operator_colMajor_poisson1D_Id(double* AB, int *lab, int *la, int *kv) {
    // Initializdes éléements de AB à 0
    for (int i = 0; i < (*lab) * (*la); i++) {
        AB[i] = 0.0;
    }

    // diagonale=1
    for (int i = 0; i < *la; i++) {
        AB[(*kv) + i * (*lab)] = 1.0;
    }
    
   
}


void set_dense_RHS_DBC_1D(double* RHS, int* la, double* T0, double* T1) {
    double h = 1.0 / (*la + 1);  // l espacement

    // initialisation du RHS 
    for (int i = 0; i < *la; i++) {
        RHS[i] = 0.0;  // Initialize to zero
    }

    // conditions aux limites 
    RHS[0] -= *T0 / (h * h);        // condition aux limites a x = 0
    RHS[*la - 1] -= *T1 / (h * h);  // condition aux limites a x = 1
}

void set_analytical_solution_DBC_1D(double* EX_SOL, double* X, int* la, double* BC0, double* BC1) {
    double h = 1.0 / (*la + 1); // l espacement

    for (int i = 0; i < *la; i++) {
        // Calculate the analytical solution based on the given boundary conditions
        EX_SOL[i] = *BC0 + (X[i] - 0.0) * ((*BC1 - *BC0) / 1.0);
    }
}


void set_grid_points_1D(double *X, int *la) {
    // cette fonction initialise les points de grille pour un domaine 1D

    double h = 1.0 / (*la + 1); 
    // h: l espacement de la grille, l'inverse du nombre des intervalles+1
    // *la: le nombre de points de grille internes donc *la+1 donne le nombre totale des intervalles
    // La division de 1 sur *la+1 pour avoir les valeurs entre 0 et 1

    for (int i = 0; i < *la; i++) {
        // cette boucle fait une iteration sur la grille interne pour définir sa valeur

        X[i] = (i + 1) * h;
        // la position est calculée comme (i + 1) * h.
        // l indice i + 1 est utilisé car les points de grille commencent apres la limite initiale a 0
    }
}

void write_GB_operator_rowMajor_poisson1D(double* AB, int* lab, int* la, char* filename){
  FILE * file;
  int ii,jj;
  file = fopen(filename, "w");
  //Numbering from 1 to la
  if (file != NULL){
    for (ii=0;ii<(*lab);ii++){
      for (jj=0;jj<(*la);jj++){
	fprintf(file,"%lf\t",AB[ii*(*la)+jj]);
      }
      fprintf(file,"\n");
    }
    fclose(file);
  }
  else{
    perror(filename);
  }
}

void write_GB_operator_colMajor_poisson1D(double* AB, int* lab, int* la, char* filename){
  FILE * file;
  int ii,jj;
  file = fopen(filename, "w");
  //Numbering from 1 to la
  if (file != NULL){
    for (ii=0;ii<(*la);ii++){
      for (jj=0;jj<(*lab);jj++){
	fprintf(file,"%lf\t",AB[ii*(*lab)+jj]);
      }
      fprintf(file,"\n");
    }
    fclose(file);
  }
  else{
    perror(filename);
  }
}

void write_GB2AIJ_operator_poisson1D(double* AB, int* la, char* filename){
  FILE * file;
  int jj;
  file = fopen(filename, "w");
  //Numbering from 1 to la
  if (file != NULL){
    for (jj=1;jj<(*la);jj++){
      fprintf(file,"%d\t%d\t%lf\n",jj,jj+1,AB[(*la)+jj]);
    }
    for (jj=0;jj<(*la);jj++){
      fprintf(file,"%d\t%d\t%lf\n",jj+1,jj+1,AB[2*(*la)+jj]);
    }
    for (jj=0;jj<(*la)-1;jj++){
      fprintf(file,"%d\t%d\t%lf\n",jj+2,jj+1,AB[3*(*la)+jj]);
    }
    fclose(file);
  }
  else{
    perror(filename);
  }
}

void write_vec(double* vec, int* la, char* filename){
  int jj;
  FILE * file;
  file = fopen(filename, "w");
  // Numbering from 1 to la
  if (file != NULL){
    for (jj=0;jj<(*la);jj++){
      fprintf(file,"%lf\n",vec[jj]);
    }
    fclose(file);
  }
  else{
    perror(filename);
  } 
}  

void write_xy(double* vec, double* x, int* la, char* filename){
  int jj;
  FILE * file;
  file = fopen(filename, "w");
  // Numbering from 1 to la
  if (file != NULL){
    for (jj=0;jj<(*la);jj++){
      fprintf(file,"%lf\t%lf\n",x[jj],vec[jj]);
    }
    fclose(file);
  }
  else{
    perror(filename);
  } 
}  

int indexABCol(int i, int j, int *lab){
  return 0;
}
int dgbtrftridiag(int *la, int*n, int *kl, int *ku, double *AB, int *lab, int *ipiv, int *info){
  return *info;
}

