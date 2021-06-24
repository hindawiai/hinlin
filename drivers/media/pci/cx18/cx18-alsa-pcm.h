<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA PCM device क्रम the
 *  ALSA पूर्णांकerface to cx18 PCM capture streams
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 */

पूर्णांक snd_cx18_pcm_create(काष्ठा snd_cx18_card *cxsc);

/* Used by cx18-mailbox to announce the PCM data to the module */
व्योम cx18_alsa_announce_pcm_data(काष्ठा snd_cx18_card *card, u8 *pcm_data,
				 माप_प्रकार num_bytes);
