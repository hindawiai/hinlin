<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5677.c  --  RT5677 ALSA SoC audio codec driver
 *
 * Copyright 2013 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5677.h"
#समावेश "rt5677-spi.h"

#घोषणा RT5677_DEVICE_ID 0x6327

/* Register controlling boot vector */
#घोषणा RT5677_DSP_BOOT_VECTOR		0x1801f090
#घोषणा RT5677_MODEL_ADDR		0x5FFC9800

#घोषणा RT5677_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5677_PR_SPACING 0x100

#घोषणा RT5677_PR_BASE (RT5677_PR_RANGE_BASE + (0 * RT5677_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5677_ranges[] = अणु
	अणु
		.name = "PR",
		.range_min = RT5677_PR_BASE,
		.range_max = RT5677_PR_BASE + 0xfd,
		.selector_reg = RT5677_PRIV_INDEX,
		.selector_mask = 0xff,
		.selector_shअगरt = 0x0,
		.winकरोw_start = RT5677_PRIV_DATA,
		.winकरोw_len = 0x1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणुRT5677_ASRC_12,	0x0018पूर्ण,
	अणुRT5677_PR_BASE + 0x3d,	0x364dपूर्ण,
	अणुRT5677_PR_BASE + 0x17,	0x4fc0पूर्ण,
	अणुRT5677_PR_BASE + 0x13,	0x0312पूर्ण,
	अणुRT5677_PR_BASE + 0x1e,	0x0000पूर्ण,
	अणुRT5677_PR_BASE + 0x12,	0x0eaaपूर्ण,
	अणुRT5677_PR_BASE + 0x14,	0x018aपूर्ण,
	अणुRT5677_PR_BASE + 0x15,	0x0490पूर्ण,
	अणुRT5677_PR_BASE + 0x38,	0x0f71पूर्ण,
	अणुRT5677_PR_BASE + 0x39,	0x0f71पूर्ण,
पूर्ण;
#घोषणा RT5677_INIT_REG_LEN ARRAY_SIZE(init_list)

अटल स्थिर काष्ठा reg_शेष rt5677_reg[] = अणु
	अणुRT5677_RESET			, 0x0000पूर्ण,
	अणुRT5677_LOUT1			, 0xa800पूर्ण,
	अणुRT5677_IN1			, 0x0000पूर्ण,
	अणुRT5677_MICBIAS			, 0x0000पूर्ण,
	अणुRT5677_SLIMBUS_PARAM		, 0x0000पूर्ण,
	अणुRT5677_SLIMBUS_RX		, 0x0000पूर्ण,
	अणुRT5677_SLIMBUS_CTRL		, 0x0000पूर्ण,
	अणुRT5677_SIDETONE_CTRL		, 0x000bपूर्ण,
	अणुRT5677_ANA_DAC1_2_3_SRC	, 0x0000पूर्ण,
	अणुRT5677_IF_DSP_DAC3_4_MIXER	, 0x1111पूर्ण,
	अणुRT5677_DAC4_DIG_VOL		, 0xafafपूर्ण,
	अणुRT5677_DAC3_DIG_VOL		, 0xafafपूर्ण,
	अणुRT5677_DAC1_DIG_VOL		, 0xafafपूर्ण,
	अणुRT5677_DAC2_DIG_VOL		, 0xafafपूर्ण,
	अणुRT5677_IF_DSP_DAC2_MIXER	, 0x0011पूर्ण,
	अणुRT5677_STO1_ADC_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_MONO_ADC_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_STO1_2_ADC_BST		, 0x0000पूर्ण,
	अणुRT5677_STO2_ADC_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_ADC_BST_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_STO3_4_ADC_BST		, 0x0000पूर्ण,
	अणुRT5677_STO3_ADC_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_STO4_ADC_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_STO4_ADC_MIXER		, 0xd4c0पूर्ण,
	अणुRT5677_STO3_ADC_MIXER		, 0xd4c0पूर्ण,
	अणुRT5677_STO2_ADC_MIXER		, 0xd4c0पूर्ण,
	अणुRT5677_STO1_ADC_MIXER		, 0xd4c0पूर्ण,
	अणुRT5677_MONO_ADC_MIXER		, 0xd4d1पूर्ण,
	अणुRT5677_ADC_IF_DSP_DAC1_MIXER	, 0x8080पूर्ण,
	अणुRT5677_STO1_DAC_MIXER		, 0xaaaaपूर्ण,
	अणुRT5677_MONO_DAC_MIXER		, 0xaaaaपूर्ण,
	अणुRT5677_DD1_MIXER		, 0xaaaaपूर्ण,
	अणुRT5677_DD2_MIXER		, 0xaaaaपूर्ण,
	अणुRT5677_IF3_DATA		, 0x0000पूर्ण,
	अणुRT5677_IF4_DATA		, 0x0000पूर्ण,
	अणुRT5677_PDM_OUT_CTRL		, 0x8888पूर्ण,
	अणुRT5677_PDM_DATA_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_PDM_DATA_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_PDM1_DATA_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_PDM1_DATA_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_PDM1_DATA_CTRL4		, 0x0000पूर्ण,
	अणुRT5677_PDM2_DATA_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_PDM2_DATA_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_PDM2_DATA_CTRL4		, 0x0000पूर्ण,
	अणुRT5677_TDM1_CTRL1		, 0x0300पूर्ण,
	अणुRT5677_TDM1_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_TDM1_CTRL3		, 0x4000पूर्ण,
	अणुRT5677_TDM1_CTRL4		, 0x0123पूर्ण,
	अणुRT5677_TDM1_CTRL5		, 0x4567पूर्ण,
	अणुRT5677_TDM2_CTRL1		, 0x0300पूर्ण,
	अणुRT5677_TDM2_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_TDM2_CTRL3		, 0x4000पूर्ण,
	अणुRT5677_TDM2_CTRL4		, 0x0123पूर्ण,
	अणुRT5677_TDM2_CTRL5		, 0x4567पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL1	, 0x0001पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL4	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL5	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL6	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL7	, 0x0000पूर्ण,
	अणुRT5677_I2C_MASTER_CTRL8	, 0x0000पूर्ण,
	अणुRT5677_DMIC_CTRL1		, 0x1505पूर्ण,
	अणुRT5677_DMIC_CTRL2		, 0x0055पूर्ण,
	अणुRT5677_HAP_GENE_CTRL1		, 0x0111पूर्ण,
	अणुRT5677_HAP_GENE_CTRL2		, 0x0064पूर्ण,
	अणुRT5677_HAP_GENE_CTRL3		, 0xef0eपूर्ण,
	अणुRT5677_HAP_GENE_CTRL4		, 0xf0f0पूर्ण,
	अणुRT5677_HAP_GENE_CTRL5		, 0xef0eपूर्ण,
	अणुRT5677_HAP_GENE_CTRL6		, 0xf0f0पूर्ण,
	अणुRT5677_HAP_GENE_CTRL7		, 0xef0eपूर्ण,
	अणुRT5677_HAP_GENE_CTRL8		, 0xf0f0पूर्ण,
	अणुRT5677_HAP_GENE_CTRL9		, 0xf000पूर्ण,
	अणुRT5677_HAP_GENE_CTRL10		, 0x0000पूर्ण,
	अणुRT5677_PWR_DIG1		, 0x0000पूर्ण,
	अणुRT5677_PWR_DIG2		, 0x0000पूर्ण,
	अणुRT5677_PWR_ANLG1		, 0x0055पूर्ण,
	अणुRT5677_PWR_ANLG2		, 0x0000पूर्ण,
	अणुRT5677_PWR_DSP1		, 0x0001पूर्ण,
	अणुRT5677_PWR_DSP_ST		, 0x0000पूर्ण,
	अणुRT5677_PWR_DSP2		, 0x0000पूर्ण,
	अणुRT5677_ADC_DAC_HPF_CTRL1	, 0x0e00पूर्ण,
	अणुRT5677_PRIV_INDEX		, 0x0000पूर्ण,
	अणुRT5677_PRIV_DATA		, 0x0000पूर्ण,
	अणुRT5677_I2S4_SDP		, 0x8000पूर्ण,
	अणुRT5677_I2S1_SDP		, 0x8000पूर्ण,
	अणुRT5677_I2S2_SDP		, 0x8000पूर्ण,
	अणुRT5677_I2S3_SDP		, 0x8000पूर्ण,
	अणुRT5677_CLK_TREE_CTRL1		, 0x1111पूर्ण,
	अणुRT5677_CLK_TREE_CTRL2		, 0x1111पूर्ण,
	अणुRT5677_CLK_TREE_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_PLL1_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_PLL1_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_PLL2_CTRL1		, 0x0c60पूर्ण,
	अणुRT5677_PLL2_CTRL2		, 0x2000पूर्ण,
	अणुRT5677_GLB_CLK1		, 0x0000पूर्ण,
	अणुRT5677_GLB_CLK2		, 0x0000पूर्ण,
	अणुRT5677_ASRC_1			, 0x0000पूर्ण,
	अणुRT5677_ASRC_2			, 0x0000पूर्ण,
	अणुRT5677_ASRC_3			, 0x0000पूर्ण,
	अणुRT5677_ASRC_4			, 0x0000पूर्ण,
	अणुRT5677_ASRC_5			, 0x0000पूर्ण,
	अणुRT5677_ASRC_6			, 0x0000पूर्ण,
	अणुRT5677_ASRC_7			, 0x0000पूर्ण,
	अणुRT5677_ASRC_8			, 0x0000पूर्ण,
	अणुRT5677_ASRC_9			, 0x0000पूर्ण,
	अणुRT5677_ASRC_10			, 0x0000पूर्ण,
	अणुRT5677_ASRC_11			, 0x0000पूर्ण,
	अणुRT5677_ASRC_12			, 0x0018पूर्ण,
	अणुRT5677_ASRC_13			, 0x0000पूर्ण,
	अणुRT5677_ASRC_14			, 0x0000पूर्ण,
	अणुRT5677_ASRC_15			, 0x0000पूर्ण,
	अणुRT5677_ASRC_16			, 0x0000पूर्ण,
	अणुRT5677_ASRC_17			, 0x0000पूर्ण,
	अणुRT5677_ASRC_18			, 0x0000पूर्ण,
	अणुRT5677_ASRC_19			, 0x0000पूर्ण,
	अणुRT5677_ASRC_20			, 0x0000पूर्ण,
	अणुRT5677_ASRC_21			, 0x000cपूर्ण,
	अणुRT5677_ASRC_22			, 0x0000पूर्ण,
	अणुRT5677_ASRC_23			, 0x0000पूर्ण,
	अणुRT5677_VAD_CTRL1		, 0x2184पूर्ण,
	अणुRT5677_VAD_CTRL2		, 0x010aपूर्ण,
	अणुRT5677_VAD_CTRL3		, 0x0aeaपूर्ण,
	अणुRT5677_VAD_CTRL4		, 0x000cपूर्ण,
	अणुRT5677_VAD_CTRL5		, 0x0000पूर्ण,
	अणुRT5677_DSP_INB_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_DSP_INB_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_DSP_IN_OUTB_CTRL	, 0x0000पूर्ण,
	अणुRT5677_DSP_OUTB0_1_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_DSP_OUTB2_3_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_DSP_OUTB4_5_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_DSP_OUTB6_7_DIG_VOL	, 0x2f2fपूर्ण,
	अणुRT5677_ADC_EQ_CTRL1		, 0x6000पूर्ण,
	अणुRT5677_ADC_EQ_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_EQ_CTRL1		, 0xc000पूर्ण,
	अणुRT5677_EQ_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_EQ_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_SOFT_VOL_ZERO_CROSS1	, 0x0009पूर्ण,
	अणुRT5677_JD_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_JD_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_JD_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_IRQ_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_IRQ_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_GPIO_ST			, 0x0000पूर्ण,
	अणुRT5677_GPIO_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_GPIO_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_GPIO_CTRL3		, 0x0000पूर्ण,
	अणुRT5677_STO1_ADC_HI_FILTER1	, 0xb320पूर्ण,
	अणुRT5677_STO1_ADC_HI_FILTER2	, 0x0000पूर्ण,
	अणुRT5677_MONO_ADC_HI_FILTER1	, 0xb300पूर्ण,
	अणुRT5677_MONO_ADC_HI_FILTER2	, 0x0000पूर्ण,
	अणुRT5677_STO2_ADC_HI_FILTER1	, 0xb300पूर्ण,
	अणुRT5677_STO2_ADC_HI_FILTER2	, 0x0000पूर्ण,
	अणुRT5677_STO3_ADC_HI_FILTER1	, 0xb300पूर्ण,
	अणुRT5677_STO3_ADC_HI_FILTER2	, 0x0000पूर्ण,
	अणुRT5677_STO4_ADC_HI_FILTER1	, 0xb300पूर्ण,
	अणुRT5677_STO4_ADC_HI_FILTER2	, 0x0000पूर्ण,
	अणुRT5677_MB_DRC_CTRL1		, 0x0f20पूर्ण,
	अणुRT5677_DRC1_CTRL1		, 0x001fपूर्ण,
	अणुRT5677_DRC1_CTRL2		, 0x020cपूर्ण,
	अणुRT5677_DRC1_CTRL3		, 0x1f00पूर्ण,
	अणुRT5677_DRC1_CTRL4		, 0x0000पूर्ण,
	अणुRT5677_DRC1_CTRL5		, 0x0000पूर्ण,
	अणुRT5677_DRC1_CTRL6		, 0x0029पूर्ण,
	अणुRT5677_DRC2_CTRL1		, 0x001fपूर्ण,
	अणुRT5677_DRC2_CTRL2		, 0x020cपूर्ण,
	अणुRT5677_DRC2_CTRL3		, 0x1f00पूर्ण,
	अणुRT5677_DRC2_CTRL4		, 0x0000पूर्ण,
	अणुRT5677_DRC2_CTRL5		, 0x0000पूर्ण,
	अणुRT5677_DRC2_CTRL6		, 0x0029पूर्ण,
	अणुRT5677_DRC1_HL_CTRL1		, 0x8000पूर्ण,
	अणुRT5677_DRC1_HL_CTRL2		, 0x0200पूर्ण,
	अणुRT5677_DRC2_HL_CTRL1		, 0x8000पूर्ण,
	अणुRT5677_DRC2_HL_CTRL2		, 0x0200पूर्ण,
	अणुRT5677_DSP_INB1_SRC_CTRL1	, 0x5800पूर्ण,
	अणुRT5677_DSP_INB1_SRC_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB1_SRC_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB1_SRC_CTRL4	, 0x0800पूर्ण,
	अणुRT5677_DSP_INB2_SRC_CTRL1	, 0x5800पूर्ण,
	अणुRT5677_DSP_INB2_SRC_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB2_SRC_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB2_SRC_CTRL4	, 0x0800पूर्ण,
	अणुRT5677_DSP_INB3_SRC_CTRL1	, 0x5800पूर्ण,
	अणुRT5677_DSP_INB3_SRC_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB3_SRC_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_DSP_INB3_SRC_CTRL4	, 0x0800पूर्ण,
	अणुRT5677_DSP_OUTB1_SRC_CTRL1	, 0x5800पूर्ण,
	अणुRT5677_DSP_OUTB1_SRC_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_DSP_OUTB1_SRC_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_DSP_OUTB1_SRC_CTRL4	, 0x0800पूर्ण,
	अणुRT5677_DSP_OUTB2_SRC_CTRL1	, 0x5800पूर्ण,
	अणुRT5677_DSP_OUTB2_SRC_CTRL2	, 0x0000पूर्ण,
	अणुRT5677_DSP_OUTB2_SRC_CTRL3	, 0x0000पूर्ण,
	अणुRT5677_DSP_OUTB2_SRC_CTRL4	, 0x0800पूर्ण,
	अणुRT5677_DSP_OUTB_0123_MIXER_CTRL, 0xfefeपूर्ण,
	अणुRT5677_DSP_OUTB_45_MIXER_CTRL	, 0xfefeपूर्ण,
	अणुRT5677_DSP_OUTB_67_MIXER_CTRL	, 0xfefeपूर्ण,
	अणुRT5677_DIG_MISC		, 0x0000पूर्ण,
	अणुRT5677_GEN_CTRL1		, 0x0000पूर्ण,
	अणुRT5677_GEN_CTRL2		, 0x0000पूर्ण,
	अणुRT5677_VENDOR_ID		, 0x0000पूर्ण,
	अणुRT5677_VENDOR_ID1		, 0x10ecपूर्ण,
	अणुRT5677_VENDOR_ID2		, 0x6327पूर्ण,
पूर्ण;

अटल bool rt5677_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5677_ranges); i++) अणु
		अगर (reg >= rt5677_ranges[i].range_min &&
			reg <= rt5677_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5677_RESET:
	हाल RT5677_SLIMBUS_PARAM:
	हाल RT5677_PDM_DATA_CTRL1:
	हाल RT5677_PDM_DATA_CTRL2:
	हाल RT5677_PDM1_DATA_CTRL4:
	हाल RT5677_PDM2_DATA_CTRL4:
	हाल RT5677_I2C_MASTER_CTRL1:
	हाल RT5677_I2C_MASTER_CTRL7:
	हाल RT5677_I2C_MASTER_CTRL8:
	हाल RT5677_HAP_GENE_CTRL2:
	हाल RT5677_PWR_ANLG2: /* Modअगरied by DSP firmware */
	हाल RT5677_PWR_DSP_ST:
	हाल RT5677_PRIV_DATA:
	हाल RT5677_ASRC_22:
	हाल RT5677_ASRC_23:
	हाल RT5677_VAD_CTRL5:
	हाल RT5677_ADC_EQ_CTRL1:
	हाल RT5677_EQ_CTRL1:
	हाल RT5677_IRQ_CTRL1:
	हाल RT5677_IRQ_CTRL2:
	हाल RT5677_GPIO_ST:
	हाल RT5677_GPIO_CTRL1: /* Modअगरied by DSP firmware */
	हाल RT5677_GPIO_CTRL2: /* Modअगरied by DSP firmware */
	हाल RT5677_DSP_INB1_SRC_CTRL4:
	हाल RT5677_DSP_INB2_SRC_CTRL4:
	हाल RT5677_DSP_INB3_SRC_CTRL4:
	हाल RT5677_DSP_OUTB1_SRC_CTRL4:
	हाल RT5677_DSP_OUTB2_SRC_CTRL4:
	हाल RT5677_VENDOR_ID:
	हाल RT5677_VENDOR_ID1:
	हाल RT5677_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5677_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5677_ranges); i++) अणु
		अगर (reg >= rt5677_ranges[i].range_min &&
			reg <= rt5677_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5677_RESET:
	हाल RT5677_LOUT1:
	हाल RT5677_IN1:
	हाल RT5677_MICBIAS:
	हाल RT5677_SLIMBUS_PARAM:
	हाल RT5677_SLIMBUS_RX:
	हाल RT5677_SLIMBUS_CTRL:
	हाल RT5677_SIDETONE_CTRL:
	हाल RT5677_ANA_DAC1_2_3_SRC:
	हाल RT5677_IF_DSP_DAC3_4_MIXER:
	हाल RT5677_DAC4_DIG_VOL:
	हाल RT5677_DAC3_DIG_VOL:
	हाल RT5677_DAC1_DIG_VOL:
	हाल RT5677_DAC2_DIG_VOL:
	हाल RT5677_IF_DSP_DAC2_MIXER:
	हाल RT5677_STO1_ADC_DIG_VOL:
	हाल RT5677_MONO_ADC_DIG_VOL:
	हाल RT5677_STO1_2_ADC_BST:
	हाल RT5677_STO2_ADC_DIG_VOL:
	हाल RT5677_ADC_BST_CTRL2:
	हाल RT5677_STO3_4_ADC_BST:
	हाल RT5677_STO3_ADC_DIG_VOL:
	हाल RT5677_STO4_ADC_DIG_VOL:
	हाल RT5677_STO4_ADC_MIXER:
	हाल RT5677_STO3_ADC_MIXER:
	हाल RT5677_STO2_ADC_MIXER:
	हाल RT5677_STO1_ADC_MIXER:
	हाल RT5677_MONO_ADC_MIXER:
	हाल RT5677_ADC_IF_DSP_DAC1_MIXER:
	हाल RT5677_STO1_DAC_MIXER:
	हाल RT5677_MONO_DAC_MIXER:
	हाल RT5677_DD1_MIXER:
	हाल RT5677_DD2_MIXER:
	हाल RT5677_IF3_DATA:
	हाल RT5677_IF4_DATA:
	हाल RT5677_PDM_OUT_CTRL:
	हाल RT5677_PDM_DATA_CTRL1:
	हाल RT5677_PDM_DATA_CTRL2:
	हाल RT5677_PDM1_DATA_CTRL2:
	हाल RT5677_PDM1_DATA_CTRL3:
	हाल RT5677_PDM1_DATA_CTRL4:
	हाल RT5677_PDM2_DATA_CTRL2:
	हाल RT5677_PDM2_DATA_CTRL3:
	हाल RT5677_PDM2_DATA_CTRL4:
	हाल RT5677_TDM1_CTRL1:
	हाल RT5677_TDM1_CTRL2:
	हाल RT5677_TDM1_CTRL3:
	हाल RT5677_TDM1_CTRL4:
	हाल RT5677_TDM1_CTRL5:
	हाल RT5677_TDM2_CTRL1:
	हाल RT5677_TDM2_CTRL2:
	हाल RT5677_TDM2_CTRL3:
	हाल RT5677_TDM2_CTRL4:
	हाल RT5677_TDM2_CTRL5:
	हाल RT5677_I2C_MASTER_CTRL1:
	हाल RT5677_I2C_MASTER_CTRL2:
	हाल RT5677_I2C_MASTER_CTRL3:
	हाल RT5677_I2C_MASTER_CTRL4:
	हाल RT5677_I2C_MASTER_CTRL5:
	हाल RT5677_I2C_MASTER_CTRL6:
	हाल RT5677_I2C_MASTER_CTRL7:
	हाल RT5677_I2C_MASTER_CTRL8:
	हाल RT5677_DMIC_CTRL1:
	हाल RT5677_DMIC_CTRL2:
	हाल RT5677_HAP_GENE_CTRL1:
	हाल RT5677_HAP_GENE_CTRL2:
	हाल RT5677_HAP_GENE_CTRL3:
	हाल RT5677_HAP_GENE_CTRL4:
	हाल RT5677_HAP_GENE_CTRL5:
	हाल RT5677_HAP_GENE_CTRL6:
	हाल RT5677_HAP_GENE_CTRL7:
	हाल RT5677_HAP_GENE_CTRL8:
	हाल RT5677_HAP_GENE_CTRL9:
	हाल RT5677_HAP_GENE_CTRL10:
	हाल RT5677_PWR_DIG1:
	हाल RT5677_PWR_DIG2:
	हाल RT5677_PWR_ANLG1:
	हाल RT5677_PWR_ANLG2:
	हाल RT5677_PWR_DSP1:
	हाल RT5677_PWR_DSP_ST:
	हाल RT5677_PWR_DSP2:
	हाल RT5677_ADC_DAC_HPF_CTRL1:
	हाल RT5677_PRIV_INDEX:
	हाल RT5677_PRIV_DATA:
	हाल RT5677_I2S4_SDP:
	हाल RT5677_I2S1_SDP:
	हाल RT5677_I2S2_SDP:
	हाल RT5677_I2S3_SDP:
	हाल RT5677_CLK_TREE_CTRL1:
	हाल RT5677_CLK_TREE_CTRL2:
	हाल RT5677_CLK_TREE_CTRL3:
	हाल RT5677_PLL1_CTRL1:
	हाल RT5677_PLL1_CTRL2:
	हाल RT5677_PLL2_CTRL1:
	हाल RT5677_PLL2_CTRL2:
	हाल RT5677_GLB_CLK1:
	हाल RT5677_GLB_CLK2:
	हाल RT5677_ASRC_1:
	हाल RT5677_ASRC_2:
	हाल RT5677_ASRC_3:
	हाल RT5677_ASRC_4:
	हाल RT5677_ASRC_5:
	हाल RT5677_ASRC_6:
	हाल RT5677_ASRC_7:
	हाल RT5677_ASRC_8:
	हाल RT5677_ASRC_9:
	हाल RT5677_ASRC_10:
	हाल RT5677_ASRC_11:
	हाल RT5677_ASRC_12:
	हाल RT5677_ASRC_13:
	हाल RT5677_ASRC_14:
	हाल RT5677_ASRC_15:
	हाल RT5677_ASRC_16:
	हाल RT5677_ASRC_17:
	हाल RT5677_ASRC_18:
	हाल RT5677_ASRC_19:
	हाल RT5677_ASRC_20:
	हाल RT5677_ASRC_21:
	हाल RT5677_ASRC_22:
	हाल RT5677_ASRC_23:
	हाल RT5677_VAD_CTRL1:
	हाल RT5677_VAD_CTRL2:
	हाल RT5677_VAD_CTRL3:
	हाल RT5677_VAD_CTRL4:
	हाल RT5677_VAD_CTRL5:
	हाल RT5677_DSP_INB_CTRL1:
	हाल RT5677_DSP_INB_CTRL2:
	हाल RT5677_DSP_IN_OUTB_CTRL:
	हाल RT5677_DSP_OUTB0_1_DIG_VOL:
	हाल RT5677_DSP_OUTB2_3_DIG_VOL:
	हाल RT5677_DSP_OUTB4_5_DIG_VOL:
	हाल RT5677_DSP_OUTB6_7_DIG_VOL:
	हाल RT5677_ADC_EQ_CTRL1:
	हाल RT5677_ADC_EQ_CTRL2:
	हाल RT5677_EQ_CTRL1:
	हाल RT5677_EQ_CTRL2:
	हाल RT5677_EQ_CTRL3:
	हाल RT5677_SOFT_VOL_ZERO_CROSS1:
	हाल RT5677_JD_CTRL1:
	हाल RT5677_JD_CTRL2:
	हाल RT5677_JD_CTRL3:
	हाल RT5677_IRQ_CTRL1:
	हाल RT5677_IRQ_CTRL2:
	हाल RT5677_GPIO_ST:
	हाल RT5677_GPIO_CTRL1:
	हाल RT5677_GPIO_CTRL2:
	हाल RT5677_GPIO_CTRL3:
	हाल RT5677_STO1_ADC_HI_FILTER1:
	हाल RT5677_STO1_ADC_HI_FILTER2:
	हाल RT5677_MONO_ADC_HI_FILTER1:
	हाल RT5677_MONO_ADC_HI_FILTER2:
	हाल RT5677_STO2_ADC_HI_FILTER1:
	हाल RT5677_STO2_ADC_HI_FILTER2:
	हाल RT5677_STO3_ADC_HI_FILTER1:
	हाल RT5677_STO3_ADC_HI_FILTER2:
	हाल RT5677_STO4_ADC_HI_FILTER1:
	हाल RT5677_STO4_ADC_HI_FILTER2:
	हाल RT5677_MB_DRC_CTRL1:
	हाल RT5677_DRC1_CTRL1:
	हाल RT5677_DRC1_CTRL2:
	हाल RT5677_DRC1_CTRL3:
	हाल RT5677_DRC1_CTRL4:
	हाल RT5677_DRC1_CTRL5:
	हाल RT5677_DRC1_CTRL6:
	हाल RT5677_DRC2_CTRL1:
	हाल RT5677_DRC2_CTRL2:
	हाल RT5677_DRC2_CTRL3:
	हाल RT5677_DRC2_CTRL4:
	हाल RT5677_DRC2_CTRL5:
	हाल RT5677_DRC2_CTRL6:
	हाल RT5677_DRC1_HL_CTRL1:
	हाल RT5677_DRC1_HL_CTRL2:
	हाल RT5677_DRC2_HL_CTRL1:
	हाल RT5677_DRC2_HL_CTRL2:
	हाल RT5677_DSP_INB1_SRC_CTRL1:
	हाल RT5677_DSP_INB1_SRC_CTRL2:
	हाल RT5677_DSP_INB1_SRC_CTRL3:
	हाल RT5677_DSP_INB1_SRC_CTRL4:
	हाल RT5677_DSP_INB2_SRC_CTRL1:
	हाल RT5677_DSP_INB2_SRC_CTRL2:
	हाल RT5677_DSP_INB2_SRC_CTRL3:
	हाल RT5677_DSP_INB2_SRC_CTRL4:
	हाल RT5677_DSP_INB3_SRC_CTRL1:
	हाल RT5677_DSP_INB3_SRC_CTRL2:
	हाल RT5677_DSP_INB3_SRC_CTRL3:
	हाल RT5677_DSP_INB3_SRC_CTRL4:
	हाल RT5677_DSP_OUTB1_SRC_CTRL1:
	हाल RT5677_DSP_OUTB1_SRC_CTRL2:
	हाल RT5677_DSP_OUTB1_SRC_CTRL3:
	हाल RT5677_DSP_OUTB1_SRC_CTRL4:
	हाल RT5677_DSP_OUTB2_SRC_CTRL1:
	हाल RT5677_DSP_OUTB2_SRC_CTRL2:
	हाल RT5677_DSP_OUTB2_SRC_CTRL3:
	हाल RT5677_DSP_OUTB2_SRC_CTRL4:
	हाल RT5677_DSP_OUTB_0123_MIXER_CTRL:
	हाल RT5677_DSP_OUTB_45_MIXER_CTRL:
	हाल RT5677_DSP_OUTB_67_MIXER_CTRL:
	हाल RT5677_DIG_MISC:
	हाल RT5677_GEN_CTRL1:
	हाल RT5677_GEN_CTRL2:
	हाल RT5677_VENDOR_ID:
	हाल RT5677_VENDOR_ID1:
	हाल RT5677_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * rt5677_dsp_mode_i2c_ग_लिखो_addr - Write value to address on DSP mode.
 * @rt5677: Private Data.
 * @addr: Address index.
 * @value: Address data.
 * @opcode: opcode value
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक rt5677_dsp_mode_i2c_ग_लिखो_addr(काष्ठा rt5677_priv *rt5677,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक opcode)
अणु
	काष्ठा snd_soc_component *component = rt5677->component;
	पूर्णांक ret;

	mutex_lock(&rt5677->dsp_cmd_lock);

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_MSB,
		addr >> 16);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set addr msb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_LSB,
		addr & 0xffff);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set addr lsb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_MSB,
		value >> 16);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set data msb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_LSB,
		value & 0xffff);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set data lsb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_OP_CODE,
		opcode);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set op code value: %d\n", ret);
		जाओ err;
	पूर्ण

