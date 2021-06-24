<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#समावेश "pp_debug.h"
#समावेश "hwmgr.h"
#समावेश "smumgr.h"
#समावेश "smu7_hwmgr.h"
#समावेश "smu7_powertune.h"
#समावेश "smu7_common.h"

#घोषणा VOLTAGE_SCALE  4

अटल uपूर्णांक32_t DIDTBlock_Info = SQ_IR_MASK | TCP_IR_MASK | TD_PCC_MASK;

अटल uपूर्णांक32_t Polaris11_DIDTBlock_Info = SQ_PCC_MASK | TCP_IR_MASK | TD_PCC_MASK;

अटल स्थिर काष्ठा gpu_pt_config_reg GCCACConfig_Polaris10[] = अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x04060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x000E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x008E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x010E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x018E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x020E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg GCCACConfig_Polaris11[] = अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00060011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00860011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01060011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01860011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02060011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02860011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03060011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03860011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x04060011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x000E0011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x008E0011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x010E0011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x018E0011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x020E0011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00100011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00900011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01100011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01900011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02100011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
	अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02900011, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg DIDTConfig_Polaris10[] = अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT0__SHIFT,                  0x0073,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT1__SHIFT,                  0x00ab,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT3__SHIFT,                  0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0067,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT5__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0027,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT8_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT8__SHIFT,                 0x00aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT9_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT9__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT10_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT10__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT11_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT11__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                      DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                      DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__UNUSED_0_MASK,                    DIDT_SQ_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_SQ_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_0_MASK,                       DIDT_SQ_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_1_MASK,                       DIDT_SQ_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_2_MASK,                       DIDT_SQ_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x0ebb,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__UNUSED_0_MASK,                  DIDT_SQ_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x3153,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_SQ_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,                   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__UNUSED_0_MASK,                       DIDT_SQ_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT0__SHIFT,                  0x000a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT1__SHIFT,                  0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0017,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT3__SHIFT,                  0x002f,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT5__SHIFT,                  0x005d,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                      DIDT_TD_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                      DIDT_TD_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__UNUSED_0_MASK,                    DIDT_TD_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_TD_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_0_MASK,                       DIDT_TD_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_1_MASK,                       DIDT_TD_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_2_MASK,                       DIDT_TD_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__UNUSED_0_MASK,                  DIDT_TD_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TD_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0009,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0009,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__UNUSED_0_MASK,                       DIDT_TD_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT0_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT0__SHIFT,                 0x0004,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT1_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT1__SHIFT,                 0x0037,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT2_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT2__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT3_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT3__SHIFT,                 0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT4_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT4__SHIFT,                 0x0054,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT5_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT5__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT6_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT6__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT7_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT7__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                     DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                   0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                     DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                   0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__UNUSED_0_MASK,                   DIDT_TCP_CTRL_OCP__UNUSED_0__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__OCP_MAX_POWER_MASK,              DIDT_TCP_CTRL_OCP__OCP_MAX_POWER__SHIFT,            0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,               DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,             0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_0_MASK,                      DIDT_TCP_CTRL2__UNUSED_0__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,      DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,    0x0032,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_1_MASK,                      DIDT_TCP_CTRL2__UNUSED_1__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,      DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_2_MASK,                      DIDT_TCP_CTRL2__UNUSED_2__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT, 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__UNUSED_0_MASK,                 DIDT_TCP_STALL_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,      DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK,                DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT,              0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TCP_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__UNUSED_0_MASK,                       DIDT_TCP_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg DIDTConfig_Polaris11[] = अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT0__SHIFT,                  0x0073,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT1__SHIFT,                  0x00ab,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT3__SHIFT,                  0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0067,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT5__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0027,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT8_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT8__SHIFT,                 0x00aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT9_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT9__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT10_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT10__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT11_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT11__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                      DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                      DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__UNUSED_0_MASK,                    DIDT_SQ_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_SQ_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_0_MASK,                       DIDT_SQ_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_1_MASK,                       DIDT_SQ_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_2_MASK,                       DIDT_SQ_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__UNUSED_0_MASK,                  DIDT_SQ_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_SQ_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,                   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__UNUSED_0_MASK,                       DIDT_SQ_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT0__SHIFT,                  0x000a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT1__SHIFT,                  0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0017,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT3__SHIFT,                  0x002f,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT5__SHIFT,                  0x005d,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                      DIDT_TD_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                      DIDT_TD_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__UNUSED_0_MASK,                    DIDT_TD_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_TD_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_0_MASK,                       DIDT_TD_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_1_MASK,                       DIDT_TD_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_2_MASK,                       DIDT_TD_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__UNUSED_0_MASK,                  DIDT_TD_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TD_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__UNUSED_0_MASK,                       DIDT_TD_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT0_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT0__SHIFT,                 0x0004,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT1_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT1__SHIFT,                 0x0037,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT2_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT2__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT3_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT3__SHIFT,                 0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT4_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT4__SHIFT,                 0x0054,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT5_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT5__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT6_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT6__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT7_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT7__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                     DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                   0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                     DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                   0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__UNUSED_0_MASK,                   DIDT_TCP_CTRL_OCP__UNUSED_0__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__OCP_MAX_POWER_MASK,              DIDT_TCP_CTRL_OCP__OCP_MAX_POWER__SHIFT,            0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,               DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,             0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_0_MASK,                      DIDT_TCP_CTRL2__UNUSED_0__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,      DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,    0x0032,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_1_MASK,                      DIDT_TCP_CTRL2__UNUSED_1__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,      DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_2_MASK,                      DIDT_TCP_CTRL2__UNUSED_2__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT, 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__UNUSED_0_MASK,                 DIDT_TCP_STALL_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,      DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK,                DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT,              0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TCP_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__UNUSED_0_MASK,                       DIDT_TCP_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg DIDTConfig_Polaris12[] = अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT0__SHIFT,                  0x0073,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT1__SHIFT,                  0x00ab,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT3__SHIFT,                  0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0067,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT5__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0027,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT8_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT8__SHIFT,                 0x00aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT9_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT9__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT10_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT10__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT11_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT11__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                      DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                      DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__UNUSED_0_MASK,                    DIDT_SQ_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_SQ_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_0_MASK,                       DIDT_SQ_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_1_MASK,                       DIDT_SQ_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_2_MASK,                       DIDT_SQ_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x0ebb,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__UNUSED_0_MASK,                  DIDT_SQ_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x3153,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_SQ_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,                   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__UNUSED_0_MASK,                       DIDT_SQ_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT0__SHIFT,                  0x000a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT1__SHIFT,                  0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0017,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT3__SHIFT,                  0x002f,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT5__SHIFT,                  0x005d,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                      DIDT_TD_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                      DIDT_TD_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__UNUSED_0_MASK,                    DIDT_TD_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_TD_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_0_MASK,                       DIDT_TD_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_1_MASK,                       DIDT_TD_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_2_MASK,                       DIDT_TD_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__UNUSED_0_MASK,                  DIDT_TD_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TD_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__UNUSED_0_MASK,                       DIDT_TD_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT0_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT0__SHIFT,                 0x0004,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT1_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT1__SHIFT,                 0x0037,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT2_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT2__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT3_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT3__SHIFT,                 0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT4_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT4__SHIFT,                 0x0054,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT5_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT5__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT6_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT6__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT7_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT7__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                     DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                   0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                     DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                   0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__UNUSED_0_MASK,                   DIDT_TCP_CTRL_OCP__UNUSED_0__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__OCP_MAX_POWER_MASK,              DIDT_TCP_CTRL_OCP__OCP_MAX_POWER__SHIFT,            0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,               DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,             0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_0_MASK,                      DIDT_TCP_CTRL2__UNUSED_0__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,      DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,    0x0032,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_1_MASK,                      DIDT_TCP_CTRL2__UNUSED_1__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,      DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_2_MASK,                      DIDT_TCP_CTRL2__UNUSED_2__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT, 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__UNUSED_0_MASK,                 DIDT_TCP_STALL_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,      DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK,                DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT,              0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TCP_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__UNUSED_0_MASK,                       DIDT_TCP_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   0xFFFFFFFF  पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg DIDTConfig_Polaris11_Kicker[] =
