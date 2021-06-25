<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम SiS7019 Audio Accelerator
 *
 *  Copyright (C) 2004-2007, David Dillow
 *  Written by David Dillow <dave@thedillows.org>
 *  Inspired by the Trident 4D-WaveDX/NX driver.
 *
 *  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश "sis7019.h"

MODULE_AUTHOR("David Dillow <dave@thedillows.org>");
MODULE_DESCRIPTION("SiS7019");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल bool enable = 1;
अटल पूर्णांक codecs = 1;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for SiS7019 Audio Accelerator.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for SiS7019 Audio Accelerator.");
module_param(enable, bool, 0444);
MODULE_PARM_DESC(enable, "Enable SiS7019 Audio Accelerator.");
module_param(codecs, पूर्णांक, 0444);
MODULE_PARM_DESC(codecs, "Set bit to indicate that codec number is expected to be present (default 1)");

अटल स्थिर काष्ठा pci_device_id snd_sis7019_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, 0x7019) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_sis7019_ids);

/* There are three timing modes क्रम the voices.
 *
 * For both playback and capture, when the buffer is one or two periods दीर्घ,
 * we use the hardware's built-in Mid-Loop Interrupt and End-Loop Interrupt
 * to let us know when the periods have ended.
 *
 * When perक्रमming playback with more than two periods per buffer, we set
 * the "Stop Sample Offset" and tell the hardware to पूर्णांकerrupt us when we
 * reach it. We then update the offset and जारी on until we are
 * पूर्णांकerrupted क्रम the next period.
 *
 * Capture channels करो not have a SSO, so we allocate a playback channel to
 * use as a समयr क्रम the capture periods. We use the SSO on the playback
 * channel to घड़ी out भव periods, and adjust the भव period length
 * to मुख्यtain synchronization. This algorithm came from the Trident driver.
 *
 * FIXME: It'd be nice to make use of some of the synth features in the
 * hardware, but a woeful lack of करोcumentation is a signअगरicant roadblock.
 */
काष्ठा voice अणु
	u16 flags;
#घोषणा 	VOICE_IN_USE		1
#घोषणा 	VOICE_CAPTURE		2
#घोषणा 	VOICE_SSO_TIMING	4
#घोषणा 	VOICE_SYNC_TIMING	8
	u16 sync_cso;
	u16 period_size;
	u16 buffer_size;
	u16 sync_period_size;
	u16 sync_buffer_size;
	u32 sso;
	u32 vperiod;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा voice *timing;
	व्योम __iomem *ctrl_base;
	व्योम __iomem *wave_base;
	व्योम __iomem *sync_base;
	पूर्णांक num;
पूर्ण;

/* We need four pages to store our wave parameters during a suspend. If
 * we're not करोing घातer management, we still need to allocate a page
 * क्रम the silence buffer.
 */
#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा SIS_SUSPEND_PAGES	4
#अन्यथा
#घोषणा SIS_SUSPEND_PAGES	1
#पूर्ण_अगर

काष्ठा sis7019 अणु
	अचिन्हित दीर्घ ioport;
	व्योम __iomem *ioaddr;
	पूर्णांक irq;
	पूर्णांक codecs_present;

	काष्ठा pci_dev *pci;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_card *card;
	काष्ठा snd_ac97 *ac97[3];

	/* Protect against more than one thपढ़ो hitting the AC97
	 * रेजिस्टरs (in a more polite manner than pounding the hardware
	 * semaphore)
	 */
	काष्ठा mutex ac97_mutex;

	/* voice_lock protects allocation/मुक्तing of the voice descriptions
	 */
	spinlock_t voice_lock;

	काष्ठा voice voices[64];
	काष्ठा voice capture_voice;

	/* Allocate pages to store the पूर्णांकernal wave state during
	 * suspends. When we're operating, this can be used as a silence
	 * buffer क्रम a timing channel.
	 */
	व्योम *suspend_state[SIS_SUSPEND_PAGES];

	पूर्णांक silence_users;
	dma_addr_t silence_dma_addr;
पूर्ण;

/* These values are also used by the module param 'codecs' to indicate
 * which codecs should be present.
 */
#घोषणा SIS_PRIMARY_CODEC_PRESENT	0x0001
#घोषणा SIS_SECONDARY_CODEC_PRESENT	0x0002
#घोषणा SIS_TERTIARY_CODEC_PRESENT	0x0004

/* The HW offset parameters (Loop End, Stop Sample, End Sample) have a
 * करोcumented range of 8-0xfff8 samples. Given that they are 0-based,
 * that places our period/buffer range at 9-0xfff9 samples. That makes the
 * max buffer size 0xfff9 samples * 2 channels * 2 bytes per sample, and
 * max samples / min samples gives us the max periods in a buffer.
 *
 * We'll add a स्थिरraपूर्णांक upon खोलो that limits the period and buffer sample
 * size to values that are legal क्रम the hardware.
 */
अटल स्थिर काष्ठा snd_pcm_hardware sis_playback_hw_info = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_SYNC_START |
		 SNDRV_PCM_INFO_RESUME),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
		    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE),
	.rates = SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 4000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = (0xfff9 * 4),
	.period_bytes_min = 9,
	.period_bytes_max = (0xfff9 * 4),
	.periods_min = 1,
	.periods_max = (0xfff9 / 9),
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sis_capture_hw_info = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_SYNC_START |
		 SNDRV_PCM_INFO_RESUME),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
		    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE),
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 4000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = (0xfff9 * 4),
	.period_bytes_min = 9,
	.period_bytes_max = (0xfff9 * 4),
	.periods_min = 1,
	.periods_max = (0xfff9 / 9),
पूर्ण;

अटल व्योम sis_update_sso(काष्ठा voice *voice, u16 period)
अणु
	व्योम __iomem *base = voice->ctrl_base;

	voice->sso += period;
	अगर (voice->sso >= voice->buffer_size)
		voice->sso -= voice->buffer_size;

	/* Enक्रमce the करोcumented hardware minimum offset */
	अगर (voice->sso < 8)
		voice->sso = 8;

	/* The SSO is in the upper 16 bits of the रेजिस्टर. */
	ग_लिखोw(voice->sso & 0xffff, base + SIS_PLAY_DMA_SSO_ESO + 2);
