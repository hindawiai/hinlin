<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Roger Nilsson <roger.xr.nilsson@stericsson.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/platक्रमm_data/asoc-ux500-msp.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "ux500_msp_i2s.h"
#समावेश "ux500_msp_dai.h"
#समावेश "ux500_pcm.h"

अटल पूर्णांक setup_pcm_multichan(काष्ठा snd_soc_dai *dai,
			काष्ठा ux500_msp_config *msp_config)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	काष्ठा msp_multichannel_config *multi =
					&msp_config->multichannel_config;

	अगर (drvdata->slots > 1) अणु
		msp_config->multichannel_configured = 1;

		multi->tx_multichannel_enable = true;
		multi->rx_multichannel_enable = true;
		multi->rx_comparison_enable_mode = MSP_COMPARISON_DISABLED;

		multi->tx_channel_0_enable = drvdata->tx_mask;
		multi->tx_channel_1_enable = 0;
		multi->tx_channel_2_enable = 0;
		multi->tx_channel_3_enable = 0;

		multi->rx_channel_0_enable = drvdata->rx_mask;
		multi->rx_channel_1_enable = 0;
		multi->rx_channel_2_enable = 0;
		multi->rx_channel_3_enable = 0;

		dev_dbg(dai->dev,
			"%s: Multichannel enabled. Slots: %d, TX: %u, RX: %u\n",
			__func__, drvdata->slots, multi->tx_channel_0_enable,
			multi->rx_channel_0_enable);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_frameper(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक rate,
			काष्ठा msp_protdesc *prot_desc)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	चयन (drvdata->slots) अणु
	हाल 1:
		चयन (rate) अणु
		हाल 8000:
			prot_desc->frame_period =
				FRAME_PER_SINGLE_SLOT_8_KHZ;
			अवरोध;

		हाल 16000:
			prot_desc->frame_period =
				FRAME_PER_SINGLE_SLOT_16_KHZ;
			अवरोध;

		हाल 44100:
			prot_desc->frame_period =
				FRAME_PER_SINGLE_SLOT_44_1_KHZ;
			अवरोध;

		हाल 48000:
			prot_desc->frame_period =
				FRAME_PER_SINGLE_SLOT_48_KHZ;
			अवरोध;

		शेष:
			dev_err(dai->dev,
				"%s: Error: Unsupported sample-rate (freq = %d)!\n",
				__func__, rate);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल 2:
		prot_desc->frame_period = FRAME_PER_2_SLOTS;
		अवरोध;

	हाल 8:
		prot_desc->frame_period = FRAME_PER_8_SLOTS;
		अवरोध;

	हाल 16:
		prot_desc->frame_period = FRAME_PER_16_SLOTS;
		अवरोध;
	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported slot-count (slots = %d)!\n",
			__func__, drvdata->slots);
		वापस -EINVAL;
	पूर्ण

	prot_desc->घड़ीs_per_frame =
			prot_desc->frame_period+1;

	dev_dbg(dai->dev, "%s: Clocks per frame: %u\n",
		__func__,
		prot_desc->घड़ीs_per_frame);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_pcm_framing(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक rate,
			काष्ठा msp_protdesc *prot_desc)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	u32 frame_length = MSP_FRAME_LEN_1;

	prot_desc->frame_width = 0;

	चयन (drvdata->slots) अणु
	हाल 1:
		frame_length = MSP_FRAME_LEN_1;
		अवरोध;

	हाल 2:
		frame_length = MSP_FRAME_LEN_2;
		अवरोध;

	हाल 8:
		frame_length = MSP_FRAME_LEN_8;
		अवरोध;

	हाल 16:
		frame_length = MSP_FRAME_LEN_16;
		अवरोध;
	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported slot-count (slots = %d)!\n",
			__func__, drvdata->slots);
		वापस -EINVAL;
	पूर्ण

	prot_desc->tx_frame_len_1 = frame_length;
	prot_desc->rx_frame_len_1 = frame_length;
	prot_desc->tx_frame_len_2 = frame_length;
	prot_desc->rx_frame_len_2 = frame_length;

	prot_desc->tx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->rx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->tx_elem_len_2 = MSP_ELEM_LEN_16;
	prot_desc->rx_elem_len_2 = MSP_ELEM_LEN_16;

	वापस setup_frameper(dai, rate, prot_desc);
