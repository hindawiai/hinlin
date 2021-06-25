<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम audio on multअगरunction CS5535 companion device
 * Copyright (C) Jaya Kumar
 *
 * Based on Jaroslav Kysela and Takashi Iwai's examples.
 * This work was sponsored by CIS(M) Sdn Bhd.
 *
 * toकरो: add be fmt support, spdअगर, pm
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/ac97_codec.h>
#समावेश "cs5535audio.h"

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs5535audio_playback =
अणु
	.info =			(
				SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
		 		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 		SNDRV_PCM_INFO_MMAP_VALID |
		 		SNDRV_PCM_INFO_PAUSE |
				SNDRV_PCM_INFO_RESUME
				),
	.क्रमmats =		(
				SNDRV_PCM_FMTBIT_S16_LE
				),
	.rates =		(
				SNDRV_PCM_RATE_CONTINUOUS |
				SNDRV_PCM_RATE_8000_48000
				),
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(64*1024 - 16),
	.periods_min =		1,
	.periods_max =		CS5535AUDIO_MAX_DESCRIPTORS,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs5535audio_capture =
अणु
	.info =			(
				SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
		 		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 		SNDRV_PCM_INFO_MMAP_VALID
				),
	.क्रमmats =		(
				SNDRV_PCM_FMTBIT_S16_LE
				),
	.rates =		(
				SNDRV_PCM_RATE_CONTINUOUS |
				SNDRV_PCM_RATE_8000_48000
				),
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(64*1024 - 16),
	.periods_min =		1,
	.periods_max =		CS5535AUDIO_MAX_DESCRIPTORS,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_cs5535audio_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_cs5535audio_playback;
	runसमय->hw.rates = cs5535au->ac97->rates[AC97_RATES_FRONT_DAC];
	snd_pcm_limit_hw_rates(runसमय);
	cs5535au->playback_substream = substream;
	runसमय->निजी_data = &(cs5535au->dmas[CS5535AUDIO_DMA_PLAYBACK]);
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
				SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5535audio_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

#घोषणा CS5535AUDIO_DESC_LIST_SIZE \
	PAGE_ALIGN(CS5535AUDIO_MAX_DESCRIPTORS * माप(काष्ठा cs5535audio_dma_desc))

अटल पूर्णांक cs5535audio_build_dma_packets(काष्ठा cs5535audio *cs5535au,
					 काष्ठा cs5535audio_dma *dma,
					 काष्ठा snd_pcm_substream *substream,
					 अचिन्हित पूर्णांक periods,
					 अचिन्हित पूर्णांक period_bytes)
अणु
	अचिन्हित पूर्णांक i;
	u32 addr, desc_addr, jmpprd_addr;
	काष्ठा cs5535audio_dma_desc *lastdesc;

	अगर (periods > CS5535AUDIO_MAX_DESCRIPTORS)
		वापस -ENOMEM;

	अगर (dma->desc_buf.area == शून्य) अणु
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					&cs5535au->pci->dev,
					CS5535AUDIO_DESC_LIST_SIZE+1,
					&dma->desc_buf) < 0)
			वापस -ENOMEM;
		dma->period_bytes = dma->periods = 0;
	पूर्ण

	अगर (dma->periods == periods && dma->period_bytes == period_bytes)
		वापस 0;

	/* the u32 cast is okay because in snd*create we successfully told
   	   pci alloc that we're only 32 bit capable so the uppper will be 0 */
	addr = (u32) substream->runसमय->dma_addr;
	desc_addr = (u32) dma->desc_buf.addr;
	क्रम (i = 0; i < periods; i++) अणु
		काष्ठा cs5535audio_dma_desc *desc =
			&((काष्ठा cs5535audio_dma_desc *) dma->desc_buf.area)[i];
		desc->addr = cpu_to_le32(addr);
		desc->size = cpu_to_le16(period_bytes);
		desc->ctlreserved = cpu_to_le16(PRD_EOP);
		desc_addr += माप(काष्ठा cs5535audio_dma_desc);
		addr += period_bytes;
	पूर्ण
	/* we reserved one dummy descriptor at the end to करो the PRD jump */
	lastdesc = &((काष्ठा cs5535audio_dma_desc *) dma->desc_buf.area)[periods];
	lastdesc->addr = cpu_to_le32((u32) dma->desc_buf.addr);
	lastdesc->size = 0;
	lastdesc->ctlreserved = cpu_to_le16(PRD_JMP);
	jmpprd_addr = (u32)dma->desc_buf.addr +
		माप(काष्ठा cs5535audio_dma_desc) * periods;

	dma->substream = substream;
	dma->period_bytes = period_bytes;
	dma->periods = periods;
	spin_lock_irq(&cs5535au->reg_lock);
	dma->ops->disable_dma(cs5535au);
	dma->ops->setup_prd(cs5535au, jmpprd_addr);
	spin_unlock_irq(&cs5535au->reg_lock);
	वापस 0;
