<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>

बाह्य पूर्णांक snd_gf1_synth_init(काष्ठा snd_gus_card * gus);
बाह्य व्योम snd_gf1_synth_करोne(काष्ठा snd_gus_card * gus);

/*
 *  ok.. शेष पूर्णांकerrupt handlers...
 */

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_midi_out(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd &= ~0x20);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_midi_in(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd &= ~0x80);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_समयr1(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, gus->gf1.समयr_enabled &= ~4);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_समयr2(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, gus->gf1.समयr_enabled &= ~8);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_wave_and_volume(काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice * voice)
अणु
	snd_gf1_i_ctrl_stop(gus, 0x00);
	snd_gf1_i_ctrl_stop(gus, 0x0d);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_dma_ग_लिखो(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, 0x41, 0x00);
पूर्ण

अटल व्योम snd_gf1_शेष_पूर्णांकerrupt_handler_dma_पढ़ो(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, 0x49, 0x00);
पूर्ण

व्योम snd_gf1_set_शेष_handlers(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक what)
अणु
	अगर (what & SNDRV_GF1_HANDLER_MIDI_OUT)
		gus->gf1.पूर्णांकerrupt_handler_midi_out = snd_gf1_शेष_पूर्णांकerrupt_handler_midi_out;
	अगर (what & SNDRV_GF1_HANDLER_MIDI_IN)
		gus->gf1.पूर्णांकerrupt_handler_midi_in = snd_gf1_शेष_पूर्णांकerrupt_handler_midi_in;
	अगर (what & SNDRV_GF1_HANDLER_TIMER1)
		gus->gf1.पूर्णांकerrupt_handler_समयr1 = snd_gf1_शेष_पूर्णांकerrupt_handler_समयr1;
	अगर (what & SNDRV_GF1_HANDLER_TIMER2)
		gus->gf1.पूर्णांकerrupt_handler_समयr2 = snd_gf1_शेष_पूर्णांकerrupt_handler_समयr2;
	अगर (what & SNDRV_GF1_HANDLER_VOICE) अणु
		काष्ठा snd_gus_voice *voice;
		
		voice = &gus->gf1.voices[what & 0xffff];
		voice->handler_wave =
		voice->handler_volume = snd_gf1_शेष_पूर्णांकerrupt_handler_wave_and_volume;
		voice->handler_effect = शून्य;
		voice->volume_change = शून्य;
	पूर्ण
	अगर (what & SNDRV_GF1_HANDLER_DMA_WRITE)
		gus->gf1.पूर्णांकerrupt_handler_dma_ग_लिखो = snd_gf1_शेष_पूर्णांकerrupt_handler_dma_ग_लिखो;
	अगर (what & SNDRV_GF1_HANDLER_DMA_READ)
		gus->gf1.पूर्णांकerrupt_handler_dma_पढ़ो = snd_gf1_शेष_पूर्णांकerrupt_handler_dma_पढ़ो;
पूर्ण

/*

 */

अटल व्योम snd_gf1_clear_regs(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	inb(GUSP(gus, IRQSTAT));
	snd_gf1_ग_लिखो8(gus, 0x41, 0);	/* DRAM DMA Control Register */
	snd_gf1_ग_लिखो8(gus, 0x45, 0);	/* Timer Control */
	snd_gf1_ग_लिखो8(gus, 0x49, 0);	/* Sampling Control Register */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अटल व्योम snd_gf1_look_regs(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_look8(gus, 0x41);	/* DRAM DMA Control Register */
	snd_gf1_look8(gus, 0x49);	/* Sampling Control Register */
	inb(GUSP(gus, IRQSTAT));
	snd_gf1_पढ़ो8(gus, 0x0f);	/* IRQ Source Register */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

/*
 *  put selected GF1 voices to initial stage...
 */

व्योम snd_gf1_smart_stop_voice(काष्ठा snd_gus_card * gus, अचिन्हित लघु voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_select_voice(gus, voice);
#अगर 0
	prपूर्णांकk(KERN_DEBUG " -%i- smart stop voice - volume = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, SNDRV_GF1_VW_VOLUME));
#पूर्ण_अगर
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

व्योम snd_gf1_stop_voice(काष्ठा snd_gus_card * gus, अचिन्हित लघु voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_select_voice(gus, voice);
#अगर 0
	prपूर्णांकk(KERN_DEBUG " -%i- stop voice - volume = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, SNDRV_GF1_VW_VOLUME));
#पूर्ण_अगर
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
	अगर (gus->gf1.enh_mode)
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ACCUMULATOR, 0);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
#अगर 0
	snd_gf1_lfo_shutकरोwn(gus, voice, ULTRA_LFO_VIBRATO);
	snd_gf1_lfo_shutकरोwn(gus, voice, ULTRA_LFO_TREMOLO);
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_gf1_clear_voices(काष्ठा snd_gus_card * gus, अचिन्हित लघु v_min,
				 अचिन्हित लघु v_max)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक daddr;
	अचिन्हित लघु i, w_16;

	daddr = gus->gf1.शेष_voice_address << 4;
	क्रम (i = v_min; i <= v_max; i++) अणु
#अगर 0
		अगर (gus->gf1.syn_voices)
			gus->gf1.syn_voices[i].flags = ~VFLG_DYNAMIC;
#पूर्ण_अगर
		spin_lock_irqsave(&gus->reg_lock, flags);
		snd_gf1_select_voice(gus, i);
		snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);	/* Voice Control Register = voice stop */
		snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);	/* Volume Ramp Control Register = ramp off */
		अगर (gus->gf1.enh_mode)
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_MODE, gus->gf1.memory ? 0x02 : 0x82);	/* Deactivate voice */
		w_16 = snd_gf1_पढ़ो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL) & 0x04;
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_FREQUENCY, 0x400);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_START, daddr, w_16);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_END, daddr, w_16);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_START, 0);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_END, 0);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_RATE, 0);
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_VOLUME, 0);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_CURRENT, daddr, w_16);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_PAN, 7);
		अगर (gus->gf1.enh_mode) अणु
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ACCUMULATOR, 0);
			snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_EFFECT_VOLUME, 0);
			snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_EFFECT_VOLUME_FINAL, 0);
		पूर्ण
		spin_unlock_irqrestore(&gus->reg_lock, flags);
