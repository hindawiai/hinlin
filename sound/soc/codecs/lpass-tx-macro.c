<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/clk-provider.h>

#घोषणा CDC_TX_CLK_RST_CTRL_MCLK_CONTROL (0x0000)
#घोषणा CDC_TX_MCLK_EN_MASK		BIT(0)
#घोषणा CDC_TX_MCLK_ENABLE		BIT(0)
#घोषणा CDC_TX_CLK_RST_CTRL_FS_CNT_CONTROL (0x0004)
#घोषणा CDC_TX_FS_CNT_EN_MASK		BIT(0)
#घोषणा CDC_TX_FS_CNT_ENABLE		BIT(0)
#घोषणा CDC_TX_CLK_RST_CTRL_SWR_CONTROL	(0x0008)
#घोषणा CDC_TX_SWR_RESET_MASK		BIT(1)
#घोषणा CDC_TX_SWR_RESET_ENABLE		BIT(1)
#घोषणा CDC_TX_SWR_CLK_EN_MASK		BIT(0)
#घोषणा CDC_TX_SWR_CLK_ENABLE		BIT(0)
#घोषणा CDC_TX_TOP_CSR_TOP_CFG0		(0x0080)
#घोषणा CDC_TX_TOP_CSR_ANC_CFG		(0x0084)
#घोषणा CDC_TX_TOP_CSR_SWR_CTRL		(0x0088)
#घोषणा CDC_TX_TOP_CSR_FREQ_MCLK	(0x0090)
#घोषणा CDC_TX_TOP_CSR_DEBUG_BUS	(0x0094)
#घोषणा CDC_TX_TOP_CSR_DEBUG_EN		(0x0098)
#घोषणा CDC_TX_TOP_CSR_TX_I2S_CTL	(0x00A4)
#घोषणा CDC_TX_TOP_CSR_I2S_CLK		(0x00A8)
#घोषणा CDC_TX_TOP_CSR_I2S_RESET	(0x00AC)
#घोषणा CDC_TX_TOP_CSR_SWR_DMICn_CTL(n)	(0x00C0 + n * 0x4)
#घोषणा CDC_TX_TOP_CSR_SWR_DMIC0_CTL	(0x00C0)
#घोषणा CDC_TX_SWR_DMIC_CLK_SEL_MASK	GENMASK(3, 1)
#घोषणा CDC_TX_TOP_CSR_SWR_DMIC1_CTL	(0x00C4)
#घोषणा CDC_TX_TOP_CSR_SWR_DMIC2_CTL	(0x00C8)
#घोषणा CDC_TX_TOP_CSR_SWR_DMIC3_CTL	(0x00CC)
#घोषणा CDC_TX_TOP_CSR_SWR_AMIC0_CTL	(0x00D0)
#घोषणा CDC_TX_TOP_CSR_SWR_AMIC1_CTL	(0x00D4)
#घोषणा CDC_TX_INP_MUX_ADC_MUXn_CFG0(n)	(0x0100 + 0x8 * n)
#घोषणा CDC_TX_MACRO_SWR_MIC_MUX_SEL_MASK GENMASK(3, 0)
#घोषणा CDC_TX_INP_MUX_ADC_MUX0_CFG0	(0x0100)
#घोषणा CDC_TX_INP_MUX_ADC_MUXn_CFG1(n)	(0x0104 + 0x8 * n)
#घोषणा CDC_TX_INP_MUX_ADC_MUX0_CFG1	(0x0104)
#घोषणा CDC_TX_INP_MUX_ADC_MUX1_CFG0	(0x0108)
#घोषणा CDC_TX_INP_MUX_ADC_MUX1_CFG1	(0x010C)
#घोषणा CDC_TX_INP_MUX_ADC_MUX2_CFG0	(0x0110)
#घोषणा CDC_TX_INP_MUX_ADC_MUX2_CFG1	(0x0114)
#घोषणा CDC_TX_INP_MUX_ADC_MUX3_CFG0	(0x0118)
#घोषणा CDC_TX_INP_MUX_ADC_MUX3_CFG1	(0x011C)
#घोषणा CDC_TX_INP_MUX_ADC_MUX4_CFG0	(0x0120)
#घोषणा CDC_TX_INP_MUX_ADC_MUX4_CFG1	(0x0124)
#घोषणा CDC_TX_INP_MUX_ADC_MUX5_CFG0	(0x0128)
#घोषणा CDC_TX_INP_MUX_ADC_MUX5_CFG1	(0x012C)
#घोषणा CDC_TX_INP_MUX_ADC_MUX6_CFG0	(0x0130)
#घोषणा CDC_TX_INP_MUX_ADC_MUX6_CFG1	(0x0134)
#घोषणा CDC_TX_INP_MUX_ADC_MUX7_CFG0	(0x0138)
#घोषणा CDC_TX_INP_MUX_ADC_MUX7_CFG1	(0x013C)
#घोषणा CDC_TX_ANC0_CLK_RESET_CTL	(0x0200)
#घोषणा CDC_TX_ANC0_MODE_1_CTL		(0x0204)
#घोषणा CDC_TX_ANC0_MODE_2_CTL		(0x0208)
#घोषणा CDC_TX_ANC0_FF_SHIFT		(0x020C)
#घोषणा CDC_TX_ANC0_FB_SHIFT		(0x0210)
#घोषणा CDC_TX_ANC0_LPF_FF_A_CTL	(0x0214)
#घोषणा CDC_TX_ANC0_LPF_FF_B_CTL	(0x0218)
#घोषणा CDC_TX_ANC0_LPF_FB_CTL		(0x021C)
#घोषणा CDC_TX_ANC0_SMLPF_CTL		(0x0220)
#घोषणा CDC_TX_ANC0_DCFLT_SHIFT_CTL	(0x0224)
#घोषणा CDC_TX_ANC0_IIR_ADAPT_CTL	(0x0228)
#घोषणा CDC_TX_ANC0_IIR_COEFF_1_CTL	(0x022C)
#घोषणा CDC_TX_ANC0_IIR_COEFF_2_CTL	(0x0230)
#घोषणा CDC_TX_ANC0_FF_A_GAIN_CTL	(0x0234)
#घोषणा CDC_TX_ANC0_FF_B_GAIN_CTL	(0x0238)
#घोषणा CDC_TX_ANC0_FB_GAIN_CTL		(0x023C)
#घोषणा CDC_TXn_TX_PATH_CTL(n)		(0x0400 + 0x80 * n)
#घोषणा CDC_TXn_PCM_RATE_MASK		GENMASK(3, 0)
#घोषणा CDC_TXn_PGA_MUTE_MASK		BIT(4)
#घोषणा CDC_TXn_CLK_EN_MASK		BIT(5)
#घोषणा CDC_TX0_TX_PATH_CTL		(0x0400)
#घोषणा CDC_TXn_TX_PATH_CFG0(n)		(0x0404 + 0x80 * n)
#घोषणा CDC_TX0_TX_PATH_CFG0		(0x0404)
#घोषणा CDC_TXn_PH_EN_MASK		BIT(0)
#घोषणा CDC_TXn_ADC_MODE_MASK		GENMASK(2, 1)
#घोषणा CDC_TXn_HPF_CUT_FREQ_MASK	GENMASK(6, 5)
#घोषणा CDC_TXn_ADC_DMIC_SEL_MASK	BIT(7)
#घोषणा CDC_TX0_TX_PATH_CFG1		(0x0408)
#घोषणा CDC_TXn_TX_VOL_CTL(n)		(0x040C + 0x80 * n)
#घोषणा CDC_TX0_TX_VOL_CTL		(0x040C)
#घोषणा CDC_TX0_TX_PATH_SEC0		(0x0410)
#घोषणा CDC_TX0_TX_PATH_SEC1		(0x0414)
#घोषणा CDC_TXn_TX_PATH_SEC2(n)		(0x0418 + 0x80 * n)
#घोषणा CDC_TXn_HPF_F_CHANGE_MASK	 BIT(1)
#घोषणा CDC_TXn_HPF_ZERO_GATE_MASK	 BIT(0)
#घोषणा CDC_TX0_TX_PATH_SEC2		(0x0418)
#घोषणा CDC_TX0_TX_PATH_SEC3		(0x041C)
#घोषणा CDC_TX0_TX_PATH_SEC4		(0x0420)
#घोषणा CDC_TX0_TX_PATH_SEC5		(0x0424)
#घोषणा CDC_TX0_TX_PATH_SEC6		(0x0428)
#घोषणा CDC_TX0_TX_PATH_SEC7		(0x042C)
#घोषणा CDC_TX0_MBHC_CTL_EN_MASK	BIT(6)
#घोषणा CDC_TX1_TX_PATH_CTL		(0x0480)
#घोषणा CDC_TX1_TX_PATH_CFG0		(0x0484)
#घोषणा CDC_TX1_TX_PATH_CFG1		(0x0488)
#घोषणा CDC_TX1_TX_VOL_CTL		(0x048C)
#घोषणा CDC_TX1_TX_PATH_SEC0		(0x0490)
#घोषणा CDC_TX1_TX_PATH_SEC1		(0x0494)
#घोषणा CDC_TX1_TX_PATH_SEC2		(0x0498)
#घोषणा CDC_TX1_TX_PATH_SEC3		(0x049C)
#घोषणा CDC_TX1_TX_PATH_SEC4		(0x04A0)
#घोषणा CDC_TX1_TX_PATH_SEC5		(0x04A4)
#घोषणा CDC_TX1_TX_PATH_SEC6		(0x04A8)
#घोषणा CDC_TX2_TX_PATH_CTL		(0x0500)
#घोषणा CDC_TX2_TX_PATH_CFG0		(0x0504)
#घोषणा CDC_TX2_TX_PATH_CFG1		(0x0508)
#घोषणा CDC_TX2_TX_VOL_CTL		(0x050C)
#घोषणा CDC_TX2_TX_PATH_SEC0		(0x0510)
#घोषणा CDC_TX2_TX_PATH_SEC1		(0x0514)
#घोषणा CDC_TX2_TX_PATH_SEC2		(0x0518)
#घोषणा CDC_TX2_TX_PATH_SEC3		(0x051C)
#घोषणा CDC_TX2_TX_PATH_SEC4		(0x0520)
#घोषणा CDC_TX2_TX_PATH_SEC5		(0x0524)
#घोषणा CDC_TX2_TX_PATH_SEC6		(0x0528)
#घोषणा CDC_TX3_TX_PATH_CTL		(0x0580)
#घोषणा CDC_TX3_TX_PATH_CFG0		(0x0584)
#घोषणा CDC_TX3_TX_PATH_CFG1		(0x0588)
#घोषणा CDC_TX3_TX_VOL_CTL		(0x058C)
#घोषणा CDC_TX3_TX_PATH_SEC0		(0x0590)
#घोषणा CDC_TX3_TX_PATH_SEC1		(0x0594)
#घोषणा CDC_TX3_TX_PATH_SEC2		(0x0598)
#घोषणा CDC_TX3_TX_PATH_SEC3		(0x059C)
#घोषणा CDC_TX3_TX_PATH_SEC4		(0x05A0)
#घोषणा CDC_TX3_TX_PATH_SEC5		(0x05A4)
#घोषणा CDC_TX3_TX_PATH_SEC6		(0x05A8)
#घोषणा CDC_TX4_TX_PATH_CTL		(0x0600)
#घोषणा CDC_TX4_TX_PATH_CFG0		(0x0604)
#घोषणा CDC_TX4_TX_PATH_CFG1		(0x0608)
#घोषणा CDC_TX4_TX_VOL_CTL		(0x060C)
#घोषणा CDC_TX4_TX_PATH_SEC0		(0x0610)
#घोषणा CDC_TX4_TX_PATH_SEC1		(0x0614)
#घोषणा CDC_TX4_TX_PATH_SEC2		(0x0618)
#घोषणा CDC_TX4_TX_PATH_SEC3		(0x061C)
#घोषणा CDC_TX4_TX_PATH_SEC4		(0x0620)
#घोषणा CDC_TX4_TX_PATH_SEC5		(0x0624)
#घोषणा CDC_TX4_TX_PATH_SEC6		(0x0628)
#घोषणा CDC_TX5_TX_PATH_CTL		(0x0680)
#घोषणा CDC_TX5_TX_PATH_CFG0		(0x0684)
#घोषणा CDC_TX5_TX_PATH_CFG1		(0x0688)
#घोषणा CDC_TX5_TX_VOL_CTL		(0x068C)
#घोषणा CDC_TX5_TX_PATH_SEC0		(0x0690)
#घोषणा CDC_TX5_TX_PATH_SEC1		(0x0694)
#घोषणा CDC_TX5_TX_PATH_SEC2		(0x0698)
#घोषणा CDC_TX5_TX_PATH_SEC3		(0x069C)
#घोषणा CDC_TX5_TX_PATH_SEC4		(0x06A0)
#घोषणा CDC_TX5_TX_PATH_SEC5		(0x06A4)
#घोषणा CDC_TX5_TX_PATH_SEC6		(0x06A8)
#घोषणा CDC_TX6_TX_PATH_CTL		(0x0700)
#घोषणा CDC_TX6_TX_PATH_CFG0		(0x0704)
#घोषणा CDC_TX6_TX_PATH_CFG1		(0x0708)
#घोषणा CDC_TX6_TX_VOL_CTL		(0x070C)
#घोषणा CDC_TX6_TX_PATH_SEC0		(0x0710)
#घोषणा CDC_TX6_TX_PATH_SEC1		(0x0714)
#घोषणा CDC_TX6_TX_PATH_SEC2		(0x0718)
#घोषणा CDC_TX6_TX_PATH_SEC3		(0x071C)
#घोषणा CDC_TX6_TX_PATH_SEC4		(0x0720)
#घोषणा CDC_TX6_TX_PATH_SEC5		(0x0724)
#घोषणा CDC_TX6_TX_PATH_SEC6		(0x0728)
#घोषणा CDC_TX7_TX_PATH_CTL		(0x0780)
#घोषणा CDC_TX7_TX_PATH_CFG0		(0x0784)
#घोषणा CDC_TX7_TX_PATH_CFG1		(0x0788)
#घोषणा CDC_TX7_TX_VOL_CTL		(0x078C)
#घोषणा CDC_TX7_TX_PATH_SEC0		(0x0790)
#घोषणा CDC_TX7_TX_PATH_SEC1		(0x0794)
#घोषणा CDC_TX7_TX_PATH_SEC2		(0x0798)
#घोषणा CDC_TX7_TX_PATH_SEC3		(0x079C)
#घोषणा CDC_TX7_TX_PATH_SEC4		(0x07A0)
#घोषणा CDC_TX7_TX_PATH_SEC5		(0x07A4)
#घोषणा CDC_TX7_TX_PATH_SEC6		(0x07A8)
#घोषणा TX_MAX_OFFSET			(0x07A8)

