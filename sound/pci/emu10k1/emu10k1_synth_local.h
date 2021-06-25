<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __EMU10K1_SYNTH_LOCAL_H
#घोषणा __EMU10K1_SYNTH_LOCAL_H
/*
 *  Local defininitons क्रम Emu10k1 wavetable
 *
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1_synth.h>

/* emu10k1_patch.c */
पूर्णांक snd_emu10k1_sample_new(काष्ठा snd_emux *निजी_data,
			   काष्ठा snd_sf_sample *sp,
			   काष्ठा snd_util_memhdr *hdr,
			   स्थिर व्योम __user *_data, दीर्घ count);
पूर्णांक snd_emu10k1_sample_मुक्त(काष्ठा snd_emux *निजी_data,
			    काष्ठा snd_sf_sample *sp,
			    काष्ठा snd_util_memhdr *hdr);
पूर्णांक snd_emu10k1_memhdr_init(काष्ठा snd_emux *emu);

/* emu10k1_callback.c */
व्योम snd_emu10k1_ops_setup(काष्ठा snd_emux *emu);
पूर्णांक snd_emu10k1_synth_get_voice(काष्ठा snd_emu10k1 *hw);


#पूर्ण_अगर	/* __EMU10K1_SYNTH_LOCAL_H */
