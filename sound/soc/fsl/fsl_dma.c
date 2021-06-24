<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale DMA ALSA SoC PCM driver
//
// Author: Timur Tabi <timur@मुक्तscale.com>
//
// Copyright 2007-2010 Freescale Semiconductor, Inc.
//
// This driver implements ASoC support क्रम the Elo DMA controller, which is
// the DMA controller on Freescale 83xx, 85xx, and 86xx SOCs. In ALSA terms,
// the PCM driver is what handles the DMA buffer.

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/पन.स>

#समावेश "fsl_dma.h"
#समावेश "fsl_ssi.h"	/* For the offset of stx0 and srx0 */

#घोषणा DRV_NAME "fsl_dma"

/*
 * The क्रमmats that the DMA controller supports, which is anything
 * that is 8, 16, or 32 bits.
 */
#घोषणा FSLDMA_PCM_FORMATS (SNDRV_PCM_FMTBIT_S8 	| \
			    SNDRV_PCM_FMTBIT_U8 	| \
			    SNDRV_PCM_FMTBIT_S16_LE     | \
			    SNDRV_PCM_FMTBIT_S16_BE     | \
			    SNDRV_PCM_FMTBIT_U16_LE     | \
			    SNDRV_PCM_FMTBIT_U16_BE     | \
			    SNDRV_PCM_FMTBIT_S24_LE     | \
			    SNDRV_PCM_FMTBIT_S24_BE     | \
			    SNDRV_PCM_FMTBIT_U24_LE     | \
			    SNDRV_PCM_FMTBIT_U24_BE     | \
			    SNDRV_PCM_FMTBIT_S32_LE     | \
			    SNDRV_PCM_FMTBIT_S32_BE     | \
			    SNDRV_PCM_FMTBIT_U32_LE     | \
			    SNDRV_PCM_FMTBIT_U32_BE)
काष्ठा dma_object अणु
	काष्ठा snd_soc_component_driver dai;
	dma_addr_t ssi_stx_phys;
	dma_addr_t ssi_srx_phys;
	अचिन्हित पूर्णांक ssi_fअगरo_depth;
	काष्ठा ccsr_dma_channel __iomem *channel;
	अचिन्हित पूर्णांक irq;
	bool asचिन्हित;
पूर्ण;

/*
 * The number of DMA links to use.  Two is the bare minimum, but अगर you
 * have really small links you might need more.
 */
#घोषणा NUM_DMA_LINKS   2

/** fsl_dma_निजी: p-substream DMA data
 *
 * Each substream has a 1-to-1 association with a DMA channel.
 *
 * The link[] array is first because it needs to be aligned on a 32-byte
 * boundary, so putting it first will ensure alignment without padding the
 * काष्ठाure.
 *
 * @link[]: array of link descriptors
 * @dma_channel: poपूर्णांकer to the DMA channel's रेजिस्टरs
 * @irq: IRQ क्रम this DMA channel
 * @substream: poपूर्णांकer to the substream object, needed by the ISR
 * @ssi_sxx_phys: bus address of the STX or SRX रेजिस्टर to use
 * @ld_buf_phys: physical address of the LD buffer
 * @current_link: index पूर्णांकo link[] of the link currently being processed
 * @dma_buf_phys: physical address of the DMA buffer
 * @dma_buf_next: physical address of the next period to process
 * @dma_buf_end: physical address of the byte after the end of the DMA
 * @buffer period_size: the size of a single period
 * @num_periods: the number of periods in the DMA buffer
 */
काष्ठा fsl_dma_निजी अणु
	काष्ठा fsl_dma_link_descriptor link[NUM_DMA_LINKS];
	काष्ठा ccsr_dma_channel __iomem *dma_channel;
	अचिन्हित पूर्णांक irq;
	काष्ठा snd_pcm_substream *substream;
	dma_addr_t ssi_sxx_phys;
	अचिन्हित पूर्णांक ssi_fअगरo_depth;
	dma_addr_t ld_buf_phys;
	अचिन्हित पूर्णांक current_link;
	dma_addr_t dma_buf_phys;
	dma_addr_t dma_buf_next;
	dma_addr_t dma_buf_end;
	माप_प्रकार period_size;
	अचिन्हित पूर्णांक num_periods;
पूर्ण;

