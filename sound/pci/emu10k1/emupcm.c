<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम control of EMU10K1 chips / PCM routines
 *  Multichannel PCM support Copyright (c) Lee Revell <rlrevell@joe-job.com>
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

अटल व्योम snd_emu10k1_pcm_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu,
				      काष्ठा snd_emu10k1_voice *voice)
अणु
	काष्ठा snd_emu10k1_pcm *epcm;

	अगर ((epcm = voice->epcm) == शून्य)
		वापस;
	अगर (epcm->substream == शून्य)
		वापस;
#अगर 0
	dev_dbg(emu->card->dev,
		"IRQ: position = 0x%x, period = 0x%x, size = 0x%x\n",
			epcm->substream->runसमय->hw->poपूर्णांकer(emu, epcm->substream),
			snd_pcm_lib_period_bytes(epcm->substream),
			snd_pcm_lib_buffer_bytes(epcm->substream));
#पूर्ण_अगर
	snd_pcm_period_elapsed(epcm->substream);
पूर्ण

अटल व्योम snd_emu10k1_pcm_ac97adc_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu,
					      अचिन्हित पूर्णांक status)
अणु
#अगर 0
	अगर (status & IPR_ADCBUFHALFFULL) अणु
		अगर (emu->pcm_capture_substream->runसमय->mode == SNDRV_PCM_MODE_FRAME)
			वापस;
	पूर्ण
#पूर्ण_अगर
	snd_pcm_period_elapsed(emu->pcm_capture_substream);
पूर्ण

अटल व्योम snd_emu10k1_pcm_ac97mic_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu,
					      अचिन्हित पूर्णांक status)
अणु
#अगर 0
	अगर (status & IPR_MICBUFHALFFULL) अणु
		अगर (emu->pcm_capture_mic_substream->runसमय->mode == SNDRV_PCM_MODE_FRAME)
			वापस;
	पूर्ण
#पूर्ण_अगर
	snd_pcm_period_elapsed(emu->pcm_capture_mic_substream);
पूर्ण

अटल व्योम snd_emu10k1_pcm_efx_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu,
					  अचिन्हित पूर्णांक status)
अणु
#अगर 0
	अगर (status & IPR_EFXBUFHALFFULL) अणु
		अगर (emu->pcm_capture_efx_substream->runसमय->mode == SNDRV_PCM_MODE_FRAME)
			वापस;
	पूर्ण
#पूर्ण_अगर
	snd_pcm_period_elapsed(emu->pcm_capture_efx_substream);
पूर्ण	 

अटल snd_pcm_uframes_t snd_emu10k1_efx_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक ptr;

	अगर (!epcm->running)
		वापस 0;
	ptr = snd_emu10k1_ptr_पढ़ो(emu, CCCA, epcm->voices[0]->number) & 0x00ffffff;
	ptr += runसमय->buffer_size;
	ptr -= epcm->ccca_start_addr;
	ptr %= runसमय->buffer_size;

	वापस ptr;
पूर्ण

अटल पूर्णांक snd_emu10k1_pcm_channel_alloc(काष्ठा snd_emu10k1_pcm * epcm, पूर्णांक voices)
अणु
	पूर्णांक err, i;

	अगर (epcm->voices[1] != शून्य && voices < 2) अणु
		snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[1]);
		epcm->voices[1] = शून्य;
	पूर्ण
	क्रम (i = 0; i < voices; i++) अणु
		अगर (epcm->voices[i] == शून्य)
			अवरोध;
	पूर्ण
	अगर (i == voices)
		वापस 0; /* alपढ़ोy allocated */

	क्रम (i = 0; i < ARRAY_SIZE(epcm->voices); i++) अणु
		अगर (epcm->voices[i]) अणु
			snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[i]);
			epcm->voices[i] = शून्य;
		पूर्ण
	पूर्ण
	err = snd_emu10k1_voice_alloc(epcm->emu,
				      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
				      voices,
				      &epcm->voices[0]);
	
	अगर (err < 0)
		वापस err;
	epcm->voices[0]->epcm = epcm;
	अगर (voices > 1) अणु
		क्रम (i = 1; i < voices; i++) अणु
			epcm->voices[i] = &epcm->emu->voices[epcm->voices[0]->number + i];
			epcm->voices[i]->epcm = epcm;
		पूर्ण
	पूर्ण
	अगर (epcm->extra == शून्य) अणु
		err = snd_emu10k1_voice_alloc(epcm->emu,
					      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
					      1,
					      &epcm->extra);
		अगर (err < 0) अणु
			/*
			dev_dbg(emu->card->dev, "pcm_channel_alloc: "
			       "failed extra: voices=%d, frame=%d\n",
			       voices, frame);
			*/
			क्रम (i = 0; i < voices; i++) अणु
				snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[i]);
				epcm->voices[i] = शून्य;
			पूर्ण
			वापस err;
		पूर्ण
		epcm->extra->epcm = epcm;
		epcm->extra->पूर्णांकerrupt = snd_emu10k1_pcm_पूर्णांकerrupt;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक capture_period_sizes[31] = अणु
	384,	448,	512,	640,
	384*2,	448*2,	512*2,	640*2,
	384*4,	448*4,	512*4,	640*4,
	384*8,	448*8,	512*8,	640*8,
	384*16,	448*16,	512*16,	640*16,
	384*32,	448*32,	512*32,	640*32,
	384*64,	448*64,	512*64,	640*64,
	384*128,448*128,512*128
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_capture_period_sizes = अणु
	.count = 31,
	.list = capture_period_sizes,
	.mask = 0
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक capture_rates[8] = अणु
	8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_capture_rates = अणु
	.count = 8,
	.list = capture_rates,
	.mask = 0
पूर्ण;

