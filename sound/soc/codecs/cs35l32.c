<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs35l32.c -- CS35L32 ALSA SoC audio driver
 *
 * Copyright 2014 CirrusLogic, Inc.
 *
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <dt-bindings/sound/cs35l32.h>

#समावेश "cs35l32.h"

#घोषणा CS35L32_NUM_SUPPLIES 2
अटल स्थिर अक्षर *स्थिर cs35l32_supply_names[CS35L32_NUM_SUPPLIES] = अणु
	"VA",
	"VP",
पूर्ण;

काष्ठा  cs35l32_निजी अणु
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा regulator_bulk_data supplies[CS35L32_NUM_SUPPLIES];
	काष्ठा cs35l32_platक्रमm_data pdata;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs35l32_reg_शेषs[] = अणु

	अणु 0x06, 0x04 पूर्ण, /* Power Ctl 1 */
	अणु 0x07, 0xE8 पूर्ण, /* Power Ctl 2 */
	अणु 0x08, 0x40 पूर्ण, /* Clock Ctl */
	अणु 0x09, 0x20 पूर्ण, /* Low Battery Threshold */
	अणु 0x0A, 0x00 पूर्ण, /* Voltage Monitor [RO] */
	अणु 0x0B, 0x40 पूर्ण, /* Conv Peak Curr Protection CTL */
	अणु 0x0C, 0x07 पूर्ण, /* IMON Scaling */
	अणु 0x0D, 0x03 पूर्ण, /* Audio/LED Pwr Manager */
	अणु 0x0F, 0x20 पूर्ण, /* Serial Port Control */
	अणु 0x10, 0x14 पूर्ण, /* Class D Amp CTL */
	अणु 0x11, 0x00 पूर्ण, /* Protection Release CTL */
	अणु 0x12, 0xFF पूर्ण, /* Interrupt Mask 1 */
	अणु 0x13, 0xFF पूर्ण, /* Interrupt Mask 2 */
	अणु 0x14, 0xFF पूर्ण, /* Interrupt Mask 3 */
	अणु 0x19, 0x00 पूर्ण, /* LED Flash Mode Current */
	अणु 0x1A, 0x00 पूर्ण, /* LED Movie Mode Current */
	अणु 0x1B, 0x20 पूर्ण, /* LED Flash Timer */
	अणु 0x1C, 0x00 पूर्ण, /* LED Flash Inhibit Current */
पूर्ण;

