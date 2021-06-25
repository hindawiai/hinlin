<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 PRM module functions
 *
 * Copyright (C) 2011-2012 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 * Benoथऍt Cousson
 * Paul Walmsley
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of.h>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "vp.h"
#समावेश "prm44xx.h"
#समावेश "prcm43xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prminst44xx.h"
#समावेश "powerdomain.h"
#समावेश "pm.h"

/* Static data */

अटल व्योम omap44xx_prm_पढ़ो_pending_irqs(अचिन्हित दीर्घ *events);
अटल व्योम omap44xx_prm_ocp_barrier(व्योम);
अटल व्योम omap44xx_prm_save_and_clear_irqen(u32 *saved_mask);
अटल व्योम omap44xx_prm_restore_irqen(u32 *saved_mask);
अटल व्योम omap44xx_prm_reconfigure_io_chain(व्योम);

अटल स्थिर काष्ठा omap_prcm_irq omap4_prcm_irqs[] = अणु
	OMAP_PRCM_IRQ("io",     9,      1),
पूर्ण;

अटल काष्ठा omap_prcm_irq_setup omap4_prcm_irq_setup = अणु
	.ack			= OMAP4_PRM_IRQSTATUS_MPU_OFFSET,
	.mask			= OMAP4_PRM_IRQENABLE_MPU_OFFSET,
	.pm_ctrl		= OMAP4_PRM_IO_PMCTRL_OFFSET,
	.nr_regs		= 2,
	.irqs			= omap4_prcm_irqs,
	.nr_irqs		= ARRAY_SIZE(omap4_prcm_irqs),
	.पढ़ो_pending_irqs	= &omap44xx_prm_पढ़ो_pending_irqs,
	.ocp_barrier		= &omap44xx_prm_ocp_barrier,
	.save_and_clear_irqen	= &omap44xx_prm_save_and_clear_irqen,
	.restore_irqen		= &omap44xx_prm_restore_irqen,
	.reconfigure_io_chain	= &omap44xx_prm_reconfigure_io_chain,
पूर्ण;

काष्ठा omap_prm_irq_context अणु
	अचिन्हित दीर्घ irq_enable;
	अचिन्हित दीर्घ pm_ctrl;
पूर्ण;

अटल काष्ठा omap_prm_irq_context omap_prm_context;

/*
 * omap44xx_prm_reset_src_map - map from bits in the PRM_RSTST
 *   hardware रेजिस्टर (which are specअगरic to OMAP44xx SoCs) to reset
 *   source ID bit shअगरts (which is an OMAP SoC-independent
 *   क्रमागतeration)
 */
अटल काष्ठा prm_reset_src_map omap44xx_prm_reset_src_map[] = अणु
	अणु OMAP4430_GLOBAL_WARM_SW_RST_SHIFT,
	  OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_GLOBAL_COLD_RST_SHIFT,
	  OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_MPU_SECURITY_VIOL_RST_SHIFT,
	  OMAP_SECU_VIOL_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_MPU_WDT_RST_SHIFT, OMAP_MPU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_SECURE_WDT_RST_SHIFT, OMAP_SECU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_EXTERNAL_WARM_RST_SHIFT, OMAP_EXTWARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_VDD_MPU_VOLT_MGR_RST_SHIFT,
	  OMAP_VDD_MPU_VM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_VDD_IVA_VOLT_MGR_RST_SHIFT,
	  OMAP_VDD_IVA_VM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_VDD_CORE_VOLT_MGR_RST_SHIFT,
	  OMAP_VDD_CORE_VM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_ICEPICK_RST_SHIFT, OMAP_ICEPICK_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP4430_C2C_RST_SHIFT, OMAP_C2C_RST_SRC_ID_SHIFT पूर्ण,
	अणु -1, -1 पूर्ण,
पूर्ण;

/* PRM low-level functions */

/* Read a रेजिस्टर in a CM/PRM instance in the PRM module */
अटल u32 omap4_prm_पढ़ो_inst_reg(s16 inst, u16 reg)
अणु
	वापस पढ़ोl_relaxed(prm_base.va + inst + reg);