err:
	mutex_unlock(&rt5677->dsp_cmd_lock);

	वापस ret;
पूर्ण

/**
 * rt5677_dsp_mode_i2c_पढ़ो_addr - Read value from address on DSP mode.
 * @rt5677: Private Data.
 * @addr: Address index.
 * @value: Address data.
 *
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक rt5677_dsp_mode_i2c_पढ़ो_addr(
	काष्ठा rt5677_priv *rt5677, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा snd_soc_component *component = rt5677->component;
	पूर्णांक ret;
	अचिन्हित पूर्णांक msb, lsb;

	mutex_lock(&rt5677->dsp_cmd_lock);

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_MSB,
		addr >> 16);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set addr msb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_LSB,
		addr & 0xffff);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set addr lsb value: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(rt5677->regmap_physical, RT5677_DSP_I2C_OP_CODE,
		0x0002);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set op code value: %d\n", ret);
		जाओ err;
	पूर्ण

	regmap_पढ़ो(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_MSB, &msb);
	regmap_पढ़ो(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_LSB, &lsb);
	*value = (msb << 16) | lsb;

err:
	mutex_unlock(&rt5677->dsp_cmd_lock);

	वापस ret;
पूर्ण

/**
 * rt5677_dsp_mode_i2c_ग_लिखो - Write रेजिस्टर on DSP mode.
 * @rt5677: Private Data.
 * @reg: Register index.
 * @value: Register data.
 *
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक rt5677_dsp_mode_i2c_ग_लिखो(काष्ठा rt5677_priv *rt5677,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	वापस rt5677_dsp_mode_i2c_ग_लिखो_addr(rt5677, 0x18020000 + reg * 2,
		value, 0x0001);
पूर्ण

/**
 * rt5677_dsp_mode_i2c_पढ़ो - Read रेजिस्टर on DSP mode.
 * @rt5677: Private Data
 * @reg: Register index.
 * @value: Register data.
 *
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक rt5677_dsp_mode_i2c_पढ़ो(
	काष्ठा rt5677_priv *rt5677, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret = rt5677_dsp_mode_i2c_पढ़ो_addr(rt5677, 0x18020000 + reg * 2,
		value);

	*value &= 0xffff;

	वापस ret;
पूर्ण

अटल व्योम rt5677_set_dsp_mode(काष्ठा rt5677_priv *rt5677, bool on)
अणु
	अगर (on) अणु
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP, RT5677_PWR_DSP);
		rt5677->is_dsp_mode = true;
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP, 0x0);
		rt5677->is_dsp_mode = false;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक rt5677_set_vad_source(काष्ठा rt5677_priv *rt5677)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(rt5677->component);
	/* Force dapm to sync beक्रमe we enable the
	 * DSP to prevent ग_लिखो corruption
	 */
	snd_soc_dapm_sync(dapm);

	/* DMIC1 घातer = enabled
	 * DMIC CLK = 256 * fs / 12
	 */
	regmap_update_bits(rt5677->regmap, RT5677_DMIC_CTRL1,
		RT5677_DMIC_CLK_MASK, 5 << RT5677_DMIC_CLK_SFT);

	/* I2S pre भागide 2 = /6 (clk_sys2) */
	regmap_update_bits(rt5677->regmap, RT5677_CLK_TREE_CTRL1,
		RT5677_I2S_PD2_MASK, RT5677_I2S_PD2_6);

	/* DSP Clock = MCLK1 (bypassed PLL2) */
	regmap_ग_लिखो(rt5677->regmap, RT5677_GLB_CLK2,
		RT5677_DSP_CLK_SRC_BYPASS);

	/* SAD Threshold1 */
	regmap_ग_लिखो(rt5677->regmap, RT5677_VAD_CTRL2, 0x013f);
	/* SAD Threshold2 */
	regmap_ग_लिखो(rt5677->regmap, RT5677_VAD_CTRL3, 0x0ae5);
	/* SAD Sample Rate Converter = Up 6 (8K to 48K)
	 * SAD Output Sample Rate = Same as I2S
	 * SAD Threshold3
	 */
	regmap_update_bits(rt5677->regmap, RT5677_VAD_CTRL4,
		RT5677_VAD_OUT_SRC_RATE_MASK | RT5677_VAD_OUT_SRC_MASK |
		RT5677_VAD_LV_DIFF_MASK, 0x7f << RT5677_VAD_LV_DIFF_SFT);
	/* Minimum frame level within a pre-determined duration = 32 frames
	 * Bypass ADPCM Encoder/Decoder = Bypass ADPCM
	 * Automatic Push Data to SAD Buffer Once SAD Flag is triggered = enable
	 * SAD Buffer Over-Writing = enable
	 * SAD Buffer Pop Mode Control = disable
	 * SAD Buffer Push Mode Control = enable
	 * SAD Detector Control = enable
	 * SAD Function Control = enable
	 * SAD Function Reset = normal
	 */
	regmap_ग_लिखो(rt5677->regmap, RT5677_VAD_CTRL1,
		RT5677_VAD_FUNC_RESET | RT5677_VAD_FUNC_ENABLE |
		RT5677_VAD_DET_ENABLE | RT5677_VAD_BUF_PUSH |
		RT5677_VAD_BUF_OW | RT5677_VAD_FG2ENC |
		RT5677_VAD_ADPCM_BYPASS | 1 << RT5677_VAD_MIN_DUR_SFT);

	/* VAD/SAD is not routed to the IRQ output (i.e. MX-BE[14] = 0), but it
	 * is routed to DSP_IRQ_0, so DSP firmware may use it to sleep and save
	 * घातer. See ALC5677 datasheet section 9.17 "GPIO, Interrupt and Jack
	 * Detection" क्रम more info.
	 */

	/* Private रेजिस्टर, no करोc */
	regmap_update_bits(rt5677->regmap, RT5677_PR_BASE + RT5677_BIAS_CUR4,
		0x0f00, 0x0100);

	/* LDO2 output = 1.2V
	 * LDO1 output = 1.2V (LDO_IN = 1.8V)
	 */
	regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG1,
		RT5677_LDO1_SEL_MASK | RT5677_LDO2_SEL_MASK,
		5 << RT5677_LDO1_SEL_SFT | 5 << RT5677_LDO2_SEL_SFT);

	/* Codec core घातer =  घातer on
	 * LDO1 घातer = घातer on
	 */
	regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
		RT5677_PWR_CORE | RT5677_PWR_LDO1,
		RT5677_PWR_CORE | RT5677_PWR_LDO1);

	/* Isolation क्रम DCVDD4 = normal (set during probe)
	 * Isolation क्रम DCVDD2 = normal (set during probe)
	 * Isolation क्रम DSP = normal
	 * Isolation क्रम Band 0~7 = disable
	 * Isolation क्रम InBound 4~10 and OutBound 4~10 = disable
	 */
	regmap_ग_लिखो(rt5677->regmap, RT5677_PWR_DSP2,
		RT5677_PWR_CORE_ISO | RT5677_PWR_DSP_ISO |
		RT5677_PWR_SR7_ISO | RT5677_PWR_SR6_ISO |
		RT5677_PWR_SR5_ISO | RT5677_PWR_SR4_ISO |
		RT5677_PWR_SR3_ISO | RT5677_PWR_SR2_ISO |
		RT5677_PWR_SR1_ISO | RT5677_PWR_SR0_ISO |
		RT5677_PWR_MLT_ISO);

	/* System Band 0~7 = घातer on
	 * InBound 4~10 and OutBound 4~10 = घातer on
	 * DSP = घातer on
	 * DSP CPU = stop (will be set to "run" after firmware loaded)
	 */
	regmap_ग_लिखो(rt5677->regmap, RT5677_PWR_DSP1,
		RT5677_PWR_SR7 | RT5677_PWR_SR6 |
		RT5677_PWR_SR5 | RT5677_PWR_SR4 |
		RT5677_PWR_SR3 | RT5677_PWR_SR2 |
		RT5677_PWR_SR1 | RT5677_PWR_SR0 |
		RT5677_PWR_MLT | RT5677_PWR_DSP |
		RT5677_PWR_DSP_CPU);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_parse_and_load_dsp(काष्ठा rt5677_priv *rt5677, स्थिर u8 *buf,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा snd_soc_component *component = rt5677->component;
	Elf32_Ehdr *elf_hdr;
	Elf32_Phdr *pr_hdr;
	Elf32_Half i;
	पूर्णांक ret = 0;

	अगर (!buf || (len < माप(Elf32_Ehdr)))
		वापस -ENOMEM;

	elf_hdr = (Elf32_Ehdr *)buf;
#अगर_अघोषित EM_XTENSA
#घोषणा EM_XTENSA	94
#पूर्ण_अगर
	अगर (म_भेदन(elf_hdr->e_ident, ELFMAG, माप(ELFMAG) - 1))
		dev_err(component->dev, "Wrong ELF header prefix\n");
	अगर (elf_hdr->e_ehsize != माप(Elf32_Ehdr))
		dev_err(component->dev, "Wrong Elf header size\n");
	अगर (elf_hdr->e_machine != EM_XTENSA)
		dev_err(component->dev, "Wrong DSP code file\n");

	अगर (len < elf_hdr->e_phoff)
		वापस -ENOMEM;
	pr_hdr = (Elf32_Phdr *)(buf + elf_hdr->e_phoff);
	क्रम (i = 0; i < elf_hdr->e_phnum; i++) अणु
		/* TODO: handle p_memsz != p_filesz */
		अगर (pr_hdr->p_paddr && pr_hdr->p_filesz) अणु
			dev_info(component->dev, "Load 0x%x bytes to 0x%x\n",
					pr_hdr->p_filesz, pr_hdr->p_paddr);

			ret = rt5677_spi_ग_लिखो(pr_hdr->p_paddr,
					buf + pr_hdr->p_offset,
					pr_hdr->p_filesz);
			अगर (ret)
				dev_err(component->dev, "Load firmware failed %d\n",
						ret);
		पूर्ण
		pr_hdr++;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rt5677_load_dsp_from_file(काष्ठा rt5677_priv *rt5677)
अणु
	स्थिर काष्ठा firmware *fwp;
	काष्ठा device *dev = rt5677->component->dev;
	पूर्णांक ret = 0;

	/* Load dsp firmware from rt5677_elf_vad file */
	ret = request_firmware(&fwp, "rt5677_elf_vad", dev);
	अगर (ret) अणु
		dev_err(dev, "Request rt5677_elf_vad failed %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(dev, "Requested rt5677_elf_vad (%zu)\n", fwp->size);

	ret = rt5677_parse_and_load_dsp(rt5677, fwp->data, fwp->size);
	release_firmware(fwp);
	वापस ret;
पूर्ण

अटल पूर्णांक rt5677_set_dsp_vad(काष्ठा snd_soc_component *component, bool on)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	rt5677->dsp_vad_en_request = on;
	rt5677->dsp_vad_en = on;

	अगर (!IS_ENABLED(CONFIG_SND_SOC_RT5677_SPI))
		वापस -ENXIO;

	schedule_delayed_work(&rt5677->dsp_work, 0);
	वापस 0;
पूर्ण

अटल व्योम rt5677_dsp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5677_priv *rt5677 =
		container_of(work, काष्ठा rt5677_priv, dsp_work.work);
	अटल bool activity;
	bool enable = rt5677->dsp_vad_en;
	पूर्णांक i, val;


	dev_info(rt5677->component->dev, "DSP VAD: enable=%d, activity=%d\n",
			enable, activity);

	अगर (enable && !activity) अणु
		activity = true;

		/* Beक्रमe a hotword is detected, GPIO1 pin is configured as IRQ
		 * output so that jack detect works. When a hotword is detected,
		 * the DSP firmware configures the GPIO1 pin as GPIO1 and
		 * drives a 1. rt5677_irq() is called after a rising edge on
		 * the GPIO1 pin, due to either jack detect event or hotword
		 * event, or both. All possible events are checked and handled
		 * in rt5677_irq() where GPIO1 pin is configured back to IRQ
		 * output अगर a hotword is detected.
		 */

		rt5677_set_vad_source(rt5677);
		rt5677_set_dsp_mode(rt5677, true);

#घोषणा RT5677_BOOT_RETRY 20
		क्रम (i = 0; i < RT5677_BOOT_RETRY; i++) अणु
			regmap_पढ़ो(rt5677->regmap, RT5677_PWR_DSP_ST, &val);
			अगर (val == 0x3ff)
				अवरोध;
			udelay(500);
		पूर्ण
		अगर (i == RT5677_BOOT_RETRY && val != 0x3ff) अणु
			dev_err(rt5677->component->dev, "DSP Boot Timed Out!");
			वापस;
		पूर्ण

		/* Boot the firmware from IRAM instead of SRAM0. */
		rt5677_dsp_mode_i2c_ग_लिखो_addr(rt5677, RT5677_DSP_BOOT_VECTOR,
			0x0009, 0x0003);
		rt5677_dsp_mode_i2c_ग_लिखो_addr(rt5677, RT5677_DSP_BOOT_VECTOR,
			0x0019, 0x0003);
		rt5677_dsp_mode_i2c_ग_लिखो_addr(rt5677, RT5677_DSP_BOOT_VECTOR,
			0x0009, 0x0003);

		rt5677_load_dsp_from_file(rt5677);

		/* Set DSP CPU to Run */
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP_CPU, 0x0);
	पूर्ण अन्यथा अगर (!enable && activity) अणु
		activity = false;

		/* Don't turn off the DSP जबतक handling irqs */
		mutex_lock(&rt5677->irq_lock);
		/* Set DSP CPU to Stop */
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP_CPU, RT5677_PWR_DSP_CPU);

		rt5677_set_dsp_mode(rt5677, false);

		/* Disable and clear VAD पूर्णांकerrupt */
		regmap_ग_लिखो(rt5677->regmap, RT5677_VAD_CTRL1, 0x2184);

		/* Set GPIO1 pin back to be IRQ output क्रम jack detect */
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL1,
			RT5677_GPIO1_PIN_MASK, RT5677_GPIO1_PIN_IRQ);

		mutex_unlock(&rt5677->irq_lock);
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -6525, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(st_vol_tlv, -4650, 150, 0);

