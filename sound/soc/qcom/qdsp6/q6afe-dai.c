<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश "q6afe.h"

#घोषणा Q6AFE_TDM_PB_DAI(pre, num, did) अणु				\
		.playback = अणु						\
			.stream_name = pre" TDM"#num" Playback",	\
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
				SNDRV_PCM_RATE_176400,			\
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |		\
				   SNDRV_PCM_FMTBIT_S24_LE |		\
				   SNDRV_PCM_FMTBIT_S32_LE,		\
			.channels_min = 1,				\
			.channels_max = 8,				\
			.rate_min = 8000,				\
			.rate_max = 176400,				\
		पूर्ण,							\
		.name = #did,						\
		.ops = &q6tdm_ops,					\
		.id = did,						\
		.probe = msm_dai_q6_dai_probe,				\
		.हटाओ = msm_dai_q6_dai_हटाओ,			\
	पूर्ण

#घोषणा Q6AFE_TDM_CAP_DAI(pre, num, did) अणु				\
		.capture = अणु						\
			.stream_name = pre" TDM"#num" Capture",		\
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
				SNDRV_PCM_RATE_176400,			\
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |		\
				   SNDRV_PCM_FMTBIT_S24_LE |		\
				   SNDRV_PCM_FMTBIT_S32_LE,		\
			.channels_min = 1,				\
			.channels_max = 8,				\
			.rate_min = 8000,				\
			.rate_max = 176400,				\
		पूर्ण,							\
		.name = #did,						\
		.ops = &q6tdm_ops,					\
		.id = did,						\
		.probe = msm_dai_q6_dai_probe,				\
		.हटाओ = msm_dai_q6_dai_हटाओ,			\
	पूर्ण

#घोषणा Q6AFE_CDC_DMA_RX_DAI(did) अणु				\
		.playback = अणु						\
			.stream_name = #did" Playback",	\
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
				SNDRV_PCM_RATE_176400,			\
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |		\
				   SNDRV_PCM_FMTBIT_S24_LE |		\
				   SNDRV_PCM_FMTBIT_S32_LE,		\
			.channels_min = 1,				\
			.channels_max = 8,				\
			.rate_min = 8000,				\
			.rate_max = 176400,				\
		पूर्ण,							\
		.name = #did,						\
		.ops = &q6dma_ops,					\
		.id = did,						\
		.probe = msm_dai_q6_dai_probe,				\
		.हटाओ = msm_dai_q6_dai_हटाओ,			\
	पूर्ण

#घोषणा Q6AFE_CDC_DMA_TX_DAI(did) अणु				\
		.capture = अणु						\
			.stream_name = #did" Capture",		\
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
				SNDRV_PCM_RATE_176400,			\
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |		\
				   SNDRV_PCM_FMTBIT_S24_LE |		\
				   SNDRV_PCM_FMTBIT_S32_LE,		\
			.channels_min = 1,				\
			.channels_max = 8,				\
			.rate_min = 8000,				\
			.rate_max = 176400,				\
		पूर्ण,							\
		.name = #did,						\
		.ops = &q6dma_ops,					\
		.id = did,						\
		.probe = msm_dai_q6_dai_probe,				\
		.हटाओ = msm_dai_q6_dai_हटाओ,			\
	पूर्ण

काष्ठा q6afe_dai_priv_data अणु
	uपूर्णांक32_t sd_line_mask;
	uपूर्णांक32_t sync_mode;
	uपूर्णांक32_t sync_src;
	uपूर्णांक32_t data_out_enable;
	uपूर्णांक32_t invert_sync;
	uपूर्णांक32_t data_delay;
	uपूर्णांक32_t data_align;
पूर्ण;

काष्ठा q6afe_dai_data अणु
	काष्ठा q6afe_port *port[AFE_PORT_MAX];
	काष्ठा q6afe_port_config port_config[AFE_PORT_MAX];
	bool is_port_started[AFE_PORT_MAX];
	काष्ठा q6afe_dai_priv_data priv[AFE_PORT_MAX];
पूर्ण;

