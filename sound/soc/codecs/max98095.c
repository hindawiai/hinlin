<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98095.c -- MAX98095 ALSA SoC Audio driver
 *
 * Copyright 2011 Maxim Integrated Products
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <sound/max98095.h>
#समावेश <sound/jack.h>
#समावेश "max98095.h"

क्रमागत max98095_type अणु
	MAX98095,
पूर्ण;

काष्ठा max98095_cdata अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक fmt;
	पूर्णांक eq_sel;
	पूर्णांक bq_sel;
पूर्ण;

काष्ठा max98095_priv अणु
	काष्ठा regmap *regmap;
	क्रमागत max98095_type devtype;
	काष्ठा max98095_pdata *pdata;
	काष्ठा clk *mclk;
	अचिन्हित पूर्णांक sysclk;
	काष्ठा max98095_cdata dai[3];
	स्थिर अक्षर **eq_texts;
	स्थिर अक्षर **bq_texts;
	काष्ठा soc_क्रमागत eq_क्रमागत;
	काष्ठा soc_क्रमागत bq_क्रमागत;
	पूर्णांक eq_textcnt;
	पूर्णांक bq_textcnt;
	u8 lin_state;
	अचिन्हित पूर्णांक mic1pre;
	अचिन्हित पूर्णांक mic2pre;
	काष्ठा snd_soc_jack *headphone_jack;
	काष्ठा snd_soc_jack *mic_jack;
	काष्ठा mutex lock;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष max98095_reg_def[] = अणु
	अणु  0xf, 0x00 पूर्ण, /* 0F */
	अणु 0x10, 0x00 पूर्ण, /* 10 */
	अणु 0x11, 0x00 पूर्ण, /* 11 */
	अणु 0x12, 0x00 पूर्ण, /* 12 */
	अणु 0x13, 0x00 पूर्ण, /* 13 */
	अणु 0x14, 0x00 पूर्ण, /* 14 */
	अणु 0x15, 0x00 पूर्ण, /* 15 */
	अणु 0x16, 0x00 पूर्ण, /* 16 */
	अणु 0x17, 0x00 पूर्ण, /* 17 */
	अणु 0x18, 0x00 पूर्ण, /* 18 */
	अणु 0x19, 0x00 पूर्ण, /* 19 */
	अणु 0x1a, 0x00 पूर्ण, /* 1A */
	अणु 0x1b, 0x00 पूर्ण, /* 1B */
	अणु 0x1c, 0x00 पूर्ण, /* 1C */
	अणु 0x1d, 0x00 पूर्ण, /* 1D */
	अणु 0x1e, 0x00 पूर्ण, /* 1E */
	अणु 0x1f, 0x00 पूर्ण, /* 1F */
	अणु 0x20, 0x00 पूर्ण, /* 20 */
	अणु 0x21, 0x00 पूर्ण, /* 21 */
	अणु 0x22, 0x00 पूर्ण, /* 22 */
	अणु 0x23, 0x00 पूर्ण, /* 23 */
	अणु 0x24, 0x00 पूर्ण, /* 24 */
	अणु 0x25, 0x00 पूर्ण, /* 25 */
	अणु 0x26, 0x00 पूर्ण, /* 26 */
	अणु 0x27, 0x00 पूर्ण, /* 27 */
	अणु 0x28, 0x00 पूर्ण, /* 28 */
	अणु 0x29, 0x00 पूर्ण, /* 29 */
	अणु 0x2a, 0x00 पूर्ण, /* 2A */
	अणु 0x2b, 0x00 पूर्ण, /* 2B */
	अणु 0x2c, 0x00 पूर्ण, /* 2C */
	अणु 0x2d, 0x00 पूर्ण, /* 2D */
	अणु 0x2e, 0x00 पूर्ण, /* 2E */
	अणु 0x2f, 0x00 पूर्ण, /* 2F */
	अणु 0x30, 0x00 पूर्ण, /* 30 */
	अणु 0x31, 0x00 पूर्ण, /* 31 */
	अणु 0x32, 0x00 पूर्ण, /* 32 */
	अणु 0x33, 0x00 पूर्ण, /* 33 */
	अणु 0x34, 0x00 पूर्ण, /* 34 */
	अणु 0x35, 0x00 पूर्ण, /* 35 */
	अणु 0x36, 0x00 पूर्ण, /* 36 */
	अणु 0x37, 0x00 पूर्ण, /* 37 */
	अणु 0x38, 0x00 पूर्ण, /* 38 */
	अणु 0x39, 0x00 पूर्ण, /* 39 */
	अणु 0x3a, 0x00 पूर्ण, /* 3A */
	अणु 0x3b, 0x00 पूर्ण, /* 3B */
	अणु 0x3c, 0x00 पूर्ण, /* 3C */
	अणु 0x3d, 0x00 पूर्ण, /* 3D */
	अणु 0x3e, 0x00 पूर्ण, /* 3E */
	अणु 0x3f, 0x00 पूर्ण, /* 3F */
	अणु 0x40, 0x00 पूर्ण, /* 40 */
	अणु 0x41, 0x00 पूर्ण, /* 41 */
	अणु 0x42, 0x00 पूर्ण, /* 42 */
	अणु 0x43, 0x00 पूर्ण, /* 43 */
	अणु 0x44, 0x00 पूर्ण, /* 44 */
	अणु 0x45, 0x00 पूर्ण, /* 45 */
	अणु 0x46, 0x00 पूर्ण, /* 46 */
	अणु 0x47, 0x00 पूर्ण, /* 47 */
	अणु 0x48, 0x00 पूर्ण, /* 48 */
	अणु 0x49, 0x00 पूर्ण, /* 49 */
	अणु 0x4a, 0x00 पूर्ण, /* 4A */
	अणु 0x4b, 0x00 पूर्ण, /* 4B */
	अणु 0x4c, 0x00 पूर्ण, /* 4C */
	अणु 0x4d, 0x00 पूर्ण, /* 4D */
	अणु 0x4e, 0x00 पूर्ण, /* 4E */
	अणु 0x4f, 0x00 पूर्ण, /* 4F */
	अणु 0x50, 0x00 पूर्ण, /* 50 */
	अणु 0x51, 0x00 पूर्ण, /* 51 */
	अणु 0x52, 0x00 पूर्ण, /* 52 */
	अणु 0x53, 0x00 पूर्ण, /* 53 */
	अणु 0x54, 0x00 पूर्ण, /* 54 */
	अणु 0x55, 0x00 पूर्ण, /* 55 */
	अणु 0x56, 0x00 पूर्ण, /* 56 */
	अणु 0x57, 0x00 पूर्ण, /* 57 */
	अणु 0x58, 0x00 पूर्ण, /* 58 */
	अणु 0x59, 0x00 पूर्ण, /* 59 */
	अणु 0x5a, 0x00 पूर्ण, /* 5A */
	अणु 0x5b, 0x00 पूर्ण, /* 5B */
	अणु 0x5c, 0x00 पूर्ण, /* 5C */
	अणु 0x5d, 0x00 पूर्ण, /* 5D */
	अणु 0x5e, 0x00 पूर्ण, /* 5E */
	अणु 0x5f, 0x00 पूर्ण, /* 5F */
	अणु 0x60, 0x00 पूर्ण, /* 60 */
	अणु 0x61, 0x00 पूर्ण, /* 61 */
	अणु 0x62, 0x00 पूर्ण, /* 62 */
	अणु 0x63, 0x00 पूर्ण, /* 63 */
	अणु 0x64, 0x00 पूर्ण, /* 64 */
	अणु 0x65, 0x00 पूर्ण, /* 65 */
	अणु 0x66, 0x00 पूर्ण, /* 66 */
	अणु 0x67, 0x00 पूर्ण, /* 67 */
	अणु 0x68, 0x00 पूर्ण, /* 68 */
	अणु 0x69, 0x00 पूर्ण, /* 69 */
	अणु 0x6a, 0x00 पूर्ण, /* 6A */
	अणु 0x6b, 0x00 पूर्ण, /* 6B */
	अणु 0x6c, 0x00 पूर्ण, /* 6C */
	अणु 0x6d, 0x00 पूर्ण, /* 6D */
	अणु 0x6e, 0x00 पूर्ण, /* 6E */
	अणु 0x6f, 0x00 पूर्ण, /* 6F */
	अणु 0x70, 0x00 पूर्ण, /* 70 */
	अणु 0x71, 0x00 पूर्ण, /* 71 */
	अणु 0x72, 0x00 पूर्ण, /* 72 */
	अणु 0x73, 0x00 पूर्ण, /* 73 */
	अणु 0x74, 0x00 पूर्ण, /* 74 */
	अणु 0x75, 0x00 पूर्ण, /* 75 */
	अणु 0x76, 0x00 पूर्ण, /* 76 */
	अणु 0x77, 0x00 पूर्ण, /* 77 */
	अणु 0x78, 0x00 पूर्ण, /* 78 */
	अणु 0x79, 0x00 पूर्ण, /* 79 */
	अणु 0x7a, 0x00 पूर्ण, /* 7A */
	अणु 0x7b, 0x00 पूर्ण, /* 7B */
	अणु 0x7c, 0x00 पूर्ण, /* 7C */
	अणु 0x7d, 0x00 पूर्ण, /* 7D */
	अणु 0x7e, 0x00 पूर्ण, /* 7E */
	अणु 0x7f, 0x00 पूर्ण, /* 7F */
	अणु 0x80, 0x00 पूर्ण, /* 80 */
	अणु 0x81, 0x00 पूर्ण, /* 81 */
	अणु 0x82, 0x00 पूर्ण, /* 82 */
	अणु 0x83, 0x00 पूर्ण, /* 83 */
	अणु 0x84, 0x00 पूर्ण, /* 84 */
	अणु 0x85, 0x00 पूर्ण, /* 85 */
	अणु 0x86, 0x00 पूर्ण, /* 86 */
	अणु 0x87, 0x00 पूर्ण, /* 87 */
	अणु 0x88, 0x00 पूर्ण, /* 88 */
	अणु 0x89, 0x00 पूर्ण, /* 89 */
	अणु 0x8a, 0x00 पूर्ण, /* 8A */
	अणु 0x8b, 0x00 पूर्ण, /* 8B */
	अणु 0x8c, 0x00 पूर्ण, /* 8C */
	अणु 0x8d, 0x00 पूर्ण, /* 8D */
	अणु 0x8e, 0x00 पूर्ण, /* 8E */
	अणु 0x8f, 0x00 पूर्ण, /* 8F */
	अणु 0x90, 0x00 पूर्ण, /* 90 */
	अणु 0x91, 0x00 पूर्ण, /* 91 */
	अणु 0x92, 0x30 पूर्ण, /* 92 */
	अणु 0x93, 0xF0 पूर्ण, /* 93 */
	अणु 0x94, 0x00 पूर्ण, /* 94 */
	अणु 0x95, 0x00 पूर्ण, /* 95 */
	अणु 0x96, 0x3F पूर्ण, /* 96 */
	अणु 0x97, 0x00 पूर्ण, /* 97 */
	अणु 0xff, 0x00 पूर्ण, /* FF */
