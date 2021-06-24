<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम IRQ control of EMU10K1 chips
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

irqवापस_t snd_emu10k1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_emu10k1 *emu = dev_id;
	अचिन्हित पूर्णांक status, status2, orig_status, orig_status2;
	पूर्णांक handled = 0;
	पूर्णांक समयout = 0;

	जबतक (((status = inl(emu->port + IPR)) != 0) && (समयout < 1000)) अणु
		समयout++;
		orig_status = status;
		handled = 1;
		अगर ((status & 0xffffffff) == 0xffffffff) अणु
			dev_info(emu->card->dev,
				 "Suspected sound card removal\n");
			अवरोध;
		पूर्ण
		अगर (status & IPR_PCIERROR) अणु
			dev_err(emu->card->dev, "interrupt: PCI error\n");
			snd_emu10k1_पूर्णांकr_disable(emu, INTE_PCIERRORENABLE);
			status &= ~IPR_PCIERROR;
		पूर्ण
		अगर (status & (IPR_VOLINCR|IPR_VOLDECR|IPR_MUTE)) अणु
			अगर (emu->hwvol_पूर्णांकerrupt)
				emu->hwvol_पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_VOLINCRENABLE|INTE_VOLDECRENABLE|INTE_MUTEENABLE);
			status &= ~(IPR_VOLINCR|IPR_VOLDECR|IPR_MUTE);
		पूर्ण
		अगर (status & IPR_CHANNELLOOP) अणु
			पूर्णांक voice;
			पूर्णांक voice_max = status & IPR_CHANNELNUMBERMASK;
			u32 val;
			काष्ठा snd_emu10k1_voice *pvoice = emu->voices;

			val = snd_emu10k1_ptr_पढ़ो(emu, CLIPL, 0);
			क्रम (voice = 0; voice <= voice_max; voice++) अणु
				अगर (voice == 0x20)
					val = snd_emu10k1_ptr_पढ़ो(emu, CLIPH, 0);
				अगर (val & 1) अणु
					अगर (pvoice->use && pvoice->पूर्णांकerrupt != शून्य) अणु
						pvoice->पूर्णांकerrupt(emu, pvoice);
						snd_emu10k1_voice_पूर्णांकr_ack(emu, voice);
					पूर्ण अन्यथा अणु
						snd_emu10k1_voice_पूर्णांकr_disable(emu, voice);
					पूर्ण
				पूर्ण
				val >>= 1;
				pvoice++;
			पूर्ण
			val = snd_emu10k1_ptr_पढ़ो(emu, HLIPL, 0);
			क्रम (voice = 0; voice <= voice_max; voice++) अणु
				अगर (voice == 0x20)
					val = snd_emu10k1_ptr_पढ़ो(emu, HLIPH, 0);
				अगर (val & 1) अणु
					अगर (pvoice->use && pvoice->पूर्णांकerrupt != शून्य) अणु
						pvoice->पूर्णांकerrupt(emu, pvoice);
						snd_emu10k1_voice_half_loop_पूर्णांकr_ack(emu, voice);
					पूर्ण अन्यथा अणु
						snd_emu10k1_voice_half_loop_पूर्णांकr_disable(emu, voice);
					पूर्ण
				पूर्ण
				val >>= 1;
				pvoice++;
			पूर्ण
			status &= ~IPR_CHANNELLOOP;
		पूर्ण
		status &= ~IPR_CHANNELNUMBERMASK;
		अगर (status & (IPR_ADCBUFFULL|IPR_ADCBUFHALFFULL)) अणु
			अगर (emu->capture_पूर्णांकerrupt)
				emu->capture_पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_ADCBUFENABLE);
			status &= ~(IPR_ADCBUFFULL|IPR_ADCBUFHALFFULL);
		पूर्ण
		अगर (status & (IPR_MICBUFFULL|IPR_MICBUFHALFFULL)) अणु
			अगर (emu->capture_mic_पूर्णांकerrupt)
				emu->capture_mic_पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_MICBUFENABLE);
			status &= ~(IPR_MICBUFFULL|IPR_MICBUFHALFFULL);
		पूर्ण
		अगर (status & (IPR_EFXBUFFULL|IPR_EFXBUFHALFFULL)) अणु
			अगर (emu->capture_efx_पूर्णांकerrupt)
				emu->capture_efx_पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_EFXBUFENABLE);
			status &= ~(IPR_EFXBUFFULL|IPR_EFXBUFHALFFULL);
		पूर्ण
		अगर (status & (IPR_MIDITRANSBUFEMPTY|IPR_MIसूचीECVBUFEMPTY)) अणु
			अगर (emu->midi.पूर्णांकerrupt)
				emu->midi.पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_MIDITXENABLE|INTE_MIसूचीXENABLE);
			status &= ~(IPR_MIDITRANSBUFEMPTY|IPR_MIसूचीECVBUFEMPTY);
		पूर्ण
		अगर (status & (IPR_A_MIDITRANSBUFEMPTY2|IPR_A_MIसूचीECVBUFEMPTY2)) अणु
			अगर (emu->midi2.पूर्णांकerrupt)
				emu->midi2.पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_A_MIDITXENABLE2|INTE_A_MIसूचीXENABLE2);
			status &= ~(IPR_A_MIDITRANSBUFEMPTY2|IPR_A_MIसूचीECVBUFEMPTY2);
		पूर्ण
		अगर (status & IPR_INTERVALTIMER) अणु
			अगर (emu->समयr)
				snd_समयr_पूर्णांकerrupt(emu->समयr, emu->समयr->sticks);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_INTERVALTIMERENB);
			status &= ~IPR_INTERVALTIMER;
		पूर्ण
		अगर (status & (IPR_GPSPDIFSTATUSCHANGE|IPR_CDROMSTATUSCHANGE)) अणु
			अगर (emu->spdअगर_पूर्णांकerrupt)
				emu->spdअगर_पूर्णांकerrupt(emu, status);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_GPSPDIFENABLE|INTE_CDSPDIFENABLE);
			status &= ~(IPR_GPSPDIFSTATUSCHANGE|IPR_CDROMSTATUSCHANGE);
		पूर्ण
		अगर (status & IPR_FXDSP) अणु
			अगर (emu->dsp_पूर्णांकerrupt)
				emu->dsp_पूर्णांकerrupt(emu);
			अन्यथा
				snd_emu10k1_पूर्णांकr_disable(emu, INTE_FXDSPENABLE);
			status &= ~IPR_FXDSP;
		पूर्ण
		अगर (status & IPR_P16V) अणु
			जबतक ((status2 = inl(emu->port + IPR2)) != 0) अणु
				u32 mask = INTE2_PLAYBACK_CH_0_LOOP;  /* Full Loop */
				काष्ठा snd_emu10k1_voice *pvoice = &(emu->p16v_voices[0]);
				काष्ठा snd_emu10k1_voice *cvoice = &(emu->p16v_capture_voice);

				/* dev_dbg(emu->card->dev, "status2=0x%x\n", status2); */
				orig_status2 = status2;
				अगर(status2 & mask) अणु
					अगर(pvoice->use) अणु
						snd_pcm_period_elapsed(pvoice->epcm->substream);
					पूर्ण अन्यथा अणु 
						dev_err(emu->card->dev,
							"p16v: status: 0x%08x, mask=0x%08x, pvoice=%p, use=%d\n",
							status2, mask, pvoice,
							pvoice->use);
					पूर्ण
				पूर्ण
				अगर(status2 & 0x110000) अणु
					/* dev_info(emu->card->dev, "capture int found\n"); */
					अगर(cvoice->use) अणु
						/* dev_info(emu->card->dev, "capture period_elapsed\n"); */
						snd_pcm_period_elapsed(cvoice->epcm->substream);
					पूर्ण
				पूर्ण
				outl(orig_status2, emu->port + IPR2); /* ack all */
			पूर्ण
			status &= ~IPR_P16V;
		पूर्ण

		अगर (status) अणु
			अचिन्हित पूर्णांक bits;
			dev_err(emu->card->dev,
				"unhandled interrupt: 0x%08x\n", status);
			//make sure any पूर्णांकerrupts we करोn't handle are disabled:
			bits = INTE_FXDSPENABLE |
				INTE_PCIERRORENABLE |
				INTE_VOLINCRENABLE |
				INTE_VOLDECRENABLE |
				INTE_MUTEENABLE |
				INTE_MICBUFENABLE |
				INTE_ADCBUFENABLE |
				INTE_EFXBUFENABLE |
				INTE_GPSPDIFENABLE |
				INTE_CDSPDIFENABLE |
				INTE_INTERVALTIMERENB |
				INTE_MIDITXENABLE |
				INTE_MIसूचीXENABLE;
			अगर (emu->audigy)
				bits |= INTE_A_MIDITXENABLE2 | INTE_A_MIसूचीXENABLE2;
			snd_emu10k1_पूर्णांकr_disable(emu, bits);
		पूर्ण
		outl(orig_status, emu->port + IPR); /* ack all */
	पूर्ण
	अगर (समयout == 1000)
		dev_info(emu->card->dev, "emu10k1 irq routine failure\n");

	वापस IRQ_RETVAL(handled);
पूर्ण
