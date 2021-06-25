<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra210_i2s.c - Tegra210 I2S driver
//
// Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "tegra210_i2s.h"
#समावेश "tegra_cif.h"

अटल स्थिर काष्ठा reg_शेष tegra210_i2s_reg_शेषs[] = अणु
	अणु TEGRA210_I2S_RX_INT_MASK, 0x00000003 पूर्ण,
	अणु TEGRA210_I2S_RX_CIF_CTRL, 0x00007700 पूर्ण,
	अणु TEGRA210_I2S_TX_INT_MASK, 0x00000003 पूर्ण,
	अणु TEGRA210_I2S_TX_CIF_CTRL, 0x00007700 पूर्ण,
	अणु TEGRA210_I2S_CG, 0x1 पूर्ण,
	अणु TEGRA210_I2S_TIMING, 0x0000001f पूर्ण,
	अणु TEGRA210_I2S_ENABLE, 0x1 पूर्ण,
	/*
	 * Below update करोes not have any effect on Tegra186 and Tegra194.
	 * On Tegra210, I2S4 has "i2s4a" and "i2s4b" pins and below update
	 * is required to select i2s4b क्रम it to be functional क्रम I2S
	 * operation.
	 */
	अणु TEGRA210_I2S_CYA, 0x1 पूर्ण,
पूर्ण;

अटल व्योम tegra210_i2s_set_slot_ctrl(काष्ठा regmap *regmap,
				       अचिन्हित पूर्णांक total_slots,
				       अचिन्हित पूर्णांक tx_slot_mask,
				       अचिन्हित पूर्णांक rx_slot_mask)
अणु
	regmap_ग_लिखो(regmap, TEGRA210_I2S_SLOT_CTRL, total_slots - 1);
	regmap_ग_लिखो(regmap, TEGRA210_I2S_TX_SLOT_CTRL, tx_slot_mask);
	regmap_ग_लिखो(regmap, TEGRA210_I2S_RX_SLOT_CTRL, rx_slot_mask);
पूर्ण

अटल पूर्णांक tegra210_i2s_set_घड़ी_rate(काष्ठा device *dev,
				       अचिन्हित पूर्णांक घड़ी_rate)
