/*
 * MessagePriorityQueue.h
 *
 * This file contains the implementation of class MessagePriorityQueue.
 *
 *  @since 2017-05-04
 *  @author philip gust
 */
package edu.northeastern.cs_5004;

/**
 * This class implements a priority queue for Messages, using a separate
 * MessageQueue instance for messages of each priority. * 
 */
public class MessagePriorityQueue {
	/**
	 * The array of message queues for each priority
	 */
	private MessageQueue[] msgQueues;
			
	/**
	 * The priorities for the MessagePriorityQueue
	 */
	public enum Priority{
		highest,
		high,
		low,
		lowest
	};

	/**
	 * Create a new message priority queue
	 */
	public MessagePriorityQueue() {
		// allocate array for message queues
		int nPriorities = Priority.values().length;
		msgQueues = new MessageQueue[nPriorities];

		// allocate message queue for each priority
		for (Priority p : Priority.values()) {
			msgQueues[p.ordinal()] = new MessageQueue();
		}
	}

	/**
	 * Add a message to the queue with the given priority
	 *
	 * @param the message to enqueue
	 * @param the priority of the message
	 */
	public void enqueue(Message message, Priority priority) {
		assert( message != null);

		// enqueue the message on the specified queue
		msgQueues[priority.ordinal()].enqueue(message);
	}

	/**
	 * Remove and return the first element of the greatest priority in the queue.
	 *
	 * @return the first element with the greatest priority
	 */
	public Message dequeue() {
		Message msg = null;

		// dequeue message from the first non-empty queue
		for (Priority p : Priority.values()) {
			msg =  msgQueues[p.ordinal()].dequeue();
			// found message to dequeue
			if (msg != null) {
				break;
			}
		}

		// return the message if found
		return msg;
	}

	/**
	 * Get the current number of elements in the queue with the specified priority.
	 *
	 * @param the number of elements for the specified priority
	 */
	public int getSize(Priority priority) {
		return msgQueues[priority.ordinal()].getSize();
	}

	/**
	 * Get the current number of elements in the queue.
	 */
	public int getSize() {
		// add the size of all the queues
		int nElements = 0;
		for (Priority p : Priority.values()) {
			nElements+= getSize(p);
		}
		return nElements;
	}
}
