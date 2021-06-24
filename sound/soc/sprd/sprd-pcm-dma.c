<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Spपढ़ोtrum Communications Inc.

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/sprd-dma.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "sprd-pcm-dma.h"

#घोषणा SPRD_PCM_DMA_LINKLIST_SIZE	64
#घोषणा SPRD_PCM_DMA_BRUST_LEN		640

काष्ठा sprd_pcm_dma_data अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	dma_addr_t phys;
	व्योम *virt;
	पूर्णांक pre_poपूर्णांकer;
पूर्ण;

काष्ठा sprd_pcm_dma_निजी अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा sprd_pcm_dma_params *params;
	काष्ठा sprd_pcm_dma_data data[SPRD_PCM_CHANNEL_MAX];
	पूर्णांक hw_chan;
	पूर्णांक dma_addr_offset;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sprd_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	.period_bytes_min = 1,
	.period_bytes_max = 64 * 1024,
	.periods_min = 1,
	.periods_max = PAGE_SIZE / SPRD_PCM_DMA_LINKLIST_SIZE,
	.buffer_bytes_max = 64 * 1024,
पूर्ण;

अटल पूर्णांक sprd_pcm_खोलो(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = component->dev;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी;
	पूर्णांक hw_chan = SPRD_PCM_CHANNEL_MAX;
	पूर्णांक size, ret, i;

	snd_soc_set_runसमय_hwparams(substream, &sprd_pcm_hardware);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					 SPRD_PCM_DMA_BRUST_LEN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					 SPRD_PCM_DMA_BRUST_LEN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		वापस ret;

	dma_निजी = devm_kzalloc(dev, माप(*dma_निजी), GFP_KERNEL);
	अगर (!dma_निजी)
		वापस -ENOMEM;

	size = runसमय->hw.periods_max * SPRD_PCM_DMA_LINKLIST_SIZE;

	क्रम (i = 0; i < hw_chan; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		data->virt = dmam_alloc_coherent(dev, size, &data->phys,
						 GFP_KERNEL);
		अगर (!data->virt) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	dma_निजी->hw_chan = hw_chan;
	runसमय->निजी_data = dma_निजी;
	dma_निजी->substream = substream;

	वापस 0;

error:
	क्रम (i = 0; i < hw_chan; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		अगर (data->virt)
			dmam_मुक्त_coherent(dev, size, data->virt, data->phys);
	पूर्ण

	devm_kमुक्त(dev, dma_निजी);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_pcm_बंद(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	पूर्णांक size = runसमय->hw.periods_max * SPRD_PCM_DMA_LINKLIST_SIZE;
	पूर्णांक i;

	क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		dmam_मुक्त_coherent(dev, size, data->virt, data->phys);
	पूर्ण

	devm_kमुक्त(dev, dma_निजी);

	वापस 0;
पूर्ण

अटल व्योम sprd_pcm_dma_complete(व्योम *data)
अणु
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = data;
	काष्ठा snd_pcm_substream *substream = dma_निजी->substream;

	snd_pcm_period_elapsed(substream);
पूर्ण

अटल व्योम sprd_pcm_release_dma_channel(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = runसमय->निजी_data;
	पूर्णांक i;

	क्रम (i = 0; i < SPRD_PCM_CHANNEL_MAX; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		अगर (data->chan) अणु
			dma_release_channel(data->chan);
			data->chan = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_pcm_request_dma_channel(काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_substream *substream,
					पूर्णांक channels)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा device *dev = component->dev;
	काष्ठा sprd_pcm_dma_params *dma_params = dma_निजी->params;
	पूर्णांक i;

	अगर (channels > SPRD_PCM_CHANNEL_MAX) अणु
		dev_err(dev, "invalid dma channel number:%d\n", channels);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < channels; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		data->chan = dma_request_slave_channel(dev,
						       dma_params->chan_name[i]);
		अगर (!data->chan) अणु
			dev_err(dev, "failed to request dma channel:%s\n",
				dma_params->chan_name[i]);
			sprd_pcm_release_dma_channel(substream);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pcm_hw_params(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sprd_pcm_dma_params *dma_params;
	माप_प्रकार totsize = params_buffer_bytes(params);
	माप_प्रकार period = params_period_bytes(params);
	पूर्णांक channels = params_channels(params);
	पूर्णांक is_playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i, j, sg_num;

	dma_params = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dma_params) अणु
		dev_warn(component->dev, "no dma parameters setting\n");
		dma_निजी->params = शून्य;
		snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);
		runसमय->dma_bytes = totsize;
		वापस 0;
	पूर्ण

	अगर (!dma_निजी->params) अणु
		dma_निजी->params = dma_params;
		ret = sprd_pcm_request_dma_channel(component,
						   substream, channels);
		अगर (ret)
			वापस ret;
	पूर्ण

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	runसमय->dma_bytes = totsize;
	sg_num = totsize / period;
	dma_निजी->dma_addr_offset = totsize / channels;

	sg = devm_kसुस्मृति(component->dev, sg_num, माप(*sg), GFP_KERNEL);
	अगर (!sg) अणु
		ret = -ENOMEM;
		जाओ sg_err;
	पूर्ण

	क्रम (i = 0; i < channels; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];
		काष्ठा dma_chan *chan = data->chan;
		काष्ठा dma_slave_config config = अणु पूर्ण;
		काष्ठा sprd_dma_linklist link = अणु पूर्ण;
		क्रमागत dma_transfer_direction dir;
		काष्ठा scatterlist *sgt = sg;

		config.src_maxburst = dma_params->fragment_len[i];
		config.src_addr_width = dma_params->datawidth[i];
		config.dst_addr_width = dma_params->datawidth[i];
		अगर (is_playback) अणु
			config.src_addr = runसमय->dma_addr +
				i * dma_निजी->dma_addr_offset;
			config.dst_addr = dma_params->dev_phys[i];
			dir = DMA_MEM_TO_DEV;
		पूर्ण अन्यथा अणु
			config.src_addr = dma_params->dev_phys[i];
			config.dst_addr = runसमय->dma_addr +
				i * dma_निजी->dma_addr_offset;
			dir = DMA_DEV_TO_MEM;
		पूर्ण

		sg_init_table(sgt, sg_num);
		क्रम (j = 0; j < sg_num; j++, sgt++) अणु
			u32 sg_len = period / channels;

			sg_dma_len(sgt) = sg_len;
			sg_dma_address(sgt) = runसमय->dma_addr +
				i * dma_निजी->dma_addr_offset + sg_len * j;
		पूर्ण

		/*
		 * Configure the link-list address क्रम the DMA engine link-list
		 * mode.
		 */
		link.virt_addr = (अचिन्हित दीर्घ)data->virt;
		link.phy_addr = data->phys;

		ret = dmaengine_slave_config(chan, &config);
		अगर (ret) अणु
			dev_err(component->dev,
				"failed to set slave configuration: %d\n", ret);
			जाओ config_err;
		पूर्ण

		/*
		 * We configure the DMA request mode, पूर्णांकerrupt mode, channel
		 * mode and channel trigger mode by the flags.
		 */
		flags = SPRD_DMA_FLAGS(SPRD_DMA_CHN_MODE_NONE, SPRD_DMA_NO_TRG,
				       SPRD_DMA_FRAG_REQ, SPRD_DMA_TRANS_INT);
		data->desc = chan->device->device_prep_slave_sg(chan, sg,
								sg_num, dir,
								flags, &link);
		अगर (!data->desc) अणु
			dev_err(component->dev, "failed to prepare slave sg\n");
			ret = -ENOMEM;
			जाओ config_err;
		पूर्ण

		अगर (!runसमय->no_period_wakeup) अणु
			data->desc->callback = sprd_pcm_dma_complete;
			data->desc->callback_param = dma_निजी;
		पूर्ण
	पूर्ण

	devm_kमुक्त(component->dev, sg);

	वापस 0;

config_err:
	devm_kमुक्त(component->dev, sg);
sg_err:
	sprd_pcm_release_dma_channel(substream);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_set_runसमय_buffer(substream, शून्य);
	sprd_pcm_release_dma_channel(substream);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pcm_trigger(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा sprd_pcm_dma_निजी *dma_निजी =
		substream->runसमय->निजी_data;
	पूर्णांक ret = 0, i;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
			काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

			अगर (!data->desc)
				जारी;

			data->cookie = dmaengine_submit(data->desc);
			ret = dma_submit_error(data->cookie);
			अगर (ret) अणु
				dev_err(component->dev,
					"failed to submit dma request: %d\n",
					ret);
				वापस ret;
			पूर्ण

			dma_async_issue_pending(data->chan);
		पूर्ण

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
			काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

			अगर (data->chan)
				dmaengine_resume(data->chan);
		पूर्ण

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
			काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

			अगर (data->chan)
				dmaengine_terminate_async(data->chan);
		पूर्ण

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
			काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

			अगर (data->chan)
				dmaengine_छोड़ो(data->chan);
		पूर्ण

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t sprd_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sprd_pcm_dma_निजी *dma_निजी = runसमय->निजी_data;
	पूर्णांक poपूर्णांकer[SPRD_PCM_CHANNEL_MAX];
	पूर्णांक bytes_of_poपूर्णांकer = 0, sel_max = 0, i;
	snd_pcm_uframes_t x;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	क्रम (i = 0; i < dma_निजी->hw_chan; i++) अणु
		काष्ठा sprd_pcm_dma_data *data = &dma_निजी->data[i];

		अगर (!data->chan)
			जारी;

		status = dmaengine_tx_status(data->chan, data->cookie, &state);
		अगर (status == DMA_ERROR) अणु
			dev_err(component->dev,
				"failed to get dma channel %d status\n", i);
			वापस 0;
		पूर्ण

		/*
		 * We just get current transfer address from the DMA engine, so
		 * we need convert to current poपूर्णांकer.
		 */
		poपूर्णांकer[i] = state.residue - runसमय->dma_addr -
			i * dma_निजी->dma_addr_offset;

		अगर (i == 0) अणु
			bytes_of_poपूर्णांकer = poपूर्णांकer[i];
			sel_max = poपूर्णांकer[i] < data->pre_poपूर्णांकer ? 1 : 0;
		पूर्ण अन्यथा अणु
			sel_max ^= poपूर्णांकer[i] < data->pre_poपूर्णांकer ? 1 : 0;

			अगर (sel_max)
				bytes_of_poपूर्णांकer =
					max(poपूर्णांकer[i], poपूर्णांकer[i - 1]) << 1;
			अन्यथा
				bytes_of_poपूर्णांकer =
					min(poपूर्णांकer[i], poपूर्णांकer[i - 1]) << 1;
		पूर्ण

		data->pre_poपूर्णांकer = poपूर्णांकer[i];
	पूर्ण

	x = bytes_to_frames(runसमय, bytes_of_poपूर्णांकer);
	अगर (x == runसमय->buffer_size)
		x = 0;

	वापस x;
पूर्ण

अटल पूर्णांक sprd_pcm_mmap(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream,
			 काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start,
			       runसमय->dma_addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
पूर्ण

अटल पूर्णांक sprd_pcm_new(काष्ठा snd_soc_component *component,
			काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	अगर (substream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
					  sprd_pcm_hardware.buffer_bytes_max,
					  &substream->dma_buffer);
		अगर (ret) अणु
			dev_err(card->dev,
				"can't alloc playback dma buffer: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	अगर (substream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
					  sprd_pcm_hardware.buffer_bytes_max,
					  &substream->dma_buffer);
		अगर (ret) अणु
			dev_err(card->dev,
				"can't alloc capture dma buffer: %d\n", ret);
			snd_dma_मुक्त_pages(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_pcm_मुक्त(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcm->streams); i++) अणु
		substream = pcm->streams[i].substream;
		अगर (substream) अणु
			snd_dma_मुक्त_pages(&substream->dma_buffer);
			substream->dma_buffer.area = शून्य;
			substream->dma_buffer.addr = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sprd_soc_component = अणु
	.name		= DRV_NAME,
	.खोलो		= sprd_pcm_खोलो,
	.बंद		= sprd_pcm_बंद,
	.hw_params	= sprd_pcm_hw_params,
	.hw_मुक्त	= sprd_pcm_hw_मुक्त,
	.trigger	= sprd_pcm_trigger,
	.poपूर्णांकer	= sprd_pcm_poपूर्णांकer,
	.mmap		= sprd_pcm_mmap,
	.pcm_स्थिरruct	= sprd_pcm_new,
	.pcm_deकाष्ठा	= sprd_pcm_मुक्त,
	.compress_ops	= &sprd_platक्रमm_compress_ops,
पूर्ण;

अटल पूर्णांक sprd_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	ret = of_reserved_mem_device_init_by_idx(&pdev->dev, np, 0);
	अगर (ret)
		dev_warn(&pdev->dev,
			 "no reserved DMA memory for audio platform device\n");

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sprd_soc_component,
					      शून्य, 0);
	अगर (ret)
		dev_err(&pdev->dev, "could not register platform:%d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_pcm_of_match[] = अणु
	अणु .compatible = "sprd,pcm-platform", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_pcm_of_match);

अटल काष्ठा platक्रमm_driver sprd_pcm_driver = अणु
	.driver = अणु
		.name = "sprd-pcm-audio",
		.of_match_table = sprd_pcm_of_match,
	पूर्ण,

	.probe = sprd_soc_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(sprd_pcm_driver);

MODULE_DESCRIPTION("Spreadtrum ASoC PCM DMA");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sprd-audio");
