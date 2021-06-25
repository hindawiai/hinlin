<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

/* VA macro रेजिस्टरs */
#घोषणा CDC_VA_CLK_RST_CTRL_MCLK_CONTROL	(0x0000)
#घोषणा CDC_VA_MCLK_CONTROL_EN			BIT(0)
#घोषणा CDC_VA_CLK_RST_CTRL_FS_CNT_CONTROL	(0x0004)
#घोषणा CDC_VA_FS_CONTROL_EN			BIT(0)
#घोषणा CDC_VA_CLK_RST_CTRL_SWR_CONTROL		(0x0008)
#घोषणा CDC_VA_TOP_CSR_TOP_CFG0			(0x0080)
#घोषणा CDC_VA_FS_BROADCAST_EN			BIT(1)
#घोषणा CDC_VA_TOP_CSR_DMIC0_CTL		(0x0084)
#घोषणा CDC_VA_TOP_CSR_DMIC1_CTL		(0x0088)
#घोषणा CDC_VA_TOP_CSR_DMIC2_CTL		(0x008C)
#घोषणा CDC_VA_TOP_CSR_DMIC3_CTL		(0x0090)
#घोषणा CDC_VA_DMIC_EN_MASK			BIT(0)
#घोषणा CDC_VA_DMIC_ENABLE			BIT(0)
#घोषणा CDC_VA_DMIC_CLK_SEL_MASK		GENMASK(3, 1)
#घोषणा CDC_VA_DMIC_CLK_SEL_SHFT		1
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV0		0x0
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV1		0x2
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV2		0x4
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV3		0x6
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV4		0x8
#घोषणा CDC_VA_DMIC_CLK_SEL_DIV5		0xa
#घोषणा CDC_VA_TOP_CSR_DMIC_CFG			(0x0094)
#घोषणा CDC_VA_RESET_ALL_DMICS_MASK		BIT(7)
#घोषणा CDC_VA_RESET_ALL_DMICS_RESET		BIT(7)
#घोषणा CDC_VA_RESET_ALL_DMICS_DISABLE		0
#घोषणा CDC_VA_DMIC3_FREQ_CHANGE_MASK		BIT(3)
#घोषणा CDC_VA_DMIC3_FREQ_CHANGE_EN		BIT(3)
#घोषणा CDC_VA_DMIC2_FREQ_CHANGE_MASK		BIT(2)
#घोषणा CDC_VA_DMIC2_FREQ_CHANGE_EN		BIT(2)
#घोषणा CDC_VA_DMIC1_FREQ_CHANGE_MASK		BIT(1)
#घोषणा CDC_VA_DMIC1_FREQ_CHANGE_EN		BIT(1)
#घोषणा CDC_VA_DMIC0_FREQ_CHANGE_MASK		BIT(0)
#घोषणा CDC_VA_DMIC0_FREQ_CHANGE_EN		BIT(0)
#घोषणा CDC_VA_DMIC_FREQ_CHANGE_DISABLE		0
#घोषणा CDC_VA_TOP_CSR_DEBUG_BUS		(0x009C)
#घोषणा CDC_VA_TOP_CSR_DEBUG_EN			(0x00A0)
#घोषणा CDC_VA_TOP_CSR_TX_I2S_CTL		(0x00A4)
#घोषणा CDC_VA_TOP_CSR_I2S_CLK			(0x00A8)
#घोषणा CDC_VA_TOP_CSR_I2S_RESET		(0x00AC)
#घोषणा CDC_VA_TOP_CSR_CORE_ID_0		(0x00C0)
#घोषणा CDC_VA_TOP_CSR_CORE_ID_1		(0x00C4)
#घोषणा CDC_VA_TOP_CSR_CORE_ID_2		(0x00C8)
#घोषणा CDC_VA_TOP_CSR_CORE_ID_3		(0x00CC)
#घोषणा CDC_VA_TOP_CSR_SWR_MIC_CTL0		(0x00D0)
#घोषणा CDC_VA_TOP_CSR_SWR_MIC_CTL1		(0x00D4)
#घोषणा CDC_VA_TOP_CSR_SWR_MIC_CTL2		(0x00D8)
#घोषणा CDC_VA_TOP_CSR_SWR_CTRL			(0x00DC)
#घोषणा CDC_VA_INP_MUX_ADC_MUX0_CFG0		(0x0100)
#घोषणा CDC_VA_INP_MUX_ADC_MUX0_CFG1		(0x0104)
#घोषणा CDC_VA_INP_MUX_ADC_MUX1_CFG0		(0x0108)
#घोषणा CDC_VA_INP_MUX_ADC_MUX1_CFG1		(0x010C)
#घोषणा CDC_VA_INP_MUX_ADC_MUX2_CFG0		(0x0110)
#घोषणा CDC_VA_INP_MUX_ADC_MUX2_CFG1		(0x0114)
#घोषणा CDC_VA_INP_MUX_ADC_MUX3_CFG0		(0x0118)
#घोषणा CDC_VA_INP_MUX_ADC_MUX3_CFG1		(0x011C)
#घोषणा CDC_VA_TX0_TX_PATH_CTL			(0x0400)
#घोषणा CDC_VA_TX_PATH_CLK_EN_MASK		BIT(5)
#घोषणा CDC_VA_TX_PATH_CLK_EN			BIT(5)
#घोषणा CDC_VA_TX_PATH_CLK_DISABLE		0
#घोषणा CDC_VA_TX_PATH_PGA_MUTE_EN_MASK		BIT(4)
#घोषणा CDC_VA_TX_PATH_PGA_MUTE_EN		BIT(4)
#घोषणा CDC_VA_TX_PATH_PGA_MUTE_DISABLE		0
#घोषणा CDC_VA_TX0_TX_PATH_CFG0			(0x0404)
#घोषणा CDC_VA_ADC_MODE_MASK			GENMASK(2, 1)
#घोषणा CDC_VA_ADC_MODE_SHIFT			1
#घोषणा  TX_HPF_CUT_OFF_FREQ_MASK		GENMASK(6, 5)
#घोषणा  CF_MIN_3DB_4HZ			0x0
#घोषणा  CF_MIN_3DB_75HZ		0x1
#घोषणा  CF_MIN_3DB_150HZ		0x2
#घोषणा CDC_VA_TX0_TX_PATH_CFG1			(0x0408)
#घोषणा CDC_VA_TX0_TX_VOL_CTL			(0x040C)
#घोषणा CDC_VA_TX0_TX_PATH_SEC0			(0x0410)
#घोषणा CDC_VA_TX0_TX_PATH_SEC1			(0x0414)
#घोषणा CDC_VA_TX0_TX_PATH_SEC2			(0x0418)
#घोषणा CDC_VA_TX_HPF_CUTOFF_FREQ_CHANGE_MASK	BIT(1)
#घोषणा CDC_VA_TX_HPF_CUTOFF_FREQ_CHANGE_REQ	BIT(1)
#घोषणा CDC_VA_TX_HPF_ZERO_GATE_MASK		BIT(0)
#घोषणा CDC_VA_TX_HPF_ZERO_NO_GATE		BIT(0)
#घोषणा CDC_VA_TX_HPF_ZERO_GATE			0
#घोषणा CDC_VA_TX0_TX_PATH_SEC3			(0x041C)
#घोषणा CDC_VA_TX0_TX_PATH_SEC4			(0x0420)
#घोषणा CDC_VA_TX0_TX_PATH_SEC5			(0x0424)
#घोषणा CDC_VA_TX0_TX_PATH_SEC6			(0x0428)
#घोषणा CDC_VA_TX0_TX_PATH_SEC7			(0x042C)
#घोषणा CDC_VA_TX1_TX_PATH_CTL			(0x0480)
#घोषणा CDC_VA_TX1_TX_PATH_CFG0			(0x0484)
#घोषणा CDC_VA_TX1_TX_PATH_CFG1			(0x0488)
#घोषणा CDC_VA_TX1_TX_VOL_CTL			(0x048C)
#घोषणा CDC_VA_TX1_TX_PATH_SEC0			(0x0490)
#घोषणा CDC_VA_TX1_TX_PATH_SEC1			(0x0494)
#घोषणा CDC_VA_TX1_TX_PATH_SEC2			(0x0498)
#घोषणा CDC_VA_TX1_TX_PATH_SEC3			(0x049C)
#घोषणा CDC_VA_TX1_TX_PATH_SEC4			(0x04A0)
#घोषणा CDC_VA_TX1_TX_PATH_SEC5			(0x04A4)
#घोषणा CDC_VA_TX1_TX_PATH_SEC6			(0x04A8)
#घोषणा CDC_VA_TX2_TX_PATH_CTL			(0x0500)
#घोषणा CDC_VA_TX2_TX_PATH_CFG0			(0x0504)
#घोषणा CDC_VA_TX2_TX_PATH_CFG1			(0x0508)
#घोषणा CDC_VA_TX2_TX_VOL_CTL			(0x050C)
#घोषणा CDC_VA_TX2_TX_PATH_SEC0			(0x0510)
#घोषणा CDC_VA_TX2_TX_PATH_SEC1			(0x0514)
#घोषणा CDC_VA_TX2_TX_PATH_SEC2			(0x0518)
#घोषणा CDC_VA_TX2_TX_PATH_SEC3			(0x051C)
#घोषणा CDC_VA_TX2_TX_PATH_SEC4			(0x0520)
#घोषणा CDC_VA_TX2_TX_PATH_SEC5			(0x0524)
#घोषणा CDC_VA_TX2_TX_PATH_SEC6			(0x0528)
#घोषणा CDC_VA_TX3_TX_PATH_CTL			(0x0580)
#घोषणा CDC_VA_TX3_TX_PATH_CFG0			(0x0584)
#घोषणा CDC_VA_TX_PATH_ADC_DMIC_SEL_MASK	BIT(7)
#घोषणा CDC_VA_TX_PATH_ADC_DMIC_SEL_DMIC	BIT(7)
#घोषणा CDC_VA_TX_PATH_ADC_DMIC_SEL_ADC		0
#घोषणा CDC_VA_TX3_TX_PATH_CFG1			(0x0588)
#घोषणा CDC_VA_TX3_TX_VOL_CTL			(0x058C)
#घोषणा CDC_VA_TX3_TX_PATH_SEC0			(0x0590)
#घोषणा CDC_VA_TX3_TX_PATH_SEC1			(0x0594)
#घोषणा CDC_VA_TX3_TX_PATH_SEC2			(0x0598)
#घोषणा CDC_VA_TX3_TX_PATH_SEC3			(0x059C)
#घोषणा CDC_VA_TX3_TX_PATH_SEC4			(0x05A0)
#घोषणा CDC_VA_TX3_TX_PATH_SEC5			(0x05A4)
#घोषणा CDC_VA_TX3_TX_PATH_SEC6			(0x05A8)

