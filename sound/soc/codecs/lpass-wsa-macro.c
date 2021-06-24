<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/tlv.h>
#समावेश "lpass-wsa-macro.h"

#घोषणा CDC_WSA_CLK_RST_CTRL_MCLK_CONTROL	(0x0000)
#घोषणा CDC_WSA_MCLK_EN_MASK			BIT(0)
#घोषणा CDC_WSA_MCLK_ENABLE			BIT(0)
#घोषणा CDC_WSA_MCLK_DISABLE			0
#घोषणा CDC_WSA_CLK_RST_CTRL_FS_CNT_CONTROL	(0x0004)
#घोषणा CDC_WSA_FS_CNT_EN_MASK			BIT(0)
#घोषणा CDC_WSA_FS_CNT_ENABLE			BIT(0)
#घोषणा CDC_WSA_FS_CNT_DISABLE			0
#घोषणा CDC_WSA_CLK_RST_CTRL_SWR_CONTROL	(0x0008)
#घोषणा CDC_WSA_SWR_CLK_EN_MASK			BIT(0)
#घोषणा CDC_WSA_SWR_CLK_ENABLE			BIT(0)
#घोषणा CDC_WSA_SWR_RST_EN_MASK			BIT(1)
#घोषणा CDC_WSA_SWR_RST_ENABLE			BIT(1)
#घोषणा CDC_WSA_SWR_RST_DISABLE			0
#घोषणा CDC_WSA_TOP_TOP_CFG0			(0x0080)
#घोषणा CDC_WSA_TOP_TOP_CFG1			(0x0084)
#घोषणा CDC_WSA_TOP_FREQ_MCLK			(0x0088)
#घोषणा CDC_WSA_TOP_DEBUG_BUS_SEL		(0x008C)
#घोषणा CDC_WSA_TOP_DEBUG_EN0			(0x0090)
#घोषणा CDC_WSA_TOP_DEBUG_EN1			(0x0094)
#घोषणा CDC_WSA_TOP_DEBUG_DSM_LB		(0x0098)
#घोषणा CDC_WSA_TOP_RX_I2S_CTL			(0x009C)
#घोषणा CDC_WSA_TOP_TX_I2S_CTL			(0x00A0)
#घोषणा CDC_WSA_TOP_I2S_CLK			(0x00A4)
#घोषणा CDC_WSA_TOP_I2S_RESET			(0x00A8)
#घोषणा CDC_WSA_RX_INP_MUX_RX_INT0_CFG0		(0x0100)
#घोषणा CDC_WSA_RX_INTX_1_MIX_INP0_SEL_MASK	GENMASK(2, 0)
#घोषणा CDC_WSA_RX_INTX_1_MIX_INP1_SEL_MASK	GENMASK(5, 3)
#घोषणा CDC_WSA_RX_INP_MUX_RX_INT0_CFG1		(0x0104)
#घोषणा CDC_WSA_RX_INTX_2_SEL_MASK		GENMASK(2, 0)
#घोषणा CDC_WSA_RX_INTX_1_MIX_INP2_SEL_MASK	GENMASK(5, 3)
#घोषणा CDC_WSA_RX_INP_MUX_RX_INT1_CFG0		(0x0108)
#घोषणा CDC_WSA_RX_INP_MUX_RX_INT1_CFG1		(0x010C)
#घोषणा CDC_WSA_RX_INP_MUX_RX_MIX_CFG0		(0x0110)
#घोषणा CDC_WSA_RX_MIX_TX1_SEL_MASK		GENMASK(5, 3)
#घोषणा CDC_WSA_RX_MIX_TX1_SEL_SHFT		3
#घोषणा CDC_WSA_RX_MIX_TX0_SEL_MASK		GENMASK(2, 0)
#घोषणा CDC_WSA_RX_INP_MUX_RX_EC_CFG0		(0x0114)
#घोषणा CDC_WSA_RX_INP_MUX_SOFTCLIP_CFG0	(0x0118)
#घोषणा CDC_WSA_TX0_SPKR_PROT_PATH_CTL		(0x0244)
#घोषणा CDC_WSA_TX_SPKR_PROT_RESET_MASK		BIT(5)
#घोषणा CDC_WSA_TX_SPKR_PROT_RESET		BIT(5)
#घोषणा CDC_WSA_TX_SPKR_PROT_NO_RESET		0
#घोषणा CDC_WSA_TX_SPKR_PROT_CLK_EN_MASK	BIT(4)
#घोषणा CDC_WSA_TX_SPKR_PROT_CLK_ENABLE		BIT(4)
#घोषणा CDC_WSA_TX_SPKR_PROT_CLK_DISABLE	0
#घोषणा CDC_WSA_TX_SPKR_PROT_PCM_RATE_MASK	GENMASK(3, 0)
#घोषणा CDC_WSA_TX_SPKR_PROT_PCM_RATE_8K	0
#घोषणा CDC_WSA_TX0_SPKR_PROT_PATH_CFG0		(0x0248)
#घोषणा CDC_WSA_TX1_SPKR_PROT_PATH_CTL		(0x0264)
#घोषणा CDC_WSA_TX1_SPKR_PROT_PATH_CFG0		(0x0268)
#घोषणा CDC_WSA_TX2_SPKR_PROT_PATH_CTL		(0x0284)
#घोषणा CDC_WSA_TX2_SPKR_PROT_PATH_CFG0		(0x0288)
#घोषणा CDC_WSA_TX3_SPKR_PROT_PATH_CTL		(0x02A4)
#घोषणा CDC_WSA_TX3_SPKR_PROT_PATH_CFG0		(0x02A8)
#घोषणा CDC_WSA_INTR_CTRL_CFG			(0x0340)
#घोषणा CDC_WSA_INTR_CTRL_CLR_COMMIT		(0x0344)
#घोषणा CDC_WSA_INTR_CTRL_PIN1_MASK0		(0x0360)
#घोषणा CDC_WSA_INTR_CTRL_PIN1_STATUS0		(0x0368)
#घोषणा CDC_WSA_INTR_CTRL_PIN1_CLEAR0		(0x0370)
#घोषणा CDC_WSA_INTR_CTRL_PIN2_MASK0		(0x0380)
#घोषणा CDC_WSA_INTR_CTRL_PIN2_STATUS0		(0x0388)
#घोषणा CDC_WSA_INTR_CTRL_PIN2_CLEAR0		(0x0390)
#घोषणा CDC_WSA_INTR_CTRL_LEVEL0		(0x03C0)
#घोषणा CDC_WSA_INTR_CTRL_BYPASS0		(0x03C8)
#घोषणा CDC_WSA_INTR_CTRL_SET0			(0x03D0)
#घोषणा CDC_WSA_RX0_RX_PATH_CTL			(0x0400)
#घोषणा CDC_WSA_RX_PATH_CLK_EN_MASK		BIT(5)
#घोषणा CDC_WSA_RX_PATH_CLK_ENABLE		BIT(5)
#घोषणा CDC_WSA_RX_PATH_CLK_DISABLE		0
#घोषणा CDC_WSA_RX_PATH_PGA_MUTE_EN_MASK	BIT(4)
#घोषणा CDC_WSA_RX_PATH_PGA_MUTE_ENABLE		BIT(4)
#घोषणा CDC_WSA_RX_PATH_PGA_MUTE_DISABLE	0
#घोषणा CDC_WSA_RX0_RX_PATH_CFG0		(0x0404)
#घोषणा CDC_WSA_RX_PATH_COMP_EN_MASK		BIT(1)
#घोषणा CDC_WSA_RX_PATH_COMP_ENABLE		BIT(1)
#घोषणा CDC_WSA_RX_PATH_HD2_EN_MASK		BIT(2)
#घोषणा CDC_WSA_RX_PATH_HD2_ENABLE		BIT(2)
#घोषणा CDC_WSA_RX_PATH_SPKR_RATE_MASK		BIT(3)
#घोषणा CDC_WSA_RX_PATH_SPKR_RATE_FS_2P4_3P072	BIT(3)
#घोषणा CDC_WSA_RX0_RX_PATH_CFG1		(0x0408)
#घोषणा CDC_WSA_RX_PATH_SMART_BST_EN_MASK	BIT(0)
#घोषणा CDC_WSA_RX_PATH_SMART_BST_ENABLE	BIT(0)
#घोषणा CDC_WSA_RX_PATH_SMART_BST_DISABLE	0
#घोषणा CDC_WSA_RX0_RX_PATH_CFG2		(0x040C)
#घोषणा CDC_WSA_RX0_RX_PATH_CFG3		(0x0410)
#घोषणा CDC_WSA_RX_DC_DCOEFF_MASK		GENMASK(1, 0)
#घोषणा CDC_WSA_RX0_RX_VOL_CTL			(0x0414)
#घोषणा CDC_WSA_RX0_RX_PATH_MIX_CTL		(0x0418)
#घोषणा CDC_WSA_RX_PATH_MIX_CLK_EN_MASK		BIT(5)
#घोषणा CDC_WSA_RX_PATH_MIX_CLK_ENABLE		BIT(5)
#घोषणा CDC_WSA_RX_PATH_MIX_CLK_DISABLE		0
#घोषणा CDC_WSA_RX0_RX_PATH_MIX_CFG		(0x041C)
#घोषणा CDC_WSA_RX0_RX_VOL_MIX_CTL		(0x0420)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC0		(0x0424)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC1		(0x0428)
#घोषणा CDC_WSA_RX_PGA_HALF_DB_MASK		BIT(0)
#घोषणा CDC_WSA_RX_PGA_HALF_DB_ENABLE		BIT(0)
#घोषणा CDC_WSA_RX_PGA_HALF_DB_DISABLE		0
#घोषणा CDC_WSA_RX0_RX_PATH_SEC2		(0x042C)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC3		(0x0430)
#घोषणा CDC_WSA_RX_PATH_HD2_SCALE_MASK		GENMASK(1, 0)
#घोषणा CDC_WSA_RX_PATH_HD2_ALPHA_MASK		GENMASK(5, 2)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC5		(0x0438)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC6		(0x043C)
#घोषणा CDC_WSA_RX0_RX_PATH_SEC7		(0x0440)
#घोषणा CDC_WSA_RX0_RX_PATH_MIX_SEC0		(0x0444)
#घोषणा CDC_WSA_RX0_RX_PATH_MIX_SEC1		(0x0448)
#घोषणा CDC_WSA_RX0_RX_PATH_DSMDEM_CTL		(0x044C)
#घोषणा CDC_WSA_RX_DSMDEM_CLK_EN_MASK		BIT(0)
#घोषणा CDC_WSA_RX_DSMDEM_CLK_ENABLE		BIT(0)
#घोषणा CDC_WSA_RX1_RX_PATH_CTL			(0x0480)
#घोषणा CDC_WSA_RX1_RX_PATH_CFG0		(0x0484)
#घोषणा CDC_WSA_RX1_RX_PATH_CFG1		(0x0488)
#घोषणा CDC_WSA_RX1_RX_PATH_CFG2		(0x048C)
#घोषणा CDC_WSA_RX1_RX_PATH_CFG3		(0x0490)
#घोषणा CDC_WSA_RX1_RX_VOL_CTL			(0x0494)
#घोषणा CDC_WSA_RX1_RX_PATH_MIX_CTL		(0x0498)
#घोषणा CDC_WSA_RX1_RX_PATH_MIX_CFG		(0x049C)
#घोषणा CDC_WSA_RX1_RX_VOL_MIX_CTL		(0x04A0)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC0		(0x04A4)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC1		(0x04A8)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC2		(0x04AC)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC3		(0x04B0)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC5		(0x04B8)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC6		(0x04BC)
#घोषणा CDC_WSA_RX1_RX_PATH_SEC7		(0x04C0)
#घोषणा CDC_WSA_RX1_RX_PATH_MIX_SEC0		(0x04C4)
#घोषणा CDC_WSA_RX1_RX_PATH_MIX_SEC1		(0x04C8)
#घोषणा CDC_WSA_RX1_RX_PATH_DSMDEM_CTL		(0x04CC)
#घोषणा CDC_WSA_BOOST0_BOOST_PATH_CTL		(0x0500)
#घोषणा CDC_WSA_BOOST_PATH_CLK_EN_MASK		BIT(4)
#घोषणा CDC_WSA_BOOST_PATH_CLK_ENABLE		BIT(4)
#घोषणा CDC_WSA_BOOST_PATH_CLK_DISABLE		0
#घोषणा CDC_WSA_BOOST0_BOOST_CTL		(0x0504)
#घोषणा CDC_WSA_BOOST0_BOOST_CFG1		(0x0508)
#घोषणा CDC_WSA_BOOST0_BOOST_CFG2		(0x050C)
#घोषणा CDC_WSA_BOOST1_BOOST_PATH_CTL		(0x0540)
#घोषणा CDC_WSA_BOOST1_BOOST_CTL		(0x0544)
#घोषणा CDC_WSA_BOOST1_BOOST_CFG1		(0x0548)
#घोषणा CDC_WSA_BOOST1_BOOST_CFG2		(0x054C)
#घोषणा CDC_WSA_COMPANDER0_CTL0			(0x0580)
#घोषणा CDC_WSA_COMPANDER_CLK_EN_MASK		BIT(0)
#घोषणा CDC_WSA_COMPANDER_CLK_ENABLE		BIT(0)
#घोषणा CDC_WSA_COMPANDER_SOFT_RST_MASK		BIT(1)
#घोषणा CDC_WSA_COMPANDER_SOFT_RST_ENABLE	BIT(1)
#घोषणा CDC_WSA_COMPANDER_HALT_MASK		BIT(2)
#घोषणा CDC_WSA_COMPANDER_HALT			BIT(2)
#घोषणा CDC_WSA_COMPANDER0_CTL1			(0x0584)
#घोषणा CDC_WSA_COMPANDER0_CTL2			(0x0588)
#घोषणा CDC_WSA_COMPANDER0_CTL3			(0x058C)
#घोषणा CDC_WSA_COMPANDER0_CTL4			(0x0590)
#घोषणा CDC_WSA_COMPANDER0_CTL5			(0x0594)
#घोषणा CDC_WSA_COMPANDER0_CTL6			(0x0598)
#घोषणा CDC_WSA_COMPANDER0_CTL7			(0x059C)
#घोषणा CDC_WSA_COMPANDER1_CTL0			(0x05C0)
#घोषणा CDC_WSA_COMPANDER1_CTL1			(0x05C4)
#घोषणा CDC_WSA_COMPANDER1_CTL2			(0x05C8)
#घोषणा CDC_WSA_COMPANDER1_CTL3			(0x05CC)
#घोषणा CDC_WSA_COMPANDER1_CTL4			(0x05D0)
#घोषणा CDC_WSA_COMPANDER1_CTL5			(0x05D4)
#घोषणा CDC_WSA_COMPANDER1_CTL6			(0x05D8)
#घोषणा CDC_WSA_COMPANDER1_CTL7			(0x05DC)
#घोषणा CDC_WSA_SOFTCLIP0_CRC			(0x0600)
#घोषणा CDC_WSA_SOFTCLIP_CLK_EN_MASK		BIT(0)
#घोषणा CDC_WSA_SOFTCLIP_CLK_ENABLE		BIT(0)
#घोषणा CDC_WSA_SOFTCLIP0_SOFTCLIP_CTRL		(0x0604)
#घोषणा CDC_WSA_SOFTCLIP_EN_MASK		BIT(0)
#घोषणा CDC_WSA_SOFTCLIP_ENABLE			BIT(0)
#घोषणा CDC_WSA_SOFTCLIP1_CRC			(0x0640)
#घोषणा CDC_WSA_SOFTCLIP1_SOFTCLIP_CTRL		(0x0644)
#घोषणा CDC_WSA_EC_HQ0_EC_REF_HQ_PATH_CTL	(0x0680)
#घोषणा CDC_WSA_EC_HQ_EC_CLK_EN_MASK		BIT(0)
#घोषणा CDC_WSA_EC_HQ_EC_CLK_ENABLE		BIT(0)
#घोषणा CDC_WSA_EC_HQ0_EC_REF_HQ_CFG0		(0x0684)
#घोषणा CDC_WSA_EC_HQ_EC_REF_PCM_RATE_MASK	GENMASK(4, 1)
#घोषणा CDC_WSA_EC_HQ_EC_REF_PCM_RATE_48K	BIT(3)
#घोषणा CDC_WSA_EC_HQ1_EC_REF_HQ_PATH_CTL	(0x06C0)
#घोषणा CDC_WSA_EC_HQ1_EC_REF_HQ_CFG0		(0x06C4)
#घोषणा CDC_WSA_SPLINE_ASRC0_CLK_RST_CTL	(0x0700)
#घोषणा CDC_WSA_SPLINE_ASRC0_CTL0		(0x0704)
#घोषणा CDC_WSA_SPLINE_ASRC0_CTL1		(0x0708)
#घोषणा CDC_WSA_SPLINE_ASRC0_FIFO_CTL		(0x070C)
#घोषणा CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_LSB	(0x0710)
#घोषणा CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_MSB	(0x0714)
#घोषणा CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_LSB	(0x0718)
#घोषणा CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_MSB	(0x071C)
#घोषणा CDC_WSA_SPLINE_ASRC0_STATUS_FIFO		(0x0720)
#घोषणा CDC_WSA_SPLINE_ASRC1_CLK_RST_CTL		(0x0740)
#घोषणा CDC_WSA_SPLINE_ASRC1_CTL0		(0x0744)
#घोषणा CDC_WSA_SPLINE_ASRC1_CTL1		(0x0748)
#घोषणा CDC_WSA_SPLINE_ASRC1_FIFO_CTL		(0x074C)
#घोषणा CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_LSB (0x0750)
#घोषणा CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_MSB (0x0754)
#घोषणा CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_LSB (0x0758)
#घोषणा CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_MSB (0x075C)
#घोषणा CDC_WSA_SPLINE_ASRC1_STATUS_FIFO	(0x0760)
#घोषणा WSA_MAX_OFFSET				(0x0760)

