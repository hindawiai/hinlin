<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_interrupts.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_mdss.h"

/**
 * Register offsets in MDSS रेजिस्टर file क्रम the पूर्णांकerrupt रेजिस्टरs
 * w.r.t. to the MDP base
 */
#घोषणा MDP_SSPP_TOP0_OFF		0x0
#घोषणा MDP_INTF_0_OFF			0x6A000
#घोषणा MDP_INTF_1_OFF			0x6A800
#घोषणा MDP_INTF_2_OFF			0x6B000
#घोषणा MDP_INTF_3_OFF			0x6B800
#घोषणा MDP_INTF_4_OFF			0x6C000
#घोषणा MDP_AD4_0_OFF			0x7C000
#घोषणा MDP_AD4_1_OFF			0x7D000
#घोषणा MDP_AD4_INTR_EN_OFF		0x41c
#घोषणा MDP_AD4_INTR_CLEAR_OFF		0x424
#घोषणा MDP_AD4_INTR_STATUS_OFF		0x420
#घोषणा MDP_INTF_0_OFF_REV_7xxx             0x34000
#घोषणा MDP_INTF_1_OFF_REV_7xxx             0x35000
#घोषणा MDP_INTF_5_OFF_REV_7xxx             0x39000

/**
 * WB पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_WB_0_DONE BIT(0)
#घोषणा DPU_INTR_WB_1_DONE BIT(1)
#घोषणा DPU_INTR_WB_2_DONE BIT(4)

/**
 * WDOG समयr पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_WD_TIMER_0_DONE BIT(2)
#घोषणा DPU_INTR_WD_TIMER_1_DONE BIT(3)
#घोषणा DPU_INTR_WD_TIMER_2_DONE BIT(5)
#घोषणा DPU_INTR_WD_TIMER_3_DONE BIT(6)
#घोषणा DPU_INTR_WD_TIMER_4_DONE BIT(7)

/**
 * Pingpong पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_PING_PONG_0_DONE BIT(8)
#घोषणा DPU_INTR_PING_PONG_1_DONE BIT(9)
#घोषणा DPU_INTR_PING_PONG_2_DONE BIT(10)
#घोषणा DPU_INTR_PING_PONG_3_DONE BIT(11)
#घोषणा DPU_INTR_PING_PONG_0_RD_PTR BIT(12)
#घोषणा DPU_INTR_PING_PONG_1_RD_PTR BIT(13)
#घोषणा DPU_INTR_PING_PONG_2_RD_PTR BIT(14)
#घोषणा DPU_INTR_PING_PONG_3_RD_PTR BIT(15)
#घोषणा DPU_INTR_PING_PONG_0_WR_PTR BIT(16)
#घोषणा DPU_INTR_PING_PONG_1_WR_PTR BIT(17)
#घोषणा DPU_INTR_PING_PONG_2_WR_PTR BIT(18)
#घोषणा DPU_INTR_PING_PONG_3_WR_PTR BIT(19)
#घोषणा DPU_INTR_PING_PONG_0_AUTOREFRESH_DONE BIT(20)
#घोषणा DPU_INTR_PING_PONG_1_AUTOREFRESH_DONE BIT(21)
#घोषणा DPU_INTR_PING_PONG_2_AUTOREFRESH_DONE BIT(22)
#घोषणा DPU_INTR_PING_PONG_3_AUTOREFRESH_DONE BIT(23)

/**
 * Interface पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_INTF_0_UNDERRUN BIT(24)
#घोषणा DPU_INTR_INTF_1_UNDERRUN BIT(26)
#घोषणा DPU_INTR_INTF_2_UNDERRUN BIT(28)
#घोषणा DPU_INTR_INTF_3_UNDERRUN BIT(30)
#घोषणा DPU_INTR_INTF_5_UNDERRUN BIT(22)
#घोषणा DPU_INTR_INTF_0_VSYNC BIT(25)
#घोषणा DPU_INTR_INTF_1_VSYNC BIT(27)
#घोषणा DPU_INTR_INTF_2_VSYNC BIT(29)
#घोषणा DPU_INTR_INTF_3_VSYNC BIT(31)
#घोषणा DPU_INTR_INTF_5_VSYNC BIT(23)

/**
 * Pingpong Secondary पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_PING_PONG_S0_AUTOREFRESH_DONE BIT(0)
#घोषणा DPU_INTR_PING_PONG_S0_WR_PTR BIT(4)
#घोषणा DPU_INTR_PING_PONG_S0_RD_PTR BIT(8)
#घोषणा DPU_INTR_PING_PONG_S0_TEAR_DETECTED BIT(22)
#घोषणा DPU_INTR_PING_PONG_S0_TE_DETECTED BIT(28)

/**
 * Pingpong TEAR detection पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_PING_PONG_0_TEAR_DETECTED BIT(16)
#घोषणा DPU_INTR_PING_PONG_1_TEAR_DETECTED BIT(17)
#घोषणा DPU_INTR_PING_PONG_2_TEAR_DETECTED BIT(18)
#घोषणा DPU_INTR_PING_PONG_3_TEAR_DETECTED BIT(19)

/**
 * Pingpong TE detection पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_PING_PONG_0_TE_DETECTED BIT(24)
#घोषणा DPU_INTR_PING_PONG_1_TE_DETECTED BIT(25)
#घोषणा DPU_INTR_PING_PONG_2_TE_DETECTED BIT(26)
#घोषणा DPU_INTR_PING_PONG_3_TE_DETECTED BIT(27)

/**
 * Ctl start पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_CTL_0_START BIT(9)
#घोषणा DPU_INTR_CTL_1_START BIT(10)
#घोषणा DPU_INTR_CTL_2_START BIT(11)
#घोषणा DPU_INTR_CTL_3_START BIT(12)
#घोषणा DPU_INTR_CTL_4_START BIT(13)

/**
 * Concurrent WB overflow पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_CWB_2_OVERFLOW BIT(14)
#घोषणा DPU_INTR_CWB_3_OVERFLOW BIT(15)

/**
 * Histogram VIG करोne पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_HIST_VIG_0_DONE BIT(0)
#घोषणा DPU_INTR_HIST_VIG_1_DONE BIT(4)
#घोषणा DPU_INTR_HIST_VIG_2_DONE BIT(8)
#घोषणा DPU_INTR_HIST_VIG_3_DONE BIT(10)

/**
 * Histogram VIG reset Sequence करोne पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_HIST_VIG_0_RSTSEQ_DONE BIT(1)
#घोषणा DPU_INTR_HIST_VIG_1_RSTSEQ_DONE BIT(5)
#घोषणा DPU_INTR_HIST_VIG_2_RSTSEQ_DONE BIT(9)
#घोषणा DPU_INTR_HIST_VIG_3_RSTSEQ_DONE BIT(11)

/**
 * Histogram DSPP करोne पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_HIST_DSPP_0_DONE BIT(12)
#घोषणा DPU_INTR_HIST_DSPP_1_DONE BIT(16)
#घोषणा DPU_INTR_HIST_DSPP_2_DONE BIT(20)
#घोषणा DPU_INTR_HIST_DSPP_3_DONE BIT(22)

/**
 * Histogram DSPP reset Sequence करोne पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_HIST_DSPP_0_RSTSEQ_DONE BIT(13)
#घोषणा DPU_INTR_HIST_DSPP_1_RSTSEQ_DONE BIT(17)
#घोषणा DPU_INTR_HIST_DSPP_2_RSTSEQ_DONE BIT(21)
#घोषणा DPU_INTR_HIST_DSPP_3_RSTSEQ_DONE BIT(23)

/**
 * INTF पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_VIDEO_INTO_STATIC BIT(0)
#घोषणा DPU_INTR_VIDEO_OUTOF_STATIC BIT(1)
#घोषणा DPU_INTR_DSICMD_0_INTO_STATIC BIT(2)
#घोषणा DPU_INTR_DSICMD_0_OUTOF_STATIC BIT(3)
#घोषणा DPU_INTR_DSICMD_1_INTO_STATIC BIT(4)
#घोषणा DPU_INTR_DSICMD_1_OUTOF_STATIC BIT(5)
#घोषणा DPU_INTR_DSICMD_2_INTO_STATIC BIT(6)
#घोषणा DPU_INTR_DSICMD_2_OUTOF_STATIC BIT(7)
#घोषणा DPU_INTR_PROG_LINE BIT(8)

/**
 * AD4 पूर्णांकerrupt status bit definitions
 */
