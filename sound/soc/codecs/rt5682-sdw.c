<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt5682-sdw.c  --  RT5682 ALSA SoC audio component driver
//
// Copyright 2019 Realtek Semiconductor Corp.
// Author: Oder Chiou <oder_chiou@realtek.com>
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rt5682.h"

#घोषणा RT5682_SDW_ADDR_L			0x3000
#घोषणा RT5682_SDW_ADDR_H			0x3001
#घोषणा RT5682_SDW_DATA_L			0x3004
#घोषणा RT5682_SDW_DATA_H			0x3005
#घोषणा RT5682_SDW_CMD				0x3008

अटल पूर्णांक rt5682_sdw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक data_l, data_h;

	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_CMD, 0);
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_ADDR_H, (reg >> 8) & 0xff);
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_ADDR_L, (reg & 0xff));
	regmap_पढ़ो(rt5682->sdw_regmap, RT5682_SDW_DATA_H, &data_h);
	regmap_पढ़ो(rt5682->sdw_regmap, RT5682_SDW_DATA_L, &data_l);

	*val = (data_h << 8) | data_l;

	dev_vdbg(dev, "[%s] %04x => %04x\n", __func__, reg, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_sdw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);

	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_CMD, 1);
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_ADDR_H, (reg >> 8) & 0xff);
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_ADDR_L, (reg & 0xff));
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_DATA_H, (val >> 8) & 0xff);
	regmap_ग_लिखो(rt5682->sdw_regmap, RT5682_SDW_DATA_L, (val & 0xff));

	dev_vdbg(dev, "[%s] %04x <= %04x\n", __func__, reg, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config rt5682_sdw_indirect_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = RT5682_I2C_MODE,
	.अस्थिर_reg = rt5682_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5682_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5682_reg,
	.num_reg_शेषs = RT5682_REG_NUM,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.reg_पढ़ो = rt5682_sdw_पढ़ो,
	.reg_ग_लिखो = rt5682_sdw_ग_लिखो,
पूर्ण;

काष्ठा sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

अटल पूर्णांक rt5682_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
				 पूर्णांक direction)
अणु
	काष्ठा sdw_stream_data *stream;

	अगर (!sdw_stream)
		वापस 0;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	stream->sdw_stream = sdw_stream;

	/* Use tx_mask or rx_mask to configure stream tag and set dma_data */
	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		dai->playback_dma_data = stream;
	अन्यथा
		dai->capture_dma_data = stream;

	वापस 0;
पूर्ण