अटल अचिन्हित पूर्णांक snd_emu10k1_capture_rate_reg(अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:	वापस ADCCR_SAMPLERATE_8;
	हाल 11025:	वापस ADCCR_SAMPLERATE_11;
	हाल 16000:	वापस ADCCR_SAMPLERATE_16;
	हाल 22050:	वापस ADCCR_SAMPLERATE_22;
	हाल 24000:	वापस ADCCR_SAMPLERATE_24;
	हाल 32000:	वापस ADCCR_SAMPLERATE_32;
	हाल 44100:	वापस ADCCR_SAMPLERATE_44;
	हाल 48000:	वापस ADCCR_SAMPLERATE_48;
	शेष:
			snd_BUG();
			वापस ADCCR_SAMPLERATE_8;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक snd_emu10k1_audigy_capture_rate_reg(अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:	वापस A_ADCCR_SAMPLERATE_8;
	हाल 11025:	वापस A_ADCCR_SAMPLERATE_11;
	हाल 12000:	वापस A_ADCCR_SAMPLERATE_12; /* really supported? */
	हाल 16000:	वापस ADCCR_SAMPLERATE_16;
	हाल 22050:	वापस ADCCR_SAMPLERATE_22;
	हाल 24000:	वापस ADCCR_SAMPLERATE_24;
	हाल 32000:	वापस ADCCR_SAMPLERATE_32;
	हाल 44100:	वापस ADCCR_SAMPLERATE_44;
	हाल 48000:	वापस ADCCR_SAMPLERATE_48;
	शेष:
			snd_BUG();
			वापस A_ADCCR_SAMPLERATE_8;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक emu10k1_calc_pitch_target(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक pitch_target;

	pitch_target = (rate << 8) / 375;
	pitch_target = (pitch_target >> 1) + (pitch_target & 1);
	वापस pitch_target;
पूर्ण

#घोषणा PITCH_48000 0x00004000
#घोषणा PITCH_96000 0x00008000
#घोषणा PITCH_85000 0x00007155
#घोषणा PITCH_80726 0x00006ba2
#घोषणा PITCH_67882 0x00005a82
#घोषणा PITCH_57081 0x00004c1c

अटल अचिन्हित पूर्णांक emu10k1_select_पूर्णांकerprom(अचिन्हित पूर्णांक pitch_target)
अणु
	अगर (pitch_target == PITCH_48000)
		वापस CCCA_INTERPROM_0;
	अन्यथा अगर (pitch_target < PITCH_48000)
		वापस CCCA_INTERPROM_1;
	अन्यथा अगर (pitch_target >= PITCH_96000)
		वापस CCCA_INTERPROM_0;
	अन्यथा अगर (pitch_target >= PITCH_85000)
		वापस CCCA_INTERPROM_6;
	अन्यथा अगर (pitch_target >= PITCH_80726)
		वापस CCCA_INTERPROM_5;
	अन्यथा अगर (pitch_target >= PITCH_67882)
		वापस CCCA_INTERPROM_4;
	अन्यथा अगर (pitch_target >= PITCH_57081)
		वापस CCCA_INTERPROM_3;
	अन्यथा  
		वापस CCCA_INTERPROM_2;
पूर्ण

/*
 * calculate cache invalidate size 
 *
 * stereo: channel is stereo
 * w_16: using 16bit samples
 *
 * वापसs: cache invalidate size in samples
 */
अटल अंतरभूत पूर्णांक emu10k1_ccis(पूर्णांक stereo, पूर्णांक w_16)
अणु
	अगर (w_16) अणु
		वापस stereo ? 24 : 26;
	पूर्ण अन्यथा अणु
		वापस stereo ? 24*2 : 26*2;
	पूर्ण
पूर्ण

अटल व्योम snd_emu10k1_pcm_init_voice(काष्ठा snd_emu10k1 *emu,
				       पूर्णांक master, पूर्णांक extra,
				       काष्ठा snd_emu10k1_voice *evoice,
				       अचिन्हित पूर्णांक start_addr,
				       अचिन्हित पूर्णांक end_addr,
				       काष्ठा snd_emu10k1_pcm_mixer *mix)
अणु
	काष्ठा snd_pcm_substream *substream = evoice->epcm->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक silent_page, पंचांगp;
	पूर्णांक voice, stereo, w_16;
	अचिन्हित अक्षर send_amount[8];
	अचिन्हित अक्षर send_routing[8];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pitch_target;
	अचिन्हित पूर्णांक ccis;

	voice = evoice->number;
	stereo = runसमय->channels == 2;
	w_16 = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16;

	अगर (!extra && stereo) अणु
		start_addr >>= 1;
		end_addr >>= 1;
	पूर्ण
	अगर (w_16) अणु
		start_addr >>= 1;
		end_addr >>= 1;
	पूर्ण

	spin_lock_irqsave(&emu->reg_lock, flags);

	/* volume parameters */
	अगर (extra) अणु
		स_रखो(send_routing, 0, माप(send_routing));
		send_routing[0] = 0;
		send_routing[1] = 1;
		send_routing[2] = 2;
		send_routing[3] = 3;
		स_रखो(send_amount, 0, माप(send_amount));
	पूर्ण अन्यथा अणु
		/* mono, left, right (master voice = left) */
		पंचांगp = stereo ? (master ? 1 : 2) : 0;
		स_नकल(send_routing, &mix->send_routing[पंचांगp][0], 8);
		स_नकल(send_amount, &mix->send_volume[पंचांगp][0], 8);
	पूर्ण

	ccis = emu10k1_ccis(stereo, w_16);
	
	अगर (master) अणु
		evoice->epcm->ccca_start_addr = start_addr + ccis;
		अगर (extra) अणु
			start_addr += ccis;
			end_addr += ccis + emu->delay_pcm_irq;
		पूर्ण
		अगर (stereo && !extra) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, CPF, voice, CPF_STEREO_MASK);
			snd_emu10k1_ptr_ग_लिखो(emu, CPF, (voice + 1), CPF_STEREO_MASK);
		पूर्ण अन्यथा अणु
			snd_emu10k1_ptr_ग_लिखो(emu, CPF, voice, 0);
		पूर्ण
	पूर्ण

	/* setup routing */
	अगर (emu->audigy) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT1, voice,
				      snd_emu10k1_compose_audigy_fxrt1(send_routing));
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT2, voice,
				      snd_emu10k1_compose_audigy_fxrt2(send_routing));
		snd_emu10k1_ptr_ग_लिखो(emu, A_SENDAMOUNTS, voice,
				      ((अचिन्हित पूर्णांक)send_amount[4] << 24) |
				      ((अचिन्हित पूर्णांक)send_amount[5] << 16) |
				      ((अचिन्हित पूर्णांक)send_amount[6] << 8) |
				      (अचिन्हित पूर्णांक)send_amount[7]);
	पूर्ण अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, FXRT, voice,
				      snd_emu10k1_compose_send_routing(send_routing));
	/* Stop CA */
	/* Assumption that PT is alपढ़ोy 0 so no harm overwriting */
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX, voice, (send_amount[0] << 8) | send_amount[1]);
	snd_emu10k1_ptr_ग_लिखो(emu, DSL, voice, end_addr | (send_amount[3] << 24));
	snd_emu10k1_ptr_ग_लिखो(emu, PSST, voice,
			(start_addr + (extra ? emu->delay_pcm_irq : 0)) |
			(send_amount[2] << 24));
	अगर (emu->card_capabilities->emu_model)
		pitch_target = PITCH_48000; /* Disable पूर्णांकerpolators on emu1010 card */
	अन्यथा 
		pitch_target = emu10k1_calc_pitch_target(runसमय->rate);
	अगर (extra)
		snd_emu10k1_ptr_ग_लिखो(emu, CCCA, voice, start_addr |
			      emu10k1_select_पूर्णांकerprom(pitch_target) |
			      (w_16 ? 0 : CCCA_8BITSELECT));
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, CCCA, voice, (start_addr + ccis) |
			      emu10k1_select_पूर्णांकerprom(pitch_target) |
			      (w_16 ? 0 : CCCA_8BITSELECT));
	/* Clear filter delay memory */
	snd_emu10k1_ptr_ग_लिखो(emu, Z1, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, Z2, voice, 0);
	/* invalidate maps */
	silent_page = ((अचिन्हित पूर्णांक)emu->silent_page.addr << emu->address_mode) | (emu->address_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);
	snd_emu10k1_ptr_ग_लिखो(emu, MAPA, voice, silent_page);
	snd_emu10k1_ptr_ग_लिखो(emu, MAPB, voice, silent_page);
	/* modulation envelope */
	snd_emu10k1_ptr_ग_लिखो(emu, CVCF, voice, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, VTFT, voice, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, ATKHLDM, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, DCYSUSM, voice, 0x007f);
	snd_emu10k1_ptr_ग_लिखो(emu, LFOVAL1, voice, 0x8000);
	snd_emu10k1_ptr_ग_लिखो(emu, LFOVAL2, voice, 0x8000);
	snd_emu10k1_ptr_ग_लिखो(emu, FMMOD, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, TREMFRQ, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FM2FRQ2, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ENVVAL, voice, 0x8000);
	/* volume envelope */
	snd_emu10k1_ptr_ग_लिखो(emu, ATKHLDV, voice, 0x7f7f);
	snd_emu10k1_ptr_ग_लिखो(emu, ENVVOL, voice, 0x0000);
	/* filter envelope */
	snd_emu10k1_ptr_ग_लिखो(emu, PEFE_FILTERAMOUNT, voice, 0x7f);
	/* pitch envelope */
	snd_emu10k1_ptr_ग_लिखो(emu, PEFE_PITCHAMOUNT, voice, 0);

	spin_unlock_irqrestore(&emu->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	अगर ((err = snd_emu10k1_pcm_channel_alloc(epcm, params_channels(hw_params))) < 0)
		वापस err;

	alloc_size = params_buffer_bytes(hw_params);
	अगर (emu->iommu_workaround)
		alloc_size += EMUPAGESIZE;
	err = snd_pcm_lib_दो_स्मृति_pages(substream, alloc_size);
	अगर (err < 0)
		वापस err;
	अगर (emu->iommu_workaround && runसमय->dma_bytes >= EMUPAGESIZE)
		runसमय->dma_bytes -= EMUPAGESIZE;
	अगर (err > 0) अणु	/* change */
		पूर्णांक mapped;
		अगर (epcm->memblk != शून्य)
			snd_emu10k1_मुक्त_pages(emu, epcm->memblk);
		epcm->memblk = snd_emu10k1_alloc_pages(emu, substream);
		epcm->start_addr = 0;
		अगर (! epcm->memblk)
			वापस -ENOMEM;
		mapped = ((काष्ठा snd_emu10k1_memblk *)epcm->memblk)->mapped_page;
		अगर (mapped < 0)
			वापस -ENOMEM;
		epcm->start_addr = mapped << PAGE_SHIFT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm;

	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	epcm = runसमय->निजी_data;
	अगर (epcm->extra) अणु
		snd_emu10k1_voice_मुक्त(epcm->emu, epcm->extra);
		epcm->extra = शून्य;
	पूर्ण
	अगर (epcm->voices[1]) अणु
		snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[1]);
		epcm->voices[1] = शून्य;
	पूर्ण
	अगर (epcm->voices[0]) अणु
		snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[0]);
		epcm->voices[0] = शून्य;
	पूर्ण
	अगर (epcm->memblk) अणु
		snd_emu10k1_मुक्त_pages(emu, epcm->memblk);
		epcm->memblk = शून्य;
		epcm->start_addr = 0;
	पूर्ण
	snd_pcm_lib_मुक्त_pages(substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm;
	पूर्णांक i;

	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	epcm = runसमय->निजी_data;
	अगर (epcm->extra) अणु
		snd_emu10k1_voice_मुक्त(epcm->emu, epcm->extra);
		epcm->extra = शून्य;
	पूर्ण
	क्रम (i = 0; i < NUM_EFX_PLAYBACK; i++) अणु
		अगर (epcm->voices[i]) अणु
			snd_emu10k1_voice_मुक्त(epcm->emu, epcm->voices[i]);
			epcm->voices[i] = शून्य;
		पूर्ण
	पूर्ण
	अगर (epcm->memblk) अणु
		snd_emu10k1_मुक्त_pages(emu, epcm->memblk);
		epcm->memblk = शून्य;
		epcm->start_addr = 0;
	पूर्ण
	snd_pcm_lib_मुक्त_pages(substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक start_addr, end_addr;

	start_addr = epcm->start_addr;
	end_addr = snd_pcm_lib_period_bytes(substream);
	अगर (runसमय->channels == 2) अणु
		start_addr >>= 1;
		end_addr >>= 1;
	पूर्ण
	end_addr += start_addr;
	snd_emu10k1_pcm_init_voice(emu, 1, 1, epcm->extra,
				   start_addr, end_addr, शून्य);
	start_addr = epcm->start_addr;
	end_addr = epcm->start_addr + snd_pcm_lib_buffer_bytes(substream);
	snd_emu10k1_pcm_init_voice(emu, 1, 0, epcm->voices[0],
				   start_addr, end_addr,
				   &emu->pcm_mixer[substream->number]);
	अगर (epcm->voices[1])
		snd_emu10k1_pcm_init_voice(emu, 0, 0, epcm->voices[1],
					   start_addr, end_addr,
					   &emu->pcm_mixer[substream->number]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक start_addr, end_addr;
	अचिन्हित पूर्णांक channel_size;
	पूर्णांक i;

	start_addr = epcm->start_addr;
	end_addr = epcm->start_addr + snd_pcm_lib_buffer_bytes(substream);

	/*
	 * the kX driver leaves some space between voices
	 */
	channel_size = ( end_addr - start_addr ) / NUM_EFX_PLAYBACK;

	snd_emu10k1_pcm_init_voice(emu, 1, 1, epcm->extra,
				   start_addr, start_addr + (channel_size / 2), शून्य);

	/* only dअगरference with the master voice is we use it क्रम the poपूर्णांकer */
	snd_emu10k1_pcm_init_voice(emu, 1, 0, epcm->voices[0],
				   start_addr, start_addr + channel_size,
				   &emu->efx_pcm_mixer[0]);

	start_addr += channel_size;
	क्रम (i = 1; i < NUM_EFX_PLAYBACK; i++) अणु
		snd_emu10k1_pcm_init_voice(emu, 0, 0, epcm->voices[i],
					   start_addr, start_addr + channel_size,
					   &emu->efx_pcm_mixer[i]);
		start_addr += channel_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1_efx_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		NUM_EFX_PLAYBACK,
	.channels_max =		NUM_EFX_PLAYBACK,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(64*1024),
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_emu10k1_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	पूर्णांक idx;

	/* zeroing the buffer size will stop capture */
	snd_emu10k1_ptr_ग_लिखो(emu, epcm->capture_bs_reg, 0, 0);
	चयन (epcm->type) अणु
	हाल CAPTURE_AC97ADC:
		snd_emu10k1_ptr_ग_लिखो(emu, ADCCR, 0, 0);
		अवरोध;
	हाल CAPTURE_EFX:
		अगर (emu->audigy) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC1, 0, 0);
			snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC2, 0, 0);
		पूर्ण अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, FXWC, 0, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण	
	snd_emu10k1_ptr_ग_लिखो(emu, epcm->capture_ba_reg, 0, runसमय->dma_addr);
	epcm->capture_bufsize = snd_pcm_lib_buffer_bytes(substream);
	epcm->capture_bs_val = 0;
	क्रम (idx = 0; idx < 31; idx++) अणु
		अगर (capture_period_sizes[idx] == epcm->capture_bufsize) अणु
			epcm->capture_bs_val = idx + 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (epcm->capture_bs_val == 0) अणु
		snd_BUG();
		epcm->capture_bs_val++;
	पूर्ण
	अगर (epcm->type == CAPTURE_AC97ADC) अणु
		epcm->capture_cr_val = emu->audigy ? A_ADCCR_LCHANENABLE : ADCCR_LCHANENABLE;
		अगर (runसमय->channels > 1)
			epcm->capture_cr_val |= emu->audigy ? A_ADCCR_RCHANENABLE : ADCCR_RCHANENABLE;
		epcm->capture_cr_val |= emu->audigy ?
			snd_emu10k1_audigy_capture_rate_reg(runसमय->rate) :
			snd_emu10k1_capture_rate_reg(runसमय->rate);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_emu10k1_playback_invalidate_cache(काष्ठा snd_emu10k1 *emu, पूर्णांक extra, काष्ठा snd_emu10k1_voice *evoice)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक voice, stereo, i, ccis, cra = 64, cs, sample;

	अगर (evoice == शून्य)
		वापस;
	runसमय = evoice->epcm->substream->runसमय;
	voice = evoice->number;
	stereo = (!extra && runसमय->channels == 2);
	sample = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0 : 0x80808080;
	ccis = emu10k1_ccis(stereo, sample == 0);
	/* set cs to 2 * number of cache रेजिस्टरs beside the invalidated */
	cs = (sample == 0) ? (32-ccis) : (64-ccis+1) >> 1;
	अगर (cs > 16) cs = 16;
	क्रम (i = 0; i < cs; i++) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, CD0 + i, voice, sample);
		अगर (stereo) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, CD0 + i, voice + 1, sample);
		पूर्ण
	पूर्ण
	/* reset cache */
	snd_emu10k1_ptr_ग_लिखो(emu, CCR_CACHEINVALIDSIZE, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CCR_READADDRESS, voice, cra);
	अगर (stereo) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, CCR_CACHEINVALIDSIZE, voice + 1, 0);
		snd_emu10k1_ptr_ग_लिखो(emu, CCR_READADDRESS, voice + 1, cra);
	पूर्ण
	/* fill cache */
	snd_emu10k1_ptr_ग_लिखो(emu, CCR_CACHEINVALIDSIZE, voice, ccis);
	अगर (stereo) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, CCR_CACHEINVALIDSIZE, voice+1, ccis);
	पूर्ण