पूर्ण

/* Write पूर्णांकo a रेजिस्टर in a CM/PRM instance in the PRM module */
अटल व्योम omap4_prm_ग_लिखो_inst_reg(u32 val, s16 inst, u16 reg)
अणु
	ग_लिखोl_relaxed(val, prm_base.va + inst + reg);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in a PRM module. Caller must lock */
अटल u32 omap4_prm_rmw_inst_reg_bits(u32 mask, u32 bits, s16 inst, s16 reg)
अणु
	u32 v;

	v = omap4_prm_पढ़ो_inst_reg(inst, reg);
	v &= ~mask;
	v |= bits;
	omap4_prm_ग_लिखो_inst_reg(v, inst, reg);

	वापस v;
पूर्ण

/* PRM VP */

/*
 * काष्ठा omap4_vp - OMAP4 VP रेजिस्टर access description.
 * @irqstatus_mpu: offset to IRQSTATUS_MPU रेजिस्टर क्रम VP
 * @tranxकरोne_status: VP_TRANXDONE_ST biपंचांगask in PRM_IRQSTATUS_MPU reg
 */
काष्ठा omap4_vp अणु
	u32 irqstatus_mpu;
	u32 tranxकरोne_status;
पूर्ण;

अटल काष्ठा omap4_vp omap4_vp[] = अणु
	[OMAP4_VP_VDD_MPU_ID] = अणु
		.irqstatus_mpu = OMAP4_PRM_IRQSTATUS_MPU_2_OFFSET,
		.tranxकरोne_status = OMAP4430_VP_MPU_TRANXDONE_ST_MASK,
	पूर्ण,
	[OMAP4_VP_VDD_IVA_ID] = अणु
		.irqstatus_mpu = OMAP4_PRM_IRQSTATUS_MPU_OFFSET,
		.tranxकरोne_status = OMAP4430_VP_IVA_TRANXDONE_ST_MASK,
	पूर्ण,
	[OMAP4_VP_VDD_CORE_ID] = अणु
		.irqstatus_mpu = OMAP4_PRM_IRQSTATUS_MPU_OFFSET,
		.tranxकरोne_status = OMAP4430_VP_CORE_TRANXDONE_ST_MASK,
	पूर्ण,
पूर्ण;

अटल u32 omap4_prm_vp_check_txकरोne(u8 vp_id)
अणु
	काष्ठा omap4_vp *vp = &omap4_vp[vp_id];
	u32 irqstatus;

	irqstatus = omap4_prminst_पढ़ो_inst_reg(OMAP4430_PRM_PARTITION,
						OMAP4430_PRM_OCP_SOCKET_INST,
						vp->irqstatus_mpu);
	वापस irqstatus & vp->tranxकरोne_status;
पूर्ण

अटल व्योम omap4_prm_vp_clear_txकरोne(u8 vp_id)
अणु
	काष्ठा omap4_vp *vp = &omap4_vp[vp_id];

	omap4_prminst_ग_लिखो_inst_reg(vp->tranxकरोne_status,
				     OMAP4430_PRM_PARTITION,
				     OMAP4430_PRM_OCP_SOCKET_INST,
				     vp->irqstatus_mpu);
पूर्ण;

u32 omap4_prm_vcvp_पढ़ो(u8 offset)
अणु
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस 0;

	वापस omap4_prminst_पढ़ो_inst_reg(OMAP4430_PRM_PARTITION,
					   inst, offset);
पूर्ण

व्योम omap4_prm_vcvp_ग_लिखो(u32 val, u8 offset)
अणु
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस;

	omap4_prminst_ग_लिखो_inst_reg(val, OMAP4430_PRM_PARTITION,
				     inst, offset);
पूर्ण

u32 omap4_prm_vcvp_rmw(u32 mask, u32 bits, u8 offset)
अणु
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस 0;

	वापस omap4_prminst_rmw_inst_reg_bits(mask, bits,
					       OMAP4430_PRM_PARTITION,
					       inst,
					       offset);
पूर्ण

