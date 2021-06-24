<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6359.c  --  mt6359 ALSA SoC audio codec driver
//
// Copyright (c) 2020 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "mt6359.h"

अटल व्योम mt6359_set_playback_gpio(काष्ठा mt6359_priv *priv)
अणु
	/* set gpio mosi mode, clk / data mosi */
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE2_CLR, 0x0ffe);
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE2_SET, 0x0249);

	/* sync mosi */
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE3_CLR, 0x6);
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE3_SET, 0x1);
पूर्ण

अटल व्योम mt6359_reset_playback_gpio(काष्ठा mt6359_priv *priv)
अणु
	/* set pad_aud_*_mosi to GPIO mode and dir input
	 * reason:
	 * pad_aud_dat_mosi*, because the pin is used as boot strap
	 * करोn't clean clk/sync, क्रम mtkaअगर protocol 2
	 */
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE2_CLR, 0x0ff8);
	regmap_update_bits(priv->regmap, MT6359_GPIO_सूची0, 0x7 << 9, 0x0);
पूर्ण

अटल व्योम mt6359_set_capture_gpio(काष्ठा mt6359_priv *priv)
अणु
	/* set gpio miso mode */
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE3_CLR, 0x0e00);
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE3_SET, 0x0200);

	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE4_CLR, 0x003f);
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE4_SET, 0x0009);
पूर्ण

अटल व्योम mt6359_reset_capture_gpio(काष्ठा mt6359_priv *priv)
अणु
	/* set pad_aud_*_miso to GPIO mode and dir input
	 * reason:
	 * pad_aud_clk_miso, because when playback only the miso_clk
	 * will also have 26m, so will have घातer leak
	 * pad_aud_dat_miso*, because the pin is used as boot strap
	 */
	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE3_CLR, 0x0e00);

	regmap_ग_लिखो(priv->regmap, MT6359_GPIO_MODE4_CLR, 0x003f);

	regmap_update_bits(priv->regmap, MT6359_GPIO_सूची0,
			   0x7 << 13, 0x0);
	regmap_update_bits(priv->regmap, MT6359_GPIO_सूची1,
			   0x3 << 0, 0x0);
पूर्ण

/* use only when करोing mtkaअगर calibraiton at the boot समय */
अटल व्योम mt6359_set_dcxo(काष्ठा mt6359_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6359_DCXO_CW12,
			   0x1 << RG_XO_AUDIO_EN_M_SFT,
			   (enable ? 1 : 0) << RG_XO_AUDIO_EN_M_SFT);
पूर्ण

/* use only when करोing mtkaअगर calibraiton at the boot समय */
अटल व्योम mt6359_set_clksq(काष्ठा mt6359_priv *priv, bool enable)
अणु
	/* Enable/disable CLKSQ 26MHz */
	regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON23,
			   RG_CLKSQ_EN_MASK_SFT,
			   (enable ? 1 : 0) << RG_CLKSQ_EN_SFT);
पूर्ण

/* use only when करोing mtkaअगर calibraiton at the boot समय */
अटल व्योम mt6359_set_aud_global_bias(काष्ठा mt6359_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON13,
			   RG_AUDGLB_PWRDN_VA32_MASK_SFT,
			   (enable ? 0 : 1) << RG_AUDGLB_PWRDN_VA32_SFT);
पूर्ण

/* use only when करोing mtkaअगर calibraiton at the boot समय */
अटल व्योम mt6359_set_topck(काष्ठा mt6359_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6359_AUD_TOP_CKPDN_CON0,
			   0x0066, enable ? 0x0 : 0x66);
पूर्ण

अटल व्योम mt6359_set_decoder_clk(काष्ठा mt6359_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON13,
			   RG_RSTB_DECODER_VA32_MASK_SFT,
			   (enable ? 1 : 0) << RG_RSTB_DECODER_VA32_SFT);
पूर्ण

अटल व्योम mt6359_mtkaअगर_tx_enable(काष्ठा mt6359_priv *priv)
अणु
	चयन (priv->mtkaअगर_protocol) अणु
	हाल MT6359_MTKAIF_PROTOCOL_2_CLK_P2:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0210);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_AUD_PAD_TOP,
				   0xff00, 0x3800);
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_AUD_PAD_TOP,
				   0xff00, 0x3900);
		अवरोध;
	हाल MT6359_MTKAIF_PROTOCOL_2:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0210);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		अवरोध;
	हाल MT6359_MTKAIF_PROTOCOL_1:
	शेष:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0000);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6359_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt6359_mtkaअगर_tx_disable(काष्ठा mt6359_priv *priv)
अणु
	/* disable aud_pad TX fअगरos */
	regmap_update_bits(priv->regmap, MT6359_AFE_AUD_PAD_TOP,
			   0xff00, 0x3000);
पूर्ण

व्योम mt6359_set_mtkaअगर_protocol(काष्ठा snd_soc_component *cmpnt,
				पूर्णांक mtkaअगर_protocol)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	priv->mtkaअगर_protocol = mtkaअगर_protocol;
पूर्ण
EXPORT_SYMBOL_GPL(mt6359_set_mtkaअगर_protocol);

व्योम mt6359_mtkaअगर_calibration_enable(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	mt6359_set_playback_gpio(priv);
	mt6359_set_capture_gpio(priv);
	mt6359_mtkaअगर_tx_enable(priv);

	mt6359_set_dcxo(priv, true);
	mt6359_set_aud_global_bias(priv, true);
	mt6359_set_clksq(priv, true);
	mt6359_set_topck(priv, true);

	/* set dat_miso_loopback on */
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT,
			   1 << RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT,
			   1 << RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG1,
			   RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_MASK_SFT,
			   1 << RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_SFT);
पूर्ण
EXPORT_SYMBOL_GPL(mt6359_mtkaअगर_calibration_enable);

व्योम mt6359_mtkaअगर_calibration_disable(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	/* set dat_miso_loopback off */
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG1,
			   RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_SFT);

	mt6359_set_topck(priv, false);
	mt6359_set_clksq(priv, false);
	mt6359_set_aud_global_bias(priv, false);
	mt6359_set_dcxo(priv, false);

	mt6359_mtkaअगर_tx_disable(priv);
	mt6359_reset_playback_gpio(priv);
	mt6359_reset_capture_gpio(priv);
पूर्ण
EXPORT_SYMBOL_GPL(mt6359_mtkaअगर_calibration_disable);

व्योम mt6359_set_mtkaअगर_calibration_phase(काष्ठा snd_soc_component *cmpnt,
					 पूर्णांक phase_1, पूर्णांक phase_2, पूर्णांक phase_3)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT,
			   phase_1 << RG_AUD_PAD_TOP_PHASE_MODE_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT,
			   phase_2 << RG_AUD_PAD_TOP_PHASE_MODE2_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDIO_DIG_CFG1,
			   RG_AUD_PAD_TOP_PHASE_MODE3_MASK_SFT,
			   phase_3 << RG_AUD_PAD_TOP_PHASE_MODE3_SFT);
पूर्ण
EXPORT_SYMBOL_GPL(mt6359_set_mtkaअगर_calibration_phase);

अटल व्योम zcd_disable(काष्ठा mt6359_priv *priv)
अणु
	regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON0, 0x0000);
पूर्ण

अटल व्योम hp_मुख्य_output_ramp(काष्ठा mt6359_priv *priv, bool up)
अणु
	पूर्णांक i, stage;
	पूर्णांक target = 7;

	/* Enable/Reduce HPL/R मुख्य output stage step by step */
	क्रम (i = 0; i <= target; i++) अणु
		stage = up ? i : target - i;
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1,
				   RG_HPLOUTSTGCTRL_VAUDP32_MASK_SFT,
				   stage << RG_HPLOUTSTGCTRL_VAUDP32_SFT);
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1,
				   RG_HPROUTSTGCTRL_VAUDP32_MASK_SFT,
				   stage << RG_HPROUTSTGCTRL_VAUDP32_SFT);
		usleep_range(600, 650);
	पूर्ण
पूर्ण

अटल व्योम hp_aux_feedback_loop_gain_ramp(काष्ठा mt6359_priv *priv, bool up)
अणु
	पूर्णांक i, stage;
	पूर्णांक target = 0xf;

	/* Enable/Reduce HP aux feedback loop gain step by step */
	क्रम (i = 0; i <= target; i++) अणु
		stage = up ? i : target - i;
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON9,
				   0xf << 12, stage << 12);
		usleep_range(600, 650);
	पूर्ण
पूर्ण

अटल व्योम hp_in_pair_current(काष्ठा mt6359_priv *priv, bool increase)
अणु
	पूर्णांक i = 0, stage = 0;
	पूर्णांक target = 0x3;

	/* Set input dअगरf pair bias select (Hi-Fi mode) */
	अगर (priv->hp_hअगरi_mode) अणु
		/* Reduce HP aux feedback loop gain step by step */
		क्रम (i = 0; i <= target; i++) अणु
			stage = increase ? i : target - i;
			regmap_update_bits(priv->regmap,
					   MT6359_AUDDEC_ANA_CON10,
					   0x3 << 3, stage << 3);
			usleep_range(100, 150);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hp_pull_करोwn(काष्ठा mt6359_priv *priv, bool enable)
अणु
	पूर्णांक i;

	अगर (enable) अणु
		क्रम (i = 0x0; i <= 0x7; i++) अणु
			regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON2,
					   RG_HPPSHORT2VCM_VAUDP32_MASK_SFT,
					   i << RG_HPPSHORT2VCM_VAUDP32_SFT);
			usleep_range(100, 150);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0x7; i >= 0x0; i--) अणु
			regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON2,
					   RG_HPPSHORT2VCM_VAUDP32_MASK_SFT,
					   i << RG_HPPSHORT2VCM_VAUDP32_SFT);
			usleep_range(100, 150);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool is_valid_hp_pga_idx(पूर्णांक reg_idx)
अणु
	वापस (reg_idx >= DL_GAIN_8DB && reg_idx <= DL_GAIN_N_22DB) ||
	       reg_idx == DL_GAIN_N_40DB;
पूर्ण

अटल व्योम headset_volume_ramp(काष्ठा mt6359_priv *priv,
				पूर्णांक from, पूर्णांक to)
