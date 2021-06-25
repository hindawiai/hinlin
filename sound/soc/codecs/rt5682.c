<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt5682.c  --  RT5682 ALSA SoC audio component driver
//
// Copyright 2018 Realtek Semiconductor Corp.
// Author: Bard Liao <bardliao@realtek.com>
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/rt5682.h>

#समावेश "rl6231.h"
#समावेश "rt5682.h"

स्थिर अक्षर *rt5682_supply_names[RT5682_NUM_SUPPLIES] = अणु
	"AVDD",
	"MICVDD",
	"VBAT",
पूर्ण;
EXPORT_SYMBOL_GPL(rt5682_supply_names);

अटल स्थिर काष्ठा reg_sequence patch_list[] = अणु
	अणुRT5682_HP_IMP_SENS_CTRL_19, 0x1000पूर्ण,
	अणुRT5682_DAC_ADC_DIG_VOL1, 0xa020पूर्ण,
	अणुRT5682_I2C_CTRL, 0x000fपूर्ण,
	अणुRT5682_PLL2_INTERNAL, 0x8266पूर्ण,
	अणुRT5682_SAR_IL_CMD_3, 0x8365पूर्ण,
पूर्ण;

व्योम rt5682_apply_patch_list(काष्ठा rt5682_priv *rt5682, काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = regmap_multi_reg_ग_लिखो(rt5682->regmap, patch_list,
				     ARRAY_SIZE(patch_list));
	अगर (ret)
		dev_warn(dev, "Failed to apply regmap patch: %d\n", ret);
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_apply_patch_list);

स्थिर काष्ठा reg_शेष rt5682_reg[RT5682_REG_NUM] = अणु
	अणु0x0002, 0x8080पूर्ण,
	अणु0x0003, 0x8000पूर्ण,
	अणु0x0005, 0x0000पूर्ण,
	अणु0x0006, 0x0000पूर्ण,
	अणु0x0008, 0x800fपूर्ण,
	अणु0x000b, 0x0000पूर्ण,
	अणु0x0010, 0x4040पूर्ण,
	अणु0x0011, 0x0000पूर्ण,
	अणु0x0012, 0x1404पूर्ण,
	अणु0x0013, 0x1000पूर्ण,
	अणु0x0014, 0xa00aपूर्ण,
	अणु0x0015, 0x0404पूर्ण,
	अणु0x0016, 0x0404पूर्ण,
	अणु0x0019, 0xafafपूर्ण,
	अणु0x001c, 0x2f2fपूर्ण,
	अणु0x001f, 0x0000पूर्ण,
	अणु0x0022, 0x5757पूर्ण,
	अणु0x0023, 0x0039पूर्ण,
	अणु0x0024, 0x000bपूर्ण,
	अणु0x0026, 0xc0c4पूर्ण,
	अणु0x0029, 0x8080पूर्ण,
	अणु0x002a, 0xa0a0पूर्ण,
	अणु0x002b, 0x0300पूर्ण,
	अणु0x0030, 0x0000पूर्ण,
	अणु0x003c, 0x0080पूर्ण,
	अणु0x0044, 0x0c0cपूर्ण,
	अणु0x0049, 0x0000पूर्ण,
	अणु0x0061, 0x0000पूर्ण,
	अणु0x0062, 0x0000पूर्ण,
	अणु0x0063, 0x003fपूर्ण,
	अणु0x0064, 0x0000पूर्ण,
	अणु0x0065, 0x0000पूर्ण,
	अणु0x0066, 0x0030पूर्ण,
	अणु0x0067, 0x0000पूर्ण,
	अणु0x006b, 0x0000पूर्ण,
	अणु0x006c, 0x0000पूर्ण,
	अणु0x006d, 0x2200पूर्ण,
	अणु0x006e, 0x0a10पूर्ण,
	अणु0x0070, 0x8000पूर्ण,
	अणु0x0071, 0x8000पूर्ण,
	अणु0x0073, 0x0000पूर्ण,
	अणु0x0074, 0x0000पूर्ण,
	अणु0x0075, 0x0002पूर्ण,
	अणु0x0076, 0x0001पूर्ण,
	अणु0x0079, 0x0000पूर्ण,
	अणु0x007a, 0x0000पूर्ण,
	अणु0x007b, 0x0000पूर्ण,
	अणु0x007c, 0x0100पूर्ण,
	अणु0x007e, 0x0000पूर्ण,
	अणु0x0080, 0x0000पूर्ण,
	अणु0x0081, 0x0000पूर्ण,
	अणु0x0082, 0x0000पूर्ण,
	अणु0x0083, 0x0000पूर्ण,
	अणु0x0084, 0x0000पूर्ण,
	अणु0x0085, 0x0000पूर्ण,
	अणु0x0086, 0x0005पूर्ण,
	अणु0x0087, 0x0000पूर्ण,
	अणु0x0088, 0x0000पूर्ण,
	अणु0x008c, 0x0003पूर्ण,
	अणु0x008d, 0x0000पूर्ण,
	अणु0x008e, 0x0060पूर्ण,
	अणु0x008f, 0x1000पूर्ण,
	अणु0x0091, 0x0c26पूर्ण,
	अणु0x0092, 0x0073पूर्ण,
	अणु0x0093, 0x0000पूर्ण,
	अणु0x0094, 0x0080पूर्ण,
	अणु0x0098, 0x0000पूर्ण,
	अणु0x009a, 0x0000पूर्ण,
	अणु0x009b, 0x0000पूर्ण,
	अणु0x009c, 0x0000पूर्ण,
	अणु0x009d, 0x0000पूर्ण,
	अणु0x009e, 0x100cपूर्ण,
	अणु0x009f, 0x0000पूर्ण,
	अणु0x00a0, 0x0000पूर्ण,
	अणु0x00a3, 0x0002पूर्ण,
	अणु0x00a4, 0x0001पूर्ण,
	अणु0x00ae, 0x2040पूर्ण,
	अणु0x00af, 0x0000पूर्ण,
	अणु0x00b6, 0x0000पूर्ण,
	अणु0x00b7, 0x0000पूर्ण,
	अणु0x00b8, 0x0000पूर्ण,
	अणु0x00b9, 0x0002पूर्ण,
	अणु0x00be, 0x0000पूर्ण,
	अणु0x00c0, 0x0160पूर्ण,
	अणु0x00c1, 0x82a0पूर्ण,
	अणु0x00c2, 0x0000पूर्ण,
	अणु0x00d0, 0x0000पूर्ण,
	अणु0x00d1, 0x2244पूर्ण,
	अणु0x00d2, 0x3300पूर्ण,
	अणु0x00d3, 0x2200पूर्ण,
	अणु0x00d4, 0x0000पूर्ण,
	अणु0x00d9, 0x0009पूर्ण,
	अणु0x00da, 0x0000पूर्ण,
	अणु0x00db, 0x0000पूर्ण,
	अणु0x00dc, 0x00c0पूर्ण,
	अणु0x00dd, 0x2220पूर्ण,
	अणु0x00de, 0x3131पूर्ण,
	अणु0x00df, 0x3131पूर्ण,
	अणु0x00e0, 0x3131पूर्ण,
	अणु0x00e2, 0x0000पूर्ण,
	अणु0x00e3, 0x4000पूर्ण,
	अणु0x00e4, 0x0aa0पूर्ण,
	अणु0x00e5, 0x3131पूर्ण,
	अणु0x00e6, 0x3131पूर्ण,
	अणु0x00e7, 0x3131पूर्ण,
	अणु0x00e8, 0x3131पूर्ण,
	अणु0x00ea, 0xb320पूर्ण,
	अणु0x00eb, 0x0000पूर्ण,
	अणु0x00f0, 0x0000पूर्ण,
	अणु0x00f1, 0x00d0पूर्ण,
	अणु0x00f2, 0x00d0पूर्ण,
	अणु0x00f6, 0x0000पूर्ण,
	अणु0x00fa, 0x0000पूर्ण,
	अणु0x00fb, 0x0000पूर्ण,
	अणु0x00fc, 0x0000पूर्ण,
	अणु0x00fd, 0x0000पूर्ण,
	अणु0x00fe, 0x10ecपूर्ण,
	अणु0x00ff, 0x6530पूर्ण,
	अणु0x0100, 0xa0a0पूर्ण,
	अणु0x010b, 0x0000पूर्ण,
	अणु0x010c, 0xae00पूर्ण,
	अणु0x010d, 0xaaa0पूर्ण,
	अणु0x010e, 0x8aa2पूर्ण,
	अणु0x010f, 0x02a2पूर्ण,
	अणु0x0110, 0xc000पूर्ण,
	अणु0x0111, 0x04a2पूर्ण,
	अणु0x0112, 0x2800पूर्ण,
	अणु0x0113, 0x0000पूर्ण,
	अणु0x0117, 0x0100पूर्ण,
	अणु0x0125, 0x0410पूर्ण,
	अणु0x0132, 0x6026पूर्ण,
	अणु0x0136, 0x5555पूर्ण,
	अणु0x0138, 0x3700पूर्ण,
	अणु0x013a, 0x2000पूर्ण,
	अणु0x013b, 0x2000पूर्ण,
	अणु0x013c, 0x2005पूर्ण,
	अणु0x013f, 0x0000पूर्ण,
	अणु0x0142, 0x0000पूर्ण,
	अणु0x0145, 0x0002पूर्ण,
	अणु0x0146, 0x0000पूर्ण,
	अणु0x0147, 0x0000पूर्ण,
	अणु0x0148, 0x0000पूर्ण,
	अणु0x0149, 0x0000पूर्ण,
	अणु0x0150, 0x79a1पूर्ण,
	अणु0x0156, 0xaaaaपूर्ण,
	अणु0x0160, 0x4ec0पूर्ण,
	अणु0x0161, 0x0080पूर्ण,
	अणु0x0162, 0x0200पूर्ण,
	अणु0x0163, 0x0800पूर्ण,
	अणु0x0164, 0x0000पूर्ण,
	अणु0x0165, 0x0000पूर्ण,
	अणु0x0166, 0x0000पूर्ण,
	अणु0x0167, 0x000fपूर्ण,
	अणु0x0168, 0x000fपूर्ण,
	अणु0x0169, 0x0021पूर्ण,
	अणु0x0190, 0x413dपूर्ण,
	अणु0x0194, 0x0000पूर्ण,
	अणु0x0195, 0x0000पूर्ण,
	अणु0x0197, 0x0022पूर्ण,
	अणु0x0198, 0x0000पूर्ण,
	अणु0x0199, 0x0000पूर्ण,
	अणु0x01af, 0x0000पूर्ण,
	अणु0x01b0, 0x0400पूर्ण,
	अणु0x01b1, 0x0000पूर्ण,
	अणु0x01b2, 0x0000पूर्ण,
	अणु0x01b3, 0x0000पूर्ण,
	अणु0x01b4, 0x0000पूर्ण,
	अणु0x01b5, 0x0000पूर्ण,
	अणु0x01b6, 0x01c3पूर्ण,
	अणु0x01b7, 0x02a0पूर्ण,
	अणु0x01b8, 0x03e9पूर्ण,
	अणु0x01b9, 0x1389पूर्ण,
	अणु0x01ba, 0xc351पूर्ण,
	अणु0x01bb, 0x0009पूर्ण,
	अणु0x01bc, 0x0018पूर्ण,
	अणु0x01bd, 0x002aपूर्ण,
	अणु0x01be, 0x004cपूर्ण,
	अणु0x01bf, 0x0097पूर्ण,
	अणु0x01c0, 0x433dपूर्ण,
	अणु0x01c2, 0x0000पूर्ण,
	अणु0x01c3, 0x0000पूर्ण,
	अणु0x01c4, 0x0000पूर्ण,
	अणु0x01c5, 0x0000पूर्ण,
	अणु0x01c6, 0x0000पूर्ण,
	अणु0x01c7, 0x0000पूर्ण,
	अणु0x01c8, 0x40afपूर्ण,
	अणु0x01c9, 0x0702पूर्ण,
	अणु0x01ca, 0x0000पूर्ण,
	अणु0x01cb, 0x0000पूर्ण,
	अणु0x01cc, 0x5757पूर्ण,
	अणु0x01cd, 0x5757पूर्ण,
	अणु0x01ce, 0x5757पूर्ण,
	अणु0x01cf, 0x5757पूर्ण,
	अणु0x01d0, 0x5757पूर्ण,
	अणु0x01d1, 0x5757पूर्ण,
	अणु0x01d2, 0x5757पूर्ण,
	अणु0x01d3, 0x5757पूर्ण,
	अणु0x01d4, 0x5757पूर्ण,
	अणु0x01d5, 0x5757पूर्ण,
	अणु0x01d6, 0x0000पूर्ण,
	अणु0x01d7, 0x0008पूर्ण,
	अणु0x01d8, 0x0029पूर्ण,
	अणु0x01d9, 0x3333पूर्ण,
	अणु0x01da, 0x0000पूर्ण,
	अणु0x01db, 0x0004पूर्ण,
	अणु0x01dc, 0x0000पूर्ण,
	अणु0x01de, 0x7c00पूर्ण,
	अणु0x01df, 0x0320पूर्ण,
	अणु0x01e0, 0x06a1पूर्ण,
	अणु0x01e1, 0x0000पूर्ण,
	अणु0x01e2, 0x0000पूर्ण,
	अणु0x01e3, 0x0000पूर्ण,
	अणु0x01e4, 0x0000पूर्ण,
	अणु0x01e6, 0x0001पूर्ण,
	अणु0x01e7, 0x0000पूर्ण,
	अणु0x01e8, 0x0000पूर्ण,
	अणु0x01ea, 0x0000पूर्ण,
	अणु0x01eb, 0x0000पूर्ण,
	अणु0x01ec, 0x0000पूर्ण,
	अणु0x01ed, 0x0000पूर्ण,
	अणु0x01ee, 0x0000पूर्ण,
	अणु0x01ef, 0x0000पूर्ण,
	अणु0x01f0, 0x0000पूर्ण,
	अणु0x01f1, 0x0000पूर्ण,
	अणु0x01f2, 0x0000पूर्ण,
	अणु0x01f3, 0x0000पूर्ण,
	अणु0x01f4, 0x0000पूर्ण,
	अणु0x0210, 0x6297पूर्ण,
	अणु0x0211, 0xa005पूर्ण,
	अणु0x0212, 0x824cपूर्ण,
	अणु0x0213, 0xf7ffपूर्ण,
	अणु0x0214, 0xf24cपूर्ण,
	अणु0x0215, 0x0102पूर्ण,
	अणु0x0216, 0x00a3पूर्ण,
	अणु0x0217, 0x0048पूर्ण,
	अणु0x0218, 0xa2c0पूर्ण,
	अणु0x0219, 0x0400पूर्ण,
	अणु0x021a, 0x00c8पूर्ण,
	अणु0x021b, 0x00c0पूर्ण,
	अणु0x021c, 0x0000पूर्ण,
	अणु0x0250, 0x4500पूर्ण,
	अणु0x0251, 0x40b3पूर्ण,
	अणु0x0252, 0x0000पूर्ण,
	अणु0x0253, 0x0000पूर्ण,
	अणु0x0254, 0x0000पूर्ण,
	अणु0x0255, 0x0000पूर्ण,
	अणु0x0256, 0x0000पूर्ण,
	अणु0x0257, 0x0000पूर्ण,
	अणु0x0258, 0x0000पूर्ण,
	अणु0x0259, 0x0000पूर्ण,
	अणु0x025a, 0x0005पूर्ण,
	अणु0x0270, 0x0000पूर्ण,
	अणु0x02ff, 0x0110पूर्ण,
	अणु0x0300, 0x001fपूर्ण,
	अणु0x0301, 0x032cपूर्ण,
	अणु0x0302, 0x5f21पूर्ण,
	अणु0x0303, 0x4000पूर्ण,
	अणु0x0304, 0x4000पूर्ण,
	अणु0x0305, 0x06d5पूर्ण,
	अणु0x0306, 0x8000पूर्ण,
	अणु0x0307, 0x0700पूर्ण,
	अणु0x0310, 0x4560पूर्ण,
	अणु0x0311, 0xa4a8पूर्ण,
	अणु0x0312, 0x7418पूर्ण,
	अणु0x0313, 0x0000पूर्ण,
	अणु0x0314, 0x0006पूर्ण,
	अणु0x0315, 0xffffपूर्ण,
	अणु0x0316, 0xc400पूर्ण,
	अणु0x0317, 0x0000पूर्ण,
	अणु0x03c0, 0x7e00पूर्ण,
	अणु0x03c1, 0x8000पूर्ण,
	अणु0x03c2, 0x8000पूर्ण,
	अणु0x03c3, 0x8000पूर्ण,
	अणु0x03c4, 0x8000पूर्ण,
	अणु0x03c5, 0x8000पूर्ण,
	अणु0x03c6, 0x8000पूर्ण,
	अणु0x03c7, 0x8000पूर्ण,
	अणु0x03c8, 0x8000पूर्ण,
	अणु0x03c9, 0x8000पूर्ण,
	अणु0x03ca, 0x8000पूर्ण,
	अणु0x03cb, 0x8000पूर्ण,
	अणु0x03cc, 0x8000पूर्ण,
	अणु0x03d0, 0x0000पूर्ण,
	अणु0x03d1, 0x0000पूर्ण,
	अणु0x03d2, 0x0000पूर्ण,
	अणु0x03d3, 0x0000पूर्ण,
	अणु0x03d4, 0x2000पूर्ण,
	अणु0x03d5, 0x2000पूर्ण,
	अणु0x03d6, 0x0000पूर्ण,
	अणु0x03d7, 0x0000पूर्ण,
	अणु0x03d8, 0x2000पूर्ण,
	अणु0x03d9, 0x2000पूर्ण,
	अणु0x03da, 0x2000पूर्ण,
	अणु0x03db, 0x2000पूर्ण,
	अणु0x03dc, 0x0000पूर्ण,
	अणु0x03dd, 0x0000पूर्ण,
	अणु0x03de, 0x0000पूर्ण,
	अणु0x03df, 0x2000पूर्ण,
	अणु0x03e0, 0x0000पूर्ण,
	अणु0x03e1, 0x0000पूर्ण,
	अणु0x03e2, 0x0000पूर्ण,
	अणु0x03e3, 0x0000पूर्ण,
	अणु0x03e4, 0x0000पूर्ण,
	अणु0x03e5, 0x0000पूर्ण,
	अणु0x03e6, 0x0000पूर्ण,
	अणु0x03e7, 0x0000पूर्ण,
	अणु0x03e8, 0x0000पूर्ण,
	अणु0x03e9, 0x0000पूर्ण,
	अणु0x03ea, 0x0000पूर्ण,
	अणु0x03eb, 0x0000पूर्ण,
	अणु0x03ec, 0x0000पूर्ण,
	अणु0x03ed, 0x0000पूर्ण,
	अणु0x03ee, 0x0000पूर्ण,
	अणु0x03ef, 0x0000पूर्ण,
	अणु0x03f0, 0x0800पूर्ण,
	अणु0x03f1, 0x0800पूर्ण,
	अणु0x03f2, 0x0800पूर्ण,
	अणु0x03f3, 0x0800पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(rt5682_reg);

