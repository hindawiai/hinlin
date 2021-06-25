<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
// Copyright (c) 2017-2018, Linaro Limited

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slimbus.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <sound/tlv.h>
#समावेश <sound/info.h>
#समावेश "wcd9335.h"
#समावेश "wcd-clsh-v2.h"

#घोषणा WCD9335_RATES_MASK (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			    SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
			    SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
/* Fractional Rates */
#घोषणा WCD9335_FRAC_RATES_MASK (SNDRV_PCM_RATE_44100)
#घोषणा WCD9335_FORMATS_S16_S24_LE (SNDRV_PCM_FMTBIT_S16_LE | \
				  SNDRV_PCM_FMTBIT_S24_LE)

/* slave port water mark level
 *   (0: 6bytes, 1: 9bytes, 2: 12 bytes, 3: 15 bytes)
 */
#घोषणा SLAVE_PORT_WATER_MARK_6BYTES  0
#घोषणा SLAVE_PORT_WATER_MARK_9BYTES  1
#घोषणा SLAVE_PORT_WATER_MARK_12BYTES 2
#घोषणा SLAVE_PORT_WATER_MARK_15BYTES 3
#घोषणा SLAVE_PORT_WATER_MARK_SHIFT 1
#घोषणा SLAVE_PORT_ENABLE           1
#घोषणा SLAVE_PORT_DISABLE          0
#घोषणा WCD9335_SLIM_WATER_MARK_VAL \
	((SLAVE_PORT_WATER_MARK_12BYTES << SLAVE_PORT_WATER_MARK_SHIFT) | \
	 (SLAVE_PORT_ENABLE))

#घोषणा WCD9335_SLIM_NUM_PORT_REG 3
#घोषणा WCD9335_SLIM_PGD_PORT_INT_TX_EN0 (WCD9335_SLIM_PGD_PORT_INT_EN0 + 2)

#घोषणा WCD9335_MCLK_CLK_12P288MHZ	12288000
#घोषणा WCD9335_MCLK_CLK_9P6MHZ		9600000

#घोषणा WCD9335_SLIM_CLOSE_TIMEOUT 1000
#घोषणा WCD9335_SLIM_IRQ_OVERFLOW (1 << 0)
#घोषणा WCD9335_SLIM_IRQ_UNDERFLOW (1 << 1)
#घोषणा WCD9335_SLIM_IRQ_PORT_CLOSED (1 << 2)

#घोषणा WCD9335_NUM_INTERPOLATORS 9
#घोषणा WCD9335_RX_START	16
#घोषणा WCD9335_SLIM_CH_START 128
#घोषणा WCD9335_MAX_MICBIAS 4
#घोषणा WCD9335_MAX_VALID_ADC_MUX  13
#घोषणा WCD9335_INVALID_ADC_MUX 9

#घोषणा  TX_HPF_CUT_OFF_FREQ_MASK	0x60
#घोषणा  CF_MIN_3DB_4HZ			0x0
#घोषणा  CF_MIN_3DB_75HZ		0x1
#घोषणा  CF_MIN_3DB_150HZ		0x2
#घोषणा WCD9335_DMIC_CLK_DIV_2  0x0
#घोषणा WCD9335_DMIC_CLK_DIV_3  0x1
#घोषणा WCD9335_DMIC_CLK_DIV_4  0x2
#घोषणा WCD9335_DMIC_CLK_DIV_6  0x3
#घोषणा WCD9335_DMIC_CLK_DIV_8  0x4
#घोषणा WCD9335_DMIC_CLK_DIV_16  0x5
#घोषणा WCD9335_DMIC_CLK_DRIVE_DEFAULT 0x02
#घोषणा WCD9335_AMIC_PWR_LEVEL_LP 0
#घोषणा WCD9335_AMIC_PWR_LEVEL_DEFAULT 1
#घोषणा WCD9335_AMIC_PWR_LEVEL_HP 2
#घोषणा WCD9335_AMIC_PWR_LVL_MASK 0x60
#घोषणा WCD9335_AMIC_PWR_LVL_SHIFT 0x5

#घोषणा WCD9335_DEC_PWR_LVL_MASK 0x06
#घोषणा WCD9335_DEC_PWR_LVL_LP 0x02
#घोषणा WCD9335_DEC_PWR_LVL_HP 0x04
#घोषणा WCD9335_DEC_PWR_LVL_DF 0x00

#घोषणा WCD9335_SLIM_RX_CH(p) \
	अणु.port = p + WCD9335_RX_START, .shअगरt = p,पूर्ण

#घोषणा WCD9335_SLIM_TX_CH(p) \
	अणु.port = p, .shअगरt = p,पूर्ण

/* vout step value */
#घोषणा WCD9335_CALCULATE_VOUT_D(req_mv) (((req_mv - 650) * 10) / 25)

#घोषणा WCD9335_INTERPOLATOR_PATH(id)			\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP2"पूर्ण,	\
	अणु"RX INT" #id " SEC MIX", शून्य, "RX INT" #id "_2 MUX"पूर्ण,		\
	अणु"RX INT" #id " SEC MIX", शून्य, "RX INT" #id "_1 MIX1"पूर्ण,	\
	अणु"RX INT" #id " MIX2", शून्य, "RX INT" #id " SEC MIX"पूर्ण,		\
	अणु"RX INT" #id " INTERP", शून्य, "RX INT" #id " MIX2"पूर्ण

#घोषणा WCD9335_ADC_MUX_PATH(id)			\
	अणु"AIF1_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id " MUX"पूर्ण, \
	अणु"AIF2_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id " MUX"पूर्ण, \
	अणु"AIF3_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id " MUX"पूर्ण, \
	अणु"SLIM TX" #id " MUX", "DEC" #id, "ADC MUX" #idपूर्ण, \
	अणु"ADC MUX" #id, "DMIC", "DMIC MUX" #idपूर्ण,	\
	अणु"ADC MUX" #id, "AMIC", "AMIC MUX" #idपूर्ण,	\
	अणु"DMIC MUX" #id, "DMIC0", "DMIC0"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC1", "DMIC1"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC2", "DMIC2"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC3", "DMIC3"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC4", "DMIC4"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC5", "DMIC5"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC1", "ADC1"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC2", "ADC2"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC3", "ADC3"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC4", "ADC4"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC5", "ADC5"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC6", "ADC6"पूर्ण

क्रमागत अणु
	WCD9335_RX0 = 0,
	WCD9335_RX1,
	WCD9335_RX2,
	WCD9335_RX3,
	WCD9335_RX4,
	WCD9335_RX5,
	WCD9335_RX6,
	WCD9335_RX7,
	WCD9335_RX8,
	WCD9335_RX9,
	WCD9335_RX10,
	WCD9335_RX11,
	WCD9335_RX12,
	WCD9335_RX_MAX,
पूर्ण;

क्रमागत अणु
	WCD9335_TX0 = 0,
	WCD9335_TX1,
	WCD9335_TX2,
	WCD9335_TX3,
	WCD9335_TX4,
	WCD9335_TX5,
	WCD9335_TX6,
	WCD9335_TX7,
	WCD9335_TX8,
	WCD9335_TX9,
	WCD9335_TX10,
	WCD9335_TX11,
	WCD9335_TX12,
	WCD9335_TX13,
	WCD9335_TX14,
	WCD9335_TX15,
	WCD9335_TX_MAX,
पूर्ण;

क्रमागत अणु
	SIDO_SOURCE_INTERNAL = 0,
	SIDO_SOURCE_RCO_BG,
पूर्ण;

क्रमागत wcd9335_siकरो_voltage अणु
	SIDO_VOLTAGE_SVS_MV = 950,
	SIDO_VOLTAGE_NOMINAL_MV = 1100,
पूर्ण;

क्रमागत अणु
	AIF1_PB = 0,
	AIF1_CAP,
	AIF2_PB,
	AIF2_CAP,
	AIF3_PB,
	AIF3_CAP,
	AIF4_PB,
	NUM_CODEC_DAIS,
पूर्ण;

क्रमागत अणु
	COMPANDER_1, /* HPH_L */
	COMPANDER_2, /* HPH_R */
	COMPANDER_3, /* LO1_DIFF */
	COMPANDER_4, /* LO2_DIFF */
	COMPANDER_5, /* LO3_SE */
	COMPANDER_6, /* LO4_SE */
	COMPANDER_7, /* SWR SPK CH1 */
	COMPANDER_8, /* SWR SPK CH2 */
	COMPANDER_MAX,
पूर्ण;

क्रमागत अणु
	INTn_2_INP_SEL_ZERO = 0,
	INTn_2_INP_SEL_RX0,
	INTn_2_INP_SEL_RX1,
	INTn_2_INP_SEL_RX2,
	INTn_2_INP_SEL_RX3,
	INTn_2_INP_SEL_RX4,
	INTn_2_INP_SEL_RX5,
	INTn_2_INP_SEL_RX6,
	INTn_2_INP_SEL_RX7,
	INTn_2_INP_SEL_PROXIMITY,
पूर्ण;

क्रमागत अणु
	INTn_1_MIX_INP_SEL_ZERO = 0,
	INTn_1_MIX_INP_SEL_DEC0,
	INTn_1_MIX_INP_SEL_DEC1,
	INTn_1_MIX_INP_SEL_IIR0,
	INTn_1_MIX_INP_SEL_IIR1,
	INTn_1_MIX_INP_SEL_RX0,
	INTn_1_MIX_INP_SEL_RX1,
	INTn_1_MIX_INP_SEL_RX2,
	INTn_1_MIX_INP_SEL_RX3,
	INTn_1_MIX_INP_SEL_RX4,
	INTn_1_MIX_INP_SEL_RX5,
	INTn_1_MIX_INP_SEL_RX6,
	INTn_1_MIX_INP_SEL_RX7,

पूर्ण;

क्रमागत अणु
	INTERP_EAR = 0,
	INTERP_HPHL,
	INTERP_HPHR,
	INTERP_LO1,
	INTERP_LO2,
	INTERP_LO3,
	INTERP_LO4,
	INTERP_SPKR1,
	INTERP_SPKR2,
पूर्ण;

क्रमागत wcd_घड़ी_प्रकारype अणु
	WCD_CLK_OFF,
	WCD_CLK_RCO,
	WCD_CLK_MCLK,
पूर्ण;

क्रमागत अणु
	MIC_BIAS_1 = 1,
	MIC_BIAS_2,
	MIC_BIAS_3,
	MIC_BIAS_4
पूर्ण;

क्रमागत अणु
	MICB_PULLUP_ENABLE,
	MICB_PULLUP_DISABLE,
	MICB_ENABLE,
	MICB_DISABLE,
पूर्ण;

काष्ठा wcd9335_slim_ch अणु
	u32 ch_num;
	u16 port;
	u16 shअगरt;
	काष्ठा list_head list;
पूर्ण;

काष्ठा wcd_slim_codec_dai_data अणु
	काष्ठा list_head slim_ch_list;
	काष्ठा slim_stream_config sconfig;
	काष्ठा slim_stream_runसमय *srunसमय;
पूर्ण;

काष्ठा wcd9335_codec अणु
	काष्ठा device *dev;
	काष्ठा clk *mclk;
	काष्ठा clk *native_clk;
	u32 mclk_rate;
	u8 version;

	काष्ठा slim_device *slim;
	काष्ठा slim_device *slim_अगरc_dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap *अगर_regmap;
	काष्ठा regmap_irq_chip_data *irq_data;

	काष्ठा wcd9335_slim_ch rx_chs[WCD9335_RX_MAX];
	काष्ठा wcd9335_slim_ch tx_chs[WCD9335_TX_MAX];
	u32 num_rx_port;
	u32 num_tx_port;

	पूर्णांक siकरो_input_src;
	क्रमागत wcd9335_siकरो_voltage siकरो_voltage;

	काष्ठा wcd_slim_codec_dai_data dai[NUM_CODEC_DAIS];
	काष्ठा snd_soc_component *component;

	पूर्णांक master_bias_users;
	पूर्णांक clk_mclk_users;
	पूर्णांक clk_rco_users;
	पूर्णांक siकरो_ccl_cnt;
	क्रमागत wcd_घड़ी_प्रकारype clk_type;

	काष्ठा wcd_clsh_ctrl *clsh_ctrl;
	u32 hph_mode;
	पूर्णांक prim_पूर्णांक_users[WCD9335_NUM_INTERPOLATORS];

	पूर्णांक comp_enabled[COMPANDER_MAX];

	पूर्णांक पूर्णांकr1;
	पूर्णांक reset_gpio;
	काष्ठा regulator_bulk_data supplies[WCD9335_MAX_SUPPLY];

	अचिन्हित पूर्णांक rx_port_value;
	अचिन्हित पूर्णांक tx_port_value;
	पूर्णांक hph_l_gain;
	पूर्णांक hph_r_gain;
	u32 rx_bias_count;

	/*TX*/
	पूर्णांक micb_ref[WCD9335_MAX_MICBIAS];
	पूर्णांक pullup_ref[WCD9335_MAX_MICBIAS];

	पूर्णांक dmic_0_1_clk_cnt;
	पूर्णांक dmic_2_3_clk_cnt;
	पूर्णांक dmic_4_5_clk_cnt;
	पूर्णांक dmic_sample_rate;
	पूर्णांक mad_dmic_sample_rate;

	पूर्णांक native_clk_users;
पूर्ण;

काष्ठा wcd9335_irq अणु
	पूर्णांक irq;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *data);
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा wcd9335_slim_ch wcd9335_tx_chs[WCD9335_TX_MAX] = अणु
	WCD9335_SLIM_TX_CH(0),
	WCD9335_SLIM_TX_CH(1),
	WCD9335_SLIM_TX_CH(2),
	WCD9335_SLIM_TX_CH(3),
	WCD9335_SLIM_TX_CH(4),
	WCD9335_SLIM_TX_CH(5),
	WCD9335_SLIM_TX_CH(6),
	WCD9335_SLIM_TX_CH(7),
	WCD9335_SLIM_TX_CH(8),
	WCD9335_SLIM_TX_CH(9),
	WCD9335_SLIM_TX_CH(10),
	WCD9335_SLIM_TX_CH(11),
	WCD9335_SLIM_TX_CH(12),
	WCD9335_SLIM_TX_CH(13),
	WCD9335_SLIM_TX_CH(14),
	WCD9335_SLIM_TX_CH(15),
पूर्ण;

अटल स्थिर काष्ठा wcd9335_slim_ch wcd9335_rx_chs[WCD9335_RX_MAX] = अणु
	WCD9335_SLIM_RX_CH(0),	 /* 16 */
	WCD9335_SLIM_RX_CH(1),	 /* 17 */
	WCD9335_SLIM_RX_CH(2),
	WCD9335_SLIM_RX_CH(3),
	WCD9335_SLIM_RX_CH(4),
	WCD9335_SLIM_RX_CH(5),
	WCD9335_SLIM_RX_CH(6),
	WCD9335_SLIM_RX_CH(7),
	WCD9335_SLIM_RX_CH(8),
	WCD9335_SLIM_RX_CH(9),
	WCD9335_SLIM_RX_CH(10),
	WCD9335_SLIM_RX_CH(11),
	WCD9335_SLIM_RX_CH(12),
पूर्ण;

काष्ठा पूर्णांकerp_sample_rate अणु
	पूर्णांक rate;
	पूर्णांक rate_val;
पूर्ण;

अटल काष्ठा पूर्णांकerp_sample_rate पूर्णांक_mix_rate_val[] = अणु
	अणु48000, 0x4पूर्ण,	/* 48K */
	अणु96000, 0x5पूर्ण,	/* 96K */
	अणु192000, 0x6पूर्ण,	/* 192K */
पूर्ण;

अटल काष्ठा पूर्णांकerp_sample_rate पूर्णांक_prim_rate_val[] = अणु
	अणु8000, 0x0पूर्ण,	/* 8K */
	अणु16000, 0x1पूर्ण,	/* 16K */
	अणु24000, -EINVALपूर्ण,/* 24K */
	अणु32000, 0x3पूर्ण,	/* 32K */
	अणु48000, 0x4पूर्ण,	/* 48K */
	अणु96000, 0x5पूर्ण,	/* 96K */
	अणु192000, 0x6पूर्ण,	/* 192K */
	अणु384000, 0x7पूर्ण,	/* 384K */
	अणु44100, 0x8पूर्ण, /* 44.1K */
पूर्ण;

काष्ठा wcd9335_reg_mask_val अणु
	u16 reg;
	u8 mask;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा wcd9335_reg_mask_val wcd9335_codec_reg_init[] = अणु
	/* Rbuckfly/R_EAR(32) */
	अणुWCD9335_CDC_CLSH_K2_MSB, 0x0F, 0x00पूर्ण,
	अणुWCD9335_CDC_CLSH_K2_LSB, 0xFF, 0x60पूर्ण,
	अणुWCD9335_CPE_SS_DMIC_CFG, 0x80, 0x00पूर्ण,
	अणुWCD9335_CDC_BOOST0_BOOST_CTL, 0x70, 0x50पूर्ण,
	अणुWCD9335_CDC_BOOST1_BOOST_CTL, 0x70, 0x50पूर्ण,
	अणुWCD9335_CDC_RX7_RX_PATH_CFG1, 0x08, 0x08पूर्ण,
	अणुWCD9335_CDC_RX8_RX_PATH_CFG1, 0x08, 0x08पूर्ण,
	अणुWCD9335_ANA_LO_1_2, 0x3C, 0X3Cपूर्ण,
	अणुWCD9335_DIFF_LO_COM_SWCAP_REFBUF_FREQ, 0x70, 0x00पूर्ण,
	अणुWCD9335_DIFF_LO_COM_PA_FREQ, 0x70, 0x40पूर्ण,
	अणुWCD9335_SOC_MAD_AUDIO_CTL_2, 0x03, 0x03पूर्ण,
	अणुWCD9335_CDC_TOP_TOP_CFG1, 0x02, 0x02पूर्ण,
	अणुWCD9335_CDC_TOP_TOP_CFG1, 0x01, 0x01पूर्ण,
	अणुWCD9335_EAR_CMBUFF, 0x08, 0x00पूर्ण,
	अणुWCD9335_CDC_TX9_SPKR_PROT_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_TX10_SPKR_PROT_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_TX11_SPKR_PROT_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_TX12_SPKR_PROT_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_COMPANDER7_CTL3, 0x80, 0x80पूर्ण,
	अणुWCD9335_CDC_COMPANDER8_CTL3, 0x80, 0x80पूर्ण,
	अणुWCD9335_CDC_COMPANDER7_CTL7, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_COMPANDER8_CTL7, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX0_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX1_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX2_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX3_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX4_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX5_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX6_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX7_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX8_RX_PATH_CFG0, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX0_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX1_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX2_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX3_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX4_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX5_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX6_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX7_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_RX8_RX_PATH_MIX_CFG, 0x01, 0x01पूर्ण,
	अणुWCD9335_VBADC_IBIAS_FE, 0x0C, 0x08पूर्ण,
	अणुWCD9335_RCO_CTRL_2, 0x0F, 0x08पूर्ण,
	अणुWCD9335_RX_BIAS_FLYB_MID_RST, 0xF0, 0x10पूर्ण,
	अणुWCD9335_FLYBACK_CTRL_1, 0x20, 0x20पूर्ण,
	अणुWCD9335_HPH_OCP_CTL, 0xFF, 0x5Aपूर्ण,
	अणुWCD9335_HPH_L_TEST, 0x01, 0x01पूर्ण,
	अणुWCD9335_HPH_R_TEST, 0x01, 0x01पूर्ण,
	अणुWCD9335_CDC_BOOST0_BOOST_CFG1, 0x3F, 0x12पूर्ण,
	अणुWCD9335_CDC_BOOST0_BOOST_CFG2, 0x1C, 0x08पूर्ण,
	अणुWCD9335_CDC_COMPANDER7_CTL7, 0x1E, 0x18पूर्ण,
	अणुWCD9335_CDC_BOOST1_BOOST_CFG1, 0x3F, 0x12पूर्ण,
	अणुWCD9335_CDC_BOOST1_BOOST_CFG2, 0x1C, 0x08पूर्ण,
	अणुWCD9335_CDC_COMPANDER8_CTL7, 0x1E, 0x18पूर्ण,
	अणुWCD9335_CDC_TX0_TX_PATH_SEC7, 0xFF, 0x45पूर्ण,
	अणुWCD9335_CDC_RX0_RX_PATH_SEC0, 0xFC, 0xF4पूर्ण,
	अणुWCD9335_HPH_REFBUFF_LP_CTL, 0x08, 0x08पूर्ण,
	अणुWCD9335_HPH_REFBUFF_LP_CTL, 0x06, 0x02पूर्ण,
