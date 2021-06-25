<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC CX20721/CX20723 codec driver
//
// Copyright:	(C) 2017 Conexant Systems, Inc.
// Author:	Simon Ho, <Simon.ho@conexant.com>
//
// TODO: add support क्रम TDM mode.
//

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश "cx2072x.h"

#घोषणा PLL_OUT_HZ_48	(1024 * 3 * 48000)
#घोषणा BITS_PER_SLOT	8

/* codec निजी data */
काष्ठा cx2072x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;
	अचिन्हित पूर्णांक mclk_rate;
	काष्ठा device *dev;
	काष्ठा snd_soc_component *codec;
	काष्ठा snd_soc_jack_gpio jack_gpio;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक bclk_ratio;
	bool pll_changed;
	bool i2spcm_changed;
	पूर्णांक sample_size;
	पूर्णांक frame_size;
	पूर्णांक sample_rate;
	अचिन्हित पूर्णांक dai_fmt;
	bool en_aec_ref;
पूर्ण;

/*
 * DAC/ADC Volume
 *
 * max : 74 : 0 dB
 *	 ( in 1 dB  step )
 * min : 0 : -74 dB
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -7400, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -7400, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, 0, 1200, 0);

काष्ठा cx2072x_eq_ctrl अणु
	u8 ch;
	u8 band;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(hpf_tlv,
	0, 0, TLV_DB_SCALE_ITEM(120, 0, 0),
	1, 63, TLV_DB_SCALE_ITEM(30, 30, 0)
);

/* Lookup table क्रम PRE_DIV */
अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक mclk;
	अचिन्हित पूर्णांक भाग;
पूर्ण mclk_pre_भाग[] = अणु
	अणु 6144000, 1 पूर्ण,
	अणु 12288000, 2 पूर्ण,
	अणु 19200000, 3 पूर्ण,
	अणु 26000000, 4 पूर्ण,
	अणु 28224000, 5 पूर्ण,
	अणु 36864000, 6 पूर्ण,
	अणु 36864000, 7 पूर्ण,
	अणु 48000000, 8 पूर्ण,
	अणु 49152000, 8 पूर्ण,
पूर्ण;

/*
 * cx2072x रेजिस्टर cache.
 */
अटल स्थिर काष्ठा reg_शेष cx2072x_reg_शेषs[] = अणु
	अणु CX2072X_AFG_POWER_STATE, 0x00000003 पूर्ण,
	अणु CX2072X_UM_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_DATA, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_ENABLE, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_सूचीECTION, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_WAKE, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_UM_ENABLE, 0x00000000 पूर्ण,
	अणु CX2072X_GPIO_STICKY_MASK, 0x00000000 पूर्ण,
	अणु CX2072X_DAC1_CONVERTER_FORMAT, 0x00000031 पूर्ण,
	अणु CX2072X_DAC1_AMP_GAIN_RIGHT, 0x0000004a पूर्ण,
	अणु CX2072X_DAC1_AMP_GAIN_LEFT, 0x0000004a पूर्ण,
	अणु CX2072X_DAC1_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_DAC1_CONVERTER_STREAM_CHANNEL, 0x00000000 पूर्ण,
	अणु CX2072X_DAC1_EAPD_ENABLE, 0x00000000 पूर्ण,
	अणु CX2072X_DAC2_CONVERTER_FORMAT, 0x00000031 पूर्ण,
	अणु CX2072X_DAC2_AMP_GAIN_RIGHT, 0x0000004a पूर्ण,
	अणु CX2072X_DAC2_AMP_GAIN_LEFT, 0x0000004a पूर्ण,
	अणु CX2072X_DAC2_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_DAC2_CONVERTER_STREAM_CHANNEL, 0x00000000 पूर्ण,
	अणु CX2072X_ADC1_CONVERTER_FORMAT, 0x00000031 पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_0, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_0, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_1, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_1, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_2, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_2, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_3, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_3, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_4, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_4, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_5, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_5, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_RIGHT_6, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_AMP_GAIN_LEFT_6, 0x0000004a पूर्ण,
	अणु CX2072X_ADC1_CONNECTION_SELECT_CONTROL, 0x00000000 पूर्ण,
	अणु CX2072X_ADC1_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_ADC1_CONVERTER_STREAM_CHANNEL, 0x00000000 पूर्ण,
	अणु CX2072X_ADC2_CONVERTER_FORMAT, 0x00000031 पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_RIGHT_0, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_LEFT_0, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_RIGHT_1, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_LEFT_1, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_RIGHT_2, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_AMP_GAIN_LEFT_2, 0x0000004a पूर्ण,
	अणु CX2072X_ADC2_CONNECTION_SELECT_CONTROL, 0x00000000 पूर्ण,
	अणु CX2072X_ADC2_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_ADC2_CONVERTER_STREAM_CHANNEL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTA_CONNECTION_SELECT_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTA_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTA_PIN_CTRL, 0x000000c0 पूर्ण,
	अणु CX2072X_PORTA_UNSOLICITED_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTA_PIN_SENSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTA_EAPD_BTL, 0x00000002 पूर्ण,
	अणु CX2072X_PORTB_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTB_PIN_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTB_UNSOLICITED_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTB_PIN_SENSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTB_EAPD_BTL, 0x00000002 पूर्ण,
	अणु CX2072X_PORTB_GAIN_RIGHT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTB_GAIN_LEFT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTC_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTC_PIN_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTC_GAIN_RIGHT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTC_GAIN_LEFT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTD_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTD_PIN_CTRL, 0x00000020 पूर्ण,
	अणु CX2072X_PORTD_UNSOLICITED_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTD_PIN_SENSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTD_GAIN_RIGHT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTD_GAIN_LEFT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTE_CONNECTION_SELECT_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTE_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTE_PIN_CTRL, 0x00000040 पूर्ण,
	अणु CX2072X_PORTE_UNSOLICITED_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTE_PIN_SENSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTE_EAPD_BTL, 0x00000002 पूर्ण,
	अणु CX2072X_PORTE_GAIN_RIGHT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTE_GAIN_LEFT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTF_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTF_PIN_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTF_UNSOLICITED_RESPONSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTF_PIN_SENSE, 0x00000000 पूर्ण,
	अणु CX2072X_PORTF_GAIN_RIGHT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTF_GAIN_LEFT, 0x00000000 पूर्ण,
	अणु CX2072X_PORTG_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTG_PIN_CTRL, 0x00000040 पूर्ण,
	अणु CX2072X_PORTG_CONNECTION_SELECT_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTG_EAPD_BTL, 0x00000002 पूर्ण,
	अणु CX2072X_PORTM_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_PORTM_PIN_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTM_CONNECTION_SELECT_CTRL, 0x00000000 पूर्ण,
	अणु CX2072X_PORTM_EAPD_BTL, 0x00000002 पूर्ण,
	अणु CX2072X_MIXER_POWER_STATE, 0x00000433 पूर्ण,
	अणु CX2072X_MIXER_GAIN_RIGHT_0, 0x0000004a पूर्ण,
	अणु CX2072X_MIXER_GAIN_LEFT_0, 0x0000004a पूर्ण,
	अणु CX2072X_MIXER_GAIN_RIGHT_1, 0x0000004a पूर्ण,
	अणु CX2072X_MIXER_GAIN_LEFT_1, 0x0000004a पूर्ण,
	अणु CX2072X_SPKR_DRC_ENABLE_STEP, 0x040065a4 पूर्ण,
	अणु CX2072X_SPKR_DRC_CONTROL, 0x007b0024 पूर्ण,
	अणु CX2072X_SPKR_DRC_TEST, 0x00000000 पूर्ण,
	अणु CX2072X_DIGITAL_BIOS_TEST0, 0x001f008a पूर्ण,
	अणु CX2072X_DIGITAL_BIOS_TEST2, 0x00990026 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL1, 0x00010001 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL2, 0x00000000 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL3, 0x00000000 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL4, 0x00000000 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL5, 0x00000000 पूर्ण,
	अणु CX2072X_I2SPCM_CONTROL6, 0x00000000 पूर्ण,
	अणु CX2072X_UM_INTERRUPT_CRTL_E, 0x00000000 पूर्ण,
	अणु CX2072X_CODEC_TEST2, 0x00000000 पूर्ण,
	अणु CX2072X_CODEC_TEST9, 0x00000004 पूर्ण,
	अणु CX2072X_CODEC_TEST20, 0x00000600 पूर्ण,
	अणु CX2072X_CODEC_TEST26, 0x00000208 पूर्ण,
	अणु CX2072X_ANALOG_TEST4, 0x00000000 पूर्ण,
	अणु CX2072X_ANALOG_TEST5, 0x00000000 पूर्ण,
	अणु CX2072X_ANALOG_TEST6, 0x0000059a पूर्ण,
	अणु CX2072X_ANALOG_TEST7, 0x000000a7 पूर्ण,
	अणु CX2072X_ANALOG_TEST8, 0x00000017 पूर्ण,
	अणु CX2072X_ANALOG_TEST9, 0x00000000 पूर्ण,
	अणु CX2072X_ANALOG_TEST10, 0x00000285 पूर्ण,
	अणु CX2072X_ANALOG_TEST11, 0x00000000 पूर्ण,
	अणु CX2072X_ANALOG_TEST12, 0x00000000 पूर्ण,
	अणु CX2072X_ANALOG_TEST13, 0x00000000 पूर्ण,
	अणु CX2072X_DIGITAL_TEST1, 0x00000242 पूर्ण,
	अणु CX2072X_DIGITAL_TEST11, 0x00000000 पूर्ण,
	अणु CX2072X_DIGITAL_TEST12, 0x00000084 पूर्ण,
	अणु CX2072X_DIGITAL_TEST15, 0x00000077 पूर्ण,
	अणु CX2072X_DIGITAL_TEST16, 0x00000021 पूर्ण,
	अणु CX2072X_DIGITAL_TEST17, 0x00000018 पूर्ण,
	अणु CX2072X_DIGITAL_TEST18, 0x00000024 पूर्ण,
	अणु CX2072X_DIGITAL_TEST19, 0x00000001 पूर्ण,
	अणु CX2072X_DIGITAL_TEST20, 0x00000002 पूर्ण,
