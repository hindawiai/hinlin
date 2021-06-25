<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADAV80X Audio Codec driver supporting ADAV801, ADAV803
 *
 * Copyright 2011 Analog Devices Inc.
 * Author: Yi Li <yi.li@analog.com>
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "adav80x.h"

#घोषणा ADAV80X_PLAYBACK_CTRL	0x04
#घोषणा ADAV80X_AUX_IN_CTRL	0x05
#घोषणा ADAV80X_REC_CTRL	0x06
#घोषणा ADAV80X_AUX_OUT_CTRL	0x07
#घोषणा ADAV80X_DPATH_CTRL1	0x62
#घोषणा ADAV80X_DPATH_CTRL2	0x63
#घोषणा ADAV80X_DAC_CTRL1	0x64
#घोषणा ADAV80X_DAC_CTRL2	0x65
#घोषणा ADAV80X_DAC_CTRL3	0x66
#घोषणा ADAV80X_DAC_L_VOL	0x68
#घोषणा ADAV80X_DAC_R_VOL	0x69
#घोषणा ADAV80X_PGA_L_VOL	0x6c
#घोषणा ADAV80X_PGA_R_VOL	0x6d
#घोषणा ADAV80X_ADC_CTRL1	0x6e
#घोषणा ADAV80X_ADC_CTRL2	0x6f
#घोषणा ADAV80X_ADC_L_VOL	0x70
#घोषणा ADAV80X_ADC_R_VOL	0x71
#घोषणा ADAV80X_PLL_CTRL1	0x74
#घोषणा ADAV80X_PLL_CTRL2	0x75
#घोषणा ADAV80X_ICLK_CTRL1	0x76
#घोषणा ADAV80X_ICLK_CTRL2	0x77
#घोषणा ADAV80X_PLL_CLK_SRC	0x78
#घोषणा ADAV80X_PLL_OUTE	0x7a

#घोषणा ADAV80X_PLL_CLK_SRC_PLL_XIN(pll)	0x00
#घोषणा ADAV80X_PLL_CLK_SRC_PLL_MCLKI(pll)	(0x40 << (pll))
#घोषणा ADAV80X_PLL_CLK_SRC_PLL_MASK(pll)	(0x40 << (pll))

#घोषणा ADAV80X_ICLK_CTRL1_DAC_SRC(src)		((src) << 5)
#घोषणा ADAV80X_ICLK_CTRL1_ADC_SRC(src)		((src) << 2)
#घोषणा ADAV80X_ICLK_CTRL1_ICLK2_SRC(src)	(src)
#घोषणा ADAV80X_ICLK_CTRL2_ICLK1_SRC(src)	((src) << 3)

#घोषणा ADAV80X_PLL_CTRL1_PLLDIV		0x10
#घोषणा ADAV80X_PLL_CTRL1_PLLPD(pll)		(0x04 << (pll))
#घोषणा ADAV80X_PLL_CTRL1_XTLPD			0x02

#घोषणा ADAV80X_PLL_CTRL2_FIELD(pll, x)		((x) << ((pll) * 4))

#घोषणा ADAV80X_PLL_CTRL2_FS_48(pll)	ADAV80X_PLL_CTRL2_FIELD((pll), 0x00)
#घोषणा ADAV80X_PLL_CTRL2_FS_32(pll)	ADAV80X_PLL_CTRL2_FIELD((pll), 0x08)
#घोषणा ADAV80X_PLL_CTRL2_FS_44(pll)	ADAV80X_PLL_CTRL2_FIELD((pll), 0x0c)

#घोषणा ADAV80X_PLL_CTRL2_SEL(pll)	ADAV80X_PLL_CTRL2_FIELD((pll), 0x02)
#घोषणा ADAV80X_PLL_CTRL2_DOUB(pll)	ADAV80X_PLL_CTRL2_FIELD((pll), 0x01)
#घोषणा ADAV80X_PLL_CTRL2_PLL_MASK(pll) ADAV80X_PLL_CTRL2_FIELD((pll), 0x0f)

