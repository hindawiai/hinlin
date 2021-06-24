<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3 Power Management Routines
 *
 * Copyright (C) 2006-2008 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 * Jouni Hogander
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 *
 * Copyright (C) 2005 Texas Instruments, Inc.
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *
 * Based on pm.c क्रम omap1
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/omap-gpmc.h>

#समावेश <trace/events/घातer.h>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "clockdomain.h"
#समावेश "powerdomain.h"
#समावेश "soc.h"
#समावेश "common.h"
#समावेश "cm3xxx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "prm3xxx.h"
#समावेश "pm.h"
#समावेश "sdrc.h"
#समावेश "omap-secure.h"
#समावेश "sram.h"
#समावेश "control.h"
#समावेश "vc.h"

/* pm34xx errata defined in pm.h */
u16 pm34xx_errata;

काष्ठा घातer_state अणु
	काष्ठा घातerकरोमुख्य *pwrdm;
	u32 next_state;
#अगर_घोषित CONFIG_SUSPEND
	u32 saved_state;
#पूर्ण_अगर
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(pwrst_list);

व्योम (*omap3_करो_wfi_sram)(व्योम);

अटल काष्ठा घातerकरोमुख्य *mpu_pwrdm, *neon_pwrdm;
अटल काष्ठा घातerकरोमुख्य *core_pwrdm, *per_pwrdm;

अटल व्योम omap3_core_save_context(व्योम)
अणु
	omap3_ctrl_save_padconf();

	/*
	 * Force ग_लिखो last pad पूर्णांकo memory, as this can fail in some
	 * हालs according to errata 1.157, 1.185
	 */
	omap_ctrl_ग_लिखोl(omap_ctrl_पढ़ोl(OMAP343X_PADCONF_ETK_D14),
		OMAP343X_CONTROL_MEM_WKUP + 0x2a0);

	/* Save the Interrupt controller context */
	omap_पूर्णांकc_save_context();
	/* Save the GPMC context */
	omap3_gpmc_save_context();
	/* Save the प्रणाली control module context, padconf alपढ़ोy save above*/
	omap3_control_save_context();
पूर्ण

अटल व्योम omap3_core_restore_context(व्योम)
अणु
	/* Restore the control module context, padconf restored by h/w */
	omap3_control_restore_context();
	/* Restore the GPMC context */
	omap3_gpmc_restore_context();
	/* Restore the पूर्णांकerrupt controller context */
	omap_पूर्णांकc_restore_context();
पूर्ण

/*
 * FIXME: This function should be called beक्रमe entering off-mode after
 * OMAP3 secure services have been accessed. Currently it is only called
 * once during boot sequence, but this works as we are not using secure
 * services.
 */
अटल व्योम omap3_save_secure_ram_context(व्योम)
अणु
	u32 ret;
	पूर्णांक mpu_next_state = pwrdm_पढ़ो_next_pwrst(mpu_pwrdm);

	अगर (omap_type() != OMAP2_DEVICE_TYPE_GP) अणु
		/*
		 * MPU next state must be set to POWER_ON temporarily,
		 * otherwise the WFI executed inside the ROM code
		 * will hang the प्रणाली.
		 */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
		ret = omap3_save_secure_ram(omap3_secure_ram_storage,
					    OMAP3_SAVE_SECURE_RAM_SZ);
		pwrdm_set_next_pwrst(mpu_pwrdm, mpu_next_state);
		/* Following is क्रम error tracking, it should not happen */
		अगर (ret) अणु
			pr_err("save_secure_sram() returns %08x\n", ret);
			जबतक (1)
				;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t _prcm_पूर्णांक_handle_io(पूर्णांक irq, व्योम *unused)
अणु
	पूर्णांक c;

	c = omap_prm_clear_mod_irqs(WKUP_MOD, 1, OMAP3430_ST_IO_MASK |
				    OMAP3430_ST_IO_CHAIN_MASK);

	वापस c ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल irqवापस_t _prcm_पूर्णांक_handle_wakeup(पूर्णांक irq, व्योम *unused)
