<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs53l30.c  --  CS53l30 ALSA Soc Audio driver
 *
 * Copyright 2015 Cirrus Logic, Inc.
 *
 * Authors: Paul Handrigan <Paul.Handrigan@cirrus.com>,
 *          Tim Howe <Tim.Howe@cirrus.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "cs53l30.h"

#घोषणा CS53L30_NUM_SUPPLIES 2
अटल स्थिर अक्षर *स्थिर cs53l30_supply_names[CS53L30_NUM_SUPPLIES] = अणु
	"VA",
	"VP",
पूर्ण;

काष्ठा cs53l30_निजी अणु
	काष्ठा regulator_bulk_data	supplies[CS53L30_NUM_SUPPLIES];
	काष्ठा regmap			*regmap;
	काष्ठा gpio_desc		*reset_gpio;
	काष्ठा gpio_desc		*mute_gpio;
	काष्ठा clk			*mclk;
	bool				use_sकरोut2;
	u32				mclk_rate;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs53l30_reg_शेषs[] = अणु
	अणु CS53L30_PWRCTL,		CS53L30_PWRCTL_DEFAULT पूर्ण,
	अणु CS53L30_MCLKCTL,		CS53L30_MCLKCTL_DEFAULT पूर्ण,
	अणु CS53L30_INT_SR_CTL,		CS53L30_INT_SR_CTL_DEFAULT पूर्ण,
	अणु CS53L30_MICBIAS_CTL,		CS53L30_MICBIAS_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ASPCFG_CTL,		CS53L30_ASPCFG_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ASP_CTL1,		CS53L30_ASP_CTL1_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_CTL1,	CS53L30_ASP_TDMTX_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_CTL2,	CS53L30_ASP_TDMTX_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_CTL3,	CS53L30_ASP_TDMTX_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_CTL4,	CS53L30_ASP_TDMTX_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN1,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN2,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN3,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN4,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN5,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_TDMTX_EN6,	CS53L30_ASP_TDMTX_ENx_DEFAULT पूर्ण,
	अणु CS53L30_ASP_CTL2,		CS53L30_ASP_CTL2_DEFAULT पूर्ण,
	अणु CS53L30_SFT_RAMP,		CS53L30_SFT_RMP_DEFAULT पूर्ण,
	अणु CS53L30_LRCK_CTL1,		CS53L30_LRCK_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_LRCK_CTL2,		CS53L30_LRCK_CTLx_DEFAULT पूर्ण,
	अणु CS53L30_MUTEP_CTL1,		CS53L30_MUTEP_CTL1_DEFAULT पूर्ण,
	अणु CS53L30_MUTEP_CTL2,		CS53L30_MUTEP_CTL2_DEFAULT पूर्ण,
	अणु CS53L30_INBIAS_CTL1,		CS53L30_INBIAS_CTL1_DEFAULT पूर्ण,
	अणु CS53L30_INBIAS_CTL2,		CS53L30_INBIAS_CTL2_DEFAULT पूर्ण,
	अणु CS53L30_DMIC1_STR_CTL,	CS53L30_DMIC1_STR_CTL_DEFAULT पूर्ण,
	अणु CS53L30_DMIC2_STR_CTL,	CS53L30_DMIC2_STR_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADCDMIC1_CTL1,	CS53L30_ADCDMICx_CTL1_DEFAULT पूर्ण,
	अणु CS53L30_ADCDMIC1_CTL2,	CS53L30_ADCDMIC1_CTL2_DEFAULT पूर्ण,
	अणु CS53L30_ADC1_CTL3,		CS53L30_ADCx_CTL3_DEFAULT पूर्ण,
	अणु CS53L30_ADC1_NG_CTL,		CS53L30_ADCx_NG_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC1A_AFE_CTL,	CS53L30_ADCxy_AFE_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC1B_AFE_CTL,	CS53L30_ADCxy_AFE_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC1A_DIG_VOL,	CS53L30_ADCxy_DIG_VOL_DEFAULT पूर्ण,
	अणु CS53L30_ADC1B_DIG_VOL,	CS53L30_ADCxy_DIG_VOL_DEFAULT पूर्ण,
	अणु CS53L30_ADCDMIC2_CTL1,	CS53L30_ADCDMICx_CTL1_DEFAULT पूर्ण,
	अणु CS53L30_ADCDMIC2_CTL2,	CS53L30_ADCDMIC1_CTL2_DEFAULT पूर्ण,
	अणु CS53L30_ADC2_CTL3,		CS53L30_ADCx_CTL3_DEFAULT पूर्ण,
	अणु CS53L30_ADC2_NG_CTL,		CS53L30_ADCx_NG_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC2A_AFE_CTL,	CS53L30_ADCxy_AFE_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC2B_AFE_CTL,	CS53L30_ADCxy_AFE_CTL_DEFAULT पूर्ण,
	अणु CS53L30_ADC2A_DIG_VOL,	CS53L30_ADCxy_DIG_VOL_DEFAULT पूर्ण,
	अणु CS53L30_ADC2B_DIG_VOL,	CS53L30_ADCxy_DIG_VOL_DEFAULT पूर्ण,
	अणु CS53L30_INT_MASK,		CS53L30_DEVICE_INT_MASK पूर्ण,
पूर्ण;