अटल पूर्णांक q6slim_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु

	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_slim_cfg *slim = &dai_data->port_config[dai->id].slim;

	slim->sample_rate = params_rate(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
	हाल SNDRV_PCM_FORMAT_SPECIAL:
		slim->bit_width = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		slim->bit_width = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		slim->bit_width = 32;
		अवरोध;
	शेष:
		pr_err("%s: format %d\n",
			__func__, params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6hdmi_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	पूर्णांक channels = params_channels(params);
	काष्ठा q6afe_hdmi_cfg *hdmi = &dai_data->port_config[dai->id].hdmi;

	hdmi->sample_rate = params_rate(params);
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		hdmi->bit_width = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		hdmi->bit_width = 24;
		अवरोध;
	पूर्ण

	/* HDMI spec CEA-861-E: Table 28 Audio InfoFrame Data Byte 4 */
	चयन (channels) अणु
	हाल 2:
		hdmi->channel_allocation = 0;
		अवरोध;
	हाल 3:
		hdmi->channel_allocation = 0x02;
		अवरोध;
	हाल 4:
		hdmi->channel_allocation = 0x06;
		अवरोध;
	हाल 5:
		hdmi->channel_allocation = 0x0A;
		अवरोध;
	हाल 6:
		hdmi->channel_allocation = 0x0B;
		अवरोध;
	हाल 7:
		hdmi->channel_allocation = 0x12;
		अवरोध;
	हाल 8:
		hdmi->channel_allocation = 0x13;
		अवरोध;
	शेष:
		dev_err(dai->dev, "invalid Channels = %u\n", channels);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_i2s_cfg *i2s = &dai_data->port_config[dai->id].i2s_cfg;

	i2s->sample_rate = params_rate(params);
	i2s->bit_width = params_width(params);
	i2s->num_channels = params_channels(params);
	i2s->sd_line_mask = dai_data->priv[dai->id].sd_line_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक q6i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_i2s_cfg *i2s = &dai_data->port_config[dai->id].i2s_cfg;

	i2s->fmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक q6tdm_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask,
				पूर्णांक slots, पूर्णांक slot_width)
अणु

	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_tdm_cfg *tdm = &dai_data->port_config[dai->id].tdm;
	अचिन्हित पूर्णांक cap_mask;
	पूर्णांक rc = 0;

	/* HW only supports 16 and 32 bit slot width configuration */
	अगर ((slot_width != 16) && (slot_width != 32)) अणु
		dev_err(dai->dev, "%s: invalid slot_width %d\n",
			__func__, slot_width);
		वापस -EINVAL;
	पूर्ण

	/* HW supports 1-32 slots configuration. Typical: 1, 2, 4, 8, 16, 32 */
	चयन (slots) अणु
	हाल 2:
		cap_mask = 0x03;
		अवरोध;
	हाल 4:
		cap_mask = 0x0F;
		अवरोध;
	हाल 8:
		cap_mask = 0xFF;
		अवरोध;
	हाल 16:
		cap_mask = 0xFFFF;
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: invalid slots %d\n",
			__func__, slots);
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल PRIMARY_TDM_RX_0 ... QUINARY_TDM_TX_7:
		tdm->nslots_per_frame = slots;
		tdm->slot_width = slot_width;
		/* TDM RX dais ids are even and tx are odd */
		tdm->slot_mask = ((dai->id & 0x1) ? tx_mask : rx_mask) & cap_mask;
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: invalid dai id 0x%x\n",
			__func__, dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक q6tdm_set_channel_map(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु

	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_tdm_cfg *tdm = &dai_data->port_config[dai->id].tdm;
	पूर्णांक rc = 0;
	पूर्णांक i = 0;

	चयन (dai->id) अणु
	हाल PRIMARY_TDM_RX_0 ... QUINARY_TDM_TX_7:
		अगर (dai->id & 0x1) अणु
			अगर (!tx_slot) अणु
				dev_err(dai->dev, "tx slot not found\n");
				वापस -EINVAL;
			पूर्ण
			अगर (tx_num > AFE_PORT_MAX_AUDIO_CHAN_CNT) अणु
				dev_err(dai->dev, "invalid tx num %d\n",
					tx_num);
				वापस -EINVAL;
			पूर्ण

			क्रम (i = 0; i < tx_num; i++)
				tdm->ch_mapping[i] = tx_slot[i];

			क्रम (i = tx_num; i < AFE_PORT_MAX_AUDIO_CHAN_CNT; i++)
				tdm->ch_mapping[i] = Q6AFE_CMAP_INVALID;

			tdm->num_channels = tx_num;
		पूर्ण अन्यथा अणु
			/* rx */
			अगर (!rx_slot) अणु
				dev_err(dai->dev, "rx slot not found\n");
				वापस -EINVAL;
			पूर्ण
			अगर (rx_num > AFE_PORT_MAX_AUDIO_CHAN_CNT) अणु
				dev_err(dai->dev, "invalid rx num %d\n",
					rx_num);
				वापस -EINVAL;
			पूर्ण

			क्रम (i = 0; i < rx_num; i++)
				tdm->ch_mapping[i] = rx_slot[i];

			क्रम (i = rx_num; i < AFE_PORT_MAX_AUDIO_CHAN_CNT; i++)
				tdm->ch_mapping[i] = Q6AFE_CMAP_INVALID;

			tdm->num_channels = rx_num;
		पूर्ण

		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: invalid dai id 0x%x\n",
			__func__, dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक q6tdm_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_tdm_cfg *tdm = &dai_data->port_config[dai->id].tdm;

	tdm->bit_width = params_width(params);
	tdm->sample_rate = params_rate(params);
	tdm->num_channels = params_channels(params);
	tdm->data_align_type = dai_data->priv[dai->id].data_align;
	tdm->sync_src = dai_data->priv[dai->id].sync_src;
	tdm->sync_mode = dai_data->priv[dai->id].sync_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक q6dma_set_channel_map(काष्ठा snd_soc_dai *dai,
				 अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_ch_mask,
				 अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_ch_mask)
अणु

	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_cdc_dma_cfg *cfg = &dai_data->port_config[dai->id].dma_cfg;
	पूर्णांक ch_mask;
	पूर्णांक rc = 0;

	चयन (dai->id) अणु
	हाल WSA_CODEC_DMA_TX_0:
	हाल WSA_CODEC_DMA_TX_1:
	हाल WSA_CODEC_DMA_TX_2:
	हाल VA_CODEC_DMA_TX_0:
	हाल VA_CODEC_DMA_TX_1:
	हाल VA_CODEC_DMA_TX_2:
	हाल TX_CODEC_DMA_TX_0:
	हाल TX_CODEC_DMA_TX_1:
	हाल TX_CODEC_DMA_TX_2:
	हाल TX_CODEC_DMA_TX_3:
	हाल TX_CODEC_DMA_TX_4:
	हाल TX_CODEC_DMA_TX_5:
		अगर (!tx_ch_mask) अणु
			dev_err(dai->dev, "tx slot not found\n");
			वापस -EINVAL;
		पूर्ण

		अगर (tx_num > AFE_PORT_MAX_AUDIO_CHAN_CNT) अणु
			dev_err(dai->dev, "invalid tx num %d\n",
				tx_num);
			वापस -EINVAL;
		पूर्ण
		ch_mask = *tx_ch_mask;

		अवरोध;
	हाल WSA_CODEC_DMA_RX_0:
	हाल WSA_CODEC_DMA_RX_1:
	हाल RX_CODEC_DMA_RX_0:
	हाल RX_CODEC_DMA_RX_1:
	हाल RX_CODEC_DMA_RX_2:
	हाल RX_CODEC_DMA_RX_3:
	हाल RX_CODEC_DMA_RX_4:
	हाल RX_CODEC_DMA_RX_5:
	हाल RX_CODEC_DMA_RX_6:
	हाल RX_CODEC_DMA_RX_7:
		/* rx */
		अगर (!rx_ch_mask) अणु
			dev_err(dai->dev, "rx slot not found\n");
			वापस -EINVAL;
		पूर्ण
		अगर (rx_num > AFE_PORT_MAX_AUDIO_CHAN_CNT) अणु
			dev_err(dai->dev, "invalid rx num %d\n",
				rx_num);
			वापस -EINVAL;
		पूर्ण
		ch_mask = *rx_ch_mask;

		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: invalid dai id 0x%x\n",
			__func__, dai->id);
		वापस -EINVAL;
	पूर्ण

	cfg->active_channels_mask = ch_mask;

	वापस rc;