पूर्ण

अटल पूर्णांक setup_घड़ीing(काष्ठा snd_soc_dai *dai,
			अचिन्हित पूर्णांक fmt,
			काष्ठा ux500_msp_config *msp_config)
अणु
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;

	हाल SND_SOC_DAIFMT_NB_IF:
		msp_config->tx_fsync_pol ^= 1 << TFSPOL_SHIFT;
		msp_config->rx_fsync_pol ^= 1 << RFSPOL_SHIFT;

		अवरोध;

	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported inversion (fmt = 0x%x)!\n",
			__func__, fmt);

		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		dev_dbg(dai->dev, "%s: Codec is master.\n", __func__);

		msp_config->iodelay = 0x20;
		msp_config->rx_fsync_sel = 0;
		msp_config->tx_fsync_sel = 1 << TFSSEL_SHIFT;
		msp_config->tx_clk_sel = 0;
		msp_config->rx_clk_sel = 0;
		msp_config->srg_clk_sel = 0x2 << SCKSEL_SHIFT;

		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFS:
		dev_dbg(dai->dev, "%s: Codec is slave.\n", __func__);

		msp_config->tx_clk_sel = TX_CLK_SEL_SRG;
		msp_config->tx_fsync_sel = TX_SYNC_SRG_PROG;
		msp_config->rx_clk_sel = RX_CLK_SEL_SRG;
		msp_config->rx_fsync_sel = RX_SYNC_SRG;
		msp_config->srg_clk_sel = 1 << SCKSEL_SHIFT;

		अवरोध;

	शेष:
		dev_err(dai->dev, "%s: Error: Unsupported master (fmt = 0x%x)!\n",
			__func__, fmt);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_pcm_protdesc(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक fmt,
				काष्ठा msp_protdesc *prot_desc)
अणु
	prot_desc->rx_phase_mode = MSP_SINGLE_PHASE;
	prot_desc->tx_phase_mode = MSP_SINGLE_PHASE;
	prot_desc->rx_phase2_start_mode = MSP_PHASE2_START_MODE_IMEDIATE;
	prot_desc->tx_phase2_start_mode = MSP_PHASE2_START_MODE_IMEDIATE;
	prot_desc->rx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_fsync_pol = MSP_FSYNC_POL(MSP_FSYNC_POL_ACT_HI);
	prot_desc->rx_fsync_pol = MSP_FSYNC_POL_ACT_HI << RFSPOL_SHIFT;

	अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) == SND_SOC_DAIFMT_DSP_A) अणु
		dev_dbg(dai->dev, "%s: DSP_A.\n", __func__);
		prot_desc->rx_clk_pol = MSP_RISING_EDGE;
		prot_desc->tx_clk_pol = MSP_FALLING_EDGE;

		prot_desc->rx_data_delay = MSP_DELAY_1;
		prot_desc->tx_data_delay = MSP_DELAY_1;
	पूर्ण अन्यथा अणु
		dev_dbg(dai->dev, "%s: DSP_B.\n", __func__);
		prot_desc->rx_clk_pol = MSP_FALLING_EDGE;
		prot_desc->tx_clk_pol = MSP_RISING_EDGE;

		prot_desc->rx_data_delay = MSP_DELAY_0;
		prot_desc->tx_data_delay = MSP_DELAY_0;
	पूर्ण

	prot_desc->rx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->tx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->compression_mode = MSP_COMPRESS_MODE_LINEAR;
	prot_desc->expansion_mode = MSP_EXPAND_MODE_LINEAR;
	prot_desc->frame_sync_ignore = MSP_FSYNC_IGNORE;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_i2s_protdesc(काष्ठा msp_protdesc *prot_desc)
