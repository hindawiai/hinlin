<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * APBridge ALSA SoC dummy codec driver
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <uapi/linux/input.h>

#समावेश "audio_codec.h"
#समावेश "audio_apbridgea.h"
#समावेश "audio_manager.h"
#समावेश "audio_helper.h"

अटल काष्ठा gbaudio_codec_info *gbcodec;

अटल काष्ठा gbaudio_data_connection *
find_data(काष्ठा gbaudio_module_info *module, पूर्णांक id)
अणु
	काष्ठा gbaudio_data_connection *data;

	list_क्रम_each_entry(data, &module->data_list, list) अणु
		अगर (id == data->id)
			वापस data;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा gbaudio_stream_params *
find_dai_stream_params(काष्ठा gbaudio_codec_info *codec, पूर्णांक id, पूर्णांक stream)
अणु
	काष्ठा gbaudio_codec_dai *dai;

	list_क्रम_each_entry(dai, &codec->dai_list, list) अणु
		अगर (dai->id == id)
			वापस &dai->params[stream];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक gbaudio_module_enable_tx(काष्ठा gbaudio_codec_info *codec,
				    काष्ठा gbaudio_module_info *module, पूर्णांक id)
अणु
	पूर्णांक module_state, ret = 0;
	u16 data_cport, i2s_port, cportid;
	u8 sig_bits, channels;
	u32 क्रमmat, rate;
	काष्ठा gbaudio_data_connection *data;
	काष्ठा gbaudio_stream_params *params;

	/* find the dai */
	data = find_data(module, id);
	अगर (!data) अणु
		dev_err(module->dev, "%d:DATA connection missing\n", id);
		वापस -ENODEV;
	पूर्ण
	module_state = data->state[SNDRV_PCM_STREAM_PLAYBACK];

	params = find_dai_stream_params(codec, id, SNDRV_PCM_STREAM_PLAYBACK);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		वापस -EINVAL;
	पूर्ण

	/* रेजिस्टर cport */
	अगर (module_state < GBAUDIO_CODEC_STARTUP) अणु
		i2s_port = 0;	/* fixed क्रम now */
		cportid = data->connection->hd_cport_id;
		ret = gb_audio_apbridgea_रेजिस्टर_cport(data->connection,
							i2s_port, cportid,
							AUDIO_APBRIDGEA_सूचीECTION_TX);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev, "reg_cport failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_PLAYBACK] = GBAUDIO_CODEC_STARTUP;
		dev_dbg(module->dev, "Dynamic Register %d DAI\n", cportid);
	पूर्ण

	/* hw_params */
	अगर (module_state < GBAUDIO_CODEC_HWPARAMS) अणु
		क्रमmat = params->क्रमmat;
		channels = params->channels;
		rate = params->rate;
		sig_bits = params->sig_bits;
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_set_pcm(module->mgmt_connection, data_cport,
					  क्रमmat, rate, channels, sig_bits);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev, "set_pcm failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_PLAYBACK] = GBAUDIO_CODEC_HWPARAMS;
		dev_dbg(module->dev, "Dynamic hw_params %d DAI\n", data_cport);
	पूर्ण

	/* prepare */
	अगर (module_state < GBAUDIO_CODEC_PREPARE) अणु
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_set_tx_data_size(module->mgmt_connection,
						   data_cport, 192);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "set_tx_data_size failed:%d\n",
					    ret);
			वापस ret;
		पूर्ण
		ret = gb_audio_gb_activate_tx(module->mgmt_connection, data_cport);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "activate_tx failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_PLAYBACK] = GBAUDIO_CODEC_PREPARE;
		dev_dbg(module->dev, "Dynamic prepare %d DAI\n", data_cport);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_module_disable_tx(काष्ठा gbaudio_module_info *module, पूर्णांक id)
