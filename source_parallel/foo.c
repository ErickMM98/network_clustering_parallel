#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char const *argv[]){
	int n = 5000;
	int D[n][n];
	float p = 0.8;
	int i,j;
	int **A;
	//foo_function(matrix_a);
	
	//Aquí generamos la matriz
	for (i = 0; i < n; i++){
		for(j= 0 ; j < n; j++){
			D[i][j] = 0;
		}
	}

	for (i = 0; i < n; i++){
		for(j= i +1 ; j < n; j++){
			double r = ((double) rand() / (RAND_MAX));
			//printf("%f \n", r);
			if ( r < p){
					D[i][j] = 1;
					D[j][i] = 1;
			}
		}
	}

	//Hasta aquí tenemos la matriz de adyacencia


	//Esto es para imprimir la matriz
	/*
	for (i = 0; i < n; i++){
		for(j= 0; j < n; j++){
			printf("%d \t", D[i][j]);
		}
		printf("------------ \n");
	}
	*/


	//#Primer algoritmo secuencial.
	int number_triagles[n];
	int number_degree[n];
	float clustering[n];

	//Sacamos el vector de grados
	for (int node = 0; node < n; ++node){
		int degree = 0;
		for (int k = 0; k < n; ++k){
			degree += D[node][k];
		}
		number_degree[node] = degree;
		//printf("Node %d ------> %d \n",node, degree );
	}

	//Sacamos los triángulos
	for (int node = 0; node < n; ++node){
		//printf("%ls\n", D[node]);
		number_triagles[node] = 0;
		for (int v = 0; v < n; ++v){
			int v_comun_v = 0;
			if ( node != v){
				//printf("%d , %d \n", node, v );
				//Conteo de triángulos
				if (D[node][v] == 1){
					for (int k = 0; k < n; ++k){
						v_comun_v += D[node][k] * D[v][k];
					}
				}
			
			}
			//Este es el doble de números al cuadrado
			number_triagles[node] += v_comun_v;
		}
		//typeof(D[node][node]);
		//printf("%d  --------- %d \n", node+1, number_triagles[node]);
	}

	//Sacamos clustering
	for (int node = 0; node < n; ++node){
		float t = (float) number_triagles[node];
		float d = (float) number_degree[node];
		//printf("%f \n", t / (d * (d-1)) );
	}
	//Acaterminaclustering
	
}