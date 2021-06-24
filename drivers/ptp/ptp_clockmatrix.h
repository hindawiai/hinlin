<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PTP hardware घड़ी driver क्रम the IDT ClockMatrix(TM) family of timing and
 * synchronization devices.
 *
 * Copyright (C) 2019 Integrated Device Technology, Inc., a Renesas Company.
 */
#अगर_अघोषित PTP_IDTCLOCKMATRIX_H
#घोषणा PTP_IDTCLOCKMATRIX_H

#समावेश <linux/kसमय.स>

#समावेश "idt8a340_reg.h"

#घोषणा FW_खाताNAME	"idtcm.bin"
#घोषणा MAX_TOD		(4)
#घोषणा MAX_PLL		(8)

#घोषणा MAX_ABS_WRITE_PHASE_PICOSECONDS (107374182350LL)

#घोषणा TOD_MASK_ADDR		(0xFFA5)
#घोषणा DEFAULT_TOD_MASK	(0x04)

#घोषणा SET_U16_LSB(orig, val8) (orig = (0xff00 & (orig)) | (val8))
#घोषणा SET_U16_MSB(orig, val8) (orig = (0x00ff & (orig)) | (val8 << 8))

#घोषणा TOD0_PTP_PLL_ADDR		(0xFFA8)
#घोषणा TOD1_PTP_PLL_ADDR		(0xFFA9)
#घोषणा TOD2_PTP_PLL_ADDR		(0xFFAA)
#घोषणा TOD3_PTP_PLL_ADDR		(0xFFAB)

#घोषणा TOD0_OUT_ALIGN_MASK_ADDR	(0xFFB0)
#घोषणा TOD1_OUT_ALIGN_MASK_ADDR	(0xFFB2)
#घोषणा TOD2_OUT_ALIGN_MASK_ADDR	(0xFFB4)
#घोषणा TOD3_OUT_ALIGN_MASK_ADDR	(0xFFB6)

#घोषणा DEFAULT_OUTPUT_MASK_PLL0	(0x003)
#घोषणा DEFAULT_OUTPUT_MASK_PLL1	(0x00c)
#घोषणा DEFAULT_OUTPUT_MASK_PLL2	(0x030)
#घोषणा DEFAULT_OUTPUT_MASK_PLL3	(0x0c0)

#घोषणा DEFAULT_TOD0_PTP_PLL		(0)
#घोषणा DEFAULT_TOD1_PTP_PLL		(1)
#घोषणा DEFAULT_TOD2_PTP_PLL		(2)
#घोषणा DEFAULT_TOD3_PTP_PLL		(3)

#घोषणा POST_SM_RESET_DELAY_MS			(3000)
#घोषणा PHASE_PULL_IN_THRESHOLD_NS_DEPRECATED	(150000)
#घोषणा PHASE_PULL_IN_THRESHOLD_NS		(15000)
#घोषणा TOD_WRITE_OVERHEAD_COUNT_MAX		(2)
#घोषणा TOD_BYTE_COUNT				(11)

#घोषणा LOCK_TIMEOUT_MS			(2000)
#घोषणा LOCK_POLL_INTERVAL_MS		(10)

#घोषणा PEROUT_ENABLE_OUTPUT_MASK	(0xdeadbeef)

#घोषणा IDTCM_MAX_WRITE_COUNT		(512)

#घोषणा FULL_FW_CFG_BYTES		(SCRATCH - GPIO_USER_CONTROL)
#घोषणा FULL_FW_CFG_SKIPPED_BYTES	(((SCRATCH >> 7) \
					  - (GPIO_USER_CONTROL >> 7)) \
					 * 4) /* 4 bytes skipped every 0x80 */

/* Values of DPLL_N.DPLL_MODE.PLL_MODE */
क्रमागत pll_mode अणु
	PLL_MODE_MIN = 0,
	PLL_MODE_NORMAL = PLL_MODE_MIN,
	PLL_MODE_WRITE_PHASE = 1,
	PLL_MODE_WRITE_FREQUENCY = 2,
	PLL_MODE_GPIO_INC_DEC = 3,
	PLL_MODE_SYNTHESIS = 4,
	PLL_MODE_PHASE_MEASUREMENT = 5,
	PLL_MODE_DISABLED = 6,
	PLL_MODE_MAX = PLL_MODE_DISABLED,
पूर्ण;

