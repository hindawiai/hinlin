<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routine क्रम IRQ handling from GF1/InterWave chip
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/gus.h>

#अगर_घोषित CONFIG_SND_DEBUG
#घोषणा STAT_ADD(x)	((x)++)
#अन्यथा
#घोषणा STAT_ADD(x)	जबतक (0) अणु ; पूर्ण
#पूर्ण_अगर

irqवापस_t snd_gus_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_gus_card * gus = dev_id;
	अचिन्हित अक्षर status;
	पूर्णांक loop = 100;
	पूर्णांक handled = 0;

__again:
	status = inb(gus->gf1.reg_irqstat);
	अगर (status == 0)
		वापस IRQ_RETVAL(handled);
	handled = 1;
	/* snd_prपूर्णांकk(KERN_DEBUG "IRQ: status = 0x%x\n", status); */
	अगर (status & 0x02) अणु
		STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_midi_in);
		अगर (gus->gf1.पूर्णांकerrupt_handler_midi_in)
			gus->gf1.पूर्णांकerrupt_handler_midi_in(gus);
	पूर्ण
	अगर (status & 0x01) अणु
		STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_midi_out);
		अगर (gus->gf1.पूर्णांकerrupt_handler_midi_out)
			gus->gf1.पूर्णांकerrupt_handler_midi_out(gus);
	पूर्ण
	अगर (status & (0x20 | 0x40)) अणु
		अचिन्हित पूर्णांक alपढ़ोy, _current_;
		अचिन्हित अक्षर voice_status, voice;
		काष्ठा snd_gus_voice *pvoice;

		alपढ़ोy = 0;
		जबतक (((voice_status = snd_gf1_i_पढ़ो8(gus, SNDRV_GF1_GB_VOICES_IRQ)) & 0xc0) != 0xc0) अणु
			voice = voice_status & 0x1f;
			_current_ = 1 << voice;
			अगर (alपढ़ोy & _current_)
				जारी;	/* multi request */
			alपढ़ोy |= _current_;	/* mark request */
#अगर 0
			prपूर्णांकk(KERN_DEBUG "voice = %i, voice_status = 0x%x, "
			       "voice_verify = %i\n",
			       voice, voice_status, inb(GUSP(gus, GF1PAGE)));
#पूर्ण_अगर
			pvoice = &gus->gf1.voices[voice]; 
			अगर (pvoice->use) अणु
				अगर (!(voice_status & 0x80)) अणु	/* voice position IRQ */
					STAT_ADD(pvoice->पूर्णांकerrupt_stat_wave);
					pvoice->handler_wave(gus, pvoice);
				पूर्ण
				अगर (!(voice_status & 0x40)) अणु	/* volume ramp IRQ */
					STAT_ADD(pvoice->पूर्णांकerrupt_stat_volume);
					pvoice->handler_volume(gus, pvoice);
				पूर्ण
			पूर्ण अन्यथा अणु
				STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_voice_lost);
				snd_gf1_i_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
				snd_gf1_i_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (status & 0x04) अणु
		STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_समयr1);
		अगर (gus->gf1.पूर्णांकerrupt_handler_समयr1)
			gus->gf1.पूर्णांकerrupt_handler_समयr1(gus);
	पूर्ण
	अगर (status & 0x08) अणु
		STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_समयr2);
		अगर (gus->gf1.पूर्णांकerrupt_handler_समयr2)
			gus->gf1.पूर्णांकerrupt_handler_समयr2(gus);
	पूर्ण
	अगर (status & 0x80) अणु
		अगर (snd_gf1_i_look8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL) & 0x40) अणु
			STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_dma_ग_लिखो);
			अगर (gus->gf1.पूर्णांकerrupt_handler_dma_ग_लिखो)
				gus->gf1.पूर्णांकerrupt_handler_dma_ग_लिखो(gus);
		पूर्ण
		अगर (snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL) & 0x40) अणु
			STAT_ADD(gus->gf1.पूर्णांकerrupt_stat_dma_पढ़ो);
			अगर (gus->gf1.पूर्णांकerrupt_handler_dma_पढ़ो)
				gus->gf1.पूर्णांकerrupt_handler_dma_पढ़ो(gus);
		पूर्ण
	पूर्ण
	अगर (--loop > 0)
		जाओ __again;
	वापस IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम snd_gus_irq_info_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_gus_card *gus;
	काष्ठा snd_gus_voice *pvoice;
	पूर्णांक idx;

	gus = entry->निजी_data;
	snd_iम_लिखो(buffer, "midi out = %u\n", gus->gf1.पूर्णांकerrupt_stat_midi_out);
	snd_iम_लिखो(buffer, "midi in = %u\n", gus->gf1.पूर्णांकerrupt_stat_midi_in);
	snd_iम_लिखो(buffer, "timer1 = %u\n", gus->gf1.पूर्णांकerrupt_stat_समयr1);
	snd_iम_लिखो(buffer, "timer2 = %u\n", gus->gf1.पूर्णांकerrupt_stat_समयr2);
	snd_iम_लिखो(buffer, "dma write = %u\n", gus->gf1.पूर्णांकerrupt_stat_dma_ग_लिखो);
	snd_iम_लिखो(buffer, "dma read = %u\n", gus->gf1.पूर्णांकerrupt_stat_dma_पढ़ो);
	snd_iम_लिखो(buffer, "voice lost = %u\n", gus->gf1.पूर्णांकerrupt_stat_voice_lost);
	क्रम (idx = 0; idx < 32; idx++) अणु
		pvoice = &gus->gf1.voices[idx];
		snd_iम_लिखो(buffer, "voice %i: wave = %u, volume = %u\n",
					idx,
					pvoice->पूर्णांकerrupt_stat_wave,
					pvoice->पूर्णांकerrupt_stat_volume);
	पूर्ण
पूर्ण

व्योम snd_gus_irq_profile_init(काष्ठा snd_gus_card *gus)
अणु
	snd_card_ro_proc_new(gus->card, "gusirq", gus, snd_gus_irq_info_पढ़ो);
पूर्ण

#पूर्ण_अगर
