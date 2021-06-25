<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Support क्रम CX23885 analog audio capture
 *
 *    (c) 2008 Mijhail Moreyra <mijhail.moreyra@gmail.com>
 *    Adapted from cx88-alsa.c
 *    (c) 2009 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-reg.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/delay.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>

#समावेश <sound/tlv.h>

#घोषणा AUDIO_SRAM_CHANNEL	SRAM_CH07

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (audio_debug + 1 > level)					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: alsa: " fmt), \
			chip->dev->name, ##arg); \
पूर्ण जबतक(0)

/****************************************************************************
			Module global अटल vars
 ****************************************************************************/

अटल अचिन्हित पूर्णांक disable_analog_audio;
module_param(disable_analog_audio, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_analog_audio, "disable analog audio ALSA driver");

अटल अचिन्हित पूर्णांक audio_debug;
module_param(audio_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_debug, "enable debug messages [analog audio]");

/****************************************************************************
			Board specअगरic functions
 ****************************************************************************/

/* Constants taken from cx88-reg.h */
#घोषणा AUD_INT_DN_RISCI1       (1 <<  0)
#घोषणा AUD_INT_UP_RISCI1       (1 <<  1)
#घोषणा AUD_INT_RDS_DN_RISCI1   (1 <<  2)
#घोषणा AUD_INT_DN_RISCI2       (1 <<  4) /* yes, 3 is skipped */
#घोषणा AUD_INT_UP_RISCI2       (1 <<  5)
#घोषणा AUD_INT_RDS_DN_RISCI2   (1 <<  6)
#घोषणा AUD_INT_DN_SYNC         (1 << 12)
#घोषणा AUD_INT_UP_SYNC         (1 << 13)
#घोषणा AUD_INT_RDS_DN_SYNC     (1 << 14)
#घोषणा AUD_INT_OPC_ERR         (1 << 16)
#घोषणा AUD_INT_BER_IRQ         (1 << 20)
#घोषणा AUD_INT_MCHG_IRQ        (1 << 21)
#घोषणा GP_COUNT_CONTROL_RESET	0x3