अणु
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	regmap_पढ़ो(i2s->regmap, TEGRA210_I2S_CTRL, &val);

	/* No need to set rates अगर I2S is being operated in slave */
	अगर (!(val & I2S_CTRL_MASTER_EN))
		वापस 0;

	err = clk_set_rate(i2s->clk_i2s, घड़ी_rate);
	अगर (err) अणु
		dev_err(dev, "can't set I2S bit clock rate %u, err: %d\n",
			घड़ी_rate, err);
		वापस err;
	पूर्ण

	अगर (!IS_ERR(i2s->clk_sync_input)) अणु
		/*
		 * Other I/O modules in AHUB can use i2s bclk as reference
		 * घड़ी. Below sets sync input घड़ी rate as per bclk,
		 * which can be used as input to other I/O modules.
		 */
		err = clk_set_rate(i2s->clk_sync_input, घड़ी_rate);
		अगर (err) अणु
			dev_err(dev,
				"can't set I2S sync input rate %u, err = %d\n",
				घड़ी_rate, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_sw_reset(काष्ठा snd_soc_component *compnt,
				 bool is_playback)
अणु
	काष्ठा device *dev = compnt->dev;
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reset_mask = I2S_SOFT_RESET_MASK;
	अचिन्हित पूर्णांक reset_en = I2S_SOFT_RESET_EN;
	अचिन्हित पूर्णांक reset_reg, cअगर_reg, stream_reg;
	अचिन्हित पूर्णांक cअगर_ctrl, stream_ctrl, i2s_ctrl, val;
	पूर्णांक err;

	अगर (is_playback) अणु
		reset_reg = TEGRA210_I2S_RX_SOFT_RESET;
		cअगर_reg = TEGRA210_I2S_RX_CIF_CTRL;
		stream_reg = TEGRA210_I2S_RX_CTRL;
	पूर्ण अन्यथा अणु
		reset_reg = TEGRA210_I2S_TX_SOFT_RESET;
		cअगर_reg = TEGRA210_I2S_TX_CIF_CTRL;
		stream_reg = TEGRA210_I2S_TX_CTRL;
	पूर्ण

	/* Store CIF and I2S control values */
	regmap_पढ़ो(i2s->regmap, cअगर_reg, &cअगर_ctrl);
	regmap_पढ़ो(i2s->regmap, stream_reg, &stream_ctrl);
	regmap_पढ़ो(i2s->regmap, TEGRA210_I2S_CTRL, &i2s_ctrl);

	/* Reset to make sure the previous transactions are clean */
	regmap_update_bits(i2s->regmap, reset_reg, reset_mask, reset_en);

	err = regmap_पढ़ो_poll_समयout(i2s->regmap, reset_reg, val,
				       !(val & reset_mask & reset_en),
				       10, 10000);
	अगर (err) अणु
		dev_err(dev, "timeout: failed to reset I2S for %s\n",
			is_playback ? "playback" : "capture");
		वापस err;
	पूर्ण

	/* Restore CIF and I2S control values */
	regmap_ग_लिखो(i2s->regmap, cअगर_reg, cअगर_ctrl);
	regmap_ग_लिखो(i2s->regmap, stream_reg, stream_ctrl);
	regmap_ग_लिखो(i2s->regmap, TEGRA210_I2S_CTRL, i2s_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_init(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *compnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा device *dev = compnt->dev;
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val, status_reg;
	bool is_playback;
	पूर्णांक err;

	चयन (w->reg) अणु
	हाल TEGRA210_I2S_RX_ENABLE:
		is_playback = true;
		status_reg = TEGRA210_I2S_RX_STATUS;
		अवरोध;
	हाल TEGRA210_I2S_TX_ENABLE:
		is_playback = false;
		status_reg = TEGRA210_I2S_TX_STATUS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Ensure I2S is in disabled state beक्रमe new session */
	err = regmap_पढ़ो_poll_समयout(i2s->regmap, status_reg, val,
				       !(val & I2S_EN_MASK & I2S_EN),
				       10, 10000);
	अगर (err) अणु
		dev_err(dev, "timeout: previous I2S %s is still active\n",
			is_playback ? "playback" : "capture");
		वापस err;
	पूर्ण

	वापस tegra210_i2s_sw_reset(compnt, is_playback);
पूर्ण

अटल पूर्णांक __maybe_unused tegra210_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);
	regcache_mark_dirty(i2s->regmap);

	clk_disable_unprepare(i2s->clk_i2s);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra210_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(i2s->clk_i2s);
	अगर (err) अणु
		dev_err(dev, "failed to enable I2S bit clock, err: %d\n", err);
		वापस err;
	पूर्ण

	regcache_cache_only(i2s->regmap, false);
	regcache_sync(i2s->regmap);

	वापस 0;
पूर्ण

अटल व्योम tegra210_i2s_set_data_offset(काष्ठा tegra210_i2s *i2s,
					 अचिन्हित पूर्णांक data_offset)
अणु
	/* Capture path */
	regmap_update_bits(i2s->regmap, TEGRA210_I2S_TX_CTRL,
			   I2S_CTRL_DATA_OFFSET_MASK,
			   data_offset << I2S_DATA_SHIFT);

	/* Playback path */
	regmap_update_bits(i2s->regmap, TEGRA210_I2S_RX_CTRL,
			   I2S_CTRL_DATA_OFFSET_MASK,
			   data_offset << I2S_DATA_SHIFT);
पूर्ण

अटल पूर्णांक tegra210_i2s_set_fmt(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा tegra210_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask, val;

	mask = I2S_CTRL_MASTER_EN_MASK;
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val = I2S_CTRL_MASTER_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= I2S_CTRL_FRAME_FMT_MASK | I2S_CTRL_LRCK_POL_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		val |= I2S_CTRL_FRAME_FMT_FSYNC_MODE;
		val |= I2S_CTRL_LRCK_POL_HIGH;
		tegra210_i2s_set_data_offset(i2s, 1);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		val |= I2S_CTRL_FRAME_FMT_FSYNC_MODE;
		val |= I2S_CTRL_LRCK_POL_HIGH;
		tegra210_i2s_set_data_offset(i2s, 0);
		अवरोध;
	/* I2S mode has data offset of 1 */
	हाल SND_SOC_DAIFMT_I2S:
		val |= I2S_CTRL_FRAME_FMT_LRCK_MODE;
		val |= I2S_CTRL_LRCK_POL_LOW;
		tegra210_i2s_set_data_offset(i2s, 1);
		अवरोध;
	/*
	 * For RJ mode data offset is dependent on the sample size
	 * and the bclk ratio, and so is set when hw_params is called.
	 */
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val |= I2S_CTRL_FRAME_FMT_LRCK_MODE;
		val |= I2S_CTRL_LRCK_POL_HIGH;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= I2S_CTRL_FRAME_FMT_LRCK_MODE;
		val |= I2S_CTRL_LRCK_POL_HIGH;
		tegra210_i2s_set_data_offset(i2s, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= I2S_CTRL_EDGE_CTRL_MASK;
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		val |= I2S_CTRL_EDGE_CTRL_POS_EDGE;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		val |= I2S_CTRL_EDGE_CTRL_POS_EDGE;
		val ^= I2S_CTRL_LRCK_POL_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		val |= I2S_CTRL_EDGE_CTRL_NEG_EDGE;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		val |= I2S_CTRL_EDGE_CTRL_NEG_EDGE;
		val ^= I2S_CTRL_LRCK_POL_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, TEGRA210_I2S_CTRL, mask, val);

	i2s->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				     अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				     पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा tegra210_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	/* Copy the required tx and rx mask */
	i2s->tx_mask = (tx_mask > DEFAULT_I2S_SLOT_MASK) ?
		       DEFAULT_I2S_SLOT_MASK : tx_mask;
	i2s->rx_mask = (rx_mask > DEFAULT_I2S_SLOT_MASK) ?
		       DEFAULT_I2S_SLOT_MASK : rx_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_set_dai_bclk_ratio(काष्ठा snd_soc_dai *dai,
					   अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा tegra210_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	i2s->bclk_ratio = ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_get_control(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *compnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra210_i2s *i2s = snd_soc_component_get_drvdata(compnt);
	दीर्घ *uctl_val = &ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "Loopback"))
		*uctl_val = i2s->loopback;
	अन्यथा अगर (म_माला(kcontrol->id.name, "FSYNC Width"))
		*uctl_val = i2s->fsync_width;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Stereo To Mono"))
		*uctl_val = i2s->stereo_to_mono[I2S_TX_PATH];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Mono To Stereo"))
		*uctl_val = i2s->mono_to_stereo[I2S_TX_PATH];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Stereo To Mono"))
		*uctl_val = i2s->stereo_to_mono[I2S_RX_PATH];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Mono To Stereo"))
		*uctl_val = i2s->mono_to_stereo[I2S_RX_PATH];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Playback FIFO Threshold"))
		*uctl_val = i2s->rx_fअगरo_th;
	अन्यथा अगर (म_माला(kcontrol->id.name, "BCLK Ratio"))
		*uctl_val = i2s->bclk_ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_put_control(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *compnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra210_i2s *i2s = snd_soc_component_get_drvdata(compnt);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "Loopback")) अणु
		i2s->loopback = value;

		regmap_update_bits(i2s->regmap, TEGRA210_I2S_CTRL,
				   I2S_CTRL_LPBK_MASK,
				   i2s->loopback << I2S_CTRL_LPBK_SHIFT);

	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "FSYNC Width")) अणु
		/*
		 * Frame sync width is used only क्रम FSYNC modes and not
		 * applicable क्रम LRCK modes. Reset value क्रम this field is "0",
		 * which means the width is one bit घड़ी wide.
		 * The width requirement may depend on the codec and in such
		 * हालs mixer control is used to update custom values. A value
		 * of "N" here means, width is "N + 1" bit घड़ी wide.
		 */
		i2s->fsync_width = value;

		regmap_update_bits(i2s->regmap, TEGRA210_I2S_CTRL,
				   I2S_CTRL_FSYNC_WIDTH_MASK,
				   i2s->fsync_width << I2S_FSYNC_WIDTH_SHIFT);

	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Stereo To Mono")) अणु
		i2s->stereo_to_mono[I2S_TX_PATH] = value;
	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Mono To Stereo")) अणु
		i2s->mono_to_stereo[I2S_TX_PATH] = value;
	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Stereo To Mono")) अणु
		i2s->stereo_to_mono[I2S_RX_PATH] = value;
	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Mono To Stereo")) अणु
		i2s->mono_to_stereo[I2S_RX_PATH] = value;
	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "Playback FIFO Threshold")) अणु
		i2s->rx_fअगरo_th = value;
	पूर्ण अन्यथा अगर (म_माला(kcontrol->id.name, "BCLK Ratio")) अणु
		i2s->bclk_ratio = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_set_timing_params(काष्ठा device *dev,
					  अचिन्हित पूर्णांक sample_size,
					  अचिन्हित पूर्णांक srate,
					  अचिन्हित पूर्णांक channels)