पूर्ण;

/* Cutoff frequency क्रम high pass filter */
अटल स्थिर अक्षर * स्थिर cf_text[] = अणु
	"CF_NEG_3DB_4HZ", "CF_NEG_3DB_75HZ", "CF_NEG_3DB_150HZ"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_cf_text[] = अणु
	"CF_NEG_3DB_4HZ", "CF_NEG_3DB_75HZ", "CF_NEG_3DB_150HZ",
	"CF_NEG_3DB_0P48HZ"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक0_7_mix_mux_text[] = अणु
	"ZERO", "RX0", "RX1", "RX2", "RX3", "RX4", "RX5",
	"RX6", "RX7", "PROXIMITY"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक_mix_mux_text[] = अणु
	"ZERO", "RX0", "RX1", "RX2", "RX3", "RX4", "RX5",
	"RX6", "RX7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_prim_mix_text[] = अणु
	"ZERO", "DEC0", "DEC1", "IIR0", "IIR1", "RX0", "RX1", "RX2",
	"RX3", "RX4", "RX5", "RX6", "RX7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक_dem_inp_mux_text[] = अणु
	"NORMAL_DSM_OUT", "CLSH_DSM_OUT",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक0_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT0 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT1 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT2 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक3_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT3 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक4_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT4 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक5_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT5 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक6_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT6 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक7_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT7 MIX2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक8_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT8 SEC MIX"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_hph_mode_mux_text[] = अणु
	"Class H Invalid", "Class-H Hi-Fi", "Class-H Low Power", "Class-AB",
	"Class-H Hi-Fi Low Power"
पूर्ण;