अटल bool cs53l30_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == CS53L30_IS)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool cs53l30_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS53L30_DEVID_AB:
	हाल CS53L30_DEVID_CD:
	हाल CS53L30_DEVID_E:
	हाल CS53L30_REVID:
	हाल CS53L30_IS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool cs53l30_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS53L30_DEVID_AB:
	हाल CS53L30_DEVID_CD:
	हाल CS53L30_DEVID_E:
	हाल CS53L30_REVID:
	हाल CS53L30_PWRCTL:
	हाल CS53L30_MCLKCTL:
	हाल CS53L30_INT_SR_CTL:
	हाल CS53L30_MICBIAS_CTL:
	हाल CS53L30_ASPCFG_CTL:
	हाल CS53L30_ASP_CTL1:
	हाल CS53L30_ASP_TDMTX_CTL1:
	हाल CS53L30_ASP_TDMTX_CTL2:
	हाल CS53L30_ASP_TDMTX_CTL3:
	हाल CS53L30_ASP_TDMTX_CTL4:
	हाल CS53L30_ASP_TDMTX_EN1:
	हाल CS53L30_ASP_TDMTX_EN2:
	हाल CS53L30_ASP_TDMTX_EN3:
	हाल CS53L30_ASP_TDMTX_EN4:
	हाल CS53L30_ASP_TDMTX_EN5:
	हाल CS53L30_ASP_TDMTX_EN6:
	हाल CS53L30_ASP_CTL2:
	हाल CS53L30_SFT_RAMP:
	हाल CS53L30_LRCK_CTL1:
	हाल CS53L30_LRCK_CTL2:
	हाल CS53L30_MUTEP_CTL1:
	हाल CS53L30_MUTEP_CTL2:
	हाल CS53L30_INBIAS_CTL1:
	हाल CS53L30_INBIAS_CTL2:
	हाल CS53L30_DMIC1_STR_CTL:
	हाल CS53L30_DMIC2_STR_CTL:
	हाल CS53L30_ADCDMIC1_CTL1:
	हाल CS53L30_ADCDMIC1_CTL2:
	हाल CS53L30_ADC1_CTL3:
	हाल CS53L30_ADC1_NG_CTL:
	हाल CS53L30_ADC1A_AFE_CTL:
	हाल CS53L30_ADC1B_AFE_CTL:
	हाल CS53L30_ADC1A_DIG_VOL:
	हाल CS53L30_ADC1B_DIG_VOL:
	हाल CS53L30_ADCDMIC2_CTL1:
	हाल CS53L30_ADCDMIC2_CTL2:
	हाल CS53L30_ADC2_CTL3:
	हाल CS53L30_ADC2_NG_CTL:
	हाल CS53L30_ADC2A_AFE_CTL:
	हाल CS53L30_ADC2B_AFE_CTL:
	हाल CS53L30_ADC2A_DIG_VOL:
	हाल CS53L30_ADC2B_DIG_VOL:
	हाल CS53L30_INT_MASK:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(adc_boost_tlv, 0, 2000, 0);
अटल DECLARE_TLV_DB_SCALE(adc_ng_boost_tlv, 0, 3000, 0);
अटल DECLARE_TLV_DB_SCALE(pga_tlv, -600, 50, 0);
अटल DECLARE_TLV_DB_SCALE(dig_tlv, -9600, 100, 1);
अटल DECLARE_TLV_DB_SCALE(pga_preamp_tlv, 0, 10000, 0);

अटल स्थिर अक्षर * स्थिर input1_sel_text[] = अणु
	"DMIC1 On AB In",
	"DMIC1 On A In",
	"DMIC1 On B In",
	"ADC1 On AB In",
	"ADC1 On A In",
	"ADC1 On B In",
	"DMIC1 Off ADC1 Off",
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर input1_sel_values[] = अणु
	CS53L30_CH_TYPE,
	CS53L30_ADCxB_PDN | CS53L30_CH_TYPE,
	CS53L30_ADCxA_PDN | CS53L30_CH_TYPE,
	CS53L30_DMICx_PDN,
	CS53L30_ADCxB_PDN | CS53L30_DMICx_PDN,
	CS53L30_ADCxA_PDN | CS53L30_DMICx_PDN,
	CS53L30_ADCxA_PDN | CS53L30_ADCxB_PDN | CS53L30_DMICx_PDN,
पूर्ण;

अटल स्थिर अक्षर * स्थिर input2_sel_text[] = अणु
	"DMIC2 On AB In",
	"DMIC2 On A In",
	"DMIC2 On B In",
	"ADC2 On AB In",
	"ADC2 On A In",
	"ADC2 On B In",
	"DMIC2 Off ADC2 Off",
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर input2_sel_values[] = अणु
	0x0,
	CS53L30_ADCxB_PDN,
	CS53L30_ADCxA_PDN,
	CS53L30_DMICx_PDN,
	CS53L30_ADCxB_PDN | CS53L30_DMICx_PDN,
	CS53L30_ADCxA_PDN | CS53L30_DMICx_PDN,
	CS53L30_ADCxA_PDN | CS53L30_ADCxB_PDN | CS53L30_DMICx_PDN,
पूर्ण;

अटल स्थिर अक्षर * स्थिर input1_route_sel_text[] = अणु
	"ADC1_SEL", "DMIC1_SEL",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत input1_route_sel_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADCDMIC1_CTL1, CS53L30_CH_TYPE_SHIFT,
			ARRAY_SIZE(input1_route_sel_text),
			input1_route_sel_text);

अटल SOC_VALUE_ENUM_SINGLE_DECL(input1_sel_क्रमागत, CS53L30_ADCDMIC1_CTL1, 0,
				  CS53L30_ADCDMICx_PDN_MASK, input1_sel_text,
				  input1_sel_values);

अटल स्थिर काष्ठा snd_kcontrol_new input1_route_sel_mux =
	SOC_DAPM_ENUM("Input 1 Route", input1_route_sel_क्रमागत);

अटल स्थिर अक्षर * स्थिर input2_route_sel_text[] = अणु
	"ADC2_SEL", "DMIC2_SEL",
पूर्ण;

/* Note: CS53L30_ADCDMIC1_CTL1 CH_TYPE controls inमाला_दो 1 and 2 */
अटल स्थिर काष्ठा soc_क्रमागत input2_route_sel_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADCDMIC1_CTL1, 0,
			ARRAY_SIZE(input2_route_sel_text),
			input2_route_sel_text);

