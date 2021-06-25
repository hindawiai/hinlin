<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Spपढ़ोtrum Communications Inc.

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/sprd-dma.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>

#समावेश "sprd-pcm-dma.h"

#घोषणा SPRD_COMPR_DMA_CHANS		2

/* Default values अगर userspace करोes not set */
#घोषणा SPRD_COMPR_MIN_FRAGMENT_SIZE	SZ_8K
#घोषणा SPRD_COMPR_MAX_FRAGMENT_SIZE	SZ_128K
#घोषणा SPRD_COMPR_MIN_NUM_FRAGMENTS	4
#घोषणा SPRD_COMPR_MAX_NUM_FRAGMENTS	64

/* DSP FIFO size */
#घोषणा SPRD_COMPR_MCDT_EMPTY_WMK	0
#घोषणा SPRD_COMPR_MCDT_FIFO_SIZE	512

/* Stage 0 IRAM buffer size definition */
#घोषणा SPRD_COMPR_IRAM_BUF_SIZE	SZ_32K
#घोषणा SPRD_COMPR_IRAM_INFO_SIZE	(माप(काष्ठा sprd_compr_playinfo))
#घोषणा SPRD_COMPR_IRAM_LINKLIST_SIZE	(1024 - SPRD_COMPR_IRAM_INFO_SIZE)
#घोषणा SPRD_COMPR_IRAM_SIZE		(SPRD_COMPR_IRAM_BUF_SIZE + \
					 SPRD_COMPR_IRAM_INFO_SIZE + \
					 SPRD_COMPR_IRAM_LINKLIST_SIZE)

/* Stage 1 DDR buffer size definition */
#घोषणा SPRD_COMPR_AREA_BUF_SIZE	SZ_2M
#घोषणा SPRD_COMPR_AREA_LINKLIST_SIZE	1024
#घोषणा SPRD_COMPR_AREA_SIZE		(SPRD_COMPR_AREA_BUF_SIZE + \
					 SPRD_COMPR_AREA_LINKLIST_SIZE)

काष्ठा sprd_compr_dma अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	dma_addr_t phys;
	व्योम *virt;
	पूर्णांक trans_len;
पूर्ण;

/*
 * The Spपढ़ोtrum Audio compress offload mode will use 2-stage DMA transfer to
 * save घातer. That means we can request 2 dma channels, one क्रम source channel,
 * and another one क्रम destination channel. Once the source channel's transaction
 * is करोne, it will trigger the destination channel's transaction स्वतःmatically
 * by hardware संकेत.
 *
 * For 2-stage DMA transfer, we can allocate 2 buffers: IRAM buffer (always
 * घातer-on) and DDR buffer. The source channel will transfer data from IRAM
 * buffer to the DSP fअगरo to decoding/encoding, once IRAM buffer is empty by
 * transferring करोne, the destination channel will start to transfer data from
 * DDR buffer to IRAM buffer.
 *
 * Since the DSP fअगरo is only 512B, IRAM buffer is allocated by 32K, and DDR
 * buffer is larger to 2M. That means only the IRAM 32k data is transferred
 * करोne, we can wake up the AP प्रणाली to transfer data from DDR to IRAM, and
 * other समय the AP प्रणाली can be suspended to save घातer.
 */
काष्ठा sprd_compr_stream अणु
	काष्ठा snd_compr_stream *cstream;
	काष्ठा sprd_compr_ops *compr_ops;
	काष्ठा sprd_compr_dma dma[SPRD_COMPR_DMA_CHANS];

	/* DMA engine channel number */
	पूर्णांक num_channels;

	/* Stage 0 IRAM buffer */
	काष्ठा snd_dma_buffer iram_buffer;
	/* Stage 1 DDR buffer */
	काष्ठा snd_dma_buffer compr_buffer;

	/* DSP play inक्रमmation IRAM buffer */
	dma_addr_t info_phys;
	व्योम *info_area;
	पूर्णांक info_size;

	/* Data size copied to IRAM buffer */
	पूर्णांक copied_total;
	/* Total received data size from userspace */
	पूर्णांक received_total;
	/* Stage 0 IRAM buffer received data size */
	पूर्णांक received_stage0;
	/* Stage 1 DDR buffer received data size */
	पूर्णांक received_stage1;
	/* Stage 1 DDR buffer poपूर्णांकer */
	पूर्णांक stage1_poपूर्णांकer;
पूर्ण;

अटल पूर्णांक sprd_platक्रमm_compr_trigger(काष्ठा snd_soc_component *component,
				       काष्ठा snd_compr_stream *cstream,
				       पूर्णांक cmd);

