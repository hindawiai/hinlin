<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6358.c  --  mt6358 ALSA SoC audio codec driver
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "mt6358.h"

क्रमागत अणु
	AUDIO_ANALOG_VOLUME_HSOUTL,
	AUDIO_ANALOG_VOLUME_HSOUTR,
	AUDIO_ANALOG_VOLUME_HPOUTL,
	AUDIO_ANALOG_VOLUME_HPOUTR,
	AUDIO_ANALOG_VOLUME_LINEOUTL,
	AUDIO_ANALOG_VOLUME_LINEOUTR,
	AUDIO_ANALOG_VOLUME_MICAMP1,
	AUDIO_ANALOG_VOLUME_MICAMP2,
	AUDIO_ANALOG_VOLUME_TYPE_MAX
पूर्ण;

क्रमागत अणु
	MUX_ADC_L,
	MUX_ADC_R,
	MUX_PGA_L,
	MUX_PGA_R,
	MUX_MIC_TYPE,
	MUX_HP_L,
	MUX_HP_R,
	MUX_NUM,
पूर्ण;

क्रमागत अणु
	DEVICE_HP,
	DEVICE_LO,
	DEVICE_RCV,
	DEVICE_MIC1,
	DEVICE_MIC2,
	DEVICE_NUM
पूर्ण;

/* Supply widget subseq */
क्रमागत अणु
	/* common */
	SUPPLY_SEQ_CLK_BUF,
	SUPPLY_SEQ_AUD_GLB,
	SUPPLY_SEQ_CLKSQ,
	SUPPLY_SEQ_VOW_AUD_LPW,
	SUPPLY_SEQ_AUD_VOW,
	SUPPLY_SEQ_VOW_CLK,
	SUPPLY_SEQ_VOW_LDO,
	SUPPLY_SEQ_TOP_CK,
	SUPPLY_SEQ_TOP_CK_LAST,
	SUPPLY_SEQ_AUD_TOP,
	SUPPLY_SEQ_AUD_TOP_LAST,
	SUPPLY_SEQ_AFE,
	/* capture */
	SUPPLY_SEQ_ADC_SUPPLY,
पूर्ण;

क्रमागत अणु
	CH_L = 0,
	CH_R,
	NUM_CH,
पूर्ण;

#घोषणा REG_STRIDE 2

काष्ठा mt6358_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक dl_rate;
	अचिन्हित पूर्णांक ul_rate;

	पूर्णांक ana_gain[AUDIO_ANALOG_VOLUME_TYPE_MAX];
	अचिन्हित पूर्णांक mux_select[MUX_NUM];

	पूर्णांक dev_counter[DEVICE_NUM];

	पूर्णांक mtkaअगर_protocol;

	काष्ठा regulator *avdd_reg;

	पूर्णांक wov_enabled;

	अचिन्हित पूर्णांक dmic_one_wire_mode;
पूर्ण;

पूर्णांक mt6358_set_mtkaअगर_protocol(काष्ठा snd_soc_component *cmpnt,
			       पूर्णांक mtkaअगर_protocol)
अणु
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	priv->mtkaअगर_protocol = mtkaअगर_protocol;
	वापस 0;
पूर्ण

अटल व्योम playback_gpio_set(काष्ठा mt6358_priv *priv)
अणु
	/* set gpio mosi mode */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2_CLR,
			   0x01f8, 0x01f8);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2_SET,
			   0xffff, 0x0249);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2,
			   0xffff, 0x0249);
पूर्ण

अटल व्योम playback_gpio_reset(काष्ठा mt6358_priv *priv)
अणु
	/* set pad_aud_*_mosi to GPIO mode and dir input
	 * reason:
	 * pad_aud_dat_mosi*, because the pin is used as boot strap
	 * करोn't clean clk/sync, क्रम mtkaअगर protocol 2
	 */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2_CLR,
			   0x01f8, 0x01f8);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2,
			   0x01f8, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_सूची0,
			   0xf << 8, 0x0);
पूर्ण

अटल व्योम capture_gpio_set(काष्ठा mt6358_priv *priv)
अणु
	/* set gpio miso mode */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3_CLR,
			   0xffff, 0xffff);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3_SET,
			   0xffff, 0x0249);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3,
			   0xffff, 0x0249);
पूर्ण

अटल व्योम capture_gpio_reset(काष्ठा mt6358_priv *priv)
अणु
	/* set pad_aud_*_miso to GPIO mode and dir input
	 * reason:
	 * pad_aud_clk_miso, because when playback only the miso_clk
	 * will also have 26m, so will have घातer leak
	 * pad_aud_dat_miso*, because the pin is used as boot strap
	 */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3_CLR,
			   0xffff, 0xffff);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_सूची0,
			   0xf << 12, 0x0);
पूर्ण

/* use only when not govern by DAPM */
अटल पूर्णांक mt6358_set_dcxo(काष्ठा mt6358_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6358_DCXO_CW14,
			   0x1 << RG_XO_AUDIO_EN_M_SFT,
			   (enable ? 1 : 0) << RG_XO_AUDIO_EN_M_SFT);
	वापस 0;
पूर्ण

/* use only when not govern by DAPM */
अटल पूर्णांक mt6358_set_clksq(काष्ठा mt6358_priv *priv, bool enable)
अणु
	/* audio clk source from पूर्णांकernal dcxo */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON6,
			   RG_CLKSQ_IN_SEL_TEST_MASK_SFT,
			   0x0);

	/* Enable/disable CLKSQ 26MHz */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON6,
			   RG_CLKSQ_EN_MASK_SFT,
			   (enable ? 1 : 0) << RG_CLKSQ_EN_SFT);
	वापस 0;
पूर्ण

/* use only when not govern by DAPM */
अटल पूर्णांक mt6358_set_aud_global_bias(काष्ठा mt6358_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
			   RG_AUDGLB_PWRDN_VA28_MASK_SFT,
			   (enable ? 0 : 1) << RG_AUDGLB_PWRDN_VA28_SFT);
	वापस 0;
पूर्ण

/* use only when not govern by DAPM */
अटल पूर्णांक mt6358_set_topck(काष्ठा mt6358_priv *priv, bool enable)
अणु
	regmap_update_bits(priv->regmap, MT6358_AUD_TOP_CKPDN_CON0,
			   0x0066, enable ? 0x0 : 0x66);
	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_mtkaअगर_tx_enable(काष्ठा mt6358_priv *priv)
अणु
	चयन (priv->mtkaअगर_protocol) अणु
	हाल MT6358_MTKAIF_PROTOCOL_2_CLK_P2:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0010);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3800);
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3900);
		अवरोध;
	हाल MT6358_MTKAIF_PROTOCOL_2:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0010);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		अवरोध;
	हाल MT6358_MTKAIF_PROTOCOL_1:
	शेष:
		/* MTKAIF TX क्रमmat setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0000);
		/* enable aud_pad TX fअगरos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_mtkaअगर_tx_disable(काष्ठा mt6358_priv *priv)
अणु
	/* disable aud_pad TX fअगरos */
	regmap_update_bits(priv->regmap, MT6358_AFE_AUD_PAD_TOP,
			   0xff00, 0x3000);
	वापस 0;
पूर्ण

पूर्णांक mt6358_mtkaअगर_calibration_enable(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	playback_gpio_set(priv);
	capture_gpio_set(priv);
	mt6358_mtkaअगर_tx_enable(priv);

	mt6358_set_dcxo(priv, true);
	mt6358_set_aud_global_bias(priv, true);
	mt6358_set_clksq(priv, true);
	mt6358_set_topck(priv, true);

	/* set dat_miso_loopback on */
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT,
			   1 << RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT,
			   1 << RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT);
	वापस 0;
पूर्ण

पूर्णांक mt6358_mtkaअगर_calibration_disable(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	/* set dat_miso_loopback off */
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT);

	mt6358_set_topck(priv, false);
	mt6358_set_clksq(priv, false);
	mt6358_set_aud_global_bias(priv, false);
	mt6358_set_dcxo(priv, false);

	mt6358_mtkaअगर_tx_disable(priv);
	playback_gpio_reset(priv);
	capture_gpio_reset(priv);
	वापस 0;
पूर्ण

पूर्णांक mt6358_set_mtkaअगर_calibration_phase(काष्ठा snd_soc_component *cmpnt,
					पूर्णांक phase_1, पूर्णांक phase_2)
अणु
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT,
			   phase_1 << RG_AUD_PAD_TOP_PHASE_MODE_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT,
			   phase_2 << RG_AUD_PAD_TOP_PHASE_MODE2_SFT);
	वापस 0;
पूर्ण

/* dl pga gain */
क्रमागत अणु
	DL_GAIN_8DB = 0,
	DL_GAIN_0DB = 8,
	DL_GAIN_N_1DB = 9,
	DL_GAIN_N_10DB = 18,
	DL_GAIN_N_40DB = 0x1f,
