#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double make_parallel(int n){
  int D[n][n];
	int D2[n][n];
	float static p = 0.8;
	int i,j;
	
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

	//#Aquí emepzamos a paralelizar.
  double start; 
  double end; 
  start = omp_get_wtime(); 
	int number_triagles[n];
	int number_degree[n];
	float clustering[n];

	//SACAMOS LOS D²
	//AQUÍ SE APLICAR LA PRIMERA Y SEGUNDA ESTRATEGIA
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
		}

	}
	//SACAMOS LA DIAGONAL 

	int diag[n];
	float clus[n];

	//Aquí se aplica la última estrategia.
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

  end = omp_get_wtime(); 
  double final_time = end - start;
  return final_time;
}


int main(int argc, char const *argv[]){
	int N = 10000;
	/*
	Aquí definismo el número máximo de nodos (N)
	en la iteración y generación de gráficas. 

	Aquí se presenta el problem de que no se
	pueden gráficas con más de 1000 nodos.
	*/
  double time_step;
  printf("n , time \n");
	for (int n = 5; n <= N; n += 20 ){
    time_step = make_parallel(n);
    printf("%d , %f \n",n , time_step );
  }	
}