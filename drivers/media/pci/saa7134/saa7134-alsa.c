<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   SAA713x ALSA support क्रम V4L
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>

/*
 * Configuration macros
 */

/* शेषs */
#घोषणा MIXER_ADDR_UNSELECTED	-1
#घोषणा MIXER_ADDR_TVTUNER	0
#घोषणा MIXER_ADDR_LINE1	1
#घोषणा MIXER_ADDR_LINE2	2
#घोषणा MIXER_ADDR_LAST		2


अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल पूर्णांक enable[SNDRV_CARDS] = अणु1, [1 ... (SNDRV_CARDS - 1)] = 1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
module_param_array(enable, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for SAA7134 capture interface(s).");
MODULE_PARM_DESC(enable, "Enable (or not) the SAA7134 capture interface(s).");

/*
 * Main chip काष्ठाure
 */

प्रकार काष्ठा snd_card_saa7134 अणु
	काष्ठा snd_card *card;
	spinlock_t mixer_lock;
	पूर्णांक mixer_volume[MIXER_ADDR_LAST+1][2];
	पूर्णांक capture_source_addr;
	पूर्णांक capture_source[2];
	काष्ठा snd_kcontrol *capture_ctl[MIXER_ADDR_LAST+1];
	काष्ठा pci_dev *pci;
	काष्ठा saa7134_dev *dev;

	अचिन्हित दीर्घ iobase;
	s16 irq;
	u16 mute_was_on;

	spinlock_t lock;
पूर्ण snd_card_saa7134_t;


/*
 * PCM काष्ठाure
 */

प्रकार काष्ठा snd_card_saa7134_pcm अणु
	काष्ठा saa7134_dev *dev;

	spinlock_t lock;

	काष्ठा snd_pcm_substream *substream;
पूर्ण snd_card_saa7134_pcm_t;

अटल काष्ठा snd_card *snd_saa7134_cards[SNDRV_CARDS];


/*
 * saa7134 DMA audio stop
 *
 *   Called when the capture device is released or the buffer overflows
 *
 *   - Copied verbatim from saa7134-oss's dsp_dma_stop.
 *
 */

अटल व्योम saa7134_dma_stop(काष्ठा saa7134_dev *dev)
अणु
	dev->dmasound.dma_blk     = -1;
	dev->dmasound.dma_running = 0;
	saa7134_set_dmabits(dev);
पूर्ण

/*
 * saa7134 DMA audio start
 *
 *   Called when preparing the capture device क्रम use
 *
 *   - Copied verbatim from saa7134-oss's dsp_dma_start.
 *
 */

अटल व्योम saa7134_dma_start(काष्ठा saa7134_dev *dev)
अणु
	dev->dmasound.dma_blk     = 0;
	dev->dmasound.dma_running = 1;
	saa7134_set_dmabits(dev);
पूर्ण

/*
 * saa7134 audio DMA IRQ handler
 *
 *   Called whenever we get an SAA7134_IRQ_REPORT_DONE_RA3 पूर्णांकerrupt
 *   Handles shअगरting between the 2 buffers, manages the पढ़ो counters,
 *  and notअगरies ALSA when periods elapse
 *
 *   - Mostly copied from saa7134-oss's saa7134_irq_oss_करोne.
 *
 */

अटल व्योम saa7134_irq_alsa_करोne(काष्ठा saa7134_dev *dev,
				  अचिन्हित दीर्घ status)
अणु
	पूर्णांक next_blk, reg = 0;

	spin_lock(&dev->slock);
	अगर (UNSET == dev->dmasound.dma_blk) अणु
		pr_debug("irq: recording stopped\n");
		जाओ करोne;
	पूर्ण
	अगर (0 != (status & 0x0f000000))
		pr_debug("irq: lost %ld\n", (status >> 24) & 0x0f);
	अगर (0 == (status & 0x10000000)) अणु
		/* odd */
		अगर (0 == (dev->dmasound.dma_blk & 0x01))
			reg = SAA7134_RS_BA1(6);
	पूर्ण अन्यथा अणु
		/* even */
		अगर (1 == (dev->dmasound.dma_blk & 0x01))
			reg = SAA7134_RS_BA2(6);
	पूर्ण
	अगर (0 == reg) अणु
		pr_debug("irq: field oops [%s]\n",
			(status & 0x10000000) ? "even" : "odd");
		जाओ करोne;
	पूर्ण

	अगर (dev->dmasound.पढ़ो_count >= dev->dmasound.blksize * (dev->dmasound.blocks-2)) अणु
		pr_debug("irq: overrun [full=%d/%d] - Blocks in %d\n",
			dev->dmasound.पढ़ो_count,
			dev->dmasound.bufsize, dev->dmasound.blocks);
		spin_unlock(&dev->slock);
		snd_pcm_stop_xrun(dev->dmasound.substream);
		वापस;
	पूर्ण

	/* next block addr */
	next_blk = (dev->dmasound.dma_blk + 2) % dev->dmasound.blocks;
	saa_ग_लिखोl(reg,next_blk * dev->dmasound.blksize);
	pr_debug("irq: ok, %s, next_blk=%d, addr=%x, blocks=%u, size=%u, read=%u\n",
		(status & 0x10000000) ? "even" : "odd ", next_blk,
		 next_blk * dev->dmasound.blksize, dev->dmasound.blocks,
		 dev->dmasound.blksize, dev->dmasound.पढ़ो_count);

	/* update status & wake रुकोing पढ़ोers */
	dev->dmasound.dma_blk = (dev->dmasound.dma_blk + 1) % dev->dmasound.blocks;
	dev->dmasound.पढ़ो_count += dev->dmasound.blksize;

	dev->dmasound.recording_on = reg;

	अगर (dev->dmasound.पढ़ो_count >= snd_pcm_lib_period_bytes(dev->dmasound.substream)) अणु
		spin_unlock(&dev->slock);
		snd_pcm_period_elapsed(dev->dmasound.substream);
		spin_lock(&dev->slock);
	पूर्ण

 करोne:
	spin_unlock(&dev->slock);

पूर्ण

/*
 * IRQ request handler
 *
 *   Runs aदीर्घ with saa7134's IRQ handler, discards anything that isn't
 *   DMA sound
 *
 */

अटल irqवापस_t saa7134_alsa_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा saa7134_dmasound *dmasound = dev_id;
	काष्ठा saa7134_dev *dev = dmasound->priv_data;

	अचिन्हित दीर्घ report, status;
	पूर्णांक loop, handled = 0;

	क्रम (loop = 0; loop < 10; loop++) अणु
		report = saa_पढ़ोl(SAA7134_IRQ_REPORT);
		status = saa_पढ़ोl(SAA7134_IRQ_STATUS);

		अगर (report & SAA7134_IRQ_REPORT_DONE_RA3) अणु
			handled = 1;
			saa_ग_लिखोl(SAA7134_IRQ_REPORT,
				   SAA7134_IRQ_REPORT_DONE_RA3);
			saa7134_irq_alsa_करोne(dev, status);
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (loop == 10) अणु
		pr_debug("error! looping IRQ!");
	पूर्ण

out:
	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 * ALSA capture trigger
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called whenever a capture is started or stopped. Must be defined,
 *   but there's nothing we want to करो here
 *
 */

अटल पूर्णांक snd_card_saa7134_capture_trigger(काष्ठा snd_pcm_substream * substream,
					  पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_card_saa7134_pcm_t *pcm = runसमय->निजी_data;
	काष्ठा saa7134_dev *dev=pcm->dev;
	पूर्णांक err = 0;

	spin_lock(&dev->slock);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		/* start dma */
		saa7134_dma_start(dev);
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		/* stop dma */
		saa7134_dma_stop(dev);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण
	spin_unlock(&dev->slock);

	वापस err;
पूर्ण

अटल पूर्णांक saa7134_alsa_dma_init(काष्ठा saa7134_dev *dev,
				 अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा saa7134_dmasound *dma = &dev->dmasound;
	काष्ठा page *pg;
	पूर्णांक i;

	dma->vaddr = vदो_स्मृति_32(nr_pages << PAGE_SHIFT);
	अगर (शून्य == dma->vaddr) अणु
		pr_debug("vmalloc_32(%lu pages) failed\n", nr_pages);
		वापस -ENOMEM;
	पूर्ण

	pr_debug("vmalloc is at addr %p, size=%lu\n",
		 dma->vaddr, nr_pages << PAGE_SHIFT);

	स_रखो(dma->vaddr, 0, nr_pages << PAGE_SHIFT);
	dma->nr_pages = nr_pages;

	dma->sglist = vzalloc(array_size(माप(*dma->sglist), dma->nr_pages));
	अगर (शून्य == dma->sglist)
		जाओ vzalloc_err;

	sg_init_table(dma->sglist, dma->nr_pages);
	क्रम (i = 0; i < dma->nr_pages; i++) अणु
		pg = vदो_स्मृति_to_page(dma->vaddr + i * PAGE_SIZE);
		अगर (शून्य == pg)
			जाओ vदो_स्मृति_to_page_err;
		sg_set_page(&dma->sglist[i], pg, PAGE_SIZE, 0);
	पूर्ण
	वापस 0;

vदो_स्मृति_to_page_err:
	vमुक्त(dma->sglist);
	dma->sglist = शून्य;
vzalloc_err:
	vमुक्त(dma->vaddr);
	dma->vaddr = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक saa7134_alsa_dma_map(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_dmasound *dma = &dev->dmasound;

	dma->sglen = dma_map_sg(&dev->pci->dev, dma->sglist,
			dma->nr_pages, DMA_FROM_DEVICE);

	अगर (0 == dma->sglen) अणु
		pr_warn("%s: saa7134_alsa_map_sg failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_alsa_dma_unmap(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_dmasound *dma = &dev->dmasound;

	अगर (!dma->sglen)
		वापस 0;

	dma_unmap_sg(&dev->pci->dev, dma->sglist, dma->nr_pages, DMA_FROM_DEVICE);
	dma->sglen = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_alsa_dma_मुक्त(काष्ठा saa7134_dmasound *dma)
अणु
	vमुक्त(dma->sglist);
	dma->sglist = शून्य;
	vमुक्त(dma->vaddr);
	dma->vaddr = शून्य;
	वापस 0;
पूर्ण

/*
 * DMA buffer initialization
 *
 *   Uses V4L functions to initialize the DMA. Shouldn't be necessary in
 *  ALSA, but I was unable to use ALSA's own DMA, and had to क्रमce the
 *  usage of V4L's
 *
 *   - Copied verbatim from saa7134-oss.
 *
 */

अटल पूर्णांक dsp_buffer_init(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक err;

	BUG_ON(!dev->dmasound.bufsize);

	err = saa7134_alsa_dma_init(dev,
			       (dev->dmasound.bufsize + PAGE_SIZE) >> PAGE_SHIFT);
	अगर (0 != err)
		वापस err;
	वापस 0;
पूर्ण

/*
 * DMA buffer release
 *
 *   Called after closing the device, during snd_card_saa7134_capture_बंद
 *
 */

अटल पूर्णांक dsp_buffer_मुक्त(काष्ठा saa7134_dev *dev)
अणु
	BUG_ON(!dev->dmasound.blksize);

	saa7134_alsa_dma_मुक्त(&dev->dmasound);

	dev->dmasound.blocks  = 0;
	dev->dmasound.blksize = 0;
	dev->dmasound.bufsize = 0;

	वापस 0;
पूर्ण

/*
 * Setting the capture source and updating the ALSA controls
 */
अटल पूर्णांक snd_saa7134_capsrc_set(काष्ठा snd_kcontrol *kcontrol,
				  पूर्णांक left, पूर्णांक right, bool क्रमce_notअगरy)
अणु
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0, addr = kcontrol->निजी_value;
	पूर्णांक active, old_addr;
	u32 anabar, xbarin;
	पूर्णांक analog_io, rate;
	काष्ठा saa7134_dev *dev;

	dev = chip->dev;

	spin_lock_irq(&chip->mixer_lock);

	active = left != 0 || right != 0;
	old_addr = chip->capture_source_addr;

	/* The active capture source cannot be deactivated */
	अगर (active) अणु
		change = old_addr != addr ||
			 chip->capture_source[0] != left ||
			 chip->capture_source[1] != right;

		chip->capture_source[0] = left;
		chip->capture_source[1] = right;
		chip->capture_source_addr = addr;
		dev->dmasound.input = addr;
	पूर्ण
	spin_unlock_irq(&chip->mixer_lock);

	अगर (change) अणु
		चयन (dev->pci->device) अणु

		हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
			चयन (addr) अणु
			हाल MIXER_ADDR_TVTUNER:
				saa_anकरोrb(SAA7134_AUDIO_FORMAT_CTRL,
					   0xc0, 0xc0);
				saa_anकरोrb(SAA7134_SIF_SAMPLE_FREQ,
					   0x03, 0x00);
				अवरोध;
			हाल MIXER_ADDR_LINE1:
			हाल MIXER_ADDR_LINE2:
				analog_io = (MIXER_ADDR_LINE1 == addr) ?
					     0x00 : 0x08;
				rate = (32000 == dev->dmasound.rate) ?
					0x01 : 0x03;
				saa_anकरोrb(SAA7134_ANALOG_IO_SELECT,
					   0x08, analog_io);
				saa_anकरोrb(SAA7134_AUDIO_FORMAT_CTRL,
					   0xc0, 0x80);
				saa_anकरोrb(SAA7134_SIF_SAMPLE_FREQ,
					   0x03, rate);
				अवरोध;
			पूर्ण

			अवरोध;
		हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
		हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
			xbarin = 0x03; /* adc */
			anabar = 0;
			चयन (addr) अणु
			हाल MIXER_ADDR_TVTUNER:
				xbarin = 0; /* Demodulator */
				anabar = 2; /* DACs */
				अवरोध;
			हाल MIXER_ADDR_LINE1:
				anabar = 0;  /* aux1, aux1 */
				अवरोध;
			हाल MIXER_ADDR_LINE2:
				anabar = 9;  /* aux2, aux2 */
				अवरोध;
			पूर्ण

			/* output xbar always मुख्य channel */
			saa_dsp_ग_लिखोl(dev, SAA7133_DIGITAL_OUTPUT_SEL1,
				       0xbbbb10);

			अगर (left || right) अणु
				/* We've got data, turn the input on */
				saa_dsp_ग_लिखोl(dev, SAA7133_DIGITAL_INPUT_XBAR1,
					       xbarin);
				saa_ग_लिखोl(SAA7133_ANALOG_IO_SELECT, anabar);
			पूर्ण अन्यथा अणु
				saa_dsp_ग_लिखोl(dev, SAA7133_DIGITAL_INPUT_XBAR1,
					       0);
				saa_ग_लिखोl(SAA7133_ANALOG_IO_SELECT, 0);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (change) अणु
		अगर (क्रमce_notअगरy)
			snd_ctl_notअगरy(chip->card,
				       SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->capture_ctl[addr]->id);

		अगर (old_addr != MIXER_ADDR_UNSELECTED && old_addr != addr)
			snd_ctl_notअगरy(chip->card,
				       SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->capture_ctl[old_addr]->id);
	पूर्ण

	वापस change;
पूर्ण

/*
 * ALSA PCM preparation
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called right after the capture device is खोलोed, this function configures
 *  the buffer using the previously defined functions, allocates the memory,
 *  sets up the hardware रेजिस्टरs, and then starts the DMA. When this function
 *  वापसs, the audio should be flowing.
 *
 */

अटल पूर्णांक snd_card_saa7134_capture_prepare(काष्ठा snd_pcm_substream * substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक bswap, sign;
	u32 fmt, control;
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	काष्ठा saa7134_dev *dev;
	snd_card_saa7134_pcm_t *pcm = runसमय->निजी_data;

	pcm->dev->dmasound.substream = substream;

	dev = saa7134->dev;

	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		fmt = 0x00;
	अन्यथा
		fmt = 0x01;

	अगर (snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		sign = 1;
	अन्यथा
		sign = 0;

	अगर (snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat))
		bswap = 1;
	अन्यथा
		bswap = 0;

	चयन (dev->pci->device) अणु
	  हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		अगर (1 == runसमय->channels)
			fmt |= (1 << 3);
		अगर (2 == runसमय->channels)
			fmt |= (3 << 3);
		अगर (sign)
			fmt |= 0x04;

		fmt |= (MIXER_ADDR_TVTUNER == dev->dmasound.input) ? 0xc0 : 0x80;
		saa_ग_लिखोb(SAA7134_NUM_SAMPLES0, ((dev->dmasound.blksize - 1) & 0x0000ff));
		saa_ग_लिखोb(SAA7134_NUM_SAMPLES1, ((dev->dmasound.blksize - 1) & 0x00ff00) >>  8);
		saa_ग_लिखोb(SAA7134_NUM_SAMPLES2, ((dev->dmasound.blksize - 1) & 0xff0000) >> 16);
		saa_ग_लिखोb(SAA7134_AUDIO_FORMAT_CTRL, fmt);

		अवरोध;
	  हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	  हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		अगर (1 == runसमय->channels)
			fmt |= (1 << 4);
		अगर (2 == runसमय->channels)
			fmt |= (2 << 4);
		अगर (!sign)
			fmt |= 0x04;
		saa_ग_लिखोl(SAA7133_NUM_SAMPLES, dev->dmasound.blksize -1);
		saa_ग_लिखोl(SAA7133_AUDIO_CHANNEL, 0x543210 | (fmt << 24));
		अवरोध;
	पूर्ण

	pr_debug("rec_start: afmt=%d ch=%d  =>  fmt=0x%x swap=%c\n",
		runसमय->क्रमmat, runसमय->channels, fmt,
		bswap ? 'b' : '-');
	/* dma: setup channel 6 (= AUDIO) */
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dev->dmasound.pt.dma >> 12);
	अगर (bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;

	saa_ग_लिखोl(SAA7134_RS_BA1(6),0);
	saa_ग_लिखोl(SAA7134_RS_BA2(6),dev->dmasound.blksize);
	saa_ग_लिखोl(SAA7134_RS_PITCH(6),0);
	saa_ग_लिखोl(SAA7134_RS_CONTROL(6),control);

	dev->dmasound.rate = runसमय->rate;

	/* Setup and update the card/ALSA controls */
	snd_saa7134_capsrc_set(saa7134->capture_ctl[dev->dmasound.input], 1, 1,
			       true);

	वापस 0;

पूर्ण

/*
 * ALSA poपूर्णांकer fetching
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called whenever a period elapses, it must वापस the current hardware
 *  position of the buffer.
 *   Also resets the पढ़ो counter used to prevent overruns
 *
 */

अटल snd_pcm_uframes_t
snd_card_saa7134_capture_poपूर्णांकer(काष्ठा snd_pcm_substream * substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_card_saa7134_pcm_t *pcm = runसमय->निजी_data;
	काष्ठा saa7134_dev *dev=pcm->dev;

	अगर (dev->dmasound.पढ़ो_count) अणु
		dev->dmasound.पढ़ो_count  -= snd_pcm_lib_period_bytes(substream);
		dev->dmasound.पढ़ो_offset += snd_pcm_lib_period_bytes(substream);
		अगर (dev->dmasound.पढ़ो_offset == dev->dmasound.bufsize)
			dev->dmasound.पढ़ो_offset = 0;
	पूर्ण

	वापस bytes_to_frames(runसमय, dev->dmasound.पढ़ो_offset);
पूर्ण

/*
 * ALSA hardware capabilities definition
 *
 *  Report only 32kHz क्रम ALSA:
 *
 *  - SAA7133/35 uses DDEP (DemDec Easy Programming mode), which works in 32kHz
 *    only
 *  - SAA7134 क्रम TV mode uses DemDec mode (32kHz)
 *  - Radio works in 32kHz only
 *  - When recording 48kHz from Line1/Line2, चयनing of capture source to TV
 *    means
 *    चयनing to 32kHz without any frequency translation
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_card_saa7134_capture =
अणु
	.info =                 (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_S16_BE | \
				SNDRV_PCM_FMTBIT_S8 | \
				SNDRV_PCM_FMTBIT_U8 | \
				SNDRV_PCM_FMTBIT_U16_LE | \
				SNDRV_PCM_FMTBIT_U16_BE,
	.rates =		SNDRV_PCM_RATE_32000,
	.rate_min =		32000,
	.rate_max =		32000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(256*1024),
	.periods_min =		4,
	.periods_max =		1024,
पूर्ण;

अटल व्योम snd_card_saa7134_runसमय_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_card_saa7134_pcm_t *pcm = runसमय->निजी_data;

	kमुक्त(pcm);
पूर्ण


/*
 * ALSA hardware params
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called on initialization, right beक्रमe the PCM preparation
 *
 */

अटल पूर्णांक snd_card_saa7134_hw_params(काष्ठा snd_pcm_substream * substream,
				      काष्ठा snd_pcm_hw_params * hw_params)
अणु
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	काष्ठा saa7134_dev *dev;
	अचिन्हित पूर्णांक period_size, periods;
	पूर्णांक err;

	period_size = params_period_bytes(hw_params);
	periods = params_periods(hw_params);

	अगर (period_size < 0x100 || period_size > 0x10000)
		वापस -EINVAL;
	अगर (periods < 4)
		वापस -EINVAL;
	अगर (period_size * periods > 1024 * 1024)
		वापस -EINVAL;

	dev = saa7134->dev;

	अगर (dev->dmasound.blocks == periods &&
	    dev->dmasound.blksize == period_size)
		वापस 0;

	/* release the old buffer */
	अगर (substream->runसमय->dma_area) अणु
		saa7134_pgtable_मुक्त(dev->pci, &dev->dmasound.pt);
		saa7134_alsa_dma_unmap(dev);
		dsp_buffer_मुक्त(dev);
		substream->runसमय->dma_area = शून्य;
	पूर्ण
	dev->dmasound.blocks  = periods;
	dev->dmasound.blksize = period_size;
	dev->dmasound.bufsize = period_size * periods;

	err = dsp_buffer_init(dev);
	अगर (0 != err) अणु
		dev->dmasound.blocks  = 0;
		dev->dmasound.blksize = 0;
		dev->dmasound.bufsize = 0;
		वापस err;
	पूर्ण

	err = saa7134_alsa_dma_map(dev);
	अगर (err) अणु
		dsp_buffer_मुक्त(dev);
		वापस err;
	पूर्ण
	err = saa7134_pgtable_alloc(dev->pci, &dev->dmasound.pt);
	अगर (err) अणु
		saa7134_alsa_dma_unmap(dev);
		dsp_buffer_मुक्त(dev);
		वापस err;
	पूर्ण
	err = saa7134_pgtable_build(dev->pci, &dev->dmasound.pt,
				dev->dmasound.sglist, dev->dmasound.sglen, 0);
	अगर (err) अणु
		saa7134_pgtable_मुक्त(dev->pci, &dev->dmasound.pt);
		saa7134_alsa_dma_unmap(dev);
		dsp_buffer_मुक्त(dev);
		वापस err;
	पूर्ण

	/* I should be able to use runसमय->dma_addr in the control
	   byte, but it करोesn't work. So I allocate the DMA using the
	   V4L functions, and क्रमce ALSA to use that as the DMA area */

	substream->runसमय->dma_area = dev->dmasound.vaddr;
	substream->runसमय->dma_bytes = dev->dmasound.bufsize;
	substream->runसमय->dma_addr = 0;

	वापस 0;

पूर्ण

/*
 * ALSA hardware release
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called after closing the device, but beक्रमe snd_card_saa7134_capture_बंद
 *   It stops the DMA audio and releases the buffers.
 *
 */

अटल पूर्णांक snd_card_saa7134_hw_मुक्त(काष्ठा snd_pcm_substream * substream)
अणु
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	काष्ठा saa7134_dev *dev;

	dev = saa7134->dev;

	अगर (substream->runसमय->dma_area) अणु
		saa7134_pgtable_मुक्त(dev->pci, &dev->dmasound.pt);
		saa7134_alsa_dma_unmap(dev);
		dsp_buffer_मुक्त(dev);
		substream->runसमय->dma_area = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ALSA capture finish
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called after closing the device.
 *
 */

अटल पूर्णांक snd_card_saa7134_capture_बंद(काष्ठा snd_pcm_substream * substream)
अणु
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	काष्ठा saa7134_dev *dev = saa7134->dev;

	अगर (saa7134->mute_was_on) अणु
		dev->ctl_mute = 1;
		saa7134_tvaudio_seपंचांगute(dev);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ALSA capture start
 *
 *   - One of the ALSA capture callbacks.
 *
 *   Called when खोलोing the device. It creates and populates the PCM
 *  काष्ठाure
 *
 */

अटल पूर्णांक snd_card_saa7134_capture_खोलो(काष्ठा snd_pcm_substream * substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_card_saa7134_pcm_t *pcm;
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	काष्ठा saa7134_dev *dev;
	पूर्णांक amux, err;

	अगर (!saa7134) अणु
		pr_err("BUG: saa7134 can't find device struct. Can't proceed with open\n");
		वापस -ENODEV;
	पूर्ण
	dev = saa7134->dev;
	mutex_lock(&dev->dmasound.lock);

	dev->dmasound.पढ़ो_count  = 0;
	dev->dmasound.पढ़ो_offset = 0;

	amux = dev->input->amux;
	अगर ((amux < 1) || (amux > 3))
		amux = 1;
	dev->dmasound.input  =  amux - 1;

	mutex_unlock(&dev->dmasound.lock);

	pcm = kzalloc(माप(*pcm), GFP_KERNEL);
	अगर (pcm == शून्य)
		वापस -ENOMEM;

	pcm->dev=saa7134->dev;

	spin_lock_init(&pcm->lock);

	pcm->substream = substream;
	runसमय->निजी_data = pcm;
	runसमय->निजी_मुक्त = snd_card_saa7134_runसमय_मुक्त;
	runसमय->hw = snd_card_saa7134_capture;

	अगर (dev->ctl_mute != 0) अणु
		saa7134->mute_was_on = 1;
		dev->ctl_mute = 0;
		saa7134_tvaudio_seपंचांगute(dev);
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
						SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
						SNDRV_PCM_HW_PARAM_PERIODS, 2);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * page callback (needed क्रम mmap)
 */

अटल काष्ठा page *snd_card_saa7134_page(काष्ठा snd_pcm_substream *substream,
					अचिन्हित दीर्घ offset)
अणु
	व्योम *pageptr = substream->runसमय->dma_area + offset;
	वापस vदो_स्मृति_to_page(pageptr);
पूर्ण

/*
 * ALSA capture callbacks definition
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_card_saa7134_capture_ops = अणु
	.खोलो =			snd_card_saa7134_capture_खोलो,
	.बंद =		snd_card_saa7134_capture_बंद,
	.hw_params =		snd_card_saa7134_hw_params,
	.hw_मुक्त =		snd_card_saa7134_hw_मुक्त,
	.prepare =		snd_card_saa7134_capture_prepare,
	.trigger =		snd_card_saa7134_capture_trigger,
	.poपूर्णांकer =		snd_card_saa7134_capture_poपूर्णांकer,
	.page =			snd_card_saa7134_page,
पूर्ण;

/*
 * ALSA PCM setup
 *
 *   Called when initializing the board. Sets up the name and hooks up
 *  the callbacks
 *
 */

अटल पूर्णांक snd_card_saa7134_pcm(snd_card_saa7134_t *saa7134, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(saa7134->card, "SAA7134 PCM", device, 0, 1, &pcm)) < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_saa7134_capture_ops);
	pcm->निजी_data = saa7134;
	pcm->info_flags = 0;
	strscpy(pcm->name, "SAA7134 PCM", माप(pcm->name));
	वापस 0;
पूर्ण

#घोषणा SAA713x_VOLUME(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_saa7134_volume_info, \
  .get = snd_saa7134_volume_get, .put = snd_saa7134_volume_put, \
  .निजी_value = addr पूर्ण

अटल पूर्णांक snd_saa7134_volume_info(काष्ठा snd_kcontrol * kcontrol,
				   काष्ठा snd_ctl_elem_info * uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 20;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_saa7134_volume_get(काष्ठा snd_kcontrol * kcontrol,
				  काष्ठा snd_ctl_elem_value * ucontrol)
अणु
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक addr = kcontrol->निजी_value;

	ucontrol->value.पूर्णांकeger.value[0] = chip->mixer_volume[addr][0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->mixer_volume[addr][1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_saa7134_volume_put(काष्ठा snd_kcontrol * kcontrol,
				  काष्ठा snd_ctl_elem_value * ucontrol)
अणु
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा saa7134_dev *dev = chip->dev;

	पूर्णांक change, addr = kcontrol->निजी_value;
	पूर्णांक left, right;

	left = ucontrol->value.पूर्णांकeger.value[0];
	अगर (left < 0)
		left = 0;
	अगर (left > 20)
		left = 20;
	right = ucontrol->value.पूर्णांकeger.value[1];
	अगर (right < 0)
		right = 0;
	अगर (right > 20)
		right = 20;
	spin_lock_irq(&chip->mixer_lock);
	change = 0;
	अगर (chip->mixer_volume[addr][0] != left) अणु
		change = 1;
		right = left;
	पूर्ण
	अगर (chip->mixer_volume[addr][1] != right) अणु
		change = 1;
		left = right;
	पूर्ण
	अगर (change) अणु
		चयन (dev->pci->device) अणु
			हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
				चयन (addr) अणु
					हाल MIXER_ADDR_TVTUNER:
						left = 20;
						अवरोध;
					हाल MIXER_ADDR_LINE1:
						saa_anकरोrb(SAA7134_ANALOG_IO_SELECT,  0x10,
							   (left > 10) ? 0x00 : 0x10);
						अवरोध;
					हाल MIXER_ADDR_LINE2:
						saa_anकरोrb(SAA7134_ANALOG_IO_SELECT,  0x20,
							   (left > 10) ? 0x00 : 0x20);
						अवरोध;
				पूर्ण
				अवरोध;
			हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
			हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
				चयन (addr) अणु
					हाल MIXER_ADDR_TVTUNER:
						left = 20;
						अवरोध;
					हाल MIXER_ADDR_LINE1:
						saa_anकरोrb(0x0594,  0x10,
							   (left > 10) ? 0x00 : 0x10);
						अवरोध;
					हाल MIXER_ADDR_LINE2:
						saa_anकरोrb(0x0594,  0x20,
							   (left > 10) ? 0x00 : 0x20);
						अवरोध;
				पूर्ण
				अवरोध;
		पूर्ण
		chip->mixer_volume[addr][0] = left;
		chip->mixer_volume[addr][1] = right;
	पूर्ण
	spin_unlock_irq(&chip->mixer_lock);
	वापस change;
पूर्ण

#घोषणा SAA713x_CAPSRC(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_saa7134_capsrc_info, \
  .get = snd_saa7134_capsrc_get, .put = snd_saa7134_capsrc_put, \
  .निजी_value = addr पूर्ण

अटल पूर्णांक snd_saa7134_capsrc_info(काष्ठा snd_kcontrol * kcontrol,
				   काष्ठा snd_ctl_elem_info * uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_saa7134_capsrc_get(काष्ठा snd_kcontrol * kcontrol,
				  काष्ठा snd_ctl_elem_value * ucontrol)
अणु
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक addr = kcontrol->निजी_value;

	spin_lock_irq(&chip->mixer_lock);
	अगर (chip->capture_source_addr == addr) अणु
		ucontrol->value.पूर्णांकeger.value[0] = chip->capture_source[0];
		ucontrol->value.पूर्णांकeger.value[1] = chip->capture_source[1];
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0;
		ucontrol->value.पूर्णांकeger.value[1] = 0;
	पूर्ण
	spin_unlock_irq(&chip->mixer_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_saa7134_capsrc_put(काष्ठा snd_kcontrol * kcontrol,
				  काष्ठा snd_ctl_elem_value * ucontrol)
अणु
	पूर्णांक left, right;
	left = ucontrol->value.पूर्णांकeger.value[0] & 1;
	right = ucontrol->value.पूर्णांकeger.value[1] & 1;

	वापस snd_saa7134_capsrc_set(kcontrol, left, right, false);
पूर्ण

अटल काष्ठा snd_kcontrol_new snd_saa7134_volume_controls[] = अणु
SAA713x_VOLUME("Video Volume", 0, MIXER_ADDR_TVTUNER),
SAA713x_VOLUME("Line Volume", 1, MIXER_ADDR_LINE1),
SAA713x_VOLUME("Line Volume", 2, MIXER_ADDR_LINE2),
पूर्ण;

अटल काष्ठा snd_kcontrol_new snd_saa7134_capture_controls[] = अणु
SAA713x_CAPSRC("Video Capture Switch", 0, MIXER_ADDR_TVTUNER),
SAA713x_CAPSRC("Line Capture Switch", 1, MIXER_ADDR_LINE1),
SAA713x_CAPSRC("Line Capture Switch", 2, MIXER_ADDR_LINE2),
पूर्ण;

/*
 * ALSA mixer setup
 *
 *   Called when initializing the board. Sets up the name and hooks up
 *  the callbacks
 *
 */

अटल पूर्णांक snd_card_saa7134_new_mixer(snd_card_saa7134_t * chip)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_kcontrol *kcontrol;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err, addr;

	strscpy(card->mixername, "SAA7134 Mixer", माप(card->mixername));

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_saa7134_volume_controls); idx++) अणु
		kcontrol = snd_ctl_new1(&snd_saa7134_volume_controls[idx],
					chip);
		err = snd_ctl_add(card, kcontrol);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_saa7134_capture_controls); idx++) अणु
		kcontrol = snd_ctl_new1(&snd_saa7134_capture_controls[idx],
					chip);
		addr = snd_saa7134_capture_controls[idx].निजी_value;
		chip->capture_ctl[addr] = kcontrol;
		err = snd_ctl_add(card, kcontrol);
		अगर (err < 0)
			वापस err;
	पूर्ण

	chip->capture_source_addr = MIXER_ADDR_UNSELECTED;
	वापस 0;
पूर्ण

अटल व्योम snd_saa7134_मुक्त(काष्ठा snd_card * card)
अणु
	snd_card_saa7134_t *chip = card->निजी_data;

	अगर (chip->dev->dmasound.priv_data == शून्य)
		वापस;

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, &chip->dev->dmasound);

	chip->dev->dmasound.priv_data = शून्य;

पूर्ण

/*
 * ALSA initialization
 *
 *   Called by the init routine, once क्रम each saa7134 device present,
 *  it creates the basic काष्ठाures and रेजिस्टरs the ALSA devices
 *
 */

अटल पूर्णांक alsa_card_saa7134_create(काष्ठा saa7134_dev *dev, पूर्णांक devnum)
अणु

	काष्ठा snd_card *card;
	snd_card_saa7134_t *chip;
	पूर्णांक err;


	अगर (devnum >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[devnum])
		वापस -ENODEV;

	err = snd_card_new(&dev->pci->dev, index[devnum], id[devnum],
			   THIS_MODULE, माप(snd_card_saa7134_t), &card);
	अगर (err < 0)
		वापस err;

	strscpy(card->driver, "SAA7134", माप(card->driver));

	/* Card "creation" */

	card->निजी_मुक्त = snd_saa7134_मुक्त;
	chip = card->निजी_data;

	spin_lock_init(&chip->lock);
	spin_lock_init(&chip->mixer_lock);

	chip->dev = dev;

	chip->card = card;

	chip->pci = dev->pci;
	chip->iobase = pci_resource_start(dev->pci, 0);


	err = request_irq(dev->pci->irq, saa7134_alsa_irq,
				IRQF_SHARED, dev->name,
				(व्योम*) &dev->dmasound);

	अगर (err < 0) अणु
		pr_err("%s: can't get IRQ %d for ALSA\n",
			dev->name, dev->pci->irq);
		जाओ __nodev;
	पूर्ण

	chip->irq = dev->pci->irq;

	mutex_init(&dev->dmasound.lock);

	अगर ((err = snd_card_saa7134_new_mixer(chip)) < 0)
		जाओ __nodev;

	अगर ((err = snd_card_saa7134_pcm(chip, 0)) < 0)
		जाओ __nodev;

	/* End of "creation" */

	strscpy(card->लघुname, "SAA7134", माप(card->लघुname));
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %d",
		chip->dev->name, chip->iobase, chip->irq);

	pr_info("%s/alsa: %s registered as card %d\n",
		dev->name, card->दीर्घname, index[devnum]);

	अगर ((err = snd_card_रेजिस्टर(card)) == 0) अणु
		snd_saa7134_cards[devnum] = card;
		वापस 0;
	पूर्ण

__nodev:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण


अटल पूर्णांक alsa_device_init(काष्ठा saa7134_dev *dev)
अणु
	dev->dmasound.priv_data = dev;
	alsa_card_saa7134_create(dev,dev->nr);
	वापस 1;
पूर्ण

अटल पूर्णांक alsa_device_निकास(काष्ठा saa7134_dev *dev)
अणु
	अगर (!snd_saa7134_cards[dev->nr])
		वापस 1;

	snd_card_मुक्त(snd_saa7134_cards[dev->nr]);
	snd_saa7134_cards[dev->nr] = शून्य;
	वापस 1;
पूर्ण

/*
 * Module initializer
 *
 * Loops through present saa7134 cards, and assigns an ALSA device
 * to each one
 *
 */

अटल पूर्णांक saa7134_alsa_init(व्योम)
अणु
	काष्ठा saa7134_dev *dev = शून्य;
	काष्ठा list_head *list;

	saa7134_dmasound_init = alsa_device_init;
	saa7134_dmasound_निकास = alsa_device_निकास;

	pr_info("saa7134 ALSA driver for DMA sound loaded\n");

	list_क्रम_each(list,&saa7134_devlist) अणु
		dev = list_entry(list, काष्ठा saa7134_dev, devlist);
		अगर (dev->pci->device == PCI_DEVICE_ID_PHILIPS_SAA7130)
			pr_info("%s/alsa: %s doesn't support digital audio\n",
				dev->name, saa7134_boards[dev->board].name);
		अन्यथा
			alsa_device_init(dev);
	पूर्ण

	अगर (dev == शून्य)
		pr_info("saa7134 ALSA: no saa7134 cards found\n");

	वापस 0;

पूर्ण

/*
 * Module deकाष्ठाor
 */

अटल व्योम saa7134_alsa_निकास(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		अगर (snd_saa7134_cards[idx])
			snd_card_मुक्त(snd_saa7134_cards[idx]);
	पूर्ण

	saa7134_dmasound_init = शून्य;
	saa7134_dmasound_निकास = शून्य;
	pr_info("saa7134 ALSA driver for DMA sound unloaded\n");

	वापस;
पूर्ण

/* We initialize this late, to make sure the sound प्रणाली is up and running */
late_initcall(saa7134_alsa_init);
module_निकास(saa7134_alsa_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Cerqueira");