अटल bool cs35l32_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L32_DEVID_AB ... CS35L32_AUDIO_LED_MNGR:
	हाल CS35L32_ADSP_CTL ... CS35L32_FLASH_INHIBIT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l32_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L32_DEVID_AB ... CS35L32_REV_ID:
	हाल CS35L32_INT_STATUS_1 ... CS35L32_LED_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l32_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L32_INT_STATUS_1 ... CS35L32_LED_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(classd_ctl_tlv, 900, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new imon_ctl =
	SOC_DAPM_SINGLE("Switch", CS35L32_PWRCTL2, 6, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new vmon_ctl =
	SOC_DAPM_SINGLE("Switch", CS35L32_PWRCTL2, 7, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new vpmon_ctl =
	SOC_DAPM_SINGLE("Switch", CS35L32_PWRCTL2, 5, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new cs35l32_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Volume", CS35L32_CLASSD_CTL,
		       3, 0x04, 1, classd_ctl_tlv),
	SOC_SINGLE("Zero Cross Switch", CS35L32_CLASSD_CTL, 2, 1, 0),
	SOC_SINGLE("Gain Manager Switch", CS35L32_AUDIO_LED_MNGR, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs35l32_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_SUPPLY("BOOST", CS35L32_PWRCTL1, 2, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Speaker", CS35L32_PWRCTL1, 7, 1, शून्य, 0),

	SND_SOC_DAPM_AIF_OUT("SDOUT", शून्य, 0, CS35L32_PWRCTL2, 3, 1),

	SND_SOC_DAPM_INPUT("VP"),
	SND_SOC_DAPM_INPUT("ISENSE"),
	SND_SOC_DAPM_INPUT("VSENSE"),

	SND_SOC_DAPM_SWITCH("VMON ADC", CS35L32_PWRCTL2, 7, 1, &vmon_ctl),
	SND_SOC_DAPM_SWITCH("IMON ADC", CS35L32_PWRCTL2, 6, 1, &imon_ctl),
	SND_SOC_DAPM_SWITCH("VPMON ADC", CS35L32_PWRCTL2, 5, 1, &vpmon_ctl),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l32_audio_map[] = अणु

	अणु"Speaker", शून्य, "BOOST"पूर्ण,

	अणु"VMON ADC", शून्य, "VSENSE"पूर्ण,
	अणु"IMON ADC", शून्य, "ISENSE"पूर्ण,
	अणु"VPMON ADC", शून्य, "VP"पूर्ण,

	अणु"SDOUT", "Switch", "VMON ADC"पूर्ण,
	अणु"SDOUT",  "Switch", "IMON ADC"पूर्ण,
	अणु"SDOUT", "Switch", "VPMON ADC"पूर्ण,

	अणु"Capture", शून्य, "SDOUT"पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l32_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_MASTER_MASK,
				CS35L32_ADSP_MASTER_MASK);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_MASTER_MASK, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l32_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_update_bits(component, CS35L32_PWRCTL2,
					CS35L32_SDOUT_3ST, tristate << 3);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l32_ops = अणु
	.set_fmt = cs35l32_set_dai_fmt,
	.set_tristate = cs35l32_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs35l32_dai[] = अणु
	अणु
		.name = "cs35l32-monitor",
		.id = 0,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = CS35L32_RATES,
			.क्रमmats = CS35L32_FORMATS,
		पूर्ण,
		.ops = &cs35l32_ops,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

अटल पूर्णांक cs35l32_component_set_sysclk(काष्ठा snd_soc_component *component,
			      पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक val;

	चयन (freq) अणु
	हाल 6000000:
		val = CS35L32_MCLK_RATIO;
		अवरोध;
	हाल 12000000:
		val = CS35L32_MCLK_DIV2_MASK | CS35L32_MCLK_RATIO;
		अवरोध;
	हाल 6144000:
		val = 0;
		अवरोध;
	हाल 12288000:
		val = CS35L32_MCLK_DIV2_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_update_bits(component, CS35L32_CLK_CTL,
			CS35L32_MCLK_DIV2_MASK | CS35L32_MCLK_RATIO_MASK, val);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs35l32 = अणु
	.set_sysclk		= cs35l32_component_set_sysclk,
	.controls		= cs35l32_snd_controls,
	.num_controls		= ARRAY_SIZE(cs35l32_snd_controls),
	.dapm_widमाला_लो		= cs35l32_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs35l32_dapm_widमाला_लो),
	.dapm_routes		= cs35l32_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs35l32_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/* Current and threshold घातerup sequence Pg37 in datasheet */
अटल स्थिर काष्ठा reg_sequence cs35l32_monitor_patch[] = अणु

	अणु 0x00, 0x99 पूर्ण,
	अणु 0x48, 0x17 पूर्ण,
	अणु 0x49, 0x56 पूर्ण,
	अणु 0x43, 0x01 पूर्ण,
	अणु 0x3B, 0x62 पूर्ण,
	अणु 0x3C, 0x80 पूर्ण,
	अणु 0x00, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs35l32_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS35L32_MAX_REGISTER,
	.reg_शेषs = cs35l32_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs35l32_reg_शेषs),
	.अस्थिर_reg = cs35l32_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = cs35l32_पढ़ोable_रेजिस्टर,
	.precious_reg = cs35l32_precious_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक cs35l32_handle_of_data(काष्ठा i2c_client *i2c_client,
				    काष्ठा cs35l32_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	अचिन्हित पूर्णांक val;

	अगर (of_property_पढ़ो_u32(np, "cirrus,sdout-share", &val) >= 0)
		pdata->sकरोut_share = val;

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-manager", &val))
		val = -1u;

	चयन (val) अणु
	हाल CS35L32_BOOST_MGR_AUTO:
	हाल CS35L32_BOOST_MGR_AUTO_AUDIO:
	हाल CS35L32_BOOST_MGR_BYPASS:
	हाल CS35L32_BOOST_MGR_FIXED:
		pdata->boost_mng = val;
		अवरोध;
	हाल -1u:
	शेष:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,boost-manager DT value %d\n", val);
		pdata->boost_mng = CS35L32_BOOST_MGR_BYPASS;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,sdout-datacfg", &val))
		val = -1u;
	चयन (val) अणु
	हाल CS35L32_DATA_CFG_LR_VP:
	हाल CS35L32_DATA_CFG_LR_STAT:
	हाल CS35L32_DATA_CFG_LR:
	हाल CS35L32_DATA_CFG_LR_VPSTAT:
		pdata->sकरोut_datacfg = val;
		अवरोध;
	हाल -1u:
	शेष:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,sdout-datacfg DT value %d\n", val);
		pdata->sकरोut_datacfg = CS35L32_DATA_CFG_LR;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,battery-threshold", &val))
		val = -1u;
	चयन (val) अणु
	हाल CS35L32_BATT_THRESH_3_1V:
	हाल CS35L32_BATT_THRESH_3_2V:
	हाल CS35L32_BATT_THRESH_3_3V:
	हाल CS35L32_BATT_THRESH_3_4V:
		pdata->batt_thresh = val;
		अवरोध;
	हाल -1u:
	शेष:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,battery-threshold DT value %d\n", val);
		pdata->batt_thresh = CS35L32_BATT_THRESH_3_3V;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,battery-recovery", &val))
		val = -1u;
	चयन (val) अणु
	हाल CS35L32_BATT_RECOV_3_1V:
	हाल CS35L32_BATT_RECOV_3_2V:
	हाल CS35L32_BATT_RECOV_3_3V:
	हाल CS35L32_BATT_RECOV_3_4V:
	हाल CS35L32_BATT_RECOV_3_5V:
	हाल CS35L32_BATT_RECOV_3_6V:
		pdata->batt_recov = val;
		अवरोध;
	हाल -1u:
	शेष:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,battery-recovery DT value %d\n", val);
		pdata->batt_recov = CS35L32_BATT_RECOV_3_4V;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l32_i2c_probe(काष्ठा i2c_client *i2c_client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs35l32_निजी *cs35l32;
	काष्ठा cs35l32_platक्रमm_data *pdata =
		dev_get_platdata(&i2c_client->dev);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;

	cs35l32 = devm_kzalloc(&i2c_client->dev, माप(*cs35l32), GFP_KERNEL);
	अगर (!cs35l32)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_client, cs35l32);

	cs35l32->regmap = devm_regmap_init_i2c(i2c_client, &cs35l32_regmap);
	अगर (IS_ERR(cs35l32->regmap)) अणु
		ret = PTR_ERR(cs35l32->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs35l32->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(&i2c_client->dev, माप(*pdata),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (i2c_client->dev.of_node) अणु
			ret = cs35l32_handle_of_data(i2c_client,
						     &cs35l32->pdata);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cs35l32->supplies); i++)
		cs35l32->supplies[i].supply = cs35l32_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
				      ARRAY_SIZE(cs35l32->supplies),
				      cs35l32->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs35l32->supplies),
				    cs35l32->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the Device */
	cs35l32->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs35l32->reset_gpio))
		वापस PTR_ERR(cs35l32->reset_gpio);

	gpiod_set_value_cansleep(cs35l32->reset_gpio, 1);

	/* initialize codec */
	ret = regmap_पढ़ो(cs35l32->regmap, CS35L32_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;

	ret = regmap_पढ़ो(cs35l32->regmap, CS35L32_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;

	ret = regmap_पढ़ो(cs35l32->regmap, CS35L32_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS35L32_CHIP_ID) अणु
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS35L32 Device ID (%X). Expected %X\n",
			devid, CS35L32_CHIP_ID);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(cs35l32->regmap, CS35L32_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		वापस ret;
	पूर्ण

	ret = regmap_रेजिस्टर_patch(cs35l32->regmap, cs35l32_monitor_patch,
				    ARRAY_SIZE(cs35l32_monitor_patch));
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Failed to apply errata patch\n");
		वापस ret;
	पूर्ण

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS35L32, Revision: %02X\n", reg & 0xFF);

	/* Setup VBOOST Management */
	अगर (cs35l32->pdata.boost_mng)
		regmap_update_bits(cs35l32->regmap, CS35L32_AUDIO_LED_MNGR,
				   CS35L32_BOOST_MASK,
				cs35l32->pdata.boost_mng);

	/* Setup ADSP Format Config */
	अगर (cs35l32->pdata.sकरोut_share)
		regmap_update_bits(cs35l32->regmap, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_SHARE_MASK,
				cs35l32->pdata.sकरोut_share << 3);

	/* Setup ADSP Data Configuration */
	अगर (cs35l32->pdata.sकरोut_datacfg)
		regmap_update_bits(cs35l32->regmap, CS35L32_ADSP_CTL,
				   CS35L32_ADSP_DATACFG_MASK,
				cs35l32->pdata.sकरोut_datacfg << 4);

	/* Setup Low Battery Recovery  */
	अगर (cs35l32->pdata.batt_recov)
		regmap_update_bits(cs35l32->regmap, CS35L32_BATT_THRESHOLD,
				   CS35L32_BATT_REC_MASK,
				cs35l32->pdata.batt_recov << 1);

	/* Setup Low Battery Threshold */
	अगर (cs35l32->pdata.batt_thresh)
		regmap_update_bits(cs35l32->regmap, CS35L32_BATT_THRESHOLD,
				   CS35L32_BATT_THRESH_MASK,
				cs35l32->pdata.batt_thresh << 4);

	/* Power करोwn the AMP */
	regmap_update_bits(cs35l32->regmap, CS35L32_PWRCTL1, CS35L32_PDN_AMP,
			    CS35L32_PDN_AMP);

	/* Clear MCLK Error Bit since we करोn't have the घड़ी yet */
	ret = regmap_पढ़ो(cs35l32->regmap, CS35L32_INT_STATUS_1, &reg);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs35l32, cs35l32_dai,
			ARRAY_SIZE(cs35l32_dai));
	अगर (ret < 0)
		जाओ err_disable;

	वापस 0;

err_disable:
	regulator_bulk_disable(ARRAY_SIZE(cs35l32->supplies),
			       cs35l32->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक cs35l32_i2c_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा cs35l32_निजी *cs35l32 = i2c_get_clientdata(i2c_client);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs35l32->reset_gpio, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs35l32_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs35l32_निजी *cs35l32 = dev_get_drvdata(dev);

	regcache_cache_only(cs35l32->regmap, true);
	regcache_mark_dirty(cs35l32->regmap);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs35l32->reset_gpio, 0);

	/* हटाओ घातer */
	regulator_bulk_disable(ARRAY_SIZE(cs35l32->supplies),
			       cs35l32->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l32_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs35l32_निजी *cs35l32 = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Enable घातer */
	ret = regulator_bulk_enable(ARRAY_SIZE(cs35l32->supplies),
				    cs35l32->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(cs35l32->reset_gpio, 1);

	regcache_cache_only(cs35l32->regmap, false);
	regcache_sync(cs35l32->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cs35l32_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cs35l32_runसमय_suspend, cs35l32_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs35l32_of_match[] = अणु
	अणु .compatible = "cirrus,cs35l32", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs35l32_of_match);


अटल स्थिर काष्ठा i2c_device_id cs35l32_id[] = अणु
	अणु"cs35l32", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs35l32_id);

अटल काष्ठा i2c_driver cs35l32_i2c_driver = अणु
	.driver = अणु
		   .name = "cs35l32",
		   .pm = &cs35l32_runसमय_pm,
		   .of_match_table = cs35l32_of_match,
		   पूर्ण,
	.id_table = cs35l32_id,
	.probe = cs35l32_i2c_probe,
	.हटाओ = cs35l32_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs35l32_i2c_driver);

MODULE_DESCRIPTION("ASoC CS35L32 driver");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_LICENSE("GPL");
