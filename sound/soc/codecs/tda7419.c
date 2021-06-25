<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TDA7419 audio processor driver
 *
 * Copyright 2018 Konsulko Group
 *
 * Author: Matt Porter <mporter@konsulko.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा TDA7419_MAIN_SRC_REG		0x00
#घोषणा TDA7419_LOUDNESS_REG		0x01
#घोषणा TDA7419_MUTE_CLK_REG		0x02
#घोषणा TDA7419_VOLUME_REG		0x03
#घोषणा TDA7419_TREBLE_REG		0x04
#घोषणा TDA7419_MIDDLE_REG		0x05
#घोषणा TDA7419_BASS_REG		0x06
#घोषणा TDA7419_SECOND_SRC_REG		0x07
#घोषणा TDA7419_SUB_MID_BASS_REG	0x08
#घोषणा TDA7419_MIXING_GAIN_REG		0x09
#घोषणा TDA7419_ATTENUATOR_LF_REG	0x0a
#घोषणा TDA7419_ATTENUATOR_RF_REG	0x0b
#घोषणा TDA7419_ATTENUATOR_LR_REG	0x0c
#घोषणा TDA7419_ATTENUATOR_RR_REG	0x0d
#घोषणा TDA7419_MIXING_LEVEL_REG	0x0e
#घोषणा TDA7419_ATTENUATOR_SUB_REG	0x0f
#घोषणा TDA7419_SA_CLK_AC_REG		0x10
#घोषणा TDA7419_TESTING_REG		0x11

#घोषणा TDA7419_MAIN_SRC_SEL		0
#घोषणा TDA7419_MAIN_SRC_GAIN		3
#घोषणा TDA7419_MAIN_SRC_AUTOZERO	7

#घोषणा TDA7419_LOUDNESS_ATTEN		0
#घोषणा TDA7419_LOUDNESS_CENTER_FREQ	4
#घोषणा TDA7419_LOUDNESS_BOOST		6
#घोषणा TDA7419_LOUDNESS_SOFT_STEP	7

#घोषणा TDA7419_VOLUME_SOFT_STEP	7

#घोषणा TDA7419_SOFT_MUTE		0
#घोषणा TDA7419_MUTE_INFLUENCE		1
#घोषणा TDA7419_SOFT_MUTE_TIME		2
#घोषणा TDA7419_SOFT_STEP_TIME		4
#घोषणा TDA7419_CLK_FAST_MODE		7

#घोषणा TDA7419_TREBLE_CENTER_FREQ	5
#घोषणा TDA7419_REF_OUT_SELECT		7

#घोषणा TDA7419_MIDDLE_Q_FACTOR		5
#घोषणा TDA7419_MIDDLE_SOFT_STEP	7

#घोषणा TDA7419_BASS_Q_FACTOR		5
#घोषणा TDA7419_BASS_SOFT_STEP		7

#घोषणा TDA7419_SECOND_SRC_SEL		0
#घोषणा TDA7419_SECOND_SRC_GAIN		3
#घोषणा TDA7419_REAR_SPKR_SRC		7

#घोषणा TDA7419_SUB_CUT_OFF_FREQ	0
#घोषणा TDA7419_MIDDLE_CENTER_FREQ	2
#घोषणा TDA7419_BASS_CENTER_FREQ	4
#घोषणा TDA7419_BASS_DC_MODE		6
#घोषणा TDA7419_SMOOTHING_FILTER	7

#घोषणा TDA7419_MIX_LF			0
#घोषणा TDA7419_MIX_RF			1
#घोषणा TDA7419_MIX_ENABLE		2
#घोषणा TDA7419_SUB_ENABLE		3
#घोषणा TDA7419_HPF_GAIN		4

#घोषणा TDA7419_SA_Q_FACTOR		0
#घोषणा TDA7419_RESET_MODE		1
#घोषणा TDA7419_SA_SOURCE		2
#घोषणा TDA7419_SA_RUN			3
#घोषणा TDA7419_RESET			4
#घोषणा TDA7419_CLK_SOURCE		5
#घोषणा TDA7419_COUPLING_MODE		6

