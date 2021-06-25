<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5645.c  --  RT5645 ALSA SoC audio codec driver
 *
 * Copyright 2013 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5645.h"

#घोषणा QUIRK_INV_JD1_1(q)	((q) & 1)
#घोषणा QUIRK_LEVEL_IRQ(q)	(((q) >> 1) & 1)
#घोषणा QUIRK_IN2_DIFF(q)	(((q) >> 2) & 1)
#घोषणा QUIRK_INV_HP_POL(q)	(((q) >> 3) & 1)
#घोषणा QUIRK_JD_MODE(q)	(((q) >> 4) & 7)
#घोषणा QUIRK_DMIC1_DATA_PIN(q)	(((q) >> 8) & 3)
#घोषणा QUIRK_DMIC2_DATA_PIN(q)	(((q) >> 12) & 3)

अटल अचिन्हित पूर्णांक quirk = -1;
module_param(quirk, uपूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "RT5645 pdata quirk override");

अटल स्थिर काष्ठा acpi_gpio_mapping *cht_rt5645_gpios;

#घोषणा RT5645_DEVICE_ID 0x6308
#घोषणा RT5650_DEVICE_ID 0x6419

#घोषणा RT5645_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5645_PR_SPACING 0x100

#घोषणा RT5645_PR_BASE (RT5645_PR_RANGE_BASE + (0 * RT5645_PR_SPACING))

#घोषणा RT5645_HWEQ_NUM 57

#घोषणा TIME_TO_POWER_MS 400

अटल स्थिर काष्ठा regmap_range_cfg rt5645_ranges[] = अणु
	अणु
		.name = "PR",
		.range_min = RT5645_PR_BASE,
		.range_max = RT5645_PR_BASE + 0xf8,
		.selector_reg = RT5645_PRIV_INDEX,
		.selector_mask = 0xff,
		.selector_shअगरt = 0x0,
		.winकरोw_start = RT5645_PRIV_DATA,
		.winकरोw_len = 0x1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणुRT5645_PR_BASE + 0x3d,	0x3600पूर्ण,
	अणुRT5645_PR_BASE + 0x1c,	0xfd70पूर्ण,
	अणुRT5645_PR_BASE + 0x20,	0x611fपूर्ण,
	अणुRT5645_PR_BASE + 0x21,	0x4040पूर्ण,
	अणुRT5645_PR_BASE + 0x23,	0x0004पूर्ण,
	अणुRT5645_ASRC_4, 0x0120पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence rt5650_init_list[] = अणु
	अणु0xf6,	0x0100पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5645_reg[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x01, 0xc8c8 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x03, 0xc8c8 पूर्ण,
	अणु 0x0a, 0x0002 पूर्ण,
	अणु 0x0b, 0x2827 पूर्ण,
	अणु 0x0c, 0xe000 पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0e, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x14, 0x3333 पूर्ण,
	अणु 0x16, 0x4b00 पूर्ण,
	अणु 0x18, 0x018b पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1a, 0xafaf पूर्ण,
	अणु 0x1b, 0x0001 पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1d, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x27, 0x7060 पूर्ण,
	अणु 0x28, 0x7070 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5656 पूर्ण,
	अणु 0x2b, 0x5454 पूर्ण,
	अणु 0x2c, 0xaaa0 पूर्ण,
	अणु 0x2d, 0x0000 पूर्ण,
	अणु 0x2f, 0x1002 पूर्ण,
	अणु 0x31, 0x5000 पूर्ण,
	अणु 0x32, 0x0000 पूर्ण,
	अणु 0x33, 0x0000 पूर्ण,
	अणु 0x34, 0x0000 पूर्ण,
	अणु 0x35, 0x0000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x007f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x007f पूर्ण,
	अणु 0x3f, 0x0000 पूर्ण,
	अणु 0x40, 0x001f पूर्ण,
	अणु 0x41, 0x0000 पूर्ण,
	अणु 0x42, 0x001f पूर्ण,
	अणु 0x45, 0x6000 पूर्ण,
	अणु 0x46, 0x003e पूर्ण,
	अणु 0x47, 0x003e पूर्ण,
	अणु 0x48, 0xf807 पूर्ण,
	अणु 0x4a, 0x0004 पूर्ण,
	अणु 0x4d, 0x0000 पूर्ण,
	अणु 0x4e, 0x0000 पूर्ण,
	अणु 0x4f, 0x01ff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0x01ff पूर्ण,
	अणु 0x53, 0xf000 पूर्ण,
	अणु 0x56, 0x0111 पूर्ण,
	अणु 0x57, 0x0064 पूर्ण,
	अणु 0x58, 0xef0e पूर्ण,
	अणु 0x59, 0xf0f0 पूर्ण,
	अणु 0x5a, 0xef0e पूर्ण,
	अणु 0x5b, 0xf0f0 पूर्ण,
	अणु 0x5c, 0xef0e पूर्ण,
	अणु 0x5d, 0xf0f0 पूर्ण,
	अणु 0x5e, 0xf000 पूर्ण,
	अणु 0x5f, 0x0000 पूर्ण,
	अणु 0x61, 0x0300 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x00c2 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0000 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x6a, 0x0000 पूर्ण,
	अणु 0x6c, 0x0aaa पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x8000 पूर्ण,
	अणु 0x72, 0x8000 पूर्ण,
	अणु 0x73, 0x7770 पूर्ण,
	अणु 0x74, 0x3e00 पूर्ण,
	अणु 0x75, 0x2409 पूर्ण,
	अणु 0x76, 0x000a पूर्ण,
	अणु 0x77, 0x0c00 पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
	अणु 0x79, 0x0123 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x83, 0x0000 पूर्ण,
	अणु 0x84, 0x0000 पूर्ण,
	अणु 0x85, 0x0000 पूर्ण,
	अणु 0x8a, 0x0120 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0646 पूर्ण,
	अणु 0x91, 0x0c06 पूर्ण,
	अणु 0x93, 0x0000 पूर्ण,
	अणु 0x94, 0x0200 पूर्ण,
	अणु 0x95, 0x0000 पूर्ण,
	अणु 0x9a, 0x2184 पूर्ण,
	अणु 0x9b, 0x010a पूर्ण,
	अणु 0x9c, 0x0aea पूर्ण,
	अणु 0x9d, 0x000c पूर्ण,
	अणु 0x9e, 0x0400 पूर्ण,
	अणु 0xa0, 0xa0a8 पूर्ण,
	अणु 0xa1, 0x0059 पूर्ण,
	अणु 0xa2, 0x0001 पूर्ण,
	अणु 0xae, 0x6000 पूर्ण,
	अणु 0xaf, 0x0000 पूर्ण,
	अणु 0xb0, 0x6000 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb2, 0x0000 पूर्ण,
	अणु 0xb3, 0x001f पूर्ण,
	अणु 0xb4, 0x020c पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x3100 पूर्ण,
	अणु 0xc0, 0x0000 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xc3, 0x2000 पूर्ण,
	अणु 0xcd, 0x0000 पूर्ण,
	अणु 0xce, 0x0000 पूर्ण,
	अणु 0xcf, 0x1813 पूर्ण,
	अणु 0xd0, 0x0690 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd3, 0xb320 पूर्ण,
	अणु 0xd4, 0x0000 पूर्ण,
	अणु 0xd6, 0x0400 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xdb, 0x0003 पूर्ण,
	अणु 0xdc, 0x0049 पूर्ण,
	अणु 0xdd, 0x001b पूर्ण,
	अणु 0xdf, 0x0008 पूर्ण,
	अणु 0xe0, 0x4000 पूर्ण,
	अणु 0xe6, 0x8000 पूर्ण,
	अणु 0xe7, 0x0200 पूर्ण,
	अणु 0xec, 0xb300 पूर्ण,
	अणु 0xed, 0x0000 पूर्ण,
	अणु 0xf0, 0x001f पूर्ण,
	अणु 0xf1, 0x020c पूर्ण,
	अणु 0xf2, 0x1f00 पूर्ण,
	अणु 0xf3, 0x0000 पूर्ण,
	अणु 0xf4, 0x4000 पूर्ण,
	अणु 0xf8, 0x0000 पूर्ण,
	अणु 0xf9, 0x0000 पूर्ण,
	अणु 0xfa, 0x2060 पूर्ण,
	अणु 0xfb, 0x4040 पूर्ण,
	अणु 0xfc, 0x0000 पूर्ण,
	अणु 0xfd, 0x0002 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6308 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5650_reg[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x01, 0xc8c8 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x03, 0xc8c8 पूर्ण,
	अणु 0x0a, 0x0002 पूर्ण,
	अणु 0x0b, 0x2827 पूर्ण,
	अणु 0x0c, 0xe000 पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0e, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x14, 0x3333 पूर्ण,
	अणु 0x16, 0x4b00 पूर्ण,
	अणु 0x18, 0x018b पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1a, 0xafaf पूर्ण,
	अणु 0x1b, 0x0001 पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1d, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x27, 0x7060 पूर्ण,
	अणु 0x28, 0x7070 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5656 पूर्ण,
	अणु 0x2b, 0x5454 पूर्ण,
	अणु 0x2c, 0xaaa0 पूर्ण,
	अणु 0x2d, 0x0000 पूर्ण,
	अणु 0x2f, 0x5002 पूर्ण,
	अणु 0x31, 0x5000 पूर्ण,
	अणु 0x32, 0x0000 पूर्ण,
	अणु 0x33, 0x0000 पूर्ण,
	अणु 0x34, 0x0000 पूर्ण,
	अणु 0x35, 0x0000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x007f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x007f पूर्ण,
	अणु 0x3f, 0x0000 पूर्ण,
	अणु 0x40, 0x001f पूर्ण,
	अणु 0x41, 0x0000 पूर्ण,
	अणु 0x42, 0x001f पूर्ण,
	अणु 0x45, 0x6000 पूर्ण,
	अणु 0x46, 0x003e पूर्ण,
	अणु 0x47, 0x003e पूर्ण,
	अणु 0x48, 0xf807 पूर्ण,
	अणु 0x4a, 0x0004 पूर्ण,
	अणु 0x4d, 0x0000 पूर्ण,
	अणु 0x4e, 0x0000 पूर्ण,
	अणु 0x4f, 0x01ff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0x01ff पूर्ण,
	अणु 0x53, 0xf000 पूर्ण,
	अणु 0x56, 0x0111 पूर्ण,
	अणु 0x57, 0x0064 पूर्ण,
	अणु 0x58, 0xef0e पूर्ण,
	अणु 0x59, 0xf0f0 पूर्ण,
	अणु 0x5a, 0xef0e पूर्ण,
	अणु 0x5b, 0xf0f0 पूर्ण,
	अणु 0x5c, 0xef0e पूर्ण,
	अणु 0x5d, 0xf0f0 पूर्ण,
	अणु 0x5e, 0xf000 पूर्ण,
	अणु 0x5f, 0x0000 पूर्ण,
	अणु 0x61, 0x0300 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x00c2 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0000 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x6a, 0x0000 पूर्ण,
	अणु 0x6c, 0x0aaa पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x8000 पूर्ण,
	अणु 0x72, 0x8000 पूर्ण,
	अणु 0x73, 0x7770 पूर्ण,
	अणु 0x74, 0x3e00 पूर्ण,
	अणु 0x75, 0x2409 पूर्ण,
	अणु 0x76, 0x000a पूर्ण,
	अणु 0x77, 0x0c00 पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
	अणु 0x79, 0x0123 पूर्ण,
	अणु 0x7a, 0x0123 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x83, 0x0000 पूर्ण,
	अणु 0x84, 0x0000 पूर्ण,
	अणु 0x85, 0x0000 पूर्ण,
	अणु 0x8a, 0x0120 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0646 पूर्ण,
	अणु 0x91, 0x0c06 पूर्ण,
	अणु 0x93, 0x0000 पूर्ण,
	अणु 0x94, 0x0200 पूर्ण,
	अणु 0x95, 0x0000 पूर्ण,
	अणु 0x9a, 0x2184 पूर्ण,
	अणु 0x9b, 0x010a पूर्ण,
	अणु 0x9c, 0x0aea पूर्ण,
	अणु 0x9d, 0x000c पूर्ण,
	अणु 0x9e, 0x0400 पूर्ण,
	अणु 0xa0, 0xa0a8 पूर्ण,
	अणु 0xa1, 0x0059 पूर्ण,
	अणु 0xa2, 0x0001 पूर्ण,
	अणु 0xae, 0x6000 पूर्ण,
	अणु 0xaf, 0x0000 पूर्ण,
	अणु 0xb0, 0x6000 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb2, 0x0000 पूर्ण,
	अणु 0xb3, 0x001f पूर्ण,
	अणु 0xb4, 0x020c पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x3100 पूर्ण,
	अणु 0xc0, 0x0000 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xc3, 0x2000 पूर्ण,
	अणु 0xcd, 0x0000 पूर्ण,
	अणु 0xce, 0x0000 पूर्ण,
	अणु 0xcf, 0x1813 पूर्ण,
	अणु 0xd0, 0x0690 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd3, 0xb320 पूर्ण,
	अणु 0xd4, 0x0000 पूर्ण,
	अणु 0xd6, 0x0400 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xdb, 0x0003 पूर्ण,
	अणु 0xdc, 0x0049 पूर्ण,
	अणु 0xdd, 0x001b पूर्ण,
	अणु 0xdf, 0x0008 पूर्ण,
	अणु 0xe0, 0x4000 पूर्ण,
	अणु 0xe6, 0x8000 पूर्ण,
	अणु 0xe7, 0x0200 पूर्ण,
	अणु 0xec, 0xb300 पूर्ण,
	अणु 0xed, 0x0000 पूर्ण,
	अणु 0xf0, 0x001f पूर्ण,
	अणु 0xf1, 0x020c पूर्ण,
	अणु 0xf2, 0x1f00 पूर्ण,
	अणु 0xf3, 0x0000 पूर्ण,
	अणु 0xf4, 0x4000 पूर्ण,
	अणु 0xf8, 0x0000 पूर्ण,
	अणु 0xf9, 0x0000 पूर्ण,
	अणु 0xfa, 0x2060 पूर्ण,
	अणु 0xfb, 0x4040 पूर्ण,
	अणु 0xfc, 0x0000 पूर्ण,
	अणु 0xfd, 0x0002 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6308 पूर्ण,
पूर्ण;

काष्ठा rt5645_eq_param_s अणु
	अचिन्हित लघु reg;
	अचिन्हित लघु val;
पूर्ण;

काष्ठा rt5645_eq_param_s_be16 अणु
	__be16 reg;
	__be16 val;
पूर्ण;

अटल स्थिर अक्षर *स्थिर rt5645_supply_names[] = अणु
	"avdd",
	"cpvdd",
पूर्ण;

काष्ठा rt5645_platक्रमm_data अणु
	/* IN2 can optionally be dअगरferential */
	bool in2_dअगरf;

	अचिन्हित पूर्णांक dmic1_data_pin;
	/* 0 = IN2N; 1 = GPIO5; 2 = GPIO11 */
	अचिन्हित पूर्णांक dmic2_data_pin;
	/* 0 = IN2P; 1 = GPIO6; 2 = GPIO10; 3 = GPIO12 */

	अचिन्हित पूर्णांक jd_mode;
	/* Use level triggered irq */
	bool level_trigger_irq;
	/* Invert JD1_1 status polarity */
	bool inv_jd1_1;
	/* Invert HP detect status polarity */
	bool inv_hp_pol;

	/* Value to assign to snd_soc_card.दीर्घ_name */
	स्थिर अक्षर *दीर्घ_name;

	/* Some (package) variants have the headset-mic pin not-connected */
	bool no_headset_mic;
पूर्ण;

काष्ठा rt5645_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा rt5645_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *i2c;
	काष्ठा gpio_desc *gpiod_hp_det;
	काष्ठा snd_soc_jack *hp_jack;
	काष्ठा snd_soc_jack *mic_jack;
	काष्ठा snd_soc_jack *btn_jack;
	काष्ठा delayed_work jack_detect_work, rcघड़ी_work;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(rt5645_supply_names)];
	काष्ठा rt5645_eq_param_s *eq_param;
	काष्ठा समयr_list btn_check_समयr;

	पूर्णांक codec_type;
	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck[RT5645_AIFS];
	पूर्णांक bclk[RT5645_AIFS];
	पूर्णांक master[RT5645_AIFS];

	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;

	पूर्णांक jack_type;
	bool en_button_func;
	पूर्णांक v_id;
पूर्ण;

अटल पूर्णांक rt5645_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, RT5645_RESET, 0);
पूर्ण

