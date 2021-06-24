<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <uapi/linux/input-event-codes.h>
#समावेश "common.h"
#समावेश "qdsp6/q6afe.h"
#समावेश "../codecs/rt5663.h"

#घोषणा DRIVER_NAME	"sdm845"
#घोषणा DEFAULT_SAMPLE_RATE_48K		48000
#घोषणा DEFAULT_MCLK_RATE		24576000
#घोषणा TDM_BCLK_RATE		6144000
#घोषणा MI2S_BCLK_RATE		1536000
#घोषणा LEFT_SPK_TDM_TX_MASK    0x30
#घोषणा RIGHT_SPK_TDM_TX_MASK   0xC0
#घोषणा SPK_TDM_RX_MASK         0x03
#घोषणा NUM_TDM_SLOTS           8
#घोषणा SLIM_MAX_TX_PORTS 16
#घोषणा SLIM_MAX_RX_PORTS 13
#घोषणा WCD934X_DEFAULT_MCLK_RATE	9600000

काष्ठा sdm845_snd_data अणु
	काष्ठा snd_soc_jack jack;
	bool jack_setup;
	bool stream_prepared[AFE_PORT_MAX];
	काष्ठा snd_soc_card *card;
	uपूर्णांक32_t pri_mi2s_clk_count;
	uपूर्णांक32_t sec_mi2s_clk_count;
	uपूर्णांक32_t quat_tdm_clk_count;
	काष्ठा sdw_stream_runसमय *srunसमय[AFE_PORT_MAX];
पूर्ण;

अटल अचिन्हित पूर्णांक tdm_slot_offset[8] = अणु0, 4, 8, 12, 16, 20, 24, 28पूर्ण;