अणु
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *      Offset                             Mask                                                Shअगरt                                               Value       Type
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */
	/* DIDT_SQ */
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT0__SHIFT,                  0x004c,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT1__SHIFT,                  0x00d0,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0069,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT3__SHIFT,                  0x0048,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT4__SHIFT,                  0x005f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT5__SHIFT,                  0x007a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT6__SHIFT,                  0x001f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT7__SHIFT,                  0x002d,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT8_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT8__SHIFT,                 0x0088,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT9_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT9__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT10_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT10__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT11_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT11__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                      DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                      DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__UNUSED_0_MASK,                    DIDT_SQ_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_SQ_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_0_MASK,                       DIDT_SQ_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_1_MASK,                       DIDT_SQ_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_2_MASK,                       DIDT_SQ_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__UNUSED_0_MASK,                  DIDT_SQ_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_SQ_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,                   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__UNUSED_0_MASK,                       DIDT_SQ_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	/* DIDT_TD */
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT0__SHIFT,                  0x000a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT1__SHIFT,                  0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0017,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT3__SHIFT,                  0x002f,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT5__SHIFT,                  0x005d,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                      DIDT_TD_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                      DIDT_TD_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__UNUSED_0_MASK,                    DIDT_TD_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_TD_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_0_MASK,                       DIDT_TD_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_1_MASK,                       DIDT_TD_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_2_MASK,                       DIDT_TD_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__UNUSED_0_MASK,                  DIDT_TD_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TD_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0008,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__UNUSED_0_MASK,                       DIDT_TD_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	/* DIDT_TCP */
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT0_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT0__SHIFT,                 0x0004,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT1_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT1__SHIFT,                 0x0037,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT2_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT2__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT3_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT3__SHIFT,                 0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT4_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT4__SHIFT,                 0x0054,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT5_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT5__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT6_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT6__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT7_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT7__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                     DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                   0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                     DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                   0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__UNUSED_0_MASK,                   DIDT_TCP_CTRL_OCP__UNUSED_0__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__OCP_MAX_POWER_MASK,              DIDT_TCP_CTRL_OCP__OCP_MAX_POWER__SHIFT,            0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,               DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,             0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_0_MASK,                      DIDT_TCP_CTRL2__UNUSED_0__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,      DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,    0x0032,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_1_MASK,                      DIDT_TCP_CTRL2__UNUSED_1__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,      DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_2_MASK,                      DIDT_TCP_CTRL2__UNUSED_2__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT, 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT,0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__UNUSED_0_MASK,                 DIDT_TCP_STALL_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,      DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK,                DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT,              0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TCP_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
	अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__UNUSED_0_MASK,                       DIDT_TCP_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

	अणु   0xFFFFFFFF  पूर्ण  /* End of list */
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg GCCACConfig_VegaM[] =
अणु
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//      Offset                             Mask                                                Shअगरt                                               Value       Type
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // DIDT_SQ
    //
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x03860013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x04060013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

    // DIDT_TD
    //
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x000E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x008E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x010E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x018E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x020E0013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

    // DIDT_TCP
    //
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x00900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x01900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02100013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,
    अणु   ixGC_CAC_CNTL,                     0xFFFFFFFF,                                         0,                                                  0x02900013, GPU_CONFIGREG_GC_CAC_IND पूर्ण,

    अणु   0xFFFFFFFF  पूर्ण  // End of list
