#include <stdio.h>
#include "oslabs.h"
//tr
struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
	
	//The method determines the process to execute next; and returns its PCB.
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
			
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
		
			ready_queue[*queue_cnt] = new_process; // add pcb to the ready queue
			(*queue_cnt)++; //increment the queue count (queue is growing) 
			return current_process; //return the pcb of the currently running process
			//ready_queue
			//queue_cnt

		}
		else { //if the new process has a higher priority
			current_process.execution_endtime = 0;
			current_process.remaining_bursttime = current_process.execution_endtime - timestamp; //subtract the differenec between the timestamp and cp.st
	
			ready_queue[*queue_cnt] = current_process; //add to the ready queue
			(*queue_cnt)++;
			new_process.execution_starttime = timestamp;
			new_process.remaining_bursttime = new_process.total_bursttime;
			new_process.execution_endtime = timestamp + new_process.total_bursttime;
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

	struct PCB holder;
	holder.process_id = 0;
	holder.arrival_timestamp = 0;
	holder.execution_endtime = 0;
	holder.execution_starttime = 0;
	holder.process_priority = 0;
	holder.remaining_bursttime = 0;
	holder.total_bursttime = 0;

	if ((*queue_cnt) <= 0) //if ready queue is empty  
	{
		return nullbyte; //return NullPCB
	}
	else {
		int count = 0; //find the highest priority
		int ctr = 0;
		int COUNTER = 1;
		count = ready_queue[0].process_priority; //set this equal to the first in the ready queue
		for (int i = 1; i < (*queue_cnt); i++) { 
			if (ready_queue[i].process_priority <= count) { //if element in ready queue has higher priority.
				count = ready_queue[i].process_priority; //save the higher priority here
				ctr = COUNTER; //store the exact index where the pcb is in the readyqueue
			} 
			//increment the counter
			COUNTER++; 
		}
		//ctr now holds the readyqueue #
		//Holder will hold the PCB we need to return later
		holder.arrival_timestamp = ready_queue[ctr].arrival_timestamp;
		holder.execution_endtime = ready_queue[ctr].execution_endtime;
		holder.execution_starttime = ready_queue[ctr].execution_starttime;
		holder.process_id = ready_queue[ctr].process_id;
		holder.process_priority = ready_queue[ctr].process_priority;
		holder.remaining_bursttime = ready_queue[ctr].remaining_bursttime;
		holder.total_bursttime = ready_queue[ctr].total_bursttime;

		int queuecount = (*queue_cnt)- 1;
		//now we need to remove the PCB from the readyqueue.... we know that CTR is the index where PCB is at; so we must remove this
		for (int i = ctr; i < queuecount; i++)
		{
			ready_queue[i] = ready_queue[i + 1]; //this shifts everything down one
		}
		//Set the execution start time as the current timestamp
		(*queue_cnt)--; //decrease the queue size
		holder.execution_starttime = timestamp;
		holder.execution_endtime = timestamp + holder.remaining_bursttime;
		return holder;
	}

}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
		if (current_process.process_id ==0 && current_process.process_priority == 0
    && current_process.total_bursttime ==0 && current_process.remaining_bursttime == 0
    && current_process.execution_starttime == 0 
    && current_process.execution_endtime == 0 && current_process.arrival_timestamp == 0) {
        new_process.execution_starttime = timestamp;
        if(time_quantum<=new_process.total_bursttime){
            new_process.execution_endtime=time_quantum+timestamp;
        } 
        else {
            new_process.execution_endtime=timestamp+new_process.total_bursttime;
        }
        new_process.remaining_bursttime=new_process.total_bursttime;
        return new_process;
    }
    new_process.execution_starttime = 0;
    new_process.execution_endtime = 0;
    new_process.remaining_bursttime = new_process.total_bursttime;
    ready_queue[*queue_cnt] = new_process;
    (*queue_cnt)++;
    return current_process

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
	//remove this process from the ready queue and then return it.
	for (int i = position; i < (*queue_cnt); i++)
	{
		ready_queue[i] = ready_queue[i + 1]; //copy next element value to current element.
	}
	(*queue_cnt)--;
	hold.execution_starttime = timestamp;
	hold.execution_endtime = timestamp + hold.remaining_bursttime;
	return hold; //removed from the ready_queue and returned the pcb that was removed.
}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
	struct PCB nullbyte; //ROUND ROBIN
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
	if ((*queue_cnt) <= 0)
	{
		new_process.execution_starttime = timestamp;
		new_process.execution_endtime = timestamp + time_quantum + new_process.total_bursttime;
		new_process.remaining_bursttime = new_process.total_bursttime;
		return new_process;
	}
	else {
		new_process.execution_endtime = 0;
		new_process.execution_starttime = 0;
		new_process.remaining_bursttime = new_process.total_bursttime;
		ready_queue[*queue_cnt] = new_process;
		(*queue_cnt)++;
		return current_process;
	}

}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int* queue_cnt, int timestamp, int time_quantum) {


}
