<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2012, Analog Devices Inc.
 *	Author: Lars-Peter Clausen <lars@metafoo.de>
 *
 *  Based on:
 *	imx-pcm-dma-mx2.c, Copyright 2009 Sascha Hauer <s.hauer@pengutronix.de>
 *	mxs-pcm.c, Copyright (C) 2011 Freescale Semiconductor, Inc.
 *	ep93xx-pcm.c, Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 *		      Copyright (C) 2006 Applied Data Systems
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <sound/dmaengine_pcm.h>

काष्ठा dmaengine_pcm_runसमय_data अणु
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;

	अचिन्हित पूर्णांक pos;
पूर्ण;

अटल अंतरभूत काष्ठा dmaengine_pcm_runसमय_data *substream_to_prtd(
	स्थिर काष्ठा snd_pcm_substream *substream)
अणु
	वापस substream->runसमय->निजी_data;
पूर्ण

काष्ठा dma_chan *snd_dmaengine_pcm_get_chan(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);

	वापस prtd->dma_chan;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_get_chan);

/**
 * snd_hwparams_to_dma_slave_config - Convert hw_params to dma_slave_config
 * @substream: PCM substream
 * @params: hw_params
 * @slave_config: DMA slave config
 *
 * This function can be used to initialize a dma_slave_config from a substream
 * and hw_params in a dmaengine based PCM driver implementation.
 */
पूर्णांक snd_hwparams_to_dma_slave_config(स्थिर काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_pcm_hw_params *params,
	काष्ठा dma_slave_config *slave_config)
अणु
	क्रमागत dma_slave_buswidth buswidth;
	पूर्णांक bits;

	bits = params_physical_width(params);
	अगर (bits < 8 || bits > 64)
		वापस -EINVAL;
	अन्यथा अगर (bits == 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	अन्यथा अगर (bits == 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा अगर (bits == 24)
		buswidth = DMA_SLAVE_BUSWIDTH_3_BYTES;
	अन्यथा अगर (bits <= 32)
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
	अन्यथा
		buswidth = DMA_SLAVE_BUSWIDTH_8_BYTES;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		slave_config->direction = DMA_MEM_TO_DEV;
		slave_config->dst_addr_width = buswidth;
	पूर्ण अन्यथा अणु
		slave_config->direction = DMA_DEV_TO_MEM;
		slave_config->src_addr_width = buswidth;
	पूर्ण

	slave_config->device_fc = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hwparams_to_dma_slave_config);

/**
 * snd_dmaengine_pcm_set_config_from_dai_data() - Initializes a dma slave config
 *  using DAI DMA data.
 * @substream: PCM substream
 * @dma_data: DAI DMA data
 * @slave_config: DMA slave configuration
 *
 * Initializes the अणुdst,srcपूर्ण_addr, अणुdst,srcपूर्ण_maxburst, अणुdst,srcपूर्ण_addr_width and
 * slave_id fields of the DMA slave config from the same fields of the DAI DMA
 * data काष्ठा. The src and dst fields will be initialized depending on the
 * direction of the substream. If the substream is a playback stream the dst
 * fields will be initialized, अगर it is a capture stream the src fields will be
 * initialized. The अणुdst,srcपूर्ण_addr_width field will only be initialized अगर the
 * SND_DMAENGINE_PCM_DAI_FLAG_PACK flag is set or अगर the addr_width field of
 * the DAI DMA data काष्ठा is not equal to DMA_SLAVE_BUSWIDTH_UNDEFINED. If
 * both conditions are met the latter takes priority.
 */
व्योम snd_dmaengine_pcm_set_config_from_dai_data(
	स्थिर काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_dmaengine_dai_dma_data *dma_data,
	काष्ठा dma_slave_config *slave_config)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		slave_config->dst_addr = dma_data->addr;
		slave_config->dst_maxburst = dma_data->maxburst;
		अगर (dma_data->flags & SND_DMAENGINE_PCM_DAI_FLAG_PACK)
			slave_config->dst_addr_width =
				DMA_SLAVE_BUSWIDTH_UNDEFINED;
		अगर (dma_data->addr_width != DMA_SLAVE_BUSWIDTH_UNDEFINED)
			slave_config->dst_addr_width = dma_data->addr_width;
	पूर्ण अन्यथा अणु
		slave_config->src_addr = dma_data->addr;
		slave_config->src_maxburst = dma_data->maxburst;
		अगर (dma_data->flags & SND_DMAENGINE_PCM_DAI_FLAG_PACK)
			slave_config->src_addr_width =
				DMA_SLAVE_BUSWIDTH_UNDEFINED;
		अगर (dma_data->addr_width != DMA_SLAVE_BUSWIDTH_UNDEFINED)
			slave_config->src_addr_width = dma_data->addr_width;
	पूर्ण

	slave_config->slave_id = dma_data->slave_id;
	slave_config->peripheral_config = dma_data->peripheral_config;
	slave_config->peripheral_size = dma_data->peripheral_size;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_set_config_from_dai_data);

