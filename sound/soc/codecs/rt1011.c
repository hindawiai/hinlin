<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rt1011.c -- rt1011 ALSA SoC amplअगरier component driver
 *
 * Copyright(c) 2019 Realtek Semiconductor Corp.
 *
 * Author: Shuming Fan <shumingf@realtek.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt1011.h"

अटल पूर्णांक rt1011_calibrate(काष्ठा rt1011_priv *rt1011,
	अचिन्हित अक्षर cali_flag);

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु

	अणु RT1011_POWER_9, 0xa840 पूर्ण,

	अणु RT1011_ADC_SET_5, 0x0a20 पूर्ण,
	अणु RT1011_DAC_SET_2, 0xa032 पूर्ण,

	अणु RT1011_SPK_PRO_DC_DET_1, 0xb00c पूर्ण,
	अणु RT1011_SPK_PRO_DC_DET_2, 0xcccc पूर्ण,

	अणु RT1011_A_TIMING_1, 0x6054 पूर्ण,

	अणु RT1011_POWER_7, 0x3e55 पूर्ण,
	अणु RT1011_POWER_8, 0x0520 पूर्ण,
	अणु RT1011_BOOST_CON_1, 0xe188 पूर्ण,
	अणु RT1011_POWER_4, 0x16f2 पूर्ण,

	अणु RT1011_CROSS_BQ_SET_1, 0x0004 पूर्ण,
	अणु RT1011_SIL_DET, 0xc313 पूर्ण,
	अणु RT1011_SINE_GEN_REG_1, 0x0707 पूर्ण,

	अणु RT1011_DC_CALIB_CLASSD_3, 0xcb00 पूर्ण,

	अणु RT1011_DAC_SET_1, 0xe702 पूर्ण,
	अणु RT1011_DAC_SET_3, 0x2004 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt1011_reg[] = अणु
	अणु0x0000, 0x0000पूर्ण,
	अणु0x0002, 0x0000पूर्ण,
	अणु0x0004, 0xa000पूर्ण,
	अणु0x0006, 0x0000पूर्ण,
	अणु0x0008, 0x0003पूर्ण,
	अणु0x000a, 0x087eपूर्ण,
	अणु0x000c, 0x0020पूर्ण,
	अणु0x000e, 0x9002पूर्ण,
	अणु0x0010, 0x0000पूर्ण,
	अणु0x0012, 0x0000पूर्ण,
	अणु0x0020, 0x0c40पूर्ण,
	अणु0x0022, 0x4313पूर्ण,
	अणु0x0076, 0x0000पूर्ण,
	अणु0x0078, 0x0000पूर्ण,
	अणु0x007a, 0x0000पूर्ण,
	अणु0x007c, 0x10ecपूर्ण,
	अणु0x007d, 0x1011पूर्ण,
	अणु0x00f0, 0x5000पूर्ण,
	अणु0x00f2, 0x0374पूर्ण,
	अणु0x00f3, 0x0000पूर्ण,
	अणु0x00f4, 0x0000पूर्ण,
	अणु0x0100, 0x0038पूर्ण,
	अणु0x0102, 0xff02पूर्ण,
	अणु0x0104, 0x0232पूर्ण,
	अणु0x0106, 0x200cपूर्ण,
	अणु0x0107, 0x0000पूर्ण,
	अणु0x0108, 0x2f2fपूर्ण,
	अणु0x010a, 0x2f2fपूर्ण,
	अणु0x010c, 0x002fपूर्ण,
	अणु0x010e, 0xe000पूर्ण,
	अणु0x0110, 0x0820पूर्ण,
	अणु0x0111, 0x4010पूर्ण,
	अणु0x0112, 0x0000पूर्ण,
	अणु0x0114, 0x0000पूर्ण,
	अणु0x0116, 0x0000पूर्ण,
	अणु0x0118, 0x0000पूर्ण,
	अणु0x011a, 0x0101पूर्ण,
	अणु0x011c, 0x4567पूर्ण,
	अणु0x011e, 0x0000पूर्ण,
	अणु0x0120, 0x0000पूर्ण,
	अणु0x0122, 0x0000पूर्ण,
	अणु0x0124, 0x0123पूर्ण,
	अणु0x0126, 0x4567पूर्ण,
	अणु0x0200, 0x0000पूर्ण,
	अणु0x0300, 0xffddपूर्ण,
	अणु0x0302, 0x001eपूर्ण,
	अणु0x0311, 0x0000पूर्ण,
	अणु0x0313, 0x5254पूर्ण,
	अणु0x0314, 0x0062पूर्ण,
	अणु0x0316, 0x7f40पूर्ण,
	अणु0x0319, 0x000fपूर्ण,
	अणु0x031a, 0xffffपूर्ण,
	अणु0x031b, 0x0000पूर्ण,
	अणु0x031c, 0x009fपूर्ण,
	अणु0x031d, 0xffffपूर्ण,
	अणु0x031e, 0x0000पूर्ण,
	अणु0x031f, 0x0000पूर्ण,
	अणु0x0320, 0xe31cपूर्ण,
	अणु0x0321, 0x0000पूर्ण,
	अणु0x0322, 0x0000पूर्ण,
	अणु0x0324, 0x0000पूर्ण,
	अणु0x0326, 0x0002पूर्ण,
	अणु0x0328, 0x20b2पूर्ण,
	अणु0x0329, 0x0175पूर्ण,
	अणु0x032a, 0x32adपूर्ण,
	अणु0x032b, 0x3455पूर्ण,
	अणु0x032c, 0x0528पूर्ण,
	अणु0x032d, 0xa800पूर्ण,
	अणु0x032e, 0x030eपूर्ण,
	अणु0x0330, 0x2080पूर्ण,
	अणु0x0332, 0x0034पूर्ण,
	अणु0x0334, 0x0000पूर्ण,
	अणु0x0508, 0x0010पूर्ण,
	अणु0x050a, 0x0018पूर्ण,
	अणु0x050c, 0x0000पूर्ण,
	अणु0x050d, 0xffffपूर्ण,
	अणु0x050e, 0x1f1fपूर्ण,
	अणु0x050f, 0x04ffपूर्ण,
	अणु0x0510, 0x4020पूर्ण,
	अणु0x0511, 0x01f0पूर्ण,
	अणु0x0512, 0x0702पूर्ण,
	अणु0x0516, 0xbb80पूर्ण,
	अणु0x0517, 0xffffपूर्ण,
	अणु0x0518, 0xffffपूर्ण,
	अणु0x0519, 0x307fपूर्ण,
	अणु0x051a, 0xffffपूर्ण,
	अणु0x051b, 0x0000पूर्ण,
	अणु0x051c, 0x0000पूर्ण,
	अणु0x051d, 0x2000पूर्ण,
	अणु0x051e, 0x0000पूर्ण,
	अणु0x051f, 0x0000पूर्ण,
	अणु0x0520, 0x0000पूर्ण,
	अणु0x0521, 0x1001पूर्ण,
	अणु0x0522, 0x7fffपूर्ण,
	अणु0x0524, 0x7fffपूर्ण,
	अणु0x0526, 0x0000पूर्ण,
	अणु0x0528, 0x0000पूर्ण,
	अणु0x052a, 0x0000पूर्ण,
	अणु0x0530, 0x0401पूर्ण,
	अणु0x0532, 0x3000पूर्ण,
	अणु0x0534, 0x0000पूर्ण,
	अणु0x0535, 0xffffपूर्ण,
	अणु0x0536, 0x101cपूर्ण,
	अणु0x0538, 0x1814पूर्ण,
	अणु0x053a, 0x100cपूर्ण,
	अणु0x053c, 0x0804पूर्ण,
	अणु0x053d, 0x0000पूर्ण,
	अणु0x053e, 0x0000पूर्ण,
	अणु0x053f, 0x0000पूर्ण,
	अणु0x0540, 0x0000पूर्ण,
	अणु0x0541, 0x0000पूर्ण,
	अणु0x0542, 0x0000पूर्ण,
	अणु0x0543, 0x0000पूर्ण,
	अणु0x0544, 0x001cपूर्ण,
	अणु0x0545, 0x1814पूर्ण,
	अणु0x0546, 0x100cपूर्ण,
	अणु0x0547, 0x0804पूर्ण,
	अणु0x0548, 0x0000पूर्ण,
	अणु0x0549, 0x0000पूर्ण,
	अणु0x054a, 0x0000पूर्ण,
	अणु0x054b, 0x0000पूर्ण,
	अणु0x054c, 0x0000पूर्ण,
	अणु0x054d, 0x0000पूर्ण,
	अणु0x054e, 0x0000पूर्ण,
	अणु0x054f, 0x0000पूर्ण,
	अणु0x0566, 0x0000पूर्ण,
	अणु0x0568, 0x20f1पूर्ण,
	अणु0x056a, 0x0007पूर्ण,
	अणु0x0600, 0x9d00पूर्ण,
	अणु0x0611, 0x2000पूर्ण,
	अणु0x0612, 0x505fपूर्ण,
	अणु0x0613, 0x0444पूर्ण,
	अणु0x0614, 0x4000पूर्ण,
	अणु0x0615, 0x4004पूर्ण,
	अणु0x0616, 0x0606पूर्ण,
	अणु0x0617, 0x8904पूर्ण,
	अणु0x0618, 0xe021पूर्ण,
	अणु0x0621, 0x2000पूर्ण,
	अणु0x0622, 0x505fपूर्ण,
	अणु0x0623, 0x0444पूर्ण,
	अणु0x0624, 0x4000पूर्ण,
	अणु0x0625, 0x4004पूर्ण,
	अणु0x0626, 0x0606पूर्ण,
	अणु0x0627, 0x8704पूर्ण,
	अणु0x0628, 0xe021पूर्ण,
	अणु0x0631, 0x2000पूर्ण,
	अणु0x0632, 0x517fपूर्ण,
	अणु0x0633, 0x0440पूर्ण,
	अणु0x0634, 0x4000पूर्ण,
	अणु0x0635, 0x4104पूर्ण,
	अणु0x0636, 0x0306पूर्ण,
	अणु0x0637, 0x8904पूर्ण,
	अणु0x0638, 0xe021पूर्ण,
	अणु0x0702, 0x0014पूर्ण,
	अणु0x0704, 0x0000पूर्ण,
	अणु0x0706, 0x0014पूर्ण,
	अणु0x0708, 0x0000पूर्ण,
	अणु0x070a, 0x0000पूर्ण,
	अणु0x0710, 0x0200पूर्ण,
	अणु0x0711, 0x0000पूर्ण,
	अणु0x0712, 0x0200पूर्ण,
	अणु0x0713, 0x0000पूर्ण,
	अणु0x0720, 0x0200पूर्ण,
	अणु0x0721, 0x0000पूर्ण,
	अणु0x0722, 0x0000पूर्ण,
	अणु0x0723, 0x0000पूर्ण,
	अणु0x0724, 0x0000पूर्ण,
	अणु0x0725, 0x0000पूर्ण,
	अणु0x0726, 0x0000पूर्ण,
	अणु0x0727, 0x0000पूर्ण,
	अणु0x0728, 0x0000पूर्ण,
	अणु0x0729, 0x0000पूर्ण,
	अणु0x0730, 0x0200पूर्ण,
	अणु0x0731, 0x0000पूर्ण,
	अणु0x0732, 0x0000पूर्ण,
	अणु0x0733, 0x0000पूर्ण,
	अणु0x0734, 0x0000पूर्ण,
	अणु0x0735, 0x0000पूर्ण,
	अणु0x0736, 0x0000पूर्ण,
	अणु0x0737, 0x0000पूर्ण,
	अणु0x0738, 0x0000पूर्ण,
	अणु0x0739, 0x0000पूर्ण,
	अणु0x0740, 0x0200पूर्ण,
	अणु0x0741, 0x0000पूर्ण,
	अणु0x0742, 0x0000पूर्ण,
	अणु0x0743, 0x0000पूर्ण,
	अणु0x0744, 0x0000पूर्ण,
	अणु0x0745, 0x0000पूर्ण,
	अणु0x0746, 0x0000पूर्ण,
	अणु0x0747, 0x0000पूर्ण,
	अणु0x0748, 0x0000पूर्ण,
	अणु0x0749, 0x0000पूर्ण,
	अणु0x0750, 0x0200पूर्ण,
	अणु0x0751, 0x0000पूर्ण,
	अणु0x0752, 0x0000पूर्ण,
	अणु0x0753, 0x0000पूर्ण,
	अणु0x0754, 0x0000पूर्ण,
	अणु0x0755, 0x0000पूर्ण,
	अणु0x0756, 0x0000पूर्ण,
	अणु0x0757, 0x0000पूर्ण,
	अणु0x0758, 0x0000पूर्ण,
	अणु0x0759, 0x0000पूर्ण,
	अणु0x0760, 0x0200पूर्ण,
	अणु0x0761, 0x0000पूर्ण,
	अणु0x0762, 0x0000पूर्ण,
	अणु0x0763, 0x0000पूर्ण,
	अणु0x0764, 0x0000पूर्ण,
	अणु0x0765, 0x0000पूर्ण,
	अणु0x0766, 0x0000पूर्ण,
	अणु0x0767, 0x0000पूर्ण,
	अणु0x0768, 0x0000पूर्ण,
	अणु0x0769, 0x0000पूर्ण,
	अणु0x0770, 0x0200पूर्ण,
	अणु0x0771, 0x0000पूर्ण,
	अणु0x0772, 0x0000पूर्ण,
	अणु0x0773, 0x0000पूर्ण,
	अणु0x0774, 0x0000पूर्ण,
	अणु0x0775, 0x0000पूर्ण,
	अणु0x0776, 0x0000पूर्ण,
	अणु0x0777, 0x0000पूर्ण,
	अणु0x0778, 0x0000पूर्ण,
	अणु0x0779, 0x0000पूर्ण,
	अणु0x0780, 0x0200पूर्ण,
	अणु0x0781, 0x0000पूर्ण,
	अणु0x0782, 0x0000पूर्ण,
	अणु0x0783, 0x0000पूर्ण,
	अणु0x0784, 0x0000पूर्ण,
	अणु0x0785, 0x0000पूर्ण,
	अणु0x0786, 0x0000पूर्ण,
	अणु0x0787, 0x0000पूर्ण,
	अणु0x0788, 0x0000पूर्ण,
	अणु0x0789, 0x0000पूर्ण,
	अणु0x0790, 0x0200पूर्ण,
	अणु0x0791, 0x0000पूर्ण,
	अणु0x0792, 0x0000पूर्ण,
	अणु0x0793, 0x0000पूर्ण,
	अणु0x0794, 0x0000पूर्ण,
	अणु0x0795, 0x0000पूर्ण,
	अणु0x0796, 0x0000पूर्ण,
	अणु0x0797, 0x0000पूर्ण,
	अणु0x0798, 0x0000पूर्ण,
	अणु0x0799, 0x0000पूर्ण,
	अणु0x07a0, 0x0200पूर्ण,
	अणु0x07a1, 0x0000पूर्ण,
	अणु0x07a2, 0x0000पूर्ण,
	अणु0x07a3, 0x0000पूर्ण,
	अणु0x07a4, 0x0000पूर्ण,
	अणु0x07a5, 0x0000पूर्ण,
	अणु0x07a6, 0x0000पूर्ण,
	अणु0x07a7, 0x0000पूर्ण,
	अणु0x07a8, 0x0000पूर्ण,
	अणु0x07a9, 0x0000पूर्ण,
	अणु0x07b0, 0x0200पूर्ण,
	अणु0x07b1, 0x0000पूर्ण,
	अणु0x07b2, 0x0000पूर्ण,
	अणु0x07b3, 0x0000पूर्ण,
	अणु0x07b4, 0x0000पूर्ण,
	अणु0x07b5, 0x0000पूर्ण,
	अणु0x07b6, 0x0000पूर्ण,
	अणु0x07b7, 0x0000पूर्ण,
	अणु0x07b8, 0x0000पूर्ण,
	अणु0x07b9, 0x0000पूर्ण,
	अणु0x07c0, 0x0200पूर्ण,
	अणु0x07c1, 0x0000पूर्ण,
	अणु0x07c2, 0x0000पूर्ण,
	अणु0x07c3, 0x0000पूर्ण,
	अणु0x07c4, 0x0000पूर्ण,
	अणु0x07c5, 0x0000पूर्ण,
	अणु0x07c6, 0x0000पूर्ण,
	अणु0x07c7, 0x0000पूर्ण,
	अणु0x07c8, 0x0000पूर्ण,
	अणु0x07c9, 0x0000पूर्ण,
	अणु0x1000, 0x4040पूर्ण,
	अणु0x1002, 0x6505पूर्ण,
	अणु0x1004, 0x5405पूर्ण,
	अणु0x1006, 0x5555पूर्ण,
	अणु0x1007, 0x003fपूर्ण,
	अणु0x1008, 0x7fd7पूर्ण,
	अणु0x1009, 0x770fपूर्ण,
	अणु0x100a, 0xfffeपूर्ण,
	अणु0x100b, 0xe000पूर्ण,
	अणु0x100c, 0x0000पूर्ण,
	अणु0x100d, 0x0007पूर्ण,
	अणु0x1010, 0xa433पूर्ण,
	अणु0x1020, 0x0000पूर्ण,
	अणु0x1022, 0x0000पूर्ण,
	अणु0x1024, 0x0000पूर्ण,
	अणु0x1200, 0x5a01पूर्ण,
	अणु0x1202, 0x6324पूर्ण,
	अणु0x1204, 0x0b00पूर्ण,
	अणु0x1206, 0x0000पूर्ण,
	अणु0x1208, 0x0000पूर्ण,
	अणु0x120a, 0x0024पूर्ण,
	अणु0x120c, 0x0000पूर्ण,
	अणु0x120e, 0x000eपूर्ण,
	अणु0x1210, 0x0000पूर्ण,
	अणु0x1212, 0x0000पूर्ण,
	अणु0x1300, 0x0701पूर्ण,
	अणु0x1302, 0x12f9पूर्ण,
	अणु0x1304, 0x3405पूर्ण,
	अणु0x1305, 0x0844पूर्ण,
	अणु0x1306, 0x5611पूर्ण,
	अणु0x1308, 0x555eपूर्ण,
	अणु0x130a, 0xa605पूर्ण,
	अणु0x130c, 0x2000पूर्ण,
	अणु0x130e, 0x0000पूर्ण,
	अणु0x130f, 0x0001पूर्ण,
	अणु0x1310, 0xaa48पूर्ण,
	अणु0x1312, 0x0285पूर्ण,
	अणु0x1314, 0xaaaaपूर्ण,
	अणु0x1316, 0xaaa0पूर्ण,
	अणु0x1318, 0x2aaaपूर्ण,
	अणु0x131a, 0xaa07पूर्ण,
	अणु0x1322, 0x0029पूर्ण,
	अणु0x1323, 0x4a52पूर्ण,
	अणु0x1324, 0x002cपूर्ण,
	अणु0x1325, 0x0b02पूर्ण,
	अणु0x1326, 0x002dपूर्ण,
	अणु0x1327, 0x6b5aपूर्ण,
	अणु0x1328, 0x002eपूर्ण,
	अणु0x1329, 0xcbb2पूर्ण,
	अणु0x132a, 0x0030पूर्ण,
	अणु0x132b, 0x2c0bपूर्ण,
	अणु0x1330, 0x0031पूर्ण,
	अणु0x1331, 0x8c63पूर्ण,
	अणु0x1332, 0x0032पूर्ण,
	अणु0x1333, 0xecbbपूर्ण,
	अणु0x1334, 0x0034पूर्ण,
	अणु0x1335, 0x4d13पूर्ण,
	अणु0x1336, 0x0037पूर्ण,
	अणु0x1337, 0x0dc3पूर्ण,
	अणु0x1338, 0x003dपूर्ण,
	अणु0x1339, 0xef7bपूर्ण,
	अणु0x133a, 0x0044पूर्ण,
	अणु0x133b, 0xd134पूर्ण,
	अणु0x133c, 0x0047पूर्ण,
	अणु0x133d, 0x91e4पूर्ण,
	अणु0x133e, 0x004dपूर्ण,
	अणु0x133f, 0xc370पूर्ण,
	अणु0x1340, 0x0053पूर्ण,
	अणु0x1341, 0xf4fdपूर्ण,
	अणु0x1342, 0x0060पूर्ण,
	अणु0x1343, 0x5816पूर्ण,
	अणु0x1344, 0x006cपूर्ण,
	अणु0x1345, 0xbb2eपूर्ण,
	अणु0x1346, 0x0072पूर्ण,
	अणु0x1347, 0xecbbपूर्ण,
	अणु0x1348, 0x0076पूर्ण,
	अणु0x1349, 0x5d97पूर्ण,
	अणु0x1500, 0x0702पूर्ण,
	अणु0x1502, 0x002fपूर्ण,
	अणु0x1504, 0x0000पूर्ण,
	अणु0x1510, 0x0064पूर्ण,
	अणु0x1512, 0x0000पूर्ण,
	अणु0x1514, 0xdf47पूर्ण,
	अणु0x1516, 0x079cपूर्ण,
	अणु0x1518, 0xfbf5पूर्ण,
	अणु0x151a, 0x00bcपूर्ण,
	अणु0x151c, 0x3b85पूर्ण,
	अणु0x151e, 0x02b3पूर्ण,
	अणु0x1520, 0x3333पूर्ण,
	अणु0x1522, 0x0000पूर्ण,
	अणु0x1524, 0x4000पूर्ण,
	अणु0x1528, 0x0064पूर्ण,
	अणु0x152a, 0x0000पूर्ण,
	अणु0x152c, 0x0000पूर्ण,
	अणु0x152e, 0x0000पूर्ण,
	अणु0x1530, 0x0000पूर्ण,
	अणु0x1532, 0x0000पूर्ण,
	अणु0x1534, 0x0000पूर्ण,
	अणु0x1536, 0x0000पूर्ण,
	अणु0x1538, 0x0040पूर्ण,
	अणु0x1539, 0x0000पूर्ण,
	अणु0x153a, 0x0040पूर्ण,
	अणु0x153b, 0x0000पूर्ण,
	अणु0x153c, 0x0064पूर्ण,
	अणु0x153e, 0x0bf9पूर्ण,
	अणु0x1540, 0xb2a9पूर्ण,
	अणु0x1544, 0x0200पूर्ण,
	अणु0x1546, 0x0000पूर्ण,
	अणु0x1548, 0x00caपूर्ण,
	अणु0x1552, 0x03ffपूर्ण,
	अणु0x1554, 0x017fपूर्ण,
	अणु0x1556, 0x017fपूर्ण,
	अणु0x155a, 0x0000पूर्ण,
	अणु0x155c, 0x0000पूर्ण,
	अणु0x1560, 0x0040पूर्ण,
	अणु0x1562, 0x0000पूर्ण,
	अणु0x1570, 0x03ffपूर्ण,
	अणु0x1571, 0xdcffपूर्ण,
	अणु0x1572, 0x1e00पूर्ण,
	अणु0x1573, 0x224fपूर्ण,
	अणु0x1574, 0x0000पूर्ण,
	अणु0x1575, 0x0000पूर्ण,
	अणु0x1576, 0x1e00पूर्ण,
	अणु0x1577, 0x0000पूर्ण,
	अणु0x1578, 0x0000पूर्ण,
	अणु0x1579, 0x1128पूर्ण,
	अणु0x157a, 0x03ffपूर्ण,
	अणु0x157b, 0xdcffपूर्ण,
	अणु0x157c, 0x1e00पूर्ण,
	अणु0x157d, 0x224fपूर्ण,
	अणु0x157e, 0x0000पूर्ण,
	अणु0x157f, 0x0000पूर्ण,
	अणु0x1580, 0x1e00पूर्ण,
	अणु0x1581, 0x0000पूर्ण,
	अणु0x1582, 0x0000पूर्ण,
	अणु0x1583, 0x1128पूर्ण,
	अणु0x1590, 0x03ffपूर्ण,
	अणु0x1591, 0xdcffपूर्ण,
	अणु0x1592, 0x1e00पूर्ण,
	अणु0x1593, 0x224fपूर्ण,
	अणु0x1594, 0x0000पूर्ण,
	अणु0x1595, 0x0000पूर्ण,
	अणु0x1596, 0x1e00पूर्ण,
	अणु0x1597, 0x0000पूर्ण,
	अणु0x1598, 0x0000पूर्ण,
	अणु0x1599, 0x1128पूर्ण,
	अणु0x159a, 0x03ffपूर्ण,
	अणु0x159b, 0xdcffपूर्ण,
	अणु0x159c, 0x1e00पूर्ण,
	अणु0x159d, 0x224fपूर्ण,
	अणु0x159e, 0x0000पूर्ण,
	अणु0x159f, 0x0000पूर्ण,
	अणु0x15a0, 0x1e00पूर्ण,
	अणु0x15a1, 0x0000पूर्ण,
	अणु0x15a2, 0x0000पूर्ण,
	अणु0x15a3, 0x1128पूर्ण,
	अणु0x15b0, 0x007fपूर्ण,
	अणु0x15b1, 0xffffपूर्ण,
	अणु0x15b2, 0x007fपूर्ण,
	अणु0x15b3, 0xffffपूर्ण,
	अणु0x15b4, 0x007fपूर्ण,
	अणु0x15b5, 0xffffपूर्ण,
	अणु0x15b8, 0x007fपूर्ण,
	अणु0x15b9, 0xffffपूर्ण,
	अणु0x15bc, 0x0000पूर्ण,
	अणु0x15bd, 0x0000पूर्ण,
	अणु0x15be, 0xff00पूर्ण,
	अणु0x15bf, 0x0000पूर्ण,
	अणु0x15c0, 0xff00पूर्ण,
	अणु0x15c1, 0x0000पूर्ण,
	अणु0x15c3, 0xfc00पूर्ण,
	अणु0x15c4, 0xbb80पूर्ण,
	अणु0x15d0, 0x0000पूर्ण,
	अणु0x15d1, 0x0000पूर्ण,
	अणु0x15d2, 0x0000पूर्ण,
	अणु0x15d3, 0x0000पूर्ण,
	अणु0x15d4, 0x0000पूर्ण,
	अणु0x15d5, 0x0000पूर्ण,
	अणु0x15d6, 0x0000पूर्ण,
	अणु0x15d7, 0x0000पूर्ण,
	अणु0x15d8, 0x0200पूर्ण,
	अणु0x15d9, 0x0000पूर्ण,
	अणु0x15da, 0x0000पूर्ण,
	अणु0x15db, 0x0000पूर्ण,
	अणु0x15dc, 0x0000पूर्ण,
	अणु0x15dd, 0x0000पूर्ण,
	अणु0x15de, 0x0000पूर्ण,
	अणु0x15df, 0x0000पूर्ण,
	अणु0x15e0, 0x0000पूर्ण,
	अणु0x15e1, 0x0000पूर्ण,
	अणु0x15e2, 0x0200पूर्ण,
	अणु0x15e3, 0x0000पूर्ण,
	अणु0x15e4, 0x0000पूर्ण,
	अणु0x15e5, 0x0000पूर्ण,
	अणु0x15e6, 0x0000पूर्ण,
	अणु0x15e7, 0x0000पूर्ण,
	अणु0x15e8, 0x0000पूर्ण,
	अणु0x15e9, 0x0000पूर्ण,
	अणु0x15ea, 0x0000पूर्ण,
	अणु0x15eb, 0x0000पूर्ण,
	अणु0x15ec, 0x0200पूर्ण,
	अणु0x15ed, 0x0000पूर्ण,
	अणु0x15ee, 0x0000पूर्ण,
	अणु0x15ef, 0x0000पूर्ण,
	अणु0x15f0, 0x0000पूर्ण,
	अणु0x15f1, 0x0000पूर्ण,
	अणु0x15f2, 0x0000पूर्ण,
	अणु0x15f3, 0x0000पूर्ण,
	अणु0x15f4, 0x0000पूर्ण,
	अणु0x15f5, 0x0000पूर्ण,
	अणु0x15f6, 0x0200पूर्ण,
	अणु0x15f7, 0x0200पूर्ण,
	अणु0x15f8, 0x8200पूर्ण,
	अणु0x15f9, 0x0000पूर्ण,
	अणु0x1600, 0x007dपूर्ण,
	अणु0x1601, 0xa178पूर्ण,
	अणु0x1602, 0x00c2पूर्ण,
	अणु0x1603, 0x5383पूर्ण,
	अणु0x1604, 0x0000पूर्ण,
	अणु0x1605, 0x02c1पूर्ण,
	अणु0x1606, 0x007dपूर्ण,
	अणु0x1607, 0xa178पूर्ण,
	अणु0x1608, 0x00c2पूर्ण,
	अणु0x1609, 0x5383पूर्ण,
	अणु0x160a, 0x003eपूर्ण,
	अणु0x160b, 0xd37dपूर्ण,
	अणु0x1611, 0x3210पूर्ण,
	अणु0x1612, 0x7418पूर्ण,
	अणु0x1613, 0xc0ffपूर्ण,
	अणु0x1614, 0x0000पूर्ण,
	अणु0x1615, 0x00ffपूर्ण,
	अणु0x1616, 0x0000पूर्ण,
	अणु0x1617, 0x0000पूर्ण,
	अणु0x1621, 0x6210पूर्ण,
	अणु0x1622, 0x7418पूर्ण,
	अणु0x1623, 0xc0ffपूर्ण,
	अणु0x1624, 0x0000पूर्ण,
	अणु0x1625, 0x00ffपूर्ण,
	अणु0x1626, 0x0000पूर्ण,
	अणु0x1627, 0x0000पूर्ण,
	अणु0x1631, 0x3a14पूर्ण,
	अणु0x1632, 0x7418पूर्ण,
	अणु0x1633, 0xc3ffपूर्ण,
	अणु0x1634, 0x0000पूर्ण,
	अणु0x1635, 0x00ffपूर्ण,
	अणु0x1636, 0x0000पूर्ण,
	अणु0x1637, 0x0000पूर्ण,
	अणु0x1638, 0x0000पूर्ण,
	अणु0x163a, 0x0000पूर्ण,
	अणु0x163c, 0x0000पूर्ण,
	अणु0x163e, 0x0000पूर्ण,
	अणु0x1640, 0x0000पूर्ण,
	अणु0x1642, 0x0000पूर्ण,
	अणु0x1644, 0x0000पूर्ण,
	अणु0x1646, 0x0000पूर्ण,
	अणु0x1648, 0x0000पूर्ण,
	अणु0x1650, 0x0000पूर्ण,
	अणु0x1652, 0x0000पूर्ण,
	अणु0x1654, 0x0000पूर्ण,
	अणु0x1656, 0x0000पूर्ण,
	अणु0x1658, 0x0000पूर्ण,
	अणु0x1660, 0x0000पूर्ण,
	अणु0x1662, 0x0000पूर्ण,
	अणु0x1664, 0x0000पूर्ण,
	अणु0x1666, 0x0000पूर्ण,
	अणु0x1668, 0x0000पूर्ण,
	अणु0x1670, 0x0000पूर्ण,
	अणु0x1672, 0x0000पूर्ण,
	अणु0x1674, 0x0000पूर्ण,
	अणु0x1676, 0x0000पूर्ण,
	अणु0x1678, 0x0000पूर्ण,
	अणु0x1680, 0x0000पूर्ण,
	अणु0x1682, 0x0000पूर्ण,
	अणु0x1684, 0x0000पूर्ण,
	अणु0x1686, 0x0000पूर्ण,
	अणु0x1688, 0x0000पूर्ण,
	अणु0x1690, 0x0000पूर्ण,
	अणु0x1692, 0x0000पूर्ण,
	अणु0x1694, 0x0000पूर्ण,
	अणु0x1696, 0x0000पूर्ण,
	अणु0x1698, 0x0000पूर्ण,
	अणु0x1700, 0x0000पूर्ण,
	अणु0x1702, 0x0000पूर्ण,
	अणु0x1704, 0x0000पूर्ण,
	अणु0x1706, 0x0000पूर्ण,
	अणु0x1708, 0x0000पूर्ण,
	अणु0x1710, 0x0000पूर्ण,
	अणु0x1712, 0x0000पूर्ण,
	अणु0x1714, 0x0000पूर्ण,
	अणु0x1716, 0x0000पूर्ण,
	अणु0x1718, 0x0000पूर्ण,
	अणु0x1720, 0x0000पूर्ण,
	अणु0x1722, 0x0000पूर्ण,
	अणु0x1724, 0x0000पूर्ण,
	अणु0x1726, 0x0000पूर्ण,
	अणु0x1728, 0x0000पूर्ण,
	अणु0x1730, 0x0000पूर्ण,
	अणु0x1732, 0x0000पूर्ण,
	अणु0x1734, 0x0000पूर्ण,
	अणु0x1736, 0x0000पूर्ण,
	अणु0x1738, 0x0000पूर्ण,
	अणु0x173a, 0x0000पूर्ण,
	अणु0x173c, 0x0000पूर्ण,
	अणु0x173e, 0x0000पूर्ण,
	अणु0x17bb, 0x0500पूर्ण,
	अणु0x17bd, 0x0004पूर्ण,
	अणु0x17bf, 0x0004पूर्ण,
	अणु0x17c1, 0x0004पूर्ण,
	अणु0x17c2, 0x7fffपूर्ण,
	अणु0x17c3, 0x0000पूर्ण,
	अणु0x17c5, 0x0000पूर्ण,
	अणु0x17c7, 0x0000पूर्ण,
	अणु0x17c9, 0x0000पूर्ण,
	अणु0x17cb, 0x2010पूर्ण,
	अणु0x17cd, 0x0000पूर्ण,
	अणु0x17cf, 0x0000पूर्ण,
	अणु0x17d1, 0x0000पूर्ण,
	अणु0x17d3, 0x0000पूर्ण,
	अणु0x17d5, 0x0000पूर्ण,
	अणु0x17d7, 0x0000पूर्ण,
	अणु0x17d9, 0x0000पूर्ण,
	अणु0x17db, 0x0000पूर्ण,
	अणु0x17dd, 0x0000पूर्ण,
	अणु0x17df, 0x0000पूर्ण,
	अणु0x17e1, 0x0000पूर्ण,
	अणु0x17e3, 0x0000पूर्ण,
	अणु0x17e5, 0x0000पूर्ण,
	अणु0x17e7, 0x0000पूर्ण,
	अणु0x17e9, 0x0000पूर्ण,
	अणु0x17eb, 0x0000पूर्ण,
	अणु0x17ed, 0x0000पूर्ण,
	अणु0x17ef, 0x0000पूर्ण,
	अणु0x17f1, 0x0000पूर्ण,
	अणु0x17f3, 0x0000पूर्ण,
	अणु0x17f5, 0x0000पूर्ण,
	अणु0x17f7, 0x0000पूर्ण,
	अणु0x17f9, 0x0000पूर्ण,
	अणु0x17fb, 0x0000पूर्ण,
	अणु0x17fd, 0x0000पूर्ण,
	अणु0x17ff, 0x0000पूर्ण,
	अणु0x1801, 0x0000पूर्ण,
	अणु0x1803, 0x0000पूर्ण,
