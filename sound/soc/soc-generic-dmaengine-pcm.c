<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
//  Copyright (C) 2013, Analog Devices Inc.
//	Author: Lars-Peter Clausen <lars@metafoo.de>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>

#समावेश <sound/dmaengine_pcm.h>

/*
 * The platक्रमms dmaengine driver करोes not support reporting the amount of
 * bytes that are still left to transfer.
 */
#घोषणा SND_DMAENGINE_PCM_FLAG_NO_RESIDUE BIT(31)

अटल काष्ठा device *dmaengine_dma_dev(काष्ठा dmaengine_pcm *pcm,
	काष्ठा snd_pcm_substream *substream)
अणु
	अगर (!pcm->chan[substream->stream])
		वापस शून्य;

	वापस pcm->chan[substream->stream]->device->dev;
पूर्ण

/**
 * snd_dmaengine_pcm_prepare_slave_config() - Generic prepare_slave_config callback
 * @substream: PCM substream
 * @params: hw_params
 * @slave_config: DMA slave config to prepare
 *
 * This function can be used as a generic prepare_slave_config callback क्रम
 * platक्रमms which make use of the snd_dmaengine_dai_dma_data काष्ठा क्रम their
 * DAI DMA data. Internally the function will first call
 * snd_hwparams_to_dma_slave_config to fill in the slave config based on the
 * hw_params, followed by snd_dmaengine_set_config_from_dai_data to fill in the
 * reमुख्यing fields based on the DAI DMA data.
 */
