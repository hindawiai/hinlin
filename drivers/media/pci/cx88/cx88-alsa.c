<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम audio capture
 *  PCI function #1 of the cx2388x.
 *
 *    (c) 2007 Trent Piepho <xyzzy@speakeasy.org>
 *    (c) 2005,2006 Ricarकरो Cerqueira <v4l@cerqueira.org>
 *    (c) 2005 Mauro Carvalho Chehab <mchehab@kernel.org>
 *    Based on a dummy cx88 module by Gerd Knorr <kraxel@bytesex.org>
 *    Based on dummy.c by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश "cx88.h"
#समावेश "cx88-reg.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <media/i2c/wm8775.h>

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug + 1 > level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: alsa: " fmt),		\
			chip->core->name, ##arg);			\
पूर्ण जबतक (0)

/*
 * Data type declarations - Can be moded to a header file later
 */

काष्ठा cx88_audio_buffer अणु
	अचिन्हित पूर्णांक		bpl;
	काष्ठा cx88_riscmem	risc;
	व्योम			*vaddr;
	काष्ठा scatterlist	*sglist;
	पूर्णांक                     sglen;
	अचिन्हित दीर्घ		nr_pages;
पूर्ण;

काष्ठा cx88_audio_dev अणु
	काष्ठा cx88_core           *core;
	काष्ठा cx88_dmaqueue       q;

	/* pci i/o */
	काष्ठा pci_dev             *pci;

	/* audio controls */
	पूर्णांक                        irq;

	काष्ठा snd_card            *card;

	spinlock_t                 reg_lock;
	atomic_t		   count;

	अचिन्हित पूर्णांक               dma_size;
	अचिन्हित पूर्णांक               period_size;
	अचिन्हित पूर्णांक               num_periods;

	काष्ठा cx88_audio_buffer   *buf;

	काष्ठा snd_pcm_substream   *substream;
पूर्ण;

/*
 * Module global अटल vars
 */

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल स्थिर अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable cx88x soundcard. default enabled.");

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for cx88x capture interface(s).");

/*
 * Module macros
 */

MODULE_DESCRIPTION("ALSA driver module for cx2388x based TV cards");
MODULE_AUTHOR("Ricardo Cerqueira");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(CX88_VERSION);

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

/*
 * Module specअगरic functions
 */

/*
 * BOARD Specअगरic: Sets audio DMA
 */

अटल पूर्णांक _cx88_start_audio_dma(काष्ठा cx88_audio_dev *chip)
अणु
	काष्ठा cx88_audio_buffer *buf = chip->buf;
	काष्ठा cx88_core *core = chip->core;
	स्थिर काष्ठा sram_channel *audio_ch = &cx88_sram_channels[SRAM_CH25];

	/* Make sure RISC/FIFO are off beक्रमe changing FIFO/RISC settings */
	cx_clear(MO_AUD_DMACNTRL, 0x11);

	/* setup fअगरo + क्रमmat - out channel */
	cx88_sram_channel_setup(chip->core, audio_ch, buf->bpl, buf->risc.dma);

	/* sets bpl size */
	cx_ग_लिखो(MO_AUDD_LNGTH, buf->bpl);

	/* reset counter */
	cx_ग_लिखो(MO_AUDD_GPCNTRL, GP_COUNT_CONTROL_RESET);
	atomic_set(&chip->count, 0);

	dprपूर्णांकk(1,
		"Start audio DMA, %d B/line, %d lines/FIFO, %d periods, %d byte buffer\n",
		buf->bpl, cx_पढ़ो(audio_ch->cmds_start + 8) >> 1,
		chip->num_periods, buf->bpl * chip->num_periods);

	/* Enables corresponding bits at AUD_INT_STAT */
	cx_ग_लिखो(MO_AUD_INTMSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				AUD_INT_DN_RISCI2 | AUD_INT_DN_RISCI1);

	/* Clean any pending पूर्णांकerrupt bits alपढ़ोy set */
	cx_ग_लिखो(MO_AUD_INTSTAT, ~0);

	/* enable audio irqs */
	cx_set(MO_PCI_INTMSK, chip->core->pci_irqmask | PCI_INT_AUDINT);

	/* start dma */

	/* Enables Risc Processor */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	/* audio करोwnstream FIFO and RISC enable */
	cx_set(MO_AUD_DMACNTRL, 0x11);

	अगर (debug)
		cx88_sram_channel_dump(chip->core, audio_ch);

	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Resets audio DMA
 */