#घोषणा WSA_MACRO_RX_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
#घोषणा WSA_MACRO_RX_MIX_RATES (SNDRV_PCM_RATE_48000 |\
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
#घोषणा WSA_MACRO_RX_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
		SNDRV_PCM_FMTBIT_S24_LE |\
		SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा WSA_MACRO_ECHO_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			SNDRV_PCM_RATE_48000)
#घोषणा WSA_MACRO_ECHO_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
		SNDRV_PCM_FMTBIT_S24_LE |\
		SNDRV_PCM_FMTBIT_S24_3LE)

#घोषणा NUM_INTERPOLATORS 2
#घोषणा WSA_NUM_CLKS_MAX	5
#घोषणा WSA_MACRO_MCLK_FREQ 19200000
#घोषणा WSA_MACRO_MUX_INP_MASK2 0x38
#घोषणा WSA_MACRO_MUX_CFG_OFFSET 0x8
#घोषणा WSA_MACRO_MUX_CFG1_OFFSET 0x4
#घोषणा WSA_MACRO_RX_COMP_OFFSET 0x40
#घोषणा WSA_MACRO_RX_SOFTCLIP_OFFSET 0x40
#घोषणा WSA_MACRO_RX_PATH_OFFSET 0x80
#घोषणा WSA_MACRO_RX_PATH_CFG3_OFFSET 0x10
#घोषणा WSA_MACRO_RX_PATH_DSMDEM_OFFSET 0x4C
#घोषणा WSA_MACRO_FS_RATE_MASK 0x0F
#घोषणा WSA_MACRO_EC_MIX_TX0_MASK 0x03
#घोषणा WSA_MACRO_EC_MIX_TX1_MASK 0x18
#घोषणा WSA_MACRO_MAX_DMA_CH_PER_PORT 0x2

क्रमागत अणु
	WSA_MACRO_GAIN_OFFSET_M1P5_DB,
	WSA_MACRO_GAIN_OFFSET_0_DB,
पूर्ण;
क्रमागत अणु
	WSA_MACRO_RX0 = 0,
	WSA_MACRO_RX1,
	WSA_MACRO_RX_MIX,
	WSA_MACRO_RX_MIX0 = WSA_MACRO_RX_MIX,
	WSA_MACRO_RX_MIX1,
	WSA_MACRO_RX_MAX,
पूर्ण;

क्रमागत अणु
	WSA_MACRO_TX0 = 0,
	WSA_MACRO_TX1,
	WSA_MACRO_TX_MAX,
पूर्ण;

क्रमागत अणु
	WSA_MACRO_EC0_MUX = 0,
	WSA_MACRO_EC1_MUX,
	WSA_MACRO_EC_MUX_MAX,
पूर्ण;

क्रमागत अणु
	WSA_MACRO_COMP1, /* SPK_L */
	WSA_MACRO_COMP2, /* SPK_R */
	WSA_MACRO_COMP_MAX
पूर्ण;

क्रमागत अणु
	WSA_MACRO_SOFTCLIP0, /* RX0 */
	WSA_MACRO_SOFTCLIP1, /* RX1 */
	WSA_MACRO_SOFTCLIP_MAX
पूर्ण;

क्रमागत अणु
	INTn_1_INP_SEL_ZERO = 0,
	INTn_1_INP_SEL_RX0,
	INTn_1_INP_SEL_RX1,
	INTn_1_INP_SEL_RX2,
	INTn_1_INP_SEL_RX3,
	INTn_1_INP_SEL_DEC0,
	INTn_1_INP_SEL_DEC1,
पूर्ण;

क्रमागत अणु
	INTn_2_INP_SEL_ZERO = 0,
	INTn_2_INP_SEL_RX0,
	INTn_2_INP_SEL_RX1,
	INTn_2_INP_SEL_RX2,
	INTn_2_INP_SEL_RX3,
पूर्ण;

काष्ठा पूर्णांकerp_sample_rate अणु
	पूर्णांक sample_rate;
	पूर्णांक rate_val;
पूर्ण;

अटल काष्ठा पूर्णांकerp_sample_rate पूर्णांक_prim_sample_rate_val[] = अणु
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

अटल काष्ठा पूर्णांकerp_sample_rate पूर्णांक_mix_sample_rate_val[] = अणु
	अणु48000, 0x4पूर्ण,	/* 48K */
	अणु96000, 0x5पूर्ण,	/* 96K */
	अणु192000, 0x6पूर्ण,	/* 192K */
पूर्ण;

क्रमागत अणु
	WSA_MACRO_AIF_INVALID = 0,
	WSA_MACRO_AIF1_PB,
	WSA_MACRO_AIF_MIX1_PB,
	WSA_MACRO_AIF_VI,
	WSA_MACRO_AIF_ECHO,
	WSA_MACRO_MAX_DAIS,
पूर्ण;

काष्ठा wsa_macro अणु
	काष्ठा device *dev;
	पूर्णांक comp_enabled[WSA_MACRO_COMP_MAX];
	पूर्णांक ec_hq[WSA_MACRO_RX1 + 1];
	u16 prim_पूर्णांक_users[WSA_MACRO_RX1 + 1];
	u16 wsa_mclk_users;
	bool reset_swr;
	अचिन्हित दीर्घ active_ch_mask[WSA_MACRO_MAX_DAIS];
	अचिन्हित दीर्घ active_ch_cnt[WSA_MACRO_MAX_DAIS];
	पूर्णांक rx_port_value[WSA_MACRO_RX_MAX];
	पूर्णांक ear_spkr_gain;
	पूर्णांक spkr_gain_offset;
	पूर्णांक spkr_mode;
	पूर्णांक is_softclip_on[WSA_MACRO_SOFTCLIP_MAX];
	पूर्णांक softclip_clk_users[WSA_MACRO_SOFTCLIP_MAX];
	काष्ठा regmap *regmap;
	काष्ठा clk_bulk_data clks[WSA_NUM_CLKS_MAX];
	काष्ठा clk_hw hw;
पूर्ण;
#घोषणा to_wsa_macro(_hw) container_of(_hw, काष्ठा wsa_macro, hw)

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -8400, 100, -8400);

अटल स्थिर अक्षर *स्थिर rx_text[] = अणु
	"ZERO", "RX0", "RX1", "RX_MIX0", "RX_MIX1", "DEC0", "DEC1"
पूर्ण;

अटल स्थिर अक्षर *स्थिर rx_mix_text[] = अणु
	"ZERO", "RX0", "RX1", "RX_MIX0", "RX_MIX1"
पूर्ण;

अटल स्थिर अक्षर *स्थिर rx_mix_ec_text[] = अणु
	"ZERO", "RX_MIX_TX0", "RX_MIX_TX1"
पूर्ण;

अटल स्थिर अक्षर *स्थिर rx_mux_text[] = अणु
	"ZERO", "AIF1_PB", "AIF_MIX1_PB"
पूर्ण;

अटल स्थिर अक्षर *स्थिर rx_sidetone_mix_text[] = अणु
	"ZERO", "SRC0"
पूर्ण;

अटल स्थिर अक्षर * स्थिर wsa_macro_ear_spkr_pa_gain_text[] = अणु
	"G_DEFAULT", "G_0_DB", "G_1_DB", "G_2_DB", "G_3_DB",
	"G_4_DB", "G_5_DB", "G_6_DB"
पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(wsa_macro_ear_spkr_pa_gain_क्रमागत,
				wsa_macro_ear_spkr_pa_gain_text);

/* RX INT0 */
अटल स्थिर काष्ठा soc_क्रमागत rx0_prim_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT0_CFG0,
		0, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx0_prim_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT0_CFG0,
		3, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx0_prim_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT0_CFG1,
		3, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx0_mix_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT0_CFG1,
		0, 5, rx_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx0_sidetone_mix_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, 2, rx_sidetone_mix_text);