अटल अंतरभूत u32 _पढ़ो_pending_irq_reg(u16 irqen_offs, u16 irqst_offs)
अणु
	u32 mask, st;

	/* XXX पढ़ो mask from RAM? */
	mask = omap4_prm_पढ़ो_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
				       irqen_offs);
	st = omap4_prm_पढ़ो_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST, irqst_offs);

	वापस mask & st;
पूर्ण

/**
 * omap44xx_prm_पढ़ो_pending_irqs - पढ़ो pending PRM MPU IRQs पूर्णांकo @events
 * @events: ptr to two consecutive u32s, pपुनः_स्मृतिated by caller
 *
 * Read PRM_IRQSTATUS_MPU* bits, AND'ed with the currently-enabled PRM
 * MPU IRQs, and store the result पूर्णांकo the two u32s poपूर्णांकed to by @events.
 * No वापस value.
 */
अटल व्योम omap44xx_prm_पढ़ो_pending_irqs(अचिन्हित दीर्घ *events)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < omap4_prcm_irq_setup.nr_regs; i++)
		events[i] = _पढ़ो_pending_irq_reg(omap4_prcm_irq_setup.mask +
				i * 4, omap4_prcm_irq_setup.ack + i * 4);
पूर्ण

/**
 * omap44xx_prm_ocp_barrier - क्रमce buffered MPU ग_लिखोs to the PRM to complete
 *
 * Force any buffered ग_लिखोs to the PRM IP block to complete.  Needed
 * by the PRM IRQ handler, which पढ़ोs and ग_लिखोs directly to the IP
 * block, to aव्योम race conditions after acknowledging or clearing IRQ
 * bits.  No वापस value.
 */
अटल व्योम omap44xx_prm_ocp_barrier(व्योम)
अणु
	omap4_prm_पढ़ो_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
				OMAP4_REVISION_PRM_OFFSET);
पूर्ण

/**
 * omap44xx_prm_save_and_clear_irqen - save/clear PRM_IRQENABLE_MPU* regs
 * @saved_mask: ptr to a u32 array to save IRQENABLE bits
 *
 * Save the PRM_IRQENABLE_MPU and PRM_IRQENABLE_MPU_2 रेजिस्टरs to
 * @saved_mask.  @saved_mask must be allocated by the caller.
 * Intended to be used in the PRM पूर्णांकerrupt handler suspend callback.
 * The OCP barrier is needed to ensure the ग_लिखो to disable PRM
 * पूर्णांकerrupts reaches the PRM beक्रमe वापसing; otherwise, spurious
 * पूर्णांकerrupts might occur.  No वापस value.
 */
अटल व्योम omap44xx_prm_save_and_clear_irqen(u32 *saved_mask)
अणु
	पूर्णांक i;
	u16 reg;

	क्रम (i = 0; i < omap4_prcm_irq_setup.nr_regs; i++) अणु
		reg = omap4_prcm_irq_setup.mask + i * 4;

		saved_mask[i] =
			omap4_prm_पढ़ो_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
						reg);
		omap4_prm_ग_लिखो_inst_reg(0, OMAP4430_PRM_OCP_SOCKET_INST, reg);
	पूर्ण

	/* OCP barrier */
	omap4_prm_पढ़ो_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
				OMAP4_REVISION_PRM_OFFSET);
पूर्ण

/**
 * omap44xx_prm_restore_irqen - set PRM_IRQENABLE_MPU* रेजिस्टरs from args
 * @saved_mask: ptr to a u32 array of IRQENABLE bits saved previously
 *
 * Restore the PRM_IRQENABLE_MPU and PRM_IRQENABLE_MPU_2 रेजिस्टरs from
 * @saved_mask.  Intended to be used in the PRM पूर्णांकerrupt handler resume
 * callback to restore values saved by omap44xx_prm_save_and_clear_irqen().
 * No OCP barrier should be needed here; any pending PRM पूर्णांकerrupts will fire
 * once the ग_लिखोs reach the PRM.  No वापस value.
 */
अटल व्योम omap44xx_prm_restore_irqen(u32 *saved_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < omap4_prcm_irq_setup.nr_regs; i++)
		omap4_prm_ग_लिखो_inst_reg(saved_mask[i],
					 OMAP4430_PRM_OCP_SOCKET_INST,
					 omap4_prcm_irq_setup.mask + i * 4);
