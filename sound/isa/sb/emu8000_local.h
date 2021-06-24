<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __EMU8000_LOCAL_H
#घोषणा __EMU8000_LOCAL_H
/*
 *  Local defininitons क्रम the emu8000 (AWE32/64)
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/emu8000.h>
#समावेश <sound/emu8000_reg.h>

/* emu8000_patch.c */
पूर्णांक snd_emu8000_sample_new(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
			   काष्ठा snd_util_memhdr *hdr,
			   स्थिर व्योम __user *data, दीर्घ count);
पूर्णांक snd_emu8000_sample_मुक्त(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
			    काष्ठा snd_util_memhdr *hdr);
व्योम snd_emu8000_sample_reset(काष्ठा snd_emux *rec);

/* emu8000_callback.c */
व्योम snd_emu8000_ops_setup(काष्ठा snd_emu8000 *emu);

/* emu8000_pcm.c */
पूर्णांक snd_emu8000_pcm_new(काष्ठा snd_card *card, काष्ठा snd_emu8000 *emu, पूर्णांक index);

#पूर्ण_अगर	/* __EMU8000_LOCAL_H */
