<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019, Linaro Limited

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/wcd934x/रेजिस्टरs.h>
#समावेश <linux/mfd/wcd934x/wcd934x.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/slimbus.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश "wcd-clsh-v2.h"

#घोषणा WCD934X_RATES_MASK (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			    SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |\
			    SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)
/* Fractional Rates */
#घोषणा WCD934X_FRAC_RATES_MASK (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_88200 |\
				 SNDRV_PCM_RATE_176400)
#घोषणा WCD934X_FORMATS_S16_S24_LE (SNDRV_PCM_FMTBIT_S16_LE | \
				    SNDRV_PCM_FMTBIT_S24_LE)

/* slave port water mark level
 *   (0: 6bytes, 1: 9bytes, 2: 12 bytes, 3: 15 bytes)
 */
#घोषणा SLAVE_PORT_WATER_MARK_6BYTES	0
#घोषणा SLAVE_PORT_WATER_MARK_9BYTES	1
#घोषणा SLAVE_PORT_WATER_MARK_12BYTES	2
#घोषणा SLAVE_PORT_WATER_MARK_15BYTES	3
#घोषणा SLAVE_PORT_WATER_MARK_SHIFT	1
#घोषणा SLAVE_PORT_ENABLE		1
#घोषणा SLAVE_PORT_DISABLE		0
#घोषणा WCD934X_SLIM_WATER_MARK_VAL \
	((SLAVE_PORT_WATER_MARK_12BYTES << SLAVE_PORT_WATER_MARK_SHIFT) | \
	 (SLAVE_PORT_ENABLE))

#घोषणा WCD934X_SLIM_NUM_PORT_REG	3
#घोषणा WCD934X_SLIM_PGD_PORT_INT_TX_EN0 (WCD934X_SLIM_PGD_PORT_INT_EN0 + 2)
#घोषणा WCD934X_SLIM_IRQ_OVERFLOW	BIT(0)
#घोषणा WCD934X_SLIM_IRQ_UNDERFLOW	BIT(1)
#घोषणा WCD934X_SLIM_IRQ_PORT_CLOSED	BIT(2)

#घोषणा WCD934X_MCLK_CLK_12P288MHZ	12288000
#घोषणा WCD934X_MCLK_CLK_9P6MHZ		9600000

/* Only valid क्रम 9.6 MHz mclk */
#घोषणा WCD9XXX_DMIC_SAMPLE_RATE_2P4MHZ 2400000
#घोषणा WCD9XXX_DMIC_SAMPLE_RATE_4P8MHZ 4800000

/* Only valid क्रम 12.288 MHz mclk */
#घोषणा WCD9XXX_DMIC_SAMPLE_RATE_4P096MHZ 4096000

#घोषणा WCD934X_DMIC_CLK_DIV_2		0x0
#घोषणा WCD934X_DMIC_CLK_DIV_3		0x1
#घोषणा WCD934X_DMIC_CLK_DIV_4		0x2
#घोषणा WCD934X_DMIC_CLK_DIV_6		0x3
#घोषणा WCD934X_DMIC_CLK_DIV_8		0x4
#घोषणा WCD934X_DMIC_CLK_DIV_16		0x5
#घोषणा WCD934X_DMIC_CLK_DRIVE_DEFAULT 0x02

#घोषणा TX_HPF_CUT_OFF_FREQ_MASK	0x60
#घोषणा CF_MIN_3DB_4HZ			0x0
#घोषणा CF_MIN_3DB_75HZ			0x1
#घोषणा CF_MIN_3DB_150HZ		0x2

#घोषणा WCD934X_RX_START		16
#घोषणा WCD934X_NUM_INTERPOLATORS	9
#घोषणा WCD934X_RX_PATH_CTL_OFFSET	20
#घोषणा WCD934X_MAX_VALID_ADC_MUX	13
#घोषणा WCD934X_INVALID_ADC_MUX		9

#घोषणा WCD934X_SLIM_RX_CH(p) \
	अणु.port = p + WCD934X_RX_START, .shअगरt = p,पूर्ण

#घोषणा WCD934X_SLIM_TX_CH(p) \
	अणु.port = p, .shअगरt = p,पूर्ण

/* Feature masks to distinguish codec version */
#घोषणा DSD_DISABLED_MASK   0
#घोषणा SLNQ_DISABLED_MASK  1

#घोषणा DSD_DISABLED   BIT(DSD_DISABLED_MASK)
#घोषणा SLNQ_DISABLED  BIT(SLNQ_DISABLED_MASK)

/* As fine version info cannot be retrieved beक्रमe wcd probe.
 * Define three coarse versions क्रम possible future use beक्रमe wcd probe.
 */
#घोषणा WCD_VERSION_WCD9340_1_0     0x400
#घोषणा WCD_VERSION_WCD9341_1_0     0x410
#घोषणा WCD_VERSION_WCD9340_1_1     0x401
#घोषणा WCD_VERSION_WCD9341_1_1     0x411
#घोषणा WCD934X_AMIC_PWR_LEVEL_LP	0
#घोषणा WCD934X_AMIC_PWR_LEVEL_DEFAULT	1
#घोषणा WCD934X_AMIC_PWR_LEVEL_HP	2
#घोषणा WCD934X_AMIC_PWR_LEVEL_HYBRID	3
#घोषणा WCD934X_AMIC_PWR_LVL_MASK	0x60
#घोषणा WCD934X_AMIC_PWR_LVL_SHIFT	0x5

#घोषणा WCD934X_DEC_PWR_LVL_MASK	0x06
#घोषणा WCD934X_DEC_PWR_LVL_LP		0x02
#घोषणा WCD934X_DEC_PWR_LVL_HP		0x04
#घोषणा WCD934X_DEC_PWR_LVL_DF		0x00
#घोषणा WCD934X_DEC_PWR_LVL_HYBRID WCD934X_DEC_PWR_LVL_DF

#घोषणा WCD934X_DEF_MICBIAS_MV	1800
#घोषणा WCD934X_MAX_MICBIAS_MV	2850

#घोषणा WCD_IIR_FILTER_SIZE	(माप(u32) * BAND_MAX)

#घोषणा WCD_IIR_FILTER_CTL(xname, iidx, bidx) \
अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = wcd934x_iir_filter_info, \
	.get = wcd934x_get_iir_band_audio_mixer, \
	.put = wcd934x_put_iir_band_audio_mixer, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा wcd_iir_filter_ctl) अणु \
		.iir_idx = iidx, \
		.band_idx = bidx, \
		.bytes_ext = अणु.max = WCD_IIR_FILTER_SIZE, पूर्ण, \
	पूर्ण \
पूर्ण

#घोषणा WCD934X_INTERPOLATOR_PATH(id)			\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "IIR0", "IIR0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP0", "IIR1", "IIR1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "IIR0", "IIR0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP1", "IIR1", "IIR1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_1 MIX1 INP2", "IIR0", "IIR0"पूर्ण,		\
	अणु"RX INT" #id "_1 MIX1 INP2", "IIR1", "IIR1"पूर्ण,		\
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP0"पूर्ण, \
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP1"पूर्ण, \
	अणु"RX INT" #id "_1 MIX1", शून्य, "RX INT" #id "_1 MIX1 INP2"पूर्ण, \
	अणु"RX INT" #id "_2 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"RX INT" #id "_2 MUX", शून्य, "INT" #id "_CLK"पूर्ण, \
	अणु"RX INT" #id "_2 MUX", शून्य, "DSMDEM" #id "_CLK"पूर्ण, \
	अणु"RX INT" #id "_2 INTERP", शून्य, "RX INT" #id "_2 MUX"पूर्ण,	\
	अणु"RX INT" #id " SEC MIX", शून्य, "RX INT" #id "_2 INTERP"पूर्ण,	\
	अणु"RX INT" #id "_1 INTERP", शून्य, "RX INT" #id "_1 MIX1"पूर्ण,	\
	अणु"RX INT" #id "_1 INTERP", शून्य, "INT" #id "_CLK"पूर्ण,	\
	अणु"RX INT" #id "_1 INTERP", शून्य, "DSMDEM" #id "_CLK"पूर्ण,	\
	अणु"RX INT" #id " SEC MIX", शून्य, "RX INT" #id "_1 INTERP"पूर्ण

#घोषणा WCD934X_INTERPOLATOR_MIX2(id)			\
	अणु"RX INT" #id " MIX2", शून्य, "RX INT" #id " SEC MIX"पूर्ण, \
	अणु"RX INT" #id " MIX2", शून्य, "RX INT" #id " MIX2 INP"पूर्ण

#घोषणा WCD934X_SLIM_RX_AIF_PATH(id)	\
	अणु"SLIM RX"#id" MUX", "AIF1_PB", "AIF1 PB"पूर्ण,	\
	अणु"SLIM RX"#id" MUX", "AIF2_PB", "AIF2 PB"पूर्ण,	\
	अणु"SLIM RX"#id" MUX", "AIF3_PB", "AIF3 PB"पूर्ण,	\
	अणु"SLIM RX"#id" MUX", "AIF4_PB", "AIF4 PB"पूर्ण,   \
	अणु"SLIM RX"#id, शून्य, "SLIM RX"#id" MUX"पूर्ण

#घोषणा WCD934X_ADC_MUX(id) \
	अणु"ADC MUX" #id, "DMIC", "DMIC MUX" #id पूर्ण,	\
	अणु"ADC MUX" #id, "AMIC", "AMIC MUX" #id पूर्ण,	\
	अणु"DMIC MUX" #id, "DMIC0", "DMIC0"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC1", "DMIC1"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC2", "DMIC2"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC3", "DMIC3"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC4", "DMIC4"पूर्ण,		\
	अणु"DMIC MUX" #id, "DMIC5", "DMIC5"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC1", "ADC1"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC2", "ADC2"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC3", "ADC3"पूर्ण,		\
	अणु"AMIC MUX" #id, "ADC4", "ADC4"पूर्ण

#घोषणा WCD934X_IIR_INP_MUX(id) \
	अणु"IIR" #id, शून्य, "IIR" #id " INP0 MUX"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC0", "ADC MUX0"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC1", "ADC MUX1"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC2", "ADC MUX2"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC3", "ADC MUX3"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC4", "ADC MUX4"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC5", "ADC MUX5"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC6", "ADC MUX6"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC7", "ADC MUX7"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "DEC8", "ADC MUX8"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"IIR" #id " INP0 MUX", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"IIR" #id, शून्य, "IIR" #id " INP1 MUX"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC0", "ADC MUX0"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC1", "ADC MUX1"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC2", "ADC MUX2"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC3", "ADC MUX3"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC4", "ADC MUX4"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC5", "ADC MUX5"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC6", "ADC MUX6"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC7", "ADC MUX7"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "DEC8", "ADC MUX8"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"IIR" #id " INP1 MUX", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"IIR" #id, शून्य, "IIR" #id " INP2 MUX"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC0", "ADC MUX0"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC1", "ADC MUX1"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC2", "ADC MUX2"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC3", "ADC MUX3"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC4", "ADC MUX4"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC5", "ADC MUX5"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC6", "ADC MUX6"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC7", "ADC MUX7"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "DEC8", "ADC MUX8"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"IIR" #id " INP2 MUX", "RX7", "SLIM RX7"पूर्ण,	\
	अणु"IIR" #id, शून्य, "IIR" #id " INP3 MUX"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC0", "ADC MUX0"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC1", "ADC MUX1"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC2", "ADC MUX2"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC3", "ADC MUX3"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC4", "ADC MUX4"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC5", "ADC MUX5"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC6", "ADC MUX6"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC7", "ADC MUX7"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "DEC8", "ADC MUX8"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX0", "SLIM RX0"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX1", "SLIM RX1"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX2", "SLIM RX2"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX3", "SLIM RX3"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX4", "SLIM RX4"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX5", "SLIM RX5"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX6", "SLIM RX6"पूर्ण,	\
	अणु"IIR" #id " INP3 MUX", "RX7", "SLIM RX7"पूर्ण

#घोषणा WCD934X_SLIM_TX_AIF_PATH(id)	\
	अणु"AIF1_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id पूर्ण,	\
	अणु"AIF2_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id पूर्ण,	\
	अणु"AIF3_CAP Mixer", "SLIM TX" #id, "SLIM TX" #id पूर्ण,	\
	अणु"SLIM TX" #id, शून्य, "CDC_IF TX" #id " MUX"पूर्ण

क्रमागत अणु
	MIC_BIAS_1 = 1,
	MIC_BIAS_2,
	MIC_BIAS_3,
	MIC_BIAS_4
पूर्ण;

क्रमागत अणु
	SIDO_SOURCE_INTERNAL,
	SIDO_SOURCE_RCO_BG,
पूर्ण;

क्रमागत अणु
	INTERP_EAR = 0,
	INTERP_HPHL,
	INTERP_HPHR,
	INTERP_LO1,
	INTERP_LO2,
	INTERP_LO3_NA, /* LO3 not avalible in Tavil */
	INTERP_LO4_NA,
	INTERP_SPKR1, /*INT7 WSA Speakers via soundwire */
	INTERP_SPKR2, /*INT8 WSA Speakers via soundwire */
	INTERP_MAX,
पूर्ण;

क्रमागत अणु
	WCD934X_RX0 = 0,
	WCD934X_RX1,
	WCD934X_RX2,
	WCD934X_RX3,
	WCD934X_RX4,
	WCD934X_RX5,
	WCD934X_RX6,
	WCD934X_RX7,
	WCD934X_RX8,
	WCD934X_RX9,
	WCD934X_RX10,
	WCD934X_RX11,
	WCD934X_RX12,
	WCD934X_RX_MAX,
पूर्ण;

क्रमागत अणु
	WCD934X_TX0 = 0,
	WCD934X_TX1,
	WCD934X_TX2,
	WCD934X_TX3,
	WCD934X_TX4,
	WCD934X_TX5,
	WCD934X_TX6,
	WCD934X_TX7,
	WCD934X_TX8,
	WCD934X_TX9,
	WCD934X_TX10,
	WCD934X_TX11,
	WCD934X_TX12,
	WCD934X_TX13,
	WCD934X_TX14,
	WCD934X_TX15,
	WCD934X_TX_MAX,
पूर्ण;

काष्ठा wcd934x_slim_ch अणु
	u32 ch_num;
	u16 port;
	u16 shअगरt;
	काष्ठा list_head list;
पूर्ण;

अटल स्थिर काष्ठा wcd934x_slim_ch wcd934x_tx_chs[WCD934X_TX_MAX] = अणु
	WCD934X_SLIM_TX_CH(0),
	WCD934X_SLIM_TX_CH(1),
	WCD934X_SLIM_TX_CH(2),
	WCD934X_SLIM_TX_CH(3),
	WCD934X_SLIM_TX_CH(4),
	WCD934X_SLIM_TX_CH(5),
	WCD934X_SLIM_TX_CH(6),
	WCD934X_SLIM_TX_CH(7),
	WCD934X_SLIM_TX_CH(8),
	WCD934X_SLIM_TX_CH(9),
	WCD934X_SLIM_TX_CH(10),
	WCD934X_SLIM_TX_CH(11),
	WCD934X_SLIM_TX_CH(12),
	WCD934X_SLIM_TX_CH(13),
	WCD934X_SLIM_TX_CH(14),
	WCD934X_SLIM_TX_CH(15),
पूर्ण;

अटल स्थिर काष्ठा wcd934x_slim_ch wcd934x_rx_chs[WCD934X_RX_MAX] = अणु
	WCD934X_SLIM_RX_CH(0),	 /* 16 */
	WCD934X_SLIM_RX_CH(1),	 /* 17 */
	WCD934X_SLIM_RX_CH(2),
	WCD934X_SLIM_RX_CH(3),
	WCD934X_SLIM_RX_CH(4),
	WCD934X_SLIM_RX_CH(5),
	WCD934X_SLIM_RX_CH(6),
	WCD934X_SLIM_RX_CH(7),
	WCD934X_SLIM_RX_CH(8),
	WCD934X_SLIM_RX_CH(9),
	WCD934X_SLIM_RX_CH(10),
	WCD934X_SLIM_RX_CH(11),
	WCD934X_SLIM_RX_CH(12),
पूर्ण;

/* Codec supports 2 IIR filters */
क्रमागत अणु
	IIR0 = 0,
	IIR1,
	IIR_MAX,
पूर्ण;

/* Each IIR has 5 Filter Stages */
क्रमागत अणु
	BAND1 = 0,
	BAND2,
	BAND3,
	BAND4,
	BAND5,
	BAND_MAX,
पूर्ण;

क्रमागत अणु
	COMPANDER_1, /* HPH_L */
	COMPANDER_2, /* HPH_R */
	COMPANDER_3, /* LO1_DIFF */
	COMPANDER_4, /* LO2_DIFF */
	COMPANDER_5, /* LO3_SE - not used in Tavil */
	COMPANDER_6, /* LO4_SE - not used in Tavil */
	COMPANDER_7, /* SWR SPK CH1 */
	COMPANDER_8, /* SWR SPK CH2 */
	COMPANDER_MAX,
पूर्ण;

क्रमागत अणु
	AIF1_PB = 0,
	AIF1_CAP,
	AIF2_PB,
	AIF2_CAP,
	AIF3_PB,
	AIF3_CAP,
	AIF4_PB,
	AIF4_VIFEED,
	AIF4_MAD_TX,
	NUM_CODEC_DAIS,
पूर्ण;

क्रमागत अणु
	INTn_1_INP_SEL_ZERO = 0,
	INTn_1_INP_SEL_DEC0,
	INTn_1_INP_SEL_DEC1,
	INTn_1_INP_SEL_IIR0,
	INTn_1_INP_SEL_IIR1,
	INTn_1_INP_SEL_RX0,
	INTn_1_INP_SEL_RX1,
	INTn_1_INP_SEL_RX2,
	INTn_1_INP_SEL_RX3,
	INTn_1_INP_SEL_RX4,
	INTn_1_INP_SEL_RX5,
	INTn_1_INP_SEL_RX6,
	INTn_1_INP_SEL_RX7,
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
	INTERP_MAIN_PATH,
	INTERP_MIX_PATH,
पूर्ण;

काष्ठा पूर्णांकerp_sample_rate अणु
	पूर्णांक sample_rate;
	पूर्णांक rate_val;
पूर्ण;

अटल काष्ठा पूर्णांकerp_sample_rate sr_val_tbl[] = अणु
	अणु8000, 0x0पूर्ण,
	अणु16000, 0x1पूर्ण,
	अणु32000, 0x3पूर्ण,
	अणु48000, 0x4पूर्ण,
	अणु96000, 0x5पूर्ण,
	अणु192000, 0x6पूर्ण,
	अणु384000, 0x7पूर्ण,
	अणु44100, 0x9पूर्ण,
	अणु88200, 0xAपूर्ण,
	अणु176400, 0xBपूर्ण,
	अणु352800, 0xCपूर्ण,
पूर्ण;

काष्ठा wcd_slim_codec_dai_data अणु
	काष्ठा list_head slim_ch_list;
	काष्ठा slim_stream_config sconfig;
	काष्ठा slim_stream_runसमय *srunसमय;
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg wcd934x_अगरc_ranges[] = अणु
	अणु
		.name = "WCD9335-IFC-DEV",
		.range_min =  0x0,
		.range_max = 0xffff,
		.selector_reg = 0x800,
		.selector_mask = 0xfff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0x800,
		.winकरोw_len = 0x400,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config wcd934x_अगरc_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = 0xffff,
	.ranges = wcd934x_अगरc_ranges,
	.num_ranges = ARRAY_SIZE(wcd934x_अगरc_ranges),
पूर्ण;

