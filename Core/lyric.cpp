#include "lyric.h"

tstLyric stLyric[MAX_LINE];
char acLrcBuffer[MAX_LINE][MAX_LINE_LEN] = {0x00};

/* The max lyric line showed on box */
#define MAX_SHOW_LINE	10

void Lyric_Box::vInputLyric(const char* pcText, const uint32 u32Len)
{
	uint8 u8LrcIdx = 0;
	/* Get the array relative position which the data should save in */
	u8LrcIdx = u8PutQueue(m_u8LrcCnt);
	m_u8LrcCnt++;
	memset(m_acMultiLyricLine[u8LrcIdx], 0x00, MAX_LINE_LEN);
	/* Save lyric into internal buffer */
	memcpy(m_acMultiLyricLine[u8LrcIdx], pcText, u32Len);
	/* Show LRC on box, and LRC number should be less than max number */
	m_u8LrcShowCnt = m_u8LrcCnt > m_u8LrcMaxShowNum ? m_u8LrcMaxShowNum : m_u8LrcCnt;
}

/* Overloader of draw method */
void Lyric_Box::draw()
{
	uint8 u8Idx = 0;
	int dx = 0, dy = 0;

	draw_box();
	fl_font(labelfont(), labelsize());
	fl_color(labelcolor());

	/* Show all saved lyrics */
	for (u8Idx = 0; u8Idx < m_u8LrcShowCnt; u8Idx++)
	{
		fl_push_clip(x(), y(), w(), h());
		/* It's needed to set dx and dy to 0 before calling fl_measure */
		dx = 0;
		dy = 0;
		uint8 u8LrcIdx = u8GetQueue(u8Idx);
		//printf("%d-%s\n", u8LrcIdx, m_acMultiLyricLine[u8LrcIdx]);
		/* Get the width and height of the lyric */
		fl_measure(m_acMultiLyricLine[u8LrcIdx], dx, dy);
		fl_draw(m_acMultiLyricLine[u8LrcIdx], x() + w() / 2 - dx / 2, y() + h() - (m_u8LrcShowCnt - u8Idx) * (dy + 5));
		fl_pop_clip();
		draw_label();
		Sleep(10);
	}
}

char acTitle[MAX_LINE_LEN] = {0x00};
char acAuthor[MAX_LINE_LEN] = { 0x00 };
char* pcSkipLyricTime(char *pcLrc)
{
	char *pcStr = NULL;
	char *pcRet = NULL;
	pcStr = pcLrc;
	/* First '[' */
	if (*pcStr == '[')
	{
		while (*pcStr != ']')
		{
			pcStr++;
			if ((*pcStr == 't') && 
				(*(pcStr + 1) == 'i') && 
				(*(pcStr + 2) == ':')
				)
			{
				memcpy(acTitle, pcStr, strlen(pcStr) - 1);
				//printf("Ti:%d-%s\n",strlen(pcStr), pcStr);
				break;
			}
			else if ((*pcStr == 'b') &&
				(*(pcStr + 1) == 'y') &&
				(*(pcStr + 2) == ':')
				)
			{
				memcpy(acAuthor, pcStr, strlen(pcStr) - 1);
				break;
			}
			else
			{
				pcRet = pcStr + 1;
			}
		}
	}
	/* Return pointer place at the first charactor after ']' */
	return pcRet;
}