/**
 * fsl_dma_hardare: define अक्षरacteristics of the PCM hardware.
 *
 * The PCM hardware is the Freescale DMA controller.  This काष्ठाure defines
 * the capabilities of that hardware.
 *
 * Since the sampling rate and data क्रमmat are not controlled by the DMA
 * controller, we specअगरy no limits क्रम those values.  The only exception is
 * period_bytes_min, which is set to a reasonably low value to prevent the
 * DMA controller from generating too many पूर्णांकerrupts per second.
 *
 * Since each link descriptor has a 32-bit byte count field, we set
 * period_bytes_max to the largest 32-bit number.  We also have no maximum
 * number of periods.
 *
 * Note that we specअगरy SNDRV_PCM_INFO_JOINT_DUPLEX here, but only because a
 * limitation in the SSI driver requires the sample rates क्रम playback and
 * capture to be the same.
 */
अटल स्थिर काष्ठा snd_pcm_hardware fsl_dma_hardware = अणु

	.info   		= SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_JOINT_DUPLEX |
				  SNDRV_PCM_INFO_PAUSE,
	.क्रमmats		= FSLDMA_PCM_FORMATS,
	.period_bytes_min       = 512,  	/* A reasonable limit */
	.period_bytes_max       = (u32) -1,
	.periods_min    	= NUM_DMA_LINKS,
	.periods_max    	= (अचिन्हित पूर्णांक) -1,
	.buffer_bytes_max       = 128 * 1024,   /* A reasonable limit */
पूर्ण;

/**
 * fsl_dma_पात_stream: tell ALSA that the DMA transfer has पातed
 *
 * This function should be called by the ISR whenever the DMA controller
 * halts data transfer.
 */
अटल व्योम fsl_dma_पात_stream(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_stop_xrun(substream);
पूर्ण

/**
 * fsl_dma_update_poपूर्णांकers - update LD poपूर्णांकers to poपूर्णांक to the next period
 *
 * As each period is completed, this function changes the link
 * descriptor poपूर्णांकers क्रम that period to poपूर्णांक to the next period.
 */
अटल व्योम fsl_dma_update_poपूर्णांकers(काष्ठा fsl_dma_निजी *dma_निजी)
अणु
	काष्ठा fsl_dma_link_descriptor *link =
		&dma_निजी->link[dma_निजी->current_link];

	/* Update our link descriptors to poपूर्णांक to the next period. On a 36-bit
	 * प्रणाली, we also need to update the ESAD bits.  We also set (keep) the
	 * snoop bits.  See the comments in fsl_dma_hw_params() about snooping.
	 */
	अगर (dma_निजी->substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		link->source_addr = cpu_to_be32(dma_निजी->dma_buf_next);
#अगर_घोषित CONFIG_PHYS_64BIT
		link->source_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
			upper_32_bits(dma_निजी->dma_buf_next));
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		link->dest_addr = cpu_to_be32(dma_निजी->dma_buf_next);
#अगर_घोषित CONFIG_PHYS_64BIT
		link->dest_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
			upper_32_bits(dma_निजी->dma_buf_next));
#पूर्ण_अगर
	पूर्ण

	/* Update our variables क्रम next समय */
	dma_निजी->dma_buf_next += dma_निजी->period_size;

	अगर (dma_निजी->dma_buf_next >= dma_निजी->dma_buf_end)
		dma_निजी->dma_buf_next = dma_निजी->dma_buf_phys;

	अगर (++dma_निजी->current_link >= NUM_DMA_LINKS)
		dma_निजी->current_link = 0;
पूर्ण

/**
 * fsl_dma_isr: पूर्णांकerrupt handler क्रम the DMA controller
 *
 * @irq: IRQ of the DMA channel
 * @dev_id: poपूर्णांकer to the dma_निजी काष्ठाure क्रम this DMA channel
 */
