/*
 * MessageQueue.h
 *
 * This file contains the declarations for class MessageQueue.
 *
 * @since 2017-05-04
 * @author philip gust
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "Message.h"

namespace CS_5004 {

/**
 * This class enqueues and dequeues instances of Message on a first-in first-out
 * (FIFO) order. A MessageQueue can grow to accommodate any number of messages.
 *
 */
class MessageQueue {
private:
	/**
	 * Array of message pointers
	 */
    Message** messages = nullptr;

    /**
     * Number of elements in the queue
     */
    int size = 0;

    /**
     * Length of allocated array
     */
    int capacity = 0;

	/**
	 * Ensure that queue has the capacity for an additional message
	 */
	void ensureCapacity();

protected:
	/**
	 * Get the current capacity of the queue.
	 * NOTE: testing purposes only!
	 *
	 * @return the current capacity of the queue
	 */
	int getCapacity() const;

public:
	/**
	 * Create a new message queue
	 */
	MessageQueue();

	/**
	 * Deallocate the memory for the queue.
	 */
	~MessageQueue();

	/**
     * Add a message  to the queue.
     * The Message must have been allocated, and will
     * be deleted by the queue if the queue is deleted.
	 *
	 * @param message the message
	 */
	void enqueue(Message* message);

	/**
	 * Remove and return the first element in the queue.
	 * Message was allocated and must be deleted once used.
	 *
	 * @return the first message in the queue
	 */
	Message* dequeue();

	/**
	 * Get the current number of elements in the queue.
	 *
	 * @return the number of elements in the queue
	 */
	int getSize() const;

};

}

#endif /* MESSAGEQUEUE_H_ */
