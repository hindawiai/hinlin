<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "hwmgr.h"
#समावेश "vega10_hwmgr.h"
#समावेश "vega10_smumgr.h"
#समावेश "vega10_powertune.h"
#समावेश "vega10_ppsmc.h"
#समावेश "vega10_inc.h"
#समावेश "pp_debug.h"
#समावेश "soc15_common.h"

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtTuningCtrlConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,        DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,        0x3853 पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,        DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,        0x3153 पूर्ण,

	/* DIDT_TD */
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,        DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,        0x0dde पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,        DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,        0x0dde पूर्ण,

	/* DIDT_TCP */
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,       0x3dde पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,       0x3dde पूर्ण,

	/* DIDT_DB */
	अणु   ixDIDT_DB_TUNING_CTRL,             DIDT_DB_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,        DIDT_DB_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,        0x3dde पूर्ण,
	अणु   ixDIDT_DB_TUNING_CTRL,             DIDT_DB_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,        DIDT_DB_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,        0x3dde पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtCtrl3Config_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset               Mask                                                     Shअगरt                                                            Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/*DIDT_SQ_CTRL3 */
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__GC_DIDT_ENABLE_MASK,       DIDT_SQ_CTRL3__GC_DIDT_ENABLE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__GC_DIDT_CLK_EN_OVERRIDE_MASK,       DIDT_SQ_CTRL3__GC_DIDT_CLK_EN_OVERRIDE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__THROTTLE_POLICY_MASK,       DIDT_SQ_CTRL3__THROTTLE_POLICY__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT_MASK,       DIDT_SQ_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_POWER_LEVEL_LOWBIT_MASK,       DIDT_SQ_CTRL3__DIDT_POWER_LEVEL_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS_MASK,       DIDT_SQ_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__GC_DIDT_LEVEL_COMB_EN_MASK,       DIDT_SQ_CTRL3__GC_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__SE_DIDT_LEVEL_COMB_EN_MASK,       DIDT_SQ_CTRL3__SE_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__QUALIFY_STALL_EN_MASK,       DIDT_SQ_CTRL3__QUALIFY_STALL_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_STALL_SEL_MASK,       DIDT_SQ_CTRL3__DIDT_STALL_SEL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_FORCE_STALL_MASK,       DIDT_SQ_CTRL3__DIDT_FORCE_STALL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL3,     DIDT_SQ_CTRL3__DIDT_STALL_DELAY_EN_MASK,       DIDT_SQ_CTRL3__DIDT_STALL_DELAY_EN__SHIFT,             0x0000 पूर्ण,

	/*DIDT_TCP_CTRL3 */
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__GC_DIDT_ENABLE_MASK,      DIDT_TCP_CTRL3__GC_DIDT_ENABLE__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__GC_DIDT_CLK_EN_OVERRIDE_MASK,      DIDT_TCP_CTRL3__GC_DIDT_CLK_EN_OVERRIDE__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__THROTTLE_POLICY_MASK,      DIDT_TCP_CTRL3__THROTTLE_POLICY__SHIFT,            0x0003 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT_MASK,      DIDT_TCP_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_POWER_LEVEL_LOWBIT_MASK,      DIDT_TCP_CTRL3__DIDT_POWER_LEVEL_LOWBIT__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS_MASK,      DIDT_TCP_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS__SHIFT,            0x0003 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__GC_DIDT_LEVEL_COMB_EN_MASK,      DIDT_TCP_CTRL3__GC_DIDT_LEVEL_COMB_EN__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__SE_DIDT_LEVEL_COMB_EN_MASK,      DIDT_TCP_CTRL3__SE_DIDT_LEVEL_COMB_EN__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__QUALIFY_STALL_EN_MASK,      DIDT_TCP_CTRL3__QUALIFY_STALL_EN__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_STALL_SEL_MASK,      DIDT_TCP_CTRL3__DIDT_STALL_SEL__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_FORCE_STALL_MASK,      DIDT_TCP_CTRL3__DIDT_FORCE_STALL__SHIFT,            0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL3,    DIDT_TCP_CTRL3__DIDT_STALL_DELAY_EN_MASK,      DIDT_TCP_CTRL3__DIDT_STALL_DELAY_EN__SHIFT,            0x0000 पूर्ण,

	/*DIDT_TD_CTRL3 */
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__GC_DIDT_ENABLE_MASK,       DIDT_TD_CTRL3__GC_DIDT_ENABLE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__GC_DIDT_CLK_EN_OVERRIDE_MASK,       DIDT_TD_CTRL3__GC_DIDT_CLK_EN_OVERRIDE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__THROTTLE_POLICY_MASK,       DIDT_TD_CTRL3__THROTTLE_POLICY__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT_MASK,       DIDT_TD_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_POWER_LEVEL_LOWBIT_MASK,       DIDT_TD_CTRL3__DIDT_POWER_LEVEL_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS_MASK,       DIDT_TD_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__GC_DIDT_LEVEL_COMB_EN_MASK,       DIDT_TD_CTRL3__GC_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__SE_DIDT_LEVEL_COMB_EN_MASK,       DIDT_TD_CTRL3__SE_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__QUALIFY_STALL_EN_MASK,       DIDT_TD_CTRL3__QUALIFY_STALL_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_STALL_SEL_MASK,       DIDT_TD_CTRL3__DIDT_STALL_SEL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_FORCE_STALL_MASK,       DIDT_TD_CTRL3__DIDT_FORCE_STALL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL3,     DIDT_TD_CTRL3__DIDT_STALL_DELAY_EN_MASK,       DIDT_TD_CTRL3__DIDT_STALL_DELAY_EN__SHIFT,             0x0000 पूर्ण,

	/*DIDT_DB_CTRL3 */
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__GC_DIDT_ENABLE_MASK,       DIDT_DB_CTRL3__GC_DIDT_ENABLE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__GC_DIDT_CLK_EN_OVERRIDE_MASK,       DIDT_DB_CTRL3__GC_DIDT_CLK_EN_OVERRIDE__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__THROTTLE_POLICY_MASK,       DIDT_DB_CTRL3__THROTTLE_POLICY__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT_MASK,       DIDT_DB_CTRL3__DIDT_TRIGGER_THROTTLE_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_POWER_LEVEL_LOWBIT_MASK,       DIDT_DB_CTRL3__DIDT_POWER_LEVEL_LOWBIT__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS_MASK,       DIDT_DB_CTRL3__DIDT_STALL_PATTERN_BIT_NUMS__SHIFT,             0x0003 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__GC_DIDT_LEVEL_COMB_EN_MASK,       DIDT_DB_CTRL3__GC_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__SE_DIDT_LEVEL_COMB_EN_MASK,       DIDT_DB_CTRL3__SE_DIDT_LEVEL_COMB_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__QUALIFY_STALL_EN_MASK,       DIDT_DB_CTRL3__QUALIFY_STALL_EN__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_STALL_SEL_MASK,       DIDT_DB_CTRL3__DIDT_STALL_SEL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_FORCE_STALL_MASK,       DIDT_DB_CTRL3__DIDT_FORCE_STALL__SHIFT,             0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL3,     DIDT_DB_CTRL3__DIDT_STALL_DELAY_EN_MASK,       DIDT_DB_CTRL3__DIDT_STALL_DELAY_EN__SHIFT,             0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtCtrl2Config_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                            Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_CTRL2,                  DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                 DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,                 0x3853 पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                  DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,        DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,        0x00c0 पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                  DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,        DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,        0x0000 पूर्ण,

	/* DIDT_TD */
	अणु   ixDIDT_TD_CTRL2,                  DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                 DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,                 0x3fff पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                  DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,        DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,        0x00c0 पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                  DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,        DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,        0x0001 पूर्ण,

	/* DIDT_TCP */
	अणु   ixDIDT_TCP_CTRL2,                 DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,                0x3dde पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                 DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,       0x00c0 पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                 DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,       0x0001 पूर्ण,

	/* DIDT_DB */
	अणु   ixDIDT_DB_CTRL2,                  DIDT_DB_CTRL2__MAX_POWER_DELTA_MASK,                 DIDT_DB_CTRL2__MAX_POWER_DELTA__SHIFT,                 0x3dde पूर्ण,
	अणु   ixDIDT_DB_CTRL2,                  DIDT_DB_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,        DIDT_DB_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,        0x00c0 पूर्ण,
	अणु   ixDIDT_DB_CTRL2,                  DIDT_DB_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,        DIDT_DB_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,        0x0001 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtCtrl1Config_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                       DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                       0x0000 पूर्ण,
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                       DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                       0xffff पूर्ण,
	/* DIDT_TD */
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                       DIDT_TD_CTRL1__MIN_POWER__SHIFT,                       0x0000 पूर्ण,
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                       DIDT_TD_CTRL1__MAX_POWER__SHIFT,                       0xffff पूर्ण,
	/* DIDT_TCP */
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                      DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                      0x0000 पूर्ण,
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                      DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                      0xffff पूर्ण,
	/* DIDT_DB */
	अणु   ixDIDT_DB_CTRL1,                   DIDT_DB_CTRL1__MIN_POWER_MASK,                       DIDT_DB_CTRL1__MIN_POWER__SHIFT,                       0x0000 पूर्ण,
	अणु   ixDIDT_DB_CTRL1,                   DIDT_DB_CTRL1__MAX_POWER_MASK,                       DIDT_DB_CTRL1__MAX_POWER__SHIFT,                       0xffff पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;


अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtWeightConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                  Shअगरt                                                 Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_WEIGHT0_3,               0xFFFFFFFF,                                           0,                                                    0x2B363B1A पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               0xFFFFFFFF,                                           0,                                                    0x270B2432 पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              0xFFFFFFFF,                                           0,                                                    0x00000018 पूर्ण,

	/* DIDT_TD */
	अणु   ixDIDT_TD_WEIGHT0_3,               0xFFFFFFFF,                                           0,                                                    0x2B1D220F पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               0xFFFFFFFF,                                           0,                                                    0x00007558 पूर्ण,
	अणु   ixDIDT_TD_WEIGHT8_11,              0xFFFFFFFF,                                           0,                                                    0x00000000 पूर्ण,

	/* DIDT_TCP */
	अणु   ixDIDT_TCP_WEIGHT0_3,               0xFFFFFFFF,                                          0,                                                    0x5ACE160D पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,               0xFFFFFFFF,                                          0,                                                    0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT8_11,              0xFFFFFFFF,                                          0,                                                    0x00000000 पूर्ण,

	/* DIDT_DB */
	अणु   ixDIDT_DB_WEIGHT0_3,                0xFFFFFFFF,                                          0,                                                    0x0E152A0F पूर्ण,
	अणु   ixDIDT_DB_WEIGHT4_7,                0xFFFFFFFF,                                          0,                                                    0x09061813 पूर्ण,
	अणु   ixDIDT_DB_WEIGHT8_11,               0xFFFFFFFF,                                          0,                                                    0x00000013 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtCtrl0Config_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,   DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_STALL_CTRL_EN_MASK,   DIDT_SQ_CTRL0__DIDT_STALL_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_TUNING_CTRL_EN_MASK,   DIDT_SQ_CTRL0__DIDT_TUNING_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_STALL_AUTO_RELEASE_EN_MASK,   DIDT_SQ_CTRL0__DIDT_STALL_AUTO_RELEASE_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_CTRL0__DIDT_HI_POWER_THRESHOLD__SHIFT,  0xffff पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_AUTO_MPD_EN_MASK,   DIDT_SQ_CTRL0__DIDT_AUTO_MPD_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_STALL_EVENT_EN_MASK,   DIDT_SQ_CTRL0__DIDT_STALL_EVENT_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR_MASK,   DIDT_SQ_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR__SHIFT,  0x0000 पूर्ण,
	/* DIDT_TD */
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,   DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_STALL_CTRL_EN_MASK,   DIDT_TD_CTRL0__DIDT_STALL_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_TUNING_CTRL_EN_MASK,   DIDT_TD_CTRL0__DIDT_TUNING_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_STALL_AUTO_RELEASE_EN_MASK,   DIDT_TD_CTRL0__DIDT_STALL_AUTO_RELEASE_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_CTRL0__DIDT_HI_POWER_THRESHOLD__SHIFT,  0xffff पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_AUTO_MPD_EN_MASK,   DIDT_TD_CTRL0__DIDT_AUTO_MPD_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_STALL_EVENT_EN_MASK,   DIDT_TD_CTRL0__DIDT_STALL_EVENT_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR_MASK,   DIDT_TD_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR__SHIFT,  0x0000 पूर्ण,
	/* DIDT_TCP */
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,  DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,  DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,  DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_STALL_CTRL_EN_MASK,  DIDT_TCP_CTRL0__DIDT_STALL_CTRL_EN__SHIFT, 0x0001 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_TUNING_CTRL_EN_MASK,  DIDT_TCP_CTRL0__DIDT_TUNING_CTRL_EN__SHIFT, 0x0001 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_STALL_AUTO_RELEASE_EN_MASK,  DIDT_TCP_CTRL0__DIDT_STALL_AUTO_RELEASE_EN__SHIFT, 0x0001 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_CTRL0__DIDT_HI_POWER_THRESHOLD__SHIFT, 0xffff पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_AUTO_MPD_EN_MASK,  DIDT_TCP_CTRL0__DIDT_AUTO_MPD_EN__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_STALL_EVENT_EN_MASK,  DIDT_TCP_CTRL0__DIDT_STALL_EVENT_EN__SHIFT, 0x0000 पूर्ण,
	अणु  ixDIDT_TCP_CTRL0,                  DIDT_TCP_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR_MASK,  DIDT_TCP_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR__SHIFT, 0x0000 पूर्ण,
	/* DIDT_DB */
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_CTRL_EN_MASK,   DIDT_DB_CTRL0__DIDT_CTRL_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__PHASE_OFFSET_MASK,   DIDT_DB_CTRL0__PHASE_OFFSET__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_CTRL_RST_MASK,   DIDT_DB_CTRL0__DIDT_CTRL_RST__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,   DIDT_DB_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_STALL_CTRL_EN_MASK,   DIDT_DB_CTRL0__DIDT_STALL_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_TUNING_CTRL_EN_MASK,   DIDT_DB_CTRL0__DIDT_TUNING_CTRL_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_STALL_AUTO_RELEASE_EN_MASK,   DIDT_DB_CTRL0__DIDT_STALL_AUTO_RELEASE_EN__SHIFT,  0x0001 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_DB_CTRL0__DIDT_HI_POWER_THRESHOLD__SHIFT,  0xffff पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_AUTO_MPD_EN_MASK,   DIDT_DB_CTRL0__DIDT_AUTO_MPD_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_STALL_EVENT_EN_MASK,   DIDT_DB_CTRL0__DIDT_STALL_EVENT_EN__SHIFT,  0x0000 पूर्ण,
	अणु  ixDIDT_DB_CTRL0,                   DIDT_DB_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR_MASK,   DIDT_DB_CTRL0__DIDT_STALL_EVENT_COUNTER_CLEAR__SHIFT,  0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;


अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtStallCtrlConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                   Mask                                                     Shअगरt                                                      Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_STALL_CTRL,    DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0004 पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,    DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0004 पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,    DIDT_SQ_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI_MASK,    DIDT_SQ_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,     0x000a पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,    DIDT_SQ_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO_MASK,    DIDT_SQ_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,     0x000a पूर्ण,

	/* DIDT_TD */
	अणु   ixDIDT_TD_STALL_CTRL,    DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001 पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,    DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001 पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,    DIDT_TD_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI_MASK,    DIDT_TD_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,     0x000a पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,    DIDT_TD_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO_MASK,    DIDT_TD_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,     0x000a पूर्ण,

	/* DIDT_TCP */
	अणु   ixDIDT_TCP_STALL_CTRL,   DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001 पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,   DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001 पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,   DIDT_TCP_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI_MASK,   DIDT_TCP_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,    0x000a पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,   DIDT_TCP_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO_MASK,   DIDT_TCP_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,    0x000a पूर्ण,

	/* DIDT_DB */
	अणु   ixDIDT_DB_STALL_CTRL,    DIDT_DB_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,    DIDT_DB_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0004 पूर्ण,
	अणु   ixDIDT_DB_STALL_CTRL,    DIDT_DB_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,    DIDT_DB_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0004 पूर्ण,
	अणु   ixDIDT_DB_STALL_CTRL,    DIDT_DB_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI_MASK,    DIDT_DB_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,     0x000a पूर्ण,
	अणु   ixDIDT_DB_STALL_CTRL,    DIDT_DB_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO_MASK,    DIDT_DB_STALL_CTRL__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,     0x000a पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEDiDtStallPatternConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                        Mask                                                      Shअगरt                                                    Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ_STALL_PATTERN_1_2 */
	अणु   ixDIDT_SQ_STALL_PATTERN_1_2,  DIDT_SQ_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1_MASK,    DIDT_SQ_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_SQ_STALL_PATTERN_1_2,  DIDT_SQ_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2_MASK,    DIDT_SQ_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2__SHIFT,  0x0001 पूर्ण,

	/* DIDT_SQ_STALL_PATTERN_3_4 */
	अणु   ixDIDT_SQ_STALL_PATTERN_3_4,  DIDT_SQ_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3_MASK,    DIDT_SQ_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_SQ_STALL_PATTERN_3_4,  DIDT_SQ_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4_MASK,    DIDT_SQ_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4__SHIFT,  0x0001 पूर्ण,

	/* DIDT_SQ_STALL_PATTERN_5_6 */
	अणु   ixDIDT_SQ_STALL_PATTERN_5_6,  DIDT_SQ_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5_MASK,    DIDT_SQ_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_STALL_PATTERN_5_6,  DIDT_SQ_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6_MASK,    DIDT_SQ_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6__SHIFT,  0x0000 पूर्ण,

	/* DIDT_SQ_STALL_PATTERN_7 */
	अणु   ixDIDT_SQ_STALL_PATTERN_7,    DIDT_SQ_STALL_PATTERN_7__DIDT_STALL_PATTERN_7_MASK,      DIDT_SQ_STALL_PATTERN_7__DIDT_STALL_PATTERN_7__SHIFT,    0x0000 पूर्ण,

	/* DIDT_TCP_STALL_PATTERN_1_2 */
	अणु   ixDIDT_TCP_STALL_PATTERN_1_2, DIDT_TCP_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1_MASK,   DIDT_TCP_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1__SHIFT, 0x0001 पूर्ण,
	अणु   ixDIDT_TCP_STALL_PATTERN_1_2, DIDT_TCP_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2_MASK,   DIDT_TCP_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2__SHIFT, 0x0001 पूर्ण,

	/* DIDT_TCP_STALL_PATTERN_3_4 */
	अणु   ixDIDT_TCP_STALL_PATTERN_3_4, DIDT_TCP_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3_MASK,   DIDT_TCP_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3__SHIFT, 0x0001 पूर्ण,
	अणु   ixDIDT_TCP_STALL_PATTERN_3_4, DIDT_TCP_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4_MASK,   DIDT_TCP_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4__SHIFT, 0x0001 पूर्ण,

	/* DIDT_TCP_STALL_PATTERN_5_6 */
	अणु   ixDIDT_TCP_STALL_PATTERN_5_6, DIDT_TCP_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5_MASK,   DIDT_TCP_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5__SHIFT, 0x0000 पूर्ण,
	अणु   ixDIDT_TCP_STALL_PATTERN_5_6, DIDT_TCP_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6_MASK,   DIDT_TCP_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6__SHIFT, 0x0000 पूर्ण,

	/* DIDT_TCP_STALL_PATTERN_7 */
	अणु   ixDIDT_TCP_STALL_PATTERN_7,   DIDT_TCP_STALL_PATTERN_7__DIDT_STALL_PATTERN_7_MASK,     DIDT_TCP_STALL_PATTERN_7__DIDT_STALL_PATTERN_7__SHIFT,   0x0000 पूर्ण,

	/* DIDT_TD_STALL_PATTERN_1_2 */
	अणु   ixDIDT_TD_STALL_PATTERN_1_2,  DIDT_TD_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1_MASK,    DIDT_TD_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_TD_STALL_PATTERN_1_2,  DIDT_TD_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2_MASK,    DIDT_TD_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2__SHIFT,  0x0001 पूर्ण,

	/* DIDT_TD_STALL_PATTERN_3_4 */
	अणु   ixDIDT_TD_STALL_PATTERN_3_4,  DIDT_TD_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3_MASK,    DIDT_TD_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_TD_STALL_PATTERN_3_4,  DIDT_TD_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4_MASK,    DIDT_TD_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4__SHIFT,  0x0001 पूर्ण,

	/* DIDT_TD_STALL_PATTERN_5_6 */
	अणु   ixDIDT_TD_STALL_PATTERN_5_6,  DIDT_TD_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5_MASK,    DIDT_TD_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_TD_STALL_PATTERN_5_6,  DIDT_TD_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6_MASK,    DIDT_TD_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6__SHIFT,  0x0000 पूर्ण,

	/* DIDT_TD_STALL_PATTERN_7 */
	अणु   ixDIDT_TD_STALL_PATTERN_7,    DIDT_TD_STALL_PATTERN_7__DIDT_STALL_PATTERN_7_MASK,      DIDT_TD_STALL_PATTERN_7__DIDT_STALL_PATTERN_7__SHIFT,    0x0000 पूर्ण,

	/* DIDT_DB_STALL_PATTERN_1_2 */
	अणु   ixDIDT_DB_STALL_PATTERN_1_2,  DIDT_DB_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1_MASK,    DIDT_DB_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_1__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_DB_STALL_PATTERN_1_2,  DIDT_DB_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2_MASK,    DIDT_DB_STALL_PATTERN_1_2__DIDT_STALL_PATTERN_2__SHIFT,  0x0001 पूर्ण,

	/* DIDT_DB_STALL_PATTERN_3_4 */
	अणु   ixDIDT_DB_STALL_PATTERN_3_4,  DIDT_DB_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3_MASK,    DIDT_DB_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_3__SHIFT,  0x0001 पूर्ण,
	अणु   ixDIDT_DB_STALL_PATTERN_3_4,  DIDT_DB_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4_MASK,    DIDT_DB_STALL_PATTERN_3_4__DIDT_STALL_PATTERN_4__SHIFT,  0x0001 पूर्ण,

	/* DIDT_DB_STALL_PATTERN_5_6 */
	अणु   ixDIDT_DB_STALL_PATTERN_5_6,  DIDT_DB_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5_MASK,    DIDT_DB_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_5__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_DB_STALL_PATTERN_5_6,  DIDT_DB_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6_MASK,    DIDT_DB_STALL_PATTERN_5_6__DIDT_STALL_PATTERN_6__SHIFT,  0x0000 पूर्ण,

	/* DIDT_DB_STALL_PATTERN_7 */
	अणु   ixDIDT_DB_STALL_PATTERN_7,    DIDT_DB_STALL_PATTERN_7__DIDT_STALL_PATTERN_7_MASK,      DIDT_DB_STALL_PATTERN_7__DIDT_STALL_PATTERN_7__SHIFT,    0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SELCacConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x00060021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x00860021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x01060021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x01860021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x02060021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x02860021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x03060021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x03860021 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x04060021 पूर्ण,
	/* TD */
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x000E0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x008E0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x010E0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x018E0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x020E0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x028E0020 पूर्ण,
	/* TCP */
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x001c0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x009c0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x011c0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x019c0020 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x021c0020 पूर्ण,
	/* DB */
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x00200008 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x00820008 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x01020008 पूर्ण,
	अणु   ixSE_CAC_CNTL,                     0xFFFFFFFF,                                          0,                                                     0x01820008 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;


अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCStallPatternConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                          0,                                                     0x00030001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                          0,                                                     0x000F0007 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                          0,                                                     0x003F001F पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                          0,                                                     0x0000007F पूर्ण,
	/* TD */
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	/* TCP */
	अणु   ixDIDT_TCP_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                         0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                         0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                         0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                         0,                                                     0x00000000 पूर्ण,
	/* DB */
	अणु   ixDIDT_DB_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_DB_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_DB_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_DB_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCForceStallPatternConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                          0,                                                     0x00000015 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	/* TD */
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_1_2,   0xFFFFFFFF,                                          0,                                                     0x00000015 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_3_4,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_5_6,   0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_PATTERN_7,     0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCStallDelayConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_1,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_2,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_3,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_4,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	/* TD */
	अणु   ixDIDT_TD_EDC_STALL_DELAY_1,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_DELAY_2,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_DELAY_3,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TD_EDC_STALL_DELAY_4,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	/* TCP */
	अणु   ixDIDT_TCP_EDC_STALL_DELAY_1,      0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_DELAY_2,      0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_DELAY_3,      0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	अणु   ixDIDT_TCP_EDC_STALL_DELAY_4,      0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,
	/* DB */
	अणु   ixDIDT_DB_EDC_STALL_DELAY_1,       0xFFFFFFFF,                                          0,                                                     0x00000000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCThresholdConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixDIDT_SQ_EDC_THRESHOLD,           0xFFFFFFFF,                                          0,                                                     0x0000010E पूर्ण,
	अणु   ixDIDT_TD_EDC_THRESHOLD,           0xFFFFFFFF,                                          0,                                                     0xFFFFFFFF पूर्ण,
	अणु   ixDIDT_TCP_EDC_THRESHOLD,          0xFFFFFFFF,                                          0,                                                     0xFFFFFFFF पूर्ण,
	अणु   ixDIDT_DB_EDC_THRESHOLD,           0xFFFFFFFF,                                          0,                                                     0xFFFFFFFF पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCCtrlResetConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_EN_MASK,                       DIDT_SQ_EDC_CTRL__EDC_EN__SHIFT,                        0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_SQ_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_SQ_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCCtrlConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_EN_MASK,                       DIDT_SQ_EDC_CTRL__EDC_EN__SHIFT,                        0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_SQ_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0004 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x0006 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_SQ_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg SEEDCCtrlForceStallConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ */
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_EN_MASK,                       DIDT_SQ_EDC_CTRL__EDC_EN__SHIFT,                        0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_SQ_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x000C पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_SQ_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0001 पूर्ण,

	/* TD */
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_EN_MASK,                       DIDT_TD_EDC_CTRL__EDC_EN__SHIFT,                        0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_TD_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_TD_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_TD_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0001 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_TD_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0001 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_TD_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x000E पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_TD_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_TD_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_TD_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_TD_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,
	अणु   ixDIDT_TD_EDC_CTRL,                DIDT_TD_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_TD_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0001 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg    GCDiDtDroopCtrlConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   mmGC_DIDT_DROOP_CTRL,             GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_EN_MASK,   GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_EN__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_DROOP_CTRL,             GC_DIDT_DROOP_CTRL__DIDT_DROOP_THRESHOLD_MASK,   GC_DIDT_DROOP_CTRL__DIDT_DROOP_THRESHOLD__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_DROOP_CTRL,             GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_INDEX_MASK,   GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_INDEX__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_DROOP_CTRL,             GC_DIDT_DROOP_CTRL__DIDT_LEVEL_SEL_MASK,   GC_DIDT_DROOP_CTRL__DIDT_LEVEL_SEL__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_DROOP_CTRL,             GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_OVERFLOW_MASK,   GC_DIDT_DROOP_CTRL__DIDT_DROOP_LEVEL_OVERFLOW__SHIFT,  0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg    GCDiDtCtrl0Config_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   mmGC_DIDT_CTRL0,                  GC_DIDT_CTRL0__DIDT_CTRL_EN_MASK,   GC_DIDT_CTRL0__DIDT_CTRL_EN__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_CTRL0,                  GC_DIDT_CTRL0__PHASE_OFFSET_MASK,   GC_DIDT_CTRL0__PHASE_OFFSET__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_CTRL0,                  GC_DIDT_CTRL0__DIDT_SW_RST_MASK,   GC_DIDT_CTRL0__DIDT_SW_RST__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_CTRL0,                  GC_DIDT_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,   GC_DIDT_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,  0x0000 पूर्ण,
	अणु   mmGC_DIDT_CTRL0,                  GC_DIDT_CTRL0__DIDT_TRIGGER_THROTTLE_LOWBIT_MASK,   GC_DIDT_CTRL0__DIDT_TRIGGER_THROTTLE_LOWBIT__SHIFT,  0x0000 पूर्ण,
	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;


