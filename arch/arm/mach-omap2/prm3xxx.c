<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3xxx PRM module functions
 *
 * Copyright (C) 2010-2012 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 * Benoथऍt Cousson
 * Paul Walmsley
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "vp.h"
#समावेश "powerdomain.h"
#समावेश "prm3xxx.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "cm3xxx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "clock.h"

अटल व्योम omap3xxx_prm_पढ़ो_pending_irqs(अचिन्हित दीर्घ *events);
अटल व्योम omap3xxx_prm_ocp_barrier(व्योम);
अटल व्योम omap3xxx_prm_save_and_clear_irqen(u32 *saved_mask);
अटल व्योम omap3xxx_prm_restore_irqen(u32 *saved_mask);

अटल स्थिर काष्ठा omap_prcm_irq omap3_prcm_irqs[] = अणु
	OMAP_PRCM_IRQ("wkup",	0,	0),
	OMAP_PRCM_IRQ("io",	9,	1),
पूर्ण;

अटल काष्ठा omap_prcm_irq_setup omap3_prcm_irq_setup = अणु
	.ack			= OMAP3_PRM_IRQSTATUS_MPU_OFFSET,
	.mask			= OMAP3_PRM_IRQENABLE_MPU_OFFSET,
	.nr_regs		= 1,
	.irqs			= omap3_prcm_irqs,
	.nr_irqs		= ARRAY_SIZE(omap3_prcm_irqs),
	.irq			= 11 + OMAP_INTC_START,
	.पढ़ो_pending_irqs	= &omap3xxx_prm_पढ़ो_pending_irqs,
	.ocp_barrier		= &omap3xxx_prm_ocp_barrier,
	.save_and_clear_irqen	= &omap3xxx_prm_save_and_clear_irqen,
	.restore_irqen		= &omap3xxx_prm_restore_irqen,
	.reconfigure_io_chain	= शून्य,
पूर्ण;

/*
 * omap3_prm_reset_src_map - map from bits in the PRM_RSTST hardware
 *   रेजिस्टर (which are specअगरic to OMAP3xxx SoCs) to reset source ID
 *   bit shअगरts (which is an OMAP SoC-independent क्रमागतeration)
 */
अटल काष्ठा prm_reset_src_map omap3xxx_prm_reset_src_map[] = अणु
	अणु OMAP3430_GLOBAL_COLD_RST_SHIFT, OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_GLOBAL_SW_RST_SHIFT, OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_SECURITY_VIOL_RST_SHIFT, OMAP_SECU_VIOL_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_MPU_WD_RST_SHIFT, OMAP_MPU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_SECURE_WD_RST_SHIFT, OMAP_MPU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_EXTERNAL_WARM_RST_SHIFT, OMAP_EXTWARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_VDD1_VOLTAGE_MANAGER_RST_SHIFT,
	  OMAP_VDD_MPU_VM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_VDD2_VOLTAGE_MANAGER_RST_SHIFT,
	  OMAP_VDD_CORE_VM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_ICEPICK_RST_SHIFT, OMAP_ICEPICK_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP3430_ICECRUSHER_RST_SHIFT, OMAP_ICECRUSHER_RST_SRC_ID_SHIFT पूर्ण,
	अणु -1, -1 पूर्ण,
पूर्ण;

/* PRM VP */

/*
 * काष्ठा omap3_vp - OMAP3 VP रेजिस्टर access description.
 * @tranxकरोne_status: VP_TRANXDONE_ST biपंचांगask in PRM_IRQSTATUS_MPU reg
 */
काष्ठा omap3_vp अणु
	u32 tranxकरोne_status;
पूर्ण;

अटल काष्ठा omap3_vp omap3_vp[] = अणु
	[OMAP3_VP_VDD_MPU_ID] = अणु
		.tranxकरोne_status = OMAP3430_VP1_TRANXDONE_ST_MASK,
	पूर्ण,
	[OMAP3_VP_VDD_CORE_ID] = अणु
		.tranxकरोne_status = OMAP3430_VP2_TRANXDONE_ST_MASK,
	पूर्ण,
पूर्ण;

#घोषणा MAX_VP_ID ARRAY_SIZE(omap3_vp);