अणु
	काष्ठा tegra210_i2s *i2s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val, bit_count, bclk_rate, num_bclk = sample_size;
	पूर्णांक err;

	अगर (i2s->bclk_ratio)
		num_bclk *= i2s->bclk_ratio;

	अगर (i2s->dai_fmt == SND_SOC_DAIFMT_RIGHT_J)
		tegra210_i2s_set_data_offset(i2s, num_bclk - sample_size);

	/* I2S bit घड़ी rate */
	bclk_rate = srate * channels * num_bclk;

	err = tegra210_i2s_set_घड़ी_rate(dev, bclk_rate);
	अगर (err) अणु
		dev_err(dev, "can't set I2S bit clock rate %u, err: %d\n",
			bclk_rate, err);
		वापस err;
	पूर्ण

	regmap_पढ़ो(i2s->regmap, TEGRA210_I2S_CTRL, &val);

	/*
	 * For LRCK mode, channel bit count depends on number of bit घड़ीs
	 * on the left channel, where as क्रम FSYNC mode bit count depends on
	 * the number of bit घड़ीs in both left and right channels क्रम DSP
	 * mode or the number of bit घड़ीs in one TDM frame.
	 *
	 */
	चयन (val & I2S_CTRL_FRAME_FMT_MASK) अणु
	हाल I2S_CTRL_FRAME_FMT_LRCK_MODE:
		bit_count = (bclk_rate / (srate * 2)) - 1;
		अवरोध;
	हाल I2S_CTRL_FRAME_FMT_FSYNC_MODE:
		bit_count = (bclk_rate / srate) - 1;

		tegra210_i2s_set_slot_ctrl(i2s->regmap, channels,
					   i2s->tx_mask, i2s->rx_mask);
		अवरोध;
	शेष:
		dev_err(dev, "invalid I2S frame format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bit_count > I2S_TIMING_CH_BIT_CNT_MASK) अणु
		dev_err(dev, "invalid I2S channel bit count %u\n", bit_count);
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(i2s->regmap, TEGRA210_I2S_TIMING,
		     bit_count << I2S_TIMING_CH_BIT_CNT_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra210_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक sample_size, channels, srate, val, reg, path;
	काष्ठा tegra_cअगर_conf cअगर_conf;

	स_रखो(&cअगर_conf, 0, माप(काष्ठा tegra_cअगर_conf));

	channels = params_channels(params);
	अगर (channels < 1) अणु
		dev_err(dev, "invalid I2S %d channel configuration\n",
			channels);
		वापस -EINVAL;
	पूर्ण

	cअगर_conf.audio_ch = channels;
	cअगर_conf.client_ch = channels;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		val = I2S_BITS_8;
		sample_size = 8;
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_8;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val = I2S_BITS_16;
		sample_size = 16;
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_16;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val = I2S_BITS_32;
		sample_size = 32;
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_32;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_32;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported format!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Program sample size */
	regmap_update_bits(i2s->regmap, TEGRA210_I2S_CTRL,
			   I2S_CTRL_BIT_SIZE_MASK, val);

	srate = params_rate(params);

	/* For playback I2S RX-CIF and क्रम capture TX-CIF is used */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		path = I2S_RX_PATH;
	अन्यथा
		path = I2S_TX_PATH;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अचिन्हित पूर्णांक max_th;

		/* FIFO threshold in terms of frames */
		max_th = (I2S_RX_FIFO_DEPTH / cअगर_conf.audio_ch) - 1;

		अगर (i2s->rx_fअगरo_th > max_th)
			i2s->rx_fअगरo_th = max_th;

		cअगर_conf.threshold = i2s->rx_fअगरo_th;

		reg = TEGRA210_I2S_RX_CIF_CTRL;
	पूर्ण अन्यथा अणु
		reg = TEGRA210_I2S_TX_CIF_CTRL;
	पूर्ण

	cअगर_conf.mono_conv = i2s->mono_to_stereo[path];
	cअगर_conf.stereo_conv = i2s->stereo_to_mono[path];

	tegra_set_cअगर(i2s->regmap, reg, &cअगर_conf);

	वापस tegra210_i2s_set_timing_params(dev, sample_size, srate,
					      cअगर_conf.client_ch);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra210_i2s_dai_ops = अणु
	.set_fmt	= tegra210_i2s_set_fmt,
	.hw_params	= tegra210_i2s_hw_params,
	.set_bclk_ratio	= tegra210_i2s_set_dai_bclk_ratio,
	.set_tdm_slot	= tegra210_i2s_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra210_i2s_dais[] = अणु
	अणु
		.name = "I2S-CIF",
		.playback = अणु
			.stream_name = "CIF-Playback",
			.channels_min = 1,
			.channels_max = 16,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "CIF-Capture",
			.channels_min = 1,
			.channels_max = 16,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "I2S-DAP",
		.playback = अणु
			.stream_name = "DAP-Playback",
			.channels_min = 1,
			.channels_max = 16,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "DAP-Capture",
			.channels_min = 1,
			.channels_max = 16,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &tegra210_i2s_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_i2s_stereo_conv_text[] = अणु
	"CH0", "CH1", "AVG",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_i2s_mono_conv_text[] = अणु
	"Zero", "Copy",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra210_i2s_mono_conv_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_i2s_mono_conv_text),
			tegra210_i2s_mono_conv_text);

