<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rt711.h -- RT711 ALSA SoC audio driver header
 *
 * Copyright(c) 2019 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT711_H__
#घोषणा __RT711_H__

बाह्य स्थिर काष्ठा dev_pm_ops rt711_runसमय_pm;

काष्ठा  rt711_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap *sdw_regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा sdw_slave *slave;
	क्रमागत sdw_slave_status status;
	काष्ठा sdw_bus_params params;
	bool hw_init;
	bool first_hw_init;
	काष्ठा snd_soc_jack *hs_jack;
	काष्ठा delayed_work jack_detect_work;
	काष्ठा delayed_work jack_btn_check_work;
	काष्ठा work_काष्ठा calibration_work;
	काष्ठा mutex calibrate_mutex; /* क्रम headset calibration */
	पूर्णांक jack_type, jd_src;
पूर्ण;

काष्ठा sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

/* NID */
#घोषणा RT711_AUDIO_FUNCTION_GROUP			0x01
#घोषणा RT711_DAC_OUT2					0x03
#घोषणा RT711_ADC_IN1					0x09
#घोषणा RT711_ADC_IN2					0x08
#घोषणा RT711_DMIC1					0x12
#घोषणा RT711_DMIC2					0x13
#घोषणा RT711_MIC2					0x19
#घोषणा RT711_LINE1					0x1a
#घोषणा RT711_LINE2					0x1b
#घोषणा RT711_BEEP					0x1d
#घोषणा RT711_VENDOR_REG				0x20
#घोषणा RT711_HP_OUT					0x21
#घोषणा RT711_MIXER_IN1					0x22
#घोषणा RT711_MIXER_IN2					0x23
#घोषणा RT711_INLINE_CMD				0x55
#घोषणा RT711_VENDOR_CALI				0x58
#घोषणा RT711_VENDOR_IMS_DRE			0x5b

/* Index (NID:20h) */
#घोषणा RT711_DAC_DC_CALI_CTL1				0x00
#घोषणा RT711_JD_CTL2				0x09
#घोषणा RT711_CC_DET1				0x11
#घोषणा RT711_PARA_VERB_CTL				0x1a
#घोषणा RT711_COMBO_JACK_AUTO_CTL1				0x45
#घोषणा RT711_COMBO_JACK_AUTO_CTL2				0x46
#घोषणा RT711_INLINE_CMD_CTL				0x48
#घोषणा RT711_DIGITAL_MISC_CTRL4			0x4a
#घोषणा RT711_VREFOUT_CTL				0x6b
#घोषणा RT711_FSM_CTL				0x6f
#घोषणा RT711_IRQ_FLAG_TABLE1				0x80
#घोषणा RT711_IRQ_FLAG_TABLE2				0x81
#घोषणा RT711_IRQ_FLAG_TABLE3				0x82
#घोषणा RT711_TX_RX_MUX_CTL				0x91

/* Index (NID:5bh) */
#घोषणा RT711_IMS_DIGITAL_CTL1				0x00
#घोषणा RT711_HP_IMS_RESULT_L				0x20
#घोषणा RT711_HP_IMS_RESULT_R				0x21

/* Verb */
#घोषणा RT711_VERB_SET_CONNECT_SEL			0x3100
#घोषणा RT711_VERB_SET_EAPD_BTLENABLE			0x3c00
#घोषणा RT711_VERB_GET_CONNECT_SEL			0xb100
#घोषणा RT711_VERB_SET_POWER_STATE			0x3500
#घोषणा RT711_VERB_SET_CHANNEL_STREAMID			0x3600
#घोषणा RT711_VERB_SET_PIN_WIDGET_CONTROL		0x3700
#घोषणा RT711_VERB_SET_UNSOLICITED_ENABLE		0x3800
#घोषणा RT711_SET_AMP_GAIN_MUTE_H			0x7300
#घोषणा RT711_SET_AMP_GAIN_MUTE_L			0x8380
#घोषणा RT711_VERB_GET_POWER_STATE			0xb500
#घोषणा RT711_VERB_GET_CHANNEL_STREAMID			0xb600
#घोषणा RT711_VERB_GET_PIN_SENSE			0xb900
#घोषणा RT711_FUNC_RESET			0xff01

