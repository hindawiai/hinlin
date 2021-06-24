<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * processor_driver.c - ACPI Processor Driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004       Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *  			- Added processor hotplug support
 *  Copyright (C) 2013, Intel Corporation
 *                      Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#समावेश <acpi/processor.h>

#समावेश "internal.h"

#घोषणा ACPI_PROCESSOR_NOTIFY_PERFORMANCE 0x80
#घोषणा ACPI_PROCESSOR_NOTIFY_POWER	0x81
#घोषणा ACPI_PROCESSOR_NOTIFY_THROTTLING	0x82

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_DESCRIPTION("ACPI Processor Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक acpi_processor_start(काष्ठा device *dev);
अटल पूर्णांक acpi_processor_stop(काष्ठा device *dev);

अटल स्थिर काष्ठा acpi_device_id processor_device_ids[] = अणु
	अणुACPI_PROCESSOR_OBJECT_HID, 0पूर्ण,
	अणुACPI_PROCESSOR_DEVICE_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, processor_device_ids);

अटल काष्ठा device_driver acpi_processor_driver = अणु
	.name = "processor",
	.bus = &cpu_subsys,
	.acpi_match_table = processor_device_ids,
	.probe = acpi_processor_start,
	.हटाओ = acpi_processor_stop,
पूर्ण;

