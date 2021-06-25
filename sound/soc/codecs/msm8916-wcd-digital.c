<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2016, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#घोषणा LPASS_CDC_CLK_RX_RESET_CTL		(0x000)
#घोषणा LPASS_CDC_CLK_TX_RESET_B1_CTL		(0x004)
#घोषणा CLK_RX_RESET_B1_CTL_TX1_RESET_MASK	BIT(0)
#घोषणा CLK_RX_RESET_B1_CTL_TX2_RESET_MASK	BIT(1)
#घोषणा LPASS_CDC_CLK_DMIC_B1_CTL		(0x008)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_MASK		GENMASK(3, 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_DIV2		(0x0 << 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_DIV3		(0x1 << 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_DIV4		(0x2 << 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_DIV6		(0x3 << 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_SEL_DIV16		(0x4 << 1)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_EN_MASK		BIT(0)
#घोषणा DMIC_B1_CTL_DMIC0_CLK_EN_ENABLE		BIT(0)

#घोषणा LPASS_CDC_CLK_RX_I2S_CTL		(0x00C)
#घोषणा RX_I2S_CTL_RX_I2S_MODE_MASK		BIT(5)
#घोषणा RX_I2S_CTL_RX_I2S_MODE_16		BIT(5)
#घोषणा RX_I2S_CTL_RX_I2S_MODE_32		0
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_MASK		GENMASK(2, 0)
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_8_KHZ	0x0
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_16_KHZ	0x1
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_32_KHZ	0x2
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_48_KHZ	0x3
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_96_KHZ	0x4
#घोषणा RX_I2S_CTL_RX_I2S_FS_RATE_F_192_KHZ	0x5
#घोषणा LPASS_CDC_CLK_TX_I2S_CTL		(0x010)
#घोषणा TX_I2S_CTL_TX_I2S_MODE_MASK		BIT(5)
#घोषणा TX_I2S_CTL_TX_I2S_MODE_16		BIT(5)
#घोषणा TX_I2S_CTL_TX_I2S_MODE_32		0
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_MASK		GENMASK(2, 0)
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_8_KHZ	0x0
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_16_KHZ	0x1
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_32_KHZ	0x2
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_48_KHZ	0x3
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_96_KHZ	0x4
#घोषणा TX_I2S_CTL_TX_I2S_FS_RATE_F_192_KHZ	0x5

#घोषणा LPASS_CDC_CLK_OTHR_RESET_B1_CTL		(0x014)
#घोषणा LPASS_CDC_CLK_TX_CLK_EN_B1_CTL		(0x018)
#घोषणा LPASS_CDC_CLK_OTHR_CTL			(0x01C)
#घोषणा LPASS_CDC_CLK_RX_B1_CTL			(0x020)
#घोषणा LPASS_CDC_CLK_MCLK_CTL			(0x024)
#घोषणा MCLK_CTL_MCLK_EN_MASK			BIT(0)
#घोषणा MCLK_CTL_MCLK_EN_ENABLE			BIT(0)
#घोषणा MCLK_CTL_MCLK_EN_DISABLE		0
#घोषणा LPASS_CDC_CLK_PDM_CTL			(0x028)
#घोषणा LPASS_CDC_CLK_PDM_CTL_PDM_EN_MASK	BIT(0)
#घोषणा LPASS_CDC_CLK_PDM_CTL_PDM_EN		BIT(0)
#घोषणा LPASS_CDC_CLK_PDM_CTL_PDM_CLK_SEL_MASK	BIT(1)
#घोषणा LPASS_CDC_CLK_PDM_CTL_PDM_CLK_SEL_FB	BIT(1)
#घोषणा LPASS_CDC_CLK_PDM_CTL_PDM_CLK_PDM_CLK	0

#घोषणा LPASS_CDC_CLK_SD_CTL			(0x02C)
#घोषणा LPASS_CDC_RX1_B1_CTL			(0x040)
#घोषणा LPASS_CDC_RX2_B1_CTL			(0x060)
#घोषणा LPASS_CDC_RX3_B1_CTL			(0x080)
#घोषणा LPASS_CDC_RX1_B2_CTL			(0x044)
#घोषणा LPASS_CDC_RX2_B2_CTL			(0x064)
#घोषणा LPASS_CDC_RX3_B2_CTL			(0x084)
#घोषणा LPASS_CDC_RX1_B3_CTL			(0x048)
#घोषणा LPASS_CDC_RX2_B3_CTL			(0x068)
#घोषणा LPASS_CDC_RX3_B3_CTL			(0x088)
#घोषणा LPASS_CDC_RX1_B4_CTL			(0x04C)
#घोषणा LPASS_CDC_RX2_B4_CTL			(0x06C)
#घोषणा LPASS_CDC_RX3_B4_CTL			(0x08C)
#घोषणा LPASS_CDC_RX1_B5_CTL			(0x050)
#घोषणा LPASS_CDC_RX2_B5_CTL			(0x070)
#घोषणा LPASS_CDC_RX3_B5_CTL			(0x090)
#घोषणा LPASS_CDC_RX1_B6_CTL			(0x054)
#घोषणा RXn_B6_CTL_MUTE_MASK			BIT(0)
#घोषणा RXn_B6_CTL_MUTE_ENABLE			BIT(0)
#घोषणा RXn_B6_CTL_MUTE_DISABLE			0
#घोषणा LPASS_CDC_RX2_B6_CTL			(0x074)
#घोषणा LPASS_CDC_RX3_B6_CTL			(0x094)
#घोषणा LPASS_CDC_RX1_VOL_CTL_B1_CTL		(0x058)
#घोषणा LPASS_CDC_RX2_VOL_CTL_B1_CTL		(0x078)
#घोषणा LPASS_CDC_RX3_VOL_CTL_B1_CTL		(0x098)
#घोषणा LPASS_CDC_RX1_VOL_CTL_B2_CTL		(0x05C)
#घोषणा LPASS_CDC_RX2_VOL_CTL_B2_CTL		(0x07C)
#घोषणा LPASS_CDC_RX3_VOL_CTL_B2_CTL		(0x09C)
#घोषणा LPASS_CDC_TOP_GAIN_UPDATE		(0x0A0)
#घोषणा LPASS_CDC_TOP_CTL			(0x0A4)
#घोषणा TOP_CTL_DIG_MCLK_FREQ_MASK		BIT(0)
#घोषणा TOP_CTL_DIG_MCLK_FREQ_F_12_288MHZ	0
#घोषणा TOP_CTL_DIG_MCLK_FREQ_F_9_6MHZ		BIT(0)

