#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char const *argv[]){
	int static n = 3000;
	int D[n][n];
	int D2[n][n];
	float static p = 0.8;
	int i,j;
	//int **A;
	//int array_D[ n*(n-1) / 2];
	//printf("%ld \n", sizeof(array_D));
	//int k_ad;
	//k_ad = 0;
	//foo_function(matrix_a);
	
	//Aquí generamos la matriz
	
	for (i = 0; i < n; i++){
		for(j= 0 ; j < n; j++){
			D[i][j] = 0;
		}
	}
	
	//printf("%ld \n", sizeof(D) );
	for (i = 0; i < n; i++){
		for(j= i +1 ; j < n; j++){
			double r = ((double) rand() / (RAND_MAX));
			//printf("%f \n", r);
			if ( r < p){
					D[i][j] = 1;
					//array_D[k_ad] = 1;
					//k_ad = k_ad + 1;
					D[j][i] = 1;
			}else{
					D[i][j] = 0;
					D[j][i] = 0;
					//array_D[k_ad] = 0;
					//k_ad = k_ad + 1;
			}
		}
	}
	//printf("%ld \n", sizeof(D) );

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
	


	//#Aquí emepzamos a paralelizar.
	int number_triagles[n];
	int number_degree[n];
	float clustering[n];

	//Paralelizamos el vector de grados; por es claro que es una suma 
	//de valores independientes. 
	//Directamente; cada hilo le toca un nodo; separamos los nodos.
	/*
	#pragma omp parallel
	{
		int id;
		id = omp_get_thread_num();
		#pragma omp for
			for (int node = 0; node < n; ++node){
				printf("Nodo %d , ---- , thread -> %d \n", node, id);
				int degree = 0;
				for (int k = 0; k < n; ++k){
					degree += D[node][k];
				}
				number_degree[node] = degree;
				//printf("node %d - > degree %d \n", node,number_degree[node]);
			}

	}
	*/

	//printf("TERMINAMOS DE SACAR LOS grados\n"); 

	//SACAMOS LOS D²
	#pragma omp parallel
	{
		int id;
		id = omp_get_thread_num();
		#pragma omp for
		for (int i = 0; i < n; ++i){
				for (int j = i; j < n; ++j){
					if (i == j){
						int degree = 0;
						for (int k = 0; k < n; ++k){
							degree += D[i][k];
						}
						//number_degree[node] = degree;
						D2[i][i] = degree;
					}else{
						//printf("ENTRADA (%d, %d) , ---- , thread -> %d \n", i,j, id);
						//Hacemos la multuplicación; 

						int result = 0;
						for (int k = 0; k < n; ++k){
							result += D[i][k] * D[j][k];
							//D2[i][j] = 
							/* code */
						}
						D2[i][j] = result;
						D2[j][i] = result;
					}
				}

				//printf("node %d - > degree %d \n", node,number_degree[node]);
		}

	}
	//SACAMOS LA DIAGONAL 

	int diag[n];
	float clus[n];

	#pragma omp parallel
	{
		int id;
		id = omp_get_thread_num();
		#pragma omp for
		for (int i = 0; i < n; ++i){
			int suma_diag = 0;
			for (int k = 0; k < n; ++k){
				suma_diag += D2[i][k] * D[i][k];
			}
			diag[i] = suma_diag; 
			clus[i] = (float) suma_diag / (float)( D2[i][i] * (D2[i][i] - 1));
				//printf("node %d - > degree %d \n", node,number_degree[node]);
		}

	}

	/*
	for (i = 0; i < n; i++){
		for(j= 0; j < n; j++){
			printf("%d \t", D2[i][j]);
		}
		printf("------------ \n");
	}

	printf(".........----------------------------------.................. \n");
	for (i = 0; i < n; i++){
			printf("%d \t", diag[i]);
	}
	printf("\n");

	printf(".........----------------------------------.................. \n");
	for (i = 0; i < n; i++){
			printf("%f \t", clus[i]);
	}
	printf("\n");
	*/





	/*



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
	*/
	
}