<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2016, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>

#घोषणा CDC_D_REVISION1			(0xf000)
#घोषणा CDC_D_PERPH_SUBTYPE		(0xf005)
#घोषणा CDC_D_INT_EN_SET		(0xf015)
#घोषणा CDC_D_INT_EN_CLR		(0xf016)
#घोषणा MBHC_SWITCH_INT			BIT(7)
#घोषणा MBHC_MIC_ELECTRICAL_INS_REM_DET	BIT(6)
#घोषणा MBHC_BUTTON_PRESS_DET		BIT(5)
#घोषणा MBHC_BUTTON_RELEASE_DET		BIT(4)
#घोषणा CDC_D_CDC_RST_CTL		(0xf046)
#घोषणा RST_CTL_DIG_SW_RST_N_MASK	BIT(7)
#घोषणा RST_CTL_DIG_SW_RST_N_RESET	0
#घोषणा RST_CTL_DIG_SW_RST_N_REMOVE_RESET BIT(7)

#घोषणा CDC_D_CDC_TOP_CLK_CTL		(0xf048)
#घोषणा TOP_CLK_CTL_A_MCLK_MCLK2_EN_MASK (BIT(2) | BIT(3))
#घोषणा TOP_CLK_CTL_A_MCLK_EN_ENABLE	 BIT(2)
#घोषणा TOP_CLK_CTL_A_MCLK2_EN_ENABLE	BIT(3)

#घोषणा CDC_D_CDC_ANA_CLK_CTL		(0xf049)
#घोषणा ANA_CLK_CTL_EAR_HPHR_CLK_EN_MASK BIT(0)
#घोषणा ANA_CLK_CTL_EAR_HPHR_CLK_EN	BIT(0)
#घोषणा ANA_CLK_CTL_EAR_HPHL_CLK_EN	BIT(1)
#घोषणा ANA_CLK_CTL_SPKR_CLK_EN_MASK	BIT(4)
#घोषणा ANA_CLK_CTL_SPKR_CLK_EN	BIT(4)
#घोषणा ANA_CLK_CTL_TXA_CLK25_EN	BIT(5)

#घोषणा CDC_D_CDC_DIG_CLK_CTL		(0xf04A)
#घोषणा DIG_CLK_CTL_RXD1_CLK_EN		BIT(0)
#घोषणा DIG_CLK_CTL_RXD2_CLK_EN		BIT(1)
#घोषणा DIG_CLK_CTL_RXD3_CLK_EN		BIT(2)
#घोषणा DIG_CLK_CTL_D_MBHC_CLK_EN_MASK	BIT(3)
#घोषणा DIG_CLK_CTL_D_MBHC_CLK_EN	BIT(3)
#घोषणा DIG_CLK_CTL_TXD_CLK_EN		BIT(4)
#घोषणा DIG_CLK_CTL_NCP_CLK_EN_MASK	BIT(6)
#घोषणा DIG_CLK_CTL_NCP_CLK_EN		BIT(6)
#घोषणा DIG_CLK_CTL_RXD_PDM_CLK_EN_MASK	BIT(7)
#घोषणा DIG_CLK_CTL_RXD_PDM_CLK_EN	BIT(7)

#घोषणा CDC_D_CDC_CONN_TX1_CTL		(0xf050)
#घोषणा CONN_TX1_SERIAL_TX1_MUX		GENMASK(1, 0)
#घोषणा CONN_TX1_SERIAL_TX1_ADC_1	0x0
#घोषणा CONN_TX1_SERIAL_TX1_RX_PDM_LB	0x1
#घोषणा CONN_TX1_SERIAL_TX1_ZERO	0x2

#घोषणा CDC_D_CDC_CONN_TX2_CTL		(0xf051)
#घोषणा CONN_TX2_SERIAL_TX2_MUX		GENMASK(1, 0)
#घोषणा CONN_TX2_SERIAL_TX2_ADC_2	0x0
#घोषणा CONN_TX2_SERIAL_TX2_RX_PDM_LB	0x1
#घोषणा CONN_TX2_SERIAL_TX2_ZERO	0x2
#घोषणा CDC_D_CDC_CONN_HPHR_DAC_CTL	(0xf052)
#घोषणा CDC_D_CDC_CONN_RX1_CTL		(0xf053)
#घोषणा CDC_D_CDC_CONN_RX2_CTL		(0xf054)
#घोषणा CDC_D_CDC_CONN_RX3_CTL		(0xf055)
#घोषणा CDC_D_CDC_CONN_RX_LB_CTL	(0xf056)
#घोषणा CDC_D_SEC_ACCESS		(0xf0D0)
#घोषणा CDC_D_PERPH_RESET_CTL3		(0xf0DA)
#घोषणा CDC_D_PERPH_RESET_CTL4		(0xf0DB)
#घोषणा CDC_A_REVISION1			(0xf100)
#घोषणा CDC_A_REVISION2			(0xf101)
#घोषणा CDC_A_REVISION3			(0xf102)
#घोषणा CDC_A_REVISION4			(0xf103)
#घोषणा CDC_A_PERPH_TYPE		(0xf104)
#घोषणा CDC_A_PERPH_SUBTYPE		(0xf105)
#घोषणा CDC_A_INT_RT_STS		(0xf110)
#घोषणा CDC_A_INT_SET_TYPE		(0xf111)
#घोषणा CDC_A_INT_POLARITY_HIGH		(0xf112)
#घोषणा CDC_A_INT_POLARITY_LOW		(0xf113)
#घोषणा CDC_A_INT_LATCHED_CLR		(0xf114)
#घोषणा CDC_A_INT_EN_SET		(0xf115)
#घोषणा CDC_A_INT_EN_CLR		(0xf116)
#घोषणा CDC_A_INT_LATCHED_STS		(0xf118)
#घोषणा CDC_A_INT_PENDING_STS		(0xf119)
#घोषणा CDC_A_INT_MID_SEL		(0xf11A)
#घोषणा CDC_A_INT_PRIORITY		(0xf11B)
#घोषणा CDC_A_MICB_1_EN			(0xf140)
#घोषणा MICB_1_EN_MICB_ENABLE		BIT(7)
#घोषणा MICB_1_EN_BYP_CAP_MASK		BIT(6)
#घोषणा MICB_1_EN_NO_EXT_BYP_CAP	BIT(6)
#घोषणा MICB_1_EN_EXT_BYP_CAP		0
#घोषणा MICB_1_EN_PULL_DOWN_EN_MASK	BIT(5)
#घोषणा MICB_1_EN_PULL_DOWN_EN_ENABLE	BIT(5)
#घोषणा MICB_1_EN_OPA_STG2_TAIL_CURR_MASK GENMASK(3, 1)
#घोषणा MICB_1_EN_OPA_STG2_TAIL_CURR_1_60UA	(0x4)
#घोषणा MICB_1_EN_PULL_UP_EN_MASK	BIT(4)
#घोषणा MICB_1_EN_TX3_GND_SEL_MASK	BIT(0)
#घोषणा MICB_1_EN_TX3_GND_SEL_TX_GND	0

#घोषणा CDC_A_MICB_1_VAL		(0xf141)
#घोषणा MICB_MIN_VAL 1600
#घोषणा MICB_STEP_SIZE 50
#घोषणा MICB_VOLTAGE_REGVAL(v)		(((v - MICB_MIN_VAL)/MICB_STEP_SIZE) << 3)
#घोषणा MICB_1_VAL_MICB_OUT_VAL_MASK	GENMASK(7, 3)
#घोषणा MICB_1_VAL_MICB_OUT_VAL_V2P70V	((0x16)  << 3)
#घोषणा MICB_1_VAL_MICB_OUT_VAL_V1P80V	((0x4)  << 3)
#घोषणा CDC_A_MICB_1_CTL		(0xf142)

