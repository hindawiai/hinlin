<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5665.c  --  RT5665/RT5658 ALSA SoC audio codec driver
 *
 * Copyright 2016 Realtek Semiconductor Corp.
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
#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/rt5665.h>

#समावेश "rl6231.h"
#समावेश "rt5665.h"

#घोषणा RT5665_NUM_SUPPLIES 3

अटल स्थिर अक्षर *rt5665_supply_names[RT5665_NUM_SUPPLIES] = अणु
	"AVDD",
	"MICVDD",
	"VBAT",
पूर्ण;

काष्ठा rt5665_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा rt5665_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *gpiod_lकरो1_en;
	काष्ठा gpio_desc *gpiod_reset;
	काष्ठा snd_soc_jack *hs_jack;
	काष्ठा regulator_bulk_data supplies[RT5665_NUM_SUPPLIES];
	काष्ठा delayed_work jack_detect_work;
	काष्ठा delayed_work calibrate_work;
	काष्ठा delayed_work jd_check_work;
	काष्ठा mutex calibrate_mutex;

	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck[RT5665_AIFS];
	पूर्णांक bclk[RT5665_AIFS];
	पूर्णांक master[RT5665_AIFS];
	पूर्णांक id;

	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;

	पूर्णांक jack_type;
	पूर्णांक irq_work_delay_समय;
	अचिन्हित पूर्णांक sar_adc_value;
	bool calibration_करोne;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5665_reg[] = अणु
	अणु0x0000, 0x0000पूर्ण,
	अणु0x0001, 0xc8c8पूर्ण,
	अणु0x0002, 0x8080पूर्ण,
	अणु0x0003, 0x8000पूर्ण,
	अणु0x0004, 0xc80aपूर्ण,
	अणु0x0005, 0x0000पूर्ण,
	अणु0x0006, 0x0000पूर्ण,
	अणु0x0007, 0x0000पूर्ण,
	अणु0x000a, 0x0000पूर्ण,
	अणु0x000b, 0x0000पूर्ण,
	अणु0x000c, 0x0000पूर्ण,
	अणु0x000d, 0x0000पूर्ण,
	अणु0x000f, 0x0808पूर्ण,
	अणु0x0010, 0x4040पूर्ण,
	अणु0x0011, 0x0000पूर्ण,
	अणु0x0012, 0x1404पूर्ण,
	अणु0x0013, 0x1000पूर्ण,
	अणु0x0014, 0xa00aपूर्ण,
	अणु0x0015, 0x0404पूर्ण,
	अणु0x0016, 0x0404पूर्ण,
	अणु0x0017, 0x0011पूर्ण,
	अणु0x0018, 0xafafपूर्ण,
	अणु0x0019, 0xafafपूर्ण,
	अणु0x001a, 0xafafपूर्ण,
	अणु0x001b, 0x0011पूर्ण,
	अणु0x001c, 0x2f2fपूर्ण,
	अणु0x001d, 0x2f2fपूर्ण,
	अणु0x001e, 0x2f2fपूर्ण,
	अणु0x001f, 0x0000पूर्ण,
	अणु0x0020, 0x0000पूर्ण,
	अणु0x0021, 0x0000पूर्ण,
	अणु0x0022, 0x5757पूर्ण,
	अणु0x0023, 0x0039पूर्ण,
	अणु0x0026, 0xc0c0पूर्ण,
	अणु0x0027, 0xc0c0पूर्ण,
	अणु0x0028, 0xc0c0पूर्ण,
	अणु0x0029, 0x8080पूर्ण,
	अणु0x002a, 0xaaaaपूर्ण,
	अणु0x002b, 0xaaaaपूर्ण,
	अणु0x002c, 0xaba8पूर्ण,
	अणु0x002d, 0x0000पूर्ण,
	अणु0x002e, 0x0000पूर्ण,
	अणु0x002f, 0x0000पूर्ण,
	अणु0x0030, 0x0000पूर्ण,
	अणु0x0031, 0x5000पूर्ण,
	अणु0x0032, 0x0000पूर्ण,
	अणु0x0033, 0x0000पूर्ण,
	अणु0x0034, 0x0000पूर्ण,
	अणु0x0035, 0x0000पूर्ण,
	अणु0x003a, 0x0000पूर्ण,
	अणु0x003b, 0x0000पूर्ण,
	अणु0x003c, 0x00ffपूर्ण,
	अणु0x003d, 0x0000पूर्ण,
	अणु0x003e, 0x00ffपूर्ण,
	अणु0x003f, 0x0000पूर्ण,
	अणु0x0040, 0x0000पूर्ण,
	अणु0x0041, 0x00ffपूर्ण,
	अणु0x0042, 0x0000पूर्ण,
	अणु0x0043, 0x00ffपूर्ण,
	अणु0x0044, 0x0c0cपूर्ण,
	अणु0x0049, 0xc00bपूर्ण,
	अणु0x004a, 0x0000पूर्ण,
	अणु0x004b, 0x031fपूर्ण,
	अणु0x004d, 0x0000पूर्ण,
	अणु0x004e, 0x001fपूर्ण,
	अणु0x004f, 0x0000पूर्ण,
	अणु0x0050, 0x001fपूर्ण,
	अणु0x0052, 0xf000पूर्ण,
	अणु0x0061, 0x0000पूर्ण,
	अणु0x0062, 0x0000पूर्ण,
	अणु0x0063, 0x003eपूर्ण,
	अणु0x0064, 0x0000पूर्ण,
	अणु0x0065, 0x0000पूर्ण,
	अणु0x0066, 0x003fपूर्ण,
	अणु0x0067, 0x0000पूर्ण,
	अणु0x006b, 0x0000पूर्ण,
	अणु0x006d, 0xff00पूर्ण,
	अणु0x006e, 0x2808पूर्ण,
	अणु0x006f, 0x000aपूर्ण,
	अणु0x0070, 0x8000पूर्ण,
	अणु0x0071, 0x8000पूर्ण,
	अणु0x0072, 0x8000पूर्ण,
	अणु0x0073, 0x7000पूर्ण,
	अणु0x0074, 0x7770पूर्ण,
	अणु0x0075, 0x0002पूर्ण,
	अणु0x0076, 0x0001पूर्ण,
	अणु0x0078, 0x00f0पूर्ण,
	अणु0x0079, 0x0000पूर्ण,
	अणु0x007a, 0x0000पूर्ण,
	अणु0x007b, 0x0000पूर्ण,
	अणु0x007c, 0x0000पूर्ण,
	अणु0x007d, 0x0123पूर्ण,
	अणु0x007e, 0x4500पूर्ण,
	अणु0x007f, 0x8003पूर्ण,
	अणु0x0080, 0x0000पूर्ण,
	अणु0x0081, 0x0000पूर्ण,
	अणु0x0082, 0x0000पूर्ण,
	अणु0x0083, 0x0000पूर्ण,
	अणु0x0084, 0x0000पूर्ण,
	अणु0x0085, 0x0000पूर्ण,
	अणु0x0086, 0x0008पूर्ण,
	अणु0x0087, 0x0000पूर्ण,
	अणु0x0088, 0x0000पूर्ण,
	अणु0x0089, 0x0000पूर्ण,
	अणु0x008a, 0x0000पूर्ण,
	अणु0x008b, 0x0000पूर्ण,
	अणु0x008c, 0x0003पूर्ण,
	अणु0x008e, 0x0060पूर्ण,
	अणु0x008f, 0x1000पूर्ण,
	अणु0x0091, 0x0c26पूर्ण,
	अणु0x0092, 0x0073पूर्ण,
	अणु0x0093, 0x0000पूर्ण,
	अणु0x0094, 0x0080पूर्ण,
	अणु0x0098, 0x0000पूर्ण,
	अणु0x0099, 0x0000पूर्ण,
	अणु0x009a, 0x0007पूर्ण,
	अणु0x009f, 0x0000पूर्ण,
	अणु0x00a0, 0x0000पूर्ण,
	अणु0x00a1, 0x0002पूर्ण,
	अणु0x00a2, 0x0001पूर्ण,
	अणु0x00a3, 0x0002पूर्ण,
	अणु0x00a4, 0x0001पूर्ण,
	अणु0x00ae, 0x2040पूर्ण,
	अणु0x00af, 0x0000पूर्ण,
	अणु0x00b6, 0x0000पूर्ण,
	अणु0x00b7, 0x0000पूर्ण,
	अणु0x00b8, 0x0000पूर्ण,
	अणु0x00b9, 0x0000पूर्ण,
	अणु0x00ba, 0x0002पूर्ण,
	अणु0x00bb, 0x0000पूर्ण,
	अणु0x00be, 0x0000पूर्ण,
	अणु0x00c0, 0x0000पूर्ण,
	अणु0x00c1, 0x0aaaपूर्ण,
	अणु0x00c2, 0xaa80पूर्ण,
	अणु0x00c3, 0x0003पूर्ण,
	अणु0x00c4, 0x0000पूर्ण,
	अणु0x00d0, 0x0000पूर्ण,
	अणु0x00d1, 0x2244पूर्ण,
	अणु0x00d3, 0x3300पूर्ण,
	अणु0x00d4, 0x2200पूर्ण,
	अणु0x00d9, 0x0809पूर्ण,
	अणु0x00da, 0x0000पूर्ण,
	अणु0x00db, 0x0008पूर्ण,
	अणु0x00dc, 0x00c0पूर्ण,
	अणु0x00dd, 0x6724पूर्ण,
	अणु0x00de, 0x3131पूर्ण,
	अणु0x00df, 0x0008पूर्ण,
	अणु0x00e0, 0x4000पूर्ण,
	अणु0x00e1, 0x3131पूर्ण,
	अणु0x00e2, 0x600cपूर्ण,
	अणु0x00ea, 0xb320पूर्ण,
	अणु0x00eb, 0x0000पूर्ण,
	अणु0x00ec, 0xb300पूर्ण,
	अणु0x00ed, 0x0000पूर्ण,
	अणु0x00ee, 0xb320पूर्ण,
	अणु0x00ef, 0x0000पूर्ण,
	अणु0x00f0, 0x0201पूर्ण,
	अणु0x00f1, 0x0dddपूर्ण,
	अणु0x00f2, 0x0dddपूर्ण,
	अणु0x00f6, 0x0000पूर्ण,
	अणु0x00f7, 0x0000पूर्ण,
	अणु0x00f8, 0x0000पूर्ण,
	अणु0x00fa, 0x0000पूर्ण,
	अणु0x00fb, 0x0000पूर्ण,
	अणु0x00fc, 0x0000पूर्ण,
	अणु0x00fd, 0x0000पूर्ण,
	अणु0x00fe, 0x10ecपूर्ण,
	अणु0x00ff, 0x6451पूर्ण,
	अणु0x0100, 0xaaaaपूर्ण,
	अणु0x0101, 0x000aपूर्ण,
	अणु0x010a, 0xaaaaपूर्ण,
	अणु0x010b, 0xa0a0पूर्ण,
	अणु0x010c, 0xaeaeपूर्ण,
	अणु0x010d, 0xaaaaपूर्ण,
	अणु0x010e, 0xaaaaपूर्ण,
	अणु0x010f, 0xaaaaपूर्ण,
	अणु0x0110, 0xe002पूर्ण,
	अणु0x0111, 0xa402पूर्ण,
	अणु0x0112, 0xaaaaपूर्ण,
	अणु0x0113, 0x2000पूर्ण,
	अणु0x0117, 0x0f00पूर्ण,
	अणु0x0125, 0x0410पूर्ण,
	अणु0x0132, 0x0000पूर्ण,
	अणु0x0133, 0x0000पूर्ण,
	अणु0x0137, 0x5540पूर्ण,
	अणु0x0138, 0x3700पूर्ण,
	अणु0x0139, 0x79a1पूर्ण,
	अणु0x013a, 0x2020पूर्ण,
	अणु0x013b, 0x2020पूर्ण,
	अणु0x013c, 0x2005पूर्ण,
	अणु0x013f, 0x0000पूर्ण,
	अणु0x0145, 0x0002पूर्ण,
	अणु0x0146, 0x0000पूर्ण,
	अणु0x0147, 0x0000पूर्ण,
	अणु0x0148, 0x0000पूर्ण,
	अणु0x0150, 0x0000पूर्ण,
	अणु0x0160, 0x4effपूर्ण,
	अणु0x0161, 0x0080पूर्ण,
	अणु0x0162, 0x0200पूर्ण,
	अणु0x0163, 0x0800पूर्ण,
	अणु0x0164, 0x0000पूर्ण,
	अणु0x0165, 0x0000पूर्ण,
	अणु0x0166, 0x0000पूर्ण,
	अणु0x0167, 0x000fपूर्ण,
	अणु0x0170, 0x4e87पूर्ण,
	अणु0x0171, 0x0080पूर्ण,
	अणु0x0172, 0x0200पूर्ण,
	अणु0x0173, 0x0800पूर्ण,
	अणु0x0174, 0x00ffपूर्ण,
	अणु0x0175, 0x0000पूर्ण,
	अणु0x0190, 0x413dपूर्ण,
	अणु0x0191, 0x4139पूर्ण,
	अणु0x0192, 0x4135पूर्ण,
	अणु0x0193, 0x413dपूर्ण,
	अणु0x0194, 0x0000पूर्ण,
	अणु0x0195, 0x0000पूर्ण,
	अणु0x0196, 0x0000पूर्ण,
	अणु0x0197, 0x0000पूर्ण,
	अणु0x0198, 0x0000पूर्ण,
	अणु0x0199, 0x0000पूर्ण,
	अणु0x01a0, 0x1e64पूर्ण,
	अणु0x01a1, 0x06a3पूर्ण,
	अणु0x01a2, 0x0000पूर्ण,
	अणु0x01a3, 0x0000पूर्ण,
	अणु0x01a4, 0x0000पूर्ण,
	अणु0x01a5, 0x0000पूर्ण,
	अणु0x01a6, 0x0000पूर्ण,
	अणु0x01a7, 0x8000पूर्ण,
	अणु0x01a8, 0x0000पूर्ण,
	अणु0x01a9, 0x0000पूर्ण,
	अणु0x01aa, 0x0000पूर्ण,
	अणु0x01ab, 0x0000पूर्ण,
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
	अणु0x01c1, 0x0000पूर्ण,
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
	अणु0x01d6, 0x003cपूर्ण,
	अणु0x01da, 0x0000पूर्ण,
	अणु0x01db, 0x0000पूर्ण,
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
	अणु0x01ea, 0xbf3fपूर्ण,
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
	अणु0x0200, 0x0000पूर्ण,
	अणु0x0201, 0x0000पूर्ण,
	अणु0x0202, 0x0000पूर्ण,
	अणु0x0203, 0x0000पूर्ण,
	अणु0x0204, 0x0000पूर्ण,
	अणु0x0205, 0x0000पूर्ण,
	अणु0x0206, 0x0000पूर्ण,
	अणु0x0207, 0x0000पूर्ण,
	अणु0x0208, 0x0000पूर्ण,
	अणु0x0210, 0x60b1पूर्ण,
	अणु0x0211, 0xa005पूर्ण,
	अणु0x0212, 0x024cपूर्ण,
	अणु0x0213, 0xf7ffपूर्ण,
	अणु0x0214, 0x024cपूर्ण,
	अणु0x0215, 0x0102पूर्ण,
	अणु0x0216, 0x00a3पूर्ण,
	अणु0x0217, 0x0048पूर्ण,
	अणु0x0218, 0xa2c0पूर्ण,
	अणु0x0219, 0x0400पूर्ण,
	अणु0x021a, 0x00c8पूर्ण,
	अणु0x021b, 0x00c0पूर्ण,
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
	अणु0x0330, 0x00a6पूर्ण,
	अणु0x0331, 0x04c3पूर्ण,
	अणु0x0332, 0x27c8पूर्ण,
	अणु0x0333, 0xbf50पूर्ण,
	अणु0x0334, 0x0045पूर्ण,
	अणु0x0335, 0x0007पूर्ण,
	अणु0x0336, 0x7418पूर्ण,
	अणु0x0337, 0x0501पूर्ण,
	अणु0x0338, 0x0000पूर्ण,
	अणु0x0339, 0x0010पूर्ण,
	अणु0x033a, 0x1010पूर्ण,
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