अटल स्थिर अक्षर *स्थिर slim_rx_mux_text[] = अणु
	"ZERO", "AIF1_PB", "AIF2_PB", "AIF3_PB", "AIF4_PB",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_mux_text[] = अणु
	"DMIC", "AMIC", "ANC_FB_TUNE1", "ANC_FB_TUNE2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic_mux_text[] = अणु
	"ZERO", "DMIC0", "DMIC1", "DMIC2", "DMIC3", "DMIC4", "DMIC5",
	"SMIC0", "SMIC1", "SMIC2", "SMIC3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic_mux_alt_text[] = अणु
	"ZERO", "DMIC0", "DMIC1", "DMIC2", "DMIC3", "DMIC4", "DMIC5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर amic_mux_text[] = अणु
	"ZERO", "ADC1", "ADC2", "ADC3", "ADC4", "ADC5", "ADC6"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx0_mux_text[] = अणु
	"ZERO", "RX_MIX_TX0", "DEC0", "DEC0_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx1_mux_text[] = अणु
	"ZERO", "RX_MIX_TX1", "DEC1", "DEC1_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx2_mux_text[] = अणु
	"ZERO", "RX_MIX_TX2", "DEC2", "DEC2_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx3_mux_text[] = अणु
	"ZERO", "RX_MIX_TX3", "DEC3", "DEC3_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx4_mux_text[] = अणु
	"ZERO", "RX_MIX_TX4", "DEC4", "DEC4_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx5_mux_text[] = अणु
	"ZERO", "RX_MIX_TX5", "DEC5", "DEC5_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx6_mux_text[] = अणु
	"ZERO", "RX_MIX_TX6", "DEC6", "DEC6_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx7_mux_text[] = अणु
	"ZERO", "RX_MIX_TX7", "DEC7", "DEC7_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sb_tx8_mux_text[] = अणु
	"ZERO", "RX_MIX_TX8", "DEC8", "DEC8_192"
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -8400, 100, -8400);
अटल स्थिर DECLARE_TLV_DB_SCALE(line_gain, 0, 7, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(analog_gain, 0, 25, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(ear_pa_gain, 0, 150, 0);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec0_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX0_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX1_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec2_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX2_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec3_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX3_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec4_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX4_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec5_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX5_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec6_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX6_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec7_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX7_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec8_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX8_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक0_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX0_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक0_2_क्रमागत, WCD9335_CDC_RX0_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक1_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX1_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक1_2_क्रमागत, WCD9335_CDC_RX1_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक2_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX2_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक2_2_क्रमागत, WCD9335_CDC_RX2_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक3_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX3_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक3_2_क्रमागत, WCD9335_CDC_RX3_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक4_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX4_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक4_2_क्रमागत, WCD9335_CDC_RX4_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक5_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX5_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक5_2_क्रमागत, WCD9335_CDC_RX5_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक6_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX6_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक6_2_क्रमागत, WCD9335_CDC_RX6_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक7_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX7_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक7_2_क्रमागत, WCD9335_CDC_RX7_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक8_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX8_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक8_2_क्रमागत, WCD9335_CDC_RX8_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_hph_mode_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(rx_hph_mode_mux_text),
			    rx_hph_mode_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत slim_rx_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(slim_rx_mux_text), slim_rx_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT0_CFG1, 0, 10,
			rx_पूर्णांक0_7_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT1_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT2_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT3_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT4_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक5_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT5_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक6_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT6_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT7_CFG1, 0, 10,
			rx_पूर्णांक0_7_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT8_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT0_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT0_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT0_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT1_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT1_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT1_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT2_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT2_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT2_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT3_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT3_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT3_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT4_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT4_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT4_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक5_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT5_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक5_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT5_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक5_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT5_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक6_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT6_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक6_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT6_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक6_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT6_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT7_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT7_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT7_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT8_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT8_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX_INP_MUX_RX_INT8_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX0_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX1_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX2_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX0_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक0_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX1_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX2_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX3_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक3_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX4_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक4_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक5_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX5_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक5_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक6_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX6_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक6_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX7_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक7_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_RX8_RX_PATH_CTL, 5, 2,
			rx_पूर्णांक8_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG1, 0, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX1_CFG1, 0, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX2_CFG1, 0, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux3_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX3_CFG1, 0, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux4_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0, 6, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux5_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX5_CFG0, 6, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux6_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX6_CFG0, 6, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux7_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX7_CFG0, 6, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux8_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX8_CFG0, 6, 4,
			adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux0_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG0, 3, 11,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX1_CFG0, 3, 11,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux2_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX2_CFG0, 3, 11,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux3_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX3_CFG0, 3, 11,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux4_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0, 3, 7,
			dmic_mux_alt_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux5_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX5_CFG0, 3, 7,
			dmic_mux_alt_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux6_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX6_CFG0, 3, 7,
			dmic_mux_alt_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux7_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX7_CFG0, 3, 7,
			dmic_mux_alt_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux8_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX8_CFG0, 3, 7,
			dmic_mux_alt_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux0_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux1_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX1_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux2_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX2_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux3_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX3_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux4_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux5_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX5_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux6_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX6_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux7_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX7_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux8_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_TX_INP_MUX_ADC_MUX8_CFG0, 0, 7,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx0_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG0, 0, 4,
			sb_tx0_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG0, 2, 4,
			sb_tx1_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx2_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG0, 4, 4,
			sb_tx2_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx3_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG0, 6, 4,
			sb_tx3_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx4_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG1, 0, 4,
			sb_tx4_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx5_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG1, 2, 4,
			sb_tx5_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx6_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG1, 4, 4,
			sb_tx6_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx7_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG1, 6, 4,
			sb_tx7_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत sb_tx8_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD9335_CDC_IF_ROUTER_TX_MUX_CFG2, 0, 4,
			sb_tx8_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_2_mux =
	SOC_DAPM_ENUM("RX INT0_2 MUX Mux", rx_पूर्णांक0_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_2_mux =
	SOC_DAPM_ENUM("RX INT1_2 MUX Mux", rx_पूर्णांक1_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_2_mux =
	SOC_DAPM_ENUM("RX INT2_2 MUX Mux", rx_पूर्णांक2_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_2_mux =
	SOC_DAPM_ENUM("RX INT3_2 MUX Mux", rx_पूर्णांक3_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_2_mux =
	SOC_DAPM_ENUM("RX INT4_2 MUX Mux", rx_पूर्णांक4_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक5_2_mux =
	SOC_DAPM_ENUM("RX INT5_2 MUX Mux", rx_पूर्णांक5_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक6_2_mux =
	SOC_DAPM_ENUM("RX INT6_2 MUX Mux", rx_पूर्णांक6_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_2_mux =
	SOC_DAPM_ENUM("RX INT7_2 MUX Mux", rx_पूर्णांक7_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_2_mux =
	SOC_DAPM_ENUM("RX INT8_2 MUX Mux", rx_पूर्णांक8_2_mux_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT0_1 MIX1 INP0 Mux", rx_पूर्णांक0_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT0_1 MIX1 INP1 Mux", rx_पूर्णांक0_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT0_1 MIX1 INP2 Mux", rx_पूर्णांक0_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT1_1 MIX1 INP0 Mux", rx_पूर्णांक1_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT1_1 MIX1 INP1 Mux", rx_पूर्णांक1_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT1_1 MIX1 INP2 Mux", rx_पूर्णांक1_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT2_1 MIX1 INP0 Mux", rx_पूर्णांक2_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT2_1 MIX1 INP1 Mux", rx_पूर्णांक2_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT2_1 MIX1 INP2 Mux", rx_पूर्णांक2_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT3_1 MIX1 INP0 Mux", rx_पूर्णांक3_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT3_1 MIX1 INP1 Mux", rx_पूर्णांक3_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT3_1 MIX1 INP2 Mux", rx_पूर्णांक3_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT4_1 MIX1 INP0 Mux", rx_पूर्णांक4_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT4_1 MIX1 INP1 Mux", rx_पूर्णांक4_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT4_1 MIX1 INP2 Mux", rx_पूर्णांक4_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक5_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT5_1 MIX1 INP0 Mux", rx_पूर्णांक5_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक5_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT5_1 MIX1 INP1 Mux", rx_पूर्णांक5_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक5_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT5_1 MIX1 INP2 Mux", rx_पूर्णांक5_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक6_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT6_1 MIX1 INP0 Mux", rx_पूर्णांक6_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक6_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT6_1 MIX1 INP1 Mux", rx_पूर्णांक6_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक6_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT6_1 MIX1 INP2 Mux", rx_पूर्णांक6_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT7_1 MIX1 INP0 Mux", rx_पूर्णांक7_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT7_1 MIX1 INP1 Mux", rx_पूर्णांक7_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT7_1 MIX1 INP2 Mux", rx_पूर्णांक7_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_1_mix_inp0_mux =
	SOC_DAPM_ENUM("RX INT8_1 MIX1 INP0 Mux", rx_पूर्णांक8_1_mix_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_1_mix_inp1_mux =
	SOC_DAPM_ENUM("RX INT8_1 MIX1 INP1 Mux", rx_पूर्णांक8_1_mix_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_1_mix_inp2_mux =
	SOC_DAPM_ENUM("RX INT8_1 MIX1 INP2 Mux", rx_पूर्णांक8_1_mix_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT0 INTERP Mux", rx_पूर्णांक0_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT1 INTERP Mux", rx_पूर्णांक1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT2 INTERP Mux", rx_पूर्णांक2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT3 INTERP Mux", rx_पूर्णांक3_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT4 INTERP Mux", rx_पूर्णांक4_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक5_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT5 INTERP Mux", rx_पूर्णांक5_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक6_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT6 INTERP Mux", rx_पूर्णांक6_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT7 INTERP Mux", rx_पूर्णांक7_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT8 INTERP Mux", rx_पूर्णांक8_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux0 =
	SOC_DAPM_ENUM("DMIC MUX0 Mux", tx_dmic_mux0_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux1 =
	SOC_DAPM_ENUM("DMIC MUX1 Mux", tx_dmic_mux1_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux2 =
	SOC_DAPM_ENUM("DMIC MUX2 Mux", tx_dmic_mux2_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux3 =
	SOC_DAPM_ENUM("DMIC MUX3 Mux", tx_dmic_mux3_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux4 =
	SOC_DAPM_ENUM("DMIC MUX4 Mux", tx_dmic_mux4_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux5 =
	SOC_DAPM_ENUM("DMIC MUX5 Mux", tx_dmic_mux5_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux6 =
	SOC_DAPM_ENUM("DMIC MUX6 Mux", tx_dmic_mux6_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux7 =
	SOC_DAPM_ENUM("DMIC MUX7 Mux", tx_dmic_mux7_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dmic_mux8 =
	SOC_DAPM_ENUM("DMIC MUX8 Mux", tx_dmic_mux8_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux0 =
	SOC_DAPM_ENUM("AMIC MUX0 Mux", tx_amic_mux0_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux1 =
	SOC_DAPM_ENUM("AMIC MUX1 Mux", tx_amic_mux1_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux2 =
	SOC_DAPM_ENUM("AMIC MUX2 Mux", tx_amic_mux2_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux3 =
	SOC_DAPM_ENUM("AMIC MUX3 Mux", tx_amic_mux3_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux4 =
	SOC_DAPM_ENUM("AMIC MUX4 Mux", tx_amic_mux4_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux5 =
	SOC_DAPM_ENUM("AMIC MUX5 Mux", tx_amic_mux5_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux6 =
	SOC_DAPM_ENUM("AMIC MUX6 Mux", tx_amic_mux6_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux7 =
	SOC_DAPM_ENUM("AMIC MUX7 Mux", tx_amic_mux7_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic_mux8 =
	SOC_DAPM_ENUM("AMIC MUX8 Mux", tx_amic_mux8_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx0_mux =
	SOC_DAPM_ENUM("SLIM TX0 MUX Mux", sb_tx0_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx1_mux =
	SOC_DAPM_ENUM("SLIM TX1 MUX Mux", sb_tx1_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx2_mux =
	SOC_DAPM_ENUM("SLIM TX2 MUX Mux", sb_tx2_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx3_mux =
	SOC_DAPM_ENUM("SLIM TX3 MUX Mux", sb_tx3_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx4_mux =
	SOC_DAPM_ENUM("SLIM TX4 MUX Mux", sb_tx4_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx5_mux =
	SOC_DAPM_ENUM("SLIM TX5 MUX Mux", sb_tx5_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx6_mux =
	SOC_DAPM_ENUM("SLIM TX6 MUX Mux", sb_tx6_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx7_mux =
	SOC_DAPM_ENUM("SLIM TX7 MUX Mux", sb_tx7_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sb_tx8_mux =
	SOC_DAPM_ENUM("SLIM TX8 MUX Mux", sb_tx8_mux_क्रमागत);

अटल पूर्णांक slim_rx_mux_get(काष्ठा snd_kcontrol *kc,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(dapm->dev);

	ucontrol->value.क्रमागतerated.item[0] = wcd->rx_port_value;

	वापस 0;
पूर्ण

अटल पूर्णांक slim_rx_mux_put(काष्ठा snd_kcontrol *kc,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(w->dapm->dev);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kc->निजी_value;
	काष्ठा snd_soc_dapm_update *update = शून्य;
	u32 port_id = w->shअगरt;

	wcd->rx_port_value = ucontrol->value.क्रमागतerated.item[0];

	चयन (wcd->rx_port_value) अणु
	हाल 0:
		list_del_init(&wcd->rx_chs[port_id].list);
		अवरोध;
	हाल 1:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF1_PB].slim_ch_list);
		अवरोध;
	हाल 2:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF2_PB].slim_ch_list);
		अवरोध;
	हाल 3:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF3_PB].slim_ch_list);
		अवरोध;
	हाल 4:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF4_PB].slim_ch_list);
		अवरोध;
	शेष:
		dev_err(wcd->dev, "Unknown AIF %d\n", wcd->rx_port_value);
		जाओ err;
	पूर्ण

	snd_soc_dapm_mux_update_घातer(w->dapm, kc, wcd->rx_port_value,
				      e, update);

	वापस 0;
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक slim_tx_mixer_get(काष्ठा snd_kcontrol *kc,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(dapm->dev);

	ucontrol->value.पूर्णांकeger.value[0] = wcd->tx_port_value;

	वापस 0;
पूर्ण

अटल पूर्णांक slim_tx_mixer_put(काष्ठा snd_kcontrol *kc,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(widget->dapm->dev);
	काष्ठा snd_soc_dapm_update *update = शून्य;
	काष्ठा soc_mixer_control *mixer =
			(काष्ठा soc_mixer_control *)kc->निजी_value;
	पूर्णांक enable = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक dai_id = widget->shअगरt;
	पूर्णांक port_id = mixer->shअगरt;

	चयन (dai_id) अणु
	हाल AIF1_CAP:
	हाल AIF2_CAP:
	हाल AIF3_CAP:
		/* only add to the list अगर value not set */
		अगर (enable && !(wcd->tx_port_value & BIT(port_id))) अणु
			wcd->tx_port_value |= BIT(port_id);
			list_add_tail(&wcd->tx_chs[port_id].list,
					&wcd->dai[dai_id].slim_ch_list);
		पूर्ण अन्यथा अगर (!enable && (wcd->tx_port_value & BIT(port_id))) अणु
			wcd->tx_port_value &= ~BIT(port_id);
			list_del_init(&wcd->tx_chs[port_id].list);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(wcd->dev, "Unknown AIF %d\n", dai_id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_dapm_mixer_update_घातer(widget->dapm, kc, enable, update);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new slim_rx_mux[WCD9335_RX_MAX] = अणु
	SOC_DAPM_ENUM_EXT("SLIM RX0 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX1 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX2 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX3 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX4 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX5 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX6 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
	SOC_DAPM_ENUM_EXT("SLIM RX7 Mux", slim_rx_mux_क्रमागत,
			  slim_rx_mux_get, slim_rx_mux_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD9335_TX0, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD9335_TX1, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD9335_TX2, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD9335_TX3, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD9335_TX4, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD9335_TX5, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD9335_TX6, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD9335_TX7, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD9335_TX8, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX9", SND_SOC_NOPM, WCD9335_TX9, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX10", SND_SOC_NOPM, WCD9335_TX10, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX11", SND_SOC_NOPM, WCD9335_TX11, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX13", SND_SOC_NOPM, WCD9335_TX13, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD9335_TX0, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD9335_TX1, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD9335_TX2, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD9335_TX3, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD9335_TX4, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD9335_TX5, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD9335_TX6, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD9335_TX7, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD9335_TX8, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX9", SND_SOC_NOPM, WCD9335_TX9, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX10", SND_SOC_NOPM, WCD9335_TX10, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX11", SND_SOC_NOPM, WCD9335_TX11, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX13", SND_SOC_NOPM, WCD9335_TX13, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर3_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD9335_TX0, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD9335_TX1, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD9335_TX2, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD9335_TX3, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD9335_TX4, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD9335_TX5, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD9335_TX6, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD9335_TX7, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD9335_TX8, 1, 0,
			slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल पूर्णांक wcd9335_put_dec_क्रमागत(काष्ठा snd_kcontrol *kc,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kc);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kc->निजी_value;
	अचिन्हित पूर्णांक val, reg, sel;

	val = ucontrol->value.क्रमागतerated.item[0];

	चयन (e->reg) अणु
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG1:
		reg = WCD9335_CDC_TX0_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX1_CFG1:
		reg = WCD9335_CDC_TX1_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX2_CFG1:
		reg = WCD9335_CDC_TX2_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX3_CFG1:
		reg = WCD9335_CDC_TX3_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0:
		reg = WCD9335_CDC_TX4_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX5_CFG0:
		reg = WCD9335_CDC_TX5_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX6_CFG0:
		reg = WCD9335_CDC_TX6_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX7_CFG0:
		reg = WCD9335_CDC_TX7_TX_PATH_CFG0;
		अवरोध;
	हाल WCD9335_CDC_TX_INP_MUX_ADC_MUX8_CFG0:
		reg = WCD9335_CDC_TX8_TX_PATH_CFG0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* AMIC: 0, DMIC: 1 */
	sel = val ? WCD9335_CDC_TX_ADC_AMIC_SEL : WCD9335_CDC_TX_ADC_DMIC_SEL;
	snd_soc_component_update_bits(component, reg,
				      WCD9335_CDC_TX_ADC_AMIC_DMIC_SEL_MASK,
				      sel);

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kc, ucontrol);
पूर्ण

अटल पूर्णांक wcd9335_पूर्णांक_dem_inp_mux_put(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kc->निजी_value;
	काष्ठा snd_soc_component *component;
	पूर्णांक reg, val;

	component = snd_soc_dapm_kcontrol_component(kc);
	val = ucontrol->value.क्रमागतerated.item[0];

	अगर (e->reg == WCD9335_CDC_RX0_RX_PATH_SEC0)
		reg = WCD9335_CDC_RX0_RX_PATH_CFG0;
	अन्यथा अगर (e->reg == WCD9335_CDC_RX1_RX_PATH_SEC0)
		reg = WCD9335_CDC_RX1_RX_PATH_CFG0;
	अन्यथा अगर (e->reg == WCD9335_CDC_RX2_RX_PATH_SEC0)
		reg = WCD9335_CDC_RX2_RX_PATH_CFG0;
	अन्यथा
		वापस -EINVAL;

	/* Set Look Ahead Delay */
	snd_soc_component_update_bits(component, reg,
				WCD9335_CDC_RX_PATH_CFG0_DLY_ZN_EN_MASK,
				val ? WCD9335_CDC_RX_PATH_CFG0_DLY_ZN_EN : 0);
	/* Set DEM INP Select */
	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kc, ucontrol);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT0 DEM MUX Mux", rx_पूर्णांक0_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT1 DEM MUX Mux", rx_पूर्णांक1_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT2 DEM MUX Mux", rx_पूर्णांक2_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux0 =
	SOC_DAPM_ENUM_EXT("ADC MUX0 Mux", tx_adc_mux0_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux1 =
	SOC_DAPM_ENUM_EXT("ADC MUX1 Mux", tx_adc_mux1_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux2 =
	SOC_DAPM_ENUM_EXT("ADC MUX2 Mux", tx_adc_mux2_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux3 =
	SOC_DAPM_ENUM_EXT("ADC MUX3 Mux", tx_adc_mux3_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux4 =
	SOC_DAPM_ENUM_EXT("ADC MUX4 Mux", tx_adc_mux4_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux5 =
	SOC_DAPM_ENUM_EXT("ADC MUX5 Mux", tx_adc_mux5_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux6 =
	SOC_DAPM_ENUM_EXT("ADC MUX6 Mux", tx_adc_mux6_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux7 =
	SOC_DAPM_ENUM_EXT("ADC MUX7 Mux", tx_adc_mux7_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux8 =
	SOC_DAPM_ENUM_EXT("ADC MUX8 Mux", tx_adc_mux8_chain_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd9335_put_dec_क्रमागत);

अटल पूर्णांक wcd9335_set_mix_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					     पूर्णांक rate_val,
					     u32 rate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	काष्ठा wcd9335_slim_ch *ch;
	पूर्णांक val, j;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		क्रम (j = 0; j < WCD9335_NUM_INTERPOLATORS; j++) अणु
			val = snd_soc_component_पढ़ो(component,
					WCD9335_CDC_RX_INP_MUX_RX_INT_CFG1(j)) &
					WCD9335_CDC_RX_INP_MUX_RX_INT_SEL_MASK;

			अगर (val == (ch->shअगरt + INTn_2_INP_SEL_RX0))
				snd_soc_component_update_bits(component,
						WCD9335_CDC_RX_PATH_MIX_CTL(j),
						WCD9335_CDC_MIX_PCM_RATE_MASK,
						rate_val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_set_prim_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					      u8 rate_val,
					      u32 rate)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	काष्ठा wcd9335_slim_ch *ch;
	u8 cfg0, cfg1, inp0_sel, inp1_sel, inp2_sel;
	पूर्णांक inp, j;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		inp = ch->shअगरt + INTn_1_MIX_INP_SEL_RX0;
		/*
		 * Loop through all पूर्णांकerpolator MUX inमाला_दो and find out
		 * to which पूर्णांकerpolator input, the slim rx port
		 * is connected
		 */
		क्रम (j = 0; j < WCD9335_NUM_INTERPOLATORS; j++) अणु
			cfg0 = snd_soc_component_पढ़ो(comp,
					WCD9335_CDC_RX_INP_MUX_RX_INT_CFG0(j));
			cfg1 = snd_soc_component_पढ़ो(comp,
					WCD9335_CDC_RX_INP_MUX_RX_INT_CFG1(j));

			inp0_sel = cfg0 &
				 WCD9335_CDC_RX_INP_MUX_RX_INT_SEL_MASK;
			inp1_sel = (cfg0 >> 4) &
				 WCD9335_CDC_RX_INP_MUX_RX_INT_SEL_MASK;
			inp2_sel = (cfg1 >> 4) &
				 WCD9335_CDC_RX_INP_MUX_RX_INT_SEL_MASK;

			अगर ((inp0_sel == inp) ||  (inp1_sel == inp) ||
			    (inp2_sel == inp)) अणु
				/* rate is in Hz */
				अगर ((j == 0) && (rate == 44100))
					dev_info(wcd->dev,
						"Cannot set 44.1KHz on INT0\n");
				अन्यथा
					snd_soc_component_update_bits(comp,
						WCD9335_CDC_RX_PATH_CTL(j),
						WCD9335_CDC_MIX_PCM_RATE_MASK,
						rate_val);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_set_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai, u32 rate)
अणु
	पूर्णांक i;

	/* set mixing path rate */
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_mix_rate_val); i++) अणु
		अगर (rate == पूर्णांक_mix_rate_val[i].rate) अणु
			wcd9335_set_mix_पूर्णांकerpolator_rate(dai,
					पूर्णांक_mix_rate_val[i].rate_val, rate);
			अवरोध;
		पूर्ण
	पूर्ण

	/* set primary path sample rate */
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_prim_rate_val); i++) अणु
		अगर (rate == पूर्णांक_prim_rate_val[i].rate) अणु
			wcd9335_set_prim_पूर्णांकerpolator_rate(dai,
					पूर्णांक_prim_rate_val[i].rate_val, rate);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_slim_set_hw_params(काष्ठा wcd9335_codec *wcd,
				 काष्ठा wcd_slim_codec_dai_data *dai_data,
				 पूर्णांक direction)
अणु
	काष्ठा list_head *slim_ch_list = &dai_data->slim_ch_list;
	काष्ठा slim_stream_config *cfg = &dai_data->sconfig;
	काष्ठा wcd9335_slim_ch *ch;
	u16 payload = 0;
	पूर्णांक ret, i;

	cfg->ch_count = 0;
	cfg->direction = direction;
	cfg->port_mask = 0;

	/* Configure slave पूर्णांकerface device */
	list_क्रम_each_entry(ch, slim_ch_list, list) अणु
		cfg->ch_count++;
		payload |= 1 << ch->shअगरt;
		cfg->port_mask |= BIT(ch->port);
	पूर्ण

	cfg->chs = kसुस्मृति(cfg->ch_count, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!cfg->chs)
		वापस -ENOMEM;

	i = 0;
	list_क्रम_each_entry(ch, slim_ch_list, list) अणु
		cfg->chs[i++] = ch->ch_num;
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/* ग_लिखो to पूर्णांकerface device */
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
				WCD9335_SLIM_PGD_RX_PORT_MULTI_CHNL_0(ch->port),
				payload);

			अगर (ret < 0)
				जाओ err;

			/* configure the slave port क्रम water mark and enable*/
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
					WCD9335_SLIM_PGD_RX_PORT_CFG(ch->port),
					WCD9335_SLIM_WATER_MARK_VAL);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
				WCD9335_SLIM_PGD_TX_PORT_MULTI_CHNL_0(ch->port),
				payload & 0x00FF);
			अगर (ret < 0)
				जाओ err;

			/* ports 8,9 */
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
				WCD9335_SLIM_PGD_TX_PORT_MULTI_CHNL_1(ch->port),
				(payload & 0xFF00)>>8);
			अगर (ret < 0)
				जाओ err;

			/* configure the slave port क्रम water mark and enable*/
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
					WCD9335_SLIM_PGD_TX_PORT_CFG(ch->port),
					WCD9335_SLIM_WATER_MARK_VAL);

			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	dai_data->srunसमय = slim_stream_allocate(wcd->slim, "WCD9335-SLIM");

	वापस 0;

err:
	dev_err(wcd->dev, "Error Setting slim hw params\n");
	kमुक्त(cfg->chs);
	cfg->chs = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक wcd9335_set_decimator_rate(काष्ठा snd_soc_dai *dai,
				      u8 rate_val, u32 rate)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा wcd9335_codec *wcd = snd_soc_component_get_drvdata(comp);
	u8 shअगरt = 0, shअगरt_val = 0, tx_mux_sel;
	काष्ठा wcd9335_slim_ch *ch;
	पूर्णांक tx_port, tx_port_reg;
	पूर्णांक decimator = -1;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		tx_port = ch->port;
		अगर ((tx_port == 12) || (tx_port >= 14)) अणु
			dev_err(wcd->dev, "Invalid SLIM TX%u port DAI ID:%d\n",
				tx_port, dai->id);
			वापस -EINVAL;
		पूर्ण
		/* Find the SB TX MUX input - which decimator is connected */
		अगर (tx_port < 4) अणु
			tx_port_reg = WCD9335_CDC_IF_ROUTER_TX_MUX_CFG0;
			shअगरt = (tx_port << 1);
			shअगरt_val = 0x03;
		पूर्ण अन्यथा अगर ((tx_port >= 4) && (tx_port < 8)) अणु
			tx_port_reg = WCD9335_CDC_IF_ROUTER_TX_MUX_CFG1;
			shअगरt = ((tx_port - 4) << 1);
			shअगरt_val = 0x03;
		पूर्ण अन्यथा अगर ((tx_port >= 8) && (tx_port < 11)) अणु
			tx_port_reg = WCD9335_CDC_IF_ROUTER_TX_MUX_CFG2;
			shअगरt = ((tx_port - 8) << 1);
			shअगरt_val = 0x03;
		पूर्ण अन्यथा अगर (tx_port == 11) अणु
			tx_port_reg = WCD9335_CDC_IF_ROUTER_TX_MUX_CFG3;
			shअगरt = 0;
			shअगरt_val = 0x0F;
		पूर्ण अन्यथा अगर (tx_port == 13) अणु
			tx_port_reg = WCD9335_CDC_IF_ROUTER_TX_MUX_CFG3;
			shअगरt = 4;
			shअगरt_val = 0x03;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		tx_mux_sel = snd_soc_component_पढ़ो(comp, tx_port_reg) &
						      (shअगरt_val << shअगरt);

		tx_mux_sel = tx_mux_sel >> shअगरt;
		अगर (tx_port <= 8) अणु
			अगर ((tx_mux_sel == 0x2) || (tx_mux_sel == 0x3))
				decimator = tx_port;
		पूर्ण अन्यथा अगर (tx_port <= 10) अणु
			अगर ((tx_mux_sel == 0x1) || (tx_mux_sel == 0x2))
				decimator = ((tx_port == 9) ? 7 : 6);
		पूर्ण अन्यथा अगर (tx_port == 11) अणु
			अगर ((tx_mux_sel >= 1) && (tx_mux_sel < 7))
				decimator = tx_mux_sel - 1;
		पूर्ण अन्यथा अगर (tx_port == 13) अणु
			अगर ((tx_mux_sel == 0x1) || (tx_mux_sel == 0x2))
				decimator = 5;
		पूर्ण

		अगर (decimator >= 0) अणु
			snd_soc_component_update_bits(comp,
					WCD9335_CDC_TX_PATH_CTL(decimator),
					WCD9335_CDC_TX_PATH_CTL_PCM_RATE_MASK,
					rate_val);
		पूर्ण अन्यथा अगर ((tx_port <= 8) && (tx_mux_sel == 0x01)) अणु
			/* Check अगर the TX Mux input is RX MIX TXn */
			dev_err(wcd->dev, "RX_MIX_TX%u going to SLIM TX%u\n",
				tx_port, tx_port);
		पूर्ण अन्यथा अणु
			dev_err(wcd->dev, "ERROR: Invalid decimator: %d\n",
				decimator);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wcd9335_codec *wcd;
	पूर्णांक ret, tx_fs_rate = 0;

	wcd = snd_soc_component_get_drvdata(dai->component);

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		ret = wcd9335_set_पूर्णांकerpolator_rate(dai, params_rate(params));
		अगर (ret) अणु
			dev_err(wcd->dev, "cannot set sample rate: %u\n",
				params_rate(params));
			वापस ret;
		पूर्ण
		चयन (params_width(params)) अणु
		हाल 16 ... 24:
			wcd->dai[dai->id].sconfig.bps = params_width(params);
			अवरोध;
		शेष:
			dev_err(wcd->dev, "%s: Invalid format 0x%x\n",
				__func__, params_width(params));
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_STREAM_CAPTURE:
		चयन (params_rate(params)) अणु
		हाल 8000:
			tx_fs_rate = 0;
			अवरोध;
		हाल 16000:
			tx_fs_rate = 1;
			अवरोध;
		हाल 32000:
			tx_fs_rate = 3;
			अवरोध;
		हाल 48000:
			tx_fs_rate = 4;
			अवरोध;
		हाल 96000:
			tx_fs_rate = 5;
			अवरोध;
		हाल 192000:
			tx_fs_rate = 6;
			अवरोध;
		हाल 384000:
			tx_fs_rate = 7;
			अवरोध;
		शेष:
			dev_err(wcd->dev, "%s: Invalid TX sample rate: %d\n",
				__func__, params_rate(params));
			वापस -EINVAL;

		पूर्ण

		ret = wcd9335_set_decimator_rate(dai, tx_fs_rate,
						params_rate(params));
		अगर (ret < 0) अणु
			dev_err(wcd->dev, "Cannot set TX Decimator rate\n");
			वापस ret;
		पूर्ण
		चयन (params_width(params)) अणु
		हाल 16 ... 32:
			wcd->dai[dai->id].sconfig.bps = params_width(params);
			अवरोध;
		शेष:
			dev_err(wcd->dev, "%s: Invalid format 0x%x\n",
				__func__, params_width(params));
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(wcd->dev, "Invalid stream type %d\n",
			substream->stream);
		वापस -EINVAL;
	पूर्ण

	wcd->dai[dai->id].sconfig.rate = params_rate(params);
	wcd9335_slim_set_hw_params(wcd, &wcd->dai[dai->id], substream->stream);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wcd_slim_codec_dai_data *dai_data;
	काष्ठा wcd9335_codec *wcd;
	काष्ठा slim_stream_config *cfg;

	wcd = snd_soc_component_get_drvdata(dai->component);

	dai_data = &wcd->dai[dai->id];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		cfg = &dai_data->sconfig;
		slim_stream_prepare(dai_data->srunसमय, cfg);
		slim_stream_enable(dai_data->srunसमय);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		slim_stream_unprepare(dai_data->srunसमय);
		slim_stream_disable(dai_data->srunसमय);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_set_channel_map(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				   अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा wcd9335_codec *wcd;
	पूर्णांक i;

	wcd = snd_soc_component_get_drvdata(dai->component);

	अगर (!tx_slot || !rx_slot) अणु
		dev_err(wcd->dev, "Invalid tx_slot=%p, rx_slot=%p\n",
			tx_slot, rx_slot);
		वापस -EINVAL;
	पूर्ण

	wcd->num_rx_port = rx_num;
	क्रम (i = 0; i < rx_num; i++) अणु
		wcd->rx_chs[i].ch_num = rx_slot[i];
		INIT_LIST_HEAD(&wcd->rx_chs[i].list);
	पूर्ण

	wcd->num_tx_port = tx_num;
	क्रम (i = 0; i < tx_num; i++) अणु
		wcd->tx_chs[i].ch_num = tx_slot[i];
		INIT_LIST_HEAD(&wcd->tx_chs[i].list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_get_channel_map(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				   अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा wcd9335_slim_ch *ch;
	काष्ठा wcd9335_codec *wcd;
	पूर्णांक i = 0;

	wcd = snd_soc_component_get_drvdata(dai->component);

	चयन (dai->id) अणु
	हाल AIF1_PB:
	हाल AIF2_PB:
	हाल AIF3_PB:
	हाल AIF4_PB:
		अगर (!rx_slot || !rx_num) अणु
			dev_err(wcd->dev, "Invalid rx_slot %p or rx_num %p\n",
				rx_slot, rx_num);
			वापस -EINVAL;
		पूर्ण

		list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list)
			rx_slot[i++] = ch->ch_num;

		*rx_num = i;
		अवरोध;
	हाल AIF1_CAP:
	हाल AIF2_CAP:
	हाल AIF3_CAP:
		अगर (!tx_slot || !tx_num) अणु
			dev_err(wcd->dev, "Invalid tx_slot %p or tx_num %p\n",
				tx_slot, tx_num);
			वापस -EINVAL;
		पूर्ण
		list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list)
			tx_slot[i++] = ch->ch_num;

		*tx_num = i;
		अवरोध;
	शेष:
		dev_err(wcd->dev, "Invalid DAI ID %x\n", dai->id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wcd9335_dai_ops = अणु
	.hw_params = wcd9335_hw_params,
	.trigger = wcd9335_trigger,
	.set_channel_map = wcd9335_set_channel_map,
	.get_channel_map = wcd9335_get_channel_map,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wcd9335_slim_dais[] = अणु
	[0] = अणु
		.name = "wcd9335_rx1",
		.id = AIF1_PB,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.rates = WCD9335_RATES_MASK | WCD9335_FRAC_RATES_MASK |
				 SNDRV_PCM_RATE_384000,
			.क्रमmats = WCD9335_FORMATS_S16_S24_LE,
			.rate_max = 384000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[1] = अणु
		.name = "wcd9335_tx1",
		.id = AIF1_CAP,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.rates = WCD9335_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[2] = अणु
		.name = "wcd9335_rx2",
		.id = AIF2_PB,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.rates = WCD9335_RATES_MASK | WCD9335_FRAC_RATES_MASK |
				 SNDRV_PCM_RATE_384000,
			.क्रमmats = WCD9335_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 384000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[3] = अणु
		.name = "wcd9335_tx2",
		.id = AIF2_CAP,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.rates = WCD9335_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[4] = अणु
		.name = "wcd9335_rx3",
		.id = AIF3_PB,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.rates = WCD9335_RATES_MASK | WCD9335_FRAC_RATES_MASK |
				 SNDRV_PCM_RATE_384000,
			.क्रमmats = WCD9335_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 384000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[5] = अणु
		.name = "wcd9335_tx3",
		.id = AIF3_CAP,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.rates = WCD9335_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
	[6] = अणु
		.name = "wcd9335_rx4",
		.id = AIF4_PB,
		.playback = अणु
			.stream_name = "AIF4 Playback",
			.rates = WCD9335_RATES_MASK | WCD9335_FRAC_RATES_MASK |
				 SNDRV_PCM_RATE_384000,
			.क्रमmats = WCD9335_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 384000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd9335_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wcd9335_get_compander(काष्ठा snd_kcontrol *kc,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *)kc->निजी_value)->shअगरt;
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);

	ucontrol->value.पूर्णांकeger.value[0] = wcd->comp_enabled[comp];
	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_set_compander(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *) kc->निजी_value)->shअगरt;
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक sel;

	wcd->comp_enabled[comp] = value;
	sel = value ? WCD9335_HPH_GAIN_SRC_SEL_COMPANDER :
		WCD9335_HPH_GAIN_SRC_SEL_REGISTER;

	/* Any specअगरic रेजिस्टर configuration क्रम compander */
	चयन (comp) अणु
	हाल COMPANDER_1:
		/* Set Gain Source Select based on compander enable/disable */
		snd_soc_component_update_bits(component, WCD9335_HPH_L_EN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		अवरोध;
	हाल COMPANDER_2:
		snd_soc_component_update_bits(component, WCD9335_HPH_R_EN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		अवरोध;
	हाल COMPANDER_5:
		snd_soc_component_update_bits(component, WCD9335_SE_LO_LO3_GAIN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		अवरोध;
	हाल COMPANDER_6:
		snd_soc_component_update_bits(component, WCD9335_SE_LO_LO4_GAIN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_rx_hph_mode_get(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);

	ucontrol->value.क्रमागतerated.item[0] = wcd->hph_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_rx_hph_mode_put(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	u32 mode_val;

	mode_val = ucontrol->value.क्रमागतerated.item[0];

	अगर (mode_val == 0) अणु
		dev_err(wcd->dev, "Invalid HPH Mode, default to ClSH HiFi\n");
		mode_val = CLS_H_HIFI;
	पूर्ण
	wcd->hph_mode = mode_val;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wcd9335_snd_controls[] = अणु
	/* -84dB min - 40dB max */
	SOC_SINGLE_SX_TLV("RX0 Digital Volume", WCD9335_CDC_RX0_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX1 Digital Volume", WCD9335_CDC_RX1_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX2 Digital Volume", WCD9335_CDC_RX2_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX3 Digital Volume", WCD9335_CDC_RX3_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX4 Digital Volume", WCD9335_CDC_RX4_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX5 Digital Volume", WCD9335_CDC_RX5_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX6 Digital Volume", WCD9335_CDC_RX6_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX7 Digital Volume", WCD9335_CDC_RX7_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX8 Digital Volume", WCD9335_CDC_RX8_RX_VOL_CTL,
		0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX0 Mix Digital Volume",
			  WCD9335_CDC_RX0_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX1 Mix Digital Volume",
			  WCD9335_CDC_RX1_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX2 Mix Digital Volume",
			  WCD9335_CDC_RX2_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX3 Mix Digital Volume",
			  WCD9335_CDC_RX3_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX4 Mix Digital Volume",
			  WCD9335_CDC_RX4_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX5 Mix Digital Volume",
			  WCD9335_CDC_RX5_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX6 Mix Digital Volume",
			  WCD9335_CDC_RX6_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX7 Mix Digital Volume",
			  WCD9335_CDC_RX7_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("RX8 Mix Digital Volume",
			  WCD9335_CDC_RX8_RX_VOL_MIX_CTL,
			  0, -84, 40, digital_gain),
	SOC_ENUM("RX INT0_1 HPF cut off", cf_पूर्णांक0_1_क्रमागत),
	SOC_ENUM("RX INT0_2 HPF cut off", cf_पूर्णांक0_2_क्रमागत),
	SOC_ENUM("RX INT1_1 HPF cut off", cf_पूर्णांक1_1_क्रमागत),
	SOC_ENUM("RX INT1_2 HPF cut off", cf_पूर्णांक1_2_क्रमागत),
	SOC_ENUM("RX INT2_1 HPF cut off", cf_पूर्णांक2_1_क्रमागत),
	SOC_ENUM("RX INT2_2 HPF cut off", cf_पूर्णांक2_2_क्रमागत),
	SOC_ENUM("RX INT3_1 HPF cut off", cf_पूर्णांक3_1_क्रमागत),
	SOC_ENUM("RX INT3_2 HPF cut off", cf_पूर्णांक3_2_क्रमागत),
	SOC_ENUM("RX INT4_1 HPF cut off", cf_पूर्णांक4_1_क्रमागत),
	SOC_ENUM("RX INT4_2 HPF cut off", cf_पूर्णांक4_2_क्रमागत),
	SOC_ENUM("RX INT5_1 HPF cut off", cf_पूर्णांक5_1_क्रमागत),
	SOC_ENUM("RX INT5_2 HPF cut off", cf_पूर्णांक5_2_क्रमागत),
	SOC_ENUM("RX INT6_1 HPF cut off", cf_पूर्णांक6_1_क्रमागत),
	SOC_ENUM("RX INT6_2 HPF cut off", cf_पूर्णांक6_2_क्रमागत),
	SOC_ENUM("RX INT7_1 HPF cut off", cf_पूर्णांक7_1_क्रमागत),
	SOC_ENUM("RX INT7_2 HPF cut off", cf_पूर्णांक7_2_क्रमागत),
	SOC_ENUM("RX INT8_1 HPF cut off", cf_पूर्णांक8_1_क्रमागत),
	SOC_ENUM("RX INT8_2 HPF cut off", cf_पूर्णांक8_2_क्रमागत),
	SOC_SINGLE_EXT("COMP1 Switch", SND_SOC_NOPM, COMPANDER_1, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP2 Switch", SND_SOC_NOPM, COMPANDER_2, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP3 Switch", SND_SOC_NOPM, COMPANDER_3, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP4 Switch", SND_SOC_NOPM, COMPANDER_4, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP5 Switch", SND_SOC_NOPM, COMPANDER_5, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP6 Switch", SND_SOC_NOPM, COMPANDER_6, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP7 Switch", SND_SOC_NOPM, COMPANDER_7, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_SINGLE_EXT("COMP8 Switch", SND_SOC_NOPM, COMPANDER_8, 1, 0,
		       wcd9335_get_compander, wcd9335_set_compander),
	SOC_ENUM_EXT("RX HPH Mode", rx_hph_mode_mux_क्रमागत,
		       wcd9335_rx_hph_mode_get, wcd9335_rx_hph_mode_put),

	/* Gain Controls */
	SOC_SINGLE_TLV("EAR PA Volume", WCD9335_ANA_EAR, 4, 4, 1,
		ear_pa_gain),
	SOC_SINGLE_TLV("HPHL Volume", WCD9335_HPH_L_EN, 0, 20, 1,
		line_gain),
	SOC_SINGLE_TLV("HPHR Volume", WCD9335_HPH_R_EN, 0, 20, 1,
		line_gain),
	SOC_SINGLE_TLV("LINEOUT1 Volume", WCD9335_DIFF_LO_LO1_COMPANDER,
			3, 16, 1, line_gain),
	SOC_SINGLE_TLV("LINEOUT2 Volume", WCD9335_DIFF_LO_LO2_COMPANDER,
			3, 16, 1, line_gain),
	SOC_SINGLE_TLV("LINEOUT3 Volume", WCD9335_SE_LO_LO3_GAIN, 0, 20, 1,
			line_gain),
	SOC_SINGLE_TLV("LINEOUT4 Volume", WCD9335_SE_LO_LO4_GAIN, 0, 20, 1,
			line_gain),

	SOC_SINGLE_TLV("ADC1 Volume", WCD9335_ANA_AMIC1, 0, 20, 0,
			analog_gain),
	SOC_SINGLE_TLV("ADC2 Volume", WCD9335_ANA_AMIC2, 0, 20, 0,
			analog_gain),
	SOC_SINGLE_TLV("ADC3 Volume", WCD9335_ANA_AMIC3, 0, 20, 0,
			analog_gain),
	SOC_SINGLE_TLV("ADC4 Volume", WCD9335_ANA_AMIC4, 0, 20, 0,
			analog_gain),
	SOC_SINGLE_TLV("ADC5 Volume", WCD9335_ANA_AMIC5, 0, 20, 0,
			analog_gain),
	SOC_SINGLE_TLV("ADC6 Volume", WCD9335_ANA_AMIC6, 0, 20, 0,
			analog_gain),

	SOC_ENUM("TX0 HPF cut off", cf_dec0_क्रमागत),
	SOC_ENUM("TX1 HPF cut off", cf_dec1_क्रमागत),
	SOC_ENUM("TX2 HPF cut off", cf_dec2_क्रमागत),
	SOC_ENUM("TX3 HPF cut off", cf_dec3_क्रमागत),
	SOC_ENUM("TX4 HPF cut off", cf_dec4_क्रमागत),
	SOC_ENUM("TX5 HPF cut off", cf_dec5_क्रमागत),
	SOC_ENUM("TX6 HPF cut off", cf_dec6_क्रमागत),
	SOC_ENUM("TX7 HPF cut off", cf_dec7_क्रमागत),
	SOC_ENUM("TX8 HPF cut off", cf_dec8_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wcd9335_audio_map[] = अणु
	अणु"SLIM RX0 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX1 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX2 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX3 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX4 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX5 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX6 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,
	अणु"SLIM RX7 MUX", "AIF1_PB", "AIF1 PB"पूर्ण,

	अणु"SLIM RX0 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX1 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX2 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX3 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX4 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX5 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX6 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,
	अणु"SLIM RX7 MUX", "AIF2_PB", "AIF2 PB"पूर्ण,

	अणु"SLIM RX0 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX1 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX2 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX3 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX4 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX5 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX6 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,
	अणु"SLIM RX7 MUX", "AIF3_PB", "AIF3 PB"पूर्ण,

	अणु"SLIM RX0 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX1 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX2 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX3 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX4 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX5 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX6 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,
	अणु"SLIM RX7 MUX", "AIF4_PB", "AIF4 PB"पूर्ण,

	अणु"SLIM RX0", शून्य, "SLIM RX0 MUX"पूर्ण,
	अणु"SLIM RX1", शून्य, "SLIM RX1 MUX"पूर्ण,
	अणु"SLIM RX2", शून्य, "SLIM RX2 MUX"पूर्ण,
	अणु"SLIM RX3", शून्य, "SLIM RX3 MUX"पूर्ण,
	अणु"SLIM RX4", शून्य, "SLIM RX4 MUX"पूर्ण,
	अणु"SLIM RX5", शून्य, "SLIM RX5 MUX"पूर्ण,
	अणु"SLIM RX6", शून्य, "SLIM RX6 MUX"पूर्ण,
	अणु"SLIM RX7", शून्य, "SLIM RX7 MUX"पूर्ण,

	WCD9335_INTERPOLATOR_PATH(0),
	WCD9335_INTERPOLATOR_PATH(1),
	WCD9335_INTERPOLATOR_PATH(2),
	WCD9335_INTERPOLATOR_PATH(3),
	WCD9335_INTERPOLATOR_PATH(4),
	WCD9335_INTERPOLATOR_PATH(5),
	WCD9335_INTERPOLATOR_PATH(6),
	WCD9335_INTERPOLATOR_PATH(7),
	WCD9335_INTERPOLATOR_PATH(8),

	/* EAR PA */
	अणु"RX INT0 DEM MUX", "CLSH_DSM_OUT", "RX INT0 INTERP"पूर्ण,
	अणु"RX INT0 DAC", शून्य, "RX INT0 DEM MUX"पूर्ण,
	अणु"RX INT0 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"EAR PA", शून्य, "RX INT0 DAC"पूर्ण,
	अणु"EAR", शून्य, "EAR PA"पूर्ण,

	/* HPHL */
	अणु"RX INT1 DEM MUX", "CLSH_DSM_OUT", "RX INT1 INTERP"पूर्ण,
	अणु"RX INT1 DAC", शून्य, "RX INT1 DEM MUX"पूर्ण,
	अणु"RX INT1 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHL PA", शून्य, "RX INT1 DAC"पूर्ण,
	अणु"HPHL", शून्य, "HPHL PA"पूर्ण,

	/* HPHR */
	अणु"RX INT2 DEM MUX", "CLSH_DSM_OUT", "RX INT2 INTERP"पूर्ण,
	अणु"RX INT2 DAC", शून्य, "RX INT2 DEM MUX"पूर्ण,
	अणु"RX INT2 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHR PA", शून्य, "RX INT2 DAC"पूर्ण,
	अणु"HPHR", शून्य, "HPHR PA"पूर्ण,

	/* LINEOUT1 */
	अणु"RX INT3 DAC", शून्य, "RX INT3 INTERP"पूर्ण,
	अणु"RX INT3 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT1 PA", शून्य, "RX INT3 DAC"पूर्ण,
	अणु"LINEOUT1", शून्य, "LINEOUT1 PA"पूर्ण,

	/* LINEOUT2 */
	अणु"RX INT4 DAC", शून्य, "RX INT4 INTERP"पूर्ण,
	अणु"RX INT4 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT2 PA", शून्य, "RX INT4 DAC"पूर्ण,
	अणु"LINEOUT2", शून्य, "LINEOUT2 PA"पूर्ण,

	/* LINEOUT3 */
	अणु"RX INT5 DAC", शून्य, "RX INT5 INTERP"पूर्ण,
	अणु"RX INT5 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT3 PA", शून्य, "RX INT5 DAC"पूर्ण,
	अणु"LINEOUT3", शून्य, "LINEOUT3 PA"पूर्ण,

	/* LINEOUT4 */
	अणु"RX INT6 DAC", शून्य, "RX INT6 INTERP"पूर्ण,
	अणु"RX INT6 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT4 PA", शून्य, "RX INT6 DAC"पूर्ण,
	अणु"LINEOUT4", शून्य, "LINEOUT4 PA"पूर्ण,

	/* SLIMBUS Connections */
	अणु"AIF1 CAP", शून्य, "AIF1_CAP Mixer"पूर्ण,
	अणु"AIF2 CAP", शून्य, "AIF2_CAP Mixer"पूर्ण,
	अणु"AIF3 CAP", शून्य, "AIF3_CAP Mixer"पूर्ण,

	/* ADC Mux */
	WCD9335_ADC_MUX_PATH(0),
	WCD9335_ADC_MUX_PATH(1),
	WCD9335_ADC_MUX_PATH(2),
	WCD9335_ADC_MUX_PATH(3),
	WCD9335_ADC_MUX_PATH(4),
	WCD9335_ADC_MUX_PATH(5),
	WCD9335_ADC_MUX_PATH(6),
	WCD9335_ADC_MUX_PATH(7),
	WCD9335_ADC_MUX_PATH(8),

	/* ADC Connections */
	अणु"ADC1", शून्य, "AMIC1"पूर्ण,
	अणु"ADC2", शून्य, "AMIC2"पूर्ण,
	अणु"ADC3", शून्य, "AMIC3"पूर्ण,
	अणु"ADC4", शून्य, "AMIC4"पूर्ण,
	अणु"ADC5", शून्य, "AMIC5"पूर्ण,
	अणु"ADC6", शून्य, "AMIC6"पूर्ण,
पूर्ण;

अटल पूर्णांक wcd9335_micbias_control(काष्ठा snd_soc_component *component,
				   पूर्णांक micb_num, पूर्णांक req, bool is_dapm)
अणु
	काष्ठा wcd9335_codec *wcd = snd_soc_component_get_drvdata(component);
	पूर्णांक micb_index = micb_num - 1;
	u16 micb_reg;

	अगर ((micb_index < 0) || (micb_index > WCD9335_MAX_MICBIAS - 1)) अणु
		dev_err(wcd->dev, "Invalid micbias index, micb_ind:%d\n",
			micb_index);
		वापस -EINVAL;
	पूर्ण

	चयन (micb_num) अणु
	हाल MIC_BIAS_1:
		micb_reg = WCD9335_ANA_MICB1;
		अवरोध;
	हाल MIC_BIAS_2:
		micb_reg = WCD9335_ANA_MICB2;
		अवरोध;
	हाल MIC_BIAS_3:
		micb_reg = WCD9335_ANA_MICB3;
		अवरोध;
	हाल MIC_BIAS_4:
		micb_reg = WCD9335_ANA_MICB4;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: Invalid micbias number: %d\n",
			__func__, micb_num);
		वापस -EINVAL;
	पूर्ण

	चयन (req) अणु
	हाल MICB_PULLUP_ENABLE:
		wcd->pullup_ref[micb_index]++;
		अगर ((wcd->pullup_ref[micb_index] == 1) &&
		    (wcd->micb_ref[micb_index] == 0))
			snd_soc_component_update_bits(component, micb_reg,
							0xC0, 0x80);
		अवरोध;
	हाल MICB_PULLUP_DISABLE:
		wcd->pullup_ref[micb_index]--;
		अगर ((wcd->pullup_ref[micb_index] == 0) &&
		    (wcd->micb_ref[micb_index] == 0))
			snd_soc_component_update_bits(component, micb_reg,
							0xC0, 0x00);
		अवरोध;
	हाल MICB_ENABLE:
		wcd->micb_ref[micb_index]++;
		अगर (wcd->micb_ref[micb_index] == 1)
			snd_soc_component_update_bits(component, micb_reg,
							0xC0, 0x40);
		अवरोध;
	हाल MICB_DISABLE:
		wcd->micb_ref[micb_index]--;
		अगर ((wcd->micb_ref[micb_index] == 0) &&
		    (wcd->pullup_ref[micb_index] > 0))
			snd_soc_component_update_bits(component, micb_reg,
							0xC0, 0x80);
		अन्यथा अगर ((wcd->micb_ref[micb_index] == 0) &&
			 (wcd->pullup_ref[micb_index] == 0)) अणु
			snd_soc_component_update_bits(component, micb_reg,
							0xC0, 0x00);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __wcd9335_codec_enable_micbias(काष्ठा snd_soc_dapm_widget *w,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक micb_num;

	अगर (strnstr(w->name, "MIC BIAS1", माप("MIC BIAS1")))
		micb_num = MIC_BIAS_1;
	अन्यथा अगर (strnstr(w->name, "MIC BIAS2", माप("MIC BIAS2")))
		micb_num = MIC_BIAS_2;
	अन्यथा अगर (strnstr(w->name, "MIC BIAS3", माप("MIC BIAS3")))
		micb_num = MIC_BIAS_3;
	अन्यथा अगर (strnstr(w->name, "MIC BIAS4", माप("MIC BIAS4")))
		micb_num = MIC_BIAS_4;
	अन्यथा
		वापस -EINVAL;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/*
		 * MIC BIAS can also be requested by MBHC,
		 * so use ref count to handle micbias pullup
		 * and enable requests
		 */
		wcd9335_micbias_control(comp, micb_num, MICB_ENABLE, true);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* रुको क्रम cnp समय */
		usleep_range(1000, 1100);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd9335_micbias_control(comp, micb_num, MICB_DISABLE, true);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_micbias(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	वापस __wcd9335_codec_enable_micbias(w, event);
पूर्ण

अटल व्योम wcd9335_codec_set_tx_hold(काष्ठा snd_soc_component *comp,
				      u16 amic_reg, bool set)
अणु
	u8 mask = 0x20;
	u8 val;

	अगर (amic_reg == WCD9335_ANA_AMIC1 || amic_reg == WCD9335_ANA_AMIC3 ||
	    amic_reg == WCD9335_ANA_AMIC5)
		mask = 0x40;

	val = set ? mask : 0x00;

	चयन (amic_reg) अणु
	हाल WCD9335_ANA_AMIC1:
	हाल WCD9335_ANA_AMIC2:
		snd_soc_component_update_bits(comp, WCD9335_ANA_AMIC2, mask,
						val);
		अवरोध;
	हाल WCD9335_ANA_AMIC3:
	हाल WCD9335_ANA_AMIC4:
		snd_soc_component_update_bits(comp, WCD9335_ANA_AMIC4, mask,
						val);
		अवरोध;
	हाल WCD9335_ANA_AMIC5:
	हाल WCD9335_ANA_AMIC6:
		snd_soc_component_update_bits(comp, WCD9335_ANA_AMIC6, mask,
						val);
		अवरोध;
	शेष:
		dev_err(comp->dev, "%s: invalid amic: %d\n",
			__func__, amic_reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_adc(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd9335_codec_set_tx_hold(comp, w->reg, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_find_amic_input(काष्ठा snd_soc_component *comp,
					 पूर्णांक adc_mux_n)
अणु
	पूर्णांक mux_sel, reg, mreg;

	अगर (adc_mux_n < 0 || adc_mux_n > WCD9335_MAX_VALID_ADC_MUX ||
	    adc_mux_n == WCD9335_INVALID_ADC_MUX)
		वापस 0;

	/* Check whether adc mux input is AMIC or DMIC */
	अगर (adc_mux_n < 4) अणु
		reg = WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG1 + 2 * adc_mux_n;
		mreg = WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG0 + 2 * adc_mux_n;
		mux_sel = snd_soc_component_पढ़ो(comp, reg) & 0x3;
	पूर्ण अन्यथा अणु
		reg = WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0 + adc_mux_n - 4;
		mreg = reg;
		mux_sel = snd_soc_component_पढ़ो(comp, reg) >> 6;
	पूर्ण

	अगर (mux_sel != WCD9335_CDC_TX_INP_MUX_SEL_AMIC)
		वापस 0;

	वापस snd_soc_component_पढ़ो(comp, mreg) & 0x07;
पूर्ण

अटल u16 wcd9335_codec_get_amic_pwlvl_reg(काष्ठा snd_soc_component *comp,
					    पूर्णांक amic)
अणु
	u16 pwr_level_reg = 0;

	चयन (amic) अणु
	हाल 1:
	हाल 2:
		pwr_level_reg = WCD9335_ANA_AMIC1;
		अवरोध;

	हाल 3:
	हाल 4:
		pwr_level_reg = WCD9335_ANA_AMIC3;
		अवरोध;

	हाल 5:
	हाल 6:
		pwr_level_reg = WCD9335_ANA_AMIC5;
		अवरोध;
	शेष:
		dev_err(comp->dev, "invalid amic: %d\n", amic);
		अवरोध;
	पूर्ण

	वापस pwr_level_reg;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_dec(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक decimator;
	अक्षर *dec_adc_mux_name = शून्य;
	अक्षर *widget_name = शून्य;
	अक्षर *wname;
	पूर्णांक ret = 0, amic_n;
	u16 tx_vol_ctl_reg, pwr_level_reg = 0, dec_cfg_reg, hpf_gate_reg;
	u16 tx_gain_ctl_reg;
	अक्षर *dec;
	u8 hpf_coff_freq;

	widget_name = kmemdup_nul(w->name, 15, GFP_KERNEL);
	अगर (!widget_name)
		वापस -ENOMEM;

	wname = widget_name;
	dec_adc_mux_name = strsep(&widget_name, " ");
	अगर (!dec_adc_mux_name) अणु
		dev_err(comp->dev, "%s: Invalid decimator = %s\n",
			__func__, w->name);
		ret =  -EINVAL;
		जाओ out;
	पूर्ण
	dec_adc_mux_name = widget_name;

	dec = strpbrk(dec_adc_mux_name, "012345678");
	अगर (!dec) अणु
		dev_err(comp->dev, "%s: decimator index not found\n",
			__func__);
		ret =  -EINVAL;
		जाओ out;
	पूर्ण

	ret = kstrtouपूर्णांक(dec, 10, &decimator);
	अगर (ret < 0) अणु
		dev_err(comp->dev, "%s: Invalid decimator = %s\n",
			__func__, wname);
		ret =  -EINVAL;
		जाओ out;
	पूर्ण

	tx_vol_ctl_reg = WCD9335_CDC_TX0_TX_PATH_CTL + 16 * decimator;
	hpf_gate_reg = WCD9335_CDC_TX0_TX_PATH_SEC2 + 16 * decimator;
	dec_cfg_reg = WCD9335_CDC_TX0_TX_PATH_CFG0 + 16 * decimator;
	tx_gain_ctl_reg = WCD9335_CDC_TX0_TX_VOL_CTL + 16 * decimator;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		amic_n = wcd9335_codec_find_amic_input(comp, decimator);
		अगर (amic_n)
			pwr_level_reg = wcd9335_codec_get_amic_pwlvl_reg(comp,
								       amic_n);

		अगर (pwr_level_reg) अणु
			चयन ((snd_soc_component_पढ़ो(comp, pwr_level_reg) &
					      WCD9335_AMIC_PWR_LVL_MASK) >>
					      WCD9335_AMIC_PWR_LVL_SHIFT) अणु
			हाल WCD9335_AMIC_PWR_LEVEL_LP:
				snd_soc_component_update_bits(comp, dec_cfg_reg,
						    WCD9335_DEC_PWR_LVL_MASK,
						    WCD9335_DEC_PWR_LVL_LP);
				अवरोध;

			हाल WCD9335_AMIC_PWR_LEVEL_HP:
				snd_soc_component_update_bits(comp, dec_cfg_reg,
						    WCD9335_DEC_PWR_LVL_MASK,
						    WCD9335_DEC_PWR_LVL_HP);
				अवरोध;
			हाल WCD9335_AMIC_PWR_LEVEL_DEFAULT:
			शेष:
				snd_soc_component_update_bits(comp, dec_cfg_reg,
						    WCD9335_DEC_PWR_LVL_MASK,
						    WCD9335_DEC_PWR_LVL_DF);
				अवरोध;
			पूर्ण
		पूर्ण
		hpf_coff_freq = (snd_soc_component_पढ़ो(comp, dec_cfg_reg) &
				   TX_HPF_CUT_OFF_FREQ_MASK) >> 5;

		अगर (hpf_coff_freq != CF_MIN_3DB_150HZ)
			snd_soc_component_update_bits(comp, dec_cfg_reg,
					    TX_HPF_CUT_OFF_FREQ_MASK,
					    CF_MIN_3DB_150HZ << 5);
		/* Enable TX PGA Mute */
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg,
						0x10, 0x10);
		/* Enable APC */
		snd_soc_component_update_bits(comp, dec_cfg_reg, 0x08, 0x08);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(comp, hpf_gate_reg, 0x01, 0x00);

		अगर (decimator == 0) अणु
			snd_soc_component_ग_लिखो(comp,
					WCD9335_MBHC_ZDET_RAMP_CTL, 0x83);
			snd_soc_component_ग_लिखो(comp,
					WCD9335_MBHC_ZDET_RAMP_CTL, 0xA3);
			snd_soc_component_ग_लिखो(comp,
					WCD9335_MBHC_ZDET_RAMP_CTL, 0x83);
			snd_soc_component_ग_लिखो(comp,
					WCD9335_MBHC_ZDET_RAMP_CTL, 0x03);
		पूर्ण

		snd_soc_component_update_bits(comp, hpf_gate_reg,
						0x01, 0x01);
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg,
						0x10, 0x00);
		snd_soc_component_ग_लिखो(comp, tx_gain_ctl_reg,
			      snd_soc_component_पढ़ो(comp, tx_gain_ctl_reg));
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		hpf_coff_freq = (snd_soc_component_पढ़ो(comp, dec_cfg_reg) &
				   TX_HPF_CUT_OFF_FREQ_MASK) >> 5;
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg, 0x10, 0x10);
		snd_soc_component_update_bits(comp, dec_cfg_reg, 0x08, 0x00);
		अगर (hpf_coff_freq != CF_MIN_3DB_150HZ) अणु
			snd_soc_component_update_bits(comp, dec_cfg_reg,
						      TX_HPF_CUT_OFF_FREQ_MASK,
						      hpf_coff_freq << 5);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg, 0x10, 0x00);
		अवरोध;
	पूर्ण
out:
	kमुक्त(wname);
	वापस ret;
पूर्ण

अटल u8 wcd9335_get_dmic_clk_val(काष्ठा snd_soc_component *component,
				 u32 mclk_rate, u32 dmic_clk_rate)
अणु
	u32 भाग_factor;
	u8 dmic_ctl_val;

	dev_err(component->dev,
		"%s: mclk_rate = %d, dmic_sample_rate = %d\n",
		__func__, mclk_rate, dmic_clk_rate);

	/* Default value to वापस in हाल of error */
	अगर (mclk_rate == WCD9335_MCLK_CLK_9P6MHZ)
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_2;
	अन्यथा
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_3;

	अगर (dmic_clk_rate == 0) अणु
		dev_err(component->dev,
			"%s: dmic_sample_rate cannot be 0\n",
			__func__);
		जाओ करोne;
	पूर्ण

	भाग_factor = mclk_rate / dmic_clk_rate;
	चयन (भाग_factor) अणु
	हाल 2:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_2;
		अवरोध;
	हाल 3:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_3;
		अवरोध;
	हाल 4:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_4;
		अवरोध;
	हाल 6:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_6;
		अवरोध;
	हाल 8:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_8;
		अवरोध;
	हाल 16:
		dmic_ctl_val = WCD9335_DMIC_CLK_DIV_16;
		अवरोध;
	शेष:
		dev_err(component->dev,
			"%s: Invalid div_factor %u, clk_rate(%u), dmic_rate(%u)\n",
			__func__, भाग_factor, mclk_rate, dmic_clk_rate);
		अवरोध;
	पूर्ण

करोne:
	वापस dmic_ctl_val;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_dmic(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = snd_soc_component_get_drvdata(comp);
	u8  dmic_clk_en = 0x01;
	u16 dmic_clk_reg;
	s32 *dmic_clk_cnt;
	u8 dmic_rate_val, dmic_rate_shअगरt = 1;
	अचिन्हित पूर्णांक dmic;
	पूर्णांक ret;
	अक्षर *wname;

	wname = strpbrk(w->name, "012345");
	अगर (!wname) अणु
		dev_err(comp->dev, "%s: widget not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ret = kstrtouपूर्णांक(wname, 10, &dmic);
	अगर (ret < 0) अणु
		dev_err(comp->dev, "%s: Invalid DMIC line on the codec\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (dmic) अणु
	हाल 0:
	हाल 1:
		dmic_clk_cnt = &(wcd->dmic_0_1_clk_cnt);
		dmic_clk_reg = WCD9335_CPE_SS_DMIC0_CTL;
		अवरोध;
	हाल 2:
	हाल 3:
		dmic_clk_cnt = &(wcd->dmic_2_3_clk_cnt);
		dmic_clk_reg = WCD9335_CPE_SS_DMIC1_CTL;
		अवरोध;
	हाल 4:
	हाल 5:
		dmic_clk_cnt = &(wcd->dmic_4_5_clk_cnt);
		dmic_clk_reg = WCD9335_CPE_SS_DMIC2_CTL;
		अवरोध;
	शेष:
		dev_err(comp->dev, "%s: Invalid DMIC Selection\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dmic_rate_val =
			wcd9335_get_dmic_clk_val(comp,
					wcd->mclk_rate,
					wcd->dmic_sample_rate);

		(*dmic_clk_cnt)++;
		अगर (*dmic_clk_cnt == 1) अणु
			snd_soc_component_update_bits(comp, dmic_clk_reg,
				0x07 << dmic_rate_shअगरt,
				dmic_rate_val << dmic_rate_shअगरt);
			snd_soc_component_update_bits(comp, dmic_clk_reg,
					dmic_clk_en, dmic_clk_en);
		पूर्ण

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		dmic_rate_val =
			wcd9335_get_dmic_clk_val(comp,
					wcd->mclk_rate,
					wcd->mad_dmic_sample_rate);
		(*dmic_clk_cnt)--;
		अगर (*dmic_clk_cnt  == 0) अणु
			snd_soc_component_update_bits(comp, dmic_clk_reg,
					dmic_clk_en, 0);
			snd_soc_component_update_bits(comp, dmic_clk_reg,
				0x07 << dmic_rate_shअगरt,
				dmic_rate_val << dmic_rate_shअगरt);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcd9335_codec_enable_पूर्णांक_port(काष्ठा wcd_slim_codec_dai_data *dai,
					काष्ठा snd_soc_component *component)
अणु
	पूर्णांक port_num = 0;
	अचिन्हित लघु reg = 0;
	अचिन्हित पूर्णांक val = 0;
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	काष्ठा wcd9335_slim_ch *ch;

	list_क्रम_each_entry(ch, &dai->slim_ch_list, list) अणु
		अगर (ch->port >= WCD9335_RX_START) अणु
			port_num = ch->port - WCD9335_RX_START;
			reg = WCD9335_SLIM_PGD_PORT_INT_EN0 + (port_num / 8);
		पूर्ण अन्यथा अणु
			port_num = ch->port;
			reg = WCD9335_SLIM_PGD_PORT_INT_TX_EN0 + (port_num / 8);
		पूर्ण

		regmap_पढ़ो(wcd->अगर_regmap, reg, &val);
		अगर (!(val & BIT(port_num % 8)))
			regmap_ग_लिखो(wcd->अगर_regmap, reg,
					val | BIT(port_num % 8));
	पूर्ण
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_slim(काष्ठा snd_soc_dapm_widget *w,
				       काष्ठा snd_kcontrol *kc,
				       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = snd_soc_component_get_drvdata(comp);
	काष्ठा wcd_slim_codec_dai_data *dai = &wcd->dai[w->shअगरt];

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		wcd9335_codec_enable_पूर्णांक_port(dai, comp);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		kमुक्त(dai->sconfig.chs);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_mix_path(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	u16 gain_reg;
	पूर्णांक offset_val = 0;
	पूर्णांक val = 0;

	चयन (w->reg) अणु
	हाल WCD9335_CDC_RX0_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX0_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX1_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX1_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX2_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX2_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX3_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX3_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX4_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX4_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX5_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX5_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX6_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX6_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX7_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX7_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WCD9335_CDC_RX8_RX_PATH_MIX_CTL:
		gain_reg = WCD9335_CDC_RX8_RX_VOL_MIX_CTL;
		अवरोध;
	शेष:
		dev_err(comp->dev, "%s: No gain register avail for %s\n",
			__func__, w->name);
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_पढ़ो(comp, gain_reg);
		val += offset_val;
		snd_soc_component_ग_लिखो(comp, gain_reg, val);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 wcd9335_पूर्णांकerp_get_primary_reg(u16 reg, u16 *ind)
अणु
	u16 prim_पूर्णांक_reg = WCD9335_CDC_RX0_RX_PATH_CTL;

	चयन (reg) अणु
	हाल WCD9335_CDC_RX0_RX_PATH_CTL:
	हाल WCD9335_CDC_RX0_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX0_RX_PATH_CTL;
		*ind = 0;
		अवरोध;
	हाल WCD9335_CDC_RX1_RX_PATH_CTL:
	हाल WCD9335_CDC_RX1_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX1_RX_PATH_CTL;
		*ind = 1;
		अवरोध;
	हाल WCD9335_CDC_RX2_RX_PATH_CTL:
	हाल WCD9335_CDC_RX2_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX2_RX_PATH_CTL;
		*ind = 2;
		अवरोध;
	हाल WCD9335_CDC_RX3_RX_PATH_CTL:
	हाल WCD9335_CDC_RX3_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX3_RX_PATH_CTL;
		*ind = 3;
		अवरोध;
	हाल WCD9335_CDC_RX4_RX_PATH_CTL:
	हाल WCD9335_CDC_RX4_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX4_RX_PATH_CTL;
		*ind = 4;
		अवरोध;
	हाल WCD9335_CDC_RX5_RX_PATH_CTL:
	हाल WCD9335_CDC_RX5_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX5_RX_PATH_CTL;
		*ind = 5;
		अवरोध;
	हाल WCD9335_CDC_RX6_RX_PATH_CTL:
	हाल WCD9335_CDC_RX6_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX6_RX_PATH_CTL;
		*ind = 6;
		अवरोध;
	हाल WCD9335_CDC_RX7_RX_PATH_CTL:
	हाल WCD9335_CDC_RX7_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX7_RX_PATH_CTL;
		*ind = 7;
		अवरोध;
	हाल WCD9335_CDC_RX8_RX_PATH_CTL:
	हाल WCD9335_CDC_RX8_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = WCD9335_CDC_RX8_RX_PATH_CTL;
		*ind = 8;
		अवरोध;
	पूर्ण

	वापस prim_पूर्णांक_reg;
पूर्ण

अटल व्योम wcd9335_codec_hd2_control(काष्ठा snd_soc_component *component,
				    u16 prim_पूर्णांक_reg, पूर्णांक event)
अणु
	u16 hd2_scale_reg;
	u16 hd2_enable_reg = 0;

	अगर (prim_पूर्णांक_reg == WCD9335_CDC_RX1_RX_PATH_CTL) अणु
		hd2_scale_reg = WCD9335_CDC_RX1_RX_PATH_SEC3;
		hd2_enable_reg = WCD9335_CDC_RX1_RX_PATH_CFG0;
	पूर्ण
	अगर (prim_पूर्णांक_reg == WCD9335_CDC_RX2_RX_PATH_CTL) अणु
		hd2_scale_reg = WCD9335_CDC_RX2_RX_PATH_SEC3;
		hd2_enable_reg = WCD9335_CDC_RX2_RX_PATH_CFG0;
	पूर्ण

	अगर (hd2_enable_reg && SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P2500);
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_2);
		snd_soc_component_update_bits(component, hd2_enable_reg,
				WCD9335_CDC_RX_PATH_CFG_HD2_EN_MASK,
				WCD9335_CDC_RX_PATH_CFG_HD2_ENABLE);
	पूर्ण

	अगर (hd2_enable_reg && SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, hd2_enable_reg,
					WCD9335_CDC_RX_PATH_CFG_HD2_EN_MASK,
					WCD9335_CDC_RX_PATH_CFG_HD2_DISABLE);
		snd_soc_component_update_bits(component, hd2_scale_reg,
					WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_MASK,
					WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_1);
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P0000);
	पूर्ण
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_prim_पूर्णांकerpolator(
						काष्ठा snd_soc_component *comp,
						u16 reg, पूर्णांक event)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	u16 ind = 0;
	पूर्णांक prim_पूर्णांक_reg = wcd9335_पूर्णांकerp_get_primary_reg(reg, &ind);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd->prim_पूर्णांक_users[ind]++;
		अगर (wcd->prim_पूर्णांक_users[ind] == 1) अणु
			snd_soc_component_update_bits(comp, prim_पूर्णांक_reg,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_ENABLE);
			wcd9335_codec_hd2_control(comp, prim_पूर्णांक_reg, event);
			snd_soc_component_update_bits(comp, prim_पूर्णांक_reg,
					WCD9335_CDC_RX_CLK_EN_MASK,
					WCD9335_CDC_RX_CLK_ENABLE);
		पूर्ण

		अगर ((reg != prim_पूर्णांक_reg) &&
			((snd_soc_component_पढ़ो(comp, prim_पूर्णांक_reg)) &
			 WCD9335_CDC_RX_PGA_MUTE_EN_MASK))
			snd_soc_component_update_bits(comp, reg,
						WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
						WCD9335_CDC_RX_PGA_MUTE_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd->prim_पूर्णांक_users[ind]--;
		अगर (wcd->prim_पूर्णांक_users[ind] == 0) अणु
			snd_soc_component_update_bits(comp, prim_पूर्णांक_reg,
					WCD9335_CDC_RX_CLK_EN_MASK,
					WCD9335_CDC_RX_CLK_DISABLE);
			snd_soc_component_update_bits(comp, prim_पूर्णांक_reg,
					WCD9335_CDC_RX_RESET_MASK,
					WCD9335_CDC_RX_RESET_ENABLE);
			snd_soc_component_update_bits(comp, prim_पूर्णांक_reg,
					WCD9335_CDC_RX_RESET_MASK,
					WCD9335_CDC_RX_RESET_DISABLE);
			wcd9335_codec_hd2_control(comp, prim_पूर्णांक_reg, event);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_config_compander(काष्ठा snd_soc_component *component,
				    पूर्णांक पूर्णांकerp_n, पूर्णांक event)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक comp;
	u16 comp_ctl0_reg, rx_path_cfg0_reg;

	/* EAR करोes not have compander */
	अगर (!पूर्णांकerp_n)
		वापस 0;

	comp = पूर्णांकerp_n - 1;
	अगर (!wcd->comp_enabled[comp])
		वापस 0;

	comp_ctl0_reg = WCD9335_CDC_COMPANDER1_CTL(comp);
	rx_path_cfg0_reg = WCD9335_CDC_RX1_RX_PATH_CFG(comp);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/* Enable Compander Clock */
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_CLK_EN_MASK,
					WCD9335_CDC_COMPANDER_CLK_ENABLE);
		/* Reset comander */
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_SOFT_RST_MASK,
					WCD9335_CDC_COMPANDER_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
				WCD9335_CDC_COMPANDER_SOFT_RST_MASK,
				WCD9335_CDC_COMPANDER_SOFT_RST_DISABLE);
		/* Enables DRE in this path */
		snd_soc_component_update_bits(component, rx_path_cfg0_reg,
					WCD9335_CDC_RX_PATH_CFG_CMP_EN_MASK,
					WCD9335_CDC_RX_PATH_CFG_CMP_ENABLE);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_HALT_MASK,
					WCD9335_CDC_COMPANDER_HALT);
		snd_soc_component_update_bits(component, rx_path_cfg0_reg,
					WCD9335_CDC_RX_PATH_CFG_CMP_EN_MASK,
					WCD9335_CDC_RX_PATH_CFG_CMP_DISABLE);

		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_SOFT_RST_MASK,
					WCD9335_CDC_COMPANDER_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
				WCD9335_CDC_COMPANDER_SOFT_RST_MASK,
				WCD9335_CDC_COMPANDER_SOFT_RST_DISABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_CLK_EN_MASK,
					WCD9335_CDC_COMPANDER_CLK_DISABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					WCD9335_CDC_COMPANDER_HALT_MASK,
					WCD9335_CDC_COMPANDER_NOHALT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_पूर्णांकerpolator(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	u16 gain_reg;
	u16 reg;
	पूर्णांक val;
	पूर्णांक offset_val = 0;

	अगर (!(म_भेद(w->name, "RX INT0 INTERP"))) अणु
		reg = WCD9335_CDC_RX0_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX0_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT1 INTERP"))) अणु
		reg = WCD9335_CDC_RX1_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX1_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT2 INTERP"))) अणु
		reg = WCD9335_CDC_RX2_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX2_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT3 INTERP"))) अणु
		reg = WCD9335_CDC_RX3_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX3_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT4 INTERP"))) अणु
		reg = WCD9335_CDC_RX4_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX4_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT5 INTERP"))) अणु
		reg = WCD9335_CDC_RX5_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX5_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT6 INTERP"))) अणु
		reg = WCD9335_CDC_RX6_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX6_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT7 INTERP"))) अणु
		reg = WCD9335_CDC_RX7_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX7_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (!(म_भेद(w->name, "RX INT8 INTERP"))) अणु
		reg = WCD9335_CDC_RX8_RX_PATH_CTL;
		gain_reg = WCD9335_CDC_RX8_RX_VOL_CTL;
	पूर्ण अन्यथा अणु
		dev_err(comp->dev, "%s: Interpolator reg not found\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Reset अगर needed */
		wcd9335_codec_enable_prim_पूर्णांकerpolator(comp, reg, event);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		wcd9335_config_compander(comp, w->shअगरt, event);
		val = snd_soc_component_पढ़ो(comp, gain_reg);
		val += offset_val;
		snd_soc_component_ग_लिखो(comp, gain_reg, val);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd9335_config_compander(comp, w->shअगरt, event);
		wcd9335_codec_enable_prim_पूर्णांकerpolator(comp, reg, event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcd9335_codec_hph_mode_gain_opt(काष्ठा snd_soc_component *component,
					    u8 gain)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	u8 hph_l_en, hph_r_en;
	u8 l_val, r_val;
	u8 hph_pa_status;
	bool is_hphl_pa, is_hphr_pa;

	hph_pa_status = snd_soc_component_पढ़ो(component, WCD9335_ANA_HPH);
	is_hphl_pa = hph_pa_status >> 7;
	is_hphr_pa = (hph_pa_status & 0x40) >> 6;

	hph_l_en = snd_soc_component_पढ़ो(component, WCD9335_HPH_L_EN);
	hph_r_en = snd_soc_component_पढ़ो(component, WCD9335_HPH_R_EN);

	l_val = (hph_l_en & 0xC0) | 0x20 | gain;
	r_val = (hph_r_en & 0xC0) | 0x20 | gain;

	/*
	 * Set HPH_L & HPH_R gain source selection to REGISTER
	 * क्रम better click and pop only अगर corresponding PAs are
	 * not enabled. Also cache the values of the HPHL/R
	 * PA gains to be applied after PAs are enabled
	 */
	अगर ((l_val != hph_l_en) && !is_hphl_pa) अणु
		snd_soc_component_ग_लिखो(component, WCD9335_HPH_L_EN, l_val);
		wcd->hph_l_gain = hph_l_en & 0x1F;
	पूर्ण

	अगर ((r_val != hph_r_en) && !is_hphr_pa) अणु
		snd_soc_component_ग_लिखो(component, WCD9335_HPH_R_EN, r_val);
		wcd->hph_r_gain = hph_r_en & 0x1F;
	पूर्ण
पूर्ण

अटल व्योम wcd9335_codec_hph_lohअगरi_config(काष्ठा snd_soc_component *comp,
					  पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(comp, WCD9335_RX_BIAS_HPH_PA,
					WCD9335_RX_BIAS_HPH_PA_AMP_5_UA_MASK,
					0x06);
		snd_soc_component_update_bits(comp,
					WCD9335_RX_BIAS_HPH_RDACBUFF_CNP2,
					0xF0, 0x40);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_1000);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL1,
				WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
				0x0C);
		wcd9335_codec_hph_mode_gain_opt(comp, 0x11);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_500);
		snd_soc_component_ग_लिखो(comp, WCD9335_RX_BIAS_HPH_RDACBUFF_CNP2,
					0x8A);
		snd_soc_component_update_bits(comp, WCD9335_RX_BIAS_HPH_PA,
					WCD9335_RX_BIAS_HPH_PA_AMP_5_UA_MASK,
					0x0A);
	पूर्ण
पूर्ण

अटल व्योम wcd9335_codec_hph_lp_config(काष्ठा snd_soc_component *comp,
				      पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL1,
				WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
				0x0C);
		wcd9335_codec_hph_mode_gain_opt(comp, 0x10);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_1000);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENH_MASK,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_RDAC_LDO_CTL,
				WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_MASK,
				WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_V_N1P60);
		snd_soc_component_update_bits(comp, WCD9335_HPH_RDAC_LDO_CTL,
				WCD9335_HPH_RDAC_1P65_LD_OUTCTL_MASK,
				WCD9335_HPH_RDAC_1P65_LD_OUTCTL_V_N1P60);
		snd_soc_component_update_bits(comp,
				WCD9335_RX_BIAS_HPH_RDAC_LDO, 0x0F, 0x01);
		snd_soc_component_update_bits(comp,
				WCD9335_RX_BIAS_HPH_RDAC_LDO, 0xF0, 0x10);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_ग_लिखो(comp, WCD9335_RX_BIAS_HPH_RDAC_LDO,
					0x88);
		snd_soc_component_ग_लिखो(comp, WCD9335_HPH_RDAC_LDO_CTL,
					0x33);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENH_MASK,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_500);
		snd_soc_component_update_bits(comp, WCD9335_HPH_R_EN,
				WCD9335_HPH_CONST_SEL_L_MASK,
				WCD9335_HPH_CONST_SEL_L_HQ_PATH);
		snd_soc_component_update_bits(comp, WCD9335_HPH_L_EN,
				WCD9335_HPH_CONST_SEL_L_MASK,
				WCD9335_HPH_CONST_SEL_L_HQ_PATH);
	पूर्ण
पूर्ण

अटल व्योम wcd9335_codec_hph_hअगरi_config(काष्ठा snd_soc_component *comp,
					पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_1000);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL1,
				WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
				0x0C);
		wcd9335_codec_hph_mode_gain_opt(comp, 0x11);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_500);
	पूर्ण
पूर्ण

अटल व्योम wcd9335_codec_hph_mode_config(काष्ठा snd_soc_component *component,
					  पूर्णांक event, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल CLS_H_LP:
		wcd9335_codec_hph_lp_config(component, event);
		अवरोध;
	हाल CLS_H_LOHIFI:
		wcd9335_codec_hph_lohअगरi_config(component, event);
		अवरोध;
	हाल CLS_H_HIFI:
		wcd9335_codec_hph_hअगरi_config(component, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wcd9335_codec_hphl_dac_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kc,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;
	u8 dem_inp;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Read DEM INP Select */
		dem_inp = snd_soc_component_पढ़ो(comp,
				WCD9335_CDC_RX1_RX_PATH_SEC0) & 0x03;
		अगर (((hph_mode == CLS_H_HIFI) || (hph_mode == CLS_H_LOHIFI) ||
				(hph_mode == CLS_H_LP)) && (dem_inp != 0x01)) अणु
			dev_err(comp->dev, "Incorrect DEM Input\n");
			वापस -EINVAL;
		पूर्ण
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_HPHL,
					((hph_mode == CLS_H_LOHIFI) ?
					 CLS_H_HIFI : hph_mode));

		wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(1000, 1100);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 1000us required as per HW requirement */
		usleep_range(1000, 1100);

		अगर (!(wcd_clsh_ctrl_get_state(wcd->clsh_ctrl) &
				WCD_CLSH_STATE_HPHR))
			wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
				WCD_CLSH_STATE_HPHL,
				((hph_mode == CLS_H_LOHIFI) ?
				 CLS_H_HIFI : hph_mode));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_lineout_dac_event(काष्ठा snd_soc_dapm_widget *w,
					   काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_LO, CLS_AB);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
					WCD_CLSH_STATE_LO, CLS_AB);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_ear_dac_event(काष्ठा snd_soc_dapm_widget *w,
				       काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_EAR, CLS_H_NORMAL);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
					WCD_CLSH_STATE_EAR, CLS_H_NORMAL);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcd9335_codec_hph_post_pa_config(काष्ठा wcd9335_codec *wcd,
					     पूर्णांक mode, पूर्णांक event)
अणु
	u8 scale_val = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		चयन (mode) अणु
		हाल CLS_H_HIFI:
			scale_val = 0x3;
			अवरोध;
		हाल CLS_H_LOHIFI:
			scale_val = 0x1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		scale_val = 0x6;
		अवरोध;
	पूर्ण

	अगर (scale_val)
		snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_PA_CTL1,
					WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
					scale_val << 1);
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		अगर (wcd->comp_enabled[COMPANDER_1] ||
		    wcd->comp_enabled[COMPANDER_2]) अणु
			/* GAIN Source Selection */
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_L_EN,
					WCD9335_HPH_GAIN_SRC_SEL_MASK,
					WCD9335_HPH_GAIN_SRC_SEL_COMPANDER);
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_R_EN,
					WCD9335_HPH_GAIN_SRC_SEL_MASK,
					WCD9335_HPH_GAIN_SRC_SEL_COMPANDER);
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_AUTO_CHOP,
					WCD9335_HPH_AUTO_CHOP_MASK,
					WCD9335_HPH_AUTO_CHOP_FORCE_ENABLE);
		पूर्ण
		snd_soc_component_update_bits(wcd->component,
						WCD9335_HPH_L_EN,
						WCD9335_HPH_PA_GAIN_MASK,
						wcd->hph_l_gain);
		snd_soc_component_update_bits(wcd->component,
						WCD9335_HPH_R_EN,
						WCD9335_HPH_PA_GAIN_MASK,
						wcd->hph_r_gain);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event))
		snd_soc_component_update_bits(wcd->component,
				WCD9335_HPH_AUTO_CHOP,
				WCD9335_HPH_AUTO_CHOP_MASK,
				WCD9335_HPH_AUTO_CHOP_ENABLE_BY_CMPDR_GAIN);
पूर्ण

अटल पूर्णांक wcd9335_codec_hphr_dac_event(काष्ठा snd_soc_dapm_widget *w,
				      काष्ठा snd_kcontrol *kc,
				      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;
	u8 dem_inp;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:

		/* Read DEM INP Select */
		dem_inp = snd_soc_component_पढ़ो(comp,
				WCD9335_CDC_RX2_RX_PATH_SEC0) &
				WCD9335_CDC_RX_PATH_DEM_INP_SEL_MASK;
		अगर (((hph_mode == CLS_H_HIFI) || (hph_mode == CLS_H_LOHIFI) ||
		     (hph_mode == CLS_H_LP)) && (dem_inp != 0x01)) अणु
			dev_err(comp->dev, "DEM Input not set correctly, hph_mode: %d\n",
				hph_mode);
			वापस -EINVAL;
		पूर्ण

		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl,
			     WCD_CLSH_EVENT_PRE_DAC,
			     WCD_CLSH_STATE_HPHR,
			     ((hph_mode == CLS_H_LOHIFI) ?
			       CLS_H_HIFI : hph_mode));

		wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 1000us required as per HW requirement */
		usleep_range(1000, 1100);

		अगर (!(wcd_clsh_ctrl_get_state(wcd->clsh_ctrl) &
					WCD_CLSH_STATE_HPHL))
			wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
			     WCD_CLSH_STATE_HPHR, ((hph_mode == CLS_H_LOHIFI) ?
						CLS_H_HIFI : hph_mode));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_hphl_pa(काष्ठा snd_soc_dapm_widget *w,
				      काष्ठा snd_kcontrol *kc,
				      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * 7ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(7000, 7100);

		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX1_RX_PATH_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		/* Remove mix path mute अगर it is enabled */
		अगर ((snd_soc_component_पढ़ो(comp,
					WCD9335_CDC_RX1_RX_PATH_MIX_CTL)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,
					    WCD9335_CDC_RX1_RX_PATH_MIX_CTL,
					    WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					    WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 5ms sleep is required after PA is disabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_lineout_pa(काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा snd_kcontrol *kc,
					 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक vol_reg = 0, mix_vol_reg = 0;

	अगर (w->reg == WCD9335_ANA_LO_1_2) अणु
		अगर (w->shअगरt == 7) अणु
			vol_reg = WCD9335_CDC_RX3_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX3_RX_PATH_MIX_CTL;
		पूर्ण अन्यथा अगर (w->shअगरt == 6) अणु
			vol_reg = WCD9335_CDC_RX4_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX4_RX_PATH_MIX_CTL;
		पूर्ण
	पूर्ण अन्यथा अगर (w->reg == WCD9335_ANA_LO_3_4) अणु
		अगर (w->shअगरt == 7) अणु
			vol_reg = WCD9335_CDC_RX5_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX5_RX_PATH_MIX_CTL;
		पूर्ण अन्यथा अगर (w->shअगरt == 6) अणु
			vol_reg = WCD9335_CDC_RX6_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX6_RX_PATH_MIX_CTL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(comp->dev, "Error enabling lineout PA\n");
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* 5ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		snd_soc_component_update_bits(comp, vol_reg,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		/* Remove mix path mute अगर it is enabled */
		अगर ((snd_soc_component_पढ़ो(comp, mix_vol_reg)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,  mix_vol_reg,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 5ms sleep is required after PA is disabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcd9335_codec_init_flyback(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_update_bits(component, WCD9335_HPH_L_EN,
					WCD9335_HPH_CONST_SEL_L_MASK,
					WCD9335_HPH_CONST_SEL_L_BYPASS);
	snd_soc_component_update_bits(component, WCD9335_HPH_R_EN,
					WCD9335_HPH_CONST_SEL_L_MASK,
					WCD9335_HPH_CONST_SEL_L_BYPASS);
	snd_soc_component_update_bits(component, WCD9335_RX_BIAS_FLYB_BUFF,
					WCD9335_RX_BIAS_FLYB_VPOS_5_UA_MASK,
					WCD9335_RX_BIAS_FLYB_I_0P0_UA);
	snd_soc_component_update_bits(component, WCD9335_RX_BIAS_FLYB_BUFF,
					WCD9335_RX_BIAS_FLYB_VNEG_5_UA_MASK,
					WCD9335_RX_BIAS_FLYB_I_0P0_UA);
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_rx_bias(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd->rx_bias_count++;
		अगर (wcd->rx_bias_count == 1) अणु
			wcd9335_codec_init_flyback(comp);
			snd_soc_component_update_bits(comp,
						WCD9335_ANA_RX_SUPPLIES,
						WCD9335_ANA_RX_BIAS_ENABLE_MASK,
						WCD9335_ANA_RX_BIAS_ENABLE);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd->rx_bias_count--;
		अगर (!wcd->rx_bias_count)
			snd_soc_component_update_bits(comp,
					WCD9335_ANA_RX_SUPPLIES,
					WCD9335_ANA_RX_BIAS_ENABLE_MASK,
					WCD9335_ANA_RX_BIAS_DISABLE);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_hphr_pa(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * 7ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(7000, 7100);
		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX2_RX_PATH_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);
		/* Remove mix path mute अगर it is enabled */
		अगर ((snd_soc_component_पढ़ो(comp,
					WCD9335_CDC_RX2_RX_PATH_MIX_CTL)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX2_RX_PATH_MIX_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 5ms sleep is required after PA is disabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_ear_pa(काष्ठा snd_soc_dapm_widget *w,
				       काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* 5ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX0_RX_PATH_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);
		/* Remove mix path mute अगर it is enabled */
		अगर ((snd_soc_component_पढ़ो(comp,
					WCD9335_CDC_RX0_RX_PATH_MIX_CTL)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX0_RX_PATH_MIX_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 5ms sleep is required after PA is disabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t wcd9335_slimbus_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wcd9335_codec *wcd = data;
	अचिन्हित दीर्घ status = 0;
	पूर्णांक i, j, port_id;
	अचिन्हित पूर्णांक val, पूर्णांक_val = 0;
	irqवापस_t ret = IRQ_NONE;
	bool tx;
	अचिन्हित लघु reg = 0;

	क्रम (i = WCD9335_SLIM_PGD_PORT_INT_STATUS_RX_0, j = 0;
	     i <= WCD9335_SLIM_PGD_PORT_INT_STATUS_TX_1; i++, j++) अणु
		regmap_पढ़ो(wcd->अगर_regmap, i, &val);
		status |= ((u32)val << (8 * j));
	पूर्ण

	क्रम_each_set_bit(j, &status, 32) अणु
		tx = (j >= 16);
		port_id = (tx ? j - 16 : j);
		regmap_पढ़ो(wcd->अगर_regmap,
				WCD9335_SLIM_PGD_PORT_INT_RX_SOURCE0 + j, &val);
		अगर (val) अणु
			अगर (!tx)
				reg = WCD9335_SLIM_PGD_PORT_INT_EN0 +
					(port_id / 8);
			अन्यथा
				reg = WCD9335_SLIM_PGD_PORT_INT_TX_EN0 +
					(port_id / 8);
			regmap_पढ़ो(
				wcd->अगर_regmap, reg, &पूर्णांक_val);
			/*
			 * Ignore पूर्णांकerrupts क्रम ports क्रम which the
			 * पूर्णांकerrupts are not specअगरically enabled.
			 */
			अगर (!(पूर्णांक_val & (1 << (port_id % 8))))
				जारी;
		पूर्ण

		अगर (val & WCD9335_SLIM_IRQ_OVERFLOW)
			dev_err_ratelimited(wcd->dev,
			   "%s: overflow error on %s port %d, value %x\n",
			   __func__, (tx ? "TX" : "RX"), port_id, val);

		अगर (val & WCD9335_SLIM_IRQ_UNDERFLOW)
			dev_err_ratelimited(wcd->dev,
			   "%s: underflow error on %s port %d, value %x\n",
			   __func__, (tx ? "TX" : "RX"), port_id, val);

		अगर ((val & WCD9335_SLIM_IRQ_OVERFLOW) ||
			(val & WCD9335_SLIM_IRQ_UNDERFLOW)) अणु
			अगर (!tx)
				reg = WCD9335_SLIM_PGD_PORT_INT_EN0 +
					(port_id / 8);
			अन्यथा
				reg = WCD9335_SLIM_PGD_PORT_INT_TX_EN0 +
					(port_id / 8);
			regmap_पढ़ो(
				wcd->अगर_regmap, reg, &पूर्णांक_val);
			अगर (पूर्णांक_val & (1 << (port_id % 8))) अणु
				पूर्णांक_val = पूर्णांक_val ^ (1 << (port_id % 8));
				regmap_ग_लिखो(wcd->अगर_regmap,
					reg, पूर्णांक_val);
			पूर्ण
		पूर्ण

		regmap_ग_लिखो(wcd->अगर_regmap,
				WCD9335_SLIM_PGD_PORT_INT_CLR_RX_0 + (j / 8),
				BIT(j % 8));
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा wcd9335_irq wcd9335_irqs[] = अणु
	अणु
		.irq = WCD9335_IRQ_SLIMBUS,
		.handler = wcd9335_slimbus_irq,
		.name = "SLIM Slave",
	पूर्ण,
पूर्ण;

अटल पूर्णांक wcd9335_setup_irqs(काष्ठा wcd9335_codec *wcd)
अणु
	पूर्णांक irq, ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(wcd9335_irqs); i++) अणु
		irq = regmap_irq_get_virq(wcd->irq_data, wcd9335_irqs[i].irq);
		अगर (irq < 0) अणु
			dev_err(wcd->dev, "Failed to get %s\n",
					wcd9335_irqs[i].name);
			वापस irq;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(wcd->dev, irq, शून्य,
						wcd9335_irqs[i].handler,
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						wcd9335_irqs[i].name, wcd);
		अगर (ret) अणु
			dev_err(wcd->dev, "Failed to request %s\n",
					wcd9335_irqs[i].name);
			वापस ret;
		पूर्ण
	पूर्ण

	/* enable पूर्णांकerrupts on all slave ports */
	क्रम (i = 0; i < WCD9335_SLIM_NUM_PORT_REG; i++)
		regmap_ग_लिखो(wcd->अगर_regmap, WCD9335_SLIM_PGD_PORT_INT_EN0 + i,
			     0xFF);

	वापस ret;
पूर्ण

अटल व्योम wcd9335_cdc_siकरो_ccl_enable(काष्ठा wcd9335_codec *wcd,
					bool ccl_flag)
अणु
	काष्ठा snd_soc_component *comp = wcd->component;

	अगर (ccl_flag) अणु
		अगर (++wcd->siकरो_ccl_cnt == 1)
			snd_soc_component_ग_लिखो(comp, WCD9335_SIDO_SIDO_CCL_10,
					WCD9335_SIDO_SIDO_CCL_DEF_VALUE);
	पूर्ण अन्यथा अणु
		अगर (wcd->siकरो_ccl_cnt == 0) अणु
			dev_err(wcd->dev, "sido_ccl already disabled\n");
			वापस;
		पूर्ण
		अगर (--wcd->siकरो_ccl_cnt == 0)
			snd_soc_component_ग_लिखो(comp, WCD9335_SIDO_SIDO_CCL_10,
				WCD9335_SIDO_SIDO_CCL_10_ICHARG_PWR_SEL_C320FF);
	पूर्ण
पूर्ण

अटल पूर्णांक wcd9335_enable_master_bias(काष्ठा wcd9335_codec *wcd)
अणु
	wcd->master_bias_users++;
	अगर (wcd->master_bias_users == 1) अणु
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_EN_MASK,
					WCD9335_ANA_BIAS_ENABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_PRECHRG_EN_MASK,
					WCD9335_ANA_BIAS_PRECHRG_ENABLE);
		/*
		 * 1ms delay is required after pre-अक्षरge is enabled
		 * as per HW requirement
		 */
		usleep_range(1000, 1100);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_PRECHRG_EN_MASK,
					WCD9335_ANA_BIAS_PRECHRG_DISABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_enable_mclk(काष्ठा wcd9335_codec *wcd)
अणु
	/* Enable mclk requires master bias to be enabled first */
	अगर (wcd->master_bias_users <= 0)
		वापस -EINVAL;

	अगर (((wcd->clk_mclk_users == 0) && (wcd->clk_type == WCD_CLK_MCLK)) ||
	    ((wcd->clk_mclk_users > 0) && (wcd->clk_type != WCD_CLK_MCLK))) अणु
		dev_err(wcd->dev, "Error enabling MCLK, clk_type: %d\n",
			wcd->clk_type);
		वापस -EINVAL;
	पूर्ण

	अगर (++wcd->clk_mclk_users == 1) अणु
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK,
					WCD9335_ANA_CLK_EXT_CLKBUF_ENABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_SRC_MASK,
					WCD9335_ANA_CLK_MCLK_SRC_EXTERNAL);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_EN_MASK,
					WCD9335_ANA_CLK_MCLK_ENABLE);
		regmap_update_bits(wcd->regmap,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_CONTROL,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_EN_MASK,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_ENABLE);
		regmap_update_bits(wcd->regmap,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_CONTROL,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_EN_MASK,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_ENABLE);
		/*
		 * 10us sleep is required after घड़ी is enabled
		 * as per HW requirement
		 */
		usleep_range(10, 15);
	पूर्ण

	wcd->clk_type = WCD_CLK_MCLK;

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_disable_mclk(काष्ठा wcd9335_codec *wcd)
अणु
	अगर (wcd->clk_mclk_users <= 0)
		वापस -EINVAL;

	अगर (--wcd->clk_mclk_users == 0) अणु
		अगर (wcd->clk_rco_users > 0) अणु
			/* MCLK to RCO चयन */
			regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_SRC_MASK,
					WCD9335_ANA_CLK_MCLK_SRC_RCO);
			wcd->clk_type = WCD_CLK_RCO;
		पूर्ण अन्यथा अणु
			regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_EN_MASK,
					WCD9335_ANA_CLK_MCLK_DISABLE);
			wcd->clk_type = WCD_CLK_OFF;
		पूर्ण

		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK,
					WCD9335_ANA_CLK_EXT_CLKBUF_DISABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_disable_master_bias(काष्ठा wcd9335_codec *wcd)
अणु
	अगर (wcd->master_bias_users <= 0)
		वापस -EINVAL;

	wcd->master_bias_users--;
	अगर (wcd->master_bias_users == 0) अणु
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_EN_MASK,
				WCD9335_ANA_BIAS_DISABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_cdc_req_mclk_enable(काष्ठा wcd9335_codec *wcd,
				     bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		wcd9335_cdc_siकरो_ccl_enable(wcd, true);
		ret = clk_prepare_enable(wcd->mclk);
		अगर (ret) अणु
			dev_err(wcd->dev, "%s: ext clk enable failed\n",
				__func__);
			जाओ err;
		पूर्ण
		/* get BG */
		wcd9335_enable_master_bias(wcd);
		/* get MCLK */
		wcd9335_enable_mclk(wcd);

	पूर्ण अन्यथा अणु
		/* put MCLK */
		wcd9335_disable_mclk(wcd);
		/* put BG */
		wcd9335_disable_master_bias(wcd);
		clk_disable_unprepare(wcd->mclk);
		wcd9335_cdc_siकरो_ccl_enable(wcd, false);
	पूर्ण
err:
	वापस ret;
पूर्ण

अटल व्योम wcd9335_codec_apply_siकरो_voltage(काष्ठा wcd9335_codec *wcd,
					     क्रमागत wcd9335_siकरो_voltage req_mv)
अणु
	काष्ठा snd_soc_component *comp = wcd->component;
	पूर्णांक vout_d_val;

	अगर (req_mv == wcd->siकरो_voltage)
		वापस;

	/* compute the vout_d step value */
	vout_d_val = WCD9335_CALCULATE_VOUT_D(req_mv) &
			WCD9335_ANA_BUCK_VOUT_MASK;
	snd_soc_component_ग_लिखो(comp, WCD9335_ANA_BUCK_VOUT_D, vout_d_val);
	snd_soc_component_update_bits(comp, WCD9335_ANA_BUCK_CTL,
				WCD9335_ANA_BUCK_CTL_RAMP_START_MASK,
				WCD9335_ANA_BUCK_CTL_RAMP_START_ENABLE);

	/* 1 msec sleep required after SIDO Vout_D voltage change */
	usleep_range(1000, 1100);
	wcd->siकरो_voltage = req_mv;
	snd_soc_component_update_bits(comp, WCD9335_ANA_BUCK_CTL,
				WCD9335_ANA_BUCK_CTL_RAMP_START_MASK,
				WCD9335_ANA_BUCK_CTL_RAMP_START_DISABLE);
पूर्ण

अटल पूर्णांक wcd9335_codec_update_siकरो_voltage(काष्ठा wcd9335_codec *wcd,
					     क्रमागत wcd9335_siकरो_voltage req_mv)
अणु
	पूर्णांक ret = 0;

	/* enable mclk beक्रमe setting SIDO voltage */
	ret = wcd9335_cdc_req_mclk_enable(wcd, true);
	अगर (ret) अणु
		dev_err(wcd->dev, "Ext clk enable failed\n");
		जाओ err;
	पूर्ण

	wcd9335_codec_apply_siकरो_voltage(wcd, req_mv);
	wcd9335_cdc_req_mclk_enable(wcd, false);

err:
	वापस ret;
पूर्ण

अटल पूर्णांक _wcd9335_codec_enable_mclk(काष्ठा snd_soc_component *component,
				      पूर्णांक enable)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = wcd9335_cdc_req_mclk_enable(wcd, true);
		अगर (ret)
			वापस ret;

		wcd9335_codec_apply_siकरो_voltage(wcd,
				SIDO_VOLTAGE_NOMINAL_MV);
	पूर्ण अन्यथा अणु
		wcd9335_codec_update_siकरो_voltage(wcd,
					wcd->siकरो_voltage);
		wcd9335_cdc_req_mclk_enable(wcd, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_codec_enable_mclk(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस _wcd9335_codec_enable_mclk(comp, true);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस _wcd9335_codec_enable_mclk(comp, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wcd9335_dapm_widमाला_लो[] = अणु
	/* TODO SPK1 & SPK2 OUT*/
	SND_SOC_DAPM_OUTPUT("EAR"),
	SND_SOC_DAPM_OUTPUT("HPHL"),
	SND_SOC_DAPM_OUTPUT("HPHR"),
	SND_SOC_DAPM_OUTPUT("LINEOUT1"),
	SND_SOC_DAPM_OUTPUT("LINEOUT2"),
	SND_SOC_DAPM_OUTPUT("LINEOUT3"),
	SND_SOC_DAPM_OUTPUT("LINEOUT4"),
	SND_SOC_DAPM_AIF_IN_E("AIF1 PB", "AIF1 Playback", 0, SND_SOC_NOPM,
				AIF1_PB, 0, wcd9335_codec_enable_slim,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF2 PB", "AIF2 Playback", 0, SND_SOC_NOPM,
				AIF2_PB, 0, wcd9335_codec_enable_slim,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF3 PB", "AIF3 Playback", 0, SND_SOC_NOPM,
				AIF3_PB, 0, wcd9335_codec_enable_slim,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF4 PB", "AIF4 Playback", 0, SND_SOC_NOPM,
				AIF4_PB, 0, wcd9335_codec_enable_slim,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("SLIM RX0 MUX", SND_SOC_NOPM, WCD9335_RX0, 0,
				&slim_rx_mux[WCD9335_RX0]),
	SND_SOC_DAPM_MUX("SLIM RX1 MUX", SND_SOC_NOPM, WCD9335_RX1, 0,
				&slim_rx_mux[WCD9335_RX1]),
	SND_SOC_DAPM_MUX("SLIM RX2 MUX", SND_SOC_NOPM, WCD9335_RX2, 0,
				&slim_rx_mux[WCD9335_RX2]),
	SND_SOC_DAPM_MUX("SLIM RX3 MUX", SND_SOC_NOPM, WCD9335_RX3, 0,
				&slim_rx_mux[WCD9335_RX3]),
	SND_SOC_DAPM_MUX("SLIM RX4 MUX", SND_SOC_NOPM, WCD9335_RX4, 0,
				&slim_rx_mux[WCD9335_RX4]),
	SND_SOC_DAPM_MUX("SLIM RX5 MUX", SND_SOC_NOPM, WCD9335_RX5, 0,
				&slim_rx_mux[WCD9335_RX5]),
	SND_SOC_DAPM_MUX("SLIM RX6 MUX", SND_SOC_NOPM, WCD9335_RX6, 0,
				&slim_rx_mux[WCD9335_RX6]),
	SND_SOC_DAPM_MUX("SLIM RX7 MUX", SND_SOC_NOPM, WCD9335_RX7, 0,
				&slim_rx_mux[WCD9335_RX7]),
	SND_SOC_DAPM_MIXER("SLIM RX0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX7", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX_E("RX INT0_2 MUX", WCD9335_CDC_RX0_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक0_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT1_2 MUX", WCD9335_CDC_RX1_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक1_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT2_2 MUX", WCD9335_CDC_RX2_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक2_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT3_2 MUX", WCD9335_CDC_RX3_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक3_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT4_2 MUX", WCD9335_CDC_RX4_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक4_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT5_2 MUX", WCD9335_CDC_RX5_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक5_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT6_2 MUX", WCD9335_CDC_RX6_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक6_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT7_2 MUX", WCD9335_CDC_RX7_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक7_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("RX INT8_2 MUX", WCD9335_CDC_RX8_RX_PATH_MIX_CTL,
			5, 0, &rx_पूर्णांक8_2_mux, wcd9335_codec_enable_mix_path,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX("RX INT0_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक0_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT0_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक0_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT0_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक0_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT1_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक1_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT1_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक1_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT1_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक1_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT2_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक2_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT2_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक2_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT2_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक2_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT3_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक3_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT3_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक3_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT3_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक3_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT4_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक4_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT4_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक4_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT4_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक4_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT5_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक5_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT5_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक5_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT5_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक5_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT6_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक6_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT6_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक6_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT6_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक6_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT7_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक7_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT7_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक7_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT7_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक7_1_mix_inp2_mux),
	SND_SOC_DAPM_MUX("RX INT8_1 MIX1 INP0", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक8_1_mix_inp0_mux),
	SND_SOC_DAPM_MUX("RX INT8_1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक8_1_mix_inp1_mux),
	SND_SOC_DAPM_MUX("RX INT8_1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक8_1_mix_inp2_mux),

	SND_SOC_DAPM_MIXER("RX INT0_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT0 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT1_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT1 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT5_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT5 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT6_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT6 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT7_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT7 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT8_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT8 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("RX INT0 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT1 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT5 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT6 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT7 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT8 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("RX INT0 DEM MUX", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक0_dem_inp_mux),
	SND_SOC_DAPM_MUX("RX INT1 DEM MUX", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक1_dem_inp_mux),
	SND_SOC_DAPM_MUX("RX INT2 DEM MUX", SND_SOC_NOPM, 0, 0,
		&rx_पूर्णांक2_dem_inp_mux),

	SND_SOC_DAPM_MUX_E("RX INT0 INTERP", SND_SOC_NOPM,
		INTERP_EAR, 0, &rx_पूर्णांक0_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT1 INTERP", SND_SOC_NOPM,
		INTERP_HPHL, 0, &rx_पूर्णांक1_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT2 INTERP", SND_SOC_NOPM,
		INTERP_HPHR, 0, &rx_पूर्णांक2_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT3 INTERP", SND_SOC_NOPM,
		INTERP_LO1, 0, &rx_पूर्णांक3_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT4 INTERP", SND_SOC_NOPM,
		INTERP_LO2, 0, &rx_पूर्णांक4_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT5 INTERP", SND_SOC_NOPM,
		INTERP_LO3, 0, &rx_पूर्णांक5_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT6 INTERP", SND_SOC_NOPM,
		INTERP_LO4, 0, &rx_पूर्णांक6_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT7 INTERP", SND_SOC_NOPM,
		INTERP_SPKR1, 0, &rx_पूर्णांक7_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT8 INTERP", SND_SOC_NOPM,
		INTERP_SPKR2, 0, &rx_पूर्णांक8_पूर्णांकerp_mux,
		wcd9335_codec_enable_पूर्णांकerpolator,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_DAC_E("RX INT0 DAC", शून्य, SND_SOC_NOPM,
		0, 0, wcd9335_codec_ear_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT1 DAC", शून्य, WCD9335_ANA_HPH,
		5, 0, wcd9335_codec_hphl_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT2 DAC", शून्य, WCD9335_ANA_HPH,
		4, 0, wcd9335_codec_hphr_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT3 DAC", शून्य, SND_SOC_NOPM,
		0, 0, wcd9335_codec_lineout_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT4 DAC", शून्य, SND_SOC_NOPM,
		0, 0, wcd9335_codec_lineout_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT5 DAC", शून्य, SND_SOC_NOPM,
		0, 0, wcd9335_codec_lineout_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT6 DAC", शून्य, SND_SOC_NOPM,
		0, 0, wcd9335_codec_lineout_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("HPHL PA", WCD9335_ANA_HPH, 7, 0, शून्य, 0,
			   wcd9335_codec_enable_hphl_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("HPHR PA", WCD9335_ANA_HPH, 6, 0, शून्य, 0,
			   wcd9335_codec_enable_hphr_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("EAR PA", WCD9335_ANA_EAR, 7, 0, शून्य, 0,
			   wcd9335_codec_enable_ear_pa,
			   SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LINEOUT1 PA", WCD9335_ANA_LO_1_2, 7, 0, शून्य, 0,
			   wcd9335_codec_enable_lineout_pa,
			   SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LINEOUT2 PA", WCD9335_ANA_LO_1_2, 6, 0, शून्य, 0,
			   wcd9335_codec_enable_lineout_pa,
			   SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LINEOUT3 PA", WCD9335_ANA_LO_3_4, 7, 0, शून्य, 0,
			   wcd9335_codec_enable_lineout_pa,
			   SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LINEOUT4 PA", WCD9335_ANA_LO_3_4, 6, 0, शून्य, 0,
			   wcd9335_codec_enable_lineout_pa,
			   SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("RX_BIAS", SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_rx_bias, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MCLK",  SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_mclk, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	/* TX */
	SND_SOC_DAPM_INPUT("AMIC1"),
	SND_SOC_DAPM_INPUT("AMIC2"),
	SND_SOC_DAPM_INPUT("AMIC3"),
	SND_SOC_DAPM_INPUT("AMIC4"),
	SND_SOC_DAPM_INPUT("AMIC5"),
	SND_SOC_DAPM_INPUT("AMIC6"),

	SND_SOC_DAPM_AIF_OUT_E("AIF1 CAP", "AIF1 Capture", 0, SND_SOC_NOPM,
		AIF1_CAP, 0, wcd9335_codec_enable_slim,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_AIF_OUT_E("AIF2 CAP", "AIF2 Capture", 0, SND_SOC_NOPM,
		AIF2_CAP, 0, wcd9335_codec_enable_slim,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_AIF_OUT_E("AIF3 CAP", "AIF3 Capture", 0, SND_SOC_NOPM,
		AIF3_CAP, 0, wcd9335_codec_enable_slim,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("MIC BIAS1", SND_SOC_NOPM, 0, 0,
			       wcd9335_codec_enable_micbias,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS2", SND_SOC_NOPM, 0, 0,
			       wcd9335_codec_enable_micbias,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS3", SND_SOC_NOPM, 0, 0,
			       wcd9335_codec_enable_micbias,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS4", SND_SOC_NOPM, 0, 0,
			       wcd9335_codec_enable_micbias,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("ADC1", शून्य, WCD9335_ANA_AMIC1, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC2", शून्य, WCD9335_ANA_AMIC2, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC3", शून्य, WCD9335_ANA_AMIC3, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC4", शून्य, WCD9335_ANA_AMIC4, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC5", शून्य, WCD9335_ANA_AMIC5, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC6", शून्य, WCD9335_ANA_AMIC6, 7, 0,
			   wcd9335_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),

	/* Digital Mic Inमाला_दो */
	SND_SOC_DAPM_ADC_E("DMIC0", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("DMIC1", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("DMIC2", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("DMIC3", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("DMIC4", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("DMIC5", शून्य, SND_SOC_NOPM, 0, 0,
		wcd9335_codec_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("DMIC MUX0", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux0),
	SND_SOC_DAPM_MUX("DMIC MUX1", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux1),
	SND_SOC_DAPM_MUX("DMIC MUX2", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux2),
	SND_SOC_DAPM_MUX("DMIC MUX3", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux3),
	SND_SOC_DAPM_MUX("DMIC MUX4", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux4),
	SND_SOC_DAPM_MUX("DMIC MUX5", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux5),
	SND_SOC_DAPM_MUX("DMIC MUX6", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux6),
	SND_SOC_DAPM_MUX("DMIC MUX7", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux7),
	SND_SOC_DAPM_MUX("DMIC MUX8", SND_SOC_NOPM, 0, 0,
		&tx_dmic_mux8),

	SND_SOC_DAPM_MUX("AMIC MUX0", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux0),
	SND_SOC_DAPM_MUX("AMIC MUX1", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux1),
	SND_SOC_DAPM_MUX("AMIC MUX2", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux2),
	SND_SOC_DAPM_MUX("AMIC MUX3", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux3),
	SND_SOC_DAPM_MUX("AMIC MUX4", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux4),
	SND_SOC_DAPM_MUX("AMIC MUX5", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux5),
	SND_SOC_DAPM_MUX("AMIC MUX6", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux6),
	SND_SOC_DAPM_MUX("AMIC MUX7", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux7),
	SND_SOC_DAPM_MUX("AMIC MUX8", SND_SOC_NOPM, 0, 0,
		&tx_amic_mux8),

	SND_SOC_DAPM_MIXER("AIF1_CAP Mixer", SND_SOC_NOPM, AIF1_CAP, 0,
		aअगर1_cap_mixer, ARRAY_SIZE(aअगर1_cap_mixer)),

	SND_SOC_DAPM_MIXER("AIF2_CAP Mixer", SND_SOC_NOPM, AIF2_CAP, 0,
		aअगर2_cap_mixer, ARRAY_SIZE(aअगर2_cap_mixer)),

	SND_SOC_DAPM_MIXER("AIF3_CAP Mixer", SND_SOC_NOPM, AIF3_CAP, 0,
		aअगर3_cap_mixer, ARRAY_SIZE(aअगर3_cap_mixer)),

	SND_SOC_DAPM_MUX("SLIM TX0 MUX", SND_SOC_NOPM, WCD9335_TX0, 0,
		&sb_tx0_mux),
	SND_SOC_DAPM_MUX("SLIM TX1 MUX", SND_SOC_NOPM, WCD9335_TX1, 0,
		&sb_tx1_mux),
	SND_SOC_DAPM_MUX("SLIM TX2 MUX", SND_SOC_NOPM, WCD9335_TX2, 0,
		&sb_tx2_mux),
	SND_SOC_DAPM_MUX("SLIM TX3 MUX", SND_SOC_NOPM, WCD9335_TX3, 0,
		&sb_tx3_mux),
	SND_SOC_DAPM_MUX("SLIM TX4 MUX", SND_SOC_NOPM, WCD9335_TX4, 0,
		&sb_tx4_mux),
	SND_SOC_DAPM_MUX("SLIM TX5 MUX", SND_SOC_NOPM, WCD9335_TX5, 0,
		&sb_tx5_mux),
	SND_SOC_DAPM_MUX("SLIM TX6 MUX", SND_SOC_NOPM, WCD9335_TX6, 0,
		&sb_tx6_mux),
	SND_SOC_DAPM_MUX("SLIM TX7 MUX", SND_SOC_NOPM, WCD9335_TX7, 0,
		&sb_tx7_mux),
	SND_SOC_DAPM_MUX("SLIM TX8 MUX", SND_SOC_NOPM, WCD9335_TX8, 0,
		&sb_tx8_mux),

	SND_SOC_DAPM_MUX_E("ADC MUX0", WCD9335_CDC_TX0_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux0, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX1", WCD9335_CDC_TX1_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux1, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX2", WCD9335_CDC_TX2_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux2, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX3", WCD9335_CDC_TX3_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux3, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX4", WCD9335_CDC_TX4_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux4, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX5", WCD9335_CDC_TX5_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux5, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX6", WCD9335_CDC_TX6_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux6, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX7", WCD9335_CDC_TX7_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux7, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("ADC MUX8", WCD9335_CDC_TX8_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux8, wcd9335_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल व्योम wcd9335_enable_siकरो_buck(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);

	snd_soc_component_update_bits(component, WCD9335_ANA_RCO,
					WCD9335_ANA_RCO_BG_EN_MASK,
					WCD9335_ANA_RCO_BG_ENABLE);
	snd_soc_component_update_bits(component, WCD9335_ANA_BUCK_CTL,
					WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_MASK,
					WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_EXT);
	/* 100us sleep needed after IREF settings */
	usleep_range(100, 110);
	snd_soc_component_update_bits(component, WCD9335_ANA_BUCK_CTL,
					WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_MASK,
					WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_EXT);
	/* 100us sleep needed after VREF settings */
	usleep_range(100, 110);
	wcd->siकरो_input_src = SIDO_SOURCE_RCO_BG;
पूर्ण

अटल पूर्णांक wcd9335_enable_efuse_sensing(काष्ठा snd_soc_component *comp)
अणु
	_wcd9335_codec_enable_mclk(comp, true);
	snd_soc_component_update_bits(comp,
				WCD9335_CHIP_TIER_CTRL_EFUSE_CTL,
				WCD9335_CHIP_TIER_CTRL_EFUSE_EN_MASK,
				WCD9335_CHIP_TIER_CTRL_EFUSE_ENABLE);
	/*
	 * 5ms sleep required after enabling efuse control
	 * beक्रमe checking the status.
	 */
	usleep_range(5000, 5500);

	अगर (!(snd_soc_component_पढ़ो(comp,
					WCD9335_CHIP_TIER_CTRL_EFUSE_STATUS) &
					WCD9335_CHIP_TIER_CTRL_EFUSE_EN_MASK))
		WARN(1, "%s: Efuse sense is not complete\n", __func__);

	wcd9335_enable_siकरो_buck(comp);
	_wcd9335_codec_enable_mclk(comp, false);

	वापस 0;
पूर्ण

अटल व्योम wcd9335_codec_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक i;

	/* ungate MCLK and set clk rate */
	regmap_update_bits(wcd->regmap, WCD9335_CODEC_RPM_CLK_GATE,
				WCD9335_CODEC_RPM_CLK_GATE_MCLK_GATE_MASK, 0);

	regmap_update_bits(wcd->regmap, WCD9335_CODEC_RPM_CLK_MCLK_CFG,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ);

	क्रम (i = 0; i < ARRAY_SIZE(wcd9335_codec_reg_init); i++)
		snd_soc_component_update_bits(component,
					wcd9335_codec_reg_init[i].reg,
					wcd9335_codec_reg_init[i].mask,
					wcd9335_codec_reg_init[i].val);

	wcd9335_enable_efuse_sensing(component);
पूर्ण

अटल पूर्णांक wcd9335_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक i;

	snd_soc_component_init_regmap(component, wcd->regmap);
	/* Class-H Init*/
	wcd->clsh_ctrl = wcd_clsh_ctrl_alloc(component, wcd->version);
	अगर (IS_ERR(wcd->clsh_ctrl))
		वापस PTR_ERR(wcd->clsh_ctrl);

	/* Default HPH Mode to Class-H HiFi */
	wcd->hph_mode = CLS_H_HIFI;
	wcd->component = component;

	wcd9335_codec_init(component);

	क्रम (i = 0; i < NUM_CODEC_DAIS; i++)
		INIT_LIST_HEAD(&wcd->dai[i].slim_ch_list);

	वापस wcd9335_setup_irqs(wcd);
पूर्ण

अटल व्योम wcd9335_codec_हटाओ(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	wcd_clsh_ctrl_मुक्त(wcd->clsh_ctrl);
	मुक्त_irq(regmap_irq_get_virq(wcd->irq_data, WCD9335_IRQ_SLIMBUS), wcd);
पूर्ण

अटल पूर्णांक wcd9335_codec_set_sysclk(काष्ठा snd_soc_component *comp,
				    पूर्णांक clk_id, पूर्णांक source,
				    अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	wcd->mclk_rate = freq;

	अगर (wcd->mclk_rate == WCD9335_MCLK_CLK_12P288MHZ)
		snd_soc_component_update_bits(comp,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_12P288MHZ);
	अन्यथा अगर (wcd->mclk_rate == WCD9335_MCLK_CLK_9P6MHZ)
		snd_soc_component_update_bits(comp,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ);

	वापस clk_set_rate(wcd->mclk, freq);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver wcd9335_component_drv = अणु
	.probe = wcd9335_codec_probe,
	.हटाओ = wcd9335_codec_हटाओ,
	.set_sysclk = wcd9335_codec_set_sysclk,
	.controls = wcd9335_snd_controls,
	.num_controls = ARRAY_SIZE(wcd9335_snd_controls),
	.dapm_widमाला_लो = wcd9335_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wcd9335_dapm_widमाला_लो),
	.dapm_routes = wcd9335_audio_map,
	.num_dapm_routes = ARRAY_SIZE(wcd9335_audio_map),
पूर्ण;

अटल पूर्णांक wcd9335_probe(काष्ठा wcd9335_codec *wcd)
अणु
	काष्ठा device *dev = wcd->dev;

	स_नकल(wcd->rx_chs, wcd9335_rx_chs, माप(wcd9335_rx_chs));
	स_नकल(wcd->tx_chs, wcd9335_tx_chs, माप(wcd9335_tx_chs));

	wcd->siकरो_input_src = SIDO_SOURCE_INTERNAL;
	wcd->siकरो_voltage = SIDO_VOLTAGE_NOMINAL_MV;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &wcd9335_component_drv,
					       wcd9335_slim_dais,
					       ARRAY_SIZE(wcd9335_slim_dais));
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg wcd9335_ranges[] = अणु
	अणु
		.name = "WCD9335",
		.range_min =  0x0,
		.range_max =  WCD9335_MAX_REGISTER,
		.selector_reg = WCD9335_SEL_REGISTER,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0x800,
		.winकरोw_len = 0x100,
	पूर्ण,
पूर्ण;

अटल bool wcd9335_is_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WCD9335_INTR_PIN1_STATUS0...WCD9335_INTR_PIN2_CLEAR3:
	हाल WCD9335_ANA_MBHC_RESULT_3:
	हाल WCD9335_ANA_MBHC_RESULT_2:
	हाल WCD9335_ANA_MBHC_RESULT_1:
	हाल WCD9335_ANA_MBHC_MECH:
	हाल WCD9335_ANA_MBHC_ELECT:
	हाल WCD9335_ANA_MBHC_ZDET:
	हाल WCD9335_ANA_MICB2:
	हाल WCD9335_ANA_RCO:
	हाल WCD9335_ANA_BIAS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा regmap_config wcd9335_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = WCD9335_MAX_REGISTER,
	.can_multi_ग_लिखो = true,
	.ranges = wcd9335_ranges,
	.num_ranges = ARRAY_SIZE(wcd9335_ranges),
	.अस्थिर_reg = wcd9335_is_अस्थिर_रेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg wcd9335_अगरc_ranges[] = अणु
	अणु
		.name = "WCD9335-IFC-DEV",
		.range_min =  0x0,
		.range_max = WCD9335_MAX_REGISTER,
		.selector_reg = WCD9335_SEL_REGISTER,
		.selector_mask = 0xfff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0x800,
		.winकरोw_len = 0x400,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config wcd9335_अगरc_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.can_multi_ग_लिखो = true,
	.max_रेजिस्टर = WCD9335_MAX_REGISTER,
	.ranges = wcd9335_अगरc_ranges,
	.num_ranges = ARRAY_SIZE(wcd9335_अगरc_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq wcd9335_codec_irqs[] = अणु
	/* INTR_REG 0 */
	[WCD9335_IRQ_SLIMBUS] = अणु
		.reg_offset = 0,
		.mask = BIT(0),
		.type = अणु
			.type_reg_offset = 0,
			.types_supported = IRQ_TYPE_EDGE_BOTH,
			.type_reg_mask	= BIT(0),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip wcd9335_regmap_irq1_chip = अणु
	.name = "wcd9335_pin1_irq",
	.status_base = WCD9335_INTR_PIN1_STATUS0,
	.mask_base = WCD9335_INTR_PIN1_MASK0,
	.ack_base = WCD9335_INTR_PIN1_CLEAR0,
	.type_base = WCD9335_INTR_LEVEL0,
	.num_type_reg = 4,
	.num_regs = 4,
	.irqs = wcd9335_codec_irqs,
	.num_irqs = ARRAY_SIZE(wcd9335_codec_irqs),
पूर्ण;

अटल पूर्णांक wcd9335_parse_dt(काष्ठा wcd9335_codec *wcd)
अणु
	काष्ठा device *dev = wcd->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	wcd->reset_gpio = of_get_named_gpio(np,	"reset-gpios", 0);
	अगर (wcd->reset_gpio < 0) अणु
		dev_err(dev, "Reset GPIO missing from DT\n");
		वापस wcd->reset_gpio;
	पूर्ण

	wcd->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(wcd->mclk)) अणु
		dev_err(dev, "mclk not found\n");
		वापस PTR_ERR(wcd->mclk);
	पूर्ण

	wcd->native_clk = devm_clk_get(dev, "slimbus");
	अगर (IS_ERR(wcd->native_clk)) अणु
		dev_err(dev, "slimbus clock not found\n");
		वापस PTR_ERR(wcd->native_clk);
	पूर्ण

	wcd->supplies[0].supply = "vdd-buck";
	wcd->supplies[1].supply = "vdd-buck-sido";
	wcd->supplies[2].supply = "vdd-tx";
	wcd->supplies[3].supply = "vdd-rx";
	wcd->supplies[4].supply = "vdd-io";

	ret = regulator_bulk_get(dev, WCD9335_MAX_SUPPLY, wcd->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get supplies: err = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_घातer_on_reset(काष्ठा wcd9335_codec *wcd)
अणु
	काष्ठा device *dev = wcd->dev;
	पूर्णांक ret;

	ret = regulator_bulk_enable(WCD9335_MAX_SUPPLY, wcd->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get supplies: err = %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * For WCD9335, it takes about 600us क्रम the Vout_A and
	 * Vout_D to be पढ़ोy after BUCK_SIDO is घातered up.
	 * SYS_RST_N shouldn't be pulled high during this समय
	 * Toggle the reset line to make sure the reset pulse is
	 * correctly applied
	 */
	usleep_range(600, 650);

	gpio_direction_output(wcd->reset_gpio, 0);
	msleep(20);
	gpio_set_value(wcd->reset_gpio, 1);
	msleep(20);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_bring_up(काष्ठा wcd9335_codec *wcd)
अणु
	काष्ठा regmap *rm = wcd->regmap;
	पूर्णांक val, byte0;

	regmap_पढ़ो(rm, WCD9335_CHIP_TIER_CTRL_EFUSE_VAL_OUT0, &val);
	regmap_पढ़ो(rm, WCD9335_CHIP_TIER_CTRL_CHIP_ID_BYTE0, &byte0);

	अगर ((val < 0) || (byte0 < 0)) अणु
		dev_err(wcd->dev, "WCD9335 CODEC version detection fail!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (byte0 == 0x1) अणु
		dev_info(wcd->dev, "WCD9335 CODEC version is v2.0\n");
		wcd->version = WCD9335_VERSION_2_0;
		regmap_ग_लिखो(rm, WCD9335_CODEC_RPM_RST_CTL, 0x01);
		regmap_ग_लिखो(rm, WCD9335_SIDO_SIDO_TEST_2, 0x00);
		regmap_ग_लिखो(rm, WCD9335_SIDO_SIDO_CCL_8, 0x6F);
		regmap_ग_लिखो(rm, WCD9335_BIAS_VBG_FINE_ADJ, 0x65);
		regmap_ग_लिखो(rm, WCD9335_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x5);
		regmap_ग_लिखो(rm, WCD9335_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x7);
		regmap_ग_लिखो(rm, WCD9335_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x3);
		regmap_ग_लिखो(rm, WCD9335_CODEC_RPM_RST_CTL, 0x3);
	पूर्ण अन्यथा अणु
		dev_err(wcd->dev, "WCD9335 CODEC version not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_irq_init(काष्ठा wcd9335_codec *wcd)
अणु
	पूर्णांक ret;

	/*
	 * INTR1 consists of all possible पूर्णांकerrupt sources Ear OCP,
	 * HPH OCP, MBHC, MAD, VBAT, and SVA
	 * INTR2 is a subset of first पूर्णांकerrupt sources MAD, VBAT, and SVA
	 */
	wcd->पूर्णांकr1 = of_irq_get_byname(wcd->dev->of_node, "intr1");
	अगर (wcd->पूर्णांकr1 < 0) अणु
		अगर (wcd->पूर्णांकr1 != -EPROBE_DEFER)
			dev_err(wcd->dev, "Unable to configure IRQ\n");

		वापस wcd->पूर्णांकr1;
	पूर्ण

	ret = devm_regmap_add_irq_chip(wcd->dev, wcd->regmap, wcd->पूर्णांकr1,
				 IRQF_TRIGGER_HIGH, 0,
				 &wcd9335_regmap_irq1_chip, &wcd->irq_data);
	अगर (ret)
		dev_err(wcd->dev, "Failed to register IRQ chip: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wcd9335_slim_probe(काष्ठा slim_device *slim)
अणु
	काष्ठा device *dev = &slim->dev;
	काष्ठा wcd9335_codec *wcd;
	पूर्णांक ret;

	wcd = devm_kzalloc(dev, माप(*wcd), GFP_KERNEL);
	अगर (!wcd)
		वापस	-ENOMEM;

	wcd->dev = dev;
	ret = wcd9335_parse_dt(wcd);
	अगर (ret) अणु
		dev_err(dev, "Error parsing DT: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wcd9335_घातer_on_reset(wcd);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, wcd);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd9335_slim_status(काष्ठा slim_device *sdev,
			       क्रमागत slim_device_status status)
अणु
	काष्ठा device *dev = &sdev->dev;
	काष्ठा device_node *अगरc_dev_np;
	काष्ठा wcd9335_codec *wcd;
	पूर्णांक ret;

	wcd = dev_get_drvdata(dev);

	अगरc_dev_np = of_parse_phandle(dev->of_node, "slim-ifc-dev", 0);
	अगर (!अगरc_dev_np) अणु
		dev_err(dev, "No Interface device found\n");
		वापस -EINVAL;
	पूर्ण

	wcd->slim = sdev;
	wcd->slim_अगरc_dev = of_slim_get_device(sdev->ctrl, अगरc_dev_np);
	of_node_put(अगरc_dev_np);
	अगर (!wcd->slim_अगरc_dev) अणु
		dev_err(dev, "Unable to get SLIM Interface device\n");
		वापस -EINVAL;
	पूर्ण

	slim_get_logical_addr(wcd->slim_अगरc_dev);

	wcd->regmap = regmap_init_slimbus(sdev, &wcd9335_regmap_config);
	अगर (IS_ERR(wcd->regmap)) अणु
		dev_err(dev, "Failed to allocate slim register map\n");
		वापस PTR_ERR(wcd->regmap);
	पूर्ण

	wcd->अगर_regmap = regmap_init_slimbus(wcd->slim_अगरc_dev,
						  &wcd9335_अगरc_regmap_config);
	अगर (IS_ERR(wcd->अगर_regmap)) अणु
		dev_err(dev, "Failed to allocate ifc register map\n");
		वापस PTR_ERR(wcd->अगर_regmap);
	पूर्ण

	ret = wcd9335_bring_up(wcd);
	अगर (ret) अणु
		dev_err(dev, "Failed to bringup WCD9335\n");
		वापस ret;
	पूर्ण

	ret = wcd9335_irq_init(wcd);
	अगर (ret)
		वापस ret;

	wcd9335_probe(wcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा slim_device_id wcd9335_slim_id[] = अणु
	अणुSLIM_MANF_ID_QCOM, SLIM_PROD_CODE_WCD9335, 0x1, 0x0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(slim, wcd9335_slim_id);

अटल काष्ठा slim_driver wcd9335_slim_driver = अणु
	.driver = अणु
		.name = "wcd9335-slim",
	पूर्ण,
	.probe = wcd9335_slim_probe,
	.device_status = wcd9335_slim_status,
	.id_table = wcd9335_slim_id,
पूर्ण;

module_slim_driver(wcd9335_slim_driver);
MODULE_DESCRIPTION("WCD9335 slim driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("slim:217:1a0:*");