#घोषणा MICB_1_CTL_CFILT_REF_SEL_MASK		BIT(1)
#घोषणा MICB_1_CTL_CFILT_REF_SEL_HPF_REF	BIT(1)
#घोषणा MICB_1_CTL_EXT_PRECHARG_EN_MASK		BIT(5)
#घोषणा MICB_1_CTL_EXT_PRECHARG_EN_ENABLE	BIT(5)
#घोषणा MICB_1_CTL_INT_PRECHARG_BYP_MASK	BIT(6)
#घोषणा MICB_1_CTL_INT_PRECHARG_BYP_EXT_PRECHRG_SEL	BIT(6)

#घोषणा CDC_A_MICB_1_INT_RBIAS			(0xf143)
#घोषणा MICB_1_INT_TX1_INT_RBIAS_EN_MASK	BIT(7)
#घोषणा MICB_1_INT_TX1_INT_RBIAS_EN_ENABLE	BIT(7)
#घोषणा MICB_1_INT_TX1_INT_RBIAS_EN_DISABLE	0

#घोषणा MICB_1_INT_TX1_INT_PULLUP_EN_MASK	BIT(6)
#घोषणा MICB_1_INT_TX1_INT_PULLUP_EN_TX1N_TO_MICBIAS BIT(6)
#घोषणा MICB_1_INT_TX1_INT_PULLUP_EN_TX1N_TO_GND	0

#घोषणा MICB_1_INT_TX2_INT_RBIAS_EN_MASK	BIT(4)
#घोषणा MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE	BIT(4)
#घोषणा MICB_1_INT_TX2_INT_RBIAS_EN_DISABLE	0
#घोषणा MICB_1_INT_TX2_INT_PULLUP_EN_MASK	BIT(3)
#घोषणा MICB_1_INT_TX2_INT_PULLUP_EN_TX1N_TO_MICBIAS BIT(3)
#घोषणा MICB_1_INT_TX2_INT_PULLUP_EN_TX1N_TO_GND	0

#घोषणा MICB_1_INT_TX3_INT_RBIAS_EN_MASK	BIT(1)
#घोषणा MICB_1_INT_TX3_INT_RBIAS_EN_ENABLE	BIT(1)
#घोषणा MICB_1_INT_TX3_INT_RBIAS_EN_DISABLE	0
#घोषणा MICB_1_INT_TX3_INT_PULLUP_EN_MASK	BIT(0)
#घोषणा MICB_1_INT_TX3_INT_PULLUP_EN_TX1N_TO_MICBIAS BIT(0)
#घोषणा MICB_1_INT_TX3_INT_PULLUP_EN_TX1N_TO_GND	0

#घोषणा CDC_A_MICB_2_EN			(0xf144)
#घोषणा CDC_A_MICB_2_EN_ENABLE		BIT(7)
#घोषणा CDC_A_MICB_2_PULL_DOWN_EN_MASK	BIT(5)
#घोषणा CDC_A_MICB_2_PULL_DOWN_EN	BIT(5)
#घोषणा CDC_A_TX_1_2_ATEST_CTL_2	(0xf145)
#घोषणा CDC_A_MASTER_BIAS_CTL		(0xf146)
#घोषणा CDC_A_MBHC_DET_CTL_1		(0xf147)
#घोषणा CDC_A_MBHC_DET_CTL_L_DET_EN			BIT(7)
#घोषणा CDC_A_MBHC_DET_CTL_GND_DET_EN			BIT(6)
#घोषणा CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_INSERTION	BIT(5)
#घोषणा CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_REMOVAL	(0)
#घोषणा CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK		BIT(5)
#घोषणा CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_SHIFT		(5)
#घोषणा CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_AUTO		BIT(4)
#घोषणा CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_MANUAL		BIT(3)
#घोषणा CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_MASK		GENMASK(4, 3)
#घोषणा CDC_A_MBHC_DET_CTL_MBHC_BIAS_EN			BIT(2)
#घोषणा CDC_A_MBHC_DET_CTL_2		(0xf150)
#घोषणा CDC_A_MBHC_DET_CTL_HS_L_DET_PULL_UP_CTRL_I_3P0	(BIT(7) | BIT(6))
#घोषणा CDC_A_MBHC_DET_CTL_HS_L_DET_COMPA_CTRL_V0P9_VDD	BIT(5)
#घोषणा CDC_A_PLUG_TYPE_MASK				GENMASK(4, 3)
#घोषणा CDC_A_HPHL_PLUG_TYPE_NO				BIT(4)
#घोषणा CDC_A_GND_PLUG_TYPE_NO				BIT(3)
#घोषणा CDC_A_MBHC_DET_CTL_HPHL_100K_TO_GND_EN_MASK	BIT(0)
#घोषणा CDC_A_MBHC_DET_CTL_HPHL_100K_TO_GND_EN		BIT(0)
#घोषणा CDC_A_MBHC_FSM_CTL		(0xf151)
#घोषणा CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN			BIT(7)
#घोषणा CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN_MASK		BIT(7)
#घोषणा CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_I_100UA	(0x3 << 4)
#घोषणा CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_MASK		GENMASK(6, 4)
#घोषणा CDC_A_MBHC_DBNC_TIMER		(0xf152)
#घोषणा CDC_A_MBHC_DBNC_TIMER_BTN_DBNC_T_16MS		BIT(3)
#घोषणा CDC_A_MBHC_DBNC_TIMER_INSREM_DBNC_T_256_MS	(0x9 << 4)
#घोषणा CDC_A_MBHC_BTN0_ZDET_CTL_0	(0xf153)
#घोषणा CDC_A_MBHC_BTN1_ZDET_CTL_1	(0xf154)
#घोषणा CDC_A_MBHC_BTN2_ZDET_CTL_2	(0xf155)
#घोषणा CDC_A_MBHC_BTN3_CTL		(0xf156)
#घोषणा CDC_A_MBHC_BTN4_CTL		(0xf157)
#घोषणा CDC_A_MBHC_BTN_VREF_FINE_SHIFT	(2)
#घोषणा CDC_A_MBHC_BTN_VREF_FINE_MASK	GENMASK(4, 2)
#घोषणा CDC_A_MBHC_BTN_VREF_COARSE_MASK	GENMASK(7, 5)
#घोषणा CDC_A_MBHC_BTN_VREF_COARSE_SHIFT (5)
#घोषणा CDC_A_MBHC_BTN_VREF_MASK	(CDC_A_MBHC_BTN_VREF_COARSE_MASK | \
					CDC_A_MBHC_BTN_VREF_FINE_MASK)
#घोषणा CDC_A_MBHC_RESULT_1		(0xf158)
#घोषणा CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK	GENMASK(4, 0)
#घोषणा CDC_A_TX_1_EN			(0xf160)
#घोषणा CDC_A_TX_2_EN			(0xf161)
#घोषणा CDC_A_TX_1_2_TEST_CTL_1		(0xf162)
#घोषणा CDC_A_TX_1_2_TEST_CTL_2		(0xf163)
#घोषणा CDC_A_TX_1_2_ATEST_CTL		(0xf164)
#घोषणा CDC_A_TX_1_2_OPAMP_BIAS		(0xf165)
#घोषणा CDC_A_TX_3_EN			(0xf167)
#घोषणा CDC_A_NCP_EN			(0xf180)
#घोषणा CDC_A_NCP_CLK			(0xf181)
#घोषणा CDC_A_NCP_FBCTRL		(0xf183)
#घोषणा CDC_A_NCP_FBCTRL_FB_CLK_INV_MASK	BIT(5)
#घोषणा CDC_A_NCP_FBCTRL_FB_CLK_INV		BIT(5)
#घोषणा CDC_A_NCP_BIAS			(0xf184)
#घोषणा CDC_A_NCP_VCTRL			(0xf185)
#घोषणा CDC_A_NCP_TEST			(0xf186)
#घोषणा CDC_A_NCP_CLIM_ADDR		(0xf187)
#घोषणा CDC_A_RX_CLOCK_DIVIDER		(0xf190)
#घोषणा CDC_A_RX_COM_OCP_CTL		(0xf191)
#घोषणा CDC_A_RX_COM_OCP_COUNT		(0xf192)
#घोषणा CDC_A_RX_COM_BIAS_DAC		(0xf193)
#घोषणा RX_COM_BIAS_DAC_RX_BIAS_EN_MASK		BIT(7)
#घोषणा RX_COM_BIAS_DAC_RX_BIAS_EN_ENABLE	BIT(7)
#घोषणा RX_COM_BIAS_DAC_DAC_REF_EN_MASK		BIT(0)
#घोषणा RX_COM_BIAS_DAC_DAC_REF_EN_ENABLE	BIT(0)