अटल u32 omap3_prm_vp_check_txकरोne(u8 vp_id)
अणु
	काष्ठा omap3_vp *vp = &omap3_vp[vp_id];
	u32 irqstatus;

	irqstatus = omap2_prm_पढ़ो_mod_reg(OCP_MOD,
					   OMAP3_PRM_IRQSTATUS_MPU_OFFSET);
	वापस irqstatus & vp->tranxकरोne_status;
पूर्ण

अटल व्योम omap3_prm_vp_clear_txकरोne(u8 vp_id)
अणु
	काष्ठा omap3_vp *vp = &omap3_vp[vp_id];

	omap2_prm_ग_लिखो_mod_reg(vp->tranxकरोne_status,
				OCP_MOD, OMAP3_PRM_IRQSTATUS_MPU_OFFSET);
पूर्ण

u32 omap3_prm_vcvp_पढ़ो(u8 offset)
अणु
	वापस omap2_prm_पढ़ो_mod_reg(OMAP3430_GR_MOD, offset);
पूर्ण

व्योम omap3_prm_vcvp_ग_लिखो(u32 val, u8 offset)
अणु
	omap2_prm_ग_लिखो_mod_reg(val, OMAP3430_GR_MOD, offset);
पूर्ण

u32 omap3_prm_vcvp_rmw(u32 mask, u32 bits, u8 offset)
अणु
	वापस omap2_prm_rmw_mod_reg_bits(mask, bits, OMAP3430_GR_MOD, offset);
पूर्ण

/**
 * omap3xxx_prm_dpll3_reset - use DPLL3 reset to reboot the OMAP SoC
 *
 * Set the DPLL3 reset bit, which should reboot the SoC.  This is the
 * recommended way to restart the SoC, considering Errata i520.  No
 * वापस value.
 */
अटल व्योम omap3xxx_prm_dpll3_reset(व्योम)
अणु
	omap2_prm_set_mod_reg_bits(OMAP_RST_DPLL3_MASK, OMAP3430_GR_MOD,
				   OMAP2_RM_RSTCTRL);
	/* OCP barrier */
	omap2_prm_पढ़ो_mod_reg(OMAP3430_GR_MOD, OMAP2_RM_RSTCTRL);
पूर्ण

/**
 * omap3xxx_prm_पढ़ो_pending_irqs - पढ़ो pending PRM MPU IRQs पूर्णांकo @events
 * @events: ptr to a u32, pपुनः_स्मृतिated by caller
 *
 * Read PRM_IRQSTATUS_MPU bits, AND'ed with the currently-enabled PRM
 * MPU IRQs, and store the result पूर्णांकo the u32 poपूर्णांकed to by @events.
 * No वापस value.
 */
अटल व्योम omap3xxx_prm_पढ़ो_pending_irqs(अचिन्हित दीर्घ *events)
अणु
	u32 mask, st;

	/* XXX Can the mask पढ़ो be aव्योमed (e.g., can it come from RAM?) */
	mask = omap2_prm_पढ़ो_mod_reg(OCP_MOD, OMAP3_PRM_IRQENABLE_MPU_OFFSET);
	st = omap2_prm_पढ़ो_mod_reg(OCP_MOD, OMAP3_PRM_IRQSTATUS_MPU_OFFSET);

	events[0] = mask & st;
पूर्ण

/**
 * omap3xxx_prm_ocp_barrier - क्रमce buffered MPU ग_लिखोs to the PRM to complete
 *
 * Force any buffered ग_लिखोs to the PRM IP block to complete.  Needed
 * by the PRM IRQ handler, which पढ़ोs and ग_लिखोs directly to the IP
 * block, to aव्योम race conditions after acknowledging or clearing IRQ
 * bits.  No वापस value.
 */
अटल व्योम omap3xxx_prm_ocp_barrier(व्योम)
अणु
	omap2_prm_पढ़ो_mod_reg(OCP_MOD, OMAP3_PRM_REVISION_OFFSET);
पूर्ण

/**
 * omap3xxx_prm_save_and_clear_irqen - save/clear PRM_IRQENABLE_MPU reg
 * @saved_mask: ptr to a u32 array to save IRQENABLE bits
 *
 * Save the PRM_IRQENABLE_MPU रेजिस्टर to @saved_mask.  @saved_mask
 * must be allocated by the caller.  Intended to be used in the PRM
 * पूर्णांकerrupt handler suspend callback.  The OCP barrier is needed to
 * ensure the ग_लिखो to disable PRM पूर्णांकerrupts reaches the PRM beक्रमe
 * वापसing; otherwise, spurious पूर्णांकerrupts might occur.  No वापस
 * value.
 */
