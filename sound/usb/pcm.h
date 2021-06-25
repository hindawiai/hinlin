<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_PCM_H
#घोषणा __USBAUDIO_PCM_H

snd_pcm_uframes_t snd_usb_pcm_delay(काष्ठा snd_usb_substream *subs,
				    अचिन्हित पूर्णांक rate);

व्योम snd_usb_set_pcm_ops(काष्ठा snd_pcm *pcm, पूर्णांक stream);
पूर्णांक snd_usb_pcm_suspend(काष्ठा snd_usb_stream *as);
पूर्णांक snd_usb_pcm_resume(काष्ठा snd_usb_stream *as);

पूर्णांक snd_usb_init_pitch(काष्ठा snd_usb_audio *chip,
		       स्थिर काष्ठा audioक्रमmat *fmt);
व्योम snd_usb_pपुनः_स्मृतिate_buffer(काष्ठा snd_usb_substream *subs);

पूर्णांक snd_usb_audioक्रमmat_set_sync_ep(काष्ठा snd_usb_audio *chip,
				    काष्ठा audioक्रमmat *fmt);

#पूर्ण_अगर /* __USBAUDIO_PCM_H */
