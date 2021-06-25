<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8994-regmap.c  --  Register map data क्रम WM8994 series devices
 *
 * Copyright 2011 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/regmap.h>
#समावेश <linux/device.h>

#समावेश "wm8994.h"

अटल स्थिर काष्ठा reg_शेष wm1811_शेषs[] = अणु
	अणु 0x0001, 0x0000 पूर्ण,    /* R1    - Power Management (1) */
	अणु 0x0002, 0x6000 पूर्ण,    /* R2    - Power Management (2) */
	अणु 0x0003, 0x0000 पूर्ण,    /* R3    - Power Management (3) */
	अणु 0x0004, 0x0000 पूर्ण,    /* R4    - Power Management (4) */
	अणु 0x0005, 0x0000 पूर्ण,    /* R5    - Power Management (5) */
	अणु 0x0006, 0x0000 पूर्ण,    /* R6    - Power Management (6) */
	अणु 0x0015, 0x0000 पूर्ण,    /* R21   - Input Mixer (1) */
	अणु 0x0018, 0x008B पूर्ण,    /* R24   - Left Line Input 1&2 Volume */
	अणु 0x0019, 0x008B पूर्ण,    /* R25   - Left Line Input 3&4 Volume */
	अणु 0x001A, 0x008B पूर्ण,    /* R26   - Right Line Input 1&2 Volume */
	अणु 0x001B, 0x008B पूर्ण,    /* R27   - Right Line Input 3&4 Volume */
	अणु 0x001C, 0x006D पूर्ण,    /* R28   - Left Output Volume */
	अणु 0x001D, 0x006D पूर्ण,    /* R29   - Right Output Volume */
	अणु 0x001E, 0x0066 पूर्ण,    /* R30   - Line Outमाला_दो Volume */
	अणु 0x001F, 0x0020 पूर्ण,    /* R31   - HPOUT2 Volume */
	अणु 0x0020, 0x0079 पूर्ण,    /* R32   - Left OPGA Volume */
	अणु 0x0021, 0x0079 पूर्ण,    /* R33   - Right OPGA Volume */
	अणु 0x0022, 0x0003 पूर्ण,    /* R34   - SPKMIXL Attenuation */
	अणु 0x0023, 0x0003 पूर्ण,    /* R35   - SPKMIXR Attenuation */
	अणु 0x0024, 0x0011 पूर्ण,    /* R36   - SPKOUT Mixers */
	अणु 0x0025, 0x0140 पूर्ण,    /* R37   - ClassD */
	अणु 0x0026, 0x0079 पूर्ण,    /* R38   - Speaker Volume Left */
	अणु 0x0027, 0x0079 पूर्ण,    /* R39   - Speaker Volume Right */
	अणु 0x0028, 0x0000 पूर्ण,    /* R40   - Input Mixer (2) */
	अणु 0x0029, 0x0000 पूर्ण,    /* R41   - Input Mixer (3) */
	अणु 0x002A, 0x0000 पूर्ण,    /* R42   - Input Mixer (4) */
	अणु 0x002B, 0x0000 पूर्ण,    /* R43   - Input Mixer (5) */
	अणु 0x002C, 0x0000 पूर्ण,    /* R44   - Input Mixer (6) */
	अणु 0x002D, 0x0000 पूर्ण,    /* R45   - Output Mixer (1) */
	अणु 0x002E, 0x0000 पूर्ण,    /* R46   - Output Mixer (2) */
	अणु 0x002F, 0x0000 पूर्ण,    /* R47   - Output Mixer (3) */
	अणु 0x0030, 0x0000 पूर्ण,    /* R48   - Output Mixer (4) */
	अणु 0x0031, 0x0000 पूर्ण,    /* R49   - Output Mixer (5) */
	अणु 0x0032, 0x0000 पूर्ण,    /* R50   - Output Mixer (6) */
	अणु 0x0033, 0x0000 पूर्ण,    /* R51   - HPOUT2 Mixer */
	अणु 0x0034, 0x0000 पूर्ण,    /* R52   - Line Mixer (1) */
	अणु 0x0035, 0x0000 पूर्ण,    /* R53   - Line Mixer (2) */
	अणु 0x0036, 0x0000 पूर्ण,    /* R54   - Speaker Mixer */
	अणु 0x0037, 0x0000 पूर्ण,    /* R55   - Additional Control */
	अणु 0x0038, 0x0000 पूर्ण,    /* R56   - AntiPOP (1) */
	अणु 0x0039, 0x0000 पूर्ण,    /* R57   - AntiPOP (2) */
	अणु 0x003B, 0x000D पूर्ण,    /* R59   - LDO 1 */
	अणु 0x003C, 0x0003 पूर्ण,    /* R60   - LDO 2 */
	अणु 0x003D, 0x0039 पूर्ण,    /* R61   - MICBIAS1 */
	अणु 0x003E, 0x0039 पूर्ण,    /* R62   - MICBIAS2 */
	अणु 0x004C, 0x1F25 पूर्ण,    /* R76   - Charge Pump (1) */
	अणु 0x004D, 0xAB19 पूर्ण,    /* R77   - Charge Pump (2) */
	अणु 0x0051, 0x0004 पूर्ण,    /* R81   - Class W (1) */
	अणु 0x0055, 0x054A पूर्ण,    /* R85   - DC Servo (2) */
	अणु 0x0059, 0x0000 पूर्ण,    /* R89   - DC Servo (4) */
	अणु 0x0060, 0x0000 पूर्ण,    /* R96   - Analogue HP (1) */
	अणु 0x00C5, 0x0000 पूर्ण,    /* R197  - Class D Test (5) */
	अणु 0x00D0, 0x7600 पूर्ण,    /* R208  - Mic Detect 1 */
	अणु 0x00D1, 0x007F पूर्ण,    /* R209  - Mic Detect 2 */
	अणु 0x0101, 0x8004 पूर्ण,    /* R257  - Control Interface */
	अणु 0x0200, 0x0000 पूर्ण,    /* R512  - AIF1 Clocking (1) */
	अणु 0x0201, 0x0000 पूर्ण,    /* R513  - AIF1 Clocking (2) */
	अणु 0x0204, 0x0000 पूर्ण,    /* R516  - AIF2 Clocking (1) */
	अणु 0x0205, 0x0000 पूर्ण,    /* R517  - AIF2 Clocking (2) */
	अणु 0x0208, 0x0000 पूर्ण,    /* R520  - Clocking (1) */
	अणु 0x0209, 0x0000 पूर्ण,    /* R521  - Clocking (2) */
	अणु 0x0210, 0x0083 पूर्ण,    /* R528  - AIF1 Rate */
	अणु 0x0211, 0x0083 पूर्ण,    /* R529  - AIF2 Rate */
	अणु 0x0220, 0x0000 पूर्ण,    /* R544  - FLL1 Control (1) */
	अणु 0x0221, 0x0000 पूर्ण,    /* R545  - FLL1 Control (2) */
	अणु 0x0222, 0x0000 पूर्ण,    /* R546  - FLL1 Control (3) */
	अणु 0x0223, 0x0000 पूर्ण,    /* R547  - FLL1 Control (4) */
	अणु 0x0224, 0x0C80 पूर्ण,    /* R548  - FLL1 Control (5) */
	अणु 0x0226, 0x0000 पूर्ण,    /* R550  - FLL1 EFS 1 */
	अणु 0x0227, 0x0006 पूर्ण,    /* R551  - FLL1 EFS 2 */
	अणु 0x0240, 0x0000 पूर्ण,    /* R576  - FLL2Control (1) */
	अणु 0x0241, 0x0000 पूर्ण,    /* R577  - FLL2Control (2) */
	अणु 0x0242, 0x0000 पूर्ण,    /* R578  - FLL2Control (3) */
	अणु 0x0243, 0x0000 पूर्ण,    /* R579  - FLL2 Control (4) */
	अणु 0x0244, 0x0C80 पूर्ण,    /* R580  - FLL2Control (5) */
	अणु 0x0246, 0x0000 पूर्ण,    /* R582  - FLL2 EFS 1 */
	अणु 0x0247, 0x0006 पूर्ण,    /* R583  - FLL2 EFS 2 */
	अणु 0x0300, 0x4050 पूर्ण,    /* R768  - AIF1 Control (1) */
	अणु 0x0301, 0x4000 पूर्ण,    /* R769  - AIF1 Control (2) */
	अणु 0x0302, 0x0000 पूर्ण,    /* R770  - AIF1 Master/Slave */
	अणु 0x0303, 0x0040 पूर्ण,    /* R771  - AIF1 BCLK */
	अणु 0x0304, 0x0040 पूर्ण,    /* R772  - AIF1ADC LRCLK */
	अणु 0x0305, 0x0040 पूर्ण,    /* R773  - AIF1DAC LRCLK */
	अणु 0x0306, 0x0004 पूर्ण,    /* R774  - AIF1DAC Data */
	अणु 0x0307, 0x0100 पूर्ण,    /* R775  - AIF1ADC Data */
	अणु 0x0310, 0x4050 पूर्ण,    /* R784  - AIF2 Control (1) */
	अणु 0x0311, 0x4000 पूर्ण,    /* R785  - AIF2 Control (2) */
	अणु 0x0312, 0x0000 पूर्ण,    /* R786  - AIF2 Master/Slave */
	अणु 0x0313, 0x0040 पूर्ण,    /* R787  - AIF2 BCLK */
	अणु 0x0314, 0x0040 पूर्ण,    /* R788  - AIF2ADC LRCLK */
	अणु 0x0315, 0x0040 पूर्ण,    /* R789  - AIF2DAC LRCLK */
	अणु 0x0316, 0x0000 पूर्ण,    /* R790  - AIF2DAC Data */
	अणु 0x0317, 0x0000 पूर्ण,    /* R791  - AIF2ADC Data */
	अणु 0x0318, 0x0003 पूर्ण,    /* R792  - AIF2TX Control */
	अणु 0x0320, 0x0040 पूर्ण,    /* R800  - AIF3 Control (1) */
	अणु 0x0321, 0x0000 पूर्ण,    /* R801  - AIF3 Control (2) */
	अणु 0x0322, 0x0000 पूर्ण,    /* R802  - AIF3DAC Data */
	अणु 0x0323, 0x0000 पूर्ण,    /* R803  - AIF3ADC Data */
	अणु 0x0400, 0x00C0 पूर्ण,    /* R1024 - AIF1 ADC1 Left Volume */
	अणु 0x0401, 0x00C0 पूर्ण,    /* R1025 - AIF1 ADC1 Right Volume */
	अणु 0x0402, 0x00C0 पूर्ण,    /* R1026 - AIF1 DAC1 Left Volume */
	अणु 0x0403, 0x00C0 पूर्ण,    /* R1027 - AIF1 DAC1 Right Volume */
	अणु 0x0410, 0x0000 पूर्ण,    /* R1040 - AIF1 ADC1 Filters */
	अणु 0x0411, 0x0000 पूर्ण,    /* R1041 - AIF1 ADC2 Filters */
	अणु 0x0420, 0x0200 पूर्ण,    /* R1056 - AIF1 DAC1 Filters (1) */
	अणु 0x0421, 0x0010 पूर्ण,    /* R1057 - AIF1 DAC1 Filters (2) */
	अणु 0x0422, 0x0200 पूर्ण,    /* R1058 - AIF1 DAC2 Filters (1) */
	अणु 0x0423, 0x0010 पूर्ण,    /* R1059 - AIF1 DAC2 Filters (2) */
	अणु 0x0430, 0x0068 पूर्ण,    /* R1072 - AIF1 DAC1 Noise Gate */
	अणु 0x0431, 0x0068 पूर्ण,    /* R1073 - AIF1 DAC2 Noise Gate */
	अणु 0x0440, 0x0098 पूर्ण,    /* R1088 - AIF1 DRC1 (1) */
	अणु 0x0441, 0x0845 पूर्ण,    /* R1089 - AIF1 DRC1 (2) */
	अणु 0x0442, 0x0000 पूर्ण,    /* R1090 - AIF1 DRC1 (3) */
	अणु 0x0443, 0x0000 पूर्ण,    /* R1091 - AIF1 DRC1 (4) */
	अणु 0x0444, 0x0000 पूर्ण,    /* R1092 - AIF1 DRC1 (5) */
	अणु 0x0450, 0x0098 पूर्ण,    /* R1104 - AIF1 DRC2 (1) */
	अणु 0x0451, 0x0845 पूर्ण,    /* R1105 - AIF1 DRC2 (2) */
	अणु 0x0452, 0x0000 पूर्ण,    /* R1106 - AIF1 DRC2 (3) */
	अणु 0x0453, 0x0000 पूर्ण,    /* R1107 - AIF1 DRC2 (4) */
	अणु 0x0454, 0x0000 पूर्ण,    /* R1108 - AIF1 DRC2 (5) */
	अणु 0x0480, 0x6318 पूर्ण,    /* R1152 - AIF1 DAC1 EQ Gains (1) */
	अणु 0x0481, 0x6300 पूर्ण,    /* R1153 - AIF1 DAC1 EQ Gains (2) */
	अणु 0x0482, 0x0FCA पूर्ण,    /* R1154 - AIF1 DAC1 EQ Band 1 A */
	अणु 0x0483, 0x0400 पूर्ण,    /* R1155 - AIF1 DAC1 EQ Band 1 B */
	अणु 0x0484, 0x00D8 पूर्ण,    /* R1156 - AIF1 DAC1 EQ Band 1 PG */
	अणु 0x0485, 0x1EB5 पूर्ण,    /* R1157 - AIF1 DAC1 EQ Band 2 A */
	अणु 0x0486, 0xF145 पूर्ण,    /* R1158 - AIF1 DAC1 EQ Band 2 B */
	अणु 0x0487, 0x0B75 पूर्ण,    /* R1159 - AIF1 DAC1 EQ Band 2 C */
	अणु 0x0488, 0x01C5 पूर्ण,    /* R1160 - AIF1 DAC1 EQ Band 2 PG */
	अणु 0x0489, 0x1C58 पूर्ण,    /* R1161 - AIF1 DAC1 EQ Band 3 A */
	अणु 0x048A, 0xF373 पूर्ण,    /* R1162 - AIF1 DAC1 EQ Band 3 B */
	अणु 0x048B, 0x0A54 पूर्ण,    /* R1163 - AIF1 DAC1 EQ Band 3 C */
	अणु 0x048C, 0x0558 पूर्ण,    /* R1164 - AIF1 DAC1 EQ Band 3 PG */
	अणु 0x048D, 0x168E पूर्ण,    /* R1165 - AIF1 DAC1 EQ Band 4 A */
	अणु 0x048E, 0xF829 पूर्ण,    /* R1166 - AIF1 DAC1 EQ Band 4 B */
	अणु 0x048F, 0x07AD पूर्ण,    /* R1167 - AIF1 DAC1 EQ Band 4 C */
	अणु 0x0490, 0x1103 पूर्ण,    /* R1168 - AIF1 DAC1 EQ Band 4 PG */
	अणु 0x0491, 0x0564 पूर्ण,    /* R1169 - AIF1 DAC1 EQ Band 5 A */
	अणु 0x0492, 0x0559 पूर्ण,    /* R1170 - AIF1 DAC1 EQ Band 5 B */
	अणु 0x0493, 0x4000 पूर्ण,    /* R1171 - AIF1 DAC1 EQ Band 5 PG */
	अणु 0x0494, 0x0000 पूर्ण,    /* R1172 - AIF1 DAC1 EQ Band 1 C */
	अणु 0x04A0, 0x6318 पूर्ण,    /* R1184 - AIF1 DAC2 EQ Gains (1) */
	अणु 0x04A1, 0x6300 पूर्ण,    /* R1185 - AIF1 DAC2 EQ Gains (2) */
	अणु 0x04A2, 0x0FCA पूर्ण,    /* R1186 - AIF1 DAC2 EQ Band 1 A */
	अणु 0x04A3, 0x0400 पूर्ण,    /* R1187 - AIF1 DAC2 EQ Band 1 B */
	अणु 0x04A4, 0x00D8 पूर्ण,    /* R1188 - AIF1 DAC2 EQ Band 1 PG */
	अणु 0x04A5, 0x1EB5 पूर्ण,    /* R1189 - AIF1 DAC2 EQ Band 2 A */
	अणु 0x04A6, 0xF145 पूर्ण,    /* R1190 - AIF1 DAC2 EQ Band 2 B */
	अणु 0x04A7, 0x0B75 पूर्ण,    /* R1191 - AIF1 DAC2 EQ Band 2 C */
	अणु 0x04A8, 0x01C5 पूर्ण,    /* R1192 - AIF1 DAC2 EQ Band 2 PG */
	अणु 0x04A9, 0x1C58 पूर्ण,    /* R1193 - AIF1 DAC2 EQ Band 3 A */
	अणु 0x04AA, 0xF373 पूर्ण,    /* R1194 - AIF1 DAC2 EQ Band 3 B */
	अणु 0x04AB, 0x0A54 पूर्ण,    /* R1195 - AIF1 DAC2 EQ Band 3 C */
	अणु 0x04AC, 0x0558 पूर्ण,    /* R1196 - AIF1 DAC2 EQ Band 3 PG */
	अणु 0x04AD, 0x168E पूर्ण,    /* R1197 - AIF1 DAC2 EQ Band 4 A */
	अणु 0x04AE, 0xF829 पूर्ण,    /* R1198 - AIF1 DAC2 EQ Band 4 B */
	अणु 0x04AF, 0x07AD पूर्ण,    /* R1199 - AIF1 DAC2 EQ Band 4 C */
	अणु 0x04B0, 0x1103 पूर्ण,    /* R1200 - AIF1 DAC2 EQ Band 4 PG */
	अणु 0x04B1, 0x0564 पूर्ण,    /* R1201 - AIF1 DAC2 EQ Band 5 A */
	अणु 0x04B2, 0x0559 पूर्ण,    /* R1202 - AIF1 DAC2 EQ Band 5 B */
	अणु 0x04B3, 0x4000 पूर्ण,    /* R1203 - AIF1 DAC2 EQ Band 5 PG */
	अणु 0x04B4, 0x0000 पूर्ण,    /* R1204 - AIF1 DAC2 EQ Band 1 C */
	अणु 0x0500, 0x00C0 पूर्ण,    /* R1280 - AIF2 ADC Left Volume */
	अणु 0x0501, 0x00C0 पूर्ण,    /* R1281 - AIF2 ADC Right Volume */
	अणु 0x0502, 0x00C0 पूर्ण,    /* R1282 - AIF2 DAC Left Volume */
	अणु 0x0503, 0x00C0 पूर्ण,    /* R1283 - AIF2 DAC Right Volume */
	अणु 0x0510, 0x0000 पूर्ण,    /* R1296 - AIF2 ADC Filters */
	अणु 0x0520, 0x0200 पूर्ण,    /* R1312 - AIF2 DAC Filters (1) */
	अणु 0x0521, 0x0010 पूर्ण,    /* R1313 - AIF2 DAC Filters (2) */
	अणु 0x0530, 0x0068 पूर्ण,    /* R1328 - AIF2 DAC Noise Gate */
	अणु 0x0540, 0x0098 पूर्ण,    /* R1344 - AIF2 DRC (1) */
	अणु 0x0541, 0x0845 पूर्ण,    /* R1345 - AIF2 DRC (2) */
	अणु 0x0542, 0x0000 पूर्ण,    /* R1346 - AIF2 DRC (3) */
	अणु 0x0543, 0x0000 पूर्ण,    /* R1347 - AIF2 DRC (4) */
	अणु 0x0544, 0x0000 पूर्ण,    /* R1348 - AIF2 DRC (5) */
	अणु 0x0580, 0x6318 पूर्ण,    /* R1408 - AIF2 EQ Gains (1) */
	अणु 0x0581, 0x6300 पूर्ण,    /* R1409 - AIF2 EQ Gains (2) */
	अणु 0x0582, 0x0FCA पूर्ण,    /* R1410 - AIF2 EQ Band 1 A */
	अणु 0x0583, 0x0400 पूर्ण,    /* R1411 - AIF2 EQ Band 1 B */
	अणु 0x0584, 0x00D8 पूर्ण,    /* R1412 - AIF2 EQ Band 1 PG */
	अणु 0x0585, 0x1EB5 पूर्ण,    /* R1413 - AIF2 EQ Band 2 A */
	अणु 0x0586, 0xF145 पूर्ण,    /* R1414 - AIF2 EQ Band 2 B */
	अणु 0x0587, 0x0B75 पूर्ण,    /* R1415 - AIF2 EQ Band 2 C */
	अणु 0x0588, 0x01C5 पूर्ण,    /* R1416 - AIF2 EQ Band 2 PG */
	अणु 0x0589, 0x1C58 पूर्ण,    /* R1417 - AIF2 EQ Band 3 A */
	अणु 0x058A, 0xF373 पूर्ण,    /* R1418 - AIF2 EQ Band 3 B */
	अणु 0x058B, 0x0A54 पूर्ण,    /* R1419 - AIF2 EQ Band 3 C */
	अणु 0x058C, 0x0558 पूर्ण,    /* R1420 - AIF2 EQ Band 3 PG */
	अणु 0x058D, 0x168E पूर्ण,    /* R1421 - AIF2 EQ Band 4 A */
	अणु 0x058E, 0xF829 पूर्ण,    /* R1422 - AIF2 EQ Band 4 B */
	अणु 0x058F, 0x07AD पूर्ण,    /* R1423 - AIF2 EQ Band 4 C */
	अणु 0x0590, 0x1103 पूर्ण,    /* R1424 - AIF2 EQ Band 4 PG */
	अणु 0x0591, 0x0564 पूर्ण,    /* R1425 - AIF2 EQ Band 5 A */
	अणु 0x0592, 0x0559 पूर्ण,    /* R1426 - AIF2 EQ Band 5 B */
	अणु 0x0593, 0x4000 पूर्ण,    /* R1427 - AIF2 EQ Band 5 PG */
	अणु 0x0594, 0x0000 पूर्ण,    /* R1428 - AIF2 EQ Band 1 C */
	अणु 0x0600, 0x0000 पूर्ण,    /* R1536 - DAC1 Mixer Volumes */
	अणु 0x0601, 0x0000 पूर्ण,    /* R1537 - DAC1 Left Mixer Routing */
	अणु 0x0602, 0x0000 पूर्ण,    /* R1538 - DAC1 Right Mixer Routing */
	अणु 0x0603, 0x0000 पूर्ण,    /* R1539 - AIF2ADC Mixer Volumes */
	अणु 0x0604, 0x0000 पूर्ण,    /* R1540 - AIF2ADC Left Mixer Routing */
	अणु 0x0605, 0x0000 पूर्ण,    /* R1541 - AIF2ADC Right Mixer Routing */
	अणु 0x0606, 0x0000 पूर्ण,    /* R1542 - AIF1 ADC1 Left Mixer Routing */
	अणु 0x0607, 0x0000 पूर्ण,    /* R1543 - AIF1 ADC1 Right Mixer Routing */
	अणु 0x0608, 0x0000 पूर्ण,    /* R1544 - AIF1 ADC2 Left Mixer Routing */
	अणु 0x0609, 0x0000 पूर्ण,    /* R1545 - AIF1 ADC2 Right Mixer Routing */
	अणु 0x0610, 0x02C0 पूर्ण,    /* R1552 - DAC1 Left Volume */
	अणु 0x0611, 0x02C0 पूर्ण,    /* R1553 - DAC1 Right Volume */
	अणु 0x0612, 0x02C0 पूर्ण,    /* R1554 - AIF2TX Left Volume */
	अणु 0x0613, 0x02C0 पूर्ण,    /* R1555 - AIF2TX Right Volume */
	अणु 0x0614, 0x0000 पूर्ण,    /* R1556 - DAC Sofपंचांगute */
	अणु 0x0620, 0x0002 पूर्ण,    /* R1568 - Oversampling */
	अणु 0x0621, 0x0000 पूर्ण,    /* R1569 - Sidetone */
	अणु 0x0700, 0x8100 पूर्ण,    /* R1792 - GPIO 1 */
	अणु 0x0701, 0xA101 पूर्ण,    /* R1793 - Pull Control (MCLK2) */
	अणु 0x0702, 0xA101 पूर्ण,    /* R1794 - Pull Control (BCLK2) */
	अणु 0x0703, 0xA101 पूर्ण,    /* R1795 - Pull Control (DACLRCLK2) */
	अणु 0x0704, 0xA101 पूर्ण,    /* R1796 - Pull Control (DACDAT2) */
	अणु 0x0707, 0xA101 पूर्ण,    /* R1799 - GPIO 8 */
	अणु 0x0708, 0xA101 पूर्ण,    /* R1800 - GPIO 9 */
	अणु 0x0709, 0xA101 पूर्ण,    /* R1801 - GPIO 10 */
	अणु 0x070A, 0xA101 पूर्ण,    /* R1802 - GPIO 11 */
	अणु 0x0720, 0x0000 पूर्ण,    /* R1824 - Pull Control (1) */
	अणु 0x0721, 0x0156 पूर्ण,    /* R1825 - Pull Control (2) */
	अणु 0x0732, 0x0000 पूर्ण,    /* R1842 - Interrupt Raw Status 2 */
	अणु 0x0738, 0x07FF पूर्ण,    /* R1848 - Interrupt Status 1 Mask */
	अणु 0x0739, 0xDFEF पूर्ण,    /* R1849 - Interrupt Status 2 Mask */
	अणु 0x0740, 0x0000 पूर्ण,    /* R1856 - Interrupt Control */
	अणु 0x0748, 0x003F पूर्ण,    /* R1864 - IRQ Debounce */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8994_शेषs[] = अणु
	अणु 0x0001, 0x0000 पूर्ण,    /* R1     - Power Management (1) */ 
	अणु 0x0002, 0x6000 पूर्ण,    /* R2     - Power Management (2) */ 
	अणु 0x0003, 0x0000 पूर्ण,    /* R3     - Power Management (3) */ 
	अणु 0x0004, 0x0000 पूर्ण,    /* R4     - Power Management (4) */ 
	अणु 0x0005, 0x0000 पूर्ण,    /* R5     - Power Management (5) */ 
	अणु 0x0006, 0x0000 पूर्ण,    /* R6     - Power Management (6) */ 
	अणु 0x0015, 0x0000 पूर्ण,    /* R21    - Input Mixer (1) */ 
	अणु 0x0018, 0x008B पूर्ण,    /* R24    - Left Line Input 1&2 Volume */ 
	अणु 0x0019, 0x008B पूर्ण,    /* R25    - Left Line Input 3&4 Volume */ 
	अणु 0x001A, 0x008B पूर्ण,    /* R26    - Right Line Input 1&2 Volume */ 
	अणु 0x001B, 0x008B पूर्ण,    /* R27    - Right Line Input 3&4 Volume */ 
	अणु 0x001C, 0x006D पूर्ण,    /* R28    - Left Output Volume */ 
	अणु 0x001D, 0x006D पूर्ण,    /* R29    - Right Output Volume */ 
	अणु 0x001E, 0x0066 पूर्ण,    /* R30    - Line Outमाला_दो Volume */ 
	अणु 0x001F, 0x0020 पूर्ण,    /* R31    - HPOUT2 Volume */ 
	अणु 0x0020, 0x0079 पूर्ण,    /* R32    - Left OPGA Volume */ 
	अणु 0x0021, 0x0079 पूर्ण,    /* R33    - Right OPGA Volume */ 
	अणु 0x0022, 0x0003 पूर्ण,    /* R34    - SPKMIXL Attenuation */ 
	अणु 0x0023, 0x0003 पूर्ण,    /* R35    - SPKMIXR Attenuation */ 
	अणु 0x0024, 0x0011 पूर्ण,    /* R36    - SPKOUT Mixers */ 
	अणु 0x0025, 0x0140 पूर्ण,    /* R37    - ClassD */ 
	अणु 0x0026, 0x0079 पूर्ण,    /* R38    - Speaker Volume Left */ 
	अणु 0x0027, 0x0079 पूर्ण,    /* R39    - Speaker Volume Right */ 
	अणु 0x0028, 0x0000 पूर्ण,    /* R40    - Input Mixer (2) */ 
	अणु 0x0029, 0x0000 पूर्ण,    /* R41    - Input Mixer (3) */ 
	अणु 0x002A, 0x0000 पूर्ण,    /* R42    - Input Mixer (4) */ 
	अणु 0x002B, 0x0000 पूर्ण,    /* R43    - Input Mixer (5) */ 
	अणु 0x002C, 0x0000 पूर्ण,    /* R44    - Input Mixer (6) */ 
	अणु 0x002D, 0x0000 पूर्ण,    /* R45    - Output Mixer (1) */ 
	अणु 0x002E, 0x0000 पूर्ण,    /* R46    - Output Mixer (2) */ 
	अणु 0x002F, 0x0000 पूर्ण,    /* R47    - Output Mixer (3) */ 
	अणु 0x0030, 0x0000 पूर्ण,    /* R48    - Output Mixer (4) */ 
	अणु 0x0031, 0x0000 पूर्ण,    /* R49    - Output Mixer (5) */ 
	अणु 0x0032, 0x0000 पूर्ण,    /* R50    - Output Mixer (6) */ 
	अणु 0x0033, 0x0000 पूर्ण,    /* R51    - HPOUT2 Mixer */ 
	अणु 0x0034, 0x0000 पूर्ण,    /* R52    - Line Mixer (1) */ 
	अणु 0x0035, 0x0000 पूर्ण,    /* R53    - Line Mixer (2) */ 
	अणु 0x0036, 0x0000 पूर्ण,    /* R54    - Speaker Mixer */ 
	अणु 0x0037, 0x0000 पूर्ण,    /* R55    - Additional Control */ 
	अणु 0x0038, 0x0000 पूर्ण,    /* R56    - AntiPOP (1) */ 
	अणु 0x0039, 0x0000 पूर्ण,    /* R57    - AntiPOP (2) */ 
	अणु 0x003A, 0x0000 पूर्ण,    /* R58    - MICBIAS */ 
	अणु 0x003B, 0x000D पूर्ण,    /* R59    - LDO 1 */ 
	अणु 0x003C, 0x0003 पूर्ण,    /* R60    - LDO 2 */ 
	अणु 0x004C, 0x1F25 पूर्ण,    /* R76    - Charge Pump (1) */ 
	अणु 0x0051, 0x0004 पूर्ण,    /* R81    - Class W (1) */ 
	अणु 0x0055, 0x054A पूर्ण,    /* R85    - DC Servo (2) */ 
	अणु 0x0057, 0x0000 पूर्ण,    /* R87    - DC Servo (4) */ 
	अणु 0x0060, 0x0000 पूर्ण,    /* R96    - Analogue HP (1) */ 
	अणु 0x0101, 0x8004 पूर्ण,    /* R257   - Control Interface */ 
	अणु 0x0110, 0x0000 पूर्ण,    /* R272   - Write Sequencer Ctrl (1) */ 
	अणु 0x0111, 0x0000 पूर्ण,    /* R273   - Write Sequencer Ctrl (2) */ 
	अणु 0x0200, 0x0000 पूर्ण,    /* R512   - AIF1 Clocking (1) */ 
	अणु 0x0201, 0x0000 पूर्ण,    /* R513   - AIF1 Clocking (2) */ 
	अणु 0x0204, 0x0000 पूर्ण,    /* R516   - AIF2 Clocking (1) */ 
	अणु 0x0205, 0x0000 पूर्ण,    /* R517   - AIF2 Clocking (2) */ 
	अणु 0x0208, 0x0000 पूर्ण,    /* R520   - Clocking (1) */ 
	अणु 0x0209, 0x0000 पूर्ण,    /* R521   - Clocking (2) */ 
	अणु 0x0210, 0x0083 पूर्ण,    /* R528   - AIF1 Rate */ 
	अणु 0x0211, 0x0083 पूर्ण,    /* R529   - AIF2 Rate */ 
	अणु 0x0220, 0x0000 पूर्ण,    /* R544   - FLL1 Control (1) */ 
	अणु 0x0221, 0x0000 पूर्ण,    /* R545   - FLL1 Control (2) */ 
	अणु 0x0222, 0x0000 पूर्ण,    /* R546   - FLL1 Control (3) */ 
	अणु 0x0223, 0x0000 पूर्ण,    /* R547   - FLL1 Control (4) */ 
	अणु 0x0224, 0x0C80 पूर्ण,    /* R548   - FLL1 Control (5) */ 
	अणु 0x0240, 0x0000 पूर्ण,    /* R576   - FLL2 Control (1) */ 
	अणु 0x0241, 0x0000 पूर्ण,    /* R577   - FLL2 Control (2) */ 
	अणु 0x0242, 0x0000 पूर्ण,    /* R578   - FLL2 Control (3) */ 
	अणु 0x0243, 0x0000 पूर्ण,    /* R579   - FLL2 Control (4) */ 
	अणु 0x0244, 0x0C80 पूर्ण,    /* R580   - FLL2 Control (5) */ 
	अणु 0x0300, 0x4050 पूर्ण,    /* R768   - AIF1 Control (1) */ 
	अणु 0x0301, 0x4000 पूर्ण,    /* R769   - AIF1 Control (2) */ 
	अणु 0x0302, 0x0000 पूर्ण,    /* R770   - AIF1 Master/Slave */ 
	अणु 0x0303, 0x0040 पूर्ण,    /* R771   - AIF1 BCLK */ 
	अणु 0x0304, 0x0040 पूर्ण,    /* R772   - AIF1ADC LRCLK */ 
	अणु 0x0305, 0x0040 पूर्ण,    /* R773   - AIF1DAC LRCLK */ 
	अणु 0x0306, 0x0004 पूर्ण,    /* R774   - AIF1DAC Data */ 
	अणु 0x0307, 0x0100 पूर्ण,    /* R775   - AIF1ADC Data */ 
	अणु 0x0310, 0x4050 पूर्ण,    /* R784   - AIF2 Control (1) */ 
	अणु 0x0311, 0x4000 पूर्ण,    /* R785   - AIF2 Control (2) */ 
	अणु 0x0312, 0x0000 पूर्ण,    /* R786   - AIF2 Master/Slave */ 
	अणु 0x0313, 0x0040 पूर्ण,    /* R787   - AIF2 BCLK */ 
	अणु 0x0314, 0x0040 पूर्ण,    /* R788   - AIF2ADC LRCLK */ 
	अणु 0x0315, 0x0040 पूर्ण,    /* R789   - AIF2DAC LRCLK */ 
	अणु 0x0316, 0x0000 पूर्ण,    /* R790   - AIF2DAC Data */ 
	अणु 0x0317, 0x0000 पूर्ण,    /* R791   - AIF2ADC Data */ 
	अणु 0x0400, 0x00C0 पूर्ण,    /* R1024  - AIF1 ADC1 Left Volume */ 
	अणु 0x0401, 0x00C0 पूर्ण,    /* R1025  - AIF1 ADC1 Right Volume */ 
	अणु 0x0402, 0x00C0 पूर्ण,    /* R1026  - AIF1 DAC1 Left Volume */ 
	अणु 0x0403, 0x00C0 पूर्ण,    /* R1027  - AIF1 DAC1 Right Volume */ 
	अणु 0x0404, 0x00C0 पूर्ण,    /* R1028  - AIF1 ADC2 Left Volume */ 
	अणु 0x0405, 0x00C0 पूर्ण,    /* R1029  - AIF1 ADC2 Right Volume */ 
	अणु 0x0406, 0x00C0 पूर्ण,    /* R1030  - AIF1 DAC2 Left Volume */ 
	अणु 0x0407, 0x00C0 पूर्ण,    /* R1031  - AIF1 DAC2 Right Volume */ 
	अणु 0x0410, 0x0000 पूर्ण,    /* R1040  - AIF1 ADC1 Filters */ 
	अणु 0x0411, 0x0000 पूर्ण,    /* R1041  - AIF1 ADC2 Filters */ 
	अणु 0x0420, 0x0200 पूर्ण,    /* R1056  - AIF1 DAC1 Filters (1) */ 
	अणु 0x0421, 0x0010 पूर्ण,    /* R1057  - AIF1 DAC1 Filters (2) */ 
	अणु 0x0422, 0x0200 पूर्ण,    /* R1058  - AIF1 DAC2 Filters (1) */ 
	अणु 0x0423, 0x0010 पूर्ण,    /* R1059  - AIF1 DAC2 Filters (2) */ 
	अणु 0x0440, 0x0098 पूर्ण,    /* R1088  - AIF1 DRC1 (1) */ 
	अणु 0x0441, 0x0845 पूर्ण,    /* R1089  - AIF1 DRC1 (2) */ 
	अणु 0x0442, 0x0000 पूर्ण,    /* R1090  - AIF1 DRC1 (3) */ 
	अणु 0x0443, 0x0000 पूर्ण,    /* R1091  - AIF1 DRC1 (4) */ 
	अणु 0x0444, 0x0000 पूर्ण,    /* R1092  - AIF1 DRC1 (5) */ 
	अणु 0x0450, 0x0098 पूर्ण,    /* R1104  - AIF1 DRC2 (1) */ 
	अणु 0x0451, 0x0845 पूर्ण,    /* R1105  - AIF1 DRC2 (2) */ 
	अणु 0x0452, 0x0000 पूर्ण,    /* R1106  - AIF1 DRC2 (3) */ 
	अणु 0x0453, 0x0000 पूर्ण,    /* R1107  - AIF1 DRC2 (4) */ 
	अणु 0x0454, 0x0000 पूर्ण,    /* R1108  - AIF1 DRC2 (5) */ 
	अणु 0x0480, 0x6318 पूर्ण,    /* R1152  - AIF1 DAC1 EQ Gains (1) */ 
	अणु 0x0481, 0x6300 पूर्ण,    /* R1153  - AIF1 DAC1 EQ Gains (2) */ 
	अणु 0x0482, 0x0FCA पूर्ण,    /* R1154  - AIF1 DAC1 EQ Band 1 A */ 
	अणु 0x0483, 0x0400 पूर्ण,    /* R1155  - AIF1 DAC1 EQ Band 1 B */ 
	अणु 0x0484, 0x00D8 पूर्ण,    /* R1156  - AIF1 DAC1 EQ Band 1 PG */ 
	अणु 0x0485, 0x1EB5 पूर्ण,    /* R1157  - AIF1 DAC1 EQ Band 2 A */ 
	अणु 0x0486, 0xF145 पूर्ण,    /* R1158  - AIF1 DAC1 EQ Band 2 B */ 
	अणु 0x0487, 0x0B75 पूर्ण,    /* R1159  - AIF1 DAC1 EQ Band 2 C */ 
	अणु 0x0488, 0x01C5 पूर्ण,    /* R1160  - AIF1 DAC1 EQ Band 2 PG */ 
	अणु 0x0489, 0x1C58 पूर्ण,    /* R1161  - AIF1 DAC1 EQ Band 3 A */ 
	अणु 0x048A, 0xF373 पूर्ण,    /* R1162  - AIF1 DAC1 EQ Band 3 B */ 
	अणु 0x048B, 0x0A54 पूर्ण,    /* R1163  - AIF1 DAC1 EQ Band 3 C */ 
	अणु 0x048C, 0x0558 पूर्ण,    /* R1164  - AIF1 DAC1 EQ Band 3 PG */ 
	अणु 0x048D, 0x168E पूर्ण,    /* R1165  - AIF1 DAC1 EQ Band 4 A */ 
	अणु 0x048E, 0xF829 पूर्ण,    /* R1166  - AIF1 DAC1 EQ Band 4 B */ 
	अणु 0x048F, 0x07AD पूर्ण,    /* R1167  - AIF1 DAC1 EQ Band 4 C */ 
	अणु 0x0490, 0x1103 पूर्ण,    /* R1168  - AIF1 DAC1 EQ Band 4 PG */ 
	अणु 0x0491, 0x0564 पूर्ण,    /* R1169  - AIF1 DAC1 EQ Band 5 A */ 
	अणु 0x0492, 0x0559 पूर्ण,    /* R1170  - AIF1 DAC1 EQ Band 5 B */ 
	अणु 0x0493, 0x4000 पूर्ण,    /* R1171  - AIF1 DAC1 EQ Band 5 PG */ 
	अणु 0x04A0, 0x6318 पूर्ण,    /* R1184  - AIF1 DAC2 EQ Gains (1) */ 
	अणु 0x04A1, 0x6300 पूर्ण,    /* R1185  - AIF1 DAC2 EQ Gains (2) */ 
	अणु 0x04A2, 0x0FCA पूर्ण,    /* R1186  - AIF1 DAC2 EQ Band 1 A */ 
	अणु 0x04A3, 0x0400 पूर्ण,    /* R1187  - AIF1 DAC2 EQ Band 1 B */ 
	अणु 0x04A4, 0x00D8 पूर्ण,    /* R1188  - AIF1 DAC2 EQ Band 1 PG */ 
	अणु 0x04A5, 0x1EB5 पूर्ण,    /* R1189  - AIF1 DAC2 EQ Band 2 A */ 
	अणु 0x04A6, 0xF145 पूर्ण,    /* R1190  - AIF1 DAC2 EQ Band 2 B */ 
	अणु 0x04A7, 0x0B75 पूर्ण,    /* R1191  - AIF1 DAC2 EQ Band 2 C */ 
	अणु 0x04A8, 0x01C5 पूर्ण,    /* R1192  - AIF1 DAC2 EQ Band 2 PG */ 
	अणु 0x04A9, 0x1C58 पूर्ण,    /* R1193  - AIF1 DAC2 EQ Band 3 A */ 
	अणु 0x04AA, 0xF373 पूर्ण,    /* R1194  - AIF1 DAC2 EQ Band 3 B */ 
	अणु 0x04AB, 0x0A54 पूर्ण,    /* R1195  - AIF1 DAC2 EQ Band 3 C */ 
	अणु 0x04AC, 0x0558 पूर्ण,    /* R1196  - AIF1 DAC2 EQ Band 3 PG */ 
	अणु 0x04AD, 0x168E पूर्ण,    /* R1197  - AIF1 DAC2 EQ Band 4 A */ 
	अणु 0x04AE, 0xF829 पूर्ण,    /* R1198  - AIF1 DAC2 EQ Band 4 B */ 
	अणु 0x04AF, 0x07AD पूर्ण,    /* R1199  - AIF1 DAC2 EQ Band 4 C */ 
	अणु 0x04B0, 0x1103 पूर्ण,    /* R1200  - AIF1 DAC2 EQ Band 4 PG */ 
	अणु 0x04B1, 0x0564 पूर्ण,    /* R1201  - AIF1 DAC2 EQ Band 5 A */ 
	अणु 0x04B2, 0x0559 पूर्ण,    /* R1202  - AIF1 DAC2 EQ Band 5 B */ 
	अणु 0x04B3, 0x4000 पूर्ण,    /* R1203  - AIF1 DAC2 EQ Band 5 PG */ 
	अणु 0x0500, 0x00C0 पूर्ण,    /* R1280  - AIF2 ADC Left Volume */ 
	अणु 0x0501, 0x00C0 पूर्ण,    /* R1281  - AIF2 ADC Right Volume */ 
	अणु 0x0502, 0x00C0 पूर्ण,    /* R1282  - AIF2 DAC Left Volume */ 
	अणु 0x0503, 0x00C0 पूर्ण,    /* R1283  - AIF2 DAC Right Volume */ 
	अणु 0x0510, 0x0000 पूर्ण,    /* R1296  - AIF2 ADC Filters */ 
	अणु 0x0520, 0x0200 पूर्ण,    /* R1312  - AIF2 DAC Filters (1) */ 
	अणु 0x0521, 0x0010 पूर्ण,    /* R1313  - AIF2 DAC Filters (2) */ 
	अणु 0x0540, 0x0098 पूर्ण,    /* R1344  - AIF2 DRC (1) */ 
	अणु 0x0541, 0x0845 पूर्ण,    /* R1345  - AIF2 DRC (2) */ 
	अणु 0x0542, 0x0000 पूर्ण,    /* R1346  - AIF2 DRC (3) */ 
	अणु 0x0543, 0x0000 पूर्ण,    /* R1347  - AIF2 DRC (4) */ 
	अणु 0x0544, 0x0000 पूर्ण,    /* R1348  - AIF2 DRC (5) */ 
	अणु 0x0580, 0x6318 पूर्ण,    /* R1408  - AIF2 EQ Gains (1) */ 
	अणु 0x0581, 0x6300 पूर्ण,    /* R1409  - AIF2 EQ Gains (2) */ 
	अणु 0x0582, 0x0FCA पूर्ण,    /* R1410  - AIF2 EQ Band 1 A */ 
	अणु 0x0583, 0x0400 पूर्ण,    /* R1411  - AIF2 EQ Band 1 B */ 
	अणु 0x0584, 0x00D8 पूर्ण,    /* R1412  - AIF2 EQ Band 1 PG */ 
	अणु 0x0585, 0x1EB5 पूर्ण,    /* R1413  - AIF2 EQ Band 2 A */ 
	अणु 0x0586, 0xF145 पूर्ण,    /* R1414  - AIF2 EQ Band 2 B */ 
	अणु 0x0587, 0x0B75 पूर्ण,    /* R1415  - AIF2 EQ Band 2 C */ 
	अणु 0x0588, 0x01C5 पूर्ण,    /* R1416  - AIF2 EQ Band 2 PG */ 
	अणु 0x0589, 0x1C58 पूर्ण,    /* R1417  - AIF2 EQ Band 3 A */ 
	अणु 0x058A, 0xF373 पूर्ण,    /* R1418  - AIF2 EQ Band 3 B */ 
	अणु 0x058B, 0x0A54 पूर्ण,    /* R1419  - AIF2 EQ Band 3 C */ 
	अणु 0x058C, 0x0558 पूर्ण,    /* R1420  - AIF2 EQ Band 3 PG */ 
	अणु 0x058D, 0x168E पूर्ण,    /* R1421  - AIF2 EQ Band 4 A */ 
	अणु 0x058E, 0xF829 पूर्ण,    /* R1422  - AIF2 EQ Band 4 B */ 
	अणु 0x058F, 0x07AD पूर्ण,    /* R1423  - AIF2 EQ Band 4 C */ 
	अणु 0x0590, 0x1103 पूर्ण,    /* R1424  - AIF2 EQ Band 4 PG */ 
	अणु 0x0591, 0x0564 पूर्ण,    /* R1425  - AIF2 EQ Band 5 A */ 
	अणु 0x0592, 0x0559 पूर्ण,    /* R1426  - AIF2 EQ Band 5 B */ 
	अणु 0x0593, 0x4000 पूर्ण,    /* R1427  - AIF2 EQ Band 5 PG */ 
	अणु 0x0600, 0x0000 पूर्ण,    /* R1536  - DAC1 Mixer Volumes */ 
	अणु 0x0601, 0x0000 पूर्ण,    /* R1537  - DAC1 Left Mixer Routing */ 
	अणु 0x0602, 0x0000 पूर्ण,    /* R1538  - DAC1 Right Mixer Routing */ 
	अणु 0x0603, 0x0000 पूर्ण,    /* R1539  - DAC2 Mixer Volumes */ 
	अणु 0x0604, 0x0000 पूर्ण,    /* R1540  - DAC2 Left Mixer Routing */ 
	अणु 0x0605, 0x0000 पूर्ण,    /* R1541  - DAC2 Right Mixer Routing */ 
	अणु 0x0606, 0x0000 पूर्ण,    /* R1542  - AIF1 ADC1 Left Mixer Routing */ 
	अणु 0x0607, 0x0000 पूर्ण,    /* R1543  - AIF1 ADC1 Right Mixer Routing */ 
	अणु 0x0608, 0x0000 पूर्ण,    /* R1544  - AIF1 ADC2 Left Mixer Routing */ 
	अणु 0x0609, 0x0000 पूर्ण,    /* R1545  - AIF1 ADC2 Right mixer Routing */ 
	अणु 0x0610, 0x02C0 पूर्ण,    /* R1552  - DAC1 Left Volume */ 
	अणु 0x0611, 0x02C0 पूर्ण,    /* R1553  - DAC1 Right Volume */ 
	अणु 0x0612, 0x02C0 पूर्ण,    /* R1554  - DAC2 Left Volume */ 
	अणु 0x0613, 0x02C0 पूर्ण,    /* R1555  - DAC2 Right Volume */ 
	अणु 0x0614, 0x0000 पूर्ण,    /* R1556  - DAC Sofपंचांगute */ 
	अणु 0x0620, 0x0002 पूर्ण,    /* R1568  - Oversampling */ 
	अणु 0x0621, 0x0000 पूर्ण,    /* R1569  - Sidetone */ 
	अणु 0x0700, 0x8100 पूर्ण,    /* R1792  - GPIO 1 */ 
	अणु 0x0701, 0xA101 पूर्ण,    /* R1793  - GPIO 2 */ 
	अणु 0x0702, 0xA101 पूर्ण,    /* R1794  - GPIO 3 */ 
	अणु 0x0703, 0xA101 पूर्ण,    /* R1795  - GPIO 4 */ 
	अणु 0x0704, 0xA101 पूर्ण,    /* R1796  - GPIO 5 */ 
	अणु 0x0705, 0xA101 पूर्ण,    /* R1797  - GPIO 6 */ 
	अणु 0x0706, 0xA101 पूर्ण,    /* R1798  - GPIO 7 */ 
	अणु 0x0707, 0xA101 पूर्ण,    /* R1799  - GPIO 8 */ 
	अणु 0x0708, 0xA101 पूर्ण,    /* R1800  - GPIO 9 */ 
	अणु 0x0709, 0xA101 पूर्ण,    /* R1801  - GPIO 10 */ 
	अणु 0x070A, 0xA101 पूर्ण,    /* R1802  - GPIO 11 */ 
	अणु 0x0720, 0x0000 पूर्ण,    /* R1824  - Pull Control (1) */ 
	अणु 0x0721, 0x0156 पूर्ण,    /* R1825  - Pull Control (2) */ 
	अणु 0x0738, 0x07FF पूर्ण,    /* R1848  - Interrupt Status 1 Mask */ 
	अणु 0x0739, 0xFFFF पूर्ण,    /* R1849  - Interrupt Status 2 Mask */ 
	अणु 0x0740, 0x0000 पूर्ण,    /* R1856  - Interrupt Control */ 
	अणु 0x0748, 0x003F पूर्ण,    /* R1864  - IRQ Debounce */ 
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8958_शेषs[] = अणु
	अणु 0x0001, 0x0000 पूर्ण,    /* R1     - Power Management (1) */
	अणु 0x0002, 0x6000 पूर्ण,    /* R2     - Power Management (2) */
	अणु 0x0003, 0x0000 पूर्ण,    /* R3     - Power Management (3) */
	अणु 0x0004, 0x0000 पूर्ण,    /* R4     - Power Management (4) */
	अणु 0x0005, 0x0000 पूर्ण,    /* R5     - Power Management (5) */
	अणु 0x0006, 0x0000 पूर्ण,    /* R6     - Power Management (6) */
	अणु 0x0015, 0x0000 पूर्ण,    /* R21    - Input Mixer (1) */
	अणु 0x0018, 0x008B पूर्ण,    /* R24    - Left Line Input 1&2 Volume */
	अणु 0x0019, 0x008B पूर्ण,    /* R25    - Left Line Input 3&4 Volume */
	अणु 0x001A, 0x008B पूर्ण,    /* R26    - Right Line Input 1&2 Volume */
	अणु 0x001B, 0x008B पूर्ण,    /* R27    - Right Line Input 3&4 Volume */
	अणु 0x001C, 0x006D पूर्ण,    /* R28    - Left Output Volume */
	अणु 0x001D, 0x006D पूर्ण,    /* R29    - Right Output Volume */
	अणु 0x001E, 0x0066 पूर्ण,    /* R30    - Line Outमाला_दो Volume */
	अणु 0x001F, 0x0020 पूर्ण,    /* R31    - HPOUT2 Volume */
	अणु 0x0020, 0x0079 पूर्ण,    /* R32    - Left OPGA Volume */
	अणु 0x0021, 0x0079 पूर्ण,    /* R33    - Right OPGA Volume */
	अणु 0x0022, 0x0003 पूर्ण,    /* R34    - SPKMIXL Attenuation */
	अणु 0x0023, 0x0003 पूर्ण,    /* R35    - SPKMIXR Attenuation */
	अणु 0x0024, 0x0011 पूर्ण,    /* R36    - SPKOUT Mixers */
	अणु 0x0025, 0x0140 पूर्ण,    /* R37    - ClassD */
	अणु 0x0026, 0x0079 पूर्ण,    /* R38    - Speaker Volume Left */
	अणु 0x0027, 0x0079 पूर्ण,    /* R39    - Speaker Volume Right */
	अणु 0x0028, 0x0000 पूर्ण,    /* R40    - Input Mixer (2) */
	अणु 0x0029, 0x0000 पूर्ण,    /* R41    - Input Mixer (3) */
	अणु 0x002A, 0x0000 पूर्ण,    /* R42    - Input Mixer (4) */
	अणु 0x002B, 0x0000 पूर्ण,    /* R43    - Input Mixer (5) */
	अणु 0x002C, 0x0000 पूर्ण,    /* R44    - Input Mixer (6) */
	अणु 0x002D, 0x0000 पूर्ण,    /* R45    - Output Mixer (1) */
	अणु 0x002E, 0x0000 पूर्ण,    /* R46    - Output Mixer (2) */
	अणु 0x002F, 0x0000 पूर्ण,    /* R47    - Output Mixer (3) */
	अणु 0x0030, 0x0000 पूर्ण,    /* R48    - Output Mixer (4) */
	अणु 0x0031, 0x0000 पूर्ण,    /* R49    - Output Mixer (5) */
	अणु 0x0032, 0x0000 पूर्ण,    /* R50    - Output Mixer (6) */
	अणु 0x0033, 0x0000 पूर्ण,    /* R51    - HPOUT2 Mixer */
	अणु 0x0034, 0x0000 पूर्ण,    /* R52    - Line Mixer (1) */
	अणु 0x0035, 0x0000 पूर्ण,    /* R53    - Line Mixer (2) */
	अणु 0x0036, 0x0000 पूर्ण,    /* R54    - Speaker Mixer */
	अणु 0x0037, 0x0000 पूर्ण,    /* R55    - Additional Control */
	अणु 0x0038, 0x0000 पूर्ण,    /* R56    - AntiPOP (1) */
	अणु 0x0039, 0x0180 पूर्ण,    /* R57    - AntiPOP (2) */
	अणु 0x003B, 0x000D पूर्ण,    /* R59    - LDO 1 */
	अणु 0x003C, 0x0005 पूर्ण,    /* R60    - LDO 2 */
	अणु 0x003D, 0x0039 पूर्ण,    /* R61    - MICBIAS1 */
	अणु 0x003E, 0x0039 पूर्ण,    /* R62    - MICBIAS2 */
	अणु 0x004C, 0x1F25 पूर्ण,    /* R76    - Charge Pump (1) */
	अणु 0x004D, 0xAB19 पूर्ण,    /* R77    - Charge Pump (2) */
	अणु 0x0051, 0x0004 पूर्ण,    /* R81    - Class W (1) */
	अणु 0x0055, 0x054A पूर्ण,    /* R85    - DC Servo (2) */
	अणु 0x0057, 0x0000 पूर्ण,    /* R87    - DC Servo (4) */
	अणु 0x0060, 0x0000 पूर्ण,    /* R96    - Analogue HP (1) */
	अणु 0x00C5, 0x0000 पूर्ण,    /* R197   - Class D Test (5) */
	अणु 0x00D0, 0x5600 पूर्ण,    /* R208   - Mic Detect 1 */
	अणु 0x00D1, 0x007F पूर्ण,    /* R209   - Mic Detect 2 */
	अणु 0x0101, 0x8004 पूर्ण,    /* R257   - Control Interface */
	अणु 0x0110, 0x0000 पूर्ण,    /* R272   - Write Sequencer Ctrl (1) */
	अणु 0x0111, 0x0000 पूर्ण,    /* R273   - Write Sequencer Ctrl (2) */
	अणु 0x0200, 0x0000 पूर्ण,    /* R512   - AIF1 Clocking (1) */
	अणु 0x0201, 0x0000 पूर्ण,    /* R513   - AIF1 Clocking (2) */
	अणु 0x0204, 0x0000 पूर्ण,    /* R516   - AIF2 Clocking (1) */
	अणु 0x0205, 0x0000 पूर्ण,    /* R517   - AIF2 Clocking (2) */
	अणु 0x0208, 0x0000 पूर्ण,    /* R520   - Clocking (1) */
	अणु 0x0209, 0x0000 पूर्ण,    /* R521   - Clocking (2) */
	अणु 0x0210, 0x0083 पूर्ण,    /* R528   - AIF1 Rate */
	अणु 0x0211, 0x0083 पूर्ण,    /* R529   - AIF2 Rate */
	अणु 0x0220, 0x0000 पूर्ण,    /* R544   - FLL1 Control (1) */
	अणु 0x0221, 0x0000 पूर्ण,    /* R545   - FLL1 Control (2) */
	अणु 0x0222, 0x0000 पूर्ण,    /* R546   - FLL1 Control (3) */
	अणु 0x0223, 0x0000 पूर्ण,    /* R547   - FLL1 Control (4) */
	अणु 0x0224, 0x0C80 पूर्ण,    /* R548   - FLL1 Control (5) */
	अणु 0x0226, 0x0000 पूर्ण,    /* R550   - FLL1 EFS 1 */
	अणु 0x0227, 0x0006 पूर्ण,    /* R551   - FLL1 EFS 2 */
	अणु 0x0240, 0x0000 पूर्ण,    /* R576   - FLL2Control (1) */
	अणु 0x0241, 0x0000 पूर्ण,    /* R577   - FLL2Control (2) */
	अणु 0x0242, 0x0000 पूर्ण,    /* R578   - FLL2Control (3) */
	अणु 0x0243, 0x0000 पूर्ण,    /* R579   - FLL2 Control (4) */
	अणु 0x0244, 0x0C80 पूर्ण,    /* R580   - FLL2Control (5) */
	अणु 0x0246, 0x0000 पूर्ण,    /* R582   - FLL2 EFS 1 */
	अणु 0x0247, 0x0006 पूर्ण,    /* R583   - FLL2 EFS 2 */
	अणु 0x0300, 0x4050 पूर्ण,    /* R768   - AIF1 Control (1) */
	अणु 0x0301, 0x4000 पूर्ण,    /* R769   - AIF1 Control (2) */
	अणु 0x0302, 0x0000 पूर्ण,    /* R770   - AIF1 Master/Slave */
	अणु 0x0303, 0x0040 पूर्ण,    /* R771   - AIF1 BCLK */
	अणु 0x0304, 0x0040 पूर्ण,    /* R772   - AIF1ADC LRCLK */
	अणु 0x0305, 0x0040 पूर्ण,    /* R773   - AIF1DAC LRCLK */
	अणु 0x0306, 0x0004 पूर्ण,    /* R774   - AIF1DAC Data */
	अणु 0x0307, 0x0100 पूर्ण,    /* R775   - AIF1ADC Data */
	अणु 0x0310, 0x4053 पूर्ण,    /* R784   - AIF2 Control (1) */
	अणु 0x0311, 0x4000 पूर्ण,    /* R785   - AIF2 Control (2) */
	अणु 0x0312, 0x0000 पूर्ण,    /* R786   - AIF2 Master/Slave */
	अणु 0x0313, 0x0040 पूर्ण,    /* R787   - AIF2 BCLK */
	अणु 0x0314, 0x0040 पूर्ण,    /* R788   - AIF2ADC LRCLK */
	अणु 0x0315, 0x0040 पूर्ण,    /* R789   - AIF2DAC LRCLK */
	अणु 0x0316, 0x0000 पूर्ण,    /* R790   - AIF2DAC Data */
	अणु 0x0317, 0x0000 पूर्ण,    /* R791   - AIF2ADC Data */
	अणु 0x0320, 0x0040 पूर्ण,    /* R800   - AIF3 Control (1) */
	अणु 0x0321, 0x0000 पूर्ण,    /* R801   - AIF3 Control (2) */
	अणु 0x0322, 0x0000 पूर्ण,    /* R802   - AIF3DAC Data */
	अणु 0x0323, 0x0000 पूर्ण,    /* R803   - AIF3ADC Data */
	अणु 0x0400, 0x00C0 पूर्ण,    /* R1024  - AIF1 ADC1 Left Volume */
	अणु 0x0401, 0x00C0 पूर्ण,    /* R1025  - AIF1 ADC1 Right Volume */
	अणु 0x0402, 0x00C0 पूर्ण,    /* R1026  - AIF1 DAC1 Left Volume */
	अणु 0x0403, 0x00C0 पूर्ण,    /* R1027  - AIF1 DAC1 Right Volume */
	अणु 0x0404, 0x00C0 पूर्ण,    /* R1028  - AIF1 ADC2 Left Volume */
	अणु 0x0405, 0x00C0 पूर्ण,    /* R1029  - AIF1 ADC2 Right Volume */
	अणु 0x0406, 0x00C0 पूर्ण,    /* R1030  - AIF1 DAC2 Left Volume */
	अणु 0x0407, 0x00C0 पूर्ण,    /* R1031  - AIF1 DAC2 Right Volume */
	अणु 0x0410, 0x0000 पूर्ण,    /* R1040  - AIF1 ADC1 Filters */
	अणु 0x0411, 0x0000 पूर्ण,    /* R1041  - AIF1 ADC2 Filters */
	अणु 0x0420, 0x0200 पूर्ण,    /* R1056  - AIF1 DAC1 Filters (1) */
	अणु 0x0421, 0x0010 पूर्ण,    /* R1057  - AIF1 DAC1 Filters (2) */
	अणु 0x0422, 0x0200 पूर्ण,    /* R1058  - AIF1 DAC2 Filters (1) */
	अणु 0x0423, 0x0010 पूर्ण,    /* R1059  - AIF1 DAC2 Filters (2) */
	अणु 0x0430, 0x0068 पूर्ण,    /* R1072  - AIF1 DAC1 Noise Gate */
	अणु 0x0431, 0x0068 पूर्ण,    /* R1073  - AIF1 DAC2 Noise Gate */
	अणु 0x0440, 0x0098 पूर्ण,    /* R1088  - AIF1 DRC1 (1) */
	अणु 0x0441, 0x0845 पूर्ण,    /* R1089  - AIF1 DRC1 (2) */
	अणु 0x0442, 0x0000 पूर्ण,    /* R1090  - AIF1 DRC1 (3) */
	अणु 0x0443, 0x0000 पूर्ण,    /* R1091  - AIF1 DRC1 (4) */
	अणु 0x0444, 0x0000 पूर्ण,    /* R1092  - AIF1 DRC1 (5) */
	अणु 0x0450, 0x0098 पूर्ण,    /* R1104  - AIF1 DRC2 (1) */
	अणु 0x0451, 0x0845 पूर्ण,    /* R1105  - AIF1 DRC2 (2) */
	अणु 0x0452, 0x0000 पूर्ण,    /* R1106  - AIF1 DRC2 (3) */
	अणु 0x0453, 0x0000 पूर्ण,    /* R1107  - AIF1 DRC2 (4) */
	अणु 0x0454, 0x0000 पूर्ण,    /* R1108  - AIF1 DRC2 (5) */
	अणु 0x0480, 0x6318 पूर्ण,    /* R1152  - AIF1 DAC1 EQ Gains (1) */
	अणु 0x0481, 0x6300 पूर्ण,    /* R1153  - AIF1 DAC1 EQ Gains (2) */
	अणु 0x0482, 0x0FCA पूर्ण,    /* R1154  - AIF1 DAC1 EQ Band 1 A */
	अणु 0x0483, 0x0400 पूर्ण,    /* R1155  - AIF1 DAC1 EQ Band 1 B */
	अणु 0x0484, 0x00D8 पूर्ण,    /* R1156  - AIF1 DAC1 EQ Band 1 PG */
	अणु 0x0485, 0x1EB5 पूर्ण,    /* R1157  - AIF1 DAC1 EQ Band 2 A */
	अणु 0x0486, 0xF145 पूर्ण,    /* R1158  - AIF1 DAC1 EQ Band 2 B */
	अणु 0x0487, 0x0B75 पूर्ण,    /* R1159  - AIF1 DAC1 EQ Band 2 C */
	अणु 0x0488, 0x01C5 पूर्ण,    /* R1160  - AIF1 DAC1 EQ Band 2 PG */
	अणु 0x0489, 0x1C58 पूर्ण,    /* R1161  - AIF1 DAC1 EQ Band 3 A */
	अणु 0x048A, 0xF373 पूर्ण,    /* R1162  - AIF1 DAC1 EQ Band 3 B */
	अणु 0x048B, 0x0A54 पूर्ण,    /* R1163  - AIF1 DAC1 EQ Band 3 C */
	अणु 0x048C, 0x0558 पूर्ण,    /* R1164  - AIF1 DAC1 EQ Band 3 PG */
	अणु 0x048D, 0x168E पूर्ण,    /* R1165  - AIF1 DAC1 EQ Band 4 A */
	अणु 0x048E, 0xF829 पूर्ण,    /* R1166  - AIF1 DAC1 EQ Band 4 B */
	अणु 0x048F, 0x07AD पूर्ण,    /* R1167  - AIF1 DAC1 EQ Band 4 C */
	अणु 0x0490, 0x1103 पूर्ण,    /* R1168  - AIF1 DAC1 EQ Band 4 PG */
	अणु 0x0491, 0x0564 पूर्ण,    /* R1169  - AIF1 DAC1 EQ Band 5 A */
	अणु 0x0492, 0x0559 पूर्ण,    /* R1170  - AIF1 DAC1 EQ Band 5 B */
	अणु 0x0493, 0x4000 पूर्ण,    /* R1171  - AIF1 DAC1 EQ Band 5 PG */
	अणु 0x0494, 0x0000 पूर्ण,    /* R1172  - AIF1 DAC1 EQ Band 1 C */
	अणु 0x04A0, 0x6318 पूर्ण,    /* R1184  - AIF1 DAC2 EQ Gains (1) */
	अणु 0x04A1, 0x6300 पूर्ण,    /* R1185  - AIF1 DAC2 EQ Gains (2) */
	अणु 0x04A2, 0x0FCA पूर्ण,    /* R1186  - AIF1 DAC2 EQ Band 1 A */
	अणु 0x04A3, 0x0400 पूर्ण,    /* R1187  - AIF1 DAC2 EQ Band 1 B */
	अणु 0x04A4, 0x00D8 पूर्ण,    /* R1188  - AIF1 DAC2 EQ Band 1 PG */
	अणु 0x04A5, 0x1EB5 पूर्ण,    /* R1189  - AIF1 DAC2 EQ Band 2 A */
	अणु 0x04A6, 0xF145 पूर्ण,    /* R1190  - AIF1 DAC2 EQ Band 2 B */
	अणु 0x04A7, 0x0B75 पूर्ण,    /* R1191  - AIF1 DAC2 EQ Band 2 C */
	अणु 0x04A8, 0x01C5 पूर्ण,    /* R1192  - AIF1 DAC2 EQ Band 2 PG */
	अणु 0x04A9, 0x1C58 पूर्ण,    /* R1193  - AIF1 DAC2 EQ Band 3 A */
	अणु 0x04AA, 0xF373 पूर्ण,    /* R1194  - AIF1 DAC2 EQ Band 3 B */
	अणु 0x04AB, 0x0A54 पूर्ण,    /* R1195  - AIF1 DAC2 EQ Band 3 C */
	अणु 0x04AC, 0x0558 पूर्ण,    /* R1196  - AIF1 DAC2 EQ Band 3 PG */
	अणु 0x04AD, 0x168E पूर्ण,    /* R1197  - AIF1 DAC2 EQ Band 4 A */
	अणु 0x04AE, 0xF829 पूर्ण,    /* R1198  - AIF1 DAC2 EQ Band 4 B */
	अणु 0x04AF, 0x07AD पूर्ण,    /* R1199  - AIF1 DAC2 EQ Band 4 C */
	अणु 0x04B0, 0x1103 पूर्ण,    /* R1200  - AIF1 DAC2 EQ Band 4 PG */
	अणु 0x04B1, 0x0564 पूर्ण,    /* R1201  - AIF1 DAC2 EQ Band 5 A */
	अणु 0x04B2, 0x0559 पूर्ण,    /* R1202  - AIF1 DAC2 EQ Band 5 B */
	अणु 0x04B3, 0x4000 पूर्ण,    /* R1203  - AIF1 DAC2 EQ Band 5 PG */
	अणु 0x04B4, 0x0000 पूर्ण,    /* R1204  - AIF1 DAC2EQ Band 1 C */
	अणु 0x0500, 0x00C0 पूर्ण,    /* R1280  - AIF2 ADC Left Volume */
	अणु 0x0501, 0x00C0 पूर्ण,    /* R1281  - AIF2 ADC Right Volume */
	अणु 0x0502, 0x00C0 पूर्ण,    /* R1282  - AIF2 DAC Left Volume */
	अणु 0x0503, 0x00C0 पूर्ण,    /* R1283  - AIF2 DAC Right Volume */
	अणु 0x0510, 0x0000 पूर्ण,    /* R1296  - AIF2 ADC Filters */
	अणु 0x0520, 0x0200 पूर्ण,    /* R1312  - AIF2 DAC Filters (1) */
	अणु 0x0521, 0x0010 पूर्ण,    /* R1313  - AIF2 DAC Filters (2) */
	अणु 0x0530, 0x0068 पूर्ण,    /* R1328  - AIF2 DAC Noise Gate */
	अणु 0x0540, 0x0098 पूर्ण,    /* R1344  - AIF2 DRC (1) */
	अणु 0x0541, 0x0845 पूर्ण,    /* R1345  - AIF2 DRC (2) */
	अणु 0x0542, 0x0000 पूर्ण,    /* R1346  - AIF2 DRC (3) */
	अणु 0x0543, 0x0000 पूर्ण,    /* R1347  - AIF2 DRC (4) */
	अणु 0x0544, 0x0000 पूर्ण,    /* R1348  - AIF2 DRC (5) */
	अणु 0x0580, 0x6318 पूर्ण,    /* R1408  - AIF2 EQ Gains (1) */
	अणु 0x0581, 0x6300 पूर्ण,    /* R1409  - AIF2 EQ Gains (2) */
	अणु 0x0582, 0x0FCA पूर्ण,    /* R1410  - AIF2 EQ Band 1 A */
	अणु 0x0583, 0x0400 पूर्ण,    /* R1411  - AIF2 EQ Band 1 B */
	अणु 0x0584, 0x00D8 पूर्ण,    /* R1412  - AIF2 EQ Band 1 PG */
	अणु 0x0585, 0x1EB5 पूर्ण,    /* R1413  - AIF2 EQ Band 2 A */
	अणु 0x0586, 0xF145 पूर्ण,    /* R1414  - AIF2 EQ Band 2 B */
	अणु 0x0587, 0x0B75 पूर्ण,    /* R1415  - AIF2 EQ Band 2 C */
	अणु 0x0588, 0x01C5 पूर्ण,    /* R1416  - AIF2 EQ Band 2 PG */
	अणु 0x0589, 0x1C58 पूर्ण,    /* R1417  - AIF2 EQ Band 3 A */
	अणु 0x058A, 0xF373 पूर्ण,    /* R1418  - AIF2 EQ Band 3 B */
	अणु 0x058B, 0x0A54 पूर्ण,    /* R1419  - AIF2 EQ Band 3 C */
	अणु 0x058C, 0x0558 पूर्ण,    /* R1420  - AIF2 EQ Band 3 PG */
	अणु 0x058D, 0x168E पूर्ण,    /* R1421  - AIF2 EQ Band 4 A */
	अणु 0x058E, 0xF829 पूर्ण,    /* R1422  - AIF2 EQ Band 4 B */
	अणु 0x058F, 0x07AD पूर्ण,    /* R1423  - AIF2 EQ Band 4 C */
	अणु 0x0590, 0x1103 पूर्ण,    /* R1424  - AIF2 EQ Band 4 PG */
	अणु 0x0591, 0x0564 पूर्ण,    /* R1425  - AIF2 EQ Band 5 A */
	अणु 0x0592, 0x0559 पूर्ण,    /* R1426  - AIF2 EQ Band 5 B */
	अणु 0x0593, 0x4000 पूर्ण,    /* R1427  - AIF2 EQ Band 5 PG */
	अणु 0x0594, 0x0000 पूर्ण,    /* R1428  - AIF2 EQ Band 1 C */
	अणु 0x0600, 0x0000 पूर्ण,    /* R1536  - DAC1 Mixer Volumes */
	अणु 0x0601, 0x0000 पूर्ण,    /* R1537  - DAC1 Left Mixer Routing */
	अणु 0x0602, 0x0000 पूर्ण,    /* R1538  - DAC1 Right Mixer Routing */
	अणु 0x0603, 0x0000 पूर्ण,    /* R1539  - DAC2 Mixer Volumes */
	अणु 0x0604, 0x0000 पूर्ण,    /* R1540  - DAC2 Left Mixer Routing */
	अणु 0x0605, 0x0000 पूर्ण,    /* R1541  - DAC2 Right Mixer Routing */
	अणु 0x0606, 0x0000 पूर्ण,    /* R1542  - AIF1 ADC1 Left Mixer Routing */
	अणु 0x0607, 0x0000 पूर्ण,    /* R1543  - AIF1 ADC1 Right Mixer Routing */
	अणु 0x0608, 0x0000 पूर्ण,    /* R1544  - AIF1 ADC2 Left Mixer Routing */
	अणु 0x0609, 0x0000 पूर्ण,    /* R1545  - AIF1 ADC2 Right mixer Routing */
	अणु 0x0610, 0x02C0 पूर्ण,    /* R1552  - DAC1 Left Volume */
	अणु 0x0611, 0x02C0 पूर्ण,    /* R1553  - DAC1 Right Volume */
	अणु 0x0612, 0x02C0 पूर्ण,    /* R1554  - DAC2 Left Volume */
	अणु 0x0613, 0x02C0 पूर्ण,    /* R1555  - DAC2 Right Volume */
	अणु 0x0614, 0x0000 पूर्ण,    /* R1556  - DAC Sofपंचांगute */
	अणु 0x0620, 0x0002 पूर्ण,    /* R1568  - Oversampling */
	अणु 0x0621, 0x0000 पूर्ण,    /* R1569  - Sidetone */
	अणु 0x0700, 0x8100 पूर्ण,    /* R1792  - GPIO 1 */
	अणु 0x0701, 0xA101 पूर्ण,    /* R1793  - Pull Control (MCLK2) */
	अणु 0x0702, 0xA101 पूर्ण,    /* R1794  - Pull Control (BCLK2) */
	अणु 0x0703, 0xA101 पूर्ण,    /* R1795  - Pull Control (DACLRCLK2) */
	अणु 0x0704, 0xA101 पूर्ण,    /* R1796  - Pull Control (DACDAT2) */
	अणु 0x0705, 0xA101 पूर्ण,    /* R1797  - GPIO 6 */
	अणु 0x0707, 0xA101 पूर्ण,    /* R1799  - GPIO 8 */
	अणु 0x0708, 0xA101 पूर्ण,    /* R1800  - GPIO 9 */
	अणु 0x0709, 0xA101 पूर्ण,    /* R1801  - GPIO 10 */
	अणु 0x070A, 0xA101 पूर्ण,    /* R1802  - GPIO 11 */
	अणु 0x0720, 0x0000 पूर्ण,    /* R1824  - Pull Control (1) */
	अणु 0x0721, 0x0156 पूर्ण,    /* R1825  - Pull Control (2) */
	अणु 0x0738, 0x07FF पूर्ण,    /* R1848  - Interrupt Status 1 Mask */
	अणु 0x0739, 0xFFEF पूर्ण,    /* R1849  - Interrupt Status 2 Mask */
	अणु 0x0740, 0x0000 पूर्ण,    /* R1856  - Interrupt Control */
	अणु 0x0748, 0x003F पूर्ण,    /* R1864  - IRQ Debounce */
	अणु 0x0900, 0x1C00 पूर्ण,    /* R2304  - DSP2_Program */
	अणु 0x0901, 0x0000 पूर्ण,    /* R2305  - DSP2_Config */
	अणु 0x0A0D, 0x0000 पूर्ण,    /* R2573  - DSP2_ExecControl */
	अणु 0x2400, 0x003F पूर्ण,    /* R9216  - MBC Band 1 K (1) */
	अणु 0x2401, 0x8BD8 पूर्ण,    /* R9217  - MBC Band 1 K (2) */
	अणु 0x2402, 0x0032 पूर्ण,    /* R9218  - MBC Band 1 N1 (1) */
	अणु 0x2403, 0xF52D पूर्ण,    /* R9219  - MBC Band 1 N1 (2) */
	अणु 0x2404, 0x0065 पूर्ण,    /* R9220  - MBC Band 1 N2 (1) */
	अणु 0x2405, 0xAC8C पूर्ण,    /* R9221  - MBC Band 1 N2 (2) */
	अणु 0x2406, 0x006B पूर्ण,    /* R9222  - MBC Band 1 N3 (1) */
	अणु 0x2407, 0xE087 पूर्ण,    /* R9223  - MBC Band 1 N3 (2) */
	अणु 0x2408, 0x0072 पूर्ण,    /* R9224  - MBC Band 1 N4 (1) */
	अणु 0x2409, 0x1483 पूर्ण,    /* R9225  - MBC Band 1 N4 (2) */
	अणु 0x240A, 0x0072 पूर्ण,    /* R9226  - MBC Band 1 N5 (1) */
	अणु 0x240B, 0x1483 पूर्ण,    /* R9227  - MBC Band 1 N5 (2) */
	अणु 0x240C, 0x0043 पूर्ण,    /* R9228  - MBC Band 1 X1 (1) */
	अणु 0x240D, 0x3525 पूर्ण,    /* R9229  - MBC Band 1 X1 (2) */
	अणु 0x240E, 0x0006 पूर्ण,    /* R9230  - MBC Band 1 X2 (1) */
	अणु 0x240F, 0x6A4A पूर्ण,    /* R9231  - MBC Band 1 X2 (2) */
	अणु 0x2410, 0x0043 पूर्ण,    /* R9232  - MBC Band 1 X3 (1) */
	अणु 0x2411, 0x6079 पूर्ण,    /* R9233  - MBC Band 1 X3 (2) */
	अणु 0x2412, 0x000C पूर्ण,    /* R9234  - MBC Band 1 Attack (1) */
	अणु 0x2413, 0xCCCD पूर्ण,    /* R9235  - MBC Band 1 Attack (2) */
	अणु 0x2414, 0x0000 पूर्ण,    /* R9236  - MBC Band 1 Decay (1) */
	अणु 0x2415, 0x0800 पूर्ण,    /* R9237  - MBC Band 1 Decay (2) */
	अणु 0x2416, 0x003F पूर्ण,    /* R9238  - MBC Band 2 K (1) */
	अणु 0x2417, 0x8BD8 पूर्ण,    /* R9239  - MBC Band 2 K (2) */
	अणु 0x2418, 0x0032 पूर्ण,    /* R9240  - MBC Band 2 N1 (1) */
	अणु 0x2419, 0xF52D पूर्ण,    /* R9241  - MBC Band 2 N1 (2) */
	अणु 0x241A, 0x0065 पूर्ण,    /* R9242  - MBC Band 2 N2 (1) */
	अणु 0x241B, 0xAC8C पूर्ण,    /* R9243  - MBC Band 2 N2 (2) */
	अणु 0x241C, 0x006B पूर्ण,    /* R9244  - MBC Band 2 N3 (1) */
	अणु 0x241D, 0xE087 पूर्ण,    /* R9245  - MBC Band 2 N3 (2) */
	अणु 0x241E, 0x0072 पूर्ण,    /* R9246  - MBC Band 2 N4 (1) */
	अणु 0x241F, 0x1483 पूर्ण,    /* R9247  - MBC Band 2 N4 (2) */
	अणु 0x2420, 0x0072 पूर्ण,    /* R9248  - MBC Band 2 N5 (1) */
	अणु 0x2421, 0x1483 पूर्ण,    /* R9249  - MBC Band 2 N5 (2) */
	अणु 0x2422, 0x0043 पूर्ण,    /* R9250  - MBC Band 2 X1 (1) */
	अणु 0x2423, 0x3525 पूर्ण,    /* R9251  - MBC Band 2 X1 (2) */
	अणु 0x2424, 0x0006 पूर्ण,    /* R9252  - MBC Band 2 X2 (1) */
	अणु 0x2425, 0x6A4A पूर्ण,    /* R9253  - MBC Band 2 X2 (2) */
	अणु 0x2426, 0x0043 पूर्ण,    /* R9254  - MBC Band 2 X3 (1) */
	अणु 0x2427, 0x6079 पूर्ण,    /* R9255  - MBC Band 2 X3 (2) */
	अणु 0x2428, 0x000C पूर्ण,    /* R9256  - MBC Band 2 Attack (1) */
	अणु 0x2429, 0xCCCD पूर्ण,    /* R9257  - MBC Band 2 Attack (2) */
	अणु 0x242A, 0x0000 पूर्ण,    /* R9258  - MBC Band 2 Decay (1) */
	अणु 0x242B, 0x0800 पूर्ण,    /* R9259  - MBC Band 2 Decay (2) */
	अणु 0x242C, 0x005A पूर्ण,    /* R9260  - MBC_B2_PG2 (1) */
	अणु 0x242D, 0x7EFA पूर्ण,    /* R9261  - MBC_B2_PG2 (2) */
	अणु 0x242E, 0x005A पूर्ण,    /* R9262  - MBC_B1_PG2 (1) */
	अणु 0x242F, 0x7EFA पूर्ण,    /* R9263  - MBC_B1_PG2 (2) */
	अणु 0x2600, 0x00A7 पूर्ण,    /* R9728  - MBC Crossover (1) */
	अणु 0x2601, 0x0D1C पूर्ण,    /* R9729  - MBC Crossover (2) */
	अणु 0x2602, 0x0083 पूर्ण,    /* R9730  - MBC HPF (1) */
	अणु 0x2603, 0x98AD पूर्ण,    /* R9731  - MBC HPF (2) */
	अणु 0x2606, 0x0008 पूर्ण,    /* R9734  - MBC LPF (1) */
	अणु 0x2607, 0xE7A2 पूर्ण,    /* R9735  - MBC LPF (2) */
	अणु 0x260A, 0x0055 पूर्ण,    /* R9738  - MBC RMS Limit (1) */
	अणु 0x260B, 0x8C4B पूर्ण,    /* R9739  - MBC RMS Limit (2) */
