/*
 * Assignment 1.c
 * 
 * Copyright 2023  <pi@osboxes>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

#define SCHEDULING_POLICY SCHED_FIFO

void *thread_100();
void *thread_200();
void *thread_300();

static void timespec_add_us(struct timespec *t, long us);
//static void timespec_cmp(struct timespec *a, struct timespec *b);


int main(int arg, char **argv)
{
    fflush(stdout);
    int th1, th2, th3;
    pthread_t thread1, thread2, thread3;
    pthread_attr_t th1_attr, th2_attr, th3_attr;
    cpu_set_t cpu1, cpu2, cpu3;
    struct sched_param sched_param1, sched_param2, sched_param3;
    
    /* THREAD ATTRIBUITES 1 */
    pthread_attr_init(&th1_attr);
    pthread_attr_setinheritsched(&th1_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&th1_attr, SCHED_RR);
    CPU_ZERO(&cpu1);
    CPU_SET(1, &cpu1);
    pthread_attr_setaffinity_np(&th1_attr, sizeof(cpu_set_t), &cpu1);
    
    #if (SCHEDULING_POLICY == SCHED_FIFO)
        sched_param1.sched_priority = 10;
    #elif (SCHEDULING_POLICY == SCHED_RR)
        sched_param1.sched_priority = 10;
    #endif
        
    pthread_attr_setschedparam(&th1_attr, &sched_param1);
    
    /* THREAD ATTRIBUITES 2 */
    pthread_attr_init(&th2_attr);
    pthread_attr_setinheritsched(&th2_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&th2_attr, SCHED_RR);
    CPU_ZERO(&cpu2);
    CPU_SET(1, &cpu2);
    pthread_attr_setaffinity_np(&th2_attr, sizeof(cpu_set_t), &cpu2);

    #if (SCHEDULING_POLICY == SCHED_FIFO)
        sched_param1.sched_priority = 9;
    #elif (SCHEDULING_POLICY == SCHED_RR)
        sched_param1.sched_priority = 10;
    #endif
    
    pthread_attr_setschedparam(&th2_attr, &sched_param2);
    

    /* THREAD ATTRIBUITES 3 */
    pthread_attr_init(&th3_attr);
    pthread_attr_setinheritsched(&th3_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&th3_attr, SCHED_RR);
    CPU_ZERO(&cpu3);
    CPU_SET(1, &cpu3);
    pthread_attr_setaffinity_np(&th3_attr, sizeof(cpu_set_t), &cpu3);

    #if (SCHEDULING_POLICY == SCHED_FIFO)
        sched_param1.sched_priority = 8;
    #elif (SCHEDULING_POLICY == SCHED_RR)
        sched_param1.sched_priority = 10;
    #endif

    pthread_attr_setschedparam(&th3_attr, &sched_param3);
    
    printf("gggg");
    
    /* THREADs CREATION */
    th1 = pthread_create(&thread1, &th1_attr, thread_100, NULL);
    th2 = pthread_create(&thread2, &th2_attr, thread_200, NULL);
    th3 = pthread_create(&thread3, &th3_attr, thread_300, NULL);
    
    /* CHECK ERROR on THREADs CREATION */
    if(th1 == 1 || th2 == 1 || th3 == 1)
    {
	printf(" ERROR ");
    }
    
    /* DESRTOYING THREADs ATTRIBUITEs */
    pthread_attr_destroy(&th1_attr);
    pthread_attr_destroy(&th2_attr);
    pthread_attr_destroy(&th3_attr);
    
    th1 = pthread_join(thread1, NULL);
    th2 = pthread_join(thread2, NULL);
    th3 = pthread_join(thread3, NULL);
    
    /* CHECK ERROR ON JOINING THREADs */
    if(th1 == 1 || th2 == 1 || th3 == 1)
    {
	printf(" ERROR ");
    }
    
    return 0;
}

static int n1 = 10000000;
static int n2 = 20000000;

/* 100ms */
void *thread_100()
{
	struct timespec current_time, next_time;
	long thread_period_us = 100000;
	clock_gettime(CLOCK_MONOTONIC, &next_time);
	
	while(1)
	{
		timespec_add_us(&next_time, thread_period_us);
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		
		/* CHECK MISSING OR NOT THE DEADLINE */
		if((current_time.tv_sec > next_time.tv_sec) || ((current_time.tv_sec == next_time.tv_sec) && (current_time.tv_nsec > next_time.tv_nsec)))
		   printf("Deadline is missed for this thread (100ms Periodic Thread)");
		else
		   printf("Deadline is met for this thread (100ms Periodic Thread)");
		
		/* Simulating operations executed in the task (consuming some CPU time) */
		int i, j, a;
		for (i=0; i<n1; i++)
		{
		    for(j=0; j<n2; j++)
		    {
			a = j/2;
		    }
		}

	}
}

/* 200ms */
void *thread_200()
{
	struct timespec current_time, next_time;
	long thread_period_us = 200000;
	clock_gettime(CLOCK_MONOTONIC, &next_time);
	
	while(1)
	{
		timespec_add_us(&next_time, thread_period_us);
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		
		/* CHECK MISSING OR NOT THE DEADLINE */
		if((current_time.tv_sec > next_time.tv_sec) || ((current_time.tv_sec == next_time.tv_sec) && (current_time.tv_nsec > next_time.tv_nsec)))
		   printf("Deadline is missed for this thread (200ms Periodic Thread)");
		else
		   printf("Deadline is met for this thread (200ms Periodic Thread)");
		
		/* Simulating operations executed in the task (consuming some CPU time) */
		int i, j, a;
		for (i=0; i<n1; i++)
		{
		    for(j=0; j<n2; j++)
		    {
			a = j/2;
		    }
		}
	}
}
 
/* 300ms */
void *thread_300()
{
	struct timespec current_time, next_time;
	long thread_period_us = 300000;
	clock_gettime(CLOCK_MONOTONIC, &next_time);
	
	while(1)
	{
		timespec_add_us(&next_time, thread_period_us);
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		
		/* CHECK MISSING OR NOT THE DEADLINE */
		if((current_time.tv_sec > next_time.tv_sec) || ((current_time.tv_sec == next_time.tv_sec) && (current_time.tv_nsec > next_time.tv_nsec)))
		   printf("Deadline is missed for this thread (300ms Periodic Thread)");
		else
		   printf("Deadline is met for this thread (300ms Periodic Thread)");
		
		/* Simulating operations executed in the task (consuming some CPU time) */
		int i, j, a;
		for (i=0; i<n1; i++)
		{
		    for(j=0; j<n2; j++)
		    {
			a = j/2;
		    }
		}
	}
}


static void timespec_add_us(struct timespec *t, long us)
{
	t -> tv_nsec += us * 1000;
	if( t -> tv_nsec > 1000000000)
	{
		t -> tv_nsec = t -> tv_nsec - 1000000000;
		t -> tv_sec += 1;
	}
}

/*static int timespec_cmp(struct timespec *a, struct timespec *b)
{
	if( a -> tv_sec > b -> tv_sec) 
	   return 1;
	else if( a -> tv_sec < b -> tv_sec)
   	   return -1;
	else if( a -> tv_sec == b -> tv_sec)
	{
		if( a -> tv_nsec > b -> tv_nsec)
		   return 1;
		else if( a -> tv_nsec == b -> tv_nsec)
		   return 0;
		else
		   return -1;
	} 
}*/
