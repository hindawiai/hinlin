<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5659.c  --  RT5659/RT5658 ALSA SoC audio codec driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/clk.h>
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
#समावेश <linux/gpio/consumer.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/rt5659.h>

#समावेश "rl6231.h"
#समावेश "rt5659.h"

अटल स्थिर काष्ठा reg_शेष rt5659_reg[] = अणु
	अणु 0x0000, 0x0000 पूर्ण,
	अणु 0x0001, 0x4848 पूर्ण,
	अणु 0x0002, 0x8080 पूर्ण,
	अणु 0x0003, 0xc8c8 पूर्ण,
	अणु 0x0004, 0xc80a पूर्ण,
	अणु 0x0005, 0x0000 पूर्ण,
	अणु 0x0006, 0x0000 पूर्ण,
	अणु 0x0007, 0x0103 पूर्ण,
	अणु 0x0008, 0x0080 पूर्ण,
	अणु 0x0009, 0x0000 पूर्ण,
	अणु 0x000a, 0x0000 पूर्ण,
	अणु 0x000c, 0x0000 पूर्ण,
	अणु 0x000d, 0x0000 पूर्ण,
	अणु 0x000f, 0x0808 पूर्ण,
	अणु 0x0010, 0x3080 पूर्ण,
	अणु 0x0011, 0x4a00 पूर्ण,
	अणु 0x0012, 0x4e00 पूर्ण,
	अणु 0x0015, 0x42c1 पूर्ण,
	अणु 0x0016, 0x0000 पूर्ण,
	अणु 0x0018, 0x000b पूर्ण,
	अणु 0x0019, 0xafaf पूर्ण,
	अणु 0x001a, 0xafaf पूर्ण,
	अणु 0x001b, 0x0011 पूर्ण,
	अणु 0x001c, 0x2f2f पूर्ण,
	अणु 0x001d, 0x2f2f पूर्ण,
	अणु 0x001e, 0x2f2f पूर्ण,
	अणु 0x001f, 0x0000 पूर्ण,
	अणु 0x0020, 0x0000 पूर्ण,
	अणु 0x0021, 0x0000 पूर्ण,
	अणु 0x0022, 0x5757 पूर्ण,
	अणु 0x0023, 0x0039 पूर्ण,
	अणु 0x0026, 0xc060 पूर्ण,
	अणु 0x0027, 0xd8d8 पूर्ण,
	अणु 0x0029, 0x8080 पूर्ण,
	अणु 0x002a, 0xaaaa पूर्ण,
	अणु 0x002b, 0xaaaa पूर्ण,
	अणु 0x002c, 0x00af पूर्ण,
	अणु 0x002d, 0x0000 पूर्ण,
	अणु 0x002f, 0x1002 पूर्ण,
	अणु 0x0031, 0x5000 पूर्ण,
	अणु 0x0032, 0x0000 पूर्ण,
	अणु 0x0033, 0x0000 पूर्ण,
	अणु 0x0034, 0x0000 पूर्ण,
	अणु 0x0035, 0x0000 पूर्ण,
	अणु 0x0036, 0x0000 पूर्ण,
	अणु 0x003a, 0x0000 पूर्ण,
	अणु 0x003b, 0x0000 पूर्ण,
	अणु 0x003c, 0x007f पूर्ण,
	अणु 0x003d, 0x0000 पूर्ण,
	अणु 0x003e, 0x007f पूर्ण,
	अणु 0x0040, 0x0808 पूर्ण,
	अणु 0x0046, 0x001f पूर्ण,
	अणु 0x0047, 0x001f पूर्ण,
	अणु 0x0048, 0x0003 पूर्ण,
	अणु 0x0049, 0xe061 पूर्ण,
	अणु 0x004a, 0x0000 पूर्ण,
	अणु 0x004b, 0x031f पूर्ण,
	अणु 0x004d, 0x0000 पूर्ण,
	अणु 0x004e, 0x001f पूर्ण,
	अणु 0x004f, 0x0000 पूर्ण,
	अणु 0x0050, 0x001f पूर्ण,
	अणु 0x0052, 0xf000 पूर्ण,
	अणु 0x0053, 0x0111 पूर्ण,
	अणु 0x0054, 0x0064 पूर्ण,
	अणु 0x0055, 0x0080 पूर्ण,
	अणु 0x0056, 0xef0e पूर्ण,
	अणु 0x0057, 0xf0f0 पूर्ण,
	अणु 0x0058, 0xef0e पूर्ण,
	अणु 0x0059, 0xf0f0 पूर्ण,
	अणु 0x005a, 0xef0e पूर्ण,
	अणु 0x005b, 0xf0f0 पूर्ण,
	अणु 0x005c, 0xf000 पूर्ण,
	अणु 0x005d, 0x0000 पूर्ण,
	अणु 0x005e, 0x1f2c पूर्ण,
	अणु 0x005f, 0x1f2c पूर्ण,
	अणु 0x0060, 0x2717 पूर्ण,
	अणु 0x0061, 0x0000 पूर्ण,
	अणु 0x0062, 0x0000 पूर्ण,
	अणु 0x0063, 0x003e पूर्ण,
	अणु 0x0064, 0x0000 पूर्ण,
	अणु 0x0065, 0x0000 पूर्ण,
	अणु 0x0066, 0x0000 पूर्ण,
	अणु 0x0067, 0x0000 पूर्ण,
	अणु 0x006a, 0x0000 पूर्ण,
	अणु 0x006b, 0x0000 पूर्ण,
	अणु 0x006c, 0x0000 पूर्ण,
	अणु 0x006e, 0x0000 पूर्ण,
	अणु 0x006f, 0x0000 पूर्ण,
	अणु 0x0070, 0x8000 पूर्ण,
	अणु 0x0071, 0x8000 पूर्ण,
	अणु 0x0072, 0x8000 पूर्ण,
	अणु 0x0073, 0x1110 पूर्ण,
	अणु 0x0074, 0xfe00 पूर्ण,
	अणु 0x0075, 0x2409 पूर्ण,
	अणु 0x0076, 0x000a पूर्ण,
	अणु 0x0077, 0x00f0 पूर्ण,
	अणु 0x0078, 0x0000 पूर्ण,
	अणु 0x0079, 0x0000 पूर्ण,
	अणु 0x007a, 0x0123 पूर्ण,
	अणु 0x007b, 0x8003 पूर्ण,
	अणु 0x0080, 0x0000 पूर्ण,
	अणु 0x0081, 0x0000 पूर्ण,
	अणु 0x0082, 0x0000 पूर्ण,
	अणु 0x0083, 0x0000 पूर्ण,
	अणु 0x0084, 0x0000 पूर्ण,
	अणु 0x0085, 0x0000 पूर्ण,
	अणु 0x0086, 0x0008 पूर्ण,
	अणु 0x0087, 0x0000 पूर्ण,
	अणु 0x0088, 0x0000 पूर्ण,
	अणु 0x0089, 0x0000 पूर्ण,
	अणु 0x008a, 0x0000 पूर्ण,
	अणु 0x008b, 0x0000 पूर्ण,
	अणु 0x008c, 0x0003 पूर्ण,
	अणु 0x008e, 0x0000 पूर्ण,
	अणु 0x008f, 0x1000 पूर्ण,
	अणु 0x0090, 0x0646 पूर्ण,
	अणु 0x0091, 0x0c16 पूर्ण,
	अणु 0x0092, 0x0073 पूर्ण,
	अणु 0x0093, 0x0000 पूर्ण,
	अणु 0x0094, 0x0080 पूर्ण,
	अणु 0x0097, 0x0000 पूर्ण,
	अणु 0x0098, 0x0000 पूर्ण,
	अणु 0x0099, 0x0000 पूर्ण,
	अणु 0x009a, 0x0000 पूर्ण,
	अणु 0x009b, 0x0000 पूर्ण,
	अणु 0x009c, 0x007f पूर्ण,
	अणु 0x009d, 0x0000 पूर्ण,
	अणु 0x009e, 0x007f पूर्ण,
	अणु 0x009f, 0x0000 पूर्ण,
	अणु 0x00a0, 0x0060 पूर्ण,
	अणु 0x00a1, 0x90a1 पूर्ण,
	अणु 0x00ae, 0x2000 पूर्ण,
	अणु 0x00af, 0x0000 पूर्ण,
	अणु 0x00b0, 0x2000 पूर्ण,
	अणु 0x00b1, 0x0000 पूर्ण,
	अणु 0x00b2, 0x0000 पूर्ण,
	अणु 0x00b6, 0x0000 पूर्ण,
	अणु 0x00b7, 0x0000 पूर्ण,
	अणु 0x00b8, 0x0000 पूर्ण,
	अणु 0x00b9, 0x0000 पूर्ण,
	अणु 0x00ba, 0x0000 पूर्ण,
	अणु 0x00bb, 0x0000 पूर्ण,
	अणु 0x00be, 0x0000 पूर्ण,
	अणु 0x00bf, 0x0000 पूर्ण,
	अणु 0x00c0, 0x0000 पूर्ण,
	अणु 0x00c1, 0x0000 पूर्ण,
	अणु 0x00c2, 0x0000 पूर्ण,
	अणु 0x00c3, 0x0000 पूर्ण,
	अणु 0x00c4, 0x0003 पूर्ण,
	अणु 0x00c5, 0x0000 पूर्ण,
	अणु 0x00cb, 0xa02f पूर्ण,
	अणु 0x00cc, 0x0000 पूर्ण,
	अणु 0x00cd, 0x0e02 पूर्ण,
	अणु 0x00d6, 0x0000 पूर्ण,
	अणु 0x00d7, 0x2244 पूर्ण,
	अणु 0x00d9, 0x0809 पूर्ण,
	अणु 0x00da, 0x0000 पूर्ण,
	अणु 0x00db, 0x0008 पूर्ण,
	अणु 0x00dc, 0x00c0 पूर्ण,
	अणु 0x00dd, 0x6724 पूर्ण,
	अणु 0x00de, 0x3131 पूर्ण,
	अणु 0x00df, 0x0008 पूर्ण,
	अणु 0x00e0, 0x4000 पूर्ण,
	अणु 0x00e1, 0x3131 पूर्ण,
	अणु 0x00e4, 0x400c पूर्ण,
	अणु 0x00e5, 0x8031 पूर्ण,
	अणु 0x00ea, 0xb320 पूर्ण,
	अणु 0x00eb, 0x0000 पूर्ण,
	अणु 0x00ec, 0xb300 पूर्ण,
	अणु 0x00ed, 0x0000 पूर्ण,
	अणु 0x00f0, 0x0000 पूर्ण,
	अणु 0x00f1, 0x0202 पूर्ण,
	अणु 0x00f2, 0x0ddd पूर्ण,
	अणु 0x00f3, 0x0ddd पूर्ण,
	अणु 0x00f4, 0x0ddd पूर्ण,
	अणु 0x00f6, 0x0000 पूर्ण,
	अणु 0x00f7, 0x0000 पूर्ण,
	अणु 0x00f8, 0x0000 पूर्ण,
	अणु 0x00f9, 0x0000 पूर्ण,
	अणु 0x00fa, 0x8000 पूर्ण,
	अणु 0x00fb, 0x0000 पूर्ण,
	अणु 0x00fc, 0x0000 पूर्ण,
	अणु 0x00fd, 0x0001 पूर्ण,
	अणु 0x00fe, 0x10ec पूर्ण,
	अणु 0x00ff, 0x6311 पूर्ण,
	अणु 0x0100, 0xaaaa पूर्ण,
	अणु 0x010a, 0xaaaa पूर्ण,
	अणु 0x010b, 0x00a0 पूर्ण,
	अणु 0x010c, 0xaeae पूर्ण,
	अणु 0x010d, 0xaaaa पूर्ण,
	अणु 0x010e, 0xaaa8 पूर्ण,
	अणु 0x010f, 0xa0aa पूर्ण,
	अणु 0x0110, 0xe02a पूर्ण,
	अणु 0x0111, 0xa702 पूर्ण,
	अणु 0x0112, 0xaaaa पूर्ण,
	अणु 0x0113, 0x2800 पूर्ण,
	अणु 0x0116, 0x0000 पूर्ण,
	अणु 0x0117, 0x0f00 पूर्ण,
	अणु 0x011a, 0x0020 पूर्ण,
	अणु 0x011b, 0x0011 पूर्ण,
	अणु 0x011c, 0x0150 पूर्ण,
	अणु 0x011d, 0x0000 पूर्ण,
	अणु 0x011e, 0x0000 पूर्ण,
	अणु 0x011f, 0x0000 पूर्ण,
	अणु 0x0120, 0x0000 पूर्ण,
	अणु 0x0121, 0x009b पूर्ण,
	अणु 0x0122, 0x5014 पूर्ण,
	अणु 0x0123, 0x0421 पूर्ण,
	अणु 0x0124, 0x7cea पूर्ण,
	अणु 0x0125, 0x0420 पूर्ण,
	अणु 0x0126, 0x5550 पूर्ण,
	अणु 0x0132, 0x0000 पूर्ण,
	अणु 0x0133, 0x0000 पूर्ण,
	अणु 0x0137, 0x5055 पूर्ण,
	अणु 0x0138, 0x3700 पूर्ण,
	अणु 0x0139, 0x79a1 पूर्ण,
	अणु 0x013a, 0x2020 पूर्ण,
	अणु 0x013b, 0x2020 पूर्ण,
	अणु 0x013c, 0x2005 पूर्ण,
	अणु 0x013e, 0x1f00 पूर्ण,
	अणु 0x013f, 0x0000 पूर्ण,
	अणु 0x0145, 0x0002 पूर्ण,
	अणु 0x0146, 0x0000 पूर्ण,
	अणु 0x0147, 0x0000 पूर्ण,
	अणु 0x0148, 0x0000 पूर्ण,
	अणु 0x0150, 0x1813 पूर्ण,
	अणु 0x0151, 0x0690 पूर्ण,
	अणु 0x0152, 0x1c17 पूर्ण,
	अणु 0x0153, 0x6883 पूर्ण,
	अणु 0x0154, 0xd3ce पूर्ण,
	अणु 0x0155, 0x352d पूर्ण,
	अणु 0x0156, 0x00eb पूर्ण,
	अणु 0x0157, 0x3717 पूर्ण,
	अणु 0x0158, 0x4c6a पूर्ण,
	अणु 0x0159, 0xe41b पूर्ण,
	अणु 0x015a, 0x2a13 पूर्ण,
	अणु 0x015b, 0xb600 पूर्ण,
	अणु 0x015c, 0xc730 पूर्ण,
	अणु 0x015d, 0x35d4 पूर्ण,
	अणु 0x015e, 0x00bf पूर्ण,
	अणु 0x0160, 0x0ec0 पूर्ण,
	अणु 0x0161, 0x0020 पूर्ण,
	अणु 0x0162, 0x0080 पूर्ण,
	अणु 0x0163, 0x0800 पूर्ण,
	अणु 0x0164, 0x0000 पूर्ण,
	अणु 0x0165, 0x0000 पूर्ण,
	अणु 0x0166, 0x0000 पूर्ण,
	अणु 0x0167, 0x001f पूर्ण,
	अणु 0x0170, 0x4e80 पूर्ण,
	अणु 0x0171, 0x0020 पूर्ण,
	अणु 0x0172, 0x0080 पूर्ण,
	अणु 0x0173, 0x0800 पूर्ण,
	अणु 0x0174, 0x000c पूर्ण,
	अणु 0x0175, 0x0000 पूर्ण,
	अणु 0x0190, 0x3300 पूर्ण,
	अणु 0x0191, 0x2200 पूर्ण,
	अणु 0x0192, 0x0000 पूर्ण,
	अणु 0x01b0, 0x4b38 पूर्ण,
	अणु 0x01b1, 0x0000 पूर्ण,
	अणु 0x01b2, 0x0000 पूर्ण,
	अणु 0x01b3, 0x0000 पूर्ण,
	अणु 0x01c0, 0x0045 पूर्ण,
	अणु 0x01c1, 0x0540 पूर्ण,
	अणु 0x01c2, 0x0000 पूर्ण,
	अणु 0x01c3, 0x0030 पूर्ण,
	अणु 0x01c7, 0x0000 पूर्ण,
	अणु 0x01c8, 0x5757 पूर्ण,
	अणु 0x01c9, 0x5757 पूर्ण,
	अणु 0x01ca, 0x5757 पूर्ण,
	अणु 0x01cb, 0x5757 पूर्ण,
	अणु 0x01cc, 0x5757 पूर्ण,
	अणु 0x01cd, 0x5757 पूर्ण,
	अणु 0x01ce, 0x006f पूर्ण,
	अणु 0x01da, 0x0000 पूर्ण,
	अणु 0x01db, 0x0000 पूर्ण,
	अणु 0x01de, 0x7d00 पूर्ण,
	अणु 0x01df, 0x10c0 पूर्ण,
	अणु 0x01e0, 0x06a1 पूर्ण,
	अणु 0x01e1, 0x0000 पूर्ण,
	अणु 0x01e2, 0x0000 पूर्ण,
	अणु 0x01e3, 0x0000 पूर्ण,
	अणु 0x01e4, 0x0001 पूर्ण,
	अणु 0x01e6, 0x0000 पूर्ण,
	अणु 0x01e7, 0x0000 पूर्ण,
	अणु 0x01e8, 0x0000 पूर्ण,
	अणु 0x01ea, 0x0000 पूर्ण,
	अणु 0x01eb, 0x0000 पूर्ण,
	अणु 0x01ec, 0x0000 पूर्ण,
	अणु 0x01ed, 0x0000 पूर्ण,
	अणु 0x01ee, 0x0000 पूर्ण,
	अणु 0x01ef, 0x0000 पूर्ण,
	अणु 0x01f0, 0x0000 पूर्ण,
	अणु 0x01f1, 0x0000 पूर्ण,
	अणु 0x01f2, 0x0000 पूर्ण,
	अणु 0x01f6, 0x1e04 पूर्ण,
	अणु 0x01f7, 0x01a1 पूर्ण,
	अणु 0x01f8, 0x0000 पूर्ण,
	अणु 0x01f9, 0x0000 पूर्ण,
	अणु 0x01fa, 0x0002 पूर्ण,
	अणु 0x01fb, 0x0000 पूर्ण,
	अणु 0x01fc, 0x0000 पूर्ण,
	अणु 0x01fd, 0x0000 पूर्ण,
	अणु 0x01fe, 0x0000 पूर्ण,
	अणु 0x0200, 0x066c पूर्ण,
	अणु 0x0201, 0x7fff पूर्ण,
	अणु 0x0202, 0x7fff पूर्ण,
	अणु 0x0203, 0x0000 पूर्ण,
	अणु 0x0204, 0x0000 पूर्ण,
	अणु 0x0205, 0x0000 पूर्ण,
	अणु 0x0206, 0x0000 पूर्ण,
	अणु 0x0207, 0x0000 पूर्ण,
	अणु 0x0208, 0x0000 पूर्ण,
	अणु 0x0256, 0x0000 पूर्ण,
	अणु 0x0257, 0x0000 पूर्ण,
	अणु 0x0258, 0x0000 पूर्ण,
	अणु 0x0259, 0x0000 पूर्ण,
	अणु 0x025a, 0x0000 पूर्ण,
	अणु 0x025b, 0x3333 पूर्ण,
	अणु 0x025c, 0x3333 पूर्ण,
	अणु 0x025d, 0x3333 पूर्ण,
	अणु 0x025e, 0x0000 पूर्ण,
	अणु 0x025f, 0x0000 पूर्ण,
	अणु 0x0260, 0x0000 पूर्ण,
	अणु 0x0261, 0x0022 पूर्ण,
	अणु 0x0262, 0x0300 पूर्ण,
	अणु 0x0265, 0x1e80 पूर्ण,
	अणु 0x0266, 0x0131 पूर्ण,
	अणु 0x0267, 0x0003 पूर्ण,
	अणु 0x0268, 0x0000 पूर्ण,
	अणु 0x0269, 0x0000 पूर्ण,
	अणु 0x026a, 0x0000 पूर्ण,
	अणु 0x026b, 0x0000 पूर्ण,
	अणु 0x026c, 0x0000 पूर्ण,
	अणु 0x026d, 0x0000 पूर्ण,
	अणु 0x026e, 0x0000 पूर्ण,
	अणु 0x026f, 0x0000 पूर्ण,
	अणु 0x0270, 0x0000 पूर्ण,
	अणु 0x0271, 0x0000 पूर्ण,
	अणु 0x0272, 0x0000 पूर्ण,
	अणु 0x0273, 0x0000 पूर्ण,
	अणु 0x0280, 0x0000 पूर्ण,
	अणु 0x0281, 0x0000 पूर्ण,
	अणु 0x0282, 0x0418 पूर्ण,
	अणु 0x0283, 0x7fff पूर्ण,
	अणु 0x0284, 0x7000 पूर्ण,
	अणु 0x0290, 0x01d0 पूर्ण,
	अणु 0x0291, 0x0100 पूर्ण,
	अणु 0x02fa, 0x0000 पूर्ण,
	अणु 0x02fb, 0x0000 पूर्ण,
	अणु 0x02fc, 0x0000 पूर्ण,
	अणु 0x0300, 0x001f पूर्ण,
	अणु 0x0301, 0x032c पूर्ण,
	अणु 0x0302, 0x5f21 पूर्ण,
	अणु 0x0303, 0x4000 पूर्ण,
	अणु 0x0304, 0x4000 पूर्ण,
	अणु 0x0305, 0x0600 पूर्ण,
	अणु 0x0306, 0x8000 पूर्ण,
	अणु 0x0307, 0x0700 पूर्ण,
	अणु 0x0308, 0x001f पूर्ण,
	अणु 0x0309, 0x032c पूर्ण,
	अणु 0x030a, 0x5f21 पूर्ण,
	अणु 0x030b, 0x4000 पूर्ण,
	अणु 0x030c, 0x4000 पूर्ण,
	अणु 0x030d, 0x0600 पूर्ण,
	अणु 0x030e, 0x8000 पूर्ण,
	अणु 0x030f, 0x0700 पूर्ण,
	अणु 0x0310, 0x4560 पूर्ण,
	अणु 0x0311, 0xa4a8 पूर्ण,
	अणु 0x0312, 0x7418 पूर्ण,
	अणु 0x0313, 0x0000 पूर्ण,
	अणु 0x0314, 0x0006 पूर्ण,
	अणु 0x0315, 0x00ff पूर्ण,
	अणु 0x0316, 0xc400 पूर्ण,
	अणु 0x0317, 0x4560 पूर्ण,
	अणु 0x0318, 0xa4a8 पूर्ण,
	अणु 0x0319, 0x7418 पूर्ण,
	अणु 0x031a, 0x0000 पूर्ण,
	अणु 0x031b, 0x0006 पूर्ण,
	अणु 0x031c, 0x00ff पूर्ण,
	अणु 0x031d, 0xc400 पूर्ण,
	अणु 0x0320, 0x0f20 पूर्ण,
	अणु 0x0321, 0x8700 पूर्ण,
	अणु 0x0322, 0x7dc2 पूर्ण,
	अणु 0x0323, 0xa178 पूर्ण,
	अणु 0x0324, 0x5383 पूर्ण,
	अणु 0x0325, 0x7dc2 पूर्ण,
	अणु 0x0326, 0xa178 पूर्ण,
	अणु 0x0327, 0x5383 पूर्ण,
	अणु 0x0328, 0x003e पूर्ण,
	अणु 0x0329, 0x02c1 पूर्ण,
	अणु 0x032a, 0xd37d पूर्ण,
	अणु 0x0330, 0x00a6 पूर्ण,
	अणु 0x0331, 0x04c3 पूर्ण,
	अणु 0x0332, 0x27c8 पूर्ण,
	अणु 0x0333, 0xbf50 पूर्ण,
	अणु 0x0334, 0x0045 पूर्ण,
	अणु 0x0335, 0x2007 पूर्ण,
	अणु 0x0336, 0x7418 पूर्ण,
	अणु 0x0337, 0x0501 पूर्ण,
	अणु 0x0338, 0x0000 पूर्ण,
	अणु 0x0339, 0x0010 पूर्ण,
	अणु 0x033a, 0x1010 पूर्ण,
	अणु 0x0340, 0x0800 पूर्ण,
	अणु 0x0341, 0x0800 पूर्ण,
	अणु 0x0342, 0x0800 पूर्ण,
	अणु 0x0343, 0x0800 पूर्ण,
	अणु 0x0344, 0x0000 पूर्ण,
	अणु 0x0345, 0x0000 पूर्ण,
	अणु 0x0346, 0x0000 पूर्ण,
	अणु 0x0347, 0x0000 पूर्ण,
	अणु 0x0348, 0x0000 पूर्ण,
	अणु 0x0349, 0x0000 पूर्ण,
	अणु 0x034a, 0x0000 पूर्ण,
	अणु 0x034b, 0x0000 पूर्ण,
	अणु 0x034c, 0x0000 पूर्ण,
	अणु 0x034d, 0x0000 पूर्ण,
	अणु 0x034e, 0x0000 पूर्ण,
	अणु 0x034f, 0x0000 पूर्ण,
	अणु 0x0350, 0x0000 पूर्ण,
	अणु 0x0351, 0x0000 पूर्ण,
	अणु 0x0352, 0x0000 पूर्ण,
	अणु 0x0353, 0x0000 पूर्ण,
	अणु 0x0354, 0x0000 पूर्ण,
	अणु 0x0355, 0x0000 पूर्ण,
	अणु 0x0356, 0x0000 पूर्ण,
	अणु 0x0357, 0x0000 पूर्ण,
	अणु 0x0358, 0x0000 पूर्ण,
	अणु 0x0359, 0x0000 पूर्ण,
	अणु 0x035a, 0x0000 पूर्ण,
	अणु 0x035b, 0x0000 पूर्ण,
	अणु 0x035c, 0x0000 पूर्ण,
	अणु 0x035d, 0x0000 पूर्ण,
	अणु 0x035e, 0x2000 पूर्ण,
	अणु 0x035f, 0x0000 पूर्ण,
	अणु 0x0360, 0x2000 पूर्ण,
	अणु 0x0361, 0x2000 पूर्ण,
	अणु 0x0362, 0x0000 पूर्ण,
	अणु 0x0363, 0x2000 पूर्ण,
	अणु 0x0364, 0x0200 पूर्ण,
	अणु 0x0365, 0x0000 पूर्ण,
	अणु 0x0366, 0x0000 पूर्ण,
	अणु 0x0367, 0x0000 पूर्ण,
	अणु 0x0368, 0x0000 पूर्ण,
	अणु 0x0369, 0x0000 पूर्ण,
	अणु 0x036a, 0x0000 पूर्ण,
	अणु 0x036b, 0x0000 पूर्ण,
	अणु 0x036c, 0x0000 पूर्ण,
	अणु 0x036d, 0x0000 पूर्ण,
	अणु 0x036e, 0x0200 पूर्ण,
	अणु 0x036f, 0x0000 पूर्ण,
	अणु 0x0370, 0x0000 पूर्ण,
	अणु 0x0371, 0x0000 पूर्ण,
	अणु 0x0372, 0x0000 पूर्ण,
	अणु 0x0373, 0x0000 पूर्ण,
	अणु 0x0374, 0x0000 पूर्ण,
	अणु 0x0375, 0x0000 पूर्ण,
	अणु 0x0376, 0x0000 पूर्ण,
	अणु 0x0377, 0x0000 पूर्ण,
	अणु 0x03d0, 0x0000 पूर्ण,
	अणु 0x03d1, 0x0000 पूर्ण,
	अणु 0x03d2, 0x0000 पूर्ण,
	अणु 0x03d3, 0x0000 पूर्ण,
	अणु 0x03d4, 0x2000 पूर्ण,
	अणु 0x03d5, 0x2000 पूर्ण,
	अणु 0x03d6, 0x0000 पूर्ण,
	अणु 0x03d7, 0x0000 पूर्ण,
	अणु 0x03d8, 0x2000 पूर्ण,
	अणु 0x03d9, 0x2000 पूर्ण,
	अणु 0x03da, 0x2000 पूर्ण,
	अणु 0x03db, 0x2000 पूर्ण,
	अणु 0x03dc, 0x0000 पूर्ण,
	अणु 0x03dd, 0x0000 पूर्ण,
	अणु 0x03de, 0x0000 पूर्ण,
	अणु 0x03df, 0x2000 पूर्ण,
	अणु 0x03e0, 0x0000 पूर्ण,
	अणु 0x03e1, 0x0000 पूर्ण,
	अणु 0x03e2, 0x0000 पूर्ण,
	अणु 0x03e3, 0x0000 पूर्ण,
	अणु 0x03e4, 0x0000 पूर्ण,
	अणु 0x03e5, 0x0000 पूर्ण,
	अणु 0x03e6, 0x0000 पूर्ण,
	अणु 0x03e7, 0x0000 पूर्ण,
	अणु 0x03e8, 0x0000 पूर्ण,
	अणु 0x03e9, 0x0000 पूर्ण,
	अणु 0x03ea, 0x0000 पूर्ण,
	अणु 0x03eb, 0x0000 पूर्ण,
	अणु 0x03ec, 0x0000 पूर्ण,
	अणु 0x03ed, 0x0000 पूर्ण,
	अणु 0x03ee, 0x0000 पूर्ण,
	अणु 0x03ef, 0x0000 पूर्ण,
	अणु 0x03f0, 0x0800 पूर्ण,
	अणु 0x03f1, 0x0800 पूर्ण,
	अणु 0x03f2, 0x0800 पूर्ण,
	अणु 0x03f3, 0x0800 पूर्ण,