पूर्ण;

#घोषणा DL_GAIN_N_10DB_REG (DL_GAIN_N_10DB << 7 | DL_GAIN_N_10DB)
#घोषणा DL_GAIN_N_40DB_REG (DL_GAIN_N_40DB << 7 | DL_GAIN_N_40DB)
#घोषणा DL_GAIN_REG_MASK 0x0f9f

अटल व्योम hp_zcd_disable(काष्ठा mt6358_priv *priv)
अणु
	regmap_ग_लिखो(priv->regmap, MT6358_ZCD_CON0, 0x0000);
पूर्ण

अटल व्योम hp_मुख्य_output_ramp(काष्ठा mt6358_priv *priv, bool up)
अणु
	पूर्णांक i, stage;
	पूर्णांक target = 7;

	/* Enable/Reduce HPL/R मुख्य output stage step by step */
	क्रम (i = 0; i <= target; i++) अणु
		stage = up ? i : target - i;
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
				   0x7 << 8, stage << 8);
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
				   0x7 << 11, stage << 11);
		usleep_range(100, 150);
	पूर्ण
पूर्ण

अटल व्योम hp_aux_feedback_loop_gain_ramp(काष्ठा mt6358_priv *priv, bool up)
अणु
	पूर्णांक i, stage;

	/* Reduce HP aux feedback loop gain step by step */
	क्रम (i = 0; i <= 0xf; i++) अणु
		stage = up ? i : 0xf - i;
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
				   0xf << 12, stage << 12);
		usleep_range(100, 150);
	पूर्ण
पूर्ण

अटल व्योम hp_pull_करोwn(काष्ठा mt6358_priv *priv, bool enable)
अणु
	पूर्णांक i;

	अगर (enable) अणु
		क्रम (i = 0x0; i <= 0x6; i++) अणु
			regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
					   0x7, i);
			usleep_range(600, 700);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0x6; i >= 0x1; i--) अणु
			regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
					   0x7, i);
			usleep_range(600, 700);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool is_valid_hp_pga_idx(पूर्णांक reg_idx)
अणु
	वापस (reg_idx >= DL_GAIN_8DB && reg_idx <= DL_GAIN_N_10DB) ||
	       reg_idx == DL_GAIN_N_40DB;
पूर्ण

अटल व्योम headset_volume_ramp(काष्ठा mt6358_priv *priv, पूर्णांक from, पूर्णांक to)
अणु
	पूर्णांक offset = 0, count = 0, reg_idx;

	अगर (!is_valid_hp_pga_idx(from) || !is_valid_hp_pga_idx(to))
		dev_warn(priv->dev, "%s(), volume index is not valid, from %d, to %d\n",
			 __func__, from, to);

	dev_info(priv->dev, "%s(), from %d, to %d\n",
		 __func__, from, to);

	अगर (to > from)
		offset = to - from;
	अन्यथा
		offset = from - to;

	जबतक (offset >= 0) अणु
		अगर (to > from)
			reg_idx = from + count;
		अन्यथा
			reg_idx = from - count;

		अगर (is_valid_hp_pga_idx(reg_idx)) अणु
			regmap_update_bits(priv->regmap,
					   MT6358_ZCD_CON2,
					   DL_GAIN_REG_MASK,
					   (reg_idx << 7) | reg_idx);
			usleep_range(200, 300);
		पूर्ण
		offset--;
		count++;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6358_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
			(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	चयन (mc->reg) अणु
	हाल MT6358_ZCD_CON2:
		regmap_पढ़ो(priv->regmap, MT6358_ZCD_CON2, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL] =
			(reg >> RG_AUDHPLGAIN_SFT) & RG_AUDHPLGAIN_MASK;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTR] =
			(reg >> RG_AUDHPRGAIN_SFT) & RG_AUDHPRGAIN_MASK;
		अवरोध;
	हाल MT6358_ZCD_CON1:
		regmap_पढ़ो(priv->regmap, MT6358_ZCD_CON1, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTL] =
			(reg >> RG_AUDLOLGAIN_SFT) & RG_AUDLOLGAIN_MASK;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTR] =
			(reg >> RG_AUDLORGAIN_SFT) & RG_AUDLORGAIN_MASK;
		अवरोध;
	हाल MT6358_ZCD_CON3:
		regmap_पढ़ो(priv->regmap, MT6358_ZCD_CON3, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HSOUTL] =
			(reg >> RG_AUDHSGAIN_SFT) & RG_AUDHSGAIN_MASK;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HSOUTR] =
			(reg >> RG_AUDHSGAIN_SFT) & RG_AUDHSGAIN_MASK;
		अवरोध;
	हाल MT6358_AUDENC_ANA_CON0:
	हाल MT6358_AUDENC_ANA_CON1:
		regmap_पढ़ो(priv->regmap, MT6358_AUDENC_ANA_CON0, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP1] =
			(reg >> RG_AUDPREAMPLGAIN_SFT) & RG_AUDPREAMPLGAIN_MASK;
		regmap_पढ़ो(priv->regmap, MT6358_AUDENC_ANA_CON1, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP2] =
			(reg >> RG_AUDPREAMPRGAIN_SFT) & RG_AUDPREAMPRGAIN_MASK;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mt6358_restore_pga(काष्ठा mt6358_priv *priv);

अटल पूर्णांक mt6358_enable_wov_phase2(काष्ठा mt6358_priv *priv)
अणु
	/* analog */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_DCXO_CW14, 0xffff, 0xa2b5);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0xffff, 0x0800);
	mt6358_restore_pga(priv);

	regmap_update_bits(priv->regmap, MT6358_DCXO_CW13, 0xffff, 0x9929);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
			   0xffff, 0x0025);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON8,
			   0xffff, 0x0005);

	/* digital */
	regmap_update_bits(priv->regmap, MT6358_AUD_TOP_CKPDN_CON0,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3, 0xffff, 0x0120);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG0, 0xffff, 0xffff);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG1, 0xffff, 0x0200);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG2, 0xffff, 0x2424);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG3, 0xffff, 0xdbac);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG4, 0xffff, 0x029e);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG5, 0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_POSDIV_CFG0,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_HPF_CFG0,
			   0xffff, 0x0451);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_TOP, 0xffff, 0x68d1);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_disable_wov_phase2(काष्ठा mt6358_priv *priv)
