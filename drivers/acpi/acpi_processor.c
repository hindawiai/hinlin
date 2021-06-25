<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * acpi_processor.c - ACPI processor क्रमागतeration support
 *
 * Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 * Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 * Copyright (C) 2004       Dominik Broकरोwski <linux@broकरो.de>
 * Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 * Copyright (C) 2013, Intel Corporation
 *                     Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <acpi/processor.h>

#समावेश <यंत्र/cpu.h>

#समावेश "internal.h"

DEFINE_PER_CPU(काष्ठा acpi_processor *, processors);
EXPORT_PER_CPU_SYMBOL(processors);

/* Errata Handling */
काष्ठा acpi_processor_errata errata __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(errata);

अटल पूर्णांक acpi_processor_errata_piix4(काष्ठा pci_dev *dev)
अणु
	u8 value1 = 0;
	u8 value2 = 0;


	अगर (!dev)
		वापस -EINVAL;

	/*
	 * Note that 'dev' references the PIIX4 ACPI Controller.
	 */

	चयन (dev->revision) अणु
	हाल 0:
		dev_dbg(&dev->dev, "Found PIIX4 A-step\n");
		अवरोध;
	हाल 1:
		dev_dbg(&dev->dev, "Found PIIX4 B-step\n");
		अवरोध;
	हाल 2:
		dev_dbg(&dev->dev, "Found PIIX4E\n");
		अवरोध;
	हाल 3:
		dev_dbg(&dev->dev, "Found PIIX4M\n");
		अवरोध;
	शेष:
		dev_dbg(&dev->dev, "Found unknown PIIX4\n");
		अवरोध;
	पूर्ण

	चयन (dev->revision) अणु

	हाल 0:		/* PIIX4 A-step */
	हाल 1:		/* PIIX4 B-step */
		/*
		 * See specअगरication changes #13 ("Manual Throttle Duty Cycle")
		 * and #14 ("Enabling and Disabling Manual Throttle"), plus
		 * erratum #5 ("STPCLK# Deassertion Time") from the January
		 * 2002 PIIX4 specअगरication update.  Applies to only older
		 * PIIX4 models.
		 */
		errata.piix4.throttle = 1;
		fallthrough;

	हाल 2:		/* PIIX4E */
	हाल 3:		/* PIIX4M */
		/*
		 * See erratum #18 ("C3 Power State/BMIDE and Type-F DMA
		 * Livelock") from the January 2002 PIIX4 specअगरication update.
		 * Applies to all PIIX4 models.
		 */

		/*
		 * BM-IDE
		 * ------
		 * Find the PIIX4 IDE Controller and get the Bus Master IDE
		 * Status रेजिस्टर address.  We'll use this later to पढ़ो
		 * each IDE controller's DMA status to make sure we catch all
		 * DMA activity.
		 */
		dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
				     PCI_DEVICE_ID_INTEL_82371AB,
				     PCI_ANY_ID, PCI_ANY_ID, शून्य);
		अगर (dev) अणु
			errata.piix4.bmisx = pci_resource_start(dev, 4);
			pci_dev_put(dev);
		पूर्ण

		/*
		 * Type-F DMA
		 * ----------
		 * Find the PIIX4 ISA Controller and पढ़ो the Motherboard
		 * DMA controller's status to see अगर Type-F (Fast) DMA mode
		 * is enabled (bit 7) on either channel.  Note that we'll
		 * disable C3 support अगर this is enabled, as some legacy
		 * devices won't operate well अगर fast DMA is disabled.
		 */
		dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
				     PCI_DEVICE_ID_INTEL_82371AB_0,
				     PCI_ANY_ID, PCI_ANY_ID, शून्य);
		अगर (dev) अणु
			pci_पढ़ो_config_byte(dev, 0x76, &value1);
			pci_पढ़ो_config_byte(dev, 0x77, &value2);
			अगर ((value1 & 0x80) || (value2 & 0x80))
				errata.piix4.fdma = 1;
			pci_dev_put(dev);
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (errata.piix4.bmisx)
		dev_dbg(&dev->dev, "Bus master activity detection (BM-IDE) erratum enabled\n");
	अगर (errata.piix4.fdma)
		dev_dbg(&dev->dev, "Type-F DMA livelock erratum (C3 disabled)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_errata(व्योम)
अणु
	पूर्णांक result = 0;
	काष्ठा pci_dev *dev = शून्य;

	/*
	 * PIIX4
	 */
	dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			     PCI_DEVICE_ID_INTEL_82371AB_3, PCI_ANY_ID,
			     PCI_ANY_ID, शून्य);
	अगर (dev) अणु
		result = acpi_processor_errata_piix4(dev);
		pci_dev_put(dev);
	पूर्ण

	वापस result;