पूर्ण;

/*
 * रेजिस्टर initialization
 */
अटल स्थिर काष्ठा reg_sequence cx2072x_reg_init[] = अणु
	अणु CX2072X_ANALOG_TEST9,	0x080 पूर्ण,    /* DC offset Calibration */
	अणु CX2072X_CODEC_TEST26,	0x65f पूर्ण,    /* Disable the PA */
	अणु CX2072X_ANALOG_TEST10, 0x289 पूर्ण,   /* Set the speaker output gain */
	अणु CX2072X_CODEC_TEST20,	0xf05 पूर्ण,
	अणु CX2072X_CODEC_TESTXX,	0x380 पूर्ण,
	अणु CX2072X_CODEC_TEST26,	0xb90 पूर्ण,
	अणु CX2072X_CODEC_TEST9,	0x001 पूर्ण,    /* Enable 30 Hz High pass filter */
	अणु CX2072X_ANALOG_TEST3,	0x300 पूर्ण,    /* Disable PCBEEP pad */
	अणु CX2072X_CODEC_TEST24,	0x100 पूर्ण,    /* Disable SnM mode */
	अणु CX2072X_PORTD_PIN_CTRL, 0x020 पूर्ण,  /* Enable PortD input */
	अणु CX2072X_GPIO_ENABLE,	0x040 पूर्ण,    /* Enable GPIO7 pin क्रम button */
	अणु CX2072X_GPIO_UM_ENABLE, 0x040 पूर्ण,  /* Enable UM क्रम GPIO7 */
	अणु CX2072X_UM_RESPONSE,	0x080 पूर्ण,    /* Enable button response */
	अणु CX2072X_DIGITAL_TEST12, 0x0c4 पूर्ण,  /* Enable headset button */
	अणु CX2072X_DIGITAL_TEST0, 0x415 पूर्ण,   /* Power करोwn class-D during idle */
	अणु CX2072X_I2SPCM_CONTROL2, 0x00f पूर्ण, /* Enable I2S TX */
	अणु CX2072X_I2SPCM_CONTROL3, 0x00f पूर्ण, /* Enable I2S RX */
पूर्ण;

