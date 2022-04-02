#include "../App/Aplayer.h"
#include <FL/Fl_Native_File_Chooser.H>
#include "Windows.h"
#include "cdef.h"
#include "audio.h"
#include <process.h>
#include "lyric.h"
#include "panelif.h"

//#define UPPER_BOX_SHOW

#ifdef UPPER_BOX_SHOW
/* The upper part of lyric display area */
Lyric_Box* Lyric_Show_Upper;
#endif
/* The middle part of lyric display area */
Lyric_Box* Lyric_Show_Middle;

Mtk_audio* clAudio;

extern char acLrcBuffer[MAX_LINE][MAX_LINE_LEN];
uint8 u8LrcNum = 0;
uint8 u8Cnt = 0;
void vLoadLyric_Upper(uint8 u8UpperCnt)
{
#ifdef UPPER_BOX_SHOW
	/* Push playded lyrics to show on upper-box */
	Lyric_Show_Upper->vInputLyric(acLrcBuffer[u8UpperCnt], strlen(acLrcBuffer[u8UpperCnt]));
#endif
}

void vLoadLyric_Middle(uint8 u8Cnt)
{
	uint8 u8UpperCnt = u8Cnt;
	/* Push playing lyric to show on middle-box */
	Lyric_Show_Middle->vInputLyric(acLrcBuffer[u8Cnt], strlen(acLrcBuffer[u8Cnt]));
	//u8Cnt++;
	vLoadLyric_Upper(u8UpperCnt - 1);
	Window_Player->redraw();
	//if (u8Cnt < u8LrcNum)//Load all lyric
	//{
	//	Fl::repeat_timeout(1, vLoadLyric_Middle);
	//}
}



void Button_Play_Callback(Fl_Button*, void*)
{
	static uint8 u8State = PLAY_STATE;
	if (u8State == PLAY_STATE)
	{
		printf("Play\n");
		u8State = PAUSE_STATE;
		Button_Play->label("@+2||");
		//Fl::add_timeout(1, vLoadLyric_Middle);
	}
	else
	{
		printf("Pause\n");
		u8State = PLAY_STATE;
		Button_Play->label("@+2>");
		//Fl::remove_timeout(vLoadLyric_Middle);
	}
}

/* Show last lyric have played on show box */
void Button_LastLrc_Callback(Fl_Button*, void*)
{
	/* u8Cnt has increased by once after inputing to middler-box buffer, so it's not enough 
	to deduct by only one, should deduct by two */
	u8Cnt = u8Cnt - 2;
	/* Push last lyric to show on middle-box right now */
	Lyric_Show_Middle->vInputLyric(acLrcBuffer[u8Cnt], strlen(acLrcBuffer[u8Cnt]));
	/* Push lyrics that have played to show on upper-box, so need to refresh circle queue backward */
	//uint8 u8Oldeset = Lyric_Show_Upper->u8GetOldest();
	//Lyric_Show_Upper->vBackwardLyric(u8Oldeset);
	//Lyric_Show_Upper->vSetOldest(u8Oldeset + 2);
	Window_Player->redraw();
}

void Button_NextLrc_Callback(Fl_Button*, void*)
{

}


char chrFilePath[256] = {0x00};
/* The length of directoy where file place */
size_t szDirPathLen = 0x00;
void Pick_Directory()
{
	Fl_Native_File_Chooser File_Chooser;
	/* Choose a directory not file */
	File_Chooser.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
	File_Chooser.title("Pick a Directory as list");
	//FlChooser.directory(G_filename->value());
	struct dirent **File_list;//TODO: why don't use arr[][]
	switch (File_Chooser.show())
	{
	case -1:// ERROR
		printf("ERROR: %s\n", File_Chooser.errmsg());
		break;

	case  1:// CANCEL 
		printf("*** CANCEL\n");
		fl_beep();
		break;

	default:// PICKED DIR
		if (File_Chooser.filename())
		{
			sprintf_s(chrFilePath, "%s\\", File_Chooser.filename());
			szDirPathLen = strlen(chrFilePath);
			//printf("dirname='%s'\n", File_Chooser.filename());
			/* Get all files name into File_list*/
			int32_t i32File_Num = fl_filename_list(File_Chooser.filename(), &File_list);
			uint8 u8Idx = 0;
			/* Show all mp3 file name on Browser */
			for (u8Idx = 0; u8Idx < i32File_Num; u8Idx++)
			{
				if (fl_filename_match(File_list[u8Idx]->d_name, "*.mp3"))
				{
					Browser_List->add(File_list[u8Idx]->d_name);

				}
			}
		}
		else
		{
			//G_filename->value("NULL");
			printf("dirname='(null)'\n");
		}
		break;
	}
}

void Button_Create_Callback(Fl_Button*, void*)
{
	Pick_Directory();
}