अटल स्थिर काष्ठा vega10_didt_config_reg   PSMSEEDCStallPatternConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ EDC STALL PATTERNs */
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_1_2,  DIDT_SQ_EDC_STALL_PATTERN_1_2__EDC_STALL_PATTERN_1_MASK,   DIDT_SQ_EDC_STALL_PATTERN_1_2__EDC_STALL_PATTERN_1__SHIFT,   0x0101 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_1_2,  DIDT_SQ_EDC_STALL_PATTERN_1_2__EDC_STALL_PATTERN_2_MASK,   DIDT_SQ_EDC_STALL_PATTERN_1_2__EDC_STALL_PATTERN_2__SHIFT,   0x0101 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_3_4,  DIDT_SQ_EDC_STALL_PATTERN_3_4__EDC_STALL_PATTERN_3_MASK,   DIDT_SQ_EDC_STALL_PATTERN_3_4__EDC_STALL_PATTERN_3__SHIFT,   0x1111 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_3_4,  DIDT_SQ_EDC_STALL_PATTERN_3_4__EDC_STALL_PATTERN_4_MASK,   DIDT_SQ_EDC_STALL_PATTERN_3_4__EDC_STALL_PATTERN_4__SHIFT,   0x1111 पूर्ण,

	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_5_6,  DIDT_SQ_EDC_STALL_PATTERN_5_6__EDC_STALL_PATTERN_5_MASK,   DIDT_SQ_EDC_STALL_PATTERN_5_6__EDC_STALL_PATTERN_5__SHIFT,   0x1515 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_5_6,  DIDT_SQ_EDC_STALL_PATTERN_5_6__EDC_STALL_PATTERN_6_MASK,   DIDT_SQ_EDC_STALL_PATTERN_5_6__EDC_STALL_PATTERN_6__SHIFT,   0x1515 पूर्ण,

	अणु   ixDIDT_SQ_EDC_STALL_PATTERN_7,  DIDT_SQ_EDC_STALL_PATTERN_7__EDC_STALL_PATTERN_7_MASK,   DIDT_SQ_EDC_STALL_PATTERN_7__EDC_STALL_PATTERN_7__SHIFT,     0x5555 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMSEEDCStallDelayConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ EDC STALL DELAYs */
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_1,      DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ0_MASK,  DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ0__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_1,      DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ1_MASK,  DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ1__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_1,      DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ2_MASK,  DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ2__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_1,      DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ3_MASK,  DIDT_SQ_EDC_STALL_DELAY_1__EDC_STALL_DELAY_SQ3__SHIFT,  0x0000 पूर्ण,

	अणु   ixDIDT_SQ_EDC_STALL_DELAY_2,      DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ4_MASK,  DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ4__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_2,      DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ5_MASK,  DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ5__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_2,      DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ6_MASK,  DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ6__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_2,      DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ7_MASK,  DIDT_SQ_EDC_STALL_DELAY_2__EDC_STALL_DELAY_SQ7__SHIFT,  0x0000 पूर्ण,

	अणु   ixDIDT_SQ_EDC_STALL_DELAY_3,      DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ8_MASK,  DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ8__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_3,      DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ9_MASK,  DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ9__SHIFT,  0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_3,      DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ10_MASK, DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ10__SHIFT, 0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_3,      DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ11_MASK, DIDT_SQ_EDC_STALL_DELAY_3__EDC_STALL_DELAY_SQ11__SHIFT, 0x0000 पूर्ण,

	अणु   ixDIDT_SQ_EDC_STALL_DELAY_4,      DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ12_MASK, DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ12__SHIFT, 0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_4,      DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ12_MASK, DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ13__SHIFT, 0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_4,      DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ14_MASK, DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ14__SHIFT, 0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_STALL_DELAY_4,      DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ15_MASK, DIDT_SQ_EDC_STALL_DELAY_4__EDC_STALL_DELAY_SQ15__SHIFT, 0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMSEEDCCtrlResetConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ EDC CTRL */
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_EN_MASK,                       DIDT_SQ_EDC_CTRL__EDC_EN__SHIFT,                        0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_SQ_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_SQ_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMSEEDCCtrlConfig_Vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* SQ EDC CTRL */
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_EN_MASK,                       DIDT_SQ_EDC_CTRL__EDC_EN__SHIFT,                        0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_SW_RST_MASK,                   DIDT_SQ_EDC_CTRL__EDC_SW_RST__SHIFT,                    0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,          DIDT_SQ_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,           0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL_MASK,              DIDT_SQ_EDC_CTRL__EDC_FORCE_STALL__SHIFT,               0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,  DIDT_SQ_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,   0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS_MASK,   DIDT_SQ_EDC_CTRL__EDC_STALL_PATTERN_BIT_NUMS__SHIFT,    0x000E पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,     DIDT_SQ_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,      0x0000 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_EN_MASK,                    DIDT_SQ_EDC_CTRL__GC_EDC_EN__SHIFT,                     0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY_MASK,          DIDT_SQ_EDC_CTRL__GC_EDC_STALL_POLICY__SHIFT,           0x0003 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__GC_EDC_LEVEL_COMB_EN__SHIFT,          0x0001 पूर्ण,
	अणु   ixDIDT_SQ_EDC_CTRL,                DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN_MASK,         DIDT_SQ_EDC_CTRL__SE_EDC_LEVEL_COMB_EN__SHIFT,          0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMGCEDCDroopCtrlConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   mmGC_EDC_DROOP_CTRL,               GC_EDC_DROOP_CTRL__EDC_DROOP_LEVEL_EN_MASK,          GC_EDC_DROOP_CTRL__EDC_DROOP_LEVEL_EN__SHIFT,           0x0001 पूर्ण,
	अणु   mmGC_EDC_DROOP_CTRL,               GC_EDC_DROOP_CTRL__EDC_DROOP_THRESHOLD_MASK,         GC_EDC_DROOP_CTRL__EDC_DROOP_THRESHOLD__SHIFT,          0x0384 पूर्ण,
	अणु   mmGC_EDC_DROOP_CTRL,               GC_EDC_DROOP_CTRL__EDC_DROOP_LEVEL_INDEX_MASK,       GC_EDC_DROOP_CTRL__EDC_DROOP_LEVEL_INDEX__SHIFT,        0x0001 पूर्ण,
	अणु   mmGC_EDC_DROOP_CTRL,               GC_EDC_DROOP_CTRL__AVG_PSM_SEL_MASK,                 GC_EDC_DROOP_CTRL__AVG_PSM_SEL__SHIFT,                  0x0001 पूर्ण,
	अणु   mmGC_EDC_DROOP_CTRL,               GC_EDC_DROOP_CTRL__EDC_LEVEL_SEL_MASK,               GC_EDC_DROOP_CTRL__EDC_LEVEL_SEL__SHIFT,                0x0001 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMGCEDCCtrlResetConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_EN_MASK,                            GC_EDC_CTRL__EDC_EN__SHIFT,                             0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_SW_RST_MASK,                        GC_EDC_CTRL__EDC_SW_RST__SHIFT,                         0x0001 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,               GC_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,                0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_FORCE_STALL_MASK,                   GC_EDC_CTRL__EDC_FORCE_STALL__SHIFT,                    0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,       GC_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,        0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,          GC_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,           0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg   PSMGCEDCCtrlConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_EN_MASK,                            GC_EDC_CTRL__EDC_EN__SHIFT,                             0x0001 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_SW_RST_MASK,                        GC_EDC_CTRL__EDC_SW_RST__SHIFT,                         0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_CLK_EN_OVERRIDE_MASK,               GC_EDC_CTRL__EDC_CLK_EN_OVERRIDE__SHIFT,                0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_FORCE_STALL_MASK,                   GC_EDC_CTRL__EDC_FORCE_STALL__SHIFT,                    0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT_MASK,       GC_EDC_CTRL__EDC_TRIGGER_THROTTLE_LOWBIT__SHIFT,        0x0000 पूर्ण,
	अणु   mmGC_EDC_CTRL,                     GC_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA_MASK,          GC_EDC_CTRL__EDC_ALLOW_WRITE_PWRDELTA__SHIFT,           0x0000 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg    AvfsPSMResetConfig_vega10[]=
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   0x16A02,                         0xFFFFFFFF,                                            0x0,                                                    0x0000005F पूर्ण,
	अणु   0x16A05,                         0xFFFFFFFF,                                            0x0,                                                    0x00000001 पूर्ण,
	अणु   0x16A06,                         0x00000001,                                            0x0,                                                    0x02000000 पूर्ण,
	अणु   0x16A01,                         0xFFFFFFFF,                                            0x0,                                                    0x00003027 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा vega10_didt_config_reg    AvfsPSMInitConfig_vega10[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                 Shअगरt                                                  Value
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   0x16A05,                         0xFFFFFFFF,                                            0x18,                                                    0x00000001 पूर्ण,
	अणु   0x16A05,                         0xFFFFFFFF,                                            0x8,                                                     0x00000003 पूर्ण,
	अणु   0x16A05,                         0xFFFFFFFF,                                            0xa,                                                     0x00000006 पूर्ण,
	अणु   0x16A05,                         0xFFFFFFFF,                                            0x7,                                                     0x00000000 पूर्ण,
	अणु   0x16A06,                         0xFFFFFFFF,                                            0x18,                                                    0x00000001 पूर्ण,
	अणु   0x16A06,                         0xFFFFFFFF,                                            0x19,                                                    0x00000001 पूर्ण,
	अणु   0x16A01,                         0xFFFFFFFF,                                            0x0,                                                     0x00003027 पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल पूर्णांक vega10_program_didt_config_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा vega10_didt_config_reg *config_regs, क्रमागत vega10_didt_config_reg_type reg_type)
