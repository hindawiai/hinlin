<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __EMU10K1_SYNTH_H
#घोषणा __EMU10K1_SYNTH_H
/*
 *  Defines क्रम the Emu10k1 WaveTable synth
 *
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/emu10k1.h>
#समावेश <sound/emux_synth.h>

/* sequencer device id */
#घोषणा SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH	"emu10k1-synth"

/* argument क्रम snd_seq_device_new */
काष्ठा snd_emu10k1_synth_arg अणु
	काष्ठा snd_emu10k1 *hwptr;	/* chip */
	पूर्णांक index;		/* sequencer client index */
	पूर्णांक seq_ports;		/* number of sequencer ports to be created */
	पूर्णांक max_voices;		/* maximum number of voices क्रम wavetable */
पूर्ण;

#घोषणा EMU10K1_MAX_MEMSIZE	(32 * 1024 * 1024) /* 32MB */

#पूर्ण_अगर