अटल स्थिर काष्ठा soc_क्रमागत tegra210_i2s_stereo_conv_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_i2s_stereo_conv_text),
			tegra210_i2s_stereo_conv_text);

अटल स्थिर काष्ठा snd_kcontrol_new tegra210_i2s_controls[] = अणु
	SOC_SINGLE_EXT("Loopback", 0, 0, 1, 0, tegra210_i2s_get_control,
		       tegra210_i2s_put_control),
	SOC_SINGLE_EXT("FSYNC Width", 0, 0, 255, 0, tegra210_i2s_get_control,
		       tegra210_i2s_put_control),
	SOC_ENUM_EXT("Capture Stereo To Mono", tegra210_i2s_stereo_conv_क्रमागत,
		     tegra210_i2s_get_control, tegra210_i2s_put_control),
	SOC_ENUM_EXT("Capture Mono To Stereo", tegra210_i2s_mono_conv_क्रमागत,
		     tegra210_i2s_get_control, tegra210_i2s_put_control),
	SOC_ENUM_EXT("Playback Stereo To Mono", tegra210_i2s_stereo_conv_क्रमागत,
		     tegra210_i2s_get_control, tegra210_i2s_put_control),
	SOC_ENUM_EXT("Playback Mono To Stereo", tegra210_i2s_mono_conv_क्रमागत,
		     tegra210_i2s_get_control, tegra210_i2s_put_control),
	SOC_SINGLE_EXT("Playback FIFO Threshold", 0, 0, I2S_RX_FIFO_DEPTH - 1,
		       0, tegra210_i2s_get_control, tegra210_i2s_put_control),
	SOC_SINGLE_EXT("BCLK Ratio", 0, 0, पूर्णांक_उच्च, 0, tegra210_i2s_get_control,
		       tegra210_i2s_put_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra210_i2s_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN_E("RX", शून्य, 0, TEGRA210_I2S_RX_ENABLE,
			      0, 0, tegra210_i2s_init, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_AIF_OUT_E("TX", शून्य, 0, TEGRA210_I2S_TX_ENABLE,
			       0, 0, tegra210_i2s_init, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MIC("MIC", शून्य),
	SND_SOC_DAPM_SPK("SPK", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tegra210_i2s_routes[] = अणु
	/* Playback route from XBAR */
	अणु "XBAR-Playback",	शून्य,	"XBAR-TX" पूर्ण,
	अणु "CIF-Playback",	शून्य,	"XBAR-Playback" पूर्ण,
	अणु "RX",			शून्य,	"CIF-Playback" पूर्ण,
	अणु "DAP-Playback",	शून्य,	"RX" पूर्ण,
	अणु "SPK",		शून्य,	"DAP-Playback" पूर्ण,
	/* Capture route to XBAR */
	अणु "XBAR-RX",		शून्य,	"XBAR-Capture" पूर्ण,
	अणु "XBAR-Capture",	शून्य,	"CIF-Capture" पूर्ण,
	अणु "CIF-Capture",	शून्य,	"TX" पूर्ण,
	अणु "TX",			शून्य,	"DAP-Capture" पूर्ण,
	अणु "DAP-Capture",	शून्य,	"MIC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra210_i2s_cmpnt = अणु
	.dapm_widमाला_लो		= tegra210_i2s_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tegra210_i2s_widमाला_लो),
	.dapm_routes		= tegra210_i2s_routes,
	.num_dapm_routes	= ARRAY_SIZE(tegra210_i2s_routes),
	.controls		= tegra210_i2s_controls,
	.num_controls		= ARRAY_SIZE(tegra210_i2s_controls),
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल bool tegra210_i2s_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA210_I2S_RX_ENABLE ... TEGRA210_I2S_RX_SOFT_RESET:
	हाल TEGRA210_I2S_RX_INT_MASK ... TEGRA210_I2S_RX_CLK_TRIM:
	हाल TEGRA210_I2S_TX_ENABLE ... TEGRA210_I2S_TX_SOFT_RESET:
	हाल TEGRA210_I2S_TX_INT_MASK ... TEGRA210_I2S_TX_CLK_TRIM:
	हाल TEGRA210_I2S_ENABLE ... TEGRA210_I2S_CG:
	हाल TEGRA210_I2S_CTRL ... TEGRA210_I2S_CYA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra210_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (tegra210_i2s_wr_reg(dev, reg))
		वापस true;

	चयन (reg) अणु
	हाल TEGRA210_I2S_RX_STATUS:
	हाल TEGRA210_I2S_RX_INT_STATUS:
	हाल TEGRA210_I2S_RX_CIF_FIFO_STATUS:
	हाल TEGRA210_I2S_TX_STATUS:
	हाल TEGRA210_I2S_TX_INT_STATUS:
	हाल TEGRA210_I2S_TX_CIF_FIFO_STATUS:
	हाल TEGRA210_I2S_STATUS:
	हाल TEGRA210_I2S_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra210_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA210_I2S_RX_STATUS:
	हाल TEGRA210_I2S_RX_INT_STATUS:
	हाल TEGRA210_I2S_RX_CIF_FIFO_STATUS:
	हाल TEGRA210_I2S_TX_STATUS:
	हाल TEGRA210_I2S_TX_INT_STATUS:
	हाल TEGRA210_I2S_TX_CIF_FIFO_STATUS:
	हाल TEGRA210_I2S_STATUS:
	हाल TEGRA210_I2S_INT_STATUS:
	हाल TEGRA210_I2S_RX_SOFT_RESET:
	हाल TEGRA210_I2S_TX_SOFT_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra210_i2s_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= TEGRA210_I2S_CYA,
	.ग_लिखोable_reg		= tegra210_i2s_wr_reg,
	.पढ़ोable_reg		= tegra210_i2s_rd_reg,
	.अस्थिर_reg		= tegra210_i2s_अस्थिर_reg,
	.reg_शेषs		= tegra210_i2s_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(tegra210_i2s_reg_शेषs),
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra210_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra210_i2s *i2s;
	व्योम __iomem *regs;
	पूर्णांक err;

	i2s = devm_kzalloc(dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	i2s->rx_fअगरo_th = DEFAULT_I2S_RX_FIFO_THRESHOLD;
	i2s->tx_mask = DEFAULT_I2S_SLOT_MASK;
	i2s->rx_mask = DEFAULT_I2S_SLOT_MASK;
	i2s->loopback = false;

	dev_set_drvdata(dev, i2s);

	i2s->clk_i2s = devm_clk_get(dev, "i2s");
	अगर (IS_ERR(i2s->clk_i2s)) अणु
		dev_err(dev, "can't retrieve I2S bit clock\n");
		वापस PTR_ERR(i2s->clk_i2s);
	पूर्ण

	/*
	 * Not an error, as this घड़ी is needed only when some other I/O
	 * requires input घड़ी from current I2S instance, which is
	 * configurable from DT.
	 */
	i2s->clk_sync_input = devm_clk_get(dev, "sync_input");
	अगर (IS_ERR(i2s->clk_sync_input))
		dev_dbg(dev, "can't retrieve I2S sync input clock\n");

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	i2s->regmap = devm_regmap_init_mmio(dev, regs,
					    &tegra210_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(i2s->regmap);
	पूर्ण

	regcache_cache_only(i2s->regmap, true);

	err = devm_snd_soc_रेजिस्टर_component(dev, &tegra210_i2s_cmpnt,
					      tegra210_i2s_dais,
					      ARRAY_SIZE(tegra210_i2s_dais));
	अगर (err) अणु
		dev_err(dev, "can't register I2S component, err: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra210_i2s_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra210_i2s_runसमय_suspend,
			   tegra210_i2s_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra210_i2s_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-i2s" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra210_i2s_of_match);

अटल काष्ठा platक्रमm_driver tegra210_i2s_driver = अणु
	.driver = अणु
		.name = "tegra210-i2s",
		.of_match_table = tegra210_i2s_of_match,
		.pm = &tegra210_i2s_pm_ops,
	पूर्ण,
	.probe = tegra210_i2s_probe,
	.हटाओ = tegra210_i2s_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra210_i2s_driver)

MODULE_AUTHOR("Songhee Baek <sbaek@nvidia.com>");
MODULE_DESCRIPTION("Tegra210 ASoC I2S driver");
MODULE_LICENSE("GPL v2");