#घोषणा VA_MAX_OFFSET				(0x07A8)

#घोषणा VA_MACRO_NUM_DECIMATORS 4
#घोषणा VA_MACRO_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
#घोषणा VA_MACRO_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
		SNDRV_PCM_FMTBIT_S24_LE |\
		SNDRV_PCM_FMTBIT_S24_3LE)

#घोषणा VA_MACRO_MCLK_FREQ 9600000
#घोषणा VA_MACRO_TX_PATH_OFFSET 0x80
#घोषणा VA_MACRO_SWR_MIC_MUX_SEL_MASK 0xF
#घोषणा VA_MACRO_ADC_MUX_CFG_OFFSET 0x8

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -8400, 100, -8400);

क्रमागत अणु
	VA_MACRO_AIF_INVALID = 0,
	VA_MACRO_AIF1_CAP,
	VA_MACRO_AIF2_CAP,
	VA_MACRO_AIF3_CAP,
	VA_MACRO_MAX_DAIS,
पूर्ण;

क्रमागत अणु
	VA_MACRO_DEC0,
	VA_MACRO_DEC1,
	VA_MACRO_DEC2,
	VA_MACRO_DEC3,
	VA_MACRO_DEC4,
	VA_MACRO_DEC5,
	VA_MACRO_DEC6,
	VA_MACRO_DEC7,
	VA_MACRO_DEC_MAX,
पूर्ण;

क्रमागत अणु
	VA_MACRO_CLK_DIV_2,
	VA_MACRO_CLK_DIV_3,
	VA_MACRO_CLK_DIV_4,
	VA_MACRO_CLK_DIV_6,
	VA_MACRO_CLK_DIV_8,
	VA_MACRO_CLK_DIV_16,
पूर्ण;

#घोषणा VA_NUM_CLKS_MAX		3

काष्ठा va_macro अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ active_ch_mask[VA_MACRO_MAX_DAIS];
	अचिन्हित दीर्घ active_ch_cnt[VA_MACRO_MAX_DAIS];
	u16 dmic_clk_भाग;

	पूर्णांक dec_mode[VA_MACRO_NUM_DECIMATORS];
	काष्ठा regmap *regmap;
	काष्ठा clk_bulk_data clks[VA_NUM_CLKS_MAX];
	काष्ठा clk_hw hw;

	s32 dmic_0_1_clk_cnt;
	s32 dmic_2_3_clk_cnt;
	s32 dmic_4_5_clk_cnt;
	s32 dmic_6_7_clk_cnt;
	u8 dmic_0_1_clk_भाग;
	u8 dmic_2_3_clk_भाग;
	u8 dmic_4_5_clk_भाग;
	u8 dmic_6_7_clk_भाग;
पूर्ण;

#घोषणा to_va_macro(_hw) container_of(_hw, काष्ठा va_macro, hw)

