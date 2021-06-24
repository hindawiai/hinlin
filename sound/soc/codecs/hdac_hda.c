<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2015-18 Intel Corporation.

/*
 * hdac_hda.c - ASoC extensions to reuse the legacy HDA codec drivers
 * with ASoC platक्रमm drivers. These APIs are called by the legacy HDA
 * codec drivers using hdac_ext_bus_ops ops.
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_i915.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/hda_रेजिस्टर.h>

#समावेश "hdac_hda.h"

#घोषणा STUB_FORMATS	(SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_U8 | \
			SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_U16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | \
			SNDRV_PCM_FMTBIT_U24_LE | \
			SNDRV_PCM_FMTBIT_S32_LE | \
			SNDRV_PCM_FMTBIT_U32_LE | \
			SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)

#घोषणा STUB_HDMI_RATES	(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |\
				 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |\
				 SNDRV_PCM_RATE_192000)

अटल पूर्णांक hdac_hda_dai_खोलो(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai);
अटल व्योम hdac_hda_dai_बंद(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai);
अटल पूर्णांक hdac_hda_dai_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai);
अटल पूर्णांक hdac_hda_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai);
अटल पूर्णांक hdac_hda_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai);
अटल पूर्णांक hdac_hda_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				     अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				     पूर्णांक slots, पूर्णांक slot_width);
अटल काष्ठा hda_pcm *snd_soc_find_pcm_from_dai(काष्ठा hdac_hda_priv *hda_pvt,
						 काष्ठा snd_soc_dai *dai);

अटल स्थिर काष्ठा snd_soc_dai_ops hdac_hda_dai_ops = अणु
	.startup = hdac_hda_dai_खोलो,
	.shutकरोwn = hdac_hda_dai_बंद,
	.prepare = hdac_hda_dai_prepare,
	.hw_params = hdac_hda_dai_hw_params,
	.hw_मुक्त = hdac_hda_dai_hw_मुक्त,
	.set_tdm_slot = hdac_hda_dai_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver hdac_hda_dais[] = अणु
अणु
	.id = HDAC_ANALOG_DAI_ID,
	.name = "Analog Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name	= "Analog Codec Playback",
		.channels_min	= 1,
		.channels_max	= 16,
		.rates		= SNDRV_PCM_RATE_8000_192000,
		.क्रमmats	= STUB_FORMATS,
		.sig_bits	= 24,
	पूर्ण,
	.capture = अणु
		.stream_name    = "Analog Codec Capture",
		.channels_min   = 1,
		.channels_max   = 16,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_DIGITAL_DAI_ID,
	.name = "Digital Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name    = "Digital Codec Playback",
		.channels_min   = 1,
		.channels_max   = 16,
		.rates          = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats        = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.capture = अणु
		.stream_name    = "Digital Codec Capture",
		.channels_min   = 1,
		.channels_max   = 16,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_ALT_ANALOG_DAI_ID,
	.name = "Alt Analog Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name	= "Alt Analog Codec Playback",
		.channels_min	= 1,
		.channels_max	= 16,
		.rates		= SNDRV_PCM_RATE_8000_192000,
		.क्रमmats	= STUB_FORMATS,
		.sig_bits	= 24,
	पूर्ण,
	.capture = अणु
		.stream_name    = "Alt Analog Codec Capture",
		.channels_min   = 1,
		.channels_max   = 16,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_HDMI_0_DAI_ID,
	.name = "intel-hdmi-hifi1",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name    = "hifi1",
		.channels_min   = 1,
		.channels_max   = 32,
		.rates          = STUB_HDMI_RATES,
		.क्रमmats        = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_HDMI_1_DAI_ID,
	.name = "intel-hdmi-hifi2",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name    = "hifi2",
		.channels_min   = 1,
		.channels_max   = 32,
		.rates          = STUB_HDMI_RATES,
		.क्रमmats        = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_HDMI_2_DAI_ID,
	.name = "intel-hdmi-hifi3",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name    = "hifi3",
		.channels_min   = 1,
		.channels_max   = 32,
		.rates          = STUB_HDMI_RATES,
		.क्रमmats        = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,
अणु
	.id = HDAC_HDMI_3_DAI_ID,
	.name = "intel-hdmi-hifi4",
	.ops = &hdac_hda_dai_ops,
	.playback = अणु
		.stream_name    = "hifi4",
		.channels_min   = 1,
		.channels_max   = 32,
		.rates          = STUB_HDMI_RATES,
		.क्रमmats        = STUB_FORMATS,
		.sig_bits = 24,
	पूर्ण,
पूर्ण,

पूर्ण;

अटल पूर्णांक hdac_hda_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				     अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				     पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hdac_hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = &hda_pvt->pcm[dai->id];

	अगर (tx_mask)
		pcm->stream_tag[SNDRV_PCM_STREAM_PLAYBACK] = tx_mask;
	अन्यथा
		pcm->stream_tag[SNDRV_PCM_STREAM_CAPTURE] = rx_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hda_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hda_priv *hda_pvt;
	अचिन्हित पूर्णांक क्रमmat_val;
	अचिन्हित पूर्णांक maxbps;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		maxbps = dai->driver->playback.sig_bits;
	अन्यथा
		maxbps = dai->driver->capture.sig_bits;

	hda_pvt = snd_soc_component_get_drvdata(component);
	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(params_rate(params),
						 params_channels(params),
						 params_क्रमmat(params),
						 maxbps,
						 0);
	अगर (!क्रमmat_val) अणु
		dev_err(dai->dev,
			"invalid format_val, rate=%d, ch=%d, format=%d, maxbps=%d\n",
			params_rate(params), params_channels(params),
			params_क्रमmat(params), maxbps);

		वापस -EINVAL;
	पूर्ण

	hda_pvt->pcm[dai->id].क्रमmat_val[substream->stream] = क्रमmat_val;
	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hda_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hda_pcm_stream *hda_stream;
	काष्ठा hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = snd_soc_find_pcm_from_dai(hda_pvt, dai);
	अगर (!pcm)
		वापस -EINVAL;

	hda_stream = &pcm->stream[substream->stream];
	snd_hda_codec_cleanup(&hda_pvt->codec, hda_stream, substream);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hda_dai_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hda_pcm_stream *hda_stream;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hdac_device *hdev;
	अचिन्हित पूर्णांक क्रमmat_val;
	काष्ठा hda_pcm *pcm;
	अचिन्हित पूर्णांक stream;
	पूर्णांक ret = 0;

	hda_pvt = snd_soc_component_get_drvdata(component);
	hdev = &hda_pvt->codec.core;
	pcm = snd_soc_find_pcm_from_dai(hda_pvt, dai);
	अगर (!pcm)
		वापस -EINVAL;

	hda_stream = &pcm->stream[substream->stream];

	stream = hda_pvt->pcm[dai->id].stream_tag[substream->stream];
	क्रमmat_val = hda_pvt->pcm[dai->id].क्रमmat_val[substream->stream];

	ret = snd_hda_codec_prepare(&hda_pvt->codec, hda_stream,
				    stream, क्रमmat_val, substream);
	अगर (ret < 0)
		dev_err(&hdev->dev, "codec prepare failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hdac_hda_dai_खोलो(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hda_pcm_stream *hda_stream;
	काष्ठा hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = snd_soc_find_pcm_from_dai(hda_pvt, dai);
	अगर (!pcm)
		वापस -EINVAL;

	snd_hda_codec_pcm_get(pcm);

	hda_stream = &pcm->stream[substream->stream];

	वापस hda_stream->ops.खोलो(hda_stream, &hda_pvt->codec, substream);
पूर्ण

अटल व्योम hdac_hda_dai_बंद(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hda_pcm_stream *hda_stream;
	काष्ठा hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = snd_soc_find_pcm_from_dai(hda_pvt, dai);
	अगर (!pcm)
		वापस;

	hda_stream = &pcm->stream[substream->stream];

	hda_stream->ops.बंद(hda_stream, &hda_pvt->codec, substream);

	snd_hda_codec_pcm_put(pcm);
पूर्ण

अटल काष्ठा hda_pcm *snd_soc_find_pcm_from_dai(काष्ठा hdac_hda_priv *hda_pvt,
						 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hda_codec *hcodec = &hda_pvt->codec;
	काष्ठा hda_pcm *cpcm;
	स्थिर अक्षर *pcm_name;

	/*
	 * map DAI ID to the बंदst matching PCM name, using the naming
	 * scheme used by hda-codec snd_hda_gen_build_pcms() and क्रम
	 * HDMI in hda_codec patch_hdmi.c)
	 */

	चयन (dai->id) अणु
	हाल HDAC_ANALOG_DAI_ID:
		pcm_name = "Analog";
		अवरोध;
	हाल HDAC_DIGITAL_DAI_ID:
		pcm_name = "Digital";
		अवरोध;
	हाल HDAC_ALT_ANALOG_DAI_ID:
		pcm_name = "Alt Analog";
		अवरोध;
	हाल HDAC_HDMI_0_DAI_ID:
		pcm_name = "HDMI 0";
		अवरोध;
	हाल HDAC_HDMI_1_DAI_ID:
		pcm_name = "HDMI 1";
		अवरोध;
	हाल HDAC_HDMI_2_DAI_ID:
		pcm_name = "HDMI 2";
		अवरोध;
	हाल HDAC_HDMI_3_DAI_ID:
		pcm_name = "HDMI 3";
		अवरोध;
	शेष:
		dev_err(&hcodec->core.dev, "invalid dai id %d\n", dai->id);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(cpcm, &hcodec->pcm_list_head, list) अणु
		अगर (म_माला(cpcm->name, pcm_name))
			वापस cpcm;
	पूर्ण

	dev_err(&hcodec->core.dev, "didn't find PCM for DAI %s\n", dai->name);
	वापस शून्य;