अटल व्योम omap3xxx_prm_save_and_clear_irqen(u32 *saved_mask)
अणु
	saved_mask[0] = omap2_prm_पढ़ो_mod_reg(OCP_MOD,
					       OMAP3_PRM_IRQENABLE_MPU_OFFSET);
	omap2_prm_ग_लिखो_mod_reg(0, OCP_MOD, OMAP3_PRM_IRQENABLE_MPU_OFFSET);

	/* OCP barrier */
	omap2_prm_पढ़ो_mod_reg(OCP_MOD, OMAP3_PRM_REVISION_OFFSET);
पूर्ण

/**
 * omap3xxx_prm_restore_irqen - set PRM_IRQENABLE_MPU रेजिस्टर from args
 * @saved_mask: ptr to a u32 array of IRQENABLE bits saved previously
 *
 * Restore the PRM_IRQENABLE_MPU रेजिस्टर from @saved_mask.  Intended
 * to be used in the PRM पूर्णांकerrupt handler resume callback to restore
 * values saved by omap3xxx_prm_save_and_clear_irqen().  No OCP
 * barrier should be needed here; any pending PRM पूर्णांकerrupts will fire
 * once the ग_लिखोs reach the PRM.  No वापस value.
 */
अटल व्योम omap3xxx_prm_restore_irqen(u32 *saved_mask)
अणु
	omap2_prm_ग_लिखो_mod_reg(saved_mask[0], OCP_MOD,
				OMAP3_PRM_IRQENABLE_MPU_OFFSET);
पूर्ण

/**
 * omap3xxx_prm_clear_mod_irqs - clear wake-up events from PRCM पूर्णांकerrupt
 * @module: PRM module to clear wakeups from
 * @regs: रेजिस्टर set to clear, 1 or 3
 * @wkst_mask: wkst bits to clear
 *
 * The purpose of this function is to clear any wake-up events latched
 * in the PRCM PM_WKST_x रेजिस्टरs. It is possible that a wake-up event
 * may occur whilst attempting to clear a PM_WKST_x रेजिस्टर and thus
 * set another bit in this रेजिस्टर. A जबतक loop is used to ensure
 * that any peripheral wake-up events occurring जबतक attempting to
 * clear the PM_WKST_x are detected and cleared.
 */
अटल पूर्णांक omap3xxx_prm_clear_mod_irqs(s16 module, u8 regs, u32 wkst_mask)
अणु
	u32 wkst, fclk, iclk, clken;
	u16 wkst_off = (regs == 3) ? OMAP3430ES2_PM_WKST3 : PM_WKST1;
	u16 fclk_off = (regs == 3) ? OMAP3430ES2_CM_FCLKEN3 : CM_FCLKEN1;
	u16 iclk_off = (regs == 3) ? CM_ICLKEN3 : CM_ICLKEN1;
	u16 grpsel_off = (regs == 3) ?
		OMAP3430ES2_PM_MPUGRPSEL3 : OMAP3430_PM_MPUGRPSEL;
	पूर्णांक c = 0;

	wkst = omap2_prm_पढ़ो_mod_reg(module, wkst_off);
	wkst &= omap2_prm_पढ़ो_mod_reg(module, grpsel_off);
	wkst &= wkst_mask;
	अगर (wkst) अणु
		iclk = omap2_cm_पढ़ो_mod_reg(module, iclk_off);
		fclk = omap2_cm_पढ़ो_mod_reg(module, fclk_off);
		जबतक (wkst) अणु
			clken = wkst;
			omap2_cm_set_mod_reg_bits(clken, module, iclk_off);
			/*
			 * For USBHOST, we करोn't know whether HOST1 or
			 * HOST2 woke us up, so enable both f-घड़ीs
			 */
			अगर (module == OMAP3430ES2_USBHOST_MOD)
				clken |= 1 << OMAP3430ES2_EN_USBHOST2_SHIFT;
			omap2_cm_set_mod_reg_bits(clken, module, fclk_off);
			omap2_prm_ग_लिखो_mod_reg(wkst, module, wkst_off);
			wkst = omap2_prm_पढ़ो_mod_reg(module, wkst_off);
			wkst &= wkst_mask;
			c++;
		पूर्ण
		omap2_cm_ग_लिखो_mod_reg(iclk, module, iclk_off);
		omap2_cm_ग_लिखो_mod_reg(fclk, module, fclk_off);
	पूर्ण

	वापस c;
