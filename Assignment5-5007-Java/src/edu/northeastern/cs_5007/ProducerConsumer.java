package edu.northeastern.cs_5007;
import java.util.Date;
public class ProducerConsumer {
	
		//synchronized field, string builder 
		public static StringBuilder sb = new StringBuilder();
		
		/**
		 * nested class, producer
		 * 
		 *
		 */
		public static class Producer implements Runnable {
			@Override
			public void run() {
				for(int i=0;i<20;i++) {
					synchronized(sb) {
						while(sb.length()!=0) {
								//wait for other thread
								try {
									sb.wait();
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
							}
						
						long timeMilli = new Date().getTime();
						sb.append(timeMilli);
						sb.notify();
						//sleeps for 2 seconds to simulate a slow producer
						try {
							Thread.sleep(1000); //sleep 2 seconds
						}catch (InterruptedException e) {
							// try again
						}
					}
				}
				
			}
			
		}
		/**
		 * nested class, Consumer
		 * 
		 *
		 */
		public static class Consumer implements Runnable {

			@Override
			public void run() {
				
				for(int i =0;i<20;i++) {
					synchronized(sb) {
						while(sb.length()==0) {
								try {
									//wait for other thread
									//wait for the Producer to set sb
									sb.wait();					
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
							}
						System.out.println("time in milisec: " + sb);
						sb.setLength(0);
						sb.notify();

					}
				}
			}


			
		}
		
		public static void main(String[] args) {
			//Create a main() method that creates and starts two threads with the Runnables. 
			//It then waits for both threads to terminate using Thread.join().
			System.out.println("Assignment 5");
			Thread consumerThread = new Thread(new Consumer(),"consumerThread");
			Thread producerThread = new Thread(new Producer(),"producerThread");
			producerThread.start();
			consumerThread.start();
			try {
				producerThread.join();
				consumerThread.join();
				
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

			
			
		}

}