पूर्ण

/* Initialization */
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
पूर्णांक __weak acpi_map_cpu(acpi_handle handle,
		phys_cpuid_t physid, u32 acpi_id, पूर्णांक *pcpu)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक __weak acpi_unmap_cpu(पूर्णांक cpu)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक __weak arch_रेजिस्टर_cpu(पूर्णांक cpu)
अणु
	वापस -ENODEV;
पूर्ण

व्योम __weak arch_unरेजिस्टर_cpu(पूर्णांक cpu) अणुपूर्ण

अटल पूर्णांक acpi_processor_hotadd_init(काष्ठा acpi_processor *pr)
अणु
	अचिन्हित दीर्घ दीर्घ sta;
	acpi_status status;
	पूर्णांक ret;

	अगर (invalid_phys_cpuid(pr->phys_id))
		वापस -ENODEV;

	status = acpi_evaluate_पूर्णांकeger(pr->handle, "_STA", शून्य, &sta);
	अगर (ACPI_FAILURE(status) || !(sta & ACPI_STA_DEVICE_PRESENT))
		वापस -ENODEV;

	cpu_maps_update_begin();
	cpu_hotplug_begin();

	ret = acpi_map_cpu(pr->handle, pr->phys_id, pr->acpi_id, &pr->id);
	अगर (ret)
		जाओ out;

	ret = arch_रेजिस्टर_cpu(pr->id);
	अगर (ret) अणु
		acpi_unmap_cpu(pr->id);
		जाओ out;
	पूर्ण

	/*
	 * CPU got hot-added, but cpu_data is not initialized yet.  Set a flag
	 * to delay cpu_idle/throttling initialization and करो it when the CPU
	 * माला_लो online क्रम the first समय.
	 */
	pr_info("CPU%d has been hot-added\n", pr->id);
	pr->flags.need_hotplug_init = 1;

