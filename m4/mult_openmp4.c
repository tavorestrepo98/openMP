//Multiplicacion de dos matrices cuadradas
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

void multiplicacion(int **a, int **b, int **c, int n){
	
	int i, j, k;
	#pragma omp loop 
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			for (k = 0; k < n; k++){
				c[i][j] += a[i][k]*b[k][j];                          
			}          
		}
	}
}


void imprimir(int **m, int n){
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");	
	}
}

void liberar(int **m, int n){
	for (int i = 0; i < n; i++){
	    free(m[i]);
		m[i] = NULL;
	}	
	free(m);
	m = NULL;
}

int main(int argc, char *argv[]){
	int n;
	n = atoi(argv[1]);
	clock_t begin, end;
	float time;
	
	int **a = (int **)malloc(n * sizeof(int *));
	int **b = (int **)malloc(n * sizeof(int *));
	int **c = (int **)malloc(n * sizeof(int *));

	for (int i = 0; i < n; i++){
		a[i] = (int *)malloc(n * sizeof(int));
		b[i] = (int *)malloc(n * sizeof(int));
		c[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++){
			a[i][j] = j+1;	
			b[i][j] = j+1;
			c[i][j] = 0;		
		}
	}
	

	begin = clock();
	multiplicacion(a, b, c, n);
	end = clock();

	time = (float)(end-begin);
	time = time/CLOCKS_PER_SEC;
	printf("%.6f\n", time);
	
	/*
	imprimir(a, n);
	printf("\n");
	imprimir(b, n);
	printf("\n");
	imprimir(c, n);*/
	

	liberar(a, n);
	liberar(b, n);
	liberar(c, n);

	return 0;
}