अटल अचिन्हित पूर्णांक cx2072x_रेजिस्टर_size(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CX2072X_VENDOR_ID:
	हाल CX2072X_REVISION_ID:
	हाल CX2072X_PORTA_PIN_SENSE:
	हाल CX2072X_PORTB_PIN_SENSE:
	हाल CX2072X_PORTD_PIN_SENSE:
	हाल CX2072X_PORTE_PIN_SENSE:
	हाल CX2072X_PORTF_PIN_SENSE:
	हाल CX2072X_I2SPCM_CONTROL1:
	हाल CX2072X_I2SPCM_CONTROL2:
	हाल CX2072X_I2SPCM_CONTROL3:
	हाल CX2072X_I2SPCM_CONTROL4:
	हाल CX2072X_I2SPCM_CONTROL5:
	हाल CX2072X_I2SPCM_CONTROL6:
	हाल CX2072X_UM_INTERRUPT_CRTL_E:
	हाल CX2072X_EQ_G_COEFF:
	हाल CX2072X_SPKR_DRC_CONTROL:
	हाल CX2072X_SPKR_DRC_TEST:
	हाल CX2072X_DIGITAL_BIOS_TEST0:
	हाल CX2072X_DIGITAL_BIOS_TEST2:
		वापस 4;
	हाल CX2072X_EQ_ENABLE_BYPASS:
	हाल CX2072X_EQ_B0_COEFF:
	हाल CX2072X_EQ_B1_COEFF:
	हाल CX2072X_EQ_B2_COEFF:
	हाल CX2072X_EQ_A1_COEFF:
	हाल CX2072X_EQ_A2_COEFF:
	हाल CX2072X_DAC1_CONVERTER_FORMAT:
	हाल CX2072X_DAC2_CONVERTER_FORMAT:
	हाल CX2072X_ADC1_CONVERTER_FORMAT:
	हाल CX2072X_ADC2_CONVERTER_FORMAT:
	हाल CX2072X_CODEC_TEST2:
	हाल CX2072X_CODEC_TEST9:
	हाल CX2072X_CODEC_TEST20:
	हाल CX2072X_CODEC_TEST26:
	हाल CX2072X_ANALOG_TEST3:
	हाल CX2072X_ANALOG_TEST4:
	हाल CX2072X_ANALOG_TEST5:
	हाल CX2072X_ANALOG_TEST6:
	हाल CX2072X_ANALOG_TEST7:
	हाल CX2072X_ANALOG_TEST8:
	हाल CX2072X_ANALOG_TEST9:
	हाल CX2072X_ANALOG_TEST10:
	हाल CX2072X_ANALOG_TEST11:
	हाल CX2072X_ANALOG_TEST12:
	हाल CX2072X_ANALOG_TEST13:
	हाल CX2072X_DIGITAL_TEST0:
	हाल CX2072X_DIGITAL_TEST1:
	हाल CX2072X_DIGITAL_TEST11:
	हाल CX2072X_DIGITAL_TEST12:
	हाल CX2072X_DIGITAL_TEST15:
	हाल CX2072X_DIGITAL_TEST16:
	हाल CX2072X_DIGITAL_TEST17:
	हाल CX2072X_DIGITAL_TEST18:
	हाल CX2072X_DIGITAL_TEST19:
	हाल CX2072X_DIGITAL_TEST20:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल bool cx2072x_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CX2072X_VENDOR_ID:
	हाल CX2072X_REVISION_ID:
	हाल CX2072X_CURRENT_BCLK_FREQUENCY:
	हाल CX2072X_AFG_POWER_STATE:
	हाल CX2072X_UM_RESPONSE:
	हाल CX2072X_GPIO_DATA:
	हाल CX2072X_GPIO_ENABLE:
	हाल CX2072X_GPIO_सूचीECTION:
	हाल CX2072X_GPIO_WAKE:
	हाल CX2072X_GPIO_UM_ENABLE:
	हाल CX2072X_GPIO_STICKY_MASK:
	हाल CX2072X_DAC1_CONVERTER_FORMAT:
	हाल CX2072X_DAC1_AMP_GAIN_RIGHT:
	हाल CX2072X_DAC1_AMP_GAIN_LEFT:
	हाल CX2072X_DAC1_POWER_STATE:
	हाल CX2072X_DAC1_CONVERTER_STREAM_CHANNEL:
	हाल CX2072X_DAC1_EAPD_ENABLE:
	हाल CX2072X_DAC2_CONVERTER_FORMAT:
	हाल CX2072X_DAC2_AMP_GAIN_RIGHT:
	हाल CX2072X_DAC2_AMP_GAIN_LEFT:
	हाल CX2072X_DAC2_POWER_STATE:
	हाल CX2072X_DAC2_CONVERTER_STREAM_CHANNEL:
	हाल CX2072X_ADC1_CONVERTER_FORMAT:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_0:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_0:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_1:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_1:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_2:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_2:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_3:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_3:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_4:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_4:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_5:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_5:
	हाल CX2072X_ADC1_AMP_GAIN_RIGHT_6:
	हाल CX2072X_ADC1_AMP_GAIN_LEFT_6:
	हाल CX2072X_ADC1_CONNECTION_SELECT_CONTROL:
	हाल CX2072X_ADC1_POWER_STATE:
	हाल CX2072X_ADC1_CONVERTER_STREAM_CHANNEL:
	हाल CX2072X_ADC2_CONVERTER_FORMAT:
	हाल CX2072X_ADC2_AMP_GAIN_RIGHT_0:
	हाल CX2072X_ADC2_AMP_GAIN_LEFT_0:
	हाल CX2072X_ADC2_AMP_GAIN_RIGHT_1:
	हाल CX2072X_ADC2_AMP_GAIN_LEFT_1:
	हाल CX2072X_ADC2_AMP_GAIN_RIGHT_2:
	हाल CX2072X_ADC2_AMP_GAIN_LEFT_2:
	हाल CX2072X_ADC2_CONNECTION_SELECT_CONTROL:
	हाल CX2072X_ADC2_POWER_STATE:
	हाल CX2072X_ADC2_CONVERTER_STREAM_CHANNEL:
	हाल CX2072X_PORTA_CONNECTION_SELECT_CTRL:
	हाल CX2072X_PORTA_POWER_STATE:
	हाल CX2072X_PORTA_PIN_CTRL:
	हाल CX2072X_PORTA_UNSOLICITED_RESPONSE:
	हाल CX2072X_PORTA_PIN_SENSE:
	हाल CX2072X_PORTA_EAPD_BTL:
	हाल CX2072X_PORTB_POWER_STATE:
	हाल CX2072X_PORTB_PIN_CTRL:
	हाल CX2072X_PORTB_UNSOLICITED_RESPONSE:
	हाल CX2072X_PORTB_PIN_SENSE:
	हाल CX2072X_PORTB_EAPD_BTL:
	हाल CX2072X_PORTB_GAIN_RIGHT:
	हाल CX2072X_PORTB_GAIN_LEFT:
	हाल CX2072X_PORTC_POWER_STATE:
	हाल CX2072X_PORTC_PIN_CTRL:
	हाल CX2072X_PORTC_GAIN_RIGHT:
	हाल CX2072X_PORTC_GAIN_LEFT:
	हाल CX2072X_PORTD_POWER_STATE:
	हाल CX2072X_PORTD_PIN_CTRL:
	हाल CX2072X_PORTD_UNSOLICITED_RESPONSE:
	हाल CX2072X_PORTD_PIN_SENSE:
	हाल CX2072X_PORTD_GAIN_RIGHT:
	हाल CX2072X_PORTD_GAIN_LEFT:
	हाल CX2072X_PORTE_CONNECTION_SELECT_CTRL:
	हाल CX2072X_PORTE_POWER_STATE:
	हाल CX2072X_PORTE_PIN_CTRL:
	हाल CX2072X_PORTE_UNSOLICITED_RESPONSE:
	हाल CX2072X_PORTE_PIN_SENSE:
	हाल CX2072X_PORTE_EAPD_BTL:
	हाल CX2072X_PORTE_GAIN_RIGHT:
	हाल CX2072X_PORTE_GAIN_LEFT:
	हाल CX2072X_PORTF_POWER_STATE:
	हाल CX2072X_PORTF_PIN_CTRL:
	हाल CX2072X_PORTF_UNSOLICITED_RESPONSE:
	हाल CX2072X_PORTF_PIN_SENSE:
	हाल CX2072X_PORTF_GAIN_RIGHT:
	हाल CX2072X_PORTF_GAIN_LEFT:
	हाल CX2072X_PORTG_POWER_STATE:
	हाल CX2072X_PORTG_PIN_CTRL:
	हाल CX2072X_PORTG_CONNECTION_SELECT_CTRL:
	हाल CX2072X_PORTG_EAPD_BTL:
	हाल CX2072X_PORTM_POWER_STATE:
	हाल CX2072X_PORTM_PIN_CTRL:
	हाल CX2072X_PORTM_CONNECTION_SELECT_CTRL:
	हाल CX2072X_PORTM_EAPD_BTL:
	हाल CX2072X_MIXER_POWER_STATE:
	हाल CX2072X_MIXER_GAIN_RIGHT_0:
	हाल CX2072X_MIXER_GAIN_LEFT_0:
	हाल CX2072X_MIXER_GAIN_RIGHT_1:
	हाल CX2072X_MIXER_GAIN_LEFT_1:
	हाल CX2072X_EQ_ENABLE_BYPASS:
	हाल CX2072X_EQ_B0_COEFF:
	हाल CX2072X_EQ_B1_COEFF:
	हाल CX2072X_EQ_B2_COEFF:
	हाल CX2072X_EQ_A1_COEFF:
	हाल CX2072X_EQ_A2_COEFF:
	हाल CX2072X_EQ_G_COEFF:
	हाल CX2072X_SPKR_DRC_ENABLE_STEP:
	हाल CX2072X_SPKR_DRC_CONTROL:
	हाल CX2072X_SPKR_DRC_TEST:
	हाल CX2072X_DIGITAL_BIOS_TEST0:
	हाल CX2072X_DIGITAL_BIOS_TEST2:
	हाल CX2072X_I2SPCM_CONTROL1:
	हाल CX2072X_I2SPCM_CONTROL2:
	हाल CX2072X_I2SPCM_CONTROL3:
	हाल CX2072X_I2SPCM_CONTROL4:
	हाल CX2072X_I2SPCM_CONTROL5:
	हाल CX2072X_I2SPCM_CONTROL6:
	हाल CX2072X_UM_INTERRUPT_CRTL_E:
	हाल CX2072X_CODEC_TEST2:
	हाल CX2072X_CODEC_TEST9:
	हाल CX2072X_CODEC_TEST20:
	हाल CX2072X_CODEC_TEST26:
	हाल CX2072X_ANALOG_TEST4:
	हाल CX2072X_ANALOG_TEST5:
	हाल CX2072X_ANALOG_TEST6:
	हाल CX2072X_ANALOG_TEST7:
	हाल CX2072X_ANALOG_TEST8:
	हाल CX2072X_ANALOG_TEST9:
	हाल CX2072X_ANALOG_TEST10:
	हाल CX2072X_ANALOG_TEST11:
	हाल CX2072X_ANALOG_TEST12:
	हाल CX2072X_ANALOG_TEST13:
	हाल CX2072X_DIGITAL_TEST0:
	हाल CX2072X_DIGITAL_TEST1:
	हाल CX2072X_DIGITAL_TEST11:
	हाल CX2072X_DIGITAL_TEST12:
	हाल CX2072X_DIGITAL_TEST15:
	हाल CX2072X_DIGITAL_TEST16:
	हाल CX2072X_DIGITAL_TEST17:
	हाल CX2072X_DIGITAL_TEST18:
	हाल CX2072X_DIGITAL_TEST19:
	हाल CX2072X_DIGITAL_TEST20:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cx2072x_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CX2072X_VENDOR_ID:
	हाल CX2072X_REVISION_ID:
	हाल CX2072X_UM_INTERRUPT_CRTL_E:
	हाल CX2072X_DIGITAL_TEST11:
	हाल CX2072X_PORTA_PIN_SENSE:
	हाल CX2072X_PORTB_PIN_SENSE:
	हाल CX2072X_PORTD_PIN_SENSE:
	हाल CX2072X_PORTE_PIN_SENSE:
	हाल CX2072X_PORTF_PIN_SENSE:
	हाल CX2072X_EQ_G_COEFF:
	हाल CX2072X_EQ_BAND:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक cx2072x_reg_raw_ग_लिखो(काष्ठा i2c_client *client,
				 अचिन्हित पूर्णांक reg,
				 स्थिर व्योम *val, माप_प्रकार val_count)
अणु
	काष्ठा device *dev = &client->dev;
	u8 buf[2 + CX2072X_MAX_EQ_COEFF];
	पूर्णांक ret;

	अगर (WARN_ON(val_count + 2 > माप(buf)))
		वापस -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	स_नकल(buf + 2, val, val_count);

	ret = i2c_master_send(client, buf, val_count + 2);
	अगर (ret != val_count + 2) अणु
		dev_err(dev, "I2C write failed, ret = %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक value)
अणु
	__le32 raw_value;
	अचिन्हित पूर्णांक size;

	size = cx2072x_रेजिस्टर_size(reg);

	अगर (reg == CX2072X_UM_INTERRUPT_CRTL_E) अणु
		/* Update the MSB byte only */
		reg += 3;
		size = 1;
		value >>= 24;
	पूर्ण

	raw_value = cpu_to_le32(value);
	वापस cx2072x_reg_raw_ग_लिखो(context, reg, &raw_value, size);
पूर्ण

अटल पूर्णांक cx2072x_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *value)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा device *dev = &client->dev;
	__le32 recv_buf = 0;
	काष्ठा i2c_msg msgs[2];
	अचिन्हित पूर्णांक size;
	u8 send_buf[2];
	पूर्णांक ret;

	size = cx2072x_रेजिस्टर_size(reg);

	send_buf[0] = reg >> 8;
	send_buf[1] = reg & 0xff;

	msgs[0].addr = client->addr;
	msgs[0].len = माप(send_buf);
	msgs[0].buf = send_buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = size;
	msgs[1].buf = (u8 *)&recv_buf;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(dev, "Failed to read register, ret = %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	*value = le32_to_cpu(recv_buf);
	वापस 0;
पूर्ण

/* get suggested pre_भाग valuce from mclk frequency */
अटल अचिन्हित पूर्णांक get_भाग_from_mclk(अचिन्हित पूर्णांक mclk)
अणु
	अचिन्हित पूर्णांक भाग = 8;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mclk_pre_भाग); i++) अणु
		अगर (mclk <= mclk_pre_भाग[i].mclk) अणु
			भाग = mclk_pre_भाग[i].भाग;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस भाग;
