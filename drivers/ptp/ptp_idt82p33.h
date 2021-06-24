<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PTP hardware घड़ी driver क्रम the IDT 82P33XXX family of घड़ीs.
 *
 * Copyright (C) 2019 Integrated Device Technology, Inc., a Renesas Company.
 */
#अगर_अघोषित PTP_IDT82P33_H
#घोषणा PTP_IDT82P33_H

#समावेश <linux/kसमय.स>
#समावेश <linux/workqueue.h>


/* Register Map - AN888_SMUक्रमIEEE_SynchEther_82P33xxx_RevH.pdf */
#घोषणा PAGE_NUM (8)
#घोषणा _ADDR(page, offset) (((page) << 0x7) | ((offset) & 0x7f))
#घोषणा _PAGE(addr) (((addr) >> 0x7) & 0x7)
#घोषणा _OFFSET(addr)  ((addr) & 0x7f)

#घोषणा DPLL1_TOD_CNFG 0x134
#घोषणा DPLL2_TOD_CNFG 0x1B4

#घोषणा DPLL1_TOD_STS 0x10B
#घोषणा DPLL2_TOD_STS 0x18B

#घोषणा DPLL1_TOD_TRIGGER 0x115
#घोषणा DPLL2_TOD_TRIGGER 0x195

#घोषणा DPLL1_OPERATING_MODE_CNFG 0x120
#घोषणा DPLL2_OPERATING_MODE_CNFG 0x1A0

#घोषणा DPLL1_HOLDOVER_FREQ_CNFG 0x12C
#घोषणा DPLL2_HOLDOVER_FREQ_CNFG 0x1AC

#घोषणा DPLL1_PHASE_OFFSET_CNFG 0x143
#घोषणा DPLL2_PHASE_OFFSET_CNFG 0x1C3

#घोषणा DPLL1_SYNC_EDGE_CNFG 0X140
#घोषणा DPLL2_SYNC_EDGE_CNFG 0X1C0

#घोषणा DPLL1_INPUT_MODE_CNFG 0X116
#घोषणा DPLL2_INPUT_MODE_CNFG 0X196

#घोषणा OUT_MUX_CNFG(outn) _ADDR(0x6, (0xC * (outn)))

#घोषणा PAGE_ADDR 0x7F
/* Register Map end */

/* Register definitions - AN888_SMUक्रमIEEE_SynchEther_82P33xxx_RevH.pdf*/
#घोषणा TOD_TRIGGER(wr_trig, rd_trig) ((wr_trig & 0xf) << 4 | (rd_trig & 0xf))
#घोषणा SYNC_TOD BIT(1)
#घोषणा PH_OFFSET_EN BIT(7)
#घोषणा SQUELCH_ENABLE BIT(5)

/* Bit definitions क्रम the DPLL_MODE रेजिस्टर */
#घोषणा PLL_MODE_SHIFT                    (0)
#घोषणा PLL_MODE_MASK                     (0x1F)

#घोषणा PEROUT_ENABLE_OUTPUT_MASK         (0xdeadbeef)

क्रमागत pll_mode अणु
	PLL_MODE_MIN = 0,
	PLL_MODE_AUTOMATIC = PLL_MODE_MIN,
	PLL_MODE_FORCE_FREERUN = 1,
	PLL_MODE_FORCE_HOLDOVER = 2,
	PLL_MODE_FORCE_LOCKED = 4,
	PLL_MODE_FORCE_PRE_LOCKED2 = 5,
	PLL_MODE_FORCE_PRE_LOCKED = 6,
	PLL_MODE_FORCE_LOST_PHASE = 7,
	PLL_MODE_DCO = 10,
	PLL_MODE_WPH = 18,
	PLL_MODE_MAX = PLL_MODE_WPH,
पूर्ण;

क्रमागत hw_tod_trig_sel अणु
	HW_TOD_TRIG_SEL_MIN = 0,
	HW_TOD_TRIG_SEL_NO_WRITE = HW_TOD_TRIG_SEL_MIN,
	HW_TOD_TRIG_SEL_SYNC_SEL = 1,
	HW_TOD_TRIG_SEL_IN12 = 2,
	HW_TOD_TRIG_SEL_IN13 = 3,
	HW_TOD_TRIG_SEL_IN14 = 4,
	HW_TOD_TRIG_SEL_TOD_PPS = 5,
	HW_TOD_TRIG_SEL_TIMER_INTERVAL = 6,
	HW_TOD_TRIG_SEL_MSB_PHASE_OFFSET_CNFG = 7,
	HW_TOD_TRIG_SEL_MSB_HOLDOVER_FREQ_CNFG = 8,
	HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG = 9,
	HW_TOD_RD_TRIG_SEL_LSB_TOD_STS = HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG,
	WR_TRIG_SEL_MAX = HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG,