/* अणु0, +20, +24, +30, +35, +40, +44, +50, +52पूर्ण dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(bst_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(2000, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2400, 0, 0),
	3, 5, TLV_DB_SCALE_ITEM(3000, 500, 0),
	6, 6, TLV_DB_SCALE_ITEM(4400, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(5000, 0, 0),
	8, 8, TLV_DB_SCALE_ITEM(5200, 0, 0)
);

अटल पूर्णांक rt5677_dsp_vad_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt5677->dsp_vad_en_request;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_dsp_vad_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);

	rt5677_set_dsp_vad(component, !!ucontrol->value.पूर्णांकeger.value[0]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_snd_controls[] = अणु
	/* OUTPUT Control */
	SOC_SINGLE("OUT1 Playback Switch", RT5677_LOUT1,
		RT5677_LOUT1_L_MUTE_SFT, 1, 1),
	SOC_SINGLE("OUT2 Playback Switch", RT5677_LOUT1,
		RT5677_LOUT2_L_MUTE_SFT, 1, 1),
	SOC_SINGLE("OUT3 Playback Switch", RT5677_LOUT1,
		RT5677_LOUT3_L_MUTE_SFT, 1, 1),

	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5677_DAC1_DIG_VOL,
		RT5677_L_VOL_SFT, RT5677_R_VOL_SFT, 127, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("DAC2 Playback Volume", RT5677_DAC2_DIG_VOL,
		RT5677_L_VOL_SFT, RT5677_R_VOL_SFT, 127, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("DAC3 Playback Volume", RT5677_DAC3_DIG_VOL,
		RT5677_L_VOL_SFT, RT5677_R_VOL_SFT, 127, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("DAC4 Playback Volume", RT5677_DAC4_DIG_VOL,
		RT5677_L_VOL_SFT, RT5677_R_VOL_SFT, 127, 0, dac_vol_tlv),

	/* IN1/IN2 Control */
	SOC_SINGLE_TLV("IN1 Boost", RT5677_IN1, RT5677_BST_SFT1, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost", RT5677_IN1, RT5677_BST_SFT2, 8, 0, bst_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC1 Capture Switch", RT5677_STO1_ADC_DIG_VOL,
		RT5677_L_MUTE_SFT, RT5677_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("ADC2 Capture Switch", RT5677_STO2_ADC_DIG_VOL,
		RT5677_L_MUTE_SFT, RT5677_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("ADC3 Capture Switch", RT5677_STO3_ADC_DIG_VOL,
		RT5677_L_MUTE_SFT, RT5677_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("ADC4 Capture Switch", RT5677_STO4_ADC_DIG_VOL,
		RT5677_L_MUTE_SFT, RT5677_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("Mono ADC Capture Switch", RT5677_MONO_ADC_DIG_VOL,
		RT5677_L_MUTE_SFT, RT5677_R_MUTE_SFT, 1, 1),

	SOC_DOUBLE_TLV("ADC1 Capture Volume", RT5677_STO1_ADC_DIG_VOL,
		RT5677_STO1_ADC_L_VOL_SFT, RT5677_STO1_ADC_R_VOL_SFT, 63, 0,
		adc_vol_tlv),
	SOC_DOUBLE_TLV("ADC2 Capture Volume", RT5677_STO2_ADC_DIG_VOL,
		RT5677_STO1_ADC_L_VOL_SFT, RT5677_STO1_ADC_R_VOL_SFT, 63, 0,
		adc_vol_tlv),
	SOC_DOUBLE_TLV("ADC3 Capture Volume", RT5677_STO3_ADC_DIG_VOL,
		RT5677_STO1_ADC_L_VOL_SFT, RT5677_STO1_ADC_R_VOL_SFT, 63, 0,
		adc_vol_tlv),
	SOC_DOUBLE_TLV("ADC4 Capture Volume", RT5677_STO4_ADC_DIG_VOL,
		RT5677_STO1_ADC_L_VOL_SFT, RT5677_STO1_ADC_R_VOL_SFT, 63, 0,
		adc_vol_tlv),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5677_MONO_ADC_DIG_VOL,
		RT5677_MONO_ADC_L_VOL_SFT, RT5677_MONO_ADC_R_VOL_SFT, 63, 0,
		adc_vol_tlv),

	/* Sidetone Control */
	SOC_SINGLE_TLV("Sidetone Volume", RT5677_SIDETONE_CTRL,
		RT5677_ST_VOL_SFT, 31, 0, st_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Volume", RT5677_STO1_2_ADC_BST,
		RT5677_STO1_ADC_L_BST_SFT, RT5677_STO1_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),
	SOC_DOUBLE_TLV("STO2 ADC Boost Volume", RT5677_STO1_2_ADC_BST,
		RT5677_STO2_ADC_L_BST_SFT, RT5677_STO2_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),
	SOC_DOUBLE_TLV("STO3 ADC Boost Volume", RT5677_STO3_4_ADC_BST,
		RT5677_STO3_ADC_L_BST_SFT, RT5677_STO3_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),
	SOC_DOUBLE_TLV("STO4 ADC Boost Volume", RT5677_STO3_4_ADC_BST,
		RT5677_STO4_ADC_L_BST_SFT, RT5677_STO4_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),
	SOC_DOUBLE_TLV("Mono ADC Boost Volume", RT5677_ADC_BST_CTRL2,
		RT5677_MONO_ADC_L_BST_SFT, RT5677_MONO_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),

	SOC_SINGLE_EXT("DSP VAD Switch", SND_SOC_NOPM, 0, 1, 0,
		rt5677_dsp_vad_get, rt5677_dsp_vad_put),
पूर्ण;

/**
 * set_dmic_clk - Set parameter of dmic.
 *
 * @w: DAPM widget.
 * @kcontrol: The kcontrol of this widget.
 * @event: Event id.
 *
 * Choose dmic घड़ी between 1MHz and 3MHz.
 * It is better क्रम घड़ी to approximate 3MHz.
 */
अटल पूर्णांक set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5677->sysclk / rl6231_get_pre_भाग(rt5677->regmap,
		RT5677_CLK_TREE_CTRL1, RT5677_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		regmap_update_bits(rt5677->regmap, RT5677_DMIC_CTRL1,
			RT5677_DMIC_CLK_MASK, idx << RT5677_DMIC_CLK_SFT);
	वापस idx;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(rt5677->regmap, RT5677_GLB_CLK1, &val);
	val &= RT5677_SCLK_SRC_MASK;
	अगर (val == RT5677_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, shअगरt, val;

	अगर (source->reg == RT5677_ASRC_1) अणु
		चयन (source->shअगरt) अणु
		हाल 12:
			reg = RT5677_ASRC_4;
			shअगरt = 0;
			अवरोध;
		हाल 13:
			reg = RT5677_ASRC_4;
			shअगरt = 4;
			अवरोध;
		हाल 14:
			reg = RT5677_ASRC_4;
			shअगरt = 8;
			अवरोध;
		हाल 15:
			reg = RT5677_ASRC_4;
			shअगरt = 12;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (source->shअगरt) अणु
		हाल 0:
			reg = RT5677_ASRC_6;
			shअगरt = 8;
			अवरोध;
		हाल 1:
			reg = RT5677_ASRC_6;
			shअगरt = 12;
			अवरोध;
		हाल 2:
			reg = RT5677_ASRC_5;
			shअगरt = 0;
			अवरोध;
		हाल 3:
			reg = RT5677_ASRC_5;
			shअगरt = 4;
			अवरोध;
		हाल 4:
			reg = RT5677_ASRC_5;
			shअगरt = 8;
			अवरोध;
		हाल 5:
			reg = RT5677_ASRC_5;
			shअगरt = 12;
			अवरोध;
		हाल 12:
			reg = RT5677_ASRC_3;
			shअगरt = 0;
			अवरोध;
		हाल 13:
			reg = RT5677_ASRC_3;
			shअगरt = 4;
			अवरोध;
		हाल 14:
			reg = RT5677_ASRC_3;
			shअगरt = 12;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	regmap_पढ़ो(rt5677->regmap, reg, &val);
	val = (val >> shअगरt) & 0xf;

	चयन (val) अणु
	हाल 1 ... 6:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

पूर्ण

अटल पूर्णांक can_use_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	अगर (rt5677->sysclk > rt5677->lrck[RT5677_AIF1] * 384)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * rt5677_sel_asrc_clk_src - select ASRC घड़ी source क्रम a set of filters
 * @component: SoC audio component device.
 * @filter_mask: mask of filters.
 * @clk_src: घड़ी source
 *
 * The ASRC function is क्रम asynchronous MCLK and LRCK. Also, since RT5677 can
 * only support standard 32fs or 64fs i2s क्रमmat, ASRC should be enabled to
 * support special i2s घड़ी क्रमmat such as Intel's 100fs(100 * sampling rate).
 * ASRC function will track i2s घड़ी and generate a corresponding प्रणाली घड़ी
 * क्रम codec. This function provides an API to select the घड़ी source क्रम a
 * set of filters specअगरied by the mask. And the codec driver will turn on ASRC
 * क्रम these filters अगर ASRC is selected as their घड़ी source.
 */
पूर्णांक rt5677_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक asrc3_mask = 0, asrc3_value = 0;
	अचिन्हित पूर्णांक asrc4_mask = 0, asrc4_value = 0;
	अचिन्हित पूर्णांक asrc5_mask = 0, asrc5_value = 0;
	अचिन्हित पूर्णांक asrc6_mask = 0, asrc6_value = 0;
	अचिन्हित पूर्णांक asrc7_mask = 0, asrc7_value = 0;
	अचिन्हित पूर्णांक asrc8_mask = 0, asrc8_value = 0;

	चयन (clk_src) अणु
	हाल RT5677_CLK_SEL_SYS:
	हाल RT5677_CLK_SEL_I2S1_ASRC:
	हाल RT5677_CLK_SEL_I2S2_ASRC:
	हाल RT5677_CLK_SEL_I2S3_ASRC:
	हाल RT5677_CLK_SEL_I2S4_ASRC:
	हाल RT5677_CLK_SEL_I2S5_ASRC:
	हाल RT5677_CLK_SEL_I2S6_ASRC:
	हाल RT5677_CLK_SEL_SYS2:
	हाल RT5677_CLK_SEL_SYS3:
	हाल RT5677_CLK_SEL_SYS4:
	हाल RT5677_CLK_SEL_SYS5:
	हाल RT5677_CLK_SEL_SYS6:
	हाल RT5677_CLK_SEL_SYS7:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* ASRC 3 */
	अगर (filter_mask & RT5677_DA_STEREO_FILTER) अणु
		asrc3_mask |= RT5677_DA_STO_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5677_DA_STO_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_STO_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DA_MONO2_L_FILTER) अणु
		asrc3_mask |= RT5677_DA_MONO2L_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5677_DA_MONO2L_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO2L_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DA_MONO2_R_FILTER) अणु
		asrc3_mask |= RT5677_DA_MONO2R_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5677_DA_MONO2R_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO2R_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc3_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_3, asrc3_mask,
			asrc3_value);

	/* ASRC 4 */
	अगर (filter_mask & RT5677_DA_MONO3_L_FILTER) अणु
		asrc4_mask |= RT5677_DA_MONO3L_CLK_SEL_MASK;
		asrc4_value = (asrc4_value & ~RT5677_DA_MONO3L_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO3L_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DA_MONO3_R_FILTER) अणु
		asrc4_mask |= RT5677_DA_MONO3R_CLK_SEL_MASK;
		asrc4_value = (asrc4_value & ~RT5677_DA_MONO3R_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO3R_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DA_MONO4_L_FILTER) अणु
		asrc4_mask |= RT5677_DA_MONO4L_CLK_SEL_MASK;
		asrc4_value = (asrc4_value & ~RT5677_DA_MONO4L_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO4L_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DA_MONO4_R_FILTER) अणु
		asrc4_mask |= RT5677_DA_MONO4R_CLK_SEL_MASK;
		asrc4_value = (asrc4_value & ~RT5677_DA_MONO4R_CLK_SEL_MASK)
			| (clk_src << RT5677_DA_MONO4R_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc4_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_4, asrc4_mask,
			asrc4_value);

	/* ASRC 5 */
	अगर (filter_mask & RT5677_AD_STEREO1_FILTER) अणु
		asrc5_mask |= RT5677_AD_STO1_CLK_SEL_MASK;
		asrc5_value = (asrc5_value & ~RT5677_AD_STO1_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_STO1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_AD_STEREO2_FILTER) अणु
		asrc5_mask |= RT5677_AD_STO2_CLK_SEL_MASK;
		asrc5_value = (asrc5_value & ~RT5677_AD_STO2_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_STO2_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_AD_STEREO3_FILTER) अणु
		asrc5_mask |= RT5677_AD_STO3_CLK_SEL_MASK;
		asrc5_value = (asrc5_value & ~RT5677_AD_STO3_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_STO3_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_AD_STEREO4_FILTER) अणु
		asrc5_mask |= RT5677_AD_STO4_CLK_SEL_MASK;
		asrc5_value = (asrc5_value & ~RT5677_AD_STO4_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_STO4_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc5_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_5, asrc5_mask,
			asrc5_value);

	/* ASRC 6 */
	अगर (filter_mask & RT5677_AD_MONO_L_FILTER) अणु
		asrc6_mask |= RT5677_AD_MONOL_CLK_SEL_MASK;
		asrc6_value = (asrc6_value & ~RT5677_AD_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_AD_MONO_R_FILTER) अणु
		asrc6_mask |= RT5677_AD_MONOR_CLK_SEL_MASK;
		asrc6_value = (asrc6_value & ~RT5677_AD_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5677_AD_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc6_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_6, asrc6_mask,
			asrc6_value);

	/* ASRC 7 */
	अगर (filter_mask & RT5677_DSP_OB_0_3_FILTER) अणु
		asrc7_mask |= RT5677_DSP_OB_0_3_CLK_SEL_MASK;
		asrc7_value = (asrc7_value & ~RT5677_DSP_OB_0_3_CLK_SEL_MASK)
			| (clk_src << RT5677_DSP_OB_0_3_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_DSP_OB_4_7_FILTER) अणु
		asrc7_mask |= RT5677_DSP_OB_4_7_CLK_SEL_MASK;
		asrc7_value = (asrc7_value & ~RT5677_DSP_OB_4_7_CLK_SEL_MASK)
			| (clk_src << RT5677_DSP_OB_4_7_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc7_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_7, asrc7_mask,
			asrc7_value);

	/* ASRC 8 */
	अगर (filter_mask & RT5677_I2S1_SOURCE) अणु
		asrc8_mask |= RT5677_I2S1_CLK_SEL_MASK;
		asrc8_value = (asrc8_value & ~RT5677_I2S1_CLK_SEL_MASK)
			| ((clk_src - 1) << RT5677_I2S1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_I2S2_SOURCE) अणु
		asrc8_mask |= RT5677_I2S2_CLK_SEL_MASK;
		asrc8_value = (asrc8_value & ~RT5677_I2S2_CLK_SEL_MASK)
			| ((clk_src - 1) << RT5677_I2S2_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_I2S3_SOURCE) अणु
		asrc8_mask |= RT5677_I2S3_CLK_SEL_MASK;
		asrc8_value = (asrc8_value & ~RT5677_I2S3_CLK_SEL_MASK)
			| ((clk_src - 1) << RT5677_I2S3_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5677_I2S4_SOURCE) अणु
		asrc8_mask |= RT5677_I2S4_CLK_SEL_MASK;
		asrc8_value = (asrc8_value & ~RT5677_I2S4_CLK_SEL_MASK)
			| ((clk_src - 1) << RT5677_I2S4_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc8_mask)
		regmap_update_bits(rt5677->regmap, RT5677_ASRC_8, asrc8_mask,
			asrc8_value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5677_sel_asrc_clk_src);

अटल पूर्णांक rt5677_dmic_use_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक asrc_setting;

	चयन (source->shअगरt) अणु
	हाल 11:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO1_CLK_SEL_MASK) >>
				RT5677_AD_STO1_CLK_SEL_SFT;
		अवरोध;

	हाल 10:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO2_CLK_SEL_MASK) >>
				RT5677_AD_STO2_CLK_SEL_SFT;
		अवरोध;

	हाल 9:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO3_CLK_SEL_MASK) >>
				RT5677_AD_STO3_CLK_SEL_SFT;
		अवरोध;

	हाल 8:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO4_CLK_SEL_MASK) >>
			RT5677_AD_STO4_CLK_SEL_SFT;
		अवरोध;

	हाल 7:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_6, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_MONOL_CLK_SEL_MASK) >>
			RT5677_AD_MONOL_CLK_SEL_SFT;
		अवरोध;

	हाल 6:
		regmap_पढ़ो(rt5677->regmap, RT5677_ASRC_6, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_MONOR_CLK_SEL_MASK) >>
			RT5677_AD_MONOR_CLK_SEL_SFT;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (asrc_setting >= RT5677_CLK_SEL_I2S1_ASRC &&
	    asrc_setting <= RT5677_CLK_SEL_I2S6_ASRC)
		वापस 1;

	वापस 0;
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO1_ADC_MIXER,
			RT5677_M_STO1_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO1_ADC_MIXER,
			RT5677_M_STO1_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO1_ADC_MIXER,
			RT5677_M_STO1_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO1_ADC_MIXER,
			RT5677_M_STO1_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO2_ADC_MIXER,
			RT5677_M_STO2_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO2_ADC_MIXER,
			RT5677_M_STO2_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO2_ADC_MIXER,
			RT5677_M_STO2_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO2_ADC_MIXER,
			RT5677_M_STO2_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto3_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO3_ADC_MIXER,
			RT5677_M_STO3_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO3_ADC_MIXER,
			RT5677_M_STO3_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto3_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO3_ADC_MIXER,
			RT5677_M_STO3_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO3_ADC_MIXER,
			RT5677_M_STO3_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto4_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO4_ADC_MIXER,
			RT5677_M_STO4_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO4_ADC_MIXER,
			RT5677_M_STO4_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto4_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_STO4_ADC_MIXER,
			RT5677_M_STO4_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_STO4_ADC_MIXER,
			RT5677_M_STO4_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_MONO_ADC_MIXER,
			RT5677_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_MONO_ADC_MIXER,
			RT5677_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5677_MONO_ADC_MIXER,
			RT5677_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5677_MONO_ADC_MIXER,
			RT5677_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5677_ADC_IF_DSP_DAC1_MIXER,
			RT5677_M_ADDA_MIXER1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5677_ADC_IF_DSP_DAC1_MIXER,
			RT5677_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5677_ADC_IF_DSP_DAC1_MIXER,
			RT5677_M_ADDA_MIXER1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5677_ADC_IF_DSP_DAC1_MIXER,
			RT5677_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ST L Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_ST_DAC1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 L Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC1_L_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 L Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC2_L_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 R Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC1_R_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ST R Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_ST_DAC1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 R Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC1_R_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 R Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC2_R_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 L Switch", RT5677_STO1_DAC_MIXER,
			RT5677_M_DAC1_L_STO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ST L Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_ST_DAC2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 L Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC1_L_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 L Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC2_L_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 R Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC2_R_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ST R Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_ST_DAC2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 R Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC1_R_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 R Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC2_R_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC2 L Switch", RT5677_MONO_DAC_MIXER,
			RT5677_M_DAC2_L_MONO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dd1_l_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Sto DAC Mix L Switch", RT5677_DD1_MIXER,
			RT5677_M_STO_L_DD1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("Mono DAC Mix L Switch", RT5677_DD1_MIXER,
			RT5677_M_MONO_L_DD1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC3 L Switch", RT5677_DD1_MIXER,
			RT5677_M_DAC3_L_DD1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC3 R Switch", RT5677_DD1_MIXER,
			RT5677_M_DAC3_R_DD1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dd1_r_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Sto DAC Mix R Switch", RT5677_DD1_MIXER,
			RT5677_M_STO_R_DD1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("Mono DAC Mix R Switch", RT5677_DD1_MIXER,
			RT5677_M_MONO_R_DD1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC3 R Switch", RT5677_DD1_MIXER,
			RT5677_M_DAC3_R_DD1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC3 L Switch", RT5677_DD1_MIXER,
			RT5677_M_DAC3_L_DD1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dd2_l_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Sto DAC Mix L Switch", RT5677_DD2_MIXER,
			RT5677_M_STO_L_DD2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("Mono DAC Mix L Switch", RT5677_DD2_MIXER,
			RT5677_M_MONO_L_DD2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC4 L Switch", RT5677_DD2_MIXER,
			RT5677_M_DAC4_L_DD2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC4 R Switch", RT5677_DD2_MIXER,
			RT5677_M_DAC4_R_DD2_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dd2_r_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Sto DAC Mix R Switch", RT5677_DD2_MIXER,
			RT5677_M_STO_R_DD2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("Mono DAC Mix R Switch", RT5677_DD2_MIXER,
			RT5677_M_MONO_R_DD2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC4 R Switch", RT5677_DD2_MIXER,
			RT5677_M_DAC4_R_DD2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC4 L Switch", RT5677_DD2_MIXER,
			RT5677_M_DAC4_L_DD2_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_01_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_01_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_23_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_45_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_6_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_7_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_8_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_9_H_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_23_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_01_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_23_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_45_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_6_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_7_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_8_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_0123_MIXER_CTRL,
			RT5677_DSP_IB_9_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_4_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_01_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_23_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_45_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_6_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_7_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_8_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_9_H_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_5_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_01_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_23_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_45_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_6_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_7_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_8_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_45_MIXER_CTRL,
			RT5677_DSP_IB_9_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_6_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_01_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_23_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_45_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_6_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_7_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_8_H_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_9_H_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob_7_mix[] = अणु
	SOC_DAPM_SINGLE("IB01 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_01_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB23 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_23_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB45 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_45_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB6 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_6_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB7 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_7_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB8 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_8_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("IB9 Switch", RT5677_DSP_OUTB_67_MIXER_CTRL,
			RT5677_DSP_IB_9_L_SFT, 1, 1),
पूर्ण;


/* Mux */
/* DAC1 L/R Source */ /* MX-29 [10:8] */
अटल स्थिर अक्षर * स्थिर rt5677_dac1_src[] = अणु
	"IF1 DAC 01", "IF2 DAC 01", "IF3 DAC LR", "IF4 DAC LR", "SLB DAC 01",
	"OB 01"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac1_क्रमागत, RT5677_ADC_IF_DSP_DAC1_MIXER,
	RT5677_DAC1_L_SEL_SFT, rt5677_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac1_mux =
	SOC_DAPM_ENUM("DAC1 Source", rt5677_dac1_क्रमागत);

/* ADDA1 L/R Source */ /* MX-29 [1:0] */
अटल स्थिर अक्षर * स्थिर rt5677_adda1_src[] = अणु
	"STO1 ADC MIX", "STO2 ADC MIX", "OB 67",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_adda1_क्रमागत, RT5677_ADC_IF_DSP_DAC1_MIXER,
	RT5677_ADDA1_SEL_SFT, rt5677_adda1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_adda1_mux =
	SOC_DAPM_ENUM("ADDA1 Source", rt5677_adda1_क्रमागत);


/*DAC2 L/R Source*/ /* MX-1B [6:4] [2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_dac2l_src[] = अणु
	"IF1 DAC 2", "IF2 DAC 2", "IF3 DAC L", "IF4 DAC L", "SLB DAC 2",
	"OB 2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac2l_क्रमागत, RT5677_IF_DSP_DAC2_MIXER,
	RT5677_SEL_DAC2_L_SRC_SFT, rt5677_dac2l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac2_l_mux =
	SOC_DAPM_ENUM("DAC2 L Source", rt5677_dac2l_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5677_dac2r_src[] = अणु
	"IF1 DAC 3", "IF2 DAC 3", "IF3 DAC R", "IF4 DAC R", "SLB DAC 3",
	"OB 3", "Haptic Generator", "VAD ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac2r_क्रमागत, RT5677_IF_DSP_DAC2_MIXER,
	RT5677_SEL_DAC2_R_SRC_SFT, rt5677_dac2r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac2_r_mux =
	SOC_DAPM_ENUM("DAC2 R Source", rt5677_dac2r_क्रमागत);

/*DAC3 L/R Source*/ /* MX-16 [6:4] [2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_dac3l_src[] = अणु
	"IF1 DAC 4", "IF2 DAC 4", "IF3 DAC L", "IF4 DAC L",
	"SLB DAC 4", "OB 4"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac3l_क्रमागत, RT5677_IF_DSP_DAC3_4_MIXER,
	RT5677_SEL_DAC3_L_SRC_SFT, rt5677_dac3l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac3_l_mux =
	SOC_DAPM_ENUM("DAC3 L Source", rt5677_dac3l_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5677_dac3r_src[] = अणु
	"IF1 DAC 5", "IF2 DAC 5", "IF3 DAC R", "IF4 DAC R",
	"SLB DAC 5", "OB 5"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac3r_क्रमागत, RT5677_IF_DSP_DAC3_4_MIXER,
	RT5677_SEL_DAC3_R_SRC_SFT, rt5677_dac3r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac3_r_mux =
	SOC_DAPM_ENUM("DAC3 R Source", rt5677_dac3r_क्रमागत);

/*DAC4 L/R Source*/ /* MX-16 [14:12] [10:8] */
अटल स्थिर अक्षर * स्थिर rt5677_dac4l_src[] = अणु
	"IF1 DAC 6", "IF2 DAC 6", "IF3 DAC L", "IF4 DAC L",
	"SLB DAC 6", "OB 6"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac4l_क्रमागत, RT5677_IF_DSP_DAC3_4_MIXER,
	RT5677_SEL_DAC4_L_SRC_SFT, rt5677_dac4l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac4_l_mux =
	SOC_DAPM_ENUM("DAC4 L Source", rt5677_dac4l_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5677_dac4r_src[] = अणु
	"IF1 DAC 7", "IF2 DAC 7", "IF3 DAC R", "IF4 DAC R",
	"SLB DAC 7", "OB 7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac4r_क्रमागत, RT5677_IF_DSP_DAC3_4_MIXER,
	RT5677_SEL_DAC4_R_SRC_SFT, rt5677_dac4r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac4_r_mux =
	SOC_DAPM_ENUM("DAC4 R Source", rt5677_dac4r_क्रमागत);

/* In/OutBound Source Pass SRC */ /* MX-A5 [3] [4] [0] [1] [2] */
अटल स्थिर अक्षर * स्थिर rt5677_iob_bypass_src[] = अणु
	"Bypass", "Pass SRC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_ob01_bypass_src_क्रमागत, RT5677_DSP_IN_OUTB_CTRL,
	RT5677_SEL_SRC_OB01_SFT, rt5677_iob_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob01_bypass_src_mux =
	SOC_DAPM_ENUM("OB01 Bypass Source", rt5677_ob01_bypass_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_ob23_bypass_src_क्रमागत, RT5677_DSP_IN_OUTB_CTRL,
	RT5677_SEL_SRC_OB23_SFT, rt5677_iob_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ob23_bypass_src_mux =
	SOC_DAPM_ENUM("OB23 Bypass Source", rt5677_ob23_bypass_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_ib01_bypass_src_क्रमागत, RT5677_DSP_IN_OUTB_CTRL,
	RT5677_SEL_SRC_IB01_SFT, rt5677_iob_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib01_bypass_src_mux =
	SOC_DAPM_ENUM("IB01 Bypass Source", rt5677_ib01_bypass_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_ib23_bypass_src_क्रमागत, RT5677_DSP_IN_OUTB_CTRL,
	RT5677_SEL_SRC_IB23_SFT, rt5677_iob_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib23_bypass_src_mux =
	SOC_DAPM_ENUM("IB23 Bypass Source", rt5677_ib23_bypass_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_ib45_bypass_src_क्रमागत, RT5677_DSP_IN_OUTB_CTRL,
	RT5677_SEL_SRC_IB45_SFT, rt5677_iob_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib45_bypass_src_mux =
	SOC_DAPM_ENUM("IB45 Bypass Source", rt5677_ib45_bypass_src_क्रमागत);

/* Stereo ADC Source 2 */ /* MX-27 MX26 MX25 [11:10] */
अटल स्थिर अक्षर * स्थिर rt5677_stereo_adc2_src[] = अणु
	"DD MIX1", "DMIC", "Stereo DAC MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo1_adc2_क्रमागत, RT5677_STO1_ADC_MIXER,
	RT5677_SEL_STO1_ADC2_SFT, rt5677_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_adc2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2 Source", rt5677_stereo1_adc2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo2_adc2_क्रमागत, RT5677_STO2_ADC_MIXER,
	RT5677_SEL_STO2_ADC2_SFT, rt5677_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_adc2_mux =
	SOC_DAPM_ENUM("Stereo2 ADC2 Source", rt5677_stereo2_adc2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo3_adc2_क्रमागत, RT5677_STO3_ADC_MIXER,
	RT5677_SEL_STO3_ADC2_SFT, rt5677_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto3_adc2_mux =
	SOC_DAPM_ENUM("Stereo3 ADC2 Source", rt5677_stereo3_adc2_क्रमागत);

/* DMIC Source */ /* MX-28 [9:8][1:0] MX-27 MX-26 MX-25 MX-24 [9:8] */
अटल स्थिर अक्षर * स्थिर rt5677_dmic_src[] = अणु
	"DMIC1", "DMIC2", "DMIC3", "DMIC4"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_dmic_l_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_DMIC_L_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_dmic_l_mux =
	SOC_DAPM_ENUM("Mono DMIC L Source", rt5677_mono_dmic_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_dmic_r_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_DMIC_R_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_dmic_r_mux =
	SOC_DAPM_ENUM("Mono DMIC R Source", rt5677_mono_dmic_r_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo1_dmic_क्रमागत, RT5677_STO1_ADC_MIXER,
	RT5677_SEL_STO1_DMIC_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC Source", rt5677_stereo1_dmic_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo2_dmic_क्रमागत, RT5677_STO2_ADC_MIXER,
	RT5677_SEL_STO2_DMIC_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_dmic_mux =
	SOC_DAPM_ENUM("Stereo2 DMIC Source", rt5677_stereo2_dmic_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo3_dmic_क्रमागत, RT5677_STO3_ADC_MIXER,
	RT5677_SEL_STO3_DMIC_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto3_dmic_mux =
	SOC_DAPM_ENUM("Stereo3 DMIC Source", rt5677_stereo3_dmic_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo4_dmic_क्रमागत, RT5677_STO4_ADC_MIXER,
	RT5677_SEL_STO4_DMIC_SFT, rt5677_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto4_dmic_mux =
	SOC_DAPM_ENUM("Stereo4 DMIC Source", rt5677_stereo4_dmic_क्रमागत);

/* Stereo2 ADC Source */ /* MX-26 [0] */
अटल स्थिर अक्षर * स्थिर rt5677_stereo2_adc_lr_src[] = अणु
	"L", "LR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo2_adc_lr_क्रमागत, RT5677_STO2_ADC_MIXER,
	RT5677_SEL_STO2_LR_MIX_SFT, rt5677_stereo2_adc_lr_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_adc_lr_mux =
	SOC_DAPM_ENUM("Stereo2 ADC LR Source", rt5677_stereo2_adc_lr_क्रमागत);

/* Stereo1 ADC Source 1 */ /* MX-27 MX26 MX25 [13:12] */
अटल स्थिर अक्षर * स्थिर rt5677_stereo_adc1_src[] = अणु
	"DD MIX1", "ADC1/2", "Stereo DAC MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo1_adc1_क्रमागत, RT5677_STO1_ADC_MIXER,
	RT5677_SEL_STO1_ADC1_SFT, rt5677_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto1_adc1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1 Source", rt5677_stereo1_adc1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo2_adc1_क्रमागत, RT5677_STO2_ADC_MIXER,
	RT5677_SEL_STO2_ADC1_SFT, rt5677_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto2_adc1_mux =
	SOC_DAPM_ENUM("Stereo2 ADC1 Source", rt5677_stereo2_adc1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo3_adc1_क्रमागत, RT5677_STO3_ADC_MIXER,
	RT5677_SEL_STO3_ADC1_SFT, rt5677_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto3_adc1_mux =
	SOC_DAPM_ENUM("Stereo3 ADC1 Source", rt5677_stereo3_adc1_क्रमागत);

/* Mono ADC Left Source 2 */ /* MX-28 [11:10] */
अटल स्थिर अक्षर * स्थिर rt5677_mono_adc2_l_src[] = अणु
	"DD MIX1L", "DMIC", "MONO DAC MIXL"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_adc2_l_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_ADC_L2_SFT, rt5677_mono_adc2_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc2_l_mux =
	SOC_DAPM_ENUM("Mono ADC2 L Source", rt5677_mono_adc2_l_क्रमागत);

/* Mono ADC Left Source 1 */ /* MX-28 [13:12] */
अटल स्थिर अक्षर * स्थिर rt5677_mono_adc1_l_src[] = अणु
	"DD MIX1L", "ADC1", "MONO DAC MIXL"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_adc1_l_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_ADC_L1_SFT, rt5677_mono_adc1_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc1_l_mux =
	SOC_DAPM_ENUM("Mono ADC1 L Source", rt5677_mono_adc1_l_क्रमागत);

/* Mono ADC Right Source 2 */ /* MX-28 [3:2] */
अटल स्थिर अक्षर * स्थिर rt5677_mono_adc2_r_src[] = अणु
	"DD MIX1R", "DMIC", "MONO DAC MIXR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_adc2_r_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_ADC_R2_SFT, rt5677_mono_adc2_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc2_r_mux =
	SOC_DAPM_ENUM("Mono ADC2 R Source", rt5677_mono_adc2_r_क्रमागत);

/* Mono ADC Right Source 1 */ /* MX-28 [5:4] */
अटल स्थिर अक्षर * स्थिर rt5677_mono_adc1_r_src[] = अणु
	"DD MIX1R", "ADC2", "MONO DAC MIXR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_mono_adc1_r_क्रमागत, RT5677_MONO_ADC_MIXER,
	RT5677_SEL_MONO_ADC_R1_SFT, rt5677_mono_adc1_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_mono_adc1_r_mux =
	SOC_DAPM_ENUM("Mono ADC1 R Source", rt5677_mono_adc1_r_क्रमागत);

/* Stereo4 ADC Source 2 */ /* MX-24 [11:10] */
अटल स्थिर अक्षर * स्थिर rt5677_stereo4_adc2_src[] = अणु
	"DD MIX1", "DMIC", "DD MIX2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo4_adc2_क्रमागत, RT5677_STO4_ADC_MIXER,
	RT5677_SEL_STO4_ADC2_SFT, rt5677_stereo4_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto4_adc2_mux =
	SOC_DAPM_ENUM("Stereo4 ADC2 Source", rt5677_stereo4_adc2_क्रमागत);


/* Stereo4 ADC Source 1 */ /* MX-24 [13:12] */
अटल स्थिर अक्षर * स्थिर rt5677_stereo4_adc1_src[] = अणु
	"DD MIX1", "ADC1/2", "DD MIX2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_stereo4_adc1_क्रमागत, RT5677_STO4_ADC_MIXER,
	RT5677_SEL_STO4_ADC1_SFT, rt5677_stereo4_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sto4_adc1_mux =
	SOC_DAPM_ENUM("Stereo4 ADC1 Source", rt5677_stereo4_adc1_क्रमागत);

/* InBound0/1 Source */ /* MX-A3 [14:12] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound01_src[] = अणु
	"IF1 DAC 01", "IF2 DAC 01", "SLB DAC 01", "STO1 ADC MIX",
	"VAD ADC/DAC1 FS"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound01_क्रमागत, RT5677_DSP_INB_CTRL1,
	RT5677_IB01_SRC_SFT, rt5677_inbound01_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib01_src_mux =
	SOC_DAPM_ENUM("InBound0/1 Source", rt5677_inbound01_क्रमागत);

/* InBound2/3 Source */ /* MX-A3 [10:8] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound23_src[] = अणु
	"IF1 DAC 23", "IF2 DAC 23", "SLB DAC 23", "STO2 ADC MIX",
	"DAC1 FS", "IF4 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound23_क्रमागत, RT5677_DSP_INB_CTRL1,
	RT5677_IB23_SRC_SFT, rt5677_inbound23_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib23_src_mux =
	SOC_DAPM_ENUM("InBound2/3 Source", rt5677_inbound23_क्रमागत);

/* InBound4/5 Source */ /* MX-A3 [6:4] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound45_src[] = अणु
	"IF1 DAC 45", "IF2 DAC 45", "SLB DAC 45", "STO3 ADC MIX",
	"IF3 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound45_क्रमागत, RT5677_DSP_INB_CTRL1,
	RT5677_IB45_SRC_SFT, rt5677_inbound45_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib45_src_mux =
	SOC_DAPM_ENUM("InBound4/5 Source", rt5677_inbound45_क्रमागत);

/* InBound6 Source */ /* MX-A3 [2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound6_src[] = अणु
	"IF1 DAC 6", "IF2 DAC 6", "SLB DAC 6", "STO4 ADC MIX L",
	"IF4 DAC L", "STO1 ADC MIX L", "STO2 ADC MIX L", "STO3 ADC MIX L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound6_क्रमागत, RT5677_DSP_INB_CTRL1,
	RT5677_IB6_SRC_SFT, rt5677_inbound6_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib6_src_mux =
	SOC_DAPM_ENUM("InBound6 Source", rt5677_inbound6_क्रमागत);

/* InBound7 Source */ /* MX-A4 [14:12] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound7_src[] = अणु
	"IF1 DAC 7", "IF2 DAC 7", "SLB DAC 7", "STO4 ADC MIX R",
	"IF4 DAC R", "STO1 ADC MIX R", "STO2 ADC MIX R", "STO3 ADC MIX R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound7_क्रमागत, RT5677_DSP_INB_CTRL2,
	RT5677_IB7_SRC_SFT, rt5677_inbound7_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib7_src_mux =
	SOC_DAPM_ENUM("InBound7 Source", rt5677_inbound7_क्रमागत);

/* InBound8 Source */ /* MX-A4 [10:8] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound8_src[] = अणु
	"STO1 ADC MIX L", "STO2 ADC MIX L", "STO3 ADC MIX L", "STO4 ADC MIX L",
	"MONO ADC MIX L", "DACL1 FS"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound8_क्रमागत, RT5677_DSP_INB_CTRL2,
	RT5677_IB8_SRC_SFT, rt5677_inbound8_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib8_src_mux =
	SOC_DAPM_ENUM("InBound8 Source", rt5677_inbound8_क्रमागत);

/* InBound9 Source */ /* MX-A4 [6:4] */
अटल स्थिर अक्षर * स्थिर rt5677_inbound9_src[] = अणु
	"STO1 ADC MIX R", "STO2 ADC MIX R", "STO3 ADC MIX R", "STO4 ADC MIX R",
	"MONO ADC MIX R", "DACR1 FS", "DAC1 FS"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_inbound9_क्रमागत, RT5677_DSP_INB_CTRL2,
	RT5677_IB9_SRC_SFT, rt5677_inbound9_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_ib9_src_mux =
	SOC_DAPM_ENUM("InBound9 Source", rt5677_inbound9_क्रमागत);

/* VAD Source */ /* MX-9F [6:4] */
अटल स्थिर अक्षर * स्थिर rt5677_vad_src[] = अणु
	"STO1 ADC MIX L", "MONO ADC MIX L", "MONO ADC MIX R", "STO2 ADC MIX L",
	"STO3 ADC MIX L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_vad_क्रमागत, RT5677_VAD_CTRL4,
	RT5677_VAD_SRC_SFT, rt5677_vad_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_vad_src_mux =
	SOC_DAPM_ENUM("VAD Source", rt5677_vad_क्रमागत);

/* Sidetone Source */ /* MX-13 [11:9] */
अटल स्थिर अक्षर * स्थिर rt5677_sidetone_src[] = अणु
	"DMIC1 L", "DMIC2 L", "DMIC3 L", "DMIC4 L", "ADC1", "ADC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_sidetone_क्रमागत, RT5677_SIDETONE_CTRL,
	RT5677_ST_SEL_SFT, rt5677_sidetone_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_sidetone_mux =
	SOC_DAPM_ENUM("Sidetone Source", rt5677_sidetone_क्रमागत);

/* DAC1/2 Source */ /* MX-15 [1:0] */
अटल स्थिर अक्षर * स्थिर rt5677_dac12_src[] = अणु
	"STO1 DAC MIX", "MONO DAC MIX", "DD MIX1", "DD MIX2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac12_क्रमागत, RT5677_ANA_DAC1_2_3_SRC,
	RT5677_ANA_DAC1_2_SRC_SEL_SFT, rt5677_dac12_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac12_mux =
	SOC_DAPM_ENUM("Analog DAC1/2 Source", rt5677_dac12_क्रमागत);

/* DAC3 Source */ /* MX-15 [5:4] */
अटल स्थिर अक्षर * स्थिर rt5677_dac3_src[] = अणु
	"MONO DAC MIXL", "MONO DAC MIXR", "DD MIX1L", "DD MIX2L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_dac3_क्रमागत, RT5677_ANA_DAC1_2_3_SRC,
	RT5677_ANA_DAC3_SRC_SEL_SFT, rt5677_dac3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_dac3_mux =
	SOC_DAPM_ENUM("Analog DAC3 Source", rt5677_dac3_क्रमागत);

/* PDM channel Source */ /* MX-31 [13:12][9:8][5:4][1:0] */
अटल स्थिर अक्षर * स्थिर rt5677_pdm_src[] = अणु
	"STO1 DAC MIX", "MONO DAC MIX", "DD MIX1", "DD MIX2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_pdm1_l_क्रमागत, RT5677_PDM_OUT_CTRL,
	RT5677_SEL_PDM1_L_SFT, rt5677_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_pdm1_l_mux =
	SOC_DAPM_ENUM("PDM1 Source", rt5677_pdm1_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_pdm2_l_क्रमागत, RT5677_PDM_OUT_CTRL,
	RT5677_SEL_PDM2_L_SFT, rt5677_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_pdm2_l_mux =
	SOC_DAPM_ENUM("PDM2 Source", rt5677_pdm2_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_pdm1_r_क्रमागत, RT5677_PDM_OUT_CTRL,
	RT5677_SEL_PDM1_R_SFT, rt5677_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_pdm1_r_mux =
	SOC_DAPM_ENUM("PDM1 Source", rt5677_pdm1_r_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_pdm2_r_क्रमागत, RT5677_PDM_OUT_CTRL,
	RT5677_SEL_PDM2_R_SFT, rt5677_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_pdm2_r_mux =
	SOC_DAPM_ENUM("PDM2 Source", rt5677_pdm2_r_क्रमागत);

/* TDM IF1/2 SLB ADC1 Data Selection */ /* MX-3C MX-41 [5:4] MX-08 [1:0] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_adc1_src[] = अणु
	"STO1 ADC MIX", "OB01", "VAD ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc1_क्रमागत, RT5677_TDM1_CTRL2,
	RT5677_IF1_ADC1_SFT, rt5677_अगर12_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc1_mux =
	SOC_DAPM_ENUM("IF1 ADC1 Source", rt5677_अगर1_adc1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc1_क्रमागत, RT5677_TDM2_CTRL2,
	RT5677_IF2_ADC1_SFT, rt5677_अगर12_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc1_mux =
	SOC_DAPM_ENUM("IF2 ADC1 Source", rt5677_अगर2_adc1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_slb_adc1_क्रमागत, RT5677_SLIMBUS_RX,
	RT5677_SLB_ADC1_SFT, rt5677_अगर12_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_slb_adc1_mux =
	SOC_DAPM_ENUM("SLB ADC1 Source", rt5677_slb_adc1_क्रमागत);

/* TDM IF1/2 SLB ADC2 Data Selection */ /* MX-3C MX-41 [7:6] MX-08 [3:2] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_adc2_src[] = अणु
	"STO2 ADC MIX", "OB23"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc2_क्रमागत, RT5677_TDM1_CTRL2,
	RT5677_IF1_ADC2_SFT, rt5677_अगर12_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc2_mux =
	SOC_DAPM_ENUM("IF1 ADC2 Source", rt5677_अगर1_adc2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc2_क्रमागत, RT5677_TDM2_CTRL2,
	RT5677_IF2_ADC2_SFT, rt5677_अगर12_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc2_mux =
	SOC_DAPM_ENUM("IF2 ADC2 Source", rt5677_अगर2_adc2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_slb_adc2_क्रमागत, RT5677_SLIMBUS_RX,
	RT5677_SLB_ADC2_SFT, rt5677_अगर12_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_slb_adc2_mux =
	SOC_DAPM_ENUM("SLB ADC2 Source", rt5677_slb_adc2_क्रमागत);

/* TDM IF1/2 SLB ADC3 Data Selection */ /* MX-3C MX-41 [9:8] MX-08 [5:4] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_adc3_src[] = अणु
	"STO3 ADC MIX", "MONO ADC MIX", "OB45"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc3_क्रमागत, RT5677_TDM1_CTRL2,
	RT5677_IF1_ADC3_SFT, rt5677_अगर12_adc3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc3_mux =
	SOC_DAPM_ENUM("IF1 ADC3 Source", rt5677_अगर1_adc3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc3_क्रमागत, RT5677_TDM2_CTRL2,
	RT5677_IF2_ADC3_SFT, rt5677_अगर12_adc3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc3_mux =
	SOC_DAPM_ENUM("IF2 ADC3 Source", rt5677_अगर2_adc3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_slb_adc3_क्रमागत, RT5677_SLIMBUS_RX,
	RT5677_SLB_ADC3_SFT, rt5677_अगर12_adc3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_slb_adc3_mux =
	SOC_DAPM_ENUM("SLB ADC3 Source", rt5677_slb_adc3_क्रमागत);

/* TDM IF1/2 SLB ADC4 Data Selection */ /* MX-3C MX-41 [11:10] MX-08 [7:6] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_adc4_src[] = अणु
	"STO4 ADC MIX", "OB67", "OB01"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc4_क्रमागत, RT5677_TDM1_CTRL2,
	RT5677_IF1_ADC4_SFT, rt5677_अगर12_adc4_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc4_mux =
	SOC_DAPM_ENUM("IF1 ADC4 Source", rt5677_अगर1_adc4_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc4_क्रमागत, RT5677_TDM2_CTRL2,
	RT5677_IF2_ADC4_SFT, rt5677_अगर12_adc4_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc4_mux =
	SOC_DAPM_ENUM("IF2 ADC4 Source", rt5677_अगर2_adc4_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_slb_adc4_क्रमागत, RT5677_SLIMBUS_RX,
	RT5677_SLB_ADC4_SFT, rt5677_अगर12_adc4_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_slb_adc4_mux =
	SOC_DAPM_ENUM("SLB ADC4 Source", rt5677_slb_adc4_क्रमागत);

/* Interface3/4 ADC Data Input */ /* MX-2F [3:0] MX-30 [7:4] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर34_adc_src[] = अणु
	"STO1 ADC MIX", "STO2 ADC MIX", "STO3 ADC MIX", "STO4 ADC MIX",
	"MONO ADC MIX", "OB01", "OB23", "VAD ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर3_adc_क्रमागत, RT5677_IF3_DATA,
	RT5677_IF3_ADC_IN_SFT, rt5677_अगर34_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर3_adc_mux =
	SOC_DAPM_ENUM("IF3 ADC Source", rt5677_अगर3_adc_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर4_adc_क्रमागत, RT5677_IF4_DATA,
	RT5677_IF4_ADC_IN_SFT, rt5677_अगर34_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर4_adc_mux =
	SOC_DAPM_ENUM("IF4 ADC Source", rt5677_अगर4_adc_क्रमागत);

/* TDM IF1/2 ADC Data Selection */ /* MX-3B MX-40 [7:6][5:4][3:2][1:0] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_adc_swap_src[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc1_swap_क्रमागत, RT5677_TDM1_CTRL1,
	RT5677_IF1_ADC1_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc1_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC1 Swap Source", rt5677_अगर1_adc1_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc2_swap_क्रमागत, RT5677_TDM1_CTRL1,
	RT5677_IF1_ADC2_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc2_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC2 Swap Source", rt5677_अगर1_adc2_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc3_swap_क्रमागत, RT5677_TDM1_CTRL1,
	RT5677_IF1_ADC3_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc3_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC3 Swap Source", rt5677_अगर1_adc3_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc4_swap_क्रमागत, RT5677_TDM1_CTRL1,
	RT5677_IF1_ADC4_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc4_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC4 Swap Source", rt5677_अगर1_adc4_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc1_swap_क्रमागत, RT5677_TDM2_CTRL1,
	RT5677_IF1_ADC2_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc1_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC2 Swap Source", rt5677_अगर2_adc1_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc2_swap_क्रमागत, RT5677_TDM2_CTRL1,
	RT5677_IF2_ADC2_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc2_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC2 Swap Source", rt5677_अगर2_adc2_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc3_swap_क्रमागत, RT5677_TDM2_CTRL1,
	RT5677_IF2_ADC3_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc3_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC3 Swap Source", rt5677_अगर2_adc3_swap_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc4_swap_क्रमागत, RT5677_TDM2_CTRL1,
	RT5677_IF2_ADC4_SWAP_SFT, rt5677_अगर12_adc_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc4_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC4 Swap Source", rt5677_अगर2_adc4_swap_क्रमागत);

/* TDM IF1 ADC Data Selection */ /* MX-3C [2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर1_adc_tdm_swap_src[] = अणु
	"1/2/3/4", "2/1/3/4", "2/3/1/4", "4/1/2/3", "1/3/2/4", "1/4/2/3",
	"3/1/2/4", "3/4/1/2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_adc_tdm_swap_क्रमागत, RT5677_TDM1_CTRL2,
	RT5677_IF1_ADC_CTRL_SFT, rt5677_अगर1_adc_tdm_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_adc_tdm_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC TDM Swap Source", rt5677_अगर1_adc_tdm_swap_क्रमागत);

/* TDM IF2 ADC Data Selection */ /* MX-41[2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर2_adc_tdm_swap_src[] = अणु
	"1/2/3/4", "2/1/3/4", "3/1/2/4", "4/1/2/3", "1/3/2/4", "1/4/2/3",
	"2/3/1/4", "3/4/1/2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_adc_tdm_swap_क्रमागत, RT5677_TDM2_CTRL2,
	RT5677_IF2_ADC_CTRL_SFT, rt5677_अगर2_adc_tdm_swap_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_adc_tdm_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC TDM Swap Source", rt5677_अगर2_adc_tdm_swap_क्रमागत);

/* TDM IF1/2 DAC Data Selection */ /* MX-3E[14:12][10:8][6:4][2:0]
					MX-3F[14:12][10:8][6:4][2:0]
					MX-43[14:12][10:8][6:4][2:0]
					MX-44[14:12][10:8][6:4][2:0] */
अटल स्थिर अक्षर * स्थिर rt5677_अगर12_dac_tdm_sel_src[] = अणु
	"Slot0", "Slot1", "Slot2", "Slot3", "Slot4", "Slot5", "Slot6", "Slot7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac0_tdm_sel_क्रमागत, RT5677_TDM1_CTRL4,
	RT5677_IF1_DAC0_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac0_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC0 TDM Source", rt5677_अगर1_dac0_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac1_tdm_sel_क्रमागत, RT5677_TDM1_CTRL4,
	RT5677_IF1_DAC1_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac1_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC1 TDM Source", rt5677_अगर1_dac1_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac2_tdm_sel_क्रमागत, RT5677_TDM1_CTRL4,
	RT5677_IF1_DAC2_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac2_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC2 TDM Source", rt5677_अगर1_dac2_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac3_tdm_sel_क्रमागत, RT5677_TDM1_CTRL4,
	RT5677_IF1_DAC3_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac3_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC3 TDM Source", rt5677_अगर1_dac3_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac4_tdm_sel_क्रमागत, RT5677_TDM1_CTRL5,
	RT5677_IF1_DAC4_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac4_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC4 TDM Source", rt5677_अगर1_dac4_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac5_tdm_sel_क्रमागत, RT5677_TDM1_CTRL5,
	RT5677_IF1_DAC5_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac5_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC5 TDM Source", rt5677_अगर1_dac5_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac6_tdm_sel_क्रमागत, RT5677_TDM1_CTRL5,
	RT5677_IF1_DAC6_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac6_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC6 TDM Source", rt5677_अगर1_dac6_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर1_dac7_tdm_sel_क्रमागत, RT5677_TDM1_CTRL5,
	RT5677_IF1_DAC7_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर1_dac7_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC7 TDM Source", rt5677_अगर1_dac7_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac0_tdm_sel_क्रमागत, RT5677_TDM2_CTRL4,
	RT5677_IF2_DAC0_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac0_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC0 TDM Source", rt5677_अगर2_dac0_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac1_tdm_sel_क्रमागत, RT5677_TDM2_CTRL4,
	RT5677_IF2_DAC1_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac1_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC1 TDM Source", rt5677_अगर2_dac1_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac2_tdm_sel_क्रमागत, RT5677_TDM2_CTRL4,
	RT5677_IF2_DAC2_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac2_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC2 TDM Source", rt5677_अगर2_dac2_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac3_tdm_sel_क्रमागत, RT5677_TDM2_CTRL4,
	RT5677_IF2_DAC3_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac3_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC3 TDM Source", rt5677_अगर2_dac3_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac4_tdm_sel_क्रमागत, RT5677_TDM2_CTRL5,
	RT5677_IF2_DAC4_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac4_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC4 TDM Source", rt5677_अगर2_dac4_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac5_tdm_sel_क्रमागत, RT5677_TDM2_CTRL5,
	RT5677_IF2_DAC5_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac5_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC5 TDM Source", rt5677_अगर2_dac5_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac6_tdm_sel_क्रमागत, RT5677_TDM2_CTRL5,
	RT5677_IF2_DAC6_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac6_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC6 TDM Source", rt5677_अगर2_dac6_tdm_sel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5677_अगर2_dac7_tdm_sel_क्रमागत, RT5677_TDM2_CTRL5,
	RT5677_IF2_DAC7_SFT, rt5677_अगर12_dac_tdm_sel_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5677_अगर2_dac7_tdm_sel_mux =
	SOC_DAPM_ENUM("IF2 DAC7 TDM Source", rt5677_अगर2_dac7_tdm_sel_क्रमागत);

अटल पूर्णांक rt5677_bst1_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_BST1_P, RT5677_PWR_BST1_P);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_BST1_P, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_bst2_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_BST2_P, RT5677_PWR_BST2_P);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_BST2_P, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_pll1_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PLL1_CTRL2, 0x2, 0x2);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PLL1_CTRL2, 0x2, 0x0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_pll2_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PLL2_CTRL2, 0x2, 0x2);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PLL2_CTRL2, 0x2, 0x0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_micbias1_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_CLK_MB1 | RT5677_PWR_PP_MB1 |
			RT5677_PWR_CLK_MB, RT5677_PWR_CLK_MB1 |
			RT5677_PWR_PP_MB1 | RT5677_PWR_CLK_MB);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_CLK_MB1 | RT5677_PWR_PP_MB1 |
			RT5677_PWR_CLK_MB, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_अगर1_adc_tdm_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_पढ़ो(rt5677->regmap, RT5677_TDM1_CTRL2, &value);
		अगर (value & RT5677_IF1_ADC_CTRL_MASK)
			regmap_update_bits(rt5677->regmap, RT5677_TDM1_CTRL1,
				RT5677_IF1_ADC_MODE_MASK,
				RT5677_IF1_ADC_MODE_TDM);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_अगर2_adc_tdm_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_पढ़ो(rt5677->regmap, RT5677_TDM2_CTRL2, &value);
		अगर (value & RT5677_IF2_ADC_CTRL_MASK)
			regmap_update_bits(rt5677->regmap, RT5677_TDM2_CTRL1,
				RT5677_IF2_ADC_MODE_MASK,
				RT5677_IF2_ADC_MODE_TDM);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_vref_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_ON &&
			!rt5677->is_vref_slow) अणु
			mdelay(20);
			regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG1,
				RT5677_PWR_FV1 | RT5677_PWR_FV2,
				RT5677_PWR_FV1 | RT5677_PWR_FV2);
			rt5677->is_vref_slow = true;
		पूर्ण
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_filter_घातer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(50);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5677_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL1", RT5677_PWR_ANLG2, RT5677_PWR_PLL1_BIT,
		0, rt5677_set_pll1_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("PLL2", RT5677_PWR_ANLG2, RT5677_PWR_PLL2_BIT,
		0, rt5677_set_pll2_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMU),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5677_ASRC_1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5677_ASRC_1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S3 ASRC", 1, RT5677_ASRC_1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S4 ASRC", 1, RT5677_ASRC_1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO ASRC", 1, RT5677_ASRC_2, 14, 0,
		rt5677_filter_घातer_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO2 L ASRC", 1, RT5677_ASRC_2, 13, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO2 R ASRC", 1, RT5677_ASRC_2, 12, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO3 L ASRC", 1, RT5677_ASRC_1, 15, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO3 R ASRC", 1, RT5677_ASRC_1, 14, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO4 L ASRC", 1, RT5677_ASRC_1, 13, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO4 R ASRC", 1, RT5677_ASRC_1, 12, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO1 ASRC", 1, RT5677_ASRC_2, 11, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO2 ASRC", 1, RT5677_ASRC_2, 10, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO3 ASRC", 1, RT5677_ASRC_2, 9, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO4 ASRC", 1, RT5677_ASRC_2, 8, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO L ASRC", 1, RT5677_ASRC_2, 7, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO R ASRC", 1, RT5677_ASRC_2, 6, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5677_ASRC_2, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO2 ASRC", 1, RT5677_ASRC_2, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO3 ASRC", 1, RT5677_ASRC_2, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO4 ASRC", 1, RT5677_ASRC_2, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO L ASRC", 1, RT5677_ASRC_2, 1, 0, शून्य,
		0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO R ASRC", 1, RT5677_ASRC_2, 0, 0, शून्य,
		0),

	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5677_PWR_ANLG2, RT5677_PWR_MB1_BIT,
		0, rt5677_set_micbias1_event, SND_SOC_DAPM_PRE_PMD |
		SND_SOC_DAPM_POST_PMU),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),
	SND_SOC_DAPM_INPUT("DMIC L2"),
	SND_SOC_DAPM_INPUT("DMIC R2"),
	SND_SOC_DAPM_INPUT("DMIC L3"),
	SND_SOC_DAPM_INPUT("DMIC R3"),
	SND_SOC_DAPM_INPUT("DMIC L4"),
	SND_SOC_DAPM_INPUT("DMIC R4"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	SND_SOC_DAPM_INPUT("Haptic Generator"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DMIC1 power", RT5677_DMIC_CTRL1,
		RT5677_DMIC_1_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC2 power", RT5677_DMIC_CTRL1,
		RT5677_DMIC_2_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC3 power", RT5677_DMIC_CTRL1,
		RT5677_DMIC_3_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC4 power", RT5677_DMIC_CTRL2,
		RT5677_DMIC_4_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		set_dmic_clk, SND_SOC_DAPM_PRE_PMU),

	/* Boost */
	SND_SOC_DAPM_PGA_E("BST1", RT5677_PWR_ANLG2,
		RT5677_PWR_BST1_BIT, 0, शून्य, 0, rt5677_bst1_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST2", RT5677_PWR_ANLG2,
		RT5677_PWR_BST2_BIT, 0, शून्य, 0, rt5677_bst2_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 1", शून्य, SND_SOC_NOPM,
		0, 0),
	SND_SOC_DAPM_ADC("ADC 2", शून्य, SND_SOC_NOPM,
		0, 0),
	SND_SOC_DAPM_PGA("ADC 1_2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("ADC 1 power", RT5677_PWR_DIG1,
		RT5677_PWR_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC 2 power", RT5677_PWR_DIG1,
		RT5677_PWR_ADC_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 clock", RT5677_PWR_DIG1,
		RT5677_PWR_ADCFED1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 clock", RT5677_PWR_DIG1,
		RT5677_PWR_ADCFED2_BIT, 0, शून्य, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto1_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto1_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo2 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto2_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto2_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto2_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC LR Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto2_adc_lr_mux),
	SND_SOC_DAPM_MUX("Stereo3 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto3_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo3 ADC1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto3_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo3 ADC2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto3_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo4 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto4_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo4 ADC1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto4_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo4 ADC2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_sto4_adc2_mux),
	SND_SOC_DAPM_MUX("Mono DMIC L Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_dmic_l_mux),
	SND_SOC_DAPM_MUX("Mono DMIC R Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_dmic_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC2 L Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_adc2_l_mux),
	SND_SOC_DAPM_MUX("Mono ADC1 L Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_adc1_l_mux),
	SND_SOC_DAPM_MUX("Mono ADC1 R Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_adc1_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC2 R Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_mono_adc2_r_mux),

	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("adc stereo1 filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("adc stereo2 filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_S2F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("adc stereo3 filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_S3F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("adc stereo4 filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_S4F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_sto1_adc_l_mix, ARRAY_SIZE(rt5677_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_sto1_adc_r_mix, ARRAY_SIZE(rt5677_sto1_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_sto2_adc_l_mix, ARRAY_SIZE(rt5677_sto2_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_sto2_adc_r_mix, ARRAY_SIZE(rt5677_sto2_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Sto3 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_sto3_adc_l_mix, ARRAY_SIZE(rt5677_sto3_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto3 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_sto3_adc_r_mix, ARRAY_SIZE(rt5677_sto3_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Sto4 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_sto4_adc_l_mix, ARRAY_SIZE(rt5677_sto4_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto4 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_sto4_adc_r_mix, ARRAY_SIZE(rt5677_sto4_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("adc mono left filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_mono_adc_l_mix, ARRAY_SIZE(rt5677_mono_adc_l_mix)),
	SND_SOC_DAPM_SUPPLY("adc mono right filter", RT5677_PWR_DIG2,
		RT5677_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_mono_adc_r_mix, ARRAY_SIZE(rt5677_mono_adc_r_mix)),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo3 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo3 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo3 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo4 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo4 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo4 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Sto2 ADC LR MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DSP */
	SND_SOC_DAPM_MUX("IB9 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib9_src_mux),
	SND_SOC_DAPM_MUX("IB8 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib8_src_mux),
	SND_SOC_DAPM_MUX("IB7 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib7_src_mux),
	SND_SOC_DAPM_MUX("IB6 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib6_src_mux),
	SND_SOC_DAPM_MUX("IB45 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib45_src_mux),
	SND_SOC_DAPM_MUX("IB23 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib23_src_mux),
	SND_SOC_DAPM_MUX("IB01 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib01_src_mux),
	SND_SOC_DAPM_MUX("IB45 Bypass Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib45_bypass_src_mux),
	SND_SOC_DAPM_MUX("IB23 Bypass Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib23_bypass_src_mux),
	SND_SOC_DAPM_MUX("IB01 Bypass Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ib01_bypass_src_mux),
	SND_SOC_DAPM_MUX("OB23 Bypass Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ob23_bypass_src_mux),
	SND_SOC_DAPM_MUX("OB01 Bypass Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_ob01_bypass_src_mux),

	SND_SOC_DAPM_PGA("OB45", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OB67", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("OutBound2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OutBound3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OutBound4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OutBound5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OutBound6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OutBound7", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5677_PWR_DIG1,
		RT5677_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC7", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC01", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC23", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC45", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC67", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("I2S2", RT5677_PWR_DIG1,
		RT5677_PWR_I2S2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC7", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC01", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC23", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC45", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC67", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("I2S3", RT5677_PWR_DIG1,
		RT5677_PWR_I2S3_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("I2S4", RT5677_PWR_DIG1,
		RT5677_PWR_I2S4_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF4 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("SLB", RT5677_PWR_DIG1,
		RT5677_PWR_SLB_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC6", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC7", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC01", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC23", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC45", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB DAC67", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SLB ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("IF1 ADC1 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc1_mux),
	SND_SOC_DAPM_MUX("IF1 ADC2 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc2_mux),
	SND_SOC_DAPM_MUX("IF1 ADC3 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc3_mux),
	SND_SOC_DAPM_MUX("IF1 ADC4 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc4_mux),
	SND_SOC_DAPM_MUX("IF1 ADC1 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc1_swap_mux),
	SND_SOC_DAPM_MUX("IF1 ADC2 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc2_swap_mux),
	SND_SOC_DAPM_MUX("IF1 ADC3 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc3_swap_mux),
	SND_SOC_DAPM_MUX("IF1 ADC4 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc4_swap_mux),
	SND_SOC_DAPM_MUX_E("IF1 ADC TDM Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_adc_tdm_swap_mux, rt5677_अगर1_adc_tdm_event,
			SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MUX("IF2 ADC1 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc1_mux),
	SND_SOC_DAPM_MUX("IF2 ADC2 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc2_mux),
	SND_SOC_DAPM_MUX("IF2 ADC3 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc3_mux),
	SND_SOC_DAPM_MUX("IF2 ADC4 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc4_mux),
	SND_SOC_DAPM_MUX("IF2 ADC1 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc1_swap_mux),
	SND_SOC_DAPM_MUX("IF2 ADC2 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc2_swap_mux),
	SND_SOC_DAPM_MUX("IF2 ADC3 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc3_swap_mux),
	SND_SOC_DAPM_MUX("IF2 ADC4 Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc4_swap_mux),
	SND_SOC_DAPM_MUX_E("IF2 ADC TDM Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_adc_tdm_swap_mux, rt5677_अगर2_adc_tdm_event,
			SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MUX("IF3 ADC Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर3_adc_mux),
	SND_SOC_DAPM_MUX("IF4 ADC Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर4_adc_mux),
	SND_SOC_DAPM_MUX("SLB ADC1 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_slb_adc1_mux),
	SND_SOC_DAPM_MUX("SLB ADC2 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_slb_adc2_mux),
	SND_SOC_DAPM_MUX("SLB ADC3 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_slb_adc3_mux),
	SND_SOC_DAPM_MUX("SLB ADC4 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_slb_adc4_mux),

	SND_SOC_DAPM_MUX("IF1 DAC0 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac0_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC1 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac1_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC2 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac2_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC3 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac3_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC4 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac4_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC5 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac5_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC6 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac6_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF1 DAC7 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर1_dac7_tdm_sel_mux),

	SND_SOC_DAPM_MUX("IF2 DAC0 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac0_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC1 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac1_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC2 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac2_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC3 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac3_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC4 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac4_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC5 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac5_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC6 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac6_tdm_sel_mux),
	SND_SOC_DAPM_MUX("IF2 DAC7 Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_अगर2_dac7_tdm_sel_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3RX", "AIF3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "AIF3 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF4RX", "AIF4 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF4TX", "AIF4 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SLBRX", "SLIMBus Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SLBTX", "SLIMBus Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DSPTX", "DSP Buffer", 0, SND_SOC_NOPM, 0, 0),

	/* Sidetone Mux */
	SND_SOC_DAPM_MUX("Sidetone Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_sidetone_mux),
	SND_SOC_DAPM_SUPPLY("Sidetone Power", RT5677_SIDETONE_CTRL,
		RT5677_ST_EN_SFT, 0, शून्य, 0),

	/* VAD Mux*/
	SND_SOC_DAPM_MUX("VAD ADC Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_vad_src_mux),

	/* Tensilica DSP */
	SND_SOC_DAPM_PGA("Tensilica DSP", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("OB01 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_01_mix, ARRAY_SIZE(rt5677_ob_01_mix)),
	SND_SOC_DAPM_MIXER("OB23 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_23_mix, ARRAY_SIZE(rt5677_ob_23_mix)),
	SND_SOC_DAPM_MIXER("OB4 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_4_mix, ARRAY_SIZE(rt5677_ob_4_mix)),
	SND_SOC_DAPM_MIXER("OB5 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_5_mix, ARRAY_SIZE(rt5677_ob_5_mix)),
	SND_SOC_DAPM_MIXER("OB6 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_6_mix, ARRAY_SIZE(rt5677_ob_6_mix)),
	SND_SOC_DAPM_MIXER("OB7 MIX", SND_SOC_NOPM, 0, 0,
		rt5677_ob_7_mix, ARRAY_SIZE(rt5677_ob_7_mix)),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_dac_l_mix, ARRAY_SIZE(rt5677_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_dac_r_mix, ARRAY_SIZE(rt5677_dac_r_mix)),
	SND_SOC_DAPM_PGA("DAC1 FS", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DAC Mux */
	SND_SOC_DAPM_MUX("DAC1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_dac1_mux),
	SND_SOC_DAPM_MUX("ADDA1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_adda1_mux),
	SND_SOC_DAPM_MUX("DAC12 SRC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_dac12_mux),
	SND_SOC_DAPM_MUX("DAC3 SRC Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_dac3_mux),

	/* DAC2 channel Mux */
	SND_SOC_DAPM_MUX("DAC2 L Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_dac2_l_mux),
	SND_SOC_DAPM_MUX("DAC2 R Mux", SND_SOC_NOPM, 0, 0,
				&rt5677_dac2_r_mux),

	/* DAC3 channel Mux */
	SND_SOC_DAPM_MUX("DAC3 L Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_dac3_l_mux),
	SND_SOC_DAPM_MUX("DAC3 R Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_dac3_r_mux),

	/* DAC4 channel Mux */
	SND_SOC_DAPM_MUX("DAC4 L Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_dac4_l_mux),
	SND_SOC_DAPM_MUX("DAC4 R Mux", SND_SOC_NOPM, 0, 0,
			&rt5677_dac4_r_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("dac stereo1 filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_S1F_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono2 left filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M2F_L_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono2 right filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M2F_R_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono3 left filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M3F_L_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono3 right filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M3F_R_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono4 left filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M4F_L_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("dac mono4 right filter", RT5677_PWR_DIG2,
		RT5677_PWR_DAC_M4F_R_BIT, 0, rt5677_filter_घातer_event,
		SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_sto1_dac_l_mix, ARRAY_SIZE(rt5677_sto1_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_sto1_dac_r_mix, ARRAY_SIZE(rt5677_sto1_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_mono_dac_l_mix, ARRAY_SIZE(rt5677_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_mono_dac_r_mix, ARRAY_SIZE(rt5677_mono_dac_r_mix)),
	SND_SOC_DAPM_MIXER("DD1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_dd1_l_mix, ARRAY_SIZE(rt5677_dd1_l_mix)),
	SND_SOC_DAPM_MIXER("DD1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_dd1_r_mix, ARRAY_SIZE(rt5677_dd1_r_mix)),
	SND_SOC_DAPM_MIXER("DD2 MIXL", SND_SOC_NOPM, 0, 0,
		rt5677_dd2_l_mix, ARRAY_SIZE(rt5677_dd2_l_mix)),
	SND_SOC_DAPM_MIXER("DD2 MIXR", SND_SOC_NOPM, 0, 0,
		rt5677_dd2_r_mix, ARRAY_SIZE(rt5677_dd2_r_mix)),
	SND_SOC_DAPM_PGA("Stereo DAC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono DAC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DD1 MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DD2 MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC 1", शून्य, RT5677_PWR_DIG1,
		RT5677_PWR_DAC1_BIT, 0),
	SND_SOC_DAPM_DAC("DAC 2", शून्य, RT5677_PWR_DIG1,
		RT5677_PWR_DAC2_BIT, 0),
	SND_SOC_DAPM_DAC("DAC 3", शून्य, RT5677_PWR_DIG1,
		RT5677_PWR_DAC3_BIT, 0),

	/* PDM */
	SND_SOC_DAPM_SUPPLY("PDM1 Power", RT5677_PWR_DIG2,
		RT5677_PWR_PDM1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PDM2 Power", RT5677_PWR_DIG2,
		RT5677_PWR_PDM2_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("PDM1 L Mux", RT5677_PDM_OUT_CTRL, RT5677_M_PDM1_L_SFT,
		1, &rt5677_pdm1_l_mux),
	SND_SOC_DAPM_MUX("PDM1 R Mux", RT5677_PDM_OUT_CTRL, RT5677_M_PDM1_R_SFT,
		1, &rt5677_pdm1_r_mux),
	SND_SOC_DAPM_MUX("PDM2 L Mux", RT5677_PDM_OUT_CTRL, RT5677_M_PDM2_L_SFT,
		1, &rt5677_pdm2_l_mux),
	SND_SOC_DAPM_MUX("PDM2 R Mux", RT5677_PDM_OUT_CTRL, RT5677_M_PDM2_R_SFT,
		1, &rt5677_pdm2_r_mux),

	SND_SOC_DAPM_PGA_S("LOUT1 amp", 0, RT5677_PWR_ANLG1, RT5677_PWR_LO1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("LOUT2 amp", 0, RT5677_PWR_ANLG1, RT5677_PWR_LO2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("LOUT3 amp", 0, RT5677_PWR_ANLG1, RT5677_PWR_LO3_BIT,
		0, शून्य, 0),

	SND_SOC_DAPM_PGA_S("LOUT1 vref", 1, SND_SOC_NOPM, 0, 0,
		rt5677_vref_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT2 vref", 1, SND_SOC_NOPM, 0, 0,
		rt5677_vref_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT3 vref", 1, SND_SOC_NOPM, 0, 0,
		rt5677_vref_event, SND_SOC_DAPM_POST_PMU),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("LOUT3"),
	SND_SOC_DAPM_OUTPUT("PDM1L"),
	SND_SOC_DAPM_OUTPUT("PDM1R"),
	SND_SOC_DAPM_OUTPUT("PDM2L"),
	SND_SOC_DAPM_OUTPUT("PDM2R"),

	SND_SOC_DAPM_POST("vref", rt5677_vref_event),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5677_dapm_routes[] = अणु
	अणु "Stereo1 DMIC Mux", शून्य, "DMIC STO1 ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "Stereo2 DMIC Mux", शून्य, "DMIC STO2 ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "Stereo3 DMIC Mux", शून्य, "DMIC STO3 ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "Stereo4 DMIC Mux", शून्य, "DMIC STO4 ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "Mono DMIC L Mux", शून्य, "DMIC MONO L ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "Mono DMIC R Mux", शून्य, "DMIC MONO R ASRC", rt5677_dmic_use_asrc पूर्ण,
	अणु "I2S1", शून्य, "I2S1 ASRC", can_use_asrcपूर्ण,
	अणु "I2S2", शून्य, "I2S2 ASRC", can_use_asrcपूर्ण,
	अणु "I2S3", शून्य, "I2S3 ASRC", can_use_asrcपूर्ण,
	अणु "I2S4", शून्य, "I2S4 ASRC", can_use_asrcपूर्ण,

	अणु "dac stereo1 filter", शून्य, "DAC STO ASRC", is_using_asrc पूर्ण,
	अणु "dac mono2 left filter", शून्य, "DAC MONO2 L ASRC", is_using_asrc पूर्ण,
	अणु "dac mono2 right filter", शून्य, "DAC MONO2 R ASRC", is_using_asrc पूर्ण,
	अणु "dac mono3 left filter", शून्य, "DAC MONO3 L ASRC", is_using_asrc पूर्ण,
	अणु "dac mono3 right filter", शून्य, "DAC MONO3 R ASRC", is_using_asrc पूर्ण,
	अणु "dac mono4 left filter", शून्य, "DAC MONO4 L ASRC", is_using_asrc पूर्ण,
	अणु "dac mono4 right filter", शून्य, "DAC MONO4 R ASRC", is_using_asrc पूर्ण,
	अणु "adc stereo1 filter", शून्य, "ADC STO1 ASRC", is_using_asrc पूर्ण,
	अणु "adc stereo2 filter", शून्य, "ADC STO2 ASRC", is_using_asrc पूर्ण,
	अणु "adc stereo3 filter", शून्य, "ADC STO3 ASRC", is_using_asrc पूर्ण,
	अणु "adc stereo4 filter", शून्य, "ADC STO4 ASRC", is_using_asrc पूर्ण,
	अणु "adc mono left filter", शून्य, "ADC MONO L ASRC", is_using_asrc पूर्ण,
	अणु "adc mono right filter", शून्य, "ADC MONO R ASRC", is_using_asrc पूर्ण,

	अणु "DMIC1", शून्य, "DMIC L1" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC R1" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC L2" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC R2" पूर्ण,
	अणु "DMIC3", शून्य, "DMIC L3" पूर्ण,
	अणु "DMIC3", शून्य, "DMIC R3" पूर्ण,
	अणु "DMIC4", शून्य, "DMIC L4" पूर्ण,
	अणु "DMIC4", शून्य, "DMIC R4" पूर्ण,

	अणु "DMIC L1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L3", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R3", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L4", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R4", शून्य, "DMIC CLK" पूर्ण,

	अणु "DMIC L1", शून्य, "DMIC1 power" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC1 power" पूर्ण,
	अणु "DMIC L3", शून्य, "DMIC3 power" पूर्ण,
	अणु "DMIC R3", शून्य, "DMIC3 power" पूर्ण,
	अणु "DMIC L4", शून्य, "DMIC4 power" पूर्ण,
	अणु "DMIC R4", शून्य, "DMIC4 power" पूर्ण,

	अणु "BST1", शून्य, "IN1P" पूर्ण,
	अणु "BST1", शून्य, "IN1N" पूर्ण,
	अणु "BST2", शून्य, "IN2P" पूर्ण,
	अणु "BST2", शून्य, "IN2N" पूर्ण,

	अणु "IN1P", शून्य, "MICBIAS1" पूर्ण,
	अणु "IN1N", शून्य, "MICBIAS1" पूर्ण,
	अणु "IN2P", शून्य, "MICBIAS1" पूर्ण,
	अणु "IN2N", शून्य, "MICBIAS1" पूर्ण,

	अणु "ADC 1", शून्य, "BST1" पूर्ण,
	अणु "ADC 1", शून्य, "ADC 1 power" पूर्ण,
	अणु "ADC 1", शून्य, "ADC1 clock" पूर्ण,
	अणु "ADC 2", शून्य, "BST2" पूर्ण,
	अणु "ADC 2", शून्य, "ADC 2 power" पूर्ण,
	अणु "ADC 2", शून्य, "ADC2 clock" पूर्ण,

	अणु "Stereo1 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "Stereo2 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "Stereo3 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo3 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo3 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Stereo3 DMIC Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "Stereo4 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo4 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo4 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Stereo4 DMIC Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "Mono DMIC L Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "Mono DMIC R Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC3", "DMIC3" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC4", "DMIC4" पूर्ण,

	अणु "ADC 1_2", शून्य, "ADC 1" पूर्ण,
	अणु "ADC 1_2", शून्य, "ADC 2" पूर्ण,

	अणु "Stereo1 ADC1 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo1 ADC1 Mux", "ADC1/2", "ADC 1_2" पूर्ण,
	अणु "Stereo1 ADC1 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo1 ADC2 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo1 ADC2 Mux", "DMIC", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Stereo1 ADC2 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo2 ADC1 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo2 ADC1 Mux", "ADC1/2", "ADC 1_2" पूर्ण,
	अणु "Stereo2 ADC1 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo2 ADC2 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo2 ADC2 Mux", "DMIC", "Stereo2 DMIC Mux" पूर्ण,
	अणु "Stereo2 ADC2 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo3 ADC1 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo3 ADC1 Mux", "ADC1/2", "ADC 1_2" पूर्ण,
	अणु "Stereo3 ADC1 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo3 ADC2 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo3 ADC2 Mux", "DMIC", "Stereo3 DMIC Mux" पूर्ण,
	अणु "Stereo3 ADC2 Mux", "Stereo DAC MIX", "Stereo DAC MIX" पूर्ण,

	अणु "Stereo4 ADC1 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo4 ADC1 Mux", "ADC1/2", "ADC 1_2" पूर्ण,
	अणु "Stereo4 ADC1 Mux", "DD MIX2", "DD2 MIX" पूर्ण,

	अणु "Stereo4 ADC2 Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "Stereo4 ADC2 Mux", "DMIC", "Stereo3 DMIC Mux" पूर्ण,
	अणु "Stereo4 ADC2 Mux", "DD MIX2", "DD2 MIX" पूर्ण,

	अणु "Mono ADC2 L Mux", "DD MIX1L", "DD1 MIXL" पूर्ण,
	अणु "Mono ADC2 L Mux", "DMIC", "Mono DMIC L Mux" पूर्ण,
	अणु "Mono ADC2 L Mux", "MONO DAC MIXL", "Mono DAC MIXL" पूर्ण,

	अणु "Mono ADC1 L Mux", "DD MIX1L", "DD1 MIXL" पूर्ण,
	अणु "Mono ADC1 L Mux", "ADC1", "ADC 1" पूर्ण,
	अणु "Mono ADC1 L Mux", "MONO DAC MIXL", "Mono DAC MIXL" पूर्ण,

	अणु "Mono ADC1 R Mux", "DD MIX1R", "DD1 MIXR" पूर्ण,
	अणु "Mono ADC1 R Mux", "ADC2", "ADC 2" पूर्ण,
	अणु "Mono ADC1 R Mux", "MONO DAC MIXR", "Mono DAC MIXR" पूर्ण,

	अणु "Mono ADC2 R Mux", "DD MIX1R", "DD1 MIXR" पूर्ण,
	अणु "Mono ADC2 R Mux", "DMIC", "Mono DMIC R Mux" पूर्ण,
	अणु "Mono ADC2 R Mux", "MONO DAC MIXR", "Mono DAC MIXR" पूर्ण,

	अणु "Sto1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC2 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC2 Mux" पूर्ण,

	अणु "Stereo1 ADC MIXL", शून्य, "Sto1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIXL", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "Sto1 ADC MIXR" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXR" पूर्ण,

	अणु "Sto2 ADC MIXL", "ADC1 Switch", "Stereo2 ADC1 Mux" पूर्ण,
	अणु "Sto2 ADC MIXL", "ADC2 Switch", "Stereo2 ADC2 Mux" पूर्ण,
	अणु "Sto2 ADC MIXR", "ADC1 Switch", "Stereo2 ADC1 Mux" पूर्ण,
	अणु "Sto2 ADC MIXR", "ADC2 Switch", "Stereo2 ADC2 Mux" पूर्ण,

	अणु "Sto2 ADC LR MIX", शून्य, "Sto2 ADC MIXL" पूर्ण,
	अणु "Sto2 ADC LR MIX", शून्य, "Sto2 ADC MIXR" पूर्ण,

	अणु "Stereo2 ADC LR Mux", "L", "Sto2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC LR Mux", "LR", "Sto2 ADC LR MIX" पूर्ण,

	अणु "Stereo2 ADC MIXL", शून्य, "Stereo2 ADC LR Mux" पूर्ण,
	अणु "Stereo2 ADC MIXL", शून्य, "adc stereo2 filter" पूर्ण,
	अणु "Stereo2 ADC MIXR", शून्य, "Sto2 ADC MIXR" पूर्ण,
	अणु "Stereo2 ADC MIXR", शून्य, "adc stereo2 filter" पूर्ण,
	अणु "adc stereo2 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXR" पूर्ण,

	अणु "Sto3 ADC MIXL", "ADC1 Switch", "Stereo3 ADC1 Mux" पूर्ण,
	अणु "Sto3 ADC MIXL", "ADC2 Switch", "Stereo3 ADC2 Mux" पूर्ण,
	अणु "Sto3 ADC MIXR", "ADC1 Switch", "Stereo3 ADC1 Mux" पूर्ण,
	अणु "Sto3 ADC MIXR", "ADC2 Switch", "Stereo3 ADC2 Mux" पूर्ण,

	अणु "Stereo3 ADC MIXL", शून्य, "Sto3 ADC MIXL" पूर्ण,
	अणु "Stereo3 ADC MIXL", शून्य, "adc stereo3 filter" पूर्ण,
	अणु "Stereo3 ADC MIXR", शून्य, "Sto3 ADC MIXR" पूर्ण,
	अणु "Stereo3 ADC MIXR", शून्य, "adc stereo3 filter" पूर्ण,
	अणु "adc stereo3 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo3 ADC MIX", शून्य, "Stereo3 ADC MIXL" पूर्ण,
	अणु "Stereo3 ADC MIX", शून्य, "Stereo3 ADC MIXR" पूर्ण,

	अणु "Sto4 ADC MIXL", "ADC1 Switch", "Stereo4 ADC1 Mux" पूर्ण,
	अणु "Sto4 ADC MIXL", "ADC2 Switch", "Stereo4 ADC2 Mux" पूर्ण,
	अणु "Sto4 ADC MIXR", "ADC1 Switch", "Stereo4 ADC1 Mux" पूर्ण,
	अणु "Sto4 ADC MIXR", "ADC2 Switch", "Stereo4 ADC2 Mux" पूर्ण,

	अणु "Stereo4 ADC MIXL", शून्य, "Sto4 ADC MIXL" पूर्ण,
	अणु "Stereo4 ADC MIXL", शून्य, "adc stereo4 filter" पूर्ण,
	अणु "Stereo4 ADC MIXR", शून्य, "Sto4 ADC MIXR" पूर्ण,
	अणु "Stereo4 ADC MIXR", शून्य, "adc stereo4 filter" पूर्ण,
	अणु "adc stereo4 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo4 ADC MIX", शून्य, "Stereo4 ADC MIXL" पूर्ण,
	अणु "Stereo4 ADC MIX", शून्य, "Stereo4 ADC MIXR" पूर्ण,

	अणु "Mono ADC MIXL", "ADC1 Switch", "Mono ADC1 L Mux" पूर्ण,
	अणु "Mono ADC MIXL", "ADC2 Switch", "Mono ADC2 L Mux" पूर्ण,
	अणु "Mono ADC MIXL", शून्य, "adc mono left filter" पूर्ण,
	अणु "adc mono left filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIXR", "ADC1 Switch", "Mono ADC1 R Mux" पूर्ण,
	अणु "Mono ADC MIXR", "ADC2 Switch", "Mono ADC2 R Mux" पूर्ण,
	अणु "Mono ADC MIXR", शून्य, "adc mono right filter" पूर्ण,
	अणु "adc mono right filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIX", शून्य, "Mono ADC MIXL" पूर्ण,
	अणु "Mono ADC MIX", शून्य, "Mono ADC MIXR" पूर्ण,

	अणु "VAD ADC Mux", "STO1 ADC MIX L", "Stereo1 ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "MONO ADC MIX L", "Mono ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "MONO ADC MIX R", "Mono ADC MIXR" पूर्ण,
	अणु "VAD ADC Mux", "STO2 ADC MIX L", "Stereo2 ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "STO3 ADC MIX L", "Stereo3 ADC MIXL" पूर्ण,

	अणु "IF1 ADC1 Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "IF1 ADC1 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,
	अणु "IF1 ADC1 Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "IF1 ADC2 Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "IF1 ADC2 Mux", "OB23", "OB23 Bypass Mux" पूर्ण,

	अणु "IF1 ADC3 Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "IF1 ADC3 Mux", "MONO ADC MIX", "Mono ADC MIX" पूर्ण,
	अणु "IF1 ADC3 Mux", "OB45", "OB45" पूर्ण,

	अणु "IF1 ADC4 Mux", "STO4 ADC MIX", "Stereo4 ADC MIX" पूर्ण,
	अणु "IF1 ADC4 Mux", "OB67", "OB67" पूर्ण,
	अणु "IF1 ADC4 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,

	अणु "IF1 ADC1 Swap Mux", "L/R", "IF1 ADC1 Mux" पूर्ण,
	अणु "IF1 ADC1 Swap Mux", "R/L", "IF1 ADC1 Mux" पूर्ण,
	अणु "IF1 ADC1 Swap Mux", "L/L", "IF1 ADC1 Mux" पूर्ण,
	अणु "IF1 ADC1 Swap Mux", "R/R", "IF1 ADC1 Mux" पूर्ण,

	अणु "IF1 ADC2 Swap Mux", "L/R", "IF1 ADC2 Mux" पूर्ण,
	अणु "IF1 ADC2 Swap Mux", "R/L", "IF1 ADC2 Mux" पूर्ण,
	अणु "IF1 ADC2 Swap Mux", "L/L", "IF1 ADC2 Mux" पूर्ण,
	अणु "IF1 ADC2 Swap Mux", "R/R", "IF1 ADC2 Mux" पूर्ण,

	अणु "IF1 ADC3 Swap Mux", "L/R", "IF1 ADC3 Mux" पूर्ण,
	अणु "IF1 ADC3 Swap Mux", "R/L", "IF1 ADC3 Mux" पूर्ण,
	अणु "IF1 ADC3 Swap Mux", "L/L", "IF1 ADC3 Mux" पूर्ण,
	अणु "IF1 ADC3 Swap Mux", "R/R", "IF1 ADC3 Mux" पूर्ण,

	अणु "IF1 ADC4 Swap Mux", "L/R", "IF1 ADC4 Mux" पूर्ण,
	अणु "IF1 ADC4 Swap Mux", "R/L", "IF1 ADC4 Mux" पूर्ण,
	अणु "IF1 ADC4 Swap Mux", "L/L", "IF1 ADC4 Mux" पूर्ण,
	अणु "IF1 ADC4 Swap Mux", "R/R", "IF1 ADC4 Mux" पूर्ण,

	अणु "IF1 ADC", शून्य, "IF1 ADC1 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 ADC2 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 ADC3 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 ADC4 Swap Mux" पूर्ण,

	अणु "IF1 ADC TDM Swap Mux", "1/2/3/4", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "2/1/3/4", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "2/3/1/4", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "4/1/2/3", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "1/3/2/4", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "1/4/2/3", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "3/1/2/4", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC TDM Swap Mux", "3/4/1/2", "IF1 ADC" पूर्ण,

	अणु "AIF1TX", शून्य, "I2S1" पूर्ण,
	अणु "AIF1TX", शून्य, "IF1 ADC TDM Swap Mux" पूर्ण,

	अणु "IF2 ADC1 Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "IF2 ADC1 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,
	अणु "IF2 ADC1 Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "IF2 ADC2 Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "IF2 ADC2 Mux", "OB23", "OB23 Bypass Mux" पूर्ण,

	अणु "IF2 ADC3 Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "IF2 ADC3 Mux", "MONO ADC MIX", "Mono ADC MIX" पूर्ण,
	अणु "IF2 ADC3 Mux", "OB45", "OB45" पूर्ण,

	अणु "IF2 ADC4 Mux", "STO4 ADC MIX", "Stereo4 ADC MIX" पूर्ण,
	अणु "IF2 ADC4 Mux", "OB67", "OB67" पूर्ण,
	अणु "IF2 ADC4 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,

	अणु "IF2 ADC1 Swap Mux", "L/R", "IF2 ADC1 Mux" पूर्ण,
	अणु "IF2 ADC1 Swap Mux", "R/L", "IF2 ADC1 Mux" पूर्ण,
	अणु "IF2 ADC1 Swap Mux", "L/L", "IF2 ADC1 Mux" पूर्ण,
	अणु "IF2 ADC1 Swap Mux", "R/R", "IF2 ADC1 Mux" पूर्ण,

	अणु "IF2 ADC2 Swap Mux", "L/R", "IF2 ADC2 Mux" पूर्ण,
	अणु "IF2 ADC2 Swap Mux", "R/L", "IF2 ADC2 Mux" पूर्ण,
	अणु "IF2 ADC2 Swap Mux", "L/L", "IF2 ADC2 Mux" पूर्ण,
	अणु "IF2 ADC2 Swap Mux", "R/R", "IF2 ADC2 Mux" पूर्ण,

	अणु "IF2 ADC3 Swap Mux", "L/R", "IF2 ADC3 Mux" पूर्ण,
	अणु "IF2 ADC3 Swap Mux", "R/L", "IF2 ADC3 Mux" पूर्ण,
	अणु "IF2 ADC3 Swap Mux", "L/L", "IF2 ADC3 Mux" पूर्ण,
	अणु "IF2 ADC3 Swap Mux", "R/R", "IF2 ADC3 Mux" पूर्ण,

	अणु "IF2 ADC4 Swap Mux", "L/R", "IF2 ADC4 Mux" पूर्ण,
	अणु "IF2 ADC4 Swap Mux", "R/L", "IF2 ADC4 Mux" पूर्ण,
	अणु "IF2 ADC4 Swap Mux", "L/L", "IF2 ADC4 Mux" पूर्ण,
	अणु "IF2 ADC4 Swap Mux", "R/R", "IF2 ADC4 Mux" पूर्ण,

	अणु "IF2 ADC", शून्य, "IF2 ADC1 Swap Mux" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC2 Swap Mux" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC3 Swap Mux" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC4 Swap Mux" पूर्ण,

	अणु "IF2 ADC TDM Swap Mux", "1/2/3/4", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "2/1/3/4", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "3/1/2/4", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "4/1/2/3", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "1/3/2/4", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "1/4/2/3", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "2/3/1/4", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC TDM Swap Mux", "3/4/1/2", "IF2 ADC" पूर्ण,

	अणु "AIF2TX", शून्य, "I2S2" पूर्ण,
	अणु "AIF2TX", शून्य, "IF2 ADC TDM Swap Mux" पूर्ण,

	अणु "IF3 ADC Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "IF3 ADC Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "IF3 ADC Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "IF3 ADC Mux", "STO4 ADC MIX", "Stereo4 ADC MIX" पूर्ण,
	अणु "IF3 ADC Mux", "MONO ADC MIX", "Mono ADC MIX" पूर्ण,
	अणु "IF3 ADC Mux", "OB01", "OB01 Bypass Mux" पूर्ण,
	अणु "IF3 ADC Mux", "OB23", "OB23 Bypass Mux" पूर्ण,
	अणु "IF3 ADC Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "AIF3TX", शून्य, "I2S3" पूर्ण,
	अणु "AIF3TX", शून्य, "IF3 ADC Mux" पूर्ण,

	अणु "IF4 ADC Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "IF4 ADC Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "IF4 ADC Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "IF4 ADC Mux", "STO4 ADC MIX", "Stereo4 ADC MIX" पूर्ण,
	अणु "IF4 ADC Mux", "MONO ADC MIX", "Mono ADC MIX" पूर्ण,
	अणु "IF4 ADC Mux", "OB01", "OB01 Bypass Mux" पूर्ण,
	अणु "IF4 ADC Mux", "OB23", "OB23 Bypass Mux" पूर्ण,
	अणु "IF4 ADC Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "AIF4TX", शून्य, "I2S4" पूर्ण,
	अणु "AIF4TX", शून्य, "IF4 ADC Mux" पूर्ण,

	अणु "SLB ADC1 Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "SLB ADC1 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,
	अणु "SLB ADC1 Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "SLB ADC2 Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "SLB ADC2 Mux", "OB23", "OB23 Bypass Mux" पूर्ण,

	अणु "SLB ADC3 Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "SLB ADC3 Mux", "MONO ADC MIX", "Mono ADC MIX" पूर्ण,
	अणु "SLB ADC3 Mux", "OB45", "OB45" पूर्ण,

	अणु "SLB ADC4 Mux", "STO4 ADC MIX", "Stereo4 ADC MIX" पूर्ण,
	अणु "SLB ADC4 Mux", "OB67", "OB67" पूर्ण,
	अणु "SLB ADC4 Mux", "OB01", "OB01 Bypass Mux" पूर्ण,

	अणु "SLBTX", शून्य, "SLB" पूर्ण,
	अणु "SLBTX", शून्य, "SLB ADC1 Mux" पूर्ण,
	अणु "SLBTX", शून्य, "SLB ADC2 Mux" पूर्ण,
	अणु "SLBTX", शून्य, "SLB ADC3 Mux" पूर्ण,
	अणु "SLBTX", शून्य, "SLB ADC4 Mux" पूर्ण,

	अणु "DSPTX", शून्य, "IB01 Bypass Mux" पूर्ण,

	अणु "IB01 Mux", "IF1 DAC 01", "IF1 DAC01" पूर्ण,
	अणु "IB01 Mux", "IF2 DAC 01", "IF2 DAC01" पूर्ण,
	अणु "IB01 Mux", "SLB DAC 01", "SLB DAC01" पूर्ण,
	अणु "IB01 Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	/* The IB01 Mux controls the source क्रम InBound0 and InBound1.
	 * When the mux option "VAD ADC/DAC1 FS" is selected, "VAD ADC" goes to
	 * InBound0 and "DAC1 FS" goes to InBound1. "VAD ADC" is used क्रम
	 * hotwording. "DAC1 FS" is not used currently.
	 *
	 * Creating a common widget node क्रम "VAD ADC" + "DAC1 FS" and
	 * connecting the common widget to IB01 Mux causes the issue where
	 * there is an active path going from प्रणाली playback -> "DAC1 FS" ->
	 * IB01 Mux -> DSP Buffer -> hotword stream. This wrong path confuses
	 * DAPM. Thereक्रमe "DAC1 FS" is ignored क्रम now.
	 */
	अणु "IB01 Mux", "VAD ADC/DAC1 FS", "VAD ADC Mux" पूर्ण,

	अणु "IB01 Bypass Mux", "Bypass", "IB01 Mux" पूर्ण,
	अणु "IB01 Bypass Mux", "Pass SRC", "IB01 Mux" पूर्ण,

	अणु "IB23 Mux", "IF1 DAC 23", "IF1 DAC23" पूर्ण,
	अणु "IB23 Mux", "IF2 DAC 23", "IF2 DAC23" पूर्ण,
	अणु "IB23 Mux", "SLB DAC 23", "SLB DAC23" पूर्ण,
	अणु "IB23 Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "IB23 Mux", "DAC1 FS", "DAC1 FS" पूर्ण,
	अणु "IB23 Mux", "IF4 DAC", "IF4 DAC" पूर्ण,

	अणु "IB23 Bypass Mux", "Bypass", "IB23 Mux" पूर्ण,
	अणु "IB23 Bypass Mux", "Pass SRC", "IB23 Mux" पूर्ण,

	अणु "IB45 Mux", "IF1 DAC 45", "IF1 DAC45" पूर्ण,
	अणु "IB45 Mux", "IF2 DAC 45", "IF2 DAC45" पूर्ण,
	अणु "IB45 Mux", "SLB DAC 45", "SLB DAC45" पूर्ण,
	अणु "IB45 Mux", "STO3 ADC MIX", "Stereo3 ADC MIX" पूर्ण,
	अणु "IB45 Mux", "IF3 DAC", "IF3 DAC" पूर्ण,

	अणु "IB45 Bypass Mux", "Bypass", "IB45 Mux" पूर्ण,
	अणु "IB45 Bypass Mux", "Pass SRC", "IB45 Mux" पूर्ण,

	अणु "IB6 Mux", "IF1 DAC 6", "IF1 DAC6 Mux" पूर्ण,
	अणु "IB6 Mux", "IF2 DAC 6", "IF2 DAC6 Mux" पूर्ण,
	अणु "IB6 Mux", "SLB DAC 6", "SLB DAC6" पूर्ण,
	अणु "IB6 Mux", "STO4 ADC MIX L", "Stereo4 ADC MIXL" पूर्ण,
	अणु "IB6 Mux", "IF4 DAC L", "IF4 DAC L" पूर्ण,
	अणु "IB6 Mux", "STO1 ADC MIX L", "Stereo1 ADC MIXL" पूर्ण,
	अणु "IB6 Mux", "STO2 ADC MIX L", "Stereo2 ADC MIXL" पूर्ण,
	अणु "IB6 Mux", "STO3 ADC MIX L", "Stereo3 ADC MIXL" पूर्ण,

	अणु "IB7 Mux", "IF1 DAC 7", "IF1 DAC7 Mux" पूर्ण,
	अणु "IB7 Mux", "IF2 DAC 7", "IF2 DAC7 Mux" पूर्ण,
	अणु "IB7 Mux", "SLB DAC 7", "SLB DAC7" पूर्ण,
	अणु "IB7 Mux", "STO4 ADC MIX R", "Stereo4 ADC MIXR" पूर्ण,
	अणु "IB7 Mux", "IF4 DAC R", "IF4 DAC R" पूर्ण,
	अणु "IB7 Mux", "STO1 ADC MIX R", "Stereo1 ADC MIXR" पूर्ण,
	अणु "IB7 Mux", "STO2 ADC MIX R", "Stereo2 ADC MIXR" पूर्ण,
	अणु "IB7 Mux", "STO3 ADC MIX R", "Stereo3 ADC MIXR" पूर्ण,

	अणु "IB8 Mux", "STO1 ADC MIX L", "Stereo1 ADC MIXL" पूर्ण,
	अणु "IB8 Mux", "STO2 ADC MIX L", "Stereo2 ADC MIXL" पूर्ण,
	अणु "IB8 Mux", "STO3 ADC MIX L", "Stereo3 ADC MIXL" पूर्ण,
	अणु "IB8 Mux", "STO4 ADC MIX L", "Stereo4 ADC MIXL" पूर्ण,
	अणु "IB8 Mux", "MONO ADC MIX L", "Mono ADC MIXL" पूर्ण,
	अणु "IB8 Mux", "DACL1 FS", "DAC1 MIXL" पूर्ण,

	अणु "IB9 Mux", "STO1 ADC MIX R", "Stereo1 ADC MIXR" पूर्ण,
	अणु "IB9 Mux", "STO2 ADC MIX R", "Stereo2 ADC MIXR" पूर्ण,
	अणु "IB9 Mux", "STO3 ADC MIX R", "Stereo3 ADC MIXR" पूर्ण,
	अणु "IB9 Mux", "STO4 ADC MIX R", "Stereo4 ADC MIXR" पूर्ण,
	अणु "IB9 Mux", "MONO ADC MIX R", "Mono ADC MIXR" पूर्ण,
	अणु "IB9 Mux", "DACR1 FS", "DAC1 MIXR" पूर्ण,
	अणु "IB9 Mux", "DAC1 FS", "DAC1 FS" पूर्ण,

	अणु "OB01 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB01 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB01 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB01 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB01 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB01 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB01 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB23 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB23 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB23 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB23 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB23 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB23 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB23 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB4 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB4 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB4 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB4 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB4 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB4 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB4 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB5 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB5 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB5 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB5 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB5 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB5 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB5 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB6 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB6 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB6 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB6 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB6 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB6 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB6 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB7 MIX", "IB01 Switch", "IB01 Bypass Mux" पूर्ण,
	अणु "OB7 MIX", "IB23 Switch", "IB23 Bypass Mux" पूर्ण,
	अणु "OB7 MIX", "IB45 Switch", "IB45 Bypass Mux" पूर्ण,
	अणु "OB7 MIX", "IB6 Switch", "IB6 Mux" पूर्ण,
	अणु "OB7 MIX", "IB7 Switch", "IB7 Mux" पूर्ण,
	अणु "OB7 MIX", "IB8 Switch", "IB8 Mux" पूर्ण,
	अणु "OB7 MIX", "IB9 Switch", "IB9 Mux" पूर्ण,

	अणु "OB01 Bypass Mux", "Bypass", "OB01 MIX" पूर्ण,
	अणु "OB01 Bypass Mux", "Pass SRC", "OB01 MIX" पूर्ण,
	अणु "OB23 Bypass Mux", "Bypass", "OB23 MIX" पूर्ण,
	अणु "OB23 Bypass Mux", "Pass SRC", "OB23 MIX" पूर्ण,

	अणु "OutBound2", शून्य, "OB23 Bypass Mux" पूर्ण,
	अणु "OutBound3", शून्य, "OB23 Bypass Mux" पूर्ण,
	अणु "OutBound4", शून्य, "OB4 MIX" पूर्ण,
	अणु "OutBound5", शून्य, "OB5 MIX" पूर्ण,
	अणु "OutBound6", शून्य, "OB6 MIX" पूर्ण,
	अणु "OutBound7", शून्य, "OB7 MIX" पूर्ण,

	अणु "OB45", शून्य, "OutBound4" पूर्ण,
	अणु "OB45", शून्य, "OutBound5" पूर्ण,
	अणु "OB67", शून्य, "OutBound6" पूर्ण,
	अणु "OB67", शून्य, "OutBound7" पूर्ण,

	अणु "IF1 DAC0", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC1", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC2", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC3", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC4", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC5", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC6", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC7", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC0", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC1", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC2", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC3", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC4", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC5", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC6", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC7", शून्य, "I2S1" पूर्ण,

	अणु "IF1 DAC0 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC0 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC1 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC1 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC2 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC2 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC3 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC3 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC4 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC4 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC5 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC5 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC6 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC6 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC7 Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot3", "IF1 DAC3" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot4", "IF1 DAC4" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot5", "IF1 DAC5" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot6", "IF1 DAC6" पूर्ण,
	अणु "IF1 DAC7 Mux", "Slot7", "IF1 DAC7" पूर्ण,

	अणु "IF1 DAC01", शून्य, "IF1 DAC0 Mux" पूर्ण,
	अणु "IF1 DAC01", शून्य, "IF1 DAC1 Mux" पूर्ण,
	अणु "IF1 DAC23", शून्य, "IF1 DAC2 Mux" पूर्ण,
	अणु "IF1 DAC23", शून्य, "IF1 DAC3 Mux" पूर्ण,
	अणु "IF1 DAC45", शून्य, "IF1 DAC4 Mux" पूर्ण,
	अणु "IF1 DAC45", शून्य, "IF1 DAC5 Mux" पूर्ण,
	अणु "IF1 DAC67", शून्य, "IF1 DAC6 Mux" पूर्ण,
	अणु "IF1 DAC67", शून्य, "IF1 DAC7 Mux" पूर्ण,

	अणु "IF2 DAC0", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC1", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC2", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC3", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC4", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC5", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC6", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC7", शून्य, "AIF2RX" पूर्ण,
	अणु "IF2 DAC0", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC1", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC2", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC3", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC4", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC5", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC6", शून्य, "I2S2" पूर्ण,
	अणु "IF2 DAC7", शून्य, "I2S2" पूर्ण,

	अणु "IF2 DAC0 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC0 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC1 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC1 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC2 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC2 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC3 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC3 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC4 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC4 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC5 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC5 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC6 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC6 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC7 Mux", "Slot0", "IF2 DAC0" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot1", "IF2 DAC1" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot2", "IF2 DAC2" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot3", "IF2 DAC3" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot4", "IF2 DAC4" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot5", "IF2 DAC5" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot6", "IF2 DAC6" पूर्ण,
	अणु "IF2 DAC7 Mux", "Slot7", "IF2 DAC7" पूर्ण,

	अणु "IF2 DAC01", शून्य, "IF2 DAC0 Mux" पूर्ण,
	अणु "IF2 DAC01", शून्य, "IF2 DAC1 Mux" पूर्ण,
	अणु "IF2 DAC23", शून्य, "IF2 DAC2 Mux" पूर्ण,
	अणु "IF2 DAC23", शून्य, "IF2 DAC3 Mux" पूर्ण,
	अणु "IF2 DAC45", शून्य, "IF2 DAC4 Mux" पूर्ण,
	अणु "IF2 DAC45", शून्य, "IF2 DAC5 Mux" पूर्ण,
	अणु "IF2 DAC67", शून्य, "IF2 DAC6 Mux" पूर्ण,
	अणु "IF2 DAC67", शून्य, "IF2 DAC7 Mux" पूर्ण,

	अणु "IF3 DAC", शून्य, "AIF3RX" पूर्ण,
	अणु "IF3 DAC", शून्य, "I2S3" पूर्ण,

	अणु "IF4 DAC", शून्य, "AIF4RX" पूर्ण,
	अणु "IF4 DAC", शून्य, "I2S4" पूर्ण,

	अणु "IF3 DAC L", शून्य, "IF3 DAC" पूर्ण,
	अणु "IF3 DAC R", शून्य, "IF3 DAC" पूर्ण,

	अणु "IF4 DAC L", शून्य, "IF4 DAC" पूर्ण,
	अणु "IF4 DAC R", शून्य, "IF4 DAC" पूर्ण,

	अणु "SLB DAC0", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC1", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC2", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC3", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC4", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC5", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC6", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC7", शून्य, "SLBRX" पूर्ण,
	अणु "SLB DAC0", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC1", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC2", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC3", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC4", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC5", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC6", शून्य, "SLB" पूर्ण,
	अणु "SLB DAC7", शून्य, "SLB" पूर्ण,

	अणु "SLB DAC01", शून्य, "SLB DAC0" पूर्ण,
	अणु "SLB DAC01", शून्य, "SLB DAC1" पूर्ण,
	अणु "SLB DAC23", शून्य, "SLB DAC2" पूर्ण,
	अणु "SLB DAC23", शून्य, "SLB DAC3" पूर्ण,
	अणु "SLB DAC45", शून्य, "SLB DAC4" पूर्ण,
	अणु "SLB DAC45", शून्य, "SLB DAC5" पूर्ण,
	अणु "SLB DAC67", शून्य, "SLB DAC6" पूर्ण,
	अणु "SLB DAC67", शून्य, "SLB DAC7" पूर्ण,

	अणु "ADDA1 Mux", "STO1 ADC MIX", "Stereo1 ADC MIX" पूर्ण,
	अणु "ADDA1 Mux", "STO2 ADC MIX", "Stereo2 ADC MIX" पूर्ण,
	अणु "ADDA1 Mux", "OB 67", "OB67" पूर्ण,

	अणु "DAC1 Mux", "IF1 DAC 01", "IF1 DAC01" पूर्ण,
	अणु "DAC1 Mux", "IF2 DAC 01", "IF2 DAC01" पूर्ण,
	अणु "DAC1 Mux", "IF3 DAC LR", "IF3 DAC" पूर्ण,
	अणु "DAC1 Mux", "IF4 DAC LR", "IF4 DAC" पूर्ण,
	अणु "DAC1 Mux", "SLB DAC 01", "SLB DAC01" पूर्ण,
	अणु "DAC1 Mux", "OB 01", "OB01 Bypass Mux" पूर्ण,

	अणु "DAC1 MIXL", "Stereo ADC Switch", "ADDA1 Mux" पूर्ण,
	अणु "DAC1 MIXL", "DAC1 Switch", "DAC1 Mux" पूर्ण,
	अणु "DAC1 MIXR", "Stereo ADC Switch", "ADDA1 Mux" पूर्ण,
	अणु "DAC1 MIXR", "DAC1 Switch", "DAC1 Mux" पूर्ण,

	अणु "DAC1 FS", शून्य, "DAC1 MIXL" पूर्ण,
	अणु "DAC1 FS", शून्य, "DAC1 MIXR" पूर्ण,

	अणु "DAC2 L Mux", "IF1 DAC 2", "IF1 DAC2 Mux" पूर्ण,
	अणु "DAC2 L Mux", "IF2 DAC 2", "IF2 DAC2 Mux" पूर्ण,
	अणु "DAC2 L Mux", "IF3 DAC L", "IF3 DAC L" पूर्ण,
	अणु "DAC2 L Mux", "IF4 DAC L", "IF4 DAC L" पूर्ण,
	अणु "DAC2 L Mux", "SLB DAC 2", "SLB DAC2" पूर्ण,
	अणु "DAC2 L Mux", "OB 2", "OutBound2" पूर्ण,

	अणु "DAC2 R Mux", "IF1 DAC 3", "IF1 DAC3 Mux" पूर्ण,
	अणु "DAC2 R Mux", "IF2 DAC 3", "IF2 DAC3 Mux" पूर्ण,
	अणु "DAC2 R Mux", "IF3 DAC R", "IF3 DAC R" पूर्ण,
	अणु "DAC2 R Mux", "IF4 DAC R", "IF4 DAC R" पूर्ण,
	अणु "DAC2 R Mux", "SLB DAC 3", "SLB DAC3" पूर्ण,
	अणु "DAC2 R Mux", "OB 3", "OutBound3" पूर्ण,
	अणु "DAC2 R Mux", "Haptic Generator", "Haptic Generator" पूर्ण,
	अणु "DAC2 R Mux", "VAD ADC", "VAD ADC Mux" पूर्ण,

	अणु "DAC3 L Mux", "IF1 DAC 4", "IF1 DAC4 Mux" पूर्ण,
	अणु "DAC3 L Mux", "IF2 DAC 4", "IF2 DAC4 Mux" पूर्ण,
	अणु "DAC3 L Mux", "IF3 DAC L", "IF3 DAC L" पूर्ण,
	अणु "DAC3 L Mux", "IF4 DAC L", "IF4 DAC L" पूर्ण,
	अणु "DAC3 L Mux", "SLB DAC 4", "SLB DAC4" पूर्ण,
	अणु "DAC3 L Mux", "OB 4", "OutBound4" पूर्ण,

	अणु "DAC3 R Mux", "IF1 DAC 5", "IF1 DAC5 Mux" पूर्ण,
	अणु "DAC3 R Mux", "IF2 DAC 5", "IF2 DAC5 Mux" पूर्ण,
	अणु "DAC3 R Mux", "IF3 DAC R", "IF3 DAC R" पूर्ण,
	अणु "DAC3 R Mux", "IF4 DAC R", "IF4 DAC R" पूर्ण,
	अणु "DAC3 R Mux", "SLB DAC 5", "SLB DAC5" पूर्ण,
	अणु "DAC3 R Mux", "OB 5", "OutBound5" पूर्ण,

	अणु "DAC4 L Mux", "IF1 DAC 6", "IF1 DAC6 Mux" पूर्ण,
	अणु "DAC4 L Mux", "IF2 DAC 6", "IF2 DAC6 Mux" पूर्ण,
	अणु "DAC4 L Mux", "IF3 DAC L", "IF3 DAC L" पूर्ण,
	अणु "DAC4 L Mux", "IF4 DAC L", "IF4 DAC L" पूर्ण,
	अणु "DAC4 L Mux", "SLB DAC 6", "SLB DAC6" पूर्ण,
	अणु "DAC4 L Mux", "OB 6", "OutBound6" पूर्ण,

	अणु "DAC4 R Mux", "IF1 DAC 7", "IF1 DAC7 Mux" पूर्ण,
	अणु "DAC4 R Mux", "IF2 DAC 7", "IF2 DAC7 Mux" पूर्ण,
	अणु "DAC4 R Mux", "IF3 DAC R", "IF3 DAC R" पूर्ण,
	अणु "DAC4 R Mux", "IF4 DAC R", "IF4 DAC R" पूर्ण,
	अणु "DAC4 R Mux", "SLB DAC 7", "SLB DAC7" पूर्ण,
	अणु "DAC4 R Mux", "OB 7", "OutBound7" पूर्ण,

	अणु "Sidetone Mux", "DMIC1 L", "DMIC L1" पूर्ण,
	अणु "Sidetone Mux", "DMIC2 L", "DMIC L2" पूर्ण,
	अणु "Sidetone Mux", "DMIC3 L", "DMIC L3" पूर्ण,
	अणु "Sidetone Mux", "DMIC4 L", "DMIC L4" पूर्ण,
	अणु "Sidetone Mux", "ADC1", "ADC 1" पूर्ण,
	अणु "Sidetone Mux", "ADC2", "ADC 2" पूर्ण,
	अणु "Sidetone Mux", शून्य, "Sidetone Power" पूर्ण,

	अणु "Stereo DAC MIXL", "ST L Switch", "Sidetone Mux" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC1 L Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC2 L Switch", "DAC2 L Mux" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC1 R Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXL", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "Stereo DAC MIXR", "ST R Switch", "Sidetone Mux" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC1 R Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC2 R Switch", "DAC2 R Mux" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC1 L Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXR", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "dac stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono DAC MIXL", "ST L Switch", "Sidetone Mux" पूर्ण,
	अणु "Mono DAC MIXL", "DAC1 L Switch", "DAC1 MIXL" पूर्ण,
	अणु "Mono DAC MIXL", "DAC2 L Switch", "DAC2 L Mux" पूर्ण,
	अणु "Mono DAC MIXL", "DAC2 R Switch", "DAC2 R Mux" पूर्ण,
	अणु "Mono DAC MIXL", शून्य, "dac mono2 left filter" पूर्ण,
	अणु "dac mono2 left filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "Mono DAC MIXR", "ST R Switch", "Sidetone Mux" पूर्ण,
	अणु "Mono DAC MIXR", "DAC1 R Switch", "DAC1 MIXR" पूर्ण,
	अणु "Mono DAC MIXR", "DAC2 R Switch", "DAC2 R Mux" पूर्ण,
	अणु "Mono DAC MIXR", "DAC2 L Switch", "DAC2 L Mux" पूर्ण,
	अणु "Mono DAC MIXR", शून्य, "dac mono2 right filter" पूर्ण,
	अणु "dac mono2 right filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "DD1 MIXL", "Sto DAC Mix L Switch", "Stereo DAC MIXL" पूर्ण,
	अणु "DD1 MIXL", "Mono DAC Mix L Switch", "Mono DAC MIXL" पूर्ण,
	अणु "DD1 MIXL", "DAC3 L Switch", "DAC3 L Mux" पूर्ण,
	अणु "DD1 MIXL", "DAC3 R Switch", "DAC3 R Mux" पूर्ण,
	अणु "DD1 MIXL", शून्य, "dac mono3 left filter" पूर्ण,
	अणु "dac mono3 left filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DD1 MIXR", "Sto DAC Mix R Switch", "Stereo DAC MIXR" पूर्ण,
	अणु "DD1 MIXR", "Mono DAC Mix R Switch", "Mono DAC MIXR" पूर्ण,
	अणु "DD1 MIXR", "DAC3 L Switch", "DAC3 L Mux" पूर्ण,
	अणु "DD1 MIXR", "DAC3 R Switch", "DAC3 R Mux" पूर्ण,
	अणु "DD1 MIXR", शून्य, "dac mono3 right filter" पूर्ण,
	अणु "dac mono3 right filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "DD2 MIXL", "Sto DAC Mix L Switch", "Stereo DAC MIXL" पूर्ण,
	अणु "DD2 MIXL", "Mono DAC Mix L Switch", "Mono DAC MIXL" पूर्ण,
	अणु "DD2 MIXL", "DAC4 L Switch", "DAC4 L Mux" पूर्ण,
	अणु "DD2 MIXL", "DAC4 R Switch", "DAC4 R Mux" पूर्ण,
	अणु "DD2 MIXL", शून्य, "dac mono4 left filter" पूर्ण,
	अणु "dac mono4 left filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DD2 MIXR", "Sto DAC Mix R Switch", "Stereo DAC MIXR" पूर्ण,
	अणु "DD2 MIXR", "Mono DAC Mix R Switch", "Mono DAC MIXR" पूर्ण,
	अणु "DD2 MIXR", "DAC4 L Switch", "DAC4 L Mux" पूर्ण,
	अणु "DD2 MIXR", "DAC4 R Switch", "DAC4 R Mux" पूर्ण,
	अणु "DD2 MIXR", शून्य, "dac mono4 right filter" पूर्ण,
	अणु "dac mono4 right filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo DAC MIX", शून्य, "Stereo DAC MIXL" पूर्ण,
	अणु "Stereo DAC MIX", शून्य, "Stereo DAC MIXR" पूर्ण,
	अणु "Mono DAC MIX", शून्य, "Mono DAC MIXL" पूर्ण,
	अणु "Mono DAC MIX", शून्य, "Mono DAC MIXR" पूर्ण,
	अणु "DD1 MIX", शून्य, "DD1 MIXL" पूर्ण,
	अणु "DD1 MIX", शून्य, "DD1 MIXR" पूर्ण,
	अणु "DD2 MIX", शून्य, "DD2 MIXL" पूर्ण,
	अणु "DD2 MIX", शून्य, "DD2 MIXR" पूर्ण,

	अणु "DAC12 SRC Mux", "STO1 DAC MIX", "Stereo DAC MIX" पूर्ण,
	अणु "DAC12 SRC Mux", "MONO DAC MIX", "Mono DAC MIX" पूर्ण,
	अणु "DAC12 SRC Mux", "DD MIX1", "DD1 MIX" पूर्ण,
	अणु "DAC12 SRC Mux", "DD MIX2", "DD2 MIX" पूर्ण,

	अणु "DAC3 SRC Mux", "MONO DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "DAC3 SRC Mux", "MONO DAC MIXR", "Mono DAC MIXR" पूर्ण,
	अणु "DAC3 SRC Mux", "DD MIX1L", "DD1 MIXL" पूर्ण,
	अणु "DAC3 SRC Mux", "DD MIX2L", "DD2 MIXL" पूर्ण,

	अणु "DAC 1", शून्य, "DAC12 SRC Mux" पूर्ण,
	अणु "DAC 2", शून्य, "DAC12 SRC Mux" पूर्ण,
	अणु "DAC 3", शून्य, "DAC3 SRC Mux" पूर्ण,

	अणु "PDM1 L Mux", "STO1 DAC MIX", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", "MONO DAC MIX", "Mono DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", "DD MIX1", "DD1 MIXL" पूर्ण,
	अणु "PDM1 L Mux", "DD MIX2", "DD2 MIXL" पूर्ण,
	अणु "PDM1 L Mux", शून्य, "PDM1 Power" पूर्ण,
	अणु "PDM1 R Mux", "STO1 DAC MIX", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", "MONO DAC MIX", "Mono DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", "DD MIX1", "DD1 MIXR" पूर्ण,
	अणु "PDM1 R Mux", "DD MIX2", "DD2 MIXR" पूर्ण,
	अणु "PDM1 R Mux", शून्य, "PDM1 Power" पूर्ण,
	अणु "PDM2 L Mux", "STO1 DAC MIX", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM2 L Mux", "MONO DAC MIX", "Mono DAC MIXL" पूर्ण,
	अणु "PDM2 L Mux", "DD MIX1", "DD1 MIXL" पूर्ण,
	अणु "PDM2 L Mux", "DD MIX2", "DD2 MIXL" पूर्ण,
	अणु "PDM2 L Mux", शून्य, "PDM2 Power" पूर्ण,
	अणु "PDM2 R Mux", "STO1 DAC MIX", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM2 R Mux", "MONO DAC MIX", "Mono DAC MIXR" पूर्ण,
	अणु "PDM2 R Mux", "DD MIX1", "DD1 MIXR" पूर्ण,
	अणु "PDM2 R Mux", "DD MIX1", "DD2 MIXR" पूर्ण,
	अणु "PDM2 R Mux", शून्य, "PDM2 Power" पूर्ण,

	अणु "LOUT1 amp", शून्य, "DAC 1" पूर्ण,
	अणु "LOUT2 amp", शून्य, "DAC 2" पूर्ण,
	अणु "LOUT3 amp", शून्य, "DAC 3" पूर्ण,

	अणु "LOUT1 vref", शून्य, "LOUT1 amp" पूर्ण,
	अणु "LOUT2 vref", शून्य, "LOUT2 amp" पूर्ण,
	अणु "LOUT3 vref", शून्य, "LOUT3 amp" पूर्ण,

	अणु "LOUT1", शून्य, "LOUT1 vref" पूर्ण,
	अणु "LOUT2", शून्य, "LOUT2 vref" पूर्ण,
	अणु "LOUT3", शून्य, "LOUT3 vref" पूर्ण,

	अणु "PDM1L", शून्य, "PDM1 L Mux" पूर्ण,
	अणु "PDM1R", शून्य, "PDM1 R Mux" पूर्ण,
	अणु "PDM2L", शून्य, "PDM2 L Mux" पूर्ण,
	अणु "PDM2R", शून्य, "PDM2 R Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5677_dmic2_clk_1[] = अणु
	अणु "DMIC L2", शून्य, "DMIC1 power" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC1 power" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5677_dmic2_clk_2[] = अणु
	अणु "DMIC L2", शून्य, "DMIC2 power" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC2 power" पूर्ण,
पूर्ण;

अटल पूर्णांक rt5677_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5677->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5677->sysclk, rt5677->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting: sysclk=%dHz lrck=%dHz\n",
			rt5677->sysclk, rt5677->lrck[dai->id]);
		वापस -EINVAL;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण
	bclk_ms = frame_size > 32;
	rt5677->bclk[dai->id] = rt5677->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5677->bclk[dai->id], rt5677->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5677_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5677_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5677_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5677_AIF1:
		mask_clk = RT5677_I2S_PD1_MASK;
		val_clk = pre_भाग << RT5677_I2S_PD1_SFT;
		regmap_update_bits(rt5677->regmap, RT5677_I2S1_SDP,
			RT5677_I2S_DL_MASK, val_len);
		regmap_update_bits(rt5677->regmap, RT5677_CLK_TREE_CTRL1,
			mask_clk, val_clk);
		अवरोध;
	हाल RT5677_AIF2:
		mask_clk = RT5677_I2S_PD2_MASK;
		val_clk = pre_भाग << RT5677_I2S_PD2_SFT;
		regmap_update_bits(rt5677->regmap, RT5677_I2S2_SDP,
			RT5677_I2S_DL_MASK, val_len);
		regmap_update_bits(rt5677->regmap, RT5677_CLK_TREE_CTRL1,
			mask_clk, val_clk);
		अवरोध;
	हाल RT5677_AIF3:
		mask_clk = RT5677_I2S_BCLK_MS3_MASK | RT5677_I2S_PD3_MASK;
		val_clk = bclk_ms << RT5677_I2S_BCLK_MS3_SFT |
			pre_भाग << RT5677_I2S_PD3_SFT;
		regmap_update_bits(rt5677->regmap, RT5677_I2S3_SDP,
			RT5677_I2S_DL_MASK, val_len);
		regmap_update_bits(rt5677->regmap, RT5677_CLK_TREE_CTRL1,
			mask_clk, val_clk);
		अवरोध;
	हाल RT5677_AIF4:
		mask_clk = RT5677_I2S_BCLK_MS4_MASK | RT5677_I2S_PD4_MASK;
		val_clk = bclk_ms << RT5677_I2S_BCLK_MS4_SFT |
			pre_भाग << RT5677_I2S_PD4_SFT;
		regmap_update_bits(rt5677->regmap, RT5677_I2S4_SDP,
			RT5677_I2S_DL_MASK, val_len);
		regmap_update_bits(rt5677->regmap, RT5677_CLK_TREE_CTRL1,
			mask_clk, val_clk);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5677->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5677_I2S_MS_S;
		rt5677->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5677_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5677_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5677_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5677_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5677_AIF1:
		regmap_update_bits(rt5677->regmap, RT5677_I2S1_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5677_AIF2:
		regmap_update_bits(rt5677->regmap, RT5677_I2S2_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5677_AIF3:
		regmap_update_bits(rt5677->regmap, RT5677_I2S3_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5677_AIF4:
		regmap_update_bits(rt5677->regmap, RT5677_I2S4_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt5677->sysclk && clk_id == rt5677->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5677_SCLK_S_MCLK:
		reg_val |= RT5677_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5677_SCLK_S_PLL1:
		reg_val |= RT5677_SCLK_SRC_PLL1;
		अवरोध;
	हाल RT5677_SCLK_S_RCCLK:
		reg_val |= RT5677_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
		RT5677_SCLK_SRC_MASK, reg_val);
	rt5677->sysclk = freq;
	rt5677->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

/**
 * rt5677_pll_calc - Calcualte PLL M/N/K code.
 * @freq_in: बाह्यal घड़ी provided to codec.
 * @freq_out: target घड़ी which codec works on.
 * @pll_code: Poपूर्णांकer to काष्ठाure with M, N, K, bypass K and bypass M flag.
 *
 * Calcualte M/N/K code and bypass K/M flag to configure PLL क्रम codec.
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक rt5677_pll_calc(स्थिर अचिन्हित पूर्णांक freq_in,
	स्थिर अचिन्हित पूर्णांक freq_out, काष्ठा rl6231_pll_code *pll_code)
अणु
	अगर (RT5677_PLL_INP_MIN > freq_in)
		वापस -EINVAL;

	वापस rl6231_pll_calc(freq_in, freq_out, pll_code);
पूर्ण

अटल पूर्णांक rt5677_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5677->pll_src && freq_in == rt5677->pll_in &&
	    freq_out == rt5677->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5677->pll_in = 0;
		rt5677->pll_out = 0;
		regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
			RT5677_SCLK_SRC_MASK, RT5677_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5677_PLL1_S_MCLK:
		regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
			RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5677_PLL1_S_BCLK1:
	हाल RT5677_PLL1_S_BCLK2:
	हाल RT5677_PLL1_S_BCLK3:
	हाल RT5677_PLL1_S_BCLK4:
		चयन (dai->id) अणु
		हाल RT5677_AIF1:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK1);
			अवरोध;
		हाल RT5677_AIF2:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK2);
			अवरोध;
		हाल RT5677_AIF3:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK3);
			अवरोध;
		हाल RT5677_AIF4:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK4);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rt5677_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "m_bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	regmap_ग_लिखो(rt5677->regmap, RT5677_PLL1_CTRL1,
		pll_code.n_code << RT5677_PLL_N_SFT | pll_code.k_code);
	regmap_ग_लिखो(rt5677->regmap, RT5677_PLL1_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5677_PLL_M_SFT) |
		(pll_code.m_bp << RT5677_PLL_M_BP_SFT));

	rt5677->pll_in = freq_in;
	rt5677->pll_out = freq_out;
	rt5677->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0, slot_width_25 = 0;

	अगर (rx_mask || tx_mask)
		val |= (1 << 12);

	चयन (slots) अणु
	हाल 4:
		val |= (1 << 10);
		अवरोध;
	हाल 6:
		val |= (2 << 10);
		अवरोध;
	हाल 8:
		val |= (3 << 10);
		अवरोध;
	हाल 2:
	शेष:
		अवरोध;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= (1 << 8);
		अवरोध;
	हाल 25:
		slot_width_25 = 0x8080;
		fallthrough;
	हाल 24:
		val |= (2 << 8);
		अवरोध;
	हाल 32:
		val |= (3 << 8);
		अवरोध;
	हाल 16:
	शेष:
		अवरोध;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5677_AIF1:
		regmap_update_bits(rt5677->regmap, RT5677_TDM1_CTRL1, 0x1f00,
			val);
		regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC, 0x8000,
			slot_width_25);
		अवरोध;
	हाल RT5677_AIF2:
		regmap_update_bits(rt5677->regmap, RT5677_TDM2_CTRL1, 0x1f00,
			val);
		regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC, 0x80,
			slot_width_25);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	क्रमागत snd_soc_bias_level prev_bias =
		snd_soc_component_get_bias_level(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अगर (prev_bias == SND_SOC_BIAS_STANDBY) अणु

			regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG1,
				RT5677_LDO1_SEL_MASK | RT5677_LDO2_SEL_MASK,
				5 << RT5677_LDO1_SEL_SFT |
				5 << RT5677_LDO2_SEL_SFT);
			regmap_update_bits(rt5677->regmap,
				RT5677_PR_BASE + RT5677_BIAS_CUR4,
				0x0f00, 0x0f00);
			regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG1,
				RT5677_PWR_FV1 | RT5677_PWR_FV2 |
				RT5677_PWR_VREF1 | RT5677_PWR_MB |
				RT5677_PWR_BG | RT5677_PWR_VREF2,
				RT5677_PWR_VREF1 | RT5677_PWR_MB |
				RT5677_PWR_BG | RT5677_PWR_VREF2);
			rt5677->is_vref_slow = false;
			regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
				RT5677_PWR_CORE, RT5677_PWR_CORE);
			regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC,
				0x1, 0x1);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (prev_bias == SND_SOC_BIAS_OFF &&
				rt5677->dsp_vad_en_request) अणु
			/* Re-enable the DSP अगर it was turned off at suspend */
			rt5677->dsp_vad_en = true;
			/* The delay is to रुको क्रम MCLK */
			schedule_delayed_work(&rt5677->dsp_work,
					msecs_to_jअगरfies(1000));
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		flush_delayed_work(&rt5677->dsp_work);
		अगर (rt5677->is_dsp_mode) अणु
			/* Turn off the DSP beक्रमe suspend */
			rt5677->dsp_vad_en = false;
			schedule_delayed_work(&rt5677->dsp_work, 0);
			flush_delayed_work(&rt5677->dsp_work);
		पूर्ण

		regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC, 0x1, 0x0);
		regmap_ग_लिखो(rt5677->regmap, RT5677_PWR_DIG1, 0x0000);
		regmap_ग_लिखो(rt5677->regmap, RT5677_PWR_ANLG1,
			2 << RT5677_LDO1_SEL_SFT |
			2 << RT5677_LDO2_SEL_SFT);
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_CORE, 0);
		regmap_update_bits(rt5677->regmap,
			RT5677_PR_BASE + RT5677_BIAS_CUR4, 0x0f00, 0x0000);

		अगर (rt5677->dsp_vad_en)
			rt5677_set_dsp_vad(component, true);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल व्योम rt5677_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा rt5677_priv *rt5677 = gpiochip_get_data(chip);

	चयन (offset) अणु
	हाल RT5677_GPIO1 ... RT5677_GPIO5:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL2,
			0x1 << (offset * 3 + 1), !!value << (offset * 3 + 1));
		अवरोध;

	हाल RT5677_GPIO6:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL3,
			RT5677_GPIO6_OUT_MASK, !!value << RT5677_GPIO6_OUT_SFT);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rt5677_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा rt5677_priv *rt5677 = gpiochip_get_data(chip);

	चयन (offset) अणु
	हाल RT5677_GPIO1 ... RT5677_GPIO5:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL2,
			0x3 << (offset * 3 + 1),
			(0x2 | !!value) << (offset * 3 + 1));
		अवरोध;

	हाल RT5677_GPIO6:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL3,
			RT5677_GPIO6_सूची_MASK | RT5677_GPIO6_OUT_MASK,
			RT5677_GPIO6_सूची_OUT | !!value << RT5677_GPIO6_OUT_SFT);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rt5677_priv *rt5677 = gpiochip_get_data(chip);
	पूर्णांक value, ret;

	ret = regmap_पढ़ो(rt5677->regmap, RT5677_GPIO_ST, &value);
	अगर (ret < 0)
		वापस ret;

	वापस (value & (0x1 << offset)) >> offset;
पूर्ण

अटल पूर्णांक rt5677_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rt5677_priv *rt5677 = gpiochip_get_data(chip);

	चयन (offset) अणु
	हाल RT5677_GPIO1 ... RT5677_GPIO5:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL2,
			0x1 << (offset * 3 + 2), 0x0);
		अवरोध;

	हाल RT5677_GPIO6:
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL3,
			RT5677_GPIO6_सूची_MASK, RT5677_GPIO6_सूची_IN);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/** Configures the gpio as
 *   0 - भग्नing
 *   1 - pull करोwn
 *   2 - pull up
 */
अटल व्योम rt5677_gpio_config(काष्ठा rt5677_priv *rt5677, अचिन्हित offset,
		पूर्णांक value)
अणु
	पूर्णांक shअगरt;

	चयन (offset) अणु
	हाल RT5677_GPIO1 ... RT5677_GPIO2:
		shअगरt = 2 * (1 - offset);
		regmap_update_bits(rt5677->regmap,
			RT5677_PR_BASE + RT5677_DIG_IN_PIN_ST_CTRL2,
			0x3 << shअगरt,
			(value & 0x3) << shअगरt);
		अवरोध;

	हाल RT5677_GPIO3 ... RT5677_GPIO6:
		shअगरt = 2 * (9 - offset);
		regmap_update_bits(rt5677->regmap,
			RT5677_PR_BASE + RT5677_DIG_IN_PIN_ST_CTRL3,
			0x3 << shअगरt,
			(value & 0x3) << shअगरt);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rt5677_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rt5677_priv *rt5677 = gpiochip_get_data(chip);
	पूर्णांक irq;

	अगर ((rt5677->pdata.jd1_gpio == 1 && offset == RT5677_GPIO1) ||
		(rt5677->pdata.jd1_gpio == 2 &&
			offset == RT5677_GPIO2) ||
		(rt5677->pdata.jd1_gpio == 3 &&
			offset == RT5677_GPIO3)) अणु
		irq = RT5677_IRQ_JD1;
	पूर्ण अन्यथा अगर ((rt5677->pdata.jd2_gpio == 1 && offset == RT5677_GPIO4) ||
		(rt5677->pdata.jd2_gpio == 2 &&
			offset == RT5677_GPIO5) ||
		(rt5677->pdata.jd2_gpio == 3 &&
			offset == RT5677_GPIO6)) अणु
		irq = RT5677_IRQ_JD2;
	पूर्ण अन्यथा अगर ((rt5677->pdata.jd3_gpio == 1 &&
			offset == RT5677_GPIO4) ||
		(rt5677->pdata.jd3_gpio == 2 &&
			offset == RT5677_GPIO5) ||
		(rt5677->pdata.jd3_gpio == 3 &&
			offset == RT5677_GPIO6)) अणु
		irq = RT5677_IRQ_JD3;
	पूर्ण अन्यथा अणु
		वापस -ENXIO;
	पूर्ण

	वापस irq_create_mapping(rt5677->करोमुख्य, irq);
पूर्ण

अटल स्थिर काष्ठा gpio_chip rt5677_ढाँचा_chip = अणु
	.label			= RT5677_DRV_NAME,
	.owner			= THIS_MODULE,
	.direction_output	= rt5677_gpio_direction_out,
	.set			= rt5677_gpio_set,
	.direction_input	= rt5677_gpio_direction_in,
	.get			= rt5677_gpio_get,
	.to_irq			= rt5677_to_irq,
	.can_sleep		= 1,
पूर्ण;

अटल व्योम rt5677_init_gpio(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt5677_priv *rt5677 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	rt5677->gpio_chip = rt5677_ढाँचा_chip;
	rt5677->gpio_chip.ngpio = RT5677_GPIO_NUM;
	rt5677->gpio_chip.parent = &i2c->dev;
	rt5677->gpio_chip.base = -1;

	ret = gpiochip_add_data(&rt5677->gpio_chip, rt5677);
	अगर (ret != 0)
		dev_err(&i2c->dev, "Failed to add GPIOs: %d\n", ret);
पूर्ण

अटल व्योम rt5677_मुक्त_gpio(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt5677_priv *rt5677 = i2c_get_clientdata(i2c);

	gpiochip_हटाओ(&rt5677->gpio_chip);
पूर्ण
#अन्यथा
अटल व्योम rt5677_gpio_config(काष्ठा rt5677_priv *rt5677, अचिन्हित offset,
		पूर्णांक value)
अणु
पूर्ण

अटल व्योम rt5677_init_gpio(काष्ठा i2c_client *i2c)
अणु
पूर्ण

अटल व्योम rt5677_मुक्त_gpio(काष्ठा i2c_client *i2c)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rt5677_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	rt5677->component = component;

	अगर (rt5677->pdata.dmic2_clk_pin == RT5677_DMIC_CLK2) अणु
		snd_soc_dapm_add_routes(dapm,
			rt5677_dmic2_clk_2,
			ARRAY_SIZE(rt5677_dmic2_clk_2));
	पूर्ण अन्यथा अणु /*use dmic1 घड़ी by शेष*/
		snd_soc_dapm_add_routes(dapm,
			rt5677_dmic2_clk_1,
			ARRAY_SIZE(rt5677_dmic2_clk_1));
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC,
			~RT5677_IRQ_DEBOUNCE_SEL_MASK, 0x0020);
	regmap_ग_लिखो(rt5677->regmap, RT5677_PWR_DSP2,
			RT5677_PWR_SLIM_ISO | RT5677_PWR_CORE_ISO);

	क्रम (i = 0; i < RT5677_GPIO_NUM; i++)
		rt5677_gpio_config(rt5677, i, rt5677->pdata.gpio_config[i]);

	mutex_init(&rt5677->dsp_cmd_lock);
	mutex_init(&rt5677->dsp_pri_lock);

	वापस 0;
पूर्ण

अटल व्योम rt5677_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&rt5677->dsp_work);

	regmap_ग_लिखो(rt5677->regmap, RT5677_RESET, 0x10ec);
	gpiod_set_value_cansleep(rt5677->घात_lकरो2, 0);
	gpiod_set_value_cansleep(rt5677->reset_pin, 1);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5677_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	अगर (rt5677->irq) अणु
		cancel_delayed_work_sync(&rt5677->resume_irq_check);
		disable_irq(rt5677->irq);
	पूर्ण

	अगर (!rt5677->dsp_vad_en) अणु
		regcache_cache_only(rt5677->regmap, true);
		regcache_mark_dirty(rt5677->regmap);

		gpiod_set_value_cansleep(rt5677->घात_lकरो2, 0);
		gpiod_set_value_cansleep(rt5677->reset_pin, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	अगर (!rt5677->dsp_vad_en) अणु
		rt5677->pll_src = 0;
		rt5677->pll_in = 0;
		rt5677->pll_out = 0;
		gpiod_set_value_cansleep(rt5677->घात_lकरो2, 1);
		gpiod_set_value_cansleep(rt5677->reset_pin, 0);
		अगर (rt5677->घात_lकरो2 || rt5677->reset_pin)
			msleep(10);

		regcache_cache_only(rt5677->regmap, false);
		regcache_sync(rt5677->regmap);
	पूर्ण

	अगर (rt5677->irq) अणु
		enable_irq(rt5677->irq);
		schedule_delayed_work(&rt5677->resume_irq_check, 0);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5677_suspend शून्य
#घोषणा rt5677_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक rt5677_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा rt5677_priv *rt5677 = i2c_get_clientdata(client);

	अगर (rt5677->is_dsp_mode) अणु
		अगर (reg > 0xff) अणु
			mutex_lock(&rt5677->dsp_pri_lock);
			rt5677_dsp_mode_i2c_ग_लिखो(rt5677, RT5677_PRIV_INDEX,
				reg & 0xff);
			rt5677_dsp_mode_i2c_पढ़ो(rt5677, RT5677_PRIV_DATA, val);
			mutex_unlock(&rt5677->dsp_pri_lock);
		पूर्ण अन्यथा अणु
			rt5677_dsp_mode_i2c_पढ़ो(rt5677, reg, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(rt5677->regmap_physical, reg, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5677_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा rt5677_priv *rt5677 = i2c_get_clientdata(client);

	अगर (rt5677->is_dsp_mode) अणु
		अगर (reg > 0xff) अणु
			mutex_lock(&rt5677->dsp_pri_lock);
			rt5677_dsp_mode_i2c_ग_लिखो(rt5677, RT5677_PRIV_INDEX,
				reg & 0xff);
			rt5677_dsp_mode_i2c_ग_लिखो(rt5677, RT5677_PRIV_DATA,
				val);
			mutex_unlock(&rt5677->dsp_pri_lock);
		पूर्ण अन्यथा अणु
			rt5677_dsp_mode_i2c_ग_लिखो(rt5677, reg, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(rt5677->regmap_physical, reg, val);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RT5677_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5677_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5677_aअगर_dai_ops = अणु
	.hw_params = rt5677_hw_params,
	.set_fmt = rt5677_set_dai_fmt,
	.set_sysclk = rt5677_set_dai_sysclk,
	.set_pll = rt5677_set_dai_pll,
	.set_tdm_slot = rt5677_set_tdm_slot,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops rt5677_dsp_dai_ops = अणु
	.set_sysclk = rt5677_set_dai_sysclk,
	.set_pll = rt5677_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5677_dai[] = अणु
	अणु
		.name = "rt5677-aif1",
		.id = RT5677_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.ops = &rt5677_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5677-aif2",
		.id = RT5677_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.ops = &rt5677_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5677-aif3",
		.id = RT5677_AIF3,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.ops = &rt5677_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5677-aif4",
		.id = RT5677_AIF4,
		.playback = अणु
			.stream_name = "AIF4 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF4 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.ops = &rt5677_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5677-slimbus",
		.id = RT5677_AIF5,
		.playback = अणु
			.stream_name = "SLIMBus Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "SLIMBus Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5677_STEREO_RATES,
			.क्रमmats = RT5677_FORMATS,
		पूर्ण,
		.ops = &rt5677_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5677-dspbuffer",
		.id = RT5677_DSPBUFF,
		.capture = अणु
			.stream_name = "DSP Buffer",
			.channels_min = 1,
			.channels_max = 1,
			.rates = SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &rt5677_dsp_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5677 = अणु
	.name			= RT5677_DRV_NAME,
	.probe			= rt5677_probe,
	.हटाओ			= rt5677_हटाओ,
	.suspend		= rt5677_suspend,
	.resume			= rt5677_resume,
	.set_bias_level		= rt5677_set_bias_level,
	.controls		= rt5677_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5677_snd_controls),
	.dapm_widमाला_लो		= rt5677_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5677_dapm_widमाला_लो),
	.dapm_routes		= rt5677_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5677_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5677_regmap_physical = अणु
	.name = "physical",
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = RT5677_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5677_ranges) *
						RT5677_PR_SPACING),
	.पढ़ोable_reg = rt5677_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_NONE,
	.ranges = rt5677_ranges,
	.num_ranges = ARRAY_SIZE(rt5677_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5677_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = RT5677_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5677_ranges) *
						RT5677_PR_SPACING),

	.अस्थिर_reg = rt5677_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5677_पढ़ोable_रेजिस्टर,
	.reg_पढ़ो = rt5677_पढ़ो,
	.reg_ग_लिखो = rt5677_ग_लिखो,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5677_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5677_reg),
	.ranges = rt5677_ranges,
	.num_ranges = ARRAY_SIZE(rt5677_ranges),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rt5677_of_match[] = अणु
	अणु .compatible = "realtek,rt5677", .data = (स्थिर व्योम *)RT5677 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5677_of_match);

अटल स्थिर काष्ठा acpi_device_id rt5677_acpi_match[] = अणु
	अणु "RT5677CE", RT5677 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5677_acpi_match);

अटल व्योम rt5677_पढ़ो_device_properties(काष्ठा rt5677_priv *rt5677,
		काष्ठा device *dev)
अणु
	u32 val;

	rt5677->pdata.in1_dअगरf =
		device_property_पढ़ो_bool(dev, "IN1") ||
		device_property_पढ़ो_bool(dev, "realtek,in1-differential");

	rt5677->pdata.in2_dअगरf =
		device_property_पढ़ो_bool(dev, "IN2") ||
		device_property_पढ़ो_bool(dev, "realtek,in2-differential");

	rt5677->pdata.lout1_dअगरf =
		device_property_पढ़ो_bool(dev, "OUT1") ||
		device_property_पढ़ो_bool(dev, "realtek,lout1-differential");

	rt5677->pdata.lout2_dअगरf =
		device_property_पढ़ो_bool(dev, "OUT2") ||
		device_property_पढ़ो_bool(dev, "realtek,lout2-differential");

	rt5677->pdata.lout3_dअगरf =
		device_property_पढ़ो_bool(dev, "OUT3") ||
		device_property_पढ़ो_bool(dev, "realtek,lout3-differential");

	device_property_पढ़ो_u8_array(dev, "realtek,gpio-config",
				      rt5677->pdata.gpio_config,
				      RT5677_GPIO_NUM);

	अगर (!device_property_पढ़ो_u32(dev, "DCLK", &val) ||
	    !device_property_पढ़ो_u32(dev, "realtek,dmic2_clk_pin", &val))
		rt5677->pdata.dmic2_clk_pin = val;

	अगर (!device_property_पढ़ो_u32(dev, "JD1", &val) ||
	    !device_property_पढ़ो_u32(dev, "realtek,jd1-gpio", &val))
		rt5677->pdata.jd1_gpio = val;

	अगर (!device_property_पढ़ो_u32(dev, "JD2", &val) ||
	    !device_property_पढ़ो_u32(dev, "realtek,jd2-gpio", &val))
		rt5677->pdata.jd2_gpio = val;

	अगर (!device_property_पढ़ो_u32(dev, "JD3", &val) ||
	    !device_property_पढ़ो_u32(dev, "realtek,jd3-gpio", &val))
		rt5677->pdata.jd3_gpio = val;
पूर्ण

काष्ठा rt5677_irq_desc अणु
	अचिन्हित पूर्णांक enable_mask;
	अचिन्हित पूर्णांक status_mask;
	अचिन्हित पूर्णांक polarity_mask;
पूर्ण;

अटल स्थिर काष्ठा rt5677_irq_desc rt5677_irq_descs[] = अणु
	[RT5677_IRQ_JD1] = अणु
		.enable_mask = RT5677_EN_IRQ_GPIO_JD1,
		.status_mask = RT5677_STA_GPIO_JD1,
		.polarity_mask = RT5677_INV_GPIO_JD1,
	पूर्ण,
	[RT5677_IRQ_JD2] = अणु
		.enable_mask = RT5677_EN_IRQ_GPIO_JD2,
		.status_mask = RT5677_STA_GPIO_JD2,
		.polarity_mask = RT5677_INV_GPIO_JD2,
	पूर्ण,
	[RT5677_IRQ_JD3] = अणु
		.enable_mask = RT5677_EN_IRQ_GPIO_JD3,
		.status_mask = RT5677_STA_GPIO_JD3,
		.polarity_mask = RT5677_INV_GPIO_JD3,
	पूर्ण,
पूर्ण;

अटल bool rt5677_check_hotword(काष्ठा rt5677_priv *rt5677)
अणु
	पूर्णांक reg_gpio;

	अगर (!rt5677->is_dsp_mode)
		वापस false;

	अगर (regmap_पढ़ो(rt5677->regmap, RT5677_GPIO_CTRL1, &reg_gpio))
		वापस false;

	/* Firmware sets GPIO1 pin to be GPIO1 after hotword is detected */
	अगर ((reg_gpio & RT5677_GPIO1_PIN_MASK) == RT5677_GPIO1_PIN_IRQ)
		वापस false;

	/* Set GPIO1 pin back to be IRQ output क्रम jack detect */
	regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL1,
			RT5677_GPIO1_PIN_MASK, RT5677_GPIO1_PIN_IRQ);

	rt5677_spi_hotword_detected();
	वापस true;
पूर्ण

अटल irqवापस_t rt5677_irq(पूर्णांक unused, व्योम *data)
अणु
	काष्ठा rt5677_priv *rt5677 = data;
	पूर्णांक ret, loop, i, reg_irq, virq;
	bool irq_fired = false;

	mutex_lock(&rt5677->irq_lock);

	/*
	 * Loop to handle पूर्णांकerrupts until the last i2c पढ़ो shows no pending
	 * irqs. The पूर्णांकerrupt line is shared by multiple पूर्णांकerrupt sources.
	 * After the regmap_पढ़ो() below, a new पूर्णांकerrupt source line may
	 * become high beक्रमe the regmap_ग_लिखो() finishes, so there isn't a
	 * rising edge on the shared पूर्णांकerrupt line क्रम the new पूर्णांकerrupt. Thus,
	 * the loop is needed to aव्योम missing irqs.
	 *
	 * A safeguard of 20 loops is used to aव्योम hanging in the irq handler
	 * अगर there is something wrong with the पूर्णांकerrupt status update. The
	 * पूर्णांकerrupt sources here are audio jack plug/unplug events which
	 * shouldn't happen at a high frequency क्रम a दीर्घ period of समय.
	 * Empirically, more than 3 loops have never been seen.
	 */
	क्रम (loop = 0; loop < 20; loop++) अणु
		/* Read पूर्णांकerrupt status */
		ret = regmap_पढ़ो(rt5677->regmap, RT5677_IRQ_CTRL1, &reg_irq);
		अगर (ret) अणु
			dev_err(rt5677->dev, "failed reading IRQ status: %d\n",
				ret);
			जाओ निकास;
		पूर्ण

		irq_fired = false;
		क्रम (i = 0; i < RT5677_IRQ_NUM; i++) अणु
			अगर (reg_irq & rt5677_irq_descs[i].status_mask) अणु
				irq_fired = true;
				virq = irq_find_mapping(rt5677->करोमुख्य, i);
				अगर (virq)
					handle_nested_irq(virq);

				/* Clear the पूर्णांकerrupt by flipping the polarity
				 * of the पूर्णांकerrupt source line that fired
				 */
				reg_irq ^= rt5677_irq_descs[i].polarity_mask;
			पूर्ण
		पूर्ण

		/* Exit the loop only when we know क्रम sure that GPIO1 pin
		 * was low at some poपूर्णांक since irq_lock was acquired. Any event
		 * after that poपूर्णांक creates a rising edge that triggers another
		 * call to rt5677_irq().
		 */
		अगर (!irq_fired && !rt5677_check_hotword(rt5677))
			जाओ निकास;

		ret = regmap_ग_लिखो(rt5677->regmap, RT5677_IRQ_CTRL1, reg_irq);
		अगर (ret) अणु
			dev_err(rt5677->dev, "failed updating IRQ status: %d\n",
				ret);
			जाओ निकास;
		पूर्ण
	पूर्ण
निकास:
	WARN_ON_ONCE(loop == 20);
	mutex_unlock(&rt5677->irq_lock);
	अगर (irq_fired)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम rt5677_resume_irq_check(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i, virq;
	काष्ठा rt5677_priv *rt5677 =
		container_of(work, काष्ठा rt5677_priv, resume_irq_check.work);

	/* This is needed to check and clear the पूर्णांकerrupt status रेजिस्टर
	 * at resume. If the headset is plugged/unplugged when the device is
	 * fully suspended, there won't be a rising edge at resume to trigger
	 * the पूर्णांकerrupt. Without this, we miss the next unplug/plug event.
	 */
	rt5677_irq(0, rt5677);

	/* Call all enabled jack detect irq handlers again. This is needed in
	 * addition to the above check क्रम a corner हाल caused by jack gpio
	 * debounce. After codec irq is disabled at suspend, the delayed work
	 * scheduled by soc-jack may run and पढ़ो wrong jack gpio values, since
	 * the regmap is in cache only mode. At resume, there is no irq because
	 * rt5677_irq has alपढ़ोy ran and cleared the irq status at suspend.
	 * Without this explicit check, unplug the headset right after suspend
	 * starts, then after resume the headset is still shown as plugged in.
	 */
	mutex_lock(&rt5677->irq_lock);
	क्रम (i = 0; i < RT5677_IRQ_NUM; i++) अणु
		अगर (rt5677->irq_en & rt5677_irq_descs[i].enable_mask) अणु
			virq = irq_find_mapping(rt5677->करोमुख्य, i);
			अगर (virq)
				handle_nested_irq(virq);
		पूर्ण
	पूर्ण
	mutex_unlock(&rt5677->irq_lock);
पूर्ण

अटल व्योम rt5677_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	mutex_lock(&rt5677->irq_lock);
पूर्ण

अटल व्योम rt5677_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	// Set the enable/disable bits क्रम the jack detect IRQs.
	regmap_update_bits(rt5677->regmap, RT5677_IRQ_CTRL1,
			RT5677_EN_IRQ_GPIO_JD1 | RT5677_EN_IRQ_GPIO_JD2 |
			RT5677_EN_IRQ_GPIO_JD3, rt5677->irq_en);
	mutex_unlock(&rt5677->irq_lock);
पूर्ण

अटल व्योम rt5677_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	rt5677->irq_en |= rt5677_irq_descs[data->hwirq].enable_mask;
पूर्ण

अटल व्योम rt5677_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	rt5677->irq_en &= ~rt5677_irq_descs[data->hwirq].enable_mask;
पूर्ण

अटल काष्ठा irq_chip rt5677_irq_chip = अणु
	.name			= "rt5677_irq_chip",
	.irq_bus_lock		= rt5677_irq_bus_lock,
	.irq_bus_sync_unlock	= rt5677_irq_bus_sync_unlock,
	.irq_disable		= rt5677_irq_disable,
	.irq_enable		= rt5677_irq_enable,
पूर्ण;

अटल पूर्णांक rt5677_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	काष्ठा rt5677_priv *rt5677 = h->host_data;

	irq_set_chip_data(virq, rt5677);
	irq_set_chip(virq, &rt5677_irq_chip);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा irq_करोमुख्य_ops rt5677_करोमुख्य_ops = अणु
	.map	= rt5677_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक rt5677_init_irq(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक ret;
	काष्ठा rt5677_priv *rt5677 = i2c_get_clientdata(i2c);
	अचिन्हित पूर्णांक jd_mask = 0, jd_val = 0;

	अगर (!rt5677->pdata.jd1_gpio &&
		!rt5677->pdata.jd2_gpio &&
		!rt5677->pdata.jd3_gpio)
		वापस 0;

	अगर (!i2c->irq) अणु
		dev_err(&i2c->dev, "No interrupt specified\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&rt5677->irq_lock);
	INIT_DELAYED_WORK(&rt5677->resume_irq_check, rt5677_resume_irq_check);

	/*
	 * Select RC as the debounce घड़ी so that GPIO works even when
	 * MCLK is gated which happens when there is no audio stream
	 * (SND_SOC_BIAS_OFF).
	 */
	regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC,
			RT5677_IRQ_DEBOUNCE_SEL_MASK,
			RT5677_IRQ_DEBOUNCE_SEL_RC);
	/* Enable स्वतः घातer on RC when GPIO states are changed */
	regmap_update_bits(rt5677->regmap, RT5677_GEN_CTRL1, 0xff, 0xff);

	/* Select and enable jack detection sources per platक्रमm data */
	अगर (rt5677->pdata.jd1_gpio) अणु
		jd_mask	|= RT5677_SEL_GPIO_JD1_MASK;
		jd_val	|= rt5677->pdata.jd1_gpio << RT5677_SEL_GPIO_JD1_SFT;
	पूर्ण
	अगर (rt5677->pdata.jd2_gpio) अणु
		jd_mask	|= RT5677_SEL_GPIO_JD2_MASK;
		jd_val	|= rt5677->pdata.jd2_gpio << RT5677_SEL_GPIO_JD2_SFT;
	पूर्ण
	अगर (rt5677->pdata.jd3_gpio) अणु
		jd_mask	|= RT5677_SEL_GPIO_JD3_MASK;
		jd_val	|= rt5677->pdata.jd3_gpio << RT5677_SEL_GPIO_JD3_SFT;
	पूर्ण
	regmap_update_bits(rt5677->regmap, RT5677_JD_CTRL1, jd_mask, jd_val);

	/* Set GPIO1 pin to be IRQ output */
	regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL1,
			RT5677_GPIO1_PIN_MASK, RT5677_GPIO1_PIN_IRQ);

	/* Ready to listen क्रम पूर्णांकerrupts */
	rt5677->करोमुख्य = irq_करोमुख्य_add_linear(i2c->dev.of_node,
			RT5677_IRQ_NUM, &rt5677_करोमुख्य_ops, rt5677);
	अगर (!rt5677->करोमुख्य) अणु
		dev_err(&i2c->dev, "Failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य, rt5677_irq,
			IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			"rt5677", rt5677);
	अगर (ret)
		dev_err(&i2c->dev, "Failed to request IRQ: %d\n", ret);

	rt5677->irq = i2c->irq;

	वापस ret;
पूर्ण

अटल पूर्णांक rt5677_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt5677_priv *rt5677;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt5677 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5677_priv),
				GFP_KERNEL);
	अगर (rt5677 == शून्य)
		वापस -ENOMEM;

	rt5677->dev = &i2c->dev;
	rt5677->set_dsp_vad = rt5677_set_dsp_vad;
	INIT_DELAYED_WORK(&rt5677->dsp_work, rt5677_dsp_work);
	i2c_set_clientdata(i2c, rt5677);

	अगर (i2c->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match_id;

		match_id = of_match_device(rt5677_of_match, &i2c->dev);
		अगर (match_id)
			rt5677->type = (क्रमागत rt5677_type)match_id->data;
	पूर्ण अन्यथा अगर (ACPI_HANDLE(&i2c->dev)) अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(rt5677_acpi_match, &i2c->dev);
		अगर (acpi_id)
			rt5677->type = (क्रमागत rt5677_type)acpi_id->driver_data;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	rt5677_पढ़ो_device_properties(rt5677, &i2c->dev);

	/* घात-lकरो2 and reset are optional. The codec pins may be अटलally
	 * connected on the board without gpios. If the gpio device property
	 * isn't specअगरied, devm_gpiod_get_optional वापसs शून्य.
	 */
	rt5677->घात_lकरो2 = devm_gpiod_get_optional(&i2c->dev,
			"realtek,pow-ldo2", GPIOD_OUT_HIGH);
	अगर (IS_ERR(rt5677->घात_lकरो2)) अणु
		ret = PTR_ERR(rt5677->घात_lकरो2);
		dev_err(&i2c->dev, "Failed to request POW_LDO2: %d\n", ret);
		वापस ret;
	पूर्ण
	rt5677->reset_pin = devm_gpiod_get_optional(&i2c->dev,
			"realtek,reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(rt5677->reset_pin)) अणु
		ret = PTR_ERR(rt5677->reset_pin);
		dev_err(&i2c->dev, "Failed to request RESET: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (rt5677->घात_lकरो2 || rt5677->reset_pin) अणु
		/* Wait a जबतक until I2C bus becomes available. The datasheet
		 * करोes not specअगरy the exact we should रुको but startup
		 * sequence mentiones at least a few milliseconds.
		 */
		msleep(10);
	पूर्ण

	rt5677->regmap_physical = devm_regmap_init_i2c(i2c,
					&rt5677_regmap_physical);
	अगर (IS_ERR(rt5677->regmap_physical)) अणु
		ret = PTR_ERR(rt5677->regmap_physical);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	rt5677->regmap = devm_regmap_init(&i2c->dev, शून्य, i2c, &rt5677_regmap);
	अगर (IS_ERR(rt5677->regmap)) अणु
		ret = PTR_ERR(rt5677->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5677->regmap, RT5677_VENDOR_ID2, &val);
	अगर (val != RT5677_DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5677\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5677->regmap, RT5677_RESET, 0x10ec);

	ret = regmap_रेजिस्टर_patch(rt5677->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	अगर (rt5677->pdata.in1_dअगरf)
		regmap_update_bits(rt5677->regmap, RT5677_IN1,
					RT5677_IN_DF1, RT5677_IN_DF1);

	अगर (rt5677->pdata.in2_dअगरf)
		regmap_update_bits(rt5677->regmap, RT5677_IN1,
					RT5677_IN_DF2, RT5677_IN_DF2);

	अगर (rt5677->pdata.lout1_dअगरf)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT1_L_DF, RT5677_LOUT1_L_DF);

	अगर (rt5677->pdata.lout2_dअगरf)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT2_L_DF, RT5677_LOUT2_L_DF);

	अगर (rt5677->pdata.lout3_dअगरf)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT3_L_DF, RT5677_LOUT3_L_DF);

	अगर (rt5677->pdata.dmic2_clk_pin == RT5677_DMIC_CLK2) अणु
		regmap_update_bits(rt5677->regmap, RT5677_GEN_CTRL2,
					RT5677_GPIO5_FUNC_MASK,
					RT5677_GPIO5_FUNC_DMIC);
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL2,
					RT5677_GPIO5_सूची_MASK,
					RT5677_GPIO5_सूची_OUT);
	पूर्ण

	अगर (rt5677->pdata.micbias1_vdd_3v3)
		regmap_update_bits(rt5677->regmap, RT5677_MICBIAS,
			RT5677_MICBIAS1_CTRL_VDD_MASK,
			RT5677_MICBIAS1_CTRL_VDD_3_3V);

	rt5677_init_gpio(i2c);
	ret = rt5677_init_irq(i2c);
	अगर (ret)
		dev_err(&i2c->dev, "Failed to initialize irq: %d\n", ret);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				      &soc_component_dev_rt5677,
				      rt5677_dai, ARRAY_SIZE(rt5677_dai));
पूर्ण

अटल पूर्णांक rt5677_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	rt5677_मुक्त_gpio(i2c);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver rt5677_i2c_driver = अणु
	.driver = अणु
		.name = RT5677_DRV_NAME,
		.of_match_table = rt5677_of_match,
		.acpi_match_table = ACPI_PTR(rt5677_acpi_match),
	पूर्ण,
	.probe_new = rt5677_i2c_probe,
	.हटाओ   = rt5677_i2c_हटाओ,
पूर्ण;
module_i2c_driver(rt5677_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5677 driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