#घोषणा LPASS_CDC_DEBUG_DESER1_CTL		(0x0E0)
#घोषणा LPASS_CDC_DEBUG_DESER2_CTL		(0x0E4)
#घोषणा LPASS_CDC_DEBUG_B1_CTL_CFG		(0x0E8)
#घोषणा LPASS_CDC_DEBUG_B2_CTL_CFG		(0x0EC)
#घोषणा LPASS_CDC_DEBUG_B3_CTL_CFG		(0x0F0)
#घोषणा LPASS_CDC_IIR1_GAIN_B1_CTL		(0x100)
#घोषणा LPASS_CDC_IIR2_GAIN_B1_CTL		(0x140)
#घोषणा LPASS_CDC_IIR1_GAIN_B2_CTL		(0x104)
#घोषणा LPASS_CDC_IIR2_GAIN_B2_CTL		(0x144)
#घोषणा LPASS_CDC_IIR1_GAIN_B3_CTL		(0x108)
#घोषणा LPASS_CDC_IIR2_GAIN_B3_CTL		(0x148)
#घोषणा LPASS_CDC_IIR1_GAIN_B4_CTL		(0x10C)
#घोषणा LPASS_CDC_IIR2_GAIN_B4_CTL		(0x14C)
#घोषणा LPASS_CDC_IIR1_GAIN_B5_CTL		(0x110)
#घोषणा LPASS_CDC_IIR2_GAIN_B5_CTL		(0x150)
#घोषणा LPASS_CDC_IIR1_GAIN_B6_CTL		(0x114)
#घोषणा LPASS_CDC_IIR2_GAIN_B6_CTL		(0x154)
#घोषणा LPASS_CDC_IIR1_GAIN_B7_CTL		(0x118)
#घोषणा LPASS_CDC_IIR2_GAIN_B7_CTL		(0x158)
#घोषणा LPASS_CDC_IIR1_GAIN_B8_CTL		(0x11C)
#घोषणा LPASS_CDC_IIR2_GAIN_B8_CTL		(0x15C)
#घोषणा LPASS_CDC_IIR1_CTL			(0x120)
#घोषणा LPASS_CDC_IIR2_CTL			(0x160)
#घोषणा LPASS_CDC_IIR1_GAIN_TIMER_CTL		(0x124)
#घोषणा LPASS_CDC_IIR2_GAIN_TIMER_CTL		(0x164)
#घोषणा LPASS_CDC_IIR1_COEF_B1_CTL		(0x128)
#घोषणा LPASS_CDC_IIR2_COEF_B1_CTL		(0x168)
#घोषणा LPASS_CDC_IIR1_COEF_B2_CTL		(0x12C)
#घोषणा LPASS_CDC_IIR2_COEF_B2_CTL		(0x16C)
#घोषणा LPASS_CDC_CONN_RX1_B1_CTL		(0x180)
#घोषणा LPASS_CDC_CONN_RX1_B2_CTL		(0x184)
#घोषणा LPASS_CDC_CONN_RX1_B3_CTL		(0x188)
#घोषणा LPASS_CDC_CONN_RX2_B1_CTL		(0x18C)
#घोषणा LPASS_CDC_CONN_RX2_B2_CTL		(0x190)
#घोषणा LPASS_CDC_CONN_RX2_B3_CTL		(0x194)
#घोषणा LPASS_CDC_CONN_RX3_B1_CTL		(0x198)
#घोषणा LPASS_CDC_CONN_RX3_B2_CTL		(0x19C)
#घोषणा LPASS_CDC_CONN_TX_B1_CTL		(0x1A0)
#घोषणा LPASS_CDC_CONN_EQ1_B1_CTL		(0x1A8)
#घोषणा LPASS_CDC_CONN_EQ1_B2_CTL		(0x1AC)
#घोषणा LPASS_CDC_CONN_EQ1_B3_CTL		(0x1B0)
#घोषणा LPASS_CDC_CONN_EQ1_B4_CTL		(0x1B4)
#घोषणा LPASS_CDC_CONN_EQ2_B1_CTL		(0x1B8)
#घोषणा LPASS_CDC_CONN_EQ2_B2_CTL		(0x1BC)
#घोषणा LPASS_CDC_CONN_EQ2_B3_CTL		(0x1C0)
#घोषणा LPASS_CDC_CONN_EQ2_B4_CTL		(0x1C4)
#घोषणा LPASS_CDC_CONN_TX_I2S_SD1_CTL		(0x1C8)
#घोषणा LPASS_CDC_TX1_VOL_CTL_TIMER		(0x280)
#घोषणा LPASS_CDC_TX2_VOL_CTL_TIMER		(0x2A0)
#घोषणा LPASS_CDC_TX1_VOL_CTL_GAIN		(0x284)
#घोषणा LPASS_CDC_TX2_VOL_CTL_GAIN		(0x2A4)
#घोषणा LPASS_CDC_TX1_VOL_CTL_CFG		(0x288)
#घोषणा TX_VOL_CTL_CFG_MUTE_EN_MASK		BIT(0)
#घोषणा TX_VOL_CTL_CFG_MUTE_EN_ENABLE		BIT(0)

#घोषणा LPASS_CDC_TX2_VOL_CTL_CFG		(0x2A8)
#घोषणा LPASS_CDC_TX1_MUX_CTL			(0x28C)
#घोषणा TX_MUX_CTL_CUT_OFF_FREQ_MASK		GENMASK(5, 4)
#घोषणा TX_MUX_CTL_CUT_OFF_FREQ_SHIFT		4
#घोषणा TX_MUX_CTL_CF_NEG_3DB_4HZ		(0x0 << 4)
#घोषणा TX_MUX_CTL_CF_NEG_3DB_75HZ		(0x1 << 4)
#घोषणा TX_MUX_CTL_CF_NEG_3DB_150HZ		(0x2 << 4)
#घोषणा TX_MUX_CTL_HPF_BP_SEL_MASK		BIT(3)
#घोषणा TX_MUX_CTL_HPF_BP_SEL_BYPASS		BIT(3)
#घोषणा TX_MUX_CTL_HPF_BP_SEL_NO_BYPASS		0

#घोषणा LPASS_CDC_TX2_MUX_CTL			(0x2AC)
#घोषणा LPASS_CDC_TX1_CLK_FS_CTL		(0x290)
#घोषणा LPASS_CDC_TX2_CLK_FS_CTL		(0x2B0)
#घोषणा LPASS_CDC_TX1_DMIC_CTL			(0x294)
#घोषणा LPASS_CDC_TX2_DMIC_CTL			(0x2B4)
#घोषणा TXN_DMIC_CTL_CLK_SEL_MASK		GENMASK(2, 0)
#घोषणा TXN_DMIC_CTL_CLK_SEL_DIV2		0x0
#घोषणा TXN_DMIC_CTL_CLK_SEL_DIV3		0x1
#घोषणा TXN_DMIC_CTL_CLK_SEL_DIV4		0x2
#घोषणा TXN_DMIC_CTL_CLK_SEL_DIV6		0x3
#घोषणा TXN_DMIC_CTL_CLK_SEL_DIV16		0x4

#घोषणा MSM8916_WCD_DIGITAL_RATES (SNDRV_PCM_RATE_8000 | \
				   SNDRV_PCM_RATE_16000 | \
				   SNDRV_PCM_RATE_32000 | \
				   SNDRV_PCM_RATE_48000)
#घोषणा MSM8916_WCD_DIGITAL_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
				     SNDRV_PCM_FMTBIT_S32_LE)

/* Codec supports 2 IIR filters */
क्रमागत अणु
	IIR1 = 0,
	IIR2,
	IIR_MAX,
पूर्ण;

/* Codec supports 5 bands */
क्रमागत अणु
	BAND1 = 0,
	BAND2,
	BAND3,
	BAND4,
	BAND5,
	BAND_MAX,
पूर्ण;

#घोषणा WCD_IIR_FILTER_SIZE	(माप(u32)*BAND_MAX)

#घोषणा WCD_IIR_FILTER_CTL(xname, iidx, bidx) \
अणु       .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = wcd_iir_filter_info, \
	.get = msm8x16_wcd_get_iir_band_audio_mixer, \
	.put = msm8x16_wcd_put_iir_band_audio_mixer, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा wcd_iir_filter_ctl) अणु \
		.iir_idx = iidx, \
		.band_idx = bidx, \
		.bytes_ext = अणु.max = WCD_IIR_FILTER_SIZE, पूर्ण, \
	पूर्ण \
पूर्ण

काष्ठा wcd_iir_filter_ctl अणु
	अचिन्हित पूर्णांक iir_idx;
	अचिन्हित पूर्णांक band_idx;
	काष्ठा soc_bytes_ext bytes_ext;
पूर्ण;

काष्ठा msm8916_wcd_digital_priv अणु
	काष्ठा clk *ahbclk, *mclk;
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ rx_gain_reg[] = अणु
	LPASS_CDC_RX1_VOL_CTL_B2_CTL,
	LPASS_CDC_RX2_VOL_CTL_B2_CTL,
	LPASS_CDC_RX3_VOL_CTL_B2_CTL,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ tx_gain_reg[] = अणु
	LPASS_CDC_TX1_VOL_CTL_GAIN,
	LPASS_CDC_TX2_VOL_CTL_GAIN,