पूर्ण

/**
 * omap44xx_prm_reconfigure_io_chain - clear latches and reconfigure I/O chain
 *
 * Clear any previously-latched I/O wakeup events and ensure that the
 * I/O wakeup gates are aligned with the current mux settings.  Works
 * by निश्चितing WUCLKIN, रुकोing क्रम WUCLKOUT to be निश्चितed, and then
 * deनिश्चितing WUCLKIN and रुकोing क्रम WUCLKOUT to be deनिश्चितed.
 * No वापस value. XXX Are the final two steps necessary?
 */
अटल व्योम omap44xx_prm_reconfigure_io_chain(व्योम)
अणु
	पूर्णांक i = 0;
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस;

	/* Trigger WUCLKIN enable */
	omap4_prm_rmw_inst_reg_bits(OMAP4430_WUCLK_CTRL_MASK,
				    OMAP4430_WUCLK_CTRL_MASK,
				    inst,
				    omap4_prcm_irq_setup.pm_ctrl);
	omap_test_समयout(
		(((omap4_prm_पढ़ो_inst_reg(inst,
					   omap4_prcm_irq_setup.pm_ctrl) &
		   OMAP4430_WUCLK_STATUS_MASK) >>
		  OMAP4430_WUCLK_STATUS_SHIFT) == 1),
		MAX_IOPAD_LATCH_TIME, i);
	अगर (i == MAX_IOPAD_LATCH_TIME)
		pr_warn("PRM: I/O chain clock line assertion timed out\n");

	/* Trigger WUCLKIN disable */
	omap4_prm_rmw_inst_reg_bits(OMAP4430_WUCLK_CTRL_MASK, 0x0,
				    inst,
				    omap4_prcm_irq_setup.pm_ctrl);
	omap_test_समयout(
		(((omap4_prm_पढ़ो_inst_reg(inst,
					   omap4_prcm_irq_setup.pm_ctrl) &
		   OMAP4430_WUCLK_STATUS_MASK) >>
		  OMAP4430_WUCLK_STATUS_SHIFT) == 0),
		MAX_IOPAD_LATCH_TIME, i);
	अगर (i == MAX_IOPAD_LATCH_TIME)
		pr_warn("PRM: I/O chain clock line deassertion timed out\n");

	वापस;
पूर्ण

/**
 * omap44xx_prm_enable_io_wakeup - enable wakeup events from I/O wakeup latches
 *
 * Activates the I/O wakeup event latches and allows events logged by
 * those latches to संकेत a wakeup event to the PRCM.  For I/O wakeups
 * to occur, WAKEUPENABLE bits must be set in the pad mux रेजिस्टरs, and
 * omap44xx_prm_reconfigure_io_chain() must be called.  No वापस value.
 */
अटल व्योम omap44xx_prm_enable_io_wakeup(व्योम)
अणु
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस;

	omap4_prm_rmw_inst_reg_bits(OMAP4430_GLOBAL_WUEN_MASK,
				    OMAP4430_GLOBAL_WUEN_MASK,
				    inst,
				    omap4_prcm_irq_setup.pm_ctrl);
पूर्ण

/**
 * omap44xx_prm_पढ़ो_reset_sources - वापस the last SoC reset source
 *
 * Return a u32 representing the last reset sources of the SoC.  The
 * वापसed reset source bits are standardized across OMAP SoCs.
 */
अटल u32 omap44xx_prm_पढ़ो_reset_sources(व्योम)
अणु
	काष्ठा prm_reset_src_map *p;
	u32 r = 0;
	u32 v;
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस 0;


	v = omap4_prm_पढ़ो_inst_reg(inst,
				    OMAP4_RM_RSTST);

	p = omap44xx_prm_reset_src_map;
	जबतक (p->reg_shअगरt >= 0 && p->std_shअगरt >= 0) अणु
		अगर (v & (1 << p->reg_shअगरt))
			r |= 1 << p->std_shअगरt;
		p++;
	पूर्ण

	वापस r;
