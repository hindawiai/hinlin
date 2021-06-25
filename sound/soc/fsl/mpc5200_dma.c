<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Freescale MPC5200 PSC DMA
// ALSA SoC Platक्रमm driver
//
// Copyright (C) 2008 Secret Lab Technologies Ltd.
// Copyright (C) 2009 Jon Smirl, Digispeaker

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <sound/soc.h>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/gen_bd.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश "mpc5200_dma.h"

#घोषणा DRV_NAME "mpc5200_dma"

/*
 * Interrupt handlers
 */
अटल irqवापस_t psc_dma_status_irq(पूर्णांक irq, व्योम *_psc_dma)
अणु
	काष्ठा psc_dma *psc_dma = _psc_dma;
	काष्ठा mpc52xx_psc __iomem *regs = psc_dma->psc_regs;
	u16 isr;

	isr = in_be16(&regs->mpc52xx_psc_isr);

	/* Playback underrun error */
	अगर (psc_dma->playback.active && (isr & MPC52xx_PSC_IMR_TXEMP))
		psc_dma->stats.underrun_count++;

	/* Capture overrun error */
	अगर (psc_dma->capture.active && (isr & MPC52xx_PSC_IMR_ORERR))
		psc_dma->stats.overrun_count++;

	out_8(&regs->command, MPC52xx_PSC_RST_ERR_STAT);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * psc_dma_bcom_enqueue_next_buffer - Enqueue another audio buffer
 * @s: poपूर्णांकer to stream निजी data काष्ठाure
 *
 * Enqueues another audio period buffer पूर्णांकo the bestcomm queue.
 *
 * Note: The routine must only be called when there is space available in
 * the queue.  Otherwise the enqueue will fail and the audio ring buffer
 * will get out of sync
 */
अटल व्योम psc_dma_bcom_enqueue_next_buffer(काष्ठा psc_dma_stream *s)
अणु
	काष्ठा bcom_bd *bd;

	/* Prepare and enqueue the next buffer descriptor */
	bd = bcom_prepare_next_buffer(s->bcom_task);
	bd->status = s->period_bytes;
	bd->data[0] = s->runसमय->dma_addr + (s->period_next * s->period_bytes);
	bcom_submit_next_buffer(s->bcom_task, शून्य);

	/* Update क्रम next period */
	s->period_next = (s->period_next + 1) % s->runसमय->periods;
पूर्ण