#घोषणा TX_MACRO_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
#घोषणा TX_MACRO_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S24_3LE)

#घोषणा  CF_MIN_3DB_4HZ			0x0
#घोषणा  CF_MIN_3DB_75HZ		0x1
#घोषणा  CF_MIN_3DB_150HZ		0x2
#घोषणा	TX_ADC_MAX	5
#घोषणा TX_ADC_TO_DMIC(n) ((n - TX_ADC_MAX)/2)
#घोषणा NUM_DECIMATORS 8
#घोषणा TX_NUM_CLKS_MAX	5
#घोषणा TX_MACRO_DMIC_UNMUTE_DELAY_MS	40
#घोषणा TX_MACRO_AMIC_UNMUTE_DELAY_MS	100
#घोषणा TX_MACRO_DMIC_HPF_DELAY_MS	300
#घोषणा TX_MACRO_AMIC_HPF_DELAY_MS	300
#घोषणा MCLK_FREQ		9600000

क्रमागत अणु
	TX_MACRO_AIF_INVALID = 0,
	TX_MACRO_AIF1_CAP,
	TX_MACRO_AIF2_CAP,
	TX_MACRO_AIF3_CAP,
	TX_MACRO_MAX_DAIS
पूर्ण;

क्रमागत अणु
	TX_MACRO_DEC0,
	TX_MACRO_DEC1,
	TX_MACRO_DEC2,
	TX_MACRO_DEC3,
	TX_MACRO_DEC4,
	TX_MACRO_DEC5,
	TX_MACRO_DEC6,
	TX_MACRO_DEC7,
	TX_MACRO_DEC_MAX,
पूर्ण;

क्रमागत अणु
	TX_MACRO_CLK_DIV_2,
	TX_MACRO_CLK_DIV_3,
	TX_MACRO_CLK_DIV_4,
	TX_MACRO_CLK_DIV_6,
	TX_MACRO_CLK_DIV_8,
	TX_MACRO_CLK_DIV_16,
पूर्ण;

क्रमागत अणु
	MSM_DMIC,
	SWR_MIC,
	ANC_FB_TUNE1
