<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * media.h - Media Controller specअगरic ALSA driver code
 *
 * Copyright (c) 2019 Shuah Khan <shuah@kernel.org>
 *
 */

/*
 * This file adds Media Controller support to the ALSA driver
 * to use the Media Controller API to share the tuner with DVB
 * and V4L2 drivers that control the media device.
 *
 * The media device is created based on the existing quirks framework.
 * Using this approach, the media controller API usage can be added क्रम
 * a specअगरic device.
 */
#अगर_अघोषित __MEDIA_H

#अगर_घोषित CONFIG_SND_USB_AUDIO_USE_MEDIA_CONTROLLER

#समावेश <linux/media.h>
#समावेश <media/media-device.h>
#समावेश <media/media-entity.h>
#समावेश <media/media-dev-allocator.h>
#समावेश <sound/asound.h>

काष्ठा media_ctl अणु
	काष्ठा media_device *media_dev;
	काष्ठा media_entity media_entity;
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;
	काष्ठा media_link *पूर्णांकf_link;
	काष्ठा media_pad media_pad;
	काष्ठा media_pipeline media_pipe;
पूर्ण;

/*
 * One source pad each क्रम SNDRV_PCM_STREAM_CAPTURE and
 * SNDRV_PCM_STREAM_PLAYBACK. One क्रम sink pad to link
 * to AUDIO Source
 */
#घोषणा MEDIA_MIXER_PAD_MAX    (SNDRV_PCM_STREAM_LAST + 2)

काष्ठा media_mixer_ctl अणु
	काष्ठा media_device *media_dev;
	काष्ठा media_entity media_entity;
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;
	काष्ठा media_link *पूर्णांकf_link;
	काष्ठा media_pad media_pad[MEDIA_MIXER_PAD_MAX];
	काष्ठा media_pipeline media_pipe;
पूर्ण;

पूर्णांक snd_media_device_create(काष्ठा snd_usb_audio *chip,
			    काष्ठा usb_पूर्णांकerface *अगरace);
व्योम snd_media_device_delete(काष्ठा snd_usb_audio *chip);
पूर्णांक snd_media_stream_init(काष्ठा snd_usb_substream *subs, काष्ठा snd_pcm *pcm,
			  पूर्णांक stream);
व्योम snd_media_stream_delete(काष्ठा snd_usb_substream *subs);
पूर्णांक snd_media_start_pipeline(काष्ठा snd_usb_substream *subs);
व्योम snd_media_stop_pipeline(काष्ठा snd_usb_substream *subs);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_media_device_create(काष्ठा snd_usb_audio *chip,
					  काष्ठा usb_पूर्णांकerface *अगरace)
						अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_media_device_delete(काष्ठा snd_usb_audio *chip) अणु पूर्ण
अटल अंतरभूत पूर्णांक snd_media_stream_init(काष्ठा snd_usb_substream *subs,
					काष्ठा snd_pcm *pcm, पूर्णांक stream)
						अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_media_stream_delete(काष्ठा snd_usb_substream *subs) अणु पूर्ण
अटल अंतरभूत पूर्णांक snd_media_start_pipeline(काष्ठा snd_usb_substream *subs)
					अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_media_stop_pipeline(काष्ठा snd_usb_substream *subs) अणु पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __MEDIA_H */
