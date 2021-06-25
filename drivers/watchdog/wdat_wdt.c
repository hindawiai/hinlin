<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI Hardware Watchकरोg (WDAT) driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/watchकरोg.h>

#घोषणा MAX_WDAT_ACTIONS ACPI_WDAT_ACTION_RESERVED

/**
 * काष्ठा wdat_inकाष्ठाion - Single ACPI WDAT inकाष्ठाion
 * @entry: Copy of the ACPI table inकाष्ठाion
 * @reg: Register the inकाष्ठाion is accessing
 * @node: Next inकाष्ठाion in action sequence
 */
काष्ठा wdat_inकाष्ठाion अणु
	काष्ठा acpi_wdat_entry entry;
	व्योम __iomem *reg;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा wdat_wdt - ACPI WDAT watchकरोg device
 * @pdev: Parent platक्रमm device
 * @wdd: Watchकरोg core device
 * @period: How दीर्घ is one watchकरोg period in ms
 * @stopped_in_sleep: Is this watchकरोg stopped by the firmware in S1-S5
 * @stopped: Was the watchकरोg stopped by the driver in suspend
 * @inकाष्ठाions: An array of inकाष्ठाion lists indexed by an action number from
 *                the WDAT table. There can be %शून्य entries क्रम not implemented
 *                actions.
 */
काष्ठा wdat_wdt अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा watchकरोg_device wdd;
	अचिन्हित पूर्णांक period;
	bool stopped_in_sleep;
	bool stopped;
	काष्ठा list_head *inकाष्ठाions[MAX_WDAT_ACTIONS];
पूर्ण;

#घोषणा to_wdat_wdt(wdd) container_of(wdd, काष्ठा wdat_wdt, wdd)

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा WDAT_DEFAULT_TIMEOUT	30

अटल पूर्णांक समयout = WDAT_DEFAULT_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds (default="
		 __MODULE_STRING(WDAT_DEFAULT_TIMEOUT) ")");

अटल पूर्णांक wdat_wdt_पढ़ो(काष्ठा wdat_wdt *wdat,
	 स्थिर काष्ठा wdat_inकाष्ठाion *instr, u32 *value)
अणु
	स्थिर काष्ठा acpi_generic_address *gas = &instr->entry.रेजिस्टर_region;

	चयन (gas->access_width) अणु
	हाल 1:
		*value = ioपढ़ो8(instr->reg);
		अवरोध;
	हाल 2:
		*value = ioपढ़ो16(instr->reg);
		अवरोध;
	हाल 3:
		*value = ioपढ़ो32(instr->reg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&wdat->pdev->dev, "Read %#x from 0x%08llx\n", *value,
		gas->address);

	वापस 0;
पूर्ण

अटल पूर्णांक wdat_wdt_ग_लिखो(काष्ठा wdat_wdt *wdat,
	स्थिर काष्ठा wdat_inकाष्ठाion *instr, u32 value)
अणु
	स्थिर काष्ठा acpi_generic_address *gas = &instr->entry.रेजिस्टर_region;

	चयन (gas->access_width) अणु
	हाल 1:
		ioग_लिखो8((u8)value, instr->reg);
		अवरोध;
	हाल 2:
		ioग_लिखो16((u16)value, instr->reg);
		अवरोध;
	हाल 3:
		ioग_लिखो32(value, instr->reg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&wdat->pdev->dev, "Wrote %#x to 0x%08llx\n", value,
		gas->address);

	वापस 0;
पूर्ण

अटल पूर्णांक wdat_wdt_run_action(काष्ठा wdat_wdt *wdat, अचिन्हित पूर्णांक action,
			       u32 param, u32 *retval)