पूर्ण

अटल व्योम sis_update_voice(काष्ठा voice *voice)
अणु
	अगर (voice->flags & VOICE_SSO_TIMING) अणु
		sis_update_sso(voice, voice->period_size);
	पूर्ण अन्यथा अगर (voice->flags & VOICE_SYNC_TIMING) अणु
		पूर्णांक sync;

		/* If we've not hit the end of the भव period, update
		 * our records and keep going.
		 */
		अगर (voice->vperiod > voice->period_size) अणु
			voice->vperiod -= voice->period_size;
			अगर (voice->vperiod < voice->period_size)
				sis_update_sso(voice, voice->vperiod);
			अन्यथा
				sis_update_sso(voice, voice->period_size);
			वापस;
		पूर्ण

		/* Calculate our relative offset between the target and
		 * the actual CSO value. Since we're operating in a loop,
		 * अगर the value is more than half way around, we can
		 * consider ourselves wrapped.
		 */
		sync = voice->sync_cso;
		sync -= पढ़ोw(voice->sync_base + SIS_CAPTURE_DMA_FORMAT_CSO);
		अगर (sync > (voice->sync_buffer_size / 2))
			sync -= voice->sync_buffer_size;

		/* If sync is positive, then we पूर्णांकerrupted too early, and
		 * we'll need to come back in a few samples and try again.
		 * There's a minimum रुको, as it takes some समय क्रम the DMA
		 * engine to startup, etc...
		 */
		अगर (sync > 0) अणु
			अगर (sync < 16)
				sync = 16;
			sis_update_sso(voice, sync);
			वापस;
		पूर्ण

		/* Ok, we पूर्णांकerrupted right on समय, or (hopefully) just
		 * a bit late. We'll adjst our next रुकोing period based
		 * on how बंद we got.
		 *
		 * We need to stay just behind the actual channel to ensure
		 * it really is past a period when we get our पूर्णांकerrupt --
		 * otherwise we'll fall पूर्णांकo the early code above and have
		 * a minimum रुको समय, which makes us quite late here,
		 * eating पूर्णांकo the user's समय to refresh the buffer, esp.
		 * अगर using small periods.
		 *
		 * If we're less than 9 samples behind, we're on target.
		 * Otherwise, लघुen the next vperiod by the amount we've
		 * been delayed.
		 */
		अगर (sync > -9)
			voice->vperiod = voice->sync_period_size + 1;
		अन्यथा
			voice->vperiod = voice->sync_period_size + sync + 10;

		अगर (voice->vperiod < voice->buffer_size) अणु
			sis_update_sso(voice, voice->vperiod);
			voice->vperiod = 0;
		पूर्ण अन्यथा
			sis_update_sso(voice, voice->period_size);

		sync = voice->sync_cso + voice->sync_period_size;
		अगर (sync >= voice->sync_buffer_size)
			sync -= voice->sync_buffer_size;
		voice->sync_cso = sync;
	पूर्ण

	snd_pcm_period_elapsed(voice->substream);
पूर्ण

अटल व्योम sis_voice_irq(u32 status, काष्ठा voice *voice)
अणु
	पूर्णांक bit;

	जबतक (status) अणु
		bit = __ffs(status);
		status >>= bit + 1;
		voice += bit;
		sis_update_voice(voice);
		voice++;
	पूर्ण
पूर्ण

अटल irqवापस_t sis_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा sis7019 *sis = dev;
	अचिन्हित दीर्घ io = sis->ioport;
	काष्ठा voice *voice;
	u32 पूर्णांकr, status;

	/* We only use the DMA पूर्णांकerrupts, and we करोn't enable any other
	 * source of पूर्णांकerrupts. But, it is possible to see an पूर्णांकerrupt
	 * status that didn't actually पूर्णांकerrupt us, so eliminate anything
	 * we're not expecting to aव्योम falsely claiming an IRQ, and an
	 * ensuing endless loop.
	 */
	पूर्णांकr = inl(io + SIS_GISR);
	पूर्णांकr &= SIS_GISR_AUDIO_PLAY_DMA_IRQ_STATUS |
		SIS_GISR_AUDIO_RECORD_DMA_IRQ_STATUS;
	अगर (!पूर्णांकr)
		वापस IRQ_NONE;

	करो अणु
		status = inl(io + SIS_PISR_A);
		अगर (status) अणु
			sis_voice_irq(status, sis->voices);
			outl(status, io + SIS_PISR_A);
		पूर्ण

		status = inl(io + SIS_PISR_B);
		अगर (status) अणु
			sis_voice_irq(status, &sis->voices[32]);
			outl(status, io + SIS_PISR_B);
		पूर्ण

		status = inl(io + SIS_RISR);
		अगर (status) अणु
			voice = &sis->capture_voice;
			अगर (!voice->timing)
				snd_pcm_period_elapsed(voice->substream);

			outl(status, io + SIS_RISR);
		पूर्ण

		outl(पूर्णांकr, io + SIS_GISR);
		पूर्णांकr = inl(io + SIS_GISR);
		पूर्णांकr &= SIS_GISR_AUDIO_PLAY_DMA_IRQ_STATUS |
			SIS_GISR_AUDIO_RECORD_DMA_IRQ_STATUS;
	पूर्ण जबतक (पूर्णांकr);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 sis_rate_to_delta(अचिन्हित पूर्णांक rate)
अणु
	u32 delta;

	/* This was copied from the trident driver, but it seems its gotten
	 * around a bit... nevertheless, it works well.
	 *
	 * We special हाल 44100 and 8000 since rounding with the equation
	 * करोes not give us an accurate enough value. For 11025 and 22050
	 * the equation gives us the best answer. All other frequencies will
	 * also use the equation. JDW
	 */
	अगर (rate == 44100)
		delta = 0xeb3;
	अन्यथा अगर (rate == 8000)
		delta = 0x2ab;
	अन्यथा अगर (rate == 48000)
		delta = 0x1000;
	अन्यथा
		delta = DIV_ROUND_CLOSEST(rate << 12, 48000) & 0x0000ffff;
	वापस delta;
पूर्ण

