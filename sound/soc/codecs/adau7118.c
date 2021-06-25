<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Analog Devices ADAU7118 8 channel PDM-to-I2S/TDM Converter driver
//
// Copyright 2019 Analog Devices Inc.

#समावेश <linux/bitfield.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "adau7118.h"

#घोषणा ADAU7118_DEC_RATIO_MASK		GENMASK(1, 0)
#घोषणा ADAU7118_DEC_RATIO(x)		FIELD_PREP(ADAU7118_DEC_RATIO_MASK, x)
#घोषणा ADAU7118_CLK_MAP_MASK		GENMASK(7, 4)
#घोषणा ADAU7118_SLOT_WIDTH_MASK	GENMASK(5, 4)
#घोषणा ADAU7118_SLOT_WIDTH(x)		FIELD_PREP(ADAU7118_SLOT_WIDTH_MASK, x)
#घोषणा ADAU7118_TRISTATE_MASK		BIT(6)
#घोषणा ADAU7118_TRISTATE(x)		FIELD_PREP(ADAU7118_TRISTATE_MASK, x)
#घोषणा ADAU7118_DATA_FMT_MASK		GENMASK(3, 1)
#घोषणा ADAU7118_DATA_FMT(x)		FIELD_PREP(ADAU7118_DATA_FMT_MASK, x)
#घोषणा ADAU7118_SAI_MODE_MASK		BIT(0)
#घोषणा ADAU7118_SAI_MODE(x)		FIELD_PREP(ADAU7118_SAI_MODE_MASK, x)
#घोषणा ADAU7118_LRCLK_BCLK_POL_MASK	GENMASK(1, 0)
#घोषणा ADAU7118_LRCLK_BCLK_POL(x) \
				FIELD_PREP(ADAU7118_LRCLK_BCLK_POL_MASK, x)
#घोषणा ADAU7118_SPT_SLOT_MASK		GENMASK(7, 4)
#घोषणा ADAU7118_SPT_SLOT(x)		FIELD_PREP(ADAU7118_SPT_SLOT_MASK, x)
#घोषणा ADAU7118_FULL_SOFT_R_MASK	BIT(1)
#घोषणा ADAU7118_FULL_SOFT_R(x)		FIELD_PREP(ADAU7118_FULL_SOFT_R_MASK, x)

काष्ठा adau7118_data अणु
	काष्ठा regmap *map;
	काष्ठा device *dev;
	काष्ठा regulator *iovdd;
	काष्ठा regulator *dvdd;
	u32 slot_width;
	u32 slots;
	bool hw_mode;
	bool right_j;
पूर्ण;