out:
	cpu_hotplug_करोne();
	cpu_maps_update_करोne();
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_processor_hotadd_init(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_HOTPLUG_CPU */

अटल पूर्णांक acpi_processor_get_info(काष्ठा acpi_device *device)
अणु
	जोड़ acpi_object object = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(जोड़ acpi_object), &object पूर्ण;
	काष्ठा acpi_processor *pr = acpi_driver_data(device);
	पूर्णांक device_declaration = 0;
	acpi_status status = AE_OK;
	अटल पूर्णांक cpu0_initialized;
	अचिन्हित दीर्घ दीर्घ value;

	acpi_processor_errata();

	/*
	 * Check to see अगर we have bus mastering arbitration control.  This
	 * is required क्रम proper C3 usage (to मुख्यtain cache coherency).
	 */
	अगर (acpi_gbl_FADT.pm2_control_block && acpi_gbl_FADT.pm2_control_length) अणु
		pr->flags.bm_control = 1;
		dev_dbg(&device->dev, "Bus mastering arbitration control present\n");
	पूर्ण अन्यथा
		dev_dbg(&device->dev, "No bus mastering arbitration control\n");

	अगर (!म_भेद(acpi_device_hid(device), ACPI_PROCESSOR_OBJECT_HID)) अणु
		/* Declared with "Processor" statement; match ProcessorID */
		status = acpi_evaluate_object(pr->handle, शून्य, शून्य, &buffer);
		अगर (ACPI_FAILURE(status)) अणु
			dev_err(&device->dev,
				"Failed to evaluate processor object (0x%x)\n",
				status);
			वापस -ENODEV;
		पूर्ण

		pr->acpi_id = object.processor.proc_id;
	पूर्ण अन्यथा अणु
		/*
		 * Declared with "Device" statement; match _UID.
		 */
		status = acpi_evaluate_पूर्णांकeger(pr->handle, METHOD_NAME__UID,
						शून्य, &value);
		अगर (ACPI_FAILURE(status)) अणु
			dev_err(&device->dev,
				"Failed to evaluate processor _UID (0x%x)\n",
				status);
			वापस -ENODEV;
		पूर्ण
		device_declaration = 1;
		pr->acpi_id = value;
	पूर्ण

	अगर (acpi_duplicate_processor_id(pr->acpi_id)) अणु
		अगर (pr->acpi_id == 0xff)
			dev_info_once(&device->dev,
				"Entry not well-defined, consider updating BIOS\n");
		अन्यथा
			dev_err(&device->dev,
				"Failed to get unique processor _UID (0x%x)\n",
				pr->acpi_id);
		वापस -ENODEV;
	पूर्ण

	pr->phys_id = acpi_get_phys_id(pr->handle, device_declaration,
					pr->acpi_id);
	अगर (invalid_phys_cpuid(pr->phys_id))
		dev_dbg(&device->dev, "Failed to get CPU physical ID.\n");

	pr->id = acpi_map_cpuid(pr->phys_id, pr->acpi_id);
	अगर (!cpu0_initialized && !acpi_has_cpu_in_madt()) अणु
		cpu0_initialized = 1;
		/*
		 * Handle UP प्रणाली running SMP kernel, with no CPU
		 * entry in MADT
		 */
		अगर (invalid_logical_cpuid(pr->id) && (num_online_cpus() == 1))
			pr->id = 0;
	पूर्ण

	/*
	 *  Extra Processor objects may be क्रमागतerated on MP प्रणालीs with
	 *  less than the max # of CPUs. They should be ignored _अगरf
	 *  they are physically not present.
	 *
	 *  NOTE: Even अगर the processor has a cpuid, it may not be present
	 *  because cpuid <-> apicid mapping is persistent now.
	 */
	अगर (invalid_logical_cpuid(pr->id) || !cpu_present(pr->id)) अणु
		पूर्णांक ret = acpi_processor_hotadd_init(pr);

		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * On some boxes several processors use the same processor bus id.
	 * But they are located in dअगरferent scope. For example:
	 * \_SB.SCK0.CPU0
	 * \_SB.SCK1.CPU0
	 * Rename the processor device bus id. And the new bus id will be
	 * generated as the following क्रमmat:
	 * CPU+CPU ID.
	 */
	प्र_लिखो(acpi_device_bid(device), "CPU%X", pr->id);
	dev_dbg(&device->dev, "Processor [%d:%d]\n", pr->id, pr->acpi_id);

	अगर (!object.processor.pblk_address)
		dev_dbg(&device->dev, "No PBLK (NULL address)\n");
	अन्यथा अगर (object.processor.pblk_length != 6)
		dev_err(&device->dev, "Invalid PBLK length [%d]\n",
			    object.processor.pblk_length);
	अन्यथा अणु
		pr->throttling.address = object.processor.pblk_address;
		pr->throttling.duty_offset = acpi_gbl_FADT.duty_offset;
		pr->throttling.duty_width = acpi_gbl_FADT.duty_width;

		pr->pblk = object.processor.pblk_address;
	पूर्ण

	/*
	 * If ACPI describes a slot number क्रम this CPU, we can use it to
	 * ensure we get the right value in the "physical id" field
	 * of /proc/cpuinfo
	 */
	status = acpi_evaluate_पूर्णांकeger(pr->handle, "_SUN", शून्य, &value);
	अगर (ACPI_SUCCESS(status))
		arch_fix_phys_package_id(pr->id, value);

	वापस 0;
पूर्ण

/*
 * Do not put anything in here which needs the core to be online.
 * For example MSR access or setting up things which check क्रम cpuinfo_x86
 * (cpu_data(cpu)) values, like CPU feature flags, family, model, etc.
 * Such things have to be put in and set up by the processor driver's .probe().
 */
अटल DEFINE_PER_CPU(व्योम *, processor_device_array);

अटल पूर्णांक acpi_processor_add(काष्ठा acpi_device *device,
					स्थिर काष्ठा acpi_device_id *id)
अणु
	काष्ठा acpi_processor *pr;
	काष्ठा device *dev;
	पूर्णांक result = 0;

	pr = kzalloc(माप(काष्ठा acpi_processor), GFP_KERNEL);
	अगर (!pr)
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(&pr->throttling.shared_cpu_map, GFP_KERNEL)) अणु
		result = -ENOMEM;
		जाओ err_मुक्त_pr;
	पूर्ण

	pr->handle = device->handle;
	म_नकल(acpi_device_name(device), ACPI_PROCESSOR_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PROCESSOR_CLASS);
	device->driver_data = pr;

	result = acpi_processor_get_info(device);
	अगर (result) /* Processor is not physically present or unavailable */
		वापस 0;

	BUG_ON(pr->id >= nr_cpu_ids);

	/*
	 * Buggy BIOS check.
	 * ACPI id of processors can be reported wrongly by the BIOS.
	 * Don't trust it blindly
	 */
	अगर (per_cpu(processor_device_array, pr->id) != शून्य &&
	    per_cpu(processor_device_array, pr->id) != device) अणु
		dev_warn(&device->dev,
			"BIOS reported wrong ACPI id %d for the processor\n",
			pr->id);
		/* Give up, but करो not पात the namespace scan. */
		जाओ err;
	पूर्ण
	/*
	 * processor_device_array is not cleared on errors to allow buggy BIOS
	 * checks.
	 */
	per_cpu(processor_device_array, pr->id) = device;
	per_cpu(processors, pr->id) = pr;

	dev = get_cpu_device(pr->id);
	अगर (!dev) अणु
		result = -ENODEV;
		जाओ err;
	पूर्ण

	result = acpi_bind_one(dev, device);
	अगर (result)
		जाओ err;

	pr->dev = dev;

	/* Trigger the processor driver's .probe() अगर present. */
	अगर (device_attach(dev) >= 0)
		वापस 1;

	dev_err(dev, "Processor driver could not be attached\n");
	acpi_unbind_one(dev);

 err:
	मुक्त_cpumask_var(pr->throttling.shared_cpu_map);
	device->driver_data = शून्य;
	per_cpu(processors, pr->id) = शून्य;
 err_मुक्त_pr:
	kमुक्त(pr);
	वापस result;