अटल स्थिर काष्ठा snd_kcontrol_new rx0_prim_inp0_mux =
	SOC_DAPM_ENUM("WSA_RX0 INP0 Mux", rx0_prim_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx0_prim_inp1_mux =
	SOC_DAPM_ENUM("WSA_RX0 INP1 Mux", rx0_prim_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx0_prim_inp2_mux =
	SOC_DAPM_ENUM("WSA_RX0 INP2 Mux", rx0_prim_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx0_mix_mux =
	SOC_DAPM_ENUM("WSA_RX0 MIX Mux", rx0_mix_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx0_sidetone_mix_mux =
	SOC_DAPM_ENUM("WSA_RX0 SIDETONE MIX Mux", rx0_sidetone_mix_क्रमागत);

/* RX INT1 */
अटल स्थिर काष्ठा soc_क्रमागत rx1_prim_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT1_CFG0,
		0, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx1_prim_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT1_CFG0,
		3, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx1_prim_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT1_CFG1,
		3, 7, rx_text);

अटल स्थिर काष्ठा soc_क्रमागत rx1_mix_chain_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_INT1_CFG1,
		0, 5, rx_mix_text);

अटल स्थिर काष्ठा snd_kcontrol_new rx1_prim_inp0_mux =
	SOC_DAPM_ENUM("WSA_RX1 INP0 Mux", rx1_prim_inp0_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx1_prim_inp1_mux =
	SOC_DAPM_ENUM("WSA_RX1 INP1 Mux", rx1_prim_inp1_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx1_prim_inp2_mux =
	SOC_DAPM_ENUM("WSA_RX1 INP2 Mux", rx1_prim_inp2_chain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx1_mix_mux =
	SOC_DAPM_ENUM("WSA_RX1 MIX Mux", rx1_mix_chain_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत rx_mix_ec0_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_MIX_CFG0,
		0, 3, rx_mix_ec_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_mix_ec1_क्रमागत =
	SOC_ENUM_SINGLE(CDC_WSA_RX_INP_MUX_RX_MIX_CFG0,
		3, 3, rx_mix_ec_text);

अटल स्थिर काष्ठा snd_kcontrol_new rx_mix_ec0_mux =
	SOC_DAPM_ENUM("WSA RX_MIX EC0_Mux", rx_mix_ec0_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_mix_ec1_mux =
	SOC_DAPM_ENUM("WSA RX_MIX EC1_Mux", rx_mix_ec1_क्रमागत);

अटल स्थिर काष्ठा reg_शेष wsa_शेषs[] = अणु
	/* WSA Macro */
	अणु CDC_WSA_CLK_RST_CTRL_MCLK_CONTROL, 0x00पूर्ण,
	अणु CDC_WSA_CLK_RST_CTRL_FS_CNT_CONTROL, 0x00पूर्ण,
	अणु CDC_WSA_CLK_RST_CTRL_SWR_CONTROL, 0x00पूर्ण,
	अणु CDC_WSA_TOP_TOP_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_TOP_TOP_CFG1, 0x00पूर्ण,
	अणु CDC_WSA_TOP_FREQ_MCLK, 0x00पूर्ण,
	अणु CDC_WSA_TOP_DEBUG_BUS_SEL, 0x00पूर्ण,
	अणु CDC_WSA_TOP_DEBUG_EN0, 0x00पूर्ण,
	अणु CDC_WSA_TOP_DEBUG_EN1, 0x00पूर्ण,
	अणु CDC_WSA_TOP_DEBUG_DSM_LB, 0x88पूर्ण,
	अणु CDC_WSA_TOP_RX_I2S_CTL, 0x0Cपूर्ण,
	अणु CDC_WSA_TOP_TX_I2S_CTL, 0x0Cपूर्ण,
	अणु CDC_WSA_TOP_I2S_CLK, 0x02पूर्ण,
	अणु CDC_WSA_TOP_I2S_RESET, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_INT0_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_INT0_CFG1, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_INT1_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_INT1_CFG1, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_MIX_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_RX_EC_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX_INP_MUX_SOFTCLIP_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_TX0_SPKR_PROT_PATH_CTL, 0x02पूर्ण,
	अणु CDC_WSA_TX0_SPKR_PROT_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_TX1_SPKR_PROT_PATH_CTL, 0x02पूर्ण,
	अणु CDC_WSA_TX1_SPKR_PROT_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_TX2_SPKR_PROT_PATH_CTL, 0x02पूर्ण,
	अणु CDC_WSA_TX2_SPKR_PROT_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_TX3_SPKR_PROT_PATH_CTL, 0x02पूर्ण,
	अणु CDC_WSA_TX3_SPKR_PROT_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_CFG, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_CLR_COMMIT, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN1_MASK0, 0xFFपूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN1_STATUS0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN1_CLEAR0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN2_MASK0, 0xFFपूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN2_STATUS0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_PIN2_CLEAR0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_LEVEL0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_BYPASS0, 0x00पूर्ण,
	अणु CDC_WSA_INTR_CTRL_SET0, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_CTL, 0x04पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_CFG1, 0x64पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_CFG2, 0x8Fपूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_CFG3, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_MIX_CTL, 0x04पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_MIX_CFG, 0x7Eपूर्ण,
	अणु CDC_WSA_RX0_RX_VOL_MIX_CTL, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC0, 0x04पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC1, 0x08पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC2, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC3, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_SEC7, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_MIX_SEC0, 0x08पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_MIX_SEC1, 0x00पूर्ण,
	अणु CDC_WSA_RX0_RX_PATH_DSMDEM_CTL, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_CFG0, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_CFG1, 0x64पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_CFG2, 0x8Fपूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_CFG3, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_VOL_CTL, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_MIX_CTL, 0x04पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_MIX_CFG, 0x7Eपूर्ण,
	अणु CDC_WSA_RX1_RX_VOL_MIX_CTL, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC0, 0x04पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC1, 0x08पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC2, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC3, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC5, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC6, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_SEC7, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_MIX_SEC0, 0x08पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_MIX_SEC1, 0x00पूर्ण,
	अणु CDC_WSA_RX1_RX_PATH_DSMDEM_CTL, 0x00पूर्ण,
	अणु CDC_WSA_BOOST0_BOOST_PATH_CTL, 0x00पूर्ण,
	अणु CDC_WSA_BOOST0_BOOST_CTL, 0xD0पूर्ण,
	अणु CDC_WSA_BOOST0_BOOST_CFG1, 0x89पूर्ण,
	अणु CDC_WSA_BOOST0_BOOST_CFG2, 0x04पूर्ण,
	अणु CDC_WSA_BOOST1_BOOST_PATH_CTL, 0x00पूर्ण,
	अणु CDC_WSA_BOOST1_BOOST_CTL, 0xD0पूर्ण,
	अणु CDC_WSA_BOOST1_BOOST_CFG1, 0x89पूर्ण,
	अणु CDC_WSA_BOOST1_BOOST_CFG2, 0x04पूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL0, 0x60पूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL1, 0xDBपूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL2, 0xFFपूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL3, 0x35पूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL4, 0xFFपूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL5, 0x00पूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL6, 0x01पूर्ण,
	अणु CDC_WSA_COMPANDER0_CTL7, 0x28पूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL0, 0x60पूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL1, 0xDBपूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL2, 0xFFपूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL3, 0x35पूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL4, 0xFFपूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL5, 0x00पूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL6, 0x01पूर्ण,
	अणु CDC_WSA_COMPANDER1_CTL7, 0x28पूर्ण,
	अणु CDC_WSA_SOFTCLIP0_CRC, 0x00पूर्ण,
	अणु CDC_WSA_SOFTCLIP0_SOFTCLIP_CTRL, 0x38पूर्ण,
	अणु CDC_WSA_SOFTCLIP1_CRC, 0x00पूर्ण,
	अणु CDC_WSA_SOFTCLIP1_SOFTCLIP_CTRL, 0x38पूर्ण,
	अणु CDC_WSA_EC_HQ0_EC_REF_HQ_PATH_CTL, 0x00पूर्ण,
	अणु CDC_WSA_EC_HQ0_EC_REF_HQ_CFG0, 0x01पूर्ण,
	अणु CDC_WSA_EC_HQ1_EC_REF_HQ_PATH_CTL, 0x00पूर्ण,
	अणु CDC_WSA_EC_HQ1_EC_REF_HQ_CFG0, 0x01पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_CLK_RST_CTL, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_CTL0, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_CTL1, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_FIFO_CTL, 0xA8पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_LSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_MSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_LSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_MSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC0_STATUS_FIFO, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_CLK_RST_CTL, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_CTL0, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_CTL1, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_FIFO_CTL, 0xA8पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_LSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_MSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_LSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_MSB, 0x00पूर्ण,
	अणु CDC_WSA_SPLINE_ASRC1_STATUS_FIFO, 0x00पूर्ण,
पूर्ण;

अटल bool wsa_is_wronly_रेजिस्टर(काष्ठा device *dev,
					अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_WSA_INTR_CTRL_CLR_COMMIT:
	हाल CDC_WSA_INTR_CTRL_PIN1_CLEAR0:
	हाल CDC_WSA_INTR_CTRL_PIN2_CLEAR0:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool wsa_is_rw_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_WSA_CLK_RST_CTRL_MCLK_CONTROL:
	हाल CDC_WSA_CLK_RST_CTRL_FS_CNT_CONTROL:
	हाल CDC_WSA_CLK_RST_CTRL_SWR_CONTROL:
	हाल CDC_WSA_TOP_TOP_CFG0:
	हाल CDC_WSA_TOP_TOP_CFG1:
	हाल CDC_WSA_TOP_FREQ_MCLK:
	हाल CDC_WSA_TOP_DEBUG_BUS_SEL:
	हाल CDC_WSA_TOP_DEBUG_EN0:
	हाल CDC_WSA_TOP_DEBUG_EN1:
	हाल CDC_WSA_TOP_DEBUG_DSM_LB:
	हाल CDC_WSA_TOP_RX_I2S_CTL:
	हाल CDC_WSA_TOP_TX_I2S_CTL:
	हाल CDC_WSA_TOP_I2S_CLK:
	हाल CDC_WSA_TOP_I2S_RESET:
	हाल CDC_WSA_RX_INP_MUX_RX_INT0_CFG0:
	हाल CDC_WSA_RX_INP_MUX_RX_INT0_CFG1:
	हाल CDC_WSA_RX_INP_MUX_RX_INT1_CFG0:
	हाल CDC_WSA_RX_INP_MUX_RX_INT1_CFG1:
	हाल CDC_WSA_RX_INP_MUX_RX_MIX_CFG0:
	हाल CDC_WSA_RX_INP_MUX_RX_EC_CFG0:
	हाल CDC_WSA_RX_INP_MUX_SOFTCLIP_CFG0:
	हाल CDC_WSA_TX0_SPKR_PROT_PATH_CTL:
	हाल CDC_WSA_TX0_SPKR_PROT_PATH_CFG0:
	हाल CDC_WSA_TX1_SPKR_PROT_PATH_CTL:
	हाल CDC_WSA_TX1_SPKR_PROT_PATH_CFG0:
	हाल CDC_WSA_TX2_SPKR_PROT_PATH_CTL:
	हाल CDC_WSA_TX2_SPKR_PROT_PATH_CFG0:
	हाल CDC_WSA_TX3_SPKR_PROT_PATH_CTL:
	हाल CDC_WSA_TX3_SPKR_PROT_PATH_CFG0:
	हाल CDC_WSA_INTR_CTRL_CFG:
	हाल CDC_WSA_INTR_CTRL_PIN1_MASK0:
	हाल CDC_WSA_INTR_CTRL_PIN2_MASK0:
	हाल CDC_WSA_INTR_CTRL_LEVEL0:
	हाल CDC_WSA_INTR_CTRL_BYPASS0:
	हाल CDC_WSA_INTR_CTRL_SET0:
	हाल CDC_WSA_RX0_RX_PATH_CTL:
	हाल CDC_WSA_RX0_RX_PATH_CFG0:
	हाल CDC_WSA_RX0_RX_PATH_CFG1:
	हाल CDC_WSA_RX0_RX_PATH_CFG2:
	हाल CDC_WSA_RX0_RX_PATH_CFG3:
	हाल CDC_WSA_RX0_RX_VOL_CTL:
	हाल CDC_WSA_RX0_RX_PATH_MIX_CTL:
	हाल CDC_WSA_RX0_RX_PATH_MIX_CFG:
	हाल CDC_WSA_RX0_RX_VOL_MIX_CTL:
	हाल CDC_WSA_RX0_RX_PATH_SEC0:
	हाल CDC_WSA_RX0_RX_PATH_SEC1:
	हाल CDC_WSA_RX0_RX_PATH_SEC2:
	हाल CDC_WSA_RX0_RX_PATH_SEC3:
	हाल CDC_WSA_RX0_RX_PATH_SEC5:
	हाल CDC_WSA_RX0_RX_PATH_SEC6:
	हाल CDC_WSA_RX0_RX_PATH_SEC7:
	हाल CDC_WSA_RX0_RX_PATH_MIX_SEC0:
	हाल CDC_WSA_RX0_RX_PATH_MIX_SEC1:
	हाल CDC_WSA_RX0_RX_PATH_DSMDEM_CTL:
	हाल CDC_WSA_RX1_RX_PATH_CTL:
	हाल CDC_WSA_RX1_RX_PATH_CFG0:
	हाल CDC_WSA_RX1_RX_PATH_CFG1:
	हाल CDC_WSA_RX1_RX_PATH_CFG2:
	हाल CDC_WSA_RX1_RX_PATH_CFG3:
	हाल CDC_WSA_RX1_RX_VOL_CTL:
	हाल CDC_WSA_RX1_RX_PATH_MIX_CTL:
	हाल CDC_WSA_RX1_RX_PATH_MIX_CFG:
	हाल CDC_WSA_RX1_RX_VOL_MIX_CTL:
	हाल CDC_WSA_RX1_RX_PATH_SEC0:
	हाल CDC_WSA_RX1_RX_PATH_SEC1:
	हाल CDC_WSA_RX1_RX_PATH_SEC2:
	हाल CDC_WSA_RX1_RX_PATH_SEC3:
	हाल CDC_WSA_RX1_RX_PATH_SEC5:
	हाल CDC_WSA_RX1_RX_PATH_SEC6:
	हाल CDC_WSA_RX1_RX_PATH_SEC7:
	हाल CDC_WSA_RX1_RX_PATH_MIX_SEC0:
	हाल CDC_WSA_RX1_RX_PATH_MIX_SEC1:
	हाल CDC_WSA_RX1_RX_PATH_DSMDEM_CTL:
	हाल CDC_WSA_BOOST0_BOOST_PATH_CTL:
	हाल CDC_WSA_BOOST0_BOOST_CTL:
	हाल CDC_WSA_BOOST0_BOOST_CFG1:
	हाल CDC_WSA_BOOST0_BOOST_CFG2:
	हाल CDC_WSA_BOOST1_BOOST_PATH_CTL:
	हाल CDC_WSA_BOOST1_BOOST_CTL:
	हाल CDC_WSA_BOOST1_BOOST_CFG1:
	हाल CDC_WSA_BOOST1_BOOST_CFG2:
	हाल CDC_WSA_COMPANDER0_CTL0:
	हाल CDC_WSA_COMPANDER0_CTL1:
	हाल CDC_WSA_COMPANDER0_CTL2:
	हाल CDC_WSA_COMPANDER0_CTL3:
	हाल CDC_WSA_COMPANDER0_CTL4:
	हाल CDC_WSA_COMPANDER0_CTL5:
	हाल CDC_WSA_COMPANDER0_CTL7:
	हाल CDC_WSA_COMPANDER1_CTL0:
	हाल CDC_WSA_COMPANDER1_CTL1:
	हाल CDC_WSA_COMPANDER1_CTL2:
	हाल CDC_WSA_COMPANDER1_CTL3:
	हाल CDC_WSA_COMPANDER1_CTL4:
	हाल CDC_WSA_COMPANDER1_CTL5:
	हाल CDC_WSA_COMPANDER1_CTL7:
	हाल CDC_WSA_SOFTCLIP0_CRC:
	हाल CDC_WSA_SOFTCLIP0_SOFTCLIP_CTRL:
	हाल CDC_WSA_SOFTCLIP1_CRC:
	हाल CDC_WSA_SOFTCLIP1_SOFTCLIP_CTRL:
	हाल CDC_WSA_EC_HQ0_EC_REF_HQ_PATH_CTL:
	हाल CDC_WSA_EC_HQ0_EC_REF_HQ_CFG0:
	हाल CDC_WSA_EC_HQ1_EC_REF_HQ_PATH_CTL:
	हाल CDC_WSA_EC_HQ1_EC_REF_HQ_CFG0:
	हाल CDC_WSA_SPLINE_ASRC0_CLK_RST_CTL:
	हाल CDC_WSA_SPLINE_ASRC0_CTL0:
	हाल CDC_WSA_SPLINE_ASRC0_CTL1:
	हाल CDC_WSA_SPLINE_ASRC0_FIFO_CTL:
	हाल CDC_WSA_SPLINE_ASRC1_CLK_RST_CTL:
	हाल CDC_WSA_SPLINE_ASRC1_CTL0:
	हाल CDC_WSA_SPLINE_ASRC1_CTL1:
	हाल CDC_WSA_SPLINE_ASRC1_FIFO_CTL:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool wsa_is_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool ret;

	ret = wsa_is_rw_रेजिस्टर(dev, reg);
	अगर (!ret)
		वापस wsa_is_wronly_रेजिस्टर(dev, reg);

	वापस ret;
पूर्ण

अटल bool wsa_is_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CDC_WSA_INTR_CTRL_CLR_COMMIT:
	हाल CDC_WSA_INTR_CTRL_PIN1_CLEAR0:
	हाल CDC_WSA_INTR_CTRL_PIN2_CLEAR0:
	हाल CDC_WSA_INTR_CTRL_PIN1_STATUS0:
	हाल CDC_WSA_INTR_CTRL_PIN2_STATUS0:
	हाल CDC_WSA_COMPANDER0_CTL6:
	हाल CDC_WSA_COMPANDER1_CTL6:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FIFO:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FIFO:
		वापस true;
	पूर्ण

	वापस wsa_is_rw_रेजिस्टर(dev, reg);
पूर्ण

अटल bool wsa_is_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Update अस्थिर list क्रम rx/tx macros */
	चयन (reg) अणु
	हाल CDC_WSA_INTR_CTRL_PIN1_STATUS0:
	हाल CDC_WSA_INTR_CTRL_PIN2_STATUS0:
	हाल CDC_WSA_COMPANDER0_CTL6:
	हाल CDC_WSA_COMPANDER1_CTL6:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMIN_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FMAX_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC0_STATUS_FIFO:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMIN_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_LSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FMAX_CNTR_MSB:
	हाल CDC_WSA_SPLINE_ASRC1_STATUS_FIFO:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config wsa_regmap_config = अणु
	.name = "wsa_macro",
	.reg_bits = 16,
	.val_bits = 32, /* 8 but with 32 bit पढ़ो/ग_लिखो */
	.reg_stride = 4,
	.cache_type = REGCACHE_FLAT,
	.reg_शेषs = wsa_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wsa_शेषs),
	.max_रेजिस्टर = WSA_MAX_OFFSET,
	.ग_लिखोable_reg = wsa_is_ग_लिखोable_रेजिस्टर,
	.अस्थिर_reg = wsa_is_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wsa_is_पढ़ोable_रेजिस्टर,
पूर्ण;

/**
 * wsa_macro_set_spkr_mode - Configures speaker compander and smartboost
 * settings based on speaker mode.
 *
 * @component: codec instance
 * @mode: Indicates speaker configuration mode.
 *
 * Returns 0 on success or -EINVAL on error.
 */
पूर्णांक wsa_macro_set_spkr_mode(काष्ठा snd_soc_component *component, पूर्णांक mode)
अणु
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	wsa->spkr_mode = mode;

	चयन (mode) अणु
	हाल WSA_MACRO_SPKR_MODE_1:
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER0_CTL3, 0x80, 0x00);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER1_CTL3, 0x80, 0x00);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER0_CTL7, 0x01, 0x00);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER1_CTL7, 0x01, 0x00);
		snd_soc_component_update_bits(component, CDC_WSA_BOOST0_BOOST_CTL, 0x7C, 0x44);
		snd_soc_component_update_bits(component, CDC_WSA_BOOST1_BOOST_CTL, 0x7C, 0x44);
		अवरोध;
	शेष:
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER0_CTL3, 0x80, 0x80);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER1_CTL3, 0x80, 0x80);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER0_CTL7, 0x01, 0x01);
		snd_soc_component_update_bits(component, CDC_WSA_COMPANDER1_CTL7, 0x01, 0x01);
		snd_soc_component_update_bits(component, CDC_WSA_BOOST0_BOOST_CTL, 0x7C, 0x58);
		snd_soc_component_update_bits(component, CDC_WSA_BOOST1_BOOST_CTL, 0x7C, 0x58);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(wsa_macro_set_spkr_mode);