अणु
	पूर्णांक c;

	/*
	 * Clear all except ST_IO and ST_IO_CHAIN क्रम wkup module,
	 * these are handled in a separate handler to aव्योम acking
	 * IO events beक्रमe parsing in mux code
	 */
	c = omap_prm_clear_mod_irqs(WKUP_MOD, 1, ~(OMAP3430_ST_IO_MASK |
						   OMAP3430_ST_IO_CHAIN_MASK));
	c += omap_prm_clear_mod_irqs(CORE_MOD, 1, ~0);
	c += omap_prm_clear_mod_irqs(OMAP3430_PER_MOD, 1, ~0);
	अगर (omap_rev() > OMAP3430_REV_ES1_0) अणु
		c += omap_prm_clear_mod_irqs(CORE_MOD, 3, ~0);
		c += omap_prm_clear_mod_irqs(OMAP3430ES2_USBHOST_MOD, 1, ~0);
	पूर्ण

	वापस c ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम omap34xx_save_context(u32 *save)
अणु
	u32 val;

	/* Read Auxiliary Control Register */
	यंत्र("mrc p15, 0, %0, c1, c0, 1" : "=r" (val));
	*save++ = 1;
	*save++ = val;

	/* Read L2 AUX ctrl रेजिस्टर */
	यंत्र("mrc p15, 1, %0, c9, c0, 2" : "=r" (val));
	*save++ = 1;
	*save++ = val;
पूर्ण

अटल पूर्णांक omap34xx_करो_sram_idle(अचिन्हित दीर्घ save_state)
अणु
	omap34xx_cpu_suspend(save_state);
	वापस 0;
पूर्ण

व्योम omap_sram_idle(व्योम)
अणु
	/* Variable to tell what needs to be saved and restored
	 * in omap_sram_idle*/
	/* save_state = 0 => Nothing to save and restored */
	/* save_state = 1 => Only L1 and logic lost */
	/* save_state = 2 => Only L2 lost */
	/* save_state = 3 => L1, L2 and logic lost */
	पूर्णांक save_state = 0;
	पूर्णांक mpu_next_state = PWRDM_POWER_ON;
	पूर्णांक per_next_state = PWRDM_POWER_ON;
	पूर्णांक core_next_state = PWRDM_POWER_ON;
	u32 sdrc_pwr = 0;
	पूर्णांक error;

	mpu_next_state = pwrdm_पढ़ो_next_pwrst(mpu_pwrdm);
	चयन (mpu_next_state) अणु
	हाल PWRDM_POWER_ON:
	हाल PWRDM_POWER_RET:
		/* No need to save context */
		save_state = 0;
		अवरोध;
	हाल PWRDM_POWER_OFF:
		save_state = 3;
		अवरोध;
	शेष:
		/* Invalid state */
		pr_err("Invalid mpu state in sram_idle\n");
		वापस;
	पूर्ण

	/* NEON control */
	अगर (pwrdm_पढ़ो_pwrst(neon_pwrdm) == PWRDM_POWER_ON)
		pwrdm_set_next_pwrst(neon_pwrdm, mpu_next_state);

	/* Enable IO-PAD and IO-CHAIN wakeups */
	per_next_state = pwrdm_पढ़ो_next_pwrst(per_pwrdm);
	core_next_state = pwrdm_पढ़ो_next_pwrst(core_pwrdm);

	pwrdm_pre_transition(शून्य);

	/* PER */
	अगर (per_next_state == PWRDM_POWER_OFF) अणु
		error = cpu_cluster_pm_enter();
		अगर (error)
			वापस;
	पूर्ण

	/* CORE */
	अगर (core_next_state < PWRDM_POWER_ON) अणु
		अगर (core_next_state == PWRDM_POWER_OFF) अणु
			omap3_core_save_context();
			omap3_cm_save_context();
		पूर्ण
	पूर्ण

	/* Configure PMIC संकेतing क्रम I2C4 or sys_off_mode */
	omap3_vc_set_pmic_संकेतing(core_next_state);

	omap3_पूर्णांकc_prepare_idle();

	/*
	 * On EMU/HS devices ROM code restores a SRDC value
	 * from scratchpad which has स्वतःmatic self refresh on समयout
	 * of AUTO_CNT = 1 enabled. This takes care of erratum ID i443.
	 * Hence store/restore the SDRC_POWER रेजिस्टर here.
	 */
	अगर (cpu_is_omap3430() && omap_rev() >= OMAP3430_REV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    core_next_state == PWRDM_POWER_OFF)
		sdrc_pwr = sdrc_पढ़ो_reg(SDRC_POWER);

	/*
	 * omap3_arm_context is the location where some ARM context
	 * get saved. The rest is placed on the stack, and restored
	 * from there beक्रमe resuming.
	 */
	अगर (save_state)
		omap34xx_save_context(omap3_arm_context);
	अगर (save_state == 1 || save_state == 3)
		cpu_suspend(save_state, omap34xx_करो_sram_idle);
	अन्यथा
		omap34xx_करो_sram_idle(save_state);

	/* Restore normal SDRC POWER settings */
	अगर (cpu_is_omap3430() && omap_rev() >= OMAP3430_REV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    core_next_state == PWRDM_POWER_OFF)
		sdrc_ग_लिखो_reg(sdrc_pwr, SDRC_POWER);

	/* CORE */
	अगर (core_next_state < PWRDM_POWER_ON &&
	    pwrdm_पढ़ो_prev_pwrst(core_pwrdm) == PWRDM_POWER_OFF) अणु
		omap3_core_restore_context();
		omap3_cm_restore_context();
		omap3_sram_restore_context();
		omap2_sms_restore_context();
	पूर्ण अन्यथा अणु
		/*
		 * In off-mode resume path above, omap3_core_restore_context
		 * also handles the INTC स्वतःidle restore करोne here so limit
		 * this to non-off mode resume paths so we करोn't करो it twice.
		 */
		omap3_पूर्णांकc_resume_idle();
	पूर्ण

	pwrdm_post_transition(शून्य);

	/* PER */
	अगर (per_next_state == PWRDM_POWER_OFF)
		cpu_cluster_pm_निकास();