अटल व्योम __sis_map_silence(काष्ठा sis7019 *sis)
अणु
	/* Helper function: must hold sis->voice_lock on entry */
	अगर (!sis->silence_users)
		sis->silence_dma_addr = dma_map_single(&sis->pci->dev,
						sis->suspend_state[0],
						4096, DMA_TO_DEVICE);
	sis->silence_users++;
पूर्ण

अटल व्योम __sis_unmap_silence(काष्ठा sis7019 *sis)
अणु
	/* Helper function: must hold sis->voice_lock on entry */
	sis->silence_users--;
	अगर (!sis->silence_users)
		dma_unmap_single(&sis->pci->dev, sis->silence_dma_addr, 4096,
					DMA_TO_DEVICE);
पूर्ण

अटल व्योम sis_मुक्त_voice(काष्ठा sis7019 *sis, काष्ठा voice *voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sis->voice_lock, flags);
	अगर (voice->timing) अणु
		__sis_unmap_silence(sis);
		voice->timing->flags &= ~(VOICE_IN_USE | VOICE_SSO_TIMING |
						VOICE_SYNC_TIMING);
		voice->timing = शून्य;
	पूर्ण
	voice->flags &= ~(VOICE_IN_USE | VOICE_SSO_TIMING | VOICE_SYNC_TIMING);
	spin_unlock_irqrestore(&sis->voice_lock, flags);
पूर्ण

अटल काष्ठा voice *__sis_alloc_playback_voice(काष्ठा sis7019 *sis)
अणु
	/* Must hold the voice_lock on entry */
	काष्ठा voice *voice;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		voice = &sis->voices[i];
		अगर (voice->flags & VOICE_IN_USE)
			जारी;
		voice->flags |= VOICE_IN_USE;
		जाओ found_one;
	पूर्ण
	voice = शून्य;

found_one:
	वापस voice;
पूर्ण

अटल काष्ठा voice *sis_alloc_playback_voice(काष्ठा sis7019 *sis)
अणु
	काष्ठा voice *voice;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sis->voice_lock, flags);
	voice = __sis_alloc_playback_voice(sis);
	spin_unlock_irqrestore(&sis->voice_lock, flags);

	वापस voice;
पूर्ण

अटल पूर्णांक sis_alloc_timing_voice(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = runसमय->निजी_data;
	अचिन्हित पूर्णांक period_size, buffer_size;
	अचिन्हित दीर्घ flags;
	पूर्णांक needed;

	/* If there are one or two periods per buffer, we करोn't need a
	 * timing voice, as we can use the capture channel's पूर्णांकerrupts
	 * to घड़ी out the periods.
	 */
	period_size = params_period_size(hw_params);
	buffer_size = params_buffer_size(hw_params);
	needed = (period_size != buffer_size &&
			period_size != (buffer_size / 2));

	अगर (needed && !voice->timing) अणु
		spin_lock_irqsave(&sis->voice_lock, flags);
		voice->timing = __sis_alloc_playback_voice(sis);
		अगर (voice->timing)
			__sis_map_silence(sis);
		spin_unlock_irqrestore(&sis->voice_lock, flags);
		अगर (!voice->timing)
			वापस -ENOMEM;
		voice->timing->substream = substream;
	पूर्ण अन्यथा अगर (!needed && voice->timing) अणु
		sis_मुक्त_voice(sis, voice);
		voice->timing = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sis_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice;

	voice = sis_alloc_playback_voice(sis);
	अगर (!voice)
		वापस -EAGAIN;

	voice->substream = substream;
	runसमय->निजी_data = voice;
	runसमय->hw = sis_playback_hw_info;
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
						9, 0xfff9);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
						9, 0xfff9);
	snd_pcm_set_sync(substream);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_substream_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = runसमय->निजी_data;

	sis_मुक्त_voice(sis, voice);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = runसमय->निजी_data;
	व्योम __iomem *ctrl_base = voice->ctrl_base;
	व्योम __iomem *wave_base = voice->wave_base;
	u32 क्रमmat, dma_addr, control, sso_eso, delta, reg;
	u16 leo;

	/* We rely on the PCM core to ensure that the parameters क्रम this
	 * substream करो not change on us जबतक we're programming the HW.
	 */
	क्रमmat = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		क्रमmat |= SIS_PLAY_DMA_FORMAT_8BIT;
	अगर (!snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		क्रमmat |= SIS_PLAY_DMA_FORMAT_UNSIGNED;
	अगर (runसमय->channels == 1)
		क्रमmat |= SIS_PLAY_DMA_FORMAT_MONO;

	/* The baseline setup is क्रम a single period per buffer, and
	 * we add bells and whistles as needed from there.
	 */
	dma_addr = runसमय->dma_addr;
	leo = runसमय->buffer_size - 1;
	control = leo | SIS_PLAY_DMA_LOOP | SIS_PLAY_DMA_INTR_AT_LEO;
	sso_eso = leo;

	अगर (runसमय->period_size == (runसमय->buffer_size / 2)) अणु
		control |= SIS_PLAY_DMA_INTR_AT_MLP;
	पूर्ण अन्यथा अगर (runसमय->period_size != runसमय->buffer_size) अणु
		voice->flags |= VOICE_SSO_TIMING;
		voice->sso = runसमय->period_size - 1;
		voice->period_size = runसमय->period_size;
		voice->buffer_size = runसमय->buffer_size;

		control &= ~SIS_PLAY_DMA_INTR_AT_LEO;
		control |= SIS_PLAY_DMA_INTR_AT_SSO;
		sso_eso |= (runसमय->period_size - 1) << 16;
	पूर्ण

	delta = sis_rate_to_delta(runसमय->rate);

	/* Ok, we're पढ़ोy to go, set up the channel.
	 */
	ग_लिखोl(क्रमmat, ctrl_base + SIS_PLAY_DMA_FORMAT_CSO);
	ग_लिखोl(dma_addr, ctrl_base + SIS_PLAY_DMA_BASE);
	ग_लिखोl(control, ctrl_base + SIS_PLAY_DMA_CONTROL);
	ग_लिखोl(sso_eso, ctrl_base + SIS_PLAY_DMA_SSO_ESO);

	क्रम (reg = 0; reg < SIS_WAVE_SIZE; reg += 4)
		ग_लिखोl(0, wave_base + reg);

	ग_लिखोl(SIS_WAVE_GENERAL_WAVE_VOLUME, wave_base + SIS_WAVE_GENERAL);
	ग_लिखोl(delta << 16, wave_base + SIS_WAVE_GENERAL_ARTICULATION);
	ग_लिखोl(SIS_WAVE_CHANNEL_CONTROL_FIRST_SAMPLE |
			SIS_WAVE_CHANNEL_CONTROL_AMP_ENABLE |
			SIS_WAVE_CHANNEL_CONTROL_INTERPOLATE_ENABLE,
			wave_base + SIS_WAVE_CHANNEL_CONTROL);

	/* Force PCI ग_लिखोs to post. */
	पढ़ोl(ctrl_base);

	वापस 0;
पूर्ण

अटल पूर्णांक sis_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ io = sis->ioport;
	काष्ठा snd_pcm_substream *s;
	काष्ठा voice *voice;
	व्योम *chip;
	पूर्णांक starting;
	u32 record = 0;
	u32 play[2] = अणु 0, 0 पूर्ण;

	/* No locks needed, as the PCM core will hold the locks on the
	 * substreams, and the HW will only start/stop the indicated voices
	 * without changing the state of the others.
	 */
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		starting = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		starting = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		/* Make sure it is क्रम us... */
		chip = snd_pcm_substream_chip(s);
		अगर (chip != sis)
			जारी;

		voice = s->runसमय->निजी_data;
		अगर (voice->flags & VOICE_CAPTURE) अणु
			record |= 1 << voice->num;
			voice = voice->timing;
		पूर्ण

		/* voice could be शून्य अगर this a recording stream, and it
		 * करोesn't have an बाह्यal timing channel.
		 */
		अगर (voice)
			play[voice->num / 32] |= 1 << (voice->num & 0x1f);

		snd_pcm_trigger_करोne(s, substream);
	पूर्ण

	अगर (starting) अणु
		अगर (record)
			outl(record, io + SIS_RECORD_START_REG);
		अगर (play[0])
			outl(play[0], io + SIS_PLAY_START_A_REG);
		अगर (play[1])
			outl(play[1], io + SIS_PLAY_START_B_REG);
	पूर्ण अन्यथा अणु
		अगर (record)
			outl(record, io + SIS_RECORD_STOP_REG);
		अगर (play[0])
			outl(play[0], io + SIS_PLAY_STOP_A_REG);
		अगर (play[1])
			outl(play[1], io + SIS_PLAY_STOP_B_REG);
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t sis_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = runसमय->निजी_data;
	u32 cso;

	cso = पढ़ोl(voice->ctrl_base + SIS_PLAY_DMA_FORMAT_CSO);
	cso &= 0xffff;
	वापस cso;
पूर्ण

अटल पूर्णांक sis_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = &sis->capture_voice;
	अचिन्हित दीर्घ flags;

	/* FIXME: The driver only supports recording from one channel
	 * at the moment, but it could support more.
	 */
	spin_lock_irqsave(&sis->voice_lock, flags);
	अगर (voice->flags & VOICE_IN_USE)
		voice = शून्य;
	अन्यथा
		voice->flags |= VOICE_IN_USE;
	spin_unlock_irqrestore(&sis->voice_lock, flags);

	अगर (!voice)
		वापस -EAGAIN;

	voice->substream = substream;
	runसमय->निजी_data = voice;
	runसमय->hw = sis_capture_hw_info;
	runसमय->hw.rates = sis->ac97[0]->rates[AC97_RATES_ADC];
	snd_pcm_limit_hw_rates(runसमय);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
						9, 0xfff9);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
						9, 0xfff9);
	snd_pcm_set_sync(substream);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	पूर्णांक rc;

	rc = snd_ac97_set_rate(sis->ac97[0], AC97_PCM_LR_ADC_RATE,
						params_rate(hw_params));
	अगर (rc)
		जाओ out;

	rc = sis_alloc_timing_voice(substream, hw_params);

