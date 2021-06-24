<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediatek 8173 ALSA SoC AFE platक्रमm driver
 *
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Koro Chen <koro.chen@mediatek.com>
 *             Sascha Hauer <s.hauer@pengutronix.de>
 *             Hidalgo Huang <hidalgo.huang@mediatek.com>
 *             Ir Lian <ir.lian@mediatek.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश "mt8173-afe-common.h"
#समावेश "../common/mtk-base-afe.h"
#समावेश "../common/mtk-afe-platform-driver.h"
#समावेश "../common/mtk-afe-fe-dai.h"

/*****************************************************************************
 *                  R E G I S T E R       D E F I N I T I O N
 *****************************************************************************/
#घोषणा AUDIO_TOP_CON0		0x0000
#घोषणा AUDIO_TOP_CON1		0x0004
#घोषणा AFE_DAC_CON0		0x0010
#घोषणा AFE_DAC_CON1		0x0014
#घोषणा AFE_I2S_CON1		0x0034
#घोषणा AFE_I2S_CON2		0x0038
#घोषणा AFE_CONN_24BIT		0x006c
#घोषणा AFE_MEMIF_MSB		0x00cc

#घोषणा AFE_CONN1		0x0024
#घोषणा AFE_CONN2		0x0028
#घोषणा AFE_CONN3		0x002c
#घोषणा AFE_CONN7		0x0460
#घोषणा AFE_CONN8		0x0464
#घोषणा AFE_HDMI_CONN0		0x0390

/* Memory पूर्णांकerface */
#घोषणा AFE_DL1_BASE		0x0040
#घोषणा AFE_DL1_CUR		0x0044
#घोषणा AFE_DL1_END		0x0048
#घोषणा AFE_DL2_BASE		0x0050
#घोषणा AFE_DL2_CUR		0x0054
#घोषणा AFE_AWB_BASE		0x0070
#घोषणा AFE_AWB_CUR		0x007c
#घोषणा AFE_VUL_BASE		0x0080
#घोषणा AFE_VUL_CUR		0x008c
#घोषणा AFE_VUL_END		0x0088
#घोषणा AFE_DAI_BASE		0x0090
#घोषणा AFE_DAI_CUR		0x009c
#घोषणा AFE_MOD_PCM_BASE	0x0330
#घोषणा AFE_MOD_PCM_CUR		0x033c
#घोषणा AFE_HDMI_OUT_BASE	0x0374
#घोषणा AFE_HDMI_OUT_CUR	0x0378
#घोषणा AFE_HDMI_OUT_END	0x037c

#घोषणा AFE_ADDA_TOP_CON0	0x0120
#घोषणा AFE_ADDA2_TOP_CON0	0x0600

#घोषणा AFE_HDMI_OUT_CON0	0x0370

#घोषणा AFE_IRQ_MCU_CON		0x03a0
#घोषणा AFE_IRQ_STATUS		0x03a4
#घोषणा AFE_IRQ_CLR		0x03a8
#घोषणा AFE_IRQ_CNT1		0x03ac
#घोषणा AFE_IRQ_CNT2		0x03b0
#घोषणा AFE_IRQ_MCU_EN		0x03b4
#घोषणा AFE_IRQ_CNT5		0x03bc
#घोषणा AFE_IRQ_CNT7		0x03dc

#घोषणा AFE_TDM_CON1		0x0548
#घोषणा AFE_TDM_CON2		0x054c

#घोषणा AFE_IRQ_STATUS_BITS	0xff

/* AUDIO_TOP_CON0 (0x0000) */
#घोषणा AUD_TCON0_PDN_SPDF		(0x1 << 21)
#घोषणा AUD_TCON0_PDN_HDMI		(0x1 << 20)
#घोषणा AUD_TCON0_PDN_24M		(0x1 << 9)
#घोषणा AUD_TCON0_PDN_22M		(0x1 << 8)
#घोषणा AUD_TCON0_PDN_AFE		(0x1 << 2)

/* AFE_I2S_CON1 (0x0034) */
#घोषणा AFE_I2S_CON1_LOW_JITTER_CLK	(0x1 << 12)
#घोषणा AFE_I2S_CON1_RATE(x)		(((x) & 0xf) << 8)
#घोषणा AFE_I2S_CON1_FORMAT_I2S		(0x1 << 3)
#घोषणा AFE_I2S_CON1_EN			(0x1 << 0)

/* AFE_I2S_CON2 (0x0038) */
#घोषणा AFE_I2S_CON2_LOW_JITTER_CLK	(0x1 << 12)
#घोषणा AFE_I2S_CON2_RATE(x)		(((x) & 0xf) << 8)
#घोषणा AFE_I2S_CON2_FORMAT_I2S		(0x1 << 3)
#घोषणा AFE_I2S_CON2_EN			(0x1 << 0)

