#include <stdint.h>
#include <stdio.h>
#include <pthread.h>


void* task( void* args);

/**
 * To build and link this simple file you must use the following command
 *  gcc -pthread basic -o basic
 * And use the following command to run it
 *  ./basic
*/

int main()
{
    uint8_t arg = 55;

    /**
     * This simple example create 
    */
   pthread_t th;
   pthread_create( &th, NULL, task, (void*) &arg);

   /**
    * Main process wait until thread finish
   */
  pthread_join( th, NULL );

}

void* task( void* arg )
{
    uint8_t* localArg = (uint8_t*) arg;

    pthread_t th = pthread_self();
    printf("Hello World. I'm a thread my identifier is: %lu. My creator passed me the following arg: %d\n", th, *localArg);
}