पूर्ण

अटल व्योम snd_emu10k1_playback_prepare_voice(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_voice *evoice,
					       पूर्णांक master, पूर्णांक extra,
					       काष्ठा snd_emu10k1_pcm_mixer *mix)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक attn, vattn;
	अचिन्हित पूर्णांक voice, पंचांगp;

	अगर (evoice == शून्य)	/* skip second voice क्रम mono */
		वापस;
	substream = evoice->epcm->substream;
	runसमय = substream->runसमय;
	voice = evoice->number;

	attn = extra ? 0 : 0x00ff;
	पंचांगp = runसमय->channels == 2 ? (master ? 1 : 2) : 0;
	vattn = mix != शून्य ? (mix->attn[पंचांगp] << 16) : 0;
	snd_emu10k1_ptr_ग_लिखो(emu, IFATN, voice, attn);
	snd_emu10k1_ptr_ग_लिखो(emu, VTFT, voice, vattn | 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, CVCF, voice, vattn | 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, DCYSUSV, voice, 0x7f7f);
	snd_emu10k1_voice_clear_loop_stop(emu, voice);
पूर्ण	

अटल व्योम snd_emu10k1_playback_trigger_voice(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_voice *evoice, पूर्णांक master, पूर्णांक extra)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक voice, pitch, pitch_target;

	अगर (evoice == शून्य)	/* skip second voice क्रम mono */
		वापस;
	substream = evoice->epcm->substream;
	runसमय = substream->runसमय;
	voice = evoice->number;

	pitch = snd_emu10k1_rate_to_pitch(runसमय->rate) >> 8;
	अगर (emu->card_capabilities->emu_model)
		pitch_target = PITCH_48000; /* Disable पूर्णांकerpolators on emu1010 card */
	अन्यथा 
		pitch_target = emu10k1_calc_pitch_target(runसमय->rate);
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX_PITCHTARGET, voice, pitch_target);
	अगर (master || evoice->epcm->type == PLAYBACK_EFX)
		snd_emu10k1_ptr_ग_लिखो(emu, CPF_CURRENTPITCH, voice, pitch_target);
	snd_emu10k1_ptr_ग_लिखो(emu, IP, voice, pitch);
	अगर (extra)
		snd_emu10k1_voice_पूर्णांकr_enable(emu, voice);