अटल व्योम rt5682_sdw_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt5682_sdw_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels;
	अचिन्हित पूर्णांक val_p = 0, val_c = 0, osr_p = 0, osr_c = 0;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);

	stream = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!stream)
		वापस -ENOMEM;

	अगर (!rt5682->slave)
		वापस -EINVAL;

	/* SoundWire specअगरic configuration */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port = 1;
	पूर्ण अन्यथा अणु
		direction = SDW_DATA_सूची_TX;
		port = 2;
	पूर्ण

	stream_config.frame_rate = params_rate(params);
	stream_config.ch_count = params_channels(params);
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	num_channels = params_channels(params);
	port_config.ch_mask = (1 << (num_channels)) - 1;
	port_config.num = port;

	retval = sdw_stream_add_slave(rt5682->slave, &stream_config,
				      &port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 48000:
		val_p = RT5682_SDW_REF_1_48K;
		val_c = RT5682_SDW_REF_2_48K;
		अवरोध;
	हाल 96000:
		val_p = RT5682_SDW_REF_1_96K;
		val_c = RT5682_SDW_REF_2_96K;
		अवरोध;
	हाल 192000:
		val_p = RT5682_SDW_REF_1_192K;
		val_c = RT5682_SDW_REF_2_192K;
		अवरोध;
	हाल 32000:
		val_p = RT5682_SDW_REF_1_32K;
		val_c = RT5682_SDW_REF_2_32K;
		अवरोध;
	हाल 24000:
		val_p = RT5682_SDW_REF_1_24K;
		val_c = RT5682_SDW_REF_2_24K;
		अवरोध;
	हाल 16000:
		val_p = RT5682_SDW_REF_1_16K;
		val_c = RT5682_SDW_REF_2_16K;
		अवरोध;
	हाल 12000:
		val_p = RT5682_SDW_REF_1_12K;
		val_c = RT5682_SDW_REF_2_12K;
		अवरोध;
	हाल 8000:
		val_p = RT5682_SDW_REF_1_8K;
		val_c = RT5682_SDW_REF_2_8K;
		अवरोध;
	हाल 44100:
		val_p = RT5682_SDW_REF_1_44K;
		val_c = RT5682_SDW_REF_2_44K;
		अवरोध;
	हाल 88200:
		val_p = RT5682_SDW_REF_1_88K;
		val_c = RT5682_SDW_REF_2_88K;
		अवरोध;
	हाल 176400:
		val_p = RT5682_SDW_REF_1_176K;
		val_c = RT5682_SDW_REF_2_176K;
		अवरोध;
	हाल 22050:
		val_p = RT5682_SDW_REF_1_22K;
		val_c = RT5682_SDW_REF_2_22K;
		अवरोध;
	हाल 11025:
		val_p = RT5682_SDW_REF_1_11K;
		val_c = RT5682_SDW_REF_2_11K;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (params_rate(params) <= 48000) अणु
		osr_p = RT5682_DAC_OSR_D_8;
		osr_c = RT5682_ADC_OSR_D_8;
	पूर्ण अन्यथा अगर (params_rate(params) <= 96000) अणु
		osr_p = RT5682_DAC_OSR_D_4;
		osr_c = RT5682_ADC_OSR_D_4;
	पूर्ण अन्यथा अणु
		osr_p = RT5682_DAC_OSR_D_2;
		osr_c = RT5682_ADC_OSR_D_2;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(rt5682->regmap, RT5682_SDW_REF_CLK,
			RT5682_SDW_REF_1_MASK, val_p);
		regmap_update_bits(rt5682->regmap, RT5682_ADDA_CLK_1,
			RT5682_DAC_OSR_MASK, osr_p);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5682->regmap, RT5682_SDW_REF_CLK,
			RT5682_SDW_REF_2_MASK, val_c);
		regmap_update_bits(rt5682->regmap, RT5682_ADDA_CLK_1,
			RT5682_ADC_OSR_MASK, osr_c);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक rt5682_sdw_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt5682->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt5682->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rt5682_sdw_ops = अणु
	.hw_params	= rt5682_sdw_hw_params,
	.hw_मुक्त	= rt5682_sdw_hw_मुक्त,
	.set_sdw_stream	= rt5682_set_sdw_stream,
	.shutकरोwn	= rt5682_sdw_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5682_dai[] = अणु
	अणु
		.name = "rt5682-aif1",
		.id = RT5682_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.ops = &rt5682_aअगर1_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5682-aif2",
		.id = RT5682_AIF2,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.ops = &rt5682_aअगर2_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5682-sdw",
		.id = RT5682_SDW,
		.playback = अणु
			.stream_name = "SDW Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "SDW Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.ops = &rt5682_sdw_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt5682_sdw_init(काष्ठा device *dev, काष्ठा regmap *regmap,
			   काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt5682_priv *rt5682;
	पूर्णांक ret;

	rt5682 = devm_kzalloc(dev, माप(*rt5682), GFP_KERNEL);
	अगर (!rt5682)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt5682);
	rt5682->slave = slave;
	rt5682->sdw_regmap = regmap;
	rt5682->is_sdw = true;

	rt5682->regmap = devm_regmap_init(dev, शून्य, dev,
					  &rt5682_sdw_indirect_regmap);
	अगर (IS_ERR(rt5682->regmap)) अणु
		ret = PTR_ERR(rt5682->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt5682->hw_init = false;
	rt5682->first_hw_init = false;

	mutex_init(&rt5682->calibrate_mutex);
	INIT_DELAYED_WORK(&rt5682->jack_detect_work,
		rt5682_jack_detect_handler);

	ret = devm_snd_soc_रेजिस्टर_component(dev,
					      &rt5682_soc_component_dev,
					      rt5682_dai, ARRAY_SIZE(rt5682_dai));
	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक rt5682_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);
	पूर्णांक ret = 0, loop = 10;
	अचिन्हित पूर्णांक val;

	अगर (rt5682->hw_init)
		वापस 0;

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!rt5682->first_hw_init) अणु
		/* set स्वतःsuspend parameters */
		pm_runसमय_set_स्वतःsuspend_delay(&slave->dev, 3000);
		pm_runसमय_use_स्वतःsuspend(&slave->dev);

		/* update count of parent 'active' children */
		pm_runसमय_set_active(&slave->dev);

		/* make sure the device करोes not suspend immediately */
		pm_runसमय_mark_last_busy(&slave->dev);

		pm_runसमय_enable(&slave->dev);
	पूर्ण

	pm_runसमय_get_noresume(&slave->dev);

	जबतक (loop > 0) अणु
		regmap_पढ़ो(rt5682->regmap, RT5682_DEVICE_ID, &val);
		अगर (val == DEVICE_ID)
			अवरोध;
		dev_warn(dev, "Device with ID register %x is not rt5682\n", val);
		usleep_range(30000, 30005);
		loop--;
	पूर्ण
	अगर (val != DEVICE_ID) अणु
		dev_err(dev, "Device with ID register %x is not rt5682\n", val);
		वापस -ENODEV;
	पूर्ण

	अगर (rt5682->first_hw_init) अणु
		regcache_cache_only(rt5682->regmap, false);
		regcache_cache_bypass(rt5682->regmap, true);
	पूर्ण

	rt5682_calibrate(rt5682);

	अगर (rt5682->first_hw_init) अणु
		regcache_cache_bypass(rt5682->regmap, false);
		regcache_mark_dirty(rt5682->regmap);
		regcache_sync(rt5682->regmap);

		/* अस्थिर रेजिस्टरs */
		regmap_update_bits(rt5682->regmap, RT5682_CBJ_CTRL_2,
			RT5682_EXT_JD_SRC, RT5682_EXT_JD_SRC_MANUAL);

		जाओ reinit;
	पूर्ण

	rt5682_apply_patch_list(rt5682, dev);

	regmap_ग_लिखो(rt5682->regmap, RT5682_DEPOP_1, 0x0000);

	regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
		RT5682_LDO1_DVO_MASK | RT5682_HP_DRIVER_MASK,
		RT5682_LDO1_DVO_12 | RT5682_HP_DRIVER_5X);
	regmap_ग_लिखो(rt5682->regmap, RT5682_MICBIAS_2, 0x0080);
	regmap_ग_लिखो(rt5682->regmap, RT5682_TEST_MODE_CTRL_1, 0x0000);
	regmap_update_bits(rt5682->regmap, RT5682_BIAS_CUR_CTRL_8,
		RT5682_HPA_CP_BIAS_CTRL_MASK, RT5682_HPA_CP_BIAS_3UA);
	regmap_update_bits(rt5682->regmap, RT5682_CHARGE_PUMP_1,
		RT5682_CP_CLK_HP_MASK, RT5682_CP_CLK_HP_300KHZ);
	regmap_update_bits(rt5682->regmap, RT5682_HP_CHARGE_PUMP_1,
		RT5682_PM_HP_MASK, RT5682_PM_HP_HV);

	/* Soundwire */
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL2_INTERNAL, 0xa266);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL2_CTRL_1, 0x1700);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL2_CTRL_2, 0x0006);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL2_CTRL_3, 0x2600);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL2_CTRL_4, 0x0c8f);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL_TRACK_2, 0x3000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PLL_TRACK_3, 0x4000);
	regmap_update_bits(rt5682->regmap, RT5682_GLB_CLK,
		RT5682_SCLK_SRC_MASK | RT5682_PLL2_SRC_MASK,
		RT5682_SCLK_SRC_PLL2 | RT5682_PLL2_SRC_SDW);

	regmap_update_bits(rt5682->regmap, RT5682_CBJ_CTRL_2,
		RT5682_EXT_JD_SRC, RT5682_EXT_JD_SRC_MANUAL);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CBJ_CTRL_1, 0xd142);
	regmap_update_bits(rt5682->regmap, RT5682_CBJ_CTRL_5, 0x0700, 0x0600);
	regmap_update_bits(rt5682->regmap, RT5682_CBJ_CTRL_3,
		RT5682_CBJ_IN_BUF_EN, RT5682_CBJ_IN_BUF_EN);
	regmap_update_bits(rt5682->regmap, RT5682_SAR_IL_CMD_1,
		RT5682_SAR_POW_MASK, RT5682_SAR_POW_EN);
	regmap_update_bits(rt5682->regmap, RT5682_RC_CLK_CTRL,
		RT5682_POW_IRQ | RT5682_POW_JDH |
		RT5682_POW_ANA, RT5682_POW_IRQ |
		RT5682_POW_JDH | RT5682_POW_ANA);
	regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_2,
		RT5682_PWR_JDH, RT5682_PWR_JDH);
	regmap_update_bits(rt5682->regmap, RT5682_IRQ_CTRL_2,
		RT5682_JD1_EN_MASK | RT5682_JD1_IRQ_MASK,
		RT5682_JD1_EN | RT5682_JD1_IRQ_PUL);

