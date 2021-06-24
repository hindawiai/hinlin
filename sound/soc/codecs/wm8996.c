<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8996.c - WM8996 audio codec पूर्णांकerface
 *
 * Copyright 2011-2 Wolfson Microelectronics PLC.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gcd.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <trace/events/asoc.h>

#समावेश <sound/wm8996.h>
#समावेश "wm8996.h"

#घोषणा WM8996_AIFS 2

#घोषणा HPOUT1L 1
#घोषणा HPOUT1R 2
#घोषणा HPOUT2L 4
#घोषणा HPOUT2R 8

#घोषणा WM8996_NUM_SUPPLIES 3
अटल स्थिर अक्षर *wm8996_supply_names[WM8996_NUM_SUPPLIES] = अणु
	"DBVDD",
	"AVDD1",
	"AVDD2",
पूर्ण;

काष्ठा wm8996_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;

	पूर्णांक lकरो1ena;

	पूर्णांक sysclk;
	पूर्णांक sysclk_src;

	पूर्णांक fll_src;
	पूर्णांक fll_fref;
	पूर्णांक fll_fout;

	काष्ठा completion fll_lock;

	u16 dcs_pending;
	काष्ठा completion dcs_करोne;

	u16 hpout_ena;
	u16 hpout_pending;

	काष्ठा regulator_bulk_data supplies[WM8996_NUM_SUPPLIES];
	काष्ठा notअगरier_block disable_nb[WM8996_NUM_SUPPLIES];
	पूर्णांक bg_ena;

	काष्ठा wm8996_pdata pdata;

	पूर्णांक rx_rate[WM8996_AIFS];
	पूर्णांक bclk_rate[WM8996_AIFS];

	/* Platक्रमm dependant ReTune mobile configuration */
	पूर्णांक num_retune_mobile_texts;
	स्थिर अक्षर **retune_mobile_texts;
	पूर्णांक retune_mobile_cfg[2];
	काष्ठा soc_क्रमागत retune_mobile_क्रमागत;

	काष्ठा snd_soc_jack *jack;
	bool detecting;
	bool jack_mic;
	पूर्णांक jack_flips;
	wm8996_polarity_fn polarity_cb;

#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर
पूर्ण;

/* We can't use the same notअगरier block क्रम more than one supply and
 * there's no way I can see to get from a callback to the caller
 * except container_of().
 */
#घोषणा WM8996_REGULATOR_EVENT(n) \
अटल पूर्णांक wm8996_regulator_event_##n(काष्ठा notअगरier_block *nb, \
				    अचिन्हित दीर्घ event, व्योम *data)	\
अणु \
	काष्ठा wm8996_priv *wm8996 = container_of(nb, काष्ठा wm8996_priv, \
						  disable_nb[n]); \
	अगर (event & REGULATOR_EVENT_DISABLE) अणु \
		regcache_mark_dirty(wm8996->regmap);	\
	पूर्ण \
	वापस 0; \
पूर्ण

WM8996_REGULATOR_EVENT(0)
WM8996_REGULATOR_EVENT(1)
WM8996_REGULATOR_EVENT(2)

अटल स्थिर काष्ठा reg_शेष wm8996_reg[] = अणु
	अणु WM8996_POWER_MANAGEMENT_1, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_2, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_3, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_4, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_5, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_6, 0x0 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_7, 0x10 पूर्ण,
	अणु WM8996_POWER_MANAGEMENT_8, 0x0 पूर्ण,
	अणु WM8996_LEFT_LINE_INPUT_VOLUME, 0x0 पूर्ण,
	अणु WM8996_RIGHT_LINE_INPUT_VOLUME, 0x0 पूर्ण,
	अणु WM8996_LINE_INPUT_CONTROL, 0x0 पूर्ण,
	अणु WM8996_DAC1_HPOUT1_VOLUME, 0x88 पूर्ण,
	अणु WM8996_DAC2_HPOUT2_VOLUME, 0x88 पूर्ण,
	अणु WM8996_DAC1_LEFT_VOLUME, 0x2c0 पूर्ण,
	अणु WM8996_DAC1_RIGHT_VOLUME, 0x2c0 पूर्ण,
	अणु WM8996_DAC2_LEFT_VOLUME, 0x2c0 पूर्ण,
	अणु WM8996_DAC2_RIGHT_VOLUME, 0x2c0 पूर्ण,
	अणु WM8996_OUTPUT1_LEFT_VOLUME, 0x80 पूर्ण,
	अणु WM8996_OUTPUT1_RIGHT_VOLUME, 0x80 पूर्ण,
	अणु WM8996_OUTPUT2_LEFT_VOLUME, 0x80 पूर्ण,
	अणु WM8996_OUTPUT2_RIGHT_VOLUME, 0x80 पूर्ण,
	अणु WM8996_MICBIAS_1, 0x39 पूर्ण,
	अणु WM8996_MICBIAS_2, 0x39 पूर्ण,
	अणु WM8996_LDO_1, 0x3 पूर्ण,
	अणु WM8996_LDO_2, 0x13 पूर्ण,
	अणु WM8996_ACCESSORY_DETECT_MODE_1, 0x4 पूर्ण,
	अणु WM8996_ACCESSORY_DETECT_MODE_2, 0x0 पूर्ण,
	अणु WM8996_HEADPHONE_DETECT_1, 0x20 पूर्ण,
	अणु WM8996_HEADPHONE_DETECT_2, 0x0 पूर्ण,
	अणु WM8996_MIC_DETECT_1, 0x7600 पूर्ण,
	अणु WM8996_MIC_DETECT_2, 0xbf पूर्ण,
	अणु WM8996_CHARGE_PUMP_1, 0x1f25 पूर्ण,
	अणु WM8996_CHARGE_PUMP_2, 0xab19 पूर्ण,
	अणु WM8996_DC_SERVO_1, 0x0 पूर्ण,
	अणु WM8996_DC_SERVO_3, 0x0 पूर्ण,
	अणु WM8996_DC_SERVO_5, 0x2a2a पूर्ण,
	अणु WM8996_DC_SERVO_6, 0x0 पूर्ण,
	अणु WM8996_DC_SERVO_7, 0x0 पूर्ण,
	अणु WM8996_ANALOGUE_HP_1, 0x0 पूर्ण,
	अणु WM8996_ANALOGUE_HP_2, 0x0 पूर्ण,
	अणु WM8996_CONTROL_INTERFACE_1, 0x8004 पूर्ण,
	अणु WM8996_WRITE_SEQUENCER_CTRL_1, 0x0 पूर्ण,
	अणु WM8996_WRITE_SEQUENCER_CTRL_2, 0x0 पूर्ण,
	अणु WM8996_AIF_CLOCKING_1, 0x0 पूर्ण,
	अणु WM8996_AIF_CLOCKING_2, 0x0 पूर्ण,
	अणु WM8996_CLOCKING_1, 0x10 पूर्ण,
	अणु WM8996_CLOCKING_2, 0x0 पूर्ण,
	अणु WM8996_AIF_RATE, 0x83 पूर्ण,
	अणु WM8996_FLL_CONTROL_1, 0x0 पूर्ण,
	अणु WM8996_FLL_CONTROL_2, 0x0 पूर्ण,
	अणु WM8996_FLL_CONTROL_3, 0x0 पूर्ण,
	अणु WM8996_FLL_CONTROL_4, 0x5dc0 पूर्ण,
	अणु WM8996_FLL_CONTROL_5, 0xc84 पूर्ण,
	अणु WM8996_FLL_EFS_1, 0x0 पूर्ण,
	अणु WM8996_FLL_EFS_2, 0x2 पूर्ण,
	अणु WM8996_AIF1_CONTROL, 0x0 पूर्ण,
	अणु WM8996_AIF1_BCLK, 0x0 पूर्ण,
	अणु WM8996_AIF1_TX_LRCLK_1, 0x80 पूर्ण,
	अणु WM8996_AIF1_TX_LRCLK_2, 0x8 पूर्ण,
	अणु WM8996_AIF1_RX_LRCLK_1, 0x80 पूर्ण,
	अणु WM8996_AIF1_RX_LRCLK_2, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_DATA_CONFIGURATION_1, 0x1818 पूर्ण,
	अणु WM8996_AIF1TX_DATA_CONFIGURATION_2, 0 पूर्ण,
	अणु WM8996_AIF1RX_DATA_CONFIGURATION, 0x1818 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_0_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_1_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_2_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_3_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_4_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_CHANNEL_5_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_0_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_1_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_2_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_3_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_4_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_CHANNEL_5_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1RX_MONO_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF1TX_TEST, 0x7 पूर्ण,
	अणु WM8996_AIF2_CONTROL, 0x0 पूर्ण,
	अणु WM8996_AIF2_BCLK, 0x0 पूर्ण,
	अणु WM8996_AIF2_TX_LRCLK_1, 0x80 पूर्ण,
	अणु WM8996_AIF2_TX_LRCLK_2, 0x8 पूर्ण,
	अणु WM8996_AIF2_RX_LRCLK_1, 0x80 पूर्ण,
	अणु WM8996_AIF2_RX_LRCLK_2, 0x0 पूर्ण,
	अणु WM8996_AIF2TX_DATA_CONFIGURATION_1, 0x1818 पूर्ण,
	अणु WM8996_AIF2RX_DATA_CONFIGURATION, 0x1818 पूर्ण,
	अणु WM8996_AIF2RX_DATA_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2TX_CHANNEL_0_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2TX_CHANNEL_1_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2RX_CHANNEL_0_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2RX_CHANNEL_1_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2RX_MONO_CONFIGURATION, 0x0 पूर्ण,
	अणु WM8996_AIF2TX_TEST, 0x1 पूर्ण,
	अणु WM8996_DSP1_TX_LEFT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP1_TX_RIGHT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP1_RX_LEFT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP1_RX_RIGHT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP1_TX_FILTERS, 0x2000 पूर्ण,
	अणु WM8996_DSP1_RX_FILTERS_1, 0x200 पूर्ण,
	अणु WM8996_DSP1_RX_FILTERS_2, 0x10 पूर्ण,
	अणु WM8996_DSP1_DRC_1, 0x98 पूर्ण,
	अणु WM8996_DSP1_DRC_2, 0x845 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_GAINS_1, 0x6318 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_GAINS_2, 0x6300 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_1_A, 0xfca पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_1_B, 0x400 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_1_PG, 0xd8 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_2_A, 0x1eb5 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_2_B, 0xf145 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_2_C, 0xb75 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_2_PG, 0x1c5 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_3_A, 0x1c58 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_3_B, 0xf373 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_3_C, 0xa54 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_3_PG, 0x558 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_4_A, 0x168e पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_4_B, 0xf829 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_4_C, 0x7ad पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_4_PG, 0x1103 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_5_A, 0x564 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_5_B, 0x559 पूर्ण,
	अणु WM8996_DSP1_RX_EQ_BAND_5_PG, 0x4000 पूर्ण,
	अणु WM8996_DSP2_TX_LEFT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP2_TX_RIGHT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP2_RX_LEFT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP2_RX_RIGHT_VOLUME, 0xc0 पूर्ण,
	अणु WM8996_DSP2_TX_FILTERS, 0x2000 पूर्ण,
	अणु WM8996_DSP2_RX_FILTERS_1, 0x200 पूर्ण,
	अणु WM8996_DSP2_RX_FILTERS_2, 0x10 पूर्ण,
	अणु WM8996_DSP2_DRC_1, 0x98 पूर्ण,
	अणु WM8996_DSP2_DRC_2, 0x845 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_GAINS_1, 0x6318 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_GAINS_2, 0x6300 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_1_A, 0xfca पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_1_B, 0x400 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_1_PG, 0xd8 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_2_A, 0x1eb5 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_2_B, 0xf145 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_2_C, 0xb75 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_2_PG, 0x1c5 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_3_A, 0x1c58 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_3_B, 0xf373 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_3_C, 0xa54 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_3_PG, 0x558 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_4_A, 0x168e पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_4_B, 0xf829 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_4_C, 0x7ad पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_4_PG, 0x1103 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_5_A, 0x564 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_5_B, 0x559 पूर्ण,
	अणु WM8996_DSP2_RX_EQ_BAND_5_PG, 0x4000 पूर्ण,
	अणु WM8996_DAC1_MIXER_VOLUMES, 0x0 पूर्ण,
	अणु WM8996_DAC1_LEFT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DAC1_RIGHT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DAC2_MIXER_VOLUMES, 0x0 पूर्ण,
	अणु WM8996_DAC2_LEFT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DAC2_RIGHT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DSP1_TX_LEFT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DSP1_TX_RIGHT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DSP2_TX_LEFT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DSP2_TX_RIGHT_MIXER_ROUTING, 0x0 पूर्ण,
	अणु WM8996_DSP_TX_MIXER_SELECT, 0x0 पूर्ण,
	अणु WM8996_DAC_SOFTMUTE, 0x0 पूर्ण,
	अणु WM8996_OVERSAMPLING, 0xd पूर्ण,
	अणु WM8996_SIDETONE, 0x1040 पूर्ण,
	अणु WM8996_GPIO_1, 0xa101 पूर्ण,
	अणु WM8996_GPIO_2, 0xa101 पूर्ण,
	अणु WM8996_GPIO_3, 0xa101 पूर्ण,
	अणु WM8996_GPIO_4, 0xa101 पूर्ण,
	अणु WM8996_GPIO_5, 0xa101 पूर्ण,
	अणु WM8996_PULL_CONTROL_1, 0x0 पूर्ण,
	अणु WM8996_PULL_CONTROL_2, 0x140 पूर्ण,
	अणु WM8996_INTERRUPT_STATUS_1_MASK, 0x1f पूर्ण,
	अणु WM8996_INTERRUPT_STATUS_2_MASK, 0x1ecf पूर्ण,
	अणु WM8996_LEFT_PDM_SPEAKER, 0x0 पूर्ण,
	अणु WM8996_RIGHT_PDM_SPEAKER, 0x1 पूर्ण,
	अणु WM8996_PDM_SPEAKER_MUTE_SEQUENCE, 0x69 पूर्ण,
	अणु WM8996_PDM_SPEAKER_VOLUME, 0x66 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -3600, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_digital_tlv, -1200, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -900, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spk_tlv, -900, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(threedstereo_tlv, -1600, 183, 1);

अटल स्थिर अक्षर *sidetone_hpf_text[] = अणु
	"2.9kHz", "1.5kHz", "735Hz", "403Hz", "196Hz", "98Hz", "49Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sidetone_hpf,
			    WM8996_SIDETONE, 7, sidetone_hpf_text);

अटल स्थिर अक्षर *hpf_mode_text[] = अणु
	"HiFi", "Custom", "Voice"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dsp1tx_hpf_mode,
			    WM8996_DSP1_TX_FILTERS, 3, hpf_mode_text);

अटल SOC_ENUM_SINGLE_DECL(dsp2tx_hpf_mode,
			    WM8996_DSP2_TX_FILTERS, 3, hpf_mode_text);

अटल स्थिर अक्षर *hpf_cutoff_text[] = अणु
	"50Hz", "75Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dsp1tx_hpf_cutoff,
			    WM8996_DSP1_TX_FILTERS, 0, hpf_cutoff_text);

अटल SOC_ENUM_SINGLE_DECL(dsp2tx_hpf_cutoff,
			    WM8996_DSP2_TX_FILTERS, 0, hpf_cutoff_text);