#अगर 0
		snd_gf1_lfo_shutकरोwn(gus, i, ULTRA_LFO_VIBRATO);
		snd_gf1_lfo_shutकरोwn(gus, i, ULTRA_LFO_TREMOLO);
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम snd_gf1_stop_voices(काष्ठा snd_gus_card * gus, अचिन्हित लघु v_min, अचिन्हित लघु v_max)
अणु
	अचिन्हित दीर्घ flags;
	लघु i, ramp_ok;
	अचिन्हित लघु ramp_end;

	अगर (!in_पूर्णांकerrupt()) अणु	/* this can't be करोne in पूर्णांकerrupt */
		क्रम (i = v_min, ramp_ok = 0; i <= v_max; i++) अणु
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_select_voice(gus, i);
			ramp_end = snd_gf1_पढ़ो16(gus, 9) >> 8;
			अगर (ramp_end > SNDRV_GF1_MIN_OFFSET) अणु
				ramp_ok++;
				snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_RATE, 20);	/* ramp rate */
				snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_START, SNDRV_GF1_MIN_OFFSET);	/* ramp start */
				snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_END, ramp_end);	/* ramp end */
				snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, 0x40);	/* ramp करोwn */
				अगर (gus->gf1.enh_mode) अणु
					snd_gf1_delay(gus);
					snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, 0x40);
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&gus->reg_lock, flags);
		पूर्ण
		msleep_पूर्णांकerruptible(50);
	पूर्ण
	snd_gf1_clear_voices(gus, v_min, v_max);
पूर्ण

अटल व्योम snd_gf1_alloc_voice_use(काष्ठा snd_gus_card * gus, 
				    काष्ठा snd_gus_voice * pvoice,
				    पूर्णांक type, पूर्णांक client, पूर्णांक port)
अणु
	pvoice->use = 1;
	चयन (type) अणु
	हाल SNDRV_GF1_VOICE_TYPE_PCM:
		gus->gf1.pcm_alloc_voices++;
		pvoice->pcm = 1;
		अवरोध;
	हाल SNDRV_GF1_VOICE_TYPE_SYNTH:
		pvoice->synth = 1;
		pvoice->client = client;
		pvoice->port = port;
		अवरोध;
	हाल SNDRV_GF1_VOICE_TYPE_MIDI:
		pvoice->midi = 1;
		pvoice->client = client;
		pvoice->port = port;
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा snd_gus_voice *snd_gf1_alloc_voice(काष्ठा snd_gus_card * gus, पूर्णांक type, पूर्णांक client, पूर्णांक port)
अणु
	काष्ठा snd_gus_voice *pvoice;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&gus->voice_alloc, flags);
	अगर (type == SNDRV_GF1_VOICE_TYPE_PCM) अणु
		अगर (gus->gf1.pcm_alloc_voices >= gus->gf1.pcm_channels) अणु
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			वापस शून्य;
		पूर्ण
	पूर्ण
	क्रम (idx = 0; idx < 32; idx++) अणु
		pvoice = &gus->gf1.voices[idx];
		अगर (!pvoice->use) अणु
			snd_gf1_alloc_voice_use(gus, pvoice, type, client, port);
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			वापस pvoice;
		पूर्ण
	पूर्ण 
	क्रम (idx = 0; idx < 32; idx++) अणु
		pvoice = &gus->gf1.voices[idx];
		अगर (pvoice->midi && !pvoice->client) अणु
			snd_gf1_clear_voices(gus, pvoice->number, pvoice->number);
			snd_gf1_alloc_voice_use(gus, pvoice, type, client, port);
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			वापस pvoice;
		पूर्ण
	पूर्ण 
	spin_unlock_irqrestore(&gus->voice_alloc, flags);
	वापस शून्य;
पूर्ण