अटल bool rt5645_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5645_ranges); i++) अणु
		अगर (reg >= rt5645_ranges[i].range_min &&
			reg <= rt5645_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5645_RESET:
	हाल RT5645_PRIV_INDEX:
	हाल RT5645_PRIV_DATA:
	हाल RT5645_IN1_CTRL1:
	हाल RT5645_IN1_CTRL2:
	हाल RT5645_IN1_CTRL3:
	हाल RT5645_A_JD_CTRL1:
	हाल RT5645_ADC_EQ_CTRL1:
	हाल RT5645_EQ_CTRL1:
	हाल RT5645_ALC_CTRL_1:
	हाल RT5645_IRQ_CTRL2:
	हाल RT5645_IRQ_CTRL3:
	हाल RT5645_INT_IRQ_ST:
	हाल RT5645_IL_CMD:
	हाल RT5650_4BTN_IL_CMD1:
	हाल RT5645_VENDOR_ID:
	हाल RT5645_VENDOR_ID1:
	हाल RT5645_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5645_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5645_ranges); i++) अणु
		अगर (reg >= rt5645_ranges[i].range_min &&
			reg <= rt5645_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5645_RESET:
	हाल RT5645_SPK_VOL:
	हाल RT5645_HP_VOL:
	हाल RT5645_LOUT1:
	हाल RT5645_IN1_CTRL1:
	हाल RT5645_IN1_CTRL2:
	हाल RT5645_IN1_CTRL3:
	हाल RT5645_IN2_CTRL:
	हाल RT5645_INL1_INR1_VOL:
	हाल RT5645_SPK_FUNC_LIM:
	हाल RT5645_ADJ_HPF_CTRL:
	हाल RT5645_DAC1_DIG_VOL:
	हाल RT5645_DAC2_DIG_VOL:
	हाल RT5645_DAC_CTRL:
	हाल RT5645_STO1_ADC_DIG_VOL:
	हाल RT5645_MONO_ADC_DIG_VOL:
	हाल RT5645_ADC_BST_VOL1:
	हाल RT5645_ADC_BST_VOL2:
	हाल RT5645_STO1_ADC_MIXER:
	हाल RT5645_MONO_ADC_MIXER:
	हाल RT5645_AD_DA_MIXER:
	हाल RT5645_STO_DAC_MIXER:
	हाल RT5645_MONO_DAC_MIXER:
	हाल RT5645_DIG_MIXER:
	हाल RT5650_A_DAC_SOUR:
	हाल RT5645_DIG_INF1_DATA:
	हाल RT5645_PDM_OUT_CTRL:
	हाल RT5645_REC_L1_MIXER:
	हाल RT5645_REC_L2_MIXER:
	हाल RT5645_REC_R1_MIXER:
	हाल RT5645_REC_R2_MIXER:
	हाल RT5645_HPMIXL_CTRL:
	हाल RT5645_HPOMIXL_CTRL:
	हाल RT5645_HPMIXR_CTRL:
	हाल RT5645_HPOMIXR_CTRL:
	हाल RT5645_HPO_MIXER:
	हाल RT5645_SPK_L_MIXER:
	हाल RT5645_SPK_R_MIXER:
	हाल RT5645_SPO_MIXER:
	हाल RT5645_SPO_CLSD_RATIO:
	हाल RT5645_OUT_L1_MIXER:
	हाल RT5645_OUT_R1_MIXER:
	हाल RT5645_OUT_L_GAIN1:
	हाल RT5645_OUT_L_GAIN2:
	हाल RT5645_OUT_R_GAIN1:
	हाल RT5645_OUT_R_GAIN2:
	हाल RT5645_LOUT_MIXER:
	हाल RT5645_HAPTIC_CTRL1:
	हाल RT5645_HAPTIC_CTRL2:
	हाल RT5645_HAPTIC_CTRL3:
	हाल RT5645_HAPTIC_CTRL4:
	हाल RT5645_HAPTIC_CTRL5:
	हाल RT5645_HAPTIC_CTRL6:
	हाल RT5645_HAPTIC_CTRL7:
	हाल RT5645_HAPTIC_CTRL8:
	हाल RT5645_HAPTIC_CTRL9:
	हाल RT5645_HAPTIC_CTRL10:
	हाल RT5645_PWR_DIG1:
	हाल RT5645_PWR_DIG2:
	हाल RT5645_PWR_ANLG1:
	हाल RT5645_PWR_ANLG2:
	हाल RT5645_PWR_MIXER:
	हाल RT5645_PWR_VOL:
	हाल RT5645_PRIV_INDEX:
	हाल RT5645_PRIV_DATA:
	हाल RT5645_I2S1_SDP:
	हाल RT5645_I2S2_SDP:
	हाल RT5645_ADDA_CLK1:
	हाल RT5645_ADDA_CLK2:
	हाल RT5645_DMIC_CTRL1:
	हाल RT5645_DMIC_CTRL2:
	हाल RT5645_TDM_CTRL_1:
	हाल RT5645_TDM_CTRL_2:
	हाल RT5645_TDM_CTRL_3:
	हाल RT5650_TDM_CTRL_4:
	हाल RT5645_GLB_CLK:
	हाल RT5645_PLL_CTRL1:
	हाल RT5645_PLL_CTRL2:
	हाल RT5645_ASRC_1:
	हाल RT5645_ASRC_2:
	हाल RT5645_ASRC_3:
	हाल RT5645_ASRC_4:
	हाल RT5645_DEPOP_M1:
	हाल RT5645_DEPOP_M2:
	हाल RT5645_DEPOP_M3:
	हाल RT5645_CHARGE_PUMP:
	हाल RT5645_MICBIAS:
	हाल RT5645_A_JD_CTRL1:
	हाल RT5645_VAD_CTRL4:
	हाल RT5645_CLSD_OUT_CTRL:
	हाल RT5645_ADC_EQ_CTRL1:
	हाल RT5645_ADC_EQ_CTRL2:
	हाल RT5645_EQ_CTRL1:
	हाल RT5645_EQ_CTRL2:
	हाल RT5645_ALC_CTRL_1:
	हाल RT5645_ALC_CTRL_2:
	हाल RT5645_ALC_CTRL_3:
	हाल RT5645_ALC_CTRL_4:
	हाल RT5645_ALC_CTRL_5:
	हाल RT5645_JD_CTRL:
	हाल RT5645_IRQ_CTRL1:
	हाल RT5645_IRQ_CTRL2:
	हाल RT5645_IRQ_CTRL3:
	हाल RT5645_INT_IRQ_ST:
	हाल RT5645_GPIO_CTRL1:
	हाल RT5645_GPIO_CTRL2:
	हाल RT5645_GPIO_CTRL3:
	हाल RT5645_BASS_BACK:
	हाल RT5645_MP3_PLUS1:
	हाल RT5645_MP3_PLUS2:
	हाल RT5645_ADJ_HPF1:
	हाल RT5645_ADJ_HPF2:
	हाल RT5645_HP_CALIB_AMP_DET:
	हाल RT5645_SV_ZCD1:
	हाल RT5645_SV_ZCD2:
	हाल RT5645_IL_CMD:
	हाल RT5645_IL_CMD2:
	हाल RT5645_IL_CMD3:
	हाल RT5650_4BTN_IL_CMD1:
	हाल RT5650_4BTN_IL_CMD2:
	हाल RT5645_DRC1_HL_CTRL1:
	हाल RT5645_DRC2_HL_CTRL1:
	हाल RT5645_ADC_MONO_HP_CTRL1:
	हाल RT5645_ADC_MONO_HP_CTRL2:
	हाल RT5645_DRC2_CTRL1:
	हाल RT5645_DRC2_CTRL2:
	हाल RT5645_DRC2_CTRL3:
	हाल RT5645_DRC2_CTRL4:
	हाल RT5645_DRC2_CTRL5:
	हाल RT5645_JD_CTRL3:
	हाल RT5645_JD_CTRL4:
	हाल RT5645_GEN_CTRL1:
	हाल RT5645_GEN_CTRL2:
	हाल RT5645_GEN_CTRL3:
	हाल RT5645_VENDOR_ID:
	हाल RT5645_VENDOR_ID1:
	हाल RT5645_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -6525, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);

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