/* Bestcomm DMA irq handler */
अटल irqवापस_t psc_dma_bcom_irq(पूर्णांक irq, व्योम *_psc_dma_stream)
अणु
	काष्ठा psc_dma_stream *s = _psc_dma_stream;

	spin_lock(&s->psc_dma->lock);
	/* For each finished period, dequeue the completed period buffer
	 * and enqueue a new one in it's place. */
	जबतक (bcom_buffer_करोne(s->bcom_task)) अणु
		bcom_retrieve_buffer(s->bcom_task, शून्य, शून्य);

		s->period_current = (s->period_current+1) % s->runसमय->periods;
		s->period_count++;

		psc_dma_bcom_enqueue_next_buffer(s);
	पूर्ण
	spin_unlock(&s->psc_dma->lock);

	/* If the stream is active, then also inक्रमm the PCM middle layer
	 * of the period finished event. */
	अगर (s->active)
		snd_pcm_period_elapsed(s->stream);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक psc_dma_hw_मुक्त(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_set_runसमय_buffer(substream, शून्य);
	वापस 0;
पूर्ण

/**
 * psc_dma_trigger: start and stop the DMA transfer.
 *
 * This function is called by ALSA to start, stop, छोड़ो, and resume the DMA
 * transfer of data.
 */
अटल पूर्णांक psc_dma_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा psc_dma_stream *s = to_psc_dma_stream(substream, psc_dma);
	काष्ठा mpc52xx_psc __iomem *regs = psc_dma->psc_regs;
	u16 imr;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dev_dbg(psc_dma->dev, "START: stream=%i fbits=%u ps=%u #p=%u\n",
			substream->pstr->stream, runसमय->frame_bits,
			(पूर्णांक)runसमय->period_size, runसमय->periods);
		s->period_bytes = frames_to_bytes(runसमय,
						  runसमय->period_size);
		s->period_next = 0;
		s->period_current = 0;
		s->active = 1;
		s->period_count = 0;
		s->runसमय = runसमय;

		/* Fill up the bestcomm bd queue and enable DMA.
		 * This will begin filling the PSC's fअगरo.
		 */
		spin_lock_irqsave(&psc_dma->lock, flags);

		अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
			bcom_gen_bd_rx_reset(s->bcom_task);
		अन्यथा
			bcom_gen_bd_tx_reset(s->bcom_task);

		क्रम (i = 0; i < runसमय->periods; i++)
			अगर (!bcom_queue_full(s->bcom_task))
				psc_dma_bcom_enqueue_next_buffer(s);

		bcom_enable(s->bcom_task);
		spin_unlock_irqrestore(&psc_dma->lock, flags);

		out_8(&regs->command, MPC52xx_PSC_RST_ERR_STAT);

		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(psc_dma->dev, "STOP: stream=%i periods_count=%i\n",
			substream->pstr->stream, s->period_count);
		s->active = 0;

		spin_lock_irqsave(&psc_dma->lock, flags);
		bcom_disable(s->bcom_task);
		अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
			bcom_gen_bd_rx_reset(s->bcom_task);
		अन्यथा
			bcom_gen_bd_tx_reset(s->bcom_task);
		spin_unlock_irqrestore(&psc_dma->lock, flags);

		अवरोध;

	शेष:
		dev_dbg(psc_dma->dev, "unhandled trigger: stream=%i cmd=%i\n",
			substream->pstr->stream, cmd);
		वापस -EINVAL;
	पूर्ण

	/* Update पूर्णांकerrupt enable settings */
	imr = 0;
	अगर (psc_dma->playback.active)
		imr |= MPC52xx_PSC_IMR_TXEMP;
	अगर (psc_dma->capture.active)
		imr |= MPC52xx_PSC_IMR_ORERR;
	out_be16(&regs->isr_imr.imr, psc_dma->imr | imr);

	वापस 0;
पूर्ण


/* ---------------------------------------------------------------------
 * The PSC DMA 'ASoC platform' driver
 *
 * Can be referenced by an 'ASoC machine' driver
 * This driver only deals with the audio bus; it करोesn't have any
 * पूर्णांकeraction with the attached codec
 */

अटल स्थिर काष्ठा snd_pcm_hardware psc_dma_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_BATCH,
	.क्रमmats = SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_BE |
		SNDRV_PCM_FMTBIT_S24_BE | SNDRV_PCM_FMTBIT_S32_BE,
	.period_bytes_max	= 1024 * 1024,
	.period_bytes_min	= 32,
	.periods_min		= 2,
	.periods_max		= 256,
	.buffer_bytes_max	= 2 * 1024 * 1024,
	.fअगरo_size		= 512,
पूर्ण;

अटल पूर्णांक psc_dma_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा psc_dma_stream *s;
	पूर्णांक rc;

	dev_dbg(psc_dma->dev, "psc_dma_open(substream=%p)\n", substream);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		s = &psc_dma->capture;
	अन्यथा
		s = &psc_dma->playback;

	snd_soc_set_runसमय_hwparams(substream, &psc_dma_hardware);

	rc = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
		SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (rc < 0) अणु
		dev_err(substream->pcm->card->dev, "invalid buffer size\n");
		वापस rc;
	पूर्ण

	s->stream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक psc_dma_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा psc_dma_stream *s;

	dev_dbg(psc_dma->dev, "psc_dma_close(substream=%p)\n", substream);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		s = &psc_dma->capture;
	अन्यथा
		s = &psc_dma->playback;

	अगर (!psc_dma->playback.active &&
	    !psc_dma->capture.active) अणु

		/* Disable all पूर्णांकerrupts and reset the PSC */
		out_be16(&psc_dma->psc_regs->isr_imr.imr, psc_dma->imr);
		out_8(&psc_dma->psc_regs->command, 4 << 4); /* reset error */
	पूर्ण
	s->stream = शून्य;
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
psc_dma_poपूर्णांकer(काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा psc_dma_stream *s;
	dma_addr_t count;

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		s = &psc_dma->capture;
	अन्यथा
		s = &psc_dma->playback;

	count = s->period_current * s->period_bytes;

	वापस bytes_to_frames(substream->runसमय, count);
पूर्ण

अटल पूर्णांक psc_dma_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक psc_dma_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_pcm *pcm = rtd->pcm;
	माप_प्रकार size = psc_dma_hardware.buffer_bytes_max;
	पूर्णांक rc;

	dev_dbg(component->dev, "psc_dma_new(card=%p, dai=%p, pcm=%p)\n",
		card, dai, pcm);

	rc = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		rc = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, pcm->card->dev,
				size, &pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);
		अगर (rc)
			जाओ playback_alloc_err;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		rc = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, pcm->card->dev,
				size, &pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream->dma_buffer);
		अगर (rc)
			जाओ capture_alloc_err;
	पूर्ण

	वापस 0;

 capture_alloc_err:
	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream)
		snd_dma_मुक्त_pages(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);

 playback_alloc_err:
	dev_err(card->dev, "Cannot allocate buffer(s)\n");

	वापस -ENOMEM;