काष्ठा tda7419_data अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल bool tda7419_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा reg_शेष tda7419_regmap_शेषs[] = अणु
	अणु TDA7419_MAIN_SRC_REG,	0xfe पूर्ण,
	अणु TDA7419_LOUDNESS_REG, 0xfe पूर्ण,
	अणु TDA7419_MUTE_CLK_REG, 0xfe पूर्ण,
	अणु TDA7419_VOLUME_REG, 0xfe पूर्ण,
	अणु TDA7419_TREBLE_REG, 0xfe पूर्ण,
	अणु TDA7419_MIDDLE_REG, 0xfe पूर्ण,
	अणु TDA7419_BASS_REG, 0xfe पूर्ण,
	अणु TDA7419_SECOND_SRC_REG, 0xfe पूर्ण,
	अणु TDA7419_SUB_MID_BASS_REG, 0xfe पूर्ण,
	अणु TDA7419_MIXING_GAIN_REG, 0xfe पूर्ण,
	अणु TDA7419_ATTENUATOR_LF_REG, 0xfe पूर्ण,
	अणु TDA7419_ATTENUATOR_RF_REG, 0xfe पूर्ण,
	अणु TDA7419_ATTENUATOR_LR_REG, 0xfe पूर्ण,
	अणु TDA7419_ATTENUATOR_RR_REG, 0xfe पूर्ण,
	अणु TDA7419_MIXING_LEVEL_REG, 0xfe पूर्ण,
	अणु TDA7419_ATTENUATOR_SUB_REG, 0xfe पूर्ण,
	अणु TDA7419_SA_CLK_AC_REG, 0xfe पूर्ण,
	अणु TDA7419_TESTING_REG, 0xfe पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tda7419_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TDA7419_TESTING_REG,
	.cache_type = REGCACHE_RBTREE,
	.पढ़ोable_reg = tda7419_पढ़ोable_reg,
	.reg_शेषs = tda7419_regmap_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tda7419_regmap_शेषs),
पूर्ण;

काष्ठा tda7419_vol_control अणु
	पूर्णांक min, max;
	अचिन्हित पूर्णांक reg, rreg, mask, thresh;
	अचिन्हित पूर्णांक invert:1;
पूर्ण;

अटल अंतरभूत bool tda7419_vol_is_stereo(काष्ठा tda7419_vol_control *tvc)
अणु
	अगर (tvc->reg == tvc->rreg)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक tda7419_vol_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा tda7419_vol_control *tvc =
		(काष्ठा tda7419_vol_control *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = tda7419_vol_is_stereo(tvc) ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = tvc->min;
	uinfo->value.पूर्णांकeger.max = tvc->max;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tda7419_vol_get_value(पूर्णांक val, अचिन्हित पूर्णांक mask,
					पूर्णांक min, पूर्णांक thresh,
					अचिन्हित पूर्णांक invert)
अणु
	val &= mask;
	अगर (val < thresh) अणु
		अगर (invert)
			val = 0 - val;
	पूर्ण अन्यथा अगर (val > thresh) अणु
		अगर (invert)
			val = val - thresh;
		अन्यथा
			val = thresh - val;
	पूर्ण

	अगर (val < min)
		val = min;

	वापस val;
पूर्ण

अटल पूर्णांक tda7419_vol_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा tda7419_vol_control *tvc =
		(काष्ठा tda7419_vol_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = tvc->reg;
	अचिन्हित पूर्णांक rreg = tvc->rreg;
	अचिन्हित पूर्णांक mask = tvc->mask;
	पूर्णांक min = tvc->min;
	पूर्णांक thresh = tvc->thresh;
	अचिन्हित पूर्णांक invert = tvc->invert;
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);
	ucontrol->value.पूर्णांकeger.value[0] =
		tda7419_vol_get_value(val, mask, min, thresh, invert);

	अगर (tda7419_vol_is_stereo(tvc)) अणु
		val = snd_soc_component_पढ़ो(component, rreg);
		ucontrol->value.पूर्णांकeger.value[1] =
			tda7419_vol_get_value(val, mask, min, thresh, invert);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tda7419_vol_put_value(पूर्णांक val, पूर्णांक thresh,
					अचिन्हित पूर्णांक invert)
अणु
	अगर (val < 0) अणु
		अगर (invert)
			val = असल(val);
		अन्यथा
			val = thresh - val;
	पूर्ण अन्यथा अगर ((val > 0) && invert) अणु
		val += thresh;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक tda7419_vol_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_kcontrol_chip(kcontrol);
	काष्ठा tda7419_vol_control *tvc =
		(काष्ठा tda7419_vol_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = tvc->reg;
	अचिन्हित पूर्णांक rreg = tvc->rreg;
	अचिन्हित पूर्णांक mask = tvc->mask;
	पूर्णांक thresh = tvc->thresh;
	अचिन्हित पूर्णांक invert = tvc->invert;
	पूर्णांक val;
	पूर्णांक ret;

	val = tda7419_vol_put_value(ucontrol->value.पूर्णांकeger.value[0],
				    thresh, invert);
	ret = snd_soc_component_update_bits(component, reg,
					    mask, val);
	अगर (ret < 0)
		वापस ret;

	अगर (tda7419_vol_is_stereo(tvc)) अणु
		val = tda7419_vol_put_value(ucontrol->value.पूर्णांकeger.value[1],
					    thresh, invert);
		ret = snd_soc_component_update_bits(component, rreg,
						    mask, val);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा TDA7419_SINGLE_VALUE(xreg, xmask, xmin, xmax, xthresh, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा tda7419_vol_control) \
	अणु.reg = xreg, .rreg = xreg, .mask = xmask, .min = xmin, \
	 .max = xmax, .thresh = xthresh, .invert = xinvertपूर्ण)

#घोषणा TDA7419_DOUBLE_R_VALUE(xregl, xregr, xmask, xmin, xmax, xthresh, \
			       xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा tda7419_vol_control) \
	अणु.reg = xregl, .rreg = xregr, .mask = xmask, .min = xmin, \
	 .max = xmax, .thresh = xthresh, .invert = xinvertपूर्ण)

