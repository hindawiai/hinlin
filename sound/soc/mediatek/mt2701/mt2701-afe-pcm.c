<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediatek ALSA SoC AFE platक्रमm driver क्रम 2701
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 *	   Ir Lian <ir.lian@mediatek.com>
 *	   Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "mt2701-afe-common.h"
#समावेश "mt2701-afe-clock-ctrl.h"
#समावेश "../common/mtk-afe-platform-driver.h"
#समावेश "../common/mtk-afe-fe-dai.h"

अटल स्थिर काष्ठा snd_pcm_hardware mt2701_afe_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED
		| SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE
		   | SNDRV_PCM_FMTBIT_S32_LE,
	.period_bytes_min = 1024,
	.period_bytes_max = 1024 * 256,
	.periods_min = 4,
	.periods_max = 1024,
	.buffer_bytes_max = 1024 * 1024,
	.fअगरo_size = 0,
पूर्ण;

काष्ठा mt2701_afe_rate अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक regvalue;
पूर्ण;

अटल स्थिर काष्ठा mt2701_afe_rate mt2701_afe_i2s_rates[] = अणु
	अणु .rate = 8000, .regvalue = 0 पूर्ण,
	अणु .rate = 12000, .regvalue = 1 पूर्ण,
	अणु .rate = 16000, .regvalue = 2 पूर्ण,
	अणु .rate = 24000, .regvalue = 3 पूर्ण,
	अणु .rate = 32000, .regvalue = 4 पूर्ण,
	अणु .rate = 48000, .regvalue = 5 पूर्ण,
	अणु .rate = 96000, .regvalue = 6 पूर्ण,
	अणु .rate = 192000, .regvalue = 7 पूर्ण,
	अणु .rate = 384000, .regvalue = 8 पूर्ण,
	अणु .rate = 7350, .regvalue = 16 पूर्ण,
	अणु .rate = 11025, .regvalue = 17 पूर्ण,
	अणु .rate = 14700, .regvalue = 18 पूर्ण,
	अणु .rate = 22050, .regvalue = 19 पूर्ण,
	अणु .rate = 29400, .regvalue = 20 पूर्ण,
	अणु .rate = 44100, .regvalue = 21 पूर्ण,
	अणु .rate = 88200, .regvalue = 22 पूर्ण,
	अणु .rate = 176400, .regvalue = 23 पूर्ण,
	अणु .rate = 352800, .regvalue = 24 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt2701_afe_backup_list[] = अणु
	AUDIO_TOP_CON0,
	AUDIO_TOP_CON4,
	AUDIO_TOP_CON5,
	ASYS_TOP_CON,
	AFE_CONN0,
	AFE_CONN1,
	AFE_CONN2,
	AFE_CONN3,
	AFE_CONN15,
	AFE_CONN16,
	AFE_CONN17,
	AFE_CONN18,
	AFE_CONN19,
	AFE_CONN20,
	AFE_CONN21,
	AFE_CONN22,
	AFE_DAC_CON0,
	AFE_MEMIF_PBUF_SIZE,
पूर्ण;

अटल पूर्णांक mt2701_dai_num_to_i2s(काष्ठा mtk_base_afe *afe, पूर्णांक num)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक val = num - MT2701_IO_I2S;

	अगर (val < 0 || val >= afe_priv->soc->i2s_num) अणु
		dev_err(afe->dev, "%s, num not available, num %d, val %d\n",
			__func__, num, val);
		वापस -EINVAL;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक mt2701_afe_i2s_fs(अचिन्हित पूर्णांक sample_rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt2701_afe_i2s_rates); i++)
		अगर (mt2701_afe_i2s_rates[i].rate == sample_rate)
			वापस mt2701_afe_i2s_rates[i].regvalue;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt2701_afe_i2s_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i2s_num = mt2701_dai_num_to_i2s(afe, dai->id);
	bool mode = afe_priv->soc->has_one_heart_mode;

	अगर (i2s_num < 0)
		वापस i2s_num;

	वापस mt2701_afe_enable_mclk(afe, mode ? 1 : i2s_num);
पूर्ण

अटल पूर्णांक mt2701_afe_i2s_path_disable(काष्ठा mtk_base_afe *afe,
				       काष्ठा mt2701_i2s_path *i2s_path,
				       पूर्णांक stream_dir)
अणु
	स्थिर काष्ठा mt2701_i2s_data *i2s_data = i2s_path->i2s_data[stream_dir];

	अगर (--i2s_path->on[stream_dir] < 0)
		i2s_path->on[stream_dir] = 0;

	अगर (i2s_path->on[stream_dir])
		वापस 0;

	/* disable i2s */
	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg,
			   ASYS_I2S_CON_I2S_EN, 0);

	mt2701_afe_disable_i2s(afe, i2s_path, stream_dir);

	वापस 0;
पूर्ण

अटल व्योम mt2701_afe_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i2s_num = mt2701_dai_num_to_i2s(afe, dai->id);
	काष्ठा mt2701_i2s_path *i2s_path;
	bool mode = afe_priv->soc->has_one_heart_mode;

	अगर (i2s_num < 0)
		वापस;

	i2s_path = &afe_priv->i2s_path[i2s_num];

	अगर (i2s_path->occupied[substream->stream])
		i2s_path->occupied[substream->stream] = 0;
	अन्यथा
		जाओ निकास;

	mt2701_afe_i2s_path_disable(afe, i2s_path, substream->stream);

	/* need to disable i2s-out path when disable i2s-in */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mt2701_afe_i2s_path_disable(afe, i2s_path, !substream->stream);

निकास:
	/* disable mclk */
	mt2701_afe_disable_mclk(afe, mode ? 1 : i2s_num);
पूर्ण