अटल bool va_is_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_VA_TOP_CSR_CORE_ID_0:
	हाल CDC_VA_TOP_CSR_CORE_ID_1:
	हाल CDC_VA_TOP_CSR_CORE_ID_2:
	हाल CDC_VA_TOP_CSR_CORE_ID_3:
	हाल CDC_VA_TOP_CSR_DMIC0_CTL:
	हाल CDC_VA_TOP_CSR_DMIC1_CTL:
	हाल CDC_VA_TOP_CSR_DMIC2_CTL:
	हाल CDC_VA_TOP_CSR_DMIC3_CTL:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा reg_शेष va_शेषs[] = अणु
	/* VA macro */
	अणु CDC_VA_CLK_RST_CTRL_MCLK_CONTROL, 0x00पूर्ण,
	अणु CDC_VA_CLK_RST_CTRL_FS_CNT_CONTROL, 0x00पूर्ण,
	अणु CDC_VA_CLK_RST_CTRL_SWR_CONTROL, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_TOP_CFG0, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DMIC0_CTL, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DMIC1_CTL, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DMIC2_CTL, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DMIC3_CTL, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DMIC_CFG, 0x80पूर्ण,
	अणु CDC_VA_TOP_CSR_DEBUG_BUS, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_DEBUG_EN, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_TX_I2S_CTL, 0x0Cपूर्ण,
	अणु CDC_VA_TOP_CSR_I2S_CLK, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_I2S_RESET, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_CORE_ID_0, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_CORE_ID_1, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_CORE_ID_2, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_CORE_ID_3, 0x00पूर्ण,
	अणु CDC_VA_TOP_CSR_SWR_MIC_CTL0, 0xEEपूर्ण,
	अणु CDC_VA_TOP_CSR_SWR_MIC_CTL1, 0xEEपूर्ण,
	अणु CDC_VA_TOP_CSR_SWR_MIC_CTL2, 0xEEपूर्ण,
	अणु CDC_VA_TOP_CSR_SWR_CTRL, 0x06पूर्ण,

	/* VA core */
	अणु CDC_VA_INP_MUX_ADC_MUX0_CFG0, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX0_CFG1, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX1_CFG0, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX1_CFG1, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX2_CFG0, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX2_CFG1, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX3_CFG0, 0x00पूर्ण,
	अणु CDC_VA_INP_MUX_ADC_MUX3_CFG1, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_VA_TX0_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_VA_TX0_TX_PATH_SEC7, 0x25पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_VA_TX1_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_VA_TX1_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_VA_TX2_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_VA_TX2_TX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_CFG0, 0x10पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_CFG1, 0x0Bपूर्ण,
	अणु CDC_VA_TX3_TX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC0, 0x00पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC1, 0x00पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC2, 0x01पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC3, 0x3Cपूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC4, 0x20पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_VA_TX3_TX_PATH_SEC6, 0x00पूर्ण,
पूर्ण;

अटल bool va_is_rw_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_VA_CLK_RST_CTRL_MCLK_CONTROL:
	हाल CDC_VA_CLK_RST_CTRL_FS_CNT_CONTROL:
	हाल CDC_VA_CLK_RST_CTRL_SWR_CONTROL:
	हाल CDC_VA_TOP_CSR_TOP_CFG0:
	हाल CDC_VA_TOP_CSR_DMIC0_CTL:
	हाल CDC_VA_TOP_CSR_DMIC1_CTL:
	हाल CDC_VA_TOP_CSR_DMIC2_CTL:
	हाल CDC_VA_TOP_CSR_DMIC3_CTL:
	हाल CDC_VA_TOP_CSR_DMIC_CFG:
	हाल CDC_VA_TOP_CSR_DEBUG_BUS:
	हाल CDC_VA_TOP_CSR_DEBUG_EN:
	हाल CDC_VA_TOP_CSR_TX_I2S_CTL:
	हाल CDC_VA_TOP_CSR_I2S_CLK:
	हाल CDC_VA_TOP_CSR_I2S_RESET:
	हाल CDC_VA_INP_MUX_ADC_MUX0_CFG0:
	हाल CDC_VA_INP_MUX_ADC_MUX0_CFG1:
	हाल CDC_VA_INP_MUX_ADC_MUX1_CFG0:
	हाल CDC_VA_INP_MUX_ADC_MUX1_CFG1:
	हाल CDC_VA_INP_MUX_ADC_MUX2_CFG0:
	हाल CDC_VA_INP_MUX_ADC_MUX2_CFG1:
	हाल CDC_VA_INP_MUX_ADC_MUX3_CFG0:
	हाल CDC_VA_INP_MUX_ADC_MUX3_CFG1:
	हाल CDC_VA_TX0_TX_PATH_CTL:
	हाल CDC_VA_TX0_TX_PATH_CFG0:
	हाल CDC_VA_TX0_TX_PATH_CFG1:
	हाल CDC_VA_TX0_TX_VOL_CTL:
	हाल CDC_VA_TX0_TX_PATH_SEC0:
	हाल CDC_VA_TX0_TX_PATH_SEC1:
	हाल CDC_VA_TX0_TX_PATH_SEC2:
	हाल CDC_VA_TX0_TX_PATH_SEC3:
	हाल CDC_VA_TX0_TX_PATH_SEC4:
	हाल CDC_VA_TX0_TX_PATH_SEC5:
	हाल CDC_VA_TX0_TX_PATH_SEC6:
	हाल CDC_VA_TX0_TX_PATH_SEC7:
	हाल CDC_VA_TX1_TX_PATH_CTL:
	हाल CDC_VA_TX1_TX_PATH_CFG0:
	हाल CDC_VA_TX1_TX_PATH_CFG1:
	हाल CDC_VA_TX1_TX_VOL_CTL:
	हाल CDC_VA_TX1_TX_PATH_SEC0:
	हाल CDC_VA_TX1_TX_PATH_SEC1:
	हाल CDC_VA_TX1_TX_PATH_SEC2:
	हाल CDC_VA_TX1_TX_PATH_SEC3:
	हाल CDC_VA_TX1_TX_PATH_SEC4:
	हाल CDC_VA_TX1_TX_PATH_SEC5:
	हाल CDC_VA_TX1_TX_PATH_SEC6:
	हाल CDC_VA_TX2_TX_PATH_CTL:
	हाल CDC_VA_TX2_TX_PATH_CFG0:
	हाल CDC_VA_TX2_TX_PATH_CFG1:
	हाल CDC_VA_TX2_TX_VOL_CTL:
	हाल CDC_VA_TX2_TX_PATH_SEC0:
	हाल CDC_VA_TX2_TX_PATH_SEC1:
	हाल CDC_VA_TX2_TX_PATH_SEC2:
	हाल CDC_VA_TX2_TX_PATH_SEC3:
	हाल CDC_VA_TX2_TX_PATH_SEC4:
	हाल CDC_VA_TX2_TX_PATH_SEC5:
	हाल CDC_VA_TX2_TX_PATH_SEC6:
	हाल CDC_VA_TX3_TX_PATH_CTL:
	हाल CDC_VA_TX3_TX_PATH_CFG0:
	हाल CDC_VA_TX3_TX_PATH_CFG1:
	हाल CDC_VA_TX3_TX_VOL_CTL:
	हाल CDC_VA_TX3_TX_PATH_SEC0:
	हाल CDC_VA_TX3_TX_PATH_SEC1:
	हाल CDC_VA_TX3_TX_PATH_SEC2:
	हाल CDC_VA_TX3_TX_PATH_SEC3:
	हाल CDC_VA_TX3_TX_PATH_SEC4:
	हाल CDC_VA_TX3_TX_PATH_SEC5:
	हाल CDC_VA_TX3_TX_PATH_SEC6:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool va_is_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_VA_TOP_CSR_CORE_ID_0:
	हाल CDC_VA_TOP_CSR_CORE_ID_1:
	हाल CDC_VA_TOP_CSR_CORE_ID_2:
	हाल CDC_VA_TOP_CSR_CORE_ID_3:
		वापस true;
	पूर्ण

	वापस va_is_rw_रेजिस्टर(dev, reg);
पूर्ण