#define LRC_TIME_LEN 10
time_t tLoadLyricTime(char *pcStr)
{
	int8_t i8SegTimeLow, i8SegTimeHigh;
	uint8 u8SegTime = 0;
	time_t Time = 0;

	/* Segment2: Get the millisecond */
	i8SegTimeLow = i8Char2Dec(*(pcStr));
	i8SegTimeHigh = i8Char2Dec(*(pcStr - 1));
	//printf("Msec:%d%d\n", i8SegTimeHigh, i8SegTimeLow);
	if ((i8SegTimeLow != -1) && (i8SegTimeHigh != -1))
	{
		u8SegTime = i8SegTimeHigh * 10 + i8SegTimeLow;
		pcStr = pcStr - 3;
	}
	Time = u8SegTime;

	/* Segment2: Get the second */
	i8SegTimeLow = i8Char2Dec(*(pcStr));
	i8SegTimeHigh = i8Char2Dec(*(pcStr - 1));
	//printf("Sec:%d%d\n", i8SegTimeHigh, i8SegTimeLow);
	if ((i8SegTimeLow != -1) && (i8SegTimeHigh != -1))
	{
		u8SegTime = i8SegTimeHigh * 10 + i8SegTimeLow;
		pcStr = pcStr - 3;
	}
	Time = Time + (u8SegTime * 1000);

	/* Segment3: Get the minute */
	i8SegTimeLow = i8Char2Dec(*(pcStr));
	i8SegTimeHigh = i8Char2Dec(*(pcStr - 1));
	//printf("Min:%d%d\n", i8SegTimeHigh, i8SegTimeLow);
	if ((i8SegTimeLow != -1) && (i8SegTimeHigh != -1))
	{
		u8SegTime = i8SegTimeHigh * 10 + i8SegTimeLow;
		pcStr = pcStr - 3;
	}
	Time = Time + (u8SegTime * 60000);
	//printf("Time:%d-%s\n", Time, pcStr);
	return Time;
}

uint8 u8LrcIndex = 0;
uint8 u8ReadLyric(const char* pcPath)
{
	FILE *Rfp = NULL;
	
	uint32 u32LrcLineLen = 0;
	char* pcLrcLine = NULL;
	char acTmpBuffer[MAX_LINE_LEN];
	//if (fopen_s(&Rfp, pcPath, "r") == 0)
	if (fopen_s(&Rfp, "E:\\Study\\Listening\\Education\\face-covering-requirements-end-but-some-us-parents-are-worried.lrc", "r") == 0)
	{
		do/* Read all content from file to buffer */
		{
			pcLrcLine = fgets(acTmpBuffer, MAX_LINE_LEN, Rfp);
			/* Skip time as format [00:00.00] in each lrc */
			char* pcStr = pcSkipLyricTime(acTmpBuffer);
			if (pcStr != NULL)
			{
				u32LrcLineLen = strlen(acTmpBuffer);
				/* Deduct length of position time like [00:00.00] */
				memcpy(acLrcBuffer[u8LrcIndex], pcStr, u32LrcLineLen - LRC_TIME_LEN);
				stLyric[u8LrcIndex].pcLrc = acLrcBuffer[u8LrcIndex];
				stLyric[u8LrcIndex].tLrcTime = tLoadLyricTime(pcStr - 2);
				u8LrcIndex++;
			}
		} while (!feof(Rfp));
	}
	/* Total size of lyric that acculated by lyric row */
	return u8LrcIndex;
}

/* Search lyric by lyric time */
int8_t i8SearchLyric(time_t tCurTime)
{
	int8_t i8Ret = 0;
	uint8 u8Idx = 0;

	/* Out of range */
	if ((tCurTime < stLyric[0].tLrcTime) || (tCurTime > stLyric[u8LrcIndex - 1].tLrcTime))
	{
		i8Ret = -1;
	}
	else
	{
		uint8 u8BiggestIdx = u8LrcIndex;
		uint8 u8MidIdx = u8LrcIndex / 2;
		u8MidIdx = u8MidIdx - 1;
		do
		{
			if (tCurTime < stLyric[u8MidIdx].tLrcTime)/* Search lyric forward */
			{
				u8BiggestIdx = u8MidIdx;
				u8MidIdx = u8MidIdx / 2;
			}
			else/* Search lyric backward */
			{
				u8MidIdx = (u8MidIdx + u8BiggestIdx) / 2;
			}
		} while (!((tCurTime >= stLyric[u8MidIdx].tLrcTime) && (tCurTime <= stLyric[u8MidIdx + 1].tLrcTime)));
		i8Ret = u8MidIdx;
	}
	//cout << stLyric[i8Ret].tLrcTime << '#' << stLyric[i8Ret + 1].tLrcTime << endl;
	//printf("F:%d-%d\n", stLyric[i8Ret].tLrcTime, stLyric[i8Ret + 1].tLrcTime);
	return i8Ret;
}