अटल पूर्णांक mt2701_i2s_path_enable(काष्ठा mtk_base_afe *afe,
				  काष्ठा mt2701_i2s_path *i2s_path,
				  पूर्णांक stream_dir, पूर्णांक rate)
अणु
	स्थिर काष्ठा mt2701_i2s_data *i2s_data = i2s_path->i2s_data[stream_dir];
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक reg, fs, w_len = 1; /* now we support bck 64bits only */
	अचिन्हित पूर्णांक mask, val;

	/* no need to enable अगर alपढ़ोy करोne */
	अगर (++i2s_path->on[stream_dir] != 1)
		वापस 0;

	fs = mt2701_afe_i2s_fs(rate);

	mask = ASYS_I2S_CON_FS |
	       ASYS_I2S_CON_I2S_COUPLE_MODE | /* 0 */
	       ASYS_I2S_CON_I2S_MODE |
	       ASYS_I2S_CON_WIDE_MODE;

	val = ASYS_I2S_CON_FS_SET(fs) |
	      ASYS_I2S_CON_I2S_MODE |
	      ASYS_I2S_CON_WIDE_MODE_SET(w_len);

	अगर (stream_dir == SNDRV_PCM_STREAM_CAPTURE) अणु
		mask |= ASYS_I2S_IN_PHASE_FIX;
		val |= ASYS_I2S_IN_PHASE_FIX;
		reg = ASMI_TIMING_CON1;
	पूर्ण अन्यथा अणु
		अगर (afe_priv->soc->has_one_heart_mode) अणु
			mask |= ASYS_I2S_CON_ONE_HEART_MODE;
			val |= ASYS_I2S_CON_ONE_HEART_MODE;
		पूर्ण
		reg = ASMO_TIMING_CON1;
	पूर्ण

	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg, mask, val);

	regmap_update_bits(afe->regmap, reg,
			   i2s_data->i2s_asrc_fs_mask
			   << i2s_data->i2s_asrc_fs_shअगरt,
			   fs << i2s_data->i2s_asrc_fs_shअगरt);

	/* enable i2s */
	mt2701_afe_enable_i2s(afe, i2s_path, stream_dir);

	/* reset i2s hw status beक्रमe enable */
	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg,
			   ASYS_I2S_CON_RESET, ASYS_I2S_CON_RESET);
	udelay(1);
	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg,
			   ASYS_I2S_CON_RESET, 0);
	udelay(1);
	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg,
			   ASYS_I2S_CON_I2S_EN, ASYS_I2S_CON_I2S_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक mt2701_afe_i2s_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret, i2s_num = mt2701_dai_num_to_i2s(afe, dai->id);
	काष्ठा mt2701_i2s_path *i2s_path;
	bool mode = afe_priv->soc->has_one_heart_mode;

	अगर (i2s_num < 0)
		वापस i2s_num;

	i2s_path = &afe_priv->i2s_path[i2s_num];

	अगर (i2s_path->occupied[substream->stream])
		वापस -EBUSY;

	ret = mt2701_mclk_configuration(afe, mode ? 1 : i2s_num);
	अगर (ret)
		वापस ret;

	i2s_path->occupied[substream->stream] = 1;

	/* need to enable i2s-out path when enable i2s-in */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mt2701_i2s_path_enable(afe, i2s_path, !substream->stream,
				       substream->runसमय->rate);

	mt2701_i2s_path_enable(afe, i2s_path, substream->stream,
			       substream->runसमय->rate);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2701_afe_i2s_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i2s_num = mt2701_dai_num_to_i2s(afe, dai->id);
	bool mode = afe_priv->soc->has_one_heart_mode;

	अगर (i2s_num < 0)
		वापस i2s_num;

	/* mclk */
	अगर (dir == SND_SOC_CLOCK_IN) अणु
		dev_warn(dai->dev, "The SoCs doesn't support mclk input\n");
		वापस -EINVAL;
	पूर्ण

	afe_priv->i2s_path[mode ? 1 : i2s_num].mclk_rate = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक mt2701_bपंचांगrg_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = mt2701_enable_bपंचांगrg_clk(afe);
	अगर (ret)
		वापस ret;

	afe_priv->mrg_enable[substream->stream] = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mt2701_bपंचांगrg_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक stream_fs;
	u32 val, msk;

	stream_fs = params_rate(params);

	अगर (stream_fs != 8000 && stream_fs != 16000) अणु
		dev_err(afe->dev, "unsupported rate %d\n", stream_fs);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_I2S_MODE_MASK,
			   AFE_MRGIF_CON_I2S_MODE_32K);

	val = AFE_DAIBT_CON0_BT_FUNC_EN | AFE_DAIBT_CON0_BT_FUNC_RDY
	      | AFE_DAIBT_CON0_MRG_USE;
	msk = val;

	अगर (stream_fs == 16000)
		val |= AFE_DAIBT_CON0_BT_WIDE_MODE_EN;

	msk |= AFE_DAIBT_CON0_BT_WIDE_MODE_EN;

	regmap_update_bits(afe->regmap, AFE_DAIBT_CON0, msk, val);

	regmap_update_bits(afe->regmap, AFE_DAIBT_CON0,
			   AFE_DAIBT_CON0_DAIBT_EN,
			   AFE_DAIBT_CON0_DAIBT_EN);
	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_MRG_I2S_EN,
			   AFE_MRGIF_CON_MRG_I2S_EN);
	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_MRG_EN,
			   AFE_MRGIF_CON_MRG_EN);
	वापस 0;
पूर्ण

