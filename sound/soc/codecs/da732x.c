<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * da732x.c --- Dialog DA732X ALSA SoC Audio Driver
 *
 * Copyright (C) 2012 Dialog Semiconductor GmbH
 *
 * Author: Michal Hajduk <Michal.Hajduk@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "da732x.h"
#समावेश "da732x_reg.h"


काष्ठा da732x_priv अणु
	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक sysclk;
	bool pll_en;
पूर्ण;

/*
 * da732x रेजिस्टर cache - शेष settings
 */
अटल स्थिर काष्ठा reg_शेष da732x_reg_cache[] = अणु
	अणु DA732X_REG_REF1		, 0x02 पूर्ण,
	अणु DA732X_REG_BIAS_EN		, 0x80 पूर्ण,
	अणु DA732X_REG_BIAS1		, 0x00 पूर्ण,
	अणु DA732X_REG_BIAS2		, 0x00 पूर्ण,
	अणु DA732X_REG_BIAS3		, 0x00 पूर्ण,
	अणु DA732X_REG_BIAS4		, 0x00 पूर्ण,
	अणु DA732X_REG_MICBIAS2		, 0x00 पूर्ण,
	अणु DA732X_REG_MICBIAS1		, 0x00 पूर्ण,
	अणु DA732X_REG_MICDET		, 0x00 पूर्ण,
	अणु DA732X_REG_MIC1_PRE		, 0x01 पूर्ण,
	अणु DA732X_REG_MIC1		, 0x40 पूर्ण,
	अणु DA732X_REG_MIC2_PRE		, 0x01 पूर्ण,
	अणु DA732X_REG_MIC2		, 0x40 पूर्ण,
	अणु DA732X_REG_AUX1L		, 0x75 पूर्ण,
	अणु DA732X_REG_AUX1R		, 0x75 पूर्ण,
	अणु DA732X_REG_MIC3_PRE		, 0x01 पूर्ण,
	अणु DA732X_REG_MIC3		, 0x40 पूर्ण,
	अणु DA732X_REG_INP_PINBIAS	, 0x00 पूर्ण,
	अणु DA732X_REG_INP_ZC_EN		, 0x00 पूर्ण,
	अणु DA732X_REG_INP_MUX		, 0x50 पूर्ण,
	अणु DA732X_REG_HP_DET		, 0x00 पूर्ण,
	अणु DA732X_REG_HPL_DAC_OFFSET	, 0x00 पूर्ण,
	अणु DA732X_REG_HPL_DAC_OFF_CNTL	, 0x00 पूर्ण,
	अणु DA732X_REG_HPL_OUT_OFFSET	, 0x00 पूर्ण,
	अणु DA732X_REG_HPL		, 0x40 पूर्ण,
	अणु DA732X_REG_HPL_VOL		, 0x0F पूर्ण,
	अणु DA732X_REG_HPR_DAC_OFFSET	, 0x00 पूर्ण,
	अणु DA732X_REG_HPR_DAC_OFF_CNTL	, 0x00 पूर्ण,
	अणु DA732X_REG_HPR_OUT_OFFSET	, 0x00 पूर्ण,
	अणु DA732X_REG_HPR		, 0x40 पूर्ण,
	अणु DA732X_REG_HPR_VOL		, 0x0F पूर्ण,
	अणु DA732X_REG_LIN2		, 0x4F पूर्ण,
	अणु DA732X_REG_LIN3		, 0x4F पूर्ण,
	अणु DA732X_REG_LIN4		, 0x4F पूर्ण,
	अणु DA732X_REG_OUT_ZC_EN		, 0x00 पूर्ण,
	अणु DA732X_REG_HP_LIN1_GNDSEL	, 0x00 पूर्ण,
	अणु DA732X_REG_CP_HP1		, 0x0C पूर्ण,
	अणु DA732X_REG_CP_HP2		, 0x03 पूर्ण,
	अणु DA732X_REG_CP_CTRL1		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_CTRL2		, 0x99 पूर्ण,
	अणु DA732X_REG_CP_CTRL3		, 0x25 पूर्ण,
	अणु DA732X_REG_CP_LEVEL_MASK	, 0x3F पूर्ण,
	अणु DA732X_REG_CP_DET		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_STATUS		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH1		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH2		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH3		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH4		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH5		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH6		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH7		, 0x00 पूर्ण,
	अणु DA732X_REG_CP_THRESH8		, 0x00 पूर्ण,
	अणु DA732X_REG_PLL_DIV_LO		, 0x00 पूर्ण,
	अणु DA732X_REG_PLL_DIV_MID	, 0x00 पूर्ण,
	अणु DA732X_REG_PLL_DIV_HI		, 0x00 पूर्ण,
	अणु DA732X_REG_PLL_CTRL		, 0x02 पूर्ण,
	अणु DA732X_REG_CLK_CTRL		, 0xaa पूर्ण,
	अणु DA732X_REG_CLK_DSP		, 0x07 पूर्ण,
	अणु DA732X_REG_CLK_EN1		, 0x00 पूर्ण,
	अणु DA732X_REG_CLK_EN2		, 0x00 पूर्ण,
	अणु DA732X_REG_CLK_EN3		, 0x00 पूर्ण,
	अणु DA732X_REG_CLK_EN4		, 0x00 पूर्ण,
	अणु DA732X_REG_CLK_EN5		, 0x00 पूर्ण,
	अणु DA732X_REG_AIF_MCLK		, 0x00 पूर्ण,
	अणु DA732X_REG_AIFA1		, 0x02 पूर्ण,
	अणु DA732X_REG_AIFA2		, 0x00 पूर्ण,
	अणु DA732X_REG_AIFA3		, 0x08 पूर्ण,
	अणु DA732X_REG_AIFB1		, 0x02 पूर्ण,
	अणु DA732X_REG_AIFB2		, 0x00 पूर्ण,
	अणु DA732X_REG_AIFB3		, 0x08 पूर्ण,
	अणु DA732X_REG_PC_CTRL		, 0xC0 पूर्ण,
	अणु DA732X_REG_DATA_ROUTE		, 0x00 पूर्ण,
	अणु DA732X_REG_DSP_CTRL		, 0x00 पूर्ण,
	अणु DA732X_REG_CIF_CTRL2		, 0x00 पूर्ण,
	अणु DA732X_REG_HANDSHAKE		, 0x00 पूर्ण,
	अणु DA732X_REG_SPARE1_OUT		, 0x00 पूर्ण,
	अणु DA732X_REG_SPARE2_OUT		, 0x00 पूर्ण,
	अणु DA732X_REG_SPARE1_IN		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_PD		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_HPF		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_SEL		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_EQ12		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_EQ34		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC1_EQ5		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_PD		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_HPF		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_SEL		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_EQ12		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_EQ34		, 0x00 पूर्ण,
	अणु DA732X_REG_ADC2_EQ5		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_HPF		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_L_VOL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_R_VOL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_SEL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_SOFTMUTE	, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_EQ12		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_EQ34		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC1_EQ5		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_HPF		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_L_VOL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_R_VOL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_SEL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_SOFTMUTE	, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_EQ12		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_EQ34		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC2_EQ5		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_HPF		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_VOL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_SEL		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_SOFTMUTE	, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_EQ12		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_EQ34		, 0x00 पूर्ण,
	अणु DA732X_REG_DAC3_EQ5		, 0x00 पूर्ण,
	अणु DA732X_REG_BIQ_BYP		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_CMD		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_ADDR0		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_ADDR1		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_DATA0		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_DATA1		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_DATA2		, 0x00 पूर्ण,
	अणु DA732X_REG_DMA_DATA3		, 0x00 पूर्ण,
	अणु DA732X_REG_UNLOCK		, 0x00 पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक da732x_get_input_भाग(काष्ठा snd_soc_component *component, पूर्णांक sysclk)
अणु
	पूर्णांक val;

	अगर (sysclk < DA732X_MCLK_10MHZ) अणु
		val = DA732X_MCLK_VAL_0_10MHZ;
	पूर्ण अन्यथा अगर ((sysclk >= DA732X_MCLK_10MHZ) &&
	    (sysclk < DA732X_MCLK_20MHZ)) अणु
		val = DA732X_MCLK_VAL_10_20MHZ;
	पूर्ण अन्यथा अगर ((sysclk >= DA732X_MCLK_20MHZ) &&
	    (sysclk < DA732X_MCLK_40MHZ)) अणु
		val = DA732X_MCLK_VAL_20_40MHZ;
	पूर्ण अन्यथा अगर ((sysclk >= DA732X_MCLK_40MHZ) &&
	    (sysclk <= DA732X_MCLK_54MHZ)) अणु
		val = DA732X_MCLK_VAL_40_54MHZ;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, DA732X_REG_PLL_CTRL, val);

	वापस val;