अटल स्थिर काष्ठा regmap_config va_regmap_config = अणु
	.name = "va_macro",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.cache_type = REGCACHE_FLAT,
	.reg_शेषs = va_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(va_शेषs),
	.max_रेजिस्टर = VA_MAX_OFFSET,
	.अस्थिर_reg = va_is_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = va_is_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg = va_is_rw_रेजिस्टर,
पूर्ण;

अटल पूर्णांक va_clk_rsc_fs_gen_request(काष्ठा va_macro *va, bool enable)
अणु
	काष्ठा regmap *regmap = va->regmap;

	अगर (enable) अणु
		regmap_update_bits(regmap, CDC_VA_CLK_RST_CTRL_MCLK_CONTROL,
				   CDC_VA_MCLK_CONTROL_EN,
				   CDC_VA_MCLK_CONTROL_EN);

		regmap_update_bits(regmap, CDC_VA_CLK_RST_CTRL_FS_CNT_CONTROL,
				   CDC_VA_FS_CONTROL_EN,
				   CDC_VA_FS_CONTROL_EN);

		regmap_update_bits(regmap, CDC_VA_TOP_CSR_TOP_CFG0,
				   CDC_VA_FS_BROADCAST_EN,
				   CDC_VA_FS_BROADCAST_EN);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap, CDC_VA_CLK_RST_CTRL_MCLK_CONTROL,
				   CDC_VA_MCLK_CONTROL_EN, 0x0);

		regmap_update_bits(regmap, CDC_VA_CLK_RST_CTRL_FS_CNT_CONTROL,
				   CDC_VA_FS_CONTROL_EN, 0x0);

		regmap_update_bits(regmap, CDC_VA_TOP_CSR_TOP_CFG0,
				   CDC_VA_FS_BROADCAST_EN, 0x0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_mclk_enable(काष्ठा va_macro *va, bool mclk_enable)
अणु
	काष्ठा regmap *regmap = va->regmap;

	अगर (mclk_enable) अणु
		va_clk_rsc_fs_gen_request(va, true);
		regcache_mark_dirty(regmap);
		regcache_sync_region(regmap, 0x0, VA_MAX_OFFSET);
	पूर्ण अन्यथा अणु
		va_clk_rsc_fs_gen_request(va, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_mclk_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(comp);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस va_macro_mclk_enable(va, true);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस va_macro_mclk_enable(va, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_put_dec_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget =
		snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;
	u16 mic_sel_reg;

	val = ucontrol->value.क्रमागतerated.item[0];

	चयन (e->reg) अणु
	हाल CDC_VA_INP_MUX_ADC_MUX0_CFG0:
		mic_sel_reg = CDC_VA_TX0_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_VA_INP_MUX_ADC_MUX1_CFG0:
		mic_sel_reg = CDC_VA_TX1_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_VA_INP_MUX_ADC_MUX2_CFG0:
		mic_sel_reg = CDC_VA_TX2_TX_PATH_CFG0;
		अवरोध;
	हाल CDC_VA_INP_MUX_ADC_MUX3_CFG0:
		mic_sel_reg = CDC_VA_TX3_TX_PATH_CFG0;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: e->reg: 0x%x not expected\n",
			__func__, e->reg);
		वापस -EINVAL;
	पूर्ण

	अगर (val != 0)
		snd_soc_component_update_bits(component, mic_sel_reg,
					      CDC_VA_TX_PATH_ADC_DMIC_SEL_MASK,
					      CDC_VA_TX_PATH_ADC_DMIC_SEL_DMIC);

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

अटल पूर्णांक va_macro_tx_mixer_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget =
		snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component =
				snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	u32 dai_id = widget->shअगरt;
	u32 dec_id = mc->shअगरt;
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);

	अगर (test_bit(dec_id, &va->active_ch_mask[dai_id]))
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_tx_mixer_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget =
					snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component =
				snd_soc_dapm_to_component(widget->dapm);
	काष्ठा snd_soc_dapm_update *update = शून्य;
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	u32 dai_id = widget->shअगरt;
	u32 dec_id = mc->shअगरt;
	u32 enable = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);

	अगर (enable) अणु
		set_bit(dec_id, &va->active_ch_mask[dai_id]);
		va->active_ch_cnt[dai_id]++;
	पूर्ण अन्यथा अणु
		clear_bit(dec_id, &va->active_ch_mask[dai_id]);
		va->active_ch_cnt[dai_id]--;
	पूर्ण

	snd_soc_dapm_mixer_update_घातer(widget->dapm, kcontrol, enable, update);

	वापस 0;
पूर्ण

अटल पूर्णांक va_dmic_clk_enable(काष्ठा snd_soc_component *component,
			      u32 dmic, bool enable)
