<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_INTERRUPTS_H
#घोषणा _DPU_HW_INTERRUPTS_H

#समावेश <linux/types.h>

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_mdss.h"

/**
 * dpu_पूर्णांकr_type - HW Interrupt Type
 * @DPU_IRQ_TYPE_WB_ROT_COMP:		WB rotator करोne
 * @DPU_IRQ_TYPE_WB_WFD_COMP:		WB WFD करोne
 * @DPU_IRQ_TYPE_PING_PONG_COMP:	PingPong करोne
 * @DPU_IRQ_TYPE_PING_PONG_RD_PTR:	PingPong पढ़ो poपूर्णांकer
 * @DPU_IRQ_TYPE_PING_PONG_WR_PTR:	PingPong ग_लिखो poपूर्णांकer
 * @DPU_IRQ_TYPE_PING_PONG_AUTO_REF:	PingPong स्वतः refresh
 * @DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK:	PingPong Tear check
 * @DPU_IRQ_TYPE_PING_PONG_TE_CHECK:	PingPong TE detection
 * @DPU_IRQ_TYPE_INTF_UNDER_RUN:	INTF underrun
 * @DPU_IRQ_TYPE_INTF_VSYNC:		INTF VSYNC
 * @DPU_IRQ_TYPE_CWB_OVERFLOW:		Concurrent WB overflow
 * @DPU_IRQ_TYPE_HIST_VIG_DONE:		VIG Histogram करोne
 * @DPU_IRQ_TYPE_HIST_VIG_RSTSEQ:	VIG Histogram reset
 * @DPU_IRQ_TYPE_HIST_DSPP_DONE:	DSPP Histogram करोne
 * @DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ:	DSPP Histogram reset
 * @DPU_IRQ_TYPE_WD_TIMER:		Watchकरोg समयr
 * @DPU_IRQ_TYPE_SFI_VIDEO_IN:		Video अटल frame INTR पूर्णांकo अटल
 * @DPU_IRQ_TYPE_SFI_VIDEO_OUT:		Video अटल frame INTR out-of अटल
 * @DPU_IRQ_TYPE_SFI_CMD_0_IN:		DSI CMD0 अटल frame INTR पूर्णांकo अटल
 * @DPU_IRQ_TYPE_SFI_CMD_0_OUT:		DSI CMD0 अटल frame INTR out-of अटल
 * @DPU_IRQ_TYPE_SFI_CMD_1_IN:		DSI CMD1 अटल frame INTR पूर्णांकo अटल
 * @DPU_IRQ_TYPE_SFI_CMD_1_OUT:		DSI CMD1 अटल frame INTR out-of अटल
 * @DPU_IRQ_TYPE_SFI_CMD_2_IN:		DSI CMD2 अटल frame INTR पूर्णांकo अटल
 * @DPU_IRQ_TYPE_SFI_CMD_2_OUT:		DSI CMD2 अटल frame INTR out-of अटल
 * @DPU_IRQ_TYPE_PROG_LINE:		Programmable Line पूर्णांकerrupt
 * @DPU_IRQ_TYPE_AD4_BL_DONE:		AD4 backlight
 * @DPU_IRQ_TYPE_CTL_START:		Control start
 * @DPU_IRQ_TYPE_RESERVED:		Reserved क्रम expansion
 */
क्रमागत dpu_पूर्णांकr_type अणु
	DPU_IRQ_TYPE_WB_ROT_COMP,
	DPU_IRQ_TYPE_WB_WFD_COMP,
	DPU_IRQ_TYPE_PING_PONG_COMP,
	DPU_IRQ_TYPE_PING_PONG_RD_PTR,
	DPU_IRQ_TYPE_PING_PONG_WR_PTR,
	DPU_IRQ_TYPE_PING_PONG_AUTO_REF,
	DPU_IRQ_TYPE_PING_PONG_TEAR_CHECK,
	DPU_IRQ_TYPE_PING_PONG_TE_CHECK,
	DPU_IRQ_TYPE_INTF_UNDER_RUN,
	DPU_IRQ_TYPE_INTF_VSYNC,
	DPU_IRQ_TYPE_CWB_OVERFLOW,
	DPU_IRQ_TYPE_HIST_VIG_DONE,
	DPU_IRQ_TYPE_HIST_VIG_RSTSEQ,
	DPU_IRQ_TYPE_HIST_DSPP_DONE,
	DPU_IRQ_TYPE_HIST_DSPP_RSTSEQ,
	DPU_IRQ_TYPE_WD_TIMER,
	DPU_IRQ_TYPE_SFI_VIDEO_IN,
	DPU_IRQ_TYPE_SFI_VIDEO_OUT,
	DPU_IRQ_TYPE_SFI_CMD_0_IN,
	DPU_IRQ_TYPE_SFI_CMD_0_OUT,
	DPU_IRQ_TYPE_SFI_CMD_1_IN,
	DPU_IRQ_TYPE_SFI_CMD_1_OUT,
	DPU_IRQ_TYPE_SFI_CMD_2_IN,
	DPU_IRQ_TYPE_SFI_CMD_2_OUT,
	DPU_IRQ_TYPE_PROG_LINE,
	DPU_IRQ_TYPE_AD4_BL_DONE,
	DPU_IRQ_TYPE_CTL_START,
	DPU_IRQ_TYPE_RESERVED,