पूर्ण

अटल व्योम da732x_set_अक्षरge_pump(काष्ठा snd_soc_component *component, पूर्णांक state)
अणु
	चयन (state) अणु
	हाल DA732X_ENABLE_CP:
		snd_soc_component_ग_लिखो(component, DA732X_REG_CLK_EN2, DA732X_CP_CLK_EN);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_HP2, DA732X_HP_CP_EN |
			      DA732X_HP_CP_REG | DA732X_HP_CP_PULSESKIP);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_CTRL1, DA732X_CP_EN |
			      DA732X_CP_CTRL_CPVDD1);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_CTRL2,
			      DA732X_CP_MANAGE_MAGNITUDE | DA732X_CP_BOOST);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_CTRL3, DA732X_CP_1MHZ);
		अवरोध;
	हाल DA732X_DISABLE_CP:
		snd_soc_component_ग_लिखो(component, DA732X_REG_CLK_EN2, DA732X_CP_CLK_DIS);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_HP2, DA732X_HP_CP_DIS);
		snd_soc_component_ग_लिखो(component, DA732X_REG_CP_CTRL1, DA723X_CP_DIS);
		अवरोध;
	शेष:
		pr_err("Wrong charge pump state\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(mic_boost_tlv, DA732X_MIC_PRE_VOL_DB_MIN,
				  DA732X_MIC_PRE_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(mic_pga_tlv, DA732X_MIC_VOL_DB_MIN,
				  DA732X_MIC_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(aux_pga_tlv, DA732X_AUX_VOL_DB_MIN,
				  DA732X_AUX_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(hp_pga_tlv, DA732X_HP_VOL_DB_MIN,
				  DA732X_AUX_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(lin2_pga_tlv, DA732X_LIN2_VOL_DB_MIN,
				  DA732X_LIN2_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(lin3_pga_tlv, DA732X_LIN3_VOL_DB_MIN,
				  DA732X_LIN3_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(lin4_pga_tlv, DA732X_LIN4_VOL_DB_MIN,
				  DA732X_LIN4_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_pga_tlv, DA732X_ADC_VOL_DB_MIN,
				  DA732X_ADC_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_pga_tlv, DA732X_DAC_VOL_DB_MIN,
				  DA732X_DAC_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(eq_band_pga_tlv, DA732X_EQ_BAND_VOL_DB_MIN,
				  DA732X_EQ_BAND_VOL_DB_INC, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(eq_overall_tlv, DA732X_EQ_OVERALL_VOL_DB_MIN,
				  DA732X_EQ_OVERALL_VOL_DB_INC, 0);

/* High Pass Filter */
अटल स्थिर अक्षर *da732x_hpf_mode[] = अणु
	"Disable", "Music", "Voice",
पूर्ण;

अटल स्थिर अक्षर *da732x_hpf_music[] = अणु
	"1.8Hz", "3.75Hz", "7.5Hz", "15Hz",
पूर्ण;

अटल स्थिर अक्षर *da732x_hpf_voice[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz",
	"150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da732x_dac1_hpf_mode_क्रमागत,
			    DA732X_REG_DAC1_HPF, DA732X_HPF_MODE_SHIFT,
			    da732x_hpf_mode);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac2_hpf_mode_क्रमागत,
			    DA732X_REG_DAC2_HPF, DA732X_HPF_MODE_SHIFT,
			    da732x_hpf_mode);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac3_hpf_mode_क्रमागत,
			    DA732X_REG_DAC3_HPF, DA732X_HPF_MODE_SHIFT,
			    da732x_hpf_mode);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc1_hpf_mode_क्रमागत,
			    DA732X_REG_ADC1_HPF, DA732X_HPF_MODE_SHIFT,
			    da732x_hpf_mode);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc2_hpf_mode_क्रमागत,
			    DA732X_REG_ADC2_HPF, DA732X_HPF_MODE_SHIFT,
			    da732x_hpf_mode);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac1_hp_filter_क्रमागत,
			    DA732X_REG_DAC1_HPF, DA732X_HPF_MUSIC_SHIFT,
			    da732x_hpf_music);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac2_hp_filter_क्रमागत,
			    DA732X_REG_DAC2_HPF, DA732X_HPF_MUSIC_SHIFT,
			    da732x_hpf_music);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac3_hp_filter_क्रमागत,
			    DA732X_REG_DAC3_HPF, DA732X_HPF_MUSIC_SHIFT,
			    da732x_hpf_music);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc1_hp_filter_क्रमागत,
			    DA732X_REG_ADC1_HPF, DA732X_HPF_MUSIC_SHIFT,
			    da732x_hpf_music);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc2_hp_filter_क्रमागत,
			    DA732X_REG_ADC2_HPF, DA732X_HPF_MUSIC_SHIFT,
			    da732x_hpf_music);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac1_voice_filter_क्रमागत,
			    DA732X_REG_DAC1_HPF, DA732X_HPF_VOICE_SHIFT,
			    da732x_hpf_voice);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac2_voice_filter_क्रमागत,
			    DA732X_REG_DAC2_HPF, DA732X_HPF_VOICE_SHIFT,
			    da732x_hpf_voice);

अटल SOC_ENUM_SINGLE_DECL(da732x_dac3_voice_filter_क्रमागत,
			    DA732X_REG_DAC3_HPF, DA732X_HPF_VOICE_SHIFT,
			    da732x_hpf_voice);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc1_voice_filter_क्रमागत,
			    DA732X_REG_ADC1_HPF, DA732X_HPF_VOICE_SHIFT,
			    da732x_hpf_voice);

अटल SOC_ENUM_SINGLE_DECL(da732x_adc2_voice_filter_क्रमागत,
			    DA732X_REG_ADC2_HPF, DA732X_HPF_VOICE_SHIFT,
			    da732x_hpf_voice);

अटल पूर्णांक da732x_hpf_set(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *क्रमागत_ctrl = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = क्रमागत_ctrl->reg;
	अचिन्हित पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक bits;

	चयन (sel) अणु
	हाल DA732X_HPF_DISABLED:
		bits = DA732X_HPF_DIS;
		अवरोध;
	हाल DA732X_HPF_VOICE:
		bits = DA732X_HPF_VOICE_EN;
		अवरोध;
	हाल DA732X_HPF_MUSIC:
		bits = DA732X_HPF_MUSIC_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, reg, DA732X_HPF_MASK, bits);

	वापस 0;
पूर्ण