bool rt5682_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5682_RESET:
	हाल RT5682_CBJ_CTRL_2:
	हाल RT5682_INT_ST_1:
	हाल RT5682_4BTN_IL_CMD_1:
	हाल RT5682_AJD1_CTRL:
	हाल RT5682_HP_CALIB_CTRL_1:
	हाल RT5682_DEVICE_ID:
	हाल RT5682_I2C_MODE:
	हाल RT5682_HP_CALIB_CTRL_10:
	हाल RT5682_EFUSE_CTRL_2:
	हाल RT5682_JD_TOP_VC_VTRL:
	हाल RT5682_HP_IMP_SENS_CTRL_19:
	हाल RT5682_IL_CMD_1:
	हाल RT5682_SAR_IL_CMD_2:
	हाल RT5682_SAR_IL_CMD_4:
	हाल RT5682_SAR_IL_CMD_10:
	हाल RT5682_SAR_IL_CMD_11:
	हाल RT5682_EFUSE_CTRL_6...RT5682_EFUSE_CTRL_11:
	हाल RT5682_HP_CALIB_STA_1...RT5682_HP_CALIB_STA_11:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_अस्थिर_रेजिस्टर);

bool rt5682_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5682_RESET:
	हाल RT5682_VERSION_ID:
	हाल RT5682_VENDOR_ID:
	हाल RT5682_DEVICE_ID:
	हाल RT5682_HP_CTRL_1:
	हाल RT5682_HP_CTRL_2:
	हाल RT5682_HPL_GAIN:
	हाल RT5682_HPR_GAIN:
	हाल RT5682_I2C_CTRL:
	हाल RT5682_CBJ_BST_CTRL:
	हाल RT5682_CBJ_CTRL_1:
	हाल RT5682_CBJ_CTRL_2:
	हाल RT5682_CBJ_CTRL_3:
	हाल RT5682_CBJ_CTRL_4:
	हाल RT5682_CBJ_CTRL_5:
	हाल RT5682_CBJ_CTRL_6:
	हाल RT5682_CBJ_CTRL_7:
	हाल RT5682_DAC1_DIG_VOL:
	हाल RT5682_STO1_ADC_DIG_VOL:
	हाल RT5682_STO1_ADC_BOOST:
	हाल RT5682_HP_IMP_GAIN_1:
	हाल RT5682_HP_IMP_GAIN_2:
	हाल RT5682_SIDETONE_CTRL:
	हाल RT5682_STO1_ADC_MIXER:
	हाल RT5682_AD_DA_MIXER:
	हाल RT5682_STO1_DAC_MIXER:
	हाल RT5682_A_DAC1_MUX:
	हाल RT5682_DIG_INF2_DATA:
	हाल RT5682_REC_MIXER:
	हाल RT5682_CAL_REC:
	हाल RT5682_ALC_BACK_GAIN:
	हाल RT5682_PWR_DIG_1:
	हाल RT5682_PWR_DIG_2:
	हाल RT5682_PWR_ANLG_1:
	हाल RT5682_PWR_ANLG_2:
	हाल RT5682_PWR_ANLG_3:
	हाल RT5682_PWR_MIXER:
	हाल RT5682_PWR_VOL:
	हाल RT5682_CLK_DET:
	हाल RT5682_RESET_LPF_CTRL:
	हाल RT5682_RESET_HPF_CTRL:
	हाल RT5682_DMIC_CTRL_1:
	हाल RT5682_I2S1_SDP:
	हाल RT5682_I2S2_SDP:
	हाल RT5682_ADDA_CLK_1:
	हाल RT5682_ADDA_CLK_2:
	हाल RT5682_I2S1_F_DIV_CTRL_1:
	हाल RT5682_I2S1_F_DIV_CTRL_2:
	हाल RT5682_TDM_CTRL:
	हाल RT5682_TDM_ADDA_CTRL_1:
	हाल RT5682_TDM_ADDA_CTRL_2:
	हाल RT5682_DATA_SEL_CTRL_1:
	हाल RT5682_TDM_TCON_CTRL:
	हाल RT5682_GLB_CLK:
	हाल RT5682_PLL_CTRL_1:
	हाल RT5682_PLL_CTRL_2:
	हाल RT5682_PLL_TRACK_1:
	हाल RT5682_PLL_TRACK_2:
	हाल RT5682_PLL_TRACK_3:
	हाल RT5682_PLL_TRACK_4:
	हाल RT5682_PLL_TRACK_5:
	हाल RT5682_PLL_TRACK_6:
	हाल RT5682_PLL_TRACK_11:
	हाल RT5682_SDW_REF_CLK:
	हाल RT5682_DEPOP_1:
	हाल RT5682_DEPOP_2:
	हाल RT5682_HP_CHARGE_PUMP_1:
	हाल RT5682_HP_CHARGE_PUMP_2:
	हाल RT5682_MICBIAS_1:
	हाल RT5682_MICBIAS_2:
	हाल RT5682_PLL_TRACK_12:
	हाल RT5682_PLL_TRACK_14:
	हाल RT5682_PLL2_CTRL_1:
	हाल RT5682_PLL2_CTRL_2:
	हाल RT5682_PLL2_CTRL_3:
	हाल RT5682_PLL2_CTRL_4:
	हाल RT5682_RC_CLK_CTRL:
	हाल RT5682_I2S_M_CLK_CTRL_1:
	हाल RT5682_I2S2_F_DIV_CTRL_1:
	हाल RT5682_I2S2_F_DIV_CTRL_2:
	हाल RT5682_EQ_CTRL_1:
	हाल RT5682_EQ_CTRL_2:
	हाल RT5682_IRQ_CTRL_1:
	हाल RT5682_IRQ_CTRL_2:
	हाल RT5682_IRQ_CTRL_3:
	हाल RT5682_IRQ_CTRL_4:
	हाल RT5682_INT_ST_1:
	हाल RT5682_GPIO_CTRL_1:
	हाल RT5682_GPIO_CTRL_2:
	हाल RT5682_GPIO_CTRL_3:
	हाल RT5682_HP_AMP_DET_CTRL_1:
	हाल RT5682_HP_AMP_DET_CTRL_2:
	हाल RT5682_MID_HP_AMP_DET:
	हाल RT5682_LOW_HP_AMP_DET:
	हाल RT5682_DELAY_BUF_CTRL:
	हाल RT5682_SV_ZCD_1:
	हाल RT5682_SV_ZCD_2:
	हाल RT5682_IL_CMD_1:
	हाल RT5682_IL_CMD_2:
	हाल RT5682_IL_CMD_3:
	हाल RT5682_IL_CMD_4:
	हाल RT5682_IL_CMD_5:
	हाल RT5682_IL_CMD_6:
	हाल RT5682_4BTN_IL_CMD_1:
	हाल RT5682_4BTN_IL_CMD_2:
	हाल RT5682_4BTN_IL_CMD_3:
	हाल RT5682_4BTN_IL_CMD_4:
	हाल RT5682_4BTN_IL_CMD_5:
	हाल RT5682_4BTN_IL_CMD_6:
	हाल RT5682_4BTN_IL_CMD_7:
	हाल RT5682_ADC_STO1_HP_CTRL_1:
	हाल RT5682_ADC_STO1_HP_CTRL_2:
	हाल RT5682_AJD1_CTRL:
	हाल RT5682_JD1_THD:
	हाल RT5682_JD2_THD:
	हाल RT5682_JD_CTRL_1:
	हाल RT5682_DUMMY_1:
	हाल RT5682_DUMMY_2:
	हाल RT5682_DUMMY_3:
	हाल RT5682_DAC_ADC_DIG_VOL1:
	हाल RT5682_BIAS_CUR_CTRL_2:
	हाल RT5682_BIAS_CUR_CTRL_3:
	हाल RT5682_BIAS_CUR_CTRL_4:
	हाल RT5682_BIAS_CUR_CTRL_5:
	हाल RT5682_BIAS_CUR_CTRL_6:
	हाल RT5682_BIAS_CUR_CTRL_7:
	हाल RT5682_BIAS_CUR_CTRL_8:
	हाल RT5682_BIAS_CUR_CTRL_9:
	हाल RT5682_BIAS_CUR_CTRL_10:
	हाल RT5682_VREF_REC_OP_FB_CAP_CTRL:
	हाल RT5682_CHARGE_PUMP_1:
	हाल RT5682_DIG_IN_CTRL_1:
	हाल RT5682_PAD_DRIVING_CTRL:
	हाल RT5682_SOFT_RAMP_DEPOP:
	हाल RT5682_CHOP_DAC:
	हाल RT5682_CHOP_ADC:
	हाल RT5682_CALIB_ADC_CTRL:
	हाल RT5682_VOL_TEST:
	हाल RT5682_SPKVDD_DET_STA:
	हाल RT5682_TEST_MODE_CTRL_1:
	हाल RT5682_TEST_MODE_CTRL_2:
	हाल RT5682_TEST_MODE_CTRL_3:
	हाल RT5682_TEST_MODE_CTRL_4:
	हाल RT5682_TEST_MODE_CTRL_5:
	हाल RT5682_PLL1_INTERNAL:
	हाल RT5682_PLL2_INTERNAL:
	हाल RT5682_STO_NG2_CTRL_1:
	हाल RT5682_STO_NG2_CTRL_2:
	हाल RT5682_STO_NG2_CTRL_3:
	हाल RT5682_STO_NG2_CTRL_4:
	हाल RT5682_STO_NG2_CTRL_5:
	हाल RT5682_STO_NG2_CTRL_6:
	हाल RT5682_STO_NG2_CTRL_7:
	हाल RT5682_STO_NG2_CTRL_8:
	हाल RT5682_STO_NG2_CTRL_9:
	हाल RT5682_STO_NG2_CTRL_10:
	हाल RT5682_STO1_DAC_SIL_DET:
	हाल RT5682_SIL_PSV_CTRL1:
	हाल RT5682_SIL_PSV_CTRL2:
	हाल RT5682_SIL_PSV_CTRL3:
	हाल RT5682_SIL_PSV_CTRL4:
	हाल RT5682_SIL_PSV_CTRL5:
	हाल RT5682_HP_IMP_SENS_CTRL_01:
	हाल RT5682_HP_IMP_SENS_CTRL_02:
	हाल RT5682_HP_IMP_SENS_CTRL_03:
	हाल RT5682_HP_IMP_SENS_CTRL_04:
	हाल RT5682_HP_IMP_SENS_CTRL_05:
	हाल RT5682_HP_IMP_SENS_CTRL_06:
	हाल RT5682_HP_IMP_SENS_CTRL_07:
	हाल RT5682_HP_IMP_SENS_CTRL_08:
	हाल RT5682_HP_IMP_SENS_CTRL_09:
	हाल RT5682_HP_IMP_SENS_CTRL_10:
	हाल RT5682_HP_IMP_SENS_CTRL_11:
	हाल RT5682_HP_IMP_SENS_CTRL_12:
	हाल RT5682_HP_IMP_SENS_CTRL_13:
	हाल RT5682_HP_IMP_SENS_CTRL_14:
	हाल RT5682_HP_IMP_SENS_CTRL_15:
	हाल RT5682_HP_IMP_SENS_CTRL_16:
	हाल RT5682_HP_IMP_SENS_CTRL_17:
	हाल RT5682_HP_IMP_SENS_CTRL_18:
	हाल RT5682_HP_IMP_SENS_CTRL_19:
	हाल RT5682_HP_IMP_SENS_CTRL_20:
	हाल RT5682_HP_IMP_SENS_CTRL_21:
	हाल RT5682_HP_IMP_SENS_CTRL_22:
	हाल RT5682_HP_IMP_SENS_CTRL_23:
	हाल RT5682_HP_IMP_SENS_CTRL_24:
	हाल RT5682_HP_IMP_SENS_CTRL_25:
	हाल RT5682_HP_IMP_SENS_CTRL_26:
	हाल RT5682_HP_IMP_SENS_CTRL_27:
	हाल RT5682_HP_IMP_SENS_CTRL_28:
	हाल RT5682_HP_IMP_SENS_CTRL_29:
	हाल RT5682_HP_IMP_SENS_CTRL_30:
	हाल RT5682_HP_IMP_SENS_CTRL_31:
	हाल RT5682_HP_IMP_SENS_CTRL_32:
	हाल RT5682_HP_IMP_SENS_CTRL_33:
	हाल RT5682_HP_IMP_SENS_CTRL_34:
	हाल RT5682_HP_IMP_SENS_CTRL_35:
	हाल RT5682_HP_IMP_SENS_CTRL_36:
	हाल RT5682_HP_IMP_SENS_CTRL_37:
	हाल RT5682_HP_IMP_SENS_CTRL_38:
	हाल RT5682_HP_IMP_SENS_CTRL_39:
	हाल RT5682_HP_IMP_SENS_CTRL_40:
	हाल RT5682_HP_IMP_SENS_CTRL_41:
	हाल RT5682_HP_IMP_SENS_CTRL_42:
	हाल RT5682_HP_IMP_SENS_CTRL_43:
	हाल RT5682_HP_LOGIC_CTRL_1:
	हाल RT5682_HP_LOGIC_CTRL_2:
	हाल RT5682_HP_LOGIC_CTRL_3:
	हाल RT5682_HP_CALIB_CTRL_1:
	हाल RT5682_HP_CALIB_CTRL_2:
	हाल RT5682_HP_CALIB_CTRL_3:
	हाल RT5682_HP_CALIB_CTRL_4:
	हाल RT5682_HP_CALIB_CTRL_5:
	हाल RT5682_HP_CALIB_CTRL_6:
	हाल RT5682_HP_CALIB_CTRL_7:
	हाल RT5682_HP_CALIB_CTRL_9:
	हाल RT5682_HP_CALIB_CTRL_10:
	हाल RT5682_HP_CALIB_CTRL_11:
	हाल RT5682_HP_CALIB_STA_1:
	हाल RT5682_HP_CALIB_STA_2:
	हाल RT5682_HP_CALIB_STA_3:
	हाल RT5682_HP_CALIB_STA_4:
	हाल RT5682_HP_CALIB_STA_5:
	हाल RT5682_HP_CALIB_STA_6:
	हाल RT5682_HP_CALIB_STA_7:
	हाल RT5682_HP_CALIB_STA_8:
	हाल RT5682_HP_CALIB_STA_9:
	हाल RT5682_HP_CALIB_STA_10:
	हाल RT5682_HP_CALIB_STA_11:
	हाल RT5682_SAR_IL_CMD_1:
	हाल RT5682_SAR_IL_CMD_2:
	हाल RT5682_SAR_IL_CMD_3:
	हाल RT5682_SAR_IL_CMD_4:
	हाल RT5682_SAR_IL_CMD_5:
	हाल RT5682_SAR_IL_CMD_6:
	हाल RT5682_SAR_IL_CMD_7:
	हाल RT5682_SAR_IL_CMD_8:
	हाल RT5682_SAR_IL_CMD_9:
	हाल RT5682_SAR_IL_CMD_10:
	हाल RT5682_SAR_IL_CMD_11:
	हाल RT5682_SAR_IL_CMD_12:
	हाल RT5682_SAR_IL_CMD_13:
	हाल RT5682_EFUSE_CTRL_1:
	हाल RT5682_EFUSE_CTRL_2:
	हाल RT5682_EFUSE_CTRL_3:
	हाल RT5682_EFUSE_CTRL_4:
	हाल RT5682_EFUSE_CTRL_5:
	हाल RT5682_EFUSE_CTRL_6:
	हाल RT5682_EFUSE_CTRL_7:
	हाल RT5682_EFUSE_CTRL_8:
	हाल RT5682_EFUSE_CTRL_9:
	हाल RT5682_EFUSE_CTRL_10:
	हाल RT5682_EFUSE_CTRL_11:
	हाल RT5682_JD_TOP_VC_VTRL:
	हाल RT5682_DRC1_CTRL_0:
	हाल RT5682_DRC1_CTRL_1:
	हाल RT5682_DRC1_CTRL_2:
	हाल RT5682_DRC1_CTRL_3:
	हाल RT5682_DRC1_CTRL_4:
	हाल RT5682_DRC1_CTRL_5:
	हाल RT5682_DRC1_CTRL_6:
	हाल RT5682_DRC1_HARD_LMT_CTRL_1:
	हाल RT5682_DRC1_HARD_LMT_CTRL_2:
	हाल RT5682_DRC1_PRIV_1:
	हाल RT5682_DRC1_PRIV_2:
	हाल RT5682_DRC1_PRIV_3:
	हाल RT5682_DRC1_PRIV_4:
	हाल RT5682_DRC1_PRIV_5:
	हाल RT5682_DRC1_PRIV_6:
	हाल RT5682_DRC1_PRIV_7:
	हाल RT5682_DRC1_PRIV_8:
	हाल RT5682_EQ_AUTO_RCV_CTRL1:
	हाल RT5682_EQ_AUTO_RCV_CTRL2:
	हाल RT5682_EQ_AUTO_RCV_CTRL3:
	हाल RT5682_EQ_AUTO_RCV_CTRL4:
	हाल RT5682_EQ_AUTO_RCV_CTRL5:
	हाल RT5682_EQ_AUTO_RCV_CTRL6:
	हाल RT5682_EQ_AUTO_RCV_CTRL7:
	हाल RT5682_EQ_AUTO_RCV_CTRL8:
	हाल RT5682_EQ_AUTO_RCV_CTRL9:
	हाल RT5682_EQ_AUTO_RCV_CTRL10:
	हाल RT5682_EQ_AUTO_RCV_CTRL11:
	हाल RT5682_EQ_AUTO_RCV_CTRL12:
	हाल RT5682_EQ_AUTO_RCV_CTRL13:
	हाल RT5682_ADC_L_EQ_LPF1_A1:
	हाल RT5682_R_EQ_LPF1_A1:
	हाल RT5682_L_EQ_LPF1_H0:
	हाल RT5682_R_EQ_LPF1_H0:
	हाल RT5682_L_EQ_BPF1_A1:
	हाल RT5682_R_EQ_BPF1_A1:
	हाल RT5682_L_EQ_BPF1_A2:
	हाल RT5682_R_EQ_BPF1_A2:
	हाल RT5682_L_EQ_BPF1_H0:
	हाल RT5682_R_EQ_BPF1_H0:
	हाल RT5682_L_EQ_BPF2_A1:
	हाल RT5682_R_EQ_BPF2_A1:
	हाल RT5682_L_EQ_BPF2_A2:
	हाल RT5682_R_EQ_BPF2_A2:
	हाल RT5682_L_EQ_BPF2_H0:
	हाल RT5682_R_EQ_BPF2_H0:
	हाल RT5682_L_EQ_BPF3_A1:
	हाल RT5682_R_EQ_BPF3_A1:
	हाल RT5682_L_EQ_BPF3_A2:
	हाल RT5682_R_EQ_BPF3_A2:
	हाल RT5682_L_EQ_BPF3_H0:
	हाल RT5682_R_EQ_BPF3_H0:
	हाल RT5682_L_EQ_BPF4_A1:
	हाल RT5682_R_EQ_BPF4_A1:
	हाल RT5682_L_EQ_BPF4_A2:
	हाल RT5682_R_EQ_BPF4_A2:
	हाल RT5682_L_EQ_BPF4_H0:
	हाल RT5682_R_EQ_BPF4_H0:
	हाल RT5682_L_EQ_HPF1_A1:
	हाल RT5682_R_EQ_HPF1_A1:
	हाल RT5682_L_EQ_HPF1_H0:
	हाल RT5682_R_EQ_HPF1_H0:
	हाल RT5682_L_EQ_PRE_VOL:
	हाल RT5682_R_EQ_PRE_VOL:
	हाल RT5682_L_EQ_POST_VOL:
	हाल RT5682_R_EQ_POST_VOL:
	हाल RT5682_I2C_MODE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_पढ़ोable_रेजिस्टर);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -6525, 75, 0);
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

