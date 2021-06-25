<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pm.c - Common OMAP2+ घातer management-related code
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "omap_device.h"
#समावेश "common.h"

#समावेश "soc.h"
#समावेश "prcm-common.h"
#समावेश "voltage.h"
#समावेश "powerdomain.h"
#समावेश "clockdomain.h"
#समावेश "pm.h"

u32 enable_off_mode;

#अगर_घोषित CONFIG_SUSPEND
/*
 * omap_pm_suspend: poपूर्णांकs to a function that करोes the SoC-specअगरic
 * suspend work
 */
अटल पूर्णांक (*omap_pm_suspend)(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
/**
 * काष्ठा omap2_oscillator - Describe the board मुख्य oscillator latencies
 * @startup_समय: oscillator startup latency
 * @shutकरोwn_समय: oscillator shutकरोwn latency
 */
काष्ठा omap2_oscillator अणु
	u32 startup_समय;
	u32 shutकरोwn_समय;
पूर्ण;

अटल काष्ठा omap2_oscillator oscillator = अणु
	.startup_समय = अच_दीर्घ_उच्च,
	.shutकरोwn_समय = अच_दीर्घ_उच्च,
पूर्ण;

व्योम omap_pm_setup_oscillator(u32 tstart, u32 tshut)
अणु
	oscillator.startup_समय = tstart;
	oscillator.shutकरोwn_समय = tshut;
पूर्ण

व्योम omap_pm_get_oscillator(u32 *tstart, u32 *tshut)
अणु
	अगर (!tstart || !tshut)
		वापस;

	*tstart = oscillator.startup_समय;
	*tshut = oscillator.shutकरोwn_समय;
पूर्ण
#पूर्ण_अगर

पूर्णांक omap_pm_clkdms_setup(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *unused)
अणु
	clkdm_allow_idle(clkdm);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक omap_pm_enter(suspend_state_t suspend_state)
अणु
	पूर्णांक ret = 0;

	अगर (!omap_pm_suspend)
		वापस -ENOENT; /* XXX द्विगुनcheck */

	चयन (suspend_state) अणु
	हाल PM_SUSPEND_MEM:
		ret = omap_pm_suspend();
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक omap_pm_begin(suspend_state_t state)
अणु
	cpu_idle_poll_ctrl(true);
	अगर (soc_is_omap34xx())
		omap_prcm_irq_prepare();
	वापस 0;
पूर्ण

अटल व्योम omap_pm_end(व्योम)
अणु
	cpu_idle_poll_ctrl(false);
पूर्ण

अटल व्योम omap_pm_wake(व्योम)
अणु
	अगर (soc_is_omap34xx())
		omap_prcm_irq_complete();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops omap_pm_ops = अणु
	.begin		= omap_pm_begin,
	.end		= omap_pm_end,
	.enter		= omap_pm_enter,
	.wake		= omap_pm_wake,
	.valid		= suspend_valid_only_mem,
पूर्ण;

/**
 * omap_common_suspend_init - Set common suspend routines क्रम OMAP SoCs
 * @pm_suspend: function poपूर्णांकer to SoC specअगरic suspend function
 */
व्योम omap_common_suspend_init(व्योम *pm_suspend)
अणु
	omap_pm_suspend = pm_suspend;
	suspend_set_ops(&omap_pm_ops);
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

पूर्णांक __maybe_unused omap_pm_nop_init(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक (*omap_pm_soc_init)(व्योम);

पूर्णांक __init omap2_common_pm_late_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!omap_pm_soc_init)
		वापस 0;

	/* Init the voltage layer */
	omap3_twl_init();
	omap4_twl_init();
	omap4_cpcap_init();
	omap_voltage_late_init();

	/* Smartreflex device init */
	omap_devinit_smartreflex();

	error = omap_pm_soc_init();
	अगर (error)
		pr_warn("%s: pm soc init failed: %i\n", __func__, error);

	omap2_clk_enable_स्वतःidle_all();

	वापस 0;
पूर्ण
omap_late_initcall(omap2_common_pm_late_init);