अटल पूर्णांक da732x_hpf_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *क्रमागत_ctrl = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = क्रमागत_ctrl->reg;
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg) & DA732X_HPF_MASK;

	चयन (val) अणु
	हाल DA732X_HPF_VOICE_EN:
		ucontrol->value.क्रमागतerated.item[0] = DA732X_HPF_VOICE;
		अवरोध;
	हाल DA732X_HPF_MUSIC_EN:
		ucontrol->value.क्रमागतerated.item[0] = DA732X_HPF_MUSIC;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = DA732X_HPF_DISABLED;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new da732x_snd_controls[] = अणु
	/* Input PGAs */
	SOC_SINGLE_RANGE_TLV("MIC1 Boost Volume", DA732X_REG_MIC1_PRE,
			     DA732X_MICBOOST_SHIFT, DA732X_MICBOOST_MIN,
			     DA732X_MICBOOST_MAX, 0, mic_boost_tlv),
	SOC_SINGLE_RANGE_TLV("MIC2 Boost Volume", DA732X_REG_MIC2_PRE,
			     DA732X_MICBOOST_SHIFT, DA732X_MICBOOST_MIN,
			     DA732X_MICBOOST_MAX, 0, mic_boost_tlv),
	SOC_SINGLE_RANGE_TLV("MIC3 Boost Volume", DA732X_REG_MIC3_PRE,
			     DA732X_MICBOOST_SHIFT, DA732X_MICBOOST_MIN,
			     DA732X_MICBOOST_MAX, 0, mic_boost_tlv),

	/* MICs */
	SOC_SINGLE("MIC1 Switch", DA732X_REG_MIC1, DA732X_MIC_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_RANGE_TLV("MIC1 Volume", DA732X_REG_MIC1,
			     DA732X_MIC_VOL_SHIFT, DA732X_MIC_VOL_VAL_MIN,
			     DA732X_MIC_VOL_VAL_MAX, 0, mic_pga_tlv),
	SOC_SINGLE("MIC2 Switch", DA732X_REG_MIC2, DA732X_MIC_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_RANGE_TLV("MIC2 Volume", DA732X_REG_MIC2,
			     DA732X_MIC_VOL_SHIFT, DA732X_MIC_VOL_VAL_MIN,
			     DA732X_MIC_VOL_VAL_MAX, 0, mic_pga_tlv),
	SOC_SINGLE("MIC3 Switch", DA732X_REG_MIC3, DA732X_MIC_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_RANGE_TLV("MIC3 Volume", DA732X_REG_MIC3,
			     DA732X_MIC_VOL_SHIFT, DA732X_MIC_VOL_VAL_MIN,
			     DA732X_MIC_VOL_VAL_MAX, 0, mic_pga_tlv),

	/* AUXs */
	SOC_SINGLE("AUX1L Switch", DA732X_REG_AUX1L, DA732X_AUX_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("AUX1L Volume", DA732X_REG_AUX1L,
		       DA732X_AUX_VOL_SHIFT, DA732X_AUX_VOL_VAL_MAX,
		       DA732X_NO_INVERT, aux_pga_tlv),
	SOC_SINGLE("AUX1R Switch", DA732X_REG_AUX1R, DA732X_AUX_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("AUX1R Volume", DA732X_REG_AUX1R,
		       DA732X_AUX_VOL_SHIFT, DA732X_AUX_VOL_VAL_MAX,
		       DA732X_NO_INVERT, aux_pga_tlv),

	/* ADCs */
	SOC_DOUBLE_TLV("ADC1 Volume", DA732X_REG_ADC1_SEL,
		       DA732X_ADCL_VOL_SHIFT, DA732X_ADCR_VOL_SHIFT,
		       DA732X_ADC_VOL_VAL_MAX, DA732X_INVERT, adc_pga_tlv),

	SOC_DOUBLE_TLV("ADC2 Volume", DA732X_REG_ADC2_SEL,
		       DA732X_ADCL_VOL_SHIFT, DA732X_ADCR_VOL_SHIFT,
		       DA732X_ADC_VOL_VAL_MAX, DA732X_INVERT, adc_pga_tlv),

	/* DACs */
	SOC_DOUBLE("Digital Playback DAC12 Switch", DA732X_REG_DAC1_SEL,
		   DA732X_DACL_MUTE_SHIFT, DA732X_DACR_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_DOUBLE_R_TLV("Digital Playback DAC12 Volume", DA732X_REG_DAC1_L_VOL,
			 DA732X_REG_DAC1_R_VOL, DA732X_DAC_VOL_SHIFT,
			 DA732X_DAC_VOL_VAL_MAX, DA732X_INVERT, dac_pga_tlv),
	SOC_SINGLE("Digital Playback DAC3 Switch", DA732X_REG_DAC2_SEL,
		   DA732X_DACL_MUTE_SHIFT, DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Digital Playback DAC3 Volume", DA732X_REG_DAC2_L_VOL,
			DA732X_DAC_VOL_SHIFT, DA732X_DAC_VOL_VAL_MAX,
			DA732X_INVERT, dac_pga_tlv),
	SOC_SINGLE("Digital Playback DAC4 Switch", DA732X_REG_DAC2_SEL,
		   DA732X_DACR_MUTE_SHIFT, DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Digital Playback DAC4 Volume", DA732X_REG_DAC2_R_VOL,
		       DA732X_DAC_VOL_SHIFT, DA732X_DAC_VOL_VAL_MAX,
		       DA732X_INVERT, dac_pga_tlv),
	SOC_SINGLE("Digital Playback DAC5 Switch", DA732X_REG_DAC3_SEL,
		   DA732X_DACL_MUTE_SHIFT, DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Digital Playback DAC5 Volume", DA732X_REG_DAC3_VOL,
		       DA732X_DAC_VOL_SHIFT, DA732X_DAC_VOL_VAL_MAX,
		       DA732X_INVERT, dac_pga_tlv),

	/* High Pass Filters */
	SOC_ENUM_EXT("DAC1 High Pass Filter Mode",
		     da732x_dac1_hpf_mode_क्रमागत, da732x_hpf_get, da732x_hpf_set),
	SOC_ENUM("DAC1 High Pass Filter", da732x_dac1_hp_filter_क्रमागत),
	SOC_ENUM("DAC1 Voice Filter", da732x_dac1_voice_filter_क्रमागत),

	SOC_ENUM_EXT("DAC2 High Pass Filter Mode",
		     da732x_dac2_hpf_mode_क्रमागत, da732x_hpf_get, da732x_hpf_set),
	SOC_ENUM("DAC2 High Pass Filter", da732x_dac2_hp_filter_क्रमागत),
	SOC_ENUM("DAC2 Voice Filter", da732x_dac2_voice_filter_क्रमागत),

	SOC_ENUM_EXT("DAC3 High Pass Filter Mode",
		     da732x_dac3_hpf_mode_क्रमागत, da732x_hpf_get, da732x_hpf_set),
	SOC_ENUM("DAC3 High Pass Filter", da732x_dac3_hp_filter_क्रमागत),
	SOC_ENUM("DAC3 Filter Mode", da732x_dac3_voice_filter_क्रमागत),

	SOC_ENUM_EXT("ADC1 High Pass Filter Mode",
		     da732x_adc1_hpf_mode_क्रमागत, da732x_hpf_get, da732x_hpf_set),
	SOC_ENUM("ADC1 High Pass Filter", da732x_adc1_hp_filter_क्रमागत),
	SOC_ENUM("ADC1 Voice Filter", da732x_adc1_voice_filter_क्रमागत),

	SOC_ENUM_EXT("ADC2 High Pass Filter Mode",
		     da732x_adc2_hpf_mode_क्रमागत, da732x_hpf_get, da732x_hpf_set),
	SOC_ENUM("ADC2 High Pass Filter", da732x_adc2_hp_filter_क्रमागत),
	SOC_ENUM("ADC2 Voice Filter", da732x_adc2_voice_filter_क्रमागत),

	/* Equalizers */
	SOC_SINGLE("ADC1 EQ Switch", DA732X_REG_ADC1_EQ5,
		   DA732X_EQ_EN_SHIFT, DA732X_EQ_EN_MAX, DA732X_NO_INVERT),
	SOC_SINGLE_TLV("ADC1 EQ Band 1 Volume", DA732X_REG_ADC1_EQ12,
		       DA732X_EQ_BAND1_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC1 EQ Band 2 Volume", DA732X_REG_ADC1_EQ12,
		       DA732X_EQ_BAND2_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC1 EQ Band 3 Volume", DA732X_REG_ADC1_EQ34,
		       DA732X_EQ_BAND3_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC1 EQ Band 4 Volume", DA732X_REG_ADC1_EQ34,
		       DA732X_EQ_BAND4_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC1 EQ Band 5 Volume", DA732X_REG_ADC1_EQ5,
		       DA732X_EQ_BAND5_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC1 EQ Overall Volume", DA732X_REG_ADC1_EQ5,
		       DA732X_EQ_OVERALL_SHIFT, DA732X_EQ_OVERALL_VOL_VAL_MAX,
		       DA732X_INVERT, eq_overall_tlv),

	SOC_SINGLE("ADC2 EQ Switch", DA732X_REG_ADC2_EQ5,
		   DA732X_EQ_EN_SHIFT, DA732X_EQ_EN_MAX, DA732X_NO_INVERT),
	SOC_SINGLE_TLV("ADC2 EQ Band 1 Volume", DA732X_REG_ADC2_EQ12,
		       DA732X_EQ_BAND1_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC2 EQ Band 2 Volume", DA732X_REG_ADC2_EQ12,
		       DA732X_EQ_BAND2_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC2 EQ Band 3 Volume", DA732X_REG_ADC2_EQ34,
		       DA732X_EQ_BAND3_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ACD2 EQ Band 4 Volume", DA732X_REG_ADC2_EQ34,
		       DA732X_EQ_BAND4_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ACD2 EQ Band 5 Volume", DA732X_REG_ADC2_EQ5,
		       DA732X_EQ_BAND5_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("ADC2 EQ Overall Volume", DA732X_REG_ADC1_EQ5,
		       DA732X_EQ_OVERALL_SHIFT, DA732X_EQ_OVERALL_VOL_VAL_MAX,
		       DA732X_INVERT, eq_overall_tlv),

	SOC_SINGLE("DAC1 EQ Switch", DA732X_REG_DAC1_EQ5,
		   DA732X_EQ_EN_SHIFT, DA732X_EQ_EN_MAX, DA732X_NO_INVERT),
	SOC_SINGLE_TLV("DAC1 EQ Band 1 Volume", DA732X_REG_DAC1_EQ12,
		       DA732X_EQ_BAND1_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC1 EQ Band 2 Volume", DA732X_REG_DAC1_EQ12,
		       DA732X_EQ_BAND2_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC1 EQ Band 3 Volume", DA732X_REG_DAC1_EQ34,
		       DA732X_EQ_BAND3_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC1 EQ Band 4 Volume", DA732X_REG_DAC1_EQ34,
		       DA732X_EQ_BAND4_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC1 EQ Band 5 Volume", DA732X_REG_DAC1_EQ5,
		       DA732X_EQ_BAND5_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),

	SOC_SINGLE("DAC2 EQ Switch", DA732X_REG_DAC2_EQ5,
		   DA732X_EQ_EN_SHIFT, DA732X_EQ_EN_MAX, DA732X_NO_INVERT),
	SOC_SINGLE_TLV("DAC2 EQ Band 1 Volume", DA732X_REG_DAC2_EQ12,
		       DA732X_EQ_BAND1_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC2 EQ Band 2 Volume", DA732X_REG_DAC2_EQ12,
		       DA732X_EQ_BAND2_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC2 EQ Band 3 Volume", DA732X_REG_DAC2_EQ34,
		       DA732X_EQ_BAND3_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC2 EQ Band 4 Volume", DA732X_REG_DAC2_EQ34,
		       DA732X_EQ_BAND4_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC2 EQ Band 5 Volume", DA732X_REG_DAC2_EQ5,
		       DA732X_EQ_BAND5_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),

	SOC_SINGLE("DAC3 EQ Switch", DA732X_REG_DAC3_EQ5,
		   DA732X_EQ_EN_SHIFT, DA732X_EQ_EN_MAX, DA732X_NO_INVERT),
	SOC_SINGLE_TLV("DAC3 EQ Band 1 Volume", DA732X_REG_DAC3_EQ12,
		       DA732X_EQ_BAND1_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC3 EQ Band 2 Volume", DA732X_REG_DAC3_EQ12,
		       DA732X_EQ_BAND2_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC3 EQ Band 3 Volume", DA732X_REG_DAC3_EQ34,
		       DA732X_EQ_BAND3_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC3 EQ Band 4 Volume", DA732X_REG_DAC3_EQ34,
		       DA732X_EQ_BAND4_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),
	SOC_SINGLE_TLV("DAC3 EQ Band 5 Volume", DA732X_REG_DAC3_EQ5,
		       DA732X_EQ_BAND5_SHIFT, DA732X_EQ_VOL_VAL_MAX,
		       DA732X_INVERT, eq_band_pga_tlv),

	/* Lineout 2 Reciever*/
	SOC_SINGLE("Lineout 2 Switch", DA732X_REG_LIN2, DA732X_LOUT_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Lineout 2 Volume", DA732X_REG_LIN2,
		       DA732X_LOUT_VOL_SHIFT, DA732X_LOUT_VOL_VAL_MAX,
		       DA732X_NO_INVERT, lin2_pga_tlv),

	/* Lineout 3 SPEAKER*/
	SOC_SINGLE("Lineout 3 Switch", DA732X_REG_LIN3, DA732X_LOUT_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Lineout 3 Volume", DA732X_REG_LIN3,
		       DA732X_LOUT_VOL_SHIFT, DA732X_LOUT_VOL_VAL_MAX,
		       DA732X_NO_INVERT, lin3_pga_tlv),

	/* Lineout 4 */
	SOC_SINGLE("Lineout 4 Switch", DA732X_REG_LIN4, DA732X_LOUT_MUTE_SHIFT,
		   DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_SINGLE_TLV("Lineout 4 Volume", DA732X_REG_LIN4,
		       DA732X_LOUT_VOL_SHIFT, DA732X_LOUT_VOL_VAL_MAX,
		       DA732X_NO_INVERT, lin4_pga_tlv),

	/* Headphones */
	SOC_DOUBLE_R("Headphone Switch", DA732X_REG_HPR, DA732X_REG_HPL,
		     DA732X_HP_MUTE_SHIFT, DA732X_SWITCH_MAX, DA732X_INVERT),
	SOC_DOUBLE_R_TLV("Headphone Volume", DA732X_REG_HPL_VOL,
			 DA732X_REG_HPR_VOL, DA732X_HP_VOL_SHIFT,
			 DA732X_HP_VOL_VAL_MAX, DA732X_NO_INVERT, hp_pga_tlv),
पूर्ण;

अटल पूर्णांक da732x_adc_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		चयन (w->reg) अणु
		हाल DA732X_REG_ADC1_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCA_BB_CLK_EN,
					    DA732X_ADCA_BB_CLK_EN);
			अवरोध;
		हाल DA732X_REG_ADC2_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCC_BB_CLK_EN,
					    DA732X_ADCC_BB_CLK_EN);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_RST_MASK,
				    DA732X_ADC_SET_ACT);
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_PD_MASK,
				    DA732X_ADC_ON);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_PD_MASK,
				    DA732X_ADC_OFF);
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_RST_MASK,
				    DA732X_ADC_SET_RST);

		चयन (w->reg) अणु
		हाल DA732X_REG_ADC1_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCA_BB_CLK_EN, 0);
			अवरोध;
		हाल DA732X_REG_ADC2_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCC_BB_CLK_EN, 0);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da732x_out_pga_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, w->reg,
				    (1 << w->shअगरt) | DA732X_OUT_HIZ_EN,
				    (1 << w->shअगरt) | DA732X_OUT_HIZ_EN);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg,
				    (1 << w->shअगरt) | DA732X_OUT_HIZ_EN,
				    (1 << w->shअगरt) | DA732X_OUT_HIZ_DIS);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *adcl_text[] = अणु
	"AUX1L", "MIC1"