अटल व्योम wm8996_set_retune_mobile(काष्ठा snd_soc_component *component, पूर्णांक block)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8996_pdata *pdata = &wm8996->pdata;
	पूर्णांक base, best, best_val, save, i, cfg, अगरace;

	अगर (!wm8996->num_retune_mobile_texts)
		वापस;

	चयन (block) अणु
	हाल 0:
		base = WM8996_DSP1_RX_EQ_GAINS_1;
		अगर (snd_soc_component_पढ़ो(component, WM8996_POWER_MANAGEMENT_8) &
		    WM8996_DSP1RX_SRC)
			अगरace = 1;
		अन्यथा
			अगरace = 0;
		अवरोध;
	हाल 1:
		base = WM8996_DSP1_RX_EQ_GAINS_2;
		अगर (snd_soc_component_पढ़ो(component, WM8996_POWER_MANAGEMENT_8) &
		    WM8996_DSP2RX_SRC)
			अगरace = 1;
		अन्यथा
			अगरace = 0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* Find the version of the currently selected configuration
	 * with the nearest sample rate. */
	cfg = wm8996->retune_mobile_cfg[block];
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
			   wm8996->retune_mobile_texts[cfg]) == 0 &&
		    असल(pdata->retune_mobile_cfgs[i].rate
			- wm8996->rx_rate[अगरace]) < best_val) अणु
			best = i;
			best_val = असल(pdata->retune_mobile_cfgs[i].rate
				       - wm8996->rx_rate[अगरace]);
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "ReTune Mobile %d %s/%dHz for %dHz sample rate\n",
		block,
		pdata->retune_mobile_cfgs[best].name,
		pdata->retune_mobile_cfgs[best].rate,
		wm8996->rx_rate[अगरace]);

	/* The EQ will be disabled जबतक reconfiguring it, remember the
	 * current configuration. 
	 */
	save = snd_soc_component_पढ़ो(component, base);
	save &= WM8996_DSP1RX_EQ_ENA;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->retune_mobile_cfgs[best].regs); i++)
		snd_soc_component_update_bits(component, base + i, 0xffff,
				    pdata->retune_mobile_cfgs[best].regs[i]);

	snd_soc_component_update_bits(component, base, WM8996_DSP1RX_EQ_ENA, save);
पूर्ण

/* Icky as hell but saves code duplication */
अटल पूर्णांक wm8996_get_retune_mobile_block(स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, "DSP1 EQ Mode") == 0)
		वापस 0;
	अगर (म_भेद(name, "DSP2 EQ Mode") == 0)
		वापस 1;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8996_put_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8996_pdata *pdata = &wm8996->pdata;
	पूर्णांक block = wm8996_get_retune_mobile_block(kcontrol->id.name);
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];

	अगर (block < 0)
		वापस block;

	अगर (value >= pdata->num_retune_mobile_cfgs)
		वापस -EINVAL;

	wm8996->retune_mobile_cfg[block] = value;

	wm8996_set_retune_mobile(component, block);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8996_get_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक block = wm8996_get_retune_mobile_block(kcontrol->id.name);

	अगर (block < 0)
		वापस block;
	ucontrol->value.क्रमागतerated.item[0] = wm8996->retune_mobile_cfg[block];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm8996_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Capture Volume", WM8996_LEFT_LINE_INPUT_VOLUME,
		 WM8996_RIGHT_LINE_INPUT_VOLUME, 0, 31, 0, inpga_tlv),
SOC_DOUBLE_R("Capture ZC Switch", WM8996_LEFT_LINE_INPUT_VOLUME,
	     WM8996_RIGHT_LINE_INPUT_VOLUME, 5, 1, 0),

SOC_DOUBLE_TLV("DAC1 Sidetone Volume", WM8996_DAC1_MIXER_VOLUMES,
	       0, 5, 24, 0, sidetone_tlv),
SOC_DOUBLE_TLV("DAC2 Sidetone Volume", WM8996_DAC2_MIXER_VOLUMES,
	       0, 5, 24, 0, sidetone_tlv),
SOC_SINGLE("Sidetone LPF Switch", WM8996_SIDETONE, 12, 1, 0),
SOC_ENUM("Sidetone HPF Cut-off", sidetone_hpf),
SOC_SINGLE("Sidetone HPF Switch", WM8996_SIDETONE, 6, 1, 0),

SOC_DOUBLE_R_TLV("DSP1 Capture Volume", WM8996_DSP1_TX_LEFT_VOLUME,
		 WM8996_DSP1_TX_RIGHT_VOLUME, 1, 96, 0, digital_tlv),
SOC_DOUBLE_R_TLV("DSP2 Capture Volume", WM8996_DSP2_TX_LEFT_VOLUME,
		 WM8996_DSP2_TX_RIGHT_VOLUME, 1, 96, 0, digital_tlv),

SOC_SINGLE("DSP1 Capture Notch Filter Switch", WM8996_DSP1_TX_FILTERS,
	   13, 1, 0),
SOC_DOUBLE("DSP1 Capture HPF Switch", WM8996_DSP1_TX_FILTERS, 12, 11, 1, 0),
SOC_ENUM("DSP1 Capture HPF Mode", dsp1tx_hpf_mode),
SOC_ENUM("DSP1 Capture HPF Cutoff", dsp1tx_hpf_cutoff),

SOC_SINGLE("DSP2 Capture Notch Filter Switch", WM8996_DSP2_TX_FILTERS,
	   13, 1, 0),
SOC_DOUBLE("DSP2 Capture HPF Switch", WM8996_DSP2_TX_FILTERS, 12, 11, 1, 0),
SOC_ENUM("DSP2 Capture HPF Mode", dsp2tx_hpf_mode),
SOC_ENUM("DSP2 Capture HPF Cutoff", dsp2tx_hpf_cutoff),

SOC_DOUBLE_R_TLV("DSP1 Playback Volume", WM8996_DSP1_RX_LEFT_VOLUME,
		 WM8996_DSP1_RX_RIGHT_VOLUME, 1, 112, 0, digital_tlv),
SOC_SINGLE("DSP1 Playback Switch", WM8996_DSP1_RX_FILTERS_1, 9, 1, 1),

SOC_DOUBLE_R_TLV("DSP2 Playback Volume", WM8996_DSP2_RX_LEFT_VOLUME,
		 WM8996_DSP2_RX_RIGHT_VOLUME, 1, 112, 0, digital_tlv),
SOC_SINGLE("DSP2 Playback Switch", WM8996_DSP2_RX_FILTERS_1, 9, 1, 1),

SOC_DOUBLE_R_TLV("DAC1 Volume", WM8996_DAC1_LEFT_VOLUME,
		 WM8996_DAC1_RIGHT_VOLUME, 1, 112, 0, digital_tlv),
SOC_DOUBLE_R("DAC1 Switch", WM8996_DAC1_LEFT_VOLUME,
	     WM8996_DAC1_RIGHT_VOLUME, 9, 1, 1),

SOC_DOUBLE_R_TLV("DAC2 Volume", WM8996_DAC2_LEFT_VOLUME,
		 WM8996_DAC2_RIGHT_VOLUME, 1, 112, 0, digital_tlv),
SOC_DOUBLE_R("DAC2 Switch", WM8996_DAC2_LEFT_VOLUME,
	     WM8996_DAC2_RIGHT_VOLUME, 9, 1, 1),

SOC_SINGLE("Speaker High Performance Switch", WM8996_OVERSAMPLING, 3, 1, 0),
SOC_SINGLE("DMIC High Performance Switch", WM8996_OVERSAMPLING, 2, 1, 0),
SOC_SINGLE("ADC High Performance Switch", WM8996_OVERSAMPLING, 1, 1, 0),
SOC_SINGLE("DAC High Performance Switch", WM8996_OVERSAMPLING, 0, 1, 0),

SOC_SINGLE("DAC Soft Mute Switch", WM8996_DAC_SOFTMUTE, 1, 1, 0),
SOC_SINGLE("DAC Slow Soft Mute Switch", WM8996_DAC_SOFTMUTE, 0, 1, 0),

SOC_SINGLE("DSP1 3D Stereo Switch", WM8996_DSP1_RX_FILTERS_2, 8, 1, 0),
SOC_SINGLE("DSP2 3D Stereo Switch", WM8996_DSP2_RX_FILTERS_2, 8, 1, 0),

SOC_SINGLE_TLV("DSP1 3D Stereo Volume", WM8996_DSP1_RX_FILTERS_2, 10, 15,
		0, threedstereo_tlv),
SOC_SINGLE_TLV("DSP2 3D Stereo Volume", WM8996_DSP2_RX_FILTERS_2, 10, 15,
		0, threedstereo_tlv),

SOC_DOUBLE_TLV("Digital Output 1 Volume", WM8996_DAC1_HPOUT1_VOLUME, 0, 4,
	       8, 0, out_digital_tlv),
SOC_DOUBLE_TLV("Digital Output 2 Volume", WM8996_DAC2_HPOUT2_VOLUME, 0, 4,
	       8, 0, out_digital_tlv),

SOC_DOUBLE_R_TLV("Output 1 Volume", WM8996_OUTPUT1_LEFT_VOLUME,
		 WM8996_OUTPUT1_RIGHT_VOLUME, 0, 12, 0, out_tlv),
SOC_DOUBLE_R("Output 1 ZC Switch",  WM8996_OUTPUT1_LEFT_VOLUME,
	     WM8996_OUTPUT1_RIGHT_VOLUME, 7, 1, 0),

SOC_DOUBLE_R_TLV("Output 2 Volume", WM8996_OUTPUT2_LEFT_VOLUME,
		 WM8996_OUTPUT2_RIGHT_VOLUME, 0, 12, 0, out_tlv),
SOC_DOUBLE_R("Output 2 ZC Switch",  WM8996_OUTPUT2_LEFT_VOLUME,
	     WM8996_OUTPUT2_RIGHT_VOLUME, 7, 1, 0),

SOC_DOUBLE_TLV("Speaker Volume", WM8996_PDM_SPEAKER_VOLUME, 0, 4, 8, 0,
	       spk_tlv),
SOC_DOUBLE_R("Speaker Switch", WM8996_LEFT_PDM_SPEAKER,
	     WM8996_RIGHT_PDM_SPEAKER, 3, 1, 1),
SOC_DOUBLE_R("Speaker ZC Switch", WM8996_LEFT_PDM_SPEAKER,
	     WM8996_RIGHT_PDM_SPEAKER, 2, 1, 0),

SOC_SINGLE("DSP1 EQ Switch", WM8996_DSP1_RX_EQ_GAINS_1, 0, 1, 0),
SOC_SINGLE("DSP2 EQ Switch", WM8996_DSP2_RX_EQ_GAINS_1, 0, 1, 0),

SOC_SINGLE("DSP1 DRC TXL Switch", WM8996_DSP1_DRC_1, 0, 1, 0),
SOC_SINGLE("DSP1 DRC TXR Switch", WM8996_DSP1_DRC_1, 1, 1, 0),
SOC_SINGLE("DSP1 DRC RX Switch", WM8996_DSP1_DRC_1, 2, 1, 0),
SND_SOC_BYTES_MASK("DSP1 DRC", WM8996_DSP1_DRC_1, 5,
		   WM8996_DSP1RX_DRC_ENA | WM8996_DSP1TXL_DRC_ENA |
		   WM8996_DSP1TXR_DRC_ENA),

SOC_SINGLE("DSP2 DRC TXL Switch", WM8996_DSP2_DRC_1, 0, 1, 0),
SOC_SINGLE("DSP2 DRC TXR Switch", WM8996_DSP2_DRC_1, 1, 1, 0),
SOC_SINGLE("DSP2 DRC RX Switch", WM8996_DSP2_DRC_1, 2, 1, 0),
SND_SOC_BYTES_MASK("DSP2 DRC", WM8996_DSP2_DRC_1, 5,
		   WM8996_DSP2RX_DRC_ENA | WM8996_DSP2TXL_DRC_ENA |
		   WM8996_DSP2TXR_DRC_ENA),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8996_eq_controls[] = अणु
SOC_SINGLE_TLV("DSP1 EQ B1 Volume", WM8996_DSP1_RX_EQ_GAINS_1, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP1 EQ B2 Volume", WM8996_DSP1_RX_EQ_GAINS_1, 6, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP1 EQ B3 Volume", WM8996_DSP1_RX_EQ_GAINS_1, 1, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP1 EQ B4 Volume", WM8996_DSP1_RX_EQ_GAINS_2, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP1 EQ B5 Volume", WM8996_DSP1_RX_EQ_GAINS_2, 6, 31, 0,
	       eq_tlv),

SOC_SINGLE_TLV("DSP2 EQ B1 Volume", WM8996_DSP2_RX_EQ_GAINS_1, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP2 EQ B2 Volume", WM8996_DSP2_RX_EQ_GAINS_1, 6, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP2 EQ B3 Volume", WM8996_DSP2_RX_EQ_GAINS_1, 1, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP2 EQ B4 Volume", WM8996_DSP2_RX_EQ_GAINS_2, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("DSP2 EQ B5 Volume", WM8996_DSP2_RX_EQ_GAINS_2, 6, 31, 0,
	       eq_tlv),
पूर्ण;

अटल व्योम wm8996_bg_enable(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);

	wm8996->bg_ena++;
	अगर (wm8996->bg_ena == 1) अणु
		snd_soc_component_update_bits(component, WM8996_POWER_MANAGEMENT_1,
				    WM8996_BG_ENA, WM8996_BG_ENA);
		msleep(2);
	पूर्ण
पूर्ण

अटल व्योम wm8996_bg_disable(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);

	wm8996->bg_ena--;
	अगर (!wm8996->bg_ena)
		snd_soc_component_update_bits(component, WM8996_POWER_MANAGEMENT_1,
				    WM8996_BG_ENA, 0);
पूर्ण

अटल पूर्णांक bg_event(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wm8996_bg_enable(component);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wm8996_bg_disable(component);
		अवरोध;
	शेष:
		WARN(1, "Invalid event %d\n", event);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cp_event(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(5);
		अवरोध;
	शेष:
		WARN(1, "Invalid event %d\n", event);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmv_लघु_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);

	/* Record which outमाला_दो we enabled */
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
		wm8996->hpout_pending &= ~w->shअगरt;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
		wm8996->hpout_pending |= w->shअगरt;
		अवरोध;
	शेष:
		WARN(1, "Invalid event %d\n", event);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम रुको_क्रम_dc_servo(काष्ठा snd_soc_component *component, u16 mask)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout = 200;

	snd_soc_component_ग_लिखो(component, WM8996_DC_SERVO_2, mask);

	/* Use the पूर्णांकerrupt अगर possible */
	करो अणु
		अगर (i2c->irq) अणु
			समयout = रुको_क्रम_completion_समयout(&wm8996->dcs_करोne,
							      msecs_to_jअगरfies(200));
			अगर (समयout == 0)
				dev_err(component->dev, "DC servo timed out\n");

		पूर्ण अन्यथा अणु
			msleep(1);
			समयout--;
		पूर्ण

		ret = snd_soc_component_पढ़ो(component, WM8996_DC_SERVO_2);
		dev_dbg(component->dev, "DC servo state: %x\n", ret);
	पूर्ण जबतक (समयout && ret & mask);

	अगर (समयout == 0)
		dev_err(component->dev, "DC servo timed out for %x\n", mask);
	अन्यथा
		dev_dbg(component->dev, "DC servo complete for %x\n", mask);
पूर्ण

अटल व्योम wm8996_seq_notअगरier(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_dapm_type event, पूर्णांक subseq)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	u16 val, mask;

	/* Complete any pending DC servo starts */
	अगर (wm8996->dcs_pending) अणु
		dev_dbg(component->dev, "Starting DC servo for %x\n",
			wm8996->dcs_pending);

		/* Trigger a startup sequence */
		रुको_क्रम_dc_servo(component, wm8996->dcs_pending
				         << WM8996_DCS_TRIG_STARTUP_0_SHIFT);

		wm8996->dcs_pending = 0;
	पूर्ण

	अगर (wm8996->hpout_pending != wm8996->hpout_ena) अणु
		dev_dbg(component->dev, "Applying RMV_SHORTs %x->%x\n",
			wm8996->hpout_ena, wm8996->hpout_pending);

		val = 0;
		mask = 0;
		अगर (wm8996->hpout_pending & HPOUT1L) अणु
			val |= WM8996_HPOUT1L_RMV_SHORT | WM8996_HPOUT1L_OUTP;
			mask |= WM8996_HPOUT1L_RMV_SHORT | WM8996_HPOUT1L_OUTP;
		पूर्ण अन्यथा अणु
			mask |= WM8996_HPOUT1L_RMV_SHORT |
				WM8996_HPOUT1L_OUTP |
				WM8996_HPOUT1L_DLY;
		पूर्ण

		अगर (wm8996->hpout_pending & HPOUT1R) अणु
			val |= WM8996_HPOUT1R_RMV_SHORT | WM8996_HPOUT1R_OUTP;
			mask |= WM8996_HPOUT1R_RMV_SHORT | WM8996_HPOUT1R_OUTP;
		पूर्ण अन्यथा अणु
			mask |= WM8996_HPOUT1R_RMV_SHORT |
				WM8996_HPOUT1R_OUTP |
				WM8996_HPOUT1R_DLY;
		पूर्ण

		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1, mask, val);

		val = 0;
		mask = 0;
		अगर (wm8996->hpout_pending & HPOUT2L) अणु
			val |= WM8996_HPOUT2L_RMV_SHORT | WM8996_HPOUT2L_OUTP;
			mask |= WM8996_HPOUT2L_RMV_SHORT | WM8996_HPOUT2L_OUTP;
		पूर्ण अन्यथा अणु
			mask |= WM8996_HPOUT2L_RMV_SHORT |
				WM8996_HPOUT2L_OUTP |
				WM8996_HPOUT2L_DLY;
		पूर्ण

		अगर (wm8996->hpout_pending & HPOUT2R) अणु
			val |= WM8996_HPOUT2R_RMV_SHORT | WM8996_HPOUT2R_OUTP;
			mask |= WM8996_HPOUT2R_RMV_SHORT | WM8996_HPOUT2R_OUTP;
		पूर्ण अन्यथा अणु
			mask |= WM8996_HPOUT2R_RMV_SHORT |
				WM8996_HPOUT2R_OUTP |
				WM8996_HPOUT2R_DLY;
		पूर्ण

		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_2, mask, val);

		wm8996->hpout_ena = wm8996->hpout_pending;
	पूर्ण
