<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AM33XX Arch Power Management Routines
 *
 * Copyright (C) 2016-2018 Texas Instruments Incorporated - https://www.ti.com/
 *	Dave Gerlach
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/platक्रमm_data/pm33xx.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/platक्रमm_data/gpio-omap.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/wkup_m3_ipc.h>
#समावेश <linux/of.h>
#समावेश <linux/rtc.h>

#समावेश "cm33xx.h"
#समावेश "common.h"
#समावेश "control.h"
#समावेश "clockdomain.h"
#समावेश "iomap.h"
#समावेश "pm.h"
#समावेश "powerdomain.h"
#समावेश "prm33xx.h"
#समावेश "soc.h"
#समावेश "sram.h"
#समावेश "omap-secure.h"

अटल काष्ठा घातerकरोमुख्य *cefuse_pwrdm, *gfx_pwrdm, *per_pwrdm, *mpu_pwrdm;
अटल काष्ठा घड़ीकरोमुख्य *gfx_l4ls_clkdm;
अटल व्योम __iomem *scu_base;

अटल पूर्णांक (*idle_fn)(u32 wfi_flags);

काष्ठा amx3_idle_state अणु
	पूर्णांक wfi_flags;
पूर्ण;

अटल काष्ठा amx3_idle_state *idle_states;

अटल पूर्णांक am43xx_map_scu(व्योम)
अणु
	scu_base = ioremap(scu_a9_get_base(), SZ_256);

	अगर (!scu_base)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_check_off_mode_enable(व्योम)
अणु
	अगर (enable_off_mode)
		pr_warn("WARNING: This platform does not support off-mode, entering DeepSleep suspend.\n");

	/* off mode not supported on am335x so वापस 0 always */
	वापस 0;
पूर्ण