पूर्ण

/**
 * omap3_prm_reset_modem - toggle reset संकेत क्रम modem
 *
 * Toggles the reset संकेत to modem IP block. Required to allow
 * OMAP3430 without stacked modem to idle properly.
 */
व्योम __init omap3_prm_reset_modem(व्योम)
अणु
	omap2_prm_ग_लिखो_mod_reg(
		OMAP3430_RM_RSTCTRL_CORE_MODEM_SW_RSTPWRON_MASK |
		OMAP3430_RM_RSTCTRL_CORE_MODEM_SW_RST_MASK,
				CORE_MOD, OMAP2_RM_RSTCTRL);
	omap2_prm_ग_लिखो_mod_reg(0, CORE_MOD, OMAP2_RM_RSTCTRL);
पूर्ण

/**
 * omap3_prm_init_pm - initialize PM related रेजिस्टरs क्रम PRM
 * @has_uart4: SoC has UART4
 * @has_iva: SoC has IVA
 *
 * Initializes PRM रेजिस्टरs क्रम PM use. Called from PM init.
 */
व्योम __init omap3_prm_init_pm(bool has_uart4, bool has_iva)
अणु
	u32 en_uart4_mask;
	u32 grpsel_uart4_mask;

	/*
	 * Enable control of expternal oscillator through
	 * sys_clkreq. In the दीर्घ run घड़ी framework should
	 * take care of this.
	 */
	omap2_prm_rmw_mod_reg_bits(OMAP_AUTOEXTCLKMODE_MASK,
				   1 << OMAP_AUTOEXTCLKMODE_SHIFT,
				   OMAP3430_GR_MOD,
				   OMAP3_PRM_CLKSRC_CTRL_OFFSET);

	/* setup wakup source */
	omap2_prm_ग_लिखो_mod_reg(OMAP3430_EN_IO_MASK | OMAP3430_EN_GPIO1_MASK |
				OMAP3430_EN_GPT1_MASK | OMAP3430_EN_GPT12_MASK,
				WKUP_MOD, PM_WKEN);
	/* No need to ग_लिखो EN_IO, that is always enabled */
	omap2_prm_ग_लिखो_mod_reg(OMAP3430_GRPSEL_GPIO1_MASK |
				OMAP3430_GRPSEL_GPT1_MASK |
				OMAP3430_GRPSEL_GPT12_MASK,
				WKUP_MOD, OMAP3430_PM_MPUGRPSEL);

	/* Enable PM_WKEN to support DSS LPR */
	omap2_prm_ग_लिखो_mod_reg(OMAP3430_PM_WKEN_DSS_EN_DSS_MASK,
				OMAP3430_DSS_MOD, PM_WKEN);

	अगर (has_uart4) अणु
		en_uart4_mask = OMAP3630_EN_UART4_MASK;
		grpsel_uart4_mask = OMAP3630_GRPSEL_UART4_MASK;
	पूर्ण अन्यथा अणु
		en_uart4_mask = 0;
		grpsel_uart4_mask = 0;
	पूर्ण

	/* Enable wakeups in PER */
	omap2_prm_ग_लिखो_mod_reg(en_uart4_mask |
				OMAP3430_EN_GPIO2_MASK |
				OMAP3430_EN_GPIO3_MASK |
				OMAP3430_EN_GPIO4_MASK |
				OMAP3430_EN_GPIO5_MASK |
				OMAP3430_EN_GPIO6_MASK |
				OMAP3430_EN_UART3_MASK |
				OMAP3430_EN_MCBSP2_MASK |
				OMAP3430_EN_MCBSP3_MASK |
				OMAP3430_EN_MCBSP4_MASK,
				OMAP3430_PER_MOD, PM_WKEN);

	/* and allow them to wake up MPU */
	omap2_prm_ग_लिखो_mod_reg(grpsel_uart4_mask |
				OMAP3430_GRPSEL_GPIO2_MASK |
				OMAP3430_GRPSEL_GPIO3_MASK |
				OMAP3430_GRPSEL_GPIO4_MASK |
				OMAP3430_GRPSEL_GPIO5_MASK |
				OMAP3430_GRPSEL_GPIO6_MASK |
				OMAP3430_GRPSEL_UART3_MASK |
				OMAP3430_GRPSEL_MCBSP2_MASK |
				OMAP3430_GRPSEL_MCBSP3_MASK |
				OMAP3430_GRPSEL_MCBSP4_MASK,
				OMAP3430_PER_MOD, OMAP3430_PM_MPUGRPSEL);

	/* Don't attach IVA पूर्णांकerrupts */
	अगर (has_iva) अणु
		omap2_prm_ग_लिखो_mod_reg(0, WKUP_MOD, OMAP3430_PM_IVAGRPSEL);
		omap2_prm_ग_लिखो_mod_reg(0, CORE_MOD, OMAP3430_PM_IVAGRPSEL1);
		omap2_prm_ग_लिखो_mod_reg(0, CORE_MOD, OMAP3430ES2_PM_IVAGRPSEL3);
		omap2_prm_ग_लिखो_mod_reg(0, OMAP3430_PER_MOD,
					OMAP3430_PM_IVAGRPSEL);
	पूर्ण

	/* Clear any pending 'reset' flags */
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, MPU_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, CORE_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, OMAP3430_PER_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, OMAP3430_EMU_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, OMAP3430_NEON_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, OMAP3430_DSS_MOD, OMAP2_RM_RSTST);
	omap2_prm_ग_लिखो_mod_reg(0xffffffff, OMAP3430ES2_USBHOST_MOD,
				OMAP2_RM_RSTST);

	/* Clear any pending PRCM पूर्णांकerrupts */
	omap2_prm_ग_लिखो_mod_reg(0, OCP_MOD, OMAP3_PRM_IRQSTATUS_MPU_OFFSET);

	/* We need to idle iva2_pwrdm even on am3703 with no iva2. */
	omap3xxx_prm_iva_idle();

	omap3_prm_reset_modem();