/* Interface data select */
अटल स्थिर अक्षर * स्थिर rt5682_data_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5682_अगर2_adc_क्रमागत,
	RT5682_DIG_INF2_DATA, RT5682_IF2_ADC_SEL_SFT, rt5682_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5682_अगर1_01_adc_क्रमागत,
	RT5682_TDM_ADDA_CTRL_1, RT5682_IF1_ADC1_SEL_SFT, rt5682_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5682_अगर1_23_adc_क्रमागत,
	RT5682_TDM_ADDA_CTRL_1, RT5682_IF1_ADC2_SEL_SFT, rt5682_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5682_अगर1_45_adc_क्रमागत,
	RT5682_TDM_ADDA_CTRL_1, RT5682_IF1_ADC3_SEL_SFT, rt5682_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5682_अगर1_67_adc_क्रमागत,
	RT5682_TDM_ADDA_CTRL_1, RT5682_IF1_ADC4_SEL_SFT, rt5682_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर2_adc_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC Swap Mux", rt5682_अगर2_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर1_01_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 01 ADC Swap Mux", rt5682_अगर1_01_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर1_23_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 23 ADC Swap Mux", rt5682_अगर1_23_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर1_45_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 45 ADC Swap Mux", rt5682_अगर1_45_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर1_67_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 67 ADC Swap Mux", rt5682_अगर1_67_adc_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5682_dac_select[] = अणु
	"IF1", "SOUND"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5682_dacl_क्रमागत,
	RT5682_AD_DA_MIXER, RT5682_DAC1_L_SEL_SFT, rt5682_dac_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_dac_l_mux =
	SOC_DAPM_ENUM("DAC L Mux", rt5682_dacl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5682_dacr_क्रमागत,
	RT5682_AD_DA_MIXER, RT5682_DAC1_R_SEL_SFT, rt5682_dac_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_dac_r_mux =
	SOC_DAPM_ENUM("DAC R Mux", rt5682_dacr_क्रमागत);

व्योम rt5682_reset(काष्ठा rt5682_priv *rt5682)
अणु
	regmap_ग_लिखो(rt5682->regmap, RT5682_RESET, 0);
	अगर (!rt5682->is_sdw)
		regmap_ग_लिखो(rt5682->regmap, RT5682_I2C_MODE, 1);
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_reset);

/**
 * rt5682_sel_asrc_clk_src - select ASRC घड़ी source क्रम a set of filters
 * @component: SoC audio component device.
 * @filter_mask: mask of filters.
 * @clk_src: घड़ी source
 *
 * The ASRC function is क्रम asynchronous MCLK and LRCK. Also, since RT5682 can
 * only support standard 32fs or 64fs i2s क्रमmat, ASRC should be enabled to
 * support special i2s घड़ी क्रमmat such as Intel's 100fs(100 * sampling rate).
 * ASRC function will track i2s घड़ी and generate a corresponding प्रणाली घड़ी
 * क्रम codec. This function provides an API to select the घड़ी source क्रम a
 * set of filters specअगरied by the mask. And the component driver will turn on
 * ASRC क्रम these filters अगर ASRC is selected as their घड़ी source.
 */
पूर्णांक rt5682_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	चयन (clk_src) अणु
	हाल RT5682_CLK_SEL_SYS:
	हाल RT5682_CLK_SEL_I2S1_ASRC:
	हाल RT5682_CLK_SEL_I2S2_ASRC:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (filter_mask & RT5682_DA_STEREO1_FILTER) अणु
		snd_soc_component_update_bits(component, RT5682_PLL_TRACK_2,
			RT5682_FILTER_CLK_SEL_MASK,
			clk_src << RT5682_FILTER_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5682_AD_STEREO1_FILTER) अणु
		snd_soc_component_update_bits(component, RT5682_PLL_TRACK_3,
			RT5682_FILTER_CLK_SEL_MASK,
			clk_src << RT5682_FILTER_CLK_SEL_SFT);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_sel_asrc_clk_src);