पूर्ण;

अटल पूर्णांक rt1011_reg_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	regmap_multi_reg_ग_लिखो(rt1011->regmap,
		init_list, ARRAY_SIZE(init_list));
	वापस 0;
पूर्ण

अटल bool rt1011_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1011_RESET:
	हाल RT1011_SRC_2:
	हाल RT1011_CLK_DET:
	हाल RT1011_SIL_DET:
	हाल RT1011_VERSION_ID:
	हाल RT1011_VENDOR_ID:
	हाल RT1011_DEVICE_ID:
	हाल RT1011_DUM_RO:
	हाल RT1011_DAC_SET_3:
	हाल RT1011_PWM_CAL:
	हाल RT1011_SPK_VOL_TEST_OUT:
	हाल RT1011_VBAT_VOL_DET_1:
	हाल RT1011_VBAT_TEST_OUT_1:
	हाल RT1011_VBAT_TEST_OUT_2:
	हाल RT1011_VBAT_PROTECTION:
	हाल RT1011_VBAT_DET:
	हाल RT1011_BOOST_CON_1:
	हाल RT1011_SHORT_CIRCUIT_DET_1:
	हाल RT1011_SPK_TEMP_PROTECT_3:
	हाल RT1011_SPK_TEMP_PROTECT_6:
	हाल RT1011_SPK_PRO_DC_DET_3:
	हाल RT1011_SPK_PRO_DC_DET_7:
	हाल RT1011_SPK_PRO_DC_DET_8:
	हाल RT1011_SPL_1:
	हाल RT1011_SPL_4:
	हाल RT1011_EXCUR_PROTECT_1:
	हाल RT1011_CROSS_BQ_SET_1:
	हाल RT1011_CROSS_BQ_SET_2:
	हाल RT1011_BQ_SET_0:
	हाल RT1011_BQ_SET_1:
	हाल RT1011_BQ_SET_2:
	हाल RT1011_TEST_PAD_STATUS:
	हाल RT1011_DC_CALIB_CLASSD_1:
	हाल RT1011_DC_CALIB_CLASSD_5:
	हाल RT1011_DC_CALIB_CLASSD_6:
	हाल RT1011_DC_CALIB_CLASSD_7:
	हाल RT1011_DC_CALIB_CLASSD_8:
	हाल RT1011_SINE_GEN_REG_2:
	हाल RT1011_STP_CALIB_RS_TEMP:
	हाल RT1011_SPK_RESISTANCE_1:
	हाल RT1011_SPK_RESISTANCE_2:
	हाल RT1011_SPK_THERMAL:
	हाल RT1011_ALC_BK_GAIN_O:
	हाल RT1011_ALC_BK_GAIN_O_PRE:
	हाल RT1011_SPK_DC_O_23_16:
	हाल RT1011_SPK_DC_O_15_0:
	हाल RT1011_INIT_RECIPROCAL_SYN_24_16:
	हाल RT1011_INIT_RECIPROCAL_SYN_15_0:
	हाल RT1011_SPK_EXCURSION_23_16:
	हाल RT1011_SPK_EXCURSION_15_0:
	हाल RT1011_SEP_MAIN_OUT_23_16:
	हाल RT1011_SEP_MAIN_OUT_15_0:
	हाल RT1011_ALC_DRC_HB_INTERNAL_5:
	हाल RT1011_ALC_DRC_HB_INTERNAL_6:
	हाल RT1011_ALC_DRC_HB_INTERNAL_7:
	हाल RT1011_ALC_DRC_BB_INTERNAL_5:
	हाल RT1011_ALC_DRC_BB_INTERNAL_6:
	हाल RT1011_ALC_DRC_BB_INTERNAL_7:
	हाल RT1011_ALC_DRC_POS_INTERNAL_5:
	हाल RT1011_ALC_DRC_POS_INTERNAL_6:
	हाल RT1011_ALC_DRC_POS_INTERNAL_7:
	हाल RT1011_ALC_DRC_POS_INTERNAL_8:
	हाल RT1011_ALC_DRC_POS_INTERNAL_9:
	हाल RT1011_ALC_DRC_POS_INTERNAL_10:
	हाल RT1011_ALC_DRC_POS_INTERNAL_11:
	हाल RT1011_IRQ_1:
	हाल RT1011_EFUSE_CONTROL_1:
	हाल RT1011_EFUSE_CONTROL_2:
	हाल RT1011_EFUSE_MATCH_DONE ... RT1011_EFUSE_READ_R0_3_15_0:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1011_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1011_RESET:
	हाल RT1011_CLK_1:
	हाल RT1011_CLK_2:
	हाल RT1011_CLK_3:
	हाल RT1011_CLK_4:
	हाल RT1011_PLL_1:
	हाल RT1011_PLL_2:
	हाल RT1011_SRC_1:
	हाल RT1011_SRC_2:
	हाल RT1011_SRC_3:
	हाल RT1011_CLK_DET:
	हाल RT1011_SIL_DET:
	हाल RT1011_PRIV_INDEX:
	हाल RT1011_PRIV_DATA:
	हाल RT1011_CUSTOMER_ID:
	हाल RT1011_FM_VER:
	हाल RT1011_VERSION_ID:
	हाल RT1011_VENDOR_ID:
	हाल RT1011_DEVICE_ID:
	हाल RT1011_DUM_RW_0:
	हाल RT1011_DUM_YUN:
	हाल RT1011_DUM_RW_1:
	हाल RT1011_DUM_RO:
	हाल RT1011_MAN_I2C_DEV:
	हाल RT1011_DAC_SET_1:
	हाल RT1011_DAC_SET_2:
	हाल RT1011_DAC_SET_3:
	हाल RT1011_ADC_SET:
	हाल RT1011_ADC_SET_1:
	हाल RT1011_ADC_SET_2:
	हाल RT1011_ADC_SET_3:
	हाल RT1011_ADC_SET_4:
	हाल RT1011_ADC_SET_5:
	हाल RT1011_TDM_TOTAL_SET:
	हाल RT1011_TDM1_SET_TCON:
	हाल RT1011_TDM1_SET_1:
	हाल RT1011_TDM1_SET_2:
	हाल RT1011_TDM1_SET_3:
	हाल RT1011_TDM1_SET_4:
	हाल RT1011_TDM1_SET_5:
	हाल RT1011_TDM2_SET_1:
	हाल RT1011_TDM2_SET_2:
	हाल RT1011_TDM2_SET_3:
	हाल RT1011_TDM2_SET_4:
	हाल RT1011_TDM2_SET_5:
	हाल RT1011_PWM_CAL:
	हाल RT1011_MIXER_1:
	हाल RT1011_MIXER_2:
	हाल RT1011_ADRC_LIMIT:
	हाल RT1011_A_PRO:
	हाल RT1011_A_TIMING_1:
	हाल RT1011_A_TIMING_2:
	हाल RT1011_A_TEMP_SEN:
	हाल RT1011_SPK_VOL_DET_1:
	हाल RT1011_SPK_VOL_DET_2:
	हाल RT1011_SPK_VOL_TEST_OUT:
	हाल RT1011_VBAT_VOL_DET_1:
	हाल RT1011_VBAT_VOL_DET_2:
	हाल RT1011_VBAT_TEST_OUT_1:
	हाल RT1011_VBAT_TEST_OUT_2:
	हाल RT1011_VBAT_PROTECTION:
	हाल RT1011_VBAT_DET:
	हाल RT1011_POWER_1:
	हाल RT1011_POWER_2:
	हाल RT1011_POWER_3:
	हाल RT1011_POWER_4:
	हाल RT1011_POWER_5:
	हाल RT1011_POWER_6:
	हाल RT1011_POWER_7:
	हाल RT1011_POWER_8:
	हाल RT1011_POWER_9:
	हाल RT1011_CLASS_D_POS:
	हाल RT1011_BOOST_CON_1:
	हाल RT1011_BOOST_CON_2:
	हाल RT1011_ANALOG_CTRL:
	हाल RT1011_POWER_SEQ:
	हाल RT1011_SHORT_CIRCUIT_DET_1:
	हाल RT1011_SHORT_CIRCUIT_DET_2:
	हाल RT1011_SPK_TEMP_PROTECT_0:
	हाल RT1011_SPK_TEMP_PROTECT_1:
	हाल RT1011_SPK_TEMP_PROTECT_2:
	हाल RT1011_SPK_TEMP_PROTECT_3:
	हाल RT1011_SPK_TEMP_PROTECT_4:
	हाल RT1011_SPK_TEMP_PROTECT_5:
	हाल RT1011_SPK_TEMP_PROTECT_6:
	हाल RT1011_SPK_TEMP_PROTECT_7:
	हाल RT1011_SPK_TEMP_PROTECT_8:
	हाल RT1011_SPK_TEMP_PROTECT_9:
	हाल RT1011_SPK_PRO_DC_DET_1:
	हाल RT1011_SPK_PRO_DC_DET_2:
	हाल RT1011_SPK_PRO_DC_DET_3:
	हाल RT1011_SPK_PRO_DC_DET_4:
	हाल RT1011_SPK_PRO_DC_DET_5:
	हाल RT1011_SPK_PRO_DC_DET_6:
	हाल RT1011_SPK_PRO_DC_DET_7:
	हाल RT1011_SPK_PRO_DC_DET_8:
	हाल RT1011_SPL_1:
	हाल RT1011_SPL_2:
	हाल RT1011_SPL_3:
	हाल RT1011_SPL_4:
	हाल RT1011_THER_FOLD_BACK_1:
	हाल RT1011_THER_FOLD_BACK_2:
	हाल RT1011_EXCUR_PROTECT_1:
	हाल RT1011_EXCUR_PROTECT_2:
	हाल RT1011_EXCUR_PROTECT_3:
	हाल RT1011_EXCUR_PROTECT_4:
	हाल RT1011_BAT_GAIN_1:
	हाल RT1011_BAT_GAIN_2:
	हाल RT1011_BAT_GAIN_3:
	हाल RT1011_BAT_GAIN_4:
	हाल RT1011_BAT_GAIN_5:
	हाल RT1011_BAT_GAIN_6:
	हाल RT1011_BAT_GAIN_7:
	हाल RT1011_BAT_GAIN_8:
	हाल RT1011_BAT_GAIN_9:
	हाल RT1011_BAT_GAIN_10:
	हाल RT1011_BAT_GAIN_11:
	हाल RT1011_BAT_RT_THMAX_1:
	हाल RT1011_BAT_RT_THMAX_2:
	हाल RT1011_BAT_RT_THMAX_3:
	हाल RT1011_BAT_RT_THMAX_4:
	हाल RT1011_BAT_RT_THMAX_5:
	हाल RT1011_BAT_RT_THMAX_6:
	हाल RT1011_BAT_RT_THMAX_7:
	हाल RT1011_BAT_RT_THMAX_8:
	हाल RT1011_BAT_RT_THMAX_9:
	हाल RT1011_BAT_RT_THMAX_10:
	हाल RT1011_BAT_RT_THMAX_11:
	हाल RT1011_BAT_RT_THMAX_12:
	हाल RT1011_SPREAD_SPECTURM:
	हाल RT1011_PRO_GAIN_MODE:
	हाल RT1011_RT_DRC_CROSS:
	हाल RT1011_RT_DRC_HB_1:
	हाल RT1011_RT_DRC_HB_2:
	हाल RT1011_RT_DRC_HB_3:
	हाल RT1011_RT_DRC_HB_4:
	हाल RT1011_RT_DRC_HB_5:
	हाल RT1011_RT_DRC_HB_6:
	हाल RT1011_RT_DRC_HB_7:
	हाल RT1011_RT_DRC_HB_8:
	हाल RT1011_RT_DRC_BB_1:
	हाल RT1011_RT_DRC_BB_2:
	हाल RT1011_RT_DRC_BB_3:
	हाल RT1011_RT_DRC_BB_4:
	हाल RT1011_RT_DRC_BB_5:
	हाल RT1011_RT_DRC_BB_6:
	हाल RT1011_RT_DRC_BB_7:
	हाल RT1011_RT_DRC_BB_8:
	हाल RT1011_RT_DRC_POS_1:
	हाल RT1011_RT_DRC_POS_2:
	हाल RT1011_RT_DRC_POS_3:
	हाल RT1011_RT_DRC_POS_4:
	हाल RT1011_RT_DRC_POS_5:
	हाल RT1011_RT_DRC_POS_6:
	हाल RT1011_RT_DRC_POS_7:
	हाल RT1011_RT_DRC_POS_8:
	हाल RT1011_CROSS_BQ_SET_1:
	हाल RT1011_CROSS_BQ_SET_2:
	हाल RT1011_BQ_SET_0:
	हाल RT1011_BQ_SET_1:
	हाल RT1011_BQ_SET_2:
	हाल RT1011_BQ_PRE_GAIN_28_16:
	हाल RT1011_BQ_PRE_GAIN_15_0:
	हाल RT1011_BQ_POST_GAIN_28_16:
	हाल RT1011_BQ_POST_GAIN_15_0:
	हाल RT1011_BQ_H0_28_16 ... RT1011_BQ_A2_15_0:
	हाल RT1011_BQ_1_H0_28_16 ... RT1011_BQ_1_A2_15_0:
	हाल RT1011_BQ_2_H0_28_16 ... RT1011_BQ_2_A2_15_0:
	हाल RT1011_BQ_3_H0_28_16 ... RT1011_BQ_3_A2_15_0:
	हाल RT1011_BQ_4_H0_28_16 ... RT1011_BQ_4_A2_15_0:
	हाल RT1011_BQ_5_H0_28_16 ... RT1011_BQ_5_A2_15_0:
	हाल RT1011_BQ_6_H0_28_16 ... RT1011_BQ_6_A2_15_0:
	हाल RT1011_BQ_7_H0_28_16 ... RT1011_BQ_7_A2_15_0:
	हाल RT1011_BQ_8_H0_28_16 ... RT1011_BQ_8_A2_15_0:
	हाल RT1011_BQ_9_H0_28_16 ... RT1011_BQ_9_A2_15_0:
	हाल RT1011_BQ_10_H0_28_16 ... RT1011_BQ_10_A2_15_0:
	हाल RT1011_TEST_PAD_STATUS ... RT1011_PLL_INTERNAL_SET:
	हाल RT1011_TEST_OUT_1 ... RT1011_TEST_OUT_3:
	हाल RT1011_DC_CALIB_CLASSD_1 ... RT1011_DC_CALIB_CLASSD_10:
	हाल RT1011_CLASSD_INTERNAL_SET_1 ... RT1011_VREF_LV_1:
	हाल RT1011_SMART_BOOST_TIMING_1 ... RT1011_SMART_BOOST_TIMING_36:
	हाल RT1011_SINE_GEN_REG_1 ... RT1011_SINE_GEN_REG_3:
	हाल RT1011_STP_INITIAL_RS_TEMP ... RT1011_SPK_THERMAL:
	हाल RT1011_STP_OTP_TH ... RT1011_INIT_RECIPROCAL_SYN_15_0:
	हाल RT1011_STP_BQ_1_A1_L_28_16 ... RT1011_STP_BQ_1_H0_R_15_0:
	हाल RT1011_STP_BQ_2_A1_L_28_16 ... RT1011_SEP_RE_REG_15_0:
	हाल RT1011_DRC_CF_PARAMS_1 ... RT1011_DRC_CF_PARAMS_12:
	हाल RT1011_ALC_DRC_HB_INTERNAL_1 ... RT1011_ALC_DRC_HB_INTERNAL_7:
	हाल RT1011_ALC_DRC_BB_INTERNAL_1 ... RT1011_ALC_DRC_BB_INTERNAL_7:
	हाल RT1011_ALC_DRC_POS_INTERNAL_1 ... RT1011_ALC_DRC_POS_INTERNAL_8:
	हाल RT1011_ALC_DRC_POS_INTERNAL_9 ... RT1011_BQ_1_PARAMS_CHECK_5:
	हाल RT1011_BQ_2_PARAMS_CHECK_1 ... RT1011_BQ_2_PARAMS_CHECK_5:
	हाल RT1011_BQ_3_PARAMS_CHECK_1 ... RT1011_BQ_3_PARAMS_CHECK_5:
	हाल RT1011_BQ_4_PARAMS_CHECK_1 ... RT1011_BQ_4_PARAMS_CHECK_5:
	हाल RT1011_BQ_5_PARAMS_CHECK_1 ... RT1011_BQ_5_PARAMS_CHECK_5:
	हाल RT1011_BQ_6_PARAMS_CHECK_1 ... RT1011_BQ_6_PARAMS_CHECK_5:
	हाल RT1011_BQ_7_PARAMS_CHECK_1 ... RT1011_BQ_7_PARAMS_CHECK_5:
	हाल RT1011_BQ_8_PARAMS_CHECK_1 ... RT1011_BQ_8_PARAMS_CHECK_5:
	हाल RT1011_BQ_9_PARAMS_CHECK_1 ... RT1011_BQ_9_PARAMS_CHECK_5:
	हाल RT1011_BQ_10_PARAMS_CHECK_1 ... RT1011_BQ_10_PARAMS_CHECK_5:
	हाल RT1011_IRQ_1 ... RT1011_PART_NUMBER_EFUSE:
	हाल RT1011_EFUSE_CONTROL_1 ... RT1011_EFUSE_READ_R0_3_15_0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर rt1011_din_source_select[] = अणु
	"Left",
	"Right",
	"Left + Right average",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1011_din_source_क्रमागत, RT1011_CROSS_BQ_SET_1, 5,
	rt1011_din_source_select);

