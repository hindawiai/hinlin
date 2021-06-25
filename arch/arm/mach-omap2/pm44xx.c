<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4+ Power Management Routines
 *
 * Copyright (C) 2010-2013 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "clockdomain.h"
#समावेश "powerdomain.h"
#समावेश "pm.h"

u16 pm44xx_errata;

काष्ठा घातer_state अणु
	काष्ठा घातerकरोमुख्य *pwrdm;
	u32 next_state;
	u32 next_logic_state;
#अगर_घोषित CONFIG_SUSPEND
	u32 saved_state;
	u32 saved_logic_state;
#पूर्ण_अगर
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा अटल_dep_map - Static dependency map
 * @from:	from घड़ीकरोमुख्य
 * @to:		to घड़ीकरोमुख्य
  */
काष्ठा अटल_dep_map अणु
	स्थिर अक्षर *from;
	स्थिर अक्षर *to;
पूर्ण;

अटल u32 cpu_suspend_state = PWRDM_POWER_OFF;

अटल LIST_HEAD(pwrst_list);

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक omap4_pm_suspend(व्योम)
अणु
	काष्ठा घातer_state *pwrst;
	पूर्णांक state, ret = 0;
	u32 cpu_id = smp_processor_id();

	/* Save current घातerकरोमुख्य state */
	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		pwrst->saved_state = pwrdm_पढ़ो_next_pwrst(pwrst->pwrdm);
		pwrst->saved_logic_state = pwrdm_पढ़ो_logic_retst(pwrst->pwrdm);
	पूर्ण

	/* Set targeted घातer करोमुख्य states by suspend */
	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		omap_set_pwrdm_state(pwrst->pwrdm, pwrst->next_state);
		pwrdm_set_logic_retst(pwrst->pwrdm, pwrst->next_logic_state);
	पूर्ण

	/*
	 * For MPUSS to hit घातer करोमुख्य retention(CSWR or OSWR),
	 * CPU0 and CPU1 घातer करोमुख्यs need to be in OFF or DORMANT state,
	 * since CPU घातer करोमुख्य CSWR is not supported by hardware
	 * Only master CPU follows suspend path. All other CPUs follow
	 * CPU hotplug path in प्रणाली wide suspend. On OMAP4, CPU घातer
	 * करोमुख्य CSWR is not supported by hardware.
	 * More details can be found in OMAP4430 TRM section 4.3.4.2.
	 */
	omap4_enter_lowघातer(cpu_id, cpu_suspend_state);

	/* Restore next घातerकरोमुख्य state */
	list_क्रम_each_entry(pwrst, &pwrst_list, node) अणु
		state = pwrdm_पढ़ो_prev_pwrst(pwrst->pwrdm);
		अगर (state > pwrst->next_state) अणु
			pr_info("Powerdomain (%s) didn't enter target state %d\n",
				pwrst->pwrdm->name, pwrst->next_state);
			ret = -1;
		पूर्ण
		omap_set_pwrdm_state(pwrst->pwrdm, pwrst->saved_state);
		pwrdm_set_logic_retst(pwrst->pwrdm, pwrst->saved_logic_state);
	पूर्ण
	अगर (ret) अणु
		pr_crit("Could not enter target state in pm_suspend\n");
		/*
		 * OMAP4 chip PM currently works only with certain (newer)
		 * versions of bootloaders. This is due to missing code in the
		 * kernel to properly reset and initialize some devices.
		 * Warn the user about the bootloader version being one of the
		 * possible causes.
		 * http://www.spinics.net/lists/arm-kernel/msg218641.hपंचांगl
		 */
		pr_warn("A possible cause could be an old bootloader - try u-boot >= v2012.07\n");
	पूर्ण अन्यथा अणु
		pr_info("Successfully put all powerdomains to target state\n");
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा omap4_pm_suspend शून्य
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल पूर्णांक __init pwrdms_setup(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	काष्ठा घातer_state *pwrst;

	अगर (!pwrdm->pwrsts)
		वापस 0;

	/*
	 * Skip CPU0 and CPU1 घातer करोमुख्यs. CPU1 is programmed
	 * through hotplug path and CPU0 explicitly programmed
	 * further करोwn in the code path
	 */
	अगर (!म_भेदन(pwrdm->name, "cpu", 3)) अणु
		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_CPU_OSWR_DISABLE))
			cpu_suspend_state = PWRDM_POWER_RET;
		वापस 0;
	पूर्ण

	अगर (!म_भेदन(pwrdm->name, "core", 4) ||
	    !म_भेदन(pwrdm->name, "l4per", 5))
		pwrdm_set_logic_retst(pwrdm, PWRDM_POWER_OFF);

	pwrst = kदो_स्मृति(माप(काष्ठा घातer_state), GFP_ATOMIC);
	अगर (!pwrst)
		वापस -ENOMEM;

	pwrst->pwrdm = pwrdm;
	pwrst->next_state = pwrdm_get_valid_lp_state(pwrdm, false,
						     PWRDM_POWER_RET);
	pwrst->next_logic_state = pwrdm_get_valid_lp_state(pwrdm, true,
							   PWRDM_POWER_OFF);

	list_add(&pwrst->node, &pwrst_list);

	वापस omap_set_pwrdm_state(pwrst->pwrdm, pwrst->next_state);
पूर्ण

/**
 * omap_शेष_idle - OMAP4 शेष ilde routine.'
 *
 * Implements OMAP4 memory, IO ordering requirements which can't be addressed
 * with शेष cpu_करो_idle() hook. Used by all CPUs with !CONFIG_CPU_IDLE and
 * by secondary CPU with CONFIG_CPU_IDLE.
 */