अणु
	prot_desc->rx_phase_mode = MSP_DUAL_PHASE;
	prot_desc->tx_phase_mode = MSP_DUAL_PHASE;
	prot_desc->rx_phase2_start_mode = MSP_PHASE2_START_MODE_FSYNC;
	prot_desc->tx_phase2_start_mode = MSP_PHASE2_START_MODE_FSYNC;
	prot_desc->rx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_fsync_pol = MSP_FSYNC_POL(MSP_FSYNC_POL_ACT_LO);
	prot_desc->rx_fsync_pol = MSP_FSYNC_POL_ACT_LO << RFSPOL_SHIFT;

	prot_desc->rx_frame_len_1 = MSP_FRAME_LEN_1;
	prot_desc->rx_frame_len_2 = MSP_FRAME_LEN_1;
	prot_desc->tx_frame_len_1 = MSP_FRAME_LEN_1;
	prot_desc->tx_frame_len_2 = MSP_FRAME_LEN_1;
	prot_desc->rx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->rx_elem_len_2 = MSP_ELEM_LEN_16;
	prot_desc->tx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->tx_elem_len_2 = MSP_ELEM_LEN_16;

	prot_desc->rx_clk_pol = MSP_RISING_EDGE;
	prot_desc->tx_clk_pol = MSP_FALLING_EDGE;

	prot_desc->rx_data_delay = MSP_DELAY_0;
	prot_desc->tx_data_delay = MSP_DELAY_0;

	prot_desc->tx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->rx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->compression_mode = MSP_COMPRESS_MODE_LINEAR;
	prot_desc->expansion_mode = MSP_EXPAND_MODE_LINEAR;
	prot_desc->frame_sync_ignore = MSP_FSYNC_IGNORE;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_msp_config(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai,
			काष्ठा ux500_msp_config *msp_config)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	काष्ठा msp_protdesc *prot_desc = &msp_config->protdesc;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक fmt = drvdata->fmt;
	पूर्णांक ret;

	स_रखो(msp_config, 0, माप(*msp_config));

	msp_config->f_inअ_दोlk = drvdata->master_clk;

	msp_config->tx_fअगरo_config = TX_FIFO_ENABLE;
	msp_config->rx_fअगरo_config = RX_FIFO_ENABLE;
	msp_config->def_elem_len = 1;
	msp_config->direction = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
				MSP_सूची_TX : MSP_सूची_RX;
	msp_config->data_size = MSP_DATA_BITS_32;
	msp_config->frame_freq = runसमय->rate;

	dev_dbg(dai->dev, "%s: f_inputclk = %u, frame_freq = %u.\n",
	       __func__, msp_config->f_inअ_दोlk, msp_config->frame_freq);
	/* To aव्योम भागision by zero */
	prot_desc->घड़ीs_per_frame = 1;

	dev_dbg(dai->dev, "%s: rate: %u, channels: %d.\n", __func__,
		runसमय->rate, runसमय->channels);
	चयन (fmt &
		(SND_SOC_DAIFMT_FORMAT_MASK | SND_SOC_DAIFMT_MASTER_MASK)) अणु
	हाल SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS:
		dev_dbg(dai->dev, "%s: SND_SOC_DAIFMT_I2S.\n", __func__);

		msp_config->शेष_protdesc = 1;
		msp_config->protocol = MSP_I2S_PROTOCOL;
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBM_CFM:
		dev_dbg(dai->dev, "%s: SND_SOC_DAIFMT_I2S.\n", __func__);

		msp_config->data_size = MSP_DATA_BITS_16;
		msp_config->protocol = MSP_I2S_PROTOCOL;

		ret = setup_i2s_protdesc(prot_desc);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM:
		dev_dbg(dai->dev, "%s: PCM format.\n", __func__);

		msp_config->data_size = MSP_DATA_BITS_16;
		msp_config->protocol = MSP_PCM_PROTOCOL;

		ret = setup_pcm_protdesc(dai, fmt, prot_desc);
		अगर (ret < 0)
			वापस ret;

		ret = setup_pcm_multichan(dai, msp_config);
		अगर (ret < 0)
			वापस ret;

		ret = setup_pcm_framing(dai, runसमय->rate, prot_desc);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	शेष:
		dev_err(dai->dev, "%s: Error: Unsupported format (%d)!\n",
			__func__, fmt);
		वापस -EINVAL;
	पूर्ण

	वापस setup_घड़ीing(dai, fmt, msp_config);
पूर्ण