अटल स्थिर अक्षर * स्थिर rt1011_tdm_data_out_select[] = अणु
	"TDM_O_LR", "BQ1", "DVOL", "BQ10", "ALC", "DMIX", "ADC_SRC_LR",
	"ADC_O_LR", "ADC_MONO", "RSPK_BPF_LR", "DMIX_ADD", "ENVELOPE_FS",
	"SEP_O_GAIN", "ALC_BK_GAIN", "STP_V_C", "DMIX_ABST"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rt1011_tdm_l_ch_data_select[] = अणु
	"Slot0", "Slot1", "Slot2", "Slot3", "Slot4", "Slot5", "Slot6", "Slot7"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm1_l_dac1_क्रमागत, RT1011_TDM1_SET_4, 12,
	rt1011_tdm_l_ch_data_select);
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm2_l_dac1_क्रमागत, RT1011_TDM2_SET_4, 12,
	rt1011_tdm_l_ch_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm1_adc1_dat_क्रमागत,
	RT1011_ADCDAT_OUT_SOURCE, 0, rt1011_tdm_data_out_select);
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm1_adc1_loc_क्रमागत, RT1011_TDM1_SET_2, 0,
	rt1011_tdm_l_ch_data_select);

अटल स्थिर अक्षर * स्थिर rt1011_adc_data_mode_select[] = अणु
	"Stereo", "Mono"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(rt1011_adc_करोut_mode_क्रमागत, RT1011_TDM1_SET_1, 12,
	rt1011_adc_data_mode_select);

