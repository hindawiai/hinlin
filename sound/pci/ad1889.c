<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Analog Devices 1889 audio driver
 *
 * This is a driver क्रम the AD1889 PCI audio chipset found
 * on the HP PA-RISC [BCJ]-xxx0 workstations.
 *
 * Copyright (C) 2004-2005, Kyle McMartin <kyle@parisc-linux.org>
 * Copyright (C) 2005, Thibaut Varene <varenet@parisc-linux.org>
 *   Based on the OSS AD1889 driver by Ranकरोlph Chung <tausq@debian.org>
 *
 * TODO:
 *	Do we need to take care of CCS रेजिस्टर?
 *	Maybe we could use finer grained locking (separate locks क्रम pb/cap)?
 * Wishlist:
 *	Control Interface (mixer) support
 *	Better AC97 support (VSR...)?
 *	PM support
 *	MIDI support
 *	Game Port support
 *	SG DMA support (this will need *a lot* of work)
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/ac97_codec.h>

#समावेश "ad1889.h"
#समावेश "ac97/ac97_id.h"

#घोषणा	AD1889_DRVVER	"Version: 1.7"

MODULE_AUTHOR("Kyle McMartin <kyle@parisc-linux.org>, Thibaut Varene <t-bone@parisc-linux.org>");
MODULE_DESCRIPTION("Analog Devices AD1889 ALSA sound driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the AD1889 soundcard.");

अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the AD1889 soundcard.");

अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable AD1889 soundcard.");

अटल अक्षर *ac97_quirk[SNDRV_CARDS];
module_param_array(ac97_quirk, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(ac97_quirk, "AC'97 workaround for strange hardware.");

#घोषणा DEVNAME "ad1889"
#घोषणा PFX	DEVNAME ": "

/* keep track of some hw रेजिस्टरs */
काष्ठा ad1889_रेजिस्टर_state अणु
	u16 reg;	/* reg setup */
	u32 addr;	/* dma base address */
	अचिन्हित दीर्घ size;	/* DMA buffer size */
पूर्ण;

काष्ठा snd_ad1889 अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;

	पूर्णांक irq;
	अचिन्हित दीर्घ bar;
	व्योम __iomem *iobase;

	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_info_entry *proc;

	काष्ठा snd_pcm_substream *psubs;
	काष्ठा snd_pcm_substream *csubs;

	/* playback रेजिस्टर state */
	काष्ठा ad1889_रेजिस्टर_state wave;
	काष्ठा ad1889_रेजिस्टर_state ramc;

	spinlock_t lock;
पूर्ण;

अटल अंतरभूत u16
ad1889_पढ़ोw(काष्ठा snd_ad1889 *chip, अचिन्हित reg)
अणु
	वापस पढ़ोw(chip->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम
ad1889_ग_लिखोw(काष्ठा snd_ad1889 *chip, अचिन्हित reg, u16 val)
अणु
	ग_लिखोw(val, chip->iobase + reg);
पूर्ण

अटल अंतरभूत u32
ad1889_पढ़ोl(काष्ठा snd_ad1889 *chip, अचिन्हित reg)
अणु
	वापस पढ़ोl(chip->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम
ad1889_ग_लिखोl(काष्ठा snd_ad1889 *chip, अचिन्हित reg, u32 val)
अणु
	ग_लिखोl(val, chip->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम
ad1889_unmute(काष्ठा snd_ad1889 *chip)
अणु
	u16 st;
	st = ad1889_पढ़ोw(chip, AD_DS_WADA) & 
		~(AD_DS_WADA_RWAM | AD_DS_WADA_LWAM);
	ad1889_ग_लिखोw(chip, AD_DS_WADA, st);
	ad1889_पढ़ोw(chip, AD_DS_WADA);
पूर्ण

अटल अंतरभूत व्योम
ad1889_mute(काष्ठा snd_ad1889 *chip)
अणु
	u16 st;
	st = ad1889_पढ़ोw(chip, AD_DS_WADA) | AD_DS_WADA_RWAM | AD_DS_WADA_LWAM;
	ad1889_ग_लिखोw(chip, AD_DS_WADA, st);
	ad1889_पढ़ोw(chip, AD_DS_WADA);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_adc_buffer_address(काष्ठा snd_ad1889 *chip, u32 address)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_ADCBA, address);
	ad1889_ग_लिखोl(chip, AD_DMA_ADCCA, address);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_adc_buffer_count(काष्ठा snd_ad1889 *chip, u32 count)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_ADCBC, count);
	ad1889_ग_लिखोl(chip, AD_DMA_ADCCC, count);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_adc_पूर्णांकerrupt_count(काष्ठा snd_ad1889 *chip, u32 count)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_ADCIB, count);
	ad1889_ग_लिखोl(chip, AD_DMA_ADCIC, count);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_wave_buffer_address(काष्ठा snd_ad1889 *chip, u32 address)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_WAVBA, address);
	ad1889_ग_लिखोl(chip, AD_DMA_WAVCA, address);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_wave_buffer_count(काष्ठा snd_ad1889 *chip, u32 count)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_WAVBC, count);
	ad1889_ग_लिखोl(chip, AD_DMA_WAVCC, count);
