<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 *
 * lpass-hdmi.c -- ALSA SoC HDMI-CPU DAI driver क्रम QTi LPASS HDMI
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <dt-bindings/sound/sc7180-lpass.h>
#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

अटल पूर्णांक lpass_hdmi_daiops_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक ret;
	पूर्णांक bitwidth;
	अचिन्हित पूर्णांक word_length;
	अचिन्हित पूर्णांक ch_sts_buf0;
	अचिन्हित पूर्णांक ch_sts_buf1;
	अचिन्हित पूर्णांक data_क्रमmat;
	अचिन्हित पूर्णांक sampling_freq;
	अचिन्हित पूर्णांक ch = 0;
	काष्ठा lpass_dp_metadata_ctl *meta_ctl = drvdata->meta_ctl;
	काष्ठा lpass_sstream_ctl *sstream_ctl = drvdata->sstream_ctl;

	bitwidth = snd_pcm_क्रमmat_width(क्रमmat);
	अगर (bitwidth < 0) अणु
		dev_err(dai->dev, "%s invalid bit width given : %d\n",
					__func__, bitwidth);
		वापस bitwidth;
	पूर्ण

	चयन (bitwidth) अणु
	हाल 16:
		word_length = LPASS_DP_AUDIO_BITWIDTH16;
		अवरोध;
	हाल 24:
		word_length = LPASS_DP_AUDIO_BITWIDTH24;
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s invalid bit width given : %d\n",
					__func__, bitwidth);
		वापस -EINVAL;
	पूर्ण

	चयन (rate) अणु
	हाल 32000:
		sampling_freq = LPASS_SAMPLING_FREQ32;
		अवरोध;
	हाल 44100:
		sampling_freq = LPASS_SAMPLING_FREQ44;
		अवरोध;
	हाल 48000:
		sampling_freq = LPASS_SAMPLING_FREQ48;
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s invalid bit width given : %d\n",
					__func__, bitwidth);
		वापस -EINVAL;
	पूर्ण
	data_क्रमmat = LPASS_DATA_FORMAT_LINEAR;
	ch_sts_buf0 = (((data_क्रमmat << LPASS_DATA_FORMAT_SHIFT) & LPASS_DATA_FORMAT_MASK)
				| ((sampling_freq << LPASS_FREQ_BIT_SHIFT) & LPASS_FREQ_BIT_MASK));
	ch_sts_buf1 = (word_length) & LPASS_WORDLENGTH_MASK;

	ret = regmap_field_ग_लिखो(drvdata->tx_ctl->soft_reset, LPASS_TX_CTL_RESET);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->tx_ctl->soft_reset, LPASS_TX_CTL_CLEAR);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmitx_legacy_en, LPASS_HDMITX_LEGACY_DISABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmitx_parity_calc_en, HDMITX_PARITY_CALC_EN);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->vbit_ctl->replace_vbit, REPLACE_VBIT);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->vbit_ctl->vbit_stream, LINEAR_PCM_DATA);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmitx_ch_msb[0], ch_sts_buf1);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmitx_ch_lsb[0], ch_sts_buf0);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmi_tx_dmactl[0]->use_hw_chs, HW_MODE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmi_tx_dmactl[0]->hw_chs_sel, SW_MODE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmi_tx_dmactl[0]->use_hw_usr, HW_MODE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->hdmi_tx_dmactl[0]->hw_usr_sel, SW_MODE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->mute, LPASS_MUTE_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->as_sdp_cc, channels - 1);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->as_sdp_ct, LPASS_META_DEFAULT_VAL);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->aअगर_db4, LPASS_META_DEFAULT_VAL);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->frequency, sampling_freq);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->mst_index, LPASS_META_DEFAULT_VAL);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(meta_ctl->dptx_index, LPASS_META_DEFAULT_VAL);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->sstream_en, LPASS_SSTREAM_DISABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->dma_sel, ch);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->स्वतः_bbit_en, LPASS_SSTREAM_DEFAULT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->layout, LPASS_SSTREAM_DEFAULT_DISABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->layout_sp, LPASS_LAYOUT_SP_DEFAULT);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->dp_audio, LPASS_SSTREAM_DEFAULT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->set_sp_on_en, LPASS_SSTREAM_DEFAULT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->dp_sp_b_hw_en, LPASS_SSTREAM_DEFAULT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(sstream_ctl->dp_staffing_en, LPASS_SSTREAM_DEFAULT_ENABLE);

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_hdmi_daiops_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);

	ret = regmap_field_ग_लिखो(drvdata->sstream_ctl->sstream_en, LPASS_SSTREAM_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(drvdata->meta_ctl->mute, LPASS_MUTE_DISABLE);

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_hdmi_daiops_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	काष्ठा lpass_dp_metadata_ctl *meta_ctl = drvdata->meta_ctl;
	काष्ठा lpass_sstream_ctl *sstream_ctl = drvdata->sstream_ctl;
	पूर्णांक ret = -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = regmap_field_ग_लिखो(sstream_ctl->sstream_en, LPASS_SSTREAM_ENABLE);
		अगर (ret)
			वापस ret;

		ret = regmap_field_ग_लिखो(meta_ctl->mute, LPASS_MUTE_DISABLE);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = regmap_field_ग_लिखो(sstream_ctl->sstream_en, LPASS_SSTREAM_DISABLE);
		अगर (ret)
			वापस ret;

		ret = regmap_field_ग_लिखो(meta_ctl->mute, LPASS_MUTE_ENABLE);
		अगर (ret)
			वापस ret;

		ret = regmap_field_ग_लिखो(sstream_ctl->dp_audio, 0);
		अगर (ret)
			वापस ret;

		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops asoc_qcom_lpass_hdmi_dai_ops = अणु
	.hw_params	= lpass_hdmi_daiops_hw_params,
	.prepare	= lpass_hdmi_daiops_prepare,
	.trigger	= lpass_hdmi_daiops_trigger,
पूर्ण;
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_hdmi_dai_ops);

MODULE_DESCRIPTION("QTi LPASS HDMI Driver");
MODULE_LICENSE("GPL v2");
