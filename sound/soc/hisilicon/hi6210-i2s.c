<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/soc/m8m/hi6210_i2s.c - I2S IP driver
 *
 * Copyright (C) 2015 Linaro, Ltd
 * Author: Andy Green <andy.green@linaro.org>
 *
 * This driver only deals with S2 पूर्णांकerface (BT)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reset-controller.h>

#समावेश "hi6210-i2s.h"

काष्ठा hi6210_i2s अणु
	काष्ठा device *dev;
	काष्ठा reset_control *rc;
	काष्ठा clk *clk[8];
	पूर्णांक घड़ीs;
	काष्ठा snd_soc_dai_driver dai;
	व्योम __iomem *base;
	काष्ठा regmap *sysctrl;
	phys_addr_t base_phys;
	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
	पूर्णांक clk_rate;
	spinlock_t lock;
	पूर्णांक rate;
	पूर्णांक क्रमmat;
	u8 bits;
	u8 channels;
	u8 id;
	u8 channel_length;
	u8 use;
	u32 master:1;
	u32 status:1;
पूर्ण;

#घोषणा SC_PERIPH_CLKEN1	0x210
#घोषणा SC_PERIPH_CLKDIS1	0x214

#घोषणा SC_PERIPH_CLKEN3	0x230
#घोषणा SC_PERIPH_CLKDIS3	0x234

#घोषणा SC_PERIPH_CLKEN12	0x270
#घोषणा SC_PERIPH_CLKDIS12	0x274

#घोषणा SC_PERIPH_RSTEN1	0x310
#घोषणा SC_PERIPH_RSTDIS1	0x314
#घोषणा SC_PERIPH_RSTSTAT1	0x318

#घोषणा SC_PERIPH_RSTEN2	0x320
#घोषणा SC_PERIPH_RSTDIS2	0x324
#घोषणा SC_PERIPH_RSTSTAT2	0x328

#घोषणा SOC_PMCTRL_BBPPLLALIAS	0x48

क्रमागत अणु
	CLK_DACODEC,
	CLK_I2S_BASE,
पूर्ण;

अटल अंतरभूत व्योम hi6210_ग_लिखो_reg(काष्ठा hi6210_i2s *i2s, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, i2s->base + reg);
पूर्ण

अटल अंतरभूत u32 hi6210_पढ़ो_reg(काष्ठा hi6210_i2s *i2s, पूर्णांक reg)
अणु
	वापस पढ़ोl(i2s->base + reg);
पूर्ण

अटल पूर्णांक hi6210_i2s_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक ret, n;
	u32 val;

	/* deनिश्चित reset on ABB */
	regmap_पढ़ो(i2s->sysctrl, SC_PERIPH_RSTSTAT2, &val);
	अगर (val & BIT(4))
		regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_RSTDIS2, BIT(4));

	क्रम (n = 0; n < i2s->घड़ीs; n++) अणु
		ret = clk_prepare_enable(i2s->clk[n]);
		अगर (ret) अणु
			जबतक (n--)
				clk_disable_unprepare(i2s->clk[n]);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_set_rate(i2s->clk[CLK_I2S_BASE], 49152000);
	अगर (ret) अणु
		dev_err(i2s->dev, "%s: setting 49.152MHz base rate failed %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* enable घड़ी beक्रमe frequency भागision */
	regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_CLKEN12, BIT(9));

	/* enable codec working घड़ी / == "codec bus clock" */
	regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_CLKEN1, BIT(5));

	/* deनिश्चित reset on codec / पूर्णांकerface घड़ी / working घड़ी */
	regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_RSTEN1, BIT(5));
	regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_RSTDIS1, BIT(5));

	/* not पूर्णांकerested in i2s irqs */
	val = hi6210_पढ़ो_reg(i2s, HII2S_CODEC_IRQ_MASK);
	val |= 0x3f;
	hi6210_ग_लिखो_reg(i2s, HII2S_CODEC_IRQ_MASK, val);


	/* reset the stereo करोwnlink fअगरo */
	val = hi6210_पढ़ो_reg(i2s, HII2S_APB_AFIFO_CFG_1);
	val |= (BIT(5) | BIT(4));
	hi6210_ग_लिखो_reg(i2s, HII2S_APB_AFIFO_CFG_1, val);

	val = hi6210_पढ़ो_reg(i2s, HII2S_APB_AFIFO_CFG_1);
	val &= ~(BIT(5) | BIT(4));
	hi6210_ग_लिखो_reg(i2s, HII2S_APB_AFIFO_CFG_1, val);


	val = hi6210_पढ़ो_reg(i2s, HII2S_SW_RST_N);
	val &= ~(HII2S_SW_RST_N__ST_DL_WORDLEN_MASK <<
			HII2S_SW_RST_N__ST_DL_WORDLEN_SHIFT);
	val |= (HII2S_BITS_16 << HII2S_SW_RST_N__ST_DL_WORDLEN_SHIFT);
	hi6210_ग_लिखो_reg(i2s, HII2S_SW_RST_N, val);

	val = hi6210_पढ़ो_reg(i2s, HII2S_MISC_CFG);
	/* mux 11/12 = APB not i2s */
	val &= ~HII2S_MISC_CFG__ST_DL_TEST_SEL;
	/* BT R ch  0 = mixer op of DACR ch */
	val &= ~HII2S_MISC_CFG__S2_DOUT_RIGHT_SEL;
	val &= ~HII2S_MISC_CFG__S2_DOUT_TEST_SEL;

	val |= HII2S_MISC_CFG__S2_DOUT_RIGHT_SEL;
	/* BT L ch = 1 = mux 7 = "mixer output of DACL */
	val |= HII2S_MISC_CFG__S2_DOUT_TEST_SEL;
	hi6210_ग_लिखो_reg(i2s, HII2S_MISC_CFG, val);

	val = hi6210_पढ़ो_reg(i2s, HII2S_SW_RST_N);
	val |= HII2S_SW_RST_N__SW_RST_N;
	hi6210_ग_लिखो_reg(i2s, HII2S_SW_RST_N, val);

	वापस 0;