अटल स्थिर अक्षर * स्थिर rt1011_tdm_adc_data_len_control[] = अणु
	"1CH", "2CH", "3CH", "4CH", "5CH", "6CH", "7CH", "8CH"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm1_करोut_len_क्रमागत, RT1011_TDM1_SET_2, 13,
	rt1011_tdm_adc_data_len_control);
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm2_करोut_len_क्रमागत, RT1011_TDM2_SET_2, 13,
	rt1011_tdm_adc_data_len_control);

अटल स्थिर अक्षर * स्थिर rt1011_tdm_adc_swap_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm_adc1_1_क्रमागत, RT1011_TDM1_SET_3, 6,
	rt1011_tdm_adc_swap_select);
अटल SOC_ENUM_SINGLE_DECL(rt1011_tdm_adc2_1_क्रमागत, RT1011_TDM1_SET_3, 4,
	rt1011_tdm_adc_swap_select);

अटल व्योम rt1011_reset(काष्ठा regmap *regmap)
अणु
	regmap_ग_लिखो(regmap, RT1011_RESET, 0);
पूर्ण

अटल पूर्णांक rt1011_recv_spk_mode_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1011_priv *rt1011 =
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt1011->recv_spk_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_recv_spk_mode_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1011_priv *rt1011 =
		snd_soc_component_get_drvdata(component);

	अगर (ucontrol->value.पूर्णांकeger.value[0] == rt1011->recv_spk_mode)
		वापस 0;

	अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
		rt1011->recv_spk_mode = ucontrol->value.पूर्णांकeger.value[0];

		अगर (rt1011->recv_spk_mode) अणु

			/* 1: recevier mode on */
			snd_soc_component_update_bits(component,
				RT1011_CLASSD_INTERNAL_SET_3,
				RT1011_REG_GAIN_CLASSD_RI_SPK_MASK,
				RT1011_REG_GAIN_CLASSD_RI_410K);
			snd_soc_component_update_bits(component,
				RT1011_CLASSD_INTERNAL_SET_1,
				RT1011_RECV_MODE_SPK_MASK,
				RT1011_RECV_MODE);
		पूर्ण अन्यथा अणु
			/* 0: speaker mode on */
			snd_soc_component_update_bits(component,
				RT1011_CLASSD_INTERNAL_SET_3,
				RT1011_REG_GAIN_CLASSD_RI_SPK_MASK,
				RT1011_REG_GAIN_CLASSD_RI_72P5K);
			snd_soc_component_update_bits(component,
				RT1011_CLASSD_INTERNAL_SET_1,
				RT1011_RECV_MODE_SPK_MASK,
				RT1011_SPK_MODE);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rt1011_validate_bq_drc_coeff(अचिन्हित लघु reg)