अटल bool rt5665_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5665_RESET:
	हाल RT5665_EJD_CTRL_2:
	हाल RT5665_GPIO_STA:
	हाल RT5665_INT_ST_1:
	हाल RT5665_IL_CMD_1:
	हाल RT5665_4BTN_IL_CMD_1:
	हाल RT5665_PSV_IL_CMD_1:
	हाल RT5665_AJD1_CTRL:
	हाल RT5665_JD_CTRL_3:
	हाल RT5665_STO_NG2_CTRL_1:
	हाल RT5665_SAR_IL_CMD_4:
	हाल RT5665_DEVICE_ID:
	हाल RT5665_STO1_DAC_SIL_DET ... RT5665_STO2_DAC_SIL_DET:
	हाल RT5665_MONO_AMP_CALIB_STA1 ... RT5665_MONO_AMP_CALIB_STA6:
	हाल RT5665_HP_IMP_SENS_CTRL_12 ... RT5665_HP_IMP_SENS_CTRL_15:
	हाल RT5665_HP_CALIB_STA_1 ... RT5665_HP_CALIB_STA_11:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5665_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5665_RESET:
	हाल RT5665_VENDOR_ID:
	हाल RT5665_VENDOR_ID_1:
	हाल RT5665_DEVICE_ID:
	हाल RT5665_LOUT:
	हाल RT5665_HP_CTRL_1:
	हाल RT5665_HP_CTRL_2:
	हाल RT5665_MONO_OUT:
	हाल RT5665_HPL_GAIN:
	हाल RT5665_HPR_GAIN:
	हाल RT5665_MONO_GAIN:
	हाल RT5665_CAL_BST_CTRL:
	हाल RT5665_CBJ_BST_CTRL:
	हाल RT5665_IN1_IN2:
	हाल RT5665_IN3_IN4:
	हाल RT5665_INL1_INR1_VOL:
	हाल RT5665_EJD_CTRL_1:
	हाल RT5665_EJD_CTRL_2:
	हाल RT5665_EJD_CTRL_3:
	हाल RT5665_EJD_CTRL_4:
	हाल RT5665_EJD_CTRL_5:
	हाल RT5665_EJD_CTRL_6:
	हाल RT5665_EJD_CTRL_7:
	हाल RT5665_DAC2_CTRL:
	हाल RT5665_DAC2_DIG_VOL:
	हाल RT5665_DAC1_DIG_VOL:
	हाल RT5665_DAC3_DIG_VOL:
	हाल RT5665_DAC3_CTRL:
	हाल RT5665_STO1_ADC_DIG_VOL:
	हाल RT5665_MONO_ADC_DIG_VOL:
	हाल RT5665_STO2_ADC_DIG_VOL:
	हाल RT5665_STO1_ADC_BOOST:
	हाल RT5665_MONO_ADC_BOOST:
	हाल RT5665_STO2_ADC_BOOST:
	हाल RT5665_HP_IMP_GAIN_1:
	हाल RT5665_HP_IMP_GAIN_2:
	हाल RT5665_STO1_ADC_MIXER:
	हाल RT5665_MONO_ADC_MIXER:
	हाल RT5665_STO2_ADC_MIXER:
	हाल RT5665_AD_DA_MIXER:
	हाल RT5665_STO1_DAC_MIXER:
	हाल RT5665_MONO_DAC_MIXER:
	हाल RT5665_STO2_DAC_MIXER:
	हाल RT5665_A_DAC1_MUX:
	हाल RT5665_A_DAC2_MUX:
	हाल RT5665_DIG_INF2_DATA:
	हाल RT5665_DIG_INF3_DATA:
	हाल RT5665_PDM_OUT_CTRL:
	हाल RT5665_PDM_DATA_CTRL_1:
	हाल RT5665_PDM_DATA_CTRL_2:
	हाल RT5665_PDM_DATA_CTRL_3:
	हाल RT5665_PDM_DATA_CTRL_4:
	हाल RT5665_REC1_GAIN:
	हाल RT5665_REC1_L1_MIXER:
	हाल RT5665_REC1_L2_MIXER:
	हाल RT5665_REC1_R1_MIXER:
	हाल RT5665_REC1_R2_MIXER:
	हाल RT5665_REC2_GAIN:
	हाल RT5665_REC2_L1_MIXER:
	हाल RT5665_REC2_L2_MIXER:
	हाल RT5665_REC2_R1_MIXER:
	हाल RT5665_REC2_R2_MIXER:
	हाल RT5665_CAL_REC:
	हाल RT5665_ALC_BACK_GAIN:
	हाल RT5665_MONOMIX_GAIN:
	हाल RT5665_MONOMIX_IN_GAIN:
	हाल RT5665_OUT_L_GAIN:
	हाल RT5665_OUT_L_MIXER:
	हाल RT5665_OUT_R_GAIN:
	हाल RT5665_OUT_R_MIXER:
	हाल RT5665_LOUT_MIXER:
	हाल RT5665_PWR_DIG_1:
	हाल RT5665_PWR_DIG_2:
	हाल RT5665_PWR_ANLG_1:
	हाल RT5665_PWR_ANLG_2:
	हाल RT5665_PWR_ANLG_3:
	हाल RT5665_PWR_MIXER:
	हाल RT5665_PWR_VOL:
	हाल RT5665_CLK_DET:
	हाल RT5665_HPF_CTRL1:
	हाल RT5665_DMIC_CTRL_1:
	हाल RT5665_DMIC_CTRL_2:
	हाल RT5665_I2S1_SDP:
	हाल RT5665_I2S2_SDP:
	हाल RT5665_I2S3_SDP:
	हाल RT5665_ADDA_CLK_1:
	हाल RT5665_ADDA_CLK_2:
	हाल RT5665_I2S1_F_DIV_CTRL_1:
	हाल RT5665_I2S1_F_DIV_CTRL_2:
	हाल RT5665_TDM_CTRL_1:
	हाल RT5665_TDM_CTRL_2:
	हाल RT5665_TDM_CTRL_3:
	हाल RT5665_TDM_CTRL_4:
	हाल RT5665_TDM_CTRL_5:
	हाल RT5665_TDM_CTRL_6:
	हाल RT5665_TDM_CTRL_7:
	हाल RT5665_TDM_CTRL_8:
	हाल RT5665_GLB_CLK:
	हाल RT5665_PLL_CTRL_1:
	हाल RT5665_PLL_CTRL_2:
	हाल RT5665_ASRC_1:
	हाल RT5665_ASRC_2:
	हाल RT5665_ASRC_3:
	हाल RT5665_ASRC_4:
	हाल RT5665_ASRC_5:
	हाल RT5665_ASRC_6:
	हाल RT5665_ASRC_7:
	हाल RT5665_ASRC_8:
	हाल RT5665_ASRC_9:
	हाल RT5665_ASRC_10:
	हाल RT5665_DEPOP_1:
	हाल RT5665_DEPOP_2:
	हाल RT5665_HP_CHARGE_PUMP_1:
	हाल RT5665_HP_CHARGE_PUMP_2:
	हाल RT5665_MICBIAS_1:
	हाल RT5665_MICBIAS_2:
	हाल RT5665_ASRC_12:
	हाल RT5665_ASRC_13:
	हाल RT5665_ASRC_14:
	हाल RT5665_RC_CLK_CTRL:
	हाल RT5665_I2S_M_CLK_CTRL_1:
	हाल RT5665_I2S2_F_DIV_CTRL_1:
	हाल RT5665_I2S2_F_DIV_CTRL_2:
	हाल RT5665_I2S3_F_DIV_CTRL_1:
	हाल RT5665_I2S3_F_DIV_CTRL_2:
	हाल RT5665_EQ_CTRL_1:
	हाल RT5665_EQ_CTRL_2:
	हाल RT5665_IRQ_CTRL_1:
	हाल RT5665_IRQ_CTRL_2:
	हाल RT5665_IRQ_CTRL_3:
	हाल RT5665_IRQ_CTRL_4:
	हाल RT5665_IRQ_CTRL_5:
	हाल RT5665_IRQ_CTRL_6:
	हाल RT5665_INT_ST_1:
	हाल RT5665_GPIO_CTRL_1:
	हाल RT5665_GPIO_CTRL_2:
	हाल RT5665_GPIO_CTRL_3:
	हाल RT5665_GPIO_CTRL_4:
	हाल RT5665_GPIO_STA:
	हाल RT5665_HP_AMP_DET_CTRL_1:
	हाल RT5665_HP_AMP_DET_CTRL_2:
	हाल RT5665_MID_HP_AMP_DET:
	हाल RT5665_LOW_HP_AMP_DET:
	हाल RT5665_SV_ZCD_1:
	हाल RT5665_SV_ZCD_2:
	हाल RT5665_IL_CMD_1:
	हाल RT5665_IL_CMD_2:
	हाल RT5665_IL_CMD_3:
	हाल RT5665_IL_CMD_4:
	हाल RT5665_4BTN_IL_CMD_1:
	हाल RT5665_4BTN_IL_CMD_2:
	हाल RT5665_4BTN_IL_CMD_3:
	हाल RT5665_PSV_IL_CMD_1:
	हाल RT5665_ADC_STO1_HP_CTRL_1:
	हाल RT5665_ADC_STO1_HP_CTRL_2:
	हाल RT5665_ADC_MONO_HP_CTRL_1:
	हाल RT5665_ADC_MONO_HP_CTRL_2:
	हाल RT5665_ADC_STO2_HP_CTRL_1:
	हाल RT5665_ADC_STO2_HP_CTRL_2:
	हाल RT5665_AJD1_CTRL:
	हाल RT5665_JD1_THD:
	हाल RT5665_JD2_THD:
	हाल RT5665_JD_CTRL_1:
	हाल RT5665_JD_CTRL_2:
	हाल RT5665_JD_CTRL_3:
	हाल RT5665_DIG_MISC:
	हाल RT5665_DUMMY_2:
	हाल RT5665_DUMMY_3:
	हाल RT5665_DAC_ADC_DIG_VOL1:
	हाल RT5665_DAC_ADC_DIG_VOL2:
	हाल RT5665_BIAS_CUR_CTRL_1:
	हाल RT5665_BIAS_CUR_CTRL_2:
	हाल RT5665_BIAS_CUR_CTRL_3:
	हाल RT5665_BIAS_CUR_CTRL_4:
	हाल RT5665_BIAS_CUR_CTRL_5:
	हाल RT5665_BIAS_CUR_CTRL_6:
	हाल RT5665_BIAS_CUR_CTRL_7:
	हाल RT5665_BIAS_CUR_CTRL_8:
	हाल RT5665_BIAS_CUR_CTRL_9:
	हाल RT5665_BIAS_CUR_CTRL_10:
	हाल RT5665_VREF_REC_OP_FB_CAP_CTRL:
	हाल RT5665_CHARGE_PUMP_1:
	हाल RT5665_DIG_IN_CTRL_1:
	हाल RT5665_DIG_IN_CTRL_2:
	हाल RT5665_PAD_DRIVING_CTRL:
	हाल RT5665_SOFT_RAMP_DEPOP:
	हाल RT5665_PLL:
	हाल RT5665_CHOP_DAC:
	हाल RT5665_CHOP_ADC:
	हाल RT5665_CALIB_ADC_CTRL:
	हाल RT5665_VOL_TEST:
	हाल RT5665_TEST_MODE_CTRL_1:
	हाल RT5665_TEST_MODE_CTRL_2:
	हाल RT5665_TEST_MODE_CTRL_3:
	हाल RT5665_TEST_MODE_CTRL_4:
	हाल RT5665_BASSBACK_CTRL:
	हाल RT5665_STO_NG2_CTRL_1:
	हाल RT5665_STO_NG2_CTRL_2:
	हाल RT5665_STO_NG2_CTRL_3:
	हाल RT5665_STO_NG2_CTRL_4:
	हाल RT5665_STO_NG2_CTRL_5:
	हाल RT5665_STO_NG2_CTRL_6:
	हाल RT5665_STO_NG2_CTRL_7:
	हाल RT5665_STO_NG2_CTRL_8:
	हाल RT5665_MONO_NG2_CTRL_1:
	हाल RT5665_MONO_NG2_CTRL_2:
	हाल RT5665_MONO_NG2_CTRL_3:
	हाल RT5665_MONO_NG2_CTRL_4:
	हाल RT5665_MONO_NG2_CTRL_5:
	हाल RT5665_MONO_NG2_CTRL_6:
	हाल RT5665_STO1_DAC_SIL_DET:
	हाल RT5665_MONOL_DAC_SIL_DET:
	हाल RT5665_MONOR_DAC_SIL_DET:
	हाल RT5665_STO2_DAC_SIL_DET:
	हाल RT5665_SIL_PSV_CTRL1:
	हाल RT5665_SIL_PSV_CTRL2:
	हाल RT5665_SIL_PSV_CTRL3:
	हाल RT5665_SIL_PSV_CTRL4:
	हाल RT5665_SIL_PSV_CTRL5:
	हाल RT5665_SIL_PSV_CTRL6:
	हाल RT5665_MONO_AMP_CALIB_CTRL_1:
	हाल RT5665_MONO_AMP_CALIB_CTRL_2:
	हाल RT5665_MONO_AMP_CALIB_CTRL_3:
	हाल RT5665_MONO_AMP_CALIB_CTRL_4:
	हाल RT5665_MONO_AMP_CALIB_CTRL_5:
	हाल RT5665_MONO_AMP_CALIB_CTRL_6:
	हाल RT5665_MONO_AMP_CALIB_CTRL_7:
	हाल RT5665_MONO_AMP_CALIB_STA1:
	हाल RT5665_MONO_AMP_CALIB_STA2:
	हाल RT5665_MONO_AMP_CALIB_STA3:
	हाल RT5665_MONO_AMP_CALIB_STA4:
	हाल RT5665_MONO_AMP_CALIB_STA6:
	हाल RT5665_HP_IMP_SENS_CTRL_01:
	हाल RT5665_HP_IMP_SENS_CTRL_02:
	हाल RT5665_HP_IMP_SENS_CTRL_03:
	हाल RT5665_HP_IMP_SENS_CTRL_04:
	हाल RT5665_HP_IMP_SENS_CTRL_05:
	हाल RT5665_HP_IMP_SENS_CTRL_06:
	हाल RT5665_HP_IMP_SENS_CTRL_07:
	हाल RT5665_HP_IMP_SENS_CTRL_08:
	हाल RT5665_HP_IMP_SENS_CTRL_09:
	हाल RT5665_HP_IMP_SENS_CTRL_10:
	हाल RT5665_HP_IMP_SENS_CTRL_11:
	हाल RT5665_HP_IMP_SENS_CTRL_12:
	हाल RT5665_HP_IMP_SENS_CTRL_13:
	हाल RT5665_HP_IMP_SENS_CTRL_14:
	हाल RT5665_HP_IMP_SENS_CTRL_15:
	हाल RT5665_HP_IMP_SENS_CTRL_16:
	हाल RT5665_HP_IMP_SENS_CTRL_17:
	हाल RT5665_HP_IMP_SENS_CTRL_18:
	हाल RT5665_HP_IMP_SENS_CTRL_19:
	हाल RT5665_HP_IMP_SENS_CTRL_20:
	हाल RT5665_HP_IMP_SENS_CTRL_21:
	हाल RT5665_HP_IMP_SENS_CTRL_22:
	हाल RT5665_HP_IMP_SENS_CTRL_23:
	हाल RT5665_HP_IMP_SENS_CTRL_24:
	हाल RT5665_HP_IMP_SENS_CTRL_25:
	हाल RT5665_HP_IMP_SENS_CTRL_26:
	हाल RT5665_HP_IMP_SENS_CTRL_27:
	हाल RT5665_HP_IMP_SENS_CTRL_28:
	हाल RT5665_HP_IMP_SENS_CTRL_29:
	हाल RT5665_HP_IMP_SENS_CTRL_30:
	हाल RT5665_HP_IMP_SENS_CTRL_31:
	हाल RT5665_HP_IMP_SENS_CTRL_32:
	हाल RT5665_HP_IMP_SENS_CTRL_33:
	हाल RT5665_HP_IMP_SENS_CTRL_34:
	हाल RT5665_HP_LOGIC_CTRL_1:
	हाल RT5665_HP_LOGIC_CTRL_2:
	हाल RT5665_HP_LOGIC_CTRL_3:
	हाल RT5665_HP_CALIB_CTRL_1:
	हाल RT5665_HP_CALIB_CTRL_2:
	हाल RT5665_HP_CALIB_CTRL_3:
	हाल RT5665_HP_CALIB_CTRL_4:
	हाल RT5665_HP_CALIB_CTRL_5:
	हाल RT5665_HP_CALIB_CTRL_6:
	हाल RT5665_HP_CALIB_CTRL_7:
	हाल RT5665_HP_CALIB_CTRL_9:
	हाल RT5665_HP_CALIB_CTRL_10:
	हाल RT5665_HP_CALIB_CTRL_11:
	हाल RT5665_HP_CALIB_STA_1:
	हाल RT5665_HP_CALIB_STA_2:
	हाल RT5665_HP_CALIB_STA_3:
	हाल RT5665_HP_CALIB_STA_4:
	हाल RT5665_HP_CALIB_STA_5:
	हाल RT5665_HP_CALIB_STA_6:
	हाल RT5665_HP_CALIB_STA_7:
	हाल RT5665_HP_CALIB_STA_8:
	हाल RT5665_HP_CALIB_STA_9:
	हाल RT5665_HP_CALIB_STA_10:
	हाल RT5665_HP_CALIB_STA_11:
	हाल RT5665_PGM_TAB_CTRL1:
	हाल RT5665_PGM_TAB_CTRL2:
	हाल RT5665_PGM_TAB_CTRL3:
	हाल RT5665_PGM_TAB_CTRL4:
	हाल RT5665_PGM_TAB_CTRL5:
	हाल RT5665_PGM_TAB_CTRL6:
	हाल RT5665_PGM_TAB_CTRL7:
	हाल RT5665_PGM_TAB_CTRL8:
	हाल RT5665_PGM_TAB_CTRL9:
	हाल RT5665_SAR_IL_CMD_1:
	हाल RT5665_SAR_IL_CMD_2:
	हाल RT5665_SAR_IL_CMD_3:
	हाल RT5665_SAR_IL_CMD_4:
	हाल RT5665_SAR_IL_CMD_5:
	हाल RT5665_SAR_IL_CMD_6:
	हाल RT5665_SAR_IL_CMD_7:
	हाल RT5665_SAR_IL_CMD_8:
	हाल RT5665_SAR_IL_CMD_9:
	हाल RT5665_SAR_IL_CMD_10:
	हाल RT5665_SAR_IL_CMD_11:
	हाल RT5665_SAR_IL_CMD_12:
	हाल RT5665_DRC1_CTRL_0:
	हाल RT5665_DRC1_CTRL_1:
	हाल RT5665_DRC1_CTRL_2:
	हाल RT5665_DRC1_CTRL_3:
	हाल RT5665_DRC1_CTRL_4:
	हाल RT5665_DRC1_CTRL_5:
	हाल RT5665_DRC1_CTRL_6:
	हाल RT5665_DRC1_HARD_LMT_CTRL_1:
	हाल RT5665_DRC1_HARD_LMT_CTRL_2:
	हाल RT5665_DRC1_PRIV_1:
	हाल RT5665_DRC1_PRIV_2:
	हाल RT5665_DRC1_PRIV_3:
	हाल RT5665_DRC1_PRIV_4:
	हाल RT5665_DRC1_PRIV_5:
	हाल RT5665_DRC1_PRIV_6:
	हाल RT5665_DRC1_PRIV_7:
	हाल RT5665_DRC1_PRIV_8:
	हाल RT5665_ALC_PGA_CTRL_1:
	हाल RT5665_ALC_PGA_CTRL_2:
	हाल RT5665_ALC_PGA_CTRL_3:
	हाल RT5665_ALC_PGA_CTRL_4:
	हाल RT5665_ALC_PGA_CTRL_5:
	हाल RT5665_ALC_PGA_CTRL_6:
	हाल RT5665_ALC_PGA_CTRL_7:
	हाल RT5665_ALC_PGA_CTRL_8:
	हाल RT5665_ALC_PGA_STA_1:
	हाल RT5665_ALC_PGA_STA_2:
	हाल RT5665_ALC_PGA_STA_3:
	हाल RT5665_EQ_AUTO_RCV_CTRL1:
	हाल RT5665_EQ_AUTO_RCV_CTRL2:
	हाल RT5665_EQ_AUTO_RCV_CTRL3:
	हाल RT5665_EQ_AUTO_RCV_CTRL4:
	हाल RT5665_EQ_AUTO_RCV_CTRL5:
	हाल RT5665_EQ_AUTO_RCV_CTRL6:
	हाल RT5665_EQ_AUTO_RCV_CTRL7:
	हाल RT5665_EQ_AUTO_RCV_CTRL8:
	हाल RT5665_EQ_AUTO_RCV_CTRL9:
	हाल RT5665_EQ_AUTO_RCV_CTRL10:
	हाल RT5665_EQ_AUTO_RCV_CTRL11:
	हाल RT5665_EQ_AUTO_RCV_CTRL12:
	हाल RT5665_EQ_AUTO_RCV_CTRL13:
	हाल RT5665_ADC_L_EQ_LPF1_A1:
	हाल RT5665_R_EQ_LPF1_A1:
	हाल RT5665_L_EQ_LPF1_H0:
	हाल RT5665_R_EQ_LPF1_H0:
	हाल RT5665_L_EQ_BPF1_A1:
	हाल RT5665_R_EQ_BPF1_A1:
	हाल RT5665_L_EQ_BPF1_A2:
	हाल RT5665_R_EQ_BPF1_A2:
	हाल RT5665_L_EQ_BPF1_H0:
	हाल RT5665_R_EQ_BPF1_H0:
	हाल RT5665_L_EQ_BPF2_A1:
	हाल RT5665_R_EQ_BPF2_A1:
	हाल RT5665_L_EQ_BPF2_A2:
	हाल RT5665_R_EQ_BPF2_A2:
	हाल RT5665_L_EQ_BPF2_H0:
	हाल RT5665_R_EQ_BPF2_H0:
	हाल RT5665_L_EQ_BPF3_A1:
	हाल RT5665_R_EQ_BPF3_A1:
	हाल RT5665_L_EQ_BPF3_A2:
	हाल RT5665_R_EQ_BPF3_A2:
	हाल RT5665_L_EQ_BPF3_H0:
	हाल RT5665_R_EQ_BPF3_H0:
	हाल RT5665_L_EQ_BPF4_A1:
	हाल RT5665_R_EQ_BPF4_A1:
	हाल RT5665_L_EQ_BPF4_A2:
	हाल RT5665_R_EQ_BPF4_A2:
	हाल RT5665_L_EQ_BPF4_H0:
	हाल RT5665_R_EQ_BPF4_H0:
	हाल RT5665_L_EQ_HPF1_A1:
	हाल RT5665_R_EQ_HPF1_A1:
	हाल RT5665_L_EQ_HPF1_H0:
	हाल RT5665_R_EQ_HPF1_H0:
	हाल RT5665_L_EQ_PRE_VOL:
	हाल RT5665_R_EQ_PRE_VOL:
	हाल RT5665_L_EQ_POST_VOL:
	हाल RT5665_R_EQ_POST_VOL:
	हाल RT5665_SCAN_MODE_CTRL:
	हाल RT5665_I2C_MODE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(hp_vol_tlv, -2250, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mono_vol_tlv, -1400, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -65625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -17625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_bst_tlv, -1200, 75, 0);

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
अटल स्थिर अक्षर * स्थिर rt5665_data_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_1_01_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_1_DS_ADC_SLOT01_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_1_23_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_1_DS_ADC_SLOT23_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_1_45_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_1_DS_ADC_SLOT45_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_1_67_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_1_DS_ADC_SLOT67_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_2_01_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_2_DS_ADC_SLOT01_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_2_23_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_2_DS_ADC_SLOT23_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_2_45_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_2_DS_ADC_SLOT45_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर1_2_67_adc_क्रमागत,
	RT5665_TDM_CTRL_2, RT5665_I2S1_2_DS_ADC_SLOT67_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर2_1_dac_क्रमागत,
	RT5665_DIG_INF2_DATA, RT5665_IF2_1_DAC_SEL_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर2_1_adc_क्रमागत,
	RT5665_DIG_INF2_DATA, RT5665_IF2_1_ADC_SEL_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर2_2_dac_क्रमागत,
	RT5665_DIG_INF2_DATA, RT5665_IF2_2_DAC_SEL_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर2_2_adc_क्रमागत,
	RT5665_DIG_INF2_DATA, RT5665_IF2_2_ADC_SEL_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर3_dac_क्रमागत,
	RT5665_DIG_INF3_DATA, RT5665_IF3_DAC_SEL_SFT, rt5665_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5665_अगर3_adc_क्रमागत,
	RT5665_DIG_INF3_DATA, RT5665_IF3_ADC_SEL_SFT, rt5665_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_01_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_1 01 ADC Swap Mux", rt5665_अगर1_1_01_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_23_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_1 23 ADC Swap Mux", rt5665_अगर1_1_23_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_45_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_1 45 ADC Swap Mux", rt5665_अगर1_1_45_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_67_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_1 67 ADC Swap Mux", rt5665_अगर1_1_67_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_01_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_2 01 ADC Swap Mux", rt5665_अगर1_2_01_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_23_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_2 23 ADC1 Swap Mux", rt5665_अगर1_2_23_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_45_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_2 45 ADC1 Swap Mux", rt5665_अगर1_2_45_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_67_adc_swap_mux =
	SOC_DAPM_ENUM("IF1_2 67 ADC1 Swap Mux", rt5665_अगर1_2_67_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_1_dac_swap_mux =
	SOC_DAPM_ENUM("IF2_1 DAC Swap Source", rt5665_अगर2_1_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_1_adc_swap_mux =
	SOC_DAPM_ENUM("IF2_1 ADC Swap Source", rt5665_अगर2_1_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_2_dac_swap_mux =
	SOC_DAPM_ENUM("IF2_2 DAC Swap Source", rt5665_अगर2_2_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_2_adc_swap_mux =
	SOC_DAPM_ENUM("IF2_2 ADC Swap Source", rt5665_अगर2_2_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर3_dac_swap_mux =
	SOC_DAPM_ENUM("IF3 DAC Swap Source", rt5665_अगर3_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर3_adc_swap_mux =
	SOC_DAPM_ENUM("IF3 ADC Swap Source", rt5665_अगर3_adc_क्रमागत);

अटल पूर्णांक rt5665_hp_vol_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक ret = snd_soc_put_volsw(kcontrol, ucontrol);

	अगर (snd_soc_component_पढ़ो(component, RT5665_STO_NG2_CTRL_1) & RT5665_NG2_EN) अणु
		snd_soc_component_update_bits(component, RT5665_STO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		snd_soc_component_update_bits(component, RT5665_STO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rt5665_mono_vol_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक ret = snd_soc_put_volsw(kcontrol, ucontrol);

	अगर (snd_soc_component_पढ़ो(component, RT5665_MONO_NG2_CTRL_1) & RT5665_NG2_EN) अणु
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rt5665_sel_asrc_clk_src - select ASRC घड़ी source क्रम a set of filters
 * @component: SoC audio component device.
 * @filter_mask: mask of filters.
 * @clk_src: घड़ी source
 *
 * The ASRC function is क्रम asynchronous MCLK and LRCK. Also, since RT5665 can
 * only support standard 32fs or 64fs i2s क्रमmat, ASRC should be enabled to
 * support special i2s घड़ी क्रमmat such as Intel's 100fs(100 * sampling rate).
 * ASRC function will track i2s घड़ी and generate a corresponding प्रणाली घड़ी
 * क्रम codec. This function provides an API to select the घड़ी source क्रम a
 * set of filters specअगरied by the mask. And the codec driver will turn on ASRC
 * क्रम these filters अगर ASRC is selected as their घड़ी source.
 */
पूर्णांक rt5665_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	अचिन्हित पूर्णांक asrc2_mask = 0;
	अचिन्हित पूर्णांक asrc2_value = 0;
	अचिन्हित पूर्णांक asrc3_mask = 0;
	अचिन्हित पूर्णांक asrc3_value = 0;

	चयन (clk_src) अणु
	हाल RT5665_CLK_SEL_SYS:
	हाल RT5665_CLK_SEL_I2S1_ASRC:
	हाल RT5665_CLK_SEL_I2S2_ASRC:
	हाल RT5665_CLK_SEL_I2S3_ASRC:
	हाल RT5665_CLK_SEL_SYS2:
	हाल RT5665_CLK_SEL_SYS3:
	हाल RT5665_CLK_SEL_SYS4:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (filter_mask & RT5665_DA_STEREO1_FILTER) अणु
		asrc2_mask |= RT5665_DA_STO1_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5665_DA_STO1_CLK_SEL_MASK)
			| (clk_src << RT5665_DA_STO1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_DA_STEREO2_FILTER) अणु
		asrc2_mask |= RT5665_DA_STO2_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5665_DA_STO2_CLK_SEL_MASK)
			| (clk_src << RT5665_DA_STO2_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_DA_MONO_L_FILTER) अणु
		asrc2_mask |= RT5665_DA_MONOL_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5665_DA_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5665_DA_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_DA_MONO_R_FILTER) अणु
		asrc2_mask |= RT5665_DA_MONOR_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5665_DA_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5665_DA_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_AD_STEREO1_FILTER) अणु
		asrc3_mask |= RT5665_AD_STO1_CLK_SEL_MASK;
		asrc3_value = (asrc2_value & ~RT5665_AD_STO1_CLK_SEL_MASK)
			| (clk_src << RT5665_AD_STO1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_AD_STEREO2_FILTER) अणु
		asrc3_mask |= RT5665_AD_STO2_CLK_SEL_MASK;
		asrc3_value = (asrc2_value & ~RT5665_AD_STO2_CLK_SEL_MASK)
			| (clk_src << RT5665_AD_STO2_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_AD_MONO_L_FILTER) अणु
		asrc3_mask |= RT5665_AD_MONOL_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5665_AD_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5665_AD_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5665_AD_MONO_R_FILTER)  अणु
		asrc3_mask |= RT5665_AD_MONOR_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5665_AD_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5665_AD_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc2_mask)
		snd_soc_component_update_bits(component, RT5665_ASRC_2,
			asrc2_mask, asrc2_value);

	अगर (asrc3_mask)
		snd_soc_component_update_bits(component, RT5665_ASRC_3,
			asrc3_mask, asrc3_value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5665_sel_asrc_clk_src);

अटल पूर्णांक rt5665_button_detect(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक btn_type, val;

	val = snd_soc_component_पढ़ो(component, RT5665_4BTN_IL_CMD_1);
	btn_type = val & 0xfff0;
	snd_soc_component_ग_लिखो(component, RT5665_4BTN_IL_CMD_1, val);

	वापस btn_type;
पूर्ण

अटल व्योम rt5665_enable_push_button_irq(काष्ठा snd_soc_component *component,
	bool enable)
अणु
	अगर (enable) अणु
		snd_soc_component_ग_लिखो(component, RT5665_4BTN_IL_CMD_1, 0x0003);
		snd_soc_component_update_bits(component, RT5665_SAR_IL_CMD_9, 0x1, 0x1);
		snd_soc_component_ग_लिखो(component, RT5665_IL_CMD_1, 0x0048);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_MASK | RT5665_4BTN_IL_RST_MASK,
				RT5665_4BTN_IL_EN | RT5665_4BTN_IL_NOR);
		snd_soc_component_update_bits(component, RT5665_IRQ_CTRL_3,
				RT5665_IL_IRQ_MASK, RT5665_IL_IRQ_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5665_IRQ_CTRL_3,
				RT5665_IL_IRQ_MASK, RT5665_IL_IRQ_DIS);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_MASK, RT5665_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_RST_MASK, RT5665_4BTN_IL_RST);
	पूर्ण
पूर्ण

/**
 * rt5665_headset_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insert: Jack insert or not.
 *
 * Detect whether is headset or not when jack inserted.
 *
 * Returns detect status.
 */
अटल पूर्णांक rt5665_headset_detect(काष्ठा snd_soc_component *component, पूर्णांक jack_insert)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	अचिन्हित पूर्णांक sar_hs_type, val;

	अगर (jack_insert) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_sync(dapm);

		regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2, 0x100,
			0x100);

		regmap_पढ़ो(rt5665->regmap, RT5665_GPIO_STA, &val);
		अगर (val & 0x4) अणु
			regmap_update_bits(rt5665->regmap, RT5665_EJD_CTRL_1,
				0x100, 0);

			regmap_पढ़ो(rt5665->regmap, RT5665_GPIO_STA, &val);
			जबतक (val & 0x4) अणु
				usleep_range(10000, 15000);
				regmap_पढ़ो(rt5665->regmap, RT5665_GPIO_STA,
					&val);
			पूर्ण
		पूर्ण

		regmap_update_bits(rt5665->regmap, RT5665_EJD_CTRL_1,
			0x1a0, 0x120);
		regmap_ग_लिखो(rt5665->regmap, RT5665_EJD_CTRL_3, 0x3424);
		regmap_ग_लिखो(rt5665->regmap, RT5665_IL_CMD_1, 0x0048);
		regmap_ग_लिखो(rt5665->regmap, RT5665_SAR_IL_CMD_1, 0xa291);

		usleep_range(10000, 15000);

		rt5665->sar_adc_value = snd_soc_component_पढ़ो(rt5665->component,
			RT5665_SAR_IL_CMD_4) & 0x7ff;

		sar_hs_type = rt5665->pdata.sar_hs_type ?
			rt5665->pdata.sar_hs_type : 729;

		अगर (rt5665->sar_adc_value > sar_hs_type) अणु
			rt5665->jack_type = SND_JACK_HEADSET;
			rt5665_enable_push_button_irq(component, true);
			पूर्ण अन्यथा अणु
			rt5665->jack_type = SND_JACK_HEADPHONE;
			regmap_ग_लिखो(rt5665->regmap, RT5665_SAR_IL_CMD_1,
				0x2291);
			regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2,
				0x100, 0);
			snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
			snd_soc_dapm_sync(dapm);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(rt5665->regmap, RT5665_SAR_IL_CMD_1, 0x2291);
		regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2, 0x100, 0);
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_sync(dapm);
		अगर (rt5665->jack_type == SND_JACK_HEADSET)
			rt5665_enable_push_button_irq(component, false);
		rt5665->jack_type = 0;
	पूर्ण

	dev_dbg(component->dev, "jack_type = %d\n", rt5665->jack_type);
	वापस rt5665->jack_type;
