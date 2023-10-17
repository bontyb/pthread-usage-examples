/**
 * This is the same example of mex.c but in with the incData use a semaphore to coordinate access to data.
 * Onlyy one thread at time can execute the increment code and the result will be the same of a single thread application.
 * 
 * In this case the program need 100s to complete the execution 1s for each thread because once at time can execute the code inside the incData function
*/
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>

#define TH_NUMBER 100

static uint64_t data = 0;

void* incData( void* arg );

pthread_mutex_t mux;

int main()
{
    int error;

    error = pthread_mutex_init(&mux, NULL);
    if ( error != 0 ) { 
        printf("Mutex init ERROR [%s]\n", strerror(error));  
        return 1; 
    }

    pthread_t ths[TH_NUMBER];
    size_t i;
    for ( i = 0; i < TH_NUMBER; i++ )
    {
        error = pthread_create( &ths[i], NULL, incData, NULL);
        if (error != 0)
        {
            printf("Thread creation ERROR [%s]", strerror(error)); 
        }
    }

    for ( i = 0; i < TH_NUMBER; i++ )
    {
        error = pthread_join( ths[i], NULL);
        if (error != 0)
        {
            printf("Thread Join ERROR [%s]", strerror(error)); 
        }
    }

    printf("Expected value: %u - Real Value: %lu\n", TH_NUMBER * 1, data);

}

void* incData( void* arg )
{
    /**
     * If a thread called lock without call unlock the current thread will wait until unlock is called
    */
    pthread_mutex_lock( &mux );

    /**
     * Only one thread can execute the following code
    */
    uint64_t initialVal = data;
    sleep(1);  
    data = initialVal + 1;

    /**
     * wake up other thread 
    */
    pthread_mutex_unlock( &mux );
}