पूर्ण

अटल पूर्णांक cx2072x_config_pll(काष्ठा cx2072x_priv *cx2072x)
अणु
	काष्ठा device *dev = cx2072x->dev;
	अचिन्हित पूर्णांक pre_भाग;
	अचिन्हित पूर्णांक pre_भाग_val;
	अचिन्हित पूर्णांक pll_input;
	अचिन्हित पूर्णांक pll_output;
	अचिन्हित पूर्णांक पूर्णांक_भाग;
	अचिन्हित पूर्णांक frac_भाग;
	u64 frac_num;
	अचिन्हित पूर्णांक frac;
	अचिन्हित पूर्णांक sample_rate = cx2072x->sample_rate;
	पूर्णांक pt_sample_per_sync = 2;
	पूर्णांक pt_घड़ी_per_sample = 96;

	चयन (sample_rate) अणु
	हाल 48000:
	हाल 32000:
	हाल 24000:
	हाल 16000:
		अवरोध;

	हाल 96000:
		pt_sample_per_sync = 1;
		pt_घड़ी_per_sample = 48;
		अवरोध;

	हाल 192000:
		pt_sample_per_sync = 0;
		pt_घड़ी_per_sample = 24;
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported sample rate %d\n", sample_rate);
		वापस -EINVAL;
	पूर्ण

	/* Configure PLL settings */
	pre_भाग = get_भाग_from_mclk(cx2072x->mclk_rate);
	pll_input = cx2072x->mclk_rate / pre_भाग;
	pll_output = sample_rate * 3072;
	पूर्णांक_भाग = pll_output / pll_input;
	frac_भाग = pll_output - (पूर्णांक_भाग * pll_input);

	अगर (frac_भाग) अणु
		frac_भाग *= 1000;
		frac_भाग /= pll_input;
		frac_num = (u64)(4000 + frac_भाग) * ((1 << 20) - 4);
		करो_भाग(frac_num, 7);
		frac = ((u32)frac_num + 499) / 1000;
	पूर्ण
	pre_भाग_val = (pre_भाग - 1) * 2;

	regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST4,
		     0x40 | (pre_भाग_val << 8));
	अगर (frac_भाग == 0) अणु
		/* Int mode */
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST7, 0x100);
	पूर्ण अन्यथा अणु
		/* frac mode */
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST6,
			     frac & 0xfff);
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST7,
			     (u8)(frac >> 12));
	पूर्ण

	पूर्णांक_भाग--;
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST8, पूर्णांक_भाग);

	/* configure PLL tracking */
	अगर (frac_भाग == 0) अणु
		/* disable PLL tracking */
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST16, 0x00);
	पूर्ण अन्यथा अणु
		/* configure and enable PLL tracking */
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST16,
			     (pt_sample_per_sync << 4) & 0xf0);
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST17,
			     pt_घड़ी_per_sample);
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST18,
			     pt_घड़ी_per_sample * 3 / 2);
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST19, 0x01);
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST20, 0x02);
		regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_TEST16,
				   0x01, 0x01);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_config_i2spcm(काष्ठा cx2072x_priv *cx2072x)
अणु
	काष्ठा device *dev = cx2072x->dev;
	अचिन्हित पूर्णांक bclk_rate = 0;
	पूर्णांक is_i2s = 0;
	पूर्णांक has_one_bit_delay = 0;
	पूर्णांक is_frame_inv = 0;
	पूर्णांक is_bclk_inv = 0;
	पूर्णांक pulse_len;
	पूर्णांक frame_len = cx2072x->frame_size;
	पूर्णांक sample_size = cx2072x->sample_size;
	पूर्णांक i2s_right_slot;
	पूर्णांक i2s_right_छोड़ो_पूर्णांकerval = 0;
	पूर्णांक i2s_right_छोड़ो_pos;
	पूर्णांक is_big_endian = 1;
	u64 भाग;
	अचिन्हित पूर्णांक mod;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg1 reg1;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg2 reg2;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg3 reg3;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg4 reg4;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg5 reg5;
	जोड़ cx2072x_reg_i2spcm_ctrl_reg6 reg6;
	जोड़ cx2072x_reg_digital_bios_test2 regdbt2;
	स्थिर अचिन्हित पूर्णांक fmt = cx2072x->dai_fmt;

	अगर (frame_len <= 0) अणु
		dev_err(dev, "Incorrect frame len %d\n", frame_len);
		वापस -EINVAL;
	पूर्ण

	अगर (sample_size <= 0) अणु
		dev_err(dev, "Incorrect sample size %d\n", sample_size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "config_i2spcm set_dai_fmt- %08x\n", fmt);

	regdbt2.ulval = 0xac;

	/* set master/slave */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg2.r.tx_master = 1;
		reg3.r.rx_master = 1;
		dev_dbg(dev, "Sets Master mode\n");
		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg2.r.tx_master = 0;
		reg3.r.rx_master = 0;
		dev_dbg(dev, "Sets Slave mode\n");
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI master mode\n");
		वापस -EINVAL;
	पूर्ण

	/* set क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		is_i2s = 1;
		has_one_bit_delay = 1;
		pulse_len = frame_len / 2;
		अवरोध;

	हाल SND_SOC_DAIFMT_RIGHT_J:
		is_i2s = 1;
		pulse_len = frame_len / 2;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		is_i2s = 1;
		pulse_len = frame_len / 2;
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI format\n");
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		is_frame_inv = is_i2s;
		is_bclk_inv = is_i2s;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_IF:
		is_frame_inv = !is_i2s;
		is_bclk_inv = !is_i2s;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_NF:
		is_frame_inv = is_i2s;
		is_bclk_inv = !is_i2s;
		अवरोध;

	हाल SND_SOC_DAIFMT_NB_IF:
		is_frame_inv = !is_i2s;
		is_bclk_inv = is_i2s;
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI clock inversion\n");
		वापस -EINVAL;
	पूर्ण

	reg1.r.rx_data_one_line = 1;
	reg1.r.tx_data_one_line = 1;

	अगर (is_i2s) अणु
		i2s_right_slot = (frame_len / 2) / BITS_PER_SLOT;
		i2s_right_छोड़ो_पूर्णांकerval = (frame_len / 2) % BITS_PER_SLOT;
		i2s_right_छोड़ो_pos = i2s_right_slot * BITS_PER_SLOT;
	पूर्ण

	reg1.r.rx_ws_pol = is_frame_inv;
	reg1.r.rx_ws_wid = pulse_len - 1;

	reg1.r.rx_frm_len = frame_len / BITS_PER_SLOT - 1;
	reg1.r.rx_sa_size = (sample_size / BITS_PER_SLOT) - 1;

	reg1.r.tx_ws_pol = reg1.r.rx_ws_pol;
	reg1.r.tx_ws_wid = pulse_len - 1;
	reg1.r.tx_frm_len = reg1.r.rx_frm_len;
	reg1.r.tx_sa_size = reg1.r.rx_sa_size;

	reg2.r.tx_endian_sel = !is_big_endian;
	reg2.r.tx_dstart_dly = has_one_bit_delay;
	अगर (cx2072x->en_aec_ref)
		reg2.r.tx_dstart_dly = 0;

	reg3.r.rx_endian_sel = !is_big_endian;
	reg3.r.rx_dstart_dly = has_one_bit_delay;

	reg4.ulval = 0;

	अगर (is_i2s) अणु
		reg2.r.tx_slot_1 = 0;
		reg2.r.tx_slot_2 = i2s_right_slot;
		reg3.r.rx_slot_1 = 0;
		अगर (cx2072x->en_aec_ref)
			reg3.r.rx_slot_2 = 0;
		अन्यथा
			reg3.r.rx_slot_2 = i2s_right_slot;
		reg6.r.rx_छोड़ो_start_pos = i2s_right_छोड़ो_pos;
		reg6.r.rx_छोड़ो_cycles = i2s_right_छोड़ो_पूर्णांकerval;
		reg6.r.tx_छोड़ो_start_pos = i2s_right_छोड़ो_pos;
		reg6.r.tx_छोड़ो_cycles = i2s_right_छोड़ो_पूर्णांकerval;
	पूर्ण अन्यथा अणु
		dev_err(dev, "TDM mode is not implemented yet\n");
		वापस -EINVAL;
	पूर्ण
	regdbt2.r.i2s_bclk_invert = is_bclk_inv;

	/* Configures the BCLK output */
	bclk_rate = cx2072x->sample_rate * frame_len;
	reg5.r.i2s_pcm_clk_भाग_chan_en = 0;

	/* Disables bclk output beक्रमe setting new value */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_I2SPCM_CONTROL5, 0);

	अगर (reg2.r.tx_master) अणु
		/* Configures BCLK rate */
		भाग = PLL_OUT_HZ_48;
		mod = करो_भाग(भाग, bclk_rate);
		अगर (mod) अणु
			dev_err(dev, "Unsupported BCLK %dHz\n", bclk_rate);
			वापस -EINVAL;
		पूर्ण
		dev_dbg(dev, "enables BCLK %dHz output\n", bclk_rate);
		reg5.r.i2s_pcm_clk_भाग = (u32)भाग - 1;
		reg5.r.i2s_pcm_clk_भाग_chan_en = 1;
	पूर्ण

	regmap_ग_लिखो(cx2072x->regmap, CX2072X_I2SPCM_CONTROL1, reg1.ulval);
	regmap_update_bits(cx2072x->regmap, CX2072X_I2SPCM_CONTROL2, 0xffffffc0,
			   reg2.ulval);
	regmap_update_bits(cx2072x->regmap, CX2072X_I2SPCM_CONTROL3, 0xffffffc0,
			   reg3.ulval);
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_I2SPCM_CONTROL4, reg4.ulval);
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_I2SPCM_CONTROL6, reg6.ulval);
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_I2SPCM_CONTROL5, reg5.ulval);

	regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST2,
		     regdbt2.ulval);

	वापस 0;