अणु
	uपूर्णांक32_t data;

	PP_ASSERT_WITH_CODE((config_regs != शून्य), "[vega10_program_didt_config_registers] Invalid config register table!", वापस -EINVAL);

	जबतक (config_regs->offset != 0xFFFFFFFF) अणु
		चयन (reg_type) अणु
		हाल VEGA10_CONFIGREG_DIDT:
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, config_regs->offset);
			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, config_regs->offset, data);
			अवरोध;
		हाल VEGA10_CONFIGREG_GCCAC:
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_GC_CAC, config_regs->offset);
			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_GC_CAC, config_regs->offset, data);
			अवरोध;
		हाल VEGA10_CONFIGREG_SECAC:
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_SE_CAC, config_regs->offset);
			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_SE_CAC, config_regs->offset, data);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		config_regs++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_program_gc_didt_config_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा vega10_didt_config_reg *config_regs)
अणु
	uपूर्णांक32_t data;

	जबतक (config_regs->offset != 0xFFFFFFFF) अणु
		data = cgs_पढ़ो_रेजिस्टर(hwmgr->device, config_regs->offset);
		data &= ~config_regs->mask;
		data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, config_regs->offset, data);
		config_regs++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega10_didt_set_mask(काष्ठा pp_hwmgr *hwmgr, स्थिर bool enable)
