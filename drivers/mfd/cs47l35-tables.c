<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regmap tables क्रम CS47L35 codec
 *
 * Copyright (C) 2015-2017 Cirrus Logic
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#समावेश "madera.h"

अटल स्थिर काष्ठा reg_sequence cs47l35_reva_16_patch[] = अणु
	अणु 0x460, 0x0c40 पूर्ण,
	अणु 0x461, 0xcd1a पूर्ण,
	अणु 0x462, 0x0c40 पूर्ण,
	अणु 0x463, 0xb53b पूर्ण,
	अणु 0x464, 0x0c40 पूर्ण,
	अणु 0x465, 0x7503 पूर्ण,
	अणु 0x466, 0x0c40 पूर्ण,
	अणु 0x467, 0x4a41 पूर्ण,
	अणु 0x468, 0x0041 पूर्ण,
	अणु 0x469, 0x3491 पूर्ण,
	अणु 0x46a, 0x0841 पूर्ण,
	अणु 0x46b, 0x1f50 पूर्ण,
	अणु 0x46c, 0x0446 पूर्ण,
	अणु 0x46d, 0x14ed पूर्ण,
	अणु 0x46e, 0x0446 पूर्ण,
	अणु 0x46f, 0x1455 पूर्ण,
	अणु 0x470, 0x04c6 पूर्ण,
	अणु 0x471, 0x1220 पूर्ण,
	अणु 0x472, 0x04c6 पूर्ण,
	अणु 0x473, 0x040f पूर्ण,
	अणु 0x474, 0x04ce पूर्ण,
	अणु 0x475, 0x0339 पूर्ण,
	अणु 0x476, 0x05df पूर्ण,
	अणु 0x477, 0x028f पूर्ण,
	अणु 0x478, 0x05df पूर्ण,
	अणु 0x479, 0x0209 पूर्ण,
	अणु 0x47a, 0x05df पूर्ण,
	अणु 0x47b, 0x00cf पूर्ण,
	अणु 0x47c, 0x05df पूर्ण,
	अणु 0x47d, 0x0001 पूर्ण,
	अणु 0x47e, 0x07ff पूर्ण,
पूर्ण;