पूर्ण;

अटल bool wm1811_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8994_SOFTWARE_RESET:
	हाल WM8994_POWER_MANAGEMENT_1:
	हाल WM8994_POWER_MANAGEMENT_2:
	हाल WM8994_POWER_MANAGEMENT_3:
	हाल WM8994_POWER_MANAGEMENT_4:
	हाल WM8994_POWER_MANAGEMENT_5:
	हाल WM8994_POWER_MANAGEMENT_6:
	हाल WM8994_INPUT_MIXER_1:
	हाल WM8994_LEFT_LINE_INPUT_1_2_VOLUME:
	हाल WM8994_LEFT_LINE_INPUT_3_4_VOLUME:
	हाल WM8994_RIGHT_LINE_INPUT_1_2_VOLUME:
	हाल WM8994_RIGHT_LINE_INPUT_3_4_VOLUME:
	हाल WM8994_LEFT_OUTPUT_VOLUME:
	हाल WM8994_RIGHT_OUTPUT_VOLUME:
	हाल WM8994_LINE_OUTPUTS_VOLUME:
	हाल WM8994_HPOUT2_VOLUME:
	हाल WM8994_LEFT_OPGA_VOLUME:
	हाल WM8994_RIGHT_OPGA_VOLUME:
	हाल WM8994_SPKMIXL_ATTENUATION:
	हाल WM8994_SPKMIXR_ATTENUATION:
	हाल WM8994_SPKOUT_MIXERS:
	हाल WM8994_CLASSD:
	हाल WM8994_SPEAKER_VOLUME_LEFT:
	हाल WM8994_SPEAKER_VOLUME_RIGHT:
	हाल WM8994_INPUT_MIXER_2:
	हाल WM8994_INPUT_MIXER_3:
	हाल WM8994_INPUT_MIXER_4:
	हाल WM8994_INPUT_MIXER_5:
	हाल WM8994_INPUT_MIXER_6:
	हाल WM8994_OUTPUT_MIXER_1:
	हाल WM8994_OUTPUT_MIXER_2:
	हाल WM8994_OUTPUT_MIXER_3:
	हाल WM8994_OUTPUT_MIXER_4:
	हाल WM8994_OUTPUT_MIXER_5:
	हाल WM8994_OUTPUT_MIXER_6:
	हाल WM8994_HPOUT2_MIXER:
	हाल WM8994_LINE_MIXER_1:
	हाल WM8994_LINE_MIXER_2:
	हाल WM8994_SPEAKER_MIXER:
	हाल WM8994_ADDITIONAL_CONTROL:
	हाल WM8994_ANTIPOP_1:
	हाल WM8994_ANTIPOP_2:
	हाल WM8994_LDO_1:
	हाल WM8994_LDO_2:
	हाल WM8958_MICBIAS1:
	हाल WM8958_MICBIAS2:
	हाल WM8994_CHARGE_PUMP_1:
	हाल WM8958_CHARGE_PUMP_2:
	हाल WM8994_CLASS_W_1:
	हाल WM8994_DC_SERVO_1:
	हाल WM8994_DC_SERVO_2:
	हाल WM8994_DC_SERVO_READBACK:
	हाल WM8994_DC_SERVO_4:
	हाल WM8994_DC_SERVO_4E:
	हाल WM8994_ANALOGUE_HP_1:
	हाल WM8958_MIC_DETECT_1:
	हाल WM8958_MIC_DETECT_2:
	हाल WM8958_MIC_DETECT_3:
	हाल WM8994_CHIP_REVISION:
	हाल WM8994_CONTROL_INTERFACE:
	हाल WM8994_AIF1_CLOCKING_1:
	हाल WM8994_AIF1_CLOCKING_2:
	हाल WM8994_AIF2_CLOCKING_1:
	हाल WM8994_AIF2_CLOCKING_2:
	हाल WM8994_CLOCKING_1:
	हाल WM8994_CLOCKING_2:
	हाल WM8994_AIF1_RATE:
	हाल WM8994_AIF2_RATE:
	हाल WM8994_RATE_STATUS:
	हाल WM8994_FLL1_CONTROL_1:
	हाल WM8994_FLL1_CONTROL_2:
	हाल WM8994_FLL1_CONTROL_3:
	हाल WM8994_FLL1_CONTROL_4:
	हाल WM8994_FLL1_CONTROL_5:
	हाल WM8958_FLL1_EFS_1:
	हाल WM8958_FLL1_EFS_2:
	हाल WM8994_FLL2_CONTROL_1:
	हाल WM8994_FLL2_CONTROL_2:
	हाल WM8994_FLL2_CONTROL_3:
	हाल WM8994_FLL2_CONTROL_4:
	हाल WM8994_FLL2_CONTROL_5:
	हाल WM8958_FLL2_EFS_1:
	हाल WM8958_FLL2_EFS_2:
	हाल WM8994_AIF1_CONTROL_1:
	हाल WM8994_AIF1_CONTROL_2:
	हाल WM8994_AIF1_MASTER_SLAVE:
	हाल WM8994_AIF1_BCLK:
	हाल WM8994_AIF1ADC_LRCLK:
	हाल WM8994_AIF1DAC_LRCLK:
	हाल WM8994_AIF1DAC_DATA:
	हाल WM8994_AIF1ADC_DATA:
	हाल WM8994_AIF2_CONTROL_1:
	हाल WM8994_AIF2_CONTROL_2:
	हाल WM8994_AIF2_MASTER_SLAVE:
	हाल WM8994_AIF2_BCLK:
	हाल WM8994_AIF2ADC_LRCLK:
	हाल WM8994_AIF2DAC_LRCLK:
	हाल WM8994_AIF2DAC_DATA:
	हाल WM8994_AIF2ADC_DATA:
	हाल WM1811_AIF2TX_CONTROL:
	हाल WM8958_AIF3_CONTROL_1:
	हाल WM8958_AIF3_CONTROL_2:
	हाल WM8958_AIF3DAC_DATA:
	हाल WM8958_AIF3ADC_DATA:
	हाल WM8994_AIF1_ADC1_LEFT_VOLUME:
	हाल WM8994_AIF1_ADC1_RIGHT_VOLUME:
	हाल WM8994_AIF1_DAC1_LEFT_VOLUME:
	हाल WM8994_AIF1_DAC1_RIGHT_VOLUME:
	हाल WM8994_AIF1_ADC1_FILTERS:
	हाल WM8994_AIF1_ADC2_FILTERS:
	हाल WM8994_AIF1_DAC1_FILTERS_1:
	हाल WM8994_AIF1_DAC1_FILTERS_2:
	हाल WM8994_AIF1_DAC2_FILTERS_1:
	हाल WM8994_AIF1_DAC2_FILTERS_2:
	हाल WM8958_AIF1_DAC1_NOISE_GATE:
	हाल WM8958_AIF1_DAC2_NOISE_GATE:
	हाल WM8994_AIF1_DRC1_1:
	हाल WM8994_AIF1_DRC1_2:
	हाल WM8994_AIF1_DRC1_3:
	हाल WM8994_AIF1_DRC1_4:
	हाल WM8994_AIF1_DRC1_5:
	हाल WM8994_AIF1_DRC2_1:
	हाल WM8994_AIF1_DRC2_2:
	हाल WM8994_AIF1_DRC2_3:
	हाल WM8994_AIF1_DRC2_4:
	हाल WM8994_AIF1_DRC2_5:
	हाल WM8994_AIF1_DAC1_EQ_GAINS_1:
	हाल WM8994_AIF1_DAC1_EQ_GAINS_2:
	हाल WM8994_AIF1_DAC1_EQ_BAND_1_A:
	हाल WM8994_AIF1_DAC1_EQ_BAND_1_B:
	हाल WM8994_AIF1_DAC1_EQ_BAND_1_PG:
	हाल WM8994_AIF1_DAC1_EQ_BAND_2_A:
	हाल WM8994_AIF1_DAC1_EQ_BAND_2_B:
	हाल WM8994_AIF1_DAC1_EQ_BAND_2_C:
	हाल WM8994_AIF1_DAC1_EQ_BAND_2_PG:
	हाल WM8994_AIF1_DAC1_EQ_BAND_3_A:
	हाल WM8994_AIF1_DAC1_EQ_BAND_3_B:
	हाल WM8994_AIF1_DAC1_EQ_BAND_3_C:
	हाल WM8994_AIF1_DAC1_EQ_BAND_3_PG:
	हाल WM8994_AIF1_DAC1_EQ_BAND_4_A:
	हाल WM8994_AIF1_DAC1_EQ_BAND_4_B:
	हाल WM8994_AIF1_DAC1_EQ_BAND_4_C:
	हाल WM8994_AIF1_DAC1_EQ_BAND_4_PG:
	हाल WM8994_AIF1_DAC1_EQ_BAND_5_A:
	हाल WM8994_AIF1_DAC1_EQ_BAND_5_B:
	हाल WM8994_AIF1_DAC1_EQ_BAND_5_PG:
	हाल WM8994_AIF1_DAC1_EQ_BAND_1_C:
	हाल WM8994_AIF1_DAC2_EQ_GAINS_1:
	हाल WM8994_AIF1_DAC2_EQ_GAINS_2:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_C:
	हाल WM8994_AIF2_ADC_LEFT_VOLUME:
	हाल WM8994_AIF2_ADC_RIGHT_VOLUME:
	हाल WM8994_AIF2_DAC_LEFT_VOLUME:
	हाल WM8994_AIF2_DAC_RIGHT_VOLUME:
	हाल WM8994_AIF2_ADC_FILTERS:
	हाल WM8994_AIF2_DAC_FILTERS_1:
	हाल WM8994_AIF2_DAC_FILTERS_2:
	हाल WM8958_AIF2_DAC_NOISE_GATE:
	हाल WM8994_AIF2_DRC_1:
	हाल WM8994_AIF2_DRC_2:
	हाल WM8994_AIF2_DRC_3:
	हाल WM8994_AIF2_DRC_4:
	हाल WM8994_AIF2_DRC_5:
	हाल WM8994_AIF2_EQ_GAINS_1:
	हाल WM8994_AIF2_EQ_GAINS_2:
	हाल WM8994_AIF2_EQ_BAND_1_A:
	हाल WM8994_AIF2_EQ_BAND_1_B:
	हाल WM8994_AIF2_EQ_BAND_1_PG:
	हाल WM8994_AIF2_EQ_BAND_2_A:
	हाल WM8994_AIF2_EQ_BAND_2_B:
	हाल WM8994_AIF2_EQ_BAND_2_C:
	हाल WM8994_AIF2_EQ_BAND_2_PG:
	हाल WM8994_AIF2_EQ_BAND_3_A:
	हाल WM8994_AIF2_EQ_BAND_3_B:
	हाल WM8994_AIF2_EQ_BAND_3_C:
	हाल WM8994_AIF2_EQ_BAND_3_PG:
	हाल WM8994_AIF2_EQ_BAND_4_A:
	हाल WM8994_AIF2_EQ_BAND_4_B:
	हाल WM8994_AIF2_EQ_BAND_4_C:
	हाल WM8994_AIF2_EQ_BAND_4_PG:
	हाल WM8994_AIF2_EQ_BAND_5_A:
	हाल WM8994_AIF2_EQ_BAND_5_B:
	हाल WM8994_AIF2_EQ_BAND_5_PG:
	हाल WM8994_AIF2_EQ_BAND_1_C:
	हाल WM8994_DAC1_MIXER_VOLUMES:
	हाल WM8994_DAC1_LEFT_MIXER_ROUTING:
	हाल WM8994_DAC1_RIGHT_MIXER_ROUTING:
	हाल WM8994_DAC2_MIXER_VOLUMES:
	हाल WM8994_DAC2_LEFT_MIXER_ROUTING:
	हाल WM8994_DAC2_RIGHT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC1_LEFT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC1_RIGHT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC2_LEFT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC2_RIGHT_MIXER_ROUTING:
	हाल WM8994_DAC1_LEFT_VOLUME:
	हाल WM8994_DAC1_RIGHT_VOLUME:
	हाल WM8994_DAC2_LEFT_VOLUME:
	हाल WM8994_DAC2_RIGHT_VOLUME:
	हाल WM8994_DAC_SOFTMUTE:
	हाल WM8994_OVERSAMPLING:
	हाल WM8994_SIDETONE:
	हाल WM8994_GPIO_1:
	हाल WM8994_GPIO_2:
	हाल WM8994_GPIO_3:
	हाल WM8994_GPIO_4:
	हाल WM8994_GPIO_5:
	हाल WM8994_GPIO_6:
	हाल WM8994_GPIO_8:
	हाल WM8994_GPIO_9:
	हाल WM8994_GPIO_10:
	हाल WM8994_GPIO_11:
	हाल WM8994_PULL_CONTROL_1:
	हाल WM8994_PULL_CONTROL_2:
	हाल WM8994_INTERRUPT_STATUS_1:
	हाल WM8994_INTERRUPT_STATUS_2:
	हाल WM8994_INTERRUPT_RAW_STATUS_2:
	हाल WM8994_INTERRUPT_STATUS_1_MASK:
	हाल WM8994_INTERRUPT_STATUS_2_MASK:
	हाल WM8994_INTERRUPT_CONTROL:
	हाल WM8994_IRQ_DEBOUNCE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8994_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8994_DC_SERVO_READBACK:
	हाल WM8994_MICBIAS:
	हाल WM8994_WRITE_SEQUENCER_CTRL_1:
	हाल WM8994_WRITE_SEQUENCER_CTRL_2:
	हाल WM8994_AIF1_ADC2_LEFT_VOLUME:
	हाल WM8994_AIF1_ADC2_RIGHT_VOLUME:
	हाल WM8994_AIF1_DAC2_LEFT_VOLUME:
	हाल WM8994_AIF1_DAC2_RIGHT_VOLUME:
	हाल WM8994_AIF1_ADC2_FILTERS:
	हाल WM8994_AIF1_DAC2_FILTERS_1:
	हाल WM8994_AIF1_DAC2_FILTERS_2:
	हाल WM8958_AIF1_DAC2_NOISE_GATE:
	हाल WM8994_AIF1_DRC2_1:
	हाल WM8994_AIF1_DRC2_2:
	हाल WM8994_AIF1_DRC2_3:
	हाल WM8994_AIF1_DRC2_4:
	हाल WM8994_AIF1_DRC2_5:
	हाल WM8994_AIF1_DAC2_EQ_GAINS_1:
	हाल WM8994_AIF1_DAC2_EQ_GAINS_2:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_2_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_3_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_C:
	हाल WM8994_AIF1_DAC2_EQ_BAND_4_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_A:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_B:
	हाल WM8994_AIF1_DAC2_EQ_BAND_5_PG:
	हाल WM8994_AIF1_DAC2_EQ_BAND_1_C:
	हाल WM8994_DAC2_MIXER_VOLUMES:
	हाल WM8994_DAC2_LEFT_MIXER_ROUTING:
	हाल WM8994_DAC2_RIGHT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC2_LEFT_MIXER_ROUTING:
	हाल WM8994_AIF1_ADC2_RIGHT_MIXER_ROUTING:
	हाल WM8994_DAC2_LEFT_VOLUME:
	हाल WM8994_DAC2_RIGHT_VOLUME:
		वापस true;
	शेष:
		वापस wm1811_पढ़ोable_रेजिस्टर(dev, reg);
	पूर्ण
