/*
 * MessageQueue.cpp
 *
 * This file contains method definitions for class MessageQueue.
 *
 * @since 2017-05-04
 * @author: philip gust
 */

#include <cstddef>
#include <cassert>
#include "MessageQueue.h"

using namespace std;


// allows DEFAULT_QUEUE_SIZE to be changed at compilation
#ifndef DEFAULT_QUEUE_CAPACITY
#define DEFAULT_QUEUE_CAPACITY 16
#endif

namespace CS_5004 {
/**
 * Create a message queue with the default capacity.
 */
MessageQueue::MessageQueue() {
	// create message array
	messages = new Message*[DEFAULT_QUEUE_CAPACITY];

	// initialize other fields
	size = 0;
	capacity = DEFAULT_QUEUE_CAPACITY;

}

/**
 * Deallocate the memory for the queue.
 *
 * @param queue the MessageQueue
 */
MessageQueue::~MessageQueue() {
	// delete messages in the queue
	for (int i = 0; i < size; i++) {
		delete messages[i];
		messages[i] = nullptr;
	}
	delete[] messages;
	messages = nullptr;
	capacity = 0;
	size = 0;
}

/**
 * Ensure that queue has the capacity for an additional message
 */
void MessageQueue::ensureCapacity() {
	if (size == capacity) {
		// double capacity if queue is full
		capacity *= 2;
		Message** newMessages = new Message*[capacity];
		for (int i = 0; i < size; i++) {
			newMessages[i] = messages[i];
		}
		delete[] messages;
		messages = newMessages;
	}
}

/**
 * Add a Message to the queue.
 *
 * @param the message to enqueue
 */
void MessageQueue::enqueue(Message* message) {
	assert( message != (Message*)nullptr) ;

	// ensure there is sufficient capacity for the new message
	ensureCapacity();

	// add to end of queue
	messages[size++] = message;
}

/**
 * Remove and return the first Message in the queue.
 *
 * @return the dequeued message, or NULL if no messages on queue
 */
Message* MessageQueue::dequeue() {
	// no messages to dequeue
	if (size == 0) {
		return (Message*)nullptr;
	}

	// message at head of queue to return
	Message *message = messages[0];

	// remove the message from the queue
	for (int i = 1; i < size; i++) {
		messages[i-1] = messages[i];
	}
	size--;

	return message;
}

/**
 * Get the current number of elements in the queue.
 *
 * @return the number of elements in the queue
 */
int MessageQueue::getSize() const {
	return size;
}

/**
 * Get the current capacity of the queue.
 * NOTE: testing purposes only!
 *
 * @return the current capacity of the queue
 */
int MessageQueue::getCapacity() const {
	return capacity;
}

}  // namespace CS_5004