अणु
	पूर्णांक ret;
	u16 data_cport, cportid, i2s_port;
	पूर्णांक module_state;
	काष्ठा gbaudio_data_connection *data;

	/* find the dai */
	data = find_data(module, id);
	अगर (!data) अणु
		dev_err(module->dev, "%d:DATA connection missing\n", id);
		वापस -ENODEV;
	पूर्ण
	module_state = data->state[SNDRV_PCM_STREAM_PLAYBACK];

	अगर (module_state > GBAUDIO_CODEC_HWPARAMS) अणु
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_deactivate_tx(module->mgmt_connection,
						data_cport);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "deactivate_tx failed:%d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(module->dev, "Dynamic deactivate %d DAI\n", data_cport);
		data->state[SNDRV_PCM_STREAM_PLAYBACK] = GBAUDIO_CODEC_HWPARAMS;
	पूर्ण

	अगर (module_state > GBAUDIO_CODEC_SHUTDOWN) अणु
		i2s_port = 0;	/* fixed क्रम now */
		cportid = data->connection->hd_cport_id;
		ret = gb_audio_apbridgea_unरेजिस्टर_cport(data->connection,
							  i2s_port, cportid,
							  AUDIO_APBRIDGEA_सूचीECTION_TX);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "unregister_cport failed:%d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(module->dev, "Dynamic Unregister %d DAI\n", cportid);
		data->state[SNDRV_PCM_STREAM_PLAYBACK] = GBAUDIO_CODEC_SHUTDOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_module_enable_rx(काष्ठा gbaudio_codec_info *codec,
				    काष्ठा gbaudio_module_info *module, पूर्णांक id)
अणु
	पूर्णांक module_state, ret = 0;
	u16 data_cport, i2s_port, cportid;
	u8 sig_bits, channels;
	u32 क्रमmat, rate;
	काष्ठा gbaudio_data_connection *data;
	काष्ठा gbaudio_stream_params *params;

	/* find the dai */
	data = find_data(module, id);
	अगर (!data) अणु
		dev_err(module->dev, "%d:DATA connection missing\n", id);
		वापस -ENODEV;
	पूर्ण
	module_state = data->state[SNDRV_PCM_STREAM_CAPTURE];

	params = find_dai_stream_params(codec, id, SNDRV_PCM_STREAM_CAPTURE);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		वापस -EINVAL;
	पूर्ण

	/* रेजिस्टर cport */
	अगर (module_state < GBAUDIO_CODEC_STARTUP) अणु
		i2s_port = 0;	/* fixed क्रम now */
		cportid = data->connection->hd_cport_id;
		ret = gb_audio_apbridgea_रेजिस्टर_cport(data->connection,
							i2s_port, cportid,
							AUDIO_APBRIDGEA_सूचीECTION_RX);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev, "reg_cport failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_CAPTURE] = GBAUDIO_CODEC_STARTUP;
		dev_dbg(module->dev, "Dynamic Register %d DAI\n", cportid);
	पूर्ण

	/* hw_params */
	अगर (module_state < GBAUDIO_CODEC_HWPARAMS) अणु
		क्रमmat = params->क्रमmat;
		channels = params->channels;
		rate = params->rate;
		sig_bits = params->sig_bits;
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_set_pcm(module->mgmt_connection, data_cport,
					  क्रमmat, rate, channels, sig_bits);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev, "set_pcm failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_CAPTURE] = GBAUDIO_CODEC_HWPARAMS;
		dev_dbg(module->dev, "Dynamic hw_params %d DAI\n", data_cport);
	पूर्ण

	/* prepare */
	अगर (module_state < GBAUDIO_CODEC_PREPARE) अणु
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_set_rx_data_size(module->mgmt_connection,
						   data_cport, 192);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "set_rx_data_size failed:%d\n",
					    ret);
			वापस ret;
		पूर्ण
		ret = gb_audio_gb_activate_rx(module->mgmt_connection,
					      data_cport);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "activate_rx failed:%d\n", ret);
			वापस ret;
		पूर्ण
		data->state[SNDRV_PCM_STREAM_CAPTURE] = GBAUDIO_CODEC_PREPARE;
		dev_dbg(module->dev, "Dynamic prepare %d DAI\n", data_cport);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_module_disable_rx(काष्ठा gbaudio_module_info *module, पूर्णांक id)