पूर्ण

अटल bool wm8958_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8958_DSP2_PROGRAM:
	हाल WM8958_DSP2_CONFIG:
	हाल WM8958_DSP2_MAGICNUM:
	हाल WM8958_DSP2_RELEASEYEAR:
	हाल WM8958_DSP2_RELEASEMONTHDAY:
	हाल WM8958_DSP2_RELEASETIME:
	हाल WM8958_DSP2_VERMAJMIN:
	हाल WM8958_DSP2_VERBUILD:
	हाल WM8958_DSP2_TESTREG:
	हाल WM8958_DSP2_XORREG:
	हाल WM8958_DSP2_SHIFTMAXX:
	हाल WM8958_DSP2_SHIFTMAXY:
	हाल WM8958_DSP2_SHIFTMAXZ:
	हाल WM8958_DSP2_SHIFTMAXEXTLO:
	हाल WM8958_DSP2_AESSELECT:
	हाल WM8958_DSP2_EXECCONTROL:
	हाल WM8958_DSP2_SAMPLEBREAK:
	हाल WM8958_DSP2_COUNTBREAK:
	हाल WM8958_DSP2_INTSTATUS:
	हाल WM8958_DSP2_EVENTSTATUS:
	हाल WM8958_DSP2_INTMASK:
	हाल WM8958_DSP2_CONFIGDWIDTH:
	हाल WM8958_DSP2_CONFIGINSTR:
	हाल WM8958_DSP2_CONFIGDMEM:
	हाल WM8958_DSP2_CONFIGDELAYS:
	हाल WM8958_DSP2_CONFIGNUMIO:
	हाल WM8958_DSP2_CONFIGEXTDEPTH:
	हाल WM8958_DSP2_CONFIGMULTIPLIER:
	हाल WM8958_DSP2_CONFIGCTRLDWIDTH:
	हाल WM8958_DSP2_CONFIGPIPELINE:
	हाल WM8958_DSP2_SHIFTMAXEXTHI:
	हाल WM8958_DSP2_SWVERSIONREG:
	हाल WM8958_DSP2_CONFIGXMEM:
	हाल WM8958_DSP2_CONFIGYMEM:
	हाल WM8958_DSP2_CONFIGZMEM:
	हाल WM8958_FW_BUILD_1:
	हाल WM8958_FW_BUILD_0:
	हाल WM8958_FW_ID_1:
	हाल WM8958_FW_ID_0:
	हाल WM8958_FW_MAJOR_1:
	हाल WM8958_FW_MAJOR_0:
	हाल WM8958_FW_MINOR_1:
	हाल WM8958_FW_MINOR_0:
	हाल WM8958_FW_PATCH_1:
	हाल WM8958_FW_PATCH_0:
	हाल WM8958_MBC_BAND_1_K_1:
	हाल WM8958_MBC_BAND_1_K_2:
	हाल WM8958_MBC_BAND_1_N1_1:
	हाल WM8958_MBC_BAND_1_N1_2:
	हाल WM8958_MBC_BAND_1_N2_1:
	हाल WM8958_MBC_BAND_1_N2_2:
	हाल WM8958_MBC_BAND_1_N3_1:
	हाल WM8958_MBC_BAND_1_N3_2:
	हाल WM8958_MBC_BAND_1_N4_1:
	हाल WM8958_MBC_BAND_1_N4_2:
	हाल WM8958_MBC_BAND_1_N5_1:
	हाल WM8958_MBC_BAND_1_N5_2:
	हाल WM8958_MBC_BAND_1_X1_1:
	हाल WM8958_MBC_BAND_1_X1_2:
	हाल WM8958_MBC_BAND_1_X2_1:
	हाल WM8958_MBC_BAND_1_X2_2:
	हाल WM8958_MBC_BAND_1_X3_1:
	हाल WM8958_MBC_BAND_1_X3_2:
	हाल WM8958_MBC_BAND_1_ATTACK_1:
	हाल WM8958_MBC_BAND_1_ATTACK_2:
	हाल WM8958_MBC_BAND_1_DECAY_1:
	हाल WM8958_MBC_BAND_1_DECAY_2:
	हाल WM8958_MBC_BAND_2_K_1:
	हाल WM8958_MBC_BAND_2_K_2:
	हाल WM8958_MBC_BAND_2_N1_1:
	हाल WM8958_MBC_BAND_2_N1_2:
	हाल WM8958_MBC_BAND_2_N2_1:
	हाल WM8958_MBC_BAND_2_N2_2:
	हाल WM8958_MBC_BAND_2_N3_1:
	हाल WM8958_MBC_BAND_2_N3_2:
	हाल WM8958_MBC_BAND_2_N4_1:
	हाल WM8958_MBC_BAND_2_N4_2:
	हाल WM8958_MBC_BAND_2_N5_1:
	हाल WM8958_MBC_BAND_2_N5_2:
	हाल WM8958_MBC_BAND_2_X1_1:
	हाल WM8958_MBC_BAND_2_X1_2:
	हाल WM8958_MBC_BAND_2_X2_1:
	हाल WM8958_MBC_BAND_2_X2_2:
	हाल WM8958_MBC_BAND_2_X3_1:
	हाल WM8958_MBC_BAND_2_X3_2:
	हाल WM8958_MBC_BAND_2_ATTACK_1:
	हाल WM8958_MBC_BAND_2_ATTACK_2:
	हाल WM8958_MBC_BAND_2_DECAY_1:
	हाल WM8958_MBC_BAND_2_DECAY_2:
	हाल WM8958_MBC_B2_PG2_1:
	हाल WM8958_MBC_B2_PG2_2:
	हाल WM8958_MBC_B1_PG2_1:
	हाल WM8958_MBC_B1_PG2_2:
	हाल WM8958_MBC_CROSSOVER_1:
	हाल WM8958_MBC_CROSSOVER_2:
	हाल WM8958_MBC_HPF_1:
	हाल WM8958_MBC_HPF_2:
	हाल WM8958_MBC_LPF_1:
	हाल WM8958_MBC_LPF_2:
	हाल WM8958_MBC_RMS_LIMIT_1:
	हाल WM8958_MBC_RMS_LIMIT_2:
		वापस true;
	शेष:
		वापस wm8994_पढ़ोable_रेजिस्टर(dev, reg);
	पूर्ण