अणु
	अगर ((reg == RT1011_DAC_SET_1) ||
		(reg >= RT1011_ADC_SET && reg <= RT1011_ADC_SET_1) ||
		(reg == RT1011_ADC_SET_4) || (reg == RT1011_ADC_SET_5) ||
		(reg == RT1011_MIXER_1) ||
		(reg == RT1011_A_TIMING_1) ||
		(reg >= RT1011_POWER_7 && reg <= RT1011_POWER_8) ||
		(reg == RT1011_CLASS_D_POS) || (reg == RT1011_ANALOG_CTRL) ||
		(reg >= RT1011_SPK_TEMP_PROTECT_0 && reg <= RT1011_SPK_TEMP_PROTECT_6) ||
		(reg >= RT1011_SPK_PRO_DC_DET_5 && reg <= RT1011_BAT_GAIN_1) ||
		(reg >= RT1011_RT_DRC_CROSS && reg <= RT1011_RT_DRC_POS_8) ||
		(reg >= RT1011_CROSS_BQ_SET_1 && reg <= RT1011_BQ_10_A2_15_0) ||
		(reg >= RT1011_SMART_BOOST_TIMING_1 && reg <= RT1011_SMART_BOOST_TIMING_36) ||
		(reg == RT1011_SINE_GEN_REG_1) ||
		(reg >= RT1011_STP_ALPHA_RECIPROCAL_MSB && reg <= RT1011_BQ_6_PARAMS_CHECK_5) ||
		(reg >= RT1011_BQ_7_PARAMS_CHECK_1 && reg <= RT1011_BQ_10_PARAMS_CHECK_5))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक rt1011_bq_drc_coeff_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1011_priv *rt1011 =
		snd_soc_component_get_drvdata(component);
	काष्ठा rt1011_bq_drc_params *bq_drc_info;
	काष्ठा rt1011_bq_drc_params *params =
		(काष्ठा rt1011_bq_drc_params *)ucontrol->value.पूर्णांकeger.value;
	अचिन्हित पूर्णांक i, mode_idx = 0;

	अगर (म_माला(ucontrol->id.name, "AdvanceMode Initial Set"))
		mode_idx = RT1011_ADVMODE_INITIAL_SET;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode SEP BQ Coeff"))
		mode_idx = RT1011_ADVMODE_SEP_BQ_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode EQ BQ Coeff"))
		mode_idx = RT1011_ADVMODE_EQ_BQ_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode BQ UI Coeff"))
		mode_idx = RT1011_ADVMODE_BQ_UI_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode SmartBoost Coeff"))
		mode_idx = RT1011_ADVMODE_SMARTBOOST_COEFF;
	अन्यथा
		वापस -EINVAL;

	pr_info("%s, id.name=%s, mode_idx=%d\n", __func__,
		ucontrol->id.name, mode_idx);
	bq_drc_info = rt1011->bq_drc_params[mode_idx];

	क्रम (i = 0; i < RT1011_BQ_DRC_NUM; i++) अणु
		params[i].reg = bq_drc_info[i].reg;
		params[i].val = bq_drc_info[i].val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_bq_drc_coeff_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1011_priv *rt1011 =
		snd_soc_component_get_drvdata(component);
	काष्ठा rt1011_bq_drc_params *bq_drc_info;
	काष्ठा rt1011_bq_drc_params *params =
		(काष्ठा rt1011_bq_drc_params *)ucontrol->value.पूर्णांकeger.value;
	अचिन्हित पूर्णांक i, mode_idx = 0;

	अगर (म_माला(ucontrol->id.name, "AdvanceMode Initial Set"))
		mode_idx = RT1011_ADVMODE_INITIAL_SET;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode SEP BQ Coeff"))
		mode_idx = RT1011_ADVMODE_SEP_BQ_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode EQ BQ Coeff"))
		mode_idx = RT1011_ADVMODE_EQ_BQ_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode BQ UI Coeff"))
		mode_idx = RT1011_ADVMODE_BQ_UI_COEFF;
	अन्यथा अगर (म_माला(ucontrol->id.name, "AdvanceMode SmartBoost Coeff"))
		mode_idx = RT1011_ADVMODE_SMARTBOOST_COEFF;
	अन्यथा
		वापस -EINVAL;

	bq_drc_info = rt1011->bq_drc_params[mode_idx];
	स_रखो(bq_drc_info, 0,
		माप(काष्ठा rt1011_bq_drc_params) * RT1011_BQ_DRC_NUM);

	pr_info("%s, id.name=%s, mode_idx=%d\n", __func__,
		ucontrol->id.name, mode_idx);
	क्रम (i = 0; i < RT1011_BQ_DRC_NUM; i++) अणु
		bq_drc_info[i].reg = params[i].reg;
		bq_drc_info[i].val = params[i].val;
	पूर्ण

	क्रम (i = 0; i < RT1011_BQ_DRC_NUM; i++) अणु
		अगर (bq_drc_info[i].reg == 0)
			अवरोध;
		अन्यथा अगर (rt1011_validate_bq_drc_coeff(bq_drc_info[i].reg)) अणु
			snd_soc_component_ग_लिखो(component, bq_drc_info[i].reg,
					bq_drc_info[i].val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_bq_drc_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 128;
	uinfo->value.पूर्णांकeger.max = 0x17ffffff;

	वापस 0;
पूर्ण

#घोषणा RT1011_BQ_DRC(xname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = rt1011_bq_drc_info, \
	.get = rt1011_bq_drc_coeff_get, \
	.put = rt1011_bq_drc_coeff_put \
पूर्ण

अटल पूर्णांक rt1011_r0_cali_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt1011->cali_करोne;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_r0_cali_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	rt1011->cali_करोne = 0;
	अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF &&
		ucontrol->value.पूर्णांकeger.value[0])
		rt1011_calibrate(rt1011, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_r0_load(काष्ठा rt1011_priv *rt1011)
अणु
	अगर (!rt1011->r0_reg)
		वापस -EINVAL;

	/* ग_लिखो R0 to रेजिस्टर */
	regmap_ग_लिखो(rt1011->regmap, RT1011_INIT_RECIPROCAL_REG_24_16,
		((rt1011->r0_reg>>16) & 0x1ff));
	regmap_ग_लिखो(rt1011->regmap, RT1011_INIT_RECIPROCAL_REG_15_0,
		(rt1011->r0_reg & 0xffff));
	regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_4, 0x4080);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_r0_load_mode_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt1011->r0_reg;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_r0_load_mode_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev;
	अचिन्हित पूर्णांक r0_पूर्णांकeger, r0_factor, क्रमmat;

	अगर (ucontrol->value.पूर्णांकeger.value[0] == rt1011->r0_reg)
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] == 0)
		वापस -EINVAL;

	dev = regmap_get_device(rt1011->regmap);
	अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
		rt1011->r0_reg = ucontrol->value.पूर्णांकeger.value[0];

		क्रमmat = 2147483648U; /* 2^24 * 128 */
		r0_पूर्णांकeger = क्रमmat / rt1011->r0_reg / 128;
		r0_factor = ((क्रमmat / rt1011->r0_reg * 100) / 128)
						- (r0_पूर्णांकeger * 100);
		dev_info(dev, "New r0 resistance about %d.%02d ohm, reg=0x%X\n",
			r0_पूर्णांकeger, r0_factor, rt1011->r0_reg);

		अगर (rt1011->r0_reg)
			rt1011_r0_load(rt1011);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_r0_load_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.max = 0x1ffffff;

	वापस 0;
