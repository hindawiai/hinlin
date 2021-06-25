<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on SAA713x ALSA driver and CX88 driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "cx25821.h"
#समावेश "cx25821-reg.h"

#घोषणा AUDIO_SRAM_CHANNEL	SRAM_CH08

#घोषणा dprपूर्णांकk(level, fmt, arg...)				\
करो अणु								\
	अगर (debug >= level)					\
		pr_info("%s/1: " fmt, chip->dev->name, ##arg);	\
पूर्ण जबतक (0)
#घोषणा dprपूर्णांकk_core(level, fmt, arg...)				\
करो अणु									\
	अगर (debug >= level)						\
		prपूर्णांकk(KERN_DEBUG "%s/1: " fmt, chip->dev->name, ##arg); \
पूर्ण जबतक (0)

/****************************************************************************
	Data type declarations - Can be moded to a header file later
 ****************************************************************************/

अटल पूर्णांक devno;

काष्ठा cx25821_audio_buffer अणु
	अचिन्हित पूर्णांक bpl;
	काष्ठा cx25821_riscmem risc;
	व्योम			*vaddr;
	काष्ठा scatterlist	*sglist;
	पूर्णांक			sglen;
	अचिन्हित दीर्घ		nr_pages;
पूर्ण;

काष्ठा cx25821_audio_dev अणु
	काष्ठा cx25821_dev *dev;
	काष्ठा cx25821_dmaqueue q;

	/* pci i/o */
	काष्ठा pci_dev *pci;

	/* audio controls */
	पूर्णांक irq;

	काष्ठा snd_card *card;

	अचिन्हित दीर्घ iobase;
	spinlock_t reg_lock;
	atomic_t count;

	अचिन्हित पूर्णांक dma_size;
	अचिन्हित पूर्णांक period_size;
	अचिन्हित पूर्णांक num_periods;

	काष्ठा cx25821_audio_buffer *buf;

	काष्ठा snd_pcm_substream *substream;
पूर्ण;


/****************************************************************************
			Module global अटल vars
 ****************************************************************************/

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable cx25821 soundcard. default enabled.");

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for cx25821 capture interface(s).");

/****************************************************************************
				Module macros
 ****************************************************************************/

MODULE_DESCRIPTION("ALSA driver module for cx25821 based capture cards");
MODULE_AUTHOR("Hiep Huynh");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

/****************************************************************************
			Module specअगरic functions
 ****************************************************************************/
/* Constants taken from cx88-reg.h */
#घोषणा AUD_INT_DN_RISCI1       (1 <<  0)
#घोषणा AUD_INT_UP_RISCI1       (1 <<  1)
#घोषणा AUD_INT_RDS_DN_RISCI1   (1 <<  2)
#घोषणा AUD_INT_DN_RISCI2       (1 <<  4)	/* yes, 3 is skipped */
#घोषणा AUD_INT_UP_RISCI2       (1 <<  5)
#घोषणा AUD_INT_RDS_DN_RISCI2   (1 <<  6)
#घोषणा AUD_INT_DN_SYNC         (1 << 12)
#घोषणा AUD_INT_UP_SYNC         (1 << 13)
#घोषणा AUD_INT_RDS_DN_SYNC     (1 << 14)
#घोषणा AUD_INT_OPC_ERR         (1 << 16)
#घोषणा AUD_INT_BER_IRQ         (1 << 20)
#घोषणा AUD_INT_MCHG_IRQ        (1 << 21)
#घोषणा GP_COUNT_CONTROL_RESET	0x3

#घोषणा PCI_MSK_AUD_EXT   (1 <<  4)
#घोषणा PCI_MSK_AUD_INT   (1 <<  3)

अटल पूर्णांक cx25821_alsa_dma_init(काष्ठा cx25821_audio_dev *chip,
				 अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा cx25821_audio_buffer *buf = chip->buf;
	काष्ठा page *pg;
	पूर्णांक i;

	buf->vaddr = vदो_स्मृति_32(nr_pages << PAGE_SHIFT);
	अगर (शून्य == buf->vaddr) अणु
		dprपूर्णांकk(1, "vmalloc_32(%lu pages) failed\n", nr_pages);
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(1, "vmalloc is at addr 0x%p, size=%lu\n",
				buf->vaddr,
				nr_pages << PAGE_SHIFT);

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

अटल पूर्णांक cx25821_alsa_dma_map(काष्ठा cx25821_audio_dev *dev)
अणु
	काष्ठा cx25821_audio_buffer *buf = dev->buf;

	buf->sglen = dma_map_sg(&dev->pci->dev, buf->sglist,
			buf->nr_pages, DMA_FROM_DEVICE);

	अगर (0 == buf->sglen) अणु
		pr_warn("%s: cx25821_alsa_map_sg failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_alsa_dma_unmap(काष्ठा cx25821_audio_dev *dev)
अणु
	काष्ठा cx25821_audio_buffer *buf = dev->buf;

	अगर (!buf->sglen)
		वापस 0;

	dma_unmap_sg(&dev->pci->dev, buf->sglist, buf->nr_pages, DMA_FROM_DEVICE);
	buf->sglen = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_alsa_dma_मुक्त(काष्ठा cx25821_audio_buffer *buf)
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

अटल पूर्णांक _cx25821_start_audio_dma(काष्ठा cx25821_audio_dev *chip)
अणु
	काष्ठा cx25821_audio_buffer *buf = chip->buf;
	काष्ठा cx25821_dev *dev = chip->dev;
	स्थिर काष्ठा sram_channel *audio_ch =
	    &cx25821_sram_channels[AUDIO_SRAM_CHANNEL];
	u32 पंचांगp = 0;

	/* enable output on the GPIO 0 क्रम the MCLK ADC (Audio) */
	cx25821_set_gpiopin_direction(chip->dev, 0, 0);

	/* Make sure RISC/FIFO are off beक्रमe changing FIFO/RISC settings */
	cx_clear(AUD_INT_DMA_CTL,
		 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);

	/* setup fअगरo + क्रमmat - out channel */
	cx25821_sram_channel_setup_audio(chip->dev, audio_ch, buf->bpl,
					 buf->risc.dma);

	/* sets bpl size */
	cx_ग_लिखो(AUD_A_LNGTH, buf->bpl);

	/* reset counter */
	/* GP_COUNT_CONTROL_RESET = 0x3 */
	cx_ग_लिखो(AUD_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
	atomic_set(&chip->count, 0);

	/* Set the input mode to 16-bit */
	पंचांगp = cx_पढ़ो(AUD_A_CFG);
	cx_ग_लिखो(AUD_A_CFG, पंचांगp | FLD_AUD_DST_PK_MODE | FLD_AUD_DST_ENABLE |
		 FLD_AUD_CLK_ENABLE);

	/*
	pr_info("DEBUG: Start audio DMA, %d B/line, cmds_start(0x%x)= %d lines/FIFO, %d periods, %d byte buffer\n",
		buf->bpl, audio_ch->cmds_start,
		cx_पढ़ो(audio_ch->cmds_start + 12)>>1,
		chip->num_periods, buf->bpl * chip->num_periods);
	*/

	/* Enables corresponding bits at AUD_INT_STAT */
	cx_ग_लिखो(AUD_A_INT_MSK, FLD_AUD_DST_RISCI1 | FLD_AUD_DST_OF |
		 FLD_AUD_DST_SYNC | FLD_AUD_DST_OPC_ERR);

	/* Clean any pending पूर्णांकerrupt bits alपढ़ोy set */
	cx_ग_लिखो(AUD_A_INT_STAT, ~0);

	/* enable audio irqs */
	cx_set(PCI_INT_MSK, chip->dev->pci_irqmask | PCI_MSK_AUD_INT);

	/* Turn on audio करोwnstream fअगरo and risc enable 0x101 */
	पंचांगp = cx_पढ़ो(AUD_INT_DMA_CTL);
	cx_set(AUD_INT_DMA_CTL, पंचांगp |
	       (FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN));

	mdelay(100);
	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Resets audio DMA
 */
अटल पूर्णांक _cx25821_stop_audio_dma(काष्ठा cx25821_audio_dev *chip)
अणु
	काष्ठा cx25821_dev *dev = chip->dev;

	/* stop dma */
	cx_clear(AUD_INT_DMA_CTL,
		 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);

	/* disable irqs */
	cx_clear(PCI_INT_MSK, PCI_MSK_AUD_INT);
	cx_clear(AUD_A_INT_MSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
		 AUD_INT_DN_RISCI2 | AUD_INT_DN_RISCI1);

	वापस 0;
पूर्ण

#घोषणा MAX_IRQ_LOOP 50

/*
 * BOARD Specअगरic: IRQ dma bits
 */
अटल अक्षर *cx25821_aud_irqs[32] = अणु
	"dn_risci1", "up_risci1", "rds_dn_risc1",	/* 0-2 */
	शून्य,						/* reserved */
	"dn_risci2", "up_risci2", "rds_dn_risc2",	/* 4-6 */
	शून्य,						/* reserved */
	"dnf_of", "upf_uf", "rds_dnf_uf",		/* 8-10 */
	शून्य,						/* reserved */
	"dn_sync", "up_sync", "rds_dn_sync",		/* 12-14 */
	शून्य,						/* reserved */
	"opc_err", "par_err", "rip_err",		/* 16-18 */
	"pci_abort", "ber_irq", "mchg_irq"		/* 19-21 */
पूर्ण;

/*
 * BOARD Specअगरic: Threats IRQ audio specअगरic calls
 */
अटल व्योम cx25821_aud_irq(काष्ठा cx25821_audio_dev *chip, u32 status,
			    u32 mask)
अणु
	काष्ठा cx25821_dev *dev = chip->dev;

	अगर (0 == (status & mask))
		वापस;

	cx_ग_लिखो(AUD_A_INT_STAT, status);
	अगर (debug > 1 || (status & mask & ~0xff))
		cx25821_prपूर्णांक_irqbits(dev->name, "irq aud", cx25821_aud_irqs,
				ARRAY_SIZE(cx25821_aud_irqs), status, mask);

	/* risc op code error */
	अगर (status & AUD_INT_OPC_ERR) अणु
		pr_warn("WARNING %s/1: Audio risc op code error\n", dev->name);

		cx_clear(AUD_INT_DMA_CTL,
			 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);
		cx25821_sram_channel_dump_audio(dev,
				&cx25821_sram_channels[AUDIO_SRAM_CHANNEL]);
	पूर्ण
	अगर (status & AUD_INT_DN_SYNC) अणु
		pr_warn("WARNING %s: Downstream sync error!\n", dev->name);
		cx_ग_लिखो(AUD_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
		वापस;
	पूर्ण

	/* risc1 करोwnstream */
	अगर (status & AUD_INT_DN_RISCI1) अणु
		atomic_set(&chip->count, cx_पढ़ो(AUD_A_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	पूर्ण
पूर्ण

/*
 * BOARD Specअगरic: Handles IRQ calls
 */
अटल irqवापस_t cx25821_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx25821_audio_dev *chip = dev_id;
	काष्ठा cx25821_dev *dev = chip->dev;
	u32 status, pci_status;
	u32 audपूर्णांक_status, audपूर्णांक_mask;
	पूर्णांक loop, handled = 0;

	audपूर्णांक_status = cx_पढ़ो(AUD_A_INT_STAT);
	audपूर्णांक_mask = cx_पढ़ो(AUD_A_INT_MSK);
	status = cx_पढ़ो(PCI_INT_STAT);

	क्रम (loop = 0; loop < 1; loop++) अणु
		status = cx_पढ़ो(PCI_INT_STAT);
		अगर (0 == status) अणु
			status = cx_पढ़ो(PCI_INT_STAT);
			audपूर्णांक_status = cx_पढ़ो(AUD_A_INT_STAT);
			audपूर्णांक_mask = cx_पढ़ो(AUD_A_INT_MSK);

			अगर (status) अणु
				handled = 1;
				cx_ग_लिखो(PCI_INT_STAT, status);

				cx25821_aud_irq(chip, audपूर्णांक_status,
						audपूर्णांक_mask);
				अवरोध;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
		पूर्ण

		handled = 1;
		cx_ग_लिखो(PCI_INT_STAT, status);

		cx25821_aud_irq(chip, audपूर्णांक_status, audपूर्णांक_mask);
	पूर्ण

	pci_status = cx_पढ़ो(PCI_INT_STAT);

	अगर (handled)
		cx_ग_लिखो(PCI_INT_STAT, pci_status);

out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक dsp_buffer_मुक्त(काष्ठा cx25821_audio_dev *chip)
अणु
	काष्ठा cx25821_riscmem *risc = &chip->buf->risc;

	BUG_ON(!chip->dma_size);

	dprपूर्णांकk(2, "Freeing buffer\n");
	cx25821_alsa_dma_unmap(chip);
	cx25821_alsa_dma_मुक्त(chip->buf);
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
#घोषणा DEFAULT_FIFO_SIZE	384
अटल स्थिर काष्ठा snd_pcm_hardware snd_cx25821_digital_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	/* Analog audio output will be full of clicks and pops अगर there
	   are not exactly four lines in the SRAM FIFO buffer.  */
	.period_bytes_min = DEFAULT_FIFO_SIZE / 3,
	.period_bytes_max = DEFAULT_FIFO_SIZE / 3,
	.periods_min = 1,
	.periods_max = AUDIO_LINE_SIZE,
	/* 128 * 128 = 16384 = 1024 * 16 */
	.buffer_bytes_max = (AUDIO_LINE_SIZE * AUDIO_LINE_SIZE),
पूर्ण;

/*
 * audio pcm capture खोलो callback
 */
अटल पूर्णांक snd_cx25821_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	अचिन्हित पूर्णांक bpl = 0;

	अगर (!chip) अणु
		pr_err("DEBUG: cx25821 can't find device struct. Can't proceed with open\n");
		वापस -ENODEV;
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ _error;

	chip->substream = substream;

	runसमय->hw = snd_cx25821_digital_hw;

	अगर (cx25821_sram_channels[AUDIO_SRAM_CHANNEL].fअगरo_size !=
	    DEFAULT_FIFO_SIZE) अणु
		/* since there are 3 audio Clusters */
		bpl = cx25821_sram_channels[AUDIO_SRAM_CHANNEL].fअगरo_size / 3;
		bpl &= ~7;	/* must be multiple of 8 */

		अगर (bpl > AUDIO_LINE_SIZE)
			bpl = AUDIO_LINE_SIZE;

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
अटल पूर्णांक snd_cx25821_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * hw_params callback
 */
अटल पूर्णांक snd_cx25821_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा cx25821_audio_buffer *buf;
	पूर्णांक ret;

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	chip->period_size = params_period_bytes(hw_params);
	chip->num_periods = params_periods(hw_params);
	chip->dma_size = chip->period_size * params_periods(hw_params);

	BUG_ON(!chip->dma_size);
	BUG_ON(chip->num_periods & (chip->num_periods - 1));

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (शून्य == buf)
		वापस -ENOMEM;

	अगर (chip->period_size > AUDIO_LINE_SIZE)
		chip->period_size = AUDIO_LINE_SIZE;

	buf->bpl = chip->period_size;
	chip->buf = buf;

	ret = cx25821_alsa_dma_init(chip,
			(PAGE_ALIGN(chip->dma_size) >> PAGE_SHIFT));
	अगर (ret < 0)
		जाओ error;

	ret = cx25821_alsa_dma_map(chip);
	अगर (ret < 0)
		जाओ error;

	ret = cx25821_risc_databuffer_audio(chip->pci, &buf->risc, buf->sglist,
			chip->period_size, chip->num_periods, 1);
	अगर (ret < 0) अणु
		pr_info("DEBUG: ERROR after cx25821_risc_databuffer_audio()\n");
		जाओ error;
	पूर्ण

	/* Loop back to start of program */
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_IRQ1 | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
	buf->risc.jmp[2] = cpu_to_le32(0);	/* bits 63-32 */

	substream->runसमय->dma_area = chip->buf->vaddr;
	substream->runसमय->dma_bytes = chip->dma_size;
	substream->runसमय->dma_addr = 0;

	वापस 0;

error:
	chip->buf = शून्य;
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * hw मुक्त callback
 */
अटल पूर्णांक snd_cx25821_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prepare callback
 */
अटल पूर्णांक snd_cx25821_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * trigger callback
 */
अटल पूर्णांक snd_cx25821_card_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err = 0;

	/* Local पूर्णांकerrupts are alपढ़ोy disabled by ALSA */
	spin_lock(&chip->reg_lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		err = _cx25821_start_audio_dma(chip);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		err = _cx25821_stop_audio_dma(chip);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock(&chip->reg_lock);

	वापस err;
पूर्ण

/*
 * poपूर्णांकer callback
 */
अटल snd_pcm_uframes_t snd_cx25821_poपूर्णांकer(काष्ठा snd_pcm_substream
					     *substream)
अणु
	काष्ठा cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u16 count;

	count = atomic_पढ़ो(&chip->count);

	वापस runसमय->period_size * (count & (runसमय->periods - 1));
पूर्ण

/*
 * page callback (needed क्रम mmap)
 */
अटल काष्ठा page *snd_cx25821_page(काष्ठा snd_pcm_substream *substream,
				     अचिन्हित दीर्घ offset)
अणु
	व्योम *pageptr = substream->runसमय->dma_area + offset;

	वापस vदो_स्मृति_to_page(pageptr);
पूर्ण

/*
 * चालकs
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_cx25821_pcm_ops = अणु
	.खोलो = snd_cx25821_pcm_खोलो,
	.बंद = snd_cx25821_बंद,
	.hw_params = snd_cx25821_hw_params,
	.hw_मुक्त = snd_cx25821_hw_मुक्त,
	.prepare = snd_cx25821_prepare,
	.trigger = snd_cx25821_card_trigger,
	.poपूर्णांकer = snd_cx25821_poपूर्णांकer,
	.page = snd_cx25821_page,
पूर्ण;

/*
 * ALSA create a PCM device:  Called when initializing the board.
 * Sets up the name and hooks up the callbacks
 */
अटल पूर्णांक snd_cx25821_pcm(काष्ठा cx25821_audio_dev *chip, पूर्णांक device,
			   अक्षर *name)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, name, device, 0, 1, &pcm);
	अगर (err < 0) अणु
		pr_info("ERROR: FAILED snd_pcm_new() in %s\n", __func__);
		वापस err;
	पूर्ण
	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	strscpy(pcm->name, name, माप(pcm->name));
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cx25821_pcm_ops);

	वापस 0;
पूर्ण

/****************************************************************************
			Basic Flow क्रम Sound Devices
 ****************************************************************************/

/*
 * PCI ID Table - 14f1:8801 and 14f1:8811 means function 1: Audio
 * Only boards with eeprom and byte 1 at eeprom=1 have it
 */

अटल स्थिर काष्ठा pci_device_id __maybe_unused cx25821_audio_pci_tbl[] = अणु
	अणु0x14f1, 0x0920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cx25821_audio_pci_tbl);

/*
 * Alsa Conकाष्ठाor - Component probe
 */
अटल पूर्णांक cx25821_audio_initdev(काष्ठा cx25821_dev *dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा cx25821_audio_dev *chip;
	पूर्णांक err;

	अगर (devno >= SNDRV_CARDS) अणु
		pr_info("DEBUG ERROR: devno >= SNDRV_CARDS %s\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!enable[devno]) अणु
		++devno;
		pr_info("DEBUG ERROR: !enable[devno] %s\n", __func__);
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&dev->pci->dev, index[devno], id[devno],
			   THIS_MODULE,
			   माप(काष्ठा cx25821_audio_dev), &card);
	अगर (err < 0) अणु
		pr_info("DEBUG ERROR: cannot create snd_card_new in %s\n",
			__func__);
		वापस err;
	पूर्ण

	strscpy(card->driver, "cx25821", माप(card->driver));

	/* Card "creation" */
	chip = card->निजी_data;
	spin_lock_init(&chip->reg_lock);

	chip->dev = dev;
	chip->card = card;
	chip->pci = dev->pci;
	chip->iobase = pci_resource_start(dev->pci, 0);

	chip->irq = dev->pci->irq;

	err = request_irq(dev->pci->irq, cx25821_irq,
			  IRQF_SHARED, chip->dev->name, chip);

	अगर (err < 0) अणु
		pr_err("ERROR %s: can't get IRQ %d for ALSA\n", chip->dev->name,
			dev->pci->irq);
		जाओ error;
	पूर्ण

	err = snd_cx25821_pcm(chip, 0, "cx25821 Digital");
	अगर (err < 0) अणु
		pr_info("DEBUG ERROR: cannot create snd_cx25821_pcm %s\n",
			__func__);
		जाओ error;
	पूर्ण

	strscpy(card->लघुname, "cx25821", माप(card->लघुname));
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %d", chip->dev->name,
		chip->iobase, chip->irq);
	strscpy(card->mixername, "CX25821", माप(card->mixername));

	pr_info("%s/%i: ALSA support for cx25821 boards\n", card->driver,
		devno);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		pr_info("DEBUG ERROR: cannot register sound card %s\n",
			__func__);
		जाओ error;
	पूर्ण

	dev->card = card;
	devno++;
	वापस 0;

error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

/****************************************************************************
				LINUX MODULE INIT
 ****************************************************************************/

अटल पूर्णांक cx25821_alsa_निकास_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा cx25821_dev *cxdev = get_cx25821(v4l2_dev);

	snd_card_मुक्त(cxdev->card);
	वापस 0;
पूर्ण

अटल व्योम cx25821_audio_fini(व्योम)
अणु
	काष्ठा device_driver *drv = driver_find("cx25821", &pci_bus_type);
	पूर्णांक ret;

	ret = driver_क्रम_each_device(drv, शून्य, शून्य, cx25821_alsa_निकास_callback);
	अगर (ret)
		pr_err("%s failed to find a cx25821 driver.\n", __func__);
पूर्ण

अटल पूर्णांक cx25821_alsa_init_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा cx25821_dev *cxdev = get_cx25821(v4l2_dev);

	cx25821_audio_initdev(cxdev);
	वापस 0;
पूर्ण

/*
 * Module initializer
 *
 * Loops through present saa7134 cards, and assigns an ALSA device
 * to each one
 *
 */
अटल पूर्णांक cx25821_alsa_init(व्योम)
अणु
	काष्ठा device_driver *drv = driver_find("cx25821", &pci_bus_type);

	वापस driver_क्रम_each_device(drv, शून्य, शून्य, cx25821_alsa_init_callback);

पूर्ण

late_initcall(cx25821_alsa_init);
module_निकास(cx25821_audio_fini);