पूर्ण

अटल पूर्णांक dcs_start(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		wm8996->dcs_pending |= 1 << w->shअगरt;
		अवरोध;
	शेष:
		WARN(1, "Invalid event %d\n", event);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"IN1", "IN2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(left_sidetone_क्रमागत,
			    WM8996_SIDETONE, 0, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new left_sidetone =
	SOC_DAPM_ENUM("Left Sidetone", left_sidetone_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(right_sidetone_क्रमागत,
			    WM8996_SIDETONE, 1, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new right_sidetone =
	SOC_DAPM_ENUM("Right Sidetone", right_sidetone_क्रमागत);

अटल स्थिर अक्षर *spk_text[] = अणु
	"DAC1L", "DAC1R", "DAC2L", "DAC2R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(spkl_क्रमागत,
			    WM8996_LEFT_PDM_SPEAKER, 0, spk_text);

अटल स्थिर काष्ठा snd_kcontrol_new spkl_mux =
	SOC_DAPM_ENUM("SPKL", spkl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(spkr_क्रमागत,
			    WM8996_RIGHT_PDM_SPEAKER, 0, spk_text);

अटल स्थिर काष्ठा snd_kcontrol_new spkr_mux =
	SOC_DAPM_ENUM("SPKR", spkr_क्रमागत);

अटल स्थिर अक्षर *dsp1rx_text[] = अणु
	"AIF1", "AIF2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dsp1rx_क्रमागत,
			    WM8996_POWER_MANAGEMENT_8, 0, dsp1rx_text);

अटल स्थिर काष्ठा snd_kcontrol_new dsp1rx =
	SOC_DAPM_ENUM("DSP1RX", dsp1rx_क्रमागत);

अटल स्थिर अक्षर *dsp2rx_text[] = अणु
	 "AIF2", "AIF1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dsp2rx_क्रमागत,
			    WM8996_POWER_MANAGEMENT_8, 4, dsp2rx_text);

अटल स्थिर काष्ठा snd_kcontrol_new dsp2rx =
	SOC_DAPM_ENUM("DSP2RX", dsp2rx_क्रमागत);

अटल स्थिर अक्षर *aअगर2tx_text[] = अणु
	"DSP2", "DSP1", "AIF1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर2tx_क्रमागत,
			    WM8996_POWER_MANAGEMENT_8, 6, aअगर2tx_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2tx =
	SOC_DAPM_ENUM("AIF2TX", aअगर2tx_क्रमागत);

अटल स्थिर अक्षर *inmux_text[] = अणु
	"ADC", "DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(in1_क्रमागत,
			    WM8996_POWER_MANAGEMENT_7, 0, inmux_text);

