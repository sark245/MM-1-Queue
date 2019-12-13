//External definitions for single-server queueing system

#include<stdio.h>
#include<math.h>
#include<lcgrand.h>

#define Q_LIMIT 100 //Limit on queue length
#define BUSY    1
#define IDLE    0

int next_event_type, num_custs_delayed, num_delays_required, num_events, 
    num_in_q, server_status;

float area_num_in_q, area_server_status, mean_interarrival, mean_service, 
      sim_time, time_arrival[Q_LIMIT+1], time_last_event, time_next_event[3],
      total_of_delays;

FILE *infile, *outfile;

void initialize(void);	//Intitialisation Routine
void timing(void); 	
void arrive(void); 
void depart(void);
void report(void);
void update_time_avg_stats(void);
float expon(float mean);

main(){

	infile = fopen("mm1.in", "r");
	outfile = fopen("mm1.out", "w");

	//Number of events for the timing function
	
	num_events = 2;

	//Reading Input parameters
	
	fscanf(infile, "%f %f %d", &mean_interarrival, &mean_service, &num_delays_required);

	//Report Heading and Output Parameters
	
	fprintf("outfile", "Single-server queueing system\n\n");
	fprintf("outfile", "Mean Interarrival time%11.3f minutes\n\n", mean_interarrival);
	fprintf("outfile", "Mean Service time%16.3f minutes\n\n", mean_service);
	fprintf("outfile", "Number of Customers%14d\n\n", num_delays_required);

	//Initialising the simulation
	
	intialize();

	//Run the simulation while more delays are still needed
	
	while(num_custs_delayed < num_delays_required){
		//Determine the next event

		timing();

		//Update time-avg statistical counters

		update_time_avg_stats();

		//Invoke the apt event function
		

		switch(next_event_type){
			case 1 : arrive();
				 break;
			case 2 : depart();
				 break;
		}
	}

	report();

	fclose(infile);
	fclose(outfile);

	return 0;

}

void intialize(void){
	sim_time = 0.0;

	server_status    = IDLE;
	num_in_q	 = 0;
	time_last_event  = 0.0;


	num_custs_delayed	= 0;
	total_of_delays 	= 0.0;
	area_num_in_q		= 0.0;
	area_server_status 	= 0.0;

	time_next_event[1] = sim_time + expon(mean_interarrival);
	time_next_event[2] = 1.0e+30;
}

void timing(void){
	int i;
	float min_time_next_event = 1.0e+29;
	
	next_event_type = 0;

	for(i = 1; i <= num_events; ++i)
		if(time_next_event[i] < min_time_next_event){
			min_time_next_event = time_next_event[i];
			next_event_type = i;
		}

		if(next_event_type == 0){
			fprintf(outfile, "\nEvent lsit empty at time %f", sim_time);
			exit(1);
		}

		sim_time = min_time_next_event;

}





