out:
	वापस rc;
पूर्ण

अटल व्योम sis_prepare_timing_voice(काष्ठा voice *voice,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sis7019 *sis = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *timing = voice->timing;
	व्योम __iomem *play_base = timing->ctrl_base;
	व्योम __iomem *wave_base = timing->wave_base;
	u16 buffer_size, period_size;
	u32 क्रमmat, control, sso_eso, delta;
	u32 vperiod, sso, reg;

	/* Set our initial buffer and period as large as we can given a
	 * single page of silence.
	 */
	buffer_size = 4096 / runसमय->channels;
	buffer_size /= snd_pcm_क्रमmat_size(runसमय->क्रमmat, 1);
	period_size = buffer_size;

	/* Initially, we want to पूर्णांकerrupt just a bit behind the end of
	 * the period we're घड़ीing out. 12 samples seems to give a good
	 * delay.
	 *
	 * We want to spपढ़ो our पूर्णांकerrupts throughout the भव period,
	 * so that we करोn't end up with two पूर्णांकerrupts back to back at the
	 * end -- this helps minimize the effects of any jitter. Adjust our
	 * घड़ीing period size so that the last period is at least a fourth
	 * of a full period.
	 *
	 * This is all moot अगर we करोn't need to use भव periods.
	 */
	vperiod = runसमय->period_size + 12;
	अगर (vperiod > period_size) अणु
		u16 tail = vperiod % period_size;
		u16 quarter_period = period_size / 4;

		अगर (tail && tail < quarter_period) अणु
			u16 loops = vperiod / period_size;

			tail = quarter_period - tail;
			tail += loops - 1;
			tail /= loops;
			period_size -= tail;
		पूर्ण

		sso = period_size - 1;
	पूर्ण अन्यथा अणु
		/* The initial period will fit inside the buffer, so we
		 * करोn't need to use भव periods -- disable them.
		 */
		period_size = runसमय->period_size;
		sso = vperiod - 1;
		vperiod = 0;
	पूर्ण

	/* The पूर्णांकerrupt handler implements the timing synchronization, so
	 * setup its state.
	 */
	timing->flags |= VOICE_SYNC_TIMING;
	timing->sync_base = voice->ctrl_base;
	timing->sync_cso = runसमय->period_size;
	timing->sync_period_size = runसमय->period_size;
	timing->sync_buffer_size = runसमय->buffer_size;
	timing->period_size = period_size;
	timing->buffer_size = buffer_size;
	timing->sso = sso;
	timing->vperiod = vperiod;

	/* Using अचिन्हित samples with the all-zero silence buffer
	 * क्रमces the output to the lower rail, समाप्तing playback.
	 * So ignore अचिन्हित vs चिन्हित -- it करोesn't change the timing.
	 */
	क्रमmat = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		क्रमmat = SIS_CAPTURE_DMA_FORMAT_8BIT;
	अगर (runसमय->channels == 1)
		क्रमmat |= SIS_CAPTURE_DMA_FORMAT_MONO;

	control = timing->buffer_size - 1;
	control |= SIS_PLAY_DMA_LOOP | SIS_PLAY_DMA_INTR_AT_SSO;
	sso_eso = timing->buffer_size - 1;
	sso_eso |= timing->sso << 16;

	delta = sis_rate_to_delta(runसमय->rate);

	/* We've करोne the math, now configure the channel.
	 */
	ग_लिखोl(क्रमmat, play_base + SIS_PLAY_DMA_FORMAT_CSO);
	ग_लिखोl(sis->silence_dma_addr, play_base + SIS_PLAY_DMA_BASE);
	ग_लिखोl(control, play_base + SIS_PLAY_DMA_CONTROL);
	ग_लिखोl(sso_eso, play_base + SIS_PLAY_DMA_SSO_ESO);

	क्रम (reg = 0; reg < SIS_WAVE_SIZE; reg += 4)
		ग_लिखोl(0, wave_base + reg);

	ग_लिखोl(SIS_WAVE_GENERAL_WAVE_VOLUME, wave_base + SIS_WAVE_GENERAL);
	ग_लिखोl(delta << 16, wave_base + SIS_WAVE_GENERAL_ARTICULATION);
	ग_लिखोl(SIS_WAVE_CHANNEL_CONTROL_FIRST_SAMPLE |
			SIS_WAVE_CHANNEL_CONTROL_AMP_ENABLE |
			SIS_WAVE_CHANNEL_CONTROL_INTERPOLATE_ENABLE,
			wave_base + SIS_WAVE_CHANNEL_CONTROL);
पूर्ण

अटल पूर्णांक sis_pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा voice *voice = runसमय->निजी_data;
	व्योम __iomem *rec_base = voice->ctrl_base;
	u32 क्रमmat, dma_addr, control;
	u16 leo;

	/* We rely on the PCM core to ensure that the parameters क्रम this
	 * substream करो not change on us जबतक we're programming the HW.
	 */
	क्रमmat = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		क्रमmat = SIS_CAPTURE_DMA_FORMAT_8BIT;
	अगर (!snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		क्रमmat |= SIS_CAPTURE_DMA_FORMAT_UNSIGNED;
	अगर (runसमय->channels == 1)
		क्रमmat |= SIS_CAPTURE_DMA_FORMAT_MONO;

	dma_addr = runसमय->dma_addr;
	leo = runसमय->buffer_size - 1;
	control = leo | SIS_CAPTURE_DMA_LOOP;

	/* If we've got more than two periods per buffer, then we have
	 * use a timing voice to घड़ी out the periods. Otherwise, we can
	 * use the capture channel's पूर्णांकerrupts.
	 */
	अगर (voice->timing) अणु
		sis_prepare_timing_voice(voice, substream);
	पूर्ण अन्यथा अणु
		control |= SIS_CAPTURE_DMA_INTR_AT_LEO;
		अगर (runसमय->period_size != runसमय->buffer_size)
			control |= SIS_CAPTURE_DMA_INTR_AT_MLP;
	पूर्ण

	ग_लिखोl(क्रमmat, rec_base + SIS_CAPTURE_DMA_FORMAT_CSO);
	ग_लिखोl(dma_addr, rec_base + SIS_CAPTURE_DMA_BASE);
	ग_लिखोl(control, rec_base + SIS_CAPTURE_DMA_CONTROL);

	/* Force the ग_लिखोs to post. */
	पढ़ोl(rec_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops sis_playback_ops = अणु
	.खोलो = sis_playback_खोलो,
	.बंद = sis_substream_बंद,
	.prepare = sis_pcm_playback_prepare,
	.trigger = sis_pcm_trigger,
	.poपूर्णांकer = sis_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops sis_capture_ops = अणु
	.खोलो = sis_capture_खोलो,
	.बंद = sis_substream_बंद,
	.hw_params = sis_capture_hw_params,
	.prepare = sis_pcm_capture_prepare,
	.trigger = sis_pcm_trigger,
	.poपूर्णांकer = sis_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक sis_pcm_create(काष्ठा sis7019 *sis)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक rc;

	/* We have 64 voices, and the driver currently records from
	 * only one channel, though that could change in the future.
	 */
	rc = snd_pcm_new(sis->card, "SiS7019", 0, 64, 1, &pcm);
	अगर (rc)
		वापस rc;

	pcm->निजी_data = sis;
	म_नकल(pcm->name, "SiS7019");
	sis->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &sis_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &sis_capture_ops);

	/* Try to pपुनः_स्मृतिate some memory, but it's not the end of the
	 * world अगर this fails.
	 */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &sis->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

अटल अचिन्हित लघु sis_ac97_rw(काष्ठा sis7019 *sis, पूर्णांक codec, u32 cmd)
अणु
	अचिन्हित दीर्घ io = sis->ioport;
	अचिन्हित लघु val = 0xffff;
	u16 status;
	u16 rdy;
	पूर्णांक count;
	अटल स्थिर u16 codec_पढ़ोy[3] = अणु
		SIS_AC97_STATUS_CODEC_READY,
		SIS_AC97_STATUS_CODEC2_READY,
		SIS_AC97_STATUS_CODEC3_READY,
	पूर्ण;

	rdy = codec_पढ़ोy[codec];


	/* Get the AC97 semaphore -- software first, so we करोn't spin
	 * pounding out IO पढ़ोs on the hardware semaphore...
	 */
	mutex_lock(&sis->ac97_mutex);

	count = 0xffff;
	जबतक ((inw(io + SIS_AC97_SEMA) & SIS_AC97_SEMA_BUSY) && --count)
		udelay(1);

	अगर (!count)
		जाओ समयout;

	/* ... and रुको क्रम any outstanding commands to complete ...
	 */
	count = 0xffff;
	करो अणु
		status = inw(io + SIS_AC97_STATUS);
		अगर ((status & rdy) && !(status & SIS_AC97_STATUS_BUSY))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--count);

	अगर (!count)
		जाओ समयout_sema;

	/* ... beक्रमe sending our command and रुकोing क्रम it to finish ...
	 */
	outl(cmd, io + SIS_AC97_CMD);
	udelay(10);

	count = 0xffff;
	जबतक ((inw(io + SIS_AC97_STATUS) & SIS_AC97_STATUS_BUSY) && --count)
		udelay(1);

	/* ... and पढ़ोing the results (अगर any).
	 */
	val = inl(io + SIS_AC97_CMD) >> 16;

समयout_sema:
	outl(SIS_AC97_SEMA_RELEASE, io + SIS_AC97_SEMA);
समयout:
	mutex_unlock(&sis->ac97_mutex);

	अगर (!count) अणु
		dev_err(&sis->pci->dev, "ac97 codec %d timeout cmd 0x%08x\n",
					codec, cmd);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम sis_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				अचिन्हित लघु val)