अटल स्थिर काष्ठा snd_kcontrol_new in1_mux =
	SOC_DAPM_ENUM("IN1 Mux", in1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(in2_क्रमागत,
			    WM8996_POWER_MANAGEMENT_7, 4, inmux_text);

अटल स्थिर काष्ठा snd_kcontrol_new in2_mux =
	SOC_DAPM_ENUM("IN2 Mux", in2_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new dac2r_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8996_DAC2_RIGHT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8996_DAC2_RIGHT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("DSP2 Switch", WM8996_DAC2_RIGHT_MIXER_ROUTING, 1, 1, 0),
SOC_DAPM_SINGLE("DSP1 Switch", WM8996_DAC2_RIGHT_MIXER_ROUTING, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac2l_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8996_DAC2_LEFT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8996_DAC2_LEFT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("DSP2 Switch", WM8996_DAC2_LEFT_MIXER_ROUTING, 1, 1, 0),
SOC_DAPM_SINGLE("DSP1 Switch", WM8996_DAC2_LEFT_MIXER_ROUTING, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac1r_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8996_DAC1_RIGHT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8996_DAC1_RIGHT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("DSP2 Switch", WM8996_DAC1_RIGHT_MIXER_ROUTING, 1, 1, 0),
SOC_DAPM_SINGLE("DSP1 Switch", WM8996_DAC1_RIGHT_MIXER_ROUTING, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac1l_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8996_DAC1_LEFT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8996_DAC1_LEFT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("DSP2 Switch", WM8996_DAC1_LEFT_MIXER_ROUTING, 1, 1, 0),
SOC_DAPM_SINGLE("DSP1 Switch", WM8996_DAC1_LEFT_MIXER_ROUTING, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dsp1txl[] = अणु
SOC_DAPM_SINGLE("IN1 Switch", WM8996_DSP1_TX_LEFT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8996_DSP1_TX_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dsp1txr[] = अणु
SOC_DAPM_SINGLE("IN1 Switch", WM8996_DSP1_TX_RIGHT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8996_DSP1_TX_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dsp2txl[] = अणु
SOC_DAPM_SINGLE("IN1 Switch", WM8996_DSP2_TX_LEFT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8996_DSP2_TX_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dsp2txr[] = अणु
SOC_DAPM_SINGLE("IN1 Switch", WM8996_DSP2_TX_RIGHT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8996_DSP2_TX_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;


अटल स्थिर काष्ठा snd_soc_dapm_widget wm8996_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1LN"),
SND_SOC_DAPM_INPUT("IN1LP"),
SND_SOC_DAPM_INPUT("IN1RN"),
SND_SOC_DAPM_INPUT("IN1RP"),

SND_SOC_DAPM_INPUT("IN2LN"),
SND_SOC_DAPM_INPUT("IN2LP"),
SND_SOC_DAPM_INPUT("IN2RN"),
SND_SOC_DAPM_INPUT("IN2RP"),

SND_SOC_DAPM_INPUT("DMIC1DAT"),
SND_SOC_DAPM_INPUT("DMIC2DAT"),

SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD", 20, 0),
SND_SOC_DAPM_SUPPLY_S("SYSCLK", 1, WM8996_AIF_CLOCKING_1, 0, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY_S("SYSDSPCLK", 2, WM8996_CLOCKING_1, 1, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY_S("AIFCLK", 2, WM8996_CLOCKING_1, 2, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY_S("Charge Pump", 2, WM8996_CHARGE_PUMP_1, 15, 0, cp_event,
		      SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_SUPPLY("Bandgap", SND_SOC_NOPM, 0, 0, bg_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("LDO2", WM8996_POWER_MANAGEMENT_2, 1, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICB1 Audio", WM8996_MICBIAS_1, 4, 1, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICB2 Audio", WM8996_MICBIAS_2, 4, 1, शून्य, 0),
SND_SOC_DAPM_MICBIAS("MICB2", WM8996_POWER_MANAGEMENT_1, 9, 0),
SND_SOC_DAPM_MICBIAS("MICB1", WM8996_POWER_MANAGEMENT_1, 8, 0),

SND_SOC_DAPM_PGA("IN1L PGA", WM8996_POWER_MANAGEMENT_2, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("IN1R PGA", WM8996_POWER_MANAGEMENT_2, 4, 0, शून्य, 0),

SND_SOC_DAPM_MUX("IN1L Mux", WM8996_POWER_MANAGEMENT_7, 2, 0, &in1_mux),
SND_SOC_DAPM_MUX("IN1R Mux", WM8996_POWER_MANAGEMENT_7, 3, 0, &in1_mux),
SND_SOC_DAPM_MUX("IN2L Mux", WM8996_POWER_MANAGEMENT_7, 6, 0, &in2_mux),
SND_SOC_DAPM_MUX("IN2R Mux", WM8996_POWER_MANAGEMENT_7, 7, 0, &in2_mux),

SND_SOC_DAPM_SUPPLY("DMIC2", WM8996_POWER_MANAGEMENT_7, 9, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("DMIC1", WM8996_POWER_MANAGEMENT_7, 8, 0, शून्य, 0),

SND_SOC_DAPM_ADC("DMIC2L", शून्य, WM8996_POWER_MANAGEMENT_3, 5, 0),
SND_SOC_DAPM_ADC("DMIC2R", शून्य, WM8996_POWER_MANAGEMENT_3, 4, 0),
SND_SOC_DAPM_ADC("DMIC1L", शून्य, WM8996_POWER_MANAGEMENT_3, 3, 0),
SND_SOC_DAPM_ADC("DMIC1R", शून्य, WM8996_POWER_MANAGEMENT_3, 2, 0),

SND_SOC_DAPM_ADC("ADCL", शून्य, WM8996_POWER_MANAGEMENT_3, 1, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, WM8996_POWER_MANAGEMENT_3, 0, 0),

SND_SOC_DAPM_MUX("Left Sidetone", SND_SOC_NOPM, 0, 0, &left_sidetone),
SND_SOC_DAPM_MUX("Right Sidetone", SND_SOC_NOPM, 0, 0, &right_sidetone),

SND_SOC_DAPM_AIF_IN("DSP2RXL", शून्य, 0, WM8996_POWER_MANAGEMENT_3, 11, 0),
SND_SOC_DAPM_AIF_IN("DSP2RXR", शून्य, 1, WM8996_POWER_MANAGEMENT_3, 10, 0),
SND_SOC_DAPM_AIF_IN("DSP1RXL", शून्य, 0, WM8996_POWER_MANAGEMENT_3, 9, 0),
SND_SOC_DAPM_AIF_IN("DSP1RXR", शून्य, 1, WM8996_POWER_MANAGEMENT_3, 8, 0),

SND_SOC_DAPM_MIXER("DSP2TXL", WM8996_POWER_MANAGEMENT_5, 11, 0,
		   dsp2txl, ARRAY_SIZE(dsp2txl)),
SND_SOC_DAPM_MIXER("DSP2TXR", WM8996_POWER_MANAGEMENT_5, 10, 0,
		   dsp2txr, ARRAY_SIZE(dsp2txr)),
SND_SOC_DAPM_MIXER("DSP1TXL", WM8996_POWER_MANAGEMENT_5, 9, 0,
		   dsp1txl, ARRAY_SIZE(dsp1txl)),
SND_SOC_DAPM_MIXER("DSP1TXR", WM8996_POWER_MANAGEMENT_5, 8, 0,
		   dsp1txr, ARRAY_SIZE(dsp1txr)),

SND_SOC_DAPM_MIXER("DAC2L Mixer", SND_SOC_NOPM, 0, 0,
		   dac2l_mix, ARRAY_SIZE(dac2l_mix)),
SND_SOC_DAPM_MIXER("DAC2R Mixer", SND_SOC_NOPM, 0, 0,
		   dac2r_mix, ARRAY_SIZE(dac2r_mix)),
SND_SOC_DAPM_MIXER("DAC1L Mixer", SND_SOC_NOPM, 0, 0,
		   dac1l_mix, ARRAY_SIZE(dac1l_mix)),
SND_SOC_DAPM_MIXER("DAC1R Mixer", SND_SOC_NOPM, 0, 0,
		   dac1r_mix, ARRAY_SIZE(dac1r_mix)),

SND_SOC_DAPM_DAC("DAC2L", शून्य, WM8996_POWER_MANAGEMENT_5, 3, 0),
SND_SOC_DAPM_DAC("DAC2R", शून्य, WM8996_POWER_MANAGEMENT_5, 2, 0),
SND_SOC_DAPM_DAC("DAC1L", शून्य, WM8996_POWER_MANAGEMENT_5, 1, 0),
SND_SOC_DAPM_DAC("DAC1R", शून्य, WM8996_POWER_MANAGEMENT_5, 0, 0),

SND_SOC_DAPM_AIF_IN("AIF2RX1", शून्य, 0, WM8996_POWER_MANAGEMENT_4, 9, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX0", शून्य, 1, WM8996_POWER_MANAGEMENT_4, 8, 0),

SND_SOC_DAPM_AIF_OUT("AIF2TX1", शून्य, 0, WM8996_POWER_MANAGEMENT_6, 9, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX0", शून्य, 1, WM8996_POWER_MANAGEMENT_6, 8, 0),

SND_SOC_DAPM_AIF_IN("AIF1RX5", शून्य, 5, WM8996_POWER_MANAGEMENT_4, 5, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX4", शून्य, 4, WM8996_POWER_MANAGEMENT_4, 4, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX3", शून्य, 3, WM8996_POWER_MANAGEMENT_4, 3, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX2", शून्य, 2, WM8996_POWER_MANAGEMENT_4, 2, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX1", शून्य, 1, WM8996_POWER_MANAGEMENT_4, 1, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX0", शून्य, 0, WM8996_POWER_MANAGEMENT_4, 0, 0),

SND_SOC_DAPM_AIF_OUT("AIF1TX5", शून्य, 5, WM8996_POWER_MANAGEMENT_6, 5, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX4", शून्य, 4, WM8996_POWER_MANAGEMENT_6, 4, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX3", शून्य, 3, WM8996_POWER_MANAGEMENT_6, 3, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX2", शून्य, 2, WM8996_POWER_MANAGEMENT_6, 2, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX1", शून्य, 1, WM8996_POWER_MANAGEMENT_6, 1, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX0", शून्य, 0, WM8996_POWER_MANAGEMENT_6, 0, 0),

/* We route as stereo pairs so define some dummy widमाला_लो to squash
 * things करोwn क्रम now.  RXA = 0,1, RXB = 2,3 and so on */
SND_SOC_DAPM_PGA("AIF1RXA", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_PGA("AIF1RXB", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_PGA("AIF1RXC", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_PGA("AIF2RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DSP2TX", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_MUX("DSP1RX", SND_SOC_NOPM, 0, 0, &dsp1rx),
SND_SOC_DAPM_MUX("DSP2RX", SND_SOC_NOPM, 0, 0, &dsp2rx),
SND_SOC_DAPM_MUX("AIF2TX", SND_SOC_NOPM, 0, 0, &aअगर2tx),

SND_SOC_DAPM_MUX("SPKL", SND_SOC_NOPM, 0, 0, &spkl_mux),
SND_SOC_DAPM_MUX("SPKR", SND_SOC_NOPM, 0, 0, &spkr_mux),
SND_SOC_DAPM_PGA("SPKL PGA", WM8996_LEFT_PDM_SPEAKER, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SPKR PGA", WM8996_RIGHT_PDM_SPEAKER, 4, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("HPOUT2L PGA", 0, WM8996_POWER_MANAGEMENT_1, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT2L_DLY", 1, WM8996_ANALOGUE_HP_2, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT2L_DCS", 2, WM8996_DC_SERVO_1, 2, 0, dcs_start,
		   SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_S("HPOUT2L_RMV_SHORT", 3, SND_SOC_NOPM, HPOUT2L, 0,
		   rmv_लघु_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA_S("HPOUT2R PGA", 0, WM8996_POWER_MANAGEMENT_1, 6, 0,शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT2R_DLY", 1, WM8996_ANALOGUE_HP_2, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT2R_DCS", 2, WM8996_DC_SERVO_1, 3, 0, dcs_start,
		   SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_S("HPOUT2R_RMV_SHORT", 3, SND_SOC_NOPM, HPOUT2R, 0,
		   rmv_लघु_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA_S("HPOUT1L PGA", 0, WM8996_POWER_MANAGEMENT_1, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT1L_DLY", 1, WM8996_ANALOGUE_HP_1, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT1L_DCS", 2, WM8996_DC_SERVO_1, 0, 0, dcs_start,
		   SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_S("HPOUT1L_RMV_SHORT", 3, SND_SOC_NOPM, HPOUT1L, 0,
		   rmv_लघु_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA_S("HPOUT1R PGA", 0, WM8996_POWER_MANAGEMENT_1, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT1R_DLY", 1, WM8996_ANALOGUE_HP_1, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPOUT1R_DCS", 2, WM8996_DC_SERVO_1, 1, 0, dcs_start,
		   SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_S("HPOUT1R_RMV_SHORT", 3, SND_SOC_NOPM, HPOUT1R, 0,
		   rmv_लघु_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_OUTPUT("HPOUT1L"),
SND_SOC_DAPM_OUTPUT("HPOUT1R"),
SND_SOC_DAPM_OUTPUT("HPOUT2L"),
SND_SOC_DAPM_OUTPUT("HPOUT2R"),
SND_SOC_DAPM_OUTPUT("SPKDAT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8996_dapm_routes[] = अणु
	अणु "AIFCLK", शून्य, "SYSCLK" पूर्ण,
	अणु "SYSDSPCLK", शून्य, "SYSCLK" पूर्ण,
	अणु "Charge Pump", शून्य, "SYSCLK" पूर्ण,
	अणु "Charge Pump", शून्य, "CPVDD" पूर्ण,

	अणु "MICB1", शून्य, "LDO2" पूर्ण,
	अणु "MICB1", शून्य, "MICB1 Audio" पूर्ण,
	अणु "MICB1", शून्य, "Bandgap" पूर्ण,
	अणु "MICB2", शून्य, "LDO2" पूर्ण,
	अणु "MICB2", शून्य, "MICB2 Audio" पूर्ण,
	अणु "MICB2", शून्य, "Bandgap" पूर्ण,

	अणु "AIF1RX0", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX1", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX2", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX3", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX4", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX5", शून्य, "AIF1 Playback" पूर्ण,

	अणु "AIF2RX0", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX1", शून्य, "AIF2 Playback" पूर्ण,

	अणु "AIF1 Capture", शून्य, "AIF1TX0" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX1" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX2" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX3" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX4" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX5" पूर्ण,

	अणु "AIF2 Capture", शून्य, "AIF2TX0" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX1" पूर्ण,

	अणु "IN1L PGA", शून्य, "IN2LN" पूर्ण,
	अणु "IN1L PGA", शून्य, "IN2LP" पूर्ण,
	अणु "IN1L PGA", शून्य, "IN1LN" पूर्ण,
	अणु "IN1L PGA", शून्य, "IN1LP" पूर्ण,
	अणु "IN1L PGA", शून्य, "Bandgap" पूर्ण,

	अणु "IN1R PGA", शून्य, "IN2RN" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN2RP" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN1RN" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN1RP" पूर्ण,
	अणु "IN1R PGA", शून्य, "Bandgap" पूर्ण,

	अणु "ADCL", शून्य, "IN1L PGA" पूर्ण,

	अणु "ADCR", शून्य, "IN1R PGA" पूर्ण,

	अणु "DMIC1L", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC2L", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC2DAT" पूर्ण,

	अणु "DMIC2L", शून्य, "DMIC2" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC2" पूर्ण,
	अणु "DMIC1L", शून्य, "DMIC1" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC1" पूर्ण,

	अणु "IN1L Mux", "ADC", "ADCL" पूर्ण,
	अणु "IN1L Mux", "DMIC1", "DMIC1L" पूर्ण,
	अणु "IN1L Mux", "DMIC2", "DMIC2L" पूर्ण,

	अणु "IN1R Mux", "ADC", "ADCR" पूर्ण,
	अणु "IN1R Mux", "DMIC1", "DMIC1R" पूर्ण,
	अणु "IN1R Mux", "DMIC2", "DMIC2R" पूर्ण,

	अणु "IN2L Mux", "ADC", "ADCL" पूर्ण,
	अणु "IN2L Mux", "DMIC1", "DMIC1L" पूर्ण,
	अणु "IN2L Mux", "DMIC2", "DMIC2L" पूर्ण,

	अणु "IN2R Mux", "ADC", "ADCR" पूर्ण,
	अणु "IN2R Mux", "DMIC1", "DMIC1R" पूर्ण,
	अणु "IN2R Mux", "DMIC2", "DMIC2R" पूर्ण,

	अणु "Left Sidetone", "IN1", "IN1L Mux" पूर्ण,
	अणु "Left Sidetone", "IN2", "IN2L Mux" पूर्ण,

	अणु "Right Sidetone", "IN1", "IN1R Mux" पूर्ण,
	अणु "Right Sidetone", "IN2", "IN2R Mux" पूर्ण,

	अणु "DSP1TXL", "IN1 Switch", "IN1L Mux" पूर्ण,
	अणु "DSP1TXR", "IN1 Switch", "IN1R Mux" पूर्ण,

	अणु "DSP2TXL", "IN1 Switch", "IN2L Mux" पूर्ण,
	अणु "DSP2TXR", "IN1 Switch", "IN2R Mux" पूर्ण,

	अणु "AIF1TX0", शून्य, "DSP1TXL" पूर्ण,
	अणु "AIF1TX1", शून्य, "DSP1TXR" पूर्ण,
	अणु "AIF1TX2", शून्य, "DSP2TXL" पूर्ण,
	अणु "AIF1TX3", शून्य, "DSP2TXR" पूर्ण,
	अणु "AIF1TX4", शून्य, "AIF2RX0" पूर्ण,
	अणु "AIF1TX5", शून्य, "AIF2RX1" पूर्ण,

	अणु "AIF1RX0", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1RX1", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1RX2", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1RX3", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1RX4", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1RX5", शून्य, "AIFCLK" पूर्ण,

	अणु "AIF2RX0", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF2RX1", शून्य, "AIFCLK" पूर्ण,

	अणु "AIF1TX0", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1TX1", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1TX2", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1TX3", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1TX4", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF1TX5", शून्य, "AIFCLK" पूर्ण,

	अणु "AIF2TX0", शून्य, "AIFCLK" पूर्ण,
	अणु "AIF2TX1", शून्य, "AIFCLK" पूर्ण,

	अणु "DSP1RXL", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP1RXR", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP2RXL", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP2RXR", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP1TXL", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP1TXR", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP2TXL", शून्य, "SYSDSPCLK" पूर्ण,
	अणु "DSP2TXR", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "AIF1RXA", शून्य, "AIF1RX0" पूर्ण,
	अणु "AIF1RXA", शून्य, "AIF1RX1" पूर्ण,
	अणु "AIF1RXB", शून्य, "AIF1RX2" पूर्ण,
	अणु "AIF1RXB", शून्य, "AIF1RX3" पूर्ण,
	अणु "AIF1RXC", शून्य, "AIF1RX4" पूर्ण,
	अणु "AIF1RXC", शून्य, "AIF1RX5" पूर्ण,

	अणु "AIF2RX", शून्य, "AIF2RX0" पूर्ण,
	अणु "AIF2RX", शून्य, "AIF2RX1" पूर्ण,

	अणु "AIF2TX", "DSP2", "DSP2TX" पूर्ण,
	अणु "AIF2TX", "DSP1", "DSP1RX" पूर्ण,
	अणु "AIF2TX", "AIF1", "AIF1RXC" पूर्ण,

	अणु "DSP1RXL", शून्य, "DSP1RX" पूर्ण,
	अणु "DSP1RXR", शून्य, "DSP1RX" पूर्ण,
	अणु "DSP2RXL", शून्य, "DSP2RX" पूर्ण,
	अणु "DSP2RXR", शून्य, "DSP2RX" पूर्ण,

	अणु "DSP2TX", शून्य, "DSP2TXL" पूर्ण,
	अणु "DSP2TX", शून्य, "DSP2TXR" पूर्ण,

	अणु "DSP1RX", "AIF1", "AIF1RXA" पूर्ण,
	अणु "DSP1RX", "AIF2", "AIF2RX" पूर्ण,

	अणु "DSP2RX", "AIF1", "AIF1RXB" पूर्ण,
	अणु "DSP2RX", "AIF2", "AIF2RX" पूर्ण,

	अणु "DAC2L Mixer", "DSP2 Switch", "DSP2RXL" पूर्ण,
	अणु "DAC2L Mixer", "DSP1 Switch", "DSP1RXL" पूर्ण,
	अणु "DAC2L Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,
	अणु "DAC2L Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,

	अणु "DAC2R Mixer", "DSP2 Switch", "DSP2RXR" पूर्ण,
	अणु "DAC2R Mixer", "DSP1 Switch", "DSP1RXR" पूर्ण,
	अणु "DAC2R Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,
	अणु "DAC2R Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,

	अणु "DAC1L Mixer", "DSP2 Switch", "DSP2RXL" पूर्ण,
	अणु "DAC1L Mixer", "DSP1 Switch", "DSP1RXL" पूर्ण,
	अणु "DAC1L Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,
	अणु "DAC1L Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,

	अणु "DAC1R Mixer", "DSP2 Switch", "DSP2RXR" पूर्ण,
	अणु "DAC1R Mixer", "DSP1 Switch", "DSP1RXR" पूर्ण,
	अणु "DAC1R Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,
	अणु "DAC1R Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,

	अणु "DAC1L", शून्य, "DAC1L Mixer" पूर्ण,
	अणु "DAC1R", शून्य, "DAC1R Mixer" पूर्ण,
	अणु "DAC2L", शून्य, "DAC2L Mixer" पूर्ण,
	अणु "DAC2R", शून्य, "DAC2R Mixer" पूर्ण,

	अणु "HPOUT2L PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "HPOUT2L PGA", शून्य, "Bandgap" पूर्ण,
	अणु "HPOUT2L PGA", शून्य, "DAC2L" पूर्ण,
	अणु "HPOUT2L_DLY", शून्य, "HPOUT2L PGA" पूर्ण,
	अणु "HPOUT2L_DCS", शून्य, "HPOUT2L_DLY" पूर्ण,
	अणु "HPOUT2L_RMV_SHORT", शून्य, "HPOUT2L_DCS" पूर्ण,

	अणु "HPOUT2R PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "HPOUT2R PGA", शून्य, "Bandgap" पूर्ण,
	अणु "HPOUT2R PGA", शून्य, "DAC2R" पूर्ण,
	अणु "HPOUT2R_DLY", शून्य, "HPOUT2R PGA" पूर्ण,
	अणु "HPOUT2R_DCS", शून्य, "HPOUT2R_DLY" पूर्ण,
	अणु "HPOUT2R_RMV_SHORT", शून्य, "HPOUT2R_DCS" पूर्ण,

	अणु "HPOUT1L PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "HPOUT1L PGA", शून्य, "Bandgap" पूर्ण,
	अणु "HPOUT1L PGA", शून्य, "DAC1L" पूर्ण,
	अणु "HPOUT1L_DLY", शून्य, "HPOUT1L PGA" पूर्ण,
	अणु "HPOUT1L_DCS", शून्य, "HPOUT1L_DLY" पूर्ण,
	अणु "HPOUT1L_RMV_SHORT", शून्य, "HPOUT1L_DCS" पूर्ण,

	अणु "HPOUT1R PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "HPOUT1R PGA", शून्य, "Bandgap" पूर्ण,
	अणु "HPOUT1R PGA", शून्य, "DAC1R" पूर्ण,
	अणु "HPOUT1R_DLY", शून्य, "HPOUT1R PGA" पूर्ण,
	अणु "HPOUT1R_DCS", शून्य, "HPOUT1R_DLY" पूर्ण,
	अणु "HPOUT1R_RMV_SHORT", शून्य, "HPOUT1R_DCS" पूर्ण,

	अणु "HPOUT2L", शून्य, "HPOUT2L_RMV_SHORT" पूर्ण,
	अणु "HPOUT2R", शून्य, "HPOUT2R_RMV_SHORT" पूर्ण,
	अणु "HPOUT1L", शून्य, "HPOUT1L_RMV_SHORT" पूर्ण,
	अणु "HPOUT1R", शून्य, "HPOUT1R_RMV_SHORT" पूर्ण,

	अणु "SPKL", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPKL", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPKL", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPKL", "DAC2R", "DAC2R" पूर्ण,

	अणु "SPKR", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPKR", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPKR", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPKR", "DAC2R", "DAC2R" पूर्ण,

	अणु "SPKL PGA", शून्य, "SPKL" पूर्ण,
	अणु "SPKR PGA", शून्य, "SPKR" पूर्ण,

	अणु "SPKDAT", शून्य, "SPKL PGA" पूर्ण,
	अणु "SPKDAT", शून्य, "SPKR PGA" पूर्ण,
पूर्ण;

अटल bool wm8996_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Due to the sparseness of the रेजिस्टर map the compiler
	 * output from an explicit चयन statement ends up being much
	 * more efficient than a table.
	 */
	चयन (reg) अणु
	हाल WM8996_SOFTWARE_RESET:
	हाल WM8996_POWER_MANAGEMENT_1:
	हाल WM8996_POWER_MANAGEMENT_2:
	हाल WM8996_POWER_MANAGEMENT_3:
	हाल WM8996_POWER_MANAGEMENT_4:
	हाल WM8996_POWER_MANAGEMENT_5:
	हाल WM8996_POWER_MANAGEMENT_6:
	हाल WM8996_POWER_MANAGEMENT_7:
	हाल WM8996_POWER_MANAGEMENT_8:
	हाल WM8996_LEFT_LINE_INPUT_VOLUME:
	हाल WM8996_RIGHT_LINE_INPUT_VOLUME:
	हाल WM8996_LINE_INPUT_CONTROL:
	हाल WM8996_DAC1_HPOUT1_VOLUME:
	हाल WM8996_DAC2_HPOUT2_VOLUME:
	हाल WM8996_DAC1_LEFT_VOLUME:
	हाल WM8996_DAC1_RIGHT_VOLUME:
	हाल WM8996_DAC2_LEFT_VOLUME:
	हाल WM8996_DAC2_RIGHT_VOLUME:
	हाल WM8996_OUTPUT1_LEFT_VOLUME:
	हाल WM8996_OUTPUT1_RIGHT_VOLUME:
	हाल WM8996_OUTPUT2_LEFT_VOLUME:
	हाल WM8996_OUTPUT2_RIGHT_VOLUME:
	हाल WM8996_MICBIAS_1:
	हाल WM8996_MICBIAS_2:
	हाल WM8996_LDO_1:
	हाल WM8996_LDO_2:
	हाल WM8996_ACCESSORY_DETECT_MODE_1:
	हाल WM8996_ACCESSORY_DETECT_MODE_2:
	हाल WM8996_HEADPHONE_DETECT_1:
	हाल WM8996_HEADPHONE_DETECT_2:
	हाल WM8996_MIC_DETECT_1:
	हाल WM8996_MIC_DETECT_2:
	हाल WM8996_MIC_DETECT_3:
	हाल WM8996_CHARGE_PUMP_1:
	हाल WM8996_CHARGE_PUMP_2:
	हाल WM8996_DC_SERVO_1:
	हाल WM8996_DC_SERVO_2:
	हाल WM8996_DC_SERVO_3:
	हाल WM8996_DC_SERVO_5:
	हाल WM8996_DC_SERVO_6:
	हाल WM8996_DC_SERVO_7:
	हाल WM8996_DC_SERVO_READBACK_0:
	हाल WM8996_ANALOGUE_HP_1:
	हाल WM8996_ANALOGUE_HP_2:
	हाल WM8996_CHIP_REVISION:
	हाल WM8996_CONTROL_INTERFACE_1:
	हाल WM8996_WRITE_SEQUENCER_CTRL_1:
	हाल WM8996_WRITE_SEQUENCER_CTRL_2:
	हाल WM8996_AIF_CLOCKING_1:
	हाल WM8996_AIF_CLOCKING_2:
	हाल WM8996_CLOCKING_1:
	हाल WM8996_CLOCKING_2:
	हाल WM8996_AIF_RATE:
	हाल WM8996_FLL_CONTROL_1:
	हाल WM8996_FLL_CONTROL_2:
	हाल WM8996_FLL_CONTROL_3:
	हाल WM8996_FLL_CONTROL_4:
	हाल WM8996_FLL_CONTROL_5:
	हाल WM8996_FLL_CONTROL_6:
	हाल WM8996_FLL_EFS_1:
	हाल WM8996_FLL_EFS_2:
	हाल WM8996_AIF1_CONTROL:
	हाल WM8996_AIF1_BCLK:
	हाल WM8996_AIF1_TX_LRCLK_1:
	हाल WM8996_AIF1_TX_LRCLK_2:
	हाल WM8996_AIF1_RX_LRCLK_1:
	हाल WM8996_AIF1_RX_LRCLK_2:
	हाल WM8996_AIF1TX_DATA_CONFIGURATION_1:
	हाल WM8996_AIF1TX_DATA_CONFIGURATION_2:
	हाल WM8996_AIF1RX_DATA_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_0_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_1_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_2_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_3_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_4_CONFIGURATION:
	हाल WM8996_AIF1TX_CHANNEL_5_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_0_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_1_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_2_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_3_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_4_CONFIGURATION:
	हाल WM8996_AIF1RX_CHANNEL_5_CONFIGURATION:
	हाल WM8996_AIF1RX_MONO_CONFIGURATION:
	हाल WM8996_AIF1TX_TEST:
	हाल WM8996_AIF2_CONTROL:
	हाल WM8996_AIF2_BCLK:
	हाल WM8996_AIF2_TX_LRCLK_1:
	हाल WM8996_AIF2_TX_LRCLK_2:
	हाल WM8996_AIF2_RX_LRCLK_1:
	हाल WM8996_AIF2_RX_LRCLK_2:
	हाल WM8996_AIF2TX_DATA_CONFIGURATION_1:
	हाल WM8996_AIF2TX_DATA_CONFIGURATION_2:
	हाल WM8996_AIF2RX_DATA_CONFIGURATION:
	हाल WM8996_AIF2TX_CHANNEL_0_CONFIGURATION:
	हाल WM8996_AIF2TX_CHANNEL_1_CONFIGURATION:
	हाल WM8996_AIF2RX_CHANNEL_0_CONFIGURATION:
	हाल WM8996_AIF2RX_CHANNEL_1_CONFIGURATION:
	हाल WM8996_AIF2RX_MONO_CONFIGURATION:
	हाल WM8996_AIF2TX_TEST:
	हाल WM8996_DSP1_TX_LEFT_VOLUME:
	हाल WM8996_DSP1_TX_RIGHT_VOLUME:
	हाल WM8996_DSP1_RX_LEFT_VOLUME:
	हाल WM8996_DSP1_RX_RIGHT_VOLUME:
	हाल WM8996_DSP1_TX_FILTERS:
	हाल WM8996_DSP1_RX_FILTERS_1:
	हाल WM8996_DSP1_RX_FILTERS_2:
	हाल WM8996_DSP1_DRC_1:
	हाल WM8996_DSP1_DRC_2:
	हाल WM8996_DSP1_DRC_3:
	हाल WM8996_DSP1_DRC_4:
	हाल WM8996_DSP1_DRC_5:
	हाल WM8996_DSP1_RX_EQ_GAINS_1:
	हाल WM8996_DSP1_RX_EQ_GAINS_2:
	हाल WM8996_DSP1_RX_EQ_BAND_1_A:
	हाल WM8996_DSP1_RX_EQ_BAND_1_B:
	हाल WM8996_DSP1_RX_EQ_BAND_1_PG:
	हाल WM8996_DSP1_RX_EQ_BAND_2_A:
	हाल WM8996_DSP1_RX_EQ_BAND_2_B:
	हाल WM8996_DSP1_RX_EQ_BAND_2_C:
	हाल WM8996_DSP1_RX_EQ_BAND_2_PG:
	हाल WM8996_DSP1_RX_EQ_BAND_3_A:
	हाल WM8996_DSP1_RX_EQ_BAND_3_B:
	हाल WM8996_DSP1_RX_EQ_BAND_3_C:
	हाल WM8996_DSP1_RX_EQ_BAND_3_PG:
	हाल WM8996_DSP1_RX_EQ_BAND_4_A:
	हाल WM8996_DSP1_RX_EQ_BAND_4_B:
	हाल WM8996_DSP1_RX_EQ_BAND_4_C:
	हाल WM8996_DSP1_RX_EQ_BAND_4_PG:
	हाल WM8996_DSP1_RX_EQ_BAND_5_A:
	हाल WM8996_DSP1_RX_EQ_BAND_5_B:
	हाल WM8996_DSP1_RX_EQ_BAND_5_PG:
	हाल WM8996_DSP2_TX_LEFT_VOLUME:
	हाल WM8996_DSP2_TX_RIGHT_VOLUME:
	हाल WM8996_DSP2_RX_LEFT_VOLUME:
	हाल WM8996_DSP2_RX_RIGHT_VOLUME:
	हाल WM8996_DSP2_TX_FILTERS:
	हाल WM8996_DSP2_RX_FILTERS_1:
	हाल WM8996_DSP2_RX_FILTERS_2:
	हाल WM8996_DSP2_DRC_1:
	हाल WM8996_DSP2_DRC_2:
	हाल WM8996_DSP2_DRC_3:
	हाल WM8996_DSP2_DRC_4:
	हाल WM8996_DSP2_DRC_5:
	हाल WM8996_DSP2_RX_EQ_GAINS_1:
	हाल WM8996_DSP2_RX_EQ_GAINS_2:
	हाल WM8996_DSP2_RX_EQ_BAND_1_A:
	हाल WM8996_DSP2_RX_EQ_BAND_1_B:
	हाल WM8996_DSP2_RX_EQ_BAND_1_PG:
	हाल WM8996_DSP2_RX_EQ_BAND_2_A:
	हाल WM8996_DSP2_RX_EQ_BAND_2_B:
	हाल WM8996_DSP2_RX_EQ_BAND_2_C:
	हाल WM8996_DSP2_RX_EQ_BAND_2_PG:
	हाल WM8996_DSP2_RX_EQ_BAND_3_A:
	हाल WM8996_DSP2_RX_EQ_BAND_3_B:
	हाल WM8996_DSP2_RX_EQ_BAND_3_C:
	हाल WM8996_DSP2_RX_EQ_BAND_3_PG:
	हाल WM8996_DSP2_RX_EQ_BAND_4_A:
	हाल WM8996_DSP2_RX_EQ_BAND_4_B:
	हाल WM8996_DSP2_RX_EQ_BAND_4_C:
	हाल WM8996_DSP2_RX_EQ_BAND_4_PG:
	हाल WM8996_DSP2_RX_EQ_BAND_5_A:
	हाल WM8996_DSP2_RX_EQ_BAND_5_B:
	हाल WM8996_DSP2_RX_EQ_BAND_5_PG:
	हाल WM8996_DAC1_MIXER_VOLUMES:
	हाल WM8996_DAC1_LEFT_MIXER_ROUTING:
	हाल WM8996_DAC1_RIGHT_MIXER_ROUTING:
	हाल WM8996_DAC2_MIXER_VOLUMES:
	हाल WM8996_DAC2_LEFT_MIXER_ROUTING:
	हाल WM8996_DAC2_RIGHT_MIXER_ROUTING:
	हाल WM8996_DSP1_TX_LEFT_MIXER_ROUTING:
	हाल WM8996_DSP1_TX_RIGHT_MIXER_ROUTING:
	हाल WM8996_DSP2_TX_LEFT_MIXER_ROUTING:
	हाल WM8996_DSP2_TX_RIGHT_MIXER_ROUTING:
	हाल WM8996_DSP_TX_MIXER_SELECT:
	हाल WM8996_DAC_SOFTMUTE:
	हाल WM8996_OVERSAMPLING:
	हाल WM8996_SIDETONE:
	हाल WM8996_GPIO_1:
	हाल WM8996_GPIO_2:
	हाल WM8996_GPIO_3:
	हाल WM8996_GPIO_4:
	हाल WM8996_GPIO_5:
	हाल WM8996_PULL_CONTROL_1:
	हाल WM8996_PULL_CONTROL_2:
	हाल WM8996_INTERRUPT_STATUS_1:
	हाल WM8996_INTERRUPT_STATUS_2:
	हाल WM8996_INTERRUPT_RAW_STATUS_2:
	हाल WM8996_INTERRUPT_STATUS_1_MASK:
	हाल WM8996_INTERRUPT_STATUS_2_MASK:
	हाल WM8996_INTERRUPT_CONTROL:
	हाल WM8996_LEFT_PDM_SPEAKER:
	हाल WM8996_RIGHT_PDM_SPEAKER:
	हाल WM8996_PDM_SPEAKER_MUTE_SEQUENCE:
	हाल WM8996_PDM_SPEAKER_VOLUME:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8996_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8996_SOFTWARE_RESET:
	हाल WM8996_CHIP_REVISION:
	हाल WM8996_LDO_1:
	हाल WM8996_LDO_2:
	हाल WM8996_INTERRUPT_STATUS_1:
	हाल WM8996_INTERRUPT_STATUS_2:
	हाल WM8996_INTERRUPT_RAW_STATUS_2:
	हाल WM8996_DC_SERVO_READBACK_0:
	हाल WM8996_DC_SERVO_2:
	हाल WM8996_DC_SERVO_6:
	हाल WM8996_DC_SERVO_7:
	हाल WM8996_FLL_CONTROL_6:
	हाल WM8996_MIC_DETECT_3:
	हाल WM8996_HEADPHONE_DETECT_1:
	हाल WM8996_HEADPHONE_DETECT_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक bclk_भागs[] = अणु
	1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96
पूर्ण;

अटल व्योम wm8996_update_bclk(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक aअगर, best, cur_val, bclk_rate, bclk_reg, i;

	/* Don't bother if we're in a low frequency idle mode that
	 * can't support audio.
	 */
	अगर (wm8996->sysclk < 64000)
		वापस;

	क्रम (aअगर = 0; aअगर < WM8996_AIFS; aअगर++) अणु
		चयन (aअगर) अणु
		हाल 0:
			bclk_reg = WM8996_AIF1_BCLK;
			अवरोध;
		हाल 1:
			bclk_reg = WM8996_AIF2_BCLK;
			अवरोध;
		पूर्ण

		bclk_rate = wm8996->bclk_rate[aअगर];

		/* Pick a भागisor क्रम BCLK as बंद as we can get to ideal */
		best = 0;
		क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
			cur_val = (wm8996->sysclk / bclk_भागs[i]) - bclk_rate;
			अगर (cur_val < 0) /* BCLK table is sorted */
				अवरोध;
			best = i;
		पूर्ण
		bclk_rate = wm8996->sysclk / bclk_भागs[best];
		dev_dbg(component->dev, "Using BCLK_DIV %d for actual BCLK %dHz\n",
			bclk_भागs[best], bclk_rate);

		snd_soc_component_update_bits(component, bclk_reg,
				    WM8996_AIF1_BCLK_DIV_MASK, best);
	पूर्ण
पूर्ण

अटल पूर्णांक wm8996_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Put the MICBIASes पूर्णांकo regulating mode */
		snd_soc_component_update_bits(component, WM8996_MICBIAS_1,
				    WM8996_MICB1_MODE, 0);
		snd_soc_component_update_bits(component, WM8996_MICBIAS_2,
				    WM8996_MICB2_MODE, 0);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8996->supplies),
						    wm8996->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			अगर (wm8996->pdata.lकरो_ena >= 0) अणु
				gpio_set_value_cansleep(wm8996->pdata.lकरो_ena,
							1);
				msleep(5);
			पूर्ण

			regcache_cache_only(wm8996->regmap, false);
			regcache_sync(wm8996->regmap);
		पूर्ण

		/* Bypass the MICBIASes क्रम lowest घातer */
		snd_soc_component_update_bits(component, WM8996_MICBIAS_1,
				    WM8996_MICB1_MODE, WM8996_MICB1_MODE);
		snd_soc_component_update_bits(component, WM8996_MICBIAS_2,
				    WM8996_MICB2_MODE, WM8996_MICB2_MODE);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		regcache_cache_only(wm8996->regmap, true);
		अगर (wm8996->pdata.lकरो_ena >= 0) अणु
			gpio_set_value_cansleep(wm8996->pdata.lकरो_ena, 0);
			regcache_cache_only(wm8996->regmap, true);
		पूर्ण
		regulator_bulk_disable(ARRAY_SIZE(wm8996->supplies),
				       wm8996->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8996_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक aअगरctrl = 0;
	पूर्णांक bclk = 0;
	पूर्णांक lrclk_tx = 0;
	पूर्णांक lrclk_rx = 0;
	पूर्णांक aअगरctrl_reg, bclk_reg, lrclk_tx_reg, lrclk_rx_reg;

	चयन (dai->id) अणु
	हाल 0:
		aअगरctrl_reg = WM8996_AIF1_CONTROL;
		bclk_reg = WM8996_AIF1_BCLK;
		lrclk_tx_reg = WM8996_AIF1_TX_LRCLK_2;
		lrclk_rx_reg = WM8996_AIF1_RX_LRCLK_2;
		अवरोध;
	हाल 1:
		aअगरctrl_reg = WM8996_AIF2_CONTROL;
		bclk_reg = WM8996_AIF2_BCLK;
		lrclk_tx_reg = WM8996_AIF2_TX_LRCLK_2;
		lrclk_rx_reg = WM8996_AIF2_RX_LRCLK_2;
		अवरोध;
	शेष:
		WARN(1, "Invalid dai id %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bclk |= WM8996_AIF1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk_tx |= WM8996_AIF1TX_LRCLK_INV;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bclk |= WM8996_AIF1_BCLK_INV;
		lrclk_tx |= WM8996_AIF1TX_LRCLK_INV;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_INV;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		lrclk_tx |= WM8996_AIF1TX_LRCLK_MSTR;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		bclk |= WM8996_AIF1_BCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		bclk |= WM8996_AIF1_BCLK_MSTR;
		lrclk_tx |= WM8996_AIF1TX_LRCLK_MSTR;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_MSTR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगरctrl |= 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगरctrl |= 2;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगरctrl |= 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, aअगरctrl_reg, WM8996_AIF1_FMT_MASK, aअगरctrl);
	snd_soc_component_update_bits(component, bclk_reg,
			    WM8996_AIF1_BCLK_INV | WM8996_AIF1_BCLK_MSTR,
			    bclk);
	snd_soc_component_update_bits(component, lrclk_tx_reg,
			    WM8996_AIF1TX_LRCLK_INV |
			    WM8996_AIF1TX_LRCLK_MSTR,
			    lrclk_tx);
	snd_soc_component_update_bits(component, lrclk_rx_reg,
			    WM8996_AIF1RX_LRCLK_INV |
			    WM8996_AIF1RX_LRCLK_MSTR,
			    lrclk_rx);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक dsp_भागs[] = अणु
	48000, 32000, 16000, 8000
पूर्ण;

अटल पूर्णांक wm8996_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक bits, i, bclk_rate, best;
	पूर्णांक aअगरdata = 0;
	पूर्णांक lrclk = 0;
	पूर्णांक dsp = 0;
	पूर्णांक aअगरdata_reg, lrclk_reg, dsp_shअगरt;

	चयन (dai->id) अणु
	हाल 0:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
		    (snd_soc_component_पढ़ो(component, WM8996_GPIO_1)) & WM8996_GP1_FN_MASK) अणु
			aअगरdata_reg = WM8996_AIF1RX_DATA_CONFIGURATION;
			lrclk_reg = WM8996_AIF1_RX_LRCLK_1;
		पूर्ण अन्यथा अणु
			aअगरdata_reg = WM8996_AIF1TX_DATA_CONFIGURATION_1;
			lrclk_reg = WM8996_AIF1_TX_LRCLK_1;
		पूर्ण
		dsp_shअगरt = 0;
		अवरोध;
	हाल 1:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
		    (snd_soc_component_पढ़ो(component, WM8996_GPIO_2)) & WM8996_GP2_FN_MASK) अणु
			aअगरdata_reg = WM8996_AIF2RX_DATA_CONFIGURATION;
			lrclk_reg = WM8996_AIF2_RX_LRCLK_1;
		पूर्ण अन्यथा अणु
			aअगरdata_reg = WM8996_AIF2TX_DATA_CONFIGURATION_1;
			lrclk_reg = WM8996_AIF2_TX_LRCLK_1;
		पूर्ण
		dsp_shअगरt = WM8996_DSP2_DIV_SHIFT;
		अवरोध;
	शेष:
		WARN(1, "Invalid dai id %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	bclk_rate = snd_soc_params_to_bclk(params);
	अगर (bclk_rate < 0) अणु
		dev_err(component->dev, "Unsupported BCLK rate: %d\n", bclk_rate);
		वापस bclk_rate;
	पूर्ण

	wm8996->bclk_rate[dai->id] = bclk_rate;
	wm8996->rx_rate[dai->id] = params_rate(params);

	/* Needs looking at क्रम TDM */
	bits = params_width(params);
	अगर (bits < 0)
		वापस bits;
	aअगरdata |= (bits << WM8996_AIF1TX_WL_SHIFT) | bits;

	best = 0;
	क्रम (i = 0; i < ARRAY_SIZE(dsp_भागs); i++) अणु
		अगर (असल(dsp_भागs[i] - params_rate(params)) <
		    असल(dsp_भागs[best] - params_rate(params)))
			best = i;
	पूर्ण
	dsp |= i << dsp_shअगरt;

	wm8996_update_bclk(component);

	lrclk = bclk_rate / params_rate(params);
	dev_dbg(dai->dev, "Using LRCLK rate %d for actual LRCLK %dHz\n",
		lrclk, bclk_rate / lrclk);

	snd_soc_component_update_bits(component, aअगरdata_reg,
			    WM8996_AIF1TX_WL_MASK |
			    WM8996_AIF1TX_SLOT_LEN_MASK,
			    aअगरdata);
	snd_soc_component_update_bits(component, lrclk_reg, WM8996_AIF1RX_RATE_MASK,
			    lrclk);
	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_2,
			    WM8996_DSP1_DIV_MASK << dsp_shअगरt, dsp);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8996_set_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक lfclk = 0;
	पूर्णांक rateभाग = 0;
	पूर्णांक sync = WM8996_REG_SYNC;
	पूर्णांक src;
	पूर्णांक old;

	अगर (freq == wm8996->sysclk && clk_id == wm8996->sysclk_src)
		वापस 0;

	/* Disable SYSCLK जबतक we reconfigure */
	old = snd_soc_component_पढ़ो(component, WM8996_AIF_CLOCKING_1) & WM8996_SYSCLK_ENA;
	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_ENA, 0);

	चयन (clk_id) अणु
	हाल WM8996_SYSCLK_MCLK1:
		wm8996->sysclk = freq;
		src = 0;
		अवरोध;
	हाल WM8996_SYSCLK_MCLK2:
		wm8996->sysclk = freq;
		src = 1;
		अवरोध;
	हाल WM8996_SYSCLK_FLL:
		wm8996->sysclk = freq;
		src = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	चयन (wm8996->sysclk) अणु
	हाल 5644800:
	हाल 6144000:
		snd_soc_component_update_bits(component, WM8996_AIF_RATE,
				    WM8996_SYSCLK_RATE, 0);
		अवरोध;
	हाल 22579200:
	हाल 24576000:
		rateभाग = WM8996_SYSCLK_DIV;
		wm8996->sysclk /= 2;
		fallthrough;
	हाल 11289600:
	हाल 12288000:
		snd_soc_component_update_bits(component, WM8996_AIF_RATE,
				    WM8996_SYSCLK_RATE, WM8996_SYSCLK_RATE);
		अवरोध;
	हाल 32000:
	हाल 32768:
		lfclk = WM8996_LFCLK_ENA;
		sync = 0;
		अवरोध;
	शेष:
		dev_warn(component->dev, "Unsupported clock rate %dHz\n",
			 wm8996->sysclk);
		वापस -EINVAL;
	पूर्ण

	wm8996_update_bclk(component);

	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_SRC_MASK | WM8996_SYSCLK_DIV_MASK,
			    src << WM8996_SYSCLK_SRC_SHIFT | rateभाग);
	snd_soc_component_update_bits(component, WM8996_CLOCKING_1, WM8996_LFCLK_ENA, lfclk);
	snd_soc_component_update_bits(component, WM8996_CONTROL_INTERFACE_1,
			    WM8996_REG_SYNC, sync);
	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_ENA, old);

	wm8996->sysclk_src = clk_id;

	वापस 0;
पूर्ण

काष्ठा _fll_भाग अणु
	u16 fll_fratio;
	u16 fll_outभाग;
	u16 fll_refclk_भाग;
	u16 fll_loop_gain;
	u16 fll_ref_freq;
	u16 n;
	u16 theta;
	u16 lambda;
पूर्ण;

अटल काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 fll_fratio;
	पूर्णांक ratio;
पूर्ण fll_fratios[] = अणु
	अणु       0,    64000, 4, 16 पूर्ण,
	अणु   64000,   128000, 3,  8 पूर्ण,
	अणु  128000,   256000, 2,  4 पूर्ण,
	अणु  256000,  1000000, 1,  2 पूर्ण,
	अणु 1000000, 13500000, 0,  1 पूर्ण,
पूर्ण;

अटल पूर्णांक fll_factors(काष्ठा _fll_भाग *fll_भाग, अचिन्हित पूर्णांक Fref,
		       अचिन्हित पूर्णांक Fout)
अणु
	अचिन्हित पूर्णांक target;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक fratio, gcd_fll;
	पूर्णांक i;

	/* Fref must be <=13.5MHz */
	भाग = 1;
	fll_भाग->fll_refclk_भाग = 0;
	जबतक ((Fref / भाग) > 13500000) अणु
		भाग *= 2;
		fll_भाग->fll_refclk_भाग++;

		अगर (भाग > 8) अणु
			pr_err("Can't scale %dMHz input down to <=13.5MHz\n",
			       Fref);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pr_debug("FLL Fref=%u Fout=%u\n", Fref, Fout);

	/* Apply the भागision क्रम our reमुख्यing calculations */
	Fref /= भाग;

	अगर (Fref >= 3000000)
		fll_भाग->fll_loop_gain = 5;
	अन्यथा
		fll_भाग->fll_loop_gain = 0;

	अगर (Fref >= 48000)
		fll_भाग->fll_ref_freq = 0;
	अन्यथा
		fll_भाग->fll_ref_freq = 1;

	/* Fvco should be 90-100MHz; करोn't check the upper bound */
	भाग = 2;
	जबतक (Fout * भाग < 90000000) अणु
		भाग++;
		अगर (भाग > 64) अणु
			pr_err("Unable to find FLL_OUTDIV for Fout=%uHz\n",
			       Fout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	target = Fout * भाग;
	fll_भाग->fll_outभाग = भाग - 1;

	pr_debug("FLL Fvco=%dHz\n", target);

	/* Find an appropraite FLL_FRATIO and factor it out of the target */
	क्रम (i = 0; i < ARRAY_SIZE(fll_fratios); i++) अणु
		अगर (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) अणु
			fll_भाग->fll_fratio = fll_fratios[i].fll_fratio;
			fratio = fll_fratios[i].ratio;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_fratios)) अणु
		pr_err("Unable to find FLL_FRATIO for Fref=%uHz\n", Fref);
		वापस -EINVAL;
	पूर्ण

	fll_भाग->n = target / (fratio * Fref);

	अगर (target % Fref == 0) अणु
		fll_भाग->theta = 0;
		fll_भाग->lambda = 0;
	पूर्ण अन्यथा अणु
		gcd_fll = gcd(target, fratio * Fref);

		fll_भाग->theta = (target - (fll_भाग->n * fratio * Fref))
			/ gcd_fll;
		fll_भाग->lambda = (fratio * Fref) / gcd_fll;
	पूर्ण

	pr_debug("FLL N=%x THETA=%x LAMBDA=%x\n",
		 fll_भाग->n, fll_भाग->theta, fll_भाग->lambda);
	pr_debug("FLL_FRATIO=%x FLL_OUTDIV=%x FLL_REFCLK_DIV=%x\n",
		 fll_भाग->fll_fratio, fll_भाग->fll_outभाग,
		 fll_भाग->fll_refclk_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8996_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	काष्ठा _fll_भाग fll_भाग;
	अचिन्हित दीर्घ समयout, समय_left;
	पूर्णांक ret, reg, retry;

	/* Any change? */
	अगर (source == wm8996->fll_src && Fref == wm8996->fll_fref &&
	    Fout == wm8996->fll_fout)
		वापस 0;

	अगर (Fout == 0) अणु
		dev_dbg(component->dev, "FLL disabled\n");

		wm8996->fll_fref = 0;
		wm8996->fll_fout = 0;

		snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_1,
				    WM8996_FLL_ENA, 0);

		wm8996_bg_disable(component);

		वापस 0;
	पूर्ण

	ret = fll_factors(&fll_भाग, Fref, Fout);
	अगर (ret != 0)
		वापस ret;

	चयन (source) अणु
	हाल WM8996_FLL_MCLK1:
		reg = 0;
		अवरोध;
	हाल WM8996_FLL_MCLK2:
		reg = 1;
		अवरोध;
	हाल WM8996_FLL_DACLRCLK1:
		reg = 2;
		अवरोध;
	हाल WM8996_FLL_BCLK1:
		reg = 3;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown FLL source %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	reg |= fll_भाग.fll_refclk_भाग << WM8996_FLL_REFCLK_DIV_SHIFT;
	reg |= fll_भाग.fll_ref_freq << WM8996_FLL_REF_FREQ_SHIFT;

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_5,
			    WM8996_FLL_REFCLK_DIV_MASK | WM8996_FLL_REF_FREQ |
			    WM8996_FLL_REFCLK_SRC_MASK, reg);

	reg = 0;
	अगर (fll_भाग.theta || fll_भाग.lambda)
		reg |= WM8996_FLL_EFS_ENA | (3 << WM8996_FLL_LFSR_SEL_SHIFT);
	अन्यथा
		reg |= 1 << WM8996_FLL_LFSR_SEL_SHIFT;
	snd_soc_component_ग_लिखो(component, WM8996_FLL_EFS_2, reg);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_2,
			    WM8996_FLL_OUTDIV_MASK |
			    WM8996_FLL_FRATIO_MASK,
			    (fll_भाग.fll_outभाग << WM8996_FLL_OUTDIV_SHIFT) |
			    (fll_भाग.fll_fratio));

	snd_soc_component_ग_लिखो(component, WM8996_FLL_CONTROL_3, fll_भाग.theta);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_4,
			    WM8996_FLL_N_MASK | WM8996_FLL_LOOP_GAIN_MASK,
			    (fll_भाग.n << WM8996_FLL_N_SHIFT) |
			    fll_भाग.fll_loop_gain);

	snd_soc_component_ग_लिखो(component, WM8996_FLL_EFS_1, fll_भाग.lambda);

	/* Enable the bandgap अगर it's not alपढ़ोy enabled */
	ret = snd_soc_component_पढ़ो(component, WM8996_FLL_CONTROL_1);
	अगर (!(ret & WM8996_FLL_ENA))
		wm8996_bg_enable(component);

	/* Clear any pending completions (eg, from failed startups) */
	try_रुको_क्रम_completion(&wm8996->fll_lock);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_1,
			    WM8996_FLL_ENA, WM8996_FLL_ENA);

	/* The FLL supports live reconfiguration - kick that in हाल we were
	 * alपढ़ोy enabled.
	 */
	snd_soc_component_ग_लिखो(component, WM8996_FLL_CONTROL_6, WM8996_FLL_SWITCH_CLK);

	/* Wait क्रम the FLL to lock, using the पूर्णांकerrupt अगर possible */
	अगर (Fref > 1000000)
		समयout = usecs_to_jअगरfies(300);
	अन्यथा
		समयout = msecs_to_jअगरfies(2);

	/* Allow substantially दीर्घer अगर we've actually got the IRQ, poll
	 * at a slightly higher rate अगर we करोn't.
	 */
	अगर (i2c->irq)
		समयout *= 10;
	अन्यथा
		/* ensure समयout of atleast 1 jअगरfies */
		समयout = (समयout/2) ? : 1;

	क्रम (retry = 0; retry < 10; retry++) अणु
		समय_left = रुको_क्रम_completion_समयout(&wm8996->fll_lock,
							समयout);
		अगर (समय_left != 0) अणु
			WARN_ON(!i2c->irq);
			ret = 1;
			अवरोध;
		पूर्ण

		ret = snd_soc_component_पढ़ो(component, WM8996_INTERRUPT_RAW_STATUS_2);
		अगर (ret & WM8996_FLL_LOCK_STS)
			अवरोध;
	पूर्ण
	अगर (retry == 10) अणु
		dev_err(component->dev, "Timed out waiting for FLL\n");
		ret = -ETIMEDOUT;
	पूर्ण

	dev_dbg(component->dev, "FLL configured for %dHz->%dHz\n", Fref, Fout);

	wm8996->fll_fref = Fref;
	wm8996->fll_fout = Fout;
	wm8996->fll_src = source;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल व्योम wm8996_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8996_priv *wm8996 = gpiochip_get_data(chip);

	regmap_update_bits(wm8996->regmap, WM8996_GPIO_1 + offset,
			   WM8996_GP1_LVL, !!value << WM8996_GP1_LVL_SHIFT);
पूर्ण

अटल पूर्णांक wm8996_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8996_priv *wm8996 = gpiochip_get_data(chip);
	पूर्णांक val;

	val = (1 << WM8996_GP1_FN_SHIFT) | (!!value << WM8996_GP1_LVL_SHIFT);

	वापस regmap_update_bits(wm8996->regmap, WM8996_GPIO_1 + offset,
				  WM8996_GP1_FN_MASK | WM8996_GP1_सूची |
				  WM8996_GP1_LVL, val);
पूर्ण

अटल पूर्णांक wm8996_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8996_priv *wm8996 = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm8996->regmap, WM8996_GPIO_1 + offset, &reg);
	अगर (ret < 0)
		वापस ret;

	वापस (reg & WM8996_GP1_LVL) != 0;
पूर्ण

अटल पूर्णांक wm8996_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8996_priv *wm8996 = gpiochip_get_data(chip);

	वापस regmap_update_bits(wm8996->regmap, WM8996_GPIO_1 + offset,
				  WM8996_GP1_FN_MASK | WM8996_GP1_सूची,
				  (1 << WM8996_GP1_FN_SHIFT) |
				  (1 << WM8996_GP1_सूची_SHIFT));
पूर्ण

अटल स्थिर काष्ठा gpio_chip wm8996_ढाँचा_chip = अणु
	.label			= "wm8996",
	.owner			= THIS_MODULE,
	.direction_output	= wm8996_gpio_direction_out,
	.set			= wm8996_gpio_set,
	.direction_input	= wm8996_gpio_direction_in,
	.get			= wm8996_gpio_get,
	.can_sleep		= 1,
पूर्ण;

अटल व्योम wm8996_init_gpio(काष्ठा wm8996_priv *wm8996)
अणु
	पूर्णांक ret;

	wm8996->gpio_chip = wm8996_ढाँचा_chip;
	wm8996->gpio_chip.ngpio = 5;
	wm8996->gpio_chip.parent = wm8996->dev;

	अगर (wm8996->pdata.gpio_base)
		wm8996->gpio_chip.base = wm8996->pdata.gpio_base;
	अन्यथा
		wm8996->gpio_chip.base = -1;

	ret = gpiochip_add_data(&wm8996->gpio_chip, wm8996);
	अगर (ret != 0)
		dev_err(wm8996->dev, "Failed to add GPIOs: %d\n", ret);
पूर्ण

अटल व्योम wm8996_मुक्त_gpio(काष्ठा wm8996_priv *wm8996)
अणु
	gpiochip_हटाओ(&wm8996->gpio_chip);
पूर्ण
#अन्यथा
अटल व्योम wm8996_init_gpio(काष्ठा wm8996_priv *wm8996)
अणु
पूर्ण

अटल व्योम wm8996_मुक्त_gpio(काष्ठा wm8996_priv *wm8996)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * wm8996_detect - Enable शेष WM8996 jack detection
 * @component: ASoC component
 * @jack: jack poपूर्णांकer
 * @polarity_cb: polarity callback
 *
 * The WM8996 has advanced accessory detection support क्रम headsets.
 * This function provides a शेष implementation which पूर्णांकegrates
 * the majority of this functionality with minimal user configuration.
 *
 * This will detect headset, headphone and लघु circuit button and
 * will also detect inverted microphone ground connections and update
 * the polarity of the connections.
 */
पूर्णांक wm8996_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		  wm8996_polarity_fn polarity_cb)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	wm8996->jack = jack;
	wm8996->detecting = true;
	wm8996->polarity_cb = polarity_cb;
	wm8996->jack_flips = 0;

	अगर (wm8996->polarity_cb)
		wm8996->polarity_cb(component, 0);

	/* Clear discarge to aव्योम noise during detection */
	snd_soc_component_update_bits(component, WM8996_MICBIAS_1,
			    WM8996_MICB1_DISCH, 0);
	snd_soc_component_update_bits(component, WM8996_MICBIAS_2,
			    WM8996_MICB2_DISCH, 0);

	/* LDO2 घातers the microphones, SYSCLK घड़ीs detection */
	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "LDO2");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "SYSCLK");

	snd_soc_dapm_mutex_unlock(dapm);

	/* We start off just enabling microphone detection - even a
	 * plain headphone will trigger detection.
	 */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
			    WM8996_MICD_ENA, WM8996_MICD_ENA);

	/* Slowest detection rate, gives debounce क्रम initial detection */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
			    WM8996_MICD_RATE_MASK,
			    WM8996_MICD_RATE_MASK);

	/* Enable पूर्णांकerrupts and we're off */
	snd_soc_component_update_bits(component, WM8996_INTERRUPT_STATUS_2_MASK,
			    WM8996_IM_MICD_EINT | WM8996_HP_DONE_EINT, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8996_detect);

अटल व्योम wm8996_hpdet_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, reg, report;

	/* Assume headphone in error conditions; we need to report
	 * something or we stall our state machine.
	 */
	report = SND_JACK_HEADPHONE;

	reg = snd_soc_component_पढ़ो(component, WM8996_HEADPHONE_DETECT_2);
	अगर (reg < 0) अणु
		dev_err(component->dev, "Failed to read HPDET status\n");
		जाओ out;
	पूर्ण

	अगर (!(reg & WM8996_HP_DONE)) अणु
		dev_err(component->dev, "Got HPDET IRQ but HPDET is busy\n");
		जाओ out;
	पूर्ण

	val = reg & WM8996_HP_LVL_MASK;

	dev_dbg(component->dev, "HPDET measured %d ohms\n", val);

	/* If we've got high enough impedence then report as line,
	 * otherwise assume headphone.
	 */
	अगर (val >= 126)
		report = SND_JACK_LINEOUT;
	अन्यथा
		report = SND_JACK_HEADPHONE;

out:
	अगर (wm8996->jack_mic)
		report |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(wm8996->jack, report,
			    SND_JACK_LINEOUT | SND_JACK_HEADSET);

	wm8996->detecting = false;

	/* If the output isn't running re-clamp it */
	अगर (!(snd_soc_component_पढ़ो(component, WM8996_POWER_MANAGEMENT_1) &
	      (WM8996_HPOUT1L_ENA | WM8996_HPOUT1R_RMV_SHORT)))
		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1,
				    WM8996_HPOUT1L_RMV_SHORT |
				    WM8996_HPOUT1R_RMV_SHORT, 0);

	/* Go back to looking at the microphone */
	snd_soc_component_update_bits(component, WM8996_ACCESSORY_DETECT_MODE_1,
			    WM8996_JD_MODE_MASK, 0);
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1, WM8996_MICD_ENA,
			    WM8996_MICD_ENA);

	snd_soc_dapm_disable_pin(dapm, "Bandgap");
	snd_soc_dapm_sync(dapm);
पूर्ण

अटल व्योम wm8996_hpdet_start(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Unclamp the output, we can't measure while we're लघुing it */
	snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1,
			    WM8996_HPOUT1L_RMV_SHORT |
			    WM8996_HPOUT1R_RMV_SHORT,
			    WM8996_HPOUT1L_RMV_SHORT |
			    WM8996_HPOUT1R_RMV_SHORT);

	/* We need bandgap क्रम HPDET */
	snd_soc_dapm_क्रमce_enable_pin(dapm, "Bandgap");
	snd_soc_dapm_sync(dapm);

	/* Go पूर्णांकo headphone detect left mode */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1, WM8996_MICD_ENA, 0);
	snd_soc_component_update_bits(component, WM8996_ACCESSORY_DETECT_MODE_1,
			    WM8996_JD_MODE_MASK, 1);

	/* Trigger a measurement */
	snd_soc_component_update_bits(component, WM8996_HEADPHONE_DETECT_1,
			    WM8996_HP_POLL, WM8996_HP_POLL);
पूर्ण

अटल व्योम wm8996_report_headphone(काष्ठा snd_soc_component *component)
अणु
	dev_dbg(component->dev, "Headphone detected\n");
	wm8996_hpdet_start(component);

	/* Increase the detection rate a bit क्रम responsiveness. */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
			    WM8996_MICD_RATE_MASK |
			    WM8996_MICD_BIAS_STARTTIME_MASK,
			    7 << WM8996_MICD_RATE_SHIFT |
			    7 << WM8996_MICD_BIAS_STARTTIME_SHIFT);
पूर्ण

अटल व्योम wm8996_micd(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, reg;

	val = snd_soc_component_पढ़ो(component, WM8996_MIC_DETECT_3);

	dev_dbg(component->dev, "Microphone event: %x\n", val);

	अगर (!(val & WM8996_MICD_VALID)) अणु
		dev_warn(component->dev, "Microphone detection state invalid\n");
		वापस;
	पूर्ण

	/* No accessory, reset everything and report removal */
	अगर (!(val & WM8996_MICD_STS)) अणु
		dev_dbg(component->dev, "Jack removal detected\n");
		wm8996->jack_mic = false;
		wm8996->detecting = true;
		wm8996->jack_flips = 0;
		snd_soc_jack_report(wm8996->jack, 0,
				    SND_JACK_LINEOUT | SND_JACK_HEADSET |
				    SND_JACK_BTN_0);

		snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
				    WM8996_MICD_RATE_MASK |
				    WM8996_MICD_BIAS_STARTTIME_MASK,
				    WM8996_MICD_RATE_MASK |
				    9 << WM8996_MICD_BIAS_STARTTIME_SHIFT);
		वापस;
	पूर्ण

	/* If the measurement is very high we've got a microphone,
	 * either we just detected one or अगर we alपढ़ोy reported then
	 * we've got a button release event.
	 */
	अगर (val & 0x400) अणु
		अगर (wm8996->detecting) अणु
			dev_dbg(component->dev, "Microphone detected\n");
			wm8996->jack_mic = true;
			wm8996_hpdet_start(component);

			/* Increase poll rate to give better responsiveness
			 * क्रम buttons */
			snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
					    WM8996_MICD_RATE_MASK |
					    WM8996_MICD_BIAS_STARTTIME_MASK,
					    5 << WM8996_MICD_RATE_SHIFT |
					    7 << WM8996_MICD_BIAS_STARTTIME_SHIFT);
		पूर्ण अन्यथा अणु
			dev_dbg(component->dev, "Mic button up\n");
			snd_soc_jack_report(wm8996->jack, 0, SND_JACK_BTN_0);
		पूर्ण

		वापस;
	पूर्ण

	/* If we detected a lower impedence during initial startup
	 * then we probably have the wrong polarity, flip it.  Don't
	 * करो this क्रम the lowest impedences to speed up detection of
	 * plain headphones.  If both polarities report a low
	 * impedence then give up and report headphones.
	 */
	अगर (wm8996->detecting && (val & 0x3f0)) अणु
		wm8996->jack_flips++;

		अगर (wm8996->jack_flips > 1) अणु
			wm8996_report_headphone(component);
			वापस;
		पूर्ण

		reg = snd_soc_component_पढ़ो(component, WM8996_ACCESSORY_DETECT_MODE_2);
		reg ^= WM8996_HPOUT1FB_SRC | WM8996_MICD_SRC |
			WM8996_MICD_BIAS_SRC;
		snd_soc_component_update_bits(component, WM8996_ACCESSORY_DETECT_MODE_2,
				    WM8996_HPOUT1FB_SRC | WM8996_MICD_SRC |
				    WM8996_MICD_BIAS_SRC, reg);

		अगर (wm8996->polarity_cb)
			wm8996->polarity_cb(component,
					    (reg & WM8996_MICD_SRC) != 0);

		dev_dbg(component->dev, "Set microphone polarity to %d\n",
			(reg & WM8996_MICD_SRC) != 0);

		वापस;
	पूर्ण

	/* Don't distinguish between buttons, just report any low
	 * impedence as BTN_0.
	 */
	अगर (val & 0x3fc) अणु
		अगर (wm8996->jack_mic) अणु
			dev_dbg(component->dev, "Mic button detected\n");
			snd_soc_jack_report(wm8996->jack, SND_JACK_BTN_0,
					    SND_JACK_BTN_0);
		पूर्ण अन्यथा अगर (wm8996->detecting) अणु
			wm8996_report_headphone(component);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t wm8996_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	पूर्णांक irq_val;

	irq_val = snd_soc_component_पढ़ो(component, WM8996_INTERRUPT_STATUS_2);
	अगर (irq_val < 0) अणु
		dev_err(component->dev, "Failed to read IRQ status: %d\n",
			irq_val);
		वापस IRQ_NONE;
	पूर्ण
	irq_val &= ~snd_soc_component_पढ़ो(component, WM8996_INTERRUPT_STATUS_2_MASK);

	अगर (!irq_val)
		वापस IRQ_NONE;

	snd_soc_component_ग_लिखो(component, WM8996_INTERRUPT_STATUS_2, irq_val);

	अगर (irq_val & (WM8996_DCS_DONE_01_EINT | WM8996_DCS_DONE_23_EINT)) अणु
		dev_dbg(component->dev, "DC servo IRQ\n");
		complete(&wm8996->dcs_करोne);
	पूर्ण

	अगर (irq_val & WM8996_FIFOS_ERR_EINT)
		dev_err(component->dev, "Digital core FIFO error\n");

	अगर (irq_val & WM8996_FLL_LOCK_EINT) अणु
		dev_dbg(component->dev, "FLL locked\n");
		complete(&wm8996->fll_lock);
	पूर्ण

	अगर (irq_val & WM8996_MICD_EINT)
		wm8996_micd(component);

	अगर (irq_val & WM8996_HP_DONE_EINT)
		wm8996_hpdet_irq(component);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8996_edge_irq(पूर्णांक irq, व्योम *data)
अणु
	irqवापस_t ret = IRQ_NONE;
	irqवापस_t val;

	करो अणु
		val = wm8996_irq(irq, data);
		अगर (val != IRQ_NONE)
			ret = val;
	पूर्ण जबतक (val != IRQ_NONE);

	वापस ret;
पूर्ण

अटल व्योम wm8996_retune_mobile_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8996_pdata *pdata = &wm8996->pdata;

	काष्ठा snd_kcontrol_new controls[] = अणु
		SOC_ENUM_EXT("DSP1 EQ Mode",
			     wm8996->retune_mobile_क्रमागत,
			     wm8996_get_retune_mobile_क्रमागत,
			     wm8996_put_retune_mobile_क्रमागत),
		SOC_ENUM_EXT("DSP2 EQ Mode",
			     wm8996->retune_mobile_क्रमागत,
			     wm8996_get_retune_mobile_क्रमागत,
			     wm8996_put_retune_mobile_क्रमागत),
	पूर्ण;
	पूर्णांक ret, i, j;
	स्थिर अक्षर **t;

	/* We need an array of texts क्रम the क्रमागत API but the number
	 * of texts is likely to be less than the number of
	 * configurations due to the sample rate dependency of the
	 * configurations. */
	wm8996->num_retune_mobile_texts = 0;
	wm8996->retune_mobile_texts = शून्य;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		क्रम (j = 0; j < wm8996->num_retune_mobile_texts; j++) अणु
			अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
				   wm8996->retune_mobile_texts[j]) == 0)
				अवरोध;
		पूर्ण

		अगर (j != wm8996->num_retune_mobile_texts)
			जारी;

		/* Expand the array... */
		t = kपुनः_स्मृति(wm8996->retune_mobile_texts,
			     माप(अक्षर *) * 
			     (wm8996->num_retune_mobile_texts + 1),
			     GFP_KERNEL);
		अगर (t == शून्य)
			जारी;

		/* ...store the new entry... */
		t[wm8996->num_retune_mobile_texts] = 
			pdata->retune_mobile_cfgs[i].name;

		/* ...and remember the new version. */
		wm8996->num_retune_mobile_texts++;
		wm8996->retune_mobile_texts = t;
	पूर्ण

	dev_dbg(component->dev, "Allocated %d unique ReTune Mobile names\n",
		wm8996->num_retune_mobile_texts);

	wm8996->retune_mobile_क्रमागत.items = wm8996->num_retune_mobile_texts;
	wm8996->retune_mobile_क्रमागत.texts = wm8996->retune_mobile_texts;

	ret = snd_soc_add_component_controls(component, controls, ARRAY_SIZE(controls));
	अगर (ret != 0)
		dev_err(component->dev,
			"Failed to add ReTune Mobile controls: %d\n", ret);
पूर्ण

अटल स्थिर काष्ठा regmap_config wm8996_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.max_रेजिस्टर = WM8996_MAX_REGISTER,
	.reg_शेषs = wm8996_reg,
	.num_reg_शेषs = ARRAY_SIZE(wm8996_reg),
	.अस्थिर_reg = wm8996_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm8996_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक wm8996_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	काष्ठा wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	पूर्णांक irq_flags;

	wm8996->component = component;

	init_completion(&wm8996->dcs_करोne);
	init_completion(&wm8996->fll_lock);

	अगर (wm8996->pdata.num_retune_mobile_cfgs)
		wm8996_retune_mobile_pdata(component);
	अन्यथा
		snd_soc_add_component_controls(component, wm8996_eq_controls,
				     ARRAY_SIZE(wm8996_eq_controls));

	अगर (i2c->irq) अणु
		अगर (wm8996->pdata.irq_flags)
			irq_flags = wm8996->pdata.irq_flags;
		अन्यथा
			irq_flags = IRQF_TRIGGER_LOW;

		irq_flags |= IRQF_ONESHOT;

		अगर (irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
			ret = request_thपढ़ोed_irq(i2c->irq, शून्य,
						   wm8996_edge_irq,
						   irq_flags, "wm8996", component);
		अन्यथा
			ret = request_thपढ़ोed_irq(i2c->irq, शून्य, wm8996_irq,
						   irq_flags, "wm8996", component);

		अगर (ret == 0) अणु
			/* Unmask the पूर्णांकerrupt */
			snd_soc_component_update_bits(component, WM8996_INTERRUPT_CONTROL,
					    WM8996_IM_IRQ, 0);

			/* Enable error reporting and DC servo status */
			snd_soc_component_update_bits(component,
					    WM8996_INTERRUPT_STATUS_2_MASK,
					    WM8996_IM_DCS_DONE_23_EINT |
					    WM8996_IM_DCS_DONE_01_EINT |
					    WM8996_IM_FLL_LOCK_EINT |
					    WM8996_IM_FIFOS_ERR_EINT,
					    0);
		पूर्ण अन्यथा अणु
			dev_err(component->dev, "Failed to request IRQ: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wm8996_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);

	snd_soc_component_update_bits(component, WM8996_INTERRUPT_CONTROL,
			    WM8996_IM_IRQ, WM8996_IM_IRQ);

	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8996 = अणु
	.probe			= wm8996_probe,
	.हटाओ			= wm8996_हटाओ,
	.set_bias_level		= wm8996_set_bias_level,
	.seq_notअगरier		= wm8996_seq_notअगरier,
	.controls		= wm8996_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8996_snd_controls),
	.dapm_widमाला_लो		= wm8996_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8996_dapm_widमाला_लो),
	.dapm_routes		= wm8996_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8996_dapm_routes),
	.set_pll		= wm8996_set_fll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,

पूर्ण;

#घोषणा WM8996_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
		      SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
		      SNDRV_PCM_RATE_48000)
#घोषणा WM8996_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8996_dai_ops = अणु
	.set_fmt = wm8996_set_fmt,
	.hw_params = wm8996_hw_params,
	.set_sysclk = wm8996_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8996_dai[] = अणु
	अणु
		.name = "wm8996-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 6,
			.rates = WM8996_RATES,
			.क्रमmats = WM8996_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF1 Capture",
			 .channels_min = 1,
			 .channels_max = 6,
			 .rates = WM8996_RATES,
			 .क्रमmats = WM8996_FORMATS,
			 .sig_bits = 24,
		 पूर्ण,
		.ops = &wm8996_dai_ops,
	पूर्ण,
	अणु
		.name = "wm8996-aif2",
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8996_RATES,
			.क्रमmats = WM8996_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF2 Capture",
			 .channels_min = 1,
			 .channels_max = 2,
			 .rates = WM8996_RATES,
			 .क्रमmats = WM8996_FORMATS,
			.sig_bits = 24,
		 पूर्ण,
		.ops = &wm8996_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8996_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8996_priv *wm8996;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक reg;

	wm8996 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8996_priv),
			      GFP_KERNEL);
	अगर (wm8996 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8996);
	wm8996->dev = &i2c->dev;

	अगर (dev_get_platdata(&i2c->dev))
		स_नकल(&wm8996->pdata, dev_get_platdata(&i2c->dev),
		       माप(wm8996->pdata));

	अगर (wm8996->pdata.lकरो_ena > 0) अणु
		ret = gpio_request_one(wm8996->pdata.lकरो_ena,
				       GPIOF_OUT_INIT_LOW, "WM8996 ENA");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request GPIO %d: %d\n",
				wm8996->pdata.lकरो_ena, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm8996->supplies); i++)
		wm8996->supplies[i].supply = wm8996_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8996->supplies),
				      wm8996->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		जाओ err_gpio;
	पूर्ण

	wm8996->disable_nb[0].notअगरier_call = wm8996_regulator_event_0;
	wm8996->disable_nb[1].notअगरier_call = wm8996_regulator_event_1;
	wm8996->disable_nb[2].notअगरier_call = wm8996_regulator_event_2;

	/* This should really be moved पूर्णांकo the regulator core */
	क्रम (i = 0; i < ARRAY_SIZE(wm8996->supplies); i++) अणु
		ret = devm_regulator_रेजिस्टर_notअगरier(
						wm8996->supplies[i].consumer,
						&wm8996->disable_nb[i]);
		अगर (ret != 0) अणु
			dev_err(&i2c->dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8996->supplies),
				    wm8996->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_gpio;
	पूर्ण

	अगर (wm8996->pdata.lकरो_ena > 0) अणु
		gpio_set_value_cansleep(wm8996->pdata.lकरो_ena, 1);
		msleep(5);
	पूर्ण

	wm8996->regmap = devm_regmap_init_i2c(i2c, &wm8996_regmap);
	अगर (IS_ERR(wm8996->regmap)) अणु
		ret = PTR_ERR(wm8996->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	ret = regmap_पढ़ो(wm8996->regmap, WM8996_SOFTWARE_RESET, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		जाओ err_regmap;
	पूर्ण
	अगर (reg != 0x8915) अणु
		dev_err(&i2c->dev, "Device is not a WM8996, ID %x\n", reg);
		ret = -EINVAL;
		जाओ err_regmap;
	पूर्ण

	ret = regmap_पढ़ो(wm8996->regmap, WM8996_CHIP_REVISION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read device revision: %d\n",
			ret);
		जाओ err_regmap;
	पूर्ण

	dev_info(&i2c->dev, "revision %c\n",
		 (reg & WM8996_CHIP_REV_MASK) + 'A');

	अगर (wm8996->pdata.lकरो_ena > 0) अणु
		gpio_set_value_cansleep(wm8996->pdata.lकरो_ena, 0);
		regcache_cache_only(wm8996->regmap, true);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(wm8996->regmap, WM8996_SOFTWARE_RESET,
				   0x8915);
		अगर (ret != 0) अणु
			dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
			जाओ err_regmap;
		पूर्ण
	पूर्ण

	regulator_bulk_disable(ARRAY_SIZE(wm8996->supplies), wm8996->supplies);

	/* Apply platक्रमm data settings */
	regmap_update_bits(wm8996->regmap, WM8996_LINE_INPUT_CONTROL,
			   WM8996_INL_MODE_MASK | WM8996_INR_MODE_MASK,
			   wm8996->pdata.inl_mode << WM8996_INL_MODE_SHIFT |
			   wm8996->pdata.inr_mode);

	क्रम (i = 0; i < ARRAY_SIZE(wm8996->pdata.gpio_शेष); i++) अणु
		अगर (!wm8996->pdata.gpio_शेष[i])
			जारी;

		regmap_ग_लिखो(wm8996->regmap, WM8996_GPIO_1 + i,
			     wm8996->pdata.gpio_शेष[i] & 0xffff);
	पूर्ण

	अगर (wm8996->pdata.spkmute_seq)
		regmap_update_bits(wm8996->regmap,
				   WM8996_PDM_SPEAKER_MUTE_SEQUENCE,
				   WM8996_SPK_MUTE_ENDIAN |
				   WM8996_SPK_MUTE_SEQ1_MASK,
				   wm8996->pdata.spkmute_seq);

	regmap_update_bits(wm8996->regmap, WM8996_ACCESSORY_DETECT_MODE_2,
			   WM8996_MICD_BIAS_SRC | WM8996_HPOUT1FB_SRC |
			   WM8996_MICD_SRC, wm8996->pdata.micdet_def);

	/* Latch volume update bits */
	regmap_update_bits(wm8996->regmap, WM8996_LEFT_LINE_INPUT_VOLUME,
			   WM8996_IN1_VU, WM8996_IN1_VU);
	regmap_update_bits(wm8996->regmap, WM8996_RIGHT_LINE_INPUT_VOLUME,
			   WM8996_IN1_VU, WM8996_IN1_VU);

	regmap_update_bits(wm8996->regmap, WM8996_DAC1_LEFT_VOLUME,
			   WM8996_DAC1_VU, WM8996_DAC1_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DAC1_RIGHT_VOLUME,
			   WM8996_DAC1_VU, WM8996_DAC1_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DAC2_LEFT_VOLUME,
			   WM8996_DAC2_VU, WM8996_DAC2_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DAC2_RIGHT_VOLUME,
			   WM8996_DAC2_VU, WM8996_DAC2_VU);

	regmap_update_bits(wm8996->regmap, WM8996_OUTPUT1_LEFT_VOLUME,
			   WM8996_DAC1_VU, WM8996_DAC1_VU);
	regmap_update_bits(wm8996->regmap, WM8996_OUTPUT1_RIGHT_VOLUME,
			   WM8996_DAC1_VU, WM8996_DAC1_VU);
	regmap_update_bits(wm8996->regmap, WM8996_OUTPUT2_LEFT_VOLUME,
			   WM8996_DAC2_VU, WM8996_DAC2_VU);
	regmap_update_bits(wm8996->regmap, WM8996_OUTPUT2_RIGHT_VOLUME,
			   WM8996_DAC2_VU, WM8996_DAC2_VU);

	regmap_update_bits(wm8996->regmap, WM8996_DSP1_TX_LEFT_VOLUME,
			   WM8996_DSP1TX_VU, WM8996_DSP1TX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP1_TX_RIGHT_VOLUME,
			   WM8996_DSP1TX_VU, WM8996_DSP1TX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP2_TX_LEFT_VOLUME,
			   WM8996_DSP2TX_VU, WM8996_DSP2TX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP2_TX_RIGHT_VOLUME,
			   WM8996_DSP2TX_VU, WM8996_DSP2TX_VU);

	regmap_update_bits(wm8996->regmap, WM8996_DSP1_RX_LEFT_VOLUME,
			   WM8996_DSP1RX_VU, WM8996_DSP1RX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP1_RX_RIGHT_VOLUME,
			   WM8996_DSP1RX_VU, WM8996_DSP1RX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP2_RX_LEFT_VOLUME,
			   WM8996_DSP2RX_VU, WM8996_DSP2RX_VU);
	regmap_update_bits(wm8996->regmap, WM8996_DSP2_RX_RIGHT_VOLUME,
			   WM8996_DSP2RX_VU, WM8996_DSP2RX_VU);

	/* No support currently क्रम the underघड़ीed TDM modes and
	 * pick a शेष TDM layout with each channel pair working with
	 * slots 0 and 1. */
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_0_CONFIGURATION,
			   WM8996_AIF1RX_CHAN0_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN0_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_1_CONFIGURATION,
			   WM8996_AIF1RX_CHAN1_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN1_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN1_SLOTS_SHIFT | 1);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_2_CONFIGURATION,
			   WM8996_AIF1RX_CHAN2_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN2_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN2_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_3_CONFIGURATION,
			   WM8996_AIF1RX_CHAN3_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN3_SLOTS_SHIFT | 1);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_4_CONFIGURATION,
			   WM8996_AIF1RX_CHAN4_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN4_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1RX_CHANNEL_5_CONFIGURATION,
			   WM8996_AIF1RX_CHAN5_SLOTS_MASK |
			   WM8996_AIF1RX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1RX_CHAN5_SLOTS_SHIFT | 1);

	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF2RX_CHANNEL_0_CONFIGURATION,
			   WM8996_AIF2RX_CHAN0_SLOTS_MASK |
			   WM8996_AIF2RX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF2RX_CHAN0_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF2RX_CHANNEL_1_CONFIGURATION,
			   WM8996_AIF2RX_CHAN1_SLOTS_MASK |
			   WM8996_AIF2RX_CHAN1_START_SLOT_MASK,
			   1 << WM8996_AIF2RX_CHAN1_SLOTS_SHIFT | 1);

	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_0_CONFIGURATION,
			   WM8996_AIF1TX_CHAN0_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN0_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_1_CONFIGURATION,
			   WM8996_AIF1TX_CHAN1_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN1_SLOTS_SHIFT | 1);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_2_CONFIGURATION,
			   WM8996_AIF1TX_CHAN2_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN2_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_3_CONFIGURATION,
			   WM8996_AIF1TX_CHAN3_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN3_SLOTS_SHIFT | 1);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_4_CONFIGURATION,
			   WM8996_AIF1TX_CHAN4_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN4_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_5_CONFIGURATION,
			   WM8996_AIF1TX_CHAN5_SLOTS_MASK |
			   WM8996_AIF1TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN5_SLOTS_SHIFT | 1);

	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF2TX_CHANNEL_0_CONFIGURATION,
			   WM8996_AIF2TX_CHAN0_SLOTS_MASK |
			   WM8996_AIF2TX_CHAN0_START_SLOT_MASK,
			   1 << WM8996_AIF2TX_CHAN0_SLOTS_SHIFT | 0);
	regmap_update_bits(wm8996->regmap,
			   WM8996_AIF1TX_CHANNEL_1_CONFIGURATION,
			   WM8996_AIF2TX_CHAN1_SLOTS_MASK |
			   WM8996_AIF2TX_CHAN1_START_SLOT_MASK,
			   1 << WM8996_AIF1TX_CHAN1_SLOTS_SHIFT | 1);

	/* If the TX LRCLK pins are not in LRCLK mode configure the
	 * AIFs to source their घड़ीs from the RX LRCLKs.
	 */
	ret = regmap_पढ़ो(wm8996->regmap, WM8996_GPIO_1, &reg);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read GPIO1: %d\n", ret);
		जाओ err_regmap;
	पूर्ण

	अगर (reg & WM8996_GP1_FN_MASK)
		regmap_update_bits(wm8996->regmap, WM8996_AIF1_TX_LRCLK_2,
				   WM8996_AIF1TX_LRCLK_MODE,
				   WM8996_AIF1TX_LRCLK_MODE);

	ret = regmap_पढ़ो(wm8996->regmap, WM8996_GPIO_2, &reg);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read GPIO2: %d\n", ret);
		जाओ err_regmap;
	पूर्ण

	अगर (reg & WM8996_GP2_FN_MASK)
		regmap_update_bits(wm8996->regmap, WM8996_AIF2_TX_LRCLK_2,
				   WM8996_AIF2TX_LRCLK_MODE,
				   WM8996_AIF2TX_LRCLK_MODE);

	wm8996_init_gpio(wm8996);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_wm8996, wm8996_dai,
				     ARRAY_SIZE(wm8996_dai));
	अगर (ret < 0)
		जाओ err_gpiolib;

	वापस ret;

