#include <pthread.h>
#include <stdio.h>

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
  int count =0;
  // Prime number
  for (; start <= end; start++) {
      int is_prime = 1;

      // Check if start is prime
      for (int i = 2; i * i <= start; i++) {
          if (start % i == 0) {
              is_prime = 0;
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
  pthread_t thread, thread_2, thread_3, thread_4, thread_5;
  struct thread_data arg,arg_2,arg_3,arg_4,arg_5;
  // 1-9,999
  arg.start = 1;
  arg.end = 9999;
  arg.prime_number = NULL;
  // 10,000-19,999
  arg_2.start = 10000;
  arg_2.end = 19999;
  arg_2.prime_number = NULL;
  // 20,000-29,999
  arg_3.start = 20000;
  arg_3.end = 29999;
  arg_3.prime_number = NULL;

  // 30,000-39,999
  arg_4.start = 30000;
  arg_4.end = 39999;
  arg_4.prime_number = NULL;

  // 40,000-49,999
  arg_5.start = 40000;
  arg_5.end = 50000;
  arg_5.prime_number = NULL;

  start_time = clock();
  
  pthread_create(&thread, NULL, &compute_prime, &arg);
  pthread_create(&thread_2, NULL, &compute_prime, &arg_2);
  pthread_create(&thread_3, NULL, &compute_prime, &arg_3);
  pthread_create(&thread_4, NULL, &compute_prime, &arg_4);
  pthread_create(&thread_5, NULL, &compute_prime, &arg_5);

  pthread_join(thread, NULL); 
  pthread_join(thread_2, NULL); 
  pthread_join(thread_3, NULL);
  pthread_join(thread_4, NULL);
  pthread_join(thread_5, NULL);
  for (int i = 0; i < arg.size; i++) {
      printf("%d ", arg.prime_number[i]);
  }
  for (int i = 0; i < arg_2.size; i++) {
      printf("%d ", arg_2.prime_number[i]);
  }
  for (int i = 0; i < arg_3.size; i++) {
      printf("%d ", arg_3.prime_number[i]);
  }
  for (int i = 0; i < arg_4.size; i++) {
      printf("%d ", arg_4.prime_number[i]);
  }
  for (int i = 0; i < arg_5.size; i++) {
      printf("%d ", arg_5.prime_number[i]);
  }
  
  end_time = clock(); 
  float elapsed_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("\nElapsed time: %f seconds", elapsed_time);
  
  return 0;
}


 