पूर्ण

अटल पूर्णांक afg_घातer_ev(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST0,
				   0x00, 0x10);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST0,
				   0x10, 0x10);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cx2072x_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("PortD Boost Volume", CX2072X_PORTD_GAIN_LEFT,
			 CX2072X_PORTD_GAIN_RIGHT, 0, 3, 0, boost_tlv),
	SOC_DOUBLE_R_TLV("PortC Boost Volume", CX2072X_PORTC_GAIN_LEFT,
			 CX2072X_PORTC_GAIN_RIGHT, 0, 3, 0, boost_tlv),
	SOC_DOUBLE_R_TLV("PortB Boost Volume", CX2072X_PORTB_GAIN_LEFT,
			 CX2072X_PORTB_GAIN_RIGHT, 0, 3, 0, boost_tlv),
	SOC_DOUBLE_R_TLV("PortD ADC1 Volume", CX2072X_ADC1_AMP_GAIN_LEFT_1,
			 CX2072X_ADC1_AMP_GAIN_RIGHT_1, 0, 0x4a, 0, adc_tlv),
	SOC_DOUBLE_R_TLV("PortC ADC1 Volume", CX2072X_ADC1_AMP_GAIN_LEFT_2,
			 CX2072X_ADC1_AMP_GAIN_RIGHT_2, 0, 0x4a, 0, adc_tlv),
	SOC_DOUBLE_R_TLV("PortB ADC1 Volume", CX2072X_ADC1_AMP_GAIN_LEFT_0,
			 CX2072X_ADC1_AMP_GAIN_RIGHT_0, 0, 0x4a, 0, adc_tlv),
	SOC_DOUBLE_R_TLV("DAC1 Volume", CX2072X_DAC1_AMP_GAIN_LEFT,
			 CX2072X_DAC1_AMP_GAIN_RIGHT, 0, 0x4a, 0, dac_tlv),
	SOC_DOUBLE_R("DAC1 Switch", CX2072X_DAC1_AMP_GAIN_LEFT,
		     CX2072X_DAC1_AMP_GAIN_RIGHT, 7,  1, 0),
	SOC_DOUBLE_R_TLV("DAC2 Volume", CX2072X_DAC2_AMP_GAIN_LEFT,
			 CX2072X_DAC2_AMP_GAIN_RIGHT, 0, 0x4a, 0, dac_tlv),
	SOC_SINGLE_TLV("HPF Freq", CX2072X_CODEC_TEST9, 0, 0x3f, 0, hpf_tlv),
	SOC_DOUBLE("HPF Switch", CX2072X_CODEC_TEST9, 8, 9, 1, 1),
	SOC_SINGLE("PortA HP Amp Switch", CX2072X_PORTA_PIN_CTRL, 7, 1, 0),
पूर्ण;