err_gpiolib:
	wm8996_मुक्त_gpio(wm8996);
err_regmap:
err_enable:
	अगर (wm8996->pdata.lकरो_ena > 0)
		gpio_set_value_cansleep(wm8996->pdata.lकरो_ena, 0);
	regulator_bulk_disable(ARRAY_SIZE(wm8996->supplies), wm8996->supplies);
err_gpio:
	अगर (wm8996->pdata.lकरो_ena > 0)
		gpio_मुक्त(wm8996->pdata.lकरो_ena);
err:

	वापस ret;
पूर्ण

अटल पूर्णांक wm8996_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wm8996_priv *wm8996 = i2c_get_clientdata(client);

	wm8996_मुक्त_gpio(wm8996);
	अगर (wm8996->pdata.lकरो_ena > 0) अणु
		gpio_set_value_cansleep(wm8996->pdata.lकरो_ena, 0);
		gpio_मुक्त(wm8996->pdata.lकरो_ena);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8996_i2c_id[] = अणु
	अणु "wm8996", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8996_i2c_id);

अटल काष्ठा i2c_driver wm8996_i2c_driver = अणु
	.driver = अणु
		.name = "wm8996",
	पूर्ण,
	.probe =    wm8996_i2c_probe,
	.हटाओ =   wm8996_i2c_हटाओ,
	.id_table = wm8996_i2c_id,
पूर्ण;

module_i2c_driver(wm8996_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8996 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