पूर्ण

#घोषणा RT1011_R0_LOAD(xname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = rt1011_r0_load_info, \
	.get = rt1011_r0_load_mode_get, \
	.put = rt1011_r0_load_mode_put \
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt1011_snd_controls[] = अणु
	/* I2S Data In Selection */
	SOC_ENUM("DIN Source", rt1011_din_source_क्रमागत),

	/* TDM Data In Selection */
	SOC_ENUM("TDM1 DIN Source", rt1011_tdm1_l_dac1_क्रमागत),
	SOC_ENUM("TDM2 DIN Source", rt1011_tdm2_l_dac1_क्रमागत),

	/* TDM1 Data Out Selection */
	SOC_ENUM("TDM1 DOUT Source", rt1011_tdm1_adc1_dat_क्रमागत),
	SOC_ENUM("TDM1 DOUT Location", rt1011_tdm1_adc1_loc_क्रमागत),
	SOC_ENUM("TDM1 ADC1DAT Swap Select", rt1011_tdm_adc1_1_क्रमागत),
	SOC_ENUM("TDM1 ADC2DAT Swap Select", rt1011_tdm_adc2_1_क्रमागत),

	/* Data Out Mode */
	SOC_ENUM("I2S ADC DOUT Mode", rt1011_adc_करोut_mode_क्रमागत),
	SOC_ENUM("TDM1 DOUT Length", rt1011_tdm1_करोut_len_क्रमागत),
	SOC_ENUM("TDM2 DOUT Length", rt1011_tdm2_करोut_len_क्रमागत),

	/* Speaker/Receiver Mode */
	SOC_SINGLE_EXT("RECV SPK Mode", SND_SOC_NOPM, 0, 1, 0,
		rt1011_recv_spk_mode_get, rt1011_recv_spk_mode_put),

	/* BiQuad/DRC/SmartBoost Settings */
	RT1011_BQ_DRC("AdvanceMode Initial Set"),
	RT1011_BQ_DRC("AdvanceMode SEP BQ Coeff"),
	RT1011_BQ_DRC("AdvanceMode EQ BQ Coeff"),
	RT1011_BQ_DRC("AdvanceMode BQ UI Coeff"),
	RT1011_BQ_DRC("AdvanceMode SmartBoost Coeff"),

	/* R0 */
	SOC_SINGLE_EXT("R0 Calibration", SND_SOC_NOPM, 0, 1, 0,
		rt1011_r0_cali_get, rt1011_r0_cali_put),
	RT1011_R0_LOAD("R0 Load Mode"),

	/* R0 temperature */
	SOC_SINGLE("R0 Temperature", RT1011_STP_INITIAL_RESISTANCE_TEMP,
		2, 255, 0),
पूर्ण;