पूर्ण

अटल व्योम psc_dma_मुक्त(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक stream;

	dev_dbg(component->dev, "psc_dma_free(pcm=%p)\n", pcm);

	क्रम (stream = 0; stream < 2; stream++) अणु
		substream = pcm->streams[stream].substream;
		अगर (substream) अणु
			snd_dma_मुक्त_pages(&substream->dma_buffer);
			substream->dma_buffer.area = शून्य;
			substream->dma_buffer.addr = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mpc5200_audio_dma_component = अणु
	.name		= DRV_NAME,
	.खोलो		= psc_dma_खोलो,
	.बंद		= psc_dma_बंद,
	.hw_मुक्त	= psc_dma_hw_मुक्त,
	.poपूर्णांकer	= psc_dma_poपूर्णांकer,
	.trigger	= psc_dma_trigger,
	.hw_params	= psc_dma_hw_params,
	.pcm_स्थिरruct	= psc_dma_new,
	.pcm_deकाष्ठा	= psc_dma_मुक्त,
पूर्ण;

पूर्णांक mpc5200_audio_dma_create(काष्ठा platक्रमm_device *op)
अणु
	phys_addr_t fअगरo;
	काष्ठा psc_dma *psc_dma;
	काष्ठा resource res;
	पूर्णांक size, irq, rc;
	स्थिर __be32 *prop;
	व्योम __iomem *regs;
	पूर्णांक ret;

	/* Fetch the रेजिस्टरs and IRQ of the PSC */
	irq = irq_of_parse_and_map(op->dev.of_node, 0);
	अगर (of_address_to_resource(op->dev.of_node, 0, &res)) अणु
		dev_err(&op->dev, "Missing reg property\n");
		वापस -ENODEV;
	पूर्ण
	regs = ioremap(res.start, resource_size(&res));
	अगर (!regs) अणु
		dev_err(&op->dev, "Could not map registers\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate and initialize the driver निजी data */
	psc_dma = kzalloc(माप *psc_dma, GFP_KERNEL);
	अगर (!psc_dma) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	/* Get the PSC ID */
	prop = of_get_property(op->dev.of_node, "cell-index", &size);
	अगर (!prop || size < माप *prop) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_init(&psc_dma->lock);
	mutex_init(&psc_dma->mutex);
	psc_dma->id = be32_to_cpu(*prop);
	psc_dma->irq = irq;
	psc_dma->psc_regs = regs;
	psc_dma->fअगरo_regs = regs + माप *psc_dma->psc_regs;
	psc_dma->dev = &op->dev;
	psc_dma->playback.psc_dma = psc_dma;
	psc_dma->capture.psc_dma = psc_dma;
	snम_लिखो(psc_dma->name, माप(psc_dma->name), "PSC%d", psc_dma->id);

	/* Find the address of the fअगरo data रेजिस्टरs and setup the
	 * DMA tasks */
	fअगरo = res.start + दुरत्व(काष्ठा mpc52xx_psc, buffer.buffer_32);
	psc_dma->capture.bcom_task =
		bcom_psc_gen_bd_rx_init(psc_dma->id, 10, fअगरo, 512);
	psc_dma->playback.bcom_task =
		bcom_psc_gen_bd_tx_init(psc_dma->id, 10, fअगरo);
	अगर (!psc_dma->capture.bcom_task ||
	    !psc_dma->playback.bcom_task) अणु
		dev_err(&op->dev, "Could not allocate bestcomm tasks\n");
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	/* Disable all पूर्णांकerrupts and reset the PSC */
	out_be16(&psc_dma->psc_regs->isr_imr.imr, psc_dma->imr);
	 /* reset receiver */
	out_8(&psc_dma->psc_regs->command, MPC52xx_PSC_RST_RX);
	 /* reset transmitter */
	out_8(&psc_dma->psc_regs->command, MPC52xx_PSC_RST_TX);
	 /* reset error */
	out_8(&psc_dma->psc_regs->command, MPC52xx_PSC_RST_ERR_STAT);
	 /* reset mode */
	out_8(&psc_dma->psc_regs->command, MPC52xx_PSC_SEL_MODE_REG_1);

	/* Set up mode रेजिस्टर;
	 * First ग_लिखो: RxRdy (FIFO Alarm) generates rx FIFO irq
	 * Second ग_लिखो: रेजिस्टर Normal mode क्रम non loopback
	 */
	out_8(&psc_dma->psc_regs->mode, 0);
	out_8(&psc_dma->psc_regs->mode, 0);

	/* Set the TX and RX fअगरo alarm thresholds */
	out_be16(&psc_dma->fअगरo_regs->rfalarm, 0x100);
	out_8(&psc_dma->fअगरo_regs->rfcntl, 0x4);
	out_be16(&psc_dma->fअगरo_regs->tfalarm, 0x100);
	out_8(&psc_dma->fअगरo_regs->tfcntl, 0x7);

	/* Lookup the IRQ numbers */
	psc_dma->playback.irq =
		bcom_get_task_irq(psc_dma->playback.bcom_task);
	psc_dma->capture.irq =
		bcom_get_task_irq(psc_dma->capture.bcom_task);

	rc = request_irq(psc_dma->irq, &psc_dma_status_irq, IRQF_SHARED,
			 "psc-dma-status", psc_dma);
	rc |= request_irq(psc_dma->capture.irq, &psc_dma_bcom_irq, IRQF_SHARED,
			  "psc-dma-capture", &psc_dma->capture);
	rc |= request_irq(psc_dma->playback.irq, &psc_dma_bcom_irq, IRQF_SHARED,
			  "psc-dma-playback", &psc_dma->playback);
	अगर (rc) अणु
		ret = -ENODEV;
		जाओ out_irq;
	पूर्ण

	/* Save what we've करोne so it can be found again later */
	dev_set_drvdata(&op->dev, psc_dma);

	/* Tell the ASoC OF helpers about it */
	वापस devm_snd_soc_रेजिस्टर_component(&op->dev,
					&mpc5200_audio_dma_component, शून्य, 0);
out_irq:
	मुक्त_irq(psc_dma->irq, psc_dma);
	मुक्त_irq(psc_dma->capture.irq, &psc_dma->capture);
	मुक्त_irq(psc_dma->playback.irq, &psc_dma->playback);
out_मुक्त:
	kमुक्त(psc_dma);
out_unmap:
	iounmap(regs);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mpc5200_audio_dma_create);

पूर्णांक mpc5200_audio_dma_destroy(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा psc_dma *psc_dma = dev_get_drvdata(&op->dev);

	dev_dbg(&op->dev, "mpc5200_audio_dma_destroy()\n");

	bcom_gen_bd_rx_release(psc_dma->capture.bcom_task);
	bcom_gen_bd_tx_release(psc_dma->playback.bcom_task);

	/* Release irqs */
	मुक्त_irq(psc_dma->irq, psc_dma);
	मुक्त_irq(psc_dma->capture.irq, &psc_dma->capture);
	मुक्त_irq(psc_dma->playback.irq, &psc_dma->playback);

	iounmap(psc_dma->psc_regs);
	kमुक्त(psc_dma);
	dev_set_drvdata(&op->dev, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpc5200_audio_dma_destroy);

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_DESCRIPTION("Freescale MPC5200 PSC in DMA mode ASoC Driver");
MODULE_LICENSE("GPL");