अटल पूर्णांक cx23885_alsa_dma_init(काष्ठा cx23885_audio_dev *chip,
				 अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा cx23885_audio_buffer *buf = chip->buf;
	काष्ठा page *pg;
	पूर्णांक i;

	buf->vaddr = vदो_स्मृति_32(nr_pages << PAGE_SHIFT);
	अगर (शून्य == buf->vaddr) अणु
		dprपूर्णांकk(1, "vmalloc_32(%lu pages) failed\n", nr_pages);
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(1, "vmalloc is at addr %p, size=%lu\n",
		buf->vaddr, nr_pages << PAGE_SHIFT);

	स_रखो(buf->vaddr, 0, nr_pages << PAGE_SHIFT);
	buf->nr_pages = nr_pages;

	buf->sglist = vzalloc(array_size(माप(*buf->sglist), buf->nr_pages));
	अगर (शून्य == buf->sglist)
		जाओ vzalloc_err;

	sg_init_table(buf->sglist, buf->nr_pages);
	क्रम (i = 0; i < buf->nr_pages; i++) अणु
		pg = vदो_स्मृति_to_page(buf->vaddr + i * PAGE_SIZE);
		अगर (शून्य == pg)
			जाओ vदो_स्मृति_to_page_err;
		sg_set_page(&buf->sglist[i], pg, PAGE_SIZE, 0);
	पूर्ण
	वापस 0;

vदो_स्मृति_to_page_err:
	vमुक्त(buf->sglist);
	buf->sglist = शून्य;
vzalloc_err:
	vमुक्त(buf->vaddr);
	buf->vaddr = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cx23885_alsa_dma_map(काष्ठा cx23885_audio_dev *dev)
अणु
	काष्ठा cx23885_audio_buffer *buf = dev->buf;

	buf->sglen = dma_map_sg(&dev->pci->dev, buf->sglist,
			buf->nr_pages, DMA_FROM_DEVICE);

	अगर (0 == buf->sglen) अणु
		pr_warn("%s: cx23885_alsa_map_sg failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_alsa_dma_unmap(काष्ठा cx23885_audio_dev *dev)
अणु
	काष्ठा cx23885_audio_buffer *buf = dev->buf;

	अगर (!buf->sglen)
		वापस 0;

	dma_unmap_sg(&dev->pci->dev, buf->sglist, buf->nr_pages, DMA_FROM_DEVICE);
	buf->sglen = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_alsa_dma_मुक्त(काष्ठा cx23885_audio_buffer *buf)
अणु
	vमुक्त(buf->sglist);
	buf->sglist = शून्य;
	vमुक्त(buf->vaddr);
	buf->vaddr = शून्य;
	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Sets audio DMA
 */

अटल पूर्णांक cx23885_start_audio_dma(काष्ठा cx23885_audio_dev *chip)
अणु
	काष्ठा cx23885_audio_buffer *buf = chip->buf;
	काष्ठा cx23885_dev *dev  = chip->dev;
	काष्ठा sram_channel *audio_ch =
		&dev->sram_channels[AUDIO_SRAM_CHANNEL];

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Make sure RISC/FIFO are off beक्रमe changing FIFO/RISC settings */
	cx_clear(AUD_INT_DMA_CTL, 0x11);

	/* setup fअगरo + क्रमmat - out channel */
	cx23885_sram_channel_setup(chip->dev, audio_ch, buf->bpl,
		buf->risc.dma);

	/* sets bpl size */
	cx_ग_लिखो(AUD_INT_A_LNGTH, buf->bpl);

	/* This is required to get good audio (1 seems to be ok) */
	cx_ग_लिखो(AUD_INT_A_MODE, 1);

	/* reset counter */
	cx_ग_लिखो(AUD_INT_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
	atomic_set(&chip->count, 0);

	dprपूर्णांकk(1, "Start audio DMA, %d B/line, %d lines/FIFO, %d periods, %d byte buffer\n",
		buf->bpl, cx_पढ़ो(audio_ch->cmds_start+12)>>1,
		chip->num_periods, buf->bpl * chip->num_periods);

	/* Enables corresponding bits at AUD_INT_STAT */
	cx_ग_लिखो(AUDIO_INT_INT_MSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				    AUD_INT_DN_RISCI1);

	/* Clean any pending पूर्णांकerrupt bits alपढ़ोy set */
	cx_ग_लिखो(AUDIO_INT_INT_STAT, ~0);

	/* enable audio irqs */
	cx_set(PCI_INT_MSK, chip->dev->pci_irqmask | PCI_MSK_AUD_INT);

	/* start dma */
	cx_set(DEV_CNTRL2, (1<<5)); /* Enables Risc Processor */
	cx_set(AUD_INT_DMA_CTL, 0x11); /* audio करोwnstream FIFO and
					  RISC enable */
	अगर (audio_debug)
		cx23885_sram_channel_dump(chip->dev, audio_ch);

	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Resets audio DMA
 */
अटल पूर्णांक cx23885_stop_audio_dma(काष्ठा cx23885_audio_dev *chip)
अणु
	काष्ठा cx23885_dev *dev = chip->dev;
	dprपूर्णांकk(1, "Stopping audio DMA\n");

	/* stop dma */
	cx_clear(AUD_INT_DMA_CTL, 0x11);

	/* disable irqs */
	cx_clear(PCI_INT_MSK, PCI_MSK_AUD_INT);
	cx_clear(AUDIO_INT_INT_MSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				    AUD_INT_DN_RISCI1);

	अगर (audio_debug)
		cx23885_sram_channel_dump(chip->dev,
			&dev->sram_channels[AUDIO_SRAM_CHANNEL]);

	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Handles audio IRQ
 */
पूर्णांक cx23885_audio_irq(काष्ठा cx23885_dev *dev, u32 status, u32 mask)
अणु
	काष्ठा cx23885_audio_dev *chip = dev->audio_dev;

	अगर (0 == (status & mask))
		वापस 0;

	cx_ग_लिखो(AUDIO_INT_INT_STAT, status);

	/* risc op code error */
	अगर (status & AUD_INT_OPC_ERR) अणु
		pr_warn("%s/1: Audio risc op code error\n",
			dev->name);
		cx_clear(AUD_INT_DMA_CTL, 0x11);
		cx23885_sram_channel_dump(dev,
			&dev->sram_channels[AUDIO_SRAM_CHANNEL]);
	पूर्ण
	अगर (status & AUD_INT_DN_SYNC) अणु
		dprपूर्णांकk(1, "Downstream sync error\n");
		cx_ग_लिखो(AUD_INT_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
		वापस 1;
	पूर्ण
	/* risc1 करोwnstream */
	अगर (status & AUD_INT_DN_RISCI1) अणु
		atomic_set(&chip->count, cx_पढ़ो(AUD_INT_A_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	पूर्ण
	/* FIXME: Any other status should deserve a special handling? */

	वापस 1;
पूर्ण

अटल पूर्णांक dsp_buffer_मुक्त(काष्ठा cx23885_audio_dev *chip)
अणु
	काष्ठा cx23885_riscmem *risc;

	BUG_ON(!chip->dma_size);

	dprपूर्णांकk(2, "Freeing buffer\n");
	cx23885_alsa_dma_unmap(chip);
	cx23885_alsa_dma_मुक्त(chip->buf);
	risc = &chip->buf->risc;
	dma_मुक्त_coherent(&chip->pci->dev, risc->size, risc->cpu, risc->dma);
	kमुक्त(chip->buf);

	chip->buf = शून्य;
	chip->dma_size = 0;

	वापस 0;
पूर्ण

/****************************************************************************
				ALSA PCM Interface
 ****************************************************************************/

/*
 * Digital hardware definition
 */
#घोषणा DEFAULT_FIFO_SIZE	4096

अटल स्थिर काष्ठा snd_pcm_hardware snd_cx23885_digital_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min = 2,
	.channels_max = 2,
	/* Analog audio output will be full of clicks and pops अगर there
	   are not exactly four lines in the SRAM FIFO buffer.  */
	.period_bytes_min = DEFAULT_FIFO_SIZE/4,
	.period_bytes_max = DEFAULT_FIFO_SIZE/4,
	.periods_min = 1,
	.periods_max = 1024,
	.buffer_bytes_max = (1024*1024),
पूर्ण;

/*
 * audio pcm capture खोलो callback
 */
अटल पूर्णांक snd_cx23885_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx23885_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर (!chip) अणु
		pr_err("BUG: cx23885 can't find device struct. Can't proceed with open\n");
		वापस -ENODEV;
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
		SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ _error;

	chip->substream = substream;

	runसमय->hw = snd_cx23885_digital_hw;

	अगर (chip->dev->sram_channels[AUDIO_SRAM_CHANNEL].fअगरo_size !=
		DEFAULT_FIFO_SIZE) अणु
		अचिन्हित पूर्णांक bpl = chip->dev->
			sram_channels[AUDIO_SRAM_CHANNEL].fअगरo_size / 4;
		bpl &= ~7; /* must be multiple of 8 */
		runसमय->hw.period_bytes_min = bpl;
		runसमय->hw.period_bytes_max = bpl;
	पूर्ण

	वापस 0;
_error:
	dprपूर्णांकk(1, "Error opening PCM!\n");
	वापस err;
पूर्ण

/*
 * audio बंद callback
 */
अटल पूर्णांक snd_cx23885_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण


/*
 * hw_params callback
 */
अटल पूर्णांक snd_cx23885_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cx23885_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा cx23885_audio_buffer *buf;
	पूर्णांक ret;

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	chip->period_size = params_period_bytes(hw_params);
	chip->num_periods = params_periods(hw_params);
	chip->dma_size = chip->period_size * params_periods(hw_params);

	BUG_ON(!chip->dma_size);
	BUG_ON(chip->num_periods & (chip->num_periods-1));

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (शून्य == buf)
		वापस -ENOMEM;

	buf->bpl = chip->period_size;
	chip->buf = buf;

	ret = cx23885_alsa_dma_init(chip,
			(PAGE_ALIGN(chip->dma_size) >> PAGE_SHIFT));
	अगर (ret < 0)
		जाओ error;

	ret = cx23885_alsa_dma_map(chip);
	अगर (ret < 0)
		जाओ error;

	ret = cx23885_risc_databuffer(chip->pci, &buf->risc, buf->sglist,
				   chip->period_size, chip->num_periods, 1);
	अगर (ret < 0)
		जाओ error;

	/* Loop back to start of program */
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP|RISC_IRQ1|RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
	buf->risc.jmp[2] = cpu_to_le32(0); /* bits 63-32 */

	substream->runसमय->dma_area = chip->buf->vaddr;
	substream->runसमय->dma_bytes = chip->dma_size;
	substream->runसमय->dma_addr = 0;

	वापस 0;

error:
	kमुक्त(buf);
	chip->buf = शून्य;
	वापस ret;
पूर्ण

/*
 * hw मुक्त callback
 */
अटल पूर्णांक snd_cx23885_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु

	काष्ठा cx23885_audio_dev *chip = snd_pcm_substream_chip(substream);

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prepare callback
 */
अटल पूर्णांक snd_cx23885_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * trigger callback
 */
अटल पूर्णांक snd_cx23885_card_trigger(काष्ठा snd_pcm_substream *substream,
	पूर्णांक cmd)
अणु
	काष्ठा cx23885_audio_dev *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	/* Local पूर्णांकerrupts are alपढ़ोy disabled by ALSA */
	spin_lock(&chip->lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		err = cx23885_start_audio_dma(chip);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		err = cx23885_stop_audio_dma(chip);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock(&chip->lock);

	वापस err;
पूर्ण

/*
 * poपूर्णांकer callback
 */
अटल snd_pcm_uframes_t snd_cx23885_poपूर्णांकer(
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx23885_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u16 count;

	count = atomic_पढ़ो(&chip->count);

	वापस runसमय->period_size * (count & (runसमय->periods-1));
पूर्ण

/*
 * page callback (needed क्रम mmap)
 */
अटल काष्ठा page *snd_cx23885_page(काष्ठा snd_pcm_substream *substream,
				अचिन्हित दीर्घ offset)
अणु
	व्योम *pageptr = substream->runसमय->dma_area + offset;
	वापस vदो_स्मृति_to_page(pageptr);
पूर्ण

/*
 * चालकs
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_cx23885_pcm_ops = अणु
	.खोलो = snd_cx23885_pcm_खोलो,
	.बंद = snd_cx23885_बंद,
	.hw_params = snd_cx23885_hw_params,
	.hw_मुक्त = snd_cx23885_hw_मुक्त,
	.prepare = snd_cx23885_prepare,
	.trigger = snd_cx23885_card_trigger,
	.poपूर्णांकer = snd_cx23885_poपूर्णांकer,
	.page = snd_cx23885_page,
पूर्ण;

/*
 * create a PCM device
 */
अटल पूर्णांक snd_cx23885_pcm(काष्ठा cx23885_audio_dev *chip, पूर्णांक device,
	अक्षर *name)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	err = snd_pcm_new(chip->card, name, device, 0, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = chip;
	strscpy(pcm->name, name, माप(pcm->name));
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cx23885_pcm_ops);

	वापस 0;
पूर्ण

/****************************************************************************
			Basic Flow क्रम Sound Devices
 ****************************************************************************/

/*
 * Alsa Conकाष्ठाor - Component probe
 */

काष्ठा cx23885_audio_dev *cx23885_audio_रेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा cx23885_audio_dev *chip;
	पूर्णांक err;

	अगर (disable_analog_audio)
		वापस शून्य;

	अगर (dev->sram_channels[AUDIO_SRAM_CHANNEL].cmds_start == 0) अणु
		pr_warn("%s(): Missing SRAM channel configuration for analog TV Audio\n",
		       __func__);
		वापस शून्य;
	पूर्ण

	err = snd_card_new(&dev->pci->dev,
			   SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			THIS_MODULE, माप(काष्ठा cx23885_audio_dev), &card);
	अगर (err < 0)
		जाओ error;

	chip = (काष्ठा cx23885_audio_dev *) card->निजी_data;
	chip->dev = dev;
	chip->pci = dev->pci;
	chip->card = card;
	spin_lock_init(&chip->lock);

	err = snd_cx23885_pcm(chip, 0, "CX23885 Digital");
	अगर (err < 0)
		जाओ error;

	strscpy(card->driver, "CX23885", माप(card->driver));
	प्र_लिखो(card->लघुname, "Conexant CX23885");
	प्र_लिखो(card->दीर्घname, "%s at %s", card->लघुname, dev->name);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	dprपूर्णांकk(0, "registered ALSA audio device\n");

	वापस chip;

error:
	snd_card_मुक्त(card);
	pr_err("%s(): Failed to register analog audio adapter\n",
	       __func__);

	वापस शून्य;
पूर्ण

/*
 * ALSA deकाष्ठाor
 */
व्योम cx23885_audio_unरेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा cx23885_audio_dev *chip = dev->audio_dev;

	snd_card_मुक्त(chip->card);
पूर्ण
