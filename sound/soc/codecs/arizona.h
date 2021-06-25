<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arizona.h - Wolfson Arizona class device shared support
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _ASOC_ARIZONA_H
#घोषणा _ASOC_ARIZONA_H

#समावेश <linux/completion.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mfd/arizona/core.h>

#समावेश <sound/soc.h>

#समावेश "wm_adsp.h"

#घोषणा ARIZONA_CLK_SYSCLK         1
#घोषणा ARIZONA_CLK_ASYNCCLK       2
#घोषणा ARIZONA_CLK_OPCLK          3
#घोषणा ARIZONA_CLK_ASYNC_OPCLK    4

#घोषणा ARIZONA_CLK_SRC_MCLK1    0x0
#घोषणा ARIZONA_CLK_SRC_MCLK2    0x1
#घोषणा ARIZONA_CLK_SRC_FLL1     0x4
#घोषणा ARIZONA_CLK_SRC_FLL2     0x5
#घोषणा ARIZONA_CLK_SRC_AIF1BCLK 0x8
#घोषणा ARIZONA_CLK_SRC_AIF2BCLK 0x9
#घोषणा ARIZONA_CLK_SRC_AIF3BCLK 0xa

#घोषणा ARIZONA_FLL_SRC_NONE      -1
#घोषणा ARIZONA_FLL_SRC_MCLK1      0
#घोषणा ARIZONA_FLL_SRC_MCLK2      1
#घोषणा ARIZONA_FLL_SRC_SLIMCLK    3
#घोषणा ARIZONA_FLL_SRC_FLL1       4
#घोषणा ARIZONA_FLL_SRC_FLL2       5
#घोषणा ARIZONA_FLL_SRC_AIF1BCLK   8
#घोषणा ARIZONA_FLL_SRC_AIF2BCLK   9
#घोषणा ARIZONA_FLL_SRC_AIF3BCLK  10
#घोषणा ARIZONA_FLL_SRC_AIF1LRCLK 12
#घोषणा ARIZONA_FLL_SRC_AIF2LRCLK 13
#घोषणा ARIZONA_FLL_SRC_AIF3LRCLK 14

#घोषणा ARIZONA_MIXER_VOL_MASK             0x00FE
#घोषणा ARIZONA_MIXER_VOL_SHIFT                 1
#घोषणा ARIZONA_MIXER_VOL_WIDTH                 7

#घोषणा ARIZONA_CLK_6MHZ   0
#घोषणा ARIZONA_CLK_12MHZ  1
#घोषणा ARIZONA_CLK_24MHZ  2
#घोषणा ARIZONA_CLK_49MHZ  3
#घोषणा ARIZONA_CLK_73MHZ  4
#घोषणा ARIZONA_CLK_98MHZ  5
#घोषणा ARIZONA_CLK_147MHZ 6

#घोषणा ARIZONA_MAX_DAI  10
#घोषणा ARIZONA_MAX_ADSP 4

#घोषणा ARIZONA_DVFS_SR1_RQ	0x001
#घोषणा ARIZONA_DVFS_ADSP1_RQ	0x100

/* Notअगरier events */
#घोषणा ARIZONA_NOTIFY_VOICE_TRIGGER   0x1

काष्ठा wm_adsp;

काष्ठा arizona_dai_priv अणु
	पूर्णांक clk;

	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांक;
पूर्ण;

काष्ठा arizona_priv अणु
	काष्ठा wm_adsp adsp[ARIZONA_MAX_ADSP];
	काष्ठा arizona *arizona;
	पूर्णांक sysclk;
	पूर्णांक asyncclk;
	काष्ठा arizona_dai_priv dai[ARIZONA_MAX_DAI];

	पूर्णांक num_inमाला_दो;
	अचिन्हित पूर्णांक in_pending;

	अचिन्हित पूर्णांक out_up_pending;
	अचिन्हित पूर्णांक out_up_delay;
	अचिन्हित पूर्णांक out_करोwn_pending;
	अचिन्हित पूर्णांक out_करोwn_delay;

	अचिन्हित पूर्णांक dvfs_reqs;
	काष्ठा mutex dvfs_lock;
	bool dvfs_cached;

	/* Variables used by arizona-jack.c code */
	काष्ठा mutex lock;
	काष्ठा delayed_work hpdet_work;
	काष्ठा delayed_work micd_detect_work;
	काष्ठा delayed_work micd_समयout_work;
	काष्ठा snd_soc_jack *jack;
	काष्ठा regulator *micvdd;
	काष्ठा gpio_desc *micd_pol_gpio;

	u16 last_jackdet;

	पूर्णांक micd_mode;
	स्थिर काष्ठा arizona_micd_config *micd_modes;
	पूर्णांक micd_num_modes;

	पूर्णांक micd_button_mask;
	स्थिर काष्ठा arizona_micd_range *micd_ranges;
	पूर्णांक num_micd_ranges;

	bool micd_reva;
	bool micd_clamp;

	bool hpdet_active;
	bool hpdet_करोne;
	bool hpdet_retried;

	bool mic;
	bool detecting;

	पूर्णांक num_hpdet_res;
	अचिन्हित पूर्णांक hpdet_res[3];

	पूर्णांक jack_flips;
	पूर्णांक hpdet_ip_version;