पूर्ण

अटल पूर्णांक q6dma_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_cdc_dma_cfg *cfg = &dai_data->port_config[dai->id].dma_cfg;

	cfg->bit_width = params_width(params);
	cfg->sample_rate = params_rate(params);
	cfg->num_channels = params_channels(params);

	वापस 0;
पूर्ण
अटल व्योम q6afe_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	पूर्णांक rc;

	अगर (!dai_data->is_port_started[dai->id])
		वापस;

	rc = q6afe_port_stop(dai_data->port[dai->id]);
	अगर (rc < 0)
		dev_err(dai->dev, "fail to close AFE port (%d)\n", rc);

	dai_data->is_port_started[dai->id] = false;

पूर्ण

अटल पूर्णांक q6afe_dai_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	पूर्णांक rc;

	अगर (dai_data->is_port_started[dai->id]) अणु
		/* stop the port and restart with new port config */
		rc = q6afe_port_stop(dai_data->port[dai->id]);
		अगर (rc < 0) अणु
			dev_err(dai->dev, "fail to close AFE port (%d)\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	चयन (dai->id) अणु
	हाल HDMI_RX:
	हाल DISPLAY_PORT_RX:
		q6afe_hdmi_port_prepare(dai_data->port[dai->id],
					&dai_data->port_config[dai->id].hdmi);
		अवरोध;
	हाल SLIMBUS_0_RX ... SLIMBUS_6_TX:
		q6afe_slim_port_prepare(dai_data->port[dai->id],
					&dai_data->port_config[dai->id].slim);
		अवरोध;
	हाल PRIMARY_MI2S_RX ... QUATERNARY_MI2S_TX:
		rc = q6afe_i2s_port_prepare(dai_data->port[dai->id],
			       &dai_data->port_config[dai->id].i2s_cfg);
		अगर (rc < 0) अणु
			dev_err(dai->dev, "fail to prepare AFE port %x\n",
				dai->id);
			वापस rc;
		पूर्ण
		अवरोध;
	हाल PRIMARY_TDM_RX_0 ... QUINARY_TDM_TX_7:
		q6afe_tdm_port_prepare(dai_data->port[dai->id],
					&dai_data->port_config[dai->id].tdm);
		अवरोध;
	हाल WSA_CODEC_DMA_RX_0 ... RX_CODEC_DMA_RX_7:
		q6afe_cdc_dma_port_prepare(dai_data->port[dai->id],
					   &dai_data->port_config[dai->id].dma_cfg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = q6afe_port_start(dai_data->port[dai->id]);
	अगर (rc < 0) अणु
		dev_err(dai->dev, "fail to start AFE port %x\n", dai->id);
		वापस rc;
	पूर्ण
	dai_data->is_port_started[dai->id] = true;

	वापस 0;
पूर्ण

अटल पूर्णांक q6slim_set_channel_map(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_port_config *pcfg = &dai_data->port_config[dai->id];
	पूर्णांक i;

	अगर (dai->id & 0x1) अणु
		/* TX */
		अगर (!tx_slot) अणु
			pr_err("%s: tx slot not found\n", __func__);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < tx_num; i++)
			pcfg->slim.ch_mapping[i] = tx_slot[i];

		pcfg->slim.num_channels = tx_num;


	पूर्ण अन्यथा अणु
		अगर (!rx_slot) अणु
			pr_err("%s: rx slot not found\n", __func__);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < rx_num; i++)
			pcfg->slim.ch_mapping[i] =   rx_slot[i];

		pcfg->slim.num_channels = rx_num;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6afe_mi2s_set_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_port *port = dai_data->port[dai->id];

	चयन (clk_id) अणु
	हाल LPAIF_DIG_CLK:
		वापस q6afe_port_set_sysclk(port, clk_id, 0, 5, freq, dir);
	हाल LPAIF_BIT_CLK:
	हाल LPAIF_OSR_CLK:
		वापस q6afe_port_set_sysclk(port, clk_id,
					     Q6AFE_LPASS_CLK_SRC_INTERNAL,
					     Q6AFE_LPASS_CLK_ROOT_DEFAULT,
					     freq, dir);
	हाल Q6AFE_LPASS_CLK_ID_PRI_MI2S_IBIT ... Q6AFE_LPASS_CLK_ID_QUI_MI2S_OSR:
	हाल Q6AFE_LPASS_CLK_ID_MCLK_1 ... Q6AFE_LPASS_CLK_ID_INT_MCLK_1:
	हाल Q6AFE_LPASS_CLK_ID_WSA_CORE_MCLK ... Q6AFE_LPASS_CLK_ID_VA_CORE_2X_MCLK:
		वापस q6afe_port_set_sysclk(port, clk_id,
					     Q6AFE_LPASS_CLK_ATTRIBUTE_COUPLE_NO,
					     Q6AFE_LPASS_CLK_ROOT_DEFAULT,
					     freq, dir);
	हाल Q6AFE_LPASS_CLK_ID_PRI_TDM_IBIT ... Q6AFE_LPASS_CLK_ID_QUIN_TDM_EBIT:
		वापस q6afe_port_set_sysclk(port, clk_id,
					     Q6AFE_LPASS_CLK_ATTRIBUTE_INVERT_COUPLE_NO,
					     Q6AFE_LPASS_CLK_ROOT_DEFAULT,
					     freq, dir);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route q6afe_dapm_routes[] = अणु
	अणु"HDMI Playback", शून्य, "HDMI_RX"पूर्ण,
	अणु"Display Port Playback", शून्य, "DISPLAY_PORT_RX"पूर्ण,
	अणु"Slimbus Playback", शून्य, "SLIMBUS_0_RX"पूर्ण,
	अणु"Slimbus1 Playback", शून्य, "SLIMBUS_1_RX"पूर्ण,
	अणु"Slimbus2 Playback", शून्य, "SLIMBUS_2_RX"पूर्ण,
	अणु"Slimbus3 Playback", शून्य, "SLIMBUS_3_RX"पूर्ण,
	अणु"Slimbus4 Playback", शून्य, "SLIMBUS_4_RX"पूर्ण,
	अणु"Slimbus5 Playback", शून्य, "SLIMBUS_5_RX"पूर्ण,
	अणु"Slimbus6 Playback", शून्य, "SLIMBUS_6_RX"पूर्ण,

	अणु"SLIMBUS_0_TX", शून्य, "Slimbus Capture"पूर्ण,
	अणु"SLIMBUS_1_TX", शून्य, "Slimbus1 Capture"पूर्ण,
	अणु"SLIMBUS_2_TX", शून्य, "Slimbus2 Capture"पूर्ण,
	अणु"SLIMBUS_3_TX", शून्य, "Slimbus3 Capture"पूर्ण,
	अणु"SLIMBUS_4_TX", शून्य, "Slimbus4 Capture"पूर्ण,
	अणु"SLIMBUS_5_TX", शून्य, "Slimbus5 Capture"पूर्ण,
	अणु"SLIMBUS_6_TX", शून्य, "Slimbus6 Capture"पूर्ण,

	अणु"Primary MI2S Playback", शून्य, "PRI_MI2S_RX"पूर्ण,
	अणु"Secondary MI2S Playback", शून्य, "SEC_MI2S_RX"पूर्ण,
	अणु"Tertiary MI2S Playback", शून्य, "TERT_MI2S_RX"पूर्ण,
	अणु"Quaternary MI2S Playback", शून्य, "QUAT_MI2S_RX"पूर्ण,

	अणु"Primary TDM0 Playback", शून्य, "PRIMARY_TDM_RX_0"पूर्ण,
	अणु"Primary TDM1 Playback", शून्य, "PRIMARY_TDM_RX_1"पूर्ण,
	अणु"Primary TDM2 Playback", शून्य, "PRIMARY_TDM_RX_2"पूर्ण,
	अणु"Primary TDM3 Playback", शून्य, "PRIMARY_TDM_RX_3"पूर्ण,
	अणु"Primary TDM4 Playback", शून्य, "PRIMARY_TDM_RX_4"पूर्ण,
	अणु"Primary TDM5 Playback", शून्य, "PRIMARY_TDM_RX_5"पूर्ण,
	अणु"Primary TDM6 Playback", शून्य, "PRIMARY_TDM_RX_6"पूर्ण,
	अणु"Primary TDM7 Playback", शून्य, "PRIMARY_TDM_RX_7"पूर्ण,

	अणु"Secondary TDM0 Playback", शून्य, "SEC_TDM_RX_0"पूर्ण,
	अणु"Secondary TDM1 Playback", शून्य, "SEC_TDM_RX_1"पूर्ण,
	अणु"Secondary TDM2 Playback", शून्य, "SEC_TDM_RX_2"पूर्ण,
	अणु"Secondary TDM3 Playback", शून्य, "SEC_TDM_RX_3"पूर्ण,
	अणु"Secondary TDM4 Playback", शून्य, "SEC_TDM_RX_4"पूर्ण,
	अणु"Secondary TDM5 Playback", शून्य, "SEC_TDM_RX_5"पूर्ण,
	अणु"Secondary TDM6 Playback", शून्य, "SEC_TDM_RX_6"पूर्ण,
	अणु"Secondary TDM7 Playback", शून्य, "SEC_TDM_RX_7"पूर्ण,

	अणु"Tertiary TDM0 Playback", शून्य, "TERT_TDM_RX_0"पूर्ण,
	अणु"Tertiary TDM1 Playback", शून्य, "TERT_TDM_RX_1"पूर्ण,
	अणु"Tertiary TDM2 Playback", शून्य, "TERT_TDM_RX_2"पूर्ण,
	अणु"Tertiary TDM3 Playback", शून्य, "TERT_TDM_RX_3"पूर्ण,
	अणु"Tertiary TDM4 Playback", शून्य, "TERT_TDM_RX_4"पूर्ण,
	अणु"Tertiary TDM5 Playback", शून्य, "TERT_TDM_RX_5"पूर्ण,
	अणु"Tertiary TDM6 Playback", शून्य, "TERT_TDM_RX_6"पूर्ण,
	अणु"Tertiary TDM7 Playback", शून्य, "TERT_TDM_RX_7"पूर्ण,

	अणु"Quaternary TDM0 Playback", शून्य, "QUAT_TDM_RX_0"पूर्ण,
	अणु"Quaternary TDM1 Playback", शून्य, "QUAT_TDM_RX_1"पूर्ण,
	अणु"Quaternary TDM2 Playback", शून्य, "QUAT_TDM_RX_2"पूर्ण,
	अणु"Quaternary TDM3 Playback", शून्य, "QUAT_TDM_RX_3"पूर्ण,
	अणु"Quaternary TDM4 Playback", शून्य, "QUAT_TDM_RX_4"पूर्ण,
	अणु"Quaternary TDM5 Playback", शून्य, "QUAT_TDM_RX_5"पूर्ण,
	अणु"Quaternary TDM6 Playback", शून्य, "QUAT_TDM_RX_6"पूर्ण,
	अणु"Quaternary TDM7 Playback", शून्य, "QUAT_TDM_RX_7"पूर्ण,

	अणु"Quinary TDM0 Playback", शून्य, "QUIN_TDM_RX_0"पूर्ण,
	अणु"Quinary TDM1 Playback", शून्य, "QUIN_TDM_RX_1"पूर्ण,
	अणु"Quinary TDM2 Playback", शून्य, "QUIN_TDM_RX_2"पूर्ण,
	अणु"Quinary TDM3 Playback", शून्य, "QUIN_TDM_RX_3"पूर्ण,
	अणु"Quinary TDM4 Playback", शून्य, "QUIN_TDM_RX_4"पूर्ण,
	अणु"Quinary TDM5 Playback", शून्य, "QUIN_TDM_RX_5"पूर्ण,
	अणु"Quinary TDM6 Playback", शून्य, "QUIN_TDM_RX_6"पूर्ण,
	अणु"Quinary TDM7 Playback", शून्य, "QUIN_TDM_RX_7"पूर्ण,

	अणु"PRIMARY_TDM_TX_0", शून्य, "Primary TDM0 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_1", शून्य, "Primary TDM1 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_2", शून्य, "Primary TDM2 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_3", शून्य, "Primary TDM3 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_4", शून्य, "Primary TDM4 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_5", शून्य, "Primary TDM5 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_6", शून्य, "Primary TDM6 Capture"पूर्ण,
	अणु"PRIMARY_TDM_TX_7", शून्य, "Primary TDM7 Capture"पूर्ण,

	अणु"SEC_TDM_TX_0", शून्य, "Secondary TDM0 Capture"पूर्ण,
	अणु"SEC_TDM_TX_1", शून्य, "Secondary TDM1 Capture"पूर्ण,
	अणु"SEC_TDM_TX_2", शून्य, "Secondary TDM2 Capture"पूर्ण,
	अणु"SEC_TDM_TX_3", शून्य, "Secondary TDM3 Capture"पूर्ण,
	अणु"SEC_TDM_TX_4", शून्य, "Secondary TDM4 Capture"पूर्ण,
	अणु"SEC_TDM_TX_5", शून्य, "Secondary TDM5 Capture"पूर्ण,
	अणु"SEC_TDM_TX_6", शून्य, "Secondary TDM6 Capture"पूर्ण,
	अणु"SEC_TDM_TX_7", शून्य, "Secondary TDM7 Capture"पूर्ण,

	अणु"TERT_TDM_TX_0", शून्य, "Tertiary TDM0 Capture"पूर्ण,
	अणु"TERT_TDM_TX_1", शून्य, "Tertiary TDM1 Capture"पूर्ण,
	अणु"TERT_TDM_TX_2", शून्य, "Tertiary TDM2 Capture"पूर्ण,
	अणु"TERT_TDM_TX_3", शून्य, "Tertiary TDM3 Capture"पूर्ण,
	अणु"TERT_TDM_TX_4", शून्य, "Tertiary TDM4 Capture"पूर्ण,
	अणु"TERT_TDM_TX_5", शून्य, "Tertiary TDM5 Capture"पूर्ण,
	अणु"TERT_TDM_TX_6", शून्य, "Tertiary TDM6 Capture"पूर्ण,
	अणु"TERT_TDM_TX_7", शून्य, "Tertiary TDM7 Capture"पूर्ण,

	अणु"QUAT_TDM_TX_0", शून्य, "Quaternary TDM0 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_1", शून्य, "Quaternary TDM1 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_2", शून्य, "Quaternary TDM2 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_3", शून्य, "Quaternary TDM3 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_4", शून्य, "Quaternary TDM4 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_5", शून्य, "Quaternary TDM5 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_6", शून्य, "Quaternary TDM6 Capture"पूर्ण,
	अणु"QUAT_TDM_TX_7", शून्य, "Quaternary TDM7 Capture"पूर्ण,

	अणु"QUIN_TDM_TX_0", शून्य, "Quinary TDM0 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_1", शून्य, "Quinary TDM1 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_2", शून्य, "Quinary TDM2 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_3", शून्य, "Quinary TDM3 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_4", शून्य, "Quinary TDM4 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_5", शून्य, "Quinary TDM5 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_6", शून्य, "Quinary TDM6 Capture"पूर्ण,
	अणु"QUIN_TDM_TX_7", शून्य, "Quinary TDM7 Capture"पूर्ण,

	अणु"TERT_MI2S_TX", शून्य, "Tertiary MI2S Capture"पूर्ण,
	अणु"PRI_MI2S_TX", शून्य, "Primary MI2S Capture"पूर्ण,
	अणु"SEC_MI2S_TX", शून्य, "Secondary MI2S Capture"पूर्ण,
	अणु"QUAT_MI2S_TX", शून्य, "Quaternary MI2S Capture"पूर्ण,

	अणु"WSA_CODEC_DMA_RX_0 Playback", शून्य, "WSA_CODEC_DMA_RX_0"पूर्ण,
	अणु"WSA_CODEC_DMA_TX_0", शून्य, "WSA_CODEC_DMA_TX_0 Capture"पूर्ण,
	अणु"WSA_CODEC_DMA_RX_1 Playback", शून्य, "WSA_CODEC_DMA_RX_1"पूर्ण,
	अणु"WSA_CODEC_DMA_TX_1", शून्य, "WSA_CODEC_DMA_TX_1 Capture"पूर्ण,
	अणु"WSA_CODEC_DMA_TX_2", शून्य, "WSA_CODEC_DMA_TX_2 Capture"पूर्ण,
	अणु"VA_CODEC_DMA_TX_0", शून्य, "VA_CODEC_DMA_TX_0 Capture"पूर्ण,
	अणु"VA_CODEC_DMA_TX_1", शून्य, "VA_CODEC_DMA_TX_1 Capture"पूर्ण,
	अणु"VA_CODEC_DMA_TX_2", शून्य, "VA_CODEC_DMA_TX_2 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_0 Playback", शून्य, "RX_CODEC_DMA_RX_0"पूर्ण,
	अणु"TX_CODEC_DMA_TX_0", शून्य, "TX_CODEC_DMA_TX_0 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_1 Playback", शून्य, "RX_CODEC_DMA_RX_1"पूर्ण,
	अणु"TX_CODEC_DMA_TX_1", शून्य, "TX_CODEC_DMA_TX_1 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_2 Playback", शून्य, "RX_CODEC_DMA_RX_2"पूर्ण,
	अणु"TX_CODEC_DMA_TX_2", शून्य, "TX_CODEC_DMA_TX_2 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_3 Playback", शून्य, "RX_CODEC_DMA_RX_3"पूर्ण,
	अणु"TX_CODEC_DMA_TX_3", शून्य, "TX_CODEC_DMA_TX_3 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_4 Playback", शून्य, "RX_CODEC_DMA_RX_4"पूर्ण,
	अणु"TX_CODEC_DMA_TX_4", शून्य, "TX_CODEC_DMA_TX_4 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_5 Playback", शून्य, "RX_CODEC_DMA_RX_5"पूर्ण,
	अणु"TX_CODEC_DMA_TX_5", शून्य, "TX_CODEC_DMA_TX_5 Capture"पूर्ण,
	अणु"RX_CODEC_DMA_RX_6 Playback", शून्य, "RX_CODEC_DMA_RX_6"पूर्ण,
	अणु"RX_CODEC_DMA_RX_7 Playback", शून्य, "RX_CODEC_DMA_RX_7"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops q6hdmi_ops = अणु
	.prepare	= q6afe_dai_prepare,
	.hw_params	= q6hdmi_hw_params,
	.shutकरोwn	= q6afe_dai_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops q6i2s_ops = अणु
	.prepare	= q6afe_dai_prepare,
	.hw_params	= q6i2s_hw_params,
	.set_fmt	= q6i2s_set_fmt,
	.shutकरोwn	= q6afe_dai_shutकरोwn,
	.set_sysclk	= q6afe_mi2s_set_sysclk,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops q6slim_ops = अणु
	.prepare	= q6afe_dai_prepare,
	.hw_params	= q6slim_hw_params,
	.shutकरोwn	= q6afe_dai_shutकरोwn,
	.set_channel_map = q6slim_set_channel_map,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops q6tdm_ops = अणु
	.prepare	= q6afe_dai_prepare,
	.shutकरोwn	= q6afe_dai_shutकरोwn,
	.set_sysclk	= q6afe_mi2s_set_sysclk,
	.set_tdm_slot     = q6tdm_set_tdm_slot,
	.set_channel_map  = q6tdm_set_channel_map,
	.hw_params        = q6tdm_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops q6dma_ops = अणु
	.prepare	= q6afe_dai_prepare,
	.shutकरोwn	= q6afe_dai_shutकरोwn,
	.set_sysclk	= q6afe_mi2s_set_sysclk,
	.set_channel_map  = q6dma_set_channel_map,
	.hw_params        = q6dma_hw_params,
पूर्ण;

अटल पूर्णांक msm_dai_q6_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	काष्ठा q6afe_port *port;

	port = q6afe_port_get_from_id(dai->dev, dai->id);
	अगर (IS_ERR(port)) अणु
		dev_err(dai->dev, "Unable to get afe port\n");
		वापस -EINVAL;
	पूर्ण
	dai_data->port[dai->id] = port;

	वापस 0;
पूर्ण

अटल पूर्णांक msm_dai_q6_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);

	q6afe_port_put(dai_data->port[dai->id]);
	dai_data->port[dai->id] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver q6afe_dais[] = अणु
	अणु
		.playback = अणु
			.stream_name = "HDMI Playback",
			.rates = SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 2,
			.channels_max = 8,
			.rate_max =     192000,
			.rate_min =	48000,
		पूर्ण,
		.ops = &q6hdmi_ops,
		.id = HDMI_RX,
		.name = "HDMI",
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.name = "SLIMBUS_0_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_0_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.playback = अणु
			.stream_name = "Slimbus Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.name = "SLIMBUS_0_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_0_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus1 Playback",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.name = "SLIMBUS_1_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_1_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.name = "SLIMBUS_1_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_1_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus1 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus2 Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.name = "SLIMBUS_2_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_2_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,

	पूर्ण, अणु
		.name = "SLIMBUS_2_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_2_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus2 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus3 Playback",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.name = "SLIMBUS_3_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_3_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,

	पूर्ण, अणु
		.name = "SLIMBUS_3_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_3_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus3 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus4 Playback",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.name = "SLIMBUS_4_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_4_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,

	पूर्ण, अणु
		.name = "SLIMBUS_4_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_4_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus4 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus5 Playback",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.name = "SLIMBUS_5_RX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_5_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,

	पूर्ण, अणु
		.name = "SLIMBUS_5_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_5_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus5 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Slimbus6 Playback",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
		.ops = &q6slim_ops,
		.name = "SLIMBUS_6_RX",
		.id = SLIMBUS_6_RX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,

	पूर्ण, अणु
		.name = "SLIMBUS_6_TX",
		.ops = &q6slim_ops,
		.id = SLIMBUS_6_TX,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
		.capture = अणु
			.stream_name = "Slimbus6 Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 192000,
		पूर्ण,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Primary MI2S Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.id = PRIMARY_MI2S_RX,
		.name = "PRI_MI2S_RX",
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.capture = अणु
			.stream_name = "Primary MI2S Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.id = PRIMARY_MI2S_TX,
		.name = "PRI_MI2S_TX",
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Secondary MI2S Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.name = "SEC_MI2S_RX",
		.id = SECONDARY_MI2S_RX,
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.capture = अणु
			.stream_name = "Secondary MI2S Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.id = SECONDARY_MI2S_TX,
		.name = "SEC_MI2S_TX",
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Tertiary MI2S Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.name = "TERT_MI2S_RX",
		.id = TERTIARY_MI2S_RX,
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.capture = अणु
			.stream_name = "Tertiary MI2S Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.id = TERTIARY_MI2S_TX,
		.name = "TERT_MI2S_TX",
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.playback = अणु
			.stream_name = "Quaternary MI2S Playback",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.name = "QUAT_MI2S_RX",
		.id = QUATERNARY_MI2S_RX,
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण, अणु
		.capture = अणु
			.stream_name = "Quaternary MI2S Capture",
			.rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 1,
			.channels_max = 8,
			.rate_min =     8000,
			.rate_max =     48000,
		पूर्ण,
		.id = QUATERNARY_MI2S_TX,
		.name = "QUAT_MI2S_TX",
		.ops = &q6i2s_ops,
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण,
	Q6AFE_TDM_PB_DAI("Primary", 0, PRIMARY_TDM_RX_0),
	Q6AFE_TDM_PB_DAI("Primary", 1, PRIMARY_TDM_RX_1),
	Q6AFE_TDM_PB_DAI("Primary", 2, PRIMARY_TDM_RX_2),
	Q6AFE_TDM_PB_DAI("Primary", 3, PRIMARY_TDM_RX_3),
	Q6AFE_TDM_PB_DAI("Primary", 4, PRIMARY_TDM_RX_4),
	Q6AFE_TDM_PB_DAI("Primary", 5, PRIMARY_TDM_RX_5),
	Q6AFE_TDM_PB_DAI("Primary", 6, PRIMARY_TDM_RX_6),
	Q6AFE_TDM_PB_DAI("Primary", 7, PRIMARY_TDM_RX_7),
	Q6AFE_TDM_CAP_DAI("Primary", 0, PRIMARY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Primary", 1, PRIMARY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Primary", 2, PRIMARY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Primary", 3, PRIMARY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Primary", 4, PRIMARY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Primary", 5, PRIMARY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Primary", 6, PRIMARY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Primary", 7, PRIMARY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Secondary", 0, SECONDARY_TDM_RX_0),
	Q6AFE_TDM_PB_DAI("Secondary", 1, SECONDARY_TDM_RX_1),
	Q6AFE_TDM_PB_DAI("Secondary", 2, SECONDARY_TDM_RX_2),
	Q6AFE_TDM_PB_DAI("Secondary", 3, SECONDARY_TDM_RX_3),
	Q6AFE_TDM_PB_DAI("Secondary", 4, SECONDARY_TDM_RX_4),
	Q6AFE_TDM_PB_DAI("Secondary", 5, SECONDARY_TDM_RX_5),
	Q6AFE_TDM_PB_DAI("Secondary", 6, SECONDARY_TDM_RX_6),
	Q6AFE_TDM_PB_DAI("Secondary", 7, SECONDARY_TDM_RX_7),
	Q6AFE_TDM_CAP_DAI("Secondary", 0, SECONDARY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Secondary", 1, SECONDARY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Secondary", 2, SECONDARY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Secondary", 3, SECONDARY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Secondary", 4, SECONDARY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Secondary", 5, SECONDARY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Secondary", 6, SECONDARY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Secondary", 7, SECONDARY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Tertiary", 0, TERTIARY_TDM_RX_0),
	Q6AFE_TDM_PB_DAI("Tertiary", 1, TERTIARY_TDM_RX_1),
	Q6AFE_TDM_PB_DAI("Tertiary", 2, TERTIARY_TDM_RX_2),
	Q6AFE_TDM_PB_DAI("Tertiary", 3, TERTIARY_TDM_RX_3),
	Q6AFE_TDM_PB_DAI("Tertiary", 4, TERTIARY_TDM_RX_4),
	Q6AFE_TDM_PB_DAI("Tertiary", 5, TERTIARY_TDM_RX_5),
	Q6AFE_TDM_PB_DAI("Tertiary", 6, TERTIARY_TDM_RX_6),
	Q6AFE_TDM_PB_DAI("Tertiary", 7, TERTIARY_TDM_RX_7),
	Q6AFE_TDM_CAP_DAI("Tertiary", 0, TERTIARY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Tertiary", 1, TERTIARY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Tertiary", 2, TERTIARY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Tertiary", 3, TERTIARY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Tertiary", 4, TERTIARY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Tertiary", 5, TERTIARY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Tertiary", 6, TERTIARY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Tertiary", 7, TERTIARY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Quaternary", 0, QUATERNARY_TDM_RX_0),
	Q6AFE_TDM_PB_DAI("Quaternary", 1, QUATERNARY_TDM_RX_1),
	Q6AFE_TDM_PB_DAI("Quaternary", 2, QUATERNARY_TDM_RX_2),
	Q6AFE_TDM_PB_DAI("Quaternary", 3, QUATERNARY_TDM_RX_3),
	Q6AFE_TDM_PB_DAI("Quaternary", 4, QUATERNARY_TDM_RX_4),
	Q6AFE_TDM_PB_DAI("Quaternary", 5, QUATERNARY_TDM_RX_5),
	Q6AFE_TDM_PB_DAI("Quaternary", 6, QUATERNARY_TDM_RX_6),
	Q6AFE_TDM_PB_DAI("Quaternary", 7, QUATERNARY_TDM_RX_7),
	Q6AFE_TDM_CAP_DAI("Quaternary", 0, QUATERNARY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Quaternary", 1, QUATERNARY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Quaternary", 2, QUATERNARY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Quaternary", 3, QUATERNARY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Quaternary", 4, QUATERNARY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Quaternary", 5, QUATERNARY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Quaternary", 6, QUATERNARY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Quaternary", 7, QUATERNARY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Quinary", 0, QUINARY_TDM_RX_0),
	Q6AFE_TDM_PB_DAI("Quinary", 1, QUINARY_TDM_RX_1),
	Q6AFE_TDM_PB_DAI("Quinary", 2, QUINARY_TDM_RX_2),
	Q6AFE_TDM_PB_DAI("Quinary", 3, QUINARY_TDM_RX_3),
	Q6AFE_TDM_PB_DAI("Quinary", 4, QUINARY_TDM_RX_4),
	Q6AFE_TDM_PB_DAI("Quinary", 5, QUINARY_TDM_RX_5),
	Q6AFE_TDM_PB_DAI("Quinary", 6, QUINARY_TDM_RX_6),
	Q6AFE_TDM_PB_DAI("Quinary", 7, QUINARY_TDM_RX_7),
	Q6AFE_TDM_CAP_DAI("Quinary", 0, QUINARY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Quinary", 1, QUINARY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Quinary", 2, QUINARY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Quinary", 3, QUINARY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Quinary", 4, QUINARY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Quinary", 5, QUINARY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Quinary", 6, QUINARY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Quinary", 7, QUINARY_TDM_TX_7),
	अणु
		.playback = अणु
			.stream_name = "Display Port Playback",
			.rates = SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_LE,
			.channels_min = 2,
			.channels_max = 8,
			.rate_max =     192000,
			.rate_min =	48000,
		पूर्ण,
		.ops = &q6hdmi_ops,
		.id = DISPLAY_PORT_RX,
		.name = "DISPLAY_PORT",
		.probe = msm_dai_q6_dai_probe,
		.हटाओ = msm_dai_q6_dai_हटाओ,
	पूर्ण,
	Q6AFE_CDC_DMA_RX_DAI(WSA_CODEC_DMA_RX_0),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_RX_DAI(WSA_CODEC_DMA_RX_1),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_0),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_1),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_2),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_3),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_3),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_4),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_4),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_5),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_5),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_6),
	Q6AFE_CDC_DMA_RX_DAI(RX_CODEC_DMA_RX_7),
