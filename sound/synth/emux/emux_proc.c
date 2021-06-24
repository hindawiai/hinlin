<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Proc पूर्णांकerface क्रम Emu8k/Emu10k1 WaveTable synth
 */

#समावेश <linux/रुको.h>
#समावेश <sound/core.h>
#समावेश <sound/emux_synth.h>
#समावेश <sound/info.h>
#समावेश "emux_voice.h"

अटल व्योम
snd_emux_proc_info_पढ़ो(काष्ठा snd_info_entry *entry, 
			काष्ठा snd_info_buffer *buf)
अणु
	काष्ठा snd_emux *emu;
	पूर्णांक i;

	emu = entry->निजी_data;
	mutex_lock(&emu->रेजिस्टर_mutex);
	अगर (emu->name)
		snd_iम_लिखो(buf, "Device: %s\n", emu->name);
	snd_iम_लिखो(buf, "Ports: %d\n", emu->num_ports);
	snd_iम_लिखो(buf, "Addresses:");
	क्रम (i = 0; i < emu->num_ports; i++)
		snd_iम_लिखो(buf, " %d:%d", emu->client, emu->ports[i]);
	snd_iम_लिखो(buf, "\n");
	snd_iम_लिखो(buf, "Use Counter: %d\n", emu->used);
	snd_iम_लिखो(buf, "Max Voices: %d\n", emu->max_voices);
	snd_iम_लिखो(buf, "Allocated Voices: %d\n", emu->num_voices);
	अगर (emu->memhdr) अणु
		snd_iम_लिखो(buf, "Memory Size: %d\n", emu->memhdr->size);
		snd_iम_लिखो(buf, "Memory Available: %d\n", snd_util_mem_avail(emu->memhdr));
		snd_iम_लिखो(buf, "Allocated Blocks: %d\n", emu->memhdr->nblocks);
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buf, "Memory Size: 0\n");
	पूर्ण
	अगर (emu->sflist) अणु
		mutex_lock(&emu->sflist->presets_mutex);
		snd_iम_लिखो(buf, "SoundFonts: %d\n", emu->sflist->fonts_size);
		snd_iम_लिखो(buf, "Instruments: %d\n", emu->sflist->zone_counter);
		snd_iम_लिखो(buf, "Samples: %d\n", emu->sflist->sample_counter);
		snd_iम_लिखो(buf, "Locked Instruments: %d\n", emu->sflist->zone_locked);
		snd_iम_लिखो(buf, "Locked Samples: %d\n", emu->sflist->sample_locked);
		mutex_unlock(&emu->sflist->presets_mutex);
	पूर्ण
#अगर 0  /* debug */
	अगर (emu->voices[0].state != SNDRV_EMUX_ST_OFF && emu->voices[0].ch >= 0) अणु
		काष्ठा snd_emux_voice *vp = &emu->voices[0];
		snd_iम_लिखो(buf, "voice 0: on\n");
		snd_iम_लिखो(buf, "mod delay=%x, atkhld=%x, dcysus=%x, rel=%x\n",
			    vp->reg.parm.moddelay,
			    vp->reg.parm.modatkhld,
			    vp->reg.parm.moddcysus,
			    vp->reg.parm.modrelease);
		snd_iम_लिखो(buf, "vol delay=%x, atkhld=%x, dcysus=%x, rel=%x\n",
			    vp->reg.parm.voldelay,
			    vp->reg.parm.volatkhld,
			    vp->reg.parm.voldcysus,
			    vp->reg.parm.volrelease);
		snd_iम_लिखो(buf, "lfo1 delay=%x, lfo2 delay=%x, pefe=%x\n",
			    vp->reg.parm.lfo1delay,
			    vp->reg.parm.lfo2delay,
			    vp->reg.parm.pefe);
		snd_iम_लिखो(buf, "fmmod=%x, tremfrq=%x, fm2frq2=%x\n",
			    vp->reg.parm.fmmod,
			    vp->reg.parm.tremfrq,
			    vp->reg.parm.fm2frq2);
		snd_iम_लिखो(buf, "cutoff=%x, filterQ=%x, chorus=%x, reverb=%x\n",
			    vp->reg.parm.cutoff,
			    vp->reg.parm.filterQ,
			    vp->reg.parm.chorus,
			    vp->reg.parm.reverb);
		snd_iम_लिखो(buf, "avol=%x, acutoff=%x, apitch=%x\n",
			    vp->avol, vp->acutoff, vp->apitch);
		snd_iम_लिखो(buf, "apan=%x, aaux=%x, ptarget=%x, vtarget=%x, ftarget=%x\n",
			    vp->apan, vp->aaux,
			    vp->ptarget,
			    vp->vtarget,
			    vp->ftarget);
		snd_iम_लिखो(buf, "start=%x, end=%x, loopstart=%x, loopend=%x\n",
			    vp->reg.start, vp->reg.end, vp->reg.loopstart, vp->reg.loखोलोd);
		snd_iम_लिखो(buf, "sample_mode=%x, rate=%x\n", vp->reg.sample_mode, vp->reg.rate_offset);
	पूर्ण
#पूर्ण_अगर
	mutex_unlock(&emu->रेजिस्टर_mutex);
पूर्ण


व्योम snd_emux_proc_init(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_info_entry *entry;
	अक्षर name[64];

	प्र_लिखो(name, "wavetableD%d", device);
	entry = snd_info_create_card_entry(card, name, card->proc_root);
	अगर (entry == शून्य)
		वापस;

	entry->content = SNDRV_INFO_CONTENT_TEXT;
	entry->निजी_data = emu;
	entry->c.text.पढ़ो = snd_emux_proc_info_पढ़ो;
पूर्ण

व्योम snd_emux_proc_मुक्त(काष्ठा snd_emux *emu)
अणु
	snd_info_मुक्त_entry(emu->proc);
	emu->proc = शून्य;
पूर्ण
