#include "audio.h"
#include "windows.h"
#include "cdef.h"

//"E:\\Study\\Listening\\Education\\us-parents-look-to-have-more-influence-over-school-curriculums.mp3"

int Mtk_audio::Mtk_audio_Open(const char *pFilePath)
{
	int iRet = -1;
	/* Create a Media */
	m_pAudio = libvlc_media_new_path(m_pInstance, pFilePath);
	if (m_pAudio != NULL)
	{
		printf("Mp3:%s\n", pFilePath);
		iRet = 0;
		libvlc_media_parse(m_pAudio);
	}
	else
	{
		printf("Open audio failed\n");
	}
	return iRet;
}

void Mtk_audio::Mtk_audio_Play()
{
	/* Create a Media Player object from a Media */
	if (m_boPlayed != true)
	{
		m_pPlayer = libvlc_media_player_new_from_media(m_pAudio);
		m_boPlayed = true;
	}
	
	if (m_pPlayer != NULL)
	{
		/* Start to play the media_player */
		libvlc_media_player_play(m_pPlayer);

		/* Let it play a bit */
		//Sleep((uint32)m_i64Duration);
		Sleep(330762);
		//Sleep(m_i64Duration);
		/* Stop playing */
		libvlc_media_player_stop(m_pPlayer);
		/* Free the media_player */
		libvlc_media_player_release(m_pPlayer);
		libvlc_release(m_pInstance);
	}
}

int64_t Mtk_audio::Mtk_audio_GetPosition()
{
	int64_t i64CurTime = 0;
	if (m_pPlayer != NULL)
	{
		/* Get the current song time(in ms). */
		i64CurTime = libvlc_media_player_get_time(m_pPlayer);

		/*int64_t min = i64CurTime / 1000 / 60;
		int64_t sec = i64CurTime / 1000 % 60;
		int64_t msec = i64CurTime - min * 6000 - sec * 1000;
		printf("D:%lld-%lld-%lld-%lld\n", i64CurTime, min, sec, msec);*/
	}
	return i64CurTime;
}

int64_t Mtk_audio::Mtk_audio_GetDuration()
{
	if (m_boPlayed != true)
	{
		/* Note, duration time is only avaliable after played */
		m_pPlayer = libvlc_media_player_new_from_media(m_pAudio);
		m_boPlayed = true;
	}
	m_i64Duration = libvlc_media_get_duration(m_pAudio);
	return m_i64Duration;
}