पूर्ण;

अटल bool rt5659_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5659_RESET:
	हाल RT5659_EJD_CTRL_2:
	हाल RT5659_SILENCE_CTRL:
	हाल RT5659_DAC2_DIG_VOL:
	हाल RT5659_HP_IMP_GAIN_2:
	हाल RT5659_PDM_OUT_CTRL:
	हाल RT5659_PDM_DATA_CTRL_1:
	हाल RT5659_PDM_DATA_CTRL_4:
	हाल RT5659_HAPTIC_GEN_CTRL_1:
	हाल RT5659_HAPTIC_GEN_CTRL_3:
	हाल RT5659_HAPTIC_LPF_CTRL_3:
	हाल RT5659_CLK_DET:
	हाल RT5659_MICBIAS_1:
	हाल RT5659_ASRC_11:
	हाल RT5659_ADC_EQ_CTRL_1:
	हाल RT5659_DAC_EQ_CTRL_1:
	हाल RT5659_INT_ST_1:
	हाल RT5659_INT_ST_2:
	हाल RT5659_GPIO_STA:
	हाल RT5659_SINE_GEN_CTRL_1:
	हाल RT5659_IL_CMD_1:
	हाल RT5659_4BTN_IL_CMD_1:
	हाल RT5659_PSV_IL_CMD_1:
	हाल RT5659_AJD1_CTRL:
	हाल RT5659_AJD2_AJD3_CTRL:
	हाल RT5659_JD_CTRL_3:
	हाल RT5659_VENDOR_ID:
	हाल RT5659_VENDOR_ID_1:
	हाल RT5659_DEVICE_ID:
	हाल RT5659_MEMORY_TEST:
	हाल RT5659_SOFT_RAMP_DEPOP_DAC_CLK_CTRL:
	हाल RT5659_VOL_TEST:
	हाल RT5659_STO_NG2_CTRL_1:
	हाल RT5659_STO_NG2_CTRL_5:
	हाल RT5659_STO_NG2_CTRL_6:
	हाल RT5659_STO_NG2_CTRL_7:
	हाल RT5659_MONO_NG2_CTRL_1:
	हाल RT5659_MONO_NG2_CTRL_5:
	हाल RT5659_MONO_NG2_CTRL_6:
	हाल RT5659_HP_IMP_SENS_CTRL_1:
	हाल RT5659_HP_IMP_SENS_CTRL_3:
	हाल RT5659_HP_IMP_SENS_CTRL_4:
	हाल RT5659_HP_CALIB_CTRL_1:
	हाल RT5659_HP_CALIB_CTRL_9:
	हाल RT5659_HP_CALIB_STA_1:
	हाल RT5659_HP_CALIB_STA_2:
	हाल RT5659_HP_CALIB_STA_3:
	हाल RT5659_HP_CALIB_STA_4:
	हाल RT5659_HP_CALIB_STA_5:
	हाल RT5659_HP_CALIB_STA_6:
	हाल RT5659_HP_CALIB_STA_7:
	हाल RT5659_HP_CALIB_STA_8:
	हाल RT5659_HP_CALIB_STA_9:
	हाल RT5659_MONO_AMP_CALIB_CTRL_1:
	हाल RT5659_MONO_AMP_CALIB_CTRL_3:
	हाल RT5659_MONO_AMP_CALIB_STA_1:
	हाल RT5659_MONO_AMP_CALIB_STA_2:
	हाल RT5659_MONO_AMP_CALIB_STA_3:
	हाल RT5659_MONO_AMP_CALIB_STA_4:
	हाल RT5659_SPK_PWR_LMT_STA_1:
	हाल RT5659_SPK_PWR_LMT_STA_2:
	हाल RT5659_SPK_PWR_LMT_STA_3:
	हाल RT5659_SPK_PWR_LMT_STA_4:
	हाल RT5659_SPK_PWR_LMT_STA_5:
	हाल RT5659_SPK_PWR_LMT_STA_6:
	हाल RT5659_SPK_DC_CAILB_CTRL_1:
	हाल RT5659_SPK_DC_CAILB_STA_1:
	हाल RT5659_SPK_DC_CAILB_STA_2:
	हाल RT5659_SPK_DC_CAILB_STA_3:
	हाल RT5659_SPK_DC_CAILB_STA_4:
	हाल RT5659_SPK_DC_CAILB_STA_5:
	हाल RT5659_SPK_DC_CAILB_STA_6:
	हाल RT5659_SPK_DC_CAILB_STA_7:
	हाल RT5659_SPK_DC_CAILB_STA_8:
	हाल RT5659_SPK_DC_CAILB_STA_9:
	हाल RT5659_SPK_DC_CAILB_STA_10:
	हाल RT5659_SPK_VDD_STA_1:
	हाल RT5659_SPK_VDD_STA_2:
	हाल RT5659_SPK_DC_DET_CTRL_1:
	हाल RT5659_PURE_DC_DET_CTRL_1:
	हाल RT5659_PURE_DC_DET_CTRL_2:
	हाल RT5659_DRC1_PRIV_1:
	हाल RT5659_DRC1_PRIV_4:
	हाल RT5659_DRC1_PRIV_5:
	हाल RT5659_DRC1_PRIV_6:
	हाल RT5659_DRC1_PRIV_7:
	हाल RT5659_DRC2_PRIV_1:
	हाल RT5659_DRC2_PRIV_4:
	हाल RT5659_DRC2_PRIV_5:
	हाल RT5659_DRC2_PRIV_6:
	हाल RT5659_DRC2_PRIV_7:
	हाल RT5659_ALC_PGA_STA_1:
	हाल RT5659_ALC_PGA_STA_2:
	हाल RT5659_ALC_PGA_STA_3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5659_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5659_RESET:
	हाल RT5659_SPO_VOL:
	हाल RT5659_HP_VOL:
	हाल RT5659_LOUT:
	हाल RT5659_MONO_OUT:
	हाल RT5659_HPL_GAIN:
	हाल RT5659_HPR_GAIN:
	हाल RT5659_MONO_GAIN:
	हाल RT5659_SPDIF_CTRL_1:
	हाल RT5659_SPDIF_CTRL_2:
	हाल RT5659_CAL_BST_CTRL:
	हाल RT5659_IN1_IN2:
	हाल RT5659_IN3_IN4:
	हाल RT5659_INL1_INR1_VOL:
	हाल RT5659_EJD_CTRL_1:
	हाल RT5659_EJD_CTRL_2:
	हाल RT5659_EJD_CTRL_3:
	हाल RT5659_SILENCE_CTRL:
	हाल RT5659_PSV_CTRL:
	हाल RT5659_SIDETONE_CTRL:
	हाल RT5659_DAC1_DIG_VOL:
	हाल RT5659_DAC2_DIG_VOL:
	हाल RT5659_DAC_CTRL:
	हाल RT5659_STO1_ADC_DIG_VOL:
	हाल RT5659_MONO_ADC_DIG_VOL:
	हाल RT5659_STO2_ADC_DIG_VOL:
	हाल RT5659_STO1_BOOST:
	हाल RT5659_MONO_BOOST:
	हाल RT5659_STO2_BOOST:
	हाल RT5659_HP_IMP_GAIN_1:
	हाल RT5659_HP_IMP_GAIN_2:
	हाल RT5659_STO1_ADC_MIXER:
	हाल RT5659_MONO_ADC_MIXER:
	हाल RT5659_AD_DA_MIXER:
	हाल RT5659_STO_DAC_MIXER:
	हाल RT5659_MONO_DAC_MIXER:
	हाल RT5659_DIG_MIXER:
	हाल RT5659_A_DAC_MUX:
	हाल RT5659_DIG_INF23_DATA:
	हाल RT5659_PDM_OUT_CTRL:
	हाल RT5659_PDM_DATA_CTRL_1:
	हाल RT5659_PDM_DATA_CTRL_2:
	हाल RT5659_PDM_DATA_CTRL_3:
	हाल RT5659_PDM_DATA_CTRL_4:
	हाल RT5659_SPDIF_CTRL:
	हाल RT5659_REC1_GAIN:
	हाल RT5659_REC1_L1_MIXER:
	हाल RT5659_REC1_L2_MIXER:
	हाल RT5659_REC1_R1_MIXER:
	हाल RT5659_REC1_R2_MIXER:
	हाल RT5659_CAL_REC:
	हाल RT5659_REC2_L1_MIXER:
	हाल RT5659_REC2_L2_MIXER:
	हाल RT5659_REC2_R1_MIXER:
	हाल RT5659_REC2_R2_MIXER:
	हाल RT5659_SPK_L_MIXER:
	हाल RT5659_SPK_R_MIXER:
	हाल RT5659_SPO_AMP_GAIN:
	हाल RT5659_ALC_BACK_GAIN:
	हाल RT5659_MONOMIX_GAIN:
	हाल RT5659_MONOMIX_IN_GAIN:
	हाल RT5659_OUT_L_GAIN:
	हाल RT5659_OUT_L_MIXER:
	हाल RT5659_OUT_R_GAIN:
	हाल RT5659_OUT_R_MIXER:
	हाल RT5659_LOUT_MIXER:
	हाल RT5659_HAPTIC_GEN_CTRL_1:
	हाल RT5659_HAPTIC_GEN_CTRL_2:
	हाल RT5659_HAPTIC_GEN_CTRL_3:
	हाल RT5659_HAPTIC_GEN_CTRL_4:
	हाल RT5659_HAPTIC_GEN_CTRL_5:
	हाल RT5659_HAPTIC_GEN_CTRL_6:
	हाल RT5659_HAPTIC_GEN_CTRL_7:
	हाल RT5659_HAPTIC_GEN_CTRL_8:
	हाल RT5659_HAPTIC_GEN_CTRL_9:
	हाल RT5659_HAPTIC_GEN_CTRL_10:
	हाल RT5659_HAPTIC_GEN_CTRL_11:
	हाल RT5659_HAPTIC_LPF_CTRL_1:
	हाल RT5659_HAPTIC_LPF_CTRL_2:
	हाल RT5659_HAPTIC_LPF_CTRL_3:
	हाल RT5659_PWR_DIG_1:
	हाल RT5659_PWR_DIG_2:
	हाल RT5659_PWR_ANLG_1:
	हाल RT5659_PWR_ANLG_2:
	हाल RT5659_PWR_ANLG_3:
	हाल RT5659_PWR_MIXER:
	हाल RT5659_PWR_VOL:
	हाल RT5659_PRIV_INDEX:
	हाल RT5659_CLK_DET:
	हाल RT5659_PRIV_DATA:
	हाल RT5659_PRE_DIV_1:
	हाल RT5659_PRE_DIV_2:
	हाल RT5659_I2S1_SDP:
	हाल RT5659_I2S2_SDP:
	हाल RT5659_I2S3_SDP:
	हाल RT5659_ADDA_CLK_1:
	हाल RT5659_ADDA_CLK_2:
	हाल RT5659_DMIC_CTRL_1:
	हाल RT5659_DMIC_CTRL_2:
	हाल RT5659_TDM_CTRL_1:
	हाल RT5659_TDM_CTRL_2:
	हाल RT5659_TDM_CTRL_3:
	हाल RT5659_TDM_CTRL_4:
	हाल RT5659_TDM_CTRL_5:
	हाल RT5659_GLB_CLK:
	हाल RT5659_PLL_CTRL_1:
	हाल RT5659_PLL_CTRL_2:
	हाल RT5659_ASRC_1:
	हाल RT5659_ASRC_2:
	हाल RT5659_ASRC_3:
	हाल RT5659_ASRC_4:
	हाल RT5659_ASRC_5:
	हाल RT5659_ASRC_6:
	हाल RT5659_ASRC_7:
	हाल RT5659_ASRC_8:
	हाल RT5659_ASRC_9:
	हाल RT5659_ASRC_10:
	हाल RT5659_DEPOP_1:
	हाल RT5659_DEPOP_2:
	हाल RT5659_DEPOP_3:
	हाल RT5659_HP_CHARGE_PUMP_1:
	हाल RT5659_HP_CHARGE_PUMP_2:
	हाल RT5659_MICBIAS_1:
	हाल RT5659_MICBIAS_2:
	हाल RT5659_ASRC_11:
	हाल RT5659_ASRC_12:
	हाल RT5659_ASRC_13:
	हाल RT5659_REC_M1_M2_GAIN_CTRL:
	हाल RT5659_RC_CLK_CTRL:
	हाल RT5659_CLASSD_CTRL_1:
	हाल RT5659_CLASSD_CTRL_2:
	हाल RT5659_ADC_EQ_CTRL_1:
	हाल RT5659_ADC_EQ_CTRL_2:
	हाल RT5659_DAC_EQ_CTRL_1:
	हाल RT5659_DAC_EQ_CTRL_2:
	हाल RT5659_DAC_EQ_CTRL_3:
	हाल RT5659_IRQ_CTRL_1:
	हाल RT5659_IRQ_CTRL_2:
	हाल RT5659_IRQ_CTRL_3:
	हाल RT5659_IRQ_CTRL_4:
	हाल RT5659_IRQ_CTRL_5:
	हाल RT5659_IRQ_CTRL_6:
	हाल RT5659_INT_ST_1:
	हाल RT5659_INT_ST_2:
	हाल RT5659_GPIO_CTRL_1:
	हाल RT5659_GPIO_CTRL_2:
	हाल RT5659_GPIO_CTRL_3:
	हाल RT5659_GPIO_CTRL_4:
	हाल RT5659_GPIO_CTRL_5:
	हाल RT5659_GPIO_STA:
	हाल RT5659_SINE_GEN_CTRL_1:
	हाल RT5659_SINE_GEN_CTRL_2:
	हाल RT5659_SINE_GEN_CTRL_3:
	हाल RT5659_HP_AMP_DET_CTRL_1:
	हाल RT5659_HP_AMP_DET_CTRL_2:
	हाल RT5659_SV_ZCD_1:
	हाल RT5659_SV_ZCD_2:
	हाल RT5659_IL_CMD_1:
	हाल RT5659_IL_CMD_2:
	हाल RT5659_IL_CMD_3:
	हाल RT5659_IL_CMD_4:
	हाल RT5659_4BTN_IL_CMD_1:
	हाल RT5659_4BTN_IL_CMD_2:
	हाल RT5659_4BTN_IL_CMD_3:
	हाल RT5659_PSV_IL_CMD_1:
	हाल RT5659_PSV_IL_CMD_2:
	हाल RT5659_ADC_STO1_HP_CTRL_1:
	हाल RT5659_ADC_STO1_HP_CTRL_2:
	हाल RT5659_ADC_MONO_HP_CTRL_1:
	हाल RT5659_ADC_MONO_HP_CTRL_2:
	हाल RT5659_AJD1_CTRL:
	हाल RT5659_AJD2_AJD3_CTRL:
	हाल RT5659_JD1_THD:
	हाल RT5659_JD2_THD:
	हाल RT5659_JD3_THD:
	हाल RT5659_JD_CTRL_1:
	हाल RT5659_JD_CTRL_2:
	हाल RT5659_JD_CTRL_3:
	हाल RT5659_JD_CTRL_4:
	हाल RT5659_DIG_MISC:
	हाल RT5659_DUMMY_2:
	हाल RT5659_DUMMY_3:
	हाल RT5659_VENDOR_ID:
	हाल RT5659_VENDOR_ID_1:
	हाल RT5659_DEVICE_ID:
	हाल RT5659_DAC_ADC_DIG_VOL:
	हाल RT5659_BIAS_CUR_CTRL_1:
	हाल RT5659_BIAS_CUR_CTRL_2:
	हाल RT5659_BIAS_CUR_CTRL_3:
	हाल RT5659_BIAS_CUR_CTRL_4:
	हाल RT5659_BIAS_CUR_CTRL_5:
	हाल RT5659_BIAS_CUR_CTRL_6:
	हाल RT5659_BIAS_CUR_CTRL_7:
	हाल RT5659_BIAS_CUR_CTRL_8:
	हाल RT5659_BIAS_CUR_CTRL_9:
	हाल RT5659_BIAS_CUR_CTRL_10:
	हाल RT5659_MEMORY_TEST:
	हाल RT5659_VREF_REC_OP_FB_CAP_CTRL:
	हाल RT5659_CLASSD_0:
	हाल RT5659_CLASSD_1:
	हाल RT5659_CLASSD_2:
	हाल RT5659_CLASSD_3:
	हाल RT5659_CLASSD_4:
	हाल RT5659_CLASSD_5:
	हाल RT5659_CLASSD_6:
	हाल RT5659_CLASSD_7:
	हाल RT5659_CLASSD_8:
	हाल RT5659_CLASSD_9:
	हाल RT5659_CLASSD_10:
	हाल RT5659_CHARGE_PUMP_1:
	हाल RT5659_CHARGE_PUMP_2:
	हाल RT5659_DIG_IN_CTRL_1:
	हाल RT5659_DIG_IN_CTRL_2:
	हाल RT5659_PAD_DRIVING_CTRL:
	हाल RT5659_SOFT_RAMP_DEPOP:
	हाल RT5659_PLL:
	हाल RT5659_CHOP_DAC:
	हाल RT5659_CHOP_ADC:
	हाल RT5659_CALIB_ADC_CTRL:
	हाल RT5659_SOFT_RAMP_DEPOP_DAC_CLK_CTRL:
	हाल RT5659_VOL_TEST:
	हाल RT5659_TEST_MODE_CTRL_1:
	हाल RT5659_TEST_MODE_CTRL_2:
	हाल RT5659_TEST_MODE_CTRL_3:
	हाल RT5659_TEST_MODE_CTRL_4:
	हाल RT5659_BASSBACK_CTRL:
	हाल RT5659_MP3_PLUS_CTRL_1:
	हाल RT5659_MP3_PLUS_CTRL_2:
	हाल RT5659_MP3_HPF_A1:
	हाल RT5659_MP3_HPF_A2:
	हाल RT5659_MP3_HPF_H0:
	हाल RT5659_MP3_LPF_H0:
	हाल RT5659_3D_SPK_CTRL:
	हाल RT5659_3D_SPK_COEF_1:
	हाल RT5659_3D_SPK_COEF_2:
	हाल RT5659_3D_SPK_COEF_3:
	हाल RT5659_3D_SPK_COEF_4:
	हाल RT5659_3D_SPK_COEF_5:
	हाल RT5659_3D_SPK_COEF_6:
	हाल RT5659_3D_SPK_COEF_7:
	हाल RT5659_STO_NG2_CTRL_1:
	हाल RT5659_STO_NG2_CTRL_2:
	हाल RT5659_STO_NG2_CTRL_3:
	हाल RT5659_STO_NG2_CTRL_4:
	हाल RT5659_STO_NG2_CTRL_5:
	हाल RT5659_STO_NG2_CTRL_6:
	हाल RT5659_STO_NG2_CTRL_7:
	हाल RT5659_STO_NG2_CTRL_8:
	हाल RT5659_MONO_NG2_CTRL_1:
	हाल RT5659_MONO_NG2_CTRL_2:
	हाल RT5659_MONO_NG2_CTRL_3:
	हाल RT5659_MONO_NG2_CTRL_4:
	हाल RT5659_MONO_NG2_CTRL_5:
	हाल RT5659_MONO_NG2_CTRL_6:
	हाल RT5659_MID_HP_AMP_DET:
	हाल RT5659_LOW_HP_AMP_DET:
	हाल RT5659_LDO_CTRL:
	हाल RT5659_HP_DECROSS_CTRL_1:
	हाल RT5659_HP_DECROSS_CTRL_2:
	हाल RT5659_HP_DECROSS_CTRL_3:
	हाल RT5659_HP_DECROSS_CTRL_4:
	हाल RT5659_HP_IMP_SENS_CTRL_1:
	हाल RT5659_HP_IMP_SENS_CTRL_2:
	हाल RT5659_HP_IMP_SENS_CTRL_3:
	हाल RT5659_HP_IMP_SENS_CTRL_4:
	हाल RT5659_HP_IMP_SENS_MAP_1:
	हाल RT5659_HP_IMP_SENS_MAP_2:
	हाल RT5659_HP_IMP_SENS_MAP_3:
	हाल RT5659_HP_IMP_SENS_MAP_4:
	हाल RT5659_HP_IMP_SENS_MAP_5:
	हाल RT5659_HP_IMP_SENS_MAP_6:
	हाल RT5659_HP_IMP_SENS_MAP_7:
	हाल RT5659_HP_IMP_SENS_MAP_8:
	हाल RT5659_HP_LOGIC_CTRL_1:
	हाल RT5659_HP_LOGIC_CTRL_2:
	हाल RT5659_HP_CALIB_CTRL_1:
	हाल RT5659_HP_CALIB_CTRL_2:
	हाल RT5659_HP_CALIB_CTRL_3:
	हाल RT5659_HP_CALIB_CTRL_4:
	हाल RT5659_HP_CALIB_CTRL_5:
	हाल RT5659_HP_CALIB_CTRL_6:
	हाल RT5659_HP_CALIB_CTRL_7:
	हाल RT5659_HP_CALIB_CTRL_9:
	हाल RT5659_HP_CALIB_CTRL_10:
	हाल RT5659_HP_CALIB_CTRL_11:
	हाल RT5659_HP_CALIB_STA_1:
	हाल RT5659_HP_CALIB_STA_2:
	हाल RT5659_HP_CALIB_STA_3:
	हाल RT5659_HP_CALIB_STA_4:
	हाल RT5659_HP_CALIB_STA_5:
	हाल RT5659_HP_CALIB_STA_6:
	हाल RT5659_HP_CALIB_STA_7:
	हाल RT5659_HP_CALIB_STA_8:
	हाल RT5659_HP_CALIB_STA_9:
	हाल RT5659_MONO_AMP_CALIB_CTRL_1:
	हाल RT5659_MONO_AMP_CALIB_CTRL_2:
	हाल RT5659_MONO_AMP_CALIB_CTRL_3:
	हाल RT5659_MONO_AMP_CALIB_CTRL_4:
	हाल RT5659_MONO_AMP_CALIB_CTRL_5:
	हाल RT5659_MONO_AMP_CALIB_STA_1:
	हाल RT5659_MONO_AMP_CALIB_STA_2:
	हाल RT5659_MONO_AMP_CALIB_STA_3:
	हाल RT5659_MONO_AMP_CALIB_STA_4:
	हाल RT5659_SPK_PWR_LMT_CTRL_1:
	हाल RT5659_SPK_PWR_LMT_CTRL_2:
	हाल RT5659_SPK_PWR_LMT_CTRL_3:
	हाल RT5659_SPK_PWR_LMT_STA_1:
	हाल RT5659_SPK_PWR_LMT_STA_2:
	हाल RT5659_SPK_PWR_LMT_STA_3:
	हाल RT5659_SPK_PWR_LMT_STA_4:
	हाल RT5659_SPK_PWR_LMT_STA_5:
	हाल RT5659_SPK_PWR_LMT_STA_6:
	हाल RT5659_FLEX_SPK_BST_CTRL_1:
	हाल RT5659_FLEX_SPK_BST_CTRL_2:
	हाल RT5659_FLEX_SPK_BST_CTRL_3:
	हाल RT5659_FLEX_SPK_BST_CTRL_4:
	हाल RT5659_SPK_EX_LMT_CTRL_1:
	हाल RT5659_SPK_EX_LMT_CTRL_2:
	हाल RT5659_SPK_EX_LMT_CTRL_3:
	हाल RT5659_SPK_EX_LMT_CTRL_4:
	हाल RT5659_SPK_EX_LMT_CTRL_5:
	हाल RT5659_SPK_EX_LMT_CTRL_6:
	हाल RT5659_SPK_EX_LMT_CTRL_7:
	हाल RT5659_ADJ_HPF_CTRL_1:
	हाल RT5659_ADJ_HPF_CTRL_2:
	हाल RT5659_SPK_DC_CAILB_CTRL_1:
	हाल RT5659_SPK_DC_CAILB_CTRL_2:
	हाल RT5659_SPK_DC_CAILB_CTRL_3:
	हाल RT5659_SPK_DC_CAILB_CTRL_4:
	हाल RT5659_SPK_DC_CAILB_CTRL_5:
	हाल RT5659_SPK_DC_CAILB_STA_1:
	हाल RT5659_SPK_DC_CAILB_STA_2:
	हाल RT5659_SPK_DC_CAILB_STA_3:
	हाल RT5659_SPK_DC_CAILB_STA_4:
	हाल RT5659_SPK_DC_CAILB_STA_5:
	हाल RT5659_SPK_DC_CAILB_STA_6:
	हाल RT5659_SPK_DC_CAILB_STA_7:
	हाल RT5659_SPK_DC_CAILB_STA_8:
	हाल RT5659_SPK_DC_CAILB_STA_9:
	हाल RT5659_SPK_DC_CAILB_STA_10:
	हाल RT5659_SPK_VDD_STA_1:
	हाल RT5659_SPK_VDD_STA_2:
	हाल RT5659_SPK_DC_DET_CTRL_1:
	हाल RT5659_SPK_DC_DET_CTRL_2:
	हाल RT5659_SPK_DC_DET_CTRL_3:
	हाल RT5659_PURE_DC_DET_CTRL_1:
	हाल RT5659_PURE_DC_DET_CTRL_2:
	हाल RT5659_DUMMY_4:
	हाल RT5659_DUMMY_5:
	हाल RT5659_DUMMY_6:
	हाल RT5659_DRC1_CTRL_1:
	हाल RT5659_DRC1_CTRL_2:
	हाल RT5659_DRC1_CTRL_3:
	हाल RT5659_DRC1_CTRL_4:
	हाल RT5659_DRC1_CTRL_5:
	हाल RT5659_DRC1_CTRL_6:
	हाल RT5659_DRC1_HARD_LMT_CTRL_1:
	हाल RT5659_DRC1_HARD_LMT_CTRL_2:
	हाल RT5659_DRC2_CTRL_1:
	हाल RT5659_DRC2_CTRL_2:
	हाल RT5659_DRC2_CTRL_3:
	हाल RT5659_DRC2_CTRL_4:
	हाल RT5659_DRC2_CTRL_5:
	हाल RT5659_DRC2_CTRL_6:
	हाल RT5659_DRC2_HARD_LMT_CTRL_1:
	हाल RT5659_DRC2_HARD_LMT_CTRL_2:
	हाल RT5659_DRC1_PRIV_1:
	हाल RT5659_DRC1_PRIV_2:
	हाल RT5659_DRC1_PRIV_3:
	हाल RT5659_DRC1_PRIV_4:
	हाल RT5659_DRC1_PRIV_5:
	हाल RT5659_DRC1_PRIV_6:
	हाल RT5659_DRC1_PRIV_7:
	हाल RT5659_DRC2_PRIV_1:
	हाल RT5659_DRC2_PRIV_2:
	हाल RT5659_DRC2_PRIV_3:
	हाल RT5659_DRC2_PRIV_4:
	हाल RT5659_DRC2_PRIV_5:
	हाल RT5659_DRC2_PRIV_6:
	हाल RT5659_DRC2_PRIV_7:
	हाल RT5659_MULTI_DRC_CTRL:
	हाल RT5659_CROSS_OVER_1:
	हाल RT5659_CROSS_OVER_2:
	हाल RT5659_CROSS_OVER_3:
	हाल RT5659_CROSS_OVER_4:
	हाल RT5659_CROSS_OVER_5:
	हाल RT5659_CROSS_OVER_6:
	हाल RT5659_CROSS_OVER_7:
	हाल RT5659_CROSS_OVER_8:
	हाल RT5659_CROSS_OVER_9:
	हाल RT5659_CROSS_OVER_10:
	हाल RT5659_ALC_PGA_CTRL_1:
	हाल RT5659_ALC_PGA_CTRL_2:
	हाल RT5659_ALC_PGA_CTRL_3:
	हाल RT5659_ALC_PGA_CTRL_4:
	हाल RT5659_ALC_PGA_CTRL_5:
	हाल RT5659_ALC_PGA_CTRL_6:
	हाल RT5659_ALC_PGA_CTRL_7:
	हाल RT5659_ALC_PGA_CTRL_8:
	हाल RT5659_ALC_PGA_STA_1:
	हाल RT5659_ALC_PGA_STA_2:
	हाल RT5659_ALC_PGA_STA_3:
	हाल RT5659_DAC_L_EQ_PRE_VOL:
	हाल RT5659_DAC_R_EQ_PRE_VOL:
	हाल RT5659_DAC_L_EQ_POST_VOL:
	हाल RT5659_DAC_R_EQ_POST_VOL:
	हाल RT5659_DAC_L_EQ_LPF1_A1:
	हाल RT5659_DAC_L_EQ_LPF1_H0:
	हाल RT5659_DAC_R_EQ_LPF1_A1:
	हाल RT5659_DAC_R_EQ_LPF1_H0:
	हाल RT5659_DAC_L_EQ_BPF2_A1:
	हाल RT5659_DAC_L_EQ_BPF2_A2:
	हाल RT5659_DAC_L_EQ_BPF2_H0:
	हाल RT5659_DAC_R_EQ_BPF2_A1:
	हाल RT5659_DAC_R_EQ_BPF2_A2:
	हाल RT5659_DAC_R_EQ_BPF2_H0:
	हाल RT5659_DAC_L_EQ_BPF3_A1:
	हाल RT5659_DAC_L_EQ_BPF3_A2:
	हाल RT5659_DAC_L_EQ_BPF3_H0:
	हाल RT5659_DAC_R_EQ_BPF3_A1:
	हाल RT5659_DAC_R_EQ_BPF3_A2:
	हाल RT5659_DAC_R_EQ_BPF3_H0:
	हाल RT5659_DAC_L_EQ_BPF4_A1:
	हाल RT5659_DAC_L_EQ_BPF4_A2:
	हाल RT5659_DAC_L_EQ_BPF4_H0:
	हाल RT5659_DAC_R_EQ_BPF4_A1:
	हाल RT5659_DAC_R_EQ_BPF4_A2:
	हाल RT5659_DAC_R_EQ_BPF4_H0:
	हाल RT5659_DAC_L_EQ_HPF1_A1:
	हाल RT5659_DAC_L_EQ_HPF1_H0:
	हाल RT5659_DAC_R_EQ_HPF1_A1:
	हाल RT5659_DAC_R_EQ_HPF1_H0:
	हाल RT5659_DAC_L_EQ_HPF2_A1:
	हाल RT5659_DAC_L_EQ_HPF2_A2:
	हाल RT5659_DAC_L_EQ_HPF2_H0:
	हाल RT5659_DAC_R_EQ_HPF2_A1:
	हाल RT5659_DAC_R_EQ_HPF2_A2:
	हाल RT5659_DAC_R_EQ_HPF2_H0:
	हाल RT5659_DAC_L_BI_EQ_BPF1_H0_1:
	हाल RT5659_DAC_L_BI_EQ_BPF1_H0_2:
	हाल RT5659_DAC_L_BI_EQ_BPF1_B1_1:
	हाल RT5659_DAC_L_BI_EQ_BPF1_B1_2:
	हाल RT5659_DAC_L_BI_EQ_BPF1_B2_1:
	हाल RT5659_DAC_L_BI_EQ_BPF1_B2_2:
	हाल RT5659_DAC_L_BI_EQ_BPF1_A1_1:
	हाल RT5659_DAC_L_BI_EQ_BPF1_A1_2:
	हाल RT5659_DAC_L_BI_EQ_BPF1_A2_1:
	हाल RT5659_DAC_L_BI_EQ_BPF1_A2_2:
	हाल RT5659_DAC_R_BI_EQ_BPF1_H0_1:
	हाल RT5659_DAC_R_BI_EQ_BPF1_H0_2:
	हाल RT5659_DAC_R_BI_EQ_BPF1_B1_1:
	हाल RT5659_DAC_R_BI_EQ_BPF1_B1_2:
	हाल RT5659_DAC_R_BI_EQ_BPF1_B2_1:
	हाल RT5659_DAC_R_BI_EQ_BPF1_B2_2:
	हाल RT5659_DAC_R_BI_EQ_BPF1_A1_1:
	हाल RT5659_DAC_R_BI_EQ_BPF1_A1_2:
	हाल RT5659_DAC_R_BI_EQ_BPF1_A2_1:
	हाल RT5659_DAC_R_BI_EQ_BPF1_A2_2:
	हाल RT5659_ADC_L_EQ_LPF1_A1:
	हाल RT5659_ADC_R_EQ_LPF1_A1:
	हाल RT5659_ADC_L_EQ_LPF1_H0:
	हाल RT5659_ADC_R_EQ_LPF1_H0:
	हाल RT5659_ADC_L_EQ_BPF1_A1:
	हाल RT5659_ADC_R_EQ_BPF1_A1:
	हाल RT5659_ADC_L_EQ_BPF1_A2:
	हाल RT5659_ADC_R_EQ_BPF1_A2:
	हाल RT5659_ADC_L_EQ_BPF1_H0:
	हाल RT5659_ADC_R_EQ_BPF1_H0:
	हाल RT5659_ADC_L_EQ_BPF2_A1:
	हाल RT5659_ADC_R_EQ_BPF2_A1:
	हाल RT5659_ADC_L_EQ_BPF2_A2:
	हाल RT5659_ADC_R_EQ_BPF2_A2:
	हाल RT5659_ADC_L_EQ_BPF2_H0:
	हाल RT5659_ADC_R_EQ_BPF2_H0:
	हाल RT5659_ADC_L_EQ_BPF3_A1:
	हाल RT5659_ADC_R_EQ_BPF3_A1:
	हाल RT5659_ADC_L_EQ_BPF3_A2:
	हाल RT5659_ADC_R_EQ_BPF3_A2:
	हाल RT5659_ADC_L_EQ_BPF3_H0:
	हाल RT5659_ADC_R_EQ_BPF3_H0:
	हाल RT5659_ADC_L_EQ_BPF4_A1:
	हाल RT5659_ADC_R_EQ_BPF4_A1:
	हाल RT5659_ADC_L_EQ_BPF4_A2:
	हाल RT5659_ADC_R_EQ_BPF4_A2:
	हाल RT5659_ADC_L_EQ_BPF4_H0:
	हाल RT5659_ADC_R_EQ_BPF4_H0:
	हाल RT5659_ADC_L_EQ_HPF1_A1:
	हाल RT5659_ADC_R_EQ_HPF1_A1:
	हाल RT5659_ADC_L_EQ_HPF1_H0:
	हाल RT5659_ADC_R_EQ_HPF1_H0:
	हाल RT5659_ADC_L_EQ_PRE_VOL:
	हाल RT5659_ADC_R_EQ_PRE_VOL:
	हाल RT5659_ADC_L_EQ_POST_VOL:
	हाल RT5659_ADC_R_EQ_POST_VOL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(hp_vol_tlv, -2325, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -65625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -17625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_bst_tlv, -1200, 75, 0);

