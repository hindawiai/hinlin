<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rk3328 ALSA SoC Audio driver
//
// Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "rk3328_codec.h"

/*
 * volume setting
 * 0: -39dB
 * 26: 0dB
 * 31: 6dB
 * Step: 1.5dB
 */
#घोषणा OUT_VOLUME	(0x18)
#घोषणा RK3328_GRF_SOC_CON2	(0x0408)
#घोषणा RK3328_GRF_SOC_CON10	(0x0428)
#घोषणा INITIAL_FREQ	(11289600)

काष्ठा rk3328_codec_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *mute;
	काष्ठा clk *mclk;
	काष्ठा clk *pclk;
	अचिन्हित पूर्णांक sclk;
	पूर्णांक spk_depop_समय; /* msec */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rk3328_codec_reg_शेषs[] = अणु
	अणु CODEC_RESET, 0x03 पूर्ण,
	अणु DAC_INIT_CTRL1, 0x00 पूर्ण,
	अणु DAC_INIT_CTRL2, 0x50 पूर्ण,
	अणु DAC_INIT_CTRL3, 0x0e पूर्ण,
	अणु DAC_PRECHARGE_CTRL, 0x01 पूर्ण,
	अणु DAC_PWR_CTRL, 0x00 पूर्ण,
	अणु DAC_CLK_CTRL, 0x00 पूर्ण,
	अणु HPMIX_CTRL, 0x00 पूर्ण,
	अणु HPOUT_CTRL, 0x00 पूर्ण,
	अणु HPOUTL_GAIN_CTRL, 0x00 पूर्ण,
	अणु HPOUTR_GAIN_CTRL, 0x00 पूर्ण,
	अणु HPOUT_POP_CTRL, 0x11 पूर्ण,
पूर्ण;

अटल पूर्णांक rk3328_codec_reset(काष्ठा rk3328_codec_priv *rk3328)
अणु
	regmap_ग_लिखो(rk3328->regmap, CODEC_RESET, 0x00);
	mdelay(10);
	regmap_ग_लिखो(rk3328->regmap, CODEC_RESET, 0x03);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val = PIN_सूचीECTION_IN | DAC_I2S_MODE_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val = PIN_सूचीECTION_OUT | DAC_I2S_MODE_MASTER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL1,
			   PIN_सूचीECTION_MASK | DAC_I2S_MODE_MASK, val);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		val = DAC_MODE_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = DAC_MODE_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = DAC_MODE_RJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = DAC_MODE_LJM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL2,
			   DAC_MODE_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	अगर (mute)
		val = HPOUTL_MUTE | HPOUTR_MUTE;
	अन्यथा
		val = HPOUTL_UNMUTE | HPOUTR_UNMUTE;

	regmap_update_bits(rk3328->regmap, HPOUT_CTRL,
			   HPOUTL_MUTE_MASK | HPOUTR_MUTE_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_codec_घातer_on(काष्ठा rk3328_codec_priv *rk3328, पूर्णांक रुको_ms)
अणु
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_XCHARGE_MASK, DAC_CHARGE_PRECHARGE);
	mdelay(10);
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_ALL_ON);
	mdelay(रुको_ms);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_codec_घातer_off(काष्ठा rk3328_codec_priv *rk3328, पूर्णांक रुको_ms)