अटल SOC_VALUE_ENUM_SINGLE_DECL(input2_sel_क्रमागत, CS53L30_ADCDMIC2_CTL1, 0,
				  CS53L30_ADCDMICx_PDN_MASK, input2_sel_text,
				  input2_sel_values);

अटल स्थिर काष्ठा snd_kcontrol_new input2_route_sel_mux =
	SOC_DAPM_ENUM("Input 2 Route", input2_route_sel_क्रमागत);

/*
 * TB = 6144*(MCLK(पूर्णांक) scaling factor)/MCLK(पूर्णांकernal)
 * TB - Time base
 * NOTE: If MCLK_INT_SCALE = 0, then TB=1
 */
अटल स्थिर अक्षर * स्थिर cs53l30_ng_delay_text[] = अणु
	"TB*50ms", "TB*100ms", "TB*150ms", "TB*200ms",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc1_ng_delay_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC1_NG_CTL, CS53L30_ADCx_NG_DELAY_SHIFT,
			ARRAY_SIZE(cs53l30_ng_delay_text),
			cs53l30_ng_delay_text);

अटल स्थिर काष्ठा soc_क्रमागत adc2_ng_delay_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC2_NG_CTL, CS53L30_ADCx_NG_DELAY_SHIFT,
			ARRAY_SIZE(cs53l30_ng_delay_text),
			cs53l30_ng_delay_text);

/* The noise gate threshold selected will depend on NG Boost */
अटल स्थिर अक्षर * स्थिर cs53l30_ng_thres_text[] = अणु
	"-64dB/-34dB", "-66dB/-36dB", "-70dB/-40dB", "-73dB/-43dB",
	"-76dB/-46dB", "-82dB/-52dB", "-58dB", "-64dB",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc1_ng_thres_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC1_NG_CTL, CS53L30_ADCx_NG_THRESH_SHIFT,
			ARRAY_SIZE(cs53l30_ng_thres_text),
			cs53l30_ng_thres_text);

अटल स्थिर काष्ठा soc_क्रमागत adc2_ng_thres_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC2_NG_CTL, CS53L30_ADCx_NG_THRESH_SHIFT,
			ARRAY_SIZE(cs53l30_ng_thres_text),
			cs53l30_ng_thres_text);

/* Corner frequencies are with an Fs of 48kHz. */
अटल स्थिर अक्षर * स्थिर hpf_corner_freq_text[] = अणु
	"1.86Hz", "120Hz", "235Hz", "466Hz",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc1_hpf_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC1_CTL3, CS53L30_ADCx_HPF_CF_SHIFT,
			ARRAY_SIZE(hpf_corner_freq_text), hpf_corner_freq_text);

अटल स्थिर काष्ठा soc_क्रमागत adc2_hpf_क्रमागत =
	SOC_ENUM_SINGLE(CS53L30_ADC2_CTL3, CS53L30_ADCx_HPF_CF_SHIFT,
			ARRAY_SIZE(hpf_corner_freq_text), hpf_corner_freq_text);

