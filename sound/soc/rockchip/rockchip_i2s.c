<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sound/soc/rockchip/rockchip_i2s.c
 *
 * ALSA SoC Audio Layer - Rockchip I2S Controller driver
 *
 * Copyright (c) 2014 Rockchip Electronics Co. Ltd.
 * Author: Jianqun <jay.xu@rock-chips.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "rockchip_i2s.h"
#समावेश "rockchip_pcm.h"

#घोषणा DRV_NAME "rockchip-i2s"

काष्ठा rk_i2s_pins अणु
	u32 reg_offset;
	u32 shअगरt;
पूर्ण;

काष्ठा rk_i2s_dev अणु
	काष्ठा device *dev;

	काष्ठा clk *hclk;
	काष्ठा clk *mclk;

	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;

	काष्ठा regmap *regmap;
	काष्ठा regmap *grf;

/*
 * Used to indicate the tx/rx status.
 * I2S controller hopes to start the tx and rx together,
 * also to stop them when they are both try to stop.
*/
	bool tx_start;
	bool rx_start;
	bool is_master_mode;
	स्थिर काष्ठा rk_i2s_pins *pins;
पूर्ण;

अटल पूर्णांक i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_i2s_dev *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);
	clk_disable_unprepare(i2s->mclk);

	वापस 0;
पूर्ण