पूर्ण

अटल व्योम snd_emu10k1_playback_stop_voice(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_voice *evoice)
अणु
	अचिन्हित पूर्णांक voice;

	अगर (evoice == शून्य)
		वापस;
	voice = evoice->number;
	snd_emu10k1_voice_पूर्णांकr_disable(emu, voice);
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX_PITCHTARGET, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CPF_CURRENTPITCH, voice, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, IFATN, voice, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, VTFT, voice, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, CVCF, voice, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, IP, voice, 0);
पूर्ण

अटल अंतरभूत व्योम snd_emu10k1_playback_mangle_extra(काष्ठा snd_emu10k1 *emu,
		काष्ठा snd_emu10k1_pcm *epcm,
		काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अचिन्हित पूर्णांक ptr, period_pos;

	/* try to sychronize the current position क्रम the पूर्णांकerrupt
	   source voice */
	period_pos = runसमय->status->hw_ptr - runसमय->hw_ptr_पूर्णांकerrupt;
	period_pos %= runसमय->period_size;
	ptr = snd_emu10k1_ptr_पढ़ो(emu, CCCA, epcm->extra->number);
	ptr &= ~0x00ffffff;
	ptr |= epcm->ccca_start_addr + period_pos;
	snd_emu10k1_ptr_ग_लिखो(emu, CCCA, epcm->extra->number, ptr);
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_trigger(काष्ठा snd_pcm_substream *substream,
				        पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	काष्ठा snd_emu10k1_pcm_mixer *mix;
	पूर्णांक result = 0;

	/*
	dev_dbg(emu->card->dev,
		"trigger - emu10k1 = 0x%x, cmd = %i, pointer = %i\n",
	       (पूर्णांक)emu, cmd, substream->ops->poपूर्णांकer(substream))
	*/
	spin_lock(&emu->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_emu10k1_playback_invalidate_cache(emu, 1, epcm->extra);	/* करो we need this? */
		snd_emu10k1_playback_invalidate_cache(emu, 0, epcm->voices[0]);
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_RELEASE)
			snd_emu10k1_playback_mangle_extra(emu, epcm, substream, runसमय);
		mix = &emu->pcm_mixer[substream->number];
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[0], 1, 0, mix);
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[1], 0, 0, mix);
		snd_emu10k1_playback_prepare_voice(emu, epcm->extra, 1, 1, शून्य);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[0], 1, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[1], 0, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->extra, 1, 1);
		epcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		epcm->running = 0;
		snd_emu10k1_playback_stop_voice(emu, epcm->voices[0]);
		snd_emu10k1_playback_stop_voice(emu, epcm->voices[1]);
		snd_emu10k1_playback_stop_voice(emu, epcm->extra);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&emu->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	पूर्णांक result = 0;

	spin_lock(&emu->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* hmm this should cause full and half full पूर्णांकerrupt to be उठाओd? */
		outl(epcm->capture_ipr, emu->port + IPR);
		snd_emu10k1_पूर्णांकr_enable(emu, epcm->capture_पूर्णांकe);
		/*
		dev_dbg(emu->card->dev, "adccr = 0x%x, adcbs = 0x%x\n",
		       epcm->adccr, epcm->adcbs);
		*/
		चयन (epcm->type) अणु
		हाल CAPTURE_AC97ADC:
			snd_emu10k1_ptr_ग_लिखो(emu, ADCCR, 0, epcm->capture_cr_val);
			अवरोध;
		हाल CAPTURE_EFX:
			अगर (emu->audigy) अणु
				snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC1, 0, epcm->capture_cr_val);
				snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC2, 0, epcm->capture_cr_val2);
				dev_dbg(emu->card->dev,
					"cr_val=0x%x, cr_val2=0x%x\n",
					epcm->capture_cr_val,
					epcm->capture_cr_val2);
			पूर्ण अन्यथा
				snd_emu10k1_ptr_ग_लिखो(emu, FXWC, 0, epcm->capture_cr_val);
			अवरोध;
		शेष:	
			अवरोध;
		पूर्ण
		snd_emu10k1_ptr_ग_लिखो(emu, epcm->capture_bs_reg, 0, epcm->capture_bs_val);
		epcm->running = 1;
		epcm->first_ptr = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		epcm->running = 0;
		snd_emu10k1_पूर्णांकr_disable(emu, epcm->capture_पूर्णांकe);
		outl(epcm->capture_ipr, emu->port + IPR);
		snd_emu10k1_ptr_ग_लिखो(emu, epcm->capture_bs_reg, 0, 0);
		चयन (epcm->type) अणु
		हाल CAPTURE_AC97ADC:
			snd_emu10k1_ptr_ग_लिखो(emu, ADCCR, 0, 0);
			अवरोध;
		हाल CAPTURE_EFX:
			अगर (emu->audigy) अणु
				snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC1, 0, 0);
				snd_emu10k1_ptr_ग_लिखो(emu, A_FXWC2, 0, 0);
			पूर्ण अन्यथा
				snd_emu10k1_ptr_ग_लिखो(emu, FXWC, 0, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		result = -EINVAL;
	पूर्ण
	spin_unlock(&emu->reg_lock);
	वापस result;
पूर्ण

अटल snd_pcm_uframes_t snd_emu10k1_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक ptr;

	अगर (!epcm->running)
		वापस 0;
	ptr = snd_emu10k1_ptr_पढ़ो(emu, CCCA, epcm->voices[0]->number) & 0x00ffffff;
#अगर 0	/* Perex's code */
	ptr += runसमय->buffer_size;
	ptr -= epcm->ccca_start_addr;
	ptr %= runसमय->buffer_size;
#अन्यथा	/* EMU10K1 Open Source code from Creative */
	अगर (ptr < epcm->ccca_start_addr)
		ptr += runसमय->buffer_size - epcm->ccca_start_addr;
	अन्यथा अणु
		ptr -= epcm->ccca_start_addr;
		अगर (ptr >= runसमय->buffer_size)
			ptr -= runसमय->buffer_size;
	पूर्ण
#पूर्ण_अगर
	/*
	dev_dbg(emu->card->dev,
	       "ptr = 0x%lx, buffer_size = 0x%lx, period_size = 0x%lx\n",
	       (दीर्घ)ptr, (दीर्घ)runसमय->buffer_size,
	       (दीर्घ)runसमय->period_size);
	*/
	वापस ptr;
पूर्ण


अटल पूर्णांक snd_emu10k1_efx_playback_trigger(काष्ठा snd_pcm_substream *substream,
				        पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	पूर्णांक i;
	पूर्णांक result = 0;

	spin_lock(&emu->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* prepare voices */
		क्रम (i = 0; i < NUM_EFX_PLAYBACK; i++) अणु	
			snd_emu10k1_playback_invalidate_cache(emu, 0, epcm->voices[i]);
		पूर्ण
		snd_emu10k1_playback_invalidate_cache(emu, 1, epcm->extra);
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		snd_emu10k1_playback_prepare_voice(emu, epcm->extra, 1, 1, शून्य);
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[0], 0, 0,
						   &emu->efx_pcm_mixer[0]);
		क्रम (i = 1; i < NUM_EFX_PLAYBACK; i++)
			snd_emu10k1_playback_prepare_voice(emu, epcm->voices[i], 0, 0,
							   &emu->efx_pcm_mixer[i]);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[0], 0, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->extra, 1, 1);
		क्रम (i = 1; i < NUM_EFX_PLAYBACK; i++)
			snd_emu10k1_playback_trigger_voice(emu, epcm->voices[i], 0, 0);
		epcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		epcm->running = 0;
		क्रम (i = 0; i < NUM_EFX_PLAYBACK; i++) अणु	
			snd_emu10k1_playback_stop_voice(emu, epcm->voices[i]);
		पूर्ण
		snd_emu10k1_playback_stop_voice(emu, epcm->extra);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&emu->reg_lock);
	वापस result;