पूर्ण;

अटल स्थिर अक्षर *स्थिर rx_mix1_text[] = अणु
	"ZERO", "IIR1", "IIR2", "RX1", "RX2", "RX3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_mix2_text[] = अणु
	"ZERO", "IIR1", "IIR2"
पूर्ण;

अटल स्थिर अक्षर *स्थिर dec_mux_text[] = अणु
	"ZERO", "ADC1", "ADC2", "ADC3", "DMIC1", "DMIC2"
पूर्ण;

अटल स्थिर अक्षर *स्थिर cic_mux_text[] = अणु "AMIC", "DMIC" पूर्ण;

/* RX1 MIX1 */
अटल स्थिर काष्ठा soc_क्रमागत rx_mix1_inp_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX1_B1_CTL, 0, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX1_B1_CTL, 3, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX1_B2_CTL, 0, 6, rx_mix1_text),
पूर्ण;

/* RX2 MIX1 */
अटल स्थिर काष्ठा soc_क्रमागत rx2_mix1_inp_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX2_B1_CTL, 0, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX2_B1_CTL, 3, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX2_B2_CTL, 0, 6, rx_mix1_text),
पूर्ण;

/* RX3 MIX1 */
अटल स्थिर काष्ठा soc_क्रमागत rx3_mix1_inp_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX3_B1_CTL, 0, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX3_B1_CTL, 3, 6, rx_mix1_text),
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX3_B2_CTL, 0, 6, rx_mix1_text),
पूर्ण;

/* RX1 MIX2 */
अटल स्थिर काष्ठा soc_क्रमागत rx_mix2_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX1_B3_CTL,
		0, 3, rx_mix2_text);

/* RX2 MIX2 */
अटल स्थिर काष्ठा soc_क्रमागत rx2_mix2_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_RX2_B3_CTL,
		0, 3, rx_mix2_text);

/* DEC */
अटल स्थिर काष्ठा soc_क्रमागत dec1_mux_क्रमागत = SOC_ENUM_SINGLE(
				LPASS_CDC_CONN_TX_B1_CTL, 0, 6, dec_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत dec2_mux_क्रमागत = SOC_ENUM_SINGLE(
				LPASS_CDC_CONN_TX_B1_CTL, 3, 6, dec_mux_text);

/* CIC */
अटल स्थिर काष्ठा soc_क्रमागत cic1_mux_क्रमागत = SOC_ENUM_SINGLE(
				LPASS_CDC_TX1_MUX_CTL, 0, 2, cic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cic2_mux_क्रमागत = SOC_ENUM_SINGLE(
				LPASS_CDC_TX2_MUX_CTL, 0, 2, cic_mux_text);

/* RDAC2 MUX */
अटल स्थिर काष्ठा snd_kcontrol_new dec1_mux = SOC_DAPM_ENUM(
				"DEC1 MUX Mux", dec1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new dec2_mux = SOC_DAPM_ENUM(
				"DEC2 MUX Mux",	dec2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cic1_mux = SOC_DAPM_ENUM(
				"CIC1 MUX Mux", cic1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cic2_mux = SOC_DAPM_ENUM(
				"CIC2 MUX Mux",	cic2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new rx_mix1_inp1_mux = SOC_DAPM_ENUM(
				"RX1 MIX1 INP1 Mux", rx_mix1_inp_क्रमागत[0]);
अटल स्थिर काष्ठा snd_kcontrol_new rx_mix1_inp2_mux = SOC_DAPM_ENUM(
				"RX1 MIX1 INP2 Mux", rx_mix1_inp_क्रमागत[1]);
अटल स्थिर काष्ठा snd_kcontrol_new rx_mix1_inp3_mux = SOC_DAPM_ENUM(
				"RX1 MIX1 INP3 Mux", rx_mix1_inp_क्रमागत[2]);
अटल स्थिर काष्ठा snd_kcontrol_new rx2_mix1_inp1_mux = SOC_DAPM_ENUM(
				"RX2 MIX1 INP1 Mux", rx2_mix1_inp_क्रमागत[0]);
अटल स्थिर काष्ठा snd_kcontrol_new rx2_mix1_inp2_mux = SOC_DAPM_ENUM(
				"RX2 MIX1 INP2 Mux", rx2_mix1_inp_क्रमागत[1]);
अटल स्थिर काष्ठा snd_kcontrol_new rx2_mix1_inp3_mux = SOC_DAPM_ENUM(
				"RX2 MIX1 INP3 Mux", rx2_mix1_inp_क्रमागत[2]);
अटल स्थिर काष्ठा snd_kcontrol_new rx3_mix1_inp1_mux = SOC_DAPM_ENUM(
				"RX3 MIX1 INP1 Mux", rx3_mix1_inp_क्रमागत[0]);
अटल स्थिर काष्ठा snd_kcontrol_new rx3_mix1_inp2_mux = SOC_DAPM_ENUM(
				"RX3 MIX1 INP2 Mux", rx3_mix1_inp_क्रमागत[1]);
अटल स्थिर काष्ठा snd_kcontrol_new rx3_mix1_inp3_mux = SOC_DAPM_ENUM(
				"RX3 MIX1 INP3 Mux", rx3_mix1_inp_क्रमागत[2]);
अटल स्थिर काष्ठा snd_kcontrol_new rx1_mix2_inp1_mux = SOC_DAPM_ENUM(
				"RX1 MIX2 INP1 Mux", rx_mix2_inp1_chain_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new rx2_mix2_inp1_mux = SOC_DAPM_ENUM(
				"RX2 MIX2 INP1 Mux", rx2_mix2_inp1_chain_क्रमागत);

/* Digital Gain control -38.4 dB to +38.4 dB in 0.3 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -3840, 30, 0);

/* Cutoff Freq क्रम High Pass Filter at -3dB */
अटल स्थिर अक्षर * स्थिर hpf_cutoff_text[] = अणु
	"4Hz", "75Hz", "150Hz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(tx1_hpf_cutoff_क्रमागत, LPASS_CDC_TX1_MUX_CTL, 4,
			    hpf_cutoff_text);
अटल SOC_ENUM_SINGLE_DECL(tx2_hpf_cutoff_क्रमागत, LPASS_CDC_TX2_MUX_CTL, 4,
			    hpf_cutoff_text);

/* cut off क्रम dc blocker inside rx chain */
अटल स्थिर अक्षर * स्थिर dc_blocker_cutoff_text[] = अणु
	"4Hz", "75Hz", "150Hz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rx1_dcb_cutoff_क्रमागत, LPASS_CDC_RX1_B4_CTL, 0,
			    dc_blocker_cutoff_text);
अटल SOC_ENUM_SINGLE_DECL(rx2_dcb_cutoff_क्रमागत, LPASS_CDC_RX2_B4_CTL, 0,
			    dc_blocker_cutoff_text);
अटल SOC_ENUM_SINGLE_DECL(rx3_dcb_cutoff_क्रमागत, LPASS_CDC_RX3_B4_CTL, 0,
			    dc_blocker_cutoff_text);

अटल पूर्णांक msm8x16_wcd_codec_set_iir_gain(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	पूर्णांक value = 0, reg = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (w->shअगरt == 0)
			reg = LPASS_CDC_IIR1_GAIN_B1_CTL;
		अन्यथा अगर (w->shअगरt == 1)
			reg = LPASS_CDC_IIR2_GAIN_B1_CTL;
		value = snd_soc_component_पढ़ो(component, reg);
		snd_soc_component_ग_लिखो(component, reg, value);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t get_iir_band_coeff(काष्ठा snd_soc_component *component,
				   पूर्णांक iir_idx, पूर्णांक band_idx,
				   पूर्णांक coeff_idx)
अणु
	uपूर्णांक32_t value = 0;

	/* Address करोes not स्वतःmatically update अगर पढ़ोing */
	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		((band_idx * BAND_MAX + coeff_idx)
		* माप(uपूर्णांक32_t)) & 0x7F);

	value |= snd_soc_component_पढ़ो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx));

	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		((band_idx * BAND_MAX + coeff_idx)
		* माप(uपूर्णांक32_t) + 1) & 0x7F);

	value |= (snd_soc_component_पढ़ो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx)) << 8);

	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		((band_idx * BAND_MAX + coeff_idx)
		* माप(uपूर्णांक32_t) + 2) & 0x7F);

	value |= (snd_soc_component_पढ़ो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx)) << 16);

	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		((band_idx * BAND_MAX + coeff_idx)
		* माप(uपूर्णांक32_t) + 3) & 0x7F);

	/* Mask bits top 2 bits since they are reserved */
	value |= ((snd_soc_component_पढ़ो(component,
		 (LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx)) & 0x3f) << 24);
	वापस value;