अटल irqवापस_t fsl_dma_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_dma_निजी *dma_निजी = dev_id;
	काष्ठा snd_pcm_substream *substream = dma_निजी->substream;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा device *dev = rtd->dev;
	काष्ठा ccsr_dma_channel __iomem *dma_channel = dma_निजी->dma_channel;
	irqवापस_t ret = IRQ_NONE;
	u32 sr, sr2 = 0;

	/* We got an पूर्णांकerrupt, so पढ़ो the status रेजिस्टर to see what we
	   were पूर्णांकerrupted क्रम.
	 */
	sr = in_be32(&dma_channel->sr);

	अगर (sr & CCSR_DMA_SR_TE) अणु
		dev_err(dev, "dma transmit error\n");
		fsl_dma_पात_stream(substream);
		sr2 |= CCSR_DMA_SR_TE;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (sr & CCSR_DMA_SR_CH)
		ret = IRQ_HANDLED;

	अगर (sr & CCSR_DMA_SR_PE) अणु
		dev_err(dev, "dma programming error\n");
		fsl_dma_पात_stream(substream);
		sr2 |= CCSR_DMA_SR_PE;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (sr & CCSR_DMA_SR_EOLNI) अणु
		sr2 |= CCSR_DMA_SR_EOLNI;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (sr & CCSR_DMA_SR_CB)
		ret = IRQ_HANDLED;

	अगर (sr & CCSR_DMA_SR_EOSI) अणु
		/* Tell ALSA we completed a period. */
		snd_pcm_period_elapsed(substream);

		/*
		 * Update our link descriptors to poपूर्णांक to the next period. We
		 * only need to करो this अगर the number of periods is not equal to
		 * the number of links.
		 */
		अगर (dma_निजी->num_periods != NUM_DMA_LINKS)
			fsl_dma_update_poपूर्णांकers(dma_निजी);

		sr2 |= CCSR_DMA_SR_EOSI;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (sr & CCSR_DMA_SR_EOLSI) अणु
		sr2 |= CCSR_DMA_SR_EOLSI;
		ret = IRQ_HANDLED;
	पूर्ण

	/* Clear the bits that we set */
	अगर (sr2)
		out_be32(&dma_channel->sr, sr2);

	वापस ret;
पूर्ण

/**
 * fsl_dma_new: initialize this PCM driver.
 *
 * This function is called when the codec driver calls snd_soc_new_pcms(),
 * once क्रम each .dai_link in the machine driver's snd_soc_card
 * काष्ठाure.
 *
 * snd_dma_alloc_pages() is just a front-end to dma_alloc_coherent(), which
 * (currently) always allocates the DMA buffer in lowmem, even अगर GFP_HIGHMEM
 * is specअगरied. Thereक्रमe, any DMA buffers we allocate will always be in low
 * memory, but we support क्रम 36-bit physical addresses anyway.
 *
 * Regardless of where the memory is actually allocated, since the device can
 * technically DMA to any 36-bit address, we करो need to set the DMA mask to 36.
 */