पूर्ण;

काष्ठा tx_mute_work अणु
	काष्ठा tx_macro *tx;
	u32 decimator;
	काष्ठा delayed_work dwork;
पूर्ण;

काष्ठा hpf_work अणु
	काष्ठा tx_macro *tx;
	u8 decimator;
	u8 hpf_cut_off_freq;
	काष्ठा delayed_work dwork;
पूर्ण;

काष्ठा tx_macro अणु
	काष्ठा device *dev;
	काष्ठा snd_soc_component *component;
	काष्ठा hpf_work tx_hpf_work[NUM_DECIMATORS];
	काष्ठा tx_mute_work tx_mute_dwork[NUM_DECIMATORS];
	अचिन्हित दीर्घ active_ch_mask[TX_MACRO_MAX_DAIS];
	अचिन्हित दीर्घ active_ch_cnt[TX_MACRO_MAX_DAIS];
	अचिन्हित दीर्घ active_decimator[TX_MACRO_MAX_DAIS];
	काष्ठा regmap *regmap;
	काष्ठा clk_bulk_data clks[TX_NUM_CLKS_MAX];
	काष्ठा clk_hw hw;
	bool dec_active[NUM_DECIMATORS];
	bool reset_swr;
	पूर्णांक tx_mclk_users;
	u16 dmic_clk_भाग;
	bool bcs_enable;
	पूर्णांक dec_mode[NUM_DECIMATORS];
	bool bcs_clk_en;
पूर्ण;
#घोषणा to_tx_macro(_hw) container_of(_hw, काष्ठा tx_macro, hw)

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -8400, 100, -8400);

अटल स्थिर काष्ठा reg_शेष tx_शेषs[] = अणु
	/* TX Macro */
	अणु CDC_TX_CLK_RST_CTRL_MCLK_CONTROL, 0x00 पूर्ण,
	अणु CDC_TX_CLK_RST_CTRL_FS_CNT_CONTROL, 0x00 पूर्ण,
	अणु CDC_TX_CLK_RST_CTRL_SWR_CONTROL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_TOP_CFG0, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_ANC_CFG, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_CTRL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_FREQ_MCLK, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_DEBUG_BUS, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_DEBUG_EN, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_TX_I2S_CTL, 0x0Cपूर्ण,
	अणु CDC_TX_TOP_CSR_I2S_CLK, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_I2S_RESET, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_DMIC0_CTL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_DMIC1_CTL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_DMIC2_CTL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_DMIC3_CTL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_AMIC0_CTL, 0x00पूर्ण,
	अणु CDC_TX_TOP_CSR_SWR_AMIC1_CTL, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX0_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX0_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX1_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX1_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX2_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX2_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX3_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX3_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX4_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX4_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX5_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX5_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX6_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX6_CFG1, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX7_CFG0, 0x00पूर्ण,
	अणु CDC_TX_INP_MUX_ADC_MUX7_CFG1, 0x00पूर्ण,
	अणु CDC_TX_ANC0_CLK_RESET_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_MODE_1_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_MODE_2_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_FF_SHIFT, 0x00पूर्ण,
	अणु CDC_TX_ANC0_FB_SHIFT, 0x00पूर्ण,
	अणु CDC_TX_ANC0_LPF_FF_A_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_LPF_FF_B_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_LPF_FB_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_SMLPF_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_DCFLT_SHIFT_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_IIR_ADAPT_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_IIR_COEFF_1_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_IIR_COEFF_2_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_FF_A_GAIN_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_FF_B_GAIN_CTL, 0x00पूर्ण,
	अणु CDC_TX_ANC0_FB_GAIN_CTL, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX0_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX0_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX0_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX0_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX0_TX_PATH_SEC7, 0x25पूर्ण,
	अणु CDC_TX1_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX1_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX1_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX1_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX1_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX1_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX2_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX2_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX2_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX2_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX2_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX2_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX3_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX3_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX3_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX3_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX3_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX3_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX4_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX4_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX4_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX4_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX4_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX4_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX5_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX5_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX5_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX5_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX5_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX5_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX6_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX6_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX6_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX6_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX6_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX6_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_TX7_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_TX7_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_TX7_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_TX7_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_TX7_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_TX7_TX_PATH_SEC6, 0x00पूर्ण,
पूर्ण;