अटल पूर्णांक cx2072x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	काष्ठा device *dev = codec->dev;
	स्थिर अचिन्हित पूर्णांक sample_rate = params_rate(params);
	पूर्णांक sample_size, frame_size;

	/* Data sizes अगर not using TDM */
	sample_size = params_width(params);

	अगर (sample_size < 0)
		वापस sample_size;

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0)
		वापस frame_size;

	अगर (cx2072x->mclk_rate == 0) अणु
		dev_err(dev, "Master clock rate is not configured\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cx2072x->bclk_ratio)
		frame_size = cx2072x->bclk_ratio;

	चयन (sample_rate) अणु
	हाल 48000:
	हाल 32000:
	हाल 24000:
	हाल 16000:
	हाल 96000:
	हाल 192000:
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported sample rate %d\n", sample_rate);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "Sample size %d bits, frame = %d bits, rate = %d Hz\n",
		sample_size, frame_size, sample_rate);

	cx2072x->frame_size = frame_size;
	cx2072x->sample_size = sample_size;
	cx2072x->sample_rate = sample_rate;

	अगर (dai->id == CX2072X_DAI_DSP) अणु
		cx2072x->en_aec_ref = true;
		dev_dbg(cx2072x->dev, "enables aec reference\n");
		regmap_ग_लिखो(cx2072x->regmap,
			     CX2072X_ADC1_CONNECTION_SELECT_CONTROL, 3);
	पूर्ण

	अगर (cx2072x->pll_changed) अणु
		cx2072x_config_pll(cx2072x);
		cx2072x->pll_changed = false;
	पूर्ण

	अगर (cx2072x->i2spcm_changed) अणु
		cx2072x_config_i2spcm(cx2072x);
		cx2072x->i2spcm_changed = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_set_dai_bclk_ratio(काष्ठा snd_soc_dai *dai,
				      अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	cx2072x->bclk_ratio = ratio;
	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	अगर (clk_set_rate(cx2072x->mclk, freq)) अणु
		dev_err(codec->dev, "set clk rate failed\n");
		वापस -EINVAL;
	पूर्ण

	cx2072x->mclk_rate = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	काष्ठा device *dev = codec->dev;

	dev_dbg(dev, "set_dai_fmt- %08x\n", fmt);
	/* set master/slave */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI master mode\n");
		वापस -EINVAL;
	पूर्ण

	/* set क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI format\n");
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_IB_IF:
	हाल SND_SOC_DAIFMT_IB_NF:
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported DAI clock inversion\n");
		वापस -EINVAL;
	पूर्ण

	cx2072x->dai_fmt = fmt;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new portaouten_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTA_PIN_CTRL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new porteouten_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTE_PIN_CTRL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new portgouten_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTG_PIN_CTRL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new porपंचांगouten_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTM_PIN_CTRL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new portbinen_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTB_PIN_CTRL, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new portcinen_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTC_PIN_CTRL, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new portdinen_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTD_PIN_CTRL, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new porteinen_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_PORTE_PIN_CTRL, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sadc1l_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL2, 0, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sadc1r_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL2, 1, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sadc2l_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL2, 2, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sadc2r_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL2, 3, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sdac1l_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL3, 0, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sdac1r_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL3, 1, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sdac2l_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL3, 2, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new i2sdac2r_ctl =
	SOC_DAPM_SINGLE("Switch", CX2072X_I2SPCM_CONTROL3, 3, 1, 0);

अटल स्थिर अक्षर * स्थिर dac_क्रमागत_text[] = अणु
	"DAC1 Switch", "DAC2 Switch",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत porta_dac_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_PORTA_CONNECTION_SELECT_CTRL, 0, 2, dac_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new porta_mux =
SOC_DAPM_ENUM("PortA Mux", porta_dac_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत portg_dac_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_PORTG_CONNECTION_SELECT_CTRL, 0, 2, dac_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new portg_mux =
SOC_DAPM_ENUM("PortG Mux", portg_dac_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत porte_dac_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_PORTE_CONNECTION_SELECT_CTRL, 0, 2, dac_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new porte_mux =
SOC_DAPM_ENUM("PortE Mux", porte_dac_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत porपंचांग_dac_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_PORTM_CONNECTION_SELECT_CTRL, 0, 2, dac_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new porपंचांग_mux =
SOC_DAPM_ENUM("PortM Mux", porपंचांग_dac_क्रमागत);

अटल स्थिर अक्षर * स्थिर adc1in_sel_text[] = अणु
	"PortB Switch", "PortD Switch", "PortC Switch", "Widget15 Switch",
	"PortE Switch", "PortF Switch", "PortH Switch"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc1in_sel_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_ADC1_CONNECTION_SELECT_CONTROL, 0, 7, adc1in_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adc1_mux =
SOC_DAPM_ENUM("ADC1 Mux", adc1in_sel_क्रमागत);

अटल स्थिर अक्षर * स्थिर adc2in_sel_text[] = अणु
	"PortC Switch", "Widget15 Switch", "PortH Switch"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc2in_sel_क्रमागत =
SOC_ENUM_SINGLE(CX2072X_ADC2_CONNECTION_SELECT_CONTROL, 0, 3, adc2in_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adc2_mux =
SOC_DAPM_ENUM("ADC2 Mux", adc2in_sel_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new wid15_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1L Switch", CX2072X_MIXER_GAIN_LEFT_0, 7, 1, 1),
	SOC_DAPM_SINGLE("DAC1R Switch", CX2072X_MIXER_GAIN_RIGHT_0, 7, 1, 1),
	SOC_DAPM_SINGLE("DAC2L Switch", CX2072X_MIXER_GAIN_LEFT_1, 7, 1, 1),
	SOC_DAPM_SINGLE("DAC2R Switch", CX2072X_MIXER_GAIN_RIGHT_1, 7, 1, 1),
पूर्ण;

#घोषणा CX2072X_DAPM_SUPPLY_S(wname, wsubseq, wreg, wshअगरt, wmask,  won_val, \
	woff_val, wevent, wflags) \
	अणु.id = snd_soc_dapm_supply, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = wreg, .shअगरt = wshअगरt, .mask = wmask, \
	.on_val = won_val, .off_val = woff_val, \
	.subseq = wsubseq, .event = wevent, .event_flags = wflagsपूर्ण

#घोषणा CX2072X_DAPM_SWITCH(wname,  wreg, wshअगरt, wmask,  won_val, woff_val, \
	wevent, wflags) \
	अणु.id = snd_soc_dapm_चयन, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = wreg, .shअगरt = wshअगरt, .mask = wmask, \
	.on_val = won_val, .off_val = woff_val, \
	.event = wevent, .event_flags = wflagsपूर्ण

#घोषणा CX2072X_DAPM_SWITCH(wname,  wreg, wshअगरt, wmask,  won_val, woff_val, \
	wevent, wflags) \
	अणु.id = snd_soc_dapm_चयन, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = wreg, .shअगरt = wshअगरt, .mask = wmask, \
	.on_val = won_val, .off_val = woff_val, \
	.event = wevent, .event_flags = wflagsपूर्ण

#घोषणा CX2072X_DAPM_REG_E(wid, wname, wreg, wshअगरt, wmask, won_val, woff_val, \
				wevent, wflags) \
	अणु.id = wid, .name = wname, .kcontrol_news = शून्य, .num_kcontrols = 0, \
	.reg = wreg, .shअगरt = wshअगरt, .mask = wmask, \
	.on_val = won_val, .off_val = woff_val, \
	.event = wevent, .event_flags = wflagsपूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cx2072x_dapm_widमाला_लो[] = अणु
	/*Playback*/
	SND_SOC_DAPM_AIF_IN("In AIF", "Playback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("I2S DAC1L", SND_SOC_NOPM, 0, 0, &i2sdac1l_ctl),
	SND_SOC_DAPM_SWITCH("I2S DAC1R", SND_SOC_NOPM, 0, 0, &i2sdac1r_ctl),
	SND_SOC_DAPM_SWITCH("I2S DAC2L", SND_SOC_NOPM, 0, 0, &i2sdac2l_ctl),
	SND_SOC_DAPM_SWITCH("I2S DAC2R", SND_SOC_NOPM, 0, 0, &i2sdac2r_ctl),

	SND_SOC_DAPM_REG(snd_soc_dapm_dac, "DAC1", CX2072X_DAC1_POWER_STATE,
			 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_REG(snd_soc_dapm_dac, "DAC2", CX2072X_DAC2_POWER_STATE,
			 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_MUX("PortA Mux", SND_SOC_NOPM, 0, 0, &porta_mux),
	SND_SOC_DAPM_MUX("PortG Mux", SND_SOC_NOPM, 0, 0, &portg_mux),
	SND_SOC_DAPM_MUX("PortE Mux", SND_SOC_NOPM, 0, 0, &porte_mux),
	SND_SOC_DAPM_MUX("PortM Mux", SND_SOC_NOPM, 0, 0, &porपंचांग_mux),

	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortA Power",
			 CX2072X_PORTA_POWER_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortM Power",
			 CX2072X_PORTM_POWER_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortG Power",
			 CX2072X_PORTG_POWER_STATE, 0, 0xfff, 0x00, 0x03),

	CX2072X_DAPM_SUPPLY_S("AFG Power", 0, CX2072X_AFG_POWER_STATE,
			      0, 0xfff, 0x00, 0x03, afg_घातer_ev,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SWITCH("PortA Out En", SND_SOC_NOPM, 0, 0,
			    &portaouten_ctl),
	SND_SOC_DAPM_SWITCH("PortE Out En", SND_SOC_NOPM, 0, 0,
			    &porteouten_ctl),
	SND_SOC_DAPM_SWITCH("PortG Out En", SND_SOC_NOPM, 0, 0,
			    &portgouten_ctl),
	SND_SOC_DAPM_SWITCH("PortM Out En", SND_SOC_NOPM, 0, 0,
			    &porपंचांगouten_ctl),

	SND_SOC_DAPM_OUTPUT("PORTA"),
	SND_SOC_DAPM_OUTPUT("PORTG"),
	SND_SOC_DAPM_OUTPUT("PORTE"),
	SND_SOC_DAPM_OUTPUT("PORTM"),
	SND_SOC_DAPM_OUTPUT("AEC REF"),

	/*Capture*/
	SND_SOC_DAPM_AIF_OUT("Out AIF", "Capture", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("I2S ADC1L", SND_SOC_NOPM, 0, 0, &i2sadc1l_ctl),
	SND_SOC_DAPM_SWITCH("I2S ADC1R", SND_SOC_NOPM, 0, 0, &i2sadc1r_ctl),
	SND_SOC_DAPM_SWITCH("I2S ADC2L", SND_SOC_NOPM, 0, 0, &i2sadc2l_ctl),
	SND_SOC_DAPM_SWITCH("I2S ADC2R", SND_SOC_NOPM, 0, 0, &i2sadc2r_ctl),

	SND_SOC_DAPM_REG(snd_soc_dapm_adc, "ADC1", CX2072X_ADC1_POWER_STATE,
			 0, 0xff, 0x00, 0x03),
	SND_SOC_DAPM_REG(snd_soc_dapm_adc, "ADC2", CX2072X_ADC2_POWER_STATE,
			 0, 0xff, 0x00, 0x03),

	SND_SOC_DAPM_MUX("ADC1 Mux", SND_SOC_NOPM, 0, 0, &adc1_mux),
	SND_SOC_DAPM_MUX("ADC2 Mux", SND_SOC_NOPM, 0, 0, &adc2_mux),

	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortB Power",
			 CX2072X_PORTB_POWER_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortC Power",
			 CX2072X_PORTC_POWER_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortD Power",
			 CX2072X_PORTD_POWER_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "PortE Power",
			 CX2072X_PORTE_POWER_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "Widget15 Power",
			 CX2072X_MIXER_POWER_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_MIXER("Widget15 Mixer", SND_SOC_NOPM, 0, 0,
			   wid15_mix, ARRAY_SIZE(wid15_mix)),
	SND_SOC_DAPM_SWITCH("PortB In En", SND_SOC_NOPM, 0, 0, &portbinen_ctl),
	SND_SOC_DAPM_SWITCH("PortC In En", SND_SOC_NOPM, 0, 0, &portcinen_ctl),
	SND_SOC_DAPM_SWITCH("PortD In En", SND_SOC_NOPM, 0, 0, &portdinen_ctl),
	SND_SOC_DAPM_SWITCH("PortE In En", SND_SOC_NOPM, 0, 0, &porteinen_ctl),

	SND_SOC_DAPM_MICBIAS("Headset Bias", CX2072X_ANALOG_TEST11, 1, 0),
	SND_SOC_DAPM_MICBIAS("PortB Mic Bias", CX2072X_PORTB_PIN_CTRL, 2, 0),
	SND_SOC_DAPM_MICBIAS("PortD Mic Bias", CX2072X_PORTD_PIN_CTRL, 2, 0),
	SND_SOC_DAPM_MICBIAS("PortE Mic Bias", CX2072X_PORTE_PIN_CTRL, 2, 0),
	SND_SOC_DAPM_INPUT("PORTB"),
	SND_SOC_DAPM_INPUT("PORTC"),
	SND_SOC_DAPM_INPUT("PORTD"),
	SND_SOC_DAPM_INPUT("PORTEIN"),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cx2072x_पूर्णांकercon[] = अणु
	/* Playback */
	अणु"In AIF", शून्य, "AFG Power"पूर्ण,
	अणु"I2S DAC1L", "Switch", "In AIF"पूर्ण,
	अणु"I2S DAC1R", "Switch", "In AIF"पूर्ण,
	अणु"I2S DAC2L", "Switch", "In AIF"पूर्ण,
	अणु"I2S DAC2R", "Switch", "In AIF"पूर्ण,
	अणु"DAC1", शून्य, "I2S DAC1L"पूर्ण,
	अणु"DAC1", शून्य, "I2S DAC1R"पूर्ण,
	अणु"DAC2", शून्य, "I2S DAC2L"पूर्ण,
	अणु"DAC2", शून्य, "I2S DAC2R"पूर्ण,
	अणु"PortA Mux", "DAC1 Switch", "DAC1"पूर्ण,
	अणु"PortA Mux", "DAC2 Switch", "DAC2"पूर्ण,
	अणु"PortG Mux", "DAC1 Switch", "DAC1"पूर्ण,
	अणु"PortG Mux", "DAC2 Switch", "DAC2"पूर्ण,
	अणु"PortE Mux", "DAC1 Switch", "DAC1"पूर्ण,
	अणु"PortE Mux", "DAC2 Switch", "DAC2"पूर्ण,
	अणु"PortM Mux", "DAC1 Switch", "DAC1"पूर्ण,
	अणु"PortM Mux", "DAC2 Switch", "DAC2"पूर्ण,
	अणु"Widget15 Mixer", "DAC1L Switch", "DAC1"पूर्ण,
	अणु"Widget15 Mixer", "DAC1R Switch", "DAC2"पूर्ण,
	अणु"Widget15 Mixer", "DAC2L Switch", "DAC1"पूर्ण,
	अणु"Widget15 Mixer", "DAC2R Switch", "DAC2"पूर्ण,
	अणु"Widget15 Mixer", शून्य, "Widget15 Power"पूर्ण,
	अणु"PortA Out En", "Switch", "PortA Mux"पूर्ण,
	अणु"PortG Out En", "Switch", "PortG Mux"पूर्ण,
	अणु"PortE Out En", "Switch", "PortE Mux"पूर्ण,
	अणु"PortM Out En", "Switch", "PortM Mux"पूर्ण,
	अणु"PortA Mux", शून्य, "PortA Power"पूर्ण,
	अणु"PortG Mux", शून्य, "PortG Power"पूर्ण,
	अणु"PortE Mux", शून्य, "PortE Power"पूर्ण,
	अणु"PortM Mux", शून्य, "PortM Power"पूर्ण,
	अणु"PortA Out En", शून्य, "PortA Power"पूर्ण,
	अणु"PortG Out En", शून्य, "PortG Power"पूर्ण,
	अणु"PortE Out En", शून्य, "PortE Power"पूर्ण,
	अणु"PortM Out En", शून्य, "PortM Power"पूर्ण,
	अणु"PORTA", शून्य, "PortA Out En"पूर्ण,
	अणु"PORTG", शून्य, "PortG Out En"पूर्ण,
	अणु"PORTE", शून्य, "PortE Out En"पूर्ण,
	अणु"PORTM", शून्य, "PortM Out En"पूर्ण,

	/* Capture */
	अणु"PORTD", शून्य, "Headset Bias"पूर्ण,
	अणु"PortB In En", "Switch", "PORTB"पूर्ण,
	अणु"PortC In En", "Switch", "PORTC"पूर्ण,
	अणु"PortD In En", "Switch", "PORTD"पूर्ण,
	अणु"PortE In En", "Switch", "PORTEIN"पूर्ण,
	अणु"ADC1 Mux", "PortB Switch", "PortB In En"पूर्ण,
	अणु"ADC1 Mux", "PortC Switch", "PortC In En"पूर्ण,
	अणु"ADC1 Mux", "PortD Switch", "PortD In En"पूर्ण,
	अणु"ADC1 Mux", "PortE Switch", "PortE In En"पूर्ण,
	अणु"ADC1 Mux", "Widget15 Switch", "Widget15 Mixer"पूर्ण,
	अणु"ADC2 Mux", "PortC Switch", "PortC In En"पूर्ण,
	अणु"ADC2 Mux", "Widget15 Switch", "Widget15 Mixer"पूर्ण,
	अणु"ADC1", शून्य, "ADC1 Mux"पूर्ण,
	अणु"ADC2", शून्य, "ADC2 Mux"पूर्ण,
	अणु"I2S ADC1L", "Switch", "ADC1"पूर्ण,
	अणु"I2S ADC1R", "Switch", "ADC1"पूर्ण,
	अणु"I2S ADC2L", "Switch", "ADC2"पूर्ण,
	अणु"I2S ADC2R", "Switch", "ADC2"पूर्ण,
	अणु"Out AIF", शून्य, "I2S ADC1L"पूर्ण,
	अणु"Out AIF", शून्य, "I2S ADC1R"पूर्ण,
	अणु"Out AIF", शून्य, "I2S ADC2L"पूर्ण,
	अणु"Out AIF", शून्य, "I2S ADC2R"पूर्ण,
	अणु"Out AIF", शून्य, "AFG Power"पूर्ण,
	अणु"AEC REF", शून्य, "Out AIF"पूर्ण,
	अणु"PortB In En", शून्य, "PortB Power"पूर्ण,
	अणु"PortC In En", शून्य, "PortC Power"पूर्ण,
	अणु"PortD In En", शून्य, "PortD Power"पूर्ण,
	अणु"PortE In En", शून्य, "PortE Power"पूर्ण,
पूर्ण;

अटल पूर्णांक cx2072x_set_bias_level(काष्ठा snd_soc_component *codec,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	स्थिर क्रमागत snd_soc_bias_level old_level =
		snd_soc_component_get_bias_level(codec);

	अगर (level == SND_SOC_BIAS_STANDBY && old_level == SND_SOC_BIAS_OFF)
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 0);
	अन्यथा अगर (level == SND_SOC_BIAS_OFF && old_level != SND_SOC_BIAS_OFF)
		regmap_ग_लिखो(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 3);

	वापस 0;
पूर्ण

/*
 * FIXME: the whole jack detection code below is pretty platक्रमm-specअगरic;
 * it has lots of implicit assumptions about the pins, etc.
 * However, since we have no other code and reference, take this hard-coded
 * setup क्रम now.  Once when we have dअगरferent platक्रमm implementations,
 * this needs to be rewritten in a more generic क्रमm, or moving पूर्णांकo the
 * platक्रमm data.
 */
अटल व्योम cx2072x_enable_jack_detect(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	/* No-sticky input type */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_GPIO_STICKY_MASK, 0x1f);

	/* Use GPOI0 as पूर्णांकerrupt pin */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0x12 << 24);

	/* Enables unsolitited message on PortA */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_PORTA_UNSOLICITED_RESPONSE, 0x80);

	/* support both nokia and apple headset set. Monitor समय = 275 ms */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST15, 0x73);

	/* Disable TIP detection */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_ANALOG_TEST12, 0x300);

	/* Switch MusicD3Live pin to GPIO */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_DIGITAL_TEST1, 0);

	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PORTD");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Headset Bias");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PortD Mic Bias");

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल व्योम cx2072x_disable_jack_detect(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	regmap_ग_लिखो(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0);
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_PORTA_UNSOLICITED_RESPONSE, 0);
पूर्ण