पूर्ण


अटल snd_pcm_uframes_t snd_emu10k1_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक ptr;

	अगर (!epcm->running)
		वापस 0;
	अगर (epcm->first_ptr) अणु
		udelay(50);	/* hack, it takes aजबतक until capture is started */
		epcm->first_ptr = 0;
	पूर्ण
	ptr = snd_emu10k1_ptr_पढ़ो(emu, epcm->capture_idx_reg, 0) & 0x0000ffff;
	वापस bytes_to_frames(runसमय, ptr);
पूर्ण

/*
 *  Playback support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_96000,
	.rate_min =		4000,
	.rate_max =		96000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  Capture support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	384,
	.period_bytes_max =	(64*1024),
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1_capture_efx =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | 
				 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | 
				 SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000,
	.rate_min =		44100,
	.rate_max =		192000,
	.channels_min =		8,
	.channels_max =		8,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	384,
	.period_bytes_max =	(64*1024),
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

/*
 *
 */

अटल व्योम snd_emu10k1_pcm_mixer_notअगरy1(काष्ठा snd_emu10k1 *emu, काष्ठा snd_kcontrol *kctl, पूर्णांक idx, पूर्णांक activate)
अणु
	काष्ठा snd_ctl_elem_id id;

	अगर (! kctl)
		वापस;
	अगर (activate)
		kctl->vd[idx].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	अन्यथा
		kctl->vd[idx].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(emu->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO,
		       snd_ctl_build_ioff(&id, kctl, idx));
पूर्ण

अटल व्योम snd_emu10k1_pcm_mixer_notअगरy(काष्ठा snd_emu10k1 *emu, पूर्णांक idx, पूर्णांक activate)
अणु
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_send_routing, idx, activate);
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_send_volume, idx, activate);
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_attn, idx, activate);
पूर्ण

अटल व्योम snd_emu10k1_pcm_efx_mixer_notअगरy(काष्ठा snd_emu10k1 *emu, पूर्णांक idx, पूर्णांक activate)
अणु
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_efx_send_routing, idx, activate);
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_efx_send_volume, idx, activate);
	snd_emu10k1_pcm_mixer_notअगरy1(emu, emu->ctl_efx_attn, idx, activate);
पूर्ण

