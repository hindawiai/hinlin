<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Advanced Linux Sound Architecture
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <sound/core.h>

अटल पूर्णांक __init alsa_sound_last_init(व्योम)
अणु
	काष्ठा snd_card *card;
	पूर्णांक idx, ok = 0;
	
	prपूर्णांकk(KERN_INFO "ALSA device list:\n");
	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		card = snd_card_ref(idx);
		अगर (card) अणु
			prपूर्णांकk(KERN_INFO "  #%i: %s\n", idx, card->दीर्घname);
			snd_card_unref(card);
			ok++;
		पूर्ण
	पूर्ण
	अगर (ok == 0)
		prपूर्णांकk(KERN_INFO "  No soundcards found.\n");
	वापस 0;
पूर्ण

late_initcall_sync(alsa_sound_last_init);