#घोषणा CDC_A_RX_HPH_BIAS_PA		(0xf194)
#घोषणा CDC_A_RX_HPH_BIAS_LDO_OCP	(0xf195)
#घोषणा CDC_A_RX_HPH_BIAS_CNP		(0xf196)
#घोषणा CDC_A_RX_HPH_CNP_EN		(0xf197)
#घोषणा CDC_A_RX_HPH_L_PA_DAC_CTL	(0xf19B)
#घोषणा RX_HPA_L_PA_DAC_CTL_DATA_RESET_MASK	BIT(1)
#घोषणा RX_HPA_L_PA_DAC_CTL_DATA_RESET_RESET	BIT(1)
#घोषणा CDC_A_RX_HPH_R_PA_DAC_CTL	(0xf19D)
#घोषणा RX_HPH_R_PA_DAC_CTL_DATA_RESET	BIT(1)
#घोषणा RX_HPH_R_PA_DAC_CTL_DATA_RESET_MASK BIT(1)

#घोषणा CDC_A_RX_EAR_CTL			(0xf19E)
#घोषणा RX_EAR_CTL_SPK_VBAT_LDO_EN_MASK		BIT(0)
#घोषणा RX_EAR_CTL_SPK_VBAT_LDO_EN_ENABLE	BIT(0)
#घोषणा RX_EAR_CTL_PA_EAR_PA_EN_MASK		BIT(6)
#घोषणा RX_EAR_CTL_PA_EAR_PA_EN_ENABLE		BIT(6)
#घोषणा RX_EAR_CTL_PA_SEL_MASK			BIT(7)
#घोषणा RX_EAR_CTL_PA_SEL			BIT(7)

#घोषणा CDC_A_SPKR_DAC_CTL		(0xf1B0)
#घोषणा SPKR_DAC_CTL_DAC_RESET_MASK	BIT(4)
#घोषणा SPKR_DAC_CTL_DAC_RESET_NORMAL	0

#घोषणा CDC_A_SPKR_DRV_CTL		(0xf1B2)
#घोषणा SPKR_DRV_CTL_DEF_MASK		0xEF
#घोषणा SPKR_DRV_CLASSD_PA_EN_MASK	BIT(7)
#घोषणा SPKR_DRV_CLASSD_PA_EN_ENABLE	BIT(7)
#घोषणा SPKR_DRV_CAL_EN			BIT(6)
#घोषणा SPKR_DRV_SETTLE_EN		BIT(5)
#घोषणा SPKR_DRV_FW_EN			BIT(3)
#घोषणा SPKR_DRV_BOOST_SET		BIT(2)
#घोषणा SPKR_DRV_CMFB_SET		BIT(1)
#घोषणा SPKR_DRV_GAIN_SET		BIT(0)
#घोषणा SPKR_DRV_CTL_DEF_VAL (SPKR_DRV_CLASSD_PA_EN_ENABLE | \
		SPKR_DRV_CAL_EN | SPKR_DRV_SETTLE_EN | \
		SPKR_DRV_FW_EN | SPKR_DRV_BOOST_SET | \
		SPKR_DRV_CMFB_SET | SPKR_DRV_GAIN_SET)
#घोषणा CDC_A_SPKR_OCP_CTL		(0xf1B4)
#घोषणा CDC_A_SPKR_PWRSTG_CTL		(0xf1B5)
#घोषणा SPKR_PWRSTG_CTL_DAC_EN_MASK	BIT(0)
#घोषणा SPKR_PWRSTG_CTL_DAC_EN		BIT(0)
#घोषणा SPKR_PWRSTG_CTL_MASK		0xE0
#घोषणा SPKR_PWRSTG_CTL_BBM_MASK	BIT(7)
#घोषणा SPKR_PWRSTG_CTL_BBM_EN		BIT(7)
#घोषणा SPKR_PWRSTG_CTL_HBRDGE_EN_MASK	BIT(6)
#घोषणा SPKR_PWRSTG_CTL_HBRDGE_EN	BIT(6)
#घोषणा SPKR_PWRSTG_CTL_CLAMP_EN_MASK	BIT(5)
#घोषणा SPKR_PWRSTG_CTL_CLAMP_EN	BIT(5)

#घोषणा CDC_A_SPKR_DRV_DBG		(0xf1B7)
#घोषणा CDC_A_CURRENT_LIMIT		(0xf1C0)
#घोषणा CDC_A_BOOST_EN_CTL		(0xf1C3)
#घोषणा CDC_A_SLOPE_COMP_IP_ZERO	(0xf1C4)
#घोषणा CDC_A_SEC_ACCESS		(0xf1D0)
#घोषणा CDC_A_PERPH_RESET_CTL3		(0xf1DA)
#घोषणा CDC_A_PERPH_RESET_CTL4		(0xf1DB)

#घोषणा MSM8916_WCD_ANALOG_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000)
#घोषणा MSM8916_WCD_ANALOG_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
				    SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक btn_mask = SND_JACK_BTN_0 | SND_JACK_BTN_1 |
	       SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_BTN_4;
अटल पूर्णांक hs_jack_mask = SND_JACK_HEADPHONE | SND_JACK_HEADSET;

अटल स्थिर अक्षर * स्थिर supply_names[] = अणु
	"vdd-cdc-io",
	"vdd-cdc-tx-rx-cx",
पूर्ण;

#घोषणा MBHC_MAX_BUTTONS	(5)

काष्ठा pm8916_wcd_analog_priv अणु
	u16 pmic_rev;
	u16 codec_version;
	bool	mbhc_btn_enabled;
	/* special event to detect accessory type */
	पूर्णांक	mbhc_btn0_released;
	bool	detect_accessory_type;
	काष्ठा clk *mclk;
	काष्ठा snd_soc_component *component;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];
	काष्ठा snd_soc_jack *jack;
	bool hphl_jack_type_normally_खोलो;
	bool gnd_jack_type_normally_खोलो;
	/* Voltage threshold when पूर्णांकernal current source of 100uA is used */
	u32 vref_btn_cs[MBHC_MAX_BUTTONS];
	/* Voltage threshold when microphone bias is ON */
	u32 vref_btn_micb[MBHC_MAX_BUTTONS];
	अचिन्हित पूर्णांक micbias1_cap_mode;
	अचिन्हित पूर्णांक micbias2_cap_mode;
	अचिन्हित पूर्णांक micbias_mv;
पूर्ण;

अटल स्थिर अक्षर *स्थिर adc2_mux_text[] = अणु "ZERO", "INP2", "INP3" पूर्ण;
अटल स्थिर अक्षर *स्थिर rdac2_mux_text[] = अणु "RX1", "RX2" पूर्ण;
अटल स्थिर अक्षर *स्थिर hph_text[] = अणु "ZERO", "Switch", पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत hph_क्रमागत = SOC_ENUM_SINGLE_VIRT(
					ARRAY_SIZE(hph_text), hph_text);