पूर्ण

अटल अंतरभूत व्योम
ad1889_load_wave_पूर्णांकerrupt_count(काष्ठा snd_ad1889 *chip, u32 count)
अणु
	ad1889_ग_लिखोl(chip, AD_DMA_WAVIB, count);
	ad1889_ग_लिखोl(chip, AD_DMA_WAVIC, count);
पूर्ण

अटल व्योम
ad1889_channel_reset(काष्ठा snd_ad1889 *chip, अचिन्हित पूर्णांक channel)
अणु
	u16 reg;
	
	अगर (channel & AD_CHAN_WAV) अणु
		/* Disable wave channel */
		reg = ad1889_पढ़ोw(chip, AD_DS_WSMC) & ~AD_DS_WSMC_WAEN;
		ad1889_ग_लिखोw(chip, AD_DS_WSMC, reg);
		chip->wave.reg = reg;
		
		/* disable IRQs */
		reg = ad1889_पढ़ोw(chip, AD_DMA_WAV);
		reg &= AD_DMA_IM_DIS;
		reg &= ~AD_DMA_LOOP;
		ad1889_ग_लिखोw(chip, AD_DMA_WAV, reg);

		/* clear IRQ and address counters and poपूर्णांकers */
		ad1889_load_wave_buffer_address(chip, 0x0);
		ad1889_load_wave_buffer_count(chip, 0x0);
		ad1889_load_wave_पूर्णांकerrupt_count(chip, 0x0);

		/* flush */
		ad1889_पढ़ोw(chip, AD_DMA_WAV);
	पूर्ण
	
	अगर (channel & AD_CHAN_ADC) अणु
		/* Disable ADC channel */
		reg = ad1889_पढ़ोw(chip, AD_DS_RAMC) & ~AD_DS_RAMC_ADEN;
		ad1889_ग_लिखोw(chip, AD_DS_RAMC, reg);
		chip->ramc.reg = reg;

		reg = ad1889_पढ़ोw(chip, AD_DMA_ADC);
		reg &= AD_DMA_IM_DIS;
		reg &= ~AD_DMA_LOOP;
		ad1889_ग_लिखोw(chip, AD_DMA_ADC, reg);
	
		ad1889_load_adc_buffer_address(chip, 0x0);
		ad1889_load_adc_buffer_count(chip, 0x0);
		ad1889_load_adc_पूर्णांकerrupt_count(chip, 0x0);

		/* flush */
		ad1889_पढ़ोw(chip, AD_DMA_ADC);
	पूर्ण
पूर्ण

अटल u16
snd_ad1889_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा snd_ad1889 *chip = ac97->निजी_data;
	वापस ad1889_पढ़ोw(chip, AD_AC97_BASE + reg);