#घोषणा TDA7419_SINGLE_TLV(xname, xreg, xmask, xmin, xmax, xthresh, \
			   xinvert, xtlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (xtlv_array), \
	.info = tda7419_vol_info, \
	.get = tda7419_vol_get, \
	.put = tda7419_vol_put, \
	.निजी_value = TDA7419_SINGLE_VALUE(xreg, xmask, xmin, \
					      xmax, xthresh, xinvert), \
पूर्ण

#घोषणा TDA7419_DOUBLE_R_TLV(xname, xregl, xregr, xmask, xmin, xmax, \
			     xthresh, xinvert, xtlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (xtlv_array), \
	.info = tda7419_vol_info, \
	.get = tda7419_vol_get, \
	.put = tda7419_vol_put, \
	.निजी_value = TDA7419_DOUBLE_R_VALUE(xregl, xregr, xmask, \
						xmin, xmax, xthresh, \
						xinvert), \
पूर्ण

अटल स्थिर अक्षर * स्थिर क्रमागत_src_sel[] = अणु
	"QD", "SE1", "SE2", "SE3", "SE", "Mute", "Mute", "Mute"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_मुख्य_src_sel,
	TDA7419_MAIN_SRC_REG, TDA7419_MAIN_SRC_SEL, क्रमागत_src_sel);
अटल स्थिर काष्ठा snd_kcontrol_new soc_mux_मुख्य_src_sel =
	SOC_DAPM_ENUM("Main Source Select", soc_क्रमागत_मुख्य_src_sel);
अटल DECLARE_TLV_DB_SCALE(tlv_src_gain, 0, 100, 0);
अटल DECLARE_TLV_DB_SCALE(tlv_loudness_atten, -1500, 100, 0);
अटल स्थिर अक्षर * स्थिर क्रमागत_loudness_center_freq[] = अणु
	"Flat", "400 Hz", "800 Hz", "2400 Hz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_loudness_center_freq,
	TDA7419_LOUDNESS_REG, TDA7419_LOUDNESS_CENTER_FREQ,
	क्रमागत_loudness_center_freq);