अणु
	uपूर्णांक32_t data;
	uपूर्णांक32_t en = (enable ? 1 : 0);
	uपूर्णांक32_t didt_block_info = SQ_IR_MASK | TCP_IR_MASK | TD_PCC_MASK;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SQRamping)) अणु
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_SQ_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~SQ_Enable_MASK;
		didt_block_info |= en << SQ_Enable_SHIFT;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_DBRamping)) अणु
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_DB_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~DB_Enable_MASK;
		didt_block_info |= en << DB_Enable_SHIFT;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_TDRamping)) अणु
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_TD_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~TD_Enable_MASK;
		didt_block_info |= en << TD_Enable_SHIFT;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_TCPRamping)) अणु
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_TCP_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~TCP_Enable_MASK;
		didt_block_info |= en << TCP_Enable_SHIFT;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_DBRRamping)) अणु
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_DBR_CTRL0, DIDT_CTRL_EN, en);
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_DiDtEDCEnable)) अणु
		अगर (PP_CAP(PHM_Platक्रमmCaps_SQRamping)) अणु
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_SQ_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_SQ_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_SQ_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_SQ_EDC_CTRL, data);
		पूर्ण

		अगर (PP_CAP(PHM_Platक्रमmCaps_DBRamping)) अणु
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DB_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_DB_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_DB_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DB_EDC_CTRL, data);
		पूर्ण

		अगर (PP_CAP(PHM_Platक्रमmCaps_TDRamping)) अणु
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TD_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_TD_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_TD_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TD_EDC_CTRL, data);
		पूर्ण

		अगर (PP_CAP(PHM_Platक्रमmCaps_TCPRamping)) अणु
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TCP_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_TCP_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_TCP_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TCP_EDC_CTRL, data);
		पूर्ण

		अगर (PP_CAP(PHM_Platक्रमmCaps_DBRRamping)) अणु
			data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DBR_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_DBR_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_DBR_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DBR_EDC_CTRL, data);
		पूर्ण
	पूर्ण

	/* For Vega10, SMC करोes not support any mask yet. */
	अगर (enable)
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ConfigureGfxDidt, didt_block_info,
						शून्य);

पूर्ण

अटल पूर्णांक vega10_enable_cac_driving_se_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result;
	uपूर्णांक32_t num_se = 0, count, data;

	num_se = adev->gfx.config.max_shader_engines;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (count = 0; count < num_se; count++) अणु
		data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK | GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK | ( count << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
		WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, data);

		result =  vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtStallCtrlConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtStallPatternConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtWeightConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl1Config_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl2Config_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl3Config_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtTuningCtrlConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SELCacConfig_Vega10, VEGA10_CONFIGREG_SECAC);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl0Config_Vega10, VEGA10_CONFIGREG_DIDT);

		अगर (0 != result)
			अवरोध;
	पूर्ण
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	vega10_didt_set_mask(hwmgr, true);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_cac_driving_se_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_psm_gc_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result;
	uपूर्णांक32_t num_se = 0, count, data;

	num_se = adev->gfx.config.max_shader_engines;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (count = 0; count < num_se; count++) अणु
		data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK | GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK | ( count << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
		WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, data);

		result = vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtStallCtrlConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtStallPatternConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl3Config_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtCtrl0Config_Vega10, VEGA10_CONFIGREG_DIDT);
		अगर (0 != result)
			अवरोध;
	पूर्ण
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	vega10_didt_set_mask(hwmgr, true);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, GCDiDtDroopCtrlConfig_vega10);
	अगर (PP_CAP(PHM_Platक्रमmCaps_GCEDC))
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, GCDiDtCtrl0Config_vega10);

	अगर (PP_CAP(PHM_Platक्रमmCaps_PSM))
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr,  AvfsPSMInitConfig_vega10);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_psm_gc_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t data;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	अगर (PP_CAP(PHM_Platक्रमmCaps_GCEDC)) अणु
		data = 0x00000000;
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGC_DIDT_CTRL0, data);
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_PSM))
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr,  AvfsPSMResetConfig_vega10);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_se_edc_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result;
	uपूर्णांक32_t num_se = 0, count, data;

	num_se = adev->gfx.config.max_shader_engines;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (count = 0; count < num_se; count++) अणु
		data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK | GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK | ( count << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
		WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, data);
		result = vega10_program_didt_config_रेजिस्टरs(hwmgr, SEDiDtWeightConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCStallPatternConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCStallDelayConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCThresholdConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCCtrlResetConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCCtrlConfig_Vega10, VEGA10_CONFIGREG_DIDT);

		अगर (0 != result)
			अवरोध;
	पूर्ण
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	vega10_didt_set_mask(hwmgr, true);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_se_edc_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_psm_gc_edc_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result = 0;
	uपूर्णांक32_t num_se = 0;
	uपूर्णांक32_t count, data;

	num_se = adev->gfx.config.max_shader_engines;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, AvfsPSMResetConfig_vega10);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (count = 0; count < num_se; count++) अणु
		data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK | GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK | ( count << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
		WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, data);
		result = vega10_program_didt_config_रेजिस्टरs(hwmgr, PSMSEEDCStallPatternConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, PSMSEEDCStallDelayConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, PSMSEEDCCtrlResetConfig_Vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, PSMSEEDCCtrlConfig_Vega10, VEGA10_CONFIGREG_DIDT);

		अगर (0 != result)
			अवरोध;
	पूर्ण
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	vega10_didt_set_mask(hwmgr, true);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, PSMGCEDCDroopCtrlConfig_vega10);

	अगर (PP_CAP(PHM_Platक्रमmCaps_GCEDC)) अणु
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, PSMGCEDCCtrlResetConfig_vega10);
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr, PSMGCEDCCtrlConfig_vega10);
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_PSM))
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr,  AvfsPSMInitConfig_vega10);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_psm_gc_edc_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t data;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	अगर (PP_CAP(PHM_Platक्रमmCaps_GCEDC)) अणु
		data = 0x00000000;
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGC_EDC_CTRL, data);
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_PSM))
		vega10_program_gc_didt_config_रेजिस्टरs(hwmgr,  AvfsPSMResetConfig_vega10);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_se_edc_क्रमce_stall_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	result = vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCForceStallPatternConfig_Vega10, VEGA10_CONFIGREG_DIDT);
	result |= vega10_program_didt_config_रेजिस्टरs(hwmgr, SEEDCCtrlForceStallConfig_Vega10, VEGA10_CONFIGREG_DIDT);
	अगर (0 != result)
		वापस result;

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_se_edc_क्रमce_stall_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	result = vega10_disable_se_edc_config(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDtConfig] Pre DIDT disable clock gating failed!", वापस result);

	वापस 0;
पूर्ण

