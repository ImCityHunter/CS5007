/**
 * MessagePriorityQueue_test.java
 * 
 * This file contains the unit tests for the MessagePriorityQueue classes.
 * 
 * @author philip gust
 * @since 2017-05-04
 * 
 */
package edu.northeastern.cs_5004;

import static org.junit.Assert.*;
import org.junit.FixMethodOrder;  
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runners.MethodSorters;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

/**
 * This class performs unit tests for the MessagePriorityQueue classes.
 */

@FixMethodOrder(MethodSorters.NAME_ASCENDING)

public class MessagePriorityQueue_test {
	/**
	 * Unit tests for Message
	 */
	@Test
	public void test_0010_Message() {
		// test creation of message with null string
		Message msg = new Message();
		assertNotNull("Message created", msg);
		assertNull("Message string null", msg.getMessage());

		// test allocation of message with non-null string
		msg = new Message("Hello");
		assertNotNull("Message created", msg);
		assertNotNull("Message string", msg.getMessage());
		assertEquals("Message string", "Hello", msg.getMessage());
	}
	
	/**
	 * Unit tests for MessageQueue
	 */
	@Test
	public void test_0020_MessageQueue() {
		//// test empty queue
		// create a message queue
		MessageQueue mq = new MessageQueue();
		assertNotNull("Message queue created", mq);
		assertEquals("Message queue empty", 0, mq.getSize());

		// dequeue message from empty queue
		assertNull("Message queue empty", mq.dequeue());
		assertEquals("Message queue empty", 0, mq.getSize());

		//// test single message on queue
		// create message queue and enqueue message
		mq = new MessageQueue();
		Message msg = new Message("0");
		mq.enqueue(msg);
		assertEquals("Message queue not empty", 1, mq.getSize());

		// dequeue a message
		assertEquals("Message dequeued", mq.dequeue(), msg);
		assertEquals("Message queue empty", 0, mq.getSize());

		// dequeue message from empty queue
		assertNull("Message queue empty", mq.dequeue());
		assertEquals("Message queue empty", 0, mq.getSize());

		//// over-fill queue test
		mq = new MessageQueue();
		int qsize = mq.getCapacity();
		for (int i = 0; i <= qsize; i++) {
			msg = new Message(Integer.toString(i));
			mq.enqueue(msg);
		}
		// verify that the queue expanded
		assertEquals("Message queue exanded", qsize+1, mq.getSize());
		assertTrue("Message queue expanded", mq.getCapacity() > qsize);

		// dequeue first message
		Message msg0 = mq.dequeue();
		assertEquals("Message dequeued", qsize, mq.getSize());
		assertNotNull("Message dequeued", msg0);
		assertEquals("Message dequeued", "0", msg0.getMessage());

		// dequeue second message
		Message msg1 = mq.dequeue();
		assertEquals("Message dequeued", qsize-1, mq.getSize());
		assertNotNull("Message dequeued", msg1);
		assertEquals("Message dequeued", "1", msg1.getMessage());
	}
	
	/**
	 * Unit tests for MessageQueue
	 */
	@Test
	public void test_0020_MessagePriorityQueue() {
		//// test empty queue
		// create a message queue
		MessagePriorityQueue mpq = new MessagePriorityQueue();
		assertNotNull("Priority queue createed", mpq);
		assertEquals("Priority queue empty", 0, mpq.getSize());

		// dequeueue message from empty queue
		assertNull("Priority queue empty", mpq.dequeue());

		//// test single message on queue
		// create message queue and enqueue message
		mpq = new MessagePriorityQueue();
		Message msg = new Message("0.0");
		mpq.enqueue(msg, MessagePriorityQueue.Priority.high);
		assertEquals("Prioity queue size", 1, mpq.getSize());
		assertEquals("Priority queue size: high",
					 1, mpq.getSize(MessagePriorityQueue.Priority.high));

		// dequeue a message
		assertEquals("Expected message dequeued", mpq.dequeue(), msg);
		assertEquals("Priority queue empty", 0, mpq.getSize());

		// dequeue message from empty queue
		assertNull("Priority queue empty", mpq.dequeue());
		assertEquals("Priority queue empty", 0, mpq.getSize());

		//// Enqueue 3 messages for each priority
		mpq = new MessagePriorityQueue();
		for (MessagePriorityQueue.Priority p : MessagePriorityQueue.Priority.values()) {
			for (int i = 0; i < 3; i++) {
				msg = new Message(p + "." + i);
				mpq.enqueue(msg, p);
			}
		}

		// ensure that each queue has 3 messages
		assertEquals("Expected #messages", 
					 12, mpq.getSize());
		assertEquals("Expected highest messages",
					 3, mpq.getSize(MessagePriorityQueue.Priority.highest));
		assertEquals("Expected high messages",
				     3, mpq.getSize(MessagePriorityQueue.Priority.high));
		assertEquals("Expected low messages",
				     3, mpq.getSize(MessagePriorityQueue.Priority.low));
		assertEquals("Expected highest lowest",
				 	 3, mpq.getSize(MessagePriorityQueue.Priority.lowest));

		// verify that the messages dequeue in the right order
		for (MessagePriorityQueue.Priority p : MessagePriorityQueue.Priority.values()) {
			for (int i = 0; i < 3; i++) {
				msg = mpq.dequeue();
				assertNotNull("Message not null", msg);
				assertEquals("Message dequeue order", 
							 p + "." + i, msg.getMessage());
			}
		}
		assertEquals("Queue empty", 0, mpq.getSize());
	}
	
	/**
	 * Run the tests in this class.
	 * 
	 * @param args the program arguments
	 */
	public static void main(String[] args) {
	    Result result = JUnitCore.runClasses(MessagePriorityQueue_test.class);
	    
	    System.out.println("[Unit Test Results]");
	    System.out.println();
	    
	    if (result.getFailureCount() > 0) {
	    	System.out.println("Test failure details:");
		    for (Failure failure : result.getFailures()) {
		       System.out.println(failure.toString());
		    }
		    System.out.println();
	    }
	    
	    int passCount = result.getRunCount()-result.getFailureCount()-result.getIgnoreCount(); 
	    System.out.println("Test summary:");
	    System.out.println("* Total tests = " + result.getRunCount());
	    System.out.println("* Passed tests: " + passCount);
	    System.out.println("* Failed tests = " + result.getFailureCount());
	    System.out.println("* Inactive tests = " + result.getIgnoreCount());
	}
}