पूर्ण;

काष्ठा arizona_voice_trigger_info अणु
	पूर्णांक core;
पूर्ण;

#घोषणा ARIZONA_NUM_MIXER_INPUTS 104

बाह्य स्थिर अचिन्हित पूर्णांक arizona_mixer_tlv[];
बाह्य स्थिर अक्षर * स्थिर arizona_mixer_texts[ARIZONA_NUM_MIXER_INPUTS];
बाह्य अचिन्हित पूर्णांक arizona_mixer_values[ARIZONA_NUM_MIXER_INPUTS];

#घोषणा ARIZONA_GAINMUX_CONTROLS(name, base) \
	SOC_SINGLE_RANGE_TLV(name " Input Volume", base + 1,		\
			     ARIZONA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     arizona_mixer_tlv)

#घोषणा ARIZONA_MIXER_CONTROLS(name, base) \
	SOC_SINGLE_RANGE_TLV(name " Input 1 Volume", base + 1,		\
			     ARIZONA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     arizona_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 2 Volume", base + 3,		\
			     ARIZONA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     arizona_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 3 Volume", base + 5,		\
			     ARIZONA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     arizona_mixer_tlv),			\
	SOC_SINGLE_RANGE_TLV(name " Input 4 Volume", base + 7,		\
			     ARIZONA_MIXER_VOL_SHIFT, 0x20, 0x50, 0,	\
			     arizona_mixer_tlv)

#घोषणा ARIZONA_MUX_ENUM_DECL(name, reg) \
	SOC_VALUE_ENUM_SINGLE_AUTODISABLE_DECL( \
		name, reg, 0, 0xff, arizona_mixer_texts, arizona_mixer_values)