पूर्ण

/**
 * omap3430_pre_es3_1_reconfigure_io_chain - restart wake-up daisy chain
 *
 * The ST_IO_CHAIN bit करोes not exist in 3430 beक्रमe es3.1. The only
 * thing we can करो is toggle EN_IO bit क्रम earlier omaps.
 */
अटल व्योम omap3430_pre_es3_1_reconfigure_io_chain(व्योम)
अणु
	omap2_prm_clear_mod_reg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
				     PM_WKEN);
	omap2_prm_set_mod_reg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
				   PM_WKEN);
	omap2_prm_पढ़ो_mod_reg(WKUP_MOD, PM_WKEN);
पूर्ण

/**
 * omap3_prm_reconfigure_io_chain - clear latches and reconfigure I/O chain
 *
 * Clear any previously-latched I/O wakeup events and ensure that the
 * I/O wakeup gates are aligned with the current mux settings.  Works
 * by निश्चितing WUCLKIN, रुकोing क्रम WUCLKOUT to be निश्चितed, and then
 * deनिश्चितing WUCLKIN and clearing the ST_IO_CHAIN WKST bit.  No
 * वापस value. These रेजिस्टरs are only available in 3430 es3.1 and later.
 */
अटल व्योम omap3_prm_reconfigure_io_chain(व्योम)
अणु
	पूर्णांक i = 0;

	omap2_prm_set_mod_reg_bits(OMAP3430_EN_IO_CHAIN_MASK, WKUP_MOD,
				   PM_WKEN);

	omap_test_समयout(omap2_prm_पढ़ो_mod_reg(WKUP_MOD, PM_WKST) &
			  OMAP3430_ST_IO_CHAIN_MASK,
			  MAX_IOPAD_LATCH_TIME, i);
	अगर (i == MAX_IOPAD_LATCH_TIME)
		pr_warn("PRM: I/O chain clock line assertion timed out\n");

	omap2_prm_clear_mod_reg_bits(OMAP3430_EN_IO_CHAIN_MASK, WKUP_MOD,
				     PM_WKEN);

	omap2_prm_set_mod_reg_bits(OMAP3430_ST_IO_CHAIN_MASK, WKUP_MOD,
				   PM_WKST);

	omap2_prm_पढ़ो_mod_reg(WKUP_MOD, PM_WKST);
