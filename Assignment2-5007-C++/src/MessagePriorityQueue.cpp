/*
 * MessagePriorityQueue.cpp
 *
 * This file contains the method definitions for class MessagePriorityQueue.
 *
 * @since: 2017-05-04
 * @author: philip gust
 */

#include <cstddef>
#include <cassert>
#include "MessagePriorityQueue.h"

using namespace std;

namespace CS_5004 {
/**
 * Create a new message priority queue
 */
MessagePriorityQueue::MessagePriorityQueue() {
	// allocate array for message queues
	int nPriorities = lowest - highest + 1;
	msgQueues = new MessageQueue*[nPriorities];

	// allocate message queue for each priority
	for (int p = highest; p <= lowest; p++) {
		msgQueues[p] = new MessageQueue();
	}
}

/**
 * Deallocate the memory for the queue.
 */
MessagePriorityQueue::~MessagePriorityQueue() {
	// delete the message queues
	for (int p = highest; p <= lowest; p++) {
		delete msgQueues[p];
		msgQueues[p] = nullptr;
	}

	// free the message queue array
	delete[] msgQueues;
	msgQueues = nullptr;
}

/**
 * Add a message to the queue with the given priority
 * The Message must have been allocated, and will
 * be deleted by the queue if the queue is deleted.
 *
 * @param the message to enqueue
 * @param the priority of the message
 */
void MessagePriorityQueue::enqueue(Message* message, Priority priority) {
	assert( message != nullptr );

	// enqueue the message on the specified queue
	msgQueues[priority]->enqueue(message);
}

/**
 * Remove and return the first element of the greatest priority in the queue.
 * Message was allocated and must be deleted once used.
 *
 * @return the first element with the greatest priority
 */
Message* MessagePriorityQueue::dequeue() {
	Message* msg = nullptr;

	// dequeue message from the first non-empty queue
	for (int p = highest; p <= lowest; p++) {
		msg =  msgQueues[p]->dequeue();
		// found message to dequeue
		if (msg != nullptr) {
			break;
		}
	}

	// return the message if found
	return msg;
}

/**
 * Get the current number of elements in the queue with the specified priority.
 *
 * @param the priority to query
 * @return the number of elements for the specified priority
 */
int MessagePriorityQueue::getSize(Priority priority) const {
	return msgQueues[priority]->getSize();
}

/**
 * Get the current number of elements in the queue.
 *
 * @return the number of elements in the queue
 */
int MessagePriorityQueue::getSize() const {
	// add the size of all the queues
	int nElements = 0;
	for (int p = highest; p <= lowest; p++) {
		nElements+= msgQueues[p]->getSize();
	}
	return nElements;
}

} // namespace CS_5004