अणु
	/* digital */
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_TOP, 0xffff, 0xc000);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_HPF_CFG0,
			   0xffff, 0x0450);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_POSDIV_CFG0,
			   0xffff, 0x0c00);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG5, 0xffff, 0x0100);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG4, 0xffff, 0x006c);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG3, 0xffff, 0xa879);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG2, 0xffff, 0x2323);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG1, 0xffff, 0x0400);
	regmap_update_bits(priv->regmap, MT6358_AFE_VOW_CFG0, 0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3, 0xffff, 0x02d8);
	regmap_update_bits(priv->regmap, MT6358_AUD_TOP_CKPDN_CON0,
			   0xffff, 0x0000);

	/* analog */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON8,
			   0xffff, 0x0004);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_DCXO_CW13, 0xffff, 0x9829);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0xffff, 0x0000);
	mt6358_restore_pga(priv);
	regmap_update_bits(priv->regmap, MT6358_DCXO_CW14, 0xffff, 0xa2b5);
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
			   0xffff, 0x0010);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_get_wov(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.पूर्णांकeger.value[0] = priv->wov_enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_put_wov(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(c);
	पूर्णांक enabled = ucontrol->value.पूर्णांकeger.value[0];

	अगर (priv->wov_enabled != enabled) अणु
		अगर (enabled)
			mt6358_enable_wov_phase2(priv);
		अन्यथा
			mt6358_disable_wov_phase2(priv);

		priv->wov_enabled = enabled;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(playback_tlv, -1000, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mt6358_snd_controls[] = अणु
	/* dl pga gain */
	SOC_DOUBLE_EXT_TLV("Headphone Volume",
			   MT6358_ZCD_CON2, 0, 7, 0x12, 1,
			   snd_soc_get_volsw, mt6358_put_volsw, playback_tlv),
	SOC_DOUBLE_EXT_TLV("Lineout Volume",
			   MT6358_ZCD_CON1, 0, 7, 0x12, 1,
			   snd_soc_get_volsw, mt6358_put_volsw, playback_tlv),
	SOC_SINGLE_EXT_TLV("Handset Volume",
			   MT6358_ZCD_CON3, 0, 0x12, 1,
			   snd_soc_get_volsw, mt6358_put_volsw, playback_tlv),
	/* ul pga gain */
	SOC_DOUBLE_R_EXT_TLV("PGA Volume",
			     MT6358_AUDENC_ANA_CON0, MT6358_AUDENC_ANA_CON1,
			     8, 4, 0,
			     snd_soc_get_volsw, mt6358_put_volsw, pga_tlv),

	SOC_SINGLE_BOOL_EXT("Wake-on-Voice Phase2 Switch", 0,
			    mt6358_get_wov, mt6358_put_wov),
पूर्ण;

/* MUX */
/* LOL MUX */
अटल स्थिर अक्षर * स्थिर lo_in_mux_map[] = अणु
	"Open", "Mute", "Playback", "Test Mode"
पूर्ण;

अटल पूर्णांक lo_in_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(lo_in_mux_map_क्रमागत,
				  MT6358_AUDDEC_ANA_CON7,
				  RG_AUDLOLMUXINPUTSEL_VAUDP15_SFT,
				  RG_AUDLOLMUXINPUTSEL_VAUDP15_MASK,
				  lo_in_mux_map,
				  lo_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new lo_in_mux_control =
	SOC_DAPM_ENUM("In Select", lo_in_mux_map_क्रमागत);

/*HP MUX */
क्रमागत अणु
	HP_MUX_OPEN = 0,
	HP_MUX_HPSPK,
	HP_MUX_HP,
	HP_MUX_TEST_MODE,
	HP_MUX_HP_IMPEDANCE,
	HP_MUX_MASK = 0x7,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hp_in_mux_map[] = अणु
	"Open",
	"LoudSPK Playback",
	"Audio Playback",
	"Test Mode",
	"HP Impedance",
	"undefined1",
	"undefined2",
	"undefined3",
पूर्ण;

अटल पूर्णांक hp_in_mux_map_value[] = अणु
	HP_MUX_OPEN,
	HP_MUX_HPSPK,
	HP_MUX_HP,
	HP_MUX_TEST_MODE,
	HP_MUX_HP_IMPEDANCE,
	HP_MUX_OPEN,
	HP_MUX_OPEN,
	HP_MUX_OPEN,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(hpl_in_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  HP_MUX_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hpl_in_mux_control =
	SOC_DAPM_ENUM("HPL Select", hpl_in_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hpr_in_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  HP_MUX_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hpr_in_mux_control =
	SOC_DAPM_ENUM("HPR Select", hpr_in_mux_map_क्रमागत);

/* RCV MUX */
क्रमागत अणु
	RCV_MUX_OPEN = 0,
	RCV_MUX_MUTE,
	RCV_MUX_VOICE_PLAYBACK,
	RCV_MUX_TEST_MODE,
	RCV_MUX_MASK = 0x3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rcv_in_mux_map[] = अणु
	"Open", "Mute", "Voice Playback", "Test Mode"
पूर्ण;

अटल पूर्णांक rcv_in_mux_map_value[] = अणु
	RCV_MUX_OPEN,
	RCV_MUX_MUTE,
	RCV_MUX_VOICE_PLAYBACK,
	RCV_MUX_TEST_MODE,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rcv_in_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  RCV_MUX_MASK,
				  rcv_in_mux_map,
				  rcv_in_mux_map_value);

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
				  MT6358_AFE_TOP_CON0,
				  DL_SINE_ON_SFT,
				  DL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dac_in_mux_control =
	SOC_DAPM_ENUM("DAC Select", dac_in_mux_map_क्रमागत);

/* AIF Out MUX */
अटल SOC_VALUE_ENUM_SINGLE_DECL(aअगर_out_mux_map_क्रमागत,
				  MT6358_AFE_TOP_CON0,
				  UL_SINE_ON_SFT,
				  UL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर_out_mux_control =
	SOC_DAPM_ENUM("AIF Out Select", aअगर_out_mux_map_क्रमागत);

/* Mic Type MUX */
क्रमागत अणु
	MIC_TYPE_MUX_IDLE = 0,
	MIC_TYPE_MUX_ACC,
	MIC_TYPE_MUX_DMIC,
	MIC_TYPE_MUX_DCC,
	MIC_TYPE_MUX_DCC_ECM_DIFF,
	MIC_TYPE_MUX_DCC_ECM_SINGLE,
	MIC_TYPE_MUX_MASK = 0x7,
पूर्ण;

#घोषणा IS_DCC_BASE(type) ((type) == MIC_TYPE_MUX_DCC || \
			(type) == MIC_TYPE_MUX_DCC_ECM_DIFF || \
			(type) == MIC_TYPE_MUX_DCC_ECM_SINGLE)

अटल स्थिर अक्षर * स्थिर mic_type_mux_map[] = अणु
	"Idle",
	"ACC",
	"DMIC",
	"DCC",
	"DCC_ECM_DIFF",
	"DCC_ECM_SINGLE",
पूर्ण;

अटल पूर्णांक mic_type_mux_map_value[] = अणु
	MIC_TYPE_MUX_IDLE,
	MIC_TYPE_MUX_ACC,
	MIC_TYPE_MUX_DMIC,
	MIC_TYPE_MUX_DCC,
	MIC_TYPE_MUX_DCC_ECM_DIFF,
	MIC_TYPE_MUX_DCC_ECM_SINGLE,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(mic_type_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  MIC_TYPE_MUX_MASK,
				  mic_type_mux_map,
				  mic_type_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new mic_type_mux_control =
	SOC_DAPM_ENUM("Mic Type Select", mic_type_mux_map_क्रमागत);

/* ADC L MUX */
क्रमागत अणु
	ADC_MUX_IDLE = 0,
	ADC_MUX_AIN0,
	ADC_MUX_PREAMPLIFIER,
	ADC_MUX_IDLE1,
	ADC_MUX_MASK = 0x3,
पूर्ण;

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
				  SND_SOC_NOPM,
				  0,
				  ADC_MUX_MASK,
				  adc_left_mux_map,
				  adc_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_left_mux_control =
	SOC_DAPM_ENUM("ADC L Select", adc_left_mux_map_क्रमागत);

/* ADC R MUX */
अटल स्थिर अक्षर * स्थिर adc_right_mux_map[] = अणु
	"Idle", "AIN0", "Right Preamplifier", "Idle_1"
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_right_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  ADC_MUX_MASK,
				  adc_right_mux_map,
				  adc_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_right_mux_control =
	SOC_DAPM_ENUM("ADC R Select", adc_right_mux_map_क्रमागत);

/* PGA L MUX */
क्रमागत अणु
	PGA_MUX_NONE = 0,
	PGA_MUX_AIN0,
	PGA_MUX_AIN1,
	PGA_MUX_AIN2,
	PGA_MUX_MASK = 0x3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर pga_mux_map[] = अणु
	"None", "AIN0", "AIN1", "AIN2"
पूर्ण;

अटल पूर्णांक pga_mux_map_value[] = अणु
	PGA_MUX_NONE,
	PGA_MUX_AIN0,
	PGA_MUX_AIN1,
	PGA_MUX_AIN2,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_left_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  PGA_MUX_MASK,
				  pga_mux_map,
				  pga_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_left_mux_control =
	SOC_DAPM_ENUM("PGA L Select", pga_left_mux_map_क्रमागत);

/* PGA R MUX */
अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_right_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  PGA_MUX_MASK,
				  pga_mux_map,
				  pga_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_right_mux_control =
	SOC_DAPM_ENUM("PGA R Select", pga_right_mux_map_क्रमागत);

अटल पूर्णांक mt_clksq_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* audio clk source from पूर्णांकernal dcxo */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON6,
				   RG_CLKSQ_IN_SEL_TEST_MASK_SFT,
				   0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_sgen_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event = 0x%x\n", __func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* sdm audio fअगरo घड़ी घातer on */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON0, 0xCBA1);
		/* sdm घातer on */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0003);
		/* sdm fअगरo enable */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x000B);

		regmap_update_bits(priv->regmap, MT6358_AFE_SGEN_CFG0,
				   0xff3f,
				   0x0000);
		regmap_update_bits(priv->regmap, MT6358_AFE_SGEN_CFG1,
				   0xffff,
				   0x0001);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* DL scrambler disabling sequence */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0000);
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON0, 0xcba0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_aअगर_in_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol,
			   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_info(priv->dev, "%s(), event 0x%x, rate %d\n",
		 __func__, event, priv->dl_rate);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		playback_gpio_set(priv);

		/* sdm audio fअगरo घड़ी घातer on */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON0, 0xCBA1);
		/* sdm घातer on */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0003);
		/* sdm fअगरo enable */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x000B);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* DL scrambler disabling sequence */
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON2, 0x0000);
		regmap_ग_लिखो(priv->regmap, MT6358_AFUNC_AUD_CON0, 0xcba0);

		playback_gpio_reset(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hp_enable(काष्ठा mt6358_priv *priv)
अणु
	/* Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, true);
	/* release HP CMFB gate rstb */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
			   0x1 << 6, 0x1 << 6);

	/* Reduce ESD resistance of AU_REFN */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON2, 0x4000);

	/* Set HPR/HPL gain as minimum (~ -40dB) */
	regmap_ग_लिखो(priv->regmap, MT6358_ZCD_CON2, DL_GAIN_N_40DB_REG);

	/* Turn on DA_600K_NCP_VA18 */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON1, 0x0001);
	/* Set NCP घड़ी as 604kHz // 26MHz/43 = 604KHz */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON2, 0x002c);
	/* Toggle RG_DIVCKS_CHG */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON0, 0x0001);
	/* Set NCP soft start mode as शेष mode: 100us */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON4, 0x0003);
	/* Enable NCP */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3, 0x0000);
	usleep_range(250, 270);

	/* Enable cap-less LDOs (1.5V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
			   0x1055, 0x1055);
	/* Enable NV regulator (-1.2V) */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x0001);
	usleep_range(100, 120);

	/* Disable AUD_ZCD */
	hp_zcd_disable(priv);

	/* Disable headphone लघु-circuit protection */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x3000);

	/* Enable IBIST */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);

	/* Set HP DR bias current optimization, 010: 6uA */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON11, 0x4900);
	/* Set HP & ZCD bias current optimization */
	/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);
	/* Set HPP/N STB enhance circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON2, 0x4033);

	/* Enable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x000c);
	/* Enable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x003c);
	/* Enable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0c00);
	/* Enable HP driver bias circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30c0);
	/* Enable HP driver core circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30f0);
	/* Short HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x00fc);

	/* Enable HP मुख्य CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0e00);
	/* Disable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0200);

	/* Select CMFB resistor bulk to AC mode */
	/* Selec HS/LO cap size (6.5pF शेष) */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON10, 0x0000);

	/* Enable HP मुख्य output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x00ff);
	/* Enable HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, true);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, true);
	/* Disable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fcf);

	/* apply volume setting */
	headset_volume_ramp(priv,
			    DL_GAIN_N_10DB,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL]);

	/* Disable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fc3);
	/* Unलघु HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3f03);
	usleep_range(100, 120);

	/* Enable AUD_CLK */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13, 0x1, 0x1);
	/* Enable Audio DAC  */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30ff);
	/* Enable low-noise mode of DAC */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0xf201);
	usleep_range(100, 120);

	/* Switch HPL MUX to audio DAC */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x32ff);
	/* Switch HPR MUX to audio DAC */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x3aff);

	/* Disable Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hp_disable(काष्ठा mt6358_priv *priv)
अणु
	/* Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, true);

	/* HPR/HPL mux to खोलो */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x0f00, 0x0000);

	/* Disable low-noise mode of DAC */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
			   0x0001, 0x0000);

	/* Disable Audio DAC */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x000f, 0x0000);

	/* Disable AUD_CLK */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13, 0x1, 0x0);

	/* Short HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fc3);
	/* Enable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fcf);

	/* decrease HPL/R gain to normal gain step by step */
	headset_volume_ramp(priv,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL],
			    DL_GAIN_N_40DB);

	/* Enable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fff);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, false);

	/* decrease HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, false);

	/* Disable HP मुख्य output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3, 0x0);

	/* Enable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0e00);

	/* Disable HP मुख्य CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0c00);

	/* Unलघु HP मुख्य output to HP aux output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 6, 0x0);

	/* Disable HP driver core circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 4, 0x0);

	/* Disable HP driver bias circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 6, 0x0);

	/* Disable HP aux CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0000);

	/* Disable HP aux feedback loop */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 4, 0x0);

	/* Disable HP aux output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 2, 0x0);

	/* Disable IBIST */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON12,
			   0x1 << 8, 0x1 << 8);

	/* Disable NV regulator (-1.2V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x1, 0x0);
	/* Disable cap-less LDOs (1.5V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
			   0x1055, 0x0);
	/* Disable NCP */
	regmap_update_bits(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3,
			   0x1, 0x1);

	/* Increase ESD resistance of AU_REFN */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON2,
			   0x1 << 14, 0x0);

	/* Set HP CMFB gate rstb */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
			   0x1 << 6, 0x0);
	/* disable Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hp_spk_enable(काष्ठा mt6358_priv *priv)
अणु
	/* Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, true);
	/* release HP CMFB gate rstb */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
			   0x1 << 6, 0x1 << 6);

	/* Reduce ESD resistance of AU_REFN */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON2, 0x4000);

	/* Set HPR/HPL gain to -10dB */
	regmap_ग_लिखो(priv->regmap, MT6358_ZCD_CON2, DL_GAIN_N_10DB_REG);

	/* Turn on DA_600K_NCP_VA18 */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON1, 0x0001);
	/* Set NCP घड़ी as 604kHz // 26MHz/43 = 604KHz */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON2, 0x002c);
	/* Toggle RG_DIVCKS_CHG */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON0, 0x0001);
	/* Set NCP soft start mode as शेष mode: 100us */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON4, 0x0003);
	/* Enable NCP */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3, 0x0000);
	usleep_range(250, 270);

	/* Enable cap-less LDOs (1.5V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
			   0x1055, 0x1055);
	/* Enable NV regulator (-1.2V) */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x0001);
	usleep_range(100, 120);

	/* Disable AUD_ZCD */
	hp_zcd_disable(priv);

	/* Disable headphone लघु-circuit protection */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x3000);

	/* Enable IBIST */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);

	/* Set HP DR bias current optimization, 010: 6uA */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON11, 0x4900);
	/* Set HP & ZCD bias current optimization */
	/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);
	/* Set HPP/N STB enhance circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON2, 0x4033);

	/* Disable Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, false);

	/* Enable HP driver bias circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30c0);
	/* Enable HP driver core circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30f0);
	/* Enable HP मुख्य CMFB loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0200);

	/* Select CMFB resistor bulk to AC mode */
	/* Selec HS/LO cap size (6.5pF शेष) */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON10, 0x0000);

	/* Enable HP मुख्य output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x0003);
	/* Enable HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, true);

	/* Set LO gain as minimum (~ -40dB) */
	regmap_ग_लिखो(priv->regmap, MT6358_ZCD_CON1, DL_GAIN_N_40DB_REG);
	/* apply volume setting */
	headset_volume_ramp(priv,
			    DL_GAIN_N_10DB,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL]);

	/* Set LO STB enhance circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON7, 0x0110);
	/* Enable LO driver bias circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON7, 0x0112);
	/* Enable LO driver core circuits */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON7, 0x0113);

	/* Set LOL gain to normal gain step by step */
	regmap_update_bits(priv->regmap, MT6358_ZCD_CON1,
			   RG_AUDLOLGAIN_MASK_SFT,
			   priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTL] <<
			   RG_AUDLOLGAIN_SFT);
	regmap_update_bits(priv->regmap, MT6358_ZCD_CON1,
			   RG_AUDLORGAIN_MASK_SFT,
			   priv->ana_gain[AUDIO_ANALOG_VOLUME_LINEOUTR] <<
			   RG_AUDLORGAIN_SFT);

	/* Enable AUD_CLK */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13, 0x1, 0x1);
	/* Enable Audio DAC  */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x30f9);
	/* Enable low-noise mode of DAC */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0201);
	/* Switch LOL MUX to audio DAC */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON7, 0x011b);
	/* Switch HPL/R MUX to Line-out */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x35f9);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hp_spk_disable(काष्ठा mt6358_priv *priv)