/* AFE_CONN_24BIT (0x006c) */
#घोषणा AFE_CONN_24BIT_O04		(0x1 << 4)
#घोषणा AFE_CONN_24BIT_O03		(0x1 << 3)

/* AFE_HDMI_CONN0 (0x0390) */
#घोषणा AFE_HDMI_CONN0_O37_I37		(0x7 << 21)
#घोषणा AFE_HDMI_CONN0_O36_I36		(0x6 << 18)
#घोषणा AFE_HDMI_CONN0_O35_I33		(0x3 << 15)
#घोषणा AFE_HDMI_CONN0_O34_I32		(0x2 << 12)
#घोषणा AFE_HDMI_CONN0_O33_I35		(0x5 << 9)
#घोषणा AFE_HDMI_CONN0_O32_I34		(0x4 << 6)
#घोषणा AFE_HDMI_CONN0_O31_I31		(0x1 << 3)
#घोषणा AFE_HDMI_CONN0_O30_I30		(0x0 << 0)

/* AFE_TDM_CON1 (0x0548) */
#घोषणा AFE_TDM_CON1_LRCK_WIDTH(x)	(((x) - 1) << 24)
#घोषणा AFE_TDM_CON1_32_BCK_CYCLES	(0x2 << 12)
#घोषणा AFE_TDM_CON1_WLEN_32BIT		(0x2 << 8)
#घोषणा AFE_TDM_CON1_MSB_ALIGNED	(0x1 << 4)
#घोषणा AFE_TDM_CON1_1_BCK_DELAY	(0x1 << 3)
#घोषणा AFE_TDM_CON1_LRCK_INV		(0x1 << 2)
#घोषणा AFE_TDM_CON1_BCK_INV		(0x1 << 1)
#घोषणा AFE_TDM_CON1_EN			(0x1 << 0)

क्रमागत afe_tdm_ch_start अणु
	AFE_TDM_CH_START_O30_O31 = 0,
	AFE_TDM_CH_START_O32_O33,
	AFE_TDM_CH_START_O34_O35,
	AFE_TDM_CH_START_O36_O37,
	AFE_TDM_CH_ZERO,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8173_afe_backup_list[] = अणु
	AUDIO_TOP_CON0,
	AFE_CONN1,
	AFE_CONN2,
	AFE_CONN7,
	AFE_CONN8,
	AFE_DAC_CON1,
	AFE_DL1_BASE,
	AFE_DL1_END,
	AFE_VUL_BASE,
	AFE_VUL_END,
	AFE_HDMI_OUT_BASE,
	AFE_HDMI_OUT_END,
	AFE_HDMI_CONN0,
	AFE_DAC_CON0,
पूर्ण;

काष्ठा mt8173_afe_निजी अणु
	काष्ठा clk *घड़ीs[MT8173_CLK_NUM];
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware mt8173_afe_hardware = अणु
	.info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_MMAP_VALID),
	.buffer_bytes_max = 256 * 1024,
	.period_bytes_min = 512,
	.period_bytes_max = 128 * 1024,
	.periods_min = 2,
	.periods_max = 256,
	.fअगरo_size = 0,
पूर्ण;

काष्ठा mt8173_afe_rate अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक regvalue;
पूर्ण;

अटल स्थिर काष्ठा mt8173_afe_rate mt8173_afe_i2s_rates[] = अणु
	अणु .rate = 8000, .regvalue = 0 पूर्ण,
	अणु .rate = 11025, .regvalue = 1 पूर्ण,
	अणु .rate = 12000, .regvalue = 2 पूर्ण,
	अणु .rate = 16000, .regvalue = 4 पूर्ण,
	अणु .rate = 22050, .regvalue = 5 पूर्ण,
	अणु .rate = 24000, .regvalue = 6 पूर्ण,
	अणु .rate = 32000, .regvalue = 8 पूर्ण,
	अणु .rate = 44100, .regvalue = 9 पूर्ण,
	अणु .rate = 48000, .regvalue = 10 पूर्ण,
	अणु .rate = 88000, .regvalue = 11 पूर्ण,
	अणु .rate = 96000, .regvalue = 12 पूर्ण,
	अणु .rate = 174000, .regvalue = 13 पूर्ण,
	अणु .rate = 192000, .regvalue = 14 पूर्ण,
पूर्ण;