पूर्ण;

अटल पूर्णांक q6afe_of_xlate_dai_name(काष्ठा snd_soc_component *component,
				   स्थिर काष्ठा of_phandle_args *args,
				   स्थिर अक्षर **dai_name)
अणु
	पूर्णांक id = args->args[0];
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i  < ARRAY_SIZE(q6afe_dais); i++) अणु
		अगर (q6afe_dais[i].id == id) अणु
			*dai_name = q6afe_dais[i].name;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget q6afe_dai_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("HDMI_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_0_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_1_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_2_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_3_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_4_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_5_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLIMBUS_6_RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_0_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_1_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_2_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_3_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_4_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_5_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLIMBUS_6_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_MI2S_RX", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_MI2S_TX", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_MI2S_RX", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_MI2S_TX", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_MI2S_RX", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_MI2S_TX", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_MI2S_RX_SD1",
			"Secondary MI2S Playback SD1",
			0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRI_MI2S_RX", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRI_MI2S_TX", शून्य,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_0", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_1", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_2", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_3", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_4", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_5", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_6", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PRIMARY_TDM_RX_7", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_0", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_1", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_2", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_3", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_4", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_5", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_6", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PRIMARY_TDM_TX_7", शून्य,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_0", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_1", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_2", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_3", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_4", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_5", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_6", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_RX_7", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_0", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_1", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_2", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_3", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_4", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_5", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_6", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_7", शून्य,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_0", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_1", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_2", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_3", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_4", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_5", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_6", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TERT_TDM_RX_7", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_0", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_1", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_2", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_3", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_4", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_5", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_6", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TERT_TDM_TX_7", शून्य,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_0", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_1", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_2", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_3", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_4", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_5", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_6", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_RX_7", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_0", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_1", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_2", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_3", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_4", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_5", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_6", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_7", शून्य,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_0", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_1", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_2", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_3", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_4", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_5", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_6", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_RX_7", शून्य,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_0", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_1", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_2", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_3", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_4", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_5", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_6", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_7", शून्य,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DISPLAY_PORT_RX", "NULL", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("WSA_CODEC_DMA_RX_0", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_0", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WSA_CODEC_DMA_RX_1", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_1", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_2", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_0", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_1", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_2", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_0", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_0", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_1", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_1", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_2", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_2", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_3", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_3", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_4", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_4", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_5", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_5", "NULL",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_6", "NULL",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("RX_CODEC_DMA_RX_7", "NULL",
		0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver q6afe_dai_component = अणु
	.name		= "q6afe-dai-component",
	.dapm_widमाला_लो = q6afe_dai_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(q6afe_dai_widमाला_लो),
	.dapm_routes = q6afe_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(q6afe_dapm_routes),
	.of_xlate_dai_name = q6afe_of_xlate_dai_name,

पूर्ण;

अटल व्योम of_q6afe_parse_dai_data(काष्ठा device *dev,
				    काष्ठा q6afe_dai_data *data)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret;

	क्रम_each_child_of_node(dev->of_node, node) अणु
		अचिन्हित पूर्णांक lines[Q6AFE_MAX_MI2S_LINES];
		काष्ठा q6afe_dai_priv_data *priv;
		पूर्णांक id, i, num_lines;

		ret = of_property_पढ़ो_u32(node, "reg", &id);
		अगर (ret || id < 0 || id >= AFE_PORT_MAX) अणु
			dev_err(dev, "valid dai id not found:%d\n", ret);
			जारी;
		पूर्ण

		चयन (id) अणु
		/* MI2S specअगरic properties */
		हाल PRIMARY_MI2S_RX ... QUATERNARY_MI2S_TX:
			priv = &data->priv[id];
			ret = of_property_पढ़ो_variable_u32_array(node,
							"qcom,sd-lines",
							lines, 0,
							Q6AFE_MAX_MI2S_LINES);
			अगर (ret < 0)
				num_lines = 0;
			अन्यथा
				num_lines = ret;

			priv->sd_line_mask = 0;

			क्रम (i = 0; i < num_lines; i++)
				priv->sd_line_mask |= BIT(lines[i]);

			अवरोध;
		हाल PRIMARY_TDM_RX_0 ... QUINARY_TDM_TX_7:
			priv = &data->priv[id];
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-sync-mode",
						   &priv->sync_mode);
			अगर (ret) अणु
				dev_err(dev, "No Sync mode from DT\n");
				अवरोध;
			पूर्ण
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-sync-src",
						   &priv->sync_src);
			अगर (ret) अणु
				dev_err(dev, "No Sync Src from DT\n");
				अवरोध;
			पूर्ण
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-data-out",
						   &priv->data_out_enable);
			अगर (ret) अणु
				dev_err(dev, "No Data out enable from DT\n");
				अवरोध;
			पूर्ण
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-invert-sync",
						   &priv->invert_sync);
			अगर (ret) अणु
				dev_err(dev, "No Invert sync from DT\n");
				अवरोध;
			पूर्ण
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-data-delay",
						   &priv->data_delay);
			अगर (ret) अणु
				dev_err(dev, "No Data Delay from DT\n");
				अवरोध;
			पूर्ण
			ret = of_property_पढ़ो_u32(node, "qcom,tdm-data-align",
						   &priv->data_align);
			अगर (ret) अणु
				dev_err(dev, "No Data align from DT\n");
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक q6afe_dai_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा q6afe_dai_data *dai_data;
	काष्ठा device *dev = &pdev->dev;

	dai_data = devm_kzalloc(dev, माप(*dai_data), GFP_KERNEL);
	अगर (!dai_data)
		वापस -ENOMEM;

	dev_set_drvdata(dev, dai_data);

	of_q6afe_parse_dai_data(dev, dai_data);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &q6afe_dai_component,
					  q6afe_dais, ARRAY_SIZE(q6afe_dais));
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6afe_dai_device_id[] = अणु
	अणु .compatible = "qcom,q6afe-dais" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6afe_dai_device_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver q6afe_dai_platक्रमm_driver = अणु
	.driver = अणु
		.name = "q6afe-dai",
		.of_match_table = of_match_ptr(q6afe_dai_device_id),
	पूर्ण,
	.probe = q6afe_dai_dev_probe,
पूर्ण;
module_platक्रमm_driver(q6afe_dai_platक्रमm_driver);

MODULE_DESCRIPTION("Q6 Audio Fronend dai driver");
MODULE_LICENSE("GPL v2");