reinit:
	mod_delayed_work(प्रणाली_घातer_efficient_wq,
		&rt5682->jack_detect_work, msecs_to_jअगरfies(250));

	/* Mark Slave initialization complete */
	rt5682->hw_init = true;
	rt5682->first_hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	dev_dbg(&slave->dev, "%s hw_init complete\n", __func__);

	वापस ret;
पूर्ण

अटल bool rt5682_sdw_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00e0:
	हाल 0x00f0:
	हाल 0x3000:
	हाल 0x3001:
	हाल 0x3004:
	हाल 0x3005:
	हाल 0x3008:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt5682_sdw_regmap = अणु
	.name = "sdw",
	.reg_bits = 32,
	.val_bits = 8,
	.max_रेजिस्टर = RT5682_I2C_MODE,
	.पढ़ोable_reg = rt5682_sdw_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_NONE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक rt5682_update_status(काष्ठा sdw_slave *slave,
					क्रमागत sdw_slave_status status)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt5682->status = status;

	अगर (status == SDW_SLAVE_UNATTACHED)
		rt5682->hw_init = false;

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt5682->hw_init || rt5682->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt5682_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt5682_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval, i;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_IMPL_DEF | SDW_SCP_INT1_BUS_CLASH |
		SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;

	prop->paging_support = false;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x4;	/* BITMAP: 00000100 */
	prop->sink_ports = 0x2;		/* BITMAP: 00000010 */

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					  माप(*prop->src_dpn_prop),
					  GFP_KERNEL);
	अगर (!prop->src_dpn_prop)
		वापस -ENOMEM;

	i = 0;
	dpn = prop->src_dpn_prop;
	addr = prop->source_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FULL;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* करो this again क्रम sink now */
	nval = hweight32(prop->sink_ports);
	prop->sink_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					   माप(*prop->sink_dpn_prop),
					   GFP_KERNEL);
	अगर (!prop->sink_dpn_prop)
		वापस -ENOMEM;

	i = 0;
	dpn = prop->sink_dpn_prop;
	addr = prop->sink_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FULL;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* set the समयout values */
	prop->clk_stop_समयout = 20;

	/* wake-up event */
	prop->wake_capable = 1;

	वापस 0;