अटल पूर्णांक _cx88_stop_audio_dma(काष्ठा cx88_audio_dev *chip)
अणु
	काष्ठा cx88_core *core = chip->core;

	dprपूर्णांकk(1, "Stopping audio DMA\n");

	/* stop dma */
	cx_clear(MO_AUD_DMACNTRL, 0x11);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_AUDINT);
	cx_clear(MO_AUD_INTMSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				AUD_INT_DN_RISCI2 | AUD_INT_DN_RISCI1);

	अगर (debug)
		cx88_sram_channel_dump(chip->core,
				       &cx88_sram_channels[SRAM_CH25]);

	वापस 0;
पूर्ण

#घोषणा MAX_IRQ_LOOP 50

/*
 * BOARD Specअगरic: IRQ dma bits
 */
अटल स्थिर अक्षर *cx88_aud_irqs[32] = अणु
	"dn_risci1", "up_risci1", "rds_dn_risc1", /* 0-2 */
	शून्य,					  /* reserved */
	"dn_risci2", "up_risci2", "rds_dn_risc2", /* 4-6 */
	शून्य,					  /* reserved */
	"dnf_of", "upf_uf", "rds_dnf_uf",	  /* 8-10 */
	शून्य,					  /* reserved */
	"dn_sync", "up_sync", "rds_dn_sync",	  /* 12-14 */
	शून्य,					  /* reserved */
	"opc_err", "par_err", "rip_err",	  /* 16-18 */
	"pci_abort", "ber_irq", "mchg_irq"	  /* 19-21 */
पूर्ण;

/*
 * BOARD Specअगरic: Threats IRQ audio specअगरic calls
 */
