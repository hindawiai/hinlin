<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm2200.c  --  WM2200 ALSA SoC Audio driver
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gcd.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm2200.h>

#समावेश "wm2200.h"
#समावेश "wmfw.h"
#समावेश "wm_adsp.h"

#घोषणा WM2200_DSP_CONTROL_1                   0x00
#घोषणा WM2200_DSP_CONTROL_2                   0x02
#घोषणा WM2200_DSP_CONTROL_3                   0x03
#घोषणा WM2200_DSP_CONTROL_4                   0x04
#घोषणा WM2200_DSP_CONTROL_5                   0x06
#घोषणा WM2200_DSP_CONTROL_6                   0x07
#घोषणा WM2200_DSP_CONTROL_7                   0x08
#घोषणा WM2200_DSP_CONTROL_8                   0x09
#घोषणा WM2200_DSP_CONTROL_9                   0x0A
#घोषणा WM2200_DSP_CONTROL_10                  0x0B
#घोषणा WM2200_DSP_CONTROL_11                  0x0C
#घोषणा WM2200_DSP_CONTROL_12                  0x0D
#घोषणा WM2200_DSP_CONTROL_13                  0x0F
#घोषणा WM2200_DSP_CONTROL_14                  0x10
#घोषणा WM2200_DSP_CONTROL_15                  0x11
#घोषणा WM2200_DSP_CONTROL_16                  0x12
#घोषणा WM2200_DSP_CONTROL_17                  0x13
#घोषणा WM2200_DSP_CONTROL_18                  0x14
#घोषणा WM2200_DSP_CONTROL_19                  0x16
#घोषणा WM2200_DSP_CONTROL_20                  0x17
#घोषणा WM2200_DSP_CONTROL_21                  0x18
#घोषणा WM2200_DSP_CONTROL_22                  0x1A
#घोषणा WM2200_DSP_CONTROL_23                  0x1B
#घोषणा WM2200_DSP_CONTROL_24                  0x1C
#घोषणा WM2200_DSP_CONTROL_25                  0x1E
#घोषणा WM2200_DSP_CONTROL_26                  0x20
#घोषणा WM2200_DSP_CONTROL_27                  0x21
#घोषणा WM2200_DSP_CONTROL_28                  0x22
#घोषणा WM2200_DSP_CONTROL_29                  0x23
#घोषणा WM2200_DSP_CONTROL_30                  0x24
#घोषणा WM2200_DSP_CONTROL_31                  0x26

/* The code assumes DCVDD is generated पूर्णांकernally */
#घोषणा WM2200_NUM_CORE_SUPPLIES 2
अटल स्थिर अक्षर *wm2200_core_supply_names[WM2200_NUM_CORE_SUPPLIES] = अणु
	"DBVDD",
	"LDOVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm2200_priv अणु
	काष्ठा wm_adsp dsp[2];
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा snd_soc_component *component;
	काष्ठा wm2200_pdata pdata;
	काष्ठा regulator_bulk_data core_supplies[WM2200_NUM_CORE_SUPPLIES];

	काष्ठा completion fll_lock;
	पूर्णांक fll_fout;
	पूर्णांक fll_fref;
	पूर्णांक fll_src;

	पूर्णांक rev;
	पूर्णांक sysclk;

	अचिन्हित पूर्णांक symmetric_rates:1;
पूर्ण;

#घोषणा WM2200_DSP_RANGE_BASE (WM2200_MAX_REGISTER + 1)
#घोषणा WM2200_DSP_SPACING 12288