पूर्ण

/**
 * omap44xx_prm_was_any_context_lost_old - was module hardware context lost?
 * @part: PRM partition ID (e.g., OMAP4430_PRM_PARTITION)
 * @inst: PRM instance offset (e.g., OMAP4430_PRM_MPU_INST)
 * @idx: CONTEXT रेजिस्टर offset
 *
 * Return 1 अगर any bits were set in the *_CONTEXT_* रेजिस्टर
 * identअगरied by (@part, @inst, @idx), which means that some context
 * was lost क्रम that module; otherwise, वापस 0.
 */
अटल bool omap44xx_prm_was_any_context_lost_old(u8 part, s16 inst, u16 idx)
अणु
	वापस (omap4_prminst_पढ़ो_inst_reg(part, inst, idx)) ? 1 : 0;
पूर्ण

/**
 * omap44xx_prm_clear_context_lost_flags_old - clear context loss flags
 * @part: PRM partition ID (e.g., OMAP4430_PRM_PARTITION)
 * @inst: PRM instance offset (e.g., OMAP4430_PRM_MPU_INST)
 * @idx: CONTEXT रेजिस्टर offset
 *
 * Clear hardware context loss bits क्रम the module identअगरied by
 * (@part, @inst, @idx).  No वापस value.  XXX Writes to reserved bits;
 * is there a way to aव्योम this?
 */
अटल व्योम omap44xx_prm_clear_context_loss_flags_old(u8 part, s16 inst,
						      u16 idx)
अणु
	omap4_prminst_ग_लिखो_inst_reg(0xffffffff, part, inst, idx);
पूर्ण

/* Powerकरोमुख्य low-level functions */

अटल पूर्णांक omap4_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	omap4_prminst_rmw_inst_reg_bits(OMAP_POWERSTATE_MASK,
					(pwrst << OMAP_POWERSTATE_SHIFT),
					pwrdm->prcm_partition,
					pwrdm->prcm_offs, OMAP4_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);
	v &= OMAP_POWERSTATE_MASK;
	v >>= OMAP_POWERSTATE_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP_POWERSTATEST_MASK;
	v >>= OMAP_POWERSTATEST_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP4430_LASTPOWERSTATEENTERED_MASK;
	v >>= OMAP4430_LASTPOWERSTATEENTERED_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक omap4_pwrdm_set_lowpwrstchange(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	omap4_prminst_rmw_inst_reg_bits(OMAP4430_LOWPOWERSTATECHANGE_MASK,
					(1 << OMAP4430_LOWPOWERSTATECHANGE_SHIFT),
					pwrdm->prcm_partition,
					pwrdm->prcm_offs, OMAP4_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_clear_all_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	omap4_prminst_rmw_inst_reg_bits(OMAP4430_LASTPOWERSTATEENTERED_MASK,
					OMAP4430_LASTPOWERSTATEENTERED_MASK,
					pwrdm->prcm_partition,
					pwrdm->prcm_offs, OMAP4_PM_PWSTST);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	u32 v;

	v = pwrst << __ffs(OMAP4430_LOGICRETSTATE_MASK);
	omap4_prminst_rmw_inst_reg_bits(OMAP4430_LOGICRETSTATE_MASK, v,
					pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
				    u8 pwrst)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_onstate_mask(bank);

	omap4_prminst_rmw_inst_reg_bits(m, (pwrst << __ffs(m)),
					pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
				     u8 pwrst)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	omap4_prminst_rmw_inst_reg_bits(m, (pwrst << __ffs(m)),
					pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP4430_LOGICSTATEST_MASK;
	v >>= OMAP4430_LOGICSTATEST_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);
	v &= OMAP4430_LOGICRETSTATE_MASK;
	v >>= OMAP4430_LOGICRETSTATE_SHIFT;

	वापस v;
पूर्ण

/**
 * omap4_pwrdm_पढ़ो_prev_logic_pwrst - पढ़ो the previous logic घातerstate
 * @pwrdm: काष्ठा घातerकरोमुख्य * to पढ़ो the state क्रम
 *
 * Reads the previous logic घातerstate क्रम a घातerकरोमुख्य. This
 * function must determine the previous logic घातerstate by first
 * checking the previous घातerstate क्रम the करोमुख्य. If that was OFF,
 * then logic has been lost. If previous state was RETENTION, the
 * function पढ़ोs the setting क्रम the next retention logic state to
 * see the actual value.  In every other हाल, the logic is
 * retained. Returns either PWRDM_POWER_OFF or PWRDM_POWER_RET
 * depending whether the logic was retained or not.
 */
अटल पूर्णांक omap4_pwrdm_पढ़ो_prev_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक state;

	state = omap4_pwrdm_पढ़ो_prev_pwrst(pwrdm);

	अगर (state == PWRDM_POWER_OFF)
		वापस PWRDM_POWER_OFF;

	अगर (state != PWRDM_POWER_RET)
		वापस PWRDM_POWER_RET;

	वापस omap4_pwrdm_पढ़ो_logic_retst(pwrdm);
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m, v;

	m = omap2_pwrdm_get_mem_bank_stst_mask(bank);

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTST);
	v &= m;
	v >>= __ffs(m);

	वापस v;
पूर्ण

अटल पूर्णांक omap4_pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m, v;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	v = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);
	v &= m;
	v >>= __ffs(m);

	वापस v;