पूर्ण

अटल bool wm8994_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8994_SOFTWARE_RESET:
	हाल WM8994_DC_SERVO_1:
	हाल WM8994_DC_SERVO_READBACK:
	हाल WM8994_RATE_STATUS:
	हाल WM8958_MIC_DETECT_3:
	हाल WM8994_DC_SERVO_4E:
	हाल WM8994_INTERRUPT_STATUS_1:
	हाल WM8994_INTERRUPT_STATUS_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm1811_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा wm8994 *wm8994 = dev_get_drvdata(dev);

	चयन (reg) अणु
	हाल WM8994_GPIO_6:
		अगर (wm8994->cust_id > 1 || wm8994->revision > 1)
			वापस true;
		अन्यथा
			वापस false;
	शेष:
		वापस wm8994_अस्थिर_रेजिस्टर(dev, reg);
	पूर्ण
पूर्ण

अटल bool wm8958_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8958_DSP2_MAGICNUM:
	हाल WM8958_DSP2_RELEASEYEAR:
	हाल WM8958_DSP2_RELEASEMONTHDAY:
	हाल WM8958_DSP2_RELEASETIME:
	हाल WM8958_DSP2_VERMAJMIN:
	हाल WM8958_DSP2_VERBUILD:
	हाल WM8958_DSP2_EXECCONTROL:
	हाल WM8958_DSP2_SWVERSIONREG:
	हाल WM8958_DSP2_CONFIGXMEM:
	हाल WM8958_DSP2_CONFIGYMEM:
	हाल WM8958_DSP2_CONFIGZMEM:
	हाल WM8958_FW_BUILD_1:
	हाल WM8958_FW_BUILD_0:
	हाल WM8958_FW_ID_1:
	हाल WM8958_FW_ID_0:
	हाल WM8958_FW_MAJOR_1:
	हाल WM8958_FW_MAJOR_0:
	हाल WM8958_FW_MINOR_1:
	हाल WM8958_FW_MINOR_0:
	हाल WM8958_FW_PATCH_1:
	हाल WM8958_FW_PATCH_0:
		वापस true;
	शेष:
		वापस wm8994_अस्थिर_रेजिस्टर(dev, reg);
	पूर्ण
पूर्ण

काष्ठा regmap_config wm1811_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm1811_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm1811_शेषs),

	.max_रेजिस्टर = WM8994_MAX_REGISTER,
	.अस्थिर_reg = wm1811_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm1811_पढ़ोable_रेजिस्टर,
पूर्ण;
EXPORT_SYMBOL(wm1811_regmap_config);

काष्ठा regmap_config wm8994_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm8994_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8994_शेषs),

	.max_रेजिस्टर = WM8994_MAX_REGISTER,
	.अस्थिर_reg = wm8994_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm8994_पढ़ोable_रेजिस्टर,
पूर्ण;
EXPORT_SYMBOL(wm8994_regmap_config);

काष्ठा regmap_config wm8958_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm8958_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8958_शेषs),

	.max_रेजिस्टर = WM8994_MAX_REGISTER,
	.अस्थिर_reg = wm8958_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm8958_पढ़ोable_रेजिस्टर,
पूर्ण;
EXPORT_SYMBOL(wm8958_regmap_config);

काष्ठा regmap_config wm8994_base_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,
पूर्ण;
EXPORT_SYMBOL(wm8994_base_regmap_config);
