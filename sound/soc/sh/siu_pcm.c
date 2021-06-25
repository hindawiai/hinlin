<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// siu_pcm.c - ALSA driver क्रम Renesas SH7343, SH7722 SIU peripheral.
//
// Copyright (C) 2009-2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
// Copyright (C) 2006 Carlos Munoz <carlos@kenati.com>

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/siu.h>

#समावेश "siu.h"

#घोषणा DRV_NAME "siu-i2s"
#घोषणा GET_MAX_PERIODS(buf_bytes, period_bytes) \
				((buf_bytes) / (period_bytes))
#घोषणा PERIOD_OFFSET(buf_addr, period_num, period_bytes) \
				((buf_addr) + ((period_num) * (period_bytes)))

#घोषणा RWF_STM_RD		0x01		/* Read in progress */
#घोषणा RWF_STM_WT		0x02		/* Write in progress */

काष्ठा siu_port *siu_ports[SIU_PORT_NUM];

/* transfersize is number of u32 dma transfers per period */
अटल पूर्णांक siu_pcm_sपंचांगग_लिखो_stop(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_stream *siu_stream = &port_info->playback;
	u32 stfअगरo;

	अगर (!siu_stream->rw_flg)
		वापस -EPERM;

	/* output FIFO disable */
	stfअगरo = siu_पढ़ो32(base + SIU_STFIFO);
	siu_ग_लिखो32(base + SIU_STFIFO, stfअगरo & ~0x0c180c18);
	pr_debug("%s: STFIFO %x -> %x\n", __func__,
		 stfअगरo, stfअगरo & ~0x0c180c18);

	/* during sपंचांगग_लिखो clear */
	siu_stream->rw_flg = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_sपंचांगग_लिखो_start(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_stream *siu_stream = &port_info->playback;

	अगर (siu_stream->rw_flg)
		वापस -EPERM;

	/* Current period in buffer */
	port_info->playback.cur_period = 0;

	/* during sपंचांगग_लिखो flag set */
	siu_stream->rw_flg = RWF_STM_WT;

	/* DMA transfer start */
	queue_work(प्रणाली_highpri_wq, &siu_stream->work);

	वापस 0;
पूर्ण

अटल व्योम siu_dma_tx_complete(व्योम *arg)
अणु
	काष्ठा siu_stream *siu_stream = arg;

	अगर (!siu_stream->rw_flg)
		वापस;

	/* Update completed period count */
	अगर (++siu_stream->cur_period >=
	    GET_MAX_PERIODS(siu_stream->buf_bytes,
			    siu_stream->period_bytes))
		siu_stream->cur_period = 0;

	pr_debug("%s: done period #%d (%u/%u bytes), cookie %d\n",
		__func__, siu_stream->cur_period,
		siu_stream->cur_period * siu_stream->period_bytes,
		siu_stream->buf_bytes, siu_stream->cookie);

	queue_work(प्रणाली_highpri_wq, &siu_stream->work);

	/* Notअगरy alsa: a period is करोne */
	snd_pcm_period_elapsed(siu_stream->substream);
पूर्ण

अटल पूर्णांक siu_pcm_wr_set(काष्ठा siu_port *port_info,
			  dma_addr_t buff, u32 size)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_stream *siu_stream = &port_info->playback;
	काष्ठा snd_pcm_substream *substream = siu_stream->substream;
	काष्ठा device *dev = substream->pcm->card->dev;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	काष्ठा scatterlist sg;
	u32 stfअगरo;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, pfn_to_page(PFN_DOWN(buff)),
		    size, offset_in_page(buff));
	sg_dma_len(&sg) = size;
	sg_dma_address(&sg) = buff;

	desc = dmaengine_prep_slave_sg(siu_stream->chan,
		&sg, 1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(dev, "Failed to allocate a dma descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	desc->callback = siu_dma_tx_complete;
	desc->callback_param = siu_stream;
	cookie = dmaengine_submit(desc);
	अगर (cookie < 0) अणु
		dev_err(dev, "Failed to submit a dma transfer\n");
		वापस cookie;
	पूर्ण

	siu_stream->tx_desc = desc;
	siu_stream->cookie = cookie;

	dma_async_issue_pending(siu_stream->chan);

	/* only output FIFO enable */
	stfअगरo = siu_पढ़ो32(base + SIU_STFIFO);
	siu_ग_लिखो32(base + SIU_STFIFO, stfअगरo | (port_info->stfअगरo & 0x0c180c18));
	dev_dbg(dev, "%s: STFIFO %x -> %x\n", __func__,
		stfअगरo, stfअगरo | (port_info->stfअगरo & 0x0c180c18));

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_rd_set(काष्ठा siu_port *port_info,
			  dma_addr_t buff, माप_प्रकार size)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_stream *siu_stream = &port_info->capture;
	काष्ठा snd_pcm_substream *substream = siu_stream->substream;
	काष्ठा device *dev = substream->pcm->card->dev;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	काष्ठा scatterlist sg;
	u32 stfअगरo;

	dev_dbg(dev, "%s: %u@%llx\n", __func__, size, (अचिन्हित दीर्घ दीर्घ)buff);

	sg_init_table(&sg, 1);
	sg_set_page(&sg, pfn_to_page(PFN_DOWN(buff)),
		    size, offset_in_page(buff));
	sg_dma_len(&sg) = size;
	sg_dma_address(&sg) = buff;

	desc = dmaengine_prep_slave_sg(siu_stream->chan,
		&sg, 1, DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(dev, "Failed to allocate dma descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	desc->callback = siu_dma_tx_complete;
	desc->callback_param = siu_stream;
	cookie = dmaengine_submit(desc);
	अगर (cookie < 0) अणु
		dev_err(dev, "Failed to submit dma descriptor\n");
		वापस cookie;
	पूर्ण

	siu_stream->tx_desc = desc;
	siu_stream->cookie = cookie;

	dma_async_issue_pending(siu_stream->chan);

	/* only input FIFO enable */
	stfअगरo = siu_पढ़ो32(base + SIU_STFIFO);
	siu_ग_लिखो32(base + SIU_STFIFO, siu_पढ़ो32(base + SIU_STFIFO) |
		    (port_info->stfअगरo & 0x13071307));
	dev_dbg(dev, "%s: STFIFO %x -> %x\n", __func__,
		stfअगरo, stfअगरo | (port_info->stfअगरo & 0x13071307));

	वापस 0;
पूर्ण

अटल व्योम siu_io_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा siu_stream *siu_stream = container_of(work, काष्ठा siu_stream,
						     work);
	काष्ठा snd_pcm_substream *substream = siu_stream->substream;
	काष्ठा device *dev = substream->pcm->card->dev;
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा siu_port *port_info = siu_port_info(substream);

	dev_dbg(dev, "%s: flags %x\n", __func__, siu_stream->rw_flg);

	अगर (!siu_stream->rw_flg) अणु
		dev_dbg(dev, "%s: stream inactive\n", __func__);
		वापस;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		dma_addr_t buff;
		माप_प्रकार count;

		buff = (dma_addr_t)PERIOD_OFFSET(rt->dma_addr,
						siu_stream->cur_period,
						siu_stream->period_bytes);
		count = siu_stream->period_bytes;

		/* DMA transfer start */
		siu_pcm_rd_set(port_info, buff, count);
	पूर्ण अन्यथा अणु
		siu_pcm_wr_set(port_info,
			       (dma_addr_t)PERIOD_OFFSET(rt->dma_addr,
						siu_stream->cur_period,
						siu_stream->period_bytes),
			       siu_stream->period_bytes);
	पूर्ण
पूर्ण

/* Capture */
अटल पूर्णांक siu_pcm_sपंचांगपढ़ो_start(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_stream *siu_stream = &port_info->capture;

	अगर (siu_stream->xfer_cnt > 0x1000000)
		वापस -EINVAL;
	अगर (siu_stream->rw_flg)
		वापस -EPERM;

	/* Current period in buffer */
	siu_stream->cur_period = 0;

	/* during sपंचांगपढ़ो flag set */
	siu_stream->rw_flg = RWF_STM_RD;

	queue_work(प्रणाली_highpri_wq, &siu_stream->work);

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_sपंचांगपढ़ो_stop(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_stream *siu_stream = &port_info->capture;
	काष्ठा device *dev = siu_stream->substream->pcm->card->dev;
	u32 stfअगरo;

	अगर (!siu_stream->rw_flg)
		वापस -EPERM;

	/* input FIFO disable */
	stfअगरo = siu_पढ़ो32(base + SIU_STFIFO);
	siu_ग_लिखो32(base + SIU_STFIFO, stfअगरo & ~0x13071307);
	dev_dbg(dev, "%s: STFIFO %x -> %x\n", __func__,
		stfअगरo, stfअगरo & ~0x13071307);

	/* during sपंचांगपढ़ो flag clear */
	siu_stream->rw_flg = 0;

	वापस 0;
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *secondary)
अणु
	काष्ठा sh_dmae_slave *param = secondary;

	pr_debug("%s: secondary ID %d\n", __func__, param->shdma_slave.slave_id);

	chan->निजी = &param->shdma_slave;
	वापस true;
पूर्ण

अटल पूर्णांक siu_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *ss)
अणु
	/* Playback / Capture */
	काष्ठा siu_platक्रमm *pdata = component->dev->platक्रमm_data;
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा siu_port *port_info = siu_port_info(ss);
	काष्ठा siu_stream *siu_stream;
	u32 port = info->port_id;
	काष्ठा device *dev = ss->pcm->card->dev;
	dma_cap_mask_t mask;
	काष्ठा sh_dmae_slave *param;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	dev_dbg(dev, "%s, port=%d@%p\n", __func__, port, port_info);

	अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		siu_stream = &port_info->playback;
		param = &siu_stream->param;
		param->shdma_slave.slave_id = port ? pdata->dma_slave_tx_b :
			pdata->dma_slave_tx_a;
	पूर्ण अन्यथा अणु
		siu_stream = &port_info->capture;
		param = &siu_stream->param;
		param->shdma_slave.slave_id = port ? pdata->dma_slave_rx_b :
			pdata->dma_slave_rx_a;
	पूर्ण

	/* Get DMA channel */
	siu_stream->chan = dma_request_channel(mask, filter, param);
	अगर (!siu_stream->chan) अणु
		dev_err(dev, "DMA channel allocation failed!\n");
		वापस -EBUSY;
	पूर्ण

	siu_stream->substream = ss;

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा device *dev = ss->pcm->card->dev;
	काष्ठा siu_port *port_info = siu_port_info(ss);
	काष्ठा siu_stream *siu_stream;

	dev_dbg(dev, "%s: port=%d\n", __func__, info->port_id);

	अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
		siu_stream = &port_info->playback;
	अन्यथा
		siu_stream = &port_info->capture;

	dma_release_channel(siu_stream->chan);
	siu_stream->chan = शून्य;

	siu_stream->substream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_prepare(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा siu_port *port_info = siu_port_info(ss);
	काष्ठा device *dev = ss->pcm->card->dev;
	काष्ठा snd_pcm_runसमय *rt;
	काष्ठा siu_stream *siu_stream;
	snd_pcm_sframes_t xfer_cnt;

	अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
		siu_stream = &port_info->playback;
	अन्यथा
		siu_stream = &port_info->capture;

	rt = siu_stream->substream->runसमय;

	siu_stream->buf_bytes = snd_pcm_lib_buffer_bytes(ss);
	siu_stream->period_bytes = snd_pcm_lib_period_bytes(ss);

	dev_dbg(dev, "%s: port=%d, %d channels, period=%u bytes\n", __func__,
		info->port_id, rt->channels, siu_stream->period_bytes);

	/* We only support buffers that are multiples of the period */
	अगर (siu_stream->buf_bytes % siu_stream->period_bytes) अणु
		dev_err(dev, "%s() - buffer=%d not multiple of period=%d\n",
		       __func__, siu_stream->buf_bytes,
		       siu_stream->period_bytes);
		वापस -EINVAL;
	पूर्ण

	xfer_cnt = bytes_to_frames(rt, siu_stream->period_bytes);
	अगर (!xfer_cnt || xfer_cnt > 0x1000000)
		वापस -EINVAL;

	siu_stream->क्रमmat = rt->क्रमmat;
	siu_stream->xfer_cnt = xfer_cnt;

	dev_dbg(dev, "port=%d buf=%lx buf_bytes=%d period_bytes=%d "
		"format=%d channels=%d xfer_cnt=%d\n", info->port_id,
		(अचिन्हित दीर्घ)rt->dma_addr, siu_stream->buf_bytes,
		siu_stream->period_bytes,
		siu_stream->क्रमmat, rt->channels, (पूर्णांक)xfer_cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक siu_pcm_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा device *dev = ss->pcm->card->dev;
	काष्ठा siu_port *port_info = siu_port_info(ss);
	पूर्णांक ret;

	dev_dbg(dev, "%s: port=%d@%p, cmd=%d\n", __func__,
		info->port_id, port_info, cmd);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = siu_pcm_sपंचांगग_लिखो_start(port_info);
		अन्यथा
			ret = siu_pcm_sपंचांगपढ़ो_start(port_info);

		अगर (ret < 0)
			dev_warn(dev, "%s: start failed on port=%d\n",
				 __func__, info->port_id);

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
			siu_pcm_sपंचांगग_लिखो_stop(port_info);
		अन्यथा
			siu_pcm_sपंचांगपढ़ो_stop(port_info);
		ret = 0;

		अवरोध;
	शेष:
		dev_err(dev, "%s() unsupported cmd=%d\n", __func__, cmd);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * So far only resolution of one period is supported, subject to extending the
 * dmangine API
 */
अटल snd_pcm_uframes_t
siu_pcm_poपूर्णांकer_dma(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा device *dev = ss->pcm->card->dev;
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_port *port_info = siu_port_info(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	माप_प्रकार ptr;
	काष्ठा siu_stream *siu_stream;

	अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
		siu_stream = &port_info->playback;
	अन्यथा
		siu_stream = &port_info->capture;

	/*
	 * ptr is the offset पूर्णांकo the buffer where the dma is currently at. We
	 * check अगर the dma buffer has just wrapped.
	 */
	ptr = PERIOD_OFFSET(rt->dma_addr,
			    siu_stream->cur_period,
			    siu_stream->period_bytes) - rt->dma_addr;

	dev_dbg(dev,
		"%s: port=%d, events %x, FSTS %x, xferred %u/%u, cookie %d\n",
		__func__, info->port_id, siu_पढ़ो32(base + SIU_EVNTC),
		siu_पढ़ो32(base + SIU_SBFSTS), ptr, siu_stream->buf_bytes,
		siu_stream->cookie);

	अगर (ptr >= siu_stream->buf_bytes)
		ptr = 0;

	वापस bytes_to_frames(ss->runसमय, ptr);
पूर्ण

अटल पूर्णांक siu_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	/* card->dev == socdev->dev, see snd_soc_new_pcms() */
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(card->dev);
	पूर्णांक ret;
	पूर्णांक i;

	/* pdev->id selects between SIUA and SIUB */
	अगर (pdev->id < 0 || pdev->id >= SIU_PORT_NUM)
		वापस -EINVAL;

	info->port_id = pdev->id;

	/*
	 * While the siu has 2 ports, only one port can be on at a समय (only 1
	 * SPB). So far all the boards using the siu had only one of the ports
	 * wired to a codec. To simplअगरy things, we only रेजिस्टर one port with
	 * alsa. In हाल both ports are needed, it should be changed here
	 */
	क्रम (i = pdev->id; i < pdev->id + 1; i++) अणु
		काष्ठा siu_port **port_info = &siu_ports[i];

		ret = siu_init_port(i, port_info, card);
		अगर (ret < 0)
			वापस ret;

		snd_pcm_set_managed_buffer_all(pcm,
				SNDRV_DMA_TYPE_DEV, card->dev,
				SIU_BUFFER_BYTES_MAX, SIU_BUFFER_BYTES_MAX);

		(*port_info)->pcm = pcm;

		/* IO works */
		INIT_WORK(&(*port_info)->playback.work, siu_io_work);
		INIT_WORK(&(*port_info)->capture.work, siu_io_work);
	पूर्ण

	dev_info(card->dev, "SuperH SIU driver initialized.\n");
	वापस 0;
पूर्ण

अटल व्योम siu_pcm_मुक्त(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm *pcm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(pcm->card->dev);
	काष्ठा siu_port *port_info = siu_ports[pdev->id];

	cancel_work_sync(&port_info->capture.work);
	cancel_work_sync(&port_info->playback.work);

	siu_मुक्त_port(port_info);

	dev_dbg(pcm->card->dev, "%s\n", __func__);
पूर्ण

स्थिर काष्ठा snd_soc_component_driver siu_component = अणु
	.name		= DRV_NAME,
	.खोलो		= siu_pcm_खोलो,
	.बंद		= siu_pcm_बंद,
	.prepare	= siu_pcm_prepare,
	.trigger	= siu_pcm_trigger,
	.poपूर्णांकer	= siu_pcm_poपूर्णांकer_dma,
	.pcm_स्थिरruct	= siu_pcm_new,
	.pcm_deकाष्ठा	= siu_pcm_मुक्त,
पूर्ण;
EXPORT_SYMBOL_GPL(siu_component);
