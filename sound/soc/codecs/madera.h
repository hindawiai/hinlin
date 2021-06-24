<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Cirrus Logic Madera class codecs common support
 *
 * Copyright (C) 2015-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 */

#अगर_अघोषित ASOC_MADERA_H
#घोषणा ASOC_MADERA_H

#समावेश <linux/completion.h>
#समावेश <sound/soc.h>
#समावेश <sound/madera-pdata.h>

#समावेश "wm_adsp.h"

#घोषणा MADERA_FLL1_REFCLK		1
#घोषणा MADERA_FLL2_REFCLK		2
#घोषणा MADERA_FLL3_REFCLK		3
#घोषणा MADERA_FLLAO_REFCLK		4
#घोषणा MADERA_FLL1_SYNCCLK		5
#घोषणा MADERA_FLL2_SYNCCLK		6
#घोषणा MADERA_FLL3_SYNCCLK		7
#घोषणा MADERA_FLLAO_SYNCCLK		8

#घोषणा MADERA_FLL_SRC_NONE		-1
#घोषणा MADERA_FLL_SRC_MCLK1		0
#घोषणा MADERA_FLL_SRC_MCLK2		1
#घोषणा MADERA_FLL_SRC_MCLK3		2
#घोषणा MADERA_FLL_SRC_SLIMCLK		3
#घोषणा MADERA_FLL_SRC_FLL1		4
#घोषणा MADERA_FLL_SRC_FLL2		5
#घोषणा MADERA_FLL_SRC_AIF1BCLK		8
#घोषणा MADERA_FLL_SRC_AIF2BCLK		9
#घोषणा MADERA_FLL_SRC_AIF3BCLK		10
#घोषणा MADERA_FLL_SRC_AIF4BCLK		11
#घोषणा MADERA_FLL_SRC_AIF1LRCLK	12
#घोषणा MADERA_FLL_SRC_AIF2LRCLK	13
#घोषणा MADERA_FLL_SRC_AIF3LRCLK	14
#घोषणा MADERA_FLL_SRC_AIF4LRCLK	15

#घोषणा MADERA_CLK_SYSCLK_1		1
#घोषणा MADERA_CLK_ASYNCCLK_1		2
#घोषणा MADERA_CLK_OPCLK		3
#घोषणा MADERA_CLK_ASYNC_OPCLK		4
#घोषणा MADERA_CLK_SYSCLK_2		5
#घोषणा MADERA_CLK_SYSCLK_3		6
#घोषणा MADERA_CLK_ASYNCCLK_2		7
#घोषणा MADERA_CLK_DSPCLK		8
#घोषणा MADERA_CLK_OUTCLK		9

#घोषणा MADERA_CLK_SRC_MCLK1		0x0
#घोषणा MADERA_CLK_SRC_MCLK2		0x1
#घोषणा MADERA_CLK_SRC_MCLK3		0x2
#घोषणा MADERA_CLK_SRC_FLL1		0x4
#घोषणा MADERA_CLK_SRC_FLL2		0x5
#घोषणा MADERA_CLK_SRC_FLL3		0x6
#घोषणा MADERA_CLK_SRC_FLLAO_HI		0x7
#घोषणा MADERA_CLK_SRC_FLL1_DIV6	0x7
#घोषणा MADERA_CLK_SRC_AIF1BCLK		0x8
#घोषणा MADERA_CLK_SRC_AIF2BCLK		0x9
#घोषणा MADERA_CLK_SRC_AIF3BCLK		0xA
#घोषणा MADERA_CLK_SRC_AIF4BCLK		0xB
#घोषणा MADERA_CLK_SRC_FLLAO		0xF

#घोषणा MADERA_OUTCLK_SYSCLK		0
#घोषणा MADERA_OUTCLK_ASYNCCLK		1
#घोषणा MADERA_OUTCLK_MCLK1		4
#घोषणा MADERA_OUTCLK_MCLK2		5
#घोषणा MADERA_OUTCLK_MCLK3		6

#घोषणा MADERA_MIXER_VOL_MASK		0x00FE
#घोषणा MADERA_MIXER_VOL_SHIFT		1
#घोषणा MADERA_MIXER_VOL_WIDTH		7