अटल पूर्णांक wsa_macro_set_prim_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
						u8 पूर्णांक_prim_fs_rate_reg_val,
						u32 sample_rate)
अणु
	u8 पूर्णांक_1_mix1_inp;
	u32 j, port;
	u16 पूर्णांक_mux_cfg0, पूर्णांक_mux_cfg1;
	u16 पूर्णांक_fs_reg;
	u8 inp0_sel, inp1_sel, inp2_sel;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	क्रम_each_set_bit(port, &wsa->active_ch_mask[dai->id], WSA_MACRO_RX_MAX) अणु
		पूर्णांक_1_mix1_inp = port;
		अगर ((पूर्णांक_1_mix1_inp < WSA_MACRO_RX0) || (पूर्णांक_1_mix1_inp > WSA_MACRO_RX_MIX1)) अणु
			dev_err(component->dev,	"%s: Invalid RX port, Dai ID is %d\n",
				__func__, dai->id);
			वापस -EINVAL;
		पूर्ण

		पूर्णांक_mux_cfg0 = CDC_WSA_RX_INP_MUX_RX_INT0_CFG0;

		/*
		 * Loop through all पूर्णांकerpolator MUX inमाला_दो and find out
		 * to which पूर्णांकerpolator input, the cdc_dma rx port
		 * is connected
		 */
		क्रम (j = 0; j < NUM_INTERPOLATORS; j++) अणु
			पूर्णांक_mux_cfg1 = पूर्णांक_mux_cfg0 + WSA_MACRO_MUX_CFG1_OFFSET;
			inp0_sel = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg0, 
								CDC_WSA_RX_INTX_1_MIX_INP0_SEL_MASK);
			inp1_sel = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg0, 
								CDC_WSA_RX_INTX_1_MIX_INP1_SEL_MASK);
			inp2_sel = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg1,
								CDC_WSA_RX_INTX_1_MIX_INP2_SEL_MASK);

			अगर ((inp0_sel == पूर्णांक_1_mix1_inp + INTn_1_INP_SEL_RX0) ||
			    (inp1_sel == पूर्णांक_1_mix1_inp + INTn_1_INP_SEL_RX0) ||
			    (inp2_sel == पूर्णांक_1_mix1_inp + INTn_1_INP_SEL_RX0)) अणु
				पूर्णांक_fs_reg = CDC_WSA_RX0_RX_PATH_CTL +
					     WSA_MACRO_RX_PATH_OFFSET * j;
				/* sample_rate is in Hz */
				snd_soc_component_update_bits(component, पूर्णांक_fs_reg,
							      WSA_MACRO_FS_RATE_MASK,
							      पूर्णांक_prim_fs_rate_reg_val);
			पूर्ण
			पूर्णांक_mux_cfg0 += WSA_MACRO_MUX_CFG_OFFSET;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_set_mix_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					       u8 पूर्णांक_mix_fs_rate_reg_val,
					       u32 sample_rate)
अणु
	u8 पूर्णांक_2_inp;
	u32 j, port;
	u16 पूर्णांक_mux_cfg1, पूर्णांक_fs_reg;
	u8 पूर्णांक_mux_cfg1_val;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	क्रम_each_set_bit(port, &wsa->active_ch_mask[dai->id], WSA_MACRO_RX_MAX) अणु
		पूर्णांक_2_inp = port;
		अगर ((पूर्णांक_2_inp < WSA_MACRO_RX0) || (पूर्णांक_2_inp > WSA_MACRO_RX_MIX1)) अणु
			dev_err(component->dev,	"%s: Invalid RX port, Dai ID is %d\n",
				__func__, dai->id);
			वापस -EINVAL;
		पूर्ण

		पूर्णांक_mux_cfg1 = CDC_WSA_RX_INP_MUX_RX_INT0_CFG1;
		क्रम (j = 0; j < NUM_INTERPOLATORS; j++) अणु
			पूर्णांक_mux_cfg1_val = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg1,
									CDC_WSA_RX_INTX_2_SEL_MASK);

			अगर (पूर्णांक_mux_cfg1_val == पूर्णांक_2_inp + INTn_2_INP_SEL_RX0) अणु
				पूर्णांक_fs_reg = CDC_WSA_RX0_RX_PATH_MIX_CTL +
					WSA_MACRO_RX_PATH_OFFSET * j;

				snd_soc_component_update_bits(component,
						      पूर्णांक_fs_reg,
						      WSA_MACRO_FS_RATE_MASK,
						      पूर्णांक_mix_fs_rate_reg_val);
			पूर्ण
			पूर्णांक_mux_cfg1 += WSA_MACRO_MUX_CFG_OFFSET;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_set_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					   u32 sample_rate)
अणु
	पूर्णांक rate_val = 0;
	पूर्णांक i, ret;

	/* set mixing path rate */
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_mix_sample_rate_val); i++) अणु
		अगर (sample_rate == पूर्णांक_mix_sample_rate_val[i].sample_rate) अणु
			rate_val = पूर्णांक_mix_sample_rate_val[i].rate_val;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((i == ARRAY_SIZE(पूर्णांक_mix_sample_rate_val)) || (rate_val < 0))
		जाओ prim_rate;

	ret = wsa_macro_set_mix_पूर्णांकerpolator_rate(dai, (u8) rate_val, sample_rate);
	अगर (ret < 0)
		वापस ret;
prim_rate:
	/* set primary path sample rate */
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_prim_sample_rate_val); i++) अणु
		अगर (sample_rate == पूर्णांक_prim_sample_rate_val[i].sample_rate) अणु
			rate_val = पूर्णांक_prim_sample_rate_val[i].rate_val;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((i == ARRAY_SIZE(पूर्णांक_prim_sample_rate_val)) || (rate_val < 0))
		वापस -EINVAL;

	ret = wsa_macro_set_prim_पूर्णांकerpolator_rate(dai, (u8) rate_val, sample_rate);

	वापस ret;
पूर्ण