#घोषणा WM2200_DSP1_DM_BASE (WM2200_DSP_RANGE_BASE + (0 * WM2200_DSP_SPACING))
#घोषणा WM2200_DSP1_PM_BASE (WM2200_DSP_RANGE_BASE + (1 * WM2200_DSP_SPACING))
#घोषणा WM2200_DSP1_ZM_BASE (WM2200_DSP_RANGE_BASE + (2 * WM2200_DSP_SPACING))
#घोषणा WM2200_DSP2_DM_BASE (WM2200_DSP_RANGE_BASE + (3 * WM2200_DSP_SPACING))
#घोषणा WM2200_DSP2_PM_BASE (WM2200_DSP_RANGE_BASE + (4 * WM2200_DSP_SPACING))
#घोषणा WM2200_DSP2_ZM_BASE (WM2200_DSP_RANGE_BASE + (5 * WM2200_DSP_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg wm2200_ranges[] = अणु
	अणु .name = "DSP1DM", .range_min = WM2200_DSP1_DM_BASE,
	  .range_max = WM2200_DSP1_DM_BASE + 12287,
	  .selector_reg = WM2200_DSP1_CONTROL_3,
	  .selector_mask = WM2200_DSP1_PAGE_BASE_DM_0_MASK,
	  .selector_shअगरt = WM2200_DSP1_PAGE_BASE_DM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP1_DM_0, .winकरोw_len = 2048, पूर्ण,

	अणु .name = "DSP1PM", .range_min = WM2200_DSP1_PM_BASE,
	  .range_max = WM2200_DSP1_PM_BASE + 12287,
	  .selector_reg = WM2200_DSP1_CONTROL_2,
	  .selector_mask = WM2200_DSP1_PAGE_BASE_PM_0_MASK,
	  .selector_shअगरt = WM2200_DSP1_PAGE_BASE_PM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP1_PM_0, .winकरोw_len = 768, पूर्ण,

	अणु .name = "DSP1ZM", .range_min = WM2200_DSP1_ZM_BASE,
	  .range_max = WM2200_DSP1_ZM_BASE + 2047,
	  .selector_reg = WM2200_DSP1_CONTROL_4,
	  .selector_mask = WM2200_DSP1_PAGE_BASE_ZM_0_MASK,
	  .selector_shअगरt = WM2200_DSP1_PAGE_BASE_ZM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP1_ZM_0, .winकरोw_len = 1024, पूर्ण,

	अणु .name = "DSP2DM", .range_min = WM2200_DSP2_DM_BASE,
	  .range_max = WM2200_DSP2_DM_BASE + 4095,
	  .selector_reg = WM2200_DSP2_CONTROL_3,
	  .selector_mask = WM2200_DSP2_PAGE_BASE_DM_0_MASK,
	  .selector_shअगरt = WM2200_DSP2_PAGE_BASE_DM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP2_DM_0, .winकरोw_len = 2048, पूर्ण,

	अणु .name = "DSP2PM", .range_min = WM2200_DSP2_PM_BASE,
	  .range_max = WM2200_DSP2_PM_BASE + 11287,
	  .selector_reg = WM2200_DSP2_CONTROL_2,
	  .selector_mask = WM2200_DSP2_PAGE_BASE_PM_0_MASK,
	  .selector_shअगरt = WM2200_DSP2_PAGE_BASE_PM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP2_PM_0, .winकरोw_len = 768, पूर्ण,

	अणु .name = "DSP2ZM", .range_min = WM2200_DSP2_ZM_BASE,
	  .range_max = WM2200_DSP2_ZM_BASE + 2047,
	  .selector_reg = WM2200_DSP2_CONTROL_4,
	  .selector_mask = WM2200_DSP2_PAGE_BASE_ZM_0_MASK,
	  .selector_shअगरt = WM2200_DSP2_PAGE_BASE_ZM_0_SHIFT,
	  .winकरोw_start = WM2200_DSP2_ZM_0, .winकरोw_len = 1024, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_region wm2200_dsp1_regions[] = अणु
	अणु .type = WMFW_ADSP1_PM, .base = WM2200_DSP1_PM_BASE पूर्ण,
	अणु .type = WMFW_ADSP1_DM, .base = WM2200_DSP1_DM_BASE पूर्ण,
	अणु .type = WMFW_ADSP1_ZM, .base = WM2200_DSP1_ZM_BASE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_region wm2200_dsp2_regions[] = अणु
	अणु .type = WMFW_ADSP1_PM, .base = WM2200_DSP2_PM_BASE पूर्ण,
	अणु .type = WMFW_ADSP1_DM, .base = WM2200_DSP2_DM_BASE पूर्ण,
	अणु .type = WMFW_ADSP1_ZM, .base = WM2200_DSP2_ZM_BASE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm2200_reg_शेषs[] = अणु
	अणु 0x000B, 0x0000 पूर्ण,   /* R11    - Tone Generator 1 */
	अणु 0x0102, 0x0000 पूर्ण,   /* R258   - Clocking 3 */
	अणु 0x0103, 0x0011 पूर्ण,   /* R259   - Clocking 4 */
	अणु 0x0111, 0x0000 पूर्ण,   /* R273   - FLL Control 1 */
	अणु 0x0112, 0x0000 पूर्ण,   /* R274   - FLL Control 2 */
	अणु 0x0113, 0x0000 पूर्ण,   /* R275   - FLL Control 3 */
	अणु 0x0114, 0x0000 पूर्ण,   /* R276   - FLL Control 4 */
	अणु 0x0116, 0x0177 पूर्ण,   /* R278   - FLL Control 6 */
	अणु 0x0117, 0x0004 पूर्ण,   /* R279   - FLL Control 7 */
	अणु 0x0119, 0x0000 पूर्ण,   /* R281   - FLL EFS 1 */
	अणु 0x011A, 0x0002 पूर्ण,   /* R282   - FLL EFS 2 */
	अणु 0x0200, 0x0000 पूर्ण,   /* R512   - Mic Charge Pump 1 */
	अणु 0x0201, 0x03FF पूर्ण,   /* R513   - Mic Charge Pump 2 */
	अणु 0x0202, 0x9BDE पूर्ण,   /* R514   - DM Charge Pump 1 */
	अणु 0x020C, 0x0000 पूर्ण,   /* R524   - Mic Bias Ctrl 1 */
	अणु 0x020D, 0x0000 पूर्ण,   /* R525   - Mic Bias Ctrl 2 */
	अणु 0x020F, 0x0000 पूर्ण,   /* R527   - Ear Piece Ctrl 1 */
	अणु 0x0210, 0x0000 पूर्ण,   /* R528   - Ear Piece Ctrl 2 */
	अणु 0x0301, 0x0000 पूर्ण,   /* R769   - Input Enables */
	अणु 0x0302, 0x2240 पूर्ण,   /* R770   - IN1L Control */
	अणु 0x0303, 0x0040 पूर्ण,   /* R771   - IN1R Control */
	अणु 0x0304, 0x2240 पूर्ण,   /* R772   - IN2L Control */
	अणु 0x0305, 0x0040 पूर्ण,   /* R773   - IN2R Control */
	अणु 0x0306, 0x2240 पूर्ण,   /* R774   - IN3L Control */
	अणु 0x0307, 0x0040 पूर्ण,   /* R775   - IN3R Control */
	अणु 0x030A, 0x0000 पूर्ण,   /* R778   - RXANC_SRC */
	अणु 0x030B, 0x0022 पूर्ण,   /* R779   - Input Volume Ramp */
	अणु 0x030C, 0x0180 पूर्ण,   /* R780   - ADC Digital Volume 1L */
	अणु 0x030D, 0x0180 पूर्ण,   /* R781   - ADC Digital Volume 1R */
	अणु 0x030E, 0x0180 पूर्ण,   /* R782   - ADC Digital Volume 2L */
	अणु 0x030F, 0x0180 पूर्ण,   /* R783   - ADC Digital Volume 2R */
	अणु 0x0310, 0x0180 पूर्ण,   /* R784   - ADC Digital Volume 3L */
	अणु 0x0311, 0x0180 पूर्ण,   /* R785   - ADC Digital Volume 3R */
	अणु 0x0400, 0x0000 पूर्ण,   /* R1024  - Output Enables */
	अणु 0x0401, 0x0000 पूर्ण,   /* R1025  - DAC Volume Limit 1L */
	अणु 0x0402, 0x0000 पूर्ण,   /* R1026  - DAC Volume Limit 1R */
	अणु 0x0403, 0x0000 पूर्ण,   /* R1027  - DAC Volume Limit 2L */
	अणु 0x0404, 0x0000 पूर्ण,   /* R1028  - DAC Volume Limit 2R */
	अणु 0x0409, 0x0000 पूर्ण,   /* R1033  - DAC AEC Control 1 */
	अणु 0x040A, 0x0022 पूर्ण,   /* R1034  - Output Volume Ramp */
	अणु 0x040B, 0x0180 पूर्ण,   /* R1035  - DAC Digital Volume 1L */
	अणु 0x040C, 0x0180 पूर्ण,   /* R1036  - DAC Digital Volume 1R */
	अणु 0x040D, 0x0180 पूर्ण,   /* R1037  - DAC Digital Volume 2L */
	अणु 0x040E, 0x0180 पूर्ण,   /* R1038  - DAC Digital Volume 2R */
	अणु 0x0417, 0x0069 पूर्ण,   /* R1047  - PDM 1 */
	अणु 0x0418, 0x0000 पूर्ण,   /* R1048  - PDM 2 */
	अणु 0x0500, 0x0000 पूर्ण,   /* R1280  - Audio IF 1_1 */
	अणु 0x0501, 0x0008 पूर्ण,   /* R1281  - Audio IF 1_2 */
	अणु 0x0502, 0x0000 पूर्ण,   /* R1282  - Audio IF 1_3 */
	अणु 0x0503, 0x0000 पूर्ण,   /* R1283  - Audio IF 1_4 */
	अणु 0x0504, 0x0000 पूर्ण,   /* R1284  - Audio IF 1_5 */
	अणु 0x0505, 0x0001 पूर्ण,   /* R1285  - Audio IF 1_6 */
	अणु 0x0506, 0x0001 पूर्ण,   /* R1286  - Audio IF 1_7 */
	अणु 0x0507, 0x0000 पूर्ण,   /* R1287  - Audio IF 1_8 */
	अणु 0x0508, 0x0000 पूर्ण,   /* R1288  - Audio IF 1_9 */
	अणु 0x0509, 0x0000 पूर्ण,   /* R1289  - Audio IF 1_10 */
	अणु 0x050A, 0x0000 पूर्ण,   /* R1290  - Audio IF 1_11 */
	अणु 0x050B, 0x0000 पूर्ण,   /* R1291  - Audio IF 1_12 */
	अणु 0x050C, 0x0000 पूर्ण,   /* R1292  - Audio IF 1_13 */
	अणु 0x050D, 0x0000 पूर्ण,   /* R1293  - Audio IF 1_14 */
	अणु 0x050E, 0x0000 पूर्ण,   /* R1294  - Audio IF 1_15 */
	अणु 0x050F, 0x0000 पूर्ण,   /* R1295  - Audio IF 1_16 */
	अणु 0x0510, 0x0000 पूर्ण,   /* R1296  - Audio IF 1_17 */
	अणु 0x0511, 0x0000 पूर्ण,   /* R1297  - Audio IF 1_18 */
	अणु 0x0512, 0x0000 पूर्ण,   /* R1298  - Audio IF 1_19 */
	अणु 0x0513, 0x0000 पूर्ण,   /* R1299  - Audio IF 1_20 */
	अणु 0x0514, 0x0000 पूर्ण,   /* R1300  - Audio IF 1_21 */
	अणु 0x0515, 0x0001 पूर्ण,   /* R1301  - Audio IF 1_22 */
	अणु 0x0600, 0x0000 पूर्ण,   /* R1536  - OUT1LMIX Input 1 Source */
	अणु 0x0601, 0x0080 पूर्ण,   /* R1537  - OUT1LMIX Input 1 Volume */
	अणु 0x0602, 0x0000 पूर्ण,   /* R1538  - OUT1LMIX Input 2 Source */
	अणु 0x0603, 0x0080 पूर्ण,   /* R1539  - OUT1LMIX Input 2 Volume */
	अणु 0x0604, 0x0000 पूर्ण,   /* R1540  - OUT1LMIX Input 3 Source */
	अणु 0x0605, 0x0080 पूर्ण,   /* R1541  - OUT1LMIX Input 3 Volume */
	अणु 0x0606, 0x0000 पूर्ण,   /* R1542  - OUT1LMIX Input 4 Source */
	अणु 0x0607, 0x0080 पूर्ण,   /* R1543  - OUT1LMIX Input 4 Volume */
	अणु 0x0608, 0x0000 पूर्ण,   /* R1544  - OUT1RMIX Input 1 Source */
	अणु 0x0609, 0x0080 पूर्ण,   /* R1545  - OUT1RMIX Input 1 Volume */
	अणु 0x060A, 0x0000 पूर्ण,   /* R1546  - OUT1RMIX Input 2 Source */
	अणु 0x060B, 0x0080 पूर्ण,   /* R1547  - OUT1RMIX Input 2 Volume */
	अणु 0x060C, 0x0000 पूर्ण,   /* R1548  - OUT1RMIX Input 3 Source */
	अणु 0x060D, 0x0080 पूर्ण,   /* R1549  - OUT1RMIX Input 3 Volume */
	अणु 0x060E, 0x0000 पूर्ण,   /* R1550  - OUT1RMIX Input 4 Source */
	अणु 0x060F, 0x0080 पूर्ण,   /* R1551  - OUT1RMIX Input 4 Volume */
	अणु 0x0610, 0x0000 पूर्ण,   /* R1552  - OUT2LMIX Input 1 Source */
	अणु 0x0611, 0x0080 पूर्ण,   /* R1553  - OUT2LMIX Input 1 Volume */
	अणु 0x0612, 0x0000 पूर्ण,   /* R1554  - OUT2LMIX Input 2 Source */
	अणु 0x0613, 0x0080 पूर्ण,   /* R1555  - OUT2LMIX Input 2 Volume */
	अणु 0x0614, 0x0000 पूर्ण,   /* R1556  - OUT2LMIX Input 3 Source */
	अणु 0x0615, 0x0080 पूर्ण,   /* R1557  - OUT2LMIX Input 3 Volume */
	अणु 0x0616, 0x0000 पूर्ण,   /* R1558  - OUT2LMIX Input 4 Source */
	अणु 0x0617, 0x0080 पूर्ण,   /* R1559  - OUT2LMIX Input 4 Volume */
	अणु 0x0618, 0x0000 पूर्ण,   /* R1560  - OUT2RMIX Input 1 Source */
	अणु 0x0619, 0x0080 पूर्ण,   /* R1561  - OUT2RMIX Input 1 Volume */
	अणु 0x061A, 0x0000 पूर्ण,   /* R1562  - OUT2RMIX Input 2 Source */
	अणु 0x061B, 0x0080 पूर्ण,   /* R1563  - OUT2RMIX Input 2 Volume */
	अणु 0x061C, 0x0000 पूर्ण,   /* R1564  - OUT2RMIX Input 3 Source */
	अणु 0x061D, 0x0080 पूर्ण,   /* R1565  - OUT2RMIX Input 3 Volume */
	अणु 0x061E, 0x0000 पूर्ण,   /* R1566  - OUT2RMIX Input 4 Source */
	अणु 0x061F, 0x0080 पूर्ण,   /* R1567  - OUT2RMIX Input 4 Volume */
	अणु 0x0620, 0x0000 पूर्ण,   /* R1568  - AIF1TX1MIX Input 1 Source */
	अणु 0x0621, 0x0080 पूर्ण,   /* R1569  - AIF1TX1MIX Input 1 Volume */
	अणु 0x0622, 0x0000 पूर्ण,   /* R1570  - AIF1TX1MIX Input 2 Source */
	अणु 0x0623, 0x0080 पूर्ण,   /* R1571  - AIF1TX1MIX Input 2 Volume */
	अणु 0x0624, 0x0000 पूर्ण,   /* R1572  - AIF1TX1MIX Input 3 Source */
	अणु 0x0625, 0x0080 पूर्ण,   /* R1573  - AIF1TX1MIX Input 3 Volume */
	अणु 0x0626, 0x0000 पूर्ण,   /* R1574  - AIF1TX1MIX Input 4 Source */
	अणु 0x0627, 0x0080 पूर्ण,   /* R1575  - AIF1TX1MIX Input 4 Volume */
	अणु 0x0628, 0x0000 पूर्ण,   /* R1576  - AIF1TX2MIX Input 1 Source */
	अणु 0x0629, 0x0080 पूर्ण,   /* R1577  - AIF1TX2MIX Input 1 Volume */
	अणु 0x062A, 0x0000 पूर्ण,   /* R1578  - AIF1TX2MIX Input 2 Source */
	अणु 0x062B, 0x0080 पूर्ण,   /* R1579  - AIF1TX2MIX Input 2 Volume */
	अणु 0x062C, 0x0000 पूर्ण,   /* R1580  - AIF1TX2MIX Input 3 Source */
	अणु 0x062D, 0x0080 पूर्ण,   /* R1581  - AIF1TX2MIX Input 3 Volume */
	अणु 0x062E, 0x0000 पूर्ण,   /* R1582  - AIF1TX2MIX Input 4 Source */
	अणु 0x062F, 0x0080 पूर्ण,   /* R1583  - AIF1TX2MIX Input 4 Volume */
	अणु 0x0630, 0x0000 पूर्ण,   /* R1584  - AIF1TX3MIX Input 1 Source */
	अणु 0x0631, 0x0080 पूर्ण,   /* R1585  - AIF1TX3MIX Input 1 Volume */
	अणु 0x0632, 0x0000 पूर्ण,   /* R1586  - AIF1TX3MIX Input 2 Source */
	अणु 0x0633, 0x0080 पूर्ण,   /* R1587  - AIF1TX3MIX Input 2 Volume */
	अणु 0x0634, 0x0000 पूर्ण,   /* R1588  - AIF1TX3MIX Input 3 Source */
	अणु 0x0635, 0x0080 पूर्ण,   /* R1589  - AIF1TX3MIX Input 3 Volume */
	अणु 0x0636, 0x0000 पूर्ण,   /* R1590  - AIF1TX3MIX Input 4 Source */
	अणु 0x0637, 0x0080 पूर्ण,   /* R1591  - AIF1TX3MIX Input 4 Volume */
	अणु 0x0638, 0x0000 पूर्ण,   /* R1592  - AIF1TX4MIX Input 1 Source */
	अणु 0x0639, 0x0080 पूर्ण,   /* R1593  - AIF1TX4MIX Input 1 Volume */
	अणु 0x063A, 0x0000 पूर्ण,   /* R1594  - AIF1TX4MIX Input 2 Source */
	अणु 0x063B, 0x0080 पूर्ण,   /* R1595  - AIF1TX4MIX Input 2 Volume */
	अणु 0x063C, 0x0000 पूर्ण,   /* R1596  - AIF1TX4MIX Input 3 Source */
	अणु 0x063D, 0x0080 पूर्ण,   /* R1597  - AIF1TX4MIX Input 3 Volume */
	अणु 0x063E, 0x0000 पूर्ण,   /* R1598  - AIF1TX4MIX Input 4 Source */
	अणु 0x063F, 0x0080 पूर्ण,   /* R1599  - AIF1TX4MIX Input 4 Volume */
	अणु 0x0640, 0x0000 पूर्ण,   /* R1600  - AIF1TX5MIX Input 1 Source */
	अणु 0x0641, 0x0080 पूर्ण,   /* R1601  - AIF1TX5MIX Input 1 Volume */
	अणु 0x0642, 0x0000 पूर्ण,   /* R1602  - AIF1TX5MIX Input 2 Source */
	अणु 0x0643, 0x0080 पूर्ण,   /* R1603  - AIF1TX5MIX Input 2 Volume */
	अणु 0x0644, 0x0000 पूर्ण,   /* R1604  - AIF1TX5MIX Input 3 Source */
	अणु 0x0645, 0x0080 पूर्ण,   /* R1605  - AIF1TX5MIX Input 3 Volume */
	अणु 0x0646, 0x0000 पूर्ण,   /* R1606  - AIF1TX5MIX Input 4 Source */
	अणु 0x0647, 0x0080 पूर्ण,   /* R1607  - AIF1TX5MIX Input 4 Volume */
	अणु 0x0648, 0x0000 पूर्ण,   /* R1608  - AIF1TX6MIX Input 1 Source */
	अणु 0x0649, 0x0080 पूर्ण,   /* R1609  - AIF1TX6MIX Input 1 Volume */
	अणु 0x064A, 0x0000 पूर्ण,   /* R1610  - AIF1TX6MIX Input 2 Source */
	अणु 0x064B, 0x0080 पूर्ण,   /* R1611  - AIF1TX6MIX Input 2 Volume */
	अणु 0x064C, 0x0000 पूर्ण,   /* R1612  - AIF1TX6MIX Input 3 Source */
	अणु 0x064D, 0x0080 पूर्ण,   /* R1613  - AIF1TX6MIX Input 3 Volume */
	अणु 0x064E, 0x0000 पूर्ण,   /* R1614  - AIF1TX6MIX Input 4 Source */
	अणु 0x064F, 0x0080 पूर्ण,   /* R1615  - AIF1TX6MIX Input 4 Volume */
	अणु 0x0650, 0x0000 पूर्ण,   /* R1616  - EQLMIX Input 1 Source */
	अणु 0x0651, 0x0080 पूर्ण,   /* R1617  - EQLMIX Input 1 Volume */
	अणु 0x0652, 0x0000 पूर्ण,   /* R1618  - EQLMIX Input 2 Source */
	अणु 0x0653, 0x0080 पूर्ण,   /* R1619  - EQLMIX Input 2 Volume */
	अणु 0x0654, 0x0000 पूर्ण,   /* R1620  - EQLMIX Input 3 Source */
	अणु 0x0655, 0x0080 पूर्ण,   /* R1621  - EQLMIX Input 3 Volume */
	अणु 0x0656, 0x0000 पूर्ण,   /* R1622  - EQLMIX Input 4 Source */
	अणु 0x0657, 0x0080 पूर्ण,   /* R1623  - EQLMIX Input 4 Volume */
	अणु 0x0658, 0x0000 पूर्ण,   /* R1624  - EQRMIX Input 1 Source */
	अणु 0x0659, 0x0080 पूर्ण,   /* R1625  - EQRMIX Input 1 Volume */
	अणु 0x065A, 0x0000 पूर्ण,   /* R1626  - EQRMIX Input 2 Source */
	अणु 0x065B, 0x0080 पूर्ण,   /* R1627  - EQRMIX Input 2 Volume */
	अणु 0x065C, 0x0000 पूर्ण,   /* R1628  - EQRMIX Input 3 Source */
	अणु 0x065D, 0x0080 पूर्ण,   /* R1629  - EQRMIX Input 3 Volume */
	अणु 0x065E, 0x0000 पूर्ण,   /* R1630  - EQRMIX Input 4 Source */
	अणु 0x065F, 0x0080 पूर्ण,   /* R1631  - EQRMIX Input 4 Volume */
	अणु 0x0660, 0x0000 पूर्ण,   /* R1632  - LHPF1MIX Input 1 Source */
	अणु 0x0661, 0x0080 पूर्ण,   /* R1633  - LHPF1MIX Input 1 Volume */
	अणु 0x0662, 0x0000 पूर्ण,   /* R1634  - LHPF1MIX Input 2 Source */
	अणु 0x0663, 0x0080 पूर्ण,   /* R1635  - LHPF1MIX Input 2 Volume */
	अणु 0x0664, 0x0000 पूर्ण,   /* R1636  - LHPF1MIX Input 3 Source */
	अणु 0x0665, 0x0080 पूर्ण,   /* R1637  - LHPF1MIX Input 3 Volume */
	अणु 0x0666, 0x0000 पूर्ण,   /* R1638  - LHPF1MIX Input 4 Source */
	अणु 0x0667, 0x0080 पूर्ण,   /* R1639  - LHPF1MIX Input 4 Volume */
	अणु 0x0668, 0x0000 पूर्ण,   /* R1640  - LHPF2MIX Input 1 Source */
	अणु 0x0669, 0x0080 पूर्ण,   /* R1641  - LHPF2MIX Input 1 Volume */
	अणु 0x066A, 0x0000 पूर्ण,   /* R1642  - LHPF2MIX Input 2 Source */
	अणु 0x066B, 0x0080 पूर्ण,   /* R1643  - LHPF2MIX Input 2 Volume */
	अणु 0x066C, 0x0000 पूर्ण,   /* R1644  - LHPF2MIX Input 3 Source */
	अणु 0x066D, 0x0080 पूर्ण,   /* R1645  - LHPF2MIX Input 3 Volume */
	अणु 0x066E, 0x0000 पूर्ण,   /* R1646  - LHPF2MIX Input 4 Source */
	अणु 0x066F, 0x0080 पूर्ण,   /* R1647  - LHPF2MIX Input 4 Volume */
	अणु 0x0670, 0x0000 पूर्ण,   /* R1648  - DSP1LMIX Input 1 Source */
	अणु 0x0671, 0x0080 पूर्ण,   /* R1649  - DSP1LMIX Input 1 Volume */
	अणु 0x0672, 0x0000 पूर्ण,   /* R1650  - DSP1LMIX Input 2 Source */
	अणु 0x0673, 0x0080 पूर्ण,   /* R1651  - DSP1LMIX Input 2 Volume */
	अणु 0x0674, 0x0000 पूर्ण,   /* R1652  - DSP1LMIX Input 3 Source */
	अणु 0x0675, 0x0080 पूर्ण,   /* R1653  - DSP1LMIX Input 3 Volume */
	अणु 0x0676, 0x0000 पूर्ण,   /* R1654  - DSP1LMIX Input 4 Source */
	अणु 0x0677, 0x0080 पूर्ण,   /* R1655  - DSP1LMIX Input 4 Volume */
	अणु 0x0678, 0x0000 पूर्ण,   /* R1656  - DSP1RMIX Input 1 Source */
	अणु 0x0679, 0x0080 पूर्ण,   /* R1657  - DSP1RMIX Input 1 Volume */
	अणु 0x067A, 0x0000 पूर्ण,   /* R1658  - DSP1RMIX Input 2 Source */
	अणु 0x067B, 0x0080 पूर्ण,   /* R1659  - DSP1RMIX Input 2 Volume */
	अणु 0x067C, 0x0000 पूर्ण,   /* R1660  - DSP1RMIX Input 3 Source */
	अणु 0x067D, 0x0080 पूर्ण,   /* R1661  - DSP1RMIX Input 3 Volume */
	अणु 0x067E, 0x0000 पूर्ण,   /* R1662  - DSP1RMIX Input 4 Source */
	अणु 0x067F, 0x0080 पूर्ण,   /* R1663  - DSP1RMIX Input 4 Volume */
	अणु 0x0680, 0x0000 पूर्ण,   /* R1664  - DSP1AUX1MIX Input 1 Source */
	अणु 0x0681, 0x0000 पूर्ण,   /* R1665  - DSP1AUX2MIX Input 1 Source */
	अणु 0x0682, 0x0000 पूर्ण,   /* R1666  - DSP1AUX3MIX Input 1 Source */
	अणु 0x0683, 0x0000 पूर्ण,   /* R1667  - DSP1AUX4MIX Input 1 Source */
	अणु 0x0684, 0x0000 पूर्ण,   /* R1668  - DSP1AUX5MIX Input 1 Source */
	अणु 0x0685, 0x0000 पूर्ण,   /* R1669  - DSP1AUX6MIX Input 1 Source */
	अणु 0x0686, 0x0000 पूर्ण,   /* R1670  - DSP2LMIX Input 1 Source */
	अणु 0x0687, 0x0080 पूर्ण,   /* R1671  - DSP2LMIX Input 1 Volume */
	अणु 0x0688, 0x0000 पूर्ण,   /* R1672  - DSP2LMIX Input 2 Source */
	अणु 0x0689, 0x0080 पूर्ण,   /* R1673  - DSP2LMIX Input 2 Volume */
	अणु 0x068A, 0x0000 पूर्ण,   /* R1674  - DSP2LMIX Input 3 Source */
	अणु 0x068B, 0x0080 पूर्ण,   /* R1675  - DSP2LMIX Input 3 Volume */
	अणु 0x068C, 0x0000 पूर्ण,   /* R1676  - DSP2LMIX Input 4 Source */
	अणु 0x068D, 0x0080 पूर्ण,   /* R1677  - DSP2LMIX Input 4 Volume */
	अणु 0x068E, 0x0000 पूर्ण,   /* R1678  - DSP2RMIX Input 1 Source */
	अणु 0x068F, 0x0080 पूर्ण,   /* R1679  - DSP2RMIX Input 1 Volume */
	अणु 0x0690, 0x0000 पूर्ण,   /* R1680  - DSP2RMIX Input 2 Source */
	अणु 0x0691, 0x0080 पूर्ण,   /* R1681  - DSP2RMIX Input 2 Volume */
	अणु 0x0692, 0x0000 पूर्ण,   /* R1682  - DSP2RMIX Input 3 Source */
	अणु 0x0693, 0x0080 पूर्ण,   /* R1683  - DSP2RMIX Input 3 Volume */
	अणु 0x0694, 0x0000 पूर्ण,   /* R1684  - DSP2RMIX Input 4 Source */
	अणु 0x0695, 0x0080 पूर्ण,   /* R1685  - DSP2RMIX Input 4 Volume */
	अणु 0x0696, 0x0000 पूर्ण,   /* R1686  - DSP2AUX1MIX Input 1 Source */
	अणु 0x0697, 0x0000 पूर्ण,   /* R1687  - DSP2AUX2MIX Input 1 Source */
	अणु 0x0698, 0x0000 पूर्ण,   /* R1688  - DSP2AUX3MIX Input 1 Source */
	अणु 0x0699, 0x0000 पूर्ण,   /* R1689  - DSP2AUX4MIX Input 1 Source */
	अणु 0x069A, 0x0000 पूर्ण,   /* R1690  - DSP2AUX5MIX Input 1 Source */
	अणु 0x069B, 0x0000 पूर्ण,   /* R1691  - DSP2AUX6MIX Input 1 Source */
	अणु 0x0700, 0xA101 पूर्ण,   /* R1792  - GPIO CTRL 1 */
	अणु 0x0701, 0xA101 पूर्ण,   /* R1793  - GPIO CTRL 2 */
	अणु 0x0702, 0xA101 पूर्ण,   /* R1794  - GPIO CTRL 3 */
	अणु 0x0703, 0xA101 पूर्ण,   /* R1795  - GPIO CTRL 4 */
	अणु 0x0709, 0x0000 पूर्ण,   /* R1801  - Misc Pad Ctrl 1 */
	अणु 0x0801, 0x00FF पूर्ण,   /* R2049  - Interrupt Status 1 Mask */
	अणु 0x0804, 0xFFFF पूर्ण,   /* R2052  - Interrupt Status 2 Mask */
	अणु 0x0808, 0x0000 पूर्ण,   /* R2056  - Interrupt Control */
	अणु 0x0900, 0x0000 पूर्ण,   /* R2304  - EQL_1 */
	अणु 0x0901, 0x0000 पूर्ण,   /* R2305  - EQL_2 */
	अणु 0x0902, 0x0000 पूर्ण,   /* R2306  - EQL_3 */
	अणु 0x0903, 0x0000 पूर्ण,   /* R2307  - EQL_4 */
	अणु 0x0904, 0x0000 पूर्ण,   /* R2308  - EQL_5 */
	अणु 0x0905, 0x0000 पूर्ण,   /* R2309  - EQL_6 */
	अणु 0x0906, 0x0000 पूर्ण,   /* R2310  - EQL_7 */
	अणु 0x0907, 0x0000 पूर्ण,   /* R2311  - EQL_8 */
	अणु 0x0908, 0x0000 पूर्ण,   /* R2312  - EQL_9 */
	अणु 0x0909, 0x0000 पूर्ण,   /* R2313  - EQL_10 */
	अणु 0x090A, 0x0000 पूर्ण,   /* R2314  - EQL_11 */
	अणु 0x090B, 0x0000 पूर्ण,   /* R2315  - EQL_12 */
	अणु 0x090C, 0x0000 पूर्ण,   /* R2316  - EQL_13 */
	अणु 0x090D, 0x0000 पूर्ण,   /* R2317  - EQL_14 */
	अणु 0x090E, 0x0000 पूर्ण,   /* R2318  - EQL_15 */
	अणु 0x090F, 0x0000 पूर्ण,   /* R2319  - EQL_16 */
	अणु 0x0910, 0x0000 पूर्ण,   /* R2320  - EQL_17 */
	अणु 0x0911, 0x0000 पूर्ण,   /* R2321  - EQL_18 */
	अणु 0x0912, 0x0000 पूर्ण,   /* R2322  - EQL_19 */
	अणु 0x0913, 0x0000 पूर्ण,   /* R2323  - EQL_20 */
	अणु 0x0916, 0x0000 पूर्ण,   /* R2326  - EQR_1 */
	अणु 0x0917, 0x0000 पूर्ण,   /* R2327  - EQR_2 */
	अणु 0x0918, 0x0000 पूर्ण,   /* R2328  - EQR_3 */
	अणु 0x0919, 0x0000 पूर्ण,   /* R2329  - EQR_4 */
	अणु 0x091A, 0x0000 पूर्ण,   /* R2330  - EQR_5 */
	अणु 0x091B, 0x0000 पूर्ण,   /* R2331  - EQR_6 */
	अणु 0x091C, 0x0000 पूर्ण,   /* R2332  - EQR_7 */
	अणु 0x091D, 0x0000 पूर्ण,   /* R2333  - EQR_8 */
	अणु 0x091E, 0x0000 पूर्ण,   /* R2334  - EQR_9 */
	अणु 0x091F, 0x0000 पूर्ण,   /* R2335  - EQR_10 */
	अणु 0x0920, 0x0000 पूर्ण,   /* R2336  - EQR_11 */
	अणु 0x0921, 0x0000 पूर्ण,   /* R2337  - EQR_12 */
	अणु 0x0922, 0x0000 पूर्ण,   /* R2338  - EQR_13 */
	अणु 0x0923, 0x0000 पूर्ण,   /* R2339  - EQR_14 */
	अणु 0x0924, 0x0000 पूर्ण,   /* R2340  - EQR_15 */
	अणु 0x0925, 0x0000 पूर्ण,   /* R2341  - EQR_16 */
	अणु 0x0926, 0x0000 पूर्ण,   /* R2342  - EQR_17 */
	अणु 0x0927, 0x0000 पूर्ण,   /* R2343  - EQR_18 */
	अणु 0x0928, 0x0000 पूर्ण,   /* R2344  - EQR_19 */
	अणु 0x0929, 0x0000 पूर्ण,   /* R2345  - EQR_20 */
	अणु 0x093E, 0x0000 पूर्ण,   /* R2366  - HPLPF1_1 */
	अणु 0x093F, 0x0000 पूर्ण,   /* R2367  - HPLPF1_2 */
	अणु 0x0942, 0x0000 पूर्ण,   /* R2370  - HPLPF2_1 */
	अणु 0x0943, 0x0000 पूर्ण,   /* R2371  - HPLPF2_2 */
	अणु 0x0A00, 0x0000 पूर्ण,   /* R2560  - DSP1 Control 1 */
	अणु 0x0A02, 0x0000 पूर्ण,   /* R2562  - DSP1 Control 2 */
	अणु 0x0A03, 0x0000 पूर्ण,   /* R2563  - DSP1 Control 3 */
	अणु 0x0A04, 0x0000 पूर्ण,   /* R2564  - DSP1 Control 4 */
	अणु 0x0A06, 0x0000 पूर्ण,   /* R2566  - DSP1 Control 5 */
	अणु 0x0A07, 0x0000 पूर्ण,   /* R2567  - DSP1 Control 6 */
	अणु 0x0A08, 0x0000 पूर्ण,   /* R2568  - DSP1 Control 7 */
	अणु 0x0A09, 0x0000 पूर्ण,   /* R2569  - DSP1 Control 8 */
	अणु 0x0A0A, 0x0000 पूर्ण,   /* R2570  - DSP1 Control 9 */
	अणु 0x0A0B, 0x0000 पूर्ण,   /* R2571  - DSP1 Control 10 */
	अणु 0x0A0C, 0x0000 पूर्ण,   /* R2572  - DSP1 Control 11 */
	अणु 0x0A0D, 0x0000 पूर्ण,   /* R2573  - DSP1 Control 12 */
	अणु 0x0A0F, 0x0000 पूर्ण,   /* R2575  - DSP1 Control 13 */
	अणु 0x0A10, 0x0000 पूर्ण,   /* R2576  - DSP1 Control 14 */
	अणु 0x0A11, 0x0000 पूर्ण,   /* R2577  - DSP1 Control 15 */
	अणु 0x0A12, 0x0000 पूर्ण,   /* R2578  - DSP1 Control 16 */
	अणु 0x0A13, 0x0000 पूर्ण,   /* R2579  - DSP1 Control 17 */
	अणु 0x0A14, 0x0000 पूर्ण,   /* R2580  - DSP1 Control 18 */
	अणु 0x0A16, 0x0000 पूर्ण,   /* R2582  - DSP1 Control 19 */
	अणु 0x0A17, 0x0000 पूर्ण,   /* R2583  - DSP1 Control 20 */
	अणु 0x0A18, 0x0000 पूर्ण,   /* R2584  - DSP1 Control 21 */
	अणु 0x0A1A, 0x1800 पूर्ण,   /* R2586  - DSP1 Control 22 */
	अणु 0x0A1B, 0x1000 पूर्ण,   /* R2587  - DSP1 Control 23 */
	अणु 0x0A1C, 0x0400 पूर्ण,   /* R2588  - DSP1 Control 24 */
	अणु 0x0A1E, 0x0000 पूर्ण,   /* R2590  - DSP1 Control 25 */
	अणु 0x0A20, 0x0000 पूर्ण,   /* R2592  - DSP1 Control 26 */
	अणु 0x0A21, 0x0000 पूर्ण,   /* R2593  - DSP1 Control 27 */
	अणु 0x0A22, 0x0000 पूर्ण,   /* R2594  - DSP1 Control 28 */
	अणु 0x0A23, 0x0000 पूर्ण,   /* R2595  - DSP1 Control 29 */
	अणु 0x0A24, 0x0000 पूर्ण,   /* R2596  - DSP1 Control 30 */
	अणु 0x0A26, 0x0000 पूर्ण,   /* R2598  - DSP1 Control 31 */
	अणु 0x0B00, 0x0000 पूर्ण,   /* R2816  - DSP2 Control 1 */
	अणु 0x0B02, 0x0000 पूर्ण,   /* R2818  - DSP2 Control 2 */
	अणु 0x0B03, 0x0000 पूर्ण,   /* R2819  - DSP2 Control 3 */
	अणु 0x0B04, 0x0000 पूर्ण,   /* R2820  - DSP2 Control 4 */
	अणु 0x0B06, 0x0000 पूर्ण,   /* R2822  - DSP2 Control 5 */
	अणु 0x0B07, 0x0000 पूर्ण,   /* R2823  - DSP2 Control 6 */
	अणु 0x0B08, 0x0000 पूर्ण,   /* R2824  - DSP2 Control 7 */
	अणु 0x0B09, 0x0000 पूर्ण,   /* R2825  - DSP2 Control 8 */
	अणु 0x0B0A, 0x0000 पूर्ण,   /* R2826  - DSP2 Control 9 */
	अणु 0x0B0B, 0x0000 पूर्ण,   /* R2827  - DSP2 Control 10 */
	अणु 0x0B0C, 0x0000 पूर्ण,   /* R2828  - DSP2 Control 11 */
	अणु 0x0B0D, 0x0000 पूर्ण,   /* R2829  - DSP2 Control 12 */
	अणु 0x0B0F, 0x0000 पूर्ण,   /* R2831  - DSP2 Control 13 */
	अणु 0x0B10, 0x0000 पूर्ण,   /* R2832  - DSP2 Control 14 */
	अणु 0x0B11, 0x0000 पूर्ण,   /* R2833  - DSP2 Control 15 */
	अणु 0x0B12, 0x0000 पूर्ण,   /* R2834  - DSP2 Control 16 */
	अणु 0x0B13, 0x0000 पूर्ण,   /* R2835  - DSP2 Control 17 */
	अणु 0x0B14, 0x0000 पूर्ण,   /* R2836  - DSP2 Control 18 */
	अणु 0x0B16, 0x0000 पूर्ण,   /* R2838  - DSP2 Control 19 */
	अणु 0x0B17, 0x0000 पूर्ण,   /* R2839  - DSP2 Control 20 */
	अणु 0x0B18, 0x0000 पूर्ण,   /* R2840  - DSP2 Control 21 */
	अणु 0x0B1A, 0x0800 पूर्ण,   /* R2842  - DSP2 Control 22 */
	अणु 0x0B1B, 0x1000 पूर्ण,   /* R2843  - DSP2 Control 23 */
	अणु 0x0B1C, 0x0400 पूर्ण,   /* R2844  - DSP2 Control 24 */
	अणु 0x0B1E, 0x0000 पूर्ण,   /* R2846  - DSP2 Control 25 */
	अणु 0x0B20, 0x0000 पूर्ण,   /* R2848  - DSP2 Control 26 */
	अणु 0x0B21, 0x0000 पूर्ण,   /* R2849  - DSP2 Control 27 */
	अणु 0x0B22, 0x0000 पूर्ण,   /* R2850  - DSP2 Control 28 */
	अणु 0x0B23, 0x0000 पूर्ण,   /* R2851  - DSP2 Control 29 */
	अणु 0x0B24, 0x0000 पूर्ण,   /* R2852  - DSP2 Control 30 */
	अणु 0x0B26, 0x0000 पूर्ण,   /* R2854  - DSP2 Control 31 */
