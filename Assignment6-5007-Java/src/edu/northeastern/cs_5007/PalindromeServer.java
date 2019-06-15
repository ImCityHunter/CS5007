package edu.northeastern.cs_5007;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * The connecting client will send a single text string to the server, and the
 * server will return a text string that is a palindrome of the input text and
 * disconnect from the client.
 * 
 * @author hky
 *
 */
public class PalindromeServer {
	/**
	 * Runs the server.
	 */
	public static void main(String[] args) throws IOException {
		String host = (args.length < 1) ? null : args[0];
		try {
			int port = Integer.parseInt(host);
			ServerSocket listener = new ServerSocket(port);
			try {
				while (true) {
					System.err.println("connection?");
					Socket socket = listener.accept();
					System.err.println("got one! " + socket.getPort());
					try {
						PrintWriter mssg = new PrintWriter(socket.getOutputStream(), true);
						mssg.print("Input a string: ");
						mssg.flush();
						//take the input string
						String input = new BufferedReader(new InputStreamReader(socket.getInputStream())).readLine();
						//reverse the string
						String reverse = new StringBuffer(input).reverse().toString();
						input += reverse;
						PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
						out.println(input);
					} finally {
						socket.close();
					}
				}
			} finally {
				listener.close();
			}
		} catch (NumberFormatException e) {
			//catch whether argument is integer or not
			System.err.println("input is not an Integer");
			e.printStackTrace();

		}
	}
}