अटल पूर्णांक rt1011_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	अगर (rt1011->sysclk_src == RT1011_FS_SYS_PRE_S_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक rt1011_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component,
			RT1011_SPK_TEMP_PROTECT_0,
			RT1011_STP_EN_MASK | RT1011_STP_RS_CLB_EN_MASK,
			RT1011_STP_EN | RT1011_STP_RS_CLB_EN);
		snd_soc_component_update_bits(component, RT1011_POWER_9,
			RT1011_POW_MNL_SDB_MASK, RT1011_POW_MNL_SDB);
		msleep(50);
		snd_soc_component_update_bits(component,
			RT1011_CLASSD_INTERNAL_SET_1,
			RT1011_DRIVER_READY_SPK, RT1011_DRIVER_READY_SPK);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT1011_POWER_9,
			RT1011_POW_MNL_SDB_MASK, 0);
		snd_soc_component_update_bits(component,
			RT1011_SPK_TEMP_PROTECT_0,
			RT1011_STP_EN_MASK | RT1011_STP_RS_CLB_EN_MASK, 0);
		msleep(200);
		snd_soc_component_update_bits(component,
			RT1011_CLASSD_INTERNAL_SET_1,
			RT1011_DRIVER_READY_SPK, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_soc_dapm_widget rt1011_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT1011_POWER_1,
		RT1011_POW_LDO2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ISENSE SPK", RT1011_POWER_1,
		RT1011_POW_ISENSE_SPK_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VSENSE SPK", RT1011_POWER_1,
		RT1011_POW_VSENSE_SPK_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("PLL", RT1011_POWER_2,
		RT1011_PLLEN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG", RT1011_POWER_2,
		RT1011_POW_BG_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG MBIAS", RT1011_POWER_2,
		RT1011_POW_BG_MBIAS_LV_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DET VBAT", RT1011_POWER_3,
		RT1011_POW_DET_VBAT_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS", RT1011_POWER_3,
		RT1011_POW_MBIAS_LV_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC I", RT1011_POWER_3,
		RT1011_POW_ADC_I_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC V", RT1011_POWER_3,
		RT1011_POW_ADC_V_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC T", RT1011_POWER_3,
		RT1011_POW_ADC_T_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DITHER ADC T", RT1011_POWER_3,
		RT1011_POWD_ADC_T_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIX I", RT1011_POWER_3,
		RT1011_POW_MIX_I_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIX V", RT1011_POWER_3,
		RT1011_POW_MIX_V_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SUM I", RT1011_POWER_3,
		RT1011_POW_SUM_I_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SUM V", RT1011_POWER_3,
		RT1011_POW_SUM_V_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIX T", RT1011_POWER_3,
		RT1011_POW_MIX_T_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF", RT1011_POWER_3,
		RT1011_POW_VREF_LV_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("BOOST SWR", RT1011_POWER_4,
		RT1011_POW_EN_SWR_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BGOK SWR", RT1011_POWER_4,
		RT1011_POW_EN_PASS_BGOK_SWR_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VPOK SWR", RT1011_POWER_4,
		RT1011_POW_EN_PASS_VPOK_SWR_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("TEMP REG", RT1011_A_TEMP_SEN,
		RT1011_POW_TEMP_REG_BIT, 0, शून्य, 0),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("DAC Power", RT1011_POWER_1,
		RT1011_POW_DAC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK12M", RT1011_POWER_1,
		RT1011_POW_CLK12M_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, RT1011_DAC_SET_3,
		RT1011_DA_MUTE_EN_SFT, 1, rt1011_dac_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("SPO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1011_dapm_routes[] = अणु

	अणु "DAC", शून्य, "AIF1RX" पूर्ण,
	अणु "DAC", शून्य, "DAC Power" पूर्ण,
	अणु "DAC", शून्य, "LDO2" पूर्ण,
	अणु "DAC", शून्य, "ISENSE SPK" पूर्ण,
	अणु "DAC", शून्य, "VSENSE SPK" पूर्ण,
	अणु "DAC", शून्य, "CLK12M" पूर्ण,

	अणु "DAC", शून्य, "PLL", rt1011_is_sys_clk_from_pll पूर्ण,
	अणु "DAC", शून्य, "BG" पूर्ण,
	अणु "DAC", शून्य, "BG MBIAS" पूर्ण,

	अणु "DAC", शून्य, "BOOST SWR" पूर्ण,
	अणु "DAC", शून्य, "BGOK SWR" पूर्ण,
	अणु "DAC", शून्य, "VPOK SWR" पूर्ण,

	अणु "DAC", शून्य, "DET VBAT" पूर्ण,
	अणु "DAC", शून्य, "MBIAS" पूर्ण,
	अणु "DAC", शून्य, "VREF" पूर्ण,
	अणु "DAC", शून्य, "ADC I" पूर्ण,
	अणु "DAC", शून्य, "ADC V" पूर्ण,
	अणु "DAC", शून्य, "ADC T" पूर्ण,
	अणु "DAC", शून्य, "DITHER ADC T" पूर्ण,
	अणु "DAC", शून्य, "MIX I" पूर्ण,
	अणु "DAC", शून्य, "MIX V" पूर्ण,
	अणु "DAC", शून्य, "SUM I" पूर्ण,
	अणु "DAC", शून्य, "SUM V" पूर्ण,
	अणु "DAC", शून्य, "MIX T" पूर्ण,

	अणु "DAC", शून्य, "TEMP REG" पूर्ण,

	अणु "SPO", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1011_get_clk_info(पूर्णांक sclk, पूर्णांक rate)
अणु
	पूर्णांक i;
	अटल स्थिर पूर्णांक pd[] = अणु1, 2, 3, 4, 6, 8, 12, 16पूर्ण;

	अगर (sclk <= 0 || rate <= 0)
		वापस -EINVAL;

	rate = rate << 8;
	क्रम (i = 0; i < ARRAY_SIZE(pd); i++)
		अगर (sclk == rate * pd[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rt1011_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, ch_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt1011->lrck = params_rate(params);
	pre_भाग = rt1011_get_clk_info(rt1011->sysclk, rt1011->lrck);
	अगर (pre_भाग < 0) अणु
		dev_warn(component->dev, "Force using PLL ");
		snd_soc_dai_set_pll(dai, 0, RT1011_PLL1_S_BCLK,
			rt1011->lrck * 64, rt1011->lrck * 256);
		snd_soc_dai_set_sysclk(dai, RT1011_FS_SYS_PRE_S_PLL1,
			rt1011->lrck * 256, SND_SOC_CLOCK_IN);
		pre_भाग = 0;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt1011->bclk = rt1011->lrck * (32 << bclk_ms);

	dev_dbg(component->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	dev_dbg(component->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt1011->lrck, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= RT1011_I2S_TX_DL_16B;
		val_len |= RT1011_I2S_RX_DL_16B;
		ch_len |= RT1011_I2S_CH_TX_LEN_16B;
		ch_len |= RT1011_I2S_CH_RX_LEN_16B;
		अवरोध;
	हाल 20:
		val_len |= RT1011_I2S_TX_DL_20B;
		val_len |= RT1011_I2S_RX_DL_20B;
		ch_len |= RT1011_I2S_CH_TX_LEN_20B;
		ch_len |= RT1011_I2S_CH_RX_LEN_20B;
		अवरोध;
	हाल 24:
		val_len |= RT1011_I2S_TX_DL_24B;
		val_len |= RT1011_I2S_RX_DL_24B;
		ch_len |= RT1011_I2S_CH_TX_LEN_24B;
		ch_len |= RT1011_I2S_CH_RX_LEN_24B;
		अवरोध;
	हाल 32:
		val_len |= RT1011_I2S_TX_DL_32B;
		val_len |= RT1011_I2S_RX_DL_32B;
		ch_len |= RT1011_I2S_CH_TX_LEN_32B;
		ch_len |= RT1011_I2S_CH_RX_LEN_32B;
		अवरोध;
	हाल 8:
		val_len |= RT1011_I2S_TX_DL_8B;
		val_len |= RT1011_I2S_RX_DL_8B;
		ch_len |= RT1011_I2S_CH_TX_LEN_8B;
		ch_len |= RT1011_I2S_CH_RX_LEN_8B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1011_AIF1:
		mask_clk = RT1011_FS_SYS_DIV_MASK;
		val_clk = pre_भाग << RT1011_FS_SYS_DIV_SFT;
		snd_soc_component_update_bits(component, RT1011_TDM_TOTAL_SET,
			RT1011_I2S_TX_DL_MASK | RT1011_I2S_RX_DL_MASK,
			val_len);
		snd_soc_component_update_bits(component, RT1011_TDM1_SET_1,
			RT1011_I2S_CH_TX_LEN_MASK |
			RT1011_I2S_CH_RX_LEN_MASK,
			ch_len);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component,
		RT1011_CLK_2, mask_clk, val_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	अचिन्हित पूर्णांक reg_val = 0, reg_bclk_inv = 0;
	पूर्णांक ret = 0;

	snd_soc_dapm_mutex_lock(dapm);
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1011_I2S_TDM_MS_S;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_fmt_err_;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_bclk_inv |= RT1011_TDM_INV_BCLK;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_fmt_err_;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1011_I2S_TDM_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1011_I2S_TDM_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1011_I2S_TDM_DF_PCM_B;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_fmt_err_;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1011_AIF1:
		snd_soc_component_update_bits(component, RT1011_TDM_TOTAL_SET,
			RT1011_I2S_TDM_MS_MASK | RT1011_I2S_TDM_DF_MASK,
			reg_val);
		snd_soc_component_update_bits(component, RT1011_TDM1_SET_1,
			RT1011_TDM_INV_BCLK_MASK, reg_bclk_inv);
		snd_soc_component_update_bits(component, RT1011_TDM2_SET_1,
			RT1011_TDM_INV_BCLK_MASK, reg_bclk_inv);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		ret = -EINVAL;
	पूर्ण

_set_fmt_err_:
	snd_soc_dapm_mutex_unlock(dapm);
	वापस ret;
पूर्ण

अटल पूर्णांक rt1011_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1011->sysclk && clk_id == rt1011->sysclk_src)
		वापस 0;

	/* disable MCLK detect in शेष */
	snd_soc_component_update_bits(component, RT1011_CLK_DET,
			RT1011_EN_MCLK_DET_MASK, 0);

	चयन (clk_id) अणु
	हाल RT1011_FS_SYS_PRE_S_MCLK:
		reg_val |= RT1011_FS_SYS_PRE_MCLK;
		snd_soc_component_update_bits(component, RT1011_CLK_DET,
			RT1011_EN_MCLK_DET_MASK, RT1011_EN_MCLK_DET);
		अवरोध;
	हाल RT1011_FS_SYS_PRE_S_BCLK:
		reg_val |= RT1011_FS_SYS_PRE_BCLK;
		अवरोध;
	हाल RT1011_FS_SYS_PRE_S_PLL1:
		reg_val |= RT1011_FS_SYS_PRE_PLL1;
		अवरोध;
	हाल RT1011_FS_SYS_PRE_S_RCCLK:
		reg_val |= RT1011_FS_SYS_PRE_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT1011_CLK_2,
		RT1011_FS_SYS_PRE_MASK, reg_val);
	rt1011->sysclk = freq;
	rt1011->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt1011->pll_src && freq_in == rt1011->pll_in &&
	    freq_out == rt1011->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt1011->pll_in = 0;
		rt1011->pll_out = 0;
		snd_soc_component_update_bits(component, RT1011_CLK_2,
			RT1011_FS_SYS_PRE_MASK, RT1011_FS_SYS_PRE_BCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT1011_PLL2_S_MCLK:
		snd_soc_component_update_bits(component, RT1011_CLK_2,
			RT1011_PLL2_SRC_MASK, RT1011_PLL2_SRC_MCLK);
		snd_soc_component_update_bits(component, RT1011_CLK_2,
			RT1011_PLL1_SRC_MASK, RT1011_PLL1_SRC_PLL2);
		snd_soc_component_update_bits(component, RT1011_CLK_DET,
			RT1011_EN_MCLK_DET_MASK, RT1011_EN_MCLK_DET);
		अवरोध;
	हाल RT1011_PLL1_S_BCLK:
		snd_soc_component_update_bits(component, RT1011_CLK_2,
				RT1011_PLL1_SRC_MASK, RT1011_PLL1_SRC_BCLK);
		अवरोध;
	हाल RT1011_PLL2_S_RCCLK:
		snd_soc_component_update_bits(component, RT1011_CLK_2,
			RT1011_PLL2_SRC_MASK, RT1011_PLL2_SRC_RCCLK);
		snd_soc_component_update_bits(component, RT1011_CLK_2,
			RT1011_PLL1_SRC_MASK, RT1011_PLL1_SRC_PLL2);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL Source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupported input clock %d\n",
			freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_ग_लिखो(component, RT1011_PLL_1,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT1011_PLL1_QM_SFT) |
		(pll_code.m_bp << RT1011_PLL1_BPM_SFT) |
		pll_code.n_code);
	snd_soc_component_ग_लिखो(component, RT1011_PLL_2,
		pll_code.k_code);

	rt1011->pll_in = freq_in;
	rt1011->pll_out = freq_out;
	rt1011->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	अचिन्हित पूर्णांक val = 0, tdm_en = 0, rx_slotnum, tx_slotnum;
	पूर्णांक ret = 0, first_bit, last_bit;

	snd_soc_dapm_mutex_lock(dapm);
	अगर (rx_mask || tx_mask)
		tdm_en = RT1011_TDM_I2S_DOCK_EN_1;

	चयन (slots) अणु
	हाल 4:
		val |= RT1011_I2S_TX_4CH;
		val |= RT1011_I2S_RX_4CH;
		अवरोध;
	हाल 6:
		val |= RT1011_I2S_TX_6CH;
		val |= RT1011_I2S_RX_6CH;
		अवरोध;
	हाल 8:
		val |= RT1011_I2S_TX_8CH;
		val |= RT1011_I2S_RX_8CH;
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= RT1011_I2S_CH_TX_LEN_20B;
		val |= RT1011_I2S_CH_RX_LEN_20B;
		अवरोध;
	हाल 24:
		val |= RT1011_I2S_CH_TX_LEN_24B;
		val |= RT1011_I2S_CH_RX_LEN_24B;
		अवरोध;
	हाल 32:
		val |= RT1011_I2S_CH_TX_LEN_32B;
		val |= RT1011_I2S_CH_RX_LEN_32B;
		अवरोध;
	हाल 16:
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	/* Rx slot configuration */
	rx_slotnum = hweight_दीर्घ(rx_mask);
	अगर (rx_slotnum > 1 || !rx_slotnum) अणु
		ret = -EINVAL;
		dev_err(component->dev, "too many rx slots or zero slot\n");
		जाओ _set_tdm_err_;
	पूर्ण

	first_bit = __ffs(rx_mask);
	चयन (first_bit) अणु
	हाल 0:
	हाल 2:
	हाल 4:
	हाल 6:
		snd_soc_component_update_bits(component,
			RT1011_CROSS_BQ_SET_1, RT1011_MONO_LR_SEL_MASK,
			RT1011_MONO_L_CHANNEL);
		snd_soc_component_update_bits(component,
			RT1011_TDM1_SET_4,
			RT1011_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1011_TDM_I2S_TX_R_DAC1_1_MASK,
			(first_bit << RT1011_TDM_I2S_TX_L_DAC1_1_SFT) |
			((first_bit+1) << RT1011_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	हाल 1:
	हाल 3:
	हाल 5:
	हाल 7:
		snd_soc_component_update_bits(component,
			RT1011_CROSS_BQ_SET_1, RT1011_MONO_LR_SEL_MASK,
			RT1011_MONO_R_CHANNEL);
		snd_soc_component_update_bits(component,
			RT1011_TDM1_SET_4,
			RT1011_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1011_TDM_I2S_TX_R_DAC1_1_MASK,
			((first_bit-1) << RT1011_TDM_I2S_TX_L_DAC1_1_SFT) |
			(first_bit << RT1011_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	/* Tx slot configuration */
	tx_slotnum = hweight_दीर्घ(tx_mask);
	अगर (tx_slotnum > 2 || !tx_slotnum) अणु
		ret = -EINVAL;
		dev_err(component->dev, "too many tx slots or zero slot\n");
		जाओ _set_tdm_err_;
	पूर्ण

	first_bit = __ffs(tx_mask);
	last_bit = __fls(tx_mask);
	अगर (last_bit - first_bit > 1) अणु
		ret = -EINVAL;
		dev_err(component->dev, "tx slot location error\n");
		जाओ _set_tdm_err_;
	पूर्ण

	अगर (tx_slotnum == 1) अणु
		snd_soc_component_update_bits(component, RT1011_TDM1_SET_2,
			RT1011_TDM_I2S_DOCK_ADCDAT_LEN_1_MASK |
			RT1011_TDM_ADCDAT1_DATA_LOCATION, first_bit);
		चयन (first_bit) अणु
		हाल 1:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC1_1_MASK,
				RT1011_TDM_I2S_RX_ADC1_1_LL);
			अवरोध;
		हाल 3:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC2_1_MASK,
				RT1011_TDM_I2S_RX_ADC2_1_LL);
			अवरोध;
		हाल 5:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC3_1_MASK,
				RT1011_TDM_I2S_RX_ADC3_1_LL);
			अवरोध;
		हाल 7:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC4_1_MASK,
				RT1011_TDM_I2S_RX_ADC4_1_LL);
			अवरोध;
		हाल 0:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC1_1_MASK, 0);
			अवरोध;
		हाल 2:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC2_1_MASK, 0);
			अवरोध;
		हाल 4:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC3_1_MASK, 0);
			अवरोध;
		हाल 6:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_3,
				RT1011_TDM_I2S_RX_ADC4_1_MASK, 0);
			अवरोध;
		शेष:
			ret = -EINVAL;
			dev_dbg(component->dev,
				"tx slot location error\n");
			जाओ _set_tdm_err_;
		पूर्ण
	पूर्ण अन्यथा अगर (tx_slotnum == 2) अणु
		चयन (first_bit) अणु
		हाल 0:
		हाल 2:
		हाल 4:
		हाल 6:
			snd_soc_component_update_bits(component,
				RT1011_TDM1_SET_2,
				RT1011_TDM_I2S_DOCK_ADCDAT_LEN_1_MASK |
				RT1011_TDM_ADCDAT1_DATA_LOCATION,
				RT1011_TDM_I2S_DOCK_ADCDAT_2CH | first_bit);
			अवरोध;
		शेष:
			ret = -EINVAL;
			dev_dbg(component->dev,
				"tx slot location should be paired and start from slot0/2/4/6\n");
			जाओ _set_tdm_err_;
		पूर्ण
	पूर्ण

	snd_soc_component_update_bits(component, RT1011_TDM1_SET_1,
		RT1011_I2S_CH_TX_MASK | RT1011_I2S_CH_RX_MASK |
		RT1011_I2S_CH_TX_LEN_MASK | RT1011_I2S_CH_RX_LEN_MASK, val);
	snd_soc_component_update_bits(component, RT1011_TDM2_SET_1,
		RT1011_I2S_CH_TX_MASK | RT1011_I2S_CH_RX_MASK |
		RT1011_I2S_CH_TX_LEN_MASK | RT1011_I2S_CH_RX_LEN_MASK, val);
	snd_soc_component_update_bits(component, RT1011_TDM1_SET_2,
		RT1011_TDM_I2S_DOCK_EN_1_MASK, tdm_en);
	snd_soc_component_update_bits(component, RT1011_TDM2_SET_2,
		RT1011_TDM_I2S_DOCK_EN_2_MASK, tdm_en);

	snd_soc_component_update_bits(component, RT1011_TDM_TOTAL_SET,
		RT1011_ADCDAT1_PIN_CONFIG | RT1011_ADCDAT2_PIN_CONFIG,
		RT1011_ADCDAT1_OUTPUT | RT1011_ADCDAT2_OUTPUT);

_set_tdm_err_:
	snd_soc_dapm_mutex_unlock(dapm);
	वापस ret;
पूर्ण

अटल पूर्णांक rt1011_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	rt1011->component = component;

	schedule_work(&rt1011->cali_work);

	rt1011->bq_drc_params = devm_kसुस्मृति(component->dev,
		RT1011_ADVMODE_NUM, माप(काष्ठा rt1011_bq_drc_params *),
		GFP_KERNEL);
	अगर (!rt1011->bq_drc_params)
		वापस -ENOMEM;

	क्रम (i = 0; i < RT1011_ADVMODE_NUM; i++) अणु
		rt1011->bq_drc_params[i] = devm_kसुस्मृति(component->dev,
			RT1011_BQ_DRC_NUM, माप(काष्ठा rt1011_bq_drc_params),
			GFP_KERNEL);
		अगर (!rt1011->bq_drc_params[i])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt1011_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	cancel_work_sync(&rt1011->cali_work);
	rt1011_reset(rt1011->regmap);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1011_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1011->regmap, true);
	regcache_mark_dirty(rt1011->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1011->regmap, false);
	regcache_sync(rt1011->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1011_suspend शून्य
#घोषणा rt1011_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक rt1011_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_1, 0x0000);
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_2, 0x0000);
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_3, 0x0001);
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_1, 0x003f);
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_2, 0x7fd7);
		snd_soc_component_ग_लिखो(component,
			RT1011_SYSTEM_RESET_3, 0x770f);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RT1011_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT1011_FORMATS (SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1011_aअगर_dai_ops = अणु
	.hw_params = rt1011_hw_params,
	.set_fmt = rt1011_set_dai_fmt,
	.set_tdm_slot = rt1011_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1011_dai[] = अणु
	अणु
		.name = "rt1011-aif",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1011_STEREO_RATES,
			.क्रमmats = RT1011_FORMATS,
		पूर्ण,
		.ops = &rt1011_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1011 = अणु
	.probe = rt1011_probe,
	.हटाओ = rt1011_हटाओ,
	.suspend = rt1011_suspend,
	.resume = rt1011_resume,
	.set_bias_level = rt1011_set_bias_level,
	.controls = rt1011_snd_controls,
	.num_controls = ARRAY_SIZE(rt1011_snd_controls),
	.dapm_widमाला_लो = rt1011_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1011_dapm_widमाला_लो),
	.dapm_routes = rt1011_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1011_dapm_routes),
	.set_sysclk = rt1011_set_component_sysclk,
	.set_pll = rt1011_set_component_pll,
	.use_pmकरोwn_समय = 1,
	.endianness = 1,
	.non_legacy_dai_naming = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1011_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = RT1011_MAX_REG + 1,
	.अस्थिर_reg = rt1011_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1011_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1011_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1011_reg),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt1011_of_match[] = अणु
	अणु .compatible = "realtek,rt1011", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1011_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1011_acpi_match[] = अणु
	अणु"10EC1011", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1011_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id rt1011_i2c_id[] = अणु
	अणु "rt1011", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1011_i2c_id);

