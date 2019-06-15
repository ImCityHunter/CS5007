/*
 * Message.h
 *
 * This file contains declarations for class Message.
 *
 * @since 2017-05-04
 * @author philip gust
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

namespace CS_5004 {

/**
 * This class implements a Message with optional message string that can
 * be enqueued on a MesssageQueue.
 */
class Message {
private:
	const char* msgstr = nullptr;

	/**
	 * Create a Message with the specified message string.
	 *
	 * @param msgstr the message string
	 */
	Message(const char* msgstr = nullptr);

public:
	/**
	 * Factory method allocates a Message with the specified message string.
	 *
	 * @param msgstr the message string
     * @return a new Message with the specified string
	 */
	static Message *createMessage(const char* msgstr = nullptr);

	/**
	 * Delete this message and free its resources
	 */
	~Message();

	/**
	 * Get the message string for this message
	 *
	 * @return the message string for this message
	 */
	const char* getMessage() const;
};

}

#endif /* MESSAGE_H_ */