पूर्ण

अटल bool is_hdmi_codec(काष्ठा hda_codec *hcodec)
अणु
	काष्ठा hda_pcm *cpcm;

	list_क्रम_each_entry(cpcm, &hcodec->pcm_list_head, list) अणु
		अगर (cpcm->pcm_type == HDA_PCM_TYPE_HDMI)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक hdac_hda_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_hda_priv *hda_pvt =
			snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	काष्ठा hdac_device *hdev = &hda_pvt->codec.core;
	काष्ठा hda_codec *hcodec = &hda_pvt->codec;
	काष्ठा hdac_ext_link *hlink;
	hda_codec_patch_t patch;
	पूर्णांक ret;

	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	अगर (!hlink) अणु
		dev_err(&hdev->dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण

	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	/*
	 * Ensure any HDA display is घातered at codec probe.
	 * After snd_hda_codec_device_new(), display घातer is
	 * managed by runसमय PM.
	 */
	अगर (hda_pvt->need_display_घातer)
		snd_hdac_display_घातer(hdev->bus,
				       HDA_CODEC_IDX_CONTROLLER, true);

	ret = snd_hda_codec_device_new(hcodec->bus, component->card->snd_card,
				       hdev->addr, hcodec);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to create hda codec %d\n", ret);
		जाओ error_no_pm;
	पूर्ण
	/*
	 * Overग_लिखो type to HDA_DEV_ASOC since it is a ASoC driver
	 * hda_codec.c will check this flag to determine अगर unरेजिस्टर
	 * device is needed.
	 */
	hdev->type = HDA_DEV_ASOC;

	/*
	 * snd_hda_codec_device_new decrements the usage count so call get pm
	 * अन्यथा the device will be घातered off
	 */
	pm_runसमय_get_noresume(&hdev->dev);

	hcodec->bus->card = dapm->card->snd_card;

	ret = snd_hda_codec_set_name(hcodec, hcodec->preset->name);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "name failed %s\n", hcodec->preset->name);
		जाओ error_pm;
	पूर्ण

	ret = snd_hdac_regmap_init(&hcodec->core);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "regmap init failed\n");
		जाओ error_pm;
	पूर्ण

	patch = (hda_codec_patch_t)hcodec->preset->driver_data;
	अगर (patch) अणु
		ret = patch(hcodec);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "patch failed %d\n", ret);
			जाओ error_regmap;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&hdev->dev, "no patch file found\n");
	पूर्ण

	/* configure codec क्रम 1:1 PCM:DAI mapping */
	hcodec->mst_no_extra_pcms = 1;

	ret = snd_hda_codec_parse_pcms(hcodec);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "unable to map pcms to dai %d\n", ret);
		जाओ error_patch;
	पूर्ण

	/* HDMI controls need to be created in machine drivers */
	अगर (!is_hdmi_codec(hcodec)) अणु
		ret = snd_hda_codec_build_controls(hcodec);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "unable to create controls %d\n",
				ret);
			जाओ error_patch;
		पूर्ण
	पूर्ण

	hcodec->core.lazy_cache = true;

	अगर (hda_pvt->need_display_घातer)
		snd_hdac_display_घातer(hdev->bus,
				       HDA_CODEC_IDX_CONTROLLER, false);

	/* match क्रम क्रमbid call in snd_hda_codec_device_new() */
	pm_runसमय_allow(&hdev->dev);

	/*
	 * hdac_device core alपढ़ोy sets the state to active and calls
	 * get_noresume. So enable runसमय and set the device to suspend.
	 * pm_runसमय_enable is also called during codec रेजिस्टरation
	 */
	pm_runसमय_put(&hdev->dev);
	pm_runसमय_suspend(&hdev->dev);

	वापस 0;