अटल स्थिर अक्षर * स्थिर क्रमागत_mute_influence[] = अणु
	"Pin and IIC", "IIC"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_mute_influence,
	TDA7419_MUTE_CLK_REG, TDA7419_MUTE_INFLUENCE, क्रमागत_mute_influence);
अटल स्थिर अक्षर * स्थिर क्रमागत_soft_mute_समय[] = अणु
	"0.48 ms", "0.96 ms", "123 ms", "123 ms"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_soft_mute_समय,
	TDA7419_MUTE_CLK_REG, TDA7419_SOFT_MUTE_TIME, क्रमागत_soft_mute_समय);
अटल स्थिर अक्षर * स्थिर क्रमागत_soft_step_समय[] = अणु
	"0.160 ms", "0.321 ms", "0.642 ms", "1.28 ms",
	"2.56 ms", "5.12 ms", "10.24 ms", "20.48 ms"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_soft_step_समय,
	TDA7419_MUTE_CLK_REG, TDA7419_SOFT_STEP_TIME, क्रमागत_soft_step_समय);
अटल DECLARE_TLV_DB_SCALE(tlv_volume, -8000, 100, 1);
अटल स्थिर अक्षर * स्थिर क्रमागत_treble_center_freq[] = अणु
	"10.0 kHz", "12.5 kHz", "15.0 kHz", "17.5 kHz"पूर्ण;
अटल DECLARE_TLV_DB_SCALE(tlv_filter, -1500, 100, 0);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_treble_center_freq,
	TDA7419_TREBLE_REG, TDA7419_TREBLE_CENTER_FREQ,
	क्रमागत_treble_center_freq);
अटल स्थिर अक्षर * स्थिर क्रमागत_ref_out_select[] = अणु
	"External Vref (4 V)", "Internal Vref (3.3 V)"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_ref_out_select,
	TDA7419_TREBLE_REG, TDA7419_REF_OUT_SELECT, क्रमागत_ref_out_select);
अटल स्थिर अक्षर * स्थिर क्रमागत_middle_q_factor[] = अणु
	"0.5", "0.75", "1.0", "1.25"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_middle_q_factor,
	TDA7419_MIDDLE_REG, TDA7419_MIDDLE_Q_FACTOR, क्रमागत_middle_q_factor);
अटल स्थिर अक्षर * स्थिर क्रमागत_bass_q_factor[] = अणु
	"1.0", "1.25", "1.5", "2.0"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_bass_q_factor,
	TDA7419_BASS_REG, TDA7419_BASS_Q_FACTOR, क्रमागत_bass_q_factor);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_second_src_sel,
	TDA7419_SECOND_SRC_REG, TDA7419_SECOND_SRC_SEL, क्रमागत_src_sel);
अटल स्थिर काष्ठा snd_kcontrol_new soc_mux_second_src_sel =
	SOC_DAPM_ENUM("Second Source Select", soc_क्रमागत_second_src_sel);
अटल स्थिर अक्षर * स्थिर क्रमागत_rear_spkr_src[] = अणु
	"Main", "Second"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_rear_spkr_src,
	TDA7419_SECOND_SRC_REG, TDA7419_REAR_SPKR_SRC, क्रमागत_rear_spkr_src);
अटल स्थिर काष्ठा snd_kcontrol_new soc_mux_rear_spkr_src =
	SOC_DAPM_ENUM("Rear Speaker Source", soc_क्रमागत_rear_spkr_src);
अटल स्थिर अक्षर * स्थिर क्रमागत_sub_cut_off_freq[] = अणु
	"Flat", "80 Hz", "120 Hz", "160 Hz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_sub_cut_off_freq,
	TDA7419_SUB_MID_BASS_REG, TDA7419_SUB_CUT_OFF_FREQ,
	क्रमागत_sub_cut_off_freq);
अटल स्थिर अक्षर * स्थिर क्रमागत_middle_center_freq[] = अणु
	"500 Hz", "1000 Hz", "1500 Hz", "2500 Hz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_middle_center_freq,
	TDA7419_SUB_MID_BASS_REG, TDA7419_MIDDLE_CENTER_FREQ,
	क्रमागत_middle_center_freq);