#घोषणा MADERA_DOM_GRP_FX		0
#घोषणा MADERA_DOM_GRP_ASRC1		1
#घोषणा MADERA_DOM_GRP_ASRC2		2
#घोषणा MADERA_DOM_GRP_ISRC1		3
#घोषणा MADERA_DOM_GRP_ISRC2		4
#घोषणा MADERA_DOM_GRP_ISRC3		5
#घोषणा MADERA_DOM_GRP_ISRC4		6
#घोषणा MADERA_DOM_GRP_OUT		7
#घोषणा MADERA_DOM_GRP_SPD		8
#घोषणा MADERA_DOM_GRP_DSP1		9
#घोषणा MADERA_DOM_GRP_DSP2		10
#घोषणा MADERA_DOM_GRP_DSP3		11
#घोषणा MADERA_DOM_GRP_DSP4		12
#घोषणा MADERA_DOM_GRP_DSP5		13
#घोषणा MADERA_DOM_GRP_DSP6		14
#घोषणा MADERA_DOM_GRP_DSP7		15
#घोषणा MADERA_DOM_GRP_AIF1		16
#घोषणा MADERA_DOM_GRP_AIF2		17
#घोषणा MADERA_DOM_GRP_AIF3		18
#घोषणा MADERA_DOM_GRP_AIF4		19
#घोषणा MADERA_DOM_GRP_SLIMBUS		20
#घोषणा MADERA_DOM_GRP_PWM		21
#घोषणा MADERA_DOM_GRP_DFC		22
#घोषणा MADERA_N_DOM_GRPS		23

#घोषणा MADERA_MAX_DAI			11
#घोषणा MADERA_MAX_ADSP			7

#घोषणा MADERA_NUM_MIXER_INPUTS		148

काष्ठा madera;
काष्ठा wm_adsp;

काष्ठा madera_voice_trigger_info अणु
	/** Which core triggered, 1-based (1 = DSP1, ...) */
	पूर्णांक core_num;
पूर्ण;

काष्ठा madera_dai_priv अणु
	पूर्णांक clk;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांक;
पूर्ण;

काष्ठा madera_priv अणु
	काष्ठा wm_adsp adsp[MADERA_MAX_ADSP];
	काष्ठा madera *madera;
	काष्ठा device *dev;
	पूर्णांक sysclk;
	पूर्णांक asyncclk;
	पूर्णांक dspclk;
	काष्ठा madera_dai_priv dai[MADERA_MAX_DAI];

	पूर्णांक num_inमाला_दो;

	अचिन्हित पूर्णांक in_pending;

	अचिन्हित पूर्णांक out_up_pending;
	अचिन्हित पूर्णांक out_up_delay;
	अचिन्हित पूर्णांक out_करोwn_pending;
	अचिन्हित पूर्णांक out_करोwn_delay;

	अचिन्हित पूर्णांक adsp_rate_cache[MADERA_MAX_ADSP];

	काष्ठा mutex rate_lock;

	पूर्णांक tdm_width[MADERA_MAX_AIF];
	पूर्णांक tdm_slots[MADERA_MAX_AIF];

	पूर्णांक करोमुख्य_group_ref[MADERA_N_DOM_GRPS];
पूर्ण;

काष्ठा madera_fll_cfg अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक theta;
	अचिन्हित पूर्णांक lambda;
	पूर्णांक refभाग;
	पूर्णांक fratio;
	पूर्णांक gain;
	पूर्णांक alt_gain;
पूर्ण;

काष्ठा madera_fll अणु
	काष्ठा madera *madera;
	पूर्णांक id;
	अचिन्हित पूर्णांक base;

	अचिन्हित पूर्णांक fout;

	पूर्णांक sync_src;
	अचिन्हित पूर्णांक sync_freq;

	पूर्णांक ref_src;
	अचिन्हित पूर्णांक ref_freq;
	काष्ठा madera_fll_cfg ref_cfg;
पूर्ण;

काष्ठा madera_क्रमागत अणु
	काष्ठा soc_क्रमागत mixer_क्रमागत;
	पूर्णांक val;
पूर्ण;

बाह्य स्थिर अचिन्हित पूर्णांक madera_ana_tlv[];
बाह्य स्थिर अचिन्हित पूर्णांक madera_eq_tlv[];
बाह्य स्थिर अचिन्हित पूर्णांक madera_digital_tlv[];
बाह्य स्थिर अचिन्हित पूर्णांक madera_noise_tlv[];
बाह्य स्थिर अचिन्हित पूर्णांक madera_ng_tlv[];