पूर्ण;

अटल स्थिर काष्ठा gpu_pt_config_reg DIDTConfig_VegaM[] =
अणु
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//      Offset                             Mask                                                Shअगरt                                               Value       Type
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // DIDT_SQ
    //
    अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT0__SHIFT,                  0x0073,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT1__SHIFT,                  0x00ab,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT0_3,               DIDT_SQ_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_SQ_WEIGHT0_3__WEIGHT3__SHIFT,                  0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0067,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT5__SHIFT,                  0x0084,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0027,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT4_7,               DIDT_SQ_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_SQ_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT8_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT8__SHIFT,                 0x00aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT9_MASK,                   DIDT_SQ_WEIGHT8_11__WEIGHT9__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT10_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT10__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_WEIGHT8_11,              DIDT_SQ_WEIGHT8_11__WEIGHT11_MASK,                  DIDT_SQ_WEIGHT8_11__WEIGHT11__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MIN_POWER_MASK,                      DIDT_SQ_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL1,                   DIDT_SQ_CTRL1__MAX_POWER_MASK,                      DIDT_SQ_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__UNUSED_0_MASK,                    DIDT_SQ_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL_OCP,                DIDT_SQ_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_SQ_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_SQ_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_0_MASK,                       DIDT_SQ_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_SQ_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x005a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_1_MASK,                       DIDT_SQ_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_SQ_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL2,                   DIDT_SQ_CTRL2__UNUSED_2_MASK,                       DIDT_SQ_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_SQ_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_SQ_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_SQ_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x0ebb,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_STALL_CTRL,              DIDT_SQ_STALL_CTRL__UNUSED_0_MASK,                  DIDT_SQ_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_SQ_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x3853,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_SQ_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x3153,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_TUNING_CTRL,             DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_SQ_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_SQ_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__PHASE_OFFSET_MASK,                   DIDT_SQ_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_SQ_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_SQ_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_SQ_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_SQ_CTRL0,                   DIDT_SQ_CTRL0__UNUSED_0_MASK,                       DIDT_SQ_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    // DIDT_TD
    //
    अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT0_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT0__SHIFT,                  0x000a,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT1_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT1__SHIFT,                  0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT2_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT2__SHIFT,                  0x0017,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT0_3,               DIDT_TD_WEIGHT0_3__WEIGHT3_MASK,                    DIDT_TD_WEIGHT0_3__WEIGHT3__SHIFT,                  0x002f,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT4_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT4__SHIFT,                  0x0046,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT5_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT5__SHIFT,                  0x005d,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT6_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT6__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_WEIGHT4_7,               DIDT_TD_WEIGHT4_7__WEIGHT7_MASK,                    DIDT_TD_WEIGHT4_7__WEIGHT7__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MIN_POWER_MASK,                      DIDT_TD_CTRL1__MIN_POWER__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL1,                   DIDT_TD_CTRL1__MAX_POWER_MASK,                      DIDT_TD_CTRL1__MAX_POWER__SHIFT,                    0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__UNUSED_0_MASK,                    DIDT_TD_CTRL_OCP__UNUSED_0__SHIFT,                  0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL_OCP,                DIDT_TD_CTRL_OCP__OCP_MAX_POWER_MASK,               DIDT_TD_CTRL_OCP__OCP_MAX_POWER__SHIFT,             0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__MAX_POWER_DELTA_MASK,                DIDT_TD_CTRL2__MAX_POWER_DELTA__SHIFT,              0x3fff,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_0_MASK,                       DIDT_TD_CTRL2__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,       DIDT_TD_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,     0x000f,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_1_MASK,                       DIDT_TD_CTRL2__UNUSED_1__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,       DIDT_TD_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL2,                   DIDT_TD_CTRL2__UNUSED_2_MASK,                       DIDT_TD_CTRL2__UNUSED_2__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,    DIDT_TD_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT,  0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,       DIDT_TD_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,     0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,   DIDT_TD_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT, 0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_STALL_CTRL,              DIDT_TD_STALL_CTRL__UNUSED_0_MASK,                  DIDT_TD_STALL_CTRL__UNUSED_0__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,       DIDT_TD_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,       DIDT_TD_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,     0x0dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_TUNING_CTRL,             DIDT_TD_TUNING_CTRL__UNUSED_0_MASK,                 DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TD_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TD_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TD_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TD_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TD_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0009,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TD_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0009,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TD_CTRL0,                   DIDT_TD_CTRL0__UNUSED_0_MASK,                       DIDT_TD_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    // DIDT_TCP
    //
    अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT0_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT0__SHIFT,                 0x0004,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT1_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT1__SHIFT,                 0x0037,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT2_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT2__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT0_3,              DIDT_TCP_WEIGHT0_3__WEIGHT3_MASK,                   DIDT_TCP_WEIGHT0_3__WEIGHT3__SHIFT,                 0x00ff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT4_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT4__SHIFT,                 0x0054,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT5_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT5__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT6_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT6__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_WEIGHT4_7,              DIDT_TCP_WEIGHT4_7__WEIGHT7_MASK,                   DIDT_TCP_WEIGHT4_7__WEIGHT7__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MIN_POWER_MASK,                     DIDT_TCP_CTRL1__MIN_POWER__SHIFT,                   0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL1,                  DIDT_TCP_CTRL1__MAX_POWER_MASK,                     DIDT_TCP_CTRL1__MAX_POWER__SHIFT,                   0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__UNUSED_0_MASK,                   DIDT_TCP_CTRL_OCP__UNUSED_0__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL_OCP,               DIDT_TCP_CTRL_OCP__OCP_MAX_POWER_MASK,              DIDT_TCP_CTRL_OCP__OCP_MAX_POWER__SHIFT,            0xffff,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__MAX_POWER_DELTA_MASK,               DIDT_TCP_CTRL2__MAX_POWER_DELTA__SHIFT,             0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_0_MASK,                      DIDT_TCP_CTRL2__UNUSED_0__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE_MASK,      DIDT_TCP_CTRL2__SHORT_TERM_INTERVAL_SIZE__SHIFT,    0x0032,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_1_MASK,                      DIDT_TCP_CTRL2__UNUSED_1__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO_MASK,      DIDT_TCP_CTRL2__LONG_TERM_INTERVAL_RATIO__SHIFT,    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL2,                  DIDT_TCP_CTRL2__UNUSED_2_MASK,                      DIDT_TCP_CTRL2__UNUSED_2__SHIFT,                    0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE_MASK,   DIDT_TCP_STALL_CTRL__DIDT_STALL_CTRL_ENABLE__SHIFT, 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_HI__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO_MASK,      DIDT_TCP_STALL_CTRL__DIDT_STALL_DELAY_LO__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD_MASK,  DIDT_TCP_STALL_CTRL__DIDT_HI_POWER_THRESHOLD__SHIFT,0x01aa,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_STALL_CTRL,             DIDT_TCP_STALL_CTRL__UNUSED_0_MASK,                 DIDT_TCP_STALL_CTRL__UNUSED_0__SHIFT,               0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE_MASK,      DIDT_TCP_TUNING_CTRL__DIDT_TUNING_ENABLE__SHIFT,    0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_HI__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO_MASK,      DIDT_TCP_TUNING_CTRL__MAX_POWER_DELTA_LO__SHIFT,    0x3dde,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_TUNING_CTRL,            DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK,                DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT,              0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK,                   DIDT_TCP_CTRL0__DIDT_CTRL_EN__SHIFT,                 0x0001,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__USE_REF_CLOCK_MASK,                  DIDT_TCP_CTRL0__USE_REF_CLOCK__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__PHASE_OFFSET_MASK,                   DIDT_TCP_CTRL0__PHASE_OFFSET__SHIFT,                 0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CTRL_RST_MASK,                  DIDT_TCP_CTRL0__DIDT_CTRL_RST__SHIFT,                0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE_MASK,           DIDT_TCP_CTRL0__DIDT_CLK_EN_OVERRIDE__SHIFT,         0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_HI__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO_MASK,     DIDT_TCP_CTRL0__DIDT_MAX_STALLS_ALLOWED_LO__SHIFT,   0x0010,     GPU_CONFIGREG_DIDT_IND पूर्ण,
    अणु   ixDIDT_TCP_CTRL0,                   DIDT_TCP_CTRL0__UNUSED_0_MASK,                       DIDT_TCP_CTRL0__UNUSED_0__SHIFT,                     0x0000,     GPU_CONFIGREG_DIDT_IND पूर्ण,

    अणु   0xFFFFFFFF  पूर्ण  // End of list