पूर्ण;

अटल bool max98095_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98095_001_HOST_INT_STS ... M98095_097_PWR_SYS:
	हाल M98095_0FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98095_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98095_00F_HOST_CFG ... M98095_097_PWR_SYS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98095_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98095_000_HOST_DATA ... M98095_00E_TEMP_SENSOR_STS:
	हाल M98095_REG_MAX_CACHED + 1 ... M98095_0FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max98095_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = max98095_reg_def,
	.num_reg_शेषs = ARRAY_SIZE(max98095_reg_def),
	.max_रेजिस्टर = M98095_0FF_REV_ID,
	.cache_type = REGCACHE_RBTREE,

	.पढ़ोable_reg = max98095_पढ़ोable,
	.ग_लिखोable_reg = max98095_ग_लिखोable,
	.अस्थिर_reg = max98095_अस्थिर,
पूर्ण;

/*
 * Load equalizer DSP coefficient configurations रेजिस्टरs
 */
अटल व्योम m98095_eq_band(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक dai,
		    अचिन्हित पूर्णांक band, u16 *coefs)
अणु
	अचिन्हित पूर्णांक eq_reg;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(band > 4) ||
	    WARN_ON(dai > 1))
		वापस;

	/* Load the base रेजिस्टर address */
	eq_reg = dai ? M98095_142_DAI2_EQ_BASE : M98095_110_DAI1_EQ_BASE;

	/* Add the band address offset, note adjusपंचांगent क्रम word address */
	eq_reg += band * (M98095_COEFS_PER_BAND << 1);

	/* Step through the रेजिस्टरs and coefs */
	क्रम (i = 0; i < M98095_COEFS_PER_BAND; i++) अणु
		snd_soc_component_ग_लिखो(component, eq_reg++, M98095_BYTE1(coefs[i]));
		snd_soc_component_ग_लिखो(component, eq_reg++, M98095_BYTE0(coefs[i]));
	पूर्ण
पूर्ण

/*
 * Load biquad filter coefficient configurations रेजिस्टरs
 */
अटल व्योम m98095_biquad_band(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक dai,
		    अचिन्हित पूर्णांक band, u16 *coefs)
अणु
	अचिन्हित पूर्णांक bq_reg;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(band > 1) ||
	    WARN_ON(dai > 1))
		वापस;

	/* Load the base रेजिस्टर address */
	bq_reg = dai ? M98095_17E_DAI2_BQ_BASE : M98095_174_DAI1_BQ_BASE;

	/* Add the band address offset, note adjusपंचांगent क्रम word address */
	bq_reg += band * (M98095_COEFS_PER_BAND << 1);

	/* Step through the रेजिस्टरs and coefs */
	क्रम (i = 0; i < M98095_COEFS_PER_BAND; i++) अणु
		snd_soc_component_ग_लिखो(component, bq_reg++, M98095_BYTE1(coefs[i]));
		snd_soc_component_ग_लिखो(component, bq_reg++, M98095_BYTE0(coefs[i]));
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर max98095_fltr_mode[] = अणु "Voice", "Music" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(max98095_dai1_filter_mode_क्रमागत,
			    M98095_02E_DAI1_FILTERS, 7,
			    max98095_fltr_mode);
अटल SOC_ENUM_SINGLE_DECL(max98095_dai2_filter_mode_क्रमागत,
			    M98095_038_DAI2_FILTERS, 7,
			    max98095_fltr_mode);

अटल स्थिर अक्षर * स्थिर max98095_exपंचांगic_text[] = अणु "None", "MIC1", "MIC2" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98095_exपंचांगic_क्रमागत,
			    M98095_087_CFG_MIC, 0,
			    max98095_exपंचांगic_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98095_exपंचांगic_mux =
	SOC_DAPM_ENUM("External MIC Mux", max98095_exपंचांगic_क्रमागत);

अटल स्थिर अक्षर * स्थिर max98095_linein_text[] = अणु "INA", "INB" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98095_linein_क्रमागत,
			    M98095_086_CFG_LINE, 6,
			    max98095_linein_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98095_linein_mux =
	SOC_DAPM_ENUM("Linein Input Mux", max98095_linein_क्रमागत);

अटल स्थिर अक्षर * स्थिर max98095_line_mode_text[] = अणु
	"Stereo", "Differential"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98095_linein_mode_क्रमागत,
			    M98095_086_CFG_LINE, 7,
			    max98095_line_mode_text);

अटल SOC_ENUM_SINGLE_DECL(max98095_lineout_mode_क्रमागत,
			    M98095_086_CFG_LINE, 4,
			    max98095_line_mode_text);

अटल स्थिर अक्षर * स्थिर max98095_dai_fltr[] = अणु
	"Off", "Elliptical-HPF-16k", "Butterworth-HPF-16k",
	"Elliptical-HPF-8k", "Butterworth-HPF-8k", "Butterworth-HPF-Fs/240"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(max98095_dai1_dac_filter_क्रमागत,
			    M98095_02E_DAI1_FILTERS, 0,
			    max98095_dai_fltr);
अटल SOC_ENUM_SINGLE_DECL(max98095_dai2_dac_filter_क्रमागत,
			    M98095_038_DAI2_FILTERS, 0,
			    max98095_dai_fltr);
अटल SOC_ENUM_SINGLE_DECL(max98095_dai3_dac_filter_क्रमागत,
			    M98095_042_DAI3_FILTERS, 0,
			    max98095_dai_fltr);