/* Interface data select */
अटल स्थिर अक्षर * स्थिर rt5659_data_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर1_01_adc_क्रमागत,
	RT5659_TDM_CTRL_2, RT5659_DS_ADC_SLOT01_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर1_23_adc_क्रमागत,
	RT5659_TDM_CTRL_2, RT5659_DS_ADC_SLOT23_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर1_45_adc_क्रमागत,
	RT5659_TDM_CTRL_2, RT5659_DS_ADC_SLOT45_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर1_67_adc_क्रमागत,
	RT5659_TDM_CTRL_2, RT5659_DS_ADC_SLOT67_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर2_dac_क्रमागत,
	RT5659_DIG_INF23_DATA, RT5659_IF2_DAC_SEL_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर2_adc_क्रमागत,
	RT5659_DIG_INF23_DATA, RT5659_IF2_ADC_SEL_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर3_dac_क्रमागत,
	RT5659_DIG_INF23_DATA, RT5659_IF3_DAC_SEL_SFT, rt5659_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5659_अगर3_adc_क्रमागत,
	RT5659_DIG_INF23_DATA, RT5659_IF3_ADC_SEL_SFT, rt5659_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर1_01_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 01 ADC Swap Source", rt5659_अगर1_01_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर1_23_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 23 ADC1 Swap Source", rt5659_अगर1_23_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर1_45_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 45 ADC1 Swap Source", rt5659_अगर1_45_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर1_67_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 67 ADC1 Swap Source", rt5659_अगर1_67_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर2_dac_swap_mux =
	SOC_DAPM_ENUM("IF2 DAC Swap Source", rt5659_अगर2_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर2_adc_swap_mux =
	SOC_DAPM_ENUM("IF2 ADC Swap Source", rt5659_अगर2_adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर3_dac_swap_mux =
	SOC_DAPM_ENUM("IF3 DAC Swap Source", rt5659_अगर3_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर3_adc_swap_mux =
	SOC_DAPM_ENUM("IF3 ADC Swap Source", rt5659_अगर3_adc_क्रमागत);

अटल पूर्णांक rt5659_hp_vol_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक ret = snd_soc_put_volsw(kcontrol, ucontrol);

	अगर (snd_soc_component_पढ़ो(component, RT5659_STO_NG2_CTRL_1) & RT5659_NG2_EN) अणु
		snd_soc_component_update_bits(component, RT5659_STO_NG2_CTRL_1,
			RT5659_NG2_EN_MASK, RT5659_NG2_DIS);
		snd_soc_component_update_bits(component, RT5659_STO_NG2_CTRL_1,
			RT5659_NG2_EN_MASK, RT5659_NG2_EN);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rt5659_enable_push_button_irq(काष्ठा snd_soc_component *component,
	bool enable)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (enable) अणु
		snd_soc_component_ग_लिखो(component, RT5659_4BTN_IL_CMD_1, 0x000b);

		/* MICBIAS1 and Mic Det Power क्रम button detect*/
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_क्रमce_enable_pin(dapm,
			"Mic Det Power");
		snd_soc_dapm_sync(dapm);

		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_2,
			RT5659_PWR_MB1, RT5659_PWR_MB1);
		snd_soc_component_update_bits(component, RT5659_PWR_VOL,
			RT5659_PWR_MIC_DET, RT5659_PWR_MIC_DET);

		snd_soc_component_update_bits(component, RT5659_IRQ_CTRL_2,
				RT5659_IL_IRQ_MASK, RT5659_IL_IRQ_EN);
		snd_soc_component_update_bits(component, RT5659_4BTN_IL_CMD_2,
				RT5659_4BTN_IL_MASK, RT5659_4BTN_IL_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5659_4BTN_IL_CMD_2,
				RT5659_4BTN_IL_MASK, RT5659_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5659_IRQ_CTRL_2,
				RT5659_IL_IRQ_MASK, RT5659_IL_IRQ_DIS);
		/* MICBIAS1 and Mic Det Power क्रम button detect*/
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
	पूर्ण
पूर्ण

/**
 * rt5659_headset_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insert: Jack insert or not.
 *
 * Detect whether is headset or not when jack inserted.
 *
 * Returns detect status.
 */

अटल पूर्णांक rt5659_headset_detect(काष्ठा snd_soc_component *component, पूर्णांक jack_insert)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक val, i = 0, sleep_समय[5] = अणु300, 150, 100, 50, 30पूर्ण;
	पूर्णांक reg_63;

	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	अगर (jack_insert) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm,
			"Mic Det Power");
		snd_soc_dapm_sync(dapm);
		reg_63 = snd_soc_component_पढ़ो(component, RT5659_PWR_ANLG_1);

		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_1,
			RT5659_PWR_VREF2 | RT5659_PWR_MB,
			RT5659_PWR_VREF2 | RT5659_PWR_MB);
		msleep(20);
		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_1,
			RT5659_PWR_FV2, RT5659_PWR_FV2);

		snd_soc_component_ग_लिखो(component, RT5659_EJD_CTRL_2, 0x4160);
		snd_soc_component_update_bits(component, RT5659_EJD_CTRL_1,
			0x20, 0x0);
		msleep(20);
		snd_soc_component_update_bits(component, RT5659_EJD_CTRL_1,
			0x20, 0x20);

		जबतक (i < 5) अणु
			msleep(sleep_समय[i]);
			val = snd_soc_component_पढ़ो(component, RT5659_EJD_CTRL_2) & 0x0003;
			i++;
			अगर (val == 0x1 || val == 0x2 || val == 0x3)
				अवरोध;
		पूर्ण

		चयन (val) अणु
		हाल 1:
			rt5659->jack_type = SND_JACK_HEADSET;
			rt5659_enable_push_button_irq(component, true);
			अवरोध;
		शेष:
			snd_soc_component_ग_लिखो(component, RT5659_PWR_ANLG_1, reg_63);
			rt5659->jack_type = SND_JACK_HEADPHONE;
			snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
			snd_soc_dapm_sync(dapm);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		अगर (rt5659->jack_type == SND_JACK_HEADSET)
			rt5659_enable_push_button_irq(component, false);
		rt5659->jack_type = 0;
	पूर्ण

	dev_dbg(component->dev, "jack_type = %d\n", rt5659->jack_type);
	वापस rt5659->jack_type;