अटल व्योम mt2701_bपंचांगrg_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;

	/* अगर the other direction stream is not occupied */
	अगर (!afe_priv->mrg_enable[!substream->stream]) अणु
		regmap_update_bits(afe->regmap, AFE_DAIBT_CON0,
				   AFE_DAIBT_CON0_DAIBT_EN, 0);
		regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
				   AFE_MRGIF_CON_MRG_EN, 0);
		regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
				   AFE_MRGIF_CON_MRG_I2S_EN, 0);
		mt2701_disable_bपंचांगrg_clk(afe);
	पूर्ण

	afe_priv->mrg_enable[substream->stream] = 0;
पूर्ण

अटल पूर्णांक mt2701_simple_fe_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mtk_base_afe_memअगर *memअगर_पंचांगp;
	पूर्णांक stream_dir = substream->stream;

	/* can't run single DL & DLM at the same समय */
	अगर (stream_dir == SNDRV_PCM_STREAM_PLAYBACK) अणु
		memअगर_पंचांगp = &afe->memअगर[MT2701_MEMIF_DLM];
		अगर (memअगर_पंचांगp->substream) अणु
			dev_warn(afe->dev, "memif is not available");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस mtk_afe_fe_startup(substream, dai);
पूर्ण

अटल पूर्णांक mt2701_simple_fe_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक stream_dir = substream->stream;

	/* single DL use PAIR_INTERLEAVE */
	अगर (stream_dir == SNDRV_PCM_STREAM_PLAYBACK)
		regmap_update_bits(afe->regmap,
				   AFE_MEMIF_PBUF_SIZE,
				   AFE_MEMIF_PBUF_SIZE_DLM_MASK,
				   AFE_MEMIF_PBUF_SIZE_PAIR_INTERLEAVE);

	वापस mtk_afe_fe_hw_params(substream, params, dai);
पूर्ण

अटल पूर्णांक mt2701_dlm_fe_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mtk_base_afe_memअगर *memअगर_पंचांगp;
	स्थिर काष्ठा mtk_base_memअगर_data *memअगर_data;
	पूर्णांक i;

	क्रम (i = MT2701_MEMIF_DL1; i < MT2701_MEMIF_DL_SINGLE_NUM; ++i) अणु
		memअगर_पंचांगp = &afe->memअगर[i];
		अगर (memअगर_पंचांगp->substream)
			वापस -EBUSY;
	पूर्ण

	/* enable agent क्रम all संकेत DL (due to hw design) */
	क्रम (i = MT2701_MEMIF_DL1; i < MT2701_MEMIF_DL_SINGLE_NUM; ++i) अणु
		memअगर_data = afe->memअगर[i].data;
		regmap_update_bits(afe->regmap,
				   memअगर_data->agent_disable_reg,
				   1 << memअगर_data->agent_disable_shअगरt,
				   0 << memअगर_data->agent_disable_shअगरt);
	पूर्ण

	वापस mtk_afe_fe_startup(substream, dai);
पूर्ण

अटल व्योम mt2701_dlm_fe_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	स्थिर काष्ठा mtk_base_memअगर_data *memअगर_data;
	पूर्णांक i;

	क्रम (i = MT2701_MEMIF_DL1; i < MT2701_MEMIF_DL_SINGLE_NUM; ++i) अणु
		memअगर_data = afe->memअगर[i].data;
		regmap_update_bits(afe->regmap,
				   memअगर_data->agent_disable_reg,
				   1 << memअगर_data->agent_disable_shअगरt,
				   1 << memअगर_data->agent_disable_shअगरt);
	पूर्ण

	वापस mtk_afe_fe_shutकरोwn(substream, dai);
पूर्ण

अटल पूर्णांक mt2701_dlm_fe_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक channels = params_channels(params);

	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_MASK,
			   AFE_MEMIF_PBUF_SIZE_FULL_INTERLEAVE);
	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_BYTE_MASK,
			   AFE_MEMIF_PBUF_SIZE_DLM_32BYTES);
	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_CH_MASK,
			   AFE_MEMIF_PBUF_SIZE_DLM_CH(channels));

	वापस mtk_afe_fe_hw_params(substream, params, dai);
पूर्ण

