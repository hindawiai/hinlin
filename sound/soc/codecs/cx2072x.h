<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ALSA SoC CX20721/CX20723 codec driver
 *
 * Copyright:	(C) 2017 Conexant Systems, Inc.
 * Author:	Simon Ho, <Simon.ho@conexant.com>
 */

#अगर_अघोषित __CX2072X_H__
#घोषणा __CX2072X_H__

#घोषणा CX2072X_MCLK_PLL		1
#घोषणा CX2072X_MCLK_EXTERNAL_PLL	1
#घोषणा CX2072X_MCLK_INTERNAL_OSC	2

/*#घोषणा CX2072X_RATES		SNDRV_PCM_RATE_8000_192000*/
#घोषणा CX2072X_RATES_DSP	SNDRV_PCM_RATE_48000

#घोषणा CX2072X_REG_MAX					0x8a3c

#घोषणा CX2072X_VENDOR_ID				0x0200
#घोषणा CX2072X_REVISION_ID				0x0208
#घोषणा CX2072X_CURRENT_BCLK_FREQUENCY			0x00dc
#घोषणा CX2072X_AFG_POWER_STATE				0x0414
#घोषणा CX2072X_UM_RESPONSE				0x0420
#घोषणा CX2072X_GPIO_DATA				0x0454
#घोषणा CX2072X_GPIO_ENABLE				0x0458
#घोषणा CX2072X_GPIO_सूचीECTION				0x045c
#घोषणा CX2072X_GPIO_WAKE				0x0460
#घोषणा CX2072X_GPIO_UM_ENABLE				0x0464
#घोषणा CX2072X_GPIO_STICKY_MASK			0x0468
#घोषणा CX2072X_AFG_FUNCTION_RESET			0x07fc
#घोषणा CX2072X_DAC1_CONVERTER_FORMAT			0x43c8
#घोषणा CX2072X_DAC1_AMP_GAIN_RIGHT			0x41c0
#घोषणा CX2072X_DAC1_AMP_GAIN_LEFT			0x41e0
#घोषणा CX2072X_DAC1_POWER_STATE			0x4014
#घोषणा CX2072X_DAC1_CONVERTER_STREAM_CHANNEL		0x4018
#घोषणा CX2072X_DAC1_EAPD_ENABLE			0x4030
#घोषणा CX2072X_DAC2_CONVERTER_FORMAT			0x47c8
#घोषणा CX2072X_DAC2_AMP_GAIN_RIGHT			0x45c0
#घोषणा CX2072X_DAC2_AMP_GAIN_LEFT			0x45e0
#घोषणा CX2072X_DAC2_POWER_STATE			0x4414
#घोषणा CX2072X_DAC2_CONVERTER_STREAM_CHANNEL		0x4418
#घोषणा CX2072X_ADC1_CONVERTER_FORMAT			0x4fc8
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_0			0x4d80
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_0			0x4da0
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_1			0x4d84
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_1			0x4da4
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_2			0x4d88
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_2			0x4da8
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_3			0x4d8c
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_3			0x4dac
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_4			0x4d90
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_4			0x4db0
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_5			0x4d94
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_5			0x4db4
#घोषणा CX2072X_ADC1_AMP_GAIN_RIGHT_6			0x4d98
#घोषणा CX2072X_ADC1_AMP_GAIN_LEFT_6			0x4db8
#घोषणा CX2072X_ADC1_CONNECTION_SELECT_CONTROL		0x4c04
#घोषणा CX2072X_ADC1_POWER_STATE			0x4c14
#घोषणा CX2072X_ADC1_CONVERTER_STREAM_CHANNEL		0x4c18
#घोषणा CX2072X_ADC2_CONVERTER_FORMAT			0x53c8
#घोषणा CX2072X_ADC2_AMP_GAIN_RIGHT_0			0x5180
#घोषणा CX2072X_ADC2_AMP_GAIN_LEFT_0			0x51a0
#घोषणा CX2072X_ADC2_AMP_GAIN_RIGHT_1			0x5184
#घोषणा CX2072X_ADC2_AMP_GAIN_LEFT_1			0x51a4
#घोषणा CX2072X_ADC2_AMP_GAIN_RIGHT_2			0x5188
#घोषणा CX2072X_ADC2_AMP_GAIN_LEFT_2			0x51a8
#घोषणा CX2072X_ADC2_CONNECTION_SELECT_CONTROL		0x5004
#घोषणा CX2072X_ADC2_POWER_STATE			0x5014
#घोषणा CX2072X_ADC2_CONVERTER_STREAM_CHANNEL		0x5018
#घोषणा CX2072X_PORTA_CONNECTION_SELECT_CTRL		0x5804
#घोषणा CX2072X_PORTA_POWER_STATE			0x5814
#घोषणा CX2072X_PORTA_PIN_CTRL				0x581c
#घोषणा CX2072X_PORTA_UNSOLICITED_RESPONSE		0x5820
#घोषणा CX2072X_PORTA_PIN_SENSE				0x5824
#घोषणा CX2072X_PORTA_EAPD_BTL				0x5830
#घोषणा CX2072X_PORTB_POWER_STATE			0x6014
#घोषणा CX2072X_PORTB_PIN_CTRL				0x601c
#घोषणा CX2072X_PORTB_UNSOLICITED_RESPONSE		0x6020
#घोषणा CX2072X_PORTB_PIN_SENSE				0x6024
#घोषणा CX2072X_PORTB_EAPD_BTL				0x6030
#घोषणा CX2072X_PORTB_GAIN_RIGHT			0x6180
#घोषणा CX2072X_PORTB_GAIN_LEFT				0x61a0
#घोषणा CX2072X_PORTC_POWER_STATE			0x6814
#घोषणा CX2072X_PORTC_PIN_CTRL				0x681c
#घोषणा CX2072X_PORTC_GAIN_RIGHT			0x6980
#घोषणा CX2072X_PORTC_GAIN_LEFT				0x69a0
#घोषणा CX2072X_PORTD_POWER_STATE			0x6414
#घोषणा CX2072X_PORTD_PIN_CTRL				0x641c
#घोषणा CX2072X_PORTD_UNSOLICITED_RESPONSE		0x6420
#घोषणा CX2072X_PORTD_PIN_SENSE				0x6424
#घोषणा CX2072X_PORTD_GAIN_RIGHT			0x6580
#घोषणा CX2072X_PORTD_GAIN_LEFT				0x65a0
#घोषणा CX2072X_PORTE_CONNECTION_SELECT_CTRL		0x7404
#घोषणा CX2072X_PORTE_POWER_STATE			0x7414
#घोषणा CX2072X_PORTE_PIN_CTRL				0x741c
#घोषणा CX2072X_PORTE_UNSOLICITED_RESPONSE		0x7420
#घोषणा CX2072X_PORTE_PIN_SENSE				0x7424
#घोषणा CX2072X_PORTE_EAPD_BTL				0x7430
#घोषणा CX2072X_PORTE_GAIN_RIGHT			0x7580
#घोषणा CX2072X_PORTE_GAIN_LEFT				0x75a0
#घोषणा CX2072X_PORTF_POWER_STATE			0x7814
#घोषणा CX2072X_PORTF_PIN_CTRL				0x781c
#घोषणा CX2072X_PORTF_UNSOLICITED_RESPONSE		0x7820
#घोषणा CX2072X_PORTF_PIN_SENSE				0x7824
#घोषणा CX2072X_PORTF_GAIN_RIGHT			0x7980
#घोषणा CX2072X_PORTF_GAIN_LEFT				0x79a0
#घोषणा CX2072X_PORTG_POWER_STATE			0x5c14
#घोषणा CX2072X_PORTG_PIN_CTRL				0x5c1c
#घोषणा CX2072X_PORTG_CONNECTION_SELECT_CTRL		0x5c04
#घोषणा CX2072X_PORTG_EAPD_BTL				0x5c30
#घोषणा CX2072X_PORTM_POWER_STATE			0x8814
#घोषणा CX2072X_PORTM_PIN_CTRL				0x881c
#घोषणा CX2072X_PORTM_CONNECTION_SELECT_CTRL		0x8804
#घोषणा CX2072X_PORTM_EAPD_BTL				0x8830
#घोषणा CX2072X_MIXER_POWER_STATE			0x5414
#घोषणा CX2072X_MIXER_GAIN_RIGHT_0			0x5580
#घोषणा CX2072X_MIXER_GAIN_LEFT_0			0x55a0
#घोषणा CX2072X_MIXER_GAIN_RIGHT_1			0x5584
#घोषणा CX2072X_MIXER_GAIN_LEFT_1			0x55a4
#घोषणा CX2072X_EQ_ENABLE_BYPASS			0x6d00
#घोषणा CX2072X_EQ_B0_COEFF				0x6d02
#घोषणा CX2072X_EQ_B1_COEFF				0x6d04
#घोषणा CX2072X_EQ_B2_COEFF				0x6d06
#घोषणा CX2072X_EQ_A1_COEFF				0x6d08
#घोषणा CX2072X_EQ_A2_COEFF				0x6d0a
#घोषणा CX2072X_EQ_G_COEFF				0x6d0c
#घोषणा CX2072X_EQ_BAND					0x6d0d
#घोषणा CX2072X_SPKR_DRC_ENABLE_STEP			0x6d10
#घोषणा CX2072X_SPKR_DRC_CONTROL			0x6d14
#घोषणा CX2072X_SPKR_DRC_TEST				0x6d18
#घोषणा CX2072X_DIGITAL_BIOS_TEST0			0x6d80
#घोषणा CX2072X_DIGITAL_BIOS_TEST2			0x6d84
#घोषणा CX2072X_I2SPCM_CONTROL1				0x6e00
#घोषणा CX2072X_I2SPCM_CONTROL2				0x6e04
#घोषणा CX2072X_I2SPCM_CONTROL3				0x6e08
#घोषणा CX2072X_I2SPCM_CONTROL4				0x6e0c
#घोषणा CX2072X_I2SPCM_CONTROL5				0x6e10
#घोषणा CX2072X_I2SPCM_CONTROL6				0x6e18
#घोषणा CX2072X_UM_INTERRUPT_CRTL_E			0x6e14
#घोषणा CX2072X_CODEC_TEST2				0x7108
#घोषणा CX2072X_CODEC_TEST9				0x7124
#घोषणा CX2072X_CODEC_TESTXX				0x7290
#घोषणा CX2072X_CODEC_TEST20				0x7310
#घोषणा CX2072X_CODEC_TEST24				0x731c
#घोषणा CX2072X_CODEC_TEST26				0x7328
#घोषणा CX2072X_ANALOG_TEST3				0x718c
#घोषणा CX2072X_ANALOG_TEST4				0x7190
#घोषणा CX2072X_ANALOG_TEST5				0x7194
#घोषणा CX2072X_ANALOG_TEST6				0x7198
#घोषणा CX2072X_ANALOG_TEST7				0x719c
#घोषणा CX2072X_ANALOG_TEST8				0x71a0
#घोषणा CX2072X_ANALOG_TEST9				0x71a4
#घोषणा CX2072X_ANALOG_TEST10				0x71a8
#घोषणा CX2072X_ANALOG_TEST11				0x71ac
#घोषणा CX2072X_ANALOG_TEST12				0x71b0
#घोषणा CX2072X_ANALOG_TEST13				0x71b4
#घोषणा CX2072X_DIGITAL_TEST0				0x7200
#घोषणा CX2072X_DIGITAL_TEST1				0x7204
#घोषणा CX2072X_DIGITAL_TEST11				0x722c
#घोषणा CX2072X_DIGITAL_TEST12				0x7230
#घोषणा CX2072X_DIGITAL_TEST15				0x723c
#घोषणा CX2072X_DIGITAL_TEST16				0x7080
#घोषणा CX2072X_DIGITAL_TEST17				0x7084
#घोषणा CX2072X_DIGITAL_TEST18				0x7088
#घोषणा CX2072X_DIGITAL_TEST19				0x708c
#घोषणा CX2072X_DIGITAL_TEST20				0x7090