अटल व्योम cx8801_aud_irq(काष्ठा cx88_audio_dev *chip)
अणु
	काष्ठा cx88_core *core = chip->core;
	u32 status, mask;

	status = cx_पढ़ो(MO_AUD_INTSTAT);
	mask   = cx_पढ़ो(MO_AUD_INTMSK);
	अगर (0 == (status & mask))
		वापस;
	cx_ग_लिखो(MO_AUD_INTSTAT, status);
	अगर (debug > 1  ||  (status & mask & ~0xff))
		cx88_prपूर्णांक_irqbits("irq aud",
				   cx88_aud_irqs, ARRAY_SIZE(cx88_aud_irqs),
				   status, mask);
	/* risc op code error */
	अगर (status & AUD_INT_OPC_ERR) अणु
		pr_warn("Audio risc op code error\n");
		cx_clear(MO_AUD_DMACNTRL, 0x11);
		cx88_sram_channel_dump(core, &cx88_sram_channels[SRAM_CH25]);
	पूर्ण
	अगर (status & AUD_INT_DN_SYNC) अणु
		dprपूर्णांकk(1, "Downstream sync error\n");
		cx_ग_लिखो(MO_AUDD_GPCNTRL, GP_COUNT_CONTROL_RESET);
		वापस;
	पूर्ण
	/* risc1 करोwnstream */
	अगर (status & AUD_INT_DN_RISCI1) अणु
		atomic_set(&chip->count, cx_पढ़ो(MO_AUDD_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	पूर्ण
	/* FIXME: Any other status should deserve a special handling? */
पूर्ण

/*
 * BOARD Specअगरic: Handles IRQ calls
 */
अटल irqवापस_t cx8801_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx88_audio_dev *chip = dev_id;
	काष्ठा cx88_core *core = chip->core;
	u32 status;
	पूर्णांक loop, handled = 0;

	क्रम (loop = 0; loop < MAX_IRQ_LOOP; loop++) अणु
		status = cx_पढ़ो(MO_PCI_INTSTAT) &
			(core->pci_irqmask | PCI_INT_AUDINT);
		अगर (status == 0)
			जाओ out;
		dprपूर्णांकk(3, "cx8801_irq loop %d/%d, status %x\n",
			loop, MAX_IRQ_LOOP, status);
		handled = 1;
		cx_ग_लिखो(MO_PCI_INTSTAT, status);

		अगर (status & core->pci_irqmask)
			cx88_core_irq(core, status);
		अगर (status & PCI_INT_AUDINT)
			cx8801_aud_irq(chip);
	पूर्ण

	अगर (loop == MAX_IRQ_LOOP) अणु
		pr_err("IRQ loop detected, disabling interrupts\n");
		cx_clear(MO_PCI_INTMSK, PCI_INT_AUDINT);
	पूर्ण

 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक cx88_alsa_dma_init(काष्ठा cx88_audio_dev *chip,
			      अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा cx88_audio_buffer *buf = chip->buf;
	काष्ठा page *pg;
	पूर्णांक i;

	buf->vaddr = vदो_स्मृति_32(nr_pages << PAGE_SHIFT);
	अगर (!buf->vaddr) अणु
		dprपूर्णांकk(1, "vmalloc_32(%lu pages) failed\n", nr_pages);
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(1, "vmalloc is at addr %p, size=%lu\n",
		buf->vaddr, nr_pages << PAGE_SHIFT);

	स_रखो(buf->vaddr, 0, nr_pages << PAGE_SHIFT);
	buf->nr_pages = nr_pages;

	buf->sglist = vzalloc(array_size(माप(*buf->sglist), buf->nr_pages));
	अगर (!buf->sglist)
		जाओ vzalloc_err;

	sg_init_table(buf->sglist, buf->nr_pages);
	क्रम (i = 0; i < buf->nr_pages; i++) अणु
		pg = vदो_स्मृति_to_page(buf->vaddr + i * PAGE_SIZE);
		अगर (!pg)
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

अटल पूर्णांक cx88_alsa_dma_map(काष्ठा cx88_audio_dev *dev)
अणु
	काष्ठा cx88_audio_buffer *buf = dev->buf;

	buf->sglen = dma_map_sg(&dev->pci->dev, buf->sglist,
			buf->nr_pages, DMA_FROM_DEVICE);

	अगर (buf->sglen == 0) अणु
		pr_warn("%s: cx88_alsa_map_sg failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx88_alsa_dma_unmap(काष्ठा cx88_audio_dev *dev)
अणु
	काष्ठा cx88_audio_buffer *buf = dev->buf;

	अगर (!buf->sglen)
		वापस 0;

	dma_unmap_sg(&dev->pci->dev, buf->sglist, buf->nr_pages,
		     DMA_FROM_DEVICE);
	buf->sglen = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx88_alsa_dma_मुक्त(काष्ठा cx88_audio_buffer *buf)
अणु
	vमुक्त(buf->sglist);
	buf->sglist = शून्य;
	vमुक्त(buf->vaddr);
	buf->vaddr = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक dsp_buffer_मुक्त(काष्ठा cx88_audio_dev *chip)
अणु
	काष्ठा cx88_riscmem *risc = &chip->buf->risc;

	WARN_ON(!chip->dma_size);

	dprपूर्णांकk(2, "Freeing buffer\n");
	cx88_alsa_dma_unmap(chip);
	cx88_alsa_dma_मुक्त(chip->buf);
	अगर (risc->cpu)
		pci_मुक्त_consistent(chip->pci, risc->size,
				    risc->cpu, risc->dma);
	kमुक्त(chip->buf);

	chip->buf = शून्य;

	वापस 0;
पूर्ण

/*
 * ALSA PCM Interface
 */

/*
 * Digital hardware definition
 */
#घोषणा DEFAULT_FIFO_SIZE	4096
अटल स्थिर काष्ठा snd_pcm_hardware snd_cx88_digital_hw = अणु
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
	/*
	 * Analog audio output will be full of clicks and pops अगर there
	 * are not exactly four lines in the SRAM FIFO buffer.
	 */
	.period_bytes_min = DEFAULT_FIFO_SIZE / 4,
	.period_bytes_max = DEFAULT_FIFO_SIZE / 4,
	.periods_min = 1,
	.periods_max = 1024,
	.buffer_bytes_max = (1024 * 1024),
पूर्ण;

/*
 * audio pcm capture खोलो callback
 */
अटल पूर्णांक snd_cx88_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx88_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर (!chip) अणु
		pr_err("BUG: cx88 can't find device struct. Can't proceed with open\n");
		वापस -ENODEV;
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ _error;

	chip->substream = substream;

	runसमय->hw = snd_cx88_digital_hw;

	अगर (cx88_sram_channels[SRAM_CH25].fअगरo_size != DEFAULT_FIFO_SIZE) अणु
		अचिन्हित पूर्णांक bpl = cx88_sram_channels[SRAM_CH25].fअगरo_size / 4;

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
अटल पूर्णांक snd_cx88_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * hw_params callback
 */
अटल पूर्णांक snd_cx88_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cx88_audio_dev *chip = snd_pcm_substream_chip(substream);

	काष्ठा cx88_audio_buffer *buf;
	पूर्णांक ret;

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	chip->period_size = params_period_bytes(hw_params);
	chip->num_periods = params_periods(hw_params);
	chip->dma_size = chip->period_size * params_periods(hw_params);

	WARN_ON(!chip->dma_size);
	WARN_ON(chip->num_periods & (chip->num_periods - 1));

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	chip->buf = buf;
	buf->bpl = chip->period_size;

	ret = cx88_alsa_dma_init(chip,
				 (PAGE_ALIGN(chip->dma_size) >> PAGE_SHIFT));
	अगर (ret < 0)
		जाओ error;

	ret = cx88_alsa_dma_map(chip);
	अगर (ret < 0)
		जाओ error;

	ret = cx88_risc_databuffer(chip->pci, &buf->risc, buf->sglist,
				   chip->period_size, chip->num_periods, 1);
	अगर (ret < 0)
		जाओ error;

	/* Loop back to start of program */
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_IRQ1 | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma);

	substream->runसमय->dma_area = chip->buf->vaddr;
	substream->runसमय->dma_bytes = chip->dma_size;
	substream->runसमय->dma_addr = 0;
	वापस 0;

error:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * hw मुक्त callback
 */
अटल पूर्णांक snd_cx88_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx88_audio_dev *chip = snd_pcm_substream_chip(substream);

	अगर (substream->runसमय->dma_area) अणु
		dsp_buffer_मुक्त(chip);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prepare callback
 */
अटल पूर्णांक snd_cx88_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * trigger callback
 */
अटल पूर्णांक snd_cx88_card_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा cx88_audio_dev *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	/* Local पूर्णांकerrupts are alपढ़ोy disabled by ALSA */
	spin_lock(&chip->reg_lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		err = _cx88_start_audio_dma(chip);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		err = _cx88_stop_audio_dma(chip);
		अवरोध;
	शेष:
		err =  -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock(&chip->reg_lock);

	वापस err;
पूर्ण

/*
 * poपूर्णांकer callback
 */
अटल snd_pcm_uframes_t snd_cx88_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx88_audio_dev *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u16 count;

	count = atomic_पढ़ो(&chip->count);

//	dprपूर्णांकk(2, "%s - count %d (+%u), period %d, frame %lu\n", __func__,
//		count, new, count & (runसमय->periods-1),
//		runसमय->period_size * (count & (runसमय->periods-1)));
	वापस runसमय->period_size * (count & (runसमय->periods - 1));
पूर्ण

/*
 * page callback (needed क्रम mmap)
 */
अटल काष्ठा page *snd_cx88_page(काष्ठा snd_pcm_substream *substream,
				  अचिन्हित दीर्घ offset)
अणु
	व्योम *pageptr = substream->runसमय->dma_area + offset;

	वापस vदो_स्मृति_to_page(pageptr);
पूर्ण

/*
 * चालकs
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_cx88_pcm_ops = अणु
	.खोलो = snd_cx88_pcm_खोलो,
	.बंद = snd_cx88_बंद,
	.hw_params = snd_cx88_hw_params,
	.hw_मुक्त = snd_cx88_hw_मुक्त,
	.prepare = snd_cx88_prepare,
	.trigger = snd_cx88_card_trigger,
	.poपूर्णांकer = snd_cx88_poपूर्णांकer,
	.page = snd_cx88_page,
पूर्ण;

/*
 * create a PCM device
 */
अटल पूर्णांक snd_cx88_pcm(काष्ठा cx88_audio_dev *chip, पूर्णांक device,
			स्थिर अक्षर *name)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	err = snd_pcm_new(chip->card, name, device, 0, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = chip;
	strscpy(pcm->name, name, माप(pcm->name));
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cx88_pcm_ops);

	वापस 0;
पूर्ण

/*
 * CONTROL INTERFACE
 */
अटल पूर्णांक snd_cx88_volume_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 0x3f;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx88_volume_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	पूर्णांक vol = 0x3f - (cx_पढ़ो(AUD_VOL_CTL) & 0x3f),
	    bal = cx_पढ़ो(AUD_BAL_CTL);

	value->value.पूर्णांकeger.value[(bal & 0x40) ? 0 : 1] = vol;
	vol -= (bal & 0x3f);
	value->value.पूर्णांकeger.value[(bal & 0x40) ? 1 : 0] = vol < 0 ? 0 : vol;

	वापस 0;
पूर्ण

अटल व्योम snd_cx88_wm8775_volume_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	u16 left = value->value.पूर्णांकeger.value[0];
	u16 right = value->value.पूर्णांकeger.value[1];
	पूर्णांक v, b;

	/* Pass volume & balance onto any WM8775 */
	अगर (left >= right) अणु
		v = left << 10;
		b = left ? (0x8000 * right) / left : 0x8000;
	पूर्ण अन्यथा अणु
		v = right << 10;
		b = right ? 0xffff - (0x8000 * left) / right : 0x8000;
	पूर्ण
	wm8775_s_ctrl(core, V4L2_CID_AUDIO_VOLUME, v);
	wm8775_s_ctrl(core, V4L2_CID_AUDIO_BALANCE, b);
पूर्ण

/* OK - TODO: test it */
अटल पूर्णांक snd_cx88_volume_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	पूर्णांक left, right, v, b;
	पूर्णांक changed = 0;
	u32 old;

	अगर (core->sd_wm8775)
		snd_cx88_wm8775_volume_put(kcontrol, value);

	left = value->value.पूर्णांकeger.value[0] & 0x3f;
	right = value->value.पूर्णांकeger.value[1] & 0x3f;
	b = right - left;
	अगर (b < 0) अणु
		v = 0x3f - left;
		b = (-b) | 0x40;
	पूर्ण अन्यथा अणु
		v = 0x3f - right;
	पूर्ण
	/* Do we really know this will always be called with IRQs on? */
	spin_lock_irq(&chip->reg_lock);
	old = cx_पढ़ो(AUD_VOL_CTL);
	अगर (v != (old & 0x3f)) अणु
		cx_sग_लिखो(SHADOW_AUD_VOL_CTL, AUD_VOL_CTL, (old & ~0x3f) | v);
		changed = 1;
	पूर्ण
	अगर ((cx_पढ़ो(AUD_BAL_CTL) & 0x7f) != b) अणु
		cx_ग_लिखो(AUD_BAL_CTL, b);
		changed = 1;
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);

	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(snd_cx88_db_scale, -6300, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_cx88_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.name = "Analog-TV Volume",
	.info = snd_cx88_volume_info,
	.get = snd_cx88_volume_get,
	.put = snd_cx88_volume_put,
	.tlv.p = snd_cx88_db_scale,
पूर्ण;

अटल पूर्णांक snd_cx88_चयन_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	u32 bit = kcontrol->निजी_value;

	value->value.पूर्णांकeger.value[0] = !(cx_पढ़ो(AUD_VOL_CTL) & bit);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx88_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	u32 bit = kcontrol->निजी_value;
	पूर्णांक ret = 0;
	u32 vol;

	spin_lock_irq(&chip->reg_lock);
	vol = cx_पढ़ो(AUD_VOL_CTL);
	अगर (value->value.पूर्णांकeger.value[0] != !(vol & bit)) अणु
		vol ^= bit;
		cx_sग_लिखो(SHADOW_AUD_VOL_CTL, AUD_VOL_CTL, vol);
		/* Pass mute onto any WM8775 */
		अगर (core->sd_wm8775 && ((1 << 6) == bit))
			wm8775_s_ctrl(core,
				      V4L2_CID_AUDIO_MUTE, 0 != (vol & bit));
		ret = 1;
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cx88_dac_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Audio-Out Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_cx88_चयन_get,
	.put = snd_cx88_चयन_put,
	.निजी_value = (1 << 8),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_cx88_source_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Analog-TV Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_cx88_चयन_get,
	.put = snd_cx88_चयन_put,
	.निजी_value = (1 << 6),
पूर्ण;

अटल पूर्णांक snd_cx88_alc_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;
	s32 val;

	val = wm8775_g_ctrl(core, V4L2_CID_AUDIO_LOUDNESS);
	value->value.पूर्णांकeger.value[0] = val ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx88_alc_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा cx88_core *core = chip->core;

	wm8775_s_ctrl(core, V4L2_CID_AUDIO_LOUDNESS,
		      value->value.पूर्णांकeger.value[0] != 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cx88_alc_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line-In ALC Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_cx88_alc_get,
	.put = snd_cx88_alc_put,
पूर्ण;

/*
 * Basic Flow क्रम Sound Devices
 */

/*
 * PCI ID Table - 14f1:8801 and 14f1:8811 means function 1: Audio
 * Only boards with eeprom and byte 1 at eeprom=1 have it
 */

अटल स्थिर काष्ठा pci_device_id cx88_audio_pci_tbl[] = अणु
	अणु0x14f1, 0x8801, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0x14f1, 0x8811, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cx88_audio_pci_tbl);

/*
 * Chip-specअगरic deकाष्ठाor
 */

अटल पूर्णांक snd_cx88_मुक्त(काष्ठा cx88_audio_dev *chip)
अणु
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	cx88_core_put(chip->core, chip->pci);

	pci_disable_device(chip->pci);
	वापस 0;
पूर्ण

/*
 * Component Deकाष्ठाor
 */
अटल व्योम snd_cx88_dev_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा cx88_audio_dev *chip = card->निजी_data;

	snd_cx88_मुक्त(chip);
पूर्ण

/*
 * Alsa Conकाष्ठाor - Component probe
 */

अटल पूर्णांक devno;
अटल पूर्णांक snd_cx88_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
			   काष्ठा cx88_audio_dev **rchip,
			   काष्ठा cx88_core **core_ptr)
अणु
	काष्ठा cx88_audio_dev	*chip;
	काष्ठा cx88_core	*core;
	पूर्णांक			err;
	अचिन्हित अक्षर		pci_lat;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	pci_set_master(pci);

	chip = card->निजी_data;

	core = cx88_core_get(pci);
	अगर (!core) अणु
		err = -EINVAL;
		वापस err;
	पूर्ण

	err = pci_set_dma_mask(pci, DMA_BIT_MASK(32));
	अगर (err) अणु
		dprपूर्णांकk(0, "%s/1: Oops: no 32bit PCI DMA ???\n", core->name);
		cx88_core_put(core, pci);
		वापस err;
	पूर्ण

	/* pci init */
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	spin_lock_init(&chip->reg_lock);

	chip->core = core;

	/* get irq */
	err = request_irq(chip->pci->irq, cx8801_irq,
			  IRQF_SHARED, chip->core->name, chip);
	अगर (err < 0) अणु
		dprपूर्णांकk(0, "%s: can't get IRQ %d\n",
			chip->core->name, chip->pci->irq);
		वापस err;
	पूर्ण

	/* prपूर्णांक pci info */
	pci_पढ़ो_config_byte(pci, PCI_LATENCY_TIMER, &pci_lat);

	dprपूर्णांकk(1,
		"ALSA %s/%i: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		core->name, devno,
		pci_name(pci), pci->revision, pci->irq,
		pci_lat, (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci, 0));

	chip->irq = pci->irq;
	synchronize_irq(chip->irq);

	*rchip = chip;
	*core_ptr = core;

	वापस 0;
पूर्ण

अटल पूर्णांक cx88_audio_initdev(काष्ठा pci_dev *pci,
			      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card		*card;
	काष्ठा cx88_audio_dev	*chip;
	काष्ठा cx88_core	*core = शून्य;
	पूर्णांक			err;

	अगर (devno >= SNDRV_CARDS)
		वापस (-ENODEV);

	अगर (!enable[devno]) अणु
		++devno;
		वापस (-ENOENT);
	पूर्ण

	err = snd_card_new(&pci->dev, index[devno], id[devno], THIS_MODULE,
			   माप(काष्ठा cx88_audio_dev), &card);
	अगर (err < 0)
		वापस err;

	card->निजी_मुक्त = snd_cx88_dev_मुक्त;

	err = snd_cx88_create(card, pci, &chip, &core);
	अगर (err < 0)
		जाओ error;

	err = snd_cx88_pcm(chip, 0, "CX88 Digital");
	अगर (err < 0)
		जाओ error;

	err = snd_ctl_add(card, snd_ctl_new1(&snd_cx88_volume, chip));
	अगर (err < 0)
		जाओ error;
	err = snd_ctl_add(card, snd_ctl_new1(&snd_cx88_dac_चयन, chip));
	अगर (err < 0)
		जाओ error;
	err = snd_ctl_add(card, snd_ctl_new1(&snd_cx88_source_चयन, chip));
	अगर (err < 0)
		जाओ error;

	/* If there's a wm8775 then add a Line-In ALC चयन */
	अगर (core->sd_wm8775) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_cx88_alc_चयन, chip));
		अगर (err < 0)
			जाओ error;
	पूर्ण

	strscpy(card->driver, "CX88x", माप(card->driver));
	प्र_लिखो(card->लघुname, "Conexant CX%x", pci->device);
	प्र_लिखो(card->दीर्घname, "%s at %#llx",
		card->लघुname,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci, 0));
	strscpy(card->mixername, "CX88", माप(card->mixername));

	dprपूर्णांकk(0, "%s/%i: ALSA support for cx2388x boards\n",
		card->driver, devno);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;
	pci_set_drvdata(pci, card);

	devno++;
	वापस 0;

error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

/*
 * ALSA deकाष्ठाor
 */
अटल व्योम cx88_audio_finidev(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);

	snd_card_मुक्त(card);

	devno--;
पूर्ण

/*
 * PCI driver definition
 */

अटल काष्ठा pci_driver cx88_audio_pci_driver = अणु
	.name     = "cx88_audio",
	.id_table = cx88_audio_pci_tbl,
	.probe    = cx88_audio_initdev,
	.हटाओ   = cx88_audio_finidev,
पूर्ण;

module_pci_driver(cx88_audio_pci_driver);
