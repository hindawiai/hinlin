<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rt700.h -- RT700 ALSA SoC audio driver header
 *
 * Copyright(c) 2019 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT700_H__
#घोषणा __RT700_H__

बाह्य स्थिर काष्ठा dev_pm_ops rt700_runसमय_pm;

काष्ठा  rt700_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	काष्ठा regmap *sdw_regmap;
	काष्ठा sdw_slave *slave;
	क्रमागत sdw_slave_status status;
	काष्ठा sdw_bus_params params;
	bool hw_init;
	bool first_hw_init;
	काष्ठा snd_soc_jack *hs_jack;
	काष्ठा delayed_work jack_detect_work;
	काष्ठा delayed_work jack_btn_check_work;
	पूर्णांक jack_type;
पूर्ण;

काष्ठा sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

/* NID */
#घोषणा RT700_AUDIO_FUNCTION_GROUP			0x01
#घोषणा RT700_DAC_OUT1					0x02
#घोषणा RT700_DAC_OUT2					0x03
#घोषणा RT700_ADC_IN1					0x09
#घोषणा RT700_ADC_IN2					0x08
#घोषणा RT700_DMIC1					0x12
#घोषणा RT700_DMIC2					0x13
#घोषणा RT700_SPK_OUT					0x14
#घोषणा RT700_MIC2					0x19
#घोषणा RT700_LINE1					0x1a
#घोषणा RT700_LINE2					0x1b
#घोषणा RT700_BEEP					0x1d
#घोषणा RT700_SPDIF					0x1e
#घोषणा RT700_VENDOR_REGISTERS				0x20
#घोषणा RT700_HP_OUT					0x21
#घोषणा RT700_MIXER_IN1					0x22
#घोषणा RT700_MIXER_IN2					0x23
#घोषणा RT700_INLINE_CMD				0x55

/* Index (NID:20h) */
#घोषणा RT700_DAC_DC_CALI_CTL1				0x00
#घोषणा RT700_PARA_VERB_CTL				0x1a
#घोषणा RT700_COMBO_JACK_AUTO_CTL1				0x45
#घोषणा RT700_COMBO_JACK_AUTO_CTL2				0x46
#घोषणा RT700_INLINE_CMD_CTL				0x48
#घोषणा RT700_DIGITAL_MISC_CTRL4			0x4a
#घोषणा RT700_VREFOUT_CTL				0x6b
#घोषणा RT700_FSM_CTL				0x6f
#घोषणा RT700_IRQ_FLAG_TABLE1				0x80
#घोषणा RT700_IRQ_FLAG_TABLE2				0x81
#घोषणा RT700_IRQ_FLAG_TABLE3				0x82

/* Verb */
#घोषणा RT700_VERB_SET_CONNECT_SEL			0x3100
#घोषणा RT700_VERB_SET_EAPD_BTLENABLE			0x3c00
#घोषणा RT700_VERB_GET_CONNECT_SEL			0xb100
#घोषणा RT700_VERB_SET_POWER_STATE			0x3500
#घोषणा RT700_VERB_SET_CHANNEL_STREAMID			0x3600
#घोषणा RT700_VERB_SET_PIN_WIDGET_CONTROL		0x3700
#घोषणा RT700_VERB_SET_UNSOLICITED_ENABLE		0x3800
#घोषणा RT700_SET_AMP_GAIN_MUTE_H			0x7300
#घोषणा RT700_SET_AMP_GAIN_MUTE_L			0x8380
#घोषणा RT700_VERB_GET_PIN_SENSE			0xb900

#घोषणा RT700_READ_HDA_3				0x2012
#घोषणा RT700_READ_HDA_2				0x2013
#घोषणा RT700_READ_HDA_1				0x2014
#घोषणा RT700_READ_HDA_0				0x2015
#घोषणा RT700_PRIV_INDEX_W_H				0x7520
#घोषणा RT700_PRIV_INDEX_W_L				0x85a0
#घोषणा RT700_PRIV_DATA_W_H				0x7420
#घोषणा RT700_PRIV_DATA_W_L				0x84a0
#घोषणा RT700_PRIV_INDEX_R_H				0x9d20
#घोषणा RT700_PRIV_INDEX_R_L				0xada0
#घोषणा RT700_PRIV_DATA_R_H				0x9c20
#घोषणा RT700_PRIV_DATA_R_L				0xaca0
#घोषणा RT700_DAC_FORMAT_H				0x7203
#घोषणा RT700_DAC_FORMAT_L				0x8283
#घोषणा RT700_ADC_FORMAT_H				0x7209
#घोषणा RT700_ADC_FORMAT_L				0x8289
#घोषणा RT700_SET_AUDIO_POWER_STATE\
	(RT700_VERB_SET_POWER_STATE | RT700_AUDIO_FUNCTION_GROUP)