अणु
	पूर्णांक offset = 0, count = 1, reg_idx;

	अगर (!is_valid_hp_pga_idx(from) || !is_valid_hp_pga_idx(to)) अणु
		dev_warn(priv->dev, "%s(), volume index is not valid, from %d, to %d\n",
			 __func__, from, to);
		वापस;
	पूर्ण

	dev_dbg(priv->dev, "%s(), from %d, to %d\n", __func__, from, to);

	अगर (to > from)
		offset = to - from;
	अन्यथा
		offset = from - to;

	जबतक (offset > 0) अणु
		अगर (to > from)
			reg_idx = from + count;
		अन्यथा
			reg_idx = from - count;

		अगर (is_valid_hp_pga_idx(reg_idx)) अणु
			regmap_update_bits(priv->regmap,
					   MT6359_ZCD_CON2,
					   DL_GAIN_REG_MASK,
					   (reg_idx << 7) | reg_idx);
			usleep_range(600, 650);
		पूर्ण
		offset--;
		count++;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6359_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
			(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg;
	पूर्णांक index = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	चयन (mc->reg) अणु
	हाल MT6359_ZCD_CON2:
		regmap_पढ़ो(priv->regmap, MT6359_ZCD_CON2, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL] =
			(reg >> RG_AUDHPLGAIN_SFT) & RG_AUDHPLGAIN_MASK;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTR] =
			(reg >> RG_AUDHPRGAIN_SFT) & RG_AUDHPRGAIN_MASK;
		अवरोध;
	हाल MT6359_ZCD_CON1:
		regmap_पढ़ो(priv->regmap, MT6359_ZCD_CON1, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTL] =
			(reg >> RG_AUDLOLGAIN_SFT) & RG_AUDLOLGAIN_MASK;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTR] =
			(reg >> RG_AUDLORGAIN_SFT) & RG_AUDLORGAIN_MASK;
		अवरोध;
	हाल MT6359_ZCD_CON3:
		regmap_पढ़ो(priv->regmap, MT6359_ZCD_CON3, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HSOUTL] =
			(reg >> RG_AUDHSGAIN_SFT) & RG_AUDHSGAIN_MASK;
		अवरोध;
	हाल MT6359_AUDENC_ANA_CON0:
		regmap_पढ़ो(priv->regmap, MT6359_AUDENC_ANA_CON0, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP1] =
			(reg >> RG_AUDPREAMPLGAIN_SFT) & RG_AUDPREAMPLGAIN_MASK;
		अवरोध;
	हाल MT6359_AUDENC_ANA_CON1:
		regmap_पढ़ो(priv->regmap, MT6359_AUDENC_ANA_CON1, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP2] =
			(reg >> RG_AUDPREAMPRGAIN_SFT) & RG_AUDPREAMPRGAIN_MASK;
		अवरोध;
	हाल MT6359_AUDENC_ANA_CON2:
		regmap_पढ़ो(priv->regmap, MT6359_AUDENC_ANA_CON2, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP3] =
			(reg >> RG_AUDPREAMP3GAIN_SFT) & RG_AUDPREAMP3GAIN_MASK;
		अवरोध;
	पूर्ण

	dev_dbg(priv->dev, "%s(), name %s, reg(0x%x) = 0x%x, set index = %x\n",
		__func__, kcontrol->id.name, mc->reg, reg, index);

	वापस ret;
पूर्ण

/* MUX */

/* LOL MUX */
अटल स्थिर अक्षर * स्थिर lo_in_mux_map[] = अणु
	"Open", "Playback_L_DAC", "Playback", "Test Mode"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lo_in_mux_map_क्रमागत, SND_SOC_NOPM, 0, lo_in_mux_map);

अटल स्थिर काष्ठा snd_kcontrol_new lo_in_mux_control =
	SOC_DAPM_ENUM("LO Select", lo_in_mux_map_क्रमागत);

/*HP MUX */
अटल स्थिर अक्षर * स्थिर hp_in_mux_map[] = अणु
	"Open",
	"LoudSPK Playback",
	"Audio Playback",
	"Test Mode",
	"HP Impedance",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hp_in_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  hp_in_mux_map);

अटल स्थिर काष्ठा snd_kcontrol_new hp_in_mux_control =
	SOC_DAPM_ENUM("HP Select", hp_in_mux_map_क्रमागत);

/* RCV MUX */
अटल स्थिर अक्षर * स्थिर rcv_in_mux_map[] = अणु
	"Open", "Mute", "Voice Playback", "Test Mode"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rcv_in_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  rcv_in_mux_map);

अटल स्थिर काष्ठा snd_kcontrol_new rcv_in_mux_control =
	SOC_DAPM_ENUM("RCV Select", rcv_in_mux_map_क्रमागत);

/* DAC In MUX */
अटल स्थिर अक्षर * स्थिर dac_in_mux_map[] = अणु
	"Normal Path", "Sgen"
पूर्ण;