अणु
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);
	u16 dmic_clk_reg;
	s32 *dmic_clk_cnt;
	u8 *dmic_clk_भाग;
	u8 freq_change_mask;
	u8 clk_भाग;

	चयन (dmic) अणु
	हाल 0:
	हाल 1:
		dmic_clk_cnt = &(va->dmic_0_1_clk_cnt);
		dmic_clk_भाग = &(va->dmic_0_1_clk_भाग);
		dmic_clk_reg = CDC_VA_TOP_CSR_DMIC0_CTL;
		freq_change_mask = CDC_VA_DMIC0_FREQ_CHANGE_MASK;
		अवरोध;
	हाल 2:
	हाल 3:
		dmic_clk_cnt = &(va->dmic_2_3_clk_cnt);
		dmic_clk_भाग = &(va->dmic_2_3_clk_भाग);
		dmic_clk_reg = CDC_VA_TOP_CSR_DMIC1_CTL;
		freq_change_mask = CDC_VA_DMIC1_FREQ_CHANGE_MASK;
		अवरोध;
	हाल 4:
	हाल 5:
		dmic_clk_cnt = &(va->dmic_4_5_clk_cnt);
		dmic_clk_भाग = &(va->dmic_4_5_clk_भाग);
		dmic_clk_reg = CDC_VA_TOP_CSR_DMIC2_CTL;
		freq_change_mask = CDC_VA_DMIC2_FREQ_CHANGE_MASK;
		अवरोध;
	हाल 6:
	हाल 7:
		dmic_clk_cnt = &(va->dmic_6_7_clk_cnt);
		dmic_clk_भाग = &(va->dmic_6_7_clk_भाग);
		dmic_clk_reg = CDC_VA_TOP_CSR_DMIC3_CTL;
		freq_change_mask = CDC_VA_DMIC3_FREQ_CHANGE_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: Invalid DMIC Selection\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (enable) अणु
		clk_भाग = va->dmic_clk_भाग;
		(*dmic_clk_cnt)++;
		अगर (*dmic_clk_cnt == 1) अणु
			snd_soc_component_update_bits(component,
					      CDC_VA_TOP_CSR_DMIC_CFG,
					      CDC_VA_RESET_ALL_DMICS_MASK,
					      CDC_VA_RESET_ALL_DMICS_DISABLE);
			snd_soc_component_update_bits(component, dmic_clk_reg,
					CDC_VA_DMIC_CLK_SEL_MASK,
					clk_भाग << CDC_VA_DMIC_CLK_SEL_SHFT);
			snd_soc_component_update_bits(component, dmic_clk_reg,
						      CDC_VA_DMIC_EN_MASK,
						      CDC_VA_DMIC_ENABLE);
		पूर्ण अन्यथा अणु
			अगर (*dmic_clk_भाग > clk_भाग) अणु
				snd_soc_component_update_bits(component,
						CDC_VA_TOP_CSR_DMIC_CFG,
						freq_change_mask,
						freq_change_mask);
				snd_soc_component_update_bits(component, dmic_clk_reg,
						CDC_VA_DMIC_CLK_SEL_MASK,
						clk_भाग << CDC_VA_DMIC_CLK_SEL_SHFT);
				snd_soc_component_update_bits(component,
					      CDC_VA_TOP_CSR_DMIC_CFG,
					      freq_change_mask,
					      CDC_VA_DMIC_FREQ_CHANGE_DISABLE);
			पूर्ण अन्यथा अणु
				clk_भाग = *dmic_clk_भाग;
			पूर्ण
		पूर्ण
		*dmic_clk_भाग = clk_भाग;
	पूर्ण अन्यथा अणु
		(*dmic_clk_cnt)--;
		अगर (*dmic_clk_cnt  == 0) अणु
			snd_soc_component_update_bits(component, dmic_clk_reg,
						      CDC_VA_DMIC_EN_MASK, 0);
			clk_भाग = 0;
			snd_soc_component_update_bits(component, dmic_clk_reg,
						CDC_VA_DMIC_CLK_SEL_MASK,
						clk_भाग << CDC_VA_DMIC_CLK_SEL_SHFT);
		पूर्ण अन्यथा अणु
			clk_भाग = va->dmic_clk_भाग;
			अगर (*dmic_clk_भाग > clk_भाग) अणु
				clk_भाग = va->dmic_clk_भाग;
				snd_soc_component_update_bits(component,
							CDC_VA_TOP_CSR_DMIC_CFG,
							freq_change_mask,
							freq_change_mask);
				snd_soc_component_update_bits(component, dmic_clk_reg,
						CDC_VA_DMIC_CLK_SEL_MASK,
						clk_भाग << CDC_VA_DMIC_CLK_SEL_SHFT);
				snd_soc_component_update_bits(component,
						      CDC_VA_TOP_CSR_DMIC_CFG,
						      freq_change_mask,
						      CDC_VA_DMIC_FREQ_CHANGE_DISABLE);
			पूर्ण अन्यथा अणु
				clk_भाग = *dmic_clk_भाग;
			पूर्ण
		पूर्ण
		*dmic_clk_भाग = clk_भाग;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_enable_dmic(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक dmic = w->shअगरt;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		va_dmic_clk_enable(comp, dmic, true);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		va_dmic_clk_enable(comp, dmic, false);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_enable_dec(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक decimator;
	u16 tx_vol_ctl_reg, dec_cfg_reg, hpf_gate_reg;
	u16 tx_gain_ctl_reg;
	u8 hpf_cut_off_freq;

	काष्ठा va_macro *va = snd_soc_component_get_drvdata(comp);

	decimator = w->shअगरt;

	tx_vol_ctl_reg = CDC_VA_TX0_TX_PATH_CTL +
				VA_MACRO_TX_PATH_OFFSET * decimator;
	hpf_gate_reg = CDC_VA_TX0_TX_PATH_SEC2 +
				VA_MACRO_TX_PATH_OFFSET * decimator;
	dec_cfg_reg = CDC_VA_TX0_TX_PATH_CFG0 +
				VA_MACRO_TX_PATH_OFFSET * decimator;
	tx_gain_ctl_reg = CDC_VA_TX0_TX_VOL_CTL +
				VA_MACRO_TX_PATH_OFFSET * decimator;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(comp,
			dec_cfg_reg, CDC_VA_ADC_MODE_MASK,
			va->dec_mode[decimator] << CDC_VA_ADC_MODE_SHIFT);
		/* Enable TX PGA Mute */
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* Enable TX CLK */
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg,
					      CDC_VA_TX_PATH_CLK_EN_MASK,
					      CDC_VA_TX_PATH_CLK_EN);
		snd_soc_component_update_bits(comp, hpf_gate_reg,
					      CDC_VA_TX_HPF_ZERO_GATE_MASK,
					      CDC_VA_TX_HPF_ZERO_GATE);

		usleep_range(1000, 1010);
		hpf_cut_off_freq = (snd_soc_component_पढ़ो(comp, dec_cfg_reg) &
				    TX_HPF_CUT_OFF_FREQ_MASK) >> 5;

		अगर (hpf_cut_off_freq != CF_MIN_3DB_150HZ) अणु
			snd_soc_component_update_bits(comp, dec_cfg_reg,
						      TX_HPF_CUT_OFF_FREQ_MASK,
						      CF_MIN_3DB_150HZ << 5);

			snd_soc_component_update_bits(comp, hpf_gate_reg,
				      CDC_VA_TX_HPF_CUTOFF_FREQ_CHANGE_MASK,
				      CDC_VA_TX_HPF_CUTOFF_FREQ_CHANGE_REQ);

			/*
			 * Minimum 1 clk cycle delay is required as per HW spec
			 */
			usleep_range(1000, 1010);

			snd_soc_component_update_bits(comp,
				hpf_gate_reg,
				CDC_VA_TX_HPF_CUTOFF_FREQ_CHANGE_MASK,
				0x0);
		पूर्ण


		usleep_range(1000, 1010);
		snd_soc_component_update_bits(comp, hpf_gate_reg,
					      CDC_VA_TX_HPF_ZERO_GATE_MASK,
					      CDC_VA_TX_HPF_ZERO_NO_GATE);
		/*
		 * 6ms delay is required as per HW spec
		 */
		usleep_range(6000, 6010);
		/* apply gain after decimator is enabled */
		snd_soc_component_ग_लिखो(comp, tx_gain_ctl_reg,
			snd_soc_component_पढ़ो(comp, tx_gain_ctl_reg));
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable TX CLK */
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg,
						CDC_VA_TX_PATH_CLK_EN_MASK,
						CDC_VA_TX_PATH_CLK_DISABLE);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_dec_mode_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	पूर्णांक path = e->shअगरt_l;

	ucontrol->value.पूर्णांकeger.value[0] = va->dec_mode[path];

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_dec_mode_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	पूर्णांक path = e->shअगरt_l;
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(comp);

	va->dec_mode[path] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक tx_fs_rate;
	काष्ठा snd_soc_component *component = dai->component;
	u32 decimator, sample_rate;
	u16 tx_fs_reg;
	काष्ठा device *va_dev = component->dev;
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);

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
		dev_err(va_dev, "%s: Invalid TX sample rate: %d\n",
			__func__, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	क्रम_each_set_bit(decimator, &va->active_ch_mask[dai->id],
			 VA_MACRO_DEC_MAX) अणु
		tx_fs_reg = CDC_VA_TX0_TX_PATH_CTL +
			    VA_MACRO_TX_PATH_OFFSET * decimator;
		snd_soc_component_update_bits(component, tx_fs_reg, 0x0F,
					      tx_fs_rate);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_get_channel_map(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				    अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा device *va_dev = component->dev;
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);

	चयन (dai->id) अणु
	हाल VA_MACRO_AIF1_CAP:
	हाल VA_MACRO_AIF2_CAP:
	हाल VA_MACRO_AIF3_CAP:
		*tx_slot = va->active_ch_mask[dai->id];
		*tx_num = va->active_ch_cnt[dai->id];
		अवरोध;
	शेष:
		dev_err(va_dev, "%s: Invalid AIF\n", __func__);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक va_macro_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);
	u16 tx_vol_ctl_reg, decimator;

	क्रम_each_set_bit(decimator, &va->active_ch_mask[dai->id],
			 VA_MACRO_DEC_MAX) अणु
		tx_vol_ctl_reg = CDC_VA_TX0_TX_PATH_CTL +
					VA_MACRO_TX_PATH_OFFSET * decimator;
		अगर (mute)
			snd_soc_component_update_bits(component, tx_vol_ctl_reg,
					CDC_VA_TX_PATH_PGA_MUTE_EN_MASK,
					CDC_VA_TX_PATH_PGA_MUTE_EN);
		अन्यथा
			snd_soc_component_update_bits(component, tx_vol_ctl_reg,
					CDC_VA_TX_PATH_PGA_MUTE_EN_MASK,
					CDC_VA_TX_PATH_PGA_MUTE_DISABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops va_macro_dai_ops = अणु
	.hw_params = va_macro_hw_params,
	.get_channel_map = va_macro_get_channel_map,
	.mute_stream = va_macro_digital_mute,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver va_macro_dais[] = अणु
	अणु
		.name = "va_macro_tx1",
		.id = VA_MACRO_AIF1_CAP,
		.capture = अणु
			.stream_name = "VA_AIF1 Capture",
			.rates = VA_MACRO_RATES,
			.क्रमmats = VA_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &va_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "va_macro_tx2",
		.id = VA_MACRO_AIF2_CAP,
		.capture = अणु
			.stream_name = "VA_AIF2 Capture",
			.rates = VA_MACRO_RATES,
			.क्रमmats = VA_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &va_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "va_macro_tx3",
		.id = VA_MACRO_AIF3_CAP,
		.capture = अणु
			.stream_name = "VA_AIF3 Capture",
			.rates = VA_MACRO_RATES,
			.क्रमmats = VA_MACRO_FORMATS,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 8,
		पूर्ण,
		.ops = &va_macro_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_mux_text[] = अणु
	"VA_DMIC", "SWR_MIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(va_dec0_क्रमागत, CDC_VA_INP_MUX_ADC_MUX0_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(va_dec1_क्रमागत, CDC_VA_INP_MUX_ADC_MUX1_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(va_dec2_क्रमागत, CDC_VA_INP_MUX_ADC_MUX2_CFG1,
		   0, adc_mux_text);