पूर्ण;

अटल स्थिर अक्षर *adcr_text[] = अणु
	"AUX1R", "MIC2", "MIC3"
पूर्ण;

अटल स्थिर अक्षर *enable_text[] = अणु
	"Disabled",
	"Enabled"
पूर्ण;

/* ADC1LMUX */
अटल SOC_ENUM_SINGLE_DECL(adc1l_क्रमागत,
			    DA732X_REG_INP_MUX, DA732X_ADC1L_MUX_SEL_SHIFT,
			    adcl_text);
अटल स्थिर काष्ठा snd_kcontrol_new adc1l_mux =
	SOC_DAPM_ENUM("ADC Route", adc1l_क्रमागत);

/* ADC1RMUX */
अटल SOC_ENUM_SINGLE_DECL(adc1r_क्रमागत,
			    DA732X_REG_INP_MUX, DA732X_ADC1R_MUX_SEL_SHIFT,
			    adcr_text);
अटल स्थिर काष्ठा snd_kcontrol_new adc1r_mux =
	SOC_DAPM_ENUM("ADC Route", adc1r_क्रमागत);

/* ADC2LMUX */
अटल SOC_ENUM_SINGLE_DECL(adc2l_क्रमागत,
			    DA732X_REG_INP_MUX, DA732X_ADC2L_MUX_SEL_SHIFT,
			    adcl_text);
अटल स्थिर काष्ठा snd_kcontrol_new adc2l_mux =
	SOC_DAPM_ENUM("ADC Route", adc2l_क्रमागत);

/* ADC2RMUX */
अटल SOC_ENUM_SINGLE_DECL(adc2r_क्रमागत,
			    DA732X_REG_INP_MUX, DA732X_ADC2R_MUX_SEL_SHIFT,
			    adcr_text);