#घोषणा RT700_SET_PIN_DMIC1\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_DMIC1)
#घोषणा RT700_SET_PIN_DMIC2\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_DMIC2)
#घोषणा RT700_SET_PIN_SPK\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_SPK_OUT)
#घोषणा RT700_SET_PIN_HP\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_HP_OUT)
#घोषणा RT700_SET_PIN_MIC2\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_MIC2)
#घोषणा RT700_SET_PIN_LINE1\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_LINE1)
#घोषणा RT700_SET_PIN_LINE2\
	(RT700_VERB_SET_PIN_WIDGET_CONTROL | RT700_LINE2)
#घोषणा RT700_SET_MIC2_UNSOLICITED_ENABLE\
	(RT700_VERB_SET_UNSOLICITED_ENABLE | RT700_MIC2)
#घोषणा RT700_SET_HP_UNSOLICITED_ENABLE\
	(RT700_VERB_SET_UNSOLICITED_ENABLE | RT700_HP_OUT)
#घोषणा RT700_SET_INLINE_UNSOLICITED_ENABLE\
	(RT700_VERB_SET_UNSOLICITED_ENABLE | RT700_INLINE_CMD)
#घोषणा RT700_SET_STREAMID_DAC1\
	(RT700_VERB_SET_CHANNEL_STREAMID | RT700_DAC_OUT1)
#घोषणा RT700_SET_STREAMID_DAC2\
	(RT700_VERB_SET_CHANNEL_STREAMID | RT700_DAC_OUT2)
#घोषणा RT700_SET_STREAMID_ADC1\
	(RT700_VERB_SET_CHANNEL_STREAMID | RT700_ADC_IN1)
#घोषणा RT700_SET_STREAMID_ADC2\
	(RT700_VERB_SET_CHANNEL_STREAMID | RT700_ADC_IN2)
#घोषणा RT700_SET_GAIN_DAC1_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_DAC_OUT1)
#घोषणा RT700_SET_GAIN_DAC1_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_DAC_OUT1)
#घोषणा RT700_SET_GAIN_ADC1_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_ADC_IN1)
#घोषणा RT700_SET_GAIN_ADC1_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_ADC_IN1)
#घोषणा RT700_SET_GAIN_ADC2_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_ADC_IN2)
#घोषणा RT700_SET_GAIN_ADC2_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_ADC_IN2)
#घोषणा RT700_SET_GAIN_AMIC_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_MIC2)
#घोषणा RT700_SET_GAIN_AMIC_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_MIC2)
#घोषणा RT700_SET_GAIN_HP_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_HP_OUT)
#घोषणा RT700_SET_GAIN_HP_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_HP_OUT)
#घोषणा RT700_SET_GAIN_SPK_L\
	(RT700_SET_AMP_GAIN_MUTE_L | RT700_SPK_OUT)
#घोषणा RT700_SET_GAIN_SPK_H\
	(RT700_SET_AMP_GAIN_MUTE_H | RT700_SPK_OUT)
#घोषणा RT700_SET_EAPD_SPK\
	(RT700_VERB_SET_EAPD_BTLENABLE | RT700_SPK_OUT)

/* combo jack स्वतः चयन control 2 (0x46)(NID:20h) */
#घोषणा RT700_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#घोषणा RT700_COMBOJACK_AUTO_DET_TRS			(0x1 << 10)
#घोषणा RT700_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#घोषणा RT700_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

#घोषणा RT700_EAPD_HIGH					0x2
#घोषणा RT700_EAPD_LOW					0x0
#घोषणा RT700_MUTE_SFT					7
#घोषणा RT700_सूची_IN_SFT				6
#घोषणा RT700_सूची_OUT_SFT				7

क्रमागत अणु
	RT700_AIF1,
	RT700_AIF2,
	RT700_AIFS,
पूर्ण;

पूर्णांक rt700_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave);
पूर्णांक rt700_init(काष्ठा device *dev, काष्ठा regmap *sdw_regmap,
	       काष्ठा regmap *regmap, काष्ठा sdw_slave *slave);

पूर्णांक rt700_jack_detect(काष्ठा rt700_priv *rt700, bool *hp, bool *mic);
पूर्णांक rt700_घड़ी_config(काष्ठा device *dev);
#पूर्ण_अगर /* __RT700_H__ */
