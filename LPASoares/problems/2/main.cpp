/*
 * LPA 2018/2019
 * Mooshak ID -> PASSEVITE
 * João Soares - jmsoares@student.dei.uc.pt
 * José Ferreira - jmamede@student.dei.uc.pt
 * Madalena Santos - mcsantos@student.dei.uc.pt
 *
 * To print the events that make up the solution to the stdout use the argument -out when calling the program
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

//#define DEBUG

//Event Structure
typedef struct event{
	int deadline, duration, profit;
} event;

//Variables to hold the number of events and the biggest deadline of the set of events
int total_count_events, max_deadline = 0;

//Declares the matrix that will support our DP approach (we store the profit)
int **profit_matrix;

//Declares the table to store the events to schedule
event *events;

//Compares events deadline: returns >0 if deadline a > b, 0 if a=b and <0 if deadline b > a
int compare_events_deadline(const void *a, const void *b) {
	return  ((event*)a)->deadline - ((event*)b)->deadline;
}

//Returns the max of 2 numbers
int max(int a, int b) {
	return a > b ? a : b;
}

//Returns the min of 2 numbers
int min(int a, int b) {
	return a < b ? a : b;
}

//Function to fill the profit matrix (DP Approach)
void fill_profit_matrix() {

    //We initialize the first line to 0's since without any events our profit is always 0
	for(int t = 0; t <= max_deadline; t++) profit_matrix[0][t] = 0;

	//For all the events
	for(int i = 1; i <= total_count_events; i++) {

	    //For all the time "ticks" available for events (this value is the maximum deadline available)
		for(int t = 0; t <= max_deadline; t++) {

		    /* We store the minimum value between the current time tick and the event deadline, minus the event
		     * duration - this will give us the time tick we'd have to consider for the start of the event if we were
		     * to chose it */
			int possible_event_start_time_tick = min(t, events[i-1].deadline) - events[i-1].duration;

			/* if the possible start time for the event is less then 0, it means the event has a duration bigger than
			 * the time tick we're currently analyzing */
			if (possible_event_start_time_tick < 0)
			    //So for the profit we can't consider this event, thus we copy the profit
				profit_matrix[i][t] = profit_matrix[i - 1][t];

			//if we can consider the event, possible_event_start_time_tick >= 0
			else
			    //we will store as the profit the maximum value of the 2 possible cases, choosing the event, or not
				profit_matrix[i][t] =
				        //not considering the event we get the profit value from the row about in the same column
				        max(profit_matrix[i - 1][t],
				                /*Considering the event, the total profit is the sum the of the profit of our event with 
								 * the profit that is possible so far at the time we would start it*/
				                events[i-1].profit + profit_matrix[i - 1][possible_event_start_time_tick]);
		}
	}
}

//Function to print the events that make up our best solution
void write_results_to_stdout(int i, int t) {

    //if the number of events is 0 return without doing nothing
	if (i == 0) return;

	/* If the profit of the row above in the current time tick is the same, it means that we have not chosen the current
	 * event for our solution, so we call our print function for the previous event and give it the same time tick*/
	if (profit_matrix[i][t] == profit_matrix[i - 1][t]) write_results_to_stdout(i - 1, t);

	//If the profit of the row above is not the same, it means that we have chosen the event
	else {
	    //we store the current event start time
        int event_start_time = min(t, events[i - 1].deadline) - events[i - 1].duration;

        //we call the function again for the previous event and give it the time tick where our event has started
        write_results_to_stdout(i - 1, event_start_time);

        /* When the last call returns we print the information of our event. Doing this will print the events in
         * ascending order*/
		std::cout   << i << " "
					<< event_start_time << " "
					<< event_start_time + events[i - 1].duration << " "
					<< events[i - 1].deadline << " "
					<< events[i - 1].profit << std::endl;
        return;
	}
}

int main(int argc, char *argv[]) {

	if (argc > 2) {
		printf("Wrong number of arguments\nUse -out to print results to the stdout\n");
		return 0;
	}

	std::cin >> total_count_events;

	events = (event*) std::malloc((total_count_events + 1) * sizeof(event));

#ifdef DEBUG
	std::cout << "Input read:" << std::endl;
#endif
	for (int i = 0; i < total_count_events; i++) {
		std::cin >> events[i].deadline;
		std::cin >> events[i].duration;
		std::cin >> events[i].profit;
		max_deadline = events[i].deadline > max_deadline ? events[i].deadline : max_deadline;
#ifdef DEBUG
		std::cout << events[i].deadline <<" "<< events[i].duration <<" "<< events[i].profit << std::endl;
#endif
	}

	profit_matrix = (int**) std::malloc((total_count_events + 1)  * sizeof(int*));

	for (int i = 0; i <= total_count_events; i++) {
		profit_matrix[i] = (int*) std::malloc((max_deadline + 1) * sizeof(int));
	}

	// Sorts events for ascending order of deadline value
    std::qsort(events, static_cast<size_t>(total_count_events), sizeof(event), compare_events_deadline);

#ifdef DEBUG
	std::cout << "Input ordered by deadline: " << std::endl;
	for (int i = 0; i < total_count_events; i++) {
		std::cout << events[i].deadline <<" "<< events[i].duration <<" "<< events[i].profit << std::endl;
	}
	std::cout << "Max deadline found: " << max_deadline << std::endl;
#endif

	fill_profit_matrix();

#ifdef DEBUG
	std::cout << "Profit matrix dump:" << std::endl;
	for(int i = 0; i <= total_count_events; i++) {
		for(int t = 0; t < max_deadline; t++) {
			std::cout << profit_matrix[i][t] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Highest possible profit: ";
#endif

	// The solution to the problem is the value in the low rightmost value in the profit_matrix
	std::cout << profit_matrix[total_count_events][max_deadline] << std::endl;

#ifndef DEBUG
	if (argc == 2){
		if (strcmp(argv[1],"-out") == 0) write_results_to_stdout(total_count_events, max_deadline);
	}
#endif

#ifdef DEBUG
	std::cout << "Events chosen to get the highest profit:\n"
			  "<event id, starting time, ending time, deadline, profit>" << std::endl;
	write_results_to_stdout(total_count_events, max_deadline);
#endif

	free(events);
	for (int i = 0; i <= total_count_events; i++) {
		free(profit_matrix[i]);
	}
	free(profit_matrix);

	return 0;
}