अटल स्थिर अक्षर * स्थिर क्रमागत_bass_center_freq[] = अणु
	"60 Hz", "80 Hz", "100 Hz", "200 Hz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_bass_center_freq,
	TDA7419_SUB_MID_BASS_REG, TDA7419_BASS_CENTER_FREQ,
	क्रमागत_bass_center_freq);
अटल स्थिर अक्षर * स्थिर क्रमागत_sa_q_factor[] = अणु
	"3.5", "1.75" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_sa_q_factor,
	TDA7419_SA_CLK_AC_REG, TDA7419_SA_Q_FACTOR, क्रमागत_sa_q_factor);
अटल स्थिर अक्षर * स्थिर क्रमागत_reset_mode[] = अणु
	"IIC", "Auto" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_reset_mode,
	TDA7419_SA_CLK_AC_REG, TDA7419_RESET_MODE, क्रमागत_reset_mode);
अटल स्थिर अक्षर * स्थिर क्रमागत_sa_src[] = अणु
	"Bass", "In Gain" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_sa_src,
	TDA7419_SA_CLK_AC_REG, TDA7419_SA_SOURCE, क्रमागत_sa_src);
अटल स्थिर अक्षर * स्थिर क्रमागत_clk_src[] = अणु
	"Internal", "External" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_clk_src,
	TDA7419_SA_CLK_AC_REG, TDA7419_CLK_SOURCE, क्रमागत_clk_src);
अटल स्थिर अक्षर * स्थिर क्रमागत_coupling_mode[] = अणु
	"DC Coupling (without HPF)", "AC Coupling after In Gain",
	"DC Coupling (with HPF)", "AC Coupling after Bass" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_coupling_mode,
	TDA7419_SA_CLK_AC_REG, TDA7419_COUPLING_MODE, क्रमागत_coupling_mode);

/* ASoC Controls */
अटल काष्ठा snd_kcontrol_new tda7419_controls[] = अणु
SOC_SINGLE_TLV("Main Source Capture Volume", TDA7419_MAIN_SRC_REG,
	       TDA7419_MAIN_SRC_GAIN, 15, 0, tlv_src_gain),
SOC_SINGLE("Main Source AutoZero Switch", TDA7419_MAIN_SRC_REG,
	   TDA7419_MAIN_SRC_AUTOZERO, 1, 1),
SOC_SINGLE_TLV("Loudness Playback Volume", TDA7419_LOUDNESS_REG,
	       TDA7419_LOUDNESS_ATTEN, 15, 1, tlv_loudness_atten),
SOC_ENUM("Loudness Center Frequency", soc_क्रमागत_loudness_center_freq),
SOC_SINGLE("Loudness High Boost Switch", TDA7419_LOUDNESS_REG,
	   TDA7419_LOUDNESS_BOOST, 1, 1),
SOC_SINGLE("Loudness Soft Step Switch", TDA7419_LOUDNESS_REG,
	   TDA7419_LOUDNESS_SOFT_STEP, 1, 1),
SOC_SINGLE("Soft Mute Switch", TDA7419_MUTE_CLK_REG, TDA7419_SOFT_MUTE, 1, 1),
SOC_ENUM("Mute Influence", soc_क्रमागत_mute_influence),
SOC_ENUM("Soft Mute Time", soc_क्रमागत_soft_mute_समय),
SOC_ENUM("Soft Step Time", soc_क्रमागत_soft_step_समय),
SOC_SINGLE("Clock Fast Mode Switch", TDA7419_MUTE_CLK_REG,
	   TDA7419_CLK_FAST_MODE, 1, 1),
TDA7419_SINGLE_TLV("Master Playback Volume", TDA7419_VOLUME_REG,
		   0x7f, -80, 15, 0x10, 0, tlv_volume),