अणु
	/* HPR/HPL mux to खोलो */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x0f00, 0x0000);
	/* LOL mux to खोलो */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON7,
			   0x3 << 2, 0x0000);

	/* Disable Audio DAC */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x000f, 0x0000);

	/* Disable AUD_CLK */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13, 0x1, 0x0);

	/* decrease HPL/R gain to normal gain step by step */
	headset_volume_ramp(priv,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL],
			    DL_GAIN_N_40DB);

	/* decrease LOL gain to minimum gain step by step */
	regmap_update_bits(priv->regmap, MT6358_ZCD_CON1,
			   DL_GAIN_REG_MASK, DL_GAIN_N_40DB_REG);

	/* decrease HPR/L मुख्य output stage step by step */
	hp_मुख्य_output_ramp(priv, false);

	/* Disable HP मुख्य output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3, 0x0);

	/* Short HP मुख्य output to HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fc3);
	/* Enable HP aux output stage */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fcf);

	/* Enable HP aux feedback loop */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fff);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, false);

	/* Disable HP driver core circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 4, 0x0);
	/* Disable LO driver core circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON7,
			   0x1, 0x0);

	/* Disable HP driver bias circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 6, 0x0);
	/* Disable LO driver bias circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON7,
			   0x1 << 1, 0x0);

	/* Disable HP aux CMFB loop */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
			   0xff << 8, 0x0000);

	/* Disable IBIST */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON12,
			   0x1 << 8, 0x1 << 8);
	/* Disable NV regulator (-1.2V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x1, 0x0);
	/* Disable cap-less LDOs (1.5V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14, 0x1055, 0x0);
	/* Disable NCP */
	regmap_update_bits(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3, 0x1, 0x1);

	/* Set HP CMFB gate rstb */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
			   0x1 << 6, 0x0);
	/* disable Pull-करोwn HPL/R to AVSS28_AUD */
	hp_pull_करोwn(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mt_hp_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol,
		       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);
	पूर्णांक device = DEVICE_HP;

	dev_info(priv->dev, "%s(), event 0x%x, dev_counter[DEV_HP] %d, mux %u\n",
		 __func__,
		 event,
		 priv->dev_counter[device],
		 mux);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		priv->dev_counter[device]++;
		अगर (priv->dev_counter[device] > 1)
			अवरोध;	/* alपढ़ोy enabled, करो nothing */
		अन्यथा अगर (priv->dev_counter[device] <= 0)
			dev_warn(priv->dev, "%s(), dev_counter[DEV_HP] %d <= 0\n",
				 __func__,
				 priv->dev_counter[device]);

		priv->mux_select[MUX_HP_L] = mux;

		अगर (mux == HP_MUX_HP)
			mtk_hp_enable(priv);
		अन्यथा अगर (mux == HP_MUX_HPSPK)
			mtk_hp_spk_enable(priv);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		priv->dev_counter[device]--;
		अगर (priv->dev_counter[device] > 0) अणु
			अवरोध;	/* still being used, करोn't बंद */
		पूर्ण अन्यथा अगर (priv->dev_counter[device] < 0) अणु
			dev_warn(priv->dev, "%s(), dev_counter[DEV_HP] %d < 0\n",
				 __func__,
				 priv->dev_counter[device]);
			priv->dev_counter[device] = 0;
			अवरोध;
		पूर्ण

		अगर (priv->mux_select[MUX_HP_L] == HP_MUX_HP)
			mtk_hp_disable(priv);
		अन्यथा अगर (priv->mux_select[MUX_HP_L] == HP_MUX_HPSPK)
			mtk_hp_spk_disable(priv);

		priv->mux_select[MUX_HP_L] = mux;
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
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_info(priv->dev, "%s(), event 0x%x, mux %u\n",
		 __func__,
		 event,
		 dapm_kcontrol_get_value(w->kcontrols[0]));

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Reduce ESD resistance of AU_REFN */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON2, 0x4000);

		/* Turn on DA_600K_NCP_VA18 */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON1, 0x0001);
		/* Set NCP घड़ी as 604kHz // 26MHz/43 = 604KHz */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON2, 0x002c);
		/* Toggle RG_DIVCKS_CHG */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON0, 0x0001);
		/* Set NCP soft start mode as शेष mode: 100us */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON4, 0x0003);
		/* Enable NCP */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3, 0x0000);
		usleep_range(250, 270);

		/* Enable cap-less LDOs (1.5V) */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x1055, 0x1055);
		/* Enable NV regulator (-1.2V) */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x0001);
		usleep_range(100, 120);

		/* Disable AUD_ZCD */
		hp_zcd_disable(priv);

		/* Disable handset लघु-circuit protection */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON6, 0x0010);

		/* Enable IBIST */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);
		/* Set HP DR bias current optimization, 010: 6uA */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON11, 0x4900);
		/* Set HP & ZCD bias current optimization */
		/* 01: ZCD: 4uA, HP/HS/LO: 5uA */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON12, 0x0055);
		/* Set HS STB enhance circuits */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON6, 0x0090);

		/* Disable HP मुख्य CMFB loop */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0000);
		/* Select CMFB resistor bulk to AC mode */
		/* Selec HS/LO cap size (6.5pF शेष) */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON10, 0x0000);

		/* Enable HS driver bias circuits */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON6, 0x0092);
		/* Enable HS driver core circuits */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON6, 0x0093);

		/* Enable AUD_CLK */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
				   0x1, 0x1);

		/* Enable Audio DAC  */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON0, 0x0009);
		/* Enable low-noise mode of DAC */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0001);
		/* Switch HS MUX to audio DAC */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDDEC_ANA_CON6, 0x009b);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* HS mux to खोलो */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON6,
				   RG_AUDHSMUXINPUTSEL_VAUDP15_MASK_SFT,
				   RCV_MUX_OPEN);

		/* Disable Audio DAC */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
				   0x000f, 0x0000);

		/* Disable AUD_CLK */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
				   0x1, 0x0);

		/* decrease HS gain to minimum gain step by step */
		regmap_ग_लिखो(priv->regmap, MT6358_ZCD_CON3, DL_GAIN_N_40DB);

		/* Disable HS driver core circuits */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON6,
				   0x1, 0x0);

		/* Disable HS driver bias circuits */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON6,
				   0x1 << 1, 0x0000);

		/* Disable HP aux CMFB loop */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
				   0xff << 8, 0x0);

		/* Enable HP मुख्य CMFB Switch */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
				   0xff << 8, 0x2 << 8);

		/* Disable IBIST */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON12,
				   0x1 << 8, 0x1 << 8);

		/* Disable NV regulator (-1.2V) */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON15,
				   0x1, 0x0);
		/* Disable cap-less LDOs (1.5V) */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x1055, 0x0);
		/* Disable NCP */
		regmap_update_bits(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3,
				   0x1, 0x1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_aअगर_out_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x, rate %d\n",
		__func__, event, priv->ul_rate);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		capture_gpio_set(priv);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		capture_gpio_reset(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_supply_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x\n",
		__func__, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable audio ADC CLKGEN  */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
				   0x1 << 5, 0x1 << 5);
		/* ADC CLK from CLKGEN (13MHz) */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON3,
			     0x0000);
		/* Enable  LCLDO_ENC 1P8V */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x2500, 0x0100);
		/* LCLDO_ENC remote sense */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x2500, 0x2500);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* LCLDO_ENC remote sense off */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x2500, 0x0100);
		/* disable LCLDO_ENC 1P8V */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
				   0x2500, 0x0000);

		/* ADC CLK from CLKGEN (13MHz) */
		regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON3, 0x0000);
		/* disable audio ADC CLKGEN  */
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
				   0x1 << 5, 0x0 << 5);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6358_amic_enable(काष्ठा mt6358_priv *priv)