/* Input Enable */
अटल स्थिर काष्ठा snd_kcontrol_new adau7118_dapm_pdm_control[4] = अणु
	SOC_DAPM_SINGLE("Capture Switch", ADAU7118_REG_ENABLES, 0, 1, 0),
	SOC_DAPM_SINGLE("Capture Switch", ADAU7118_REG_ENABLES, 1, 1, 0),
	SOC_DAPM_SINGLE("Capture Switch", ADAU7118_REG_ENABLES, 2, 1, 0),
	SOC_DAPM_SINGLE("Capture Switch", ADAU7118_REG_ENABLES, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau7118_widमाला_लो_sw[] = अणु
	/* Input Enable Switches */
	SND_SOC_DAPM_SWITCH("PDM0", SND_SOC_NOPM, 0, 0,
			    &adau7118_dapm_pdm_control[0]),
	SND_SOC_DAPM_SWITCH("PDM1", SND_SOC_NOPM, 0, 0,
			    &adau7118_dapm_pdm_control[1]),
	SND_SOC_DAPM_SWITCH("PDM2", SND_SOC_NOPM, 0, 0,
			    &adau7118_dapm_pdm_control[2]),
	SND_SOC_DAPM_SWITCH("PDM3", SND_SOC_NOPM, 0, 0,
			    &adau7118_dapm_pdm_control[3]),

	/* PDM Clocks */
	SND_SOC_DAPM_SUPPLY("PDM_CLK0", ADAU7118_REG_ENABLES, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PDM_CLK1", ADAU7118_REG_ENABLES, 5, 0, शून्य, 0),

	/* Output channels */
	SND_SOC_DAPM_AIF_OUT("AIF1TX1", "Capture", 0, ADAU7118_REG_SPT_CX(0),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX2", "Capture", 0, ADAU7118_REG_SPT_CX(1),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX3", "Capture", 0, ADAU7118_REG_SPT_CX(2),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX4", "Capture", 0, ADAU7118_REG_SPT_CX(3),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX5", "Capture", 0, ADAU7118_REG_SPT_CX(4),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX6", "Capture", 0, ADAU7118_REG_SPT_CX(5),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX7", "Capture", 0, ADAU7118_REG_SPT_CX(6),
			     0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX8", "Capture", 0, ADAU7118_REG_SPT_CX(7),
			     0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau7118_routes_sw[] = अणु
	अणु "PDM0", "Capture Switch", "PDM_DAT0" पूर्ण,
	अणु "PDM1", "Capture Switch", "PDM_DAT1" पूर्ण,
	अणु "PDM2", "Capture Switch", "PDM_DAT2" पूर्ण,
	अणु "PDM3", "Capture Switch", "PDM_DAT3" पूर्ण,
	अणु "AIF1TX1", शून्य, "PDM0" पूर्ण,
	अणु "AIF1TX2", शून्य, "PDM0" पूर्ण,
	अणु "AIF1TX3", शून्य, "PDM1" पूर्ण,
	अणु "AIF1TX4", शून्य, "PDM1" पूर्ण,
	अणु "AIF1TX5", शून्य, "PDM2" पूर्ण,
	अणु "AIF1TX6", शून्य, "PDM2" पूर्ण,
	अणु "AIF1TX7", शून्य, "PDM3" पूर्ण,
	अणु "AIF1TX8", शून्य, "PDM3" पूर्ण,
	अणु "Capture", शून्य, "PDM_CLK0" पूर्ण,
	अणु "Capture", शून्य, "PDM_CLK1" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau7118_widमाला_लो_hw[] = अणु
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau7118_routes_hw[] = अणु
	अणु "AIF1TX", शून्य, "PDM_DAT0" पूर्ण,
	अणु "AIF1TX", शून्य, "PDM_DAT1" पूर्ण,
	अणु "AIF1TX", शून्य, "PDM_DAT2" पूर्ण,
	अणु "AIF1TX", शून्य, "PDM_DAT3" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau7118_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("PDM_DAT0"),
	SND_SOC_DAPM_INPUT("PDM_DAT1"),
	SND_SOC_DAPM_INPUT("PDM_DAT2"),
	SND_SOC_DAPM_INPUT("PDM_DAT3"),
पूर्ण;

अटल पूर्णांक adau7118_set_channel_map(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				    अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा adau7118_data *st =
		snd_soc_component_get_drvdata(dai->component);
	पूर्णांक chan, ret;

	dev_dbg(st->dev, "Set channel map, %d", tx_num);

	क्रम (chan = 0; chan < tx_num; chan++) अणु
		ret = snd_soc_component_update_bits(dai->component,
					ADAU7118_REG_SPT_CX(chan),
					ADAU7118_SPT_SLOT_MASK,
					ADAU7118_SPT_SLOT(tx_slot[chan]));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau7118_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा adau7118_data *st =
		snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret = 0;
	u32 regval;

	dev_dbg(st->dev, "Set format, fmt:%d\n", fmt);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ret = snd_soc_component_update_bits(dai->component,
						    ADAU7118_REG_SPT_CTRL1,
						    ADAU7118_DATA_FMT_MASK,
						    ADAU7118_DATA_FMT(0));
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ret = snd_soc_component_update_bits(dai->component,
						    ADAU7118_REG_SPT_CTRL1,
						    ADAU7118_DATA_FMT_MASK,
						    ADAU7118_DATA_FMT(1));
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		st->right_j = true;
		अवरोध;
	शेष:
		dev_err(st->dev, "Invalid format %d",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		regval = ADAU7118_LRCLK_BCLK_POL(0);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		regval = ADAU7118_LRCLK_BCLK_POL(2);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		regval = ADAU7118_LRCLK_BCLK_POL(1);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		regval = ADAU7118_LRCLK_BCLK_POL(3);
		अवरोध;
	शेष:
		dev_err(st->dev, "Invalid Inv mask %d",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(dai->component,
					    ADAU7118_REG_SPT_CTRL2,
					    ADAU7118_LRCLK_BCLK_POL_MASK,
					    regval);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक adau7118_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा adau7118_data *st =
		snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	dev_dbg(st->dev, "Set tristate, %d\n", tristate);

	ret = snd_soc_component_update_bits(dai->component,
					    ADAU7118_REG_SPT_CTRL1,
					    ADAU7118_TRISTATE_MASK,
					    ADAU7118_TRISTATE(tristate));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक adau7118_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				 अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
				 पूर्णांक slot_width)
अणु
	काष्ठा adau7118_data *st =
		snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret = 0;
	u32 regval;

	dev_dbg(st->dev, "Set tdm, slots:%d width:%d\n", slots, slot_width);

	चयन (slot_width) अणु
	हाल 32:
		regval = ADAU7118_SLOT_WIDTH(0);
		अवरोध;
	हाल 24:
		regval = ADAU7118_SLOT_WIDTH(2);
		अवरोध;
	हाल 16:
		regval = ADAU7118_SLOT_WIDTH(1);
		अवरोध;
	शेष:
		dev_err(st->dev, "Invalid slot width:%d\n", slot_width);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(dai->component,
					    ADAU7118_REG_SPT_CTRL1,
					    ADAU7118_SLOT_WIDTH_MASK, regval);
	अगर (ret < 0)
		वापस ret;

	st->slot_width = slot_width;
	st->slots = slots;

	वापस 0;
पूर्ण

अटल पूर्णांक adau7118_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau7118_data *st =
		snd_soc_component_get_drvdata(dai->component);
	u32 data_width = params_width(params), slots_width;
	पूर्णांक ret;
	u32 regval;

	अगर (!st->slots) अणु
		/* set stereo mode */
		ret = snd_soc_component_update_bits(dai->component,
						    ADAU7118_REG_SPT_CTRL1,
						    ADAU7118_SAI_MODE_MASK,
						    ADAU7118_SAI_MODE(0));
		अगर (ret < 0)
			वापस ret;

		slots_width = 32;
	पूर्ण अन्यथा अणु
		slots_width = st->slot_width;
	पूर्ण

	अगर (data_width > slots_width) अणु
		dev_err(st->dev, "Invalid data_width:%d, slots_width:%d",
			data_width, slots_width);
		वापस -EINVAL;
	पूर्ण

	अगर (st->right_j) अणु
		चयन (slots_width - data_width) अणु
		हाल 8:
			/* delay bclck by 8 */
			regval = ADAU7118_DATA_FMT(2);
			अवरोध;
		हाल 12:
			/* delay bclck by 12 */
			regval = ADAU7118_DATA_FMT(3);
			अवरोध;
		हाल 16:
			/* delay bclck by 16 */
			regval = ADAU7118_DATA_FMT(4);
			अवरोध;
		शेष:
			dev_err(st->dev,
				"Cannot set right_j setting, slot_w:%d, data_w:%d\n",
					slots_width, data_width);
			वापस -EINVAL;
		पूर्ण

		ret = snd_soc_component_update_bits(dai->component,
						    ADAU7118_REG_SPT_CTRL1,
						    ADAU7118_DATA_FMT_MASK,
						    regval);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau7118_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau7118_data *st = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	dev_dbg(st->dev, "Set bias level %d\n", level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) ==
							SND_SOC_BIAS_OFF) अणु
			/* घातer on */
			ret = regulator_enable(st->iovdd);
			अगर (ret)
				वापस ret;

			/* there's no timing स्थिरraपूर्णांकs beक्रमe enabling dvdd */
			ret = regulator_enable(st->dvdd);
			अगर (ret) अणु
				regulator_disable(st->iovdd);
				वापस ret;
			पूर्ण

			अगर (st->hw_mode)
				वापस 0;

			regcache_cache_only(st->map, false);
			/* sync cache */
			ret = snd_soc_component_cache_sync(component);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* घातer off */
		ret = regulator_disable(st->dvdd);
		अगर (ret)
			वापस ret;

		ret = regulator_disable(st->iovdd);
		अगर (ret)
			वापस ret;

		अगर (st->hw_mode)
			वापस 0;

		/* cache only */
		regcache_mark_dirty(st->map);
		regcache_cache_only(st->map, true);

		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adau7118_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau7118_data *st = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm =
					snd_soc_component_get_dapm(component);
	पूर्णांक ret = 0;

	अगर (st->hw_mode) अणु
		ret = snd_soc_dapm_new_controls(dapm, adau7118_widमाला_लो_hw,
					ARRAY_SIZE(adau7118_widमाला_लो_hw));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, adau7118_routes_hw,
					      ARRAY_SIZE(adau7118_routes_hw));
	पूर्ण अन्यथा अणु
		snd_soc_component_init_regmap(component, st->map);
		ret = snd_soc_dapm_new_controls(dapm, adau7118_widमाला_लो_sw,
					ARRAY_SIZE(adau7118_widमाला_लो_sw));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, adau7118_routes_sw,
					      ARRAY_SIZE(adau7118_routes_sw));
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops adau7118_ops = अणु
	.hw_params = adau7118_hw_params,
	.set_channel_map = adau7118_set_channel_map,
	.set_fmt = adau7118_set_fmt,
	.set_tdm_slot = adau7118_set_tdm_slot,
	.set_tristate = adau7118_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adau7118_dai = अणु
	.name = "adau7118-hifi-capture",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 8,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |
			SNDRV_PCM_FMTBIT_S20_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S24_3LE,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 4000,
		.rate_max = 192000,
		.sig_bits = 24,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver adau7118_component_driver = अणु
	.probe			= adau7118_component_probe,
	.set_bias_level		= adau7118_set_bias_level,
	.dapm_widमाला_लो		= adau7118_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau7118_widमाला_लो),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम adau7118_regulator_disable(व्योम *data)
अणु
	काष्ठा adau7118_data *st = data;
	पूर्णांक ret;
	/*
	 * If we fail to disable DVDD, करोn't bother in trying IOVDD. We
	 * actually करोn't want to be left in the situation where DVDD
	 * is enabled and IOVDD is disabled.
	 */
	ret = regulator_disable(st->dvdd);
	अगर (ret)
		वापस;

	regulator_disable(st->iovdd);
पूर्ण

अटल पूर्णांक adau7118_regulator_setup(काष्ठा adau7118_data *st)
अणु
	st->iovdd = devm_regulator_get(st->dev, "iovdd");
	अगर (IS_ERR(st->iovdd)) अणु
		dev_err(st->dev, "Could not get iovdd: %ld\n",
			PTR_ERR(st->iovdd));
		वापस PTR_ERR(st->iovdd);
	पूर्ण

	st->dvdd = devm_regulator_get(st->dev, "dvdd");
	अगर (IS_ERR(st->dvdd)) अणु
		dev_err(st->dev, "Could not get dvdd: %ld\n",
			PTR_ERR(st->dvdd));
		वापस PTR_ERR(st->dvdd);
	पूर्ण
	/* just assume the device is in reset */
	अगर (!st->hw_mode) अणु
		regcache_mark_dirty(st->map);
		regcache_cache_only(st->map, true);
	पूर्ण

	वापस devm_add_action_or_reset(st->dev, adau7118_regulator_disable,
					st);
पूर्ण

अटल पूर्णांक adau7118_parset_dt(स्थिर काष्ठा adau7118_data *st)
अणु
	पूर्णांक ret;
	u32 dec_ratio = 0;
	/* 4 inमाला_दो */
	u32 clk_map[4], regval;

	अगर (st->hw_mode)
		वापस 0;

	ret = device_property_पढ़ो_u32(st->dev, "adi,decimation-ratio",
				       &dec_ratio);
	अगर (!ret) अणु
		चयन (dec_ratio) अणु
		हाल 64:
			regval = ADAU7118_DEC_RATIO(0);
			अवरोध;
		हाल 32:
			regval = ADAU7118_DEC_RATIO(1);
			अवरोध;
		हाल 16:
			regval = ADAU7118_DEC_RATIO(2);
			अवरोध;
		शेष:
			dev_err(st->dev, "Invalid dec ratio: %u", dec_ratio);
			वापस -EINVAL;
		पूर्ण

		ret = regmap_update_bits(st->map,
					 ADAU7118_REG_DEC_RATIO_CLK_MAP,
					 ADAU7118_DEC_RATIO_MASK, regval);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32_array(st->dev, "adi,pdm-clk-map",
					     clk_map, ARRAY_SIZE(clk_map));
	अगर (!ret) अणु
		पूर्णांक pdm;
		u32 _clk_map = 0;

		क्रम (pdm = 0; pdm < ARRAY_SIZE(clk_map); pdm++)
			_clk_map |= (clk_map[pdm] << (pdm + 4));

		ret = regmap_update_bits(st->map,
					 ADAU7118_REG_DEC_RATIO_CLK_MAP,
					 ADAU7118_CLK_MAP_MASK, _clk_map);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक adau7118_probe(काष्ठा device *dev, काष्ठा regmap *map, bool hw_mode)
अणु
	काष्ठा adau7118_data *st;
	पूर्णांक ret;

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->dev = dev;
	st->hw_mode = hw_mode;
	dev_set_drvdata(dev, st);

	अगर (!hw_mode) अणु
		st->map = map;
		adau7118_dai.ops = &adau7118_ops;
		/*
		 * Perक्रमm a full soft reset. This will set all रेजिस्टर's
		 * with their reset values.
		 */
		ret = regmap_update_bits(map, ADAU7118_REG_RESET,
					 ADAU7118_FULL_SOFT_R_MASK,
					 ADAU7118_FULL_SOFT_R(1));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adau7118_parset_dt(st);
	अगर (ret)
		वापस ret;

	ret = adau7118_regulator_setup(st);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(dev,
					       &adau7118_component_driver,
					       &adau7118_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(adau7118_probe);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("ADAU7118 8 channel PDM-to-I2S/TDM Converter driver");
MODULE_LICENSE("GPL");
