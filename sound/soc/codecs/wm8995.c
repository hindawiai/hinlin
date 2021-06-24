<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8995.c  --  WM8995 ALSA SoC Audio driver
 *
 * Copyright 2010 Wolfson Microelectronics plc
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 *
 * Based on wm8994.c and wm_hubs.c by Mark Brown
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8995.h"

#घोषणा WM8995_NUM_SUPPLIES 8
अटल स्थिर अक्षर *wm8995_supply_names[WM8995_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD1",
	"DBVDD2",
	"DBVDD3",
	"AVDD1",
	"AVDD2",
	"CPVDD",
	"MICVDD"
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8995_reg_शेषs[] = अणु
	अणु 0, 0x8995 पूर्ण,
	अणु 5, 0x0100 पूर्ण,
	अणु 16, 0x000b पूर्ण,
	अणु 17, 0x000b पूर्ण,
	अणु 24, 0x02c0 पूर्ण,
	अणु 25, 0x02c0 पूर्ण,
	अणु 26, 0x02c0 पूर्ण,
	अणु 27, 0x02c0 पूर्ण,
	अणु 28, 0x000f पूर्ण,
	अणु 32, 0x0005 पूर्ण,
	अणु 33, 0x0005 पूर्ण,
	अणु 40, 0x0003 पूर्ण,
	अणु 41, 0x0013 पूर्ण,
	अणु 48, 0x0004 पूर्ण,
	अणु 56, 0x09f8 पूर्ण,
	अणु 64, 0x1f25 पूर्ण,
	अणु 69, 0x0004 पूर्ण,
	अणु 82, 0xaaaa पूर्ण,
	अणु 84, 0x2a2a पूर्ण,
	अणु 146, 0x0060 पूर्ण,
	अणु 256, 0x0002 पूर्ण,
	अणु 257, 0x8004 पूर्ण,
	अणु 520, 0x0010 पूर्ण,
	अणु 528, 0x0083 पूर्ण,
	अणु 529, 0x0083 पूर्ण,
	अणु 548, 0x0c80 पूर्ण,
	अणु 580, 0x0c80 पूर्ण,
	अणु 768, 0x4050 पूर्ण,
	अणु 769, 0x4000 पूर्ण,
	अणु 771, 0x0040 पूर्ण,
	अणु 772, 0x0040 पूर्ण,
	अणु 773, 0x0040 पूर्ण,
	अणु 774, 0x0004 पूर्ण,
	अणु 775, 0x0100 पूर्ण,
	अणु 784, 0x4050 पूर्ण,
	अणु 785, 0x4000 पूर्ण,
	अणु 787, 0x0040 पूर्ण,
	अणु 788, 0x0040 पूर्ण,
	अणु 789, 0x0040 पूर्ण,
	अणु 1024, 0x00c0 पूर्ण,
	अणु 1025, 0x00c0 पूर्ण,
	अणु 1026, 0x00c0 पूर्ण,
	अणु 1027, 0x00c0 पूर्ण,
	अणु 1028, 0x00c0 पूर्ण,
	अणु 1029, 0x00c0 पूर्ण,
	अणु 1030, 0x00c0 पूर्ण,
	अणु 1031, 0x00c0 पूर्ण,
	अणु 1056, 0x0200 पूर्ण,
	अणु 1057, 0x0010 पूर्ण,
	अणु 1058, 0x0200 पूर्ण,
	अणु 1059, 0x0010 पूर्ण,
	अणु 1088, 0x0098 पूर्ण,
	अणु 1089, 0x0845 पूर्ण,
	अणु 1104, 0x0098 पूर्ण,
	अणु 1105, 0x0845 पूर्ण,
	अणु 1152, 0x6318 पूर्ण,
	अणु 1153, 0x6300 पूर्ण,
	अणु 1154, 0x0fca पूर्ण,
	अणु 1155, 0x0400 पूर्ण,
	अणु 1156, 0x00d8 पूर्ण,
	अणु 1157, 0x1eb5 पूर्ण,
	अणु 1158, 0xf145 पूर्ण,
	अणु 1159, 0x0b75 पूर्ण,
	अणु 1160, 0x01c5 पूर्ण,
	अणु 1161, 0x1c58 पूर्ण,
	अणु 1162, 0xf373 पूर्ण,
	अणु 1163, 0x0a54 पूर्ण,
	अणु 1164, 0x0558 पूर्ण,
	अणु 1165, 0x168e पूर्ण,
	अणु 1166, 0xf829 पूर्ण,
	अणु 1167, 0x07ad पूर्ण,
	अणु 1168, 0x1103 पूर्ण,
	अणु 1169, 0x0564 पूर्ण,
	अणु 1170, 0x0559 पूर्ण,
	अणु 1171, 0x4000 पूर्ण,
	अणु 1184, 0x6318 पूर्ण,
	अणु 1185, 0x6300 पूर्ण,
	अणु 1186, 0x0fca पूर्ण,
	अणु 1187, 0x0400 पूर्ण,
	अणु 1188, 0x00d8 पूर्ण,
	अणु 1189, 0x1eb5 पूर्ण,
	अणु 1190, 0xf145 पूर्ण,
	अणु 1191, 0x0b75 पूर्ण,
	अणु 1192, 0x01c5 पूर्ण,
	अणु 1193, 0x1c58 पूर्ण,
	अणु 1194, 0xf373 पूर्ण,
	अणु 1195, 0x0a54 पूर्ण,
	अणु 1196, 0x0558 पूर्ण,
	अणु 1197, 0x168e पूर्ण,
	अणु 1198, 0xf829 पूर्ण,
	अणु 1199, 0x07ad पूर्ण,
	अणु 1200, 0x1103 पूर्ण,
	अणु 1201, 0x0564 पूर्ण,
	अणु 1202, 0x0559 पूर्ण,
	अणु 1203, 0x4000 पूर्ण,
	अणु 1280, 0x00c0 पूर्ण,
	अणु 1281, 0x00c0 पूर्ण,
	अणु 1282, 0x00c0 पूर्ण,
	अणु 1283, 0x00c0 पूर्ण,
	अणु 1312, 0x0200 पूर्ण,
	अणु 1313, 0x0010 पूर्ण,
	अणु 1344, 0x0098 पूर्ण,
	अणु 1345, 0x0845 पूर्ण,
	अणु 1408, 0x6318 पूर्ण,
	अणु 1409, 0x6300 पूर्ण,
	अणु 1410, 0x0fca पूर्ण,
	अणु 1411, 0x0400 पूर्ण,
	अणु 1412, 0x00d8 पूर्ण,
	अणु 1413, 0x1eb5 पूर्ण,
	अणु 1414, 0xf145 पूर्ण,
	अणु 1415, 0x0b75 पूर्ण,
	अणु 1416, 0x01c5 पूर्ण,
	अणु 1417, 0x1c58 पूर्ण,
	अणु 1418, 0xf373 पूर्ण,
	अणु 1419, 0x0a54 पूर्ण,
	अणु 1420, 0x0558 पूर्ण,
	अणु 1421, 0x168e पूर्ण,
	अणु 1422, 0xf829 पूर्ण,
	अणु 1423, 0x07ad पूर्ण,
	अणु 1424, 0x1103 पूर्ण,
	अणु 1425, 0x0564 पूर्ण,
	अणु 1426, 0x0559 पूर्ण,
	अणु 1427, 0x4000 पूर्ण,
	अणु 1568, 0x0002 पूर्ण,
	अणु 1792, 0xa100 पूर्ण,
	अणु 1793, 0xa101 पूर्ण,
	अणु 1794, 0xa101 पूर्ण,
	अणु 1795, 0xa101 पूर्ण,
	अणु 1796, 0xa101 पूर्ण,
	अणु 1797, 0xa101 पूर्ण,
	अणु 1798, 0xa101 पूर्ण,
	अणु 1799, 0xa101 पूर्ण,
	अणु 1800, 0xa101 पूर्ण,
	अणु 1801, 0xa101 पूर्ण,
	अणु 1802, 0xa101 पूर्ण,
	अणु 1803, 0xa101 पूर्ण,
	अणु 1804, 0xa101 पूर्ण,
	अणु 1805, 0xa101 पूर्ण,
	अणु 1825, 0x0055 पूर्ण,
	अणु 1848, 0x3fff पूर्ण,
	अणु 1849, 0x1fff पूर्ण,
	अणु 2049, 0x0001 पूर्ण,
	अणु 2050, 0x0069 पूर्ण,
	अणु 2056, 0x0002 पूर्ण,
	अणु 2057, 0x0003 पूर्ण,
	अणु 2058, 0x0069 पूर्ण,
	अणु 12288, 0x0001 पूर्ण,
	अणु 12289, 0x0001 पूर्ण,
	अणु 12291, 0x0006 पूर्ण,
	अणु 12292, 0x0040 पूर्ण,
	अणु 12293, 0x0001 पूर्ण,
	अणु 12294, 0x000f पूर्ण,
	अणु 12295, 0x0006 पूर्ण,
	अणु 12296, 0x0001 पूर्ण,
	अणु 12297, 0x0003 पूर्ण,
	अणु 12298, 0x0104 पूर्ण,
	अणु 12300, 0x0060 पूर्ण,
	अणु 12301, 0x0011 पूर्ण,
	अणु 12302, 0x0401 पूर्ण,
	अणु 12304, 0x0050 पूर्ण,
	अणु 12305, 0x0003 पूर्ण,
	अणु 12306, 0x0100 पूर्ण,
	अणु 12308, 0x0051 पूर्ण,
	अणु 12309, 0x0003 पूर्ण,
	अणु 12310, 0x0104 पूर्ण,
	अणु 12311, 0x000a पूर्ण,
	अणु 12312, 0x0060 पूर्ण,
	अणु 12313, 0x003b पूर्ण,
	अणु 12314, 0x0502 पूर्ण,
	अणु 12315, 0x0100 पूर्ण,
	अणु 12316, 0x2fff पूर्ण,
	अणु 12320, 0x2fff पूर्ण,
	अणु 12324, 0x2fff पूर्ण,
	अणु 12328, 0x2fff पूर्ण,
	अणु 12332, 0x2fff पूर्ण,
	अणु 12336, 0x2fff पूर्ण,
	अणु 12340, 0x2fff पूर्ण,
	अणु 12344, 0x2fff पूर्ण,
	अणु 12348, 0x2fff पूर्ण,
	अणु 12352, 0x0001 पूर्ण,
	अणु 12353, 0x0001 पूर्ण,
	अणु 12355, 0x0006 पूर्ण,
	अणु 12356, 0x0040 पूर्ण,
	अणु 12357, 0x0001 पूर्ण,
	अणु 12358, 0x000f पूर्ण,
	अणु 12359, 0x0006 पूर्ण,
	अणु 12360, 0x0001 पूर्ण,
	अणु 12361, 0x0003 पूर्ण,
	अणु 12362, 0x0104 पूर्ण,
	अणु 12364, 0x0060 पूर्ण,
	अणु 12365, 0x0011 पूर्ण,
	अणु 12366, 0x0401 पूर्ण,
	अणु 12368, 0x0050 पूर्ण,
	अणु 12369, 0x0003 पूर्ण,
	अणु 12370, 0x0100 पूर्ण,
	अणु 12372, 0x0060 पूर्ण,
	अणु 12373, 0x003b पूर्ण,
	अणु 12374, 0x0502 पूर्ण,
	अणु 12375, 0x0100 पूर्ण,
	अणु 12376, 0x2fff पूर्ण,
	अणु 12380, 0x2fff पूर्ण,
	अणु 12384, 0x2fff पूर्ण,
	अणु 12388, 0x2fff पूर्ण,
	अणु 12392, 0x2fff पूर्ण,
	अणु 12396, 0x2fff पूर्ण,
	अणु 12400, 0x2fff पूर्ण,
	अणु 12404, 0x2fff पूर्ण,
	अणु 12408, 0x2fff पूर्ण,
	अणु 12412, 0x2fff पूर्ण,
	अणु 12416, 0x0001 पूर्ण,
	अणु 12417, 0x0001 पूर्ण,
	अणु 12419, 0x0006 पूर्ण,
	अणु 12420, 0x0040 पूर्ण,
	अणु 12421, 0x0001 पूर्ण,
	अणु 12422, 0x000f पूर्ण,
	अणु 12423, 0x0006 पूर्ण,
	अणु 12424, 0x0001 पूर्ण,
	अणु 12425, 0x0003 पूर्ण,
	अणु 12426, 0x0106 पूर्ण,
	अणु 12428, 0x0061 पूर्ण,
	अणु 12429, 0x0011 पूर्ण,
	अणु 12430, 0x0401 पूर्ण,
	अणु 12432, 0x0050 पूर्ण,
	अणु 12433, 0x0003 पूर्ण,
	अणु 12434, 0x0102 पूर्ण,
	अणु 12436, 0x0051 पूर्ण,
	अणु 12437, 0x0003 पूर्ण,
	अणु 12438, 0x0106 पूर्ण,
	अणु 12439, 0x000a पूर्ण,
	अणु 12440, 0x0061 पूर्ण,
	अणु 12441, 0x003b पूर्ण,
	अणु 12442, 0x0502 पूर्ण,
	अणु 12443, 0x0100 पूर्ण,
	अणु 12444, 0x2fff पूर्ण,
	अणु 12448, 0x2fff पूर्ण,
	अणु 12452, 0x2fff पूर्ण,
	अणु 12456, 0x2fff पूर्ण,
	अणु 12460, 0x2fff पूर्ण,
	अणु 12464, 0x2fff पूर्ण,
	अणु 12468, 0x2fff पूर्ण,
	अणु 12472, 0x2fff पूर्ण,
	अणु 12476, 0x2fff पूर्ण,
	अणु 12480, 0x0001 पूर्ण,
	अणु 12481, 0x0001 पूर्ण,
	अणु 12483, 0x0006 पूर्ण,
	अणु 12484, 0x0040 पूर्ण,
	अणु 12485, 0x0001 पूर्ण,
	अणु 12486, 0x000f पूर्ण,
	अणु 12487, 0x0006 पूर्ण,
	अणु 12488, 0x0001 पूर्ण,
	अणु 12489, 0x0003 पूर्ण,
	अणु 12490, 0x0106 पूर्ण,
	अणु 12492, 0x0061 पूर्ण,
	अणु 12493, 0x0011 पूर्ण,
	अणु 12494, 0x0401 पूर्ण,
	अणु 12496, 0x0050 पूर्ण,
	अणु 12497, 0x0003 पूर्ण,
	अणु 12498, 0x0102 पूर्ण,
	अणु 12500, 0x0061 पूर्ण,
	अणु 12501, 0x003b पूर्ण,
	अणु 12502, 0x0502 पूर्ण,
	अणु 12503, 0x0100 पूर्ण,
	अणु 12504, 0x2fff पूर्ण,
	अणु 12508, 0x2fff पूर्ण,
	अणु 12512, 0x2fff पूर्ण,
	अणु 12516, 0x2fff पूर्ण,
	अणु 12520, 0x2fff पूर्ण,
	अणु 12524, 0x2fff पूर्ण,
	अणु 12528, 0x2fff पूर्ण,
	अणु 12532, 0x2fff पूर्ण,
	अणु 12536, 0x2fff पूर्ण,
	अणु 12540, 0x2fff पूर्ण,
	अणु 12544, 0x0060 पूर्ण,
	अणु 12546, 0x0601 पूर्ण,
	अणु 12548, 0x0050 पूर्ण,
	अणु 12550, 0x0100 पूर्ण,
	अणु 12552, 0x0001 पूर्ण,
	अणु 12554, 0x0104 पूर्ण,
	अणु 12555, 0x0100 पूर्ण,
	अणु 12556, 0x2fff पूर्ण,
	अणु 12560, 0x2fff पूर्ण,
	अणु 12564, 0x2fff पूर्ण,
	अणु 12568, 0x2fff पूर्ण,
	अणु 12572, 0x2fff पूर्ण,
	अणु 12576, 0x2fff पूर्ण,
	अणु 12580, 0x2fff पूर्ण,
	अणु 12584, 0x2fff पूर्ण,
	अणु 12588, 0x2fff पूर्ण,
	अणु 12592, 0x2fff पूर्ण,
	अणु 12596, 0x2fff पूर्ण,
	अणु 12600, 0x2fff पूर्ण,
	अणु 12604, 0x2fff पूर्ण,
	अणु 12608, 0x0061 पूर्ण,
	अणु 12610, 0x0601 पूर्ण,
	अणु 12612, 0x0050 पूर्ण,
	अणु 12614, 0x0102 पूर्ण,
	अणु 12616, 0x0001 पूर्ण,
	अणु 12618, 0x0106 पूर्ण,
	अणु 12619, 0x0100 पूर्ण,
	अणु 12620, 0x2fff पूर्ण,
	अणु 12624, 0x2fff पूर्ण,
	अणु 12628, 0x2fff पूर्ण,
	अणु 12632, 0x2fff पूर्ण,
	अणु 12636, 0x2fff पूर्ण,
	अणु 12640, 0x2fff पूर्ण,
	अणु 12644, 0x2fff पूर्ण,
	अणु 12648, 0x2fff पूर्ण,
	अणु 12652, 0x2fff पूर्ण,
	अणु 12656, 0x2fff पूर्ण,
	अणु 12660, 0x2fff पूर्ण,
	अणु 12664, 0x2fff पूर्ण,
	अणु 12668, 0x2fff पूर्ण,
	अणु 12672, 0x0060 पूर्ण,
	अणु 12674, 0x0601 पूर्ण,
	अणु 12676, 0x0061 पूर्ण,
	अणु 12678, 0x0601 पूर्ण,
	अणु 12680, 0x0050 पूर्ण,
	अणु 12682, 0x0300 पूर्ण,
	अणु 12684, 0x0001 पूर्ण,
	अणु 12686, 0x0304 पूर्ण,
	अणु 12688, 0x0040 पूर्ण,
	अणु 12690, 0x000f पूर्ण,
	अणु 12692, 0x0001 पूर्ण,
	अणु 12695, 0x0100 पूर्ण,
पूर्ण;

काष्ठा fll_config अणु
	पूर्णांक src;
	पूर्णांक in;
	पूर्णांक out;
पूर्ण;

काष्ठा wm8995_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक sysclk[2];
	पूर्णांक mclk[2];
	पूर्णांक aअगरclk[2];
	काष्ठा fll_config fll[2], fll_suspend[2];
	काष्ठा regulator_bulk_data supplies[WM8995_NUM_SUPPLIES];
	काष्ठा notअगरier_block disable_nb[WM8995_NUM_SUPPLIES];
	काष्ठा snd_soc_component *component;
पूर्ण;

/*
 * We can't use the same notअगरier block क्रम more than one supply and
 * there's no way I can see to get from a callback to the caller
 * except container_of().
 */
#घोषणा WM8995_REGULATOR_EVENT(n) \
अटल पूर्णांक wm8995_regulator_event_##n(काष्ठा notअगरier_block *nb, \
				      अचिन्हित दीर्घ event, व्योम *data)    \