अटल व्योम dmaengine_pcm_dma_complete(व्योम *arg)
अणु
	काष्ठा snd_pcm_substream *substream = arg;
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);

	prtd->pos += snd_pcm_lib_period_bytes(substream);
	अगर (prtd->pos >= snd_pcm_lib_buffer_bytes(substream))
		prtd->pos = 0;

	snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक dmaengine_pcm_prepare_and_submit(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);
	काष्ठा dma_chan *chan = prtd->dma_chan;
	काष्ठा dma_async_tx_descriptor *desc;
	क्रमागत dma_transfer_direction direction;
	अचिन्हित दीर्घ flags = DMA_CTRL_ACK;

	direction = snd_pcm_substream_to_dma_direction(substream);

	अगर (!substream->runसमय->no_period_wakeup)
		flags |= DMA_PREP_INTERRUPT;

	prtd->pos = 0;
	desc = dmaengine_prep_dma_cyclic(chan,
		substream->runसमय->dma_addr,
		snd_pcm_lib_buffer_bytes(substream),
		snd_pcm_lib_period_bytes(substream), direction, flags);

	अगर (!desc)
		वापस -ENOMEM;

	desc->callback = dmaengine_pcm_dma_complete;
	desc->callback_param = substream;
	prtd->cookie = dmaengine_submit(desc);

	वापस 0;
पूर्ण

/**
 * snd_dmaengine_pcm_trigger - dmaengine based PCM trigger implementation
 * @substream: PCM substream
 * @cmd: Trigger command
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * This function can be used as the PCM trigger callback क्रम dmaengine based PCM
 * driver implementations.
 */
पूर्णांक snd_dmaengine_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		ret = dmaengine_pcm_prepare_and_submit(substream);
		अगर (ret)
			वापस ret;
		dma_async_issue_pending(prtd->dma_chan);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dmaengine_resume(prtd->dma_chan);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (runसमय->info & SNDRV_PCM_INFO_PAUSE)
			dmaengine_छोड़ो(prtd->dma_chan);
		अन्यथा
			dmaengine_terminate_async(prtd->dma_chan);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dmaengine_छोड़ो(prtd->dma_chan);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dmaengine_terminate_async(prtd->dma_chan);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_trigger);

/**
 * snd_dmaengine_pcm_poपूर्णांकer_no_residue - dmaengine based PCM poपूर्णांकer implementation
 * @substream: PCM substream
 *
 * This function is deprecated and should not be used by new drivers, as its
 * results may be unreliable.
 */
snd_pcm_uframes_t snd_dmaengine_pcm_poपूर्णांकer_no_residue(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);
	वापस bytes_to_frames(substream->runसमय, prtd->pos);
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_poपूर्णांकer_no_residue);

/**
 * snd_dmaengine_pcm_poपूर्णांकer - dmaengine based PCM poपूर्णांकer implementation
 * @substream: PCM substream
 *
 * This function can be used as the PCM poपूर्णांकer callback क्रम dmaengine based PCM
 * driver implementations.
 */
snd_pcm_uframes_t snd_dmaengine_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित पूर्णांक pos = 0;

	status = dmaengine_tx_status(prtd->dma_chan, prtd->cookie, &state);
	अगर (status == DMA_IN_PROGRESS || status == DMA_PAUSED) अणु
		buf_size = snd_pcm_lib_buffer_bytes(substream);
		अगर (state.residue > 0 && state.residue <= buf_size)
			pos = buf_size - state.residue;

		runसमय->delay = bytes_to_frames(runसमय,
						 state.in_flight_bytes);
	पूर्ण

	वापस bytes_to_frames(runसमय, pos);
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_poपूर्णांकer);

/**
 * snd_dmaengine_pcm_request_channel - Request channel क्रम the dmaengine PCM
 * @filter_fn: Filter function used to request the DMA channel
 * @filter_data: Data passed to the DMA filter function
 *
 * Returns शून्य or the requested DMA channel.
 *
 * This function request a DMA channel क्रम usage with dmaengine PCM.
 */
काष्ठा dma_chan *snd_dmaengine_pcm_request_channel(dma_filter_fn filter_fn,
	व्योम *filter_data)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_CYCLIC, mask);

	वापस dma_request_channel(mask, filter_fn, filter_data);
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_request_channel);

/**
 * snd_dmaengine_pcm_खोलो - Open a dmaengine based PCM substream
 * @substream: PCM substream
 * @chan: DMA channel to use क्रम data transfers
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * The function should usually be called from the pcm खोलो callback. Note that
 * this function will use निजी_data field of the substream's runसमय. So it
 * is not available to your pcm driver implementation.
 */