अटल पूर्णांक mt8173_afe_i2s_fs(अचिन्हित पूर्णांक sample_rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt8173_afe_i2s_rates); i++)
		अगर (mt8173_afe_i2s_rates[i].rate == sample_rate)
			वापस mt8173_afe_i2s_rates[i].regvalue;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt8173_afe_set_i2s(काष्ठा mtk_base_afe *afe, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक fs = mt8173_afe_i2s_fs(rate);

	अगर (fs < 0)
		वापस -EINVAL;

	/* from बाह्यal ADC */
	regmap_update_bits(afe->regmap, AFE_ADDA_TOP_CON0, 0x1, 0x1);
	regmap_update_bits(afe->regmap, AFE_ADDA2_TOP_CON0, 0x1, 0x1);

	/* set input */
	val = AFE_I2S_CON2_LOW_JITTER_CLK |
	      AFE_I2S_CON2_RATE(fs) |
	      AFE_I2S_CON2_FORMAT_I2S;

	regmap_update_bits(afe->regmap, AFE_I2S_CON2, ~AFE_I2S_CON2_EN, val);

	/* set output */
	val = AFE_I2S_CON1_LOW_JITTER_CLK |
	      AFE_I2S_CON1_RATE(fs) |
	      AFE_I2S_CON1_FORMAT_I2S;

	regmap_update_bits(afe->regmap, AFE_I2S_CON1, ~AFE_I2S_CON1_EN, val);
	वापस 0;
पूर्ण

अटल व्योम mt8173_afe_set_i2s_enable(काष्ठा mtk_base_afe *afe, bool enable)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(afe->regmap, AFE_I2S_CON2, &val);
	अगर (!!(val & AFE_I2S_CON2_EN) == enable)
		वापस;

	/* input */
	regmap_update_bits(afe->regmap, AFE_I2S_CON2, 0x1, enable);

	/* output */
	regmap_update_bits(afe->regmap, AFE_I2S_CON1, 0x1, enable);
पूर्ण

अटल पूर्णांक mt8173_afe_dais_enable_clks(काष्ठा mtk_base_afe *afe,
				       काष्ठा clk *m_ck, काष्ठा clk *b_ck)
अणु
	पूर्णांक ret;

	अगर (m_ck) अणु
		ret = clk_prepare_enable(m_ck);
		अगर (ret) अणु
			dev_err(afe->dev, "Failed to enable m_ck\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (b_ck) अणु
		ret = clk_prepare_enable(b_ck);
		अगर (ret) अणु
			dev_err(afe->dev, "Failed to enable b_ck\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt8173_afe_dais_set_clks(काष्ठा mtk_base_afe *afe,
				    काष्ठा clk *m_ck, अचिन्हित पूर्णांक mck_rate,
				    काष्ठा clk *b_ck, अचिन्हित पूर्णांक bck_rate)
अणु
	पूर्णांक ret;

	अगर (m_ck) अणु
		ret = clk_set_rate(m_ck, mck_rate);
		अगर (ret) अणु
			dev_err(afe->dev, "Failed to set m_ck rate\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (b_ck) अणु
		ret = clk_set_rate(b_ck, bck_rate);
		अगर (ret) अणु
			dev_err(afe->dev, "Failed to set b_ck rate\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mt8173_afe_dais_disable_clks(काष्ठा mtk_base_afe *afe,
					 काष्ठा clk *m_ck, काष्ठा clk *b_ck)
अणु
	अगर (m_ck)
		clk_disable_unprepare(m_ck);
	अगर (b_ck)
		clk_disable_unprepare(b_ck);
पूर्ण

अटल पूर्णांक mt8173_afe_i2s_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	अगर (snd_soc_dai_active(dai))
		वापस 0;

	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M, 0);
	वापस 0;
पूर्ण

अटल व्योम mt8173_afe_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	अगर (snd_soc_dai_active(dai))
		वापस;

	mt8173_afe_set_i2s_enable(afe, false);
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M);
पूर्ण

अटल पूर्णांक mt8173_afe_i2s_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय * स्थिर runसमय = substream->runसमय;
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	mt8173_afe_dais_set_clks(afe, afe_priv->घड़ीs[MT8173_CLK_I2S1_M],
				 runसमय->rate * 256, शून्य, 0);
	mt8173_afe_dais_set_clks(afe, afe_priv->घड़ीs[MT8173_CLK_I2S2_M],
				 runसमय->rate * 256, शून्य, 0);
	/* config I2S */
	ret = mt8173_afe_set_i2s(afe, substream->runसमय->rate);
	अगर (ret)
		वापस ret;

	mt8173_afe_set_i2s_enable(afe, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mt8173_afe_hdmi_startup(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;

	अगर (snd_soc_dai_active(dai))
		वापस 0;

	mt8173_afe_dais_enable_clks(afe, afe_priv->घड़ीs[MT8173_CLK_I2S3_M],
				    afe_priv->घड़ीs[MT8173_CLK_I2S3_B]);
	वापस 0;
पूर्ण

अटल व्योम mt8173_afe_hdmi_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;

	अगर (snd_soc_dai_active(dai))
		वापस;

	mt8173_afe_dais_disable_clks(afe, afe_priv->घड़ीs[MT8173_CLK_I2S3_M],
				     afe_priv->घड़ीs[MT8173_CLK_I2S3_B]);
पूर्ण

अटल पूर्णांक mt8173_afe_hdmi_prepare(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय * स्थिर runसमय = substream->runसमय;
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;

	अचिन्हित पूर्णांक val;

	mt8173_afe_dais_set_clks(afe, afe_priv->घड़ीs[MT8173_CLK_I2S3_M],
				 runसमय->rate * 128,
				 afe_priv->घड़ीs[MT8173_CLK_I2S3_B],
				 runसमय->rate * runसमय->channels * 32);

	val = AFE_TDM_CON1_BCK_INV |
	      AFE_TDM_CON1_LRCK_INV |
	      AFE_TDM_CON1_1_BCK_DELAY |
	      AFE_TDM_CON1_MSB_ALIGNED | /* I2S mode */
	      AFE_TDM_CON1_WLEN_32BIT |
	      AFE_TDM_CON1_32_BCK_CYCLES |
	      AFE_TDM_CON1_LRCK_WIDTH(32);
	regmap_update_bits(afe->regmap, AFE_TDM_CON1, ~AFE_TDM_CON1_EN, val);

	/* set tdm2 config */
	चयन (runसमय->channels) अणु
	हाल 1:
	हाल 2:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_ZERO << 4);
		val |= (AFE_TDM_CH_ZERO << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		अवरोध;
	हाल 3:
	हाल 4:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_ZERO << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		अवरोध;
	हाल 5:
	हाल 6:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_START_O34_O35 << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		अवरोध;
	हाल 7:
	हाल 8:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_START_O34_O35 << 8);
		val |= (AFE_TDM_CH_START_O36_O37 << 12);
		अवरोध;
	शेष:
		val = 0;
	पूर्ण
	regmap_update_bits(afe->regmap, AFE_TDM_CON2, 0x0000ffff, val);

	regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
			   0x000000f0, runसमय->channels << 4);
	वापस 0;
पूर्ण

अटल पूर्णांक mt8173_afe_hdmi_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	dev_info(afe->dev, "%s cmd=%d %s\n", __func__, cmd, dai->name);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF, 0);

		/* set connections:  O30~O37: L/R/LS/RS/C/LFE/CH7/CH8 */
		regmap_ग_लिखो(afe->regmap, AFE_HDMI_CONN0,
				 AFE_HDMI_CONN0_O30_I30 |
				 AFE_HDMI_CONN0_O31_I31 |
				 AFE_HDMI_CONN0_O32_I34 |
				 AFE_HDMI_CONN0_O33_I35 |
				 AFE_HDMI_CONN0_O34_I32 |
				 AFE_HDMI_CONN0_O35_I33 |
				 AFE_HDMI_CONN0_O36_I36 |
				 AFE_HDMI_CONN0_O37_I37);

		/* enable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0, 0x1, 0x1);

		/* enable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1, 0x1, 0x1);

		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		/* disable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1, 0x1, 0);

		/* disable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0, 0x1, 0);

		regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt8173_memअगर_fs(काष्ठा snd_pcm_substream *substream,
			   अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक fs;

	अगर (memअगर->data->id == MT8173_AFE_MEMIF_DAI ||
	    memअगर->data->id == MT8173_AFE_MEMIF_MOD_DAI) अणु
		चयन (rate) अणु
		हाल 8000:
			fs = 0;
			अवरोध;
		हाल 16000:
			fs = 1;
			अवरोध;
		हाल 32000:
			fs = 2;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		fs = mt8173_afe_i2s_fs(rate);
	पूर्ण
	वापस fs;
पूर्ण

अटल पूर्णांक mt8173_irq_fs(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक rate)
अणु
	वापस mt8173_afe_i2s_fs(rate);
पूर्ण

/* BE DAIs */
अटल स्थिर काष्ठा snd_soc_dai_ops mt8173_afe_i2s_ops = अणु
	.startup	= mt8173_afe_i2s_startup,
	.shutकरोwn	= mt8173_afe_i2s_shutकरोwn,
	.prepare	= mt8173_afe_i2s_prepare,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops mt8173_afe_hdmi_ops = अणु
	.startup	= mt8173_afe_hdmi_startup,
	.shutकरोwn	= mt8173_afe_hdmi_shutकरोwn,
	.prepare	= mt8173_afe_hdmi_prepare,
	.trigger	= mt8173_afe_hdmi_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mt8173_afe_pcm_dais[] = अणु
	/* FE DAIs: memory पूर्णांकefaces to CPU */
	अणु
		.name = "DL1", /* करोwnlink 1 */
		.id = MT8173_AFE_MEMIF_DL1,
		.playback = अणु
			.stream_name = "DL1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण, अणु
		.name = "VUL", /* voice uplink */
		.id = MT8173_AFE_MEMIF_VUL,
		.capture = अणु
			.stream_name = "VUL",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण, अणु
	/* BE DAIs */
		.name = "I2S",
		.id = MT8173_AFE_IO_I2S,
		.playback = अणु
			.stream_name = "I2S Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "I2S Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mt8173_afe_i2s_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mt8173_afe_hdmi_dais[] = अणु
	/* FE DAIs */
	अणु
		.name = "HDMI",
		.id = MT8173_AFE_MEMIF_HDMI,
		.playback = अणु
			.stream_name = "HDMI",
			.channels_min = 2,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
				SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
				SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण, अणु
	/* BE DAIs */
		.name = "HDMIO",
		.id = MT8173_AFE_IO_HDMI,
		.playback = अणु
			.stream_name = "HDMIO Playback",
			.channels_min = 2,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
				SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
				SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &mt8173_afe_hdmi_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_afe_o03_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I05 Switch", AFE_CONN1, 21, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_afe_o04_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I06 Switch", AFE_CONN2, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_afe_o09_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I03 Switch", AFE_CONN3, 0, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I17 Switch", AFE_CONN7, 30, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_afe_o10_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I04 Switch", AFE_CONN3, 3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I18 Switch", AFE_CONN8, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8173_afe_pcm_widमाला_लो[] = अणु
	/* पूर्णांकer-connections */
	SND_SOC_DAPM_MIXER("I03", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I04", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I05", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I06", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I17", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("I18", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("O03", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o03_mix, ARRAY_SIZE(mt8173_afe_o03_mix)),
	SND_SOC_DAPM_MIXER("O04", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o04_mix, ARRAY_SIZE(mt8173_afe_o04_mix)),
	SND_SOC_DAPM_MIXER("O09", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o09_mix, ARRAY_SIZE(mt8173_afe_o09_mix)),
	SND_SOC_DAPM_MIXER("O10", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o10_mix, ARRAY_SIZE(mt8173_afe_o10_mix)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8173_afe_pcm_routes[] = अणु
	अणु"I05", शून्य, "DL1"पूर्ण,
	अणु"I06", शून्य, "DL1"पूर्ण,
	अणु"I2S Playback", शून्य, "O03"पूर्ण,
	अणु"I2S Playback", शून्य, "O04"पूर्ण,
	अणु"VUL", शून्य, "O09"पूर्ण,
	अणु"VUL", शून्य, "O10"पूर्ण,
	अणु"I03", शून्य, "I2S Capture"पूर्ण,
	अणु"I04", शून्य, "I2S Capture"पूर्ण,
	अणु"I17", शून्य, "I2S Capture"पूर्ण,
	अणु"I18", शून्य, "I2S Capture"पूर्ण,
	अणु "O03", "I05 Switch", "I05" पूर्ण,
	अणु "O04", "I06 Switch", "I06" पूर्ण,
	अणु "O09", "I17 Switch", "I17" पूर्ण,
	अणु "O09", "I03 Switch", "I03" पूर्ण,
	अणु "O10", "I18 Switch", "I18" पूर्ण,
	अणु "O10", "I04 Switch", "I04" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8173_afe_hdmi_routes[] = अणु
	अणु"HDMIO Playback", शून्य, "HDMI"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mt8173_afe_pcm_dai_component = अणु
	.name = "mt8173-afe-pcm-dai",
	.dapm_widमाला_लो = mt8173_afe_pcm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8173_afe_pcm_widमाला_लो),
	.dapm_routes = mt8173_afe_pcm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8173_afe_pcm_routes),
	.suspend = mtk_afe_suspend,
	.resume = mtk_afe_resume,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mt8173_afe_hdmi_dai_component = अणु
	.name = "mt8173-afe-hdmi-dai",
	.dapm_routes = mt8173_afe_hdmi_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8173_afe_hdmi_routes),
	.suspend = mtk_afe_suspend,
	.resume = mtk_afe_resume,
पूर्ण;

अटल स्थिर अक्षर *aud_clks[MT8173_CLK_NUM] = अणु
	[MT8173_CLK_INFRASYS_AUD] = "infra_sys_audio_clk",
	[MT8173_CLK_TOP_PDN_AUD] = "top_pdn_audio",
	[MT8173_CLK_TOP_PDN_AUD_BUS] = "top_pdn_aud_intbus",
	[MT8173_CLK_I2S0_M] =  "i2s0_m",
	[MT8173_CLK_I2S1_M] =  "i2s1_m",
	[MT8173_CLK_I2S2_M] =  "i2s2_m",
	[MT8173_CLK_I2S3_M] =  "i2s3_m",
	[MT8173_CLK_I2S3_B] =  "i2s3_b",
	[MT8173_CLK_BCK0] =  "bck0",
	[MT8173_CLK_BCK1] =  "bck1",
पूर्ण;

अटल स्थिर काष्ठा mtk_base_memअगर_data memअगर_data[MT8173_AFE_MEMIF_NUM] = अणु
	अणु
		.name = "DL1",
		.id = MT8173_AFE_MEMIF_DL1,
		.reg_ofs_base = AFE_DL1_BASE,
		.reg_ofs_cur = AFE_DL1_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 0,
		.fs_maskbit = 0xf,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = 21,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 1,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 0,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "DL2",
		.id = MT8173_AFE_MEMIF_DL2,
		.reg_ofs_base = AFE_DL2_BASE,
		.reg_ofs_cur = AFE_DL2_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 4,
		.fs_maskbit = 0xf,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = 22,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 2,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 1,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "VUL",
		.id = MT8173_AFE_MEMIF_VUL,
		.reg_ofs_base = AFE_VUL_BASE,
		.reg_ofs_cur = AFE_VUL_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 16,
		.fs_maskbit = 0xf,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = 27,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 3,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 6,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "DAI",
		.id = MT8173_AFE_MEMIF_DAI,
		.reg_ofs_base = AFE_DAI_BASE,
		.reg_ofs_cur = AFE_DAI_CUR,
		.fs_reg = AFE_DAC_CON0,
		.fs_shअगरt = 24,
		.fs_maskbit = 0x3,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 4,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 5,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "AWB",
		.id = MT8173_AFE_MEMIF_AWB,
		.reg_ofs_base = AFE_AWB_BASE,
		.reg_ofs_cur = AFE_AWB_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 12,
		.fs_maskbit = 0xf,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = 24,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 6,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 3,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "MOD_DAI",
		.id = MT8173_AFE_MEMIF_MOD_DAI,
		.reg_ofs_base = AFE_MOD_PCM_BASE,
		.reg_ofs_cur = AFE_MOD_PCM_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = 30,
		.fs_maskbit = 0x3,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = 30,
		.hd_reg = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = 7,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 4,
		.agent_disable_reg = -1,
	पूर्ण, अणु
		.name = "HDMI",
		.id = MT8173_AFE_MEMIF_HDMI,
		.reg_ofs_base = AFE_HDMI_OUT_BASE,
		.reg_ofs_cur = AFE_HDMI_OUT_CUR,
		.fs_reg = -1,
		.fs_shअगरt = -1,
		.fs_maskbit = -1,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.hd_reg = -1,
		.enable_reg = -1,
		.msb_reg = AFE_MEMIF_MSB,
		.msb_shअगरt = 8,
		.agent_disable_reg = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_irq_data irq_data[MT8173_AFE_IRQ_NUM] = अणु
	अणु
		.id = MT8173_AFE_IRQ_DL1,
		.irq_cnt_reg = AFE_IRQ_CNT1,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 0,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 4,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 0,
	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_DL2,
		.irq_cnt_reg = AFE_IRQ_CNT1,
		.irq_cnt_shअगरt = 20,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 2,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 16,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 2,

	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_VUL,
		.irq_cnt_reg = AFE_IRQ_CNT2,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 1,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 8,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 1,
	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_DAI,
		.irq_cnt_reg = AFE_IRQ_CNT2,
		.irq_cnt_shअगरt = 20,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 3,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 20,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 3,
	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_AWB,
		.irq_cnt_reg = AFE_IRQ_CNT7,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 14,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 24,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 6,
	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_DAI,
		.irq_cnt_reg = AFE_IRQ_CNT2,
		.irq_cnt_shअगरt = 20,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 3,
		.irq_fs_reg = AFE_IRQ_MCU_CON,
		.irq_fs_shअगरt = 20,
		.irq_fs_maskbit = 0xf,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 3,
	पूर्ण, अणु
		.id = MT8173_AFE_IRQ_HDMI,
		.irq_cnt_reg = AFE_IRQ_CNT5,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_en_reg = AFE_IRQ_MCU_CON,
		.irq_en_shअगरt = 12,
		.irq_fs_reg = -1,
		.irq_fs_maskbit = -1,
		.irq_clr_reg = AFE_IRQ_CLR,
		.irq_clr_shअगरt = 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mt8173_afe_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = AFE_ADDA2_TOP_CON0,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल irqवापस_t mt8173_afe_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_base_afe *afe = dev_id;
	अचिन्हित पूर्णांक reg_value;
	पूर्णांक i, ret;

	ret = regmap_पढ़ो(afe->regmap, AFE_IRQ_STATUS, &reg_value);
	अगर (ret) अणु
		dev_err(afe->dev, "%s irq status err\n", __func__);
		reg_value = AFE_IRQ_STATUS_BITS;
		जाओ err_irq;
	पूर्ण

	क्रम (i = 0; i < MT8173_AFE_MEMIF_NUM; i++) अणु
		काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[i];
		काष्ठा mtk_base_afe_irq *irq_p;

		अगर (memअगर->irq_usage < 0)
			जारी;

		irq_p = &afe->irqs[memअगर->irq_usage];

		अगर (!(reg_value & (1 << irq_p->irq_data->irq_clr_shअगरt)))
			जारी;

		snd_pcm_period_elapsed(memअगर->substream);
	पूर्ण

err_irq:
	/* clear irq */
	regmap_ग_लिखो(afe->regmap, AFE_IRQ_CLR,
		     reg_value & AFE_IRQ_STATUS_BITS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mt8173_afe_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;

	/* disable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, 0x1, 0);

	/* disable AFE clk */
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_AFE, AUD_TCON0_PDN_AFE);

	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_I2S1_M]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_I2S2_M]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_BCK0]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_BCK1]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD_BUS]);
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_INFRASYS_AUD]);
	वापस 0;
