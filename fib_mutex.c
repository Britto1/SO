/*Utilizando um vetor de mutex para a sincronização, sera realizado o calculo do valor desejado passado por argumento do fib.
*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 
 pthread_mutex_t * mutex_fib;
 pthread_t * tids;
 int * result; 
 size_t size;

 void *fib(void * arg){

    size_t id = (size_t) arg;

   	// perdir permissão para resolver o termo "id" caso ja esteja trancado, aguarda.
   	 pthread_mutex_lock(&mutex_fib[id]);

   	/* calcular o termo "id" */
   	 if (id == 0) {
       		result[0] = 0; // padrao fib
   	 } else if (id == 1) {
       		result[1] = 1; // padrao fib
   	 } else {
		
       		result[id] = result[id - 1] + result[id - 2];
   	 }
	// identifica qual thread realizou a operação
	  printf("Feito pela thread %u.\n", (size_t)pthread_self());

   	/* destranca para a proxima thread */
   	 if (id < size - 1) {
     		pthread_mutex_unlock(&mutex_fib[id + 1]);
   	 }

   	 pthread_exit(0);
 }

 int main(int argc, char ** argv)
 {
    size_t i = 0;   
    sscanf(argv[1], "%d", &size); 
    size = size+1;	
    result = malloc(sizeof(int) * size+1);   
    mutex_fib = malloc(sizeof(pthread_mutex_t) * size+1);
    tids = malloc(sizeof(pthread_t) * size+1);

    /* inicializar todos os mutex_fib como "locked" */
    for (i = 0; i < size; i++) {
        pthread_mutex_init(&mutex_fib[i], NULL);
        pthread_mutex_lock(&mutex_fib[i]);
    }

   /* criar os threads que irão calcular os termos */
    for (i = 0;i < size; i++) {
       pthread_create(&tids[i], NULL, fib, (void *) i);
    }

   /* dizer que pode ser calculado o primeiro termo */
    pthread_mutex_unlock(&mutex_fib[0]);

   /* esperar que todos os termos estejam calculados */
    for (i = 0; i < size; i++) {
        pthread_join(tids[i], NULL);
    }

   /* apresentar o resultado */
    printf("Resultado : ");
    for (i = 0; i < size; i++){
        printf("\nfib[%d] - %d\n",i,result[i]);
    }
   printf("\n");

   /* destruir todos os mutex_fib inicializados */
   for (i = 0; i < size; i++) {
       pthread_mutex_destroy(&mutex_fib[i]);
   }

   /* libertar toda a memória alocada */
   free(tids);
   free(mutex_fib);
   free(result);

   return 0;
 }