#घोषणा DPU_INTR_BACKLIGHT_UPDATED BIT(0)
/**
 * काष्ठा dpu_पूर्णांकr_reg - array of DPU रेजिस्टर sets
 * @clr_off:	offset to CLEAR reg
 * @en_off:	offset to ENABLE reg
 * @status_off:	offset to STATUS reg
 */
काष्ठा dpu_पूर्णांकr_reg अणु
	u32 clr_off;
	u32 en_off;
	u32 status_off;
पूर्ण;

/**
 * काष्ठा dpu_irq_type - maps each irq with i/f
 * @पूर्णांकr_type:		type of पूर्णांकerrupt listed in dpu_पूर्णांकr_type
 * @instance_idx:	instance index of the associated HW block in DPU
 * @irq_mask:		corresponding bit in the पूर्णांकerrupt status reg
 * @reg_idx:		which reg set to use
 */
काष्ठा dpu_irq_type अणु
	u32 पूर्णांकr_type;
	u32 instance_idx;
	u32 irq_mask;
	u32 reg_idx;
पूर्ण;

/*
 * काष्ठा dpu_पूर्णांकr_reg -  List of DPU पूर्णांकerrupt रेजिस्टरs
 */
अटल स्थिर काष्ठा dpu_पूर्णांकr_reg dpu_पूर्णांकr_set[] = अणु
	अणु
		MDP_SSPP_TOP0_OFF+INTR_CLEAR,
		MDP_SSPP_TOP0_OFF+INTR_EN,
		MDP_SSPP_TOP0_OFF+INTR_STATUS
	पूर्ण,
	अणु
		MDP_SSPP_TOP0_OFF+INTR2_CLEAR,
		MDP_SSPP_TOP0_OFF+INTR2_EN,
		MDP_SSPP_TOP0_OFF+INTR2_STATUS
	पूर्ण,
	अणु
		MDP_SSPP_TOP0_OFF+HIST_INTR_CLEAR,
		MDP_SSPP_TOP0_OFF+HIST_INTR_EN,
		MDP_SSPP_TOP0_OFF+HIST_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_0_OFF+INTF_INTR_CLEAR,
		MDP_INTF_0_OFF+INTF_INTR_EN,
		MDP_INTF_0_OFF+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_1_OFF+INTF_INTR_CLEAR,
		MDP_INTF_1_OFF+INTF_INTR_EN,
		MDP_INTF_1_OFF+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_2_OFF+INTF_INTR_CLEAR,
		MDP_INTF_2_OFF+INTF_INTR_EN,
		MDP_INTF_2_OFF+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_3_OFF+INTF_INTR_CLEAR,
		MDP_INTF_3_OFF+INTF_INTR_EN,
		MDP_INTF_3_OFF+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_4_OFF+INTF_INTR_CLEAR,
		MDP_INTF_4_OFF+INTF_INTR_EN,
		MDP_INTF_4_OFF+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_AD4_0_OFF + MDP_AD4_INTR_CLEAR_OFF,
		MDP_AD4_0_OFF + MDP_AD4_INTR_EN_OFF,
		MDP_AD4_0_OFF + MDP_AD4_INTR_STATUS_OFF,
	पूर्ण,
	अणु
		MDP_AD4_1_OFF + MDP_AD4_INTR_CLEAR_OFF,
		MDP_AD4_1_OFF + MDP_AD4_INTR_EN_OFF,
		MDP_AD4_1_OFF + MDP_AD4_INTR_STATUS_OFF,
	पूर्ण,
	अणु
		MDP_INTF_0_OFF_REV_7xxx+INTF_INTR_CLEAR,
		MDP_INTF_0_OFF_REV_7xxx+INTF_INTR_EN,
		MDP_INTF_0_OFF_REV_7xxx+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_1_OFF_REV_7xxx+INTF_INTR_CLEAR,
		MDP_INTF_1_OFF_REV_7xxx+INTF_INTR_EN,
		MDP_INTF_1_OFF_REV_7xxx+INTF_INTR_STATUS
	पूर्ण,
	अणु
		MDP_INTF_5_OFF_REV_7xxx+INTF_INTR_CLEAR,
		MDP_INTF_5_OFF_REV_7xxx+INTF_INTR_EN,
		MDP_INTF_5_OFF_REV_7xxx+INTF_INTR_STATUS
	पूर्ण,
