<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale ASRC ALSA SoC Platक्रमm (DMA) driver
//
// Copyright (C) 2014 Freescale Semiconductor, Inc.
//
// Author: Nicolin Chen <nicoleotsuka@gmail.com>

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_asrc_common.h"

#घोषणा FSL_ASRC_DMABUF_SIZE	(256 * 1024)

अटल काष्ठा snd_pcm_hardware snd_imx_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID,
	.buffer_bytes_max = FSL_ASRC_DMABUF_SIZE,
	.period_bytes_min = 128,
	.period_bytes_max = 65535, /* Limited by SDMA engine */
	.periods_min = 2,
	.periods_max = 255,
	.fअगरo_size = 0,
पूर्ण;

अटल bool filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	अगर (!imx_dma_is_general_purpose(chan))
		वापस false;

	chan->निजी = param;

	वापस true;
पूर्ण

अटल व्योम fsl_asrc_dma_complete(व्योम *arg)
अणु
	काष्ठा snd_pcm_substream *substream = arg;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;

	pair->pos += snd_pcm_lib_period_bytes(substream);
	अगर (pair->pos >= snd_pcm_lib_buffer_bytes(substream))
		pair->pos = 0;

	snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक fsl_asrc_dma_prepare_and_submit(काष्ठा snd_pcm_substream *substream,
					   काष्ठा snd_soc_component *component)