पूर्णांक cs47l35_patch(काष्ठा madera *madera)
अणु
	पूर्णांक ret;

	ret = regmap_रेजिस्टर_patch(madera->regmap, cs47l35_reva_16_patch,
				    ARRAY_SIZE(cs47l35_reva_16_patch));
	अगर (ret < 0)
		dev_err(madera->dev, "Error applying patch: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cs47l35_patch);

अटल स्थिर काष्ठा reg_शेष cs47l35_reg_शेष[] = अणु
	अणु 0x00000020, 0x0000 पूर्ण, /* R32 (0x20) - Tone Generator 1 */
	अणु 0x00000021, 0x1000 पूर्ण, /* R33 (0x21) - Tone Generator 2 */
	अणु 0x00000022, 0x0000 पूर्ण, /* R34 (0x22) - Tone Generator 3 */
	अणु 0x00000023, 0x1000 पूर्ण, /* R35 (0x23) - Tone Generator 4 */
	अणु 0x00000024, 0x0000 पूर्ण, /* R36 (0x24) - Tone Generator 5 */
	अणु 0x00000030, 0x0000 पूर्ण, /* R48 (0x30) - PWM Drive 1 */
	अणु 0x00000031, 0x0100 पूर्ण, /* R49 (0x31) - PWM Drive 2 */
	अणु 0x00000032, 0x0100 पूर्ण, /* R50 (0x32) - PWM Drive 3 */
	अणु 0x00000061, 0x01ff पूर्ण, /* R97 (0x61) - Sample Rate Sequence Select 1 */
	अणु 0x00000062, 0x01ff पूर्ण, /* R98 (0x62) - Sample Rate Sequence Select 2 */
	अणु 0x00000063, 0x01ff पूर्ण, /* R99 (0x63) - Sample Rate Sequence Select 3 */
	अणु 0x00000064, 0x01ff पूर्ण, /* R100 (0x64) - Sample Rate Sequence Select 4*/
	अणु 0x00000066, 0x01ff पूर्ण, /* R102 (0x66) - Always On Triggers Sequence Select 1*/
	अणु 0x00000067, 0x01ff पूर्ण, /* R103 (0x67) - Always On Triggers Sequence Select 2*/
	अणु 0x00000090, 0x0000 पूर्ण, /* R144 (0x90) - Haptics Control 1 */
	अणु 0x00000091, 0x7fff पूर्ण, /* R145 (0x91) - Haptics Control 2 */
	अणु 0x00000092, 0x0000 पूर्ण, /* R146 (0x92) - Haptics phase 1 पूर्णांकensity */
	अणु 0x00000093, 0x0000 पूर्ण, /* R147 (0x93) - Haptics phase 1 duration */
	अणु 0x00000094, 0x0000 पूर्ण, /* R148 (0x94) - Haptics phase 2 पूर्णांकensity */
	अणु 0x00000095, 0x0000 पूर्ण, /* R149 (0x95) - Haptics phase 2 duration */
	अणु 0x00000096, 0x0000 पूर्ण, /* R150 (0x96) - Haptics phase 3 पूर्णांकensity */
	अणु 0x00000097, 0x0000 पूर्ण, /* R151 (0x97) - Haptics phase 3 duration */
	अणु 0x000000A0, 0x0000 पूर्ण, /* R160 (0xa0) - Comक्रमt Noise Generator */
	अणु 0x00000100, 0x0002 पूर्ण, /* R256 (0x100) - Clock 32k 1 */
	अणु 0x00000101, 0x0404 पूर्ण, /* R257 (0x101) - System Clock 1 */
	अणु 0x00000102, 0x0011 पूर्ण, /* R258 (0x102) - Sample rate 1 */
	अणु 0x00000103, 0x0011 पूर्ण, /* R259 (0x103) - Sample rate 2 */
	अणु 0x00000104, 0x0011 पूर्ण, /* R260 (0x104) - Sample rate 3 */
	अणु 0x00000120, 0x0305 पूर्ण, /* R288 (0x120) - DSP Clock 1 */
	अणु 0x00000122, 0x0000 पूर्ण, /* R290 (0x122) - DSP Clock 2 */
	अणु 0x00000149, 0x0000 पूर्ण, /* R329 (0x149) - Output प्रणाली घड़ी */
	अणु 0x0000014a, 0x0000 पूर्ण, /* R330 (0x14a) - Output async घड़ी */
	अणु 0x00000152, 0x0000 पूर्ण, /* R338 (0x152) - Rate Estimator 1 */
	अणु 0x00000153, 0x0000 पूर्ण, /* R339 (0x153) - Rate Estimator 2 */
	अणु 0x00000154, 0x0000 पूर्ण, /* R340 (0x154) - Rate Estimator 3 */
	अणु 0x00000155, 0x0000 पूर्ण, /* R341 (0x155) - Rate Estimator 4 */
	अणु 0x00000156, 0x0000 पूर्ण, /* R342 (0x156) - Rate Estimator 5 */
	अणु 0x00000171, 0x0002 पूर्ण, /* R369 (0x171) - FLL1 Control 1 */
	अणु 0x00000172, 0x0008 पूर्ण, /* R370 (0x172) - FLL1 Control 2 */
	अणु 0x00000173, 0x0018 पूर्ण, /* R371 (0x173) - FLL1 Control 3 */
	अणु 0x00000174, 0x007d पूर्ण, /* R372 (0x174) - FLL1 Control 4 */
	अणु 0x00000175, 0x0000 पूर्ण, /* R373 (0x175) - FLL1 Control 5 */
	अणु 0x00000176, 0x0000 पूर्ण, /* R374 (0x176) - FLL1 Control 6 */
	अणु 0x00000179, 0x0000 पूर्ण, /* R377 (0x179) - FLL1 Control 7 */
	अणु 0x0000017a, 0x2906 पूर्ण, /* R378 (0x17a) - FLL1 EFS2 */
	अणु 0x0000017f, 0x0000 पूर्ण, /* R383 (0x17f) - FLL1 Synchroniser 1 */
	अणु 0x00000180, 0x0000 पूर्ण, /* R384 (0x180) - FLL1 Synchroniser 2 */
	अणु 0x00000181, 0x0000 पूर्ण, /* R385 (0x181) - FLL1 Synchroniser 3 */
	अणु 0x00000182, 0x0000 पूर्ण, /* R386 (0x182) - FLL1 Synchroniser 4 */
	अणु 0x00000183, 0x0000 पूर्ण, /* R387 (0x183) - FLL1 Synchroniser 5 */
	अणु 0x00000184, 0x0000 पूर्ण, /* R388 (0x184) - FLL1 Synchroniser 6 */
	अणु 0x00000185, 0x0001 पूर्ण, /* R389 (0x185) - FLL1 Synchroniser 7 */
	अणु 0x00000187, 0x0000 पूर्ण, /* R391 (0x187) - FLL1 Spपढ़ो Spectrum */
	अणु 0x00000188, 0x000c पूर्ण, /* R392 (0x188) - FLL1 GPIO Clock */
	अणु 0x00000200, 0x0006 पूर्ण, /* R512 (0x200) - Mic Charge Pump 1 */
	अणु 0x0000020b, 0x0400 पूर्ण, /* R523 (0x20b) - HP Charge Pump 8 */
	अणु 0x00000213, 0x03e4 पूर्ण, /* R531 (0x213) - LDO2 Control 1 */
	अणु 0x00000218, 0x00e6 पूर्ण, /* R536 (0x218) - Mic Bias Ctrl 1 */
	अणु 0x00000219, 0x00e6 पूर्ण, /* R537 (0x219) - Mic Bias Ctrl 2 */
	अणु 0x0000021c, 0x0022 पूर्ण, /* R540 (0x21c) - Mic Bias Ctrl 5 */
	अणु 0x0000021e, 0x0022 पूर्ण, /* R542 (0x21e) - Mic Bias Ctrl 6 */
	अणु 0x0000027e, 0x0000 पूर्ण, /* R638 (0x27e) - EDRE HP stereo control */
	अणु 0x00000293, 0x0080 पूर्ण, /* R659 (0x293) - Accessory Detect Mode 1 */
	अणु 0x0000029b, 0x0000 पूर्ण, /* R667 (0x29b) - Headphone Detect 1 */
	अणु 0x000002a3, 0x1102 पूर्ण, /* R675 (0x2a3) - Mic Detect Control 1 */
	अणु 0x000002a4, 0x009f पूर्ण, /* R676 (0x2a4) - Mic Detect Control 2 */
	अणु 0x000002a6, 0x3d3d पूर्ण, /* R678 (0x2a6) - Mic Detect Level 1 */
	अणु 0x000002a7, 0x3d3d पूर्ण, /* R679 (0x2a7) - Mic Detect Level 2 */
	अणु 0x000002a8, 0x333d पूर्ण, /* R680 (0x2a8) - Mic Detect Level 3 */
	अणु 0x000002a9, 0x202d पूर्ण, /* R681 (0x2a9) - Mic Detect Level 4 */
	अणु 0x000002c6, 0x0010 पूर्ण, /* R710 (0x2c5) - Mic Clamp control */
	अणु 0x000002c8, 0x0000 पूर्ण, /* R712 (0x2c8) - GP चयन 1 */
	अणु 0x000002d3, 0x0000 पूर्ण, /* R723 (0x2d3) - Jack detect analogue */
	अणु 0x00000300, 0x0000 पूर्ण, /* R768 (0x300) - Input Enables */
	अणु 0x00000308, 0x0000 पूर्ण, /* R776 (0x308) - Input Rate */
	अणु 0x00000309, 0x0022 पूर्ण, /* R777 (0x309) - Input Volume Ramp */
	अणु 0x0000030c, 0x0002 पूर्ण, /* R780 (0x30c) - HPF Control */
	अणु 0x00000310, 0x0080 पूर्ण, /* R784 (0x310) - IN1L Control */
	अणु 0x00000311, 0x0180 पूर्ण, /* R785 (0x311) - ADC Digital Volume 1L */
	अणु 0x00000312, 0x0500 पूर्ण, /* R786 (0x312) - DMIC1L Control */
	अणु 0x00000314, 0x0080 पूर्ण, /* R788 (0x314) - IN1R Control */
	अणु 0x00000315, 0x0180 पूर्ण, /* R789 (0x315) - ADC Digital Volume 1R */
	अणु 0x00000316, 0x0000 पूर्ण, /* R790 (0x316) - DMIC1R Control */
	अणु 0x00000318, 0x0080 पूर्ण, /* R792 (0x318) - IN2L Control */
	अणु 0x00000319, 0x0180 पूर्ण, /* R793 (0x319) - ADC Digital Volume 2L */
	अणु 0x0000031a, 0x0500 पूर्ण, /* R794 (0x31a) - DMIC2L Control */
	अणु 0x0000031c, 0x0080 पूर्ण, /* R796 (0x31c) - IN2R Control */
	अणु 0x0000031d, 0x0180 पूर्ण, /* R797 (0x31d) - ADC Digital Volume 2R */
	अणु 0x0000031e, 0x0000 पूर्ण, /* R798 (0x31e) - DMIC2R Control */
	अणु 0x00000400, 0x0000 पूर्ण, /* R1024 (0x400) - Output Enables 1 */
	अणु 0x00000408, 0x0000 पूर्ण, /* R1032 (0x408) - Output Rate 1 */
	अणु 0x00000409, 0x0022 पूर्ण, /* R1033 (0x409) - Output Volume Ramp */
	अणु 0x00000410, 0x0080 पूर्ण, /* R1040 (0x410) - Output Path Config 1L */
	अणु 0x00000411, 0x0180 पूर्ण, /* R1041 (0x411) - DAC Digital Volume 1L */
	अणु 0x00000413, 0x0001 पूर्ण, /* R1043 (0x413) - Noise Gate Select 1L */
	अणु 0x00000414, 0x0080 पूर्ण, /* R1044 (0x414) - Output Path Config 1R */
	अणु 0x00000415, 0x0180 पूर्ण, /* R1045 (0x415) - DAC Digital Volume 1R */
	अणु 0x00000417, 0x0002 पूर्ण, /* R1047 (0x417) - Noise Gate Select 1R */
	अणु 0x00000428, 0x0000 पूर्ण, /* R1064 (0x428) - Output Path Config 4L */
	अणु 0x00000429, 0x0180 पूर्ण, /* R1065 (0x429) - DAC Digital Volume 4L */
	अणु 0x0000042b, 0x0040 पूर्ण, /* R1067 (0x42b) - Noise Gate Select 4L */
	अणु 0x00000430, 0x0000 पूर्ण, /* R1072 (0x430) - Output Path Config 5L */
	अणु 0x00000431, 0x0180 पूर्ण, /* R1073 (0x431) - DAC Digital Volume 5L */
	अणु 0x00000433, 0x0100 पूर्ण, /* R1075 (0x433) - Noise Gate Select 5L */
	अणु 0x00000434, 0x0000 पूर्ण, /* R1076 (0x434) - Output Path Config 5R */
	अणु 0x00000435, 0x0180 पूर्ण, /* R1077 (0x435) - DAC Digital Volume 5R */
	अणु 0x00000437, 0x0200 पूर्ण, /* R1079 (0x437) - Noise Gate Select 5R */
	अणु 0x00000450, 0x0000 पूर्ण, /* R1104 (0x450) - DAC AEC Control 1 */
	अणु 0x00000451, 0x0000 पूर्ण, /* R1105 (0x451) - DAC AEC Control 2 */
	अणु 0x00000458, 0x0000 पूर्ण, /* R1112 (0x458) - Noise Gate Control */
	अणु 0x00000490, 0x0069 पूर्ण, /* R1168 (0x490) - PDM SPK1 CTRL 1 */
	अणु 0x00000491, 0x0000 पूर्ण, /* R1169 (0x491) - PDM SPK1 CTRL 2 */
	अणु 0x000004a0, 0x3080 पूर्ण, /* R1184 (0x4a0) - HP1 Short Circuit Ctrl */
	अणु 0x000004a8, 0x7120 पूर्ण, /* R1192 (0x4a8) - HP Test Ctrl 5 */
	अणु 0x000004a9, 0x7120 पूर्ण, /* R1193 (0x4a9) - HP Test Ctrl 6 */
	अणु 0x00000500, 0x000c पूर्ण, /* R1280 (0x500) - AIF1 BCLK Ctrl */
	अणु 0x00000501, 0x0000 पूर्ण, /* R1281 (0x501) - AIF1 Tx Pin Ctrl */
	अणु 0x00000502, 0x0000 पूर्ण, /* R1282 (0x502) - AIF1 Rx Pin Ctrl */
	अणु 0x00000503, 0x0000 पूर्ण, /* R1283 (0x503) - AIF1 Rate Ctrl */
	अणु 0x00000504, 0x0000 पूर्ण, /* R1284 (0x504) - AIF1 Format */
	अणु 0x00000506, 0x0040 पूर्ण, /* R1286 (0x506) - AIF1 Rx BCLK Rate */
	अणु 0x00000507, 0x1818 पूर्ण, /* R1287 (0x507) - AIF1 Frame Ctrl 1 */
	अणु 0x00000508, 0x1818 पूर्ण, /* R1288 (0x508) - AIF1 Frame Ctrl 2 */
	अणु 0x00000509, 0x0000 पूर्ण, /* R1289 (0x509) - AIF1 Frame Ctrl 3 */
	अणु 0x0000050a, 0x0001 पूर्ण, /* R1290 (0x50a) - AIF1 Frame Ctrl 4 */
	अणु 0x0000050b, 0x0002 पूर्ण, /* R1291 (0x50b) - AIF1 Frame Ctrl 5 */
	अणु 0x0000050c, 0x0003 पूर्ण, /* R1292 (0x50c) - AIF1 Frame Ctrl 6 */
	अणु 0x0000050d, 0x0004 पूर्ण, /* R1293 (0x50d) - AIF1 Frame Ctrl 7 */
	अणु 0x0000050e, 0x0005 पूर्ण, /* R1294 (0x50e) - AIF1 Frame Ctrl 8 */
	अणु 0x00000511, 0x0000 पूर्ण, /* R1297 (0x511) - AIF1 Frame Ctrl 11 */
	अणु 0x00000512, 0x0001 पूर्ण, /* R1298 (0x512) - AIF1 Frame Ctrl 12 */
	अणु 0x00000513, 0x0002 पूर्ण, /* R1299 (0x513) - AIF1 Frame Ctrl 13 */
	अणु 0x00000514, 0x0003 पूर्ण, /* R1300 (0x514) - AIF1 Frame Ctrl 14 */
	अणु 0x00000515, 0x0004 पूर्ण, /* R1301 (0x515) - AIF1 Frame Ctrl 15 */
	अणु 0x00000516, 0x0005 पूर्ण, /* R1302 (0x516) - AIF1 Frame Ctrl 16 */
	अणु 0x00000519, 0x0000 पूर्ण, /* R1305 (0x519) - AIF1 Tx Enables */
	अणु 0x0000051a, 0x0000 पूर्ण, /* R1306 (0x51a) - AIF1 Rx Enables */
	अणु 0x00000540, 0x000c पूर्ण, /* R1344 (0x540) - AIF2 BCLK Ctrl */
	अणु 0x00000541, 0x0000 पूर्ण, /* R1345 (0x541) - AIF2 Tx Pin Ctrl */
	अणु 0x00000542, 0x0000 पूर्ण, /* R1346 (0x542) - AIF2 Rx Pin Ctrl */
	अणु 0x00000543, 0x0000 पूर्ण, /* R1347 (0x543) - AIF2 Rate Ctrl */
	अणु 0x00000544, 0x0000 पूर्ण, /* R1348 (0x544) - AIF2 Format */
	अणु 0x00000546, 0x0040 पूर्ण, /* R1350 (0x546) - AIF2 Rx BCLK Rate */
	अणु 0x00000547, 0x1818 पूर्ण, /* R1351 (0x547) - AIF2 Frame Ctrl 1 */
	अणु 0x00000548, 0x1818 पूर्ण, /* R1352 (0x548) - AIF2 Frame Ctrl 2 */
	अणु 0x00000549, 0x0000 पूर्ण, /* R1353 (0x549) - AIF2 Frame Ctrl 3 */
	अणु 0x0000054a, 0x0001 पूर्ण, /* R1354 (0x54a) - AIF2 Frame Ctrl 4 */
	अणु 0x00000551, 0x0000 पूर्ण, /* R1361 (0x551) - AIF2 Frame Ctrl 11 */
	अणु 0x00000552, 0x0001 पूर्ण, /* R1362 (0x552) - AIF2 Frame Ctrl 12 */
	अणु 0x00000559, 0x0000 पूर्ण, /* R1369 (0x559) - AIF2 Tx Enables */
	अणु 0x0000055a, 0x0000 पूर्ण, /* R1370 (0x55a) - AIF2 Rx Enables */
	अणु 0x00000580, 0x000c पूर्ण, /* R1408 (0x580) - AIF3 BCLK Ctrl */
	अणु 0x00000581, 0x0000 पूर्ण, /* R1409 (0x581) - AIF3 Tx Pin Ctrl */
	अणु 0x00000582, 0x0000 पूर्ण, /* R1410 (0x582) - AIF3 Rx Pin Ctrl */
	अणु 0x00000583, 0x0000 पूर्ण, /* R1411 (0x583) - AIF3 Rate Ctrl */
	अणु 0x00000584, 0x0000 पूर्ण, /* R1412 (0x584) - AIF3 Format */
	अणु 0x00000586, 0x0040 पूर्ण, /* R1414 (0x586) - AIF3 Rx BCLK Rate */
	अणु 0x00000587, 0x1818 पूर्ण, /* R1415 (0x587) - AIF3 Frame Ctrl 1 */
	अणु 0x00000588, 0x1818 पूर्ण, /* R1416 (0x588) - AIF3 Frame Ctrl 2 */
	अणु 0x00000589, 0x0000 पूर्ण, /* R1417 (0x589) - AIF3 Frame Ctrl 3 */
	अणु 0x0000058a, 0x0001 पूर्ण, /* R1418 (0x58a) - AIF3 Frame Ctrl 4 */
	अणु 0x00000591, 0x0000 पूर्ण, /* R1425 (0x591) - AIF3 Frame Ctrl 11 */
	अणु 0x00000592, 0x0001 पूर्ण, /* R1426 (0x592) - AIF3 Frame Ctrl 12 */
	अणु 0x00000599, 0x0000 पूर्ण, /* R1433 (0x599) - AIF3 Tx Enables */
	अणु 0x0000059a, 0x0000 पूर्ण, /* R1434 (0x59a) - AIF3 Rx Enables */
	अणु 0x000005c2, 0x0000 पूर्ण, /* R1474 (0x5c2) - SPD1 TX Control */
	अणु 0x000005e3, 0x0000 पूर्ण, /* R1507 (0x5e3) - SLIMbus Framer Ref Gear */
	अणु 0x000005e5, 0x0000 पूर्ण, /* R1509 (0x5e5) - SLIMbus Rates 1 */
	अणु 0x000005e6, 0x0000 पूर्ण, /* R1510 (0x5e6) - SLIMbus Rates 2 */
	अणु 0x000005e7, 0x0000 पूर्ण, /* R1511 (0x5e7) - SLIMbus Rates 3 */
	अणु 0x000005e9, 0x0000 पूर्ण, /* R1513 (0x5e9) - SLIMbus Rates 5 */
	अणु 0x000005ea, 0x0000 पूर्ण, /* R1514 (0x5ea) - SLIMbus Rates 6 */
	अणु 0x000005eb, 0x0000 पूर्ण, /* R1515 (0x5eb) - SLIMbus Rates 7 */
	अणु 0x000005f5, 0x0000 पूर्ण, /* R1525 (0x5f5) - SLIMbus RX Channel Enable */
	अणु 0x000005f6, 0x0000 पूर्ण, /* R1526 (0x5f6) - SLIMbus TX Channel Enable */
	अणु 0x00000640, 0x0000 पूर्ण, /* R1600 (0x640) - PWM1MIX Input 1 Source */
	अणु 0x00000641, 0x0080 पूर्ण, /* R1601 (0x641) - PWM1MIX Input 1 Volume */
	अणु 0x00000642, 0x0000 पूर्ण, /* R1602 (0x642) - PWM1MIX Input 2 Source */
	अणु 0x00000643, 0x0080 पूर्ण, /* R1603 (0x643) - PWM1MIX Input 2 Volume */
	अणु 0x00000644, 0x0000 पूर्ण, /* R1604 (0x644) - PWM1MIX Input 3 Source */
	अणु 0x00000645, 0x0080 पूर्ण, /* R1605 (0x645) - PWM1MIX Input 3 Volume */
	अणु 0x00000646, 0x0000 पूर्ण, /* R1606 (0x646) - PWM1MIX Input 4 Source */
	अणु 0x00000647, 0x0080 पूर्ण, /* R1607 (0x647) - PWM1MIX Input 4 Volume */
	अणु 0x00000648, 0x0000 पूर्ण, /* R1608 (0x648) - PWM2MIX Input 1 Source */
	अणु 0x00000649, 0x0080 पूर्ण, /* R1609 (0x649) - PWM2MIX Input 1 Volume */
	अणु 0x0000064a, 0x0000 पूर्ण, /* R1610 (0x64a) - PWM2MIX Input 2 Source */
	अणु 0x0000064b, 0x0080 पूर्ण, /* R1611 (0x64b) - PWM2MIX Input 2 Volume */
	अणु 0x0000064c, 0x0000 पूर्ण, /* R1612 (0x64c) - PWM2MIX Input 3 Source */
	अणु 0x0000064d, 0x0080 पूर्ण, /* R1613 (0x64d) - PWM2MIX Input 3 Volume */
	अणु 0x0000064e, 0x0000 पूर्ण, /* R1614 (0x64e) - PWM2MIX Input 4 Source */
	अणु 0x0000064f, 0x0080 पूर्ण, /* R1615 (0x64f) - PWM2MIX Input 4 Volume */
	अणु 0x00000680, 0x0000 पूर्ण, /* R1664 (0x680) - OUT1LMIX Input 1 Source */
	अणु 0x00000681, 0x0080 पूर्ण, /* R1665 (0x681) - OUT1LMIX Input 1 Volume */
	अणु 0x00000682, 0x0000 पूर्ण, /* R1666 (0x682) - OUT1LMIX Input 2 Source */
	अणु 0x00000683, 0x0080 पूर्ण, /* R1667 (0x683) - OUT1LMIX Input 2 Volume */
	अणु 0x00000684, 0x0000 पूर्ण, /* R1668 (0x684) - OUT1LMIX Input 3 Source */
	अणु 0x00000685, 0x0080 पूर्ण, /* R1669 (0x685) - OUT1LMIX Input 3 Volume */
	अणु 0x00000686, 0x0000 पूर्ण, /* R1670 (0x686) - OUT1LMIX Input 4 Source */
	अणु 0x00000687, 0x0080 पूर्ण, /* R1671 (0x687) - OUT1LMIX Input 4 Volume */
	अणु 0x00000688, 0x0000 पूर्ण, /* R1672 (0x688) - OUT1RMIX Input 1 Source */
	अणु 0x00000689, 0x0080 पूर्ण, /* R1673 (0x689) - OUT1RMIX Input 1 Volume */
	अणु 0x0000068a, 0x0000 पूर्ण, /* R1674 (0x68a) - OUT1RMIX Input 2 Source */
	अणु 0x0000068b, 0x0080 पूर्ण, /* R1675 (0x68b) - OUT1RMIX Input 2 Volume */
	अणु 0x0000068c, 0x0000 पूर्ण, /* R1672 (0x68c) - OUT1RMIX Input 3 Source */
	अणु 0x0000068d, 0x0080 पूर्ण, /* R1673 (0x68d) - OUT1RMIX Input 3 Volume */
	अणु 0x0000068e, 0x0000 पूर्ण, /* R1674 (0x68e) - OUT1RMIX Input 4 Source */
	अणु 0x0000068f, 0x0080 पूर्ण, /* R1675 (0x68f) - OUT1RMIX Input 4 Volume */
	अणु 0x000006b0, 0x0000 पूर्ण, /* R1712 (0x6b0) - OUT4LMIX Input 1 Source */
	अणु 0x000006b1, 0x0080 पूर्ण, /* R1713 (0x6b1) - OUT4LMIX Input 1 Volume */
	अणु 0x000006b2, 0x0000 पूर्ण, /* R1714 (0x6b2) - OUT4LMIX Input 2 Source */
	अणु 0x000006b3, 0x0080 पूर्ण, /* R1715 (0x6b3) - OUT4LMIX Input 2 Volume */
	अणु 0x000006b4, 0x0000 पूर्ण, /* R1716 (0x6b4) - OUT4LMIX Input 3 Source */
	अणु 0x000006b5, 0x0080 पूर्ण, /* R1717 (0x6b5) - OUT4LMIX Input 3 Volume */
	अणु 0x000006b6, 0x0000 पूर्ण, /* R1718 (0x6b6) - OUT4LMIX Input 4 Source */
	अणु 0x000006b7, 0x0080 पूर्ण, /* R1719 (0x6b7) - OUT4LMIX Input 4 Volume */
	अणु 0x000006c0, 0x0000 पूर्ण, /* R1728 (0x6c0) - OUT5LMIX Input 1 Source */
	अणु 0x000006c1, 0x0080 पूर्ण, /* R1729 (0x6c1) - OUT5LMIX Input 1 Volume */
	अणु 0x000006c2, 0x0000 पूर्ण, /* R1730 (0x6c2) - OUT5LMIX Input 2 Source */
	अणु 0x000006c3, 0x0080 पूर्ण, /* R1731 (0x6c3) - OUT5LMIX Input 2 Volume */
	अणु 0x000006c4, 0x0000 पूर्ण, /* R1732 (0x6c4) - OUT5LMIX Input 3 Source */
	अणु 0x000006c5, 0x0080 पूर्ण, /* R1733 (0x6c5) - OUT5LMIX Input 3 Volume */
	अणु 0x000006c6, 0x0000 पूर्ण, /* R1734 (0x6c6) - OUT5LMIX Input 4 Source */
	अणु 0x000006c7, 0x0080 पूर्ण, /* R1735 (0x6c7) - OUT5LMIX Input 4 Volume */
	अणु 0x000006c8, 0x0000 पूर्ण, /* R1736 (0x6c8) - OUT5RMIX Input 1 Source */
	अणु 0x000006c9, 0x0080 पूर्ण, /* R1737 (0x6c9) - OUT5RMIX Input 1 Volume */
	अणु 0x000006ca, 0x0000 पूर्ण, /* R1738 (0x6ca) - OUT5RMIX Input 2 Source */
	अणु 0x000006cb, 0x0080 पूर्ण, /* R1739 (0x6cb) - OUT5RMIX Input 2 Volume */
	अणु 0x000006cc, 0x0000 पूर्ण, /* R1740 (0x6cc) - OUT5RMIX Input 3 Source */
	अणु 0x000006cd, 0x0080 पूर्ण, /* R1741 (0x6cd) - OUT5RMIX Input 3 Volume */
	अणु 0x000006ce, 0x0000 पूर्ण, /* R1742 (0x6ce) - OUT5RMIX Input 4 Source */
	अणु 0x000006cf, 0x0080 पूर्ण, /* R1743 (0x6cf) - OUT5RMIX Input 4 Volume */
	अणु 0x00000700, 0x0000 पूर्ण, /* R1792 (0x700) - AIF1TX1MIX Input 1 Source */
	अणु 0x00000701, 0x0080 पूर्ण, /* R1793 (0x701) - AIF1TX1MIX Input 1 Volume */
	अणु 0x00000702, 0x0000 पूर्ण, /* R1794 (0x702) - AIF1TX1MIX Input 2 Source */
	अणु 0x00000703, 0x0080 पूर्ण, /* R1795 (0x703) - AIF1TX1MIX Input 2 Volume */
	अणु 0x00000704, 0x0000 पूर्ण, /* R1796 (0x704) - AIF1TX1MIX Input 3 Source */
	अणु 0x00000705, 0x0080 पूर्ण, /* R1797 (0x705) - AIF1TX1MIX Input 3 Volume */
	अणु 0x00000706, 0x0000 पूर्ण, /* R1798 (0x706) - AIF1TX1MIX Input 4 Source */
	अणु 0x00000707, 0x0080 पूर्ण, /* R1799 (0x707) - AIF1TX1MIX Input 4 Volume */
	अणु 0x00000708, 0x0000 पूर्ण, /* R1800 (0x708) - AIF1TX2MIX Input 1 Source */
	अणु 0x00000709, 0x0080 पूर्ण, /* R1801 (0x709) - AIF1TX2MIX Input 1 Volume */
	अणु 0x0000070a, 0x0000 पूर्ण, /* R1802 (0x70a) - AIF1TX2MIX Input 2 Source */
	अणु 0x0000070b, 0x0080 पूर्ण, /* R1803 (0x70b) - AIF1TX2MIX Input 2 Volume */
	अणु 0x0000070c, 0x0000 पूर्ण, /* R1804 (0x70c) - AIF1TX2MIX Input 3 Source */
	अणु 0x0000070d, 0x0080 पूर्ण, /* R1805 (0x70d) - AIF1TX2MIX Input 3 Volume */
	अणु 0x0000070e, 0x0000 पूर्ण, /* R1806 (0x70e) - AIF1TX2MIX Input 4 Source */
	अणु 0x0000070f, 0x0080 पूर्ण, /* R1807 (0x70f) - AIF1TX2MIX Input 4 Volume */
	अणु 0x00000710, 0x0000 पूर्ण, /* R1808 (0x710) - AIF1TX3MIX Input 1 Source */
	अणु 0x00000711, 0x0080 पूर्ण, /* R1809 (0x711) - AIF1TX3MIX Input 1 Volume */
	अणु 0x00000712, 0x0000 पूर्ण, /* R1810 (0x712) - AIF1TX3MIX Input 2 Source */
	अणु 0x00000713, 0x0080 पूर्ण, /* R1811 (0x713) - AIF1TX3MIX Input 2 Volume */
	अणु 0x00000714, 0x0000 पूर्ण, /* R1812 (0x714) - AIF1TX3MIX Input 3 Source */
	अणु 0x00000715, 0x0080 पूर्ण, /* R1813 (0x715) - AIF1TX3MIX Input 3 Volume */
	अणु 0x00000716, 0x0000 पूर्ण, /* R1814 (0x716) - AIF1TX3MIX Input 4 Source */
	अणु 0x00000717, 0x0080 पूर्ण, /* R1815 (0x717) - AIF1TX3MIX Input 4 Volume */
	अणु 0x00000718, 0x0000 पूर्ण, /* R1816 (0x718) - AIF1TX4MIX Input 1 Source */
	अणु 0x00000719, 0x0080 पूर्ण, /* R1817 (0x719) - AIF1TX4MIX Input 1 Volume */
	अणु 0x0000071a, 0x0000 पूर्ण, /* R1818 (0x71a) - AIF1TX4MIX Input 2 Source */
	अणु 0x0000071b, 0x0080 पूर्ण, /* R1819 (0x71b) - AIF1TX4MIX Input 2 Volume */
	अणु 0x0000071c, 0x0000 पूर्ण, /* R1820 (0x71c) - AIF1TX4MIX Input 3 Source */
	अणु 0x0000071d, 0x0080 पूर्ण, /* R1821 (0x71d) - AIF1TX4MIX Input 3 Volume */
	अणु 0x0000071e, 0x0000 पूर्ण, /* R1822 (0x71e) - AIF1TX4MIX Input 4 Source */
	अणु 0x0000071f, 0x0080 पूर्ण, /* R1823 (0x71f) - AIF1TX4MIX Input 4 Volume */
	अणु 0x00000720, 0x0000 पूर्ण, /* R1824 (0x720) - AIF1TX5MIX Input 1 Source */
	अणु 0x00000721, 0x0080 पूर्ण, /* R1825 (0x721) - AIF1TX5MIX Input 1 Volume */
	अणु 0x00000722, 0x0000 पूर्ण, /* R1826 (0x722) - AIF1TX5MIX Input 2 Source */
	अणु 0x00000723, 0x0080 पूर्ण, /* R1827 (0x723) - AIF1TX5MIX Input 2 Volume */
	अणु 0x00000724, 0x0000 पूर्ण, /* R1828 (0x724) - AIF1TX5MIX Input 3 Source */
	अणु 0x00000725, 0x0080 पूर्ण, /* R1829 (0x725) - AIF1TX5MIX Input 3 Volume */
	अणु 0x00000726, 0x0000 पूर्ण, /* R1830 (0x726) - AIF1TX5MIX Input 4 Source */
	अणु 0x00000727, 0x0080 पूर्ण, /* R1831 (0x727) - AIF1TX5MIX Input 4 Volume */
	अणु 0x00000728, 0x0000 पूर्ण, /* R1832 (0x728) - AIF1TX6MIX Input 1 Source */
	अणु 0x00000729, 0x0080 पूर्ण, /* R1833 (0x729) - AIF1TX6MIX Input 1 Volume */
	अणु 0x0000072a, 0x0000 पूर्ण, /* R1834 (0x72a) - AIF1TX6MIX Input 2 Source */
	अणु 0x0000072b, 0x0080 पूर्ण, /* R1835 (0x72b) - AIF1TX6MIX Input 2 Volume */
	अणु 0x0000072c, 0x0000 पूर्ण, /* R1836 (0x72c) - AIF1TX6MIX Input 3 Source */
	अणु 0x0000072d, 0x0080 पूर्ण, /* R1837 (0x72d) - AIF1TX6MIX Input 3 Volume */
	अणु 0x0000072e, 0x0000 पूर्ण, /* R1838 (0x72e) - AIF1TX6MIX Input 4 Source */
	अणु 0x0000072f, 0x0080 पूर्ण, /* R1839 (0x72f) - AIF1TX6MIX Input 4 Volume */
	अणु 0x00000740, 0x0000 पूर्ण, /* R1856 (0x740) - AIF2TX1MIX Input 1 Source */
	अणु 0x00000741, 0x0080 पूर्ण, /* R1857 (0x741) - AIF2TX1MIX Input 1 Volume */
	अणु 0x00000742, 0x0000 पूर्ण, /* R1858 (0x742) - AIF2TX1MIX Input 2 Source */
	अणु 0x00000743, 0x0080 पूर्ण, /* R1859 (0x743) - AIF2TX1MIX Input 2 Volume */
	अणु 0x00000744, 0x0000 पूर्ण, /* R1860 (0x744) - AIF2TX1MIX Input 3 Source */
	अणु 0x00000745, 0x0080 पूर्ण, /* R1861 (0x745) - AIF2TX1MIX Input 3 Volume */
	अणु 0x00000746, 0x0000 पूर्ण, /* R1862 (0x746) - AIF2TX1MIX Input 4 Source */
	अणु 0x00000747, 0x0080 पूर्ण, /* R1863 (0x747) - AIF2TX1MIX Input 4 Volume */
	अणु 0x00000748, 0x0000 पूर्ण, /* R1864 (0x748) - AIF2TX2MIX Input 1 Source */
	अणु 0x00000749, 0x0080 पूर्ण, /* R1865 (0x749) - AIF2TX2MIX Input 1 Volume */
	अणु 0x0000074a, 0x0000 पूर्ण, /* R1866 (0x74a) - AIF2TX2MIX Input 2 Source */
	अणु 0x0000074b, 0x0080 पूर्ण, /* R1867 (0x74b) - AIF2TX2MIX Input 2 Volume */
	अणु 0x0000074c, 0x0000 पूर्ण, /* R1868 (0x74c) - AIF2TX2MIX Input 3 Source */
	अणु 0x0000074d, 0x0080 पूर्ण, /* R1869 (0x74d) - AIF2TX2MIX Input 3 Volume */
	अणु 0x0000074e, 0x0000 पूर्ण, /* R1870 (0x74e) - AIF2TX2MIX Input 4 Source */
	अणु 0x0000074f, 0x0080 पूर्ण, /* R1871 (0x74f) - AIF2TX2MIX Input 4 Volume */
	अणु 0x00000780, 0x0000 पूर्ण, /* R1920 (0x780) - AIF3TX1MIX Input 1 Source */
	अणु 0x00000781, 0x0080 पूर्ण, /* R1921 (0x781) - AIF3TX1MIX Input 1 Volume */
	अणु 0x00000782, 0x0000 पूर्ण, /* R1922 (0x782) - AIF3TX1MIX Input 2 Source */
	अणु 0x00000783, 0x0080 पूर्ण, /* R1923 (0x783) - AIF3TX1MIX Input 2 Volume */
	अणु 0x00000784, 0x0000 पूर्ण, /* R1924 (0x784) - AIF3TX1MIX Input 3 Source */
	अणु 0x00000785, 0x0080 पूर्ण, /* R1925 (0x785) - AIF3TX1MIX Input 3 Volume */
	अणु 0x00000786, 0x0000 पूर्ण, /* R1926 (0x786) - AIF3TX1MIX Input 4 Source */
	अणु 0x00000787, 0x0080 पूर्ण, /* R1927 (0x787) - AIF3TX1MIX Input 4 Volume */
	अणु 0x00000788, 0x0000 पूर्ण, /* R1928 (0x788) - AIF3TX2MIX Input 1 Source */
	अणु 0x00000789, 0x0080 पूर्ण, /* R1929 (0x789) - AIF3TX2MIX Input 1 Volume */
	अणु 0x0000078a, 0x0000 पूर्ण, /* R1930 (0x78a) - AIF3TX2MIX Input 2 Source */
	अणु 0x0000078b, 0x0080 पूर्ण, /* R1931 (0x78b) - AIF3TX2MIX Input 2 Volume */
	अणु 0x0000078c, 0x0000 पूर्ण, /* R1932 (0x78c) - AIF3TX2MIX Input 3 Source */
	अणु 0x0000078d, 0x0080 पूर्ण, /* R1933 (0x78d) - AIF3TX2MIX Input 3 Volume */
	अणु 0x0000078e, 0x0000 पूर्ण, /* R1934 (0x78e) - AIF3TX2MIX Input 4 Source */
	अणु 0x0000078f, 0x0080 पूर्ण, /* R1935 (0x78f) - AIF3TX2MIX Input 4 Volume */
	अणु 0x000007c0, 0x0000 पूर्ण, /* R1984 (0x7c0) - SLIMTX1MIX Input 1 Source */
	अणु 0x000007c1, 0x0080 पूर्ण, /* R1985 (0x7c1) - SLIMTX1MIX Input 1 Volume */
	अणु 0x000007c2, 0x0000 पूर्ण, /* R1986 (0x7c2) - SLIMTX1MIX Input 2 Source */
	अणु 0x000007c3, 0x0080 पूर्ण, /* R1987 (0x7c3) - SLIMTX1MIX Input 2 Volume */
	अणु 0x000007c4, 0x0000 पूर्ण, /* R1988 (0x7c4) - SLIMTX1MIX Input 3 Source */
	अणु 0x000007c5, 0x0080 पूर्ण, /* R1989 (0x7c5) - SLIMTX1MIX Input 3 Volume */
	अणु 0x000007c6, 0x0000 पूर्ण, /* R1990 (0x7c6) - SLIMTX1MIX Input 4 Source */
	अणु 0x000007c7, 0x0080 पूर्ण, /* R1991 (0x7c7) - SLIMTX1MIX Input 4 Volume */
	अणु 0x000007c8, 0x0000 पूर्ण, /* R1992 (0x7c8) - SLIMTX2MIX Input 1 Source */
	अणु 0x000007c9, 0x0080 पूर्ण, /* R1993 (0x7c9) - SLIMTX2MIX Input 1 Volume */
	अणु 0x000007ca, 0x0000 पूर्ण, /* R1994 (0x7ca) - SLIMTX2MIX Input 2 Source */
	अणु 0x000007cb, 0x0080 पूर्ण, /* R1995 (0x7cb) - SLIMTX2MIX Input 2 Volume */
	अणु 0x000007cc, 0x0000 पूर्ण, /* R1996 (0x7cc) - SLIMTX2MIX Input 3 Source */
	अणु 0x000007cd, 0x0080 पूर्ण, /* R1997 (0x7cd) - SLIMTX2MIX Input 3 Volume */
	अणु 0x000007ce, 0x0000 पूर्ण, /* R1998 (0x7ce) - SLIMTX2MIX Input 4 Source */
	अणु 0x000007cf, 0x0080 पूर्ण, /* R1999 (0x7cf) - SLIMTX2MIX Input 4 Volume */
	अणु 0x000007d0, 0x0000 पूर्ण, /* R2000 (0x7d0) - SLIMTX3MIX Input 1 Source */
	अणु 0x000007d1, 0x0080 पूर्ण, /* R2001 (0x7d1) - SLIMTX3MIX Input 1 Volume */
	अणु 0x000007d2, 0x0000 पूर्ण, /* R2002 (0x7d2) - SLIMTX3MIX Input 2 Source */
	अणु 0x000007d3, 0x0080 पूर्ण, /* R2003 (0x7d3) - SLIMTX3MIX Input 2 Volume */
	अणु 0x000007d4, 0x0000 पूर्ण, /* R2004 (0x7d4) - SLIMTX3MIX Input 3 Source */
	अणु 0x000007d5, 0x0080 पूर्ण, /* R2005 (0x7d5) - SLIMTX3MIX Input 3 Volume */
	अणु 0x000007d6, 0x0000 पूर्ण, /* R2006 (0x7d6) - SLIMTX3MIX Input 4 Source */
	अणु 0x000007d7, 0x0080 पूर्ण, /* R2007 (0x7d7) - SLIMTX3MIX Input 4 Volume */
	अणु 0x000007d8, 0x0000 पूर्ण, /* R2008 (0x7d8) - SLIMTX4MIX Input 1 Source */
	अणु 0x000007d9, 0x0080 पूर्ण, /* R2009 (0x7d9) - SLIMTX4MIX Input 1 Volume */
	अणु 0x000007da, 0x0000 पूर्ण, /* R2010 (0x7da) - SLIMTX4MIX Input 2 Source */
	अणु 0x000007db, 0x0080 पूर्ण, /* R2011 (0x7db) - SLIMTX4MIX Input 2 Volume */
	अणु 0x000007dc, 0x0000 पूर्ण, /* R2012 (0x7dc) - SLIMTX4MIX Input 3 Source */
	अणु 0x000007dd, 0x0080 पूर्ण, /* R2013 (0x7dd) - SLIMTX4MIX Input 3 Volume */
	अणु 0x000007de, 0x0000 पूर्ण, /* R2014 (0x7de) - SLIMTX4MIX Input 4 Source */
	अणु 0x000007df, 0x0080 पूर्ण, /* R2015 (0x7df) - SLIMTX4MIX Input 4 Volume */
	अणु 0x000007e0, 0x0000 पूर्ण, /* R2016 (0x7e0) - SLIMTX5MIX Input 1 Source */
	अणु 0x000007e1, 0x0080 पूर्ण, /* R2017 (0x7e1) - SLIMTX5MIX Input 1 Volume */
	अणु 0x000007e2, 0x0000 पूर्ण, /* R2018 (0x7e2) - SLIMTX5MIX Input 2 Source */
	अणु 0x000007e3, 0x0080 पूर्ण, /* R2019 (0x7e3) - SLIMTX5MIX Input 2 Volume */
	अणु 0x000007e4, 0x0000 पूर्ण, /* R2020 (0x7e4) - SLIMTX5MIX Input 3 Source */
	अणु 0x000007e5, 0x0080 पूर्ण, /* R2021 (0x7e5) - SLIMTX5MIX Input 3 Volume */
	अणु 0x000007e6, 0x0000 पूर्ण, /* R2022 (0x7e6) - SLIMTX5MIX Input 4 Source */
	अणु 0x000007e7, 0x0080 पूर्ण, /* R2023 (0x7e7) - SLIMTX5MIX Input 4 Volume */
	अणु 0x000007e8, 0x0000 पूर्ण, /* R2024 (0x7e8) - SLIMTX6MIX Input 1 Source */
	अणु 0x000007e9, 0x0080 पूर्ण, /* R2025 (0x7e9) - SLIMTX6MIX Input 1 Volume */
	अणु 0x000007ea, 0x0000 पूर्ण, /* R2026 (0x7ea) - SLIMTX6MIX Input 2 Source */
	अणु 0x000007eb, 0x0080 पूर्ण, /* R2027 (0x7eb) - SLIMTX6MIX Input 2 Volume */
	अणु 0x000007ec, 0x0000 पूर्ण, /* R2028 (0x7ec) - SLIMTX6MIX Input 3 Source */
	अणु 0x000007ed, 0x0080 पूर्ण, /* R2029 (0x7ed) - SLIMTX6MIX Input 3 Volume */
	अणु 0x000007ee, 0x0000 पूर्ण, /* R2030 (0x7ee) - SLIMTX6MIX Input 4 Source */
	अणु 0x000007ef, 0x0080 पूर्ण, /* R2031 (0x7ef) - SLIMTX6MIX Input 4 Volume */
	अणु 0x00000800, 0x0000 पूर्ण, /* R2048 (0x800) - SPDIF1TX1MIX Input 1 Source*/
	अणु 0x00000801, 0x0080 पूर्ण, /* R2049 (0x801) - SPDIF1TX1MIX Input 1 Volume*/
	अणु 0x00000808, 0x0000 पूर्ण, /* R2056 (0x808) - SPDIF1TX2MIX Input 1 Source*/
	अणु 0x00000809, 0x0080 पूर्ण, /* R2057 (0x809) - SPDIF1TX2MIX Input 1 Volume*/
	अणु 0x00000880, 0x0000 पूर्ण, /* R2176 (0x880) - EQ1MIX Input 1 Source */
	अणु 0x00000881, 0x0080 पूर्ण, /* R2177 (0x881) - EQ1MIX Input 1 Volume */
	अणु 0x00000882, 0x0000 पूर्ण, /* R2178 (0x882) - EQ1MIX Input 2 Source */
	अणु 0x00000883, 0x0080 पूर्ण, /* R2179 (0x883) - EQ1MIX Input 2 Volume */
	अणु 0x00000884, 0x0000 पूर्ण, /* R2180 (0x884) - EQ1MIX Input 3 Source */
	अणु 0x00000885, 0x0080 पूर्ण, /* R2181 (0x885) - EQ1MIX Input 3 Volume */
	अणु 0x00000886, 0x0000 पूर्ण, /* R2182 (0x886) - EQ1MIX Input 4 Source */
	अणु 0x00000887, 0x0080 पूर्ण, /* R2183 (0x887) - EQ1MIX Input 4 Volume */
	अणु 0x00000888, 0x0000 पूर्ण, /* R2184 (0x888) - EQ2MIX Input 1 Source */
	अणु 0x00000889, 0x0080 पूर्ण, /* R2185 (0x889) - EQ2MIX Input 1 Volume */
	अणु 0x0000088a, 0x0000 पूर्ण, /* R2186 (0x88a) - EQ2MIX Input 2 Source */
	अणु 0x0000088b, 0x0080 पूर्ण, /* R2187 (0x88b) - EQ2MIX Input 2 Volume */
	अणु 0x0000088c, 0x0000 पूर्ण, /* R2188 (0x88c) - EQ2MIX Input 3 Source */
	अणु 0x0000088d, 0x0080 पूर्ण, /* R2189 (0x88d) - EQ2MIX Input 3 Volume */
	अणु 0x0000088e, 0x0000 पूर्ण, /* R2190 (0x88e) - EQ2MIX Input 4 Source */
	अणु 0x0000088f, 0x0080 पूर्ण, /* R2191 (0x88f) - EQ2MIX Input 4 Volume */
	अणु 0x00000890, 0x0000 पूर्ण, /* R2192 (0x890) - EQ3MIX Input 1 Source */
	अणु 0x00000891, 0x0080 पूर्ण, /* R2193 (0x891) - EQ3MIX Input 1 Volume */
	अणु 0x00000892, 0x0000 पूर्ण, /* R2194 (0x892) - EQ3MIX Input 2 Source */
	अणु 0x00000893, 0x0080 पूर्ण, /* R2195 (0x893) - EQ3MIX Input 2 Volume */
	अणु 0x00000894, 0x0000 पूर्ण, /* R2196 (0x894) - EQ3MIX Input 3 Source */
	अणु 0x00000895, 0x0080 पूर्ण, /* R2197 (0x895) - EQ3MIX Input 3 Volume */
	अणु 0x00000896, 0x0000 पूर्ण, /* R2198 (0x896) - EQ3MIX Input 4 Source */
	अणु 0x00000897, 0x0080 पूर्ण, /* R2199 (0x897) - EQ3MIX Input 4 Volume */
	अणु 0x00000898, 0x0000 पूर्ण, /* R2200 (0x898) - EQ4MIX Input 1 Source */
	अणु 0x00000899, 0x0080 पूर्ण, /* R2201 (0x899) - EQ4MIX Input 1 Volume */
	अणु 0x0000089a, 0x0000 पूर्ण, /* R2202 (0x89a) - EQ4MIX Input 2 Source */
	अणु 0x0000089b, 0x0080 पूर्ण, /* R2203 (0x89b) - EQ4MIX Input 2 Volume */
	अणु 0x0000089c, 0x0000 पूर्ण, /* R2204 (0x89c) - EQ4MIX Input 3 Source */
	अणु 0x0000089d, 0x0080 पूर्ण, /* R2205 (0x89d) - EQ4MIX Input 3 Volume */
	अणु 0x0000089e, 0x0000 पूर्ण, /* R2206 (0x89e) - EQ4MIX Input 4 Source */
	अणु 0x0000089f, 0x0080 पूर्ण, /* R2207 (0x89f) - EQ4MIX Input 4 Volume */
	अणु 0x000008c0, 0x0000 पूर्ण, /* R2240 (0x8c0) - DRC1LMIX Input 1 Source */
	अणु 0x000008c1, 0x0080 पूर्ण, /* R2241 (0x8c1) - DRC1LMIX Input 1 Volume */
	अणु 0x000008c2, 0x0000 पूर्ण, /* R2242 (0x8c2) - DRC1LMIX Input 2 Source */
	अणु 0x000008c3, 0x0080 पूर्ण, /* R2243 (0x8c3) - DRC1LMIX Input 2 Volume */
	अणु 0x000008c4, 0x0000 पूर्ण, /* R2244 (0x8c4) - DRC1LMIX Input 3 Source */
	अणु 0x000008c5, 0x0080 पूर्ण, /* R2245 (0x8c5) - DRC1LMIX Input 3 Volume */
	अणु 0x000008c6, 0x0000 पूर्ण, /* R2246 (0x8c6) - DRC1LMIX Input 4 Source */
	अणु 0x000008c7, 0x0080 पूर्ण, /* R2247 (0x8c7) - DRC1LMIX Input 4 Volume */
	अणु 0x000008c8, 0x0000 पूर्ण, /* R2248 (0x8c8) - DRC1RMIX Input 1 Source */
	अणु 0x000008c9, 0x0080 पूर्ण, /* R2249 (0x8c9) - DRC1RMIX Input 1 Volume */
	अणु 0x000008ca, 0x0000 पूर्ण, /* R2250 (0x8ca) - DRC1RMIX Input 2 Source */
	अणु 0x000008cb, 0x0080 पूर्ण, /* R2251 (0x8cb) - DRC1RMIX Input 2 Volume */
	अणु 0x000008cc, 0x0000 पूर्ण, /* R2252 (0x8cc) - DRC1RMIX Input 3 Source */
	अणु 0x000008cd, 0x0080 पूर्ण, /* R2253 (0x8cd) - DRC1RMIX Input 3 Volume */
	अणु 0x000008ce, 0x0000 पूर्ण, /* R2254 (0x8ce) - DRC1RMIX Input 4 Source */
	अणु 0x000008cf, 0x0080 पूर्ण, /* R2255 (0x8cf) - DRC1RMIX Input 4 Volume */
	अणु 0x000008d0, 0x0000 पूर्ण, /* R2256 (0x8d0) - DRC2LMIX Input 1 Source */
	अणु 0x000008d1, 0x0080 पूर्ण, /* R2257 (0x8d1) - DRC2LMIX Input 1 Volume */
	अणु 0x000008d2, 0x0000 पूर्ण, /* R2258 (0x8d2) - DRC2LMIX Input 2 Source */
	अणु 0x000008d3, 0x0080 पूर्ण, /* R2259 (0x8d3) - DRC2LMIX Input 2 Volume */
	अणु 0x000008d4, 0x0000 पूर्ण, /* R2260 (0x8d4) - DRC2LMIX Input 3 Source */
	अणु 0x000008d5, 0x0080 पूर्ण, /* R2261 (0x8d5) - DRC2LMIX Input 3 Volume */
	अणु 0x000008d6, 0x0000 पूर्ण, /* R2262 (0x8d6) - DRC2LMIX Input 4 Source */
	अणु 0x000008d7, 0x0080 पूर्ण, /* R2263 (0x8d7) - DRC2LMIX Input 4 Volume */
	अणु 0x000008d8, 0x0000 पूर्ण, /* R2264 (0x8d8) - DRC2RMIX Input 1 Source */
	अणु 0x000008d9, 0x0080 पूर्ण, /* R2265 (0x8d9) - DRC2RMIX Input 1 Volume */
	अणु 0x000008da, 0x0000 पूर्ण, /* R2266 (0x8da) - DRC2RMIX Input 2 Source */
	अणु 0x000008db, 0x0080 पूर्ण, /* R2267 (0x8db) - DRC2RMIX Input 2 Volume */
	अणु 0x000008dc, 0x0000 पूर्ण, /* R2268 (0x8dc) - DRC2RMIX Input 3 Source */
	अणु 0x000008dd, 0x0080 पूर्ण, /* R2269 (0x8dd) - DRC2RMIX Input 3 Volume */
	अणु 0x000008de, 0x0000 पूर्ण, /* R2270 (0x8de) - DRC2RMIX Input 4 Source */
	अणु 0x000008df, 0x0080 पूर्ण, /* R2271 (0x8df) - DRC2RMIX Input 4 Volume */
	अणु 0x00000900, 0x0000 पूर्ण, /* R2304 (0x900) - HPLP1MIX Input 1 Source */
	अणु 0x00000901, 0x0080 पूर्ण, /* R2305 (0x901) - HPLP1MIX Input 1 Volume */
	अणु 0x00000902, 0x0000 पूर्ण, /* R2306 (0x902) - HPLP1MIX Input 2 Source */
	अणु 0x00000903, 0x0080 पूर्ण, /* R2307 (0x903) - HPLP1MIX Input 2 Volume */
	अणु 0x00000904, 0x0000 पूर्ण, /* R2308 (0x904) - HPLP1MIX Input 3 Source */
	अणु 0x00000905, 0x0080 पूर्ण, /* R2309 (0x905) - HPLP1MIX Input 3 Volume */
	अणु 0x00000906, 0x0000 पूर्ण, /* R2310 (0x906) - HPLP1MIX Input 4 Source */
	अणु 0x00000907, 0x0080 पूर्ण, /* R2311 (0x907) - HPLP1MIX Input 4 Volume */
	अणु 0x00000908, 0x0000 पूर्ण, /* R2312 (0x908) - HPLP2MIX Input 1 Source */
	अणु 0x00000909, 0x0080 पूर्ण, /* R2313 (0x909) - HPLP2MIX Input 1 Volume */
	अणु 0x0000090a, 0x0000 पूर्ण, /* R2314 (0x90a) - HPLP2MIX Input 2 Source */
	अणु 0x0000090b, 0x0080 पूर्ण, /* R2315 (0x90b) - HPLP2MIX Input 2 Volume */
	अणु 0x0000090c, 0x0000 पूर्ण, /* R2316 (0x90c) - HPLP2MIX Input 3 Source */
	अणु 0x0000090d, 0x0080 पूर्ण, /* R2317 (0x90d) - HPLP2MIX Input 3 Volume */
	अणु 0x0000090e, 0x0000 पूर्ण, /* R2318 (0x90e) - HPLP2MIX Input 4 Source */
	अणु 0x0000090f, 0x0080 पूर्ण, /* R2319 (0x90f) - HPLP2MIX Input 4 Volume */
	अणु 0x00000910, 0x0000 पूर्ण, /* R2320 (0x910) - HPLP3MIX Input 1 Source */
	अणु 0x00000911, 0x0080 पूर्ण, /* R2321 (0x911) - HPLP3MIX Input 1 Volume */
	अणु 0x00000912, 0x0000 पूर्ण, /* R2322 (0x912) - HPLP3MIX Input 2 Source */
	अणु 0x00000913, 0x0080 पूर्ण, /* R2323 (0x913) - HPLP3MIX Input 2 Volume */
	अणु 0x00000914, 0x0000 पूर्ण, /* R2324 (0x914) - HPLP3MIX Input 3 Source */
	अणु 0x00000915, 0x0080 पूर्ण, /* R2325 (0x915) - HPLP3MIX Input 3 Volume */
	अणु 0x00000916, 0x0000 पूर्ण, /* R2326 (0x916) - HPLP3MIX Input 4 Source */
	अणु 0x00000917, 0x0080 पूर्ण, /* R2327 (0x917) - HPLP3MIX Input 4 Volume */
	अणु 0x00000918, 0x0000 पूर्ण, /* R2328 (0x918) - HPLP4MIX Input 1 Source */
	अणु 0x00000919, 0x0080 पूर्ण, /* R2329 (0x919) - HPLP4MIX Input 1 Volume */
	अणु 0x0000091a, 0x0000 पूर्ण, /* R2330 (0x91a) - HPLP4MIX Input 2 Source */
	अणु 0x0000091b, 0x0080 पूर्ण, /* R2331 (0x91b) - HPLP4MIX Input 2 Volume */
	अणु 0x0000091c, 0x0000 पूर्ण, /* R2332 (0x91c) - HPLP4MIX Input 3 Source */
	अणु 0x0000091d, 0x0080 पूर्ण, /* R2333 (0x91d) - HPLP4MIX Input 3 Volume */
	अणु 0x0000091e, 0x0000 पूर्ण, /* R2334 (0x91e) - HPLP4MIX Input 4 Source */
	अणु 0x0000091f, 0x0080 पूर्ण, /* R2335 (0x91f) - HPLP4MIX Input 4 Volume */
	अणु 0x00000940, 0x0000 पूर्ण, /* R2368 (0x940) - DSP1LMIX Input 1 Source */
	अणु 0x00000941, 0x0080 पूर्ण, /* R2369 (0x941) - DSP1LMIX Input 1 Volume */
	अणु 0x00000942, 0x0000 पूर्ण, /* R2370 (0x942) - DSP1LMIX Input 2 Source */
	अणु 0x00000943, 0x0080 पूर्ण, /* R2371 (0x943) - DSP1LMIX Input 2 Volume */
	अणु 0x00000944, 0x0000 पूर्ण, /* R2372 (0x944) - DSP1LMIX Input 3 Source */
	अणु 0x00000945, 0x0080 पूर्ण, /* R2373 (0x945) - DSP1LMIX Input 3 Volume */
	अणु 0x00000946, 0x0000 पूर्ण, /* R2374 (0x946) - DSP1LMIX Input 4 Source */
	अणु 0x00000947, 0x0080 पूर्ण, /* R2375 (0x947) - DSP1LMIX Input 4 Volume */
	अणु 0x00000948, 0x0000 पूर्ण, /* R2376 (0x948) - DSP1RMIX Input 1 Source */
	अणु 0x00000949, 0x0080 पूर्ण, /* R2377 (0x949) - DSP1RMIX Input 1 Volume */
	अणु 0x0000094a, 0x0000 पूर्ण, /* R2378 (0x94a) - DSP1RMIX Input 2 Source */
	अणु 0x0000094b, 0x0080 पूर्ण, /* R2379 (0x94b) - DSP1RMIX Input 2 Volume */
	अणु 0x0000094c, 0x0000 पूर्ण, /* R2380 (0x94c) - DSP1RMIX Input 3 Source */
	अणु 0x0000094d, 0x0080 पूर्ण, /* R2381 (0x94d) - DSP1RMIX Input 3 Volume */
	अणु 0x0000094e, 0x0000 पूर्ण, /* R2382 (0x94e) - DSP1RMIX Input 4 Source */
	अणु 0x0000094f, 0x0080 पूर्ण, /* R2383 (0x94f) - DSP1RMIX Input 4 Volume */
	अणु 0x00000950, 0x0000 पूर्ण, /* R2384 (0x950) - DSP1AUX1MIX Input 1 Source */
	अणु 0x00000958, 0x0000 पूर्ण, /* R2392 (0x958) - DSP1AUX2MIX Input 1 Source */
	अणु 0x00000960, 0x0000 पूर्ण, /* R2400 (0x960) - DSP1AUX3MIX Input 1 Source */
	अणु 0x00000968, 0x0000 पूर्ण, /* R2408 (0x968) - DSP1AUX4MIX Input 1 Source */
	अणु 0x00000970, 0x0000 पूर्ण, /* R2416 (0x970) - DSP1AUX5MIX Input 1 Source */
	अणु 0x00000978, 0x0000 पूर्ण, /* R2424 (0x978) - DSP1AUX6MIX Input 1 Source */
	अणु 0x00000980, 0x0000 पूर्ण, /* R2432 (0x980) - DSP2LMIX Input 1 Source */
	अणु 0x00000981, 0x0080 पूर्ण, /* R2433 (0x981) - DSP2LMIX Input 1 Volume */
	अणु 0x00000982, 0x0000 पूर्ण, /* R2434 (0x982) - DSP2LMIX Input 2 Source */
	अणु 0x00000983, 0x0080 पूर्ण, /* R2435 (0x983) - DSP2LMIX Input 2 Volume */
	अणु 0x00000984, 0x0000 पूर्ण, /* R2436 (0x984) - DSP2LMIX Input 3 Source */
	अणु 0x00000985, 0x0080 पूर्ण, /* R2437 (0x985) - DSP2LMIX Input 3 Volume */
	अणु 0x00000986, 0x0000 पूर्ण, /* R2438 (0x986) - DSP2LMIX Input 4 Source */
	अणु 0x00000987, 0x0080 पूर्ण, /* R2439 (0x987) - DSP2LMIX Input 4 Volume */
	अणु 0x00000988, 0x0000 पूर्ण, /* R2440 (0x988) - DSP2RMIX Input 1 Source */
	अणु 0x00000989, 0x0080 पूर्ण, /* R2441 (0x989) - DSP2RMIX Input 1 Volume */
	अणु 0x0000098a, 0x0000 पूर्ण, /* R2442 (0x98a) - DSP2RMIX Input 2 Source */
	अणु 0x0000098b, 0x0080 पूर्ण, /* R2443 (0x98b) - DSP2RMIX Input 2 Volume */
	अणु 0x0000098c, 0x0000 पूर्ण, /* R2444 (0x98c) - DSP2RMIX Input 3 Source */
	अणु 0x0000098d, 0x0080 पूर्ण, /* R2445 (0x98d) - DSP2RMIX Input 3 Volume */
	अणु 0x0000098e, 0x0000 पूर्ण, /* R2446 (0x98e) - DSP2RMIX Input 4 Source */
	अणु 0x0000098f, 0x0080 पूर्ण, /* R2447 (0x98f) - DSP2RMIX Input 4 Volume */
	अणु 0x00000990, 0x0000 पूर्ण, /* R2448 (0x990) - DSP2AUX1MIX Input 1 Source */
	अणु 0x00000998, 0x0000 पूर्ण, /* R2456 (0x998) - DSP2AUX2MIX Input 1 Source */
	अणु 0x000009a0, 0x0000 पूर्ण, /* R2464 (0x9a0) - DSP2AUX3MIX Input 1 Source */
	अणु 0x000009a8, 0x0000 पूर्ण, /* R2472 (0x9a8) - DSP2AUX4MIX Input 1 Source */
	अणु 0x000009b0, 0x0000 पूर्ण, /* R2480 (0x9b0) - DSP2AUX5MIX Input 1 Source */
	अणु 0x000009b8, 0x0000 पूर्ण, /* R2488 (0x9b8) - DSP2AUX6MIX Input 1 Source */
	अणु 0x000009c0, 0x0000 पूर्ण, /* R2496 (0x9c0) - DSP3LMIX Input 1 Source */
	अणु 0x000009c1, 0x0080 पूर्ण, /* R2497 (0x9c1) - DSP3LMIX Input 1 Volume */
	अणु 0x000009c2, 0x0000 पूर्ण, /* R2498 (0x9c2) - DSP3LMIX Input 2 Source */
	अणु 0x000009c3, 0x0080 पूर्ण, /* R2499 (0x9c3) - DSP3LMIX Input 2 Volume */
	अणु 0x000009c4, 0x0000 पूर्ण, /* R2500 (0x9c4) - DSP3LMIX Input 3 Source */
	अणु 0x000009c5, 0x0080 पूर्ण, /* R2501 (0x9c5) - DSP3LMIX Input 3 Volume */
	अणु 0x000009c6, 0x0000 पूर्ण, /* R2502 (0x9c6) - DSP3LMIX Input 4 Source */
	अणु 0x000009c7, 0x0080 पूर्ण, /* R2503 (0x9c7) - DSP3LMIX Input 4 Volume */
	अणु 0x000009c8, 0x0000 पूर्ण, /* R2504 (0x9c8) - DSP3RMIX Input 1 Source */
	अणु 0x000009c9, 0x0080 पूर्ण, /* R2505 (0x9c9) - DSP3RMIX Input 1 Volume */
	अणु 0x000009ca, 0x0000 पूर्ण, /* R2506 (0x9ca) - DSP3RMIX Input 2 Source */
	अणु 0x000009cb, 0x0080 पूर्ण, /* R2507 (0x9cb) - DSP3RMIX Input 2 Volume */
	अणु 0x000009cc, 0x0000 पूर्ण, /* R2508 (0x9cc) - DSP3RMIX Input 3 Source */
	अणु 0x000009cd, 0x0080 पूर्ण, /* R2509 (0x9cd) - DSP3RMIX Input 3 Volume */
	अणु 0x000009ce, 0x0000 पूर्ण, /* R2510 (0x9ce) - DSP3RMIX Input 4 Source */
	अणु 0x000009cf, 0x0080 पूर्ण, /* R2511 (0x9cf) - DSP3RMIX Input 4 Volume */
	अणु 0x000009d0, 0x0000 पूर्ण, /* R2512 (0x9d0) - DSP3AUX1MIX Input 1 Source */
	अणु 0x000009d8, 0x0000 पूर्ण, /* R2520 (0x9d8) - DSP3AUX2MIX Input 1 Source */
	अणु 0x000009e0, 0x0000 पूर्ण, /* R2528 (0x9e0) - DSP3AUX3MIX Input 1 Source */
	अणु 0x000009e8, 0x0000 पूर्ण, /* R2536 (0x9e8) - DSP3AUX4MIX Input 1 Source */
	अणु 0x000009f0, 0x0000 पूर्ण, /* R2544 (0x9f0) - DSP3AUX5MIX Input 1 Source */
	अणु 0x000009f8, 0x0000 पूर्ण, /* R2552 (0x9f8) - DSP3AUX6MIX Input 1 Source */
	अणु 0x00000b00, 0x0000 पूर्ण, /* R2816 (0xb00) - ISRC1DEC1MIX Input 1 Source*/
	अणु 0x00000b08, 0x0000 पूर्ण, /* R2824 (0xb08) - ISRC1DEC2MIX Input 1 Source*/
	अणु 0x00000b10, 0x0000 पूर्ण, /* R2832 (0xb10) - ISRC1DEC3MIX Input 1 Source*/
	अणु 0x00000b18, 0x0000 पूर्ण, /* R2840 (0xb18) - ISRC1DEC4MIX Input 1 Source*/
	अणु 0x00000b20, 0x0000 पूर्ण, /* R2848 (0xb20) - ISRC1INT1MIX Input 1 Source*/
	अणु 0x00000b28, 0x0000 पूर्ण, /* R2856 (0xb28) - ISRC1INT2MIX Input 1 Source*/
	अणु 0x00000b30, 0x0000 पूर्ण, /* R2864 (0xb30) - ISRC1INT3MIX Input 1 Source*/
	अणु 0x00000b38, 0x0000 पूर्ण, /* R2872 (0xb38) - ISRC1INT4MIX Input 1 Source*/
	अणु 0x00000b40, 0x0000 पूर्ण, /* R2880 (0xb40) - ISRC2DEC1MIX Input 1 Source*/
	अणु 0x00000b48, 0x0000 पूर्ण, /* R2888 (0xb48) - ISRC2DEC2MIX Input 1 Source*/
	अणु 0x00000b50, 0x0000 पूर्ण, /* R2896 (0xb50) - ISRC2DEC3MIX Input 1 Source*/
	अणु 0x00000b58, 0x0000 पूर्ण, /* R2904 (0xb58) - ISRC2DEC4MIX Input 1 Source*/
	अणु 0x00000b60, 0x0000 पूर्ण, /* R2912 (0xb60) - ISRC2INT1MIX Input 1 Source*/
	अणु 0x00000b68, 0x0000 पूर्ण, /* R2920 (0xb68) - ISRC2INT2MIX Input 1 Source*/
	अणु 0x00000b70, 0x0000 पूर्ण, /* R2928 (0xb70) - ISRC2INT3MIX Input 1 Source*/
	अणु 0x00000b78, 0x0000 पूर्ण, /* R2936 (0xb78) - ISRC2INT4MIX Input 1 Source*/
	अणु 0x00000e00, 0x0000 पूर्ण, /* R3584 (0xe00) - FX Ctrl1 */
	अणु 0x00000e10, 0x6318 पूर्ण, /* R3600 (0xe10) - EQ1_1 */
	अणु 0x00000e11, 0x6300 पूर्ण, /* R3601 (0xe11) - EQ1_2 */
	अणु 0x00000e12, 0x0fc8 पूर्ण, /* R3602 (0xe12) - EQ1_3 */
	अणु 0x00000e13, 0x03fe पूर्ण, /* R3603 (0xe13) - EQ1_4 */
	अणु 0x00000e14, 0x00e0 पूर्ण, /* R3604 (0xe14) - EQ1_5 */
	अणु 0x00000e15, 0x1ec4 पूर्ण, /* R3605 (0xe15) - EQ1_6 */
	अणु 0x00000e16, 0xf136 पूर्ण, /* R3606 (0xe16) - EQ1_7 */
	अणु 0x00000e17, 0x0409 पूर्ण, /* R3607 (0xe17) - EQ1_8 */
	अणु 0x00000e18, 0x04cc पूर्ण, /* R3608 (0xe18) - EQ1_9 */
	अणु 0x00000e19, 0x1c9b पूर्ण, /* R3609 (0xe19) - EQ1_10 */
	अणु 0x00000e1a, 0xf337 पूर्ण, /* R3610 (0xe1a) - EQ1_11 */
	अणु 0x00000e1b, 0x040b पूर्ण, /* R3611 (0xe1b) - EQ1_12 */
	अणु 0x00000e1c, 0x0cbb पूर्ण, /* R3612 (0xe1c) - EQ1_13 */
	अणु 0x00000e1d, 0x16f8 पूर्ण, /* R3613 (0xe1d) - EQ1_14 */
	अणु 0x00000e1e, 0xf7d9 पूर्ण, /* R3614 (0xe1e) - EQ1_15 */
	अणु 0x00000e1f, 0x040a पूर्ण, /* R3615 (0xe1f) - EQ1_16 */
	अणु 0x00000e20, 0x1f14 पूर्ण, /* R3616 (0xe20) - EQ1_17 */
	अणु 0x00000e21, 0x058c पूर्ण, /* R3617 (0xe21) - EQ1_18 */
	अणु 0x00000e22, 0x0563 पूर्ण, /* R3618 (0xe22) - EQ1_19 */
	अणु 0x00000e23, 0x4000 पूर्ण, /* R3619 (0xe23) - EQ1_20 */
	अणु 0x00000e24, 0x0b75 पूर्ण, /* R3620 (0xe24) - EQ1_21 */
	अणु 0x00000e26, 0x6318 पूर्ण, /* R3622 (0xe26) - EQ2_1 */
	अणु 0x00000e27, 0x6300 पूर्ण, /* R3623 (0xe27) - EQ2_2 */
	अणु 0x00000e28, 0x0fc8 पूर्ण, /* R3624 (0xe28) - EQ2_3 */
	अणु 0x00000e29, 0x03fe पूर्ण, /* R3625 (0xe29) - EQ2_4 */
	अणु 0x00000e2a, 0x00e0 पूर्ण, /* R3626 (0xe2a) - EQ2_5 */
	अणु 0x00000e2b, 0x1ec4 पूर्ण, /* R3627 (0xe2b) - EQ2_6 */
	अणु 0x00000e2c, 0xf136 पूर्ण, /* R3628 (0xe2c) - EQ2_7 */
	अणु 0x00000e2d, 0x0409 पूर्ण, /* R3629 (0xe2d) - EQ2_8 */
	अणु 0x00000e2e, 0x04cc पूर्ण, /* R3630 (0xe2e) - EQ2_9 */
	अणु 0x00000e2f, 0x1c9b पूर्ण, /* R3631 (0xe2f) - EQ2_10 */
	अणु 0x00000e30, 0xf337 पूर्ण, /* R3632 (0xe30) - EQ2_11 */
	अणु 0x00000e31, 0x040b पूर्ण, /* R3633 (0xe31) - EQ2_12 */
	अणु 0x00000e32, 0x0cbb पूर्ण, /* R3634 (0xe32) - EQ2_13 */
	अणु 0x00000e33, 0x16f8 पूर्ण, /* R3635 (0xe33) - EQ2_14 */
	अणु 0x00000e34, 0xf7d9 पूर्ण, /* R3636 (0xe34) - EQ2_15 */
	अणु 0x00000e35, 0x040a पूर्ण, /* R3637 (0xe35) - EQ2_16 */
	अणु 0x00000e36, 0x1f14 पूर्ण, /* R3638 (0xe36) - EQ2_17 */
	अणु 0x00000e37, 0x058c पूर्ण, /* R3639 (0xe37) - EQ2_18 */
	अणु 0x00000e38, 0x0563 पूर्ण, /* R3640 (0xe38) - EQ2_19 */
	अणु 0x00000e39, 0x4000 पूर्ण, /* R3641 (0xe39) - EQ2_20 */
	अणु 0x00000e3a, 0x0b75 पूर्ण, /* R3642 (0xe3a) - EQ2_21 */
	अणु 0x00000e3c, 0x6318 पूर्ण, /* R3644 (0xe3c) - EQ3_1 */
	अणु 0x00000e3d, 0x6300 पूर्ण, /* R3645 (0xe3d) - EQ3_2 */
	अणु 0x00000e3e, 0x0fc8 पूर्ण, /* R3646 (0xe3e) - EQ3_3 */
	अणु 0x00000e3f, 0x03fe पूर्ण, /* R3647 (0xe3f) - EQ3_4 */
	अणु 0x00000e40, 0x00e0 पूर्ण, /* R3648 (0xe40) - EQ3_5 */
	अणु 0x00000e41, 0x1ec4 पूर्ण, /* R3649 (0xe41) - EQ3_6 */
	अणु 0x00000e42, 0xf136 पूर्ण, /* R3650 (0xe42) - EQ3_7 */
	अणु 0x00000e43, 0x0409 पूर्ण, /* R3651 (0xe43) - EQ3_8 */
	अणु 0x00000e44, 0x04cc पूर्ण, /* R3652 (0xe44) - EQ3_9 */
	अणु 0x00000e45, 0x1c9b पूर्ण, /* R3653 (0xe45) - EQ3_10 */
	अणु 0x00000e46, 0xf337 पूर्ण, /* R3654 (0xe46) - EQ3_11 */
	अणु 0x00000e47, 0x040b पूर्ण, /* R3655 (0xe47) - EQ3_12 */
	अणु 0x00000e48, 0x0cbb पूर्ण, /* R3656 (0xe48) - EQ3_13 */
	अणु 0x00000e49, 0x16f8 पूर्ण, /* R3657 (0xe49) - EQ3_14 */
	अणु 0x00000e4a, 0xf7d9 पूर्ण, /* R3658 (0xe4a) - EQ3_15 */
	अणु 0x00000e4b, 0x040a पूर्ण, /* R3659 (0xe4b) - EQ3_16 */
	अणु 0x00000e4c, 0x1f14 पूर्ण, /* R3660 (0xe4c) - EQ3_17 */
	अणु 0x00000e4d, 0x058c पूर्ण, /* R3661 (0xe4d) - EQ3_18 */
	अणु 0x00000e4e, 0x0563 पूर्ण, /* R3662 (0xe4e) - EQ3_19 */
	अणु 0x00000e4f, 0x4000 पूर्ण, /* R3663 (0xe4f) - EQ3_20 */
	अणु 0x00000e50, 0x0b75 पूर्ण, /* R3664 (0xe50) - EQ3_21 */
	अणु 0x00000e52, 0x6318 पूर्ण, /* R3666 (0xe52) - EQ4_1 */
	अणु 0x00000e53, 0x6300 पूर्ण, /* R3667 (0xe53) - EQ4_2 */
	अणु 0x00000e54, 0x0fc8 पूर्ण, /* R3668 (0xe54) - EQ4_3 */
	अणु 0x00000e55, 0x03fe पूर्ण, /* R3669 (0xe55) - EQ4_4 */
	अणु 0x00000e56, 0x00e0 पूर्ण, /* R3670 (0xe56) - EQ4_5 */
	अणु 0x00000e57, 0x1ec4 पूर्ण, /* R3671 (0xe57) - EQ4_6 */
	अणु 0x00000e58, 0xf136 पूर्ण, /* R3672 (0xe58) - EQ4_7 */
	अणु 0x00000e59, 0x0409 पूर्ण, /* R3673 (0xe59) - EQ4_8 */
	अणु 0x00000e5a, 0x04cc पूर्ण, /* R3674 (0xe5a) - EQ4_9 */
	अणु 0x00000e5b, 0x1c9b पूर्ण, /* R3675 (0xe5b) - EQ4_10 */
	अणु 0x00000e5c, 0xf337 पूर्ण, /* R3676 (0xe5c) - EQ4_11 */
	अणु 0x00000e5d, 0x040b पूर्ण, /* R3677 (0xe5d) - EQ4_12 */
	अणु 0x00000e5e, 0x0cbb पूर्ण, /* R3678 (0xe5e) - EQ4_13 */
	अणु 0x00000e5f, 0x16f8 पूर्ण, /* R3679 (0xe5f) - EQ4_14 */
	अणु 0x00000e60, 0xf7d9 पूर्ण, /* R3680 (0xe60) - EQ4_15 */
	अणु 0x00000e61, 0x040a पूर्ण, /* R3681 (0xe61) - EQ4_16 */
	अणु 0x00000e62, 0x1f14 पूर्ण, /* R3682 (0xe62) - EQ4_17 */
	अणु 0x00000e63, 0x058c पूर्ण, /* R3683 (0xe63) - EQ4_18 */
	अणु 0x00000e64, 0x0563 पूर्ण, /* R3684 (0xe64) - EQ4_19 */
	अणु 0x00000e65, 0x4000 पूर्ण, /* R3685 (0xe65) - EQ4_20 */
	अणु 0x00000e66, 0x0b75 पूर्ण, /* R3686 (0xe66) - EQ4_21 */
	अणु 0x00000e80, 0x0018 पूर्ण, /* R3712 (0xe80) - DRC1 ctrl1 */
	अणु 0x00000e81, 0x0933 पूर्ण, /* R3713 (0xe81) - DRC1 ctrl2 */
	अणु 0x00000e82, 0x0018 पूर्ण, /* R3714 (0xe82) - DRC1 ctrl3 */
	अणु 0x00000e83, 0x0000 पूर्ण, /* R3715 (0xe83) - DRC1 ctrl4 */
	अणु 0x00000e84, 0x0000 पूर्ण, /* R3716 (0xe84) - DRC1 ctrl5 */
	अणु 0x00000e88, 0x0018 पूर्ण, /* R3720 (0xe88) - DRC2 ctrl1 */
	अणु 0x00000e89, 0x0933 पूर्ण, /* R3721 (0xe89) - DRC2 ctrl2 */
	अणु 0x00000e8a, 0x0018 पूर्ण, /* R3722 (0xe8a) - DRC2 ctrl3 */
	अणु 0x00000e8b, 0x0000 पूर्ण, /* R3723 (0xe8b) - DRC2 ctrl4 */
	अणु 0x00000e8c, 0x0000 पूर्ण, /* R3724 (0xe8c) - DRC2 ctrl5 */
	अणु 0x00000ec0, 0x0000 पूर्ण, /* R3776 (0xec0) - HPLPF1_1 */
	अणु 0x00000ec1, 0x0000 पूर्ण, /* R3777 (0xec1) - HPLPF1_2 */
	अणु 0x00000ec4, 0x0000 पूर्ण, /* R3780 (0xec4) - HPLPF2_1 */
	अणु 0x00000ec5, 0x0000 पूर्ण, /* R3781 (0xec5) - HPLPF2_2 */
	अणु 0x00000ec8, 0x0000 पूर्ण, /* R3784 (0xec8) - HPLPF3_1 */
	अणु 0x00000ec9, 0x0000 पूर्ण, /* R3785 (0xec9) - HPLPF3_2 */
	अणु 0x00000ecc, 0x0000 पूर्ण, /* R3788 (0xecc) - HPLPF4_1 */
	अणु 0x00000ecd, 0x0000 पूर्ण, /* R3789 (0xecd) - HPLPF4_2 */
	अणु 0x00000ef0, 0x0000 पूर्ण, /* R3824 (0xef0) - ISRC 1 CTRL 1 */
	अणु 0x00000ef1, 0x0001 पूर्ण, /* R3825 (0xef1) - ISRC 1 CTRL 2 */
	अणु 0x00000ef2, 0x0000 पूर्ण, /* R3826 (0xef2) - ISRC 1 CTRL 3 */
	अणु 0x00000ef3, 0x0000 पूर्ण, /* R3827 (0xef3) - ISRC 2 CTRL 1 */
	अणु 0x00000ef4, 0x0001 पूर्ण, /* R3828 (0xef4) - ISRC 2 CTRL 2 */
	अणु 0x00000ef5, 0x0000 पूर्ण, /* R3829 (0xef5) - ISRC 2 CTRL 3 */
	अणु 0x00001700, 0x2001 पूर्ण, /* R5888 (0x1700) - GPIO1 Control 1 */
	अणु 0x00001701, 0xf000 पूर्ण, /* R5889 (0x1701) - GPIO1 Control 2 */
	अणु 0x00001702, 0x2001 पूर्ण, /* R5890 (0x1702) - GPIO2 Control 1 */
	अणु 0x00001703, 0xf000 पूर्ण, /* R5891 (0x1703) - GPIO2 Control 2 */
	अणु 0x00001704, 0x2001 पूर्ण, /* R5892 (0x1704) - GPIO3 Control 1 */
	अणु 0x00001705, 0xf000 पूर्ण, /* R5893 (0x1705) - GPIO3 Control 2 */
	अणु 0x00001706, 0x2001 पूर्ण, /* R5894 (0x1706) - GPIO4 Control 1 */
	अणु 0x00001707, 0xf000 पूर्ण, /* R5895 (0x1707) - GPIO4 Control 2 */
	अणु 0x00001708, 0x2001 पूर्ण, /* R5896 (0x1708) - GPIO5 Control 1 */
	अणु 0x00001709, 0xf000 पूर्ण, /* R5897 (0x1709) - GPIO5 Control 2 */
	अणु 0x0000170a, 0x2001 पूर्ण, /* R5898 (0x170a) - GPIO6 Control 1 */
	अणु 0x0000170b, 0xf000 पूर्ण, /* R5899 (0x170b) - GPIO6 Control 2 */
	अणु 0x0000170c, 0x2001 पूर्ण, /* R5900 (0x170c) - GPIO7 Control 1 */
	अणु 0x0000170d, 0xf000 पूर्ण, /* R5901 (0x170d) - GPIO7 Control 2 */
	अणु 0x0000170e, 0x2001 पूर्ण, /* R5902 (0x170e) - GPIO8 Control 1 */
	अणु 0x0000170f, 0xf000 पूर्ण, /* R5903 (0x170f) - GPIO8 Control 2 */
	अणु 0x00001710, 0x2001 पूर्ण, /* R5904 (0x1710) - GPIO9 Control 1 */
	अणु 0x00001711, 0xf000 पूर्ण, /* R5905 (0x1711) - GPIO9 Control 2 */
	अणु 0x00001712, 0x2001 पूर्ण, /* R5906 (0x1712) - GPIO10 Control 1 */
	अणु 0x00001713, 0xf000 पूर्ण, /* R5907 (0x1713) - GPIO10 Control 2 */
	अणु 0x00001714, 0x2001 पूर्ण, /* R5908 (0x1714) - GPIO11 Control 1 */
	अणु 0x00001715, 0xf000 पूर्ण, /* R5909 (0x1715) - GPIO11 Control 2 */
	अणु 0x00001716, 0x2001 पूर्ण, /* R5910 (0x1716) - GPIO12 Control 1 */
	अणु 0x00001717, 0xf000 पूर्ण, /* R5911 (0x1717) - GPIO12 Control 2 */
	अणु 0x00001718, 0x2001 पूर्ण, /* R5912 (0x1718) - GPIO13 Control 1 */
	अणु 0x00001719, 0xf000 पूर्ण, /* R5913 (0x1719) - GPIO13 Control 2 */
	अणु 0x0000171a, 0x2001 पूर्ण, /* R5914 (0x171a) - GPIO14 Control 1 */
	अणु 0x0000171b, 0xf000 पूर्ण, /* R5915 (0x171b) - GPIO14 Control 2 */
	अणु 0x0000171c, 0x2001 पूर्ण, /* R5916 (0x171c) - GPIO15 Control 1 */
	अणु 0x0000171d, 0xf000 पूर्ण, /* R5917 (0x171d) - GPIO15 Control 2 */
	अणु 0x0000171e, 0x2001 पूर्ण, /* R5918 (0x171e) - GPIO16 Control 1 */
	अणु 0x0000171f, 0xf000 पूर्ण, /* R5919 (0x171f) - GPIO16 Control 2 */
	अणु 0x00001840, 0xffff पूर्ण, /* R6208 (0x1840) - IRQ1 Mask 1 */
	अणु 0x00001841, 0xffff पूर्ण, /* R6209 (0x1841) - IRQ1 Mask 2 */
	अणु 0x00001842, 0xffff पूर्ण, /* R6210 (0x1842) - IRQ1 Mask 3 */
	अणु 0x00001843, 0xffff पूर्ण, /* R6211 (0x1843) - IRQ1 Mask 4 */
	अणु 0x00001844, 0xffff पूर्ण, /* R6212 (0x1844) - IRQ1 Mask 5 */
	अणु 0x00001845, 0xffff पूर्ण, /* R6213 (0x1845) - IRQ1 Mask 6 */
	अणु 0x00001846, 0xffff पूर्ण, /* R6214 (0x1846) - IRQ1 Mask 7 */
	अणु 0x00001847, 0xffff पूर्ण, /* R6215 (0x1847) - IRQ1 Mask 8 */
	अणु 0x00001848, 0xffff पूर्ण, /* R6216 (0x1848) - IRQ1 Mask 9 */
	अणु 0x00001849, 0xffff पूर्ण, /* R6217 (0x1849) - IRQ1 Mask 10 */
	अणु 0x0000184a, 0xffff पूर्ण, /* R6218 (0x184a) - IRQ1 Mask 11 */
	अणु 0x0000184b, 0xffff पूर्ण, /* R6219 (0x184b) - IRQ1 Mask 12 */
	अणु 0x0000184c, 0xffff पूर्ण, /* R6220 (0x184c) - IRQ1 Mask 13 */
	अणु 0x0000184d, 0xffff पूर्ण, /* R6221 (0x184d) - IRQ1 Mask 14 */
	अणु 0x0000184e, 0xffff पूर्ण, /* R6222 (0x184e) - IRQ1 Mask 15 */
	अणु 0x0000184f, 0xffff पूर्ण, /* R6223 (0x184f) - IRQ1 Mask 16 */
	अणु 0x00001850, 0xffff पूर्ण, /* R6224 (0x1850) - IRQ1 Mask 17 */
	अणु 0x00001851, 0xffff पूर्ण, /* R6225 (0x1851) - IRQ1 Mask 18 */
	अणु 0x00001852, 0xffff पूर्ण, /* R6226 (0x1852) - IRQ1 Mask 19 */
	अणु 0x00001853, 0xffff पूर्ण, /* R6227 (0x1853) - IRQ1 Mask 20 */
	अणु 0x00001854, 0xffff पूर्ण, /* R6228 (0x1854) - IRQ1 Mask 21 */
	अणु 0x00001855, 0xffff पूर्ण, /* R6229 (0x1855) - IRQ1 Mask 22 */
	अणु 0x00001856, 0xffff पूर्ण, /* R6230 (0x1856) - IRQ1 Mask 23 */
	अणु 0x00001857, 0xffff पूर्ण, /* R6231 (0x1857) - IRQ1 Mask 24 */
	अणु 0x00001858, 0xffff पूर्ण, /* R6232 (0x1858) - IRQ1 Mask 25 */
	अणु 0x00001859, 0xffff पूर्ण, /* R6233 (0x1859) - IRQ1 Mask 26 */
	अणु 0x0000185a, 0xffff पूर्ण, /* R6234 (0x185a) - IRQ1 Mask 27 */
	अणु 0x0000185b, 0xffff पूर्ण, /* R6235 (0x185b) - IRQ1 Mask 28 */
	अणु 0x0000185c, 0xffff पूर्ण, /* R6236 (0x185c) - IRQ1 Mask 29 */
	अणु 0x0000185d, 0xffff पूर्ण, /* R6237 (0x185d) - IRQ1 Mask 30 */
	अणु 0x0000185e, 0xffff पूर्ण, /* R6238 (0x185e) - IRQ1 Mask 31 */
	अणु 0x0000185f, 0xffff पूर्ण, /* R6239 (0x185f) - IRQ1 Mask 32 */
	अणु 0x00001860, 0xffff पूर्ण, /* R6240 (0x1860) - IRQ1 Mask 33 */
	अणु 0x00001a06, 0x0000 पूर्ण, /* R6662 (0x1a06) - Interrupt Debounce 7 */
	अणु 0x00001a80, 0x4400 पूर्ण, /* R6784 (0x1a80) - IRQ1 CTRL */
पूर्ण;

अटल bool cs47l35_is_adsp_memory(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x080000 ... 0x085ffe:
	हाल 0x0a0000 ... 0x0a7ffe:
	हाल 0x0c0000 ... 0x0c1ffe:
	हाल 0x0e0000 ... 0x0e1ffe:
	हाल 0x100000 ... 0x10effe:
	हाल 0x120000 ... 0x12bffe:
	हाल 0x136000 ... 0x137ffe:
	हाल 0x140000 ... 0x14bffe:
	हाल 0x160000 ... 0x161ffe:
	हाल 0x180000 ... 0x18effe:
	हाल 0x1a0000 ... 0x1b1ffe:
	हाल 0x1b6000 ... 0x1b7ffe:
	हाल 0x1c0000 ... 0x1cbffe:
	हाल 0x1e0000 ... 0x1e1ffe:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs47l35_16bit_पढ़ोable_रेजिस्टर(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MADERA_SOFTWARE_RESET:
	हाल MADERA_HARDWARE_REVISION:
	हाल MADERA_WRITE_SEQUENCER_CTRL_0:
	हाल MADERA_WRITE_SEQUENCER_CTRL_1:
	हाल MADERA_WRITE_SEQUENCER_CTRL_2:
	हाल MADERA_TONE_GENERATOR_1:
	हाल MADERA_TONE_GENERATOR_2:
	हाल MADERA_TONE_GENERATOR_3:
	हाल MADERA_TONE_GENERATOR_4:
	हाल MADERA_TONE_GENERATOR_5:
	हाल MADERA_PWM_DRIVE_1:
	हाल MADERA_PWM_DRIVE_2:
	हाल MADERA_PWM_DRIVE_3:
	हाल MADERA_SAMPLE_RATE_SEQUENCE_SELECT_1:
	हाल MADERA_SAMPLE_RATE_SEQUENCE_SELECT_2:
	हाल MADERA_SAMPLE_RATE_SEQUENCE_SELECT_3:
	हाल MADERA_SAMPLE_RATE_SEQUENCE_SELECT_4:
	हाल MADERA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_1:
	हाल MADERA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_2:
	हाल MADERA_HAPTICS_CONTROL_1:
	हाल MADERA_HAPTICS_CONTROL_2:
	हाल MADERA_HAPTICS_PHASE_1_INTENSITY:
	हाल MADERA_HAPTICS_PHASE_1_DURATION:
	हाल MADERA_HAPTICS_PHASE_2_INTENSITY:
	हाल MADERA_HAPTICS_PHASE_2_DURATION:
	हाल MADERA_HAPTICS_PHASE_3_INTENSITY:
	हाल MADERA_HAPTICS_PHASE_3_DURATION:
	हाल MADERA_HAPTICS_STATUS:
	हाल MADERA_COMFORT_NOISE_GENERATOR:
	हाल MADERA_CLOCK_32K_1:
	हाल MADERA_SYSTEM_CLOCK_1:
	हाल MADERA_SAMPLE_RATE_1:
	हाल MADERA_SAMPLE_RATE_2:
	हाल MADERA_SAMPLE_RATE_3:
	हाल MADERA_SAMPLE_RATE_1_STATUS:
	हाल MADERA_SAMPLE_RATE_2_STATUS:
	हाल MADERA_SAMPLE_RATE_3_STATUS:
	हाल MADERA_DSP_CLOCK_1:
	हाल MADERA_DSP_CLOCK_2:
	हाल MADERA_OUTPUT_SYSTEM_CLOCK:
	हाल MADERA_OUTPUT_ASYNC_CLOCK:
	हाल MADERA_RATE_ESTIMATOR_1:
	हाल MADERA_RATE_ESTIMATOR_2:
	हाल MADERA_RATE_ESTIMATOR_3:
	हाल MADERA_RATE_ESTIMATOR_4:
	हाल MADERA_RATE_ESTIMATOR_5:
	हाल MADERA_FLL1_CONTROL_1:
	हाल MADERA_FLL1_CONTROL_2:
	हाल MADERA_FLL1_CONTROL_3:
	हाल MADERA_FLL1_CONTROL_4:
	हाल MADERA_FLL1_CONTROL_5:
	हाल MADERA_FLL1_CONTROL_6:
	हाल MADERA_FLL1_CONTROL_7:
	हाल MADERA_FLL1_EFS_2:
	हाल CS47L35_FLL1_SYNCHRONISER_1:
	हाल CS47L35_FLL1_SYNCHRONISER_2:
	हाल CS47L35_FLL1_SYNCHRONISER_3:
	हाल CS47L35_FLL1_SYNCHRONISER_4:
	हाल CS47L35_FLL1_SYNCHRONISER_5:
	हाल CS47L35_FLL1_SYNCHRONISER_6:
	हाल CS47L35_FLL1_SYNCHRONISER_7:
	हाल CS47L35_FLL1_SPREAD_SPECTRUM:
	हाल CS47L35_FLL1_GPIO_CLOCK:
	हाल MADERA_MIC_CHARGE_PUMP_1:
	हाल MADERA_HP_CHARGE_PUMP_8:
	हाल MADERA_LDO2_CONTROL_1:
	हाल MADERA_MIC_BIAS_CTRL_1:
	हाल MADERA_MIC_BIAS_CTRL_2:
	हाल MADERA_MIC_BIAS_CTRL_5:
	हाल MADERA_MIC_BIAS_CTRL_6:
	हाल MADERA_HP_CTRL_1L:
	हाल MADERA_HP_CTRL_1R:
	हाल MADERA_DCS_HP1L_CONTROL:
	हाल MADERA_DCS_HP1R_CONTROL:
	हाल MADERA_EDRE_HP_STEREO_CONTROL:
	हाल MADERA_ACCESSORY_DETECT_MODE_1:
	हाल MADERA_HEADPHONE_DETECT_1:
	हाल MADERA_HEADPHONE_DETECT_2:
	हाल MADERA_HEADPHONE_DETECT_3:
	हाल MADERA_HEADPHONE_DETECT_5:
	हाल MADERA_MICD_CLAMP_CONTROL:
	हाल MADERA_MIC_DETECT_1_CONTROL_1:
	हाल MADERA_MIC_DETECT_1_CONTROL_2:
	हाल MADERA_MIC_DETECT_1_CONTROL_3:
	हाल MADERA_MIC_DETECT_1_LEVEL_1:
	हाल MADERA_MIC_DETECT_1_LEVEL_2:
	हाल MADERA_MIC_DETECT_1_LEVEL_3:
	हाल MADERA_MIC_DETECT_1_LEVEL_4:
	हाल MADERA_MIC_DETECT_1_CONTROL_4:
	हाल MADERA_GP_SWITCH_1:
	हाल MADERA_JACK_DETECT_ANALOGUE:
	हाल MADERA_INPUT_ENABLES:
	हाल MADERA_INPUT_ENABLES_STATUS:
	हाल MADERA_INPUT_RATE:
	हाल MADERA_INPUT_VOLUME_RAMP:
	हाल MADERA_HPF_CONTROL:
	हाल MADERA_IN1L_CONTROL:
	हाल MADERA_ADC_DIGITAL_VOLUME_1L:
	हाल MADERA_DMIC1L_CONTROL:
	हाल MADERA_IN1R_CONTROL:
	हाल MADERA_ADC_DIGITAL_VOLUME_1R:
	हाल MADERA_DMIC1R_CONTROL:
	हाल MADERA_IN2L_CONTROL:
	हाल MADERA_ADC_DIGITAL_VOLUME_2L:
	हाल MADERA_DMIC2L_CONTROL:
	हाल MADERA_IN2R_CONTROL:
	हाल MADERA_ADC_DIGITAL_VOLUME_2R:
	हाल MADERA_DMIC2R_CONTROL:
	हाल MADERA_OUTPUT_ENABLES_1:
	हाल MADERA_OUTPUT_STATUS_1:
	हाल MADERA_RAW_OUTPUT_STATUS_1:
	हाल MADERA_OUTPUT_RATE_1:
	हाल MADERA_OUTPUT_VOLUME_RAMP:
	हाल MADERA_OUTPUT_PATH_CONFIG_1L:
	हाल MADERA_DAC_DIGITAL_VOLUME_1L:
	हाल MADERA_NOISE_GATE_SELECT_1L:
	हाल MADERA_OUTPUT_PATH_CONFIG_1R:
	हाल MADERA_DAC_DIGITAL_VOLUME_1R:
	हाल MADERA_NOISE_GATE_SELECT_1R:
	हाल MADERA_OUTPUT_PATH_CONFIG_4L:
	हाल MADERA_DAC_DIGITAL_VOLUME_4L:
	हाल MADERA_NOISE_GATE_SELECT_4L:
	हाल MADERA_OUTPUT_PATH_CONFIG_5L:
	हाल MADERA_DAC_DIGITAL_VOLUME_5L:
	हाल MADERA_NOISE_GATE_SELECT_5L:
	हाल MADERA_OUTPUT_PATH_CONFIG_5R:
	हाल MADERA_DAC_DIGITAL_VOLUME_5R:
	हाल MADERA_NOISE_GATE_SELECT_5R:
	हाल MADERA_DAC_AEC_CONTROL_1:
	हाल MADERA_DAC_AEC_CONTROL_2:
	हाल MADERA_NOISE_GATE_CONTROL:
	हाल MADERA_PDM_SPK1_CTRL_1:
	हाल MADERA_PDM_SPK1_CTRL_2:
	हाल MADERA_HP1_SHORT_CIRCUIT_CTRL:
	हाल MADERA_HP_TEST_CTRL_5:
	हाल MADERA_HP_TEST_CTRL_6:
	हाल MADERA_AIF1_BCLK_CTRL:
	हाल MADERA_AIF1_TX_PIN_CTRL:
	हाल MADERA_AIF1_RX_PIN_CTRL:
	हाल MADERA_AIF1_RATE_CTRL:
	हाल MADERA_AIF1_FORMAT:
	हाल MADERA_AIF1_RX_BCLK_RATE:
	हाल MADERA_AIF1_FRAME_CTRL_1:
	हाल MADERA_AIF1_FRAME_CTRL_2:
	हाल MADERA_AIF1_FRAME_CTRL_3:
	हाल MADERA_AIF1_FRAME_CTRL_4:
	हाल MADERA_AIF1_FRAME_CTRL_5:
	हाल MADERA_AIF1_FRAME_CTRL_6:
	हाल MADERA_AIF1_FRAME_CTRL_7:
	हाल MADERA_AIF1_FRAME_CTRL_8:
	हाल MADERA_AIF1_FRAME_CTRL_11:
	हाल MADERA_AIF1_FRAME_CTRL_12:
	हाल MADERA_AIF1_FRAME_CTRL_13:
	हाल MADERA_AIF1_FRAME_CTRL_14:
	हाल MADERA_AIF1_FRAME_CTRL_15:
	हाल MADERA_AIF1_FRAME_CTRL_16:
	हाल MADERA_AIF1_TX_ENABLES:
	हाल MADERA_AIF1_RX_ENABLES:
	हाल MADERA_AIF2_BCLK_CTRL:
	हाल MADERA_AIF2_TX_PIN_CTRL:
	हाल MADERA_AIF2_RX_PIN_CTRL:
	हाल MADERA_AIF2_RATE_CTRL:
	हाल MADERA_AIF2_FORMAT:
	हाल MADERA_AIF2_RX_BCLK_RATE:
	हाल MADERA_AIF2_FRAME_CTRL_1:
	हाल MADERA_AIF2_FRAME_CTRL_2:
	हाल MADERA_AIF2_FRAME_CTRL_3:
	हाल MADERA_AIF2_FRAME_CTRL_4:
	हाल MADERA_AIF2_FRAME_CTRL_11:
	हाल MADERA_AIF2_FRAME_CTRL_12:
	हाल MADERA_AIF2_TX_ENABLES:
	हाल MADERA_AIF2_RX_ENABLES:
	हाल MADERA_AIF3_BCLK_CTRL:
	हाल MADERA_AIF3_TX_PIN_CTRL:
	हाल MADERA_AIF3_RX_PIN_CTRL:
	हाल MADERA_AIF3_RATE_CTRL:
	हाल MADERA_AIF3_FORMAT:
	हाल MADERA_AIF3_RX_BCLK_RATE:
	हाल MADERA_AIF3_FRAME_CTRL_1:
	हाल MADERA_AIF3_FRAME_CTRL_2:
	हाल MADERA_AIF3_FRAME_CTRL_3:
	हाल MADERA_AIF3_FRAME_CTRL_4:
	हाल MADERA_AIF3_FRAME_CTRL_11:
	हाल MADERA_AIF3_FRAME_CTRL_12:
	हाल MADERA_AIF3_TX_ENABLES:
	हाल MADERA_AIF3_RX_ENABLES:
	हाल MADERA_SPD1_TX_CONTROL:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_1:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_2:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_3:
	हाल MADERA_SLIMBUS_FRAMER_REF_GEAR:
	हाल MADERA_SLIMBUS_RATES_1:
	हाल MADERA_SLIMBUS_RATES_2:
	हाल MADERA_SLIMBUS_RATES_3:
	हाल MADERA_SLIMBUS_RATES_5:
	हाल MADERA_SLIMBUS_RATES_6:
	हाल MADERA_SLIMBUS_RATES_7:
	हाल MADERA_SLIMBUS_RX_CHANNEL_ENABLE:
	हाल MADERA_SLIMBUS_TX_CHANNEL_ENABLE:
	हाल MADERA_SLIMBUS_RX_PORT_STATUS:
	हाल MADERA_SLIMBUS_TX_PORT_STATUS:
	हाल MADERA_PWM1MIX_INPUT_1_SOURCE:
	हाल MADERA_PWM1MIX_INPUT_1_VOLUME:
	हाल MADERA_PWM1MIX_INPUT_2_SOURCE:
	हाल MADERA_PWM1MIX_INPUT_2_VOLUME:
	हाल MADERA_PWM1MIX_INPUT_3_SOURCE:
	हाल MADERA_PWM1MIX_INPUT_3_VOLUME:
	हाल MADERA_PWM1MIX_INPUT_4_SOURCE:
	हाल MADERA_PWM1MIX_INPUT_4_VOLUME:
	हाल MADERA_PWM2MIX_INPUT_1_SOURCE:
	हाल MADERA_PWM2MIX_INPUT_1_VOLUME:
	हाल MADERA_PWM2MIX_INPUT_2_SOURCE:
	हाल MADERA_PWM2MIX_INPUT_2_VOLUME:
	हाल MADERA_PWM2MIX_INPUT_3_SOURCE:
	हाल MADERA_PWM2MIX_INPUT_3_VOLUME:
	हाल MADERA_PWM2MIX_INPUT_4_SOURCE:
	हाल MADERA_PWM2MIX_INPUT_4_VOLUME:
	हाल MADERA_OUT1LMIX_INPUT_1_SOURCE:
	हाल MADERA_OUT1LMIX_INPUT_1_VOLUME:
	हाल MADERA_OUT1LMIX_INPUT_2_SOURCE:
	हाल MADERA_OUT1LMIX_INPUT_2_VOLUME:
	हाल MADERA_OUT1LMIX_INPUT_3_SOURCE:
	हाल MADERA_OUT1LMIX_INPUT_3_VOLUME:
	हाल MADERA_OUT1LMIX_INPUT_4_SOURCE:
	हाल MADERA_OUT1LMIX_INPUT_4_VOLUME:
	हाल MADERA_OUT1RMIX_INPUT_1_SOURCE:
	हाल MADERA_OUT1RMIX_INPUT_1_VOLUME:
	हाल MADERA_OUT1RMIX_INPUT_2_SOURCE:
	हाल MADERA_OUT1RMIX_INPUT_2_VOLUME:
	हाल MADERA_OUT1RMIX_INPUT_3_SOURCE:
	हाल MADERA_OUT1RMIX_INPUT_3_VOLUME:
	हाल MADERA_OUT1RMIX_INPUT_4_SOURCE:
	हाल MADERA_OUT1RMIX_INPUT_4_VOLUME:
	हाल MADERA_OUT4LMIX_INPUT_1_SOURCE:
	हाल MADERA_OUT4LMIX_INPUT_1_VOLUME:
	हाल MADERA_OUT4LMIX_INPUT_2_SOURCE:
	हाल MADERA_OUT4LMIX_INPUT_2_VOLUME:
	हाल MADERA_OUT4LMIX_INPUT_3_SOURCE:
	हाल MADERA_OUT4LMIX_INPUT_3_VOLUME:
	हाल MADERA_OUT4LMIX_INPUT_4_SOURCE:
	हाल MADERA_OUT4LMIX_INPUT_4_VOLUME:
	हाल MADERA_OUT5LMIX_INPUT_1_SOURCE:
	हाल MADERA_OUT5LMIX_INPUT_1_VOLUME:
	हाल MADERA_OUT5LMIX_INPUT_2_SOURCE:
	हाल MADERA_OUT5LMIX_INPUT_2_VOLUME:
	हाल MADERA_OUT5LMIX_INPUT_3_SOURCE:
	हाल MADERA_OUT5LMIX_INPUT_3_VOLUME:
	हाल MADERA_OUT5LMIX_INPUT_4_SOURCE:
	हाल MADERA_OUT5LMIX_INPUT_4_VOLUME:
	हाल MADERA_OUT5RMIX_INPUT_1_SOURCE:
	हाल MADERA_OUT5RMIX_INPUT_1_VOLUME:
	हाल MADERA_OUT5RMIX_INPUT_2_SOURCE:
	हाल MADERA_OUT5RMIX_INPUT_2_VOLUME:
	हाल MADERA_OUT5RMIX_INPUT_3_SOURCE:
	हाल MADERA_OUT5RMIX_INPUT_3_VOLUME:
	हाल MADERA_OUT5RMIX_INPUT_4_SOURCE:
	हाल MADERA_OUT5RMIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX1MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX1MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX1MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX1MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX1MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX1MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX1MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX1MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX2MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX2MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX2MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX2MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX2MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX2MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX2MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX2MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX3MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX3MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX3MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX3MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX3MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX3MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX3MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX3MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX4MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX4MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX4MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX4MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX4MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX4MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX4MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX4MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX5MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX5MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX5MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX5MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX5MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX5MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX5MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX5MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF1TX6MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF1TX6MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF1TX6MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF1TX6MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF1TX6MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF1TX6MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF1TX6MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF1TX6MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF2TX1MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF2TX1MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF2TX1MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF2TX1MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF2TX1MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF2TX1MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF2TX1MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF2TX1MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF2TX2MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF2TX2MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF2TX2MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF2TX2MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF2TX2MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF2TX2MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF2TX2MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF2TX2MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF3TX1MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF3TX1MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF3TX1MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF3TX1MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF3TX1MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF3TX1MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF3TX1MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF3TX1MIX_INPUT_4_VOLUME:
	हाल MADERA_AIF3TX2MIX_INPUT_1_SOURCE:
	हाल MADERA_AIF3TX2MIX_INPUT_1_VOLUME:
	हाल MADERA_AIF3TX2MIX_INPUT_2_SOURCE:
	हाल MADERA_AIF3TX2MIX_INPUT_2_VOLUME:
	हाल MADERA_AIF3TX2MIX_INPUT_3_SOURCE:
	हाल MADERA_AIF3TX2MIX_INPUT_3_VOLUME:
	हाल MADERA_AIF3TX2MIX_INPUT_4_SOURCE:
	हाल MADERA_AIF3TX2MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX1MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX1MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX1MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX1MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX1MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX1MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX1MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX1MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX2MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX2MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX2MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX2MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX2MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX2MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX2MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX2MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX3MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX3MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX3MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX3MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX3MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX3MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX3MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX3MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX4MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX4MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX4MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX4MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX4MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX4MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX4MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX4MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX5MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX5MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX5MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX5MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX5MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX5MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX5MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX5MIX_INPUT_4_VOLUME:
	हाल MADERA_SLIMTX6MIX_INPUT_1_SOURCE:
	हाल MADERA_SLIMTX6MIX_INPUT_1_VOLUME:
	हाल MADERA_SLIMTX6MIX_INPUT_2_SOURCE:
	हाल MADERA_SLIMTX6MIX_INPUT_2_VOLUME:
	हाल MADERA_SLIMTX6MIX_INPUT_3_SOURCE:
	हाल MADERA_SLIMTX6MIX_INPUT_3_VOLUME:
	हाल MADERA_SLIMTX6MIX_INPUT_4_SOURCE:
	हाल MADERA_SLIMTX6MIX_INPUT_4_VOLUME:
	हाल MADERA_SPDIF1TX1MIX_INPUT_1_SOURCE:
	हाल MADERA_SPDIF1TX1MIX_INPUT_1_VOLUME:
	हाल MADERA_SPDIF1TX2MIX_INPUT_1_SOURCE:
	हाल MADERA_SPDIF1TX2MIX_INPUT_1_VOLUME:
	हाल MADERA_EQ1MIX_INPUT_1_SOURCE:
	हाल MADERA_EQ1MIX_INPUT_1_VOLUME:
	हाल MADERA_EQ1MIX_INPUT_2_SOURCE:
	हाल MADERA_EQ1MIX_INPUT_2_VOLUME:
	हाल MADERA_EQ1MIX_INPUT_3_SOURCE:
	हाल MADERA_EQ1MIX_INPUT_3_VOLUME:
	हाल MADERA_EQ1MIX_INPUT_4_SOURCE:
	हाल MADERA_EQ1MIX_INPUT_4_VOLUME:
	हाल MADERA_EQ2MIX_INPUT_1_SOURCE:
	हाल MADERA_EQ2MIX_INPUT_1_VOLUME:
	हाल MADERA_EQ2MIX_INPUT_2_SOURCE:
	हाल MADERA_EQ2MIX_INPUT_2_VOLUME:
	हाल MADERA_EQ2MIX_INPUT_3_SOURCE:
	हाल MADERA_EQ2MIX_INPUT_3_VOLUME:
	हाल MADERA_EQ2MIX_INPUT_4_SOURCE:
	हाल MADERA_EQ2MIX_INPUT_4_VOLUME:
	हाल MADERA_EQ3MIX_INPUT_1_SOURCE:
	हाल MADERA_EQ3MIX_INPUT_1_VOLUME:
	हाल MADERA_EQ3MIX_INPUT_2_SOURCE:
	हाल MADERA_EQ3MIX_INPUT_2_VOLUME:
	हाल MADERA_EQ3MIX_INPUT_3_SOURCE:
	हाल MADERA_EQ3MIX_INPUT_3_VOLUME:
	हाल MADERA_EQ3MIX_INPUT_4_SOURCE:
	हाल MADERA_EQ3MIX_INPUT_4_VOLUME:
	हाल MADERA_EQ4MIX_INPUT_1_SOURCE:
	हाल MADERA_EQ4MIX_INPUT_1_VOLUME:
	हाल MADERA_EQ4MIX_INPUT_2_SOURCE:
	हाल MADERA_EQ4MIX_INPUT_2_VOLUME:
	हाल MADERA_EQ4MIX_INPUT_3_SOURCE:
	हाल MADERA_EQ4MIX_INPUT_3_VOLUME:
	हाल MADERA_EQ4MIX_INPUT_4_SOURCE:
	हाल MADERA_EQ4MIX_INPUT_4_VOLUME:
	हाल MADERA_DRC1LMIX_INPUT_1_SOURCE:
	हाल MADERA_DRC1LMIX_INPUT_1_VOLUME:
	हाल MADERA_DRC1LMIX_INPUT_2_SOURCE:
	हाल MADERA_DRC1LMIX_INPUT_2_VOLUME:
	हाल MADERA_DRC1LMIX_INPUT_3_SOURCE:
	हाल MADERA_DRC1LMIX_INPUT_3_VOLUME:
	हाल MADERA_DRC1LMIX_INPUT_4_SOURCE:
	हाल MADERA_DRC1LMIX_INPUT_4_VOLUME:
	हाल MADERA_DRC1RMIX_INPUT_1_SOURCE:
	हाल MADERA_DRC1RMIX_INPUT_1_VOLUME:
	हाल MADERA_DRC1RMIX_INPUT_2_SOURCE:
	हाल MADERA_DRC1RMIX_INPUT_2_VOLUME:
	हाल MADERA_DRC1RMIX_INPUT_3_SOURCE:
	हाल MADERA_DRC1RMIX_INPUT_3_VOLUME:
	हाल MADERA_DRC1RMIX_INPUT_4_SOURCE:
	हाल MADERA_DRC1RMIX_INPUT_4_VOLUME:
	हाल MADERA_DRC2LMIX_INPUT_1_SOURCE:
	हाल MADERA_DRC2LMIX_INPUT_1_VOLUME:
	हाल MADERA_DRC2LMIX_INPUT_2_SOURCE:
	हाल MADERA_DRC2LMIX_INPUT_2_VOLUME:
	हाल MADERA_DRC2LMIX_INPUT_3_SOURCE:
	हाल MADERA_DRC2LMIX_INPUT_3_VOLUME:
	हाल MADERA_DRC2LMIX_INPUT_4_SOURCE:
	हाल MADERA_DRC2LMIX_INPUT_4_VOLUME:
	हाल MADERA_DRC2RMIX_INPUT_1_SOURCE:
	हाल MADERA_DRC2RMIX_INPUT_1_VOLUME:
	हाल MADERA_DRC2RMIX_INPUT_2_SOURCE:
	हाल MADERA_DRC2RMIX_INPUT_2_VOLUME:
	हाल MADERA_DRC2RMIX_INPUT_3_SOURCE:
	हाल MADERA_DRC2RMIX_INPUT_3_VOLUME:
	हाल MADERA_DRC2RMIX_INPUT_4_SOURCE:
	हाल MADERA_DRC2RMIX_INPUT_4_VOLUME:
	हाल MADERA_HPLP1MIX_INPUT_1_SOURCE:
	हाल MADERA_HPLP1MIX_INPUT_1_VOLUME:
	हाल MADERA_HPLP1MIX_INPUT_2_SOURCE:
	हाल MADERA_HPLP1MIX_INPUT_2_VOLUME:
	हाल MADERA_HPLP1MIX_INPUT_3_SOURCE:
	हाल MADERA_HPLP1MIX_INPUT_3_VOLUME:
	हाल MADERA_HPLP1MIX_INPUT_4_SOURCE:
	हाल MADERA_HPLP1MIX_INPUT_4_VOLUME:
	हाल MADERA_HPLP2MIX_INPUT_1_SOURCE:
	हाल MADERA_HPLP2MIX_INPUT_1_VOLUME:
	हाल MADERA_HPLP2MIX_INPUT_2_SOURCE:
	हाल MADERA_HPLP2MIX_INPUT_2_VOLUME:
	हाल MADERA_HPLP2MIX_INPUT_3_SOURCE:
	हाल MADERA_HPLP2MIX_INPUT_3_VOLUME:
	हाल MADERA_HPLP2MIX_INPUT_4_SOURCE:
	हाल MADERA_HPLP2MIX_INPUT_4_VOLUME:
	हाल MADERA_HPLP3MIX_INPUT_1_SOURCE:
	हाल MADERA_HPLP3MIX_INPUT_1_VOLUME:
	हाल MADERA_HPLP3MIX_INPUT_2_SOURCE:
	हाल MADERA_HPLP3MIX_INPUT_2_VOLUME:
	हाल MADERA_HPLP3MIX_INPUT_3_SOURCE:
	हाल MADERA_HPLP3MIX_INPUT_3_VOLUME:
	हाल MADERA_HPLP3MIX_INPUT_4_SOURCE:
	हाल MADERA_HPLP3MIX_INPUT_4_VOLUME:
	हाल MADERA_HPLP4MIX_INPUT_1_SOURCE:
	हाल MADERA_HPLP4MIX_INPUT_1_VOLUME:
	हाल MADERA_HPLP4MIX_INPUT_2_SOURCE:
	हाल MADERA_HPLP4MIX_INPUT_2_VOLUME:
	हाल MADERA_HPLP4MIX_INPUT_3_SOURCE:
	हाल MADERA_HPLP4MIX_INPUT_3_VOLUME:
	हाल MADERA_HPLP4MIX_INPUT_4_SOURCE:
	हाल MADERA_HPLP4MIX_INPUT_4_VOLUME:
	हाल MADERA_DSP1LMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1LMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP1LMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP1LMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP1LMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP1LMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP1LMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP1LMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP1RMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1RMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP1RMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP1RMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP1RMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP1RMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP1RMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP1RMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP1AUX1MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1AUX2MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1AUX3MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1AUX4MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1AUX5MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP1AUX6MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2LMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2LMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP2LMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP2LMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP2LMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP2LMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP2LMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP2LMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP2RMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2RMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP2RMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP2RMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP2RMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP2RMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP2RMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP2RMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP2AUX1MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2AUX2MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2AUX3MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2AUX4MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2AUX5MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP2AUX6MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3LMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3LMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP3LMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP3LMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP3LMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP3LMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP3LMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP3LMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP3RMIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3RMIX_INPUT_1_VOLUME:
	हाल MADERA_DSP3RMIX_INPUT_2_SOURCE:
	हाल MADERA_DSP3RMIX_INPUT_2_VOLUME:
	हाल MADERA_DSP3RMIX_INPUT_3_SOURCE:
	हाल MADERA_DSP3RMIX_INPUT_3_VOLUME:
	हाल MADERA_DSP3RMIX_INPUT_4_SOURCE:
	हाल MADERA_DSP3RMIX_INPUT_4_VOLUME:
	हाल MADERA_DSP3AUX1MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3AUX2MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3AUX3MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3AUX4MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3AUX5MIX_INPUT_1_SOURCE:
	हाल MADERA_DSP3AUX6MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1DEC1MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1DEC2MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1DEC3MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1DEC4MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1INT1MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1INT2MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1INT3MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC1INT4MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2DEC1MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2DEC2MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2DEC3MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2DEC4MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2INT1MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2INT2MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2INT3MIX_INPUT_1_SOURCE:
	हाल MADERA_ISRC2INT4MIX_INPUT_1_SOURCE:
	हाल MADERA_FX_CTRL1:
	हाल MADERA_FX_CTRL2:
	हाल MADERA_EQ1_1 ... MADERA_EQ1_21:
	हाल MADERA_EQ2_1 ... MADERA_EQ2_21:
	हाल MADERA_EQ3_1 ... MADERA_EQ3_21:
	हाल MADERA_EQ4_1 ... MADERA_EQ4_21:
	हाल MADERA_DRC1_CTRL1:
	हाल MADERA_DRC1_CTRL2:
	हाल MADERA_DRC1_CTRL3:
	हाल MADERA_DRC1_CTRL4:
	हाल MADERA_DRC1_CTRL5:
	हाल MADERA_DRC2_CTRL1:
	हाल MADERA_DRC2_CTRL2:
	हाल MADERA_DRC2_CTRL3:
	हाल MADERA_DRC2_CTRL4:
	हाल MADERA_DRC2_CTRL5:
	हाल MADERA_HPLPF1_1:
	हाल MADERA_HPLPF1_2:
	हाल MADERA_HPLPF2_1:
	हाल MADERA_HPLPF2_2:
	हाल MADERA_HPLPF3_1:
	हाल MADERA_HPLPF3_2:
	हाल MADERA_HPLPF4_1:
	हाल MADERA_HPLPF4_2:
	हाल MADERA_ISRC_1_CTRL_1:
	हाल MADERA_ISRC_1_CTRL_2:
	हाल MADERA_ISRC_1_CTRL_3:
	हाल MADERA_ISRC_2_CTRL_1:
	हाल MADERA_ISRC_2_CTRL_2:
	हाल MADERA_ISRC_2_CTRL_3:
	हाल MADERA_GPIO1_CTRL_1 ... MADERA_GPIO16_CTRL_2:
	हाल MADERA_IRQ1_STATUS_1 ... MADERA_IRQ1_STATUS_33:
	हाल MADERA_IRQ1_MASK_1 ... MADERA_IRQ1_MASK_33:
	हाल MADERA_IRQ1_RAW_STATUS_1 ... MADERA_IRQ1_RAW_STATUS_33:
	हाल MADERA_INTERRUPT_DEBOUNCE_7:
	हाल MADERA_IRQ1_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs47l35_16bit_अस्थिर_रेजिस्टर(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MADERA_SOFTWARE_RESET:
	हाल MADERA_HARDWARE_REVISION:
	हाल MADERA_WRITE_SEQUENCER_CTRL_0:
	हाल MADERA_WRITE_SEQUENCER_CTRL_1:
	हाल MADERA_WRITE_SEQUENCER_CTRL_2:
	हाल MADERA_HAPTICS_STATUS:
	हाल MADERA_SAMPLE_RATE_1_STATUS:
	हाल MADERA_SAMPLE_RATE_2_STATUS:
	हाल MADERA_SAMPLE_RATE_3_STATUS:
	हाल MADERA_HP_CTRL_1L:
	हाल MADERA_HP_CTRL_1R:
	हाल MADERA_DCS_HP1L_CONTROL:
	हाल MADERA_DCS_HP1R_CONTROL:
	हाल MADERA_MIC_DETECT_1_CONTROL_3:
	हाल MADERA_MIC_DETECT_1_CONTROL_4:
	हाल MADERA_HEADPHONE_DETECT_2:
	हाल MADERA_HEADPHONE_DETECT_3:
	हाल MADERA_HEADPHONE_DETECT_5:
	हाल MADERA_INPUT_ENABLES_STATUS:
	हाल MADERA_OUTPUT_STATUS_1:
	हाल MADERA_RAW_OUTPUT_STATUS_1:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_1:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_2:
	हाल MADERA_SPD1_TX_CHANNEL_STATUS_3:
	हाल MADERA_SLIMBUS_RX_PORT_STATUS:
	हाल MADERA_SLIMBUS_TX_PORT_STATUS:
	हाल MADERA_FX_CTRL2:
	हाल MADERA_IRQ1_STATUS_1 ... MADERA_IRQ1_STATUS_33:
	हाल MADERA_IRQ1_RAW_STATUS_1 ... MADERA_IRQ1_RAW_STATUS_33:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs47l35_32bit_पढ़ोable_रेजिस्टर(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MADERA_WSEQ_SEQUENCE_1 ... MADERA_WSEQ_SEQUENCE_252:
	हाल CS47L35_OTP_HPDET_CAL_1 ... CS47L35_OTP_HPDET_CAL_2:
	हाल MADERA_DSP1_CONFIG_1 ... MADERA_DSP1_SCRATCH_2:
	हाल MADERA_DSP2_CONFIG_1 ... MADERA_DSP2_SCRATCH_2:
	हाल MADERA_DSP3_CONFIG_1 ... MADERA_DSP3_SCRATCH_2:
		वापस true;
	शेष:
		वापस cs47l35_is_adsp_memory(reg);
	पूर्ण
पूर्ण

अटल bool cs47l35_32bit_अस्थिर_रेजिस्टर(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MADERA_WSEQ_SEQUENCE_1 ... MADERA_WSEQ_SEQUENCE_252:
	हाल CS47L35_OTP_HPDET_CAL_1 ... CS47L35_OTP_HPDET_CAL_2:
	हाल MADERA_DSP1_CONFIG_1 ... MADERA_DSP1_SCRATCH_2:
	हाल MADERA_DSP2_CONFIG_1 ... MADERA_DSP2_SCRATCH_2:
	हाल MADERA_DSP3_CONFIG_1 ... MADERA_DSP3_SCRATCH_2:
		वापस true;
	शेष:
		वापस cs47l35_is_adsp_memory(reg);
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config cs47l35_16bit_spi_regmap = अणु
	.name = "cs47l35_16bit",
	.reg_bits = 32,
	.pad_bits = 16,
	.val_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = 0x1b00,
	.पढ़ोable_reg = cs47l35_16bit_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs47l35_16bit_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = cs47l35_reg_शेष,
	.num_reg_शेषs = ARRAY_SIZE(cs47l35_reg_शेष),
पूर्ण;
EXPORT_SYMBOL_GPL(cs47l35_16bit_spi_regmap);

स्थिर काष्ठा regmap_config cs47l35_16bit_i2c_regmap = अणु
	.name = "cs47l35_16bit",
	.reg_bits = 32,
	.val_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = 0x1b00,
	.पढ़ोable_reg = cs47l35_16bit_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs47l35_16bit_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = cs47l35_reg_शेष,
	.num_reg_शेषs = ARRAY_SIZE(cs47l35_reg_शेष),
पूर्ण;
EXPORT_SYMBOL_GPL(cs47l35_16bit_i2c_regmap);

स्थिर काष्ठा regmap_config cs47l35_32bit_spi_regmap = अणु
	.name = "cs47l35_32bit",
	.reg_bits = 32,
	.reg_stride = 2,
	.pad_bits = 16,
	.val_bits = 32,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = MADERA_DSP3_SCRATCH_2,
	.पढ़ोable_reg = cs47l35_32bit_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs47l35_32bit_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(cs47l35_32bit_spi_regmap);

स्थिर काष्ठा regmap_config cs47l35_32bit_i2c_regmap = अणु
	.name = "cs47l35_32bit",
	.reg_bits = 32,
	.reg_stride = 2,
	.val_bits = 32,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = MADERA_DSP3_SCRATCH_2,
	.पढ़ोable_reg = cs47l35_32bit_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs47l35_32bit_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(cs47l35_32bit_i2c_regmap);