अणु
	काष्ठा wdat_inकाष्ठाion *instr;

	अगर (action >= ARRAY_SIZE(wdat->inकाष्ठाions))
		वापस -EINVAL;

	अगर (!wdat->inकाष्ठाions[action])
		वापस -EOPNOTSUPP;

	dev_dbg(&wdat->pdev->dev, "Running action %#x\n", action);

	/* Run each inकाष्ठाion sequentially */
	list_क्रम_each_entry(instr, wdat->inकाष्ठाions[action], node) अणु
		स्थिर काष्ठा acpi_wdat_entry *entry = &instr->entry;
		स्थिर काष्ठा acpi_generic_address *gas;
		u32 flags, value, mask, x, y;
		bool preserve;
		पूर्णांक ret;

		gas = &entry->रेजिस्टर_region;

		preserve = entry->inकाष्ठाion & ACPI_WDAT_PRESERVE_REGISTER;
		flags = entry->inकाष्ठाion & ~ACPI_WDAT_PRESERVE_REGISTER;
		value = entry->value;
		mask = entry->mask;

		चयन (flags) अणु
		हाल ACPI_WDAT_READ_VALUE:
			ret = wdat_wdt_पढ़ो(wdat, instr, &x);
			अगर (ret)
				वापस ret;
			x >>= gas->bit_offset;
			x &= mask;
			अगर (retval)
				*retval = x == value;
			अवरोध;

		हाल ACPI_WDAT_READ_COUNTDOWN:
			ret = wdat_wdt_पढ़ो(wdat, instr, &x);
			अगर (ret)
				वापस ret;
			x >>= gas->bit_offset;
			x &= mask;
			अगर (retval)
				*retval = x;
			अवरोध;

		हाल ACPI_WDAT_WRITE_VALUE:
			x = value & mask;
			x <<= gas->bit_offset;
			अगर (preserve) अणु
				ret = wdat_wdt_पढ़ो(wdat, instr, &y);
				अगर (ret)
					वापस ret;
				y = y & ~(mask << gas->bit_offset);
				x |= y;
			पूर्ण
			ret = wdat_wdt_ग_लिखो(wdat, instr, x);
			अगर (ret)
				वापस ret;
			अवरोध;

		हाल ACPI_WDAT_WRITE_COUNTDOWN:
			x = param;
			x &= mask;
			x <<= gas->bit_offset;
			अगर (preserve) अणु
				ret = wdat_wdt_पढ़ो(wdat, instr, &y);
				अगर (ret)
					वापस ret;
				y = y & ~(mask << gas->bit_offset);
				x |= y;
			पूर्ण
			ret = wdat_wdt_ग_लिखो(wdat, instr, x);
			अगर (ret)
				वापस ret;
			अवरोध;

		शेष:
			dev_err(&wdat->pdev->dev, "Unknown instruction: %u\n",
				flags);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdat_wdt_enable_reboot(काष्ठा wdat_wdt *wdat)
अणु
	पूर्णांक ret;

	/*
	 * WDAT specअगरication says that the watchकरोg is required to reboot
	 * the प्रणाली when it fires. However, it also states that it is
	 * recommeded to make it configurable through hardware रेजिस्टर. We
	 * enable reboot now अगर it is configurable, just in हाल.
	 */
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_REBOOT, 0, शून्य);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		dev_err(&wdat->pdev->dev,
			"Failed to enable reboot when watchdog triggers\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wdat_wdt_boot_status(काष्ठा wdat_wdt *wdat)
अणु
	u32 boot_status = 0;
	पूर्णांक ret;

	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_GET_STATUS, 0, &boot_status);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		dev_err(&wdat->pdev->dev, "Failed to read boot status\n");
		वापस;
	पूर्ण

	अगर (boot_status)
		wdat->wdd.bootstatus = WDIOF_CARDRESET;

	/* Clear the boot status in हाल BIOS did not करो it */
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_STATUS, 0, शून्य);
	अगर (ret && ret != -EOPNOTSUPP)
		dev_err(&wdat->pdev->dev, "Failed to clear boot status\n");
पूर्ण

अटल व्योम wdat_wdt_set_running(काष्ठा wdat_wdt *wdat)
अणु
	u32 running = 0;
	पूर्णांक ret;

	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_GET_RUNNING_STATE, 0,
				  &running);
	अगर (ret && ret != -EOPNOTSUPP)
		dev_err(&wdat->pdev->dev, "Failed to read running state\n");

	अगर (running)
		set_bit(WDOG_HW_RUNNING, &wdat->wdd.status);
पूर्ण

अटल पूर्णांक wdat_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdat_wdt_run_action(to_wdat_wdt(wdd),
				   ACPI_WDAT_SET_RUNNING_STATE, 0, शून्य);
पूर्ण

अटल पूर्णांक wdat_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdat_wdt_run_action(to_wdat_wdt(wdd),
				   ACPI_WDAT_SET_STOPPED_STATE, 0, शून्य);
पूर्ण