पूर्ण;
अटल पूर्णांक smu7_enable_didt(काष्ठा pp_hwmgr *hwmgr, स्थिर bool enable)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t en = enable ? 1 : 0;
	uपूर्णांक32_t block_en = 0;
	पूर्णांक32_t result = 0;
	uपूर्णांक32_t didt_block;

	अगर ((hwmgr->chip_id == CHIP_POLARIS11) &&
	    (adev->pdev->subप्रणाली_venकरोr != 0x106B))
		didt_block = Polaris11_DIDTBlock_Info;
	अन्यथा
		didt_block = DIDTBlock_Info;

	block_en = PP_CAP(PHM_Platक्रमmCaps_SQRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_SQ_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~SQ_Enable_MASK;
	didt_block |= block_en << SQ_Enable_SHIFT;

	block_en = PP_CAP(PHM_Platक्रमmCaps_DBRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_DB_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~DB_Enable_MASK;
	didt_block |= block_en << DB_Enable_SHIFT;

	block_en = PP_CAP(PHM_Platक्रमmCaps_TDRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_TD_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~TD_Enable_MASK;
	didt_block |= block_en << TD_Enable_SHIFT;

	block_en = PP_CAP(PHM_Platक्रमmCaps_TCPRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_TCP_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~TCP_Enable_MASK;
	didt_block |= block_en << TCP_Enable_SHIFT;

	अगर (enable)
		result = smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_Didt_Block_Function,
						didt_block,
						शून्य);

	वापस result;
पूर्ण

अटल पूर्णांक smu7_program_pt_config_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
				स्थिर काष्ठा gpu_pt_config_reg *cac_config_regs)
अणु
	स्थिर काष्ठा gpu_pt_config_reg *config_regs = cac_config_regs;
	uपूर्णांक32_t cache = 0;
	uपूर्णांक32_t data = 0;

	PP_ASSERT_WITH_CODE((config_regs != शून्य), "Invalid config register table.", वापस -EINVAL);

	जबतक (config_regs->offset != 0xFFFFFFFF) अणु
		अगर (config_regs->type == GPU_CONFIGREG_CACHE)
			cache |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
		अन्यथा अणु
			चयन (config_regs->type) अणु
			हाल GPU_CONFIGREG_SMC_IND:
				data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, config_regs->offset);
				अवरोध;

			हाल GPU_CONFIGREG_DIDT_IND:
				data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, config_regs->offset);
				अवरोध;

			हाल GPU_CONFIGREG_GC_CAC_IND:
				data = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_GC_CAC, config_regs->offset);
				अवरोध;

			शेष:
				data = cgs_पढ़ो_रेजिस्टर(hwmgr->device, config_regs->offset);
				अवरोध;
			पूर्ण

			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
			data |= cache;

			चयन (config_regs->type) अणु
			हाल GPU_CONFIGREG_SMC_IND:
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, config_regs->offset, data);
				अवरोध;

			हाल GPU_CONFIGREG_DIDT_IND:
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__DIDT, config_regs->offset, data);
				अवरोध;

			हाल GPU_CONFIGREG_GC_CAC_IND:
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG_GC_CAC, config_regs->offset, data);
				अवरोध;

			शेष:
				cgs_ग_लिखो_रेजिस्टर(hwmgr->device, config_regs->offset, data);
				अवरोध;
			पूर्ण
			cache = 0;
		पूर्ण

		config_regs++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu7_enable_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	uपूर्णांक32_t num_se = 0;
	uपूर्णांक32_t count, value, value2;
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t efuse;

	num_se = adev->gfx.config.max_shader_engines;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SQRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_DBRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_TDRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_TCPRamping)) अणु

		amdgpu_gfx_rlc_enter_safe_mode(adev);
		mutex_lock(&adev->grbm_idx_mutex);
		value = 0;
		value2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmGRBM_GFX_INDEX);
		क्रम (count = 0; count < num_se; count++) अणु
			value = SYS_GRBM_GFX_INDEX_DATA__INSTANCE_BROADCAST_WRITES_MASK
				| SYS_GRBM_GFX_INDEX_DATA__SH_BROADCAST_WRITES_MASK
				| (count << SYS_GRBM_GFX_INDEX_DATA__SE_INDEX__SHIFT);
			cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGRBM_GFX_INDEX, value);

			अगर (hwmgr->chip_id == CHIP_POLARIS10) अणु
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, GCCACConfig_Polaris10);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, DIDTConfig_Polaris10);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
			पूर्ण अन्यथा अगर (hwmgr->chip_id == CHIP_POLARIS11) अणु
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, GCCACConfig_Polaris11);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);

				अगर (ASICID_IS_P21(adev->pdev->device, adev->pdev->revision) ||
				    ASICID_IS_P31(adev->pdev->device, adev->pdev->revision))
					result = smu7_program_pt_config_रेजिस्टरs(hwmgr, DIDTConfig_Polaris11_Kicker);
				अन्यथा
					result = smu7_program_pt_config_रेजिस्टरs(hwmgr, DIDTConfig_Polaris11);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
			पूर्ण अन्यथा अगर (hwmgr->chip_id == CHIP_POLARIS12) अणु
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, GCCACConfig_Polaris11);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, DIDTConfig_Polaris12);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
			पूर्ण अन्यथा अगर (hwmgr->chip_id == CHIP_VEGAM) अणु
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, GCCACConfig_VegaM);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
				result = smu7_program_pt_config_रेजिस्टरs(hwmgr, DIDTConfig_VegaM);
				PP_ASSERT_WITH_CODE((result == 0), "DIDT Config failed.", जाओ error);
			पूर्ण
		पूर्ण
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGRBM_GFX_INDEX, value2);

		result = smu7_enable_didt(hwmgr, true);
		PP_ASSERT_WITH_CODE((result == 0), "EnableDiDt failed.", जाओ error);

		अगर (hwmgr->chip_id == CHIP_POLARIS11) अणु
			result = smum_send_msg_to_smc(hwmgr,
						(uपूर्णांक16_t)(PPSMC_MSG_EnableDpmDidt),
						शून्य);
			PP_ASSERT_WITH_CODE((0 == result),
					"Failed to enable DPM DIDT.", जाओ error);

			अगर (ASICID_IS_P21(adev->pdev->device, adev->pdev->revision) ||
			    ASICID_IS_P31(adev->pdev->device, adev->pdev->revision)) अणु
				result = smum_send_msg_to_smc(hwmgr,
							(uपूर्णांक16_t)(PPSMC_MSG_EnableDpmMcBlackout),
							शून्य);
				PP_ASSERT_WITH_CODE((0 == result),
						"Failed to enable workaround for CRC issue.", जाओ error);
			पूर्ण अन्यथा अणु
				atomctrl_पढ़ो_efuse(hwmgr, 547, 547, &efuse);
				अगर (efuse == 1) अणु
					result = smum_send_msg_to_smc(hwmgr,
								(uपूर्णांक16_t)(PPSMC_MSG_EnableDpmMcBlackout),
								शून्य);
					PP_ASSERT_WITH_CODE((0 == result),
							"Failed to enable workaround for CRC issue.", जाओ error);
				पूर्ण अन्यथा अणु
					result = smum_send_msg_to_smc(hwmgr,
								(uपूर्णांक16_t)(PPSMC_MSG_DisableDpmMcBlackout),
								शून्य);
					PP_ASSERT_WITH_CODE((0 == result),
							"Failed to enable workaround for CRC issue.", जाओ error);
				पूर्ण
			पूर्ण
		पूर्ण

		mutex_unlock(&adev->grbm_idx_mutex);
		amdgpu_gfx_rlc_निकास_safe_mode(adev);
	पूर्ण

	वापस 0;