व्योम snd_gf1_मुक्त_voice(काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice *voice)
अणु
	अचिन्हित दीर्घ flags;
	व्योम (*निजी_मुक्त)(काष्ठा snd_gus_voice *voice);

	अगर (voice == शून्य || !voice->use)
		वापस;
	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_VOICE | voice->number);
	snd_gf1_clear_voices(gus, voice->number, voice->number);
	spin_lock_irqsave(&gus->voice_alloc, flags);
	निजी_मुक्त = voice->निजी_मुक्त;
	voice->निजी_मुक्त = शून्य;
	voice->निजी_data = शून्य;
	अगर (voice->pcm)
		gus->gf1.pcm_alloc_voices--;
	voice->use = voice->pcm = 0;
	voice->sample_ops = शून्य;
	spin_unlock_irqrestore(&gus->voice_alloc, flags);
	अगर (निजी_मुक्त)
		निजी_मुक्त(voice);
पूर्ण

/*
 *  call this function only by start of driver
 */

पूर्णांक snd_gf1_start(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0);	/* reset GF1 */
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 1);	/* disable IRQ & DAC */
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_JOYSTICK_DAC_LEVEL, gus->joystick_dac);

	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_ALL);
	क्रम (i = 0; i < 32; i++) अणु
		gus->gf1.voices[i].number = i;
		snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_VOICE | i);
	पूर्ण

	snd_gf1_uart_cmd(gus, 0x03);	/* huh.. this cleanup took me some समय... */

	अगर (gus->gf1.enh_mode) अणु	/* enhanced mode !!!! */
		snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_GLOBAL_MODE, snd_gf1_i_look8(gus, SNDRV_GF1_GB_GLOBAL_MODE) | 0x01);
		snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);
	पूर्ण
	snd_gf1_clear_regs(gus);
	snd_gf1_select_active_voices(gus);
	snd_gf1_delay(gus);
	gus->gf1.शेष_voice_address = gus->gf1.memory > 0 ? 0 : 512 - 8;
	/* initialize LFOs & clear LFOs memory */
	अगर (gus->gf1.enh_mode && gus->gf1.memory) अणु
		gus->gf1.hw_lfo = 1;
		gus->gf1.शेष_voice_address += 1024;
	पूर्ण अन्यथा अणु
		gus->gf1.sw_lfo = 1;
	पूर्ण
#अगर 0
	snd_gf1_lfo_init(gus);
#पूर्ण_अगर
	अगर (gus->gf1.memory > 0)
		क्रम (i = 0; i < 4; i++)
			snd_gf1_poke(gus, gus->gf1.शेष_voice_address + i, 0);
	snd_gf1_clear_regs(gus);
	snd_gf1_clear_voices(gus, 0, 31);
	snd_gf1_look_regs(gus);
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 7);	/* Reset Register = IRQ enable, DAC enable */
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 7);	/* Reset Register = IRQ enable, DAC enable */
	अगर (gus->gf1.enh_mode) अणु	/* enhanced mode !!!! */
		snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_GLOBAL_MODE, snd_gf1_i_look8(gus, SNDRV_GF1_GB_GLOBAL_MODE) | 0x01);
		snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);
	पूर्ण
	जबतक ((snd_gf1_i_पढ़ो8(gus, SNDRV_GF1_GB_VOICES_IRQ) & 0xc0) != 0xc0);

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(gus->gf1.active_voice = 0, GUSP(gus, GF1PAGE));
	outb(gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
	spin_unlock_irqrestore(&gus->reg_lock, flags);

	snd_gf1_समयrs_init(gus);
	snd_gf1_look_regs(gus);
	snd_gf1_mem_init(gus);
	snd_gf1_mem_proc_init(gus);
#अगर_घोषित CONFIG_SND_DEBUG
	snd_gus_irq_profile_init(gus);
#पूर्ण_अगर

#अगर 0
	अगर (gus->pnp_flag) अणु
		अगर (gus->chip.playback_fअगरo_size > 0)
			snd_gf1_i_ग_लिखो16(gus, SNDRV_GF1_GW_FIFO_RECORD_BASE_ADDR, gus->chip.playback_fअगरo_block->ptr >> 8);
		अगर (gus->chip.record_fअगरo_size > 0)
			snd_gf1_i_ग_लिखो16(gus, SNDRV_GF1_GW_FIFO_PLAY_BASE_ADDR, gus->chip.record_fअगरo_block->ptr >> 8);
		snd_gf1_i_ग_लिखो16(gus, SNDRV_GF1_GW_FIFO_SIZE, gus->chip.पूर्णांकerwave_fअगरo_reg);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 *  call this function only by shutकरोwn of driver
 */

पूर्णांक snd_gf1_stop(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, 0); /* stop all समयrs */
	snd_gf1_stop_voices(gus, 0, 31);		/* stop all voices */
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 1);	/* disable IRQ & DAC */
	snd_gf1_समयrs_करोne(gus);
	snd_gf1_mem_करोne(gus);
#अगर 0
	snd_gf1_lfo_करोne(gus);
#पूर्ण_अगर
	वापस 0;
पूर्ण