अणु
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_XCHARGE_MASK, DAC_CHARGE_DISCHARGE);
	mdelay(10);
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_ALL_ON);
	mdelay(रुको_ms);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rk3328_reg_msk_val playback_खोलो_list[] = अणु
	अणु DAC_PWR_CTRL, DAC_PWR_MASK, DAC_PWR_ON पूर्ण,
	अणु DAC_PWR_CTRL, DACL_PATH_REFV_MASK | DACR_PATH_REFV_MASK,
	  DACL_PATH_REFV_ON | DACR_PATH_REFV_ON पूर्ण,
	अणु DAC_PWR_CTRL, HPOUTL_ZERO_CROSSING_MASK | HPOUTR_ZERO_CROSSING_MASK,
	  HPOUTL_ZERO_CROSSING_ON | HPOUTR_ZERO_CROSSING_ON पूर्ण,
	अणु HPOUT_POP_CTRL, HPOUTR_POP_MASK | HPOUTL_POP_MASK,
	  HPOUTR_POP_WORK | HPOUTL_POP_WORK पूर्ण,
	अणु HPMIX_CTRL, HPMIXL_MASK | HPMIXR_MASK, HPMIXL_EN | HPMIXR_EN पूर्ण,
	अणु HPMIX_CTRL, HPMIXL_INIT_MASK | HPMIXR_INIT_MASK,
	  HPMIXL_INIT_EN | HPMIXR_INIT_EN पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_MASK | HPOUTR_MASK, HPOUTL_EN | HPOUTR_EN पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_INIT_MASK | HPOUTR_INIT_MASK,
	  HPOUTL_INIT_EN | HPOUTR_INIT_EN पूर्ण,
	अणु DAC_CLK_CTRL, DACL_REFV_MASK | DACR_REFV_MASK,
	  DACL_REFV_ON | DACR_REFV_ON पूर्ण,
	अणु DAC_CLK_CTRL, DACL_CLK_MASK | DACR_CLK_MASK,
	  DACL_CLK_ON | DACR_CLK_ON पूर्ण,
	अणु DAC_CLK_CTRL, DACL_MASK | DACR_MASK, DACL_ON | DACR_ON पूर्ण,
	अणु DAC_CLK_CTRL, DACL_INIT_MASK | DACR_INIT_MASK,
	  DACL_INIT_ON | DACR_INIT_ON पूर्ण,
	अणु DAC_SELECT, DACL_SELECT_MASK | DACR_SELECT_MASK,
	  DACL_SELECT | DACR_SELECT पूर्ण,
	अणु HPMIX_CTRL, HPMIXL_INIT2_MASK | HPMIXR_INIT2_MASK,
	  HPMIXL_INIT2_EN | HPMIXR_INIT2_EN पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_MUTE_MASK | HPOUTR_MUTE_MASK,
	  HPOUTL_UNMUTE | HPOUTR_UNMUTE पूर्ण,
पूर्ण;

अटल पूर्णांक rk3328_codec_खोलो_playback(काष्ठा rk3328_codec_priv *rk3328)
अणु
	पूर्णांक i;

	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_I);

	क्रम (i = 0; i < ARRAY_SIZE(playback_खोलो_list); i++) अणु
		regmap_update_bits(rk3328->regmap,
				   playback_खोलो_list[i].reg,
				   playback_खोलो_list[i].msk,
				   playback_खोलो_list[i].val);
		mdelay(1);
	पूर्ण

	msleep(rk3328->spk_depop_समय);
	gpiod_set_value(rk3328->mute, 0);

	regmap_update_bits(rk3328->regmap, HPOUTL_GAIN_CTRL,
			   HPOUTL_GAIN_MASK, OUT_VOLUME);
	regmap_update_bits(rk3328->regmap, HPOUTR_GAIN_CTRL,
			   HPOUTR_GAIN_MASK, OUT_VOLUME);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rk3328_reg_msk_val playback_बंद_list[] = अणु
	अणु HPMIX_CTRL, HPMIXL_INIT2_MASK | HPMIXR_INIT2_MASK,
	  HPMIXL_INIT2_DIS | HPMIXR_INIT2_DIS पूर्ण,
	अणु DAC_SELECT, DACL_SELECT_MASK | DACR_SELECT_MASK,
	  DACL_UNSELECT | DACR_UNSELECT पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_MUTE_MASK | HPOUTR_MUTE_MASK,
	  HPOUTL_MUTE | HPOUTR_MUTE पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_INIT_MASK | HPOUTR_INIT_MASK,
	  HPOUTL_INIT_DIS | HPOUTR_INIT_DIS पूर्ण,
	अणु HPOUT_CTRL, HPOUTL_MASK | HPOUTR_MASK, HPOUTL_DIS | HPOUTR_DIS पूर्ण,
	अणु HPMIX_CTRL, HPMIXL_MASK | HPMIXR_MASK, HPMIXL_DIS | HPMIXR_DIS पूर्ण,
	अणु DAC_CLK_CTRL, DACL_MASK | DACR_MASK, DACL_OFF | DACR_OFF पूर्ण,
	अणु DAC_CLK_CTRL, DACL_CLK_MASK | DACR_CLK_MASK,
	  DACL_CLK_OFF | DACR_CLK_OFF पूर्ण,
	अणु DAC_CLK_CTRL, DACL_REFV_MASK | DACR_REFV_MASK,
	  DACL_REFV_OFF | DACR_REFV_OFF पूर्ण,
	अणु HPOUT_POP_CTRL, HPOUTR_POP_MASK | HPOUTL_POP_MASK,
	  HPOUTR_POP_XCHARGE | HPOUTL_POP_XCHARGE पूर्ण,
	अणु DAC_PWR_CTRL, DACL_PATH_REFV_MASK | DACR_PATH_REFV_MASK,
	  DACL_PATH_REFV_OFF | DACR_PATH_REFV_OFF पूर्ण,
	अणु DAC_PWR_CTRL, DAC_PWR_MASK, DAC_PWR_OFF पूर्ण,
	अणु HPMIX_CTRL, HPMIXL_INIT_MASK | HPMIXR_INIT_MASK,
	  HPMIXL_INIT_DIS | HPMIXR_INIT_DIS पूर्ण,
	अणु DAC_CLK_CTRL, DACL_INIT_MASK | DACR_INIT_MASK,
	  DACL_INIT_OFF | DACR_INIT_OFF पूर्ण,