पूर्ण

अटल पूर्णांक rt5659_button_detect(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक btn_type, val;

	val = snd_soc_component_पढ़ो(component, RT5659_4BTN_IL_CMD_1);
	btn_type = val & 0xfff0;
	snd_soc_component_ग_लिखो(component, RT5659_4BTN_IL_CMD_1, val);

	वापस btn_type;
पूर्ण

अटल irqवापस_t rt5659_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5659_priv *rt5659 = data;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &rt5659->jack_detect_work, msecs_to_jअगरfies(250));

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक rt5659_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hs_jack)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	rt5659->hs_jack = hs_jack;

	rt5659_irq(0, rt5659);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5659_set_jack_detect);

अटल व्योम rt5659_jack_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5659_priv *rt5659 =
		container_of(work, काष्ठा rt5659_priv, jack_detect_work.work);
	पूर्णांक val, btn_type, report = 0;

	अगर (!rt5659->component)
		वापस;

	val = snd_soc_component_पढ़ो(rt5659->component, RT5659_INT_ST_1) & 0x0080;
	अगर (!val) अणु
		/* jack in */
		अगर (rt5659->jack_type == 0) अणु
			/* jack was out, report jack type */
			report = rt5659_headset_detect(rt5659->component, 1);
		पूर्ण अन्यथा अणु
			/* jack is alपढ़ोy in, report button event */
			report = SND_JACK_HEADSET;
			btn_type = rt5659_button_detect(rt5659->component);
			/**
			 * rt5659 can report three kinds of button behavior,
			 * one click, द्विगुन click and hold. However,
			 * currently we will report button pressed/released
			 * event. So all the three button behaviors are
			 * treated as button pressed.
			 */
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
				btn_type = 0;
				dev_err(rt5659->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				अवरोध;
			पूर्ण

			/* button release or spurious पूर्णांकerrput*/
			अगर (btn_type == 0)
				report =  rt5659->jack_type;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* jack out */
		report = rt5659_headset_detect(rt5659->component, 0);
	पूर्ण

	snd_soc_jack_report(rt5659->hs_jack, report, SND_JACK_HEADSET |
			    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			    SND_JACK_BTN_2 | SND_JACK_BTN_3);
पूर्ण

अटल व्योम rt5659_jack_detect_पूर्णांकel_hd_header(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5659_priv *rt5659 =
		container_of(work, काष्ठा rt5659_priv, jack_detect_work.work);
	अचिन्हित पूर्णांक value;
	bool hp_flag, mic_flag;

	अगर (!rt5659->hs_jack)
		वापस;

	/* headphone jack */
	regmap_पढ़ो(rt5659->regmap, RT5659_GPIO_STA, &value);
	hp_flag = (!(value & 0x8)) ? true : false;

	अगर (hp_flag != rt5659->hda_hp_plugged) अणु
		rt5659->hda_hp_plugged = hp_flag;

		अगर (hp_flag) अणु
			regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_1,
				0x10, 0x0);
			rt5659->jack_type |= SND_JACK_HEADPHONE;
		पूर्ण अन्यथा अणु
			regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_1,
				0x10, 0x10);
			rt5659->jack_type = rt5659->jack_type &
				(~SND_JACK_HEADPHONE);
		पूर्ण

		snd_soc_jack_report(rt5659->hs_jack, rt5659->jack_type,
			SND_JACK_HEADPHONE);
	पूर्ण

	/* mic jack */
	regmap_पढ़ो(rt5659->regmap, RT5659_4BTN_IL_CMD_1, &value);
	regmap_ग_लिखो(rt5659->regmap, RT5659_4BTN_IL_CMD_1, value);
	mic_flag = (value & 0x2000) ? true : false;

	अगर (mic_flag != rt5659->hda_mic_plugged) अणु
		rt5659->hda_mic_plugged = mic_flag;
		अगर (mic_flag) अणु
			regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_2,
				0x2, 0x2);
			rt5659->jack_type |= SND_JACK_MICROPHONE;
		पूर्ण अन्यथा अणु
			regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_2,
				0x2, 0x0);
			rt5659->jack_type = rt5659->jack_type
				& (~SND_JACK_MICROPHONE);
		पूर्ण

		snd_soc_jack_report(rt5659->hs_jack, rt5659->jack_type,
			SND_JACK_MICROPHONE);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_snd_controls[] = अणु
	/* Speaker Output Volume */
	SOC_DOUBLE_TLV("Speaker Playback Volume", RT5659_SPO_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* Headphone Output Volume */
	SOC_DOUBLE_R_EXT_TLV("Headphone Playback Volume", RT5659_HPL_GAIN,
		RT5659_HPR_GAIN, RT5659_G_HP_SFT, 31, 1, snd_soc_get_volsw,
		rt5659_hp_vol_put, hp_vol_tlv),

	/* Mono Output Volume */
	SOC_SINGLE_TLV("Mono Playback Volume", RT5659_MONO_OUT,
		RT5659_L_VOL_SFT, 39, 1, out_vol_tlv),

	/* Output Volume */
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5659_LOUT,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5659_DAC1_DIG_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 175, 0, dac_vol_tlv),
	SOC_DOUBLE("DAC1 Playback Switch", RT5659_AD_DA_MIXER,
		RT5659_M_DAC1_L_SFT, RT5659_M_DAC1_R_SFT, 1, 1),

	SOC_DOUBLE_TLV("DAC2 Playback Volume", RT5659_DAC2_DIG_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 175, 0, dac_vol_tlv),
	SOC_DOUBLE("DAC2 Playback Switch", RT5659_DAC_CTRL,
		RT5659_M_DAC2_L_VOL_SFT, RT5659_M_DAC2_R_VOL_SFT, 1, 1),

	/* IN1/IN2/IN3/IN4 Volume */
	SOC_SINGLE_TLV("IN1 Boost Volume", RT5659_IN1_IN2,
		RT5659_BST1_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost Volume", RT5659_IN1_IN2,
		RT5659_BST2_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN3 Boost Volume", RT5659_IN3_IN4,
		RT5659_BST3_SFT, 69, 0, in_bst_tlv),
	SOC_SINGLE_TLV("IN4 Boost Volume", RT5659_IN3_IN4,
		RT5659_BST4_SFT, 69, 0, in_bst_tlv),

	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5659_INL1_INR1_VOL,
		RT5659_INL_VOL_SFT, RT5659_INR_VOL_SFT, 31, 1, in_vol_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("STO1 ADC Capture Switch", RT5659_STO1_ADC_DIG_VOL,
		RT5659_L_MUTE_SFT, RT5659_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("STO1 ADC Capture Volume", RT5659_STO1_ADC_DIG_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 127, 0, adc_vol_tlv),
	SOC_DOUBLE("Mono ADC Capture Switch", RT5659_MONO_ADC_DIG_VOL,
		RT5659_L_MUTE_SFT, RT5659_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5659_MONO_ADC_DIG_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 127, 0, adc_vol_tlv),
	SOC_DOUBLE("STO2 ADC Capture Switch", RT5659_STO2_ADC_DIG_VOL,
		RT5659_L_MUTE_SFT, RT5659_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("STO2 ADC Capture Volume", RT5659_STO2_ADC_DIG_VOL,
		RT5659_L_VOL_SFT, RT5659_R_VOL_SFT, 127, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Gain Volume", RT5659_STO1_BOOST,
		RT5659_STO1_ADC_L_BST_SFT, RT5659_STO1_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	SOC_DOUBLE_TLV("Mono ADC Boost Gain Volume", RT5659_MONO_BOOST,
		RT5659_MONO_ADC_L_BST_SFT, RT5659_MONO_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	SOC_DOUBLE_TLV("STO2 ADC Boost Gain Volume", RT5659_STO2_BOOST,
		RT5659_STO2_ADC_L_BST_SFT, RT5659_STO2_ADC_R_BST_SFT,
		3, 0, adc_bst_tlv),

	SOC_SINGLE("DAC IF1 DAC1 L Data Switch", RT5659_TDM_CTRL_4, 12, 7, 0),
	SOC_SINGLE("DAC IF1 DAC1 R Data Switch", RT5659_TDM_CTRL_4, 8, 7, 0),
	SOC_SINGLE("DAC IF1 DAC2 L Data Switch", RT5659_TDM_CTRL_4, 4, 7, 0),
	SOC_SINGLE("DAC IF1 DAC2 R Data Switch", RT5659_TDM_CTRL_4, 0, 7, 0),
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
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	पूर्णांक pd, idx;

	pd = rl6231_get_pre_भाग(rt5659->regmap,
		RT5659_ADDA_CLK_1, RT5659_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rt5659->sysclk / pd);

	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा अणु
		snd_soc_component_update_bits(component, RT5659_DMIC_CTRL_1,
			RT5659_DMIC_CLK_MASK, idx << RT5659_DMIC_CLK_SFT);
	पूर्ण
	वापस idx;
पूर्ण

अटल पूर्णांक set_adc1_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5659_CHOP_ADC,
			RT5659_CKXEN_ADC1_MASK | RT5659_CKGEN_ADC1_MASK,
			RT5659_CKXEN_ADC1_MASK | RT5659_CKGEN_ADC1_MASK);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5659_CHOP_ADC,
			RT5659_CKXEN_ADC1_MASK | RT5659_CKGEN_ADC1_MASK, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक set_adc2_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5659_CHOP_ADC,
			RT5659_CKXEN_ADC2_MASK | RT5659_CKGEN_ADC2_MASK,
			RT5659_CKXEN_ADC2_MASK | RT5659_CKGEN_ADC2_MASK);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5659_CHOP_ADC,
			RT5659_CKXEN_ADC2_MASK | RT5659_CKGEN_ADC2_MASK, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rt5659_अक्षरge_pump_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Depop */
		snd_soc_component_ग_लिखो(component, RT5659_DEPOP_1, 0x0009);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, RT5659_HP_CHARGE_PUMP_1, 0x0c16);
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

	val = snd_soc_component_पढ़ो(component, RT5659_GLB_CLK);
	val &= RT5659_SCLK_SRC_MASK;
	अगर (val == RT5659_SCLK_SRC_PLL1)
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
	हाल RT5659_ADC_MONO_R_ASRC_SFT:
		reg = RT5659_ASRC_3;
		shअगरt = RT5659_AD_MONO_R_T_SFT;
		अवरोध;
	हाल RT5659_ADC_MONO_L_ASRC_SFT:
		reg = RT5659_ASRC_3;
		shअगरt = RT5659_AD_MONO_L_T_SFT;
		अवरोध;
	हाल RT5659_ADC_STO1_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shअगरt = RT5659_AD_STO1_T_SFT;
		अवरोध;
	हाल RT5659_DAC_MONO_R_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shअगरt = RT5659_DA_MONO_R_T_SFT;
		अवरोध;
	हाल RT5659_DAC_MONO_L_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shअगरt = RT5659_DA_MONO_L_T_SFT;
		अवरोध;
	हाल RT5659_DAC_STO_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shअगरt = RT5659_DA_STO_T_SFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	val = (snd_soc_component_पढ़ो(component, reg) >> shअगरt) & 0xf;
	चयन (val) अणु
	हाल 1:
	हाल 2:
	हाल 3:
		/* I2S_Pre_Div1 should be 1 in asrc mode */
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_I2S_PD1_MASK, RT5659_I2S_PD1_2);
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5659_STO1_ADC_MIXER,
			RT5659_M_STO1_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5659_STO1_ADC_MIXER,
			RT5659_M_STO1_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5659_STO1_ADC_MIXER,
			RT5659_M_STO1_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5659_STO1_ADC_MIXER,
			RT5659_M_STO1_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5659_MONO_ADC_MIXER,
			RT5659_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5659_MONO_ADC_MIXER,
			RT5659_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5659_MONO_ADC_MIXER,
			RT5659_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5659_MONO_ADC_MIXER,
			RT5659_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5659_AD_DA_MIXER,
			RT5659_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5659_AD_DA_MIXER,
			RT5659_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5659_AD_DA_MIXER,
			RT5659_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5659_AD_DA_MIXER,
			RT5659_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_L1_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_R1_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_L2_STO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_R2_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_L1_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_R1_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_L2_STO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_STO_DAC_MIXER,
			RT5659_M_DAC_R2_STO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_L1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_R1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_L2_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_R2_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_L1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_R1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_L2_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_MONO_DAC_MIXER,
			RT5659_M_DAC_R2_MONO_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5659_rec1_l_mix[] = अणु
	SOC_DAPM_SINGLE("SPKVOLL Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_SPKVOLL_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_INL_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_BST4_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_BST3_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_BST2_RM1_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_BST1_RM1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_rec1_r_mix[] = अणु
	SOC_DAPM_SINGLE("HPOVOLR Switch", RT5659_REC1_L2_MIXER,
			RT5659_M_HPOVOLR_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5659_REC1_R2_MIXER,
			RT5659_M_INR_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_REC1_R2_MIXER,
			RT5659_M_BST4_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_REC1_R2_MIXER,
			RT5659_M_BST3_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_REC1_R2_MIXER,
			RT5659_M_BST2_RM1_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_REC1_R2_MIXER,
			RT5659_M_BST1_RM1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_rec2_l_mix[] = अणु
	SOC_DAPM_SINGLE("SPKVOLL Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_SPKVOL_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLL Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_OUTVOLL_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_BST4_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_BST3_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_BST2_RM2_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_REC2_L2_MIXER,
			RT5659_M_BST1_RM2_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_rec2_r_mix[] = अणु
	SOC_DAPM_SINGLE("MONOVOL Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_MONOVOL_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLR Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_OUTVOLR_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_BST4_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_BST3_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_BST2_RM2_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_REC2_R2_MIXER,
			RT5659_M_BST1_RM2_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_spk_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_SPK_L_MIXER,
			RT5659_M_DAC_L2_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_SPK_L_MIXER,
			RT5659_M_BST1_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5659_SPK_L_MIXER,
			RT5659_M_IN_L_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5659_SPK_L_MIXER,
			RT5659_M_IN_R_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_SPK_L_MIXER,
			RT5659_M_BST3_SM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_spk_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_SPK_R_MIXER,
			RT5659_M_DAC_R2_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_SPK_R_MIXER,
			RT5659_M_BST4_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5659_SPK_R_MIXER,
			RT5659_M_IN_L_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5659_SPK_R_MIXER,
			RT5659_M_IN_R_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_SPK_R_MIXER,
			RT5659_M_BST3_SM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_monovol_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_DAC_L2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_DAC_R2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_BST1_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_BST2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_BST3_MM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_OUT_L_MIXER,
			RT5659_M_DAC_L2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5659_OUT_L_MIXER,
			RT5659_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5659_OUT_L_MIXER,
			RT5659_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_OUT_L_MIXER,
			RT5659_M_BST2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_OUT_L_MIXER,
			RT5659_M_BST3_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_OUT_R_MIXER,
			RT5659_M_DAC_R2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5659_OUT_R_MIXER,
			RT5659_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5659_OUT_R_MIXER,
			RT5659_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5659_OUT_R_MIXER,
			RT5659_M_BST3_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST4 Switch", RT5659_OUT_R_MIXER,
			RT5659_M_BST4_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_spo_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_SPO_AMP_GAIN,
			RT5659_M_DAC_L2_SPKOMIX_SFT, 1, 0),
	SOC_DAPM_SINGLE("SPKVOL L Switch", RT5659_SPO_AMP_GAIN,
			RT5659_M_SPKVOLL_SPKOMIX_SFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_spo_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_SPO_AMP_GAIN,
			RT5659_M_DAC_R2_SPKOMIX_SFT, 1, 0),
	SOC_DAPM_SINGLE("SPKVOL R Switch", RT5659_SPO_AMP_GAIN,
			RT5659_M_SPKVOLR_SPKOMIX_SFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_DAC_L2_MA_SFT, 1, 1),
	SOC_DAPM_SINGLE("MONOVOL Switch", RT5659_MONOMIX_IN_GAIN,
			RT5659_M_MONOVOL_MA_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_lout_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5659_LOUT_MIXER,
			RT5659_M_DAC_L2_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5659_LOUT_MIXER,
			RT5659_M_OV_L_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_lout_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5659_LOUT_MIXER,
			RT5659_M_DAC_R2_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5659_LOUT_MIXER,
			RT5659_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

/*DAC L2, DAC R2*/
/*MX-1B [6:4], MX-1B [2:0]*/
अटल स्थिर अक्षर * स्थिर rt5659_dac2_src[] = अणु
	"IF1 DAC2", "IF2 DAC", "IF3 DAC", "Mono ADC MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dac_l2_क्रमागत, RT5659_DAC_CTRL,
	RT5659_DAC_L2_SEL_SFT, rt5659_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_l2_mux =
	SOC_DAPM_ENUM("DAC L2 Source", rt5659_dac_l2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dac_r2_क्रमागत, RT5659_DAC_CTRL,
	RT5659_DAC_R2_SEL_SFT, rt5659_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_r2_mux =
	SOC_DAPM_ENUM("DAC R2 Source", rt5659_dac_r2_क्रमागत);


/* STO1 ADC1 Source */
/* MX-26 [13] */
अटल स्थिर अक्षर * स्थिर rt5659_sto1_adc1_src[] = अणु
	"DAC MIX", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_sto1_adc1_क्रमागत, RT5659_STO1_ADC_MIXER,
	RT5659_STO1_ADC1_SRC_SFT, rt5659_sto1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_adc1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC1 Source", rt5659_sto1_adc1_क्रमागत);

/* STO1 ADC Source */
/* MX-26 [12] */
अटल स्थिर अक्षर * स्थिर rt5659_sto1_adc_src[] = अणु
	"ADC1", "ADC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_sto1_adc_क्रमागत, RT5659_STO1_ADC_MIXER,
	RT5659_STO1_ADC_SRC_SFT, rt5659_sto1_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_adc_mux =
	SOC_DAPM_ENUM("Stereo1 ADC Source", rt5659_sto1_adc_क्रमागत);

/* STO1 ADC2 Source */
/* MX-26 [11] */
अटल स्थिर अक्षर * स्थिर rt5659_sto1_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_sto1_adc2_क्रमागत, RT5659_STO1_ADC_MIXER,
	RT5659_STO1_ADC2_SRC_SFT, rt5659_sto1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_adc2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC2 Source", rt5659_sto1_adc2_क्रमागत);

/* STO1 DMIC Source */
/* MX-26 [8] */
अटल स्थिर अक्षर * स्थिर rt5659_sto1_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_sto1_dmic_क्रमागत, RT5659_STO1_ADC_MIXER,
	RT5659_STO1_DMIC_SRC_SFT, rt5659_sto1_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC Source", rt5659_sto1_dmic_क्रमागत);


/* MONO ADC L2 Source */
/* MX-27 [12] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_adc_l2_src[] = अणु
	"Mono DAC MIXL", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adc_l2_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_L2_SRC_SFT, rt5659_mono_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_l2_mux =
	SOC_DAPM_ENUM("Mono ADC L2 Source", rt5659_mono_adc_l2_क्रमागत);


/* MONO ADC L1 Source */
/* MX-27 [11] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_adc_l1_src[] = अणु
	"Mono DAC MIXL", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adc_l1_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_L1_SRC_SFT, rt5659_mono_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_l1_mux =
	SOC_DAPM_ENUM("Mono ADC L1 Source", rt5659_mono_adc_l1_क्रमागत);

/* MONO ADC L Source, MONO ADC R Source*/
/* MX-27 [10:9], MX-27 [2:1] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_adc_src[] = अणु
	"ADC1 L", "ADC1 R", "ADC2 L", "ADC2 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adc_l_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_L_SRC_SFT, rt5659_mono_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_l_mux =
	SOC_DAPM_ENUM("Mono ADC L Source", rt5659_mono_adc_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adcr_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_R_SRC_SFT, rt5659_mono_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_r_mux =
	SOC_DAPM_ENUM("Mono ADC R Source", rt5659_mono_adcr_क्रमागत);

/* MONO DMIC L Source */
/* MX-27 [8] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_dmic_l_src[] = अणु
	"DMIC1 L", "DMIC2 L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_dmic_l_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_DMIC_L_SRC_SFT, rt5659_mono_dmic_l_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_dmic_l_mux =
	SOC_DAPM_ENUM("Mono DMIC L Source", rt5659_mono_dmic_l_क्रमागत);

/* MONO ADC R2 Source */
/* MX-27 [4] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_adc_r2_src[] = अणु
	"Mono DAC MIXR", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adc_r2_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_R2_SRC_SFT, rt5659_mono_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_r2_mux =
	SOC_DAPM_ENUM("Mono ADC R2 Source", rt5659_mono_adc_r2_क्रमागत);

/* MONO ADC R1 Source */
/* MX-27 [3] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_adc_r1_src[] = अणु
	"Mono DAC MIXR", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_adc_r1_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_ADC_R1_SRC_SFT, rt5659_mono_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_adc_r1_mux =
	SOC_DAPM_ENUM("Mono ADC R1 Source", rt5659_mono_adc_r1_क्रमागत);

/* MONO DMIC R Source */
/* MX-27 [0] */
अटल स्थिर अक्षर * स्थिर rt5659_mono_dmic_r_src[] = अणु
	"DMIC1 R", "DMIC2 R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_mono_dmic_r_क्रमागत, RT5659_MONO_ADC_MIXER,
	RT5659_MONO_DMIC_R_SRC_SFT, rt5659_mono_dmic_r_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_mono_dmic_r_mux =
	SOC_DAPM_ENUM("Mono DMIC R Source", rt5659_mono_dmic_r_क्रमागत);


/* DAC R1 Source, DAC L1 Source*/
/* MX-29 [11:10], MX-29 [9:8]*/
अटल स्थिर अक्षर * स्थिर rt5659_dac1_src[] = अणु
	"IF1 DAC1", "IF2 DAC", "IF3 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dac_r1_क्रमागत, RT5659_AD_DA_MIXER,
	RT5659_DAC1_R_SEL_SFT, rt5659_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_r1_mux =
	SOC_DAPM_ENUM("DAC R1 Source", rt5659_dac_r1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dac_l1_क्रमागत, RT5659_AD_DA_MIXER,
	RT5659_DAC1_L_SEL_SFT, rt5659_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dac_l1_mux =
	SOC_DAPM_ENUM("DAC L1 Source", rt5659_dac_l1_क्रमागत);

/* DAC Digital Mixer L Source, DAC Digital Mixer R Source*/
/* MX-2C [6], MX-2C [4]*/
अटल स्थिर अक्षर * स्थिर rt5659_dig_dac_mix_src[] = अणु
	"Stereo DAC Mixer", "Mono DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dig_dac_mixl_क्रमागत, RT5659_DIG_MIXER,
	RT5659_DAC_MIX_L_SFT, rt5659_dig_dac_mix_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dig_dac_mixl_mux =
	SOC_DAPM_ENUM("DAC Digital Mixer L Source", rt5659_dig_dac_mixl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_dig_dac_mixr_क्रमागत, RT5659_DIG_MIXER,
	RT5659_DAC_MIX_R_SFT, rt5659_dig_dac_mix_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_dig_dac_mixr_mux =
	SOC_DAPM_ENUM("DAC Digital Mixer R Source", rt5659_dig_dac_mixr_क्रमागत);

/* Analog DAC L1 Source, Analog DAC R1 Source*/
/* MX-2D [3], MX-2D [2]*/
अटल स्थिर अक्षर * स्थिर rt5659_alg_dac1_src[] = अणु
	"DAC", "Stereo DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_alg_dac_l1_क्रमागत, RT5659_A_DAC_MUX,
	RT5659_A_DACL1_SFT, rt5659_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_alg_dac_l1_mux =
	SOC_DAPM_ENUM("Analog DACL1 Source", rt5659_alg_dac_l1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_alg_dac_r1_क्रमागत, RT5659_A_DAC_MUX,
	RT5659_A_DACR1_SFT, rt5659_alg_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_alg_dac_r1_mux =
	SOC_DAPM_ENUM("Analog DACR1 Source", rt5659_alg_dac_r1_क्रमागत);

/* Analog DAC LR Source, Analog DAC R2 Source*/
/* MX-2D [1], MX-2D [0]*/
अटल स्थिर अक्षर * स्थिर rt5659_alg_dac2_src[] = अणु
	"Stereo DAC Mixer", "Mono DAC Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_alg_dac_l2_क्रमागत, RT5659_A_DAC_MUX,
	RT5659_A_DACL2_SFT, rt5659_alg_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_alg_dac_l2_mux =
	SOC_DAPM_ENUM("Analog DAC L2 Source", rt5659_alg_dac_l2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_alg_dac_r2_क्रमागत, RT5659_A_DAC_MUX,
	RT5659_A_DACR2_SFT, rt5659_alg_dac2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_alg_dac_r2_mux =
	SOC_DAPM_ENUM("Analog DAC R2 Source", rt5659_alg_dac_r2_क्रमागत);

/* Interface2 ADC Data Input*/
/* MX-2F [13:12] */
अटल स्थिर अक्षर * स्थिर rt5659_अगर2_adc_in_src[] = अणु
	"IF_ADC1", "IF_ADC2", "DAC_REF", "IF_ADC3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_अगर2_adc_in_क्रमागत, RT5659_DIG_INF23_DATA,
	RT5659_IF2_ADC_IN_SFT, rt5659_अगर2_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर2_adc_in_mux =
	SOC_DAPM_ENUM("IF2 ADC IN Source", rt5659_अगर2_adc_in_क्रमागत);

/* Interface3 ADC Data Input*/
/* MX-2F [1:0] */
अटल स्थिर अक्षर * स्थिर rt5659_अगर3_adc_in_src[] = अणु
	"IF_ADC1", "IF_ADC2", "DAC_REF", "Stereo2_ADC_L/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_अगर3_adc_in_क्रमागत, RT5659_DIG_INF23_DATA,
	RT5659_IF3_ADC_IN_SFT, rt5659_अगर3_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_अगर3_adc_in_mux =
	SOC_DAPM_ENUM("IF3 ADC IN Source", rt5659_अगर3_adc_in_क्रमागत);

/* PDM 1 L/R*/
/* MX-31 [15] [13] */
अटल स्थिर अक्षर * स्थिर rt5659_pdm_src[] = अणु
	"Mono DAC", "Stereo DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_pdm_l_क्रमागत, RT5659_PDM_OUT_CTRL,
	RT5659_PDM1_L_SFT, rt5659_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_pdm_l_mux =
	SOC_DAPM_ENUM("PDM L Source", rt5659_pdm_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_pdm_r_क्रमागत, RT5659_PDM_OUT_CTRL,
	RT5659_PDM1_R_SFT, rt5659_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_pdm_r_mux =
	SOC_DAPM_ENUM("PDM R Source", rt5659_pdm_r_क्रमागत);

/* SPDIF Output source*/
/* MX-36 [1:0] */
अटल स्थिर अक्षर * स्थिर rt5659_spdअगर_src[] = अणु
	"IF1_DAC1", "IF1_DAC2", "IF2_DAC", "IF3_DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_spdअगर_क्रमागत, RT5659_SPDIF_CTRL,
	RT5659_SPDIF_SEL_SFT, rt5659_spdअगर_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_spdअगर_mux =
	SOC_DAPM_ENUM("SPDIF Source", rt5659_spdअगर_क्रमागत);

/* I2S1 TDM ADCDAT Source */
/* MX-78[4:0] */
अटल स्थिर अक्षर * स्थिर rt5659_rx_adc_data_src[] = अणु
	"AD1:AD2:DAC:NUL", "AD1:AD2:NUL:DAC", "AD1:DAC:AD2:NUL",
	"AD1:DAC:NUL:AD2", "AD1:NUL:DAC:AD2", "AD1:NUL:AD2:DAC",
	"AD2:AD1:DAC:NUL", "AD2:AD1:NUL:DAC", "AD2:DAC:AD1:NUL",
	"AD2:DAC:NUL:AD1", "AD2:NUL:DAC:AD1", "AD1:NUL:AD1:DAC",
	"DAC:AD1:AD2:NUL", "DAC:AD1:NUL:AD2", "DAC:AD2:AD1:NUL",
	"DAC:AD2:NUL:AD1", "DAC:NUL:DAC:AD2", "DAC:NUL:AD2:DAC",
	"NUL:AD1:AD2:DAC", "NUL:AD1:DAC:AD2", "NUL:AD2:AD1:DAC",
	"NUL:AD2:DAC:AD1", "NUL:DAC:DAC:AD2", "NUL:DAC:AD2:DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5659_rx_adc_data_क्रमागत, RT5659_TDM_CTRL_2,
	RT5659_ADCDAT_SRC_SFT, rt5659_rx_adc_data_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5659_rx_adc_dac_mux =
	SOC_DAPM_ENUM("TDM ADCDAT Source", rt5659_rx_adc_data_क्रमागत);

/* Out Volume Switch */
अटल स्थिर काष्ठा snd_kcontrol_new spkvol_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_SPO_VOL, RT5659_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spkvol_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_SPO_VOL, RT5659_VOL_R_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new monovol_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_MONO_OUT, RT5659_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new outvol_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_LOUT, RT5659_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new outvol_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_LOUT, RT5659_VOL_R_SFT, 1, 1);

/* Out Switch */
अटल स्थिर काष्ठा snd_kcontrol_new spo_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_CLASSD_2, RT5659_M_RF_DIG_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new mono_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_MONO_OUT, RT5659_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpo_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_HP_VOL, RT5659_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpo_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_HP_VOL, RT5659_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_LOUT, RT5659_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_LOUT, RT5659_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm_l_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_PDM_OUT_CTRL, RT5659_M_PDM1_L_SFT, 1,
		1);

अटल स्थिर काष्ठा snd_kcontrol_new pdm_r_चयन =
	SOC_DAPM_SINGLE("Switch", RT5659_PDM_OUT_CTRL, RT5659_M_PDM1_R_SFT, 1,
		1);

अटल पूर्णांक rt5659_spk_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5659_CLASSD_CTRL_1,
			RT5659_POW_CLSD_DB_MASK, RT5659_POW_CLSD_DB_EN);
		snd_soc_component_update_bits(component, RT5659_CLASSD_2,
			RT5659_M_RI_DIG, RT5659_M_RI_DIG);
		snd_soc_component_ग_लिखो(component, RT5659_CLASSD_1, 0x0803);
		snd_soc_component_ग_लिखो(component, RT5659_SPK_DC_CAILB_CTRL_3, 0x0000);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, RT5659_CLASSD_1, 0x0011);
		snd_soc_component_update_bits(component, RT5659_CLASSD_2,
			RT5659_M_RI_DIG, 0x0);
		snd_soc_component_ग_लिखो(component, RT5659_SPK_DC_CAILB_CTRL_3, 0x0003);
		snd_soc_component_update_bits(component, RT5659_CLASSD_CTRL_1,
			RT5659_POW_CLSD_DB_MASK, RT5659_POW_CLSD_DB_DIS);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rt5659_mono_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_ग_लिखो(component, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e00);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e04);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rt5659_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो(component, RT5659_HP_CHARGE_PUMP_1, 0x0e1e);
		snd_soc_component_update_bits(component, RT5659_DEPOP_1, 0x0010, 0x0010);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_ग_लिखो(component, RT5659_DEPOP_1, 0x0000);
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
		msleep(450);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5659_particular_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT5659_PWR_ANLG_3, RT5659_PWR_LDO2_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5659_PWR_ANLG_2, RT5659_PWR_MB1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Det Power", RT5659_PWR_VOL,
		RT5659_PWR_MIC_DET_BIT, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5659_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL", RT5659_PWR_ANLG_3, RT5659_PWR_PLL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mono Vref", RT5659_PWR_ANLG_1,
		RT5659_PWR_VREF3_BIT, 0, शून्य, 0),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5659_ASRC_1,
		RT5659_I2S1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5659_ASRC_1,
		RT5659_I2S2_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S3 ASRC", 1, RT5659_ASRC_1,
		RT5659_I2S3_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO ASRC", 1, RT5659_ASRC_1,
		RT5659_DAC_STO_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC Mono L ASRC", 1, RT5659_ASRC_1,
		RT5659_DAC_MONO_L_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC Mono R ASRC", 1, RT5659_ASRC_1,
		RT5659_DAC_MONO_R_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5659_ASRC_1,
		RT5659_ADC_STO1_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC Mono L ASRC", 1, RT5659_ASRC_1,
		RT5659_ADC_MONO_L_ASRC_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC Mono R ASRC", 1, RT5659_ASRC_1,
		RT5659_ADC_MONO_R_ASRC_SFT, 0, शून्य, 0),

	/* Input Side */
	SND_SOC_DAPM_SUPPLY("MICBIAS2", RT5659_PWR_ANLG_2, RT5659_PWR_MB2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS3", RT5659_PWR_ANLG_2, RT5659_PWR_MB3_BIT,
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
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5659_DMIC_CTRL_1,
		RT5659_DMIC_1_EN_SFT, 0, set_dmic_घातer, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC2 Power", RT5659_DMIC_CTRL_1,
		RT5659_DMIC_2_EN_SFT, 0, set_dmic_घातer, SND_SOC_DAPM_POST_PMU),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST1_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST2", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST2_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST3", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST3_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST4", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST4_P_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST1 Power", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST2 Power", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST3 Power", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST3_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BST4 Power", RT5659_PWR_ANLG_2,
		RT5659_PWR_BST4_BIT, 0, शून्य, 0),


	/* Input Volume */
	SND_SOC_DAPM_PGA("INL VOL", RT5659_PWR_VOL, RT5659_PWR_IN_L_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR VOL", RT5659_PWR_VOL, RT5659_PWR_IN_R_BIT,
		0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIX1L", RT5659_PWR_MIXER, RT5659_PWR_RM1_L_BIT,
		0, rt5659_rec1_l_mix, ARRAY_SIZE(rt5659_rec1_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIX1R", RT5659_PWR_MIXER, RT5659_PWR_RM1_R_BIT,
		0, rt5659_rec1_r_mix, ARRAY_SIZE(rt5659_rec1_r_mix)),
	SND_SOC_DAPM_MIXER("RECMIX2L", RT5659_PWR_MIXER, RT5659_PWR_RM2_L_BIT,
		0, rt5659_rec2_l_mix, ARRAY_SIZE(rt5659_rec2_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIX2R", RT5659_PWR_MIXER, RT5659_PWR_RM2_R_BIT,
		0, rt5659_rec2_r_mix, ARRAY_SIZE(rt5659_rec2_r_mix)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1 L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC1 R", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC2 L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC2 R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("ADC1 L Power", RT5659_PWR_DIG_1,
		RT5659_PWR_ADC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 R Power", RT5659_PWR_DIG_1,
		RT5659_PWR_ADC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 L Power", RT5659_PWR_DIG_1,
		RT5659_PWR_ADC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 R Power", RT5659_PWR_DIG_1,
		RT5659_PWR_ADC_R2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 clock", SND_SOC_NOPM, 0, 0, set_adc1_clk,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("ADC2 clock", SND_SOC_NOPM, 0, 0, set_adc2_clk,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_sto1_adc_mux),
	SND_SOC_DAPM_MUX("Mono ADC L2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_l2_mux),
	SND_SOC_DAPM_MUX("Mono ADC R2 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_r2_mux),
	SND_SOC_DAPM_MUX("Mono ADC L1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_l1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R1 Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_r1_mux),
	SND_SOC_DAPM_MUX("Mono DMIC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_dmic_l_mux),
	SND_SOC_DAPM_MUX("Mono DMIC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_dmic_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC L Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_l_mux),
	SND_SOC_DAPM_MUX("Mono ADC R Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_mono_adc_r_mux),
	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("ADC Stereo1 Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Stereo2 Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_ADC_S2F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", SND_SOC_NOPM,
		0, 0, rt5659_sto1_adc_l_mix,
		ARRAY_SIZE(rt5659_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", SND_SOC_NOPM,
		0, 0, rt5659_sto1_adc_r_mix,
		ARRAY_SIZE(rt5659_sto1_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Left Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXL", RT5659_MONO_ADC_DIG_VOL,
		RT5659_L_MUTE_SFT, 1, rt5659_mono_adc_l_mix,
		ARRAY_SIZE(rt5659_mono_adc_l_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Right Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXR", RT5659_MONO_ADC_DIG_VOL,
		RT5659_R_MUTE_SFT, 1, rt5659_mono_adc_r_mix,
		ARRAY_SIZE(rt5659_mono_adc_r_mix)),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("IF_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC LR", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Stereo1 ADC Volume L", RT5659_STO1_ADC_DIG_VOL,
		RT5659_L_MUTE_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC Volume R", RT5659_STO1_ADC_DIG_VOL,
		RT5659_R_MUTE_SFT, 1, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5659_PWR_DIG_1, RT5659_PWR_I2S1_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5659_PWR_DIG_1, RT5659_PWR_I2S2_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S3", RT5659_PWR_DIG_1, RT5659_PWR_I2S3_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF3 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_PGA("TDM AD1:AD2:DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("TDM AD2:DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("TDM Data Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_rx_adc_dac_mux),
	SND_SOC_DAPM_MUX("IF2 ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_अगर2_adc_in_mux),
	SND_SOC_DAPM_MUX("IF3 ADC Mux", SND_SOC_NOPM, 0, 0,
		&rt5659_अगर3_adc_in_mux),
	SND_SOC_DAPM_MUX("IF1 01 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर1_01_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 23 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर1_23_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 45 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर1_45_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF1 67 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर1_67_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF2 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर2_dac_swap_mux),
	SND_SOC_DAPM_MUX("IF2 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर2_adc_swap_mux),
	SND_SOC_DAPM_MUX("IF3 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर3_dac_swap_mux),
	SND_SOC_DAPM_MUX("IF3 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5659_अगर3_adc_swap_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3RX", "AIF3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "AIF3 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
		rt5659_dac_l_mix, ARRAY_SIZE(rt5659_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
		rt5659_dac_r_mix, ARRAY_SIZE(rt5659_dac_r_mix)),

	/* DAC channel Mux */
	SND_SOC_DAPM_MUX("DAC L1 Mux", SND_SOC_NOPM, 0, 0, &rt5659_dac_l1_mux),
	SND_SOC_DAPM_MUX("DAC R1 Mux", SND_SOC_NOPM, 0, 0, &rt5659_dac_r1_mux),
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0, &rt5659_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0, &rt5659_dac_r2_mux),

	SND_SOC_DAPM_MUX("DAC L1 Source", SND_SOC_NOPM, 0, 0,
		&rt5659_alg_dac_l1_mux),
	SND_SOC_DAPM_MUX("DAC R1 Source", SND_SOC_NOPM, 0, 0,
		&rt5659_alg_dac_r1_mux),
	SND_SOC_DAPM_MUX("DAC L2 Source", SND_SOC_NOPM, 0, 0,
		&rt5659_alg_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Source", SND_SOC_NOPM, 0, 0,
		&rt5659_alg_dac_r2_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("DAC Stereo1 Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_DAC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Left Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_DAC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Right Filter", RT5659_PWR_DIG_2,
		RT5659_PWR_DAC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5659_sto_dac_l_mix, ARRAY_SIZE(rt5659_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5659_sto_dac_r_mix, ARRAY_SIZE(rt5659_sto_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5659_mono_dac_l_mix, ARRAY_SIZE(rt5659_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5659_mono_dac_r_mix, ARRAY_SIZE(rt5659_mono_dac_r_mix)),
	SND_SOC_DAPM_MUX("DAC MIXL", SND_SOC_NOPM, 0, 0,
		&rt5659_dig_dac_mixl_mux),
	SND_SOC_DAPM_MUX("DAC MIXR", SND_SOC_NOPM, 0, 0,
		&rt5659_dig_dac_mixr_mux),

	/* DACs */
	SND_SOC_DAPM_SUPPLY_S("DAC L1 Power", 1, RT5659_PWR_DIG_1,
		RT5659_PWR_DAC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC R1 Power", 1, RT5659_PWR_DIG_1,
		RT5659_PWR_DAC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC L1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("DAC L2 Power", RT5659_PWR_DIG_1,
		RT5659_PWR_DAC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R2 Power", RT5659_PWR_DIG_1,
		RT5659_PWR_DAC_R2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC L2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("DAC_REF", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("SPK MIXL", RT5659_PWR_MIXER, RT5659_PWR_SM_L_BIT,
		0, rt5659_spk_l_mix, ARRAY_SIZE(rt5659_spk_l_mix)),
	SND_SOC_DAPM_MIXER("SPK MIXR", RT5659_PWR_MIXER, RT5659_PWR_SM_R_BIT,
		0, rt5659_spk_r_mix, ARRAY_SIZE(rt5659_spk_r_mix)),
	SND_SOC_DAPM_MIXER("MONOVOL MIX", RT5659_PWR_MIXER, RT5659_PWR_MM_BIT,
		0, rt5659_monovol_mix, ARRAY_SIZE(rt5659_monovol_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5659_PWR_MIXER, RT5659_PWR_OM_L_BIT,
		0, rt5659_out_l_mix, ARRAY_SIZE(rt5659_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5659_PWR_MIXER, RT5659_PWR_OM_R_BIT,
		0, rt5659_out_r_mix, ARRAY_SIZE(rt5659_out_r_mix)),

	/* Output Volume */
	SND_SOC_DAPM_SWITCH("SPKVOL L", RT5659_PWR_VOL, RT5659_PWR_SV_L_BIT, 0,
		&spkvol_l_चयन),
	SND_SOC_DAPM_SWITCH("SPKVOL R", RT5659_PWR_VOL, RT5659_PWR_SV_R_BIT, 0,
		&spkvol_r_चयन),
	SND_SOC_DAPM_SWITCH("MONOVOL", RT5659_PWR_VOL, RT5659_PWR_MV_BIT, 0,
		&monovol_चयन),
	SND_SOC_DAPM_SWITCH("OUTVOL L", RT5659_PWR_VOL, RT5659_PWR_OV_L_BIT, 0,
		&outvol_l_चयन),
	SND_SOC_DAPM_SWITCH("OUTVOL R", RT5659_PWR_VOL, RT5659_PWR_OV_R_BIT, 0,
		&outvol_r_चयन),

	/* SPO/MONO/HPO/LOUT */
	SND_SOC_DAPM_MIXER("SPO L MIX", SND_SOC_NOPM, 0, 0, rt5659_spo_l_mix,
		ARRAY_SIZE(rt5659_spo_l_mix)),
	SND_SOC_DAPM_MIXER("SPO R MIX", SND_SOC_NOPM, 0, 0, rt5659_spo_r_mix,
		ARRAY_SIZE(rt5659_spo_r_mix)),
	SND_SOC_DAPM_MIXER("Mono MIX", SND_SOC_NOPM, 0,	0, rt5659_mono_mix,
		ARRAY_SIZE(rt5659_mono_mix)),
	SND_SOC_DAPM_MIXER("LOUT L MIX", SND_SOC_NOPM, 0, 0, rt5659_lout_l_mix,
		ARRAY_SIZE(rt5659_lout_l_mix)),
	SND_SOC_DAPM_MIXER("LOUT R MIX", SND_SOC_NOPM, 0, 0, rt5659_lout_r_mix,
		ARRAY_SIZE(rt5659_lout_r_mix)),

	SND_SOC_DAPM_PGA_S("SPK Amp", 1, RT5659_PWR_DIG_1, RT5659_PWR_CLS_D_BIT,
		0, rt5659_spk_event, SND_SOC_DAPM_POST_PMD |
		SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_PGA_S("Mono Amp", 1, RT5659_PWR_ANLG_1, RT5659_PWR_MA_BIT,
		0, rt5659_mono_event, SND_SOC_DAPM_POST_PMD |
		SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, rt5659_hp_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT Amp", 1,  RT5659_PWR_ANLG_1, RT5659_PWR_LM_BIT,
		0,  शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Charge Pump", SND_SOC_NOPM, 0, 0,
		rt5659_अक्षरge_pump_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SWITCH("SPO Playback", SND_SOC_NOPM, 0, 0, &spo_चयन),
	SND_SOC_DAPM_SWITCH("Mono Playback", SND_SOC_NOPM, 0, 0,
		&mono_चयन),
	SND_SOC_DAPM_SWITCH("HPO L Playback", SND_SOC_NOPM, 0, 0,
		&hpo_l_चयन),
	SND_SOC_DAPM_SWITCH("HPO R Playback", SND_SOC_NOPM, 0, 0,
		&hpo_r_चयन),
	SND_SOC_DAPM_SWITCH("LOUT L Playback", SND_SOC_NOPM, 0, 0,
		&lout_l_चयन),
	SND_SOC_DAPM_SWITCH("LOUT R Playback", SND_SOC_NOPM, 0, 0,
		&lout_r_चयन),
	SND_SOC_DAPM_SWITCH("PDM L Playback", SND_SOC_NOPM, 0, 0,
		&pdm_l_चयन),
	SND_SOC_DAPM_SWITCH("PDM R Playback", SND_SOC_NOPM, 0, 0,
		&pdm_r_चयन),

	/* PDM */
	SND_SOC_DAPM_SUPPLY("PDM Power", RT5659_PWR_DIG_2,
		RT5659_PWR_PDM1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("PDM L Mux", RT5659_PDM_OUT_CTRL,
		RT5659_M_PDM1_L_SFT, 1, &rt5659_pdm_l_mux),
	SND_SOC_DAPM_MUX("PDM R Mux", RT5659_PDM_OUT_CTRL,
		RT5659_M_PDM1_R_SFT, 1, &rt5659_pdm_r_mux),

	/* SPDIF */
	SND_SOC_DAPM_MUX("SPDIF Mux", SND_SOC_NOPM, 0, 0, &rt5659_spdअगर_mux),

	SND_SOC_DAPM_SUPPLY("SYS CLK DET", RT5659_CLK_DET, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKDET", RT5659_CLK_DET, 0, 0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("PDML"),
	SND_SOC_DAPM_OUTPUT("PDMR"),
	SND_SOC_DAPM_OUTPUT("SPDIF"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5659_dapm_routes[] = अणु
	/*PLL*/
	अणु "ADC Stereo1 Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "ADC Stereo2 Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "ADC Mono Left Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "ADC Mono Right Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "DAC Stereo1 Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "DAC Mono Left Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,
	अणु "DAC Mono Right Filter", शून्य, "PLL", is_sys_clk_from_pll पूर्ण,

	/*ASRC*/
	अणु "ADC Stereo1 Filter", शून्य, "ADC STO1 ASRC", is_using_asrc पूर्ण,
	अणु "ADC Mono Left Filter", शून्य, "ADC Mono L ASRC", is_using_asrc पूर्ण,
	अणु "ADC Mono Right Filter", शून्य, "ADC Mono R ASRC", is_using_asrc पूर्ण,
	अणु "DAC Mono Left Filter", शून्य, "DAC Mono L ASRC", is_using_asrc पूर्ण,
	अणु "DAC Mono Right Filter", शून्य, "DAC Mono R ASRC", is_using_asrc पूर्ण,
	अणु "DAC Stereo1 Filter", शून्य, "DAC STO ASRC", is_using_asrc पूर्ण,

	अणु "SYS CLK DET", शून्य, "CLKDET" पूर्ण,

	अणु "I2S1", शून्य, "I2S1 ASRC" पूर्ण,
	अणु "I2S2", शून्य, "I2S2 ASRC" पूर्ण,
	अणु "I2S3", शून्य, "I2S3 ASRC" पूर्ण,

	अणु "DMIC1", शून्य, "DMIC L1" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC R1" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC L2" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC R2" पूर्ण,

	अणु "BST1", शून्य, "IN1P" पूर्ण,
	अणु "BST1", शून्य, "IN1N" पूर्ण,
	अणु "BST1", शून्य, "BST1 Power" पूर्ण,
	अणु "BST2", शून्य, "IN2P" पूर्ण,
	अणु "BST2", शून्य, "IN2N" पूर्ण,
	अणु "BST2", शून्य, "BST2 Power" पूर्ण,
	अणु "BST3", शून्य, "IN3P" पूर्ण,
	अणु "BST3", शून्य, "IN3N" पूर्ण,
	अणु "BST3", शून्य, "BST3 Power" पूर्ण,
	अणु "BST4", शून्य, "IN4P" पूर्ण,
	अणु "BST4", शून्य, "IN4N" पूर्ण,
	अणु "BST4", शून्य, "BST4 Power" पूर्ण,

	अणु "INL VOL", शून्य, "IN2P" पूर्ण,
	अणु "INR VOL", शून्य, "IN2N" पूर्ण,

	अणु "RECMIX1L", "SPKVOLL Switch", "SPKVOL L" पूर्ण,
	अणु "RECMIX1L", "INL Switch", "INL VOL" पूर्ण,
	अणु "RECMIX1L", "BST4 Switch", "BST4" पूर्ण,
	अणु "RECMIX1L", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIX1L", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIX1L", "BST1 Switch", "BST1" पूर्ण,

	अणु "RECMIX1R", "HPOVOLR Switch", "HPO R Playback" पूर्ण,
	अणु "RECMIX1R", "INR Switch", "INR VOL" पूर्ण,
	अणु "RECMIX1R", "BST4 Switch", "BST4" पूर्ण,
	अणु "RECMIX1R", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIX1R", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIX1R", "BST1 Switch", "BST1" पूर्ण,

	अणु "RECMIX2L", "SPKVOLL Switch", "SPKVOL L" पूर्ण,
	अणु "RECMIX2L", "OUTVOLL Switch", "OUTVOL L" पूर्ण,
	अणु "RECMIX2L", "BST4 Switch", "BST4" पूर्ण,
	अणु "RECMIX2L", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIX2L", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIX2L", "BST1 Switch", "BST1" पूर्ण,

	अणु "RECMIX2R", "MONOVOL Switch", "MONOVOL" पूर्ण,
	अणु "RECMIX2R", "OUTVOLR Switch", "OUTVOL R" पूर्ण,
	अणु "RECMIX2R", "BST4 Switch", "BST4" पूर्ण,
	अणु "RECMIX2R", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIX2R", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIX2R", "BST1 Switch", "BST1" पूर्ण,

	अणु "ADC1 L", शून्य, "RECMIX1L" पूर्ण,
	अणु "ADC1 L", शून्य, "ADC1 L Power" पूर्ण,
	अणु "ADC1 L", शून्य, "ADC1 clock" पूर्ण,
	अणु "ADC1 R", शून्य, "RECMIX1R" पूर्ण,
	अणु "ADC1 R", शून्य, "ADC1 R Power" पूर्ण,
	अणु "ADC1 R", शून्य, "ADC1 clock" पूर्ण,

	अणु "ADC2 L", शून्य, "RECMIX2L" पूर्ण,
	अणु "ADC2 L", शून्य, "ADC2 L Power" पूर्ण,
	अणु "ADC2 L", शून्य, "ADC2 clock" पूर्ण,
	अणु "ADC2 R", शून्य, "RECMIX2R" पूर्ण,
	अणु "ADC2 R", शून्य, "ADC2 R Power" पूर्ण,
	अणु "ADC2 R", शून्य, "ADC2 clock" पूर्ण,

	अणु "DMIC L1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L1", शून्य, "DMIC1 Power" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC1 Power" पूर्ण,
	अणु "DMIC L2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L2", शून्य, "DMIC2 Power" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC2 Power" पूर्ण,

	अणु "Stereo1 DMIC L Mux", "DMIC1", "DMIC L1" पूर्ण,
	अणु "Stereo1 DMIC L Mux", "DMIC2", "DMIC L2" पूर्ण,

	अणु "Stereo1 DMIC R Mux", "DMIC1", "DMIC R1" पूर्ण,
	अणु "Stereo1 DMIC R Mux", "DMIC2", "DMIC R2" पूर्ण,

	अणु "Mono DMIC L Mux", "DMIC1 L", "DMIC L1" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC2 L", "DMIC L2" पूर्ण,

	अणु "Mono DMIC R Mux", "DMIC1 R", "DMIC R1" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC2 R", "DMIC R2" पूर्ण,

	अणु "Stereo1 ADC L Mux", "ADC1", "ADC1 L" पूर्ण,
	अणु "Stereo1 ADC L Mux", "ADC2", "ADC2 L" पूर्ण,
	अणु "Stereo1 ADC R Mux", "ADC1", "ADC1 R" पूर्ण,
	अणु "Stereo1 ADC R Mux", "ADC2", "ADC2 R" पूर्ण,

	अणु "Stereo1 ADC L1 Mux", "ADC", "Stereo1 ADC L Mux" पूर्ण,
	अणु "Stereo1 ADC L1 Mux", "DAC MIX", "DAC MIXL" पूर्ण,
	अणु "Stereo1 ADC L2 Mux", "DMIC", "Stereo1 DMIC L Mux" पूर्ण,
	अणु "Stereo1 ADC L2 Mux", "DAC MIX", "DAC MIXL" पूर्ण,

	अणु "Stereo1 ADC R1 Mux", "ADC", "Stereo1 ADC R Mux" पूर्ण,
	अणु "Stereo1 ADC R1 Mux", "DAC MIX", "DAC MIXR" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DMIC", "Stereo1 DMIC R Mux" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DAC MIX", "DAC MIXR" पूर्ण,

	अणु "Mono ADC L Mux", "ADC1 L", "ADC1 L" पूर्ण,
	अणु "Mono ADC L Mux", "ADC1 R", "ADC1 R" पूर्ण,
	अणु "Mono ADC L Mux", "ADC2 L", "ADC2 L" पूर्ण,
	अणु "Mono ADC L Mux", "ADC2 R", "ADC2 R" पूर्ण,

	अणु "Mono ADC R Mux", "ADC1 L", "ADC1 L" पूर्ण,
	अणु "Mono ADC R Mux", "ADC1 R", "ADC1 R" पूर्ण,
	अणु "Mono ADC R Mux", "ADC2 L", "ADC2 L" पूर्ण,
	अणु "Mono ADC R Mux", "ADC2 R", "ADC2 R" पूर्ण,

	अणु "Mono ADC L2 Mux", "DMIC", "Mono DMIC L Mux" पूर्ण,
	अणु "Mono ADC L2 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "ADC",  "Mono ADC L Mux" पूर्ण,

	अणु "Mono ADC R1 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,
	अणु "Mono ADC R1 Mux", "ADC", "Mono ADC R Mux" पूर्ण,
	अणु "Mono ADC R2 Mux", "DMIC", "Mono DMIC R Mux" पूर्ण,
	अणु "Mono ADC R2 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,

	अणु "Stereo1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux" पूर्ण,
	अणु "Stereo1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux" पूर्ण,
	अणु "Stereo1 ADC MIXL", शून्य, "ADC Stereo1 Filter" पूर्ण,

	अणु "Stereo1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux" पूर्ण,
	अणु "Stereo1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "ADC Stereo1 Filter" पूर्ण,

	अणु "Mono ADC MIXL", "ADC1 Switch", "Mono ADC L1 Mux" पूर्ण,
	अणु "Mono ADC MIXL", "ADC2 Switch", "Mono ADC L2 Mux" पूर्ण,
	अणु "Mono ADC MIXL", शून्य, "ADC Mono Left Filter" पूर्ण,

	अणु "Mono ADC MIXR", "ADC1 Switch", "Mono ADC R1 Mux" पूर्ण,
	अणु "Mono ADC MIXR", "ADC2 Switch", "Mono ADC R2 Mux" पूर्ण,
	अणु "Mono ADC MIXR", शून्य, "ADC Mono Right Filter" पूर्ण,

	अणु "Stereo1 ADC Volume L", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC Volume R", शून्य, "Stereo1 ADC MIXR" पूर्ण,

	अणु "IF_ADC1", शून्य, "Stereo1 ADC Volume L" पूर्ण,
	अणु "IF_ADC1", शून्य, "Stereo1 ADC Volume R" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXL" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXR" पूर्ण,

	अणु "TDM AD1:AD2:DAC", शून्य, "IF_ADC1" पूर्ण,
	अणु "TDM AD1:AD2:DAC", शून्य, "IF_ADC2" पूर्ण,
	अणु "TDM AD1:AD2:DAC", शून्य, "DAC_REF" पूर्ण,
	अणु "TDM AD2:DAC", शून्य, "IF_ADC2" पूर्ण,
	अणु "TDM AD2:DAC", शून्य, "DAC_REF" पूर्ण,
	अणु "TDM Data Mux", "AD1:AD2:DAC:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:AD2:NUL:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:DAC:AD2:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:DAC:NUL:AD2", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:NUL:DAC:AD2", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:NUL:AD2:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD2:AD1:DAC:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD2:AD1:NUL:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD2:DAC:AD1:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD2:DAC:NUL:AD1", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD2:NUL:DAC:AD1", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "AD1:NUL:AD1:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:AD1:AD2:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:AD1:NUL:AD2", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:AD2:AD1:NUL", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:AD2:NUL:AD1", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:NUL:DAC:AD2", "TDM AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "DAC:NUL:AD2:DAC", "TDM AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:AD1:AD2:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:AD1:DAC:AD2", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:AD2:AD1:DAC", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:AD2:DAC:AD1", "TDM AD1:AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:DAC:DAC:AD2", "TDM AD2:DAC" पूर्ण,
	अणु "TDM Data Mux", "NUL:DAC:AD2:DAC", "TDM AD2:DAC" पूर्ण,
	अणु "IF1 01 ADC Swap Mux", "L/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 01 ADC Swap Mux", "R/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 01 ADC Swap Mux", "L/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 01 ADC Swap Mux", "R/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 23 ADC Swap Mux", "L/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 23 ADC Swap Mux", "R/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 23 ADC Swap Mux", "L/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 23 ADC Swap Mux", "R/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 45 ADC Swap Mux", "L/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 45 ADC Swap Mux", "R/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 45 ADC Swap Mux", "L/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 45 ADC Swap Mux", "R/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 67 ADC Swap Mux", "L/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 67 ADC Swap Mux", "R/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 67 ADC Swap Mux", "L/L", "TDM Data Mux" पूर्ण,
	अणु "IF1 67 ADC Swap Mux", "R/R", "TDM Data Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 01 ADC Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 23 ADC Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 45 ADC Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1 67 ADC Swap Mux" पूर्ण,
	अणु "IF1 ADC", शून्य, "I2S1" पूर्ण,

	अणु "IF2 ADC Mux", "IF_ADC1", "IF_ADC1" पूर्ण,
	अणु "IF2 ADC Mux", "IF_ADC2", "IF_ADC2" पूर्ण,
	अणु "IF2 ADC Mux", "IF_ADC3", "IF_ADC3" पूर्ण,
	अणु "IF2 ADC Mux", "DAC_REF", "DAC_REF" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC Mux"पूर्ण,
	अणु "IF2 ADC", शून्य, "I2S2" पूर्ण,

	अणु "IF3 ADC Mux", "IF_ADC1", "IF_ADC1" पूर्ण,
	अणु "IF3 ADC Mux", "IF_ADC2", "IF_ADC2" पूर्ण,
	अणु "IF3 ADC Mux", "Stereo2_ADC_L/R", "Stereo2 ADC LR" पूर्ण,
	अणु "IF3 ADC Mux", "DAC_REF", "DAC_REF" पूर्ण,
	अणु "IF3 ADC", शून्य, "IF3 ADC Mux"पूर्ण,
	अणु "IF3 ADC", शून्य, "I2S3" पूर्ण,

	अणु "AIF1TX", शून्य, "IF1 ADC" पूर्ण,
	अणु "IF2 ADC Swap Mux", "L/R", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC Swap Mux", "R/L", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC Swap Mux", "L/L", "IF2 ADC" पूर्ण,
	अणु "IF2 ADC Swap Mux", "R/R", "IF2 ADC" पूर्ण,
	अणु "AIF2TX", शून्य, "IF2 ADC Swap Mux" पूर्ण,
	अणु "IF3 ADC Swap Mux", "L/R", "IF3 ADC" पूर्ण,
	अणु "IF3 ADC Swap Mux", "R/L", "IF3 ADC" पूर्ण,
	अणु "IF3 ADC Swap Mux", "L/L", "IF3 ADC" पूर्ण,
	अणु "IF3 ADC Swap Mux", "R/R", "IF3 ADC" पूर्ण,
	अणु "AIF3TX", शून्य, "IF3 ADC Swap Mux" पूर्ण,

	अणु "IF1 DAC1", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC2", शून्य, "AIF1RX" पूर्ण,
	अणु "IF2 DAC Swap Mux", "L/R", "AIF2RX" पूर्ण,
	अणु "IF2 DAC Swap Mux", "R/L", "AIF2RX" पूर्ण,
	अणु "IF2 DAC Swap Mux", "L/L", "AIF2RX" पूर्ण,
	अणु "IF2 DAC Swap Mux", "R/R", "AIF2RX" पूर्ण,
	अणु "IF2 DAC", शून्य, "IF2 DAC Swap Mux" पूर्ण,
	अणु "IF3 DAC Swap Mux", "L/R", "AIF3RX" पूर्ण,
	अणु "IF3 DAC Swap Mux", "R/L", "AIF3RX" पूर्ण,
	अणु "IF3 DAC Swap Mux", "L/L", "AIF3RX" पूर्ण,
	अणु "IF3 DAC Swap Mux", "R/R", "AIF3RX" पूर्ण,
	अणु "IF3 DAC", शून्य, "IF3 DAC Swap Mux" पूर्ण,

	अणु "IF1 DAC1", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC2", शून्य, "I2S1" पूर्ण,
	अणु "IF2 DAC", शून्य, "I2S2" पूर्ण,
	अणु "IF3 DAC", शून्य, "I2S3" पूर्ण,

	अणु "IF1 DAC2 L", शून्य, "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC2 R", शून्य, "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC1 L", शून्य, "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC1 R", शून्य, "IF1 DAC1" पूर्ण,
	अणु "IF2 DAC L", शून्य, "IF2 DAC" पूर्ण,
	अणु "IF2 DAC R", शून्य, "IF2 DAC" पूर्ण,
	अणु "IF3 DAC L", शून्य, "IF3 DAC" पूर्ण,
	अणु "IF3 DAC R", शून्य, "IF3 DAC" पूर्ण,

	अणु "DAC L1 Mux", "IF1 DAC1", "IF1 DAC1 L" पूर्ण,
	अणु "DAC L1 Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,
	अणु "DAC L1 Mux", "IF3 DAC", "IF3 DAC L" पूर्ण,
	अणु "DAC L1 Mux", शून्य, "DAC Stereo1 Filter" पूर्ण,

	अणु "DAC R1 Mux", "IF1 DAC1", "IF1 DAC1 R" पूर्ण,
	अणु "DAC R1 Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,
	अणु "DAC R1 Mux", "IF3 DAC", "IF3 DAC R" पूर्ण,
	अणु "DAC R1 Mux", शून्य, "DAC Stereo1 Filter" पूर्ण,

	अणु "DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC Volume L" पूर्ण,
	अणु "DAC1 MIXL", "DAC1 Switch", "DAC L1 Mux" पूर्ण,
	अणु "DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC Volume R" पूर्ण,
	अणु "DAC1 MIXR", "DAC1 Switch", "DAC R1 Mux" पूर्ण,

	अणु "DAC_REF", शून्य, "DAC1 MIXL" पूर्ण,
	अणु "DAC_REF", शून्य, "DAC1 MIXR" पूर्ण,

	अणु "DAC L2 Mux", "IF1 DAC2", "IF1 DAC2 L" पूर्ण,
	अणु "DAC L2 Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,
	अणु "DAC L2 Mux", "IF3 DAC", "IF3 DAC L" पूर्ण,
	अणु "DAC L2 Mux", "Mono ADC MIX", "Mono ADC MIXL" पूर्ण,
	अणु "DAC L2 Mux", शून्य, "DAC Mono Left Filter" पूर्ण,

	अणु "DAC R2 Mux", "IF1 DAC2", "IF1 DAC2 R" पूर्ण,
	अणु "DAC R2 Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,
	अणु "DAC R2 Mux", "IF3 DAC", "IF3 DAC R" पूर्ण,
	अणु "DAC R2 Mux", "Mono ADC MIX", "Mono ADC MIXR" पूर्ण,
	अणु "DAC R2 Mux", शून्य, "DAC Mono Right Filter" पूर्ण,

	अणु "Stereo DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC L2 Switch", "DAC L2 Mux" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC R2 Switch", "DAC R2 Mux" पूर्ण,

	अणु "Stereo DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC L2 Switch", "DAC L2 Mux" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R2 Switch", "DAC R2 Mux" पूर्ण,

	अणु "Mono DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Mono DAC MIXL", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Mono DAC MIXL", "DAC L2 Switch", "DAC L2 Mux" पूर्ण,
	अणु "Mono DAC MIXL", "DAC R2 Switch", "DAC R2 Mux" पूर्ण,
	अणु "Mono DAC MIXR", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R2 Switch", "DAC R2 Mux" पूर्ण,
	अणु "Mono DAC MIXR", "DAC L2 Switch", "DAC L2 Mux" पूर्ण,

	अणु "DAC MIXL", "Stereo DAC Mixer", "Stereo DAC MIXL" पूर्ण,
	अणु "DAC MIXL", "Mono DAC Mixer", "Mono DAC MIXL" पूर्ण,
	अणु "DAC MIXR", "Stereo DAC Mixer", "Stereo DAC MIXR" पूर्ण,
	अणु "DAC MIXR", "Mono DAC Mixer", "Mono DAC MIXR" पूर्ण,

	अणु "DAC L1 Source", शून्य, "DAC L1 Power" पूर्ण,
	अणु "DAC L1 Source", "DAC", "DAC1 MIXL" पूर्ण,
	अणु "DAC L1 Source", "Stereo DAC Mixer", "Stereo DAC MIXL" पूर्ण,
	अणु "DAC R1 Source", शून्य, "DAC R1 Power" पूर्ण,
	अणु "DAC R1 Source", "DAC", "DAC1 MIXR" पूर्ण,
	अणु "DAC R1 Source", "Stereo DAC Mixer", "Stereo DAC MIXR" पूर्ण,
	अणु "DAC L2 Source", "Stereo DAC Mixer", "Stereo DAC MIXL" पूर्ण,
	अणु "DAC L2 Source", "Mono DAC Mixer", "Mono DAC MIXL" पूर्ण,
	अणु "DAC L2 Source", शून्य, "DAC L2 Power" पूर्ण,
	अणु "DAC R2 Source", "Stereo DAC Mixer", "Stereo DAC MIXR" पूर्ण,
	अणु "DAC R2 Source", "Mono DAC Mixer", "Mono DAC MIXR" पूर्ण,
	अणु "DAC R2 Source", शून्य, "DAC R2 Power" पूर्ण,

	अणु "DAC L1", शून्य, "DAC L1 Source" पूर्ण,
	अणु "DAC R1", शून्य, "DAC R1 Source" पूर्ण,
	अणु "DAC L2", शून्य, "DAC L2 Source" पूर्ण,
	अणु "DAC R2", शून्य, "DAC R2 Source" पूर्ण,

	अणु "SPK MIXL", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "SPK MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "SPK MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "SPK MIXL", "INR Switch", "INR VOL" पूर्ण,
	अणु "SPK MIXL", "BST3 Switch", "BST3" पूर्ण,
	अणु "SPK MIXR", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "SPK MIXR", "BST4 Switch", "BST4" पूर्ण,
	अणु "SPK MIXR", "INL Switch", "INL VOL" पूर्ण,
	अणु "SPK MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "SPK MIXR", "BST3 Switch", "BST3" पूर्ण,

	अणु "MONOVOL MIX", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "MONOVOL MIX", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "MONOVOL MIX", "BST1 Switch", "BST1" पूर्ण,
	अणु "MONOVOL MIX", "BST2 Switch", "BST2" पूर्ण,
	अणु "MONOVOL MIX", "BST3 Switch", "BST3" पूर्ण,

	अणु "OUT MIXL", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "OUT MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "OUT MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "OUT MIXL", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXL", "BST3 Switch", "BST3" पूर्ण,
	अणु "OUT MIXR", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "OUT MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "OUT MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXR", "BST3 Switch", "BST3" पूर्ण,
	अणु "OUT MIXR", "BST4 Switch", "BST4" पूर्ण,

	अणु "SPKVOL L", "Switch", "SPK MIXL" पूर्ण,
	अणु "SPKVOL R", "Switch", "SPK MIXR" पूर्ण,
	अणु "SPO L MIX", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "SPO L MIX", "SPKVOL L Switch", "SPKVOL L" पूर्ण,
	अणु "SPO R MIX", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "SPO R MIX", "SPKVOL R Switch", "SPKVOL R" पूर्ण,
	अणु "SPK Amp", शून्य, "SPO L MIX" पूर्ण,
	अणु "SPK Amp", शून्य, "SPO R MIX" पूर्ण,
	अणु "SPK Amp", शून्य, "SYS CLK DET" पूर्ण,
	अणु "SPO Playback", "Switch", "SPK Amp" पूर्ण,
	अणु "SPOL", शून्य, "SPO Playback" पूर्ण,
	अणु "SPOR", शून्य, "SPO Playback" पूर्ण,

	अणु "MONOVOL", "Switch", "MONOVOL MIX" पूर्ण,
	अणु "Mono MIX", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "Mono MIX", "MONOVOL Switch", "MONOVOL" पूर्ण,
	अणु "Mono Amp", शून्य, "Mono MIX" पूर्ण,
	अणु "Mono Amp", शून्य, "Mono Vref" पूर्ण,
	अणु "Mono Amp", शून्य, "SYS CLK DET" पूर्ण,
	अणु "Mono Playback", "Switch", "Mono Amp" पूर्ण,
	अणु "MONOOUT", शून्य, "Mono Playback" पूर्ण,

	अणु "HP Amp", शून्य, "DAC L1" पूर्ण,
	अणु "HP Amp", शून्य, "DAC R1" पूर्ण,
	अणु "HP Amp", शून्य, "Charge Pump" पूर्ण,
	अणु "HP Amp", शून्य, "SYS CLK DET" पूर्ण,
	अणु "HPO L Playback", "Switch", "HP Amp"पूर्ण,
	अणु "HPO R Playback", "Switch", "HP Amp"पूर्ण,
	अणु "HPOL", शून्य, "HPO L Playback" पूर्ण,
	अणु "HPOR", शून्य, "HPO R Playback" पूर्ण,

	अणु "OUTVOL L", "Switch", "OUT MIXL" पूर्ण,
	अणु "OUTVOL R", "Switch", "OUT MIXR" पूर्ण,
	अणु "LOUT L MIX", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "LOUT L MIX", "OUTVOL L Switch", "OUTVOL L" पूर्ण,
	अणु "LOUT R MIX", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "LOUT R MIX", "OUTVOL R Switch", "OUTVOL R" पूर्ण,
	अणु "LOUT Amp", शून्य, "LOUT L MIX" पूर्ण,
	अणु "LOUT Amp", शून्य, "LOUT R MIX" पूर्ण,
	अणु "LOUT Amp", शून्य, "Charge Pump" पूर्ण,
	अणु "LOUT Amp", शून्य, "SYS CLK DET" पूर्ण,
	अणु "LOUT L Playback", "Switch", "LOUT Amp" पूर्ण,
	अणु "LOUT R Playback", "Switch", "LOUT Amp" पूर्ण,
	अणु "LOUTL", शून्य, "LOUT L Playback" पूर्ण,
	अणु "LOUTR", शून्य, "LOUT R Playback" पूर्ण,

	अणु "PDM L Mux", "Mono DAC", "Mono DAC MIXL" पूर्ण,
	अणु "PDM L Mux", "Stereo DAC", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM L Mux", शून्य, "PDM Power" पूर्ण,
	अणु "PDM R Mux", "Mono DAC", "Mono DAC MIXR" पूर्ण,
	अणु "PDM R Mux", "Stereo DAC", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM R Mux", शून्य, "PDM Power" पूर्ण,
	अणु "PDM L Playback", "Switch", "PDM L Mux" पूर्ण,
	अणु "PDM R Playback", "Switch", "PDM R Mux" पूर्ण,
	अणु "PDML", शून्य, "PDM L Playback" पूर्ण,
	अणु "PDMR", शून्य, "PDM R Playback" पूर्ण,

	अणु "SPDIF Mux", "IF3_DAC", "IF3 DAC" पूर्ण,
	अणु "SPDIF Mux", "IF2_DAC", "IF2 DAC" पूर्ण,
	अणु "SPDIF Mux", "IF1_DAC2", "IF1 DAC2" पूर्ण,
	अणु "SPDIF Mux", "IF1_DAC1", "IF1 DAC1" पूर्ण,
	अणु "SPDIF", शून्य, "SPDIF Mux" पूर्ण,
पूर्ण;

अटल पूर्णांक rt5659_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, frame_size;

	rt5659->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5659->sysclk, rt5659->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting %d for DAI %d\n",
			rt5659->lrck[dai->id], dai->id);
		वापस -EINVAL;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt5659->lrck[dai->id], pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5659_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5659_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5659_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5659_AIF1:
		mask_clk = RT5659_I2S_PD1_MASK;
		val_clk = pre_भाग << RT5659_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S1_SDP,
			RT5659_I2S_DL_MASK, val_len);
		अवरोध;
	हाल RT5659_AIF2:
		mask_clk = RT5659_I2S_PD2_MASK;
		val_clk = pre_भाग << RT5659_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S2_SDP,
			RT5659_I2S_DL_MASK, val_len);
		अवरोध;
	हाल RT5659_AIF3:
		mask_clk = RT5659_I2S_PD3_MASK;
		val_clk = pre_भाग << RT5659_I2S_PD3_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S3_SDP,
			RT5659_I2S_DL_MASK, val_len);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1, mask_clk, val_clk);

	चयन (rt5659->lrck[dai->id]) अणु
	हाल 192000:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_32);
		अवरोध;
	हाल 96000:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_64);
		अवरोध;
	शेष:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_128);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5659->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5659_I2S_MS_S;
		rt5659->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5659_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5659_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5659_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5659_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5659_AIF1:
		snd_soc_component_update_bits(component, RT5659_I2S1_SDP,
			RT5659_I2S_MS_MASK | RT5659_I2S_BP_MASK |
			RT5659_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5659_AIF2:
		snd_soc_component_update_bits(component, RT5659_I2S2_SDP,
			RT5659_I2S_MS_MASK | RT5659_I2S_BP_MASK |
			RT5659_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5659_AIF3:
		snd_soc_component_update_bits(component, RT5659_I2S3_SDP,
			RT5659_I2S_MS_MASK | RT5659_I2S_BP_MASK |
			RT5659_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_component_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
				   पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक ret;

	अगर (freq == rt5659->sysclk && clk_id == rt5659->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5659_SCLK_S_MCLK:
		ret = clk_set_rate(rt5659->mclk, freq);
		अगर (ret)
			वापस ret;

		reg_val |= RT5659_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5659_SCLK_S_PLL1:
		reg_val |= RT5659_SCLK_SRC_PLL1;
		अवरोध;
	हाल RT5659_SCLK_S_RCCLK:
		reg_val |= RT5659_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5659_GLB_CLK,
		RT5659_SCLK_SRC_MASK, reg_val);
	rt5659->sysclk = freq;
	rt5659->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_component_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
				पूर्णांक source, अचिन्हित पूर्णांक freq_in,
				अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5659->pll_src && freq_in == rt5659->pll_in &&
	    freq_out == rt5659->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5659->pll_in = 0;
		rt5659->pll_out = 0;
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
			RT5659_SCLK_SRC_MASK, RT5659_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5659_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
			RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5659_PLL1_S_BCLK1:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK1);
		अवरोध;
	हाल RT5659_PLL1_S_BCLK2:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK2);
		अवरोध;
	हाल RT5659_PLL1_S_BCLK3:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK3);
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

	snd_soc_component_ग_लिखो(component, RT5659_PLL_CTRL_1,
		pll_code.n_code << RT5659_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5659_PLL_CTRL_2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5659_PLL_M_SFT) |
		(pll_code.m_bp << RT5659_PLL_M_BP_SFT));

	rt5659->pll_in = freq_in;
	rt5659->pll_out = freq_out;
	rt5659->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;

	अगर (rx_mask || tx_mask)
		val |= (1 << 15);

	चयन (slots) अणु
	हाल 4:
		val |= (1 << 10);
		val |= (1 << 8);
		अवरोध;
	हाल 6:
		val |= (2 << 10);
		val |= (2 << 8);
		अवरोध;
	हाल 8:
		val |= (3 << 10);
		val |= (3 << 8);
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= (1 << 6);
		val |= (1 << 4);
		अवरोध;
	हाल 24:
		val |= (2 << 6);
		val |= (2 << 4);
		अवरोध;
	हाल 32:
		val |= (3 << 6);
		val |= (3 << 4);
		अवरोध;
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5659_TDM_CTRL_1, 0x8ff0, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s ratio=%d\n", __func__, ratio);

	rt5659->bclk[dai->id] = ratio;

	अगर (ratio == 64) अणु
		चयन (dai->id) अणु
		हाल RT5659_AIF2:
			snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
				RT5659_I2S_BCLK_MS2_MASK,
				RT5659_I2S_BCLK_MS2_64);
			अवरोध;
		हाल RT5659_AIF3:
			snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
				RT5659_I2S_BCLK_MS3_MASK,
				RT5659_I2S_BCLK_MS3_64);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		regmap_update_bits(rt5659->regmap, RT5659_DIG_MISC,
			RT5659_DIG_GATE_CTRL, RT5659_DIG_GATE_CTRL);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_DIG_1,
			RT5659_PWR_LDO,	RT5659_PWR_LDO);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
			RT5659_PWR_MB | RT5659_PWR_VREF1 | RT5659_PWR_VREF2,
			RT5659_PWR_MB | RT5659_PWR_VREF1 | RT5659_PWR_VREF2);
		msleep(20);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
			RT5659_PWR_FV1 | RT5659_PWR_FV2,
			RT5659_PWR_FV1 | RT5659_PWR_FV2);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (dapm->bias_level == SND_SOC_BIAS_OFF) अणु
			ret = clk_prepare_enable(rt5659->mclk);
			अगर (ret) अणु
				dev_err(component->dev,
					"failed to enable MCLK: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(rt5659->regmap, RT5659_PWR_DIG_1,
			RT5659_PWR_LDO, 0);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
			RT5659_PWR_MB | RT5659_PWR_VREF1 | RT5659_PWR_VREF2
			| RT5659_PWR_FV1 | RT5659_PWR_FV2,
			RT5659_PWR_MB | RT5659_PWR_VREF2);
		regmap_update_bits(rt5659->regmap, RT5659_DIG_MISC,
			RT5659_DIG_GATE_CTRL, 0);
		clk_disable_unprepare(rt5659->mclk);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	rt5659->component = component;

	चयन (rt5659->pdata.jd_src) अणु
	हाल RT5659_JD_HDA_HEADER:
		अवरोध;

	शेष:
		snd_soc_dapm_new_controls(dapm,
			rt5659_particular_dapm_widमाला_लो,
			ARRAY_SIZE(rt5659_particular_dapm_widमाला_लो));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt5659_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(rt5659->regmap, RT5659_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5659_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5659->regmap, true);
	regcache_mark_dirty(rt5659->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5659_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5659->regmap, false);
	regcache_sync(rt5659->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5659_suspend शून्य
#घोषणा rt5659_resume शून्य
#पूर्ण_अगर

#घोषणा RT5659_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT5659_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5659_aअगर_dai_ops = अणु
	.hw_params = rt5659_hw_params,
	.set_fmt = rt5659_set_dai_fmt,
	.set_tdm_slot = rt5659_set_tdm_slot,
	.set_bclk_ratio = rt5659_set_bclk_ratio,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5659_dai[] = अणु
	अणु
		.name = "rt5659-aif1",
		.id = RT5659_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.ops = &rt5659_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5659-aif2",
		.id = RT5659_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.ops = &rt5659_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5659-aif3",
		.id = RT5659_AIF3,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5659_STEREO_RATES,
			.क्रमmats = RT5659_FORMATS,
		पूर्ण,
		.ops = &rt5659_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5659 = अणु
	.probe			= rt5659_probe,
	.हटाओ			= rt5659_हटाओ,
	.suspend		= rt5659_suspend,
	.resume			= rt5659_resume,
	.set_bias_level		= rt5659_set_bias_level,
	.controls		= rt5659_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5659_snd_controls),
	.dapm_widमाला_लो		= rt5659_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5659_dapm_widमाला_लो),
	.dapm_routes		= rt5659_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5659_dapm_routes),
	.set_sysclk		= rt5659_set_component_sysclk,
	.set_pll		= rt5659_set_component_pll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;


अटल स्थिर काष्ठा regmap_config rt5659_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = 0x0400,
	.अस्थिर_reg = rt5659_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5659_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5659_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5659_reg),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5659_i2c_id[] = अणु
	अणु "rt5658", 0 पूर्ण,
	अणु "rt5659", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5659_i2c_id);

अटल पूर्णांक rt5659_parse_dt(काष्ठा rt5659_priv *rt5659, काष्ठा device *dev)
अणु
	rt5659->pdata.in1_dअगरf = device_property_पढ़ो_bool(dev,
					"realtek,in1-differential");
	rt5659->pdata.in3_dअगरf = device_property_पढ़ो_bool(dev,
					"realtek,in3-differential");
	rt5659->pdata.in4_dअगरf = device_property_पढ़ो_bool(dev,
					"realtek,in4-differential");


	device_property_पढ़ो_u32(dev, "realtek,dmic1-data-pin",
		&rt5659->pdata.dmic1_data_pin);
	device_property_पढ़ो_u32(dev, "realtek,dmic2-data-pin",
		&rt5659->pdata.dmic2_data_pin);
	device_property_पढ़ो_u32(dev, "realtek,jd-src",
		&rt5659->pdata.jd_src);

	वापस 0;
पूर्ण

अटल व्योम rt5659_calibrate(काष्ठा rt5659_priv *rt5659)
अणु
	पूर्णांक value, count;

	/* Calibrate HPO Start */
	/* Fine tune HP Perक्रमmance */
	regmap_ग_लिखो(rt5659->regmap, RT5659_BIAS_CUR_CTRL_8, 0xa502);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CHOP_DAC, 0x3030);

	regmap_ग_लिखो(rt5659->regmap, RT5659_PRE_DIV_1, 0xef00);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PRE_DIV_2, 0xeffc);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MICBIAS_2, 0x0280);
	regmap_ग_लिखो(rt5659->regmap, RT5659_DIG_MISC, 0x0001);
	regmap_ग_लिखो(rt5659->regmap, RT5659_GLB_CLK, 0x8000);

	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_1, 0xaa7e);
	msleep(60);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_1, 0xfe7e);
	msleep(50);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0004);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_DIG_2, 0x0400);
	msleep(50);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_DIG_1, 0x0080);
	usleep_range(10000, 10005);
	regmap_ग_लिखो(rt5659->regmap, RT5659_DEPOP_1, 0x0009);
	msleep(50);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_DIG_1, 0x0f80);
	msleep(50);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CHARGE_PUMP_1, 0x0e16);
	msleep(50);

	/* Enalbe K ADC Power And Clock */
	regmap_ग_लिखो(rt5659->regmap, RT5659_CAL_REC, 0x0505);
	msleep(50);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0184);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CALIB_ADC_CTRL, 0x3c05);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c1);

	/* K Headphone */
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x5100);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0014);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0xd100);
	msleep(60);

	/* Manual K ADC Offset */
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x4900);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0016);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, &value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 30) अणु
			dev_err(rt5659->component->dev,
				"HP Calibration 1 Failure\n");
			वापस;
		पूर्ण

		count++;
	पूर्ण

	/* Manual K Internal Path Offset */
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_VOL, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x4500);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x001f);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, &value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 85) अणु
			dev_err(rt5659->component->dev,
				"HP Calibration 2 Failure\n");
			वापस;
		पूर्ण

		count++;
	पूर्ण

	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c0);
	/* Calibrate HPO End */

	/* Calibrate SPO Start */
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_0, 0x2021);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_CTRL_1, 0x0260);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_MIXER, 0x3000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_VOL, 0xc000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_A_DAC_MUX, 0x000c);
	regmap_ग_लिखो(rt5659->regmap, RT5659_DIG_MISC, 0x8000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPO_VOL, 0x0808);
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_L_MIXER, 0x001e);
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_R_MIXER, 0x001e);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_1, 0x0803);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_2, 0x0554);
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPO_AMP_GAIN, 0x1103);

	/* Enalbe K ADC Power And Clock */
	regmap_ग_लिखो(rt5659->regmap, RT5659_CAL_REC, 0x0909);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x0001,
		0x0001);

	/* Start Calibration */
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_0, 0x0021);
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_1, 0x3e80);
	regmap_update_bits(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5659->regmap,
				RT5659_SPK_DC_CAILB_CTRL_1, &value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 10) अणु
			dev_err(rt5659->component->dev,
				"SPK Calibration Failure\n");
			वापस;
		पूर्ण

		count++;
	पूर्ण
	/* Calibrate SPO End */

	/* Calibrate MONO Start */
	regmap_ग_लिखो(rt5659->regmap, RT5659_DIG_MISC, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONOMIX_IN_GAIN, 0x021f);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_OUT, 0x480a);
	/* MONO NG2 GAIN 5dB */
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_GAIN, 0x0003);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_NG2_CTRL_5, 0x0009);

	/* Start Calibration */
	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x000f);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e00);
	regmap_update_bits(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	जबतक (true) अणु
		regmap_पढ़ो(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1,
			&value);
		अगर (value & 0x8000)
			usleep_range(10000, 10005);
		अन्यथा
			अवरोध;

		अगर (count > 35) अणु
			dev_err(rt5659->component->dev,
				"Mono Calibration Failure\n");
			वापस;
		पूर्ण

		count++;
	पूर्ण

	regmap_ग_लिखो(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x0003);
	/* Calibrate MONO End */

	/* Power Off */
	regmap_ग_लिखो(rt5659->regmap, RT5659_CAL_REC, 0x0808);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CALIB_ADC_CTRL, 0x2005);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c0);
	regmap_ग_लिखो(rt5659->regmap, RT5659_DEPOP_1, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_1, 0x0011);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_2, 0x0150);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_1, 0xfe3e);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_OUT, 0xc80a);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e04);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_MIXER, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_VOL, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_DIG_1, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_DIG_2, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_1, 0x003e);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_CTRL_1, 0x0060);
	regmap_ग_लिखो(rt5659->regmap, RT5659_CLASSD_0, 0x2021);
	regmap_ग_लिखो(rt5659->regmap, RT5659_GLB_CLK, 0x0000);
	regmap_ग_लिखो(rt5659->regmap, RT5659_MICBIAS_2, 0x0080);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_VOL, 0x8080);
	regmap_ग_लिखो(rt5659->regmap, RT5659_HP_CHARGE_PUMP_1, 0x0c16);