पूर्ण

अटल व्योम
snd_ad1889_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा snd_ad1889 *chip = ac97->निजी_data;
	ad1889_ग_लिखोw(chip, AD_AC97_BASE + reg, val);
पूर्ण

अटल पूर्णांक
snd_ad1889_ac97_पढ़ोy(काष्ठा snd_ad1889 *chip)
अणु
	पूर्णांक retry = 400; /* average needs 352 msec */
	
	जबतक (!(ad1889_पढ़ोw(chip, AD_AC97_ACIC) & AD_AC97_ACIC_ACRDY) 
			&& --retry)
		usleep_range(1000, 2000);
	अगर (!retry) अणु
		dev_err(chip->card->dev, "[%s] Link is not ready.\n",
			__func__);
		वापस -EIO;
	पूर्ण
	dev_dbg(chip->card->dev, "[%s] ready after %d ms\n", __func__, 400 - retry);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ad1889_playback_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min = 8000,	/* करोcs say 7000, but we're lazy */
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = PERIOD_BYTES_MAX,
	.periods_min = PERIODS_MIN,
	.periods_max = PERIODS_MAX,
	/*.fअगरo_size = 0,*/
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ad1889_capture_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,	/* करोcs say we could to VSR, but we're lazy */
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = PERIOD_BYTES_MAX,
	.periods_min = PERIODS_MIN,
	.periods_max = PERIODS_MAX,
	/*.fअगरo_size = 0,*/
पूर्ण;

