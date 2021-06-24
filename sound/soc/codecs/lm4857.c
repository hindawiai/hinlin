<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LM4857 AMP driver
 *
 * Copyright 2007 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com
 * Copyright 2011 Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

अटल स्थिर काष्ठा reg_शेष lm4857_शेष_regs[] = अणु
	अणु 0x0, 0x00 पूर्ण,
	अणु 0x1, 0x00 पूर्ण,
	अणु 0x2, 0x00 पूर्ण,
	अणु 0x3, 0x00 पूर्ण,
पूर्ण;

/* The रेजिस्टर offsets in the cache array */
#घोषणा LM4857_MVOL 0
#घोषणा LM4857_LVOL 1
#घोषणा LM4857_RVOL 2
#घोषणा LM4857_CTRL 3

/* the shअगरts required to set these bits */
#घोषणा LM4857_3D 5
#घोषणा LM4857_WAKEUP 5
#घोषणा LM4857_EPGAIN 4

अटल स्थिर अचिन्हित पूर्णांक lm4857_mode_values[] = अणु
	0,
	6,
	7,
	8,
	9,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lm4857_mode_texts[] = अणु
	"Off",
	"Earpiece",
	"Loudspeaker",
	"Loudspeaker + Headphone",
	"Headphone",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_AUTODISABLE_DECL(lm4857_mode_क्रमागत,
	LM4857_CTRL, 0, 0xf, lm4857_mode_texts, lm4857_mode_values);

अटल स्थिर काष्ठा snd_kcontrol_new lm4857_mode_ctrl =
	SOC_DAPM_ENUM("Mode", lm4857_mode_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget lm4857_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("IN"),

	SND_SOC_DAPM_DEMUX("Mode", SND_SOC_NOPM, 0, 0, &lm4857_mode_ctrl),

	SND_SOC_DAPM_OUTPUT("LS"),
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("EP"),
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(stereo_tlv, -4050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mono_tlv, -3450, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new lm4857_controls[] = अणु
	SOC_SINGLE_TLV("Left Playback Volume", LM4857_LVOL, 0, 31, 0,
		stereo_tlv),
	SOC_SINGLE_TLV("Right Playback Volume", LM4857_RVOL, 0, 31, 0,
		stereo_tlv),
	SOC_SINGLE_TLV("Mono Playback Volume", LM4857_MVOL, 0, 31, 0,
		mono_tlv),
	SOC_SINGLE("Spk 3D Playback Switch", LM4857_LVOL, LM4857_3D, 1, 0),
	SOC_SINGLE("HP 3D Playback Switch", LM4857_RVOL, LM4857_3D, 1, 0),
	SOC_SINGLE("Fast Wakeup Playback Switch", LM4857_CTRL,
		LM4857_WAKEUP, 1, 0),
	SOC_SINGLE("Earpiece 6dB Playback Switch", LM4857_CTRL,
		LM4857_EPGAIN, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lm4857_routes[] = अणु
	अणु "Mode", शून्य, "IN" पूर्ण,
	अणु "LS", "Loudspeaker", "Mode" पूर्ण,
	अणु "LS", "Loudspeaker + Headphone", "Mode" पूर्ण,
	अणु "HP", "Headphone", "Mode" पूर्ण,
	अणु "HP", "Loudspeaker + Headphone", "Mode" पूर्ण,
	अणु "EP", "Earpiece", "Mode" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver lm4857_component_driver = अणु
	.controls = lm4857_controls,
	.num_controls = ARRAY_SIZE(lm4857_controls),
	.dapm_widमाला_लो = lm4857_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(lm4857_dapm_widमाला_लो),
	.dapm_routes = lm4857_routes,
	.num_dapm_routes = ARRAY_SIZE(lm4857_routes),
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm4857_regmap_config = अणु
	.val_bits = 6,
	.reg_bits = 2,

	.max_रेजिस्टर = LM4857_CTRL,

	.cache_type = REGCACHE_FLAT,
	.reg_शेषs = lm4857_शेष_regs,
	.num_reg_शेषs = ARRAY_SIZE(lm4857_शेष_regs),
पूर्ण;

अटल पूर्णांक lm4857_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &lm4857_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&lm4857_component_driver, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm4857_i2c_id[] = अणु
	अणु "lm4857", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm4857_i2c_id);

अटल काष्ठा i2c_driver lm4857_i2c_driver = अणु
	.driver = अणु
		.name = "lm4857",
	पूर्ण,
	.probe = lm4857_i2c_probe,
	.id_table = lm4857_i2c_id,
पूर्ण;

module_i2c_driver(lm4857_i2c_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("LM4857 amplifier driver");
MODULE_LICENSE("GPL");