अटल पूर्णांक cx2072x_jack_status_check(व्योम *data)
अणु
	काष्ठा snd_soc_component *codec = data;
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	अचिन्हित पूर्णांक jack;
	अचिन्हित पूर्णांक type = 0;
	पूर्णांक state = 0;

	mutex_lock(&cx2072x->lock);

	regmap_पढ़ो(cx2072x->regmap, CX2072X_PORTA_PIN_SENSE, &jack);
	jack = jack >> 24;
	regmap_पढ़ो(cx2072x->regmap, CX2072X_DIGITAL_TEST11, &type);

	अगर (jack == 0x80) अणु
		type = type >> 8;

		अगर (type & 0x8) अणु
			/* Apple headset */
			state |= SND_JACK_HEADSET;
			अगर (type & 0x2)
				state |= SND_JACK_BTN_0;
		पूर्ण अन्यथा अणु
			/*
			 * Nokia headset (type & 0x4) and
			 * regular Headphone
			 */
			state |= SND_JACK_HEADPHONE;
		पूर्ण
	पूर्ण

	/* clear पूर्णांकerrupt */
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0x12 << 24);

	mutex_unlock(&cx2072x->lock);

	dev_dbg(codec->dev, "CX2072X_HSDETECT type=0x%X,Jack state = %x\n",
		type, state);
	वापस state;