/* अणु-6, -4.5, -3, -1.5, 0, 0.82, 1.58, 2.28पूर्ण dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(spk_clsd_tlv,
	0, 4, TLV_DB_SCALE_ITEM(-600, 150, 0),
	5, 5, TLV_DB_SCALE_ITEM(82, 0, 0),
	6, 6, TLV_DB_SCALE_ITEM(158, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(228, 0, 0)
);

अटल पूर्णांक rt5645_hweq_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = RT5645_HWEQ_NUM * माप(काष्ठा rt5645_eq_param_s);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_hweq_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	काष्ठा rt5645_eq_param_s_be16 *eq_param =
		(काष्ठा rt5645_eq_param_s_be16 *)ucontrol->value.bytes.data;
	पूर्णांक i;

	क्रम (i = 0; i < RT5645_HWEQ_NUM; i++) अणु
		eq_param[i].reg = cpu_to_be16(rt5645->eq_param[i].reg);
		eq_param[i].val = cpu_to_be16(rt5645->eq_param[i].val);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rt5645_validate_hweq(अचिन्हित लघु reg)
अणु
	अगर ((reg >= 0x1a4 && reg <= 0x1cd) || (reg >= 0x1e5 && reg <= 0x1f8) ||
		(reg == RT5645_EQ_CTRL2))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक rt5645_hweq_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	काष्ठा rt5645_eq_param_s_be16 *eq_param =
		(काष्ठा rt5645_eq_param_s_be16 *)ucontrol->value.bytes.data;
	पूर्णांक i;

	क्रम (i = 0; i < RT5645_HWEQ_NUM; i++) अणु
		rt5645->eq_param[i].reg = be16_to_cpu(eq_param[i].reg);
		rt5645->eq_param[i].val = be16_to_cpu(eq_param[i].val);
	पूर्ण

	/* The final setting of the table should be RT5645_EQ_CTRL2 */
	क्रम (i = RT5645_HWEQ_NUM - 1; i >= 0; i--) अणु
		अगर (rt5645->eq_param[i].reg == 0)
			जारी;
		अन्यथा अगर (rt5645->eq_param[i].reg != RT5645_EQ_CTRL2)
			वापस 0;
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < RT5645_HWEQ_NUM; i++) अणु
		अगर (!rt5645_validate_hweq(rt5645->eq_param[i].reg) &&
		    rt5645->eq_param[i].reg != 0)
			वापस 0;
		अन्यथा अगर (rt5645->eq_param[i].reg == 0)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RT5645_HWEQ(xname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = rt5645_hweq_info, \
	.get = rt5645_hweq_get, \
	.put = rt5645_hweq_put \
पूर्ण

अटल पूर्णांक rt5645_spk_put_volsw(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
		RT5645_PWR_CLK25M_MASK, RT5645_PWR_CLK25M_PU);

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

	mod_delayed_work(प्रणाली_घातer_efficient_wq, &rt5645->rcघड़ी_work,
		msecs_to_jअगरfies(200));

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर rt5645_dac1_vol_ctrl_mode_text[] = अणु
	"immediately", "zero crossing", "soft ramp"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_dac1_vol_ctrl_mode, RT5645_PR_BASE,
	RT5645_DA1_ZDET_SFT, rt5645_dac1_vol_ctrl_mode_text);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_snd_controls[] = अणु
	/* Speaker Output Volume */
	SOC_DOUBLE("Speaker Channel Switch", RT5645_SPK_VOL,
		RT5645_VOL_L_SFT, RT5645_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_EXT_TLV("Speaker Playback Volume", RT5645_SPK_VOL,
		RT5645_L_VOL_SFT, RT5645_R_VOL_SFT, 39, 1, snd_soc_get_volsw,
		rt5645_spk_put_volsw, out_vol_tlv),

	/* ClassD modulator Speaker Gain Ratio */
	SOC_SINGLE_TLV("Speaker ClassD Playback Volume", RT5645_SPO_CLSD_RATIO,
		RT5645_SPK_G_CLSD_SFT, 7, 0, spk_clsd_tlv),

	/* Headphone Output Volume */
	SOC_DOUBLE("Headphone Channel Switch", RT5645_HP_VOL,
		RT5645_VOL_L_SFT, RT5645_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("Headphone Playback Volume", RT5645_HP_VOL,
		RT5645_L_VOL_SFT, RT5645_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* OUTPUT Control */
	SOC_DOUBLE("OUT Playback Switch", RT5645_LOUT1,
		RT5645_L_MUTE_SFT, RT5645_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("OUT Channel Switch", RT5645_LOUT1,
		RT5645_VOL_L_SFT, RT5645_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5645_LOUT1,
		RT5645_L_VOL_SFT, RT5645_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE("DAC2 Playback Switch", RT5645_DAC_CTRL,
		RT5645_M_DAC_L2_VOL_SFT, RT5645_M_DAC_R2_VOL_SFT, 1, 1),
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5645_DAC1_DIG_VOL,
		RT5645_L_VOL_SFT + 1, RT5645_R_VOL_SFT + 1, 87, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("Mono DAC Playback Volume", RT5645_DAC2_DIG_VOL,
		RT5645_L_VOL_SFT + 1, RT5645_R_VOL_SFT + 1, 87, 0, dac_vol_tlv),

	/* IN1/IN2 Control */
	SOC_SINGLE_TLV("IN1 Boost", RT5645_IN1_CTRL1,
		RT5645_BST_SFT1, 12, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost", RT5645_IN2_CTRL,
		RT5645_BST_SFT2, 8, 0, bst_tlv),

	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5645_INL1_INR1_VOL,
		RT5645_INL_VOL_SFT, RT5645_INR_VOL_SFT, 31, 1, in_vol_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5645_STO1_ADC_DIG_VOL,
		RT5645_L_MUTE_SFT, RT5645_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5645_STO1_ADC_DIG_VOL,
		RT5645_L_VOL_SFT + 1, RT5645_R_VOL_SFT + 1, 63, 0, adc_vol_tlv),
	SOC_DOUBLE("Mono ADC Capture Switch", RT5645_MONO_ADC_DIG_VOL,
		RT5645_L_MUTE_SFT, RT5645_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5645_MONO_ADC_DIG_VOL,
		RT5645_L_VOL_SFT + 1, RT5645_R_VOL_SFT + 1, 63, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("ADC Boost Capture Volume", RT5645_ADC_BST_VOL1,
		RT5645_STO1_ADC_L_BST_SFT, RT5645_STO1_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),
	SOC_DOUBLE_TLV("Mono ADC Boost Capture Volume", RT5645_ADC_BST_VOL2,
		RT5645_MONO_ADC_L_BST_SFT, RT5645_MONO_ADC_R_BST_SFT, 3, 0,
		adc_bst_tlv),

	/* I2S2 function select */
	SOC_SINGLE("I2S2 Func Switch", RT5645_GPIO_CTRL1, RT5645_I2S2_SEL_SFT,
		1, 1),
	RT5645_HWEQ("Speaker HWEQ"),

	/* Digital Soft Volume Control */
	SOC_ENUM("DAC1 Digital Volume Control Func", rt5645_dac1_vol_ctrl_mode),
पूर्ण;

/**
 * set_dmic_clk - Set parameter of dmic.
 *
 * @w: DAPM widget.
 * @kcontrol: The kcontrol of this widget.
 * @event: Event id.
 *
 */
अटल पूर्णांक set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5645->sysclk / rl6231_get_pre_भाग(rt5645->regmap,
		RT5645_ADDA_CLK1, RT5645_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		snd_soc_component_update_bits(component, RT5645_DMIC_CTRL1,
			RT5645_DMIC_CLK_MASK, idx << RT5645_DMIC_CLK_SFT);
	वापस idx;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT5645_GLB_CLK);
	val &= RT5645_SCLK_SRC_MASK;
	अगर (val == RT5645_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg, shअगरt, val;

	चयन (source->shअगरt) अणु
	हाल 0:
		reg = RT5645_ASRC_3;
		shअगरt = 0;
		अवरोध;
	हाल 1:
		reg = RT5645_ASRC_3;
		shअगरt = 4;
		अवरोध;
	हाल 3:
		reg = RT5645_ASRC_2;
		shअगरt = 0;
		अवरोध;
	हाल 8:
		reg = RT5645_ASRC_2;
		shअगरt = 4;
		अवरोध;
	हाल 9:
		reg = RT5645_ASRC_2;
		shअगरt = 8;
		अवरोध;
	हाल 10:
		reg = RT5645_ASRC_2;
		shअगरt = 12;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	val = (snd_soc_component_पढ़ो(component, reg) >> shअगरt) & 0xf;
	चयन (val) अणु
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

पूर्ण

अटल पूर्णांक rt5645_enable_hweq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < RT5645_HWEQ_NUM; i++) अणु
		अगर (rt5645_validate_hweq(rt5645->eq_param[i].reg))
			regmap_ग_लिखो(rt5645->regmap, rt5645->eq_param[i].reg,
					rt5645->eq_param[i].val);
		अन्यथा
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rt5645_sel_asrc_clk_src - select ASRC घड़ी source क्रम a set of filters
 * @component: SoC audio component device.
 * @filter_mask: mask of filters.
 * @clk_src: घड़ी source
 *
 * The ASRC function is क्रम asynchronous MCLK and LRCK. Also, since RT5645 can
 * only support standard 32fs or 64fs i2s क्रमmat, ASRC should be enabled to
 * support special i2s घड़ी क्रमmat such as Intel's 100fs(100 * sampling rate).
 * ASRC function will track i2s घड़ी and generate a corresponding प्रणाली घड़ी
 * क्रम codec. This function provides an API to select the घड़ी source क्रम a
 * set of filters specअगरied by the mask. And the codec driver will turn on ASRC
 * क्रम these filters अगर ASRC is selected as their घड़ी source.
 */
पूर्णांक rt5645_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	अचिन्हित पूर्णांक asrc2_mask = 0;
	अचिन्हित पूर्णांक asrc2_value = 0;
	अचिन्हित पूर्णांक asrc3_mask = 0;
	अचिन्हित पूर्णांक asrc3_value = 0;

	चयन (clk_src) अणु
	हाल RT5645_CLK_SEL_SYS:
	हाल RT5645_CLK_SEL_I2S1_ASRC:
	हाल RT5645_CLK_SEL_I2S2_ASRC:
	हाल RT5645_CLK_SEL_SYS2:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (filter_mask & RT5645_DA_STEREO_FILTER) अणु
		asrc2_mask |= RT5645_DA_STO_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_STO_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_STO_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5645_DA_MONO_L_FILTER) अणु
		asrc2_mask |= RT5645_DA_MONOL_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5645_DA_MONO_R_FILTER) अणु
		asrc2_mask |= RT5645_DA_MONOR_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5645_AD_STEREO_FILTER) अणु
		asrc2_mask |= RT5645_AD_STO1_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_AD_STO1_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_STO1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5645_AD_MONO_L_FILTER) अणु
		asrc3_mask |= RT5645_AD_MONOL_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5645_AD_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5645_AD_MONO_R_FILTER)  अणु
		asrc3_mask |= RT5645_AD_MONOR_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5645_AD_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc2_mask)
		snd_soc_component_update_bits(component, RT5645_ASRC_2,
			asrc2_mask, asrc2_value);

	अगर (asrc3_mask)
		snd_soc_component_update_bits(component, RT5645_ASRC_3,
			asrc3_mask, asrc3_value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5645_sel_asrc_clk_src);

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5645_STO1_ADC_MIXER,
			RT5645_M_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5645_STO1_ADC_MIXER,
			RT5645_M_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5645_STO1_ADC_MIXER,
			RT5645_M_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5645_STO1_ADC_MIXER,
			RT5645_M_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5645_MONO_ADC_MIXER,
			RT5645_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5645_MONO_ADC_MIXER,
			RT5645_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5645_MONO_ADC_MIXER,
			RT5645_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5645_MONO_ADC_MIXER,
			RT5645_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5645_AD_DA_MIXER,
			RT5645_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 Switch", RT5645_AD_DA_MIXER,
			RT5645_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5645_AD_DA_MIXER,
			RT5645_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_AUTODISABLE("DAC1 Switch", RT5645_AD_DA_MIXER,
			RT5645_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_L2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_R1_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_R2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_STO_DAC_MIXER,
			RT5645_M_DAC_L1_STO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_L1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_L2_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_R2_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_R1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_R2_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_MONO_DAC_MIXER,
			RT5645_M_DAC_L2_MONO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dig_l_mix[] = अणु
	SOC_DAPM_SINGLE("Sto DAC Mix L Switch", RT5645_DIG_MIXER,
			RT5645_M_STO_L_DAC_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_DIG_MIXER,
			RT5645_M_DAC_L2_DAC_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_DIG_MIXER,
			RT5645_M_DAC_R2_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dig_r_mix[] = अणु
	SOC_DAPM_SINGLE("Sto DAC Mix R Switch", RT5645_DIG_MIXER,
			RT5645_M_STO_R_DAC_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_DIG_MIXER,
			RT5645_M_DAC_R2_DAC_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_DIG_MIXER,
			RT5645_M_DAC_L2_DAC_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5645_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("HPOL Switch", RT5645_REC_L2_MIXER,
			RT5645_M_HP_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5645_REC_L2_MIXER,
			RT5645_M_IN_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5645_REC_L2_MIXER,
			RT5645_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5645_REC_L2_MIXER,
			RT5645_M_BST1_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXL Switch", RT5645_REC_L2_MIXER,
			RT5645_M_OM_L_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("HPOR Switch", RT5645_REC_R2_MIXER,
			RT5645_M_HP_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5645_REC_R2_MIXER,
			RT5645_M_IN_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5645_REC_R2_MIXER,
			RT5645_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5645_REC_R2_MIXER,
			RT5645_M_BST1_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXR Switch", RT5645_REC_R2_MIXER,
			RT5645_M_OM_R_RM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_spk_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_SPK_L_MIXER,
			RT5645_M_DAC_L1_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_SPK_L_MIXER,
			RT5645_M_DAC_L2_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5645_SPK_L_MIXER,
			RT5645_M_IN_L_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5645_SPK_L_MIXER,
			RT5645_M_BST1_L_SM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_spk_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_SPK_R_MIXER,
			RT5645_M_DAC_R1_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_SPK_R_MIXER,
			RT5645_M_DAC_R2_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5645_SPK_R_MIXER,
			RT5645_M_IN_R_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5645_SPK_R_MIXER,
			RT5645_M_BST2_R_SM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST1 Switch", RT5645_OUT_L1_MIXER,
			RT5645_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5645_OUT_L1_MIXER,
			RT5645_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5645_OUT_L1_MIXER,
			RT5645_M_DAC_L2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_OUT_L1_MIXER,
			RT5645_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5645_OUT_R1_MIXER,
			RT5645_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5645_OUT_R1_MIXER,
			RT5645_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5645_OUT_R1_MIXER,
			RT5645_M_DAC_R2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_OUT_R1_MIXER,
			RT5645_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_spo_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_SPO_MIXER,
			RT5645_M_DAC_R1_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_SPO_MIXER,
			RT5645_M_DAC_L1_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL R Switch", RT5645_SPO_MIXER,
			RT5645_M_SV_R_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL L Switch", RT5645_SPO_MIXER,
			RT5645_M_SV_L_SPM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_spo_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_SPO_MIXER,
			RT5645_M_DAC_R1_SPM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL R Switch", RT5645_SPO_MIXER,
			RT5645_M_SV_R_SPM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5645_HPO_MIXER,
			RT5645_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPVOL Switch", RT5645_HPO_MIXER,
			RT5645_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_hpvoll_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5645_HPOMIXL_CTRL,
			RT5645_M_DAC1_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC2 Switch", RT5645_HPOMIXL_CTRL,
			RT5645_M_DAC2_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5645_HPOMIXL_CTRL,
			RT5645_M_IN_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5645_HPOMIXL_CTRL,
			RT5645_M_BST1_HV_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_hpvolr_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5645_HPOMIXR_CTRL,
			RT5645_M_DAC1_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC2 Switch", RT5645_HPOMIXR_CTRL,
			RT5645_M_DAC2_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5645_HPOMIXR_CTRL,
			RT5645_M_IN_HV_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5645_HPOMIXR_CTRL,
			RT5645_M_BST2_HV_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5645_LOUT_MIXER,
			RT5645_M_DAC_L1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5645_LOUT_MIXER,
			RT5645_M_DAC_R1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIX L Switch", RT5645_LOUT_MIXER,
			RT5645_M_OV_L_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIX R Switch", RT5645_LOUT_MIXER,
			RT5645_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

/*DAC1 L/R source*/ /* MX-29 [9:8] [11:10] */
अटल स्थिर अक्षर * स्थिर rt5645_dac1_src[] = अणु
	"IF1 DAC", "IF2 DAC", "IF3 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_dac1l_क्रमागत, RT5645_AD_DA_MIXER,
	RT5645_DAC1_L_SEL_SFT, rt5645_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac1l_mux =
	SOC_DAPM_ENUM("DAC1 L source", rt5645_dac1l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_dac1r_क्रमागत, RT5645_AD_DA_MIXER,
	RT5645_DAC1_R_SEL_SFT, rt5645_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac1r_mux =
	SOC_DAPM_ENUM("DAC1 R source", rt5645_dac1r_क्रमागत);

/*DAC2 L/R source*/ /* MX-1B [6:4] [2:0] */
अटल स्थिर अक्षर * स्थिर rt5645_dac12_src[] = अणु
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "Mono ADC", "VAD_ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_dac2l_क्रमागत, RT5645_DAC_CTRL,
	RT5645_DAC2_L_SEL_SFT, rt5645_dac12_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac_l2_mux =
	SOC_DAPM_ENUM("DAC2 L source", rt5645_dac2l_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5645_dacr2_src[] = अणु
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "Mono ADC", "Haptic"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_dac2r_क्रमागत, RT5645_DAC_CTRL,
	RT5645_DAC2_R_SEL_SFT, rt5645_dacr2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_dac_r2_mux =
	SOC_DAPM_ENUM("DAC2 R source", rt5645_dac2r_क्रमागत);

/* Stereo1 ADC source */
/* MX-27 [12] */
अटल स्थिर अक्षर * स्थिर rt5645_stereo_adc1_src[] = अणु
	"DAC MIX", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_stereo1_adc1_क्रमागत, RT5645_STO1_ADC_MIXER,
	RT5645_ADC_1_SRC_SFT, rt5645_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto_adc1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1 Mux", rt5645_stereo1_adc1_क्रमागत);

/* MX-27 [11] */
अटल स्थिर अक्षर * स्थिर rt5645_stereo_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_stereo1_adc2_क्रमागत, RT5645_STO1_ADC_MIXER,
	RT5645_ADC_2_SRC_SFT, rt5645_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto_adc2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2 Mux", rt5645_stereo1_adc2_क्रमागत);

/* MX-27 [8] */
अटल स्थिर अक्षर * स्थिर rt5645_stereo_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_stereo1_dmic_क्रमागत, RT5645_STO1_ADC_MIXER,
	RT5645_DMIC_SRC_SFT, rt5645_stereo_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC source", rt5645_stereo1_dmic_क्रमागत);

/* Mono ADC source */
/* MX-28 [12] */
अटल स्थिर अक्षर * स्थिर rt5645_mono_adc_l1_src[] = अणु
	"Mono DAC MIXL", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_adc_l1_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_ADC_L1_SRC_SFT, rt5645_mono_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_l1_mux =
	SOC_DAPM_ENUM("Mono ADC1 left source", rt5645_mono_adc_l1_क्रमागत);
/* MX-28 [11] */
अटल स्थिर अक्षर * स्थिर rt5645_mono_adc_l2_src[] = अणु
	"Mono DAC MIXL", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_adc_l2_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_ADC_L2_SRC_SFT, rt5645_mono_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_l2_mux =
	SOC_DAPM_ENUM("Mono ADC2 left source", rt5645_mono_adc_l2_क्रमागत);

/* MX-28 [8] */
अटल स्थिर अक्षर * स्थिर rt5645_mono_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_dmic_l_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_DMIC_L_SRC_SFT, rt5645_mono_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_dmic_l_mux =
	SOC_DAPM_ENUM("Mono DMIC left source", rt5645_mono_dmic_l_क्रमागत);
/* MX-28 [1:0] */
अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_dmic_r_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_DMIC_R_SRC_SFT, rt5645_mono_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_dmic_r_mux =
	SOC_DAPM_ENUM("Mono DMIC Right source", rt5645_mono_dmic_r_क्रमागत);
/* MX-28 [4] */
अटल स्थिर अक्षर * स्थिर rt5645_mono_adc_r1_src[] = अणु
	"Mono DAC MIXR", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_adc_r1_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_ADC_R1_SRC_SFT, rt5645_mono_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_r1_mux =
	SOC_DAPM_ENUM("Mono ADC1 right source", rt5645_mono_adc_r1_क्रमागत);
/* MX-28 [3] */
अटल स्थिर अक्षर * स्थिर rt5645_mono_adc_r2_src[] = अणु
	"Mono DAC MIXR", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_mono_adc_r2_क्रमागत, RT5645_MONO_ADC_MIXER,
	RT5645_MONO_ADC_R2_SRC_SFT, rt5645_mono_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_mono_adc_r2_mux =
	SOC_DAPM_ENUM("Mono ADC2 right source", rt5645_mono_adc_r2_क्रमागत);

/* MX-77 [9:8] */
अटल स्थिर अक्षर * स्थिर rt5645_अगर1_adc_in_src[] = अणु
	"IF_ADC1/IF_ADC2/VAD_ADC", "IF_ADC2/IF_ADC1/VAD_ADC",
	"VAD_ADC/IF_ADC1/IF_ADC2", "VAD_ADC/IF_ADC2/IF_ADC1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_अगर1_adc_in_क्रमागत, RT5645_TDM_CTRL_1,
	RT5645_IF1_ADC_IN_SFT, rt5645_अगर1_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_adc_in_mux =
	SOC_DAPM_ENUM("IF1 ADC IN source", rt5645_अगर1_adc_in_क्रमागत);

/* MX-78 [4:0] */
अटल स्थिर अक्षर * स्थिर rt5650_अगर1_adc_in_src[] = अणु
	"IF_ADC1/IF_ADC2/DAC_REF/Null",
	"IF_ADC1/IF_ADC2/Null/DAC_REF",
	"IF_ADC1/DAC_REF/IF_ADC2/Null",
	"IF_ADC1/DAC_REF/Null/IF_ADC2",
	"IF_ADC1/Null/DAC_REF/IF_ADC2",
	"IF_ADC1/Null/IF_ADC2/DAC_REF",

	"IF_ADC2/IF_ADC1/DAC_REF/Null",
	"IF_ADC2/IF_ADC1/Null/DAC_REF",
	"IF_ADC2/DAC_REF/IF_ADC1/Null",
	"IF_ADC2/DAC_REF/Null/IF_ADC1",
	"IF_ADC2/Null/DAC_REF/IF_ADC1",
	"IF_ADC2/Null/IF_ADC1/DAC_REF",

	"DAC_REF/IF_ADC1/IF_ADC2/Null",
	"DAC_REF/IF_ADC1/Null/IF_ADC2",
	"DAC_REF/IF_ADC2/IF_ADC1/Null",
	"DAC_REF/IF_ADC2/Null/IF_ADC1",
	"DAC_REF/Null/IF_ADC1/IF_ADC2",
	"DAC_REF/Null/IF_ADC2/IF_ADC1",

	"Null/IF_ADC1/IF_ADC2/DAC_REF",
	"Null/IF_ADC1/DAC_REF/IF_ADC2",
	"Null/IF_ADC2/IF_ADC1/DAC_REF",
	"Null/IF_ADC2/DAC_REF/IF_ADC1",
	"Null/DAC_REF/IF_ADC1/IF_ADC2",
	"Null/DAC_REF/IF_ADC2/IF_ADC1",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5650_अगर1_adc_in_क्रमागत, RT5645_TDM_CTRL_2,
	0, rt5650_अगर1_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_adc_in_mux =
	SOC_DAPM_ENUM("IF1 ADC IN source", rt5650_अगर1_adc_in_क्रमागत);

/* MX-78 [15:14][13:12][11:10] */
अटल स्थिर अक्षर * स्थिर rt5645_tdm_adc_swap_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_adc_slot0_1_क्रमागत,
	RT5645_TDM_CTRL_2, 14, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_adc1_in_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN source", rt5650_tdm_adc_slot0_1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_adc_slot2_3_क्रमागत,
	RT5645_TDM_CTRL_2, 12, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_adc2_in_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN source", rt5650_tdm_adc_slot2_3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_adc_slot4_5_क्रमागत,
	RT5645_TDM_CTRL_2, 10, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_adc3_in_mux =
	SOC_DAPM_ENUM("IF1 ADC3 IN source", rt5650_tdm_adc_slot4_5_क्रमागत);

/* MX-77 [7:6][5:4][3:2] */
अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_adc_slot0_1_क्रमागत,
	RT5645_TDM_CTRL_1, 6, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_adc1_in_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN source", rt5645_tdm_adc_slot0_1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_adc_slot2_3_क्रमागत,
	RT5645_TDM_CTRL_1, 4, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_adc2_in_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN source", rt5645_tdm_adc_slot2_3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_adc_slot4_5_क्रमागत,
	RT5645_TDM_CTRL_1, 2, rt5645_tdm_adc_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_adc3_in_mux =
	SOC_DAPM_ENUM("IF1 ADC3 IN source", rt5645_tdm_adc_slot4_5_क्रमागत);

/* MX-79 [14:12][10:8][6:4][2:0] */
अटल स्थिर अक्षर * स्थिर rt5645_tdm_dac_swap_select[] = अणु
	"Slot0", "Slot1", "Slot2", "Slot3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_dac0_क्रमागत,
	RT5645_TDM_CTRL_3, 12, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_dac0_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC0 source", rt5645_tdm_dac0_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_dac1_क्रमागत,
	RT5645_TDM_CTRL_3, 8, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_dac1_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC1 source", rt5645_tdm_dac1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_dac2_क्रमागत,
	RT5645_TDM_CTRL_3, 4, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_dac2_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC2 source", rt5645_tdm_dac2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5645_tdm_dac3_क्रमागत,
	RT5645_TDM_CTRL_3, 0, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर1_dac3_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC3 source", rt5645_tdm_dac3_क्रमागत);

/* MX-7a [14:12][10:8][6:4][2:0] */
अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_dac0_क्रमागत,
	RT5650_TDM_CTRL_4, 12, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_dac0_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC0 source", rt5650_tdm_dac0_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_dac1_क्रमागत,
	RT5650_TDM_CTRL_4, 8, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_dac1_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC1 source", rt5650_tdm_dac1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_dac2_क्रमागत,
	RT5650_TDM_CTRL_4, 4, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_dac2_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC2 source", rt5650_tdm_dac2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5650_tdm_dac3_क्रमागत,
	RT5650_TDM_CTRL_4, 0, rt5645_tdm_dac_swap_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_अगर1_dac3_tdm_sel_mux =
	SOC_DAPM_ENUM("IF1 DAC3 source", rt5650_tdm_dac3_क्रमागत);

/* MX-2d [3] [2] */
अटल स्थिर अक्षर * स्थिर rt5650_a_dac1_src[] = अणु
	"DAC1", "Stereo DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5650_a_dac1_l_क्रमागत, RT5650_A_DAC_SOUR,
	RT5650_A_DAC1_L_IN_SFT, rt5650_a_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_a_dac1_l_mux =
	SOC_DAPM_ENUM("A DAC1 L source", rt5650_a_dac1_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5650_a_dac1_r_क्रमागत, RT5650_A_DAC_SOUR,
	RT5650_A_DAC1_R_IN_SFT, rt5650_a_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_a_dac1_r_mux =
	SOC_DAPM_ENUM("A DAC1 R source", rt5650_a_dac1_r_क्रमागत);

/* MX-2d [1] [0] */
अटल स्थिर अक्षर * स्थिर rt5650_a_dac2_src[] = अणु
	"Stereo DAC Mixer", "Mono DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5650_a_dac2_l_क्रमागत, RT5650_A_DAC_SOUR,
	RT5650_A_DAC2_L_IN_SFT, rt5650_a_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_a_dac2_l_mux =
	SOC_DAPM_ENUM("A DAC2 L source", rt5650_a_dac2_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5650_a_dac2_r_क्रमागत, RT5650_A_DAC_SOUR,
	RT5650_A_DAC2_R_IN_SFT, rt5650_a_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5650_a_dac2_r_mux =
	SOC_DAPM_ENUM("A DAC2 R source", rt5650_a_dac2_r_क्रमागत);

/* MX-2F [13:12] */
अटल स्थिर अक्षर * स्थिर rt5645_अगर2_adc_in_src[] = अणु
	"IF_ADC1", "IF_ADC2", "VAD_ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_अगर2_adc_in_क्रमागत, RT5645_DIG_INF1_DATA,
	RT5645_IF2_ADC_IN_SFT, rt5645_अगर2_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_अगर2_adc_in_mux =
	SOC_DAPM_ENUM("IF2 ADC IN source", rt5645_अगर2_adc_in_क्रमागत);

/* MX-31 [15] [13] [11] [9] */
अटल स्थिर अक्षर * स्थिर rt5645_pdm_src[] = अणु
	"Mono DAC", "Stereo DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_pdm1_l_क्रमागत, RT5645_PDM_OUT_CTRL,
	RT5645_PDM1_L_SFT, rt5645_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_pdm1_l_mux =
	SOC_DAPM_ENUM("PDM1 L source", rt5645_pdm1_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_pdm1_r_क्रमागत, RT5645_PDM_OUT_CTRL,
	RT5645_PDM1_R_SFT, rt5645_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_pdm1_r_mux =
	SOC_DAPM_ENUM("PDM1 R source", rt5645_pdm1_r_क्रमागत);

/* MX-9D [9:8] */
अटल स्थिर अक्षर * स्थिर rt5645_vad_adc_src[] = अणु
	"Sto1 ADC L", "Mono ADC L", "Mono ADC R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5645_vad_adc_क्रमागत, RT5645_VAD_CTRL4,
	RT5645_VAD_SEL_SFT, rt5645_vad_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5645_vad_adc_mux =
	SOC_DAPM_ENUM("VAD ADC source", rt5645_vad_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new spk_l_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_SPK_VOL,
		RT5645_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spk_r_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_SPK_VOL,
		RT5645_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hp_l_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_HP_VOL,
		RT5645_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hp_r_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_HP_VOL,
		RT5645_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm1_l_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_PDM_OUT_CTRL,
		RT5645_M_PDM1_L, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm1_r_vol_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5645_PDM_OUT_CTRL,
		RT5645_M_PDM1_R, 1, 1);

अटल व्योम hp_amp_घातer(काष्ठा snd_soc_component *component, पूर्णांक on)
अणु
	अटल पूर्णांक hp_amp_घातer_count;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, val;

	अगर (on) अणु
		अगर (hp_amp_घातer_count <= 0) अणु
			अगर (rt5645->codec_type == CODEC_TYPE_RT5650) अणु
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M2, 0x3100);
				snd_soc_component_ग_लिखो(component, RT5645_CHARGE_PUMP,
					0x0e06);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M1, 0x000d);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					RT5645_HP_DCC_INT1, 0x9f01);
				क्रम (i = 0; i < 20; i++) अणु
					usleep_range(1000, 1500);
					regmap_पढ़ो(rt5645->regmap, RT5645_PR_BASE +
						RT5645_HP_DCC_INT1, &val);
					अगर (!(val & 0x8000))
						अवरोध;
				पूर्ण
				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_CO_MASK, RT5645_HP_CO_EN);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					0x3e, 0x7400);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M3, 0x0737);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					RT5645_MAMP_INT_REG2, 0xfc00);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M2, 0x1140);
				msleep(90);
			पूर्ण अन्यथा अणु
				/* depop parameters */
				snd_soc_component_update_bits(component, RT5645_DEPOP_M2,
					RT5645_DEPOP_MASK, RT5645_DEPOP_MAN);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M1, 0x000d);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					RT5645_HP_DCC_INT1, 0x9f01);
				mdelay(150);
				/* headphone amp घातer on */
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_FV1 | RT5645_PWR_FV2, 0);
				snd_soc_component_update_bits(component, RT5645_PWR_VOL,
					RT5645_PWR_HV_L | RT5645_PWR_HV_R,
					RT5645_PWR_HV_L | RT5645_PWR_HV_R);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA);
				mdelay(5);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_FV1 | RT5645_PWR_FV2,
					RT5645_PWR_FV1 | RT5645_PWR_FV2);

				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_CO_MASK | RT5645_HP_SG_MASK,
					RT5645_HP_CO_EN | RT5645_HP_SG_EN);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					0x14, 0x1aaa);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					0x24, 0x0430);
			पूर्ण
		पूर्ण
		hp_amp_घातer_count++;
	पूर्ण अन्यथा अणु
		hp_amp_घातer_count--;
		अगर (hp_amp_घातer_count <= 0) अणु
			अगर (rt5645->codec_type == CODEC_TYPE_RT5650) अणु
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					0x3e, 0x7400);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M3, 0x0737);
				regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
					RT5645_MAMP_INT_REG2, 0xfc00);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M2, 0x1140);
				msleep(100);
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M1, 0x0001);

			पूर्ण अन्यथा अणु
				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_SG_MASK |
					RT5645_HP_L_SMT_MASK |
					RT5645_HP_R_SMT_MASK,
					RT5645_HP_SG_DIS |
					RT5645_HP_L_SMT_DIS |
					RT5645_HP_R_SMT_DIS);
				/* headphone amp घातer करोwn */
				snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M1, 0x0000);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA, 0);
				snd_soc_component_update_bits(component, RT5645_DEPOP_M2,
					RT5645_DEPOP_MASK, 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rt5645_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		hp_amp_घातer(component, 1);
		/* headphone unmute sequence */
		अगर (rt5645->codec_type == CODEC_TYPE_RT5645) अणु
			snd_soc_component_update_bits(component, RT5645_DEPOP_M3,
				RT5645_CP_FQ1_MASK | RT5645_CP_FQ2_MASK |
				RT5645_CP_FQ3_MASK,
				(RT5645_CP_FQ_192_KHZ << RT5645_CP_FQ1_SFT) |
				(RT5645_CP_FQ_12_KHZ << RT5645_CP_FQ2_SFT) |
				(RT5645_CP_FQ_192_KHZ << RT5645_CP_FQ3_SFT));
			regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
				RT5645_MAMP_INT_REG2, 0xfc00);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_SMT_TRIG_MASK, RT5645_SMT_TRIG_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTN_MASK, RT5645_RSTN_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTN_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_RSTN_DIS |
				RT5645_HP_L_SMT_EN | RT5645_HP_R_SMT_EN);
			msleep(40);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_HP_SG_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_HP_SG_DIS |
				RT5645_HP_L_SMT_DIS | RT5645_HP_R_SMT_DIS);
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* headphone mute sequence */
		अगर (rt5645->codec_type == CODEC_TYPE_RT5645) अणु
			snd_soc_component_update_bits(component, RT5645_DEPOP_M3,
				RT5645_CP_FQ1_MASK | RT5645_CP_FQ2_MASK |
				RT5645_CP_FQ3_MASK,
				(RT5645_CP_FQ_96_KHZ << RT5645_CP_FQ1_SFT) |
				(RT5645_CP_FQ_12_KHZ << RT5645_CP_FQ2_SFT) |
				(RT5645_CP_FQ_96_KHZ << RT5645_CP_FQ3_SFT));
			regmap_ग_लिखो(rt5645->regmap, RT5645_PR_BASE +
				RT5645_MAMP_INT_REG2, 0xfc00);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_HP_SG_MASK, RT5645_HP_SG_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTP_MASK, RT5645_RSTP_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTP_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_RSTP_DIS |
				RT5645_HP_L_SMT_EN | RT5645_HP_R_SMT_EN);
			msleep(30);
		पूर्ण
		hp_amp_घातer(component, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_spk_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		rt5645_enable_hweq(component);
		snd_soc_component_update_bits(component, RT5645_PWR_DIG1,
			RT5645_PWR_CLS_D | RT5645_PWR_CLS_D_R |
			RT5645_PWR_CLS_D_L,
			RT5645_PWR_CLS_D | RT5645_PWR_CLS_D_R |
			RT5645_PWR_CLS_D_L);
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL3,
			RT5645_DET_CLK_MASK, RT5645_DET_CLK_MODE1);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL3,
			RT5645_DET_CLK_MASK, RT5645_DET_CLK_DIS);
		snd_soc_component_ग_लिखो(component, RT5645_EQ_CTRL2, 0);
		snd_soc_component_update_bits(component, RT5645_PWR_DIG1,
			RT5645_PWR_CLS_D | RT5645_PWR_CLS_D_R |
			RT5645_PWR_CLS_D_L, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_lout_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		hp_amp_घातer(component, 1);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_LM, RT5645_PWR_LM);
		snd_soc_component_update_bits(component, RT5645_LOUT1,
			RT5645_L_MUTE | RT5645_R_MUTE, 0);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5645_LOUT1,
			RT5645_L_MUTE | RT5645_R_MUTE,
			RT5645_L_MUTE | RT5645_R_MUTE);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_LM, 0);
		hp_amp_घातer(component, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_bst2_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG2,
			RT5645_PWR_BST2_P, RT5645_PWR_BST2_P);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG2,
			RT5645_PWR_BST2_P, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_micbias1_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS1_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS1_POW_CTRL_SEL_M);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS1_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS1_POW_CTRL_SEL_A);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_micbias2_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS2_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS2_POW_CTRL_SEL_M);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS2_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS2_POW_CTRL_SEL_A);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5645_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT5645_PWR_MIXER,
		RT5645_PWR_LDO2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT5645_PWR_ANLG2,
		RT5645_PWR_PLL_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("JD Power", RT5645_PWR_ANLG2,
		RT5645_PWR_JD1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Det Power", RT5645_PWR_VOL,
		RT5645_PWR_MIC_DET_BIT, 0, शून्य, 0),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5645_ASRC_1,
			      11, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5645_ASRC_1,
			      12, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO ASRC", 1, RT5645_ASRC_1,
			      10, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO L ASRC", 1, RT5645_ASRC_1,
			      9, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO R ASRC", 1, RT5645_ASRC_1,
			      8, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO1 ASRC", 1, RT5645_ASRC_1,
			      7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO L ASRC", 1, RT5645_ASRC_1,
			      5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO R ASRC", 1, RT5645_ASRC_1,
			      4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5645_ASRC_1,
			      3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO L ASRC", 1, RT5645_ASRC_1,
			      1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO R ASRC", 1, RT5645_ASRC_1,
			      0, 0, शून्य, 0),

	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPLY("micbias1", RT5645_PWR_ANLG2,
			RT5645_PWR_MB1_BIT, 0, rt5645_set_micbias1_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("micbias2", RT5645_PWR_ANLG2,
			RT5645_PWR_MB2_BIT, 0, rt5645_set_micbias2_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),
	SND_SOC_DAPM_INPUT("DMIC L2"),
	SND_SOC_DAPM_INPUT("DMIC R2"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	SND_SOC_DAPM_INPUT("Haptic Generator"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5645_DMIC_CTRL1,
		RT5645_DMIC_1_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC2 Power", RT5645_DMIC_CTRL1,
		RT5645_DMIC_2_EN_SFT, 0, शून्य, 0),
	/* Boost */
	SND_SOC_DAPM_PGA("BST1", RT5645_PWR_ANLG2,
		RT5645_PWR_BST1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_E("BST2", RT5645_PWR_ANLG2,
		RT5645_PWR_BST2_BIT, 0, शून्य, 0, rt5645_bst2_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Volume */
	SND_SOC_DAPM_PGA("INL VOL", RT5645_PWR_VOL,
		RT5645_PWR_IN_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR VOL", RT5645_PWR_VOL,
		RT5645_PWR_IN_R_BIT, 0, शून्य, 0),
	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5645_PWR_MIXER, RT5645_PWR_RM_L_BIT,
			0, rt5645_rec_l_mix, ARRAY_SIZE(rt5645_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5645_PWR_MIXER, RT5645_PWR_RM_R_BIT,
			0, rt5645_rec_r_mix, ARRAY_SIZE(rt5645_rec_r_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("ADC L power", RT5645_PWR_DIG1,
		RT5645_PWR_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC R power", RT5645_PWR_DIG1,
		RT5645_PWR_ADC_R_BIT, 0, शून्य, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_sto_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_sto_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_sto_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_sto_adc1_mux),
	SND_SOC_DAPM_MUX("Mono DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_dmic_l_mux),
	SND_SOC_DAPM_MUX("Mono DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_dmic_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_adc_l2_mux),
	SND_SOC_DAPM_MUX("Mono ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_adc_l1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_adc_r1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_mono_adc_r2_mux),
	/* ADC Mixer */

	SND_SOC_DAPM_SUPPLY_S("adc stereo1 filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_E("Sto1 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_sto1_adc_l_mix, ARRAY_SIZE(rt5645_sto1_adc_l_mix),
		शून्य, 0),
	SND_SOC_DAPM_MIXER_E("Sto1 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_sto1_adc_r_mix, ARRAY_SIZE(rt5645_sto1_adc_r_mix),
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("adc mono left filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_E("Mono ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_mono_adc_l_mix, ARRAY_SIZE(rt5645_mono_adc_l_mix),
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("adc mono right filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_E("Mono ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_mono_adc_r_mix, ARRAY_SIZE(rt5645_mono_adc_r_mix),
		शून्य, 0),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Sto2 ADC LR MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("VAD_ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* IF1 2 Mux */
	SND_SOC_DAPM_MUX("IF2 ADC Mux", SND_SOC_NOPM,
		0, 0, &rt5645_अगर2_adc_in_mux),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5645_PWR_DIG1,
		RT5645_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC0", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5645_PWR_DIG1,
		RT5645_PWR_I2S2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("VAD ADC Mux", SND_SOC_NOPM,
		0, 0, &rt5645_vad_adc_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_dac_l_mix, ARRAY_SIZE(rt5645_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_dac_r_mix, ARRAY_SIZE(rt5645_dac_r_mix)),

	/* DAC2 channel Mux */
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0, &rt5645_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0, &rt5645_dac_r2_mux),
	SND_SOC_DAPM_PGA("DAC L2 Volume", RT5645_PWR_DIG1,
		RT5645_PWR_DAC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC R2 Volume", RT5645_PWR_DIG1,
		RT5645_PWR_DAC_R2_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("DAC1 L Mux", SND_SOC_NOPM, 0, 0, &rt5645_dac1l_mux),
	SND_SOC_DAPM_MUX("DAC1 R Mux", SND_SOC_NOPM, 0, 0, &rt5645_dac1r_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY_S("dac stereo1 filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_DAC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("dac mono left filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_DAC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("dac mono right filter", 1, RT5645_PWR_DIG2,
		RT5645_PWR_DAC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_sto_dac_l_mix, ARRAY_SIZE(rt5645_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_sto_dac_r_mix, ARRAY_SIZE(rt5645_sto_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_mono_dac_l_mix, ARRAY_SIZE(rt5645_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_mono_dac_r_mix, ARRAY_SIZE(rt5645_mono_dac_r_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5645_dig_l_mix, ARRAY_SIZE(rt5645_dig_l_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5645_dig_r_mix, ARRAY_SIZE(rt5645_dig_r_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, RT5645_PWR_DIG1, RT5645_PWR_DAC_L1_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC L2", शून्य, RT5645_PWR_DIG1, RT5645_PWR_DAC_L2_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, RT5645_PWR_DIG1, RT5645_PWR_DAC_R1_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC R2", शून्य, RT5645_PWR_DIG1, RT5645_PWR_DAC_R2_BIT,
		0),
	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("SPK MIXL", RT5645_PWR_MIXER, RT5645_PWR_SM_L_BIT,
		0, rt5645_spk_l_mix, ARRAY_SIZE(rt5645_spk_l_mix)),
	SND_SOC_DAPM_MIXER("SPK MIXR", RT5645_PWR_MIXER, RT5645_PWR_SM_R_BIT,
		0, rt5645_spk_r_mix, ARRAY_SIZE(rt5645_spk_r_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5645_PWR_MIXER, RT5645_PWR_OM_L_BIT,
		0, rt5645_out_l_mix, ARRAY_SIZE(rt5645_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5645_PWR_MIXER, RT5645_PWR_OM_R_BIT,
		0, rt5645_out_r_mix, ARRAY_SIZE(rt5645_out_r_mix)),
	/* Ouput Volume */
	SND_SOC_DAPM_SWITCH("SPKVOL L", RT5645_PWR_VOL, RT5645_PWR_SV_L_BIT, 0,
		&spk_l_vol_control),
	SND_SOC_DAPM_SWITCH("SPKVOL R", RT5645_PWR_VOL, RT5645_PWR_SV_R_BIT, 0,
		&spk_r_vol_control),
	SND_SOC_DAPM_MIXER("HPOVOL MIXL", RT5645_PWR_VOL, RT5645_PWR_HV_L_BIT,
		0, rt5645_hpvoll_mix, ARRAY_SIZE(rt5645_hpvoll_mix)),
	SND_SOC_DAPM_MIXER("HPOVOL MIXR", RT5645_PWR_VOL, RT5645_PWR_HV_R_BIT,
		0, rt5645_hpvolr_mix, ARRAY_SIZE(rt5645_hpvolr_mix)),
	SND_SOC_DAPM_SUPPLY("HPOVOL MIXL Power", RT5645_PWR_MIXER,
		RT5645_PWR_HM_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HPOVOL MIXR Power", RT5645_PWR_MIXER,
		RT5645_PWR_HM_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC 2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH("HPOVOL L", SND_SOC_NOPM, 0, 0, &hp_l_vol_control),
	SND_SOC_DAPM_SWITCH("HPOVOL R", SND_SOC_NOPM, 0, 0, &hp_r_vol_control),

	/* HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("SPOL MIX", SND_SOC_NOPM, 0, 0, rt5645_spo_l_mix,
		ARRAY_SIZE(rt5645_spo_l_mix)),
	SND_SOC_DAPM_MIXER("SPOR MIX", SND_SOC_NOPM, 0, 0, rt5645_spo_r_mix,
		ARRAY_SIZE(rt5645_spo_r_mix)),
	SND_SOC_DAPM_MIXER("HPO MIX", SND_SOC_NOPM, 0, 0, rt5645_hpo_mix,
		ARRAY_SIZE(rt5645_hpo_mix)),
	SND_SOC_DAPM_MIXER("LOUT MIX", SND_SOC_NOPM, 0, 0, rt5645_lout_mix,
		ARRAY_SIZE(rt5645_lout_mix)),

	SND_SOC_DAPM_PGA_S("HP amp", 1, SND_SOC_NOPM, 0, 0, rt5645_hp_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT amp", 1, SND_SOC_NOPM, 0, 0, rt5645_lout_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("SPK amp", 2, SND_SOC_NOPM, 0, 0, rt5645_spk_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

	/* PDM */
	SND_SOC_DAPM_SUPPLY("PDM1 Power", RT5645_PWR_DIG2, RT5645_PWR_PDM1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_MUX("PDM1 L Mux", SND_SOC_NOPM, 0, 0, &rt5645_pdm1_l_mux),
	SND_SOC_DAPM_MUX("PDM1 R Mux", SND_SOC_NOPM, 0, 0, &rt5645_pdm1_r_mux),

	SND_SOC_DAPM_SWITCH("PDM1 L", SND_SOC_NOPM, 0, 0, &pdm1_l_vol_control),
	SND_SOC_DAPM_SWITCH("PDM1 R", SND_SOC_NOPM, 0, 0, &pdm1_r_vol_control),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("PDM1L"),
	SND_SOC_DAPM_OUTPUT("PDM1R"),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5645_specअगरic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("RT5645 IF1 DAC1 L Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_अगर1_dac0_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 DAC1 R Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_अगर1_dac1_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 DAC2 L Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_अगर1_dac2_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 DAC2 R Mux", SND_SOC_NOPM, 0, 0,
		&rt5645_अगर1_dac3_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 ADC Mux", SND_SOC_NOPM,
		0, 0, &rt5645_अगर1_adc_in_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 ADC1 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5645_अगर1_adc1_in_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 ADC2 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5645_अगर1_adc2_in_mux),
	SND_SOC_DAPM_MUX("RT5645 IF1 ADC3 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5645_अगर1_adc3_in_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5650_specअगरic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("A DAC1 L Mux", SND_SOC_NOPM,
		0, 0, &rt5650_a_dac1_l_mux),
	SND_SOC_DAPM_MUX("A DAC1 R Mux", SND_SOC_NOPM,
		0, 0, &rt5650_a_dac1_r_mux),
	SND_SOC_DAPM_MUX("A DAC2 L Mux", SND_SOC_NOPM,
		0, 0, &rt5650_a_dac2_l_mux),
	SND_SOC_DAPM_MUX("A DAC2 R Mux", SND_SOC_NOPM,
		0, 0, &rt5650_a_dac2_r_mux),

	SND_SOC_DAPM_MUX("RT5650 IF1 ADC1 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5650_अगर1_adc1_in_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 ADC2 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5650_अगर1_adc2_in_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 ADC3 Swap Mux", SND_SOC_NOPM,
		0, 0, &rt5650_अगर1_adc3_in_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 ADC Mux", SND_SOC_NOPM,
		0, 0, &rt5650_अगर1_adc_in_mux),

	SND_SOC_DAPM_MUX("RT5650 IF1 DAC1 L Mux", SND_SOC_NOPM, 0, 0,
		&rt5650_अगर1_dac0_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 DAC1 R Mux", SND_SOC_NOPM, 0, 0,
		&rt5650_अगर1_dac1_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 DAC2 L Mux", SND_SOC_NOPM, 0, 0,
		&rt5650_अगर1_dac2_tdm_sel_mux),
	SND_SOC_DAPM_MUX("RT5650 IF1 DAC2 R Mux", SND_SOC_NOPM, 0, 0,
		&rt5650_अगर1_dac3_tdm_sel_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5645_dapm_routes[] = अणु
	अणु "adc stereo1 filter", शून्य, "ADC STO1 ASRC", is_using_asrc पूर्ण,
	अणु "adc mono left filter", शून्य, "ADC MONO L ASRC", is_using_asrc पूर्ण,
	अणु "adc mono right filter", शून्य, "ADC MONO R ASRC", is_using_asrc पूर्ण,
	अणु "dac mono left filter", शून्य, "DAC MONO L ASRC", is_using_asrc पूर्ण,
	अणु "dac mono right filter", शून्य, "DAC MONO R ASRC", is_using_asrc पूर्ण,
	अणु "dac stereo1 filter", शून्य, "DAC STO ASRC", is_using_asrc पूर्ण,

	अणु "I2S1", शून्य, "I2S1 ASRC" पूर्ण,
	अणु "I2S2", शून्य, "I2S2 ASRC" पूर्ण,

	अणु "IN1P", शून्य, "LDO2" पूर्ण,
	अणु "IN2P", शून्य, "LDO2" पूर्ण,

	अणु "DMIC1", शून्य, "DMIC L1" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC R1" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC L2" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC R2" पूर्ण,

	अणु "BST1", शून्य, "IN1P" पूर्ण,
	अणु "BST1", शून्य, "IN1N" पूर्ण,
	अणु "BST1", शून्य, "JD Power" पूर्ण,
	अणु "BST1", शून्य, "Mic Det Power" पूर्ण,
	अणु "BST2", शून्य, "IN2P" पूर्ण,
	अणु "BST2", शून्य, "IN2N" पूर्ण,

	अणु "INL VOL", शून्य, "IN2P" पूर्ण,
	अणु "INR VOL", शून्य, "IN2N" पूर्ण,

	अणु "RECMIXL", "HPOL Switch", "HPOL" पूर्ण,
	अणु "RECMIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "RECMIXL", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "RECMIXL", "OUT MIXL Switch", "OUT MIXL" पूर्ण,

	अणु "RECMIXR", "HPOR Switch", "HPOR" पूर्ण,
	अणु "RECMIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "RECMIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXR", "BST1 Switch", "BST1" पूर्ण,
	अणु "RECMIXR", "OUT MIXR Switch", "OUT MIXR" पूर्ण,

	अणु "ADC L", शून्य, "RECMIXL" पूर्ण,
	अणु "ADC L", शून्य, "ADC L power" पूर्ण,
	अणु "ADC R", शून्य, "RECMIXR" पूर्ण,
	अणु "ADC R", शून्य, "ADC R power" पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC2 Power"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC2 Power"पूर्ण,

	अणु "Stereo1 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo1 DMIC Mux", शून्य, "DMIC STO1 ASRC" पूर्ण,

	अणु "Mono DMIC L Mux", "DMIC1", "DMIC L1" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC2", "DMIC L2" पूर्ण,
	अणु "Mono DMIC L Mux", शून्य, "DMIC MONO L ASRC" पूर्ण,

	अणु "Mono DMIC R Mux", "DMIC1", "DMIC R1" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC2", "DMIC R2" पूर्ण,
	अणु "Mono DMIC R Mux", शून्य, "DMIC MONO R ASRC" पूर्ण,

	अणु "Stereo1 ADC L2 Mux", "DMIC", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Stereo1 ADC L2 Mux", "DAC MIX", "DAC MIXL" पूर्ण,
	अणु "Stereo1 ADC L1 Mux", "ADC", "ADC L" पूर्ण,
	अणु "Stereo1 ADC L1 Mux", "DAC MIX", "DAC MIXL" पूर्ण,

	अणु "Stereo1 ADC R1 Mux", "ADC", "ADC R" पूर्ण,
	अणु "Stereo1 ADC R1 Mux", "DAC MIX", "DAC MIXR" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DMIC", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DAC MIX", "DAC MIXR" पूर्ण,

	अणु "Mono ADC L2 Mux", "DMIC", "Mono DMIC L Mux" पूर्ण,
	अणु "Mono ADC L2 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "ADC", "ADC L" पूर्ण,

	अणु "Mono ADC R1 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,
	अणु "Mono ADC R1 Mux", "ADC", "ADC R" पूर्ण,
	अणु "Mono ADC R2 Mux", "DMIC", "Mono DMIC R Mux" पूर्ण,
	अणु "Mono ADC R2 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,

	अणु "Sto1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux" पूर्ण,

	अणु "Stereo1 ADC MIXL", शून्य, "Sto1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIXL", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo1 ADC MIXR", शून्य, "Sto1 ADC MIXR" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIXL", "ADC1 Switch", "Mono ADC L1 Mux" पूर्ण,
	अणु "Mono ADC MIXL", "ADC2 Switch", "Mono ADC L2 Mux" पूर्ण,
	अणु "Mono ADC MIXL", शून्य, "adc mono left filter" पूर्ण,
	अणु "adc mono left filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIXR", "ADC1 Switch", "Mono ADC R1 Mux" पूर्ण,
	अणु "Mono ADC MIXR", "ADC2 Switch", "Mono ADC R2 Mux" पूर्ण,
	अणु "Mono ADC MIXR", शून्य, "adc mono right filter" पूर्ण,
	अणु "adc mono right filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "VAD ADC Mux", "Sto1 ADC L", "Stereo1 ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "Mono ADC L", "Mono ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "Mono ADC R", "Mono ADC MIXR" पूर्ण,

	अणु "IF_ADC1", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "IF_ADC1", शून्य, "Stereo1 ADC MIXR" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXL" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXR" पूर्ण,
	अणु "VAD_ADC", शून्य, "VAD ADC Mux" पूर्ण,

	अणु "IF2 ADC Mux", "IF_ADC1", "IF_ADC1" पूर्ण,
	अणु "IF2 ADC Mux", "IF_ADC2", "IF_ADC2" पूर्ण,
	अणु "IF2 ADC Mux", "VAD_ADC", "VAD_ADC" पूर्ण,

	अणु "IF1 ADC", शून्य, "I2S1" पूर्ण,
	अणु "IF2 ADC", शून्य, "I2S2" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC Mux" पूर्ण,

	अणु "AIF2TX", शून्य, "IF2 ADC" पूर्ण,

	अणु "IF1 DAC0", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC1", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC2", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC3", शून्य, "AIF1RX" पूर्ण,
	अणु "IF2 DAC", शून्य, "AIF2RX" पूर्ण,

	अणु "IF1 DAC0", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC1", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC2", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC3", शून्य, "I2S1" पूर्ण,
	अणु "IF2 DAC", शून्य, "I2S2" पूर्ण,

	अणु "IF2 DAC L", शून्य, "IF2 DAC" पूर्ण,
	अणु "IF2 DAC R", शून्य, "IF2 DAC" पूर्ण,

	अणु "DAC1 L Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,
	अणु "DAC1 R Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,

	अणु "DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL" पूर्ण,
	अणु "DAC1 MIXL", "DAC1 Switch", "DAC1 L Mux" पूर्ण,
	अणु "DAC1 MIXL", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR" पूर्ण,
	अणु "DAC1 MIXR", "DAC1 Switch", "DAC1 R Mux" पूर्ण,
	अणु "DAC1 MIXR", शून्य, "dac stereo1 filter" पूर्ण,

	अणु "DAC L2 Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,
	अणु "DAC L2 Mux", "Mono ADC", "Mono ADC MIXL" पूर्ण,
	अणु "DAC L2 Mux", "VAD_ADC", "VAD_ADC" पूर्ण,
	अणु "DAC L2 Volume", शून्य, "DAC L2 Mux" पूर्ण,
	अणु "DAC L2 Volume", शून्य, "dac mono left filter" पूर्ण,

	अणु "DAC R2 Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,
	अणु "DAC R2 Mux", "Mono ADC", "Mono ADC MIXR" पूर्ण,
	अणु "DAC R2 Mux", "Haptic", "Haptic Generator" पूर्ण,
	अणु "DAC R2 Volume", शून्य, "DAC R2 Mux" पूर्ण,
	अणु "DAC R2 Volume", शून्य, "dac mono right filter" पूर्ण,

	अणु "Stereo DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Stereo DAC MIXL", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Stereo DAC MIXR", शून्य, "dac stereo1 filter" पूर्ण,

	अणु "Mono DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Mono DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Mono DAC MIXL", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Mono DAC MIXL", शून्य, "dac mono left filter" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Mono DAC MIXR", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Mono DAC MIXR", शून्य, "dac mono right filter" पूर्ण,

	अणु "DAC MIXL", "Sto DAC Mix L Switch", "Stereo DAC MIXL" पूर्ण,
	अणु "DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "DAC MIXL", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "DAC MIXR", "Sto DAC Mix R Switch", "Stereo DAC MIXR" पूर्ण,
	अणु "DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "DAC MIXR", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,

	अणु "DAC L1", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DAC R1", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DAC L2", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DAC R2", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "SPK MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "SPK MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "SPK MIXL", "DAC L1 Switch", "DAC L1" पूर्ण,
	अणु "SPK MIXL", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "SPK MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "SPK MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "SPK MIXR", "DAC R1 Switch", "DAC R1" पूर्ण,
	अणु "SPK MIXR", "DAC R2 Switch", "DAC R2" पूर्ण,

	अणु "OUT MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "OUT MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "OUT MIXL", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "OUT MIXL", "DAC L1 Switch", "DAC L1" पूर्ण,

	अणु "OUT MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "OUT MIXR", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "OUT MIXR", "DAC R1 Switch", "DAC R1" पूर्ण,

	अणु "HPOVOL MIXL", "DAC1 Switch", "DAC L1" पूर्ण,
	अणु "HPOVOL MIXL", "DAC2 Switch", "DAC L2" पूर्ण,
	अणु "HPOVOL MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "HPOVOL MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "HPOVOL MIXL", शून्य, "HPOVOL MIXL Power" पूर्ण,
	अणु "HPOVOL MIXR", "DAC1 Switch", "DAC R1" पूर्ण,
	अणु "HPOVOL MIXR", "DAC2 Switch", "DAC R2" पूर्ण,
	अणु "HPOVOL MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "HPOVOL MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "HPOVOL MIXR", शून्य, "HPOVOL MIXR Power" पूर्ण,

	अणु "DAC 2", शून्य, "DAC L2" पूर्ण,
	अणु "DAC 2", शून्य, "DAC R2" पूर्ण,
	अणु "DAC 1", शून्य, "DAC L1" पूर्ण,
	अणु "DAC 1", शून्य, "DAC R1" पूर्ण,
	अणु "HPOVOL L", "Switch", "HPOVOL MIXL" पूर्ण,
	अणु "HPOVOL R", "Switch", "HPOVOL MIXR" पूर्ण,
	अणु "HPOVOL", शून्य, "HPOVOL L" पूर्ण,
	अणु "HPOVOL", शून्य, "HPOVOL R" पूर्ण,
	अणु "HPO MIX", "DAC1 Switch", "DAC 1" पूर्ण,
	अणु "HPO MIX", "HPVOL Switch", "HPOVOL" पूर्ण,

	अणु "SPKVOL L", "Switch", "SPK MIXL" पूर्ण,
	अणु "SPKVOL R", "Switch", "SPK MIXR" पूर्ण,

	अणु "SPOL MIX", "DAC L1 Switch", "DAC L1" पूर्ण,
	अणु "SPOL MIX", "SPKVOL L Switch", "SPKVOL L" पूर्ण,
	अणु "SPOR MIX", "DAC R1 Switch", "DAC R1" पूर्ण,
	अणु "SPOR MIX", "SPKVOL R Switch", "SPKVOL R" पूर्ण,

	अणु "LOUT MIX", "DAC L1 Switch", "DAC L1" पूर्ण,
	अणु "LOUT MIX", "DAC R1 Switch", "DAC R1" पूर्ण,
	अणु "LOUT MIX", "OUTMIX L Switch", "OUT MIXL" पूर्ण,
	अणु "LOUT MIX", "OUTMIX R Switch", "OUT MIXR" पूर्ण,

	अणु "PDM1 L Mux", "Stereo DAC", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", "Mono DAC", "Mono DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", शून्य, "PDM1 Power" पूर्ण,
	अणु "PDM1 R Mux", "Stereo DAC", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", "Mono DAC", "Mono DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", शून्य, "PDM1 Power" पूर्ण,

	अणु "HP amp", शून्य, "HPO MIX" पूर्ण,
	अणु "HP amp", शून्य, "JD Power" पूर्ण,
	अणु "HP amp", शून्य, "Mic Det Power" पूर्ण,
	अणु "HP amp", शून्य, "LDO2" पूर्ण,
	अणु "HPOL", शून्य, "HP amp" पूर्ण,
	अणु "HPOR", शून्य, "HP amp" पूर्ण,

	अणु "LOUT amp", शून्य, "LOUT MIX" पूर्ण,
	अणु "LOUTL", शून्य, "LOUT amp" पूर्ण,
	अणु "LOUTR", शून्य, "LOUT amp" पूर्ण,

	अणु "PDM1 L", "Switch", "PDM1 L Mux" पूर्ण,
	अणु "PDM1 R", "Switch", "PDM1 R Mux" पूर्ण,

	अणु "PDM1L", शून्य, "PDM1 L" पूर्ण,
	अणु "PDM1R", शून्य, "PDM1 R" पूर्ण,

	अणु "SPK amp", शून्य, "SPOL MIX" पूर्ण,
	अणु "SPK amp", शून्य, "SPOR MIX" पूर्ण,
	अणु "SPOL", शून्य, "SPK amp" पूर्ण,
	अणु "SPOR", शून्य, "SPK amp" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5650_specअगरic_dapm_routes[] = अणु
	अणु "A DAC1 L Mux", "DAC1",  "DAC1 MIXL"पूर्ण,
	अणु "A DAC1 L Mux", "Stereo DAC Mixer", "Stereo DAC MIXL"पूर्ण,
	अणु "A DAC1 R Mux", "DAC1",  "DAC1 MIXR"पूर्ण,
	अणु "A DAC1 R Mux", "Stereo DAC Mixer", "Stereo DAC MIXR"पूर्ण,

	अणु "A DAC2 L Mux", "Stereo DAC Mixer", "Stereo DAC MIXL"पूर्ण,
	अणु "A DAC2 L Mux", "Mono DAC Mixer", "Mono DAC MIXL"पूर्ण,
	अणु "A DAC2 R Mux", "Stereo DAC Mixer", "Stereo DAC MIXR"पूर्ण,
	अणु "A DAC2 R Mux", "Mono DAC Mixer", "Mono DAC MIXR"पूर्ण,

	अणु "DAC L1", शून्य, "A DAC1 L Mux" पूर्ण,
	अणु "DAC R1", शून्य, "A DAC1 R Mux" पूर्ण,
	अणु "DAC L2", शून्य, "A DAC2 L Mux" पूर्ण,
	अणु "DAC R2", शून्य, "A DAC2 R Mux" पूर्ण,

	अणु "RT5650 IF1 ADC1 Swap Mux", "L/R", "IF_ADC1" पूर्ण,
	अणु "RT5650 IF1 ADC1 Swap Mux", "R/L", "IF_ADC1" पूर्ण,
	अणु "RT5650 IF1 ADC1 Swap Mux", "L/L", "IF_ADC1" पूर्ण,
	अणु "RT5650 IF1 ADC1 Swap Mux", "R/R", "IF_ADC1" पूर्ण,

	अणु "RT5650 IF1 ADC2 Swap Mux", "L/R", "IF_ADC2" पूर्ण,
	अणु "RT5650 IF1 ADC2 Swap Mux", "R/L", "IF_ADC2" पूर्ण,
	अणु "RT5650 IF1 ADC2 Swap Mux", "L/L", "IF_ADC2" पूर्ण,
	अणु "RT5650 IF1 ADC2 Swap Mux", "R/R", "IF_ADC2" पूर्ण,

	अणु "RT5650 IF1 ADC3 Swap Mux", "L/R", "VAD_ADC" पूर्ण,
	अणु "RT5650 IF1 ADC3 Swap Mux", "R/L", "VAD_ADC" पूर्ण,
	अणु "RT5650 IF1 ADC3 Swap Mux", "L/L", "VAD_ADC" पूर्ण,
	अणु "RT5650 IF1 ADC3 Swap Mux", "R/R", "VAD_ADC" पूर्ण,

	अणु "IF1 ADC", शून्य, "RT5650 IF1 ADC1 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "RT5650 IF1 ADC2 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "RT5650 IF1 ADC3 Swap Mux" पूर्ण,

	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/IF_ADC2/DAC_REF/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/IF_ADC2/Null/DAC_REF", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/DAC_REF/IF_ADC2/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/DAC_REF/Null/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/Null/DAC_REF/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC1/Null/IF_ADC2/DAC_REF", "IF1 ADC" पूर्ण,

	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/IF_ADC1/DAC_REF/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/IF_ADC1/Null/DAC_REF", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/DAC_REF/IF_ADC1/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/DAC_REF/Null/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/Null/DAC_REF/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "IF_ADC2/Null/IF_ADC1/DAC_REF", "IF1 ADC" पूर्ण,

	अणु "RT5650 IF1 ADC Mux", "DAC_REF/IF_ADC1/IF_ADC2/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "DAC_REF/IF_ADC1/Null/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "DAC_REF/IF_ADC2/IF_ADC1/Null", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "DAC_REF/IF_ADC2/Null/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "DAC_REF/Null/IF_ADC1/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "DAC_REF/Null/IF_ADC2/IF_ADC1", "IF1 ADC" पूर्ण,

	अणु "RT5650 IF1 ADC Mux", "Null/IF_ADC1/IF_ADC2/DAC_REF", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "Null/IF_ADC1/DAC_REF/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "Null/IF_ADC2/IF_ADC1/DAC_REF", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "Null/IF_ADC2/DAC_REF/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "Null/DAC_REF/IF_ADC1/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5650 IF1 ADC Mux", "Null/DAC_REF/IF_ADC2/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "AIF1TX", शून्य, "RT5650 IF1 ADC Mux" पूर्ण,

	अणु "RT5650 IF1 DAC1 L Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5650 IF1 DAC1 L Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5650 IF1 DAC1 L Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5650 IF1 DAC1 L Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5650 IF1 DAC1 R Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5650 IF1 DAC1 R Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5650 IF1 DAC1 R Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5650 IF1 DAC1 R Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5650 IF1 DAC2 L Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5650 IF1 DAC2 L Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5650 IF1 DAC2 L Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5650 IF1 DAC2 L Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5650 IF1 DAC2 R Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5650 IF1 DAC2 R Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5650 IF1 DAC2 R Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5650 IF1 DAC2 R Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "DAC1 L Mux", "IF1 DAC", "RT5650 IF1 DAC1 L Mux" पूर्ण,
	अणु "DAC1 R Mux", "IF1 DAC", "RT5650 IF1 DAC1 R Mux" पूर्ण,

	अणु "DAC L2 Mux", "IF1 DAC", "RT5650 IF1 DAC2 L Mux" पूर्ण,
	अणु "DAC R2 Mux", "IF1 DAC", "RT5650 IF1 DAC2 R Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5645_specअगरic_dapm_routes[] = अणु
	अणु "DAC L1", शून्य, "Stereo DAC MIXL" पूर्ण,
	अणु "DAC R1", शून्य, "Stereo DAC MIXR" पूर्ण,
	अणु "DAC L2", शून्य, "Mono DAC MIXL" पूर्ण,
	अणु "DAC R2", शून्य, "Mono DAC MIXR" पूर्ण,

	अणु "RT5645 IF1 ADC1 Swap Mux", "L/R", "IF_ADC1" पूर्ण,
	अणु "RT5645 IF1 ADC1 Swap Mux", "R/L", "IF_ADC1" पूर्ण,
	अणु "RT5645 IF1 ADC1 Swap Mux", "L/L", "IF_ADC1" पूर्ण,
	अणु "RT5645 IF1 ADC1 Swap Mux", "R/R", "IF_ADC1" पूर्ण,

	अणु "RT5645 IF1 ADC2 Swap Mux", "L/R", "IF_ADC2" पूर्ण,
	अणु "RT5645 IF1 ADC2 Swap Mux", "R/L", "IF_ADC2" पूर्ण,
	अणु "RT5645 IF1 ADC2 Swap Mux", "L/L", "IF_ADC2" पूर्ण,
	अणु "RT5645 IF1 ADC2 Swap Mux", "R/R", "IF_ADC2" पूर्ण,

	अणु "RT5645 IF1 ADC3 Swap Mux", "L/R", "VAD_ADC" पूर्ण,
	अणु "RT5645 IF1 ADC3 Swap Mux", "R/L", "VAD_ADC" पूर्ण,
	अणु "RT5645 IF1 ADC3 Swap Mux", "L/L", "VAD_ADC" पूर्ण,
	अणु "RT5645 IF1 ADC3 Swap Mux", "R/R", "VAD_ADC" पूर्ण,

	अणु "IF1 ADC", शून्य, "RT5645 IF1 ADC1 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "RT5645 IF1 ADC2 Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "RT5645 IF1 ADC3 Swap Mux" पूर्ण,

	अणु "RT5645 IF1 ADC Mux", "IF_ADC1/IF_ADC2/VAD_ADC", "IF1 ADC" पूर्ण,
	अणु "RT5645 IF1 ADC Mux", "IF_ADC2/IF_ADC1/VAD_ADC", "IF1 ADC" पूर्ण,
	अणु "RT5645 IF1 ADC Mux", "VAD_ADC/IF_ADC1/IF_ADC2", "IF1 ADC" पूर्ण,
	अणु "RT5645 IF1 ADC Mux", "VAD_ADC/IF_ADC2/IF_ADC1", "IF1 ADC" पूर्ण,
	अणु "AIF1TX", शून्य, "RT5645 IF1 ADC Mux" पूर्ण,

	अणु "RT5645 IF1 DAC1 L Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5645 IF1 DAC1 L Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5645 IF1 DAC1 L Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5645 IF1 DAC1 L Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5645 IF1 DAC1 R Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5645 IF1 DAC1 R Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5645 IF1 DAC1 R Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5645 IF1 DAC1 R Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5645 IF1 DAC2 L Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5645 IF1 DAC2 L Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5645 IF1 DAC2 L Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5645 IF1 DAC2 L Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "RT5645 IF1 DAC2 R Mux", "Slot0", "IF1 DAC0" पूर्ण,
	अणु "RT5645 IF1 DAC2 R Mux", "Slot1", "IF1 DAC1" पूर्ण,
	अणु "RT5645 IF1 DAC2 R Mux", "Slot2", "IF1 DAC2" पूर्ण,
	अणु "RT5645 IF1 DAC2 R Mux", "Slot3", "IF1 DAC3" पूर्ण,

	अणु "DAC1 L Mux", "IF1 DAC", "RT5645 IF1 DAC1 L Mux" पूर्ण,
	अणु "DAC1 R Mux", "IF1 DAC", "RT5645 IF1 DAC1 R Mux" पूर्ण,

	अणु "DAC L2 Mux", "IF1 DAC", "RT5645 IF1 DAC2 L Mux" पूर्ण,
	अणु "DAC R2 Mux", "IF1 DAC", "RT5645 IF1 DAC2 R Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5645_old_dapm_routes[] = अणु
	अणु "SPOL MIX", "DAC R1 Switch", "DAC R1" पूर्ण,
	अणु "SPOL MIX", "SPKVOL R Switch", "SPKVOL R" पूर्ण,
पूर्ण;

अटल पूर्णांक rt5645_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk, dl_sft;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5645->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5645->sysclk, rt5645->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting\n");
		वापस -EINVAL;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	चयन (rt5645->codec_type) अणु
	हाल CODEC_TYPE_RT5650:
		dl_sft = 4;
		अवरोध;
	शेष:
		dl_sft = 2;
		अवरोध;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt5645->bclk[dai->id] = rt5645->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5645->bclk[dai->id], rt5645->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len = 0x1;
		अवरोध;
	हाल 24:
		val_len = 0x2;
		अवरोध;
	हाल 8:
		val_len = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5645_AIF1:
		mask_clk = RT5645_I2S_PD1_MASK;
		val_clk = pre_भाग << RT5645_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5645_I2S1_SDP,
			(0x3 << dl_sft), (val_len << dl_sft));
		snd_soc_component_update_bits(component, RT5645_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	हाल  RT5645_AIF2:
		mask_clk = RT5645_I2S_BCLK_MS2_MASK | RT5645_I2S_PD2_MASK;
		val_clk = bclk_ms << RT5645_I2S_BCLK_MS2_SFT |
			pre_भाग << RT5645_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5645_I2S2_SDP,
			(0x3 << dl_sft), (val_len << dl_sft));
		snd_soc_component_update_bits(component, RT5645_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, pol_sft;

	चयन (rt5645->codec_type) अणु
	हाल CODEC_TYPE_RT5650:
		pol_sft = 8;
		अवरोध;
	शेष:
		pol_sft = 7;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5645->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5645_I2S_MS_S;
		rt5645->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= (1 << pol_sft);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5645_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5645_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5645_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	चयन (dai->id) अणु
	हाल RT5645_AIF1:
		snd_soc_component_update_bits(component, RT5645_I2S1_SDP,
			RT5645_I2S_MS_MASK | (1 << pol_sft) |
			RT5645_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5645_AIF2:
		snd_soc_component_update_bits(component, RT5645_I2S2_SDP,
			RT5645_I2S_MS_MASK | (1 << pol_sft) |
			RT5645_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt5645->sysclk && clk_id == rt5645->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5645_SCLK_S_MCLK:
		reg_val |= RT5645_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5645_SCLK_S_PLL1:
		reg_val |= RT5645_SCLK_SRC_PLL1;
		अवरोध;
	हाल RT5645_SCLK_S_RCCLK:
		reg_val |= RT5645_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5645_GLB_CLK,
		RT5645_SCLK_SRC_MASK, reg_val);
	rt5645->sysclk = freq;
	rt5645->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5645->pll_src && freq_in == rt5645->pll_in &&
	    freq_out == rt5645->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5645->pll_in = 0;
		rt5645->pll_out = 0;
		snd_soc_component_update_bits(component, RT5645_GLB_CLK,
			RT5645_SCLK_SRC_MASK, RT5645_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5645_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5645_GLB_CLK,
			RT5645_PLL1_SRC_MASK, RT5645_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5645_PLL1_S_BCLK1:
	हाल RT5645_PLL1_S_BCLK2:
		चयन (dai->id) अणु
		हाल RT5645_AIF1:
			snd_soc_component_update_bits(component, RT5645_GLB_CLK,
				RT5645_PLL1_SRC_MASK, RT5645_PLL1_SRC_BCLK1);
			अवरोध;
		हाल  RT5645_AIF2:
			snd_soc_component_update_bits(component, RT5645_GLB_CLK,
				RT5645_PLL1_SRC_MASK, RT5645_PLL1_SRC_BCLK2);
			अवरोध;
		शेष:
			dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_ग_लिखो(component, RT5645_PLL_CTRL1,
		pll_code.n_code << RT5645_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5645_PLL_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5645_PLL_M_SFT) |
		(pll_code.m_bp << RT5645_PLL_M_BP_SFT));

	rt5645->pll_in = freq_in;
	rt5645->pll_out = freq_out;
	rt5645->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक i_slot_sft, o_slot_sft, i_width_sht, o_width_sht, en_sft;
	अचिन्हित पूर्णांक mask, val = 0;

	चयन (rt5645->codec_type) अणु
	हाल CODEC_TYPE_RT5650:
		en_sft = 15;
		i_slot_sft = 10;
		o_slot_sft = 8;
		i_width_sht = 6;
		o_width_sht = 4;
		mask = 0x8ff0;
		अवरोध;
	शेष:
		en_sft = 14;
		i_slot_sft = o_slot_sft = 12;
		i_width_sht = o_width_sht = 10;
		mask = 0x7c00;
		अवरोध;
	पूर्ण
	अगर (rx_mask || tx_mask) अणु
		val |= (1 << en_sft);
		अगर (rt5645->codec_type == CODEC_TYPE_RT5645)
			snd_soc_component_update_bits(component, RT5645_BASS_BACK,
				RT5645_G_BB_BST_MASK, RT5645_G_BB_BST_25DB);
	पूर्ण

	चयन (slots) अणु
	हाल 4:
		val |= (1 << i_slot_sft) | (1 << o_slot_sft);
		अवरोध;
	हाल 6:
		val |= (2 << i_slot_sft) | (2 << o_slot_sft);
		अवरोध;
	हाल 8:
		val |= (3 << i_slot_sft) | (3 << o_slot_sft);
		अवरोध;
	हाल 2:
	शेष:
		अवरोध;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= (1 << i_width_sht) | (1 << o_width_sht);
		अवरोध;
	हाल 24:
		val |= (2 << i_width_sht) | (2 << o_width_sht);
		अवरोध;
	हाल 32:
		val |= (3 << i_width_sht) | (3 << o_width_sht);
		अवरोध;
	हाल 16:
	शेष:
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, RT5645_TDM_CTRL_1, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2);
			mdelay(10);
			snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_FV1 | RT5645_PWR_FV2,
				RT5645_PWR_FV1 | RT5645_PWR_FV2);
			snd_soc_component_update_bits(component, RT5645_GEN_CTRL1,
				RT5645_DIG_GATE_CTRL, RT5645_DIG_GATE_CTRL);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_VREF1 | RT5645_PWR_MB |
			RT5645_PWR_BG | RT5645_PWR_VREF2,
			RT5645_PWR_VREF1 | RT5645_PWR_MB |
			RT5645_PWR_BG | RT5645_PWR_VREF2);
		mdelay(10);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_FV1 | RT5645_PWR_FV2,
			RT5645_PWR_FV1 | RT5645_PWR_FV2);
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M2, 0x1140);
			msleep(40);
			अगर (rt5645->en_button_func)
				queue_delayed_work(प्रणाली_घातer_efficient_wq,
					&rt5645->jack_detect_work,
					msecs_to_jअगरfies(0));
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, RT5645_DEPOP_M2, 0x1100);
		अगर (!rt5645->en_button_func)
			snd_soc_component_update_bits(component, RT5645_GEN_CTRL1,
					RT5645_DIG_GATE_CTRL, 0);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2 |
				RT5645_PWR_FV1 | RT5645_PWR_FV2, 0x0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt5645_enable_push_button_irq(काष्ठा snd_soc_component *component,
	bool enable)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (enable) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "ADC L power");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "ADC R power");
		snd_soc_dapm_sync(dapm);

		snd_soc_component_update_bits(component, RT5650_4BTN_IL_CMD1, 0x3, 0x3);
		snd_soc_component_update_bits(component,
					RT5645_INT_IRQ_ST, 0x8, 0x8);
		snd_soc_component_update_bits(component,
					RT5650_4BTN_IL_CMD2, 0x8000, 0x8000);
		snd_soc_component_पढ़ो(component, RT5650_4BTN_IL_CMD1);
		pr_debug("%s read %x = %x\n", __func__, RT5650_4BTN_IL_CMD1,
			snd_soc_component_पढ़ो(component, RT5650_4BTN_IL_CMD1));
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5650_4BTN_IL_CMD2, 0x8000, 0x0);
		snd_soc_component_update_bits(component, RT5645_INT_IRQ_ST, 0x8, 0x0);

		snd_soc_dapm_disable_pin(dapm, "ADC L power");
		snd_soc_dapm_disable_pin(dapm, "ADC R power");
		snd_soc_dapm_sync(dapm);
	पूर्ण
पूर्ण

अटल पूर्णांक rt5645_jack_detect(काष्ठा snd_soc_component *component, पूर्णांक jack_insert)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (jack_insert) अणु
		regmap_ग_लिखो(rt5645->regmap, RT5645_CHARGE_PUMP, 0x0e06);

		/* क्रम jack type detect */
		snd_soc_dapm_क्रमce_enable_pin(dapm, "LDO2");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		अगर (!dapm->card->instantiated) अणु
			/* Power up necessary bits क्रम JD अगर dapm is
			   not पढ़ोy yet */
			regmap_update_bits(rt5645->regmap, RT5645_PWR_ANLG1,
				RT5645_PWR_MB | RT5645_PWR_VREF2,
				RT5645_PWR_MB | RT5645_PWR_VREF2);
			regmap_update_bits(rt5645->regmap, RT5645_PWR_MIXER,
				RT5645_PWR_LDO2, RT5645_PWR_LDO2);
			regmap_update_bits(rt5645->regmap, RT5645_PWR_VOL,
				RT5645_PWR_MIC_DET, RT5645_PWR_MIC_DET);
		पूर्ण

		regmap_ग_लिखो(rt5645->regmap, RT5645_JD_CTRL3, 0x00f0);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, RT5645_CBJ_MN_JD);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1,
			RT5645_CBJ_BST1_EN, RT5645_CBJ_BST1_EN);
		msleep(100);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, 0);

		msleep(600);
		regmap_पढ़ो(rt5645->regmap, RT5645_IN1_CTRL3, &val);
		val &= 0x7;
		dev_dbg(component->dev, "val = %d\n", val);

		अगर ((val == 1 || val == 2) && !rt5645->pdata.no_headset_mic) अणु
			rt5645->jack_type = SND_JACK_HEADSET;
			अगर (rt5645->en_button_func) अणु
				rt5645_enable_push_button_irq(component, true);
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
			snd_soc_dapm_sync(dapm);
			rt5645->jack_type = SND_JACK_HEADPHONE;
		पूर्ण
		अगर (rt5645->pdata.level_trigger_irq)
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_NOR);
	पूर्ण अन्यथा अणु /* jack out */
		rt5645->jack_type = 0;

		regmap_update_bits(rt5645->regmap, RT5645_HP_VOL,
			RT5645_L_MUTE | RT5645_R_MUTE,
			RT5645_L_MUTE | RT5645_R_MUTE);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, RT5645_CBJ_MN_JD);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1,
			RT5645_CBJ_BST1_EN, 0);

		अगर (rt5645->en_button_func)
			rt5645_enable_push_button_irq(component, false);

		अगर (rt5645->pdata.jd_mode == 0)
			snd_soc_dapm_disable_pin(dapm, "LDO2");
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		अगर (rt5645->pdata.level_trigger_irq)
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
	पूर्ण

	वापस rt5645->jack_type;
पूर्ण

अटल पूर्णांक rt5645_button_detect(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक btn_type, val;

	val = snd_soc_component_पढ़ो(component, RT5650_4BTN_IL_CMD1);
	pr_debug("val=0x%x\n", val);
	btn_type = val & 0xfff0;
	snd_soc_component_ग_लिखो(component, RT5650_4BTN_IL_CMD1, val);

	वापस btn_type;
पूर्ण

अटल irqवापस_t rt5645_irq(पूर्णांक irq, व्योम *data);

पूर्णांक rt5645_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hp_jack, काष्ठा snd_soc_jack *mic_jack,
	काष्ठा snd_soc_jack *btn_jack)
अणु
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	rt5645->hp_jack = hp_jack;
	rt5645->mic_jack = mic_jack;
	rt5645->btn_jack = btn_jack;
	अगर (rt5645->btn_jack && rt5645->codec_type == CODEC_TYPE_RT5650) अणु
		rt5645->en_button_func = true;
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
				RT5645_GP1_PIN_IRQ, RT5645_GP1_PIN_IRQ);
		regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL1,
				RT5645_DIG_GATE_CTRL, RT5645_DIG_GATE_CTRL);
	पूर्ण
	rt5645_irq(0, rt5645);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5645_set_jack_detect);

अटल व्योम rt5645_jack_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5645_priv *rt5645 =
		container_of(work, काष्ठा rt5645_priv, jack_detect_work.work);
	पूर्णांक val, btn_type, gpio_state = 0, report = 0;

	अगर (!rt5645->component)
		वापस;

	चयन (rt5645->pdata.jd_mode) अणु
	हाल 0: /* Not using rt5645 JD */
		अगर (rt5645->gpiod_hp_det) अणु
			gpio_state = gpiod_get_value(rt5645->gpiod_hp_det);
			अगर (rt5645->pdata.inv_hp_pol)
				gpio_state ^= 1;
			dev_dbg(rt5645->component->dev, "gpio_state = %d\n",
				gpio_state);
			report = rt5645_jack_detect(rt5645->component, gpio_state);
		पूर्ण
		snd_soc_jack_report(rt5645->hp_jack,
				    report, SND_JACK_HEADPHONE);
		snd_soc_jack_report(rt5645->mic_jack,
				    report, SND_JACK_MICROPHONE);
		वापस;
	हाल 4:
		val = snd_soc_component_पढ़ो(rt5645->component, RT5645_A_JD_CTRL1) & 0x0020;
		अवरोध;
	शेष: /* पढ़ो rt5645 jd1_1 status */
		val = snd_soc_component_पढ़ो(rt5645->component, RT5645_INT_IRQ_ST) & 0x1000;
		अवरोध;

	पूर्ण

	अगर (!val && (rt5645->jack_type == 0)) अणु /* jack in */
		report = rt5645_jack_detect(rt5645->component, 1);
	पूर्ण अन्यथा अगर (!val && rt5645->jack_type != 0) अणु
		/* क्रम push button and jack out */
		btn_type = 0;
		अगर (snd_soc_component_पढ़ो(rt5645->component, RT5645_INT_IRQ_ST) & 0x4) अणु
			/* button pressed */
			report = SND_JACK_HEADSET;
			btn_type = rt5645_button_detect(rt5645->component);
			/* rt5650 can report three kinds of button behavior,
			   one click, द्विगुन click and hold. However,
			   currently we will report button pressed/released
			   event. So all the three button behaviors are
			   treated as button pressed. */
			चयन (btn_type) अणु
			हाल 0x8000:
			हाल 0x4000:
			हाल 0x2000:
				report |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x1000:
			हाल 0x0800:
			हाल 0x0400:
				report |= SND_JACK_BTN_1;
				अवरोध;
			हाल 0x0200:
			हाल 0x0100:
			हाल 0x0080:
				report |= SND_JACK_BTN_2;
				अवरोध;
			हाल 0x0040:
			हाल 0x0020:
			हाल 0x0010:
				report |= SND_JACK_BTN_3;
				अवरोध;
			हाल 0x0000: /* unpressed */
				अवरोध;
			शेष:
				dev_err(rt5645->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (btn_type == 0)/* button release */
			report =  rt5645->jack_type;
		अन्यथा अणु
			mod_समयr(&rt5645->btn_check_समयr,
				msecs_to_jअगरfies(100));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* jack out */
		report = 0;
		snd_soc_component_update_bits(rt5645->component,
				    RT5645_INT_IRQ_ST, 0x1, 0x0);
		rt5645_jack_detect(rt5645->component, 0);
	पूर्ण

	snd_soc_jack_report(rt5645->hp_jack, report, SND_JACK_HEADPHONE);
	snd_soc_jack_report(rt5645->mic_jack, report, SND_JACK_MICROPHONE);
	अगर (rt5645->en_button_func)
		snd_soc_jack_report(rt5645->btn_jack,
			report, SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3);
पूर्ण

अटल व्योम rt5645_rcघड़ी_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5645_priv *rt5645 =
		container_of(work, काष्ठा rt5645_priv, rcघड़ी_work.work);

	regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
		RT5645_PWR_CLK25M_MASK, RT5645_PWR_CLK25M_PD);
पूर्ण

अटल irqवापस_t rt5645_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5645_priv *rt5645 = data;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &rt5645->jack_detect_work, msecs_to_jअगरfies(250));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rt5645_btn_check_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा rt5645_priv *rt5645 = from_समयr(rt5645, t, btn_check_समयr);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
		   &rt5645->jack_detect_work, msecs_to_jअगरfies(5));
पूर्ण

अटल पूर्णांक rt5645_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	rt5645->component = component;

	चयन (rt5645->codec_type) अणु
	हाल CODEC_TYPE_RT5645:
		ret = snd_soc_dapm_new_controls(dapm,
			rt5645_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5645_specअगरic_dapm_widमाला_लो));
		अगर (ret < 0)
			जाओ निकास;

		ret = snd_soc_dapm_add_routes(dapm,
			rt5645_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5645_specअगरic_dapm_routes));
		अगर (ret < 0)
			जाओ निकास;

		अगर (rt5645->v_id < 3) अणु
			ret = snd_soc_dapm_add_routes(dapm,
				rt5645_old_dapm_routes,
				ARRAY_SIZE(rt5645_old_dapm_routes));
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
		अवरोध;
	हाल CODEC_TYPE_RT5650:
		ret = snd_soc_dapm_new_controls(dapm,
			rt5650_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5650_specअगरic_dapm_widमाला_लो));
		अगर (ret < 0)
			जाओ निकास;

		ret = snd_soc_dapm_add_routes(dapm,
			rt5650_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5650_specअगरic_dapm_routes));
		अगर (ret < 0)
			जाओ निकास;
		अवरोध;
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	/* क्रम JD function */
	अगर (rt5645->pdata.jd_mode) अणु
		ret = snd_soc_dapm_क्रमce_enable_pin(dapm, "JD Power");
		अगर (ret < 0)
			जाओ निकास;

		ret = snd_soc_dapm_क्रमce_enable_pin(dapm, "LDO2");
		अगर (ret < 0)
			जाओ निकास;

		ret = snd_soc_dapm_sync(dapm);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	अगर (rt5645->pdata.दीर्घ_name)
		component->card->दीर्घ_name = rt5645->pdata.दीर्घ_name;

	rt5645->eq_param = devm_kसुस्मृति(component->dev,
		RT5645_HWEQ_NUM, माप(काष्ठा rt5645_eq_param_s),
		GFP_KERNEL);

	अगर (!rt5645->eq_param)
		ret = -ENOMEM;
निकास:
	/*
	 * If there was an error above, everything will be cleaned up by the
	 * caller अगर we वापस an error here.  This will be करोne with a later
	 * call to rt5645_हटाओ().
	 */
	वापस ret;
पूर्ण

अटल व्योम rt5645_हटाओ(काष्ठा snd_soc_component *component)
अणु
	rt5645_reset(component);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5645_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5645->regmap, true);
	regcache_mark_dirty(rt5645->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5645->regmap, false);
	regcache_sync(rt5645->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5645_suspend शून्य
#घोषणा rt5645_resume शून्य
#पूर्ण_अगर

#घोषणा RT5645_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5645_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5645_aअगर_dai_ops = अणु
	.hw_params = rt5645_hw_params,
	.set_fmt = rt5645_set_dai_fmt,
	.set_sysclk = rt5645_set_dai_sysclk,
	.set_tdm_slot = rt5645_set_tdm_slot,
	.set_pll = rt5645_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5645_dai[] = अणु
	अणु
		.name = "rt5645-aif1",
		.id = RT5645_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5645_STEREO_RATES,
			.क्रमmats = RT5645_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = RT5645_STEREO_RATES,
			.क्रमmats = RT5645_FORMATS,
		पूर्ण,
		.ops = &rt5645_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5645-aif2",
		.id = RT5645_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5645_STEREO_RATES,
			.क्रमmats = RT5645_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5645_STEREO_RATES,
			.क्रमmats = RT5645_FORMATS,
		पूर्ण,
		.ops = &rt5645_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5645 = अणु
	.probe			= rt5645_probe,
	.हटाओ			= rt5645_हटाओ,
	.suspend		= rt5645_suspend,
	.resume			= rt5645_resume,
	.set_bias_level		= rt5645_set_bias_level,
	.controls		= rt5645_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5645_snd_controls),
	.dapm_widमाला_लो		= rt5645_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5645_dapm_widमाला_लो),
	.dapm_routes		= rt5645_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5645_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5645_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT5645_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5645_ranges) *
					       RT5645_PR_SPACING),
	.अस्थिर_reg = rt5645_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5645_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5645_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5645_reg),
	.ranges = rt5645_ranges,
	.num_ranges = ARRAY_SIZE(rt5645_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5650_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT5645_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5645_ranges) *
					       RT5645_PR_SPACING),
	.अस्थिर_reg = rt5645_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5645_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5650_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5650_reg),
	.ranges = rt5645_ranges,
	.num_ranges = ARRAY_SIZE(rt5645_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config temp_regmap = अणु
	.name="nocache",
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT5645_VENDOR_ID2 + 1,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5645_i2c_id[] = अणु
	अणु "rt5645", 0 पूर्ण,
	अणु "rt5650", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5645_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt5645_of_match[] = अणु
	अणु .compatible = "realtek,rt5645", पूर्ण,
	अणु .compatible = "realtek,rt5650", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5645_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5645_acpi_match[] = अणु
	अणु "10EC5645", 0 पूर्ण,
	अणु "10EC5648", 0 पूर्ण,
	अणु "10EC5650", 0 पूर्ण,
	अणु "10EC5640", 0 पूर्ण,
	अणु "10EC3270", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5645_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा rt5645_platक्रमm_data पूर्णांकel_braswell_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC1_DISABLE,
	.dmic2_data_pin = RT5645_DMIC_DATA_IN2P,
	.jd_mode = 3,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data buddy_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC_DATA_GPIO5,
	.dmic2_data_pin = RT5645_DMIC_DATA_IN2P,
	.jd_mode = 4,
	.level_trigger_irq = true,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data gpd_win_platक्रमm_data = अणु
	.jd_mode = 3,
	.inv_jd1_1 = true,
	.दीर्घ_name = "gpd-win-pocket-rt5645",
	/* The GPD pocket has a dअगरf. mic, क्रम the win this करोes not matter. */
	.in2_dअगरf = true,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data asus_t100ha_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC_DATA_IN2N,
	.dmic2_data_pin = RT5645_DMIC2_DISABLE,
	.jd_mode = 3,
	.inv_jd1_1 = true,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data asus_t101ha_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC_DATA_IN2N,
	.dmic2_data_pin = RT5645_DMIC2_DISABLE,
	.jd_mode = 3,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data lenovo_ideapad_miix_310_pdata = अणु
	.jd_mode = 3,
	.in2_dअगरf = true,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data jd_mode3_platक्रमm_data = अणु
	.jd_mode = 3,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data lattepanda_board_platक्रमm_data = अणु
	.jd_mode = 2,
	.inv_jd1_1 = true
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data kahlee_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC_DATA_GPIO5,
	.dmic2_data_pin = RT5645_DMIC_DATA_IN2P,
	.jd_mode = 3,
पूर्ण;

अटल स्थिर काष्ठा rt5645_platक्रमm_data ecs_ef20_platक्रमm_data = अणु
	.dmic1_data_pin = RT5645_DMIC1_DISABLE,
	.dmic2_data_pin = RT5645_DMIC_DATA_IN2P,
	.inv_hp_pol = 1,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params ef20_hp_detect = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping cht_rt5645_ef20_gpios[] = अणु
	अणु "hp-detect-gpios", &ef20_hp_detect, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक cht_rt5645_ef20_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	cht_rt5645_gpios = cht_rt5645_ef20_gpios;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_platक्रमm_data[] = अणु
	अणु
		.ident = "Chrome Buddy",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Buddy"),
		पूर्ण,
		.driver_data = (व्योम *)&buddy_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Intel Strago",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Strago"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Google Chrome",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Google Setzer",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Setzer"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Microsoft Surface 3",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Surface 3"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		/*
		 * Match क्रम the GPDwin which unक्रमtunately uses somewhat
		 * generic dmi strings, which is why we test क्रम 4 strings.
		 * Comparing against 23 other byt/cht boards, board_venकरोr
		 * and board_name are unique to the GPDwin, where as only one
		 * other board has the same board_serial and 3 others have
		 * the same शेष product_name. Also the GPDwin is the
		 * only device to have both board_ and product_name not set.
		 */
		.ident = "GPD Win / Pocket",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Default string"),
			DMI_MATCH(DMI_BOARD_SERIAL, "Default string"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_win_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "ASUS T100HAN",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "T100HAN"),
		पूर्ण,
		.driver_data = (व्योम *)&asus_t100ha_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "ASUS T101HA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "T101HA"),
		पूर्ण,
		.driver_data = (व्योम *)&asus_t101ha_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "MINIX Z83-4",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "MINIX"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Z83-4"),
		पूर्ण,
		.driver_data = (व्योम *)&jd_mode3_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Teclast X80 Pro",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X80 Pro"),
		पूर्ण,
		.driver_data = (व्योम *)&jd_mode3_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Lenovo Ideapad Miix 310",
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "80SG"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "MIIX 310-10ICR"),
		पूर्ण,
		.driver_data = (व्योम *)&lenovo_ideapad_miix_310_pdata,
	पूर्ण,
	अणु
		.ident = "Lenovo Ideapad Miix 320",
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "80XF"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 320-10ICR"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "LattePanda board",
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		  DMI_EXACT_MATCH(DMI_BOARD_VERSION, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&lattepanda_board_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Chrome Kahlee",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Kahlee"),
		पूर्ण,
		.driver_data = (व्योम *)&kahlee_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "Medion E1239T",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "E1239T MD60568"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_braswell_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "EF20",
		.callback = cht_rt5645_ef20_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20"),
		पूर्ण,
		.driver_data = (व्योम *)&ecs_ef20_platक्रमm_data,
	पूर्ण,
	अणु
		.ident = "EF20EA",
		.callback = cht_rt5645_ef20_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20EA"),
		पूर्ण,
		.driver_data = (व्योम *)&ecs_ef20_platक्रमm_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल bool rt5645_check_dp(काष्ठा device *dev)