अटल पूर्णांक wsa_macro_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		ret = wsa_macro_set_पूर्णांकerpolator_rate(dai, params_rate(params));
		अगर (ret) अणु
			dev_err(component->dev,
				"%s: cannot set sample rate: %u\n",
				__func__, params_rate(params));
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_get_channel_map(काष्ठा snd_soc_dai *dai,
				     अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				     अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	u16 val, mask = 0, cnt = 0, temp;

	चयन (dai->id) अणु
	हाल WSA_MACRO_AIF_VI:
		*tx_slot = wsa->active_ch_mask[dai->id];
		*tx_num = wsa->active_ch_cnt[dai->id];
		अवरोध;
	हाल WSA_MACRO_AIF1_PB:
	हाल WSA_MACRO_AIF_MIX1_PB:
		क्रम_each_set_bit(temp, &wsa->active_ch_mask[dai->id],
					WSA_MACRO_RX_MAX) अणु
			mask |= (1 << temp);
			अगर (++cnt == WSA_MACRO_MAX_DMA_CH_PER_PORT)
				अवरोध;
		पूर्ण
		अगर (mask & 0x0C)
			mask = mask >> 0x2;
		*rx_slot = mask;
		*rx_num = cnt;
		अवरोध;
	हाल WSA_MACRO_AIF_ECHO:
		val = snd_soc_component_पढ़ो(component, CDC_WSA_RX_INP_MUX_RX_MIX_CFG0);
		अगर (val & WSA_MACRO_EC_MIX_TX1_MASK) अणु
			mask |= 0x2;
			cnt++;
		पूर्ण
		अगर (val & WSA_MACRO_EC_MIX_TX0_MASK) अणु
			mask |= 0x1;
			cnt++;
		पूर्ण
		*tx_slot = mask;
		*tx_num = cnt;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: Invalid AIF\n", __func__);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wsa_macro_dai_ops = अणु
	.hw_params = wsa_macro_hw_params,
	.get_channel_map = wsa_macro_get_channel_map,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wsa_macro_dai[] = अणु
	अणु
		.name = "wsa_macro_rx1",
		.id = WSA_MACRO_AIF1_PB,
		.playback = अणु
			.stream_name = "WSA_AIF1 Playback",
			.rates = WSA_MACRO_RX_RATES,
			.क्रमmats = WSA_MACRO_RX_FORMATS,
			.rate_max = 384000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wsa_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "wsa_macro_rx_mix",
		.id = WSA_MACRO_AIF_MIX1_PB,
		.playback = अणु
			.stream_name = "WSA_AIF_MIX1 Playback",
			.rates = WSA_MACRO_RX_MIX_RATES,
			.क्रमmats = WSA_MACRO_RX_FORMATS,
			.rate_max = 192000,
			.rate_min = 48000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wsa_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "wsa_macro_vifeedback",
		.id = WSA_MACRO_AIF_VI,
		.capture = अणु
			.stream_name = "WSA_AIF_VI Capture",
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_48000,
			.क्रमmats = WSA_MACRO_RX_FORMATS,
			.rate_max = 48000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wsa_macro_dai_ops,
	पूर्ण,
	अणु
		.name = "wsa_macro_echo",
		.id = WSA_MACRO_AIF_ECHO,
		.capture = अणु
			.stream_name = "WSA_AIF_ECHO Capture",
			.rates = WSA_MACRO_ECHO_RATES,
			.क्रमmats = WSA_MACRO_ECHO_FORMATS,
			.rate_max = 48000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wsa_macro_dai_ops,
	पूर्ण,
पूर्ण;

अटल व्योम wsa_macro_mclk_enable(काष्ठा wsa_macro *wsa, bool mclk_enable)
अणु
	काष्ठा regmap *regmap = wsa->regmap;

	अगर (mclk_enable) अणु
		अगर (wsa->wsa_mclk_users == 0) अणु
			regcache_mark_dirty(regmap);
			regcache_sync(regmap);
			/* 9.6MHz MCLK, set value 0x00 अगर other frequency */
			regmap_update_bits(regmap, CDC_WSA_TOP_FREQ_MCLK, 0x01, 0x01);
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_MCLK_CONTROL,
					   CDC_WSA_MCLK_EN_MASK,
					   CDC_WSA_MCLK_ENABLE);
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_FS_CNT_CONTROL,
					   CDC_WSA_FS_CNT_EN_MASK,
					   CDC_WSA_FS_CNT_ENABLE);
		पूर्ण
		wsa->wsa_mclk_users++;
	पूर्ण अन्यथा अणु
		अगर (wsa->wsa_mclk_users <= 0) अणु
			dev_err(wsa->dev, "clock already disabled\n");
			wsa->wsa_mclk_users = 0;
			वापस;
		पूर्ण
		wsa->wsa_mclk_users--;
		अगर (wsa->wsa_mclk_users == 0) अणु
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_FS_CNT_CONTROL,
					   CDC_WSA_FS_CNT_EN_MASK,
					   CDC_WSA_FS_CNT_DISABLE);
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_MCLK_CONTROL,
					   CDC_WSA_MCLK_EN_MASK,
					   CDC_WSA_MCLK_DISABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wsa_macro_mclk_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	wsa_macro_mclk_enable(wsa, event == SND_SOC_DAPM_PRE_PMU);
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_enable_vi_feedback(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kcontrol,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	u32 tx_reg0, tx_reg1;

	अगर (test_bit(WSA_MACRO_TX0, &wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
		tx_reg0 = CDC_WSA_TX0_SPKR_PROT_PATH_CTL;
		tx_reg1 = CDC_WSA_TX1_SPKR_PROT_PATH_CTL;
	पूर्ण अन्यथा अगर (test_bit(WSA_MACRO_TX1, &wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
		tx_reg0 = CDC_WSA_TX2_SPKR_PROT_PATH_CTL;
		tx_reg1 = CDC_WSA_TX3_SPKR_PROT_PATH_CTL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
			/* Enable V&I sensing */
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_RESET);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_RESET);
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_PCM_RATE_MASK,
					      CDC_WSA_TX_SPKR_PROT_PCM_RATE_8K);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_PCM_RATE_MASK,
					      CDC_WSA_TX_SPKR_PROT_PCM_RATE_8K);
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_CLK_EN_MASK,
					      CDC_WSA_TX_SPKR_PROT_CLK_ENABLE);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_CLK_EN_MASK,
					      CDC_WSA_TX_SPKR_PROT_CLK_ENABLE);
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_NO_RESET);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_NO_RESET);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable V&I sensing */
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_RESET);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_RESET_MASK,
					      CDC_WSA_TX_SPKR_PROT_RESET);
		snd_soc_component_update_bits(component, tx_reg0,
					      CDC_WSA_TX_SPKR_PROT_CLK_EN_MASK,
					      CDC_WSA_TX_SPKR_PROT_CLK_DISABLE);
		snd_soc_component_update_bits(component, tx_reg1,
					      CDC_WSA_TX_SPKR_PROT_CLK_EN_MASK,
					      CDC_WSA_TX_SPKR_PROT_CLK_DISABLE);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_enable_mix_path(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 path_reg, gain_reg;
	पूर्णांक val;

	चयन (w->shअगरt) अणु
	हाल WSA_MACRO_RX_MIX0:
		path_reg = CDC_WSA_RX0_RX_PATH_MIX_CTL;
		gain_reg = CDC_WSA_RX0_RX_VOL_MIX_CTL;
		अवरोध;
	हाल WSA_MACRO_RX_MIX1:
		path_reg = CDC_WSA_RX1_RX_PATH_MIX_CTL;
		gain_reg = CDC_WSA_RX1_RX_VOL_MIX_CTL;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_पढ़ो(component, gain_reg);
		snd_soc_component_ग_लिखो(component, gain_reg, val);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, path_reg,
					      CDC_WSA_RX_PATH_MIX_CLK_EN_MASK,
					      CDC_WSA_RX_PATH_MIX_CLK_DISABLE);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wsa_macro_hd2_control(काष्ठा snd_soc_component *component,
				  u16 reg, पूर्णांक event)
अणु
	u16 hd2_scale_reg;
	u16 hd2_enable_reg;

	अगर (reg == CDC_WSA_RX0_RX_PATH_CTL) अणु
		hd2_scale_reg = CDC_WSA_RX0_RX_PATH_SEC3;
		hd2_enable_reg = CDC_WSA_RX0_RX_PATH_CFG0;
	पूर्ण
	अगर (reg == CDC_WSA_RX1_RX_PATH_CTL) अणु
		hd2_scale_reg = CDC_WSA_RX1_RX_PATH_SEC3;
		hd2_enable_reg = CDC_WSA_RX1_RX_PATH_CFG0;
	पूर्ण

	अगर (hd2_enable_reg && SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(component, hd2_scale_reg,
					      CDC_WSA_RX_PATH_HD2_ALPHA_MASK,
					      0x10);
		snd_soc_component_update_bits(component, hd2_scale_reg,
					      CDC_WSA_RX_PATH_HD2_SCALE_MASK,
					      0x1);
		snd_soc_component_update_bits(component, hd2_enable_reg,
					      CDC_WSA_RX_PATH_HD2_EN_MASK,
					      CDC_WSA_RX_PATH_HD2_ENABLE);
	पूर्ण

	अगर (hd2_enable_reg && SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, hd2_enable_reg,
					      CDC_WSA_RX_PATH_HD2_EN_MASK, 0);
		snd_soc_component_update_bits(component, hd2_scale_reg,
					      CDC_WSA_RX_PATH_HD2_SCALE_MASK,
					      0);
		snd_soc_component_update_bits(component, hd2_scale_reg,
					      CDC_WSA_RX_PATH_HD2_ALPHA_MASK,
					      0);
	पूर्ण
पूर्ण

अटल पूर्णांक wsa_macro_config_compander(काष्ठा snd_soc_component *component,
				      पूर्णांक comp, पूर्णांक event)
अणु
	u16 comp_ctl0_reg, rx_path_cfg0_reg;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	अगर (!wsa->comp_enabled[comp])
		वापस 0;

	comp_ctl0_reg = CDC_WSA_COMPANDER0_CTL0 +
					(comp * WSA_MACRO_RX_COMP_OFFSET);
	rx_path_cfg0_reg = CDC_WSA_RX0_RX_PATH_CFG0 +
					(comp * WSA_MACRO_RX_PATH_OFFSET);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/* Enable Compander Clock */
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_CLK_EN_MASK,
					      CDC_WSA_COMPANDER_CLK_ENABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_SOFT_RST_MASK,
					      CDC_WSA_COMPANDER_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_SOFT_RST_MASK,
					      0);
		snd_soc_component_update_bits(component, rx_path_cfg0_reg,
					      CDC_WSA_RX_PATH_COMP_EN_MASK,
					      CDC_WSA_RX_PATH_COMP_ENABLE);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_HALT_MASK,
					      CDC_WSA_COMPANDER_HALT);
		snd_soc_component_update_bits(component, rx_path_cfg0_reg,
					      CDC_WSA_RX_PATH_COMP_EN_MASK, 0);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_SOFT_RST_MASK,
					      CDC_WSA_COMPANDER_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_SOFT_RST_MASK,
					      0);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_CLK_EN_MASK, 0);
		snd_soc_component_update_bits(component, comp_ctl0_reg,
					      CDC_WSA_COMPANDER_HALT_MASK, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wsa_macro_enable_softclip_clk(काष्ठा snd_soc_component *component,
					 काष्ठा wsa_macro *wsa,
					 पूर्णांक path,
					 bool enable)
अणु
	u16 softclip_clk_reg = CDC_WSA_SOFTCLIP0_CRC +
			(path * WSA_MACRO_RX_SOFTCLIP_OFFSET);
	u8 softclip_mux_mask = (1 << path);
	u8 softclip_mux_value = (1 << path);

	अगर (enable) अणु
		अगर (wsa->softclip_clk_users[path] == 0) अणु
			snd_soc_component_update_bits(component,
						softclip_clk_reg,
						CDC_WSA_SOFTCLIP_CLK_EN_MASK,
						CDC_WSA_SOFTCLIP_CLK_ENABLE);
			snd_soc_component_update_bits(component,
				CDC_WSA_RX_INP_MUX_SOFTCLIP_CFG0,
				softclip_mux_mask, softclip_mux_value);
		पूर्ण
		wsa->softclip_clk_users[path]++;
	पूर्ण अन्यथा अणु
		wsa->softclip_clk_users[path]--;
		अगर (wsa->softclip_clk_users[path] == 0) अणु
			snd_soc_component_update_bits(component,
						softclip_clk_reg,
						CDC_WSA_SOFTCLIP_CLK_EN_MASK,
						0);
			snd_soc_component_update_bits(component,
				CDC_WSA_RX_INP_MUX_SOFTCLIP_CFG0,
				softclip_mux_mask, 0x00);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wsa_macro_config_softclip(काष्ठा snd_soc_component *component,
				     पूर्णांक path, पूर्णांक event)
अणु
	u16 softclip_ctrl_reg;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	पूर्णांक softclip_path = 0;

	अगर (path == WSA_MACRO_COMP1)
		softclip_path = WSA_MACRO_SOFTCLIP0;
	अन्यथा अगर (path == WSA_MACRO_COMP2)
		softclip_path = WSA_MACRO_SOFTCLIP1;

	अगर (!wsa->is_softclip_on[softclip_path])
		वापस 0;

	softclip_ctrl_reg = CDC_WSA_SOFTCLIP0_SOFTCLIP_CTRL +
				(softclip_path * WSA_MACRO_RX_SOFTCLIP_OFFSET);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/* Enable Softclip घड़ी and mux */
		wsa_macro_enable_softclip_clk(component, wsa, softclip_path,
					      true);
		/* Enable Softclip control */
		snd_soc_component_update_bits(component, softclip_ctrl_reg,
					      CDC_WSA_SOFTCLIP_EN_MASK,
					      CDC_WSA_SOFTCLIP_ENABLE);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, softclip_ctrl_reg,
					      CDC_WSA_SOFTCLIP_EN_MASK, 0);
		wsa_macro_enable_softclip_clk(component, wsa, softclip_path,
					      false);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool wsa_macro_adie_lb(काष्ठा snd_soc_component *component,
			      पूर्णांक पूर्णांकerp_idx)