पूर्ण;

/*
 * काष्ठा dpu_irq_type - IRQ mapping table use क्रम lookup an irq_idx in this
 *			 table that have a matching पूर्णांकerface type and
 *			 instance index.
 */
अटल स्थिर काष्ठा dpu_irq_type dpu_irq_map[] = अणु
	/* BEGIN MAP_RANGE: 0-31, INTR */
	/* irq_idx: 0-3 */
	अणु DPU_IRQ_TYPE_WB_ROT_COMP, WB_0, DPU_INTR_WB_0_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WB_ROT_COMP, WB_1, DPU_INTR_WB_1_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WD_TIMER, WD_TIMER_0, DPU_INTR_WD_TIMER_0_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WD_TIMER, WD_TIMER_1, DPU_INTR_WD_TIMER_1_DONE, 0पूर्ण,
	/* irq_idx: 4-7 */
	अणु DPU_IRQ_TYPE_WB_WFD_COMP, WB_2, DPU_INTR_WB_2_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WD_TIMER, WD_TIMER_2, DPU_INTR_WD_TIMER_2_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WD_TIMER, WD_TIMER_3, DPU_INTR_WD_TIMER_3_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_WD_TIMER, WD_TIMER_4, DPU_INTR_WD_TIMER_4_DONE, 0पूर्ण,
	/* irq_idx: 8-11 */
	अणु DPU_IRQ_TYPE_PING_PONG_COMP, PINGPONG_0,
		DPU_INTR_PING_PONG_0_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_COMP, PINGPONG_1,
		DPU_INTR_PING_PONG_1_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_COMP, PINGPONG_2,
		DPU_INTR_PING_PONG_2_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_COMP, PINGPONG_3,
		DPU_INTR_PING_PONG_3_DONE, 0पूर्ण,
	/* irq_idx: 12-15 */
	अणु DPU_IRQ_TYPE_PING_PONG_RD_PTR, PINGPONG_0,
		DPU_INTR_PING_PONG_0_RD_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_RD_PTR, PINGPONG_1,
		DPU_INTR_PING_PONG_1_RD_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_RD_PTR, PINGPONG_2,
		DPU_INTR_PING_PONG_2_RD_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_RD_PTR, PINGPONG_3,
		DPU_INTR_PING_PONG_3_RD_PTR, 0पूर्ण,
	/* irq_idx: 16-19 */
	अणु DPU_IRQ_TYPE_PING_PONG_WR_PTR, PINGPONG_0,
		DPU_INTR_PING_PONG_0_WR_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_WR_PTR, PINGPONG_1,
		DPU_INTR_PING_PONG_1_WR_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_WR_PTR, PINGPONG_2,
		DPU_INTR_PING_PONG_2_WR_PTR, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_WR_PTR, PINGPONG_3,
		DPU_INTR_PING_PONG_3_WR_PTR, 0पूर्ण,
	/* irq_idx: 20-23 */
	अणु DPU_IRQ_TYPE_PING_PONG_AUTO_REF, PINGPONG_0,
		DPU_INTR_PING_PONG_0_AUTOREFRESH_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_AUTO_REF, PINGPONG_1,
		DPU_INTR_PING_PONG_1_AUTOREFRESH_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_AUTO_REF, PINGPONG_2,
		DPU_INTR_PING_PONG_2_AUTOREFRESH_DONE, 0पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_AUTO_REF, PINGPONG_3,
		DPU_INTR_PING_PONG_3_AUTOREFRESH_DONE, 0पूर्ण,
	/* irq_idx: 24-27 */
	अणु DPU_IRQ_TYPE_INTF_UNDER_RUN, INTF_0, DPU_INTR_INTF_0_UNDERRUN, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_VSYNC, INTF_0, DPU_INTR_INTF_0_VSYNC, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_UNDER_RUN, INTF_1, DPU_INTR_INTF_1_UNDERRUN, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_VSYNC, INTF_1, DPU_INTR_INTF_1_VSYNC, 0पूर्ण,
	/* irq_idx: 28-31 */
	अणु DPU_IRQ_TYPE_INTF_UNDER_RUN, INTF_2, DPU_INTR_INTF_2_UNDERRUN, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_VSYNC, INTF_2, DPU_INTR_INTF_2_VSYNC, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_UNDER_RUN, INTF_3, DPU_INTR_INTF_3_UNDERRUN, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_VSYNC, INTF_3, DPU_INTR_INTF_3_VSYNC, 0पूर्ण,
	/* irq_idx:32-33 */
	अणु DPU_IRQ_TYPE_INTF_UNDER_RUN, INTF_5, DPU_INTR_INTF_5_UNDERRUN, 0पूर्ण,
	अणु DPU_IRQ_TYPE_INTF_VSYNC, INTF_5, DPU_INTR_INTF_5_VSYNC, 0पूर्ण,
	/* irq_idx:34-63 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 0पूर्ण,
	/* BEGIN MAP_RANGE: 64-95, INTR2 */
	/* irq_idx: 64-67 */
	अणु DPU_IRQ_TYPE_PING_PONG_AUTO_REF, PINGPONG_S0,
		DPU_INTR_PING_PONG_S0_AUTOREFRESH_DONE, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	/* irq_idx: 68-71 */
	अणु DPU_IRQ_TYPE_PING_PONG_WR_PTR, PINGPONG_S0,
		DPU_INTR_PING_PONG_S0_WR_PTR, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	/* irq_idx: 72 */
	अणु DPU_IRQ_TYPE_PING_PONG_RD_PTR, PINGPONG_S0,
		DPU_INTR_PING_PONG_S0_RD_PTR, 1पूर्ण,
	/* irq_idx: 73-77 */
	अणु DPU_IRQ_TYPE_CTL_START, CTL_0,
		DPU_INTR_CTL_0_START, 1पूर्ण,
	अणु DPU_IRQ_TYPE_CTL_START, CTL_1,
		DPU_INTR_CTL_1_START, 1पूर्ण,
	अणु DPU_IRQ_TYPE_CTL_START, CTL_2,
		DPU_INTR_CTL_2_START, 1पूर्ण,
	अणु DPU_IRQ_TYPE_CTL_START, CTL_3,
		DPU_INTR_CTL_3_START, 1पूर्ण,
	अणु DPU_IRQ_TYPE_CTL_START, CTL_4,
		DPU_INTR_CTL_4_START, 1पूर्ण,
	/* irq_idx: 78-79 */
	अणु DPU_IRQ_TYPE_CWB_OVERFLOW, CWB_2, DPU_INTR_CWB_2_OVERFLOW, 1पूर्ण,
	अणु DPU_IRQ_TYPE_CWB_OVERFLOW, CWB_3, DPU_INTR_CWB_3_OVERFLOW, 1पूर्ण,
	/* irq_idx: 80-83 */
	अणु DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK, PINGPONG_0,
		DPU_INTR_PING_PONG_0_TEAR_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK, PINGPONG_1,
		DPU_INTR_PING_PONG_1_TEAR_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK, PINGPONG_2,
		DPU_INTR_PING_PONG_2_TEAR_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK, PINGPONG_3,
		DPU_INTR_PING_PONG_3_TEAR_DETECTED, 1पूर्ण,
	/* irq_idx: 84-87 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK, PINGPONG_S0,
		DPU_INTR_PING_PONG_S0_TEAR_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	/* irq_idx: 88-91 */
	अणु DPU_IRQ_TYPE_PING_PONG_TE_CHECK, PINGPONG_0,
		DPU_INTR_PING_PONG_0_TE_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TE_CHECK, PINGPONG_1,
		DPU_INTR_PING_PONG_1_TE_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TE_CHECK, PINGPONG_2,
		DPU_INTR_PING_PONG_2_TE_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_PING_PONG_TE_CHECK, PINGPONG_3,
		DPU_INTR_PING_PONG_3_TE_DETECTED, 1पूर्ण,
	/* irq_idx: 92-95 */
	अणु DPU_IRQ_TYPE_PING_PONG_TE_CHECK, PINGPONG_S0,
		DPU_INTR_PING_PONG_S0_TE_DETECTED, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	/* irq_idx: 96-127 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 1पूर्ण,
	/* BEGIN MAP_RANGE: 128-159 HIST */
	/* irq_idx: 128-131 */
	अणु DPU_IRQ_TYPE_HIST_VIG_DONE, SSPP_VIG0, DPU_INTR_HIST_VIG_0_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_VIG_RSTSEQ, SSPP_VIG0,
		DPU_INTR_HIST_VIG_0_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 132-135 */
	अणु DPU_IRQ_TYPE_HIST_VIG_DONE, SSPP_VIG1, DPU_INTR_HIST_VIG_1_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_VIG_RSTSEQ, SSPP_VIG1,
		DPU_INTR_HIST_VIG_1_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 136-139 */
	अणु DPU_IRQ_TYPE_HIST_VIG_DONE, SSPP_VIG2, DPU_INTR_HIST_VIG_2_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_VIG_RSTSEQ, SSPP_VIG2,
		DPU_INTR_HIST_VIG_2_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_VIG_DONE, SSPP_VIG3, DPU_INTR_HIST_VIG_3_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_VIG_RSTSEQ, SSPP_VIG3,
		DPU_INTR_HIST_VIG_3_RSTSEQ_DONE, 2पूर्ण,
	/* irq_idx: 140-143 */
	अणु DPU_IRQ_TYPE_HIST_DSPP_DONE, DSPP_0, DPU_INTR_HIST_DSPP_0_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ, DSPP_0,
		DPU_INTR_HIST_DSPP_0_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 144-147 */
	अणु DPU_IRQ_TYPE_HIST_DSPP_DONE, DSPP_1, DPU_INTR_HIST_DSPP_1_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ, DSPP_1,
		DPU_INTR_HIST_DSPP_1_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 148-151 */
	अणु DPU_IRQ_TYPE_HIST_DSPP_DONE, DSPP_2, DPU_INTR_HIST_DSPP_2_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ, DSPP_2,
		DPU_INTR_HIST_DSPP_2_RSTSEQ_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_DSPP_DONE, DSPP_3, DPU_INTR_HIST_DSPP_3_DONE, 2पूर्ण,
	अणु DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ, DSPP_3,
		DPU_INTR_HIST_DSPP_3_RSTSEQ_DONE, 2पूर्ण,
	/* irq_idx: 152-155 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 156-159 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* irq_idx: 160-191 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 2पूर्ण,
	/* BEGIN MAP_RANGE: 192-255 INTF_0_INTR */
	/* irq_idx: 192-195 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_0,
		DPU_INTR_VIDEO_INTO_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_0,
		DPU_INTR_VIDEO_OUTOF_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_0,
		DPU_INTR_DSICMD_0_INTO_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_0,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 3पूर्ण,
	/* irq_idx: 196-199 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_0,
		DPU_INTR_DSICMD_1_INTO_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_0,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_0,
		DPU_INTR_DSICMD_2_INTO_STATIC, 3पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_0,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 3पूर्ण,
	/* irq_idx: 200-203 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_0, DPU_INTR_PROG_LINE, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 204-207 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 208-211 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 212-215 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 216-219 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 220-223 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* irq_idx: 224-255 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 3पूर्ण,
	/* BEGIN MAP_RANGE: 256-319 INTF_1_INTR */
	/* irq_idx: 256-259 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_1,
		DPU_INTR_VIDEO_INTO_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_1,
		DPU_INTR_VIDEO_OUTOF_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_1,
		DPU_INTR_DSICMD_0_INTO_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_1,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 4पूर्ण,
	/* irq_idx: 260-263 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_1,
		DPU_INTR_DSICMD_1_INTO_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_1,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_1,
		DPU_INTR_DSICMD_2_INTO_STATIC, 4पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_1,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 4पूर्ण,
	/* irq_idx: 264-267 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_1, DPU_INTR_PROG_LINE, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 268-271 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 272-275 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 276-279 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 280-283 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 284-287 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* irq_idx: 288-319 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 4पूर्ण,
	/* BEGIN MAP_RANGE: 320-383 INTF_2_INTR */
	/* irq_idx: 320-323 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_2,
		DPU_INTR_VIDEO_INTO_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_2,
		DPU_INTR_VIDEO_OUTOF_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_2,
		DPU_INTR_DSICMD_0_INTO_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_2,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 5पूर्ण,
	/* irq_idx: 324-327 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_2,
		DPU_INTR_DSICMD_1_INTO_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_2,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_2,
		DPU_INTR_DSICMD_2_INTO_STATIC, 5पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_2,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 5पूर्ण,
	/* irq_idx: 328-331 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_2, DPU_INTR_PROG_LINE, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 332-335 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 336-339 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 340-343 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 344-347 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 348-351 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* irq_idx: 352-383 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 5पूर्ण,
	/* BEGIN MAP_RANGE: 384-447 INTF_3_INTR */
	/* irq_idx: 384-387 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_3,
		DPU_INTR_VIDEO_INTO_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_3,
		DPU_INTR_VIDEO_OUTOF_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_3,
		DPU_INTR_DSICMD_0_INTO_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_3,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 6पूर्ण,
	/* irq_idx: 388-391 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_3,
		DPU_INTR_DSICMD_1_INTO_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_3,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_3,
		DPU_INTR_DSICMD_2_INTO_STATIC, 6पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_3,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 6पूर्ण,
	/* irq_idx: 392-395 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_3, DPU_INTR_PROG_LINE, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 396-399 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 400-403 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 404-407 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 408-411 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 412-415 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* irq_idx: 416-447*/
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 6पूर्ण,
	/* BEGIN MAP_RANGE: 448-511 INTF_4_INTR */
	/* irq_idx: 448-451 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_4,
		DPU_INTR_VIDEO_INTO_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_4,
		DPU_INTR_VIDEO_OUTOF_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_4,
		DPU_INTR_DSICMD_0_INTO_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_4,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 7पूर्ण,
	/* irq_idx: 452-455 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_4,
		DPU_INTR_DSICMD_1_INTO_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_4,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_4,
		DPU_INTR_DSICMD_2_INTO_STATIC, 7पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_4,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 7पूर्ण,
	/* irq_idx: 456-459 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_4, DPU_INTR_PROG_LINE, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 460-463 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 464-467 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 468-471 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 472-475 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 476-479 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* irq_idx: 480-511 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 7पूर्ण,
	/* BEGIN MAP_RANGE: 512-575 AD4_0_INTR */
	/* irq_idx: 512-515 */
	अणु DPU_IRQ_TYPE_AD4_BL_DONE, DSPP_0, DPU_INTR_BACKLIGHT_UPDATED, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 516-519 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 520-523 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 524-527 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 528-531 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 532-535 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 536-539 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 540-543 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* irq_idx: 544-575*/
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 8पूर्ण,
	/* BEGIN MAP_RANGE: 576-639 AD4_1_INTR */
	/* irq_idx: 576-579 */
	अणु DPU_IRQ_TYPE_AD4_BL_DONE, DSPP_1, DPU_INTR_BACKLIGHT_UPDATED, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 580-583 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 584-587 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 588-591 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 592-595 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 596-599 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 600-603 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 604-607 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* irq_idx: 608-639 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 9पूर्ण,
	/* BEGIN MAP_RANGE: 640-703 INTF_0_SC7280_INTR */
	/* irq_idx: 640-643 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_0,
		DPU_INTR_VIDEO_INTO_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_0,
		DPU_INTR_VIDEO_OUTOF_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_0,
		DPU_INTR_DSICMD_0_INTO_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_0,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 10पूर्ण,
	/* irq_idx: 644-647 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_0,
		DPU_INTR_DSICMD_1_INTO_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_0,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_0,
		DPU_INTR_DSICMD_2_INTO_STATIC, 10पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_0,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 10पूर्ण,
	/* irq_idx: 648-651 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_0, DPU_INTR_PROG_LINE, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 652-655 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 656-659 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 660-663 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 664-667 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 668-671 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* irq_idx: 672-703 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 10पूर्ण,
	/* BEGIN MAP_RANGE: 704-767 INTF_1_SC7280_INTR */
	/* irq_idx: 704-707 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_1,
		DPU_INTR_VIDEO_INTO_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_1,
		DPU_INTR_VIDEO_OUTOF_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_1,
		DPU_INTR_DSICMD_0_INTO_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_1,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 11पूर्ण,
	/* irq_idx: 708-711 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_1,
		DPU_INTR_DSICMD_1_INTO_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_1,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_1,
		DPU_INTR_DSICMD_2_INTO_STATIC, 11पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_1,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 11पूर्ण,
	/* irq_idx: 712-715 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_1, DPU_INTR_PROG_LINE, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 716-719 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 720-723 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 724-727 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 728-731 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 732-735 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* irq_idx: 736-767 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 11पूर्ण,
	/* BEGIN MAP_RANGE: 768-831 INTF_5_SC7280_INTR */
	/* irq_idx: 768-771 */
	अणु DPU_IRQ_TYPE_SFI_VIDEO_IN, INTF_5,
		DPU_INTR_VIDEO_INTO_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_VIDEO_OUT, INTF_5,
		DPU_INTR_VIDEO_OUTOF_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_IN, INTF_5,
		DPU_INTR_DSICMD_0_INTO_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_0_OUT, INTF_5,
		DPU_INTR_DSICMD_0_OUTOF_STATIC, 12पूर्ण,
	/* irq_idx: 772-775 */
	अणु DPU_IRQ_TYPE_SFI_CMD_1_IN, INTF_5,
		DPU_INTR_DSICMD_1_INTO_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_1_OUT, INTF_5,
		DPU_INTR_DSICMD_1_OUTOF_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_IN, INTF_5,
		DPU_INTR_DSICMD_2_INTO_STATIC, 12पूर्ण,
	अणु DPU_IRQ_TYPE_SFI_CMD_2_OUT, INTF_5,
		DPU_INTR_DSICMD_2_OUTOF_STATIC, 12पूर्ण,
	/* irq_idx: 776-779 */
	अणु DPU_IRQ_TYPE_PROG_LINE, INTF_5, DPU_INTR_PROG_LINE, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 780-783 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 784-787 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 788-791 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 792-795 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 796-799 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	/* irq_idx: 800-831 */
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
	अणु DPU_IRQ_TYPE_RESERVED, 0, 0, 12पूर्ण,