अटल पूर्णांक rt5682_button_detect(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक btn_type, val;

	val = snd_soc_component_पढ़ो(component, RT5682_4BTN_IL_CMD_1);
	btn_type = val & 0xfff0;
	snd_soc_component_ग_लिखो(component, RT5682_4BTN_IL_CMD_1, val);
	dev_dbg(component->dev, "%s btn_type=%x\n", __func__, btn_type);
	snd_soc_component_update_bits(component,
		RT5682_SAR_IL_CMD_2, 0x10, 0x10);

	वापस btn_type;
पूर्ण

अटल व्योम rt5682_enable_push_button_irq(काष्ठा snd_soc_component *component,
		bool enable)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	अगर (enable) अणु
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_1,
			RT5682_SAR_BUTT_DET_MASK, RT5682_SAR_BUTT_DET_EN);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_13,
			RT5682_SAR_SOUR_MASK, RT5682_SAR_SOUR_BTN);
		snd_soc_component_ग_लिखो(component, RT5682_IL_CMD_1, 0x0040);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_MASK | RT5682_4BTN_IL_RST_MASK,
			RT5682_4BTN_IL_EN | RT5682_4BTN_IL_NOR);
		अगर (rt5682->is_sdw)
			snd_soc_component_update_bits(component,
				RT5682_IRQ_CTRL_3,
				RT5682_IL_IRQ_MASK | RT5682_IL_IRQ_TYPE_MASK,
				RT5682_IL_IRQ_EN | RT5682_IL_IRQ_PUL);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5682_IRQ_CTRL_3, RT5682_IL_IRQ_MASK,
				RT5682_IL_IRQ_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5682_IRQ_CTRL_3,
			RT5682_IL_IRQ_MASK, RT5682_IL_IRQ_DIS);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_1,
			RT5682_SAR_BUTT_DET_MASK, RT5682_SAR_BUTT_DET_DIS);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_MASK, RT5682_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_RST_MASK, RT5682_4BTN_IL_RST);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_13,
			RT5682_SAR_SOUR_MASK, RT5682_SAR_SOUR_TYPE);
	पूर्ण
पूर्ण

/**
 * rt5682_headset_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insert: Jack insert or not.
 *
 * Detect whether is headset or not when jack inserted.
 *
 * Returns detect status.
 */
पूर्णांक rt5682_headset_detect(काष्ठा snd_soc_component *component, पूर्णांक jack_insert)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = &component->dapm;
	अचिन्हित पूर्णांक val, count;

	अगर (jack_insert) अणु
		snd_soc_component_update_bits(component, RT5682_PWR_ANLG_1,
			RT5682_PWR_VREF2 | RT5682_PWR_MB,
			RT5682_PWR_VREF2 | RT5682_PWR_MB);
		snd_soc_component_update_bits(component,
			RT5682_PWR_ANLG_1, RT5682_PWR_FV2, 0);
		usleep_range(15000, 20000);
		snd_soc_component_update_bits(component,
			RT5682_PWR_ANLG_1, RT5682_PWR_FV2, RT5682_PWR_FV2);
		snd_soc_component_update_bits(component, RT5682_PWR_ANLG_3,
			RT5682_PWR_CBJ, RT5682_PWR_CBJ);
		snd_soc_component_update_bits(component,
			RT5682_HP_CHARGE_PUMP_1,
			RT5682_OSW_L_MASK | RT5682_OSW_R_MASK, 0);
		snd_soc_component_update_bits(component, RT5682_CBJ_CTRL_1,
			RT5682_TRIG_JD_MASK, RT5682_TRIG_JD_HIGH);

		count = 0;
		val = snd_soc_component_पढ़ो(component, RT5682_CBJ_CTRL_2)
			& RT5682_JACK_TYPE_MASK;
		जबतक (val == 0 && count < 50) अणु
			usleep_range(10000, 15000);
			val = snd_soc_component_पढ़ो(component,
				RT5682_CBJ_CTRL_2) & RT5682_JACK_TYPE_MASK;
			count++;
		पूर्ण

		चयन (val) अणु
		हाल 0x1:
		हाल 0x2:
			rt5682->jack_type = SND_JACK_HEADSET;
			snd_soc_component_update_bits(component, RT5682_CBJ_CTRL_1,
				RT5682_FAST_OFF_MASK, RT5682_FAST_OFF_EN);
			rt5682_enable_push_button_irq(component, true);
			अवरोध;
		शेष:
			rt5682->jack_type = SND_JACK_HEADPHONE;
			अवरोध;
		पूर्ण

		snd_soc_component_update_bits(component,
			RT5682_HP_CHARGE_PUMP_1,
			RT5682_OSW_L_MASK | RT5682_OSW_R_MASK,
			RT5682_OSW_L_EN | RT5682_OSW_R_EN);
		snd_soc_component_update_bits(component, RT5682_MICBIAS_2,
			RT5682_PWR_CLK25M_MASK | RT5682_PWR_CLK1M_MASK,
			RT5682_PWR_CLK25M_PU | RT5682_PWR_CLK1M_PU);
	पूर्ण अन्यथा अणु
		rt5682_enable_push_button_irq(component, false);
		snd_soc_component_update_bits(component, RT5682_CBJ_CTRL_1,
			RT5682_TRIG_JD_MASK, RT5682_TRIG_JD_LOW);
		अगर (!snd_soc_dapm_get_pin_status(dapm, "MICBIAS"))
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_MB, 0);
		अगर (!snd_soc_dapm_get_pin_status(dapm, "Vref2"))
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_VREF2, 0);
		snd_soc_component_update_bits(component, RT5682_PWR_ANLG_3,
			RT5682_PWR_CBJ, 0);
		snd_soc_component_update_bits(component, RT5682_MICBIAS_2,
			RT5682_PWR_CLK25M_MASK | RT5682_PWR_CLK1M_MASK,
			RT5682_PWR_CLK25M_PD | RT5682_PWR_CLK1M_PD);
		snd_soc_component_update_bits(component, RT5682_CBJ_CTRL_1,
			RT5682_FAST_OFF_MASK, RT5682_FAST_OFF_DIS);

		rt5682->jack_type = 0;
	पूर्ण

	dev_dbg(component->dev, "jack_type = %d\n", rt5682->jack_type);
	वापस rt5682->jack_type;
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_headset_detect);

