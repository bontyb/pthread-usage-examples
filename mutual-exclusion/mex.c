/**
 * When concurrent tasks work on same data they can work togheter on same memory location and your application can evolve into an unexpected way.
 * 
 * Concurrency Task: two task are concurrent if the first statement of the one is executed before the last statement of the other one
 * Critical Section: is the part of code that use shared data. The access to critical section must be controlled by special costruct that assure only one 
 * task can execute that section of code.
 * Mutex: is a 
*/
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define TH_NUMBER 100

static uint64_t data = 0;

void* incData( void* arg );

int main()
{
    pthread_t ths[TH_NUMBER];
    size_t i;
    for ( i = 0; i < TH_NUMBER; i++ )
    {
        pthread_create( &ths[i], NULL, incData, NULL);
    }

    for ( i = 0; i < TH_NUMBER; i++ )
    {
        pthread_join( ths[i], NULL);
    }

    /**
     * In single task environment. 
     * The value of shared data in 'incData' function won't change 
     * from the reading of value at the beginning of the function until the assignment.
     * So the increment operation was equal to data = data + 1.
     * So the expected result is the total number of increment (in this case one for each thread)
     *
     * In multi task environment ( multithread environment in this case ) the initial value of data could change after 1 second
     * so the expected result is unpredictable.
    */
    printf("Expected value: %u - Real Value: %lu\n", TH_NUMBER * 1, data);

}

void* incData( void* arg )
{
    /**
     * Get global value
    */
    uint64_t initialVal = data;

    /**
     * Simulate execution of operation using this data
    */
    sleep(1);  

    /**
     * Increment the value using the initial value.
    */
    data = initialVal + 1;
}