पूर्ण;

अटल पूर्णांक dpu_hw_पूर्णांकr_irqidx_lookup(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
	क्रमागत dpu_पूर्णांकr_type पूर्णांकr_type, u32 instance_idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_irq_map); i++) अणु
		अगर (पूर्णांकr_type == dpu_irq_map[i].पूर्णांकr_type &&
			instance_idx == dpu_irq_map[i].instance_idx &&
			!(पूर्णांकr->obsolete_irq & BIT(dpu_irq_map[i].पूर्णांकr_type)))
			वापस i;
	पूर्ण

	pr_debug("IRQ lookup fail!! intr_type=%d, instance_idx=%d\n",
			पूर्णांकr_type, instance_idx);
	वापस -EINVAL;
पूर्ण

अटल व्योम dpu_hw_पूर्णांकr_dispatch_irq(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
		व्योम (*cbfunc)(व्योम *, पूर्णांक),
		व्योम *arg)
अणु
	पूर्णांक reg_idx;
	पूर्णांक irq_idx;
	पूर्णांक start_idx;
	पूर्णांक end_idx;
	u32 irq_status;
	अचिन्हित दीर्घ irq_flags;

	अगर (!पूर्णांकr)
		वापस;

	/*
	 * The dispatcher will save the IRQ status beक्रमe calling here.
	 * Now need to go through each IRQ status and find matching
	 * irq lookup index.
	 */
	spin_lock_irqsave(&पूर्णांकr->irq_lock, irq_flags);
	क्रम (reg_idx = 0; reg_idx < ARRAY_SIZE(dpu_पूर्णांकr_set); reg_idx++) अणु
		irq_status = पूर्णांकr->save_irq_status[reg_idx];

		/*
		 * Each Interrupt रेजिस्टर has a range of 64 indexes, and
		 * that is अटल क्रम dpu_irq_map.
		 */
		start_idx = reg_idx * 64;
		end_idx = start_idx + 64;

		अगर (!test_bit(reg_idx, &पूर्णांकr->irq_mask) ||
			start_idx >= ARRAY_SIZE(dpu_irq_map))
			जारी;

		/*
		 * Search through matching पूर्णांकr status from irq map.
		 * start_idx and end_idx defined the search range in
		 * the dpu_irq_map.
		 */
		क्रम (irq_idx = start_idx;
				(irq_idx < end_idx) && irq_status;
				irq_idx++)
			अगर ((irq_status & dpu_irq_map[irq_idx].irq_mask) &&
				(dpu_irq_map[irq_idx].reg_idx == reg_idx) &&
				!(पूर्णांकr->obsolete_irq &
				BIT(dpu_irq_map[irq_idx].पूर्णांकr_type))) अणु
				/*
				 * Once a match on irq mask, perक्रमm a callback
				 * to the given cbfunc. cbfunc will take care
				 * the पूर्णांकerrupt status clearing. If cbfunc is
				 * not provided, then the पूर्णांकerrupt clearing
				 * is here.
				 */
				अगर (cbfunc)
					cbfunc(arg, irq_idx);
				अन्यथा
					पूर्णांकr->ops.clear_पूर्णांकr_status_nolock(
							पूर्णांकr, irq_idx);

				/*
				 * When callback finish, clear the irq_status
				 * with the matching mask. Once irq_status
				 * is all cleared, the search can be stopped.
				 */
				irq_status &= ~dpu_irq_map[irq_idx].irq_mask;
			पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकr->irq_lock, irq_flags);