पूर्ण

/**
 * omap3xxx_prm_enable_io_wakeup - enable wakeup events from I/O wakeup latches
 *
 * Activates the I/O wakeup event latches and allows events logged by
 * those latches to संकेत a wakeup event to the PRCM.  For I/O
 * wakeups to occur, WAKEUPENABLE bits must be set in the pad mux
 * रेजिस्टरs, and omap3xxx_prm_reconfigure_io_chain() must be called.
 * No वापस value.
 */
अटल व्योम omap3xxx_prm_enable_io_wakeup(व्योम)
अणु
	अगर (prm_features & PRM_HAS_IO_WAKEUP)
		omap2_prm_set_mod_reg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
					   PM_WKEN);
पूर्ण

/**
 * omap3xxx_prm_पढ़ो_reset_sources - वापस the last SoC reset source
 *
 * Return a u32 representing the last reset sources of the SoC.  The
 * वापसed reset source bits are standardized across OMAP SoCs.
 */
अटल u32 omap3xxx_prm_पढ़ो_reset_sources(व्योम)
अणु
	काष्ठा prm_reset_src_map *p;
	u32 r = 0;
	u32 v;

	v = omap2_prm_पढ़ो_mod_reg(WKUP_MOD, OMAP2_RM_RSTST);

	p = omap3xxx_prm_reset_src_map;
	जबतक (p->reg_shअगरt >= 0 && p->std_shअगरt >= 0) अणु
		अगर (v & (1 << p->reg_shअगरt))
			r |= 1 << p->std_shअगरt;
		p++;
	पूर्ण

	वापस r;
पूर्ण

/**
 * omap3xxx_prm_iva_idle - ensure IVA is in idle so it can be put पूर्णांकo retention
 *
 * In हालs where IVA2 is activated by bootcode, it may prevent
 * full-chip retention or off-mode because it is not idle.  This
 * function क्रमces the IVA2 पूर्णांकo idle state so it can go
 * पूर्णांकo retention/off and thus allow full-chip retention/off.
 */
व्योम omap3xxx_prm_iva_idle(व्योम)
अणु
	/* ensure IVA2 घड़ी is disabled */
	omap2_cm_ग_लिखो_mod_reg(0, OMAP3430_IVA2_MOD, CM_FCLKEN);

	/* अगर no घड़ी activity, nothing अन्यथा to करो */
	अगर (!(omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, OMAP3430_CM_CLKSTST) &
	      OMAP3430_CLKACTIVITY_IVA2_MASK))
		वापस;

	/* Reset IVA2 */
	omap2_prm_ग_लिखो_mod_reg(OMAP3430_RST1_IVA2_MASK |
				OMAP3430_RST2_IVA2_MASK |
				OMAP3430_RST3_IVA2_MASK,
				OMAP3430_IVA2_MOD, OMAP2_RM_RSTCTRL);

	/* Enable IVA2 घड़ी */
	omap2_cm_ग_लिखो_mod_reg(OMAP3430_CM_FCLKEN_IVA2_EN_IVA2_MASK,
			       OMAP3430_IVA2_MOD, CM_FCLKEN);

	/* Un-reset IVA2 */
	omap2_prm_ग_लिखो_mod_reg(0, OMAP3430_IVA2_MOD, OMAP2_RM_RSTCTRL);

	/* Disable IVA2 घड़ी */
	omap2_cm_ग_लिखो_mod_reg(0, OMAP3430_IVA2_MOD, CM_FCLKEN);

	/* Reset IVA2 */
	omap2_prm_ग_लिखो_mod_reg(OMAP3430_RST1_IVA2_MASK |
				OMAP3430_RST2_IVA2_MASK |
				OMAP3430_RST3_IVA2_MASK,
				OMAP3430_IVA2_MOD, OMAP2_RM_RSTCTRL);
पूर्ण

/**
 * omap3xxx_prm_clear_global_cold_reset - checks the global cold reset status
 *					  and clears it अगर निश्चितed
 *
 * Checks अगर cold-reset has occurred and clears the status bit अगर yes. Returns
 * 1 अगर cold-reset has occurred, 0 otherwise.
 */