पूर्ण;

काष्ठा dpu_hw_पूर्णांकr;

/**
 * Interrupt operations.
 */
काष्ठा dpu_hw_पूर्णांकr_ops अणु
	/**
	 * irq_idx_lookup - Lookup IRQ index on the HW पूर्णांकerrupt type
	 *                 Used क्रम all irq related ops
	 * @पूर्णांकr:		HW पूर्णांकerrupt handle
	 * @पूर्णांकr_type:		Interrupt type defined in dpu_पूर्णांकr_type
	 * @instance_idx:	HW पूर्णांकerrupt block instance
	 * @वापस:		irq_idx or -EINVAL क्रम lookup fail
	 */
	पूर्णांक (*irq_idx_lookup)(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			क्रमागत dpu_पूर्णांकr_type पूर्णांकr_type,
			u32 instance_idx);

	/**
	 * enable_irq - Enable IRQ based on lookup IRQ index
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @irq_idx:	Lookup irq index वापस from irq_idx_lookup
	 * @वापस:	0 क्रम success, otherwise failure
	 */
	पूर्णांक (*enable_irq)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			पूर्णांक irq_idx);

	/**
	 * disable_irq - Disable IRQ based on lookup IRQ index
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @irq_idx:	Lookup irq index वापस from irq_idx_lookup
	 * @वापस:	0 क्रम success, otherwise failure
	 */
	पूर्णांक (*disable_irq)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			पूर्णांक irq_idx);

	/**
	 * clear_all_irqs - Clears all the पूर्णांकerrupts (i.e. acknowledges
	 *                  any निश्चितed IRQs). Useful during reset.
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @वापस:	0 क्रम success, otherwise failure
	 */
	पूर्णांक (*clear_all_irqs)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr);

	/**
	 * disable_all_irqs - Disables all the पूर्णांकerrupts. Useful during reset.
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @वापस:	0 क्रम success, otherwise failure
	 */
	पूर्णांक (*disable_all_irqs)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr);

	/**
	 * dispatch_irqs - IRQ dispatcher will call the given callback
	 *                 function when a matching पूर्णांकerrupt status bit is
	 *                 found in the irq mapping table.
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @cbfunc:	Callback function poपूर्णांकer
	 * @arg:	Argument to pass back during callback
	 */
	व्योम (*dispatch_irqs)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			व्योम (*cbfunc)(व्योम *arg, पूर्णांक irq_idx),
			व्योम *arg);

	/**
	 * get_पूर्णांकerrupt_statuses - Gets and store value from all पूर्णांकerrupt
	 *                          status रेजिस्टरs that are currently fired.
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 */
	व्योम (*get_पूर्णांकerrupt_statuses)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr);

	/**
	 * clear_पूर्णांकr_status_nolock() - clears the HW पूर्णांकerrupts without lock
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @irq_idx:	Lookup irq index वापस from irq_idx_lookup
	 */
	व्योम (*clear_पूर्णांकr_status_nolock)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			पूर्णांक irq_idx);

	/**
	 * get_पूर्णांकerrupt_status - Gets HW पूर्णांकerrupt status, and clear अगर set,
	 *                        based on given lookup IRQ index.
	 * @पूर्णांकr:	HW पूर्णांकerrupt handle
	 * @irq_idx:	Lookup irq index वापस from irq_idx_lookup
	 * @clear:	True to clear irq after पढ़ो
	 */
	u32 (*get_पूर्णांकerrupt_status)(
			काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr,
			पूर्णांक irq_idx,
			bool clear);
पूर्ण;

/**
 * काष्ठा dpu_hw_पूर्णांकr: hw पूर्णांकerrupts handling data काष्ठाure
 * @hw:               भव address mapping
 * @ops:              function poपूर्णांकer mapping क्रम IRQ handling
 * @cache_irq_mask:   array of IRQ enable masks reg storage created during init
 * @save_irq_status:  array of IRQ status reg storage created during init
 * @irq_idx_tbl_size: total number of irq_idx mapped in the hw_पूर्णांकerrupts
 * @irq_lock:         spinlock क्रम accessing IRQ resources
 * @obsolete_irq:      irq types that are obsolete क्रम a particular target
 */
काष्ठा dpu_hw_पूर्णांकr अणु
	काष्ठा dpu_hw_blk_reg_map hw;
	काष्ठा dpu_hw_पूर्णांकr_ops ops;
	u32 *cache_irq_mask;
	u32 *save_irq_status;
	u32 irq_idx_tbl_size;
	spinlock_t irq_lock;
	अचिन्हित दीर्घ irq_mask;
	अचिन्हित दीर्घ obsolete_irq;
पूर्ण;

/**
 * dpu_hw_पूर्णांकr_init(): Initializes the पूर्णांकerrupts hw object
 * @addr: mapped रेजिस्टर io address of MDP
 * @m :   poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_पूर्णांकr *dpu_hw_पूर्णांकr_init(व्योम __iomem *addr,
		काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_पूर्णांकr_destroy(): Cleanup पूर्णांकerrutps hw object
 * @पूर्णांकr: poपूर्णांकer to पूर्णांकerrupts hw object
 */
व्योम dpu_hw_पूर्णांकr_destroy(काष्ठा dpu_hw_पूर्णांकr *पूर्णांकr);
#पूर्ण_अगर