SOC_SINGLE("Volume Soft Step Switch", TDA7419_VOLUME_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
TDA7419_SINGLE_TLV("Treble Playback Volume", TDA7419_TREBLE_REG,
		   0x1f, -15, 15, 0x10, 1, tlv_filter),
SOC_ENUM("Treble Center Frequency", soc_क्रमागत_treble_center_freq),
SOC_ENUM("Reference Output Select", soc_क्रमागत_ref_out_select),
TDA7419_SINGLE_TLV("Middle Playback Volume", TDA7419_MIDDLE_REG,
		   0x1f, -15, 15, 0x10, 1, tlv_filter),
SOC_ENUM("Middle Q Factor", soc_क्रमागत_middle_q_factor),
SOC_SINGLE("Middle Soft Step Switch", TDA7419_MIDDLE_REG,
	   TDA7419_MIDDLE_SOFT_STEP, 1, 1),
TDA7419_SINGLE_TLV("Bass Playback Volume", TDA7419_BASS_REG,
		   0x1f, -15, 15, 0x10, 1, tlv_filter),
SOC_ENUM("Bass Q Factor", soc_क्रमागत_bass_q_factor),
SOC_SINGLE("Bass Soft Step Switch", TDA7419_BASS_REG,
	   TDA7419_BASS_SOFT_STEP, 1, 1),
SOC_SINGLE_TLV("Second Source Capture Volume", TDA7419_SECOND_SRC_REG,
	       TDA7419_SECOND_SRC_GAIN, 15, 0, tlv_src_gain),
SOC_ENUM("Subwoofer Cut-off Frequency", soc_क्रमागत_sub_cut_off_freq),
SOC_ENUM("Middle Center Frequency", soc_क्रमागत_middle_center_freq),
SOC_ENUM("Bass Center Frequency", soc_क्रमागत_bass_center_freq),
SOC_SINGLE("Bass DC Mode Switch", TDA7419_SUB_MID_BASS_REG,
	   TDA7419_BASS_DC_MODE, 1, 1),
SOC_SINGLE("Smoothing Filter Switch", TDA7419_SUB_MID_BASS_REG,
	   TDA7419_SMOOTHING_FILTER, 1, 1),
TDA7419_DOUBLE_R_TLV("Front Speaker Playback Volume", TDA7419_ATTENUATOR_LF_REG,
		     TDA7419_ATTENUATOR_RF_REG, 0x7f, -80, 15, 0x10, 0,
		     tlv_volume),
SOC_SINGLE("Left Front Soft Step Switch", TDA7419_ATTENUATOR_LF_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
SOC_SINGLE("Right Front Soft Step Switch", TDA7419_ATTENUATOR_RF_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
TDA7419_DOUBLE_R_TLV("Rear Speaker Playback Volume", TDA7419_ATTENUATOR_LR_REG,
		     TDA7419_ATTENUATOR_RR_REG, 0x7f, -80, 15, 0x10, 0,
		     tlv_volume),
SOC_SINGLE("Left Rear Soft Step Switch", TDA7419_ATTENUATOR_LR_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
SOC_SINGLE("Right Rear Soft Step Switch", TDA7419_ATTENUATOR_RR_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
TDA7419_SINGLE_TLV("Mixing Capture Volume", TDA7419_MIXING_LEVEL_REG,
		   0x7f, -80, 15, 0x10, 0, tlv_volume),
SOC_SINGLE("Mixing Level Soft Step Switch", TDA7419_MIXING_LEVEL_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
TDA7419_SINGLE_TLV("Subwoofer Playback Volume", TDA7419_ATTENUATOR_SUB_REG,
		   0x7f, -80, 15, 0x10, 0, tlv_volume),
SOC_SINGLE("Subwoofer Soft Step Switch", TDA7419_ATTENUATOR_SUB_REG,
	   TDA7419_VOLUME_SOFT_STEP, 1, 1),
SOC_ENUM("Spectrum Analyzer Q Factor", soc_क्रमागत_sa_q_factor),
SOC_ENUM("Spectrum Analyzer Reset Mode", soc_क्रमागत_reset_mode),
SOC_ENUM("Spectrum Analyzer Source", soc_क्रमागत_sa_src),
SOC_SINGLE("Spectrum Analyzer Run Switch", TDA7419_SA_CLK_AC_REG,
	   TDA7419_SA_RUN, 1, 1),
SOC_SINGLE("Spectrum Analyzer Reset Switch", TDA7419_SA_CLK_AC_REG,
	   TDA7419_RESET, 1, 1),
SOC_ENUM("Clock Source", soc_क्रमागत_clk_src),
SOC_ENUM("Coupling Mode", soc_क्रमागत_coupling_mode),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new soc_mixer_lf_output_controls[] = अणु
	SOC_DAPM_SINGLE("Mix to LF Speaker Switch",
			TDA7419_MIXING_GAIN_REG,
			TDA7419_MIX_LF, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new soc_mixer_rf_output_controls[] = अणु
	SOC_DAPM_SINGLE("Mix to RF Speaker Switch",
			TDA7419_MIXING_GAIN_REG,
			TDA7419_MIX_RF, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new soc_mix_enable_चयन_controls[] = अणु
	SOC_DAPM_SINGLE("Switch", TDA7419_MIXING_GAIN_REG,
			TDA7419_MIX_ENABLE, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new soc_sub_enable_चयन_controls[] = अणु
	SOC_DAPM_SINGLE("Switch", TDA7419_MIXING_GAIN_REG,
			TDA7419_MIX_ENABLE, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tda7419_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("SE3L"),
	SND_SOC_DAPM_INPUT("SE3R"),
	SND_SOC_DAPM_INPUT("SE2L"),
	SND_SOC_DAPM_INPUT("SE2R"),
	SND_SOC_DAPM_INPUT("SE1L"),
	SND_SOC_DAPM_INPUT("SE1R"),
	SND_SOC_DAPM_INPUT("DIFFL"),
	SND_SOC_DAPM_INPUT("DIFFR"),
	SND_SOC_DAPM_INPUT("MIX"),

	SND_SOC_DAPM_MUX("Main Source Select", SND_SOC_NOPM,
			 0, 0, &soc_mux_मुख्य_src_sel),
	SND_SOC_DAPM_MUX("Second Source Select", SND_SOC_NOPM,
			 0, 0, &soc_mux_second_src_sel),
	SND_SOC_DAPM_MUX("Rear Speaker Source", SND_SOC_NOPM,
			 0, 0, &soc_mux_rear_spkr_src),

	SND_SOC_DAPM_SWITCH("Mix Enable", SND_SOC_NOPM,
			0, 0, &soc_mix_enable_चयन_controls[0]),
	SND_SOC_DAPM_MIXER_NAMED_CTL("LF Output Mixer", SND_SOC_NOPM,
			0, 0, &soc_mixer_lf_output_controls[0],
			ARRAY_SIZE(soc_mixer_lf_output_controls)),
	SND_SOC_DAPM_MIXER_NAMED_CTL("RF Output Mixer", SND_SOC_NOPM,
			0, 0, &soc_mixer_rf_output_controls[0],
			ARRAY_SIZE(soc_mixer_rf_output_controls)),

	SND_SOC_DAPM_SWITCH("Subwoofer Enable",
			SND_SOC_NOPM, 0, 0,
			&soc_sub_enable_चयन_controls[0]),

	SND_SOC_DAPM_OUTPUT("OUTLF"),
	SND_SOC_DAPM_OUTPUT("OUTRF"),
	SND_SOC_DAPM_OUTPUT("OUTLR"),
	SND_SOC_DAPM_OUTPUT("OUTRR"),
	SND_SOC_DAPM_OUTPUT("OUTSW"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tda7419_dapm_routes[] = अणु
	अणु"Main Source Select", "SE3", "SE3L"पूर्ण,
	अणु"Main Source Select", "SE3", "SE3R"पूर्ण,
	अणु"Main Source Select", "SE2", "SE2L"पूर्ण,
	अणु"Main Source Select", "SE2", "SE2R"पूर्ण,
	अणु"Main Source Select", "SE1", "SE1L"पूर्ण,
	अणु"Main Source Select", "SE1", "SE1R"पूर्ण,
	अणु"Main Source Select", "SE", "DIFFL"पूर्ण,
	अणु"Main Source Select", "SE", "DIFFR"पूर्ण,
	अणु"Main Source Select", "QD", "DIFFL"पूर्ण,
	अणु"Main Source Select", "QD", "DIFFR"पूर्ण,

	अणु"Second Source Select", "SE3", "SE3L"पूर्ण,
	अणु"Second Source Select", "SE3", "SE3R"पूर्ण,
	अणु"Second Source Select", "SE2", "SE2L"पूर्ण,
	अणु"Second Source Select", "SE2", "SE2R"पूर्ण,
	अणु"Second Source Select", "SE1", "SE1L"पूर्ण,
	अणु"Second Source Select", "SE1", "SE1R"पूर्ण,
	अणु"Second Source Select", "SE", "DIFFL"पूर्ण,
	अणु"Second Source Select", "SE", "DIFFR"पूर्ण,
	अणु"Second Source Select", "QD", "DIFFL"पूर्ण,
	अणु"Second Source Select", "QD", "DIFFR"पूर्ण,

	अणु"Rear Speaker Source", "Main", "Main Source Select"पूर्ण,
	अणु"Rear Speaker Source", "Second", "Second Source Select"पूर्ण,

	अणु"Subwoofer Enable", "Switch", "Main Source Select"पूर्ण,

	अणु"Mix Enable", "Switch", "MIX"पूर्ण,

	अणु"LF Output Mixer", शून्य, "Main Source Select"पूर्ण,
	अणु"LF Output Mixer", "Mix to LF Speaker Switch", "Mix Enable"पूर्ण,
	अणु"RF Output Mixer", शून्य, "Main Source Select"पूर्ण,
	अणु"RF Output Mixer", "Mix to RF Speaker Switch", "Mix Enable"पूर्ण,

	अणु"OUTLF", शून्य, "LF Output Mixer"पूर्ण,
	अणु"OUTRF", शून्य, "RF Output Mixer"पूर्ण,
	अणु"OUTLR", शून्य, "Rear Speaker Source"पूर्ण,
	अणु"OUTRR", शून्य, "Rear Speaker Source"पूर्ण,
	अणु"OUTSW", शून्य, "Subwoofer Enable"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tda7419_component_driver = अणु
	.name			= "tda7419",
	.controls		= tda7419_controls,
	.num_controls		= ARRAY_SIZE(tda7419_controls),
	.dapm_widमाला_लो		= tda7419_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tda7419_dapm_widमाला_लो),
	.dapm_routes		= tda7419_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(tda7419_dapm_routes),
पूर्ण;

अटल पूर्णांक tda7419_probe(काष्ठा i2c_client *i2c,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda7419_data *tda7419;
	पूर्णांक i, ret;

	tda7419 = devm_kzalloc(&i2c->dev,
			       माप(काष्ठा tda7419_data),
			       GFP_KERNEL);
	अगर (tda7419 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, tda7419);

	tda7419->regmap = devm_regmap_init_i2c(i2c, &tda7419_regmap_config);
	अगर (IS_ERR(tda7419->regmap)) अणु
		ret = PTR_ERR(tda7419->regmap);
		dev_err(&i2c->dev, "error initializing regmap: %d\n",
				ret);
		वापस ret;
	पूर्ण

	/*
	 * Reset रेजिस्टरs to घातer-on शेषs. The part करोes not provide a
	 * soft-reset function and the रेजिस्टरs are not पढ़ोable. This ensures
	 * that the cache matches रेजिस्टर contents even अगर the रेजिस्टरs have
	 * been previously initialized and not घातer cycled beक्रमe probe.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(tda7419_regmap_शेषs); i++)
		regmap_ग_लिखो(tda7419->regmap,
			     tda7419_regmap_शेषs[i].reg,
			     tda7419_regmap_शेषs[i].def);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&tda7419_component_driver, शून्य, 0);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "error registering component: %d\n",
				ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda7419_i2c_id[] = अणु
	अणु "tda7419", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda7419_i2c_id);

अटल स्थिर काष्ठा of_device_id tda7419_of_match[] = अणु
	अणु .compatible = "st,tda7419" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver tda7419_driver = अणु
	.driver = अणु
		.name   = "tda7419",
		.of_match_table = tda7419_of_match,
	पूर्ण,
	.probe          = tda7419_probe,
	.id_table       = tda7419_i2c_id,
पूर्ण;

module_i2c_driver(tda7419_driver);

MODULE_AUTHOR("Matt Porter <mporter@konsulko.com>");
MODULE_DESCRIPTION("TDA7419 audio processor driver");
MODULE_LICENSE("GPL");