boolean boPlayed = FALSE;
void PLayer_Position_Update(void *vp)
{
	int64_t i64CurTime = clAudio->Mtk_audio_GetPosition();
	/* Match the lyric in accordance with current time */
	int8_t i8Idx = i8SearchLyric(i64CurTime);
	if (i8Idx != -1)
	{
		vLoadLyric_Middle(i8Idx);
	}
	//else
	{
		//printf("Find no lrc\n");
	}
	Fl::repeat_timeout(1, PLayer_Position_Update);
}

void LrcUpdate_Thread(void* p)
{
	Fl::add_timeout(1, PLayer_Position_Update);
}

void Player_Thread(void* p)
{
	clAudio = new Mtk_audio();
	if (clAudio != NULL)
	{
		clAudio->Mtk_audio_Open(chrFilePath);
		int64_t i64Duration = clAudio->Mtk_audio_GetDuration();
		int64_t min = i64Duration / 1000 / 60;
		int64_t sec = i64Duration / 1000 % 60;
		printf("D:%lld-%lld-%lld\n", i64Duration, min, sec);

		//Fl::add_timeout(1, PLayer_Position_Update);
		clAudio->Mtk_audio_Play();	
	}
	else
	{
		printf("NULL AUDIO\n");
	}
}

void Browser_List_Callback(Fl_Browser*, void*)
{
	static boolean boPlaying = FALSE;
	static uint32 u32ThreadId = 0u;
	if (Fl::event_clicks() == 1)//double click-
	{
		if (u32ThreadId == 0u)//Nothing is playing
		{
			//boPlaying = TRUE;
			const int itemIdx = Browser_List->value();
			const char *pcFileName = (const char *)Browser_List->text(itemIdx);
			/* Clear file path except directory path */
			memset(&chrFilePath[szDirPathLen], 0x00, 256 - szDirPathLen);
			/* Directory path + file path */
			strcat_s(chrFilePath, pcFileName);
			printf("Path:%s\n", chrFilePath);

			/* Create a thread to play */
			u32ThreadId = _beginthread(Player_Thread, 0, NULL);
			/* Create a thread to update lyric */
			_beginthread(LrcUpdate_Thread, 0, NULL);
		}
		else//Something is playing, stop it
		{
			printf("END\n");
			_endthread();
		}

	}
}

#define LRC_UPPER_BOX_AREA_Y	20
#define LRC_UPPER_BOX_AREA_H	200

#define LRC_MIDDLE_BOX_AREA_Y	(LRC_UPPER_BOX_AREA_Y + LRC_UPPER_BOX_AREA_H)
#define LRC_MIDDLE_BOX_AREA_H	60

#define LRC_LOWER_BOX_AREA_Y	(LRC_MIDDLE_BOX_AREA_Y + LRC_MIDDLE_BOX_AREA_H)
#define LRC_LOWER_BOX_AREA_H	200
void Init()
{
	u8LrcNum = u8ReadLyric("E:\\Study\\Listening\\Education\\face-covering-requirements-end-but-some-us-parents-are-worried.lrc");
	
#if 1
	Lyric_Show_Middle = new Lyric_Box(15, LRC_MIDDLE_BOX_AREA_Y, 700, LRC_MIDDLE_BOX_AREA_H);
	Lyric_Show_Middle->vSetShowNum(1);
	Lyric_Show_Middle->vSetQueueLen(1);
	/* Add box widget to window */
	Group_Lyric->add(Lyric_Show_Middle);
	//Group_Lyric->image();
	/* Box settings */
	//Lyric_Show_Middle->box(FL_FRAME_BOX);
	Lyric_Show_Middle->align(FL_ALIGN_BOTTOM);
	/* Font settings */
	Lyric_Show_Middle->labelsize(16);
	Lyric_Show_Middle->labelcolor(FL_BLUE);
	Lyric_Show_Middle->labelfont(FL_BOLD_ITALIC);
#endif

#ifdef UPPER_BOX_SHOW
	Lyric_Show_Upper = new Lyric_Box(15, LRC_UPPER_BOX_AREA_Y, 700, LRC_UPPER_BOX_AREA_H);
	Lyric_Show_Upper->vSetShowNum(20);
	Lyric_Show_Upper->vSetQueueLen(20);
	/* Add box widget to window */
	Group_Lyric->add(Lyric_Show_Upper);
	//Lyric_Show_Upper->box(FL_FRAME_BOX);
	Lyric_Show_Upper->align(FL_ALIGN_BOTTOM);
	/* Font settings */
	Lyric_Show_Upper->labelsize(14);
	Lyric_Show_Upper->labelcolor(FL_BLACK);
	Lyric_Show_Middle->labelfont(FL_ITALIC);
#endif
	
}