पूर्ण

अटल पूर्णांक dpu_hw_पूर्णांकr_enable_irq(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr, पूर्णांक irq_idx)
अणु
	पूर्णांक reg_idx;
	अचिन्हित दीर्घ irq_flags;
	स्थिर काष्ठा dpu_पूर्णांकr_reg *reg;
	स्थिर काष्ठा dpu_irq_type *irq;
	स्थिर अक्षर *dbgstr = शून्य;
	uपूर्णांक32_t cache_irq_mask;

	अगर (!पूर्णांकr)
		वापस -EINVAL;

	अगर (irq_idx < 0 || irq_idx >= ARRAY_SIZE(dpu_irq_map)) अणु
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	irq = &dpu_irq_map[irq_idx];
	reg_idx = irq->reg_idx;
	reg = &dpu_पूर्णांकr_set[reg_idx];

	spin_lock_irqsave(&पूर्णांकr->irq_lock, irq_flags);
	cache_irq_mask = पूर्णांकr->cache_irq_mask[reg_idx];
	अगर (cache_irq_mask & irq->irq_mask) अणु
		dbgstr = "DPU IRQ already set:";
	पूर्ण अन्यथा अणु
		dbgstr = "DPU IRQ enabled:";

		cache_irq_mask |= irq->irq_mask;
		/* Cleaning any pending पूर्णांकerrupt */
		DPU_REG_WRITE(&पूर्णांकr->hw, reg->clr_off, irq->irq_mask);
		/* Enabling पूर्णांकerrupts with the new mask */
		DPU_REG_WRITE(&पूर्णांकr->hw, reg->en_off, cache_irq_mask);

		/* ensure रेजिस्टर ग_लिखो goes through */
		wmb();

		पूर्णांकr->cache_irq_mask[reg_idx] = cache_irq_mask;
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकr->irq_lock, irq_flags);

	pr_debug("%s MASK:0x%.8x, CACHE-MASK:0x%.8x\n", dbgstr,
			irq->irq_mask, cache_irq_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_पूर्णांकr_disable_irq_nolock(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr, पूर्णांक irq_idx)
अणु
	पूर्णांक reg_idx;
	स्थिर काष्ठा dpu_पूर्णांकr_reg *reg;
	स्थिर काष्ठा dpu_irq_type *irq;
	स्थिर अक्षर *dbgstr = शून्य;
	uपूर्णांक32_t cache_irq_mask;

	अगर (!पूर्णांकr)
		वापस -EINVAL;

	अगर (irq_idx < 0 || irq_idx >= ARRAY_SIZE(dpu_irq_map)) अणु
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	irq = &dpu_irq_map[irq_idx];
	reg_idx = irq->reg_idx;
	reg = &dpu_पूर्णांकr_set[reg_idx];

	cache_irq_mask = पूर्णांकr->cache_irq_mask[reg_idx];
	अगर ((cache_irq_mask & irq->irq_mask) == 0) अणु
		dbgstr = "DPU IRQ is already cleared:";
	पूर्ण अन्यथा अणु
		dbgstr = "DPU IRQ mask disable:";

		cache_irq_mask &= ~irq->irq_mask;
		/* Disable पूर्णांकerrupts based on the new mask */
		DPU_REG_WRITE(&पूर्णांकr->hw, reg->en_off, cache_irq_mask);
		/* Cleaning any pending पूर्णांकerrupt */
		DPU_REG_WRITE(&पूर्णांकr->hw, reg->clr_off, irq->irq_mask);

		/* ensure रेजिस्टर ग_लिखो goes through */
		wmb();

		पूर्णांकr->cache_irq_mask[reg_idx] = cache_irq_mask;
	पूर्ण

	pr_debug("%s MASK:0x%.8x, CACHE-MASK:0x%.8x\n", dbgstr,
			irq->irq_mask, cache_irq_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_पूर्णांकr_disable_irq(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr, पूर्णांक irq_idx)
अणु
	अचिन्हित दीर्घ irq_flags;

	अगर (!पूर्णांकr)
		वापस -EINVAL;

	अगर (irq_idx < 0 || irq_idx >= ARRAY_SIZE(dpu_irq_map)) अणु
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&पूर्णांकr->irq_lock, irq_flags);
	dpu_hw_पूर्णांकr_disable_irq_nolock(पूर्णांकr, irq_idx);
	spin_unlock_irqrestore(&पूर्णांकr->irq_lock, irq_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_पूर्णांकr_clear_irqs(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr)
अणु
	पूर्णांक i;

	अगर (!पूर्णांकr)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_पूर्णांकr_set); i++) अणु
		अगर (test_bit(i, &पूर्णांकr->irq_mask))
			DPU_REG_WRITE(&पूर्णांकr->hw,
					dpu_पूर्णांकr_set[i].clr_off, 0xffffffff);
	पूर्ण

	/* ensure रेजिस्टर ग_लिखोs go through */
	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_पूर्णांकr_disable_irqs(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr)