पूर्ण

अटल पूर्णांक msm8x16_wcd_get_iir_band_audio_mixer(
					काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु

	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा wcd_iir_filter_ctl *ctl =
			(काष्ठा wcd_iir_filter_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;
	पूर्णांक iir_idx = ctl->iir_idx;
	पूर्णांक band_idx = ctl->band_idx;
	u32 coeff[BAND_MAX];

	coeff[0] = get_iir_band_coeff(component, iir_idx, band_idx, 0);
	coeff[1] = get_iir_band_coeff(component, iir_idx, band_idx, 1);
	coeff[2] = get_iir_band_coeff(component, iir_idx, band_idx, 2);
	coeff[3] = get_iir_band_coeff(component, iir_idx, band_idx, 3);
	coeff[4] = get_iir_band_coeff(component, iir_idx, band_idx, 4);

	स_नकल(ucontrol->value.bytes.data, &coeff[0], params->max);

	वापस 0;
पूर्ण

अटल व्योम set_iir_band_coeff(काष्ठा snd_soc_component *component,
				पूर्णांक iir_idx, पूर्णांक band_idx,
				uपूर्णांक32_t value)
अणु
	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx),
		(value & 0xFF));

	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx),
		(value >> 8) & 0xFF);

	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx),
		(value >> 16) & 0xFF);

	/* Mask top 2 bits, 7-8 are reserved */
	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B2_CTL + 64 * iir_idx),
		(value >> 24) & 0x3F);
पूर्ण