error_patch:
	अगर (hcodec->patch_ops.मुक्त)
		hcodec->patch_ops.मुक्त(hcodec);
error_regmap:
	snd_hdac_regmap_निकास(hdev);
error_pm:
	pm_runसमय_put(&hdev->dev);
error_no_pm:
	snd_hdac_ext_bus_link_put(hdev->bus, hlink);
	वापस ret;
पूर्ण

अटल व्योम hdac_hda_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_hda_priv *hda_pvt =
		      snd_soc_component_get_drvdata(component);
	काष्ठा hdac_device *hdev = &hda_pvt->codec.core;
	काष्ठा hda_codec *codec = &hda_pvt->codec;
	काष्ठा hdac_ext_link *hlink = शून्य;

	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	अगर (!hlink) अणु
		dev_err(&hdev->dev, "hdac link not found\n");
		वापस;
	पूर्ण

	pm_runसमय_disable(&hdev->dev);
	snd_hdac_ext_bus_link_put(hdev->bus, hlink);

	अगर (codec->patch_ops.मुक्त)
		codec->patch_ops.मुक्त(codec);

	snd_hda_codec_cleanup_क्रम_unbind(codec);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route hdac_hda_dapm_routes[] = अणु
	अणु"AIF1TX", शून्य, "Codec Input Pin1"पूर्ण,
	अणु"AIF2TX", शून्य, "Codec Input Pin2"पूर्ण,
	अणु"AIF3TX", शून्य, "Codec Input Pin3"पूर्ण,

	अणु"Codec Output Pin1", शून्य, "AIF1RX"पूर्ण,
	अणु"Codec Output Pin2", शून्य, "AIF2RX"पूर्ण,
	अणु"Codec Output Pin3", शून्य, "AIF3RX"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget hdac_hda_dapm_widमाला_लो[] = अणु
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "Analog Codec Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "Digital Codec Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3RX", "Alt Analog Codec Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "Analog Codec Capture", 0,
			     SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "Digital Codec Capture", 0,
			     SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "Alt Analog Codec Capture", 0,
			     SND_SOC_NOPM, 0, 0),

	/* Input Pins */
	SND_SOC_DAPM_INPUT("Codec Input Pin1"),
	SND_SOC_DAPM_INPUT("Codec Input Pin2"),
	SND_SOC_DAPM_INPUT("Codec Input Pin3"),

	/* Output Pins */
	SND_SOC_DAPM_OUTPUT("Codec Output Pin1"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin2"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver hdac_hda_codec = अणु
	.probe		= hdac_hda_codec_probe,
	.हटाओ		= hdac_hda_codec_हटाओ,
	.idle_bias_on	= false,
	.dapm_widमाला_लो           = hdac_hda_dapm_widमाला_लो,
	.num_dapm_widमाला_लो       = ARRAY_SIZE(hdac_hda_dapm_widमाला_लो),
	.dapm_routes            = hdac_hda_dapm_routes,
	.num_dapm_routes        = ARRAY_SIZE(hdac_hda_dapm_routes),
पूर्ण;

अटल पूर्णांक hdac_hda_dev_probe(काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_ext_link *hlink;
	काष्ठा hdac_hda_priv *hda_pvt;
	पूर्णांक ret;

	/* hold the ref जबतक we probe */
	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	अगर (!hlink) अणु
		dev_err(&hdev->dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण
	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	hda_pvt = hdac_to_hda_priv(hdev);
	अगर (!hda_pvt)
		वापस -ENOMEM;

	/* ASoC specअगरic initialization */
	ret = devm_snd_soc_रेजिस्टर_component(&hdev->dev,
					 &hdac_hda_codec, hdac_hda_dais,
					 ARRAY_SIZE(hdac_hda_dais));
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to register HDA codec %d\n", ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&hdev->dev, hda_pvt);
	snd_hdac_ext_bus_link_put(hdev->bus, hlink);

	वापस ret;
पूर्ण

अटल पूर्णांक hdac_hda_dev_हटाओ(काष्ठा hdac_device *hdev)
अणु
	/*
	 * Resources are मुक्तd in hdac_hda_codec_हटाओ(). This
	 * function is kept to keep hda_codec_driver_हटाओ() happy.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा hdac_ext_bus_ops hdac_ops = अणु
	.hdev_attach = hdac_hda_dev_probe,
	.hdev_detach = hdac_hda_dev_हटाओ,
पूर्ण;

काष्ठा hdac_ext_bus_ops *snd_soc_hdac_hda_get_ops(व्योम)
अणु
	वापस &hdac_ops;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_hdac_hda_get_ops);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASoC Extensions for legacy HDA Drivers");
MODULE_AUTHOR("Rakesh Ughreja<rakesh.a.ughreja@intel.com>");