अणु
	पूर्णांक i;

	अगर (!पूर्णांकr)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_पूर्णांकr_set); i++) अणु
		अगर (test_bit(i, &पूर्णांकr->irq_mask))
			DPU_REG_WRITE(&पूर्णांकr->hw,
					dpu_पूर्णांकr_set[i].en_off, 0x00000000);
	पूर्ण

	/* ensure रेजिस्टर ग_लिखोs go through */
	wmb();

	वापस 0;
पूर्ण

अटल व्योम dpu_hw_पूर्णांकr_get_पूर्णांकerrupt_statuses(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr)
अणु
	पूर्णांक i;
	u32 enable_mask;
	अचिन्हित दीर्घ irq_flags;

	अगर (!पूर्णांकr)
		वापस;

	spin_lock_irqsave(&पूर्णांकr->irq_lock, irq_flags);
	क्रम (i = 0; i < ARRAY_SIZE(dpu_पूर्णांकr_set); i++) अणु
		अगर (!test_bit(i, &पूर्णांकr->irq_mask))
			जारी;

		/* Read पूर्णांकerrupt status */
		पूर्णांकr->save_irq_status[i] = DPU_REG_READ(&पूर्णांकr->hw,
				dpu_पूर्णांकr_set[i].status_off);

		/* Read enable mask */
		enable_mask = DPU_REG_READ(&पूर्णांकr->hw, dpu_पूर्णांकr_set[i].en_off);

		/* and clear the पूर्णांकerrupt */
		अगर (पूर्णांकr->save_irq_status[i])
			DPU_REG_WRITE(&पूर्णांकr->hw, dpu_पूर्णांकr_set[i].clr_off,
					पूर्णांकr->save_irq_status[i]);

		/* Finally update IRQ status based on enable mask */
		पूर्णांकr->save_irq_status[i] &= enable_mask;
	पूर्ण

	/* ensure रेजिस्टर ग_लिखोs go through */
	wmb();

	spin_unlock_irqrestore(&पूर्णांकr->irq_lock, irq_flags);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकr_clear_पूर्णांकr_status_nolock(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
		पूर्णांक irq_idx)