पूर्ण

#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
/* Removal */
अटल व्योम acpi_processor_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_processor *pr;

	अगर (!device || !acpi_driver_data(device))
		वापस;

	pr = acpi_driver_data(device);
	अगर (pr->id >= nr_cpu_ids)
		जाओ out;

	/*
	 * The only reason why we ever get here is CPU hot-removal.  The CPU is
	 * alपढ़ोy offline and the ACPI device removal locking prevents it from
	 * being put back online at this poपूर्णांक.
	 *
	 * Unbind the driver from the processor device and detach it from the
	 * ACPI companion object.
	 */
	device_release_driver(pr->dev);
	acpi_unbind_one(pr->dev);

	/* Clean up. */
	per_cpu(processor_device_array, pr->id) = शून्य;
	per_cpu(processors, pr->id) = शून्य;

	cpu_maps_update_begin();
	cpu_hotplug_begin();

	/* Remove the CPU. */
	arch_unरेजिस्टर_cpu(pr->id);
	acpi_unmap_cpu(pr->id);

	cpu_hotplug_करोne();
	cpu_maps_update_करोne();

	try_offline_node(cpu_to_node(pr->id));

 out:
	मुक्त_cpumask_var(pr->throttling.shared_cpu_map);
	kमुक्त(pr);
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_HOTPLUG_CPU */