अटल पूर्णांक
snd_ad1889_playback_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;

	chip->psubs = ss;
	rt->hw = snd_ad1889_playback_hw;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_capture_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;

	chip->csubs = ss;
	rt->hw = snd_ad1889_capture_hw;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_playback_बंद(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	chip->psubs = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_capture_बंद(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	chip->csubs = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_playback_prepare(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(ss);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(ss);
	u16 reg;

	ad1889_channel_reset(chip, AD_CHAN_WAV);

	reg = ad1889_पढ़ोw(chip, AD_DS_WSMC);
	
	/* Mask out 16-bit / Stereo */
	reg &= ~(AD_DS_WSMC_WA16 | AD_DS_WSMC_WAST);

	अगर (snd_pcm_क्रमmat_width(rt->क्रमmat) == 16)
		reg |= AD_DS_WSMC_WA16;

	अगर (rt->channels > 1)
		reg |= AD_DS_WSMC_WAST;

	/* let's make sure we don't clobber ourselves */
	spin_lock_irq(&chip->lock);
	
	chip->wave.size = size;
	chip->wave.reg = reg;
	chip->wave.addr = rt->dma_addr;

	ad1889_ग_लिखोw(chip, AD_DS_WSMC, chip->wave.reg);
	
	/* Set sample rates on the codec */
	ad1889_ग_लिखोw(chip, AD_DS_WAS, rt->rate);

	/* Set up DMA */
	ad1889_load_wave_buffer_address(chip, chip->wave.addr);
	ad1889_load_wave_buffer_count(chip, size);
	ad1889_load_wave_पूर्णांकerrupt_count(chip, count);

	/* ग_लिखोs flush */
	ad1889_पढ़ोw(chip, AD_DS_WSMC);
	
	spin_unlock_irq(&chip->lock);
	
	dev_dbg(chip->card->dev,
		"prepare playback: addr = 0x%x, count = %u, size = %u, reg = 0x%x, rate = %u\n",
		chip->wave.addr, count, size, reg, rt->rate);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_capture_prepare(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(ss);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(ss);
	u16 reg;

	ad1889_channel_reset(chip, AD_CHAN_ADC);
	
	reg = ad1889_पढ़ोw(chip, AD_DS_RAMC);

	/* Mask out 16-bit / Stereo */
	reg &= ~(AD_DS_RAMC_AD16 | AD_DS_RAMC_ADST);

	अगर (snd_pcm_क्रमmat_width(rt->क्रमmat) == 16)
		reg |= AD_DS_RAMC_AD16;

	अगर (rt->channels > 1)
		reg |= AD_DS_RAMC_ADST;

	/* let's make sure we don't clobber ourselves */
	spin_lock_irq(&chip->lock);
	
	chip->ramc.size = size;
	chip->ramc.reg = reg;
	chip->ramc.addr = rt->dma_addr;

	ad1889_ग_लिखोw(chip, AD_DS_RAMC, chip->ramc.reg);

	/* Set up DMA */
	ad1889_load_adc_buffer_address(chip, chip->ramc.addr);
	ad1889_load_adc_buffer_count(chip, size);
	ad1889_load_adc_पूर्णांकerrupt_count(chip, count);

	/* ग_लिखोs flush */
	ad1889_पढ़ोw(chip, AD_DS_RAMC);
	
	spin_unlock_irq(&chip->lock);
	
	dev_dbg(chip->card->dev,
		"prepare capture: addr = 0x%x, count = %u, size = %u, reg = 0x%x, rate = %u\n",
		chip->ramc.addr, count, size, reg, rt->rate);
	वापस 0;
पूर्ण

/* this is called in atomic context with IRQ disabled.
   Must be as fast as possible and not sleep.
   DMA should be *triggered* by this call.
   The WSMC "WAEN" bit triggers DMA Wave On/Off */
अटल पूर्णांक
snd_ad1889_playback_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	u16 wsmc;
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	
	wsmc = ad1889_पढ़ोw(chip, AD_DS_WSMC);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* enable DMA loop & पूर्णांकerrupts */
		ad1889_ग_लिखोw(chip, AD_DMA_WAV, AD_DMA_LOOP | AD_DMA_IM_CNT);
		wsmc |= AD_DS_WSMC_WAEN;
		/* 1 to clear CHSS bit */
		ad1889_ग_लिखोl(chip, AD_DMA_CHSS, AD_DMA_CHSS_WAVS);
		ad1889_unmute(chip);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		ad1889_mute(chip);
		wsmc &= ~AD_DS_WSMC_WAEN;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	
	chip->wave.reg = wsmc;
	ad1889_ग_लिखोw(chip, AD_DS_WSMC, wsmc);	
	ad1889_पढ़ोw(chip, AD_DS_WSMC);	/* flush */

	/* reset the chip when STOP - will disable IRQs */
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP)
		ad1889_channel_reset(chip, AD_CHAN_WAV);

	वापस 0;
पूर्ण

/* this is called in atomic context with IRQ disabled.
   Must be as fast as possible and not sleep.
   DMA should be *triggered* by this call.
   The RAMC "ADEN" bit triggers DMA ADC On/Off */
अटल पूर्णांक
snd_ad1889_capture_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	u16 ramc;
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);

	ramc = ad1889_पढ़ोw(chip, AD_DS_RAMC);
	
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* enable DMA loop & पूर्णांकerrupts */
		ad1889_ग_लिखोw(chip, AD_DMA_ADC, AD_DMA_LOOP | AD_DMA_IM_CNT);
		ramc |= AD_DS_RAMC_ADEN;
		/* 1 to clear CHSS bit */
		ad1889_ग_लिखोl(chip, AD_DMA_CHSS, AD_DMA_CHSS_ADCS);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		ramc &= ~AD_DS_RAMC_ADEN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	
	chip->ramc.reg = ramc;
	ad1889_ग_लिखोw(chip, AD_DS_RAMC, ramc);	
	ad1889_पढ़ोw(chip, AD_DS_RAMC);	/* flush */
	
	/* reset the chip when STOP - will disable IRQs */
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP)
		ad1889_channel_reset(chip, AD_CHAN_ADC);
		
	वापस 0;
पूर्ण

/* Called in atomic context with IRQ disabled */
अटल snd_pcm_uframes_t
snd_ad1889_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
	माप_प्रकार ptr = 0;
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);

	अगर (unlikely(!(chip->wave.reg & AD_DS_WSMC_WAEN)))
		वापस 0;

	ptr = ad1889_पढ़ोl(chip, AD_DMA_WAVCA);
	ptr -= chip->wave.addr;
	
	अगर (snd_BUG_ON(ptr >= chip->wave.size))
		वापस 0;
	
	वापस bytes_to_frames(ss->runसमय, ptr);
