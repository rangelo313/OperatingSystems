#include <stdio.h>
#include "oslabs.h"
struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
	
	//The method determines the process to execute nextand returns its PCB.
		//if there is no currently-running process (ex: NULLPCB); then return the PCB of the newly arriving process indicating that it is the process to execute next 
	if (current_process.process_id == 0 && current_process.arrival_timestamp == 0 && current_process.execution_endtime && current_process.execution_starttime ==0 && current_process.process_priority ==0 && current_process.remaining_bursttime == 0 && current_process.total_bursttime ==0)
	{
		new_process.execution_starttime = timestamp;
		new_process.execution_endtime = timestamp + new_process.total_bursttime;
		new_process.remaining_bursttime = new_process.total_bursttime; //remaining burst time must equal total burst time
		return new_process;
	}
	else {
		//compare the priority of the newly-arriving process with the currently-running process; 
		//if the new process has equal or lower priority (smaller integers for the priority field in the PCB indicate higher priority)
		if (new_process.process_priority >= current_process.process_priority) 
		{
			//add pcb to redy queue and return value is the pcb of the currently running process
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
		
			ready_queue[(*queue_cnt)] = new_process;
			(*queue_cnt)++;
			return current_process;
			//ready_queue
			//queue_cnt

		}
		else { //if the new process has a higher priority
			current_process.execution_endtime = 0;
			current_process.remaining_bursttime = current_process.total_bursttime;
			
			ready_queue[(*queue_cnt)] = current_process;
			(*queue_cnt)++;
			new_process.execution_starttime = timestamp;
			new_process.execution_endtime = timestamp + new_process.total_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
			
			return new_process;
		}
	}


	//The NULLPCB is defined as[PID:0, AT : 0, TBT : 0, EST : 0, EET : 0, RBT : 0, Priority : 0]

}
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, int timestamp)
{
	struct PCB nullbyte;
	nullbyte.process_id = 0;
	nullbyte.arrival_timestamp = 0;
	nullbyte.execution_endtime = 0;
	nullbyte.execution_starttime = 0;
	nullbyte.process_priority = 0;
	nullbyte.remaining_bursttime = 0;
	nullbyte.total_bursttime = 0;
	if ((*queue_cnt) <= 0) //if empty  
	{
		return nullbyte; //return NullPCB
	}
	else {
		int count = 0;
		count = ready_queue[0].process_priority;
		for (int i = 1; i < (*queue_cnt); i++) {
			if (ready_queue[i].process_priority <= count) {
				count = ready_queue[i].process_priority;
			} //if process_priority is higher save the one with the highest priority in count
		}


		for (int i = 0; i < (*queue_cnt); i++) {
			if (ready_queue[i].process_priority == count)
			{
				ready_queue[i].execution_starttime = timestamp;
				ready_queue[i].execution_endtime = timestamp + ready_queue[i].remaining_bursttime;
				return ready_queue[i];
			} //if process_priority is higher save the one with the highest priority in count
		}

		//count should store the highest priority number; now return the pcb with this priority number


	}

}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
	if (current_process.process_id == 0) //if the third argument is nullpcb
	{
		new_process.execution_starttime = time_stamp;
		new_process.execution_endtime = time_stamp + new_process.total_bursttime;
		new_process.remaining_bursttime = new_process.total_bursttime;
		return new_process;
	}
	else {
		// If the new process does not have a shorter burst time
		if (current_process.remaining_bursttime > new_process.total_bursttime)
		{
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[(*queue_cnt)] = new_process;
			return current_process;//return value is the PCB of currently running process
		}
		else {
			current_process.execution_starttime = 0;
			current_process.execution_endtime = 0;
			current_process.remaining_bursttime = current_process.total_bursttime; //adjusting its remaining bursttime?
			ready_queue[(*queue_cnt)] = current_process;
			new_process.execution_starttime = time_stamp;
			new_process.execution_endtime = time_stamp + new_process.total_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
			return new_process;
		}
	}

}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, int timestamp)
{
	struct PCB nullbyte;
	struct PCB hold;
	nullbyte.process_id = 0;
	nullbyte.arrival_timestamp = 0;
	nullbyte.execution_endtime = 0;
	nullbyte.execution_starttime = 0;
	nullbyte.process_priority = 0;
	nullbyte.remaining_bursttime = 0;
	nullbyte.total_bursttime = 0;
	int lowest = 0;
	int position = 0;
	if ((*queue_cnt) <= 0) {
		return nullbyte;
	}
	else
	{
		lowest = ready_queue[0].remaining_bursttime;
		for (int i = 1; i < (*queue_cnt); i++)
		{
			if (ready_queue[i].remaining_bursttime < lowest)
			{
				lowest = ready_queue[i].remaining_bursttime;
				hold = ready_queue[i];
				position = i; //find and save the position that we want to replace
			}
		}
	}
	for (int i = position - 1; i < (*queue_cnt) - 1; i++)
	{
		ready_queue[i] = ready_queue[i + 1]; //copy next element value to current element.
	}
	(*queue_cnt)--; //decrease the size of the queue?
	hold.execution_starttime = timestamp;
	hold.execution_endtime = timestamp + hold.remaining_bursttime;
	return hold; //removed from the ready_queue and returned the pcb that was removed.
}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{

}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, int timestamp, int time_quantum) {



}