पूर्ण

अटल व्योम hi6210_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक n;

	क्रम (n = 0; n < i2s->घड़ीs; n++)
		clk_disable_unprepare(i2s->clk[n]);

	regmap_ग_लिखो(i2s->sysctrl, SC_PERIPH_RSTEN1, BIT(5));
पूर्ण

अटल व्योम hi6210_i2s_txctrl(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक on)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	u32 val;

	spin_lock(&i2s->lock);
	अगर (on) अणु
		/* enable S2 TX */
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_IF_TX_EN;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
	पूर्ण अन्यथा अणु
		/* disable S2 TX */
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_IF_TX_EN;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
	पूर्ण
	spin_unlock(&i2s->lock);
पूर्ण

अटल व्योम hi6210_i2s_rxctrl(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक on)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	u32 val;

	spin_lock(&i2s->lock);
	अगर (on) अणु
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_IF_RX_EN;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
	पूर्ण अन्यथा अणु
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_IF_RX_EN;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
	पूर्ण
	spin_unlock(&i2s->lock);
पूर्ण

अटल पूर्णांक hi6210_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);

	/*
	 * We करोn't actually set the hardware until the hw_params
	 * call, but we need to validate the user input here.
	 */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	i2s->क्रमmat = fmt;
	i2s->master = (i2s->क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) ==
		      SND_SOC_DAIFMT_CBS_CFS;

	वापस 0;
पूर्ण