#अगर_घोषित CONFIG_X86
अटल bool acpi_hwp_native_thermal_lvt_set;
अटल acpi_status __init acpi_hwp_native_thermal_lvt_osc(acpi_handle handle,
							  u32 lvl,
							  व्योम *context,
							  व्योम **rv)
अणु
	u8 sb_uuid_str[] = "4077A616-290C-47BE-9EBD-D87058713953";
	u32 capbuf[2];
	काष्ठा acpi_osc_context osc_context = अणु
		.uuid_str = sb_uuid_str,
		.rev = 1,
		.cap.length = 8,
		.cap.poपूर्णांकer = capbuf,
	पूर्ण;

	अगर (acpi_hwp_native_thermal_lvt_set)
		वापस AE_CTRL_TERMINATE;

	capbuf[0] = 0x0000;
	capbuf[1] = 0x1000; /* set bit 12 */

	अगर (ACPI_SUCCESS(acpi_run_osc(handle, &osc_context))) अणु
		अगर (osc_context.ret.poपूर्णांकer && osc_context.ret.length > 1) अणु
			u32 *capbuf_ret = osc_context.ret.poपूर्णांकer;

			अगर (capbuf_ret[1] & 0x1000) अणु
				acpi_handle_info(handle,
					"_OSC native thermal LVT Acked\n");
				acpi_hwp_native_thermal_lvt_set = true;
			पूर्ण
		पूर्ण
		kमुक्त(osc_context.ret.poपूर्णांकer);
	पूर्ण

	वापस AE_OK;
पूर्ण

व्योम __init acpi_early_processor_osc(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_HWP)) अणु
		acpi_walk_namespace(ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT,
				    ACPI_UINT32_MAX,
				    acpi_hwp_native_thermal_lvt_osc,
				    शून्य, शून्य, शून्य);
		acpi_get_devices(ACPI_PROCESSOR_DEVICE_HID,
				 acpi_hwp_native_thermal_lvt_osc,
				 शून्य, शून्य);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * The following ACPI IDs are known to be suitable क्रम representing as
 * processor devices.
 */
अटल स्थिर काष्ठा acpi_device_id processor_device_ids[] = अणु

	अणु ACPI_PROCESSOR_OBJECT_HID, पूर्ण,
	अणु ACPI_PROCESSOR_DEVICE_HID, पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल काष्ठा acpi_scan_handler processor_handler = अणु
	.ids = processor_device_ids,
	.attach = acpi_processor_add,
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
	.detach = acpi_processor_हटाओ,
#पूर्ण_अगर
	.hotplug = अणु
		.enabled = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक acpi_processor_container_attach(काष्ठा acpi_device *dev,
					   स्थिर काष्ठा acpi_device_id *id)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id processor_container_ids[] = अणु
	अणु ACPI_PROCESSOR_CONTAINER_HID, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा acpi_scan_handler processor_container_handler = अणु
	.ids = processor_container_ids,
	.attach = acpi_processor_container_attach,
पूर्ण;

/* The number of the unique processor IDs */
अटल पूर्णांक nr_unique_ids __initdata;

/* The number of the duplicate processor IDs */
अटल पूर्णांक nr_duplicate_ids;