अटल व्योम snd_emu10k1_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm_mixer *mix;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_EFX_PLAYBACK; i++) अणु
		mix = &emu->efx_pcm_mixer[i];
		mix->epcm = शून्य;
		snd_emu10k1_pcm_efx_mixer_notअगरy(emu, i, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_emu10k1_pcm_mixer *mix;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक i;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->type = PLAYBACK_EFX;
	epcm->substream = substream;
	
	emu->pcm_playback_efx_substream = substream;

	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_emu10k1_pcm_मुक्त_substream;
	runसमय->hw = snd_emu10k1_efx_playback;
	
	क्रम (i = 0; i < NUM_EFX_PLAYBACK; i++) अणु
		mix = &emu->efx_pcm_mixer[i];
		mix->send_routing[0][0] = i;
		स_रखो(&mix->send_volume, 0, माप(mix->send_volume));
		mix->send_volume[0][0] = 255;
		mix->attn[0] = 0xffff;
		mix->epcm = epcm;
		snd_emu10k1_pcm_efx_mixer_notअगरy(emu, i, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_emu10k1_pcm_mixer *mix;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक i, err, sample_rate;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->type = PLAYBACK_EMUVOICE;
	epcm->substream = substream;
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_emu10k1_pcm_मुक्त_substream;
	runसमय->hw = snd_emu10k1_playback;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0) अणु
		kमुक्त(epcm);
		वापस err;
	पूर्ण
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 256, अच_पूर्णांक_उच्च)) < 0) अणु
		kमुक्त(epcm);
		वापस err;
	पूर्ण
	अगर (emu->card_capabilities->emu_model && emu->emu1010.पूर्णांकernal_घड़ी == 0)
		sample_rate = 44100;
	अन्यथा
		sample_rate = 48000;
	err = snd_pcm_hw_rule_noresample(runसमय, sample_rate);
	अगर (err < 0) अणु
		kमुक्त(epcm);
		वापस err;
	पूर्ण
	mix = &emu->pcm_mixer[substream->number];
	क्रम (i = 0; i < 4; i++)
		mix->send_routing[0][i] = mix->send_routing[1][i] = mix->send_routing[2][i] = i;
	स_रखो(&mix->send_volume, 0, माप(mix->send_volume));
	mix->send_volume[0][0] = mix->send_volume[0][1] =
	mix->send_volume[1][0] = mix->send_volume[2][1] = 255;
	mix->attn[0] = mix->attn[1] = mix->attn[2] = 0xffff;
	mix->epcm = epcm;
	snd_emu10k1_pcm_mixer_notअगरy(emu, substream->number, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm_mixer *mix = &emu->pcm_mixer[substream->number];

	mix->epcm = शून्य;
	snd_emu10k1_pcm_mixer_notअगरy(emu, substream->number, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->type = CAPTURE_AC97ADC;
	epcm->substream = substream;
	epcm->capture_ipr = IPR_ADCBUFFULL|IPR_ADCBUFHALFFULL;
	epcm->capture_पूर्णांकe = INTE_ADCBUFENABLE;
	epcm->capture_ba_reg = ADCBA;
	epcm->capture_bs_reg = ADCBS;
	epcm->capture_idx_reg = emu->audigy ? A_ADCIDX : ADCIDX;
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_emu10k1_pcm_मुक्त_substream;
	runसमय->hw = snd_emu10k1_capture;
	emu->capture_पूर्णांकerrupt = snd_emu10k1_pcm_ac97adc_पूर्णांकerrupt;
	emu->pcm_capture_substream = substream;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, &hw_स्थिरraपूर्णांकs_capture_period_sizes);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_capture_rates);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);

	emu->capture_पूर्णांकerrupt = शून्य;
	emu->pcm_capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_mic_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->type = CAPTURE_AC97MIC;
	epcm->substream = substream;
	epcm->capture_ipr = IPR_MICBUFFULL|IPR_MICBUFHALFFULL;
	epcm->capture_पूर्णांकe = INTE_MICBUFENABLE;
	epcm->capture_ba_reg = MICBA;
	epcm->capture_bs_reg = MICBS;
	epcm->capture_idx_reg = emu->audigy ? A_MICIDX : MICIDX;
	substream->runसमय->निजी_data = epcm;
	substream->runसमय->निजी_मुक्त = snd_emu10k1_pcm_मुक्त_substream;
	runसमय->hw = snd_emu10k1_capture;
	runसमय->hw.rates = SNDRV_PCM_RATE_8000;
	runसमय->hw.rate_min = runसमय->hw.rate_max = 8000;
	runसमय->hw.channels_min = 1;
	emu->capture_mic_पूर्णांकerrupt = snd_emu10k1_pcm_ac97mic_पूर्णांकerrupt;
	emu->pcm_capture_mic_substream = substream;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, &hw_स्थिरraपूर्णांकs_capture_period_sizes);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_mic_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);

	emu->capture_पूर्णांकerrupt = शून्य;
	emu->pcm_capture_mic_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_efx_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक nefx = emu->audigy ? 64 : 32;
	पूर्णांक idx;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->type = CAPTURE_EFX;
	epcm->substream = substream;
	epcm->capture_ipr = IPR_EFXBUFFULL|IPR_EFXBUFHALFFULL;
	epcm->capture_पूर्णांकe = INTE_EFXBUFENABLE;
	epcm->capture_ba_reg = FXBA;
	epcm->capture_bs_reg = FXBS;
	epcm->capture_idx_reg = FXIDX;
	substream->runसमय->निजी_data = epcm;
	substream->runसमय->निजी_मुक्त = snd_emu10k1_pcm_मुक्त_substream;
	runसमय->hw = snd_emu10k1_capture_efx;
	runसमय->hw.rates = SNDRV_PCM_RATE_48000;
	runसमय->hw.rate_min = runसमय->hw.rate_max = 48000;
	spin_lock_irq(&emu->reg_lock);
	अगर (emu->card_capabilities->emu_model) अणु
		/*  Nb. of channels has been increased to 16 */
		/* TODO
		 * SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE
		 * SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
		 * SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
		 * SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000
		 * rate_min = 44100,
		 * rate_max = 192000,
		 * channels_min = 16,
		 * channels_max = 16,
		 * Need to add mixer control to fix sample rate
		 *                 
		 * There are 32 mono channels of 16bits each.
		 * 24bit Audio uses 2x channels over 16bit
		 * 96kHz uses 2x channels over 48kHz
		 * 192kHz uses 4x channels over 48kHz
		 * So, क्रम 48kHz 24bit, one has 16 channels
		 * क्रम 96kHz 24bit, one has 8 channels
		 * क्रम 192kHz 24bit, one has 4 channels
		 *
		 */
#अगर 1
		चयन (emu->emu1010.पूर्णांकernal_घड़ी) अणु
		हाल 0:
			/* For 44.1kHz */
			runसमय->hw.rates = SNDRV_PCM_RATE_44100;
			runसमय->hw.rate_min = runसमय->hw.rate_max = 44100;
			runसमय->hw.channels_min =
				runसमय->hw.channels_max = 16;
			अवरोध;
		हाल 1:
			/* For 48kHz */
			runसमय->hw.rates = SNDRV_PCM_RATE_48000;
			runसमय->hw.rate_min = runसमय->hw.rate_max = 48000;
			runसमय->hw.channels_min =
				runसमय->hw.channels_max = 16;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
#अगर 0
		/* For 96kHz */
		runसमय->hw.rates = SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_min = runसमय->hw.rate_max = 96000;
		runसमय->hw.channels_min = runसमय->hw.channels_max = 4;
#पूर्ण_अगर
#अगर 0
		/* For 192kHz */
		runसमय->hw.rates = SNDRV_PCM_RATE_192000;
		runसमय->hw.rate_min = runसमय->hw.rate_max = 192000;
		runसमय->hw.channels_min = runसमय->hw.channels_max = 2;
#पूर्ण_अगर
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE;
		/* efx_voices_mask[0] is expected to be zero
 		 * efx_voices_mask[1] is expected to have 32bits set
		 */
	पूर्ण अन्यथा अणु
		runसमय->hw.channels_min = runसमय->hw.channels_max = 0;
		क्रम (idx = 0; idx < nefx; idx++) अणु
			अगर (emu->efx_voices_mask[idx/32] & (1 << (idx%32))) अणु
				runसमय->hw.channels_min++;
				runसमय->hw.channels_max++;
			पूर्ण
		पूर्ण
	पूर्ण
	epcm->capture_cr_val = emu->efx_voices_mask[0];
	epcm->capture_cr_val2 = emu->efx_voices_mask[1];
	spin_unlock_irq(&emu->reg_lock);
	emu->capture_efx_पूर्णांकerrupt = snd_emu10k1_pcm_efx_पूर्णांकerrupt;
	emu->pcm_capture_efx_substream = substream;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, &hw_स्थिरraपूर्णांकs_capture_period_sizes);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_capture_efx_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);

	emu->capture_पूर्णांकerrupt = शून्य;
	emu->pcm_capture_efx_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_playback_ops = अणु
	.खोलो =			snd_emu10k1_playback_खोलो,
	.बंद =		snd_emu10k1_playback_बंद,
	.hw_params =		snd_emu10k1_playback_hw_params,
	.hw_मुक्त =		snd_emu10k1_playback_hw_मुक्त,
	.prepare =		snd_emu10k1_playback_prepare,
	.trigger =		snd_emu10k1_playback_trigger,
	.poपूर्णांकer =		snd_emu10k1_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_capture_ops = अणु
	.खोलो =			snd_emu10k1_capture_खोलो,
	.बंद =		snd_emu10k1_capture_बंद,
	.prepare =		snd_emu10k1_capture_prepare,
	.trigger =		snd_emu10k1_capture_trigger,
	.poपूर्णांकer =		snd_emu10k1_capture_poपूर्णांकer,
