#include <iostream>
#include <cassert>
#include <mutex>

#include "bluegrass/service_queue.hpp"

using namespace std;
using namespace bluegrass;

mutex M;
size_t I;
char STR0[] = 
	"service_queue in action! Test pipes a DEQUEUE s_q into an ENQUEUE s_q\n";
char STR1[] = 
	"service_queue in action! Test utilizes a NOQUEUE s_q\n";

void create_test0(char& data) 
{
	unique_lock lock(M);
	data = STR0[I];
	if (STR0[I]) { ++I; }
}

void create_test1(char& data)
{
	unique_lock lock(M);
	data = STR1[I];
	if (STR1[I]) { ++I; }
}

void utilize_test(char& data) 
{
	cout << data << flush;
}

// routine pipes the output of one service_queue into the input of another service_queue
bool test_ende_queues() 
{
	I = 0;
	char data;
	service_queue<char, queue_t::DEQUEUE> dq(create_test0, 4, 16);
	service_queue<char, queue_t::ENQUEUE> eq(utilize_test, 4, 16);
	
	// perform manual transfer of data
	do { 
		dq.dequeue(data);
		eq.enqueue(data);
	} while (data);
	
	dq.shutdown();
	eq.shutdown();
	
	return true;
}

// uses a special service_queue type to perform function of previous function
bool test_no_queue() 
{
	I = 0;
	service_queue<char, queue_t::NOQUEUE> no(create_test1, utilize_test, 4, 4, 16);
	
	// wait until all the input string is consumed
	while (STR1[I]);
	
	no.shutdown();
	
	return true;
}

int main() 
{
	assert(test_ende_queues());
	cout << endl << flush;
	assert(test_no_queue());
	cout << endl << flush;
	
	return 0;
}