पूर्ण

/**
 * omap4_pwrdm_पढ़ो_prev_mem_pwrst - पढ़ोs the previous memory घातerstate
 * @pwrdm: काष्ठा घातerकरोमुख्य * to पढ़ो mem घातerstate क्रम
 * @bank: memory bank index
 *
 * Reads the previous memory घातerstate क्रम a घातerकरोमुख्य. This
 * function must determine the previous memory घातerstate by first
 * checking the previous घातerstate क्रम the करोमुख्य. If that was OFF,
 * then logic has been lost. If previous state was RETENTION, the
 * function पढ़ोs the setting क्रम the next memory retention state to
 * see the actual value.  In every other हाल, the logic is
 * retained. Returns either PWRDM_POWER_OFF or PWRDM_POWER_RET
 * depending whether logic was retained or not.
 */
अटल पूर्णांक omap4_pwrdm_पढ़ो_prev_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	पूर्णांक state;

	state = omap4_pwrdm_पढ़ो_prev_pwrst(pwrdm);

	अगर (state == PWRDM_POWER_OFF)
		वापस PWRDM_POWER_OFF;

	अगर (state != PWRDM_POWER_RET)
		वापस PWRDM_POWER_RET;

	वापस omap4_pwrdm_पढ़ो_mem_retst(pwrdm, bank);
पूर्ण

अटल पूर्णांक omap4_pwrdm_रुको_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 c = 0;

	/*
	 * REVISIT: pwrdm_रुको_transition() may be better implemented
	 * via a callback and a periodic समयr check -- how दीर्घ करो we expect
	 * घातerकरोमुख्य transitions to take?
	 */

	/* XXX Is this udelay() value meaningful? */
	जबतक ((omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition,
					    pwrdm->prcm_offs,
					    OMAP4_PM_PWSTST) &
		OMAP_INTRANSITION_MASK) &&
	       (c++ < PWRDM_TRANSITION_BAILOUT))
		udelay(1);

	अगर (c > PWRDM_TRANSITION_BAILOUT) अणु
		pr_err("powerdomain: %s: waited too long to complete transition\n",
		       pwrdm->name);
		वापस -EAGAIN;
	पूर्ण

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_check_vcvp(व्योम)
अणु
	अगर (prm_features & PRM_HAS_VOLTAGE)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * omap4_pwrdm_save_context - Saves the घातerकरोमुख्य state
 * @pwrdm: poपूर्णांकer to inभागidual घातerकरोमुख्य
 *
 * The function saves the घातerकरोमुख्य state control inक्रमmation.
 * This is needed in rtc+ddr modes where we lose घातerकरोमुख्य context.
 */
