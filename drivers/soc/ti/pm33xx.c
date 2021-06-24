<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AM33XX Power Management Routines
 *
 * Copyright (C) 2012-2018 Texas Instruments Incorporated - http://www.ti.com/
 *	Vaibhav Bedia, Dave Gerlach
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_data/pm33xx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/rtc/rtc-omap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/sram.h>
#समावेश <linux/suspend.h>
#समावेश <linux/ti-emअगर-sram.h>
#समावेश <linux/wkup_m3_ipc.h>

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#घोषणा AMX3_PM_SRAM_SYMBOL_OFFSET(sym) ((अचिन्हित दीर्घ)(sym) - \
					 (अचिन्हित दीर्घ)pm_sram->करो_wfi)

#घोषणा RTC_SCRATCH_RESUME_REG	0
#घोषणा RTC_SCRATCH_MAGIC_REG	1
#घोषणा RTC_REG_BOOT_MAGIC	0x8cd0 /* RTC */
#घोषणा GIC_INT_SET_PENDING_BASE 0x200
#घोषणा AM43XX_GIC_DIST_BASE	0x48241000

अटल व्योम __iomem *rtc_base_virt;
अटल काष्ठा clk *rtc_fck;
अटल u32 rtc_magic_val;

अटल पूर्णांक (*am33xx_करो_wfi_sram)(अचिन्हित दीर्घ unused);
अटल phys_addr_t am33xx_करो_wfi_sram_phys;

अटल काष्ठा gen_pool *sram_pool, *sram_pool_data;
अटल अचिन्हित दीर्घ ocmcram_location, ocmcram_location_data;

अटल काष्ठा rtc_device *omap_rtc;
अटल व्योम __iomem *gic_dist_base;

अटल काष्ठा am33xx_pm_platक्रमm_data *pm_ops;
अटल काष्ठा am33xx_pm_sram_addr *pm_sram;

अटल काष्ठा device *pm33xx_dev;
अटल काष्ठा wkup_m3_ipc *m3_ipc;

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक rtc_only_idle;
अटल पूर्णांक retrigger_irq;
अटल अचिन्हित दीर्घ suspend_wfi_flags;

अटल काष्ठा wkup_m3_wakeup_src wakeup_src = अणु.irq_nr = 0,
	.src = "Unknown",
पूर्ण;

अटल काष्ठा wkup_m3_wakeup_src rtc_alarm_wakeup = अणु
	.irq_nr = 108, .src = "RTC Alarm",
पूर्ण;

अटल काष्ठा wkup_m3_wakeup_src rtc_ext_wakeup = अणु
	.irq_nr = 0, .src = "Ext wakeup",
पूर्ण;
#पूर्ण_अगर

अटल u32 sram_suspend_address(अचिन्हित दीर्घ addr)
अणु
	वापस ((अचिन्हित दीर्घ)am33xx_करो_wfi_sram +
		AMX3_PM_SRAM_SYMBOL_OFFSET(addr));
पूर्ण