पूर्ण;

अटल पूर्णांक rk3328_codec_बंद_playback(काष्ठा rk3328_codec_priv *rk3328)
अणु
	माप_प्रकार i;

	gpiod_set_value(rk3328->mute, 1);

	regmap_update_bits(rk3328->regmap, HPOUTL_GAIN_CTRL,
			   HPOUTL_GAIN_MASK, 0);
	regmap_update_bits(rk3328->regmap, HPOUTR_GAIN_CTRL,
			   HPOUTR_GAIN_MASK, 0);

	क्रम (i = 0; i < ARRAY_SIZE(playback_बंद_list); i++) अणु
		regmap_update_bits(rk3328->regmap,
				   playback_बंद_list[i].reg,
				   playback_बंद_list[i].msk,
				   playback_बंद_list[i].val);
		mdelay(1);
	पूर्ण

	/* Workaround क्रम silence when changed Fs 48 -> 44.1kHz */
	rk3328_codec_reset(rk3328);

	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_ALL_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val = 0;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val = DAC_VDL_16BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val = DAC_VDL_20BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val = DAC_VDL_24BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val = DAC_VDL_32BITS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL2, DAC_VDL_MASK, val);

	val = DAC_WL_32BITS | DAC_RST_DIS;
	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL3,
			   DAC_WL_MASK | DAC_RST_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3328_pcm_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);

	वापस rk3328_codec_खोलो_playback(rk3328);
पूर्ण

अटल व्योम rk3328_pcm_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);

	rk3328_codec_बंद_playback(rk3328);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rk3328_dai_ops = अणु
	.hw_params = rk3328_hw_params,
	.set_fmt = rk3328_set_dai_fmt,
	.mute_stream = rk3328_mute_stream,
	.startup = rk3328_pcm_startup,
	.shutकरोwn = rk3328_pcm_shutकरोwn,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rk3328_dai[] = अणु
	अणु
		.name = "rk3328-hifi",
		.id = RK3328_HIFI,
		.playback = अणु
			.stream_name = "HIFI Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
				    SNDRV_PCM_FMTBIT_S20_3LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_S32_LE),
		पूर्ण,
		.capture = अणु
			.stream_name = "HIFI Capture",
			.channels_min = 2,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
				    SNDRV_PCM_FMTBIT_S20_3LE |
				    SNDRV_PCM_FMTBIT_S24_LE |
				    SNDRV_PCM_FMTBIT_S32_LE),
		पूर्ण,
		.ops = &rk3328_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rk3328_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(component);

	rk3328_codec_reset(rk3328);
	rk3328_codec_घातer_on(rk3328, 0);

	वापस 0;
पूर्ण