पूर्ण

/* Bus घड़ी frequency */
#घोषणा RT5682_CLK_FREQ_9600000HZ 9600000
#घोषणा RT5682_CLK_FREQ_12000000HZ 12000000
#घोषणा RT5682_CLK_FREQ_6000000HZ 6000000
#घोषणा RT5682_CLK_FREQ_4800000HZ 4800000
#घोषणा RT5682_CLK_FREQ_2400000HZ 2400000
#घोषणा RT5682_CLK_FREQ_12288000HZ 12288000

अटल पूर्णांक rt5682_घड़ी_config(काष्ठा device *dev)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक clk_freq, value;

	clk_freq = (rt5682->params.curr_dr_freq >> 1);

	चयन (clk_freq) अणु
	हाल RT5682_CLK_FREQ_12000000HZ:
		value = 0x0;
		अवरोध;
	हाल RT5682_CLK_FREQ_6000000HZ:
		value = 0x1;
		अवरोध;
	हाल RT5682_CLK_FREQ_9600000HZ:
		value = 0x2;
		अवरोध;
	हाल RT5682_CLK_FREQ_4800000HZ:
		value = 0x3;
		अवरोध;
	हाल RT5682_CLK_FREQ_2400000HZ:
		value = 0x4;
		अवरोध;
	हाल RT5682_CLK_FREQ_12288000HZ:
		value = 0x5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(rt5682->sdw_regmap, 0xe0, value);
	regmap_ग_लिखो(rt5682->sdw_regmap, 0xf0, value);

	dev_dbg(dev, "%s complete, clk_freq=%d\n", __func__, clk_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_bus_config(काष्ठा sdw_slave *slave,
					काष्ठा sdw_bus_params *params)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(&slave->dev);
	पूर्णांक ret;

	स_नकल(&rt5682->params, params, माप(*params));

	ret = rt5682_घड़ी_config(&slave->dev);
	अगर (ret < 0)
		dev_err(&slave->dev, "Invalid clk config");

	वापस ret;
पूर्ण

अटल पूर्णांक rt5682_पूर्णांकerrupt_callback(काष्ठा sdw_slave *slave,
					काष्ठा sdw_slave_पूर्णांकr_status *status)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(&slave->dev);

	dev_dbg(&slave->dev,
		"%s control_port_stat=%x", __func__, status->control_port);

	अगर (status->control_port & 0x4) अणु
		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt5682->jack_detect_work, msecs_to_jअगरfies(rt5682->irq_work_delay_समय));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_slave_ops rt5682_slave_ops = अणु
	.पढ़ो_prop = rt5682_पढ़ो_prop,
	.पूर्णांकerrupt_callback = rt5682_पूर्णांकerrupt_callback,
	.update_status = rt5682_update_status,
	.bus_config = rt5682_bus_config,