पूर्णांक snd_dmaengine_pcm_prepare_slave_config(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक ret;

	अगर (rtd->num_cpus > 1) अणु
		dev_err(rtd->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dma_data = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

	ret = snd_hwparams_to_dma_slave_config(substream, params, slave_config);
	अगर (ret)
		वापस ret;

	snd_dmaengine_pcm_set_config_from_dai_data(substream, dma_data,
		slave_config);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_prepare_slave_config);

अटल पूर्णांक dmaengine_pcm_hw_params(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	काष्ठा dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
	पूर्णांक (*prepare_slave_config)(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params,
			काष्ठा dma_slave_config *slave_config);
	काष्ठा dma_slave_config slave_config;
	पूर्णांक ret;

	स_रखो(&slave_config, 0, माप(slave_config));

	अगर (!pcm->config)
		prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config;
	अन्यथा
		prepare_slave_config = pcm->config->prepare_slave_config;

	अगर (prepare_slave_config) अणु
		ret = prepare_slave_config(substream, params, &slave_config);
		अगर (ret)
			वापस ret;

		ret = dmaengine_slave_config(chan, &slave_config);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
dmaengine_pcm_set_runसमय_hwparams(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	काष्ठा device *dma_dev = dmaengine_dma_dev(pcm, substream);
	काष्ठा dma_chan *chan = pcm->chan[substream->stream];
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	काष्ठा snd_pcm_hardware hw;

	अगर (rtd->num_cpus > 1) अणु
		dev_err(rtd->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (pcm->config && pcm->config->pcm_hardware)
		वापस snd_soc_set_runसमय_hwparams(substream,
				pcm->config->pcm_hardware);

	dma_data = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

	स_रखो(&hw, 0, माप(hw));
	hw.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED;
	hw.periods_min = 2;
	hw.periods_max = अच_पूर्णांक_उच्च;
	hw.period_bytes_min = 256;
	hw.period_bytes_max = dma_get_max_seg_size(dma_dev);
	hw.buffer_bytes_max = SIZE_MAX;
	hw.fअगरo_size = dma_data->fअगरo_size;

	अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_NO_RESIDUE)
		hw.info |= SNDRV_PCM_INFO_BATCH;

	/**
	 * FIXME: Remove the वापस value check to align with the code
	 * beक्रमe adding snd_dmaengine_pcm_refine_runसमय_hwparams
	 * function.
	 */
	snd_dmaengine_pcm_refine_runसमय_hwparams(substream,
						  dma_data,
						  &hw,
						  chan);

	वापस snd_soc_set_runसमय_hwparams(substream, &hw);
पूर्ण

अटल पूर्णांक dmaengine_pcm_खोलो(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	काष्ठा dma_chan *chan = pcm->chan[substream->stream];
	पूर्णांक ret;

	ret = dmaengine_pcm_set_runसमय_hwparams(component, substream);
	अगर (ret)
		वापस ret;

	वापस snd_dmaengine_pcm_खोलो(substream, chan);
पूर्ण

अटल पूर्णांक dmaengine_pcm_बंद(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_बंद(substream);
पूर्ण

अटल पूर्णांक dmaengine_pcm_trigger(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस snd_dmaengine_pcm_trigger(substream, cmd);
पूर्ण

अटल काष्ठा dma_chan *dmaengine_pcm_compat_request_channel(
	काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_pcm_runसमय *rtd,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	dma_filter_fn fn = शून्य;

	अगर (rtd->num_cpus > 1) अणु
		dev_err(rtd->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस शून्य;
	पूर्ण

	dma_data = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

	अगर ((pcm->flags & SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX) && pcm->chan[0])
		वापस pcm->chan[0];

	अगर (pcm->config && pcm->config->compat_request_channel)
		वापस pcm->config->compat_request_channel(rtd, substream);

	अगर (pcm->config)
		fn = pcm->config->compat_filter_fn;

	वापस snd_dmaengine_pcm_request_channel(fn, dma_data->filter_data);
पूर्ण

अटल bool dmaengine_pcm_can_report_residue(काष्ठा device *dev,
	काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_slave_caps dma_caps;
	पूर्णांक ret;

	ret = dma_get_slave_caps(chan, &dma_caps);
	अगर (ret != 0) अणु
		dev_warn(dev, "Failed to get DMA channel capabilities, falling back to period counting: %d\n",
			 ret);
		वापस false;
	पूर्ण

	अगर (dma_caps.residue_granularity == DMA_RESIDUE_GRANULARITY_DESCRIPTOR)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक dmaengine_pcm_new(काष्ठा snd_soc_component *component,
			     काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	स्थिर काष्ठा snd_dmaengine_pcm_config *config = pcm->config;
	काष्ठा device *dev = component->dev;
	काष्ठा snd_pcm_substream *substream;
	माप_प्रकार pपुनः_स्मृति_buffer_size;
	माप_प्रकार max_buffer_size;
	अचिन्हित पूर्णांक i;

	अगर (config && config->pपुनः_स्मृति_buffer_size) अणु
		pपुनः_स्मृति_buffer_size = config->pपुनः_स्मृति_buffer_size;
		max_buffer_size = config->pcm_hardware->buffer_bytes_max;
	पूर्ण अन्यथा अणु
		pपुनः_स्मृति_buffer_size = 512 * 1024;
		max_buffer_size = SIZE_MAX;
	पूर्ण

	क्रम_each_pcm_streams(i) अणु
		substream = rtd->pcm->streams[i].substream;
		अगर (!substream)
			जारी;

		अगर (!pcm->chan[i] && config && config->chan_names[i])
			pcm->chan[i] = dma_request_slave_channel(dev,
				config->chan_names[i]);

		अगर (!pcm->chan[i] && (pcm->flags & SND_DMAENGINE_PCM_FLAG_COMPAT)) अणु
			pcm->chan[i] = dmaengine_pcm_compat_request_channel(
				component, rtd, substream);
		पूर्ण

		अगर (!pcm->chan[i]) अणु
			dev_err(component->dev,
				"Missing dma channel for stream: %d\n", i);
			वापस -EINVAL;
		पूर्ण

		snd_pcm_set_managed_buffer(substream,
				SNDRV_DMA_TYPE_DEV_IRAM,
				dmaengine_dma_dev(pcm, substream),
				pपुनः_स्मृति_buffer_size,
				max_buffer_size);

		अगर (!dmaengine_pcm_can_report_residue(dev, pcm->chan[i]))
			pcm->flags |= SND_DMAENGINE_PCM_FLAG_NO_RESIDUE;

		अगर (rtd->pcm->streams[i].pcm->name[0] == '\0') अणु
			strscpy_pad(rtd->pcm->streams[i].pcm->name,
				    rtd->pcm->streams[i].pcm->id,
				    माप(rtd->pcm->streams[i].pcm->name));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t dmaengine_pcm_poपूर्णांकer(
	काष्ठा snd_soc_component *component,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);

	अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_NO_RESIDUE)
		वापस snd_dmaengine_pcm_poपूर्णांकer_no_residue(substream);
	अन्यथा
		वापस snd_dmaengine_pcm_poपूर्णांकer(substream);
पूर्ण

अटल पूर्णांक dmaengine_copy_user(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ hwoff,
			       व्योम __user *buf, अचिन्हित दीर्घ bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dmaengine_pcm *pcm = soc_component_to_pcm(component);
	पूर्णांक (*process)(काष्ठा snd_pcm_substream *substream,
		       पूर्णांक channel, अचिन्हित दीर्घ hwoff,
		       व्योम *buf, अचिन्हित दीर्घ bytes) = pcm->config->process;
	bool is_playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	व्योम *dma_ptr = runसमय->dma_area + hwoff +
			channel * (runसमय->dma_bytes / runसमय->channels);
	पूर्णांक ret;

	अगर (is_playback)
		अगर (copy_from_user(dma_ptr, buf, bytes))
			वापस -EFAULT;

	अगर (process) अणु
		ret = process(substream, channel, hwoff, (__क्रमce व्योम *)buf, bytes);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!is_playback)
		अगर (copy_to_user(buf, dma_ptr, bytes))
			वापस -EFAULT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver dmaengine_pcm_component = अणु
	.name		= SND_DMAENGINE_PCM_DRV_NAME,
	.probe_order	= SND_SOC_COMP_ORDER_LATE,
	.खोलो		= dmaengine_pcm_खोलो,
	.बंद		= dmaengine_pcm_बंद,
	.hw_params	= dmaengine_pcm_hw_params,
	.trigger	= dmaengine_pcm_trigger,
	.poपूर्णांकer	= dmaengine_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= dmaengine_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver dmaengine_pcm_component_process = अणु
	.name		= SND_DMAENGINE_PCM_DRV_NAME,
	.probe_order	= SND_SOC_COMP_ORDER_LATE,
	.खोलो		= dmaengine_pcm_खोलो,
	.बंद		= dmaengine_pcm_बंद,
	.hw_params	= dmaengine_pcm_hw_params,
	.trigger	= dmaengine_pcm_trigger,
	.poपूर्णांकer	= dmaengine_pcm_poपूर्णांकer,
	.copy_user	= dmaengine_copy_user,
	.pcm_स्थिरruct	= dmaengine_pcm_new,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmaengine_pcm_dma_channel_names[] = अणु
	[SNDRV_PCM_STREAM_PLAYBACK] = "tx",
	[SNDRV_PCM_STREAM_CAPTURE] = "rx",
पूर्ण;

अटल पूर्णांक dmaengine_pcm_request_chan_of(काष्ठा dmaengine_pcm *pcm,
	काष्ठा device *dev, स्थिर काष्ठा snd_dmaengine_pcm_config *config)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *name;
	काष्ठा dma_chan *chan;

	अगर ((pcm->flags & SND_DMAENGINE_PCM_FLAG_NO_DT) || (!dev->of_node &&
	    !(config && config->dma_dev && config->dma_dev->of_node)))
		वापस 0;

	अगर (config && config->dma_dev) अणु
		/*
		 * If this warning is seen, it probably means that your Linux
		 * device काष्ठाure करोes not match your HW device काष्ठाure.
		 * It would be best to refactor the Linux device काष्ठाure to
		 * correctly match the HW काष्ठाure.
		 */
		dev_warn(dev, "DMA channels sourced from device %s",
			 dev_name(config->dma_dev));
		dev = config->dma_dev;
	पूर्ण

	क्रम_each_pcm_streams(i) अणु
		अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX)
			name = "rx-tx";
		अन्यथा
			name = dmaengine_pcm_dma_channel_names[i];
		अगर (config && config->chan_names[i])
			name = config->chan_names[i];
		chan = dma_request_chan(dev, name);
		अगर (IS_ERR(chan)) अणु
			/*
			 * Only report probe deferral errors, channels
			 * might not be present क्रम devices that
			 * support only TX or only RX.
			 */
			अगर (PTR_ERR(chan) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			pcm->chan[i] = शून्य;
		पूर्ण अन्यथा अणु
			pcm->chan[i] = chan;
		पूर्ण
		अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX)
			अवरोध;
	पूर्ण

	अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX)
		pcm->chan[1] = pcm->chan[0];

	वापस 0;
पूर्ण

अटल व्योम dmaengine_pcm_release_chan(काष्ठा dmaengine_pcm *pcm)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_pcm_streams(i) अणु
		अगर (!pcm->chan[i])
			जारी;
		dma_release_channel(pcm->chan[i]);
		अगर (pcm->flags & SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * snd_dmaengine_pcm_रेजिस्टर - Register a dmaengine based PCM device
 * @dev: The parent device क्रम the PCM device
 * @config: Platक्रमm specअगरic PCM configuration
 * @flags: Platक्रमm specअगरic quirks
 */
पूर्णांक snd_dmaengine_pcm_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा snd_dmaengine_pcm_config *config, अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा snd_soc_component_driver *driver;
	काष्ठा dmaengine_pcm *pcm;
	पूर्णांक ret;

	pcm = kzalloc(माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_DEBUG_FS
	pcm->component.debugfs_prefix = "dma";
#पूर्ण_अगर
	pcm->config = config;
	pcm->flags = flags;

	ret = dmaengine_pcm_request_chan_of(pcm, dev, config);
	अगर (ret)
		जाओ err_मुक्त_dma;

	अगर (config && config->process)
		driver = &dmaengine_pcm_component_process;
	अन्यथा
		driver = &dmaengine_pcm_component;

	ret = snd_soc_component_initialize(&pcm->component, driver, dev);
	अगर (ret)
		जाओ err_मुक्त_dma;

	ret = snd_soc_add_component(&pcm->component, शून्य, 0);
	अगर (ret)
		जाओ err_मुक्त_dma;

	वापस 0;

err_मुक्त_dma:
	dmaengine_pcm_release_chan(pcm);
	kमुक्त(pcm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_रेजिस्टर);

/**
 * snd_dmaengine_pcm_unरेजिस्टर - Removes a dmaengine based PCM device
 * @dev: Parent device the PCM was रेजिस्टर with
 *
 * Removes a dmaengine based PCM device previously रेजिस्टरed with
 * snd_dmaengine_pcm_रेजिस्टर.
 */
व्योम snd_dmaengine_pcm_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा dmaengine_pcm *pcm;

	component = snd_soc_lookup_component(dev, SND_DMAENGINE_PCM_DRV_NAME);
	अगर (!component)
		वापस;

	pcm = soc_component_to_pcm(component);

	snd_soc_unरेजिस्टर_component_by_driver(dev, component->driver);
	dmaengine_pcm_release_chan(pcm);
	kमुक्त(pcm);
पूर्ण
EXPORT_SYMBOL_GPL(snd_dmaengine_pcm_unरेजिस्टर);

MODULE_LICENSE("GPL");