अणु
	अटल स्थिर u32 cmd[3] = अणु
		SIS_AC97_CMD_CODEC_WRITE,
		SIS_AC97_CMD_CODEC2_WRITE,
		SIS_AC97_CMD_CODEC3_WRITE,
	पूर्ण;
	sis_ac97_rw(ac97->निजी_data, ac97->num,
			(val << 16) | (reg << 8) | cmd[ac97->num]);
पूर्ण

अटल अचिन्हित लघु sis_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	अटल स्थिर u32 cmd[3] = अणु
		SIS_AC97_CMD_CODEC_READ,
		SIS_AC97_CMD_CODEC2_READ,
		SIS_AC97_CMD_CODEC3_READ,
	पूर्ण;
	वापस sis_ac97_rw(ac97->निजी_data, ac97->num,
					(reg << 8) | cmd[ac97->num]);
पूर्ण

अटल पूर्णांक sis_mixer_create(काष्ठा sis7019 *sis)
अणु
	काष्ठा snd_ac97_bus *bus;
	काष्ठा snd_ac97_ढाँचा ac97;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = sis_ac97_ग_लिखो,
		.पढ़ो = sis_ac97_पढ़ो,
	पूर्ण;
	पूर्णांक rc;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = sis;

	rc = snd_ac97_bus(sis->card, 0, &ops, शून्य, &bus);
	अगर (!rc && sis->codecs_present & SIS_PRIMARY_CODEC_PRESENT)
		rc = snd_ac97_mixer(bus, &ac97, &sis->ac97[0]);
	ac97.num = 1;
	अगर (!rc && (sis->codecs_present & SIS_SECONDARY_CODEC_PRESENT))
		rc = snd_ac97_mixer(bus, &ac97, &sis->ac97[1]);
	ac97.num = 2;
	अगर (!rc && (sis->codecs_present & SIS_TERTIARY_CODEC_PRESENT))
		rc = snd_ac97_mixer(bus, &ac97, &sis->ac97[2]);

	/* If we वापस an error here, then snd_card_मुक्त() should
	 * मुक्त up any ac97 codecs that got created, as well as the bus.
	 */
	वापस rc;