अणु
	अगर (device_property_present(dev, "realtek,in2-differential") ||
	    device_property_present(dev, "realtek,dmic1-data-pin") ||
	    device_property_present(dev, "realtek,dmic2-data-pin") ||
	    device_property_present(dev, "realtek,jd-mode"))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक rt5645_parse_dt(काष्ठा rt5645_priv *rt5645, काष्ठा device *dev)
अणु
	rt5645->pdata.in2_dअगरf = device_property_पढ़ो_bool(dev,
		"realtek,in2-differential");
	device_property_पढ़ो_u32(dev,
		"realtek,dmic1-data-pin", &rt5645->pdata.dmic1_data_pin);
	device_property_पढ़ो_u32(dev,
		"realtek,dmic2-data-pin", &rt5645->pdata.dmic2_data_pin);
	device_property_पढ़ो_u32(dev,
		"realtek,jd-mode", &rt5645->pdata.jd_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5645_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5645_platक्रमm_data *pdata = शून्य;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_data;
	काष्ठा rt5645_priv *rt5645;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val;
	काष्ठा regmap *regmap;

	rt5645 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5645_priv),
				GFP_KERNEL);
	अगर (rt5645 == शून्य)
		वापस -ENOMEM;

	rt5645->i2c = i2c;
	i2c_set_clientdata(i2c, rt5645);

	dmi_data = dmi_first_match(dmi_platक्रमm_data);
	अगर (dmi_data) अणु
		dev_info(&i2c->dev, "Detected %s platform\n", dmi_data->ident);
		pdata = dmi_data->driver_data;
	पूर्ण

	अगर (pdata)
		rt5645->pdata = *pdata;
	अन्यथा अगर (rt5645_check_dp(&i2c->dev))
		rt5645_parse_dt(rt5645, &i2c->dev);
	अन्यथा
		rt5645->pdata = jd_mode3_platक्रमm_data;

	अगर (quirk != -1) अणु
		rt5645->pdata.in2_dअगरf = QUIRK_IN2_DIFF(quirk);
		rt5645->pdata.level_trigger_irq = QUIRK_LEVEL_IRQ(quirk);
		rt5645->pdata.inv_jd1_1 = QUIRK_INV_JD1_1(quirk);
		rt5645->pdata.inv_hp_pol = QUIRK_INV_HP_POL(quirk);
		rt5645->pdata.jd_mode = QUIRK_JD_MODE(quirk);
		rt5645->pdata.dmic1_data_pin = QUIRK_DMIC1_DATA_PIN(quirk);
		rt5645->pdata.dmic2_data_pin = QUIRK_DMIC2_DATA_PIN(quirk);
	पूर्ण

	अगर (has_acpi_companion(&i2c->dev)) अणु
		अगर (cht_rt5645_gpios) अणु
			अगर (devm_acpi_dev_add_driver_gpios(&i2c->dev, cht_rt5645_gpios))
				dev_dbg(&i2c->dev, "Failed to add driver gpios\n");
		पूर्ण

		/* The ALC3270 package has the headset-mic pin not-connected */
		अगर (acpi_dev_hid_uid_match(ACPI_COMPANION(&i2c->dev), "10EC3270", शून्य))
			rt5645->pdata.no_headset_mic = true;
	पूर्ण

	rt5645->gpiod_hp_det = devm_gpiod_get_optional(&i2c->dev, "hp-detect",
						       GPIOD_IN);

	अगर (IS_ERR(rt5645->gpiod_hp_det)) अणु
		dev_info(&i2c->dev, "failed to initialize gpiod\n");
		ret = PTR_ERR(rt5645->gpiod_hp_det);
		/*
		 * Continue अगर optional gpiod is missing, bail क्रम all other
		 * errors, including -EPROBE_DEFER
		 */
		अगर (ret != -ENOENT)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rt5645->supplies); i++)
		rt5645->supplies[i].supply = rt5645_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(rt5645->supplies),
				      rt5645->supplies);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(rt5645->supplies),
				    rt5645->supplies);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regmap = devm_regmap_init_i2c(i2c, &temp_regmap);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to allocate temp register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * Read after 400msec, as it is the पूर्णांकerval required between
	 * पढ़ो and घातer On.
	 */
	msleep(TIME_TO_POWER_MS);
	regmap_पढ़ो(regmap, RT5645_VENDOR_ID2, &val);

	चयन (val) अणु
	हाल RT5645_DEVICE_ID:
		rt5645->regmap = devm_regmap_init_i2c(i2c, &rt5645_regmap);
		rt5645->codec_type = CODEC_TYPE_RT5645;
		अवरोध;
	हाल RT5650_DEVICE_ID:
		rt5645->regmap = devm_regmap_init_i2c(i2c, &rt5650_regmap);
		rt5645->codec_type = CODEC_TYPE_RT5650;
		अवरोध;
	शेष:
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5645 or rt5650\n",
			val);
		ret = -ENODEV;
		जाओ err_enable;
	पूर्ण

	अगर (IS_ERR(rt5645->regmap)) अणु
		ret = PTR_ERR(rt5645->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_ग_लिखो(rt5645->regmap, RT5645_RESET, 0);

	regmap_पढ़ो(regmap, RT5645_VENDOR_ID, &val);
	rt5645->v_id = val & 0xff;

	regmap_ग_लिखो(rt5645->regmap, RT5645_AD_DA_MIXER, 0x8080);

	ret = regmap_रेजिस्टर_patch(rt5645->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	अगर (rt5645->codec_type == CODEC_TYPE_RT5650) अणु
		ret = regmap_रेजिस्टर_patch(rt5645->regmap, rt5650_init_list,
				    ARRAY_SIZE(rt5650_init_list));
		अगर (ret != 0)
			dev_warn(&i2c->dev, "Apply rt5650 patch failed: %d\n",
					   ret);
	पूर्ण

	regmap_update_bits(rt5645->regmap, RT5645_CLSD_OUT_CTRL, 0xc0, 0xc0);

	अगर (rt5645->pdata.in2_dअगरf)
		regmap_update_bits(rt5645->regmap, RT5645_IN2_CTRL,
					RT5645_IN_DF2, RT5645_IN_DF2);

	अगर (rt5645->pdata.dmic1_data_pin || rt5645->pdata.dmic2_data_pin) अणु
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP2_PIN_MASK, RT5645_GP2_PIN_DMIC1_SCL);
	पूर्ण
	चयन (rt5645->pdata.dmic1_data_pin) अणु
	हाल RT5645_DMIC_DATA_IN2N:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_IN2N);
		अवरोध;

	हाल RT5645_DMIC_DATA_GPIO5:
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_I2S2_DAC_PIN_MASK, RT5645_I2S2_DAC_PIN_GPIO);
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_GPIO5);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP5_PIN_MASK, RT5645_GP5_PIN_DMIC1_SDA);
		अवरोध;

	हाल RT5645_DMIC_DATA_GPIO11:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_GPIO11);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP11_PIN_MASK,
			RT5645_GP11_PIN_DMIC1_SDA);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	चयन (rt5645->pdata.dmic2_data_pin) अणु
	हाल RT5645_DMIC_DATA_IN2P:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_IN2P);
		अवरोध;

	हाल RT5645_DMIC_DATA_GPIO6:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO6);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP6_PIN_MASK, RT5645_GP6_PIN_DMIC2_SDA);
		अवरोध;

	हाल RT5645_DMIC_DATA_GPIO10:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO10);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP10_PIN_MASK,
			RT5645_GP10_PIN_DMIC2_SDA);
		अवरोध;

	हाल RT5645_DMIC_DATA_GPIO12:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO12);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP12_PIN_MASK,
			RT5645_GP12_PIN_DMIC2_SDA);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (rt5645->pdata.jd_mode) अणु
		regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
				   RT5645_IRQ_CLK_GATE_CTRL,
				   RT5645_IRQ_CLK_GATE_CTRL);
		regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
				   RT5645_IRQ_CLK_INT, RT5645_IRQ_CLK_INT);
		regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				   RT5645_IRQ_JD_1_1_EN, RT5645_IRQ_JD_1_1_EN);
		regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
				   RT5645_JD_PSV_MODE, RT5645_JD_PSV_MODE);
		regmap_update_bits(rt5645->regmap, RT5645_HPO_MIXER,
				   RT5645_IRQ_PSV_MODE, RT5645_IRQ_PSV_MODE);
		regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
				   RT5645_MIC2_OVCD_EN, RT5645_MIC2_OVCD_EN);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
				   RT5645_GP1_PIN_IRQ, RT5645_GP1_PIN_IRQ);
		चयन (rt5645->pdata.jd_mode) अणु
		हाल 1:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_0);
			अवरोध;
		हाल 2:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_1);
			अवरोध;
		हाल 3:
		हाल 4:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_2);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (rt5645->pdata.inv_jd1_1) अणु
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
		पूर्ण
	पूर्ण

	regmap_update_bits(rt5645->regmap, RT5645_ADDA_CLK1,
		RT5645_I2S_PD1_MASK, RT5645_I2S_PD1_2);

	अगर (rt5645->pdata.level_trigger_irq) अणु
		regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
			RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
	पूर्ण
	समयr_setup(&rt5645->btn_check_समयr, rt5645_btn_check_callback, 0);

	INIT_DELAYED_WORK(&rt5645->jack_detect_work, rt5645_jack_detect_work);
	INIT_DELAYED_WORK(&rt5645->rcघड़ी_work, rt5645_rcघड़ी_work);

	अगर (rt5645->i2c->irq) अणु
		ret = request_thपढ़ोed_irq(rt5645->i2c->irq, शून्य, rt5645_irq,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5645", rt5645);
		अगर (ret) अणु
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);
			जाओ err_enable;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &soc_component_dev_rt5645,
				     rt5645_dai, ARRAY_SIZE(rt5645_dai));
	अगर (ret)
		जाओ err_irq;

	वापस 0;