अटल पूर्णांक dac_in_mux_map_value[] = अणु
	0x0, 0x1,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(dac_in_mux_map_क्रमागत,
				  MT6359_AFE_TOP_CON0,
				  DL_SINE_ON_SFT,
				  DL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dac_in_mux_control =
	SOC_DAPM_ENUM("DAC Select", dac_in_mux_map_क्रमागत);

/* AIF Out MUX */
अटल SOC_VALUE_ENUM_SINGLE_DECL(aअगर_out_mux_map_क्रमागत,
				  MT6359_AFE_TOP_CON0,
				  UL_SINE_ON_SFT,
				  UL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर_out_mux_control =
	SOC_DAPM_ENUM("AIF Out Select", aअगर_out_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(aअगर2_out_mux_map_क्रमागत,
				  MT6359_AFE_TOP_CON0,
				  ADDA6_UL_SINE_ON_SFT,
				  ADDA6_UL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2_out_mux_control =
	SOC_DAPM_ENUM("AIF Out Select", aअगर2_out_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर ul_src_mux_map[] = अणु
	"AMIC",
	"DMIC",
पूर्ण;

अटल पूर्णांक ul_src_mux_map_value[] = अणु
	UL_SRC_MUX_AMIC,
	UL_SRC_MUX_DMIC,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(ul_src_mux_map_क्रमागत,
				  MT6359_AFE_UL_SRC_CON0_L,
				  UL_SDM_3_LEVEL_CTL_SFT,
				  UL_SDM_3_LEVEL_CTL_MASK,
				  ul_src_mux_map,
				  ul_src_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new ul_src_mux_control =
	SOC_DAPM_ENUM("UL_SRC_MUX Select", ul_src_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(ul2_src_mux_map_क्रमागत,
				  MT6359_AFE_ADDA6_UL_SRC_CON0_L,
				  ADDA6_UL_SDM_3_LEVEL_CTL_SFT,
				  ADDA6_UL_SDM_3_LEVEL_CTL_MASK,
				  ul_src_mux_map,
				  ul_src_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new ul2_src_mux_control =
	SOC_DAPM_ENUM("UL_SRC_MUX Select", ul2_src_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर miso_mux_map[] = अणु
	"UL1_CH1",
	"UL1_CH2",
	"UL2_CH1",
	"UL2_CH2",
पूर्ण;

अटल पूर्णांक miso_mux_map_value[] = अणु
	MISO_MUX_UL1_CH1,
	MISO_MUX_UL1_CH2,
	MISO_MUX_UL2_CH1,
	MISO_MUX_UL2_CH2,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(miso0_mux_map_क्रमागत,
				  MT6359_AFE_MTKAIF_MUX_CFG,
				  RG_ADDA_CH1_SEL_SFT,
				  RG_ADDA_CH1_SEL_MASK,
				  miso_mux_map,
				  miso_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new miso0_mux_control =
	SOC_DAPM_ENUM("MISO_MUX Select", miso0_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(miso1_mux_map_क्रमागत,
				  MT6359_AFE_MTKAIF_MUX_CFG,
				  RG_ADDA_CH2_SEL_SFT,
				  RG_ADDA_CH2_SEL_MASK,
				  miso_mux_map,
				  miso_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new miso1_mux_control =
	SOC_DAPM_ENUM("MISO_MUX Select", miso1_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(miso2_mux_map_क्रमागत,
				  MT6359_AFE_MTKAIF_MUX_CFG,
				  RG_ADDA6_CH1_SEL_SFT,
				  RG_ADDA6_CH1_SEL_MASK,
				  miso_mux_map,
				  miso_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new miso2_mux_control =
	SOC_DAPM_ENUM("MISO_MUX Select", miso2_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर dmic_mux_map[] = अणु
	"DMIC_DATA0",
	"DMIC_DATA1_L",
	"DMIC_DATA1_L_1",
	"DMIC_DATA1_R",
पूर्ण;

अटल पूर्णांक dmic_mux_map_value[] = अणु
	DMIC_MUX_DMIC_DATA0,
	DMIC_MUX_DMIC_DATA1_L,
	DMIC_MUX_DMIC_DATA1_L_1,
	DMIC_MUX_DMIC_DATA1_R,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(dmic0_mux_map_क्रमागत,
				  MT6359_AFE_MIC_ARRAY_CFG,
				  RG_DMIC_ADC1_SOURCE_SEL_SFT,
				  RG_DMIC_ADC1_SOURCE_SEL_MASK,
				  dmic_mux_map,
				  dmic_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dmic0_mux_control =
	SOC_DAPM_ENUM("DMIC_MUX Select", dmic0_mux_map_क्रमागत);

/* ul1 ch2 use RG_DMIC_ADC3_SOURCE_SEL */
अटल SOC_VALUE_ENUM_SINGLE_DECL(dmic1_mux_map_क्रमागत,
				  MT6359_AFE_MIC_ARRAY_CFG,
				  RG_DMIC_ADC3_SOURCE_SEL_SFT,
				  RG_DMIC_ADC3_SOURCE_SEL_MASK,
				  dmic_mux_map,
				  dmic_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dmic1_mux_control =
	SOC_DAPM_ENUM("DMIC_MUX Select", dmic1_mux_map_क्रमागत);

/* ul2 ch1 use RG_DMIC_ADC2_SOURCE_SEL */
अटल SOC_VALUE_ENUM_SINGLE_DECL(dmic2_mux_map_क्रमागत,
				  MT6359_AFE_MIC_ARRAY_CFG,
				  RG_DMIC_ADC2_SOURCE_SEL_SFT,
				  RG_DMIC_ADC2_SOURCE_SEL_MASK,
				  dmic_mux_map,
				  dmic_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dmic2_mux_control =
	SOC_DAPM_ENUM("DMIC_MUX Select", dmic2_mux_map_क्रमागत);

/* ADC L MUX */
अटल स्थिर अक्षर * स्थिर adc_left_mux_map[] = अणु
	"Idle", "AIN0", "Left Preamplifier", "Idle_1"
पूर्ण;

अटल पूर्णांक adc_mux_map_value[] = अणु
	ADC_MUX_IDLE,
	ADC_MUX_AIN0,
	ADC_MUX_PREAMPLIFIER,
	ADC_MUX_IDLE1,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_left_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON0,
				  RG_AUDADCLINPUTSEL_SFT,
				  RG_AUDADCLINPUTSEL_MASK,
				  adc_left_mux_map,
				  adc_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_left_mux_control =
	SOC_DAPM_ENUM("ADC L Select", adc_left_mux_map_क्रमागत);

/* ADC R MUX */
अटल स्थिर अक्षर * स्थिर adc_right_mux_map[] = अणु
	"Idle", "AIN0", "Right Preamplifier", "Idle_1"
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_right_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON1,
				  RG_AUDADCRINPUTSEL_SFT,
				  RG_AUDADCRINPUTSEL_MASK,
				  adc_right_mux_map,
				  adc_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_right_mux_control =
	SOC_DAPM_ENUM("ADC R Select", adc_right_mux_map_क्रमागत);

/* ADC 3 MUX */
अटल स्थिर अक्षर * स्थिर adc_3_mux_map[] = अणु
	"Idle", "AIN0", "Preamplifier", "Idle_1"
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_3_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON2,
				  RG_AUDADC3INPUTSEL_SFT,
				  RG_AUDADC3INPUTSEL_MASK,
				  adc_3_mux_map,
				  adc_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_3_mux_control =
	SOC_DAPM_ENUM("ADC 3 Select", adc_3_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर pga_l_mux_map[] = अणु
	"None", "AIN0", "AIN1"
पूर्ण;

अटल पूर्णांक pga_l_mux_map_value[] = अणु
	PGA_L_MUX_NONE,
	PGA_L_MUX_AIN0,
	PGA_L_MUX_AIN1
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_left_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON0,
				  RG_AUDPREAMPLINPUTSEL_SFT,
				  RG_AUDPREAMPLINPUTSEL_MASK,
				  pga_l_mux_map,
				  pga_l_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_left_mux_control =
	SOC_DAPM_ENUM("PGA L Select", pga_left_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर pga_r_mux_map[] = अणु
	"None", "AIN2", "AIN3", "AIN0"
पूर्ण;

अटल पूर्णांक pga_r_mux_map_value[] = अणु
	PGA_R_MUX_NONE,
	PGA_R_MUX_AIN2,
	PGA_R_MUX_AIN3,
	PGA_R_MUX_AIN0
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_right_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON1,
				  RG_AUDPREAMPRINPUTSEL_SFT,
				  RG_AUDPREAMPRINPUTSEL_MASK,
				  pga_r_mux_map,
				  pga_r_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_right_mux_control =
	SOC_DAPM_ENUM("PGA R Select", pga_right_mux_map_क्रमागत);

अटल स्थिर अक्षर * स्थिर pga_3_mux_map[] = अणु
	"None", "AIN3", "AIN2"
पूर्ण;

अटल पूर्णांक pga_3_mux_map_value[] = अणु
	PGA_3_MUX_NONE,
	PGA_3_MUX_AIN3,
	PGA_3_MUX_AIN2
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_3_mux_map_क्रमागत,
				  MT6359_AUDENC_ANA_CON2,
				  RG_AUDPREAMP3INPUTSEL_SFT,
				  RG_AUDPREAMP3INPUTSEL_MASK,
				  pga_3_mux_map,
				  pga_3_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_3_mux_control =
	SOC_DAPM_ENUM("PGA 3 Select", pga_3_mux_map_क्रमागत);

अटल पूर्णांक mt_sgen_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* sdm audio fअगरo घड़ी घातer on */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON2, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON0, 0xcba1);
		/* sdm घातer on */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON2, 0x0003);
		/* sdm fअगरo enable */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON2, 0x000b);

		regmap_update_bits(priv->regmap, MT6359_AFE_SGEN_CFG0,
				   0xff3f,
				   0x0000);
		regmap_update_bits(priv->regmap, MT6359_AFE_SGEN_CFG1,
				   0xffff,
				   0x0001);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* DL scrambler disabling sequence */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON2, 0x0000);
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON0, 0xcba0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_hp_enable(काष्ठा mt6359_priv *priv)
अणु
	अगर (priv->hp_hअगरi_mode) अणु
		/* Set HP DR bias current optimization, 010: 6uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON11,
				   DRBIAS_HP_MASK_SFT,
				   DRBIAS_6UA << DRBIAS_HP_SFT);
		/* Set HP & ZCD bias current optimization */
		/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_ZCD_MASK_SFT,
				   IBIAS_ZCD_4UA << IBIAS_ZCD_SFT);
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_HP_MASK_SFT,
				   IBIAS_5UA << IBIAS_HP_SFT);
	पूर्ण अन्यथा अणु
		/* Set HP DR bias current optimization, 001: 5uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON11,
				   DRBIAS_HP_MASK_SFT,
				   DRBIAS_5UA << DRBIAS_HP_SFT);
		/* Set HP & ZCD bias current optimization */
		/* 00: ZCD: 3uA, HP/HS/LO: 4uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_ZCD_MASK_SFT,
				   IBIAS_ZCD_3UA << IBIAS_ZCD_SFT);
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_HP_MASK_SFT,
				   IBIAS_4UA << IBIAS_HP_SFT);
	पूर्ण

	/* HP damp circuit enable */
	/* Enable HPRN/HPLN output 4K to VCM */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON10, 0x0087);

	/* HP Feedback Cap select 2'b00: 15pF */
	/* क्रम >= 96KHz sampling rate: 2'b01: 10.5pF */
	अगर (priv->dl_rate[MT6359_AIF_1] >= 96000)
		regmap_update_bits(priv->regmap,
				   MT6359_AUDDEC_ANA_CON4,
				   RG_AUDHPHFCOMPBUFGAINSEL_VAUDP32_MASK_SFT,
				   0x1 << RG_AUDHPHFCOMPBUFGAINSEL_VAUDP32_SFT);
	अन्यथा
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON4, 0x0000);

	/* Set HPP/N STB enhance circuits */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON2, 0xf133);

	/* Enable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x000c);
	/* Enable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x003c);
	/* Enable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0c00);
	/* Enable HP driver bias circuits */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x30c0);
	/* Enable HP driver core circuits */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x30f0);
	/* Short HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x00fc);

	/* Increase HP input pair current to HPM step by step */
	hp_in_pair_current(priv, true);

	/* Enable HP मुख्य CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0e00);
	/* Disable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0200);

	/* Enable HP मुख्य output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x00ff);
	/* Enable HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, true);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, true);
	/* Disable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x77cf);

	/* apply volume setting */
	headset_volume_ramp(priv,
			    DL_GAIN_N_22DB,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL]);

	/* Disable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x77c3);
	/* Unलघु HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x7703);
	usleep_range(100, 120);

	/* Enable AUD_CLK */
	mt6359_set_decoder_clk(priv, true);

	/* Enable Audio DAC  */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x30ff);
	अगर (priv->hp_hअगरi_mode) अणु
		/* Enable low-noise mode of DAC */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0xf201);
	पूर्ण अन्यथा अणु
		/* Disable low-noise mode of DAC */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0xf200);
	पूर्ण
	usleep_range(100, 120);

	/* Switch HPL MUX to audio DAC */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x32ff);
	/* Switch HPR MUX to audio DAC */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x3aff);

	/* Disable Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, false);
पूर्ण

अटल व्योम mtk_hp_disable(काष्ठा mt6359_priv *priv)
अणु
	/* Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, true);

	/* HPR/HPL mux to खोलो */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   0x0f00, 0x0000);

	/* Disable low-noise mode of DAC */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON9,
			   0x0001, 0x0000);

	/* Disable Audio DAC */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   0x000f, 0x0000);

	/* Disable AUD_CLK */
	mt6359_set_decoder_clk(priv, false);

	/* Short HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x77c3);
	/* Enable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x77cf);

	/* decrease HPL/R gain to normal gain step by step */
	headset_volume_ramp(priv,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL],
			    DL_GAIN_N_22DB);

	/* Enable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x77ff);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, false);

	/* decrease HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, false);

	/* Disable HP मुख्य output stage */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1, 0x3, 0x0);

	/* Enable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0e01);

	/* Disable HP मुख्य CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0c01);

	/* Decrease HP input pair current to 2'b00 step by step */
	hp_in_pair_current(priv, false);

	/* Unलघु HP मुख्य output to HP aux output stage */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1,
			   0x3 << 6, 0x0);

	/* Disable HP driver core circuits */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   0x3 << 4, 0x0);

	/* Disable HP driver bias circuits */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   0x3 << 6, 0x0);

	/* Disable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x201);

	/* Disable HP aux feedback loop */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1,
			   0x3 << 4, 0x0);

	/* Disable HP aux output stage */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON1,
			   0x3 << 2, 0x0);
पूर्ण