अटल पूर्णांक am33xx_push_sram_idle(व्योम)
अणु
	काष्ठा am33xx_pm_ro_sram_data ro_sram_data;
	पूर्णांक ret;
	u32 table_addr, ro_data_addr;
	व्योम *copy_addr;

	ro_sram_data.amx3_pm_sram_data_virt = ocmcram_location_data;
	ro_sram_data.amx3_pm_sram_data_phys =
		gen_pool_virt_to_phys(sram_pool_data, ocmcram_location_data);
	ro_sram_data.rtc_base_virt = rtc_base_virt;

	/* Save physical address to calculate resume offset during pm init */
	am33xx_करो_wfi_sram_phys = gen_pool_virt_to_phys(sram_pool,
							ocmcram_location);

	am33xx_करो_wfi_sram = sram_exec_copy(sram_pool, (व्योम *)ocmcram_location,
					    pm_sram->करो_wfi,
					    *pm_sram->करो_wfi_sz);
	अगर (!am33xx_करो_wfi_sram) अणु
		dev_err(pm33xx_dev,
			"PM: %s: am33xx_do_wfi copy to sram failed\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	table_addr =
		sram_suspend_address((अचिन्हित दीर्घ)pm_sram->emअगर_sram_table);
	ret = ti_emअगर_copy_pm_function_table(sram_pool, (व्योम *)table_addr);
	अगर (ret) अणु
		dev_dbg(pm33xx_dev,
			"PM: %s: EMIF function copy failed\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	ro_data_addr =
		sram_suspend_address((अचिन्हित दीर्घ)pm_sram->ro_sram_data);
	copy_addr = sram_exec_copy(sram_pool, (व्योम *)ro_data_addr,
				   &ro_sram_data,
				   माप(ro_sram_data));
	अगर (!copy_addr) अणु
		dev_err(pm33xx_dev,
			"PM: %s: ro_sram_data copy to sram failed\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_करो_sram_idle(u32 wfi_flags)
अणु
	अगर (!m3_ipc || !pm_ops)
		वापस 0;

	अगर (wfi_flags & WFI_FLAG_WAKE_M3)
		m3_ipc->ops->prepare_low_घातer(m3_ipc, WKUP_M3_IDLE);

	वापस pm_ops->cpu_suspend(am33xx_करो_wfi_sram, wfi_flags);
पूर्ण

अटल पूर्णांक __init am43xx_map_gic(व्योम)
अणु
	gic_dist_base = ioremap(AM43XX_GIC_DIST_BASE, SZ_4K);

	अगर (!gic_dist_base)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल काष्ठा wkup_m3_wakeup_src rtc_wake_src(व्योम)
अणु
	u32 i;

	i = __raw_पढ़ोl(rtc_base_virt + 0x44) & 0x40;

	अगर (i) अणु
		retrigger_irq = rtc_alarm_wakeup.irq_nr;
		वापस rtc_alarm_wakeup;
	पूर्ण

	retrigger_irq = rtc_ext_wakeup.irq_nr;

	वापस rtc_ext_wakeup;
पूर्ण

अटल पूर्णांक am33xx_rtc_only_idle(अचिन्हित दीर्घ wfi_flags)
अणु
	omap_rtc_घातer_off_program(&omap_rtc->dev);
	am33xx_करो_wfi_sram(wfi_flags);
	वापस 0;
पूर्ण

/*
 * Note that the RTC module घड़ी must be re-enabled only क्रम rtc+ddr suspend.
 * And looks like the module can stay in SYSC_IDLE_SMART_WKUP mode configured
 * by the पूर्णांकerconnect code just fine क्रम both rtc+ddr suspend and retention
 * suspend.
 */
अटल पूर्णांक am33xx_pm_suspend(suspend_state_t suspend_state)
अणु
	पूर्णांक i, ret = 0;

	अगर (suspend_state == PM_SUSPEND_MEM &&
	    pm_ops->check_off_mode_enable()) अणु
		ret = clk_prepare_enable(rtc_fck);
		अगर (ret) अणु
			dev_err(pm33xx_dev, "Failed to enable clock: %i\n", ret);
			वापस ret;
		पूर्ण

		pm_ops->save_context();
		suspend_wfi_flags |= WFI_FLAG_RTC_ONLY;
		clk_save_context();
		ret = pm_ops->soc_suspend(suspend_state, am33xx_rtc_only_idle,
					  suspend_wfi_flags);

		suspend_wfi_flags &= ~WFI_FLAG_RTC_ONLY;
		dev_info(pm33xx_dev, "Entering RTC Only mode with DDR in self-refresh\n");

		अगर (!ret) अणु
			clk_restore_context();
			pm_ops->restore_context();
			m3_ipc->ops->set_rtc_only(m3_ipc);
			am33xx_push_sram_idle();
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pm_ops->soc_suspend(suspend_state, am33xx_करो_wfi_sram,
					  suspend_wfi_flags);
	पूर्ण

	अगर (ret) अणु
		dev_err(pm33xx_dev, "PM: Kernel suspend failure\n");
	पूर्ण अन्यथा अणु
		i = m3_ipc->ops->request_pm_status(m3_ipc);

		चयन (i) अणु
		हाल 0:
			dev_info(pm33xx_dev,
				 "PM: Successfully put all powerdomains to target state\n");
			अवरोध;
		हाल 1:
			dev_err(pm33xx_dev,
				"PM: Could not transition all powerdomains to target state\n");
			ret = -1;
			अवरोध;
		शेष:
			dev_err(pm33xx_dev,
				"PM: CM3 returned unknown result = %d\n", i);
			ret = -1;
		पूर्ण

		/* prपूर्णांक the wakeup reason */
		अगर (rtc_only_idle) अणु
			wakeup_src = rtc_wake_src();
			pr_info("PM: Wakeup source %s\n", wakeup_src.src);
		पूर्ण अन्यथा अणु
			pr_info("PM: Wakeup source %s\n",
				m3_ipc->ops->request_wake_src(m3_ipc));
		पूर्ण
	पूर्ण

	अगर (suspend_state == PM_SUSPEND_MEM && pm_ops->check_off_mode_enable())
		clk_disable_unprepare(rtc_fck);

	वापस ret;
पूर्ण

अटल पूर्णांक am33xx_pm_enter(suspend_state_t suspend_state)
अणु
	पूर्णांक ret = 0;

	चयन (suspend_state) अणु
	हाल PM_SUSPEND_MEM:
	हाल PM_SUSPEND_STANDBY:
		ret = am33xx_pm_suspend(suspend_state);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक am33xx_pm_begin(suspend_state_t state)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा nvmem_device *nvmem;

	अगर (state == PM_SUSPEND_MEM && pm_ops->check_off_mode_enable()) अणु
		nvmem = devm_nvmem_device_get(&omap_rtc->dev,
					      "omap_rtc_scratch0");
		अगर (!IS_ERR(nvmem))
			nvmem_device_ग_लिखो(nvmem, RTC_SCRATCH_MAGIC_REG * 4, 4,
					   (व्योम *)&rtc_magic_val);
		rtc_only_idle = 1;
	पूर्ण अन्यथा अणु
		rtc_only_idle = 0;
	पूर्ण

	pm_ops->begin_suspend();

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		ret = m3_ipc->ops->prepare_low_घातer(m3_ipc, WKUP_M3_DEEPSLEEP);
		अवरोध;
	हाल PM_SUSPEND_STANDBY:
		ret = m3_ipc->ops->prepare_low_घातer(m3_ipc, WKUP_M3_STANDBY);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम am33xx_pm_end(व्योम)
अणु
	u32 val = 0;
	काष्ठा nvmem_device *nvmem;

	nvmem = devm_nvmem_device_get(&omap_rtc->dev, "omap_rtc_scratch0");
	अगर (IS_ERR(nvmem))
		वापस;

	m3_ipc->ops->finish_low_घातer(m3_ipc);
	अगर (rtc_only_idle) अणु
		अगर (retrigger_irq) अणु
			/*
			 * 32 bits of Interrupt Set-Pending correspond to 32
			 * 32 पूर्णांकerrupts. Compute the bit offset of the
			 * Interrupt and set that particular bit
			 * Compute the रेजिस्टर offset by भागiding पूर्णांकerrupt
			 * number by 32 and mutiplying by 4
			 */
			ग_लिखोl_relaxed(1 << (retrigger_irq & 31),
				       gic_dist_base + GIC_INT_SET_PENDING_BASE
				       + retrigger_irq / 32 * 4);
		पूर्ण

		nvmem_device_ग_लिखो(nvmem, RTC_SCRATCH_MAGIC_REG * 4, 4,
				   (व्योम *)&val);
	पूर्ण

	rtc_only_idle = 0;

	pm_ops->finish_suspend();
पूर्ण

अटल पूर्णांक am33xx_pm_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
	हाल PM_SUSPEND_MEM:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops am33xx_pm_ops = अणु
	.begin		= am33xx_pm_begin,
	.end		= am33xx_pm_end,
	.enter		= am33xx_pm_enter,
	.valid		= am33xx_pm_valid,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल व्योम am33xx_pm_set_ipc_ops(व्योम)
अणु
	u32 resume_address;
	पूर्णांक temp;

	temp = ti_emअगर_get_mem_type();
	अगर (temp < 0) अणु
		dev_err(pm33xx_dev, "PM: Cannot determine memory type, no PM available\n");
		वापस;
	पूर्ण
	m3_ipc->ops->set_mem_type(m3_ipc, temp);

	/* Physical resume address to be used by ROM code */
	resume_address = am33xx_करो_wfi_sram_phys +
			 *pm_sram->resume_offset + 0x4;

	m3_ipc->ops->set_resume_address(m3_ipc, (व्योम *)resume_address);
पूर्ण

अटल व्योम am33xx_pm_मुक्त_sram(व्योम)
अणु
	gen_pool_मुक्त(sram_pool, ocmcram_location, *pm_sram->करो_wfi_sz);
	gen_pool_मुक्त(sram_pool_data, ocmcram_location_data,
		      माप(काष्ठा am33xx_pm_ro_sram_data));
पूर्ण

/*
 * Push the minimal suspend-resume code to SRAM
 */
अटल पूर्णांक am33xx_pm_alloc_sram(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "ti,omap3-mpu");
	अगर (!np) अणु
		np = of_find_compatible_node(शून्य, शून्य, "ti,omap4-mpu");
		अगर (!np) अणु
			dev_err(pm33xx_dev, "PM: %s: Unable to find device node for mpu\n",
				__func__);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	sram_pool = of_gen_pool_get(np, "pm-sram", 0);
	अगर (!sram_pool) अणु
		dev_err(pm33xx_dev, "PM: %s: Unable to get sram pool for ocmcram\n",
			__func__);
		ret = -ENODEV;
		जाओ mpu_put_node;
	पूर्ण

	sram_pool_data = of_gen_pool_get(np, "pm-sram", 1);
	अगर (!sram_pool_data) अणु
		dev_err(pm33xx_dev, "PM: %s: Unable to get sram data pool for ocmcram\n",
			__func__);
		ret = -ENODEV;
		जाओ mpu_put_node;
	पूर्ण

	ocmcram_location = gen_pool_alloc(sram_pool, *pm_sram->करो_wfi_sz);
	अगर (!ocmcram_location) अणु
		dev_err(pm33xx_dev, "PM: %s: Unable to allocate memory from ocmcram\n",
			__func__);
		ret = -ENOMEM;
		जाओ mpu_put_node;
	पूर्ण

	ocmcram_location_data = gen_pool_alloc(sram_pool_data,
					       माप(काष्ठा emअगर_regs_amx3));
	अगर (!ocmcram_location_data) अणु
		dev_err(pm33xx_dev, "PM: Unable to allocate memory from ocmcram\n");
		gen_pool_मुक्त(sram_pool, ocmcram_location, *pm_sram->करो_wfi_sz);
		ret = -ENOMEM;
	पूर्ण

mpu_put_node:
	of_node_put(np);
	वापस ret;
पूर्ण

अटल पूर्णांक am33xx_pm_rtc_setup(व्योम)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ val = 0;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक error;

	np = of_find_node_by_name(शून्य, "rtc");

	अगर (of_device_is_available(np)) अणु
		/* RTC पूर्णांकerconnect target module घड़ी */
		rtc_fck = of_clk_get_by_name(np->parent, "fck");
		अगर (IS_ERR(rtc_fck))
			वापस PTR_ERR(rtc_fck);

		rtc_base_virt = of_iomap(np, 0);
		अगर (!rtc_base_virt) अणु
			pr_warn("PM: could not iomap rtc");
			error = -ENODEV;
			जाओ err_clk_put;
		पूर्ण

		omap_rtc = rtc_class_खोलो("rtc0");
		अगर (!omap_rtc) अणु
			pr_warn("PM: rtc0 not available");
			error = -EPROBE_DEFER;
			जाओ err_iounmap;
		पूर्ण

		nvmem = devm_nvmem_device_get(&omap_rtc->dev,
					      "omap_rtc_scratch0");
		अगर (!IS_ERR(nvmem)) अणु
			nvmem_device_पढ़ो(nvmem, RTC_SCRATCH_MAGIC_REG * 4,
					  4, (व्योम *)&rtc_magic_val);
			अगर ((rtc_magic_val & 0xffff) != RTC_REG_BOOT_MAGIC)
				pr_warn("PM: bootloader does not support rtc-only!\n");

			nvmem_device_ग_लिखो(nvmem, RTC_SCRATCH_MAGIC_REG * 4,
					   4, (व्योम *)&val);
			val = pm_sram->resume_address;
			nvmem_device_ग_लिखो(nvmem, RTC_SCRATCH_RESUME_REG * 4,
					   4, (व्योम *)&val);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("PM: no-rtc available, rtc-only mode disabled.\n");
	पूर्ण

	वापस 0;

err_iounmap:
	iounmap(rtc_base_virt);
err_clk_put:
	clk_put(rtc_fck);

	वापस error;
पूर्ण

अटल पूर्णांक am33xx_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	अगर (!of_machine_is_compatible("ti,am33xx") &&
	    !of_machine_is_compatible("ti,am43"))
		वापस -ENODEV;

	pm_ops = dev->platक्रमm_data;
	अगर (!pm_ops) अणु
		dev_err(dev, "PM: Cannot get core PM ops!\n");
		वापस -ENODEV;
	पूर्ण

	ret = am43xx_map_gic();
	अगर (ret) अणु
		pr_err("PM: Could not ioremap GIC base\n");
		वापस ret;
	पूर्ण

	pm_sram = pm_ops->get_sram_addrs();
	अगर (!pm_sram) अणु
		dev_err(dev, "PM: Cannot get PM asm function addresses!!\n");
		वापस -ENODEV;
	पूर्ण

	m3_ipc = wkup_m3_ipc_get();
	अगर (!m3_ipc) अणु
		pr_err("PM: Cannot get wkup_m3_ipc handle\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	pm33xx_dev = dev;

	ret = am33xx_pm_alloc_sram();
	अगर (ret)
		वापस ret;

	ret = am33xx_pm_rtc_setup();
	अगर (ret)
		जाओ err_मुक्त_sram;

	ret = am33xx_push_sram_idle();
	अगर (ret)
		जाओ err_unsetup_rtc;

	am33xx_pm_set_ipc_ops();

#अगर_घोषित CONFIG_SUSPEND
	suspend_set_ops(&am33xx_pm_ops);

	/*
	 * For a प्रणाली suspend we must flush the caches, we want
	 * the DDR in self-refresh, we want to save the context
	 * of the EMIF, and we want the wkup_m3 to handle low-घातer
	 * transition.
	 */
	suspend_wfi_flags |= WFI_FLAG_FLUSH_CACHE;
	suspend_wfi_flags |= WFI_FLAG_SELF_REFRESH;
	suspend_wfi_flags |= WFI_FLAG_SAVE_EMIF;
	suspend_wfi_flags |= WFI_FLAG_WAKE_M3;
#पूर्ण_अगर /* CONFIG_SUSPEND */

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ err_pm_runसमय_disable;
	पूर्ण

	ret = pm_ops->init(am33xx_करो_sram_idle);
	अगर (ret) अणु
		dev_err(dev, "Unable to call core pm init!\n");
		ret = -ENODEV;
		जाओ err_pm_runसमय_put;
	पूर्ण

	वापस 0;

err_pm_runसमय_put:
	pm_runसमय_put_sync(dev);
err_pm_runसमय_disable:
	pm_runसमय_disable(dev);
	wkup_m3_ipc_put(m3_ipc);
err_unsetup_rtc:
	iounmap(rtc_base_virt);
	clk_put(rtc_fck);
err_मुक्त_sram:
	am33xx_pm_मुक्त_sram();
	pm33xx_dev = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक am33xx_pm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	अगर (pm_ops->deinit)
		pm_ops->deinit();
	suspend_set_ops(शून्य);
	wkup_m3_ipc_put(m3_ipc);
	am33xx_pm_मुक्त_sram();
	iounmap(rtc_base_virt);
	clk_put(rtc_fck);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver am33xx_pm_driver = अणु
	.driver = अणु
		.name   = "pm33xx",
	पूर्ण,
	.probe = am33xx_pm_probe,
	.हटाओ = am33xx_pm_हटाओ,
पूर्ण;
module_platक्रमm_driver(am33xx_pm_driver);

MODULE_ALIAS("platform:pm33xx");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("am33xx power management driver");