#घोषणा RT711_READ_HDA_3				0x2012
#घोषणा RT711_READ_HDA_2				0x2013
#घोषणा RT711_READ_HDA_1				0x2014
#घोषणा RT711_READ_HDA_0				0x2015
#घोषणा RT711_PRIV_INDEX_W_H				0x7500
#घोषणा RT711_PRIV_INDEX_W_L				0x8580
#घोषणा RT711_PRIV_DATA_W_H				0x7400
#घोषणा RT711_PRIV_DATA_W_L				0x8480
#घोषणा RT711_PRIV_INDEX_R_H				0x9d00
#घोषणा RT711_PRIV_INDEX_R_L				0xad80
#घोषणा RT711_PRIV_DATA_R_H				0x9c00
#घोषणा RT711_PRIV_DATA_R_L				0xac80
#घोषणा RT711_DAC_FORMAT_H				0x7203
#घोषणा RT711_DAC_FORMAT_L				0x8283
#घोषणा RT711_ADC1_FORMAT_H				0x7209
#घोषणा RT711_ADC1_FORMAT_L				0x8289
#घोषणा RT711_ADC2_FORMAT_H				0x7208
#घोषणा RT711_ADC2_FORMAT_L				0x8288

#घोषणा RT711_SET_AUDIO_POWER_STATE\
	(RT711_VERB_SET_POWER_STATE | RT711_AUDIO_FUNCTION_GROUP)
#घोषणा RT711_GET_AUDIO_POWER_STATE\
		(RT711_VERB_GET_POWER_STATE | RT711_AUDIO_FUNCTION_GROUP)
#घोषणा RT711_SET_PIN_DMIC1\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_DMIC1)
#घोषणा RT711_SET_PIN_DMIC2\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_DMIC2)
#घोषणा RT711_SET_PIN_HP\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_HP_OUT)
#घोषणा RT711_SET_PIN_MIC2\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_MIC2)
#घोषणा RT711_SET_PIN_LINE1\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_LINE1)
#घोषणा RT711_SET_PIN_LINE2\
	(RT711_VERB_SET_PIN_WIDGET_CONTROL | RT711_LINE2)
#घोषणा RT711_SET_MIC2_UNSOLICITED_ENABLE\
	(RT711_VERB_SET_UNSOLICITED_ENABLE | RT711_MIC2)
#घोषणा RT711_SET_HP_UNSOLICITED_ENABLE\
	(RT711_VERB_SET_UNSOLICITED_ENABLE | RT711_HP_OUT)
#घोषणा RT711_SET_INLINE_UNSOLICITED_ENABLE\
	(RT711_VERB_SET_UNSOLICITED_ENABLE | RT711_INLINE_CMD)
#घोषणा RT711_SET_STREAMID_DAC2\
	(RT711_VERB_SET_CHANNEL_STREAMID | RT711_DAC_OUT2)
#घोषणा RT711_SET_STREAMID_ADC1\
	(RT711_VERB_SET_CHANNEL_STREAMID | RT711_ADC_IN1)
#घोषणा RT711_SET_STREAMID_ADC2\
	(RT711_VERB_SET_CHANNEL_STREAMID | RT711_ADC_IN2)
#घोषणा RT711_GET_STREAMID_DAC2\
	(RT711_VERB_GET_CHANNEL_STREAMID | RT711_DAC_OUT2)
#घोषणा RT711_GET_STREAMID_ADC1\
	(RT711_VERB_GET_CHANNEL_STREAMID | RT711_ADC_IN1)
#घोषणा RT711_GET_STREAMID_ADC2\
	(RT711_VERB_GET_CHANNEL_STREAMID | RT711_ADC_IN2)