#घोषणा ARIZONA_MUX_CTL_DECL(name) \
	स्थिर काष्ठा snd_kcontrol_new name##_mux =	\
		SOC_DAPM_ENUM("Route", name##_क्रमागत)

#घोषणा ARIZONA_MUX_ENUMS(name, base_reg) \
	अटल ARIZONA_MUX_ENUM_DECL(name##_क्रमागत, base_reg);      \
	अटल ARIZONA_MUX_CTL_DECL(name)

#घोषणा ARIZONA_MIXER_ENUMS(name, base_reg) \
	ARIZONA_MUX_ENUMS(name##_in1, base_reg);     \
	ARIZONA_MUX_ENUMS(name##_in2, base_reg + 2); \
	ARIZONA_MUX_ENUMS(name##_in3, base_reg + 4); \
	ARIZONA_MUX_ENUMS(name##_in4, base_reg + 6)

#घोषणा ARIZONA_DSP_AUX_ENUMS(name, base_reg) \
	ARIZONA_MUX_ENUMS(name##_aux1, base_reg);	\
	ARIZONA_MUX_ENUMS(name##_aux2, base_reg + 8);	\
	ARIZONA_MUX_ENUMS(name##_aux3, base_reg + 16);	\
	ARIZONA_MUX_ENUMS(name##_aux4, base_reg + 24);	\
	ARIZONA_MUX_ENUMS(name##_aux5, base_reg + 32);	\
	ARIZONA_MUX_ENUMS(name##_aux6, base_reg + 40)

#घोषणा ARIZONA_MUX(name, ctrl) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctrl)

#घोषणा ARIZONA_MUX_WIDGETS(name, name_str) \
	ARIZONA_MUX(name_str " Input", &name##_mux)

#घोषणा ARIZONA_MIXER_WIDGETS(name, name_str)	\
	ARIZONA_MUX(name_str " Input 1", &name##_in1_mux), \
	ARIZONA_MUX(name_str " Input 2", &name##_in2_mux), \
	ARIZONA_MUX(name_str " Input 3", &name##_in3_mux), \
	ARIZONA_MUX(name_str " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXER(name_str " Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0)

#घोषणा ARIZONA_DSP_WIDGETS(name, name_str) \
	ARIZONA_MIXER_WIDGETS(name##L, name_str "L"), \
	ARIZONA_MIXER_WIDGETS(name##R, name_str "R"), \
	ARIZONA_MUX(name_str " Aux 1", &name##_aux1_mux), \
	ARIZONA_MUX(name_str " Aux 2", &name##_aux2_mux), \
	ARIZONA_MUX(name_str " Aux 3", &name##_aux3_mux), \
	ARIZONA_MUX(name_str " Aux 4", &name##_aux4_mux), \
	ARIZONA_MUX(name_str " Aux 5", &name##_aux5_mux), \
	ARIZONA_MUX(name_str " Aux 6", &name##_aux6_mux)

#घोषणा ARIZONA_MUX_ROUTES(widget, name) \
	अणु widget, शून्य, name " Input" पूर्ण, \
	ARIZONA_MIXER_INPUT_ROUTES(name " Input")

#घोषणा ARIZONA_MIXER_ROUTES(widget, name) \
	अणु widget, शून्य, name " Mixer" पूर्ण,         \
	अणु name " Mixer", शून्य, name " Input 1" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 2" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 3" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 4" पूर्ण, \
	ARIZONA_MIXER_INPUT_ROUTES(name " Input 1"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Input 2"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Input 3"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Input 4")

#घोषणा ARIZONA_DSP_ROUTES(name) \
	अणु name, शून्य, name " Preloader"पूर्ण, \
	अणु name " Preloader", शून्य, "SYSCLK" पूर्ण, \
	अणु name " Preload", शून्य, name " Preloader"पूर्ण, \
	अणु name, शून्य, name " Aux 1" पूर्ण, \
	अणु name, शून्य, name " Aux 2" पूर्ण, \
	अणु name, शून्य, name " Aux 3" पूर्ण, \
	अणु name, शून्य, name " Aux 4" पूर्ण, \
	अणु name, शून्य, name " Aux 5" पूर्ण, \
	अणु name, शून्य, name " Aux 6" पूर्ण, \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 1"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 2"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 3"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 4"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 5"), \
	ARIZONA_MIXER_INPUT_ROUTES(name " Aux 6"), \
	ARIZONA_MIXER_ROUTES(name, name "L"), \
	ARIZONA_MIXER_ROUTES(name, name "R")

#घोषणा ARIZONA_EQ_CONTROL(xname, xbase)                      \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = arizona_eq_coeff_put, .निजी_value =         \
	((अचिन्हित दीर्घ)&(काष्ठा soc_bytes) अणु .base = xbase,  \
	 .num_regs = 20, .mask = ~ARIZONA_EQ1_B1_MODE पूर्ण) पूर्ण

#घोषणा ARIZONA_LHPF_CONTROL(xname, xbase)                    \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = arizona_lhpf_coeff_put, .निजी_value =       \
	((अचिन्हित दीर्घ)&(काष्ठा soc_bytes) अणु .base = xbase,  \
	 .num_regs = 1 पूर्ण) पूर्ण

#घोषणा ARIZONA_RATE_ENUM_SIZE 4
#घोषणा ARIZONA_SAMPLE_RATE_ENUM_SIZE 14

/* SND_JACK_* mask क्रम supported cable/चयन types */
#घोषणा ARIZONA_JACK_MASK  (SND_JACK_HEADSET | SND_JACK_LINEOUT | SND_JACK_MECHANICAL)

बाह्य स्थिर अक्षर * स्थिर arizona_rate_text[ARIZONA_RATE_ENUM_SIZE];
बाह्य स्थिर अचिन्हित पूर्णांक arizona_rate_val[ARIZONA_RATE_ENUM_SIZE];
बाह्य स्थिर अक्षर * स्थिर arizona_sample_rate_text[ARIZONA_SAMPLE_RATE_ENUM_SIZE];
बाह्य स्थिर अचिन्हित पूर्णांक arizona_sample_rate_val[ARIZONA_SAMPLE_RATE_ENUM_SIZE];

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_isrc_fsl[];
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_isrc_fsh[];
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_asrc_rate1;

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_in_vi_ramp;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_in_vd_ramp;

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_out_vi_ramp;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_out_vd_ramp;

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_lhpf1_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_lhpf2_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_lhpf3_mode;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_lhpf4_mode;

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_ng_hold;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_in_hpf_cut_क्रमागत;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_in_dmic_osr[];

बाह्य स्थिर काष्ठा snd_kcontrol_new arizona_adsp2_rate_controls[];

बाह्य स्थिर काष्ठा soc_क्रमागत arizona_anc_input_src[];
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_anc_ng_क्रमागत;
बाह्य स्थिर काष्ठा soc_क्रमागत arizona_output_anc_src[];

बाह्य स्थिर काष्ठा snd_kcontrol_new arizona_voice_trigger_चयन[];

पूर्णांक arizona_in_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		  पूर्णांक event);
पूर्णांक arizona_out_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		   पूर्णांक event);
पूर्णांक arizona_hp_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		  पूर्णांक event);
पूर्णांक arizona_anc_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		   पूर्णांक event);

पूर्णांक arizona_eq_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक arizona_lhpf_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक arizona_clk_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		   पूर्णांक event);
पूर्णांक arizona_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id, पूर्णांक source,
		       अचिन्हित पूर्णांक freq, पूर्णांक dir);

बाह्य स्थिर काष्ठा snd_soc_dai_ops arizona_dai_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops arizona_simple_dai_ops;

#घोषणा ARIZONA_FLL_NAME_LEN 20

काष्ठा arizona_fll अणु
	काष्ठा arizona *arizona;
	पूर्णांक id;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक vco_mult;

	अचिन्हित पूर्णांक fout;
	पूर्णांक sync_src;
	अचिन्हित पूर्णांक sync_freq;
	पूर्णांक ref_src;
	अचिन्हित पूर्णांक ref_freq;

	अक्षर lock_name[ARIZONA_FLL_NAME_LEN];
	अक्षर घड़ी_ok_name[ARIZONA_FLL_NAME_LEN];
पूर्ण;

पूर्णांक arizona_dvfs_up(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक flags);
पूर्णांक arizona_dvfs_करोwn(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक flags);
पूर्णांक arizona_dvfs_sysclk_ev(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
व्योम arizona_init_dvfs(काष्ठा arizona_priv *priv);

पूर्णांक arizona_init_fll(काष्ठा arizona *arizona, पूर्णांक id, पूर्णांक base,
		     पूर्णांक lock_irq, पूर्णांक ok_irq, काष्ठा arizona_fll *fll);
पूर्णांक arizona_set_fll_refclk(काष्ठा arizona_fll *fll, पूर्णांक source,
			   अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout);
पूर्णांक arizona_set_fll(काष्ठा arizona_fll *fll, पूर्णांक source,
		    अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout);

पूर्णांक arizona_init_spk(काष्ठा snd_soc_component *component);
पूर्णांक arizona_init_gpio(काष्ठा snd_soc_component *component);
पूर्णांक arizona_init_mono(काष्ठा snd_soc_component *component);

पूर्णांक arizona_init_common(काष्ठा arizona *arizona);
पूर्णांक arizona_init_vol_limit(काष्ठा arizona *arizona);

पूर्णांक arizona_init_spk_irqs(काष्ठा arizona *arizona);
पूर्णांक arizona_मुक्त_spk_irqs(काष्ठा arizona *arizona);

पूर्णांक arizona_init_dai(काष्ठा arizona_priv *priv, पूर्णांक id);

पूर्णांक arizona_set_output_mode(काष्ठा snd_soc_component *component, पूर्णांक output,
			    bool dअगरf);

bool arizona_input_analog(काष्ठा snd_soc_component *component, पूर्णांक shअगरt);

स्थिर अक्षर *arizona_sample_rate_val_to_name(अचिन्हित पूर्णांक rate_val);

अटल अंतरभूत पूर्णांक arizona_रेजिस्टर_notअगरier(काष्ठा snd_soc_component *component,
					    काष्ठा notअगरier_block *nb,
					    पूर्णांक (*notअगरy)
					    (काष्ठा notअगरier_block *nb,
					    अचिन्हित दीर्घ action, व्योम *data))
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;

	nb->notअगरier_call = notअगरy;

	वापस blocking_notअगरier_chain_रेजिस्टर(&arizona->notअगरier, nb);
पूर्ण

अटल अंतरभूत पूर्णांक arizona_unरेजिस्टर_notअगरier(काष्ठा snd_soc_component *component,
					      काष्ठा notअगरier_block *nb)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;

	वापस blocking_notअगरier_chain_unरेजिस्टर(&arizona->notअगरier, nb);
पूर्ण

पूर्णांक arizona_of_get_audio_pdata(काष्ठा arizona *arizona);

पूर्णांक arizona_jack_codec_dev_probe(काष्ठा arizona_priv *info, काष्ठा device *dev);
पूर्णांक arizona_jack_codec_dev_हटाओ(काष्ठा arizona_priv *info);

पूर्णांक arizona_jack_set_jack(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_jack *jack, व्योम *data);

#पूर्ण_अगर