अटल पूर्णांक rt5682_set_jack_detect(काष्ठा snd_soc_component *component,
		काष्ठा snd_soc_jack *hs_jack, व्योम *data)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	rt5682->hs_jack = hs_jack;

	अगर (!hs_jack) अणु
		regmap_update_bits(rt5682->regmap, RT5682_IRQ_CTRL_2,
			RT5682_JD1_EN_MASK, RT5682_JD1_DIS);
		regmap_update_bits(rt5682->regmap, RT5682_RC_CLK_CTRL,
			RT5682_POW_JDH | RT5682_POW_JDL, 0);
		cancel_delayed_work_sync(&rt5682->jack_detect_work);

		वापस 0;
	पूर्ण

	अगर (!rt5682->is_sdw) अणु
		चयन (rt5682->pdata.jd_src) अणु
		हाल RT5682_JD1:
			snd_soc_component_update_bits(component,
				RT5682_CBJ_CTRL_5, 0x0700, 0x0600);
			snd_soc_component_update_bits(component,
				RT5682_CBJ_CTRL_2, RT5682_EXT_JD_SRC,
				RT5682_EXT_JD_SRC_MANUAL);
			snd_soc_component_ग_लिखो(component, RT5682_CBJ_CTRL_1,
				0xd142);
			snd_soc_component_update_bits(component,
				RT5682_CBJ_CTRL_3, RT5682_CBJ_IN_BUF_EN,
				RT5682_CBJ_IN_BUF_EN);
			snd_soc_component_update_bits(component,
				RT5682_SAR_IL_CMD_1, RT5682_SAR_POW_MASK,
				RT5682_SAR_POW_EN);
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP1_PIN_MASK, RT5682_GP1_PIN_IRQ);
			regmap_update_bits(rt5682->regmap, RT5682_RC_CLK_CTRL,
				RT5682_POW_IRQ | RT5682_POW_JDH |
				RT5682_POW_ANA, RT5682_POW_IRQ |
				RT5682_POW_JDH | RT5682_POW_ANA);
			regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_2,
				RT5682_PWR_JDH, RT5682_PWR_JDH);
			regmap_update_bits(rt5682->regmap, RT5682_IRQ_CTRL_2,
				RT5682_JD1_EN_MASK | RT5682_JD1_POL_MASK,
				RT5682_JD1_EN | RT5682_JD1_POL_NOR);
			regmap_update_bits(rt5682->regmap, RT5682_4BTN_IL_CMD_4,
				0x7f7f, (rt5682->pdata.btndet_delay << 8 |
				rt5682->pdata.btndet_delay));
			regmap_update_bits(rt5682->regmap, RT5682_4BTN_IL_CMD_5,
				0x7f7f, (rt5682->pdata.btndet_delay << 8 |
				rt5682->pdata.btndet_delay));
			regmap_update_bits(rt5682->regmap, RT5682_4BTN_IL_CMD_6,
				0x7f7f, (rt5682->pdata.btndet_delay << 8 |
				rt5682->pdata.btndet_delay));
			regmap_update_bits(rt5682->regmap, RT5682_4BTN_IL_CMD_7,
				0x7f7f, (rt5682->pdata.btndet_delay << 8 |
				rt5682->pdata.btndet_delay));
			mod_delayed_work(प्रणाली_घातer_efficient_wq,
				&rt5682->jack_detect_work,
				msecs_to_jअगरfies(250));
			अवरोध;

		हाल RT5682_JD_शून्य:
			regmap_update_bits(rt5682->regmap, RT5682_IRQ_CTRL_2,
				RT5682_JD1_EN_MASK, RT5682_JD1_DIS);
			regmap_update_bits(rt5682->regmap, RT5682_RC_CLK_CTRL,
				RT5682_POW_JDH | RT5682_POW_JDL, 0);
			अवरोध;

		शेष:
			dev_warn(component->dev, "Wrong JD source\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम rt5682_jack_detect_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(work, काष्ठा rt5682_priv, jack_detect_work.work);
	पूर्णांक val, btn_type;

	जबतक (!rt5682->component)
		usleep_range(10000, 15000);

	जबतक (!rt5682->component->card->instantiated)
		usleep_range(10000, 15000);

	mutex_lock(&rt5682->calibrate_mutex);

	val = snd_soc_component_पढ़ो(rt5682->component, RT5682_AJD1_CTRL)
		& RT5682_JDH_RS_MASK;
	अगर (!val) अणु
		/* jack in */
		अगर (rt5682->jack_type == 0) अणु
			/* jack was out, report jack type */
			rt5682->jack_type =
				rt5682_headset_detect(rt5682->component, 1);
			rt5682->irq_work_delay_समय = 0;
		पूर्ण अन्यथा अगर ((rt5682->jack_type & SND_JACK_HEADSET) ==
			SND_JACK_HEADSET) अणु
			/* jack is alपढ़ोy in, report button event */
			rt5682->jack_type = SND_JACK_HEADSET;
			btn_type = rt5682_button_detect(rt5682->component);
			/**
			 * rt5682 can report three kinds of button behavior,
			 * one click, द्विगुन click and hold. However,
			 * currently we will report button pressed/released
			 * event. So all the three button behaviors are
			 * treated as button pressed.
			 */
			चयन (btn_type) अणु
			हाल 0x8000:
			हाल 0x4000:
			हाल 0x2000:
				rt5682->jack_type |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x1000:
			हाल 0x0800:
			हाल 0x0400:
				rt5682->jack_type |= SND_JACK_BTN_1;
				अवरोध;
			हाल 0x0200:
			हाल 0x0100:
			हाल 0x0080:
				rt5682->jack_type |= SND_JACK_BTN_2;
				अवरोध;
			हाल 0x0040:
			हाल 0x0020:
			हाल 0x0010:
				rt5682->jack_type |= SND_JACK_BTN_3;
				अवरोध;
			हाल 0x0000: /* unpressed */
				अवरोध;
			शेष:
				dev_err(rt5682->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* jack out */
		rt5682->jack_type = rt5682_headset_detect(rt5682->component, 0);
		rt5682->irq_work_delay_समय = 50;
	पूर्ण

	snd_soc_jack_report(rt5682->hs_jack, rt5682->jack_type,
		SND_JACK_HEADSET |
		SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (!rt5682->is_sdw) अणु
		अगर (rt5682->jack_type & (SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3))
			schedule_delayed_work(&rt5682->jd_check_work, 0);
		अन्यथा
			cancel_delayed_work_sync(&rt5682->jd_check_work);
	पूर्ण

	mutex_unlock(&rt5682->calibrate_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_jack_detect_handler);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_snd_controls[] = अणु
	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5682_DAC1_DIG_VOL,
		RT5682_L_VOL_SFT + 1, RT5682_R_VOL_SFT + 1, 87, 0, dac_vol_tlv),

	/* IN Boost Volume */
	SOC_SINGLE_TLV("CBJ Boost Volume", RT5682_CBJ_BST_CTRL,
		RT5682_BST_CBJ_SFT, 8, 0, bst_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("STO1 ADC Capture Switch", RT5682_STO1_ADC_DIG_VOL,
		RT5682_L_MUTE_SFT, RT5682_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("STO1 ADC Capture Volume", RT5682_STO1_ADC_DIG_VOL,
		RT5682_L_VOL_SFT + 1, RT5682_R_VOL_SFT + 1, 63, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Gain Volume", RT5682_STO1_ADC_BOOST,
		RT5682_STO1_ADC_L_BST_SFT, RT5682_STO1_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),
पूर्ण;

अटल पूर्णांक rt5682_भाग_sel(काष्ठा rt5682_priv *rt5682,
		पूर्णांक target, स्थिर पूर्णांक भाग[], पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (rt5682->sysclk < target) अणु
		dev_err(rt5682->component->dev,
			"sysclk rate %d is too low\n", rt5682->sysclk);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < size - 1; i++) अणु
		dev_dbg(rt5682->component->dev, "div[%d]=%d\n", i, भाग[i]);
		अगर (target * भाग[i] == rt5682->sysclk)
			वापस i;
		अगर (target * भाग[i + 1] > rt5682->sysclk) अणु
			dev_dbg(rt5682->component->dev,
				"can't find div for sysclk %d\n",
				rt5682->sysclk);
			वापस i;
		पूर्ण
	पूर्ण

	अगर (target * भाग[i] < rt5682->sysclk)
		dev_err(rt5682->component->dev,
			"sysclk rate %d is too high\n", rt5682->sysclk);

	वापस size - 1;
पूर्ण

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
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, dmic_clk_rate = 3072000;
	अटल स्थिर पूर्णांक भाग[] = अणु2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128पूर्ण;

	अगर (rt5682->pdata.dmic_clk_rate)
		dmic_clk_rate = rt5682->pdata.dmic_clk_rate;

	idx = rt5682_भाग_sel(rt5682, dmic_clk_rate, भाग, ARRAY_SIZE(भाग));

	snd_soc_component_update_bits(component, RT5682_DMIC_CTRL_1,
		RT5682_DMIC_CLK_MASK, idx << RT5682_DMIC_CLK_SFT);

	वापस 0;
पूर्ण

अटल पूर्णांक set_filter_clk(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	पूर्णांक ref, val, reg, idx;
	अटल स्थिर पूर्णांक भाग_f[] = अणु1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48पूर्ण;
	अटल स्थिर पूर्णांक भाग_o[] = अणु1, 2, 4, 6, 8, 12, 16, 24, 32, 48पूर्ण;

	अगर (rt5682->is_sdw)
		वापस 0;

	val = snd_soc_component_पढ़ो(component, RT5682_GPIO_CTRL_1) &
		RT5682_GP4_PIN_MASK;
	अगर (w->shअगरt == RT5682_PWR_ADC_S1F_BIT &&
		val == RT5682_GP4_PIN_ADCDAT2)
		ref = 256 * rt5682->lrck[RT5682_AIF2];
	अन्यथा
		ref = 256 * rt5682->lrck[RT5682_AIF1];

	idx = rt5682_भाग_sel(rt5682, ref, भाग_f, ARRAY_SIZE(भाग_f));

	अगर (w->shअगरt == RT5682_PWR_ADC_S1F_BIT)
		reg = RT5682_PLL_TRACK_3;
	अन्यथा
		reg = RT5682_PLL_TRACK_2;

	snd_soc_component_update_bits(component, reg,
		RT5682_FILTER_CLK_DIV_MASK, idx << RT5682_FILTER_CLK_DIV_SFT);

	/* select over sample rate */
	क्रम (idx = 0; idx < ARRAY_SIZE(भाग_o); idx++) अणु
		अगर (rt5682->sysclk <= 12288000 * भाग_o[idx])
			अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, RT5682_ADDA_CLK_1,
		RT5682_ADC_OSR_MASK | RT5682_DAC_OSR_MASK,
		(idx << RT5682_ADC_OSR_SFT) | (idx << RT5682_DAC_OSR_SFT));

	वापस 0;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll1(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	val = snd_soc_component_पढ़ो(component, RT5682_GLB_CLK);
	val &= RT5682_SCLK_SRC_MASK;
	अगर (val == RT5682_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll2(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	val = snd_soc_component_पढ़ो(component, RT5682_GLB_CLK);
	val &= RT5682_SCLK_SRC_MASK;
	अगर (val == RT5682_SCLK_SRC_PLL2)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक reg, shअगरt, val;
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (w->shअगरt) अणु
	हाल RT5682_ADC_STO1_ASRC_SFT:
		reg = RT5682_PLL_TRACK_3;
		shअगरt = RT5682_FILTER_CLK_SEL_SFT;
		अवरोध;
	हाल RT5682_DAC_STO1_ASRC_SFT:
		reg = RT5682_PLL_TRACK_2;
		shअगरt = RT5682_FILTER_CLK_SEL_SFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	val = (snd_soc_component_पढ़ो(component, reg) >> shअगरt) & 0xf;
	चयन (val) अणु
	हाल RT5682_CLK_SEL_I2S1_ASRC:
	हाल RT5682_CLK_SEL_I2S2_ASRC:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5682_STO1_ADC_MIXER,
			RT5682_M_STO1_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5682_STO1_ADC_MIXER,
			RT5682_M_STO1_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5682_STO1_ADC_MIXER,
			RT5682_M_STO1_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5682_STO1_ADC_MIXER,
			RT5682_M_STO1_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5682_AD_DA_MIXER,
			RT5682_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5682_AD_DA_MIXER,
			RT5682_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5682_AD_DA_MIXER,
			RT5682_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5682_AD_DA_MIXER,
			RT5682_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5682_STO1_DAC_MIXER,
			RT5682_M_DAC_L1_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5682_STO1_DAC_MIXER,
			RT5682_M_DAC_R1_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5682_STO1_DAC_MIXER,
			RT5682_M_DAC_L1_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5682_STO1_DAC_MIXER,
			RT5682_M_DAC_R1_STO_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5682_rec1_l_mix[] = अणु
	SOC_DAPM_SINGLE("CBJ Switch", RT5682_REC_MIXER,
			RT5682_M_CBJ_RM1_L_SFT, 1, 1),
पूर्ण;

/* STO1 ADC1 Source */
/* MX-26 [13] [5] */
अटल स्थिर अक्षर * स्थिर rt5682_sto1_adc1_src[] = अणु
	"DAC MIX", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adc1l_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADC1L_SRC_SFT, rt5682_sto1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc1l_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1L Source", rt5682_sto1_adc1l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adc1r_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADC1R_SRC_SFT, rt5682_sto1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc1r_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1L Source", rt5682_sto1_adc1r_क्रमागत);

/* STO1 ADC Source */
/* MX-26 [11:10] [3:2] */
अटल स्थिर अक्षर * स्थिर rt5682_sto1_adc_src[] = अणु
	"ADC1 L", "ADC1 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adcl_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADCL_SRC_SFT, rt5682_sto1_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adcl_mux =
	SOC_DAPM_ENUM("Stereo1 ADCL Source", rt5682_sto1_adcl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adcr_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADCR_SRC_SFT, rt5682_sto1_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adcr_mux =
	SOC_DAPM_ENUM("Stereo1 ADCR Source", rt5682_sto1_adcr_क्रमागत);

/* STO1 ADC2 Source */
/* MX-26 [12] [4] */
अटल स्थिर अक्षर * स्थिर rt5682_sto1_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adc2l_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADC2L_SRC_SFT, rt5682_sto1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc2l_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2L Source", rt5682_sto1_adc2l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_sto1_adc2r_क्रमागत, RT5682_STO1_ADC_MIXER,
	RT5682_STO1_ADC2R_SRC_SFT, rt5682_sto1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_sto1_adc2r_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2R Source", rt5682_sto1_adc2r_क्रमागत);

/* MX-79 [6:4] I2S1 ADC data location */
अटल स्थिर अचिन्हित पूर्णांक rt5682_अगर1_adc_slot_values[] = अणु
	0,
	2,
	4,
	6,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rt5682_अगर1_adc_slot_src[] = अणु
	"Slot 0", "Slot 2", "Slot 4", "Slot 6"
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt5682_अगर1_adc_slot_क्रमागत,
	RT5682_TDM_CTRL, RT5682_TDM_ADC_LCA_SFT, RT5682_TDM_ADC_LCA_MASK,
	rt5682_अगर1_adc_slot_src, rt5682_अगर1_adc_slot_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_अगर1_adc_slot_mux =
	SOC_DAPM_ENUM("IF1 ADC Slot location", rt5682_अगर1_adc_slot_क्रमागत);

/* Analog DAC L1 Source, Analog DAC R1 Source*/
/* MX-2B [4], MX-2B [0]*/
अटल स्थिर अक्षर * स्थिर rt5682_alg_dac1_src[] = अणु
	"Stereo1 DAC Mixer", "DAC1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_alg_dac_l1_क्रमागत, RT5682_A_DAC1_MUX,
	RT5682_A_DACL1_SFT, rt5682_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_alg_dac_l1_mux =
	SOC_DAPM_ENUM("Analog DAC L1 Source", rt5682_alg_dac_l1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5682_alg_dac_r1_क्रमागत, RT5682_A_DAC1_MUX,
	RT5682_A_DACR1_SFT, rt5682_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_alg_dac_r1_mux =
	SOC_DAPM_ENUM("Analog DAC R1 Source", rt5682_alg_dac_r1_क्रमागत);

/* Out Switch */
अटल स्थिर काष्ठा snd_kcontrol_new hpol_चयन =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5682_HP_CTRL_1,
		RT5682_L_MUTE_SFT, 1, 1);
अटल स्थिर काष्ठा snd_kcontrol_new hpor_चयन =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5682_HP_CTRL_1,
		RT5682_R_MUTE_SFT, 1, 1);

अटल पूर्णांक rt5682_hp_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_ग_लिखो(component,
			RT5682_HP_LOGIC_CTRL_2, 0x0012);
		snd_soc_component_ग_लिखो(component,
			RT5682_HP_CTRL_2, 0x6000);
		snd_soc_component_update_bits(component,
			RT5682_DEPOP_1, 0x60, 0x60);
		snd_soc_component_update_bits(component,
			RT5682_DAC_ADC_DIG_VOL1, 0x00c0, 0x0080);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component,
			RT5682_DEPOP_1, 0x60, 0x0);
		snd_soc_component_ग_लिखो(component,
			RT5682_HP_CTRL_2, 0x0000);
		snd_soc_component_update_bits(component,
			RT5682_DAC_ADC_DIG_VOL1, 0x00c0, 0x0000);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_dmic_घातer(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक delay = 50, val;

	अगर (rt5682->pdata.dmic_delay)
		delay = rt5682->pdata.dmic_delay;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_पढ़ो(component, RT5682_GLB_CLK);
		val &= RT5682_SCLK_SRC_MASK;
		अगर (val == RT5682_SCLK_SRC_PLL1 || val == RT5682_SCLK_SRC_PLL2)
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1,
				RT5682_PWR_VREF2 | RT5682_PWR_MB,
				RT5682_PWR_VREF2 | RT5682_PWR_MB);

		/*Add delay to aव्योम pop noise*/
		msleep(delay);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		अगर (!rt5682->jack_type) अणु
			अगर (!snd_soc_dapm_get_pin_status(w->dapm, "MICBIAS"))
				snd_soc_component_update_bits(component,
					RT5682_PWR_ANLG_1, RT5682_PWR_MB, 0);
			अगर (!snd_soc_dapm_get_pin_status(w->dapm, "Vref2"))
				snd_soc_component_update_bits(component,
					RT5682_PWR_ANLG_1, RT5682_PWR_VREF2, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_verf(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (w->shअगरt) अणु
		हाल RT5682_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV1, 0);
			अवरोध;

		हाल RT5682_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV2, 0);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(15000, 20000);
		चयन (w->shअगरt) अणु
		हाल RT5682_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV1,
				RT5682_PWR_FV1);
			अवरोध;

		हाल RT5682_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV2,
				RT5682_PWR_FV2);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rt5682_adcdat_pin_values[] = अणु
	1,
	3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rt5682_adcdat_pin_select[] = अणु
	"ADCDAT1",
	"ADCDAT2",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt5682_adcdat_pin_क्रमागत,
	RT5682_GPIO_CTRL_1, RT5682_GP4_PIN_SFT, RT5682_GP4_PIN_MASK,
	rt5682_adcdat_pin_select, rt5682_adcdat_pin_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt5682_adcdat_pin_ctrl =
	SOC_DAPM_ENUM("ADCDAT", rt5682_adcdat_pin_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5682_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT5682_PWR_ANLG_3, RT5682_PWR_LDO2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT5682_PWR_ANLG_3, RT5682_PWR_PLL_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2B", RT5682_PWR_ANLG_3, RT5682_PWR_PLL2B_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2F", RT5682_PWR_ANLG_3, RT5682_PWR_PLL2F_BIT,
		0, set_filter_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("Vref1", RT5682_PWR_ANLG_1, RT5682_PWR_VREF1_BIT, 0,
		rt5682_set_verf, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("Vref2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("DAC STO1 ASRC", 1, RT5682_PLL_TRACK_1,
		RT5682_DAC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5682_PLL_TRACK_1,
		RT5682_ADC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AD ASRC", 1, RT5682_PLL_TRACK_1,
		RT5682_AD_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DA ASRC", 1, RT5682_PLL_TRACK_1,
		RT5682_DA_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC ASRC", 1, RT5682_PLL_TRACK_1,
		RT5682_DMIC_ASRC_SFT, 0, शून्य, 0),

	/* Input Side */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5682_PWR_ANLG_2, RT5682_PWR_MB1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS2", RT5682_PWR_ANLG_2, RT5682_PWR_MB2_BIT,
		0, शून्य, 0),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),

	SND_SOC_DAPM_INPUT("IN1P"),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5682_DMIC_CTRL_1,
		RT5682_DMIC_1_EN_SFT, 0, set_dmic_घातer,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1 CBJ", SND_SOC_NOPM,
		0, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIX1L", SND_SOC_NOPM, 0, 0, rt5682_rec1_l_mix,
		ARRAY_SIZE(rt5682_rec1_l_mix)),
	SND_SOC_DAPM_SUPPLY("RECMIX1L Power", RT5682_PWR_ANLG_2,
		RT5682_PWR_RM1_L_BIT, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1 L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC1 R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("ADC1 L Power", RT5682_PWR_DIG_1,
		RT5682_PWR_ADC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 R Power", RT5682_PWR_DIG_1,
		RT5682_PWR_ADC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 clock", RT5682_CHOP_ADC,
		RT5682_CKGEN_ADC1_SFT, 0, शून्य, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adc1l_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adc1r_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adc2l_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adc2r_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adcl_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_sto1_adcr_mux),
	SND_SOC_DAPM_MUX("IF1_ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर1_adc_slot_mux),

	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("ADC Stereo1 Filter", RT5682_PWR_DIG_2,
		RT5682_PWR_ADC_S1F_BIT, 0, set_filter_clk,
		SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", RT5682_STO1_ADC_DIG_VOL,
		RT5682_L_MUTE_SFT, 1, rt5682_sto1_adc_l_mix,
		ARRAY_SIZE(rt5682_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", RT5682_STO1_ADC_DIG_VOL,
		RT5682_R_MUTE_SFT, 1, rt5682_sto1_adc_r_mix,
		ARRAY_SIZE(rt5682_sto1_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("BTN Detection Mode", RT5682_SAR_IL_CMD_1,
		14, 1, शून्य, 0),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5682_PWR_DIG_1, RT5682_PWR_I2S1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5682_PWR_DIG_1, RT5682_PWR_I2S2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SOUND DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SOUND DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("IF1 01 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर1_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 23 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर1_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 45 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर1_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 67 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर1_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF2 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_अगर2_adc_swap_mux),

	SND_SOC_DAPM_MUX("ADCDAT Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_adcdat_pin_ctrl),

	SND_SOC_DAPM_MUX("DAC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_dac_l_mux),
	SND_SOC_DAPM_MUX("DAC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5682_dac_r_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0,
		RT5682_I2S1_SDP, RT5682_SEL_ADCDAT_SFT, 1),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0,
		RT5682_I2S2_SDP, RT5682_I2S2_PIN_CFG_SFT, 1),
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDWRX", "SDW Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SDWTX", "SDW Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5682_dac_l_mix, ARRAY_SIZE(rt5682_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5682_dac_r_mix, ARRAY_SIZE(rt5682_dac_r_mix)),

	/* DAC channel Mux */
	SND_SOC_DAPM_MUX("DAC L1 Source", SND_SOC_NOPM, 0, 0,
		&rt5682_alg_dac_l1_mux),
	SND_SOC_DAPM_MUX("DAC R1 Source", SND_SOC_NOPM, 0, 0,
		&rt5682_alg_dac_r1_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("DAC Stereo1 Filter", RT5682_PWR_DIG_2,
		RT5682_PWR_DAC_S1F_BIT, 0, set_filter_clk,
		SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MIXER("Stereo1 DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5682_sto1_dac_l_mix, ARRAY_SIZE(rt5682_sto1_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5682_sto1_dac_r_mix, ARRAY_SIZE(rt5682_sto1_dac_r_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, RT5682_PWR_DIG_1,
		RT5682_PWR_DAC_L1_BIT, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, RT5682_PWR_DIG_1,
		RT5682_PWR_DAC_R1_BIT, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC 1 Clock", 3, RT5682_CHOP_DAC,
		RT5682_CKGEN_DAC1_SFT, 0, शून्य, 0),

	/* HPO */
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, rt5682_hp_event,
		SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_SUPPLY("HP Amp L", RT5682_PWR_ANLG_1,
		RT5682_PWR_HA_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HP Amp R", RT5682_PWR_ANLG_1,
		RT5682_PWR_HA_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("Charge Pump", 1, RT5682_DEPOP_1,
		RT5682_PUMP_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("Capless", 2, RT5682_DEPOP_1,
		RT5682_CAPLESS_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("HPOL Playback", SND_SOC_NOPM, 0, 0,
		&hpol_चयन),
	SND_SOC_DAPM_SWITCH("HPOR Playback", SND_SOC_NOPM, 0, 0,
		&hpor_चयन),

	/* CLK DET */
	SND_SOC_DAPM_SUPPLY("CLKDET SYS", RT5682_CLK_DET,
		RT5682_SYS_CLK_DET_SFT,	0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET PLL1", RT5682_CLK_DET,
		RT5682_PLL1_CLK_DET_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET PLL2", RT5682_CLK_DET,
		RT5682_PLL2_CLK_DET_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET", RT5682_CLK_DET,
		RT5682_POW_CLK_DET_SFT, 0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5682_dapm_routes[] = अणु
	/*PLL*/
	अणु"ADC Stereo1 Filter", शून्य, "PLL1", is_sys_clk_from_pll1पूर्ण,
	अणु"ADC Stereo1 Filter", शून्य, "PLL2B", is_sys_clk_from_pll2पूर्ण,
	अणु"ADC Stereo1 Filter", शून्य, "PLL2F", is_sys_clk_from_pll2पूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "PLL1", is_sys_clk_from_pll1पूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "PLL2B", is_sys_clk_from_pll2पूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "PLL2F", is_sys_clk_from_pll2पूर्ण,

	/*ASRC*/
	अणु"ADC Stereo1 Filter", शून्य, "ADC STO1 ASRC", is_using_asrcपूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "DAC STO1 ASRC", is_using_asrcपूर्ण,
	अणु"ADC STO1 ASRC", शून्य, "AD ASRC"पूर्ण,
	अणु"ADC STO1 ASRC", शून्य, "DA ASRC"पूर्ण,
	अणु"ADC STO1 ASRC", शून्य, "CLKDET"पूर्ण,
	अणु"DAC STO1 ASRC", शून्य, "AD ASRC"पूर्ण,
	अणु"DAC STO1 ASRC", शून्य, "DA ASRC"पूर्ण,
	अणु"DAC STO1 ASRC", शून्य, "CLKDET"पूर्ण,

	/*Vref*/
	अणु"MICBIAS1", शून्य, "Vref1"पूर्ण,
	अणु"MICBIAS2", शून्य, "Vref1"पूर्ण,

	अणु"CLKDET SYS", शून्य, "CLKDET"पूर्ण,

	अणु"BST1 CBJ", शून्य, "IN1P"पूर्ण,

	अणु"RECMIX1L", "CBJ Switch", "BST1 CBJ"पूर्ण,
	अणु"RECMIX1L", शून्य, "RECMIX1L Power"पूर्ण,

	अणु"ADC1 L", शून्य, "RECMIX1L"पूर्ण,
	अणु"ADC1 L", शून्य, "ADC1 L Power"पूर्ण,
	अणु"ADC1 L", शून्य, "ADC1 clock"पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC CLK", शून्य, "DMIC ASRC"पूर्ण,

	अणु"Stereo1 ADC L Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo1 ADC L Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC1 R", "ADC1 R"पूर्ण,

	अणु"Stereo1 ADC L1 Mux", "ADC", "Stereo1 ADC L Mux"पूर्ण,
	अणु"Stereo1 ADC L1 Mux", "DAC MIX", "Stereo1 DAC MIXL"पूर्ण,
	अणु"Stereo1 ADC L2 Mux", "DMIC", "DMIC L1"पूर्ण,
	अणु"Stereo1 ADC L2 Mux", "DAC MIX", "Stereo1 DAC MIXL"पूर्ण,

	अणु"Stereo1 ADC R1 Mux", "ADC", "Stereo1 ADC R Mux"पूर्ण,
	अणु"Stereo1 ADC R1 Mux", "DAC MIX", "Stereo1 DAC MIXR"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DMIC", "DMIC R1"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DAC MIX", "Stereo1 DAC MIXR"पूर्ण,

	अणु"Stereo1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", शून्य, "ADC Stereo1 Filter"पूर्ण,

	अणु"Stereo1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", शून्य, "ADC Stereo1 Filter"पूर्ण,

	अणु"ADC Stereo1 Filter", शून्य, "BTN Detection Mode"पूर्ण,

	अणु"Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXL"पूर्ण,
	अणु"Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXR"पूर्ण,

	अणु"IF1 01 ADC Swap Mux", "L/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 01 ADC Swap Mux", "L/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 01 ADC Swap Mux", "R/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 01 ADC Swap Mux", "R/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 23 ADC Swap Mux", "L/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 23 ADC Swap Mux", "R/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 23 ADC Swap Mux", "L/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 23 ADC Swap Mux", "R/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 45 ADC Swap Mux", "L/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 45 ADC Swap Mux", "R/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 45 ADC Swap Mux", "L/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 45 ADC Swap Mux", "R/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 67 ADC Swap Mux", "L/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 67 ADC Swap Mux", "R/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 67 ADC Swap Mux", "L/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1 67 ADC Swap Mux", "R/R", "Stereo1 ADC MIX"पूर्ण,

	अणु"IF1_ADC Mux", "Slot 0", "IF1 01 ADC Swap Mux"पूर्ण,
	अणु"IF1_ADC Mux", "Slot 2", "IF1 23 ADC Swap Mux"पूर्ण,
	अणु"IF1_ADC Mux", "Slot 4", "IF1 45 ADC Swap Mux"पूर्ण,
	अणु"IF1_ADC Mux", "Slot 6", "IF1 67 ADC Swap Mux"पूर्ण,
	अणु"ADCDAT Mux", "ADCDAT1", "IF1_ADC Mux"पूर्ण,
	अणु"AIF1TX", शून्य, "I2S1"पूर्ण,
	अणु"AIF1TX", शून्य, "ADCDAT Mux"पूर्ण,
	अणु"IF2 ADC Swap Mux", "L/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF2 ADC Swap Mux", "R/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF2 ADC Swap Mux", "L/L", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF2 ADC Swap Mux", "R/R", "Stereo1 ADC MIX"पूर्ण,
	अणु"ADCDAT Mux", "ADCDAT2", "IF2 ADC Swap Mux"पूर्ण,
	अणु"AIF2TX", शून्य, "ADCDAT Mux"पूर्ण,

	अणु"SDWTX", शून्य, "PLL2B"पूर्ण,
	अणु"SDWTX", शून्य, "PLL2F"पूर्ण,
	अणु"SDWTX", शून्य, "ADCDAT Mux"पूर्ण,

	अणु"IF1 DAC1 L", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC1 L", शून्य, "I2S1"पूर्ण,
	अणु"IF1 DAC1 L", शून्य, "DAC Stereo1 Filter"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "I2S1"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "DAC Stereo1 Filter"पूर्ण,

	अणु"SOUND DAC L", शून्य, "SDWRX"पूर्ण,
	अणु"SOUND DAC L", शून्य, "DAC Stereo1 Filter"पूर्ण,
	अणु"SOUND DAC L", शून्य, "PLL2B"पूर्ण,
	अणु"SOUND DAC L", शून्य, "PLL2F"पूर्ण,
	अणु"SOUND DAC R", शून्य, "SDWRX"पूर्ण,
	अणु"SOUND DAC R", शून्य, "DAC Stereo1 Filter"पूर्ण,
	अणु"SOUND DAC R", शून्य, "PLL2B"पूर्ण,
	अणु"SOUND DAC R", शून्य, "PLL2F"पूर्ण,

	अणु"DAC L Mux", "IF1", "IF1 DAC1 L"पूर्ण,
	अणु"DAC L Mux", "SOUND", "SOUND DAC L"पूर्ण,
	अणु"DAC R Mux", "IF1", "IF1 DAC1 R"पूर्ण,
	अणु"DAC R Mux", "SOUND", "SOUND DAC R"पूर्ण,

	अणु"DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL"पूर्ण,
	अणु"DAC1 MIXL", "DAC1 Switch", "DAC L Mux"पूर्ण,
	अणु"DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR"पूर्ण,
	अणु"DAC1 MIXR", "DAC1 Switch", "DAC R Mux"पूर्ण,

	अणु"Stereo1 DAC MIXL", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Stereo1 DAC MIXL", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,

	अणु"Stereo1 DAC MIXR", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Stereo1 DAC MIXR", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,

	अणु"DAC L1 Source", "DAC1", "DAC1 MIXL"पूर्ण,
	अणु"DAC L1 Source", "Stereo1 DAC Mixer", "Stereo1 DAC MIXL"पूर्ण,
	अणु"DAC R1 Source", "DAC1", "DAC1 MIXR"पूर्ण,
	अणु"DAC R1 Source", "Stereo1 DAC Mixer", "Stereo1 DAC MIXR"पूर्ण,

	अणु"DAC L1", शून्य, "DAC L1 Source"पूर्ण,
	अणु"DAC R1", शून्य, "DAC R1 Source"पूर्ण,

	अणु"DAC L1", शून्य, "DAC 1 Clock"पूर्ण,
	अणु"DAC R1", शून्य, "DAC 1 Clock"पूर्ण,

	अणु"HP Amp", शून्य, "DAC L1"पूर्ण,
	अणु"HP Amp", शून्य, "DAC R1"पूर्ण,
	अणु"HP Amp", शून्य, "HP Amp L"पूर्ण,
	अणु"HP Amp", शून्य, "HP Amp R"पूर्ण,
	अणु"HP Amp", शून्य, "Capless"पूर्ण,
	अणु"HP Amp", शून्य, "Charge Pump"पूर्ण,
	अणु"HP Amp", शून्य, "CLKDET SYS"पूर्ण,
	अणु"HP Amp", शून्य, "Vref1"पूर्ण,
	अणु"HPOL Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPOR Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPOL", शून्य, "HPOL Playback"पूर्ण,
	अणु"HPOR", शून्य, "HPOR Playback"पूर्ण,
पूर्ण;

अटल पूर्णांक rt5682_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
		अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक cl, val = 0;

	अगर (tx_mask || rx_mask)
		snd_soc_component_update_bits(component, RT5682_TDM_ADDA_CTRL_2,
			RT5682_TDM_EN, RT5682_TDM_EN);
	अन्यथा
		snd_soc_component_update_bits(component, RT5682_TDM_ADDA_CTRL_2,
			RT5682_TDM_EN, 0);

	चयन (slots) अणु
	हाल 4:
		val |= RT5682_TDM_TX_CH_4;
		val |= RT5682_TDM_RX_CH_4;
		अवरोध;
	हाल 6:
		val |= RT5682_TDM_TX_CH_6;
		val |= RT5682_TDM_RX_CH_6;
		अवरोध;
	हाल 8:
		val |= RT5682_TDM_TX_CH_8;
		val |= RT5682_TDM_RX_CH_8;
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5682_TDM_CTRL,
		RT5682_TDM_TX_CH_MASK | RT5682_TDM_RX_CH_MASK, val);

	चयन (slot_width) अणु
	हाल 8:
		अगर (tx_mask || rx_mask)
			वापस -EINVAL;
		cl = RT5682_I2S1_TX_CHL_8 | RT5682_I2S1_RX_CHL_8;
		अवरोध;
	हाल 16:
		val = RT5682_TDM_CL_16;
		cl = RT5682_I2S1_TX_CHL_16 | RT5682_I2S1_RX_CHL_16;
		अवरोध;
	हाल 20:
		val = RT5682_TDM_CL_20;
		cl = RT5682_I2S1_TX_CHL_20 | RT5682_I2S1_RX_CHL_20;
		अवरोध;
	हाल 24:
		val = RT5682_TDM_CL_24;
		cl = RT5682_I2S1_TX_CHL_24 | RT5682_I2S1_RX_CHL_24;
		अवरोध;
	हाल 32:
		val = RT5682_TDM_CL_32;
		cl = RT5682_I2S1_TX_CHL_32 | RT5682_I2S1_RX_CHL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
		RT5682_TDM_CL_MASK, val);
	snd_soc_component_update_bits(component, RT5682_I2S1_SDP,
		RT5682_I2S1_TX_CHL_MASK | RT5682_I2S1_RX_CHL_MASK, cl);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक len_1 = 0, len_2 = 0;
	पूर्णांक pre_भाग, frame_size;

	rt5682->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5682->sysclk, rt5682->lrck[dai->id]);

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
		rt5682->lrck[dai->id], pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		len_1 |= RT5682_I2S1_DL_20;
		len_2 |= RT5682_I2S2_DL_20;
		अवरोध;
	हाल 24:
		len_1 |= RT5682_I2S1_DL_24;
		len_2 |= RT5682_I2S2_DL_24;
		अवरोध;
	हाल 32:
		len_1 |= RT5682_I2S1_DL_32;
		len_2 |= RT5682_I2S2_DL_24;
		अवरोध;
	हाल 8:
		len_1 |= RT5682_I2S2_DL_8;
		len_2 |= RT5682_I2S2_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5682_AIF1:
		snd_soc_component_update_bits(component, RT5682_I2S1_SDP,
			RT5682_I2S1_DL_MASK, len_1);
		अगर (rt5682->master[RT5682_AIF1]) अणु
			snd_soc_component_update_bits(component,
				RT5682_ADDA_CLK_1, RT5682_I2S_M_DIV_MASK |
				RT5682_I2S_CLK_SRC_MASK,
				pre_भाग << RT5682_I2S_M_DIV_SFT |
				(rt5682->sysclk_src) << RT5682_I2S_CLK_SRC_SFT);
		पूर्ण
		अगर (params_channels(params) == 1) /* mono mode */
			snd_soc_component_update_bits(component,
				RT5682_I2S1_SDP, RT5682_I2S1_MONO_MASK,
				RT5682_I2S1_MONO_EN);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5682_I2S1_SDP, RT5682_I2S1_MONO_MASK,
				RT5682_I2S1_MONO_DIS);
		अवरोध;
	हाल RT5682_AIF2:
		snd_soc_component_update_bits(component, RT5682_I2S2_SDP,
			RT5682_I2S2_DL_MASK, len_2);
		अगर (rt5682->master[RT5682_AIF2]) अणु
			snd_soc_component_update_bits(component,
				RT5682_I2S_M_CLK_CTRL_1, RT5682_I2S2_M_PD_MASK,
				pre_भाग << RT5682_I2S2_M_PD_SFT);
		पूर्ण
		अगर (params_channels(params) == 1) /* mono mode */
			snd_soc_component_update_bits(component,
				RT5682_I2S2_SDP, RT5682_I2S2_MONO_MASK,
				RT5682_I2S2_MONO_EN);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5682_I2S2_SDP, RT5682_I2S2_MONO_MASK,
				RT5682_I2S2_MONO_DIS);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, tdm_ctrl = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5682->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		rt5682->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5682_I2S_BP_INV;
		tdm_ctrl |= RT5682_TDM_S_BP_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगर (dai->id == RT5682_AIF1)
			tdm_ctrl |= RT5682_TDM_S_LP_INV | RT5682_TDM_M_BP_INV;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगर (dai->id == RT5682_AIF1)
			tdm_ctrl |= RT5682_TDM_S_BP_INV | RT5682_TDM_S_LP_INV |
				    RT5682_TDM_M_BP_INV | RT5682_TDM_M_LP_INV;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5682_I2S_DF_LEFT;
		tdm_ctrl |= RT5682_TDM_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5682_I2S_DF_PCM_A;
		tdm_ctrl |= RT5682_TDM_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5682_I2S_DF_PCM_B;
		tdm_ctrl |= RT5682_TDM_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5682_AIF1:
		snd_soc_component_update_bits(component, RT5682_I2S1_SDP,
			RT5682_I2S_DF_MASK, reg_val);
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_MS_MASK | RT5682_TDM_S_BP_MASK |
			RT5682_TDM_DF_MASK | RT5682_TDM_M_BP_MASK |
			RT5682_TDM_M_LP_MASK | RT5682_TDM_S_LP_MASK,
			tdm_ctrl | rt5682->master[dai->id]);
		अवरोध;
	हाल RT5682_AIF2:
		अगर (rt5682->master[dai->id] == 0)
			reg_val |= RT5682_I2S2_MS_S;
		snd_soc_component_update_bits(component, RT5682_I2S2_SDP,
			RT5682_I2S2_MS_MASK | RT5682_I2S_BP_MASK |
			RT5682_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, src = 0;

	अगर (freq == rt5682->sysclk && clk_id == rt5682->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5682_SCLK_S_MCLK:
		reg_val |= RT5682_SCLK_SRC_MCLK;
		src = RT5682_CLK_SRC_MCLK;
		अवरोध;
	हाल RT5682_SCLK_S_PLL1:
		reg_val |= RT5682_SCLK_SRC_PLL1;
		src = RT5682_CLK_SRC_PLL1;
		अवरोध;
	हाल RT5682_SCLK_S_PLL2:
		reg_val |= RT5682_SCLK_SRC_PLL2;
		src = RT5682_CLK_SRC_PLL2;
		अवरोध;
	हाल RT5682_SCLK_S_RCCLK:
		reg_val |= RT5682_SCLK_SRC_RCCLK;
		src = RT5682_CLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5682_GLB_CLK,
		RT5682_SCLK_SRC_MASK, reg_val);

	अगर (rt5682->master[RT5682_AIF2]) अणु
		snd_soc_component_update_bits(component,
			RT5682_I2S_M_CLK_CTRL_1, RT5682_I2S2_SRC_MASK,
			src << RT5682_I2S2_SRC_SFT);
	पूर्ण

	rt5682->sysclk = freq;
	rt5682->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code, pll2f_code, pll2b_code;
	अचिन्हित पूर्णांक pll2_fout1, pll2_ps_val;
	पूर्णांक ret;

	अगर (source == rt5682->pll_src[pll_id] &&
	    freq_in == rt5682->pll_in[pll_id] &&
	    freq_out == rt5682->pll_out[pll_id])
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5682->pll_in[pll_id] = 0;
		rt5682->pll_out[pll_id] = 0;
		snd_soc_component_update_bits(component, RT5682_GLB_CLK,
			RT5682_SCLK_SRC_MASK, RT5682_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	अगर (pll_id == RT5682_PLL2) अणु
		चयन (source) अणु
		हाल RT5682_PLL2_S_MCLK:
			snd_soc_component_update_bits(component,
				RT5682_GLB_CLK, RT5682_PLL2_SRC_MASK,
				RT5682_PLL2_SRC_MCLK);
			अवरोध;
		शेष:
			dev_err(component->dev, "Unknown PLL2 Source %d\n",
				source);
			वापस -EINVAL;
		पूर्ण

		/**
		 * PLL2 concatenates 2 PLL units.
		 * We suggest the Fout of the front PLL is 3.84MHz.
		 */
		pll2_fout1 = 3840000;
		ret = rl6231_pll_calc(freq_in, pll2_fout1, &pll2f_code);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Unsupport input clock %d\n",
				freq_in);
			वापस ret;
		पूर्ण
		dev_dbg(component->dev, "PLL2F: fin=%d fout=%d bypass=%d m=%d n=%d k=%d\n",
			freq_in, pll2_fout1,
			pll2f_code.m_bp,
			(pll2f_code.m_bp ? 0 : pll2f_code.m_code),
			pll2f_code.n_code, pll2f_code.k_code);

		ret = rl6231_pll_calc(pll2_fout1, freq_out, &pll2b_code);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Unsupport input clock %d\n",
				pll2_fout1);
			वापस ret;
		पूर्ण
		dev_dbg(component->dev, "PLL2B: fin=%d fout=%d bypass=%d m=%d n=%d k=%d\n",
			pll2_fout1, freq_out,
			pll2b_code.m_bp,
			(pll2b_code.m_bp ? 0 : pll2b_code.m_code),
			pll2b_code.n_code, pll2b_code.k_code);

		snd_soc_component_ग_लिखो(component, RT5682_PLL2_CTRL_1,
			pll2f_code.k_code << RT5682_PLL2F_K_SFT |
			pll2b_code.k_code << RT5682_PLL2B_K_SFT |
			pll2b_code.m_code);
		snd_soc_component_ग_लिखो(component, RT5682_PLL2_CTRL_2,
			pll2f_code.m_code << RT5682_PLL2F_M_SFT |
			pll2b_code.n_code);
		snd_soc_component_ग_लिखो(component, RT5682_PLL2_CTRL_3,
			pll2f_code.n_code << RT5682_PLL2F_N_SFT);

		अगर (freq_out == 22579200)
			pll2_ps_val = 1 << RT5682_PLL2B_SEL_PS_SFT;
		अन्यथा
			pll2_ps_val = 1 << RT5682_PLL2B_PS_BYP_SFT;
		snd_soc_component_update_bits(component, RT5682_PLL2_CTRL_4,
			RT5682_PLL2B_SEL_PS_MASK | RT5682_PLL2B_PS_BYP_MASK |
			RT5682_PLL2B_M_BP_MASK | RT5682_PLL2F_M_BP_MASK | 0xf,
			pll2_ps_val |
			(pll2b_code.m_bp ? 1 : 0) << RT5682_PLL2B_M_BP_SFT |
			(pll2f_code.m_bp ? 1 : 0) << RT5682_PLL2F_M_BP_SFT |
			0xf);
	पूर्ण अन्यथा अणु
		चयन (source) अणु
		हाल RT5682_PLL1_S_MCLK:
			snd_soc_component_update_bits(component,
				RT5682_GLB_CLK, RT5682_PLL1_SRC_MASK,
				RT5682_PLL1_SRC_MCLK);
			अवरोध;
		हाल RT5682_PLL1_S_BCLK1:
			snd_soc_component_update_bits(component,
				RT5682_GLB_CLK, RT5682_PLL1_SRC_MASK,
				RT5682_PLL1_SRC_BCLK1);
			अवरोध;
		शेष:
			dev_err(component->dev, "Unknown PLL1 Source %d\n",
				source);
			वापस -EINVAL;
		पूर्ण

		ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Unsupport input clock %d\n",
				freq_in);
			वापस ret;
		पूर्ण

		dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
			pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
			pll_code.n_code, pll_code.k_code);

		snd_soc_component_ग_लिखो(component, RT5682_PLL_CTRL_1,
			(pll_code.n_code << RT5682_PLL_N_SFT) | pll_code.k_code);
		snd_soc_component_ग_लिखो(component, RT5682_PLL_CTRL_2,
			((pll_code.m_bp ? 0 : pll_code.m_code) << RT5682_PLL_M_SFT) |
			((pll_code.m_bp << RT5682_PLL_M_BP_SFT) | RT5682_PLL_RST));
	पूर्ण

	rt5682->pll_in[pll_id] = freq_in;
	rt5682->pll_out[pll_id] = freq_out;
	rt5682->pll_src[pll_id] = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_bclk1_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	rt5682->bclk[dai->id] = ratio;

	चयन (ratio) अणु
	हाल 256:
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_BCLK_MS1_MASK, RT5682_TDM_BCLK_MS1_256);
		अवरोध;
	हाल 128:
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_BCLK_MS1_MASK, RT5682_TDM_BCLK_MS1_128);
		अवरोध;
	हाल 64:
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_BCLK_MS1_MASK, RT5682_TDM_BCLK_MS1_64);
		अवरोध;
	हाल 32:
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_BCLK_MS1_MASK, RT5682_TDM_BCLK_MS1_32);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Invalid bclk1 ratio %d\n", ratio);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_bclk2_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	rt5682->bclk[dai->id] = ratio;

	चयन (ratio) अणु
	हाल 64:
		snd_soc_component_update_bits(component, RT5682_ADDA_CLK_2,
			RT5682_I2S2_BCLK_MS2_MASK,
			RT5682_I2S2_BCLK_MS2_64);
		अवरोध;
	हाल 32:
		snd_soc_component_update_bits(component, RT5682_ADDA_CLK_2,
			RT5682_I2S2_BCLK_MS2_MASK,
			RT5682_I2S2_BCLK_MS2_32);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Invalid bclk2 ratio %d\n", ratio);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
			RT5682_PWR_BG, RT5682_PWR_BG);
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL, RT5682_DIG_GATE_CTRL);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO, 0);
		regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
			RT5682_PWR_BG, 0);
		अवरोध;
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
#घोषणा CLK_PLL2_FIN 48000000
#घोषणा CLK_48 48000
#घोषणा CLK_44 44100

