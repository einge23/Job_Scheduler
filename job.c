//This is the source file for job.h that defines all of the functions whose prototpyes appear in the header file.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "job.h"

void help() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a job to the scheduler;\n");
	printf("\t'p' for removing a job from the scheduler;\n");
	printf("\t'u' for searching jobs per user;\n");
	printf("\t'j' for searching jobs per capacity;\n");
	printf("\t'l' for listing all jobs;\n");
	printf("\t'q' for quit.\n");
}

void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority) {
	if(job_name != NULL) {
		printf("Enter the name of the job: ");
		scanf("%s", job_name);
	}
	if(user_name != NULL) {
		printf("Enter the name of the user: ");
		scanf("%s", user_name);
	}
	if(num_cpus != NULL) {
		printf("Enter the number of CPUs: ");
		scanf("%d", num_cpus);
	}
	if(num_gpus != NULL) {
		printf("Enter the number of GPUs: ");
		scanf("%d", num_gpus);
	}
	if(memory != NULL) {
		printf("Enter the amount of memory: ");
		scanf("%d", memory);
	}
	if(time != NULL) {
		printf("Enter the amount of time: ");
		scanf("%lf", time);
	}
	if(priority != NULL) {
		printf("Enter the priority: ");
		scanf("%d", priority);
	}
}

struct job *add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority) {
	struct job *new_job;
    struct job *cur;
    struct job *prev;
	
	new_job = malloc(sizeof(struct job)); //allocates memory for new job being created
	if(new_job==NULL){ //returns if unable to allocate memory
		printf("Malloc failed");
		return scheduler;
	}
	// all the values below are taken from user input and assigned to the list
	strcpy(new_job->job_name,job_name);
	strcpy(new_job->user_name,user_name);
	new_job->num_cpus = num_cpus;
	new_job->num_gpus  = num_gpus;
	new_job->memory = memory;
	new_job->time = time;
	new_job->priority = priority;
	new_job->next = NULL;
	
	/* This else block will add a job to the list based on the priority value. If the new value is equal to one of the other priorities, 
    then it will add it behind that one in the list*/
    for (cur = scheduler, prev = NULL;
        cur != NULL && new_job->priority <= cur->priority;
        prev = cur, cur = cur->next)
        ; 

    new_job->next = cur;
    if (prev == NULL)
        return new_job;
    else{
        prev->next = new_job;
        return scheduler;
    }
}

/*pop_job removes the most recently added job from the list and deallocates the memory it uses, and prints the job to be deleted. 
  Does nothing if list is empty.*/
struct job * pop_job(struct job *scheduler) {
	struct job *p;
	p = scheduler;
	if(p == NULL){
		return scheduler;
	}
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	for(p = scheduler;p!=NULL; p = p->next)// iterates until p == NULL
		;
	// the lines below deallocates the memory of the current job and assigns it to NULL, therefore deleting it or 'popping' it from the list
	struct job *q = scheduler;
	scheduler = scheduler->next;
	free(q);
	q = NULL;
	return scheduler;
}
//list_user takes in the list and an inputted user name and prints jobs with that name. Does nothing if list is empty
void list_user(struct job *scheduler, char *user_name) {
	struct job *p;
	p = scheduler;
	for(int i=0;p!=NULL;p = p->next){// i is used to make sure the header only prints for the first job, assuming there is one to print
		if(strcmp(p->user_name, user_name)==0 && i == 0){
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			i++;
		}
		if(strcmp(p->user_name, user_name)==0){
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			
		}	
	}
}

//list_jobs requires user input and prints any job in the list that satisfies the input criteria
void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time) {
	struct job *p;
	p = scheduler;
	for(int i = 0;p!=NULL;p = p->next){// i is used to make sure the header only prints for the first job, assuming there is one to print
		if(p->num_cpus <=num_cpus && p->num_gpus <= num_gpus && p->memory <= memory && p->time <= time && i == 0){
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			i++;
		}
		if(p->num_cpus <=num_cpus && p->num_gpus <= num_gpus && p->memory <= memory && p->time <= time){
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		}
	}
}
//list_all_jobs takes in the linked list and prints them out in the order they appear in the list. If the list is empty, nothing happens
void list_all_jobs(struct job *scheduler) {
	struct job *p;
	if(scheduler!= NULL){
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	}
	for(p = scheduler;p!=NULL;p = p->next){
		
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		
	}
}
// clear jobs deallocates all memory for elements in the list and makes them NULL
struct job * clear_jobs(struct job *scheduler) {
	struct job *p;
	while(scheduler != NULL){
		p = scheduler;
		scheduler = scheduler->next;
		if(p!=NULL)
			free(p);
	}
	return NULL;
}