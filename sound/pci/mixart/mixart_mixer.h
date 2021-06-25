<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * include file क्रम mixer
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_MIXART_MIXER_H
#घोषणा __SOUND_MIXART_MIXER_H

/* exported */
पूर्णांक mixart_update_playback_stream_level(काष्ठा snd_mixart* chip, पूर्णांक is_aes, पूर्णांक idx);
पूर्णांक mixart_update_capture_stream_level(काष्ठा snd_mixart* chip, पूर्णांक is_aes);
पूर्णांक snd_mixart_create_mixer(काष्ठा mixart_mgr* mgr);

#पूर्ण_अगर /* __SOUND_MIXART_MIXER_H */