/* Used to store the unique processor IDs */
अटल पूर्णांक unique_processor_ids[] __initdata = अणु
	[0 ... NR_CPUS - 1] = -1,
पूर्ण;

/* Used to store the duplicate processor IDs */
अटल पूर्णांक duplicate_processor_ids[] = अणु
	[0 ... NR_CPUS - 1] = -1,
पूर्ण;

अटल व्योम __init processor_validated_ids_update(पूर्णांक proc_id)
अणु
	पूर्णांक i;

	अगर (nr_unique_ids == NR_CPUS||nr_duplicate_ids == NR_CPUS)
		वापस;

	/*
	 * Firstly, compare the proc_id with duplicate IDs, अगर the proc_id is
	 * alपढ़ोy in the IDs, करो nothing.
	 */
	क्रम (i = 0; i < nr_duplicate_ids; i++) अणु
		अगर (duplicate_processor_ids[i] == proc_id)
			वापस;
	पूर्ण

	/*
	 * Secondly, compare the proc_id with unique IDs, अगर the proc_id is in
	 * the IDs, put it in the duplicate IDs.
	 */
	क्रम (i = 0; i < nr_unique_ids; i++) अणु
		अगर (unique_processor_ids[i] == proc_id) अणु
			duplicate_processor_ids[nr_duplicate_ids] = proc_id;
			nr_duplicate_ids++;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Lastly, the proc_id is a unique ID, put it in the unique IDs.
	 */
	unique_processor_ids[nr_unique_ids] = proc_id;
	nr_unique_ids++;
पूर्ण

अटल acpi_status __init acpi_processor_ids_walk(acpi_handle handle,
						  u32 lvl,
						  व्योम *context,
						  व्योम **rv)
अणु
	acpi_status status;
	acpi_object_type acpi_type;
	अचिन्हित दीर्घ दीर्घ uid;
	जोड़ acpi_object object = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(जोड़ acpi_object), &object पूर्ण;

	status = acpi_get_type(handle, &acpi_type);
	अगर (ACPI_FAILURE(status))
		वापस status;

	चयन (acpi_type) अणु
	हाल ACPI_TYPE_PROCESSOR:
		status = acpi_evaluate_object(handle, शून्य, शून्य, &buffer);
		अगर (ACPI_FAILURE(status))
			जाओ err;
		uid = object.processor.proc_id;
		अवरोध;

	हाल ACPI_TYPE_DEVICE:
		status = acpi_evaluate_पूर्णांकeger(handle, "_UID", शून्य, &uid);
		अगर (ACPI_FAILURE(status))
			जाओ err;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	processor_validated_ids_update(uid);
	वापस AE_OK;

err:
	/* Exit on error, but करोn't पात the namespace walk */
	acpi_handle_info(handle, "Invalid processor object\n");
	वापस AE_OK;

पूर्ण

अटल व्योम __init acpi_processor_check_duplicates(व्योम)
अणु
	/* check the correctness क्रम all processors in ACPI namespace */
	acpi_walk_namespace(ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT,
						ACPI_UINT32_MAX,
						acpi_processor_ids_walk,
						शून्य, शून्य, शून्य);
	acpi_get_devices(ACPI_PROCESSOR_DEVICE_HID, acpi_processor_ids_walk,
						शून्य, शून्य);
पूर्ण

bool acpi_duplicate_processor_id(पूर्णांक proc_id)
अणु
	पूर्णांक i;

	/*
	 * compare the proc_id with duplicate IDs, अगर the proc_id is alपढ़ोy
	 * in the duplicate IDs, वापस true, otherwise, वापस false.
	 */
	क्रम (i = 0; i < nr_duplicate_ids; i++) अणु
		अगर (duplicate_processor_ids[i] == proc_id)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम __init acpi_processor_init(व्योम)