अटल पूर्णांक mt2701_dlm_fe_trigger(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mtk_base_afe_memअगर *memअगर_पंचांगp = &afe->memअगर[MT2701_MEMIF_DL1];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		regmap_update_bits(afe->regmap, memअगर_पंचांगp->data->enable_reg,
				   1 << memअगर_पंचांगp->data->enable_shअगरt,
				   1 << memअगर_पंचांगp->data->enable_shअगरt);
		mtk_afe_fe_trigger(substream, cmd, dai);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		mtk_afe_fe_trigger(substream, cmd, dai);
		regmap_update_bits(afe->regmap, memअगर_पंचांगp->data->enable_reg,
				   1 << memअगर_पंचांगp->data->enable_shअगरt, 0);

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt2701_memअगर_fs(काष्ठा snd_pcm_substream *substream,
			   अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक fs;

	अगर (asoc_rtd_to_cpu(rtd, 0)->id != MT2701_MEMIF_ULBT)
		fs = mt2701_afe_i2s_fs(rate);
	अन्यथा
		fs = (rate == 16000 ? 1 : 0);

	वापस fs;
पूर्ण

अटल पूर्णांक mt2701_irq_fs(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक rate)
अणु
	वापस mt2701_afe_i2s_fs(rate);
पूर्ण

/* FE DAIs */
अटल स्थिर काष्ठा snd_soc_dai_ops mt2701_single_memअगर_dai_ops = अणु
	.startup	= mt2701_simple_fe_startup,
	.shutकरोwn	= mtk_afe_fe_shutकरोwn,
	.hw_params	= mt2701_simple_fe_hw_params,
	.hw_मुक्त	= mtk_afe_fe_hw_मुक्त,
	.prepare	= mtk_afe_fe_prepare,
	.trigger	= mtk_afe_fe_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops mt2701_dlm_memअगर_dai_ops = अणु
	.startup	= mt2701_dlm_fe_startup,
	.shutकरोwn	= mt2701_dlm_fe_shutकरोwn,
	.hw_params	= mt2701_dlm_fe_hw_params,
	.hw_मुक्त	= mtk_afe_fe_hw_मुक्त,
	.prepare	= mtk_afe_fe_prepare,
	.trigger	= mt2701_dlm_fe_trigger,
पूर्ण;

/* I2S BE DAIs */
अटल स्थिर काष्ठा snd_soc_dai_ops mt2701_afe_i2s_ops = अणु
	.startup	= mt2701_afe_i2s_startup,
	.shutकरोwn	= mt2701_afe_i2s_shutकरोwn,
	.prepare	= mt2701_afe_i2s_prepare,
	.set_sysclk	= mt2701_afe_i2s_set_sysclk,
पूर्ण;

/* MRG BE DAIs */
अटल स्थिर काष्ठा snd_soc_dai_ops mt2701_bपंचांगrg_ops = अणु
	.startup = mt2701_bपंचांगrg_startup,
	.shutकरोwn = mt2701_bपंचांगrg_shutकरोwn,
	.hw_params = mt2701_bपंचांगrg_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mt2701_afe_pcm_dais[] = अणु
	/* FE DAIs: memory पूर्णांकefaces to CPU */
	अणु
		.name = "PCMO0",
		.id = MT2701_MEMIF_DL1,
		.playback = अणु
			.stream_name = "DL1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
		पूर्ण,
		.ops = &mt2701_single_memअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "PCM_multi",
		.id = MT2701_MEMIF_DLM,
		.playback = अणु
			.stream_name = "DLM",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)

		पूर्ण,
		.ops = &mt2701_dlm_memअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "PCM0",
		.id = MT2701_MEMIF_UL1,
		.capture = अणु
			.stream_name = "UL1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
		पूर्ण,
		.ops = &mt2701_single_memअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "PCM1",
		.id = MT2701_MEMIF_UL2,
		.capture = अणु
			.stream_name = "UL2",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)

		पूर्ण,
		.ops = &mt2701_single_memअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "PCM_BT_DL",
		.id = MT2701_MEMIF_DLBT,
		.playback = अणु
			.stream_name = "DLBT",
			.channels_min = 1,
			.channels_max = 1,
			.rates = (SNDRV_PCM_RATE_8000
				| SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mt2701_single_memअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "PCM_BT_UL",
		.id = MT2701_MEMIF_ULBT,
		.capture = अणु
			.stream_name = "ULBT",
			.channels_min = 1,
			.channels_max = 1,
			.rates = (SNDRV_PCM_RATE_8000
				| SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mt2701_single_memअगर_dai_ops,
	पूर्ण,
	/* BE DAIs */
	अणु
		.name = "I2S0",
		.id = MT2701_IO_I2S,
		.playback = अणु
			.stream_name = "I2S0 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)

		पूर्ण,
		.capture = अणु
			.stream_name = "I2S0 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)

		पूर्ण,
		.ops = &mt2701_afe_i2s_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "I2S1",
		.id = MT2701_IO_2ND_I2S,
		.playback = अणु
			.stream_name = "I2S1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.capture = अणु
			.stream_name = "I2S1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.ops = &mt2701_afe_i2s_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "I2S2",
		.id = MT2701_IO_3RD_I2S,
		.playback = अणु
			.stream_name = "I2S2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.capture = अणु
			.stream_name = "I2S2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.ops = &mt2701_afe_i2s_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "I2S3",
		.id = MT2701_IO_4TH_I2S,
		.playback = अणु
			.stream_name = "I2S3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.capture = अणु
			.stream_name = "I2S3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE)
			पूर्ण,
		.ops = &mt2701_afe_i2s_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "MRG BT",
		.id = MT2701_IO_MRG,
		.playback = अणु
			.stream_name = "BT Playback",
			.channels_min = 1,
			.channels_max = 1,
			.rates = (SNDRV_PCM_RATE_8000
				| SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "BT Capture",
			.channels_min = 1,
			.channels_max = 1,
			.rates = (SNDRV_PCM_RATE_8000
				| SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mt2701_bपंचांगrg_ops,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o00_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I00 Switch", AFE_CONN0, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o01_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I01 Switch", AFE_CONN1, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o02_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I02 Switch", AFE_CONN2, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o03_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I03 Switch", AFE_CONN3, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o14_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I26 Switch", AFE_CONN14, 26, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o15_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I12 Switch", AFE_CONN15, 12, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o16_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I13 Switch", AFE_CONN16, 13, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o17_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I14 Switch", AFE_CONN17, 14, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o18_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I15 Switch", AFE_CONN18, 15, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o19_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I16 Switch", AFE_CONN19, 16, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o20_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I17 Switch", AFE_CONN20, 17, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o21_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I18 Switch", AFE_CONN21, 18, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o22_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I19 Switch", AFE_CONN22, 19, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_o31_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I35 Switch", AFE_CONN41, 9, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_i02_mix[] = अणु
	SOC_DAPM_SINGLE("I2S0 Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_multi_ch_out_i2s0[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Multich I2S0 Out Switch",
				    ASYS_I2SO1_CON, 26, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_multi_ch_out_i2s1[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Multich I2S1 Out Switch",
				    ASYS_I2SO2_CON, 26, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_multi_ch_out_i2s2[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Multich I2S2 Out Switch",
				    PWR2_TOP_CON, 17, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_afe_multi_ch_out_i2s3[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Multich I2S3 Out Switch",
				    PWR2_TOP_CON, 18, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mt2701_afe_pcm_widमाला_लो[] = अणु
	/* पूर्णांकer-connections */
	SND_SOC_DAPM_MIXER("I00", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I01", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I02", SND_SOC_NOPM, 0, 0, mt2701_afe_i02_mix,
			   ARRAY_SIZE(mt2701_afe_i02_mix)),
	SND_SOC_DAPM_MIXER("I03", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I12", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I13", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I14", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I15", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I16", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I17", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I18", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I19", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I26", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I35", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("O00", SND_SOC_NOPM, 0, 0, mt2701_afe_o00_mix,
			   ARRAY_SIZE(mt2701_afe_o00_mix)),
	SND_SOC_DAPM_MIXER("O01", SND_SOC_NOPM, 0, 0, mt2701_afe_o01_mix,
			   ARRAY_SIZE(mt2701_afe_o01_mix)),
	SND_SOC_DAPM_MIXER("O02", SND_SOC_NOPM, 0, 0, mt2701_afe_o02_mix,
			   ARRAY_SIZE(mt2701_afe_o02_mix)),
	SND_SOC_DAPM_MIXER("O03", SND_SOC_NOPM, 0, 0, mt2701_afe_o03_mix,
			   ARRAY_SIZE(mt2701_afe_o03_mix)),
	SND_SOC_DAPM_MIXER("O14", SND_SOC_NOPM, 0, 0, mt2701_afe_o14_mix,
			   ARRAY_SIZE(mt2701_afe_o14_mix)),
	SND_SOC_DAPM_MIXER("O15", SND_SOC_NOPM, 0, 0, mt2701_afe_o15_mix,
			   ARRAY_SIZE(mt2701_afe_o15_mix)),
	SND_SOC_DAPM_MIXER("O16", SND_SOC_NOPM, 0, 0, mt2701_afe_o16_mix,
			   ARRAY_SIZE(mt2701_afe_o16_mix)),
	SND_SOC_DAPM_MIXER("O17", SND_SOC_NOPM, 0, 0, mt2701_afe_o17_mix,
			   ARRAY_SIZE(mt2701_afe_o17_mix)),
	SND_SOC_DAPM_MIXER("O18", SND_SOC_NOPM, 0, 0, mt2701_afe_o18_mix,
			   ARRAY_SIZE(mt2701_afe_o18_mix)),
	SND_SOC_DAPM_MIXER("O19", SND_SOC_NOPM, 0, 0, mt2701_afe_o19_mix,
			   ARRAY_SIZE(mt2701_afe_o19_mix)),
	SND_SOC_DAPM_MIXER("O20", SND_SOC_NOPM, 0, 0, mt2701_afe_o20_mix,
			   ARRAY_SIZE(mt2701_afe_o20_mix)),
	SND_SOC_DAPM_MIXER("O21", SND_SOC_NOPM, 0, 0, mt2701_afe_o21_mix,
			   ARRAY_SIZE(mt2701_afe_o21_mix)),
	SND_SOC_DAPM_MIXER("O22", SND_SOC_NOPM, 0, 0, mt2701_afe_o22_mix,
			   ARRAY_SIZE(mt2701_afe_o22_mix)),
	SND_SOC_DAPM_MIXER("O31", SND_SOC_NOPM, 0, 0, mt2701_afe_o31_mix,
			   ARRAY_SIZE(mt2701_afe_o31_mix)),

	SND_SOC_DAPM_MIXER("I12I13", SND_SOC_NOPM, 0, 0,
			   mt2701_afe_multi_ch_out_i2s0,
			   ARRAY_SIZE(mt2701_afe_multi_ch_out_i2s0)),
	SND_SOC_DAPM_MIXER("I14I15", SND_SOC_NOPM, 0, 0,
			   mt2701_afe_multi_ch_out_i2s1,
			   ARRAY_SIZE(mt2701_afe_multi_ch_out_i2s1)),
	SND_SOC_DAPM_MIXER("I16I17", SND_SOC_NOPM, 0, 0,
			   mt2701_afe_multi_ch_out_i2s2,
			   ARRAY_SIZE(mt2701_afe_multi_ch_out_i2s2)),
	SND_SOC_DAPM_MIXER("I18I19", SND_SOC_NOPM, 0, 0,
			   mt2701_afe_multi_ch_out_i2s3,
			   ARRAY_SIZE(mt2701_afe_multi_ch_out_i2s3)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt2701_afe_pcm_routes[] = अणु
	अणु"I12", शून्य, "DL1"पूर्ण,
	अणु"I13", शून्य, "DL1"पूर्ण,
	अणु"I35", शून्य, "DLBT"पूर्ण,

	अणु"I2S0 Playback", शून्य, "O15"पूर्ण,
	अणु"I2S0 Playback", शून्य, "O16"पूर्ण,
	अणु"I2S1 Playback", शून्य, "O17"पूर्ण,
	अणु"I2S1 Playback", शून्य, "O18"पूर्ण,
	अणु"I2S2 Playback", शून्य, "O19"पूर्ण,
	अणु"I2S2 Playback", शून्य, "O20"पूर्ण,
	अणु"I2S3 Playback", शून्य, "O21"पूर्ण,
	अणु"I2S3 Playback", शून्य, "O22"पूर्ण,
	अणु"BT Playback", शून्य, "O31"पूर्ण,

	अणु"UL1", शून्य, "O00"पूर्ण,
	अणु"UL1", शून्य, "O01"पूर्ण,
	अणु"UL2", शून्य, "O02"पूर्ण,
	अणु"UL2", शून्य, "O03"पूर्ण,
	अणु"ULBT", शून्य, "O14"पूर्ण,

	अणु"I00", शून्य, "I2S0 Capture"पूर्ण,
	अणु"I01", शून्य, "I2S0 Capture"पूर्ण,
	अणु"I02", शून्य, "I2S1 Capture"पूर्ण,
	अणु"I03", शून्य, "I2S1 Capture"पूर्ण,
	/* I02,03 link to UL2, also need to खोलो I2S0 */
	अणु"I02", "I2S0 Switch", "I2S0 Capture"पूर्ण,

	अणु"I26", शून्य, "BT Capture"पूर्ण,

	अणु"I12I13", "Multich I2S0 Out Switch", "DLM"पूर्ण,
	अणु"I14I15", "Multich I2S1 Out Switch", "DLM"पूर्ण,
	अणु"I16I17", "Multich I2S2 Out Switch", "DLM"पूर्ण,
	अणु"I18I19", "Multich I2S3 Out Switch", "DLM"पूर्ण,

	अणु "I12", शून्य, "I12I13" पूर्ण,
	अणु "I13", शून्य, "I12I13" पूर्ण,
	अणु "I14", शून्य, "I14I15" पूर्ण,
	अणु "I15", शून्य, "I14I15" पूर्ण,
	अणु "I16", शून्य, "I16I17" पूर्ण,
	अणु "I17", शून्य, "I16I17" पूर्ण,
	अणु "I18", शून्य, "I18I19" पूर्ण,
	अणु "I19", शून्य, "I18I19" पूर्ण,

	अणु "O00", "I00 Switch", "I00" पूर्ण,
	अणु "O01", "I01 Switch", "I01" पूर्ण,
	अणु "O02", "I02 Switch", "I02" पूर्ण,
	अणु "O03", "I03 Switch", "I03" पूर्ण,
	अणु "O14", "I26 Switch", "I26" पूर्ण,
	अणु "O15", "I12 Switch", "I12" पूर्ण,
	अणु "O16", "I13 Switch", "I13" पूर्ण,
	अणु "O17", "I14 Switch", "I14" पूर्ण,
	अणु "O18", "I15 Switch", "I15" पूर्ण,
	अणु "O19", "I16 Switch", "I16" पूर्ण,
	अणु "O20", "I17 Switch", "I17" पूर्ण,
	अणु "O21", "I18 Switch", "I18" पूर्ण,
	अणु "O22", "I19 Switch", "I19" पूर्ण,
	अणु "O31", "I35 Switch", "I35" पूर्ण,
पूर्ण;

अटल पूर्णांक mt2701_afe_pcm_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);

	snd_soc_component_init_regmap(component, afe->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt2701_afe_pcm_dai_component = अणु
	.probe = mt2701_afe_pcm_probe,
	.name = "mt2701-afe-pcm-dai",
	.dapm_widमाला_लो = mt2701_afe_pcm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt2701_afe_pcm_widमाला_लो),
	.dapm_routes = mt2701_afe_pcm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt2701_afe_pcm_routes),
	.suspend = mtk_afe_suspend,
	.resume = mtk_afe_resume,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_memअगर_data memअगर_data_array[MT2701_MEMIF_NUM] = अणु
	अणु
		.name = "DL1",
		.id = MT2701_MEMIF_DL1,
		.reg_ofs_base = AFE_DL1_BASE,
		.reg_ofs_cur = AFE_DL1_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 0,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 16,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 1,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 0,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 6,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DL2",
		.id = MT2701_MEMIF_DL2,
		.reg_ofs_base = AFE_DL2_BASE,
		.reg_ofs_cur = AFE_DL2_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 5,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 17,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 2,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 2,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 7,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DL3",
		.id = MT2701_MEMIF_DL3,
		.reg_ofs_base = AFE_DL3_BASE,
		.reg_ofs_cur = AFE_DL3_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 10,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 18,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 3,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 4,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 8,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DL4",
		.id = MT2701_MEMIF_DL4,
		.reg_ofs_base = AFE_DL4_BASE,
		.reg_ofs_cur = AFE_DL4_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 15,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 19,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 4,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 6,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 9,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DL5",
		.id = MT2701_MEMIF_DL5,
		.reg_ofs_base = AFE_DL5_BASE,
		.reg_ofs_cur = AFE_DL5_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 20,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 20,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 5,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 8,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 10,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DLM",
		.id = MT2701_MEMIF_DLM,
		.reg_ofs_base = AFE_DLMCH_BASE,
		.reg_ofs_cur = AFE_DLMCH_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 0,
		.fs_maskbit = 0x1f,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 7,
		.hd_reg = AFE_MEMIF_PBUF_SIZE,
		.hd_shअगरt = 28,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 12,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "UL1",
		.id = MT2701_MEMIF_UL1,
		.reg_ofs_base = AFE_VUL_BASE,
		.reg_ofs_cur = AFE_VUL_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 0,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON4,
		.mono_shअगरt = 0,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 10,
		.hd_reg = AFE_MEMIF_HD_CON1,
		.hd_shअगरt = 0,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 0,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "UL2",
		.id = MT2701_MEMIF_UL2,
		.reg_ofs_base = AFE_UL2_BASE,
		.reg_ofs_cur = AFE_UL2_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 5,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON4,
		.mono_shअगरt = 2,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 11,
		.hd_reg = AFE_MEMIF_HD_CON1,
		.hd_shअगरt = 2,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 1,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "UL3",
		.id = MT2701_MEMIF_UL3,
		.reg_ofs_base = AFE_UL3_BASE,
		.reg_ofs_cur = AFE_UL3_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 10,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON4,
		.mono_shअगरt = 4,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 12,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 0,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 2,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "UL4",
		.id = MT2701_MEMIF_UL4,
		.reg_ofs_base = AFE_UL4_BASE,
		.reg_ofs_cur = AFE_UL4_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 15,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON4,
		.mono_shअगरt = 6,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 13,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 6,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 3,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "UL5",
		.id = MT2701_MEMIF_UL5,
		.reg_ofs_base = AFE_UL5_BASE,
		.reg_ofs_cur = AFE_UL5_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 20,
		.mono_reg = AFE_DAC_CON4,
		.mono_shअगरt = 8,
		.fs_maskbit = 0x1f,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 14,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 8,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 4,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "DLBT",
		.id = MT2701_MEMIF_DLBT,
		.reg_ofs_base = AFE_ARB1_BASE,
		.reg_ofs_cur = AFE_ARB1_CUR,
		.fs_reg = AFE_DAC_CON3,
		.fs_shअगरt = 10,
		.fs_maskbit = 0x1f,
		.mono_reg = AFE_DAC_CON3,
		.mono_shअगरt = 22,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 8,
		.hd_reg = AFE_MEMIF_HD_CON0,
		.hd_shअगरt = 14,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 13,
		.msb_reg = -1,
	पूर्ण,
	अणु
		.name = "ULBT",
		.id = MT2701_MEMIF_ULBT,
		.reg_ofs_base = AFE_DAI_BASE,
		.reg_ofs_cur = AFE_DAI_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = 30,
		.fs_maskbit = 0x1,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 17,
		.hd_reg = AFE_MEMIF_HD_CON1,
		.hd_shअगरt = 20,
		.agent_disable_reg = AUDIO_TOP_CON5,
		.agent_disable_shअगरt = 16,
		.msb_reg = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_irq_data irq_data[MT2701_IRQ_ASYS_END] = अणु
	अणु
		.id = MT2701_IRQ_ASYS_IRQ1,
		.irq_cnt_reg = ASYS_IRQ1_CON,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0xffffff,
		.irq_fs_reg = ASYS_IRQ1_CON,
		.irq_fs_shअगरt = 24,
		.irq_fs_maskbit = 0x1f,
		.irq_en_reg = ASYS_IRQ1_CON,
		.irq_en_shअगरt = 31,
		.irq_clr_reg = ASYS_IRQ_CLR,
		.irq_clr_shअगरt = 0,
	पूर्ण,
	अणु
		.id = MT2701_IRQ_ASYS_IRQ2,
		.irq_cnt_reg = ASYS_IRQ2_CON,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0xffffff,
		.irq_fs_reg = ASYS_IRQ2_CON,
		.irq_fs_shअगरt = 24,
		.irq_fs_maskbit = 0x1f,
		.irq_en_reg = ASYS_IRQ2_CON,
		.irq_en_shअगरt = 31,
		.irq_clr_reg = ASYS_IRQ_CLR,
		.irq_clr_shअगरt = 1,
	पूर्ण,
	अणु
		.id = MT2701_IRQ_ASYS_IRQ3,
		.irq_cnt_reg = ASYS_IRQ3_CON,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0xffffff,
		.irq_fs_reg = ASYS_IRQ3_CON,
		.irq_fs_shअगरt = 24,
		.irq_fs_maskbit = 0x1f,
		.irq_en_reg = ASYS_IRQ3_CON,
		.irq_en_shअगरt = 31,
		.irq_clr_reg = ASYS_IRQ_CLR,
		.irq_clr_shअगरt = 2,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा mt2701_i2s_data mt2701_i2s_data[][2] = अणु
	अणु
		अणु ASYS_I2SO1_CON, 0, 0x1f पूर्ण,
		अणु ASYS_I2SIN1_CON, 0, 0x1f पूर्ण,
	पूर्ण,
	अणु
		अणु ASYS_I2SO2_CON, 5, 0x1f पूर्ण,
		अणु ASYS_I2SIN2_CON, 5, 0x1f पूर्ण,
	पूर्ण,
	अणु
		अणु ASYS_I2SO3_CON, 10, 0x1f पूर्ण,
		अणु ASYS_I2SIN3_CON, 10, 0x1f पूर्ण,
	पूर्ण,
	अणु
		अणु ASYS_I2SO4_CON, 15, 0x1f पूर्ण,
		अणु ASYS_I2SIN4_CON, 15, 0x1f पूर्ण,
	पूर्ण,
	/* TODO - extend control रेजिस्टरs supported by newer SoCs */
पूर्ण;

अटल irqवापस_t mt2701_asys_isr(पूर्णांक irq_id, व्योम *dev)
अणु
	पूर्णांक id;
	काष्ठा mtk_base_afe *afe = dev;
	काष्ठा mtk_base_afe_memअगर *memअगर;
	काष्ठा mtk_base_afe_irq *irq;
	u32 status;

	regmap_पढ़ो(afe->regmap, ASYS_IRQ_STATUS, &status);
	regmap_ग_लिखो(afe->regmap, ASYS_IRQ_CLR, status);

	क्रम (id = 0; id < MT2701_MEMIF_NUM; ++id) अणु
		memअगर = &afe->memअगर[id];
		अगर (memअगर->irq_usage < 0)
			जारी;

		irq = &afe->irqs[memअगर->irq_usage];
		अगर (status & 1 << irq->irq_data->irq_clr_shअगरt)
			snd_pcm_period_elapsed(memअगर->substream);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mt2701_afe_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);

	वापस mt2701_afe_disable_घड़ी(afe);
पूर्ण

अटल पूर्णांक mt2701_afe_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);

	वापस mt2701_afe_enable_घड़ी(afe);
पूर्ण

अटल पूर्णांक mt2701_afe_pcm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_base_afe *afe;
	काष्ठा mt2701_afe_निजी *afe_priv;
	काष्ठा device *dev;
	पूर्णांक i, irq_id, ret;

	afe = devm_kzalloc(&pdev->dev, माप(*afe), GFP_KERNEL);
	अगर (!afe)
		वापस -ENOMEM;

	afe->platक्रमm_priv = devm_kzalloc(&pdev->dev, माप(*afe_priv),
					  GFP_KERNEL);
	अगर (!afe->platक्रमm_priv)
		वापस -ENOMEM;

	afe_priv = afe->platक्रमm_priv;
	afe_priv->soc = of_device_get_match_data(&pdev->dev);
	afe->dev = &pdev->dev;
	dev = afe->dev;

	afe_priv->i2s_path = devm_kसुस्मृति(dev,
					  afe_priv->soc->i2s_num,
					  माप(काष्ठा mt2701_i2s_path),
					  GFP_KERNEL);
	अगर (!afe_priv->i2s_path)
		वापस -ENOMEM;

	irq_id = platक्रमm_get_irq_byname(pdev, "asys");
	अगर (irq_id < 0)
		वापस irq_id;

	ret = devm_request_irq(dev, irq_id, mt2701_asys_isr,
			       IRQF_TRIGGER_NONE, "asys-isr", (व्योम *)afe);
	अगर (ret) अणु
		dev_err(dev, "could not request_irq for asys-isr\n");
		वापस ret;
	पूर्ण

	afe->regmap = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(afe->regmap)) अणु
		dev_err(dev, "could not get regmap from parent\n");
		वापस PTR_ERR(afe->regmap);
	पूर्ण

	mutex_init(&afe->irq_alloc_lock);

	/* memअगर initialize */
	afe->memअगर_size = MT2701_MEMIF_NUM;
	afe->memअगर = devm_kसुस्मृति(dev, afe->memअगर_size, माप(*afe->memअगर),
				  GFP_KERNEL);
	अगर (!afe->memअगर)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->memअगर_size; i++) अणु
		afe->memअगर[i].data = &memअगर_data_array[i];
		afe->memअगर[i].irq_usage = -1;
	पूर्ण

	/* irq initialize */
	afe->irqs_size = MT2701_IRQ_ASYS_END;
	afe->irqs = devm_kसुस्मृति(dev, afe->irqs_size, माप(*afe->irqs),
				 GFP_KERNEL);
	अगर (!afe->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->irqs_size; i++)
		afe->irqs[i].irq_data = &irq_data[i];

	/* I2S initialize */
	क्रम (i = 0; i < afe_priv->soc->i2s_num; i++) अणु
		afe_priv->i2s_path[i].i2s_data[SNDRV_PCM_STREAM_PLAYBACK] =
			&mt2701_i2s_data[i][SNDRV_PCM_STREAM_PLAYBACK];
		afe_priv->i2s_path[i].i2s_data[SNDRV_PCM_STREAM_CAPTURE] =
			&mt2701_i2s_data[i][SNDRV_PCM_STREAM_CAPTURE];
	पूर्ण

	afe->mtk_afe_hardware = &mt2701_afe_hardware;
	afe->memअगर_fs = mt2701_memअगर_fs;
	afe->irq_fs = mt2701_irq_fs;
	afe->reg_back_up_list = mt2701_afe_backup_list;
	afe->reg_back_up_list_num = ARRAY_SIZE(mt2701_afe_backup_list);
	afe->runसमय_resume = mt2701_afe_runसमय_resume;
	afe->runसमय_suspend = mt2701_afe_runसमय_suspend;

	/* initial audio related घड़ी */
	ret = mt2701_init_घड़ी(afe);
	अगर (ret) अणु
		dev_err(dev, "init clock error\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, afe);

	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = mt2701_afe_runसमय_resume(dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण
	pm_runसमय_get_sync(dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &mtk_afe_pcm_platक्रमm,
					      शून्य, 0);
	अगर (ret) अणु
		dev_warn(dev, "err_platform\n");
		जाओ err_platक्रमm;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					 &mt2701_afe_pcm_dai_component,
					 mt2701_afe_pcm_dais,
					 ARRAY_SIZE(mt2701_afe_pcm_dais));
	अगर (ret) अणु
		dev_warn(dev, "err_dai_component\n");
		जाओ err_platक्रमm;
	पूर्ण

	वापस 0;

err_platक्रमm:
	pm_runसमय_put_sync(dev);
err_pm_disable:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mt2701_afe_pcm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mt2701_afe_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mt2701_soc_variants mt2701_soc_v1 = अणु
	.i2s_num = 4,
पूर्ण;

अटल स्थिर काष्ठा mt2701_soc_variants mt2701_soc_v2 = अणु
	.has_one_heart_mode = true,
	.i2s_num = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt2701_afe_pcm_dt_match[] = अणु
	अणु .compatible = "mediatek,mt2701-audio", .data = &mt2701_soc_v1 पूर्ण,
	अणु .compatible = "mediatek,mt7622-audio", .data = &mt2701_soc_v2 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt2701_afe_pcm_dt_match);

अटल स्थिर काष्ठा dev_pm_ops mt2701_afe_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt2701_afe_runसमय_suspend,
			   mt2701_afe_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mt2701_afe_pcm_driver = अणु
	.driver = अणु
		   .name = "mt2701-audio",
		   .of_match_table = mt2701_afe_pcm_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &mt2701_afe_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt2701_afe_pcm_dev_probe,
	.हटाओ = mt2701_afe_pcm_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(mt2701_afe_pcm_driver);

MODULE_DESCRIPTION("Mediatek ALSA SoC AFE platform driver for 2701");
MODULE_AUTHOR("Garlic Tseng <garlic.tseng@mediatek.com>");
MODULE_LICENSE("GPL v2");