पूर्ण

अटल पूर्णांक mt8173_afe_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_INFRASYS_AUD]);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD_BUS]);
	अगर (ret)
		जाओ err_infra;

	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD]);
	अगर (ret)
		जाओ err_top_aud_bus;

	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_BCK0]);
	अगर (ret)
		जाओ err_top_aud;

	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_BCK1]);
	अगर (ret)
		जाओ err_bck0;
	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_I2S1_M]);
	अगर (ret)
		जाओ err_i2s1_m;
	ret = clk_prepare_enable(afe_priv->घड़ीs[MT8173_CLK_I2S2_M]);
	अगर (ret)
		जाओ err_i2s2_m;

	/* enable AFE clk */
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0, AUD_TCON0_PDN_AFE, 0);

	/* set O3/O4 16bits */
	regmap_update_bits(afe->regmap, AFE_CONN_24BIT,
			   AFE_CONN_24BIT_O03 | AFE_CONN_24BIT_O04, 0);

	/* unmask all IRQs */
	regmap_update_bits(afe->regmap, AFE_IRQ_MCU_EN, 0xff, 0xff);

	/* enable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, 0x1, 0x1);
	वापस 0;

err_i2s1_m:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_I2S1_M]);
err_i2s2_m:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_I2S2_M]);
err_bck0:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_BCK0]);
err_top_aud:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD]);
err_top_aud_bus:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_TOP_PDN_AUD_BUS]);
err_infra:
	clk_disable_unprepare(afe_priv->घड़ीs[MT8173_CLK_INFRASYS_AUD]);
	वापस ret;
पूर्ण

अटल पूर्णांक mt8173_afe_init_audio_clk(काष्ठा mtk_base_afe *afe)
अणु
	माप_प्रकार i;
	काष्ठा mt8173_afe_निजी *afe_priv = afe->platक्रमm_priv;

	क्रम (i = 0; i < ARRAY_SIZE(aud_clks); i++) अणु
		afe_priv->घड़ीs[i] = devm_clk_get(afe->dev, aud_clks[i]);
		अगर (IS_ERR(afe_priv->घड़ीs[i])) अणु
			dev_err(afe->dev, "%s devm_clk_get %s fail\n",
				__func__, aud_clks[i]);
			वापस PTR_ERR(afe_priv->घड़ीs[i]);
		पूर्ण
	पूर्ण
	clk_set_rate(afe_priv->घड़ीs[MT8173_CLK_BCK0], 22579200); /* 22M */
	clk_set_rate(afe_priv->घड़ीs[MT8173_CLK_BCK1], 24576000); /* 24M */
	वापस 0;