अणु
	अचिन्हित पूर्णांक mic_type = priv->mux_select[MUX_MIC_TYPE];
	अचिन्हित पूर्णांक mux_pga_l = priv->mux_select[MUX_PGA_L];
	अचिन्हित पूर्णांक mux_pga_r = priv->mux_select[MUX_PGA_R];

	dev_info(priv->dev, "%s(), mux, mic %u, pga l %u, pga r %u\n",
		 __func__, mic_type, mux_pga_l, mux_pga_r);

	अगर (IS_DCC_BASE(mic_type)) अणु
		/* DCC 50k CLK (from 26M) */
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2062);
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2062);
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2060);
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2061);
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG1, 0x0100);
	पूर्ण

	/* mic bias 0 */
	अगर (mux_pga_l == PGA_MUX_AIN0 || mux_pga_l == PGA_MUX_AIN2 ||
	    mux_pga_r == PGA_MUX_AIN0 || mux_pga_r == PGA_MUX_AIN2) अणु
		चयन (mic_type) अणु
		हाल MIC_TYPE_MUX_DCC_ECM_DIFF:
			regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
					   0xff00, 0x7700);
			अवरोध;
		हाल MIC_TYPE_MUX_DCC_ECM_SINGLE:
			regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
					   0xff00, 0x1100);
			अवरोध;
		शेष:
			regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
					   0xff00, 0x0000);
			अवरोध;
		पूर्ण
		/* Enable MICBIAS0, MISBIAS0 = 1P9V */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON9,
				   0xff, 0x21);
	पूर्ण

	/* mic bias 1 */
	अगर (mux_pga_l == PGA_MUX_AIN1 || mux_pga_r == PGA_MUX_AIN1) अणु
		/* Enable MICBIAS1, MISBIAS1 = 2P6V */
		अगर (mic_type == MIC_TYPE_MUX_DCC_ECM_SINGLE)
			regmap_ग_लिखो(priv->regmap,
				     MT6358_AUDENC_ANA_CON10, 0x0161);
		अन्यथा
			regmap_ग_लिखो(priv->regmap,
				     MT6358_AUDENC_ANA_CON10, 0x0061);
	पूर्ण

	अगर (IS_DCC_BASE(mic_type)) अणु
		/* Audio L/R preamplअगरier DCC preअक्षरge */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   0xf8ff, 0x0004);
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   0xf8ff, 0x0004);
	पूर्ण अन्यथा अणु
		/* reset reg */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   0xf8ff, 0x0000);
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   0xf8ff, 0x0000);
	पूर्ण

	अगर (mux_pga_l != PGA_MUX_NONE) अणु
		/* L preamplअगरier input sel */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLINPUTSEL_MASK_SFT,
				   mux_pga_l << RG_AUDPREAMPLINPUTSEL_SFT);

		/* L preamplअगरier enable */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLON_MASK_SFT,
				   0x1 << RG_AUDPREAMPLON_SFT);

		अगर (IS_DCC_BASE(mic_type)) अणु
			/* L preamplअगरier DCCEN */
			regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
					   RG_AUDPREAMPLDCCEN_MASK_SFT,
					   0x1 << RG_AUDPREAMPLDCCEN_SFT);
		पूर्ण

		/* L ADC input sel : L PGA. Enable audio L ADC */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   RG_AUDADCLINPUTSEL_MASK_SFT,
				   ADC_MUX_PREAMPLIFIER <<
				   RG_AUDADCLINPUTSEL_SFT);
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   RG_AUDADCLPWRUP_MASK_SFT,
				   0x1 << RG_AUDADCLPWRUP_SFT);
	पूर्ण

	अगर (mux_pga_r != PGA_MUX_NONE) अणु
		/* R preamplअगरier input sel */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRINPUTSEL_MASK_SFT,
				   mux_pga_r << RG_AUDPREAMPRINPUTSEL_SFT);

		/* R preamplअगरier enable */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRON_MASK_SFT,
				   0x1 << RG_AUDPREAMPRON_SFT);

		अगर (IS_DCC_BASE(mic_type)) अणु
			/* R preamplअगरier DCCEN */
			regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
					   RG_AUDPREAMPRDCCEN_MASK_SFT,
					   0x1 << RG_AUDPREAMPRDCCEN_SFT);
		पूर्ण

		/* R ADC input sel : R PGA. Enable audio R ADC */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   RG_AUDADCRINPUTSEL_MASK_SFT,
				   ADC_MUX_PREAMPLIFIER <<
				   RG_AUDADCRINPUTSEL_SFT);
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   RG_AUDADCRPWRUP_MASK_SFT,
				   0x1 << RG_AUDADCRPWRUP_SFT);
	पूर्ण

	अगर (IS_DCC_BASE(mic_type)) अणु
		usleep_range(100, 150);
		/* Audio L preamplअगरier DCC preअक्षरge off */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
				   RG_AUDPREAMPLDCPRECHARGE_MASK_SFT, 0x0);
		/* Audio R preamplअगरier DCC preअक्षरge off */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
				   RG_AUDPREAMPRDCPRECHARGE_MASK_SFT, 0x0);

		/* Short body to ground in PGA */
		regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON3,
				   0x1 << 12, 0x0);
	पूर्ण

	/* here to set digital part */
	mt6358_mtkaअगर_tx_enable(priv);

	/* UL dmic setting off */
	regmap_ग_लिखो(priv->regmap, MT6358_AFE_UL_SRC_CON0_H, 0x0000);

	/* UL turn on */
	regmap_ग_लिखो(priv->regmap, MT6358_AFE_UL_SRC_CON0_L, 0x0001);

	वापस 0;