अटल पूर्णांक rt1011_calibrate(काष्ठा rt1011_priv *rt1011, अचिन्हित अक्षर cali_flag)
अणु
	अचिन्हित पूर्णांक value, count = 0, r0[3];
	अचिन्हित पूर्णांक chk_cnt = 50; /* DONT change this */
	अचिन्हित पूर्णांक dc_offset;
	अचिन्हित पूर्णांक r0_पूर्णांकeger, r0_factor, क्रमmat;
	काष्ठा device *dev = regmap_get_device(rt1011->regmap);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(rt1011->component);
	पूर्णांक ret = 0;

	snd_soc_dapm_mutex_lock(dapm);
	regcache_cache_bypass(rt1011->regmap, true);

	regmap_ग_लिखो(rt1011->regmap, RT1011_RESET, 0x0000);
	regmap_ग_लिखो(rt1011->regmap, RT1011_SYSTEM_RESET_3, 0x740f);
	regmap_ग_लिखो(rt1011->regmap, RT1011_SYSTEM_RESET_3, 0x770f);

	/* RC घड़ी */
	regmap_ग_लिखो(rt1011->regmap, RT1011_CLK_2, 0x9400);
	regmap_ग_लिखो(rt1011->regmap, RT1011_PLL_1, 0x0800);
	regmap_ग_लिखो(rt1011->regmap, RT1011_PLL_2, 0x0020);
	regmap_ग_लिखो(rt1011->regmap, RT1011_CLK_DET, 0x0800);

	/* ADC/DAC setting */
	regmap_ग_लिखो(rt1011->regmap, RT1011_ADC_SET_5, 0x0a20);
	regmap_ग_लिखो(rt1011->regmap, RT1011_DAC_SET_2, 0xe232);
	regmap_ग_लिखो(rt1011->regmap, RT1011_ADC_SET_4, 0xc000);

	/* DC detection */
	regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_PRO_DC_DET_1, 0xb00c);
	regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_PRO_DC_DET_2, 0xcccc);

	/* Power */
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_1, 0xe0e0);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_3, 0x5003);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_9, 0xa860);
	regmap_ग_लिखो(rt1011->regmap, RT1011_DAC_SET_2, 0xa032);

	/* POW_PLL / POW_BG / POW_BG_MBIAS_LV / POW_V/I */
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_2, 0x0007);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_3, 0x5ff7);
	regmap_ग_लिखो(rt1011->regmap, RT1011_A_TEMP_SEN, 0x7f44);
	regmap_ग_लिखो(rt1011->regmap, RT1011_A_TIMING_1, 0x4054);
	regmap_ग_लिखो(rt1011->regmap, RT1011_BAT_GAIN_1, 0x309c);

	/* DC offset from EFUSE */
	regmap_ग_लिखो(rt1011->regmap, RT1011_DC_CALIB_CLASSD_3, 0xcb00);
	regmap_ग_लिखो(rt1011->regmap, RT1011_BOOST_CON_1, 0xe080);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_4, 0x16f2);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_6, 0x36ad);

	/* mixer */
	regmap_ग_लिखो(rt1011->regmap, RT1011_MIXER_1, 0x3f1d);

	/* EFUSE पढ़ो */
	regmap_ग_लिखो(rt1011->regmap, RT1011_EFUSE_CONTROL_1, 0x0d0a);
	msleep(30);

	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_ADC_OFFSET_18_16, &value);
	dc_offset = value << 16;
	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_ADC_OFFSET_15_0, &value);
	dc_offset |= (value & 0xffff);
	dev_info(dev, "ADC offset=0x%x\n", dc_offset);
	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_DAC_OFFSET_G0_20_16, &value);
	dc_offset = value << 16;
	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_DAC_OFFSET_G0_15_0, &value);
	dc_offset |= (value & 0xffff);
	dev_info(dev, "Gain0 offset=0x%x\n", dc_offset);
	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_DAC_OFFSET_G1_20_16, &value);
	dc_offset = value << 16;
	regmap_पढ़ो(rt1011->regmap, RT1011_EFUSE_DAC_OFFSET_G1_15_0, &value);
	dc_offset |= (value & 0xffff);
	dev_info(dev, "Gain1 offset=0x%x\n", dc_offset);

	अगर (cali_flag) अणु

		regmap_ग_लिखो(rt1011->regmap, RT1011_ADC_SET_1, 0x2925);
		/* Class D on */
		regmap_ग_लिखो(rt1011->regmap, RT1011_CLASS_D_POS, 0x010e);
		regmap_ग_लिखो(rt1011->regmap,
			RT1011_CLASSD_INTERNAL_SET_1, 0x1701);

		/* STP enable */
		regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_0, 0x8000);
		regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_7, 0xf000);
		regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_4, 0x4040);
		regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_0, 0xc000);
		regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_6, 0x07c2);

		r0[0] = r0[1] = r0[2] = count = 0;
		जबतक (count < chk_cnt) अणु
			msleep(100);
			regmap_पढ़ो(rt1011->regmap,
				RT1011_INIT_RECIPROCAL_SYN_24_16, &value);
			r0[count%3] = value << 16;
			regmap_पढ़ो(rt1011->regmap,
				RT1011_INIT_RECIPROCAL_SYN_15_0, &value);
			r0[count%3] |= value;

			अगर (r0[count%3] == 0)
				जारी;

			count++;

			अगर (r0[0] == r0[1] && r0[1] == r0[2])
				अवरोध;
		पूर्ण
		अगर (count > chk_cnt) अणु
			dev_err(dev, "Calibrate R0 Failure\n");
			ret = -EAGAIN;
		पूर्ण अन्यथा अणु
			क्रमmat = 2147483648U; /* 2^24 * 128 */
			r0_पूर्णांकeger = क्रमmat / r0[0] / 128;
			r0_factor = ((क्रमmat / r0[0] * 100) / 128)
							- (r0_पूर्णांकeger * 100);
			rt1011->r0_reg = r0[0];
			rt1011->cali_करोne = 1;
			dev_info(dev, "r0 resistance about %d.%02d ohm, reg=0x%X\n",
				r0_पूर्णांकeger, r0_factor, r0[0]);
		पूर्ण
	पूर्ण

	/* depop */
	regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_0, 0x0000);
	msleep(400);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_9, 0xa840);
	regmap_ग_लिखो(rt1011->regmap, RT1011_SPK_TEMP_PROTECT_6, 0x0702);
	regmap_ग_लिखो(rt1011->regmap, RT1011_MIXER_1, 0xffdd);
	regmap_ग_लिखो(rt1011->regmap, RT1011_CLASSD_INTERNAL_SET_1, 0x0701);
	regmap_ग_लिखो(rt1011->regmap, RT1011_DAC_SET_3, 0xe004);
	regmap_ग_लिखो(rt1011->regmap, RT1011_A_TEMP_SEN, 0x7f40);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_1, 0x0000);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_2, 0x0000);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_3, 0x0002);
	regmap_ग_लिखो(rt1011->regmap, RT1011_POWER_4, 0x00f2);

	regmap_ग_लिखो(rt1011->regmap, RT1011_RESET, 0x0000);

	अगर (cali_flag) अणु
		अगर (count <= chk_cnt) अणु
			regmap_ग_लिखो(rt1011->regmap,
				RT1011_INIT_RECIPROCAL_REG_24_16,
				((r0[0]>>16) & 0x1ff));
			regmap_ग_लिखो(rt1011->regmap,
				RT1011_INIT_RECIPROCAL_REG_15_0,
				(r0[0] & 0xffff));
			regmap_ग_लिखो(rt1011->regmap,
				RT1011_SPK_TEMP_PROTECT_4, 0x4080);
		पूर्ण
	पूर्ण

	regcache_cache_bypass(rt1011->regmap, false);
	regcache_mark_dirty(rt1011->regmap);
	regcache_sync(rt1011->regmap);
	snd_soc_dapm_mutex_unlock(dapm);

	वापस ret;
पूर्ण

अटल व्योम rt1011_calibration_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt1011_priv *rt1011 =
		container_of(work, काष्ठा rt1011_priv, cali_work);
	काष्ठा snd_soc_component *component = rt1011->component;
	अचिन्हित पूर्णांक r0_पूर्णांकeger, r0_factor, क्रमmat;

	अगर (rt1011->r0_calib)
		rt1011_calibrate(rt1011, 0);
	अन्यथा
		rt1011_calibrate(rt1011, 1);

	/*
	 * This flag should reset after booting.
	 * The factory test will करो calibration again and use this flag to check
	 * whether the calibration completed
	 */
	rt1011->cali_करोne = 0;

	/* initial */
	rt1011_reg_init(component);

	/* Apply temperature and calibration data from device property */
	अगर (rt1011->temperature_calib <= 0xff &&
		rt1011->temperature_calib > 0) अणु
		snd_soc_component_update_bits(component,
			RT1011_STP_INITIAL_RESISTANCE_TEMP, 0x3ff,
			(rt1011->temperature_calib << 2));
	पूर्ण

	अगर (rt1011->r0_calib) अणु
		rt1011->r0_reg = rt1011->r0_calib;

		क्रमmat = 2147483648U; /* 2^24 * 128 */
		r0_पूर्णांकeger = क्रमmat / rt1011->r0_reg / 128;
		r0_factor = ((क्रमmat / rt1011->r0_reg * 100) / 128)
						- (r0_पूर्णांकeger * 100);
		dev_info(component->dev, "DP r0 resistance about %d.%02d ohm, reg=0x%X\n",
			r0_पूर्णांकeger, r0_factor, rt1011->r0_reg);

		rt1011_r0_load(rt1011);
	पूर्ण

	snd_soc_component_ग_लिखो(component, RT1011_ADC_SET_1, 0x2925);
पूर्ण

अटल पूर्णांक rt1011_parse_dp(काष्ठा rt1011_priv *rt1011, काष्ठा device *dev)
अणु
	device_property_पढ़ो_u32(dev, "realtek,temperature_calib",
		&rt1011->temperature_calib);
	device_property_पढ़ो_u32(dev, "realtek,r0_calib",
		&rt1011->r0_calib);

	dev_dbg(dev, "%s: r0_calib: 0x%x, temperature_calib: 0x%x",
		__func__, rt1011->r0_calib, rt1011->temperature_calib);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1011_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1011_priv *rt1011;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt1011 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt1011_priv),
				GFP_KERNEL);
	अगर (!rt1011)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1011);

	rt1011_parse_dp(rt1011, &i2c->dev);

	rt1011->regmap = devm_regmap_init_i2c(i2c, &rt1011_regmap);
	अगर (IS_ERR(rt1011->regmap)) अणु
		ret = PTR_ERR(rt1011->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt1011->regmap, RT1011_DEVICE_ID, &val);
	अगर (val != RT1011_DEVICE_ID_NUM) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1011\n", val);
		वापस -ENODEV;
	पूर्ण

	INIT_WORK(&rt1011->cali_work, rt1011_calibration_work);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&soc_component_dev_rt1011,
		rt1011_dai, ARRAY_SIZE(rt1011_dai));

पूर्ण

अटल व्योम rt1011_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1011_priv *rt1011 = i2c_get_clientdata(client);

	rt1011_reset(rt1011->regmap);
पूर्ण

अटल काष्ठा i2c_driver rt1011_i2c_driver = अणु
	.driver = अणु
		.name = "rt1011",
		.of_match_table = of_match_ptr(rt1011_of_match),
		.acpi_match_table = ACPI_PTR(rt1011_acpi_match)
	पूर्ण,
	.probe = rt1011_i2c_probe,
	.shutकरोwn = rt1011_i2c_shutकरोwn,
	.id_table = rt1011_i2c_id,
पूर्ण;
module_i2c_driver(rt1011_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1011 amplifier driver");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL");