अटल पूर्णांक wdat_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdat_wdt_run_action(to_wdat_wdt(wdd), ACPI_WDAT_RESET, 0, शून्य);
पूर्ण

अटल पूर्णांक wdat_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा wdat_wdt *wdat = to_wdat_wdt(wdd);
	अचिन्हित पूर्णांक periods;
	पूर्णांक ret;

	periods = समयout * 1000 / wdat->period;
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_COUNTDOWN, periods, शून्य);
	अगर (!ret)
		wdd->समयout = समयout;
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक wdat_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा wdat_wdt *wdat = to_wdat_wdt(wdd);
	u32 periods = 0;

	wdat_wdt_run_action(wdat, ACPI_WDAT_GET_CURRENT_COUNTDOWN, 0, &periods);
	वापस periods * wdat->period / 1000;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info wdat_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.firmware_version = 0,
	.identity = "wdat_wdt",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wdat_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdat_wdt_start,
	.stop = wdat_wdt_stop,
	.ping = wdat_wdt_ping,
	.set_समयout = wdat_wdt_set_समयout,
	.get_समयleft = wdat_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक wdat_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा acpi_wdat_entry *entries;
	स्थिर काष्ठा acpi_table_wdat *tbl;
	काष्ठा wdat_wdt *wdat;
	काष्ठा resource *res;
	व्योम __iomem **regs;
	acpi_status status;
	पूर्णांक i, ret;

	status = acpi_get_table(ACPI_SIG_WDAT, 0,
				(काष्ठा acpi_table_header **)&tbl);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	wdat = devm_kzalloc(dev, माप(*wdat), GFP_KERNEL);
	अगर (!wdat)
		वापस -ENOMEM;

	regs = devm_kसुस्मृति(dev, pdev->num_resources, माप(*regs),
			    GFP_KERNEL);
	अगर (!regs)
		वापस -ENOMEM;

	/* WDAT specअगरication wants to have >= 1ms period */
	अगर (tbl->समयr_period < 1)
		वापस -EINVAL;
	अगर (tbl->min_count > tbl->max_count)
		वापस -EINVAL;

	wdat->period = tbl->समयr_period;
	wdat->wdd.min_hw_heartbeat_ms = wdat->period * tbl->min_count;
	wdat->wdd.max_hw_heartbeat_ms = wdat->period * tbl->max_count;
	wdat->stopped_in_sleep = tbl->flags & ACPI_WDAT_STOPPED;
	wdat->wdd.info = &wdat_wdt_info;
	wdat->wdd.ops = &wdat_wdt_ops;
	wdat->pdev = pdev;

	/* Request and map all resources */
	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		व्योम __iomem *reg;

		res = &pdev->resource[i];
		अगर (resource_type(res) == IORESOURCE_MEM) अणु
			reg = devm_ioremap_resource(dev, res);
			अगर (IS_ERR(reg))
				वापस PTR_ERR(reg);
		पूर्ण अन्यथा अगर (resource_type(res) == IORESOURCE_IO) अणु
			reg = devm_ioport_map(dev, res->start, 1);
			अगर (!reg)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Unsupported resource\n");
			वापस -EINVAL;
		पूर्ण

		regs[i] = reg;
	पूर्ण

	entries = (काष्ठा acpi_wdat_entry *)(tbl + 1);
	क्रम (i = 0; i < tbl->entries; i++) अणु
		स्थिर काष्ठा acpi_generic_address *gas;
		काष्ठा wdat_inकाष्ठाion *instr;
		काष्ठा list_head *inकाष्ठाions;
		अचिन्हित पूर्णांक action;
		काष्ठा resource r;
		पूर्णांक j;

		action = entries[i].action;
		अगर (action >= MAX_WDAT_ACTIONS) अणु
			dev_dbg(dev, "Skipping unknown action: %u\n", action);
			जारी;
		पूर्ण

		instr = devm_kzalloc(dev, माप(*instr), GFP_KERNEL);
		अगर (!instr)
			वापस -ENOMEM;

		INIT_LIST_HEAD(&instr->node);
		instr->entry = entries[i];

		gas = &entries[i].रेजिस्टर_region;

		स_रखो(&r, 0, माप(r));
		r.start = gas->address;
		r.end = r.start + ACPI_ACCESS_BYTE_WIDTH(gas->access_width) - 1;
		अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
			r.flags = IORESOURCE_MEM;
		पूर्ण अन्यथा अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
			r.flags = IORESOURCE_IO;
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "Unsupported address space: %d\n",
				gas->space_id);
			जारी;
		पूर्ण

		/* Find the matching resource */
		क्रम (j = 0; j < pdev->num_resources; j++) अणु
			res = &pdev->resource[j];
			अगर (resource_contains(res, &r)) अणु
				instr->reg = regs[j] + r.start - res->start;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!instr->reg) अणु
			dev_err(dev, "I/O resource not found\n");
			वापस -EINVAL;
		पूर्ण

		inकाष्ठाions = wdat->inकाष्ठाions[action];
		अगर (!inकाष्ठाions) अणु
			inकाष्ठाions = devm_kzalloc(dev,
						    माप(*inकाष्ठाions),
						    GFP_KERNEL);
			अगर (!inकाष्ठाions)
				वापस -ENOMEM;

			INIT_LIST_HEAD(inकाष्ठाions);
			wdat->inकाष्ठाions[action] = inकाष्ठाions;
		पूर्ण

		list_add_tail(&instr->node, inकाष्ठाions);
	पूर्ण

	wdat_wdt_boot_status(wdat);
	wdat_wdt_set_running(wdat);

	ret = wdat_wdt_enable_reboot(wdat);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdat);

	/*
	 * Set initial समयout so that userspace has समय to configure the
	 * watchकरोg properly after it has खोलोed the device. In some हालs
	 * the BIOS शेष is too लघु and causes immediate reboot.
	 */
	अगर (समयout * 1000 < wdat->wdd.min_hw_heartbeat_ms ||
	    समयout * 1000 > wdat->wdd.max_hw_heartbeat_ms) अणु
		dev_warn(dev, "Invalid timeout %d given, using %d\n",
			 समयout, WDAT_DEFAULT_TIMEOUT);
		समयout = WDAT_DEFAULT_TIMEOUT;
	पूर्ण

	ret = wdat_wdt_set_समयout(&wdat->wdd, समयout);
	अगर (ret)
		वापस ret;

	watchकरोg_set_nowayout(&wdat->wdd, nowayout);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, &wdat->wdd);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक wdat_wdt_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा wdat_wdt *wdat = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!watchकरोg_active(&wdat->wdd))
		वापस 0;

	/*
	 * We need to stop the watchकरोg अगर firmare is not करोing it or अगर we
	 * are going suspend to idle (where firmware is not involved). If
	 * firmware is stopping the watchकरोg we kick it here one more समय
	 * to give it some समय.
	 */
	wdat->stopped = false;
	अगर (acpi_target_प्रणाली_state() == ACPI_STATE_S0 ||
	    !wdat->stopped_in_sleep) अणु
		ret = wdat_wdt_stop(&wdat->wdd);
		अगर (!ret)
			wdat->stopped = true;
	पूर्ण अन्यथा अणु
		ret = wdat_wdt_ping(&wdat->wdd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wdat_wdt_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा wdat_wdt *wdat = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!watchकरोg_active(&wdat->wdd))
		वापस 0;

	अगर (!wdat->stopped) अणु
		/*
		 * Looks like the boot firmware reinitializes the watchकरोg
		 * beक्रमe it hands off to the OS on resume from sleep so we
		 * stop and reprogram the watchकरोg here.
		 */
		ret = wdat_wdt_stop(&wdat->wdd);
		अगर (ret)
			वापस ret;

		ret = wdat_wdt_set_समयout(&wdat->wdd, wdat->wdd.समयout);
		अगर (ret)
			वापस ret;

		ret = wdat_wdt_enable_reboot(wdat);
		अगर (ret)
			वापस ret;

		ret = wdat_wdt_ping(&wdat->wdd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस wdat_wdt_start(&wdat->wdd);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops wdat_wdt_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(wdat_wdt_suspend_noirq,
				      wdat_wdt_resume_noirq)
पूर्ण;

अटल काष्ठा platक्रमm_driver wdat_wdt_driver = अणु
	.probe = wdat_wdt_probe,
	.driver = अणु
		.name = "wdat_wdt",
		.pm = &wdat_wdt_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wdat_wdt_driver);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("ACPI Hardware Watchdog (WDAT) driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:wdat_wdt");