अटल पूर्णांक fsl_dma_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(36));
	अगर (ret)
		वापस ret;

	/* Some codecs have separate DAIs क्रम playback and capture, so we
	 * should allocate a DMA buffer only क्रम the streams that are valid.
	 */

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
			fsl_dma_hardware.buffer_bytes_max,
			&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);
		अगर (ret) अणु
			dev_err(card->dev, "can't alloc playback dma buffer\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
			fsl_dma_hardware.buffer_bytes_max,
			&pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream->dma_buffer);
		अगर (ret) अणु
			dev_err(card->dev, "can't alloc capture dma buffer\n");
			snd_dma_मुक्त_pages(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_dma_खोलो: खोलो a new substream.
 *
 * Each substream has its own DMA buffer.
 *
 * ALSA भागides the DMA buffer पूर्णांकo N periods.  We create NUM_DMA_LINKS link
 * descriptors that ping-pong from one period to the next.  For example, अगर
 * there are six periods and two link descriptors, this is how they look
 * beक्रमe playback starts:
 *
 *      	   The last link descriptor
 *   ____________  poपूर्णांकs back to the first
 *  |   	 |
 *  V   	 |
 *  ___    ___   |
 * |   |->|   |->|
 * |___|  |___|
 *   |      |
 *   |      |
 *   V      V
 *  _________________________________________
 * |      |      |      |      |      |      |  The DMA buffer is
 * |      |      |      |      |      |      |    भागided पूर्णांकo 6 parts
 * |______|______|______|______|______|______|
 *
 * and here's how they look after the first period is finished playing:
 *
 *   ____________
 *  |   	 |
 *  V   	 |
 *  ___    ___   |
 * |   |->|   |->|
 * |___|  |___|
 *   |      |
 *   |______________
 *          |       |
 *          V       V
 *  _________________________________________
 * |      |      |      |      |      |      |
 * |      |      |      |      |      |      |
 * |______|______|______|______|______|______|
 *
 * The first link descriptor now poपूर्णांकs to the third period.  The DMA
 * controller is currently playing the second period.  When it finishes, it
 * will jump back to the first descriptor and play the third period.
 *
 * There are four reasons we करो this:
 *
 * 1. The only way to get the DMA controller to स्वतःmatically restart the
 *    transfer when it माला_लो to the end of the buffer is to use chaining
 *    mode.  Basic direct mode करोesn't offer that feature.
 * 2. We need to receive an पूर्णांकerrupt at the end of every period.  The DMA
 *    controller can generate an पूर्णांकerrupt at the end of every link transfer
 *    (aka segment).  Making each period पूर्णांकo a DMA segment will give us the
 *    पूर्णांकerrupts we need.
 * 3. By creating only two link descriptors, regardless of the number of
 *    periods, we करो not need to पुनः_स्मृतिate the link descriptors अगर the
 *    number of periods changes.
 * 4. All of the audio data is still stored in a single, contiguous DMA
 *    buffer, which is what ALSA expects.  We're just भागiding it पूर्णांकo
 *    contiguous parts, and creating a link descriptor क्रम each one.
 */
अटल पूर्णांक fsl_dma_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = component->dev;
	काष्ठा dma_object *dma =
		container_of(component->driver, काष्ठा dma_object, dai);
	काष्ठा fsl_dma_निजी *dma_निजी;
	काष्ठा ccsr_dma_channel __iomem *dma_channel;
	dma_addr_t ld_buf_phys;
	u64 temp_link;  	/* Poपूर्णांकer to next link descriptor */
	u32 mr;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;

	/*
	 * Reject any DMA buffer whose size is not a multiple of the period
	 * size.  We need to make sure that the DMA buffer can be evenly भागided
	 * पूर्णांकo periods.
	 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
		SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		dev_err(dev, "invalid buffer size\n");
		वापस ret;
	पूर्ण

	अगर (dma->asचिन्हित) अणु
		dev_err(dev, "dma channel already assigned\n");
		वापस -EBUSY;
	पूर्ण

	dma_निजी = dma_alloc_coherent(dev, माप(काष्ठा fsl_dma_निजी),
					 &ld_buf_phys, GFP_KERNEL);
	अगर (!dma_निजी) अणु
		dev_err(dev, "can't allocate dma private data\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_निजी->ssi_sxx_phys = dma->ssi_stx_phys;
	अन्यथा
		dma_निजी->ssi_sxx_phys = dma->ssi_srx_phys;

	dma_निजी->ssi_fअगरo_depth = dma->ssi_fअगरo_depth;
	dma_निजी->dma_channel = dma->channel;
	dma_निजी->irq = dma->irq;
	dma_निजी->substream = substream;
	dma_निजी->ld_buf_phys = ld_buf_phys;
	dma_निजी->dma_buf_phys = substream->dma_buffer.addr;

	ret = request_irq(dma_निजी->irq, fsl_dma_isr, 0, "fsldma-audio",
			  dma_निजी);
	अगर (ret) अणु
		dev_err(dev, "can't register ISR for IRQ %u (ret=%i)\n",
			dma_निजी->irq, ret);
		dma_मुक्त_coherent(dev, माप(काष्ठा fsl_dma_निजी),
			dma_निजी, dma_निजी->ld_buf_phys);
		वापस ret;
	पूर्ण

	dma->asचिन्हित = true;

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);
	snd_soc_set_runसमय_hwparams(substream, &fsl_dma_hardware);
	runसमय->निजी_data = dma_निजी;

	/* Program the fixed DMA controller parameters */

	dma_channel = dma_निजी->dma_channel;

	temp_link = dma_निजी->ld_buf_phys +
		माप(काष्ठा fsl_dma_link_descriptor);

	क्रम (i = 0; i < NUM_DMA_LINKS; i++) अणु
		dma_निजी->link[i].next = cpu_to_be64(temp_link);

		temp_link += माप(काष्ठा fsl_dma_link_descriptor);
	पूर्ण
	/* The last link descriptor poपूर्णांकs to the first */
	dma_निजी->link[i - 1].next = cpu_to_be64(dma_निजी->ld_buf_phys);

	/* Tell the DMA controller where the first link descriptor is */
	out_be32(&dma_channel->clndar,
		CCSR_DMA_CLNDAR_ADDR(dma_निजी->ld_buf_phys));
	out_be32(&dma_channel->eclndar,
		CCSR_DMA_ECLNDAR_ADDR(dma_निजी->ld_buf_phys));

	/* The manual says the BCR must be clear beक्रमe enabling EMP */
	out_be32(&dma_channel->bcr, 0);

	/*
	 * Program the mode रेजिस्टर क्रम पूर्णांकerrupts, बाह्यal master control,
	 * and source/destination hold.  Also clear the Channel Abort bit.
	 */
	mr = in_be32(&dma_channel->mr) &
		~(CCSR_DMA_MR_CA | CCSR_DMA_MR_DAHE | CCSR_DMA_MR_SAHE);

	/*
	 * We want External Master Start and External Master Pause enabled,
	 * because the SSI is controlling the DMA controller.  We want the DMA
	 * controller to be set up in advance, and then we संकेत only the SSI
	 * to start transferring.
	 *
	 * We want End-Of-Segment Interrupts enabled, because this will generate
	 * an पूर्णांकerrupt at the end of each segment (each link descriptor
	 * represents one segment).  Each DMA segment is the same thing as an
	 * ALSA period, so this is how we get an पूर्णांकerrupt at the end of every
	 * period.
	 *
	 * We want Error Interrupt enabled, so that we can get an error अगर
	 * the DMA controller is mis-programmed somehow.
	 */
	mr |= CCSR_DMA_MR_EOSIE | CCSR_DMA_MR_EIE | CCSR_DMA_MR_EMP_EN |
		CCSR_DMA_MR_EMS_EN;

	/* For playback, we want the destination address to be held.  For
	   capture, set the source address to be held. */
	mr |= (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		CCSR_DMA_MR_DAHE : CCSR_DMA_MR_SAHE;

	out_be32(&dma_channel->mr, mr);

	वापस 0;
पूर्ण

/**
 * fsl_dma_hw_params: जारी initializing the DMA links
 *
 * This function obtains hardware parameters about the खोलोed stream and
 * programs the DMA controller accordingly.
 *
 * One drawback of big-endian is that when copying पूर्णांकegers of dअगरferent
 * sizes to a fixed-sized रेजिस्टर, the address to which the पूर्णांकeger must be
 * copied is dependent on the size of the पूर्णांकeger.
 *
 * For example, अगर P is the address of a 32-bit रेजिस्टर, and X is a 32-bit
 * पूर्णांकeger, then X should be copied to address P.  However, अगर X is a 16-bit
 * पूर्णांकeger, then it should be copied to P+2.  If X is an 8-bit रेजिस्टर,
 * then it should be copied to P+3.
 *
 * So क्रम playback of 8-bit samples, the DMA controller must transfer single
 * bytes from the DMA buffer to the last byte of the STX0 रेजिस्टर, i.e.
 * offset by 3 bytes. For 16-bit samples, the offset is two bytes.
 *
 * For 24-bit samples, the offset is 1 byte.  However, the DMA controller
 * करोes not support 3-byte copies (the DAHTS रेजिस्टर supports only 1, 2, 4,
 * and 8 bytes at a समय).  So we करो not support packed 24-bit samples.
 * 24-bit data must be padded to 32 bits.
 */
अटल पूर्णांक fsl_dma_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;

	/* Number of bits per sample */
	अचिन्हित पूर्णांक sample_bits =
		snd_pcm_क्रमmat_physical_width(params_क्रमmat(hw_params));

	/* Number of bytes per frame */
	अचिन्हित पूर्णांक sample_bytes = sample_bits / 8;

	/* Bus address of SSI STX रेजिस्टर */
	dma_addr_t ssi_sxx_phys = dma_निजी->ssi_sxx_phys;

	/* Size of the DMA buffer, in bytes */
	माप_प्रकार buffer_size = params_buffer_bytes(hw_params);

	/* Number of bytes per period */
	माप_प्रकार period_size = params_period_bytes(hw_params);

	/* Poपूर्णांकer to next period */
	dma_addr_t temp_addr = substream->dma_buffer.addr;

	/* Poपूर्णांकer to DMA controller */
	काष्ठा ccsr_dma_channel __iomem *dma_channel = dma_निजी->dma_channel;

	u32 mr; /* DMA Mode Register */

	अचिन्हित पूर्णांक i;

	/* Initialize our DMA tracking variables */
	dma_निजी->period_size = period_size;
	dma_निजी->num_periods = params_periods(hw_params);
	dma_निजी->dma_buf_end = dma_निजी->dma_buf_phys + buffer_size;
	dma_निजी->dma_buf_next = dma_निजी->dma_buf_phys +
		(NUM_DMA_LINKS * period_size);

	अगर (dma_निजी->dma_buf_next >= dma_निजी->dma_buf_end)
		/* This happens अगर the number of periods == NUM_DMA_LINKS */
		dma_निजी->dma_buf_next = dma_निजी->dma_buf_phys;

	mr = in_be32(&dma_channel->mr) & ~(CCSR_DMA_MR_BWC_MASK |
		  CCSR_DMA_MR_SAHTS_MASK | CCSR_DMA_MR_DAHTS_MASK);

	/* Due to a quirk of the SSI's STX रेजिस्टर, the target address
	 * क्रम the DMA operations depends on the sample size.  So we calculate
	 * that offset here.  While we're at it, also tell the DMA controller
	 * how much data to transfer per sample.
	 */
	चयन (sample_bits) अणु
	हाल 8:
		mr |= CCSR_DMA_MR_DAHTS_1 | CCSR_DMA_MR_SAHTS_1;
		ssi_sxx_phys += 3;
		अवरोध;
	हाल 16:
		mr |= CCSR_DMA_MR_DAHTS_2 | CCSR_DMA_MR_SAHTS_2;
		ssi_sxx_phys += 2;
		अवरोध;
	हाल 32:
		mr |= CCSR_DMA_MR_DAHTS_4 | CCSR_DMA_MR_SAHTS_4;
		अवरोध;
	शेष:
		/* We should never get here */
		dev_err(dev, "unsupported sample size %u\n", sample_bits);
		वापस -EINVAL;
	पूर्ण

	/*
	 * BWC determines how many bytes are sent/received beक्रमe the DMA
	 * controller checks the SSI to see अगर it needs to stop. BWC should
	 * always be a multiple of the frame size, so that we always transmit
	 * whole frames.  Each frame occupies two slots in the FIFO.  The
	 * parameter क्रम CCSR_DMA_MR_BWC() is rounded करोwn the next घातer of two
	 * (MR[BWC] can only represent even घातers of two).
	 *
	 * To simplअगरy the process, we set BWC to the largest value that is
	 * less than or equal to the FIFO watermark.  For playback, this ensures
	 * that we transfer the maximum amount without overrunning the FIFO.
	 * For capture, this ensures that we transfer the maximum amount without
	 * underrunning the FIFO.
	 *
	 * f = SSI FIFO depth
	 * w = SSI watermark value (which equals f - 2)
	 * b = DMA bandwidth count (in bytes)
	 * s = sample size (in bytes, which equals frame_size * 2)
	 *
	 * For playback, we never transmit more than the transmit FIFO
	 * watermark, otherwise we might ग_लिखो more data than the FIFO can hold.
	 * The watermark is equal to the FIFO depth minus two.
	 *
	 * For capture, two equations must hold:
	 *	w > f - (b / s)
	 *	w >= b / s
	 *
	 * So, b > 2 * s, but b must also be <= s * w.  To simplअगरy, we set
	 * b = s * w, which is equal to
	 *      (dma_निजी->ssi_fअगरo_depth - 2) * sample_bytes.
	 */
	mr |= CCSR_DMA_MR_BWC((dma_निजी->ssi_fअगरo_depth - 2) * sample_bytes);

	out_be32(&dma_channel->mr, mr);

	क्रम (i = 0; i < NUM_DMA_LINKS; i++) अणु
		काष्ठा fsl_dma_link_descriptor *link = &dma_निजी->link[i];

		link->count = cpu_to_be32(period_size);

		/* The snoop bit tells the DMA controller whether it should tell
		 * the ECM to snoop during a पढ़ो or ग_लिखो to an address. For
		 * audio, we use DMA to transfer data between memory and an I/O
		 * device (the SSI's STX0 or SRX0 रेजिस्टर). Snooping is only
		 * needed अगर there is a cache, so we need to snoop memory
		 * addresses only.  For playback, that means we snoop the source
		 * but not the destination.  For capture, we snoop the
		 * destination but not the source.
		 *
		 * Note that failing to snoop properly is unlikely to cause
		 * cache incoherency अगर the period size is larger than the
		 * size of L1 cache.  This is because filling in one period will
		 * flush out the data क्रम the previous period.  So अगर you
		 * increased period_bytes_min to a large enough size, you might
		 * get more perक्रमmance by not snooping, and you'll still be
		 * okay.  You'll need to update fsl_dma_update_poपूर्णांकers() also.
		 */
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			link->source_addr = cpu_to_be32(temp_addr);
			link->source_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
				upper_32_bits(temp_addr));

			link->dest_addr = cpu_to_be32(ssi_sxx_phys);
			link->dest_attr = cpu_to_be32(CCSR_DMA_ATR_NOSNOOP |
				upper_32_bits(ssi_sxx_phys));
		पूर्ण अन्यथा अणु
			link->source_addr = cpu_to_be32(ssi_sxx_phys);
			link->source_attr = cpu_to_be32(CCSR_DMA_ATR_NOSNOOP |
				upper_32_bits(ssi_sxx_phys));

			link->dest_addr = cpu_to_be32(temp_addr);
			link->dest_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
				upper_32_bits(temp_addr));
		पूर्ण

		temp_addr += period_size;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_dma_poपूर्णांकer: determine the current position of the DMA transfer
 *
 * This function is called by ALSA when ALSA wants to know where in the
 * stream buffer the hardware currently is.
 *
 * For playback, the SAR रेजिस्टर contains the physical address of the most
 * recent DMA transfer.  For capture, the value is in the DAR रेजिस्टर.
 *
 * The base address of the buffer is stored in the source_addr field of the
 * first link descriptor.
 */