अणु \
	काष्ठा wm8995_priv *wm8995 = container_of(nb, काष्ठा wm8995_priv, \
				     disable_nb[n]); \
	अगर (event & REGULATOR_EVENT_DISABLE) अणु \
		regcache_mark_dirty(wm8995->regmap);	\
	पूर्ण \
	वापस 0; \
पूर्ण

WM8995_REGULATOR_EVENT(0)
WM8995_REGULATOR_EVENT(1)
WM8995_REGULATOR_EVENT(2)
WM8995_REGULATOR_EVENT(3)
WM8995_REGULATOR_EVENT(4)
WM8995_REGULATOR_EVENT(5)
WM8995_REGULATOR_EVENT(6)
WM8995_REGULATOR_EVENT(7)

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(in1lr_pga_tlv, -1650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in1l_boost_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -3600, 150, 0);

अटल स्थिर अक्षर *in1l_text[] = अणु
	"Differential", "Single-ended IN1LN", "Single-ended IN1LP"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(in1l_क्रमागत, WM8995_LEFT_LINE_INPUT_CONTROL,
			    2, in1l_text);

अटल स्थिर अक्षर *in1r_text[] = अणु
	"Differential", "Single-ended IN1RN", "Single-ended IN1RP"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(in1r_क्रमागत, WM8995_LEFT_LINE_INPUT_CONTROL,
			    0, in1r_text);

अटल स्थिर अक्षर *dmic_src_text[] = अणु
	"DMICDAT1", "DMICDAT2", "DMICDAT3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dmic_src1_क्रमागत, WM8995_POWER_MANAGEMENT_5,
			    8, dmic_src_text);