अटल पूर्णांक am43xx_check_off_mode_enable(व्योम)
अणु
	/*
	 * Check क्रम am437x-gp-evm which has the right Hardware design to
	 * support this mode reliably.
	 */
	अगर (of_machine_is_compatible("ti,am437x-gp-evm") && enable_off_mode)
		वापस enable_off_mode;
	अन्यथा अगर (enable_off_mode)
		pr_warn("WARNING: This platform does not support off-mode, entering DeepSleep suspend.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक amx3_common_init(पूर्णांक (*idle)(u32 wfi_flags))
अणु
	gfx_pwrdm = pwrdm_lookup("gfx_pwrdm");
	per_pwrdm = pwrdm_lookup("per_pwrdm");
	mpu_pwrdm = pwrdm_lookup("mpu_pwrdm");

	अगर ((!gfx_pwrdm) || (!per_pwrdm) || (!mpu_pwrdm))
		वापस -ENODEV;

	(व्योम)clkdm_क्रम_each(omap_pm_clkdms_setup, शून्य);

	/* CEFUSE करोमुख्य can be turned off post bootup */
	cefuse_pwrdm = pwrdm_lookup("cefuse_pwrdm");
	अगर (!cefuse_pwrdm)
		pr_err("PM: Failed to get cefuse_pwrdm\n");
	अन्यथा अगर (omap_type() != OMAP2_DEVICE_TYPE_GP)
		pr_info("PM: Leaving EFUSE power domain active\n");
	अन्यथा
		omap_set_pwrdm_state(cefuse_pwrdm, PWRDM_POWER_OFF);

	idle_fn = idle;

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_suspend_init(पूर्णांक (*idle)(u32 wfi_flags))
अणु
	पूर्णांक ret;

	gfx_l4ls_clkdm = clkdm_lookup("gfx_l4ls_gfx_clkdm");

	अगर (!gfx_l4ls_clkdm) अणु
		pr_err("PM: Cannot lookup gfx_l4ls_clkdm clockdomains\n");
		वापस -ENODEV;
	पूर्ण

	ret = amx3_common_init(idle);

	वापस ret;
पूर्ण

अटल पूर्णांक am43xx_suspend_init(पूर्णांक (*idle)(u32 wfi_flags))
अणु
	पूर्णांक ret = 0;

	ret = am43xx_map_scu();
	अगर (ret) अणु
		pr_err("PM: Could not ioremap SCU\n");
		वापस ret;
	पूर्ण

	ret = amx3_common_init(idle);

	वापस ret;
पूर्ण

अटल पूर्णांक amx3_suspend_deinit(व्योम)
अणु
	idle_fn = शून्य;
	वापस 0;
पूर्ण

अटल व्योम amx3_pre_suspend_common(व्योम)
अणु
	omap_set_pwrdm_state(gfx_pwrdm, PWRDM_POWER_OFF);
पूर्ण

अटल व्योम amx3_post_suspend_common(व्योम)
अणु
	पूर्णांक status;
	/*
	 * Because gfx_pwrdm is the only one under MPU control,
	 * comment on transition status
	 */
	status = pwrdm_पढ़ो_pwrst(gfx_pwrdm);
	अगर (status != PWRDM_POWER_OFF)
		pr_err("PM: GFX domain did not transition: %x\n", status);
पूर्ण

अटल पूर्णांक am33xx_suspend(अचिन्हित पूर्णांक state, पूर्णांक (*fn)(अचिन्हित दीर्घ),
			  अचिन्हित दीर्घ args)
अणु
	पूर्णांक ret = 0;

	amx3_pre_suspend_common();
	ret = cpu_suspend(args, fn);
	amx3_post_suspend_common();

	/*
	 * BUG: GFX_L4LS घड़ी करोमुख्य needs to be woken up to
	 * ensure thet L4LS घड़ी करोमुख्य करोes not get stuck in
	 * transition. If that happens L3 module करोes not get
	 * disabled, thereby leading to PER घातer करोमुख्य
	 * transition failing
	 */

	clkdm_wakeup(gfx_l4ls_clkdm);
	clkdm_sleep(gfx_l4ls_clkdm);

	वापस ret;
पूर्ण

अटल पूर्णांक am43xx_suspend(अचिन्हित पूर्णांक state, पूर्णांक (*fn)(अचिन्हित दीर्घ),
			  अचिन्हित दीर्घ args)
अणु
	पूर्णांक ret = 0;

	/* Suspend secure side on HS devices */
	अगर (omap_type() != OMAP2_DEVICE_TYPE_GP) अणु
		अगर (optee_available)
			omap_smccc_smc(AM43xx_PPA_SVC_PM_SUSPEND, 0);
		अन्यथा
			omap_secure_dispatcher(AM43xx_PPA_SVC_PM_SUSPEND,
					       FLAG_START_CRITICAL,
					       0, 0, 0, 0, 0);
	पूर्ण

	amx3_pre_suspend_common();
	scu_घातer_mode(scu_base, SCU_PM_POWEROFF);
	ret = cpu_suspend(args, fn);
	scu_घातer_mode(scu_base, SCU_PM_NORMAL);

	अगर (!am43xx_check_off_mode_enable())
		amx3_post_suspend_common();

	/*
	 * Resume secure side on HS devices.
	 *
	 * Note that even on प्रणालीs with OP-TEE available this resume call is
	 * issued to the ROM. This is because upon waking from suspend the ROM
	 * is restored as the secure monitor. On प्रणालीs with OP-TEE ROM will
	 * restore OP-TEE during this call.
	 */
	अगर (omap_type() != OMAP2_DEVICE_TYPE_GP)
		omap_secure_dispatcher(AM43xx_PPA_SVC_PM_RESUME,
				       FLAG_START_CRITICAL,
				       0, 0, 0, 0, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक am33xx_cpu_suspend(पूर्णांक (*fn)(अचिन्हित दीर्घ), अचिन्हित दीर्घ args)
अणु
	पूर्णांक ret = 0;

	अगर (omap_irq_pending() || need_resched())
		वापस ret;

	ret = cpu_suspend(args, fn);

	वापस ret;
पूर्ण

अटल पूर्णांक am43xx_cpu_suspend(पूर्णांक (*fn)(अचिन्हित दीर्घ), अचिन्हित दीर्घ args)
अणु
	पूर्णांक ret = 0;

	अगर (!scu_base)
		वापस 0;

	scu_घातer_mode(scu_base, SCU_PM_DORMANT);
	ret = cpu_suspend(args, fn);
	scu_घातer_mode(scu_base, SCU_PM_NORMAL);

	वापस ret;
पूर्ण

अटल व्योम amx3_begin_suspend(व्योम)
अणु
	cpu_idle_poll_ctrl(true);
पूर्ण

अटल व्योम amx3_finish_suspend(व्योम)
अणु
	cpu_idle_poll_ctrl(false);
पूर्ण


अटल काष्ठा am33xx_pm_sram_addr *amx3_get_sram_addrs(व्योम)
अणु
	अगर (soc_is_am33xx())
		वापस &am33xx_pm_sram;
	अन्यथा अगर (soc_is_am437x())
		वापस &am43xx_pm_sram;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम am43xx_save_context(व्योम)
अणु
पूर्ण

अटल व्योम am33xx_save_context(व्योम)
अणु
	omap_पूर्णांकc_save_context();
पूर्ण

अटल व्योम am33xx_restore_context(व्योम)
अणु
	omap_पूर्णांकc_restore_context();
पूर्ण

अटल व्योम am43xx_restore_context(व्योम)
अणु
	/*
	 * HACK: restore dpll_per_clkdcolकरो रेजिस्टर contents, to aव्योम
	 * अवरोधing suspend-resume
	 */
	ग_लिखोl_relaxed(0x0, AM33XX_L4_WK_IO_ADDRESS(0x44df2e14));
पूर्ण

अटल काष्ठा am33xx_pm_platक्रमm_data am33xx_ops = अणु
	.init = am33xx_suspend_init,
	.deinit = amx3_suspend_deinit,
	.soc_suspend = am33xx_suspend,
	.cpu_suspend = am33xx_cpu_suspend,
	.begin_suspend = amx3_begin_suspend,
	.finish_suspend = amx3_finish_suspend,
	.get_sram_addrs = amx3_get_sram_addrs,
	.save_context = am33xx_save_context,
	.restore_context = am33xx_restore_context,
	.check_off_mode_enable = am33xx_check_off_mode_enable,
पूर्ण;

अटल काष्ठा am33xx_pm_platक्रमm_data am43xx_ops = अणु
	.init = am43xx_suspend_init,
	.deinit = amx3_suspend_deinit,
	.soc_suspend = am43xx_suspend,
	.cpu_suspend = am43xx_cpu_suspend,
	.begin_suspend = amx3_begin_suspend,
	.finish_suspend = amx3_finish_suspend,
	.get_sram_addrs = amx3_get_sram_addrs,
	.save_context = am43xx_save_context,
	.restore_context = am43xx_restore_context,
	.check_off_mode_enable = am43xx_check_off_mode_enable,
पूर्ण;

अटल काष्ठा am33xx_pm_platक्रमm_data *am33xx_pm_get_pdata(व्योम)
अणु
	अगर (soc_is_am33xx())
		वापस &am33xx_ops;
	अन्यथा अगर (soc_is_am437x())
		वापस &am43xx_ops;
	अन्यथा
		वापस शून्य;
पूर्ण

पूर्णांक __init amx3_common_pm_init(व्योम)
अणु
	काष्ठा am33xx_pm_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device_info devinfo;

	pdata = am33xx_pm_get_pdata();

	स_रखो(&devinfo, 0, माप(devinfo));
	devinfo.name = "pm33xx";
	devinfo.data = pdata;
	devinfo.size_data = माप(*pdata);
	devinfo.id = -1;
	platक्रमm_device_रेजिस्टर_full(&devinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक __init amx3_idle_init(काष्ठा device_node *cpu_node, पूर्णांक cpu)
अणु
	काष्ठा device_node *state_node;
	काष्ठा amx3_idle_state states[CPUIDLE_STATE_MAX];
	पूर्णांक i;
	पूर्णांक state_count = 1;

	क्रम (i = 0; ; i++) अणु
		state_node = of_parse_phandle(cpu_node, "cpu-idle-states", i);
		अगर (!state_node)
			अवरोध;

		अगर (!of_device_is_available(state_node))
			जारी;

		अगर (i == CPUIDLE_STATE_MAX) अणु
			pr_warn("%s: cpuidle states reached max possible\n",
				__func__);
			अवरोध;
		पूर्ण

		states[state_count].wfi_flags = 0;

		अगर (of_property_पढ़ो_bool(state_node, "ti,idle-wkup-m3"))
			states[state_count].wfi_flags |= WFI_FLAG_WAKE_M3 |
							 WFI_FLAG_FLUSH_CACHE;

		state_count++;
	पूर्ण

	idle_states = kसुस्मृति(state_count, माप(*idle_states), GFP_KERNEL);
	अगर (!idle_states)
		वापस -ENOMEM;

	क्रम (i = 1; i < state_count; i++)
		idle_states[i].wfi_flags = states[i].wfi_flags;

	वापस 0;
पूर्ण

अटल पूर्णांक amx3_idle_enter(अचिन्हित दीर्घ index)
अणु
	काष्ठा amx3_idle_state *idle_state = &idle_states[index];

	अगर (!idle_state)
		वापस -EINVAL;

	अगर (idle_fn)
		idle_fn(idle_state->wfi_flags);

	वापस 0;
पूर्ण

अटल काष्ठा cpuidle_ops amx3_cpuidle_ops __initdata = अणु
	.init = amx3_idle_init,
	.suspend = amx3_idle_enter,
पूर्ण;

CPUIDLE_METHOD_OF_DECLARE(pm33xx_idle, "ti,am3352", &amx3_cpuidle_ops);
CPUIDLE_METHOD_OF_DECLARE(pm43xx_idle, "ti,am4372", &amx3_cpuidle_ops);