पूर्ण

/* Called in atomic context with IRQ disabled */
अटल snd_pcm_uframes_t
snd_ad1889_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
	माप_प्रकार ptr = 0;
	काष्ठा snd_ad1889 *chip = snd_pcm_substream_chip(ss);

	अगर (unlikely(!(chip->ramc.reg & AD_DS_RAMC_ADEN)))
		वापस 0;

	ptr = ad1889_पढ़ोl(chip, AD_DMA_ADCCA);
	ptr -= chip->ramc.addr;

	अगर (snd_BUG_ON(ptr >= chip->ramc.size))
		वापस 0;
	
	वापस bytes_to_frames(ss->runसमय, ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ad1889_playback_ops = अणु
	.खोलो = snd_ad1889_playback_खोलो,
	.बंद = snd_ad1889_playback_बंद,
	.prepare = snd_ad1889_playback_prepare,
	.trigger = snd_ad1889_playback_trigger,
	.poपूर्णांकer = snd_ad1889_playback_poपूर्णांकer, 
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ad1889_capture_ops = अणु
	.खोलो = snd_ad1889_capture_खोलो,
	.बंद = snd_ad1889_capture_बंद,
	.prepare = snd_ad1889_capture_prepare,
	.trigger = snd_ad1889_capture_trigger,
	.poपूर्णांकer = snd_ad1889_capture_poपूर्णांकer, 
पूर्ण;

अटल irqवापस_t
snd_ad1889_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ st;
	काष्ठा snd_ad1889 *chip = dev_id;

	st = ad1889_पढ़ोl(chip, AD_DMA_DISR);

	/* clear ISR */
	ad1889_ग_लिखोl(chip, AD_DMA_DISR, st);

	st &= AD_INTR_MASK;

	अगर (unlikely(!st))
		वापस IRQ_NONE;

	अगर (st & (AD_DMA_DISR_PMAI|AD_DMA_DISR_PTAI))
		dev_dbg(chip->card->dev,
			"Unexpected master or target abort interrupt!\n");

	अगर ((st & AD_DMA_DISR_WAVI) && chip->psubs)
		snd_pcm_period_elapsed(chip->psubs);
	अगर ((st & AD_DMA_DISR_ADCI) && chip->csubs)
		snd_pcm_period_elapsed(chip->csubs);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
snd_ad1889_pcm_init(काष्ठा snd_ad1889 *chip, पूर्णांक device)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	err = snd_pcm_new(chip->card, chip->card->driver, device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, 
			&snd_ad1889_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_ad1889_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, chip->card->लघुname);
	
	chip->pcm = pcm;
	chip->psubs = शून्य;
	chip->csubs = शून्य;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				       BUFFER_BYTES_MAX / 2, BUFFER_BYTES_MAX);

	वापस 0;
पूर्ण