अटल स्थिर काष्ठा snd_kcontrol_new adc2r_mux =
	SOC_DAPM_ENUM("ADC Route", adc2r_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(da732x_hp_left_output,
			    DA732X_REG_HPL, DA732X_HP_OUT_DAC_EN_SHIFT,
			    enable_text);

अटल स्थिर काष्ठा snd_kcontrol_new hpl_mux =
	SOC_DAPM_ENUM("HPL Switch", da732x_hp_left_output);

अटल SOC_ENUM_SINGLE_DECL(da732x_hp_right_output,
			    DA732X_REG_HPR, DA732X_HP_OUT_DAC_EN_SHIFT,
			    enable_text);

अटल स्थिर काष्ठा snd_kcontrol_new hpr_mux =
	SOC_DAPM_ENUM("HPR Switch", da732x_hp_right_output);

अटल SOC_ENUM_SINGLE_DECL(da732x_speaker_output,
			    DA732X_REG_LIN3, DA732X_LOUT_DAC_EN_SHIFT,
			    enable_text);

अटल स्थिर काष्ठा snd_kcontrol_new spk_mux =
	SOC_DAPM_ENUM("SPK Switch", da732x_speaker_output);

अटल SOC_ENUM_SINGLE_DECL(da732x_lout4_output,
			    DA732X_REG_LIN4, DA732X_LOUT_DAC_EN_SHIFT,
			    enable_text);

अटल स्थिर काष्ठा snd_kcontrol_new lout4_mux =
	SOC_DAPM_ENUM("LOUT4 Switch", da732x_lout4_output);

अटल SOC_ENUM_SINGLE_DECL(da732x_lout2_output,
			    DA732X_REG_LIN2, DA732X_LOUT_DAC_EN_SHIFT,
			    enable_text);

अटल स्थिर काष्ठा snd_kcontrol_new lout2_mux =
	SOC_DAPM_ENUM("LOUT2 Switch", da732x_lout2_output);

अटल स्थिर काष्ठा snd_soc_dapm_widget da732x_dapm_widमाला_लो[] = अणु
	/* Supplies */
	SND_SOC_DAPM_SUPPLY("ADC1 Supply", DA732X_REG_ADC1_PD, 0,
			    DA732X_NO_INVERT, da732x_adc_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("ADC2 Supply", DA732X_REG_ADC2_PD, 0,
			    DA732X_NO_INVERT, da732x_adc_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("DAC1 CLK", DA732X_REG_CLK_EN4,
			    DA732X_DACA_BB_CLK_SHIFT, DA732X_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC2 CLK", DA732X_REG_CLK_EN4,
			    DA732X_DACC_BB_CLK_SHIFT, DA732X_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC3 CLK", DA732X_REG_CLK_EN5,
			    DA732X_DACE_BB_CLK_SHIFT, DA732X_NO_INVERT,
			    शून्य, 0),

	/* Micbias */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", DA732X_REG_MICBIAS1,
			    DA732X_MICBIAS_EN_SHIFT,
			    DA732X_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS2", DA732X_REG_MICBIAS2,
			    DA732X_MICBIAS_EN_SHIFT,
			    DA732X_NO_INVERT, शून्य, 0),

	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),
	SND_SOC_DAPM_INPUT("AUX1L"),
	SND_SOC_DAPM_INPUT("AUX1R"),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("ClassD"),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1L", शून्य, DA732X_REG_ADC1_SEL,
			 DA732X_ADCL_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_ADC("ADC1R", शून्य, DA732X_REG_ADC1_SEL,
			 DA732X_ADCR_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_ADC("ADC2L", शून्य, DA732X_REG_ADC2_SEL,
			 DA732X_ADCL_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_ADC("ADC2R", शून्य, DA732X_REG_ADC2_SEL,
			 DA732X_ADCR_EN_SHIFT, DA732X_NO_INVERT),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC1L", शून्य, DA732X_REG_DAC1_SEL,
			 DA732X_DACL_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_DAC("DAC1R", शून्य, DA732X_REG_DAC1_SEL,
			 DA732X_DACR_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_DAC("DAC2L", शून्य, DA732X_REG_DAC2_SEL,
			 DA732X_DACL_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_DAC("DAC2R", शून्य, DA732X_REG_DAC2_SEL,
			 DA732X_DACR_EN_SHIFT, DA732X_NO_INVERT),
	SND_SOC_DAPM_DAC("DAC3", शून्य, DA732X_REG_DAC3_SEL,
			 DA732X_DACL_EN_SHIFT, DA732X_NO_INVERT),

	/* Input Pgas */
	SND_SOC_DAPM_PGA("MIC1 PGA", DA732X_REG_MIC1, DA732X_MIC_EN_SHIFT,
			 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC2 PGA", DA732X_REG_MIC2, DA732X_MIC_EN_SHIFT,
			 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC3 PGA", DA732X_REG_MIC3, DA732X_MIC_EN_SHIFT,
			 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX1L PGA", DA732X_REG_AUX1L, DA732X_AUX_EN_SHIFT,
			 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX1R PGA", DA732X_REG_AUX1R, DA732X_AUX_EN_SHIFT,
			 0, शून्य, 0),

	SND_SOC_DAPM_PGA_E("HP Left", DA732X_REG_HPL, DA732X_HP_OUT_EN_SHIFT,
			   0, शून्य, 0, da732x_out_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("HP Right", DA732X_REG_HPR, DA732X_HP_OUT_EN_SHIFT,
			   0, शून्य, 0, da732x_out_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LIN2", DA732X_REG_LIN2, DA732X_LIN_OUT_EN_SHIFT,
			   0, शून्य, 0, da732x_out_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LIN3", DA732X_REG_LIN3, DA732X_LIN_OUT_EN_SHIFT,
			   0, शून्य, 0, da732x_out_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LIN4", DA732X_REG_LIN4, DA732X_LIN_OUT_EN_SHIFT,
			   0, शून्य, 0, da732x_out_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* MUXs */
	SND_SOC_DAPM_MUX("ADC1 Left MUX", SND_SOC_NOPM, 0, 0, &adc1l_mux),
	SND_SOC_DAPM_MUX("ADC1 Right MUX", SND_SOC_NOPM, 0, 0, &adc1r_mux),
	SND_SOC_DAPM_MUX("ADC2 Left MUX", SND_SOC_NOPM, 0, 0, &adc2l_mux),
	SND_SOC_DAPM_MUX("ADC2 Right MUX", SND_SOC_NOPM, 0, 0, &adc2r_mux),

	SND_SOC_DAPM_MUX("HP Left MUX", SND_SOC_NOPM, 0, 0, &hpl_mux),
	SND_SOC_DAPM_MUX("HP Right MUX", SND_SOC_NOPM, 0, 0, &hpr_mux),
	SND_SOC_DAPM_MUX("Speaker MUX", SND_SOC_NOPM, 0, 0, &spk_mux),
	SND_SOC_DAPM_MUX("LOUT2 MUX", SND_SOC_NOPM, 0, 0, &lout2_mux),
	SND_SOC_DAPM_MUX("LOUT4 MUX", SND_SOC_NOPM, 0, 0, &lout4_mux),

	/* AIF पूर्णांकerfaces */
	SND_SOC_DAPM_AIF_OUT("AIFA Output", "AIFA Capture", 0, DA732X_REG_AIFA3,
			     DA732X_AIF_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("AIFA Input", "AIFA Playback", 0, DA732X_REG_AIFA3,
			    DA732X_AIF_EN_SHIFT, 0),

	SND_SOC_DAPM_AIF_OUT("AIFB Output", "AIFB Capture", 0, DA732X_REG_AIFB3,
			     DA732X_AIF_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("AIFB Input", "AIFB Playback", 0, DA732X_REG_AIFB3,
			    DA732X_AIF_EN_SHIFT, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route da732x_dapm_routes[] = अणु
	/* Inमाला_दो */
	अणु"AUX1L PGA", शून्य, "AUX1L"पूर्ण,
	अणु"AUX1R PGA", शून्य, "AUX1R"पूर्ण,
	अणु"MIC1 PGA", शून्य, "MIC1"पूर्ण,
	अणु"MIC2 PGA", शून्य, "MIC2"पूर्ण,
	अणु"MIC3 PGA", शून्य, "MIC3"पूर्ण,

	/* Capture Path */
	अणु"ADC1 Left MUX", "MIC1", "MIC1 PGA"पूर्ण,
	अणु"ADC1 Left MUX", "AUX1L", "AUX1L PGA"पूर्ण,

	अणु"ADC1 Right MUX", "AUX1R", "AUX1R PGA"पूर्ण,
	अणु"ADC1 Right MUX", "MIC2", "MIC2 PGA"पूर्ण,
	अणु"ADC1 Right MUX", "MIC3", "MIC3 PGA"पूर्ण,

	अणु"ADC2 Left MUX", "AUX1L", "AUX1L PGA"पूर्ण,
	अणु"ADC2 Left MUX", "MIC1", "MIC1 PGA"पूर्ण,

	अणु"ADC2 Right MUX", "AUX1R", "AUX1R PGA"पूर्ण,
	अणु"ADC2 Right MUX", "MIC2", "MIC2 PGA"पूर्ण,
	अणु"ADC2 Right MUX", "MIC3", "MIC3 PGA"पूर्ण,

	अणु"ADC1L", शून्य, "ADC1 Supply"पूर्ण,
	अणु"ADC1R", शून्य, "ADC1 Supply"पूर्ण,
	अणु"ADC2L", शून्य, "ADC2 Supply"पूर्ण,
	अणु"ADC2R", शून्य, "ADC2 Supply"पूर्ण,

	अणु"ADC1L", शून्य, "ADC1 Left MUX"पूर्ण,
	अणु"ADC1R", शून्य, "ADC1 Right MUX"पूर्ण,
	अणु"ADC2L", शून्य, "ADC2 Left MUX"पूर्ण,
	अणु"ADC2R", शून्य, "ADC2 Right MUX"पूर्ण,

	अणु"AIFA Output", शून्य, "ADC1L"पूर्ण,
	अणु"AIFA Output", शून्य, "ADC1R"पूर्ण,
	अणु"AIFB Output", शून्य, "ADC2L"पूर्ण,
	अणु"AIFB Output", शून्य, "ADC2R"पूर्ण,

	अणु"HP Left MUX", "Enabled", "AIFA Input"पूर्ण,
	अणु"HP Right MUX", "Enabled", "AIFA Input"पूर्ण,
	अणु"Speaker MUX", "Enabled", "AIFB Input"पूर्ण,
	अणु"LOUT2 MUX", "Enabled", "AIFB Input"पूर्ण,
	अणु"LOUT4 MUX", "Enabled", "AIFB Input"पूर्ण,

	अणु"DAC1L", शून्य, "DAC1 CLK"पूर्ण,
	अणु"DAC1R", शून्य, "DAC1 CLK"पूर्ण,
	अणु"DAC2L", शून्य, "DAC2 CLK"पूर्ण,
	अणु"DAC2R", शून्य, "DAC2 CLK"पूर्ण,
	अणु"DAC3", शून्य, "DAC3 CLK"पूर्ण,

	अणु"DAC1L", शून्य, "HP Left MUX"पूर्ण,
	अणु"DAC1R", शून्य, "HP Right MUX"पूर्ण,
	अणु"DAC2L", शून्य, "Speaker MUX"पूर्ण,
	अणु"DAC2R", शून्य, "LOUT4 MUX"पूर्ण,
	अणु"DAC3", शून्य, "LOUT2 MUX"पूर्ण,

	/* Output Pgas */
	अणु"HP Left", शून्य, "DAC1L"पूर्ण,
	अणु"HP Right", शून्य, "DAC1R"पूर्ण,
	अणु"LIN3", शून्य, "DAC2L"पूर्ण,
	अणु"LIN4", शून्य, "DAC2R"पूर्ण,
	अणु"LIN2", शून्य, "DAC3"पूर्ण,

	/* Outमाला_दो */
	अणु"ClassD", शून्य, "LIN3"पूर्ण,
	अणु"LOUTL", शून्य, "LIN2"पूर्ण,
	अणु"LOUTR", शून्य, "LIN4"पूर्ण,
	अणु"HPL", शून्य, "HP Left"पूर्ण,
	अणु"HPR", शून्य, "HP Right"पूर्ण,
पूर्ण;

अटल पूर्णांक da732x_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u32 aअगर = 0;
	u32 reg_aअगर;
	u32 fs;

	reg_aअगर = dai->driver->base;

	चयन (params_width(params)) अणु
	हाल 16:
		aअगर |= DA732X_AIF_WORD_16;
		अवरोध;
	हाल 20:
		aअगर |= DA732X_AIF_WORD_20;
		अवरोध;
	हाल 24:
		aअगर |= DA732X_AIF_WORD_24;
		अवरोध;
	हाल 32:
		aअगर |= DA732X_AIF_WORD_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs = DA732X_SR_8KHZ;
		अवरोध;
	हाल 11025:
		fs = DA732X_SR_11_025KHZ;
		अवरोध;
	हाल 12000:
		fs = DA732X_SR_12KHZ;
		अवरोध;
	हाल 16000:
		fs = DA732X_SR_16KHZ;
		अवरोध;
	हाल 22050:
		fs = DA732X_SR_22_05KHZ;
		अवरोध;
	हाल 24000:
		fs = DA732X_SR_24KHZ;
		अवरोध;
	हाल 32000:
		fs = DA732X_SR_32KHZ;
		अवरोध;
	हाल 44100:
		fs = DA732X_SR_44_1KHZ;
		अवरोध;
	हाल 48000:
		fs = DA732X_SR_48KHZ;
		अवरोध;
	हाल 88100:
		fs = DA732X_SR_88_1KHZ;
		अवरोध;
	हाल 96000:
		fs = DA732X_SR_96KHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, reg_aअगर, DA732X_AIF_WORD_MASK, aअगर);
	snd_soc_component_update_bits(component, DA732X_REG_CLK_CTRL, DA732X_SR1_MASK, fs);

	वापस 0;
पूर्ण

अटल पूर्णांक da732x_set_dai_fmt(काष्ठा snd_soc_dai *dai, u32 fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u32 aअगर_mclk, pc_count;
	u32 reg_aअगर1, aअगर1;
	u32 reg_aअगर3, aअगर3;

	चयन (dai->id) अणु
	हाल DA732X_DAI_ID1:
		reg_aअगर1 = DA732X_REG_AIFA1;
		reg_aअगर3 = DA732X_REG_AIFA3;
		pc_count = DA732X_PC_PULSE_AIFA | DA732X_PC_RESYNC_NOT_AUT |
			   DA732X_PC_SAME;
		अवरोध;
	हाल DA732X_DAI_ID2:
		reg_aअगर1 = DA732X_REG_AIFB1;
		reg_aअगर3 = DA732X_REG_AIFB3;
		pc_count = DA732X_PC_PULSE_AIFB | DA732X_PC_RESYNC_NOT_AUT |
			   DA732X_PC_SAME;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		aअगर1 = DA732X_AIF_SLAVE;
		aअगर_mclk = DA732X_AIFM_FRAME_64 | DA732X_AIFM_SRC_SEL_AIFA;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर1 = DA732X_AIF_CLK_FROM_SRC;
		aअगर_mclk = DA732X_CLK_GENERATION_AIF_A;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		aअगर3 = DA732X_AIF_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		aअगर3 = DA732X_AIF_RIGHT_J_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर3 = DA732X_AIF_LEFT_J_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर3 = DA732X_AIF_DSP_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clock inversion */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर3 |= DA732X_AIF_BCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			aअगर3 |= DA732X_AIF_BCLK_INV | DA732X_AIF_WCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर3 |= DA732X_AIF_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर3 |= DA732X_AIF_WCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, DA732X_REG_AIF_MCLK, aअगर_mclk);
	snd_soc_component_update_bits(component, reg_aअगर1, DA732X_AIF1_CLK_MASK, aअगर1);
	snd_soc_component_update_bits(component, reg_aअगर3, DA732X_AIF_BCLK_INV |
			    DA732X_AIF_WCLK_INV | DA732X_AIF_MODE_MASK, aअगर3);
	snd_soc_component_ग_लिखो(component, DA732X_REG_PC_CTRL, pc_count);

	वापस 0;
पूर्ण



अटल पूर्णांक da732x_set_dai_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			      अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा da732x_priv *da732x = snd_soc_component_get_drvdata(component);
	पूर्णांक fref, inभाग;
	u8 भाग_lo, भाग_mid, भाग_hi;
	u64 frac_भाग;

	/* Disable PLL */
	अगर (freq_out == 0) अणु
		snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL,
				    DA732X_PLL_EN, 0);
		da732x->pll_en = false;
		वापस 0;
	पूर्ण

	अगर (da732x->pll_en)
		वापस -EBUSY;

	अगर (source == DA732X_SRCCLK_MCLK) अणु
		/* Validate Sysclk rate */
		चयन (da732x->sysclk) अणु
		हाल 11290000:
		हाल 12288000:
		हाल 22580000:
		हाल 24576000:
		हाल 45160000:
		हाल 49152000:
			snd_soc_component_ग_लिखो(component, DA732X_REG_PLL_CTRL,
				      DA732X_PLL_BYPASS);
			वापस 0;
		शेष:
			dev_err(component->dev,
				"Cannot use PLL Bypass, invalid SYSCLK rate\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	inभाग = da732x_get_input_भाग(component, da732x->sysclk);
	अगर (inभाग < 0)
		वापस inभाग;

	fref = da732x->sysclk / BIT(inभाग);
	भाग_hi = freq_out / fref;
	frac_भाग = (u64)(freq_out % fref) * 8192ULL;
	करो_भाग(frac_भाग, fref);
	भाग_mid = (frac_भाग >> DA732X_1BYTE_SHIFT) & DA732X_U8_MASK;
	भाग_lo = (frac_भाग) & DA732X_U8_MASK;

	snd_soc_component_ग_लिखो(component, DA732X_REG_PLL_DIV_LO, भाग_lo);
	snd_soc_component_ग_लिखो(component, DA732X_REG_PLL_DIV_MID, भाग_mid);
	snd_soc_component_ग_लिखो(component, DA732X_REG_PLL_DIV_HI, भाग_hi);

	snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL, DA732X_PLL_EN,
			    DA732X_PLL_EN);

	da732x->pll_en = true;

	वापस 0;
पूर्ण

अटल पूर्णांक da732x_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da732x_priv *da732x = snd_soc_component_get_drvdata(component);

	da732x->sysclk = freq;

	वापस 0;
पूर्ण

#घोषणा DA732X_RATES	SNDRV_PCM_RATE_8000_96000

#घोषणा	DA732X_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops da732x_dai_ops = अणु
	.hw_params	= da732x_hw_params,
	.set_fmt	= da732x_set_dai_fmt,
	.set_sysclk	= da732x_set_dai_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver da732x_dai[] = अणु
	अणु
		.name	= "DA732X_AIFA",
		.id	= DA732X_DAI_ID1,
		.base	= DA732X_REG_AIFA1,
		.playback = अणु
			.stream_name = "AIFA Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = DA732X_RATES,
			.क्रमmats = DA732X_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIFA Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = DA732X_RATES,
			.क्रमmats = DA732X_FORMATS,
		पूर्ण,
		.ops = &da732x_dai_ops,
	पूर्ण,
	अणु
		.name	= "DA732X_AIFB",
		.id	= DA732X_DAI_ID2,
		.base	= DA732X_REG_AIFB1,
		.playback = अणु
			.stream_name = "AIFB Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = DA732X_RATES,
			.क्रमmats = DA732X_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIFB Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = DA732X_RATES,
			.क्रमmats = DA732X_FORMATS,
		पूर्ण,
		.ops = &da732x_dai_ops,
	पूर्ण,
पूर्ण;

अटल bool da732x_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA732X_REG_HPL_DAC_OFF_CNTL:
	हाल DA732X_REG_HPR_DAC_OFF_CNTL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config da732x_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,

	.max_रेजिस्टर		= DA732X_MAX_REG,
	.अस्थिर_reg		= da732x_अस्थिर,
	.reg_शेषs		= da732x_reg_cache,
	.num_reg_शेषs	= ARRAY_SIZE(da732x_reg_cache),
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;


अटल व्योम da732x_dac_offset_adjust(काष्ठा snd_soc_component *component)
अणु
	u8 offset[DA732X_HP_DACS];
	u8 sign[DA732X_HP_DACS];
	u8 step = DA732X_DAC_OFFSET_STEP;

	/* Initialize DAC offset calibration circuits and रेजिस्टरs */
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_DAC_OFFSET,
		      DA732X_HP_DAC_OFFSET_TRIM_VAL);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_DAC_OFFSET,
		      DA732X_HP_DAC_OFFSET_TRIM_VAL);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_DAC_OFF_CNTL,
		      DA732X_HP_DAC_OFF_CALIBRATION |
		      DA732X_HP_DAC_OFF_SCALE_STEPS);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_DAC_OFF_CNTL,
		      DA732X_HP_DAC_OFF_CALIBRATION |
		      DA732X_HP_DAC_OFF_SCALE_STEPS);

	/* Wait क्रम voltage stabilization */
	msleep(DA732X_WAIT_FOR_STABILIZATION);

	/* Check DAC offset sign */
	sign[DA732X_HPL_DAC] = (snd_soc_component_पढ़ो(component, DA732X_REG_HPL_DAC_OFF_CNTL) &
				DA732X_HP_DAC_OFF_CNTL_COMPO);
	sign[DA732X_HPR_DAC] = (snd_soc_component_पढ़ो(component, DA732X_REG_HPR_DAC_OFF_CNTL) &
				DA732X_HP_DAC_OFF_CNTL_COMPO);

	/* Binary search DAC offset values (both channels at once) */
	offset[DA732X_HPL_DAC] = sign[DA732X_HPL_DAC] << DA732X_HP_DAC_COMPO_SHIFT;
	offset[DA732X_HPR_DAC] = sign[DA732X_HPR_DAC] << DA732X_HP_DAC_COMPO_SHIFT;

	करो अणु
		offset[DA732X_HPL_DAC] |= step;
		offset[DA732X_HPR_DAC] |= step;
		snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_DAC_OFFSET,
			      ~offset[DA732X_HPL_DAC] & DA732X_HP_DAC_OFF_MASK);
		snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_DAC_OFFSET,
			      ~offset[DA732X_HPR_DAC] & DA732X_HP_DAC_OFF_MASK);

		msleep(DA732X_WAIT_FOR_STABILIZATION);

		अगर ((snd_soc_component_पढ़ो(component, DA732X_REG_HPL_DAC_OFF_CNTL) &
		     DA732X_HP_DAC_OFF_CNTL_COMPO) ^ sign[DA732X_HPL_DAC])
			offset[DA732X_HPL_DAC] &= ~step;
		अगर ((snd_soc_component_पढ़ो(component, DA732X_REG_HPR_DAC_OFF_CNTL) &
		     DA732X_HP_DAC_OFF_CNTL_COMPO) ^ sign[DA732X_HPR_DAC])
			offset[DA732X_HPR_DAC] &= ~step;

		step >>= 1;
	पूर्ण जबतक (step);

	/* Write final DAC offsets to रेजिस्टरs */
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_DAC_OFFSET,
		      ~offset[DA732X_HPL_DAC] &	DA732X_HP_DAC_OFF_MASK);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_DAC_OFFSET,
		      ~offset[DA732X_HPR_DAC] &	DA732X_HP_DAC_OFF_MASK);

	/* End DAC calibration mode */
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_DAC_OFF_CNTL,
		DA732X_HP_DAC_OFF_SCALE_STEPS);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_DAC_OFF_CNTL,
		DA732X_HP_DAC_OFF_SCALE_STEPS);