अटल पूर्णांक ux500_msp_dai_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	dev_dbg(dai->dev, "%s: MSP %d (%s): Enter.\n", __func__, dai->id,
		snd_pcm_stream_str(substream));

	/* Enable regulator */
	ret = regulator_enable(drvdata->reg_vape);
	अगर (ret != 0) अणु
		dev_err(drvdata->msp->dev,
			"%s: Failed to enable regulator!\n", __func__);
		वापस ret;
	पूर्ण

	/* Prepare and enable घड़ीs */
	dev_dbg(dai->dev, "%s: Enabling MSP-clocks.\n", __func__);
	ret = clk_prepare_enable(drvdata->pclk);
	अगर (ret) अणु
		dev_err(drvdata->msp->dev,
			"%s: Failed to prepare/enable pclk!\n", __func__);
		जाओ err_pclk;
	पूर्ण

	ret = clk_prepare_enable(drvdata->clk);
	अगर (ret) अणु
		dev_err(drvdata->msp->dev,
			"%s: Failed to prepare/enable clk!\n", __func__);
		जाओ err_clk;
	पूर्ण

	वापस ret;
err_clk:
	clk_disable_unprepare(drvdata->pclk);
err_pclk:
	regulator_disable(drvdata->reg_vape);
	वापस ret;
पूर्ण

अटल व्योम ux500_msp_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	dev_dbg(dai->dev, "%s: MSP %d (%s): Enter.\n", __func__, dai->id,
		snd_pcm_stream_str(substream));

	अगर (drvdata->vape_opp_स्थिरraपूर्णांक == 1) अणु
		prcmu_qos_update_requirement(PRCMU_QOS_APE_OPP,
					"ux500_msp_i2s", 50);
		drvdata->vape_opp_स्थिरraपूर्णांक = 0;
	पूर्ण

	अगर (ux500_msp_i2s_बंद(drvdata->msp,
				is_playback ? MSP_सूची_TX : MSP_सूची_RX)) अणु
		dev_err(dai->dev,
			"%s: Error: MSP %d (%s): Unable to close i2s.\n",
			__func__, dai->id, snd_pcm_stream_str(substream));
	पूर्ण

	/* Disable and unprepare घड़ीs */
	clk_disable_unprepare(drvdata->clk);
	clk_disable_unprepare(drvdata->pclk);

	/* Disable regulator */
	ret = regulator_disable(drvdata->reg_vape);
	अगर (ret < 0)
		dev_err(dai->dev,
			"%s: ERROR: Failed to disable regulator (%d)!\n",
			__func__, ret);
पूर्ण