क्रमागत hw_tod_ग_लिखो_trig_sel अणु
	HW_TOD_WR_TRIG_SEL_MIN = 0,
	HW_TOD_WR_TRIG_SEL_MSB = HW_TOD_WR_TRIG_SEL_MIN,
	HW_TOD_WR_TRIG_SEL_RESERVED = 1,
	HW_TOD_WR_TRIG_SEL_TOD_PPS = 2,
	HW_TOD_WR_TRIG_SEL_IRIGB_PPS = 3,
	HW_TOD_WR_TRIG_SEL_PWM_PPS = 4,
	HW_TOD_WR_TRIG_SEL_GPIO = 5,
	HW_TOD_WR_TRIG_SEL_FOD_SYNC = 6,
	WR_TRIG_SEL_MAX = HW_TOD_WR_TRIG_SEL_FOD_SYNC,
पूर्ण;

/* 4.8.7 only */
क्रमागत scsr_tod_ग_लिखो_trig_sel अणु
	SCSR_TOD_WR_TRIG_SEL_DISABLE = 0,
	SCSR_TOD_WR_TRIG_SEL_IMMEDIATE = 1,
	SCSR_TOD_WR_TRIG_SEL_REFCLK = 2,
	SCSR_TOD_WR_TRIG_SEL_PWMPPS = 3,
	SCSR_TOD_WR_TRIG_SEL_TODPPS = 4,
	SCSR_TOD_WR_TRIG_SEL_SYNCFOD = 5,
	SCSR_TOD_WR_TRIG_SEL_GPIO = 6,
	SCSR_TOD_WR_TRIG_SEL_MAX = SCSR_TOD_WR_TRIG_SEL_GPIO,
पूर्ण;

/* 4.8.7 only */
क्रमागत scsr_tod_ग_लिखो_type_sel अणु
	SCSR_TOD_WR_TYPE_SEL_ABSOLUTE = 0,
	SCSR_TOD_WR_TYPE_SEL_DELTA_PLUS = 1,
	SCSR_TOD_WR_TYPE_SEL_DELTA_MINUS = 2,
	SCSR_TOD_WR_TYPE_SEL_MAX = SCSR_TOD_WR_TYPE_SEL_DELTA_MINUS,
पूर्ण;

/* Values STATUS.DPLL_SYS_STATUS.DPLL_SYS_STATE */
क्रमागत dpll_state अणु
	DPLL_STATE_MIN = 0,
	DPLL_STATE_FREERUN = DPLL_STATE_MIN,
	DPLL_STATE_LOCKACQ = 1,
	DPLL_STATE_LOCKREC = 2,
	DPLL_STATE_LOCKED = 3,
	DPLL_STATE_HOLDOVER = 4,
	DPLL_STATE_OPEN_LOOP = 5,
	DPLL_STATE_MAX = DPLL_STATE_OPEN_LOOP,
पूर्ण;

काष्ठा idtcm;

काष्ठा idtcm_channel अणु
	काष्ठा ptp_घड़ी_info	caps;
	काष्ठा ptp_घड़ी	*ptp_घड़ी;
	काष्ठा idtcm		*idtcm;
	u16			dpll_phase;
	u16			dpll_freq;
	u16			dpll_n;
	u16			dpll_ctrl_n;
	u16			dpll_phase_pull_in;
	u16			tod_पढ़ो_primary;
	u16			tod_ग_लिखो;
	u16			tod_n;
	u16			hw_dpll_n;
	क्रमागत pll_mode		pll_mode;
	u8			pll;
	u16			output_mask;
पूर्ण;

काष्ठा idtcm अणु
	काष्ठा idtcm_channel	channel[MAX_TOD];
	काष्ठा i2c_client	*client;
	u8			page_offset;
	u8			tod_mask;
	अक्षर			version[16];
	u8			deprecated;

	/* Overhead calculation क्रम adjसमय */
	u8			calculate_overhead_flag;
	s64			tod_ग_लिखो_overhead_ns;
	kसमय_प्रकार			start_समय;

	/* Protects I2C पढ़ो/modअगरy/ग_लिखो रेजिस्टरs from concurrent access */
	काष्ठा mutex		reg_lock;
पूर्ण;

काष्ठा idtcm_fwrc अणु
	u8 hiaddr;
	u8 loaddr;
	u8 value;
	u8 reserved;
पूर्ण __packed;

#पूर्ण_अगर /* PTP_IDTCLOCKMATRIX_H */
