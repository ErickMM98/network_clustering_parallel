#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double make_sequential(int n){
  int D[n][n];
	float p = 0.8;
	int i,j;
	//int **A;
	
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

	/* 
	-----------------------------------------------
	------- Aquí empieza el algoritmo -------------
	-----------------------------------------------
	*/
	clock_t t;
  t = clock();
	int number_triagles[n];
	int number_degree[n];
	float clust[n];

	//Sacamos el vector de grados
	for (int node = 0; node < n; ++node){
		int degree = 0;
		for (int k = 0; k < n; ++k){
			degree += D[node][k];
		}
		number_degree[node] = degree;
		//printf("Node %d ------> %d \n",node, degree );
	}

	//Hacemos D^3

	// Matrix auxiliar
	int D_aux[n][n];
	//Iteramos sobre las entradas 
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			int suma_aux = 0;
			for (int k = 0; k < n; ++k){
				suma_aux += D[i][k] * D[k][j];
			}
			D_aux[i][j] = suma_aux;
		}
	}

	int D_final[n][n];

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			int suma_aux = 0;
			for (int k = 0; k < n; ++k){
				suma_aux += D_aux[i][k] * D[k][j];
			}
			D_final[i][j] = suma_aux;
		}
	}

	//Terminamos D^3


	for (int node = 0; node < n; ++node){
		float t = (float) D_final[node][node];
		float d = (float) number_degree[node];
		clust[node] = t / (d * (d-1));
	}
	//Aquí terminamos clustering
	t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  //for (int node = 0; node < n; ++node){
	//	printf("%f \t", clust[node] );
	//}
  return time_taken;
}



/* 

Main para ver los datos. 

*/

int main(int argc, char const *argv[]){
	/*
	Aquí definismo el número máximo de nodos (N)
	en la iteración y generación de gráficas. 

	Aquí se presenta el problem de que no se
	pueden gráficas con más de 1000 nodos.
	*/
	int N = 10000;
  double time_step;
  printf("n , time \n");
	for (int n = 5; n <= N; n += 20 ){
    time_step = make_sequential(n);
    printf("%d , %f \n",n , time_step );
  }
}