पूर्ण

अटल व्योम omap3_pm_idle(व्योम)
अणु
	अगर (omap_irq_pending())
		वापस;

	omap_sram_idle();
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक omap3_pm_suspend(व्योम)
अणु
	काष्ठा घातer_state *pwrst;
	पूर्णांक state, ret = 0;

	/* Read current next_pwrsts */
	list_क्रम_each_entry(pwrst, &pwrst_list, node)
		pwrst->saved_state = pwrdm_पढ़ो_next_pwrst(pwrst->pwrdm);
	/* Set ones wanted by suspend */
	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		अगर (omap_set_pwrdm_state(pwrst->pwrdm, pwrst->next_state))
			जाओ restore;
		अगर (pwrdm_clear_all_prev_pwrst(pwrst->pwrdm))
			जाओ restore;
	पूर्ण

	omap3_पूर्णांकc_suspend();

	omap_sram_idle();

restore:
	/* Restore next_pwrsts */
	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		state = pwrdm_पढ़ो_prev_pwrst(pwrst->pwrdm);
		अगर (state > pwrst->next_state) अणु
			pr_info("Powerdomain (%s) didn't enter target state %d\n",
				pwrst->pwrdm->name, pwrst->next_state);
			ret = -1;
		पूर्ण
		omap_set_pwrdm_state(pwrst->pwrdm, pwrst->saved_state);
	पूर्ण
	अगर (ret)
		pr_err("Could not enter target state in pm_suspend\n");
	अन्यथा
		pr_info("Successfully put all powerdomains to target state\n");

	वापस ret;
पूर्ण
#अन्यथा
#घोषणा omap3_pm_suspend शून्य
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल व्योम __init prcm_setup_regs(व्योम)
अणु
	omap3_ctrl_init();

	omap3_prm_init_pm(cpu_is_omap3630(), omap3_has_iva());
पूर्ण

व्योम omap3_pm_off_mode_enable(पूर्णांक enable)
अणु
	काष्ठा घातer_state *pwrst;
	u32 state;

	अगर (enable)
		state = PWRDM_POWER_OFF;
	अन्यथा
		state = PWRDM_POWER_RET;

	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		अगर (IS_PM34XX_ERRATUM(PM_SDRC_WAKEUP_ERRATUM_i583) &&
				pwrst->pwrdm == core_pwrdm &&
				state == PWRDM_POWER_OFF) अणु
			pwrst->next_state = PWRDM_POWER_RET;
			pr_warn("%s: Core OFF disabled due to errata i583\n",
				__func__);
		पूर्ण अन्यथा अणु
			pwrst->next_state = state;
		पूर्ण
		omap_set_pwrdm_state(pwrst->pwrdm, pwrst->next_state);
	पूर्ण