अटल व्योम sprd_platक्रमm_compr_drain_notअगरy(व्योम *arg)
अणु
	काष्ठा snd_compr_stream *cstream = arg;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;

	स_रखो(stream->info_area, 0, माप(काष्ठा sprd_compr_playinfo));

	snd_compr_drain_notअगरy(cstream);
पूर्ण

अटल व्योम sprd_platक्रमm_compr_dma_complete(व्योम *data)
अणु
	काष्ठा snd_compr_stream *cstream = data;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा sprd_compr_dma *dma = &stream->dma[1];

	/* Update data size copied to IRAM buffer */
	stream->copied_total += dma->trans_len;
	अगर (stream->copied_total > stream->received_total)
		stream->copied_total = stream->received_total;

	snd_compr_fragment_elapsed(cstream);
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_dma_config(काष्ठा snd_soc_component *component,
					  काष्ठा snd_compr_stream *cstream,
					  काष्ठा snd_compr_params *params,
					  पूर्णांक channel)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा sprd_compr_data *data = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा sprd_pcm_dma_params *dma_params = data->dma_params;
	काष्ठा sprd_compr_dma *dma = &stream->dma[channel];
	काष्ठा dma_slave_config config = अणु पूर्ण;
	काष्ठा sprd_dma_linklist link = अणु पूर्ण;
	क्रमागत dma_transfer_direction dir;
	काष्ठा scatterlist *sg, *sgt;
	क्रमागत dma_slave_buswidth bus_width;
	पूर्णांक period, period_cnt, sg_num = 2;
	dma_addr_t src_addr, dst_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, j;

	अगर (!dma_params) अणु
		dev_err(dev, "no dma parameters setting\n");
		वापस -EINVAL;
	पूर्ण

	dma->chan = dma_request_slave_channel(dev,
					      dma_params->chan_name[channel]);
	अगर (!dma->chan) अणु
		dev_err(dev, "failed to request dma channel\n");
		वापस -ENODEV;
	पूर्ण

	sgt = sg = devm_kसुस्मृति(dev, sg_num, माप(*sg), GFP_KERNEL);
	अगर (!sg) अणु
		ret = -ENOMEM;
		जाओ sg_err;
	पूर्ण

	चयन (channel) अणु
	हाल 0:
		bus_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		period = (SPRD_COMPR_MCDT_FIFO_SIZE - SPRD_COMPR_MCDT_EMPTY_WMK) * 4;
		period_cnt = params->buffer.fragment_size / period;
		src_addr = stream->iram_buffer.addr;
		dst_addr = dma_params->dev_phys[channel];
		flags = SPRD_DMA_FLAGS(SPRD_DMA_SRC_CHN1,
				       SPRD_DMA_TRANS_DONE_TRG,
				       SPRD_DMA_FRAG_REQ,
				       SPRD_DMA_TRANS_INT);
		अवरोध;

	हाल 1:
		bus_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		period = params->buffer.fragment_size;
		period_cnt = params->buffer.fragments;
		src_addr = stream->compr_buffer.addr;
		dst_addr = stream->iram_buffer.addr;
		flags = SPRD_DMA_FLAGS(SPRD_DMA_DST_CHN1,
				       SPRD_DMA_TRANS_DONE_TRG,
				       SPRD_DMA_FRAG_REQ,
				       SPRD_DMA_TRANS_INT);
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ config_err;
	पूर्ण

	dma->trans_len = period * period_cnt;

	config.src_maxburst = period;
	config.src_addr_width = bus_width;
	config.dst_addr_width = bus_width;
	अगर (cstream->direction == SND_COMPRESS_PLAYBACK) अणु
		config.src_addr = src_addr;
		config.dst_addr = dst_addr;
		dir = DMA_MEM_TO_DEV;
	पूर्ण अन्यथा अणु
		config.src_addr = dst_addr;
		config.dst_addr = src_addr;
		dir = DMA_DEV_TO_MEM;
	पूर्ण

	sg_init_table(sgt, sg_num);
	क्रम (j = 0; j < sg_num; j++, sgt++) अणु
		sg_dma_len(sgt) = dma->trans_len;
		sg_dma_address(sgt) = dst_addr;
	पूर्ण

	/*
	 * Configure the link-list address क्रम the DMA engine link-list
	 * mode.
	 */
	link.virt_addr = (अचिन्हित दीर्घ)dma->virt;
	link.phy_addr = dma->phys;

	ret = dmaengine_slave_config(dma->chan, &config);
	अगर (ret) अणु
		dev_err(dev,
			"failed to set slave configuration: %d\n", ret);
		जाओ config_err;
	पूर्ण

	/*
	 * We configure the DMA request mode, पूर्णांकerrupt mode, channel
	 * mode and channel trigger mode by the flags.
	 */
	dma->desc = dma->chan->device->device_prep_slave_sg(dma->chan, sg,
							    sg_num, dir,
							    flags, &link);
	अगर (!dma->desc) अणु
		dev_err(dev, "failed to prepare slave sg\n");
		ret = -ENOMEM;
		जाओ config_err;
	पूर्ण

	/* Only channel 1 transfer can wake up the AP प्रणाली. */
	अगर (!params->no_wake_mode && channel == 1) अणु
		dma->desc->callback = sprd_platक्रमm_compr_dma_complete;
		dma->desc->callback_param = cstream;
	पूर्ण

	devm_kमुक्त(dev, sg);

	वापस 0;