अटल स्थिर काष्ठा snd_kcontrol_new ear_mux = SOC_DAPM_ENUM("EAR_S", hph_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new hphl_mux = SOC_DAPM_ENUM("HPHL", hph_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new hphr_mux = SOC_DAPM_ENUM("HPHR", hph_क्रमागत);

/* ADC2 MUX */
अटल स्थिर काष्ठा soc_क्रमागत adc2_क्रमागत = SOC_ENUM_SINGLE_VIRT(
			ARRAY_SIZE(adc2_mux_text), adc2_mux_text);

/* RDAC2 MUX */
अटल स्थिर काष्ठा soc_क्रमागत rdac2_mux_क्रमागत = SOC_ENUM_SINGLE(
			CDC_D_CDC_CONN_HPHR_DAC_CTL, 0, 2, rdac2_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new spkr_चयन[] = अणु
	SOC_DAPM_SINGLE("Switch", CDC_A_SPKR_DAC_CTL, 7, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rdac2_mux = SOC_DAPM_ENUM(
					"RDAC2 MUX Mux", rdac2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc2_mux = SOC_DAPM_ENUM(
					"ADC2 MUX Mux", adc2_क्रमागत);

/* Analog Gain control 0 dB to +24 dB in 6 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(analog_gain, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new pm8916_wcd_analog_snd_controls[] = अणु
	SOC_SINGLE_TLV("ADC1 Volume", CDC_A_TX_1_EN, 3, 8, 0, analog_gain),
	SOC_SINGLE_TLV("ADC2 Volume", CDC_A_TX_2_EN, 3, 8, 0, analog_gain),
	SOC_SINGLE_TLV("ADC3 Volume", CDC_A_TX_3_EN, 3, 8, 0, analog_gain),
पूर्ण;

अटल व्योम pm8916_wcd_analog_micbias_enable(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
			    MICB_1_CTL_EXT_PRECHARG_EN_MASK |
			    MICB_1_CTL_INT_PRECHARG_BYP_MASK,
			    MICB_1_CTL_INT_PRECHARG_BYP_EXT_PRECHRG_SEL
			    | MICB_1_CTL_EXT_PRECHARG_EN_ENABLE);

	अगर (wcd->micbias_mv) अणु
		snd_soc_component_update_bits(component, CDC_A_MICB_1_VAL,
				    MICB_1_VAL_MICB_OUT_VAL_MASK,
				    MICB_VOLTAGE_REGVAL(wcd->micbias_mv));
		/*
		 * Special headset needs MICBIAS as 2.7V so रुको क्रम
		 * 50 msec क्रम the MICBIAS to reach 2.7 volts.
		 */
		अगर (wcd->micbias_mv >= 2700)
			msleep(50);
	पूर्ण

	snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
			    MICB_1_CTL_EXT_PRECHARG_EN_MASK |
			    MICB_1_CTL_INT_PRECHARG_BYP_MASK, 0);

पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_micbias(काष्ठा snd_soc_component *component,
					    पूर्णांक event, अचिन्हित पूर्णांक cap_mode)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		pm8916_wcd_analog_micbias_enable(component);
		snd_soc_component_update_bits(component, CDC_A_MICB_1_EN,
				    MICB_1_EN_BYP_CAP_MASK, cap_mode);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_micbias_पूर्णांक(काष्ठा snd_soc_dapm_widget *w,
						काष्ठा snd_kcontrol *kcontrol,
						पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, CDC_A_MICB_1_EN,
				    MICB_1_EN_OPA_STG2_TAIL_CURR_MASK,
				    MICB_1_EN_OPA_STG2_TAIL_CURR_1_60UA);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_micbias1(काष्ठा snd_soc_dapm_widget *w,
					     काष्ठा snd_kcontrol *kcontrol,
					     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	वापस pm8916_wcd_analog_enable_micbias(component, event,
						wcd->micbias1_cap_mode);
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_micbias2(काष्ठा snd_soc_dapm_widget *w,
					     काष्ठा snd_kcontrol *kcontrol,
					     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	वापस pm8916_wcd_analog_enable_micbias(component, event,
						wcd->micbias2_cap_mode);

पूर्ण

अटल पूर्णांक pm8916_mbhc_configure_bias(काष्ठा pm8916_wcd_analog_priv *priv,
				      bool micbias2_enabled)
अणु
	काष्ठा snd_soc_component *component = priv->component;
	u32 coarse, fine, reg_val, reg_addr;
	पूर्णांक *vrefs, i;

	अगर (!micbias2_enabled) अणु /* use पूर्णांकernal 100uA Current source */
		/* Enable पूर्णांकernal 2.2k Internal Rbias Resistor */
		snd_soc_component_update_bits(component, CDC_A_MICB_1_INT_RBIAS,
				    MICB_1_INT_TX2_INT_RBIAS_EN_MASK,
				    MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE);
		/* Remove pull करोwn on MIC BIAS2 */
		snd_soc_component_update_bits(component, CDC_A_MICB_2_EN,
				   CDC_A_MICB_2_PULL_DOWN_EN_MASK,
				   0);
		/* enable 100uA पूर्णांकernal current source */
		snd_soc_component_update_bits(component, CDC_A_MBHC_FSM_CTL,
				    CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_MASK,
				    CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_I_100UA);
	पूर्ण
	snd_soc_component_update_bits(component, CDC_A_MBHC_FSM_CTL,
			CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN_MASK,
			CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN);

	अगर (micbias2_enabled)
		vrefs = &priv->vref_btn_micb[0];
	अन्यथा
		vrefs = &priv->vref_btn_cs[0];

	/* program vref ranges क्रम all the buttons */
	reg_addr = CDC_A_MBHC_BTN0_ZDET_CTL_0;
	क्रम (i = 0; i <  MBHC_MAX_BUTTONS; i++) अणु
		/* split mv in to coarse parts of 100mv & fine parts of 12mv */
		coarse = (vrefs[i] / 100);
		fine = ((vrefs[i] % 100) / 12);
		reg_val = (coarse << CDC_A_MBHC_BTN_VREF_COARSE_SHIFT) |
			 (fine << CDC_A_MBHC_BTN_VREF_FINE_SHIFT);
		snd_soc_component_update_bits(component, reg_addr,
			       CDC_A_MBHC_BTN_VREF_MASK,
			       reg_val);
		reg_addr++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pm8916_wcd_setup_mbhc(काष्ठा pm8916_wcd_analog_priv *wcd)
अणु
	काष्ठा snd_soc_component *component = wcd->component;
	bool micbias_enabled = false;
	u32 plug_type = 0;
	u32 पूर्णांक_en_mask;

	snd_soc_component_ग_लिखो(component, CDC_A_MBHC_DET_CTL_1,
		      CDC_A_MBHC_DET_CTL_L_DET_EN |
		      CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_INSERTION |
		      CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_AUTO |
		      CDC_A_MBHC_DET_CTL_MBHC_BIAS_EN);

	अगर (wcd->hphl_jack_type_normally_खोलो)
		plug_type |= CDC_A_HPHL_PLUG_TYPE_NO;

	अगर (wcd->gnd_jack_type_normally_खोलो)
		plug_type |= CDC_A_GND_PLUG_TYPE_NO;

	snd_soc_component_ग_लिखो(component, CDC_A_MBHC_DET_CTL_2,
		      CDC_A_MBHC_DET_CTL_HS_L_DET_PULL_UP_CTRL_I_3P0 |
		      CDC_A_MBHC_DET_CTL_HS_L_DET_COMPA_CTRL_V0P9_VDD |
		      plug_type |
		      CDC_A_MBHC_DET_CTL_HPHL_100K_TO_GND_EN);


	snd_soc_component_ग_लिखो(component, CDC_A_MBHC_DBNC_TIMER,
		      CDC_A_MBHC_DBNC_TIMER_INSREM_DBNC_T_256_MS |
		      CDC_A_MBHC_DBNC_TIMER_BTN_DBNC_T_16MS);

	/* enable MBHC घड़ी */
	snd_soc_component_update_bits(component, CDC_D_CDC_DIG_CLK_CTL,
			    DIG_CLK_CTL_D_MBHC_CLK_EN_MASK,
			    DIG_CLK_CTL_D_MBHC_CLK_EN);

	अगर (snd_soc_component_पढ़ो(component, CDC_A_MICB_2_EN) & CDC_A_MICB_2_EN_ENABLE)
		micbias_enabled = true;

	pm8916_mbhc_configure_bias(wcd, micbias_enabled);

	पूर्णांक_en_mask = MBHC_SWITCH_INT;
	अगर (wcd->mbhc_btn_enabled)
		पूर्णांक_en_mask |= MBHC_BUTTON_PRESS_DET | MBHC_BUTTON_RELEASE_DET;

	snd_soc_component_update_bits(component, CDC_D_INT_EN_CLR, पूर्णांक_en_mask, 0);
	snd_soc_component_update_bits(component, CDC_D_INT_EN_SET, पूर्णांक_en_mask, पूर्णांक_en_mask);
	wcd->mbhc_btn0_released = false;
	wcd->detect_accessory_type = true;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_micbias_पूर्णांक2(काष्ठा
						  snd_soc_dapm_widget
						  *w, काष्ठा snd_kcontrol
						  *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, CDC_A_MICB_2_EN,
					      CDC_A_MICB_2_PULL_DOWN_EN_MASK, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		pm8916_mbhc_configure_bias(wcd, true);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		pm8916_mbhc_configure_bias(wcd, false);
		अवरोध;
	पूर्ण

	वापस pm8916_wcd_analog_enable_micbias_पूर्णांक(w, kcontrol, event);
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_adc(काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा snd_kcontrol *kcontrol,
					 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 adc_reg = CDC_A_TX_1_2_TEST_CTL_2;
	u8 init_bit_shअगरt;

	अगर (w->reg == CDC_A_TX_1_EN)
		init_bit_shअगरt = 5;
	अन्यथा
		init_bit_shअगरt = 4;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (w->reg == CDC_A_TX_2_EN)
			snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
					    MICB_1_CTL_CFILT_REF_SEL_MASK,
					    MICB_1_CTL_CFILT_REF_SEL_HPF_REF);
		/*
		 * Add delay of 10 ms to give sufficient समय क्रम the voltage
		 * to shoot up and settle so that the txfe init करोes not
		 * happen when the input voltage is changing too much.
		 */
		usleep_range(10000, 10010);
		snd_soc_component_update_bits(component, adc_reg, 1 << init_bit_shअगरt,
				    1 << init_bit_shअगरt);
		चयन (w->reg) अणु
		हाल CDC_A_TX_1_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX1_CTL,
					    CONN_TX1_SERIAL_TX1_MUX,
					    CONN_TX1_SERIAL_TX1_ADC_1);
			अवरोध;
		हाल CDC_A_TX_2_EN:
		हाल CDC_A_TX_3_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX2_CTL,
					    CONN_TX2_SERIAL_TX2_MUX,
					    CONN_TX2_SERIAL_TX2_ADC_2);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * Add delay of 12 ms beक्रमe deनिश्चितing the init
		 * to reduce the tx pop
		 */
		usleep_range(12000, 12010);
		snd_soc_component_update_bits(component, adc_reg, 1 << init_bit_shअगरt, 0x00);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		चयन (w->reg) अणु
		हाल CDC_A_TX_1_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX1_CTL,
					    CONN_TX1_SERIAL_TX1_MUX,
					    CONN_TX1_SERIAL_TX1_ZERO);
			अवरोध;
		हाल CDC_A_TX_2_EN:
			snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
					    MICB_1_CTL_CFILT_REF_SEL_MASK, 0);
			fallthrough;
		हाल CDC_A_TX_3_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX2_CTL,
					    CONN_TX2_SERIAL_TX2_MUX,
					    CONN_TX2_SERIAL_TX2_ZERO);
			अवरोध;
		पूर्ण


		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_spk_pa(काष्ठा snd_soc_dapm_widget *w,
					    काष्ठा snd_kcontrol *kcontrol,
					    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, CDC_A_SPKR_PWRSTG_CTL,
				    SPKR_PWRSTG_CTL_DAC_EN_MASK |
				    SPKR_PWRSTG_CTL_BBM_MASK |
				    SPKR_PWRSTG_CTL_HBRDGE_EN_MASK |
				    SPKR_PWRSTG_CTL_CLAMP_EN_MASK,
				    SPKR_PWRSTG_CTL_DAC_EN|
				    SPKR_PWRSTG_CTL_BBM_EN |
				    SPKR_PWRSTG_CTL_HBRDGE_EN |
				    SPKR_PWRSTG_CTL_CLAMP_EN);

		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_SPK_VBAT_LDO_EN_MASK,
				    RX_EAR_CTL_SPK_VBAT_LDO_EN_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, CDC_A_SPKR_DRV_CTL,
				    SPKR_DRV_CTL_DEF_MASK,
				    SPKR_DRV_CTL_DEF_VAL);
		snd_soc_component_update_bits(component, w->reg,
				    SPKR_DRV_CLASSD_PA_EN_MASK,
				    SPKR_DRV_CLASSD_PA_EN_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, CDC_A_SPKR_PWRSTG_CTL,
				    SPKR_PWRSTG_CTL_DAC_EN_MASK|
				    SPKR_PWRSTG_CTL_BBM_MASK |
				    SPKR_PWRSTG_CTL_HBRDGE_EN_MASK |
				    SPKR_PWRSTG_CTL_CLAMP_EN_MASK, 0);

		snd_soc_component_update_bits(component, CDC_A_SPKR_DAC_CTL,
				    SPKR_DAC_CTL_DAC_RESET_MASK,
				    SPKR_DAC_CTL_DAC_RESET_NORMAL);
		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_SPK_VBAT_LDO_EN_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_enable_ear_pa(काष्ठा snd_soc_dapm_widget *w,
					    काष्ठा snd_kcontrol *kcontrol,
					    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_PA_SEL_MASK, RX_EAR_CTL_PA_SEL);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_PA_EAR_PA_EN_MASK,
				    RX_EAR_CTL_PA_EAR_PA_EN_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_PA_EAR_PA_EN_MASK, 0);
		/* Delay to reduce ear turn off pop */
		usleep_range(7000, 7100);
		snd_soc_component_update_bits(component, CDC_A_RX_EAR_CTL,
				    RX_EAR_CTL_PA_SEL_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_शेष wcd_reg_शेषs_2_0[] = अणु
	अणुCDC_A_RX_COM_OCP_CTL, 0xD1पूर्ण,
	अणुCDC_A_RX_COM_OCP_COUNT, 0xFFपूर्ण,
	अणुCDC_D_SEC_ACCESS, 0xA5पूर्ण,
	अणुCDC_D_PERPH_RESET_CTL3, 0x0Fपूर्ण,
	अणुCDC_A_TX_1_2_OPAMP_BIAS, 0x4Fपूर्ण,
	अणुCDC_A_NCP_FBCTRL, 0x28पूर्ण,
	अणुCDC_A_SPKR_DRV_CTL, 0x69पूर्ण,
	अणुCDC_A_SPKR_DRV_DBG, 0x01पूर्ण,
	अणुCDC_A_BOOST_EN_CTL, 0x5Fपूर्ण,
	अणुCDC_A_SLOPE_COMP_IP_ZERO, 0x88पूर्ण,
	अणुCDC_A_SEC_ACCESS, 0xA5पूर्ण,
	अणुCDC_A_PERPH_RESET_CTL3, 0x0Fपूर्ण,
	अणुCDC_A_CURRENT_LIMIT, 0x82पूर्ण,
	अणुCDC_A_SPKR_DAC_CTL, 0x03पूर्ण,
	अणुCDC_A_SPKR_OCP_CTL, 0xE1पूर्ण,
	अणुCDC_A_MASTER_BIAS_CTL, 0x30पूर्ण,
पूर्ण;

अटल पूर्णांक pm8916_wcd_analog_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = dev_get_drvdata(component->dev);
	पूर्णांक err, reg;

	err = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	अगर (err != 0) अणु
		dev_err(component->dev, "failed to enable regulators (%d)\n", err);
		वापस err;
	पूर्ण

	snd_soc_component_init_regmap(component,
				  dev_get_regmap(component->dev->parent, शून्य));
	snd_soc_component_set_drvdata(component, priv);
	priv->pmic_rev = snd_soc_component_पढ़ो(component, CDC_D_REVISION1);
	priv->codec_version = snd_soc_component_पढ़ो(component, CDC_D_PERPH_SUBTYPE);

	dev_info(component->dev, "PMIC REV: %d\t CODEC Version: %d\n",
		 priv->pmic_rev, priv->codec_version);

	snd_soc_component_ग_लिखो(component, CDC_D_PERPH_RESET_CTL4, 0x01);
	snd_soc_component_ग_लिखो(component, CDC_A_PERPH_RESET_CTL4, 0x01);

	क्रम (reg = 0; reg < ARRAY_SIZE(wcd_reg_शेषs_2_0); reg++)
		snd_soc_component_ग_लिखो(component, wcd_reg_शेषs_2_0[reg].reg,
			      wcd_reg_शेषs_2_0[reg].def);

	priv->component = component;

	snd_soc_component_update_bits(component, CDC_D_CDC_RST_CTL,
			    RST_CTL_DIG_SW_RST_N_MASK,
			    RST_CTL_DIG_SW_RST_N_REMOVE_RESET);

	pm8916_wcd_setup_mbhc(priv);

	वापस 0;
पूर्ण

अटल व्योम pm8916_wcd_analog_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = dev_get_drvdata(component->dev);

	snd_soc_component_update_bits(component, CDC_D_CDC_RST_CTL,
			    RST_CTL_DIG_SW_RST_N_MASK, 0);

	regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				      priv->supplies);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route pm8916_wcd_analog_audio_map[] = अणु

	अणु"PDM_RX1", शून्य, "PDM Playback"पूर्ण,
	अणु"PDM_RX2", शून्य, "PDM Playback"पूर्ण,
	अणु"PDM_RX3", शून्य, "PDM Playback"पूर्ण,
	अणु"PDM Capture", शून्य, "PDM_TX"पूर्ण,

	/* ADC Connections */
	अणु"PDM_TX", शून्य, "ADC2"पूर्ण,
	अणु"PDM_TX", शून्य, "ADC3"पूर्ण,
	अणु"ADC2", शून्य, "ADC2 MUX"पूर्ण,
	अणु"ADC3", शून्य, "ADC2 MUX"पूर्ण,
	अणु"ADC2 MUX", "INP2", "ADC2_INP2"पूर्ण,
	अणु"ADC2 MUX", "INP3", "ADC2_INP3"पूर्ण,

	अणु"PDM_TX", शून्य, "ADC1"पूर्ण,
	अणु"ADC1", शून्य, "AMIC1"पूर्ण,
	अणु"ADC2_INP2", शून्य, "AMIC2"पूर्ण,
	अणु"ADC2_INP3", शून्य, "AMIC3"पूर्ण,

	/* RDAC Connections */
	अणु"HPHR DAC", शून्य, "RDAC2 MUX"पूर्ण,
	अणु"RDAC2 MUX", "RX1", "PDM_RX1"पूर्ण,
	अणु"RDAC2 MUX", "RX2", "PDM_RX2"पूर्ण,
	अणु"HPHL DAC", शून्य, "PDM_RX1"पूर्ण,
	अणु"PDM_RX1", शून्य, "RXD1_CLK"पूर्ण,
	अणु"PDM_RX2", शून्य, "RXD2_CLK"पूर्ण,
	अणु"PDM_RX3", शून्य, "RXD3_CLK"पूर्ण,

	अणु"PDM_RX1", शून्य, "RXD_PDM_CLK"पूर्ण,
	अणु"PDM_RX2", शून्य, "RXD_PDM_CLK"पूर्ण,
	अणु"PDM_RX3", शून्य, "RXD_PDM_CLK"पूर्ण,

	अणु"ADC1", शून्य, "TXD_CLK"पूर्ण,
	अणु"ADC2", शून्य, "TXD_CLK"पूर्ण,
	अणु"ADC3", शून्य, "TXD_CLK"पूर्ण,

	अणु"ADC1", शून्य, "TXA_CLK25"पूर्ण,
	अणु"ADC2", शून्य, "TXA_CLK25"पूर्ण,
	अणु"ADC3", शून्य, "TXA_CLK25"पूर्ण,

	अणु"PDM_RX1", शून्य, "A_MCLK2"पूर्ण,
	अणु"PDM_RX2", शून्य, "A_MCLK2"पूर्ण,
	अणु"PDM_RX3", शून्य, "A_MCLK2"पूर्ण,

	अणु"PDM_TX", शून्य, "A_MCLK2"पूर्ण,
	अणु"A_MCLK2", शून्य, "A_MCLK"पूर्ण,

	/* Earpiece (RX MIX1) */
	अणु"EAR", शून्य, "EAR_S"पूर्ण,
	अणु"EAR_S", "Switch", "EAR PA"पूर्ण,
	अणु"EAR PA", शून्य, "RX_BIAS"पूर्ण,
	अणु"EAR PA", शून्य, "HPHL DAC"पूर्ण,
	अणु"EAR PA", शून्य, "HPHR DAC"पूर्ण,
	अणु"EAR PA", शून्य, "EAR CP"पूर्ण,

	/* Headset (RX MIX1 and RX MIX2) */
	अणु"HEADPHONE", शून्य, "HPHL PA"पूर्ण,
	अणु"HEADPHONE", शून्य, "HPHR PA"पूर्ण,

	अणु"HPHL DAC", शून्य, "EAR_HPHL_CLK"पूर्ण,
	अणु"HPHR DAC", शून्य, "EAR_HPHR_CLK"पूर्ण,

	अणु"CP", शून्य, "NCP_CLK"पूर्ण,

	अणु"HPHL PA", शून्य, "HPHL"पूर्ण,
	अणु"HPHR PA", शून्य, "HPHR"पूर्ण,
	अणु"HPHL PA", शून्य, "CP"पूर्ण,
	अणु"HPHL PA", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHR PA", शून्य, "CP"पूर्ण,
	अणु"HPHR PA", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHL", "Switch", "HPHL DAC"पूर्ण,
	अणु"HPHR", "Switch", "HPHR DAC"पूर्ण,

	अणु"RX_BIAS", शून्य, "DAC_REF"पूर्ण,

	अणु"SPK_OUT", शून्य, "SPK PA"पूर्ण,
	अणु"SPK PA", शून्य, "RX_BIAS"पूर्ण,
	अणु"SPK PA", शून्य, "SPKR_CLK"पूर्ण,
	अणु"SPK PA", शून्य, "SPK DAC"पूर्ण,
	अणु"SPK DAC", "Switch", "PDM_RX3"पूर्ण,

	अणु"MIC_BIAS1", शून्य, "INT_LDO_H"पूर्ण,
	अणु"MIC_BIAS2", शून्य, "INT_LDO_H"पूर्ण,
	अणु"MIC_BIAS1", शून्य, "vdd-micbias"पूर्ण,
	अणु"MIC_BIAS2", शून्य, "vdd-micbias"पूर्ण,

	अणु"MIC BIAS External1", शून्य, "MIC_BIAS1"पूर्ण,
	अणु"MIC BIAS Internal1", शून्य, "MIC_BIAS1"पूर्ण,
	अणु"MIC BIAS External2", शून्य, "MIC_BIAS2"पूर्ण,
	अणु"MIC BIAS Internal2", शून्य, "MIC_BIAS2"पूर्ण,
	अणु"MIC BIAS Internal3", शून्य, "MIC_BIAS1"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pm8916_wcd_analog_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_AIF_IN("PDM_RX1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PDM_RX2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PDM_RX3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PDM_TX", शून्य, 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_INPUT("AMIC1"),
	SND_SOC_DAPM_INPUT("AMIC3"),
	SND_SOC_DAPM_INPUT("AMIC2"),
	SND_SOC_DAPM_OUTPUT("EAR"),
	SND_SOC_DAPM_OUTPUT("HEADPHONE"),

	/* RX stuff */
	SND_SOC_DAPM_SUPPLY("INT_LDO_H", SND_SOC_NOPM, 1, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_E("EAR PA", SND_SOC_NOPM,
			   0, 0, शून्य, 0,
			   pm8916_wcd_analog_enable_ear_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("EAR_S", SND_SOC_NOPM, 0, 0, &ear_mux),
	SND_SOC_DAPM_SUPPLY("EAR CP", CDC_A_NCP_EN, 4, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("HPHL PA", CDC_A_RX_HPH_CNP_EN, 5, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("HPHL", SND_SOC_NOPM, 0, 0, &hphl_mux),
	SND_SOC_DAPM_MIXER("HPHL DAC", CDC_A_RX_HPH_L_PA_DAC_CTL, 3, 0, शून्य,
			   0),
	SND_SOC_DAPM_PGA("HPHR PA", CDC_A_RX_HPH_CNP_EN, 4, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("HPHR", SND_SOC_NOPM, 0, 0, &hphr_mux),
	SND_SOC_DAPM_MIXER("HPHR DAC", CDC_A_RX_HPH_R_PA_DAC_CTL, 3, 0, शून्य,
			   0),
	SND_SOC_DAPM_MIXER("SPK DAC", SND_SOC_NOPM, 0, 0,
			   spkr_चयन, ARRAY_SIZE(spkr_चयन)),

	/* Speaker */
	SND_SOC_DAPM_OUTPUT("SPK_OUT"),
	SND_SOC_DAPM_PGA_E("SPK PA", CDC_A_SPKR_DRV_CTL,
			   6, 0, शून्य, 0,
			   pm8916_wcd_analog_enable_spk_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_REGULATOR_SUPPLY("vdd-micbias", 0, 0),
	SND_SOC_DAPM_SUPPLY("CP", CDC_A_NCP_EN, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DAC_REF", CDC_A_RX_COM_BIAS_DAC, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RX_BIAS", CDC_A_RX_COM_BIAS_DAC, 7, 0, शून्य, 0),

	/* TX */
	SND_SOC_DAPM_SUPPLY("MIC_BIAS1", CDC_A_MICB_1_EN, 7, 0,
			    pm8916_wcd_analog_enable_micbias1,
			    SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("MIC_BIAS2", CDC_A_MICB_2_EN, 7, 0,
			    pm8916_wcd_analog_enable_micbias2,
			    SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPLY("MIC BIAS External1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC BIAS External2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("MIC BIAS Internal1", CDC_A_MICB_1_INT_RBIAS, 7, 0,
			    pm8916_wcd_analog_enable_micbias_पूर्णांक,
			    SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("MIC BIAS Internal2", CDC_A_MICB_1_INT_RBIAS, 4, 0,
			    pm8916_wcd_analog_enable_micbias_पूर्णांक2,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			    SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS Internal3", CDC_A_MICB_1_INT_RBIAS, 1, 0,
			    pm8916_wcd_analog_enable_micbias_पूर्णांक,
			    SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_ADC_E("ADC1", शून्य, CDC_A_TX_1_EN, 7, 0,
			   pm8916_wcd_analog_enable_adc,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("ADC2_INP2", शून्य, CDC_A_TX_2_EN, 7, 0,
			   pm8916_wcd_analog_enable_adc,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("ADC2_INP3", शून्य, CDC_A_TX_3_EN, 7, 0,
			   pm8916_wcd_analog_enable_adc,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("ADC2 MUX", SND_SOC_NOPM, 0, 0, &tx_adc2_mux),
	SND_SOC_DAPM_MUX("RDAC2 MUX", SND_SOC_NOPM, 0, 0, &rdac2_mux),

	/* Analog path घड़ीs */
	SND_SOC_DAPM_SUPPLY("EAR_HPHR_CLK", CDC_D_CDC_ANA_CLK_CTL, 0, 0, शून्य,
			    0),
	SND_SOC_DAPM_SUPPLY("EAR_HPHL_CLK", CDC_D_CDC_ANA_CLK_CTL, 1, 0, शून्य,
			    0),
	SND_SOC_DAPM_SUPPLY("SPKR_CLK", CDC_D_CDC_ANA_CLK_CTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("TXA_CLK25", CDC_D_CDC_ANA_CLK_CTL, 5, 0, शून्य, 0),

	/* Digital path घड़ीs */

	SND_SOC_DAPM_SUPPLY("RXD1_CLK", CDC_D_CDC_DIG_CLK_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RXD2_CLK", CDC_D_CDC_DIG_CLK_CTL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RXD3_CLK", CDC_D_CDC_DIG_CLK_CTL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("TXD_CLK", CDC_D_CDC_DIG_CLK_CTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("NCP_CLK", CDC_D_CDC_DIG_CLK_CTL, 6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RXD_PDM_CLK", CDC_D_CDC_DIG_CLK_CTL, 7, 0, शून्य,
			    0),

	/* System Clock source */
	SND_SOC_DAPM_SUPPLY("A_MCLK", CDC_D_CDC_TOP_CLK_CTL, 2, 0, शून्य, 0),
	/* TX ADC and RX DAC Clock source. */
	SND_SOC_DAPM_SUPPLY("A_MCLK2", CDC_D_CDC_TOP_CLK_CTL, 3, 0, शून्य, 0),
पूर्ण;

अटल पूर्णांक pm8916_wcd_analog_set_jack(काष्ठा snd_soc_component *component,
				      काष्ठा snd_soc_jack *jack,
				      व्योम *data)
अणु
	काष्ठा pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	wcd->jack = jack;

	वापस 0;
पूर्ण

अटल irqवापस_t mbhc_btn_release_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = arg;

	अगर (priv->detect_accessory_type) अणु
		काष्ठा snd_soc_component *component = priv->component;
		u32 val = snd_soc_component_पढ़ो(component, CDC_A_MBHC_RESULT_1);

		/* check अगर its BTN0 thats released */
		अगर ((val != -1) && !(val & CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK))
			priv->mbhc_btn0_released = true;

	पूर्ण अन्यथा अणु
		snd_soc_jack_report(priv->jack, 0, btn_mask);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mbhc_btn_press_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = arg;
	काष्ठा snd_soc_component *component = priv->component;
	u32 btn_result;

	btn_result = snd_soc_component_पढ़ो(component, CDC_A_MBHC_RESULT_1) &
				  CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK;

	चयन (btn_result) अणु
	हाल 0xf:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_4, btn_mask);
		अवरोध;
	हाल 0x7:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_3, btn_mask);
		अवरोध;
	हाल 0x3:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_2, btn_mask);
		अवरोध;
	हाल 0x1:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_1, btn_mask);
		अवरोध;
	हाल 0x0:
		/* handle BTN_0 specially क्रम type detection */
		अगर (!priv->detect_accessory_type)
			snd_soc_jack_report(priv->jack,
					    SND_JACK_BTN_0, btn_mask);
		अवरोध;
	शेष:
		dev_err(component->dev,
			"Unexpected button press result (%x)", btn_result);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm8916_mbhc_चयन_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = arg;
	काष्ठा snd_soc_component *component = priv->component;
	bool ins = false;

	अगर (snd_soc_component_पढ़ो(component, CDC_A_MBHC_DET_CTL_1) &
				CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK)
		ins = true;

	/* Set the detection type appropriately */
	snd_soc_component_update_bits(component, CDC_A_MBHC_DET_CTL_1,
			    CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK,
			    (!ins << CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_SHIFT));


	अगर (ins) अणु /* hs insertion */
		bool micbias_enabled = false;

		अगर (snd_soc_component_पढ़ो(component, CDC_A_MICB_2_EN) &
				CDC_A_MICB_2_EN_ENABLE)
			micbias_enabled = true;

		pm8916_mbhc_configure_bias(priv, micbias_enabled);

		/*
		 * अगर only a btn0 press event is receive just beक्रमe
		 * insert event then its a 3 pole headphone अन्यथा अगर
		 * both press and release event received then its
		 * a headset.
		 */
		अगर (priv->mbhc_btn0_released)
			snd_soc_jack_report(priv->jack,
					    SND_JACK_HEADSET, hs_jack_mask);
		अन्यथा
			snd_soc_jack_report(priv->jack,
					    SND_JACK_HEADPHONE, hs_jack_mask);

		priv->detect_accessory_type = false;

	पूर्ण अन्यथा अणु /* removal */
		snd_soc_jack_report(priv->jack, 0, hs_jack_mask);
		priv->detect_accessory_type = true;
		priv->mbhc_btn0_released = false;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा snd_soc_dai_driver pm8916_wcd_analog_dai[] = अणु
	[0] = अणु
	       .name = "pm8916_wcd_analog_pdm_rx",
	       .id = 0,
	       .playback = अणु
			    .stream_name = "PDM Playback",
			    .rates = MSM8916_WCD_ANALOG_RATES,
			    .क्रमmats = MSM8916_WCD_ANALOG_FORMATS,
			    .channels_min = 1,
			    .channels_max = 3,
			    पूर्ण,
	       पूर्ण,
	[1] = अणु
	       .name = "pm8916_wcd_analog_pdm_tx",
	       .id = 1,
	       .capture = अणु
			   .stream_name = "PDM Capture",
			   .rates = MSM8916_WCD_ANALOG_RATES,
			   .क्रमmats = MSM8916_WCD_ANALOG_FORMATS,
			   .channels_min = 1,
			   .channels_max = 4,
			   पूर्ण,
	       पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver pm8916_wcd_analog = अणु
	.probe			= pm8916_wcd_analog_probe,
	.हटाओ			= pm8916_wcd_analog_हटाओ,
	.set_jack		= pm8916_wcd_analog_set_jack,
	.controls		= pm8916_wcd_analog_snd_controls,
	.num_controls		= ARRAY_SIZE(pm8916_wcd_analog_snd_controls),
	.dapm_widमाला_लो		= pm8916_wcd_analog_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pm8916_wcd_analog_dapm_widमाला_लो),
	.dapm_routes		= pm8916_wcd_analog_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(pm8916_wcd_analog_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक pm8916_wcd_analog_parse_dt(काष्ठा device *dev,
				       काष्ठा pm8916_wcd_analog_priv *priv)
अणु
	पूर्णांक rval;

	अगर (of_property_पढ़ो_bool(dev->of_node, "qcom,micbias1-ext-cap"))
		priv->micbias1_cap_mode = MICB_1_EN_EXT_BYP_CAP;
	अन्यथा
		priv->micbias1_cap_mode = MICB_1_EN_NO_EXT_BYP_CAP;

	अगर (of_property_पढ़ो_bool(dev->of_node, "qcom,micbias2-ext-cap"))
		priv->micbias2_cap_mode = MICB_1_EN_EXT_BYP_CAP;
	अन्यथा
		priv->micbias2_cap_mode = MICB_1_EN_NO_EXT_BYP_CAP;

	of_property_पढ़ो_u32(dev->of_node, "qcom,micbias-lvl",
			     &priv->micbias_mv);

	अगर (of_property_पढ़ो_bool(dev->of_node,
				  "qcom,hphl-jack-type-normally-open"))
		priv->hphl_jack_type_normally_खोलो = true;
	अन्यथा
		priv->hphl_jack_type_normally_खोलो = false;

	अगर (of_property_पढ़ो_bool(dev->of_node,
				  "qcom,gnd-jack-type-normally-open"))
		priv->gnd_jack_type_normally_खोलो = true;
	अन्यथा
		priv->gnd_jack_type_normally_खोलो = false;

	priv->mbhc_btn_enabled = true;
	rval = of_property_पढ़ो_u32_array(dev->of_node,
					  "qcom,mbhc-vthreshold-low",
					  &priv->vref_btn_cs[0],
					  MBHC_MAX_BUTTONS);
	अगर (rval < 0) अणु
		priv->mbhc_btn_enabled = false;
	पूर्ण अन्यथा अणु
		rval = of_property_पढ़ो_u32_array(dev->of_node,
						  "qcom,mbhc-vthreshold-high",
						  &priv->vref_btn_micb[0],
						  MBHC_MAX_BUTTONS);
		अगर (rval < 0)
			priv->mbhc_btn_enabled = false;
	पूर्ण

	अगर (!priv->mbhc_btn_enabled)
		dev_err(dev,
			"DT property missing, MBHC btn detection disabled\n");


	वापस 0;
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_spmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, i, irq;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = pm8916_wcd_analog_parse_dt(dev, priv);
	अगर (ret < 0)
		वापस ret;

	priv->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(priv->mclk)) अणु
		dev_err(dev, "failed to get mclk\n");
		वापस PTR_ERR(priv->mclk);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		priv->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(priv->supplies),
				    priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get regulator supplies %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->mclk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable mclk %d\n", ret);
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "mbhc_switch_int");
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
			       pm8916_mbhc_चयन_irq_handler,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			       IRQF_ONESHOT,
			       "mbhc switch irq", priv);
	अगर (ret)
		dev_err(dev, "cannot request mbhc switch irq\n");

	अगर (priv->mbhc_btn_enabled) अणु
		irq = platक्रमm_get_irq_byname(pdev, "mbhc_but_press_det");
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
				       mbhc_btn_press_irq_handler,
				       IRQF_TRIGGER_RISING |
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       "mbhc btn press irq", priv);
		अगर (ret)
			dev_err(dev, "cannot request mbhc button press irq\n");

		irq = platक्रमm_get_irq_byname(pdev, "mbhc_but_rel_det");
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
				       mbhc_btn_release_irq_handler,
				       IRQF_TRIGGER_RISING |
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       "mbhc btn release irq", priv);
		अगर (ret)
			dev_err(dev, "cannot request mbhc button release irq\n");

	पूर्ण

	dev_set_drvdata(dev, priv);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &pm8916_wcd_analog,
				      pm8916_wcd_analog_dai,
				      ARRAY_SIZE(pm8916_wcd_analog_dai));
पूर्ण

अटल पूर्णांक pm8916_wcd_analog_spmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8916_wcd_analog_priv *priv = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(priv->mclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8916_wcd_analog_spmi_match_table[] = अणु
	अणु .compatible = "qcom,pm8916-wcd-analog-codec", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, pm8916_wcd_analog_spmi_match_table);

अटल काष्ठा platक्रमm_driver pm8916_wcd_analog_spmi_driver = अणु
	.driver = अणु
		   .name = "qcom,pm8916-wcd-spmi-codec",
		   .of_match_table = pm8916_wcd_analog_spmi_match_table,
	पूर्ण,
	.probe = pm8916_wcd_analog_spmi_probe,
	.हटाओ = pm8916_wcd_analog_spmi_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm8916_wcd_analog_spmi_driver);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org>");
MODULE_DESCRIPTION("PMIC PM8916 WCD Analog Codec driver");
MODULE_LICENSE("GPL v2");