अटल पूर्णांक mt_hp_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol,
		       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);
	पूर्णांक device = DEVICE_HP;

	dev_dbg(priv->dev, "%s(), event 0x%x, dev_counter[DEV_HP] %d, mux %u\n",
		__func__, event, priv->dev_counter[device], mux);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		priv->dev_counter[device]++;
		अगर (mux == HP_MUX_HP)
			mtk_hp_enable(priv);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		priv->dev_counter[device]--;
		अगर (mux == HP_MUX_HP)
			mtk_hp_disable(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_rcv_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol,
			पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x, mux %u\n",
		__func__, event, dapm_kcontrol_get_value(w->kcontrols[0]));

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Disable handset लघु-circuit protection */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON6, 0x0010);

		/* Set RCV DR bias current optimization, 010: 6uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON11,
				   DRBIAS_HS_MASK_SFT,
				   DRBIAS_6UA << DRBIAS_HS_SFT);
		/* Set RCV & ZCD bias current optimization */
		/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_ZCD_MASK_SFT,
				   IBIAS_ZCD_4UA << IBIAS_ZCD_SFT);
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_HS_MASK_SFT,
				   IBIAS_5UA << IBIAS_HS_SFT);

		/* Set HS STB enhance circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON6, 0x0090);

		/* Set HS output stage (3'b111 = 8x) */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON10, 0x7000);

		/* Enable HS driver bias circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON6, 0x0092);
		/* Enable HS driver core circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON6, 0x0093);

		/* Set HS gain to normal gain step by step */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON3,
			     priv->ana_gain[AUDIO_ANALOG_VOLUME_HSOUTL]);

		/* Enable AUD_CLK */
		mt6359_set_decoder_clk(priv, true);

		/* Enable Audio DAC  */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON0, 0x0009);
		/* Enable low-noise mode of DAC */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON9, 0x0001);
		/* Switch HS MUX to audio DAC */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON6, 0x009b);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* HS mux to खोलो */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON6,
				   RG_AUDHSMUXINPUTSEL_VAUDP32_MASK_SFT,
				   RCV_MUX_OPEN);

		/* Disable Audio DAC */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
				   0x000f, 0x0000);

		/* Disable AUD_CLK */
		mt6359_set_decoder_clk(priv, false);

		/* decrease HS gain to minimum gain step by step */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON3, DL_GAIN_N_40DB);

		/* Disable HS driver core circuits */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON6,
				   RG_AUDHSPWRUP_VAUDP32_MASK_SFT, 0x0);

		/* Disable HS driver bias circuits */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON6,
				   RG_AUDHSPWRUP_IBIAS_VAUDP32_MASK_SFT, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_lo_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol,
		       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x, mux %u\n",
		__func__, event, dapm_kcontrol_get_value(w->kcontrols[0]));

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Disable handset लघु-circuit protection */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x0010);

		/* Set LO DR bias current optimization, 010: 6uA */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON11,
				   DRBIAS_LO_MASK_SFT,
				   DRBIAS_6UA << DRBIAS_LO_SFT);
		/* Set LO & ZCD bias current optimization */
		/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
		अगर (priv->dev_counter[DEVICE_HP] == 0)
			regmap_update_bits(priv->regmap,
					   MT6359_AUDDEC_ANA_CON12,
					   IBIAS_ZCD_MASK_SFT,
					   IBIAS_ZCD_4UA << IBIAS_ZCD_SFT);

		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON12,
				   IBIAS_LO_MASK_SFT,
				   IBIAS_5UA << IBIAS_LO_SFT);

		/* Set LO STB enhance circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x0110);

		/* Enable LO driver bias circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x0112);
		/* Enable LO driver core circuits */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x0113);

		/* Set LO gain to normal gain step by step */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON1,
			     priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTL]);

		/* Enable AUD_CLK */
		mt6359_set_decoder_clk(priv, true);

		/* Enable Audio DAC (3rd DAC) */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x3113);
		/* Enable low-noise mode of DAC */
		अगर (priv->dev_counter[DEVICE_HP] == 0)
			regmap_ग_लिखो(priv->regmap,
				     MT6359_AUDDEC_ANA_CON9, 0x0001);
		/* Switch LOL MUX to audio 3rd DAC */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON7, 0x311b);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* Switch LOL MUX to खोलो */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON7,
				   RG_AUDLOLMUXINPUTSEL_VAUDP32_MASK_SFT,
				   LO_MUX_OPEN);

		/* Disable Audio DAC */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
				   0x000f, 0x0000);

		/* Disable AUD_CLK */
		mt6359_set_decoder_clk(priv, false);

		/* decrease LO gain to minimum gain step by step */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON1, DL_GAIN_N_40DB);

		/* Disable LO driver core circuits */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON7,
				   RG_AUDLOLPWRUP_VAUDP32_MASK_SFT, 0x0);

		/* Disable LO driver bias circuits */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON7,
				   RG_AUDLOLPWRUP_IBIAS_VAUDP32_MASK_SFT, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_clk_gen_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol,
				पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* ADC CLK from CLKGEN (6.5MHz) */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKRSTB_MASK_SFT,
				   0x1 << RG_AUDADCCLKRSTB_SFT);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKSOURCE_MASK_SFT, 0x0);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKSEL_MASK_SFT, 0x0);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKGENMODE_MASK_SFT,
				   0x1 << RG_AUDADCCLKGENMODE_SFT);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKSOURCE_MASK_SFT, 0x0);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKSEL_MASK_SFT, 0x0);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKGENMODE_MASK_SFT, 0x0);
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON5,
				   RG_AUDADCCLKRSTB_MASK_SFT, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_dcc_clk_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* DCC 50k CLK (from 26M) */
		/* MT6359_AFE_DCCLK_CFG0, bit 3 क्रम dm ck swap */
		regmap_update_bits(priv->regmap, MT6359_AFE_DCCLK_CFG0,
				   0xfff7, 0x2062);
		regmap_update_bits(priv->regmap, MT6359_AFE_DCCLK_CFG0,
				   0xfff7, 0x2060);
		regmap_update_bits(priv->regmap, MT6359_AFE_DCCLK_CFG0,
				   0xfff7, 0x2061);

		regmap_ग_लिखो(priv->regmap, MT6359_AFE_DCCLK_CFG1, 0x0100);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(priv->regmap, MT6359_AFE_DCCLK_CFG0,
				   0xfff7, 0x2060);
		regmap_update_bits(priv->regmap, MT6359_AFE_DCCLK_CFG0,
				   0xfff7, 0x2062);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_0_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mic_type = priv->mux_select[MUX_MIC_TYPE_0];

	dev_dbg(priv->dev, "%s(), event 0x%x, mic_type %d\n",
		__func__, event, mic_type);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (mic_type) अणु
		हाल MIC_TYPE_MUX_DCC_ECM_DIFF:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON15,
					   0xff00, 0x7700);
			अवरोध;
		हाल MIC_TYPE_MUX_DCC_ECM_SINGLE:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON15,
					   0xff00, 0x1100);
			अवरोध;
		शेष:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON15,
					   0xff00, 0x0000);
			अवरोध;
		पूर्ण

		/* DMIC enable */
		regmap_ग_लिखो(priv->regmap,
			     MT6359_AUDENC_ANA_CON14, 0x0004);
		/* MISBIAS0 = 1P9V */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON15,
				   RG_AUDMICBIAS0VREF_MASK_SFT,
				   MIC_BIAS_1P9 << RG_AUDMICBIAS0VREF_SFT);
		/* normal घातer select */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON15,
				   RG_AUDMICBIAS0LOWPEN_MASK_SFT,
				   0 << RG_AUDMICBIAS0LOWPEN_SFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable MICBIAS0, MISBIAS0 = 1P7V */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDENC_ANA_CON15, 0x0000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_1_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mic_type = priv->mux_select[MUX_MIC_TYPE_1];

	dev_dbg(priv->dev, "%s(), event 0x%x, mic_type %d\n",
		__func__, event, mic_type);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* MISBIAS1 = 2P6V */
		अगर (mic_type == MIC_TYPE_MUX_DCC_ECM_SINGLE)
			regmap_ग_लिखो(priv->regmap,
				     MT6359_AUDENC_ANA_CON16, 0x0160);
		अन्यथा
			regmap_ग_लिखो(priv->regmap,
				     MT6359_AUDENC_ANA_CON16, 0x0060);

		/* normal घातer select */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON16,
				   RG_AUDMICBIAS1LOWPEN_MASK_SFT,
				   0 << RG_AUDMICBIAS1LOWPEN_SFT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_2_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mic_type = priv->mux_select[MUX_MIC_TYPE_2];

	dev_dbg(priv->dev, "%s(), event 0x%x, mic_type %d\n",
		__func__, event, mic_type);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (mic_type) अणु
		हाल MIC_TYPE_MUX_DCC_ECM_DIFF:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON17,
					   0xff00, 0x7700);
			अवरोध;
		हाल MIC_TYPE_MUX_DCC_ECM_SINGLE:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON17,
					   0xff00, 0x1100);
			अवरोध;
		शेष:
			regmap_update_bits(priv->regmap,
					   MT6359_AUDENC_ANA_CON17,
					   0xff00, 0x0000);
			अवरोध;
		पूर्ण

		/* MISBIAS2 = 1P9V */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON17,
				   RG_AUDMICBIAS2VREF_MASK_SFT,
				   MIC_BIAS_1P9 << RG_AUDMICBIAS2VREF_SFT);
		/* normal घातer select */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON17,
				   RG_AUDMICBIAS2LOWPEN_MASK_SFT,
				   0 << RG_AUDMICBIAS2LOWPEN_SFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable MICBIAS2, MISBIAS0 = 1P7V */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDENC_ANA_CON17, 0x0000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_mtkaअगर_tx_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt6359_mtkaअगर_tx_enable(priv);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		mt6359_mtkaअगर_tx_disable(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_ul_src_dmic_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol,
				पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* UL dmic setting */
		अगर (priv->dmic_one_wire_mode)
			regmap_ग_लिखो(priv->regmap, MT6359_AFE_UL_SRC_CON0_H,
				     0x0400);
		अन्यथा
			regmap_ग_लिखो(priv->regmap, MT6359_AFE_UL_SRC_CON0_H,
				     0x0080);
		/* शेष one wire, 3.25M */
		regmap_update_bits(priv->regmap, MT6359_AFE_UL_SRC_CON0_L,
				   0xfffc, 0x0000);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_ग_लिखो(priv->regmap,
			     MT6359_AFE_UL_SRC_CON0_H, 0x0000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_ul_src_34_dmic_event(काष्ठा snd_soc_dapm_widget *w,
				   काष्ठा snd_kcontrol *kcontrol,
				   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* शेष two wire, 3.25M */
		regmap_ग_लिखो(priv->regmap,
			     MT6359_AFE_ADDA6_L_SRC_CON0_H, 0x0080);
		regmap_update_bits(priv->regmap, MT6359_AFE_ADDA6_UL_SRC_CON0_L,
				   0xfffc, 0x0000);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_ग_लिखो(priv->regmap,
			     MT6359_AFE_ADDA6_L_SRC_CON0_H, 0x0000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_l_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio L preamplअगरier DCC preअक्षरge off */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLDCPRECHARGE_MASK_SFT,
				   0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_r_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio R preamplअगरier DCC preअक्षरge off */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRDCPRECHARGE_MASK_SFT,
				   0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_3_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio R preamplअगरier DCC preअक्षरge off */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON2,
				   RG_AUDPREAMP3DCPRECHARGE_MASK_SFT,
				   0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_l_mux_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), mux %d\n", __func__, mux);
	priv->mux_select[MUX_PGA_L] = mux >> RG_AUDPREAMPLINPUTSEL_SFT;
	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_r_mux_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), mux %d\n", __func__, mux);
	priv->mux_select[MUX_PGA_R] = mux >> RG_AUDPREAMPRINPUTSEL_SFT;
	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_3_mux_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), mux %d\n", __func__, mux);
	priv->mux_select[MUX_PGA_3] = mux >> RG_AUDPREAMP3INPUTSEL_SFT;
	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_l_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक mic_gain_l = priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP1];
	अचिन्हित पूर्णांक mux_pga = priv->mux_select[MUX_PGA_L];
	अचिन्हित पूर्णांक mic_type;

	चयन (mux_pga) अणु
	हाल PGA_L_MUX_AIN0:
		mic_type = priv->mux_select[MUX_MIC_TYPE_0];
		अवरोध;
	हाल PGA_L_MUX_AIN1:
		mic_type = priv->mux_select[MUX_MIC_TYPE_1];
		अवरोध;
	शेष:
		dev_err(priv->dev, "%s(), invalid pga mux %d\n",
			__func__, mux_pga);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (IS_DCC_BASE(mic_type)) अणु
			/* Audio L preamplअगरier DCC preअक्षरge */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON0,
					   RG_AUDPREAMPLDCPRECHARGE_MASK_SFT,
					   0x1 << RG_AUDPREAMPLDCPRECHARGE_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* set mic pga gain */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLGAIN_MASK_SFT,
				   mic_gain_l << RG_AUDPREAMPLGAIN_SFT);

		अगर (IS_DCC_BASE(mic_type)) अणु
			/* L preamplअगरier DCCEN */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON0,
					   RG_AUDPREAMPLDCCEN_MASK_SFT,
					   0x1 << RG_AUDPREAMPLDCCEN_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* L preamplअगरier DCCEN */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLDCCEN_MASK_SFT,
				   0x0 << RG_AUDPREAMPLDCCEN_SFT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_r_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक mic_gain_r = priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP2];
	अचिन्हित पूर्णांक mux_pga = priv->mux_select[MUX_PGA_R];
	अचिन्हित पूर्णांक mic_type;

	चयन (mux_pga) अणु
	हाल PGA_R_MUX_AIN0:
		mic_type = priv->mux_select[MUX_MIC_TYPE_0];
		अवरोध;
	हाल PGA_R_MUX_AIN2:
	हाल PGA_R_MUX_AIN3:
		mic_type = priv->mux_select[MUX_MIC_TYPE_2];
		अवरोध;
	शेष:
		dev_err(priv->dev, "%s(), invalid pga mux %d\n",
			__func__, mux_pga);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (IS_DCC_BASE(mic_type)) अणु
			/* Audio R preamplअगरier DCC preअक्षरge */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON1,
					   RG_AUDPREAMPRDCPRECHARGE_MASK_SFT,
					   0x1 << RG_AUDPREAMPRDCPRECHARGE_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* set mic pga gain */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRGAIN_MASK_SFT,
				   mic_gain_r << RG_AUDPREAMPRGAIN_SFT);

		अगर (IS_DCC_BASE(mic_type)) अणु
			/* R preamplअगरier DCCEN */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON1,
					   RG_AUDPREAMPRDCCEN_MASK_SFT,
					   0x1 << RG_AUDPREAMPRDCCEN_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* R preamplअगरier DCCEN */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRDCCEN_MASK_SFT,
				   0x0 << RG_AUDPREAMPRDCCEN_SFT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_3_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक mic_gain_3 = priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP3];
	अचिन्हित पूर्णांक mux_pga = priv->mux_select[MUX_PGA_3];
	अचिन्हित पूर्णांक mic_type;

	चयन (mux_pga) अणु
	हाल PGA_3_MUX_AIN2:
	हाल PGA_3_MUX_AIN3:
		mic_type = priv->mux_select[MUX_MIC_TYPE_2];
		अवरोध;
	शेष:
		dev_err(priv->dev, "%s(), invalid pga mux %d\n",
			__func__, mux_pga);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (IS_DCC_BASE(mic_type)) अणु
			/* Audio 3 preamplअगरier DCC preअक्षरge */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON2,
					   RG_AUDPREAMP3DCPRECHARGE_MASK_SFT,
					   0x1 << RG_AUDPREAMP3DCPRECHARGE_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* set mic pga gain */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON2,
				   RG_AUDPREAMP3GAIN_MASK_SFT,
				   mic_gain_3 << RG_AUDPREAMP3GAIN_SFT);

		अगर (IS_DCC_BASE(mic_type)) अणु
			/* 3 preamplअगरier DCCEN */
			regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON2,
					   RG_AUDPREAMP3DCCEN_MASK_SFT,
					   0x1 << RG_AUDPREAMP3DCCEN_SFT);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 3 preamplअगरier DCCEN */
		regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON2,
				   RG_AUDPREAMP3DCCEN_MASK_SFT,
				   0x0 << RG_AUDPREAMP3DCCEN_SFT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* It is based on hw's control sequenece to add some delay when PMU/PMD */