अटल व्योम
snd_ad1889_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ad1889 *chip = entry->निजी_data;
	u16 reg;
	पूर्णांक पंचांगp;

	reg = ad1889_पढ़ोw(chip, AD_DS_WSMC);
	snd_iम_लिखो(buffer, "Wave output: %s\n",
			(reg & AD_DS_WSMC_WAEN) ? "enabled" : "disabled");
	snd_iम_लिखो(buffer, "Wave Channels: %s\n",
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
	snd_iम_लिखो(buffer, "Wave Quality: %d-bit linear\n",
			(reg & AD_DS_WSMC_WA16) ? 16 : 8);
	
	/* WARQ is at offset 12 */
	पंचांगp = (reg & AD_DS_WSMC_WARQ) ?
		((((reg & AD_DS_WSMC_WARQ) >> 12) & 0x01) ? 12 : 18) : 4;
	पंचांगp /= (reg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_iम_लिखो(buffer, "Wave FIFO: %d %s words\n\n", पंचांगp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
				
	
	snd_iम_लिखो(buffer, "Synthesis output: %s\n",
			reg & AD_DS_WSMC_SYEN ? "enabled" : "disabled");
	
	/* SYRQ is at offset 4 */
	पंचांगp = (reg & AD_DS_WSMC_SYRQ) ?
		((((reg & AD_DS_WSMC_SYRQ) >> 4) & 0x01) ? 12 : 18) : 4;
	पंचांगp /= (reg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_iम_लिखो(buffer, "Synthesis FIFO: %d %s words\n\n", पंचांगp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");

	reg = ad1889_पढ़ोw(chip, AD_DS_RAMC);
	snd_iम_लिखो(buffer, "ADC input: %s\n",
			(reg & AD_DS_RAMC_ADEN) ? "enabled" : "disabled");
	snd_iम_लिखो(buffer, "ADC Channels: %s\n",
			(reg & AD_DS_RAMC_ADST) ? "stereo" : "mono");
	snd_iम_लिखो(buffer, "ADC Quality: %d-bit linear\n",
			(reg & AD_DS_RAMC_AD16) ? 16 : 8);
	
	/* ACRQ is at offset 4 */
	पंचांगp = (reg & AD_DS_RAMC_ACRQ) ?
		((((reg & AD_DS_RAMC_ACRQ) >> 4) & 0x01) ? 12 : 18) : 4;
	पंचांगp /= (reg & AD_DS_RAMC_ADST) ? 2 : 1;
	
	snd_iम_लिखो(buffer, "ADC FIFO: %d %s words\n\n", पंचांगp,
			(reg & AD_DS_RAMC_ADST) ? "stereo" : "mono");
	
	snd_iम_लिखो(buffer, "Resampler input: %s\n",
			reg & AD_DS_RAMC_REEN ? "enabled" : "disabled");
			
	/* RERQ is at offset 12 */
	पंचांगp = (reg & AD_DS_RAMC_RERQ) ?
		((((reg & AD_DS_RAMC_RERQ) >> 12) & 0x01) ? 12 : 18) : 4;
	पंचांगp /= (reg & AD_DS_RAMC_ADST) ? 2 : 1;
	
	snd_iम_लिखो(buffer, "Resampler FIFO: %d %s words\n\n", पंचांगp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
				
	
	/* करोc says LSB represents -1.5dB, but the max value (-94.5dB)
	suggests that LSB is -3dB, which is more coherent with the logarithmic
	nature of the dB scale */
	reg = ad1889_पढ़ोw(chip, AD_DS_WADA);
	snd_iम_लिखो(buffer, "Left: %s, -%d dB\n",
			(reg & AD_DS_WADA_LWAM) ? "mute" : "unmute",
			((reg & AD_DS_WADA_LWAA) >> 8) * 3);
	reg = ad1889_पढ़ोw(chip, AD_DS_WADA);
	snd_iम_लिखो(buffer, "Right: %s, -%d dB\n",
			(reg & AD_DS_WADA_RWAM) ? "mute" : "unmute",
			(reg & AD_DS_WADA_RWAA) * 3);
	
	reg = ad1889_पढ़ोw(chip, AD_DS_WAS);
	snd_iम_लिखो(buffer, "Wave samplerate: %u Hz\n", reg);
	reg = ad1889_पढ़ोw(chip, AD_DS_RES);
	snd_iम_लिखो(buffer, "Resampler samplerate: %u Hz\n", reg);
पूर्ण

अटल व्योम
snd_ad1889_proc_init(काष्ठा snd_ad1889 *chip)
अणु
	snd_card_ro_proc_new(chip->card, chip->card->driver,
			     chip, snd_ad1889_proc_पढ़ो);
पूर्ण

अटल स्थिर काष्ठा ac97_quirk ac97_quirks[] = अणु
	अणु
		.subvenकरोr = 0x11d4,	/* AD */
		.subdevice = 0x1889,	/* AD1889 */
		.codec_id = AC97_ID_AD1819,
		.name = "AD1889",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

अटल व्योम
snd_ad1889_ac97_xinit(काष्ठा snd_ad1889 *chip)
अणु
	u16 reg;

	reg = ad1889_पढ़ोw(chip, AD_AC97_ACIC);
	reg |= AD_AC97_ACIC_ACRD;		/* Reset Disable */
	ad1889_ग_लिखोw(chip, AD_AC97_ACIC, reg);
	ad1889_पढ़ोw(chip, AD_AC97_ACIC);	/* flush posted ग_लिखो */
	udelay(10);
	/* Interface Enable */
	reg |= AD_AC97_ACIC_ACIE;
	ad1889_ग_लिखोw(chip, AD_AC97_ACIC, reg);
	
	snd_ad1889_ac97_पढ़ोy(chip);

	/* Audio Stream Output | Variable Sample Rate Mode */
	reg = ad1889_पढ़ोw(chip, AD_AC97_ACIC);
	reg |= AD_AC97_ACIC_ASOE | AD_AC97_ACIC_VSRM;
	ad1889_ग_लिखोw(chip, AD_AC97_ACIC, reg);
	ad1889_पढ़ोw(chip, AD_AC97_ACIC); /* flush posted ग_लिखो */

पूर्ण

अटल व्योम
snd_ad1889_ac97_bus_मुक्त(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा snd_ad1889 *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम
snd_ad1889_ac97_मुक्त(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_ad1889 *chip = ac97->निजी_data;
	chip->ac97 = शून्य;
पूर्ण

अटल पूर्णांक
snd_ad1889_ac97_init(काष्ठा snd_ad1889 *chip, स्थिर अक्षर *quirk_override)
अणु
	पूर्णांक err;
	काष्ठा snd_ac97_ढाँचा ac97;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_ad1889_ac97_ग_लिखो,
		.पढ़ो = snd_ad1889_ac97_पढ़ो,
	पूर्ण;

	/* करोing that here, it works. */
	snd_ad1889_ac97_xinit(chip);

	err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus);
	अगर (err < 0)
		वापस err;
	
	chip->ac97_bus->निजी_मुक्त = snd_ad1889_ac97_bus_मुक्त;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_ad1889_ac97_मुक्त;
	ac97.pci = chip->pci;

	err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97);
	अगर (err < 0)
		वापस err;
		
	snd_ac97_tune_hardware(chip->ac97, ac97_quirks, quirk_override);
	
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_मुक्त(काष्ठा snd_ad1889 *chip)
अणु
	अगर (chip->irq < 0)
		जाओ skip_hw;

	spin_lock_irq(&chip->lock);

	ad1889_mute(chip);

	/* Turn off पूर्णांकerrupt on count and zero DMA रेजिस्टरs */
	ad1889_channel_reset(chip, AD_CHAN_WAV | AD_CHAN_ADC);

	/* clear DISR. If we करोn't, we'd better jump off the Eअगरfel Tower */
	ad1889_ग_लिखोl(chip, AD_DMA_DISR, AD_DMA_DISR_PTAI | AD_DMA_DISR_PMAI);
	ad1889_पढ़ोl(chip, AD_DMA_DISR);	/* flush, dammit! */

	spin_unlock_irq(&chip->lock);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

skip_hw:
	iounmap(chip->iobase);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_dev_मुक्त(काष्ठा snd_device *device) 
अणु
	काष्ठा snd_ad1889 *chip = device->device_data;
	वापस snd_ad1889_मुक्त(chip);
पूर्ण

अटल पूर्णांक
snd_ad1889_init(काष्ठा snd_ad1889 *chip) 
अणु
	ad1889_ग_लिखोw(chip, AD_DS_CCS, AD_DS_CCS_CLKEN); /* turn on घड़ी */
	ad1889_पढ़ोw(chip, AD_DS_CCS);	/* flush posted ग_लिखो */

	usleep_range(10000, 11000);

	/* enable Master and Target पात पूर्णांकerrupts */
	ad1889_ग_लिखोl(chip, AD_DMA_DISR, AD_DMA_DISR_PMAE | AD_DMA_DISR_PTAE);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_ad1889_create(काष्ठा snd_card *card,
		  काष्ठा pci_dev *pci,
		  काष्ठा snd_ad1889 **rchip)
अणु
	पूर्णांक err;

	काष्ठा snd_ad1889 *chip;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_ad1889_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	/* check PCI availability (32bit DMA) */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32))) अणु
		dev_err(card->dev, "error setting 32-bit DMA mask.\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	/* allocate chip specअगरic data with zero-filled memory */
	अगर ((chip = kzalloc(माप(*chip), GFP_KERNEL)) == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	card->निजी_data = chip;
	chip->pci = pci;
	chip->irq = -1;

	/* (1) PCI resource allocation */
	अगर ((err = pci_request_regions(pci, card->driver)) < 0)
		जाओ मुक्त_and_ret;

	chip->bar = pci_resource_start(pci, 0);
	chip->iobase = pci_ioremap_bar(pci, 0);
	अगर (chip->iobase == शून्य) अणु
		dev_err(card->dev, "unable to reserve region.\n");
		err = -EBUSY;
		जाओ मुक्त_and_ret;
	पूर्ण
	
	pci_set_master(pci);

	spin_lock_init(&chip->lock);	/* only now can we call ad1889_मुक्त */

	अगर (request_irq(pci->irq, snd_ad1889_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "cannot obtain IRQ %d\n", pci->irq);
		snd_ad1889_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण

	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	/* (2) initialization of the chip hardware */
	अगर ((err = snd_ad1889_init(chip)) < 0) अणु
		snd_ad1889_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_ad1889_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;

	वापस 0;

मुक्त_and_ret:
	kमुक्त(chip);
	pci_disable_device(pci);

	वापस err;
पूर्ण

अटल पूर्णांक
snd_ad1889_probe(काष्ठा pci_dev *pci,
		 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक err;
	अटल पूर्णांक devno;
	काष्ठा snd_card *card;
	काष्ठा snd_ad1889 *chip;

	/* (1) */
	अगर (devno >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[devno]) अणु
		devno++;
		वापस -ENOENT;
	पूर्ण

	/* (2) */
	err = snd_card_new(&pci->dev, index[devno], id[devno], THIS_MODULE,
			   0, &card);
	/* XXX REVISIT: we can probably allocate chip in this call */
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "AD1889");
	म_नकल(card->लघुname, "Analog Devices AD1889");

	/* (3) */
	err = snd_ad1889_create(card, pci, &chip);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	/* (4) */
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %i",
		card->लघुname, chip->bar, chip->irq);

	/* (5) */
	/* रेजिस्टर AC97 mixer */
	err = snd_ad1889_ac97_init(chip, ac97_quirk[devno]);
	अगर (err < 0)
		जाओ मुक्त_and_ret;
	
	err = snd_ad1889_pcm_init(chip, 0);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	/* रेजिस्टर proc पूर्णांकerface */
	snd_ad1889_proc_init(chip);

	/* (6) */
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	/* (7) */
	pci_set_drvdata(pci, card);

	devno++;
	वापस 0;

मुक्त_and_ret:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम
snd_ad1889_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल स्थिर काष्ठा pci_device_id snd_ad1889_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ANALOG_DEVICES, PCI_DEVICE_ID_AD1889JS) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_ad1889_ids);

अटल काष्ठा pci_driver ad1889_pci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_ad1889_ids,
	.probe = snd_ad1889_probe,
	.हटाओ = snd_ad1889_हटाओ,
पूर्ण;

module_pci_driver(ad1889_pci_driver);