अटल पूर्णांक i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_i2s_dev *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->mclk);
	अगर (ret) अणु
		dev_err(i2s->dev, "clock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(i2s->regmap, false);
	regcache_mark_dirty(i2s->regmap);

	ret = regcache_sync(i2s->regmap);
	अगर (ret)
		clk_disable_unprepare(i2s->mclk);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा rk_i2s_dev *to_info(काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_soc_dai_get_drvdata(dai);
पूर्ण

अटल व्योम rockchip_snd_txctrl(काष्ठा rk_i2s_dev *i2s, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक retry = 10;

	अगर (on) अणु
		regmap_update_bits(i2s->regmap, I2S_DMACR,
				   I2S_DMACR_TDE_ENABLE, I2S_DMACR_TDE_ENABLE);

		regmap_update_bits(i2s->regmap, I2S_XFER,
				   I2S_XFER_TXS_START | I2S_XFER_RXS_START,
				   I2S_XFER_TXS_START | I2S_XFER_RXS_START);

		i2s->tx_start = true;
	पूर्ण अन्यथा अणु
		i2s->tx_start = false;

		regmap_update_bits(i2s->regmap, I2S_DMACR,
				   I2S_DMACR_TDE_ENABLE, I2S_DMACR_TDE_DISABLE);

		अगर (!i2s->rx_start) अणु
			regmap_update_bits(i2s->regmap, I2S_XFER,
					   I2S_XFER_TXS_START |
					   I2S_XFER_RXS_START,
					   I2S_XFER_TXS_STOP |
					   I2S_XFER_RXS_STOP);

			udelay(150);
			regmap_update_bits(i2s->regmap, I2S_CLR,
					   I2S_CLR_TXC | I2S_CLR_RXC,
					   I2S_CLR_TXC | I2S_CLR_RXC);

			regmap_पढ़ो(i2s->regmap, I2S_CLR, &val);

			/* Should रुको क्रम clear operation to finish */
			जबतक (val) अणु
				regmap_पढ़ो(i2s->regmap, I2S_CLR, &val);
				retry--;
				अगर (!retry) अणु
					dev_warn(i2s->dev, "fail to clear\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rockchip_snd_rxctrl(काष्ठा rk_i2s_dev *i2s, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक retry = 10;

	अगर (on) अणु
		regmap_update_bits(i2s->regmap, I2S_DMACR,
				   I2S_DMACR_RDE_ENABLE, I2S_DMACR_RDE_ENABLE);

		regmap_update_bits(i2s->regmap, I2S_XFER,
				   I2S_XFER_TXS_START | I2S_XFER_RXS_START,
				   I2S_XFER_TXS_START | I2S_XFER_RXS_START);

		i2s->rx_start = true;
	पूर्ण अन्यथा अणु
		i2s->rx_start = false;

		regmap_update_bits(i2s->regmap, I2S_DMACR,
				   I2S_DMACR_RDE_ENABLE, I2S_DMACR_RDE_DISABLE);

		अगर (!i2s->tx_start) अणु
			regmap_update_bits(i2s->regmap, I2S_XFER,
					   I2S_XFER_TXS_START |
					   I2S_XFER_RXS_START,
					   I2S_XFER_TXS_STOP |
					   I2S_XFER_RXS_STOP);

			udelay(150);
			regmap_update_bits(i2s->regmap, I2S_CLR,
					   I2S_CLR_TXC | I2S_CLR_RXC,
					   I2S_CLR_TXC | I2S_CLR_RXC);

			regmap_पढ़ो(i2s->regmap, I2S_CLR, &val);

			/* Should रुको क्रम clear operation to finish */
			जबतक (val) अणु
				regmap_पढ़ो(i2s->regmap, I2S_CLR, &val);
				retry--;
				अगर (!retry) अणु
					dev_warn(i2s->dev, "fail to clear\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा rk_i2s_dev *i2s = to_info(cpu_dai);
	अचिन्हित पूर्णांक mask = 0, val = 0;

	mask = I2S_CKR_MSS_MASK;
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* Set source घड़ी in Master mode */
		val = I2S_CKR_MSS_MASTER;
		i2s->is_master_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val = I2S_CKR_MSS_SLAVE;
		i2s->is_master_mode = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, I2S_CKR, mask, val);

	mask = I2S_CKR_CKP_MASK;
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		val = I2S_CKR_CKP_NEG;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		val = I2S_CKR_CKP_POS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, I2S_CKR, mask, val);

	mask = I2S_TXCR_IBM_MASK | I2S_TXCR_TFS_MASK | I2S_TXCR_PBM_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = I2S_TXCR_IBM_RSJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = I2S_TXCR_IBM_LSJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = I2S_TXCR_IBM_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A: /* PCM no delay mode */
		val = I2S_TXCR_TFS_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B: /* PCM delay 1 mode */
		val = I2S_TXCR_TFS_PCM | I2S_TXCR_PBM_MODE(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, I2S_TXCR, mask, val);

	mask = I2S_RXCR_IBM_MASK | I2S_RXCR_TFS_MASK | I2S_RXCR_PBM_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = I2S_RXCR_IBM_RSJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = I2S_RXCR_IBM_LSJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = I2S_RXCR_IBM_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A: /* PCM no delay mode */
		val = I2S_RXCR_TFS_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B: /* PCM delay 1 mode */
		val = I2S_RXCR_TFS_PCM | I2S_RXCR_PBM_MODE(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, I2S_RXCR, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_i2s_dev *i2s = to_info(dai);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mclk_rate, bclk_rate, भाग_bclk, भाग_lrck;

	अगर (i2s->is_master_mode) अणु
		mclk_rate = clk_get_rate(i2s->mclk);
		bclk_rate = 2 * 32 * params_rate(params);
		अगर (bclk_rate == 0 || mclk_rate % bclk_rate)
			वापस -EINVAL;

		भाग_bclk = mclk_rate / bclk_rate;
		भाग_lrck = bclk_rate / params_rate(params);
		regmap_update_bits(i2s->regmap, I2S_CKR,
				   I2S_CKR_MDIV_MASK,
				   I2S_CKR_MDIV(भाग_bclk));

		regmap_update_bits(i2s->regmap, I2S_CKR,
				   I2S_CKR_TSD_MASK |
				   I2S_CKR_RSD_MASK,
				   I2S_CKR_TSD(भाग_lrck) |
				   I2S_CKR_RSD(भाग_lrck));
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		val |= I2S_TXCR_VDW(8);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val |= I2S_TXCR_VDW(16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val |= I2S_TXCR_VDW(20);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val |= I2S_TXCR_VDW(24);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val |= I2S_TXCR_VDW(32);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_channels(params)) अणु
	हाल 8:
		val |= I2S_CHN_8;
		अवरोध;
	हाल 6:
		val |= I2S_CHN_6;
		अवरोध;
	हाल 4:
		val |= I2S_CHN_4;
		अवरोध;
	हाल 2:
		val |= I2S_CHN_2;
		अवरोध;
	शेष:
		dev_err(i2s->dev, "invalid channel: %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		regmap_update_bits(i2s->regmap, I2S_RXCR,
				   I2S_RXCR_VDW_MASK | I2S_RXCR_CSR_MASK,
				   val);
	अन्यथा
		regmap_update_bits(i2s->regmap, I2S_TXCR,
				   I2S_TXCR_VDW_MASK | I2S_TXCR_CSR_MASK,
				   val);

	अगर (!IS_ERR(i2s->grf) && i2s->pins) अणु
		regmap_पढ़ो(i2s->regmap, I2S_TXCR, &val);
		val &= I2S_TXCR_CSR_MASK;

		चयन (val) अणु
		हाल I2S_CHN_4:
			val = I2S_IO_4CH_OUT_6CH_IN;
			अवरोध;
		हाल I2S_CHN_6:
			val = I2S_IO_6CH_OUT_4CH_IN;
			अवरोध;
		हाल I2S_CHN_8:
			val = I2S_IO_8CH_OUT_2CH_IN;
			अवरोध;
		शेष:
			val = I2S_IO_2CH_OUT_8CH_IN;
			अवरोध;
		पूर्ण

		val <<= i2s->pins->shअगरt;
		val |= (I2S_IO_सूचीECTION_MASK << i2s->pins->shअगरt) << 16;
		regmap_ग_लिखो(i2s->grf, i2s->pins->reg_offset, val);
	पूर्ण

	regmap_update_bits(i2s->regmap, I2S_DMACR, I2S_DMACR_TDL_MASK,
			   I2S_DMACR_TDL(16));
	regmap_update_bits(i2s->regmap, I2S_DMACR, I2S_DMACR_RDL_MASK,
			   I2S_DMACR_RDL(16));

	val = I2S_CKR_TRCM_TXRX;
	अगर (dai->driver->symmetric_rate && rtd->dai_link->symmetric_rate)
		val = I2S_CKR_TRCM_TXONLY;

	regmap_update_bits(i2s->regmap, I2S_CKR,
			   I2S_CKR_TRCM_MASK,
			   val);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_i2s_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_i2s_dev *i2s = to_info(dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			rockchip_snd_rxctrl(i2s, 1);
		अन्यथा
			rockchip_snd_txctrl(i2s, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			rockchip_snd_rxctrl(i2s, 0);
		अन्यथा
			rockchip_snd_txctrl(i2s, 0);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_i2s_set_sysclk(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक clk_id,
				   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rk_i2s_dev *i2s = to_info(cpu_dai);
	पूर्णांक ret;

	अगर (freq == 0)
		वापस 0;

	ret = clk_set_rate(i2s->mclk, freq);
	अगर (ret)
		dev_err(i2s->dev, "Fail to set mclk %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_i2s_dev *i2s = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &i2s->capture_dma_data;
	dai->playback_dma_data = &i2s->playback_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rockchip_i2s_dai_ops = अणु
	.hw_params = rockchip_i2s_hw_params,
	.set_sysclk = rockchip_i2s_set_sysclk,
	.set_fmt = rockchip_i2s_set_fmt,
	.trigger = rockchip_i2s_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rockchip_i2s_dai = अणु
	.probe = rockchip_i2s_dai_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = (SNDRV_PCM_FMTBIT_S8 |
			    SNDRV_PCM_FMTBIT_S16_LE |
			    SNDRV_PCM_FMTBIT_S20_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE |
			    SNDRV_PCM_FMTBIT_S32_LE),
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = (SNDRV_PCM_FMTBIT_S8 |
			    SNDRV_PCM_FMTBIT_S16_LE |
			    SNDRV_PCM_FMTBIT_S20_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE |
			    SNDRV_PCM_FMTBIT_S32_LE),
	पूर्ण,
	.ops = &rockchip_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver rockchip_i2s_component = अणु
	.name = DRV_NAME,
पूर्ण;

अटल bool rockchip_i2s_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_TXCR:
	हाल I2S_RXCR:
	हाल I2S_CKR:
	हाल I2S_DMACR:
	हाल I2S_INTCR:
	हाल I2S_XFER:
	हाल I2S_CLR:
	हाल I2S_TXDR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_TXCR:
	हाल I2S_RXCR:
	हाल I2S_CKR:
	हाल I2S_DMACR:
	हाल I2S_INTCR:
	हाल I2S_XFER:
	हाल I2S_CLR:
	हाल I2S_TXDR:
	हाल I2S_RXDR:
	हाल I2S_FIFOLR:
	हाल I2S_INTSR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_INTSR:
	हाल I2S_CLR:
	हाल I2S_FIFOLR:
	हाल I2S_TXDR:
	हाल I2S_RXDR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_i2s_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल I2S_RXDR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष rockchip_i2s_reg_शेषs[] = अणु
	अणु0x00, 0x0000000fपूर्ण,
	अणु0x04, 0x0000000fपूर्ण,
	अणु0x08, 0x00071f1fपूर्ण,
	अणु0x10, 0x001f0000पूर्ण,
	अणु0x14, 0x01f00000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rockchip_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = I2S_RXDR,
	.reg_शेषs = rockchip_i2s_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rockchip_i2s_reg_शेषs),
	.ग_लिखोable_reg = rockchip_i2s_wr_reg,
	.पढ़ोable_reg = rockchip_i2s_rd_reg,
	.अस्थिर_reg = rockchip_i2s_अस्थिर_reg,
	.precious_reg = rockchip_i2s_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा rk_i2s_pins rk3399_i2s_pins = अणु
	.reg_offset = 0xe220,
	.shअगरt = 11,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_i2s_match[] __maybe_unused = अणु
	अणु .compatible = "rockchip,rk3066-i2s", पूर्ण,
	अणु .compatible = "rockchip,rk3188-i2s", पूर्ण,
	अणु .compatible = "rockchip,rk3288-i2s", पूर्ण,
	अणु .compatible = "rockchip,rk3399-i2s", .data = &rk3399_i2s_pins पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक rockchip_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा rk_i2s_dev *i2s;
	काष्ठा snd_soc_dai_driver *soc_dai;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret;
	पूर्णांक val;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	i2s->dev = &pdev->dev;

	i2s->grf = syscon_regmap_lookup_by_phandle(node, "rockchip,grf");
	अगर (!IS_ERR(i2s->grf)) अणु
		of_id = of_match_device(rockchip_i2s_match, &pdev->dev);
		अगर (!of_id || !of_id->data)
			वापस -EINVAL;

		i2s->pins = of_id->data;
	पूर्ण

	/* try to prepare related घड़ीs */
	i2s->hclk = devm_clk_get(&pdev->dev, "i2s_hclk");
	अगर (IS_ERR(i2s->hclk)) अणु
		dev_err(&pdev->dev, "Can't retrieve i2s bus clock\n");
		वापस PTR_ERR(i2s->hclk);
	पूर्ण
	ret = clk_prepare_enable(i2s->hclk);
	अगर (ret) अणु
		dev_err(i2s->dev, "hclock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	i2s->mclk = devm_clk_get(&pdev->dev, "i2s_clk");
	अगर (IS_ERR(i2s->mclk)) अणु
		dev_err(&pdev->dev, "Can't retrieve i2s master clock\n");
		वापस PTR_ERR(i2s->mclk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &rockchip_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(&pdev->dev,
			"Failed to initialise managed register map\n");
		वापस PTR_ERR(i2s->regmap);
	पूर्ण

	i2s->playback_dma_data.addr = res->start + I2S_TXDR;
	i2s->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->playback_dma_data.maxburst = 4;

	i2s->capture_dma_data.addr = res->start + I2S_RXDR;
	i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->capture_dma_data.maxburst = 4;

	dev_set_drvdata(&pdev->dev, i2s);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = i2s_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	soc_dai = devm_kmemdup(&pdev->dev, &rockchip_i2s_dai,
			       माप(*soc_dai), GFP_KERNEL);
	अगर (!soc_dai) अणु
		ret = -ENOMEM;
		जाओ err_pm_disable;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "rockchip,playback-channels", &val)) अणु
		अगर (val >= 2 && val <= 8)
			soc_dai->playback.channels_max = val;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "rockchip,capture-channels", &val)) अणु
		अगर (val >= 2 && val <= 8)
			soc_dai->capture.channels_max = val;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &rockchip_i2s_component,
					      soc_dai, 1);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI\n");
		जाओ err_suspend;
	पूर्ण

	ret = rockchip_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM\n");
		जाओ err_suspend;
	पूर्ण

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		i2s_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_i2s_dev *i2s = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		i2s_runसमय_suspend(&pdev->dev);

	clk_disable_unprepare(i2s->hclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rockchip_i2s_pm_ops = अणु
	SET_RUNTIME_PM_OPS(i2s_runसमय_suspend, i2s_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver rockchip_i2s_driver = अणु
	.probe = rockchip_i2s_probe,
	.हटाओ = rockchip_i2s_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(rockchip_i2s_match),
		.pm = &rockchip_i2s_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rockchip_i2s_driver);

MODULE_DESCRIPTION("ROCKCHIP IIS ASoC Interface");
MODULE_AUTHOR("jianqun <jay.xu@rock-chips.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, rockchip_i2s_match);
