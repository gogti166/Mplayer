#include <stdio.h>
#include <stdlib.h>
#include "../Core/audio.h"
#include "../Core/lyric.h"
//#include "../Core/panelif.h"

#if 1
#include "Aplayer.h"
#include "../Core/panelif.h"

int main(int argc, char* argv[])
{
	Fl::visible_focus(0);
	Fl_Window* FlWindow = make_window();
	Init();
	FlWindow->show();
	return Fl::run();

	/*Mtk_audio* clAudio = new Mtk_audio();
	clAudio->Mtk_audio_Open("E:\\Study\\Listening\\Education\\us-parents-look-to-have-more-influence-over-school-curriculums.mp3");
	clAudio->Mtk_audio_Play();
	int64_t i64Duration = clAudio->Mtk_audio_GetDuration();
	int64_t min = i64Duration / 1000 / 60;
	int64_t sec = i64Duration / 1000 % 60;
	printf("D:%lld-%lld-%lld\n", i64Duration, min, sec);*/
	while (1);
	return 0;
}

#else


#endif