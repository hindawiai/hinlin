<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2 Power Management Routines
 *
 * Copyright (C) 2005 Texas Instruments, Inc.
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Written by:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Tony Lindgren
 * Juha Yrjola
 * Amit Kucheria <amit.kucheria@nokia.com>
 * Igor Stoppa <igor.stoppa@nokia.com>
 *
 * Based on pm.c क्रम omap1
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/sched.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/irq.h>
#समावेश <linux/समय.स>

#समावेश <यंत्र/fncpy.h>

#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <linux/omap-dma.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "clock.h"
#समावेश "prm2xxx.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "cm2xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "sdrc.h"
#समावेश "sram.h"
#समावेश "pm.h"
#समावेश "control.h"
#समावेश "powerdomain.h"
#समावेश "clockdomain.h"

अटल व्योम (*omap2_sram_suspend)(u32 dllctrl, व्योम __iomem *sdrc_dlla_ctrl,
				  व्योम __iomem *sdrc_घातer);

अटल काष्ठा घातerकरोमुख्य *mpu_pwrdm, *core_pwrdm;
अटल काष्ठा घड़ीकरोमुख्य *dsp_clkdm, *mpu_clkdm, *wkup_clkdm, *gfx_clkdm;

अटल काष्ठा clk *osc_ck, *emul_ck;

अटल पूर्णांक omap2_enter_full_retention(व्योम)
अणु
	u32 l;

	/* There is 1 reference hold क्रम all children of the oscillator
	 * घड़ी, the following will हटाओ it. If no one अन्यथा uses the
	 * oscillator itself it will be disabled अगर/when we enter retention
	 * mode.
	 */
	clk_disable(osc_ck);

	/* Clear old wake-up events */
	/* REVISIT: These ग_लिखो to reserved bits? */
	omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
	omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);
	omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, ~0);

	pwrdm_set_next_pwrst(core_pwrdm, PWRDM_POWER_RET);
	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_RET);

	/* Workaround to समाप्त USB */
	l = omap_ctrl_पढ़ोl(OMAP2_CONTROL_DEVCONF0) | OMAP24XX_USBSTANDBYCTRL;
	omap_ctrl_ग_लिखोl(l, OMAP2_CONTROL_DEVCONF0);

	/* One last check क्रम pending IRQs to aव्योम extra latency due
	 * to sleeping unnecessarily. */
	अगर (omap_irq_pending())
		जाओ no_sleep;

	/* Jump to SRAM suspend code */
	omap2_sram_suspend(sdrc_पढ़ो_reg(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_POWER));

no_sleep:
	clk_enable(osc_ck);

	/* clear CORE wake-up events */
	omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
	omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);

	/* wakeup करोमुख्य events - bit 1: GPT1, bit5 GPIO */
	omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, 0x4 | 0x1);

	/* MPU करोमुख्य wake events */
	omap_prm_clear_mod_irqs(OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET, 0x1);

	omap_prm_clear_mod_irqs(OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET, 0x20);

	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
	pwrdm_set_next_pwrst(core_pwrdm, PWRDM_POWER_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक sti_console_enabled;

अटल पूर्णांक omap2_allow_mpu_retention(व्योम)
अणु
	अगर (!omap2xxx_cm_mpu_retention_allowed())
		वापस 0;
	अगर (sti_console_enabled)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम omap2_enter_mpu_retention(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;

	/* The peripherals seem not to be able to wake up the MPU when
	 * it is in retention mode. */
	अगर (omap2_allow_mpu_retention()) अणु
		/* REVISIT: These ग_लिखो to reserved bits? */
		omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
		omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);
		omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, ~0);

		/* Try to enter MPU retention */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_RET);

	पूर्ण अन्यथा अणु
		/* Block MPU retention */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
	पूर्ण

	/* WFI */
	यंत्र("mcr p15, 0, %0, c7, c0, 4" : : "r" (zero) : "memory", "cc");

	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
पूर्ण

अटल पूर्णांक omap2_can_sleep(व्योम)
अणु
	अगर (omap2xxx_cm_fclks_active())
		वापस 0;
	अगर (__clk_is_enabled(osc_ck))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम omap2_pm_idle(व्योम)
अणु
	पूर्णांक error;

	अगर (omap_irq_pending())
		वापस;

	error = cpu_cluster_pm_enter();
	अगर (error || !omap2_can_sleep()) अणु
		omap2_enter_mpu_retention();
		जाओ out_cpu_cluster_pm;
	पूर्ण

	omap2_enter_full_retention();

out_cpu_cluster_pm:
	cpu_cluster_pm_निकास();
पूर्ण