अटल पूर्णांक hi6210_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	u32 bits = 0, rate = 0, चिन्हित_data = 0, fmt = 0;
	u32 val;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_U16_LE:
		चिन्हित_data = HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		bits = HII2S_BITS_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_U24_LE:
		चिन्हित_data = HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		bits = HII2S_BITS_24;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Bad format\n");
		वापस -EINVAL;
	पूर्ण


	चयन (params_rate(params)) अणु
	हाल 8000:
		rate = HII2S_FS_RATE_8KHZ;
		अवरोध;
	हाल 16000:
		rate = HII2S_FS_RATE_16KHZ;
		अवरोध;
	हाल 32000:
		rate = HII2S_FS_RATE_32KHZ;
		अवरोध;
	हाल 48000:
		rate = HII2S_FS_RATE_48KHZ;
		अवरोध;
	हाल 96000:
		rate = HII2S_FS_RATE_96KHZ;
		अवरोध;
	हाल 192000:
		rate = HII2S_FS_RATE_192KHZ;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Bad rate: %d\n", params_rate(params));
		वापस -EINVAL;
	पूर्ण

	अगर (!(params_channels(params))) अणु
		dev_err(cpu_dai->dev, "Bad channels\n");
		वापस -EINVAL;
	पूर्ण

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substream);

	चयन (bits) अणु
	हाल HII2S_BITS_24:
		i2s->bits = 32;
		dma_data->addr_width = 3;
		अवरोध;
	शेष:
		i2s->bits = 16;
		dma_data->addr_width = 2;
		अवरोध;
	पूर्ण
	i2s->rate = params_rate(params);
	i2s->channels = params_channels(params);
	i2s->channel_length = i2s->channels * i2s->bits;

	val = hi6210_पढ़ो_reg(i2s, HII2S_ST_DL_FIFO_TH_CFG);
	val &= ~((HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_SHIFT));
	val |= ((16 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_SHIFT) |
		(30 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_SHIFT) |
		(16 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_SHIFT) |
		(30 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_SHIFT));
	hi6210_ग_लिखो_reg(i2s, HII2S_ST_DL_FIFO_TH_CFG, val);


	val = hi6210_पढ़ो_reg(i2s, HII2S_IF_CLK_EN_CFG);
	val |= (BIT(19) | BIT(18) | BIT(17) |
		HII2S_IF_CLK_EN_CFG__S2_IF_CLK_EN |
		HII2S_IF_CLK_EN_CFG__S2_OL_MIXER_EN |
		HII2S_IF_CLK_EN_CFG__S2_OL_SRC_EN |
		HII2S_IF_CLK_EN_CFG__ST_DL_R_EN |
		HII2S_IF_CLK_EN_CFG__ST_DL_L_EN);
	hi6210_ग_लिखो_reg(i2s, HII2S_IF_CLK_EN_CFG, val);


	val = hi6210_पढ़ो_reg(i2s, HII2S_DIG_FILTER_CLK_EN_CFG);
	val &= ~(HII2S_DIG_FILTER_CLK_EN_CFG__DACR_SDM_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACR_HBF2I_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACR_AGC_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_SDM_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_HBF2I_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_AGC_EN);
	val |= (HII2S_DIG_FILTER_CLK_EN_CFG__DACR_MIXER_EN |
		HII2S_DIG_FILTER_CLK_EN_CFG__DACL_MIXER_EN);
	hi6210_ग_लिखो_reg(i2s, HII2S_DIG_FILTER_CLK_EN_CFG, val);


	val = hi6210_पढ़ो_reg(i2s, HII2S_DIG_FILTER_MODULE_CFG);
	val &= ~(HII2S_DIG_FILTER_MODULE_CFG__DACR_MIXER_IN2_MUTE |
		 HII2S_DIG_FILTER_MODULE_CFG__DACL_MIXER_IN2_MUTE);
	hi6210_ग_लिखो_reg(i2s, HII2S_DIG_FILTER_MODULE_CFG, val);

	val = hi6210_पढ़ो_reg(i2s, HII2S_MUX_TOP_MODULE_CFG);
	val &= ~(HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN1_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN2_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN1_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN2_MUTE);
	hi6210_ग_लिखो_reg(i2s, HII2S_MUX_TOP_MODULE_CFG, val);


	चयन (i2s->क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		i2s->master = false;
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_MST_SLV;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		i2s->master = true;
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_MST_SLV;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid i2s->fmt MASTER_MASK. This shouldn't happen\n");
		वापस -EINVAL;
	पूर्ण

	चयन (i2s->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		fmt = HII2S_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		fmt = HII2S_FORMAT_LEFT_JUST;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		fmt = HII2S_FORMAT_RIGHT_JUST;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid i2s->fmt FORMAT_MASK. This shouldn't happen\n");
		वापस -EINVAL;
	पूर्ण

	val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
	val &= ~(HII2S_I2S_CFG__S2_FUNC_MODE_MASK <<
			HII2S_I2S_CFG__S2_FUNC_MODE_SHIFT);
	val |= fmt << HII2S_I2S_CFG__S2_FUNC_MODE_SHIFT;
	hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);


	val = hi6210_पढ़ो_reg(i2s, HII2S_CLK_SEL);
	val &= ~(HII2S_CLK_SEL__I2S_BT_FM_SEL | /* BT माला_लो the I2S */
			HII2S_CLK_SEL__EXT_12_288MHZ_SEL);
	hi6210_ग_लिखो_reg(i2s, HII2S_CLK_SEL, val);

	dma_data->maxburst = 2;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data->addr = i2s->base_phys + HII2S_ST_DL_CHANNEL;
	अन्यथा
		dma_data->addr = i2s->base_phys + HII2S_STEREO_UPLINK_CHANNEL;

	चयन (i2s->channels) अणु
	हाल 1:
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_FRAME_MODE;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
		अवरोध;
	शेष:
		val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_FRAME_MODE;
		hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);
		अवरोध;
	पूर्ण

	/* clear loopback, set चिन्हित type and word length */
	val = hi6210_पढ़ो_reg(i2s, HII2S_I2S_CFG);
	val &= ~HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
	val &= ~(HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_MASK <<
			HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_SHIFT);
	val &= ~(HII2S_I2S_CFG__S2_सूचीECT_LOOP_MASK <<
			HII2S_I2S_CFG__S2_सूचीECT_LOOP_SHIFT);
	val |= चिन्हित_data;
	val |= (bits << HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_SHIFT);
	hi6210_ग_लिखो_reg(i2s, HII2S_I2S_CFG, val);


	अगर (!i2s->master)
		वापस 0;

	/* set DAC and related units to correct rate */
	val = hi6210_पढ़ो_reg(i2s, HII2S_FS_CFG);
	val &= ~(HII2S_FS_CFG__FS_S2_MASK << HII2S_FS_CFG__FS_S2_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_DACLR_MASK << HII2S_FS_CFG__FS_DACLR_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_ST_DL_R_MASK <<
					HII2S_FS_CFG__FS_ST_DL_R_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_ST_DL_L_MASK <<
					HII2S_FS_CFG__FS_ST_DL_L_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_S2_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_DACLR_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_ST_DL_R_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_ST_DL_L_SHIFT);
	hi6210_ग_लिखो_reg(i2s, HII2S_FS_CFG, val);

	वापस 0;
