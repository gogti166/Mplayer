#include "tool.h"
#include "cdef.h"

/******************************************
*				Circle Queue			  *
*******************************************/
void Circle_Queue::vSetQueueLen(uint8 u8QueueLen)
{
	m_u8QueueLen = u8QueueLen;
}

uint8 Circle_Queue::u8PutQueue(uint8 u8AbsPos)
{
	uint8 u8RelPos = 0;
	if (u8AbsPos >= m_u8QueueLen)
	{
		u8RelPos = u8AbsPos % m_u8QueueLen;
		m_u8Oldest = u8RelPos + 1;
		if (m_u8Oldest == m_u8QueueLen)
		{
			m_u8Oldest = 0;
		}
	}
	else
	{
		u8RelPos = u8AbsPos;
		m_u8Oldest = 0;
	}
	return u8RelPos;
}

uint8 Circle_Queue::u8GetQueue(uint8 u8Index)
{
	uint8 u8RelPos = (m_u8Oldest + u8Index) % m_u8QueueLen;
	return u8RelPos;
}

uint8 Circle_Queue::u8GetOldest()
{
	return m_u8Oldest;
}

void Circle_Queue::vSetOldest(uint8 u8Oldest)
{
	m_u8Oldest = u8Oldest;
}


/******************************************
*		      Stirng to integer		      *
*******************************************/
int8_t i8Char2Dec(char u8Char)
{
	int8_t i8Dec = -1;
	if ((u8Char > 47) && (u8Char < 58)) //0~9
	{
		i8Dec = u8Char - 48;
	}
	return i8Dec;
}