#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void imprime (int *v, int ini, int fim);
void troca (int *v, int i, int j);
int partition (int *v, int ini, int fim);
void quicksort (int *v, int ini, int fim, int size);

typedef struct {
	int ini, mid, fim;
} thread_arg;

int size;
int *v;

void *thread_func(void* arg){
	thread_arg *a = arg;
	quicksort(v, a->ini, a->mid, a->fim);
	printf("done in\n");
	return NULL;
}

int main()
{
	// initializations
	scanf("%d", &size);
	v = malloc(size * sizeof(int));
	

	// read array
	for (int i = 0; i < size; ++i)
		scanf("%d", &v[i]);

	// arguments
	thread_arg argument1, argument2;
	int mid = partition(v, 0, size-1);

	argument1.ini = 0;
	argument1.mid = mid-1;
	argument1.fim = size;

	argument2.ini = mid;
	argument2.mid = size-1;
	argument2.fim = size;

	pthread_t thread1, thread2;

	// thread and execution
	pthread_create(&thread1, NULL, thread_func, &argument1);
	// thread_func(&argument1);
	printf("done out 1\n");
	pthread_create(&thread2, NULL, thread_func, &argument2);
	// thread_func(&argument2);
	printf("done out 2\n");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// checks array
	int i = 0;
	while((i < size-1) && (v[i] <= v[i+1]))
		i++;
	if (i+1 == size)
		printf("uhull %d\n", i+1);
	else{
		printf("fudeo %d\n", i);
		printf("%d %d %d\n", v[i-1], v[i] , v[i+1]);
	}

	free(v);

	return 0;
}

void quicksort (int *v, int ini, int fim, int size){
	if (ini >= fim)
		return;
	int meio = partition(v, ini, fim);
	quicksort(v, ini, meio-1, size);
	quicksort(v, meio+1, fim, size);
}

int partition (int *v, int ini, int fim){
	int i = ini-1, j = ini;
	troca(v, (ini+fim)/2, fim);
	int pivo = v[fim];

	for (; j < fim; ++j)
	{
		if (v[j] <= pivo)
		{
			i++;
			troca(v, i, j);
		}
	}
	troca(v, i+1, fim);
	return i+1; //indice do pivo;
}

void imprime (int *v, int ini, int fim){
	for (int i = ini; i < fim; ++i)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void troca (int *v, int i, int j){
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
	return;
}