<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Audio support क्रम PS3
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * All rights reserved.
 * Copyright 2006, 2007 Sony Corporation
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <sound/asound.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/meदो_स्मृति.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/ps3av.h>

#समावेश "snd_ps3.h"
#समावेश "snd_ps3_reg.h"


/*
 * global
 */
अटल काष्ठा snd_ps3_card_info the_card;

अटल पूर्णांक snd_ps3_start_delay = CONFIG_SND_PS3_DEFAULT_START_DELAY;

module_param_named(start_delay, snd_ps3_start_delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(start_delay, "time to insert silent data in ms");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;
अटल अक्षर *id = SNDRV_DEFAULT_STR1;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for PS3 soundchip.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for PS3 soundchip.");


/*
 * PS3 audio रेजिस्टर access
 */
अटल अंतरभूत u32 पढ़ो_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस in_be32(the_card.mapped_mmio_vaddr + reg);
पूर्ण
अटल अंतरभूत व्योम ग_लिखो_reg(अचिन्हित पूर्णांक reg, u32 val)
अणु
	out_be32(the_card.mapped_mmio_vaddr + reg, val);
पूर्ण
अटल अंतरभूत व्योम update_reg(अचिन्हित पूर्णांक reg, u32 or_val)
अणु
	u32 newval = पढ़ो_reg(reg) | or_val;
	ग_लिखो_reg(reg, newval);
पूर्ण
अटल अंतरभूत व्योम update_mask_reg(अचिन्हित पूर्णांक reg, u32 mask, u32 or_val)
अणु
	u32 newval = (पढ़ो_reg(reg) & mask) | or_val;
	ग_लिखो_reg(reg, newval);
पूर्ण

/*
 * ALSA defs
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_ps3_pcm_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_NONINTERLEAVED |
		 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S16_BE |
		    SNDRV_PCM_FMTBIT_S24_BE),
	.rates = (SNDRV_PCM_RATE_44100 |
		  SNDRV_PCM_RATE_48000 |
		  SNDRV_PCM_RATE_88200 |
		  SNDRV_PCM_RATE_96000),
	.rate_min = 44100,
	.rate_max = 96000,

	.channels_min = 2, /* stereo only */
	.channels_max = 2,

	.buffer_bytes_max = PS3_AUDIO_FIFO_SIZE * 64,

	/* पूर्णांकerrupt by four stages */
	.period_bytes_min = PS3_AUDIO_FIFO_STAGE_SIZE * 4,
	.period_bytes_max = PS3_AUDIO_FIFO_STAGE_SIZE * 4,

	.periods_min = 16,
	.periods_max = 32, /* buffer_size_max/ period_bytes_max */

	.fअगरo_size = PS3_AUDIO_FIFO_SIZE
पूर्ण;

अटल पूर्णांक snd_ps3_verअगरy_dma_stop(काष्ठा snd_ps3_card_info *card,
				   पूर्णांक count, पूर्णांक क्रमce_stop)
अणु
	पूर्णांक dma_ch, करोne, retries, stop_क्रमced = 0;
	uपूर्णांक32_t status;

	क्रम (dma_ch = 0; dma_ch < 8; dma_ch++) अणु
		retries = count;
		करो अणु
			status = पढ़ो_reg(PS3_AUDIO_KICK(dma_ch)) &
				PS3_AUDIO_KICK_STATUS_MASK;
			चयन (status) अणु
			हाल PS3_AUDIO_KICK_STATUS_DONE:
			हाल PS3_AUDIO_KICK_STATUS_NOTIFY:
			हाल PS3_AUDIO_KICK_STATUS_CLEAR:
			हाल PS3_AUDIO_KICK_STATUS_ERROR:
				करोne = 1;
				अवरोध;
			शेष:
				करोne = 0;
				udelay(10);
			पूर्ण
		पूर्ण जबतक (!करोne && --retries);
		अगर (!retries && क्रमce_stop) अणु
			pr_info("%s: DMA ch %d is not stopped.",
				__func__, dma_ch);
			/* last resort. क्रमce to stop dma.
			 *  NOTE: this cause DMA करोne पूर्णांकerrupts
			 */
			update_reg(PS3_AUDIO_CONFIG, PS3_AUDIO_CONFIG_CLEAR);
			stop_क्रमced = 1;
		पूर्ण
	पूर्ण
	वापस stop_क्रमced;
पूर्ण

/*
 * रुको क्रम all dma is करोne.
 * NOTE: caller should reset card->running beक्रमe call.
 *       If not, the पूर्णांकerrupt handler will re-start DMA,
 *       then DMA is never stopped.
 */
अटल व्योम snd_ps3_रुको_क्रम_dma_stop(काष्ठा snd_ps3_card_info *card)
अणु
	पूर्णांक stop_क्रमced;
	/*
	 * रुको क्रम the last dma is करोne
	 */

	/*
	 * expected maximum DMA करोne समय is 5.7ms + something (DMA itself).
	 * 5.7ms is from 16bit/sample 2ch 44.1Khz; the समय next
	 * DMA kick event would occur.
	 */
	stop_क्रमced = snd_ps3_verअगरy_dma_stop(card, 700, 1);

	/*
	 * clear outstanding पूर्णांकerrupts.
	 */
	update_reg(PS3_AUDIO_INTR_0, 0);
	update_reg(PS3_AUDIO_AX_IS, 0);

	/*
	 *revert CLEAR bit since it will not reset स्वतःmatically after DMA stop
	 */
	अगर (stop_क्रमced)
		update_mask_reg(PS3_AUDIO_CONFIG, ~PS3_AUDIO_CONFIG_CLEAR, 0);
	/* ensure the hardware sees changes */
	wmb();
पूर्ण

अटल व्योम snd_ps3_kick_dma(काष्ठा snd_ps3_card_info *card)
अणु

	update_reg(PS3_AUDIO_KICK(0), PS3_AUDIO_KICK_REQUEST);
	/* ensure the hardware sees the change */
	wmb();
पूर्ण

/*
 * convert भव addr to ioअगर bus addr.
 */
अटल dma_addr_t v_to_bus(काष्ठा snd_ps3_card_info *card, व्योम *paddr, पूर्णांक ch)
अणु
	वापस card->dma_start_bus_addr[ch] +
		(paddr - card->dma_start_vaddr[ch]);
पूर्ण;


/*
 * increment ring buffer poपूर्णांकer.
 * NOTE: caller must hold ग_लिखो spinlock
 */
अटल व्योम snd_ps3_bump_buffer(काष्ठा snd_ps3_card_info *card,
				क्रमागत snd_ps3_ch ch, माप_प्रकार byte_count,
				पूर्णांक stage)
अणु
	अगर (!stage)
		card->dma_last_transfer_vaddr[ch] =
			card->dma_next_transfer_vaddr[ch];
	card->dma_next_transfer_vaddr[ch] += byte_count;
	अगर ((card->dma_start_vaddr[ch] + (card->dma_buffer_size / 2)) <=
	    card->dma_next_transfer_vaddr[ch]) अणु
		card->dma_next_transfer_vaddr[ch] = card->dma_start_vaddr[ch];
	पूर्ण
पूर्ण
/*
 * setup dmac to send data to audio and attenuate samples on the ring buffer
 */
अटल पूर्णांक snd_ps3_program_dma(काष्ठा snd_ps3_card_info *card,
			       क्रमागत snd_ps3_dma_filltype filltype)
अणु
	/* this dmac करोes not support over 4G */
	uपूर्णांक32_t dma_addr;
	पूर्णांक fill_stages, dma_ch, stage;
	क्रमागत snd_ps3_ch ch;
	uपूर्णांक32_t ch0_kick_event = 0; /* initialize to mute gcc */
	अचिन्हित दीर्घ irqsave;
	पूर्णांक silent = 0;

	चयन (filltype) अणु
	हाल SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL:
		silent = 1;
		fallthrough;
	हाल SND_PS3_DMA_FILLTYPE_FIRSTFILL:
		ch0_kick_event = PS3_AUDIO_KICK_EVENT_ALWAYS;
		अवरोध;

	हाल SND_PS3_DMA_FILLTYPE_SILENT_RUNNING:
		silent = 1;
		fallthrough;
	हाल SND_PS3_DMA_FILLTYPE_RUNNING:
		ch0_kick_event = PS3_AUDIO_KICK_EVENT_SERIALOUT0_EMPTY;
		अवरोध;
	पूर्ण

	snd_ps3_verअगरy_dma_stop(card, 700, 0);
	fill_stages = 4;
	spin_lock_irqsave(&card->dma_lock, irqsave);
	क्रम (ch = 0; ch < 2; ch++) अणु
		क्रम (stage = 0; stage < fill_stages; stage++) अणु
			dma_ch = stage * 2 + ch;
			अगर (silent)
				dma_addr = card->null_buffer_start_dma_addr;
			अन्यथा
				dma_addr =
				v_to_bus(card,
					 card->dma_next_transfer_vaddr[ch],
					 ch);

			ग_लिखो_reg(PS3_AUDIO_SOURCE(dma_ch),
				  (PS3_AUDIO_SOURCE_TARGET_SYSTEM_MEMORY |
				   dma_addr));

			/* dst: fixed to 3wire#0 */
			अगर (ch == 0)
				ग_लिखो_reg(PS3_AUDIO_DEST(dma_ch),
					  (PS3_AUDIO_DEST_TARGET_AUDIOFIFO |
					   PS3_AUDIO_AO_3W_LDATA(0)));
			अन्यथा
				ग_लिखो_reg(PS3_AUDIO_DEST(dma_ch),
					  (PS3_AUDIO_DEST_TARGET_AUDIOFIFO |
					   PS3_AUDIO_AO_3W_RDATA(0)));

			/* count always 1 DMA block (1/2 stage = 128 bytes) */
			ग_लिखो_reg(PS3_AUDIO_DMASIZE(dma_ch), 0);
			/* bump poपूर्णांकer अगर needed */
			अगर (!silent)
				snd_ps3_bump_buffer(card, ch,
						    PS3_AUDIO_DMAC_BLOCK_SIZE,
						    stage);

			/* kick event  */
			अगर (dma_ch == 0)
				ग_लिखो_reg(PS3_AUDIO_KICK(dma_ch),
					  ch0_kick_event);
			अन्यथा
				ग_लिखो_reg(PS3_AUDIO_KICK(dma_ch),
					  PS3_AUDIO_KICK_EVENT_AUDIO_DMA(dma_ch
									 - 1) |
					  PS3_AUDIO_KICK_REQUEST);
		पूर्ण
	पूर्ण
	/* ensure the hardware sees the change */
	wmb();
	spin_unlock_irqrestore(&card->dma_lock, irqsave);

	वापस 0;
पूर्ण

/*
 * Interrupt handler
 */
अटल irqवापस_t snd_ps3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु

	uपूर्णांक32_t port_पूर्णांकr;
	पूर्णांक underflow_occured = 0;
	काष्ठा snd_ps3_card_info *card = dev_id;

	अगर (!card->running) अणु
		update_reg(PS3_AUDIO_AX_IS, 0);
		update_reg(PS3_AUDIO_INTR_0, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	port_पूर्णांकr = पढ़ो_reg(PS3_AUDIO_AX_IS);
	/*
	 *serial buffer empty detected (every 4 बार),
	 *program next dma and kick it
	 */
	अगर (port_पूर्णांकr & PS3_AUDIO_AX_IE_ASOBEIE(0)) अणु
		ग_लिखो_reg(PS3_AUDIO_AX_IS, PS3_AUDIO_AX_IE_ASOBEIE(0));
		अगर (port_पूर्णांकr & PS3_AUDIO_AX_IE_ASOBUIE(0)) अणु
			ग_लिखो_reg(PS3_AUDIO_AX_IS, port_पूर्णांकr);
			underflow_occured = 1;
		पूर्ण
		अगर (card->silent) अणु
			/* we are still in silent समय */
			snd_ps3_program_dma(card,
				(underflow_occured) ?
				SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL :
				SND_PS3_DMA_FILLTYPE_SILENT_RUNNING);
			snd_ps3_kick_dma(card);
			card->silent--;
		पूर्ण अन्यथा अणु
			snd_ps3_program_dma(card,
				(underflow_occured) ?
				SND_PS3_DMA_FILLTYPE_FIRSTFILL :
				SND_PS3_DMA_FILLTYPE_RUNNING);
			snd_ps3_kick_dma(card);
			snd_pcm_period_elapsed(card->substream);
		पूर्ण
	पूर्ण अन्यथा अगर (port_पूर्णांकr & PS3_AUDIO_AX_IE_ASOBUIE(0)) अणु
		ग_लिखो_reg(PS3_AUDIO_AX_IS, PS3_AUDIO_AX_IE_ASOBUIE(0));
		/*
		 * serial out underflow, but buffer empty not detected.
		 * in this हाल, fill fअगरo with 0 to recover.  After
		 * filling dummy data, serial स्वतःmatically start to
		 * consume them and then will generate normal buffer
		 * empty पूर्णांकerrupts.
		 * If both buffer underflow and buffer empty are occurred,
		 * it is better to करो nomal data transfer than empty one
		 */
		snd_ps3_program_dma(card,
				    SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL);
		snd_ps3_kick_dma(card);
		snd_ps3_program_dma(card,
				    SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL);
		snd_ps3_kick_dma(card);
	पूर्ण
	/* clear पूर्णांकerrupt cause */
	वापस IRQ_HANDLED;
पूर्ण;

/*
 * audio mute on/off
 * mute_on : 0 output enabled
 *           1 mute
 */
अटल पूर्णांक snd_ps3_mute(पूर्णांक mute_on)
अणु
	वापस ps3av_audio_mute(mute_on);
पूर्ण

/*
 * av setting
 * NOTE: calling this function may generate audio पूर्णांकerrupt.
 */
अटल पूर्णांक snd_ps3_change_avsetting(काष्ठा snd_ps3_card_info *card)
अणु
	पूर्णांक ret, retries, i;
	pr_debug("%s: start\n", __func__);

	ret = ps3av_set_audio_mode(card->avs.avs_audio_ch,
				  card->avs.avs_audio_rate,
				  card->avs.avs_audio_width,
				  card->avs.avs_audio_क्रमmat,
				  card->avs.avs_audio_source);
	/*
	 * Reset the following unwanted settings:
	 */

	/* disable all 3wire buffers */
	update_mask_reg(PS3_AUDIO_AO_3WMCTRL,
			~(PS3_AUDIO_AO_3WMCTRL_ASOEN(0) |
			  PS3_AUDIO_AO_3WMCTRL_ASOEN(1) |
			  PS3_AUDIO_AO_3WMCTRL_ASOEN(2) |
			  PS3_AUDIO_AO_3WMCTRL_ASOEN(3)),
			0);
	wmb();	/* ensure the hardware sees the change */
	/* रुको क्रम actually stopped */
	retries = 1000;
	जबतक ((पढ़ो_reg(PS3_AUDIO_AO_3WMCTRL) &
		(PS3_AUDIO_AO_3WMCTRL_ASORUN(0) |
		 PS3_AUDIO_AO_3WMCTRL_ASORUN(1) |
		 PS3_AUDIO_AO_3WMCTRL_ASORUN(2) |
		 PS3_AUDIO_AO_3WMCTRL_ASORUN(3))) &&
	       --retries) अणु
		udelay(1);
	पूर्ण

	/* reset buffer poपूर्णांकer */
	क्रम (i = 0; i < 4; i++) अणु
		update_reg(PS3_AUDIO_AO_3WCTRL(i),
			   PS3_AUDIO_AO_3WCTRL_ASOBRST_RESET);
		udelay(10);
	पूर्ण
	wmb(); /* ensure the hardware actually start resetting */

	/* enable 3wire#0 buffer */
	update_reg(PS3_AUDIO_AO_3WMCTRL, PS3_AUDIO_AO_3WMCTRL_ASOEN(0));


	/* In 24bit mode,ALSA inserts a zero byte at first byte of per sample */
	update_mask_reg(PS3_AUDIO_AO_3WCTRL(0),
			~PS3_AUDIO_AO_3WCTRL_ASODF,
			PS3_AUDIO_AO_3WCTRL_ASODF_LSB);
	update_mask_reg(PS3_AUDIO_AO_SPDCTRL(0),
			~PS3_AUDIO_AO_SPDCTRL_SPODF,
			PS3_AUDIO_AO_SPDCTRL_SPODF_LSB);
	/* ensure all the setting above is written back to रेजिस्टर */
	wmb();
	/* avsetting driver altered AX_IE, caller must reset it अगर you want */
	pr_debug("%s: end\n", __func__);
	वापस ret;
पूर्ण

/*
 *  set sampling rate according to the substream
 */
अटल पूर्णांक snd_ps3_set_avsetting(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ps3_card_info *card = snd_pcm_substream_chip(substream);
	काष्ठा snd_ps3_avsetting_info avs;
	पूर्णांक ret;

	avs = card->avs;

	pr_debug("%s: called freq=%d width=%d\n", __func__,
		 substream->runसमय->rate,
		 snd_pcm_क्रमmat_width(substream->runसमय->क्रमmat));

	pr_debug("%s: before freq=%d width=%d\n", __func__,
		 card->avs.avs_audio_rate, card->avs.avs_audio_width);

	/* sample rate */
	चयन (substream->runसमय->rate) अणु
	हाल 44100:
		avs.avs_audio_rate = PS3AV_CMD_AUDIO_FS_44K;
		अवरोध;
	हाल 48000:
		avs.avs_audio_rate = PS3AV_CMD_AUDIO_FS_48K;
		अवरोध;
	हाल 88200:
		avs.avs_audio_rate = PS3AV_CMD_AUDIO_FS_88K;
		अवरोध;
	हाल 96000:
		avs.avs_audio_rate = PS3AV_CMD_AUDIO_FS_96K;
		अवरोध;
	शेष:
		pr_info("%s: invalid rate %d\n", __func__,
			substream->runसमय->rate);
		वापस 1;
	पूर्ण

	/* width */
	चयन (snd_pcm_क्रमmat_width(substream->runसमय->क्रमmat)) अणु
	हाल 16:
		avs.avs_audio_width = PS3AV_CMD_AUDIO_WORD_BITS_16;
		अवरोध;
	हाल 24:
		avs.avs_audio_width = PS3AV_CMD_AUDIO_WORD_BITS_24;
		अवरोध;
	शेष:
		pr_info("%s: invalid width %d\n", __func__,
			snd_pcm_क्रमmat_width(substream->runसमय->क्रमmat));
		वापस 1;
	पूर्ण

	स_नकल(avs.avs_cs_info, ps3av_mode_cs_info, 8);

	अगर (स_भेद(&card->avs, &avs, माप(avs))) अणु
		pr_debug("%s: after freq=%d width=%d\n", __func__,
			 card->avs.avs_audio_rate, card->avs.avs_audio_width);

		card->avs = avs;
		snd_ps3_change_avsetting(card);
		ret = 0;
	पूर्ण अन्यथा
		ret = 1;

	/* check CS non-audio bit and mute accordingly */
	अगर (avs.avs_cs_info[0] & 0x02)
		ps3av_audio_mute_analog(1); /* mute अगर non-audio */
	अन्यथा
		ps3av_audio_mute_analog(0);

	वापस ret;
पूर्ण

/*
 * PCM चालकs
 */
अटल पूर्णांक snd_ps3_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ps3_card_info *card = snd_pcm_substream_chip(substream);

	/* to retrieve substream/runसमय in पूर्णांकerrupt handler */
	card->substream = substream;

	runसमय->hw = snd_ps3_pcm_hw;

	card->start_delay = snd_ps3_start_delay;

	/* mute off */
	snd_ps3_mute(0); /* this function sleep */

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   PS3_AUDIO_FIFO_STAGE_SIZE * 4 * 2);
	वापस 0;
पूर्ण;

अटल पूर्णांक snd_ps3_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	/* mute on */
	snd_ps3_mute(1);
	वापस 0;
पूर्ण;

अटल पूर्णांक snd_ps3_delay_to_bytes(काष्ठा snd_pcm_substream *substream,
				  अचिन्हित पूर्णांक delay_ms)
अणु
	पूर्णांक ret;
	पूर्णांक rate ;

	rate = substream->runसमय->rate;
	ret = snd_pcm_क्रमmat_size(substream->runसमय->क्रमmat,
				  rate * delay_ms / 1000)
		* substream->runसमय->channels;

	pr_debug("%s: time=%d rate=%d bytes=%ld, frames=%d, ret=%d\n",
		 __func__,
		 delay_ms,
		 rate,
		 snd_pcm_क्रमmat_size(substream->runसमय->क्रमmat, rate),
		 rate * delay_ms / 1000,
		 ret);

	वापस ret;
पूर्ण;

अटल पूर्णांक snd_ps3_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ps3_card_info *card = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ irqsave;

	अगर (!snd_ps3_set_avsetting(substream)) अणु
		/* some parameter changed */
		ग_लिखो_reg(PS3_AUDIO_AX_IE,
			  PS3_AUDIO_AX_IE_ASOBEIE(0) |
			  PS3_AUDIO_AX_IE_ASOBUIE(0));
		/*
		 * let SPDIF device re-lock with SPDIF संकेत,
		 * start with some silence
		 */
		card->silent = snd_ps3_delay_to_bytes(substream,
						      card->start_delay) /
			(PS3_AUDIO_FIFO_STAGE_SIZE * 4); /* every 4 बार */
	पूर्ण

	/* restart ring buffer poपूर्णांकer */
	spin_lock_irqsave(&card->dma_lock, irqsave);
	अणु
		card->dma_buffer_size = runसमय->dma_bytes;

		card->dma_last_transfer_vaddr[SND_PS3_CH_L] =
			card->dma_next_transfer_vaddr[SND_PS3_CH_L] =
			card->dma_start_vaddr[SND_PS3_CH_L] =
			runसमय->dma_area;
		card->dma_start_bus_addr[SND_PS3_CH_L] = runसमय->dma_addr;

		card->dma_last_transfer_vaddr[SND_PS3_CH_R] =
			card->dma_next_transfer_vaddr[SND_PS3_CH_R] =
			card->dma_start_vaddr[SND_PS3_CH_R] =
			runसमय->dma_area + (runसमय->dma_bytes / 2);
		card->dma_start_bus_addr[SND_PS3_CH_R] =
			runसमय->dma_addr + (runसमय->dma_bytes / 2);

		pr_debug("%s: vaddr=%p bus=%#llx\n", __func__,
			 card->dma_start_vaddr[SND_PS3_CH_L],
			 card->dma_start_bus_addr[SND_PS3_CH_L]);

	पूर्ण
	spin_unlock_irqrestore(&card->dma_lock, irqsave);

	/* ensure the hardware sees the change */
	mb();

	वापस 0;
पूर्ण;

अटल पूर्णांक snd_ps3_pcm_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd)
अणु
	काष्ठा snd_ps3_card_info *card = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* clear outstanding पूर्णांकerrupts  */
		update_reg(PS3_AUDIO_AX_IS, 0);

		spin_lock(&card->dma_lock);
		अणु
			card->running = 1;
		पूर्ण
		spin_unlock(&card->dma_lock);

		snd_ps3_program_dma(card,
				    SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL);
		snd_ps3_kick_dma(card);
		जबतक (पढ़ो_reg(PS3_AUDIO_KICK(7)) &
		       PS3_AUDIO_KICK_STATUS_MASK) अणु
			udelay(1);
		पूर्ण
		snd_ps3_program_dma(card, SND_PS3_DMA_FILLTYPE_SILENT_RUNNING);
		snd_ps3_kick_dma(card);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		spin_lock(&card->dma_lock);
		अणु
			card->running = 0;
		पूर्ण
		spin_unlock(&card->dma_lock);
		snd_ps3_रुको_क्रम_dma_stop(card);
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण;

/*
 * report current poपूर्णांकer
 */
अटल snd_pcm_uframes_t snd_ps3_pcm_poपूर्णांकer(
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ps3_card_info *card = snd_pcm_substream_chip(substream);
	माप_प्रकार bytes;
	snd_pcm_uframes_t ret;

	spin_lock(&card->dma_lock);
	अणु
		bytes = (माप_प्रकार)(card->dma_last_transfer_vaddr[SND_PS3_CH_L] -
				 card->dma_start_vaddr[SND_PS3_CH_L]);
	पूर्ण
	spin_unlock(&card->dma_lock);

	ret = bytes_to_frames(substream->runसमय, bytes * 2);

	वापस ret;
पूर्ण;

/*
 * SPDIF status bits controls
 */
अटल पूर्णांक snd_ps3_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

/* FIXME: ps3av_set_audio_mode() assumes only consumer mode */
अटल पूर्णांक snd_ps3_spdअगर_cmask_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xff, 8);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ps3_spdअगर_pmask_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ps3_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_नकल(ucontrol->value.iec958.status, ps3av_mode_cs_info, 8);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ps3_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अगर (स_भेद(ps3av_mode_cs_info, ucontrol->value.iec958.status, 8)) अणु
		स_नकल(ps3av_mode_cs_info, ucontrol->value.iec958.status, 8);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_ctls[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
		.info = snd_ps3_spdअगर_mask_info,
		.get = snd_ps3_spdअगर_cmask_get,
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, PRO_MASK),
		.info = snd_ps3_spdअगर_mask_info,
		.get = snd_ps3_spdअगर_pmask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = snd_ps3_spdअगर_mask_info,
		.get = snd_ps3_spdअगर_शेष_get,
		.put = snd_ps3_spdअगर_शेष_put,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ps3_pcm_spdअगर_ops = अणु
	.खोलो = snd_ps3_pcm_खोलो,
	.बंद = snd_ps3_pcm_बंद,
	.prepare = snd_ps3_pcm_prepare,
	.trigger = snd_ps3_pcm_trigger,
	.poपूर्णांकer = snd_ps3_pcm_poपूर्णांकer,
पूर्ण;


अटल पूर्णांक snd_ps3_map_mmio(व्योम)
अणु
	the_card.mapped_mmio_vaddr =
		ioremap(the_card.ps3_dev->m_region->bus_addr,
			the_card.ps3_dev->m_region->len);

	अगर (!the_card.mapped_mmio_vaddr) अणु
		pr_info("%s: ioremap 0 failed p=%#lx l=%#lx \n",
		       __func__, the_card.ps3_dev->m_region->lpar_addr,
		       the_card.ps3_dev->m_region->len);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण;

अटल व्योम snd_ps3_unmap_mmio(व्योम)
अणु
	iounmap(the_card.mapped_mmio_vaddr);
	the_card.mapped_mmio_vaddr = शून्य;
पूर्ण

अटल पूर्णांक snd_ps3_allocate_irq(व्योम)
अणु
	पूर्णांक ret;
	u64 lpar_addr, lpar_size;
	u64 __iomem *mapped;

	/* FIXME: move this to device_init (H/W probe) */

	/* get irq outlet */
	ret = lv1_gpu_device_map(1, &lpar_addr, &lpar_size);
	अगर (ret) अणु
		pr_info("%s: device map 1 failed %d\n", __func__,
			ret);
		वापस -ENXIO;
	पूर्ण

	mapped = ioremap(lpar_addr, lpar_size);
	अगर (!mapped) अणु
		pr_info("%s: ioremap 1 failed \n", __func__);
		वापस -ENXIO;
	पूर्ण

	the_card.audio_irq_outlet = in_be64(mapped);

	iounmap(mapped);
	ret = lv1_gpu_device_unmap(1);
	अगर (ret)
		pr_info("%s: unmap 1 failed\n", __func__);

	/* irq */
	ret = ps3_irq_plug_setup(PS3_BINDING_CPU_ANY,
				 the_card.audio_irq_outlet,
				 &the_card.irq_no);
	अगर (ret) अणु
		pr_info("%s:ps3_alloc_irq failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = request_irq(the_card.irq_no, snd_ps3_पूर्णांकerrupt, 0,
			  SND_PS3_DRIVER_NAME, &the_card);
	अगर (ret) अणु
		pr_info("%s: request_irq failed (%d)\n", __func__, ret);
		जाओ cleanup_irq;
	पूर्ण

	वापस 0;

 cleanup_irq:
	ps3_irq_plug_destroy(the_card.irq_no);
	वापस ret;
पूर्ण;

अटल व्योम snd_ps3_मुक्त_irq(व्योम)
अणु
	मुक्त_irq(the_card.irq_no, &the_card);
	ps3_irq_plug_destroy(the_card.irq_no);
पूर्ण

अटल व्योम snd_ps3_audio_set_base_addr(uपूर्णांक64_t ioaddr_start)
अणु
	uपूर्णांक64_t val;
	पूर्णांक ret;

	val = (ioaddr_start & (0x0fUL << 32)) >> (32 - 20) |
		(0x03UL << 24) |
		(0x0fUL << 12) |
		(PS3_AUDIO_IOID);

	ret = lv1_gpu_attribute(0x100, 0x007, val);
	अगर (ret)
		pr_info("%s: gpu_attribute failed %d\n", __func__,
			ret);
पूर्ण

अटल व्योम snd_ps3_audio_fixup(काष्ठा snd_ps3_card_info *card)
अणु
	/*
	 * avsetting driver seems to never change the following
	 * so, init them here once
	 */

	/* no dma पूर्णांकerrupt needed */
	ग_लिखो_reg(PS3_AUDIO_INTR_EN_0, 0);

	/* use every 4 buffer empty पूर्णांकerrupt */
	update_mask_reg(PS3_AUDIO_AX_IC,
			PS3_AUDIO_AX_IC_AASOIMD_MASK,
			PS3_AUDIO_AX_IC_AASOIMD_EVERY4);

	/* enable 3wire घड़ीs */
	update_mask_reg(PS3_AUDIO_AO_3WMCTRL,
			~(PS3_AUDIO_AO_3WMCTRL_ASOBCLKD_DISABLED |
			  PS3_AUDIO_AO_3WMCTRL_ASOLRCKD_DISABLED),
			0);
	update_reg(PS3_AUDIO_AO_3WMCTRL,
		   PS3_AUDIO_AO_3WMCTRL_ASOPLRCK_DEFAULT);
पूर्ण

अटल पूर्णांक snd_ps3_init_avsetting(काष्ठा snd_ps3_card_info *card)
अणु
	पूर्णांक ret;
	pr_debug("%s: start\n", __func__);
	card->avs.avs_audio_ch = PS3AV_CMD_AUDIO_NUM_OF_CH_2;
	card->avs.avs_audio_rate = PS3AV_CMD_AUDIO_FS_48K;
	card->avs.avs_audio_width = PS3AV_CMD_AUDIO_WORD_BITS_16;
	card->avs.avs_audio_क्रमmat = PS3AV_CMD_AUDIO_FORMAT_PCM;
	card->avs.avs_audio_source = PS3AV_CMD_AUDIO_SOURCE_SERIAL;
	स_नकल(card->avs.avs_cs_info, ps3av_mode_cs_info, 8);

	ret = snd_ps3_change_avsetting(card);

	snd_ps3_audio_fixup(card);

	/* to start to generate SPDIF संकेत, fill data */
	snd_ps3_program_dma(card, SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL);
	snd_ps3_kick_dma(card);
	pr_debug("%s: end\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_ps3_driver_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक i, ret;
	u64 lpar_addr, lpar_size;
	अटल u64 dummy_mask;

	the_card.ps3_dev = dev;

	ret = ps3_खोलो_hv_device(dev);

	अगर (ret)
		वापस -ENXIO;

	/* setup MMIO */
	ret = lv1_gpu_device_map(2, &lpar_addr, &lpar_size);
	अगर (ret) अणु
		pr_info("%s: device map 2 failed %d\n", __func__, ret);
		जाओ clean_खोलो;
	पूर्ण
	ps3_mmio_region_init(dev, dev->m_region, lpar_addr, lpar_size,
		PAGE_SHIFT);

	ret = snd_ps3_map_mmio();
	अगर (ret)
		जाओ clean_dev_map;

	/* setup DMA area */
	ps3_dma_region_init(dev, dev->d_region,
			    PAGE_SHIFT, /* use प्रणाली page size */
			    0, /* dma type; not used */
			    शून्य,
			    ALIGN(SND_PS3_DMA_REGION_SIZE, PAGE_SIZE));
	dev->d_region->ioid = PS3_AUDIO_IOID;

	ret = ps3_dma_region_create(dev->d_region);
	अगर (ret) अणु
		pr_info("%s: region_create\n", __func__);
		जाओ clean_mmio;
	पूर्ण

	dummy_mask = DMA_BIT_MASK(32);
	dev->core.dma_mask = &dummy_mask;
	dma_set_coherent_mask(&dev->core, dummy_mask);

	snd_ps3_audio_set_base_addr(dev->d_region->bus_addr);

	/* CONFIG_SND_PS3_DEFAULT_START_DELAY */
	the_card.start_delay = snd_ps3_start_delay;

	/* irq */
	अगर (snd_ps3_allocate_irq()) अणु
		ret = -ENXIO;
		जाओ clean_dma_region;
	पूर्ण

	/* create card instance */
	ret = snd_card_new(&dev->core, index, id, THIS_MODULE,
			   0, &the_card.card);
	अगर (ret < 0)
		जाओ clean_irq;

	म_नकल(the_card.card->driver, "PS3");
	म_नकल(the_card.card->लघुname, "PS3");
	म_नकल(the_card.card->दीर्घname, "PS3 sound");

	/* create control elements */
	क्रम (i = 0; i < ARRAY_SIZE(spdअगर_ctls); i++) अणु
		ret = snd_ctl_add(the_card.card,
				  snd_ctl_new1(&spdअगर_ctls[i], &the_card));
		अगर (ret < 0)
			जाओ clean_card;
	पूर्ण

	/* create PCM devices instance */
	/* NOTE:this driver works assuming pcm:substream = 1:1 */
	ret = snd_pcm_new(the_card.card,
			  "SPDIF",
			  0, /* instance index, will be stored pcm.device*/
			  1, /* output substream */
			  0, /* input substream */
			  &(the_card.pcm));
	अगर (ret)
		जाओ clean_card;

	the_card.pcm->निजी_data = &the_card;
	म_नकल(the_card.pcm->name, "SPDIF");

	/* set pcm ops */
	snd_pcm_set_ops(the_card.pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_ps3_pcm_spdअगर_ops);

	the_card.pcm->info_flags = SNDRV_PCM_INFO_NONINTERLEAVED;
	/* pre-alloc PCM DMA buffer*/
	snd_pcm_set_managed_buffer_all(the_card.pcm,
				       SNDRV_DMA_TYPE_DEV,
				       &dev->core,
				       SND_PS3_PCM_PREALLOC_SIZE,
				       SND_PS3_PCM_PREALLOC_SIZE);

	/*
	 * allocate null buffer
	 * its size should be lager than PS3_AUDIO_FIFO_STAGE_SIZE * 2
	 * PAGE_SIZE is enogh
	 */
	the_card.null_buffer_start_vaddr =
		dma_alloc_coherent(&the_card.ps3_dev->core,
				   PAGE_SIZE,
				   &the_card.null_buffer_start_dma_addr,
				   GFP_KERNEL);
	अगर (!the_card.null_buffer_start_vaddr) अणु
		pr_info("%s: nullbuffer alloc failed\n", __func__);
		ret = -ENOMEM;
		जाओ clean_card;
	पूर्ण
	pr_debug("%s: null vaddr=%p dma=%#llx\n", __func__,
		 the_card.null_buffer_start_vaddr,
		 the_card.null_buffer_start_dma_addr);
	/* set शेष sample rate/word width */
	snd_ps3_init_avsetting(&the_card);

	/* रेजिस्टर the card */
	ret = snd_card_रेजिस्टर(the_card.card);
	अगर (ret < 0)
		जाओ clean_dma_map;

	pr_info("%s started. start_delay=%dms\n",
		the_card.card->दीर्घname, the_card.start_delay);
	वापस 0;

clean_dma_map:
	dma_मुक्त_coherent(&the_card.ps3_dev->core,
			  PAGE_SIZE,
			  the_card.null_buffer_start_vaddr,
			  the_card.null_buffer_start_dma_addr);
clean_card:
	snd_card_मुक्त(the_card.card);
clean_irq:
	snd_ps3_मुक्त_irq();
clean_dma_region:
	ps3_dma_region_मुक्त(dev->d_region);
clean_mmio:
	snd_ps3_unmap_mmio();
clean_dev_map:
	lv1_gpu_device_unmap(2);
clean_खोलो:
	ps3_बंद_hv_device(dev);
	/*
	 * there is no deकाष्ठाor function to pcm.
	 * midlayer स्वतःmatically releases अगर the card हटाओd
	 */
	वापस ret;
पूर्ण; /* snd_ps3_probe */

/* called when module removal */
अटल व्योम snd_ps3_driver_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक ret;
	pr_info("%s:start id=%d\n", __func__,  dev->match_id);

	/*
	 * ctl and pपुनः_स्मृतिate buffer will be मुक्तd in
	 * snd_card_मुक्त
	 */
	ret = snd_card_मुक्त(the_card.card);
	अगर (ret)
		pr_info("%s: ctl freecard=%d\n", __func__, ret);

	dma_मुक्त_coherent(&dev->core,
			  PAGE_SIZE,
			  the_card.null_buffer_start_vaddr,
			  the_card.null_buffer_start_dma_addr);

	ps3_dma_region_मुक्त(dev->d_region);

	snd_ps3_मुक्त_irq();
	snd_ps3_unmap_mmio();

	lv1_gpu_device_unmap(2);
	ps3_बंद_hv_device(dev);
	pr_info("%s:end id=%d\n", __func__, dev->match_id);
पूर्ण /* snd_ps3_हटाओ */

अटल काष्ठा ps3_प्रणाली_bus_driver snd_ps3_bus_driver_info = अणु
	.match_id = PS3_MATCH_ID_SOUND,
	.probe = snd_ps3_driver_probe,
	.हटाओ = snd_ps3_driver_हटाओ,
	.shutकरोwn = snd_ps3_driver_हटाओ,
	.core = अणु
		.name = SND_PS3_DRIVER_NAME,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;


/*
 * module/subप्रणाली initialize/terminate
 */
अटल पूर्णांक __init snd_ps3_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENXIO;

	स_रखो(&the_card, 0, माप(the_card));
	spin_lock_init(&the_card.dma_lock);

	/* रेजिस्टर प्रणालीbus DRIVER, this calls our probe() func */
	ret = ps3_प्रणाली_bus_driver_रेजिस्टर(&snd_ps3_bus_driver_info);

	वापस ret;
पूर्ण
module_init(snd_ps3_init);

अटल व्योम __निकास snd_ps3_निकास(व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&snd_ps3_bus_driver_info);
पूर्ण
module_निकास(snd_ps3_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PS3 sound driver");
MODULE_AUTHOR("Sony Computer Entertainment Inc.");
MODULE_ALIAS(PS3_MODULE_ALIAS_SOUND);