अटल स्थिर काष्ठा snd_kcontrol_new cs53l30_snd_controls[] = अणु
	SOC_SINGLE("Digital Soft-Ramp Switch", CS53L30_SFT_RAMP,
		   CS53L30_DIGSFT_SHIFT, 1, 0),
	SOC_SINGLE("ADC1 Noise Gate Ganging Switch", CS53L30_ADC1_CTL3,
		   CS53L30_ADCx_NG_ALL_SHIFT, 1, 0),
	SOC_SINGLE("ADC2 Noise Gate Ganging Switch", CS53L30_ADC2_CTL3,
		   CS53L30_ADCx_NG_ALL_SHIFT, 1, 0),
	SOC_SINGLE("ADC1A Noise Gate Enable Switch", CS53L30_ADC1_NG_CTL,
		   CS53L30_ADCxA_NG_SHIFT, 1, 0),
	SOC_SINGLE("ADC1B Noise Gate Enable Switch", CS53L30_ADC1_NG_CTL,
		   CS53L30_ADCxB_NG_SHIFT, 1, 0),
	SOC_SINGLE("ADC2A Noise Gate Enable Switch", CS53L30_ADC2_NG_CTL,
		   CS53L30_ADCxA_NG_SHIFT, 1, 0),
	SOC_SINGLE("ADC2B Noise Gate Enable Switch", CS53L30_ADC2_NG_CTL,
		   CS53L30_ADCxB_NG_SHIFT, 1, 0),
	SOC_SINGLE("ADC1 Notch Filter Switch", CS53L30_ADCDMIC1_CTL2,
		   CS53L30_ADCx_NOTCH_DIS_SHIFT, 1, 1),
	SOC_SINGLE("ADC2 Notch Filter Switch", CS53L30_ADCDMIC2_CTL2,
		   CS53L30_ADCx_NOTCH_DIS_SHIFT, 1, 1),
	SOC_SINGLE("ADC1A Invert Switch", CS53L30_ADCDMIC1_CTL2,
		   CS53L30_ADCxA_INV_SHIFT, 1, 0),
	SOC_SINGLE("ADC1B Invert Switch", CS53L30_ADCDMIC1_CTL2,
		   CS53L30_ADCxB_INV_SHIFT, 1, 0),
	SOC_SINGLE("ADC2A Invert Switch", CS53L30_ADCDMIC2_CTL2,
		   CS53L30_ADCxA_INV_SHIFT, 1, 0),
	SOC_SINGLE("ADC2B Invert Switch", CS53L30_ADCDMIC2_CTL2,
		   CS53L30_ADCxB_INV_SHIFT, 1, 0),

	SOC_SINGLE_TLV("ADC1A Digital Boost Volume", CS53L30_ADCDMIC1_CTL2,
		       CS53L30_ADCxA_DIG_BOOST_SHIFT, 1, 0, adc_boost_tlv),
	SOC_SINGLE_TLV("ADC1B Digital Boost Volume", CS53L30_ADCDMIC1_CTL2,
		       CS53L30_ADCxB_DIG_BOOST_SHIFT, 1, 0, adc_boost_tlv),
	SOC_SINGLE_TLV("ADC2A Digital Boost Volume", CS53L30_ADCDMIC2_CTL2,
		       CS53L30_ADCxA_DIG_BOOST_SHIFT, 1, 0, adc_boost_tlv),
	SOC_SINGLE_TLV("ADC2B Digital Boost Volume", CS53L30_ADCDMIC2_CTL2,
		       CS53L30_ADCxB_DIG_BOOST_SHIFT, 1, 0, adc_boost_tlv),
	SOC_SINGLE_TLV("ADC1 NG Boost Volume", CS53L30_ADC1_NG_CTL,
		       CS53L30_ADCx_NG_BOOST_SHIFT, 1, 0, adc_ng_boost_tlv),
	SOC_SINGLE_TLV("ADC2 NG Boost Volume", CS53L30_ADC2_NG_CTL,
		       CS53L30_ADCx_NG_BOOST_SHIFT, 1, 0, adc_ng_boost_tlv),

	SOC_DOUBLE_R_TLV("ADC1 Preamplifier Volume", CS53L30_ADC1A_AFE_CTL,
			 CS53L30_ADC1B_AFE_CTL, CS53L30_ADCxy_PREAMP_SHIFT,
			 2, 0, pga_preamp_tlv),
	SOC_DOUBLE_R_TLV("ADC2 Preamplifier Volume", CS53L30_ADC2A_AFE_CTL,
			 CS53L30_ADC2B_AFE_CTL, CS53L30_ADCxy_PREAMP_SHIFT,
			 2, 0, pga_preamp_tlv),

	SOC_ENUM("Input 1 Channel Select", input1_sel_क्रमागत),
	SOC_ENUM("Input 2 Channel Select", input2_sel_क्रमागत),

	SOC_ENUM("ADC1 HPF Select", adc1_hpf_क्रमागत),
	SOC_ENUM("ADC2 HPF Select", adc2_hpf_क्रमागत),
	SOC_ENUM("ADC1 NG Threshold", adc1_ng_thres_क्रमागत),
	SOC_ENUM("ADC2 NG Threshold", adc2_ng_thres_क्रमागत),
	SOC_ENUM("ADC1 NG Delay", adc1_ng_delay_क्रमागत),
	SOC_ENUM("ADC2 NG Delay", adc2_ng_delay_क्रमागत),

	SOC_SINGLE_SX_TLV("ADC1A PGA Volume",
		    CS53L30_ADC1A_AFE_CTL, 0, 0x34, 0x18, pga_tlv),
	SOC_SINGLE_SX_TLV("ADC1B PGA Volume",
		    CS53L30_ADC1B_AFE_CTL, 0, 0x34, 0x18, pga_tlv),
	SOC_SINGLE_SX_TLV("ADC2A PGA Volume",
		    CS53L30_ADC2A_AFE_CTL, 0, 0x34, 0x18, pga_tlv),
	SOC_SINGLE_SX_TLV("ADC2B PGA Volume",
		    CS53L30_ADC2B_AFE_CTL, 0, 0x34, 0x18, pga_tlv),

	SOC_SINGLE_SX_TLV("ADC1A Digital Volume",
		    CS53L30_ADC1A_DIG_VOL, 0, 0xA0, 0x0C, dig_tlv),
	SOC_SINGLE_SX_TLV("ADC1B Digital Volume",
		    CS53L30_ADC1B_DIG_VOL, 0, 0xA0, 0x0C, dig_tlv),
	SOC_SINGLE_SX_TLV("ADC2A Digital Volume",
		    CS53L30_ADC2A_DIG_VOL, 0, 0xA0, 0x0C, dig_tlv),
	SOC_SINGLE_SX_TLV("ADC2B Digital Volume",
		    CS53L30_ADC2B_DIG_VOL, 0, 0xA0, 0x0C, dig_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs53l30_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("IN1_DMIC1"),
	SND_SOC_DAPM_INPUT("IN2"),
	SND_SOC_DAPM_INPUT("IN3_DMIC2"),
	SND_SOC_DAPM_INPUT("IN4"),
	SND_SOC_DAPM_SUPPLY("MIC1 Bias", CS53L30_MICBIAS_CTL,
			    CS53L30_MIC1_BIAS_PDN_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC2 Bias", CS53L30_MICBIAS_CTL,
			    CS53L30_MIC2_BIAS_PDN_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC3 Bias", CS53L30_MICBIAS_CTL,
			    CS53L30_MIC3_BIAS_PDN_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC4 Bias", CS53L30_MICBIAS_CTL,
			    CS53L30_MIC4_BIAS_PDN_SHIFT, 1, शून्य, 0),

	SND_SOC_DAPM_AIF_OUT("ASP_SDOUT1", शून्य, 0, CS53L30_ASP_CTL1,
			     CS53L30_ASP_SDOUTx_PDN_SHIFT, 1),
	SND_SOC_DAPM_AIF_OUT("ASP_SDOUT2", शून्य, 0, CS53L30_ASP_CTL2,
			     CS53L30_ASP_SDOUTx_PDN_SHIFT, 1),

	SND_SOC_DAPM_MUX("Input Mux 1", SND_SOC_NOPM, 0, 0,
			 &input1_route_sel_mux),
	SND_SOC_DAPM_MUX("Input Mux 2", SND_SOC_NOPM, 0, 0,
			 &input2_route_sel_mux),

	SND_SOC_DAPM_ADC("ADC1A", शून्य, CS53L30_ADCDMIC1_CTL1,
			 CS53L30_ADCxA_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC1B", शून्य, CS53L30_ADCDMIC1_CTL1,
			 CS53L30_ADCxB_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2A", शून्य, CS53L30_ADCDMIC2_CTL1,
			 CS53L30_ADCxA_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2B", शून्य, CS53L30_ADCDMIC2_CTL1,
			 CS53L30_ADCxB_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("DMIC1", शून्य, CS53L30_ADCDMIC1_CTL1,
			 CS53L30_DMICx_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("DMIC2", शून्य, CS53L30_ADCDMIC2_CTL1,
			 CS53L30_DMICx_PDN_SHIFT, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs53l30_dapm_routes[] = अणु
	/* ADC Input Paths */
	अणु"ADC1A", शून्य, "IN1_DMIC1"पूर्ण,
	अणु"Input Mux 1", "ADC1_SEL", "ADC1A"पूर्ण,
	अणु"ADC1B", शून्य, "IN2"पूर्ण,

	अणु"ADC2A", शून्य, "IN3_DMIC2"पूर्ण,
	अणु"Input Mux 2", "ADC2_SEL", "ADC2A"पूर्ण,
	अणु"ADC2B", शून्य, "IN4"पूर्ण,

	/* MIC Bias Paths */
	अणु"ADC1A", शून्य, "MIC1 Bias"पूर्ण,
	अणु"ADC1B", शून्य, "MIC2 Bias"पूर्ण,
	अणु"ADC2A", शून्य, "MIC3 Bias"पूर्ण,
	अणु"ADC2B", शून्य, "MIC4 Bias"पूर्ण,

	/* DMIC Paths */
	अणु"DMIC1", शून्य, "IN1_DMIC1"पूर्ण,
	अणु"Input Mux 1", "DMIC1_SEL", "DMIC1"पूर्ण,

	अणु"DMIC2", शून्य, "IN3_DMIC2"पूर्ण,
	अणु"Input Mux 2", "DMIC2_SEL", "DMIC2"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs53l30_dapm_routes_sकरोut1[] = अणु
	/* Output Paths when using SDOUT1 only */
	अणु"ASP_SDOUT1", शून्य, "ADC1A" पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "Input Mux 1"पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "ADC1B"पूर्ण,

	अणु"ASP_SDOUT1", शून्य, "ADC2A"पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "Input Mux 2"पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "ADC2B"पूर्ण,

	अणु"Capture", शून्य, "ASP_SDOUT1"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs53l30_dapm_routes_sकरोut2[] = अणु
	/* Output Paths when using both SDOUT1 and SDOUT2 */
	अणु"ASP_SDOUT1", शून्य, "ADC1A" पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "Input Mux 1"पूर्ण,
	अणु"ASP_SDOUT1", शून्य, "ADC1B"पूर्ण,

	अणु"ASP_SDOUT2", शून्य, "ADC2A"पूर्ण,
	अणु"ASP_SDOUT2", शून्य, "Input Mux 2"पूर्ण,
	अणु"ASP_SDOUT2", शून्य, "ADC2B"पूर्ण,

	अणु"Capture", शून्य, "ASP_SDOUT1"पूर्ण,
	अणु"Capture", शून्य, "ASP_SDOUT2"पूर्ण,
पूर्ण;

काष्ठा cs53l30_mclk_भाग अणु
	u32 mclk_rate;
	u32 srate;
	u8 asp_rate;
	u8 पूर्णांकernal_fs_ratio;
	u8 mclk_पूर्णांक_scale;
पूर्ण;

अटल स्थिर काष्ठा cs53l30_mclk_भाग cs53l30_mclk_coeffs[] = अणु
	/* NOTE: Enable MCLK_INT_SCALE to save घातer. */

	/* MCLK, Sample Rate, asp_rate, पूर्णांकernal_fs_ratio, mclk_पूर्णांक_scale */
	अणु5644800, 11025, 0x4, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु5644800, 22050, 0x8, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु5644800, 44100, 0xC, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,

	अणु6000000,  8000, 0x1, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 11025, 0x2, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 12000, 0x4, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 16000, 0x5, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 22050, 0x6, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 24000, 0x8, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 32000, 0x9, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 44100, 0xA, 0, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6000000, 48000, 0xC, 0, CS53L30_MCLK_INT_SCALEपूर्ण,

	अणु6144000,  8000, 0x1, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 11025, 0x2, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 12000, 0x4, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 16000, 0x5, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 22050, 0x6, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 24000, 0x8, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 32000, 0x9, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 44100, 0xA, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6144000, 48000, 0xC, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,

	अणु6400000,  8000, 0x1, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 11025, 0x2, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 12000, 0x4, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 16000, 0x5, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 22050, 0x6, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 24000, 0x8, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 32000, 0x9, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 44100, 0xA, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
	अणु6400000, 48000, 0xC, CS53L30_INTRNL_FS_RATIO, CS53L30_MCLK_INT_SCALEपूर्ण,
पूर्ण;

काष्ठा cs53l30_mclkx_भाग अणु
	u32 mclkx;
	u8 ratio;
	u8 mclkभाग;
पूर्ण;

अटल स्थिर काष्ठा cs53l30_mclkx_भाग cs53l30_mclkx_coeffs[] = अणु
	अणु5644800,  1, CS53L30_MCLK_DIV_BY_1पूर्ण,
	अणु6000000,  1, CS53L30_MCLK_DIV_BY_1पूर्ण,
	अणु6144000,  1, CS53L30_MCLK_DIV_BY_1पूर्ण,
	अणु11289600, 2, CS53L30_MCLK_DIV_BY_2पूर्ण,
	अणु12288000, 2, CS53L30_MCLK_DIV_BY_2पूर्ण,
	अणु12000000, 2, CS53L30_MCLK_DIV_BY_2पूर्ण,
	अणु19200000, 3, CS53L30_MCLK_DIV_BY_3पूर्ण,
पूर्ण;

अटल पूर्णांक cs53l30_get_mclkx_coeff(पूर्णांक mclkx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs53l30_mclkx_coeffs); i++) अणु
		अगर (cs53l30_mclkx_coeffs[i].mclkx == mclkx)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs53l30_get_mclk_coeff(पूर्णांक mclk_rate, पूर्णांक srate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs53l30_mclk_coeffs); i++) अणु
		अगर (cs53l30_mclk_coeffs[i].mclk_rate == mclk_rate &&
		    cs53l30_mclk_coeffs[i].srate == srate)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs53l30_set_sysclk(काष्ठा snd_soc_dai *dai,
			      पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक mclkx_coeff;
	u32 mclk_rate;

	/* MCLKX -> MCLK */
	mclkx_coeff = cs53l30_get_mclkx_coeff(freq);
	अगर (mclkx_coeff < 0)
		वापस mclkx_coeff;

	mclk_rate = cs53l30_mclkx_coeffs[mclkx_coeff].mclkx /
		    cs53l30_mclkx_coeffs[mclkx_coeff].ratio;

	regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
			   CS53L30_MCLK_DIV_MASK,
			   cs53l30_mclkx_coeffs[mclkx_coeff].mclkभाग);

	priv->mclk_rate = mclk_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	u8 aspcfg = 0, aspctl1 = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aspcfg |= CS53L30_ASP_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* Set TDM_PDN to turn off TDM mode -- Reset शेष */
		aspctl1 |= CS53L30_ASP_TDM_PDN;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		/*
		 * Clear TDM_PDN to turn on TDM mode; Use ASP_SCLK_INV = 0
		 * with SHIFT_LEFT = 1 combination as Figure 4-13 shows in
		 * the CS53L30 datasheet
		 */
		aspctl1 |= CS53L30_SHIFT_LEFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Check to see अगर the SCLK is inverted */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
	हाल SND_SOC_DAIFMT_IB_IF:
		aspcfg ^= CS53L30_ASP_SCLK_INV;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	regmap_update_bits(priv->regmap, CS53L30_ASPCFG_CTL,
			   CS53L30_ASP_MS | CS53L30_ASP_SCLK_INV, aspcfg);

	regmap_update_bits(priv->regmap, CS53L30_ASP_CTL1,
			   CS53L30_ASP_TDM_PDN | CS53L30_SHIFT_LEFT, aspctl1);

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक srate = params_rate(params);
	पूर्णांक mclk_coeff;

	/* MCLK -> srate */
	mclk_coeff = cs53l30_get_mclk_coeff(priv->mclk_rate, srate);
	अगर (mclk_coeff < 0)
		वापस -EINVAL;

	regmap_update_bits(priv->regmap, CS53L30_INT_SR_CTL,
			   CS53L30_INTRNL_FS_RATIO_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].पूर्णांकernal_fs_ratio);

	regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
			   CS53L30_MCLK_INT_SCALE_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].mclk_पूर्णांक_scale);

	regmap_update_bits(priv->regmap, CS53L30_ASPCFG_CTL,
			   CS53L30_ASP_RATE_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].asp_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;
	पूर्णांक i, पूर्णांकer_max_check, ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY)
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_LP_MASK, 0);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (dapm->bias_level == SND_SOC_BIAS_OFF) अणु
			ret = clk_prepare_enable(priv->mclk);
			अगर (ret) अणु
				dev_err(component->dev,
					"failed to enable MCLK: %d\n", ret);
				वापस ret;
			पूर्ण
			regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
					   CS53L30_MCLK_DIS_MASK, 0);
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_ULP_MASK, 0);
			msleep(50);
		पूर्ण अन्यथा अणु
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_ULP_MASK,
					   CS53L30_PDN_ULP);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(priv->regmap, CS53L30_INT_MASK,
				   CS53L30_PDN_DONE, 0);
		/*
		 * If digital softramp is set, the amount of समय required
		 * क्रम घातer करोwn increases and depends on the digital
		 * volume setting.
		 */

		/* Set the max possible समय अगर digsft is set */
		regmap_पढ़ो(priv->regmap, CS53L30_SFT_RAMP, &reg);
		अगर (reg & CS53L30_DIGSFT_MASK)
			पूर्णांकer_max_check = CS53L30_PDN_POLL_MAX;
		अन्यथा
			पूर्णांकer_max_check = 10;

		regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
				   CS53L30_PDN_ULP_MASK,
				   CS53L30_PDN_ULP);
		/* PDN_DONE will take a min of 20ms to be set.*/
		msleep(20);
		/* Clr status */
		regmap_पढ़ो(priv->regmap, CS53L30_IS, &reg);
		क्रम (i = 0; i < पूर्णांकer_max_check; i++) अणु
			अगर (पूर्णांकer_max_check < 10) अणु
				usleep_range(1000, 1100);
				regmap_पढ़ो(priv->regmap, CS53L30_IS, &reg);
				अगर (reg & CS53L30_PDN_DONE)
					अवरोध;
			पूर्ण अन्यथा अणु
				usleep_range(10000, 10100);
				regmap_पढ़ो(priv->regmap, CS53L30_IS, &reg);
				अगर (reg & CS53L30_PDN_DONE)
					अवरोध;
			पूर्ण
		पूर्ण
		/* PDN_DONE is set. We now can disable the MCLK */
		regmap_update_bits(priv->regmap, CS53L30_INT_MASK,
				   CS53L30_PDN_DONE, CS53L30_PDN_DONE);
		regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
				   CS53L30_MCLK_DIS_MASK,
				   CS53L30_MCLK_DIS);
		clk_disable_unprepare(priv->mclk);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	u8 val = tristate ? CS53L30_ASP_3ST : 0;

	वापस regmap_update_bits(priv->regmap, CS53L30_ASP_CTL1,
				  CS53L30_ASP_3ST_MASK, val);