पूर्ण

अटल व्योम cs5535audio_playback_enable_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM0_CMD, BM_CTL_EN);
पूर्ण

अटल व्योम cs5535audio_playback_disable_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM0_CMD, 0);
पूर्ण

अटल व्योम cs5535audio_playback_छोड़ो_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM0_CMD, BM_CTL_PAUSE);
पूर्ण

अटल व्योम cs5535audio_playback_setup_prd(काष्ठा cs5535audio *cs5535au,
					   u32 prd_addr)
अणु
	cs_ग_लिखोl(cs5535au, ACC_BM0_PRD, prd_addr);
पूर्ण

अटल u32 cs5535audio_playback_पढ़ो_prd(काष्ठा cs5535audio *cs5535au)
अणु
	वापस cs_पढ़ोl(cs5535au, ACC_BM0_PRD);
पूर्ण

अटल u32 cs5535audio_playback_पढ़ो_dma_pntr(काष्ठा cs5535audio *cs5535au)
अणु
	वापस cs_पढ़ोl(cs5535au, ACC_BM0_PNTR);
पूर्ण

अटल व्योम cs5535audio_capture_enable_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM1_CMD, BM_CTL_EN);
पूर्ण

अटल व्योम cs5535audio_capture_disable_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM1_CMD, 0);
पूर्ण

अटल व्योम cs5535audio_capture_छोड़ो_dma(काष्ठा cs5535audio *cs5535au)
अणु
	cs_ग_लिखोb(cs5535au, ACC_BM1_CMD, BM_CTL_PAUSE);
पूर्ण

अटल व्योम cs5535audio_capture_setup_prd(काष्ठा cs5535audio *cs5535au,
					  u32 prd_addr)
अणु
	cs_ग_लिखोl(cs5535au, ACC_BM1_PRD, prd_addr);
पूर्ण

अटल u32 cs5535audio_capture_पढ़ो_prd(काष्ठा cs5535audio *cs5535au)
अणु
	वापस cs_पढ़ोl(cs5535au, ACC_BM1_PRD);
पूर्ण

अटल u32 cs5535audio_capture_पढ़ो_dma_pntr(काष्ठा cs5535audio *cs5535au)
अणु
	वापस cs_पढ़ोl(cs5535au, ACC_BM1_PNTR);
पूर्ण

अटल व्योम cs5535audio_clear_dma_packets(काष्ठा cs5535audio *cs5535au,
					  काष्ठा cs5535audio_dma *dma,
					  काष्ठा snd_pcm_substream *substream)
अणु
	snd_dma_मुक्त_pages(&dma->desc_buf);
	dma->desc_buf.area = शून्य;
	dma->substream = शून्य;
पूर्ण

अटल पूर्णांक snd_cs5535audio_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	काष्ठा cs5535audio_dma *dma = substream->runसमय->निजी_data;
	पूर्णांक err;

	dma->buf_addr = substream->runसमय->dma_addr;
	dma->buf_bytes = params_buffer_bytes(hw_params);

	err = cs5535audio_build_dma_packets(cs5535au, dma, substream,
					    params_periods(hw_params),
					    params_period_bytes(hw_params));
	अगर (!err)
		dma->pcm_खोलो_flag = 1;

	वापस err;
पूर्ण

अटल पूर्णांक snd_cs5535audio_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	काष्ठा cs5535audio_dma *dma = substream->runसमय->निजी_data;

	अगर (dma->pcm_खोलो_flag) अणु
		अगर (substream == cs5535au->playback_substream)
			snd_ac97_update_घातer(cs5535au->ac97,
					AC97_PCM_FRONT_DAC_RATE, 0);
		अन्यथा
			snd_ac97_update_घातer(cs5535au->ac97,
					AC97_PCM_LR_ADC_RATE, 0);
		dma->pcm_खोलो_flag = 0;
	पूर्ण
	cs5535audio_clear_dma_packets(cs5535au, dma, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5535audio_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	वापस snd_ac97_set_rate(cs5535au->ac97, AC97_PCM_FRONT_DAC_RATE,
				 substream->runसमय->rate);
पूर्ण

अटल पूर्णांक snd_cs5535audio_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	काष्ठा cs5535audio_dma *dma = substream->runसमय->निजी_data;
	पूर्णांक err = 0;

	spin_lock(&cs5535au->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dma->ops->छोड़ो_dma(cs5535au);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dma->ops->enable_dma(cs5535au);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_START:
		dma->ops->enable_dma(cs5535au);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
		dma->ops->enable_dma(cs5535au);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dma->ops->disable_dma(cs5535au);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		dma->ops->disable_dma(cs5535au);
		अवरोध;
	शेष:
		dev_err(cs5535au->card->dev, "unhandled trigger\n");
		err = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&cs5535au->reg_lock);
	वापस err;
पूर्ण

अटल snd_pcm_uframes_t snd_cs5535audio_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream
							*substream)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	u32 curdma;
	काष्ठा cs5535audio_dma *dma;

	dma = substream->runसमय->निजी_data;
	curdma = dma->ops->पढ़ो_dma_pntr(cs5535au);
	अगर (curdma < dma->buf_addr) अणु
		dev_err(cs5535au->card->dev, "curdma=%x < %x bufaddr.\n",
					curdma, dma->buf_addr);
		वापस 0;
	पूर्ण
	curdma -= dma->buf_addr;
	अगर (curdma >= dma->buf_bytes) अणु
		dev_err(cs5535au->card->dev, "diff=%x >= %x buf_bytes.\n",
					curdma, dma->buf_bytes);
		वापस 0;
	पूर्ण
	वापस bytes_to_frames(substream->runसमय, curdma);