पूर्ण

अटल irqवापस_t rt5665_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5665_priv *rt5665 = data;

	mod_delayed_work(प्रणाली_घातer_efficient_wq,
			   &rt5665->jack_detect_work, msecs_to_jअगरfies(250));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rt5665_jd_check_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5665_priv *rt5665 = container_of(work, काष्ठा rt5665_priv,
		jd_check_work.work);

	अगर (snd_soc_component_पढ़ो(rt5665->component, RT5665_AJD1_CTRL) & 0x0010) अणु
		/* jack out */
		rt5665->jack_type = rt5665_headset_detect(rt5665->component, 0);

		snd_soc_jack_report(rt5665->hs_jack, rt5665->jack_type,
				SND_JACK_HEADSET |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&rt5665->jd_check_work, 500);
	पूर्ण
पूर्ण

अटल पूर्णांक rt5665_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hs_jack, व्योम *data)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	चयन (rt5665->pdata.jd_src) अणु
	हाल RT5665_JD1:
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_1,
			RT5665_GP1_PIN_MASK, RT5665_GP1_PIN_IRQ);
		regmap_update_bits(rt5665->regmap, RT5665_RC_CLK_CTRL,
				0xc000, 0xc000);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_2,
			RT5665_PWR_JD1, RT5665_PWR_JD1);
		regmap_update_bits(rt5665->regmap, RT5665_IRQ_CTRL_1, 0x8, 0x8);
		अवरोध;

	हाल RT5665_JD_शून्य:
		अवरोध;

	शेष:
		dev_warn(component->dev, "Wrong JD source\n");
		अवरोध;
	पूर्ण

	rt5665->hs_jack = hs_jack;

	वापस 0;
पूर्ण