पूर्ण

अटल अचिन्हित पूर्णांक स्थिर cs53l30_src_rates[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list src_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(cs53l30_src_rates),
	.list = cs53l30_src_rates,
पूर्ण;

अटल पूर्णांक cs53l30_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE, &src_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

/*
 * Note: CS53L30 counts the slot number per byte जबतक ASoC counts the slot
 * number per slot_width. So there is a dअगरference between the slots of ASoC
 * and the slots of CS53L30.
 */
अटल पूर्णांक cs53l30_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक loc[CS53L30_TDM_SLOT_MAX] = अणु48, 48, 48, 48पूर्ण;
	अचिन्हित पूर्णांक slot_next, slot_step;
	u64 tx_enable = 0;
	पूर्णांक i;

	अगर (!rx_mask) अणु
		dev_err(dai->dev, "rx masks must not be 0\n");
		वापस -EINVAL;
	पूर्ण

	/* Assuming slot_width is not supposed to be greater than 64 */
	अगर (slots <= 0 || slot_width <= 0 || slot_width > 64) अणु
		dev_err(dai->dev, "invalid slot number or slot width\n");
		वापस -EINVAL;
	पूर्ण

	अगर (slot_width & 0x7) अणु
		dev_err(dai->dev, "slot width must count in byte\n");
		वापस -EINVAL;
	पूर्ण

	/* How many bytes in each ASoC slot */
	slot_step = slot_width >> 3;

	क्रम (i = 0; rx_mask && i < CS53L30_TDM_SLOT_MAX; i++) अणु
		/* Find the first slot from LSB */
		slot_next = __ffs(rx_mask);
		/* Save the slot location by converting to CS53L30 slot */
		loc[i] = slot_next * slot_step;
		/* Create the mask of CS53L30 slot */
		tx_enable |= (u64)((u64)(1 << slot_step) - 1) << (u64)loc[i];
		/* Clear this slot from rx_mask */
		rx_mask &= ~(1 << slot_next);
	पूर्ण

	/* Error out to aव्योम slot shअगरt */
	अगर (rx_mask && i == CS53L30_TDM_SLOT_MAX) अणु
		dev_err(dai->dev, "rx_mask exceeds max slot number: %d\n",
			CS53L30_TDM_SLOT_MAX);
		वापस -EINVAL;
	पूर्ण

	/* Validate the last active CS53L30 slot */
	slot_next = loc[i - 1] + slot_step - 1;
	अगर (slot_next > 47) अणु
		dev_err(dai->dev, "slot selection out of bounds: %u\n",
			slot_next);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < CS53L30_TDM_SLOT_MAX && loc[i] != 48; i++) अणु
		regmap_update_bits(priv->regmap, CS53L30_ASP_TDMTX_CTL(i),
				   CS53L30_ASP_CHx_TX_LOC_MASK, loc[i]);
		dev_dbg(dai->dev, "loc[%d]=%x\n", i, loc[i]);
	पूर्ण

	क्रम (i = 0; i < CS53L30_ASP_TDMTX_ENx_MAX && tx_enable; i++) अणु
		regmap_ग_लिखो(priv->regmap, CS53L30_ASP_TDMTX_ENx(i),
			     tx_enable & 0xff);
		tx_enable >>= 8;
		dev_dbg(dai->dev, "en_reg=%x, tx_enable=%llx\n",
			CS53L30_ASP_TDMTX_ENx(i), tx_enable & 0xff);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(dai->component);

	gpiod_set_value_cansleep(priv->mute_gpio, mute);

	वापस 0;