काष्ठा wcd934x_codec अणु
	काष्ठा device *dev;
	काष्ठा clk_hw hw;
	काष्ठा clk *extclk;
	काष्ठा regmap *regmap;
	काष्ठा regmap *अगर_regmap;
	काष्ठा slim_device *sdev;
	काष्ठा slim_device *sidev;
	काष्ठा wcd_clsh_ctrl *clsh_ctrl;
	काष्ठा snd_soc_component *component;
	काष्ठा wcd934x_slim_ch rx_chs[WCD934X_RX_MAX];
	काष्ठा wcd934x_slim_ch tx_chs[WCD934X_TX_MAX];
	काष्ठा wcd_slim_codec_dai_data dai[NUM_CODEC_DAIS];
	पूर्णांक rate;
	u32 version;
	u32 hph_mode;
	पूर्णांक num_rx_port;
	पूर्णांक num_tx_port;
	u32 tx_port_value[WCD934X_TX_MAX];
	u32 rx_port_value[WCD934X_RX_MAX];
	पूर्णांक siकरो_input_src;
	पूर्णांक dmic_0_1_clk_cnt;
	पूर्णांक dmic_2_3_clk_cnt;
	पूर्णांक dmic_4_5_clk_cnt;
	पूर्णांक dmic_sample_rate;
	पूर्णांक comp_enabled[COMPANDER_MAX];
	पूर्णांक sysclk_users;
	काष्ठा mutex sysclk_mutex;
पूर्ण;

#घोषणा to_wcd934x_codec(_hw) container_of(_hw, काष्ठा wcd934x_codec, hw)

काष्ठा wcd_iir_filter_ctl अणु
	अचिन्हित पूर्णांक iir_idx;
	अचिन्हित पूर्णांक band_idx;
	काष्ठा soc_bytes_ext bytes_ext;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_gain, -8400, 100, -8400);
अटल स्थिर DECLARE_TLV_DB_SCALE(line_gain, 0, 7, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(analog_gain, 0, 25, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(ear_pa_gain, 0, 150, 0);

/* Cutoff frequency क्रम high pass filter */
अटल स्थिर अक्षर * स्थिर cf_text[] = अणु
	"CF_NEG_3DB_4HZ", "CF_NEG_3DB_75HZ", "CF_NEG_3DB_150HZ"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_cf_text[] = अणु
	"CF_NEG_3DB_4HZ", "CF_NEG_3DB_75HZ", "CF_NEG_3DB_150HZ",
	"CF_NEG_3DB_0P48HZ"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_hph_mode_mux_text[] = अणु
	"Class H Invalid", "Class-H Hi-Fi", "Class-H Low Power", "Class-AB",
	"Class-H Hi-Fi Low Power"
पूर्ण;

अटल स्थिर अक्षर *स्थिर slim_rx_mux_text[] = अणु
	"ZERO", "AIF1_PB", "AIF2_PB", "AIF3_PB", "AIF4_PB",
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

अटल स्थिर अक्षर * स्थिर rx_sidetone_mix_text[] = अणु
	"ZERO", "SRC0", "SRC1", "SRC_SUM"
पूर्ण;

अटल स्थिर अक्षर * स्थिर iir_inp_mux_text[] = अणु
	"ZERO", "DEC0", "DEC1", "DEC2", "DEC3", "DEC4", "DEC5", "DEC6",
	"DEC7", "DEC8", "RX0", "RX1", "RX2", "RX3", "RX4", "RX5", "RX6", "RX7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक_dem_inp_mux_text[] = अणु
	"NORMAL_DSM_OUT", "CLSH_DSM_OUT",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक0_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT0_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक1_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT1_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक2_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT2_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक3_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT3_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक4_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT4_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक7_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT7_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक8_1_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT8_1 MIX1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक0_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT0_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक1_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT1_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक2_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT2_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक3_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT3_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक4_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT4_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक7_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT7_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx_पूर्णांक8_2_पूर्णांकerp_mux_text[] = अणु
	"ZERO", "RX INT8_2 MUX",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic_mux_text[] = अणु
	"ZERO", "DMIC0", "DMIC1", "DMIC2", "DMIC3", "DMIC4", "DMIC5"
पूर्ण;

अटल स्थिर अक्षर * स्थिर amic_mux_text[] = अणु
	"ZERO", "ADC1", "ADC2", "ADC3", "ADC4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर amic4_5_sel_text[] = अणु
	"AMIC4", "AMIC5"
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_mux_text[] = अणु
	"DMIC", "AMIC", "ANC_FB_TUNE1", "ANC_FB_TUNE2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx0_mux_text[] = अणु
	"ZERO", "RX_MIX_TX0", "DEC0", "DEC0_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx1_mux_text[] = अणु
	"ZERO", "RX_MIX_TX1", "DEC1", "DEC1_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx2_mux_text[] = अणु
	"ZERO", "RX_MIX_TX2", "DEC2", "DEC2_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx3_mux_text[] = अणु
	"ZERO", "RX_MIX_TX3", "DEC3", "DEC3_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx4_mux_text[] = अणु
	"ZERO", "RX_MIX_TX4", "DEC4", "DEC4_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx5_mux_text[] = अणु
	"ZERO", "RX_MIX_TX5", "DEC5", "DEC5_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx6_mux_text[] = अणु
	"ZERO", "RX_MIX_TX6", "DEC6", "DEC6_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx7_mux_text[] = अणु
	"ZERO", "RX_MIX_TX7", "DEC7", "DEC7_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx8_mux_text[] = अणु
	"ZERO", "RX_MIX_TX8", "DEC8", "DEC8_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx9_mux_text[] = अणु
	"ZERO", "DEC7", "DEC7_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx10_mux_text[] = अणु
	"ZERO", "DEC6", "DEC6_192"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx11_mux_text[] = अणु
	"DEC_0_5", "DEC_9_12", "MAD_AUDIO", "MAD_BRDCST"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx11_inp1_mux_text[] = अणु
	"ZERO", "DEC0", "DEC1", "DEC2", "DEC3", "DEC4",
	"DEC5", "RX_MIX_TX5", "DEC9_10", "DEC11_12"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx13_mux_text[] = अणु
	"CDC_DEC_5", "MAD_BRDCST"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_अगर_tx13_inp1_mux_text[] = अणु
	"ZERO", "DEC5", "DEC5_192"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत cf_dec0_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX0_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX1_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec2_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX2_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec3_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX3_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec4_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX4_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec5_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX5_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec6_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX6_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec7_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX7_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_dec8_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX8_TX_PATH_CFG0, 5, 3, cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक0_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX0_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक0_2_क्रमागत, WCD934X_CDC_RX0_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक1_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX1_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक1_2_क्रमागत, WCD934X_CDC_RX1_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक2_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX2_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक2_2_क्रमागत, WCD934X_CDC_RX2_RX_PATH_MIX_CFG, 2,
		     rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक3_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX3_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक3_2_क्रमागत, WCD934X_CDC_RX3_RX_PATH_MIX_CFG, 2,
			    rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक4_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX4_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक4_2_क्रमागत, WCD934X_CDC_RX4_RX_PATH_MIX_CFG, 2,
			    rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक7_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX7_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक7_2_क्रमागत, WCD934X_CDC_RX7_RX_PATH_MIX_CFG, 2,
			    rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत cf_पूर्णांक8_1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX8_RX_PATH_CFG2, 0, 4, rx_cf_text);

अटल SOC_ENUM_SINGLE_DECL(cf_पूर्णांक8_2_क्रमागत, WCD934X_CDC_RX8_RX_PATH_MIX_CFG, 2,
			    rx_cf_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_hph_mode_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(rx_hph_mode_mux_text),
			    rx_hph_mode_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत slim_rx_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(slim_rx_mux_text), slim_rx_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT0_CFG1, 0, 10,
			rx_पूर्णांक0_7_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT1_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT2_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT3_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT4_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT7_CFG1, 0, 10,
			rx_पूर्णांक0_7_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_2_mux_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT8_CFG1, 0, 9,
			rx_पूर्णांक_mix_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT0_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT0_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT0_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT1_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT1_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT1_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT2_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT2_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT2_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT3_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT3_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT3_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT4_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT4_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT4_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT7_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT7_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT7_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp0_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT8_CFG0, 0, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp1_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT8_CFG0, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_mix_inp2_chain_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_RX_INT8_CFG1, 4, 13,
			rx_prim_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG0, 0, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG0, 2, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG0, 4, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG0, 6, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG1, 0, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_mix2_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX_INP_MUX_SIDETONE_SRC_CFG1, 2, 4,
			rx_sidetone_mix_text);

अटल स्थिर काष्ठा soc_क्रमागत iir0_inp0_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR0_MIX_CFG0,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir0_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR0_MIX_CFG1,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir0_inp2_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR0_MIX_CFG2,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir0_inp3_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR0_MIX_CFG3,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir1_inp0_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR1_MIX_CFG0,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir1_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR1_MIX_CFG1,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir1_inp2_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR1_MIX_CFG2,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत iir1_inp3_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_SIDETONE_IIR_INP_MUX_IIR1_MIX_CFG3,
			0, 18, iir_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX0_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX1_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_dem_inp_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_RX2_RX_PATH_SEC0, 0,
			ARRAY_SIZE(rx_पूर्णांक_dem_inp_mux_text),
			rx_पूर्णांक_dem_inp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux0_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1, 0,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG1, 0,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux2_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX2_CFG1, 0,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux3_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1, 0,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux4_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1, 2,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux5_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG1, 2,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux6_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX2_CFG1, 2,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux7_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1, 2,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_adc_mux8_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG1, 4,
			ARRAY_SIZE(adc_mux_text), adc_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2,
			rx_पूर्णांक0_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2,
			rx_पूर्णांक1_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2,
			rx_पूर्णांक2_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक3_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक4_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक7_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_1_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक8_1_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक0_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक0_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक1_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक1_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक2_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक2_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक3_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक3_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक4_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक4_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक7_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक7_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत rx_पूर्णांक8_2_पूर्णांकerp_mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM,	0, 2, rx_पूर्णांक8_2_पूर्णांकerp_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux0_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux2_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX2_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux3_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux4_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux5_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX5_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux6_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX6_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux7_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX7_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_dmic_mux8_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX8_CFG0, 3, 7,
			dmic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux0_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux1_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux2_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX2_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux3_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux4_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux5_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX5_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux6_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX6_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux7_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX7_CFG0, 0, 5,
			amic_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत tx_amic_mux8_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_TX_INP_MUX_ADC_MUX8_CFG0, 0, 5,
			amic_mux_text);

अटल स्थिर काष्ठा soc_क्रमागत tx_amic4_5_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_TX_NEW_AMIC_4_5_SEL, 7, 2, amic4_5_sel_text);

अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx0_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG0, 0,
			ARRAY_SIZE(cdc_अगर_tx0_mux_text), cdc_अगर_tx0_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG0, 2,
			ARRAY_SIZE(cdc_अगर_tx1_mux_text), cdc_अगर_tx1_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx2_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG0, 4,
			ARRAY_SIZE(cdc_अगर_tx2_mux_text), cdc_अगर_tx2_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx3_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG0, 6,
			ARRAY_SIZE(cdc_अगर_tx3_mux_text), cdc_अगर_tx3_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx4_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG1, 0,
			ARRAY_SIZE(cdc_अगर_tx4_mux_text), cdc_अगर_tx4_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx5_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG1, 2,
			ARRAY_SIZE(cdc_अगर_tx5_mux_text), cdc_अगर_tx5_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx6_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG1, 4,
			ARRAY_SIZE(cdc_अगर_tx6_mux_text), cdc_अगर_tx6_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx7_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG1, 6,
			ARRAY_SIZE(cdc_अगर_tx7_mux_text), cdc_अगर_tx7_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx8_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG2, 0,
			ARRAY_SIZE(cdc_अगर_tx8_mux_text), cdc_अगर_tx8_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx9_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG2, 2,
			ARRAY_SIZE(cdc_अगर_tx9_mux_text), cdc_अगर_tx9_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx10_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG2, 4,
			ARRAY_SIZE(cdc_अगर_tx10_mux_text), cdc_अगर_tx10_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx11_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG3, 0,
			ARRAY_SIZE(cdc_अगर_tx11_inp1_mux_text),
			cdc_अगर_tx11_inp1_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx11_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_DATA_HUB_SB_TX11_INP_CFG, 0,
			ARRAY_SIZE(cdc_अगर_tx11_mux_text), cdc_अगर_tx11_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx13_inp1_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_CDC_IF_ROUTER_TX_MUX_CFG3, 4,
			ARRAY_SIZE(cdc_अगर_tx13_inp1_mux_text),
			cdc_अगर_tx13_inp1_mux_text);
अटल स्थिर काष्ठा soc_क्रमागत cdc_अगर_tx13_mux_क्रमागत =
	SOC_ENUM_SINGLE(WCD934X_DATA_HUB_SB_TX13_INP_CFG, 0,
			ARRAY_SIZE(cdc_अगर_tx13_mux_text), cdc_अगर_tx13_mux_text);

अटल पूर्णांक wcd934x_set_siकरो_input_src(काष्ठा wcd934x_codec *wcd, पूर्णांक siकरो_src)
अणु
	अगर (siकरो_src == wcd->siकरो_input_src)
		वापस 0;

	अगर (siकरो_src == SIDO_SOURCE_INTERNAL) अणु
		regmap_update_bits(wcd->regmap, WCD934X_ANA_BUCK_CTL,
				   WCD934X_ANA_BUCK_HI_ACCU_EN_MASK, 0);
		usleep_range(100, 110);
		regmap_update_bits(wcd->regmap, WCD934X_ANA_BUCK_CTL,
				   WCD934X_ANA_BUCK_HI_ACCU_PRE_ENX_MASK, 0x0);
		usleep_range(100, 110);
		regmap_update_bits(wcd->regmap, WCD934X_ANA_RCO,
				   WCD934X_ANA_RCO_BG_EN_MASK, 0);
		usleep_range(100, 110);
		regmap_update_bits(wcd->regmap, WCD934X_ANA_BUCK_CTL,
				   WCD934X_ANA_BUCK_PRE_EN1_MASK,
				   WCD934X_ANA_BUCK_PRE_EN1_ENABLE);
		usleep_range(100, 110);
		regmap_update_bits(wcd->regmap, WCD934X_ANA_BUCK_CTL,
				   WCD934X_ANA_BUCK_PRE_EN2_MASK,
				   WCD934X_ANA_BUCK_PRE_EN2_ENABLE);
		usleep_range(100, 110);
		regmap_update_bits(wcd->regmap, WCD934X_ANA_BUCK_CTL,
				   WCD934X_ANA_BUCK_HI_ACCU_EN_MASK,
				   WCD934X_ANA_BUCK_HI_ACCU_ENABLE);
		usleep_range(100, 110);
	पूर्ण अन्यथा अगर (siकरो_src == SIDO_SOURCE_RCO_BG) अणु
		regmap_update_bits(wcd->regmap, WCD934X_ANA_RCO,
				   WCD934X_ANA_RCO_BG_EN_MASK,
				   WCD934X_ANA_RCO_BG_ENABLE);
		usleep_range(100, 110);
	पूर्ण
	wcd->siकरो_input_src = siकरो_src;

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_enable_ana_bias_and_sysclk(काष्ठा wcd934x_codec *wcd)
अणु
	mutex_lock(&wcd->sysclk_mutex);

	अगर (++wcd->sysclk_users != 1) अणु
		mutex_unlock(&wcd->sysclk_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&wcd->sysclk_mutex);

	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_BIAS_EN_MASK,
			   WCD934X_ANA_BIAS_EN);
	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_PRECHRG_EN_MASK,
			   WCD934X_ANA_PRECHRG_EN);
	/*
	 * 1ms delay is required after pre-अक्षरge is enabled
	 * as per HW requirement
	 */
	usleep_range(1000, 1100);
	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_PRECHRG_EN_MASK, 0);
	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_PRECHRG_MODE_MASK, 0);

	/*
	 * In data घड़ी contrl रेजिस्टर is changed
	 * to CLK_SYS_MCLK_PRG
	 */

	regmap_update_bits(wcd->regmap, WCD934X_CLK_SYS_MCLK_PRG,
			   WCD934X_EXT_CLK_BUF_EN_MASK,
			   WCD934X_EXT_CLK_BUF_EN);
	regmap_update_bits(wcd->regmap, WCD934X_CLK_SYS_MCLK_PRG,
			   WCD934X_EXT_CLK_DIV_RATIO_MASK,
			   WCD934X_EXT_CLK_DIV_BY_2);
	regmap_update_bits(wcd->regmap, WCD934X_CLK_SYS_MCLK_PRG,
			   WCD934X_MCLK_SRC_MASK,
			   WCD934X_MCLK_SRC_EXT_CLK);
	regmap_update_bits(wcd->regmap, WCD934X_CLK_SYS_MCLK_PRG,
			   WCD934X_MCLK_EN_MASK, WCD934X_MCLK_EN);
	regmap_update_bits(wcd->regmap,
			   WCD934X_CDC_CLK_RST_CTRL_FS_CNT_CONTROL,
			   WCD934X_CDC_FS_MCLK_CNT_EN_MASK,
			   WCD934X_CDC_FS_MCLK_CNT_ENABLE);
	regmap_update_bits(wcd->regmap,
			   WCD934X_CDC_CLK_RST_CTRL_MCLK_CONTROL,
			   WCD934X_MCLK_EN_MASK,
			   WCD934X_MCLK_EN);
	regmap_update_bits(wcd->regmap, WCD934X_CODEC_RPM_CLK_GATE,
			   WCD934X_CODEC_RPM_CLK_GATE_MASK, 0x0);
	/*
	 * 10us sleep is required after घड़ी is enabled
	 * as per HW requirement
	 */
	usleep_range(10, 15);

	wcd934x_set_siकरो_input_src(wcd, SIDO_SOURCE_RCO_BG);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_disable_ana_bias_and_syclk(काष्ठा wcd934x_codec *wcd)