अटल पूर्णांक max98095_mic1pre_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];

	max98095->mic1pre = sel;
	snd_soc_component_update_bits(component, M98095_05F_LVL_MIC1, M98095_MICPRE_MASK,
		(1+sel)<<M98095_MICPRE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_mic1pre_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = max98095->mic1pre;
	वापस 0;
पूर्ण

अटल पूर्णांक max98095_mic2pre_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];

	max98095->mic2pre = sel;
	snd_soc_component_update_bits(component, M98095_060_LVL_MIC2, M98095_MICPRE_MASK,
		(1+sel)<<M98095_MICPRE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_mic2pre_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = max98095->mic2pre;
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(max98095_micboost_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 2000, 0),
	2, 2, TLV_DB_SCALE_ITEM(3000, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98095_mic_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98095_adc_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98095_adcboost_tlv, 0, 600, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98095_hp_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6700, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-4000, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1700, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(-400, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(150, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98095_spk_tlv,
	0, 10, TLV_DB_SCALE_ITEM(-5900, 400, 0),
	11, 18, TLV_DB_SCALE_ITEM(-1700, 200, 0),
	19, 27, TLV_DB_SCALE_ITEM(-200, 100, 0),
	28, 39, TLV_DB_SCALE_ITEM(650, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98095_rcv_lout_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6200, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-3500, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1200, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(100, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(650, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98095_lin_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-600, 300, 0),
	3, 3, TLV_DB_SCALE_ITEM(300, 1100, 0),
	4, 5, TLV_DB_SCALE_ITEM(1400, 600, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new max98095_snd_controls[] = अणु

	SOC_DOUBLE_R_TLV("Headphone Volume", M98095_064_LVL_HP_L,
		M98095_065_LVL_HP_R, 0, 31, 0, max98095_hp_tlv),

	SOC_DOUBLE_R_TLV("Speaker Volume", M98095_067_LVL_SPK_L,
		M98095_068_LVL_SPK_R, 0, 39, 0, max98095_spk_tlv),

	SOC_SINGLE_TLV("Receiver Volume", M98095_066_LVL_RCV,
		0, 31, 0, max98095_rcv_lout_tlv),

	SOC_DOUBLE_R_TLV("Lineout Volume", M98095_062_LVL_LINEOUT1,
		M98095_063_LVL_LINEOUT2, 0, 31, 0, max98095_rcv_lout_tlv),

	SOC_DOUBLE_R("Headphone Switch", M98095_064_LVL_HP_L,
		M98095_065_LVL_HP_R, 7, 1, 1),

	SOC_DOUBLE_R("Speaker Switch", M98095_067_LVL_SPK_L,
		M98095_068_LVL_SPK_R, 7, 1, 1),

	SOC_SINGLE("Receiver Switch", M98095_066_LVL_RCV, 7, 1, 1),

	SOC_DOUBLE_R("Lineout Switch", M98095_062_LVL_LINEOUT1,
		M98095_063_LVL_LINEOUT2, 7, 1, 1),

	SOC_SINGLE_TLV("MIC1 Volume", M98095_05F_LVL_MIC1, 0, 20, 1,
		max98095_mic_tlv),

	SOC_SINGLE_TLV("MIC2 Volume", M98095_060_LVL_MIC2, 0, 20, 1,
		max98095_mic_tlv),

	SOC_SINGLE_EXT_TLV("MIC1 Boost Volume",
			M98095_05F_LVL_MIC1, 5, 2, 0,
			max98095_mic1pre_get, max98095_mic1pre_set,
			max98095_micboost_tlv),
	SOC_SINGLE_EXT_TLV("MIC2 Boost Volume",
			M98095_060_LVL_MIC2, 5, 2, 0,
			max98095_mic2pre_get, max98095_mic2pre_set,
			max98095_micboost_tlv),

	SOC_SINGLE_TLV("Linein Volume", M98095_061_LVL_LINEIN, 0, 5, 1,
		max98095_lin_tlv),

	SOC_SINGLE_TLV("ADCL Volume", M98095_05D_LVL_ADC_L, 0, 15, 1,
		max98095_adc_tlv),
	SOC_SINGLE_TLV("ADCR Volume", M98095_05E_LVL_ADC_R, 0, 15, 1,
		max98095_adc_tlv),

	SOC_SINGLE_TLV("ADCL Boost Volume", M98095_05D_LVL_ADC_L, 4, 3, 0,
		max98095_adcboost_tlv),
	SOC_SINGLE_TLV("ADCR Boost Volume", M98095_05E_LVL_ADC_R, 4, 3, 0,
		max98095_adcboost_tlv),

	SOC_SINGLE("EQ1 Switch", M98095_088_CFG_LEVEL, 0, 1, 0),
	SOC_SINGLE("EQ2 Switch", M98095_088_CFG_LEVEL, 1, 1, 0),

	SOC_SINGLE("Biquad1 Switch", M98095_088_CFG_LEVEL, 2, 1, 0),
	SOC_SINGLE("Biquad2 Switch", M98095_088_CFG_LEVEL, 3, 1, 0),

	SOC_ENUM("DAI1 Filter Mode", max98095_dai1_filter_mode_क्रमागत),
	SOC_ENUM("DAI2 Filter Mode", max98095_dai2_filter_mode_क्रमागत),
	SOC_ENUM("DAI1 DAC Filter", max98095_dai1_dac_filter_क्रमागत),
	SOC_ENUM("DAI2 DAC Filter", max98095_dai2_dac_filter_क्रमागत),
	SOC_ENUM("DAI3 DAC Filter", max98095_dai3_dac_filter_क्रमागत),

	SOC_ENUM("Linein Mode", max98095_linein_mode_क्रमागत),
	SOC_ENUM("Lineout Mode", max98095_lineout_mode_क्रमागत),
पूर्ण;

/* Left speaker mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_left_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_050_MIX_SPK_LEFT, 0, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_050_MIX_SPK_LEFT, 6, 1, 0),
	SOC_DAPM_SINGLE("Mono DAC2 Switch", M98095_050_MIX_SPK_LEFT, 3, 1, 0),
	SOC_DAPM_SINGLE("Mono DAC3 Switch", M98095_050_MIX_SPK_LEFT, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_050_MIX_SPK_LEFT, 4, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_050_MIX_SPK_LEFT, 5, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_050_MIX_SPK_LEFT, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_050_MIX_SPK_LEFT, 2, 1, 0),
पूर्ण;

/* Right speaker mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_right_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_051_MIX_SPK_RIGHT, 6, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_051_MIX_SPK_RIGHT, 0, 1, 0),
	SOC_DAPM_SINGLE("Mono DAC2 Switch", M98095_051_MIX_SPK_RIGHT, 3, 1, 0),
	SOC_DAPM_SINGLE("Mono DAC3 Switch", M98095_051_MIX_SPK_RIGHT, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_051_MIX_SPK_RIGHT, 5, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_051_MIX_SPK_RIGHT, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_051_MIX_SPK_RIGHT, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_051_MIX_SPK_RIGHT, 2, 1, 0),
पूर्ण;

/* Left headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_left_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_04C_MIX_HP_LEFT, 0, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_04C_MIX_HP_LEFT, 5, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_04C_MIX_HP_LEFT, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_04C_MIX_HP_LEFT, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_04C_MIX_HP_LEFT, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_04C_MIX_HP_LEFT, 2, 1, 0),
पूर्ण;

/* Right headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_right_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_04D_MIX_HP_RIGHT, 5, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_04D_MIX_HP_RIGHT, 0, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_04D_MIX_HP_RIGHT, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_04D_MIX_HP_RIGHT, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_04D_MIX_HP_RIGHT, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_04D_MIX_HP_RIGHT, 2, 1, 0),
पूर्ण;

/* Receiver earpiece mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_mono_rcv_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_04F_MIX_RCV, 0, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_04F_MIX_RCV, 5, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_04F_MIX_RCV, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_04F_MIX_RCV, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_04F_MIX_RCV, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_04F_MIX_RCV, 2, 1, 0),
पूर्ण;

/* Left lineout mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_left_lineout_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_053_MIX_LINEOUT1, 5, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_053_MIX_LINEOUT1, 0, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_053_MIX_LINEOUT1, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_053_MIX_LINEOUT1, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_053_MIX_LINEOUT1, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_053_MIX_LINEOUT1, 2, 1, 0),
पूर्ण;

/* Right lineout mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_right_lineout_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", M98095_054_MIX_LINEOUT2, 0, 1, 0),
	SOC_DAPM_SINGLE("Right DAC1 Switch", M98095_054_MIX_LINEOUT2, 5, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_054_MIX_LINEOUT2, 3, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_054_MIX_LINEOUT2, 4, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_054_MIX_LINEOUT2, 1, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_054_MIX_LINEOUT2, 2, 1, 0),
पूर्ण;

/* Left ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_left_ADC_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_04A_MIX_ADC_LEFT, 7, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_04A_MIX_ADC_LEFT, 6, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_04A_MIX_ADC_LEFT, 3, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_04A_MIX_ADC_LEFT, 2, 1, 0),
पूर्ण;

/* Right ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98095_right_ADC_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("MIC1 Switch", M98095_04B_MIX_ADC_RIGHT, 7, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98095_04B_MIX_ADC_RIGHT, 6, 1, 0),
	SOC_DAPM_SINGLE("IN1 Switch", M98095_04B_MIX_ADC_RIGHT, 3, 1, 0),
	SOC_DAPM_SINGLE("IN2 Switch", M98095_04B_MIX_ADC_RIGHT, 2, 1, 0),
पूर्ण;

अटल पूर्णांक max98095_mic_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (w->reg == M98095_05F_LVL_MIC1) अणु
			snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK,
				(1+max98095->mic1pre)<<M98095_MICPRE_SHIFT);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK,
				(1+max98095->mic2pre)<<M98095_MICPRE_SHIFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The line inमाला_दो are stereo inमाला_दो with the left and right
 * channels sharing a common PGA घातer control संकेत.
 */
अटल पूर्णांक max98095_line_pga(काष्ठा snd_soc_dapm_widget *w,
			     पूर्णांक event, u8 channel)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	u8 *state;

	अगर (WARN_ON(!(channel == 1 || channel == 2)))
		वापस -EINVAL;

	state = &max98095->lin_state;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		*state |= channel;
		snd_soc_component_update_bits(component, w->reg,
			(1 << w->shअगरt), (1 << w->shअगरt));
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		*state &= ~channel;
		अगर (*state == 0) अणु
			snd_soc_component_update_bits(component, w->reg,
				(1 << w->shअगरt), 0);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_pga_in1_event(काष्ठा snd_soc_dapm_widget *w,
				   काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	वापस max98095_line_pga(w, event, 1);
पूर्ण

अटल पूर्णांक max98095_pga_in2_event(काष्ठा snd_soc_dapm_widget *w,
				   काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	वापस max98095_line_pga(w, event, 2);
पूर्ण

/*
 * The stereo line out mixer outमाला_दो to two stereo line outs.
 * The 2nd pair has a separate set of enables.
 */
अटल पूर्णांक max98095_lineout_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, w->reg,
			(1 << (w->shअगरt+2)), (1 << (w->shअगरt+2)));
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg,
			(1 << (w->shअगरt+2)), 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget max98095_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_ADC("ADCL", "HiFi Capture", M98095_090_PWR_EN_IN, 0, 0),
	SND_SOC_DAPM_ADC("ADCR", "HiFi Capture", M98095_090_PWR_EN_IN, 1, 0),

	SND_SOC_DAPM_DAC("DACL1", "HiFi Playback",
		M98095_091_PWR_EN_OUT, 0, 0),
	SND_SOC_DAPM_DAC("DACR1", "HiFi Playback",
		M98095_091_PWR_EN_OUT, 1, 0),
	SND_SOC_DAPM_DAC("DACM2", "Aux Playback",
		M98095_091_PWR_EN_OUT, 2, 0),
	SND_SOC_DAPM_DAC("DACM3", "Voice Playback",
		M98095_091_PWR_EN_OUT, 2, 0),

	SND_SOC_DAPM_PGA("HP Left Out", M98095_091_PWR_EN_OUT,
		6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP Right Out", M98095_091_PWR_EN_OUT,
		7, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("SPK Left Out", M98095_091_PWR_EN_OUT,
		4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPK Right Out", M98095_091_PWR_EN_OUT,
		5, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("RCV Mono Out", M98095_091_PWR_EN_OUT,
		3, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_E("LINE Left Out", M98095_092_PWR_EN_OUT,
		0, 0, शून्य, 0, max98095_lineout_event, SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("LINE Right Out", M98095_092_PWR_EN_OUT,
		1, 0, शून्य, 0, max98095_lineout_event, SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MUX("External MIC", SND_SOC_NOPM, 0, 0,
		&max98095_exपंचांगic_mux),

	SND_SOC_DAPM_MUX("Linein Mux", SND_SOC_NOPM, 0, 0,
		&max98095_linein_mux),

	SND_SOC_DAPM_MIXER("Left Headphone Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_left_hp_mixer_controls[0],
		ARRAY_SIZE(max98095_left_hp_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Headphone Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_right_hp_mixer_controls[0],
		ARRAY_SIZE(max98095_right_hp_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Speaker Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_left_speaker_mixer_controls[0],
		ARRAY_SIZE(max98095_left_speaker_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Speaker Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_right_speaker_mixer_controls[0],
		ARRAY_SIZE(max98095_right_speaker_mixer_controls)),

	SND_SOC_DAPM_MIXER("Receiver Mixer", SND_SOC_NOPM, 0, 0,
	  &max98095_mono_rcv_mixer_controls[0],
		ARRAY_SIZE(max98095_mono_rcv_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Lineout Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_left_lineout_mixer_controls[0],
		ARRAY_SIZE(max98095_left_lineout_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Lineout Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_right_lineout_mixer_controls[0],
		ARRAY_SIZE(max98095_right_lineout_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_left_ADC_mixer_controls[0],
		ARRAY_SIZE(max98095_left_ADC_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
		&max98095_right_ADC_mixer_controls[0],
		ARRAY_SIZE(max98095_right_ADC_mixer_controls)),

	SND_SOC_DAPM_PGA_E("MIC1 Input", M98095_05F_LVL_MIC1,
		5, 0, शून्य, 0, max98095_mic_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("MIC2 Input", M98095_060_LVL_MIC2,
		5, 0, शून्य, 0, max98095_mic_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("IN1 Input", M98095_090_PWR_EN_IN,
		7, 0, शून्य, 0, max98095_pga_in1_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("IN2 Input", M98095_090_PWR_EN_IN,
		7, 0, शून्य, 0, max98095_pga_in2_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MICBIAS("MICBIAS1", M98095_090_PWR_EN_IN, 2, 0),
	SND_SOC_DAPM_MICBIAS("MICBIAS2", M98095_090_PWR_EN_IN, 3, 0),

	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("SPKR"),
	SND_SOC_DAPM_OUTPUT("RCV"),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4"),

	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("INA1"),
	SND_SOC_DAPM_INPUT("INA2"),
	SND_SOC_DAPM_INPUT("INB1"),
	SND_SOC_DAPM_INPUT("INB2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98095_audio_map[] = अणु
	/* Left headphone output mixer */
	अणु"Left Headphone Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Left Headphone Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Left Headphone Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Headphone Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Headphone Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Left Headphone Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Right headphone output mixer */
	अणु"Right Headphone Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Right Headphone Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Right Headphone Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Headphone Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Headphone Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Right Headphone Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Left speaker output mixer */
	अणु"Left Speaker Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Left Speaker Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Left Speaker Mixer", "Mono DAC2 Switch", "DACM2"पूर्ण,
	अणु"Left Speaker Mixer", "Mono DAC3 Switch", "DACM3"पूर्ण,
	अणु"Left Speaker Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Speaker Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Speaker Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Left Speaker Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Right speaker output mixer */
	अणु"Right Speaker Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Right Speaker Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Right Speaker Mixer", "Mono DAC2 Switch", "DACM2"पूर्ण,
	अणु"Right Speaker Mixer", "Mono DAC3 Switch", "DACM3"पूर्ण,
	अणु"Right Speaker Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Speaker Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Speaker Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Right Speaker Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Earpiece/Receiver output mixer */
	अणु"Receiver Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Receiver Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Receiver Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Receiver Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Receiver Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Receiver Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Left Lineout output mixer */
	अणु"Left Lineout Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Left Lineout Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Left Lineout Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Lineout Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Lineout Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Left Lineout Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Right lineout output mixer */
	अणु"Right Lineout Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
	अणु"Right Lineout Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
	अणु"Right Lineout Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Lineout Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Lineout Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Right Lineout Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	अणु"HP Left Out", शून्य, "Left Headphone Mixer"पूर्ण,
	अणु"HP Right Out", शून्य, "Right Headphone Mixer"पूर्ण,
	अणु"SPK Left Out", शून्य, "Left Speaker Mixer"पूर्ण,
	अणु"SPK Right Out", शून्य, "Right Speaker Mixer"पूर्ण,
	अणु"RCV Mono Out", शून्य, "Receiver Mixer"पूर्ण,
	अणु"LINE Left Out", शून्य, "Left Lineout Mixer"पूर्ण,
	अणु"LINE Right Out", शून्य, "Right Lineout Mixer"पूर्ण,

	अणु"HPL", शून्य, "HP Left Out"पूर्ण,
	अणु"HPR", शून्य, "HP Right Out"पूर्ण,
	अणु"SPKL", शून्य, "SPK Left Out"पूर्ण,
	अणु"SPKR", शून्य, "SPK Right Out"पूर्ण,
	अणु"RCV", शून्य, "RCV Mono Out"पूर्ण,
	अणु"OUT1", शून्य, "LINE Left Out"पूर्ण,
	अणु"OUT2", शून्य, "LINE Right Out"पूर्ण,
	अणु"OUT3", शून्य, "LINE Left Out"पूर्ण,
	अणु"OUT4", शून्य, "LINE Right Out"पूर्ण,

	/* Left ADC input mixer */
	अणु"Left ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left ADC Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Left ADC Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Right ADC input mixer */
	अणु"Right ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right ADC Mixer", "IN1 Switch", "IN1 Input"पूर्ण,
	अणु"Right ADC Mixer", "IN2 Switch", "IN2 Input"पूर्ण,

	/* Inमाला_दो */
	अणु"ADCL", शून्य, "Left ADC Mixer"पूर्ण,
	अणु"ADCR", शून्य, "Right ADC Mixer"पूर्ण,

	अणु"IN1 Input", शून्य, "INA1"पूर्ण,
	अणु"IN2 Input", शून्य, "INA2"पूर्ण,

	अणु"MIC1 Input", शून्य, "MIC1"पूर्ण,
	अणु"MIC2 Input", शून्य, "MIC2"पूर्ण,
पूर्ण;

/* codec mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा अणु
	u32 rate;
	u8  sr;
पूर्ण rate_table[] = अणु
	अणु8000,  0x01पूर्ण,
	अणु11025, 0x02पूर्ण,
	अणु16000, 0x03पूर्ण,
	अणु22050, 0x04पूर्ण,
	अणु24000, 0x05पूर्ण,
	अणु32000, 0x06पूर्ण,
	अणु44100, 0x07पूर्ण,
	अणु48000, 0x08पूर्ण,
	अणु88200, 0x09पूर्ण,
	अणु96000, 0x0Aपूर्ण,
पूर्ण;

अटल पूर्णांक rate_value(पूर्णांक rate, u8 *value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rate_table); i++) अणु
		अगर (rate_table[i].rate >= rate) अणु
			*value = rate_table[i].sr;
			वापस 0;
		पूर्ण
	पूर्ण
	*value = rate_table[0].sr;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98095_dai1_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	अचिन्हित दीर्घ दीर्घ ni;
	अचिन्हित पूर्णांक rate;
	u8 regval;

	cdata = &max98095->dai[0];

	rate = params_rate(params);

	चयन (params_width(params)) अणु
	हाल 16:
		snd_soc_component_update_bits(component, M98095_02A_DAI1_FORMAT,
			M98095_DAI_WS, 0);
		अवरोध;
	हाल 24:
		snd_soc_component_update_bits(component, M98095_02A_DAI1_FORMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate_value(rate, &regval))
		वापस -EINVAL;

	snd_soc_component_update_bits(component, M98095_027_DAI1_CLKMODE,
		M98095_CLKMODE_MASK, regval);
	cdata->rate = rate;

	/* Configure NI when operating as master */
	अगर (snd_soc_component_पढ़ो(component, M98095_02A_DAI1_FORMAT) & M98095_DAI_MAS) अणु
		अगर (max98095->sysclk == 0) अणु
			dev_err(component->dev, "Invalid system clock frequency\n");
			वापस -EINVAL;
		पूर्ण
		ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
				* (अचिन्हित दीर्घ दीर्घ पूर्णांक)rate;
		करो_भाग(ni, (अचिन्हित दीर्घ दीर्घ पूर्णांक)max98095->sysclk);
		snd_soc_component_ग_लिखो(component, M98095_028_DAI1_CLKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_ग_लिखो(component, M98095_029_DAI1_CLKCFG_LO,
			ni & 0xFF);
	पूर्ण

	/* Update sample rate mode */
	अगर (rate < 50000)
		snd_soc_component_update_bits(component, M98095_02E_DAI1_FILTERS,
			M98095_DAI_DHF, 0);
	अन्यथा
		snd_soc_component_update_bits(component, M98095_02E_DAI1_FILTERS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai2_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	अचिन्हित दीर्घ दीर्घ ni;
	अचिन्हित पूर्णांक rate;
	u8 regval;

	cdata = &max98095->dai[1];

	rate = params_rate(params);

	चयन (params_width(params)) अणु
	हाल 16:
		snd_soc_component_update_bits(component, M98095_034_DAI2_FORMAT,
			M98095_DAI_WS, 0);
		अवरोध;
	हाल 24:
		snd_soc_component_update_bits(component, M98095_034_DAI2_FORMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate_value(rate, &regval))
		वापस -EINVAL;

	snd_soc_component_update_bits(component, M98095_031_DAI2_CLKMODE,
		M98095_CLKMODE_MASK, regval);
	cdata->rate = rate;

	/* Configure NI when operating as master */
	अगर (snd_soc_component_पढ़ो(component, M98095_034_DAI2_FORMAT) & M98095_DAI_MAS) अणु
		अगर (max98095->sysclk == 0) अणु
			dev_err(component->dev, "Invalid system clock frequency\n");
			वापस -EINVAL;
		पूर्ण
		ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
				* (अचिन्हित दीर्घ दीर्घ पूर्णांक)rate;
		करो_भाग(ni, (अचिन्हित दीर्घ दीर्घ पूर्णांक)max98095->sysclk);
		snd_soc_component_ग_लिखो(component, M98095_032_DAI2_CLKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_ग_लिखो(component, M98095_033_DAI2_CLKCFG_LO,
			ni & 0xFF);
	पूर्ण

	/* Update sample rate mode */
	अगर (rate < 50000)
		snd_soc_component_update_bits(component, M98095_038_DAI2_FILTERS,
			M98095_DAI_DHF, 0);
	अन्यथा
		snd_soc_component_update_bits(component, M98095_038_DAI2_FILTERS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai3_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	अचिन्हित दीर्घ दीर्घ ni;
	अचिन्हित पूर्णांक rate;
	u8 regval;

	cdata = &max98095->dai[2];

	rate = params_rate(params);

	चयन (params_width(params)) अणु
	हाल 16:
		snd_soc_component_update_bits(component, M98095_03E_DAI3_FORMAT,
			M98095_DAI_WS, 0);
		अवरोध;
	हाल 24:
		snd_soc_component_update_bits(component, M98095_03E_DAI3_FORMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate_value(rate, &regval))
		वापस -EINVAL;

	snd_soc_component_update_bits(component, M98095_03B_DAI3_CLKMODE,
		M98095_CLKMODE_MASK, regval);
	cdata->rate = rate;

	/* Configure NI when operating as master */
	अगर (snd_soc_component_पढ़ो(component, M98095_03E_DAI3_FORMAT) & M98095_DAI_MAS) अणु
		अगर (max98095->sysclk == 0) अणु
			dev_err(component->dev, "Invalid system clock frequency\n");
			वापस -EINVAL;
		पूर्ण
		ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
				* (अचिन्हित दीर्घ दीर्घ पूर्णांक)rate;
		करो_भाग(ni, (अचिन्हित दीर्घ दीर्घ पूर्णांक)max98095->sysclk);
		snd_soc_component_ग_लिखो(component, M98095_03C_DAI3_CLKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_ग_लिखो(component, M98095_03D_DAI3_CLKCFG_LO,
			ni & 0xFF);
	पूर्ण

	/* Update sample rate mode */
	अगर (rate < 50000)
		snd_soc_component_update_bits(component, M98095_042_DAI3_FILTERS,
			M98095_DAI_DHF, 0);
	अन्यथा
		snd_soc_component_update_bits(component, M98095_042_DAI3_FILTERS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				   पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	/* Requested घड़ी frequency is alपढ़ोy setup */
	अगर (freq == max98095->sysclk)
		वापस 0;

	अगर (!IS_ERR(max98095->mclk)) अणु
		freq = clk_round_rate(max98095->mclk, freq);
		clk_set_rate(max98095->mclk, freq);
	पूर्ण

	/* Setup घड़ीs क्रम slave mode, and using the PLL
	 * PSCLK = 0x01 (when master clk is 10MHz to 20MHz)
	 *         0x02 (when master clk is 20MHz to 40MHz)..
	 *         0x03 (when master clk is 40MHz to 60MHz)..
	 */
	अगर ((freq >= 10000000) && (freq < 20000000)) अणु
		snd_soc_component_ग_लिखो(component, M98095_026_SYS_CLK, 0x10);
	पूर्ण अन्यथा अगर ((freq >= 20000000) && (freq < 40000000)) अणु
		snd_soc_component_ग_लिखो(component, M98095_026_SYS_CLK, 0x20);
	पूर्ण अन्यथा अगर ((freq >= 40000000) && (freq < 60000000)) अणु
		snd_soc_component_ग_लिखो(component, M98095_026_SYS_CLK, 0x30);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Invalid master clock frequency\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "Clock source is %d at %uHz\n", clk_id, freq);

	max98095->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai1_set_fmt(काष्ठा snd_soc_dai *codec_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	u8 regval = 0;

	cdata = &max98095->dai[0];

	अगर (fmt != cdata->fmt) अणु
		cdata->fmt = fmt;

		चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
			/* Slave mode PLL */
			snd_soc_component_ग_लिखो(component, M98095_028_DAI1_CLKCFG_HI,
				0x80);
			snd_soc_component_ग_लिखो(component, M98095_029_DAI1_CLKCFG_LO,
				0x00);
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
			/* Set to master mode */
			regval |= M98095_DAI_MAS;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBS_CFM:
		हाल SND_SOC_DAIFMT_CBM_CFS:
		शेष:
			dev_err(component->dev, "Clock mode unsupported");
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_I2S:
			regval |= M98095_DAI_DLY;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			regval |= M98095_DAI_WCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			regval |= M98095_DAI_BCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			regval |= M98095_DAI_BCI|M98095_DAI_WCI;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, M98095_02A_DAI1_FORMAT,
			M98095_DAI_MAS | M98095_DAI_DLY | M98095_DAI_BCI |
			M98095_DAI_WCI, regval);

		snd_soc_component_ग_लिखो(component, M98095_02B_DAI1_CLOCK, M98095_DAI_BSEL64);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai2_set_fmt(काष्ठा snd_soc_dai *codec_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	u8 regval = 0;

	cdata = &max98095->dai[1];

	अगर (fmt != cdata->fmt) अणु
		cdata->fmt = fmt;

		चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
			/* Slave mode PLL */
			snd_soc_component_ग_लिखो(component, M98095_032_DAI2_CLKCFG_HI,
				0x80);
			snd_soc_component_ग_लिखो(component, M98095_033_DAI2_CLKCFG_LO,
				0x00);
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
			/* Set to master mode */
			regval |= M98095_DAI_MAS;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBS_CFM:
		हाल SND_SOC_DAIFMT_CBM_CFS:
		शेष:
			dev_err(component->dev, "Clock mode unsupported");
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_I2S:
			regval |= M98095_DAI_DLY;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			regval |= M98095_DAI_WCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			regval |= M98095_DAI_BCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			regval |= M98095_DAI_BCI|M98095_DAI_WCI;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, M98095_034_DAI2_FORMAT,
			M98095_DAI_MAS | M98095_DAI_DLY | M98095_DAI_BCI |
			M98095_DAI_WCI, regval);

		snd_soc_component_ग_लिखो(component, M98095_035_DAI2_CLOCK,
			M98095_DAI_BSEL64);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_dai3_set_fmt(काष्ठा snd_soc_dai *codec_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	u8 regval = 0;

	cdata = &max98095->dai[2];

	अगर (fmt != cdata->fmt) अणु
		cdata->fmt = fmt;

		चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
			/* Slave mode PLL */
			snd_soc_component_ग_लिखो(component, M98095_03C_DAI3_CLKCFG_HI,
				0x80);
			snd_soc_component_ग_लिखो(component, M98095_03D_DAI3_CLKCFG_LO,
				0x00);
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
			/* Set to master mode */
			regval |= M98095_DAI_MAS;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBS_CFM:
		हाल SND_SOC_DAIFMT_CBM_CFS:
		शेष:
			dev_err(component->dev, "Clock mode unsupported");
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_I2S:
			regval |= M98095_DAI_DLY;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			regval |= M98095_DAI_WCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			regval |= M98095_DAI_BCI;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			regval |= M98095_DAI_BCI|M98095_DAI_WCI;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, M98095_03E_DAI3_FORMAT,
			M98095_DAI_MAS | M98095_DAI_DLY | M98095_DAI_BCI |
			M98095_DAI_WCI, regval);

		snd_soc_component_ग_लिखो(component, M98095_03F_DAI3_CLOCK,
			M98095_DAI_BSEL64);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/*
		 * SND_SOC_BIAS_PREPARE is called जबतक preparing क्रम a
		 * transition to ON or away from ON. If current bias_level
		 * is SND_SOC_BIAS_ON, then it is preparing क्रम a transition
		 * away from ON. Disable the घड़ी in that हाल, otherwise
		 * enable it.
		 */
		अगर (IS_ERR(max98095->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(max98095->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(max98095->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(max98095->regmap);

			अगर (ret != 0) अणु
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		snd_soc_component_update_bits(component, M98095_090_PWR_EN_IN,
				M98095_MBEN, M98095_MBEN);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, M98095_090_PWR_EN_IN,
				M98095_MBEN, 0);
		regcache_mark_dirty(max98095->regmap);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MAX98095_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा MAX98095_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98095_dai1_ops = अणु
	.set_sysclk = max98095_dai_set_sysclk,
	.set_fmt = max98095_dai1_set_fmt,
	.hw_params = max98095_dai1_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops max98095_dai2_ops = अणु
	.set_sysclk = max98095_dai_set_sysclk,
	.set_fmt = max98095_dai2_set_fmt,
	.hw_params = max98095_dai2_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops max98095_dai3_ops = अणु
	.set_sysclk = max98095_dai_set_sysclk,
	.set_fmt = max98095_dai3_set_fmt,
	.hw_params = max98095_dai3_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98095_dai[] = अणु
अणु
	.name = "HiFi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX98095_RATES,
		.क्रमmats = MAX98095_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX98095_RATES,
		.क्रमmats = MAX98095_FORMATS,
	पूर्ण,
	 .ops = &max98095_dai1_ops,
पूर्ण,
अणु
	.name = "Aux",
	.playback = अणु
		.stream_name = "Aux Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = MAX98095_RATES,
		.क्रमmats = MAX98095_FORMATS,
	पूर्ण,
	.ops = &max98095_dai2_ops,
पूर्ण,
अणु
	.name = "Voice",
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = MAX98095_RATES,
		.क्रमmats = MAX98095_FORMATS,
	पूर्ण,
	.ops = &max98095_dai3_ops,
पूर्ण

पूर्ण;

अटल पूर्णांक max98095_get_eq_channel(स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, "EQ1 Mode") == 0)
		वापस 0;
	अगर (म_भेद(name, "EQ2 Mode") == 0)
		वापस 1;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98095_put_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_pdata *pdata = max98095->pdata;
	पूर्णांक channel = max98095_get_eq_channel(kcontrol->id.name);
	काष्ठा max98095_cdata *cdata;
	अचिन्हित पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	काष्ठा max98095_eq_cfg *coef_set;
	पूर्णांक fs, best, best_val, i;
	पूर्णांक regmask, regsave;

	अगर (WARN_ON(channel > 1))
		वापस -EINVAL;

	अगर (!pdata || !max98095->eq_textcnt)
		वापस 0;

	अगर (sel >= pdata->eq_cfgcnt)
		वापस -EINVAL;

	cdata = &max98095->dai[channel];
	cdata->eq_sel = sel;
	fs = cdata->rate;

	/* Find the selected configuration with nearest sample rate */
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < pdata->eq_cfgcnt; i++) अणु
		अगर (म_भेद(pdata->eq_cfg[i].name, max98095->eq_texts[sel]) == 0 &&
			असल(pdata->eq_cfg[i].rate - fs) < best_val) अणु
			best = i;
			best_val = असल(pdata->eq_cfg[i].rate - fs);
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
		pdata->eq_cfg[best].name,
		pdata->eq_cfg[best].rate, fs);

	coef_set = &pdata->eq_cfg[best];

	regmask = (channel == 0) ? M98095_EQ1EN : M98095_EQ2EN;

	/* Disable filter जबतक configuring, and save current on/off state */
	regsave = snd_soc_component_पढ़ो(component, M98095_088_CFG_LEVEL);
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, 0);

	mutex_lock(&max98095->lock);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, M98095_SEG);
	m98095_eq_band(component, channel, 0, coef_set->band1);
	m98095_eq_band(component, channel, 1, coef_set->band2);
	m98095_eq_band(component, channel, 2, coef_set->band3);
	m98095_eq_band(component, channel, 3, coef_set->band4);
	m98095_eq_band(component, channel, 4, coef_set->band5);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, 0);
	mutex_unlock(&max98095->lock);

	/* Restore the original on/off state */
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, regsave);
	वापस 0;
पूर्ण

अटल पूर्णांक max98095_get_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	पूर्णांक channel = max98095_get_eq_channel(kcontrol->id.name);
	काष्ठा max98095_cdata *cdata;

	cdata = &max98095->dai[channel];
	ucontrol->value.क्रमागतerated.item[0] = cdata->eq_sel;

	वापस 0;
पूर्ण

अटल व्योम max98095_handle_eq_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_pdata *pdata = max98095->pdata;
	काष्ठा max98095_eq_cfg *cfg;
	अचिन्हित पूर्णांक cfgcnt;
	पूर्णांक i, j;
	स्थिर अक्षर **t;
	पूर्णांक ret;

	काष्ठा snd_kcontrol_new controls[] = अणु
		SOC_ENUM_EXT("EQ1 Mode",
			max98095->eq_क्रमागत,
			max98095_get_eq_क्रमागत,
			max98095_put_eq_क्रमागत),
		SOC_ENUM_EXT("EQ2 Mode",
			max98095->eq_क्रमागत,
			max98095_get_eq_क्रमागत,
			max98095_put_eq_क्रमागत),
	पूर्ण;

	cfg = pdata->eq_cfg;
	cfgcnt = pdata->eq_cfgcnt;

	/* Setup an array of texts क्रम the equalizer क्रमागत.
	 * This is based on Mark Brown's equalizer driver code.
	 */
	max98095->eq_textcnt = 0;
	max98095->eq_texts = शून्य;
	क्रम (i = 0; i < cfgcnt; i++) अणु
		क्रम (j = 0; j < max98095->eq_textcnt; j++) अणु
			अगर (म_भेद(cfg[i].name, max98095->eq_texts[j]) == 0)
				अवरोध;
		पूर्ण

		अगर (j != max98095->eq_textcnt)
			जारी;

		/* Expand the array */
		t = kपुनः_स्मृति(max98095->eq_texts,
			     माप(अक्षर *) * (max98095->eq_textcnt + 1),
			     GFP_KERNEL);
		अगर (t == शून्य)
			जारी;

		/* Store the new entry */
		t[max98095->eq_textcnt] = cfg[i].name;
		max98095->eq_textcnt++;
		max98095->eq_texts = t;
	पूर्ण

	/* Now poपूर्णांक the soc_क्रमागत to .texts array items */
	max98095->eq_क्रमागत.texts = max98095->eq_texts;
	max98095->eq_क्रमागत.items = max98095->eq_textcnt;

	ret = snd_soc_add_component_controls(component, controls, ARRAY_SIZE(controls));
	अगर (ret != 0)
		dev_err(component->dev, "Failed to add EQ control: %d\n", ret);
पूर्ण

अटल स्थिर अक्षर *bq_mode_name[] = अणु"Biquad1 Mode", "Biquad2 Mode"पूर्ण;

अटल पूर्णांक max98095_get_bq_channel(काष्ठा snd_soc_component *component,
				   स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	ret = match_string(bq_mode_name, ARRAY_SIZE(bq_mode_name), name);
	अगर (ret < 0)
		dev_err(component->dev, "Bad biquad channel name '%s'\n", name);
	वापस ret;
पूर्ण

अटल पूर्णांक max98095_put_bq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_pdata *pdata = max98095->pdata;
	पूर्णांक channel = max98095_get_bq_channel(component, kcontrol->id.name);
	काष्ठा max98095_cdata *cdata;
	अचिन्हित पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	काष्ठा max98095_biquad_cfg *coef_set;
	पूर्णांक fs, best, best_val, i;
	पूर्णांक regmask, regsave;

	अगर (channel < 0)
		वापस channel;

	अगर (!pdata || !max98095->bq_textcnt)
		वापस 0;

	अगर (sel >= pdata->bq_cfgcnt)
		वापस -EINVAL;

	cdata = &max98095->dai[channel];
	cdata->bq_sel = sel;
	fs = cdata->rate;

	/* Find the selected configuration with nearest sample rate */
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < pdata->bq_cfgcnt; i++) अणु
		अगर (म_भेद(pdata->bq_cfg[i].name, max98095->bq_texts[sel]) == 0 &&
			असल(pdata->bq_cfg[i].rate - fs) < best_val) अणु
			best = i;
			best_val = असल(pdata->bq_cfg[i].rate - fs);
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
		pdata->bq_cfg[best].name,
		pdata->bq_cfg[best].rate, fs);

	coef_set = &pdata->bq_cfg[best];

	regmask = (channel == 0) ? M98095_BQ1EN : M98095_BQ2EN;

	/* Disable filter जबतक configuring, and save current on/off state */
	regsave = snd_soc_component_पढ़ो(component, M98095_088_CFG_LEVEL);
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, 0);

	mutex_lock(&max98095->lock);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, M98095_SEG);
	m98095_biquad_band(component, channel, 0, coef_set->band1);
	m98095_biquad_band(component, channel, 1, coef_set->band2);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, 0);
	mutex_unlock(&max98095->lock);

	/* Restore the original on/off state */
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, regsave);
	वापस 0;
पूर्ण

अटल पूर्णांक max98095_get_bq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	पूर्णांक channel = max98095_get_bq_channel(component, kcontrol->id.name);
	काष्ठा max98095_cdata *cdata;

	अगर (channel < 0)
		वापस channel;

	cdata = &max98095->dai[channel];
	ucontrol->value.क्रमागतerated.item[0] = cdata->bq_sel;

	वापस 0;
पूर्ण

अटल व्योम max98095_handle_bq_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_pdata *pdata = max98095->pdata;
	काष्ठा max98095_biquad_cfg *cfg;
	अचिन्हित पूर्णांक cfgcnt;
	पूर्णांक i, j;
	स्थिर अक्षर **t;
	पूर्णांक ret;

	काष्ठा snd_kcontrol_new controls[] = अणु
		SOC_ENUM_EXT((अक्षर *)bq_mode_name[0],
			max98095->bq_क्रमागत,
			max98095_get_bq_क्रमागत,
			max98095_put_bq_क्रमागत),
		SOC_ENUM_EXT((अक्षर *)bq_mode_name[1],
			max98095->bq_क्रमागत,
			max98095_get_bq_क्रमागत,
			max98095_put_bq_क्रमागत),
	पूर्ण;
	BUILD_BUG_ON(ARRAY_SIZE(controls) != ARRAY_SIZE(bq_mode_name));

	cfg = pdata->bq_cfg;
	cfgcnt = pdata->bq_cfgcnt;

	/* Setup an array of texts क्रम the biquad क्रमागत.
	 * This is based on Mark Brown's equalizer driver code.
	 */
	max98095->bq_textcnt = 0;
	max98095->bq_texts = शून्य;
	क्रम (i = 0; i < cfgcnt; i++) अणु
		क्रम (j = 0; j < max98095->bq_textcnt; j++) अणु
			अगर (म_भेद(cfg[i].name, max98095->bq_texts[j]) == 0)
				अवरोध;
		पूर्ण

		अगर (j != max98095->bq_textcnt)
			जारी;

		/* Expand the array */
		t = kपुनः_स्मृति(max98095->bq_texts,
			     माप(अक्षर *) * (max98095->bq_textcnt + 1),
			     GFP_KERNEL);
		अगर (t == शून्य)
			जारी;

		/* Store the new entry */
		t[max98095->bq_textcnt] = cfg[i].name;
		max98095->bq_textcnt++;
		max98095->bq_texts = t;
	पूर्ण

	/* Now poपूर्णांक the soc_क्रमागत to .texts array items */
	max98095->bq_क्रमागत.texts = max98095->bq_texts;
	max98095->bq_क्रमागत.items = max98095->bq_textcnt;

	ret = snd_soc_add_component_controls(component, controls, ARRAY_SIZE(controls));
	अगर (ret != 0)
		dev_err(component->dev, "Failed to add Biquad control: %d\n", ret);
पूर्ण

अटल व्योम max98095_handle_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_pdata *pdata = max98095->pdata;
	u8 regval = 0;

	अगर (!pdata) अणु
		dev_dbg(component->dev, "No platform data\n");
		वापस;
	पूर्ण

	/* Configure mic क्रम analog/digital mic mode */
	अगर (pdata->digmic_left_mode)
		regval |= M98095_DIGMIC_L;

	अगर (pdata->digmic_right_mode)
		regval |= M98095_DIGMIC_R;

	snd_soc_component_ग_लिखो(component, M98095_087_CFG_MIC, regval);

	/* Configure equalizers */
	अगर (pdata->eq_cfgcnt)
		max98095_handle_eq_pdata(component);

	/* Configure bi-quad filters */
	अगर (pdata->bq_cfgcnt)
		max98095_handle_bq_pdata(component);
पूर्ण

अटल irqवापस_t max98095_report_jack(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;
	पूर्णांक hp_report = 0;
	पूर्णांक mic_report = 0;

	/* Read the Jack Status Register */
	value = snd_soc_component_पढ़ो(component, M98095_007_JACK_AUTO_STS);

	/* If dकरोne is not set, then detection isn't finished yet */
	अगर ((value & M98095_DDONE) == 0)
		वापस IRQ_NONE;

	/* अगर hp, check its bit, and अगर set, clear it */
	अगर ((value & M98095_HP_IN || value & M98095_LO_IN) &&
		max98095->headphone_jack)
		hp_report |= SND_JACK_HEADPHONE;

	/* अगर mic, check its bit, and अगर set, clear it */
	अगर ((value & M98095_MIC_IN) && max98095->mic_jack)
		mic_report |= SND_JACK_MICROPHONE;

	अगर (max98095->headphone_jack == max98095->mic_jack) अणु
		snd_soc_jack_report(max98095->headphone_jack,
					hp_report | mic_report,
					SND_JACK_HEADSET);
	पूर्ण अन्यथा अणु
		अगर (max98095->headphone_jack)
			snd_soc_jack_report(max98095->headphone_jack,
					hp_report, SND_JACK_HEADPHONE);
		अगर (max98095->mic_jack)
			snd_soc_jack_report(max98095->mic_jack,
					mic_report, SND_JACK_MICROPHONE);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max98095_jack_detect_enable(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;
	पूर्णांक detect_enable = M98095_JDEN;
	अचिन्हित पूर्णांक slew = M98095_DEFAULT_SLEW_DELAY;

	अगर (max98095->pdata->jack_detect_pin5en)
		detect_enable |= M98095_PIN5EN;

	अगर (max98095->pdata->jack_detect_delay)
		slew = max98095->pdata->jack_detect_delay;

	ret = snd_soc_component_ग_लिखो(component, M98095_08E_JACK_DC_SLEW, slew);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to cfg auto detect %d\n", ret);
		वापस ret;
	पूर्ण

	/* configure स्वतः detection to be enabled */
	ret = snd_soc_component_ग_लिखो(component, M98095_089_JACK_DET_AUTO, detect_enable);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to cfg auto detect %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max98095_jack_detect_disable(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	/* configure स्वतः detection to be disabled */
	ret = snd_soc_component_ग_लिखो(component, M98095_089_JACK_DET_AUTO, 0x0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to cfg auto detect %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक max98095_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hp_jack, काष्ठा snd_soc_jack *mic_jack)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *client = to_i2c_client(component->dev);
	पूर्णांक ret = 0;

	max98095->headphone_jack = hp_jack;
	max98095->mic_jack = mic_jack;

	/* only progress अगर we have at least 1 jack poपूर्णांकer */
	अगर (!hp_jack && !mic_jack)
		वापस -EINVAL;

	max98095_jack_detect_enable(component);

	/* enable पूर्णांकerrupts क्रम headphone jack detection */
	ret = snd_soc_component_update_bits(component, M98095_013_JACK_INT_EN,
		M98095_IDDONE, M98095_IDDONE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to cfg jack irqs %d\n", ret);
		वापस ret;
	पूर्ण

	max98095_report_jack(client->irq, component);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max98095_jack_detect);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक max98095_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	अगर (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disable(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक max98095_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *client = to_i2c_client(component->dev);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	अगर (max98095->headphone_jack || max98095->mic_jack) अणु
		max98095_jack_detect_enable(component);
		max98095_report_jack(client->irq, component);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा max98095_suspend शून्य
#घोषणा max98095_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक max98095_reset(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i, ret;

	/* Gracefully reset the DSP core and the codec hardware
	 * in a proper sequence */
	ret = snd_soc_component_ग_लिखो(component, M98095_00F_HOST_CFG, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to reset DSP: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_ग_लिखो(component, M98095_097_PWR_SYS, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to reset component: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset to hardware शेष क्रम रेजिस्टरs, as there is not
	 * a soft reset hardware control रेजिस्टर */
	क्रम (i = M98095_010_HOST_INT_CFG; i < M98095_REG_MAX_CACHED; i++) अणु
		ret = snd_soc_component_ग_लिखो(component, i, snd_soc_component_पढ़ो(component, i));
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to reset: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max98095_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा max98095_cdata *cdata;
	काष्ठा i2c_client *client;
	पूर्णांक ret = 0;

	max98095->mclk = devm_clk_get(component->dev, "mclk");
	अगर (PTR_ERR(max98095->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	/* reset the codec, the DSP core, and disable all पूर्णांकerrupts */
	max98095_reset(component);

	client = to_i2c_client(component->dev);

	/* initialize निजी data */

	max98095->sysclk = (अचिन्हित)-1;
	max98095->eq_textcnt = 0;
	max98095->bq_textcnt = 0;

	cdata = &max98095->dai[0];
	cdata->rate = (अचिन्हित)-1;
	cdata->fmt  = (अचिन्हित)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	cdata = &max98095->dai[1];
	cdata->rate = (अचिन्हित)-1;
	cdata->fmt  = (अचिन्हित)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	cdata = &max98095->dai[2];
	cdata->rate = (अचिन्हित)-1;
	cdata->fmt  = (अचिन्हित)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	max98095->lin_state = 0;
	max98095->mic1pre = 0;
	max98095->mic2pre = 0;

	अगर (client->irq) अणु
		/* रेजिस्टर an audio पूर्णांकerrupt */
		ret = request_thपढ़ोed_irq(client->irq, शून्य,
			max98095_report_jack,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT, "max98095", component);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to request IRQ: %d\n", ret);
			जाओ err_access;
		पूर्ण
	पूर्ण

	ret = snd_soc_component_पढ़ो(component, M98095_0FF_REV_ID);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failure reading hardware revision: %d\n",
			ret);
		जाओ err_irq;
	पूर्ण
	dev_info(component->dev, "Hardware revision: %c\n", ret - 0x40 + 'A');

	snd_soc_component_ग_लिखो(component, M98095_097_PWR_SYS, M98095_PWRSV);

	snd_soc_component_ग_लिखो(component, M98095_048_MIX_DAC_LR,
		M98095_DAI1L_TO_DACL|M98095_DAI1R_TO_DACR);

	snd_soc_component_ग_लिखो(component, M98095_049_MIX_DAC_M,
		M98095_DAI2M_TO_DACM|M98095_DAI3M_TO_DACM);

	snd_soc_component_ग_लिखो(component, M98095_092_PWR_EN_OUT, M98095_SPK_SPREADSPECTRUM);
	snd_soc_component_ग_लिखो(component, M98095_045_CFG_DSP, M98095_DSPNORMAL);
	snd_soc_component_ग_लिखो(component, M98095_04E_CFG_HP, M98095_HPNORMAL);

	snd_soc_component_ग_लिखो(component, M98095_02C_DAI1_IOCFG,
		M98095_S1NORMAL|M98095_SDATA);

	snd_soc_component_ग_लिखो(component, M98095_036_DAI2_IOCFG,
		M98095_S2NORMAL|M98095_SDATA);

	snd_soc_component_ग_लिखो(component, M98095_040_DAI3_IOCFG,
		M98095_S3NORMAL|M98095_SDATA);

	max98095_handle_pdata(component);

	/* take the codec out of the shut करोwn */
	snd_soc_component_update_bits(component, M98095_097_PWR_SYS, M98095_SHDNRUN,
		M98095_SHDNRUN);

	वापस 0;

err_irq:
	अगर (client->irq)
		मुक्त_irq(client->irq, component);
err_access:
	वापस ret;
पूर्ण

अटल व्योम max98095_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *client = to_i2c_client(component->dev);

	अगर (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disable(component);

	अगर (client->irq)
		मुक्त_irq(client->irq, component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max98095 = अणु
	.probe			= max98095_probe,
	.हटाओ			= max98095_हटाओ,
	.suspend		= max98095_suspend,
	.resume			= max98095_resume,
	.set_bias_level		= max98095_set_bias_level,
	.controls		= max98095_snd_controls,
	.num_controls		= ARRAY_SIZE(max98095_snd_controls),
	.dapm_widमाला_लो		= max98095_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98095_dapm_widमाला_लो),
	.dapm_routes		= max98095_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98095_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक max98095_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max98095_priv *max98095;
	पूर्णांक ret;

	max98095 = devm_kzalloc(&i2c->dev, माप(काष्ठा max98095_priv),
				GFP_KERNEL);
	अगर (max98095 == शून्य)
		वापस -ENOMEM;

	mutex_init(&max98095->lock);

	max98095->regmap = devm_regmap_init_i2c(i2c, &max98095_regmap);
	अगर (IS_ERR(max98095->regmap)) अणु
		ret = PTR_ERR(max98095->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	max98095->devtype = id->driver_data;
	i2c_set_clientdata(i2c, max98095);
	max98095->pdata = i2c->dev.platक्रमm_data;

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_max98095,
				     max98095_dai, ARRAY_SIZE(max98095_dai));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98095_i2c_id[] = अणु
	अणु "max98095", MAX98095 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98095_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98095_of_match[] = अणु
	अणु .compatible = "maxim,max98095", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98095_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98095_i2c_driver = अणु
	.driver = अणु
		.name = "max98095",
		.of_match_table = of_match_ptr(max98095_of_match),
	पूर्ण,
	.probe  = max98095_i2c_probe,
	.id_table = max98095_i2c_id,
पूर्ण;

module_i2c_driver(max98095_i2c_driver);

MODULE_DESCRIPTION("ALSA SoC MAX98095 driver");
MODULE_AUTHOR("Peter Hsiang");
MODULE_LICENSE("GPL");