पूर्ण

/* SNDRV_PCM_RATE_KNOT -> 12000, 24000 Hz, limit with स्थिरraपूर्णांक list */
#घोषणा CS53L30_RATES (SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_KNOT)

#घोषणा CS53L30_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops cs53l30_ops = अणु
	.startup = cs53l30_pcm_startup,
	.hw_params = cs53l30_pcm_hw_params,
	.set_fmt = cs53l30_set_dai_fmt,
	.set_sysclk = cs53l30_set_sysclk,
	.set_tristate = cs53l30_set_tristate,
	.set_tdm_slot = cs53l30_set_dai_tdm_slot,
	.mute_stream = cs53l30_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs53l30_dai = अणु
	.name = "cs53l30",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 4,
		.rates = CS53L30_RATES,
		.क्रमmats = CS53L30_FORMATS,
	पूर्ण,
	.ops = &cs53l30_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक cs53l30_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs53l30_निजी *priv = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (priv->use_sकरोut2)
		snd_soc_dapm_add_routes(dapm, cs53l30_dapm_routes_sकरोut2,
					ARRAY_SIZE(cs53l30_dapm_routes_sकरोut2));
	अन्यथा
		snd_soc_dapm_add_routes(dapm, cs53l30_dapm_routes_sकरोut1,
					ARRAY_SIZE(cs53l30_dapm_routes_sकरोut1));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver cs53l30_driver = अणु
	.probe			= cs53l30_component_probe,
	.set_bias_level		= cs53l30_set_bias_level,
	.controls		= cs53l30_snd_controls,
	.num_controls		= ARRAY_SIZE(cs53l30_snd_controls),
	.dapm_widमाला_लो		= cs53l30_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs53l30_dapm_widमाला_लो),
	.dapm_routes		= cs53l30_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs53l30_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा regmap_config cs53l30_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS53L30_MAX_REGISTER,
	.reg_शेषs = cs53l30_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs53l30_reg_शेषs),
	.अस्थिर_reg = cs53l30_अस्थिर_रेजिस्टर,
	.ग_लिखोable_reg = cs53l30_ग_लिखोable_रेजिस्टर,
	.पढ़ोable_reg = cs53l30_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक cs53l30_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा device_node *np = client->dev.of_node;
	काष्ठा device *dev = &client->dev;
	काष्ठा cs53l30_निजी *cs53l30;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret = 0, i;
	u8 val;

	cs53l30 = devm_kzalloc(dev, माप(*cs53l30), GFP_KERNEL);
	अगर (!cs53l30)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(cs53l30->supplies); i++)
		cs53l30->supplies[i].supply = cs53l30_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(cs53l30->supplies),
				      cs53l30->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs53l30->supplies),
				    cs53l30->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the Device */
	cs53l30->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(cs53l30->reset_gpio)) अणु
		ret = PTR_ERR(cs53l30->reset_gpio);
		जाओ error;
	पूर्ण

	gpiod_set_value_cansleep(cs53l30->reset_gpio, 1);

	i2c_set_clientdata(client, cs53l30);

	cs53l30->mclk_rate = 0;

	cs53l30->regmap = devm_regmap_init_i2c(client, &cs53l30_regmap);
	अगर (IS_ERR(cs53l30->regmap)) अणु
		ret = PTR_ERR(cs53l30->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		जाओ error;
	पूर्ण

	/* Initialize codec */
	ret = regmap_पढ़ो(cs53l30->regmap, CS53L30_DEVID_AB, &reg);
	devid = reg << 12;

	ret = regmap_पढ़ो(cs53l30->regmap, CS53L30_DEVID_CD, &reg);
	devid |= reg << 4;

	ret = regmap_पढ़ो(cs53l30->regmap, CS53L30_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS53L30_DEVID) अणु
		ret = -ENODEV;
		dev_err(dev, "Device ID (%X). Expected %X\n",
			devid, CS53L30_DEVID);
		जाओ error;
	पूर्ण

	ret = regmap_पढ़ो(cs53l30->regmap, CS53L30_REVID, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get Revision ID: %d\n", ret);
		जाओ error;
	पूर्ण

	/* Check अगर MCLK provided */
	cs53l30->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(cs53l30->mclk)) अणु
		अगर (PTR_ERR(cs53l30->mclk) != -ENOENT) अणु
			ret = PTR_ERR(cs53l30->mclk);
			जाओ error;
		पूर्ण
		/* Otherwise mark the mclk poपूर्णांकer to शून्य */
		cs53l30->mclk = शून्य;
	पूर्ण

	/* Fetch the MUTE control */
	cs53l30->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(cs53l30->mute_gpio)) अणु
		ret = PTR_ERR(cs53l30->mute_gpio);
		जाओ error;
	पूर्ण

	अगर (cs53l30->mute_gpio) अणु
		/* Enable MUTE controls via MUTE pin */
		regmap_ग_लिखो(cs53l30->regmap, CS53L30_MUTEP_CTL1,
			     CS53L30_MUTEP_CTL1_MUTEALL);
		/* Flip the polarity of MUTE pin */
		अगर (gpiod_is_active_low(cs53l30->mute_gpio))
			regmap_update_bits(cs53l30->regmap, CS53L30_MUTEP_CTL2,
					   CS53L30_MUTE_PIN_POLARITY, 0);
	पूर्ण

	अगर (!of_property_पढ़ो_u8(np, "cirrus,micbias-lvl", &val))
		regmap_update_bits(cs53l30->regmap, CS53L30_MICBIAS_CTL,
				   CS53L30_MIC_BIAS_CTRL_MASK, val);

	अगर (of_property_पढ़ो_bool(np, "cirrus,use-sdout2"))
		cs53l30->use_sकरोut2 = true;

	dev_info(dev, "Cirrus Logic CS53L30, Revision: %02X\n", reg & 0xFF);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &cs53l30_driver, &cs53l30_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to register component: %d\n", ret);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	regulator_bulk_disable(ARRAY_SIZE(cs53l30->supplies),
			       cs53l30->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक cs53l30_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs53l30_निजी *cs53l30 = i2c_get_clientdata(client);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs53l30->reset_gpio, 0);

	regulator_bulk_disable(ARRAY_SIZE(cs53l30->supplies),
			       cs53l30->supplies);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs53l30_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs53l30_निजी *cs53l30 = dev_get_drvdata(dev);

	regcache_cache_only(cs53l30->regmap, true);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs53l30->reset_gpio, 0);

	regulator_bulk_disable(ARRAY_SIZE(cs53l30->supplies),
			       cs53l30->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक cs53l30_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs53l30_निजी *cs53l30 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(cs53l30->supplies),
				    cs53l30->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(cs53l30->reset_gpio, 1);

	regcache_cache_only(cs53l30->regmap, false);
	ret = regcache_sync(cs53l30->regmap);
	अगर (ret) अणु
		dev_err(dev, "failed to synchronize regcache: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cs53l30_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cs53l30_runसमय_suspend, cs53l30_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs53l30_of_match[] = अणु
	अणु .compatible = "cirrus,cs53l30", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cs53l30_of_match);

अटल स्थिर काष्ठा i2c_device_id cs53l30_id[] = अणु
	अणु "cs53l30", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs53l30_id);

अटल काष्ठा i2c_driver cs53l30_i2c_driver = अणु
	.driver = अणु
		.name = "cs53l30",
		.of_match_table = cs53l30_of_match,
		.pm = &cs53l30_runसमय_pm,
	पूर्ण,
	.id_table = cs53l30_id,
	.probe = cs53l30_i2c_probe,
	.हटाओ = cs53l30_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs53l30_i2c_driver);

MODULE_DESCRIPTION("ASoC CS53L30 driver");
MODULE_AUTHOR("Paul Handrigan, Cirrus Logic Inc, <Paul.Handrigan@cirrus.com>");
MODULE_LICENSE("GPL");