अटल पूर्णांक ux500_msp_dai_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ux500_msp_config msp_config;

	dev_dbg(dai->dev, "%s: MSP %d (%s): Enter (rate = %d).\n", __func__,
		dai->id, snd_pcm_stream_str(substream), runसमय->rate);

	setup_msp_config(substream, dai, &msp_config);

	ret = ux500_msp_i2s_खोलो(drvdata->msp, &msp_config);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "%s: Error: msp_setup failed (ret = %d)!\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Set OPP-level */
	अगर ((drvdata->fmt & SND_SOC_DAIFMT_MASTER_MASK) &&
		(drvdata->msp->f_bitclk > 19200000)) अणु
		/* If the bit-घड़ी is higher than 19.2MHz, Vape should be
		 * run in 100% OPP. Only when bit-घड़ी is used (MSP master)
		 */
		prcmu_qos_update_requirement(PRCMU_QOS_APE_OPP,
					"ux500-msp-i2s", 100);
		drvdata->vape_opp_स्थिरraपूर्णांक = 1;
	पूर्ण अन्यथा अणु
		prcmu_qos_update_requirement(PRCMU_QOS_APE_OPP,
					"ux500-msp-i2s", 50);
		drvdata->vape_opp_स्थिरraपूर्णांक = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ux500_msp_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित पूर्णांक mask, slots_active;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	dev_dbg(dai->dev, "%s: MSP %d (%s): Enter.\n",
			__func__, dai->id, snd_pcm_stream_str(substream));

	चयन (drvdata->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				1, 2);
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
	हाल SND_SOC_DAIFMT_DSP_A:
		mask = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
			drvdata->tx_mask :
			drvdata->rx_mask;

		slots_active = hweight32(mask);
		dev_dbg(dai->dev, "TDM-slots active: %d", slots_active);

		snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				slots_active);
		अवरोध;

	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported protocol (fmt = 0x%x)!\n",
			__func__, drvdata->fmt);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_msp_dai_set_dai_fmt(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	dev_dbg(dai->dev, "%s: MSP %d: Enter.\n", __func__, dai->id);

	चयन (fmt & (SND_SOC_DAIFMT_FORMAT_MASK |
		SND_SOC_DAIFMT_MASTER_MASK)) अणु
	हाल SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;

	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported protocol/master (fmt = 0x%x)!\n",
			__func__, drvdata->fmt);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_NB_IF:
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;

	शेष:
		dev_err(dai->dev,
			"%s: Error: Unsupported inversion (fmt = 0x%x)!\n",
			__func__, drvdata->fmt);
		वापस -EINVAL;
	पूर्ण

	drvdata->fmt = fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक ux500_msp_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask,
				पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	अचिन्हित पूर्णांक cap;

	चयन (slots) अणु
	हाल 1:
		cap = 0x01;
		अवरोध;
	हाल 2:
		cap = 0x03;
		अवरोध;
	हाल 8:
		cap = 0xFF;
		अवरोध;
	हाल 16:
		cap = 0xFFFF;
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: Error: Unsupported slot-count (%d)!\n",
			__func__, slots);
		वापस -EINVAL;
	पूर्ण
	drvdata->slots = slots;

	अगर (!(slot_width == 16)) अणु
		dev_err(dai->dev, "%s: Error: Unsupported slot-width (%d)!\n",
			__func__, slot_width);
		वापस -EINVAL;
	पूर्ण
	drvdata->slot_width = slot_width;

	drvdata->tx_mask = tx_mask & cap;
	drvdata->rx_mask = rx_mask & cap;

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_msp_dai_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
					पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	dev_dbg(dai->dev, "%s: MSP %d: Enter. clk-id: %d, freq: %u.\n",
		__func__, dai->id, clk_id, freq);

	चयन (clk_id) अणु
	हाल UX500_MSP_MASTER_CLOCK:
		drvdata->master_clk = freq;
		अवरोध;

	शेष:
		dev_err(dai->dev, "%s: MSP %d: Invalid clk-id (%d)!\n",
			__func__, dai->id, clk_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_msp_dai_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);

	dev_dbg(dai->dev, "%s: MSP %d (%s): Enter (msp->id = %d, cmd = %d).\n",
		__func__, dai->id, snd_pcm_stream_str(substream),
		(पूर्णांक)drvdata->msp->id, cmd);

	ret = ux500_msp_i2s_trigger(drvdata->msp, cmd, substream->stream);

	वापस ret;
पूर्ण