अटल bool tx_is_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Update अस्थिर list क्रम tx/tx macros */
	चयन (reg) अणु
	हाल CDC_TX_TOP_CSR_SWR_DMIC0_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC1_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC2_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC3_CTL:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool tx_is_rw_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_TX_CLK_RST_CTRL_MCLK_CONTROL:
	हाल CDC_TX_CLK_RST_CTRL_FS_CNT_CONTROL:
	हाल CDC_TX_CLK_RST_CTRL_SWR_CONTROL:
	हाल CDC_TX_TOP_CSR_TOP_CFG0:
	हाल CDC_TX_TOP_CSR_ANC_CFG:
	हाल CDC_TX_TOP_CSR_SWR_CTRL:
	हाल CDC_TX_TOP_CSR_FREQ_MCLK:
	हाल CDC_TX_TOP_CSR_DEBUG_BUS:
	हाल CDC_TX_TOP_CSR_DEBUG_EN:
	हाल CDC_TX_TOP_CSR_TX_I2S_CTL:
	हाल CDC_TX_TOP_CSR_I2S_CLK:
	हाल CDC_TX_TOP_CSR_I2S_RESET:
	हाल CDC_TX_TOP_CSR_SWR_DMIC0_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC1_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC2_CTL:
	हाल CDC_TX_TOP_CSR_SWR_DMIC3_CTL:
	हाल CDC_TX_TOP_CSR_SWR_AMIC0_CTL:
	हाल CDC_TX_TOP_CSR_SWR_AMIC1_CTL:
	हाल CDC_TX_ANC0_CLK_RESET_CTL:
	हाल CDC_TX_ANC0_MODE_1_CTL:
	हाल CDC_TX_ANC0_MODE_2_CTL:
	हाल CDC_TX_ANC0_FF_SHIFT:
	हाल CDC_TX_ANC0_FB_SHIFT:
	हाल CDC_TX_ANC0_LPF_FF_A_CTL:
	हाल CDC_TX_ANC0_LPF_FF_B_CTL:
	हाल CDC_TX_ANC0_LPF_FB_CTL:
	हाल CDC_TX_ANC0_SMLPF_CTL:
	हाल CDC_TX_ANC0_DCFLT_SHIFT_CTL:
	हाल CDC_TX_ANC0_IIR_ADAPT_CTL:
	हाल CDC_TX_ANC0_IIR_COEFF_1_CTL:
	हाल CDC_TX_ANC0_IIR_COEFF_2_CTL:
	हाल CDC_TX_ANC0_FF_A_GAIN_CTL:
	हाल CDC_TX_ANC0_FF_B_GAIN_CTL:
	हाल CDC_TX_ANC0_FB_GAIN_CTL:
	हाल CDC_TX_INP_MUX_ADC_MUX0_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX0_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX1_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX1_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX2_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX2_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX3_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX3_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX4_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX4_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX5_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX5_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX6_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX6_CFG1:
	हाल CDC_TX_INP_MUX_ADC_MUX7_CFG0:
	हाल CDC_TX_INP_MUX_ADC_MUX7_CFG1:
	हाल CDC_TX0_TX_PATH_CTL:
	हाल CDC_TX0_TX_PATH_CFG0:
	हाल CDC_TX0_TX_PATH_CFG1:
	हाल CDC_TX0_TX_VOL_CTL:
	हाल CDC_TX0_TX_PATH_SEC0:
	हाल CDC_TX0_TX_PATH_SEC1:
	हाल CDC_TX0_TX_PATH_SEC2:
	हाल CDC_TX0_TX_PATH_SEC3:
	हाल CDC_TX0_TX_PATH_SEC4:
	हाल CDC_TX0_TX_PATH_SEC5:
	हाल CDC_TX0_TX_PATH_SEC6:
	हाल CDC_TX0_TX_PATH_SEC7:
	हाल CDC_TX1_TX_PATH_CTL:
	हाल CDC_TX1_TX_PATH_CFG0:
	हाल CDC_TX1_TX_PATH_CFG1:
	हाल CDC_TX1_TX_VOL_CTL:
	हाल CDC_TX1_TX_PATH_SEC0:
	हाल CDC_TX1_TX_PATH_SEC1:
	हाल CDC_TX1_TX_PATH_SEC2:
	हाल CDC_TX1_TX_PATH_SEC3:
	हाल CDC_TX1_TX_PATH_SEC4:
	हाल CDC_TX1_TX_PATH_SEC5:
	हाल CDC_TX1_TX_PATH_SEC6:
	हाल CDC_TX2_TX_PATH_CTL:
	हाल CDC_TX2_TX_PATH_CFG0:
	हाल CDC_TX2_TX_PATH_CFG1:
	हाल CDC_TX2_TX_VOL_CTL:
	हाल CDC_TX2_TX_PATH_SEC0:
	हाल CDC_TX2_TX_PATH_SEC1:
	हाल CDC_TX2_TX_PATH_SEC2:
	हाल CDC_TX2_TX_PATH_SEC3:
	हाल CDC_TX2_TX_PATH_SEC4:
	हाल CDC_TX2_TX_PATH_SEC5:
	हाल CDC_TX2_TX_PATH_SEC6:
	हाल CDC_TX3_TX_PATH_CTL:
	हाल CDC_TX3_TX_PATH_CFG0:
	हाल CDC_TX3_TX_PATH_CFG1:
	हाल CDC_TX3_TX_VOL_CTL:
	हाल CDC_TX3_TX_PATH_SEC0:
	हाल CDC_TX3_TX_PATH_SEC1:
	हाल CDC_TX3_TX_PATH_SEC2:
	हाल CDC_TX3_TX_PATH_SEC3:
	हाल CDC_TX3_TX_PATH_SEC4:
	हाल CDC_TX3_TX_PATH_SEC5:
	हाल CDC_TX3_TX_PATH_SEC6:
	हाल CDC_TX4_TX_PATH_CTL:
	हाल CDC_TX4_TX_PATH_CFG0:
	हाल CDC_TX4_TX_PATH_CFG1:
	हाल CDC_TX4_TX_VOL_CTL:
	हाल CDC_TX4_TX_PATH_SEC0:
	हाल CDC_TX4_TX_PATH_SEC1:
	हाल CDC_TX4_TX_PATH_SEC2:
	हाल CDC_TX4_TX_PATH_SEC3:
	हाल CDC_TX4_TX_PATH_SEC4:
	हाल CDC_TX4_TX_PATH_SEC5:
	हाल CDC_TX4_TX_PATH_SEC6:
	हाल CDC_TX5_TX_PATH_CTL:
	हाल CDC_TX5_TX_PATH_CFG0:
	हाल CDC_TX5_TX_PATH_CFG1:
	हाल CDC_TX5_TX_VOL_CTL:
	हाल CDC_TX5_TX_PATH_SEC0:
	हाल CDC_TX5_TX_PATH_SEC1:
	हाल CDC_TX5_TX_PATH_SEC2:
	हाल CDC_TX5_TX_PATH_SEC3:
	हाल CDC_TX5_TX_PATH_SEC4:
	हाल CDC_TX5_TX_PATH_SEC5:
	हाल CDC_TX5_TX_PATH_SEC6:
	हाल CDC_TX6_TX_PATH_CTL:
	हाल CDC_TX6_TX_PATH_CFG0:
	हाल CDC_TX6_TX_PATH_CFG1:
	हाल CDC_TX6_TX_VOL_CTL:
	हाल CDC_TX6_TX_PATH_SEC0:
	हाल CDC_TX6_TX_PATH_SEC1:
	हाल CDC_TX6_TX_PATH_SEC2:
	हाल CDC_TX6_TX_PATH_SEC3:
	हाल CDC_TX6_TX_PATH_SEC4:
	हाल CDC_TX6_TX_PATH_SEC5:
	हाल CDC_TX6_TX_PATH_SEC6:
	हाल CDC_TX7_TX_PATH_CTL:
	हाल CDC_TX7_TX_PATH_CFG0:
	हाल CDC_TX7_TX_PATH_CFG1:
	हाल CDC_TX7_TX_VOL_CTL:
	हाल CDC_TX7_TX_PATH_SEC0:
	हाल CDC_TX7_TX_PATH_SEC1:
	हाल CDC_TX7_TX_PATH_SEC2:
	हाल CDC_TX7_TX_PATH_SEC3:
	हाल CDC_TX7_TX_PATH_SEC4:
	हाल CDC_TX7_TX_PATH_SEC5:
	हाल CDC_TX7_TX_PATH_SEC6:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tx_regmap_config = अणु
	.name = "tx_macro",
	.reg_bits = 16,
	.val_bits = 32,
	.reg_stride = 4,
	.cache_type = REGCACHE_FLAT,
	.max_रेजिस्टर = TX_MAX_OFFSET,
	.reg_शेषs = tx_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tx_शेषs),
	.ग_लिखोable_reg = tx_is_rw_रेजिस्टर,
	.अस्थिर_reg = tx_is_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = tx_is_rw_रेजिस्टर,
पूर्ण;

अटल पूर्णांक tx_macro_mclk_enable(काष्ठा tx_macro *tx,
				bool mclk_enable)
अणु
	काष्ठा regmap *regmap = tx->regmap;

	अगर (mclk_enable) अणु
		अगर (tx->tx_mclk_users == 0) अणु
			/* 9.6MHz MCLK, set value 0x00 अगर other frequency */
			regmap_update_bits(regmap, CDC_TX_TOP_CSR_FREQ_MCLK, 0x01, 0x01);
			regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_MCLK_CONTROL,
					   CDC_TX_MCLK_EN_MASK,
					   CDC_TX_MCLK_ENABLE);
			regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_FS_CNT_CONTROL,
					   CDC_TX_FS_CNT_EN_MASK,
					   CDC_TX_FS_CNT_ENABLE);
			regcache_mark_dirty(regmap);
			regcache_sync(regmap);
		पूर्ण
		tx->tx_mclk_users++;
	पूर्ण अन्यथा अणु
		अगर (tx->tx_mclk_users <= 0) अणु
			dev_err(tx->dev, "clock already disabled\n");
			tx->tx_mclk_users = 0;
			जाओ निकास;
		पूर्ण
		tx->tx_mclk_users--;
		अगर (tx->tx_mclk_users == 0) अणु
			regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_FS_CNT_CONTROL,
					   CDC_TX_FS_CNT_EN_MASK, 0x0);
			regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_MCLK_CONTROL,
					   CDC_TX_MCLK_EN_MASK, 0x0);
		पूर्ण
	पूर्ण
निकास:
	वापस 0;
पूर्ण

अटल bool is_amic_enabled(काष्ठा snd_soc_component *component, पूर्णांक decimator)
अणु
	u16 adc_mux_reg, adc_reg, adc_n;

	adc_mux_reg = CDC_TX_INP_MUX_ADC_MUXn_CFG1(decimator);

	अगर (snd_soc_component_पढ़ो(component, adc_mux_reg) & SWR_MIC) अणु
		adc_reg = CDC_TX_INP_MUX_ADC_MUXn_CFG0(decimator);
		adc_n = snd_soc_component_पढ़ो_field(component, adc_reg,
					     CDC_TX_MACRO_SWR_MIC_MUX_SEL_MASK);
		अगर (adc_n < TX_ADC_MAX)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम tx_macro_tx_hpf_corner_freq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *hpf_delayed_work;
	काष्ठा hpf_work *hpf_work;
	काष्ठा tx_macro *tx;
	काष्ठा snd_soc_component *component;
	u16 dec_cfg_reg, hpf_gate_reg;
	u8 hpf_cut_off_freq;

	hpf_delayed_work = to_delayed_work(work);
	hpf_work = container_of(hpf_delayed_work, काष्ठा hpf_work, dwork);
	tx = hpf_work->tx;
	component = tx->component;
	hpf_cut_off_freq = hpf_work->hpf_cut_off_freq;

	dec_cfg_reg = CDC_TXn_TX_PATH_CFG0(hpf_work->decimator);
	hpf_gate_reg = CDC_TXn_TX_PATH_SEC2(hpf_work->decimator);

	अगर (is_amic_enabled(component, hpf_work->decimator)) अणु
		snd_soc_component_ग_लिखो_field(component,
				dec_cfg_reg,
				CDC_TXn_HPF_CUT_FREQ_MASK,
				hpf_cut_off_freq);
		snd_soc_component_update_bits(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x02);
		snd_soc_component_update_bits(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x01);
	पूर्ण अन्यथा अणु
		snd_soc_component_ग_लिखो_field(component, dec_cfg_reg,
					      CDC_TXn_HPF_CUT_FREQ_MASK,
					      hpf_cut_off_freq);
		snd_soc_component_ग_लिखो_field(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK, 0x1);
		/* Minimum 1 clk cycle delay is required as per HW spec */
		usleep_range(1000, 1010);
		snd_soc_component_ग_लिखो_field(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK, 0x0);
	पूर्ण