पूर्ण

अटल व्योम da732x_output_offset_adjust(काष्ठा snd_soc_component *component)
अणु
	u8 offset[DA732X_HP_AMPS];
	u8 sign[DA732X_HP_AMPS];
	u8 step = DA732X_OUTPUT_OFFSET_STEP;

	offset[DA732X_HPL_AMP] = DA732X_HP_OUT_TRIM_VAL;
	offset[DA732X_HPR_AMP] = DA732X_HP_OUT_TRIM_VAL;

	/* Initialize output offset calibration circuits and रेजिस्टरs  */
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_OUT_OFFSET, DA732X_HP_OUT_TRIM_VAL);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_OUT_OFFSET, DA732X_HP_OUT_TRIM_VAL);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL,
		      DA732X_HP_OUT_COMP | DA732X_HP_OUT_EN);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR,
		      DA732X_HP_OUT_COMP | DA732X_HP_OUT_EN);

	/* Wait क्रम voltage stabilization */
	msleep(DA732X_WAIT_FOR_STABILIZATION);

	/* Check output offset sign */
	sign[DA732X_HPL_AMP] = snd_soc_component_पढ़ो(component, DA732X_REG_HPL) &
			       DA732X_HP_OUT_COMPO;
	sign[DA732X_HPR_AMP] = snd_soc_component_पढ़ो(component, DA732X_REG_HPR) &
			       DA732X_HP_OUT_COMPO;

	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL, DA732X_HP_OUT_COMP |
		      (sign[DA732X_HPL_AMP] >> DA732X_HP_OUT_COMPO_SHIFT) |
		      DA732X_HP_OUT_EN);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR, DA732X_HP_OUT_COMP |
		      (sign[DA732X_HPR_AMP] >> DA732X_HP_OUT_COMPO_SHIFT) |
		      DA732X_HP_OUT_EN);

	/* Binary search output offset values (both channels at once) */
	करो अणु
		offset[DA732X_HPL_AMP] |= step;
		offset[DA732X_HPR_AMP] |= step;
		snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_OUT_OFFSET,
			      offset[DA732X_HPL_AMP]);
		snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_OUT_OFFSET,
			      offset[DA732X_HPR_AMP]);

		msleep(DA732X_WAIT_FOR_STABILIZATION);

		अगर ((snd_soc_component_पढ़ो(component, DA732X_REG_HPL) &
		     DA732X_HP_OUT_COMPO) ^ sign[DA732X_HPL_AMP])
			offset[DA732X_HPL_AMP] &= ~step;
		अगर ((snd_soc_component_पढ़ो(component, DA732X_REG_HPR) &
		     DA732X_HP_OUT_COMPO) ^ sign[DA732X_HPR_AMP])
			offset[DA732X_HPR_AMP] &= ~step;

		step >>= 1;
	पूर्ण जबतक (step);

	/* Write final DAC offsets to रेजिस्टरs */
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL_OUT_OFFSET, offset[DA732X_HPL_AMP]);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR_OUT_OFFSET, offset[DA732X_HPR_AMP]);
पूर्ण