अणु
	पूर्णांक ret;
	u16 data_cport, cportid, i2s_port;
	पूर्णांक module_state;
	काष्ठा gbaudio_data_connection *data;

	/* find the dai */
	data = find_data(module, id);
	अगर (!data) अणु
		dev_err(module->dev, "%d:DATA connection missing\n", id);
		वापस -ENODEV;
	पूर्ण
	module_state = data->state[SNDRV_PCM_STREAM_CAPTURE];

	अगर (module_state > GBAUDIO_CODEC_HWPARAMS) अणु
		data_cport = data->connection->पूर्णांकf_cport_id;
		ret = gb_audio_gb_deactivate_rx(module->mgmt_connection,
						data_cport);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "deactivate_rx failed:%d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(module->dev, "Dynamic deactivate %d DAI\n", data_cport);
		data->state[SNDRV_PCM_STREAM_CAPTURE] = GBAUDIO_CODEC_HWPARAMS;
	पूर्ण

	अगर (module_state > GBAUDIO_CODEC_SHUTDOWN) अणु
		i2s_port = 0;	/* fixed क्रम now */
		cportid = data->connection->hd_cport_id;
		ret = gb_audio_apbridgea_unरेजिस्टर_cport(data->connection,
							  i2s_port, cportid,
							  AUDIO_APBRIDGEA_सूचीECTION_RX);
		अगर (ret) अणु
			dev_err_ratelimited(module->dev,
					    "unregister_cport failed:%d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(module->dev, "Dynamic Unregister %d DAI\n", cportid);
		data->state[SNDRV_PCM_STREAM_CAPTURE] = GBAUDIO_CODEC_SHUTDOWN;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gbaudio_module_update(काष्ठा gbaudio_codec_info *codec,
			  काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा gbaudio_module_info *module, पूर्णांक enable)
अणु
	पूर्णांक dai_id, ret;
	अक्षर पूर्णांकf_name[NAME_SIZE], dir[NAME_SIZE];

	dev_dbg(module->dev, "%s:Module update %s sequence\n", w->name,
		enable ? "Enable" : "Disable");

	अगर ((w->id != snd_soc_dapm_aअगर_in) && (w->id != snd_soc_dapm_aअगर_out)) अणु
		dev_dbg(codec->dev, "No action required for %s\n", w->name);
		वापस 0;
	पूर्ण

	/* parse dai_id from AIF widget's stream_name */
	ret = माला_पूछो(w->sname, "%s %d %s", पूर्णांकf_name, &dai_id, dir);
	अगर (ret < 3) अणु
		dev_err(codec->dev, "Error while parsing dai_id for %s\n", w->name);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&codec->lock);
	अगर (w->id == snd_soc_dapm_aअगर_in) अणु
		अगर (enable)
			ret = gbaudio_module_enable_tx(codec, module, dai_id);
		अन्यथा
			ret = gbaudio_module_disable_tx(module, dai_id);
	पूर्ण अन्यथा अगर (w->id == snd_soc_dapm_aअगर_out) अणु
		अगर (enable)
			ret = gbaudio_module_enable_rx(codec, module, dai_id);
		अन्यथा
			ret = gbaudio_module_disable_rx(module, dai_id);
	पूर्ण

	mutex_unlock(&codec->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(gbaudio_module_update);

/*
 * codec DAI ops
 */
अटल पूर्णांक gbcodec_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	काष्ठा gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	अगर (list_empty(&codec->module_list)) अणु
		dev_err(codec->dev, "No codec module available\n");
		mutex_unlock(&codec->lock);
		वापस -ENODEV;
	पूर्ण

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण
	params->state = GBAUDIO_CODEC_STARTUP;
	mutex_unlock(&codec->lock);
	/* to prevent suspend in हाल of active audio */
	pm_stay_awake(dai->dev);

	वापस 0;
पूर्ण

अटल व्योम gbcodec_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	काष्ठा gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	अगर (list_empty(&codec->module_list))
		dev_info(codec->dev, "No codec module available during shutdown\n");

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		वापस;
	पूर्ण
	params->state = GBAUDIO_CODEC_SHUTDOWN;
	mutex_unlock(&codec->lock);
	pm_relax(dai->dev);
पूर्ण

अटल पूर्णांक gbcodec_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hwparams,
			     काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;
	u8 sig_bits, channels;
	u32 क्रमmat, rate;
	काष्ठा gbaudio_module_info *module;
	काष्ठा gbaudio_data_connection *data;
	काष्ठा gb_bundle *bundle;
	काष्ठा gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	काष्ठा gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	अगर (list_empty(&codec->module_list)) अणु
		dev_err(codec->dev, "No codec module available\n");
		mutex_unlock(&codec->lock);
		वापस -ENODEV;
	पूर्ण

	/*
	 * assuming, currently only 48000 Hz, 16BIT_LE, stereo
	 * is supported, validate params beक्रमe configuring codec
	 */
	अगर (params_channels(hwparams) != 2) अणु
		dev_err(dai->dev, "Invalid channel count:%d\n",
			params_channels(hwparams));
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण
	channels = params_channels(hwparams);

	अगर (params_rate(hwparams) != 48000) अणु
		dev_err(dai->dev, "Invalid sampling rate:%d\n",
			params_rate(hwparams));
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण
	rate = GB_AUDIO_PCM_RATE_48000;

	अगर (params_क्रमmat(hwparams) != SNDRV_PCM_FORMAT_S16_LE) अणु
		dev_err(dai->dev, "Invalid format:%d\n", params_क्रमmat(hwparams));
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण
	क्रमmat = GB_AUDIO_PCM_FMT_S16_LE;

	/* find the data connection */
	list_क्रम_each_entry(module, &codec->module_list, list) अणु
		data = find_data(module, dai->id);
		अगर (data)
			अवरोध;
	पूर्ण

	अगर (!data) अणु
		dev_err(dai->dev, "DATA connection missing\n");
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण

	bundle = to_gb_bundle(module->dev);
	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret) अणु
		mutex_unlock(&codec->lock);
		वापस ret;
	पूर्ण

	ret = gb_audio_apbridgea_set_config(data->connection, 0,
					    AUDIO_APBRIDGEA_PCM_FMT_16,
					    AUDIO_APBRIDGEA_PCM_RATE_48000,
					    6144000);
	अगर (ret) अणु
		dev_err_ratelimited(dai->dev, "%d: Error during set_config\n",
				    ret);
		gb_pm_runसमय_put_noidle(bundle);
		mutex_unlock(&codec->lock);
		वापस ret;
	पूर्ण

	gb_pm_runसमय_put_noidle(bundle);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		sig_bits = dai->driver->playback.sig_bits;
	अन्यथा
		sig_bits = dai->driver->capture.sig_bits;

	params->state = GBAUDIO_CODEC_HWPARAMS;
	params->क्रमmat = क्रमmat;
	params->rate = rate;
	params->channels = channels;
	params->sig_bits = sig_bits;

	mutex_unlock(&codec->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;
	काष्ठा gbaudio_module_info *module;
	काष्ठा gbaudio_data_connection *data;
	काष्ठा gb_bundle *bundle;
	काष्ठा gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	काष्ठा gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	अगर (list_empty(&codec->module_list)) अणु
		dev_err(codec->dev, "No codec module available\n");
		mutex_unlock(&codec->lock);
		वापस -ENODEV;
	पूर्ण

	list_क्रम_each_entry(module, &codec->module_list, list) अणु
		/* find the dai */
		data = find_data(module, dai->id);
		अगर (data)
			अवरोध;
	पूर्ण
	अगर (!data) अणु
		dev_err(dai->dev, "DATA connection missing\n");
		mutex_unlock(&codec->lock);
		वापस -ENODEV;
	पूर्ण

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण

	bundle = to_gb_bundle(module->dev);
	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret) अणु
		mutex_unlock(&codec->lock);
		वापस ret;
	पूर्ण

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		ret = gb_audio_apbridgea_set_tx_data_size(data->connection, 0, 192);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		ret = gb_audio_apbridgea_set_rx_data_size(data->connection, 0, 192);
		अवरोध;
	पूर्ण
	अगर (ret) अणु
		gb_pm_runसमय_put_noidle(bundle);
		mutex_unlock(&codec->lock);
		dev_err_ratelimited(dai->dev, "set_data_size failed:%d\n", ret);
		वापस ret;
	पूर्ण

	gb_pm_runसमय_put_noidle(bundle);

	params->state = GBAUDIO_CODEC_PREPARE;
	mutex_unlock(&codec->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	पूर्णांक ret;
	काष्ठा gbaudio_data_connection *data;
	काष्ठा gbaudio_module_info *module;
	काष्ठा gb_bundle *bundle;
	काष्ठा gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	काष्ठा gbaudio_stream_params *params;

	dev_dbg(dai->dev, "Mute:%d, Direction:%s\n", mute,
		stream ? "CAPTURE" : "PLAYBACK");

	mutex_lock(&codec->lock);

	params = find_dai_stream_params(codec, dai->id, stream);
	अगर (!params) अणु
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(&codec->module_list)) अणु
		dev_err(codec->dev, "No codec module available\n");
		अगर (mute) अणु
			params->state = GBAUDIO_CODEC_STOP;
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = -ENODEV;
		पूर्ण
		mutex_unlock(&codec->lock);
		वापस ret;
	पूर्ण

	list_क्रम_each_entry(module, &codec->module_list, list) अणु
		/* find the dai */
		data = find_data(module, dai->id);
		अगर (data)
			अवरोध;
	पूर्ण
	अगर (!data) अणु
		dev_err(dai->dev, "%s:%s DATA connection missing\n",
			dai->name, module->name);
		mutex_unlock(&codec->lock);
		वापस -ENODEV;
	पूर्ण

	bundle = to_gb_bundle(module->dev);
	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret) अणु
		mutex_unlock(&codec->lock);
		वापस ret;
	पूर्ण

	अगर (!mute && !stream) अणु/* start playback */
		ret = gb_audio_apbridgea_prepare_tx(data->connection, 0);
		अगर (!ret)
			ret = gb_audio_apbridgea_start_tx(data->connection, 0, 0);
		params->state = GBAUDIO_CODEC_START;
	पूर्ण अन्यथा अगर (!mute && stream) अणु/* start capture */
		ret = gb_audio_apbridgea_prepare_rx(data->connection, 0);
		अगर (!ret)
			ret = gb_audio_apbridgea_start_rx(data->connection, 0);
		params->state = GBAUDIO_CODEC_START;
	पूर्ण अन्यथा अगर (mute && !stream) अणु/* stop playback */
		ret = gb_audio_apbridgea_stop_tx(data->connection, 0);
		अगर (!ret)
			ret = gb_audio_apbridgea_shutकरोwn_tx(data->connection, 0);
		params->state = GBAUDIO_CODEC_STOP;
	पूर्ण अन्यथा अगर (mute && stream) अणु/* stop capture */
		ret = gb_audio_apbridgea_stop_rx(data->connection, 0);
		अगर (!ret)
			ret = gb_audio_apbridgea_shutकरोwn_rx(data->connection, 0);
		params->state = GBAUDIO_CODEC_STOP;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		dev_err_ratelimited(dai->dev,
				    "%s:Error during %s %s stream:%d\n",
				    module->name, mute ? "Mute" : "Unmute",
				    stream ? "Capture" : "Playback", ret);

	gb_pm_runसमय_put_noidle(bundle);
	mutex_unlock(&codec->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops gbcodec_dai_ops = अणु
	.startup = gbcodec_startup,
	.shutकरोwn = gbcodec_shutकरोwn,
	.hw_params = gbcodec_hw_params,
	.prepare = gbcodec_prepare,
	.mute_stream = gbcodec_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver gbaudio_dai[] = अणु
	अणु
		.name = "apb-i2s0",
		.id = 0,
		.playback = अणु
			.stream_name = "I2S 0 Playback",
			.rates = SNDRV_PCM_RATE_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_max = 48000,
			.rate_min = 48000,
			.channels_min = 1,
			.channels_max = 2,
			.sig_bits = 16,
		पूर्ण,
		.capture = अणु
			.stream_name = "I2S 0 Capture",
			.rates = SNDRV_PCM_RATE_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_max = 48000,
			.rate_min = 48000,
			.channels_min = 1,
			.channels_max = 2,
			.sig_bits = 16,
		पूर्ण,
		.ops = &gbcodec_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक gbaudio_init_jack(काष्ठा gbaudio_module_info *module,
			     काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret;
	काष्ठा gbaudio_jack *jack, *n;
	काष्ठा snd_soc_jack_pin *headset, *button;

	अगर (!module->jack_mask)
		वापस 0;

	snम_लिखो(module->jack_name, NAME_SIZE, "GB %d Headset Jack",
		 module->dev_id);

	headset = devm_kzalloc(module->dev, माप(*headset), GFP_KERNEL);
	अगर (!headset)
		वापस -ENOMEM;

	headset->pin = module->jack_name;
	headset->mask = module->jack_mask;
	ret = snd_soc_card_jack_new(card, module->jack_name, module->jack_mask,
				    &module->headset.jack, headset, 1);
	अगर (ret) अणु
		dev_err(module->dev, "Failed to create new jack\n");
		वापस ret;
	पूर्ण

	/* Add to module's jack list */
	list_add(&module->headset.list, &module->jack_list);

	अगर (!module->button_mask)
		वापस 0;

	snम_लिखो(module->button_name, NAME_SIZE, "GB %d Button Jack",
		 module->dev_id);
	button = devm_kzalloc(module->dev, माप(*button), GFP_KERNEL);
	अगर (!button) अणु
		ret = -ENOMEM;
		जाओ मुक्त_jacks;
	पूर्ण

	button->pin = module->button_name;
	button->mask = module->button_mask;
	ret = snd_soc_card_jack_new(card, module->button_name,
				    module->button_mask, &module->button.jack,
				    button, 1);
	अगर (ret) अणु
		dev_err(module->dev, "Failed to create button jack\n");
		जाओ मुक्त_jacks;
	पूर्ण

	/* Add to module's jack list */
	list_add(&module->button.list, &module->jack_list);

	/*
	 * Currently, max 4 buttons are supported with following key mapping
	 * BTN_0 = KEY_MEDIA
	 * BTN_1 = KEY_VOICECOMMAND
	 * BTN_2 = KEY_VOLUMEUP
	 * BTN_3 = KEY_VOLUMEDOWN
	 */

	अगर (module->button_mask & SND_JACK_BTN_0) अणु
		ret = snd_jack_set_key(module->button.jack.jack, SND_JACK_BTN_0,
				       KEY_MEDIA);
		अगर (ret) अणु
			dev_err(module->dev, "Failed to set BTN_0\n");
			जाओ मुक्त_jacks;
		पूर्ण
	पूर्ण

	अगर (module->button_mask & SND_JACK_BTN_1) अणु
		ret = snd_jack_set_key(module->button.jack.jack, SND_JACK_BTN_1,
				       KEY_VOICECOMMAND);
		अगर (ret) अणु
			dev_err(module->dev, "Failed to set BTN_1\n");
			जाओ मुक्त_jacks;
		पूर्ण
	पूर्ण

	अगर (module->button_mask & SND_JACK_BTN_2) अणु
		ret = snd_jack_set_key(module->button.jack.jack, SND_JACK_BTN_2,
				       KEY_VOLUMEUP);
		अगर (ret) अणु
			dev_err(module->dev, "Failed to set BTN_2\n");
			जाओ मुक्त_jacks;
		पूर्ण
	पूर्ण

	अगर (module->button_mask & SND_JACK_BTN_3) अणु
		ret = snd_jack_set_key(module->button.jack.jack, SND_JACK_BTN_3,
				       KEY_VOLUMEDOWN);
		अगर (ret) अणु
			dev_err(module->dev, "Failed to set BTN_0\n");
			जाओ मुक्त_jacks;
		पूर्ण
	पूर्ण

	/* FIXME
	 * verअगरy अगर this is really required
	set_bit(INPUT_PROP_NO_DUMMY_RELEASE,
		module->button.jack.jack->input_dev->propbit);
	*/

	वापस 0;

मुक्त_jacks:
	list_क्रम_each_entry_safe(jack, n, &module->jack_list, list) अणु
		snd_device_मुक्त(card->snd_card, jack->jack.jack);
		list_del(&jack->list);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक gbaudio_रेजिस्टर_module(काष्ठा gbaudio_module_info *module)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_component *comp;
	काष्ठा snd_card *card;
	काष्ठा gbaudio_jack *jack = शून्य;

	अगर (!gbcodec) अणु
		dev_err(module->dev, "GB Codec not yet probed\n");
		वापस -EAGAIN;
	पूर्ण

	comp = gbcodec->component;
	card = comp->card->snd_card;

	करोwn_ग_लिखो(&card->controls_rwsem);

	अगर (module->num_dais) अणु
		dev_err(gbcodec->dev,
			"%d:DAIs not supported via gbcodec driver\n",
			module->num_dais);
		up_ग_लिखो(&card->controls_rwsem);
		वापस -EINVAL;
	पूर्ण

	ret = gbaudio_init_jack(module, comp->card);
	अगर (ret) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस ret;
	पूर्ण

	अगर (module->dapm_widमाला_लो)
		snd_soc_dapm_new_controls(&comp->dapm, module->dapm_widमाला_लो,
					  module->num_dapm_widमाला_लो);
	अगर (module->controls)
		snd_soc_add_component_controls(comp, module->controls,
					       module->num_controls);
	अगर (module->dapm_routes)
		snd_soc_dapm_add_routes(&comp->dapm, module->dapm_routes,
					module->num_dapm_routes);

	/* card alपढ़ोy instantiated, create widमाला_लो here only */
	अगर (comp->card->instantiated) अणु
		gbaudio_dapm_link_component_dai_widमाला_लो(comp->card, &comp->dapm);
#अगर_घोषित CONFIG_SND_JACK
		/*
		 * रेजिस्टर jack devices क्रम this module
		 * from codec->jack_list
		 */
		list_क्रम_each_entry(jack, &module->jack_list, list) अणु
			snd_device_रेजिस्टर(comp->card->snd_card,
					    jack->jack.jack);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	mutex_lock(&gbcodec->lock);
	list_add(&module->list, &gbcodec->module_list);
	mutex_unlock(&gbcodec->lock);

	अगर (comp->card->instantiated)
		ret = snd_soc_dapm_new_widमाला_लो(comp->card);
	dev_dbg(comp->dev, "Registered %s module\n", module->name);

	up_ग_लिखो(&card->controls_rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(gbaudio_रेजिस्टर_module);

अटल व्योम gbaudio_codec_clean_data_tx(काष्ठा gbaudio_data_connection *data)
अणु
	u16 i2s_port, cportid;
	पूर्णांक ret;

	अगर (list_is_singular(&gbcodec->module_list)) अणु
		ret = gb_audio_apbridgea_stop_tx(data->connection, 0);
		अगर (ret)
			वापस;
		ret = gb_audio_apbridgea_shutकरोwn_tx(data->connection, 0);
		अगर (ret)
			वापस;
	पूर्ण
	i2s_port = 0;	/* fixed क्रम now */
	cportid = data->connection->hd_cport_id;
	ret = gb_audio_apbridgea_unरेजिस्टर_cport(data->connection,
						  i2s_port, cportid,
						  AUDIO_APBRIDGEA_सूचीECTION_TX);
	data->state[0] = GBAUDIO_CODEC_SHUTDOWN;
पूर्ण

अटल व्योम gbaudio_codec_clean_data_rx(काष्ठा gbaudio_data_connection *data)
अणु
	u16 i2s_port, cportid;
	पूर्णांक ret;

	अगर (list_is_singular(&gbcodec->module_list)) अणु
		ret = gb_audio_apbridgea_stop_rx(data->connection, 0);
		अगर (ret)
			वापस;
		ret = gb_audio_apbridgea_shutकरोwn_rx(data->connection, 0);
		अगर (ret)
			वापस;
	पूर्ण
	i2s_port = 0;	/* fixed क्रम now */
	cportid = data->connection->hd_cport_id;
	ret = gb_audio_apbridgea_unरेजिस्टर_cport(data->connection,
						  i2s_port, cportid,
						  AUDIO_APBRIDGEA_सूचीECTION_RX);
	data->state[1] = GBAUDIO_CODEC_SHUTDOWN;
पूर्ण

अटल व्योम gbaudio_codec_cleanup(काष्ठा gbaudio_module_info *module)
अणु
	काष्ठा gbaudio_data_connection *data;
	पूर्णांक pb_state, cap_state;

	dev_dbg(gbcodec->dev, "%s: removed, cleanup APBridge\n", module->name);
	list_क्रम_each_entry(data, &module->data_list, list) अणु
		pb_state = data->state[0];
		cap_state = data->state[1];

		अगर (pb_state > GBAUDIO_CODEC_SHUTDOWN)
			gbaudio_codec_clean_data_tx(data);

		अगर (cap_state > GBAUDIO_CODEC_SHUTDOWN)
			gbaudio_codec_clean_data_rx(data);
	पूर्ण
पूर्ण

व्योम gbaudio_unरेजिस्टर_module(काष्ठा gbaudio_module_info *module)
अणु
	काष्ठा snd_soc_component *comp = gbcodec->component;
	काष्ठा snd_card *card = comp->card->snd_card;
	काष्ठा gbaudio_jack *jack, *n;
	पूर्णांक mask;

	dev_dbg(comp->dev, "Unregister %s module\n", module->name);

	करोwn_ग_लिखो(&card->controls_rwsem);
	mutex_lock(&gbcodec->lock);
	gbaudio_codec_cleanup(module);
	list_del(&module->list);
	dev_dbg(comp->dev, "Process Unregister %s module\n", module->name);
	mutex_unlock(&gbcodec->lock);

#अगर_घोषित CONFIG_SND_JACK
	/* मुक्त jack devices क्रम this module jack_list */
	list_क्रम_each_entry_safe(jack, n, &module->jack_list, list) अणु
		अगर (jack == &module->headset)
			mask = GBCODEC_JACK_MASK;
		अन्यथा अगर (jack == &module->button)
			mask = GBCODEC_JACK_BUTTON_MASK;
		अन्यथा
			mask = 0;
		अगर (mask) अणु
			dev_dbg(module->dev, "Report %s removal\n",
				jack->jack.jack->id);
			snd_soc_jack_report(&jack->jack, 0, mask);
			snd_device_मुक्त(comp->card->snd_card,
					jack->jack.jack);
			list_del(&jack->list);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (module->dapm_routes) अणु
		dev_dbg(comp->dev, "Removing %d routes\n",
			module->num_dapm_routes);
		snd_soc_dapm_del_routes(&comp->dapm, module->dapm_routes,
					module->num_dapm_routes);
	पूर्ण
	अगर (module->controls) अणु
		dev_dbg(comp->dev, "Removing %d controls\n",
			module->num_controls);
		/* release control semaphore */
		up_ग_लिखो(&card->controls_rwsem);
		gbaudio_हटाओ_component_controls(comp, module->controls,
						  module->num_controls);
		करोwn_ग_लिखो(&card->controls_rwsem);
	पूर्ण
	अगर (module->dapm_widमाला_लो) अणु
		dev_dbg(comp->dev, "Removing %d widgets\n",
			module->num_dapm_widमाला_लो);
		gbaudio_dapm_मुक्त_controls(&comp->dapm, module->dapm_widमाला_लो,
					   module->num_dapm_widमाला_लो);
	पूर्ण

	dev_dbg(comp->dev, "Unregistered %s module\n", module->name);

	up_ग_लिखो(&card->controls_rwsem);
पूर्ण
EXPORT_SYMBOL(gbaudio_unरेजिस्टर_module);

/*
 * component driver ops
 */
अटल पूर्णांक gbcodec_probe(काष्ठा snd_soc_component *comp)
अणु
	पूर्णांक i;
	काष्ठा gbaudio_codec_info *info;
	काष्ठा gbaudio_codec_dai *dai;

	info = devm_kzalloc(comp->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = comp->dev;
	INIT_LIST_HEAD(&info->module_list);
	mutex_init(&info->lock);
	INIT_LIST_HEAD(&info->dai_list);

	/* init dai_list used to मुख्यtain runसमय stream info */
	क्रम (i = 0; i < ARRAY_SIZE(gbaudio_dai); i++) अणु
		dai = devm_kzalloc(comp->dev, माप(*dai), GFP_KERNEL);
		अगर (!dai)
			वापस -ENOMEM;
		dai->id = gbaudio_dai[i].id;
		list_add(&dai->list, &info->dai_list);
	पूर्ण

	info->component = comp;
	snd_soc_component_set_drvdata(comp, info);
	gbcodec = info;

	device_init_wakeup(comp->dev, 1);
	वापस 0;
पूर्ण

अटल व्योम gbcodec_हटाओ(काष्ठा snd_soc_component *comp)
अणु
	/* Empty function क्रम now */
	वापस;
पूर्ण

अटल पूर्णांक gbcodec_ग_लिखो(काष्ठा snd_soc_component *comp, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक value)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक gbcodec_पढ़ो(काष्ठा snd_soc_component *comp,
				 अचिन्हित पूर्णांक reg)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_gbaudio = अणु
	.probe	= gbcodec_probe,
	.हटाओ	= gbcodec_हटाओ,

	.पढ़ो = gbcodec_पढ़ो,
	.ग_लिखो = gbcodec_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gbaudio_codec_suspend(काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s: suspend\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_codec_resume(काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s: resume\n", __func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gbaudio_codec_pm_ops = अणु
	.suspend	= gbaudio_codec_suspend,
	.resume		= gbaudio_codec_resume,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक gbaudio_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_codec_dev_gbaudio,
			gbaudio_dai, ARRAY_SIZE(gbaudio_dai));
पूर्ण

अटल पूर्णांक gbaudio_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id greybus_asoc_machine_of_match[]  = अणु
	अणु .compatible = "toshiba,apb-dummy-codec", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gbaudio_codec_driver = अणु
	.driver = अणु
		.name = "apb-dummy-codec",
#अगर_घोषित CONFIG_PM
		.pm = &gbaudio_codec_pm_ops,
#पूर्ण_अगर
		.of_match_table = greybus_asoc_machine_of_match,
	पूर्ण,
	.probe = gbaudio_codec_probe,
	.हटाओ = gbaudio_codec_हटाओ,
पूर्ण;
module_platक्रमm_driver(gbaudio_codec_driver);

MODULE_DESCRIPTION("APBridge ALSA SoC dummy codec driver");
MODULE_AUTHOR("Vaibhav Agarwal <vaibhav.agarwal@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:apb-dummy-codec");