पूर्ण

अटल पूर्णांक hi6210_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			  काष्ठा snd_soc_dai *cpu_dai)
अणु
	pr_debug("%s\n", __func__);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			hi6210_i2s_rxctrl(cpu_dai, 1);
		अन्यथा
			hi6210_i2s_txctrl(cpu_dai, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			hi6210_i2s_rxctrl(cpu_dai, 0);
		अन्यथा
			hi6210_i2s_txctrl(cpu_dai, 0);
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "unknown cmd\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hi6210_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hi6210_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai,
				  &i2s->dma_data[SNDRV_PCM_STREAM_PLAYBACK],
				  &i2s->dma_data[SNDRV_PCM_STREAM_CAPTURE]);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_soc_dai_ops hi6210_i2s_dai_ops = अणु
	.trigger	= hi6210_i2s_trigger,
	.hw_params	= hi6210_i2s_hw_params,
	.set_fmt	= hi6210_i2s_set_fmt,
	.startup	= hi6210_i2s_startup,
	.shutकरोwn	= hi6210_i2s_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver hi6210_i2s_dai_init = अणु
	.probe		= hi6210_i2s_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_U16_LE,
		.rates = SNDRV_PCM_RATE_48000,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_U16_LE,
		.rates = SNDRV_PCM_RATE_48000,
	पूर्ण,
	.ops = &hi6210_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver hi6210_i2s_i2s_comp = अणु
	.name = "hi6210_i2s-i2s",
पूर्ण;

अटल पूर्णांक hi6210_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hi6210_i2s *i2s;
	काष्ठा resource *res;
	पूर्णांक ret;

	i2s = devm_kzalloc(dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	i2s->dev = dev;
	spin_lock_init(&i2s->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2s->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(i2s->base))
		वापस PTR_ERR(i2s->base);

	i2s->base_phys = (phys_addr_t)res->start;
	i2s->dai = hi6210_i2s_dai_init;

	dev_set_drvdata(dev, i2s);

	i2s->sysctrl = syscon_regmap_lookup_by_phandle(node,
						"hisilicon,sysctrl-syscon");
	अगर (IS_ERR(i2s->sysctrl))
		वापस PTR_ERR(i2s->sysctrl);

	i2s->clk[CLK_DACODEC] = devm_clk_get(dev, "dacodec");
	अगर (IS_ERR(i2s->clk[CLK_DACODEC]))
		वापस PTR_ERR(i2s->clk[CLK_DACODEC]);
	i2s->घड़ीs++;

	i2s->clk[CLK_I2S_BASE] = devm_clk_get(dev, "i2s-base");
	अगर (IS_ERR(i2s->clk[CLK_I2S_BASE]))
		वापस PTR_ERR(i2s->clk[CLK_I2S_BASE]);
	i2s->घड़ीs++;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev, शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &hi6210_i2s_i2s_comp,
					 &i2s->dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id hi6210_i2s_dt_ids[] = अणु
	अणु .compatible = "hisilicon,hi6210-i2s" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, hi6210_i2s_dt_ids);

अटल काष्ठा platक्रमm_driver hi6210_i2s_driver = अणु
	.probe = hi6210_i2s_probe,
	.driver = अणु
		.name = "hi6210_i2s",
		.of_match_table = hi6210_i2s_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hi6210_i2s_driver);

MODULE_DESCRIPTION("Hisilicon HI6210 I2S driver");
MODULE_AUTHOR("Andy Green <andy.green@linaro.org>");
MODULE_LICENSE("GPL");