#घोषणा ADAV80X_ADC_CTRL1_MODULATOR_MASK	0x80
#घोषणा ADAV80X_ADC_CTRL1_MODULATOR_128FS	0x00
#घोषणा ADAV80X_ADC_CTRL1_MODULATOR_64FS	0x80

#घोषणा ADAV80X_DAC_CTRL1_PD			0x80

#घोषणा ADAV80X_DAC_CTRL2_DIV1			0x00
#घोषणा ADAV80X_DAC_CTRL2_DIV1_5		0x10
#घोषणा ADAV80X_DAC_CTRL2_DIV2			0x20
#घोषणा ADAV80X_DAC_CTRL2_DIV3			0x30
#घोषणा ADAV80X_DAC_CTRL2_DIV_MASK		0x30

#घोषणा ADAV80X_DAC_CTRL2_INTERPOL_256FS	0x00
#घोषणा ADAV80X_DAC_CTRL2_INTERPOL_128FS	0x40
#घोषणा ADAV80X_DAC_CTRL2_INTERPOL_64FS		0x80
#घोषणा ADAV80X_DAC_CTRL2_INTERPOL_MASK		0xc0

#घोषणा ADAV80X_DAC_CTRL2_DEEMPH_NONE		0x00
#घोषणा ADAV80X_DAC_CTRL2_DEEMPH_44		0x01
#घोषणा ADAV80X_DAC_CTRL2_DEEMPH_32		0x02
#घोषणा ADAV80X_DAC_CTRL2_DEEMPH_48		0x03
#घोषणा ADAV80X_DAC_CTRL2_DEEMPH_MASK		0x01

#घोषणा ADAV80X_CAPTURE_MODE_MASTER		0x20
#घोषणा ADAV80X_CAPTURE_WORD_LEN24		0x00
#घोषणा ADAV80X_CAPTURE_WORD_LEN20		0x04
#घोषणा ADAV80X_CAPTRUE_WORD_LEN18		0x08
#घोषणा ADAV80X_CAPTURE_WORD_LEN16		0x0c
#घोषणा ADAV80X_CAPTURE_WORD_LEN_MASK		0x0c

#घोषणा ADAV80X_CAPTURE_MODE_LEFT_J		0x00
#घोषणा ADAV80X_CAPTURE_MODE_I2S		0x01
#घोषणा ADAV80X_CAPTURE_MODE_RIGHT_J		0x03
#घोषणा ADAV80X_CAPTURE_MODE_MASK		0x03

#घोषणा ADAV80X_PLAYBACK_MODE_MASTER		0x10
#घोषणा ADAV80X_PLAYBACK_MODE_LEFT_J		0x00
#घोषणा ADAV80X_PLAYBACK_MODE_I2S		0x01
#घोषणा ADAV80X_PLAYBACK_MODE_RIGHT_J_24	0x04
#घोषणा ADAV80X_PLAYBACK_MODE_RIGHT_J_20	0x05
#घोषणा ADAV80X_PLAYBACK_MODE_RIGHT_J_18	0x06
#घोषणा ADAV80X_PLAYBACK_MODE_RIGHT_J_16	0x07
#घोषणा ADAV80X_PLAYBACK_MODE_MASK		0x07

#घोषणा ADAV80X_PLL_OUTE_SYSCLKPD(x)		BIT(2 - (x))