अटल व्योम rk3328_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(component);

	rk3328_codec_बंद_playback(rk3328);
	rk3328_codec_घातer_off(rk3328, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_rk3328 = अणु
	.probe = rk3328_codec_probe,
	.हटाओ = rk3328_codec_हटाओ,
पूर्ण;

अटल bool rk3328_codec_ग_लिखो_पढ़ो_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CODEC_RESET:
	हाल DAC_INIT_CTRL1:
	हाल DAC_INIT_CTRL2:
	हाल DAC_INIT_CTRL3:
	हाल DAC_PRECHARGE_CTRL:
	हाल DAC_PWR_CTRL:
	हाल DAC_CLK_CTRL:
	हाल HPMIX_CTRL:
	हाल DAC_SELECT:
	हाल HPOUT_CTRL:
	हाल HPOUTL_GAIN_CTRL:
	हाल HPOUTR_GAIN_CTRL:
	हाल HPOUT_POP_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rk3328_codec_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CODEC_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rk3328_codec_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = HPOUT_POP_CTRL,
	.ग_लिखोable_reg = rk3328_codec_ग_लिखो_पढ़ो_reg,
	.पढ़ोable_reg = rk3328_codec_ग_लिखो_पढ़ो_reg,
	.अस्थिर_reg = rk3328_codec_अस्थिर_reg,
	.reg_शेषs = rk3328_codec_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rk3328_codec_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक rk3328_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *rk3328_np = pdev->dev.of_node;
	काष्ठा rk3328_codec_priv *rk3328;
	काष्ठा regmap *grf;
	व्योम __iomem *base;
	पूर्णांक ret = 0;

	rk3328 = devm_kzalloc(&pdev->dev, माप(*rk3328), GFP_KERNEL);
	अगर (!rk3328)
		वापस -ENOMEM;

	grf = syscon_regmap_lookup_by_phandle(rk3328_np,
					      "rockchip,grf");
	अगर (IS_ERR(grf)) अणु
		dev_err(&pdev->dev, "missing 'rockchip,grf'\n");
		वापस PTR_ERR(grf);
	पूर्ण
	/* enable i2s_acodec_en */
	regmap_ग_लिखो(grf, RK3328_GRF_SOC_CON2,
		     (BIT(14) << 16 | BIT(14)));

	ret = of_property_पढ़ो_u32(rk3328_np, "spk-depop-time-ms",
				   &rk3328->spk_depop_समय);
	अगर (ret < 0) अणु
		dev_info(&pdev->dev, "spk_depop_time use default value.\n");
		rk3328->spk_depop_समय = 200;
	पूर्ण

	rk3328->mute = gpiod_get_optional(&pdev->dev, "mute", GPIOD_OUT_HIGH);
	अगर (IS_ERR(rk3328->mute))
		वापस PTR_ERR(rk3328->mute);
	/*
	 * Rock64 is the only supported platक्रमm to have widely relied on
	 * this; अगर we करो happen to come across an old DTB, just leave the
	 * बाह्यal mute क्रमced off.
	 */
	अगर (!rk3328->mute && of_machine_is_compatible("pine64,rock64")) अणु
		dev_warn(&pdev->dev, "assuming implicit control of GPIO_MUTE; update devicetree if possible\n");
		regmap_ग_लिखो(grf, RK3328_GRF_SOC_CON10, BIT(17) | BIT(1));
	पूर्ण

	rk3328->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(rk3328->mclk))
		वापस PTR_ERR(rk3328->mclk);

	ret = clk_prepare_enable(rk3328->mclk);
	अगर (ret)
		वापस ret;
	clk_set_rate(rk3328->mclk, INITIAL_FREQ);

	rk3328->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(rk3328->pclk)) अणु
		dev_err(&pdev->dev, "can't get acodec pclk\n");
		वापस PTR_ERR(rk3328->pclk);
	पूर्ण

	ret = clk_prepare_enable(rk3328->pclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable acodec pclk\n");
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	rk3328->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					       &rk3328_codec_regmap_config);
	अगर (IS_ERR(rk3328->regmap))
		वापस PTR_ERR(rk3328->regmap);

	platक्रमm_set_drvdata(pdev, rk3328);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_codec_rk3328,
					       rk3328_dai,
					       ARRAY_SIZE(rk3328_dai));
पूर्ण

अटल स्थिर काष्ठा of_device_id rk3328_codec_of_match[] __maybe_unused = अणु
		अणु .compatible = "rockchip,rk3328-codec", पूर्ण,
		अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk3328_codec_of_match);

अटल काष्ठा platक्रमm_driver rk3328_codec_driver = अणु
	.driver = अणु
		   .name = "rk3328-codec",
		   .of_match_table = of_match_ptr(rk3328_codec_of_match),
	पूर्ण,
	.probe = rk3328_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(rk3328_codec_driver);

MODULE_AUTHOR("Sugar Zhang <sugar.zhang@rock-chips.com>");
MODULE_DESCRIPTION("ASoC rk3328 codec driver");
MODULE_LICENSE("GPL v2");
