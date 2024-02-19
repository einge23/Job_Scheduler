/*This is the header file that sets up the function prototypes and struct definition for the source file and main file. It also uses
ifndef endif strtucture to protect the header file*/
#ifndef JOB_H
#define JOB_H

#define NAME_LEN 20
#define SIZE_LEN 3

struct job {
	char job_name[NAME_LEN+1], user_name[NAME_LEN+1];
	int num_cpus, num_gpus, memory, priority;
	double time;
	struct job *next;
};

void help();
void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority);
struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority);
struct job * pop_job(struct job *scheduler);
void list_user(struct job *scheduler, char *user_name);
void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time);
void list_all_jobs(struct job *scheduler);
struct job * clear_jobs(struct job *scheduler);

#endif