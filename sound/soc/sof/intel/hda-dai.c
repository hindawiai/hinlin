<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

#समावेश <sound/pcm_params.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश "../sof-priv.h"
#समावेश "../sof-audio.h"
#समावेश "hda.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)

काष्ठा hda_pipe_params अणु
	u8 host_dma_id;
	u8 link_dma_id;
	u32 ch;
	u32 s_freq;
	u32 s_fmt;
	u8 linktype;
	snd_pcm_क्रमmat_t क्रमmat;
	पूर्णांक link_index;
	पूर्णांक stream;
	अचिन्हित पूर्णांक host_bps;
	अचिन्हित पूर्णांक link_bps;
पूर्ण;

/*
 * This function checks अगर the host dma channel corresponding
 * to the link DMA stream_tag argument is asचिन्हित to one
 * of the FEs connected to the BE DAI.
 */
अटल bool hda_check_fes(काष्ठा snd_soc_pcm_runसमय *rtd,
			  पूर्णांक dir, पूर्णांक stream_tag)
अणु
	काष्ठा snd_pcm_substream *fe_substream;
	काष्ठा hdac_stream *fe_hstream;
	काष्ठा snd_soc_dpcm *dpcm;

	क्रम_each_dpcm_fe(rtd, dir, dpcm) अणु
		fe_substream = snd_soc_dpcm_get_substream(dpcm->fe, dir);
		fe_hstream = fe_substream->runसमय->निजी_data;
		अगर (fe_hstream->stream_tag == stream_tag)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा hdac_ext_stream *
	hda_link_stream_assign(काष्ठा hdac_bus *bus,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा hdac_ext_stream *res = शून्य;
	काष्ठा hdac_stream *stream = शून्य;

	पूर्णांक stream_dir = substream->stream;

	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "stream type not supported\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		काष्ठा hdac_ext_stream *hstream =
			stream_to_hdac_ext_stream(stream);
		अगर (stream->direction != substream->stream)
			जारी;

		hda_stream = hstream_to_sof_hda_stream(hstream);

		/* check अगर link is available */
		अगर (!hstream->link_locked) अणु
			अगर (stream->खोलोed) अणु
				/*
				 * check अगर the stream tag matches the stream
				 * tag of one of the connected FEs
				 */
				अगर (hda_check_fes(rtd, stream_dir,
						  stream->stream_tag)) अणु
					res = hstream;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				res = hstream;

				/*
				 * This must be a hostless stream.
				 * So reserve the host DMA channel.
				 */
				hda_stream->host_reserved = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (res) अणु
		/*
		 * Decouple host and link DMA. The decoupled flag
		 * is updated in snd_hdac_ext_stream_decouple().
		 */
		अगर (!res->decoupled)
			snd_hdac_ext_stream_decouple(bus, res, true);
		spin_lock_irq(&bus->reg_lock);
		res->link_locked = 1;
		res->link_substream = substream;
		spin_unlock_irq(&bus->reg_lock);
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक hda_link_dma_params(काष्ठा hdac_ext_stream *stream,
			       काष्ठा hda_pipe_params *params)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	अचिन्हित अक्षर stream_tag = hstream->stream_tag;
	काष्ठा hdac_bus *bus = hstream->bus;
	काष्ठा hdac_ext_link *link;
	अचिन्हित पूर्णांक क्रमmat_val;

	snd_hdac_ext_stream_decouple(bus, stream, true);
	snd_hdac_ext_link_stream_reset(stream);

	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(params->s_freq, params->ch,
						 params->क्रमmat,
						 params->link_bps, 0);

	dev_dbg(bus->dev, "format_val=%d, rate=%d, ch=%d, format=%d\n",
		क्रमmat_val, params->s_freq, params->ch, params->क्रमmat);

	snd_hdac_ext_link_stream_setup(stream, क्रमmat_val);

	अगर (stream->hstream.direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		list_क्रम_each_entry(link, &bus->hlink_list, list) अणु
			अगर (link->index == params->link_index)
				snd_hdac_ext_link_set_stream_id(link,
								stream_tag);
		पूर्ण
	पूर्ण

	stream->link_prepared = 1;

	वापस 0;
पूर्ण

/* Send DAI_CONFIG IPC to the DAI that matches the dai_name and direction */
अटल पूर्णांक hda_link_config_ipc(काष्ठा sof_पूर्णांकel_hda_stream *hda_stream,
			       स्थिर अक्षर *dai_name, पूर्णांक channel, पूर्णांक dir)
अणु
	काष्ठा sof_ipc_dai_config *config;
	काष्ठा snd_sof_dai *sof_dai;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(sof_dai, &hda_stream->sdev->dai_list, list) अणु
		अगर (!sof_dai->cpu_dai_name)
			जारी;

		अगर (!म_भेद(dai_name, sof_dai->cpu_dai_name) &&
		    dir == sof_dai->comp_dai.direction) अणु
			config = sof_dai->dai_config;

			अगर (!config) अणु
				dev_err(hda_stream->sdev->dev,
					"error: no config for DAI %s\n",
					sof_dai->name);
				वापस -EINVAL;
			पूर्ण

			/* update config with stream tag */
			config->hda.link_dma_ch = channel;

			/* send IPC */
			ret = sof_ipc_tx_message(hda_stream->sdev->ipc,
						 config->hdr.cmd,
						 config,
						 config->hdr.size,
						 &reply, माप(reply));

			अगर (ret < 0)
				dev_err(hda_stream->sdev->dev,
					"error: failed to set dai config for %s\n",
					sof_dai->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hda_link_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	काष्ठा hdac_bus *bus = hstream->bus;
	काष्ठा hdac_ext_stream *link_dev;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा hda_pipe_params p_params = अणु0पूर्ण;
	काष्ठा hdac_ext_link *link;
	पूर्णांक stream_tag;
	पूर्णांक ret;

	/* get stored dma data अगर resuming from प्रणाली suspend */
	link_dev = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!link_dev) अणु
		link_dev = hda_link_stream_assign(bus, substream);
		अगर (!link_dev)
			वापस -EBUSY;

		snd_soc_dai_set_dma_data(dai, substream, (व्योम *)link_dev);
	पूर्ण

	stream_tag = hdac_stream(link_dev)->stream_tag;

	hda_stream = hstream_to_sof_hda_stream(link_dev);

	/* update the DSP with the new tag */
	ret = hda_link_config_ipc(hda_stream, dai->name, stream_tag - 1,
				  substream->stream);
	अगर (ret < 0)
		वापस ret;

	link = snd_hdac_ext_bus_get_link(bus, codec_dai->component->name);
	अगर (!link)
		वापस -EINVAL;

	/* set the stream tag in the codec dai dma params */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dai_set_tdm_slot(codec_dai, stream_tag, 0, 0, 0);
	अन्यथा
		snd_soc_dai_set_tdm_slot(codec_dai, 0, stream_tag, 0, 0);

	p_params.s_fmt = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.stream = substream->stream;
	p_params.link_dma_id = stream_tag - 1;
	p_params.link_index = link->index;
	p_params.क्रमmat = params_क्रमmat(params);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_params.link_bps = codec_dai->driver->playback.sig_bits;
	अन्यथा
		p_params.link_bps = codec_dai->driver->capture.sig_bits;

	वापस hda_link_dma_params(link_dev, &p_params);
पूर्ण

अटल पूर्णांक hda_link_pcm_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *link_dev =
				snd_soc_dai_get_dma_data(dai, substream);
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream;

	अगर (link_dev->link_prepared)
		वापस 0;

	dev_dbg(sdev->dev, "hda: prepare stream dir %d\n", substream->stream);

	वापस hda_link_hw_params(substream, &rtd->dpcm[stream].hw_params,
				  dai);
पूर्ण

अटल पूर्णांक hda_link_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *link_dev =
				snd_soc_dai_get_dma_data(dai, substream);
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा hdac_ext_link *link;
	काष्ठा hdac_stream *hstream;
	काष्ठा hdac_bus *bus;
	पूर्णांक stream_tag;
	पूर्णांक ret;

	hstream = substream->runसमय->निजी_data;
	bus = hstream->bus;
	rtd = asoc_substream_to_rtd(substream);

	link = snd_hdac_ext_bus_get_link(bus, asoc_rtd_to_codec(rtd, 0)->component->name);
	अगर (!link)
		वापस -EINVAL;

	hda_stream = hstream_to_sof_hda_stream(link_dev);

	dev_dbg(dai->dev, "In %s cmd=%d\n", __func__, cmd);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* set up hw_params */
		ret = hda_link_pcm_prepare(substream, dai);
		अगर (ret < 0) अणु
			dev_err(dai->dev,
				"error: setting up hw_params during resume\n");
			वापस ret;
		पूर्ण

		fallthrough;
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_hdac_ext_link_stream_start(link_dev);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		/*
		 * clear link DMA channel. It will be asचिन्हित when
		 * hw_params is set up again after resume.
		 */
		ret = hda_link_config_ipc(hda_stream, dai->name,
					  DMA_CHAN_INVALID, substream->stream);
		अगर (ret < 0)
			वापस ret;

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			stream_tag = hdac_stream(link_dev)->stream_tag;
			snd_hdac_ext_link_clear_stream_id(link, stream_tag);
		पूर्ण

		link_dev->link_prepared = 0;

		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		snd_hdac_ext_link_stream_clear(link_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hda_link_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित पूर्णांक stream_tag;
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा hdac_bus *bus;
	काष्ठा hdac_ext_link *link;
	काष्ठा hdac_stream *hstream;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा hdac_ext_stream *link_dev;
	पूर्णांक ret;

	hstream = substream->runसमय->निजी_data;
	bus = hstream->bus;
	rtd = asoc_substream_to_rtd(substream);
	link_dev = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!link_dev) अणु
		dev_dbg(dai->dev,
			"%s: link_dev is not assigned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	hda_stream = hstream_to_sof_hda_stream(link_dev);

	/* मुक्त the link DMA channel in the FW */
	ret = hda_link_config_ipc(hda_stream, dai->name, DMA_CHAN_INVALID,
				  substream->stream);
	अगर (ret < 0)
		वापस ret;

	link = snd_hdac_ext_bus_get_link(bus, asoc_rtd_to_codec(rtd, 0)->component->name);
	अगर (!link)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		stream_tag = hdac_stream(link_dev)->stream_tag;
		snd_hdac_ext_link_clear_stream_id(link, stream_tag);
	पूर्ण

	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	snd_hdac_ext_stream_release(link_dev, HDAC_EXT_STREAM_TYPE_LINK);
	link_dev->link_prepared = 0;

	/* मुक्त the host DMA channel reserved by hostless streams */
	hda_stream->host_reserved = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops hda_link_dai_ops = अणु
	.hw_params = hda_link_hw_params,
	.hw_मुक्त = hda_link_hw_मुक्त,
	.trigger = hda_link_pcm_trigger,
	.prepare = hda_link_pcm_prepare,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_PROBES)
#समावेश "../compress.h"

अटल काष्ठा snd_soc_cdai_ops sof_probe_compr_ops = अणु
	.startup	= sof_probe_compr_खोलो,
	.shutकरोwn	= sof_probe_compr_मुक्त,
	.set_params	= sof_probe_compr_set_params,
	.trigger	= sof_probe_compr_trigger,
	.poपूर्णांकer	= sof_probe_compr_poपूर्णांकer,
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक ssp_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, SOF_AUDIO_PCM_DRV_NAME);
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	काष्ठा sof_ipc_fw_version *v = &sdev->fw_पढ़ोy.version;
	काष्ठा sof_ipc_dai_config *config;
	काष्ठा snd_sof_dai *sof_dai;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret;

	/* DAI_CONFIG IPC during hw_params is not supported in older firmware */
	अगर (v->abi_version < SOF_ABI_VER(3, 18, 0))
		वापस 0;

	list_क्रम_each_entry(sof_dai, &sdev->dai_list, list) अणु
		अगर (!sof_dai->cpu_dai_name || !sof_dai->dai_config)
			जारी;

		अगर (!म_भेद(dai->name, sof_dai->cpu_dai_name) &&
		    substream->stream == sof_dai->comp_dai.direction) अणु
			config = &sof_dai->dai_config[sof_dai->current_config];

			/* send IPC */
			ret = sof_ipc_tx_message(sdev->ipc, config->hdr.cmd, config,
						 config->hdr.size, &reply, माप(reply));

			अगर (ret < 0)
				dev_err(sdev->dev, "error: failed to set DAI config for %s\n",
					sof_dai->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ssp_dai_ops = अणु
	.hw_params = ssp_dai_hw_params,
पूर्ण;

/*
 * common dai driver क्रम skl+ platक्रमms.
 * some products who use this DAI array only physically have a subset of
 * the DAIs, but no harm is करोne here by adding the whole set.
 */
काष्ठा snd_soc_dai_driver skl_dai[] = अणु
अणु
	.name = "SSP0 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP1 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP2 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP3 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP4 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "SSP5 Pin",
	.ops = &ssp_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "DMIC01 Pin",
	.capture = अणु
		.channels_min = 1,
		.channels_max = 4,
	पूर्ण,
पूर्ण,
अणु
	.name = "DMIC16k Pin",
	.capture = अणु
		.channels_min = 1,
		.channels_max = 4,
	पूर्ण,
पूर्ण,
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
अणु
	.name = "iDisp1 Pin",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp2 Pin",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp3 Pin",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "iDisp4 Pin",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "Analog CPU DAI",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
पूर्ण,
अणु
	.name = "Digital CPU DAI",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
पूर्ण,
अणु
	.name = "Alt Analog CPU DAI",
	.ops = &hda_link_dai_ops,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 16,
	पूर्ण,
पूर्ण,
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_PROBES)
अणु
	.name = "Probe Extraction CPU DAI",
	.compress_new = snd_soc_new_compress,
	.cops = &sof_probe_compr_ops,
	.capture = अणु
		.stream_name = "Probe Extraction",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_48000,
		.rate_min = 48000,
		.rate_max = 48000,
	पूर्ण,
पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;