पूर्ण

अटल व्योम tx_macro_mute_update_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tx_mute_work *tx_mute_dwork;
	काष्ठा snd_soc_component *component;
	काष्ठा tx_macro *tx;
	काष्ठा delayed_work *delayed_work;
	u8 decimator;

	delayed_work = to_delayed_work(work);
	tx_mute_dwork = container_of(delayed_work, काष्ठा tx_mute_work, dwork);
	tx = tx_mute_dwork->tx;
	component = tx->component;
	decimator = tx_mute_dwork->decimator;

	snd_soc_component_ग_लिखो_field(component, CDC_TXn_TX_PATH_CTL(decimator),
				      CDC_TXn_PGA_MUTE_MASK, 0x0);
पूर्ण

अटल पूर्णांक tx_macro_mclk_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		tx_macro_mclk_enable(tx, true);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		tx_macro_mclk_enable(tx, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_put_dec_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val, dmic;
	u16 mic_sel_reg;
	u16 dmic_clk_reg;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	val = ucontrol->value.क्रमागतerated.item[0];

	चयन (e->reg) अणु
	हाल CDC_TX_INP_MUX_ADC_MUX0_CFG0:
		mic_sel_reg = CDC_TX0_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX1_CFG0:
		mic_sel_reg = CDC_TX1_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX2_CFG0:
		mic_sel_reg = CDC_TX2_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX3_CFG0:
		mic_sel_reg = CDC_TX3_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX4_CFG0:
		mic_sel_reg = CDC_TX4_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX5_CFG0:
		mic_sel_reg = CDC_TX5_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX6_CFG0:
		mic_sel_reg = CDC_TX6_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_TX_INP_MUX_ADC_MUX7_CFG0:
		mic_sel_reg = CDC_TX7_TX_PATH_CFG0;
		अवरोध;
	पूर्ण

	अगर (val != 0) अणु
		अगर (val < 5) अणु
			snd_soc_component_ग_लिखो_field(component, mic_sel_reg,
						      CDC_TXn_ADC_DMIC_SEL_MASK, 0);
		पूर्ण अन्यथा अणु
			snd_soc_component_ग_लिखो_field(component, mic_sel_reg,
						      CDC_TXn_ADC_DMIC_SEL_MASK, 1);
			dmic = TX_ADC_TO_DMIC(val);
			dmic_clk_reg = CDC_TX_TOP_CSR_SWR_DMICn_CTL(dmic);
			snd_soc_component_ग_लिखो_field(component, dmic_clk_reg,
						CDC_TX_SWR_DMIC_CLK_SEL_MASK,
						tx->dmic_clk_भाग);
		पूर्ण
	पूर्ण

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

अटल पूर्णांक tx_macro_tx_mixer_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_mixer_control *mc = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	u32 dai_id = widget->shअगरt;
	u32 dec_id = mc->shअगरt;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	अगर (test_bit(dec_id, &tx->active_ch_mask[dai_id]))
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_tx_mixer_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	काष्ठा snd_soc_dapm_update *update = शून्य;
	काष्ठा soc_mixer_control *mc = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	u32 dai_id = widget->shअगरt;
	u32 dec_id = mc->shअगरt;
	u32 enable = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	अगर (enable) अणु
		set_bit(dec_id, &tx->active_ch_mask[dai_id]);
		tx->active_ch_cnt[dai_id]++;
		tx->active_decimator[dai_id] = dec_id;
	पूर्ण अन्यथा अणु
		tx->active_ch_cnt[dai_id]--;
		clear_bit(dec_id, &tx->active_ch_mask[dai_id]);
		tx->active_decimator[dai_id] = -1;
	पूर्ण
	snd_soc_dapm_mixer_update_घातer(widget->dapm, kcontrol, enable, update);

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_enable_dec(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक decimator;
	u16 tx_vol_ctl_reg, dec_cfg_reg, hpf_gate_reg, tx_gain_ctl_reg;
	u8 hpf_cut_off_freq;
	पूर्णांक hpf_delay = TX_MACRO_DMIC_HPF_DELAY_MS;
	पूर्णांक unmute_delay = TX_MACRO_DMIC_UNMUTE_DELAY_MS;
	u16 adc_mux_reg, adc_reg, adc_n, dmic;
	u16 dmic_clk_reg;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	decimator = w->shअगरt;
	tx_vol_ctl_reg = CDC_TXn_TX_PATH_CTL(decimator);
	hpf_gate_reg = CDC_TXn_TX_PATH_SEC2(decimator);
	dec_cfg_reg = CDC_TXn_TX_PATH_CFG0(decimator);
	tx_gain_ctl_reg = CDC_TXn_TX_VOL_CTL(decimator);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		adc_mux_reg = CDC_TX_INP_MUX_ADC_MUXn_CFG1(decimator);
		अगर (snd_soc_component_पढ़ो(component, adc_mux_reg) & SWR_MIC) अणु
			adc_reg = CDC_TX_INP_MUX_ADC_MUXn_CFG0(decimator);
			adc_n = snd_soc_component_पढ़ो(component, adc_reg) &
				CDC_TX_MACRO_SWR_MIC_MUX_SEL_MASK;
			अगर (adc_n >= TX_ADC_MAX) अणु
				dmic = TX_ADC_TO_DMIC(adc_n);
				dmic_clk_reg = CDC_TX_TOP_CSR_SWR_DMICn_CTL(dmic);

				snd_soc_component_ग_लिखो_field(component, dmic_clk_reg,
							CDC_TX_SWR_DMIC_CLK_SEL_MASK,
							tx->dmic_clk_भाग);
			पूर्ण
		पूर्ण
		snd_soc_component_ग_लिखो_field(component, dec_cfg_reg,
					      CDC_TXn_ADC_MODE_MASK,
					      tx->dec_mode[decimator]);
		/* Enable TX PGA Mute */
		snd_soc_component_ग_लिखो_field(component, tx_vol_ctl_reg,
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो_field(component, tx_vol_ctl_reg,
					     CDC_TXn_CLK_EN_MASK, 0x1);
		अगर (!is_amic_enabled(component, decimator)) अणु
			snd_soc_component_update_bits(component, hpf_gate_reg, 0x01, 0x00);
			/* Minimum 1 clk cycle delay is required as per HW spec */
			usleep_range(1000, 1010);
		पूर्ण
		hpf_cut_off_freq = snd_soc_component_पढ़ो_field(component, dec_cfg_reg,
								CDC_TXn_HPF_CUT_FREQ_MASK);

		tx->tx_hpf_work[decimator].hpf_cut_off_freq =
						hpf_cut_off_freq;

		अगर (hpf_cut_off_freq != CF_MIN_3DB_150HZ)
			snd_soc_component_ग_लिखो_field(component, dec_cfg_reg,
						      CDC_TXn_HPF_CUT_FREQ_MASK,
						      CF_MIN_3DB_150HZ);

		अगर (is_amic_enabled(component, decimator)) अणु
			hpf_delay = TX_MACRO_AMIC_HPF_DELAY_MS;
			unmute_delay = TX_MACRO_AMIC_UNMUTE_DELAY_MS;
		पूर्ण
		/* schedule work queue to Remove Mute */
		queue_delayed_work(प्रणाली_मुक्तzable_wq,
				   &tx->tx_mute_dwork[decimator].dwork,
				   msecs_to_jअगरfies(unmute_delay));
		अगर (tx->tx_hpf_work[decimator].hpf_cut_off_freq != CF_MIN_3DB_150HZ) अणु
			queue_delayed_work(प्रणाली_मुक्तzable_wq,
				&tx->tx_hpf_work[decimator].dwork,
				msecs_to_jअगरfies(hpf_delay));
			snd_soc_component_update_bits(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x02);
			अगर (!is_amic_enabled(component, decimator))
				snd_soc_component_update_bits(component, hpf_gate_reg,
						      CDC_TXn_HPF_F_CHANGE_MASK |
						      CDC_TXn_HPF_ZERO_GATE_MASK,
						      0x00);
			snd_soc_component_update_bits(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x01);

			/*
			 * 6ms delay is required as per HW spec
			 */
			usleep_range(6000, 6010);
		पूर्ण
		/* apply gain after decimator is enabled */
		snd_soc_component_ग_लिखो(component, tx_gain_ctl_reg,
			      snd_soc_component_पढ़ो(component,
					tx_gain_ctl_reg));
		अगर (tx->bcs_enable) अणु
			snd_soc_component_update_bits(component, dec_cfg_reg,
					0x01, 0x01);
			tx->bcs_clk_en = true;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		hpf_cut_off_freq =
			tx->tx_hpf_work[decimator].hpf_cut_off_freq;
		snd_soc_component_ग_लिखो_field(component, tx_vol_ctl_reg,
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
		अगर (cancel_delayed_work_sync(
		    &tx->tx_hpf_work[decimator].dwork)) अणु
			अगर (hpf_cut_off_freq != CF_MIN_3DB_150HZ) अणु
				snd_soc_component_ग_लिखो_field(
						component, dec_cfg_reg,
						CDC_TXn_HPF_CUT_FREQ_MASK,
						hpf_cut_off_freq);
				अगर (is_amic_enabled(component, decimator))
					snd_soc_component_update_bits(component,
					      hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x02);
				अन्यथा
					snd_soc_component_update_bits(component,
					      hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x03);

				/*
				 * Minimum 1 clk cycle delay is required
				 * as per HW spec
				 */
				usleep_range(1000, 1010);
				snd_soc_component_update_bits(component, hpf_gate_reg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZERO_GATE_MASK,
					      0x1);
			पूर्ण
		पूर्ण
		cancel_delayed_work_sync(&tx->tx_mute_dwork[decimator].dwork);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो_field(component, tx_vol_ctl_reg,
					      CDC_TXn_CLK_EN_MASK, 0x0);
		snd_soc_component_ग_लिखो_field(component, dec_cfg_reg,
					      CDC_TXn_ADC_MODE_MASK, 0x0);
		snd_soc_component_ग_लिखो_field(component, tx_vol_ctl_reg,
					      CDC_TXn_PGA_MUTE_MASK, 0x0);
		अगर (tx->bcs_enable) अणु
			snd_soc_component_ग_लिखो_field(component, dec_cfg_reg,
						      CDC_TXn_PH_EN_MASK, 0x0);
			snd_soc_component_ग_लिखो_field(component,
						      CDC_TX0_TX_PATH_SEC7,
						      CDC_TX0_MBHC_CTL_EN_MASK,
						      0x0);
			tx->bcs_clk_en = false;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_dec_mode_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	पूर्णांक path = e->shअगरt_l;

	ucontrol->value.पूर्णांकeger.value[0] = tx->dec_mode[path];

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_dec_mode_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	पूर्णांक path = e->shअगरt_l;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	tx->dec_mode[path] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_get_bcs(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = tx->bcs_enable;

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_set_bcs(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	tx->bcs_enable = value;

	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u32 decimator, sample_rate;
	पूर्णांक tx_fs_rate;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	sample_rate = params_rate(params);
	चयन (sample_rate) अणु
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
		dev_err(component->dev, "%s: Invalid TX sample rate: %d\n",
			__func__, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	क्रम_each_set_bit(decimator, &tx->active_ch_mask[dai->id], TX_MACRO_DEC_MAX)
		snd_soc_component_update_bits(component, CDC_TXn_TX_PATH_CTL(decimator),
					      CDC_TXn_PCM_RATE_MASK,
					      tx_fs_rate);
	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_get_channel_map(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				    अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);

	चयन (dai->id) अणु
	हाल TX_MACRO_AIF1_CAP:
	हाल TX_MACRO_AIF2_CAP:
	हाल TX_MACRO_AIF3_CAP:
		*tx_slot = tx->active_ch_mask[dai->id];
		*tx_num = tx->active_ch_cnt[dai->id];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tx_macro_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(component);
	u16 decimator;

	decimator = tx->active_decimator[dai->id];

	अगर (mute)
		snd_soc_component_ग_लिखो_field(component,
					      CDC_TXn_TX_PATH_CTL(decimator),
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
	अन्यथा
		snd_soc_component_update_bits(component,
					      CDC_TXn_TX_PATH_CTL(decimator),
					      CDC_TXn_PGA_MUTE_MASK, 0x0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tx_macro_dai_ops = अणु
	.hw_params = tx_macro_hw_params,
	.get_channel_map = tx_macro_get_channel_map,
	.mute_stream = tx_macro_digital_mute,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tx_macro_dai[] = अणु
	अणु
		.name = "tx_macro_tx1",
		.id = TX_MACRO_AIF1_CAP,
		.capture = अणु
			.stream_name = "TX_AIF1 Capture",
			.rates = TX_MACRO_RATES,
			.क्रमmats = TX_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &tx_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "tx_macro_tx2",
		.id = TX_MACRO_AIF2_CAP,
		.capture = अणु
			.stream_name = "TX_AIF2 Capture",
			.rates = TX_MACRO_RATES,
			.क्रमmats = TX_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &tx_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "tx_macro_tx3",
		.id = TX_MACRO_AIF3_CAP,
		.capture = अणु
			.stream_name = "TX_AIF3 Capture",
			.rates = TX_MACRO_RATES,
			.क्रमmats = TX_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &tx_macro_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_mux_text[] = अणु
	"MSM_DMIC", "SWR_MIC", "ANC_FB_TUNE1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(tx_dec0_क्रमागत, CDC_TX_INP_MUX_ADC_MUX0_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec1_क्रमागत, CDC_TX_INP_MUX_ADC_MUX1_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec2_क्रमागत, CDC_TX_INP_MUX_ADC_MUX2_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec3_क्रमागत, CDC_TX_INP_MUX_ADC_MUX3_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec4_क्रमागत, CDC_TX_INP_MUX_ADC_MUX4_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec5_क्रमागत, CDC_TX_INP_MUX_ADC_MUX5_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec6_क्रमागत, CDC_TX_INP_MUX_ADC_MUX6_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(tx_dec7_क्रमागत, CDC_TX_INP_MUX_ADC_MUX7_CFG1,
		   0, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new tx_dec0_mux = SOC_DAPM_ENUM("tx_dec0", tx_dec0_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec1_mux = SOC_DAPM_ENUM("tx_dec1", tx_dec1_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec2_mux = SOC_DAPM_ENUM("tx_dec2", tx_dec2_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec3_mux = SOC_DAPM_ENUM("tx_dec3", tx_dec3_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec4_mux = SOC_DAPM_ENUM("tx_dec4", tx_dec4_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec5_mux = SOC_DAPM_ENUM("tx_dec5", tx_dec5_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec6_mux = SOC_DAPM_ENUM("tx_dec6", tx_dec6_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_dec7_mux = SOC_DAPM_ENUM("tx_dec7", tx_dec7_क्रमागत);

अटल स्थिर अक्षर * स्थिर smic_mux_text[] = अणु
	"ZERO", "ADC0", "ADC1", "ADC2", "ADC3", "SWR_DMIC0",
	"SWR_DMIC1", "SWR_DMIC2", "SWR_DMIC3", "SWR_DMIC4",
	"SWR_DMIC5", "SWR_DMIC6", "SWR_DMIC7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(tx_smic0_क्रमागत, CDC_TX_INP_MUX_ADC_MUX0_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic1_क्रमागत, CDC_TX_INP_MUX_ADC_MUX1_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic2_क्रमागत, CDC_TX_INP_MUX_ADC_MUX2_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic3_क्रमागत, CDC_TX_INP_MUX_ADC_MUX3_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic4_क्रमागत, CDC_TX_INP_MUX_ADC_MUX4_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic5_क्रमागत, CDC_TX_INP_MUX_ADC_MUX5_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic6_क्रमागत, CDC_TX_INP_MUX_ADC_MUX6_CFG0,
			0, smic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(tx_smic7_क्रमागत, CDC_TX_INP_MUX_ADC_MUX7_CFG0,
			0, smic_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new tx_smic0_mux = SOC_DAPM_ENUM_EXT("tx_smic0", tx_smic0_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic1_mux = SOC_DAPM_ENUM_EXT("tx_smic1", tx_smic1_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic2_mux = SOC_DAPM_ENUM_EXT("tx_smic2", tx_smic2_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic3_mux = SOC_DAPM_ENUM_EXT("tx_smic3", tx_smic3_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic4_mux = SOC_DAPM_ENUM_EXT("tx_smic4", tx_smic4_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic5_mux = SOC_DAPM_ENUM_EXT("tx_smic5", tx_smic5_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic6_mux = SOC_DAPM_ENUM_EXT("tx_smic6", tx_smic6_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new tx_smic7_mux = SOC_DAPM_ENUM_EXT("tx_smic7", tx_smic7_क्रमागत,
			snd_soc_dapm_get_क्रमागत_द्विगुन, tx_macro_put_dec_क्रमागत);

अटल स्थिर अक्षर * स्थिर dec_mode_mux_text[] = अणु
	"ADC_DEFAULT", "ADC_LOW_PWR", "ADC_HIGH_PERF",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत dec_mode_mux_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 1, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 2,  ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 3, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 4, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 5, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 6, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 7, ARRAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tx_aअगर1_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, TX_MACRO_DEC0, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, TX_MACRO_DEC1, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, TX_MACRO_DEC2, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, TX_MACRO_DEC3, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, TX_MACRO_DEC4, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, TX_MACRO_DEC5, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, TX_MACRO_DEC6, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, TX_MACRO_DEC7, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tx_aअगर2_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, TX_MACRO_DEC0, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, TX_MACRO_DEC1, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, TX_MACRO_DEC2, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, TX_MACRO_DEC3, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, TX_MACRO_DEC4, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, TX_MACRO_DEC5, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, TX_MACRO_DEC6, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, TX_MACRO_DEC7, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tx_aअगर3_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, TX_MACRO_DEC0, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, TX_MACRO_DEC1, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, TX_MACRO_DEC2, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, TX_MACRO_DEC3, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, TX_MACRO_DEC4, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, TX_MACRO_DEC5, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, TX_MACRO_DEC6, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, TX_MACRO_DEC7, 1, 0,
			tx_macro_tx_mixer_get, tx_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tx_macro_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("TX_AIF1 CAP", "TX_AIF1 Capture", 0,
		SND_SOC_NOPM, TX_MACRO_AIF1_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("TX_AIF2 CAP", "TX_AIF2 Capture", 0,
		SND_SOC_NOPM, TX_MACRO_AIF2_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("TX_AIF3 CAP", "TX_AIF3 Capture", 0,
		SND_SOC_NOPM, TX_MACRO_AIF3_CAP, 0),

	SND_SOC_DAPM_MIXER("TX_AIF1_CAP Mixer", SND_SOC_NOPM, TX_MACRO_AIF1_CAP, 0,
		tx_aअगर1_cap_mixer, ARRAY_SIZE(tx_aअगर1_cap_mixer)),

	SND_SOC_DAPM_MIXER("TX_AIF2_CAP Mixer", SND_SOC_NOPM, TX_MACRO_AIF2_CAP, 0,
		tx_aअगर2_cap_mixer, ARRAY_SIZE(tx_aअगर2_cap_mixer)),

	SND_SOC_DAPM_MIXER("TX_AIF3_CAP Mixer", SND_SOC_NOPM, TX_MACRO_AIF3_CAP, 0,
		tx_aअगर3_cap_mixer, ARRAY_SIZE(tx_aअगर3_cap_mixer)),

	SND_SOC_DAPM_MUX("TX SMIC MUX0", SND_SOC_NOPM, 0, 0, &tx_smic0_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX1", SND_SOC_NOPM, 0, 0, &tx_smic1_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX2", SND_SOC_NOPM, 0, 0, &tx_smic2_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX3", SND_SOC_NOPM, 0, 0, &tx_smic3_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX4", SND_SOC_NOPM, 0, 0, &tx_smic4_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX5", SND_SOC_NOPM, 0, 0, &tx_smic5_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX6", SND_SOC_NOPM, 0, 0, &tx_smic6_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX7", SND_SOC_NOPM, 0, 0, &tx_smic7_mux),

	SND_SOC_DAPM_INPUT("TX SWR_ADC0"),
	SND_SOC_DAPM_INPUT("TX SWR_ADC1"),
	SND_SOC_DAPM_INPUT("TX SWR_ADC2"),
	SND_SOC_DAPM_INPUT("TX SWR_ADC3"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC0"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC1"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC2"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC3"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC4"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC5"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC6"),
	SND_SOC_DAPM_INPUT("TX SWR_DMIC7"),

	SND_SOC_DAPM_MUX_E("TX DEC0 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC0, 0,
			   &tx_dec0_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC1 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC1, 0,
			   &tx_dec1_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC2 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC2, 0,
			   &tx_dec2_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC3 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC3, 0,
			   &tx_dec3_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC4 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC4, 0,
			   &tx_dec4_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC5 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC5, 0,
			   &tx_dec5_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC6 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC6, 0,
			   &tx_dec6_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC7 MUX", SND_SOC_NOPM,
			   TX_MACRO_DEC7, 0,
			   &tx_dec7_mux, tx_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("TX_MCLK", 0, SND_SOC_NOPM, 0, 0,
	tx_macro_mclk_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("TX_SWR_CLK", 0, SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("VA_SWR_CLK", 0, SND_SOC_NOPM, 0, 0,
			शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tx_audio_map[] = अणु
	अणु"TX_AIF1 CAP", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX_AIF2 CAP", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX_AIF3 CAP", शून्य, "TX_MCLK"पूर्ण,

	अणु"TX_AIF1 CAP", शून्य, "TX_AIF1_CAP Mixer"पूर्ण,
	अणु"TX_AIF2 CAP", शून्य, "TX_AIF2_CAP Mixer"पूर्ण,
	अणु"TX_AIF3 CAP", शून्य, "TX_AIF3_CAP Mixer"पूर्ण,

	अणु"TX_AIF1_CAP Mixer", "DEC0", "TX DEC0 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC1", "TX DEC1 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC2", "TX DEC2 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC3", "TX DEC3 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC4", "TX DEC4 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC5", "TX DEC5 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC6", "TX DEC6 MUX"पूर्ण,
	अणु"TX_AIF1_CAP Mixer", "DEC7", "TX DEC7 MUX"पूर्ण,

	अणु"TX_AIF2_CAP Mixer", "DEC0", "TX DEC0 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC1", "TX DEC1 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC2", "TX DEC2 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC3", "TX DEC3 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC4", "TX DEC4 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC5", "TX DEC5 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC6", "TX DEC6 MUX"पूर्ण,
	अणु"TX_AIF2_CAP Mixer", "DEC7", "TX DEC7 MUX"पूर्ण,

	अणु"TX_AIF3_CAP Mixer", "DEC0", "TX DEC0 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC1", "TX DEC1 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC2", "TX DEC2 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC3", "TX DEC3 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC4", "TX DEC4 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC5", "TX DEC5 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC6", "TX DEC6 MUX"पूर्ण,
	अणु"TX_AIF3_CAP Mixer", "DEC7", "TX DEC7 MUX"पूर्ण,

	अणु"TX DEC0 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC1 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC2 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC3 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC4 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC5 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC6 MUX", शून्य, "TX_MCLK"पूर्ण,
	अणु"TX DEC7 MUX", शून्य, "TX_MCLK"पूर्ण,

	अणु"TX DEC0 MUX", "SWR_MIC", "TX SMIC MUX0"पूर्ण,
	अणु"TX SMIC MUX0", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX0", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX0", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX0", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX0", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX0", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC1 MUX", "SWR_MIC", "TX SMIC MUX1"पूर्ण,
	अणु"TX SMIC MUX1", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX1", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX1", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX1", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX1", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX1", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC2 MUX", "SWR_MIC", "TX SMIC MUX2"पूर्ण,
	अणु"TX SMIC MUX2", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX2", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX2", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX2", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX2", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX2", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC3 MUX", "SWR_MIC", "TX SMIC MUX3"पूर्ण,
	अणु"TX SMIC MUX3", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX3", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX3", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX3", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX3", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX3", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC4 MUX", "SWR_MIC", "TX SMIC MUX4"पूर्ण,
	अणु"TX SMIC MUX4", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX4", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX4", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX4", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX4", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX4", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC5 MUX", "SWR_MIC", "TX SMIC MUX5"पूर्ण,
	अणु"TX SMIC MUX5", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX5", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX5", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX5", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX5", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX5", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC6 MUX", "SWR_MIC", "TX SMIC MUX6"पूर्ण,
	अणु"TX SMIC MUX6", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX6", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX6", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX6", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX6", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX6", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,

	अणु"TX DEC7 MUX", "SWR_MIC", "TX SMIC MUX7"पूर्ण,
	अणु"TX SMIC MUX7", शून्य, "TX_SWR_CLK"पूर्ण,
	अणु"TX SMIC MUX7", "ADC0", "TX SWR_ADC0"पूर्ण,
	अणु"TX SMIC MUX7", "ADC1", "TX SWR_ADC1"पूर्ण,
	अणु"TX SMIC MUX7", "ADC2", "TX SWR_ADC2"पूर्ण,
	अणु"TX SMIC MUX7", "ADC3", "TX SWR_ADC3"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC0", "TX SWR_DMIC0"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC1", "TX SWR_DMIC1"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC2", "TX SWR_DMIC2"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC3", "TX SWR_DMIC3"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC4", "TX SWR_DMIC4"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC5", "TX SWR_DMIC5"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC6", "TX SWR_DMIC6"पूर्ण,
	अणु"TX SMIC MUX7", "SWR_DMIC7", "TX SWR_DMIC7"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tx_macro_snd_controls[] = अणु
	SOC_SINGLE_S8_TLV("TX_DEC0 Volume",
			  CDC_TX0_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC1 Volume",
			  CDC_TX1_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC2 Volume",
			  CDC_TX2_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC3 Volume",
			  CDC_TX3_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC4 Volume",
			  CDC_TX4_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC5 Volume",
			  CDC_TX5_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC6 Volume",
			  CDC_TX6_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("TX_DEC7 Volume",
			  CDC_TX7_TX_VOL_CTL,
			  -84, 40, digital_gain),

	SOC_ENUM_EXT("DEC0 MODE", dec_mode_mux_क्रमागत[0],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC1 MODE", dec_mode_mux_क्रमागत[1],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC2 MODE", dec_mode_mux_क्रमागत[2],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC3 MODE", dec_mode_mux_क्रमागत[3],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC4 MODE", dec_mode_mux_क्रमागत[4],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC5 MODE", dec_mode_mux_क्रमागत[5],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC6 MODE", dec_mode_mux_क्रमागत[6],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_ENUM_EXT("DEC7 MODE", dec_mode_mux_क्रमागत[7],
			tx_macro_dec_mode_get, tx_macro_dec_mode_put),

	SOC_SINGLE_EXT("DEC0_BCS Switch", SND_SOC_NOPM, 0, 1, 0,
		       tx_macro_get_bcs, tx_macro_set_bcs),
पूर्ण;

अटल पूर्णांक tx_macro_component_probe(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा tx_macro *tx = snd_soc_component_get_drvdata(comp);
	पूर्णांक i;

	snd_soc_component_init_regmap(comp, tx->regmap);

	क्रम (i = 0; i < NUM_DECIMATORS; i++) अणु
		tx->tx_hpf_work[i].tx = tx;
		tx->tx_hpf_work[i].decimator = i;
		INIT_DELAYED_WORK(&tx->tx_hpf_work[i].dwork,
			tx_macro_tx_hpf_corner_freq_callback);
	पूर्ण

	क्रम (i = 0; i < NUM_DECIMATORS; i++) अणु
		tx->tx_mute_dwork[i].tx = tx;
		tx->tx_mute_dwork[i].decimator = i;
		INIT_DELAYED_WORK(&tx->tx_mute_dwork[i].dwork,
			  tx_macro_mute_update_callback);
	पूर्ण
	tx->component = comp;

	snd_soc_component_update_bits(comp, CDC_TX0_TX_PATH_SEC7, 0x3F,
				      0x0A);

	वापस 0;
पूर्ण

अटल पूर्णांक swclk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tx_macro *tx = to_tx_macro(hw);
	काष्ठा regmap *regmap = tx->regmap;

	tx_macro_mclk_enable(tx, true);
	अगर (tx->reset_swr)
		regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_SWR_CONTROL,
				   CDC_TX_SWR_RESET_MASK,
				   CDC_TX_SWR_RESET_ENABLE);

	regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_SWR_CONTROL,
			   CDC_TX_SWR_CLK_EN_MASK,
			   CDC_TX_SWR_CLK_ENABLE);
	अगर (tx->reset_swr)
		regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_SWR_CONTROL,
				   CDC_TX_SWR_RESET_MASK, 0x0);
	tx->reset_swr = false;

	वापस 0;
पूर्ण

अटल व्योम swclk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tx_macro *tx = to_tx_macro(hw);
	काष्ठा regmap *regmap = tx->regmap;

	regmap_update_bits(regmap, CDC_TX_CLK_RST_CTRL_SWR_CONTROL,
			   CDC_TX_SWR_CLK_EN_MASK, 0x0);

	tx_macro_mclk_enable(tx, false);
पूर्ण

अटल पूर्णांक swclk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tx_macro *tx = to_tx_macro(hw);
	पूर्णांक ret, val;

	regmap_पढ़ो(tx->regmap, CDC_TX_CLK_RST_CTRL_SWR_CONTROL, &val);
	ret = val & BIT(0);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ swclk_recalc_rate(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate / 2;
पूर्ण

अटल स्थिर काष्ठा clk_ops swclk_gate_ops = अणु
	.prepare = swclk_gate_enable,
	.unprepare = swclk_gate_disable,
	.is_enabled = swclk_gate_is_enabled,
	.recalc_rate = swclk_recalc_rate,

पूर्ण;

अटल काष्ठा clk *tx_macro_रेजिस्टर_mclk_output(काष्ठा tx_macro *tx)
अणु
	काष्ठा device *dev = tx->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *parent_clk_name = शून्य;
	स्थिर अक्षर *clk_name = "lpass-tx-mclk";
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	parent_clk_name = __clk_get_name(tx->clks[2].clk);

	init.name = clk_name;
	init.ops = &swclk_gate_ops;
	init.flags = 0;
	init.parent_names = &parent_clk_name;
	init.num_parents = 1;
	tx->hw.init = &init;
	hw = &tx->hw;
	ret = clk_hw_रेजिस्टर(tx->dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	of_clk_add_provider(np, of_clk_src_simple_get, hw->clk);

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver tx_macro_component_drv = अणु
	.name = "RX-MACRO",
	.probe = tx_macro_component_probe,
	.controls = tx_macro_snd_controls,
	.num_controls = ARRAY_SIZE(tx_macro_snd_controls),
	.dapm_widमाला_लो = tx_macro_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tx_macro_dapm_widमाला_लो),
	.dapm_routes = tx_audio_map,
	.num_dapm_routes = ARRAY_SIZE(tx_audio_map),
पूर्ण;

अटल पूर्णांक tx_macro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tx_macro *tx;
	व्योम __iomem *base;
	पूर्णांक ret;

	tx = devm_kzalloc(dev, माप(*tx), GFP_KERNEL);
	अगर (!tx)
		वापस -ENOMEM;

	tx->clks[0].id = "macro";
	tx->clks[1].id = "dcodec";
	tx->clks[2].id = "mclk";
	tx->clks[3].id = "npl";
	tx->clks[4].id = "fsgen";

	ret = devm_clk_bulk_get(dev, TX_NUM_CLKS_MAX, tx->clks);
	अगर (ret) अणु
		dev_err(dev, "Error getting RX Clocks (%d)\n", ret);
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	tx->regmap = devm_regmap_init_mmio(dev, base, &tx_regmap_config);

	dev_set_drvdata(dev, tx);

	tx->reset_swr = true;
	tx->dev = dev;

	/* set MCLK and NPL rates */
	clk_set_rate(tx->clks[2].clk, MCLK_FREQ);
	clk_set_rate(tx->clks[3].clk, 2 * MCLK_FREQ);

	ret = clk_bulk_prepare_enable(TX_NUM_CLKS_MAX, tx->clks);
	अगर (ret)
		वापस ret;

	tx_macro_रेजिस्टर_mclk_output(tx);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &tx_macro_component_drv,
					      tx_macro_dai,
					      ARRAY_SIZE(tx_macro_dai));
	अगर (ret)
		जाओ err;
	वापस ret;
err:
	clk_bulk_disable_unprepare(TX_NUM_CLKS_MAX, tx->clks);

	वापस ret;
पूर्ण

अटल पूर्णांक tx_macro_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tx_macro *tx = dev_get_drvdata(&pdev->dev);

	of_clk_del_provider(pdev->dev.of_node);

	clk_bulk_disable_unprepare(TX_NUM_CLKS_MAX, tx->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tx_macro_dt_match[] = अणु
	अणु .compatible = "qcom,sm8250-lpass-tx-macro" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tx_macro_dt_match);
अटल काष्ठा platक्रमm_driver tx_macro_driver = अणु
	.driver = अणु
		.name = "tx_macro",
		.of_match_table = tx_macro_dt_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tx_macro_probe,
	.हटाओ = tx_macro_हटाओ,
पूर्ण;

module_platक्रमm_driver(tx_macro_driver);

MODULE_DESCRIPTION("TX macro driver");
MODULE_LICENSE("GPL");