अटल स्थिर काष्ठा reg_शेष adav80x_reg_शेषs[] = अणु
	अणु ADAV80X_PLAYBACK_CTRL,	0x01 पूर्ण,
	अणु ADAV80X_AUX_IN_CTRL,		0x01 पूर्ण,
	अणु ADAV80X_REC_CTRL,		0x02 पूर्ण,
	अणु ADAV80X_AUX_OUT_CTRL,		0x01 पूर्ण,
	अणु ADAV80X_DPATH_CTRL1,		0xc0 पूर्ण,
	अणु ADAV80X_DPATH_CTRL2,		0x11 पूर्ण,
	अणु ADAV80X_DAC_CTRL1,		0x00 पूर्ण,
	अणु ADAV80X_DAC_CTRL2,		0x00 पूर्ण,
	अणु ADAV80X_DAC_CTRL3,		0x00 पूर्ण,
	अणु ADAV80X_DAC_L_VOL,		0xff पूर्ण,
	अणु ADAV80X_DAC_R_VOL,		0xff पूर्ण,
	अणु ADAV80X_PGA_L_VOL,		0x00 पूर्ण,
	अणु ADAV80X_PGA_R_VOL,		0x00 पूर्ण,
	अणु ADAV80X_ADC_CTRL1,		0x00 पूर्ण,
	अणु ADAV80X_ADC_CTRL2,		0x00 पूर्ण,
	अणु ADAV80X_ADC_L_VOL,		0xff पूर्ण,
	अणु ADAV80X_ADC_R_VOL,		0xff पूर्ण,
	अणु ADAV80X_PLL_CTRL1,		0x00 पूर्ण,
	अणु ADAV80X_PLL_CTRL2,		0x00 पूर्ण,
	अणु ADAV80X_ICLK_CTRL1,		0x00 पूर्ण,
	अणु ADAV80X_ICLK_CTRL2,		0x00 पूर्ण,
	अणु ADAV80X_PLL_CLK_SRC,		0x00 पूर्ण,
	अणु ADAV80X_PLL_OUTE,		0x00 पूर्ण,
पूर्ण;

काष्ठा adav80x अणु
	काष्ठा regmap *regmap;

	क्रमागत adav80x_clk_src clk_src;
	अचिन्हित पूर्णांक sysclk;
	क्रमागत adav80x_pll_src pll_src;

	अचिन्हित पूर्णांक dai_fmt[2];
	अचिन्हित पूर्णांक rate;
	bool deemph;
	bool sysclk_pd[3];
पूर्ण;

अटल स्थिर अक्षर *adav80x_mux_text[] = अणु
	"ADC",
	"Playback",
	"Aux Playback",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adav80x_mux_values[] = अणु
	0, 2, 3,
पूर्ण;

#घोषणा ADAV80X_MUX_ENUM_DECL(name, reg, shअगरt) \
	SOC_VALUE_ENUM_DOUBLE_DECL(name, reg, shअगरt, 7, \
		ARRAY_SIZE(adav80x_mux_text), adav80x_mux_text, \
		adav80x_mux_values)

अटल ADAV80X_MUX_ENUM_DECL(adav80x_aux_capture_क्रमागत, ADAV80X_DPATH_CTRL1, 0);
अटल ADAV80X_MUX_ENUM_DECL(adav80x_capture_क्रमागत, ADAV80X_DPATH_CTRL1, 3);
अटल ADAV80X_MUX_ENUM_DECL(adav80x_dac_क्रमागत, ADAV80X_DPATH_CTRL2, 3);

