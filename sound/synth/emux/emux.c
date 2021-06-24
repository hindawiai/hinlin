<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Routines क्रम control of EMU WaveTable chip
 */

#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <sound/core.h>
#समावेश <sound/emux_synth.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश "emux_voice.h"

MODULE_AUTHOR("Takashi Iwai");
MODULE_DESCRIPTION("Routines for control of EMU WaveTable chip");
MODULE_LICENSE("GPL");

/*
 * create a new hardware dependent device क्रम Emu8000/Emu10k1
 */
पूर्णांक snd_emux_new(काष्ठा snd_emux **remu)
अणु
	काष्ठा snd_emux *emu;

	*remu = शून्य;
	emu = kzalloc(माप(*emu), GFP_KERNEL);
	अगर (emu == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&emu->voice_lock);
	mutex_init(&emu->रेजिस्टर_mutex);

	emu->client = -1;
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	emu->oss_synth = शून्य;
#पूर्ण_अगर
	emu->max_voices = 0;
	emu->use_समय = 0;

	समयr_setup(&emu->tlist, snd_emux_समयr_callback, 0);
	emu->समयr_active = 0;

	*remu = emu;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emux_new);

/*
 */
अटल पूर्णांक sf_sample_new(व्योम *निजी_data, काष्ठा snd_sf_sample *sp,
				  काष्ठा snd_util_memhdr *hdr,
				  स्थिर व्योम __user *buf, दीर्घ count)
अणु
	काष्ठा snd_emux *emu = निजी_data;
	वापस emu->ops.sample_new(emu, sp, hdr, buf, count);
	
पूर्ण

अटल पूर्णांक sf_sample_मुक्त(व्योम *निजी_data, काष्ठा snd_sf_sample *sp,
				   काष्ठा snd_util_memhdr *hdr)
अणु
	काष्ठा snd_emux *emu = निजी_data;
	वापस emu->ops.sample_मुक्त(emu, sp, hdr);
	
पूर्ण

अटल व्योम sf_sample_reset(व्योम *निजी_data)
अणु
	काष्ठा snd_emux *emu = निजी_data;
	emu->ops.sample_reset(emu);
पूर्ण

पूर्णांक snd_emux_रेजिस्टर(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक index, अक्षर *name)
अणु
	पूर्णांक err;
	काष्ठा snd_sf_callback sf_cb;

	अगर (snd_BUG_ON(!emu->hw || emu->max_voices <= 0))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!card || !name))
		वापस -EINVAL;

	emu->card = card;
	emu->name = kstrdup(name, GFP_KERNEL);
	emu->voices = kसुस्मृति(emu->max_voices, माप(काष्ठा snd_emux_voice),
			      GFP_KERNEL);
	अगर (emu->voices == शून्य)
		वापस -ENOMEM;

	/* create soundfont list */
	स_रखो(&sf_cb, 0, माप(sf_cb));
	sf_cb.निजी_data = emu;
	अगर (emu->ops.sample_new)
		sf_cb.sample_new = sf_sample_new;
	अगर (emu->ops.sample_मुक्त)
		sf_cb.sample_मुक्त = sf_sample_मुक्त;
	अगर (emu->ops.sample_reset)
		sf_cb.sample_reset = sf_sample_reset;
	emu->sflist = snd_sf_new(&sf_cb, emu->memhdr);
	अगर (emu->sflist == शून्य)
		वापस -ENOMEM;

	अगर ((err = snd_emux_init_hwdep(emu)) < 0)
		वापस err;

	snd_emux_init_voices(emu);

	snd_emux_init_seq(emu, card, index);
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	snd_emux_init_seq_oss(emu);
#पूर्ण_अगर
	snd_emux_init_virmidi(emu, card);

	snd_emux_proc_init(emu, card, index);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emux_रेजिस्टर);

/*
 */
पूर्णांक snd_emux_मुक्त(काष्ठा snd_emux *emu)
अणु
	अचिन्हित दीर्घ flags;

	अगर (! emu)
		वापस -EINVAL;

	spin_lock_irqsave(&emu->voice_lock, flags);
	अगर (emu->समयr_active)
		del_समयr(&emu->tlist);
	spin_unlock_irqrestore(&emu->voice_lock, flags);

	snd_emux_proc_मुक्त(emu);
	snd_emux_delete_virmidi(emu);
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	snd_emux_detach_seq_oss(emu);
#पूर्ण_अगर
	snd_emux_detach_seq(emu);
	snd_emux_delete_hwdep(emu);
	snd_sf_मुक्त(emu->sflist);
	kमुक्त(emu->voices);
	kमुक्त(emu->name);
	kमुक्त(emu);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emux_मुक्त);