पूर्ण

अटल व्योम rt5659_पूर्णांकel_hd_header_probe_setup(काष्ठा rt5659_priv *rt5659)
अणु
	पूर्णांक value;

	regmap_पढ़ो(rt5659->regmap, RT5659_GPIO_STA, &value);
	अगर (!(value & 0x8)) अणु
		rt5659->hda_hp_plugged = true;
		regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_1,
			0x10, 0x0);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_1,
			0x10, 0x10);
	पूर्ण

	regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
		RT5659_PWR_VREF2 | RT5659_PWR_MB,
		RT5659_PWR_VREF2 | RT5659_PWR_MB);
	msleep(20);
	regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
		RT5659_PWR_FV2, RT5659_PWR_FV2);

	regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_3, RT5659_PWR_LDO2,
		RT5659_PWR_LDO2);
	regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_2, RT5659_PWR_MB1,
		RT5659_PWR_MB1);
	regmap_update_bits(rt5659->regmap, RT5659_PWR_VOL, RT5659_PWR_MIC_DET,
		RT5659_PWR_MIC_DET);
	msleep(20);

	regmap_update_bits(rt5659->regmap, RT5659_4BTN_IL_CMD_2,
		RT5659_4BTN_IL_MASK, RT5659_4BTN_IL_EN);
	regmap_पढ़ो(rt5659->regmap, RT5659_4BTN_IL_CMD_1, &value);
	regmap_ग_लिखो(rt5659->regmap, RT5659_4BTN_IL_CMD_1, value);
	regmap_पढ़ो(rt5659->regmap, RT5659_4BTN_IL_CMD_1, &value);

	अगर (value & 0x2000) अणु
		rt5659->hda_mic_plugged = true;
		regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_2,
			0x2, 0x2);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_2,
			0x2, 0x0);
	पूर्ण

	regmap_update_bits(rt5659->regmap, RT5659_IRQ_CTRL_2,
		RT5659_IL_IRQ_MASK, RT5659_IL_IRQ_EN);
