#ifndef TOOL_H__
#define TOOL_H__

#include "cdef.h"

class Circle_Queue
{
public:
	Circle_Queue()
	{
		m_u8Oldest = 0;
		m_u8QueueLen = 0;
	}

	void vSetQueueLen(uint8 u8QueueLen);
	/* Get the relative position by absolute position */
	uint8 u8PutQueue(uint8 u8AbsPos);
	/* Get the specified member in queue */
	uint8 u8GetQueue(uint8 u8Index);
	uint8 u8GetOldest();
	void vSetOldest(uint8 u8Oldest);

private:
	/* The oldest member in the queue */
	uint8 m_u8Oldest;
	/* The queue length */
	uint8 m_u8QueueLen;
};

int8_t i8Char2Dec(char u8Char);

#endif // !TOOL_H__