अटल bool rt5682_clk_check(काष्ठा rt5682_priv *rt5682)
अणु
	अगर (!rt5682->master[RT5682_AIF1]) अणु
		dev_dbg(rt5682->component->dev, "sysclk/dai not set correctly\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक rt5682_wclk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	काष्ठा snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);

	अगर (!rt5682_clk_check(rt5682))
		वापस -EINVAL;

	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "MICBIAS");
	snd_soc_component_update_bits(component, RT5682_PWR_ANLG_1,
				RT5682_PWR_MB, RT5682_PWR_MB);

	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Vref2");
	snd_soc_component_update_bits(component, RT5682_PWR_ANLG_1,
			RT5682_PWR_VREF2 | RT5682_PWR_FV2,
			RT5682_PWR_VREF2);
	usleep_range(55000, 60000);
	snd_soc_component_update_bits(component, RT5682_PWR_ANLG_1,
			RT5682_PWR_FV2, RT5682_PWR_FV2);

	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "I2S1");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PLL2F");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "PLL2B");
	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);

	वापस 0;
पूर्ण

अटल व्योम rt5682_wclk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	काष्ठा snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);

	अगर (!rt5682_clk_check(rt5682))
		वापस;

	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_disable_pin_unlocked(dapm, "MICBIAS");
	snd_soc_dapm_disable_pin_unlocked(dapm, "Vref2");
	अगर (!rt5682->jack_type)
		snd_soc_component_update_bits(component, RT5682_PWR_ANLG_1,
				RT5682_PWR_VREF2 | RT5682_PWR_FV2 |
				RT5682_PWR_MB, 0);

	snd_soc_dapm_disable_pin_unlocked(dapm, "I2S1");
	snd_soc_dapm_disable_pin_unlocked(dapm, "PLL2F");
	snd_soc_dapm_disable_pin_unlocked(dapm, "PLL2B");
	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल अचिन्हित दीर्घ rt5682_wclk_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	स्थिर अक्षर * स्थिर clk_name = clk_hw_get_name(hw);

	अगर (!rt5682_clk_check(rt5682))
		वापस 0;
	/*
	 * Only accept to set wclk rate to 44.1k or 48kHz.
	 */
	अगर (rt5682->lrck[RT5682_AIF1] != CLK_48 &&
	    rt5682->lrck[RT5682_AIF1] != CLK_44) अणु
		dev_warn(component->dev, "%s: clk %s only support %d or %d Hz output\n",
			__func__, clk_name, CLK_44, CLK_48);
		वापस 0;
	पूर्ण

	वापस rt5682->lrck[RT5682_AIF1];