पूर्ण

अटल व्योम mt6358_amic_disable(काष्ठा mt6358_priv *priv)
अणु
	अचिन्हित पूर्णांक mic_type = priv->mux_select[MUX_MIC_TYPE];
	अचिन्हित पूर्णांक mux_pga_l = priv->mux_select[MUX_PGA_L];
	अचिन्हित पूर्णांक mux_pga_r = priv->mux_select[MUX_PGA_R];

	dev_info(priv->dev, "%s(), mux, mic %u, pga l %u, pga r %u\n",
		 __func__, mic_type, mux_pga_l, mux_pga_r);

	/* UL turn off */
	regmap_update_bits(priv->regmap, MT6358_AFE_UL_SRC_CON0_L,
			   0x0001, 0x0000);

	/* disable aud_pad TX fअगरos */
	mt6358_mtkaअगर_tx_disable(priv);

	/* L ADC input sel : off, disable L ADC */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
			   0xf000, 0x0000);
	/* L preamplअगरier DCCEN */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
			   0x1 << 1, 0x0);
	/* L preamplअगरier input sel : off, L PGA 0 dB gain */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
			   0xfffb, 0x0000);

	/* disable L preamplअगरier DCC preअक्षरge */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
			   0x1 << 2, 0x0);

	/* R ADC input sel : off, disable R ADC */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0xf000, 0x0000);
	/* R preamplअगरier DCCEN */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0x1 << 1, 0x0);
	/* R preamplअगरier input sel : off, R PGA 0 dB gain */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0x0ffb, 0x0000);

	/* disable R preamplअगरier DCC preअक्षरge */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   0x1 << 2, 0x0);

	/* mic bias */
	/* Disable MICBIAS0, MISBIAS0 = 1P7V */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON9, 0x0000);

	/* Disable MICBIAS1 */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON10,
			   0x0001, 0x0000);

	अगर (IS_DCC_BASE(mic_type)) अणु
		/* dcclk_gen_on=1'b0 */
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2060);
		/* dcclk_pdn=1'b1 */
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2062);
		/* dcclk_ref_ck_sel=2'b00 */
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2062);
		/* dcclk_भाग=11'b00100000011 */
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_DCCLK_CFG0, 0x2062);
	पूर्ण
पूर्ण

अटल पूर्णांक mt6358_dmic_enable(काष्ठा mt6358_priv *priv)
अणु
	dev_info(priv->dev, "%s()\n", __func__);

	/* mic bias */
	/* Enable MICBIAS0, MISBIAS0 = 1P9V */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON9, 0x0021);

	/* RG_BANDGAPGEN=1'b0 */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON10,
			   0x1 << 12, 0x0);

	/* DMIC enable */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON8, 0x0005);

	/* here to set digital part */
	mt6358_mtkaअगर_tx_enable(priv);

	/* UL dmic setting */
	अगर (priv->dmic_one_wire_mode)
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_UL_SRC_CON0_H, 0x0400);
	अन्यथा
		regmap_ग_लिखो(priv->regmap, MT6358_AFE_UL_SRC_CON0_H, 0x0080);

	/* UL turn on */
	regmap_ग_लिखो(priv->regmap, MT6358_AFE_UL_SRC_CON0_L, 0x0003);

	/* Prevent pop noise क्रमm dmic hw */
	msleep(100);

	वापस 0;
पूर्ण

अटल व्योम mt6358_dmic_disable(काष्ठा mt6358_priv *priv)
अणु
	dev_info(priv->dev, "%s()\n", __func__);

	/* UL turn off */
	regmap_update_bits(priv->regmap, MT6358_AFE_UL_SRC_CON0_L,
			   0x0003, 0x0000);

	/* disable aud_pad TX fअगरos */
	mt6358_mtkaअगर_tx_disable(priv);

	/* DMIC disable */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON8, 0x0000);

	/* mic bias */
	/* MISBIAS0 = 1P7V */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON9, 0x0001);

	/* RG_BANDGAPGEN=1'b0 */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON10,
			   0x1 << 12, 0x0);

	/* MICBIA0 disable */
	regmap_ग_लिखो(priv->regmap, MT6358_AUDENC_ANA_CON9, 0x0000);
पूर्ण

अटल व्योम mt6358_restore_pga(काष्ठा mt6358_priv *priv)
अणु
	अचिन्हित पूर्णांक gain_l, gain_r;

	gain_l = priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP1];
	gain_r = priv->ana_gain[AUDIO_ANALOG_VOLUME_MICAMP2];

	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON0,
			   RG_AUDPREAMPLGAIN_MASK_SFT,
			   gain_l << RG_AUDPREAMPLGAIN_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON1,
			   RG_AUDPREAMPRGAIN_MASK_SFT,
			   gain_r << RG_AUDPREAMPRGAIN_SFT);
पूर्ण

अटल पूर्णांक mt_mic_type_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), event 0x%x, mux %u\n",
		__func__, event, mux);

	चयन (event) अणु
	हाल SND_SOC_DAPM_WILL_PMU:
		priv->mux_select[MUX_MIC_TYPE] = mux;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (mux) अणु
		हाल MIC_TYPE_MUX_DMIC:
			mt6358_dmic_enable(priv);
			अवरोध;
		शेष:
			mt6358_amic_enable(priv);
			अवरोध;
		पूर्ण
		mt6358_restore_pga(priv);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		चयन (priv->mux_select[MUX_MIC_TYPE]) अणु
		हाल MIC_TYPE_MUX_DMIC:
			mt6358_dmic_disable(priv);
			अवरोध;
		शेष:
			mt6358_amic_disable(priv);
			अवरोध;
		पूर्ण

		priv->mux_select[MUX_MIC_TYPE] = mux;
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
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), event = 0x%x, mux %u\n",
		__func__, event, mux);

	priv->mux_select[MUX_ADC_L] = mux;

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_r_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), event = 0x%x, mux %u\n",
		__func__, event, mux);

	priv->mux_select[MUX_ADC_R] = mux;

	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_left_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), event = 0x%x, mux %u\n",
		__func__, event, mux);

	priv->mux_select[MUX_PGA_L] = mux;

	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_right_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक mux = dapm_kcontrol_get_value(w->kcontrols[0]);

	dev_dbg(priv->dev, "%s(), event = 0x%x, mux %u\n",
		__func__, event, mux);

	priv->mux_select[MUX_PGA_R] = mux;

	वापस 0;