अणु
	u8 dir = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? OUT : IN;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	अचिन्हित दीर्घ flags = DMA_CTRL_ACK;

	/* Prepare and submit Front-End DMA channel */
	अगर (!substream->runसमय->no_period_wakeup)
		flags |= DMA_PREP_INTERRUPT;

	pair->pos = 0;
	pair->desc[!dir] = dmaengine_prep_dma_cyclic(
			pair->dma_chan[!dir], runसमय->dma_addr,
			snd_pcm_lib_buffer_bytes(substream),
			snd_pcm_lib_period_bytes(substream),
			dir == OUT ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM, flags);
	अगर (!pair->desc[!dir]) अणु
		dev_err(dev, "failed to prepare slave DMA for Front-End\n");
		वापस -ENOMEM;
	पूर्ण

	pair->desc[!dir]->callback = fsl_asrc_dma_complete;
	pair->desc[!dir]->callback_param = substream;

	dmaengine_submit(pair->desc[!dir]);

	/* Prepare and submit Back-End DMA channel */
	pair->desc[dir] = dmaengine_prep_dma_cyclic(
			pair->dma_chan[dir], 0xffff, 64, 64, DMA_DEV_TO_DEV, 0);
	अगर (!pair->desc[dir]) अणु
		dev_err(dev, "failed to prepare slave DMA for Back-End\n");
		वापस -ENOMEM;
	पूर्ण

	dmaengine_submit(pair->desc[dir]);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dma_trigger(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = fsl_asrc_dma_prepare_and_submit(substream, component);
		अगर (ret)
			वापस ret;
		dma_async_issue_pending(pair->dma_chan[IN]);
		dma_async_issue_pending(pair->dma_chan[OUT]);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dmaengine_terminate_all(pair->dma_chan[OUT]);
		dmaengine_terminate_all(pair->dma_chan[IN]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dma_hw_params(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	क्रमागत dma_slave_buswidth buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_dmaengine_dai_dma_data *dma_params_fe = शून्य;
	काष्ठा snd_dmaengine_dai_dma_data *dma_params_be = शून्य;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	काष्ठा dma_chan *पंचांगp_chan = शून्य, *be_chan = शून्य;
	काष्ठा snd_soc_component *component_be = शून्य;
	काष्ठा fsl_asrc *asrc = pair->asrc;
	काष्ठा dma_slave_config config_fe, config_be;
	क्रमागत asrc_pair_index index = pair->index;
	काष्ठा device *dev = component->dev;
	काष्ठा device_node *of_dma_node;
	पूर्णांक stream = substream->stream;
	काष्ठा imx_dma_data *पंचांगp_data;
	काष्ठा snd_soc_dpcm *dpcm;
	काष्ठा device *dev_be;
	u8 dir = tx ? OUT : IN;
	dma_cap_mask_t mask;
	पूर्णांक ret, width;

	/* Fetch the Back-End dma_data from DPCM */
	क्रम_each_dpcm_be(rtd, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_pcm_substream *substream_be;
		काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(be, 0);

		अगर (dpcm->fe != rtd)
			जारी;

		substream_be = snd_soc_dpcm_get_substream(be, stream);
		dma_params_be = snd_soc_dai_get_dma_data(dai, substream_be);
		dev_be = dai->dev;
		अवरोध;
	पूर्ण

	अगर (!dma_params_be) अणु
		dev_err(dev, "failed to get the substream of Back-End\n");
		वापस -EINVAL;
	पूर्ण

	/* Override dma_data of the Front-End and config its dmaengine */
	dma_params_fe = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	dma_params_fe->addr = asrc->paddr + asrc->get_fअगरo_addr(!dir, index);
	dma_params_fe->maxburst = dma_params_be->maxburst;

	pair->dma_chan[!dir] = asrc->get_dma_channel(pair, !dir);
	अगर (!pair->dma_chan[!dir]) अणु
		dev_err(dev, "failed to request DMA channel\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&config_fe, 0, माप(config_fe));
	ret = snd_dmaengine_pcm_prepare_slave_config(substream, params, &config_fe);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare DMA config for Front-End\n");
		वापस ret;
	पूर्ण

	ret = dmaengine_slave_config(pair->dma_chan[!dir], &config_fe);
	अगर (ret) अणु
		dev_err(dev, "failed to config DMA channel for Front-End\n");
		वापस ret;
	पूर्ण

	/* Request and config DMA channel क्रम Back-End */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_CYCLIC, mask);

	/*
	 * The Back-End device might have alपढ़ोy requested a DMA channel,
	 * so try to reuse it first, and then request a new one upon शून्य.
	 */
	component_be = snd_soc_lookup_component_nolocked(dev_be, SND_DMAENGINE_PCM_DRV_NAME);
	अगर (component_be) अणु
		be_chan = soc_component_to_pcm(component_be)->chan[substream->stream];
		पंचांगp_chan = be_chan;
	पूर्ण
	अगर (!पंचांगp_chan)
		पंचांगp_chan = dma_request_slave_channel(dev_be, tx ? "tx" : "rx");

	/*
	 * An EDMA DEV_TO_DEV channel is fixed and bound with DMA event of each
	 * peripheral, unlike SDMA channel that is allocated dynamically. So no
	 * need to configure dma_request and dma_request2, but get dma_chan of
	 * Back-End device directly via dma_request_slave_channel.
	 */
	अगर (!asrc->use_edma) अणु
		/* Get DMA request of Back-End */
		पंचांगp_data = पंचांगp_chan->निजी;
		pair->dma_data.dma_request = पंचांगp_data->dma_request;
		अगर (!be_chan)
			dma_release_channel(पंचांगp_chan);

		/* Get DMA request of Front-End */
		पंचांगp_chan = asrc->get_dma_channel(pair, dir);
		पंचांगp_data = पंचांगp_chan->निजी;
		pair->dma_data.dma_request2 = पंचांगp_data->dma_request;
		pair->dma_data.peripheral_type = पंचांगp_data->peripheral_type;
		pair->dma_data.priority = पंचांगp_data->priority;
		dma_release_channel(पंचांगp_chan);

		of_dma_node = pair->dma_chan[!dir]->device->dev->of_node;
		pair->dma_chan[dir] =
			__dma_request_channel(&mask, filter, &pair->dma_data,
					      of_dma_node);
		pair->req_dma_chan = true;
	पूर्ण अन्यथा अणु
		pair->dma_chan[dir] = पंचांगp_chan;
		/* Do not flag to release अगर we are reusing the Back-End one */
		pair->req_dma_chan = !be_chan;
	पूर्ण

	अगर (!pair->dma_chan[dir]) अणु
		dev_err(dev, "failed to request DMA channel for Back-End\n");
		वापस -EINVAL;
	पूर्ण

	width = snd_pcm_क्रमmat_physical_width(asrc->asrc_क्रमmat);
	अगर (width < 8 || width > 64)
		वापस -EINVAL;
	अन्यथा अगर (width == 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	अन्यथा अगर (width == 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा अगर (width == 24)
		buswidth = DMA_SLAVE_BUSWIDTH_3_BYTES;
	अन्यथा अगर (width <= 32)
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
	अन्यथा
		buswidth = DMA_SLAVE_BUSWIDTH_8_BYTES;

	config_be.direction = DMA_DEV_TO_DEV;
	config_be.src_addr_width = buswidth;
	config_be.src_maxburst = dma_params_be->maxburst;
	config_be.dst_addr_width = buswidth;
	config_be.dst_maxburst = dma_params_be->maxburst;

	अगर (tx) अणु
		config_be.src_addr = asrc->paddr + asrc->get_fअगरo_addr(OUT, index);
		config_be.dst_addr = dma_params_be->addr;
	पूर्ण अन्यथा अणु
		config_be.dst_addr = asrc->paddr + asrc->get_fअगरo_addr(IN, index);
		config_be.src_addr = dma_params_be->addr;
	पूर्ण

	ret = dmaengine_slave_config(pair->dma_chan[dir], &config_be);
	अगर (ret) अणु
		dev_err(dev, "failed to config DMA channel for Back-End\n");
		अगर (pair->req_dma_chan)
			dma_release_channel(pair->dma_chan[dir]);
		वापस ret;
	पूर्ण

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dma_hw_मुक्त(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream)
अणु
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	u8 dir = tx ? OUT : IN;

	snd_pcm_set_runसमय_buffer(substream, शून्य);

	अगर (pair->dma_chan[!dir])
		dma_release_channel(pair->dma_chan[!dir]);

	/* release dev_to_dev chan अगर we aren't reusing the Back-End one */
	अगर (pair->dma_chan[dir] && pair->req_dma_chan)
		dma_release_channel(pair->dma_chan[dir]);

	pair->dma_chan[!dir] = शून्य;
	pair->dma_chan[dir] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dma_startup(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream)
अणु
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	काष्ठा device *dev = component->dev;
	काष्ठा fsl_asrc *asrc = dev_get_drvdata(dev);
	काष्ठा fsl_asrc_pair *pair;
	काष्ठा dma_chan *पंचांगp_chan = शून्य;
	u8 dir = tx ? OUT : IN;
	bool release_pair = true;
	पूर्णांक ret = 0;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set pcm hw params periods\n");
		वापस ret;
	पूर्ण

	pair = kzalloc(माप(*pair) + asrc->pair_priv_size, GFP_KERNEL);
	अगर (!pair)
		वापस -ENOMEM;

	pair->asrc = asrc;
	pair->निजी = (व्योम *)pair + माप(काष्ठा fsl_asrc_pair);

	runसमय->निजी_data = pair;

	/* Request a dummy pair, which will be released later.
	 * Request pair function needs channel num as input, क्रम this
	 * dummy pair, we just request "1" channel temporarily.
	 */
	ret = asrc->request_pair(1, pair);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request asrc pair\n");
		जाओ req_pair_err;
	पूर्ण

	/* Request a dummy dma channel, which will be released later. */
	पंचांगp_chan = asrc->get_dma_channel(pair, dir);
	अगर (!पंचांगp_chan) अणु
		dev_err(dev, "failed to get dma channel\n");
		ret = -EINVAL;
		जाओ dma_chan_err;
	पूर्ण

	dma_data = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

	/* Refine the snd_imx_hardware according to caps of DMA. */
	ret = snd_dmaengine_pcm_refine_runसमय_hwparams(substream,
							dma_data,
							&snd_imx_hardware,
							पंचांगp_chan);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to refine runtime hwparams\n");
		जाओ out;
	पूर्ण

	release_pair = false;
	snd_soc_set_runसमय_hwparams(substream, &snd_imx_hardware);

out:
	dma_release_channel(पंचांगp_chan);

dma_chan_err:
	asrc->release_pair(pair);

req_pair_err:
	अगर (release_pair)
		kमुक्त(pair);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_asrc_dma_shutकरोwn(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	काष्ठा fsl_asrc *asrc;

	अगर (!pair)
		वापस 0;

	asrc = pair->asrc;

	अगर (asrc->pair[pair->index] == pair)
		asrc->pair[pair->index] = शून्य;

	kमुक्त(pair);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
fsl_asrc_dma_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;

	वापस bytes_to_frames(substream->runसमय, pair->pos);
पूर्ण

अटल पूर्णांक fsl_asrc_dma_pcm_new(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret, i;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(card->dev, "failed to set DMA mask\n");
		वापस ret;
	पूर्ण

	क्रम_each_pcm_streams(i) अणु
		substream = pcm->streams[i].substream;
		अगर (!substream)
			जारी;

		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, pcm->card->dev,
				FSL_ASRC_DMABUF_SIZE, &substream->dma_buffer);
		अगर (ret) अणु
			dev_err(card->dev, "failed to allocate DMA buffer\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	अगर (--i == 0 && pcm->streams[i].substream)
		snd_dma_मुक्त_pages(&pcm->streams[i].substream->dma_buffer);

	वापस ret;
पूर्ण

अटल व्योम fsl_asrc_dma_pcm_मुक्त(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक i;

	क्रम_each_pcm_streams(i) अणु
		substream = pcm->streams[i].substream;
		अगर (!substream)
			जारी;

		snd_dma_मुक्त_pages(&substream->dma_buffer);
		substream->dma_buffer.area = शून्य;
		substream->dma_buffer.addr = 0;
	पूर्ण
पूर्ण

काष्ठा snd_soc_component_driver fsl_asrc_component = अणु
	.name		= DRV_NAME,
	.hw_params	= fsl_asrc_dma_hw_params,
	.hw_मुक्त	= fsl_asrc_dma_hw_मुक्त,
	.trigger	= fsl_asrc_dma_trigger,
	.खोलो		= fsl_asrc_dma_startup,
	.बंद		= fsl_asrc_dma_shutकरोwn,
	.poपूर्णांकer	= fsl_asrc_dma_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= fsl_asrc_dma_pcm_new,
	.pcm_deकाष्ठा	= fsl_asrc_dma_pcm_मुक्त,
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_asrc_component);
