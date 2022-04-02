#ifndef LYRIC_H__
#define LYRIC_H__

#include "cdef.h"
#include "tool.h"
#include <FL/fl_draw.H>

#define MAX_LINE_LEN 128
#define MAX_LINE	 128

#define MAX_SHOW_LINE_NUM	20

typedef struct
{
	time_t	tLrcTime;
	char*	pcLrc;
}tstLyric;

/* Used to show lyric*/
class Lyric_Box : public Fl_Widget, public Circle_Queue
{
public:
	Lyric_Box(int X, int Y, int W, int H, const char*L = 0) :Fl_Widget(X, Y, W, H, L)
	{
		m_u8LrcCnt = 0;
	}

	void vInputLyric(const char* pcText, const uint32 u32Len);

	const char* pcOutputLyric()
	{
		return m_pcLyric;
	}

	void vSetShowNum(uint8 u8MaxNum)
	{
		m_u8LrcMaxShowNum = u8MaxNum;
	}

	void vBackwardLyric(uint8 u8Oldest)
	{
		uint8 u8SrcIdx = 0;
		uint8 u8DstIdx = 0;
		for (u8SrcIdx = u8Oldest; u8SrcIdx < m_u8LrcCnt; u8SrcIdx++)
		{
			if (u8SrcIdx = MAX_SHOW_LINE_NUM - 1)
			{
				u8DstIdx = 1;
			}
			else if (u8SrcIdx = MAX_SHOW_LINE_NUM - 2)
			{
				u8DstIdx = 0;
			}
			else
			{
				u8DstIdx = u8SrcIdx + 2;
			}
			memcpy(m_acMultiLyricLine[u8DstIdx], m_acMultiLyricLine[u8SrcIdx], MAX_LINE_LEN);
		}
	}

	uint8 m_u8LrcCnt;
	/* The max number of LRC line allowed to show on box */
	uint8 m_u8LrcMaxShowNum;
	/* The number of LRC line should show on box */
	uint8 m_u8LrcShowCnt;
	const char* m_pcLyric;
	char m_acMultiLyricLine[MAX_SHOW_LINE_NUM][MAX_LINE_LEN];

protected:
	void draw();
};


uint8 u8ReadLyric(const char* pcPath);
int8_t i8SearchLyric(time_t tCurTime);
#endif