अटल पूर्णांक sdm845_slim_snd_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा sdm845_snd_data *pdata = snd_soc_card_get_drvdata(rtd->card);
	u32 rx_ch[SLIM_MAX_RX_PORTS], tx_ch[SLIM_MAX_TX_PORTS];
	काष्ठा sdw_stream_runसमय *srunसमय;
	u32 rx_ch_cnt = 0, tx_ch_cnt = 0;
	पूर्णांक ret = 0, i;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		srunसमय = snd_soc_dai_get_sdw_stream(codec_dai,
						      substream->stream);
		अगर (srunसमय != ERR_PTR(-ENOTSUPP))
			pdata->srunसमय[cpu_dai->id] = srunसमय;

		ret = snd_soc_dai_get_channel_map(codec_dai,
				&tx_ch_cnt, tx_ch, &rx_ch_cnt, rx_ch);

		अगर (ret != 0 && ret != -ENOTSUPP) अणु
			pr_err("failed to get codec chan map, err:%d\n", ret);
			वापस ret;
		पूर्ण अन्यथा अगर (ret == -ENOTSUPP) अणु
			/* Ignore unsupported */
			जारी;
		पूर्ण

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = snd_soc_dai_set_channel_map(cpu_dai, 0, शून्य,
							  rx_ch_cnt, rx_ch);
		अन्यथा
			ret = snd_soc_dai_set_channel_map(cpu_dai, tx_ch_cnt,
							  tx_ch, 0, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdm845_tdm_snd_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret = 0, j;
	पूर्णांक channels, slot_width;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		slot_width = 16;
		अवरोध;
	शेष:
		dev_err(rtd->dev, "%s: invalid param format 0x%x\n",
				__func__, params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	channels = params_channels(params);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0, 0x3,
				8, slot_width);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "%s: failed to set tdm slot, err:%d\n",
					__func__, ret);
			जाओ end;
		पूर्ण

		ret = snd_soc_dai_set_channel_map(cpu_dai, 0, शून्य,
				channels, tdm_slot_offset);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "%s: failed to set channel map, err:%d\n",
					__func__, ret);
			जाओ end;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0xf, 0,
				8, slot_width);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "%s: failed to set tdm slot, err:%d\n",
					__func__, ret);
			जाओ end;
		पूर्ण

		ret = snd_soc_dai_set_channel_map(cpu_dai, channels,
				tdm_slot_offset, 0, शून्य);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "%s: failed to set channel map, err:%d\n",
					__func__, ret);
			जाओ end;
		पूर्ण
	पूर्ण

	क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु

		अगर (!म_भेद(codec_dai->component->name_prefix, "Left")) अणु
			ret = snd_soc_dai_set_tdm_slot(
					codec_dai, LEFT_SPK_TDM_TX_MASK,
					SPK_TDM_RX_MASK, NUM_TDM_SLOTS,
					slot_width);
			अगर (ret < 0) अणु
				dev_err(rtd->dev,
					"DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (!म_भेद(codec_dai->component->name_prefix, "Right")) अणु
			ret = snd_soc_dai_set_tdm_slot(
					codec_dai, RIGHT_SPK_TDM_TX_MASK,
					SPK_TDM_RX_MASK, NUM_TDM_SLOTS,
					slot_width);
			अगर (ret < 0) अणु
				dev_err(rtd->dev,
					"DEV1 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

end:
	वापस ret;
पूर्ण

अटल पूर्णांक sdm845_snd_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret = 0;

	चयन (cpu_dai->id) अणु
	हाल PRIMARY_MI2S_RX:
	हाल PRIMARY_MI2S_TX:
		/*
		 * Use ASRC क्रम पूर्णांकernal घड़ीs, as PLL rate isn't multiple
		 * of BCLK.
		 */
		rt5663_sel_asrc_clk_src(
			codec_dai->component,
			RT5663_DA_STEREO_FILTER | RT5663_AD_STEREO_FILTER,
			RT5663_CLK_SEL_I2S1_ASRC);
		ret = snd_soc_dai_set_sysclk(
			codec_dai, RT5663_SCLK_S_MCLK, DEFAULT_MCLK_RATE,
			SND_SOC_CLOCK_IN);
		अगर (ret < 0)
			dev_err(rtd->dev,
				"snd_soc_dai_set_sysclk err = %d\n", ret);
		अवरोध;
	हाल QUATERNARY_TDM_RX_0:
	हाल QUATERNARY_TDM_TX_0:
		ret = sdm845_tdm_snd_hw_params(substream, params);
		अवरोध;
	हाल SLIMBUS_0_RX...SLIMBUS_6_TX:
		ret = sdm845_slim_snd_hw_params(substream, params);
		अवरोध;
	हाल QUATERNARY_MI2S_RX:
		अवरोध;
	शेष:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम sdm845_jack_मुक्त(काष्ठा snd_jack *jack)
अणु
	काष्ठा snd_soc_component *component = jack->निजी_data;

	snd_soc_component_set_jack(component, शून्य, शून्य);
पूर्ण

अटल पूर्णांक sdm845_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sdm845_snd_data *pdata = snd_soc_card_get_drvdata(card);
	काष्ठा snd_jack *jack;
	/*
	 * Codec SLIMBUS configuration
	 * RX1, RX2, RX3, RX4, RX5, RX6, RX7, RX8, RX9, RX10, RX11, RX12, RX13
	 * TX1, TX2, TX3, TX4, TX5, TX6, TX7, TX8, TX9, TX10, TX11, TX12, TX13
	 * TX14, TX15, TX16
	 */
	अचिन्हित पूर्णांक rx_ch[SLIM_MAX_RX_PORTS] = अणु144, 145, 146, 147, 148, 149,
					150, 151, 152, 153, 154, 155, 156पूर्ण;
	अचिन्हित पूर्णांक tx_ch[SLIM_MAX_TX_PORTS] = अणु128, 129, 130, 131, 132, 133,
					    134, 135, 136, 137, 138, 139,
					    140, 141, 142, 143पूर्ण;
	पूर्णांक rval, i;


	अगर (!pdata->jack_setup) अणु
		rval = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADSET |
				SND_JACK_HEADPHONE |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&pdata->jack, शून्य, 0);

		अगर (rval < 0) अणु
			dev_err(card->dev, "Unable to add Headphone Jack\n");
			वापस rval;
		पूर्ण

		jack = pdata->jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
		pdata->jack_setup = true;
	पूर्ण

	चयन (cpu_dai->id) अणु
	हाल PRIMARY_MI2S_RX:
		jack  = pdata->jack.jack;
		component = codec_dai->component;

		jack->निजी_data = component;
		jack->निजी_मुक्त = sdm845_jack_मुक्त;
		rval = snd_soc_component_set_jack(component,
						  &pdata->jack, शून्य);
		अगर (rval != 0 && rval != -ENOTSUPP) अणु
			dev_warn(card->dev, "Failed to set jack: %d\n", rval);
			वापस rval;
		पूर्ण
		अवरोध;
	हाल SLIMBUS_0_RX...SLIMBUS_6_TX:
		क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
			rval = snd_soc_dai_set_channel_map(codec_dai,
							  ARRAY_SIZE(tx_ch),
							  tx_ch,
							  ARRAY_SIZE(rx_ch),
							  rx_ch);
			अगर (rval != 0 && rval != -ENOTSUPP)
				वापस rval;

			snd_soc_dai_set_sysclk(codec_dai, 0,
					       WCD934X_DEFAULT_MCLK_RATE,
					       SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक sdm845_snd_startup(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक fmt = SND_SOC_DAIFMT_CBS_CFS;
	अचिन्हित पूर्णांक codec_dai_fmt = SND_SOC_DAIFMT_CBS_CFS;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sdm845_snd_data *data = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक j;
	पूर्णांक ret;

	चयन (cpu_dai->id) अणु
	हाल PRIMARY_MI2S_RX:
	हाल PRIMARY_MI2S_TX:
		codec_dai_fmt |= SND_SOC_DAIFMT_NB_NF;
		अगर (++(data->pri_mi2s_clk_count) == 1) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_MCLK_1,
				DEFAULT_MCLK_RATE, SNDRV_PCM_STREAM_PLAYBACK);
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_PRI_MI2S_IBIT,
				MI2S_BCLK_RATE, SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण
		snd_soc_dai_set_fmt(cpu_dai, fmt);
		snd_soc_dai_set_fmt(codec_dai, codec_dai_fmt);
		अवरोध;

	हाल SECONDARY_MI2S_TX:
		codec_dai_fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_I2S;
		अगर (++(data->sec_mi2s_clk_count) == 1) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_SEC_MI2S_IBIT,
				MI2S_BCLK_RATE,	SNDRV_PCM_STREAM_CAPTURE);
		पूर्ण
		snd_soc_dai_set_fmt(cpu_dai, fmt);
		snd_soc_dai_set_fmt(codec_dai, codec_dai_fmt);
		अवरोध;
	हाल QUATERNARY_MI2S_RX:
		snd_soc_dai_set_sysclk(cpu_dai,
			Q6AFE_LPASS_CLK_ID_QUAD_MI2S_IBIT,
			MI2S_BCLK_RATE, SNDRV_PCM_STREAM_PLAYBACK);
		snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_CBS_CFS);


		अवरोध;

	हाल QUATERNARY_TDM_RX_0:
	हाल QUATERNARY_TDM_TX_0:
		अगर (++(data->quat_tdm_clk_count) == 1) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_QUAD_TDM_IBIT,
				TDM_BCLK_RATE, SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण

		codec_dai_fmt |= SND_SOC_DAIFMT_IB_NF | SND_SOC_DAIFMT_DSP_B;

		क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु

			अगर (!म_भेद(codec_dai->component->name_prefix,
				    "Left")) अणु
				ret = snd_soc_dai_set_fmt(
						codec_dai, codec_dai_fmt);
				अगर (ret < 0) अणु
					dev_err(rtd->dev,
						"Left TDM fmt err:%d\n", ret);
					वापस ret;
				पूर्ण
			पूर्ण

			अगर (!म_भेद(codec_dai->component->name_prefix,
				    "Right")) अणु
				ret = snd_soc_dai_set_fmt(
						codec_dai, codec_dai_fmt);
				अगर (ret < 0) अणु
					dev_err(rtd->dev,
						"Right TDM slot err:%d\n", ret);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SLIMBUS_0_RX...SLIMBUS_6_TX:
		अवरोध;

	शेष:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम  sdm845_snd_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sdm845_snd_data *data = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल PRIMARY_MI2S_RX:
	हाल PRIMARY_MI2S_TX:
		अगर (--(data->pri_mi2s_clk_count) == 0) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_MCLK_1,
				0, SNDRV_PCM_STREAM_PLAYBACK);
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_PRI_MI2S_IBIT,
				0, SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण
		अवरोध;

	हाल SECONDARY_MI2S_TX:
		अगर (--(data->sec_mi2s_clk_count) == 0) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_SEC_MI2S_IBIT,
				0, SNDRV_PCM_STREAM_CAPTURE);
		पूर्ण
		अवरोध;

	हाल QUATERNARY_TDM_RX_0:
	हाल QUATERNARY_TDM_TX_0:
		अगर (--(data->quat_tdm_clk_count) == 0) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
				Q6AFE_LPASS_CLK_ID_QUAD_TDM_IBIT,
				0, SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण
		अवरोध;
	हाल SLIMBUS_0_RX...SLIMBUS_6_TX:
	हाल QUATERNARY_MI2S_RX:
		अवरोध;

	शेष:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sdm845_snd_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sdm845_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sdw_stream_runसमय *srunसमय = data->srunसमय[cpu_dai->id];
	पूर्णांक ret;

	अगर (!srunसमय)
		वापस 0;

	अगर (data->stream_prepared[cpu_dai->id]) अणु
		sdw_disable_stream(srunसमय);
		sdw_deprepare_stream(srunसमय);
		data->stream_prepared[cpu_dai->id] = false;
	पूर्ण

	ret = sdw_prepare_stream(srunसमय);
	अगर (ret)
		वापस ret;

	/**
	 * NOTE: there is a strict hw requirement about the ordering of port
	 * enables and actual WSA881x PA enable. PA enable should only happen
	 * after soundwire ports are enabled अगर not DC on the line is
	 * accumulated resulting in Click/Pop Noise
	 * PA enable/mute are handled as part of codec DAPM and digital mute.
	 */

	ret = sdw_enable_stream(srunसमय);
	अगर (ret) अणु
		sdw_deprepare_stream(srunसमय);
		वापस ret;
	पूर्ण
	data->stream_prepared[cpu_dai->id] = true;

	वापस ret;
