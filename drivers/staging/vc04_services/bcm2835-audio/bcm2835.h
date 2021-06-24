<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#अगर_अघोषित __SOUND_ARM_BCM2835_H
#घोषणा __SOUND_ARM_BCM2835_H

#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/raspberrypi/vchiq.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm-indirect.h>

#घोषणा MAX_SUBSTREAMS   (8)
#घोषणा AVAIL_SUBSTREAMS_MASK  (0xff)

क्रमागत अणु
	CTRL_VOL_MUTE,
	CTRL_VOL_UNMUTE
पूर्ण;

/* macros क्रम alsa2chip and chip2alsa, instead of functions */

// convert alsa to chip volume (defined as macro rather than function call)
#घोषणा alsa2chip(vol) (uपूर्णांक)(-(((vol) << 8) / 100))

// convert chip to alsa volume
#घोषणा chip2alsa(vol) -(((vol) * 100) >> 8)

#घोषणा CHIP_MIN_VOLUME		26214 /* minimum level aka mute */

/* Some स्थिरants क्रम values .. */
क्रमागत snd_bcm2835_route अणु
	AUDIO_DEST_AUTO = 0,
	AUDIO_DEST_HEADPHONES = 1,
	AUDIO_DEST_HDMI = 2,
	AUDIO_DEST_MAX,
पूर्ण;

क्रमागत snd_bcm2835_ctrl अणु
	PCM_PLAYBACK_VOLUME,
	PCM_PLAYBACK_MUTE,
	PCM_PLAYBACK_DEVICE,
पूर्ण;

काष्ठा bcm2835_vchi_ctx अणु
	काष्ठा vchiq_instance *instance;
पूर्ण;

/* definition of the chip-specअगरic record */
काष्ठा bcm2835_chip अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm *pcm_spdअगर;
	काष्ठा device *dev;
	काष्ठा bcm2835_alsa_stream *alsa_stream[MAX_SUBSTREAMS];

	पूर्णांक volume;
	पूर्णांक dest;
	पूर्णांक mute;

	अचिन्हित पूर्णांक खोलोed;
	अचिन्हित पूर्णांक spdअगर_status;
	काष्ठा mutex audio_mutex;

	काष्ठा bcm2835_vchi_ctx *vchi_ctx;
पूर्ण;

काष्ठा bcm2835_alsa_stream अणु
	काष्ठा bcm2835_chip *chip;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_indirect pcm_indirect;

	पूर्णांक draining;

	atomic_t pos;
	अचिन्हित पूर्णांक period_offset;
	अचिन्हित पूर्णांक buffer_size;
	अचिन्हित पूर्णांक period_size;
	kसमय_प्रकार पूर्णांकerpolate_start;

	काष्ठा bcm2835_audio_instance *instance;
	पूर्णांक idx;
पूर्ण;

पूर्णांक snd_bcm2835_new_ctl(काष्ठा bcm2835_chip *chip);
पूर्णांक snd_bcm2835_new_pcm(काष्ठा bcm2835_chip *chip, स्थिर अक्षर *name,
			पूर्णांक idx, क्रमागत snd_bcm2835_route route,
			u32 numchannels, bool spdअगर);

पूर्णांक snd_bcm2835_new_hdmi_ctl(काष्ठा bcm2835_chip *chip);
पूर्णांक snd_bcm2835_new_headphones_ctl(काष्ठा bcm2835_chip *chip);

पूर्णांक bcm2835_new_vchi_ctx(काष्ठा device *dev, काष्ठा bcm2835_vchi_ctx *vchi_ctx);
व्योम bcm2835_मुक्त_vchi_ctx(काष्ठा bcm2835_vchi_ctx *vchi_ctx);

पूर्णांक bcm2835_audio_खोलो(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_बंद(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_set_params(काष्ठा bcm2835_alsa_stream *alsa_stream,
			     अचिन्हित पूर्णांक channels, अचिन्हित पूर्णांक samplerate,
			     अचिन्हित पूर्णांक bps);
पूर्णांक bcm2835_audio_start(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_stop(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_drain(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_set_ctls(काष्ठा bcm2835_alsa_stream *alsa_stream);
पूर्णांक bcm2835_audio_ग_लिखो(काष्ठा bcm2835_alsa_stream *alsa_stream,
			अचिन्हित पूर्णांक count,
			व्योम *src);
व्योम bcm2835_playback_fअगरo(काष्ठा bcm2835_alsa_stream *alsa_stream,
			   अचिन्हित पूर्णांक size);
अचिन्हित पूर्णांक bcm2835_audio_retrieve_buffers(काष्ठा bcm2835_alsa_stream *alsa_stream);

#पूर्ण_अगर /* __SOUND_ARM_BCM2835_H */