error:
	mutex_unlock(&adev->grbm_idx_mutex);
	amdgpu_gfx_rlc_निकास_safe_mode(adev);
	वापस result;
पूर्ण

पूर्णांक smu7_disable_didt_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SQRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_DBRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_TDRamping) ||
	    PP_CAP(PHM_Platक्रमmCaps_TCPRamping)) अणु

		amdgpu_gfx_rlc_enter_safe_mode(adev);

		result = smu7_enable_didt(hwmgr, false);
		PP_ASSERT_WITH_CODE((result == 0),
				"Post DIDT enable clock gating failed.",
				जाओ error);
		अगर (hwmgr->chip_id == CHIP_POLARIS11) अणु
			result = smum_send_msg_to_smc(hwmgr,
						(uपूर्णांक16_t)(PPSMC_MSG_DisableDpmDidt),
						शून्य);
			PP_ASSERT_WITH_CODE((0 == result),
					"Failed to disable DPM DIDT.", जाओ error);
		पूर्ण
		amdgpu_gfx_rlc_निकास_safe_mode(adev);
	पूर्ण

	वापस 0;
error:
	amdgpu_gfx_rlc_निकास_safe_mode(adev);
	वापस result;
पूर्ण

पूर्णांक smu7_enable_smc_cac(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_CAC)) अणु
		पूर्णांक smc_result;
		smc_result = smum_send_msg_to_smc(hwmgr,
				(uपूर्णांक16_t)(PPSMC_MSG_EnableCac),
				शून्य);
		PP_ASSERT_WITH_CODE((0 == smc_result),
				"Failed to enable CAC in SMC.", result = -1);

		data->cac_enabled = (0 == smc_result) ? true : false;
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक smu7_disable_smc_cac(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_CAC) && data->cac_enabled) अणु
		पूर्णांक smc_result = smum_send_msg_to_smc(hwmgr,
				(uपूर्णांक16_t)(PPSMC_MSG_DisableCac),
				शून्य);
		PP_ASSERT_WITH_CODE((smc_result == 0),
				"Failed to disable CAC in SMC.", result = -1);

		data->cac_enabled = false;
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक smu7_set_घातer_limit(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->घातer_containment_features &
			POWERCONTAINMENT_FEATURE_PkgPwrLimit)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_PkgPwrSetLimit,
				n<<8,
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_set_overdriver_target_tdp(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t target_tdp)
अणु
	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_OverDriveSetTargetTdp,
			target_tdp,
			शून्य);
