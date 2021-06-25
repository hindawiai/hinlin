<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#अगर_अघोषित PLAYBACK_H
#घोषणा PLAYBACK_H

#समावेश <sound/pcm.h>

#समावेश "driver.h"

/*
 * When the TonePort is used with jack in full duplex mode and the outमाला_दो are
 * not connected, the software monitor produces an ugly noise since everything
 * written to the output buffer (i.e., the input संकेत) will be repeated in
 * the next period (sounds like a delay effect). As a workaround, the output
 * buffer is cleared after the data have been पढ़ो, but there must be a better
 * solution. Until one is found, this workaround can be used to fix the
 * problem.
 */
#घोषणा USE_CLEAR_BUFFER_WORKAROUND 1

बाह्य स्थिर काष्ठा snd_pcm_ops snd_line6_playback_ops;

बाह्य पूर्णांक line6_create_audio_out_urbs(काष्ठा snd_line6_pcm *line6pcm);
बाह्य पूर्णांक line6_submit_audio_out_all_urbs(काष्ठा snd_line6_pcm *line6pcm);

#पूर्ण_अगर