पूर्ण;

अटल bool wm2200_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm2200_ranges); i++)
		अगर ((reg >= wm2200_ranges[i].winकरोw_start &&
		     reg <= wm2200_ranges[i].winकरोw_start +
		     wm2200_ranges[i].winकरोw_len) ||
		    (reg >= wm2200_ranges[i].range_min &&
		     reg <= wm2200_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल WM2200_SOFTWARE_RESET:
	हाल WM2200_DEVICE_REVISION:
	हाल WM2200_ADPS1_IRQ0:
	हाल WM2200_ADPS1_IRQ1:
	हाल WM2200_INTERRUPT_STATUS_1:
	हाल WM2200_INTERRUPT_STATUS_2:
	हाल WM2200_INTERRUPT_RAW_STATUS_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm2200_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm2200_ranges); i++)
		अगर ((reg >= wm2200_ranges[i].winकरोw_start &&
		     reg <= wm2200_ranges[i].winकरोw_start +
		     wm2200_ranges[i].winकरोw_len) ||
		    (reg >= wm2200_ranges[i].range_min &&
		     reg <= wm2200_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल WM2200_SOFTWARE_RESET:
	हाल WM2200_DEVICE_REVISION:
	हाल WM2200_TONE_GENERATOR_1:
	हाल WM2200_CLOCKING_3:
	हाल WM2200_CLOCKING_4:
	हाल WM2200_FLL_CONTROL_1:
	हाल WM2200_FLL_CONTROL_2:
	हाल WM2200_FLL_CONTROL_3:
	हाल WM2200_FLL_CONTROL_4:
	हाल WM2200_FLL_CONTROL_6:
	हाल WM2200_FLL_CONTROL_7:
	हाल WM2200_FLL_EFS_1:
	हाल WM2200_FLL_EFS_2:
	हाल WM2200_MIC_CHARGE_PUMP_1:
	हाल WM2200_MIC_CHARGE_PUMP_2:
	हाल WM2200_DM_CHARGE_PUMP_1:
	हाल WM2200_MIC_BIAS_CTRL_1:
	हाल WM2200_MIC_BIAS_CTRL_2:
	हाल WM2200_EAR_PIECE_CTRL_1:
	हाल WM2200_EAR_PIECE_CTRL_2:
	हाल WM2200_INPUT_ENABLES:
	हाल WM2200_IN1L_CONTROL:
	हाल WM2200_IN1R_CONTROL:
	हाल WM2200_IN2L_CONTROL:
	हाल WM2200_IN2R_CONTROL:
	हाल WM2200_IN3L_CONTROL:
	हाल WM2200_IN3R_CONTROL:
	हाल WM2200_RXANC_SRC:
	हाल WM2200_INPUT_VOLUME_RAMP:
	हाल WM2200_ADC_DIGITAL_VOLUME_1L:
	हाल WM2200_ADC_DIGITAL_VOLUME_1R:
	हाल WM2200_ADC_DIGITAL_VOLUME_2L:
	हाल WM2200_ADC_DIGITAL_VOLUME_2R:
	हाल WM2200_ADC_DIGITAL_VOLUME_3L:
	हाल WM2200_ADC_DIGITAL_VOLUME_3R:
	हाल WM2200_OUTPUT_ENABLES:
	हाल WM2200_DAC_VOLUME_LIMIT_1L:
	हाल WM2200_DAC_VOLUME_LIMIT_1R:
	हाल WM2200_DAC_VOLUME_LIMIT_2L:
	हाल WM2200_DAC_VOLUME_LIMIT_2R:
	हाल WM2200_DAC_AEC_CONTROL_1:
	हाल WM2200_OUTPUT_VOLUME_RAMP:
	हाल WM2200_DAC_DIGITAL_VOLUME_1L:
	हाल WM2200_DAC_DIGITAL_VOLUME_1R:
	हाल WM2200_DAC_DIGITAL_VOLUME_2L:
	हाल WM2200_DAC_DIGITAL_VOLUME_2R:
	हाल WM2200_PDM_1:
	हाल WM2200_PDM_2:
	हाल WM2200_AUDIO_IF_1_1:
	हाल WM2200_AUDIO_IF_1_2:
	हाल WM2200_AUDIO_IF_1_3:
	हाल WM2200_AUDIO_IF_1_4:
	हाल WM2200_AUDIO_IF_1_5:
	हाल WM2200_AUDIO_IF_1_6:
	हाल WM2200_AUDIO_IF_1_7:
	हाल WM2200_AUDIO_IF_1_8:
	हाल WM2200_AUDIO_IF_1_9:
	हाल WM2200_AUDIO_IF_1_10:
	हाल WM2200_AUDIO_IF_1_11:
	हाल WM2200_AUDIO_IF_1_12:
	हाल WM2200_AUDIO_IF_1_13:
	हाल WM2200_AUDIO_IF_1_14:
	हाल WM2200_AUDIO_IF_1_15:
	हाल WM2200_AUDIO_IF_1_16:
	हाल WM2200_AUDIO_IF_1_17:
	हाल WM2200_AUDIO_IF_1_18:
	हाल WM2200_AUDIO_IF_1_19:
	हाल WM2200_AUDIO_IF_1_20:
	हाल WM2200_AUDIO_IF_1_21:
	हाल WM2200_AUDIO_IF_1_22:
	हाल WM2200_OUT1LMIX_INPUT_1_SOURCE:
	हाल WM2200_OUT1LMIX_INPUT_1_VOLUME:
	हाल WM2200_OUT1LMIX_INPUT_2_SOURCE:
	हाल WM2200_OUT1LMIX_INPUT_2_VOLUME:
	हाल WM2200_OUT1LMIX_INPUT_3_SOURCE:
	हाल WM2200_OUT1LMIX_INPUT_3_VOLUME:
	हाल WM2200_OUT1LMIX_INPUT_4_SOURCE:
	हाल WM2200_OUT1LMIX_INPUT_4_VOLUME:
	हाल WM2200_OUT1RMIX_INPUT_1_SOURCE:
	हाल WM2200_OUT1RMIX_INPUT_1_VOLUME:
	हाल WM2200_OUT1RMIX_INPUT_2_SOURCE:
	हाल WM2200_OUT1RMIX_INPUT_2_VOLUME:
	हाल WM2200_OUT1RMIX_INPUT_3_SOURCE:
	हाल WM2200_OUT1RMIX_INPUT_3_VOLUME:
	हाल WM2200_OUT1RMIX_INPUT_4_SOURCE:
	हाल WM2200_OUT1RMIX_INPUT_4_VOLUME:
	हाल WM2200_OUT2LMIX_INPUT_1_SOURCE:
	हाल WM2200_OUT2LMIX_INPUT_1_VOLUME:
	हाल WM2200_OUT2LMIX_INPUT_2_SOURCE:
	हाल WM2200_OUT2LMIX_INPUT_2_VOLUME:
	हाल WM2200_OUT2LMIX_INPUT_3_SOURCE:
	हाल WM2200_OUT2LMIX_INPUT_3_VOLUME:
	हाल WM2200_OUT2LMIX_INPUT_4_SOURCE:
	हाल WM2200_OUT2LMIX_INPUT_4_VOLUME:
	हाल WM2200_OUT2RMIX_INPUT_1_SOURCE:
	हाल WM2200_OUT2RMIX_INPUT_1_VOLUME:
	हाल WM2200_OUT2RMIX_INPUT_2_SOURCE:
	हाल WM2200_OUT2RMIX_INPUT_2_VOLUME:
	हाल WM2200_OUT2RMIX_INPUT_3_SOURCE:
	हाल WM2200_OUT2RMIX_INPUT_3_VOLUME:
	हाल WM2200_OUT2RMIX_INPUT_4_SOURCE:
	हाल WM2200_OUT2RMIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX1MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX1MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX1MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX1MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX1MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX1MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX1MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX1MIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX2MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX2MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX2MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX2MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX2MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX2MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX2MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX2MIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX3MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX3MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX3MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX3MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX3MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX3MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX3MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX3MIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX4MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX4MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX4MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX4MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX4MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX4MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX4MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX4MIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX5MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX5MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX5MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX5MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX5MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX5MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX5MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX5MIX_INPUT_4_VOLUME:
	हाल WM2200_AIF1TX6MIX_INPUT_1_SOURCE:
	हाल WM2200_AIF1TX6MIX_INPUT_1_VOLUME:
	हाल WM2200_AIF1TX6MIX_INPUT_2_SOURCE:
	हाल WM2200_AIF1TX6MIX_INPUT_2_VOLUME:
	हाल WM2200_AIF1TX6MIX_INPUT_3_SOURCE:
	हाल WM2200_AIF1TX6MIX_INPUT_3_VOLUME:
	हाल WM2200_AIF1TX6MIX_INPUT_4_SOURCE:
	हाल WM2200_AIF1TX6MIX_INPUT_4_VOLUME:
	हाल WM2200_EQLMIX_INPUT_1_SOURCE:
	हाल WM2200_EQLMIX_INPUT_1_VOLUME:
	हाल WM2200_EQLMIX_INPUT_2_SOURCE:
	हाल WM2200_EQLMIX_INPUT_2_VOLUME:
	हाल WM2200_EQLMIX_INPUT_3_SOURCE:
	हाल WM2200_EQLMIX_INPUT_3_VOLUME:
	हाल WM2200_EQLMIX_INPUT_4_SOURCE:
	हाल WM2200_EQLMIX_INPUT_4_VOLUME:
	हाल WM2200_EQRMIX_INPUT_1_SOURCE:
	हाल WM2200_EQRMIX_INPUT_1_VOLUME:
	हाल WM2200_EQRMIX_INPUT_2_SOURCE:
	हाल WM2200_EQRMIX_INPUT_2_VOLUME:
	हाल WM2200_EQRMIX_INPUT_3_SOURCE:
	हाल WM2200_EQRMIX_INPUT_3_VOLUME:
	हाल WM2200_EQRMIX_INPUT_4_SOURCE:
	हाल WM2200_EQRMIX_INPUT_4_VOLUME:
	हाल WM2200_LHPF1MIX_INPUT_1_SOURCE:
	हाल WM2200_LHPF1MIX_INPUT_1_VOLUME:
	हाल WM2200_LHPF1MIX_INPUT_2_SOURCE:
	हाल WM2200_LHPF1MIX_INPUT_2_VOLUME:
	हाल WM2200_LHPF1MIX_INPUT_3_SOURCE:
	हाल WM2200_LHPF1MIX_INPUT_3_VOLUME:
	हाल WM2200_LHPF1MIX_INPUT_4_SOURCE:
	हाल WM2200_LHPF1MIX_INPUT_4_VOLUME:
	हाल WM2200_LHPF2MIX_INPUT_1_SOURCE:
	हाल WM2200_LHPF2MIX_INPUT_1_VOLUME:
	हाल WM2200_LHPF2MIX_INPUT_2_SOURCE:
	हाल WM2200_LHPF2MIX_INPUT_2_VOLUME:
	हाल WM2200_LHPF2MIX_INPUT_3_SOURCE:
	हाल WM2200_LHPF2MIX_INPUT_3_VOLUME:
	हाल WM2200_LHPF2MIX_INPUT_4_SOURCE:
	हाल WM2200_LHPF2MIX_INPUT_4_VOLUME:
	हाल WM2200_DSP1LMIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1LMIX_INPUT_1_VOLUME:
	हाल WM2200_DSP1LMIX_INPUT_2_SOURCE:
	हाल WM2200_DSP1LMIX_INPUT_2_VOLUME:
	हाल WM2200_DSP1LMIX_INPUT_3_SOURCE:
	हाल WM2200_DSP1LMIX_INPUT_3_VOLUME:
	हाल WM2200_DSP1LMIX_INPUT_4_SOURCE:
	हाल WM2200_DSP1LMIX_INPUT_4_VOLUME:
	हाल WM2200_DSP1RMIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1RMIX_INPUT_1_VOLUME:
	हाल WM2200_DSP1RMIX_INPUT_2_SOURCE:
	हाल WM2200_DSP1RMIX_INPUT_2_VOLUME:
	हाल WM2200_DSP1RMIX_INPUT_3_SOURCE:
	हाल WM2200_DSP1RMIX_INPUT_3_VOLUME:
	हाल WM2200_DSP1RMIX_INPUT_4_SOURCE:
	हाल WM2200_DSP1RMIX_INPUT_4_VOLUME:
	हाल WM2200_DSP1AUX1MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1AUX2MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1AUX3MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1AUX4MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1AUX5MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP1AUX6MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2LMIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2LMIX_INPUT_1_VOLUME:
	हाल WM2200_DSP2LMIX_INPUT_2_SOURCE:
	हाल WM2200_DSP2LMIX_INPUT_2_VOLUME:
	हाल WM2200_DSP2LMIX_INPUT_3_SOURCE:
	हाल WM2200_DSP2LMIX_INPUT_3_VOLUME:
	हाल WM2200_DSP2LMIX_INPUT_4_SOURCE:
	हाल WM2200_DSP2LMIX_INPUT_4_VOLUME:
	हाल WM2200_DSP2RMIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2RMIX_INPUT_1_VOLUME:
	हाल WM2200_DSP2RMIX_INPUT_2_SOURCE:
	हाल WM2200_DSP2RMIX_INPUT_2_VOLUME:
	हाल WM2200_DSP2RMIX_INPUT_3_SOURCE:
	हाल WM2200_DSP2RMIX_INPUT_3_VOLUME:
	हाल WM2200_DSP2RMIX_INPUT_4_SOURCE:
	हाल WM2200_DSP2RMIX_INPUT_4_VOLUME:
	हाल WM2200_DSP2AUX1MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2AUX2MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2AUX3MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2AUX4MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2AUX5MIX_INPUT_1_SOURCE:
	हाल WM2200_DSP2AUX6MIX_INPUT_1_SOURCE:
	हाल WM2200_GPIO_CTRL_1:
	हाल WM2200_GPIO_CTRL_2:
	हाल WM2200_GPIO_CTRL_3:
	हाल WM2200_GPIO_CTRL_4:
	हाल WM2200_ADPS1_IRQ0:
	हाल WM2200_ADPS1_IRQ1:
	हाल WM2200_MISC_PAD_CTRL_1:
	हाल WM2200_INTERRUPT_STATUS_1:
	हाल WM2200_INTERRUPT_STATUS_1_MASK:
	हाल WM2200_INTERRUPT_STATUS_2:
	हाल WM2200_INTERRUPT_RAW_STATUS_2:
	हाल WM2200_INTERRUPT_STATUS_2_MASK:
	हाल WM2200_INTERRUPT_CONTROL:
	हाल WM2200_EQL_1:
	हाल WM2200_EQL_2:
	हाल WM2200_EQL_3:
	हाल WM2200_EQL_4:
	हाल WM2200_EQL_5:
	हाल WM2200_EQL_6:
	हाल WM2200_EQL_7:
	हाल WM2200_EQL_8:
	हाल WM2200_EQL_9:
	हाल WM2200_EQL_10:
	हाल WM2200_EQL_11:
	हाल WM2200_EQL_12:
	हाल WM2200_EQL_13:
	हाल WM2200_EQL_14:
	हाल WM2200_EQL_15:
	हाल WM2200_EQL_16:
	हाल WM2200_EQL_17:
	हाल WM2200_EQL_18:
	हाल WM2200_EQL_19:
	हाल WM2200_EQL_20:
	हाल WM2200_EQR_1:
	हाल WM2200_EQR_2:
	हाल WM2200_EQR_3:
	हाल WM2200_EQR_4:
	हाल WM2200_EQR_5:
	हाल WM2200_EQR_6:
	हाल WM2200_EQR_7:
	हाल WM2200_EQR_8:
	हाल WM2200_EQR_9:
	हाल WM2200_EQR_10:
	हाल WM2200_EQR_11:
	हाल WM2200_EQR_12:
	हाल WM2200_EQR_13:
	हाल WM2200_EQR_14:
	हाल WM2200_EQR_15:
	हाल WM2200_EQR_16:
	हाल WM2200_EQR_17:
	हाल WM2200_EQR_18:
	हाल WM2200_EQR_19:
	हाल WM2200_EQR_20:
	हाल WM2200_HPLPF1_1:
	हाल WM2200_HPLPF1_2:
	हाल WM2200_HPLPF2_1:
	हाल WM2200_HPLPF2_2:
	हाल WM2200_DSP1_CONTROL_1:
	हाल WM2200_DSP1_CONTROL_2:
	हाल WM2200_DSP1_CONTROL_3:
	हाल WM2200_DSP1_CONTROL_4:
	हाल WM2200_DSP1_CONTROL_5:
	हाल WM2200_DSP1_CONTROL_6:
	हाल WM2200_DSP1_CONTROL_7:
	हाल WM2200_DSP1_CONTROL_8:
	हाल WM2200_DSP1_CONTROL_9:
	हाल WM2200_DSP1_CONTROL_10:
	हाल WM2200_DSP1_CONTROL_11:
	हाल WM2200_DSP1_CONTROL_12:
	हाल WM2200_DSP1_CONTROL_13:
	हाल WM2200_DSP1_CONTROL_14:
	हाल WM2200_DSP1_CONTROL_15:
	हाल WM2200_DSP1_CONTROL_16:
	हाल WM2200_DSP1_CONTROL_17:
	हाल WM2200_DSP1_CONTROL_18:
	हाल WM2200_DSP1_CONTROL_19:
	हाल WM2200_DSP1_CONTROL_20:
	हाल WM2200_DSP1_CONTROL_21:
	हाल WM2200_DSP1_CONTROL_22:
	हाल WM2200_DSP1_CONTROL_23:
	हाल WM2200_DSP1_CONTROL_24:
	हाल WM2200_DSP1_CONTROL_25:
	हाल WM2200_DSP1_CONTROL_26:
	हाल WM2200_DSP1_CONTROL_27:
	हाल WM2200_DSP1_CONTROL_28:
	हाल WM2200_DSP1_CONTROL_29:
	हाल WM2200_DSP1_CONTROL_30:
	हाल WM2200_DSP1_CONTROL_31:
	हाल WM2200_DSP2_CONTROL_1:
	हाल WM2200_DSP2_CONTROL_2:
	हाल WM2200_DSP2_CONTROL_3:
	हाल WM2200_DSP2_CONTROL_4:
	हाल WM2200_DSP2_CONTROL_5:
	हाल WM2200_DSP2_CONTROL_6:
	हाल WM2200_DSP2_CONTROL_7:
	हाल WM2200_DSP2_CONTROL_8:
	हाल WM2200_DSP2_CONTROL_9:
	हाल WM2200_DSP2_CONTROL_10:
	हाल WM2200_DSP2_CONTROL_11:
	हाल WM2200_DSP2_CONTROL_12:
	हाल WM2200_DSP2_CONTROL_13:
	हाल WM2200_DSP2_CONTROL_14:
	हाल WM2200_DSP2_CONTROL_15:
	हाल WM2200_DSP2_CONTROL_16:
	हाल WM2200_DSP2_CONTROL_17:
	हाल WM2200_DSP2_CONTROL_18:
	हाल WM2200_DSP2_CONTROL_19:
	हाल WM2200_DSP2_CONTROL_20:
	हाल WM2200_DSP2_CONTROL_21:
	हाल WM2200_DSP2_CONTROL_22:
	हाल WM2200_DSP2_CONTROL_23:
	हाल WM2200_DSP2_CONTROL_24:
	हाल WM2200_DSP2_CONTROL_25:
	हाल WM2200_DSP2_CONTROL_26:
	हाल WM2200_DSP2_CONTROL_27:
	हाल WM2200_DSP2_CONTROL_28:
	हाल WM2200_DSP2_CONTROL_29:
	हाल WM2200_DSP2_CONTROL_30:
	हाल WM2200_DSP2_CONTROL_31:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_sequence wm2200_reva_patch[] = अणु
	अणु 0x07, 0x0003 पूर्ण,
	अणु 0x102, 0x0200 पूर्ण,
	अणु 0x203, 0x0084 पूर्ण,
	अणु 0x201, 0x83FF पूर्ण,
	अणु 0x20C, 0x0062 पूर्ण,
	अणु 0x20D, 0x0062 पूर्ण,
	अणु 0x207, 0x2002 पूर्ण,
	अणु 0x208, 0x20C0 पूर्ण,
	अणु 0x21D, 0x01C0 पूर्ण,
	अणु 0x50A, 0x0001 पूर्ण,
	अणु 0x50B, 0x0002 पूर्ण,
	अणु 0x50C, 0x0003 पूर्ण,
	अणु 0x50D, 0x0004 पूर्ण,
	अणु 0x50E, 0x0005 पूर्ण,
	अणु 0x510, 0x0001 पूर्ण,
	अणु 0x511, 0x0002 पूर्ण,
	अणु 0x512, 0x0003 पूर्ण,
	अणु 0x513, 0x0004 पूर्ण,
	अणु 0x514, 0x0005 पूर्ण,
	अणु 0x515, 0x0000 पूर्ण,
	अणु 0x201, 0x8084 पूर्ण,
	अणु 0x202, 0xBBDE पूर्ण,
	अणु 0x203, 0x00EC पूर्ण,
	अणु 0x500, 0x8000 पूर्ण,
	अणु 0x507, 0x1820 पूर्ण,
	अणु 0x508, 0x1820 पूर्ण,
	अणु 0x505, 0x0300 पूर्ण,
	अणु 0x506, 0x0300 पूर्ण,
	अणु 0x302, 0x2280 पूर्ण,
	अणु 0x303, 0x0080 पूर्ण,
	अणु 0x304, 0x2280 पूर्ण,
	अणु 0x305, 0x0080 पूर्ण,
	अणु 0x306, 0x2280 पूर्ण,
	अणु 0x307, 0x0080 पूर्ण,
	अणु 0x401, 0x0080 पूर्ण,
	अणु 0x402, 0x0080 पूर्ण,
	अणु 0x417, 0x3069 पूर्ण,
	अणु 0x900, 0x6318 पूर्ण,
	अणु 0x901, 0x6300 पूर्ण,
	अणु 0x902, 0x0FC8 पूर्ण,
	अणु 0x903, 0x03FE पूर्ण,
	अणु 0x904, 0x00E0 पूर्ण,
	अणु 0x905, 0x1EC4 पूर्ण,
	अणु 0x906, 0xF136 पूर्ण,
	अणु 0x907, 0x0409 पूर्ण,
	अणु 0x908, 0x04CC पूर्ण,
	अणु 0x909, 0x1C9B पूर्ण,
	अणु 0x90A, 0xF337 पूर्ण,
	अणु 0x90B, 0x040B पूर्ण,
	अणु 0x90C, 0x0CBB पूर्ण,
	अणु 0x90D, 0x16F8 पूर्ण,
	अणु 0x90E, 0xF7D9 पूर्ण,
	अणु 0x90F, 0x040A पूर्ण,
	अणु 0x910, 0x1F14 पूर्ण,
	अणु 0x911, 0x058C पूर्ण,
	अणु 0x912, 0x0563 पूर्ण,
	अणु 0x913, 0x4000 पूर्ण,
	अणु 0x916, 0x6318 पूर्ण,
	अणु 0x917, 0x6300 पूर्ण,
	अणु 0x918, 0x0FC8 पूर्ण,
	अणु 0x919, 0x03FE पूर्ण,
	अणु 0x91A, 0x00E0 पूर्ण,
	अणु 0x91B, 0x1EC4 पूर्ण,
	अणु 0x91C, 0xF136 पूर्ण,
	अणु 0x91D, 0x0409 पूर्ण,
	अणु 0x91E, 0x04CC पूर्ण,
	अणु 0x91F, 0x1C9B पूर्ण,
	अणु 0x920, 0xF337 पूर्ण,
	अणु 0x921, 0x040B पूर्ण,
	अणु 0x922, 0x0CBB पूर्ण,
	अणु 0x923, 0x16F8 पूर्ण,
	अणु 0x924, 0xF7D9 पूर्ण,
	अणु 0x925, 0x040A पूर्ण,
	अणु 0x926, 0x1F14 पूर्ण,
	अणु 0x927, 0x058C पूर्ण,
	अणु 0x928, 0x0563 पूर्ण,
	अणु 0x929, 0x4000 पूर्ण,
	अणु 0x709, 0x2000 पूर्ण,
	अणु 0x207, 0x200E पूर्ण,
	अणु 0x208, 0x20D4 पूर्ण,
	अणु 0x20A, 0x0080 पूर्ण,
	अणु 0x07, 0x0000 पूर्ण,
पूर्ण;

अटल पूर्णांक wm2200_reset(काष्ठा wm2200_priv *wm2200)
अणु
	अगर (wm2200->pdata.reset) अणु
		gpio_set_value_cansleep(wm2200->pdata.reset, 0);
		gpio_set_value_cansleep(wm2200->pdata.reset, 1);

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस regmap_ग_लिखो(wm2200->regmap, WM2200_SOFTWARE_RESET,
				    0x2200);
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(in_tlv, -6300, 100, 0);
अटल DECLARE_TLV_DB_SCALE(digital_tlv, -6400, 50, 0);
अटल DECLARE_TLV_DB_SCALE(out_tlv, -6400, 100, 0);

अटल स्थिर अक्षर * स्थिर wm2200_mixer_texts[] = अणु
	"None",
	"Tone Generator",
	"AEC Loopback",
	"IN1L",
	"IN1R",
	"IN2L",
	"IN2R",
	"IN3L",
	"IN3R",
	"AIF1RX1",
	"AIF1RX2",
	"AIF1RX3",
	"AIF1RX4",
	"AIF1RX5",
	"AIF1RX6",
	"EQL",
	"EQR",
	"LHPF1",
	"LHPF2",
	"DSP1.1",
	"DSP1.2",
	"DSP1.3",
	"DSP1.4",
	"DSP1.5",
	"DSP1.6",
	"DSP2.1",
	"DSP2.2",
	"DSP2.3",
	"DSP2.4",
	"DSP2.5",
	"DSP2.6",
पूर्ण;

अटल अचिन्हित पूर्णांक wm2200_mixer_values[] = अणु
	0x00,
	0x04,   /* Tone */
	0x08,   /* AEC */
	0x10,   /* Input */
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x20,   /* AIF */
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x50,   /* EQ */
	0x51,
	0x60,   /* LHPF1 */
	0x61,   /* LHPF2 */
	0x68,   /* DSP1 */
	0x69,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x70,   /* DSP2 */
	0x71,
	0x72,
	0x73,
	0x74,
	0x75,
पूर्ण;

#घोषणा WM2200_MIXER_CONTROLS(name, base) \
	SOC_SINGLE_TLV(name " Input 1 Volume", base + 1 , \
		       WM2200_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 2 Volume", base + 3 , \
		       WM2200_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 3 Volume", base + 5 , \
		       WM2200_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 4 Volume", base + 7 , \
		       WM2200_MIXER_VOL_SHIFT, 80, 0, mixer_tlv)

#घोषणा WM2200_MUX_ENUM_DECL(name, reg) \
	SOC_VALUE_ENUM_SINGLE_DECL(name, reg, 0, 0xff, 			\
				   wm2200_mixer_texts, wm2200_mixer_values)

#घोषणा WM2200_MUX_CTL_DECL(name) \
	स्थिर काष्ठा snd_kcontrol_new name##_mux =	\
		SOC_DAPM_ENUM("Route", name##_क्रमागत)

#घोषणा WM2200_MIXER_ENUMS(name, base_reg) \
	अटल WM2200_MUX_ENUM_DECL(name##_in1_क्रमागत, base_reg);	     \
	अटल WM2200_MUX_ENUM_DECL(name##_in2_क्रमागत, base_reg + 2);  \
	अटल WM2200_MUX_ENUM_DECL(name##_in3_क्रमागत, base_reg + 4);  \
	अटल WM2200_MUX_ENUM_DECL(name##_in4_क्रमागत, base_reg + 6);  \
	अटल WM2200_MUX_CTL_DECL(name##_in1); \
	अटल WM2200_MUX_CTL_DECL(name##_in2); \
	अटल WM2200_MUX_CTL_DECL(name##_in3); \
	अटल WM2200_MUX_CTL_DECL(name##_in4)

#घोषणा WM2200_DSP_ENUMS(name, base_reg) \
	अटल WM2200_MUX_ENUM_DECL(name##_aux1_क्रमागत, base_reg);     \
	अटल WM2200_MUX_ENUM_DECL(name##_aux2_क्रमागत, base_reg + 1); \
	अटल WM2200_MUX_ENUM_DECL(name##_aux3_क्रमागत, base_reg + 2); \
	अटल WM2200_MUX_ENUM_DECL(name##_aux4_क्रमागत, base_reg + 3); \
	अटल WM2200_MUX_ENUM_DECL(name##_aux5_क्रमागत, base_reg + 4); \
	अटल WM2200_MUX_ENUM_DECL(name##_aux6_क्रमागत, base_reg + 5); \
	अटल WM2200_MUX_CTL_DECL(name##_aux1); \
	अटल WM2200_MUX_CTL_DECL(name##_aux2); \
	अटल WM2200_MUX_CTL_DECL(name##_aux3); \
	अटल WM2200_MUX_CTL_DECL(name##_aux4); \
	अटल WM2200_MUX_CTL_DECL(name##_aux5); \
	अटल WM2200_MUX_CTL_DECL(name##_aux6);

अटल स्थिर अक्षर *wm2200_rxanc_input_sel_texts[] = अणु
	"None", "IN1", "IN2", "IN3",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm2200_rxanc_input_sel,
			    WM2200_RXANC_SRC,
			    WM2200_IN_RXANC_SEL_SHIFT,
			    wm2200_rxanc_input_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new wm2200_snd_controls[] = अणु
SOC_SINGLE("IN1 High Performance Switch", WM2200_IN1L_CONTROL,
	   WM2200_IN1_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN2 High Performance Switch", WM2200_IN2L_CONTROL,
	   WM2200_IN2_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN3 High Performance Switch", WM2200_IN3L_CONTROL,
	   WM2200_IN3_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R_TLV("IN1 Volume", WM2200_IN1L_CONTROL, WM2200_IN1R_CONTROL,
		 WM2200_IN1L_PGA_VOL_SHIFT, 0x5f, 0, in_tlv),
SOC_DOUBLE_R_TLV("IN2 Volume", WM2200_IN2L_CONTROL, WM2200_IN2R_CONTROL,
		 WM2200_IN2L_PGA_VOL_SHIFT, 0x5f, 0, in_tlv),
SOC_DOUBLE_R_TLV("IN3 Volume", WM2200_IN3L_CONTROL, WM2200_IN3R_CONTROL,
		 WM2200_IN3L_PGA_VOL_SHIFT, 0x5f, 0, in_tlv),

SOC_DOUBLE_R("IN1 Digital Switch", WM2200_ADC_DIGITAL_VOLUME_1L,
	     WM2200_ADC_DIGITAL_VOLUME_1R, WM2200_IN1L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("IN2 Digital Switch", WM2200_ADC_DIGITAL_VOLUME_2L,
	     WM2200_ADC_DIGITAL_VOLUME_2R, WM2200_IN2L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("IN3 Digital Switch", WM2200_ADC_DIGITAL_VOLUME_3L,
	     WM2200_ADC_DIGITAL_VOLUME_3R, WM2200_IN3L_MUTE_SHIFT, 1, 1),

SOC_DOUBLE_R_TLV("IN1 Digital Volume", WM2200_ADC_DIGITAL_VOLUME_1L,
		 WM2200_ADC_DIGITAL_VOLUME_1R, WM2200_IN1L_DIG_VOL_SHIFT,
		 0xbf, 0, digital_tlv),
SOC_DOUBLE_R_TLV("IN2 Digital Volume", WM2200_ADC_DIGITAL_VOLUME_2L,
		 WM2200_ADC_DIGITAL_VOLUME_2R, WM2200_IN2L_DIG_VOL_SHIFT,
		 0xbf, 0, digital_tlv),
SOC_DOUBLE_R_TLV("IN3 Digital Volume", WM2200_ADC_DIGITAL_VOLUME_3L,
		 WM2200_ADC_DIGITAL_VOLUME_3R, WM2200_IN3L_DIG_VOL_SHIFT,
		 0xbf, 0, digital_tlv),

SND_SOC_BYTES_MASK("EQL Coefficients", WM2200_EQL_1, 20, WM2200_EQL_ENA),
SND_SOC_BYTES_MASK("EQR Coefficients", WM2200_EQR_1, 20, WM2200_EQR_ENA),

SND_SOC_BYTES("LHPF1 Coefficients", WM2200_HPLPF1_2, 1),
SND_SOC_BYTES("LHPF2 Coefficients", WM2200_HPLPF2_2, 1),

SOC_SINGLE("OUT1 High Performance Switch", WM2200_DAC_DIGITAL_VOLUME_1L,
	   WM2200_OUT1_OSR_SHIFT, 1, 0),
SOC_SINGLE("OUT2 High Performance Switch", WM2200_DAC_DIGITAL_VOLUME_2L,
	   WM2200_OUT2_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R("OUT1 Digital Switch", WM2200_DAC_DIGITAL_VOLUME_1L,
	     WM2200_DAC_DIGITAL_VOLUME_1R, WM2200_OUT1L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R_TLV("OUT1 Digital Volume", WM2200_DAC_DIGITAL_VOLUME_1L,
		 WM2200_DAC_DIGITAL_VOLUME_1R, WM2200_OUT1L_VOL_SHIFT, 0x9f, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("OUT1 Volume", WM2200_DAC_VOLUME_LIMIT_1L,
		 WM2200_DAC_VOLUME_LIMIT_1R, WM2200_OUT1L_PGA_VOL_SHIFT,
		 0x46, 0, out_tlv),

SOC_DOUBLE_R("OUT2 Digital Switch", WM2200_DAC_DIGITAL_VOLUME_2L,
	     WM2200_DAC_DIGITAL_VOLUME_2R, WM2200_OUT2L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R_TLV("OUT2 Digital Volume", WM2200_DAC_DIGITAL_VOLUME_2L,
		 WM2200_DAC_DIGITAL_VOLUME_2R, WM2200_OUT2L_VOL_SHIFT, 0x9f, 0,
		 digital_tlv),
SOC_DOUBLE("OUT2 Switch", WM2200_PDM_1, WM2200_SPK1L_MUTE_SHIFT,
	   WM2200_SPK1R_MUTE_SHIFT, 1, 1),
SOC_ENUM("RxANC Src", wm2200_rxanc_input_sel),

WM_ADSP_FW_CONTROL("DSP1", 0),
WM_ADSP_FW_CONTROL("DSP2", 1),
पूर्ण;

WM2200_MIXER_ENUMS(OUT1L, WM2200_OUT1LMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(OUT1R, WM2200_OUT1RMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(OUT2L, WM2200_OUT2LMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(OUT2R, WM2200_OUT2RMIX_INPUT_1_SOURCE);

WM2200_MIXER_ENUMS(AIF1TX1, WM2200_AIF1TX1MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(AIF1TX2, WM2200_AIF1TX2MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(AIF1TX3, WM2200_AIF1TX3MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(AIF1TX4, WM2200_AIF1TX4MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(AIF1TX5, WM2200_AIF1TX5MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(AIF1TX6, WM2200_AIF1TX6MIX_INPUT_1_SOURCE);

WM2200_MIXER_ENUMS(EQL, WM2200_EQLMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(EQR, WM2200_EQRMIX_INPUT_1_SOURCE);

WM2200_MIXER_ENUMS(DSP1L, WM2200_DSP1LMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(DSP1R, WM2200_DSP1RMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(DSP2L, WM2200_DSP2LMIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(DSP2R, WM2200_DSP2RMIX_INPUT_1_SOURCE);

WM2200_DSP_ENUMS(DSP1, WM2200_DSP1AUX1MIX_INPUT_1_SOURCE);
WM2200_DSP_ENUMS(DSP2, WM2200_DSP2AUX1MIX_INPUT_1_SOURCE);

WM2200_MIXER_ENUMS(LHPF1, WM2200_LHPF1MIX_INPUT_1_SOURCE);
WM2200_MIXER_ENUMS(LHPF2, WM2200_LHPF2MIX_INPUT_1_SOURCE);

#घोषणा WM2200_MUX(name, ctrl) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctrl)

#घोषणा WM2200_MIXER_WIDGETS(name, name_str)	\
	WM2200_MUX(name_str " Input 1", &name##_in1_mux), \
	WM2200_MUX(name_str " Input 2", &name##_in2_mux), \
	WM2200_MUX(name_str " Input 3", &name##_in3_mux), \
	WM2200_MUX(name_str " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXER(name_str " Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0)

#घोषणा WM2200_DSP_WIDGETS(name, name_str) \
	WM2200_MIXER_WIDGETS(name##L, name_str "L"), \
	WM2200_MIXER_WIDGETS(name##R, name_str "R"), \
	WM2200_MUX(name_str " Aux 1", &name##_aux1_mux), \
	WM2200_MUX(name_str " Aux 2", &name##_aux2_mux), \
	WM2200_MUX(name_str " Aux 3", &name##_aux3_mux), \
	WM2200_MUX(name_str " Aux 4", &name##_aux4_mux), \
	WM2200_MUX(name_str " Aux 5", &name##_aux5_mux), \
	WM2200_MUX(name_str " Aux 6", &name##_aux6_mux)

#घोषणा WM2200_MIXER_INPUT_ROUTES(name)	\
	अणु name, "Tone Generator", "Tone Generator" पूर्ण, \
	अणु name, "AEC Loopback", "AEC Loopback" पूर्ण, \
        अणु name, "IN1L", "IN1L PGA" पूर्ण, \
        अणु name, "IN1R", "IN1R PGA" पूर्ण, \
        अणु name, "IN2L", "IN2L PGA" पूर्ण, \
        अणु name, "IN2R", "IN2R PGA" पूर्ण, \
        अणु name, "IN3L", "IN3L PGA" पूर्ण, \
        अणु name, "IN3R", "IN3R PGA" पूर्ण, \
        अणु name, "DSP1.1", "DSP1" पूर्ण, \
        अणु name, "DSP1.2", "DSP1" पूर्ण, \
        अणु name, "DSP1.3", "DSP1" पूर्ण, \
        अणु name, "DSP1.4", "DSP1" पूर्ण, \
        अणु name, "DSP1.5", "DSP1" पूर्ण, \
        अणु name, "DSP1.6", "DSP1" पूर्ण, \
        अणु name, "DSP2.1", "DSP2" पूर्ण, \
        अणु name, "DSP2.2", "DSP2" पूर्ण, \
        अणु name, "DSP2.3", "DSP2" पूर्ण, \
        अणु name, "DSP2.4", "DSP2" पूर्ण, \
        अणु name, "DSP2.5", "DSP2" पूर्ण, \
        अणु name, "DSP2.6", "DSP2" पूर्ण, \
        अणु name, "AIF1RX1", "AIF1RX1" पूर्ण, \
        अणु name, "AIF1RX2", "AIF1RX2" पूर्ण, \
        अणु name, "AIF1RX3", "AIF1RX3" पूर्ण, \
        अणु name, "AIF1RX4", "AIF1RX4" पूर्ण, \
        अणु name, "AIF1RX5", "AIF1RX5" पूर्ण, \
        अणु name, "AIF1RX6", "AIF1RX6" पूर्ण, \
        अणु name, "EQL", "EQL" पूर्ण, \
        अणु name, "EQR", "EQR" पूर्ण, \
        अणु name, "LHPF1", "LHPF1" पूर्ण, \
        अणु name, "LHPF2", "LHPF2" पूर्ण

#घोषणा WM2200_MIXER_ROUTES(widget, name) \
	अणु widget, शून्य, name " Mixer" पूर्ण,         \
	अणु name " Mixer", शून्य, name " Input 1" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 2" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 3" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 4" पूर्ण, \
	WM2200_MIXER_INPUT_ROUTES(name " Input 1"), \
	WM2200_MIXER_INPUT_ROUTES(name " Input 2"), \
	WM2200_MIXER_INPUT_ROUTES(name " Input 3"), \
	WM2200_MIXER_INPUT_ROUTES(name " Input 4")

#घोषणा WM2200_DSP_AUX_ROUTES(name) \
	अणु name, शून्य, name " Aux 1" पूर्ण, \
	अणु name, शून्य, name " Aux 2" पूर्ण, \
	अणु name, शून्य, name " Aux 3" पूर्ण, \
	अणु name, शून्य, name " Aux 4" पूर्ण, \
	अणु name, शून्य, name " Aux 5" पूर्ण, \
	अणु name, शून्य, name " Aux 6" पूर्ण, \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 1"), \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 2"), \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 3"), \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 4"), \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 5"), \
	WM2200_MIXER_INPUT_ROUTES(name " Aux 6")

अटल स्थिर अक्षर *wm2200_aec_loopback_texts[] = अणु
	"OUT1L", "OUT1R", "OUT2L", "OUT2R",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm2200_aec_loopback,
			    WM2200_DAC_AEC_CONTROL_1,
			    WM2200_AEC_LOOPBACK_SRC_SHIFT,
			    wm2200_aec_loopback_texts);

अटल स्थिर काष्ठा snd_kcontrol_new wm2200_aec_loopback_mux =
	SOC_DAPM_ENUM("AEC Loopback", wm2200_aec_loopback);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm2200_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", WM2200_CLOCKING_3, WM2200_SYSCLK_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("CP1", WM2200_DM_CHARGE_PUMP_1, WM2200_CPDM_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("CP2", WM2200_MIC_CHARGE_PUMP_1, WM2200_CPMIC_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1", WM2200_MIC_BIAS_CTRL_1, WM2200_MICB1_ENA_SHIFT,
		    0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2", WM2200_MIC_BIAS_CTRL_2, WM2200_MICB2_ENA_SHIFT,
		    0, शून्य, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("AVDD", 20, 0),

SND_SOC_DAPM_INPUT("IN1L"),
SND_SOC_DAPM_INPUT("IN1R"),
SND_SOC_DAPM_INPUT("IN2L"),
SND_SOC_DAPM_INPUT("IN2R"),
SND_SOC_DAPM_INPUT("IN3L"),
SND_SOC_DAPM_INPUT("IN3R"),

SND_SOC_DAPM_SIGGEN("TONE"),
SND_SOC_DAPM_PGA("Tone Generator", WM2200_TONE_GENERATOR_1,
		 WM2200_TONE_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("IN1L PGA", WM2200_INPUT_ENABLES, WM2200_IN1L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("IN1R PGA", WM2200_INPUT_ENABLES, WM2200_IN1R_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("IN2L PGA", WM2200_INPUT_ENABLES, WM2200_IN2L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("IN2R PGA", WM2200_INPUT_ENABLES, WM2200_IN2R_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("IN3L PGA", WM2200_INPUT_ENABLES, WM2200_IN3L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("IN3R PGA", WM2200_INPUT_ENABLES, WM2200_IN3R_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_AIF_IN("AIF1RX1", "Playback", 0,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX2", "Playback", 1,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX3", "Playback", 2,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX4", "Playback", 3,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX5", "Playback", 4,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX6", "Playback", 5,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1RX6_ENA_SHIFT, 0),

SND_SOC_DAPM_PGA("EQL", WM2200_EQL_1, WM2200_EQL_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQR", WM2200_EQR_1, WM2200_EQR_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("LHPF1", WM2200_HPLPF1_1, WM2200_LHPF1_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF2", WM2200_HPLPF2_1, WM2200_LHPF2_ENA_SHIFT, 0,
		 शून्य, 0),

WM_ADSP1("DSP1", 0),
WM_ADSP1("DSP2", 1),

SND_SOC_DAPM_AIF_OUT("AIF1TX1", "Capture", 0,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX2", "Capture", 1,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX3", "Capture", 2,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX4", "Capture", 3,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX5", "Capture", 4,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX6", "Capture", 5,
		    WM2200_AUDIO_IF_1_22, WM2200_AIF1TX6_ENA_SHIFT, 0),

SND_SOC_DAPM_MUX("AEC Loopback", WM2200_DAC_AEC_CONTROL_1,
		 WM2200_AEC_LOOPBACK_ENA_SHIFT, 0, &wm2200_aec_loopback_mux),

SND_SOC_DAPM_PGA_S("OUT1L", 0, WM2200_OUTPUT_ENABLES,
		   WM2200_OUT1L_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("OUT1R", 0, WM2200_OUTPUT_ENABLES,
		   WM2200_OUT1R_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("EPD_LP", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_LP_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_OUTP_LP", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_OUTP_LP_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_RMV_SHRT_LP", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_RMV_SHRT_LP_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("EPD_LN", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_LN_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_OUTP_LN", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_OUTP_LN_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_RMV_SHRT_LN", 1, WM2200_EAR_PIECE_CTRL_1,
		   WM2200_EPD_RMV_SHRT_LN_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("EPD_RP", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_RP_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_OUTP_RP", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_OUTP_RP_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_RMV_SHRT_RP", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_RMV_SHRT_RP_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("EPD_RN", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_RN_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_OUTP_RN", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_OUTP_RN_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("EPD_RMV_SHRT_RN", 1, WM2200_EAR_PIECE_CTRL_2,
		   WM2200_EPD_RMV_SHRT_RN_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("OUT2L", WM2200_OUTPUT_ENABLES, WM2200_OUT2L_ENA_SHIFT,
		 0, शून्य, 0),
SND_SOC_DAPM_PGA("OUT2R", WM2200_OUTPUT_ENABLES, WM2200_OUT2R_ENA_SHIFT,
		 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("EPOUTLN"),
SND_SOC_DAPM_OUTPUT("EPOUTLP"),
SND_SOC_DAPM_OUTPUT("EPOUTRN"),
SND_SOC_DAPM_OUTPUT("EPOUTRP"),
SND_SOC_DAPM_OUTPUT("SPK"),

WM2200_MIXER_WIDGETS(EQL, "EQL"),
WM2200_MIXER_WIDGETS(EQR, "EQR"),

WM2200_MIXER_WIDGETS(LHPF1, "LHPF1"),
WM2200_MIXER_WIDGETS(LHPF2, "LHPF2"),

WM2200_DSP_WIDGETS(DSP1, "DSP1"),
WM2200_DSP_WIDGETS(DSP2, "DSP2"),

WM2200_MIXER_WIDGETS(AIF1TX1, "AIF1TX1"),
WM2200_MIXER_WIDGETS(AIF1TX2, "AIF1TX2"),
WM2200_MIXER_WIDGETS(AIF1TX3, "AIF1TX3"),
WM2200_MIXER_WIDGETS(AIF1TX4, "AIF1TX4"),
WM2200_MIXER_WIDGETS(AIF1TX5, "AIF1TX5"),
WM2200_MIXER_WIDGETS(AIF1TX6, "AIF1TX6"),

WM2200_MIXER_WIDGETS(OUT1L, "OUT1L"),
WM2200_MIXER_WIDGETS(OUT1R, "OUT1R"),
WM2200_MIXER_WIDGETS(OUT2L, "OUT2L"),
WM2200_MIXER_WIDGETS(OUT2R, "OUT2R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm2200_dapm_routes[] = अणु
	/* Everything needs SYSCLK but only hook up things on the edge
	 * of the chip */
	अणु "IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2R", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX3", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX4", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX5", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX6", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX3", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX4", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX5", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX6", शून्य, "SYSCLK" पूर्ण,

	अणु "IN1L", शून्य, "AVDD" पूर्ण,
	अणु "IN1R", शून्य, "AVDD" पूर्ण,
	अणु "IN2L", शून्य, "AVDD" पूर्ण,
	अणु "IN2R", शून्य, "AVDD" पूर्ण,
	अणु "IN3L", शून्य, "AVDD" पूर्ण,
	अणु "IN3R", शून्य, "AVDD" पूर्ण,
	अणु "OUT1L", शून्य, "AVDD" पूर्ण,
	अणु "OUT1R", शून्य, "AVDD" पूर्ण,

	अणु "IN1L PGA", शून्य, "IN1L" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN1R" पूर्ण,
	अणु "IN2L PGA", शून्य, "IN2L" पूर्ण,
	अणु "IN2R PGA", शून्य, "IN2R" पूर्ण,
	अणु "IN3L PGA", शून्य, "IN3L" पूर्ण,
	अणु "IN3R PGA", शून्य, "IN3R" पूर्ण,

	अणु "Tone Generator", शून्य, "TONE" पूर्ण,

	अणु "CP2", शून्य, "CPVDD" पूर्ण,
	अणु "MICBIAS1", शून्य, "CP2" पूर्ण,
	अणु "MICBIAS2", शून्य, "CP2" पूर्ण,

	अणु "CP1", शून्य, "CPVDD" पूर्ण,
	अणु "EPD_LN", शून्य, "CP1" पूर्ण,
	अणु "EPD_LP", शून्य, "CP1" पूर्ण,
	अणु "EPD_RN", शून्य, "CP1" पूर्ण,
	अणु "EPD_RP", शून्य, "CP1" पूर्ण,

	अणु "EPD_LP", शून्य, "OUT1L" पूर्ण,
	अणु "EPD_OUTP_LP", शून्य, "EPD_LP" पूर्ण,
	अणु "EPD_RMV_SHRT_LP", शून्य, "EPD_OUTP_LP" पूर्ण,
	अणु "EPOUTLP", शून्य, "EPD_RMV_SHRT_LP" पूर्ण,

	अणु "EPD_LN", शून्य, "OUT1L" पूर्ण,
	अणु "EPD_OUTP_LN", शून्य, "EPD_LN" पूर्ण,
	अणु "EPD_RMV_SHRT_LN", शून्य, "EPD_OUTP_LN" पूर्ण,
	अणु "EPOUTLN", शून्य, "EPD_RMV_SHRT_LN" पूर्ण,

	अणु "EPD_RP", शून्य, "OUT1R" पूर्ण,
	अणु "EPD_OUTP_RP", शून्य, "EPD_RP" पूर्ण,
	अणु "EPD_RMV_SHRT_RP", शून्य, "EPD_OUTP_RP" पूर्ण,
	अणु "EPOUTRP", शून्य, "EPD_RMV_SHRT_RP" पूर्ण,

	अणु "EPD_RN", शून्य, "OUT1R" पूर्ण,
	अणु "EPD_OUTP_RN", शून्य, "EPD_RN" पूर्ण,
	अणु "EPD_RMV_SHRT_RN", शून्य, "EPD_OUTP_RN" पूर्ण,
	अणु "EPOUTRN", शून्य, "EPD_RMV_SHRT_RN" पूर्ण,

	अणु "SPK", शून्य, "OUT2L" पूर्ण,
	अणु "SPK", शून्य, "OUT2R" पूर्ण,

	अणु "AEC Loopback", "OUT1L", "OUT1L" पूर्ण,
	अणु "AEC Loopback", "OUT1R", "OUT1R" पूर्ण,
	अणु "AEC Loopback", "OUT2L", "OUT2L" पूर्ण,
	अणु "AEC Loopback", "OUT2R", "OUT2R" पूर्ण,

	WM2200_MIXER_ROUTES("DSP1", "DSP1L"),
	WM2200_MIXER_ROUTES("DSP1", "DSP1R"),
	WM2200_MIXER_ROUTES("DSP2", "DSP2L"),
	WM2200_MIXER_ROUTES("DSP2", "DSP2R"),

	WM2200_DSP_AUX_ROUTES("DSP1"),
	WM2200_DSP_AUX_ROUTES("DSP2"),

	WM2200_MIXER_ROUTES("OUT1L", "OUT1L"),
	WM2200_MIXER_ROUTES("OUT1R", "OUT1R"),
	WM2200_MIXER_ROUTES("OUT2L", "OUT2L"),
	WM2200_MIXER_ROUTES("OUT2R", "OUT2R"),

	WM2200_MIXER_ROUTES("AIF1TX1", "AIF1TX1"),
	WM2200_MIXER_ROUTES("AIF1TX2", "AIF1TX2"),
	WM2200_MIXER_ROUTES("AIF1TX3", "AIF1TX3"),
	WM2200_MIXER_ROUTES("AIF1TX4", "AIF1TX4"),
	WM2200_MIXER_ROUTES("AIF1TX5", "AIF1TX5"),
	WM2200_MIXER_ROUTES("AIF1TX6", "AIF1TX6"),

	WM2200_MIXER_ROUTES("EQL", "EQL"),
	WM2200_MIXER_ROUTES("EQR", "EQR"),

	WM2200_MIXER_ROUTES("LHPF1", "LHPF1"),
	WM2200_MIXER_ROUTES("LHPF2", "LHPF2"),
पूर्ण;

अटल पूर्णांक wm2200_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);

	wm2200->component = component;

	वापस 0;
पूर्ण

अटल पूर्णांक wm2200_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक lrclk, bclk, fmt_val;

	lrclk = 0;
	bclk = 0;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		fmt_val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		fmt_val = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported DAI format %d\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= WM2200_AIF1TX_LRCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		bclk |= WM2200_AIF1_BCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		lrclk |= WM2200_AIF1TX_LRCLK_MSTR;
		bclk |= WM2200_AIF1_BCLK_MSTR;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported master mode %d\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bclk |= WM2200_AIF1_BCLK_INV;
		lrclk |= WM2200_AIF1TX_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bclk |= WM2200_AIF1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk |= WM2200_AIF1TX_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_1, WM2200_AIF1_BCLK_MSTR |
			    WM2200_AIF1_BCLK_INV, bclk);
	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_2,
			    WM2200_AIF1TX_LRCLK_MSTR | WM2200_AIF1TX_LRCLK_INV,
			    lrclk);
	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_3,
			    WM2200_AIF1TX_LRCLK_MSTR | WM2200_AIF1TX_LRCLK_INV,
			    lrclk);
	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_5,
			    WM2200_AIF1_FMT_MASK, fmt_val);

	वापस 0;
पूर्ण

अटल पूर्णांक wm2200_sr_code[] = अणु
	0,
	12000,
	24000,
	48000,
	96000,
	192000,
	384000,
	768000,
	0,
	11025,
	22050,
	44100,
	88200,
	176400,
	352800,
	705600,
	4000,
	8000,
	16000,
	32000,
	64000,
	128000,
	256000,
	512000,
पूर्ण;

#घोषणा WM2200_NUM_BCLK_RATES 12

अटल पूर्णांक wm2200_bclk_rates_dat[WM2200_NUM_BCLK_RATES] = अणु
	6144000,
	3072000,
	2048000,
	1536000,
	768000,
	512000,
	384000,
	256000,
	192000,
	128000,
	96000,
	64000,
पूर्ण;	

अटल पूर्णांक wm2200_bclk_rates_cd[WM2200_NUM_BCLK_RATES] = अणु
	5644800,
	3763200,
	2882400,
	1881600,
	1411200,
	705600,
	470400,
	352800,
	176400,
	117600,
	88200,
	58800,
पूर्ण;

अटल पूर्णांक wm2200_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, bclk, lrclk, wl, fl, sr_code;
	पूर्णांक *bclk_rates;

	/* Data sizes अगर not using TDM */
	wl = params_width(params);
	अगर (wl < 0)
		वापस wl;
	fl = snd_soc_params_to_frame_size(params);
	अगर (fl < 0)
		वापस fl;

	dev_dbg(component->dev, "Word length %d bits, frame length %d bits\n",
		wl, fl);

	/* Target BCLK rate */
	bclk = snd_soc_params_to_bclk(params);
	अगर (bclk < 0)
		वापस bclk;

	अगर (!wm2200->sysclk) अणु
		dev_err(component->dev, "SYSCLK has no rate set\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm2200_sr_code); i++)
		अगर (wm2200_sr_code[i] == params_rate(params))
			अवरोध;
	अगर (i == ARRAY_SIZE(wm2200_sr_code)) अणु
		dev_err(component->dev, "Unsupported sample rate: %dHz\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण
	sr_code = i;

	dev_dbg(component->dev, "Target BCLK is %dHz, using %dHz SYSCLK\n",
		bclk, wm2200->sysclk);

	अगर (wm2200->sysclk % 4000)
		bclk_rates = wm2200_bclk_rates_cd;
	अन्यथा
		bclk_rates = wm2200_bclk_rates_dat;

	क्रम (i = 0; i < WM2200_NUM_BCLK_RATES; i++)
		अगर (bclk_rates[i] >= bclk && (bclk_rates[i] % bclk == 0))
			अवरोध;
	अगर (i == WM2200_NUM_BCLK_RATES) अणु
		dev_err(component->dev,
			"No valid BCLK for %dHz found from %dHz SYSCLK\n",
			bclk, wm2200->sysclk);
		वापस -EINVAL;
	पूर्ण

	bclk = i;
	dev_dbg(component->dev, "Setting %dHz BCLK\n", bclk_rates[bclk]);
	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_1,
			    WM2200_AIF1_BCLK_DIV_MASK, bclk);

	lrclk = bclk_rates[bclk] / params_rate(params);
	dev_dbg(component->dev, "Setting %dHz LRCLK\n", bclk_rates[bclk] / lrclk);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
	    wm2200->symmetric_rates)
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_7,
				    WM2200_AIF1RX_BCPF_MASK, lrclk);
	अन्यथा
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_6,
				    WM2200_AIF1TX_BCPF_MASK, lrclk);

	i = (wl << WM2200_AIF1TX_WL_SHIFT) | wl;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_9,
				    WM2200_AIF1RX_WL_MASK |
				    WM2200_AIF1RX_SLOT_LEN_MASK, i);
	अन्यथा
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_8,
				    WM2200_AIF1TX_WL_MASK |
				    WM2200_AIF1TX_SLOT_LEN_MASK, i);

	snd_soc_component_update_bits(component, WM2200_CLOCKING_4,
			    WM2200_SAMPLE_RATE_1_MASK, sr_code);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm2200_dai_ops = अणु
	.set_fmt = wm2200_set_fmt,
	.hw_params = wm2200_hw_params,
पूर्ण;

अटल पूर्णांक wm2200_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
			     पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	पूर्णांक fval;

	चयन (clk_id) अणु
	हाल WM2200_CLK_SYSCLK:
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	चयन (source) अणु
	हाल WM2200_CLKSRC_MCLK1:
	हाल WM2200_CLKSRC_MCLK2:
	हाल WM2200_CLKSRC_FLL:
	हाल WM2200_CLKSRC_BCLK1:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 22579200:
	हाल 24576000:
		fval = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock rate: %d\n", freq);
		वापस -EINVAL;
	पूर्ण

	/* TODO: Check अगर MCLKs are in use and enable/disable pulls to
	 * match.
	 */

	snd_soc_component_update_bits(component, WM2200_CLOCKING_3, WM2200_SYSCLK_FREQ_MASK |
			    WM2200_SYSCLK_SRC_MASK,
			    fval << WM2200_SYSCLK_FREQ_SHIFT | source);

	wm2200->sysclk = freq;

	वापस 0;
पूर्ण

काष्ठा _fll_भाग अणु
	u16 fll_fratio;
	u16 fll_outभाग;
	u16 fll_refclk_भाग;
	u16 n;
	u16 theta;
	u16 lambda;
पूर्ण;

अटल काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 fll_fratio;
	पूर्णांक ratio;
पूर्ण fll_fratios[] = अणु
	अणु       0,    64000, 4, 16 पूर्ण,
	अणु   64000,   128000, 3,  8 पूर्ण,
	अणु  128000,   256000, 2,  4 पूर्ण,
	अणु  256000,  1000000, 1,  2 पूर्ण,
	अणु 1000000, 13500000, 0,  1 पूर्ण,
पूर्ण;

अटल पूर्णांक fll_factors(काष्ठा _fll_भाग *fll_भाग, अचिन्हित पूर्णांक Fref,
		       अचिन्हित पूर्णांक Fout)
अणु
	अचिन्हित पूर्णांक target;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक fratio, gcd_fll;
	पूर्णांक i;

	/* Fref must be <=13.5MHz */
	भाग = 1;
	fll_भाग->fll_refclk_भाग = 0;
	जबतक ((Fref / भाग) > 13500000) अणु
		भाग *= 2;
		fll_भाग->fll_refclk_भाग++;

		अगर (भाग > 8) अणु
			pr_err("Can't scale %dMHz input down to <=13.5MHz\n",
			       Fref);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pr_debug("FLL Fref=%u Fout=%u\n", Fref, Fout);

	/* Apply the भागision क्रम our reमुख्यing calculations */
	Fref /= भाग;

	/* Fvco should be 90-100MHz; करोn't check the upper bound */
	भाग = 2;
	जबतक (Fout * भाग < 90000000) अणु
		भाग++;
		अगर (भाग > 64) अणु
			pr_err("Unable to find FLL_OUTDIV for Fout=%uHz\n",
			       Fout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	target = Fout * भाग;
	fll_भाग->fll_outभाग = भाग - 1;

	pr_debug("FLL Fvco=%dHz\n", target);

	/* Find an appropraite FLL_FRATIO and factor it out of the target */
	क्रम (i = 0; i < ARRAY_SIZE(fll_fratios); i++) अणु
		अगर (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) अणु
			fll_भाग->fll_fratio = fll_fratios[i].fll_fratio;
			fratio = fll_fratios[i].ratio;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_fratios)) अणु
		pr_err("Unable to find FLL_FRATIO for Fref=%uHz\n", Fref);
		वापस -EINVAL;
	पूर्ण

	fll_भाग->n = target / (fratio * Fref);

	अगर (target % Fref == 0) अणु
		fll_भाग->theta = 0;
		fll_भाग->lambda = 0;
	पूर्ण अन्यथा अणु
		gcd_fll = gcd(target, fratio * Fref);

		fll_भाग->theta = (target - (fll_भाग->n * fratio * Fref))
			/ gcd_fll;
		fll_भाग->lambda = (fratio * Fref) / gcd_fll;
	पूर्ण

	pr_debug("FLL N=%x THETA=%x LAMBDA=%x\n",
		 fll_भाग->n, fll_भाग->theta, fll_भाग->lambda);
	pr_debug("FLL_FRATIO=%x(%d) FLL_OUTDIV=%x FLL_REFCLK_DIV=%x\n",
		 fll_भाग->fll_fratio, fratio, fll_भाग->fll_outभाग,
		 fll_भाग->fll_refclk_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm2200_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	काष्ठा wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	काष्ठा _fll_भाग factors;
	पूर्णांक ret, i, समयout;
	अचिन्हित दीर्घ समय_left;

	अगर (!Fout) अणु
		dev_dbg(component->dev, "FLL disabled");

		अगर (wm2200->fll_fout)
			pm_runसमय_put(component->dev);

		wm2200->fll_fout = 0;
		snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_1,
				    WM2200_FLL_ENA, 0);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल WM2200_FLL_SRC_MCLK1:
	हाल WM2200_FLL_SRC_MCLK2:
	हाल WM2200_FLL_SRC_BCLK:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid FLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = fll_factors(&factors, Fref, Fout);
	अगर (ret < 0)
		वापस ret;

	/* Disable the FLL जबतक we reconfigure */
	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_1, WM2200_FLL_ENA, 0);

	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_2,
			    WM2200_FLL_OUTDIV_MASK | WM2200_FLL_FRATIO_MASK,
			    (factors.fll_outभाग << WM2200_FLL_OUTDIV_SHIFT) |
			    factors.fll_fratio);
	अगर (factors.theta) अणु
		snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_3,
				    WM2200_FLL_FRACN_ENA,
				    WM2200_FLL_FRACN_ENA);
		snd_soc_component_update_bits(component, WM2200_FLL_EFS_2,
				    WM2200_FLL_EFS_ENA,
				    WM2200_FLL_EFS_ENA);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_3,
				    WM2200_FLL_FRACN_ENA, 0);
		snd_soc_component_update_bits(component, WM2200_FLL_EFS_2,
				    WM2200_FLL_EFS_ENA, 0);
	पूर्ण

	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_4, WM2200_FLL_THETA_MASK,
			    factors.theta);
	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_6, WM2200_FLL_N_MASK,
			    factors.n);
	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_7,
			    WM2200_FLL_CLK_REF_DIV_MASK |
			    WM2200_FLL_CLK_REF_SRC_MASK,
			    (factors.fll_refclk_भाग
			     << WM2200_FLL_CLK_REF_DIV_SHIFT) | source);
	snd_soc_component_update_bits(component, WM2200_FLL_EFS_1,
			    WM2200_FLL_LAMBDA_MASK, factors.lambda);

	/* Clear any pending completions */
	try_रुको_क्रम_completion(&wm2200->fll_lock);

	pm_runसमय_get_sync(component->dev);

	snd_soc_component_update_bits(component, WM2200_FLL_CONTROL_1,
			    WM2200_FLL_ENA, WM2200_FLL_ENA);

	अगर (i2c->irq)
		समयout = 2;
	अन्यथा
		समयout = 50;

	snd_soc_component_update_bits(component, WM2200_CLOCKING_3, WM2200_SYSCLK_ENA,
			    WM2200_SYSCLK_ENA);

	/* Poll क्रम the lock; will use the पूर्णांकerrupt to निकास quickly */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर (i2c->irq) अणु
			समय_left = रुको_क्रम_completion_समयout(
							&wm2200->fll_lock,
							msecs_to_jअगरfies(25));
			अगर (समय_left > 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			msleep(1);
		पूर्ण

		ret = snd_soc_component_पढ़ो(component,
				   WM2200_INTERRUPT_RAW_STATUS_2);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to read FLL status: %d\n",
				ret);
			जारी;
		पूर्ण
		अगर (ret & WM2200_FLL_LOCK_STS)
			अवरोध;
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(component->dev, "FLL lock timed out\n");
		pm_runसमय_put(component->dev);
		वापस -ETIMEDOUT;
	पूर्ण

	wm2200->fll_src = source;
	wm2200->fll_fref = Fref;
	wm2200->fll_fout = Fout;

	dev_dbg(component->dev, "FLL running %dHz->%dHz\n", Fref, Fout);

	वापस 0;
पूर्ण

अटल पूर्णांक wm2200_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = snd_soc_component_पढ़ो(component, WM2200_GPIO_CTRL_1);
	अगर (ret >= 0) अणु
		अगर ((ret & WM2200_GP1_FN_MASK) != 0) अणु
			wm2200->symmetric_rates = true;
			val = WM2200_AIF1TX_LRCLK_SRC;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Failed to read GPIO 1 config: %d\n", ret);
	पूर्ण

	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_2,
			    WM2200_AIF1TX_LRCLK_SRC, val);

	वापस 0;
पूर्ण

#घोषणा WM2200_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा WM2200_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm2200_dai = अणु
	.name = "wm2200",
	.probe = wm2200_dai_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM2200_RATES,
		.क्रमmats = WM2200_FORMATS,
	पूर्ण,
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 2,
		 .channels_max = 2,
		 .rates = WM2200_RATES,
		 .क्रमmats = WM2200_FORMATS,
	 पूर्ण,
	.ops = &wm2200_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_wm2200 = अणु
	.probe			= wm2200_probe,
	.set_sysclk		= wm2200_set_sysclk,
	.set_pll		= wm2200_set_fll,
	.controls		= wm2200_snd_controls,
	.num_controls		= ARRAY_SIZE(wm2200_snd_controls),
	.dapm_widमाला_लो		= wm2200_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm2200_dapm_widमाला_लो),
	.dapm_routes		= wm2200_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm2200_dapm_routes),
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल irqवापस_t wm2200_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm2200_priv *wm2200 = data;
	अचिन्हित पूर्णांक val, mask;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm2200->regmap, WM2200_INTERRUPT_STATUS_2, &val);
	अगर (ret != 0) अणु
		dev_err(wm2200->dev, "Failed to read IRQ status: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(wm2200->regmap, WM2200_INTERRUPT_STATUS_2_MASK,
			   &mask);
	अगर (ret != 0) अणु
		dev_warn(wm2200->dev, "Failed to read IRQ mask: %d\n", ret);
		mask = 0;
	पूर्ण

	val &= ~mask;

	अगर (val & WM2200_FLL_LOCK_EINT) अणु
		dev_dbg(wm2200->dev, "FLL locked\n");
		complete(&wm2200->fll_lock);
	पूर्ण

	अगर (val) अणु
		regmap_ग_लिखो(wm2200->regmap, WM2200_INTERRUPT_STATUS_2, val);
		
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config wm2200_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.max_रेजिस्टर = WM2200_MAX_REGISTER + (ARRAY_SIZE(wm2200_ranges) *
					       WM2200_DSP_SPACING),
	.reg_शेषs = wm2200_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm2200_reg_शेषs),
	.अस्थिर_reg = wm2200_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm2200_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.ranges = wm2200_ranges,
	.num_ranges = ARRAY_SIZE(wm2200_ranges),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm2200_dig_vu[] = अणु
	WM2200_DAC_DIGITAL_VOLUME_1L,
	WM2200_DAC_DIGITAL_VOLUME_1R,
	WM2200_DAC_DIGITAL_VOLUME_2L,
	WM2200_DAC_DIGITAL_VOLUME_2R,
	WM2200_ADC_DIGITAL_VOLUME_1L,
	WM2200_ADC_DIGITAL_VOLUME_1R,
	WM2200_ADC_DIGITAL_VOLUME_2L,
	WM2200_ADC_DIGITAL_VOLUME_2R,
	WM2200_ADC_DIGITAL_VOLUME_3L,
	WM2200_ADC_DIGITAL_VOLUME_3R,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm2200_mic_ctrl_reg[] = अणु
	WM2200_IN1L_CONTROL,
	WM2200_IN2L_CONTROL,
	WM2200_IN3L_CONTROL,
पूर्ण;

अटल पूर्णांक wm2200_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm2200_pdata *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा wm2200_priv *wm2200;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, i;
	पूर्णांक val;

	wm2200 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm2200_priv),
			      GFP_KERNEL);
	अगर (wm2200 == शून्य)
		वापस -ENOMEM;

	wm2200->dev = &i2c->dev;
	init_completion(&wm2200->fll_lock);

	wm2200->regmap = devm_regmap_init_i2c(i2c, &wm2200_regmap);
	अगर (IS_ERR(wm2200->regmap)) अणु
		ret = PTR_ERR(wm2200->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		wm2200->dsp[i].type = WMFW_ADSP1;
		wm2200->dsp[i].part = "wm2200";
		wm2200->dsp[i].num = i + 1;
		wm2200->dsp[i].dev = &i2c->dev;
		wm2200->dsp[i].regmap = wm2200->regmap;
		wm2200->dsp[i].sysclk_reg = WM2200_CLOCKING_3;
		wm2200->dsp[i].sysclk_mask = WM2200_SYSCLK_FREQ_MASK;
		wm2200->dsp[i].sysclk_shअगरt =  WM2200_SYSCLK_FREQ_SHIFT;
	पूर्ण

	wm2200->dsp[0].base = WM2200_DSP1_CONTROL_1;
	wm2200->dsp[0].mem = wm2200_dsp1_regions;
	wm2200->dsp[0].num_mems = ARRAY_SIZE(wm2200_dsp1_regions);

	wm2200->dsp[1].base = WM2200_DSP2_CONTROL_1;
	wm2200->dsp[1].mem = wm2200_dsp2_regions;
	wm2200->dsp[1].num_mems = ARRAY_SIZE(wm2200_dsp2_regions);

	क्रम (i = 0; i < ARRAY_SIZE(wm2200->dsp); i++)
		wm_adsp1_init(&wm2200->dsp[i]);

	अगर (pdata)
		wm2200->pdata = *pdata;

	i2c_set_clientdata(i2c, wm2200);

	क्रम (i = 0; i < ARRAY_SIZE(wm2200->core_supplies); i++)
		wm2200->core_supplies[i].supply = wm2200_core_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(wm2200->core_supplies),
				      wm2200->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm2200->core_supplies),
				    wm2200->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (wm2200->pdata.lकरो_ena) अणु
		ret = devm_gpio_request_one(&i2c->dev, wm2200->pdata.lकरो_ena,
					    GPIOF_OUT_INIT_HIGH,
					    "WM2200 LDOENA");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request LDOENA %d: %d\n",
				wm2200->pdata.lकरो_ena, ret);
			जाओ err_enable;
		पूर्ण
		msleep(2);
	पूर्ण

	अगर (wm2200->pdata.reset) अणु
		ret = devm_gpio_request_one(&i2c->dev, wm2200->pdata.reset,
					    GPIOF_OUT_INIT_HIGH,
					    "WM2200 /RESET");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request /RESET %d: %d\n",
				wm2200->pdata.reset, ret);
			जाओ err_lकरो;
		पूर्ण
	पूर्ण

	ret = regmap_पढ़ो(wm2200->regmap, WM2200_SOFTWARE_RESET, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		जाओ err_reset;
	पूर्ण
	चयन (reg) अणु
	हाल 0x2200:
		अवरोध;

	शेष:
		dev_err(&i2c->dev, "Device is not a WM2200, ID is %x\n", reg);
		ret = -EINVAL;
		जाओ err_reset;
	पूर्ण

	ret = regmap_पढ़ो(wm2200->regmap, WM2200_DEVICE_REVISION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read revision register\n");
		जाओ err_reset;
	पूर्ण

	wm2200->rev = reg & WM2200_DEVICE_REVISION_MASK;

	dev_info(&i2c->dev, "revision %c\n", wm2200->rev + 'A');

	चयन (wm2200->rev) अणु
	हाल 0:
	हाल 1:
		ret = regmap_रेजिस्टर_patch(wm2200->regmap, wm2200_reva_patch,
					    ARRAY_SIZE(wm2200_reva_patch));
		अगर (ret != 0) अणु
			dev_err(&i2c->dev, "Failed to register patch: %d\n",
				ret);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = wm2200_reset(wm2200);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset\n");
		जाओ err_reset;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm2200->pdata.gpio_शेषs); i++) अणु
		अगर (!wm2200->pdata.gpio_शेषs[i])
			जारी;

		regmap_ग_लिखो(wm2200->regmap, WM2200_GPIO_CTRL_1 + i,
			     wm2200->pdata.gpio_शेषs[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm2200_dig_vu); i++)
		regmap_update_bits(wm2200->regmap, wm2200_dig_vu[i],
				   WM2200_OUT_VU, WM2200_OUT_VU);

	/* Assign slots 1-6 to channels 1-6 क्रम both TX and RX */
	क्रम (i = 0; i < 6; i++) अणु
		regmap_ग_लिखो(wm2200->regmap, WM2200_AUDIO_IF_1_10 + i, i);
		regmap_ग_लिखो(wm2200->regmap, WM2200_AUDIO_IF_1_16 + i, i);
	पूर्ण

	क्रम (i = 0; i < WM2200_MAX_MICBIAS; i++) अणु
		अगर (!wm2200->pdata.micbias[i].mb_lvl &&
		    !wm2200->pdata.micbias[i].bypass)
			जारी;

		/* Apply शेष क्रम bypass mode */
		अगर (!wm2200->pdata.micbias[i].mb_lvl)
			wm2200->pdata.micbias[i].mb_lvl
					= WM2200_MBIAS_LVL_1V5;

		val = (wm2200->pdata.micbias[i].mb_lvl -1)
					<< WM2200_MICB1_LVL_SHIFT;

		अगर (wm2200->pdata.micbias[i].disअक्षरge)
			val |= WM2200_MICB1_DISCH;

		अगर (wm2200->pdata.micbias[i].fast_start)
			val |= WM2200_MICB1_RATE;

		अगर (wm2200->pdata.micbias[i].bypass)
			val |= WM2200_MICB1_MODE;

		regmap_update_bits(wm2200->regmap,
				   WM2200_MIC_BIAS_CTRL_1 + i,
				   WM2200_MICB1_LVL_MASK |
				   WM2200_MICB1_DISCH |
				   WM2200_MICB1_MODE |
				   WM2200_MICB1_RATE, val);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm2200->pdata.in_mode); i++) अणु
		regmap_update_bits(wm2200->regmap, wm2200_mic_ctrl_reg[i],
				   WM2200_IN1_MODE_MASK |
				   WM2200_IN1_DMIC_SUP_MASK,
				   (wm2200->pdata.in_mode[i] <<
				    WM2200_IN1_MODE_SHIFT) |
				   (wm2200->pdata.dmic_sup[i] <<
				    WM2200_IN1_DMIC_SUP_SHIFT));
	पूर्ण

	अगर (i2c->irq) अणु
		ret = request_thपढ़ोed_irq(i2c->irq, शून्य, wm2200_irq,
					   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					   "wm2200", wm2200);
		अगर (ret == 0)
			regmap_update_bits(wm2200->regmap,
					   WM2200_INTERRUPT_STATUS_2_MASK,
					   WM2200_FLL_LOCK_EINT, 0);
		अन्यथा
			dev_err(&i2c->dev, "Failed to request IRQ %d: %d\n",
				i2c->irq, ret);
	पूर्ण

	pm_runसमय_set_active(&i2c->dev);
	pm_runसमय_enable(&i2c->dev);
	pm_request_idle(&i2c->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &soc_component_wm2200,
				     &wm2200_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		जाओ err_pm_runसमय;
	पूर्ण

	वापस 0;

err_pm_runसमय:
	pm_runसमय_disable(&i2c->dev);
	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm2200);
err_reset:
	अगर (wm2200->pdata.reset)
		gpio_set_value_cansleep(wm2200->pdata.reset, 0);
err_lकरो:
	अगर (wm2200->pdata.lकरो_ena)
		gpio_set_value_cansleep(wm2200->pdata.lकरो_ena, 0);
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm2200->core_supplies),
			       wm2200->core_supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक wm2200_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm2200_priv *wm2200 = i2c_get_clientdata(i2c);

	pm_runसमय_disable(&i2c->dev);
	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm2200);
	अगर (wm2200->pdata.reset)
		gpio_set_value_cansleep(wm2200->pdata.reset, 0);
	अगर (wm2200->pdata.lकरो_ena)
		gpio_set_value_cansleep(wm2200->pdata.lकरो_ena, 0);
	regulator_bulk_disable(ARRAY_SIZE(wm2200->core_supplies),
			       wm2200->core_supplies);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm2200_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm2200_priv *wm2200 = dev_get_drvdata(dev);

	regcache_cache_only(wm2200->regmap, true);
	regcache_mark_dirty(wm2200->regmap);
	अगर (wm2200->pdata.lकरो_ena)
		gpio_set_value_cansleep(wm2200->pdata.lकरो_ena, 0);
	regulator_bulk_disable(ARRAY_SIZE(wm2200->core_supplies),
			       wm2200->core_supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक wm2200_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा wm2200_priv *wm2200 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm2200->core_supplies),
				    wm2200->core_supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (wm2200->pdata.lकरो_ena) अणु
		gpio_set_value_cansleep(wm2200->pdata.lकरो_ena, 1);
		msleep(2);
	पूर्ण

	regcache_cache_only(wm2200->regmap, false);
	regcache_sync(wm2200->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops wm2200_pm = अणु
	SET_RUNTIME_PM_OPS(wm2200_runसमय_suspend, wm2200_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id wm2200_i2c_id[] = अणु
	अणु "wm2200", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm2200_i2c_id);

अटल काष्ठा i2c_driver wm2200_i2c_driver = अणु
	.driver = अणु
		.name = "wm2200",
		.pm = &wm2200_pm,
	पूर्ण,
	.probe =    wm2200_i2c_probe,
	.हटाओ =   wm2200_i2c_हटाओ,
	.id_table = wm2200_i2c_id,
पूर्ण;

module_i2c_driver(wm2200_i2c_driver);

MODULE_DESCRIPTION("ASoC WM2200 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