पूर्णांक snd_dmaengine_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
	काष्ठा dma_chan *chan)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd;
	पूर्णांक ret;

	अगर (!chan)
		वापस -ENXIO;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		वापस ret;

	prtd = kzalloc(माप(*prtd), GFP_KERNEL);
	अगर (!prtd)
		वापस -ENOMEM;

	prtd->dma_chan = chan;

	substream->runसमय->निजी_data = prtd;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_खोलो);

/**
 * snd_dmaengine_pcm_खोलो_request_chan - Open a dmaengine based PCM substream and request channel
 * @substream: PCM substream
 * @filter_fn: Filter function used to request the DMA channel
 * @filter_data: Data passed to the DMA filter function
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * This function will request a DMA channel using the passed filter function and
 * data. The function should usually be called from the pcm खोलो callback. Note
 * that this function will use निजी_data field of the substream's runसमय. So
 * it is not available to your pcm driver implementation.
 */
पूर्णांक snd_dmaengine_pcm_खोलो_request_chan(काष्ठा snd_pcm_substream *substream,
	dma_filter_fn filter_fn, व्योम *filter_data)
अणु
	वापस snd_dmaengine_pcm_खोलो(substream,
		    snd_dmaengine_pcm_request_channel(filter_fn, filter_data));
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_खोलो_request_chan);

/**
 * snd_dmaengine_pcm_बंद - Close a dmaengine based PCM substream
 * @substream: PCM substream
 */
पूर्णांक snd_dmaengine_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);

	dmaengine_synchronize(prtd->dma_chan);
	kमुक्त(prtd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_बंद);

/**
 * snd_dmaengine_pcm_बंद_release_chan - Close a dmaengine based PCM
 *					  substream and release channel
 * @substream: PCM substream
 *
 * Releases the DMA channel associated with the PCM substream.
 */
पूर्णांक snd_dmaengine_pcm_बंद_release_chan(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm_runसमय_data *prtd = substream_to_prtd(substream);

	dmaengine_synchronize(prtd->dma_chan);
	dma_release_channel(prtd->dma_chan);
	kमुक्त(prtd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_बंद_release_chan);

/**
 * snd_dmaengine_pcm_refine_runसमय_hwparams - Refine runसमय hw params
 * @substream: PCM substream
 * @dma_data: DAI DMA data
 * @hw: PCM hw params
 * @chan: DMA channel to use क्रम data transfers
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * This function will query DMA capability, then refine the pcm hardware
 * parameters.
 */
पूर्णांक snd_dmaengine_pcm_refine_runसमय_hwparams(
	काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_dmaengine_dai_dma_data *dma_data,
	काष्ठा snd_pcm_hardware *hw,
	काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_slave_caps dma_caps;
	u32 addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			  BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			  BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	snd_pcm_क्रमmat_t i;
	पूर्णांक ret = 0;

	अगर (!hw || !chan || !dma_data)
		वापस -EINVAL;

	ret = dma_get_slave_caps(chan, &dma_caps);
	अगर (ret == 0) अणु
		अगर (dma_caps.cmd_छोड़ो && dma_caps.cmd_resume)
			hw->info |= SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME;
		अगर (dma_caps.residue_granularity <= DMA_RESIDUE_GRANULARITY_SEGMENT)
			hw->info |= SNDRV_PCM_INFO_BATCH;

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			addr_widths = dma_caps.dst_addr_widths;
		अन्यथा
			addr_widths = dma_caps.src_addr_widths;
	पूर्ण

	/*
	 * If SND_DMAENGINE_PCM_DAI_FLAG_PACK is set keep
	 * hw.क्रमmats set to 0, meaning no restrictions are in place.
	 * In this हाल it's the responsibility of the DAI driver to
	 * provide the supported क्रमmat inक्रमmation.
	 */
	अगर (!(dma_data->flags & SND_DMAENGINE_PCM_DAI_FLAG_PACK))
		/*
		 * Prepare क्रमmats mask क्रम valid/allowed sample types. If the
		 * dma करोes not have support क्रम the given physical word size,
		 * it needs to be masked out so user space can not use the
		 * क्रमmat which produces corrupted audio.
		 * In हाल the dma driver करोes not implement the slave_caps the
		 * शेष assumption is that it supports 1, 2 and 4 bytes
		 * widths.
		 */
		pcm_क्रम_each_क्रमmat(i) अणु
			पूर्णांक bits = snd_pcm_क्रमmat_physical_width(i);

			/*
			 * Enable only samples with DMA supported physical
			 * widths
			 */
			चयन (bits) अणु
			हाल 8:
			हाल 16:
			हाल 24:
			हाल 32:
			हाल 64:
				अगर (addr_widths & (1 << (bits / 8)))
					hw->क्रमmats |= pcm_क्रमmat_to_bits(i);
				अवरोध;
			शेष:
				/* Unsupported types */
				अवरोध;
			पूर्ण
		पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_refine_runसमय_hwparams);

MODULE_LICENSE("GPL");