अटल व्योम acpi_processor_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा acpi_device *device = data;
	काष्ठा acpi_processor *pr;
	पूर्णांक saved;

	अगर (device->handle != handle)
		वापस;

	pr = acpi_driver_data(device);
	अगर (!pr)
		वापस;

	चयन (event) अणु
	हाल ACPI_PROCESSOR_NOTIFY_PERFORMANCE:
		saved = pr->perक्रमmance_platक्रमm_limit;
		acpi_processor_ppc_has_changed(pr, 1);
		अगर (saved == pr->perक्रमmance_platक्रमm_limit)
			अवरोध;
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event,
						  pr->perक्रमmance_platक्रमm_limit);
		अवरोध;
	हाल ACPI_PROCESSOR_NOTIFY_POWER:
		acpi_processor_घातer_state_has_changed(pr);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		अवरोध;
	हाल ACPI_PROCESSOR_NOTIFY_THROTTLING:
		acpi_processor_tstate_has_changed(pr);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		अवरोध;
	शेष:
		acpi_handle_debug(handle, "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक __acpi_processor_start(काष्ठा acpi_device *device);

अटल पूर्णांक acpi_soft_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_processor *pr = per_cpu(processors, cpu);
	काष्ठा acpi_device *device;

	अगर (!pr || acpi_bus_get_device(pr->handle, &device))
		वापस 0;
	/*
	 * CPU got physically hotplugged and onlined क्रम the first समय:
	 * Initialize missing things.
	 */
	अगर (pr->flags.need_hotplug_init) अणु
		पूर्णांक ret;

		pr_info("Will online and init hotplugged CPU: %d\n",
			pr->id);
		pr->flags.need_hotplug_init = 0;
		ret = __acpi_processor_start(device);
		WARN(ret, "Failed to start CPU: %d\n", pr->id);
	पूर्ण अन्यथा अणु
		/* Normal CPU soft online event. */
		acpi_processor_ppc_has_changed(pr, 0);
		acpi_processor_hotplug(pr);
		acpi_processor_reevaluate_tstate(pr, false);
		acpi_processor_tstate_has_changed(pr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_soft_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_processor *pr = per_cpu(processors, cpu);
	काष्ठा acpi_device *device;

	अगर (!pr || acpi_bus_get_device(pr->handle, &device))
		वापस 0;

	acpi_processor_reevaluate_tstate(pr, true);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_CPU_FREQ_PSS
अटल पूर्णांक acpi_pss_perf_init(काष्ठा acpi_processor *pr,
		काष्ठा acpi_device *device)
अणु
	पूर्णांक result = 0;

	acpi_processor_ppc_has_changed(pr, 0);

	acpi_processor_get_throttling_info(pr);

	अगर (pr->flags.throttling)
		pr->flags.limit = 1;

	pr->cdev = thermal_cooling_device_रेजिस्टर("Processor", device,
						   &processor_cooling_ops);
	अगर (IS_ERR(pr->cdev)) अणु
		result = PTR_ERR(pr->cdev);
		वापस result;
	पूर्ण

	dev_dbg(&device->dev, "registered as cooling_device%d\n",
		pr->cdev->id);

	result = sysfs_create_link(&device->dev.kobj,
				   &pr->cdev->device.kobj,
				   "thermal_cooling");
	अगर (result) अणु
		dev_err(&device->dev,
			"Failed to create sysfs link 'thermal_cooling'\n");
		जाओ err_thermal_unरेजिस्टर;
	पूर्ण

	result = sysfs_create_link(&pr->cdev->device.kobj,
				   &device->dev.kobj,
				   "device");
	अगर (result) अणु
		dev_err(&pr->cdev->device,
			"Failed to create sysfs link 'device'\n");
		जाओ err_हटाओ_sysfs_thermal;
	पूर्ण

	वापस 0;

 err_हटाओ_sysfs_thermal:
	sysfs_हटाओ_link(&device->dev.kobj, "thermal_cooling");
 err_thermal_unरेजिस्टर:
	thermal_cooling_device_unरेजिस्टर(pr->cdev);

	वापस result;
पूर्ण

अटल व्योम acpi_pss_perf_निकास(काष्ठा acpi_processor *pr,
		काष्ठा acpi_device *device)
अणु
	अगर (pr->cdev) अणु
		sysfs_हटाओ_link(&device->dev.kobj, "thermal_cooling");
		sysfs_हटाओ_link(&pr->cdev->device.kobj, "device");
		thermal_cooling_device_unरेजिस्टर(pr->cdev);
		pr->cdev = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_pss_perf_init(काष्ठा acpi_processor *pr,
		काष्ठा acpi_device *device)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम acpi_pss_perf_निकास(काष्ठा acpi_processor *pr,
		काष्ठा acpi_device *device) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_CPU_FREQ_PSS */

अटल पूर्णांक __acpi_processor_start(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_processor *pr = acpi_driver_data(device);
	acpi_status status;
	पूर्णांक result = 0;

	अगर (!pr)
		वापस -ENODEV;

	अगर (pr->flags.need_hotplug_init)
		वापस 0;

	result = acpi_cppc_processor_probe(pr);
	अगर (result && !IS_ENABLED(CONFIG_ACPI_CPU_FREQ_PSS))
		dev_dbg(&device->dev, "CPPC data invalid or not present\n");

	अगर (!cpuidle_get_driver() || cpuidle_get_driver() == &acpi_idle_driver)
		acpi_processor_घातer_init(pr);

	result = acpi_pss_perf_init(pr, device);
	अगर (result)
		जाओ err_घातer_निकास;

	status = acpi_install_notअगरy_handler(device->handle, ACPI_DEVICE_NOTIFY,
					     acpi_processor_notअगरy, device);
	अगर (ACPI_SUCCESS(status))
		वापस 0;

	result = -ENODEV;
	acpi_pss_perf_निकास(pr, device);

err_घातer_निकास:
	acpi_processor_घातer_निकास(pr);
	वापस result;
पूर्ण

अटल पूर्णांक acpi_processor_start(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = ACPI_COMPANION(dev);
	पूर्णांक ret;

	अगर (!device)
		वापस -ENODEV;

	/* Protect against concurrent CPU hotplug operations */
	cpu_hotplug_disable();
	ret = __acpi_processor_start(device);
	cpu_hotplug_enable();
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_processor_stop(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = ACPI_COMPANION(dev);
	काष्ठा acpi_processor *pr;

	अगर (!device)
		वापस 0;

	acpi_हटाओ_notअगरy_handler(device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_processor_notअगरy);

	pr = acpi_driver_data(device);
	अगर (!pr)
		वापस 0;
	acpi_processor_घातer_निकास(pr);

	acpi_pss_perf_निकास(pr, device);

	acpi_cppc_processor_निकास(pr);

	वापस 0;
पूर्ण

bool acpi_processor_cpufreq_init;

अटल पूर्णांक acpi_processor_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा cpufreq_policy *policy = data;

	अगर (event == CPUFREQ_CREATE_POLICY) अणु
		acpi_thermal_cpufreq_init(policy);
		acpi_processor_ppc_init(policy);
	पूर्ण अन्यथा अगर (event == CPUFREQ_REMOVE_POLICY) अणु
		acpi_processor_ppc_निकास(policy);
		acpi_thermal_cpufreq_निकास(policy);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block acpi_processor_notअगरier_block = अणु
	.notअगरier_call = acpi_processor_notअगरier,
पूर्ण;

/*
 * We keep the driver loaded even when ACPI is not running.
 * This is needed क्रम the घातernow-k8 driver, that works even without
 * ACPI, but needs symbols from this driver
 */
अटल क्रमागत cpuhp_state hp_online;
अटल पूर्णांक __init acpi_processor_driver_init(व्योम)
अणु
	पूर्णांक result = 0;

	अगर (acpi_disabled)
		वापस 0;

	result = driver_रेजिस्टर(&acpi_processor_driver);
	अगर (result < 0)
		वापस result;

	result = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					   "acpi/cpu-drv:online",
					   acpi_soft_cpu_online, शून्य);
	अगर (result < 0)
		जाओ err;
	hp_online = result;
	cpuhp_setup_state_nocalls(CPUHP_ACPI_CPUDRV_DEAD, "acpi/cpu-drv:dead",
				  शून्य, acpi_soft_cpu_dead);

	अगर (!cpufreq_रेजिस्टर_notअगरier(&acpi_processor_notअगरier_block,
				       CPUFREQ_POLICY_NOTIFIER)) अणु
		acpi_processor_cpufreq_init = true;
		acpi_processor_ignore_ppc_init();
	पूर्ण

	acpi_processor_throttling_init();
	वापस 0;
err:
	driver_unरेजिस्टर(&acpi_processor_driver);
	वापस result;
पूर्ण

अटल व्योम __निकास acpi_processor_driver_निकास(व्योम)
अणु
	अगर (acpi_disabled)
		वापस;

	अगर (acpi_processor_cpufreq_init) अणु
		cpufreq_unरेजिस्टर_notअगरier(&acpi_processor_notअगरier_block,
					    CPUFREQ_POLICY_NOTIFIER);
		acpi_processor_cpufreq_init = false;
	पूर्ण

	cpuhp_हटाओ_state_nocalls(hp_online);
	cpuhp_हटाओ_state_nocalls(CPUHP_ACPI_CPUDRV_DEAD);
	driver_unरेजिस्टर(&acpi_processor_driver);
पूर्ण

module_init(acpi_processor_driver_init);
module_निकास(acpi_processor_driver_निकास);

MODULE_ALIAS("processor");