config_err:
	devm_kमुक्त(dev, sg);
sg_err:
	dma_release_channel(dma->chan);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_set_params(काष्ठा snd_soc_component *component,
					  काष्ठा snd_compr_stream *cstream,
					  काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा sprd_compr_params compr_params = अणु पूर्ण;
	पूर्णांक ret;

	/*
	 * Configure the DMA engine 2-stage transfer mode. Channel 1 set as the
	 * destination channel, and channel 0 set as the source channel, that
	 * means once the source channel's transaction is करोne, it will trigger
	 * the destination channel's transaction स्वतःmatically.
	 */
	ret = sprd_platक्रमm_compr_dma_config(component, cstream, params, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to config stage 1 DMA: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = sprd_platक्रमm_compr_dma_config(component, cstream, params, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to config stage 0 DMA: %d\n", ret);
		जाओ config_err;
	पूर्ण

	compr_params.direction = cstream->direction;
	compr_params.sample_rate = params->codec.sample_rate;
	compr_params.channels = stream->num_channels;
	compr_params.info_phys = stream->info_phys;
	compr_params.info_size = stream->info_size;
	compr_params.rate = params->codec.bit_rate;
	compr_params.क्रमmat = params->codec.id;

	ret = stream->compr_ops->set_params(cstream->direction, &compr_params);
	अगर (ret) अणु
		dev_err(dev, "failed to set parameters: %d\n", ret);
		जाओ params_err;
	पूर्ण

	वापस 0;

params_err:
	dma_release_channel(stream->dma[0].chan);
config_err:
	dma_release_channel(stream->dma[1].chan);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_खोलो(काष्ठा snd_soc_component *component,
				    काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा sprd_compr_data *data = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा sprd_compr_stream *stream;
	काष्ठा sprd_compr_callback cb;
	पूर्णांक stream_id = cstream->direction, ret;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	stream = devm_kzalloc(dev, माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	stream->cstream = cstream;
	stream->num_channels = 2;
	stream->compr_ops = data->ops;

	/*
	 * Allocate the stage 0 IRAM buffer size, including the DMA 0
	 * link-list size and play inक्रमmation of DSP address size.
	 */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV_IRAM, dev,
				  SPRD_COMPR_IRAM_SIZE, &stream->iram_buffer);
	अगर (ret < 0)
		जाओ err_iram;

	/* Use to save link-list configuration क्रम DMA 0. */
	stream->dma[0].virt = stream->iram_buffer.area + SPRD_COMPR_IRAM_SIZE;
	stream->dma[0].phys = stream->iram_buffer.addr + SPRD_COMPR_IRAM_SIZE;

	/* Use to update the current data offset of DSP. */
	stream->info_phys = stream->iram_buffer.addr + SPRD_COMPR_IRAM_SIZE +
		SPRD_COMPR_IRAM_LINKLIST_SIZE;
	stream->info_area = stream->iram_buffer.area + SPRD_COMPR_IRAM_SIZE +
		SPRD_COMPR_IRAM_LINKLIST_SIZE;
	stream->info_size = SPRD_COMPR_IRAM_INFO_SIZE;

	/*
	 * Allocate the stage 1 DDR buffer size, including the DMA 1 link-list
	 * size.
	 */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, dev,
				  SPRD_COMPR_AREA_SIZE, &stream->compr_buffer);
	अगर (ret < 0)
		जाओ err_compr;

	/* Use to save link-list configuration क्रम DMA 1. */
	stream->dma[1].virt = stream->compr_buffer.area + SPRD_COMPR_AREA_SIZE;
	stream->dma[1].phys = stream->compr_buffer.addr + SPRD_COMPR_AREA_SIZE;

	cb.drain_notअगरy = sprd_platक्रमm_compr_drain_notअगरy;
	cb.drain_data = cstream;
	ret = stream->compr_ops->खोलो(stream_id, &cb);
	अगर (ret) अणु
		dev_err(dev, "failed to open compress platform: %d\n", ret);
		जाओ err_खोलो;
	पूर्ण

	runसमय->निजी_data = stream;
	वापस 0;

err_खोलो:
	snd_dma_मुक्त_pages(&stream->compr_buffer);
err_compr:
	snd_dma_मुक्त_pages(&stream->iram_buffer);
err_iram:
	devm_kमुक्त(dev, stream);

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_मुक्त(काष्ठा snd_soc_component *component,
				    काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	पूर्णांक stream_id = cstream->direction, i;

	क्रम (i = 0; i < stream->num_channels; i++) अणु
		काष्ठा sprd_compr_dma *dma = &stream->dma[i];

		अगर (dma->chan) अणु
			dma_release_channel(dma->chan);
			dma->chan = शून्य;
		पूर्ण
	पूर्ण

	snd_dma_मुक्त_pages(&stream->compr_buffer);
	snd_dma_मुक्त_pages(&stream->iram_buffer);

	stream->compr_ops->बंद(stream_id);

	devm_kमुक्त(dev, stream);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_trigger(काष्ठा snd_soc_component *component,
				       काष्ठा snd_compr_stream *cstream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	पूर्णांक channels = stream->num_channels, ret = 0, i;
	पूर्णांक stream_id = cstream->direction;

	अगर (cstream->direction != SND_COMPRESS_PLAYBACK) अणु
		dev_err(dev, "unsupported compress direction\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		क्रम (i = channels - 1; i >= 0; i--) अणु
			काष्ठा sprd_compr_dma *dma = &stream->dma[i];

			अगर (!dma->desc)
				जारी;

			dma->cookie = dmaengine_submit(dma->desc);
			ret = dma_submit_error(dma->cookie);
			अगर (ret) अणु
				dev_err(dev, "failed to submit request: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

		क्रम (i = channels - 1; i >= 0; i--) अणु
			काष्ठा sprd_compr_dma *dma = &stream->dma[i];

			अगर (dma->chan)
				dma_async_issue_pending(dma->chan);
		पूर्ण

		ret = stream->compr_ops->start(stream_id);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		क्रम (i = channels - 1; i >= 0; i--) अणु
			काष्ठा sprd_compr_dma *dma = &stream->dma[i];

			अगर (dma->chan)
				dmaengine_terminate_async(dma->chan);
		पूर्ण

		stream->copied_total = 0;
		stream->stage1_poपूर्णांकer  = 0;
		stream->received_total = 0;
		stream->received_stage0 = 0;
		stream->received_stage1 = 0;

		ret = stream->compr_ops->stop(stream_id);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		क्रम (i = channels - 1; i >= 0; i--) अणु
			काष्ठा sprd_compr_dma *dma = &stream->dma[i];

			अगर (dma->chan)
				dmaengine_छोड़ो(dma->chan);
		पूर्ण

		ret = stream->compr_ops->छोड़ो(stream_id);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		क्रम (i = channels - 1; i >= 0; i--) अणु
			काष्ठा sprd_compr_dma *dma = &stream->dma[i];

			अगर (dma->chan)
				dmaengine_resume(dma->chan);
		पूर्ण

		ret = stream->compr_ops->छोड़ो_release(stream_id);
		अवरोध;

	हाल SND_COMPR_TRIGGER_PARTIAL_DRAIN:
	हाल SND_COMPR_TRIGGER_DRAIN:
		ret = stream->compr_ops->drain(stream->received_total);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
				       काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	काष्ठा sprd_compr_playinfo *info =
		(काष्ठा sprd_compr_playinfo *)stream->info_area;

	tstamp->copied_total = stream->copied_total;
	tstamp->pcm_io_frames = info->current_data_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_copy(काष्ठा snd_soc_component *component,
				    काष्ठा snd_compr_stream *cstream,
				    अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sprd_compr_stream *stream = runसमय->निजी_data;
	पूर्णांक avail_bytes, data_count = count;
	व्योम *dst;

	/*
	 * We usually set fragment size as 32K, and the stage 0 IRAM buffer
	 * size is 32K too. So अगर now the received data size of the stage 0
	 * IRAM buffer is less than 32K, that means we have some available
	 * spaces क्रम the stage 0 IRAM buffer.
	 */
	अगर (stream->received_stage0 < runसमय->fragment_size) अणु
		avail_bytes = runसमय->fragment_size - stream->received_stage0;
		dst = stream->iram_buffer.area + stream->received_stage0;

		अगर (avail_bytes >= data_count) अणु
			/*
			 * Copy data to the stage 0 IRAM buffer directly अगर
			 * spaces are enough.
			 */
			अगर (copy_from_user(dst, buf, data_count))
				वापस -EFAULT;

			stream->received_stage0 += data_count;
			stream->copied_total += data_count;
			जाओ copy_करोne;
		पूर्ण अन्यथा अणु
			/*
			 * If the data count is larger than the available spaces
			 * of the stage 0 IRAM buffer, we should copy one
			 * partial data to the stage 0 IRAM buffer, and copy
			 * the left to the stage 1 DDR buffer.
			 */
			अगर (copy_from_user(dst, buf, avail_bytes))
				वापस -EFAULT;

			data_count -= avail_bytes;
			stream->received_stage0 += avail_bytes;
			stream->copied_total += avail_bytes;
			buf += avail_bytes;
		पूर्ण
	पूर्ण

	/*
	 * Copy data to the stage 1 DDR buffer अगर no spaces क्रम the stage 0 IRAM
	 * buffer.
	 */
	dst = stream->compr_buffer.area + stream->stage1_poपूर्णांकer;
	अगर (data_count < stream->compr_buffer.bytes - stream->stage1_poपूर्णांकer) अणु
		अगर (copy_from_user(dst, buf, data_count))
			वापस -EFAULT;

		stream->stage1_poपूर्णांकer += data_count;
	पूर्ण अन्यथा अणु
		avail_bytes = stream->compr_buffer.bytes - stream->stage1_poपूर्णांकer;

		अगर (copy_from_user(dst, buf, avail_bytes))
			वापस -EFAULT;

		अगर (copy_from_user(stream->compr_buffer.area, buf + avail_bytes,
				   data_count - avail_bytes))
			वापस -EFAULT;

		stream->stage1_poपूर्णांकer = data_count - avail_bytes;
	पूर्ण

	stream->received_stage1 += data_count;

copy_करोne:
	/* Update the copied data size. */
	stream->received_total += count;
	वापस count;
पूर्ण

अटल पूर्णांक sprd_platक्रमm_compr_get_caps(काष्ठा snd_soc_component *component,
					काष्ठा snd_compr_stream *cstream,
					काष्ठा snd_compr_caps *caps)
अणु
	caps->direction = cstream->direction;
	caps->min_fragment_size = SPRD_COMPR_MIN_FRAGMENT_SIZE;
	caps->max_fragment_size = SPRD_COMPR_MAX_FRAGMENT_SIZE;
	caps->min_fragments = SPRD_COMPR_MIN_NUM_FRAGMENTS;
	caps->max_fragments = SPRD_COMPR_MAX_NUM_FRAGMENTS;
	caps->num_codecs = 2;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_AAC;

	वापस 0;
पूर्ण

अटल पूर्णांक
sprd_platक्रमm_compr_get_codec_caps(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_codec_caps *codec)
अणु
	चयन (codec->codec) अणु
	हाल SND_AUDIOCODEC_MP3:
		codec->num_descriptors = 2;
		codec->descriptor[0].max_ch = 2;
		codec->descriptor[0].bit_rate[0] = 320;
		codec->descriptor[0].bit_rate[1] = 128;
		codec->descriptor[0].num_bitrates = 2;
		codec->descriptor[0].profiles = 0;
		codec->descriptor[0].modes = SND_AUDIOCHANMODE_MP3_STEREO;
		codec->descriptor[0].क्रमmats = 0;
		अवरोध;

	हाल SND_AUDIOCODEC_AAC:
		codec->num_descriptors = 2;
		codec->descriptor[1].max_ch = 2;
		codec->descriptor[1].bit_rate[0] = 320;
		codec->descriptor[1].bit_rate[1] = 128;
		codec->descriptor[1].num_bitrates = 2;
		codec->descriptor[1].profiles = 0;
		codec->descriptor[1].modes = 0;
		codec->descriptor[1].क्रमmats = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_compress_ops sprd_platक्रमm_compress_ops = अणु
	.खोलो = sprd_platक्रमm_compr_खोलो,
	.मुक्त = sprd_platक्रमm_compr_मुक्त,
	.set_params = sprd_platक्रमm_compr_set_params,
	.trigger = sprd_platक्रमm_compr_trigger,
	.poपूर्णांकer = sprd_platक्रमm_compr_poपूर्णांकer,
	.copy = sprd_platक्रमm_compr_copy,
	.get_caps = sprd_platक्रमm_compr_get_caps,
	.get_codec_caps = sprd_platक्रमm_compr_get_codec_caps,
पूर्ण;

MODULE_DESCRIPTION("Spreadtrum ASoC Compress Platform Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:compress-platform");