अटल पूर्णांक ux500_msp_dai_of_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	काष्ठा snd_dmaengine_dai_dma_data *playback_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data *capture_dma_data;

	playback_dma_data = devm_kzalloc(dai->dev,
					 माप(*playback_dma_data),
					 GFP_KERNEL);
	अगर (!playback_dma_data)
		वापस -ENOMEM;

	capture_dma_data = devm_kzalloc(dai->dev,
					माप(*capture_dma_data),
					GFP_KERNEL);
	अगर (!capture_dma_data)
		वापस -ENOMEM;

	playback_dma_data->addr = drvdata->msp->playback_dma_data.tx_rx_addr;
	capture_dma_data->addr = drvdata->msp->capture_dma_data.tx_rx_addr;

	playback_dma_data->maxburst = 4;
	capture_dma_data->maxburst = 4;

	snd_soc_dai_init_dma_data(dai, playback_dma_data, capture_dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_msp_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	काष्ठा msp_i2s_platक्रमm_data *pdata = dai->dev->platक्रमm_data;
	पूर्णांक ret;

	अगर (!pdata) अणु
		ret = ux500_msp_dai_of_probe(dai);
		वापस ret;
	पूर्ण

	drvdata->msp->playback_dma_data.data_size = drvdata->slot_width;
	drvdata->msp->capture_dma_data.data_size = drvdata->slot_width;

	snd_soc_dai_init_dma_data(dai,
				  &drvdata->msp->playback_dma_data,
				  &drvdata->msp->capture_dma_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ux500_msp_dai_ops[] = अणु
	अणु
		.set_sysclk = ux500_msp_dai_set_dai_sysclk,
		.set_fmt = ux500_msp_dai_set_dai_fmt,
		.set_tdm_slot = ux500_msp_dai_set_tdm_slot,
		.startup = ux500_msp_dai_startup,
		.shutकरोwn = ux500_msp_dai_shutकरोwn,
		.prepare = ux500_msp_dai_prepare,
		.trigger = ux500_msp_dai_trigger,
		.hw_params = ux500_msp_dai_hw_params,
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ux500_msp_dai_drv = अणु
	.probe                 = ux500_msp_dai_probe,
	.playback.channels_min = UX500_MSP_MIN_CHANNELS,
	.playback.channels_max = UX500_MSP_MAX_CHANNELS,
	.playback.rates        = UX500_I2S_RATES,
	.playback.क्रमmats      = UX500_I2S_FORMATS,
	.capture.channels_min  = UX500_MSP_MIN_CHANNELS,
	.capture.channels_max  = UX500_MSP_MAX_CHANNELS,
	.capture.rates         = UX500_I2S_RATES,
	.capture.क्रमmats       = UX500_I2S_FORMATS,
	.ops                   = ux500_msp_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ux500_msp_component = अणु
	.name		= "ux500-msp",
पूर्ण;


अटल पूर्णांक ux500_msp_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata;
	काष्ठा msp_i2s_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret = 0;

	अगर (!pdata && !np) अणु
		dev_err(&pdev->dev, "No platform data or Device Tree found\n");
		वापस -ENODEV;
	पूर्ण

	drvdata = devm_kzalloc(&pdev->dev,
				माप(काष्ठा ux500_msp_i2s_drvdata),
				GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->fmt = 0;
	drvdata->slots = 1;
	drvdata->tx_mask = 0x01;
	drvdata->rx_mask = 0x01;
	drvdata->slot_width = 16;
	drvdata->master_clk = MSP_INPUT_FREQ_APB;

	drvdata->reg_vape = devm_regulator_get(&pdev->dev, "v-ape");
	अगर (IS_ERR(drvdata->reg_vape)) अणु
		ret = (पूर्णांक)PTR_ERR(drvdata->reg_vape);
		dev_err(&pdev->dev,
			"%s: ERROR: Failed to get Vape supply (%d)!\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	prcmu_qos_add_requirement(PRCMU_QOS_APE_OPP, (अक्षर *)pdev->name, 50);

	drvdata->pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(drvdata->pclk)) अणु
		ret = (पूर्णांक)PTR_ERR(drvdata->pclk);
		dev_err(&pdev->dev,
			"%s: ERROR: devm_clk_get of pclk failed (%d)!\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	drvdata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(drvdata->clk)) अणु
		ret = (पूर्णांक)PTR_ERR(drvdata->clk);
		dev_err(&pdev->dev,
			"%s: ERROR: devm_clk_get failed (%d)!\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = ux500_msp_i2s_init_msp(pdev, &drvdata->msp,
				pdev->dev.platक्रमm_data);
	अगर (!drvdata->msp) अणु
		dev_err(&pdev->dev,
			"%s: ERROR: Failed to init MSP-struct (%d)!",
			__func__, ret);
		वापस ret;
	पूर्ण
	dev_set_drvdata(&pdev->dev, drvdata);

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &ux500_msp_component,
					 &ux500_msp_dai_drv, 1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Error: %s: Failed to register MSP%d!\n",
			__func__, drvdata->msp->id);
		वापस ret;
	पूर्ण

	ret = ux500_pcm_रेजिस्टर_platक्रमm(pdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Error: %s: Failed to register PCM platform device!\n",
			__func__);
		जाओ err_reg_plat;
	पूर्ण

	वापस 0;

err_reg_plat:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ux500_msp_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(&pdev->dev);

	ux500_pcm_unरेजिस्टर_platक्रमm(pdev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	prcmu_qos_हटाओ_requirement(PRCMU_QOS_APE_OPP, "ux500_msp_i2s");

	ux500_msp_i2s_cleanup_msp(pdev, drvdata->msp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ux500_msp_i2s_match[] = अणु
	अणु .compatible = "stericsson,ux500-msp-i2s", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ux500_msp_i2s_match);

अटल काष्ठा platक्रमm_driver msp_i2s_driver = अणु
	.driver = अणु
		.name = "ux500-msp-i2s",
		.of_match_table = ux500_msp_i2s_match,
	पूर्ण,
	.probe = ux500_msp_drv_probe,
	.हटाओ = ux500_msp_drv_हटाओ,
पूर्ण;
module_platक्रमm_driver(msp_i2s_driver);

MODULE_LICENSE("GPL v2");
