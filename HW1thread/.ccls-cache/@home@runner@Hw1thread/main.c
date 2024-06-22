#include <pthread.h>
#include <stdio.h>
#include <time.h>

struct thread_data{
  int start ;
  int end ;
  int *prime_number;
  int size;
};


void* compute_prime(void* arg){

  struct thread_data* args = (struct thread_data*) arg;
  int start = args->start;
  int end = args->end;
  args->prime_number = malloc((end-start)*sizeof(int));

  int count=0;
  // Prime number
  for (; start <= end; start++) {
    int is_prime =  1 ;
      // Check if start is prime
      for (int i = 2; i * i <= start; i++) {
          if (start % i == 0) {
              is_prime = 0; //not prime
              break;
          }
      }
      if (is_prime && start > 1) {
        args->prime_number[count] = start;
        count++;
      }
  }
  args->size=count;

  return NULL;
}

int main(){
  clock_t start_time, end_time;
  pthread_t thread;
  struct thread_data arg;
  // 0-50,000
  arg.start = 1;
  arg.end = 50000;
  arg.prime_number = NULL;
  arg.size=0;
  
  start_time = clock();

  pthread_create(&thread, NULL, &compute_prime, &arg);
  pthread_join(thread,NULL); 

  for (int i = 0; i < arg.size; i++) {
      printf("%d ", arg.prime_number[i]);
  }
  
  end_time = clock(); 
  float elapsed_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("\nElapsed time: %f seconds", elapsed_time);

  
  return 0;
}