बाह्य स्थिर अचिन्हित पूर्णांक madera_mixer_tlv[];
बाह्य स्थिर अक्षर * स्थिर madera_mixer_texts[MADERA_NUM_MIXER_INPUTS];
बाह्य स्थिर अचिन्हित पूर्णांक madera_mixer_values[MADERA_NUM_MIXER_INPUTS];

#घोषणा MADERA_GAINMUX_CONTROLS(name, base) \
	SOC_SINGLE_RANGE_TLV(name " Input Volume", base + 1,		\
			     MADERA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     madera_mixer_tlv)

#घोषणा MADERA_MIXER_CONTROLS(name, base) \
	SOC_SINGLE_RANGE_TLV(name " Input 1 Volume", base + 1,		\
			     MADERA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     madera_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 2 Volume", base + 3,		\
			     MADERA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     madera_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 3 Volume", base + 5,		\
			     MADERA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     madera_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 4 Volume", base + 7,		\
			     MADERA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     madera_mixer_tlv)

#घोषणा MADERA_MUX_ENUM_DECL(name, reg) \
	SOC_VALUE_ENUM_SINGLE_AUTODISABLE_DECL( \
		name, reg, 0, 0xff, madera_mixer_texts, madera_mixer_values)

#घोषणा MADERA_MUX_CTL_DECL(name) \
	स्थिर काष्ठा snd_kcontrol_new name##_mux =	\
		SOC_DAPM_ENUM("Route", name##_क्रमागत)

#घोषणा MADERA_MUX_ENUMS(name, base_reg) \
	अटल MADERA_MUX_ENUM_DECL(name##_क्रमागत, base_reg);	\
	अटल MADERA_MUX_CTL_DECL(name)

#घोषणा MADERA_MIXER_ENUMS(name, base_reg) \
	MADERA_MUX_ENUMS(name##_in1, base_reg);     \
	MADERA_MUX_ENUMS(name##_in2, base_reg + 2); \
	MADERA_MUX_ENUMS(name##_in3, base_reg + 4); \
	MADERA_MUX_ENUMS(name##_in4, base_reg + 6)

#घोषणा MADERA_DSP_AUX_ENUMS(name, base_reg) \
	MADERA_MUX_ENUMS(name##_aux1, base_reg);	\
	MADERA_MUX_ENUMS(name##_aux2, base_reg + 8);	\
	MADERA_MUX_ENUMS(name##_aux3, base_reg + 16);	\
	MADERA_MUX_ENUMS(name##_aux4, base_reg + 24);	\
	MADERA_MUX_ENUMS(name##_aux5, base_reg + 32);	\
	MADERA_MUX_ENUMS(name##_aux6, base_reg + 40)

#घोषणा MADERA_MUX(name, ctrl) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctrl)

#घोषणा MADERA_MUX_WIDGETS(name, name_str) \
	MADERA_MUX(name_str " Input 1", &name##_mux)

#घोषणा MADERA_MIXER_WIDGETS(name, name_str)	\
	MADERA_MUX(name_str " Input 1", &name##_in1_mux), \
	MADERA_MUX(name_str " Input 2", &name##_in2_mux), \
	MADERA_MUX(name_str " Input 3", &name##_in3_mux), \
	MADERA_MUX(name_str " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXER(name_str " Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0)

#घोषणा MADERA_DSP_WIDGETS(name, name_str)			\
	MADERA_MIXER_WIDGETS(name##L, name_str "L"),		\
	MADERA_MIXER_WIDGETS(name##R, name_str "R"),		\
	MADERA_MUX(name_str " Aux 1", &name##_aux1_mux),	\
	MADERA_MUX(name_str " Aux 2", &name##_aux2_mux),	\
	MADERA_MUX(name_str " Aux 3", &name##_aux3_mux),	\
	MADERA_MUX(name_str " Aux 4", &name##_aux4_mux),	\
	MADERA_MUX(name_str " Aux 5", &name##_aux5_mux),	\
	MADERA_MUX(name_str " Aux 6", &name##_aux6_mux)

#घोषणा MADERA_MUX_ROUTES(widget, name) \
	अणु widget, शून्य, name " Input 1" पूर्ण, \
	MADERA_MIXER_INPUT_ROUTES(name " Input 1")

#घोषणा MADERA_MIXER_ROUTES(widget, name)		\
	अणु widget, शून्य, name " Mixer" पूर्ण,		\
	अणु name " Mixer", शून्य, name " Input 1" पूर्ण,	\
	अणु name " Mixer", शून्य, name " Input 2" पूर्ण,	\
	अणु name " Mixer", शून्य, name " Input 3" पूर्ण,	\
	अणु name " Mixer", शून्य, name " Input 4" पूर्ण,	\
	MADERA_MIXER_INPUT_ROUTES(name " Input 1"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Input 2"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Input 3"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Input 4")

#घोषणा MADERA_DSP_ROUTES(name)				\
	अणु name, शून्य, name " Preloader"पूर्ण,		\
	अणु name " Preload", शून्य, name " Preloader"पूर्ण,	\
	अणु name, शून्य, "SYSCLK"पूर्ण,			\
	अणु name, शून्य, "DSPCLK"पूर्ण,			\
	अणु name, शून्य, name " Aux 1" पूर्ण,			\
	अणु name, शून्य, name " Aux 2" पूर्ण,			\
	अणु name, शून्य, name " Aux 3" पूर्ण,			\
	अणु name, शून्य, name " Aux 4" पूर्ण,			\
	अणु name, शून्य, name " Aux 5" पूर्ण,			\
	अणु name, शून्य, name " Aux 6" पूर्ण,			\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 1"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 2"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 3"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 4"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 5"),	\
	MADERA_MIXER_INPUT_ROUTES(name " Aux 6"),	\
	MADERA_MIXER_ROUTES(name, name "L"),		\
	MADERA_MIXER_ROUTES(name, name "R")

#घोषणा MADERA_RATE_ENUM(xname, xक्रमागत) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,\
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = snd_soc_get_क्रमागत_द्विगुन, .put = madera_rate_put, \
	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण

#घोषणा MADERA_EQ_CONTROL(xname, xbase)				\
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get,	\
	.put = madera_eq_coeff_put, .निजी_value =		\
	((अचिन्हित दीर्घ)&(काष्ठा soc_bytes) अणु .base = xbase,	\
	 .num_regs = 20, .mask = ~MADERA_EQ1_B1_MODE पूर्ण) पूर्ण

#घोषणा MADERA_LHPF_CONTROL(xname, xbase)			\
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get,	\
	.put = madera_lhpf_coeff_put, .निजी_value =		\
	((अचिन्हित दीर्घ)&(काष्ठा soc_bytes) अणु .base = xbase,	\
	 .num_regs = 1 पूर्ण) पूर्ण

#घोषणा MADERA_RATES SNDRV_PCM_RATE_KNOT

#घोषणा MADERA_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा MADERA_OSR_ENUM_SIZE		5
#घोषणा MADERA_SYNC_RATE_ENUM_SIZE	3
#घोषणा MADERA_ASYNC_RATE_ENUM_SIZE	2
#घोषणा MADERA_RATE_ENUM_SIZE \
		(MADERA_SYNC_RATE_ENUM_SIZE + MADERA_ASYNC_RATE_ENUM_SIZE)
#घोषणा MADERA_SAMPLE_RATE_ENUM_SIZE	16
#घोषणा MADERA_DFC_TYPE_ENUM_SIZE	5
#घोषणा MADERA_DFC_WIDTH_ENUM_SIZE	5

बाह्य स्थिर काष्ठा snd_soc_dai_ops madera_dai_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops madera_simple_dai_ops;

बाह्य स्थिर काष्ठा snd_kcontrol_new madera_inmux[];
बाह्य स्थिर काष्ठा snd_kcontrol_new madera_inmode[];

बाह्य स्थिर अक्षर * स्थिर madera_rate_text[MADERA_RATE_ENUM_SIZE];
बाह्य स्थिर अचिन्हित पूर्णांक madera_rate_val[MADERA_RATE_ENUM_SIZE];

बाह्य स्थिर काष्ठा soc_क्रमागत madera_sample_rate[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_isrc_fsl[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_isrc_fsh[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_asrc1_rate[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_asrc1_bidir_rate[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_asrc2_rate[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_dfc_width[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_dfc_type[];

बाह्य स्थिर काष्ठा soc_क्रमागत madera_in_vi_ramp;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_in_vd_ramp;

बाह्य स्थिर काष्ठा soc_क्रमागत madera_out_vi_ramp;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_out_vd_ramp;

बाह्य स्थिर काष्ठा soc_क्रमागत madera_lhpf1_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_lhpf2_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_lhpf3_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_lhpf4_mode;

बाह्य स्थिर काष्ठा soc_क्रमागत madera_ng_hold;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_in_hpf_cut_क्रमागत;
बाह्य स्थिर काष्ठा soc_क्रमागत madera_in_dmic_osr[];

बाह्य स्थिर काष्ठा soc_क्रमागत madera_output_anc_src[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_anc_input_src[];
बाह्य स्थिर काष्ठा soc_क्रमागत madera_anc_ng_क्रमागत;

बाह्य स्थिर काष्ठा snd_kcontrol_new madera_dsp_trigger_output_mux[];
बाह्य स्थिर काष्ठा snd_kcontrol_new madera_drc_activity_output_mux[];

बाह्य स्थिर काष्ठा snd_kcontrol_new madera_adsp_rate_controls[];

पूर्णांक madera_dfc_put(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक madera_lp_mode_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक madera_out1_demux_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक madera_out1_demux_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक madera_rate_put(काष्ठा snd_kcontrol *kcontrol,
		    काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक madera_eq_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक madera_lhpf_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक madera_clk_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_sysclk_ev(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_spk_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_in_ev(काष्ठा snd_soc_dapm_widget *w,
		 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_out_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_hp_ev(काष्ठा snd_soc_dapm_widget *w,
		 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_anc_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक madera_करोमुख्य_clk_ev(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event);

पूर्णांक madera_set_adsp_clk(काष्ठा madera_priv *priv, पूर्णांक dsp_num,
			अचिन्हित पूर्णांक freq);

पूर्णांक madera_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
		      पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir);

पूर्णांक madera_init_fll(काष्ठा madera *madera, पूर्णांक id, पूर्णांक base,
		    काष्ठा madera_fll *fll);
पूर्णांक madera_set_fll_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			  अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout);
पूर्णांक madera_set_fll_syncclk(काष्ठा madera_fll *fll, पूर्णांक source,
			   अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout);
पूर्णांक madera_set_fll_ao_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			     अचिन्हित पूर्णांक fin, अचिन्हित पूर्णांक fout);
पूर्णांक madera_fllhj_set_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			    अचिन्हित पूर्णांक fin, अचिन्हित पूर्णांक fout);

पूर्णांक madera_core_init(काष्ठा madera_priv *priv);
पूर्णांक madera_core_मुक्त(काष्ठा madera_priv *priv);
पूर्णांक madera_init_overheat(काष्ठा madera_priv *priv);
पूर्णांक madera_मुक्त_overheat(काष्ठा madera_priv *priv);
पूर्णांक madera_init_inमाला_दो(काष्ठा snd_soc_component *component);
पूर्णांक madera_init_outमाला_दो(काष्ठा snd_soc_component *component,
			स्थिर काष्ठा snd_soc_dapm_route *routes,
			पूर्णांक n_mono_routes, पूर्णांक n_real);
पूर्णांक madera_init_bus_error_irq(काष्ठा madera_priv *priv, पूर्णांक dsp_num,
			      irq_handler_t handler);
व्योम madera_मुक्त_bus_error_irq(काष्ठा madera_priv *priv, पूर्णांक dsp_num);

पूर्णांक madera_init_dai(काष्ठा madera_priv *priv, पूर्णांक id);

पूर्णांक madera_set_output_mode(काष्ठा snd_soc_component *component, पूर्णांक output,
			   bool dअगरferential);

/* Following functions are क्रम use by machine drivers */
अटल अंतरभूत पूर्णांक madera_रेजिस्टर_notअगरier(काष्ठा snd_soc_component *component,
					   काष्ठा notअगरier_block *nb)
अणु
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;

	वापस blocking_notअगरier_chain_रेजिस्टर(&madera->notअगरier, nb);
पूर्ण

अटल अंतरभूत पूर्णांक
madera_unरेजिस्टर_notअगरier(काष्ठा snd_soc_component *component,
			   काष्ठा notअगरier_block *nb)
अणु
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;

	वापस blocking_notअगरier_chain_unरेजिस्टर(&madera->notअगरier, nb);
पूर्ण

#पूर्ण_अगर