पूर्ण

अटल पूर्णांक rt5659_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5659_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt5659_priv *rt5659;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt5659 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5659_priv),
		GFP_KERNEL);

	अगर (rt5659 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5659);

	अगर (pdata)
		rt5659->pdata = *pdata;
	अन्यथा
		rt5659_parse_dt(rt5659, &i2c->dev);

	rt5659->gpiod_lकरो1_en = devm_gpiod_get_optional(&i2c->dev, "ldo1-en",
							GPIOD_OUT_HIGH);
	अगर (IS_ERR(rt5659->gpiod_lकरो1_en))
		dev_warn(&i2c->dev, "Request ldo1-en GPIO failed\n");

	rt5659->gpiod_reset = devm_gpiod_get_optional(&i2c->dev, "reset",
							GPIOD_OUT_HIGH);

	/* Sleep क्रम 300 ms miniumum */
	msleep(300);

	rt5659->regmap = devm_regmap_init_i2c(i2c, &rt5659_regmap);
	अगर (IS_ERR(rt5659->regmap)) अणु
		ret = PTR_ERR(rt5659->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5659->regmap, RT5659_DEVICE_ID, &val);
	अगर (val != DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt5659\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5659->regmap, RT5659_RESET, 0);

	/* Check अगर MCLK provided */
	rt5659->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (IS_ERR(rt5659->mclk)) अणु
		अगर (PTR_ERR(rt5659->mclk) != -ENOENT)
			वापस PTR_ERR(rt5659->mclk);
		/* Otherwise mark the mclk poपूर्णांकer to शून्य */
		rt5659->mclk = शून्य;
	पूर्ण

	rt5659_calibrate(rt5659);

	/* line in dअगरf mode*/
	अगर (rt5659->pdata.in1_dअगरf)
		regmap_update_bits(rt5659->regmap, RT5659_IN1_IN2,
			RT5659_IN1_DF_MASK, RT5659_IN1_DF_MASK);
	अगर (rt5659->pdata.in3_dअगरf)
		regmap_update_bits(rt5659->regmap, RT5659_IN3_IN4,
			RT5659_IN3_DF_MASK, RT5659_IN3_DF_MASK);
	अगर (rt5659->pdata.in4_dअगरf)
		regmap_update_bits(rt5659->regmap, RT5659_IN3_IN4,
			RT5659_IN4_DF_MASK, RT5659_IN4_DF_MASK);

	/* DMIC pin*/
	अगर (rt5659->pdata.dmic1_data_pin != RT5659_DMIC1_शून्य ||
		rt5659->pdata.dmic2_data_pin != RT5659_DMIC2_शून्य) अणु
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
			RT5659_GP2_PIN_MASK, RT5659_GP2_PIN_DMIC1_SCL);

		चयन (rt5659->pdata.dmic1_data_pin) अणु
		हाल RT5659_DMIC1_DATA_IN2N:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_IN2N);
			अवरोध;

		हाल RT5659_DMIC1_DATA_GPIO5:
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_3,
				RT5659_I2S2_PIN_MASK,
				RT5659_I2S2_PIN_GPIO);
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO5);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP5_PIN_MASK, RT5659_GP5_PIN_DMIC1_SDA);
			अवरोध;

		हाल RT5659_DMIC1_DATA_GPIO9:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO9);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP9_PIN_MASK, RT5659_GP9_PIN_DMIC1_SDA);
			अवरोध;

		हाल RT5659_DMIC1_DATA_GPIO11:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO11);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP11_PIN_MASK,
				RT5659_GP11_PIN_DMIC1_SDA);
			अवरोध;

		शेष:
			dev_dbg(&i2c->dev, "no DMIC1\n");
			अवरोध;
		पूर्ण

		चयन (rt5659->pdata.dmic2_data_pin) अणु
		हाल RT5659_DMIC2_DATA_IN2P:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_IN2P);
			अवरोध;

		हाल RT5659_DMIC2_DATA_GPIO6:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO6);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP6_PIN_MASK,
				RT5659_GP6_PIN_DMIC2_SDA);
			अवरोध;

		हाल RT5659_DMIC2_DATA_GPIO10:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO10);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP10_PIN_MASK,
				RT5659_GP10_PIN_DMIC2_SDA);
			अवरोध;

		हाल RT5659_DMIC2_DATA_GPIO12:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO12);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP12_PIN_MASK,
				RT5659_GP12_PIN_DMIC2_SDA);
			अवरोध;

		शेष:
			dev_dbg(&i2c->dev, "no DMIC2\n");
			अवरोध;

		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
			RT5659_GP2_PIN_MASK | RT5659_GP5_PIN_MASK |
			RT5659_GP9_PIN_MASK | RT5659_GP11_PIN_MASK |
			RT5659_GP6_PIN_MASK | RT5659_GP10_PIN_MASK |
			RT5659_GP12_PIN_MASK,
			RT5659_GP2_PIN_GPIO2 | RT5659_GP5_PIN_GPIO5 |
			RT5659_GP9_PIN_GPIO9 | RT5659_GP11_PIN_GPIO11 |
			RT5659_GP6_PIN_GPIO6 | RT5659_GP10_PIN_GPIO10 |
			RT5659_GP12_PIN_GPIO12);
		regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
			RT5659_DMIC_1_DP_MASK | RT5659_DMIC_2_DP_MASK,
			RT5659_DMIC_1_DP_IN2N | RT5659_DMIC_2_DP_IN2P);
	पूर्ण

	चयन (rt5659->pdata.jd_src) अणु
	हाल RT5659_JD3:
		regmap_ग_लिखो(rt5659->regmap, RT5659_EJD_CTRL_1, 0xa880);
		regmap_ग_लिखो(rt5659->regmap, RT5659_RC_CLK_CTRL, 0x9000);
		regmap_ग_लिखो(rt5659->regmap, RT5659_GPIO_CTRL_1, 0xc800);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
				RT5659_PWR_MB, RT5659_PWR_MB);
		regmap_ग_लिखो(rt5659->regmap, RT5659_PWR_ANLG_2, 0x0001);
		regmap_ग_लिखो(rt5659->regmap, RT5659_IRQ_CTRL_2, 0x0040);
		INIT_DELAYED_WORK(&rt5659->jack_detect_work,
			rt5659_jack_detect_work);
		अवरोध;
	हाल RT5659_JD_HDA_HEADER:
		regmap_ग_लिखो(rt5659->regmap, RT5659_GPIO_CTRL_3, 0x8000);
		regmap_ग_लिखो(rt5659->regmap, RT5659_RC_CLK_CTRL, 0x0900);
		regmap_ग_लिखो(rt5659->regmap, RT5659_EJD_CTRL_1,  0x70c0);
		regmap_ग_लिखो(rt5659->regmap, RT5659_JD_CTRL_1,   0x2000);
		regmap_ग_लिखो(rt5659->regmap, RT5659_IRQ_CTRL_1,  0x0040);
		INIT_DELAYED_WORK(&rt5659->jack_detect_work,
			rt5659_jack_detect_पूर्णांकel_hd_header);
		rt5659_पूर्णांकel_hd_header_probe_setup(rt5659);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (i2c->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
			rt5659_irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5659", rt5659);
		अगर (ret)
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);

		/* Enable IRQ output क्रम GPIO1 pin any way */
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				   RT5659_GP1_PIN_MASK, RT5659_GP1_PIN_IRQ);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt5659,
			rt5659_dai, ARRAY_SIZE(rt5659_dai));
पूर्ण

अटल व्योम rt5659_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5659_priv *rt5659 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt5659->regmap, RT5659_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt5659_of_match[] = अणु
	अणु .compatible = "realtek,rt5658", पूर्ण,
	अणु .compatible = "realtek,rt5659", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5659_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5659_acpi_match[] = अणु
	अणु "10EC5658", 0, पूर्ण,
	अणु "10EC5659", 0, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5659_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver rt5659_i2c_driver = अणु
	.driver = अणु
		.name = "rt5659",
		.of_match_table = of_match_ptr(rt5659_of_match),
		.acpi_match_table = ACPI_PTR(rt5659_acpi_match),
	पूर्ण,
	.probe = rt5659_i2c_probe,
	.shutकरोwn = rt5659_i2c_shutकरोwn,
	.id_table = rt5659_i2c_id,
पूर्ण;
module_i2c_driver(rt5659_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5659 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
