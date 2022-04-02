#ifndef AUDIO_H__
#define AUDIO_H__

#include <vlc/vlc.h>
class Mtk_audio
{
public:
	Mtk_audio()
	{
		/* Load the VLC engine */
		m_pInstance = libvlc_new(0, NULL);
		if (m_pInstance == NULL)
		{
			printf("#!#m_pInstance NULL\n");
		}
		else
		{
			printf("CREATOR VLC\n");
		}
	}
	int Mtk_audio_Open(const char *pFilePath);
	void Mtk_audio_Play();
	int64_t Mtk_audio_GetDuration();
	int64_t Mtk_audio_GetPosition();

private:
	char *m_pFilePath;
	bool m_boPlayed;
	int64_t m_i64Duration;
	libvlc_instance_t * m_pInstance;
	libvlc_media_t *m_pAudio;
	libvlc_media_player_t* m_pPlayer;
};

#endif