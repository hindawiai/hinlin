<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max9877.c  --  amp driver क्रम max9877
 *
 * Copyright (C) 2009 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "max9877.h"

अटल स्थिर काष्ठा reg_शेष max9877_regs[] = अणु
	अणु 0, 0x40 पूर्ण,
	अणु 1, 0x00 पूर्ण,
	अणु 2, 0x00 पूर्ण,
	अणु 3, 0x00 पूर्ण,
	अणु 4, 0x49 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(max9877_pgain_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 900, 0),
	2, 2, TLV_DB_SCALE_ITEM(2000, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max9877_output_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-7900, 400, 1),
	8, 15, TLV_DB_SCALE_ITEM(-4700, 300, 0),
	16, 23, TLV_DB_SCALE_ITEM(-2300, 200, 0),
	24, 31, TLV_DB_SCALE_ITEM(-700, 100, 0)
);

अटल स्थिर अक्षर *max9877_out_mode[] = अणु
	"INA -> SPK",
	"INA -> HP",
	"INA -> SPK and HP",
	"INB -> SPK",
	"INB -> HP",
	"INB -> SPK and HP",
	"INA + INB -> SPK",
	"INA + INB -> HP",
	"INA + INB -> SPK and HP",
पूर्ण;

अटल स्थिर अक्षर *max9877_osc_mode[] = अणु
	"1176KHz",
	"1100KHz",
	"700KHz",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत max9877_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(MAX9877_OUTPUT_MODE, 0, ARRAY_SIZE(max9877_out_mode),
			max9877_out_mode),
	SOC_ENUM_SINGLE(MAX9877_OUTPUT_MODE, MAX9877_OSC_OFFSET,
			ARRAY_SIZE(max9877_osc_mode), max9877_osc_mode),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max9877_controls[] = अणु
	SOC_SINGLE_TLV("MAX9877 PGAINA Playback Volume",
		       MAX9877_INPUT_MODE, 0, 2, 0, max9877_pgain_tlv),
	SOC_SINGLE_TLV("MAX9877 PGAINB Playback Volume",
		       MAX9877_INPUT_MODE, 2, 2, 0, max9877_pgain_tlv),
	SOC_SINGLE_TLV("MAX9877 Amp Speaker Playback Volume",
		       MAX9877_SPK_VOLUME, 0, 31, 0, max9877_output_tlv),
	SOC_DOUBLE_R_TLV("MAX9877 Amp HP Playback Volume",
			 MAX9877_HPL_VOLUME, MAX9877_HPR_VOLUME, 0, 31, 0,
			 max9877_output_tlv),
	SOC_SINGLE("MAX9877 INB Stereo Switch",
		   MAX9877_INPUT_MODE, 4, 1, 1),
	SOC_SINGLE("MAX9877 INA Stereo Switch",
		   MAX9877_INPUT_MODE, 5, 1, 1),
	SOC_SINGLE("MAX9877 Zero-crossing detection Switch",
		   MAX9877_INPUT_MODE, 6, 1, 0),
	SOC_SINGLE("MAX9877 Bypass Mode Switch",
		   MAX9877_OUTPUT_MODE, 6, 1, 0),
	SOC_ENUM("MAX9877 Output Mode", max9877_क्रमागत[0]),
	SOC_ENUM("MAX9877 Oscillator Mode", max9877_क्रमागत[1]),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max9877_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("INA1"),
SND_SOC_DAPM_INPUT("INA2"),
SND_SOC_DAPM_INPUT("INB1"),
SND_SOC_DAPM_INPUT("INB2"),
SND_SOC_DAPM_INPUT("RXIN+"),
SND_SOC_DAPM_INPUT("RXIN-"),

SND_SOC_DAPM_PGA("SHDN", MAX9877_OUTPUT_MODE, 7, 1, शून्य, 0),

SND_SOC_DAPM_OUTPUT("OUT+"),
SND_SOC_DAPM_OUTPUT("OUT-"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("HPR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max9877_dapm_routes[] = अणु
	अणु "SHDN", शून्य, "INA1" पूर्ण,
	अणु "SHDN", शून्य, "INA2" पूर्ण,
	अणु "SHDN", शून्य, "INB1" पूर्ण,
	अणु "SHDN", शून्य, "INB2" पूर्ण,

	अणु "OUT+", शून्य, "RXIN+" पूर्ण,
	अणु "OUT+", शून्य, "SHDN" पूर्ण,

	अणु "OUT-", शून्य, "SHDN" पूर्ण,
	अणु "OUT-", शून्य, "RXIN-" पूर्ण,

	अणु "HPL", शून्य, "SHDN" पूर्ण,
	अणु "HPR", शून्य, "SHDN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver max9877_component_driver = अणु
	.controls = max9877_controls,
	.num_controls = ARRAY_SIZE(max9877_controls),

	.dapm_widमाला_लो = max9877_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(max9877_dapm_widमाला_लो),
	.dapm_routes = max9877_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(max9877_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max9877_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = max9877_regs,
	.num_reg_शेषs = ARRAY_SIZE(max9877_regs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max9877_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक i;

	regmap = devm_regmap_init_i2c(client, &max9877_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Ensure the device is in reset state */
	क्रम (i = 0; i < ARRAY_SIZE(max9877_regs); i++)
		regmap_ग_लिखो(regmap, max9877_regs[i].reg, max9877_regs[i].def);

	वापस devm_snd_soc_रेजिस्टर_component(&client->dev,
			&max9877_component_driver, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max9877_i2c_id[] = अणु
	अणु "max9877", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max9877_i2c_id);

अटल काष्ठा i2c_driver max9877_i2c_driver = अणु
	.driver = अणु
		.name = "max9877",
	पूर्ण,
	.probe = max9877_i2c_probe,
	.id_table = max9877_i2c_id,
पूर्ण;

module_i2c_driver(max9877_i2c_driver);

MODULE_DESCRIPTION("ASoC MAX9877 amp driver");
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_LICENSE("GPL");
