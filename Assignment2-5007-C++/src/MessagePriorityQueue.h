/*
 * MessagePriorityQueue.h
 *
 * This file contains the declarations for class MessagePriorityQueue.
 *
 *  @since 2017-05-04
 *  @author philip gust
 */

#ifndef MESSAGEPRIORITYQUEUE_H_
#define MESSAGEPRIORITYQUEUE_H_

#include "MessageQueue.h"

namespace CS_5004 {

/**
 * This class implements a priority queue of messages. Priorities are specified
 * by the Priority enumeration with contiguous values from highest..lowest.
 */
class MessagePriorityQueue {
private:
	/**
	 * The array of message queues for each priority
	 */
	MessageQueue** msgQueues;

public:
	/**
	 * The priorities for the MessagePriorityQueue
	 */
	enum Priority{
		highest,
		high,
		low,
		lowest
	};

	/**
	 * Create a new message priority queue
	 */
	MessagePriorityQueue();

	/**
	 * Deallocate the memory for the queue.
	 */
	~MessagePriorityQueue();

	/**
	 * Add a message to the queue with the given priority
     * The Message must have been allocated, and will
     * be deleted by the queue if the queue is deleted.
	 *
	 * @param the message to enqueue
	 * @param the priority of the message
	 */
	void enqueue(Message* message, Priority priority);

	/**
	 * Remove and return the first element of the greatest priority in the queue.
     * Message was allocated and must be deleted once used.
	 *
	 * @return the first element with the greatest priority
	 */
	Message* dequeue();

	/**
	 * Get the current number of elements in the queue with the specified priority.
	 *
	 * @param the priority to query
	 * @return the number of elements for the specified priority
	 */
	int getSize(Priority priority) const;

	/**
	 * Get the current number of elements in the queue.
	 *
	 * @return the number of elements in the queue
	 */
	int getSize() const;
};

}  // namespace CS_5004

#endif /* MESSAGEPRIORITYQUEUE_H_ */