अटल SOC_ENUM_SINGLE_DECL(va_dec3_क्रमागत, CDC_VA_INP_MUX_ADC_MUX3_CFG1,
		   0, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new va_dec0_mux = SOC_DAPM_ENUM("va_dec0",
								 va_dec0_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new va_dec1_mux = SOC_DAPM_ENUM("va_dec1",
								 va_dec1_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new va_dec2_mux = SOC_DAPM_ENUM("va_dec2",
								 va_dec2_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new va_dec3_mux = SOC_DAPM_ENUM("va_dec3",
								 va_dec3_क्रमागत);

अटल स्थिर अक्षर * स्थिर dmic_mux_text[] = अणु
	"ZERO", "DMIC0", "DMIC1", "DMIC2", "DMIC3",
	"DMIC4", "DMIC5", "DMIC6", "DMIC7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(va_dmic0_क्रमागत, CDC_VA_INP_MUX_ADC_MUX0_CFG0,
			4, dmic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(va_dmic1_क्रमागत, CDC_VA_INP_MUX_ADC_MUX1_CFG0,
			4, dmic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(va_dmic2_क्रमागत, CDC_VA_INP_MUX_ADC_MUX2_CFG0,
			4, dmic_mux_text);

अटल SOC_ENUM_SINGLE_DECL(va_dmic3_क्रमागत, CDC_VA_INP_MUX_ADC_MUX3_CFG0,
			4, dmic_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new va_dmic0_mux = SOC_DAPM_ENUM_EXT("va_dmic0",
			 va_dmic0_क्रमागत, snd_soc_dapm_get_क्रमागत_द्विगुन,
			 va_macro_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new va_dmic1_mux = SOC_DAPM_ENUM_EXT("va_dmic1",
			 va_dmic1_क्रमागत, snd_soc_dapm_get_क्रमागत_द्विगुन,
			 va_macro_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new va_dmic2_mux = SOC_DAPM_ENUM_EXT("va_dmic2",
			 va_dmic2_क्रमागत, snd_soc_dapm_get_क्रमागत_द्विगुन,
			 va_macro_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new va_dmic3_mux = SOC_DAPM_ENUM_EXT("va_dmic3",
			 va_dmic3_क्रमागत, snd_soc_dapm_get_क्रमागत_द्विगुन,
			 va_macro_put_dec_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new va_aअगर1_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, VA_MACRO_DEC0, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, VA_MACRO_DEC1, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, VA_MACRO_DEC2, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, VA_MACRO_DEC3, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, VA_MACRO_DEC4, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, VA_MACRO_DEC5, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, VA_MACRO_DEC6, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, VA_MACRO_DEC7, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new va_aअगर2_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, VA_MACRO_DEC0, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, VA_MACRO_DEC1, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, VA_MACRO_DEC2, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, VA_MACRO_DEC3, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, VA_MACRO_DEC4, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, VA_MACRO_DEC5, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, VA_MACRO_DEC6, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, VA_MACRO_DEC7, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new va_aअगर3_cap_mixer[] = अणु
	SOC_SINGLE_EXT("DEC0", SND_SOC_NOPM, VA_MACRO_DEC0, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC1", SND_SOC_NOPM, VA_MACRO_DEC1, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC2", SND_SOC_NOPM, VA_MACRO_DEC2, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC3", SND_SOC_NOPM, VA_MACRO_DEC3, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC4", SND_SOC_NOPM, VA_MACRO_DEC4, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC5", SND_SOC_NOPM, VA_MACRO_DEC5, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC6", SND_SOC_NOPM, VA_MACRO_DEC6, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
	SOC_SINGLE_EXT("DEC7", SND_SOC_NOPM, VA_MACRO_DEC7, 1, 0,
			va_macro_tx_mixer_get, va_macro_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget va_macro_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("VA_AIF1 CAP", "VA_AIF1 Capture", 0,
		SND_SOC_NOPM, VA_MACRO_AIF1_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("VA_AIF2 CAP", "VA_AIF2 Capture", 0,
		SND_SOC_NOPM, VA_MACRO_AIF2_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("VA_AIF3 CAP", "VA_AIF3 Capture", 0,
		SND_SOC_NOPM, VA_MACRO_AIF3_CAP, 0),

	SND_SOC_DAPM_MIXER("VA_AIF1_CAP Mixer", SND_SOC_NOPM,
		VA_MACRO_AIF1_CAP, 0,
		va_aअगर1_cap_mixer, ARRAY_SIZE(va_aअगर1_cap_mixer)),

	SND_SOC_DAPM_MIXER("VA_AIF2_CAP Mixer", SND_SOC_NOPM,
		VA_MACRO_AIF2_CAP, 0,
		va_aअगर2_cap_mixer, ARRAY_SIZE(va_aअगर2_cap_mixer)),

	SND_SOC_DAPM_MIXER("VA_AIF3_CAP Mixer", SND_SOC_NOPM,
		VA_MACRO_AIF3_CAP, 0,
		va_aअगर3_cap_mixer, ARRAY_SIZE(va_aअगर3_cap_mixer)),

	SND_SOC_DAPM_MUX("VA DMIC MUX0", SND_SOC_NOPM, 0, 0, &va_dmic0_mux),
	SND_SOC_DAPM_MUX("VA DMIC MUX1", SND_SOC_NOPM, 0, 0, &va_dmic1_mux),
	SND_SOC_DAPM_MUX("VA DMIC MUX2", SND_SOC_NOPM, 0, 0, &va_dmic2_mux),
	SND_SOC_DAPM_MUX("VA DMIC MUX3", SND_SOC_NOPM, 0, 0, &va_dmic3_mux),

	SND_SOC_DAPM_REGULATOR_SUPPLY("vdd-micb", 0, 0),
	SND_SOC_DAPM_INPUT("DMIC0 Pin"),
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("DMIC3 Pin"),
	SND_SOC_DAPM_INPUT("DMIC4 Pin"),
	SND_SOC_DAPM_INPUT("DMIC5 Pin"),
	SND_SOC_DAPM_INPUT("DMIC6 Pin"),
	SND_SOC_DAPM_INPUT("DMIC7 Pin"),

	SND_SOC_DAPM_ADC_E("VA DMIC0", शून्य, SND_SOC_NOPM, 0, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC1", शून्य, SND_SOC_NOPM, 1, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC2", शून्य, SND_SOC_NOPM, 2, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC3", शून्य, SND_SOC_NOPM, 3, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC4", शून्य, SND_SOC_NOPM, 4, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC5", शून्य, SND_SOC_NOPM, 5, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC6", शून्य, SND_SOC_NOPM, 6, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_ADC_E("VA DMIC7", शून्य, SND_SOC_NOPM, 7, 0,
		va_macro_enable_dmic, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("VA SWR_ADC0"),
	SND_SOC_DAPM_INPUT("VA SWR_ADC1"),
	SND_SOC_DAPM_INPUT("VA SWR_ADC2"),
	SND_SOC_DAPM_INPUT("VA SWR_ADC3"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC0"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC1"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC2"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC3"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC4"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC5"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC6"),
	SND_SOC_DAPM_INPUT("VA SWR_MIC7"),

	SND_SOC_DAPM_MUX_E("VA DEC0 MUX", SND_SOC_NOPM, VA_MACRO_DEC0, 0,
			   &va_dec0_mux, va_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("VA DEC1 MUX", SND_SOC_NOPM, VA_MACRO_DEC1, 0,
			   &va_dec1_mux, va_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("VA DEC2 MUX", SND_SOC_NOPM, VA_MACRO_DEC2, 0,
			   &va_dec2_mux, va_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("VA DEC3 MUX", SND_SOC_NOPM, VA_MACRO_DEC3, 0,
			   &va_dec3_mux, va_macro_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("VA_MCLK", -1, SND_SOC_NOPM, 0, 0,
			      va_macro_mclk_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route va_audio_map[] = अणु
	अणु"VA_AIF1 CAP", शून्य, "VA_MCLK"पूर्ण,
	अणु"VA_AIF2 CAP", शून्य, "VA_MCLK"पूर्ण,
	अणु"VA_AIF3 CAP", शून्य, "VA_MCLK"पूर्ण,

	अणु"VA_AIF1 CAP", शून्य, "VA_AIF1_CAP Mixer"पूर्ण,
	अणु"VA_AIF2 CAP", शून्य, "VA_AIF2_CAP Mixer"पूर्ण,
	अणु"VA_AIF3 CAP", शून्य, "VA_AIF3_CAP Mixer"पूर्ण,

	अणु"VA_AIF1_CAP Mixer", "DEC0", "VA DEC0 MUX"पूर्ण,
	अणु"VA_AIF1_CAP Mixer", "DEC1", "VA DEC1 MUX"पूर्ण,
	अणु"VA_AIF1_CAP Mixer", "DEC2", "VA DEC2 MUX"पूर्ण,
	अणु"VA_AIF1_CAP Mixer", "DEC3", "VA DEC3 MUX"पूर्ण,

	अणु"VA_AIF2_CAP Mixer", "DEC0", "VA DEC0 MUX"पूर्ण,
	अणु"VA_AIF2_CAP Mixer", "DEC1", "VA DEC1 MUX"पूर्ण,
	अणु"VA_AIF2_CAP Mixer", "DEC2", "VA DEC2 MUX"पूर्ण,
	अणु"VA_AIF2_CAP Mixer", "DEC3", "VA DEC3 MUX"पूर्ण,

	अणु"VA_AIF3_CAP Mixer", "DEC0", "VA DEC0 MUX"पूर्ण,
	अणु"VA_AIF3_CAP Mixer", "DEC1", "VA DEC1 MUX"पूर्ण,
	अणु"VA_AIF3_CAP Mixer", "DEC2", "VA DEC2 MUX"पूर्ण,
	अणु"VA_AIF3_CAP Mixer", "DEC3", "VA DEC3 MUX"पूर्ण,

	अणु"VA DEC0 MUX", "VA_DMIC", "VA DMIC MUX0"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC0", "VA DMIC0"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC1", "VA DMIC1"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC2", "VA DMIC2"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC3", "VA DMIC3"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC4", "VA DMIC4"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC5", "VA DMIC5"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC6", "VA DMIC6"पूर्ण,
	अणु"VA DMIC MUX0", "DMIC7", "VA DMIC7"पूर्ण,

	अणु"VA DEC1 MUX", "VA_DMIC", "VA DMIC MUX1"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC0", "VA DMIC0"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC1", "VA DMIC1"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC2", "VA DMIC2"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC3", "VA DMIC3"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC4", "VA DMIC4"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC5", "VA DMIC5"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC6", "VA DMIC6"पूर्ण,
	अणु"VA DMIC MUX1", "DMIC7", "VA DMIC7"पूर्ण,

	अणु"VA DEC2 MUX", "VA_DMIC", "VA DMIC MUX2"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC0", "VA DMIC0"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC1", "VA DMIC1"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC2", "VA DMIC2"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC3", "VA DMIC3"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC4", "VA DMIC4"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC5", "VA DMIC5"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC6", "VA DMIC6"पूर्ण,
	अणु"VA DMIC MUX2", "DMIC7", "VA DMIC7"पूर्ण,

	अणु"VA DEC3 MUX", "VA_DMIC", "VA DMIC MUX3"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC0", "VA DMIC0"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC1", "VA DMIC1"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC2", "VA DMIC2"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC3", "VA DMIC3"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC4", "VA DMIC4"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC5", "VA DMIC5"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC6", "VA DMIC6"पूर्ण,
	अणु"VA DMIC MUX3", "DMIC7", "VA DMIC7"पूर्ण,

	अणु "VA DMIC0", शून्य, "DMIC0 Pin" पूर्ण,
	अणु "VA DMIC1", शून्य, "DMIC1 Pin" पूर्ण,
	अणु "VA DMIC2", शून्य, "DMIC2 Pin" पूर्ण,
	अणु "VA DMIC3", शून्य, "DMIC3 Pin" पूर्ण,
	अणु "VA DMIC4", शून्य, "DMIC4 Pin" पूर्ण,
	अणु "VA DMIC5", शून्य, "DMIC5 Pin" पूर्ण,
	अणु "VA DMIC6", शून्य, "DMIC6 Pin" पूर्ण,
	अणु "VA DMIC7", शून्य, "DMIC7 Pin" पूर्ण,
पूर्ण;

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
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new va_macro_snd_controls[] = अणु
	SOC_SINGLE_S8_TLV("VA_DEC0 Volume", CDC_VA_TX0_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("VA_DEC1 Volume", CDC_VA_TX1_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("VA_DEC2 Volume", CDC_VA_TX2_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("VA_DEC3 Volume", CDC_VA_TX3_TX_VOL_CTL,
			  -84, 40, digital_gain),

	SOC_ENUM_EXT("VA_DEC0 MODE", dec_mode_mux_क्रमागत[0],
		     va_macro_dec_mode_get, va_macro_dec_mode_put),
	SOC_ENUM_EXT("VA_DEC1 MODE", dec_mode_mux_क्रमागत[1],
		     va_macro_dec_mode_get, va_macro_dec_mode_put),
	SOC_ENUM_EXT("VA_DEC2 MODE", dec_mode_mux_क्रमागत[2],
		     va_macro_dec_mode_get, va_macro_dec_mode_put),
	SOC_ENUM_EXT("VA_DEC3 MODE", dec_mode_mux_क्रमागत[3],
		     va_macro_dec_mode_get, va_macro_dec_mode_put),
पूर्ण;

अटल पूर्णांक va_macro_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा va_macro *va = snd_soc_component_get_drvdata(component);

	snd_soc_component_init_regmap(component, va->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver va_macro_component_drv = अणु
	.name = "VA MACRO",
	.probe = va_macro_component_probe,
	.controls = va_macro_snd_controls,
	.num_controls = ARRAY_SIZE(va_macro_snd_controls),
	.dapm_widमाला_लो = va_macro_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(va_macro_dapm_widमाला_लो),
	.dapm_routes = va_audio_map,
	.num_dapm_routes = ARRAY_SIZE(va_audio_map),
पूर्ण;

अटल पूर्णांक fsgen_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस va_macro_mclk_enable(to_va_macro(hw), true);
पूर्ण

अटल व्योम fsgen_gate_disable(काष्ठा clk_hw *hw)
अणु
	va_macro_mclk_enable(to_va_macro(hw), false);
पूर्ण

अटल पूर्णांक fsgen_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा va_macro *va = to_va_macro(hw);
	पूर्णांक val;

	regmap_पढ़ो(va->regmap, CDC_VA_TOP_CSR_TOP_CFG0, &val);

	वापस  !!(val & CDC_VA_FS_BROADCAST_EN);
पूर्ण

अटल स्थिर काष्ठा clk_ops fsgen_gate_ops = अणु
	.prepare = fsgen_gate_enable,
	.unprepare = fsgen_gate_disable,
	.is_enabled = fsgen_gate_is_enabled,
पूर्ण;

अटल पूर्णांक va_macro_रेजिस्टर_fsgen_output(काष्ठा va_macro *va)
अणु
	काष्ठा clk *parent = va->clks[2].clk;
	काष्ठा device *dev = va->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *parent_clk_name;
	स्थिर अक्षर *clk_name = "fsgen";
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	parent_clk_name = __clk_get_name(parent);

	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = &fsgen_gate_ops;
	init.flags = 0;
	init.parent_names = &parent_clk_name;
	init.num_parents = 1;
	va->hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(va->dev, &va->hw);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, &va->hw);
पूर्ण

अटल पूर्णांक va_macro_validate_dmic_sample_rate(u32 dmic_sample_rate,
					      काष्ठा va_macro *va)
अणु
	u32 भाग_factor;
	u32 mclk_rate = VA_MACRO_MCLK_FREQ;

	अगर (!dmic_sample_rate || mclk_rate % dmic_sample_rate != 0)
		जाओ undefined_rate;

	भाग_factor = mclk_rate / dmic_sample_rate;

	चयन (भाग_factor) अणु
	हाल 2:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_2;
		अवरोध;
	हाल 3:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_3;
		अवरोध;
	हाल 4:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_4;
		अवरोध;
	हाल 6:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_6;
		अवरोध;
	हाल 8:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_8;
		अवरोध;
	हाल 16:
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_16;
		अवरोध;
	शेष:
		/* Any other DIV factor is invalid */
		जाओ undefined_rate;
	पूर्ण

	वापस dmic_sample_rate;

undefined_rate:
	dev_err(va->dev, "%s: Invalid rate %d, for mclk %d\n",
		__func__, dmic_sample_rate, mclk_rate);
	dmic_sample_rate = 0;

	वापस dmic_sample_rate;
पूर्ण

अटल पूर्णांक va_macro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा va_macro *va;
	व्योम __iomem *base;
	u32 sample_rate = 0;
	पूर्णांक ret;

	va = devm_kzalloc(dev, माप(*va), GFP_KERNEL);
	अगर (!va)
		वापस -ENOMEM;

	va->dev = dev;
	va->clks[0].id = "macro";
	va->clks[1].id = "dcodec";
	va->clks[2].id = "mclk";

	ret = devm_clk_bulk_get(dev, VA_NUM_CLKS_MAX, va->clks);
	अगर (ret) अणु
		dev_err(dev, "Error getting VA Clocks (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "qcom,dmic-sample-rate",
				   &sample_rate);
	अगर (ret) अणु
		dev_err(dev, "qcom,dmic-sample-rate dt entry missing\n");
		va->dmic_clk_भाग = VA_MACRO_CLK_DIV_2;
	पूर्ण अन्यथा अणु
		ret = va_macro_validate_dmic_sample_rate(sample_rate, va);
		अगर (!ret)
			वापस -EINVAL;
	पूर्ण

	/* mclk rate */
	clk_set_rate(va->clks[1].clk, VA_MACRO_MCLK_FREQ);
	ret = clk_bulk_prepare_enable(VA_NUM_CLKS_MAX, va->clks);
	अगर (ret)
		वापस ret;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ err;
	पूर्ण

	va->regmap = devm_regmap_init_mmio(dev, base,  &va_regmap_config);
	अगर (IS_ERR(va->regmap)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev_set_drvdata(dev, va);
	ret = va_macro_रेजिस्टर_fsgen_output(va);
	अगर (ret)
		जाओ err;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &va_macro_component_drv,
					      va_macro_dais,
					      ARRAY_SIZE(va_macro_dais));
	अगर (ret)
		जाओ err;

	वापस ret;

err:
	clk_bulk_disable_unprepare(VA_NUM_CLKS_MAX, va->clks);

	वापस ret;
पूर्ण

अटल पूर्णांक va_macro_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा va_macro *va = dev_get_drvdata(&pdev->dev);

	clk_bulk_disable_unprepare(VA_NUM_CLKS_MAX, va->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id va_macro_dt_match[] = अणु
	अणु .compatible = "qcom,sm8250-lpass-va-macro" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, va_macro_dt_match);

अटल काष्ठा platक्रमm_driver va_macro_driver = अणु
	.driver = अणु
		.name = "va_macro",
		.of_match_table = va_macro_dt_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = va_macro_probe,
	.हटाओ = va_macro_हटाओ,
पूर्ण;

module_platक्रमm_driver(va_macro_driver);
MODULE_DESCRIPTION("VA macro driver");
MODULE_LICENSE("GPL");
