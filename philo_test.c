#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

enum philo_data
{
    PHILO_COUNT = 3
};

typedef struct s_pthread_mutex
{
    pthread_mutex_t chopsticks[PHILO_COUNT];

}               t_pthread_mutex;
int say_hi = 0;

t_pthread_mutex   *all(void)
{
    static t_pthread_mutex cs;
    return (&cs);
}

void    *routine(void   *arg)
{
    int index = *(int *)arg;
    pthread_mutex_lock(all()->chopsticks + index);
    pthread_mutex_lock(all()->chopsticks + ((index + 1) % PHILO_COUNT));
    sleep(3);
    printf("Philosopher is : %d\n", index + 1);
    say_hi += 1;
    pthread_mutex_unlock(all()->chopsticks + index);
    pthread_mutex_unlock(all()->chopsticks + ((index + 1) % PHILO_COUNT));
    free(arg);
}

int main()
{
    pthread_t   philo[PHILO_COUNT];
    for (int i = 0; i < PHILO_COUNT; i++)
    {
        pthread_mutex_init(&(all()->chopsticks[i]), NULL);
    }
    for (int i = 0; i < PHILO_COUNT; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&philo[i], NULL, routine, a))
        {
            printf("Error philo not created!\n");
            return (101);
        }
    }

    for (int i = 0; i < PHILO_COUNT; i++)
    {
        if (pthread_join(philo[i], NULL))
        {
            printf("Error in joining threads after execution\n");
            return (102);
        }
    }
    printf("Hi's said: %d\n", say_hi);
    for (int i = 0; i < PHILO_COUNT; i++)
    {
        pthread_mutex_destroy(&(all()->chopsticks[i]));
    }
    // system("leaks a.out");
    return (0);
}