अटल snd_pcm_uframes_t fsl_dma_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा ccsr_dma_channel __iomem *dma_channel = dma_निजी->dma_channel;
	dma_addr_t position;
	snd_pcm_uframes_t frames;

	/* Obtain the current DMA poपूर्णांकer, but करोn't पढ़ो the ESAD bits अगर we
	 * only have 32-bit DMA addresses.  This function is typically called
	 * in पूर्णांकerrupt context, so we need to optimize it.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		position = in_be32(&dma_channel->sar);
#अगर_घोषित CONFIG_PHYS_64BIT
		position |= (u64)(in_be32(&dma_channel->satr) &
				  CCSR_DMA_ATR_ESAD_MASK) << 32;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		position = in_be32(&dma_channel->dar);
#अगर_घोषित CONFIG_PHYS_64BIT
		position |= (u64)(in_be32(&dma_channel->datr) &
				  CCSR_DMA_ATR_ESAD_MASK) << 32;
#पूर्ण_अगर
	पूर्ण

	/*
	 * When capture is started, the SSI immediately starts to fill its FIFO.
	 * This means that the DMA controller is not started until the FIFO is
	 * full.  However, ALSA calls this function beक्रमe that happens, when
	 * MR.DAR is still zero.  In this हाल, just वापस zero to indicate
	 * that nothing has been received yet.
	 */
	अगर (!position)
		वापस 0;

	अगर ((position < dma_निजी->dma_buf_phys) ||
	    (position > dma_निजी->dma_buf_end)) अणु
		dev_err(dev, "dma pointer is out of range, halting stream\n");
		वापस SNDRV_PCM_POS_XRUN;
	पूर्ण

	frames = bytes_to_frames(runसमय, position - dma_निजी->dma_buf_phys);

	/*
	 * If the current address is just past the end of the buffer, wrap it
	 * around.
	 */
	अगर (frames == runसमय->buffer_size)
		frames = 0;

	वापस frames;