पूर्ण;

/* EFX playback */
अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_efx_playback_ops = अणु
	.खोलो =			snd_emu10k1_efx_playback_खोलो,
	.बंद =		snd_emu10k1_efx_playback_बंद,
	.hw_params =		snd_emu10k1_playback_hw_params,
	.hw_मुक्त =		snd_emu10k1_efx_playback_hw_मुक्त,
	.prepare =		snd_emu10k1_efx_playback_prepare,
	.trigger =		snd_emu10k1_efx_playback_trigger,
	.poपूर्णांकer =		snd_emu10k1_efx_playback_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_emu10k1_pcm(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(emu->card, "emu10k1", device, 32, 1, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = emu;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_emu10k1_capture_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	म_नकल(pcm->name, "ADC Capture/Standard PCM Playback");
	emu->pcm = pcm;

	/* playback substream can't use managed buffers due to alignment */
	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
		snd_pcm_lib_pपुनः_स्मृतिate_pages(substream, SNDRV_DMA_TYPE_DEV_SG,
					      &emu->pci->dev,
					      64*1024, 64*1024);

	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream; substream; substream = substream->next)
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   &emu->pci->dev, 64*1024, 64*1024);

	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_pcm_multi(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(emu->card, "emu10k1", device, 1, 0, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = emu;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1_efx_playback_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	म_नकल(pcm->name, "Multichannel Playback");
	emu->pcm_multi = pcm;

	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
		snd_pcm_lib_pपुनः_स्मृतिate_pages(substream, SNDRV_DMA_TYPE_DEV_SG,
					      &emu->pci->dev,
					      64*1024, 64*1024);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_capture_mic_ops = अणु
	.खोलो =			snd_emu10k1_capture_mic_खोलो,
	.बंद =		snd_emu10k1_capture_mic_बंद,
	.prepare =		snd_emu10k1_capture_prepare,
	.trigger =		snd_emu10k1_capture_trigger,
	.poपूर्णांकer =		snd_emu10k1_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_emu10k1_pcm_mic(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(emu->card, "emu10k1 mic", device, 0, 1, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = emu;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_emu10k1_capture_mic_ops);

	pcm->info_flags = 0;
	म_नकल(pcm->name, "Mic Capture");
	emu->pcm_mic = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &emu->pci->dev,
				       64*1024, 64*1024);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_pcm_efx_voices_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक nefx = emu->audigy ? 64 : 32;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = nefx;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_pcm_efx_voices_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक nefx = emu->audigy ? 64 : 32;
	पूर्णांक idx;
	
	spin_lock_irq(&emu->reg_lock);
	क्रम (idx = 0; idx < nefx; idx++)
		ucontrol->value.पूर्णांकeger.value[idx] = (emu->efx_voices_mask[idx / 32] & (1 << (idx % 32))) ? 1 : 0;
	spin_unlock_irq(&emu->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_pcm_efx_voices_mask_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक nval[2], bits;
	पूर्णांक nefx = emu->audigy ? 64 : 32;
	पूर्णांक nefxb = emu->audigy ? 7 : 6;
	पूर्णांक change, idx;
	
	nval[0] = nval[1] = 0;
	क्रम (idx = 0, bits = 0; idx < nefx; idx++)
		अगर (ucontrol->value.पूर्णांकeger.value[idx]) अणु
			nval[idx / 32] |= 1 << (idx % 32);
			bits++;
		पूर्ण
		
	क्रम (idx = 0; idx < nefxb; idx++)
		अगर (1 << idx == bits)
			अवरोध;
	
	अगर (idx >= nefxb)
		वापस -EINVAL;

	spin_lock_irq(&emu->reg_lock);
	change = (nval[0] != emu->efx_voices_mask[0]) ||
		(nval[1] != emu->efx_voices_mask[1]);
	emu->efx_voices_mask[0] = nval[0];
	emu->efx_voices_mask[1] = nval[1];
	spin_unlock_irq(&emu->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_pcm_efx_voices_mask = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "Captured FX8010 Outputs",
	.info = snd_emu10k1_pcm_efx_voices_mask_info,
	.get = snd_emu10k1_pcm_efx_voices_mask_get,
	.put = snd_emu10k1_pcm_efx_voices_mask_put
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_capture_efx_ops = अणु
	.खोलो =			snd_emu10k1_capture_efx_खोलो,
	.बंद =		snd_emu10k1_capture_efx_बंद,
	.prepare =		snd_emu10k1_capture_prepare,
	.trigger =		snd_emu10k1_capture_trigger,
	.poपूर्णांकer =		snd_emu10k1_capture_poपूर्णांकer,
पूर्ण;


/* EFX playback */

#घोषणा INITIAL_TRAM_SHIFT     14
#घोषणा INITIAL_TRAM_POS(size) ((((size) / 2) - INITIAL_TRAM_SHIFT) - 1)

अटल व्योम snd_emu10k1_fx8010_playback_irq(काष्ठा snd_emu10k1 *emu, व्योम *निजी_data)
अणु
	काष्ठा snd_pcm_substream *substream = निजी_data;
	snd_pcm_period_elapsed(substream);
पूर्ण

अटल व्योम snd_emu10k1_fx8010_playback_tram_poke1(अचिन्हित लघु *dst_left,
						   अचिन्हित लघु *dst_right,
						   अचिन्हित लघु *src,
						   अचिन्हित पूर्णांक count,
						   अचिन्हित पूर्णांक tram_shअगरt)
अणु
	/*
	dev_dbg(emu->card->dev,
		"tram_poke1: dst_left = 0x%p, dst_right = 0x%p, "
	       "src = 0x%p, count = 0x%x\n",
	       dst_left, dst_right, src, count);
	*/
	अगर ((tram_shअगरt & 1) == 0) अणु
		जबतक (count--) अणु
			*dst_left-- = *src++;
			*dst_right-- = *src++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*dst_right-- = *src++;
			*dst_left-- = *src++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fx8010_pb_trans_copy(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	अचिन्हित पूर्णांक tram_size = pcm->buffer_size;
	अचिन्हित लघु *src = (अचिन्हित लघु *)(substream->runसमय->dma_area + rec->sw_data);
	अचिन्हित पूर्णांक frames = bytes >> 2, count;
	अचिन्हित पूर्णांक tram_pos = pcm->tram_pos;
	अचिन्हित पूर्णांक tram_shअगरt = pcm->tram_shअगरt;

	जबतक (frames > tram_pos) अणु
		count = tram_pos + 1;
		snd_emu10k1_fx8010_playback_tram_poke1((अचिन्हित लघु *)emu->fx8010.etram_pages.area + tram_pos,
						       (अचिन्हित लघु *)emu->fx8010.etram_pages.area + tram_pos + tram_size / 2,
						       src, count, tram_shअगरt);
		src += count * 2;
		frames -= count;
		tram_pos = (tram_size / 2) - 1;
		tram_shअगरt++;
	पूर्ण
	snd_emu10k1_fx8010_playback_tram_poke1((अचिन्हित लघु *)emu->fx8010.etram_pages.area + tram_pos,
					       (अचिन्हित लघु *)emu->fx8010.etram_pages.area + tram_pos + tram_size / 2,
					       src, frames, tram_shअगरt);
	tram_pos -= frames;
	pcm->tram_pos = tram_pos;
	pcm->tram_shअगरt = tram_shअगरt;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_playback_transfer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];

	वापस snd_pcm_indirect_playback_transfer(substream, &pcm->pcm_rec,
						  fx8010_pb_trans_copy);
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pcm->channels; i++)
		snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + 0x80 + pcm->etram[i], 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	अचिन्हित पूर्णांक i;
	
	/*
	dev_dbg(emu->card->dev, "prepare: etram_pages = 0x%p, dma_area = 0x%x, "
	       "buffer_size = 0x%x (0x%x)\n",
	       emu->fx8010.etram_pages, runसमय->dma_area,
	       runसमय->buffer_size, runसमय->buffer_size << 2);
	*/
	स_रखो(&pcm->pcm_rec, 0, माप(pcm->pcm_rec));
	pcm->pcm_rec.hw_buffer_size = pcm->buffer_size * 2; /* byte size */
	pcm->pcm_rec.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	pcm->tram_pos = INITIAL_TRAM_POS(pcm->buffer_size);
	pcm->tram_shअगरt = 0;
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_running, 0, 0);	/* reset */
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_trigger, 0, 0);	/* reset */
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_size, 0, runसमय->buffer_size);
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_ptr, 0, 0);		/* reset ptr number */
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_count, 0, runसमय->period_size);
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_पंचांगpcount, 0, runसमय->period_size);
	क्रम (i = 0; i < pcm->channels; i++)
		snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + 0x80 + pcm->etram[i], 0, (TANKMEMADDRREG_READ|TANKMEMADDRREG_ALIGN) + i * (runसमय->buffer_size / pcm->channels));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	पूर्णांक result = 0;

	spin_lock(&emu->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* follow thru */
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
#अगर_घोषित EMU10K1_SET_AC3_IEC958
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < 3; i++) अणु
			अचिन्हित पूर्णांक bits;
			bits = SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
			       SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC | SPCS_GENERATIONSTATUS |
			       0x00001200 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT | SPCS_NOTAUDIODATA;
			snd_emu10k1_ptr_ग_लिखो(emu, SPCS0 + i, 0, bits);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
		result = snd_emu10k1_fx8010_रेजिस्टर_irq_handler(emu, snd_emu10k1_fx8010_playback_irq, pcm->gpr_running, substream, &pcm->irq);
		अगर (result < 0)
			जाओ __err;
		snd_emu10k1_fx8010_playback_transfer(substream);	/* roll the ball */
		snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_trigger, 0, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		snd_emu10k1_fx8010_unरेजिस्टर_irq_handler(emu, &pcm->irq);
		snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + pcm->gpr_trigger, 0, 0);
		pcm->tram_pos = INITIAL_TRAM_POS(pcm->buffer_size);
		pcm->tram_shअगरt = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
      __err:
	spin_unlock(&emu->reg_lock);
	वापस result;