पूर्ण

अटल पूर्णांक snd_cs5535audio_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_cs5535audio_capture;
	runसमय->hw.rates = cs5535au->ac97->rates[AC97_RATES_ADC];
	snd_pcm_limit_hw_rates(runसमय);
	cs5535au->capture_substream = substream;
	runसमय->निजी_data = &(cs5535au->dmas[CS5535AUDIO_DMA_CAPTURE]);
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					 SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	olpc_capture_खोलो(cs5535au->ac97);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5535audio_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	olpc_capture_बंद(cs5535au->ac97);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5535audio_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	वापस snd_ac97_set_rate(cs5535au->ac97, AC97_PCM_LR_ADC_RATE,
				 substream->runसमय->rate);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_cs5535audio_playback_ops = अणु
	.खोलो =		snd_cs5535audio_playback_खोलो,
	.बंद =	snd_cs5535audio_playback_बंद,
	.hw_params =	snd_cs5535audio_hw_params,
	.hw_मुक्त =	snd_cs5535audio_hw_मुक्त,
	.prepare =	snd_cs5535audio_playback_prepare,
	.trigger =	snd_cs5535audio_trigger,
	.poपूर्णांकer =	snd_cs5535audio_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs5535audio_capture_ops = अणु
	.खोलो =		snd_cs5535audio_capture_खोलो,
	.बंद =	snd_cs5535audio_capture_बंद,
	.hw_params =	snd_cs5535audio_hw_params,
	.hw_मुक्त =	snd_cs5535audio_hw_मुक्त,
	.prepare =	snd_cs5535audio_capture_prepare,
	.trigger =	snd_cs5535audio_trigger,
	.poपूर्णांकer =	snd_cs5535audio_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा cs5535audio_dma_ops snd_cs5535audio_playback_dma_ops = अणु
        .type = CS5535AUDIO_DMA_PLAYBACK,
        .enable_dma = cs5535audio_playback_enable_dma,
        .disable_dma = cs5535audio_playback_disable_dma,
        .setup_prd = cs5535audio_playback_setup_prd,
        .पढ़ो_prd = cs5535audio_playback_पढ़ो_prd,
        .छोड़ो_dma = cs5535audio_playback_छोड़ो_dma,
        .पढ़ो_dma_pntr = cs5535audio_playback_पढ़ो_dma_pntr,
पूर्ण;

अटल स्थिर काष्ठा cs5535audio_dma_ops snd_cs5535audio_capture_dma_ops = अणु
        .type = CS5535AUDIO_DMA_CAPTURE,
        .enable_dma = cs5535audio_capture_enable_dma,
        .disable_dma = cs5535audio_capture_disable_dma,
        .setup_prd = cs5535audio_capture_setup_prd,
        .पढ़ो_prd = cs5535audio_capture_पढ़ो_prd,
        .छोड़ो_dma = cs5535audio_capture_छोड़ो_dma,
        .पढ़ो_dma_pntr = cs5535audio_capture_पढ़ो_dma_pntr,
पूर्ण;

पूर्णांक snd_cs5535audio_pcm(काष्ठा cs5535audio *cs5535au)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(cs5535au->card, "CS5535 Audio", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	cs5535au->dmas[CS5535AUDIO_DMA_PLAYBACK].ops =
					&snd_cs5535audio_playback_dma_ops;
	cs5535au->dmas[CS5535AUDIO_DMA_CAPTURE].ops =
					&snd_cs5535audio_capture_dma_ops;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&snd_cs5535audio_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&snd_cs5535audio_capture_ops);

	pcm->निजी_data = cs5535au;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS5535 Audio");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &cs5535au->pci->dev,
				       64*1024, 128*1024);
	cs5535au->pcm = pcm;

	वापस 0;
पूर्ण