अटल स्थिर काष्ठा snd_kcontrol_new adav80x_aux_capture_mux_ctrl =
	SOC_DAPM_ENUM("Route", adav80x_aux_capture_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adav80x_capture_mux_ctrl =
	SOC_DAPM_ENUM("Route", adav80x_capture_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adav80x_dac_mux_ctrl =
	SOC_DAPM_ENUM("Route", adav80x_dac_क्रमागत);

#घोषणा ADAV80X_MUX(name, ctrl) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctrl)

अटल स्थिर काष्ठा snd_soc_dapm_widget adav80x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", शून्य, ADAV80X_DAC_CTRL1, 7, 1),
	SND_SOC_DAPM_ADC("ADC", शून्य, ADAV80X_ADC_CTRL1, 5, 1),

	SND_SOC_DAPM_PGA("Right PGA", ADAV80X_ADC_CTRL1, 0, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Left PGA", ADAV80X_ADC_CTRL1, 1, 1, शून्य, 0),

	SND_SOC_DAPM_AIF_OUT("AIFOUT", "HiFi Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFIN", "HiFi Playback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("AIFAUXOUT", "Aux Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFAUXIN", "Aux Playback", 0, SND_SOC_NOPM, 0, 0),

	ADAV80X_MUX("Aux Capture Select", &adav80x_aux_capture_mux_ctrl),
	ADAV80X_MUX("Capture Select", &adav80x_capture_mux_ctrl),
	ADAV80X_MUX("DAC Select", &adav80x_dac_mux_ctrl),

	SND_SOC_DAPM_INPUT("VINR"),
	SND_SOC_DAPM_INPUT("VINL"),
	SND_SOC_DAPM_OUTPUT("VOUTR"),
	SND_SOC_DAPM_OUTPUT("VOUTL"),

	SND_SOC_DAPM_SUPPLY("SYSCLK", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", ADAV80X_PLL_CTRL1, 2, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2", ADAV80X_PLL_CTRL1, 3, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("OSC", ADAV80X_PLL_CTRL1, 1, 1, शून्य, 0),
पूर्ण;

अटल पूर्णांक adav80x_dapm_sysclk_check(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	स्थिर अक्षर *clk;

	चयन (adav80x->clk_src) अणु
	हाल ADAV80X_CLK_PLL1:
		clk = "PLL1";
		अवरोध;
	हाल ADAV80X_CLK_PLL2:
		clk = "PLL2";
		अवरोध;
	हाल ADAV80X_CLK_XTAL:
		clk = "OSC";
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस म_भेद(source->name, clk) == 0;
पूर्ण

अटल पूर्णांक adav80x_dapm_pll_check(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	वापस adav80x->pll_src == ADAV80X_PLL_SRC_XTAL;
पूर्ण


अटल स्थिर काष्ठा snd_soc_dapm_route adav80x_dapm_routes[] = अणु
	अणु "DAC Select", "ADC", "ADC" पूर्ण,
	अणु "DAC Select", "Playback", "AIFIN" पूर्ण,
	अणु "DAC Select", "Aux Playback", "AIFAUXIN" पूर्ण,
	अणु "DAC", शून्य,  "DAC Select" पूर्ण,

	अणु "Capture Select", "ADC", "ADC" पूर्ण,
	अणु "Capture Select", "Playback", "AIFIN" पूर्ण,
	अणु "Capture Select", "Aux Playback", "AIFAUXIN" पूर्ण,
	अणु "AIFOUT", शून्य,  "Capture Select" पूर्ण,

	अणु "Aux Capture Select", "ADC", "ADC" पूर्ण,
	अणु "Aux Capture Select", "Playback", "AIFIN" पूर्ण,
	अणु "Aux Capture Select", "Aux Playback", "AIFAUXIN" पूर्ण,
	अणु "AIFAUXOUT", शून्य,  "Aux Capture Select" पूर्ण,

	अणु "VOUTR",  शून्य, "DAC" पूर्ण,
	अणु "VOUTL",  शून्य, "DAC" पूर्ण,

	अणु "Left PGA", शून्य, "VINL" पूर्ण,
	अणु "Right PGA", शून्य, "VINR" पूर्ण,
	अणु "ADC", शून्य, "Left PGA" पूर्ण,
	अणु "ADC", शून्य, "Right PGA" पूर्ण,

	अणु "SYSCLK", शून्य, "PLL1", adav80x_dapm_sysclk_check पूर्ण,
	अणु "SYSCLK", शून्य, "PLL2", adav80x_dapm_sysclk_check पूर्ण,
	अणु "SYSCLK", शून्य, "OSC", adav80x_dapm_sysclk_check पूर्ण,
	अणु "PLL1", शून्य, "OSC", adav80x_dapm_pll_check पूर्ण,
	अणु "PLL2", शून्य, "OSC", adav80x_dapm_pll_check पूर्ण,

	अणु "ADC", शून्य, "SYSCLK" पूर्ण,
	अणु "DAC", शून्य, "SYSCLK" पूर्ण,
	अणु "AIFOUT", शून्य, "SYSCLK" पूर्ण,
	अणु "AIFAUXOUT", शून्य, "SYSCLK" पूर्ण,
	अणु "AIFIN", शून्य, "SYSCLK" पूर्ण,
	अणु "AIFAUXIN", शून्य, "SYSCLK" पूर्ण,
पूर्ण;

अटल पूर्णांक adav80x_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (adav80x->deemph) अणु
		चयन (adav80x->rate) अणु
		हाल 32000:
			val = ADAV80X_DAC_CTRL2_DEEMPH_32;
			अवरोध;
		हाल 44100:
			val = ADAV80X_DAC_CTRL2_DEEMPH_44;
			अवरोध;
		हाल 48000:
		हाल 64000:
		हाल 88200:
		हाल 96000:
			val = ADAV80X_DAC_CTRL2_DEEMPH_48;
			अवरोध;
		शेष:
			val = ADAV80X_DAC_CTRL2_DEEMPH_NONE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = ADAV80X_DAC_CTRL2_DEEMPH_NONE;
	पूर्ण

	वापस regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL2,
		ADAV80X_DAC_CTRL2_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक adav80x_put_deemph(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	adav80x->deemph = deemph;

	वापस adav80x_set_deemph(component);
पूर्ण

अटल पूर्णांक adav80x_get_deemph(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = adav80x->deemph;
	वापस 0;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(adav80x_inpga_tlv, 0, 50, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(adav80x_digital_tlv, -9563, 0);

अटल स्थिर काष्ठा snd_kcontrol_new adav80x_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume", ADAV80X_DAC_L_VOL,
		ADAV80X_DAC_R_VOL, 0, 0xff, 0, adav80x_digital_tlv),
	SOC_DOUBLE_R_TLV("Master Capture Volume", ADAV80X_ADC_L_VOL,
			ADAV80X_ADC_R_VOL, 0, 0xff, 0, adav80x_digital_tlv),

	SOC_DOUBLE_R_TLV("PGA Capture Volume", ADAV80X_PGA_L_VOL,
			ADAV80X_PGA_R_VOL, 0, 0x30, 0, adav80x_inpga_tlv),

	SOC_DOUBLE("Master Playback Switch", ADAV80X_DAC_CTRL1, 0, 1, 1, 0),
	SOC_DOUBLE("Master Capture Switch", ADAV80X_ADC_CTRL1, 2, 3, 1, 1),

	SOC_SINGLE("ADC High Pass Filter Switch", ADAV80X_ADC_CTRL1, 6, 1, 0),

	SOC_SINGLE_BOOL_EXT("Playback De-emphasis Switch", 0,
			adav80x_get_deemph, adav80x_put_deemph),
पूर्ण;

अटल अचिन्हित पूर्णांक adav80x_port_ctrl_regs[2][2] = अणु
	अणु ADAV80X_REC_CTRL, ADAV80X_PLAYBACK_CTRL, पूर्ण,
	अणु ADAV80X_AUX_OUT_CTRL, ADAV80X_AUX_IN_CTRL पूर्ण,
पूर्ण;

अटल पूर्णांक adav80x_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक capture = 0x00;
	अचिन्हित पूर्णांक playback = 0x00;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		capture |= ADAV80X_CAPTURE_MODE_MASTER;
		playback |= ADAV80X_PLAYBACK_MODE_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		capture |= ADAV80X_CAPTURE_MODE_I2S;
		playback |= ADAV80X_PLAYBACK_MODE_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		capture |= ADAV80X_CAPTURE_MODE_LEFT_J;
		playback |= ADAV80X_PLAYBACK_MODE_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		capture |= ADAV80X_CAPTURE_MODE_RIGHT_J;
		playback |= ADAV80X_PLAYBACK_MODE_RIGHT_J_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][0],
		ADAV80X_CAPTURE_MODE_MASK | ADAV80X_CAPTURE_MODE_MASTER,
		capture);
	regmap_ग_लिखो(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][1],
		playback);

	adav80x->dai_fmt[dai->id] = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_adc_घड़ी(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक sample_rate)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (sample_rate <= 48000)
		val = ADAV80X_ADC_CTRL1_MODULATOR_128FS;
	अन्यथा
		val = ADAV80X_ADC_CTRL1_MODULATOR_64FS;

	regmap_update_bits(adav80x->regmap, ADAV80X_ADC_CTRL1,
		ADAV80X_ADC_CTRL1_MODULATOR_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_dac_घड़ी(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक sample_rate)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (sample_rate <= 48000)
		val = ADAV80X_DAC_CTRL2_DIV1 | ADAV80X_DAC_CTRL2_INTERPOL_256FS;
	अन्यथा
		val = ADAV80X_DAC_CTRL2_DIV2 | ADAV80X_DAC_CTRL2_INTERPOL_128FS;

	regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL2,
		ADAV80X_DAC_CTRL2_DIV_MASK | ADAV80X_DAC_CTRL2_INTERPOL_MASK,
		val);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_capture_pcm_क्रमmat(काष्ठा snd_soc_component *component,
		काष्ठा snd_soc_dai *dai, काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	चयन (params_width(params)) अणु
	हाल 16:
		val = ADAV80X_CAPTURE_WORD_LEN16;
		अवरोध;
	हाल 18:
		val = ADAV80X_CAPTRUE_WORD_LEN18;
		अवरोध;
	हाल 20:
		val = ADAV80X_CAPTURE_WORD_LEN20;
		अवरोध;
	हाल 24:
		val = ADAV80X_CAPTURE_WORD_LEN24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][0],
		ADAV80X_CAPTURE_WORD_LEN_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_playback_pcm_क्रमmat(काष्ठा snd_soc_component *component,
		काष्ठा snd_soc_dai *dai, काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (adav80x->dai_fmt[dai->id] != SND_SOC_DAIFMT_RIGHT_J)
		वापस 0;

	चयन (params_width(params)) अणु
	हाल 16:
		val = ADAV80X_PLAYBACK_MODE_RIGHT_J_16;
		अवरोध;
	हाल 18:
		val = ADAV80X_PLAYBACK_MODE_RIGHT_J_18;
		अवरोध;
	हाल 20:
		val = ADAV80X_PLAYBACK_MODE_RIGHT_J_20;
		अवरोध;
	हाल 24:
		val = ADAV80X_PLAYBACK_MODE_RIGHT_J_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][1],
		ADAV80X_PLAYBACK_MODE_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक rate = params_rate(params);

	अगर (rate * 256 != adav80x->sysclk)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		adav80x_set_playback_pcm_क्रमmat(component, dai, params);
		adav80x_set_dac_घड़ी(component, rate);
	पूर्ण अन्यथा अणु
		adav80x_set_capture_pcm_क्रमmat(component, dai, params);
		adav80x_set_adc_घड़ी(component, rate);
	पूर्ण
	adav80x->rate = rate;
	adav80x_set_deemph(component);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_sysclk(काष्ठा snd_soc_component *component,
			      पूर्णांक clk_id, पूर्णांक source,
			      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (dir == SND_SOC_CLOCK_IN) अणु
		चयन (clk_id) अणु
		हाल ADAV80X_CLK_XIN:
		हाल ADAV80X_CLK_XTAL:
		हाल ADAV80X_CLK_MCLKI:
		हाल ADAV80X_CLK_PLL1:
		हाल ADAV80X_CLK_PLL2:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		adav80x->sysclk = freq;

		अगर (adav80x->clk_src != clk_id) अणु
			अचिन्हित पूर्णांक iclk_ctrl1, iclk_ctrl2;

			adav80x->clk_src = clk_id;
			अगर (clk_id == ADAV80X_CLK_XTAL)
				clk_id = ADAV80X_CLK_XIN;

			iclk_ctrl1 = ADAV80X_ICLK_CTRL1_DAC_SRC(clk_id) |
					ADAV80X_ICLK_CTRL1_ADC_SRC(clk_id) |
					ADAV80X_ICLK_CTRL1_ICLK2_SRC(clk_id);
			iclk_ctrl2 = ADAV80X_ICLK_CTRL2_ICLK1_SRC(clk_id);

			regmap_ग_लिखो(adav80x->regmap, ADAV80X_ICLK_CTRL1,
				iclk_ctrl1);
			regmap_ग_लिखो(adav80x->regmap, ADAV80X_ICLK_CTRL2,
				iclk_ctrl2);

			snd_soc_dapm_sync(dapm);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक mask;

		चयन (clk_id) अणु
		हाल ADAV80X_CLK_SYSCLK1:
		हाल ADAV80X_CLK_SYSCLK2:
		हाल ADAV80X_CLK_SYSCLK3:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		clk_id -= ADAV80X_CLK_SYSCLK1;
		mask = ADAV80X_PLL_OUTE_SYSCLKPD(clk_id);

		अगर (freq == 0) अणु
			regmap_update_bits(adav80x->regmap, ADAV80X_PLL_OUTE,
				mask, mask);
			adav80x->sysclk_pd[clk_id] = true;
		पूर्ण अन्यथा अणु
			regmap_update_bits(adav80x->regmap, ADAV80X_PLL_OUTE,
				mask, 0);
			adav80x->sysclk_pd[clk_id] = false;
		पूर्ण

		snd_soc_dapm_mutex_lock(dapm);

		अगर (adav80x->sysclk_pd[0])
			snd_soc_dapm_disable_pin_unlocked(dapm, "PLL1");
		अन्यथा
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PLL1");

		अगर (adav80x->sysclk_pd[1] || adav80x->sysclk_pd[2])
			snd_soc_dapm_disable_pin_unlocked(dapm, "PLL2");
		अन्यथा
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PLL2");

		snd_soc_dapm_sync_unlocked(dapm);

		snd_soc_dapm_mutex_unlock(dapm);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक pll_ctrl1 = 0;
	अचिन्हित पूर्णांक pll_ctrl2 = 0;
	अचिन्हित पूर्णांक pll_src;

	चयन (source) अणु
	हाल ADAV80X_PLL_SRC_XTAL:
	हाल ADAV80X_PLL_SRC_XIN:
	हाल ADAV80X_PLL_SRC_MCLKI:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!freq_out)
		वापस 0;

	चयन (freq_in) अणु
	हाल 27000000:
		अवरोध;
	हाल 54000000:
		अगर (source == ADAV80X_PLL_SRC_XIN) अणु
			pll_ctrl1 |= ADAV80X_PLL_CTRL1_PLLDIV;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (freq_out > 12288000) अणु
		pll_ctrl2 |= ADAV80X_PLL_CTRL2_DOUB(pll_id);
		freq_out /= 2;
	पूर्ण

	/* freq_out = sample_rate * 256 */
	चयन (freq_out) अणु
	हाल 8192000:
		pll_ctrl2 |= ADAV80X_PLL_CTRL2_FS_32(pll_id);
		अवरोध;
	हाल 11289600:
		pll_ctrl2 |= ADAV80X_PLL_CTRL2_FS_44(pll_id);
		अवरोध;
	हाल 12288000:
		pll_ctrl2 |= ADAV80X_PLL_CTRL2_FS_48(pll_id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adav80x->regmap, ADAV80X_PLL_CTRL1,
			ADAV80X_PLL_CTRL1_PLLDIV, pll_ctrl1);
	regmap_update_bits(adav80x->regmap, ADAV80X_PLL_CTRL2,
			ADAV80X_PLL_CTRL2_PLL_MASK(pll_id), pll_ctrl2);

	अगर (source != adav80x->pll_src) अणु
		अगर (source == ADAV80X_PLL_SRC_MCLKI)
			pll_src = ADAV80X_PLL_CLK_SRC_PLL_MCLKI(pll_id);
		अन्यथा
			pll_src = ADAV80X_PLL_CLK_SRC_PLL_XIN(pll_id);

		regmap_update_bits(adav80x->regmap, ADAV80X_PLL_CLK_SRC,
				ADAV80X_PLL_CLK_SRC_PLL_MASK(pll_id), pll_src);

		adav80x->pll_src = source;

		snd_soc_dapm_sync(dapm);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = ADAV80X_DAC_CTRL1_PD;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL1, mask,
			0x00);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL1, mask,
			mask);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Enक्रमce the same sample rate on all audio पूर्णांकerfaces */
अटल पूर्णांक adav80x_dai_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	अगर (!snd_soc_component_active(component) || !adav80x->rate)
		वापस 0;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, adav80x->rate);
पूर्ण

अटल व्योम adav80x_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	अगर (!snd_soc_component_active(component))
		adav80x->rate = 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops adav80x_dai_ops = अणु
	.set_fmt = adav80x_set_dai_fmt,
	.hw_params = adav80x_hw_params,
	.startup = adav80x_dai_startup,
	.shutकरोwn = adav80x_dai_shutकरोwn,
पूर्ण;

#घोषणा ADAV80X_PLAYBACK_RATES (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 | SNDRV_PCM_RATE_88200 | \
	SNDRV_PCM_RATE_96000)

#घोषणा ADAV80X_CAPTURE_RATES (SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000)

#घोषणा ADAV80X_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S18_3LE | \
	SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver adav80x_dais[] = अणु
	अणु
		.name = "adav80x-hifi",
		.id = 0,
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = ADAV80X_PLAYBACK_RATES,
			.क्रमmats = ADAV80X_FORMATS,
	पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = ADAV80X_CAPTURE_RATES,
			.क्रमmats = ADAV80X_FORMATS,
		पूर्ण,
		.ops = &adav80x_dai_ops,
	पूर्ण,
	अणु
		.name = "adav80x-aux",
		.id = 1,
		.playback = अणु
			.stream_name = "Aux Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = ADAV80X_PLAYBACK_RATES,
			.क्रमmats = ADAV80X_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Aux Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = ADAV80X_CAPTURE_RATES,
			.क्रमmats = ADAV80X_FORMATS,
		पूर्ण,
		.ops = &adav80x_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक adav80x_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	/* Force PLLs on क्रम SYSCLK output */
	snd_soc_dapm_क्रमce_enable_pin(dapm, "PLL1");
	snd_soc_dapm_क्रमce_enable_pin(dapm, "PLL2");

	/* Power करोwn S/PDIF receiver, since it is currently not supported */
	regmap_ग_लिखो(adav80x->regmap, ADAV80X_PLL_OUTE, 0x20);
	/* Disable DAC zero flag */
	regmap_ग_लिखो(adav80x->regmap, ADAV80X_DAC_CTRL3, 0x6);

	वापस 0;
पूर्ण

अटल पूर्णांक adav80x_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adav80x *adav80x = snd_soc_component_get_drvdata(component);

	regcache_sync(adav80x->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver adav80x_component_driver = अणु
	.probe			= adav80x_probe,
	.resume			= adav80x_resume,
	.set_bias_level		= adav80x_set_bias_level,
	.set_pll		= adav80x_set_pll,
	.set_sysclk		= adav80x_set_sysclk,
	.controls		= adav80x_controls,
	.num_controls		= ARRAY_SIZE(adav80x_controls),
	.dapm_widमाला_लो		= adav80x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adav80x_dapm_widमाला_लो),
	.dapm_routes		= adav80x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adav80x_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक adav80x_bus_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा adav80x *adav80x;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	adav80x = devm_kzalloc(dev, माप(*adav80x), GFP_KERNEL);
	अगर (!adav80x)
		वापस -ENOMEM;

	dev_set_drvdata(dev, adav80x);
	adav80x->regmap = regmap;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &adav80x_component_driver,
		adav80x_dais, ARRAY_SIZE(adav80x_dais));
पूर्ण
EXPORT_SYMBOL_GPL(adav80x_bus_probe);

स्थिर काष्ठा regmap_config adav80x_regmap_config = अणु
	.val_bits = 8,
	.pad_bits = 1,
	.reg_bits = 7,

	.max_रेजिस्टर = ADAV80X_PLL_OUTE,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = adav80x_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adav80x_reg_शेषs),
पूर्ण;
EXPORT_SYMBOL_GPL(adav80x_regmap_config);

MODULE_DESCRIPTION("ASoC ADAV80x driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_AUTHOR("Yi Li <yi.li@analog.com>>");
MODULE_LICENSE("GPL");
