/**
 * MessagePriorityQueue_main.java
 * 
 * This file contains the implementation of class MessageQueue. 
 * 
 * @author philip gust
 * @since 2017-05-04
 * 
 */
package edu.northeastern.cs_5004;

/**
 * This class enqueues and dequeues instances of Message on a first-in first-out 
 * (FIFO) order. A MessageQueue can grow to accommodate any number of messages.
 *
 * @since 2017-05-04
 * @author: philip gust
 */
public class MessageQueue {
	/**
	 * Default capacity of the queue
	 */
	private final int DEFAULT_QUEUE_CAPACITY = 16;
	
	/**
	 * Enqueued messages
	 */
	private Message[] messages;
	
	/**
	 * The number of messages in the queue
	 */
	private int size;
	
	/**
	 * The capacity of the queue
	 */
	private int capacity;

	/**
	 * Create a message queue with the default capacity.
	 */
	public MessageQueue() {
		// create message array
		messages = new Message[DEFAULT_QUEUE_CAPACITY];

		// initialize other fields
		size = 0;
		capacity = DEFAULT_QUEUE_CAPACITY;
	}

	/**
	 * Ensure that queue has the capacity for an additional message
	 */
	private void ensureCapacity() {
		if (size == capacity) {
			// double capacity if queue is full
			capacity *= 2;
			Message[] newMessages = new Message[capacity];
			System.arraycopy(messages, 0,  newMessages, 0, size);
			messages = newMessages;
		}
	}

	/**
	 * Add a Message to the queue.
	 *
	 * @param the message to enqueue
	 */
	public void enqueue(Message message) {
		assert( message != null);

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
	public Message dequeue() {
		// no messages to dequeue
		if (size == 0) {
			return null;
		}

		// message at head of queue to return
		Message message = messages[0];

		// remove the message from the queue
		System.arraycopy(messages,1, messages, 0, --size);

		return message;
	}

	/**
	 * Get the current number of elements in the queue.
	 *
	 * @return the number of elements in the queue
	 */
	public int getSize() {
		return size;
	}

	/**
	 * Get the current capacity of the queue.
	 * NOTE: testing purposes only! (package visibility)
	 *
	 * @return the current capacity of the queue
	 */
	int getCapacity() {
		return capacity;
	}
	
}