अटल व्योम da732x_hp_dc_offset_cancellation(काष्ठा snd_soc_component *component)
अणु
	/* Make sure that we have Soft Mute enabled */
	snd_soc_component_ग_लिखो(component, DA732X_REG_DAC1_SOFTMUTE, DA732X_SOFTMUTE_EN |
		      DA732X_GAIN_RAMPED | DA732X_16_SAMPLES);
	snd_soc_component_ग_लिखो(component, DA732X_REG_DAC1_SEL, DA732X_DACL_EN |
		      DA732X_DACR_EN | DA732X_DACL_SDM | DA732X_DACR_SDM |
		      DA732X_DACL_MUTE | DA732X_DACR_MUTE);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL, DA732X_HP_OUT_DAC_EN |
		      DA732X_HP_OUT_MUTE | DA732X_HP_OUT_EN);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR, DA732X_HP_OUT_EN |
		      DA732X_HP_OUT_MUTE | DA732X_HP_OUT_DAC_EN);

	da732x_dac_offset_adjust(component);
	da732x_output_offset_adjust(component);

	snd_soc_component_ग_लिखो(component, DA732X_REG_DAC1_SEL, DA732X_DACS_DIS);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPL, DA732X_HP_DIS);
	snd_soc_component_ग_लिखो(component, DA732X_REG_HPR, DA732X_HP_DIS);