अणु
	u16 पूर्णांक_mux_cfg0,  पूर्णांक_mux_cfg1;
	u8 पूर्णांक_n_inp0, पूर्णांक_n_inp1, पूर्णांक_n_inp2;

	पूर्णांक_mux_cfg0 = CDC_WSA_RX_INP_MUX_RX_INT0_CFG0 + पूर्णांकerp_idx * 8;
	पूर्णांक_mux_cfg1 = पूर्णांक_mux_cfg0 + 4;

	पूर्णांक_n_inp0 = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg0,
						  CDC_WSA_RX_INTX_1_MIX_INP0_SEL_MASK);
	अगर (पूर्णांक_n_inp0 == INTn_1_INP_SEL_DEC0 ||
		पूर्णांक_n_inp0 == INTn_1_INP_SEL_DEC1)
		वापस true;

	पूर्णांक_n_inp1 = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg0,
						  CDC_WSA_RX_INTX_1_MIX_INP1_SEL_MASK);
	अगर (पूर्णांक_n_inp1 == INTn_1_INP_SEL_DEC0 ||
		पूर्णांक_n_inp1 == INTn_1_INP_SEL_DEC1)
		वापस true;

	पूर्णांक_n_inp2 = snd_soc_component_पढ़ो_field(component, पूर्णांक_mux_cfg1,
						  CDC_WSA_RX_INTX_1_MIX_INP2_SEL_MASK);
	अगर (पूर्णांक_n_inp2 == INTn_1_INP_SEL_DEC0 ||
		पूर्णांक_n_inp2 == INTn_1_INP_SEL_DEC1)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक wsa_macro_enable_मुख्य_path(काष्ठा snd_soc_dapm_widget *w,
				      काष्ठा snd_kcontrol *kcontrol,
				      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 reg;

	reg = CDC_WSA_RX0_RX_PATH_CTL + WSA_MACRO_RX_PATH_OFFSET * w->shअगरt;
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (wsa_macro_adie_lb(component, w->shअगरt)) अणु
			snd_soc_component_update_bits(component, reg,
					     CDC_WSA_RX_PATH_CLK_EN_MASK,
					     CDC_WSA_RX_PATH_CLK_ENABLE);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_पूर्णांकerp_get_primary_reg(u16 reg, u16 *ind)
अणु
	u16 prim_पूर्णांक_reg = 0;

	चयन (reg) अणु
	हाल CDC_WSA_RX0_RX_PATH_CTL:
	हाल CDC_WSA_RX0_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = CDC_WSA_RX0_RX_PATH_CTL;
		*ind = 0;
		अवरोध;
	हाल CDC_WSA_RX1_RX_PATH_CTL:
	हाल CDC_WSA_RX1_RX_PATH_MIX_CTL:
		prim_पूर्णांक_reg = CDC_WSA_RX1_RX_PATH_CTL;
		*ind = 1;
		अवरोध;
	पूर्ण

	वापस prim_पूर्णांक_reg;
पूर्ण

अटल पूर्णांक wsa_macro_enable_prim_पूर्णांकerpolator(काष्ठा snd_soc_component *component,
					      u16 reg, पूर्णांक event)
अणु
	u16 prim_पूर्णांक_reg;
	u16 ind = 0;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	prim_पूर्णांक_reg = wsa_macro_पूर्णांकerp_get_primary_reg(reg, &ind);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wsa->prim_पूर्णांक_users[ind]++;
		अगर (wsa->prim_पूर्णांक_users[ind] == 1) अणु
			snd_soc_component_update_bits(component,
						      prim_पूर्णांक_reg + WSA_MACRO_RX_PATH_CFG3_OFFSET,
						      CDC_WSA_RX_DC_DCOEFF_MASK,
						      0x3);
			snd_soc_component_update_bits(component, prim_पूर्णांक_reg,
					CDC_WSA_RX_PATH_PGA_MUTE_EN_MASK,
					CDC_WSA_RX_PATH_PGA_MUTE_ENABLE);
			wsa_macro_hd2_control(component, prim_पूर्णांक_reg, event);
			snd_soc_component_update_bits(component,
				prim_पूर्णांक_reg + WSA_MACRO_RX_PATH_DSMDEM_OFFSET,
				CDC_WSA_RX_DSMDEM_CLK_EN_MASK,
				CDC_WSA_RX_DSMDEM_CLK_ENABLE);
		पूर्ण
		अगर ((reg != prim_पूर्णांक_reg) &&
		    ((snd_soc_component_पढ़ो(
				component, prim_पूर्णांक_reg)) & 0x10))
			snd_soc_component_update_bits(component, reg,
					0x10, 0x10);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wsa->prim_पूर्णांक_users[ind]--;
		अगर (wsa->prim_पूर्णांक_users[ind] == 0) अणु
			snd_soc_component_update_bits(component,
				prim_पूर्णांक_reg + WSA_MACRO_RX_PATH_DSMDEM_OFFSET,
				CDC_WSA_RX_DSMDEM_CLK_EN_MASK, 0);
			wsa_macro_hd2_control(component, prim_पूर्णांक_reg, event);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_config_ear_spkr_gain(काष्ठा snd_soc_component *component,
					  काष्ठा wsa_macro *wsa,
					  पूर्णांक event, पूर्णांक gain_reg)
अणु
	पूर्णांक comp_gain_offset, val;

	चयन (wsa->spkr_mode) अणु
	/* Compander gain in WSA_MACRO_SPKR_MODE1 हाल is 12 dB */
	हाल WSA_MACRO_SPKR_MODE_1:
		comp_gain_offset = -12;
		अवरोध;
	/* Default हाल compander gain is 15 dB */
	शेष:
		comp_gain_offset = -15;
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Apply ear spkr gain only अगर compander is enabled */
		अगर (wsa->comp_enabled[WSA_MACRO_COMP1] &&
		    (gain_reg == CDC_WSA_RX0_RX_VOL_CTL) &&
		    (wsa->ear_spkr_gain != 0)) अणु
			/* For example, val is -8(-12+5-1) क्रम 4dB of gain */
			val = comp_gain_offset + wsa->ear_spkr_gain - 1;
			snd_soc_component_ग_लिखो(component, gain_reg, val);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/*
		 * Reset RX0 volume to 0 dB अगर compander is enabled and
		 * ear_spkr_gain is non-zero.
		 */
		अगर (wsa->comp_enabled[WSA_MACRO_COMP1] &&
		    (gain_reg == CDC_WSA_RX0_RX_VOL_CTL) &&
		    (wsa->ear_spkr_gain != 0)) अणु
			snd_soc_component_ग_लिखो(component, gain_reg, 0x0);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_enable_पूर्णांकerpolator(काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा snd_kcontrol *kcontrol,
					 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 gain_reg;
	u16 reg;
	पूर्णांक val;
	पूर्णांक offset_val = 0;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	अगर (w->shअगरt == WSA_MACRO_COMP1) अणु
		reg = CDC_WSA_RX0_RX_PATH_CTL;
		gain_reg = CDC_WSA_RX0_RX_VOL_CTL;
	पूर्ण अन्यथा अगर (w->shअगरt == WSA_MACRO_COMP2) अणु
		reg = CDC_WSA_RX1_RX_PATH_CTL;
		gain_reg = CDC_WSA_RX1_RX_VOL_CTL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Reset अगर needed */
		wsa_macro_enable_prim_पूर्णांकerpolator(component, reg, event);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		wsa_macro_config_compander(component, w->shअगरt, event);
		wsa_macro_config_softclip(component, w->shअगरt, event);
		/* apply gain after पूर्णांक clk is enabled */
		अगर ((wsa->spkr_gain_offset == WSA_MACRO_GAIN_OFFSET_M1P5_DB) &&
		    (wsa->comp_enabled[WSA_MACRO_COMP1] ||
		     wsa->comp_enabled[WSA_MACRO_COMP2])) अणु
			snd_soc_component_update_bits(component,
					CDC_WSA_RX0_RX_PATH_SEC1,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_ENABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX0_RX_PATH_MIX_SEC0,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_ENABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX1_RX_PATH_SEC1,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_ENABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX1_RX_PATH_MIX_SEC0,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_ENABLE);
			offset_val = -2;
		पूर्ण
		val = snd_soc_component_पढ़ो(component, gain_reg);
		val += offset_val;
		snd_soc_component_ग_लिखो(component, gain_reg, val);
		wsa_macro_config_ear_spkr_gain(component, wsa,
						event, gain_reg);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wsa_macro_config_compander(component, w->shअगरt, event);
		wsa_macro_config_softclip(component, w->shअगरt, event);
		wsa_macro_enable_prim_पूर्णांकerpolator(component, reg, event);
		अगर ((wsa->spkr_gain_offset == WSA_MACRO_GAIN_OFFSET_M1P5_DB) &&
		    (wsa->comp_enabled[WSA_MACRO_COMP1] ||
		     wsa->comp_enabled[WSA_MACRO_COMP2])) अणु
			snd_soc_component_update_bits(component,
					CDC_WSA_RX0_RX_PATH_SEC1,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_DISABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX0_RX_PATH_MIX_SEC0,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_DISABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX1_RX_PATH_SEC1,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_DISABLE);
			snd_soc_component_update_bits(component,
					CDC_WSA_RX1_RX_PATH_MIX_SEC0,
					CDC_WSA_RX_PGA_HALF_DB_MASK,
					CDC_WSA_RX_PGA_HALF_DB_DISABLE);
			offset_val = 2;
			val = snd_soc_component_पढ़ो(component, gain_reg);
			val += offset_val;
			snd_soc_component_ग_लिखो(component, gain_reg, val);
		पूर्ण
		wsa_macro_config_ear_spkr_gain(component, wsa,
						event, gain_reg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_spk_boost_event(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kcontrol,
				     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 boost_path_ctl, boost_path_cfg1;
	u16 reg, reg_mix;

	अगर (!म_भेद(w->name, "WSA_RX INT0 CHAIN")) अणु
		boost_path_ctl = CDC_WSA_BOOST0_BOOST_PATH_CTL;
		boost_path_cfg1 = CDC_WSA_RX0_RX_PATH_CFG1;
		reg = CDC_WSA_RX0_RX_PATH_CTL;
		reg_mix = CDC_WSA_RX0_RX_PATH_MIX_CTL;
	पूर्ण अन्यथा अगर (!म_भेद(w->name, "WSA_RX INT1 CHAIN")) अणु
		boost_path_ctl = CDC_WSA_BOOST1_BOOST_PATH_CTL;
		boost_path_cfg1 = CDC_WSA_RX1_RX_PATH_CFG1;
		reg = CDC_WSA_RX1_RX_PATH_CTL;
		reg_mix = CDC_WSA_RX1_RX_PATH_MIX_CTL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, boost_path_cfg1,
					      CDC_WSA_RX_PATH_SMART_BST_EN_MASK,
					      CDC_WSA_RX_PATH_SMART_BST_ENABLE);
		snd_soc_component_update_bits(component, boost_path_ctl,
					      CDC_WSA_BOOST_PATH_CLK_EN_MASK,
					      CDC_WSA_BOOST_PATH_CLK_ENABLE);
		अगर ((snd_soc_component_पढ़ो(component, reg_mix)) & 0x10)
			snd_soc_component_update_bits(component, reg_mix,
						0x10, 0x00);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, reg, 0x10, 0x00);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, boost_path_ctl,
					      CDC_WSA_BOOST_PATH_CLK_EN_MASK,
					      CDC_WSA_BOOST_PATH_CLK_DISABLE);
		snd_soc_component_update_bits(component, boost_path_cfg1,
					      CDC_WSA_RX_PATH_SMART_BST_EN_MASK,
					      CDC_WSA_RX_PATH_SMART_BST_DISABLE);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_enable_echo(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol,
				 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	u16 val, ec_tx, ec_hq_reg;

	val = snd_soc_component_पढ़ो(component, CDC_WSA_RX_INP_MUX_RX_MIX_CFG0);

	चयन (w->shअगरt) अणु
	हाल WSA_MACRO_EC0_MUX:
		val = val & CDC_WSA_RX_MIX_TX0_SEL_MASK;
		ec_tx = val - 1;
		अवरोध;
	हाल WSA_MACRO_EC1_MUX:
		val = val & CDC_WSA_RX_MIX_TX1_SEL_MASK;
		ec_tx = (val >> CDC_WSA_RX_MIX_TX1_SEL_SHFT) - 1;
		अवरोध;
	पूर्ण

	अगर (wsa->ec_hq[ec_tx]) अणु
		ec_hq_reg = CDC_WSA_EC_HQ0_EC_REF_HQ_PATH_CTL +	0x40 * ec_tx;
		snd_soc_component_update_bits(component, ec_hq_reg,
					     CDC_WSA_EC_HQ_EC_CLK_EN_MASK,
					     CDC_WSA_EC_HQ_EC_CLK_ENABLE);
		ec_hq_reg = CDC_WSA_EC_HQ0_EC_REF_HQ_CFG0 + 0x40 * ec_tx;
		/* शेष set to 48k */
		snd_soc_component_update_bits(component, ec_hq_reg,
				      CDC_WSA_EC_HQ_EC_REF_PCM_RATE_MASK,
				      CDC_WSA_EC_HQ_EC_REF_PCM_RATE_48K);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_get_ec_hq(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक ec_tx = ((काष्ठा soc_mixer_control *) kcontrol->निजी_value)->shअगरt;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wsa->ec_hq[ec_tx];

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_set_ec_hq(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक ec_tx = ((काष्ठा soc_mixer_control *) kcontrol->निजी_value)->shअगरt;
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	wsa->ec_hq[ec_tx] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_get_compander(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *) kcontrol->निजी_value)->shअगरt;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wsa->comp_enabled[comp];
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_set_compander(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *) kcontrol->निजी_value)->shअगरt;
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	wsa->comp_enabled[comp] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_ear_spkr_pa_gain_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wsa->ear_spkr_gain;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_ear_spkr_pa_gain_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	wsa->ear_spkr_gain =  ucontrol->value.पूर्णांकeger.value[0];

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_rx_mux_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget =
		snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component =
				snd_soc_dapm_to_component(widget->dapm);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] =
			wsa->rx_port_value[widget->shअगरt];
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_rx_mux_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget =
		snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component =
				snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_soc_dapm_update *update = शून्य;
	u32 rx_port_value = ucontrol->value.पूर्णांकeger.value[0];
	u32 bit_input;
	u32 aअगर_rst;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);

	aअगर_rst = wsa->rx_port_value[widget->shअगरt];
	अगर (!rx_port_value) अणु
		अगर (aअगर_rst == 0) अणु
			dev_err(component->dev, "%s: AIF reset already\n", __func__);
			वापस 0;
		पूर्ण
		अगर (aअगर_rst >= WSA_MACRO_RX_MAX) अणु
			dev_err(component->dev, "%s: Invalid AIF reset\n", __func__);
			वापस 0;
		पूर्ण
	पूर्ण
	wsa->rx_port_value[widget->shअगरt] = rx_port_value;

	bit_input = widget->shअगरt;

	चयन (rx_port_value) अणु
	हाल 0:
		अगर (wsa->active_ch_cnt[aअगर_rst]) अणु
			clear_bit(bit_input,
				  &wsa->active_ch_mask[aअगर_rst]);
			wsa->active_ch_cnt[aअगर_rst]--;
		पूर्ण
		अवरोध;
	हाल 1:
	हाल 2:
		set_bit(bit_input,
			&wsa->active_ch_mask[rx_port_value]);
		wsa->active_ch_cnt[rx_port_value]++;
		अवरोध;
	शेष:
		dev_err(component->dev,
			"%s: Invalid AIF_ID for WSA RX MUX %d\n",
			__func__, rx_port_value);
		वापस -EINVAL;
	पूर्ण

	snd_soc_dapm_mux_update_घातer(widget->dapm, kcontrol,
					rx_port_value, e, update);
	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_soft_clip_enable_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	पूर्णांक path = ((काष्ठा soc_mixer_control *)kcontrol->निजी_value)->shअगरt;

	ucontrol->value.पूर्णांकeger.value[0] = wsa->is_softclip_on[path];

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_soft_clip_enable_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	पूर्णांक path = ((काष्ठा soc_mixer_control *) kcontrol->निजी_value)->shअगरt;

	wsa->is_softclip_on[path] =  ucontrol->value.पूर्णांकeger.value[0];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wsa_macro_snd_controls[] = अणु
	SOC_ENUM_EXT("EAR SPKR PA Gain", wsa_macro_ear_spkr_pa_gain_क्रमागत,
		     wsa_macro_ear_spkr_pa_gain_get,
		     wsa_macro_ear_spkr_pa_gain_put),
	SOC_SINGLE_EXT("WSA_Softclip0 Enable", SND_SOC_NOPM,
			WSA_MACRO_SOFTCLIP0, 1, 0,
			wsa_macro_soft_clip_enable_get,
			wsa_macro_soft_clip_enable_put),
	SOC_SINGLE_EXT("WSA_Softclip1 Enable", SND_SOC_NOPM,
			WSA_MACRO_SOFTCLIP1, 1, 0,
			wsa_macro_soft_clip_enable_get,
			wsa_macro_soft_clip_enable_put),

	SOC_SINGLE_S8_TLV("WSA_RX0 Digital Volume", CDC_WSA_RX0_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("WSA_RX1 Digital Volume", CDC_WSA_RX1_RX_VOL_CTL,
			  -84, 40, digital_gain),

	SOC_SINGLE("WSA_RX0 Digital Mute", CDC_WSA_RX0_RX_PATH_CTL, 4, 1, 0),
	SOC_SINGLE("WSA_RX1 Digital Mute", CDC_WSA_RX1_RX_PATH_CTL, 4, 1, 0),
	SOC_SINGLE("WSA_RX0_MIX Digital Mute", CDC_WSA_RX0_RX_PATH_MIX_CTL, 4,
		   1, 0),
	SOC_SINGLE("WSA_RX1_MIX Digital Mute", CDC_WSA_RX1_RX_PATH_MIX_CTL, 4,
		   1, 0),
	SOC_SINGLE_EXT("WSA_COMP1 Switch", SND_SOC_NOPM, WSA_MACRO_COMP1, 1, 0,
		       wsa_macro_get_compander, wsa_macro_set_compander),
	SOC_SINGLE_EXT("WSA_COMP2 Switch", SND_SOC_NOPM, WSA_MACRO_COMP2, 1, 0,
		       wsa_macro_get_compander, wsa_macro_set_compander),
	SOC_SINGLE_EXT("WSA_RX0 EC_HQ Switch", SND_SOC_NOPM, WSA_MACRO_RX0, 1, 0,
		       wsa_macro_get_ec_hq, wsa_macro_set_ec_hq),
	SOC_SINGLE_EXT("WSA_RX1 EC_HQ Switch", SND_SOC_NOPM, WSA_MACRO_RX1, 1, 0,
		       wsa_macro_get_ec_hq, wsa_macro_set_ec_hq),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत rx_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(rx_mux_text), rx_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new rx_mux[WSA_MACRO_RX_MAX] = अणु
	SOC_DAPM_ENUM_EXT("WSA RX0 Mux", rx_mux_क्रमागत,
			  wsa_macro_rx_mux_get, wsa_macro_rx_mux_put),
	SOC_DAPM_ENUM_EXT("WSA RX1 Mux", rx_mux_क्रमागत,
			  wsa_macro_rx_mux_get, wsa_macro_rx_mux_put),
	SOC_DAPM_ENUM_EXT("WSA RX_MIX0 Mux", rx_mux_क्रमागत,
			  wsa_macro_rx_mux_get, wsa_macro_rx_mux_put),
	SOC_DAPM_ENUM_EXT("WSA RX_MIX1 Mux", rx_mux_क्रमागत,
			  wsa_macro_rx_mux_get, wsa_macro_rx_mux_put),
पूर्ण;

अटल पूर्णांक wsa_macro_vi_feed_mixer_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_mixer_control *mixer = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	u32 spk_tx_id = mixer->shअगरt;
	u32 dai_id = widget->shअगरt;

	अगर (test_bit(spk_tx_id, &wsa->active_ch_mask[dai_id]))
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_vi_feed_mixer_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	काष्ठा soc_mixer_control *mixer = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(component);
	u32 enable = ucontrol->value.पूर्णांकeger.value[0];
	u32 spk_tx_id = mixer->shअगरt;

	अगर (enable) अणु
		अगर (spk_tx_id == WSA_MACRO_TX0 &&
			!test_bit(WSA_MACRO_TX0,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
			set_bit(WSA_MACRO_TX0,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI]);
			wsa->active_ch_cnt[WSA_MACRO_AIF_VI]++;
		पूर्ण
		अगर (spk_tx_id == WSA_MACRO_TX1 &&
			!test_bit(WSA_MACRO_TX1,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
			set_bit(WSA_MACRO_TX1,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI]);
			wsa->active_ch_cnt[WSA_MACRO_AIF_VI]++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (spk_tx_id == WSA_MACRO_TX0 &&
			test_bit(WSA_MACRO_TX0,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
			clear_bit(WSA_MACRO_TX0,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI]);
			wsa->active_ch_cnt[WSA_MACRO_AIF_VI]--;
		पूर्ण
		अगर (spk_tx_id == WSA_MACRO_TX1 &&
			test_bit(WSA_MACRO_TX1,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI])) अणु
			clear_bit(WSA_MACRO_TX1,
				&wsa->active_ch_mask[WSA_MACRO_AIF_VI]);
			wsa->active_ch_cnt[WSA_MACRO_AIF_VI]--;
		पूर्ण
	पूर्ण
	snd_soc_dapm_mixer_update_घातer(widget->dapm, kcontrol, enable, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aअगर_vi_mixer[] = अणु
	SOC_SINGLE_EXT("WSA_SPKR_VI_1", SND_SOC_NOPM, WSA_MACRO_TX0, 1, 0,
			wsa_macro_vi_feed_mixer_get,
			wsa_macro_vi_feed_mixer_put),
	SOC_SINGLE_EXT("WSA_SPKR_VI_2", SND_SOC_NOPM, WSA_MACRO_TX1, 1, 0,
			wsa_macro_vi_feed_mixer_get,
			wsa_macro_vi_feed_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wsa_macro_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("WSA AIF1 PB", "WSA_AIF1 Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WSA AIF_MIX1 PB", "WSA_AIF_MIX1 Playback", 0,
			    SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT_E("WSA AIF_VI", "WSA_AIF_VI Capture", 0,
			       SND_SOC_NOPM, WSA_MACRO_AIF_VI, 0,
			       wsa_macro_enable_vi_feedback,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("WSA AIF_ECHO", "WSA_AIF_ECHO Capture", 0,
			     SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MIXER("WSA_AIF_VI Mixer", SND_SOC_NOPM, WSA_MACRO_AIF_VI,
			   0, aअगर_vi_mixer, ARRAY_SIZE(aअगर_vi_mixer)),
	SND_SOC_DAPM_MUX_E("WSA RX_MIX EC0_MUX", SND_SOC_NOPM,
			   WSA_MACRO_EC0_MUX, 0,
			   &rx_mix_ec0_mux, wsa_macro_enable_echo,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("WSA RX_MIX EC1_MUX", SND_SOC_NOPM,
			   WSA_MACRO_EC1_MUX, 0,
			   &rx_mix_ec1_mux, wsa_macro_enable_echo,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("WSA RX0 MUX", SND_SOC_NOPM, WSA_MACRO_RX0, 0,
			 &rx_mux[WSA_MACRO_RX0]),
	SND_SOC_DAPM_MUX("WSA RX1 MUX", SND_SOC_NOPM, WSA_MACRO_RX1, 0,
			 &rx_mux[WSA_MACRO_RX1]),
	SND_SOC_DAPM_MUX("WSA RX_MIX0 MUX", SND_SOC_NOPM, WSA_MACRO_RX_MIX0, 0,
			 &rx_mux[WSA_MACRO_RX_MIX0]),
	SND_SOC_DAPM_MUX("WSA RX_MIX1 MUX", SND_SOC_NOPM, WSA_MACRO_RX_MIX1, 0,
			 &rx_mux[WSA_MACRO_RX_MIX1]),

	SND_SOC_DAPM_MIXER("WSA RX0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("WSA RX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("WSA RX_MIX0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("WSA RX_MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("WSA_RX0 INP0", SND_SOC_NOPM, 0, 0, &rx0_prim_inp0_mux),
	SND_SOC_DAPM_MUX("WSA_RX0 INP1", SND_SOC_NOPM, 0, 0, &rx0_prim_inp1_mux),
	SND_SOC_DAPM_MUX("WSA_RX0 INP2", SND_SOC_NOPM, 0, 0, &rx0_prim_inp2_mux),
	SND_SOC_DAPM_MUX_E("WSA_RX0 MIX INP", SND_SOC_NOPM, WSA_MACRO_RX_MIX0,
			   0, &rx0_mix_mux, wsa_macro_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("WSA_RX1 INP0", SND_SOC_NOPM, 0, 0, &rx1_prim_inp0_mux),
	SND_SOC_DAPM_MUX("WSA_RX1 INP1", SND_SOC_NOPM, 0, 0, &rx1_prim_inp1_mux),
	SND_SOC_DAPM_MUX("WSA_RX1 INP2", SND_SOC_NOPM, 0, 0, &rx1_prim_inp2_mux),
	SND_SOC_DAPM_MUX_E("WSA_RX1 MIX INP", SND_SOC_NOPM, WSA_MACRO_RX_MIX1,
			   0, &rx1_mix_mux, wsa_macro_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER_E("WSA_RX INT0 MIX", SND_SOC_NOPM, 0, 0, शून्य, 0,
			     wsa_macro_enable_मुख्य_path, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MIXER_E("WSA_RX INT1 MIX", SND_SOC_NOPM, 1, 0, शून्य, 0,
			     wsa_macro_enable_मुख्य_path, SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_MIXER("WSA_RX INT0 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("WSA_RX INT1 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("WSA_RX0 INT0 SIDETONE MIX", CDC_WSA_RX0_RX_PATH_CFG1,
			 4, 0, &rx0_sidetone_mix_mux),

	SND_SOC_DAPM_INPUT("WSA SRC0_INP"),
	SND_SOC_DAPM_INPUT("WSA_TX DEC0_INP"),
	SND_SOC_DAPM_INPUT("WSA_TX DEC1_INP"),

	SND_SOC_DAPM_MIXER_E("WSA_RX INT0 INTERP", SND_SOC_NOPM,
			     WSA_MACRO_COMP1, 0, शून्य, 0,
			     wsa_macro_enable_पूर्णांकerpolator,
			     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER_E("WSA_RX INT1 INTERP", SND_SOC_NOPM,
			     WSA_MACRO_COMP2, 0, शून्य, 0,
			     wsa_macro_enable_पूर्णांकerpolator,
			     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER_E("WSA_RX INT0 CHAIN", SND_SOC_NOPM, 0, 0,
			     शून्य, 0, wsa_macro_spk_boost_event,
			     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER_E("WSA_RX INT1 CHAIN", SND_SOC_NOPM, 0, 0,
			     शून्य, 0, wsa_macro_spk_boost_event,
			     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("VIINPUT_WSA"),
	SND_SOC_DAPM_OUTPUT("WSA_SPK1 OUT"),
	SND_SOC_DAPM_OUTPUT("WSA_SPK2 OUT"),

	SND_SOC_DAPM_SUPPLY("WSA_RX0_CLK", CDC_WSA_RX0_RX_PATH_CTL, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("WSA_RX1_CLK", CDC_WSA_RX1_RX_PATH_CTL, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("WSA_RX_MIX0_CLK", CDC_WSA_RX0_RX_PATH_MIX_CTL, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("WSA_RX_MIX1_CLK", CDC_WSA_RX1_RX_PATH_MIX_CTL, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("WSA_MCLK", 0, SND_SOC_NOPM, 0, 0,
			      wsa_macro_mclk_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wsa_audio_map[] = अणु
	/* VI Feedback */
	अणु"WSA_AIF_VI Mixer", "WSA_SPKR_VI_1", "VIINPUT_WSA"पूर्ण,
	अणु"WSA_AIF_VI Mixer", "WSA_SPKR_VI_2", "VIINPUT_WSA"पूर्ण,
	अणु"WSA AIF_VI", शून्य, "WSA_AIF_VI Mixer"पूर्ण,
	अणु"WSA AIF_VI", शून्य, "WSA_MCLK"पूर्ण,

	अणु"WSA RX_MIX EC0_MUX", "RX_MIX_TX0", "WSA_RX INT0 SEC MIX"पूर्ण,
	अणु"WSA RX_MIX EC1_MUX", "RX_MIX_TX0", "WSA_RX INT0 SEC MIX"पूर्ण,
	अणु"WSA RX_MIX EC0_MUX", "RX_MIX_TX1", "WSA_RX INT1 SEC MIX"पूर्ण,
	अणु"WSA RX_MIX EC1_MUX", "RX_MIX_TX1", "WSA_RX INT1 SEC MIX"पूर्ण,
	अणु"WSA AIF_ECHO", शून्य, "WSA RX_MIX EC0_MUX"पूर्ण,
	अणु"WSA AIF_ECHO", शून्य, "WSA RX_MIX EC1_MUX"पूर्ण,
	अणु"WSA AIF_ECHO", शून्य, "WSA_MCLK"पूर्ण,

	अणु"WSA AIF1 PB", शून्य, "WSA_MCLK"पूर्ण,
	अणु"WSA AIF_MIX1 PB", शून्य, "WSA_MCLK"पूर्ण,

	अणु"WSA RX0 MUX", "AIF1_PB", "WSA AIF1 PB"पूर्ण,
	अणु"WSA RX1 MUX", "AIF1_PB", "WSA AIF1 PB"पूर्ण,
	अणु"WSA RX_MIX0 MUX", "AIF1_PB", "WSA AIF1 PB"पूर्ण,
	अणु"WSA RX_MIX1 MUX", "AIF1_PB", "WSA AIF1 PB"पूर्ण,

	अणु"WSA RX0 MUX", "AIF_MIX1_PB", "WSA AIF_MIX1 PB"पूर्ण,
	अणु"WSA RX1 MUX", "AIF_MIX1_PB", "WSA AIF_MIX1 PB"पूर्ण,
	अणु"WSA RX_MIX0 MUX", "AIF_MIX1_PB", "WSA AIF_MIX1 PB"पूर्ण,
	अणु"WSA RX_MIX1 MUX", "AIF_MIX1_PB", "WSA AIF_MIX1 PB"पूर्ण,

	अणु"WSA RX0", शून्य, "WSA RX0 MUX"पूर्ण,
	अणु"WSA RX1", शून्य, "WSA RX1 MUX"पूर्ण,
	अणु"WSA RX_MIX0", शून्य, "WSA RX_MIX0 MUX"पूर्ण,
	अणु"WSA RX_MIX1", शून्य, "WSA RX_MIX1 MUX"पूर्ण,

	अणु"WSA RX0", शून्य, "WSA_RX0_CLK"पूर्ण,
	अणु"WSA RX1", शून्य, "WSA_RX1_CLK"पूर्ण,
	अणु"WSA RX_MIX0", शून्य, "WSA_RX_MIX0_CLK"पूर्ण,
	अणु"WSA RX_MIX1", शून्य, "WSA_RX_MIX1_CLK"पूर्ण,

	अणु"WSA_RX0 INP0", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX0 INP0", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX0 INP0", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX0 INP0", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX0 INP0", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX0 INP0", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT0 MIX", शून्य, "WSA_RX0 INP0"पूर्ण,

	अणु"WSA_RX0 INP1", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX0 INP1", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX0 INP1", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX0 INP1", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX0 INP1", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX0 INP1", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT0 MIX", शून्य, "WSA_RX0 INP1"पूर्ण,

	अणु"WSA_RX0 INP2", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX0 INP2", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX0 INP2", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX0 INP2", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX0 INP2", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX0 INP2", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT0 MIX", शून्य, "WSA_RX0 INP2"पूर्ण,

	अणु"WSA_RX0 MIX INP", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX0 MIX INP", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX0 MIX INP", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX0 MIX INP", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX INT0 SEC MIX", शून्य, "WSA_RX0 MIX INP"पूर्ण,

	अणु"WSA_RX INT0 SEC MIX", शून्य, "WSA_RX INT0 MIX"पूर्ण,
	अणु"WSA_RX INT0 INTERP", शून्य, "WSA_RX INT0 SEC MIX"पूर्ण,
	अणु"WSA_RX0 INT0 SIDETONE MIX", "SRC0", "WSA SRC0_INP"पूर्ण,
	अणु"WSA_RX INT0 INTERP", शून्य, "WSA_RX0 INT0 SIDETONE MIX"पूर्ण,
	अणु"WSA_RX INT0 CHAIN", शून्य, "WSA_RX INT0 INTERP"पूर्ण,

	अणु"WSA_SPK1 OUT", शून्य, "WSA_RX INT0 CHAIN"पूर्ण,
	अणु"WSA_SPK1 OUT", शून्य, "WSA_MCLK"पूर्ण,

	अणु"WSA_RX1 INP0", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX1 INP0", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX1 INP0", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX1 INP0", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX1 INP0", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX1 INP0", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT1 MIX", शून्य, "WSA_RX1 INP0"पूर्ण,

	अणु"WSA_RX1 INP1", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX1 INP1", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX1 INP1", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX1 INP1", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX1 INP1", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX1 INP1", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT1 MIX", शून्य, "WSA_RX1 INP1"पूर्ण,

	अणु"WSA_RX1 INP2", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX1 INP2", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX1 INP2", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX1 INP2", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX1 INP2", "DEC0", "WSA_TX DEC0_INP"पूर्ण,
	अणु"WSA_RX1 INP2", "DEC1", "WSA_TX DEC1_INP"पूर्ण,
	अणु"WSA_RX INT1 MIX", शून्य, "WSA_RX1 INP2"पूर्ण,

	अणु"WSA_RX1 MIX INP", "RX0", "WSA RX0"पूर्ण,
	अणु"WSA_RX1 MIX INP", "RX1", "WSA RX1"पूर्ण,
	अणु"WSA_RX1 MIX INP", "RX_MIX0", "WSA RX_MIX0"पूर्ण,
	अणु"WSA_RX1 MIX INP", "RX_MIX1", "WSA RX_MIX1"पूर्ण,
	अणु"WSA_RX INT1 SEC MIX", शून्य, "WSA_RX1 MIX INP"पूर्ण,

	अणु"WSA_RX INT1 SEC MIX", शून्य, "WSA_RX INT1 MIX"पूर्ण,
	अणु"WSA_RX INT1 INTERP", शून्य, "WSA_RX INT1 SEC MIX"पूर्ण,

	अणु"WSA_RX INT1 CHAIN", शून्य, "WSA_RX INT1 INTERP"पूर्ण,
	अणु"WSA_SPK2 OUT", शून्य, "WSA_RX INT1 CHAIN"पूर्ण,
	अणु"WSA_SPK2 OUT", शून्य, "WSA_MCLK"पूर्ण,
पूर्ण;

अटल पूर्णांक wsa_swrm_घड़ी(काष्ठा wsa_macro *wsa, bool enable)
अणु
	काष्ठा regmap *regmap = wsa->regmap;

	अगर (enable) अणु
		wsa_macro_mclk_enable(wsa, true);

		/* reset swr ip */
		अगर (wsa->reset_swr)
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_SWR_CONTROL,
					   CDC_WSA_SWR_RST_EN_MASK,
					   CDC_WSA_SWR_RST_ENABLE);

		regmap_update_bits(regmap, CDC_WSA_CLK_RST_CTRL_SWR_CONTROL,
				   CDC_WSA_SWR_CLK_EN_MASK,
				   CDC_WSA_SWR_CLK_ENABLE);

		/* Bring out of reset */
		अगर (wsa->reset_swr)
			regmap_update_bits(regmap,
					   CDC_WSA_CLK_RST_CTRL_SWR_CONTROL,
					   CDC_WSA_SWR_RST_EN_MASK,
					   CDC_WSA_SWR_RST_DISABLE);
		wsa->reset_swr = false;
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap, CDC_WSA_CLK_RST_CTRL_SWR_CONTROL,
				   CDC_WSA_SWR_CLK_EN_MASK, 0);
		wsa_macro_mclk_enable(wsa, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wsa_macro_component_probe(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा wsa_macro *wsa = snd_soc_component_get_drvdata(comp);

	snd_soc_component_init_regmap(comp, wsa->regmap);

	wsa->spkr_gain_offset = WSA_MACRO_GAIN_OFFSET_M1P5_DB;

	/* set SPKR rate to FS_2P4_3P072 */
	snd_soc_component_update_bits(comp, CDC_WSA_RX0_RX_PATH_CFG1,
				CDC_WSA_RX_PATH_SPKR_RATE_MASK,
				CDC_WSA_RX_PATH_SPKR_RATE_FS_2P4_3P072);

	snd_soc_component_update_bits(comp, CDC_WSA_RX1_RX_PATH_CFG1,
				CDC_WSA_RX_PATH_SPKR_RATE_MASK,
				CDC_WSA_RX_PATH_SPKR_RATE_FS_2P4_3P072);

	wsa_macro_set_spkr_mode(comp, WSA_MACRO_SPKR_MODE_1);

	वापस 0;
पूर्ण

अटल पूर्णांक swclk_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस wsa_swrm_घड़ी(to_wsa_macro(hw), true);
पूर्ण

अटल व्योम swclk_gate_disable(काष्ठा clk_hw *hw)
अणु
	wsa_swrm_घड़ी(to_wsa_macro(hw), false);
पूर्ण

अटल पूर्णांक swclk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा wsa_macro *wsa = to_wsa_macro(hw);
	पूर्णांक ret, val;

	regmap_पढ़ो(wsa->regmap, CDC_WSA_CLK_RST_CTRL_SWR_CONTROL, &val);
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

अटल पूर्णांक wsa_macro_रेजिस्टर_mclk_output(काष्ठा wsa_macro *wsa)
अणु
	काष्ठा device *dev = wsa->dev;
	स्थिर अक्षर *parent_clk_name;
	स्थिर अक्षर *clk_name = "mclk";
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	parent_clk_name = __clk_get_name(wsa->clks[2].clk);

	init.name = clk_name;
	init.ops = &swclk_gate_ops;
	init.flags = 0;
	init.parent_names = &parent_clk_name;
	init.num_parents = 1;
	wsa->hw.init = &init;
	hw = &wsa->hw;
	ret = clk_hw_रेजिस्टर(wsa->dev, hw);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver wsa_macro_component_drv = अणु
	.name = "WSA MACRO",
	.probe = wsa_macro_component_probe,
	.controls = wsa_macro_snd_controls,
	.num_controls = ARRAY_SIZE(wsa_macro_snd_controls),
	.dapm_widमाला_लो = wsa_macro_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wsa_macro_dapm_widमाला_लो),
	.dapm_routes = wsa_audio_map,
	.num_dapm_routes = ARRAY_SIZE(wsa_audio_map),
पूर्ण;

अटल पूर्णांक wsa_macro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wsa_macro *wsa;
	व्योम __iomem *base;
	पूर्णांक ret;

	wsa = devm_kzalloc(dev, माप(*wsa), GFP_KERNEL);
	अगर (!wsa)
		वापस -ENOMEM;

	wsa->clks[0].id = "macro";
	wsa->clks[1].id = "dcodec";
	wsa->clks[2].id = "mclk";
	wsa->clks[3].id = "npl";
	wsa->clks[4].id = "fsgen";

	ret = devm_clk_bulk_get(dev, WSA_NUM_CLKS_MAX, wsa->clks);
	अगर (ret) अणु
		dev_err(dev, "Error getting WSA Clocks (%d)\n", ret);
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	wsa->regmap = devm_regmap_init_mmio(dev, base, &wsa_regmap_config);

	dev_set_drvdata(dev, wsa);

	wsa->reset_swr = true;
	wsa->dev = dev;

	/* set MCLK and NPL rates */
	clk_set_rate(wsa->clks[2].clk, WSA_MACRO_MCLK_FREQ);
	clk_set_rate(wsa->clks[3].clk, WSA_MACRO_MCLK_FREQ);

	ret = clk_bulk_prepare_enable(WSA_NUM_CLKS_MAX, wsa->clks);
	अगर (ret)
		वापस ret;

	wsa_macro_रेजिस्टर_mclk_output(wsa);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &wsa_macro_component_drv,
					      wsa_macro_dai,
					      ARRAY_SIZE(wsa_macro_dai));
	अगर (ret)
		जाओ err;

	वापस ret;
err:
	clk_bulk_disable_unprepare(WSA_NUM_CLKS_MAX, wsa->clks);

	वापस ret;

पूर्ण

अटल पूर्णांक wsa_macro_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wsa_macro *wsa = dev_get_drvdata(&pdev->dev);

	clk_bulk_disable_unprepare(WSA_NUM_CLKS_MAX, wsa->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wsa_macro_dt_match[] = अणु
	अणु.compatible = "qcom,sm8250-lpass-wsa-macro"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wsa_macro_dt_match);

अटल काष्ठा platक्रमm_driver wsa_macro_driver = अणु
	.driver = अणु
		.name = "wsa_macro",
		.of_match_table = wsa_macro_dt_match,
	पूर्ण,
	.probe = wsa_macro_probe,
	.हटाओ = wsa_macro_हटाओ,
पूर्ण;

module_platक्रमm_driver(wsa_macro_driver);
MODULE_DESCRIPTION("WSA macro driver");
MODULE_LICENSE("GPL");