पूर्ण

अटल स्थिर काष्ठा snd_soc_jack_gpio cx2072x_jack_gpio = अणु
	.name = "headset",
	.report = SND_JACK_HEADSET | SND_JACK_BTN_0,
	.debounce_समय = 150,
	.wake = true,
	.jack_status_check = cx2072x_jack_status_check,
पूर्ण;

अटल पूर्णांक cx2072x_set_jack(काष्ठा snd_soc_component *codec,
			    काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	पूर्णांक err;

	अगर (!jack) अणु
		cx2072x_disable_jack_detect(codec);
		वापस 0;
	पूर्ण

	अगर (!cx2072x->jack_gpio.gpiod_dev) अणु
		cx2072x->jack_gpio = cx2072x_jack_gpio;
		cx2072x->jack_gpio.gpiod_dev = codec->dev;
		cx2072x->jack_gpio.data = codec;
		err = snd_soc_jack_add_gpios(jack, 1, &cx2072x->jack_gpio);
		अगर (err) अणु
			cx2072x->jack_gpio.gpiod_dev = शून्य;
			वापस err;
		पूर्ण
	पूर्ण

	cx2072x_enable_jack_detect(codec);
	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_probe(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	cx2072x->codec = codec;

	/*
	 * FIXME: below is, again, a very platक्रमm-specअगरic init sequence,
	 * but we keep the code here just क्रम simplicity.  It seems that all
	 * existing hardware implementations require this, so there is no very
	 * much reason to move this out of the codec driver to the platक्रमm
	 * data.
	 * But of course it's no "right" thing; if you are a good boy, don't
	 * पढ़ो and follow the code like this!
	 */
	pm_runसमय_get_sync(codec->dev);
	regmap_ग_लिखो(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 0);

	regmap_multi_reg_ग_लिखो(cx2072x->regmap, cx2072x_reg_init,
			       ARRAY_SIZE(cx2072x_reg_init));

	/* configure PortC as input device */
	regmap_update_bits(cx2072x->regmap, CX2072X_PORTC_PIN_CTRL,
			   0x20, 0x20);

	regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST2,
			   0x84, 0xff);

	regmap_ग_लिखो(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 3);
	pm_runसमय_put(codec->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_driver_cx2072x = अणु
	.probe = cx2072x_probe,
	.set_bias_level = cx2072x_set_bias_level,
	.set_jack = cx2072x_set_jack,
	.controls = cx2072x_snd_controls,
	.num_controls = ARRAY_SIZE(cx2072x_snd_controls),
	.dapm_widमाला_लो = cx2072x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cx2072x_dapm_widमाला_लो),
	.dapm_routes = cx2072x_पूर्णांकercon,
	.num_dapm_routes = ARRAY_SIZE(cx2072x_पूर्णांकercon),
पूर्ण;

/*
 * DAI ops
 */
अटल स्थिर काष्ठा snd_soc_dai_ops cx2072x_dai_ops = अणु
	.set_sysclk = cx2072x_set_dai_sysclk,
	.set_fmt = cx2072x_set_dai_fmt,
	.hw_params = cx2072x_hw_params,
	.set_bclk_ratio = cx2072x_set_dai_bclk_ratio,
पूर्ण;

अटल पूर्णांक cx2072x_dsp_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cx2072x_priv *cx2072x =
		snd_soc_component_get_drvdata(dai->component);

	cx2072x->en_aec_ref = true;
	वापस 0;
पूर्ण

#घोषणा CX2072X_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver soc_codec_cx2072x_dai[] = अणु
	अणु /* playback and capture */
		.name = "cx2072x-hifi",
		.id	= CX2072X_DAI_HIFI,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CX2072X_RATES_DSP,
			.क्रमmats = CX2072X_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CX2072X_RATES_DSP,
			.क्रमmats = CX2072X_FORMATS,
		पूर्ण,
		.ops = &cx2072x_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु /* plabayck only, वापस echo reference to Conexant DSP chip */
		.name = "cx2072x-dsp",
		.id	= CX2072X_DAI_DSP,
		.probe = cx2072x_dsp_dai_probe,
		.playback = अणु
			.stream_name = "DSP Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = CX2072X_RATES_DSP,
			.क्रमmats = CX2072X_FORMATS,
		पूर्ण,
		.ops = &cx2072x_dai_ops,
	पूर्ण,
	अणु /* plabayck only, वापस echo reference through I2S TX */
		.name = "cx2072x-aec",
		.id	= 3,
		.capture = अणु
			.stream_name = "AEC Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = CX2072X_RATES_DSP,
			.क्रमmats = CX2072X_FORMATS,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cx2072x_regmap = अणु
	.reg_bits = 16,
	.val_bits = 32,
	.max_रेजिस्टर = CX2072X_REG_MAX,
	.reg_शेषs = cx2072x_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cx2072x_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.पढ़ोable_reg = cx2072x_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cx2072x_अस्थिर_रेजिस्टर,
	/* Needs custom पढ़ो/ग_लिखो functions क्रम various रेजिस्टर lengths */
	.reg_पढ़ो = cx2072x_reg_पढ़ो,
	.reg_ग_लिखो = cx2072x_reg_ग_लिखो,
पूर्ण;

अटल पूर्णांक __maybe_unused cx2072x_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cx2072x_priv *cx2072x = dev_get_drvdata(dev);

	clk_disable_unprepare(cx2072x->mclk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cx2072x_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cx2072x_priv *cx2072x = dev_get_drvdata(dev);

	वापस clk_prepare_enable(cx2072x->mclk);
पूर्ण

अटल पूर्णांक cx2072x_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cx2072x_priv *cx2072x;
	अचिन्हित पूर्णांक ven_id, rev_id;
	पूर्णांक ret;

	cx2072x = devm_kzalloc(&i2c->dev, माप(काष्ठा cx2072x_priv),
			       GFP_KERNEL);
	अगर (!cx2072x)
		वापस -ENOMEM;

	cx2072x->regmap = devm_regmap_init(&i2c->dev, शून्य, i2c,
					   &cx2072x_regmap);
	अगर (IS_ERR(cx2072x->regmap))
		वापस PTR_ERR(cx2072x->regmap);

	mutex_init(&cx2072x->lock);

	i2c_set_clientdata(i2c, cx2072x);

	cx2072x->dev = &i2c->dev;
	cx2072x->pll_changed = true;
	cx2072x->i2spcm_changed = true;
	cx2072x->bclk_ratio = 0;

	cx2072x->mclk = devm_clk_get(cx2072x->dev, "mclk");
	अगर (IS_ERR(cx2072x->mclk)) अणु
		dev_err(cx2072x->dev, "Failed to get MCLK\n");
		वापस PTR_ERR(cx2072x->mclk);
	पूर्ण

	regmap_पढ़ो(cx2072x->regmap, CX2072X_VENDOR_ID, &ven_id);
	regmap_पढ़ो(cx2072x->regmap, CX2072X_REVISION_ID, &rev_id);

	dev_info(cx2072x->dev, "codec version: %08x,%08x\n", ven_id, rev_id);

	ret = devm_snd_soc_रेजिस्टर_component(cx2072x->dev,
					      &soc_codec_driver_cx2072x,
					      soc_codec_cx2072x_dai,
					      ARRAY_SIZE(soc_codec_cx2072x_dai));
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_use_स्वतःsuspend(cx2072x->dev);
	pm_runसमय_enable(cx2072x->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cx2072x_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pm_runसमय_disable(&i2c->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cx2072x_i2c_id[] = अणु
	अणु "cx20721", 0 पूर्ण,
	अणु "cx20723", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cx2072x_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा acpi_device_id cx2072x_acpi_match[] = अणु
	अणु "14F10720", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cx2072x_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cx2072x_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cx2072x_runसमय_suspend, cx2072x_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा i2c_driver cx2072x_i2c_driver = अणु
	.driver = अणु
		.name = "cx2072x",
		.acpi_match_table = ACPI_PTR(cx2072x_acpi_match),
		.pm = &cx2072x_runसमय_pm,
	पूर्ण,
	.probe = cx2072x_i2c_probe,
	.हटाओ = cx2072x_i2c_हटाओ,
	.id_table = cx2072x_i2c_id,
पूर्ण;

module_i2c_driver(cx2072x_i2c_driver);

MODULE_DESCRIPTION("ASoC cx2072x Codec Driver");
MODULE_AUTHOR("Simon Ho <simon.ho@conexant.com>");
MODULE_LICENSE("GPL");