#घोषणा RT711_SET_GAIN_DAC2_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_DAC_OUT2)
#घोषणा RT711_SET_GAIN_DAC2_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_DAC_OUT2)
#घोषणा RT711_SET_GAIN_ADC1_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_ADC_IN1)
#घोषणा RT711_SET_GAIN_ADC1_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_ADC_IN1)
#घोषणा RT711_SET_GAIN_ADC2_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_ADC_IN2)
#घोषणा RT711_SET_GAIN_ADC2_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_ADC_IN2)
#घोषणा RT711_SET_GAIN_AMIC_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_MIC2)
#घोषणा RT711_SET_GAIN_AMIC_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_MIC2)
#घोषणा RT711_SET_GAIN_DMIC1_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_DMIC1)
#घोषणा RT711_SET_GAIN_DMIC1_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_DMIC1)
#घोषणा RT711_SET_GAIN_DMIC2_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_DMIC2)
#घोषणा RT711_SET_GAIN_DMIC2_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_DMIC2)
#घोषणा RT711_SET_GAIN_HP_L\
	(RT711_SET_AMP_GAIN_MUTE_L | RT711_HP_OUT)
#घोषणा RT711_SET_GAIN_HP_H\
	(RT711_SET_AMP_GAIN_MUTE_H | RT711_HP_OUT)

/* DAC DC offset calibration control-1 (0x00)(NID:20h) */
#घोषणा RT711_DAC_DC_CALI_TRIGGER (0x1 << 15)

/* jack detect control 2 (0x09)(NID:20h) */
#घोषणा RT711_JD2_2PORT_200K_DECODE_HP (0x1 << 13)
#घोषणा RT711_HP_JD_SEL_JD1 (0x0 << 1)
#घोषणा RT711_HP_JD_SEL_JD2 (0x1 << 1)

/* CC DET1 (0x11)(NID:20h) */
#घोषणा RT711_HP_JD_FINAL_RESULT_CTL_JD12 (0x1 << 10)
#घोषणा RT711_HP_JD_FINAL_RESULT_CTL_CCDET (0x0 << 10)

/* Parameter & Verb control (0x1a)(NID:20h) */
#घोषणा RT711_HIDDEN_REG_SW_RESET (0x1 << 14)

/* combo jack स्वतः चयन control 2 (0x46)(NID:20h) */
#घोषणा RT711_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#घोषणा RT711_COMBOJACK_AUTO_DET_TRS			(0x1 << 10)
#घोषणा RT711_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#घोषणा RT711_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

/* FSM control (0x6f)(NID:20h) */
#घोषणा RT711_CALI_CTL			(0x0 << 0)
#घोषणा RT711_COMBOJACK_CTL			(0x1 << 0)
#घोषणा RT711_IMS_CTL			(0x2 << 0)
#घोषणा RT711_DEPOP_CTL			(0x3 << 0)

/* Impedance Sense Digital Control 1 (0x00)(NID:5bh) */
#घोषणा RT711_TRIGGER_IMS			(0x1 << 15)
#घोषणा RT711_IMS_EN			(0x1 << 6)

#घोषणा RT711_EAPD_HIGH					0x2
#घोषणा RT711_EAPD_LOW					0x0
#घोषणा RT711_MUTE_SFT					7
/* set input/output mapping to payload[14][15] separately */
#घोषणा RT711_सूची_IN_SFT				6
#घोषणा RT711_सूची_OUT_SFT				7

क्रमागत अणु
	RT711_AIF1,
	RT711_AIF2,
	RT711_AIFS,
पूर्ण;

क्रमागत rt711_jd_src अणु
	RT711_JD_शून्य,
	RT711_JD1,
	RT711_JD2
पूर्ण;

पूर्णांक rt711_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave);
पूर्णांक rt711_init(काष्ठा device *dev, काष्ठा regmap *sdw_regmap,
	       काष्ठा regmap *regmap, काष्ठा sdw_slave *slave);

पूर्णांक rt711_jack_detect(काष्ठा rt711_priv *rt711, bool *hp, bool *mic);
पूर्णांक rt711_घड़ी_config(काष्ठा device *dev);
#पूर्ण_अगर /* __RT711_H__ */
