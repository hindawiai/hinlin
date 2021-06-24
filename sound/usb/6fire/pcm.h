<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#अगर_अघोषित USB6FIRE_PCM_H
#घोषणा USB6FIRE_PCM_H

#समावेश <sound/pcm.h>
#समावेश <linux/mutex.h>

#समावेश "common.h"

क्रमागत /* settings क्रम pcm */
अणु
	/* maximum of EP_W_MAX_PACKET_SIZE[] (see firmware.c) */
	PCM_N_URBS = 16, PCM_N_PACKETS_PER_URB = 8, PCM_MAX_PACKET_SIZE = 604
पूर्ण;

काष्ठा pcm_urb अणु
	काष्ठा sfire_chip *chip;

	/* BEGIN DO NOT SEPARATE */
	काष्ठा urb instance;
	काष्ठा usb_iso_packet_descriptor packets[PCM_N_PACKETS_PER_URB];
	/* END DO NOT SEPARATE */
	u8 *buffer;

	काष्ठा pcm_urb *peer;
पूर्ण;

काष्ठा pcm_substream अणु
	spinlock_t lock;
	काष्ठा snd_pcm_substream *instance;

	bool active;

	snd_pcm_uframes_t dma_off; /* current position in alsa dma_area */
	snd_pcm_uframes_t period_off; /* current position in current period */
पूर्ण;

काष्ठा pcm_runसमय अणु
	काष्ठा sfire_chip *chip;
	काष्ठा snd_pcm *instance;

	काष्ठा pcm_substream playback;
	काष्ठा pcm_substream capture;
	bool panic; /* अगर set driver won't करो anymore pcm on device */

	काष्ठा pcm_urb in_urbs[PCM_N_URBS];
	काष्ठा pcm_urb out_urbs[PCM_N_URBS];
	पूर्णांक in_packet_size;
	पूर्णांक out_packet_size;
	पूर्णांक in_n_analog; /* number of analog channels soundcard sends */
	पूर्णांक out_n_analog; /* number of analog channels soundcard receives */

	काष्ठा mutex stream_mutex;
	u8 stream_state; /* one of STREAM_XXX (pcm.c) */
	u8 rate; /* one of PCM_RATE_XXX */
	रुको_queue_head_t stream_रुको_queue;
	bool stream_रुको_cond;
पूर्ण;

पूर्णांक usb6fire_pcm_init(काष्ठा sfire_chip *chip);
व्योम usb6fire_pcm_पात(काष्ठा sfire_chip *chip);
व्योम usb6fire_pcm_destroy(काष्ठा sfire_chip *chip);
#पूर्ण_अगर /* USB6FIRE_PCM_H */