अटल SOC_ENUM_SINGLE_DECL(dmic_src2_क्रमागत, WM8995_POWER_MANAGEMENT_5,
			    6, dmic_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8995_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC1 Volume", WM8995_DAC1_LEFT_VOLUME,
		WM8995_DAC1_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R("DAC1 Switch", WM8995_DAC1_LEFT_VOLUME,
		WM8995_DAC1_RIGHT_VOLUME, 9, 1, 1),

	SOC_DOUBLE_R_TLV("DAC2 Volume", WM8995_DAC2_LEFT_VOLUME,
		WM8995_DAC2_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R("DAC2 Switch", WM8995_DAC2_LEFT_VOLUME,
		WM8995_DAC2_RIGHT_VOLUME, 9, 1, 1),

	SOC_DOUBLE_R_TLV("AIF1DAC1 Volume", WM8995_AIF1_DAC1_LEFT_VOLUME,
		WM8995_AIF1_DAC1_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R_TLV("AIF1DAC2 Volume", WM8995_AIF1_DAC2_LEFT_VOLUME,
		WM8995_AIF1_DAC2_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R_TLV("AIF2DAC Volume", WM8995_AIF2_DAC_LEFT_VOLUME,
		WM8995_AIF2_DAC_RIGHT_VOLUME, 0, 96, 0, digital_tlv),

	SOC_DOUBLE_R_TLV("IN1LR Volume", WM8995_LEFT_LINE_INPUT_1_VOLUME,
		WM8995_RIGHT_LINE_INPUT_1_VOLUME, 0, 31, 0, in1lr_pga_tlv),

	SOC_SINGLE_TLV("IN1L Boost", WM8995_LEFT_LINE_INPUT_CONTROL,
		4, 3, 0, in1l_boost_tlv),

	SOC_ENUM("IN1L Mode", in1l_क्रमागत),
	SOC_ENUM("IN1R Mode", in1r_क्रमागत),

	SOC_ENUM("DMIC1 SRC", dmic_src1_क्रमागत),
	SOC_ENUM("DMIC2 SRC", dmic_src2_क्रमागत),

	SOC_DOUBLE_TLV("DAC1 Sidetone Volume", WM8995_DAC1_MIXER_VOLUMES, 0, 5,
		24, 0, sidetone_tlv),
	SOC_DOUBLE_TLV("DAC2 Sidetone Volume", WM8995_DAC2_MIXER_VOLUMES, 0, 5,
		24, 0, sidetone_tlv),

	SOC_DOUBLE_R_TLV("AIF1ADC1 Volume", WM8995_AIF1_ADC1_LEFT_VOLUME,
		WM8995_AIF1_ADC1_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R_TLV("AIF1ADC2 Volume", WM8995_AIF1_ADC2_LEFT_VOLUME,
		WM8995_AIF1_ADC2_RIGHT_VOLUME, 0, 96, 0, digital_tlv),
	SOC_DOUBLE_R_TLV("AIF2ADC Volume", WM8995_AIF2_ADC_LEFT_VOLUME,
		WM8995_AIF2_ADC_RIGHT_VOLUME, 0, 96, 0, digital_tlv)
पूर्ण;

अटल व्योम wm8995_update_class_w(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक enable = 1;
	पूर्णांक source = 0;  /* GCC flow analysis can't track enable */
	पूर्णांक reg, reg_r;

	/* We also need the same setting क्रम L/R and only one path */
	reg = snd_soc_component_पढ़ो(component, WM8995_DAC1_LEFT_MIXER_ROUTING);
	चयन (reg) अणु
	हाल WM8995_AIF2DACL_TO_DAC1L:
		dev_dbg(component->dev, "Class W source AIF2DAC\n");
		source = 2 << WM8995_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	हाल WM8995_AIF1DAC2L_TO_DAC1L:
		dev_dbg(component->dev, "Class W source AIF1DAC2\n");
		source = 1 << WM8995_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	हाल WM8995_AIF1DAC1L_TO_DAC1L:
		dev_dbg(component->dev, "Class W source AIF1DAC1\n");
		source = 0 << WM8995_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	शेष:
		dev_dbg(component->dev, "DAC mixer setting: %x\n", reg);
		enable = 0;
		अवरोध;
	पूर्ण

	reg_r = snd_soc_component_पढ़ो(component, WM8995_DAC1_RIGHT_MIXER_ROUTING);
	अगर (reg_r != reg) अणु
		dev_dbg(component->dev, "Left and right DAC mixers different\n");
		enable = 0;
	पूर्ण

	अगर (enable) अणु
		dev_dbg(component->dev, "Class W enabled\n");
		snd_soc_component_update_bits(component, WM8995_CLASS_W_1,
				    WM8995_CP_DYN_PWR_MASK |
				    WM8995_CP_DYN_SRC_SEL_MASK,
				    source | WM8995_CP_DYN_PWR);
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "Class W disabled\n");
		snd_soc_component_update_bits(component, WM8995_CLASS_W_1,
				    WM8995_CP_DYN_PWR_MASK, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक check_clk_sys(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;
	स्थिर अक्षर *clk;

	reg = snd_soc_component_पढ़ो(component, WM8995_CLOCKING_1);
	/* Check what we're currently using क्रम CLK_SYS */
	अगर (reg & WM8995_SYSCLK_SRC)
		clk = "AIF2CLK";
	अन्यथा
		clk = "AIF1CLK";
	वापस !म_भेद(source->name, clk);
पूर्ण

अटल पूर्णांक wm8995_put_class_w(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	पूर्णांक ret;

	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);
	wm8995_update_class_w(component);
	वापस ret;
पूर्ण

अटल पूर्णांक hp_supply_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable the headphone amp */
		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    WM8995_HPOUT1L_ENA |
				    WM8995_HPOUT1R_ENA);

		/* Enable the second stage */
		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_DLY_MASK |
				    WM8995_HPOUT1R_DLY_MASK,
				    WM8995_HPOUT1L_DLY |
				    WM8995_HPOUT1R_DLY);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8995_CHARGE_PUMP_1,
				    WM8995_CP_ENA_MASK, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dc_servo_cmd(काष्ठा snd_soc_component *component,
			 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mask)
अणु
	पूर्णांक समयout = 10;

	dev_dbg(component->dev, "%s: reg = %#x, val = %#x, mask = %#x\n",
		__func__, reg, val, mask);

	snd_soc_component_ग_लिखो(component, reg, val);
	जबतक (समयout--) अणु
		msleep(10);
		val = snd_soc_component_पढ़ो(component, WM8995_DC_SERVO_READBACK_0);
		अगर ((val & mask) == mask)
			वापस;
	पूर्ण

	dev_err(component->dev, "Timed out waiting for DC Servo\n");
पूर्ण

अटल पूर्णांक hp_event(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8995_ANALOGUE_HP_1);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM8995_CHARGE_PUMP_1,
				    WM8995_CP_ENA_MASK, WM8995_CP_ENA);

		msleep(5);

		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    WM8995_HPOUT1L_ENA | WM8995_HPOUT1R_ENA);

		udelay(20);

		reg |= WM8995_HPOUT1L_DLY | WM8995_HPOUT1R_DLY;
		snd_soc_component_ग_लिखो(component, WM8995_ANALOGUE_HP_1, reg);

		snd_soc_component_ग_लिखो(component, WM8995_DC_SERVO_1, WM8995_DCS_ENA_CHAN_0 |
			      WM8995_DCS_ENA_CHAN_1);

		dc_servo_cmd(component, WM8995_DC_SERVO_2,
			     WM8995_DCS_TRIG_STARTUP_0 |
			     WM8995_DCS_TRIG_STARTUP_1,
			     WM8995_DCS_TRIG_DAC_WR_0 |
			     WM8995_DCS_TRIG_DAC_WR_1);

		reg |= WM8995_HPOUT1R_OUTP | WM8995_HPOUT1R_RMV_SHORT |
		       WM8995_HPOUT1L_OUTP | WM8995_HPOUT1L_RMV_SHORT;
		snd_soc_component_ग_लिखो(component, WM8995_ANALOGUE_HP_1, reg);

		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_OUTP_MASK |
				    WM8995_HPOUT1R_OUTP_MASK |
				    WM8995_HPOUT1L_RMV_SHORT_MASK |
				    WM8995_HPOUT1R_RMV_SHORT_MASK, 0);

		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_DLY_MASK |
				    WM8995_HPOUT1R_DLY_MASK, 0);

		snd_soc_component_ग_लिखो(component, WM8995_DC_SERVO_1, 0);

		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक configure_aअगर_घड़ी(काष्ठा snd_soc_component *component, पूर्णांक aअगर)
अणु
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक rate;
	पूर्णांक reg1 = 0;
	पूर्णांक offset;

	wm8995 = snd_soc_component_get_drvdata(component);

	अगर (aअगर)
		offset = 4;
	अन्यथा
		offset = 0;

	चयन (wm8995->sysclk[aअगर]) अणु
	हाल WM8995_SYSCLK_MCLK1:
		rate = wm8995->mclk[0];
		अवरोध;
	हाल WM8995_SYSCLK_MCLK2:
		reg1 |= 0x8;
		rate = wm8995->mclk[1];
		अवरोध;
	हाल WM8995_SYSCLK_FLL1:
		reg1 |= 0x10;
		rate = wm8995->fll[0].out;
		अवरोध;
	हाल WM8995_SYSCLK_FLL2:
		reg1 |= 0x18;
		rate = wm8995->fll[1].out;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate >= 13500000) अणु
		rate /= 2;
		reg1 |= WM8995_AIF1CLK_DIV;

		dev_dbg(component->dev, "Dividing AIF%d clock to %dHz\n",
			aअगर + 1, rate);
	पूर्ण

	wm8995->aअगरclk[aअगर] = rate;

	snd_soc_component_update_bits(component, WM8995_AIF1_CLOCKING_1 + offset,
			    WM8995_AIF1CLK_SRC_MASK | WM8995_AIF1CLK_DIV_MASK,
			    reg1);
	वापस 0;
पूर्ण