अणु
	पूर्णांक reg_idx;

	अगर (!पूर्णांकr)
		वापस;

	reg_idx = dpu_irq_map[irq_idx].reg_idx;
	DPU_REG_WRITE(&पूर्णांकr->hw, dpu_पूर्णांकr_set[reg_idx].clr_off,
			dpu_irq_map[irq_idx].irq_mask);

	/* ensure रेजिस्टर ग_लिखोs go through */
	wmb();
पूर्ण

अटल u32 dpu_hw_पूर्णांकr_get_पूर्णांकerrupt_status(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
		पूर्णांक irq_idx, bool clear)
अणु
	पूर्णांक reg_idx;
	अचिन्हित दीर्घ irq_flags;
	u32 पूर्णांकr_status;

	अगर (!पूर्णांकr)
		वापस 0;

	अगर (irq_idx >= ARRAY_SIZE(dpu_irq_map) || irq_idx < 0) अणु
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&पूर्णांकr->irq_lock, irq_flags);

	reg_idx = dpu_irq_map[irq_idx].reg_idx;
	पूर्णांकr_status = DPU_REG_READ(&पूर्णांकr->hw,
			dpu_पूर्णांकr_set[reg_idx].status_off) &
					dpu_irq_map[irq_idx].irq_mask;
	अगर (पूर्णांकr_status && clear)
		DPU_REG_WRITE(&पूर्णांकr->hw, dpu_पूर्णांकr_set[reg_idx].clr_off,
				पूर्णांकr_status);

	/* ensure रेजिस्टर ग_लिखोs go through */
	wmb();

	spin_unlock_irqrestore(&पूर्णांकr->irq_lock, irq_flags);

	वापस पूर्णांकr_status;