अणु
	mutex_lock(&wcd->sysclk_mutex);
	अगर (--wcd->sysclk_users != 0) अणु
		mutex_unlock(&wcd->sysclk_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&wcd->sysclk_mutex);

	regmap_update_bits(wcd->regmap, WCD934X_CLK_SYS_MCLK_PRG,
			   WCD934X_EXT_CLK_BUF_EN_MASK |
			   WCD934X_MCLK_EN_MASK, 0x0);
	wcd934x_set_siकरो_input_src(wcd, SIDO_SOURCE_INTERNAL);

	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_BIAS_EN_MASK, 0);
	regmap_update_bits(wcd->regmap, WCD934X_ANA_BIAS,
			   WCD934X_ANA_PRECHRG_EN_MASK, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __wcd934x_cdc_mclk_enable(काष्ठा wcd934x_codec *wcd, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		ret = clk_prepare_enable(wcd->extclk);

		अगर (ret) अणु
			dev_err(wcd->dev, "%s: ext clk enable failed\n",
				__func__);
			वापस ret;
		पूर्ण
		ret = wcd934x_enable_ana_bias_and_sysclk(wcd);
	पूर्ण अन्यथा अणु
		पूर्णांक val;

		regmap_पढ़ो(wcd->regmap, WCD934X_CDC_CLK_RST_CTRL_SWR_CONTROL,
			    &val);

		/* Don't disable घड़ी अगर soundwire using it.*/
		अगर (val & WCD934X_CDC_SWR_CLK_EN_MASK)
			वापस 0;

		wcd934x_disable_ana_bias_and_syclk(wcd);
		clk_disable_unprepare(wcd->extclk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_mclk(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस __wcd934x_cdc_mclk_enable(wcd, true);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस __wcd934x_cdc_mclk_enable(wcd, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_get_version(काष्ठा wcd934x_codec *wcd)
अणु
	पूर्णांक val1, val2, ver, ret;
	काष्ठा regmap *regmap;
	u16 id_minor;
	u32 version_mask = 0;

	regmap = wcd->regmap;
	ver = 0;

	ret = regmap_bulk_पढ़ो(regmap, WCD934X_CHIP_TIER_CTRL_CHIP_ID_BYTE0,
			       (u8 *)&id_minor, माप(u16));

	अगर (ret)
		वापस ret;

	regmap_पढ़ो(regmap, WCD934X_CHIP_TIER_CTRL_EFUSE_VAL_OUT14, &val1);
	regmap_पढ़ो(regmap, WCD934X_CHIP_TIER_CTRL_EFUSE_VAL_OUT15, &val2);

	version_mask |= (!!((u8)val1 & 0x80)) << DSD_DISABLED_MASK;
	version_mask |= (!!((u8)val2 & 0x01)) << SLNQ_DISABLED_MASK;

	चयन (version_mask) अणु
	हाल DSD_DISABLED | SLNQ_DISABLED:
		अगर (id_minor == 0)
			ver = WCD_VERSION_WCD9340_1_0;
		अन्यथा अगर (id_minor == 0x01)
			ver = WCD_VERSION_WCD9340_1_1;
		अवरोध;
	हाल SLNQ_DISABLED:
		अगर (id_minor == 0)
			ver = WCD_VERSION_WCD9341_1_0;
		अन्यथा अगर (id_minor == 0x01)
			ver = WCD_VERSION_WCD9341_1_1;
		अवरोध;
	पूर्ण

	wcd->version = ver;
	dev_info(wcd->dev, "WCD934X Minor:0x%x Version:0x%x\n", id_minor, ver);

	वापस 0;
पूर्ण

अटल व्योम wcd934x_enable_efuse_sensing(काष्ठा wcd934x_codec *wcd)
अणु
	पूर्णांक rc, val;

	__wcd934x_cdc_mclk_enable(wcd, true);

	regmap_update_bits(wcd->regmap,
			   WCD934X_CHIP_TIER_CTRL_EFUSE_CTL,
			   WCD934X_EFUSE_SENSE_STATE_MASK,
			   WCD934X_EFUSE_SENSE_STATE_DEF);
	regmap_update_bits(wcd->regmap,
			   WCD934X_CHIP_TIER_CTRL_EFUSE_CTL,
			   WCD934X_EFUSE_SENSE_EN_MASK,
			   WCD934X_EFUSE_SENSE_ENABLE);
	/*
	 * 5ms sleep required after enabling efuse control
	 * beक्रमe checking the status.
	 */
	usleep_range(5000, 5500);
	wcd934x_set_siकरो_input_src(wcd, SIDO_SOURCE_RCO_BG);

	rc = regmap_पढ़ो(wcd->regmap,
			 WCD934X_CHIP_TIER_CTRL_EFUSE_STATUS, &val);
	अगर (rc || (!(val & 0x01)))
		WARN(1, "%s: Efuse sense is not complete val=%x, ret=%d\n",
		     __func__, val, rc);

	__wcd934x_cdc_mclk_enable(wcd, false);
पूर्ण

अटल पूर्णांक wcd934x_swrm_घड़ी(काष्ठा wcd934x_codec *wcd, bool enable)
अणु
	अगर (enable) अणु
		__wcd934x_cdc_mclk_enable(wcd, true);
		regmap_update_bits(wcd->regmap,
				   WCD934X_CDC_CLK_RST_CTRL_SWR_CONTROL,
				   WCD934X_CDC_SWR_CLK_EN_MASK,
				   WCD934X_CDC_SWR_CLK_ENABLE);
	पूर्ण अन्यथा अणु
		regmap_update_bits(wcd->regmap,
				   WCD934X_CDC_CLK_RST_CTRL_SWR_CONTROL,
				   WCD934X_CDC_SWR_CLK_EN_MASK, 0);
		__wcd934x_cdc_mclk_enable(wcd, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_set_prim_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					      u8 rate_val, u32 rate)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	काष्ठा wcd934x_slim_ch *ch;
	u8 cfg0, cfg1, inp0_sel, inp1_sel, inp2_sel;
	पूर्णांक inp, j;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		inp = ch->shअगरt + INTn_1_INP_SEL_RX0;
		/*
		 * Loop through all पूर्णांकerpolator MUX inमाला_दो and find out
		 * to which पूर्णांकerpolator input, the slim rx port
		 * is connected
		 */
		क्रम (j = 0; j < WCD934X_NUM_INTERPOLATORS; j++) अणु
			/* Interpolators 5 and 6 are not aviliable in Tavil */
			अगर (j == INTERP_LO3_NA || j == INTERP_LO4_NA)
				जारी;

			cfg0 = snd_soc_component_पढ़ो(comp,
					WCD934X_CDC_RX_INP_MUX_RX_INT_CFG0(j));
			cfg1 = snd_soc_component_पढ़ो(comp,
					WCD934X_CDC_RX_INP_MUX_RX_INT_CFG1(j));

			inp0_sel = cfg0 &
				 WCD934X_CDC_RX_INP_MUX_RX_INT_SEL_MASK;
			inp1_sel = (cfg0 >> 4) &
				 WCD934X_CDC_RX_INP_MUX_RX_INT_SEL_MASK;
			inp2_sel = (cfg1 >> 4) &
				 WCD934X_CDC_RX_INP_MUX_RX_INT_SEL_MASK;

			अगर ((inp0_sel == inp) ||  (inp1_sel == inp) ||
			    (inp2_sel == inp)) अणु
				/* rate is in Hz */
				/*
				 * Ear and speaker primary path करोes not support
				 * native sample rates
				 */
				अगर ((j == INTERP_EAR || j == INTERP_SPKR1 ||
				     j == INTERP_SPKR2) && rate == 44100)
					dev_err(wcd->dev,
						"Cannot set 44.1KHz on INT%d\n",
						j);
				अन्यथा
					snd_soc_component_update_bits(comp,
					      WCD934X_CDC_RX_PATH_CTL(j),
					      WCD934X_CDC_MIX_PCM_RATE_MASK,
					      rate_val);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_set_mix_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					     पूर्णांक rate_val, u32 rate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);
	काष्ठा wcd934x_slim_ch *ch;
	पूर्णांक val, j;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		क्रम (j = 0; j < WCD934X_NUM_INTERPOLATORS; j++) अणु
			/* Interpolators 5 and 6 are not aviliable in Tavil */
			अगर (j == INTERP_LO3_NA || j == INTERP_LO4_NA)
				जारी;
			val = snd_soc_component_पढ़ो(component,
					WCD934X_CDC_RX_INP_MUX_RX_INT_CFG1(j)) &
					WCD934X_CDC_RX_INP_MUX_RX_INT_SEL_MASK;

			अगर (val == (ch->shअगरt + INTn_2_INP_SEL_RX0)) अणु
				/*
				 * Ear mix path supports only 48, 96, 192,
				 * 384KHz only
				 */
				अगर ((j == INTERP_EAR) &&
				    (rate_val < 0x4 ||
				     rate_val > 0x7)) अणु
					dev_err(component->dev,
						"Invalid rate for AIF_PB DAI(%d)\n",
						dai->id);
					वापस -EINVAL;
				पूर्ण

				snd_soc_component_update_bits(component,
					      WCD934X_CDC_RX_PATH_MIX_CTL(j),
					      WCD934X_CDC_MIX_PCM_RATE_MASK,
					      rate_val);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_set_पूर्णांकerpolator_rate(काष्ठा snd_soc_dai *dai,
					 u32 sample_rate)
अणु
	पूर्णांक rate_val = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(sr_val_tbl); i++) अणु
		अगर (sample_rate == sr_val_tbl[i].sample_rate) अणु
			rate_val = sr_val_tbl[i].rate_val;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((i == ARRAY_SIZE(sr_val_tbl)) || (rate_val < 0)) अणु
		dev_err(dai->dev, "Unsupported sample rate: %d\n", sample_rate);
		वापस -EINVAL;
	पूर्ण

	ret = wcd934x_set_prim_पूर्णांकerpolator_rate(dai, (u8)rate_val,
						 sample_rate);
	अगर (ret)
		वापस ret;
	ret = wcd934x_set_mix_पूर्णांकerpolator_rate(dai, (u8)rate_val,
						sample_rate);

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_set_decimator_rate(काष्ठा snd_soc_dai *dai,
				      u8 rate_val, u32 rate)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा wcd934x_codec *wcd = snd_soc_component_get_drvdata(comp);
	u8 shअगरt = 0, shअगरt_val = 0, tx_mux_sel;
	काष्ठा wcd934x_slim_ch *ch;
	पूर्णांक tx_port, tx_port_reg;
	पूर्णांक decimator = -1;

	list_क्रम_each_entry(ch, &wcd->dai[dai->id].slim_ch_list, list) अणु
		tx_port = ch->port;
		/* Find the SB TX MUX input - which decimator is connected */
		चयन (tx_port) अणु
		हाल 0 ...  3:
			tx_port_reg = WCD934X_CDC_IF_ROUTER_TX_MUX_CFG0;
			shअगरt = (tx_port << 1);
			shअगरt_val = 0x03;
			अवरोध;
		हाल 4 ... 7:
			tx_port_reg = WCD934X_CDC_IF_ROUTER_TX_MUX_CFG1;
			shअगरt = ((tx_port - 4) << 1);
			shअगरt_val = 0x03;
			अवरोध;
		हाल 8 ... 10:
			tx_port_reg = WCD934X_CDC_IF_ROUTER_TX_MUX_CFG2;
			shअगरt = ((tx_port - 8) << 1);
			shअगरt_val = 0x03;
			अवरोध;
		हाल 11:
			tx_port_reg = WCD934X_CDC_IF_ROUTER_TX_MUX_CFG3;
			shअगरt = 0;
			shअगरt_val = 0x0F;
			अवरोध;
		हाल 13:
			tx_port_reg = WCD934X_CDC_IF_ROUTER_TX_MUX_CFG3;
			shअगरt = 4;
			shअगरt_val = 0x03;
			अवरोध;
		शेष:
			dev_err(wcd->dev, "Invalid SLIM TX%u port DAI ID:%d\n",
				tx_port, dai->id);
			वापस -EINVAL;
		पूर्ण

		tx_mux_sel = snd_soc_component_पढ़ो(comp, tx_port_reg) &
						      (shअगरt_val << shअगरt);

		tx_mux_sel = tx_mux_sel >> shअगरt;
		चयन (tx_port) अणु
		हाल 0 ... 8:
			अगर ((tx_mux_sel == 0x2) || (tx_mux_sel == 0x3))
				decimator = tx_port;
			अवरोध;
		हाल 9 ... 10:
			अगर ((tx_mux_sel == 0x1) || (tx_mux_sel == 0x2))
				decimator = ((tx_port == 9) ? 7 : 6);
			अवरोध;
		हाल 11:
			अगर ((tx_mux_sel >= 1) && (tx_mux_sel < 7))
				decimator = tx_mux_sel - 1;
			अवरोध;
		हाल 13:
			अगर ((tx_mux_sel == 0x1) || (tx_mux_sel == 0x2))
				decimator = 5;
			अवरोध;
		शेष:
			dev_err(wcd->dev, "ERROR: Invalid tx_port: %d\n",
				tx_port);
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(comp,
				      WCD934X_CDC_TX_PATH_CTL(decimator),
				      WCD934X_CDC_TX_PATH_CTL_PCM_RATE_MASK,
				      rate_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_slim_set_hw_params(काष्ठा wcd934x_codec *wcd,
				      काष्ठा wcd_slim_codec_dai_data *dai_data,
				      पूर्णांक direction)
अणु
	काष्ठा list_head *slim_ch_list = &dai_data->slim_ch_list;
	काष्ठा slim_stream_config *cfg = &dai_data->sconfig;
	काष्ठा wcd934x_slim_ch *ch;
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
			   WCD934X_SLIM_PGD_RX_PORT_MULTI_CHNL_0(ch->port),
			   payload);

			अगर (ret < 0)
				जाओ err;

			/* configure the slave port क्रम water mark and enable*/
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
					WCD934X_SLIM_PGD_RX_PORT_CFG(ch->port),
					WCD934X_SLIM_WATER_MARK_VAL);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
				WCD934X_SLIM_PGD_TX_PORT_MULTI_CHNL_0(ch->port),
				payload & 0x00FF);
			अगर (ret < 0)
				जाओ err;

			/* ports 8,9 */
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
				WCD934X_SLIM_PGD_TX_PORT_MULTI_CHNL_1(ch->port),
				(payload & 0xFF00) >> 8);
			अगर (ret < 0)
				जाओ err;

			/* configure the slave port क्रम water mark and enable*/
			ret = regmap_ग_लिखो(wcd->अगर_regmap,
					WCD934X_SLIM_PGD_TX_PORT_CFG(ch->port),
					WCD934X_SLIM_WATER_MARK_VAL);

			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	dai_data->srunसमय = slim_stream_allocate(wcd->sdev, "WCD934x-SLIM");

	वापस 0;