पूर्ण;

अटल पूर्णांक rt5682_sdw_probe(काष्ठा sdw_slave *slave,
			   स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *regmap;

	/* Regmap Initialization */
	regmap = devm_regmap_init_sdw(slave, &rt5682_sdw_regmap);
	अगर (IS_ERR(regmap))
		वापस -EINVAL;

	rt5682_sdw_init(&slave->dev, regmap, slave);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_sdw_हटाओ(काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(&slave->dev);

	अगर (rt5682 && rt5682->hw_init)
		cancel_delayed_work_sync(&rt5682->jack_detect_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt5682_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x5682, 0x2, 0, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt5682_id);

अटल पूर्णांक __maybe_unused rt5682_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);

	अगर (!rt5682->hw_init)
		वापस 0;

	cancel_delayed_work_sync(&rt5682->jack_detect_work);

	regcache_cache_only(rt5682->regmap, true);
	regcache_mark_dirty(rt5682->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rt5682_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt5682_priv *rt5682 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt5682->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
				msecs_to_jअगरfies(RT5682_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt5682->regmap, false);
	regcache_sync(rt5682->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt5682_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt5682_dev_suspend, rt5682_dev_resume)
	SET_RUNTIME_PM_OPS(rt5682_dev_suspend, rt5682_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt5682_sdw_driver = अणु
	.driver = अणु
		.name = "rt5682",
		.owner = THIS_MODULE,
		.pm = &rt5682_pm,
	पूर्ण,
	.probe = rt5682_sdw_probe,
	.हटाओ = rt5682_sdw_हटाओ,
	.ops = &rt5682_slave_ops,
	.id_table = rt5682_id,
पूर्ण;
module_sdw_driver(rt5682_sdw_driver);

MODULE_DESCRIPTION("ASoC RT5682 driver SDW");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