err_irq:
	अगर (rt5645->i2c->irq)
		मुक्त_irq(rt5645->i2c->irq, rt5645);
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(rt5645->supplies), rt5645->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक rt5645_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt5645_priv *rt5645 = i2c_get_clientdata(i2c);

	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, rt5645);

	cancel_delayed_work_sync(&rt5645->jack_detect_work);
	cancel_delayed_work_sync(&rt5645->rcघड़ी_work);
	del_समयr_sync(&rt5645->btn_check_समयr);

	regulator_bulk_disable(ARRAY_SIZE(rt5645->supplies), rt5645->supplies);

	वापस 0;
पूर्ण

अटल व्योम rt5645_i2c_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt5645_priv *rt5645 = i2c_get_clientdata(i2c);

	regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
		RT5645_RING2_SLEEVE_GND, RT5645_RING2_SLEEVE_GND);
	regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2, RT5645_CBJ_MN_JD,
		RT5645_CBJ_MN_JD);
	regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1, RT5645_CBJ_BST1_EN,
		0);
	msleep(20);
	regmap_ग_लिखो(rt5645->regmap, RT5645_RESET, 0);
पूर्ण

अटल काष्ठा i2c_driver rt5645_i2c_driver = अणु
	.driver = अणु
		.name = "rt5645",
		.of_match_table = of_match_ptr(rt5645_of_match),
		.acpi_match_table = ACPI_PTR(rt5645_acpi_match),
	पूर्ण,
	.probe = rt5645_i2c_probe,
	.हटाओ = rt5645_i2c_हटाओ,
	.shutकरोwn = rt5645_i2c_shutकरोwn,
	.id_table = rt5645_i2c_id,
पूर्ण;
module_i2c_driver(rt5645_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5645 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