अणु
	acpi_processor_check_duplicates();
	acpi_scan_add_handler_with_hotplug(&processor_handler, "processor");
	acpi_scan_add_handler(&processor_container_handler);
पूर्ण

#अगर_घोषित CONFIG_ACPI_PROCESSOR_CSTATE
/**
 * acpi_processor_claim_cst_control - Request _CST control from the platक्रमm.
 */
bool acpi_processor_claim_cst_control(व्योम)
अणु
	अटल bool cst_control_claimed;
	acpi_status status;

	अगर (!acpi_gbl_FADT.cst_control || cst_control_claimed)
		वापस true;

	status = acpi_os_ग_लिखो_port(acpi_gbl_FADT.smi_command,
				    acpi_gbl_FADT.cst_control, 8);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn("ACPI: Failed to claim processor _CST control\n");
		वापस false;
	पूर्ण

	cst_control_claimed = true;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_processor_claim_cst_control);

/**
 * acpi_processor_evaluate_cst - Evaluate the processor _CST control method.
 * @handle: ACPI handle of the processor object containing the _CST.
 * @cpu: The numeric ID of the target CPU.
 * @info: Object ग_लिखो the C-states inक्रमmation पूर्णांकo.
 *
 * Extract the C-state inक्रमmation क्रम the given CPU from the output of the _CST
 * control method under the corresponding ACPI processor object (or processor
 * device object) and populate @info with it.
 *
 * If any ACPI_ADR_SPACE_FIXED_HARDWARE C-states are found, invoke
 * acpi_processor_ffh_cstate_probe() to verअगरy them and update the
 * cpu_cstate_entry data क्रम @cpu.
 */