पूर्ण

अटल व्योम sis_मुक्त_suspend(काष्ठा sis7019 *sis)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SIS_SUSPEND_PAGES; i++)
		kमुक्त(sis->suspend_state[i]);
पूर्ण

अटल पूर्णांक sis_chip_मुक्त(काष्ठा sis7019 *sis)
अणु
	/* Reset the chip, and disable all पूर्णांकerrमाला_दो.
	 */
	outl(SIS_GCR_SOFTWARE_RESET, sis->ioport + SIS_GCR);
	udelay(25);
	outl(0, sis->ioport + SIS_GCR);
	outl(0, sis->ioport + SIS_GIER);

	/* Now, मुक्त everything we allocated.
	 */
	अगर (sis->irq >= 0)
		मुक्त_irq(sis->irq, sis);

	iounmap(sis->ioaddr);
	pci_release_regions(sis->pci);
	pci_disable_device(sis->pci);
	sis_मुक्त_suspend(sis);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_dev_मुक्त(काष्ठा snd_device *dev)
अणु
	काष्ठा sis7019 *sis = dev->device_data;
	वापस sis_chip_मुक्त(sis);
पूर्ण

अटल पूर्णांक sis_chip_init(काष्ठा sis7019 *sis)
अणु
	अचिन्हित दीर्घ io = sis->ioport;
	व्योम __iomem *ioaddr = sis->ioaddr;
	अचिन्हित दीर्घ समयout;
	u16 status;
	पूर्णांक count;
	पूर्णांक i;

	/* Reset the audio controller
	 */
	outl(SIS_GCR_SOFTWARE_RESET, io + SIS_GCR);
	udelay(25);
	outl(0, io + SIS_GCR);

	/* Get the AC-link semaphore, and reset the codecs
	 */
	count = 0xffff;
	जबतक ((inw(io + SIS_AC97_SEMA) & SIS_AC97_SEMA_BUSY) && --count)
		udelay(1);

	अगर (!count)
		वापस -EIO;

	outl(SIS_AC97_CMD_CODEC_COLD_RESET, io + SIS_AC97_CMD);
	udelay(250);

	count = 0xffff;
	जबतक ((inw(io + SIS_AC97_STATUS) & SIS_AC97_STATUS_BUSY) && --count)
		udelay(1);

	/* Command complete, we can let go of the semaphore now.
	 */
	outl(SIS_AC97_SEMA_RELEASE, io + SIS_AC97_SEMA);
	अगर (!count)
		वापस -EIO;

	/* Now that we've finished the reset, find out what's attached.
	 * There are some codec/board combinations that take an extremely
	 * दीर्घ समय to come up. 350+ ms has been observed in the field,
	 * so we'll give them up to 500ms.
	 */
	sis->codecs_present = 0;
	समयout = msecs_to_jअगरfies(500) + jअगरfies;
	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		status = inl(io + SIS_AC97_STATUS);
		अगर (status & SIS_AC97_STATUS_CODEC_READY)
			sis->codecs_present |= SIS_PRIMARY_CODEC_PRESENT;
		अगर (status & SIS_AC97_STATUS_CODEC2_READY)
			sis->codecs_present |= SIS_SECONDARY_CODEC_PRESENT;
		अगर (status & SIS_AC97_STATUS_CODEC3_READY)
			sis->codecs_present |= SIS_TERTIARY_CODEC_PRESENT;

		अगर (sis->codecs_present == codecs)
			अवरोध;

		msleep(1);
	पूर्ण

	/* All करोne, check क्रम errors.
	 */
	अगर (!sis->codecs_present) अणु
		dev_err(&sis->pci->dev, "could not find any codecs\n");
		वापस -EIO;
	पूर्ण

	अगर (sis->codecs_present != codecs) अणु
		dev_warn(&sis->pci->dev, "missing codecs, found %0x, expected %0x\n",
					 sis->codecs_present, codecs);
	पूर्ण

	/* Let the hardware know that the audio driver is alive,
	 * and enable PCM slots on the AC-link क्रम L/R playback (3 & 4) and
	 * record channels. We're going to want to use Variable Rate Audio
	 * क्रम recording, to aव्योम needlessly resampling from 48kHZ.
	 */
	outl(SIS_AC97_CONF_AUDIO_ALIVE, io + SIS_AC97_CONF);
	outl(SIS_AC97_CONF_AUDIO_ALIVE | SIS_AC97_CONF_PCM_LR_ENABLE |
		SIS_AC97_CONF_PCM_CAP_MIC_ENABLE |
		SIS_AC97_CONF_PCM_CAP_LR_ENABLE |
		SIS_AC97_CONF_CODEC_VRA_ENABLE, io + SIS_AC97_CONF);

	/* All AC97 PCM slots should be sourced from sub-mixer 0.
	 */
	outl(0, io + SIS_AC97_PSR);

	/* There is only one valid DMA setup क्रम a PCI environment.
	 */
	outl(SIS_DMA_CSR_PCI_SETTINGS, io + SIS_DMA_CSR);

	/* Reset the synchronization groups क्रम all of the channels
	 * to be asynchronous. If we start करोing SPDIF or 5.1 sound, etc.
	 * we'll need to change how we handle these. Until then, we just
	 * assign sub-mixer 0 to all playback channels, and aव्योम any
	 * attenuation on the audio.
	 */
	outl(0, io + SIS_PLAY_SYNC_GROUP_A);
	outl(0, io + SIS_PLAY_SYNC_GROUP_B);
	outl(0, io + SIS_PLAY_SYNC_GROUP_C);
	outl(0, io + SIS_PLAY_SYNC_GROUP_D);
	outl(0, io + SIS_MIXER_SYNC_GROUP);

	क्रम (i = 0; i < 64; i++) अणु
		ग_लिखोl(i, SIS_MIXER_START_ADDR(ioaddr, i));
		ग_लिखोl(SIS_MIXER_RIGHT_NO_ATTEN | SIS_MIXER_LEFT_NO_ATTEN |
				SIS_MIXER_DEST_0, SIS_MIXER_ADDR(ioaddr, i));
	पूर्ण

	/* Don't attenuate any audio set क्रम the wave amplअगरier.
	 *
	 * FIXME: Maximum attenuation is set क्रम the music amp, which will
	 * need to change अगर we start using the synth engine.
	 */
	outl(0xffff0000, io + SIS_WEVCR);

	/* Ensure that the wave engine is in normal operating mode.
	 */
	outl(0, io + SIS_WECCR);

	/* Go ahead and enable the DMA पूर्णांकerrupts. They won't go live
	 * until we start a channel.
	 */
	outl(SIS_GIER_AUDIO_PLAY_DMA_IRQ_ENABLE |
		SIS_GIER_AUDIO_RECORD_DMA_IRQ_ENABLE, io + SIS_GIER);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sis_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा sis7019 *sis = card->निजी_data;
	व्योम __iomem *ioaddr = sis->ioaddr;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	अगर (sis->codecs_present & SIS_PRIMARY_CODEC_PRESENT)
		snd_ac97_suspend(sis->ac97[0]);
	अगर (sis->codecs_present & SIS_SECONDARY_CODEC_PRESENT)
		snd_ac97_suspend(sis->ac97[1]);
	अगर (sis->codecs_present & SIS_TERTIARY_CODEC_PRESENT)
		snd_ac97_suspend(sis->ac97[2]);

	/* snd_pcm_suspend_all() stopped all channels, so we're quiescent.
	 */
	अगर (sis->irq >= 0) अणु
		मुक्त_irq(sis->irq, sis);
		sis->irq = -1;
	पूर्ण

	/* Save the पूर्णांकernal state away
	 */
	क्रम (i = 0; i < 4; i++) अणु
		स_नकल_fromio(sis->suspend_state[i], ioaddr, 4096);
		ioaddr += 4096;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sis_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा sis7019 *sis = card->निजी_data;
	व्योम __iomem *ioaddr = sis->ioaddr;
	पूर्णांक i;

	अगर (sis_chip_init(sis)) अणु
		dev_err(&pci->dev, "unable to re-init controller\n");
		जाओ error;
	पूर्ण

	अगर (request_irq(pci->irq, sis_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, sis)) अणु
		dev_err(&pci->dev, "unable to regain IRQ %d\n", pci->irq);
		जाओ error;
	पूर्ण

	/* Restore saved state, then clear out the page we use क्रम the
	 * silence buffer.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		स_नकल_toio(ioaddr, sis->suspend_state[i], 4096);
		ioaddr += 4096;
	पूर्ण

	स_रखो(sis->suspend_state[0], 0, 4096);

	sis->irq = pci->irq;

	अगर (sis->codecs_present & SIS_PRIMARY_CODEC_PRESENT)
		snd_ac97_resume(sis->ac97[0]);
	अगर (sis->codecs_present & SIS_SECONDARY_CODEC_PRESENT)
		snd_ac97_resume(sis->ac97[1]);
	अगर (sis->codecs_present & SIS_TERTIARY_CODEC_PRESENT)
		snd_ac97_resume(sis->ac97[2]);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;

error:
	snd_card_disconnect(card);
	वापस -EIO;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sis_pm, sis_suspend, sis_resume);
#घोषणा SIS_PM_OPS	&sis_pm
#अन्यथा
#घोषणा SIS_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक sis_alloc_suspend(काष्ठा sis7019 *sis)
अणु
	पूर्णांक i;

	/* We need 16K to store the पूर्णांकernal wave engine state during a
	 * suspend, but we करोn't need it to be contiguous, so play nice
	 * with the memory प्रणाली. We'll also use this area क्रम a silence
	 * buffer.
	 */
	क्रम (i = 0; i < SIS_SUSPEND_PAGES; i++) अणु
		sis->suspend_state[i] = kदो_स्मृति(4096, GFP_KERNEL);
		अगर (!sis->suspend_state[i])
			वापस -ENOMEM;
	पूर्ण
	स_रखो(sis->suspend_state[0], 0, 4096);

	वापस 0;