अटल व्योम __init prcm_setup_regs(व्योम)
अणु
	पूर्णांक i, num_mem_banks;
	काष्ठा घातerकरोमुख्य *pwrdm;

	/*
	 * Enable स्वतःidle
	 * XXX This should be handled by hwmod code or PRCM init code
	 */
	omap2_prm_ग_लिखो_mod_reg(OMAP24XX_AUTOIDLE_MASK, OCP_MOD,
			  OMAP2_PRCM_SYSCONFIG_OFFSET);

	/*
	 * Set CORE घातerकरोमुख्य memory banks to retain their contents
	 * during RETENTION
	 */
	num_mem_banks = pwrdm_get_mem_bank_count(core_pwrdm);
	क्रम (i = 0; i < num_mem_banks; i++)
		pwrdm_set_mem_retst(core_pwrdm, i, PWRDM_POWER_RET);

	pwrdm_set_logic_retst(core_pwrdm, PWRDM_POWER_RET);

	pwrdm_set_logic_retst(mpu_pwrdm, PWRDM_POWER_RET);

	/* Force-घातer करोwn DSP, GFX घातerकरोमुख्यs */

	pwrdm = clkdm_get_pwrdm(dsp_clkdm);
	pwrdm_set_next_pwrst(pwrdm, PWRDM_POWER_OFF);

	pwrdm = clkdm_get_pwrdm(gfx_clkdm);
	pwrdm_set_next_pwrst(pwrdm, PWRDM_POWER_OFF);

	/* Enable hardware-supervised idle क्रम all clkdms */
	clkdm_क्रम_each(omap_pm_clkdms_setup, शून्य);
	clkdm_add_wkdep(mpu_clkdm, wkup_clkdm);

	omap_common_suspend_init(omap2_enter_full_retention);

	/* REVISIT: Configure number of 32 kHz घड़ी cycles क्रम sys_clk
	 * stabilisation */
	omap2_prm_ग_लिखो_mod_reg(15 << OMAP_SETUP_TIME_SHIFT, OMAP24XX_GR_MOD,
				OMAP2_PRCM_CLKSSETUP_OFFSET);

	/* Configure स्वतःmatic voltage transition */
	omap2_prm_ग_लिखो_mod_reg(2 << OMAP_SETUP_TIME_SHIFT, OMAP24XX_GR_MOD,
				OMAP2_PRCM_VOLTSETUP_OFFSET);
	omap2_prm_ग_लिखो_mod_reg(OMAP24XX_AUTO_EXTVOLT_MASK |
				(0x1 << OMAP24XX_SETOFF_LEVEL_SHIFT) |
				OMAP24XX_MEMRETCTRL_MASK |
				(0x1 << OMAP24XX_SETRET_LEVEL_SHIFT) |
				(0x0 << OMAP24XX_VOLT_LEVEL_SHIFT),
				OMAP24XX_GR_MOD, OMAP2_PRCM_VOLTCTRL_OFFSET);

	/* Enable wake-up events */
	omap2_prm_ग_लिखो_mod_reg(OMAP24XX_EN_GPIOS_MASK | OMAP24XX_EN_GPT1_MASK,
				WKUP_MOD, PM_WKEN);

	/* Enable SYS_CLKEN control when all करोमुख्यs idle */
	omap2_prm_set_mod_reg_bits(OMAP_AUTOEXTCLKMODE_MASK, OMAP24XX_GR_MOD,
				   OMAP2_PRCM_CLKSRC_CTRL_OFFSET);
पूर्ण

पूर्णांक __init omap2_pm_init(व्योम)
अणु
	u32 l;

	prपूर्णांकk(KERN_INFO "Power Management for OMAP2 initializing\n");
	l = omap2_prm_पढ़ो_mod_reg(OCP_MOD, OMAP2_PRCM_REVISION_OFFSET);
	prपूर्णांकk(KERN_INFO "PRCM revision %d.%d\n", (l >> 4) & 0x0f, l & 0x0f);

	/* Look up important घातerकरोमुख्यs */

	mpu_pwrdm = pwrdm_lookup("mpu_pwrdm");
	अगर (!mpu_pwrdm)
		pr_err("PM: mpu_pwrdm not found\n");

	core_pwrdm = pwrdm_lookup("core_pwrdm");
	अगर (!core_pwrdm)
		pr_err("PM: core_pwrdm not found\n");

	/* Look up important घड़ीकरोमुख्यs */

	mpu_clkdm = clkdm_lookup("mpu_clkdm");
	अगर (!mpu_clkdm)
		pr_err("PM: mpu_clkdm not found\n");

	wkup_clkdm = clkdm_lookup("wkup_clkdm");
	अगर (!wkup_clkdm)
		pr_err("PM: wkup_clkdm not found\n");

	dsp_clkdm = clkdm_lookup("dsp_clkdm");
	अगर (!dsp_clkdm)
		pr_err("PM: dsp_clkdm not found\n");

	gfx_clkdm = clkdm_lookup("gfx_clkdm");
	अगर (!gfx_clkdm)
		pr_err("PM: gfx_clkdm not found\n");


	osc_ck = clk_get(शून्य, "osc_ck");
	अगर (IS_ERR(osc_ck)) अणु
		prपूर्णांकk(KERN_ERR "could not get osc_ck\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cpu_is_omap242x()) अणु
		emul_ck = clk_get(शून्य, "emul_ck");
		अगर (IS_ERR(emul_ck)) अणु
			prपूर्णांकk(KERN_ERR "could not get emul_ck\n");
			clk_put(osc_ck);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	prcm_setup_regs();

	/*
	 * We copy the assembler sleep/wakeup routines to SRAM.
	 * These routines need to be in SRAM as that's the only
	 * memory the MPU can see when it wakes up after the entire
	 * chip enters idle.
	 */
	omap2_sram_suspend = omap_sram_push(omap24xx_cpu_suspend,
					    omap24xx_cpu_suspend_sz);

	arm_pm_idle = omap2_pm_idle;

	वापस 0;
पूर्ण