पूर्णांक vega10_enable_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DIDT].supported) अणु
		अगर (data->smu_features[GNLD_DIDT].enabled)
			PP_DBG_LOG("[EnableDiDtConfig] Feature DiDt Already enabled!\n");

		चयन (data->registry_data.didt_mode) अणु
		हाल 0:
			result = vega10_enable_cac_driving_se_didt_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDt] Attempt to enable DiDt Mode 0 Failed!", वापस result);
			अवरोध;
		हाल 2:
			result = vega10_enable_psm_gc_didt_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDt] Attempt to enable DiDt Mode 2 Failed!", वापस result);
			अवरोध;
		हाल 3:
			result = vega10_enable_se_edc_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDt] Attempt to enable DiDt Mode 3 Failed!", वापस result);
			अवरोध;
		हाल 1:
		हाल 4:
		हाल 5:
			result = vega10_enable_psm_gc_edc_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDt] Attempt to enable DiDt Mode 5 Failed!", वापस result);
			अवरोध;
		हाल 6:
			result = vega10_enable_se_edc_क्रमce_stall_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDt] Attempt to enable DiDt Mode 6 Failed!", वापस result);
			अवरोध;
		शेष:
			result = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (0 == result) अणु
			result = vega10_enable_smc_features(hwmgr, true, data->smu_features[GNLD_DIDT].smu_feature_biपंचांगap);
			PP_ASSERT_WITH_CODE((0 == result), "[EnableDiDtConfig] Attempt to Enable DiDt feature Failed!", वापस result);
			data->smu_features[GNLD_DIDT].enabled = true;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक vega10_disable_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DIDT].supported) अणु
		अगर (!data->smu_features[GNLD_DIDT].enabled)
			PP_DBG_LOG("[DisableDiDtConfig] Feature DiDt Already Disabled!\n");

		चयन (data->registry_data.didt_mode) अणु
		हाल 0:
			result = vega10_disable_cac_driving_se_didt_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDt] Attempt to disable DiDt Mode 0 Failed!", वापस result);
			अवरोध;
		हाल 2:
			result = vega10_disable_psm_gc_didt_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDt] Attempt to disable DiDt Mode 2 Failed!", वापस result);
			अवरोध;
		हाल 3:
			result = vega10_disable_se_edc_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDt] Attempt to disable DiDt Mode 3 Failed!", वापस result);
			अवरोध;
		हाल 1:
		हाल 4:
		हाल 5:
			result = vega10_disable_psm_gc_edc_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDt] Attempt to disable DiDt Mode 5 Failed!", वापस result);
			अवरोध;
		हाल 6:
			result = vega10_disable_se_edc_क्रमce_stall_config(hwmgr);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDt] Attempt to disable DiDt Mode 6 Failed!", वापस result);
			अवरोध;
		शेष:
			result = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (0 == result) अणु
			result = vega10_enable_smc_features(hwmgr, false, data->smu_features[GNLD_DIDT].smu_feature_biपंचांगap);
			PP_ASSERT_WITH_CODE((0 == result), "[DisableDiDtConfig] Attempt to Disable DiDt feature Failed!", वापस result);
			data->smu_features[GNLD_DIDT].enabled = false;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

व्योम vega10_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_tdp_table *tdp_table = table_info->tdp_table;
	PPTable_t *table = &(data->smc_state_table.pp_table);

	table->SocketPowerLimit = cpu_to_le16(
			tdp_table->usMaximumPowerDeliveryLimit);
	table->TdcLimit = cpu_to_le16(tdp_table->usTDC);
	table->EdcLimit = cpu_to_le16(tdp_table->usEDCLimit);
	table->TedgeLimit = cpu_to_le16(tdp_table->usTemperatureLimitTedge);
	table->ThotspotLimit = cpu_to_le16(tdp_table->usTemperatureLimitHotspot);
	table->ThbmLimit = cpu_to_le16(tdp_table->usTemperatureLimitHBM);
	table->Tvr_socLimit = cpu_to_le16(tdp_table->usTemperatureLimitVrVddc);
	table->Tvr_memLimit = cpu_to_le16(tdp_table->usTemperatureLimitVrMvdd);
	table->Tliquid1Limit = cpu_to_le16(tdp_table->usTemperatureLimitLiquid1);
	table->Tliquid2Limit = cpu_to_le16(tdp_table->usTemperatureLimitLiquid2);
	table->TplxLimit = cpu_to_le16(tdp_table->usTemperatureLimitPlx);
	table->LoadLineResistance =
			hwmgr->platक्रमm_descriptor.LoadLineSlope * 256;
	table->FitLimit = 0; /* Not used क्रम Vega10 */

	table->Liquid1_I2C_address = tdp_table->ucLiquid1_I2C_address;
	table->Liquid2_I2C_address = tdp_table->ucLiquid2_I2C_address;
	table->Vr_I2C_address = tdp_table->ucVr_I2C_address;
	table->Plx_I2C_address = tdp_table->ucPlx_I2C_address;

	table->Liquid_I2C_LineSCL = tdp_table->ucLiquid_I2C_Line;
	table->Liquid_I2C_LineSDA = tdp_table->ucLiquid_I2C_LineSDA;

	table->Vr_I2C_LineSCL = tdp_table->ucVr_I2C_Line;
	table->Vr_I2C_LineSDA = tdp_table->ucVr_I2C_LineSDA;

	table->Plx_I2C_LineSCL = tdp_table->ucPlx_I2C_Line;
	table->Plx_I2C_LineSDA = tdp_table->ucPlx_I2C_LineSDA;
पूर्ण

पूर्णांक vega10_set_घातer_limit(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->registry_data.enable_pkg_pwr_tracking_feature)
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetPptLimit, n,
				शून्य);

	वापस 0;
पूर्ण

पूर्णांक vega10_enable_घातer_containment(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_tdp_table *tdp_table = table_info->tdp_table;
	पूर्णांक result = 0;

	hwmgr->शेष_घातer_limit = hwmgr->घातer_limit =
			(uपूर्णांक32_t)(tdp_table->usMaximumPowerDeliveryLimit);

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (data->smu_features[GNLD_PPT].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					true, data->smu_features[GNLD_PPT].smu_feature_biपंचांगap),
					"Attempt to enable PPT feature Failed!",
					data->smu_features[GNLD_PPT].supported = false);

		अगर (data->smu_features[GNLD_TDC].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					true, data->smu_features[GNLD_TDC].smu_feature_biपंचांगap),
					"Attempt to enable PPT feature Failed!",
					data->smu_features[GNLD_TDC].supported = false);

		result = vega10_set_घातer_limit(hwmgr, hwmgr->घातer_limit);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to set Default Power Limit in SMC!",
				वापस result);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक vega10_disable_घातer_containment(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (data->smu_features[GNLD_PPT].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					false, data->smu_features[GNLD_PPT].smu_feature_biपंचांगap),
					"Attempt to disable PPT feature Failed!",
					data->smu_features[GNLD_PPT].supported = false);

		अगर (data->smu_features[GNLD_TDC].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					false, data->smu_features[GNLD_TDC].smu_feature_biपंचांगap),
					"Attempt to disable PPT feature Failed!",
					data->smu_features[GNLD_TDC].supported = false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega10_set_overdrive_target_percentage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t adjust_percent)
अणु
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_OverDriveSetPercentage, adjust_percent,
			शून्य);
पूर्ण

पूर्णांक vega10_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक adjust_percent;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		adjust_percent =
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगentPolarity ?
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent :
				(-1 * hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent);
		vega10_set_overdrive_target_percentage(hwmgr,
				(uपूर्णांक32_t)adjust_percent);
	पूर्ण
	वापस 0;
पूर्ण