पूर्ण

अटल snd_pcm_uframes_t snd_emu10k1_fx8010_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	माप_प्रकार ptr; /* byte poपूर्णांकer */

	अगर (!snd_emu10k1_ptr_पढ़ो(emu, emu->gpr_base + pcm->gpr_trigger, 0))
		वापस 0;
	ptr = snd_emu10k1_ptr_पढ़ो(emu, emu->gpr_base + pcm->gpr_ptr, 0) << 2;
	वापस snd_pcm_indirect_playback_poपूर्णांकer(substream, &pcm->pcm_rec, ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1_fx8010_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_RESUME |
				 /* SNDRV_PCM_INFO_MMAP_VALID | */ SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	1024,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_emu10k1_fx8010_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];

	runसमय->hw = snd_emu10k1_fx8010_playback;
	runसमय->hw.channels_min = runसमय->hw.channels_max = pcm->channels;
	runसमय->hw.period_bytes_max = (pcm->buffer_size * 2) / 2;
	spin_lock_irq(&emu->reg_lock);
	अगर (pcm->valid == 0) अणु
		spin_unlock_irq(&emu->reg_lock);
		वापस -ENODEV;
	पूर्ण
	pcm->खोलोed = 1;
	spin_unlock_irq(&emu->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];

	spin_lock_irq(&emu->reg_lock);
	pcm->खोलोed = 0;
	spin_unlock_irq(&emu->reg_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1_fx8010_playback_ops = अणु
	.खोलो =			snd_emu10k1_fx8010_playback_खोलो,
	.बंद =		snd_emu10k1_fx8010_playback_बंद,
	.hw_मुक्त =		snd_emu10k1_fx8010_playback_hw_मुक्त,
	.prepare =		snd_emu10k1_fx8010_playback_prepare,
	.trigger =		snd_emu10k1_fx8010_playback_trigger,
	.poपूर्णांकer =		snd_emu10k1_fx8010_playback_poपूर्णांकer,
	.ack =			snd_emu10k1_fx8010_playback_transfer,
पूर्ण;

पूर्णांक snd_emu10k1_pcm_efx(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(emu->card, "emu10k1 efx", device, 8, 1, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = emu;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1_fx8010_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_emu10k1_capture_efx_ops);

	pcm->info_flags = 0;
	म_नकल(pcm->name, "Multichannel Capture/PT Playback");
	emu->pcm_efx = pcm;

	/* EFX capture - record the "FXBUS2" channels, by शेष we connect the EXTINs 
	 * to these
	 */	
	
	/* emu->efx_voices_mask[0] = FXWC_DEFAULTROUTE_C | FXWC_DEFAULTROUTE_A; */
	अगर (emu->audigy) अणु
		emu->efx_voices_mask[0] = 0;
		अगर (emu->card_capabilities->emu_model)
			/* Pavel Hofman - 32 voices will be used क्रम
			 * capture (ग_लिखो mode) -
			 * each bit = corresponding voice
			 */
			emu->efx_voices_mask[1] = 0xffffffff;
		अन्यथा
			emu->efx_voices_mask[1] = 0xffff;
	पूर्ण अन्यथा अणु
		emu->efx_voices_mask[0] = 0xffff0000;
		emu->efx_voices_mask[1] = 0;
	पूर्ण
	/* For emu1010, the control has to set 32 upper bits (voices)
	 * out of the 64 bits (voices) to true क्रम the 16-channels capture
	 * to work correctly. Correct A_FXWC2 initial value (0xffffffff)
	 * is alपढ़ोy defined but the snd_emu10k1_pcm_efx_voices_mask
	 * control can override this रेजिस्टर's value.
	 */
	kctl = snd_ctl_new1(&snd_emu10k1_pcm_efx_voices_mask, emu);
	अगर (!kctl)
		वापस -ENOMEM;
	kctl->id.device = device;
	err = snd_ctl_add(emu->card, kctl);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &emu->pci->dev,
				       64*1024, 64*1024);

	वापस 0;
पूर्ण