पूर्ण

अटल दीर्घ rt5682_wclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	स्थिर अक्षर * स्थिर clk_name = clk_hw_get_name(hw);

	अगर (!rt5682_clk_check(rt5682))
		वापस -EINVAL;
	/*
	 * Only accept to set wclk rate to 44.1k or 48kHz.
	 * It will क्रमce to 48kHz अगर not both.
	 */
	अगर (rate != CLK_48 && rate != CLK_44) अणु
		dev_warn(component->dev, "%s: clk %s only support %d or %d Hz output\n",
			__func__, clk_name, CLK_44, CLK_48);
		rate = CLK_48;
	पूर्ण

	वापस rate;
पूर्ण

अटल पूर्णांक rt5682_wclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	काष्ठा clk_hw *parent_hw;
	स्थिर अक्षर * स्थिर clk_name = clk_hw_get_name(hw);
	पूर्णांक pre_भाग;
	अचिन्हित पूर्णांक clk_pll2_out;

	अगर (!rt5682_clk_check(rt5682))
		वापस -EINVAL;

	/*
	 * Whether the wclk's parent clk (mclk) exists or not, please ensure
	 * it is fixed or set to 48MHz beक्रमe setting wclk rate. It's a
	 * temporary limitation. Only accept 48MHz clk as the clk provider.
	 *
	 * It will set the codec anyway by assuming mclk is 48MHz.
	 */
	parent_hw = clk_hw_get_parent(hw);
	अगर (!parent_hw)
		dev_warn(component->dev,
			"Parent mclk of wclk not acquired in driver. Please ensure mclk was provided as %d Hz.\n",
			CLK_PLL2_FIN);

	अगर (parent_rate != CLK_PLL2_FIN)
		dev_warn(component->dev, "clk %s only support %d Hz input\n",
			clk_name, CLK_PLL2_FIN);

	/*
	 * To achieve the rate conversion from 48MHz to 44.1k or 48kHz,
	 * PLL2 is needed.
	 */
	clk_pll2_out = rate * 512;
	rt5682_set_component_pll(component, RT5682_PLL2, RT5682_PLL2_S_MCLK,
		CLK_PLL2_FIN, clk_pll2_out);

	rt5682_set_component_sysclk(component, RT5682_SCLK_S_PLL2, 0,
		clk_pll2_out, SND_SOC_CLOCK_IN);

	rt5682->lrck[RT5682_AIF1] = rate;

	pre_भाग = rl6231_get_clk_info(rt5682->sysclk, rate);

	snd_soc_component_update_bits(component, RT5682_ADDA_CLK_1,
		RT5682_I2S_M_DIV_MASK | RT5682_I2S_CLK_SRC_MASK,
		pre_भाग << RT5682_I2S_M_DIV_SFT |
		(rt5682->sysclk_src) << RT5682_I2S_CLK_SRC_SFT);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ rt5682_bclk_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_BCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	अचिन्हित पूर्णांक bclks_per_wclk;

	bclks_per_wclk = snd_soc_component_पढ़ो(component, RT5682_TDM_TCON_CTRL);

	चयन (bclks_per_wclk & RT5682_TDM_BCLK_MS1_MASK) अणु
	हाल RT5682_TDM_BCLK_MS1_256:
		वापस parent_rate * 256;
	हाल RT5682_TDM_BCLK_MS1_128:
		वापस parent_rate * 128;
	हाल RT5682_TDM_BCLK_MS1_64:
		वापस parent_rate * 64;
	हाल RT5682_TDM_BCLK_MS1_32:
		वापस parent_rate * 32;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ rt5682_bclk_get_factor(अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ factor;

	factor = rate / parent_rate;
	अगर (factor < 64)
		वापस 32;
	अन्यथा अगर (factor < 128)
		वापस 64;
	अन्यथा अगर (factor < 256)
		वापस 128;
	अन्यथा
		वापस 256;
पूर्ण

अटल दीर्घ rt5682_bclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_BCLK_IDX]);
	अचिन्हित दीर्घ factor;

	अगर (!*parent_rate || !rt5682_clk_check(rt5682))
		वापस -EINVAL;

	/*
	 * BCLK rates are set as a multiplier of WCLK in HW.
	 * We करोn't allow changing the parent WCLK. We just करो
	 * some rounding करोwn based on the parent WCLK rate
	 * and find the appropriate multiplier of BCLK to
	 * get the rounded करोwn BCLK value.
	 */
	factor = rt5682_bclk_get_factor(rate, *parent_rate);

	वापस *parent_rate * factor;