पूर्ण

अटल पूर्णांक sis_chip_create(काष्ठा snd_card *card,
			   काष्ठा pci_dev *pci)
अणु
	काष्ठा sis7019 *sis = card->निजी_data;
	काष्ठा voice *voice;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = sis_dev_मुक्त,
	पूर्ण;
	पूर्णांक rc;
	पूर्णांक i;

	rc = pci_enable_device(pci);
	अगर (rc)
		जाओ error_out;

	rc = dma_set_mask(&pci->dev, DMA_BIT_MASK(30));
	अगर (rc < 0) अणु
		dev_err(&pci->dev, "architecture does not support 30-bit PCI busmaster DMA");
		जाओ error_out_enabled;
	पूर्ण

	स_रखो(sis, 0, माप(*sis));
	mutex_init(&sis->ac97_mutex);
	spin_lock_init(&sis->voice_lock);
	sis->card = card;
	sis->pci = pci;
	sis->irq = -1;
	sis->ioport = pci_resource_start(pci, 0);

	rc = pci_request_regions(pci, "SiS7019");
	अगर (rc) अणु
		dev_err(&pci->dev, "unable request regions\n");
		जाओ error_out_enabled;
	पूर्ण

	rc = -EIO;
	sis->ioaddr = ioremap(pci_resource_start(pci, 1), 0x4000);
	अगर (!sis->ioaddr) अणु
		dev_err(&pci->dev, "unable to remap MMIO, aborting\n");
		जाओ error_out_cleanup;
	पूर्ण

	rc = sis_alloc_suspend(sis);
	अगर (rc < 0) अणु
		dev_err(&pci->dev, "unable to allocate state storage\n");
		जाओ error_out_cleanup;
	पूर्ण

	rc = sis_chip_init(sis);
	अगर (rc)
		जाओ error_out_cleanup;

	rc = request_irq(pci->irq, sis_पूर्णांकerrupt, IRQF_SHARED, KBUILD_MODNAME,
			 sis);
	अगर (rc) अणु
		dev_err(&pci->dev, "unable to allocate irq %d\n", sis->irq);
		जाओ error_out_cleanup;
	पूर्ण

	sis->irq = pci->irq;
	card->sync_irq = sis->irq;
	pci_set_master(pci);

	क्रम (i = 0; i < 64; i++) अणु
		voice = &sis->voices[i];
		voice->num = i;
		voice->ctrl_base = SIS_PLAY_DMA_ADDR(sis->ioaddr, i);
		voice->wave_base = SIS_WAVE_ADDR(sis->ioaddr, i);
	पूर्ण

	voice = &sis->capture_voice;
	voice->flags = VOICE_CAPTURE;
	voice->num = SIS_CAPTURE_CHAN_AC97_PCM_IN;
	voice->ctrl_base = SIS_CAPTURE_DMA_ADDR(sis->ioaddr, voice->num);

	rc = snd_device_new(card, SNDRV_DEV_LOWLEVEL, sis, &ops);
	अगर (rc)
		जाओ error_out_cleanup;

	वापस 0;