पूर्ण

अटल पूर्णांक da732x_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा da732x_priv *da732x = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN,
				    DA732X_BIAS_BOOST_MASK,
				    DA732X_BIAS_BOOST_100PC);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Init Codec */
			snd_soc_component_ग_लिखो(component, DA732X_REG_REF1,
				      DA732X_VMID_FASTCHG);
			snd_soc_component_ग_लिखो(component, DA732X_REG_BIAS_EN,
				      DA732X_BIAS_EN);

			mdelay(DA732X_STARTUP_DELAY);

			/* Disable Fast Charge and enable DAC ref voltage */
			snd_soc_component_ग_लिखो(component, DA732X_REG_REF1,
				      DA732X_REFBUFX2_EN);

			/* Enable bypass DSP routing */
			snd_soc_component_ग_लिखो(component, DA732X_REG_DATA_ROUTE,
				      DA732X_BYPASS_DSP);

			/* Enable Digital subप्रणाली */
			snd_soc_component_ग_लिखो(component, DA732X_REG_DSP_CTRL,
				      DA732X_DIGITAL_EN);

			snd_soc_component_ग_लिखो(component, DA732X_REG_SPARE1_OUT,
				      DA732X_HP_DRIVER_EN |
				      DA732X_HP_GATE_LOW |
				      DA732X_HP_LOOP_GAIN_CTRL);
			snd_soc_component_ग_लिखो(component, DA732X_REG_HP_LIN1_GNDSEL,
				      DA732X_HP_OUT_GNDSEL);

			da732x_set_अक्षरge_pump(component, DA732X_ENABLE_CP);

			snd_soc_component_ग_लिखो(component, DA732X_REG_CLK_EN1,
			      DA732X_SYS3_CLK_EN | DA732X_PC_CLK_EN);

			/* Enable Zero Crossing */
			snd_soc_component_ग_लिखो(component, DA732X_REG_INP_ZC_EN,
				      DA732X_MIC1_PRE_ZC_EN |
				      DA732X_MIC1_ZC_EN |
				      DA732X_MIC2_PRE_ZC_EN |
				      DA732X_MIC2_ZC_EN |
				      DA732X_AUXL_ZC_EN |
				      DA732X_AUXR_ZC_EN |
				      DA732X_MIC3_PRE_ZC_EN |
				      DA732X_MIC3_ZC_EN);
			snd_soc_component_ग_लिखो(component, DA732X_REG_OUT_ZC_EN,
				      DA732X_HPL_ZC_EN | DA732X_HPR_ZC_EN |
				      DA732X_LIN2_ZC_EN | DA732X_LIN3_ZC_EN |
				      DA732X_LIN4_ZC_EN);

			da732x_hp_dc_offset_cancellation(component);

			regcache_cache_only(da732x->regmap, false);
			regcache_sync(da732x->regmap);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN,
					    DA732X_BIAS_BOOST_MASK,
					    DA732X_BIAS_BOOST_50PC);
			snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL,
					    DA732X_PLL_EN, 0);
			da732x->pll_en = false;
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regcache_cache_only(da732x->regmap, true);
		da732x_set_अक्षरge_pump(component, DA732X_DISABLE_CP);
		snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN, DA732X_BIAS_EN,
				    DA732X_BIAS_DIS);
		da732x->pll_en = false;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da732x = अणु
	.set_bias_level		= da732x_set_bias_level,
	.controls		= da732x_snd_controls,
	.num_controls		= ARRAY_SIZE(da732x_snd_controls),
	.dapm_widमाला_लो		= da732x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da732x_dapm_widमाला_लो),
	.dapm_routes		= da732x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(da732x_dapm_routes),
	.set_pll		= da732x_set_dai_pll,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक da732x_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da732x_priv *da732x;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	da732x = devm_kzalloc(&i2c->dev, माप(काष्ठा da732x_priv),
			      GFP_KERNEL);
	अगर (!da732x)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da732x);

	da732x->regmap = devm_regmap_init_i2c(i2c, &da732x_regmap);
	अगर (IS_ERR(da732x->regmap)) अणु
		ret = PTR_ERR(da732x->regmap);
		dev_err(&i2c->dev, "Failed to initialize regmap\n");
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(da732x->regmap, DA732X_REG_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		जाओ err;
	पूर्ण

	dev_info(&i2c->dev, "Revision: %d.%d\n",
		 (reg & DA732X_ID_MAJOR_MASK) >> 4,
		 (reg & DA732X_ID_MINOR_MASK));

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_da732x,
				     da732x_dai, ARRAY_SIZE(da732x_dai));
	अगर (ret != 0)
		dev_err(&i2c->dev, "Failed to register component.\n");

err:
	वापस ret;
पूर्ण

अटल पूर्णांक da732x_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da732x_i2c_id[] = अणु
	अणु "da7320", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da732x_i2c_id);

अटल काष्ठा i2c_driver da732x_i2c_driver = अणु
	.driver		= अणु
		.name	= "da7320",
	पूर्ण,
	.probe		= da732x_i2c_probe,
	.हटाओ		= da732x_i2c_हटाओ,
	.id_table	= da732x_i2c_id,
पूर्ण;

module_i2c_driver(da732x_i2c_driver);


MODULE_DESCRIPTION("ASoC DA732X driver");
MODULE_AUTHOR("Michal Hajduk <michal.hajduk@diasemi.com>");
MODULE_LICENSE("GPL");
