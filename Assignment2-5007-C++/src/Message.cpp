/*
 * Message.cpp
 *
 * This file contains definitions for methods of class Message.
 *
 * @since 2017-05-04
 * @author philip gust
 */

#include <cstddef>
#include <string>
#include "Message.h"

using namespace std;

namespace CS_5004 {

/**
 * Factory method allocates a Message with the specified message string.
 *
 * @param msgstr the message string
 */
Message* Message::createMessage(const char* msgstr) {
	return new Message(msgstr);
}

/**
 * Create a Message with the specified message string.
 *
 * @param msgstr the message string
 */
Message::Message(const char* msgstr) {
	// add copy of message string or null the field
	// note the use of the C++ 11 nullptr keyword
	if (msgstr != nullptr) {
		// copy msgstr for this message
		char *msg = new char[strlen(msgstr)+1];
		this->msgstr = strcpy(msg, msgstr);  // strcpy returns first argument
	}
}

/**
 * Get the message string for this message
 *
 * @return the message string for this message
 */
const char* Message::getMessage() const {
	return msgstr;
}

/**
 * Delete this message and free its resources
 */
Message::~Message() {
	delete []msgstr;
	msgstr = nullptr;
}

}  // namespace CS_5004