अटल व्योम omap_शेष_idle(व्योम)
अणु
	omap_करो_wfi();
पूर्ण

/*
 * The dynamic dependency between MPUSS -> MEMIF and
 * MPUSS -> L4_PER/L3_* and DUCATI -> L3_* करोesn't work as
 * expected. The hardware recommendation is to enable अटल
 * dependencies क्रम these to aव्योम प्रणाली lock ups or अक्रमom crashes.
 * The L4 wakeup depedency is added to workaround the OCP sync hardware
 * BUG with 32K synस_समयr which lead to incorrect समयr value पढ़ो
 * from the 32K counter. The BUG applies क्रम GPTIMER1 and WDT2 which
 * are part of L4 wakeup घड़ीकरोमुख्य.
 */
अटल स्थिर काष्ठा अटल_dep_map omap4_अटल_dep_map[] = अणु
	अणु.from = "mpuss_clkdm", .to = "l3_emif_clkdm"पूर्ण,
	अणु.from = "mpuss_clkdm", .to = "l3_1_clkdm"पूर्ण,
	अणु.from = "mpuss_clkdm", .to = "l3_2_clkdm"पूर्ण,
	अणु.from = "ducati_clkdm", .to = "l3_1_clkdm"पूर्ण,
	अणु.from = "ducati_clkdm", .to = "l3_2_clkdm"पूर्ण,
	अणु.from  = शून्यपूर्ण /* TERMINATION */
पूर्ण;

अटल स्थिर काष्ठा अटल_dep_map omap5_dra7_अटल_dep_map[] = अणु
	अणु.from = "mpu_clkdm", .to = "emif_clkdm"पूर्ण,
	अणु.from  = शून्यपूर्ण /* TERMINATION */
पूर्ण;

/**
 * omap4plus_init_अटल_deps() - Initialize a अटल dependency map
 * @map:	Mapping of घड़ी करोमुख्यs
 */
अटल अंतरभूत पूर्णांक omap4plus_init_अटल_deps(स्थिर काष्ठा अटल_dep_map *map)
अणु
	पूर्णांक ret;
	काष्ठा घड़ीकरोमुख्य *from, *to;

	अगर (!map)
		वापस 0;

	जबतक (map->from) अणु
		from = clkdm_lookup(map->from);
		to = clkdm_lookup(map->to);
		अगर (!from || !to) अणु
			pr_err("Failed lookup %s or %s for wakeup dependency\n",
			       map->from, map->to);
			वापस -EINVAL;
		पूर्ण
		ret = clkdm_add_wkdep(from, to);
		अगर (ret) अणु
			pr_err("Failed to add %s -> %s wakeup dependency(%d)\n",
			       map->from, map->to, ret);
			वापस ret;
		पूर्ण

		map++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap4_pm_init_early - Does early initialization necessary क्रम OMAP4+ devices
 *
 * Initializes basic stuff क्रम घातer management functionality.
 */
पूर्णांक __init omap4_pm_init_early(व्योम)
अणु
	अगर (cpu_is_omap446x())
		pm44xx_errata |= PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD;

	अगर (soc_is_omap54xx() || soc_is_dra7xx())
		pm44xx_errata |= PM_OMAP4_CPU_OSWR_DISABLE;

	वापस 0;
पूर्ण

/**
 * omap4_pm_init - Init routine क्रम OMAP4+ devices
 *
 * Initializes all घातerकरोमुख्य and घड़ीकरोमुख्य target states
 * and all PRCM settings.
 * Return: Returns the error code वापसed by called functions.
 */
पूर्णांक __init omap4_pm_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (omap_rev() == OMAP4430_REV_ES1_0) अणु
		WARN(1, "Power Management not supported on OMAP4430 ES1.0\n");
		वापस -ENODEV;
	पूर्ण

	pr_info("Power Management for TI OMAP4+ devices.\n");

	/*
	 * OMAP4 chip PM currently works only with certain (newer)
	 * versions of bootloaders. This is due to missing code in the
	 * kernel to properly reset and initialize some devices.
	 * http://www.spinics.net/lists/arm-kernel/msg218641.hपंचांगl
	 */
	अगर (cpu_is_omap44xx())
		pr_warn("OMAP4 PM: u-boot >= v2012.07 is required for full PM support\n");

	ret = pwrdm_क्रम_each(pwrdms_setup, शून्य);
	अगर (ret) अणु
		pr_err("Failed to setup powerdomains.\n");
		जाओ err2;
	पूर्ण

	अगर (cpu_is_omap44xx())
		ret = omap4plus_init_अटल_deps(omap4_अटल_dep_map);
	अन्यथा अगर (soc_is_omap54xx() || soc_is_dra7xx())
		ret = omap4plus_init_अटल_deps(omap5_dra7_अटल_dep_map);

	अगर (ret) अणु
		pr_err("Failed to initialise static dependencies.\n");
		जाओ err2;
	पूर्ण

	ret = omap4_mpuss_init();
	अगर (ret) अणु
		pr_err("Failed to initialise OMAP4 MPUSS\n");
		जाओ err2;
	पूर्ण

	(व्योम) clkdm_क्रम_each(omap_pm_clkdms_setup, शून्य);

	omap_common_suspend_init(omap4_pm_suspend);

	/* Overग_लिखो the शेष cpu_करो_idle() */
	arm_pm_idle = omap_शेष_idle;

	अगर (cpu_is_omap44xx() || soc_is_omap54xx())
		omap4_idle_init();

err2:
	वापस ret;
पूर्ण