पूर्ण

/**
 * fsl_dma_hw_मुक्त: release resources allocated in fsl_dma_hw_params()
 *
 * Release the resources allocated in fsl_dma_hw_params() and de-program the
 * रेजिस्टरs.
 *
 * This function can be called multiple बार.
 */
अटल पूर्णांक fsl_dma_hw_मुक्त(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_dma_निजी *dma_निजी = runसमय->निजी_data;

	अगर (dma_निजी) अणु
		काष्ठा ccsr_dma_channel __iomem *dma_channel;

		dma_channel = dma_निजी->dma_channel;

		/* Stop the DMA */
		out_be32(&dma_channel->mr, CCSR_DMA_MR_CA);
		out_be32(&dma_channel->mr, 0);

		/* Reset all the other रेजिस्टरs */
		out_be32(&dma_channel->sr, -1);
		out_be32(&dma_channel->clndar, 0);
		out_be32(&dma_channel->eclndar, 0);
		out_be32(&dma_channel->satr, 0);
		out_be32(&dma_channel->sar, 0);
		out_be32(&dma_channel->datr, 0);
		out_be32(&dma_channel->dar, 0);
		out_be32(&dma_channel->bcr, 0);
		out_be32(&dma_channel->nlndar, 0);
		out_be32(&dma_channel->enlndar, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_dma_बंद: बंद the stream.
 */
अटल पूर्णांक fsl_dma_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा dma_object *dma =
		container_of(component->driver, काष्ठा dma_object, dai);

	अगर (dma_निजी) अणु
		अगर (dma_निजी->irq)
			मुक्त_irq(dma_निजी->irq, dma_निजी);

		/* Deallocate the fsl_dma_निजी काष्ठाure */
		dma_मुक्त_coherent(dev, माप(काष्ठा fsl_dma_निजी),
				  dma_निजी, dma_निजी->ld_buf_phys);
		substream->runसमय->निजी_data = शून्य;
	पूर्ण

	dma->asचिन्हित = false;

	वापस 0;
पूर्ण

/*
 * Remove this PCM driver.
 */
अटल व्योम fsl_dma_मुक्त_dma_buffers(काष्ठा snd_soc_component *component,
				     काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcm->streams); i++) अणु
		substream = pcm->streams[i].substream;
		अगर (substream) अणु
			snd_dma_मुक्त_pages(&substream->dma_buffer);
			substream->dma_buffer.area = शून्य;
			substream->dma_buffer.addr = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * find_ssi_node -- वापसs the SSI node that poपूर्णांकs to its DMA channel node
 *
 * Although this DMA driver attempts to operate independently of the other
 * devices, it still needs to determine some inक्रमmation about the SSI device
 * that it's working with.  Unक्रमtunately, the device tree करोes not contain
 * a poपूर्णांकer from the DMA channel node to the SSI node -- the poपूर्णांकer goes the
 * other way.  So we need to scan the device tree क्रम SSI nodes until we find
 * the one that poपूर्णांकs to the given DMA channel node.  It's ugly, but at least
 * it's contained in this one function.
 */
अटल काष्ठा device_node *find_ssi_node(काष्ठा device_node *dma_channel_np)
अणु
	काष्ठा device_node *ssi_np, *np;

	क्रम_each_compatible_node(ssi_np, शून्य, "fsl,mpc8610-ssi") अणु
		/* Check each DMA phandle to see अगर it poपूर्णांकs to us.  We
		 * assume that device_node poपूर्णांकers are a valid comparison.
		 */
		np = of_parse_phandle(ssi_np, "fsl,playback-dma", 0);
		of_node_put(np);
		अगर (np == dma_channel_np)
			वापस ssi_np;

		np = of_parse_phandle(ssi_np, "fsl,capture-dma", 0);
		of_node_put(np);
		अगर (np == dma_channel_np)
			वापस ssi_np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक fsl_soc_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dma_object *dma;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *ssi_np;
	काष्ठा resource res;
	स्थिर uपूर्णांक32_t *iprop;
	पूर्णांक ret;

	/* Find the SSI node that poपूर्णांकs to us. */
	ssi_np = find_ssi_node(np);
	अगर (!ssi_np) अणु
		dev_err(&pdev->dev, "cannot find parent SSI node\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_address_to_resource(ssi_np, 0, &res);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not determine resources for %pOF\n",
			ssi_np);
		of_node_put(ssi_np);
		वापस ret;
	पूर्ण

	dma = kzalloc(माप(*dma), GFP_KERNEL);
	अगर (!dma) अणु
		of_node_put(ssi_np);
		वापस -ENOMEM;
	पूर्ण

	dma->dai.name = DRV_NAME;
	dma->dai.खोलो = fsl_dma_खोलो;
	dma->dai.बंद = fsl_dma_बंद;
	dma->dai.hw_params = fsl_dma_hw_params;
	dma->dai.hw_मुक्त = fsl_dma_hw_मुक्त;
	dma->dai.poपूर्णांकer = fsl_dma_poपूर्णांकer;
	dma->dai.pcm_स्थिरruct = fsl_dma_new;
	dma->dai.pcm_deकाष्ठा = fsl_dma_मुक्त_dma_buffers;

	/* Store the SSI-specअगरic inक्रमmation that we need */
	dma->ssi_stx_phys = res.start + REG_SSI_STX0;
	dma->ssi_srx_phys = res.start + REG_SSI_SRX0;

	iprop = of_get_property(ssi_np, "fsl,fifo-depth", शून्य);
	अगर (iprop)
		dma->ssi_fअगरo_depth = be32_to_cpup(iprop);
	अन्यथा
                /* Older 8610 DTs didn't have the fअगरo-depth property */
		dma->ssi_fअगरo_depth = 8;

	of_node_put(ssi_np);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &dma->dai, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register platform\n");
		kमुक्त(dma);
		वापस ret;
	पूर्ण

	dma->channel = of_iomap(np, 0);
	dma->irq = irq_of_parse_and_map(np, 0);

	dev_set_drvdata(&pdev->dev, dma);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_soc_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dma_object *dma = dev_get_drvdata(&pdev->dev);

	iounmap(dma->channel);
	irq_dispose_mapping(dma->irq);
	kमुक्त(dma);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_soc_dma_ids[] = अणु
	अणु .compatible = "fsl,ssi-dma-channel", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_soc_dma_ids);

अटल काष्ठा platक्रमm_driver fsl_soc_dma_driver = अणु
	.driver = अणु
		.name = "fsl-pcm-audio",
		.of_match_table = fsl_soc_dma_ids,
	पूर्ण,
	.probe = fsl_soc_dma_probe,
	.हटाओ = fsl_soc_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_soc_dma_driver);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale Elo DMA ASoC PCM Driver");
MODULE_LICENSE("GPL v2");