पूर्णांक acpi_processor_evaluate_cst(acpi_handle handle, u32 cpu,
				काष्ठा acpi_processor_घातer *info)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *cst;
	acpi_status status;
	u64 count;
	पूर्णांक last_index = 0;
	पूर्णांक i, ret = 0;

	status = acpi_evaluate_object(handle, "_CST", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "No _CST\n");
		वापस -ENODEV;
	पूर्ण

	cst = buffer.poपूर्णांकer;

	/* There must be at least 2 elements. */
	अगर (!cst || cst->type != ACPI_TYPE_PACKAGE || cst->package.count < 2) अणु
		acpi_handle_warn(handle, "Invalid _CST output\n");
		ret = -EFAULT;
		जाओ end;
	पूर्ण

	count = cst->package.elements[0].पूर्णांकeger.value;

	/* Validate the number of C-states. */
	अगर (count < 1 || count != cst->package.count - 1) अणु
		acpi_handle_warn(handle, "Inconsistent _CST data\n");
		ret = -EFAULT;
		जाओ end;
	पूर्ण

	क्रम (i = 1; i <= count; i++) अणु
		जोड़ acpi_object *element;
		जोड़ acpi_object *obj;
		काष्ठा acpi_घातer_रेजिस्टर *reg;
		काष्ठा acpi_processor_cx cx;

		/*
		 * If there is not enough space क्रम all C-states, skip the
		 * excess ones and log a warning.
		 */
		अगर (last_index >= ACPI_PROCESSOR_MAX_POWER - 1) अणु
			acpi_handle_warn(handle,
					 "No room for more idle states (limit: %d)\n",
					 ACPI_PROCESSOR_MAX_POWER - 1);
			अवरोध;
		पूर्ण

		स_रखो(&cx, 0, माप(cx));

		element = &cst->package.elements[i];
		अगर (element->type != ACPI_TYPE_PACKAGE) अणु
			acpi_handle_info(handle, "_CST C%d type(%x) is not package, skip...\n",
					 i, element->type);
			जारी;
		पूर्ण

		अगर (element->package.count != 4) अणु
			acpi_handle_info(handle, "_CST C%d package count(%d) is not 4, skip...\n",
					 i, element->package.count);
			जारी;
		पूर्ण

		obj = &element->package.elements[0];

		अगर (obj->type != ACPI_TYPE_BUFFER) अणु
			acpi_handle_info(handle, "_CST C%d package element[0] type(%x) is not buffer, skip...\n",
					 i, obj->type);
			जारी;
		पूर्ण

		reg = (काष्ठा acpi_घातer_रेजिस्टर *)obj->buffer.poपूर्णांकer;

		obj = &element->package.elements[1];
		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_info(handle, "_CST C[%d] package element[1] type(%x) is not integer, skip...\n",
					 i, obj->type);
			जारी;
		पूर्ण

		cx.type = obj->पूर्णांकeger.value;
		/*
		 * There are known हालs in which the _CST output करोes not
		 * contain C1, so अगर the type of the first state found is not
		 * C1, leave an empty slot क्रम C1 to be filled in later.
		 */
		अगर (i == 1 && cx.type != ACPI_STATE_C1)
			last_index = 1;

		cx.address = reg->address;
		cx.index = last_index + 1;

		अगर (reg->space_id == ACPI_ADR_SPACE_FIXED_HARDWARE) अणु
			अगर (!acpi_processor_ffh_cstate_probe(cpu, &cx, reg)) अणु
				/*
				 * In the majority of हालs _CST describes C1 as
				 * a FIXED_HARDWARE C-state, but अगर the command
				 * line क्रमbids using MWAIT, use CSTATE_HALT क्रम
				 * C1 regardless.
				 */
				अगर (cx.type == ACPI_STATE_C1 &&
				    boot_option_idle_override == IDLE_NOMWAIT) अणु
					cx.entry_method = ACPI_CSTATE_HALT;
					snम_लिखो(cx.desc, ACPI_CX_DESC_LEN, "ACPI HLT");
				पूर्ण अन्यथा अणु
					cx.entry_method = ACPI_CSTATE_FFH;
				पूर्ण
			पूर्ण अन्यथा अगर (cx.type == ACPI_STATE_C1) अणु
				/*
				 * In the special हाल of C1, FIXED_HARDWARE can
				 * be handled by executing the HLT inकाष्ठाion.
				 */
				cx.entry_method = ACPI_CSTATE_HALT;
				snम_लिखो(cx.desc, ACPI_CX_DESC_LEN, "ACPI HLT");
			पूर्ण अन्यथा अणु
				acpi_handle_info(handle, "_CST C%d declares FIXED_HARDWARE C-state but not supported in hardware, skip...\n",
						 i);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
			cx.entry_method = ACPI_CSTATE_SYSTEMIO;
			snम_लिखो(cx.desc, ACPI_CX_DESC_LEN, "ACPI IOPORT 0x%x",
				 cx.address);
		पूर्ण अन्यथा अणु
			acpi_handle_info(handle, "_CST C%d space_id(%x) neither FIXED_HARDWARE nor SYSTEM_IO, skip...\n",
					 i, reg->space_id);
			जारी;
		पूर्ण

		अगर (cx.type == ACPI_STATE_C1)
			cx.valid = 1;

		obj = &element->package.elements[2];
		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_info(handle, "_CST C%d package element[2] type(%x) not integer, skip...\n",
					 i, obj->type);
			जारी;
		पूर्ण

		cx.latency = obj->पूर्णांकeger.value;

		obj = &element->package.elements[3];
		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_info(handle, "_CST C%d package element[3] type(%x) not integer, skip...\n",
					 i, obj->type);
			जारी;
		पूर्ण

		स_नकल(&info->states[++last_index], &cx, माप(cx));
	पूर्ण

	acpi_handle_info(handle, "Found %d idle states\n", last_index);

	info->count = last_index;

end:
	kमुक्त(buffer.poपूर्णांकer);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_processor_evaluate_cst);
#पूर्ण_अगर /* CONFIG_ACPI_PROCESSOR_CSTATE */
