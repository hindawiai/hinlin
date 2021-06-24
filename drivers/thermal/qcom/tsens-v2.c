<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Copyright (c) 2018, Linaro Limited
 */

#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश "tsens.h"

/* ----- SROT ------ */
#घोषणा SROT_HW_VER_OFF	0x0000
#घोषणा SROT_CTRL_OFF		0x0004

/* ----- TM ------ */
#घोषणा TM_INT_EN_OFF			0x0004
#घोषणा TM_UPPER_LOWER_INT_STATUS_OFF	0x0008
#घोषणा TM_UPPER_LOWER_INT_CLEAR_OFF	0x000c
#घोषणा TM_UPPER_LOWER_INT_MASK_OFF	0x0010
#घोषणा TM_CRITICAL_INT_STATUS_OFF	0x0014
#घोषणा TM_CRITICAL_INT_CLEAR_OFF	0x0018
#घोषणा TM_CRITICAL_INT_MASK_OFF	0x001c
#घोषणा TM_Sn_UPPER_LOWER_THRESHOLD_OFF 0x0020
#घोषणा TM_Sn_CRITICAL_THRESHOLD_OFF	0x0060
#घोषणा TM_Sn_STATUS_OFF		0x00a0
#घोषणा TM_TRDY_OFF			0x00e4
#घोषणा TM_WDOG_LOG_OFF		0x013c

/* v2.x: 8996, 8998, sdm845 */

अटल काष्ठा tsens_features tsens_v2_feat = अणु
	.ver_major	= VER_2_X,
	.crit_पूर्णांक	= 1,
	.adc		= 0,
	.srot_split	= 1,
	.max_sensors	= 16,
पूर्ण;

अटल स्थिर काष्ठा reg_field tsens_v2_regfields[MAX_REGFIELDS] = अणु
	/* ----- SROT ------ */
	/* VERSION */
	[VER_MAJOR] = REG_FIELD(SROT_HW_VER_OFF, 28, 31),
	[VER_MINOR] = REG_FIELD(SROT_HW_VER_OFF, 16, 27),
	[VER_STEP]  = REG_FIELD(SROT_HW_VER_OFF,  0, 15),
	/* CTRL_OFF */
	[TSENS_EN]     = REG_FIELD(SROT_CTRL_OFF,    0,  0),
	[TSENS_SW_RST] = REG_FIELD(SROT_CTRL_OFF,    1,  1),

	/* ----- TM ------ */
	/* INTERRUPT ENABLE */
	/* v2 has separate enables क्रम UPPER/LOWER/CRITICAL पूर्णांकerrupts */
	[INT_EN]  = REG_FIELD(TM_INT_EN_OFF, 0, 2),

	/* TEMPERATURE THRESHOLDS */
	REG_FIELD_FOR_EACH_SENSOR16(LOW_THRESH,  TM_Sn_UPPER_LOWER_THRESHOLD_OFF,  0,  11),
	REG_FIELD_FOR_EACH_SENSOR16(UP_THRESH,   TM_Sn_UPPER_LOWER_THRESHOLD_OFF, 12,  23),
	REG_FIELD_FOR_EACH_SENSOR16(CRIT_THRESH, TM_Sn_CRITICAL_THRESHOLD_OFF,     0,  11),

	/* INTERRUPTS [CLEAR/STATUS/MASK] */
	REG_FIELD_SPLIT_BITS_0_15(LOW_INT_STATUS,  TM_UPPER_LOWER_INT_STATUS_OFF),
	REG_FIELD_SPLIT_BITS_0_15(LOW_INT_CLEAR,   TM_UPPER_LOWER_INT_CLEAR_OFF),
	REG_FIELD_SPLIT_BITS_0_15(LOW_INT_MASK,    TM_UPPER_LOWER_INT_MASK_OFF),
	REG_FIELD_SPLIT_BITS_16_31(UP_INT_STATUS,  TM_UPPER_LOWER_INT_STATUS_OFF),
	REG_FIELD_SPLIT_BITS_16_31(UP_INT_CLEAR,   TM_UPPER_LOWER_INT_CLEAR_OFF),
	REG_FIELD_SPLIT_BITS_16_31(UP_INT_MASK,    TM_UPPER_LOWER_INT_MASK_OFF),
	REG_FIELD_SPLIT_BITS_0_15(CRIT_INT_STATUS, TM_CRITICAL_INT_STATUS_OFF),
	REG_FIELD_SPLIT_BITS_0_15(CRIT_INT_CLEAR,  TM_CRITICAL_INT_CLEAR_OFF),
	REG_FIELD_SPLIT_BITS_0_15(CRIT_INT_MASK,   TM_CRITICAL_INT_MASK_OFF),

	/* WATCHDOG on v2.3 or later */
	[WDOG_BARK_STATUS] = REG_FIELD(TM_CRITICAL_INT_STATUS_OFF, 31, 31),
	[WDOG_BARK_CLEAR]  = REG_FIELD(TM_CRITICAL_INT_CLEAR_OFF,  31, 31),
	[WDOG_BARK_MASK]   = REG_FIELD(TM_CRITICAL_INT_MASK_OFF,   31, 31),
	[CC_MON_STATUS]    = REG_FIELD(TM_CRITICAL_INT_STATUS_OFF, 30, 30),
	[CC_MON_CLEAR]     = REG_FIELD(TM_CRITICAL_INT_CLEAR_OFF,  30, 30),
	[CC_MON_MASK]      = REG_FIELD(TM_CRITICAL_INT_MASK_OFF,   30, 30),
	[WDOG_BARK_COUNT]  = REG_FIELD(TM_WDOG_LOG_OFF,             0,  7),

	/* Sn_STATUS */
	REG_FIELD_FOR_EACH_SENSOR16(LAST_TEMP,       TM_Sn_STATUS_OFF,  0,  11),
	REG_FIELD_FOR_EACH_SENSOR16(VALID,           TM_Sn_STATUS_OFF, 21,  21),
	/* xxx_STATUS bits: 1 == threshold violated */
	REG_FIELD_FOR_EACH_SENSOR16(MIN_STATUS,      TM_Sn_STATUS_OFF, 16,  16),
	REG_FIELD_FOR_EACH_SENSOR16(LOWER_STATUS,    TM_Sn_STATUS_OFF, 17,  17),
	REG_FIELD_FOR_EACH_SENSOR16(UPPER_STATUS,    TM_Sn_STATUS_OFF, 18,  18),
	REG_FIELD_FOR_EACH_SENSOR16(CRITICAL_STATUS, TM_Sn_STATUS_OFF, 19,  19),
	REG_FIELD_FOR_EACH_SENSOR16(MAX_STATUS,      TM_Sn_STATUS_OFF, 20,  20),

	/* TRDY: 1=पढ़ोy, 0=in progress */
	[TRDY] = REG_FIELD(TM_TRDY_OFF, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_generic_v2 = अणु
	.init		= init_common,
	.get_temp	= get_temp_tsens_valid,
पूर्ण;

काष्ठा tsens_plat_data data_tsens_v2 = अणु
	.ops		= &ops_generic_v2,
	.feat		= &tsens_v2_feat,
	.fields	= tsens_v2_regfields,
पूर्ण;

/* Kept around क्रम backward compatibility with old msm8996.dtsi */
काष्ठा tsens_plat_data data_8996 = अणु
	.num_sensors	= 13,
	.ops		= &ops_generic_v2,
	.feat		= &tsens_v2_feat,
	.fields	= tsens_v2_regfields,
पूर्ण;