पूर्ण

पूर्णांक omap3_pm_get_suspend_state(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	काष्ठा घातer_state *pwrst;

	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		अगर (pwrst->pwrdm == pwrdm)
			वापस pwrst->next_state;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक omap3_pm_set_suspend_state(काष्ठा घातerकरोमुख्य *pwrdm, पूर्णांक state)
अणु
	काष्ठा घातer_state *pwrst;

	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		अगर (pwrst->pwrdm == pwrdm) अणु
			pwrst->next_state = state;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init pwrdms_setup(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	काष्ठा घातer_state *pwrst;

	अगर (!pwrdm->pwrsts)
		वापस 0;

	pwrst = kदो_स्मृति(माप(काष्ठा घातer_state), GFP_ATOMIC);
	अगर (!pwrst)
		वापस -ENOMEM;
	pwrst->pwrdm = pwrdm;

	अगर (enable_off_mode)
		pwrst->next_state = PWRDM_POWER_OFF;
	अन्यथा
		pwrst->next_state = PWRDM_POWER_RET;

	list_add(&pwrst->node, &pwrst_list);

	अगर (pwrdm_has_hdwr_sar(pwrdm))
		pwrdm_enable_hdwr_sar(pwrdm);

	वापस omap_set_pwrdm_state(pwrst->pwrdm, pwrst->next_state);
पूर्ण

/*
 * Push functions to SRAM
 *
 * The minimum set of functions is pushed to SRAM क्रम execution:
 * - omap3_करो_wfi क्रम erratum i581 WA,
 */
व्योम omap_push_sram_idle(व्योम)
अणु
	omap3_करो_wfi_sram = omap_sram_push(omap3_करो_wfi, omap3_करो_wfi_sz);
पूर्ण

अटल व्योम __init pm_errata_configure(व्योम)
अणु
	अगर (cpu_is_omap3630()) अणु
		pm34xx_errata |= PM_RTA_ERRATUM_i608;
		/* Enable the l2 cache toggling in sleep logic */
		enable_omap3630_toggle_l2_on_restore();
		अगर (omap_rev() < OMAP3630_REV_ES1_2)
			pm34xx_errata |= (PM_SDRC_WAKEUP_ERRATUM_i583 |
					  PM_PER_MEMORIES_ERRATUM_i582);
	पूर्ण अन्यथा अगर (cpu_is_omap34xx()) अणु
		pm34xx_errata |= PM_PER_MEMORIES_ERRATUM_i582;
	पूर्ण
पूर्ण

अटल व्योम __init omap3_pm_check_pmic(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "ti,twl4030-power-idle");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य, "ti,twl4030-power-idle-osc-off");

	अगर (np) अणु
		of_node_put(np);
		enable_off_mode = 1;
	पूर्ण अन्यथा अणु
		enable_off_mode = 0;
	पूर्ण
पूर्ण

पूर्णांक __init omap3_pm_init(व्योम)
अणु
	काष्ठा घातer_state *pwrst, *पंचांगp;
	काष्ठा घड़ीकरोमुख्य *neon_clkdm, *mpu_clkdm, *per_clkdm, *wkup_clkdm;
	पूर्णांक ret;

	अगर (!omap3_has_io_chain_ctrl())
		pr_warn("PM: no software I/O chain control; some wakeups may be lost\n");

	pm_errata_configure();

	/* XXX prcm_setup_regs needs to be beक्रमe enabling hw
	 * supervised mode क्रम घातerकरोमुख्यs */
	prcm_setup_regs();

	ret = request_irq(omap_prcm_event_to_irq("wkup"),
		_prcm_पूर्णांक_handle_wakeup, IRQF_NO_SUSPEND, "pm_wkup", शून्य);

	अगर (ret) अणु
		pr_err("pm: Failed to request pm_wkup irq\n");
		जाओ err1;
	पूर्ण

	/* IO पूर्णांकerrupt is shared with mux code */
	ret = request_irq(omap_prcm_event_to_irq("io"),
		_prcm_पूर्णांक_handle_io, IRQF_SHARED | IRQF_NO_SUSPEND, "pm_io",
		omap3_pm_init);

	अगर (ret) अणु
		pr_err("pm: Failed to request pm_io irq\n");
		जाओ err2;
	पूर्ण

	omap3_pm_check_pmic();

	ret = pwrdm_क्रम_each(pwrdms_setup, शून्य);
	अगर (ret) अणु
		pr_err("Failed to setup powerdomains\n");
		जाओ err3;
	पूर्ण

	(व्योम) clkdm_क्रम_each(omap_pm_clkdms_setup, शून्य);

	mpu_pwrdm = pwrdm_lookup("mpu_pwrdm");
	अगर (mpu_pwrdm == शून्य) अणु
		pr_err("Failed to get mpu_pwrdm\n");
		ret = -EINVAL;
		जाओ err3;
	पूर्ण

	neon_pwrdm = pwrdm_lookup("neon_pwrdm");
	per_pwrdm = pwrdm_lookup("per_pwrdm");
	core_pwrdm = pwrdm_lookup("core_pwrdm");

	neon_clkdm = clkdm_lookup("neon_clkdm");
	mpu_clkdm = clkdm_lookup("mpu_clkdm");
	per_clkdm = clkdm_lookup("per_clkdm");
	wkup_clkdm = clkdm_lookup("wkup_clkdm");

	omap_common_suspend_init(omap3_pm_suspend);

	arm_pm_idle = omap3_pm_idle;
	omap3_idle_init();

	/*
	 * RTA is disabled during initialization as per erratum i608
	 * it is safer to disable RTA by the bootloader, but we would like
	 * to be करोubly sure here and prevent any mishaps.
	 */
	अगर (IS_PM34XX_ERRATUM(PM_RTA_ERRATUM_i608))
		omap3630_ctrl_disable_rta();

	/*
	 * The UART3/4 FIFO and the sidetone memory in McBSP2/3 are
	 * not correctly reset when the PER घातerकरोमुख्य comes back
	 * from OFF or OSWR when the CORE घातerकरोमुख्य is kept active.
	 * See OMAP36xx Erratum i582 "PER Doमुख्य reset issue after
	 * Doमुख्य-OFF/OSWR Wakeup".  This wakeup dependency is not a
	 * complete workaround.  The kernel must also prevent the PER
	 * घातerकरोमुख्य from going to OSWR/OFF जबतक the CORE
	 * घातerकरोमुख्य is not going to OSWR/OFF.  And अगर PER last
	 * घातer state was off जबतक CORE last घातer state was ON, the
	 * UART3/4 and McBSP2/3 SIDETONE devices need to run a
	 * self-test using their loopback tests; अगर that fails, those
	 * devices are unusable until the PER/CORE can complete a transition
	 * from ON to OSWR/OFF and then back to ON.
	 *
	 * XXX Technically this workaround is only needed अगर off-mode
	 * or OSWR is enabled.
	 */
	अगर (IS_PM34XX_ERRATUM(PM_PER_MEMORIES_ERRATUM_i582))
		clkdm_add_wkdep(per_clkdm, wkup_clkdm);

	clkdm_add_wkdep(neon_clkdm, mpu_clkdm);
	अगर (omap_type() != OMAP2_DEVICE_TYPE_GP) अणु
		omap3_secure_ram_storage =
			kदो_स्मृति(OMAP3_SAVE_SECURE_RAM_SZ, GFP_KERNEL);
		अगर (!omap3_secure_ram_storage)
			pr_err("Memory allocation failed when allocating for secure sram context\n");

		local_irq_disable();

		omap3_save_secure_ram_context();

		local_irq_enable();
	पूर्ण

	omap3_save_scratchpad_contents();
	वापस ret;

err3:
	list_क्रम_each_entry_safe(pwrst, पंचांगp, &pwrst_list, node) अणु
		list_del(&pwrst->node);
		kमुक्त(pwrst);
	पूर्ण
	मुक्त_irq(omap_prcm_event_to_irq("io"), omap3_pm_init);
err2:
	मुक्त_irq(omap_prcm_event_to_irq("wkup"), शून्य);
err1:
	वापस ret;
पूर्ण
