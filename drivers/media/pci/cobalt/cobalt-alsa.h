<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  ALSA पूर्णांकerface to cobalt PCM capture streams
 *
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

काष्ठा snd_card;

काष्ठा snd_cobalt_card अणु
	काष्ठा cobalt_stream *s;
	काष्ठा snd_card *sc;
	अचिन्हित पूर्णांक capture_transfer_करोne;
	अचिन्हित पूर्णांक hwptr_करोne_capture;
	अचिन्हित alsa_record_cnt;
	काष्ठा snd_pcm_substream *capture_pcm_substream;

	अचिन्हित पूर्णांक pb_size;
	अचिन्हित पूर्णांक pb_count;
	अचिन्हित पूर्णांक pb_pos;
	अचिन्हित pb_filled;
	bool alsa_pb_channel;
	अचिन्हित alsa_playback_cnt;
	काष्ठा snd_pcm_substream *playback_pcm_substream;
पूर्ण;

पूर्णांक cobalt_alsa_init(काष्ठा cobalt_stream *s);
व्योम cobalt_alsa_निकास(काष्ठा cobalt_stream *s);