पूर्णांक omap3xxx_prm_clear_global_cold_reset(व्योम)
अणु
	अगर (omap2_prm_पढ़ो_mod_reg(OMAP3430_GR_MOD, OMAP3_PRM_RSTST_OFFSET) &
	    OMAP3430_GLOBAL_COLD_RST_MASK) अणु
		omap2_prm_set_mod_reg_bits(OMAP3430_GLOBAL_COLD_RST_MASK,
					   OMAP3430_GR_MOD,
					   OMAP3_PRM_RSTST_OFFSET);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम omap3_prm_save_scratchpad_contents(u32 *ptr)
अणु
	*ptr++ = omap2_prm_पढ़ो_mod_reg(OMAP3430_GR_MOD,
					OMAP3_PRM_CLKSRC_CTRL_OFFSET);

	*ptr++ = omap2_prm_पढ़ो_mod_reg(OMAP3430_GR_MOD,
					OMAP3_PRM_CLKSEL_OFFSET);
पूर्ण

/* Powerकरोमुख्य low-level functions */

अटल पूर्णांक omap3_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	omap2_prm_rmw_mod_reg_bits(OMAP_POWERSTATE_MASK,
				   (pwrst << OMAP_POWERSTATE_SHIFT),
				   pwrdm->prcm_offs, OMAP2_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTCTRL,
					     OMAP_POWERSTATE_MASK);
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTST,
					     OMAP_POWERSTATEST_MASK);
पूर्ण

/* Applicable only क्रम OMAP3. Not supported on OMAP2 */
अटल पूर्णांक omap3_pwrdm_पढ़ो_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP3430_PM_PREPWSTST,
					     OMAP3430_LASTPOWERSTATEENTERED_MASK);
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTST,
					     OMAP3430_LOGICSTATEST_MASK);
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTCTRL,
					     OMAP3430_LOGICSTATEST_MASK);
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_prev_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP3430_PM_PREPWSTST,
					     OMAP3430_LASTLOGICSTATEENTERED_MASK);
पूर्ण

अटल पूर्णांक omap3_get_mem_bank_lasपंचांगemst_mask(u8 bank)
अणु
	चयन (bank) अणु
	हाल 0:
		वापस OMAP3430_LASTMEM1STATEENTERED_MASK;
	हाल 1:
		वापस OMAP3430_LASTMEM2STATEENTERED_MASK;
	हाल 2:
		वापस OMAP3430_LASTSHAREDL2CACHEFLATSTATEENTERED_MASK;
	हाल 3:
		वापस OMAP3430_LASTL2FLATMEMSTATEENTERED_MASK;
	शेष:
		WARN_ON(1); /* should never happen */
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक omap3_pwrdm_पढ़ो_prev_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m;

	m = omap3_get_mem_bank_lasपंचांगemst_mask(bank);

	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
				OMAP3430_PM_PREPWSTST, m);
पूर्ण

अटल पूर्णांक omap3_pwrdm_clear_all_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	omap2_prm_ग_लिखो_mod_reg(0, pwrdm->prcm_offs, OMAP3430_PM_PREPWSTST);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3_pwrdm_enable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_rmw_mod_reg_bits(0,
					  1 << OMAP3430ES2_SAVEANDRESTORE_SHIFT,
					  pwrdm->prcm_offs, OMAP2_PM_PWSTCTRL);
पूर्ण

अटल पूर्णांक omap3_pwrdm_disable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_rmw_mod_reg_bits(1 << OMAP3430ES2_SAVEANDRESTORE_SHIFT,
					  0, pwrdm->prcm_offs,
					  OMAP2_PM_PWSTCTRL);
पूर्ण