अटल व्योम omap4_pwrdm_save_context(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	pwrdm->context = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition,
						     pwrdm->prcm_offs,
						     pwrdm->pwrstctrl_offs);

	/*
	 * Do not save LOWPOWERSTATECHANGE, writing a 1 indicates a request,
	 * पढ़ोing back a 1 indicates a request in progress.
	 */
	pwrdm->context &= ~OMAP4430_LOWPOWERSTATECHANGE_MASK;
पूर्ण

/**
 * omap4_pwrdm_restore_context - Restores the घातerकरोमुख्य state
 * @pwrdm: poपूर्णांकer to inभागidual घातerकरोमुख्य
 *
 * The function restores the घातerकरोमुख्य state control inक्रमmation.
 * This is needed in rtc+ddr modes where we lose घातerकरोमुख्य context.
 */
अटल व्योम omap4_pwrdm_restore_context(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक st, ctrl;

	st = omap4_prminst_पढ़ो_inst_reg(pwrdm->prcm_partition,
					 pwrdm->prcm_offs,
					 pwrdm->pwrstctrl_offs);

	omap4_prminst_ग_लिखो_inst_reg(pwrdm->context,
				     pwrdm->prcm_partition,
				     pwrdm->prcm_offs,
				     pwrdm->pwrstctrl_offs);

	/* Make sure we only रुको क्रम a transition अगर there is one */
	st &= OMAP_POWERSTATEST_MASK;
	ctrl = OMAP_POWERSTATEST_MASK & pwrdm->context;

	अगर (st != ctrl)
		omap4_pwrdm_रुको_transition(pwrdm);
पूर्ण

काष्ठा pwrdm_ops omap4_pwrdm_operations = अणु
	.pwrdm_set_next_pwrst	= omap4_pwrdm_set_next_pwrst,
	.pwrdm_पढ़ो_next_pwrst	= omap4_pwrdm_पढ़ो_next_pwrst,
	.pwrdm_पढ़ो_pwrst	= omap4_pwrdm_पढ़ो_pwrst,
	.pwrdm_पढ़ो_prev_pwrst	= omap4_pwrdm_पढ़ो_prev_pwrst,
	.pwrdm_set_lowpwrstchange	= omap4_pwrdm_set_lowpwrstchange,
	.pwrdm_clear_all_prev_pwrst	= omap4_pwrdm_clear_all_prev_pwrst,
	.pwrdm_set_logic_retst	= omap4_pwrdm_set_logic_retst,
	.pwrdm_पढ़ो_logic_pwrst	= omap4_pwrdm_पढ़ो_logic_pwrst,
	.pwrdm_पढ़ो_prev_logic_pwrst	= omap4_pwrdm_पढ़ो_prev_logic_pwrst,
	.pwrdm_पढ़ो_logic_retst	= omap4_pwrdm_पढ़ो_logic_retst,
	.pwrdm_पढ़ो_mem_pwrst	= omap4_pwrdm_पढ़ो_mem_pwrst,
	.pwrdm_पढ़ो_mem_retst	= omap4_pwrdm_पढ़ो_mem_retst,
	.pwrdm_पढ़ो_prev_mem_pwrst	= omap4_pwrdm_पढ़ो_prev_mem_pwrst,
	.pwrdm_set_mem_onst	= omap4_pwrdm_set_mem_onst,
	.pwrdm_set_mem_retst	= omap4_pwrdm_set_mem_retst,
	.pwrdm_रुको_transition	= omap4_pwrdm_रुको_transition,
	.pwrdm_has_voltdm	= omap4_check_vcvp,
	.pwrdm_save_context	= omap4_pwrdm_save_context,
	.pwrdm_restore_context	= omap4_pwrdm_restore_context,
पूर्ण;

अटल पूर्णांक omap44xx_prm_late_init(व्योम);

अटल व्योम prm_save_context(व्योम)
अणु
	omap_prm_context.irq_enable =
			omap4_prm_पढ़ो_inst_reg(AM43XX_PRM_OCP_SOCKET_INST,
						omap4_prcm_irq_setup.mask);

	omap_prm_context.pm_ctrl =
			omap4_prm_पढ़ो_inst_reg(AM43XX_PRM_DEVICE_INST,
						omap4_prcm_irq_setup.pm_ctrl);
पूर्ण

अटल व्योम prm_restore_context(व्योम)
अणु
	omap4_prm_ग_लिखो_inst_reg(omap_prm_context.irq_enable,
				 OMAP4430_PRM_OCP_SOCKET_INST,
				 omap4_prcm_irq_setup.mask);

	omap4_prm_ग_लिखो_inst_reg(omap_prm_context.pm_ctrl,
				 AM43XX_PRM_DEVICE_INST,
				 omap4_prcm_irq_setup.pm_ctrl);
पूर्ण

अटल पूर्णांक cpu_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (enable_off_mode)
			prm_save_context();
		अवरोध;
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (enable_off_mode)
			prm_restore_context();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/*
 * XXX करोcument
 */
अटल काष्ठा prm_ll_data omap44xx_prm_ll_data = अणु
	.पढ़ो_reset_sources = &omap44xx_prm_पढ़ो_reset_sources,
	.was_any_context_lost_old = &omap44xx_prm_was_any_context_lost_old,
	.clear_context_loss_flags_old = &omap44xx_prm_clear_context_loss_flags_old,
	.late_init = &omap44xx_prm_late_init,
	.निश्चित_hardreset	= omap4_prminst_निश्चित_hardreset,
	.deनिश्चित_hardreset	= omap4_prminst_deनिश्चित_hardreset,
	.is_hardreset_निश्चितed	= omap4_prminst_is_hardreset_निश्चितed,
	.reset_प्रणाली		= omap4_prminst_global_warm_sw_reset,
	.vp_check_txकरोne	= omap4_prm_vp_check_txकरोne,
	.vp_clear_txकरोne	= omap4_prm_vp_clear_txकरोne,
पूर्ण;

अटल स्थिर काष्ठा omap_prcm_init_data *prm_init_data;

पूर्णांक __init omap44xx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	अटल काष्ठा notअगरier_block nb;
	omap_prm_base_init();

	prm_init_data = data;

	अगर (data->flags & PRM_HAS_IO_WAKEUP)
		prm_features |= PRM_HAS_IO_WAKEUP;

	अगर (data->flags & PRM_HAS_VOLTAGE)
		prm_features |= PRM_HAS_VOLTAGE;

	omap4_prminst_set_prm_dev_inst(data->device_inst_offset);

	/* Add AM437X specअगरic dअगरferences */
	अगर (of_device_is_compatible(data->np, "ti,am4-prcm")) अणु
		omap4_prcm_irq_setup.nr_irqs = 1;
		omap4_prcm_irq_setup.nr_regs = 1;
		omap4_prcm_irq_setup.pm_ctrl = AM43XX_PRM_IO_PMCTRL_OFFSET;
		omap4_prcm_irq_setup.ack = AM43XX_PRM_IRQSTATUS_MPU_OFFSET;
		omap4_prcm_irq_setup.mask = AM43XX_PRM_IRQENABLE_MPU_OFFSET;
	पूर्ण

	/* Only AM43XX can lose prm context during rtc-ddr suspend */
	अगर (soc_is_am43xx()) अणु
		nb.notअगरier_call = cpu_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&nb);
	पूर्ण

	वापस prm_रेजिस्टर(&omap44xx_prm_ll_data);
पूर्ण

अटल पूर्णांक omap44xx_prm_late_init(व्योम)
अणु
	पूर्णांक irq_num;

	अगर (!(prm_features & PRM_HAS_IO_WAKEUP))
		वापस 0;

	irq_num = of_irq_get(prm_init_data->np, 0);
	अगर (irq_num == -EPROBE_DEFER)
		वापस irq_num;

	omap4_prcm_irq_setup.irq = irq_num;

	omap44xx_prm_enable_io_wakeup();

	वापस omap_prcm_रेजिस्टर_chain_handler(&omap4_prcm_irq_setup);
पूर्ण

अटल व्योम __निकास omap44xx_prm_निकास(व्योम)
अणु
	prm_unरेजिस्टर(&omap44xx_prm_ll_data);
पूर्ण
__निकासcall(omap44xx_prm_निकास);
