<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Common ACPI functions क्रम hot plug platक्रमms
 *
 * Copyright (C) 2006 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <kristen.c.accardi@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/slab.h>

#घोषणा MY_NAME	"acpi_pcihp"

#घोषणा dbg(fmt, arg...) करो अणु अगर (debug_acpi) prपूर्णांकk(KERN_DEBUG "%s: %s: " fmt, MY_NAME, __func__, ## arg); पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)

#घोषणा	METHOD_NAME__SUN	"_SUN"
#घोषणा	METHOD_NAME_OSHP	"OSHP"

अटल bool debug_acpi;

/* acpi_run_oshp - get control of hotplug from the firmware
 *
 * @handle - the handle of the hotplug controller.
 */
अटल acpi_status acpi_run_oshp(acpi_handle handle)
अणु
	acpi_status		status;
	काष्ठा acpi_buffer	string = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	acpi_get_name(handle, ACPI_FULL_PATHNAME, &string);

	/* run OSHP */
	status = acpi_evaluate_object(handle, METHOD_NAME_OSHP, शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		अगर (status != AE_NOT_FOUND)
			prपूर्णांकk(KERN_ERR "%s:%s OSHP fails=0x%x\n",
			       __func__, (अक्षर *)string.poपूर्णांकer, status);
		अन्यथा
			dbg("%s:%s OSHP not found\n",
			    __func__, (अक्षर *)string.poपूर्णांकer);
	अन्यथा
		pr_debug("%s:%s OSHP passes\n", __func__,
			(अक्षर *)string.poपूर्णांकer);

	kमुक्त(string.poपूर्णांकer);
	वापस status;
पूर्ण

/**
 * acpi_get_hp_hw_control_from_firmware
 * @pdev: the pci_dev of the bridge that has a hotplug controller
 *
 * Attempt to take hotplug control from firmware.
 */
पूर्णांक acpi_get_hp_hw_control_from_firmware(काष्ठा pci_dev *pdev)
अणु
	स्थिर काष्ठा pci_host_bridge *host;
	स्थिर काष्ठा acpi_pci_root *root;
	acpi_status status;
	acpi_handle chandle, handle;
	काष्ठा acpi_buffer string = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	/*
	 * If there's no ACPI host bridge (i.e., ACPI support is compiled
	 * पूर्णांकo the kernel but the hardware platक्रमm करोesn't support ACPI),
	 * there's nothing to करो here.
	 */
	host = pci_find_host_bridge(pdev->bus);
	root = acpi_pci_find_root(ACPI_HANDLE(&host->dev));
	अगर (!root)
		वापस 0;

	/*
	 * If _OSC exists, it determines whether we're allowed to manage
	 * the SHPC.  We executed it जबतक क्रमागतerating the host bridge.
	 */
	अगर (root->osc_support_set) अणु
		अगर (host->native_shpc_hotplug)
			वापस 0;
		वापस -ENODEV;
	पूर्ण

	/*
	 * In the असलence of _OSC, we're always allowed to manage the SHPC.
	 * However, अगर an OSHP method is present, we must execute it so the
	 * firmware can transfer control to the OS, e.g., direct पूर्णांकerrupts
	 * to the OS instead of to the firmware.
	 *
	 * N.B. The PCI Firmware Spec (r3.2, sec 4.8) करोes not enकरोrse
	 * searching up the ACPI hierarchy, so the loops below are suspect.
	 */
	handle = ACPI_HANDLE(&pdev->dev);
	अगर (!handle) अणु
		/*
		 * This hotplug controller was not listed in the ACPI name
		 * space at all. Try to get ACPI handle of parent PCI bus.
		 */
		काष्ठा pci_bus *pbus;
		क्रम (pbus = pdev->bus; pbus; pbus = pbus->parent) अणु
			handle = acpi_pci_get_bridge_handle(pbus);
			अगर (handle)
				अवरोध;
		पूर्ण
	पूर्ण

	जबतक (handle) अणु
		acpi_get_name(handle, ACPI_FULL_PATHNAME, &string);
		pci_info(pdev, "Requesting control of SHPC hotplug via OSHP (%s)\n",
			 (अक्षर *)string.poपूर्णांकer);
		status = acpi_run_oshp(handle);
		अगर (ACPI_SUCCESS(status))
			जाओ got_one;
		अगर (acpi_is_root_bridge(handle))
			अवरोध;
		chandle = handle;
		status = acpi_get_parent(chandle, &handle);
		अगर (ACPI_FAILURE(status))
			अवरोध;
	पूर्ण

	pci_info(pdev, "Cannot get control of SHPC hotplug\n");
	kमुक्त(string.poपूर्णांकer);
	वापस -ENODEV;
got_one:
	pci_info(pdev, "Gained control of SHPC hotplug (%s)\n",
		 (अक्षर *)string.poपूर्णांकer);
	kमुक्त(string.poपूर्णांकer);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_get_hp_hw_control_from_firmware);

अटल पूर्णांक pcihp_is_ejectable(acpi_handle handle)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ removable;
	अगर (!acpi_has_method(handle, "_ADR"))
		वापस 0;
	अगर (acpi_has_method(handle, "_EJ0"))
		वापस 1;
	status = acpi_evaluate_पूर्णांकeger(handle, "_RMV", शून्य, &removable);
	अगर (ACPI_SUCCESS(status) && removable)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * acpi_pci_check_ejectable - check अगर handle is ejectable ACPI PCI slot
 * @pbus: the PCI bus of the PCI slot corresponding to 'handle'
 * @handle: ACPI handle to check
 *
 * Return 1 अगर handle is ejectable PCI slot, 0 otherwise.
 */
पूर्णांक acpi_pci_check_ejectable(काष्ठा pci_bus *pbus, acpi_handle handle)
अणु
	acpi_handle bridge_handle, parent_handle;

	bridge_handle = acpi_pci_get_bridge_handle(pbus);
	अगर (!bridge_handle)
		वापस 0;
	अगर ((ACPI_FAILURE(acpi_get_parent(handle, &parent_handle))))
		वापस 0;
	अगर (bridge_handle != parent_handle)
		वापस 0;
	वापस pcihp_is_ejectable(handle);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_pci_check_ejectable);

अटल acpi_status
check_hotplug(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	पूर्णांक *found = (पूर्णांक *)context;
	अगर (pcihp_is_ejectable(handle)) अणु
		*found = 1;
		वापस AE_CTRL_TERMINATE;
	पूर्ण
	वापस AE_OK;
पूर्ण

/**
 * acpi_pci_detect_ejectable - check अगर the PCI bus has ejectable slots
 * @handle: handle of the PCI bus to scan
 *
 * Returns 1 अगर the PCI bus has ACPI based ejectable slots, 0 otherwise.
 */
पूर्णांक acpi_pci_detect_ejectable(acpi_handle handle)
अणु
	पूर्णांक found = 0;

	अगर (!handle)
		वापस found;

	acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
			    check_hotplug, शून्य, (व्योम *)&found, शून्य);
	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_pci_detect_ejectable);

module_param(debug_acpi, bool, 0644);
MODULE_PARM_DESC(debug_acpi, "Debugging mode for ACPI enabled or not");