पूर्ण

अटल पूर्णांक rt5682_bclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rt5682_priv *rt5682 =
		container_of(hw, काष्ठा rt5682_priv,
			     dai_clks_hw[RT5682_DAI_BCLK_IDX]);
	काष्ठा snd_soc_component *component = rt5682->component;
	काष्ठा snd_soc_dai *dai;
	अचिन्हित दीर्घ factor;

	अगर (!rt5682_clk_check(rt5682))
		वापस -EINVAL;

	factor = rt5682_bclk_get_factor(rate, parent_rate);

	क्रम_each_component_dais(component, dai)
		अगर (dai->id == RT5682_AIF1)
			अवरोध;
	अगर (!dai) अणु
		dev_err(component->dev, "dai %d not found in component\n",
			RT5682_AIF1);
		वापस -ENODEV;
	पूर्ण

	वापस rt5682_set_bclk1_ratio(dai, factor);
पूर्ण

अटल स्थिर काष्ठा clk_ops rt5682_dai_clk_ops[RT5682_DAI_NUM_CLKS] = अणु
	[RT5682_DAI_WCLK_IDX] = अणु
		.prepare = rt5682_wclk_prepare,
		.unprepare = rt5682_wclk_unprepare,
		.recalc_rate = rt5682_wclk_recalc_rate,
		.round_rate = rt5682_wclk_round_rate,
		.set_rate = rt5682_wclk_set_rate,
	पूर्ण,
	[RT5682_DAI_BCLK_IDX] = अणु
		.recalc_rate = rt5682_bclk_recalc_rate,
		.round_rate = rt5682_bclk_round_rate,
		.set_rate = rt5682_bclk_set_rate,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt5682_रेजिस्टर_dai_clks(काष्ठा snd_soc_component *component)
अणु
	काष्ठा device *dev = component->dev;
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा rt5682_platक्रमm_data *pdata = &rt5682->pdata;
	काष्ठा clk_hw *dai_clk_hw;
	पूर्णांक i, ret;

	क्रम (i = 0; i < RT5682_DAI_NUM_CLKS; ++i) अणु
		काष्ठा clk_init_data init = अणु पूर्ण;

		dai_clk_hw = &rt5682->dai_clks_hw[i];

		चयन (i) अणु
		हाल RT5682_DAI_WCLK_IDX:
			/* Make MCLK the parent of WCLK */
			अगर (rt5682->mclk) अणु
				init.parent_data = &(काष्ठा clk_parent_data)अणु
					.fw_name = "mclk",
				पूर्ण;
				init.num_parents = 1;
			पूर्ण
			अवरोध;
		हाल RT5682_DAI_BCLK_IDX:
			/* Make WCLK the parent of BCLK */
			init.parent_hws = &(स्थिर काष्ठा clk_hw *)अणु
				&rt5682->dai_clks_hw[RT5682_DAI_WCLK_IDX]
			पूर्ण;
			init.num_parents = 1;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid clock index\n");
			वापस -EINVAL;
		पूर्ण

		init.name = pdata->dai_clk_names[i];
		init.ops = &rt5682_dai_clk_ops[i];
		init.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_GATE;
		dai_clk_hw->init = &init;

		ret = devm_clk_hw_रेजिस्टर(dev, dai_clk_hw);
		अगर (ret) अणु
			dev_warn(dev, "Failed to register %s: %d\n",
				 init.name, ret);
			वापस ret;
		पूर्ण

		अगर (dev->of_node) अणु
			devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
						    dai_clk_hw);
		पूर्ण अन्यथा अणु
			ret = devm_clk_hw_रेजिस्टर_clkdev(dev, dai_clk_hw,
							  init.name,
							  dev_name(dev));
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMMON_CLK */

अटल पूर्णांक rt5682_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_slave *slave;
	अचिन्हित दीर्घ समय;
	काष्ठा snd_soc_dapm_context *dapm = &component->dapm;

#अगर_घोषित CONFIG_COMMON_CLK
	पूर्णांक ret;
#पूर्ण_अगर
	rt5682->component = component;

	अगर (rt5682->is_sdw) अणु
		slave = rt5682->slave;
		समय = रुको_क्रम_completion_समयout(
			&slave->initialization_complete,
			msecs_to_jअगरfies(RT5682_PROBE_TIMEOUT));
		अगर (!समय) अणु
			dev_err(&slave->dev, "Initialization not complete, timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_COMMON_CLK
		/* Check अगर MCLK provided */
		rt5682->mclk = devm_clk_get(component->dev, "mclk");
		अगर (IS_ERR(rt5682->mclk)) अणु
			अगर (PTR_ERR(rt5682->mclk) != -ENOENT) अणु
				ret = PTR_ERR(rt5682->mclk);
				वापस ret;
			पूर्ण
			rt5682->mclk = शून्य;
		पूर्ण

		/* Register CCF DAI घड़ी control */
		ret = rt5682_रेजिस्टर_dai_clks(component);
		अगर (ret)
			वापस ret;

		/* Initial setup क्रम CCF */
		rt5682->lrck[RT5682_AIF1] = CLK_48;
#पूर्ण_अगर
	पूर्ण

	snd_soc_dapm_disable_pin(dapm, "MICBIAS");
	snd_soc_dapm_disable_pin(dapm, "Vref2");
	snd_soc_dapm_sync(dapm);
	वापस 0;
पूर्ण

अटल व्योम rt5682_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	rt5682_reset(rt5682);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5682_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	अगर (rt5682->is_sdw)
		वापस 0;

	regcache_cache_only(rt5682->regmap, true);
	regcache_mark_dirty(rt5682->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	अगर (rt5682->is_sdw)
		वापस 0;

	regcache_cache_only(rt5682->regmap, false);
	regcache_sync(rt5682->regmap);

	mod_delayed_work(प्रणाली_घातer_efficient_wq,
		&rt5682->jack_detect_work, msecs_to_jअगरfies(250));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5682_suspend शून्य
#घोषणा rt5682_resume शून्य
#पूर्ण_अगर

स्थिर काष्ठा snd_soc_dai_ops rt5682_aअगर1_dai_ops = अणु
	.hw_params = rt5682_hw_params,
	.set_fmt = rt5682_set_dai_fmt,
	.set_tdm_slot = rt5682_set_tdm_slot,
	.set_bclk_ratio = rt5682_set_bclk1_ratio,
पूर्ण;
EXPORT_SYMBOL_GPL(rt5682_aअगर1_dai_ops);

स्थिर काष्ठा snd_soc_dai_ops rt5682_aअगर2_dai_ops = अणु
	.hw_params = rt5682_hw_params,
	.set_fmt = rt5682_set_dai_fmt,
	.set_bclk_ratio = rt5682_set_bclk2_ratio,
पूर्ण;
EXPORT_SYMBOL_GPL(rt5682_aअगर2_dai_ops);

स्थिर काष्ठा snd_soc_component_driver rt5682_soc_component_dev = अणु
	.probe = rt5682_probe,
	.हटाओ = rt5682_हटाओ,
	.suspend = rt5682_suspend,
	.resume = rt5682_resume,
	.set_bias_level = rt5682_set_bias_level,
	.controls = rt5682_snd_controls,
	.num_controls = ARRAY_SIZE(rt5682_snd_controls),
	.dapm_widमाला_लो = rt5682_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt5682_dapm_widमाला_लो),
	.dapm_routes = rt5682_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt5682_dapm_routes),
	.set_sysclk = rt5682_set_component_sysclk,
	.set_pll = rt5682_set_component_pll,
	.set_jack = rt5682_set_jack_detect,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;
EXPORT_SYMBOL_GPL(rt5682_soc_component_dev);

पूर्णांक rt5682_parse_dt(काष्ठा rt5682_priv *rt5682, काष्ठा device *dev)
अणु

	device_property_पढ़ो_u32(dev, "realtek,dmic1-data-pin",
		&rt5682->pdata.dmic1_data_pin);
	device_property_पढ़ो_u32(dev, "realtek,dmic1-clk-pin",
		&rt5682->pdata.dmic1_clk_pin);
	device_property_पढ़ो_u32(dev, "realtek,jd-src",
		&rt5682->pdata.jd_src);
	device_property_पढ़ो_u32(dev, "realtek,btndet-delay",
		&rt5682->pdata.btndet_delay);
	device_property_पढ़ो_u32(dev, "realtek,dmic-clk-rate-hz",
		&rt5682->pdata.dmic_clk_rate);
	device_property_पढ़ो_u32(dev, "realtek,dmic-delay-ms",
		&rt5682->pdata.dmic_delay);

	rt5682->pdata.lकरो1_en = of_get_named_gpio(dev->of_node,
		"realtek,ldo1-en-gpios", 0);

	अगर (device_property_पढ़ो_string_array(dev, "clock-output-names",
					      rt5682->pdata.dai_clk_names,
					      RT5682_DAI_NUM_CLKS) < 0)
		dev_warn(dev, "Using default DAI clk names: %s, %s\n",
			 rt5682->pdata.dai_clk_names[RT5682_DAI_WCLK_IDX],
			 rt5682->pdata.dai_clk_names[RT5682_DAI_BCLK_IDX]);

	rt5682->pdata.dmic_clk_driving_high = device_property_पढ़ो_bool(dev,
		"realtek,dmic-clk-driving-high");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_parse_dt);

व्योम rt5682_calibrate(काष्ठा rt5682_priv *rt5682)
अणु
	पूर्णांक value, count;

	mutex_lock(&rt5682->calibrate_mutex);

	rt5682_reset(rt5682);
	regmap_ग_लिखो(rt5682->regmap, RT5682_I2C_CTRL, 0x000f);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PWR_ANLG_1, 0xa2af);
	usleep_range(15000, 20000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PWR_ANLG_1, 0xf2af);
	regmap_ग_लिखो(rt5682->regmap, RT5682_MICBIAS_2, 0x0300);
	regmap_ग_लिखो(rt5682->regmap, RT5682_GLB_CLK, 0x8000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PWR_DIG_1, 0x0100);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_IMP_SENS_CTRL_19, 0x3800);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CHOP_DAC, 0x3000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CALIB_ADC_CTRL, 0x7005);
	regmap_ग_लिखो(rt5682->regmap, RT5682_STO1_ADC_MIXER, 0x686c);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CAL_REC, 0x0d0d);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_CALIB_CTRL_2, 0x0321);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_LOGIC_CTRL_2, 0x0004);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0x7c00);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_CALIB_CTRL_3, 0x06a1);
	regmap_ग_लिखो(rt5682->regmap, RT5682_A_DAC1_MUX, 0x0311);
	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0x7c00);

	regmap_ग_लिखो(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0xfc00);

	क्रम (count = 0; count < 60; count++) अणु
		regmap_पढ़ो(rt5682->regmap, RT5682_HP_CALIB_STA_1, &value);
		अगर (!(value & 0x8000))
			अवरोध;

		usleep_range(10000, 10005);
	पूर्ण

	अगर (count >= 60)
		dev_err(rt5682->component->dev, "HP Calibration Failure\n");

	/* restore settings */
	regmap_ग_लिखो(rt5682->regmap, RT5682_PWR_ANLG_1, 0x002f);
	regmap_ग_लिखो(rt5682->regmap, RT5682_MICBIAS_2, 0x0080);
	regmap_ग_लिखो(rt5682->regmap, RT5682_GLB_CLK, 0x0000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_PWR_DIG_1, 0x0000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CHOP_DAC, 0x2000);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CALIB_ADC_CTRL, 0x2005);
	regmap_ग_लिखो(rt5682->regmap, RT5682_STO1_ADC_MIXER, 0xc0c4);
	regmap_ग_लिखो(rt5682->regmap, RT5682_CAL_REC, 0x0c0c);

	mutex_unlock(&rt5682->calibrate_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rt5682_calibrate);

MODULE_DESCRIPTION("ASoC RT5682 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