/* not used in the current code, क्रम future extensions (अगर any) */
#घोषणा CX2072X_MAX_EQ_BAND		7
#घोषणा CX2072X_MAX_EQ_COEFF		11
#घोषणा CX2072X_MAX_DRC_REGS		9
#घोषणा CX2072X_MIC_EQ_COEFF		10
#घोषणा CX2072X_PLBK_EQ_BAND_NUM	7
#घोषणा CX2072X_PLBK_EQ_COEF_LEN	11
#घोषणा CX2072X_PLBK_DRC_PARM_LEN	9
#घोषणा CX2072X_CLASSD_AMP_LEN		6

/* DAI पूर्णांकerfae type */
#घोषणा CX2072X_DAI_HIFI	1
#घोषणा CX2072X_DAI_DSP		2
#घोषणा CX2072X_DAI_DSP_PWM	3 /* 4 ch, including mic and AEC */

क्रमागत cx2072x_reg_sample_size अणु
	CX2072X_SAMPLE_SIZE_8_BITS = 0,
	CX2072X_SAMPLE_SIZE_16_BITS = 1,
	CX2072X_SAMPLE_SIZE_24_BITS = 2,
	CX2072X_SAMPLE_SIZE_RESERVED = 3,
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg1 अणु
	काष्ठा अणु
		u32 rx_data_one_line:1;
		u32 rx_ws_pol:1;
		u32 rx_ws_wid:7;
		u32 rx_frm_len:5;
		u32 rx_sa_size:2;
		u32 tx_data_one_line:1;
		u32 tx_ws_pol:1;
		u32 tx_ws_wid:7;
		u32 tx_frm_len:5;
		u32 tx_sa_size:2;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg2 अणु
	काष्ठा अणु
		u32 tx_en_ch1:1;
		u32 tx_en_ch2:1;
		u32 tx_en_ch3:1;
		u32 tx_en_ch4:1;
		u32 tx_en_ch5:1;
		u32 tx_en_ch6:1;
		u32 tx_slot_1:5;
		u32 tx_slot_2:5;
		u32 tx_slot_3:5;
		u32 tx_slot_4:5;
		u32 res:1;
		u32 tx_data_neg_bclk:1;
		u32 tx_master:1;
		u32 tx_tri_n:1;
		u32 tx_endian_sel:1;
		u32 tx_dstart_dly:1;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg3 अणु
	काष्ठा अणु
		u32 rx_en_ch1:1;
		u32 rx_en_ch2:1;
		u32 rx_en_ch3:1;
		u32 rx_en_ch4:1;
		u32 rx_en_ch5:1;
		u32 rx_en_ch6:1;
		u32 rx_slot_1:5;
		u32 rx_slot_2:5;
		u32 rx_slot_3:5;
		u32 rx_slot_4:5;
		u32 res:1;
		u32 rx_data_neg_bclk:1;
		u32 rx_master:1;
		u32 rx_tri_n:1;
		u32 rx_endian_sel:1;
		u32 rx_dstart_dly:1;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg4 अणु
	काष्ठा अणु
		u32 rx_mute:1;
		u32 tx_mute:1;
		u32 reserved:1;
		u32 dac_34_independent:1;
		u32 dac_bclk_lrck_share:1;
		u32 bclk_lrck_share_en:1;
		u32 reserved2:2;
		u32 rx_last_dac_ch_en:1;
		u32 rx_last_dac_ch:3;
		u32 tx_last_adc_ch_en:1;
		u32 tx_last_adc_ch:3;
		u32 rx_slot_5:5;
		u32 rx_slot_6:5;
		u32 reserved3:6;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg5 अणु
	काष्ठा अणु
		u32 tx_slot_5:5;
		u32 reserved:3;
		u32 tx_slot_6:5;
		u32 reserved2:3;
		u32 reserved3:8;
		u32 i2s_pcm_clk_भाग:7;
		u32 i2s_pcm_clk_भाग_chan_en:1;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_i2spcm_ctrl_reg6 अणु
	काष्ठा अणु
		u32 reserved:5;
		u32 rx_छोड़ो_cycles:3;
		u32 rx_छोड़ो_start_pos:8;
		u32 reserved2:5;
		u32 tx_छोड़ो_cycles:3;
		u32 tx_छोड़ो_start_pos:8;
	पूर्ण r;
	u32 ulval;
पूर्ण;

जोड़ cx2072x_reg_digital_bios_test2 अणु
	काष्ठा अणु
		u32 pull_करोwn_eapd:2;
		u32 input_en_eapd_pad:1;
		u32 push_pull_mode:1;
		u32 eapd_pad_output_driver:2;
		u32 pll_source:1;
		u32 i2s_bclk_en:1;
		u32 i2s_bclk_invert:1;
		u32 pll_ref_घड़ी:1;
		u32 class_d_shield_clk:1;
		u32 audio_pll_bypass_mode:1;
		u32 reserved:4;
	पूर्ण r;
	u32 ulval;
पूर्ण;

#पूर्ण_अगर /* __CX2072X_H__ */