error_out_cleanup:
	sis_chip_मुक्त(sis);

error_out_enabled:
	pci_disable_device(pci);

error_out:
	वापस rc;
पूर्ण

अटल पूर्णांक snd_sis7019_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा sis7019 *sis;
	पूर्णांक rc;

	rc = -ENOENT;
	अगर (!enable)
		जाओ error_out;

	/* The user can specअगरy which codecs should be present so that we
	 * can रुको क्रम them to show up अगर they are slow to recover from
	 * the AC97 cold reset. We शेष to a single codec, the primary.
	 *
	 * We assume that SIS_PRIMARY_*_PRESENT matches bits 0-2.
	 */
	codecs &= SIS_PRIMARY_CODEC_PRESENT | SIS_SECONDARY_CODEC_PRESENT |
		  SIS_TERTIARY_CODEC_PRESENT;
	अगर (!codecs)
		codecs = SIS_PRIMARY_CODEC_PRESENT;

	rc = snd_card_new(&pci->dev, index, id, THIS_MODULE,
			  माप(*sis), &card);
	अगर (rc < 0)
		जाओ error_out;

	म_नकल(card->driver, "SiS7019");
	म_नकल(card->लघुname, "SiS7019");
	rc = sis_chip_create(card, pci);
	अगर (rc)
		जाओ card_error_out;

	sis = card->निजी_data;

	rc = sis_mixer_create(sis);
	अगर (rc)
		जाओ card_error_out;

	rc = sis_pcm_create(sis);
	अगर (rc)
		जाओ card_error_out;

	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			"%s Audio Accelerator with %s at 0x%lx, irq %d",
			card->लघुname, snd_ac97_get_लघु_name(sis->ac97[0]),
			sis->ioport, sis->irq);

	rc = snd_card_रेजिस्टर(card);
	अगर (rc)
		जाओ card_error_out;

	pci_set_drvdata(pci, card);
	वापस 0;

card_error_out:
	snd_card_मुक्त(card);

error_out:
	वापस rc;
पूर्ण

अटल व्योम snd_sis7019_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver sis7019_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_sis7019_ids,
	.probe = snd_sis7019_probe,
	.हटाओ = snd_sis7019_हटाओ,
	.driver = अणु
		.pm = SIS_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(sis7019_driver);