err:
	dev_err(wcd->dev, "Error Setting slim hw params\n");
	kमुक्त(cfg->chs);
	cfg->chs = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wcd934x_codec *wcd;
	पूर्णांक ret, tx_fs_rate = 0;

	wcd = snd_soc_component_get_drvdata(dai->component);

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		ret = wcd934x_set_पूर्णांकerpolator_rate(dai, params_rate(params));
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
			dev_err(wcd->dev, "Invalid format 0x%x\n",
				params_width(params));
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
			dev_err(wcd->dev, "Invalid TX sample rate: %d\n",
				params_rate(params));
			वापस -EINVAL;

		पूर्ण

		ret = wcd934x_set_decimator_rate(dai, tx_fs_rate,
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
			dev_err(wcd->dev, "Invalid format 0x%x\n",
				params_width(params));
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(wcd->dev, "Invalid stream type %d\n",
			substream->stream);
		वापस -EINVAL;
	पूर्ण

	wcd->dai[dai->id].sconfig.rate = params_rate(params);
	wcd934x_slim_set_hw_params(wcd, &wcd->dai[dai->id], substream->stream);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wcd_slim_codec_dai_data *dai_data;
	काष्ठा wcd934x_codec *wcd;

	wcd = snd_soc_component_get_drvdata(dai->component);

	dai_data = &wcd->dai[dai->id];

	kमुक्त(dai_data->sconfig.chs);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wcd_slim_codec_dai_data *dai_data;
	काष्ठा wcd934x_codec *wcd;
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

अटल पूर्णांक wcd934x_set_channel_map(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				   अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा wcd934x_codec *wcd;
	पूर्णांक i;

	wcd = snd_soc_component_get_drvdata(dai->component);

	अगर (tx_num > WCD934X_TX_MAX || rx_num > WCD934X_RX_MAX) अणु
		dev_err(wcd->dev, "Invalid tx %d or rx %d channel count\n",
			tx_num, rx_num);
		वापस -EINVAL;
	पूर्ण

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

अटल पूर्णांक wcd934x_get_channel_map(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				   अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा wcd934x_slim_ch *ch;
	काष्ठा wcd934x_codec *wcd;
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

अटल स्थिर काष्ठा snd_soc_dai_ops wcd934x_dai_ops = अणु
	.hw_params = wcd934x_hw_params,
	.hw_मुक्त = wcd934x_hw_मुक्त,
	.trigger = wcd934x_trigger,
	.set_channel_map = wcd934x_set_channel_map,
	.get_channel_map = wcd934x_get_channel_map,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wcd934x_slim_dais[] = अणु
	[0] = अणु
		.name = "wcd934x_rx1",
		.id = AIF1_PB,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.rates = WCD934X_RATES_MASK | WCD934X_FRAC_RATES_MASK,
			.क्रमmats = WCD934X_FORMATS_S16_S24_LE,
			.rate_max = 192000,
			.rate_min = 8000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[1] = अणु
		.name = "wcd934x_tx1",
		.id = AIF1_CAP,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.rates = WCD934X_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[2] = अणु
		.name = "wcd934x_rx2",
		.id = AIF2_PB,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.rates = WCD934X_RATES_MASK | WCD934X_FRAC_RATES_MASK,
			.क्रमmats = WCD934X_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[3] = अणु
		.name = "wcd934x_tx2",
		.id = AIF2_CAP,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.rates = WCD934X_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[4] = अणु
		.name = "wcd934x_rx3",
		.id = AIF3_PB,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.rates = WCD934X_RATES_MASK | WCD934X_FRAC_RATES_MASK,
			.क्रमmats = WCD934X_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[5] = अणु
		.name = "wcd934x_tx3",
		.id = AIF3_CAP,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.rates = WCD934X_RATES_MASK,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 4,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
	[6] = अणु
		.name = "wcd934x_rx4",
		.id = AIF4_PB,
		.playback = अणु
			.stream_name = "AIF4 Playback",
			.rates = WCD934X_RATES_MASK | WCD934X_FRAC_RATES_MASK,
			.क्रमmats = WCD934X_FORMATS_S16_S24_LE,
			.rate_min = 8000,
			.rate_max = 192000,
			.channels_min = 1,
			.channels_max = 2,
		पूर्ण,
		.ops = &wcd934x_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक swclk_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस wcd934x_swrm_घड़ी(to_wcd934x_codec(hw), true);
पूर्ण

अटल व्योम swclk_gate_disable(काष्ठा clk_hw *hw)
अणु
	wcd934x_swrm_घड़ी(to_wcd934x_codec(hw), false);
पूर्ण

अटल पूर्णांक swclk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा wcd934x_codec *wcd = to_wcd934x_codec(hw);
	पूर्णांक ret, val;

	regmap_पढ़ो(wcd->regmap, WCD934X_CDC_CLK_RST_CTRL_SWR_CONTROL, &val);
	ret = val & WCD934X_CDC_SWR_CLK_EN_MASK;

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

अटल काष्ठा clk *wcd934x_रेजिस्टर_mclk_output(काष्ठा wcd934x_codec *wcd)
अणु
	काष्ठा clk *parent = wcd->extclk;
	काष्ठा device *dev = wcd->dev;
	काष्ठा device_node *np = dev->parent->of_node;
	स्थिर अक्षर *parent_clk_name = शून्य;
	स्थिर अक्षर *clk_name = "mclk";
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &wcd->rate))
		वापस शून्य;

	parent_clk_name = __clk_get_name(parent);

	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = &swclk_gate_ops;
	init.flags = 0;
	init.parent_names = &parent_clk_name;
	init.num_parents = 1;
	wcd->hw.init = &init;

	hw = &wcd->hw;
	ret = devm_clk_hw_रेजिस्टर(wcd->dev->parent, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस शून्य;
पूर्ण

अटल पूर्णांक wcd934x_get_micbias_val(काष्ठा device *dev, स्थिर अक्षर *micbias)
अणु
	पूर्णांक mv;

	अगर (of_property_पढ़ो_u32(dev->parent->of_node, micbias, &mv)) अणु
		dev_err(dev, "%s value not found, using default\n", micbias);
		mv = WCD934X_DEF_MICBIAS_MV;
	पूर्ण अन्यथा अणु
		/* convert it to milli volts */
		mv = mv/1000;
	पूर्ण

	अगर (mv < 1000 || mv > 2850) अणु
		dev_err(dev, "%s value not in valid range, using default\n",
			micbias);
		mv = WCD934X_DEF_MICBIAS_MV;
	पूर्ण

	वापस (mv - 1000) / 50;
पूर्ण

अटल पूर्णांक wcd934x_init_dmic(काष्ठा snd_soc_component *comp)
अणु
	पूर्णांक vout_ctl_1, vout_ctl_2, vout_ctl_3, vout_ctl_4;
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	u32 def_dmic_rate, dmic_clk_drv;

	vout_ctl_1 = wcd934x_get_micbias_val(comp->dev,
					     "qcom,micbias1-microvolt");
	vout_ctl_2 = wcd934x_get_micbias_val(comp->dev,
					     "qcom,micbias2-microvolt");
	vout_ctl_3 = wcd934x_get_micbias_val(comp->dev,
					     "qcom,micbias3-microvolt");
	vout_ctl_4 = wcd934x_get_micbias_val(comp->dev,
					     "qcom,micbias4-microvolt");

	snd_soc_component_update_bits(comp, WCD934X_ANA_MICB1,
				      WCD934X_MICB_VAL_MASK, vout_ctl_1);
	snd_soc_component_update_bits(comp, WCD934X_ANA_MICB2,
				      WCD934X_MICB_VAL_MASK, vout_ctl_2);
	snd_soc_component_update_bits(comp, WCD934X_ANA_MICB3,
				      WCD934X_MICB_VAL_MASK, vout_ctl_3);
	snd_soc_component_update_bits(comp, WCD934X_ANA_MICB4,
				      WCD934X_MICB_VAL_MASK, vout_ctl_4);

	अगर (wcd->rate == WCD934X_MCLK_CLK_9P6MHZ)
		def_dmic_rate = WCD9XXX_DMIC_SAMPLE_RATE_4P8MHZ;
	अन्यथा
		def_dmic_rate = WCD9XXX_DMIC_SAMPLE_RATE_4P096MHZ;

	wcd->dmic_sample_rate = def_dmic_rate;

	dmic_clk_drv = 0;
	snd_soc_component_update_bits(comp, WCD934X_TEST_DEBUG_PAD_DRVCTL_0,
				      0x0C, dmic_clk_drv << 2);

	वापस 0;
पूर्ण

अटल व्योम wcd934x_hw_init(काष्ठा wcd934x_codec *wcd)
अणु
	काष्ठा regmap *rm = wcd->regmap;

	/* set SPKR rate to FS_2P4_3P072 */
	regmap_update_bits(rm, WCD934X_CDC_RX7_RX_PATH_CFG1, 0x08, 0x08);
	regmap_update_bits(rm, WCD934X_CDC_RX8_RX_PATH_CFG1, 0x08, 0x08);

	/* Take DMICs out of reset */
	regmap_update_bits(rm, WCD934X_CPE_SS_DMIC_CFG, 0x80, 0x00);
पूर्ण

अटल पूर्णांक wcd934x_comp_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);

	wcd934x_hw_init(wcd);
	wcd934x_enable_efuse_sensing(wcd);
	wcd934x_get_version(wcd);

	वापस 0;
पूर्ण

अटल irqवापस_t wcd934x_slim_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wcd934x_codec *wcd = data;
	अचिन्हित दीर्घ status = 0;
	पूर्णांक i, j, port_id;
	अचिन्हित पूर्णांक val, पूर्णांक_val = 0;
	irqवापस_t ret = IRQ_NONE;
	bool tx;
	अचिन्हित लघु reg = 0;

	क्रम (i = WCD934X_SLIM_PGD_PORT_INT_STATUS_RX_0, j = 0;
	     i <= WCD934X_SLIM_PGD_PORT_INT_STATUS_TX_1; i++, j++) अणु
		regmap_पढ़ो(wcd->अगर_regmap, i, &val);
		status |= ((u32)val << (8 * j));
	पूर्ण

	क्रम_each_set_bit(j, &status, 32) अणु
		tx = false;
		port_id = j;

		अगर (j >= 16) अणु
			tx = true;
			port_id = j - 16;
		पूर्ण

		regmap_पढ़ो(wcd->अगर_regmap,
			    WCD934X_SLIM_PGD_PORT_INT_RX_SOURCE0 + j, &val);
		अगर (val) अणु
			अगर (!tx)
				reg = WCD934X_SLIM_PGD_PORT_INT_EN0 +
					(port_id / 8);
			अन्यथा
				reg = WCD934X_SLIM_PGD_PORT_INT_TX_EN0 +
					(port_id / 8);
			regmap_पढ़ो(wcd->अगर_regmap, reg, &पूर्णांक_val);
		पूर्ण

		अगर (val & WCD934X_SLIM_IRQ_OVERFLOW)
			dev_err_ratelimited(wcd->dev,
					    "overflow error on %s port %d, value %x\n",
					    (tx ? "TX" : "RX"), port_id, val);

		अगर (val & WCD934X_SLIM_IRQ_UNDERFLOW)
			dev_err_ratelimited(wcd->dev,
					    "underflow error on %s port %d, value %x\n",
					    (tx ? "TX" : "RX"), port_id, val);

		अगर ((val & WCD934X_SLIM_IRQ_OVERFLOW) ||
		    (val & WCD934X_SLIM_IRQ_UNDERFLOW)) अणु
			अगर (!tx)
				reg = WCD934X_SLIM_PGD_PORT_INT_EN0 +
					(port_id / 8);
			अन्यथा
				reg = WCD934X_SLIM_PGD_PORT_INT_TX_EN0 +
					(port_id / 8);
			regmap_पढ़ो(
				wcd->अगर_regmap, reg, &पूर्णांक_val);
			अगर (पूर्णांक_val & (1 << (port_id % 8))) अणु
				पूर्णांक_val = पूर्णांक_val ^ (1 << (port_id % 8));
				regmap_ग_लिखो(wcd->अगर_regmap,
					     reg, पूर्णांक_val);
			पूर्ण
		पूर्ण

		अगर (val & WCD934X_SLIM_IRQ_PORT_CLOSED)
			dev_err_ratelimited(wcd->dev,
					    "Port Closed %s port %d, value %x\n",
					    (tx ? "TX" : "RX"), port_id, val);

		regmap_ग_लिखो(wcd->अगर_regmap,
			     WCD934X_SLIM_PGD_PORT_INT_CLR_RX_0 + (j / 8),
				BIT(j % 8));
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_comp_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक i;

	snd_soc_component_init_regmap(component, wcd->regmap);
	wcd->component = component;

	/* Class-H Init*/
	wcd->clsh_ctrl = wcd_clsh_ctrl_alloc(component, wcd->version);
	अगर (IS_ERR(wcd->clsh_ctrl))
		वापस PTR_ERR(wcd->clsh_ctrl);

	/* Default HPH Mode to Class-H Low HiFi */
	wcd->hph_mode = CLS_H_LOHIFI;

	wcd934x_comp_init(component);

	क्रम (i = 0; i < NUM_CODEC_DAIS; i++)
		INIT_LIST_HEAD(&wcd->dai[i].slim_ch_list);

	wcd934x_init_dmic(component);
	वापस 0;
पूर्ण

अटल व्योम wcd934x_comp_हटाओ(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);

	wcd_clsh_ctrl_मुक्त(wcd->clsh_ctrl);
पूर्ण

अटल पूर्णांक wcd934x_comp_set_sysclk(काष्ठा snd_soc_component *comp,
				   पूर्णांक clk_id, पूर्णांक source,
				   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक val = WCD934X_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ;

	wcd->rate = freq;

	अगर (wcd->rate == WCD934X_MCLK_CLK_12P288MHZ)
		val = WCD934X_CODEC_RPM_CLK_MCLK_CFG_12P288MHZ;

	snd_soc_component_update_bits(comp, WCD934X_CODEC_RPM_CLK_MCLK_CFG,
				      WCD934X_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
				      val);

	वापस clk_set_rate(wcd->extclk, freq);
पूर्ण

अटल uपूर्णांक32_t get_iir_band_coeff(काष्ठा snd_soc_component *component,
				   पूर्णांक iir_idx, पूर्णांक band_idx, पूर्णांक coeff_idx)
अणु
	u32 value = 0;
	पूर्णांक reg, b2_reg;

	/* Address करोes not स्वतःmatically update अगर पढ़ोing */
	reg = WCD934X_CDC_SIDETONE_IIR0_IIR_COEF_B1_CTL + 16 * iir_idx;
	b2_reg = WCD934X_CDC_SIDETONE_IIR0_IIR_COEF_B2_CTL + 16 * iir_idx;

	snd_soc_component_ग_लिखो(component, reg,
				((band_idx * BAND_MAX + coeff_idx) *
				 माप(uपूर्णांक32_t)) & 0x7F);

	value |= snd_soc_component_पढ़ो(component, b2_reg);
	snd_soc_component_ग_लिखो(component, reg,
				((band_idx * BAND_MAX + coeff_idx)
				 * माप(uपूर्णांक32_t) + 1) & 0x7F);

	value |= (snd_soc_component_पढ़ो(component, b2_reg) << 8);
	snd_soc_component_ग_लिखो(component, reg,
				((band_idx * BAND_MAX + coeff_idx)
				 * माप(uपूर्णांक32_t) + 2) & 0x7F);

	value |= (snd_soc_component_पढ़ो(component, b2_reg) << 16);
	snd_soc_component_ग_लिखो(component, reg,
		((band_idx * BAND_MAX + coeff_idx)
		* माप(uपूर्णांक32_t) + 3) & 0x7F);

	/* Mask bits top 2 bits since they are reserved */
	value |= (snd_soc_component_पढ़ो(component, b2_reg) << 24);
	वापस value;
पूर्ण

अटल व्योम set_iir_band_coeff(काष्ठा snd_soc_component *component,
			       पूर्णांक iir_idx, पूर्णांक band_idx, uपूर्णांक32_t value)
अणु
	पूर्णांक reg = WCD934X_CDC_SIDETONE_IIR0_IIR_COEF_B2_CTL + 16 * iir_idx;

	snd_soc_component_ग_लिखो(component, reg, (value & 0xFF));
	snd_soc_component_ग_लिखो(component, reg, (value >> 8) & 0xFF);
	snd_soc_component_ग_लिखो(component, reg, (value >> 16) & 0xFF);
	/* Mask top 2 bits, 7-8 are reserved */
	snd_soc_component_ग_लिखो(component, reg, (value >> 24) & 0x3F);
पूर्ण

अटल पूर्णांक wcd934x_put_iir_band_audio_mixer(
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
	पूर्णांक reg = WCD934X_CDC_SIDETONE_IIR0_IIR_COEF_B1_CTL + 16 * iir_idx;

	स_नकल(&coeff[0], ucontrol->value.bytes.data, params->max);

	/* Mask top bit it is reserved */
	/* Updates addr स्वतःmatically क्रम each B2 ग_लिखो */
	snd_soc_component_ग_लिखो(component, reg, (band_idx * BAND_MAX *
						 माप(uपूर्णांक32_t)) & 0x7F);

	set_iir_band_coeff(component, iir_idx, band_idx, coeff[0]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[1]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[2]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[3]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[4]);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_get_iir_band_audio_mixer(काष्ठा snd_kcontrol *kcontrol,
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

अटल पूर्णांक wcd934x_iir_filter_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *ucontrol)
अणु
	काष्ठा wcd_iir_filter_ctl *ctl =
		(काष्ठा wcd_iir_filter_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;

	ucontrol->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	ucontrol->count = params->max;

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_compander_get(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *)kc->निजी_value)->shअगरt;
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);

	ucontrol->value.पूर्णांकeger.value[0] = wcd->comp_enabled[comp];

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_compander_set(काष्ठा snd_kcontrol *kc,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);
	पूर्णांक comp = ((काष्ठा soc_mixer_control *)kc->निजी_value)->shअगरt;
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक sel;

	wcd->comp_enabled[comp] = value;
	sel = value ? WCD934X_HPH_GAIN_SRC_SEL_COMPANDER :
		WCD934X_HPH_GAIN_SRC_SEL_REGISTER;

	/* Any specअगरic रेजिस्टर configuration क्रम compander */
	चयन (comp) अणु
	हाल COMPANDER_1:
		/* Set Gain Source Select based on compander enable/disable */
		snd_soc_component_update_bits(component, WCD934X_HPH_L_EN,
					      WCD934X_HPH_GAIN_SRC_SEL_MASK,
					      sel);
		अवरोध;
	हाल COMPANDER_2:
		snd_soc_component_update_bits(component, WCD934X_HPH_R_EN,
					      WCD934X_HPH_GAIN_SRC_SEL_MASK,
					      sel);
		अवरोध;
	हाल COMPANDER_3:
	हाल COMPANDER_4:
	हाल COMPANDER_7:
	हाल COMPANDER_8:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_rx_hph_mode_get(काष्ठा snd_kcontrol *kc,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);

	ucontrol->value.क्रमागतerated.item[0] = wcd->hph_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_rx_hph_mode_put(काष्ठा snd_kcontrol *kc,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);
	u32 mode_val;

	mode_val = ucontrol->value.क्रमागतerated.item[0];

	अगर (mode_val == 0) अणु
		dev_err(wcd->dev, "Invalid HPH Mode, default to ClSH HiFi\n");
		mode_val = CLS_H_LOHIFI;
	पूर्ण
	wcd->hph_mode = mode_val;

	वापस 0;
पूर्ण

अटल पूर्णांक slim_rx_mux_get(काष्ठा snd_kcontrol *kc,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kc);
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(dapm->dev);

	ucontrol->value.क्रमागतerated.item[0] = wcd->rx_port_value[w->shअगरt];

	वापस 0;
पूर्ण

अटल पूर्णांक slim_rx_mux_put(काष्ठा snd_kcontrol *kc,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(w->dapm->dev);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kc->निजी_value;
	काष्ठा snd_soc_dapm_update *update = शून्य;
	u32 port_id = w->shअगरt;

	अगर (wcd->rx_port_value[port_id] == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	wcd->rx_port_value[port_id] = ucontrol->value.क्रमागतerated.item[0];

	चयन (wcd->rx_port_value[port_id]) अणु
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
		dev_err(wcd->dev, "Unknown AIF %d\n",
			wcd->rx_port_value[port_id]);
		जाओ err;
	पूर्ण

	snd_soc_dapm_mux_update_घातer(w->dapm, kc, wcd->rx_port_value[port_id],
				      e, update);

	वापस 0;
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wcd934x_पूर्णांक_dem_inp_mux_put(काष्ठा snd_kcontrol *kc,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kc->निजी_value;
	काष्ठा snd_soc_component *component;
	पूर्णांक reg, val, ret;

	component = snd_soc_dapm_kcontrol_component(kc);
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (e->reg == WCD934X_CDC_RX0_RX_PATH_SEC0)
		reg = WCD934X_CDC_RX0_RX_PATH_CFG0;
	अन्यथा अगर (e->reg == WCD934X_CDC_RX1_RX_PATH_SEC0)
		reg = WCD934X_CDC_RX1_RX_PATH_CFG0;
	अन्यथा अगर (e->reg == WCD934X_CDC_RX2_RX_PATH_SEC0)
		reg = WCD934X_CDC_RX2_RX_PATH_CFG0;
	अन्यथा
		वापस -EINVAL;

	/* Set Look Ahead Delay */
	अगर (val)
		snd_soc_component_update_bits(component, reg,
					      WCD934X_RX_DLY_ZN_EN_MASK,
					      WCD934X_RX_DLY_ZN_ENABLE);
	अन्यथा
		snd_soc_component_update_bits(component, reg,
					      WCD934X_RX_DLY_ZN_EN_MASK,
					      WCD934X_RX_DLY_ZN_DISABLE);

	ret = snd_soc_dapm_put_क्रमागत_द्विगुन(kc, ucontrol);

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_dec_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;
	u16 mic_sel_reg = 0;
	u8 mic_sel;

	comp = snd_soc_dapm_kcontrol_component(kcontrol);

	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val > e->items - 1)
		वापस -EINVAL;

	चयन (e->reg) अणु
	हाल WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1:
		अगर (e->shअगरt_l == 0)
			mic_sel_reg = WCD934X_CDC_TX0_TX_PATH_CFG0;
		अन्यथा अगर (e->shअगरt_l == 2)
			mic_sel_reg = WCD934X_CDC_TX4_TX_PATH_CFG0;
		अन्यथा अगर (e->shअगरt_l == 4)
			mic_sel_reg = WCD934X_CDC_TX8_TX_PATH_CFG0;
		अवरोध;
	हाल WCD934X_CDC_TX_INP_MUX_ADC_MUX1_CFG1:
		अगर (e->shअगरt_l == 0)
			mic_sel_reg = WCD934X_CDC_TX1_TX_PATH_CFG0;
		अन्यथा अगर (e->shअगरt_l == 2)
			mic_sel_reg = WCD934X_CDC_TX5_TX_PATH_CFG0;
		अवरोध;
	हाल WCD934X_CDC_TX_INP_MUX_ADC_MUX2_CFG1:
		अगर (e->shअगरt_l == 0)
			mic_sel_reg = WCD934X_CDC_TX2_TX_PATH_CFG0;
		अन्यथा अगर (e->shअगरt_l == 2)
			mic_sel_reg = WCD934X_CDC_TX6_TX_PATH_CFG0;
		अवरोध;
	हाल WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1:
		अगर (e->shअगरt_l == 0)
			mic_sel_reg = WCD934X_CDC_TX3_TX_PATH_CFG0;
		अन्यथा अगर (e->shअगरt_l == 2)
			mic_sel_reg = WCD934X_CDC_TX7_TX_PATH_CFG0;
		अवरोध;
	शेष:
		dev_err(comp->dev, "%s: e->reg: 0x%x not expected\n",
			__func__, e->reg);
		वापस -EINVAL;
	पूर्ण

	/* ADC: 0, DMIC: 1 */
	mic_sel = val ? 0x0 : 0x1;
	अगर (mic_sel_reg)
		snd_soc_component_update_bits(comp, mic_sel_reg, BIT(7),
					      mic_sel << 7);

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

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

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT0 MIX2 INP Mux", rx_पूर्णांक0_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT1 MIX2 INP Mux", rx_पूर्णांक1_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT2 MIX2 INP Mux", rx_पूर्णांक2_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT3 MIX2 INP Mux", rx_पूर्णांक3_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT4 MIX2 INP Mux", rx_पूर्णांक4_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_mix2_inp_mux =
	SOC_DAPM_ENUM("RX INT7 MIX2 INP Mux", rx_पूर्णांक7_mix2_inp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new iir0_inp0_mux =
	SOC_DAPM_ENUM("IIR0 INP0 Mux", iir0_inp0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir0_inp1_mux =
	SOC_DAPM_ENUM("IIR0 INP1 Mux", iir0_inp1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir0_inp2_mux =
	SOC_DAPM_ENUM("IIR0 INP2 Mux", iir0_inp2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir0_inp3_mux =
	SOC_DAPM_ENUM("IIR0 INP3 Mux", iir0_inp3_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new iir1_inp0_mux =
	SOC_DAPM_ENUM("IIR1 INP0 Mux", iir1_inp0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir1_inp1_mux =
	SOC_DAPM_ENUM("IIR1 INP1 Mux", iir1_inp1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir1_inp2_mux =
	SOC_DAPM_ENUM("IIR1 INP2 Mux", iir1_inp2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new iir1_inp3_mux =
	SOC_DAPM_ENUM("IIR1 INP3 Mux", iir1_inp3_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new slim_rx_mux[WCD934X_RX_MAX] = अणु
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

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_asrc_चयन[] = अणु
	SOC_DAPM_SINGLE("HPHL Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_asrc_चयन[] = अणु
	SOC_DAPM_SINGLE("HPHR Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_asrc_चयन[] = अणु
	SOC_DAPM_SINGLE("LO1 Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_asrc_चयन[] = अणु
	SOC_DAPM_SINGLE("LO2 Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT0 DEM MUX Mux", rx_पूर्णांक0_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd934x_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT1 DEM MUX Mux", rx_पूर्णांक1_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd934x_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_dem_inp_mux =
	SOC_DAPM_ENUM_EXT("RX INT2 DEM MUX Mux", rx_पूर्णांक2_dem_inp_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  wcd934x_पूर्णांक_dem_inp_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT0_1 INTERP Mux", rx_पूर्णांक0_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT1_1 INTERP Mux", rx_पूर्णांक1_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT2_1 INTERP Mux", rx_पूर्णांक2_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT3_1 INTERP Mux", rx_पूर्णांक3_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT4_1 INTERP Mux", rx_पूर्णांक4_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT7_1 INTERP Mux", rx_पूर्णांक7_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_1_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT8_1 INTERP Mux", rx_पूर्णांक8_1_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक0_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT0_2 INTERP Mux", rx_पूर्णांक0_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक1_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT1_2 INTERP Mux", rx_पूर्णांक1_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक2_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT2_2 INTERP Mux", rx_पूर्णांक2_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक3_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT3_2 INTERP Mux", rx_पूर्णांक3_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक4_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT4_2 INTERP Mux", rx_पूर्णांक4_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक7_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT7_2 INTERP Mux", rx_पूर्णांक7_2_पूर्णांकerp_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx_पूर्णांक8_2_पूर्णांकerp_mux =
	SOC_DAPM_ENUM("RX INT8_2 INTERP Mux", rx_पूर्णांक8_2_पूर्णांकerp_mux_क्रमागत);

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

अटल स्थिर काष्ठा snd_kcontrol_new tx_amic4_5 =
	SOC_DAPM_ENUM("AMIC4_5 SEL Mux", tx_amic4_5_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux0_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX0 Mux", tx_adc_mux0_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux1_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX1 Mux", tx_adc_mux1_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux2_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX2 Mux", tx_adc_mux2_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux3_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX3 Mux", tx_adc_mux3_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux4_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX4 Mux", tx_adc_mux4_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux5_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX5 Mux", tx_adc_mux5_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux6_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX6 Mux", tx_adc_mux6_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux7_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX7 Mux", tx_adc_mux7_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);
अटल स्थिर काष्ठा snd_kcontrol_new tx_adc_mux8_mux =
	SOC_DAPM_ENUM_EXT("ADC MUX8 Mux", tx_adc_mux8_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, wcd934x_dec_क्रमागत_put);

अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx0_mux =
	SOC_DAPM_ENUM("CDC_IF TX0 MUX Mux", cdc_अगर_tx0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx1_mux =
	SOC_DAPM_ENUM("CDC_IF TX1 MUX Mux", cdc_अगर_tx1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx2_mux =
	SOC_DAPM_ENUM("CDC_IF TX2 MUX Mux", cdc_अगर_tx2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx3_mux =
	SOC_DAPM_ENUM("CDC_IF TX3 MUX Mux", cdc_अगर_tx3_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx4_mux =
	SOC_DAPM_ENUM("CDC_IF TX4 MUX Mux", cdc_अगर_tx4_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx5_mux =
	SOC_DAPM_ENUM("CDC_IF TX5 MUX Mux", cdc_अगर_tx5_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx6_mux =
	SOC_DAPM_ENUM("CDC_IF TX6 MUX Mux", cdc_अगर_tx6_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx7_mux =
	SOC_DAPM_ENUM("CDC_IF TX7 MUX Mux", cdc_अगर_tx7_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx8_mux =
	SOC_DAPM_ENUM("CDC_IF TX8 MUX Mux", cdc_अगर_tx8_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx9_mux =
	SOC_DAPM_ENUM("CDC_IF TX9 MUX Mux", cdc_अगर_tx9_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx10_mux =
	SOC_DAPM_ENUM("CDC_IF TX10 MUX Mux", cdc_अगर_tx10_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx11_mux =
	SOC_DAPM_ENUM("CDC_IF TX11 MUX Mux", cdc_अगर_tx11_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx11_inp1_mux =
	SOC_DAPM_ENUM("CDC_IF TX11 INP1 MUX Mux", cdc_अगर_tx11_inp1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx13_mux =
	SOC_DAPM_ENUM("CDC_IF TX13 MUX Mux", cdc_अगर_tx13_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cdc_अगर_tx13_inp1_mux =
	SOC_DAPM_ENUM("CDC_IF TX13 INP1 MUX Mux", cdc_अगर_tx13_inp1_mux_क्रमागत);

अटल पूर्णांक slim_tx_mixer_get(काष्ठा snd_kcontrol *kc,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(dapm->dev);
	काष्ठा soc_mixer_control *mixer =
			(काष्ठा soc_mixer_control *)kc->निजी_value;
	पूर्णांक port_id = mixer->shअगरt;

	ucontrol->value.पूर्णांकeger.value[0] = wcd->tx_port_value[port_id];

	वापस 0;
पूर्ण

अटल पूर्णांक slim_tx_mixer_put(काष्ठा snd_kcontrol *kc,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *widget = snd_soc_dapm_kcontrol_widget(kc);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(widget->dapm->dev);
	काष्ठा snd_soc_dapm_update *update = शून्य;
	काष्ठा soc_mixer_control *mixer =
			(काष्ठा soc_mixer_control *)kc->निजी_value;
	पूर्णांक enable = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक dai_id = widget->shअगरt;
	पूर्णांक port_id = mixer->shअगरt;

	/* only add to the list अगर value not set */
	अगर (enable == wcd->tx_port_value[port_id])
		वापस 0;

	wcd->tx_port_value[port_id] = enable;

	अगर (enable)
		list_add_tail(&wcd->tx_chs[port_id].list,
			      &wcd->dai[dai_id].slim_ch_list);
	अन्यथा
		list_del_init(&wcd->tx_chs[port_id].list);

	snd_soc_dapm_mixer_update_घातer(widget->dapm, kc, enable, update);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1_slim_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD934X_TX0, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD934X_TX1, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD934X_TX2, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD934X_TX3, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD934X_TX4, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD934X_TX5, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD934X_TX6, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD934X_TX7, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD934X_TX8, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX9", SND_SOC_NOPM, WCD934X_TX9, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX10", SND_SOC_NOPM, WCD934X_TX10, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX11", SND_SOC_NOPM, WCD934X_TX11, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX13", SND_SOC_NOPM, WCD934X_TX13, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2_slim_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD934X_TX0, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD934X_TX1, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD934X_TX2, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD934X_TX3, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD934X_TX4, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD934X_TX5, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD934X_TX6, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD934X_TX7, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD934X_TX8, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX9", SND_SOC_NOPM, WCD934X_TX9, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX10", SND_SOC_NOPM, WCD934X_TX10, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX11", SND_SOC_NOPM, WCD934X_TX11, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX13", SND_SOC_NOPM, WCD934X_TX13, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर3_slim_cap_mixer[] = अणु
	SOC_SINGLE_EXT("SLIM TX0", SND_SOC_NOPM, WCD934X_TX0, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX1", SND_SOC_NOPM, WCD934X_TX1, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX2", SND_SOC_NOPM, WCD934X_TX2, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX3", SND_SOC_NOPM, WCD934X_TX3, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX4", SND_SOC_NOPM, WCD934X_TX4, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX5", SND_SOC_NOPM, WCD934X_TX5, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX6", SND_SOC_NOPM, WCD934X_TX6, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX7", SND_SOC_NOPM, WCD934X_TX7, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX8", SND_SOC_NOPM, WCD934X_TX8, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX9", SND_SOC_NOPM, WCD934X_TX9, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX10", SND_SOC_NOPM, WCD934X_TX10, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX11", SND_SOC_NOPM, WCD934X_TX11, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
	SOC_SINGLE_EXT("SLIM TX13", SND_SOC_NOPM, WCD934X_TX13, 1, 0,
		       slim_tx_mixer_get, slim_tx_mixer_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wcd934x_snd_controls[] = अणु
	/* Gain Controls */
	SOC_SINGLE_TLV("EAR PA Volume", WCD934X_ANA_EAR, 4, 4, 1, ear_pa_gain),
	SOC_SINGLE_TLV("HPHL Volume", WCD934X_HPH_L_EN, 0, 24, 1, line_gain),
	SOC_SINGLE_TLV("HPHR Volume", WCD934X_HPH_R_EN, 0, 24, 1, line_gain),
	SOC_SINGLE_TLV("LINEOUT1 Volume", WCD934X_DIFF_LO_LO1_COMPANDER,
		       3, 16, 1, line_gain),
	SOC_SINGLE_TLV("LINEOUT2 Volume", WCD934X_DIFF_LO_LO2_COMPANDER,
		       3, 16, 1, line_gain),

	SOC_SINGLE_TLV("ADC1 Volume", WCD934X_ANA_AMIC1, 0, 20, 0, analog_gain),
	SOC_SINGLE_TLV("ADC2 Volume", WCD934X_ANA_AMIC2, 0, 20, 0, analog_gain),
	SOC_SINGLE_TLV("ADC3 Volume", WCD934X_ANA_AMIC3, 0, 20, 0, analog_gain),
	SOC_SINGLE_TLV("ADC4 Volume", WCD934X_ANA_AMIC4, 0, 20, 0, analog_gain),

	SOC_SINGLE_S8_TLV("RX0 Digital Volume", WCD934X_CDC_RX0_RX_VOL_CTL,
			  -84, 40, digital_gain), /* -84dB min - 40dB max */
	SOC_SINGLE_S8_TLV("RX1 Digital Volume", WCD934X_CDC_RX1_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX2 Digital Volume", WCD934X_CDC_RX2_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX3 Digital Volume", WCD934X_CDC_RX3_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX4 Digital Volume", WCD934X_CDC_RX4_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX7 Digital Volume", WCD934X_CDC_RX7_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX8 Digital Volume", WCD934X_CDC_RX8_RX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX0 Mix Digital Volume",
			  WCD934X_CDC_RX0_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX1 Mix Digital Volume",
			  WCD934X_CDC_RX1_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX2 Mix Digital Volume",
			  WCD934X_CDC_RX2_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX3 Mix Digital Volume",
			  WCD934X_CDC_RX3_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX4 Mix Digital Volume",
			  WCD934X_CDC_RX4_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX7 Mix Digital Volume",
			  WCD934X_CDC_RX7_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("RX8 Mix Digital Volume",
			  WCD934X_CDC_RX8_RX_VOL_MIX_CTL,
			  -84, 40, digital_gain),

	SOC_SINGLE_S8_TLV("DEC0 Volume", WCD934X_CDC_TX0_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC1 Volume", WCD934X_CDC_TX1_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC2 Volume", WCD934X_CDC_TX2_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC3 Volume", WCD934X_CDC_TX3_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC4 Volume", WCD934X_CDC_TX4_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC5 Volume", WCD934X_CDC_TX5_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC6 Volume", WCD934X_CDC_TX6_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC7 Volume", WCD934X_CDC_TX7_TX_VOL_CTL,
			  -84, 40, digital_gain),
	SOC_SINGLE_S8_TLV("DEC8 Volume", WCD934X_CDC_TX8_TX_VOL_CTL,
			  -84, 40, digital_gain),

	SOC_SINGLE_S8_TLV("IIR0 INP0 Volume",
			  WCD934X_CDC_SIDETONE_IIR0_IIR_GAIN_B1_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR0 INP1 Volume",
			  WCD934X_CDC_SIDETONE_IIR0_IIR_GAIN_B2_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR0 INP2 Volume",
			  WCD934X_CDC_SIDETONE_IIR0_IIR_GAIN_B3_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR0 INP3 Volume",
			  WCD934X_CDC_SIDETONE_IIR0_IIR_GAIN_B4_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR1 INP0 Volume",
			  WCD934X_CDC_SIDETONE_IIR1_IIR_GAIN_B1_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR1 INP1 Volume",
			  WCD934X_CDC_SIDETONE_IIR1_IIR_GAIN_B2_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR1 INP2 Volume",
			  WCD934X_CDC_SIDETONE_IIR1_IIR_GAIN_B3_CTL, -84, 40,
			  digital_gain),
	SOC_SINGLE_S8_TLV("IIR1 INP3 Volume",
			  WCD934X_CDC_SIDETONE_IIR1_IIR_GAIN_B4_CTL, -84, 40,
			  digital_gain),

	SOC_ENUM("TX0 HPF cut off", cf_dec0_क्रमागत),
	SOC_ENUM("TX1 HPF cut off", cf_dec1_क्रमागत),
	SOC_ENUM("TX2 HPF cut off", cf_dec2_क्रमागत),
	SOC_ENUM("TX3 HPF cut off", cf_dec3_क्रमागत),
	SOC_ENUM("TX4 HPF cut off", cf_dec4_क्रमागत),
	SOC_ENUM("TX5 HPF cut off", cf_dec5_क्रमागत),
	SOC_ENUM("TX6 HPF cut off", cf_dec6_क्रमागत),
	SOC_ENUM("TX7 HPF cut off", cf_dec7_क्रमागत),
	SOC_ENUM("TX8 HPF cut off", cf_dec8_क्रमागत),

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
	SOC_ENUM("RX INT7_1 HPF cut off", cf_पूर्णांक7_1_क्रमागत),
	SOC_ENUM("RX INT7_2 HPF cut off", cf_पूर्णांक7_2_क्रमागत),
	SOC_ENUM("RX INT8_1 HPF cut off", cf_पूर्णांक8_1_क्रमागत),
	SOC_ENUM("RX INT8_2 HPF cut off", cf_पूर्णांक8_2_क्रमागत),

	SOC_ENUM_EXT("RX HPH Mode", rx_hph_mode_mux_क्रमागत,
		     wcd934x_rx_hph_mode_get, wcd934x_rx_hph_mode_put),

	SOC_SINGLE("IIR1 Band1 Switch", WCD934X_CDC_SIDETONE_IIR0_IIR_CTL,
		   0, 1, 0),
	SOC_SINGLE("IIR1 Band2 Switch", WCD934X_CDC_SIDETONE_IIR0_IIR_CTL,
		   1, 1, 0),
	SOC_SINGLE("IIR1 Band3 Switch", WCD934X_CDC_SIDETONE_IIR0_IIR_CTL,
		   2, 1, 0),
	SOC_SINGLE("IIR1 Band4 Switch", WCD934X_CDC_SIDETONE_IIR0_IIR_CTL,
		   3, 1, 0),
	SOC_SINGLE("IIR1 Band5 Switch", WCD934X_CDC_SIDETONE_IIR0_IIR_CTL,
		   4, 1, 0),
	SOC_SINGLE("IIR2 Band1 Switch", WCD934X_CDC_SIDETONE_IIR1_IIR_CTL,
		   0, 1, 0),
	SOC_SINGLE("IIR2 Band2 Switch", WCD934X_CDC_SIDETONE_IIR1_IIR_CTL,
		   1, 1, 0),
	SOC_SINGLE("IIR2 Band3 Switch", WCD934X_CDC_SIDETONE_IIR1_IIR_CTL,
		   2, 1, 0),
	SOC_SINGLE("IIR2 Band4 Switch", WCD934X_CDC_SIDETONE_IIR1_IIR_CTL,
		   3, 1, 0),
	SOC_SINGLE("IIR2 Band5 Switch", WCD934X_CDC_SIDETONE_IIR1_IIR_CTL,
		   4, 1, 0),
	WCD_IIR_FILTER_CTL("IIR0 Band1", IIR0, BAND1),
	WCD_IIR_FILTER_CTL("IIR0 Band2", IIR0, BAND2),
	WCD_IIR_FILTER_CTL("IIR0 Band3", IIR0, BAND3),
	WCD_IIR_FILTER_CTL("IIR0 Band4", IIR0, BAND4),
	WCD_IIR_FILTER_CTL("IIR0 Band5", IIR0, BAND5),

	WCD_IIR_FILTER_CTL("IIR1 Band1", IIR1, BAND1),
	WCD_IIR_FILTER_CTL("IIR1 Band2", IIR1, BAND2),
	WCD_IIR_FILTER_CTL("IIR1 Band3", IIR1, BAND3),
	WCD_IIR_FILTER_CTL("IIR1 Band4", IIR1, BAND4),
	WCD_IIR_FILTER_CTL("IIR1 Band5", IIR1, BAND5),

	SOC_SINGLE_EXT("COMP1 Switch", SND_SOC_NOPM, COMPANDER_1, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
	SOC_SINGLE_EXT("COMP2 Switch", SND_SOC_NOPM, COMPANDER_2, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
	SOC_SINGLE_EXT("COMP3 Switch", SND_SOC_NOPM, COMPANDER_3, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
	SOC_SINGLE_EXT("COMP4 Switch", SND_SOC_NOPM, COMPANDER_4, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
	SOC_SINGLE_EXT("COMP7 Switch", SND_SOC_NOPM, COMPANDER_7, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
	SOC_SINGLE_EXT("COMP8 Switch", SND_SOC_NOPM, COMPANDER_8, 1, 0,
		       wcd934x_compander_get, wcd934x_compander_set),
पूर्ण;

अटल व्योम wcd934x_codec_enable_पूर्णांक_port(काष्ठा wcd_slim_codec_dai_data *dai,
					  काष्ठा snd_soc_component *component)
अणु
	पूर्णांक port_num = 0;
	अचिन्हित लघु reg = 0;
	अचिन्हित पूर्णांक val = 0;
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(component->dev);
	काष्ठा wcd934x_slim_ch *ch;

	list_क्रम_each_entry(ch, &dai->slim_ch_list, list) अणु
		अगर (ch->port >= WCD934X_RX_START) अणु
			port_num = ch->port - WCD934X_RX_START;
			reg = WCD934X_SLIM_PGD_PORT_INT_EN0 + (port_num / 8);
		पूर्ण अन्यथा अणु
			port_num = ch->port;
			reg = WCD934X_SLIM_PGD_PORT_INT_TX_EN0 + (port_num / 8);
		पूर्ण

		regmap_पढ़ो(wcd->अगर_regmap, reg, &val);
		अगर (!(val & BIT(port_num % 8)))
			regmap_ग_लिखो(wcd->अगर_regmap, reg,
				     val | BIT(port_num % 8));
	पूर्ण
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_slim(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = snd_soc_component_get_drvdata(comp);
	काष्ठा wcd_slim_codec_dai_data *dai = &wcd->dai[w->shअगरt];

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		wcd934x_codec_enable_पूर्णांक_port(dai, comp);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcd934x_codec_hd2_control(काष्ठा snd_soc_component *component,
				      u16 पूर्णांकerp_idx, पूर्णांक event)
अणु
	u16 hd2_scale_reg;
	u16 hd2_enable_reg = 0;

	चयन (पूर्णांकerp_idx) अणु
	हाल INTERP_HPHL:
		hd2_scale_reg = WCD934X_CDC_RX1_RX_PATH_SEC3;
		hd2_enable_reg = WCD934X_CDC_RX1_RX_PATH_CFG0;
		अवरोध;
	हाल INTERP_HPHR:
		hd2_scale_reg = WCD934X_CDC_RX2_RX_PATH_SEC3;
		hd2_enable_reg = WCD934X_CDC_RX2_RX_PATH_CFG0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(component, hd2_scale_reg,
				      WCD934X_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				      WCD934X_CDC_RX_PATH_SEC_HD2_ALPHA_0P3125);
		snd_soc_component_update_bits(component, hd2_enable_reg,
				      WCD934X_CDC_RX_PATH_CFG_HD2_EN_MASK,
				      WCD934X_CDC_RX_PATH_CFG_HD2_ENABLE);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, hd2_enable_reg,
				      WCD934X_CDC_RX_PATH_CFG_HD2_EN_MASK,
				      WCD934X_CDC_RX_PATH_CFG_HD2_DISABLE);
		snd_soc_component_update_bits(component, hd2_scale_reg,
				      WCD934X_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				      WCD934X_CDC_RX_PATH_SEC_HD2_ALPHA_0P0000);
	पूर्ण
पूर्ण

अटल व्योम wcd934x_codec_hphdelay_lutbypass(काष्ठा snd_soc_component *comp,
					     u16 पूर्णांकerp_idx, पूर्णांक event)
अणु
	u8 hph_dly_mask;
	u16 hph_lut_bypass_reg = 0;

	चयन (पूर्णांकerp_idx) अणु
	हाल INTERP_HPHL:
		hph_dly_mask = 1;
		hph_lut_bypass_reg = WCD934X_CDC_TOP_HPHL_COMP_LUT;
		अवरोध;
	हाल INTERP_HPHR:
		hph_dly_mask = 2;
		hph_lut_bypass_reg = WCD934X_CDC_TOP_HPHR_COMP_LUT;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(comp, WCD934X_CDC_CLSH_TEST0,
					      hph_dly_mask, 0x0);
		snd_soc_component_update_bits(comp, hph_lut_bypass_reg,
					      WCD934X_HPH_LUT_BYPASS_MASK,
					      WCD934X_HPH_LUT_BYPASS_ENABLE);
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(comp, WCD934X_CDC_CLSH_TEST0,
					      hph_dly_mask, hph_dly_mask);
		snd_soc_component_update_bits(comp, hph_lut_bypass_reg,
					      WCD934X_HPH_LUT_BYPASS_MASK,
					      WCD934X_HPH_LUT_BYPASS_DISABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक wcd934x_config_compander(काष्ठा snd_soc_component *comp,
				    पूर्णांक पूर्णांकerp_n, पूर्णांक event)
अणु
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक compander;
	u16 comp_ctl0_reg, rx_path_cfg0_reg;

	/* EAR करोes not have compander */
	अगर (!पूर्णांकerp_n)
		वापस 0;

	compander = पूर्णांकerp_n - 1;
	अगर (!wcd->comp_enabled[compander])
		वापस 0;

	comp_ctl0_reg = WCD934X_CDC_COMPANDER1_CTL0 + (compander * 8);
	rx_path_cfg0_reg = WCD934X_CDC_RX1_RX_PATH_CFG0 + (compander * 20);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable Compander Clock */
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_CLK_EN_MASK,
					      WCD934X_COMP_CLK_ENABLE);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_SOFT_RST_MASK,
					      WCD934X_COMP_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_SOFT_RST_MASK,
					      WCD934X_COMP_SOFT_RST_DISABLE);
		snd_soc_component_update_bits(comp, rx_path_cfg0_reg,
					      WCD934X_HPH_CMP_EN_MASK,
					      WCD934X_HPH_CMP_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(comp, rx_path_cfg0_reg,
					      WCD934X_HPH_CMP_EN_MASK,
					      WCD934X_HPH_CMP_DISABLE);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_HALT_MASK,
					      WCD934X_COMP_HALT);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_SOFT_RST_MASK,
					      WCD934X_COMP_SOFT_RST_ENABLE);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_SOFT_RST_MASK,
					      WCD934X_COMP_SOFT_RST_DISABLE);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_CLK_EN_MASK, 0x0);
		snd_soc_component_update_bits(comp, comp_ctl0_reg,
					      WCD934X_COMP_SOFT_RST_MASK, 0x0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_पूर्णांकerp_clk(काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक पूर्णांकerp_idx = w->shअगरt;
	u16 मुख्य_reg = WCD934X_CDC_RX0_RX_PATH_CTL + (पूर्णांकerp_idx * 20);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Clk enable */
		snd_soc_component_update_bits(comp, मुख्य_reg,
					     WCD934X_RX_CLK_EN_MASK,
					     WCD934X_RX_CLK_ENABLE);
		wcd934x_codec_hd2_control(comp, पूर्णांकerp_idx, event);
		wcd934x_codec_hphdelay_lutbypass(comp, पूर्णांकerp_idx, event);
		wcd934x_config_compander(comp, पूर्णांकerp_idx, event);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wcd934x_config_compander(comp, पूर्णांकerp_idx, event);
		wcd934x_codec_hphdelay_lutbypass(comp, पूर्णांकerp_idx, event);
		wcd934x_codec_hd2_control(comp, पूर्णांकerp_idx, event);
		/* Clk Disable */
		snd_soc_component_update_bits(comp, मुख्य_reg,
					     WCD934X_RX_CLK_EN_MASK, 0);
		/* Reset enable and disable */
		snd_soc_component_update_bits(comp, मुख्य_reg,
					      WCD934X_RX_RESET_MASK,
					      WCD934X_RX_RESET_ENABLE);
		snd_soc_component_update_bits(comp, मुख्य_reg,
					      WCD934X_RX_RESET_MASK,
					      WCD934X_RX_RESET_DISABLE);
		/* Reset rate to 48K*/
		snd_soc_component_update_bits(comp, मुख्य_reg,
					      WCD934X_RX_PCM_RATE_MASK,
					      WCD934X_RX_PCM_RATE_F_48K);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_mix_path(काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक offset_val = 0;
	u16 gain_reg, mix_reg;
	पूर्णांक val = 0;

	gain_reg = WCD934X_CDC_RX0_RX_VOL_MIX_CTL +
					(w->shअगरt * WCD934X_RX_PATH_CTL_OFFSET);
	mix_reg = WCD934X_CDC_RX0_RX_PATH_MIX_CTL +
					(w->shअगरt * WCD934X_RX_PATH_CTL_OFFSET);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Clk enable */
		snd_soc_component_update_bits(comp, mix_reg,
					      WCD934X_CDC_RX_MIX_CLK_EN_MASK,
					      WCD934X_CDC_RX_MIX_CLK_ENABLE);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_पढ़ो(comp, gain_reg);
		val += offset_val;
		snd_soc_component_ग_लिखो(comp, gain_reg, val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_set_iir_gain(काष्ठा snd_soc_dapm_widget *w,
				      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक reg = w->reg;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* B1 GAIN */
		snd_soc_component_ग_लिखो(comp, reg,
					snd_soc_component_पढ़ो(comp, reg));
		/* B2 GAIN */
		reg++;
		snd_soc_component_ग_लिखो(comp, reg,
					snd_soc_component_पढ़ो(comp, reg));
		/* B3 GAIN */
		reg++;
		snd_soc_component_ग_लिखो(comp, reg,
					snd_soc_component_पढ़ो(comp, reg));
		/* B4 GAIN */
		reg++;
		snd_soc_component_ग_लिखो(comp, reg,
					snd_soc_component_पढ़ो(comp, reg));
		/* B5 GAIN */
		reg++;
		snd_soc_component_ग_लिखो(comp, reg,
					snd_soc_component_पढ़ो(comp, reg));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_मुख्य_path(काष्ठा snd_soc_dapm_widget *w,
					  काष्ठा snd_kcontrol *kcontrol,
					  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	u16 gain_reg;

	gain_reg = WCD934X_CDC_RX0_RX_VOL_CTL + (w->shअगरt *
						 WCD934X_RX_PATH_CTL_OFFSET);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो(comp, gain_reg,
				snd_soc_component_पढ़ो(comp, gain_reg));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_ear_dac_event(काष्ठा snd_soc_dapm_widget *w,
				       काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Disable AutoChop समयr during घातer up */
		snd_soc_component_update_bits(comp,
				      WCD934X_HPH_NEW_INT_HPH_TIMER1,
				      WCD934X_HPH_AUTOCHOP_TIMER_EN_MASK, 0x0);
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

अटल पूर्णांक wcd934x_codec_hphl_dac_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kcontrol,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;
	u8 dem_inp;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Read DEM INP Select */
		dem_inp = snd_soc_component_पढ़ो(comp,
				   WCD934X_CDC_RX1_RX_PATH_SEC0) & 0x03;

		अगर (((hph_mode == CLS_H_HIFI) || (hph_mode == CLS_H_LOHIFI) ||
		     (hph_mode == CLS_H_LP)) && (dem_inp != 0x01)) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (hph_mode != CLS_H_LP)
			/* Ripple freq control enable */
			snd_soc_component_update_bits(comp,
					WCD934X_SIDO_NEW_VOUT_D_FREQ2,
					WCD934X_SIDO_RIPPLE_FREQ_EN_MASK,
					WCD934X_SIDO_RIPPLE_FREQ_ENABLE);
		/* Disable AutoChop समयr during घातer up */
		snd_soc_component_update_bits(comp,
				      WCD934X_HPH_NEW_INT_HPH_TIMER1,
				      WCD934X_HPH_AUTOCHOP_TIMER_EN_MASK, 0x0);
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_HPHL, hph_mode);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 1000us required as per HW requirement */
		usleep_range(1000, 1100);
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
					WCD_CLSH_STATE_HPHL, hph_mode);
		अगर (hph_mode != CLS_H_LP)
			/* Ripple freq control disable */
			snd_soc_component_update_bits(comp,
					WCD934X_SIDO_NEW_VOUT_D_FREQ2,
					WCD934X_SIDO_RIPPLE_FREQ_EN_MASK, 0x0);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_hphr_dac_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kcontrol,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	पूर्णांक hph_mode = wcd->hph_mode;
	u8 dem_inp;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dem_inp = snd_soc_component_पढ़ो(comp,
					WCD934X_CDC_RX2_RX_PATH_SEC0) & 0x03;
		अगर (((hph_mode == CLS_H_HIFI) || (hph_mode == CLS_H_LOHIFI) ||
		     (hph_mode == CLS_H_LP)) && (dem_inp != 0x01)) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (hph_mode != CLS_H_LP)
			/* Ripple freq control enable */
			snd_soc_component_update_bits(comp,
					WCD934X_SIDO_NEW_VOUT_D_FREQ2,
					WCD934X_SIDO_RIPPLE_FREQ_EN_MASK,
					WCD934X_SIDO_RIPPLE_FREQ_ENABLE);
		/* Disable AutoChop समयr during घातer up */
		snd_soc_component_update_bits(comp,
				      WCD934X_HPH_NEW_INT_HPH_TIMER1,
				      WCD934X_HPH_AUTOCHOP_TIMER_EN_MASK, 0x0);
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_HPHR,
			     hph_mode);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* 1000us required as per HW requirement */
		usleep_range(1000, 1100);

		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
					WCD_CLSH_STATE_HPHR, hph_mode);
		अगर (hph_mode != CLS_H_LP)
			/* Ripple freq control disable */
			snd_soc_component_update_bits(comp,
					WCD934X_SIDO_NEW_VOUT_D_FREQ2,
					WCD934X_SIDO_RIPPLE_FREQ_EN_MASK, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_lineout_dac_event(काष्ठा snd_soc_dapm_widget *w,
					   काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);

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

अटल पूर्णांक wcd934x_codec_enable_hphl_pa(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kcontrol,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * 7ms sleep is required after PA is enabled as per
		 * HW requirement. If compander is disabled, then
		 * 20ms delay is needed.
		 */
		usleep_range(20000, 20100);

		snd_soc_component_update_bits(comp, WCD934X_HPH_L_TEST,
					      WCD934X_HPH_OCP_DET_MASK,
					      WCD934X_HPH_OCP_DET_ENABLE);
		/* Remove Mute on primary path */
		snd_soc_component_update_bits(comp, WCD934X_CDC_RX1_RX_PATH_CTL,
				      WCD934X_RX_PATH_PGA_MUTE_EN_MASK,
				      0);
		/* Enable GM3 boost */
		snd_soc_component_update_bits(comp, WCD934X_HPH_CNP_WG_CTL,
					      WCD934X_HPH_GM3_BOOST_EN_MASK,
					      WCD934X_HPH_GM3_BOOST_ENABLE);
		/* Enable AutoChop समयr at the end of घातer up */
		snd_soc_component_update_bits(comp,
				      WCD934X_HPH_NEW_INT_HPH_TIMER1,
				      WCD934X_HPH_AUTOCHOP_TIMER_EN_MASK,
				      WCD934X_HPH_AUTOCHOP_TIMER_ENABLE);
		/* Remove mix path mute */
		snd_soc_component_update_bits(comp,
				WCD934X_CDC_RX1_RX_PATH_MIX_CTL,
				WCD934X_CDC_RX_PGA_MUTE_EN_MASK, 0x00);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* Enable DSD Mute beक्रमe PA disable */
		snd_soc_component_update_bits(comp, WCD934X_HPH_L_TEST,
					      WCD934X_HPH_OCP_DET_MASK,
					      WCD934X_HPH_OCP_DET_DISABLE);
		snd_soc_component_update_bits(comp, WCD934X_CDC_RX1_RX_PATH_CTL,
					      WCD934X_RX_PATH_PGA_MUTE_EN_MASK,
					      WCD934X_RX_PATH_PGA_MUTE_ENABLE);
		snd_soc_component_update_bits(comp,
					      WCD934X_CDC_RX1_RX_PATH_MIX_CTL,
					      WCD934X_RX_PATH_PGA_MUTE_EN_MASK,
					      WCD934X_RX_PATH_PGA_MUTE_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/*
		 * 5ms sleep is required after PA disable. If compander is
		 * disabled, then 20ms delay is needed after PA disable.
		 */
		usleep_range(20000, 20100);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_hphr_pa(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kcontrol,
					पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * 7ms sleep is required after PA is enabled as per
		 * HW requirement. If compander is disabled, then
		 * 20ms delay is needed.
		 */
		usleep_range(20000, 20100);
		snd_soc_component_update_bits(comp, WCD934X_HPH_R_TEST,
					      WCD934X_HPH_OCP_DET_MASK,
					      WCD934X_HPH_OCP_DET_ENABLE);
		/* Remove mute */
		snd_soc_component_update_bits(comp, WCD934X_CDC_RX2_RX_PATH_CTL,
					      WCD934X_RX_PATH_PGA_MUTE_EN_MASK,
					      0);
		/* Enable GM3 boost */
		snd_soc_component_update_bits(comp, WCD934X_HPH_CNP_WG_CTL,
					      WCD934X_HPH_GM3_BOOST_EN_MASK,
					      WCD934X_HPH_GM3_BOOST_ENABLE);
		/* Enable AutoChop समयr at the end of घातer up */
		snd_soc_component_update_bits(comp,
				      WCD934X_HPH_NEW_INT_HPH_TIMER1,
				      WCD934X_HPH_AUTOCHOP_TIMER_EN_MASK,
				      WCD934X_HPH_AUTOCHOP_TIMER_ENABLE);
		/* Remove mix path mute अगर it is enabled */
		अगर ((snd_soc_component_पढ़ो(comp,
				      WCD934X_CDC_RX2_RX_PATH_MIX_CTL)) & 0x10)
			snd_soc_component_update_bits(comp,
					      WCD934X_CDC_RX2_RX_PATH_MIX_CTL,
					      WCD934X_CDC_RX_PGA_MUTE_EN_MASK,
					      WCD934X_CDC_RX_PGA_MUTE_DISABLE);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(comp, WCD934X_HPH_R_TEST,
					      WCD934X_HPH_OCP_DET_MASK,
					      WCD934X_HPH_OCP_DET_DISABLE);
		snd_soc_component_update_bits(comp, WCD934X_CDC_RX2_RX_PATH_CTL,
					      WCD934X_RX_PATH_PGA_MUTE_EN_MASK,
					      WCD934X_RX_PATH_PGA_MUTE_ENABLE);
		snd_soc_component_update_bits(comp,
					      WCD934X_CDC_RX2_RX_PATH_MIX_CTL,
					      WCD934X_CDC_RX_PGA_MUTE_EN_MASK,
					      WCD934X_CDC_RX_PGA_MUTE_ENABLE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/*
		 * 5ms sleep is required after PA disable. If compander is
		 * disabled, then 20ms delay is needed after PA disable.
		 */
		usleep_range(20000, 20100);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 wcd934x_get_dmic_sample_rate(काष्ठा snd_soc_component *comp,
					अचिन्हित पूर्णांक dmic,
				      काष्ठा wcd934x_codec *wcd)
अणु
	u8 tx_stream_fs;
	u8 adc_mux_index = 0, adc_mux_sel = 0;
	bool dec_found = false;
	u16 adc_mux_ctl_reg, tx_fs_reg;
	u32 dmic_fs;

	जबतक (!dec_found && adc_mux_index < WCD934X_MAX_VALID_ADC_MUX) अणु
		अगर (adc_mux_index < 4) अणु
			adc_mux_ctl_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG0 +
						(adc_mux_index * 2);
		पूर्ण अन्यथा अगर (adc_mux_index < WCD934X_INVALID_ADC_MUX) अणु
			adc_mux_ctl_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
						adc_mux_index - 4;
		पूर्ण अन्यथा अगर (adc_mux_index == WCD934X_INVALID_ADC_MUX) अणु
			++adc_mux_index;
			जारी;
		पूर्ण
		adc_mux_sel = ((snd_soc_component_पढ़ो(comp, adc_mux_ctl_reg)
			       & 0xF8) >> 3) - 1;

		अगर (adc_mux_sel == dmic) अणु
			dec_found = true;
			अवरोध;
		पूर्ण

		++adc_mux_index;
	पूर्ण

	अगर (dec_found && adc_mux_index <= 8) अणु
		tx_fs_reg = WCD934X_CDC_TX0_TX_PATH_CTL + (16 * adc_mux_index);
		tx_stream_fs = snd_soc_component_पढ़ो(comp, tx_fs_reg) & 0x0F;
		अगर (tx_stream_fs <= 4)  अणु
			अगर (wcd->dmic_sample_rate <=
					WCD9XXX_DMIC_SAMPLE_RATE_2P4MHZ)
				dmic_fs = wcd->dmic_sample_rate;
			अन्यथा
				dmic_fs = WCD9XXX_DMIC_SAMPLE_RATE_2P4MHZ;
		पूर्ण अन्यथा
			dmic_fs = WCD9XXX_DMIC_SAMPLE_RATE_4P8MHZ;
	पूर्ण अन्यथा अणु
		dmic_fs = wcd->dmic_sample_rate;
	पूर्ण

	वापस dmic_fs;
पूर्ण

अटल u8 wcd934x_get_dmic_clk_val(काष्ठा snd_soc_component *comp,
				   u32 mclk_rate, u32 dmic_clk_rate)
अणु
	u32 भाग_factor;
	u8 dmic_ctl_val;

	/* Default value to वापस in हाल of error */
	अगर (mclk_rate == WCD934X_MCLK_CLK_9P6MHZ)
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_2;
	अन्यथा
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_3;

	अगर (dmic_clk_rate == 0) अणु
		dev_err(comp->dev,
			"%s: dmic_sample_rate cannot be 0\n",
			__func__);
		जाओ करोne;
	पूर्ण

	भाग_factor = mclk_rate / dmic_clk_rate;
	चयन (भाग_factor) अणु
	हाल 2:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_2;
		अवरोध;
	हाल 3:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_3;
		अवरोध;
	हाल 4:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_4;
		अवरोध;
	हाल 6:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_6;
		अवरोध;
	हाल 8:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_8;
		अवरोध;
	हाल 16:
		dmic_ctl_val = WCD934X_DMIC_CLK_DIV_16;
		अवरोध;
	शेष:
		dev_err(comp->dev,
			"%s: Invalid div_factor %u, clk_rate(%u), dmic_rate(%u)\n",
			__func__, भाग_factor, mclk_rate, dmic_clk_rate);
		अवरोध;
	पूर्ण

करोne:
	वापस dmic_ctl_val;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_dmic(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wcd934x_codec *wcd = dev_get_drvdata(comp->dev);
	u8  dmic_clk_en = 0x01;
	u16 dmic_clk_reg;
	s32 *dmic_clk_cnt;
	u8 dmic_rate_val, dmic_rate_shअगरt = 1;
	अचिन्हित पूर्णांक dmic;
	u32 dmic_sample_rate;
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
		dmic_clk_cnt = &wcd->dmic_0_1_clk_cnt;
		dmic_clk_reg = WCD934X_CPE_SS_DMIC0_CTL;
		अवरोध;
	हाल 2:
	हाल 3:
		dmic_clk_cnt = &wcd->dmic_2_3_clk_cnt;
		dmic_clk_reg = WCD934X_CPE_SS_DMIC1_CTL;
		अवरोध;
	हाल 4:
	हाल 5:
		dmic_clk_cnt = &wcd->dmic_4_5_clk_cnt;
		dmic_clk_reg = WCD934X_CPE_SS_DMIC2_CTL;
		अवरोध;
	शेष:
		dev_err(comp->dev, "%s: Invalid DMIC Selection\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dmic_sample_rate = wcd934x_get_dmic_sample_rate(comp, dmic,
								wcd);
		dmic_rate_val = wcd934x_get_dmic_clk_val(comp, wcd->rate,
							 dmic_sample_rate);
		(*dmic_clk_cnt)++;
		अगर (*dmic_clk_cnt == 1) अणु
			dmic_rate_val = dmic_rate_val << dmic_rate_shअगरt;
			snd_soc_component_update_bits(comp, dmic_clk_reg,
						      WCD934X_DMIC_RATE_MASK,
						      dmic_rate_val);
			snd_soc_component_update_bits(comp, dmic_clk_reg,
						      dmic_clk_en, dmic_clk_en);
		पूर्ण

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		(*dmic_clk_cnt)--;
		अगर (*dmic_clk_cnt == 0)
			snd_soc_component_update_bits(comp, dmic_clk_reg,
						      dmic_clk_en, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_find_amic_input(काष्ठा snd_soc_component *comp,
					 पूर्णांक adc_mux_n)
अणु
	u16 mask, shअगरt, adc_mux_in_reg;
	u16 amic_mux_sel_reg;
	bool is_amic;

	अगर (adc_mux_n < 0 || adc_mux_n > WCD934X_MAX_VALID_ADC_MUX ||
	    adc_mux_n == WCD934X_INVALID_ADC_MUX)
		वापस 0;

	अगर (adc_mux_n < 3) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1 +
				 adc_mux_n;
		mask = 0x03;
		shअगरt = 0;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG0 +
				   2 * adc_mux_n;
	पूर्ण अन्यथा अगर (adc_mux_n < 4) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1;
		mask = 0x03;
		shअगरt = 0;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG0 +
				   2 * adc_mux_n;
	पूर्ण अन्यथा अगर (adc_mux_n < 7) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1 +
				 (adc_mux_n - 4);
		mask = 0x0C;
		shअगरt = 2;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
				   adc_mux_n - 4;
	पूर्ण अन्यथा अगर (adc_mux_n < 8) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1;
		mask = 0x0C;
		shअगरt = 2;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
				   adc_mux_n - 4;
	पूर्ण अन्यथा अगर (adc_mux_n < 12) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1 +
				 ((adc_mux_n == 8) ? (adc_mux_n - 8) :
				  (adc_mux_n - 9));
		mask = 0x30;
		shअगरt = 4;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
				   adc_mux_n - 4;
	पूर्ण अन्यथा अगर (adc_mux_n < 13) अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX3_CFG1;
		mask = 0x30;
		shअगरt = 4;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
				   adc_mux_n - 4;
	पूर्ण अन्यथा अणु
		adc_mux_in_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX0_CFG1;
		mask = 0xC0;
		shअगरt = 6;
		amic_mux_sel_reg = WCD934X_CDC_TX_INP_MUX_ADC_MUX4_CFG0 +
				   adc_mux_n - 4;
	पूर्ण

	is_amic = (((snd_soc_component_पढ़ो(comp, adc_mux_in_reg)
		     & mask) >> shअगरt) == 1);
	अगर (!is_amic)
		वापस 0;

	वापस snd_soc_component_पढ़ो(comp, amic_mux_sel_reg) & 0x07;
पूर्ण

अटल u16 wcd934x_codec_get_amic_pwlvl_reg(काष्ठा snd_soc_component *comp,
					    पूर्णांक amic)
अणु
	u16 pwr_level_reg = 0;

	चयन (amic) अणु
	हाल 1:
	हाल 2:
		pwr_level_reg = WCD934X_ANA_AMIC1;
		अवरोध;

	हाल 3:
	हाल 4:
		pwr_level_reg = WCD934X_ANA_AMIC3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस pwr_level_reg;
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_dec(काष्ठा snd_soc_dapm_widget *w,
				    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
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

	widget_name = kstrndup(w->name, 15, GFP_KERNEL);
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

	tx_vol_ctl_reg = WCD934X_CDC_TX0_TX_PATH_CTL + 16 * decimator;
	hpf_gate_reg = WCD934X_CDC_TX0_TX_PATH_SEC2 + 16 * decimator;
	dec_cfg_reg = WCD934X_CDC_TX0_TX_PATH_CFG0 + 16 * decimator;
	tx_gain_ctl_reg = WCD934X_CDC_TX0_TX_VOL_CTL + 16 * decimator;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		amic_n = wcd934x_codec_find_amic_input(comp, decimator);
		अगर (amic_n)
			pwr_level_reg = wcd934x_codec_get_amic_pwlvl_reg(comp,
								 amic_n);

		अगर (!pwr_level_reg)
			अवरोध;

		चयन ((snd_soc_component_पढ़ो(comp, pwr_level_reg) &
				      WCD934X_AMIC_PWR_LVL_MASK) >>
				      WCD934X_AMIC_PWR_LVL_SHIFT) अणु
		हाल WCD934X_AMIC_PWR_LEVEL_LP:
			snd_soc_component_update_bits(comp, dec_cfg_reg,
					WCD934X_DEC_PWR_LVL_MASK,
					WCD934X_DEC_PWR_LVL_LP);
			अवरोध;
		हाल WCD934X_AMIC_PWR_LEVEL_HP:
			snd_soc_component_update_bits(comp, dec_cfg_reg,
					WCD934X_DEC_PWR_LVL_MASK,
					WCD934X_DEC_PWR_LVL_HP);
			अवरोध;
		हाल WCD934X_AMIC_PWR_LEVEL_DEFAULT:
		हाल WCD934X_AMIC_PWR_LEVEL_HYBRID:
		शेष:
			snd_soc_component_update_bits(comp, dec_cfg_reg,
					WCD934X_DEC_PWR_LVL_MASK,
					WCD934X_DEC_PWR_LVL_DF);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		hpf_coff_freq = (snd_soc_component_पढ़ो(comp, dec_cfg_reg) &
				 TX_HPF_CUT_OFF_FREQ_MASK) >> 5;
		अगर (hpf_coff_freq != CF_MIN_3DB_150HZ) अणु
			snd_soc_component_update_bits(comp, dec_cfg_reg,
						      TX_HPF_CUT_OFF_FREQ_MASK,
						      CF_MIN_3DB_150HZ << 5);
			snd_soc_component_update_bits(comp, hpf_gate_reg,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ_MASK,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ);
			/*
			 * Minimum 1 clk cycle delay is required as per
			 * HW spec.
			 */
			usleep_range(1000, 1010);
			snd_soc_component_update_bits(comp, hpf_gate_reg,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ_MASK,
				      0);
		पूर्ण
		/* apply gain after decimator is enabled */
		snd_soc_component_ग_लिखो(comp, tx_gain_ctl_reg,
					snd_soc_component_पढ़ो(comp,
							 tx_gain_ctl_reg));
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		hpf_coff_freq = (snd_soc_component_पढ़ो(comp, dec_cfg_reg) &
				 TX_HPF_CUT_OFF_FREQ_MASK) >> 5;

		अगर (hpf_coff_freq != CF_MIN_3DB_150HZ) अणु
			snd_soc_component_update_bits(comp, dec_cfg_reg,
						      TX_HPF_CUT_OFF_FREQ_MASK,
						      hpf_coff_freq << 5);
			snd_soc_component_update_bits(comp, hpf_gate_reg,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ_MASK,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ);
				/*
				 * Minimum 1 clk cycle delay is required as per
				 * HW spec.
				 */
			usleep_range(1000, 1010);
			snd_soc_component_update_bits(comp, hpf_gate_reg,
				      WCD934X_HPH_CUTOFF_FREQ_CHANGE_REQ_MASK,
				      0);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(comp, tx_vol_ctl_reg,
					      0x10, 0x00);
		snd_soc_component_update_bits(comp, dec_cfg_reg,
					      WCD934X_DEC_PWR_LVL_MASK,
					      WCD934X_DEC_PWR_LVL_DF);
		अवरोध;
	पूर्ण
out:
	kमुक्त(wname);
	वापस ret;
पूर्ण

अटल व्योम wcd934x_codec_set_tx_hold(काष्ठा snd_soc_component *comp,
				      u16 amic_reg, bool set)
अणु
	u8 mask = 0x20;
	u8 val;

	अगर (amic_reg == WCD934X_ANA_AMIC1 ||
	    amic_reg == WCD934X_ANA_AMIC3)
		mask = 0x40;

	val = set ? mask : 0x00;

	चयन (amic_reg) अणु
	हाल WCD934X_ANA_AMIC1:
	हाल WCD934X_ANA_AMIC2:
		snd_soc_component_update_bits(comp, WCD934X_ANA_AMIC2,
					      mask, val);
		अवरोध;
	हाल WCD934X_ANA_AMIC3:
	हाल WCD934X_ANA_AMIC4:
		snd_soc_component_update_bits(comp, WCD934X_ANA_AMIC4,
					      mask, val);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wcd934x_codec_enable_adc(काष्ठा snd_soc_dapm_widget *w,
				    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wcd934x_codec_set_tx_hold(comp, w->reg, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wcd934x_dapm_widमाला_लो[] = अणु
	/* Analog Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("EAR"),
	SND_SOC_DAPM_OUTPUT("HPHL"),
	SND_SOC_DAPM_OUTPUT("HPHR"),
	SND_SOC_DAPM_OUTPUT("LINEOUT1"),
	SND_SOC_DAPM_OUTPUT("LINEOUT2"),
	SND_SOC_DAPM_OUTPUT("SPK1 OUT"),
	SND_SOC_DAPM_OUTPUT("SPK2 OUT"),
	SND_SOC_DAPM_OUTPUT("ANC EAR"),
	SND_SOC_DAPM_OUTPUT("ANC HPHL"),
	SND_SOC_DAPM_OUTPUT("ANC HPHR"),
	SND_SOC_DAPM_OUTPUT("WDMA3_OUT"),
	SND_SOC_DAPM_OUTPUT("MAD_CPE_OUT1"),
	SND_SOC_DAPM_OUTPUT("MAD_CPE_OUT2"),
	SND_SOC_DAPM_AIF_IN_E("AIF1 PB", "AIF1 Playback", 0, SND_SOC_NOPM,
			      AIF1_PB, 0, wcd934x_codec_enable_slim,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF2 PB", "AIF2 Playback", 0, SND_SOC_NOPM,
			      AIF2_PB, 0, wcd934x_codec_enable_slim,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF3 PB", "AIF3 Playback", 0, SND_SOC_NOPM,
			      AIF3_PB, 0, wcd934x_codec_enable_slim,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("AIF4 PB", "AIF4 Playback", 0, SND_SOC_NOPM,
			      AIF4_PB, 0, wcd934x_codec_enable_slim,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("SLIM RX0 MUX", SND_SOC_NOPM, WCD934X_RX0, 0,
			 &slim_rx_mux[WCD934X_RX0]),
	SND_SOC_DAPM_MUX("SLIM RX1 MUX", SND_SOC_NOPM, WCD934X_RX1, 0,
			 &slim_rx_mux[WCD934X_RX1]),
	SND_SOC_DAPM_MUX("SLIM RX2 MUX", SND_SOC_NOPM, WCD934X_RX2, 0,
			 &slim_rx_mux[WCD934X_RX2]),
	SND_SOC_DAPM_MUX("SLIM RX3 MUX", SND_SOC_NOPM, WCD934X_RX3, 0,
			 &slim_rx_mux[WCD934X_RX3]),
	SND_SOC_DAPM_MUX("SLIM RX4 MUX", SND_SOC_NOPM, WCD934X_RX4, 0,
			 &slim_rx_mux[WCD934X_RX4]),
	SND_SOC_DAPM_MUX("SLIM RX5 MUX", SND_SOC_NOPM, WCD934X_RX5, 0,
			 &slim_rx_mux[WCD934X_RX5]),
	SND_SOC_DAPM_MUX("SLIM RX6 MUX", SND_SOC_NOPM, WCD934X_RX6, 0,
			 &slim_rx_mux[WCD934X_RX6]),
	SND_SOC_DAPM_MUX("SLIM RX7 MUX", SND_SOC_NOPM, WCD934X_RX7, 0,
			 &slim_rx_mux[WCD934X_RX7]),

	SND_SOC_DAPM_MIXER("SLIM RX0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM RX7", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX_E("RX INT0_2 MUX", SND_SOC_NOPM, INTERP_EAR, 0,
			   &rx_पूर्णांक0_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT1_2 MUX", SND_SOC_NOPM, INTERP_HPHL, 0,
			   &rx_पूर्णांक1_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT2_2 MUX", SND_SOC_NOPM, INTERP_HPHR, 0,
			   &rx_पूर्णांक2_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT3_2 MUX", SND_SOC_NOPM, INTERP_LO1, 0,
			   &rx_पूर्णांक3_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT4_2 MUX", SND_SOC_NOPM, INTERP_LO2, 0,
			   &rx_पूर्णांक4_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT7_2 MUX", SND_SOC_NOPM, INTERP_SPKR1, 0,
			   &rx_पूर्णांक7_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT8_2 MUX", SND_SOC_NOPM, INTERP_SPKR2, 0,
			   &rx_पूर्णांक8_2_mux, wcd934x_codec_enable_mix_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

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
	SND_SOC_DAPM_MIXER("RX INT1 SEC MIX", SND_SOC_NOPM, 0, 0,
			   rx_पूर्णांक1_asrc_चयन,
			   ARRAY_SIZE(rx_पूर्णांक1_asrc_चयन)),
	SND_SOC_DAPM_MIXER("RX INT2_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2 SEC MIX", SND_SOC_NOPM, 0, 0,
			   rx_पूर्णांक2_asrc_चयन,
			   ARRAY_SIZE(rx_पूर्णांक2_asrc_चयन)),
	SND_SOC_DAPM_MIXER("RX INT3_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3 SEC MIX", SND_SOC_NOPM, 0, 0,
			   rx_पूर्णांक3_asrc_चयन,
			   ARRAY_SIZE(rx_पूर्णांक3_asrc_चयन)),
	SND_SOC_DAPM_MIXER("RX INT4_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4 SEC MIX", SND_SOC_NOPM, 0, 0,
			   rx_पूर्णांक4_asrc_चयन,
			   ARRAY_SIZE(rx_पूर्णांक4_asrc_चयन)),
	SND_SOC_DAPM_MIXER("RX INT7_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT7 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT8_1 MIX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT8 SEC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT0 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT1 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT1 MIX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT2 MIX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT3 MIX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("RX INT4 MIX3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("RX INT7 MIX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_E("RX INT7 CHAIN", SND_SOC_NOPM, 0, 0,
			     शून्य, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_E("RX INT8 CHAIN", SND_SOC_NOPM, 0, 0,
			     शून्य, 0, शून्य, 0),
	SND_SOC_DAPM_MUX_E("RX INT0 MIX2 INP", WCD934X_CDC_RX0_RX_PATH_CFG0, 4,
			   0,  &rx_पूर्णांक0_mix2_inp_mux, शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT1 MIX2 INP", WCD934X_CDC_RX1_RX_PATH_CFG0, 4,
			   0, &rx_पूर्णांक1_mix2_inp_mux,  शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT2 MIX2 INP", WCD934X_CDC_RX2_RX_PATH_CFG0, 4,
			   0, &rx_पूर्णांक2_mix2_inp_mux, शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT3 MIX2 INP", WCD934X_CDC_RX3_RX_PATH_CFG0, 4,
			   0, &rx_पूर्णांक3_mix2_inp_mux, शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT4 MIX2 INP", WCD934X_CDC_RX4_RX_PATH_CFG0, 4,
			   0, &rx_पूर्णांक4_mix2_inp_mux, शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT7 MIX2 INP", WCD934X_CDC_RX7_RX_PATH_CFG0, 4,
			   0, &rx_पूर्णांक7_mix2_inp_mux, शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("IIR0 INP0 MUX", SND_SOC_NOPM, 0, 0, &iir0_inp0_mux),
	SND_SOC_DAPM_MUX("IIR0 INP1 MUX", SND_SOC_NOPM, 0, 0, &iir0_inp1_mux),
	SND_SOC_DAPM_MUX("IIR0 INP2 MUX", SND_SOC_NOPM, 0, 0, &iir0_inp2_mux),
	SND_SOC_DAPM_MUX("IIR0 INP3 MUX", SND_SOC_NOPM, 0, 0, &iir0_inp3_mux),
	SND_SOC_DAPM_MUX("IIR1 INP0 MUX", SND_SOC_NOPM, 0, 0, &iir1_inp0_mux),
	SND_SOC_DAPM_MUX("IIR1 INP1 MUX", SND_SOC_NOPM, 0, 0, &iir1_inp1_mux),
	SND_SOC_DAPM_MUX("IIR1 INP2 MUX", SND_SOC_NOPM, 0, 0, &iir1_inp2_mux),
	SND_SOC_DAPM_MUX("IIR1 INP3 MUX", SND_SOC_NOPM, 0, 0, &iir1_inp3_mux),

	SND_SOC_DAPM_PGA_E("IIR0", WCD934X_CDC_SIDETONE_IIR0_IIR_GAIN_B1_CTL,
			   0, 0, शून्य, 0, wcd934x_codec_set_iir_gain,
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("IIR1", WCD934X_CDC_SIDETONE_IIR1_IIR_GAIN_B1_CTL,
			   1, 0, शून्य, 0, wcd934x_codec_set_iir_gain,
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MIXER("SRC0", WCD934X_CDC_SIDETONE_SRC0_ST_SRC_PATH_CTL,
			   4, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SRC1", WCD934X_CDC_SIDETONE_SRC1_ST_SRC_PATH_CTL,
			   4, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("RX INT0 DEM MUX", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक0_dem_inp_mux),
	SND_SOC_DAPM_MUX("RX INT1 DEM MUX", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक1_dem_inp_mux),
	SND_SOC_DAPM_MUX("RX INT2 DEM MUX", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक2_dem_inp_mux),

	SND_SOC_DAPM_MUX_E("RX INT0_1 INTERP", SND_SOC_NOPM, INTERP_EAR, 0,
			   &rx_पूर्णांक0_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT1_1 INTERP", SND_SOC_NOPM, INTERP_HPHL, 0,
			   &rx_पूर्णांक1_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT2_1 INTERP", SND_SOC_NOPM, INTERP_HPHR, 0,
			   &rx_पूर्णांक2_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT3_1 INTERP", SND_SOC_NOPM, INTERP_LO1, 0,
			   &rx_पूर्णांक3_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT4_1 INTERP", SND_SOC_NOPM, INTERP_LO2, 0,
			   &rx_पूर्णांक4_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT7_1 INTERP", SND_SOC_NOPM, INTERP_SPKR1, 0,
			   &rx_पूर्णांक7_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("RX INT8_1 INTERP", SND_SOC_NOPM, INTERP_SPKR2, 0,
			   &rx_पूर्णांक8_1_पूर्णांकerp_mux,
			   wcd934x_codec_enable_मुख्य_path,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("RX INT0_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक0_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT1_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक1_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT2_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक2_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT3_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक3_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT4_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक4_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT7_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक7_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_MUX("RX INT8_2 INTERP", SND_SOC_NOPM, 0, 0,
			 &rx_पूर्णांक8_2_पूर्णांकerp_mux),
	SND_SOC_DAPM_DAC_E("RX INT0 DAC", शून्य, SND_SOC_NOPM,
			   0, 0, wcd934x_codec_ear_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT1 DAC", शून्य, WCD934X_ANA_HPH,
			   5, 0, wcd934x_codec_hphl_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT2 DAC", शून्य, WCD934X_ANA_HPH,
			   4, 0, wcd934x_codec_hphr_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT3 DAC", शून्य, SND_SOC_NOPM,
			   0, 0, wcd934x_codec_lineout_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("RX INT4 DAC", शून्य, SND_SOC_NOPM,
			   0, 0, wcd934x_codec_lineout_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("EAR PA", WCD934X_ANA_EAR, 7, 0, शून्य, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_E("HPHL PA", WCD934X_ANA_HPH, 7, 0, शून्य, 0,
			   wcd934x_codec_enable_hphl_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("HPHR PA", WCD934X_ANA_HPH, 6, 0, शून्य, 0,
			   wcd934x_codec_enable_hphr_pa,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("LINEOUT1 PA", WCD934X_ANA_LO_1_2, 7, 0, शून्य, 0,
			   शून्य, 0),
	SND_SOC_DAPM_PGA_E("LINEOUT2 PA", WCD934X_ANA_LO_1_2, 6, 0, शून्य, 0,
			   शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RX_BIAS", WCD934X_ANA_RX_SUPPLIES, 0, 0, शून्य,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("SBOOST0", WCD934X_CDC_RX7_RX_PATH_CFG1,
			 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SBOOST0_CLK", WCD934X_CDC_BOOST0_BOOST_PATH_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SBOOST1", WCD934X_CDC_RX8_RX_PATH_CFG1,
			 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SBOOST1_CLK", WCD934X_CDC_BOOST1_BOOST_PATH_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("INT0_CLK", SND_SOC_NOPM, INTERP_EAR, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT1_CLK", SND_SOC_NOPM, INTERP_HPHL, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT2_CLK", SND_SOC_NOPM, INTERP_HPHR, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT3_CLK", SND_SOC_NOPM, INTERP_LO1, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT4_CLK", SND_SOC_NOPM, INTERP_LO2, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT7_CLK", SND_SOC_NOPM, INTERP_SPKR1, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("INT8_CLK", SND_SOC_NOPM, INTERP_SPKR2, 0,
			    wcd934x_codec_enable_पूर्णांकerp_clk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("DSMDEM0_CLK", WCD934X_CDC_RX0_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM1_CLK", WCD934X_CDC_RX1_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM2_CLK", WCD934X_CDC_RX2_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM3_CLK", WCD934X_CDC_RX3_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM4_CLK", WCD934X_CDC_RX4_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM7_CLK", WCD934X_CDC_RX7_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSMDEM8_CLK", WCD934X_CDC_RX8_RX_PATH_DSMDEM_CTL,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MCLK", SND_SOC_NOPM, 0, 0,
			    wcd934x_codec_enable_mclk,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* TX */
	SND_SOC_DAPM_INPUT("AMIC1"),
	SND_SOC_DAPM_INPUT("AMIC2"),
	SND_SOC_DAPM_INPUT("AMIC3"),
	SND_SOC_DAPM_INPUT("AMIC4"),
	SND_SOC_DAPM_INPUT("AMIC5"),
	SND_SOC_DAPM_INPUT("DMIC0 Pin"),
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("DMIC3 Pin"),
	SND_SOC_DAPM_INPUT("DMIC4 Pin"),
	SND_SOC_DAPM_INPUT("DMIC5 Pin"),

	SND_SOC_DAPM_AIF_OUT_E("AIF1 CAP", "AIF1 Capture", 0, SND_SOC_NOPM,
			       AIF1_CAP, 0, wcd934x_codec_enable_slim,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT_E("AIF2 CAP", "AIF2 Capture", 0, SND_SOC_NOPM,
			       AIF2_CAP, 0, wcd934x_codec_enable_slim,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT_E("AIF3 CAP", "AIF3 Capture", 0, SND_SOC_NOPM,
			       AIF3_CAP, 0, wcd934x_codec_enable_slim,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("SLIM TX0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX7", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX8", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX9", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX10", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX11", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SLIM TX13", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Mic Inमाला_दो */
	SND_SOC_DAPM_ADC_E("DMIC0", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC1", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC2", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC3", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC4", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("DMIC5", शून्य, SND_SOC_NOPM, 0, 0,
			   wcd934x_codec_enable_dmic,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("DMIC MUX0", SND_SOC_NOPM, 0, 0, &tx_dmic_mux0),
	SND_SOC_DAPM_MUX("DMIC MUX1", SND_SOC_NOPM, 0, 0, &tx_dmic_mux1),
	SND_SOC_DAPM_MUX("DMIC MUX2", SND_SOC_NOPM, 0, 0, &tx_dmic_mux2),
	SND_SOC_DAPM_MUX("DMIC MUX3", SND_SOC_NOPM, 0, 0, &tx_dmic_mux3),
	SND_SOC_DAPM_MUX("DMIC MUX4", SND_SOC_NOPM, 0, 0, &tx_dmic_mux4),
	SND_SOC_DAPM_MUX("DMIC MUX5", SND_SOC_NOPM, 0, 0, &tx_dmic_mux5),
	SND_SOC_DAPM_MUX("DMIC MUX6", SND_SOC_NOPM, 0, 0, &tx_dmic_mux6),
	SND_SOC_DAPM_MUX("DMIC MUX7", SND_SOC_NOPM, 0, 0, &tx_dmic_mux7),
	SND_SOC_DAPM_MUX("DMIC MUX8", SND_SOC_NOPM, 0, 0, &tx_dmic_mux8),
	SND_SOC_DAPM_MUX("AMIC MUX0", SND_SOC_NOPM, 0, 0, &tx_amic_mux0),
	SND_SOC_DAPM_MUX("AMIC MUX1", SND_SOC_NOPM, 0, 0, &tx_amic_mux1),
	SND_SOC_DAPM_MUX("AMIC MUX2", SND_SOC_NOPM, 0, 0, &tx_amic_mux2),
	SND_SOC_DAPM_MUX("AMIC MUX3", SND_SOC_NOPM, 0, 0, &tx_amic_mux3),
	SND_SOC_DAPM_MUX("AMIC MUX4", SND_SOC_NOPM, 0, 0, &tx_amic_mux4),
	SND_SOC_DAPM_MUX("AMIC MUX5", SND_SOC_NOPM, 0, 0, &tx_amic_mux5),
	SND_SOC_DAPM_MUX("AMIC MUX6", SND_SOC_NOPM, 0, 0, &tx_amic_mux6),
	SND_SOC_DAPM_MUX("AMIC MUX7", SND_SOC_NOPM, 0, 0, &tx_amic_mux7),
	SND_SOC_DAPM_MUX("AMIC MUX8", SND_SOC_NOPM, 0, 0, &tx_amic_mux8),
	SND_SOC_DAPM_MUX_E("ADC MUX0", WCD934X_CDC_TX0_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux0_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX1", WCD934X_CDC_TX1_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux1_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX2", WCD934X_CDC_TX2_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux2_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX3", WCD934X_CDC_TX3_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux3_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX4", WCD934X_CDC_TX4_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux4_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX5", WCD934X_CDC_TX5_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux5_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX6", WCD934X_CDC_TX6_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux6_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX7", WCD934X_CDC_TX7_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux7_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX_E("ADC MUX8", WCD934X_CDC_TX8_TX_PATH_CTL, 5, 0,
			   &tx_adc_mux8_mux, wcd934x_codec_enable_dec,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("ADC1", शून्य, WCD934X_ANA_AMIC1, 7, 0,
			   wcd934x_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC2", शून्य, WCD934X_ANA_AMIC2, 7, 0,
			   wcd934x_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC3", शून्य, WCD934X_ANA_AMIC3, 7, 0,
			   wcd934x_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_ADC_E("ADC4", शून्य, WCD934X_ANA_AMIC4, 7, 0,
			   wcd934x_codec_enable_adc, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("MIC BIAS1", WCD934X_ANA_MICB1, 6, 0, शून्य,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS2", WCD934X_ANA_MICB2, 6, 0, शून्य,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS3", WCD934X_ANA_MICB3, 6, 0, शून्य,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("MIC BIAS4", WCD934X_ANA_MICB4, 6, 0, शून्य,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("AMIC4_5 SEL", SND_SOC_NOPM, 0, 0, &tx_amic4_5),
	SND_SOC_DAPM_MUX("CDC_IF TX0 MUX", SND_SOC_NOPM, WCD934X_TX0, 0,
			 &cdc_अगर_tx0_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX1 MUX", SND_SOC_NOPM, WCD934X_TX1, 0,
			 &cdc_अगर_tx1_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX2 MUX", SND_SOC_NOPM, WCD934X_TX2, 0,
			 &cdc_अगर_tx2_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX3 MUX", SND_SOC_NOPM, WCD934X_TX3, 0,
			 &cdc_अगर_tx3_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX4 MUX", SND_SOC_NOPM, WCD934X_TX4, 0,
			 &cdc_अगर_tx4_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX5 MUX", SND_SOC_NOPM, WCD934X_TX5, 0,
			 &cdc_अगर_tx5_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX6 MUX", SND_SOC_NOPM, WCD934X_TX6, 0,
			 &cdc_अगर_tx6_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX7 MUX", SND_SOC_NOPM, WCD934X_TX7, 0,
			 &cdc_अगर_tx7_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX8 MUX", SND_SOC_NOPM, WCD934X_TX8, 0,
			 &cdc_अगर_tx8_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX9 MUX", SND_SOC_NOPM, WCD934X_TX9, 0,
			 &cdc_अगर_tx9_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX10 MUX", SND_SOC_NOPM, WCD934X_TX10, 0,
			 &cdc_अगर_tx10_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX11 MUX", SND_SOC_NOPM, WCD934X_TX11, 0,
			 &cdc_अगर_tx11_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX11 INP1 MUX", SND_SOC_NOPM, WCD934X_TX11, 0,
			 &cdc_अगर_tx11_inp1_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX13 MUX", SND_SOC_NOPM, WCD934X_TX13, 0,
			 &cdc_अगर_tx13_mux),
	SND_SOC_DAPM_MUX("CDC_IF TX13 INP1 MUX", SND_SOC_NOPM, WCD934X_TX13, 0,
			 &cdc_अगर_tx13_inp1_mux),
	SND_SOC_DAPM_MIXER("AIF1_CAP Mixer", SND_SOC_NOPM, AIF1_CAP, 0,
			   aअगर1_slim_cap_mixer,
			   ARRAY_SIZE(aअगर1_slim_cap_mixer)),
	SND_SOC_DAPM_MIXER("AIF2_CAP Mixer", SND_SOC_NOPM, AIF2_CAP, 0,
			   aअगर2_slim_cap_mixer,
			   ARRAY_SIZE(aअगर2_slim_cap_mixer)),
	SND_SOC_DAPM_MIXER("AIF3_CAP Mixer", SND_SOC_NOPM, AIF3_CAP, 0,
			   aअगर3_slim_cap_mixer,
			   ARRAY_SIZE(aअगर3_slim_cap_mixer)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wcd934x_audio_map[] = अणु
	/* RX0-RX7 */
	WCD934X_SLIM_RX_AIF_PATH(0),
	WCD934X_SLIM_RX_AIF_PATH(1),
	WCD934X_SLIM_RX_AIF_PATH(2),
	WCD934X_SLIM_RX_AIF_PATH(3),
	WCD934X_SLIM_RX_AIF_PATH(4),
	WCD934X_SLIM_RX_AIF_PATH(5),
	WCD934X_SLIM_RX_AIF_PATH(6),
	WCD934X_SLIM_RX_AIF_PATH(7),

	/* RX0 Ear out */
	WCD934X_INTERPOLATOR_PATH(0),
	WCD934X_INTERPOLATOR_MIX2(0),
	अणु"RX INT0 DEM MUX", "CLSH_DSM_OUT", "RX INT0 MIX2"पूर्ण,
	अणु"RX INT0 DAC", शून्य, "RX INT0 DEM MUX"पूर्ण,
	अणु"RX INT0 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"EAR PA", शून्य, "RX INT0 DAC"पूर्ण,
	अणु"EAR", शून्य, "EAR PA"पूर्ण,

	/* RX1 Headphone left */
	WCD934X_INTERPOLATOR_PATH(1),
	WCD934X_INTERPOLATOR_MIX2(1),
	अणु"RX INT1 MIX3", शून्य, "RX INT1 MIX2"पूर्ण,
	अणु"RX INT1 DEM MUX", "CLSH_DSM_OUT", "RX INT1 MIX3"पूर्ण,
	अणु"RX INT1 DAC", शून्य, "RX INT1 DEM MUX"पूर्ण,
	अणु"RX INT1 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHL PA", शून्य, "RX INT1 DAC"पूर्ण,
	अणु"HPHL", शून्य, "HPHL PA"पूर्ण,

	/* RX2 Headphone right */
	WCD934X_INTERPOLATOR_PATH(2),
	WCD934X_INTERPOLATOR_MIX2(2),
	अणु"RX INT2 MIX3", शून्य, "RX INT2 MIX2"पूर्ण,
	अणु"RX INT2 DEM MUX", "CLSH_DSM_OUT", "RX INT2 MIX3"पूर्ण,
	अणु"RX INT2 DAC", शून्य, "RX INT2 DEM MUX"पूर्ण,
	अणु"RX INT2 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"HPHR PA", शून्य, "RX INT2 DAC"पूर्ण,
	अणु"HPHR", शून्य, "HPHR PA"पूर्ण,

	/* RX3 HIFi LineOut1 */
	WCD934X_INTERPOLATOR_PATH(3),
	WCD934X_INTERPOLATOR_MIX2(3),
	अणु"RX INT3 MIX3", शून्य, "RX INT3 MIX2"पूर्ण,
	अणु"RX INT3 DAC", शून्य, "RX INT3 MIX3"पूर्ण,
	अणु"RX INT3 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT1 PA", शून्य, "RX INT3 DAC"पूर्ण,
	अणु"LINEOUT1", शून्य, "LINEOUT1 PA"पूर्ण,

	/* RX4 HIFi LineOut2 */
	WCD934X_INTERPOLATOR_PATH(4),
	WCD934X_INTERPOLATOR_MIX2(4),
	अणु"RX INT4 MIX3", शून्य, "RX INT4 MIX2"पूर्ण,
	अणु"RX INT4 DAC", शून्य, "RX INT4 MIX3"पूर्ण,
	अणु"RX INT4 DAC", शून्य, "RX_BIAS"पूर्ण,
	अणु"LINEOUT2 PA", शून्य, "RX INT4 DAC"पूर्ण,
	अणु"LINEOUT2", शून्य, "LINEOUT2 PA"पूर्ण,

	/* RX7 Speaker Left Out PA */
	WCD934X_INTERPOLATOR_PATH(7),
	WCD934X_INTERPOLATOR_MIX2(7),
	अणु"RX INT7 CHAIN", शून्य, "RX INT7 MIX2"पूर्ण,
	अणु"RX INT7 CHAIN", शून्य, "RX_BIAS"पूर्ण,
	अणु"RX INT7 CHAIN", शून्य, "SBOOST0"पूर्ण,
	अणु"RX INT7 CHAIN", शून्य, "SBOOST0_CLK"पूर्ण,
	अणु"SPK1 OUT", शून्य, "RX INT7 CHAIN"पूर्ण,

	/* RX8 Speaker Right Out PA */
	WCD934X_INTERPOLATOR_PATH(8),
	अणु"RX INT8 CHAIN", शून्य, "RX INT8 SEC MIX"पूर्ण,
	अणु"RX INT8 CHAIN", शून्य, "RX_BIAS"पूर्ण,
	अणु"RX INT8 CHAIN", शून्य, "SBOOST1"पूर्ण,
	अणु"RX INT8 CHAIN", शून्य, "SBOOST1_CLK"पूर्ण,
	अणु"SPK2 OUT", शून्य, "RX INT8 CHAIN"पूर्ण,

	/* Tx */
	अणु"AIF1 CAP", शून्य, "AIF1_CAP Mixer"पूर्ण,
	अणु"AIF2 CAP", शून्य, "AIF2_CAP Mixer"पूर्ण,
	अणु"AIF3 CAP", शून्य, "AIF3_CAP Mixer"पूर्ण,

	WCD934X_SLIM_TX_AIF_PATH(0),
	WCD934X_SLIM_TX_AIF_PATH(1),
	WCD934X_SLIM_TX_AIF_PATH(2),
	WCD934X_SLIM_TX_AIF_PATH(3),
	WCD934X_SLIM_TX_AIF_PATH(4),
	WCD934X_SLIM_TX_AIF_PATH(5),
	WCD934X_SLIM_TX_AIF_PATH(6),
	WCD934X_SLIM_TX_AIF_PATH(7),
	WCD934X_SLIM_TX_AIF_PATH(8),

	WCD934X_ADC_MUX(0),
	WCD934X_ADC_MUX(1),
	WCD934X_ADC_MUX(2),
	WCD934X_ADC_MUX(3),
	WCD934X_ADC_MUX(4),
	WCD934X_ADC_MUX(5),
	WCD934X_ADC_MUX(6),
	WCD934X_ADC_MUX(7),
	WCD934X_ADC_MUX(8),

	अणु"CDC_IF TX0 MUX", "DEC0", "ADC MUX0"पूर्ण,
	अणु"CDC_IF TX1 MUX", "DEC1", "ADC MUX1"पूर्ण,
	अणु"CDC_IF TX2 MUX", "DEC2", "ADC MUX2"पूर्ण,
	अणु"CDC_IF TX3 MUX", "DEC3", "ADC MUX3"पूर्ण,
	अणु"CDC_IF TX4 MUX", "DEC4", "ADC MUX4"पूर्ण,
	अणु"CDC_IF TX5 MUX", "DEC5", "ADC MUX5"पूर्ण,
	अणु"CDC_IF TX6 MUX", "DEC6", "ADC MUX6"पूर्ण,
	अणु"CDC_IF TX7 MUX", "DEC7", "ADC MUX7"पूर्ण,
	अणु"CDC_IF TX8 MUX", "DEC8", "ADC MUX8"पूर्ण,

	अणु"AMIC4_5 SEL", "AMIC4", "AMIC4"पूर्ण,
	अणु"AMIC4_5 SEL", "AMIC5", "AMIC5"पूर्ण,

	अणु "DMIC0", शून्य, "DMIC0 Pin" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC1 Pin" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC2 Pin" पूर्ण,
	अणु "DMIC3", शून्य, "DMIC3 Pin" पूर्ण,
	अणु "DMIC4", शून्य, "DMIC4 Pin" पूर्ण,
	अणु "DMIC5", शून्य, "DMIC5 Pin" पूर्ण,

	अणु"ADC1", शून्य, "AMIC1"पूर्ण,
	अणु"ADC2", शून्य, "AMIC2"पूर्ण,
	अणु"ADC3", शून्य, "AMIC3"पूर्ण,
	अणु"ADC4", शून्य, "AMIC4_5 SEL"पूर्ण,

	WCD934X_IIR_INP_MUX(0),
	WCD934X_IIR_INP_MUX(1),

	अणु"SRC0", शून्य, "IIR0"पूर्ण,
	अणु"SRC1", शून्य, "IIR1"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver wcd934x_component_drv = अणु
	.probe = wcd934x_comp_probe,
	.हटाओ = wcd934x_comp_हटाओ,
	.set_sysclk = wcd934x_comp_set_sysclk,
	.controls = wcd934x_snd_controls,
	.num_controls = ARRAY_SIZE(wcd934x_snd_controls),
	.dapm_widमाला_लो = wcd934x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wcd934x_dapm_widमाला_लो),
	.dapm_routes = wcd934x_audio_map,
	.num_dapm_routes = ARRAY_SIZE(wcd934x_audio_map),
पूर्ण;

अटल पूर्णांक wcd934x_codec_parse_data(काष्ठा wcd934x_codec *wcd)
अणु
	काष्ठा device *dev = &wcd->sdev->dev;
	काष्ठा device_node *अगरc_dev_np;

	अगरc_dev_np = of_parse_phandle(dev->of_node, "slim-ifc-dev", 0);
	अगर (!अगरc_dev_np) अणु
		dev_err(dev, "No Interface device found\n");
		वापस -EINVAL;
	पूर्ण

	wcd->sidev = of_slim_get_device(wcd->sdev->ctrl, अगरc_dev_np);
	अगर (!wcd->sidev) अणु
		dev_err(dev, "Unable to get SLIM Interface device\n");
		वापस -EINVAL;
	पूर्ण

	slim_get_logical_addr(wcd->sidev);
	wcd->अगर_regmap = regmap_init_slimbus(wcd->sidev,
				  &wcd934x_अगरc_regmap_config);
	अगर (IS_ERR(wcd->अगर_regmap)) अणु
		dev_err(dev, "Failed to allocate ifc register map\n");
		वापस PTR_ERR(wcd->अगर_regmap);
	पूर्ण

	of_property_पढ़ो_u32(dev->parent->of_node, "qcom,dmic-sample-rate",
			     &wcd->dmic_sample_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wcd934x_ddata *data = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wcd934x_codec *wcd;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, irq;

	wcd = devm_kzalloc(&pdev->dev, माप(*wcd), GFP_KERNEL);
	अगर (!wcd)
		वापस -ENOMEM;

	wcd->dev = dev;
	wcd->regmap = data->regmap;
	wcd->extclk = data->extclk;
	wcd->sdev = to_slim_device(data->dev);
	mutex_init(&wcd->sysclk_mutex);

	ret = wcd934x_codec_parse_data(wcd);
	अगर (ret) अणु
		dev_err(wcd->dev, "Failed to get SLIM IRQ\n");
		वापस ret;
	पूर्ण

	/* set शेष rate 9P6MHz */
	regmap_update_bits(wcd->regmap, WCD934X_CODEC_RPM_CLK_MCLK_CFG,
			   WCD934X_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
			   WCD934X_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ);
	स_नकल(wcd->rx_chs, wcd934x_rx_chs, माप(wcd934x_rx_chs));
	स_नकल(wcd->tx_chs, wcd934x_tx_chs, माप(wcd934x_tx_chs));

	irq = regmap_irq_get_virq(data->irq_data, WCD934X_IRQ_SLIMBUS);
	अगर (irq < 0) अणु
		dev_err(wcd->dev, "Failed to get SLIM IRQ\n");
		वापस irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					wcd934x_slim_irq_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"slim", wcd);
	अगर (ret) अणु
		dev_err(dev, "Failed to request slimbus irq\n");
		वापस ret;
	पूर्ण

	wcd934x_रेजिस्टर_mclk_output(wcd);
	platक्रमm_set_drvdata(pdev, wcd);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &wcd934x_component_drv,
					       wcd934x_slim_dais,
					       ARRAY_SIZE(wcd934x_slim_dais));
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id wcd934x_driver_id[] = अणु
	अणु
		.name = "wcd934x-codec",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, wcd934x_driver_id);

अटल काष्ठा platक्रमm_driver wcd934x_codec_driver = अणु
	.probe	= &wcd934x_codec_probe,
	.id_table = wcd934x_driver_id,
	.driver = अणु
		.name	= "wcd934x-codec",
	पूर्ण
पूर्ण;

MODULE_ALIAS("platform:wcd934x-codec");
module_platक्रमm_driver(wcd934x_codec_driver);
MODULE_DESCRIPTION("WCD934x codec driver");
MODULE_LICENSE("GPL v2");