पूर्ण;

/* Register bit definitions end */
#घोषणा FW_खाताNAME	"idt82p33xxx.bin"
#घोषणा MAX_PHC_PLL (2)
#घोषणा TOD_BYTE_COUNT (10)
#घोषणा MAX_MEASURMENT_COUNT (5)
#घोषणा SNAP_THRESHOLD_NS (150000)
#घोषणा SYNC_TOD_TIMEOUT_SEC (5)
#घोषणा IDT82P33_MAX_WRITE_COUNT (512)

#घोषणा PLLMASK_ADDR_HI	0xFF
#घोषणा PLLMASK_ADDR_LO	0xA5

#घोषणा PLL0_OUTMASK_ADDR_HI	0xFF
#घोषणा PLL0_OUTMASK_ADDR_LO	0xB0

#घोषणा PLL1_OUTMASK_ADDR_HI	0xFF
#घोषणा PLL1_OUTMASK_ADDR_LO	0xB2

#घोषणा PLL2_OUTMASK_ADDR_HI	0xFF
#घोषणा PLL2_OUTMASK_ADDR_LO	0xB4

#घोषणा PLL3_OUTMASK_ADDR_HI	0xFF
#घोषणा PLL3_OUTMASK_ADDR_LO	0xB6

#घोषणा DEFAULT_PLL_MASK	(0x01)
#घोषणा DEFAULT_OUTPUT_MASK_PLL0	(0xc0)
#घोषणा DEFAULT_OUTPUT_MASK_PLL1	DEFAULT_OUTPUT_MASK_PLL0

/* PTP Hardware Clock पूर्णांकerface */
काष्ठा idt82p33_channel अणु
	काष्ठा ptp_घड़ी_info	caps;
	काष्ठा ptp_घड़ी	*ptp_घड़ी;
	काष्ठा idt82p33	*idt82p33;
	क्रमागत pll_mode	pll_mode;
	/* task to turn off SYNC_TOD bit after pps sync */
	काष्ठा delayed_work	sync_tod_work;
	bool			sync_tod_on;
	s32			current_freq_ppb;
	u8			output_mask;
	u16			dpll_tod_cnfg;
	u16			dpll_tod_trigger;
	u16			dpll_tod_sts;
	u16			dpll_mode_cnfg;
	u16			dpll_freq_cnfg;
	u16			dpll_phase_cnfg;
	u16			dpll_sync_cnfg;
	u16			dpll_input_mode_cnfg;
पूर्ण;

काष्ठा idt82p33 अणु
	काष्ठा idt82p33_channel channel[MAX_PHC_PLL];
	काष्ठा i2c_client	*client;
	u8	page_offset;
	u8	pll_mask;
	kसमय_प्रकार start_समय;
	पूर्णांक calculate_overhead_flag;
	s64 tod_ग_लिखो_overhead_ns;
	/* Protects I2C पढ़ो/modअगरy/ग_लिखो रेजिस्टरs from concurrent access */
	काष्ठा mutex	reg_lock;
पूर्ण;

/* firmware पूर्णांकerface */
काष्ठा idt82p33_fwrc अणु
	u8 hiaddr;
	u8 loaddr;
	u8 value;
	u8 reserved;
पूर्ण __packed;

/**
 * @brief Maximum असलolute value क्रम ग_लिखो phase offset in femtoseconds
 */
#घोषणा WRITE_PHASE_OFFSET_LIMIT (20000052084ll)

/** @brief Phase offset resolution
 *
 *  DPLL phase offset = 10^15 fs / ( System Clock  * 2^13)
 *                    = 10^15 fs / ( 1638400000 * 2^23)
 *                    = 74.5058059692382 fs
 */
#घोषणा IDT_T0DPLL_PHASE_RESOL 74506


#पूर्ण_अगर /* PTP_IDT82P33_H */
