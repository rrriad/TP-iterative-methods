/**********************************************/
/* lib_poisson1D.c                            */
/* Numerical library developed to solve 1D    */ 
/* Poisson problem (Heat equation)            */
/**********************************************/
#include "lib_poisson1D.h"
#include <math.h>

//calcul de valeurs propres
void eig_poisson1D(double* eigval, int *la) {
    int n = *la;
    for (int k = 1; k <= n; ++k) {
        eigval[k-1] = 2 - 2 * cos(k * M_PI / (n + 1));
    }
}

// calcul de la plus grande valeur propre 
double eigmax_poisson1D(int *la) {
    int n = *la;
    return 2 - 2 * cos(M_PI / (n + 1));
}
// calcul de la plus petite valeur propre
double eigmin_poisson1D(int *la) {
    int n = *la;
    return 2 - 2 * cos(n * M_PI / (n + 1));
}


double richardson_alpha_opt(int *la){
  return 0;
}

void richardson_alpha(double *AB, double *RHS, double *X, double *alpha_rich, int *lab, int *la,int *ku, int*kl, double *tol, int *maxit, double *resvec, int *nbite){
}

void extract_MB_jacobi_tridiag(double *AB, double *MB, int *lab, int *la,int *ku, int*kl, int *kv){
}

void extract_MB_gauss_seidel_tridiag(double *AB, double *MB, int *lab, int *la,int *ku, int*kl, int *kv){
}

void richardson_MB(double *AB, double *RHS, double *X, double *MB, int *lab, int *la,int *ku, int*kl, double *tol, int *maxit, double *resvec, int *nbite){
}