अटल पूर्णांक mt_delay_250_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_PRE_PMD:
		usleep_range(250, 270);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_delay_100_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_PRE_PMD:
		usleep_range(100, 120);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_hp_pull_करोwn_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol,
				 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		hp_pull_करोwn(priv, true);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		hp_pull_करोwn(priv, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_hp_mute_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Set HPR/HPL gain to -22dB */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON2, DL_GAIN_N_22DB_REG);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Set HPL/HPR gain to mute */
		regmap_ग_लिखो(priv->regmap, MT6359_ZCD_CON2, DL_GAIN_N_40DB_REG);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_hp_damp_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable HP damping circuit & HPN 4K load */
		/* reset CMFB PW level */
		regmap_ग_लिखो(priv->regmap, MT6359_AUDDEC_ANA_CON10, 0x0000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_esd_resist_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Reduce ESD resistance of AU_REFN */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON2,
				   RG_AUDREFN_DERES_EN_VAUDP32_MASK_SFT,
				   0x1 << RG_AUDREFN_DERES_EN_VAUDP32_SFT);
		usleep_range(250, 270);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Increase ESD resistance of AU_REFN */
		regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON2,
				   RG_AUDREFN_DERES_EN_VAUDP32_MASK_SFT, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_sdm_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol,
			पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* sdm audio fअगरo घड़ी घातer on */
		regmap_update_bits(priv->regmap, MT6359_AFUNC_AUD_CON2,
				   0xfffd, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON0, 0xcba1);
		/* sdm घातer on */
		regmap_update_bits(priv->regmap, MT6359_AFUNC_AUD_CON2,
				   0xfffd, 0x0003);
		/* sdm fअगरo enable */
		regmap_update_bits(priv->regmap, MT6359_AFUNC_AUD_CON2,
				   0xfffd, 0x000B);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* DL scrambler disabling sequence */
		regmap_update_bits(priv->regmap, MT6359_AFUNC_AUD_CON2,
				   0xfffd, 0x0000);
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON0, 0xcba0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_sdm_3rd_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* sdm audio fअगरo घड़ी घातer on */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON11, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON9, 0xcba1);
		/* sdm घातer on */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON11, 0x0003);
		/* sdm fअगरo enable */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON11, 0x000b);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* DL scrambler disabling sequence */
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON11, 0x0000);
		regmap_ग_लिखो(priv->regmap, MT6359_AFUNC_AUD_CON9, 0xcba0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_ncp_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol,
			पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_ग_लिखो(priv->regmap, MT6359_AFE_NCP_CFG0, 0xc800);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* DAPM Widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget mt6359_dapm_widमाला_लो[] = अणु
	/* Global Supply*/
	SND_SOC_DAPM_SUPPLY_S("CLK_BUF", SUPPLY_SEQ_CLK_BUF,
			      MT6359_DCXO_CW12,
			      RG_XO_AUDIO_EN_M_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDGLB", SUPPLY_SEQ_AUD_GLB,
			      MT6359_AUDDEC_ANA_CON13,
			      RG_AUDGLB_PWRDN_VA32_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("CLKSQ Audio", SUPPLY_SEQ_CLKSQ,
			      MT6359_AUDENC_ANA_CON23,
			      RG_CLKSQ_EN_SFT, 0, शून्य, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY_S("AUDNCP_CK", SUPPLY_SEQ_TOP_CK,
			      MT6359_AUD_TOP_CKPDN_CON0,
			      RG_AUDNCP_CK_PDN_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ZCD13M_CK", SUPPLY_SEQ_TOP_CK,
			      MT6359_AUD_TOP_CKPDN_CON0,
			      RG_ZCD13M_CK_PDN_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUD_CK", SUPPLY_SEQ_TOP_CK_LAST,
			      MT6359_AUD_TOP_CKPDN_CON0,
			      RG_AUD_CK_PDN_SFT, 1, mt_delay_250_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY_S("AUDIF_CK", SUPPLY_SEQ_TOP_CK,
			      MT6359_AUD_TOP_CKPDN_CON0,
			      RG_AUDIF_CK_PDN_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("vaud18", 0, 0),

	/* Digital Clock */
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_AFE_CTL", SUPPLY_SEQ_AUD_TOP_LAST,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_AFE_CTL_SFT, 1,
			      mt_delay_250_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_DAC_CTL", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_DAC_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_ADC_CTL", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_ADC_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_ADDA6_ADC_CTL", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_ADDA6_ADC_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_I2S_DL", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_I2S_DL_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PWR_CLK", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PWR_CLK_DIS_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PDN_AFE_TESTMODEL", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_AFE_TESTMODEL_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PDN_RESERVED", SUPPLY_SEQ_AUD_TOP,
			      MT6359_AUDIO_TOP_CON0,
			      PDN_RESERVED_SFT, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("SDM", SUPPLY_SEQ_DL_SDM,
			      SND_SOC_NOPM, 0, 0,
			      mt_sdm_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("SDM_3RD", SUPPLY_SEQ_DL_SDM,
			      SND_SOC_NOPM, 0, 0,
			      mt_sdm_3rd_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* ch123 share SDM FIFO CLK */
	SND_SOC_DAPM_SUPPLY_S("SDM_FIFO_CLK", SUPPLY_SEQ_DL_SDM_FIFO_CLK,
			      MT6359_AFUNC_AUD_CON2,
			      CCI_AFIFO_CLK_PWDB_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("NCP", SUPPLY_SEQ_DL_NCP,
			      MT6359_AFE_NCP_CFG0,
			      RG_NCP_ON_SFT, 0,
			      mt_ncp_event,
			      SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_SUPPLY("DL Digital Clock", SND_SOC_NOPM,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DL Digital Clock CH_1_2", SND_SOC_NOPM,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DL Digital Clock CH_3", SND_SOC_NOPM,
			    0, 0, शून्य, 0),

	/* AFE ON */
	SND_SOC_DAPM_SUPPLY_S("AFE_ON", SUPPLY_SEQ_AFE,
			      MT6359_AFE_UL_DL_CON0, AFE_ON_SFT, 0,
			      शून्य, 0),

	/* AIF Rx*/
	SND_SOC_DAPM_AIF_IN("AIF_RX", "AIF1 Playback", 0,
			    SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("AIF2_RX", "AIF2 Playback", 0,
			    SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY_S("AFE_DL_SRC", SUPPLY_SEQ_DL_SRC,
			      MT6359_AFE_DL_SRC2_CON0_L,
			      DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0,
			      शून्य, 0),

	/* DL Supply */
	SND_SOC_DAPM_SUPPLY("DL Power Supply", SND_SOC_NOPM,
			    0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ESD_RESIST", SUPPLY_SEQ_DL_ESD_RESIST,
			      SND_SOC_NOPM,
			      0, 0,
			      mt_esd_resist_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("LDO", SUPPLY_SEQ_DL_LDO,
			      MT6359_AUDDEC_ANA_CON14,
			      RG_LCLDO_DEC_EN_VA32_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("LDO_REMOTE", SUPPLY_SEQ_DL_LDO_REMOTE_SENSE,
			      MT6359_AUDDEC_ANA_CON14,
			      RG_LCLDO_DEC_REMOTE_SENSE_VA18_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("NV_REGULATOR", SUPPLY_SEQ_DL_NV,
			      MT6359_AUDDEC_ANA_CON14,
			      RG_NVREG_EN_VAUDP32_SFT, 0,
			      mt_delay_100_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY_S("IBIST", SUPPLY_SEQ_DL_IBIST,
			      MT6359_AUDDEC_ANA_CON12,
			      RG_AUDIBIASPWRDN_VAUDP32_SFT, 1,
			      शून्य, 0),

	/* DAC */
	SND_SOC_DAPM_MUX("DAC In Mux", SND_SOC_NOPM, 0, 0, &dac_in_mux_control),

	SND_SOC_DAPM_DAC("DACL", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DACR", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC_3RD", शून्य, SND_SOC_NOPM, 0, 0),

	/* Headphone */
	SND_SOC_DAPM_MUX_E("HP Mux", SND_SOC_NOPM, 0, 0,
			   &hp_in_mux_control,
			   mt_hp_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY("HP_Supply", SND_SOC_NOPM,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("HP_PULL_DOWN", SUPPLY_SEQ_HP_PULL_DOWN,
			      SND_SOC_NOPM,
			      0, 0,
			      mt_hp_pull_करोwn_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("HP_MUTE", SUPPLY_SEQ_HP_MUTE,
			      SND_SOC_NOPM,
			      0, 0,
			      mt_hp_mute_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("HP_DAMP", SUPPLY_SEQ_HP_DAMPING_OFF_RESET_CMFB,
			      SND_SOC_NOPM,
			      0, 0,
			      mt_hp_damp_event,
			      SND_SOC_DAPM_POST_PMD),

	/* Receiver */
	SND_SOC_DAPM_MUX_E("RCV Mux", SND_SOC_NOPM, 0, 0,
			   &rcv_in_mux_control,
			   mt_rcv_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	/* LOL */
	SND_SOC_DAPM_MUX_E("LOL Mux", SND_SOC_NOPM, 0, 0,
			   &lo_in_mux_control,
			   mt_lo_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("Receiver"),
	SND_SOC_DAPM_OUTPUT("Headphone L"),
	SND_SOC_DAPM_OUTPUT("Headphone R"),
	SND_SOC_DAPM_OUTPUT("Headphone L Ext Spk Amp"),
	SND_SOC_DAPM_OUTPUT("Headphone R Ext Spk Amp"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L"),

	/* SGEN */
	SND_SOC_DAPM_SUPPLY("SGEN DL Enable", MT6359_AFE_SGEN_CFG0,
			    SGEN_DAC_EN_CTL_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SGEN MUTE", MT6359_AFE_SGEN_CFG0,
			    SGEN_MUTE_SW_CTL_SFT, 1,
			    mt_sgen_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("SGEN DL SRC", MT6359_AFE_DL_SRC2_CON0_L,
			    DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("SGEN DL"),

	/* Uplinks */
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0,
			     SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0,
			     SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY_S("ADC_CLKGEN", SUPPLY_SEQ_ADC_CLKGEN,
			      SND_SOC_NOPM, 0, 0,
			      mt_adc_clk_gen_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY_S("DCC_CLK", SUPPLY_SEQ_DCC_CLK,
			      SND_SOC_NOPM, 0, 0,
			      mt_dcc_clk_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* Uplinks MUX */
	SND_SOC_DAPM_MUX("AIF Out Mux", SND_SOC_NOPM, 0, 0,
			 &aअगर_out_mux_control),

	SND_SOC_DAPM_MUX("AIF2 Out Mux", SND_SOC_NOPM, 0, 0,
			 &aअगर2_out_mux_control),

	SND_SOC_DAPM_SUPPLY("AIFTX_Supply", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("MTKAIF_TX", SUPPLY_SEQ_UL_MTKAIF,
			      SND_SOC_NOPM, 0, 0,
			      mt_mtkaअगर_tx_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("UL_SRC", SUPPLY_SEQ_UL_SRC,
			      MT6359_AFE_UL_SRC_CON0_L,
			      UL_SRC_ON_TMP_CTL_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("UL_SRC_DMIC", SUPPLY_SEQ_UL_SRC_DMIC,
			      SND_SOC_NOPM, 0, 0,
			      mt_ul_src_dmic_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("UL_SRC_34", SUPPLY_SEQ_UL_SRC,
			      MT6359_AFE_ADDA6_UL_SRC_CON0_L,
			      ADDA6_UL_SRC_ON_TMP_CTL_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("UL_SRC_34_DMIC", SUPPLY_SEQ_UL_SRC_DMIC,
			      SND_SOC_NOPM, 0, 0,
			      mt_ul_src_34_dmic_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("MISO0_MUX", SND_SOC_NOPM, 0, 0, &miso0_mux_control),
	SND_SOC_DAPM_MUX("MISO1_MUX", SND_SOC_NOPM, 0, 0, &miso1_mux_control),
	SND_SOC_DAPM_MUX("MISO2_MUX", SND_SOC_NOPM, 0, 0, &miso2_mux_control),

	SND_SOC_DAPM_MUX("UL_SRC_MUX", SND_SOC_NOPM, 0, 0,
			 &ul_src_mux_control),
	SND_SOC_DAPM_MUX("UL2_SRC_MUX", SND_SOC_NOPM, 0, 0,
			 &ul2_src_mux_control),

	SND_SOC_DAPM_MUX("DMIC0_MUX", SND_SOC_NOPM, 0, 0, &dmic0_mux_control),
	SND_SOC_DAPM_MUX("DMIC1_MUX", SND_SOC_NOPM, 0, 0, &dmic1_mux_control),
	SND_SOC_DAPM_MUX("DMIC2_MUX", SND_SOC_NOPM, 0, 0, &dmic2_mux_control),

	SND_SOC_DAPM_MUX_E("ADC_L_Mux", SND_SOC_NOPM, 0, 0,
			   &adc_left_mux_control, शून्य, 0),
	SND_SOC_DAPM_MUX_E("ADC_R_Mux", SND_SOC_NOPM, 0, 0,
			   &adc_right_mux_control, शून्य, 0),
	SND_SOC_DAPM_MUX_E("ADC_3_Mux", SND_SOC_NOPM, 0, 0,
			   &adc_3_mux_control, शून्य, 0),

	SND_SOC_DAPM_ADC("ADC_L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC_R", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC_3", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY_S("ADC_L_EN", SUPPLY_SEQ_UL_ADC,
			      MT6359_AUDENC_ANA_CON0,
			      RG_AUDADCLPWRUP_SFT, 0,
			      mt_adc_l_event,
			      SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY_S("ADC_R_EN", SUPPLY_SEQ_UL_ADC,
			      MT6359_AUDENC_ANA_CON1,
			      RG_AUDADCRPWRUP_SFT, 0,
			      mt_adc_r_event,
			      SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY_S("ADC_3_EN", SUPPLY_SEQ_UL_ADC,
			      MT6359_AUDENC_ANA_CON2,
			      RG_AUDADC3PWRUP_SFT, 0,
			      mt_adc_3_event,
			      SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_MUX_E("PGA_L_Mux", SND_SOC_NOPM, 0, 0,
			   &pga_left_mux_control,
			   mt_pga_l_mux_event,
			   SND_SOC_DAPM_WILL_PMU),
	SND_SOC_DAPM_MUX_E("PGA_R_Mux", SND_SOC_NOPM, 0, 0,
			   &pga_right_mux_control,
			   mt_pga_r_mux_event,
			   SND_SOC_DAPM_WILL_PMU),
	SND_SOC_DAPM_MUX_E("PGA_3_Mux", SND_SOC_NOPM, 0, 0,
			   &pga_3_mux_control,
			   mt_pga_3_mux_event,
			   SND_SOC_DAPM_WILL_PMU),

	SND_SOC_DAPM_PGA("PGA_L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA_R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA_3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("PGA_L_EN", SUPPLY_SEQ_UL_PGA,
			      MT6359_AUDENC_ANA_CON0,
			      RG_AUDPREAMPLON_SFT, 0,
			      mt_pga_l_event,
			      SND_SOC_DAPM_PRE_PMU |
			      SND_SOC_DAPM_POST_PMU |
			      SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("PGA_R_EN", SUPPLY_SEQ_UL_PGA,
			      MT6359_AUDENC_ANA_CON1,
			      RG_AUDPREAMPRON_SFT, 0,
			      mt_pga_r_event,
			      SND_SOC_DAPM_PRE_PMU |
			      SND_SOC_DAPM_POST_PMU |
			      SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("PGA_3_EN", SUPPLY_SEQ_UL_PGA,
			      MT6359_AUDENC_ANA_CON2,
			      RG_AUDPREAMP3ON_SFT, 0,
			      mt_pga_3_event,
			      SND_SOC_DAPM_PRE_PMU |
			      SND_SOC_DAPM_POST_PMU |
			      SND_SOC_DAPM_POST_PMD),

	/* UL input */
	SND_SOC_DAPM_INPUT("AIN0"),
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),

	SND_SOC_DAPM_INPUT("AIN0_DMIC"),
	SND_SOC_DAPM_INPUT("AIN2_DMIC"),
	SND_SOC_DAPM_INPUT("AIN3_DMIC"),

	/* mic bias */
	SND_SOC_DAPM_SUPPLY_S("MIC_BIAS_0", SUPPLY_SEQ_MIC_BIAS,
			      MT6359_AUDENC_ANA_CON15,
			      RG_AUDPWDBMICBIAS0_SFT, 0,
			      mt_mic_bias_0_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("MIC_BIAS_1", SUPPLY_SEQ_MIC_BIAS,
			      MT6359_AUDENC_ANA_CON16,
			      RG_AUDPWDBMICBIAS1_SFT, 0,
			      mt_mic_bias_1_event,
			      SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY_S("MIC_BIAS_2", SUPPLY_SEQ_MIC_BIAS,
			      MT6359_AUDENC_ANA_CON17,
			      RG_AUDPWDBMICBIAS2_SFT, 0,
			      mt_mic_bias_2_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* dmic */
	SND_SOC_DAPM_SUPPLY_S("DMIC_0", SUPPLY_SEQ_DMIC,
			      MT6359_AUDENC_ANA_CON13,
			      RG_AUDDIGMICEN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC_1", SUPPLY_SEQ_DMIC,
			      MT6359_AUDENC_ANA_CON14,
			      RG_AUDDIGMIC1EN_SFT, 0,
			      शून्य, 0),
पूर्ण;

अटल पूर्णांक mt_dcc_clk_connect(काष्ठा snd_soc_dapm_widget *source,
			      काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	अगर (IS_DCC_BASE(priv->mux_select[MUX_MIC_TYPE_0]) ||
	    IS_DCC_BASE(priv->mux_select[MUX_MIC_TYPE_1]) ||
	    IS_DCC_BASE(priv->mux_select[MUX_MIC_TYPE_2]))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route mt6359_dapm_routes[] = अणु
	/* Capture */
	अणु"AIFTX_Supply", शून्य, "CLK_BUF"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "vaud18"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDGLB"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "CLKSQ Audio"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUD_CK"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIF_CK"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_PDN_RESERVED"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_I2S_DL"पूर्ण,
	/*
	 * *_ADC_CTL should enable only अगर UL_SRC in use,
	 * but dm ck may be needed even UL_SRC_x not in use
	 */
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_ADC_CTL"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AUDIO_TOP_ADDA6_ADC_CTL"पूर्ण,
	अणु"AIFTX_Supply", शून्य, "AFE_ON"पूर्ण,

	/* ul ch 12 */
	अणु"AIF1TX", शून्य, "AIF Out Mux"पूर्ण,
	अणु"AIF1TX", शून्य, "AIFTX_Supply"पूर्ण,
	अणु"AIF1TX", शून्य, "MTKAIF_TX"पूर्ण,

	अणु"AIF2TX", शून्य, "AIF2 Out Mux"पूर्ण,
	अणु"AIF2TX", शून्य, "AIFTX_Supply"पूर्ण,
	अणु"AIF2TX", शून्य, "MTKAIF_TX"पूर्ण,

	अणु"AIF Out Mux", "Normal Path", "MISO0_MUX"पूर्ण,
	अणु"AIF Out Mux", "Normal Path", "MISO1_MUX"पूर्ण,
	अणु"AIF2 Out Mux", "Normal Path", "MISO2_MUX"पूर्ण,

	अणु"MISO0_MUX", "UL1_CH1", "UL_SRC_MUX"पूर्ण,
	अणु"MISO0_MUX", "UL1_CH2", "UL_SRC_MUX"पूर्ण,
	अणु"MISO0_MUX", "UL2_CH1", "UL2_SRC_MUX"पूर्ण,
	अणु"MISO0_MUX", "UL2_CH2", "UL2_SRC_MUX"पूर्ण,

	अणु"MISO1_MUX", "UL1_CH1", "UL_SRC_MUX"पूर्ण,
	अणु"MISO1_MUX", "UL1_CH2", "UL_SRC_MUX"पूर्ण,
	अणु"MISO1_MUX", "UL2_CH1", "UL2_SRC_MUX"पूर्ण,
	अणु"MISO1_MUX", "UL2_CH2", "UL2_SRC_MUX"पूर्ण,

	अणु"MISO2_MUX", "UL1_CH1", "UL_SRC_MUX"पूर्ण,
	अणु"MISO2_MUX", "UL1_CH2", "UL_SRC_MUX"पूर्ण,
	अणु"MISO2_MUX", "UL2_CH1", "UL2_SRC_MUX"पूर्ण,
	अणु"MISO2_MUX", "UL2_CH2", "UL2_SRC_MUX"पूर्ण,

	अणु"UL_SRC_MUX", "AMIC", "ADC_L"पूर्ण,
	अणु"UL_SRC_MUX", "AMIC", "ADC_R"पूर्ण,
	अणु"UL_SRC_MUX", "DMIC", "DMIC0_MUX"पूर्ण,
	अणु"UL_SRC_MUX", "DMIC", "DMIC1_MUX"पूर्ण,
	अणु"UL_SRC_MUX", शून्य, "UL_SRC"पूर्ण,

	अणु"UL2_SRC_MUX", "AMIC", "ADC_3"पूर्ण,
	अणु"UL2_SRC_MUX", "DMIC", "DMIC2_MUX"पूर्ण,
	अणु"UL2_SRC_MUX", शून्य, "UL_SRC_34"पूर्ण,

	अणु"DMIC0_MUX", "DMIC_DATA0", "AIN0_DMIC"पूर्ण,
	अणु"DMIC0_MUX", "DMIC_DATA1_L", "AIN2_DMIC"पूर्ण,
	अणु"DMIC0_MUX", "DMIC_DATA1_L_1", "AIN2_DMIC"पूर्ण,
	अणु"DMIC0_MUX", "DMIC_DATA1_R", "AIN3_DMIC"पूर्ण,
	अणु"DMIC1_MUX", "DMIC_DATA0", "AIN0_DMIC"पूर्ण,
	अणु"DMIC1_MUX", "DMIC_DATA1_L", "AIN2_DMIC"पूर्ण,
	अणु"DMIC1_MUX", "DMIC_DATA1_L_1", "AIN2_DMIC"पूर्ण,
	अणु"DMIC1_MUX", "DMIC_DATA1_R", "AIN3_DMIC"पूर्ण,
	अणु"DMIC2_MUX", "DMIC_DATA0", "AIN0_DMIC"पूर्ण,
	अणु"DMIC2_MUX", "DMIC_DATA1_L", "AIN2_DMIC"पूर्ण,
	अणु"DMIC2_MUX", "DMIC_DATA1_L_1", "AIN2_DMIC"पूर्ण,
	अणु"DMIC2_MUX", "DMIC_DATA1_R", "AIN3_DMIC"पूर्ण,

	अणु"DMIC0_MUX", शून्य, "UL_SRC_DMIC"पूर्ण,
	अणु"DMIC1_MUX", शून्य, "UL_SRC_DMIC"पूर्ण,
	अणु"DMIC2_MUX", शून्य, "UL_SRC_34_DMIC"पूर्ण,

	अणु"AIN0_DMIC", शून्य, "DMIC_0"पूर्ण,
	अणु"AIN2_DMIC", शून्य, "DMIC_1"पूर्ण,
	अणु"AIN3_DMIC", शून्य, "DMIC_1"पूर्ण,
	अणु"AIN0_DMIC", शून्य, "MIC_BIAS_0"पूर्ण,
	अणु"AIN2_DMIC", शून्य, "MIC_BIAS_2"पूर्ण,
	अणु"AIN3_DMIC", शून्य, "MIC_BIAS_2"पूर्ण,

	/* adc */
	अणु"ADC_L", शून्य, "ADC_L_Mux"पूर्ण,
	अणु"ADC_L", शून्य, "ADC_CLKGEN"पूर्ण,
	अणु"ADC_L", शून्य, "ADC_L_EN"पूर्ण,
	अणु"ADC_R", शून्य, "ADC_R_Mux"पूर्ण,
	अणु"ADC_R", शून्य, "ADC_CLKGEN"पूर्ण,
	अणु"ADC_R", शून्य, "ADC_R_EN"पूर्ण,
	/*
	 * amic fअगरo ch1/2 clk from ADC_L,
	 * enable ADC_L even use ADC_R only
	 */
	अणु"ADC_R", शून्य, "ADC_L_EN"पूर्ण,
	अणु"ADC_3", शून्य, "ADC_3_Mux"पूर्ण,
	अणु"ADC_3", शून्य, "ADC_CLKGEN"पूर्ण,
	अणु"ADC_3", शून्य, "ADC_3_EN"पूर्ण,

	अणु"ADC_L_Mux", "Left Preamplifier", "PGA_L"पूर्ण,
	अणु"ADC_R_Mux", "Right Preamplifier", "PGA_R"पूर्ण,
	अणु"ADC_3_Mux", "Preamplifier", "PGA_3"पूर्ण,

	अणु"PGA_L", शून्य, "PGA_L_Mux"पूर्ण,
	अणु"PGA_L", शून्य, "PGA_L_EN"पूर्ण,
	अणु"PGA_R", शून्य, "PGA_R_Mux"पूर्ण,
	अणु"PGA_R", शून्य, "PGA_R_EN"पूर्ण,
	अणु"PGA_3", शून्य, "PGA_3_Mux"पूर्ण,
	अणु"PGA_3", शून्य, "PGA_3_EN"पूर्ण,

	अणु"PGA_L", शून्य, "DCC_CLK", mt_dcc_clk_connectपूर्ण,
	अणु"PGA_R", शून्य, "DCC_CLK", mt_dcc_clk_connectपूर्ण,
	अणु"PGA_3", शून्य, "DCC_CLK", mt_dcc_clk_connectपूर्ण,

	अणु"PGA_L_Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA_L_Mux", "AIN1", "AIN1"पूर्ण,

	अणु"PGA_R_Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA_R_Mux", "AIN2", "AIN2"पूर्ण,
	अणु"PGA_R_Mux", "AIN3", "AIN3"पूर्ण,

	अणु"PGA_3_Mux", "AIN2", "AIN2"पूर्ण,
	अणु"PGA_3_Mux", "AIN3", "AIN3"पूर्ण,

	अणु"AIN0", शून्य, "MIC_BIAS_0"पूर्ण,
	अणु"AIN1", शून्य, "MIC_BIAS_1"पूर्ण,
	अणु"AIN2", शून्य, "MIC_BIAS_0"पूर्ण,
	अणु"AIN2", शून्य, "MIC_BIAS_2"पूर्ण,
	अणु"AIN3", शून्य, "MIC_BIAS_2"पूर्ण,

	/* DL Supply */
	अणु"DL Power Supply", शून्य, "CLK_BUF"पूर्ण,
	अणु"DL Power Supply", शून्य, "vaud18"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDGLB"पूर्ण,
	अणु"DL Power Supply", शून्य, "CLKSQ Audio"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDNCP_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "ZCD13M_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUD_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDIF_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "ESD_RESIST"पूर्ण,
	अणु"DL Power Supply", शून्य, "LDO"पूर्ण,
	अणु"DL Power Supply", शून्य, "LDO_REMOTE"पूर्ण,
	अणु"DL Power Supply", शून्य, "NV_REGULATOR"पूर्ण,
	अणु"DL Power Supply", शून्य, "IBIST"पूर्ण,

	/* DL Digital Supply */
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_DAC_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_PDN_RESERVED"पूर्ण,
	अणु"DL Digital Clock", शून्य, "SDM_FIFO_CLK"पूर्ण,
	अणु"DL Digital Clock", शून्य, "NCP"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AFE_ON"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AFE_DL_SRC"पूर्ण,

	अणु"DL Digital Clock CH_1_2", शून्य, "DL Digital Clock"पूर्ण,
	अणु"DL Digital Clock CH_1_2", शून्य, "SDM"पूर्ण,

	अणु"DL Digital Clock CH_3", शून्य, "DL Digital Clock"पूर्ण,
	अणु"DL Digital Clock CH_3", शून्य, "SDM_3RD"पूर्ण,

	अणु"AIF_RX", शून्य, "DL Digital Clock CH_1_2"पूर्ण,

	अणु"AIF2_RX", शून्य, "DL Digital Clock CH_3"पूर्ण,

	/* DL Path */
	अणु"DAC In Mux", "Normal Path", "AIF_RX"पूर्ण,
	अणु"DAC In Mux", "Sgen", "SGEN DL"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL SRC"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN MUTE"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL Enable"पूर्ण,
	अणु"SGEN DL", शून्य, "DL Digital Clock CH_1_2"पूर्ण,
	अणु"SGEN DL", शून्य, "DL Digital Clock CH_3"पूर्ण,
	अणु"SGEN DL", शून्य, "AUDIO_TOP_PDN_AFE_TESTMODEL"पूर्ण,

	अणु"DACL", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACL", शून्य, "DL Power Supply"पूर्ण,

	अणु"DACR", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACR", शून्य, "DL Power Supply"पूर्ण,

	/* DAC 3RD */
	अणु"DAC In Mux", "Normal Path", "AIF2_RX"पूर्ण,
	अणु"DAC_3RD", शून्य, "DAC In Mux"पूर्ण,
	अणु"DAC_3RD", शून्य, "DL Power Supply"पूर्ण,

	/* Lineout Path */
	अणु"LOL Mux", "Playback", "DAC_3RD"पूर्ण,
	अणु"LINEOUT L", शून्य, "LOL Mux"पूर्ण,

	/* Headphone Path */
	अणु"HP_Supply", शून्य, "HP_PULL_DOWN"पूर्ण,
	अणु"HP_Supply", शून्य, "HP_MUTE"पूर्ण,
	अणु"HP_Supply", शून्य, "HP_DAMP"पूर्ण,
	अणु"HP Mux", शून्य, "HP_Supply"पूर्ण,

	अणु"HP Mux", "Audio Playback", "DACL"पूर्ण,
	अणु"HP Mux", "Audio Playback", "DACR"पूर्ण,
	अणु"HP Mux", "HP Impedance", "DACL"पूर्ण,
	अणु"HP Mux", "HP Impedance", "DACR"पूर्ण,
	अणु"HP Mux", "LoudSPK Playback", "DACL"पूर्ण,
	अणु"HP Mux", "LoudSPK Playback", "DACR"पूर्ण,

	अणु"Headphone L", शून्य, "HP Mux"पूर्ण,
	अणु"Headphone R", शून्य, "HP Mux"पूर्ण,
	अणु"Headphone L Ext Spk Amp", शून्य, "HP Mux"पूर्ण,
	अणु"Headphone R Ext Spk Amp", शून्य, "HP Mux"पूर्ण,

	/* Receiver Path */
	अणु"RCV Mux", "Voice Playback", "DACL"पूर्ण,
	अणु"Receiver", शून्य, "RCV Mux"पूर्ण,
पूर्ण;

अटल पूर्णांक mt6359_codec_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *cmpnt = dai->component;
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक id = dai->id;

	dev_dbg(priv->dev, "%s(), id %d, substream->stream %d, rate %d, number %d\n",
		__func__, id, substream->stream, rate, substream->number);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		priv->dl_rate[id] = rate;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		priv->ul_rate[id] = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक mt6359_codec_dai_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *cmpnt = dai->component;
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s stream %d\n", __func__, substream->stream);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mt6359_set_playback_gpio(priv);
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mt6359_set_capture_gpio(priv);

	वापस 0;
पूर्ण

अटल व्योम mt6359_codec_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *cmpnt = dai->component;
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s stream %d\n", __func__, substream->stream);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mt6359_reset_playback_gpio(priv);
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mt6359_reset_capture_gpio(priv);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mt6359_codec_dai_ops = अणु
	.hw_params = mt6359_codec_dai_hw_params,
	.startup = mt6359_codec_dai_startup,
	.shutकरोwn = mt6359_codec_dai_shutकरोwn,
पूर्ण;

#घोषणा MT6359_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |\
			SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |\
			SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_U24_BE |\
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE |\
			SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_U32_BE)

अटल काष्ठा snd_soc_dai_driver mt6359_dai_driver[] = अणु
	अणु
		.id = MT6359_AIF_1,
		.name = "mt6359-snd-codec-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6359_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6359_FORMATS,
		पूर्ण,
		.ops = &mt6359_codec_dai_ops,
	पूर्ण,
	अणु
		.id = MT6359_AIF_2,
		.name = "mt6359-snd-codec-aif2",
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6359_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_48000,
			.क्रमmats = MT6359_FORMATS,
		पूर्ण,
		.ops = &mt6359_codec_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mt6359_codec_init_reg(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	/* enable clk buf */
	regmap_update_bits(priv->regmap, MT6359_DCXO_CW12,
			   0x1 << RG_XO_AUDIO_EN_M_SFT,
			   0x1 << RG_XO_AUDIO_EN_M_SFT);

	/* set those not controlled by dapm widget */

	/* audio clk source from पूर्णांकernal dcxo */
	regmap_update_bits(priv->regmap, MT6359_AUDENC_ANA_CON23,
			   RG_CLKSQ_IN_SEL_TEST_MASK_SFT,
			   0x0);

	/* Disable HeadphoneL/HeadphoneR लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   RG_AUDHPLSCDISABLE_VAUDP32_MASK_SFT,
			   0x1 << RG_AUDHPLSCDISABLE_VAUDP32_SFT);
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON0,
			   RG_AUDHPRSCDISABLE_VAUDP32_MASK_SFT,
			   0x1 << RG_AUDHPRSCDISABLE_VAUDP32_SFT);
	/* Disable voice लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON6,
			   RG_AUDHSSCDISABLE_VAUDP32_MASK_SFT,
			   0x1 << RG_AUDHSSCDISABLE_VAUDP32_SFT);
	/* disable LO buffer left लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6359_AUDDEC_ANA_CON7,
			   RG_AUDLOLSCDISABLE_VAUDP32_MASK_SFT,
			   0x1 << RG_AUDLOLSCDISABLE_VAUDP32_SFT);

	/* set gpio */
	mt6359_reset_playback_gpio(priv);
	mt6359_reset_capture_gpio(priv);

	/* hp hअगरi mode, शेष normal mode */
	priv->hp_hअगरi_mode = 0;

	/* Disable AUD_ZCD */
	zcd_disable(priv);

	/* disable clk buf */
	regmap_update_bits(priv->regmap, MT6359_DCXO_CW12,
			   0x1 << RG_XO_AUDIO_EN_M_SFT,
			   0x0 << RG_XO_AUDIO_EN_M_SFT);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6359_codec_probe(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6359_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	snd_soc_component_init_regmap(cmpnt, priv->regmap);

	वापस mt6359_codec_init_reg(cmpnt);
पूर्ण

अटल व्योम mt6359_codec_हटाओ(काष्ठा snd_soc_component *cmpnt)
अणु
	snd_soc_component_निकास_regmap(cmpnt);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(hp_playback_tlv, -2200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(playback_tlv, -1000, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(capture_tlv, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mt6359_snd_controls[] = अणु
	/* dl pga gain */
	SOC_DOUBLE_EXT_TLV("Headset Volume",
			   MT6359_ZCD_CON2, 0, 7, 0x1E, 0,
			   snd_soc_get_volsw, mt6359_put_volsw,
			   hp_playback_tlv),
	SOC_DOUBLE_EXT_TLV("Lineout Volume",
			   MT6359_ZCD_CON1, 0, 7, 0x12, 0,
			   snd_soc_get_volsw, mt6359_put_volsw, playback_tlv),
	SOC_SINGLE_EXT_TLV("Handset Volume",
			   MT6359_ZCD_CON3, 0, 0x12, 0,
			   snd_soc_get_volsw, mt6359_put_volsw, playback_tlv),

	/* ul pga gain */
	SOC_SINGLE_EXT_TLV("PGA1 Volume",
			   MT6359_AUDENC_ANA_CON0, RG_AUDPREAMPLGAIN_SFT, 4, 0,
			   snd_soc_get_volsw, mt6359_put_volsw, capture_tlv),
	SOC_SINGLE_EXT_TLV("PGA2 Volume",
			   MT6359_AUDENC_ANA_CON1, RG_AUDPREAMPRGAIN_SFT, 4, 0,
			   snd_soc_get_volsw, mt6359_put_volsw, capture_tlv),
	SOC_SINGLE_EXT_TLV("PGA3 Volume",
			   MT6359_AUDENC_ANA_CON2, RG_AUDPREAMP3GAIN_SFT, 4, 0,
			   snd_soc_get_volsw, mt6359_put_volsw, capture_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mt6359_soc_component_driver = अणु
	.name = CODEC_MT6359_NAME,
	.probe = mt6359_codec_probe,
	.हटाओ = mt6359_codec_हटाओ,
	.controls = mt6359_snd_controls,
	.num_controls = ARRAY_SIZE(mt6359_snd_controls),
	.dapm_widमाला_लो = mt6359_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt6359_dapm_widमाला_लो),
	.dapm_routes = mt6359_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt6359_dapm_routes),
पूर्ण;

अटल पूर्णांक mt6359_parse_dt(काष्ठा mt6359_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = priv->dev;
	काष्ठा device_node *np;

	np = of_get_child_by_name(dev->parent->of_node, "mt6359codec");
	अगर (!np)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(np, "mediatek,dmic-mode",
				   &priv->dmic_one_wire_mode);
	अगर (ret) अणु
		dev_info(priv->dev,
			 "%s() failed to read dmic-mode, use default (0)\n",
			 __func__);
		priv->dmic_one_wire_mode = 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "mediatek,mic-type-0",
				   &priv->mux_select[MUX_MIC_TYPE_0]);
	अगर (ret) अणु
		dev_info(priv->dev,
			 "%s() failed to read mic-type-0, use default (%d)\n",
			 __func__, MIC_TYPE_MUX_IDLE);
		priv->mux_select[MUX_MIC_TYPE_0] = MIC_TYPE_MUX_IDLE;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "mediatek,mic-type-1",
				   &priv->mux_select[MUX_MIC_TYPE_1]);
	अगर (ret) अणु
		dev_info(priv->dev,
			 "%s() failed to read mic-type-1, use default (%d)\n",
			 __func__, MIC_TYPE_MUX_IDLE);
		priv->mux_select[MUX_MIC_TYPE_1] = MIC_TYPE_MUX_IDLE;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "mediatek,mic-type-2",
				   &priv->mux_select[MUX_MIC_TYPE_2]);
	अगर (ret) अणु
		dev_info(priv->dev,
			 "%s() failed to read mic-type-2, use default (%d)\n",
			 __func__, MIC_TYPE_MUX_IDLE);
		priv->mux_select[MUX_MIC_TYPE_2] = MIC_TYPE_MUX_IDLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6359_platक्रमm_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6359_priv *priv;
	पूर्णांक ret;
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);

	dev_dbg(&pdev->dev, "%s(), dev name %s\n",
		__func__, dev_name(&pdev->dev));

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = mt6397->regmap;
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	dev_set_drvdata(&pdev->dev, priv);
	priv->dev = &pdev->dev;

	ret = mt6359_parse_dt(priv);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "%s() failed to parse dts\n", __func__);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &mt6359_soc_component_driver,
					       mt6359_dai_driver,
					       ARRAY_SIZE(mt6359_dai_driver));
पूर्ण

अटल काष्ठा platक्रमm_driver mt6359_platक्रमm_driver = अणु
	.driver = अणु
		.name = "mt6359-sound",
	पूर्ण,
	.probe = mt6359_platक्रमm_driver_probe,
पूर्ण;

module_platक्रमm_driver(mt6359_platक्रमm_driver)

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT6359 ALSA SoC codec driver");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_AUTHOR("Eason Yen <eason.yen@mediatek.com>");
MODULE_LICENSE("GPL v2");