पूर्ण

अटल पूर्णांक mt8173_afe_pcm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i;
	पूर्णांक irq_id;
	काष्ठा mtk_base_afe *afe;
	काष्ठा mt8173_afe_निजी *afe_priv;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(33));
	अगर (ret)
		वापस ret;

	afe = devm_kzalloc(&pdev->dev, माप(*afe), GFP_KERNEL);
	अगर (!afe)
		वापस -ENOMEM;

	afe->platक्रमm_priv = devm_kzalloc(&pdev->dev, माप(*afe_priv),
					  GFP_KERNEL);
	afe_priv = afe->platक्रमm_priv;
	अगर (!afe_priv)
		वापस -ENOMEM;

	afe->dev = &pdev->dev;

	irq_id = platक्रमm_get_irq(pdev, 0);
	अगर (irq_id <= 0)
		वापस irq_id < 0 ? irq_id : -ENXIO;
	ret = devm_request_irq(afe->dev, irq_id, mt8173_afe_irq_handler,
			       0, "Afe_ISR_Handle", (व्योम *)afe);
	अगर (ret) अणु
		dev_err(afe->dev, "could not request_irq\n");
		वापस ret;
	पूर्ण

	afe->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(afe->base_addr))
		वापस PTR_ERR(afe->base_addr);

	afe->regmap = devm_regmap_init_mmio(&pdev->dev, afe->base_addr,
		&mt8173_afe_regmap_config);
	अगर (IS_ERR(afe->regmap))
		वापस PTR_ERR(afe->regmap);

	/* initial audio related घड़ी */
	ret = mt8173_afe_init_audio_clk(afe);
	अगर (ret) अणु
		dev_err(afe->dev, "mt8173_afe_init_audio_clk fail\n");
		वापस ret;
	पूर्ण

	/* memअगर % irq initialize*/
	afe->memअगर_size = MT8173_AFE_MEMIF_NUM;
	afe->memअगर = devm_kसुस्मृति(afe->dev, afe->memअगर_size,
				  माप(*afe->memअगर), GFP_KERNEL);
	अगर (!afe->memअगर)
		वापस -ENOMEM;

	afe->irqs_size = MT8173_AFE_IRQ_NUM;
	afe->irqs = devm_kसुस्मृति(afe->dev, afe->irqs_size,
				 माप(*afe->irqs), GFP_KERNEL);
	अगर (!afe->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->irqs_size; i++) अणु
		afe->memअगर[i].data = &memअगर_data[i];
		afe->irqs[i].irq_data = &irq_data[i];
		afe->irqs[i].irq_occupyed = true;
		afe->memअगर[i].irq_usage = i;
		afe->memअगर[i].स्थिर_irq = 1;
	पूर्ण

	afe->mtk_afe_hardware = &mt8173_afe_hardware;
	afe->memअगर_fs = mt8173_memअगर_fs;
	afe->irq_fs = mt8173_irq_fs;

	platक्रमm_set_drvdata(pdev, afe);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = mt8173_afe_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	afe->reg_back_up_list = mt8173_afe_backup_list;
	afe->reg_back_up_list_num = ARRAY_SIZE(mt8173_afe_backup_list);
	afe->runसमय_resume = mt8173_afe_runसमय_resume;
	afe->runसमय_suspend = mt8173_afe_runसमय_suspend;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					 &mtk_afe_pcm_platक्रमm,
					 शून्य, 0);
	अगर (ret)
		जाओ err_pm_disable;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					 &mt8173_afe_pcm_dai_component,
					 mt8173_afe_pcm_dais,
					 ARRAY_SIZE(mt8173_afe_pcm_dais));
	अगर (ret)
		जाओ err_pm_disable;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					 &mt8173_afe_hdmi_dai_component,
					 mt8173_afe_hdmi_dais,
					 ARRAY_SIZE(mt8173_afe_hdmi_dais));
	अगर (ret)
		जाओ err_pm_disable;

	dev_info(&pdev->dev, "MT8173 AFE driver initialized.\n");
	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mt8173_afe_pcm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mt8173_afe_runसमय_suspend(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8173_afe_pcm_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8173-afe-pcm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8173_afe_pcm_dt_match);

अटल स्थिर काष्ठा dev_pm_ops mt8173_afe_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt8173_afe_runसमय_suspend,
			   mt8173_afe_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mt8173_afe_pcm_driver = अणु
	.driver = अणु
		   .name = "mt8173-afe-pcm",
		   .of_match_table = mt8173_afe_pcm_dt_match,
		   .pm = &mt8173_afe_pm_ops,
	पूर्ण,
	.probe = mt8173_afe_pcm_dev_probe,
	.हटाओ = mt8173_afe_pcm_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(mt8173_afe_pcm_driver);

MODULE_DESCRIPTION("Mediatek ALSA SoC AFE platform driver");
MODULE_AUTHOR("Koro Chen <koro.chen@mediatek.com>");
MODULE_LICENSE("GPL v2");