अटल पूर्णांक msm8x16_wcd_put_iir_band_audio_mixer(
					काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा wcd_iir_filter_ctl *ctl =
			(काष्ठा wcd_iir_filter_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;
	पूर्णांक iir_idx = ctl->iir_idx;
	पूर्णांक band_idx = ctl->band_idx;
	u32 coeff[BAND_MAX];

	स_नकल(&coeff[0], ucontrol->value.bytes.data, params->max);

	/* Mask top bit it is reserved */
	/* Updates addr स्वतःmatically क्रम each B2 ग_लिखो */
	snd_soc_component_ग_लिखो(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		(band_idx * BAND_MAX * माप(uपूर्णांक32_t)) & 0x7F);

	set_iir_band_coeff(component, iir_idx, band_idx, coeff[0]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[1]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[2]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[3]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[4]);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd_iir_filter_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *ucontrol)
अणु
	काष्ठा wcd_iir_filter_ctl *ctl =
		(काष्ठा wcd_iir_filter_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;

	ucontrol->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	ucontrol->count = params->max;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new msm8916_wcd_digital_snd_controls[] = अणु
	SOC_SINGLE_S8_TLV("RX1 Digital Volume", LPASS_CDC_RX1_VOL_CTL_B2_CTL,
			  -128, 127, digital_gain),
	SOC_SINGLE_S8_TLV("RX2 Digital Volume", LPASS_CDC_RX2_VOL_CTL_B2_CTL,
			  -128, 127, digital_gain),
	SOC_SINGLE_S8_TLV("RX3 Digital Volume", LPASS_CDC_RX3_VOL_CTL_B2_CTL,
			  -128, 127, digital_gain),
	SOC_SINGLE_S8_TLV("TX1 Digital Volume", LPASS_CDC_TX1_VOL_CTL_GAIN,
			  -128, 127, digital_gain),
	SOC_SINGLE_S8_TLV("TX2 Digital Volume", LPASS_CDC_TX2_VOL_CTL_GAIN,
			  -128, 127, digital_gain),
	SOC_ENUM("TX1 HPF Cutoff", tx1_hpf_cutoff_क्रमागत),
	SOC_ENUM("TX2 HPF Cutoff", tx2_hpf_cutoff_क्रमागत),
	SOC_SINGLE("TX1 HPF Switch", LPASS_CDC_TX1_MUX_CTL, 3, 1, 0),
	SOC_SINGLE("TX2 HPF Switch", LPASS_CDC_TX2_MUX_CTL, 3, 1, 0),
	SOC_ENUM("RX1 DCB Cutoff", rx1_dcb_cutoff_क्रमागत),
	SOC_ENUM("RX2 DCB Cutoff", rx2_dcb_cutoff_क्रमागत),
	SOC_ENUM("RX3 DCB Cutoff", rx3_dcb_cutoff_क्रमागत),
	SOC_SINGLE("RX1 DCB Switch", LPASS_CDC_RX1_B5_CTL, 2, 1, 0),
	SOC_SINGLE("RX2 DCB Switch", LPASS_CDC_RX2_B5_CTL, 2, 1, 0),
	SOC_SINGLE("RX3 DCB Switch", LPASS_CDC_RX3_B5_CTL, 2, 1, 0),
	SOC_SINGLE("RX1 Mute Switch", LPASS_CDC_RX1_B6_CTL, 0, 1, 0),
	SOC_SINGLE("RX2 Mute Switch", LPASS_CDC_RX2_B6_CTL, 0, 1, 0),
	SOC_SINGLE("RX3 Mute Switch", LPASS_CDC_RX3_B6_CTL, 0, 1, 0),

	SOC_SINGLE("IIR1 Band1 Switch", LPASS_CDC_IIR1_CTL, 0, 1, 0),
	SOC_SINGLE("IIR1 Band2 Switch", LPASS_CDC_IIR1_CTL, 1, 1, 0),
	SOC_SINGLE("IIR1 Band3 Switch", LPASS_CDC_IIR1_CTL, 2, 1, 0),
	SOC_SINGLE("IIR1 Band4 Switch", LPASS_CDC_IIR1_CTL, 3, 1, 0),
	SOC_SINGLE("IIR1 Band5 Switch", LPASS_CDC_IIR1_CTL, 4, 1, 0),
	SOC_SINGLE("IIR2 Band1 Switch", LPASS_CDC_IIR2_CTL, 0, 1, 0),
	SOC_SINGLE("IIR2 Band2 Switch", LPASS_CDC_IIR2_CTL, 1, 1, 0),
	SOC_SINGLE("IIR2 Band3 Switch", LPASS_CDC_IIR2_CTL, 2, 1, 0),
	SOC_SINGLE("IIR2 Band4 Switch", LPASS_CDC_IIR2_CTL, 3, 1, 0),
	SOC_SINGLE("IIR2 Band5 Switch", LPASS_CDC_IIR2_CTL, 4, 1, 0),
	WCD_IIR_FILTER_CTL("IIR1 Band1", IIR1, BAND1),
	WCD_IIR_FILTER_CTL("IIR1 Band2", IIR1, BAND2),
	WCD_IIR_FILTER_CTL("IIR1 Band3", IIR1, BAND3),
	WCD_IIR_FILTER_CTL("IIR1 Band4", IIR1, BAND4),
	WCD_IIR_FILTER_CTL("IIR1 Band5", IIR1, BAND5),
	WCD_IIR_FILTER_CTL("IIR2 Band1", IIR2, BAND1),
	WCD_IIR_FILTER_CTL("IIR2 Band2", IIR2, BAND2),
	WCD_IIR_FILTER_CTL("IIR2 Band3", IIR2, BAND3),
	WCD_IIR_FILTER_CTL("IIR2 Band4", IIR2, BAND4),
	WCD_IIR_FILTER_CTL("IIR2 Band5", IIR2, BAND5),
	SOC_SINGLE_SX_TLV("IIR1 INP1 Volume", LPASS_CDC_IIR1_GAIN_B1_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR1 INP2 Volume", LPASS_CDC_IIR1_GAIN_B2_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR1 INP3 Volume", LPASS_CDC_IIR1_GAIN_B3_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR1 INP4 Volume", LPASS_CDC_IIR1_GAIN_B4_CTL,
			0,  -84,	40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR2 INP1 Volume", LPASS_CDC_IIR2_GAIN_B1_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR2 INP2 Volume", LPASS_CDC_IIR2_GAIN_B2_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR2 INP3 Volume", LPASS_CDC_IIR2_GAIN_B3_CTL,
			0,  -84, 40, digital_gain),
	SOC_SINGLE_SX_TLV("IIR2 INP4 Volume", LPASS_CDC_IIR2_GAIN_B4_CTL,
			0,  -84, 40, digital_gain),

पूर्ण;

अटल पूर्णांक msm8916_wcd_digital_enable_पूर्णांकerpolator(
						काष्ठा snd_soc_dapm_widget *w,
						काष्ठा snd_kcontrol *kcontrol,
						पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* apply the digital gain after the पूर्णांकerpolator is enabled */
		usleep_range(10000, 10100);
		snd_soc_component_ग_लिखो(component, rx_gain_reg[w->shअगरt],
			      snd_soc_component_पढ़ो(component, rx_gain_reg[w->shअगरt]));
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, LPASS_CDC_CLK_RX_RESET_CTL,
					      1 << w->shअगरt, 1 << w->shअगरt);
		snd_soc_component_update_bits(component, LPASS_CDC_CLK_RX_RESET_CTL,
					      1 << w->shअगरt, 0x0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_enable_dec(काष्ठा snd_soc_dapm_widget *w,
					  काष्ठा snd_kcontrol *kcontrol,
					  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक decimator = w->shअगरt + 1;
	u16 dec_reset_reg, tx_vol_ctl_reg, tx_mux_ctl_reg;
	u8 dec_hpf_cut_of_freq;

	dec_reset_reg = LPASS_CDC_CLK_TX_RESET_B1_CTL;
	tx_vol_ctl_reg = LPASS_CDC_TX1_VOL_CTL_CFG + 32 * (decimator - 1);
	tx_mux_ctl_reg = LPASS_CDC_TX1_MUX_CTL + 32 * (decimator - 1);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable TX digital mute */
		snd_soc_component_update_bits(component, tx_vol_ctl_reg,
				    TX_VOL_CTL_CFG_MUTE_EN_MASK,
				    TX_VOL_CTL_CFG_MUTE_EN_ENABLE);
		dec_hpf_cut_of_freq = snd_soc_component_पढ़ो(component, tx_mux_ctl_reg) &
					TX_MUX_CTL_CUT_OFF_FREQ_MASK;
		dec_hpf_cut_of_freq >>= TX_MUX_CTL_CUT_OFF_FREQ_SHIFT;
		अगर (dec_hpf_cut_of_freq != TX_MUX_CTL_CF_NEG_3DB_150HZ) अणु
			/* set cut of freq to CF_MIN_3DB_150HZ (0x1) */
			snd_soc_component_update_bits(component, tx_mux_ctl_reg,
					    TX_MUX_CTL_CUT_OFF_FREQ_MASK,
					    TX_MUX_CTL_CF_NEG_3DB_150HZ);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* enable HPF */
		snd_soc_component_update_bits(component, tx_mux_ctl_reg,
				    TX_MUX_CTL_HPF_BP_SEL_MASK,
				    TX_MUX_CTL_HPF_BP_SEL_NO_BYPASS);
		/* apply the digital gain after the decimator is enabled */
		snd_soc_component_ग_लिखो(component, tx_gain_reg[w->shअगरt],
			      snd_soc_component_पढ़ो(component, tx_gain_reg[w->shअगरt]));
		snd_soc_component_update_bits(component, tx_vol_ctl_reg,
				    TX_VOL_CTL_CFG_MUTE_EN_MASK, 0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, tx_vol_ctl_reg,
				    TX_VOL_CTL_CFG_MUTE_EN_MASK,
				    TX_VOL_CTL_CFG_MUTE_EN_ENABLE);
		snd_soc_component_update_bits(component, tx_mux_ctl_reg,
				    TX_MUX_CTL_HPF_BP_SEL_MASK,
				    TX_MUX_CTL_HPF_BP_SEL_BYPASS);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, dec_reset_reg, 1 << w->shअगरt,
				    1 << w->shअगरt);
		snd_soc_component_update_bits(component, dec_reset_reg, 1 << w->shअगरt, 0x0);
		snd_soc_component_update_bits(component, tx_mux_ctl_reg,
				    TX_MUX_CTL_HPF_BP_SEL_MASK,
				    TX_MUX_CTL_HPF_BP_SEL_BYPASS);
		snd_soc_component_update_bits(component, tx_vol_ctl_reg,
				    TX_VOL_CTL_CFG_MUTE_EN_MASK, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_enable_dmic(काष्ठा snd_soc_dapm_widget *w,
					   काष्ठा snd_kcontrol *kcontrol,
					   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक dmic;
	पूर्णांक ret;
	/* get dmic number out of widget name */
	अक्षर *dmic_num = strpbrk(w->name, "12");

	अगर (dmic_num == शून्य) अणु
		dev_err(component->dev, "Invalid DMIC\n");
		वापस -EINVAL;
	पूर्ण
	ret = kstrtouपूर्णांक(dmic_num, 10, &dmic);
	अगर (ret < 0 || dmic > 2) अणु
		dev_err(component->dev, "Invalid DMIC line on the component\n");
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, LPASS_CDC_CLK_DMIC_B1_CTL,
				    DMIC_B1_CTL_DMIC0_CLK_SEL_MASK,
				    DMIC_B1_CTL_DMIC0_CLK_SEL_DIV3);
		चयन (dmic) अणु
		हाल 1:
			snd_soc_component_update_bits(component, LPASS_CDC_TX1_DMIC_CTL,
					    TXN_DMIC_CTL_CLK_SEL_MASK,
					    TXN_DMIC_CTL_CLK_SEL_DIV3);
			अवरोध;
		हाल 2:
			snd_soc_component_update_bits(component, LPASS_CDC_TX2_DMIC_CTL,
					    TXN_DMIC_CTL_CLK_SEL_MASK,
					    TXN_DMIC_CTL_CLK_SEL_DIV3);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर iir_inp1_text[] = अणु
	"ZERO", "DEC1", "DEC2", "RX1", "RX2", "RX3"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत iir1_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_EQ1_B1_CTL,
		0, 6, iir_inp1_text);

अटल स्थिर काष्ठा soc_क्रमागत iir2_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(LPASS_CDC_CONN_EQ2_B1_CTL,
		0, 6, iir_inp1_text);

अटल स्थिर काष्ठा snd_kcontrol_new iir1_inp1_mux =
	SOC_DAPM_ENUM("IIR1 INP1 Mux", iir1_inp1_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new iir2_inp1_mux =
	SOC_DAPM_ENUM("IIR2 INP1 Mux", iir2_inp1_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget msm8916_wcd_digital_dapm_widमाला_लो[] = अणु
	/*RX stuff */
	SND_SOC_DAPM_AIF_IN("I2S RX1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("I2S RX2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("I2S RX3", शून्य, 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("PDM_RX1"),
	SND_SOC_DAPM_OUTPUT("PDM_RX2"),
	SND_SOC_DAPM_OUTPUT("PDM_RX3"),

	SND_SOC_DAPM_INPUT("LPASS_PDM_TX"),

	SND_SOC_DAPM_MIXER("RX1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX2 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX3 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Interpolator */
	SND_SOC_DAPM_MIXER_E("RX1 INT", LPASS_CDC_CLK_RX_B1_CTL, 0, 0, शून्य,
			     0, msm8916_wcd_digital_enable_पूर्णांकerpolator,
			     SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER_E("RX2 INT", LPASS_CDC_CLK_RX_B1_CTL, 1, 0, शून्य,
			     0, msm8916_wcd_digital_enable_पूर्णांकerpolator,
			     SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER_E("RX3 INT", LPASS_CDC_CLK_RX_B1_CTL, 2, 0, शून्य,
			     0, msm8916_wcd_digital_enable_पूर्णांकerpolator,
			     SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("RX1 MIX1 INP1", SND_SOC_NOPM, 0, 0,
			 &rx_mix1_inp1_mux),
	SND_SOC_DAPM_MUX("RX1 MIX1 INP2", SND_SOC_NOPM, 0, 0,
			 &rx_mix1_inp2_mux),
	SND_SOC_DAPM_MUX("RX1 MIX1 INP3", SND_SOC_NOPM, 0, 0,
			 &rx_mix1_inp3_mux),
	SND_SOC_DAPM_MUX("RX2 MIX1 INP1", SND_SOC_NOPM, 0, 0,
			 &rx2_mix1_inp1_mux),
	SND_SOC_DAPM_MUX("RX2 MIX1 INP2", SND_SOC_NOPM, 0, 0,
			 &rx2_mix1_inp2_mux),
	SND_SOC_DAPM_MUX("RX2 MIX1 INP3", SND_SOC_NOPM, 0, 0,
			 &rx2_mix1_inp3_mux),
	SND_SOC_DAPM_MUX("RX3 MIX1 INP1", SND_SOC_NOPM, 0, 0,
			 &rx3_mix1_inp1_mux),
	SND_SOC_DAPM_MUX("RX3 MIX1 INP2", SND_SOC_NOPM, 0, 0,
			 &rx3_mix1_inp2_mux),
	SND_SOC_DAPM_MUX("RX3 MIX1 INP3", SND_SOC_NOPM, 0, 0,
			 &rx3_mix1_inp3_mux),
	SND_SOC_DAPM_MUX("RX1 MIX2 INP1", SND_SOC_NOPM, 0, 0,
			 &rx1_mix2_inp1_mux),
	SND_SOC_DAPM_MUX("RX2 MIX2 INP1", SND_SOC_NOPM, 0, 0,
			 &rx2_mix2_inp1_mux),

	SND_SOC_DAPM_MUX("CIC1 MUX", SND_SOC_NOPM, 0, 0, &cic1_mux),
	SND_SOC_DAPM_MUX("CIC2 MUX", SND_SOC_NOPM, 0, 0, &cic2_mux),
	/* TX */
	SND_SOC_DAPM_MIXER("ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX_E("DEC1 MUX", LPASS_CDC_CLK_TX_CLK_EN_B1_CTL, 0, 0,
			   &dec1_mux, msm8916_wcd_digital_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("DEC2 MUX", LPASS_CDC_CLK_TX_CLK_EN_B1_CTL, 1, 0,
			   &dec2_mux, msm8916_wcd_digital_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("I2S TX1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("I2S TX2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("I2S TX3", शून्य, 0, SND_SOC_NOPM, 0, 0),

	/* Digital Mic Inमाला_दो */
	SND_SOC_DAPM_ADC_E("DMIC1", शून्य, SND_SOC_NOPM, 0, 0,
			   msm8916_wcd_digital_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC2", शून्य, SND_SOC_NOPM, 0, 0,
			   msm8916_wcd_digital_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("DMIC_CLK", LPASS_CDC_CLK_DMIC_B1_CTL, 0, 0,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RX_I2S_CLK", LPASS_CDC_CLK_RX_I2S_CTL,
			    4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("TX_I2S_CLK", LPASS_CDC_CLK_TX_I2S_CTL, 4, 0,
			    शून्य, 0),

	SND_SOC_DAPM_SUPPLY("MCLK", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PDM_CLK", LPASS_CDC_CLK_PDM_CTL, 0, 0, शून्य, 0),
	/* Connectivity Clock */
	SND_SOC_DAPM_SUPPLY_S("CDC_CONN", -2, LPASS_CDC_CLK_OTHR_CTL, 2, 0,
			      शून्य, 0),
	SND_SOC_DAPM_MIC("Digital Mic1", शून्य),
	SND_SOC_DAPM_MIC("Digital Mic2", शून्य),

	/* Sidetone */
	SND_SOC_DAPM_MUX("IIR1 INP1 MUX", SND_SOC_NOPM, 0, 0, &iir1_inp1_mux),
	SND_SOC_DAPM_PGA_E("IIR1", LPASS_CDC_CLK_SD_CTL, 0, 0, शून्य, 0,
		msm8x16_wcd_codec_set_iir_gain, SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_MUX("IIR2 INP1 MUX", SND_SOC_NOPM, 0, 0, &iir2_inp1_mux),
	SND_SOC_DAPM_PGA_E("IIR2", LPASS_CDC_CLK_SD_CTL, 1, 0, शून्य, 0,
		msm8x16_wcd_codec_set_iir_gain, SND_SOC_DAPM_POST_PMU),

पूर्ण;

अटल पूर्णांक msm8916_wcd_digital_get_clks(काष्ठा platक्रमm_device *pdev,
					काष्ठा msm8916_wcd_digital_priv	*priv)
अणु
	काष्ठा device *dev = &pdev->dev;

	priv->ahbclk = devm_clk_get(dev, "ahbix-clk");
	अगर (IS_ERR(priv->ahbclk)) अणु
		dev_err(dev, "failed to get ahbix clk\n");
		वापस PTR_ERR(priv->ahbclk);
	पूर्ण

	priv->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(priv->mclk)) अणु
		dev_err(dev, "failed to get mclk\n");
		वापस PTR_ERR(priv->mclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा msm8916_wcd_digital_priv *priv = dev_get_drvdata(component->dev);

	snd_soc_component_set_drvdata(component, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_component_set_sysclk(काष्ठा snd_soc_component *component,
						पूर्णांक clk_id, पूर्णांक source,
						अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा msm8916_wcd_digital_priv *p = dev_get_drvdata(component->dev);

	वापस clk_set_rate(p->mclk, freq);
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *params,
					 काष्ठा snd_soc_dai *dai)
अणु
	u8 tx_fs_rate;
	u8 rx_fs_rate;

	चयन (params_rate(params)) अणु
	हाल 8000:
		tx_fs_rate = TX_I2S_CTL_TX_I2S_FS_RATE_F_8_KHZ;
		rx_fs_rate = RX_I2S_CTL_RX_I2S_FS_RATE_F_8_KHZ;
		अवरोध;
	हाल 16000:
		tx_fs_rate = TX_I2S_CTL_TX_I2S_FS_RATE_F_16_KHZ;
		rx_fs_rate = RX_I2S_CTL_RX_I2S_FS_RATE_F_16_KHZ;
		अवरोध;
	हाल 32000:
		tx_fs_rate = TX_I2S_CTL_TX_I2S_FS_RATE_F_32_KHZ;
		rx_fs_rate = RX_I2S_CTL_RX_I2S_FS_RATE_F_32_KHZ;
		अवरोध;
	हाल 48000:
		tx_fs_rate = TX_I2S_CTL_TX_I2S_FS_RATE_F_48_KHZ;
		rx_fs_rate = RX_I2S_CTL_RX_I2S_FS_RATE_F_48_KHZ;
		अवरोध;
	शेष:
		dev_err(dai->component->dev, "Invalid sampling rate %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_CAPTURE:
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_TX_I2S_CTL,
				    TX_I2S_CTL_TX_I2S_FS_RATE_MASK, tx_fs_rate);
		अवरोध;
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_RX_I2S_CTL,
				    RX_I2S_CTL_RX_I2S_FS_RATE_MASK, rx_fs_rate);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_TX_I2S_CTL,
				    TX_I2S_CTL_TX_I2S_MODE_MASK,
				    TX_I2S_CTL_TX_I2S_MODE_16);
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_RX_I2S_CTL,
				    RX_I2S_CTL_RX_I2S_MODE_MASK,
				    RX_I2S_CTL_RX_I2S_MODE_16);
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_TX_I2S_CTL,
				    TX_I2S_CTL_TX_I2S_MODE_MASK,
				    TX_I2S_CTL_TX_I2S_MODE_32);
		snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_RX_I2S_CTL,
				    RX_I2S_CTL_RX_I2S_MODE_MASK,
				    RX_I2S_CTL_RX_I2S_MODE_32);
		अवरोध;
	शेष:
		dev_err(dai->dev, "%s: wrong format selected\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route msm8916_wcd_digital_audio_map[] = अणु

	अणु"I2S RX1",  शून्य, "AIF1 Playback"पूर्ण,
	अणु"I2S RX2",  शून्य, "AIF1 Playback"पूर्ण,
	अणु"I2S RX3",  शून्य, "AIF1 Playback"पूर्ण,

	अणु"AIF1 Capture", शून्य, "I2S TX1"पूर्ण,
	अणु"AIF1 Capture", शून्य, "I2S TX2"पूर्ण,
	अणु"AIF1 Capture", शून्य, "I2S TX3"पूर्ण,

	अणु"CIC1 MUX", "DMIC", "DEC1 MUX"पूर्ण,
	अणु"CIC1 MUX", "AMIC", "DEC1 MUX"पूर्ण,
	अणु"CIC2 MUX", "DMIC", "DEC2 MUX"पूर्ण,
	अणु"CIC2 MUX", "AMIC", "DEC2 MUX"पूर्ण,

	/* Decimator Inमाला_दो */
	अणु"DEC1 MUX", "DMIC1", "DMIC1"पूर्ण,
	अणु"DEC1 MUX", "DMIC2", "DMIC2"पूर्ण,
	अणु"DEC1 MUX", "ADC1", "ADC1"पूर्ण,
	अणु"DEC1 MUX", "ADC2", "ADC2"पूर्ण,
	अणु"DEC1 MUX", "ADC3", "ADC3"पूर्ण,
	अणु"DEC1 MUX", शून्य, "CDC_CONN"पूर्ण,

	अणु"DEC2 MUX", "DMIC1", "DMIC1"पूर्ण,
	अणु"DEC2 MUX", "DMIC2", "DMIC2"पूर्ण,
	अणु"DEC2 MUX", "ADC1", "ADC1"पूर्ण,
	अणु"DEC2 MUX", "ADC2", "ADC2"पूर्ण,
	अणु"DEC2 MUX", "ADC3", "ADC3"पूर्ण,
	अणु"DEC2 MUX", शून्य, "CDC_CONN"पूर्ण,

	अणु"DMIC1", शून्य, "DMIC_CLK"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC_CLK"पूर्ण,

	अणु"I2S TX1", शून्य, "CIC1 MUX"पूर्ण,
	अणु"I2S TX2", शून्य, "CIC2 MUX"पूर्ण,

	अणु"I2S TX1", शून्य, "TX_I2S_CLK"पूर्ण,
	अणु"I2S TX2", शून्य, "TX_I2S_CLK"पूर्ण,

	अणु"TX_I2S_CLK", शून्य, "MCLK"पूर्ण,
	अणु"TX_I2S_CLK", शून्य, "PDM_CLK"पूर्ण,

	अणु"ADC1", शून्य, "LPASS_PDM_TX"पूर्ण,
	अणु"ADC2", शून्य, "LPASS_PDM_TX"पूर्ण,
	अणु"ADC3", शून्य, "LPASS_PDM_TX"पूर्ण,

	अणु"I2S RX1", शून्य, "RX_I2S_CLK"पूर्ण,
	अणु"I2S RX2", शून्य, "RX_I2S_CLK"पूर्ण,
	अणु"I2S RX3", शून्य, "RX_I2S_CLK"पूर्ण,

	अणु"RX_I2S_CLK", शून्य, "PDM_CLK"पूर्ण,
	अणु"RX_I2S_CLK", शून्य, "MCLK"पूर्ण,
	अणु"RX_I2S_CLK", शून्य, "CDC_CONN"पूर्ण,

	/* RX1 PATH.. */
	अणु"PDM_RX1", शून्य, "RX1 INT"पूर्ण,
	अणु"RX1 INT", शून्य, "RX1 MIX1"पूर्ण,

	अणु"RX1 MIX1", शून्य, "RX1 MIX1 INP1"पूर्ण,
	अणु"RX1 MIX1", शून्य, "RX1 MIX1 INP2"पूर्ण,
	अणु"RX1 MIX1", शून्य, "RX1 MIX1 INP3"पूर्ण,

	अणु"RX1 MIX1 INP1", "RX1", "I2S RX1"पूर्ण,
	अणु"RX1 MIX1 INP1", "RX2", "I2S RX2"पूर्ण,
	अणु"RX1 MIX1 INP1", "RX3", "I2S RX3"पूर्ण,
	अणु"RX1 MIX1 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX1 MIX1 INP1", "IIR2", "IIR2"पूर्ण,

	अणु"RX1 MIX1 INP2", "RX1", "I2S RX1"पूर्ण,
	अणु"RX1 MIX1 INP2", "RX2", "I2S RX2"पूर्ण,
	अणु"RX1 MIX1 INP2", "RX3", "I2S RX3"पूर्ण,
	अणु"RX1 MIX1 INP2", "IIR1", "IIR1"पूर्ण,
	अणु"RX1 MIX1 INP2", "IIR2", "IIR2"पूर्ण,

	अणु"RX1 MIX1 INP3", "RX1", "I2S RX1"पूर्ण,
	अणु"RX1 MIX1 INP3", "RX2", "I2S RX2"पूर्ण,
	अणु"RX1 MIX1 INP3", "RX3", "I2S RX3"पूर्ण,

	/* RX2 PATH */
	अणु"PDM_RX2", शून्य, "RX2 INT"पूर्ण,
	अणु"RX2 INT", शून्य, "RX2 MIX1"पूर्ण,

	अणु"RX2 MIX1", शून्य, "RX2 MIX1 INP1"पूर्ण,
	अणु"RX2 MIX1", शून्य, "RX2 MIX1 INP2"पूर्ण,
	अणु"RX2 MIX1", शून्य, "RX2 MIX1 INP3"पूर्ण,

	अणु"RX2 MIX1 INP1", "RX1", "I2S RX1"पूर्ण,
	अणु"RX2 MIX1 INP1", "RX2", "I2S RX2"पूर्ण,
	अणु"RX2 MIX1 INP1", "RX3", "I2S RX3"पूर्ण,
	अणु"RX2 MIX1 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX2 MIX1 INP1", "IIR2", "IIR2"पूर्ण,

	अणु"RX2 MIX1 INP2", "RX1", "I2S RX1"पूर्ण,
	अणु"RX2 MIX1 INP2", "RX2", "I2S RX2"पूर्ण,
	अणु"RX2 MIX1 INP2", "RX3", "I2S RX3"पूर्ण,
	अणु"RX2 MIX1 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX2 MIX1 INP1", "IIR2", "IIR2"पूर्ण,

	अणु"RX2 MIX1 INP3", "RX1", "I2S RX1"पूर्ण,
	अणु"RX2 MIX1 INP3", "RX2", "I2S RX2"पूर्ण,
	अणु"RX2 MIX1 INP3", "RX3", "I2S RX3"पूर्ण,

	/* RX3 PATH */
	अणु"PDM_RX3", शून्य, "RX3 INT"पूर्ण,
	अणु"RX3 INT", शून्य, "RX3 MIX1"पूर्ण,

	अणु"RX3 MIX1", शून्य, "RX3 MIX1 INP1"पूर्ण,
	अणु"RX3 MIX1", शून्य, "RX3 MIX1 INP2"पूर्ण,
	अणु"RX3 MIX1", शून्य, "RX3 MIX1 INP3"पूर्ण,

	अणु"RX3 MIX1 INP1", "RX1", "I2S RX1"पूर्ण,
	अणु"RX3 MIX1 INP1", "RX2", "I2S RX2"पूर्ण,
	अणु"RX3 MIX1 INP1", "RX3", "I2S RX3"पूर्ण,
	अणु"RX3 MIX1 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX3 MIX1 INP1", "IIR2", "IIR2"पूर्ण,

	अणु"RX3 MIX1 INP2", "RX1", "I2S RX1"पूर्ण,
	अणु"RX3 MIX1 INP2", "RX2", "I2S RX2"पूर्ण,
	अणु"RX3 MIX1 INP2", "RX3", "I2S RX3"पूर्ण,
	अणु"RX3 MIX1 INP2", "IIR1", "IIR1"पूर्ण,
	अणु"RX3 MIX1 INP2", "IIR2", "IIR2"पूर्ण,

	अणु"RX1 MIX2 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX2 MIX2 INP1", "IIR1", "IIR1"पूर्ण,
	अणु"RX1 MIX2 INP1", "IIR2", "IIR2"पूर्ण,
	अणु"RX2 MIX2 INP1", "IIR2", "IIR2"पूर्ण,

	अणु"IIR1", शून्य, "IIR1 INP1 MUX"पूर्ण,
	अणु"IIR1 INP1 MUX", "DEC1", "DEC1 MUX"पूर्ण,
	अणु"IIR1 INP1 MUX", "DEC2", "DEC2 MUX"पूर्ण,

	अणु"IIR2", शून्य, "IIR2 INP1 MUX"पूर्ण,
	अणु"IIR2 INP1 MUX", "DEC1", "DEC1 MUX"पूर्ण,
	अणु"IIR2 INP1 MUX", "DEC2", "DEC2 MUX"पूर्ण,

	अणु"RX3 MIX1 INP3", "RX1", "I2S RX1"पूर्ण,
	अणु"RX3 MIX1 INP3", "RX2", "I2S RX2"पूर्ण,
	अणु"RX3 MIX1 INP3", "RX3", "I2S RX3"पूर्ण,

पूर्ण;

अटल पूर्णांक msm8916_wcd_digital_startup(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा msm8916_wcd_digital_priv *msm8916_wcd;
	अचिन्हित दीर्घ mclk_rate;

	msm8916_wcd = snd_soc_component_get_drvdata(component);
	snd_soc_component_update_bits(component, LPASS_CDC_CLK_MCLK_CTL,
			    MCLK_CTL_MCLK_EN_MASK,
			    MCLK_CTL_MCLK_EN_ENABLE);
	snd_soc_component_update_bits(component, LPASS_CDC_CLK_PDM_CTL,
			    LPASS_CDC_CLK_PDM_CTL_PDM_CLK_SEL_MASK,
			    LPASS_CDC_CLK_PDM_CTL_PDM_CLK_SEL_FB);

	mclk_rate = clk_get_rate(msm8916_wcd->mclk);
	चयन (mclk_rate) अणु
	हाल 12288000:
		snd_soc_component_update_bits(component, LPASS_CDC_TOP_CTL,
				    TOP_CTL_DIG_MCLK_FREQ_MASK,
				    TOP_CTL_DIG_MCLK_FREQ_F_12_288MHZ);
		अवरोध;
	हाल 9600000:
		snd_soc_component_update_bits(component, LPASS_CDC_TOP_CTL,
				    TOP_CTL_DIG_MCLK_FREQ_MASK,
				    TOP_CTL_DIG_MCLK_FREQ_F_9_6MHZ);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid mclk rate %ld\n", mclk_rate);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम msm8916_wcd_digital_shutकरोwn(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_soc_dai *dai)
अणु
	snd_soc_component_update_bits(dai->component, LPASS_CDC_CLK_PDM_CTL,
			    LPASS_CDC_CLK_PDM_CTL_PDM_CLK_SEL_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops msm8916_wcd_digital_dai_ops = अणु
	.startup = msm8916_wcd_digital_startup,
	.shutकरोwn = msm8916_wcd_digital_shutकरोwn,
	.hw_params = msm8916_wcd_digital_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver msm8916_wcd_digital_dai[] = अणु
	[0] = अणु
	       .name = "msm8916_wcd_digital_i2s_rx1",
	       .id = 0,
	       .playback = अणु
			    .stream_name = "AIF1 Playback",
			    .rates = MSM8916_WCD_DIGITAL_RATES,
			    .क्रमmats = MSM8916_WCD_DIGITAL_FORMATS,
			    .channels_min = 1,
			    .channels_max = 3,
			    पूर्ण,
	       .ops = &msm8916_wcd_digital_dai_ops,
	       पूर्ण,
	[1] = अणु
	       .name = "msm8916_wcd_digital_i2s_tx1",
	       .id = 1,
	       .capture = अणु
			   .stream_name = "AIF1 Capture",
			   .rates = MSM8916_WCD_DIGITAL_RATES,
			   .क्रमmats = MSM8916_WCD_DIGITAL_FORMATS,
			   .channels_min = 1,
			   .channels_max = 4,
			   पूर्ण,
	       .ops = &msm8916_wcd_digital_dai_ops,
	       पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver msm8916_wcd_digital = अणु
	.probe			= msm8916_wcd_digital_component_probe,
	.set_sysclk		= msm8916_wcd_digital_component_set_sysclk,
	.controls		= msm8916_wcd_digital_snd_controls,
	.num_controls		= ARRAY_SIZE(msm8916_wcd_digital_snd_controls),
	.dapm_widमाला_लो		= msm8916_wcd_digital_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(msm8916_wcd_digital_dapm_widमाला_लो),
	.dapm_routes		= msm8916_wcd_digital_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(msm8916_wcd_digital_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config msm8916_codec_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = LPASS_CDC_TX2_DMIC_CTL,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक msm8916_wcd_digital_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm8916_wcd_digital_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	काष्ठा regmap *digital_map;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	digital_map =
	    devm_regmap_init_mmio(&pdev->dev, base,
				  &msm8916_codec_regmap_config);
	अगर (IS_ERR(digital_map))
		वापस PTR_ERR(digital_map);

	ret = msm8916_wcd_digital_get_clks(pdev, priv);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(priv->ahbclk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable ahbclk %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->mclk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable mclk %d\n", ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, priv);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &msm8916_wcd_digital,
				      msm8916_wcd_digital_dai,
				      ARRAY_SIZE(msm8916_wcd_digital_dai));
पूर्ण

अटल पूर्णांक msm8916_wcd_digital_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm8916_wcd_digital_priv *priv = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(priv->mclk);
	clk_disable_unprepare(priv->ahbclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm8916_wcd_digital_match_table[] = अणु
	अणु .compatible = "qcom,msm8916-wcd-digital-codec" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, msm8916_wcd_digital_match_table);

अटल काष्ठा platक्रमm_driver msm8916_wcd_digital_driver = अणु
	.driver = अणु
		   .name = "msm8916-wcd-digital-codec",
		   .of_match_table = msm8916_wcd_digital_match_table,
	पूर्ण,
	.probe = msm8916_wcd_digital_probe,
	.हटाओ = msm8916_wcd_digital_हटाओ,
पूर्ण;

module_platक्रमm_driver(msm8916_wcd_digital_driver);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org>");
MODULE_DESCRIPTION("MSM8916 WCD Digital Codec driver");
MODULE_LICENSE("GPL v2");