काष्ठा pwrdm_ops omap3_pwrdm_operations = अणु
	.pwrdm_set_next_pwrst	= omap3_pwrdm_set_next_pwrst,
	.pwrdm_पढ़ो_next_pwrst	= omap3_pwrdm_पढ़ो_next_pwrst,
	.pwrdm_पढ़ो_pwrst	= omap3_pwrdm_पढ़ो_pwrst,
	.pwrdm_पढ़ो_prev_pwrst	= omap3_pwrdm_पढ़ो_prev_pwrst,
	.pwrdm_set_logic_retst	= omap2_pwrdm_set_logic_retst,
	.pwrdm_पढ़ो_logic_pwrst	= omap3_pwrdm_पढ़ो_logic_pwrst,
	.pwrdm_पढ़ो_logic_retst	= omap3_pwrdm_पढ़ो_logic_retst,
	.pwrdm_पढ़ो_prev_logic_pwrst	= omap3_pwrdm_पढ़ो_prev_logic_pwrst,
	.pwrdm_set_mem_onst	= omap2_pwrdm_set_mem_onst,
	.pwrdm_set_mem_retst	= omap2_pwrdm_set_mem_retst,
	.pwrdm_पढ़ो_mem_pwrst	= omap2_pwrdm_पढ़ो_mem_pwrst,
	.pwrdm_पढ़ो_mem_retst	= omap2_pwrdm_पढ़ो_mem_retst,
	.pwrdm_पढ़ो_prev_mem_pwrst	= omap3_pwrdm_पढ़ो_prev_mem_pwrst,
	.pwrdm_clear_all_prev_pwrst	= omap3_pwrdm_clear_all_prev_pwrst,
	.pwrdm_enable_hdwr_sar	= omap3_pwrdm_enable_hdwr_sar,
	.pwrdm_disable_hdwr_sar	= omap3_pwrdm_disable_hdwr_sar,
	.pwrdm_रुको_transition	= omap2_pwrdm_रुको_transition,
पूर्ण;

/*
 *
 */

अटल पूर्णांक omap3xxx_prm_late_init(व्योम);

अटल काष्ठा prm_ll_data omap3xxx_prm_ll_data = अणु
	.पढ़ो_reset_sources = &omap3xxx_prm_पढ़ो_reset_sources,
	.late_init = &omap3xxx_prm_late_init,
	.निश्चित_hardreset = &omap2_prm_निश्चित_hardreset,
	.deनिश्चित_hardreset = &omap2_prm_deनिश्चित_hardreset,
	.is_hardreset_निश्चितed = &omap2_prm_is_hardreset_निश्चितed,
	.reset_प्रणाली = &omap3xxx_prm_dpll3_reset,
	.clear_mod_irqs = &omap3xxx_prm_clear_mod_irqs,
	.vp_check_txकरोne = &omap3_prm_vp_check_txकरोne,
	.vp_clear_txकरोne = &omap3_prm_vp_clear_txकरोne,
पूर्ण;

पूर्णांक __init omap3xxx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	omap2_clk_legacy_provider_init(TI_CLKM_PRM,
				       prm_base.va + OMAP3430_IVA2_MOD);
	अगर (omap3_has_io_wakeup())
		prm_features |= PRM_HAS_IO_WAKEUP;

	वापस prm_रेजिस्टर(&omap3xxx_prm_ll_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id omap3_prm_dt_match_table[] = अणु
	अणु .compatible = "ti,omap3-prm" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक omap3xxx_prm_late_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक irq_num;

	अगर (!(prm_features & PRM_HAS_IO_WAKEUP))
		वापस 0;

	अगर (omap3_has_io_chain_ctrl())
		omap3_prcm_irq_setup.reconfigure_io_chain =
			omap3_prm_reconfigure_io_chain;
	अन्यथा
		omap3_prcm_irq_setup.reconfigure_io_chain =
			omap3430_pre_es3_1_reconfigure_io_chain;

	np = of_find_matching_node(शून्य, omap3_prm_dt_match_table);
	अगर (!np) अणु
		pr_err("PRM: no device tree node for interrupt?\n");

		वापस -ENODEV;
	पूर्ण

	irq_num = of_irq_get(np, 0);
	अगर (irq_num == -EPROBE_DEFER)
		वापस irq_num;

	omap3_prcm_irq_setup.irq = irq_num;

	omap3xxx_prm_enable_io_wakeup();

	वापस omap_prcm_रेजिस्टर_chain_handler(&omap3_prcm_irq_setup);
पूर्ण

अटल व्योम __निकास omap3xxx_prm_निकास(व्योम)
अणु
	prm_unरेजिस्टर(&omap3xxx_prm_ll_data);
पूर्ण
__निकासcall(omap3xxx_prm_निकास);