अटल व्योम rt5665_jack_detect_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5665_priv *rt5665 =
		container_of(work, काष्ठा rt5665_priv, jack_detect_work.work);
	पूर्णांक val, btn_type;

	जबतक (!rt5665->component) अणु
		pr_debug("%s codec = null\n", __func__);
		usleep_range(10000, 15000);
	पूर्ण

	जबतक (!rt5665->component->card->instantiated) अणु
		pr_debug("%s\n", __func__);
		usleep_range(10000, 15000);
	पूर्ण

	जबतक (!rt5665->calibration_करोne) अणु
		pr_debug("%s calibration not ready\n", __func__);
		usleep_range(10000, 15000);
	पूर्ण

	mutex_lock(&rt5665->calibrate_mutex);

	val = snd_soc_component_पढ़ो(rt5665->component, RT5665_AJD1_CTRL) & 0x0010;
	अगर (!val) अणु
		/* jack in */
		अगर (rt5665->jack_type == 0) अणु
			/* jack was out, report jack type */
			rt5665->jack_type =
				rt5665_headset_detect(rt5665->component, 1);
		पूर्ण अन्यथा अणु
			/* jack is alपढ़ोy in, report button event */
			rt5665->jack_type = SND_JACK_HEADSET;
			btn_type = rt5665_button_detect(rt5665->component);
			/**
			 * rt5665 can report three kinds of button behavior,
			 * one click, द्विगुन click and hold. However,
			 * currently we will report button pressed/released
			 * event. So all the three button behaviors are
			 * treated as button pressed.
			 */
			चयन (btn_type) अणु
			हाल 0x8000:
			हाल 0x4000:
			हाल 0x2000:
				rt5665->jack_type |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x1000:
			हाल 0x0800:
			हाल 0x0400:
				rt5665->jack_type |= SND_JACK_BTN_1;
				अवरोध;
			हाल 0x0200:
			हाल 0x0100:
			हाल 0x0080:
				rt5665->jack_type |= SND_JACK_BTN_2;
				अवरोध;
			हाल 0x0040:
			हाल 0x0020:
			हाल 0x0010:
				rt5665->jack_type |= SND_JACK_BTN_3;
				अवरोध;
			हाल 0x0000: /* unpressed */
				अवरोध;
			शेष:
				btn_type = 0;
				dev_err(rt5665->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* jack out */
		rt5665->jack_type = rt5665_headset_detect(rt5665->component, 0);
	पूर्ण

	snd_soc_jack_report(rt5665->hs_jack, rt5665->jack_type,
			SND_JACK_HEADSET |
			    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			    SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (rt5665->jack_type & (SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		SND_JACK_BTN_2 | SND_JACK_BTN_3))
		schedule_delayed_work(&rt5665->jd_check_work, 0);
	अन्यथा
		cancel_delayed_work_sync(&rt5665->jd_check_work);

	mutex_unlock(&rt5665->calibrate_mutex);
पूर्ण

अटल स्थिर अक्षर * स्थिर rt5665_clk_sync[] = अणु
	"I2S1_1", "I2S1_2", "I2S2", "I2S3", "IF2 Slave", "IF3 Slave"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत rt5665_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(RT5665_I2S1_SDP, 11, 5, rt5665_clk_sync),
	SOC_ENUM_SINGLE(RT5665_I2S2_SDP, 11, 5, rt5665_clk_sync),
	SOC_ENUM_SINGLE(RT5665_I2S3_SDP, 11, 5, rt5665_clk_sync),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_snd_controls[] = अणु
	/* Headphone Output Volume */
	SOC_DOUBLE_R_EXT_TLV("Headphone Playback Volume", RT5665_HPL_GAIN,
		RT5665_HPR_GAIN, RT5665_G_HP_SFT, 15, 1, snd_soc_get_volsw,
		rt5665_hp_vol_put, hp_vol_tlv),

	/* Mono Output Volume */
	SOC_SINGLE_EXT_TLV("Mono Playback Volume", RT5665_MONO_GAIN,
		RT5665_L_VOL_SFT, 15, 1, snd_soc_get_volsw,
		rt5665_mono_vol_put, mono_vol_tlv),

	SOC_SINGLE_TLV("MONOVOL Playback Volume", RT5665_MONO_OUT,
		RT5665_L_VOL_SFT, 39, 1, out_vol_tlv),

	/* Output Volume */
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5665_LOUT, RT5665_L_VOL_SFT,
		RT5665_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5665_DAC1_DIG_VOL,
		RT5665_L_VOL_SFT, RT5665_R_VOL_SFT, 175, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("DAC2 Playback Volume", RT5665_DAC2_DIG_VOL,
		RT5665_L_VOL_SFT, RT5665_R_VOL_SFT, 175, 0, dac_vol_tlv),
	SOC_DOUBLE("DAC2 Playback Switch", RT5665_DAC2_CTRL,
		RT5665_M_DAC2_L_VOL_SFT, RT5665_M_DAC2_R_VOL_SFT, 1, 1),

	/* IN1/IN2/IN3/IN4 Volume */
	SOC_SINGLE_TLV("IN1 Boost Volume", RT5665_IN1_IN2,
		RT5665_BST1_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost Volume", RT5665_IN1_IN2,
		RT5665_BST2_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN3 Boost Volume", RT5665_IN3_IN4,
		RT5665_BST3_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN4 Boost Volume", RT5665_IN3_IN4,
		RT5665_BST4_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("CBJ Boost Volume", RT5665_CBJ_BST_CTRL,
		RT5665_BST_CBJ_SFT, 8, 0, bst_tlv),

	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5665_INL1_INR1_VOL,
		RT5665_INL_VOL_SFT, RT5665_INR_VOL_SFT, 31, 1, in_vol_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("STO1 ADC Capture Switch", RT5665_STO1_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, RT5665_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("STO1 ADC Capture Volume", RT5665_STO1_ADC_DIG_VOL,
		RT5665_L_VOL_SFT, RT5665_R_VOL_SFT, 127, 0, adc_vol_tlv),
	SOC_DOUBLE("Mono ADC Capture Switch", RT5665_MONO_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, RT5665_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5665_MONO_ADC_DIG_VOL,
		RT5665_L_VOL_SFT, RT5665_R_VOL_SFT, 127, 0, adc_vol_tlv),
	SOC_DOUBLE("STO2 ADC Capture Switch", RT5665_STO2_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, RT5665_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("STO2 ADC Capture Volume", RT5665_STO2_ADC_DIG_VOL,
		RT5665_L_VOL_SFT, RT5665_R_VOL_SFT, 127, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Gain Volume", RT5665_STO1_ADC_BOOST,
		RT5665_STO1_ADC_L_BST_SFT, RT5665_STO1_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	SOC_DOUBLE_TLV("Mono ADC Boost Gain Volume", RT5665_MONO_ADC_BOOST,
		RT5665_MONO_ADC_L_BST_SFT, RT5665_MONO_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	SOC_DOUBLE_TLV("STO2 ADC Boost Gain Volume", RT5665_STO2_ADC_BOOST,
		RT5665_STO2_ADC_L_BST_SFT, RT5665_STO2_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	/* I2S3 CLK Source */
	SOC_ENUM("I2S1 Master Clk Sel", rt5665_क्रमागत[0]),
	SOC_ENUM("I2S2 Master Clk Sel", rt5665_क्रमागत[1]),
	SOC_ENUM("I2S3 Master Clk Sel", rt5665_क्रमागत[2]),
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
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	पूर्णांक pd, idx;

	pd = rl6231_get_pre_भाग(rt5665->regmap,
		RT5665_ADDA_CLK_1, RT5665_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rt5665->sysclk / pd);

	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा अणु
		snd_soc_component_update_bits(component, RT5665_DMIC_CTRL_1,
			RT5665_DMIC_CLK_MASK, idx << RT5665_DMIC_CLK_SFT);
	पूर्ण
	वापस idx;
पूर्ण

अटल पूर्णांक rt5665_अक्षरge_pump_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5665_HP_CHARGE_PUMP_1,
			RT5665_PM_HP_MASK | RT5665_OSW_L_MASK,
			RT5665_PM_HP_HV | RT5665_OSW_L_EN);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5665_HP_CHARGE_PUMP_1,
			RT5665_PM_HP_MASK | RT5665_OSW_L_MASK,
			RT5665_PM_HP_LV | RT5665_OSW_L_DIS);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	val = snd_soc_component_पढ़ो(component, RT5665_GLB_CLK);
	val &= RT5665_SCLK_SRC_MASK;
	अगर (val == RT5665_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक reg, shअगरt, val;
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (w->shअगरt) अणु
	हाल RT5665_ADC_MONO_R_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shअगरt = RT5665_AD_MONOR_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_ADC_MONO_L_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shअगरt = RT5665_AD_MONOL_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_ADC_STO1_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shअगरt = RT5665_AD_STO1_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_ADC_STO2_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shअगरt = RT5665_AD_STO2_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_DAC_MONO_R_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shअगरt = RT5665_DA_MONOR_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_DAC_MONO_L_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shअगरt = RT5665_DA_MONOL_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_DAC_STO1_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shअगरt = RT5665_DA_STO1_CLK_SEL_SFT;
		अवरोध;
	हाल RT5665_DAC_STO2_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shअगरt = RT5665_DA_STO2_CLK_SEL_SFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	val = (snd_soc_component_पढ़ो(component, reg) >> shअगरt) & 0xf;
	चयन (val) अणु
	हाल RT5665_CLK_SEL_I2S1_ASRC:
	हाल RT5665_CLK_SEL_I2S2_ASRC:
	हाल RT5665_CLK_SEL_I2S3_ASRC:
		/* I2S_Pre_Div1 should be 1 in asrc mode */
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_I2S_PD1_MASK, RT5665_I2S_PD1_2);
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_STO1_ADC_MIXER,
			RT5665_M_STO1_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_STO1_ADC_MIXER,
			RT5665_M_STO1_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_STO1_ADC_MIXER,
			RT5665_M_STO1_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_STO1_ADC_MIXER,
			RT5665_M_STO1_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_STO2_ADC_MIXER,
			RT5665_M_STO2_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_STO2_ADC_MIXER,
			RT5665_M_STO2_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_STO2_ADC_MIXER,
			RT5665_M_STO2_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_STO2_ADC_MIXER,
			RT5665_M_STO2_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_MONO_ADC_MIXER,
			RT5665_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_MONO_ADC_MIXER,
			RT5665_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5665_MONO_ADC_MIXER,
			RT5665_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5665_MONO_ADC_MIXER,
			RT5665_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5665_AD_DA_MIXER,
			RT5665_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5665_AD_DA_MIXER,
			RT5665_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5665_AD_DA_MIXER,
			RT5665_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5665_AD_DA_MIXER,
			RT5665_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_L1_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_R1_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_L2_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_R2_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_L1_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_R1_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_L2_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_STO1_DAC_MIXER,
			RT5665_M_DAC_R2_STO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_L1_STO2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_L2_STO2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L3 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_L3_STO2_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_R1_STO2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_R2_STO2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R3 Switch", RT5665_STO2_DAC_MIXER,
			RT5665_M_DAC_R3_STO2_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_L1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_R1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_L2_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_R2_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_L1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_R1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_L2_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_MONO_DAC_MIXER,
			RT5665_M_DAC_R2_MONO_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5665_rec1_l_mix[] = अणु
	SOC_DAPM_SINGLE("CBJ Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_CBJ_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_INL_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_INR_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_BST4_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_BST3_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_BST2_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_REC1_L2_MIXER,
			RT5665_M_BST1_RM1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_rec1_r_mix[] = अणु
	SOC_DAPM_SINGLE("MONOVOL Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_AEC_REF_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_INR_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_BST4_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_BST3_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_BST2_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_REC1_R2_MIXER,
			RT5665_M_BST1_RM1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_rec2_l_mix[] = अणु
	SOC_DAPM_SINGLE("INL Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_INL_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_INR_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("CBJ Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_CBJ_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_BST4_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_BST3_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_BST2_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_REC2_L2_MIXER,
			RT5665_M_BST1_RM2_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_rec2_r_mix[] = अणु
	SOC_DAPM_SINGLE("MONOVOL Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_MONOVOL_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_INL_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_INR_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_BST4_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_BST3_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_BST2_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_REC2_R2_MIXER,
			RT5665_M_BST1_RM2_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_monovol_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_DAC_L2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("RECMIX2L Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_RECMIC2L_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_BST1_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_BST2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_BST3_MM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_OUT_L_MIXER,
			RT5665_M_DAC_L2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5665_OUT_L_MIXER,
			RT5665_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5665_OUT_L_MIXER,
			RT5665_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_OUT_L_MIXER,
			RT5665_M_BST2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_OUT_L_MIXER,
			RT5665_M_BST3_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_OUT_R_MIXER,
			RT5665_M_DAC_R2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5665_OUT_R_MIXER,
			RT5665_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5665_OUT_R_MIXER,
			RT5665_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5665_OUT_R_MIXER,
			RT5665_M_BST3_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5665_OUT_R_MIXER,
			RT5665_M_BST4_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_DAC_L2_MA_SFT, 1, 1),
	SOC_DAPM_SINGLE("MONOVOL Switch", RT5665_MONOMIX_IN_GAIN,
			RT5665_M_MONOVOL_MA_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_lout_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5665_LOUT_MIXER,
			RT5665_M_DAC_L2_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5665_LOUT_MIXER,
			RT5665_M_OV_L_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_lout_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5665_LOUT_MIXER,
			RT5665_M_DAC_R2_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5665_LOUT_MIXER,
			RT5665_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

/*DAC L2, DAC R2*/
/*MX-17 [6:4], MX-17 [2:0]*/
अटल स्थिर अक्षर * स्थिर rt5665_dac2_src[] = अणु
	"IF1 DAC2", "IF2_1 DAC", "IF2_2 DAC", "IF3 DAC", "Mono ADC MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_l2_क्रमागत, RT5665_DAC2_CTRL,
	RT5665_DAC_L2_SEL_SFT, rt5665_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_l2_mux =
	SOC_DAPM_ENUM("Digital DAC L2 Source", rt5665_dac_l2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_r2_क्रमागत, RT5665_DAC2_CTRL,
	RT5665_DAC_R2_SEL_SFT, rt5665_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_r2_mux =
	SOC_DAPM_ENUM("Digital DAC R2 Source", rt5665_dac_r2_क्रमागत);

/*DAC L3, DAC R3*/
/*MX-1B [6:4], MX-1B [2:0]*/
अटल स्थिर अक्षर * स्थिर rt5665_dac3_src[] = अणु
	"IF1 DAC2", "IF2_1 DAC", "IF2_2 DAC", "IF3 DAC", "STO2 ADC MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_l3_क्रमागत, RT5665_DAC3_CTRL,
	RT5665_DAC_L3_SEL_SFT, rt5665_dac3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_l3_mux =
	SOC_DAPM_ENUM("Digital DAC L3 Source", rt5665_dac_l3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_r3_क्रमागत, RT5665_DAC3_CTRL,
	RT5665_DAC_R3_SEL_SFT, rt5665_dac3_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_r3_mux =
	SOC_DAPM_ENUM("Digital DAC R3 Source", rt5665_dac_r3_क्रमागत);

/* STO1 ADC1 Source */
/* MX-26 [13] [5] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_adc1_src[] = अणु
	"DD Mux", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adc1l_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADC1L_SRC_SFT, rt5665_sto1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc1l_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1L Source", rt5665_sto1_adc1l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adc1r_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADC1R_SRC_SFT, rt5665_sto1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc1r_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1L Source", rt5665_sto1_adc1r_क्रमागत);

/* STO1 ADC Source */
/* MX-26 [11:10] [3:2] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_adc_src[] = अणु
	"ADC1 L", "ADC1 R", "ADC2 L", "ADC2 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adcl_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADCL_SRC_SFT, rt5665_sto1_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adcl_mux =
	SOC_DAPM_ENUM("Stereo1 ADCL Source", rt5665_sto1_adcl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adcr_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADCR_SRC_SFT, rt5665_sto1_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adcr_mux =
	SOC_DAPM_ENUM("Stereo1 ADCR Source", rt5665_sto1_adcr_क्रमागत);

/* STO1 ADC2 Source */
/* MX-26 [12] [4] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adc2l_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADC2L_SRC_SFT, rt5665_sto1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc2l_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2L Source", rt5665_sto1_adc2l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_adc2r_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_ADC2R_SRC_SFT, rt5665_sto1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_adc2r_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2R Source", rt5665_sto1_adc2r_क्रमागत);

/* STO1 DMIC Source */
/* MX-26 [8] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_dmic_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_DMIC_SRC_SFT, rt5665_sto1_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC Mux", rt5665_sto1_dmic_क्रमागत);

/* MX-26 [9] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_dd_l_src[] = अणु
	"STO2 DAC", "MONO DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_dd_l_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_DD_L_SRC_SFT, rt5665_sto1_dd_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_dd_l_mux =
	SOC_DAPM_ENUM("Stereo1 DD L Source", rt5665_sto1_dd_l_क्रमागत);

/* MX-26 [1:0] */
अटल स्थिर अक्षर * स्थिर rt5665_sto1_dd_r_src[] = अणु
	"STO2 DAC", "MONO DAC", "AEC REF"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto1_dd_r_क्रमागत, RT5665_STO1_ADC_MIXER,
	RT5665_STO1_DD_R_SRC_SFT, rt5665_sto1_dd_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto1_dd_r_mux =
	SOC_DAPM_ENUM("Stereo1 DD R Source", rt5665_sto1_dd_r_क्रमागत);

/* MONO ADC L2 Source */
/* MX-27 [12] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_adc_l2_src[] = अणु
	"DAC MIXL", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adc_l2_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_L2_SRC_SFT, rt5665_mono_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_l2_mux =
	SOC_DAPM_ENUM("Mono ADC L2 Source", rt5665_mono_adc_l2_क्रमागत);


/* MONO ADC L1 Source */
/* MX-27 [13] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_adc_l1_src[] = अणु
	"DD Mux", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adc_l1_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_L1_SRC_SFT, rt5665_mono_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_l1_mux =
	SOC_DAPM_ENUM("Mono ADC L1 Source", rt5665_mono_adc_l1_क्रमागत);

/* MX-27 [9][1]*/
अटल स्थिर अक्षर * स्थिर rt5665_mono_dd_src[] = अणु
	"STO2 DAC", "MONO DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_dd_l_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_DD_L_SRC_SFT, rt5665_mono_dd_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dd_l_mux =
	SOC_DAPM_ENUM("Mono DD L Source", rt5665_mono_dd_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_dd_r_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_DD_R_SRC_SFT, rt5665_mono_dd_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dd_r_mux =
	SOC_DAPM_ENUM("Mono DD R Source", rt5665_mono_dd_r_क्रमागत);

/* MONO ADC L Source, MONO ADC R Source*/
/* MX-27 [11:10], MX-27 [3:2] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_adc_src[] = अणु
	"ADC1 L", "ADC1 R", "ADC2 L", "ADC2 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adc_l_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_L_SRC_SFT, rt5665_mono_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_l_mux =
	SOC_DAPM_ENUM("Mono ADC L Source", rt5665_mono_adc_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adcr_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_R_SRC_SFT, rt5665_mono_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_r_mux =
	SOC_DAPM_ENUM("Mono ADC R Source", rt5665_mono_adcr_क्रमागत);

/* MONO DMIC L Source */
/* MX-27 [8] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_dmic_l_src[] = अणु
	"DMIC1 L", "DMIC2 L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_dmic_l_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_DMIC_L_SRC_SFT, rt5665_mono_dmic_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dmic_l_mux =
	SOC_DAPM_ENUM("Mono DMIC L Source", rt5665_mono_dmic_l_क्रमागत);

/* MONO ADC R2 Source */
/* MX-27 [4] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_adc_r2_src[] = अणु
	"DAC MIXR", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adc_r2_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_R2_SRC_SFT, rt5665_mono_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_r2_mux =
	SOC_DAPM_ENUM("Mono ADC R2 Source", rt5665_mono_adc_r2_क्रमागत);

/* MONO ADC R1 Source */
/* MX-27 [5] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_adc_r1_src[] = अणु
	"DD Mux", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_adc_r1_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_ADC_R1_SRC_SFT, rt5665_mono_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_adc_r1_mux =
	SOC_DAPM_ENUM("Mono ADC R1 Source", rt5665_mono_adc_r1_क्रमागत);

/* MONO DMIC R Source */
/* MX-27 [0] */
अटल स्थिर अक्षर * स्थिर rt5665_mono_dmic_r_src[] = अणु
	"DMIC1 R", "DMIC2 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_mono_dmic_r_क्रमागत, RT5665_MONO_ADC_MIXER,
	RT5665_MONO_DMIC_R_SRC_SFT, rt5665_mono_dmic_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_mono_dmic_r_mux =
	SOC_DAPM_ENUM("Mono DMIC R Source", rt5665_mono_dmic_r_क्रमागत);


/* STO2 ADC1 Source */
/* MX-28 [13] [5] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_adc1_src[] = अणु
	"DD Mux", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adc1l_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADC1L_SRC_SFT, rt5665_sto2_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc1l_mux =
	SOC_DAPM_ENUM("Stereo2 ADC1L Source", rt5665_sto2_adc1l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adc1r_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADC1R_SRC_SFT, rt5665_sto2_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc1r_mux =
	SOC_DAPM_ENUM("Stereo2 ADC1L Source", rt5665_sto2_adc1r_क्रमागत);

/* STO2 ADC Source */
/* MX-28 [11:10] [3:2] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_adc_src[] = अणु
	"ADC1 L", "ADC1 R", "ADC2 L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adcl_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADCL_SRC_SFT, rt5665_sto2_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adcl_mux =
	SOC_DAPM_ENUM("Stereo2 ADCL Source", rt5665_sto2_adcl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adcr_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADCR_SRC_SFT, rt5665_sto2_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adcr_mux =
	SOC_DAPM_ENUM("Stereo2 ADCR Source", rt5665_sto2_adcr_क्रमागत);

/* STO2 ADC2 Source */
/* MX-28 [12] [4] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adc2l_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADC2L_SRC_SFT, rt5665_sto2_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc2l_mux =
	SOC_DAPM_ENUM("Stereo2 ADC2L Source", rt5665_sto2_adc2l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_adc2r_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_ADC2R_SRC_SFT, rt5665_sto2_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_adc2r_mux =
	SOC_DAPM_ENUM("Stereo2 ADC2R Source", rt5665_sto2_adc2r_क्रमागत);

/* STO2 DMIC Source */
/* MX-28 [8] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_dmic_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_DMIC_SRC_SFT, rt5665_sto2_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_dmic_mux =
	SOC_DAPM_ENUM("Stereo2 DMIC Source", rt5665_sto2_dmic_क्रमागत);

/* MX-28 [9] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_dd_l_src[] = अणु
	"STO2 DAC", "MONO DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_dd_l_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_DD_L_SRC_SFT, rt5665_sto2_dd_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_dd_l_mux =
	SOC_DAPM_ENUM("Stereo2 DD L Source", rt5665_sto2_dd_l_क्रमागत);

/* MX-28 [1] */
अटल स्थिर अक्षर * स्थिर rt5665_sto2_dd_r_src[] = अणु
	"STO2 DAC", "MONO DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_sto2_dd_r_क्रमागत, RT5665_STO2_ADC_MIXER,
	RT5665_STO2_DD_R_SRC_SFT, rt5665_sto2_dd_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_sto2_dd_r_mux =
	SOC_DAPM_ENUM("Stereo2 DD R Source", rt5665_sto2_dd_r_क्रमागत);

/* DAC R1 Source, DAC L1 Source*/
/* MX-29 [11:10], MX-29 [9:8]*/
अटल स्थिर अक्षर * स्थिर rt5665_dac1_src[] = अणु
	"IF1 DAC1", "IF2_1 DAC", "IF2_2 DAC", "IF3 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_r1_क्रमागत, RT5665_AD_DA_MIXER,
	RT5665_DAC1_R_SEL_SFT, rt5665_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_r1_mux =
	SOC_DAPM_ENUM("DAC R1 Source", rt5665_dac_r1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dac_l1_क्रमागत, RT5665_AD_DA_MIXER,
	RT5665_DAC1_L_SEL_SFT, rt5665_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dac_l1_mux =
	SOC_DAPM_ENUM("DAC L1 Source", rt5665_dac_l1_क्रमागत);

/* DAC Digital Mixer L Source, DAC Digital Mixer R Source*/
/* MX-2D [13:12], MX-2D [9:8]*/
अटल स्थिर अक्षर * स्थिर rt5665_dig_dac_mix_src[] = अणु
	"Stereo1 DAC Mixer", "Stereo2 DAC Mixer", "Mono DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dig_dac_mixl_क्रमागत, RT5665_A_DAC1_MUX,
	RT5665_DAC_MIX_L_SFT, rt5665_dig_dac_mix_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dig_dac_mixl_mux =
	SOC_DAPM_ENUM("DAC Digital Mixer L Source", rt5665_dig_dac_mixl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_dig_dac_mixr_क्रमागत, RT5665_A_DAC1_MUX,
	RT5665_DAC_MIX_R_SFT, rt5665_dig_dac_mix_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_dig_dac_mixr_mux =
	SOC_DAPM_ENUM("DAC Digital Mixer R Source", rt5665_dig_dac_mixr_क्रमागत);

/* Analog DAC L1 Source, Analog DAC R1 Source*/
/* MX-2D [5:4], MX-2D [1:0]*/
अटल स्थिर अक्षर * स्थिर rt5665_alg_dac1_src[] = अणु
	"Stereo1 DAC Mixer", "DAC1", "DMIC1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_alg_dac_l1_क्रमागत, RT5665_A_DAC1_MUX,
	RT5665_A_DACL1_SFT, rt5665_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_alg_dac_l1_mux =
	SOC_DAPM_ENUM("Analog DAC L1 Source", rt5665_alg_dac_l1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_alg_dac_r1_क्रमागत, RT5665_A_DAC1_MUX,
	RT5665_A_DACR1_SFT, rt5665_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_alg_dac_r1_mux =
	SOC_DAPM_ENUM("Analog DAC R1 Source", rt5665_alg_dac_r1_क्रमागत);

/* Analog DAC LR Source, Analog DAC R2 Source*/
/* MX-2E [5:4], MX-2E [0]*/
अटल स्थिर अक्षर * स्थिर rt5665_alg_dac2_src[] = अणु
	"Mono DAC Mixer", "DAC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_alg_dac_l2_क्रमागत, RT5665_A_DAC2_MUX,
	RT5665_A_DACL2_SFT, rt5665_alg_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_alg_dac_l2_mux =
	SOC_DAPM_ENUM("Analog DAC L2 Source", rt5665_alg_dac_l2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_alg_dac_r2_क्रमागत, RT5665_A_DAC2_MUX,
	RT5665_A_DACR2_SFT, rt5665_alg_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_alg_dac_r2_mux =
	SOC_DAPM_ENUM("Analog DAC R2 Source", rt5665_alg_dac_r2_क्रमागत);

/* Interface2 ADC Data Input*/
/* MX-2F [14:12] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर2_1_adc_in_src[] = अणु
	"STO1 ADC", "STO2 ADC", "MONO ADC", "IF1 DAC1",
	"IF1 DAC2", "IF2_2 DAC", "IF3 DAC", "DAC1 MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर2_1_adc_in_क्रमागत, RT5665_DIG_INF2_DATA,
	RT5665_IF2_1_ADC_IN_SFT, rt5665_अगर2_1_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_1_adc_in_mux =
	SOC_DAPM_ENUM("IF2_1 ADC IN Source", rt5665_अगर2_1_adc_in_क्रमागत);

/* MX-2F [6:4] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर2_2_adc_in_src[] = अणु
	"STO1 ADC", "STO2 ADC", "MONO ADC", "IF1 DAC1",
	"IF1 DAC2", "IF2_1 DAC", "IF3 DAC", "DAC1 MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर2_2_adc_in_क्रमागत, RT5665_DIG_INF2_DATA,
	RT5665_IF2_2_ADC_IN_SFT, rt5665_अगर2_2_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर2_2_adc_in_mux =
	SOC_DAPM_ENUM("IF2_1 ADC IN Source", rt5665_अगर2_2_adc_in_क्रमागत);

/* Interface3 ADC Data Input*/
/* MX-30 [6:4] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर3_adc_in_src[] = अणु
	"STO1 ADC", "STO2 ADC", "MONO ADC", "IF1 DAC1",
	"IF1 DAC2", "IF2_1 DAC", "IF2_2 DAC", "DAC1 MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर3_adc_in_क्रमागत, RT5665_DIG_INF3_DATA,
	RT5665_IF3_ADC_IN_SFT, rt5665_अगर3_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर3_adc_in_mux =
	SOC_DAPM_ENUM("IF3 ADC IN Source", rt5665_अगर3_adc_in_क्रमागत);

/* PDM 1 L/R*/
/* MX-31 [11:10] [9:8] */
अटल स्थिर अक्षर * स्थिर rt5665_pdm_src[] = अणु
	"Stereo1 DAC", "Stereo2 DAC", "Mono DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_pdm_l_क्रमागत, RT5665_PDM_OUT_CTRL,
	RT5665_PDM1_L_SFT, rt5665_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_pdm_l_mux =
	SOC_DAPM_ENUM("PDM L Source", rt5665_pdm_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_pdm_r_क्रमागत, RT5665_PDM_OUT_CTRL,
	RT5665_PDM1_R_SFT, rt5665_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_pdm_r_mux =
	SOC_DAPM_ENUM("PDM R Source", rt5665_pdm_r_क्रमागत);


/* I2S1 TDM ADCDAT Source */
/* MX-7a[10] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_1_adc1_data_src[] = अणु
	"STO1 ADC", "IF2_1 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_1_adc1_data_क्रमागत, RT5665_TDM_CTRL_3,
	RT5665_IF1_ADC1_SEL_SFT, rt5665_अगर1_1_adc1_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_adc1_mux =
	SOC_DAPM_ENUM("IF1_1 ADC1 Source", rt5665_अगर1_1_adc1_data_क्रमागत);

/* MX-7a[9] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_1_adc2_data_src[] = अणु
	"STO2 ADC", "IF2_2 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_1_adc2_data_क्रमागत, RT5665_TDM_CTRL_3,
	RT5665_IF1_ADC2_SEL_SFT, rt5665_अगर1_1_adc2_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_adc2_mux =
	SOC_DAPM_ENUM("IF1_1 ADC2 Source", rt5665_अगर1_1_adc2_data_क्रमागत);

/* MX-7a[8] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_1_adc3_data_src[] = अणु
	"MONO ADC", "IF3 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_1_adc3_data_क्रमागत, RT5665_TDM_CTRL_3,
	RT5665_IF1_ADC3_SEL_SFT, rt5665_अगर1_1_adc3_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_1_adc3_mux =
	SOC_DAPM_ENUM("IF1_1 ADC3 Source", rt5665_अगर1_1_adc3_data_क्रमागत);

/* MX-7b[10] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_2_adc1_data_src[] = अणु
	"STO1 ADC", "IF1 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_2_adc1_data_क्रमागत, RT5665_TDM_CTRL_4,
	RT5665_IF1_ADC1_SEL_SFT, rt5665_अगर1_2_adc1_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_adc1_mux =
	SOC_DAPM_ENUM("IF1_2 ADC1 Source", rt5665_अगर1_2_adc1_data_क्रमागत);

/* MX-7b[9] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_2_adc2_data_src[] = अणु
	"STO2 ADC", "IF2_1 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_2_adc2_data_क्रमागत, RT5665_TDM_CTRL_4,
	RT5665_IF1_ADC2_SEL_SFT, rt5665_अगर1_2_adc2_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_adc2_mux =
	SOC_DAPM_ENUM("IF1_2 ADC2 Source", rt5665_अगर1_2_adc2_data_क्रमागत);

/* MX-7b[8] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_2_adc3_data_src[] = अणु
	"MONO ADC", "IF2_2 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_2_adc3_data_क्रमागत, RT5665_TDM_CTRL_4,
	RT5665_IF1_ADC3_SEL_SFT, rt5665_अगर1_2_adc3_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_adc3_mux =
	SOC_DAPM_ENUM("IF1_2 ADC3 Source", rt5665_अगर1_2_adc3_data_क्रमागत);

/* MX-7b[7] */
अटल स्थिर अक्षर * स्थिर rt5665_अगर1_2_adc4_data_src[] = अणु
	"DAC1", "IF3 DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_अगर1_2_adc4_data_क्रमागत, RT5665_TDM_CTRL_4,
	RT5665_IF1_ADC4_SEL_SFT, rt5665_अगर1_2_adc4_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_अगर1_2_adc4_mux =
	SOC_DAPM_ENUM("IF1_2 ADC4 Source", rt5665_अगर1_2_adc4_data_क्रमागत);

/* MX-7a[4:0] MX-7b[4:0] */
अटल स्थिर अक्षर * स्थिर rt5665_tdm_adc_data_src[] = अणु
	"1234", "1243", "1324",	"1342", "1432", "1423",
	"2134", "2143", "2314",	"2341", "2431", "2413",
	"3124", "3142", "3214", "3241", "3412", "3421",
	"4123", "4132", "4213", "4231", "4312", "4321"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_tdm1_adc_data_क्रमागत, RT5665_TDM_CTRL_3,
	RT5665_TDM_ADC_SEL_SFT, rt5665_tdm_adc_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_tdm1_adc_mux =
	SOC_DAPM_ENUM("TDM1 ADC Mux", rt5665_tdm1_adc_data_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5665_tdm2_adc_data_क्रमागत, RT5665_TDM_CTRL_4,
	RT5665_TDM_ADC_SEL_SFT, rt5665_tdm_adc_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5665_tdm2_adc_mux =
	SOC_DAPM_ENUM("TDM2 ADCDAT Source", rt5665_tdm2_adc_data_क्रमागत);

/* Out Volume Switch */
अटल स्थिर काष्ठा snd_kcontrol_new monovol_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_MONO_OUT, RT5665_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new outvol_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_LOUT, RT5665_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new outvol_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_LOUT, RT5665_VOL_R_SFT, 1, 1);

/* Out Switch */
अटल स्थिर काष्ठा snd_kcontrol_new mono_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_MONO_OUT, RT5665_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpo_चयन =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5665_HP_CTRL_2,
					RT5665_VOL_L_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new lout_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_LOUT, RT5665_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_LOUT, RT5665_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_PDM_OUT_CTRL,
			RT5665_M_PDM1_L_SFT, 1,	1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5665_PDM_OUT_CTRL,
			RT5665_M_PDM1_R_SFT, 1,	1);

अटल पूर्णांक rt5665_mono_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
		snd_soc_component_update_bits(component, RT5665_MONO_AMP_CALIB_CTRL_1, 0x40,
			0x0);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x10, 0x10);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x20, 0x20);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x20, 0);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x10, 0);
		snd_soc_component_update_bits(component, RT5665_MONO_AMP_CALIB_CTRL_1, 0x40,
			0x40);
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rt5665_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5665_STO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
		snd_soc_component_ग_लिखो(component, RT5665_HP_LOGIC_CTRL_2, 0x0003);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, RT5665_HP_LOGIC_CTRL_2, 0x0002);
		snd_soc_component_update_bits(component, RT5665_STO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rt5665_lout_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5665_DEPOP_1,
			RT5665_PUMP_EN, RT5665_PUMP_EN);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5665_DEPOP_1,
			RT5665_PUMP_EN, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक set_dmic_घातer(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/*Add delay to aव्योम pop noise*/
		msleep(150);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_verf(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (w->shअगरt) अणु
		हाल RT5665_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV1, 0);
			अवरोध;

		हाल RT5665_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV2, 0);
			अवरोध;

		हाल RT5665_PWR_VREF3_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV3, 0);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(15000, 20000);
		चयन (w->shअगरt) अणु
		हाल RT5665_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV1, RT5665_PWR_FV1);
			अवरोध;

		हाल RT5665_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV2, RT5665_PWR_FV2);
			अवरोध;

		हाल RT5665_PWR_VREF3_BIT:
			snd_soc_component_update_bits(component, RT5665_PWR_ANLG_1,
				RT5665_PWR_FV3, RT5665_PWR_FV3);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_i2s_pin_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक val1, val2, mask1 = 0, mask2 = 0;

	चयन (w->shअगरt) अणु
	हाल RT5665_PWR_I2S2_1_BIT:
		mask1 = RT5665_GP2_PIN_MASK | RT5665_GP3_PIN_MASK |
			RT5665_GP4_PIN_MASK | RT5665_GP5_PIN_MASK;
		val1 = RT5665_GP2_PIN_BCLK2 | RT5665_GP3_PIN_LRCK2 |
			RT5665_GP4_PIN_DACDAT2_1 | RT5665_GP5_PIN_ADCDAT2_1;
		अवरोध;
	हाल RT5665_PWR_I2S2_2_BIT:
		mask1 = RT5665_GP2_PIN_MASK | RT5665_GP3_PIN_MASK |
			RT5665_GP8_PIN_MASK;
		val1 = RT5665_GP2_PIN_BCLK2 | RT5665_GP3_PIN_LRCK2 |
			RT5665_GP8_PIN_DACDAT2_2;
		mask2 = RT5665_GP9_PIN_MASK;
		val2 = RT5665_GP9_PIN_ADCDAT2_2;
		अवरोध;
	हाल RT5665_PWR_I2S3_BIT:
		mask1 = RT5665_GP6_PIN_MASK | RT5665_GP7_PIN_MASK |
			RT5665_GP8_PIN_MASK;
		val1 = RT5665_GP6_PIN_BCLK3 | RT5665_GP7_PIN_LRCK3 |
			RT5665_GP8_PIN_DACDAT3;
		mask2 = RT5665_GP9_PIN_MASK;
		val2 = RT5665_GP9_PIN_ADCDAT3;
		अवरोध;
	पूर्ण
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (mask1)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_1,
					    mask1, val1);
		अगर (mask2)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_2,
					    mask2, val2);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (mask1)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_1,
					    mask1, 0);
		अगर (mask2)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_2,
					    mask2, 0);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5665_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT5665_PWR_ANLG_3, RT5665_PWR_LDO2_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL", RT5665_PWR_ANLG_3, RT5665_PWR_PLL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Det Power", RT5665_PWR_VOL,
		RT5665_PWR_MIC_DET_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Vref1", RT5665_PWR_ANLG_1, RT5665_PWR_VREF1_BIT, 0,
		rt5665_set_verf, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("Vref2", RT5665_PWR_ANLG_1, RT5665_PWR_VREF2_BIT, 0,
		rt5665_set_verf, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("Vref3", RT5665_PWR_ANLG_1, RT5665_PWR_VREF3_BIT, 0,
		rt5665_set_verf, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5665_ASRC_1,
		RT5665_I2S1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5665_ASRC_1,
		RT5665_I2S2_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S3 ASRC", 1, RT5665_ASRC_1,
		RT5665_I2S3_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO1 ASRC", 1, RT5665_ASRC_1,
		RT5665_DAC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO2 ASRC", 1, RT5665_ASRC_1,
		RT5665_DAC_STO2_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC Mono L ASRC", 1, RT5665_ASRC_1,
		RT5665_DAC_MONO_L_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC Mono R ASRC", 1, RT5665_ASRC_1,
		RT5665_DAC_MONO_R_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5665_ASRC_1,
		RT5665_ADC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO2 ASRC", 1, RT5665_ASRC_1,
		RT5665_ADC_STO2_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC Mono L ASRC", 1, RT5665_ASRC_1,
		RT5665_ADC_MONO_L_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC Mono R ASRC", 1, RT5665_ASRC_1,
		RT5665_ADC_MONO_R_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO1 ASRC", 1, RT5665_ASRC_1,
		RT5665_DMIC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO2 ASRC", 1, RT5665_ASRC_1,
		RT5665_DMIC_STO2_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO L ASRC", 1, RT5665_ASRC_1,
		RT5665_DMIC_MONO_L_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO R ASRC", 1, RT5665_ASRC_1,
		RT5665_DMIC_MONO_R_ASRC_SFT, 0, शून्य, 0),

	/* Input Side */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5665_PWR_ANLG_2, RT5665_PWR_MB1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS2", RT5665_PWR_ANLG_2, RT5665_PWR_MB2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS3", RT5665_PWR_ANLG_2, RT5665_PWR_MB3_BIT,
		0, शून्य, 0),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),
	SND_SOC_DAPM_INPUT("DMIC L2"),
	SND_SOC_DAPM_INPUT("DMIC R2"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),
	SND_SOC_DAPM_INPUT("IN3P"),
	SND_SOC_DAPM_INPUT("IN3N"),
	SND_SOC_DAPM_INPUT("IN4P"),
	SND_SOC_DAPM_INPUT("IN4N"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5665_DMIC_CTRL_1,
		RT5665_DMIC_1_EN_SFT, 0, set_dmic_घातer, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC2 Power", RT5665_DMIC_CTRL_1,
		RT5665_DMIC_2_EN_SFT, 0, set_dmic_घातer, SND_SOC_DAPM_POST_PMU),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST2", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST3", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST4", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST1 CBJ", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST1 Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST2 Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST3 Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST3_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST4 Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST4_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST1P Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST1_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST2P Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST2_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST3P Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST3_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST4P Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_BST4_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CBJ Power", RT5665_PWR_ANLG_3,
		RT5665_PWR_CBJ_BIT, 0, शून्य, 0),


	/* Input Volume */
	SND_SOC_DAPM_PGA("INL VOL", RT5665_PWR_VOL, RT5665_PWR_IN_L_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR VOL", RT5665_PWR_VOL, RT5665_PWR_IN_R_BIT,
		0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIX1L", SND_SOC_NOPM, 0, 0, rt5665_rec1_l_mix,
		ARRAY_SIZE(rt5665_rec1_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIX1R", SND_SOC_NOPM, 0, 0, rt5665_rec1_r_mix,
		ARRAY_SIZE(rt5665_rec1_r_mix)),
	SND_SOC_DAPM_MIXER("RECMIX2L", SND_SOC_NOPM, 0, 0, rt5665_rec2_l_mix,
		ARRAY_SIZE(rt5665_rec2_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIX2R", SND_SOC_NOPM, 0, 0, rt5665_rec2_r_mix,
		ARRAY_SIZE(rt5665_rec2_r_mix)),
	SND_SOC_DAPM_SUPPLY("RECMIX1L Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_RM1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RECMIX1R Power", RT5665_PWR_ANLG_2,
		RT5665_PWR_RM1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RECMIX2L Power", RT5665_PWR_MIXER,
		RT5665_PWR_RM2_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RECMIX2R Power", RT5665_PWR_MIXER,
		RT5665_PWR_RM2_R_BIT, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1 L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC1 R", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC2 L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC2 R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("ADC1 L Power", RT5665_PWR_DIG_1,
		RT5665_PWR_ADC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 R Power", RT5665_PWR_DIG_1,
		RT5665_PWR_ADC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 L Power", RT5665_PWR_DIG_1,
		RT5665_PWR_ADC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 R Power", RT5665_PWR_DIG_1,
		RT5665_PWR_ADC_R2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 clock", RT5665_CHOP_ADC,
		RT5665_CKGEN_ADC1_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 clock", RT5665_CHOP_ADC,
		RT5665_CKGEN_ADC2_SFT, 0, शून्य, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adc1l_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adc1r_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adc2l_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adc2r_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adcl_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_adcr_mux),
	SND_SOC_DAPM_MUX("Stereo1 DD L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_dd_l_mux),
	SND_SOC_DAPM_MUX("Stereo1 DD R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto1_dd_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_l2_mux),
	SND_SOC_DAPM_MUX("Mono ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_r2_mux),
	SND_SOC_DAPM_MUX("Mono ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_l1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_r1_mux),
	SND_SOC_DAPM_MUX("Mono DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_dmic_l_mux),
	SND_SOC_DAPM_MUX("Mono DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_dmic_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_l_mux),
	SND_SOC_DAPM_MUX("Mono ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_adc_r_mux),
	SND_SOC_DAPM_MUX("Mono DD L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_dd_l_mux),
	SND_SOC_DAPM_MUX("Mono DD R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_mono_dd_r_mux),
	SND_SOC_DAPM_MUX("Stereo2 DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo2 DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adc1l_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adc1r_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adc2l_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adc2r_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adcl_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_adcr_mux),
	SND_SOC_DAPM_MUX("Stereo2 DD L Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_dd_l_mux),
	SND_SOC_DAPM_MUX("Stereo2 DD R Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_sto2_dd_r_mux),
	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("ADC Stereo1 Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Stereo2 Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_ADC_S2F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", RT5665_STO1_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, 1, rt5665_sto1_adc_l_mix,
		ARRAY_SIZE(rt5665_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", RT5665_STO1_ADC_DIG_VOL,
		RT5665_R_MUTE_SFT, 1, rt5665_sto1_adc_r_mix,
		ARRAY_SIZE(rt5665_sto1_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 ADC MIXL", RT5665_STO2_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, 1, rt5665_sto2_adc_l_mix,
		ARRAY_SIZE(rt5665_sto2_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 ADC MIXR", RT5665_STO2_ADC_DIG_VOL,
		RT5665_R_MUTE_SFT, 1, rt5665_sto2_adc_r_mix,
		ARRAY_SIZE(rt5665_sto2_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Left Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXL", RT5665_MONO_ADC_DIG_VOL,
		RT5665_L_MUTE_SFT, 1, rt5665_mono_adc_l_mix,
		ARRAY_SIZE(rt5665_mono_adc_l_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Right Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXR", RT5665_MONO_ADC_DIG_VOL,
		RT5665_R_MUTE_SFT, 1, rt5665_mono_adc_r_mix,
		ARRAY_SIZE(rt5665_mono_adc_r_mix)),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1_1", RT5665_PWR_DIG_1, RT5665_PWR_I2S1_1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S1_2", RT5665_PWR_DIG_1, RT5665_PWR_I2S1_2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2_1", RT5665_PWR_DIG_1, RT5665_PWR_I2S2_1_BIT,
		0, rt5665_i2s_pin_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("I2S2_2", RT5665_PWR_DIG_1, RT5665_PWR_I2S2_2_BIT,
		0, rt5665_i2s_pin_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("I2S3", RT5665_PWR_DIG_1, RT5665_PWR_I2S3_BIT,
		0, rt5665_i2s_pin_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3 R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("IF2_1 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_1 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_1 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2_2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("IF3 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("IF1_1_ADC1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_1_adc1_mux),
	SND_SOC_DAPM_MUX("IF1_1_ADC2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_1_adc2_mux),
	SND_SOC_DAPM_MUX("IF1_1_ADC3 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_1_adc3_mux),
	SND_SOC_DAPM_PGA("IF1_1_ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("IF1_2_ADC1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_2_adc1_mux),
	SND_SOC_DAPM_MUX("IF1_2_ADC2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_2_adc2_mux),
	SND_SOC_DAPM_MUX("IF1_2_ADC3 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_2_adc3_mux),
	SND_SOC_DAPM_MUX("IF1_2_ADC4 Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर1_2_adc4_mux),
	SND_SOC_DAPM_MUX("TDM1 slot 01 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm1_adc_mux),
	SND_SOC_DAPM_MUX("TDM1 slot 23 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm1_adc_mux),
	SND_SOC_DAPM_MUX("TDM1 slot 45 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm1_adc_mux),
	SND_SOC_DAPM_MUX("TDM1 slot 67 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm1_adc_mux),
	SND_SOC_DAPM_MUX("TDM2 slot 01 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm2_adc_mux),
	SND_SOC_DAPM_MUX("TDM2 slot 23 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm2_adc_mux),
	SND_SOC_DAPM_MUX("TDM2 slot 45 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm2_adc_mux),
	SND_SOC_DAPM_MUX("TDM2 slot 67 Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_tdm2_adc_mux),
	SND_SOC_DAPM_MUX("IF2_1 ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर2_1_adc_in_mux),
	SND_SOC_DAPM_MUX("IF2_2 ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर2_2_adc_in_mux),
	SND_SOC_DAPM_MUX("IF3 ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5665_अगर3_adc_in_mux),
	SND_SOC_DAPM_MUX("IF1_1 0 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 1 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 2 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 3 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 4 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 5 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 6 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_1 7 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_1_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 0 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 1 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 2 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 3 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 4 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 5 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 6 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1_2 7 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर1_2_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF2_1 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर2_1_dac_swap_mux),
	SND_SOC_DAPM_MUX("IF2_1 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर2_1_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF2_2 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर2_2_dac_swap_mux),
	SND_SOC_DAPM_MUX("IF2_2 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर2_2_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF3 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर3_dac_swap_mux),
	SND_SOC_DAPM_MUX("IF3 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5665_अगर3_adc_swap_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 0", "AIF1_1 Capture",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 1", "AIF1_1 Capture",
				1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 2", "AIF1_1 Capture",
				2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 3", "AIF1_1 Capture",
				3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 4", "AIF1_1 Capture",
				4, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 5", "AIF1_1 Capture",
				5, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 6", "AIF1_1 Capture",
				6, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_1TX slot 7", "AIF1_1 Capture",
				7, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 0", "AIF1_2 Capture",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 1", "AIF1_2 Capture",
				1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 2", "AIF1_2 Capture",
				2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 3", "AIF1_2 Capture",
				3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 4", "AIF1_2 Capture",
				4, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 5", "AIF1_2 Capture",
				5, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 6", "AIF1_2 Capture",
				6, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1_2TX slot 7", "AIF1_2 Capture",
				7, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2_1TX", "AIF2_1 Capture",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2_2TX", "AIF2_2 Capture",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "AIF3 Capture",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2_1RX", "AIF2_1 Playback",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2_2RX", "AIF2_2 Playback",
				0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3RX", "AIF3 Playback",
				0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5665_dac_l_mix, ARRAY_SIZE(rt5665_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5665_dac_r_mix, ARRAY_SIZE(rt5665_dac_r_mix)),

	/* DAC channel Mux */
	SND_SOC_DAPM_MUX("DAC L1 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_l1_mux),
	SND_SOC_DAPM_MUX("DAC R1 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_r1_mux),
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_r2_mux),
	SND_SOC_DAPM_MUX("DAC L3 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_l3_mux),
	SND_SOC_DAPM_MUX("DAC R3 Mux", SND_SOC_NOPM, 0, 0, &rt5665_dac_r3_mux),

	SND_SOC_DAPM_MUX("DAC L1 Source", SND_SOC_NOPM, 0, 0,
		&rt5665_alg_dac_l1_mux),
	SND_SOC_DAPM_MUX("DAC R1 Source", SND_SOC_NOPM, 0, 0,
		&rt5665_alg_dac_r1_mux),
	SND_SOC_DAPM_MUX("DAC L2 Source", SND_SOC_NOPM, 0, 0,
		&rt5665_alg_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Source", SND_SOC_NOPM, 0, 0,
		&rt5665_alg_dac_r2_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("DAC Stereo1 Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_DAC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Stereo2 Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_DAC_S2F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Left Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_DAC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Right Filter", RT5665_PWR_DIG_2,
		RT5665_PWR_DAC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo1 DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5665_sto1_dac_l_mix, ARRAY_SIZE(rt5665_sto1_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5665_sto1_dac_r_mix, ARRAY_SIZE(rt5665_sto1_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5665_sto2_dac_l_mix, ARRAY_SIZE(rt5665_sto2_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5665_sto2_dac_r_mix, ARRAY_SIZE(rt5665_sto2_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5665_mono_dac_l_mix, ARRAY_SIZE(rt5665_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5665_mono_dac_r_mix, ARRAY_SIZE(rt5665_mono_dac_r_mix)),
	SND_SOC_DAPM_MUX("DAC MIXL", SND_SOC_NOPM, 0, 0,
		&rt5665_dig_dac_mixl_mux),
	SND_SOC_DAPM_MUX("DAC MIXR", SND_SOC_NOPM, 0, 0,
		&rt5665_dig_dac_mixr_mux),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("DAC L2 Power", RT5665_PWR_DIG_1,
		RT5665_PWR_DAC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R2 Power", RT5665_PWR_DIG_1,
		RT5665_PWR_DAC_R2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC L2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("DAC1 MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("DAC 1 Clock", 1, RT5665_CHOP_DAC,
		RT5665_CKGEN_DAC1_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC 2 Clock", 1, RT5665_CHOP_DAC,
		RT5665_CKGEN_DAC2_SFT, 0, शून्य, 0),

	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("MONOVOL MIX", RT5665_PWR_MIXER, RT5665_PWR_MM_BIT,
		0, rt5665_monovol_mix, ARRAY_SIZE(rt5665_monovol_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5665_PWR_MIXER, RT5665_PWR_OM_L_BIT,
		0, rt5665_out_l_mix, ARRAY_SIZE(rt5665_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5665_PWR_MIXER, RT5665_PWR_OM_R_BIT,
		0, rt5665_out_r_mix, ARRAY_SIZE(rt5665_out_r_mix)),

	/* Output Volume */
	SND_SOC_DAPM_SWITCH("MONOVOL", RT5665_PWR_VOL, RT5665_PWR_MV_BIT, 0,
		&monovol_चयन),
	SND_SOC_DAPM_SWITCH("OUTVOL L", RT5665_PWR_VOL, RT5665_PWR_OV_L_BIT, 0,
		&outvol_l_चयन),
	SND_SOC_DAPM_SWITCH("OUTVOL R", RT5665_PWR_VOL, RT5665_PWR_OV_R_BIT, 0,
		&outvol_r_चयन),

	/* MONO/HPO/LOUT */
	SND_SOC_DAPM_MIXER("Mono MIX", SND_SOC_NOPM, 0,	0, rt5665_mono_mix,
		ARRAY_SIZE(rt5665_mono_mix)),
	SND_SOC_DAPM_MIXER("LOUT L MIX", SND_SOC_NOPM, 0, 0, rt5665_lout_l_mix,
		ARRAY_SIZE(rt5665_lout_l_mix)),
	SND_SOC_DAPM_MIXER("LOUT R MIX", SND_SOC_NOPM, 0, 0, rt5665_lout_r_mix,
		ARRAY_SIZE(rt5665_lout_r_mix)),
	SND_SOC_DAPM_PGA_S("Mono Amp", 1, RT5665_PWR_ANLG_1, RT5665_PWR_MA_BIT,
		0, rt5665_mono_event, SND_SOC_DAPM_POST_PMD |
		SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, rt5665_hp_event,
		SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_PGA_S("LOUT Amp", 1, RT5665_PWR_ANLG_1,
		RT5665_PWR_LM_BIT, 0, rt5665_lout_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD |
		SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_SUPPLY("Charge Pump", SND_SOC_NOPM, 0, 0,
		rt5665_अक्षरge_pump_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SWITCH("Mono Playback", SND_SOC_NOPM, 0, 0,
		&mono_चयन),
	SND_SOC_DAPM_SWITCH("HPO Playback", SND_SOC_NOPM, 0, 0,
		&hpo_चयन),
	SND_SOC_DAPM_SWITCH("LOUT L Playback", SND_SOC_NOPM, 0, 0,
		&lout_l_चयन),
	SND_SOC_DAPM_SWITCH("LOUT R Playback", SND_SOC_NOPM, 0, 0,
		&lout_r_चयन),
	SND_SOC_DAPM_SWITCH("PDM L Playback", SND_SOC_NOPM, 0, 0,
		&pdm_l_चयन),
	SND_SOC_DAPM_SWITCH("PDM R Playback", SND_SOC_NOPM, 0, 0,
		&pdm_r_चयन),

	/* PDM */
	SND_SOC_DAPM_SUPPLY("PDM Power", RT5665_PWR_DIG_2,
		RT5665_PWR_PDM1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("PDM L Mux", SND_SOC_NOPM,
		0, 1, &rt5665_pdm_l_mux),
	SND_SOC_DAPM_MUX("PDM R Mux", SND_SOC_NOPM,
		0, 1, &rt5665_pdm_r_mux),

	/* CLK DET */
	SND_SOC_DAPM_SUPPLY("CLKDET SYS", RT5665_CLK_DET, RT5665_SYS_CLK_DET,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET HP", RT5665_CLK_DET, RT5665_HP_CLK_DET,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET MONO", RT5665_CLK_DET, RT5665_MONO_CLK_DET,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET LOUT", RT5665_CLK_DET, RT5665_LOUT_CLK_DET,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET", RT5665_CLK_DET, RT5665_POW_CLK_DET,
		0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("PDML"),
	SND_SOC_DAPM_OUTPUT("PDMR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5665_dapm_routes[] = अणु
	/*PLL*/
	अणु"ADC Stereo1 Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"ADC Stereo2 Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"ADC Mono Left Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"ADC Mono Right Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"DAC Stereo2 Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"DAC Mono Left Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,
	अणु"DAC Mono Right Filter", शून्य, "PLL", is_sys_clk_from_pllपूर्ण,

	/*ASRC*/
	अणु"ADC Stereo1 Filter", शून्य, "ADC STO1 ASRC", is_using_asrcपूर्ण,
	अणु"ADC Stereo2 Filter", शून्य, "ADC STO2 ASRC", is_using_asrcपूर्ण,
	अणु"ADC Mono Left Filter", शून्य, "ADC Mono L ASRC", is_using_asrcपूर्ण,
	अणु"ADC Mono Right Filter", शून्य, "ADC Mono R ASRC", is_using_asrcपूर्ण,
	अणु"DAC Mono Left Filter", शून्य, "DAC Mono L ASRC", is_using_asrcपूर्ण,
	अणु"DAC Mono Right Filter", शून्य, "DAC Mono R ASRC", is_using_asrcपूर्ण,
	अणु"DAC Stereo1 Filter", शून्य, "DAC STO1 ASRC", is_using_asrcपूर्ण,
	अणु"DAC Stereo2 Filter", शून्य, "DAC STO2 ASRC", is_using_asrcपूर्ण,
	अणु"I2S1 ASRC", शून्य, "CLKDET"पूर्ण,
	अणु"I2S2 ASRC", शून्य, "CLKDET"पूर्ण,
	अणु"I2S3 ASRC", शून्य, "CLKDET"पूर्ण,

	/*Vref*/
	अणु"Mic Det Power", शून्य, "Vref2"पूर्ण,
	अणु"MICBIAS1", शून्य, "Vref1"पूर्ण,
	अणु"MICBIAS1", शून्य, "Vref2"पूर्ण,
	अणु"MICBIAS2", शून्य, "Vref1"पूर्ण,
	अणु"MICBIAS2", शून्य, "Vref2"पूर्ण,
	अणु"MICBIAS3", शून्य, "Vref1"पूर्ण,
	अणु"MICBIAS3", शून्य, "Vref2"पूर्ण,

	अणु"Stereo1 DMIC L Mux", शून्य, "DMIC STO1 ASRC"पूर्ण,
	अणु"Stereo1 DMIC R Mux", शून्य, "DMIC STO1 ASRC"पूर्ण,
	अणु"Stereo2 DMIC L Mux", शून्य, "DMIC STO2 ASRC"पूर्ण,
	अणु"Stereo2 DMIC R Mux", शून्य, "DMIC STO2 ASRC"पूर्ण,
	अणु"Mono DMIC L Mux", शून्य, "DMIC MONO L ASRC"पूर्ण,
	अणु"Mono DMIC R Mux", शून्य, "DMIC MONO R ASRC"पूर्ण,

	अणु"I2S1_1", शून्य, "I2S1 ASRC"पूर्ण,
	अणु"I2S1_2", शून्य, "I2S1 ASRC"पूर्ण,
	अणु"I2S2_1", शून्य, "I2S2 ASRC"पूर्ण,
	अणु"I2S2_2", शून्य, "I2S2 ASRC"पूर्ण,
	अणु"I2S3", शून्य, "I2S3 ASRC"पूर्ण,

	अणु"CLKDET SYS", शून्य, "CLKDET"पूर्ण,
	अणु"CLKDET HP", शून्य, "CLKDET"पूर्ण,
	अणु"CLKDET MONO", शून्य, "CLKDET"पूर्ण,
	अणु"CLKDET LOUT", शून्य, "CLKDET"पूर्ण,

	अणु"IN1P", शून्य, "LDO2"पूर्ण,
	अणु"IN2P", शून्य, "LDO2"पूर्ण,
	अणु"IN3P", शून्य, "LDO2"पूर्ण,
	अणु"IN4P", शून्य, "LDO2"पूर्ण,

	अणु"DMIC1", शून्य, "DMIC L1"पूर्ण,
	अणु"DMIC1", शून्य, "DMIC R1"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC L2"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC R2"पूर्ण,

	अणु"BST1", शून्य, "IN1P"पूर्ण,
	अणु"BST1", शून्य, "IN1N"पूर्ण,
	अणु"BST1", शून्य, "BST1 Power"पूर्ण,
	अणु"BST1", शून्य, "BST1P Power"पूर्ण,
	अणु"BST2", शून्य, "IN2P"पूर्ण,
	अणु"BST2", शून्य, "IN2N"पूर्ण,
	अणु"BST2", शून्य, "BST2 Power"पूर्ण,
	अणु"BST2", शून्य, "BST2P Power"पूर्ण,
	अणु"BST3", शून्य, "IN3P"पूर्ण,
	अणु"BST3", शून्य, "IN3N"पूर्ण,
	अणु"BST3", शून्य, "BST3 Power"पूर्ण,
	अणु"BST3", शून्य, "BST3P Power"पूर्ण,
	अणु"BST4", शून्य, "IN4P"पूर्ण,
	अणु"BST4", शून्य, "IN4N"पूर्ण,
	अणु"BST4", शून्य, "BST4 Power"पूर्ण,
	अणु"BST4", शून्य, "BST4P Power"पूर्ण,
	अणु"BST1 CBJ", शून्य, "IN1P"पूर्ण,
	अणु"BST1 CBJ", शून्य, "IN1N"पूर्ण,
	अणु"BST1 CBJ", शून्य, "CBJ Power"पूर्ण,
	अणु"CBJ Power", शून्य, "Vref2"पूर्ण,

	अणु"INL VOL", शून्य, "IN3P"पूर्ण,
	अणु"INR VOL", शून्य, "IN3N"पूर्ण,

	अणु"RECMIX1L", "CBJ Switch", "BST1 CBJ"पूर्ण,
	अणु"RECMIX1L", "INL Switch", "INL VOL"पूर्ण,
	अणु"RECMIX1L", "INR Switch", "INR VOL"पूर्ण,
	अणु"RECMIX1L", "BST4 Switch", "BST4"पूर्ण,
	अणु"RECMIX1L", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIX1L", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIX1L", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIX1L", शून्य, "RECMIX1L Power"पूर्ण,

	अणु"RECMIX1R", "MONOVOL Switch", "MONOVOL"पूर्ण,
	अणु"RECMIX1R", "INR Switch", "INR VOL"पूर्ण,
	अणु"RECMIX1R", "BST4 Switch", "BST4"पूर्ण,
	अणु"RECMIX1R", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIX1R", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIX1R", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIX1R", शून्य, "RECMIX1R Power"पूर्ण,

	अणु"RECMIX2L", "CBJ Switch", "BST1 CBJ"पूर्ण,
	अणु"RECMIX2L", "INL Switch", "INL VOL"पूर्ण,
	अणु"RECMIX2L", "INR Switch", "INR VOL"पूर्ण,
	अणु"RECMIX2L", "BST4 Switch", "BST4"पूर्ण,
	अणु"RECMIX2L", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIX2L", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIX2L", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIX2L", शून्य, "RECMIX2L Power"पूर्ण,

	अणु"RECMIX2R", "MONOVOL Switch", "MONOVOL"पूर्ण,
	अणु"RECMIX2R", "INL Switch", "INL VOL"पूर्ण,
	अणु"RECMIX2R", "INR Switch", "INR VOL"पूर्ण,
	अणु"RECMIX2R", "BST4 Switch", "BST4"पूर्ण,
	अणु"RECMIX2R", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIX2R", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIX2R", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIX2R", शून्य, "RECMIX2R Power"पूर्ण,

	अणु"ADC1 L", शून्य, "RECMIX1L"पूर्ण,
	अणु"ADC1 L", शून्य, "ADC1 L Power"पूर्ण,
	अणु"ADC1 L", शून्य, "ADC1 clock"पूर्ण,
	अणु"ADC1 R", शून्य, "RECMIX1R"पूर्ण,
	अणु"ADC1 R", शून्य, "ADC1 R Power"पूर्ण,
	अणु"ADC1 R", शून्य, "ADC1 clock"पूर्ण,

	अणु"ADC2 L", शून्य, "RECMIX2L"पूर्ण,
	अणु"ADC2 L", शून्य, "ADC2 L Power"पूर्ण,
	अणु"ADC2 L", शून्य, "ADC2 clock"पूर्ण,
	अणु"ADC2 R", शून्य, "RECMIX2R"पूर्ण,
	अणु"ADC2 R", शून्य, "ADC2 R Power"पूर्ण,
	अणु"ADC2 R", शून्य, "ADC2 clock"पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC2 Power"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC2 Power"पूर्ण,

	अणु"Stereo1 DMIC L Mux", "DMIC1", "DMIC L1"पूर्ण,
	अणु"Stereo1 DMIC L Mux", "DMIC2", "DMIC L2"पूर्ण,

	अणु"Stereo1 DMIC R Mux", "DMIC1", "DMIC R1"पूर्ण,
	अणु"Stereo1 DMIC R Mux", "DMIC2", "DMIC R2"पूर्ण,

	अणु"Mono DMIC L Mux", "DMIC1 L", "DMIC L1"पूर्ण,
	अणु"Mono DMIC L Mux", "DMIC2 L", "DMIC L2"पूर्ण,

	अणु"Mono DMIC R Mux", "DMIC1 R", "DMIC R1"पूर्ण,
	अणु"Mono DMIC R Mux", "DMIC2 R", "DMIC R2"पूर्ण,

	अणु"Stereo2 DMIC L Mux", "DMIC1", "DMIC L1"पूर्ण,
	अणु"Stereo2 DMIC L Mux", "DMIC2", "DMIC L2"पूर्ण,

	अणु"Stereo2 DMIC R Mux", "DMIC1", "DMIC R1"पूर्ण,
	अणु"Stereo2 DMIC R Mux", "DMIC2", "DMIC R2"पूर्ण,

	अणु"Stereo1 ADC L Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo1 ADC L Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Stereo1 ADC L Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Stereo1 ADC L Mux", "ADC2 R", "ADC2 R"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Stereo1 ADC R Mux", "ADC2 R", "ADC2 R"पूर्ण,

	अणु"Stereo1 DD L Mux", "STO2 DAC", "Stereo2 DAC MIXL"पूर्ण,
	अणु"Stereo1 DD L Mux", "MONO DAC", "Mono DAC MIXL"पूर्ण,

	अणु"Stereo1 DD R Mux", "STO2 DAC", "Stereo2 DAC MIXR"पूर्ण,
	अणु"Stereo1 DD R Mux", "MONO DAC", "Mono DAC MIXR"पूर्ण,

	अणु"Stereo1 ADC L1 Mux", "ADC", "Stereo1 ADC L Mux"पूर्ण,
	अणु"Stereo1 ADC L1 Mux", "DD Mux", "Stereo1 DD L Mux"पूर्ण,
	अणु"Stereo1 ADC L2 Mux", "DMIC", "Stereo1 DMIC L Mux"पूर्ण,
	अणु"Stereo1 ADC L2 Mux", "DAC MIX", "DAC MIXL"पूर्ण,

	अणु"Stereo1 ADC R1 Mux", "ADC", "Stereo1 ADC R Mux"पूर्ण,
	अणु"Stereo1 ADC R1 Mux", "DD Mux", "Stereo1 DD R Mux"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DMIC", "Stereo1 DMIC R Mux"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DAC MIX", "DAC MIXR"पूर्ण,

	अणु"Mono ADC L Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Mono ADC L Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Mono ADC L Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Mono ADC L Mux", "ADC2 R", "ADC2 R"पूर्ण,

	अणु"Mono ADC R Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Mono ADC R Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Mono ADC R Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Mono ADC R Mux", "ADC2 R", "ADC2 R"पूर्ण,

	अणु"Mono DD L Mux", "STO2 DAC", "Stereo2 DAC MIXL"पूर्ण,
	अणु"Mono DD L Mux", "MONO DAC", "Mono DAC MIXL"पूर्ण,

	अणु"Mono DD R Mux", "STO2 DAC", "Stereo2 DAC MIXR"पूर्ण,
	अणु"Mono DD R Mux", "MONO DAC", "Mono DAC MIXR"पूर्ण,

	अणु"Mono ADC L2 Mux", "DMIC", "Mono DMIC L Mux"पूर्ण,
	अणु"Mono ADC L2 Mux", "DAC MIXL", "DAC MIXL"पूर्ण,
	अणु"Mono ADC L1 Mux", "DD Mux", "Mono DD L Mux"पूर्ण,
	अणु"Mono ADC L1 Mux", "ADC",  "Mono ADC L Mux"पूर्ण,

	अणु"Mono ADC R1 Mux", "DD Mux", "Mono DD R Mux"पूर्ण,
	अणु"Mono ADC R1 Mux", "ADC", "Mono ADC R Mux"पूर्ण,
	अणु"Mono ADC R2 Mux", "DMIC", "Mono DMIC R Mux"पूर्ण,
	अणु"Mono ADC R2 Mux", "DAC MIXR", "DAC MIXR"पूर्ण,

	अणु"Stereo2 ADC L Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo2 ADC L Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Stereo2 ADC L Mux", "ADC1 R", "ADC1 R"पूर्ण,
	अणु"Stereo2 ADC R Mux", "ADC1 L", "ADC1 L"पूर्ण,
	अणु"Stereo2 ADC R Mux", "ADC2 L", "ADC2 L"पूर्ण,
	अणु"Stereo2 ADC R Mux", "ADC1 R", "ADC1 R"पूर्ण,

	अणु"Stereo2 DD L Mux", "STO2 DAC", "Stereo2 DAC MIXL"पूर्ण,
	अणु"Stereo2 DD L Mux", "MONO DAC", "Mono DAC MIXL"पूर्ण,

	अणु"Stereo2 DD R Mux", "STO2 DAC", "Stereo2 DAC MIXR"पूर्ण,
	अणु"Stereo2 DD R Mux", "MONO DAC", "Mono DAC MIXR"पूर्ण,

	अणु"Stereo2 ADC L1 Mux", "ADC", "Stereo2 ADC L Mux"पूर्ण,
	अणु"Stereo2 ADC L1 Mux", "DD Mux", "Stereo2 DD L Mux"पूर्ण,
	अणु"Stereo2 ADC L2 Mux", "DMIC", "Stereo2 DMIC L Mux"पूर्ण,
	अणु"Stereo2 ADC L2 Mux", "DAC MIX", "DAC MIXL"पूर्ण,

	अणु"Stereo2 ADC R1 Mux", "ADC", "Stereo2 ADC R Mux"पूर्ण,
	अणु"Stereo2 ADC R1 Mux", "DD Mux", "Stereo2 DD R Mux"पूर्ण,
	अणु"Stereo2 ADC R2 Mux", "DMIC", "Stereo2 DMIC R Mux"पूर्ण,
	अणु"Stereo2 ADC R2 Mux", "DAC MIX", "DAC MIXR"पूर्ण,

	अणु"Stereo1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", शून्य, "ADC Stereo1 Filter"पूर्ण,

	अणु"Stereo1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", शून्य, "ADC Stereo1 Filter"पूर्ण,

	अणु"Mono ADC MIXL", "ADC1 Switch", "Mono ADC L1 Mux"पूर्ण,
	अणु"Mono ADC MIXL", "ADC2 Switch", "Mono ADC L2 Mux"पूर्ण,
	अणु"Mono ADC MIXL", शून्य, "ADC Mono Left Filter"पूर्ण,

	अणु"Mono ADC MIXR", "ADC1 Switch", "Mono ADC R1 Mux"पूर्ण,
	अणु"Mono ADC MIXR", "ADC2 Switch", "Mono ADC R2 Mux"पूर्ण,
	अणु"Mono ADC MIXR", शून्य, "ADC Mono Right Filter"पूर्ण,

	अणु"Stereo2 ADC MIXL", "ADC1 Switch", "Stereo2 ADC L1 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXL", "ADC2 Switch", "Stereo2 ADC L2 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXL", शून्य, "ADC Stereo2 Filter"पूर्ण,

	अणु"Stereo2 ADC MIXR", "ADC1 Switch", "Stereo2 ADC R1 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXR", "ADC2 Switch", "Stereo2 ADC R2 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXR", शून्य, "ADC Stereo2 Filter"पूर्ण,

	अणु"Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXL"पूर्ण,
	अणु"Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXR"पूर्ण,
	अणु"Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXL"पूर्ण,
	अणु"Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXR"पूर्ण,
	अणु"Mono ADC MIX", शून्य, "Mono ADC MIXL"पूर्ण,
	अणु"Mono ADC MIX", शून्य, "Mono ADC MIXR"पूर्ण,

	अणु"IF1_1_ADC1 Mux", "STO1 ADC", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1_1_ADC1 Mux", "IF2_1 DAC", "IF2_1 DAC"पूर्ण,
	अणु"IF1_1_ADC2 Mux", "STO2 ADC", "Stereo2 ADC MIX"पूर्ण,
	अणु"IF1_1_ADC2 Mux", "IF2_2 DAC", "IF2_2 DAC"पूर्ण,
	अणु"IF1_1_ADC3 Mux", "MONO ADC", "Mono ADC MIX"पूर्ण,
	अणु"IF1_1_ADC3 Mux", "IF3 DAC", "IF3 DAC"पूर्ण,
	अणु"IF1_1_ADC4", शून्य, "DAC1 MIX"पूर्ण,

	अणु"IF1_2_ADC1 Mux", "STO1 ADC", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF1_2_ADC1 Mux", "IF1 DAC", "IF1 DAC1"पूर्ण,
	अणु"IF1_2_ADC2 Mux", "STO2 ADC", "Stereo2 ADC MIX"पूर्ण,
	अणु"IF1_2_ADC2 Mux", "IF2_1 DAC", "IF2_1 DAC"पूर्ण,
	अणु"IF1_2_ADC3 Mux", "MONO ADC", "Mono ADC MIX"पूर्ण,
	अणु"IF1_2_ADC3 Mux", "IF2_2 DAC", "IF2_2 DAC"पूर्ण,
	अणु"IF1_2_ADC4 Mux", "DAC1", "DAC1 MIX"पूर्ण,
	अणु"IF1_2_ADC4 Mux", "IF3 DAC", "IF3 DAC"पूर्ण,

	अणु"TDM1 slot 01 Data Mux", "1234", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "1243", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "1324", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "1342", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "1432", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "1423", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2134", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2143", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2314", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2341", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2431", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "2413", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3124", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3142", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3214", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3241", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3412", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "3421", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4123", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4132", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4213", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4231", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4312", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", "4321", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 01 Data Mux", शून्य, "I2S1_1"पूर्ण,

	अणु"TDM1 slot 23 Data Mux", "1234", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "1243", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "1324", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "1342", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "1432", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "1423", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2134", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2143", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2314", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2341", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2431", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "2413", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3124", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3142", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3214", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3241", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3412", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "3421", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4123", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4132", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4213", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4231", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4312", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", "4321", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 23 Data Mux", शून्य, "I2S1_1"पूर्ण,

	अणु"TDM1 slot 45 Data Mux", "1234", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "1243", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "1324", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "1342", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "1432", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "1423", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2134", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2143", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2314", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2341", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2431", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "2413", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3124", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3142", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3214", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3241", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3412", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "3421", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4123", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4132", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4213", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4231", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4312", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", "4321", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 45 Data Mux", शून्य, "I2S1_1"पूर्ण,

	अणु"TDM1 slot 67 Data Mux", "1234", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "1243", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "1324", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "1342", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "1432", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "1423", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2134", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2143", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2314", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2341", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2431", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "2413", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3124", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3142", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3214", "IF1_1_ADC4"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3241", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3412", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "3421", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4123", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4132", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4213", "IF1_1_ADC3 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4231", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4312", "IF1_1_ADC2 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", "4321", "IF1_1_ADC1 Mux"पूर्ण,
	अणु"TDM1 slot 67 Data Mux", शून्य, "I2S1_1"पूर्ण,


	अणु"TDM2 slot 01 Data Mux", "1234", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "1243", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "1324", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "1342", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "1432", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "1423", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2134", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2143", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2314", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2341", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2431", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "2413", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3124", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3142", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3214", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3241", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3412", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "3421", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4123", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4132", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4213", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4231", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4312", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", "4321", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 01 Data Mux", शून्य, "I2S1_2"पूर्ण,

	अणु"TDM2 slot 23 Data Mux", "1234", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "1243", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "1324", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "1342", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "1432", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "1423", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2134", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2143", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2314", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2341", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2431", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "2413", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3124", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3142", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3214", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3241", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3412", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "3421", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4123", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4132", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4213", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4231", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4312", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", "4321", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 23 Data Mux", शून्य, "I2S1_2"पूर्ण,

	अणु"TDM2 slot 45 Data Mux", "1234", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "1243", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "1324", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "1342", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "1432", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "1423", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2134", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2143", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2314", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2341", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2431", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "2413", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3124", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3142", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3214", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3241", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3412", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "3421", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4123", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4132", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4213", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4231", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4312", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", "4321", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 45 Data Mux", शून्य, "I2S1_2"पूर्ण,

	अणु"TDM2 slot 67 Data Mux", "1234", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "1243", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "1324", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "1342", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "1432", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "1423", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2134", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2143", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2314", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2341", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2431", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "2413", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3124", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3142", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3214", "IF1_2_ADC4 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3241", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3412", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "3421", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4123", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4132", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4213", "IF1_2_ADC3 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4231", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4312", "IF1_2_ADC2 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", "4321", "IF1_2_ADC1 Mux"पूर्ण,
	अणु"TDM2 slot 67 Data Mux", शून्य, "I2S1_2"पूर्ण,

	अणु"IF1_1 0 ADC Swap Mux", "L/R", "TDM1 slot 01 Data Mux"पूर्ण,
	अणु"IF1_1 0 ADC Swap Mux", "L/L", "TDM1 slot 01 Data Mux"पूर्ण,
	अणु"IF1_1 1 ADC Swap Mux", "R/L", "TDM1 slot 01 Data Mux"पूर्ण,
	अणु"IF1_1 1 ADC Swap Mux", "R/R", "TDM1 slot 01 Data Mux"पूर्ण,
	अणु"IF1_1 2 ADC Swap Mux", "L/R", "TDM1 slot 23 Data Mux"पूर्ण,
	अणु"IF1_1 2 ADC Swap Mux", "R/L", "TDM1 slot 23 Data Mux"पूर्ण,
	अणु"IF1_1 3 ADC Swap Mux", "L/L", "TDM1 slot 23 Data Mux"पूर्ण,
	अणु"IF1_1 3 ADC Swap Mux", "R/R", "TDM1 slot 23 Data Mux"पूर्ण,
	अणु"IF1_1 4 ADC Swap Mux", "L/R", "TDM1 slot 45 Data Mux"पूर्ण,
	अणु"IF1_1 4 ADC Swap Mux", "R/L", "TDM1 slot 45 Data Mux"पूर्ण,
	अणु"IF1_1 5 ADC Swap Mux", "L/L", "TDM1 slot 45 Data Mux"पूर्ण,
	अणु"IF1_1 5 ADC Swap Mux", "R/R", "TDM1 slot 45 Data Mux"पूर्ण,
	अणु"IF1_1 6 ADC Swap Mux", "L/R", "TDM1 slot 67 Data Mux"पूर्ण,
	अणु"IF1_1 6 ADC Swap Mux", "R/L", "TDM1 slot 67 Data Mux"पूर्ण,
	अणु"IF1_1 7 ADC Swap Mux", "L/L", "TDM1 slot 67 Data Mux"पूर्ण,
	अणु"IF1_1 7 ADC Swap Mux", "R/R", "TDM1 slot 67 Data Mux"पूर्ण,
	अणु"IF1_2 0 ADC Swap Mux", "L/R", "TDM2 slot 01 Data Mux"पूर्ण,
	अणु"IF1_2 0 ADC Swap Mux", "R/L", "TDM2 slot 01 Data Mux"पूर्ण,
	अणु"IF1_2 1 ADC Swap Mux", "L/L", "TDM2 slot 01 Data Mux"पूर्ण,
	अणु"IF1_2 1 ADC Swap Mux", "R/R", "TDM2 slot 01 Data Mux"पूर्ण,
	अणु"IF1_2 2 ADC Swap Mux", "L/R", "TDM2 slot 23 Data Mux"पूर्ण,
	अणु"IF1_2 2 ADC Swap Mux", "R/L", "TDM2 slot 23 Data Mux"पूर्ण,
	अणु"IF1_2 3 ADC Swap Mux", "L/L", "TDM2 slot 23 Data Mux"पूर्ण,
	अणु"IF1_2 3 ADC Swap Mux", "R/R", "TDM2 slot 23 Data Mux"पूर्ण,
	अणु"IF1_2 4 ADC Swap Mux", "L/R", "TDM2 slot 45 Data Mux"पूर्ण,
	अणु"IF1_2 4 ADC Swap Mux", "R/L", "TDM2 slot 45 Data Mux"पूर्ण,
	अणु"IF1_2 5 ADC Swap Mux", "L/L", "TDM2 slot 45 Data Mux"पूर्ण,
	अणु"IF1_2 5 ADC Swap Mux", "R/R", "TDM2 slot 45 Data Mux"पूर्ण,
	अणु"IF1_2 6 ADC Swap Mux", "L/R", "TDM2 slot 67 Data Mux"पूर्ण,
	अणु"IF1_2 6 ADC Swap Mux", "R/L", "TDM2 slot 67 Data Mux"पूर्ण,
	अणु"IF1_2 7 ADC Swap Mux", "L/L", "TDM2 slot 67 Data Mux"पूर्ण,
	अणु"IF1_2 7 ADC Swap Mux", "R/R", "TDM2 slot 67 Data Mux"पूर्ण,

	अणु"IF2_1 ADC Mux", "STO1 ADC", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF2_1 ADC Mux", "STO2 ADC", "Stereo2 ADC MIX"पूर्ण,
	अणु"IF2_1 ADC Mux", "MONO ADC", "Mono ADC MIX"पूर्ण,
	अणु"IF2_1 ADC Mux", "IF1 DAC1", "IF1 DAC1"पूर्ण,
	अणु"IF2_1 ADC Mux", "IF1 DAC2", "IF1 DAC2"पूर्ण,
	अणु"IF2_1 ADC Mux", "IF2_2 DAC", "IF2_2 DAC"पूर्ण,
	अणु"IF2_1 ADC Mux", "IF3 DAC", "IF3 DAC"पूर्ण,
	अणु"IF2_1 ADC Mux", "DAC1 MIX", "DAC1 MIX"पूर्ण,
	अणु"IF2_1 ADC", शून्य, "IF2_1 ADC Mux"पूर्ण,
	अणु"IF2_1 ADC", शून्य, "I2S2_1"पूर्ण,

	अणु"IF2_2 ADC Mux", "STO1 ADC", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF2_2 ADC Mux", "STO2 ADC", "Stereo2 ADC MIX"पूर्ण,
	अणु"IF2_2 ADC Mux", "MONO ADC", "Mono ADC MIX"पूर्ण,
	अणु"IF2_2 ADC Mux", "IF1 DAC1", "IF1 DAC1"पूर्ण,
	अणु"IF2_2 ADC Mux", "IF1 DAC2", "IF1 DAC2"पूर्ण,
	अणु"IF2_2 ADC Mux", "IF2_1 DAC", "IF2_1 DAC"पूर्ण,
	अणु"IF2_2 ADC Mux", "IF3 DAC", "IF3 DAC"पूर्ण,
	अणु"IF2_2 ADC Mux", "DAC1 MIX", "DAC1 MIX"पूर्ण,
	अणु"IF2_2 ADC", शून्य, "IF2_2 ADC Mux"पूर्ण,
	अणु"IF2_2 ADC", शून्य, "I2S2_2"पूर्ण,

	अणु"IF3 ADC Mux", "STO1 ADC", "Stereo1 ADC MIX"पूर्ण,
	अणु"IF3 ADC Mux", "STO2 ADC", "Stereo2 ADC MIX"पूर्ण,
	अणु"IF3 ADC Mux", "MONO ADC", "Mono ADC MIX"पूर्ण,
	अणु"IF3 ADC Mux", "IF1 DAC1", "IF1 DAC1"पूर्ण,
	अणु"IF3 ADC Mux", "IF1 DAC2", "IF1 DAC2"पूर्ण,
	अणु"IF3 ADC Mux", "IF2_1 DAC", "IF2_1 DAC"पूर्ण,
	अणु"IF3 ADC Mux", "IF2_2 DAC", "IF2_2 DAC"पूर्ण,
	अणु"IF3 ADC Mux", "DAC1 MIX", "DAC1 MIX"पूर्ण,
	अणु"IF3 ADC", शून्य, "IF3 ADC Mux"पूर्ण,
	अणु"IF3 ADC", शून्य, "I2S3"पूर्ण,

	अणु"AIF1_1TX slot 0", शून्य, "IF1_1 0 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 1", शून्य, "IF1_1 1 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 2", शून्य, "IF1_1 2 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 3", शून्य, "IF1_1 3 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 4", शून्य, "IF1_1 4 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 5", शून्य, "IF1_1 5 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 6", शून्य, "IF1_1 6 ADC Swap Mux"पूर्ण,
	अणु"AIF1_1TX slot 7", शून्य, "IF1_1 7 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 0", शून्य, "IF1_2 0 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 1", शून्य, "IF1_2 1 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 2", शून्य, "IF1_2 2 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 3", शून्य, "IF1_2 3 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 4", शून्य, "IF1_2 4 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 5", शून्य, "IF1_2 5 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 6", शून्य, "IF1_2 6 ADC Swap Mux"पूर्ण,
	अणु"AIF1_2TX slot 7", शून्य, "IF1_2 7 ADC Swap Mux"पूर्ण,
	अणु"IF2_1 ADC Swap Mux", "L/R", "IF2_1 ADC"पूर्ण,
	अणु"IF2_1 ADC Swap Mux", "R/L", "IF2_1 ADC"पूर्ण,
	अणु"IF2_1 ADC Swap Mux", "L/L", "IF2_1 ADC"पूर्ण,
	अणु"IF2_1 ADC Swap Mux", "R/R", "IF2_1 ADC"पूर्ण,
	अणु"AIF2_1TX", शून्य, "IF2_1 ADC Swap Mux"पूर्ण,
	अणु"IF2_2 ADC Swap Mux", "L/R", "IF2_2 ADC"पूर्ण,
	अणु"IF2_2 ADC Swap Mux", "R/L", "IF2_2 ADC"पूर्ण,
	अणु"IF2_2 ADC Swap Mux", "L/L", "IF2_2 ADC"पूर्ण,
	अणु"IF2_2 ADC Swap Mux", "R/R", "IF2_2 ADC"पूर्ण,
	अणु"AIF2_2TX", शून्य, "IF2_2 ADC Swap Mux"पूर्ण,
	अणु"IF3 ADC Swap Mux", "L/R", "IF3 ADC"पूर्ण,
	अणु"IF3 ADC Swap Mux", "R/L", "IF3 ADC"पूर्ण,
	अणु"IF3 ADC Swap Mux", "L/L", "IF3 ADC"पूर्ण,
	अणु"IF3 ADC Swap Mux", "R/R", "IF3 ADC"पूर्ण,
	अणु"AIF3TX", शून्य, "IF3 ADC Swap Mux"पूर्ण,

	अणु"IF1 DAC1", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC2", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC3", शून्य, "AIF1RX"पूर्ण,
	अणु"IF2_1 DAC Swap Mux", "L/R", "AIF2_1RX"पूर्ण,
	अणु"IF2_1 DAC Swap Mux", "R/L", "AIF2_1RX"पूर्ण,
	अणु"IF2_1 DAC Swap Mux", "L/L", "AIF2_1RX"पूर्ण,
	अणु"IF2_1 DAC Swap Mux", "R/R", "AIF2_1RX"पूर्ण,
	अणु"IF2_2 DAC Swap Mux", "L/R", "AIF2_2RX"पूर्ण,
	अणु"IF2_2 DAC Swap Mux", "R/L", "AIF2_2RX"पूर्ण,
	अणु"IF2_2 DAC Swap Mux", "L/L", "AIF2_2RX"पूर्ण,
	अणु"IF2_2 DAC Swap Mux", "R/R", "AIF2_2RX"पूर्ण,
	अणु"IF2_1 DAC", शून्य, "IF2_1 DAC Swap Mux"पूर्ण,
	अणु"IF2_2 DAC", शून्य, "IF2_2 DAC Swap Mux"पूर्ण,
	अणु"IF3 DAC Swap Mux", "L/R", "AIF3RX"पूर्ण,
	अणु"IF3 DAC Swap Mux", "R/L", "AIF3RX"पूर्ण,
	अणु"IF3 DAC Swap Mux", "L/L", "AIF3RX"पूर्ण,
	अणु"IF3 DAC Swap Mux", "R/R", "AIF3RX"पूर्ण,
	अणु"IF3 DAC", शून्य, "IF3 DAC Swap Mux"पूर्ण,

	अणु"IF1 DAC1", शून्य, "I2S1_1"पूर्ण,
	अणु"IF1 DAC2", शून्य, "I2S1_1"पूर्ण,
	अणु"IF1 DAC3", शून्य, "I2S1_1"पूर्ण,
	अणु"IF2_1 DAC", शून्य, "I2S2_1"पूर्ण,
	अणु"IF2_2 DAC", शून्य, "I2S2_2"पूर्ण,
	अणु"IF3 DAC", शून्य, "I2S3"पूर्ण,

	अणु"IF1 DAC1 L", शून्य, "IF1 DAC1"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "IF1 DAC1"पूर्ण,
	अणु"IF1 DAC2 L", शून्य, "IF1 DAC2"पूर्ण,
	अणु"IF1 DAC2 R", शून्य, "IF1 DAC2"पूर्ण,
	अणु"IF1 DAC3 L", शून्य, "IF1 DAC3"पूर्ण,
	अणु"IF1 DAC3 R", शून्य, "IF1 DAC3"पूर्ण,
	अणु"IF2_1 DAC L", शून्य, "IF2_1 DAC"पूर्ण,
	अणु"IF2_1 DAC R", शून्य, "IF2_1 DAC"पूर्ण,
	अणु"IF2_2 DAC L", शून्य, "IF2_2 DAC"पूर्ण,
	अणु"IF2_2 DAC R", शून्य, "IF2_2 DAC"पूर्ण,
	अणु"IF3 DAC L", शून्य, "IF3 DAC"पूर्ण,
	अणु"IF3 DAC R", शून्य, "IF3 DAC"पूर्ण,

	अणु"DAC L1 Mux", "IF1 DAC1", "IF1 DAC1 L"पूर्ण,
	अणु"DAC L1 Mux", "IF2_1 DAC", "IF2_1 DAC L"पूर्ण,
	अणु"DAC L1 Mux", "IF2_2 DAC", "IF2_2 DAC L"पूर्ण,
	अणु"DAC L1 Mux", "IF3 DAC", "IF3 DAC L"पूर्ण,
	अणु"DAC L1 Mux", शून्य, "DAC Stereo1 Filter"पूर्ण,

	अणु"DAC R1 Mux", "IF1 DAC1", "IF1 DAC1 R"पूर्ण,
	अणु"DAC R1 Mux", "IF2_1 DAC", "IF2_1 DAC R"पूर्ण,
	अणु"DAC R1 Mux", "IF2_2 DAC", "IF2_2 DAC R"पूर्ण,
	अणु"DAC R1 Mux", "IF3 DAC", "IF3 DAC R"पूर्ण,
	अणु"DAC R1 Mux", शून्य, "DAC Stereo1 Filter"पूर्ण,

	अणु"DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL"पूर्ण,
	अणु"DAC1 MIXL", "DAC1 Switch", "DAC L1 Mux"पूर्ण,
	अणु"DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR"पूर्ण,
	अणु"DAC1 MIXR", "DAC1 Switch", "DAC R1 Mux"पूर्ण,

	अणु"DAC1 MIX", शून्य, "DAC1 MIXL"पूर्ण,
	अणु"DAC1 MIX", शून्य, "DAC1 MIXR"पूर्ण,

	अणु"DAC L2 Mux", "IF1 DAC2", "IF1 DAC2 L"पूर्ण,
	अणु"DAC L2 Mux", "IF2_1 DAC", "IF2_1 DAC L"पूर्ण,
	अणु"DAC L2 Mux", "IF2_2 DAC", "IF2_2 DAC L"पूर्ण,
	अणु"DAC L2 Mux", "IF3 DAC", "IF3 DAC L"पूर्ण,
	अणु"DAC L2 Mux", "Mono ADC MIX", "Mono ADC MIXL"पूर्ण,
	अणु"DAC L2 Mux", शून्य, "DAC Mono Left Filter"पूर्ण,

	अणु"DAC R2 Mux", "IF1 DAC2", "IF1 DAC2 R"पूर्ण,
	अणु"DAC R2 Mux", "IF2_1 DAC", "IF2_1 DAC R"पूर्ण,
	अणु"DAC R2 Mux", "IF2_2 DAC", "IF2_2 DAC R"पूर्ण,
	अणु"DAC R2 Mux", "IF3 DAC", "IF3 DAC R"पूर्ण,
	अणु"DAC R2 Mux", "Mono ADC MIX", "Mono ADC MIXR"पूर्ण,
	अणु"DAC R2 Mux", शून्य, "DAC Mono Right Filter"पूर्ण,

	अणु"DAC L3 Mux", "IF1 DAC2", "IF1 DAC2 L"पूर्ण,
	अणु"DAC L3 Mux", "IF2_1 DAC", "IF2_1 DAC L"पूर्ण,
	अणु"DAC L3 Mux", "IF2_2 DAC", "IF2_2 DAC L"पूर्ण,
	अणु"DAC L3 Mux", "IF3 DAC", "IF3 DAC L"पूर्ण,
	अणु"DAC L3 Mux", "STO2 ADC MIX", "Stereo2 ADC MIXL"पूर्ण,
	अणु"DAC L3 Mux", शून्य, "DAC Stereo2 Filter"पूर्ण,

	अणु"DAC R3 Mux", "IF1 DAC2", "IF1 DAC2 R"पूर्ण,
	अणु"DAC R3 Mux", "IF2_1 DAC", "IF2_1 DAC R"पूर्ण,
	अणु"DAC R3 Mux", "IF2_2 DAC", "IF2_2 DAC R"पूर्ण,
	अणु"DAC R3 Mux", "IF3 DAC", "IF3 DAC R"पूर्ण,
	अणु"DAC R3 Mux", "STO2 ADC MIX", "Stereo2 ADC MIXR"पूर्ण,
	अणु"DAC R3 Mux", शून्य, "DAC Stereo2 Filter"पूर्ण,

	अणु"Stereo1 DAC MIXL", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Stereo1 DAC MIXL", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Stereo1 DAC MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Stereo1 DAC MIXL", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,

	अणु"Stereo1 DAC MIXR", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Stereo1 DAC MIXR", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Stereo1 DAC MIXR", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Stereo1 DAC MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,

	अणु"Stereo2 DAC MIXL", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Stereo2 DAC MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Stereo2 DAC MIXL", "DAC L3 Switch", "DAC L3 Mux"पूर्ण,

	अणु"Stereo2 DAC MIXR", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Stereo2 DAC MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,
	अणु"Stereo2 DAC MIXR", "DAC R3 Switch", "DAC R3 Mux"पूर्ण,

	अणु"Mono DAC MIXL", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Mono DAC MIXL", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Mono DAC MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Mono DAC MIXL", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,
	अणु"Mono DAC MIXR", "DAC L1 Switch", "DAC1 MIXL"पूर्ण,
	अणु"Mono DAC MIXR", "DAC R1 Switch", "DAC1 MIXR"पूर्ण,
	अणु"Mono DAC MIXR", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Mono DAC MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,

	अणु"DAC MIXL", "Stereo1 DAC Mixer", "Stereo1 DAC MIXL"पूर्ण,
	अणु"DAC MIXL", "Stereo2 DAC Mixer", "Stereo2 DAC MIXL"पूर्ण,
	अणु"DAC MIXL", "Mono DAC Mixer", "Mono DAC MIXL"पूर्ण,
	अणु"DAC MIXR", "Stereo1 DAC Mixer", "Stereo1 DAC MIXR"पूर्ण,
	अणु"DAC MIXR", "Stereo2 DAC Mixer", "Stereo2 DAC MIXR"पूर्ण,
	अणु"DAC MIXR", "Mono DAC Mixer", "Mono DAC MIXR"पूर्ण,

	अणु"DAC L1 Source", "DAC1", "DAC1 MIXL"पूर्ण,
	अणु"DAC L1 Source", "Stereo1 DAC Mixer", "Stereo1 DAC MIXL"पूर्ण,
	अणु"DAC L1 Source", "DMIC1", "DMIC L1"पूर्ण,
	अणु"DAC R1 Source", "DAC1", "DAC1 MIXR"पूर्ण,
	अणु"DAC R1 Source", "Stereo1 DAC Mixer", "Stereo1 DAC MIXR"पूर्ण,
	अणु"DAC R1 Source", "DMIC1", "DMIC R1"पूर्ण,

	अणु"DAC L2 Source", "DAC2", "DAC L2 Mux"पूर्ण,
	अणु"DAC L2 Source", "Mono DAC Mixer", "Mono DAC MIXL"पूर्ण,
	अणु"DAC L2 Source", शून्य, "DAC L2 Power"पूर्ण,
	अणु"DAC R2 Source", "DAC2", "DAC R2 Mux"पूर्ण,
	अणु"DAC R2 Source", "Mono DAC Mixer", "Mono DAC MIXR"पूर्ण,
	अणु"DAC R2 Source", शून्य, "DAC R2 Power"पूर्ण,

	अणु"DAC L1", शून्य, "DAC L1 Source"पूर्ण,
	अणु"DAC R1", शून्य, "DAC R1 Source"पूर्ण,
	अणु"DAC L2", शून्य, "DAC L2 Source"पूर्ण,
	अणु"DAC R2", शून्य, "DAC R2 Source"पूर्ण,

	अणु"DAC L1", शून्य, "DAC 1 Clock"पूर्ण,
	अणु"DAC R1", शून्य, "DAC 1 Clock"पूर्ण,
	अणु"DAC L2", शून्य, "DAC 2 Clock"पूर्ण,
	अणु"DAC R2", शून्य, "DAC 2 Clock"पूर्ण,

	अणु"MONOVOL MIX", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"MONOVOL MIX", "RECMIX2L Switch", "RECMIX2L"पूर्ण,
	अणु"MONOVOL MIX", "BST1 Switch", "BST1"पूर्ण,
	अणु"MONOVOL MIX", "BST2 Switch", "BST2"पूर्ण,
	अणु"MONOVOL MIX", "BST3 Switch", "BST3"पूर्ण,

	अणु"OUT MIXL", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"OUT MIXL", "INL Switch", "INL VOL"पूर्ण,
	अणु"OUT MIXL", "BST1 Switch", "BST1"पूर्ण,
	अणु"OUT MIXL", "BST2 Switch", "BST2"पूर्ण,
	अणु"OUT MIXL", "BST3 Switch", "BST3"पूर्ण,
	अणु"OUT MIXR", "DAC R2 Switch", "DAC R2"पूर्ण,
	अणु"OUT MIXR", "INR Switch", "INR VOL"पूर्ण,
	अणु"OUT MIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"OUT MIXR", "BST3 Switch", "BST3"पूर्ण,
	अणु"OUT MIXR", "BST4 Switch", "BST4"पूर्ण,

	अणु"MONOVOL", "Switch", "MONOVOL MIX"पूर्ण,
	अणु"Mono MIX", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"Mono MIX", "MONOVOL Switch", "MONOVOL"पूर्ण,
	अणु"Mono Amp", शून्य, "Mono MIX"पूर्ण,
	अणु"Mono Amp", शून्य, "Vref2"पूर्ण,
	अणु"Mono Amp", शून्य, "Vref3"पूर्ण,
	अणु"Mono Amp", शून्य, "CLKDET SYS"पूर्ण,
	अणु"Mono Amp", शून्य, "CLKDET MONO"पूर्ण,
	अणु"Mono Playback", "Switch", "Mono Amp"पूर्ण,
	अणु"MONOOUT", शून्य, "Mono Playback"पूर्ण,

	अणु"HP Amp", शून्य, "DAC L1"पूर्ण,
	अणु"HP Amp", शून्य, "DAC R1"पूर्ण,
	अणु"HP Amp", शून्य, "Charge Pump"पूर्ण,
	अणु"HP Amp", शून्य, "CLKDET SYS"पूर्ण,
	अणु"HP Amp", शून्य, "CLKDET HP"पूर्ण,
	अणु"HP Amp", शून्य, "CBJ Power"पूर्ण,
	अणु"HP Amp", शून्य, "Vref2"पूर्ण,
	अणु"HPO Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPOL", शून्य, "HPO Playback"पूर्ण,
	अणु"HPOR", शून्य, "HPO Playback"पूर्ण,

	अणु"OUTVOL L", "Switch", "OUT MIXL"पूर्ण,
	अणु"OUTVOL R", "Switch", "OUT MIXR"पूर्ण,
	अणु"LOUT L MIX", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"LOUT L MIX", "OUTVOL L Switch", "OUTVOL L"पूर्ण,
	अणु"LOUT R MIX", "DAC R2 Switch", "DAC R2"पूर्ण,
	अणु"LOUT R MIX", "OUTVOL R Switch", "OUTVOL R"पूर्ण,
	अणु"LOUT Amp", शून्य, "LOUT L MIX"पूर्ण,
	अणु"LOUT Amp", शून्य, "LOUT R MIX"पूर्ण,
	अणु"LOUT Amp", शून्य, "Vref1"पूर्ण,
	अणु"LOUT Amp", शून्य, "Vref2"पूर्ण,
	अणु"LOUT Amp", शून्य, "CLKDET SYS"पूर्ण,
	अणु"LOUT Amp", शून्य, "CLKDET LOUT"पूर्ण,
	अणु"LOUT L Playback", "Switch", "LOUT Amp"पूर्ण,
	अणु"LOUT R Playback", "Switch", "LOUT Amp"पूर्ण,
	अणु"LOUTL", शून्य, "LOUT L Playback"पूर्ण,
	अणु"LOUTR", शून्य, "LOUT R Playback"पूर्ण,

	अणु"PDM L Mux", "Mono DAC", "Mono DAC MIXL"पूर्ण,
	अणु"PDM L Mux", "Stereo1 DAC", "Stereo1 DAC MIXL"पूर्ण,
	अणु"PDM L Mux", "Stereo2 DAC", "Stereo2 DAC MIXL"पूर्ण,
	अणु"PDM L Mux", शून्य, "PDM Power"पूर्ण,
	अणु"PDM R Mux", "Mono DAC", "Mono DAC MIXR"पूर्ण,
	अणु"PDM R Mux", "Stereo1 DAC", "Stereo1 DAC MIXR"पूर्ण,
	अणु"PDM R Mux", "Stereo2 DAC", "Stereo2 DAC MIXR"पूर्ण,
	अणु"PDM R Mux", शून्य, "PDM Power"पूर्ण,
	अणु"PDM L Playback", "Switch", "PDM L Mux"पूर्ण,
	अणु"PDM R Playback", "Switch", "PDM R Mux"पूर्ण,
	अणु"PDML", शून्य, "PDM L Playback"पूर्ण,
	अणु"PDMR", शून्य, "PDM R Playback"पूर्ण,
पूर्ण;

अटल पूर्णांक rt5665_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;

	अगर (rx_mask || tx_mask)
		val |= RT5665_I2S1_MODE_TDM;

	चयन (slots) अणु
	हाल 4:
		val |= RT5665_TDM_IN_CH_4;
		val |= RT5665_TDM_OUT_CH_4;
		अवरोध;
	हाल 6:
		val |= RT5665_TDM_IN_CH_6;
		val |= RT5665_TDM_OUT_CH_6;
		अवरोध;
	हाल 8:
		val |= RT5665_TDM_IN_CH_8;
		val |= RT5665_TDM_OUT_CH_8;
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= RT5665_TDM_IN_LEN_20;
		val |= RT5665_TDM_OUT_LEN_20;
		अवरोध;
	हाल 24:
		val |= RT5665_TDM_IN_LEN_24;
		val |= RT5665_TDM_OUT_LEN_24;
		अवरोध;
	हाल 32:
		val |= RT5665_TDM_IN_LEN_32;
		val |= RT5665_TDM_OUT_LEN_32;
		अवरोध;
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5665_TDM_CTRL_1,
		RT5665_I2S1_MODE_MASK | RT5665_TDM_IN_CH_MASK |
		RT5665_TDM_OUT_CH_MASK | RT5665_TDM_IN_LEN_MASK |
		RT5665_TDM_OUT_LEN_MASK, val);

	वापस 0;
पूर्ण


अटल पूर्णांक rt5665_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, reg_clk, mask_clk, val_bits = 0x0100;
	पूर्णांक pre_भाग, frame_size;

	rt5665->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5665->sysclk, rt5665->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_warn(component->dev, "Force using PLL");
		snd_soc_component_set_pll(component, 0, RT5665_PLL1_S_MCLK,
			rt5665->sysclk,	rt5665->lrck[dai->id] * 512);
		snd_soc_component_set_sysclk(component, RT5665_SCLK_S_PLL1, 0,
			rt5665->lrck[dai->id] * 512, 0);
		pre_भाग = 1;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt5665->lrck[dai->id], pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		val_bits = 0x0100;
		अवरोध;
	हाल 20:
		val_len |= RT5665_I2S_DL_20;
		val_bits = 0x1300;
		अवरोध;
	हाल 24:
		val_len |= RT5665_I2S_DL_24;
		val_bits = 0x2500;
		अवरोध;
	हाल 8:
		val_len |= RT5665_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5665_AIF1_1:
	हाल RT5665_AIF1_2:
		अगर (params_channels(params) > 2)
			rt5665_set_tdm_slot(dai, 0xf, 0xf,
				params_channels(params), params_width(params));
		reg_clk = RT5665_ADDA_CLK_1;
		mask_clk = RT5665_I2S_PD1_MASK;
		val_clk = pre_भाग << RT5665_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S1_SDP,
			RT5665_I2S_DL_MASK, val_len);
		अवरोध;
	हाल RT5665_AIF2_1:
	हाल RT5665_AIF2_2:
		reg_clk = RT5665_ADDA_CLK_2;
		mask_clk = RT5665_I2S_PD2_MASK;
		val_clk = pre_भाग << RT5665_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S2_SDP,
			RT5665_I2S_DL_MASK, val_len);
		अवरोध;
	हाल RT5665_AIF3:
		reg_clk = RT5665_ADDA_CLK_2;
		mask_clk = RT5665_I2S_PD3_MASK;
		val_clk = pre_भाग << RT5665_I2S_PD3_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S3_SDP,
			RT5665_I2S_DL_MASK, val_len);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, reg_clk, mask_clk, val_clk);
	snd_soc_component_update_bits(component, RT5665_STO1_DAC_SIL_DET, 0x3700, val_bits);

	चयन (rt5665->lrck[dai->id]) अणु
	हाल 192000:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_32 | RT5665_ADC_OSR_32);
		अवरोध;
	हाल 96000:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_64 | RT5665_ADC_OSR_64);
		अवरोध;
	शेष:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_128 | RT5665_ADC_OSR_128);
		अवरोध;
	पूर्ण

	अगर (rt5665->master[RT5665_AIF2_1] || rt5665->master[RT5665_AIF2_2]) अणु
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S2_M_PD_MASK, pre_भाग << RT5665_I2S2_M_PD_SFT);
	पूर्ण
	अगर (rt5665->master[RT5665_AIF3]) अणु
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S3_M_PD_MASK, pre_भाग << RT5665_I2S3_M_PD_SFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5665->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5665_I2S_MS_S;
		rt5665->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5665_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5665_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5665_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5665_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5665_AIF1_1:
	हाल RT5665_AIF1_2:
		snd_soc_component_update_bits(component, RT5665_I2S1_SDP,
			RT5665_I2S_MS_MASK | RT5665_I2S_BP_MASK |
			RT5665_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5665_AIF2_1:
	हाल RT5665_AIF2_2:
		snd_soc_component_update_bits(component, RT5665_I2S2_SDP,
			RT5665_I2S_MS_MASK | RT5665_I2S_BP_MASK |
			RT5665_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5665_AIF3:
		snd_soc_component_update_bits(component, RT5665_I2S3_SDP,
			RT5665_I2S_MS_MASK | RT5665_I2S_BP_MASK |
			RT5665_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_component_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
				   पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, src = 0;

	अगर (freq == rt5665->sysclk && clk_id == rt5665->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5665_SCLK_S_MCLK:
		reg_val |= RT5665_SCLK_SRC_MCLK;
		src = RT5665_CLK_SRC_MCLK;
		अवरोध;
	हाल RT5665_SCLK_S_PLL1:
		reg_val |= RT5665_SCLK_SRC_PLL1;
		src = RT5665_CLK_SRC_PLL1;
		अवरोध;
	हाल RT5665_SCLK_S_RCCLK:
		reg_val |= RT5665_SCLK_SRC_RCCLK;
		src = RT5665_CLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5665_GLB_CLK,
		RT5665_SCLK_SRC_MASK, reg_val);

	अगर (rt5665->master[RT5665_AIF2_1] || rt5665->master[RT5665_AIF2_2]) अणु
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S2_SRC_MASK, src << RT5665_I2S2_SRC_SFT);
	पूर्ण
	अगर (rt5665->master[RT5665_AIF3]) अणु
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S3_SRC_MASK, src << RT5665_I2S3_SRC_SFT);
	पूर्ण

	rt5665->sysclk = freq;
	rt5665->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_component_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
				पूर्णांक source, अचिन्हित पूर्णांक freq_in,
				अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5665->pll_src && freq_in == rt5665->pll_in &&
	    freq_out == rt5665->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5665->pll_in = 0;
		rt5665->pll_out = 0;
		snd_soc_component_update_bits(component, RT5665_GLB_CLK,
			RT5665_SCLK_SRC_MASK, RT5665_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5665_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5665_GLB_CLK,
			RT5665_PLL1_SRC_MASK, RT5665_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5665_PLL1_S_BCLK1:
		snd_soc_component_update_bits(component, RT5665_GLB_CLK,
				RT5665_PLL1_SRC_MASK, RT5665_PLL1_SRC_BCLK1);
		अवरोध;
	हाल RT5665_PLL1_S_BCLK2:
		snd_soc_component_update_bits(component, RT5665_GLB_CLK,
				RT5665_PLL1_SRC_MASK, RT5665_PLL1_SRC_BCLK2);
		अवरोध;
	हाल RT5665_PLL1_S_BCLK3:
		snd_soc_component_update_bits(component, RT5665_GLB_CLK,
				RT5665_PLL1_SRC_MASK, RT5665_PLL1_SRC_BCLK3);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL Source %d\n", source);
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

	snd_soc_component_ग_लिखो(component, RT5665_PLL_CTRL_1,
		pll_code.n_code << RT5665_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5665_PLL_CTRL_2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5665_PLL_M_SFT) |
		(pll_code.m_bp << RT5665_PLL_M_BP_SFT));

	rt5665->pll_in = freq_in;
	rt5665->pll_out = freq_out;
	rt5665->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s ratio=%d\n", __func__, ratio);

	rt5665->bclk[dai->id] = ratio;

	अगर (ratio == 64) अणु
		चयन (dai->id) अणु
		हाल RT5665_AIF2_1:
		हाल RT5665_AIF2_2:
			snd_soc_component_update_bits(component, RT5665_ADDA_CLK_2,
				RT5665_I2S_BCLK_MS2_MASK,
				RT5665_I2S_BCLK_MS2_64);
			अवरोध;
		हाल RT5665_AIF3:
			snd_soc_component_update_bits(component, RT5665_ADDA_CLK_2,
				RT5665_I2S_BCLK_MS3_MASK,
				RT5665_I2S_BCLK_MS3_64);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		regmap_update_bits(rt5665->regmap, RT5665_DIG_MISC,
			RT5665_DIG_GATE_CTRL, RT5665_DIG_GATE_CTRL);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(rt5665->regmap, RT5665_PWR_DIG_1,
			RT5665_PWR_LDO,	RT5665_PWR_LDO);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_1,
			RT5665_PWR_MB, RT5665_PWR_MB);
		regmap_update_bits(rt5665->regmap, RT5665_DIG_MISC,
			RT5665_DIG_GATE_CTRL, 0);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(rt5665->regmap, RT5665_PWR_DIG_1,
			RT5665_PWR_LDO, 0);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_1,
			RT5665_PWR_MB, 0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	rt5665->component = component;

	schedule_delayed_work(&rt5665->calibrate_work, msecs_to_jअगरfies(100));

	वापस 0;
पूर्ण

अटल व्योम rt5665_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5665_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5665->regmap, true);
	regcache_mark_dirty(rt5665->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5665_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5665->regmap, false);
	regcache_sync(rt5665->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5665_suspend शून्य
#घोषणा rt5665_resume शून्य
#पूर्ण_अगर

#घोषणा RT5665_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT5665_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5665_aअगर_dai_ops = अणु
	.hw_params = rt5665_hw_params,
	.set_fmt = rt5665_set_dai_fmt,
	.set_tdm_slot = rt5665_set_tdm_slot,
	.set_bclk_ratio = rt5665_set_bclk_ratio,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5665_dai[] = अणु
	अणु
		.name = "rt5665-aif1_1",
		.id = RT5665_AIF1_1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1_1 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.ops = &rt5665_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5665-aif1_2",
		.id = RT5665_AIF1_2,
		.capture = अणु
			.stream_name = "AIF1_2 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.ops = &rt5665_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5665-aif2_1",
		.id = RT5665_AIF2_1,
		.playback = अणु
			.stream_name = "AIF2_1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2_1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.ops = &rt5665_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5665-aif2_2",
		.id = RT5665_AIF2_2,
		.playback = अणु
			.stream_name = "AIF2_2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2_2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.ops = &rt5665_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5665-aif3",
		.id = RT5665_AIF3,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5665_STEREO_RATES,
			.क्रमmats = RT5665_FORMATS,
		पूर्ण,
		.ops = &rt5665_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5665 = अणु
	.probe			= rt5665_probe,
	.हटाओ			= rt5665_हटाओ,
	.suspend		= rt5665_suspend,
	.resume			= rt5665_resume,
	.set_bias_level		= rt5665_set_bias_level,
	.controls		= rt5665_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5665_snd_controls),
	.dapm_widमाला_लो		= rt5665_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5665_dapm_widमाला_लो),
	.dapm_routes		= rt5665_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5665_dapm_routes),
	.set_sysclk		= rt5665_set_component_sysclk,
	.set_pll		= rt5665_set_component_pll,
	.set_jack		= rt5665_set_jack_detect,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;


अटल स्थिर काष्ठा regmap_config rt5665_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = 0x0400,
	.अस्थिर_reg = rt5665_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5665_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5665_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5665_reg),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5665_i2c_id[] = अणु
	अणु"rt5665", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5665_i2c_id);

अटल पूर्णांक rt5665_parse_dt(काष्ठा rt5665_priv *rt5665, काष्ठा device *dev)
अणु
	rt5665->pdata.in1_dअगरf = of_property_पढ़ो_bool(dev->of_node,
					"realtek,in1-differential");
	rt5665->pdata.in2_dअगरf = of_property_पढ़ो_bool(dev->of_node,
					"realtek,in2-differential");
	rt5665->pdata.in3_dअगरf = of_property_पढ़ो_bool(dev->of_node,
					"realtek,in3-differential");
	rt5665->pdata.in4_dअगरf = of_property_पढ़ो_bool(dev->of_node,
					"realtek,in4-differential");

	of_property_पढ़ो_u32(dev->of_node, "realtek,dmic1-data-pin",
		&rt5665->pdata.dmic1_data_pin);
	of_property_पढ़ो_u32(dev->of_node, "realtek,dmic2-data-pin",
		&rt5665->pdata.dmic2_data_pin);
	of_property_पढ़ो_u32(dev->of_node, "realtek,jd-src",
		&rt5665->pdata.jd_src);

	rt5665->pdata.lकरो1_en = of_get_named_gpio(dev->of_node,
		"realtek,ldo1-en-gpios", 0);

	वापस 0;
पूर्ण

अटल व्योम rt5665_calibrate(काष्ठा rt5665_priv *rt5665)
अणु
	पूर्णांक value, count;

	mutex_lock(&rt5665->calibrate_mutex);

	regcache_cache_bypass(rt5665->regmap, true);

	regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
	regmap_ग_लिखो(rt5665->regmap, RT5665_BIAS_CUR_CTRL_8, 0xa602);
	regmap_ग_लिखो(rt5665->regmap, RT5665_HP_CHARGE_PUMP_1, 0x0c26);
	regmap_ग_लिखो(rt5665->regmap, RT5665_MONOMIX_IN_GAIN, 0x021f);
	regmap_ग_लिखो(rt5665->regmap, RT5665_MONO_OUT, 0x480a);
	regmap_ग_लिखो(rt5665->regmap, RT5665_PWR_MIXER, 0x083f);
	regmap_ग_लिखो(rt5665->regmap, RT5665_PWR_DIG_1, 0x0180);
	regmap_ग_लिखो(rt5665->regmap, RT5665_EJD_CTRL_1, 0x4040);
	regmap_ग_लिखो(rt5665->regmap, RT5665_HP_LOGIC_CTRL_2, 0x0000);
	regmap_ग_लिखो(rt5665->regmap, RT5665_DIG_MISC, 0x0001);
	regmap_ग_लिखो(rt5665->regmap, RT5665_MICBIAS_2, 0x0380);
	regmap_ग_लिखो(rt5665->regmap, RT5665_GLB_CLK, 0x8000);
	regmap_ग_लिखो(rt5665->regmap, RT5665_ADDA_CLK_1, 0x1000);
	regmap_ग_लिखो(rt5665->regmap, RT5665_CHOP_DAC, 0x3030);
	regmap_ग_लिखो(rt5665->regmap, RT5665_CALIB_ADC_CTRL, 0x3c05);
	regmap_ग_लिखो(rt5665->regmap, RT5665_PWR_ANLG_1, 0xaa3e);
	usleep_range(15000, 20000);
	regmap_ग_लिखो(rt5665->regmap, RT5665_PWR_ANLG_1, 0xfe7e);
	regmap_ग_लिखो(rt5665->regmap, RT5665_HP_CALIB_CTRL_2, 0x0321);

	regmap_ग_लिखो(rt5665->regmap, RT5665_HP_CALIB_CTRL_1, 0xfc00);
	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5665->regmap, RT5665_HP_CALIB_STA_1, &value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 60) अणु
			pr_err("HP Calibration Failure\n");
			regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
			regcache_cache_bypass(rt5665->regmap, false);
			जाओ out_unlock;
		पूर्ण

		count++;
	पूर्ण

	regmap_ग_लिखो(rt5665->regmap, RT5665_MONO_AMP_CALIB_CTRL_1, 0x9e24);
	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5665->regmap, RT5665_MONO_AMP_CALIB_STA1, &value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 60) अणु
			pr_err("MONO Calibration Failure\n");
			regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
			regcache_cache_bypass(rt5665->regmap, false);
			जाओ out_unlock;
		पूर्ण

		count++;
	पूर्ण

	regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
	regcache_cache_bypass(rt5665->regmap, false);

	regcache_mark_dirty(rt5665->regmap);
	regcache_sync(rt5665->regmap);

	regmap_ग_लिखो(rt5665->regmap, RT5665_BIAS_CUR_CTRL_8, 0xa602);
	regmap_ग_लिखो(rt5665->regmap, RT5665_ASRC_8, 0x0120);

out_unlock:
	rt5665->calibration_करोne = true;
	mutex_unlock(&rt5665->calibrate_mutex);
पूर्ण

अटल व्योम rt5665_calibrate_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5665_priv *rt5665 = container_of(work, काष्ठा rt5665_priv,
		calibrate_work.work);

	जबतक (!rt5665->component->card->instantiated) अणु
		pr_debug("%s\n", __func__);
		usleep_range(10000, 15000);
	पूर्ण

	rt5665_calibrate(rt5665);
पूर्ण

अटल पूर्णांक rt5665_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5665_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt5665_priv *rt5665;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;

	rt5665 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5665_priv),
		GFP_KERNEL);

	अगर (rt5665 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5665);

	अगर (pdata)
		rt5665->pdata = *pdata;
	अन्यथा
		rt5665_parse_dt(rt5665, &i2c->dev);

	क्रम (i = 0; i < ARRAY_SIZE(rt5665->supplies); i++)
		rt5665->supplies[i].supply = rt5665_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(rt5665->supplies),
				      rt5665->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(rt5665->supplies),
				    rt5665->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (gpio_is_valid(rt5665->pdata.lकरो1_en)) अणु
		अगर (devm_gpio_request_one(&i2c->dev, rt5665->pdata.lकरो1_en,
					  GPIOF_OUT_INIT_HIGH, "rt5665"))
			dev_err(&i2c->dev, "Fail gpio_request gpio_ldo\n");
	पूर्ण

	/* Sleep क्रम 300 ms miniumum */
	usleep_range(300000, 350000);

	rt5665->regmap = devm_regmap_init_i2c(i2c, &rt5665_regmap);
	अगर (IS_ERR(rt5665->regmap)) अणु
		ret = PTR_ERR(rt5665->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5665->regmap, RT5665_DEVICE_ID, &val);
	अगर (val != DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt5665\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_पढ़ो(rt5665->regmap, RT5665_RESET, &val);
	चयन (val) अणु
	हाल 0x0:
		rt5665->id = CODEC_5666;
		अवरोध;
	हाल 0x3:
	शेष:
		rt5665->id = CODEC_5665;
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);

	/* line in dअगरf mode*/
	अगर (rt5665->pdata.in1_dअगरf)
		regmap_update_bits(rt5665->regmap, RT5665_IN1_IN2,
			RT5665_IN1_DF_MASK, RT5665_IN1_DF_MASK);
	अगर (rt5665->pdata.in2_dअगरf)
		regmap_update_bits(rt5665->regmap, RT5665_IN1_IN2,
			RT5665_IN2_DF_MASK, RT5665_IN2_DF_MASK);
	अगर (rt5665->pdata.in3_dअगरf)
		regmap_update_bits(rt5665->regmap, RT5665_IN3_IN4,
			RT5665_IN3_DF_MASK, RT5665_IN3_DF_MASK);
	अगर (rt5665->pdata.in4_dअगरf)
		regmap_update_bits(rt5665->regmap, RT5665_IN3_IN4,
			RT5665_IN4_DF_MASK, RT5665_IN4_DF_MASK);

	/* DMIC pin*/
	अगर (rt5665->pdata.dmic1_data_pin != RT5665_DMIC1_शून्य ||
		rt5665->pdata.dmic2_data_pin != RT5665_DMIC2_शून्य) अणु
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_2,
			RT5665_GP9_PIN_MASK, RT5665_GP9_PIN_DMIC1_SCL);
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_1,
				RT5665_GP8_PIN_MASK, RT5665_GP8_PIN_DMIC2_SCL);
		चयन (rt5665->pdata.dmic1_data_pin) अणु
		हाल RT5665_DMIC1_DATA_IN2N:
			regmap_update_bits(rt5665->regmap, RT5665_DMIC_CTRL_1,
				RT5665_DMIC_1_DP_MASK, RT5665_DMIC_1_DP_IN2N);
			अवरोध;

		हाल RT5665_DMIC1_DATA_GPIO4:
			regmap_update_bits(rt5665->regmap, RT5665_DMIC_CTRL_1,
				RT5665_DMIC_1_DP_MASK, RT5665_DMIC_1_DP_GPIO4);
			regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_1,
				RT5665_GP4_PIN_MASK, RT5665_GP4_PIN_DMIC1_SDA);
			अवरोध;

		शेष:
			dev_dbg(&i2c->dev, "no DMIC1\n");
			अवरोध;
		पूर्ण

		चयन (rt5665->pdata.dmic2_data_pin) अणु
		हाल RT5665_DMIC2_DATA_IN2P:
			regmap_update_bits(rt5665->regmap, RT5665_DMIC_CTRL_1,
				RT5665_DMIC_2_DP_MASK, RT5665_DMIC_2_DP_IN2P);
			अवरोध;

		हाल RT5665_DMIC2_DATA_GPIO5:
			regmap_update_bits(rt5665->regmap,
				RT5665_DMIC_CTRL_1,
				RT5665_DMIC_2_DP_MASK,
				RT5665_DMIC_2_DP_GPIO5);
			regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_1,
				RT5665_GP5_PIN_MASK, RT5665_GP5_PIN_DMIC2_SDA);
			अवरोध;

		शेष:
			dev_dbg(&i2c->dev, "no DMIC2\n");
			अवरोध;

		पूर्ण
	पूर्ण

	regmap_ग_लिखो(rt5665->regmap, RT5665_HP_LOGIC_CTRL_2, 0x0002);
	regmap_update_bits(rt5665->regmap, RT5665_EJD_CTRL_1,
		0xf000 | RT5665_VREF_POW_MASK, 0xe000 | RT5665_VREF_POW_REG);
	/* Work around क्रम घात_pump */
	regmap_update_bits(rt5665->regmap, RT5665_STO1_DAC_SIL_DET,
		RT5665_DEB_STO_DAC_MASK, RT5665_DEB_80_MS);

	regmap_update_bits(rt5665->regmap, RT5665_HP_CHARGE_PUMP_1,
		RT5665_PM_HP_MASK, RT5665_PM_HP_HV);

	/* Set GPIO4,8 as input क्रम combo jack */
	अगर (rt5665->id == CODEC_5666) अणु
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_2,
			RT5665_GP4_PF_MASK, RT5665_GP4_PF_IN);
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_3,
			RT5665_GP8_PF_MASK, RT5665_GP8_PF_IN);
	पूर्ण

	/* Enhance perक्रमmance*/
	regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_1,
		RT5665_HP_DRIVER_MASK | RT5665_LDO1_DVO_MASK,
		RT5665_HP_DRIVER_5X | RT5665_LDO1_DVO_12);

	INIT_DELAYED_WORK(&rt5665->jack_detect_work,
				rt5665_jack_detect_handler);
	INIT_DELAYED_WORK(&rt5665->calibrate_work,
				rt5665_calibrate_handler);
	INIT_DELAYED_WORK(&rt5665->jd_check_work,
				rt5665_jd_check_handler);

	mutex_init(&rt5665->calibrate_mutex);

	अगर (i2c->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
			rt5665_irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5665", rt5665);
		अगर (ret)
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);

	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt5665,
			rt5665_dai, ARRAY_SIZE(rt5665_dai));
पूर्ण

अटल व्योम rt5665_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5665_priv *rt5665 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt5665->regmap, RT5665_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt5665_of_match[] = अणु
	अणु.compatible = "realtek,rt5665"पूर्ण,
	अणु.compatible = "realtek,rt5666"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5665_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5665_acpi_match[] = अणु
	अणु"10EC5665", 0,पूर्ण,
	अणु"10EC5666", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5665_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver rt5665_i2c_driver = अणु
	.driver = अणु
		.name = "rt5665",
		.of_match_table = of_match_ptr(rt5665_of_match),
		.acpi_match_table = ACPI_PTR(rt5665_acpi_match),
	पूर्ण,
	.probe = rt5665_i2c_probe,
	.shutकरोwn = rt5665_i2c_shutकरोwn,
	.id_table = rt5665_i2c_id,
पूर्ण;
module_i2c_driver(rt5665_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5665 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