अटल पूर्णांक configure_घड़ी(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक change, new;

	wm8995 = snd_soc_component_get_drvdata(component);

	/* Bring up the AIF घड़ीs first */
	configure_aअगर_घड़ी(component, 0);
	configure_aअगर_घड़ी(component, 1);

	/*
	 * Then चयन CLK_SYS over to the higher of them; a change
	 * can only happen as a result of a घड़ीing change which can
	 * only be made outside of DAPM so we can safely reकरो the
	 * घड़ीing.
	 */

	/* If they're equal it doesn't matter which is used */
	अगर (wm8995->aअगरclk[0] == wm8995->aअगरclk[1])
		वापस 0;

	अगर (wm8995->aअगरclk[0] < wm8995->aअगरclk[1])
		new = WM8995_SYSCLK_SRC;
	अन्यथा
		new = 0;

	change = snd_soc_component_update_bits(component, WM8995_CLOCKING_1,
				     WM8995_SYSCLK_SRC_MASK, new);
	अगर (!change)
		वापस 0;

	snd_soc_dapm_sync(dapm);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sys_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस configure_घड़ी(component);

	हाल SND_SOC_DAPM_POST_PMD:
		configure_घड़ी(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"ADC/DMIC1", "DMIC2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sidetone1_क्रमागत, WM8995_SIDETONE, 0, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetone1_mux =
	SOC_DAPM_ENUM("Left Sidetone Mux", sidetone1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(sidetone2_क्रमागत, WM8995_SIDETONE, 1, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetone2_mux =
	SOC_DAPM_ENUM("Right Sidetone Mux", sidetone2_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc1l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC/DMIC Switch", WM8995_AIF1_ADC1_LEFT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_AIF1_ADC1_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc1r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC/DMIC Switch", WM8995_AIF1_ADC1_RIGHT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_AIF1_ADC1_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc2l_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", WM8995_AIF1_ADC2_LEFT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_AIF1_ADC2_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc2r_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", WM8995_AIF1_ADC2_RIGHT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_AIF1_ADC2_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac1l_mix[] = अणु
	WM8995_CLASS_W_SWITCH("Right Sidetone Switch", WM8995_DAC1_LEFT_MIXER_ROUTING,
		5, 1, 0),
	WM8995_CLASS_W_SWITCH("Left Sidetone Switch", WM8995_DAC1_LEFT_MIXER_ROUTING,
		4, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF2 Switch", WM8995_DAC1_LEFT_MIXER_ROUTING,
		2, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF1.2 Switch", WM8995_DAC1_LEFT_MIXER_ROUTING,
		1, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF1.1 Switch", WM8995_DAC1_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac1r_mix[] = अणु
	WM8995_CLASS_W_SWITCH("Right Sidetone Switch", WM8995_DAC1_RIGHT_MIXER_ROUTING,
		5, 1, 0),
	WM8995_CLASS_W_SWITCH("Left Sidetone Switch", WM8995_DAC1_RIGHT_MIXER_ROUTING,
		4, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF2 Switch", WM8995_DAC1_RIGHT_MIXER_ROUTING,
		2, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF1.2 Switch", WM8995_DAC1_RIGHT_MIXER_ROUTING,
		1, 1, 0),
	WM8995_CLASS_W_SWITCH("AIF1.1 Switch", WM8995_DAC1_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dac2l_mix[] = अणु
	SOC_DAPM_SINGLE("Right Sidetone Switch", WM8995_DAC2_LEFT_MIXER_ROUTING,
		5, 1, 0),
	SOC_DAPM_SINGLE("Left Sidetone Switch", WM8995_DAC2_LEFT_MIXER_ROUTING,
		4, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_DAC2_LEFT_MIXER_ROUTING,
		2, 1, 0),
	SOC_DAPM_SINGLE("AIF1.2 Switch", WM8995_DAC2_LEFT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF1.1 Switch", WM8995_DAC2_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dac2r_mix[] = अणु
	SOC_DAPM_SINGLE("Right Sidetone Switch", WM8995_DAC2_RIGHT_MIXER_ROUTING,
		5, 1, 0),
	SOC_DAPM_SINGLE("Left Sidetone Switch", WM8995_DAC2_RIGHT_MIXER_ROUTING,
		4, 1, 0),
	SOC_DAPM_SINGLE("AIF2 Switch", WM8995_DAC2_RIGHT_MIXER_ROUTING,
		2, 1, 0),
	SOC_DAPM_SINGLE("AIF1.2 Switch", WM8995_DAC2_RIGHT_MIXER_ROUTING,
		1, 1, 0),
	SOC_DAPM_SINGLE("AIF1.1 Switch", WM8995_DAC2_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new in1l_pga =
	SOC_DAPM_SINGLE("IN1L Switch", WM8995_POWER_MANAGEMENT_2, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new in1r_pga =
	SOC_DAPM_SINGLE("IN1R Switch", WM8995_POWER_MANAGEMENT_2, 4, 1, 0);

अटल स्थिर अक्षर *adc_mux_text[] = अणु
	"ADC",
	"DMIC",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adc_क्रमागत, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcl_mux =
	SOC_DAPM_ENUM("ADCL Mux", adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adcr_mux =
	SOC_DAPM_ENUM("ADCR Mux", adc_क्रमागत);

अटल स्थिर अक्षर *spk_src_text[] = अणु
	"DAC1L", "DAC1R", "DAC2L", "DAC2R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(spk1l_src_क्रमागत, WM8995_LEFT_PDM_SPEAKER_1,
			    0, spk_src_text);
अटल SOC_ENUM_SINGLE_DECL(spk1r_src_क्रमागत, WM8995_RIGHT_PDM_SPEAKER_1,
			    0, spk_src_text);
अटल SOC_ENUM_SINGLE_DECL(spk2l_src_क्रमागत, WM8995_LEFT_PDM_SPEAKER_2,
			    0, spk_src_text);
अटल SOC_ENUM_SINGLE_DECL(spk2r_src_क्रमागत, WM8995_RIGHT_PDM_SPEAKER_2,
			    0, spk_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new spk1l_mux =
	SOC_DAPM_ENUM("SPK1L SRC", spk1l_src_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new spk1r_mux =
	SOC_DAPM_ENUM("SPK1R SRC", spk1r_src_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new spk2l_mux =
	SOC_DAPM_ENUM("SPK2L SRC", spk2l_src_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new spk2r_mux =
	SOC_DAPM_ENUM("SPK2R SRC", spk2r_src_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8995_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMIC1DAT"),
	SND_SOC_DAPM_INPUT("DMIC2DAT"),

	SND_SOC_DAPM_INPUT("IN1L"),
	SND_SOC_DAPM_INPUT("IN1R"),

	SND_SOC_DAPM_MIXER("IN1L PGA", SND_SOC_NOPM, 0, 0,
		&in1l_pga, 1),
	SND_SOC_DAPM_MIXER("IN1R PGA", SND_SOC_NOPM, 0, 0,
		&in1r_pga, 1),

	SND_SOC_DAPM_SUPPLY("MICBIAS1", WM8995_POWER_MANAGEMENT_1, 8, 0,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS2", WM8995_POWER_MANAGEMENT_1, 9, 0,
			    शून्य, 0),

	SND_SOC_DAPM_SUPPLY("AIF1CLK", WM8995_AIF1_CLOCKING_1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF2CLK", WM8995_AIF2_CLOCKING_1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSP1CLK", WM8995_CLOCKING_1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DSP2CLK", WM8995_CLOCKING_1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SYSDSPCLK", WM8995_CLOCKING_1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK_SYS", SND_SOC_NOPM, 0, 0, clk_sys_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_AIF_OUT("AIF1ADC1L", "AIF1 Capture", 0,
		WM8995_POWER_MANAGEMENT_3, 9, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1ADC1R", "AIF1 Capture", 0,
		WM8995_POWER_MANAGEMENT_3, 8, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1ADCDAT", "AIF1 Capture", 0,
	SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1ADC2L", "AIF1 Capture",
		0, WM8995_POWER_MANAGEMENT_3, 11, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1ADC2R", "AIF1 Capture",
		0, WM8995_POWER_MANAGEMENT_3, 10, 0),

	SND_SOC_DAPM_MUX("ADCL Mux", SND_SOC_NOPM, 1, 0, &adcl_mux),
	SND_SOC_DAPM_MUX("ADCR Mux", SND_SOC_NOPM, 0, 0, &adcr_mux),

	SND_SOC_DAPM_ADC("DMIC2L", शून्य, WM8995_POWER_MANAGEMENT_3, 5, 0),
	SND_SOC_DAPM_ADC("DMIC2R", शून्य, WM8995_POWER_MANAGEMENT_3, 4, 0),
	SND_SOC_DAPM_ADC("DMIC1L", शून्य, WM8995_POWER_MANAGEMENT_3, 3, 0),
	SND_SOC_DAPM_ADC("DMIC1R", शून्य, WM8995_POWER_MANAGEMENT_3, 2, 0),

	SND_SOC_DAPM_ADC("ADCL", शून्य, WM8995_POWER_MANAGEMENT_3, 1, 0),
	SND_SOC_DAPM_ADC("ADCR", शून्य, WM8995_POWER_MANAGEMENT_3, 0, 0),

	SND_SOC_DAPM_MIXER("AIF1ADC1L Mixer", SND_SOC_NOPM, 0, 0,
		aअगर1adc1l_mix, ARRAY_SIZE(aअगर1adc1l_mix)),
	SND_SOC_DAPM_MIXER("AIF1ADC1R Mixer", SND_SOC_NOPM, 0, 0,
		aअगर1adc1r_mix, ARRAY_SIZE(aअगर1adc1r_mix)),
	SND_SOC_DAPM_MIXER("AIF1ADC2L Mixer", SND_SOC_NOPM, 0, 0,
		aअगर1adc2l_mix, ARRAY_SIZE(aअगर1adc2l_mix)),
	SND_SOC_DAPM_MIXER("AIF1ADC2R Mixer", SND_SOC_NOPM, 0, 0,
		aअगर1adc2r_mix, ARRAY_SIZE(aअगर1adc2r_mix)),

	SND_SOC_DAPM_AIF_IN("AIF1DAC1L", शून्य, 0, WM8995_POWER_MANAGEMENT_4,
		9, 0),
	SND_SOC_DAPM_AIF_IN("AIF1DAC1R", शून्य, 0, WM8995_POWER_MANAGEMENT_4,
		8, 0),
	SND_SOC_DAPM_AIF_IN("AIF1DACDAT", "AIF1 Playback", 0, SND_SOC_NOPM,
		0, 0),

	SND_SOC_DAPM_AIF_IN("AIF1DAC2L", शून्य, 0, WM8995_POWER_MANAGEMENT_4,
		11, 0),
	SND_SOC_DAPM_AIF_IN("AIF1DAC2R", शून्य, 0, WM8995_POWER_MANAGEMENT_4,
		10, 0),

	SND_SOC_DAPM_MIXER("AIF2DAC2L Mixer", SND_SOC_NOPM, 0, 0,
		aअगर2dac2l_mix, ARRAY_SIZE(aअगर2dac2l_mix)),
	SND_SOC_DAPM_MIXER("AIF2DAC2R Mixer", SND_SOC_NOPM, 0, 0,
		aअगर2dac2r_mix, ARRAY_SIZE(aअगर2dac2r_mix)),

	SND_SOC_DAPM_DAC("DAC2L", शून्य, WM8995_POWER_MANAGEMENT_4, 3, 0),
	SND_SOC_DAPM_DAC("DAC2R", शून्य, WM8995_POWER_MANAGEMENT_4, 2, 0),
	SND_SOC_DAPM_DAC("DAC1L", शून्य, WM8995_POWER_MANAGEMENT_4, 1, 0),
	SND_SOC_DAPM_DAC("DAC1R", शून्य, WM8995_POWER_MANAGEMENT_4, 0, 0),

	SND_SOC_DAPM_MIXER("DAC1L Mixer", SND_SOC_NOPM, 0, 0, dac1l_mix,
		ARRAY_SIZE(dac1l_mix)),
	SND_SOC_DAPM_MIXER("DAC1R Mixer", SND_SOC_NOPM, 0, 0, dac1r_mix,
		ARRAY_SIZE(dac1r_mix)),

	SND_SOC_DAPM_MUX("Left Sidetone", SND_SOC_NOPM, 0, 0, &sidetone1_mux),
	SND_SOC_DAPM_MUX("Right Sidetone", SND_SOC_NOPM, 0, 0, &sidetone2_mux),

	SND_SOC_DAPM_PGA_E("Headphone PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
		hp_event, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY("Headphone Supply", SND_SOC_NOPM, 0, 0,
		hp_supply_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MUX("SPK1L Driver", WM8995_LEFT_PDM_SPEAKER_1,
		4, 0, &spk1l_mux),
	SND_SOC_DAPM_MUX("SPK1R Driver", WM8995_RIGHT_PDM_SPEAKER_1,
		4, 0, &spk1r_mux),
	SND_SOC_DAPM_MUX("SPK2L Driver", WM8995_LEFT_PDM_SPEAKER_2,
		4, 0, &spk2l_mux),
	SND_SOC_DAPM_MUX("SPK2R Driver", WM8995_RIGHT_PDM_SPEAKER_2,
		4, 0, &spk2r_mux),

	SND_SOC_DAPM_SUPPLY("LDO2", WM8995_POWER_MANAGEMENT_2, 1, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("HP1L"),
	SND_SOC_DAPM_OUTPUT("HP1R"),
	SND_SOC_DAPM_OUTPUT("SPK1L"),
	SND_SOC_DAPM_OUTPUT("SPK1R"),
	SND_SOC_DAPM_OUTPUT("SPK2L"),
	SND_SOC_DAPM_OUTPUT("SPK2R")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8995_पूर्णांकercon[] = अणु
	अणु "CLK_SYS", शून्य, "AIF1CLK", check_clk_sys पूर्ण,
	अणु "CLK_SYS", शून्य, "AIF2CLK", check_clk_sys पूर्ण,

	अणु "DSP1CLK", शून्य, "CLK_SYS" पूर्ण,
	अणु "DSP2CLK", शून्य, "CLK_SYS" पूर्ण,
	अणु "SYSDSPCLK", शून्य, "CLK_SYS" पूर्ण,

	अणु "AIF1ADC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "AIF1ADC2L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC2L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "DMIC1L", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1L", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1R", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC2L", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2L", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2R", शून्य, "CLK_SYS" पूर्ण,

	अणु "ADCL", शून्य, "AIF1CLK" पूर्ण,
	अणु "ADCL", शून्य, "DSP1CLK" पूर्ण,
	अणु "ADCL", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "ADCR", शून्य, "AIF1CLK" पूर्ण,
	अणु "ADCR", शून्य, "DSP1CLK" पूर्ण,
	अणु "ADCR", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "IN1L PGA", "IN1L Switch", "IN1L" पूर्ण,
	अणु "IN1R PGA", "IN1R Switch", "IN1R" पूर्ण,
	अणु "IN1L PGA", शून्य, "LDO2" पूर्ण,
	अणु "IN1R PGA", शून्य, "LDO2" पूर्ण,

	अणु "ADCL", शून्य, "IN1L PGA" पूर्ण,
	अणु "ADCR", शून्य, "IN1R PGA" पूर्ण,

	अणु "ADCL Mux", "ADC", "ADCL" पूर्ण,
	अणु "ADCL Mux", "DMIC", "DMIC1L" पूर्ण,
	अणु "ADCR Mux", "ADC", "ADCR" पूर्ण,
	अणु "ADCR Mux", "DMIC", "DMIC1R" पूर्ण,

	/* AIF1 outमाला_दो */
	अणु "AIF1ADC1L", शून्य, "AIF1ADC1L Mixer" पूर्ण,
	अणु "AIF1ADC1L Mixer", "ADC/DMIC Switch", "ADCL Mux" पूर्ण,

	अणु "AIF1ADC1R", शून्य, "AIF1ADC1R Mixer" पूर्ण,
	अणु "AIF1ADC1R Mixer", "ADC/DMIC Switch", "ADCR Mux" पूर्ण,

	अणु "AIF1ADC2L", शून्य, "AIF1ADC2L Mixer" पूर्ण,
	अणु "AIF1ADC2L Mixer", "DMIC Switch", "DMIC2L" पूर्ण,

	अणु "AIF1ADC2R", शून्य, "AIF1ADC2R Mixer" पूर्ण,
	अणु "AIF1ADC2R Mixer", "DMIC Switch", "DMIC2R" पूर्ण,

	/* Sidetone */
	अणु "Left Sidetone", "ADC/DMIC1", "AIF1ADC1L" पूर्ण,
	अणु "Left Sidetone", "DMIC2", "AIF1ADC2L" पूर्ण,
	अणु "Right Sidetone", "ADC/DMIC1", "AIF1ADC1R" पूर्ण,
	अणु "Right Sidetone", "DMIC2", "AIF1ADC2R" पूर्ण,

	अणु "AIF1DAC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "AIF1DAC2L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC2L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "DAC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "DAC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "DAC1L", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "DAC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "DAC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "DAC1R", शून्य, "SYSDSPCLK" पूर्ण,

	अणु "AIF1DAC1L", शून्य, "AIF1DACDAT" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "AIF1DACDAT" पूर्ण,
	अणु "AIF1DAC2L", शून्य, "AIF1DACDAT" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "AIF1DACDAT" पूर्ण,

	/* DAC1 inमाला_दो */
	अणु "DAC1L", शून्य, "DAC1L Mixer" पूर्ण,
	अणु "DAC1L Mixer", "AIF1.1 Switch", "AIF1DAC1L" पूर्ण,
	अणु "DAC1L Mixer", "AIF1.2 Switch", "AIF1DAC2L" पूर्ण,
	अणु "DAC1L Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "DAC1L Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	अणु "DAC1R", शून्य, "DAC1R Mixer" पूर्ण,
	अणु "DAC1R Mixer", "AIF1.1 Switch", "AIF1DAC1R" पूर्ण,
	अणु "DAC1R Mixer", "AIF1.2 Switch", "AIF1DAC2R" पूर्ण,
	अणु "DAC1R Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "DAC1R Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	/* DAC2/AIF2 outमाला_दो */
	अणु "DAC2L", शून्य, "AIF2DAC2L Mixer" पूर्ण,
	अणु "AIF2DAC2L Mixer", "AIF1.2 Switch", "AIF1DAC2L" पूर्ण,
	अणु "AIF2DAC2L Mixer", "AIF1.1 Switch", "AIF1DAC1L" पूर्ण,

	अणु "DAC2R", शून्य, "AIF2DAC2R Mixer" पूर्ण,
	अणु "AIF2DAC2R Mixer", "AIF1.2 Switch", "AIF1DAC2R" पूर्ण,
	अणु "AIF2DAC2R Mixer", "AIF1.1 Switch", "AIF1DAC1R" पूर्ण,

	/* Output stages */
	अणु "Headphone PGA", शून्य, "DAC1L" पूर्ण,
	अणु "Headphone PGA", शून्य, "DAC1R" पूर्ण,

	अणु "Headphone PGA", शून्य, "DAC2L" पूर्ण,
	अणु "Headphone PGA", शून्य, "DAC2R" पूर्ण,

	अणु "Headphone PGA", शून्य, "Headphone Supply" पूर्ण,
	अणु "Headphone PGA", शून्य, "CLK_SYS" पूर्ण,
	अणु "Headphone PGA", शून्य, "LDO2" पूर्ण,

	अणु "HP1L", शून्य, "Headphone PGA" पूर्ण,
	अणु "HP1R", शून्य, "Headphone PGA" पूर्ण,

	अणु "SPK1L Driver", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPK1L Driver", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPK1L Driver", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPK1L Driver", "DAC2R", "DAC2R" पूर्ण,
	अणु "SPK1L Driver", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPK1R Driver", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPK1R Driver", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPK1R Driver", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPK1R Driver", "DAC2R", "DAC2R" पूर्ण,
	अणु "SPK1R Driver", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPK2L Driver", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPK2L Driver", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPK2L Driver", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPK2L Driver", "DAC2R", "DAC2R" पूर्ण,
	अणु "SPK2L Driver", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPK2R Driver", "DAC1L", "DAC1L" पूर्ण,
	अणु "SPK2R Driver", "DAC1R", "DAC1R" पूर्ण,
	अणु "SPK2R Driver", "DAC2L", "DAC2L" पूर्ण,
	अणु "SPK2R Driver", "DAC2R", "DAC2R" पूर्ण,
	अणु "SPK2R Driver", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPK1L", शून्य, "SPK1L Driver" पूर्ण,
	अणु "SPK1R", शून्य, "SPK1R Driver" पूर्ण,
	अणु "SPK2L", शून्य, "SPK2L Driver" पूर्ण,
	अणु "SPK2R", शून्य, "SPK2R Driver" पूर्ण
पूर्ण;

अटल bool wm8995_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8995_SOFTWARE_RESET:
	हाल WM8995_POWER_MANAGEMENT_1:
	हाल WM8995_POWER_MANAGEMENT_2:
	हाल WM8995_POWER_MANAGEMENT_3:
	हाल WM8995_POWER_MANAGEMENT_4:
	हाल WM8995_POWER_MANAGEMENT_5:
	हाल WM8995_LEFT_LINE_INPUT_1_VOLUME:
	हाल WM8995_RIGHT_LINE_INPUT_1_VOLUME:
	हाल WM8995_LEFT_LINE_INPUT_CONTROL:
	हाल WM8995_DAC1_LEFT_VOLUME:
	हाल WM8995_DAC1_RIGHT_VOLUME:
	हाल WM8995_DAC2_LEFT_VOLUME:
	हाल WM8995_DAC2_RIGHT_VOLUME:
	हाल WM8995_OUTPUT_VOLUME_ZC_1:
	हाल WM8995_MICBIAS_1:
	हाल WM8995_MICBIAS_2:
	हाल WM8995_LDO_1:
	हाल WM8995_LDO_2:
	हाल WM8995_ACCESSORY_DETECT_MODE1:
	हाल WM8995_ACCESSORY_DETECT_MODE2:
	हाल WM8995_HEADPHONE_DETECT1:
	हाल WM8995_HEADPHONE_DETECT2:
	हाल WM8995_MIC_DETECT_1:
	हाल WM8995_MIC_DETECT_2:
	हाल WM8995_CHARGE_PUMP_1:
	हाल WM8995_CLASS_W_1:
	हाल WM8995_DC_SERVO_1:
	हाल WM8995_DC_SERVO_2:
	हाल WM8995_DC_SERVO_3:
	हाल WM8995_DC_SERVO_5:
	हाल WM8995_DC_SERVO_6:
	हाल WM8995_DC_SERVO_7:
	हाल WM8995_DC_SERVO_READBACK_0:
	हाल WM8995_ANALOGUE_HP_1:
	हाल WM8995_ANALOGUE_HP_2:
	हाल WM8995_CHIP_REVISION:
	हाल WM8995_CONTROL_INTERFACE_1:
	हाल WM8995_CONTROL_INTERFACE_2:
	हाल WM8995_WRITE_SEQUENCER_CTRL_1:
	हाल WM8995_WRITE_SEQUENCER_CTRL_2:
	हाल WM8995_AIF1_CLOCKING_1:
	हाल WM8995_AIF1_CLOCKING_2:
	हाल WM8995_AIF2_CLOCKING_1:
	हाल WM8995_AIF2_CLOCKING_2:
	हाल WM8995_CLOCKING_1:
	हाल WM8995_CLOCKING_2:
	हाल WM8995_AIF1_RATE:
	हाल WM8995_AIF2_RATE:
	हाल WM8995_RATE_STATUS:
	हाल WM8995_FLL1_CONTROL_1:
	हाल WM8995_FLL1_CONTROL_2:
	हाल WM8995_FLL1_CONTROL_3:
	हाल WM8995_FLL1_CONTROL_4:
	हाल WM8995_FLL1_CONTROL_5:
	हाल WM8995_FLL2_CONTROL_1:
	हाल WM8995_FLL2_CONTROL_2:
	हाल WM8995_FLL2_CONTROL_3:
	हाल WM8995_FLL2_CONTROL_4:
	हाल WM8995_FLL2_CONTROL_5:
	हाल WM8995_AIF1_CONTROL_1:
	हाल WM8995_AIF1_CONTROL_2:
	हाल WM8995_AIF1_MASTER_SLAVE:
	हाल WM8995_AIF1_BCLK:
	हाल WM8995_AIF1ADC_LRCLK:
	हाल WM8995_AIF1DAC_LRCLK:
	हाल WM8995_AIF1DAC_DATA:
	हाल WM8995_AIF1ADC_DATA:
	हाल WM8995_AIF2_CONTROL_1:
	हाल WM8995_AIF2_CONTROL_2:
	हाल WM8995_AIF2_MASTER_SLAVE:
	हाल WM8995_AIF2_BCLK:
	हाल WM8995_AIF2ADC_LRCLK:
	हाल WM8995_AIF2DAC_LRCLK:
	हाल WM8995_AIF2DAC_DATA:
	हाल WM8995_AIF2ADC_DATA:
	हाल WM8995_AIF1_ADC1_LEFT_VOLUME:
	हाल WM8995_AIF1_ADC1_RIGHT_VOLUME:
	हाल WM8995_AIF1_DAC1_LEFT_VOLUME:
	हाल WM8995_AIF1_DAC1_RIGHT_VOLUME:
	हाल WM8995_AIF1_ADC2_LEFT_VOLUME:
	हाल WM8995_AIF1_ADC2_RIGHT_VOLUME:
	हाल WM8995_AIF1_DAC2_LEFT_VOLUME:
	हाल WM8995_AIF1_DAC2_RIGHT_VOLUME:
	हाल WM8995_AIF1_ADC1_FILTERS:
	हाल WM8995_AIF1_ADC2_FILTERS:
	हाल WM8995_AIF1_DAC1_FILTERS_1:
	हाल WM8995_AIF1_DAC1_FILTERS_2:
	हाल WM8995_AIF1_DAC2_FILTERS_1:
	हाल WM8995_AIF1_DAC2_FILTERS_2:
	हाल WM8995_AIF1_DRC1_1:
	हाल WM8995_AIF1_DRC1_2:
	हाल WM8995_AIF1_DRC1_3:
	हाल WM8995_AIF1_DRC1_4:
	हाल WM8995_AIF1_DRC1_5:
	हाल WM8995_AIF1_DRC2_1:
	हाल WM8995_AIF1_DRC2_2:
	हाल WM8995_AIF1_DRC2_3:
	हाल WM8995_AIF1_DRC2_4:
	हाल WM8995_AIF1_DRC2_5:
	हाल WM8995_AIF1_DAC1_EQ_GAINS_1:
	हाल WM8995_AIF1_DAC1_EQ_GAINS_2:
	हाल WM8995_AIF1_DAC1_EQ_BAND_1_A:
	हाल WM8995_AIF1_DAC1_EQ_BAND_1_B:
	हाल WM8995_AIF1_DAC1_EQ_BAND_1_PG:
	हाल WM8995_AIF1_DAC1_EQ_BAND_2_A:
	हाल WM8995_AIF1_DAC1_EQ_BAND_2_B:
	हाल WM8995_AIF1_DAC1_EQ_BAND_2_C:
	हाल WM8995_AIF1_DAC1_EQ_BAND_2_PG:
	हाल WM8995_AIF1_DAC1_EQ_BAND_3_A:
	हाल WM8995_AIF1_DAC1_EQ_BAND_3_B:
	हाल WM8995_AIF1_DAC1_EQ_BAND_3_C:
	हाल WM8995_AIF1_DAC1_EQ_BAND_3_PG:
	हाल WM8995_AIF1_DAC1_EQ_BAND_4_A:
	हाल WM8995_AIF1_DAC1_EQ_BAND_4_B:
	हाल WM8995_AIF1_DAC1_EQ_BAND_4_C:
	हाल WM8995_AIF1_DAC1_EQ_BAND_4_PG:
	हाल WM8995_AIF1_DAC1_EQ_BAND_5_A:
	हाल WM8995_AIF1_DAC1_EQ_BAND_5_B:
	हाल WM8995_AIF1_DAC1_EQ_BAND_5_PG:
	हाल WM8995_AIF1_DAC2_EQ_GAINS_1:
	हाल WM8995_AIF1_DAC2_EQ_GAINS_2:
	हाल WM8995_AIF1_DAC2_EQ_BAND_1_A:
	हाल WM8995_AIF1_DAC2_EQ_BAND_1_B:
	हाल WM8995_AIF1_DAC2_EQ_BAND_1_PG:
	हाल WM8995_AIF1_DAC2_EQ_BAND_2_A:
	हाल WM8995_AIF1_DAC2_EQ_BAND_2_B:
	हाल WM8995_AIF1_DAC2_EQ_BAND_2_C:
	हाल WM8995_AIF1_DAC2_EQ_BAND_2_PG:
	हाल WM8995_AIF1_DAC2_EQ_BAND_3_A:
	हाल WM8995_AIF1_DAC2_EQ_BAND_3_B:
	हाल WM8995_AIF1_DAC2_EQ_BAND_3_C:
	हाल WM8995_AIF1_DAC2_EQ_BAND_3_PG:
	हाल WM8995_AIF1_DAC2_EQ_BAND_4_A:
	हाल WM8995_AIF1_DAC2_EQ_BAND_4_B:
	हाल WM8995_AIF1_DAC2_EQ_BAND_4_C:
	हाल WM8995_AIF1_DAC2_EQ_BAND_4_PG:
	हाल WM8995_AIF1_DAC2_EQ_BAND_5_A:
	हाल WM8995_AIF1_DAC2_EQ_BAND_5_B:
	हाल WM8995_AIF1_DAC2_EQ_BAND_5_PG:
	हाल WM8995_AIF2_ADC_LEFT_VOLUME:
	हाल WM8995_AIF2_ADC_RIGHT_VOLUME:
	हाल WM8995_AIF2_DAC_LEFT_VOLUME:
	हाल WM8995_AIF2_DAC_RIGHT_VOLUME:
	हाल WM8995_AIF2_ADC_FILTERS:
	हाल WM8995_AIF2_DAC_FILTERS_1:
	हाल WM8995_AIF2_DAC_FILTERS_2:
	हाल WM8995_AIF2_DRC_1:
	हाल WM8995_AIF2_DRC_2:
	हाल WM8995_AIF2_DRC_3:
	हाल WM8995_AIF2_DRC_4:
	हाल WM8995_AIF2_DRC_5:
	हाल WM8995_AIF2_EQ_GAINS_1:
	हाल WM8995_AIF2_EQ_GAINS_2:
	हाल WM8995_AIF2_EQ_BAND_1_A:
	हाल WM8995_AIF2_EQ_BAND_1_B:
	हाल WM8995_AIF2_EQ_BAND_1_PG:
	हाल WM8995_AIF2_EQ_BAND_2_A:
	हाल WM8995_AIF2_EQ_BAND_2_B:
	हाल WM8995_AIF2_EQ_BAND_2_C:
	हाल WM8995_AIF2_EQ_BAND_2_PG:
	हाल WM8995_AIF2_EQ_BAND_3_A:
	हाल WM8995_AIF2_EQ_BAND_3_B:
	हाल WM8995_AIF2_EQ_BAND_3_C:
	हाल WM8995_AIF2_EQ_BAND_3_PG:
	हाल WM8995_AIF2_EQ_BAND_4_A:
	हाल WM8995_AIF2_EQ_BAND_4_B:
	हाल WM8995_AIF2_EQ_BAND_4_C:
	हाल WM8995_AIF2_EQ_BAND_4_PG:
	हाल WM8995_AIF2_EQ_BAND_5_A:
	हाल WM8995_AIF2_EQ_BAND_5_B:
	हाल WM8995_AIF2_EQ_BAND_5_PG:
	हाल WM8995_DAC1_MIXER_VOLUMES:
	हाल WM8995_DAC1_LEFT_MIXER_ROUTING:
	हाल WM8995_DAC1_RIGHT_MIXER_ROUTING:
	हाल WM8995_DAC2_MIXER_VOLUMES:
	हाल WM8995_DAC2_LEFT_MIXER_ROUTING:
	हाल WM8995_DAC2_RIGHT_MIXER_ROUTING:
	हाल WM8995_AIF1_ADC1_LEFT_MIXER_ROUTING:
	हाल WM8995_AIF1_ADC1_RIGHT_MIXER_ROUTING:
	हाल WM8995_AIF1_ADC2_LEFT_MIXER_ROUTING:
	हाल WM8995_AIF1_ADC2_RIGHT_MIXER_ROUTING:
	हाल WM8995_DAC_SOFTMUTE:
	हाल WM8995_OVERSAMPLING:
	हाल WM8995_SIDETONE:
	हाल WM8995_GPIO_1:
	हाल WM8995_GPIO_2:
	हाल WM8995_GPIO_3:
	हाल WM8995_GPIO_4:
	हाल WM8995_GPIO_5:
	हाल WM8995_GPIO_6:
	हाल WM8995_GPIO_7:
	हाल WM8995_GPIO_8:
	हाल WM8995_GPIO_9:
	हाल WM8995_GPIO_10:
	हाल WM8995_GPIO_11:
	हाल WM8995_GPIO_12:
	हाल WM8995_GPIO_13:
	हाल WM8995_GPIO_14:
	हाल WM8995_PULL_CONTROL_1:
	हाल WM8995_PULL_CONTROL_2:
	हाल WM8995_INTERRUPT_STATUS_1:
	हाल WM8995_INTERRUPT_STATUS_2:
	हाल WM8995_INTERRUPT_RAW_STATUS_2:
	हाल WM8995_INTERRUPT_STATUS_1_MASK:
	हाल WM8995_INTERRUPT_STATUS_2_MASK:
	हाल WM8995_INTERRUPT_CONTROL:
	हाल WM8995_LEFT_PDM_SPEAKER_1:
	हाल WM8995_RIGHT_PDM_SPEAKER_1:
	हाल WM8995_PDM_SPEAKER_1_MUTE_SEQUENCE:
	हाल WM8995_LEFT_PDM_SPEAKER_2:
	हाल WM8995_RIGHT_PDM_SPEAKER_2:
	हाल WM8995_PDM_SPEAKER_2_MUTE_SEQUENCE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8995_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8995_SOFTWARE_RESET:
	हाल WM8995_DC_SERVO_READBACK_0:
	हाल WM8995_INTERRUPT_STATUS_1:
	हाल WM8995_INTERRUPT_STATUS_2:
	हाल WM8995_INTERRUPT_CONTROL:
	हाल WM8995_ACCESSORY_DETECT_MODE1:
	हाल WM8995_ACCESSORY_DETECT_MODE2:
	हाल WM8995_HEADPHONE_DETECT1:
	हाल WM8995_HEADPHONE_DETECT2:
	हाल WM8995_RATE_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8995_aअगर_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक mute_reg;

	चयन (dai->id) अणु
	हाल 0:
		mute_reg = WM8995_AIF1_DAC1_FILTERS_1;
		अवरोध;
	हाल 1:
		mute_reg = WM8995_AIF2_DAC_FILTERS_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, mute_reg, WM8995_AIF1DAC1_MUTE_MASK,
			    !!mute << WM8995_AIF1DAC1_MUTE_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक master;
	पूर्णांक aअगर;

	component = dai->component;

	master = 0;
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master = WM8995_AIF1_MSTR;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown master/slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	aअगर = 0;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर |= WM8995_AIF1_LRCLK_INV;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर |= (0x3 << WM8995_AIF1_FMT_SHIFT);
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर |= (0x2 << WM8995_AIF1_FMT_SHIFT);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर |= (0x1 << WM8995_AIF1_FMT_SHIFT);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown dai format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर |= WM8995_AIF1_BCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			aअगर |= WM8995_AIF1_BCLK_INV | WM8995_AIF1_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर |= WM8995_AIF1_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर |= WM8995_AIF1_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8995_AIF1_CONTROL_1,
			    WM8995_AIF1_BCLK_INV_MASK |
			    WM8995_AIF1_LRCLK_INV_MASK |
			    WM8995_AIF1_FMT_MASK, aअगर);
	snd_soc_component_update_bits(component, WM8995_AIF1_MASTER_SLAVE,
			    WM8995_AIF1_MSTR_MASK, master);
	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक srs[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100,
	48000, 88200, 96000
पूर्ण;

अटल स्थिर पूर्णांक fs_ratios[] = अणु
	-1 /* reserved */,
	128, 192, 256, 384, 512, 768, 1024, 1408, 1536
पूर्ण;

अटल स्थिर पूर्णांक bclk_भागs[] = अणु
	10, 15, 20, 30, 40, 55, 60, 80, 110, 120, 160, 220, 240, 320, 440, 480
पूर्ण;

अटल पूर्णांक wm8995_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक aअगर1_reg;
	पूर्णांक bclk_reg;
	पूर्णांक lrclk_reg;
	पूर्णांक rate_reg;
	पूर्णांक bclk_rate;
	पूर्णांक aअगर1;
	पूर्णांक lrclk, bclk;
	पूर्णांक i, rate_val, best, best_val, cur_val;

	component = dai->component;
	wm8995 = snd_soc_component_get_drvdata(component);

	चयन (dai->id) अणु
	हाल 0:
		aअगर1_reg = WM8995_AIF1_CONTROL_1;
		bclk_reg = WM8995_AIF1_BCLK;
		rate_reg = WM8995_AIF1_RATE;
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK /* ||
			wm8995->lrclk_shared[0] */) अणु
			lrclk_reg = WM8995_AIF1DAC_LRCLK;
		पूर्ण अन्यथा अणु
			lrclk_reg = WM8995_AIF1ADC_LRCLK;
			dev_dbg(component->dev, "AIF1 using split LRCLK\n");
		पूर्ण
		अवरोध;
	हाल 1:
		aअगर1_reg = WM8995_AIF2_CONTROL_1;
		bclk_reg = WM8995_AIF2_BCLK;
		rate_reg = WM8995_AIF2_RATE;
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK /* ||
		    wm8995->lrclk_shared[1] */) अणु
			lrclk_reg = WM8995_AIF2DAC_LRCLK;
		पूर्ण अन्यथा अणु
			lrclk_reg = WM8995_AIF2ADC_LRCLK;
			dev_dbg(component->dev, "AIF2 using split LRCLK\n");
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bclk_rate = snd_soc_params_to_bclk(params);
	अगर (bclk_rate < 0)
		वापस bclk_rate;

	aअगर1 = 0;
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		aअगर1 |= (0x1 << WM8995_AIF1_WL_SHIFT);
		अवरोध;
	हाल 24:
		aअगर1 |= (0x2 << WM8995_AIF1_WL_SHIFT);
		अवरोध;
	हाल 32:
		aअगर1 |= (0x3 << WM8995_AIF1_WL_SHIFT);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported word length %u\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	/* try to find a suitable sample rate */
	क्रम (i = 0; i < ARRAY_SIZE(srs); ++i)
		अगर (srs[i] == params_rate(params))
			अवरोध;
	अगर (i == ARRAY_SIZE(srs)) अणु
		dev_err(dai->dev, "Sample rate %d is not supported\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण
	rate_val = i << WM8995_AIF1_SR_SHIFT;

	dev_dbg(dai->dev, "Sample rate is %dHz\n", srs[i]);
	dev_dbg(dai->dev, "AIF%dCLK is %dHz, target BCLK %dHz\n",
		dai->id + 1, wm8995->aअगरclk[dai->id], bclk_rate);

	/* AIFCLK/fs ratio; look क्रम a बंद match in either direction */
	best = 1;
	best_val = असल((fs_ratios[1] * params_rate(params))
		       - wm8995->aअगरclk[dai->id]);
	क्रम (i = 2; i < ARRAY_SIZE(fs_ratios); i++) अणु
		cur_val = असल((fs_ratios[i] * params_rate(params))
			      - wm8995->aअगरclk[dai->id]);
		अगर (cur_val >= best_val)
			जारी;
		best = i;
		best_val = cur_val;
	पूर्ण
	rate_val |= best;

	dev_dbg(dai->dev, "Selected AIF%dCLK/fs = %d\n",
		dai->id + 1, fs_ratios[best]);

	/*
	 * We may not get quite the right frequency अगर using
	 * approximate घड़ीs so look क्रम the बंदst match that is
	 * higher than the target (we need to ensure that there enough
	 * BCLKs to घड़ी out the samples).
	 */
	best = 0;
	bclk = 0;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
		cur_val = (wm8995->aअगरclk[dai->id] * 10 / bclk_भागs[i]) - bclk_rate;
		अगर (cur_val < 0) /* BCLK table is sorted */
			अवरोध;
		best = i;
	पूर्ण
	bclk |= best << WM8995_AIF1_BCLK_DIV_SHIFT;

	bclk_rate = wm8995->aअगरclk[dai->id] * 10 / bclk_भागs[best];
	dev_dbg(dai->dev, "Using BCLK_DIV %d for actual BCLK %dHz\n",
		bclk_भागs[best], bclk_rate);

	lrclk = bclk_rate / params_rate(params);
	dev_dbg(dai->dev, "Using LRCLK rate %d for actual LRCLK %dHz\n",
		lrclk, bclk_rate / lrclk);

	snd_soc_component_update_bits(component, aअगर1_reg,
			    WM8995_AIF1_WL_MASK, aअगर1);
	snd_soc_component_update_bits(component, bclk_reg,
			    WM8995_AIF1_BCLK_DIV_MASK, bclk);
	snd_soc_component_update_bits(component, lrclk_reg,
			    WM8995_AIF1DAC_RATE_MASK, lrclk);
	snd_soc_component_update_bits(component, rate_reg,
			    WM8995_AIF1_SR_MASK |
			    WM8995_AIF1CLK_RATE_MASK, rate_val);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_set_tristate(काष्ठा snd_soc_dai *codec_dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक reg, val, mask;

	चयन (codec_dai->id) अणु
	हाल 0:
		reg = WM8995_AIF1_MASTER_SLAVE;
		mask = WM8995_AIF1_TRI;
		अवरोध;
	हाल 1:
		reg = WM8995_AIF2_MASTER_SLAVE;
		mask = WM8995_AIF2_TRI;
		अवरोध;
	हाल 2:
		reg = WM8995_POWER_MANAGEMENT_5;
		mask = WM8995_AIF3_TRI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tristate)
		val = mask;
	अन्यथा
		val = 0;

	वापस snd_soc_component_update_bits(component, reg, mask, val);
पूर्ण

/* The size in bits of the FLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

काष्ठा fll_भाग अणु
	u16 outभाग;
	u16 n;
	u16 k;
	u16 clk_ref_भाग;
	u16 fll_fratio;
पूर्ण;

अटल पूर्णांक wm8995_get_fll_config(काष्ठा fll_भाग *fll,
				 पूर्णांक freq_in, पूर्णांक freq_out)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;

	pr_debug("FLL input=%dHz, output=%dHz\n", freq_in, freq_out);

	/* Scale the input frequency करोwn to <= 13.5MHz */
	fll->clk_ref_भाग = 0;
	जबतक (freq_in > 13500000) अणु
		fll->clk_ref_भाग++;
		freq_in /= 2;

		अगर (fll->clk_ref_भाग > 3)
			वापस -EINVAL;
	पूर्ण
	pr_debug("CLK_REF_DIV=%d, Fref=%dHz\n", fll->clk_ref_भाग, freq_in);

	/* Scale the output to give 90MHz<=Fvco<=100MHz */
	fll->outभाग = 3;
	जबतक (freq_out * (fll->outभाग + 1) < 90000000) अणु
		fll->outभाग++;
		अगर (fll->outभाग > 63)
			वापस -EINVAL;
	पूर्ण
	freq_out *= fll->outभाग + 1;
	pr_debug("OUTDIV=%d, Fvco=%dHz\n", fll->outभाग, freq_out);

	अगर (freq_in > 1000000) अणु
		fll->fll_fratio = 0;
	पूर्ण अन्यथा अगर (freq_in > 256000) अणु
		fll->fll_fratio = 1;
		freq_in *= 2;
	पूर्ण अन्यथा अगर (freq_in > 128000) अणु
		fll->fll_fratio = 2;
		freq_in *= 4;
	पूर्ण अन्यथा अगर (freq_in > 64000) अणु
		fll->fll_fratio = 3;
		freq_in *= 8;
	पूर्ण अन्यथा अणु
		fll->fll_fratio = 4;
		freq_in *= 16;
	पूर्ण
	pr_debug("FLL_FRATIO=%d, Fref=%dHz\n", fll->fll_fratio, freq_in);

	/* Now, calculate N.K */
	Nभाग = freq_out / freq_in;

	fll->n = Nभाग;
	Nmod = freq_out % freq_in;
	pr_debug("Nmod=%d\n", Nmod);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, freq_in);

	K = Kpart & 0xFFFFFFFF;

	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	fll->k = K / 10;

	pr_debug("N=%x K=%x\n", fll->n, fll->k);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_set_fll(काष्ठा snd_soc_dai *dai, पूर्णांक id,
			  पूर्णांक src, अचिन्हित पूर्णांक freq_in,
			  अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक reg_offset, ret;
	काष्ठा fll_भाग fll;
	u16 reg, aअगर1, aअगर2;

	component = dai->component;
	wm8995 = snd_soc_component_get_drvdata(component);

	aअगर1 = snd_soc_component_पढ़ो(component, WM8995_AIF1_CLOCKING_1)
	       & WM8995_AIF1CLK_ENA;

	aअगर2 = snd_soc_component_पढ़ो(component, WM8995_AIF2_CLOCKING_1)
	       & WM8995_AIF2CLK_ENA;

	चयन (id) अणु
	हाल WM8995_FLL1:
		reg_offset = 0;
		id = 0;
		अवरोध;
	हाल WM8995_FLL2:
		reg_offset = 0x20;
		id = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (src) अणु
	हाल 0:
		/* Allow no source specअगरication when stopping */
		अगर (freq_out)
			वापस -EINVAL;
		अवरोध;
	हाल WM8995_FLL_SRC_MCLK1:
	हाल WM8995_FLL_SRC_MCLK2:
	हाल WM8995_FLL_SRC_LRCLK:
	हाल WM8995_FLL_SRC_BCLK:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Are we changing anything? */
	अगर (wm8995->fll[id].src == src &&
	    wm8995->fll[id].in == freq_in && wm8995->fll[id].out == freq_out)
		वापस 0;

	/* If we're stopping the FLL reकरो the old config - no
	 * रेजिस्टरs will actually be written but we aव्योम GCC flow
	 * analysis bugs spewing warnings.
	 */
	अगर (freq_out)
		ret = wm8995_get_fll_config(&fll, freq_in, freq_out);
	अन्यथा
		ret = wm8995_get_fll_config(&fll, wm8995->fll[id].in,
					    wm8995->fll[id].out);
	अगर (ret < 0)
		वापस ret;

	/* Gate the AIF घड़ीs जबतक we reघड़ी */
	snd_soc_component_update_bits(component, WM8995_AIF1_CLOCKING_1,
			    WM8995_AIF1CLK_ENA_MASK, 0);
	snd_soc_component_update_bits(component, WM8995_AIF2_CLOCKING_1,
			    WM8995_AIF2CLK_ENA_MASK, 0);

	/* We always need to disable the FLL जबतक reconfiguring */
	snd_soc_component_update_bits(component, WM8995_FLL1_CONTROL_1 + reg_offset,
			    WM8995_FLL1_ENA_MASK, 0);

	reg = (fll.outभाग << WM8995_FLL1_OUTDIV_SHIFT) |
	      (fll.fll_fratio << WM8995_FLL1_FRATIO_SHIFT);
	snd_soc_component_update_bits(component, WM8995_FLL1_CONTROL_2 + reg_offset,
			    WM8995_FLL1_OUTDIV_MASK |
			    WM8995_FLL1_FRATIO_MASK, reg);

	snd_soc_component_ग_लिखो(component, WM8995_FLL1_CONTROL_3 + reg_offset, fll.k);

	snd_soc_component_update_bits(component, WM8995_FLL1_CONTROL_4 + reg_offset,
			    WM8995_FLL1_N_MASK,
			    fll.n << WM8995_FLL1_N_SHIFT);

	snd_soc_component_update_bits(component, WM8995_FLL1_CONTROL_5 + reg_offset,
			    WM8995_FLL1_REFCLK_DIV_MASK |
			    WM8995_FLL1_REFCLK_SRC_MASK,
			    (fll.clk_ref_भाग << WM8995_FLL1_REFCLK_DIV_SHIFT) |
			    (src - 1));

	अगर (freq_out)
		snd_soc_component_update_bits(component, WM8995_FLL1_CONTROL_1 + reg_offset,
				    WM8995_FLL1_ENA_MASK, WM8995_FLL1_ENA);

	wm8995->fll[id].in = freq_in;
	wm8995->fll[id].out = freq_out;
	wm8995->fll[id].src = src;

	/* Enable any gated AIF घड़ीs */
	snd_soc_component_update_bits(component, WM8995_AIF1_CLOCKING_1,
			    WM8995_AIF1CLK_ENA_MASK, aअगर1);
	snd_soc_component_update_bits(component, WM8995_AIF2_CLOCKING_1,
			    WM8995_AIF2CLK_ENA_MASK, aअगर2);

	configure_घड़ी(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8995_priv *wm8995;

	component = dai->component;
	wm8995 = snd_soc_component_get_drvdata(component);

	चयन (dai->id) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	शेष:
		/* AIF3 shares घड़ीing with AIF1/2 */
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल WM8995_SYSCLK_MCLK1:
		wm8995->sysclk[dai->id] = WM8995_SYSCLK_MCLK1;
		wm8995->mclk[0] = freq;
		dev_dbg(dai->dev, "AIF%d using MCLK1 at %uHz\n",
			dai->id + 1, freq);
		अवरोध;
	हाल WM8995_SYSCLK_MCLK2:
		wm8995->sysclk[dai->id] = WM8995_SYSCLK_MCLK2;
		wm8995->mclk[1] = freq;
		dev_dbg(dai->dev, "AIF%d using MCLK2 at %uHz\n",
			dai->id + 1, freq);
		अवरोध;
	हाल WM8995_SYSCLK_FLL1:
		wm8995->sysclk[dai->id] = WM8995_SYSCLK_FLL1;
		dev_dbg(dai->dev, "AIF%d using FLL1\n", dai->id + 1);
		अवरोध;
	हाल WM8995_SYSCLK_FLL2:
		wm8995->sysclk[dai->id] = WM8995_SYSCLK_FLL2;
		dev_dbg(dai->dev, "AIF%d using FLL2\n", dai->id + 1);
		अवरोध;
	हाल WM8995_SYSCLK_OPCLK:
	शेष:
		dev_err(dai->dev, "Unknown clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	configure_घड़ी(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक ret;

	wm8995 = snd_soc_component_get_drvdata(component);
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8995->supplies),
						    wm8995->supplies);
			अगर (ret)
				वापस ret;

			ret = regcache_sync(wm8995->regmap);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण

			snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
					    WM8995_BG_ENA_MASK, WM8995_BG_ENA);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_BG_ENA_MASK, 0);
		regulator_bulk_disable(ARRAY_SIZE(wm8995->supplies),
				       wm8995->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8995_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक i;
	पूर्णांक ret;

	wm8995 = snd_soc_component_get_drvdata(component);
	wm8995->component = component;

	क्रम (i = 0; i < ARRAY_SIZE(wm8995->supplies); i++)
		wm8995->supplies[i].supply = wm8995_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev,
				      ARRAY_SIZE(wm8995->supplies),
				      wm8995->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8995->disable_nb[0].notअगरier_call = wm8995_regulator_event_0;
	wm8995->disable_nb[1].notअगरier_call = wm8995_regulator_event_1;
	wm8995->disable_nb[2].notअगरier_call = wm8995_regulator_event_2;
	wm8995->disable_nb[3].notअगरier_call = wm8995_regulator_event_3;
	wm8995->disable_nb[4].notअगरier_call = wm8995_regulator_event_4;
	wm8995->disable_nb[5].notअगरier_call = wm8995_regulator_event_5;
	wm8995->disable_nb[6].notअगरier_call = wm8995_regulator_event_6;
	wm8995->disable_nb[7].notअगरier_call = wm8995_regulator_event_7;

	/* This should really be moved पूर्णांकo the regulator core */
	क्रम (i = 0; i < ARRAY_SIZE(wm8995->supplies); i++) अणु
		ret = devm_regulator_रेजिस्टर_notअगरier(
						wm8995->supplies[i].consumer,
						&wm8995->disable_nb[i]);
		अगर (ret) अणु
			dev_err(component->dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8995->supplies),
				    wm8995->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_पढ़ो(component, WM8995_SOFTWARE_RESET);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to read device ID: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	अगर (ret != 0x8995) अणु
		dev_err(component->dev, "Invalid device ID: %#x\n", ret);
		ret = -EINVAL;
		जाओ err_reg_enable;
	पूर्ण

	ret = snd_soc_component_ग_लिखो(component, WM8995_SOFTWARE_RESET, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	/* Latch volume updates (right only; we always करो left then right). */
	snd_soc_component_update_bits(component, WM8995_AIF1_DAC1_RIGHT_VOLUME,
			    WM8995_AIF1DAC1_VU_MASK, WM8995_AIF1DAC1_VU);
	snd_soc_component_update_bits(component, WM8995_AIF1_DAC2_RIGHT_VOLUME,
			    WM8995_AIF1DAC2_VU_MASK, WM8995_AIF1DAC2_VU);
	snd_soc_component_update_bits(component, WM8995_AIF2_DAC_RIGHT_VOLUME,
			    WM8995_AIF2DAC_VU_MASK, WM8995_AIF2DAC_VU);
	snd_soc_component_update_bits(component, WM8995_AIF1_ADC1_RIGHT_VOLUME,
			    WM8995_AIF1ADC1_VU_MASK, WM8995_AIF1ADC1_VU);
	snd_soc_component_update_bits(component, WM8995_AIF1_ADC2_RIGHT_VOLUME,
			    WM8995_AIF1ADC2_VU_MASK, WM8995_AIF1ADC2_VU);
	snd_soc_component_update_bits(component, WM8995_AIF2_ADC_RIGHT_VOLUME,
			    WM8995_AIF2ADC_VU_MASK, WM8995_AIF1ADC2_VU);
	snd_soc_component_update_bits(component, WM8995_DAC1_RIGHT_VOLUME,
			    WM8995_DAC1_VU_MASK, WM8995_DAC1_VU);
	snd_soc_component_update_bits(component, WM8995_DAC2_RIGHT_VOLUME,
			    WM8995_DAC2_VU_MASK, WM8995_DAC2_VU);
	snd_soc_component_update_bits(component, WM8995_RIGHT_LINE_INPUT_1_VOLUME,
			    WM8995_IN1_VU_MASK, WM8995_IN1_VU);

	wm8995_update_class_w(component);

	वापस 0;

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8995->supplies), wm8995->supplies);
	वापस ret;
पूर्ण

#घोषणा WM8995_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8995_aअगर1_dai_ops = अणु
	.set_sysclk = wm8995_set_dai_sysclk,
	.set_fmt = wm8995_set_dai_fmt,
	.hw_params = wm8995_hw_params,
	.mute_stream = wm8995_aअगर_mute,
	.set_pll = wm8995_set_fll,
	.set_tristate = wm8995_set_tristate,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8995_aअगर2_dai_ops = अणु
	.set_sysclk = wm8995_set_dai_sysclk,
	.set_fmt = wm8995_set_dai_fmt,
	.hw_params = wm8995_hw_params,
	.mute_stream = wm8995_aअगर_mute,
	.set_pll = wm8995_set_fll,
	.set_tristate = wm8995_set_tristate,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8995_aअगर3_dai_ops = अणु
	.set_tristate = wm8995_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8995_dai[] = अणु
	अणु
		.name = "wm8995-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.ops = &wm8995_aअगर1_dai_ops
	पूर्ण,
	अणु
		.name = "wm8995-aif2",
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.ops = &wm8995_aअगर2_dai_ops
	पूर्ण,
	अणु
		.name = "wm8995-aif3",
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = WM8995_FORMATS
		पूर्ण,
		.ops = &wm8995_aअगर3_dai_ops
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8995 = अणु
	.probe			= wm8995_probe,
	.set_bias_level		= wm8995_set_bias_level,
	.controls		= wm8995_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8995_snd_controls),
	.dapm_widमाला_लो		= wm8995_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8995_dapm_widमाला_लो),
	.dapm_routes		= wm8995_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8995_पूर्णांकercon),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8995_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.max_रेजिस्टर = WM8995_MAX_REGISTER,
	.reg_शेषs = wm8995_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8995_reg_शेषs),
	.अस्थिर_reg = wm8995_अस्थिर,
	.पढ़ोable_reg = wm8995_पढ़ोable,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8995_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक ret;

	wm8995 = devm_kzalloc(&spi->dev, माप(*wm8995), GFP_KERNEL);
	अगर (!wm8995)
		वापस -ENOMEM;

	spi_set_drvdata(spi, wm8995);

	wm8995->regmap = devm_regmap_init_spi(spi, &wm8995_regmap);
	अगर (IS_ERR(wm8995->regmap)) अणु
		ret = PTR_ERR(wm8995->regmap);
		dev_err(&spi->dev, "Failed to register regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				     &soc_component_dev_wm8995, wm8995_dai,
				     ARRAY_SIZE(wm8995_dai));
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8995_spi_driver = अणु
	.driver = अणु
		.name = "wm8995",
	पूर्ण,
	.probe = wm8995_spi_probe,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8995_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8995_priv *wm8995;
	पूर्णांक ret;

	wm8995 = devm_kzalloc(&i2c->dev, माप(*wm8995), GFP_KERNEL);
	अगर (!wm8995)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8995);

	wm8995->regmap = devm_regmap_init_i2c(i2c, &wm8995_regmap);
	अगर (IS_ERR(wm8995->regmap)) अणु
		ret = PTR_ERR(wm8995->regmap);
		dev_err(&i2c->dev, "Failed to register regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_wm8995, wm8995_dai,
				     ARRAY_SIZE(wm8995_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8995_i2c_id[] = अणु
	अणु"wm8995", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, wm8995_i2c_id);

अटल काष्ठा i2c_driver wm8995_i2c_driver = अणु
	.driver = अणु
		.name = "wm8995",
	पूर्ण,
	.probe = wm8995_i2c_probe,
	.id_table = wm8995_i2c_id
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8995_modinit(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8995_i2c_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8995 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8995_spi_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8995 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

module_init(wm8995_modinit);

अटल व्योम __निकास wm8995_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8995_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8995_spi_driver);
#पूर्ण_अगर
पूर्ण

module_निकास(wm8995_निकास);

MODULE_DESCRIPTION("ASoC WM8995 driver");
MODULE_AUTHOR("Dimitris Papastamos <dp@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