पूर्ण

अटल पूर्णांक sdm845_snd_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sdm845_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sdw_stream_runसमय *srunसमय = data->srunसमय[cpu_dai->id];

	अगर (srunसमय && data->stream_prepared[cpu_dai->id]) अणु
		sdw_disable_stream(srunसमय);
		sdw_deprepare_stream(srunसमय);
		data->stream_prepared[cpu_dai->id] = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops sdm845_be_ops = अणु
	.hw_params = sdm845_snd_hw_params,
	.hw_मुक्त = sdm845_snd_hw_मुक्त,
	.prepare = sdm845_snd_prepare,
	.startup = sdm845_snd_startup,
	.shutकरोwn = sdm845_snd_shutकरोwn,
पूर्ण;

अटल पूर्णांक sdm845_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	rate->min = rate->max = DEFAULT_SAMPLE_RATE_48K;
	channels->min = channels->max = 2;
	snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S16_LE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget sdm845_snd_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
पूर्ण;

अटल व्योम sdm845_add_ops(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक i;

	क्रम_each_card_prelinks(card, i, link) अणु
		अगर (link->no_pcm == 1) अणु
			link->ops = &sdm845_be_ops;
			link->be_hw_params_fixup = sdm845_be_hw_params_fixup;
		पूर्ण
		link->init = sdm845_dai_init;
	पूर्ण
पूर्ण

अटल पूर्णांक sdm845_snd_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा sdm845_snd_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	/* Allocate the निजी data */
	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	card->driver_name = DRIVER_NAME;
	card->dapm_widमाला_लो = sdm845_snd_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(sdm845_snd_widमाला_लो);
	card->dev = dev;
	card->owner = THIS_MODULE;
	dev_set_drvdata(dev, card);
	ret = qcom_snd_parse_of(card);
	अगर (ret)
		वापस ret;

	data->card = card;
	snd_soc_card_set_drvdata(card, data);

	sdm845_add_ops(card);
	वापस devm_snd_soc_रेजिस्टर_card(dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id sdm845_snd_device_id[]  = अणु
	अणु .compatible = "qcom,sdm845-sndcard" पूर्ण,
	अणु .compatible = "qcom,db845c-sndcard" पूर्ण,
	अणु .compatible = "lenovo,yoga-c630-sndcard" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdm845_snd_device_id);

अटल काष्ठा platक्रमm_driver sdm845_snd_driver = अणु
	.probe = sdm845_snd_platक्रमm_probe,
	.driver = अणु
		.name = "msm-snd-sdm845",
		.of_match_table = sdm845_snd_device_id,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sdm845_snd_driver);

MODULE_DESCRIPTION("sdm845 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
