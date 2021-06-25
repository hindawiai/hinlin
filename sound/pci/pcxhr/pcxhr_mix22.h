<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * low level पूर्णांकerface with पूर्णांकerrupt ans message handling
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_PCXHR_MIX22_H
#घोषणा __SOUND_PCXHR_MIX22_H

काष्ठा pcxhr_mgr;

पूर्णांक hr222_sub_init(काष्ठा pcxhr_mgr *mgr);
पूर्णांक hr222_sub_set_घड़ी(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक rate,
			पूर्णांक *changed);
पूर्णांक hr222_get_बाह्यal_घड़ी(काष्ठा pcxhr_mgr *mgr,
			     क्रमागत pcxhr_घड़ी_प्रकारype घड़ी_प्रकारype,
			     पूर्णांक *sample_rate);

पूर्णांक hr222_पढ़ो_gpio(काष्ठा pcxhr_mgr *mgr, पूर्णांक is_gpi, पूर्णांक *value);
पूर्णांक hr222_ग_लिखो_gpo(काष्ठा pcxhr_mgr *mgr, पूर्णांक value);
पूर्णांक hr222_manage_समयcode(काष्ठा pcxhr_mgr *mgr, पूर्णांक enable);

#घोषणा HR222_LINE_PLAYBACK_LEVEL_MIN		0	/* -25.5 dB */
#घोषणा HR222_LINE_PLAYBACK_ZERO_LEVEL		51	/* 0.0 dB */
#घोषणा HR222_LINE_PLAYBACK_LEVEL_MAX		99	/* +24.0 dB */

#घोषणा HR222_LINE_CAPTURE_LEVEL_MIN		0	/* -111.5 dB */
#घोषणा HR222_LINE_CAPTURE_ZERO_LEVEL		223	/* 0.0 dB */
#घोषणा HR222_LINE_CAPTURE_LEVEL_MAX		255	/* +16 dB */
#घोषणा HR222_MICRO_CAPTURE_LEVEL_MIN		0	/* -98.5 dB */
#घोषणा HR222_MICRO_CAPTURE_LEVEL_MAX		210	/* +6.5 dB */

पूर्णांक hr222_update_analog_audio_level(काष्ठा snd_pcxhr *chip,
				    पूर्णांक is_capture,
				    पूर्णांक channel);
पूर्णांक hr222_set_audio_source(काष्ठा snd_pcxhr *chip);
पूर्णांक hr222_iec958_capture_byte(काष्ठा snd_pcxhr *chip, पूर्णांक aes_idx,
			      अचिन्हित अक्षर *aes_bits);
पूर्णांक hr222_iec958_update_byte(काष्ठा snd_pcxhr *chip, पूर्णांक aes_idx,
			     अचिन्हित अक्षर aes_bits);

पूर्णांक hr222_add_mic_controls(काष्ठा snd_pcxhr *chip);

#पूर्ण_अगर /* __SOUND_PCXHR_MIX22_H */