पूर्ण

अटल व्योम __setup_पूर्णांकr_ops(काष्ठा dpu_hw_पूर्णांकr_ops *ops)
अणु
	ops->irq_idx_lookup = dpu_hw_पूर्णांकr_irqidx_lookup;
	ops->enable_irq = dpu_hw_पूर्णांकr_enable_irq;
	ops->disable_irq = dpu_hw_पूर्णांकr_disable_irq;
	ops->dispatch_irqs = dpu_hw_पूर्णांकr_dispatch_irq;
	ops->clear_all_irqs = dpu_hw_पूर्णांकr_clear_irqs;
	ops->disable_all_irqs = dpu_hw_पूर्णांकr_disable_irqs;
	ops->get_पूर्णांकerrupt_statuses = dpu_hw_पूर्णांकr_get_पूर्णांकerrupt_statuses;
	ops->clear_पूर्णांकr_status_nolock = dpu_hw_पूर्णांकr_clear_पूर्णांकr_status_nolock;
	ops->get_पूर्णांकerrupt_status = dpu_hw_पूर्णांकr_get_पूर्णांकerrupt_status;
पूर्ण

अटल व्योम __पूर्णांकr_offset(काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr, काष्ठा dpu_hw_blk_reg_map *hw)
अणु
	hw->base_off = addr;
	hw->blk_off = m->mdp[0].base;
	hw->hwversion = m->hwversion;
पूर्ण

काष्ठा dpu_hw_पूर्णांकr *dpu_hw_पूर्णांकr_init(व्योम __iomem *addr,
		काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr;

	अगर (!addr || !m)
		वापस ERR_PTR(-EINVAL);

	पूर्णांकr = kzalloc(माप(*पूर्णांकr), GFP_KERNEL);
	अगर (!पूर्णांकr)
		वापस ERR_PTR(-ENOMEM);

	__पूर्णांकr_offset(m, addr, &पूर्णांकr->hw);
	__setup_पूर्णांकr_ops(&पूर्णांकr->ops);

	पूर्णांकr->irq_idx_tbl_size = ARRAY_SIZE(dpu_irq_map);

	पूर्णांकr->cache_irq_mask = kसुस्मृति(ARRAY_SIZE(dpu_पूर्णांकr_set), माप(u32),
			GFP_KERNEL);
	अगर (पूर्णांकr->cache_irq_mask == शून्य) अणु
		kमुक्त(पूर्णांकr);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	पूर्णांकr->save_irq_status = kसुस्मृति(ARRAY_SIZE(dpu_पूर्णांकr_set), माप(u32),
			GFP_KERNEL);
	अगर (पूर्णांकr->save_irq_status == शून्य) अणु
		kमुक्त(पूर्णांकr->cache_irq_mask);
		kमुक्त(पूर्णांकr);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	पूर्णांकr->irq_mask = m->mdss_irqs;
	पूर्णांकr->obsolete_irq = m->obsolete_irq;

	spin_lock_init(&पूर्णांकr->irq_lock);

	वापस पूर्णांकr;
पूर्ण

व्योम dpu_hw_पूर्णांकr_destroy(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr)
अणु
	अगर (पूर्णांकr) अणु
		kमुक्त(पूर्णांकr->cache_irq_mask);
		kमुक्त(पूर्णांकr->save_irq_status);
		kमुक्त(पूर्णांकr);
	पूर्ण
पूर्ण