पूर्ण

अटल पूर्णांक mt_delay_250_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(250, 270);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		usleep_range(250, 270);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* DAPM Widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget mt6358_dapm_widमाला_लो[] = अणु
	/* Global Supply*/
	SND_SOC_DAPM_SUPPLY_S("CLK_BUF", SUPPLY_SEQ_CLK_BUF,
			      MT6358_DCXO_CW14,
			      RG_XO_AUDIO_EN_M_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDGLB", SUPPLY_SEQ_AUD_GLB,
			      MT6358_AUDDEC_ANA_CON13,
			      RG_AUDGLB_PWRDN_VA28_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("CLKSQ Audio", SUPPLY_SEQ_CLKSQ,
			      MT6358_AUDENC_ANA_CON6,
			      RG_CLKSQ_EN_SFT, 0,
			      mt_clksq_event,
			      SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY_S("AUDNCP_CK", SUPPLY_SEQ_TOP_CK,
			      MT6358_AUD_TOP_CKPDN_CON0,
			      RG_AUDNCP_CK_PDN_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ZCD13M_CK", SUPPLY_SEQ_TOP_CK,
			      MT6358_AUD_TOP_CKPDN_CON0,
			      RG_ZCD13M_CK_PDN_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUD_CK", SUPPLY_SEQ_TOP_CK_LAST,
			      MT6358_AUD_TOP_CKPDN_CON0,
			      RG_AUD_CK_PDN_SFT, 1,
			      mt_delay_250_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY_S("AUDIF_CK", SUPPLY_SEQ_TOP_CK,
			      MT6358_AUD_TOP_CKPDN_CON0,
			      RG_AUDIF_CK_PDN_SFT, 1, शून्य, 0),

	/* Digital Clock */
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_AFE_CTL", SUPPLY_SEQ_AUD_TOP_LAST,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_AFE_CTL_SFT, 1,
			      mt_delay_250_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_DAC_CTL", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_DAC_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_ADC_CTL", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_ADC_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_I2S_DL", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_I2S_DL_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PWR_CLK", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PWR_CLK_DIS_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PDN_AFE_TESTMODEL", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_AFE_TESTMODEL_CTL_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AUDIO_TOP_PDN_RESERVED", SUPPLY_SEQ_AUD_TOP,
			      MT6358_AUDIO_TOP_CON0,
			      PDN_RESERVED_SFT, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DL Digital Clock", SND_SOC_NOPM,
			    0, 0, शून्य, 0),

	/* AFE ON */
	SND_SOC_DAPM_SUPPLY_S("AFE_ON", SUPPLY_SEQ_AFE,
			      MT6358_AFE_UL_DL_CON0, AFE_ON_SFT, 0,
			      शून्य, 0),

	/* AIF Rx*/
	SND_SOC_DAPM_AIF_IN_E("AIF_RX", "AIF1 Playback", 0,
			      MT6358_AFE_DL_SRC2_CON0_L,
			      DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0,
			      mt_aअगर_in_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* DL Supply */
	SND_SOC_DAPM_SUPPLY("DL Power Supply", SND_SOC_NOPM,
			    0, 0, शून्य, 0),

	/* DAC */
	SND_SOC_DAPM_MUX("DAC In Mux", SND_SOC_NOPM, 0, 0, &dac_in_mux_control),

	SND_SOC_DAPM_DAC("DACL", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DACR", शून्य, SND_SOC_NOPM, 0, 0),

	/* LOL */
	SND_SOC_DAPM_MUX("LOL Mux", SND_SOC_NOPM, 0, 0, &lo_in_mux_control),

	SND_SOC_DAPM_SUPPLY("LO Stability Enh", MT6358_AUDDEC_ANA_CON7,
			    RG_LOOUTPUTSTBENH_VAUDP15_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("LOL Buffer", MT6358_AUDDEC_ANA_CON7,
			     RG_AUDLOLPWRUP_VAUDP15_SFT, 0, शून्य, 0),

	/* Headphone */
	SND_SOC_DAPM_MUX_E("HPL Mux", SND_SOC_NOPM, 0, 0,
			   &hpl_in_mux_control,
			   mt_hp_event,
			   SND_SOC_DAPM_PRE_PMU |
			   SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MUX_E("HPR Mux", SND_SOC_NOPM, 0, 0,
			   &hpr_in_mux_control,
			   mt_hp_event,
			   SND_SOC_DAPM_PRE_PMU |
			   SND_SOC_DAPM_PRE_PMD),

	/* Receiver */
	SND_SOC_DAPM_MUX_E("RCV Mux", SND_SOC_NOPM, 0, 0,
			   &rcv_in_mux_control,
			   mt_rcv_event,
			   SND_SOC_DAPM_PRE_PMU |
			   SND_SOC_DAPM_PRE_PMD),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("Receiver"),
	SND_SOC_DAPM_OUTPUT("Headphone L"),
	SND_SOC_DAPM_OUTPUT("Headphone R"),
	SND_SOC_DAPM_OUTPUT("Headphone L Ext Spk Amp"),
	SND_SOC_DAPM_OUTPUT("Headphone R Ext Spk Amp"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L HSSPK"),

	/* SGEN */
	SND_SOC_DAPM_SUPPLY("SGEN DL Enable", MT6358_AFE_SGEN_CFG0,
			    SGEN_DAC_EN_CTL_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SGEN MUTE", MT6358_AFE_SGEN_CFG0,
			    SGEN_MUTE_SW_CTL_SFT, 1,
			    mt_sgen_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("SGEN DL SRC", MT6358_AFE_DL_SRC2_CON0_L,
			    DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("SGEN DL"),

	/* Uplinks */
	SND_SOC_DAPM_AIF_OUT_E("AIF1TX", "AIF1 Capture", 0,
			       SND_SOC_NOPM, 0, 0,
			       mt_aअगर_out_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("ADC Supply", SUPPLY_SEQ_ADC_SUPPLY,
			      SND_SOC_NOPM, 0, 0,
			      mt_adc_supply_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* Uplinks MUX */
	SND_SOC_DAPM_MUX("AIF Out Mux", SND_SOC_NOPM, 0, 0,
			 &aअगर_out_mux_control),

	SND_SOC_DAPM_MUX_E("Mic Type Mux", SND_SOC_NOPM, 0, 0,
			   &mic_type_mux_control,
			   mt_mic_type_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD |
			   SND_SOC_DAPM_WILL_PMU),

	SND_SOC_DAPM_MUX_E("ADC L Mux", SND_SOC_NOPM, 0, 0,
			   &adc_left_mux_control,
			   mt_adc_l_event,
			   SND_SOC_DAPM_WILL_PMU),
	SND_SOC_DAPM_MUX_E("ADC R Mux", SND_SOC_NOPM, 0, 0,
			   &adc_right_mux_control,
			   mt_adc_r_event,
			   SND_SOC_DAPM_WILL_PMU),

	SND_SOC_DAPM_ADC("ADC L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX_E("PGA L Mux", SND_SOC_NOPM, 0, 0,
			   &pga_left_mux_control,
			   mt_pga_left_event,
			   SND_SOC_DAPM_WILL_PMU),
	SND_SOC_DAPM_MUX_E("PGA R Mux", SND_SOC_NOPM, 0, 0,
			   &pga_right_mux_control,
			   mt_pga_right_event,
			   SND_SOC_DAPM_WILL_PMU),

	SND_SOC_DAPM_PGA("PGA L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* UL input */
	SND_SOC_DAPM_INPUT("AIN0"),
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt6358_dapm_routes[] = अणु
	/* Capture */
	अणु"AIF1TX", शून्य, "AIF Out Mux"पूर्ण,
	अणु"AIF1TX", शून्य, "CLK_BUF"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDGLB"पूर्ण,
	अणु"AIF1TX", शून्य, "CLKSQ Audio"पूर्ण,

	अणु"AIF1TX", शून्य, "AUD_CK"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIF_CK"पूर्ण,

	अणु"AIF1TX", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_ADC_CTL"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_PDN_RESERVED"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_I2S_DL"पूर्ण,

	अणु"AIF1TX", शून्य, "AFE_ON"पूर्ण,

	अणु"AIF Out Mux", शून्य, "Mic Type Mux"पूर्ण,

	अणु"Mic Type Mux", "ACC", "ADC L"पूर्ण,
	अणु"Mic Type Mux", "ACC", "ADC R"पूर्ण,
	अणु"Mic Type Mux", "DCC", "ADC L"पूर्ण,
	अणु"Mic Type Mux", "DCC", "ADC R"पूर्ण,
	अणु"Mic Type Mux", "DCC_ECM_DIFF", "ADC L"पूर्ण,
	अणु"Mic Type Mux", "DCC_ECM_DIFF", "ADC R"पूर्ण,
	अणु"Mic Type Mux", "DCC_ECM_SINGLE", "ADC L"पूर्ण,
	अणु"Mic Type Mux", "DCC_ECM_SINGLE", "ADC R"पूर्ण,
	अणु"Mic Type Mux", "DMIC", "AIN0"पूर्ण,
	अणु"Mic Type Mux", "DMIC", "AIN2"पूर्ण,

	अणु"ADC L", शून्य, "ADC L Mux"पूर्ण,
	अणु"ADC L", शून्य, "ADC Supply"पूर्ण,
	अणु"ADC R", शून्य, "ADC R Mux"पूर्ण,
	अणु"ADC R", शून्य, "ADC Supply"पूर्ण,

	अणु"ADC L Mux", "Left Preamplifier", "PGA L"पूर्ण,

	अणु"ADC R Mux", "Right Preamplifier", "PGA R"पूर्ण,

	अणु"PGA L", शून्य, "PGA L Mux"पूर्ण,
	अणु"PGA R", शून्य, "PGA R Mux"पूर्ण,

	अणु"PGA L Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA L Mux", "AIN1", "AIN1"पूर्ण,
	अणु"PGA L Mux", "AIN2", "AIN2"पूर्ण,

	अणु"PGA R Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA R Mux", "AIN1", "AIN1"पूर्ण,
	अणु"PGA R Mux", "AIN2", "AIN2"पूर्ण,

	/* DL Supply */
	अणु"DL Power Supply", शून्य, "CLK_BUF"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDGLB"पूर्ण,
	अणु"DL Power Supply", शून्य, "CLKSQ Audio"पूर्ण,

	अणु"DL Power Supply", शून्य, "AUDNCP_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "ZCD13M_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUD_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDIF_CK"पूर्ण,

	/* DL Digital Supply */
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_DAC_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,

	अणु"DL Digital Clock", शून्य, "AFE_ON"पूर्ण,

	अणु"AIF_RX", शून्य, "DL Digital Clock"पूर्ण,

	/* DL Path */
	अणु"DAC In Mux", "Normal Path", "AIF_RX"पूर्ण,

	अणु"DAC In Mux", "Sgen", "SGEN DL"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL SRC"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN MUTE"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL Enable"पूर्ण,
	अणु"SGEN DL", शून्य, "DL Digital Clock"पूर्ण,
	अणु"SGEN DL", शून्य, "AUDIO_TOP_PDN_AFE_TESTMODEL"पूर्ण,

	अणु"DACL", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACL", शून्य, "DL Power Supply"पूर्ण,

	अणु"DACR", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACR", शून्य, "DL Power Supply"पूर्ण,

	/* Lineout Path */
	अणु"LOL Mux", "Playback", "DACL"पूर्ण,

	अणु"LOL Buffer", शून्य, "LOL Mux"पूर्ण,
	अणु"LOL Buffer", शून्य, "LO Stability Enh"पूर्ण,

	अणु"LINEOUT L", शून्य, "LOL Buffer"पूर्ण,

	/* Headphone Path */
	अणु"HPL Mux", "Audio Playback", "DACL"पूर्ण,
	अणु"HPR Mux", "Audio Playback", "DACR"पूर्ण,
	अणु"HPL Mux", "HP Impedance", "DACL"पूर्ण,
	अणु"HPR Mux", "HP Impedance", "DACR"पूर्ण,
	अणु"HPL Mux", "LoudSPK Playback", "DACL"पूर्ण,
	अणु"HPR Mux", "LoudSPK Playback", "DACR"पूर्ण,

	अणु"Headphone L", शून्य, "HPL Mux"पूर्ण,
	अणु"Headphone R", शून्य, "HPR Mux"पूर्ण,
	अणु"Headphone L Ext Spk Amp", शून्य, "HPL Mux"पूर्ण,
	अणु"Headphone R Ext Spk Amp", शून्य, "HPR Mux"पूर्ण,
	अणु"LINEOUT L HSSPK", शून्य, "HPL Mux"पूर्ण,

	/* Receiver Path */
	अणु"RCV Mux", "Voice Playback", "DACL"पूर्ण,
	अणु"Receiver", शून्य, "RCV Mux"पूर्ण,
पूर्ण;

अटल पूर्णांक mt6358_codec_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *cmpnt = dai->component;
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक rate = params_rate(params);

	dev_info(priv->dev, "%s(), substream->stream %d, rate %d, number %d\n",
		 __func__,
		 substream->stream,
		 rate,
		 substream->number);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		priv->dl_rate = rate;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		priv->ul_rate = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mt6358_codec_dai_ops = अणु
	.hw_params = mt6358_codec_dai_hw_params,
पूर्ण;

#घोषणा MT6358_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |\
			SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |\
			SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_U24_BE |\
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE |\
			SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_U32_BE)

अटल काष्ठा snd_soc_dai_driver mt6358_dai_driver[] = अणु
	अणु
		.name = "mt6358-snd-codec-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6358_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_48000,
			.क्रमmats = MT6358_FORMATS,
		पूर्ण,
		.ops = &mt6358_codec_dai_ops,
	पूर्ण,
पूर्ण;

अटल व्योम mt6358_codec_init_reg(काष्ठा mt6358_priv *priv)
अणु
	/* Disable HeadphoneL/HeadphoneR लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   RG_AUDHPLSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHPLSCDISABLE_VAUDP15_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   RG_AUDHPRSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHPRSCDISABLE_VAUDP15_SFT);
	/* Disable voice लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON6,
			   RG_AUDHSSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHSSCDISABLE_VAUDP15_SFT);
	/* disable LO buffer left लघु circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON7,
			   RG_AUDLOLSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDLOLSCDISABLE_VAUDP15_SFT);

	/* accdet s/w enable */
	regmap_update_bits(priv->regmap, MT6358_ACCDET_CON13,
			   0xFFFF, 0x700E);

	/* gpio miso driving set to 4mA */
	regmap_ग_लिखो(priv->regmap, MT6358_DRV_CON3, 0x8888);

	/* set gpio */
	playback_gpio_reset(priv);
	capture_gpio_reset(priv);
पूर्ण

अटल पूर्णांक mt6358_codec_probe(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक ret;

	snd_soc_component_init_regmap(cmpnt, priv->regmap);

	mt6358_codec_init_reg(priv);

	priv->avdd_reg = devm_regulator_get(priv->dev, "Avdd");
	अगर (IS_ERR(priv->avdd_reg)) अणु
		dev_err(priv->dev, "%s() have no Avdd supply", __func__);
		वापस PTR_ERR(priv->avdd_reg);
	पूर्ण

	ret = regulator_enable(priv->avdd_reg);
	अगर (ret)
		वापस  ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt6358_soc_component_driver = अणु
	.probe = mt6358_codec_probe,
	.controls = mt6358_snd_controls,
	.num_controls = ARRAY_SIZE(mt6358_snd_controls),
	.dapm_widमाला_लो = mt6358_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt6358_dapm_widमाला_लो),
	.dapm_routes = mt6358_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt6358_dapm_routes),
पूर्ण;

अटल व्योम mt6358_parse_dt(काष्ठा mt6358_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = priv->dev;

	ret = of_property_पढ़ो_u32(dev->of_node, "mediatek,dmic-mode",
				   &priv->dmic_one_wire_mode);
	अगर (ret) अणु
		dev_warn(priv->dev, "%s() failed to read dmic-mode\n",
			 __func__);
		priv->dmic_one_wire_mode = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6358_platक्रमm_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6358_priv *priv;
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);

	priv = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा mt6358_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, priv);

	priv->dev = &pdev->dev;

	priv->regmap = mt6397->regmap;
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	mt6358_parse_dt(priv);

	dev_info(priv->dev, "%s(), dev name %s\n",
		 __func__, dev_name(&pdev->dev));

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &mt6358_soc_component_driver,
				      mt6358_dai_driver,
				      ARRAY_SIZE(mt6358_dai_driver));
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6358_of_match[] = अणु
	अणु.compatible = "mediatek,mt6358-sound",पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6358_of_match);

अटल काष्ठा platक्रमm_driver mt6358_platक्रमm_driver = अणु
	.driver = अणु
		.name = "mt6358-sound",
		.of_match_table = mt6358_of_match,
	पूर्ण,
	.probe = mt6358_platक्रमm_driver_probe,
पूर्ण;

module_platक्रमm_driver(mt6358_platक्रमm_driver)

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT6358 ALSA SoC codec driver");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_LICENSE("GPL v2");