पूर्ण

पूर्णांक smu7_enable_घातer_containment(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	पूर्णांक smc_result;
	पूर्णांक result = 0;
	काष्ठा phm_cac_tdp_table *cac_table;

	data->घातer_containment_features = 0;
	अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		cac_table = table_info->cac_dtp_table;
	अन्यथा
		cac_table = hwmgr->dyn_state.cac_dtp_table;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (data->enable_tdc_limit_feature) अणु
			smc_result = smum_send_msg_to_smc(hwmgr,
					(uपूर्णांक16_t)(PPSMC_MSG_TDCLimitEnable),
					शून्य);
			PP_ASSERT_WITH_CODE((0 == smc_result),
					"Failed to enable TDCLimit in SMC.", result = -1;);
			अगर (0 == smc_result)
				data->घातer_containment_features |=
						POWERCONTAINMENT_FEATURE_TDCLimit;
		पूर्ण

		अगर (data->enable_pkg_pwr_tracking_feature) अणु
			smc_result = smum_send_msg_to_smc(hwmgr,
					(uपूर्णांक16_t)(PPSMC_MSG_PkgPwrLimitEnable),
					शून्य);
			PP_ASSERT_WITH_CODE((0 == smc_result),
					"Failed to enable PkgPwrTracking in SMC.", result = -1;);
			अगर (0 == smc_result) अणु
				hwmgr->शेष_घातer_limit = hwmgr->घातer_limit =
						cac_table->usMaximumPowerDeliveryLimit;
				data->घातer_containment_features |=
						POWERCONTAINMENT_FEATURE_PkgPwrLimit;

				अगर (smu7_set_घातer_limit(hwmgr, hwmgr->घातer_limit))
					pr_err("Failed to set Default Power Limit in SMC!");
			पूर्ण
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक smu7_disable_घातer_containment(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment) &&
	    data->घातer_containment_features) अणु
		पूर्णांक smc_result;

		अगर (data->घातer_containment_features &
				POWERCONTAINMENT_FEATURE_TDCLimit) अणु
			smc_result = smum_send_msg_to_smc(hwmgr,
					(uपूर्णांक16_t)(PPSMC_MSG_TDCLimitDisable),
					शून्य);
			PP_ASSERT_WITH_CODE((smc_result == 0),
					"Failed to disable TDCLimit in SMC.",
					result = smc_result);
		पूर्ण

		अगर (data->घातer_containment_features &
				POWERCONTAINMENT_FEATURE_DTE) अणु
			smc_result = smum_send_msg_to_smc(hwmgr,
					(uपूर्णांक16_t)(PPSMC_MSG_DisableDTE),
					शून्य);
			PP_ASSERT_WITH_CODE((smc_result == 0),
					"Failed to disable DTE in SMC.",
					result = smc_result);
		पूर्ण

		अगर (data->घातer_containment_features &
				POWERCONTAINMENT_FEATURE_PkgPwrLimit) अणु
			smc_result = smum_send_msg_to_smc(hwmgr,
					(uपूर्णांक16_t)(PPSMC_MSG_PkgPwrLimitDisable),
					शून्य);
			PP_ASSERT_WITH_CODE((smc_result == 0),
					"Failed to disable PkgPwrTracking in SMC.",
					result = smc_result);
		पूर्ण
		data->घातer_containment_features = 0;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक smu7_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_cac_tdp_table *cac_table;

	पूर्णांक adjust_percent, target_tdp;
	पूर्णांक result = 0;

	अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		cac_table = table_info->cac_dtp_table;
	अन्यथा
		cac_table = hwmgr->dyn_state.cac_dtp_table;
	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		/* adjusपंचांगent percentage has alपढ़ोy been validated */
		adjust_percent = hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगentPolarity ?
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent :
				(-1 * hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent);

		अगर (hwmgr->chip_id > CHIP_TONGA)
			target_tdp = ((100 + adjust_percent) * (पूर्णांक)(cac_table->usTDP * 256)) / 100;
		अन्यथा
			target_tdp = ((100 + adjust_percent) * (पूर्णांक)(cac_table->usConfigurableTDP * 256)) / 100;

		result = smu7_set_overdriver_target_tdp(hwmgr, (uपूर्णांक32_t)target_tdp);
	पूर्ण

	वापस result;
पूर्ण
