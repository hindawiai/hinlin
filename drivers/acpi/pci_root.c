<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pci_root.c - ACPI PCI Root Bridge Driver ($Revision: 40 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/dmar.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <acpi/apei.h>	/* क्रम acpi_hest_init() */

#समावेश "internal.h"

#घोषणा ACPI_PCI_ROOT_CLASS		"pci_bridge"
#घोषणा ACPI_PCI_ROOT_DEVICE_NAME	"PCI Root Bridge"
अटल पूर्णांक acpi_pci_root_add(काष्ठा acpi_device *device,
			     स्थिर काष्ठा acpi_device_id *not_used);
अटल व्योम acpi_pci_root_हटाओ(काष्ठा acpi_device *device);

अटल पूर्णांक acpi_pci_root_scan_dependent(काष्ठा acpi_device *adev)
अणु
	acpiphp_check_host_bridge(adev);
	वापस 0;
पूर्ण

#घोषणा ACPI_PCIE_REQ_SUPPORT (OSC_PCI_EXT_CONFIG_SUPPORT \
				| OSC_PCI_ASPM_SUPPORT \
				| OSC_PCI_CLOCK_PM_SUPPORT \
				| OSC_PCI_MSI_SUPPORT)

अटल स्थिर काष्ठा acpi_device_id root_device_ids[] = अणु
	अणु"PNP0A03", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_scan_handler pci_root_handler = अणु
	.ids = root_device_ids,
	.attach = acpi_pci_root_add,
	.detach = acpi_pci_root_हटाओ,
	.hotplug = अणु
		.enabled = true,
		.scan_dependent = acpi_pci_root_scan_dependent,
	पूर्ण,
पूर्ण;

/**
 * acpi_is_root_bridge - determine whether an ACPI CA node is a PCI root bridge
 * @handle:  the ACPI CA node in question.
 *
 * Note: we could make this API take a काष्ठा acpi_device * instead, but
 * क्रम now, it's more convenient to operate on an acpi_handle.
 */
पूर्णांक acpi_is_root_bridge(acpi_handle handle)
अणु
	पूर्णांक ret;
	काष्ठा acpi_device *device;

	ret = acpi_bus_get_device(handle, &device);
	अगर (ret)
		वापस 0;

	ret = acpi_match_device_ids(device, root_device_ids);
	अगर (ret)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_is_root_bridge);

अटल acpi_status
get_root_bridge_busnr_callback(काष्ठा acpi_resource *resource, व्योम *data)
अणु
	काष्ठा resource *res = data;
	काष्ठा acpi_resource_address64 address;
	acpi_status status;

	status = acpi_resource_to_address64(resource, &address);
	अगर (ACPI_FAILURE(status))
		वापस AE_OK;

	अगर ((address.address.address_length > 0) &&
	    (address.resource_type == ACPI_BUS_NUMBER_RANGE)) अणु
		res->start = address.address.minimum;
		res->end = address.address.minimum + address.address.address_length - 1;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल acpi_status try_get_root_bridge_busnr(acpi_handle handle,
					     काष्ठा resource *res)
अणु
	acpi_status status;

	res->start = -1;
	status =
	    acpi_walk_resources(handle, METHOD_NAME__CRS,
				get_root_bridge_busnr_callback, res);
	अगर (ACPI_FAILURE(status))
		वापस status;
	अगर (res->start == -1)
		वापस AE_ERROR;
	वापस AE_OK;
पूर्ण

काष्ठा pci_osc_bit_काष्ठा अणु
	u32 bit;
	अक्षर *desc;
पूर्ण;

अटल काष्ठा pci_osc_bit_काष्ठा pci_osc_support_bit[] = अणु
	अणु OSC_PCI_EXT_CONFIG_SUPPORT, "ExtendedConfig" पूर्ण,
	अणु OSC_PCI_ASPM_SUPPORT, "ASPM" पूर्ण,
	अणु OSC_PCI_CLOCK_PM_SUPPORT, "ClockPM" पूर्ण,
	अणु OSC_PCI_SEGMENT_GROUPS_SUPPORT, "Segments" पूर्ण,
	अणु OSC_PCI_MSI_SUPPORT, "MSI" पूर्ण,
	अणु OSC_PCI_EDR_SUPPORT, "EDR" पूर्ण,
	अणु OSC_PCI_HPX_TYPE_3_SUPPORT, "HPX-Type3" पूर्ण,
पूर्ण;

अटल काष्ठा pci_osc_bit_काष्ठा pci_osc_control_bit[] = अणु
	अणु OSC_PCI_EXPRESS_NATIVE_HP_CONTROL, "PCIeHotplug" पूर्ण,
	अणु OSC_PCI_SHPC_NATIVE_HP_CONTROL, "SHPCHotplug" पूर्ण,
	अणु OSC_PCI_EXPRESS_PME_CONTROL, "PME" पूर्ण,
	अणु OSC_PCI_EXPRESS_AER_CONTROL, "AER" पूर्ण,
	अणु OSC_PCI_EXPRESS_CAPABILITY_CONTROL, "PCIeCapability" पूर्ण,
	अणु OSC_PCI_EXPRESS_LTR_CONTROL, "LTR" पूर्ण,
	अणु OSC_PCI_EXPRESS_DPC_CONTROL, "DPC" पूर्ण,
पूर्ण;

अटल व्योम decode_osc_bits(काष्ठा acpi_pci_root *root, अक्षर *msg, u32 word,
			    काष्ठा pci_osc_bit_काष्ठा *table, पूर्णांक size)
अणु
	अक्षर buf[80];
	पूर्णांक i, len = 0;
	काष्ठा pci_osc_bit_काष्ठा *entry;

	buf[0] = '\0';
	क्रम (i = 0, entry = table; i < size; i++, entry++)
		अगर (word & entry->bit)
			len += scnम_लिखो(buf + len, माप(buf) - len, "%s%s",
					len ? " " : "", entry->desc);

	dev_info(&root->device->dev, "_OSC: %s [%s]\n", msg, buf);
पूर्ण

अटल व्योम decode_osc_support(काष्ठा acpi_pci_root *root, अक्षर *msg, u32 word)
अणु
	decode_osc_bits(root, msg, word, pci_osc_support_bit,
			ARRAY_SIZE(pci_osc_support_bit));
पूर्ण

अटल व्योम decode_osc_control(काष्ठा acpi_pci_root *root, अक्षर *msg, u32 word)
अणु
	decode_osc_bits(root, msg, word, pci_osc_control_bit,
			ARRAY_SIZE(pci_osc_control_bit));
पूर्ण

अटल u8 pci_osc_uuid_str[] = "33DB4D5B-1FF7-401C-9657-7441C03DD766";

अटल acpi_status acpi_pci_run_osc(acpi_handle handle,
				    स्थिर u32 *capbuf, u32 *retval)
अणु
	काष्ठा acpi_osc_context context = अणु
		.uuid_str = pci_osc_uuid_str,
		.rev = 1,
		.cap.length = 12,
		.cap.poपूर्णांकer = (व्योम *)capbuf,
	पूर्ण;
	acpi_status status;

	status = acpi_run_osc(handle, &context);
	अगर (ACPI_SUCCESS(status)) अणु
		*retval = *((u32 *)(context.ret.poपूर्णांकer + 8));
		kमुक्त(context.ret.poपूर्णांकer);
	पूर्ण
	वापस status;
पूर्ण

अटल acpi_status acpi_pci_query_osc(काष्ठा acpi_pci_root *root,
					u32 support,
					u32 *control)
अणु
	acpi_status status;
	u32 result, capbuf[3];

	support &= OSC_PCI_SUPPORT_MASKS;
	support |= root->osc_support_set;

	capbuf[OSC_QUERY_DWORD] = OSC_QUERY_ENABLE;
	capbuf[OSC_SUPPORT_DWORD] = support;
	अगर (control) अणु
		*control &= OSC_PCI_CONTROL_MASKS;
		capbuf[OSC_CONTROL_DWORD] = *control | root->osc_control_set;
	पूर्ण अन्यथा अणु
		/* Run _OSC query only with existing controls. */
		capbuf[OSC_CONTROL_DWORD] = root->osc_control_set;
	पूर्ण

	status = acpi_pci_run_osc(root->device->handle, capbuf, &result);
	अगर (ACPI_SUCCESS(status)) अणु
		root->osc_support_set = support;
		अगर (control)
			*control = result;
	पूर्ण
	वापस status;
पूर्ण

अटल acpi_status acpi_pci_osc_support(काष्ठा acpi_pci_root *root, u32 flags)
अणु
	वापस acpi_pci_query_osc(root, flags, शून्य);
पूर्ण

काष्ठा acpi_pci_root *acpi_pci_find_root(acpi_handle handle)
अणु
	काष्ठा acpi_pci_root *root;
	काष्ठा acpi_device *device;

	अगर (acpi_bus_get_device(handle, &device) ||
	    acpi_match_device_ids(device, root_device_ids))
		वापस शून्य;

	root = acpi_driver_data(device);

	वापस root;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_pci_find_root);

काष्ठा acpi_handle_node अणु
	काष्ठा list_head node;
	acpi_handle handle;
पूर्ण;

/**
 * acpi_get_pci_dev - convert ACPI CA handle to काष्ठा pci_dev
 * @handle: the handle in question
 *
 * Given an ACPI CA handle, the desired PCI device is located in the
 * list of PCI devices.
 *
 * If the device is found, its reference count is increased and this
 * function वापसs a poपूर्णांकer to its data काष्ठाure.  The caller must
 * decrement the reference count by calling pci_dev_put().
 * If no device is found, %शून्य is वापसed.
 */
काष्ठा pci_dev *acpi_get_pci_dev(acpi_handle handle)
अणु
	पूर्णांक dev, fn;
	अचिन्हित दीर्घ दीर्घ adr;
	acpi_status status;
	acpi_handle phandle;
	काष्ठा pci_bus *pbus;
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा acpi_handle_node *node, *पंचांगp;
	काष्ठा acpi_pci_root *root;
	LIST_HEAD(device_list);

	/*
	 * Walk up the ACPI CA namespace until we reach a PCI root bridge.
	 */
	phandle = handle;
	जबतक (!acpi_is_root_bridge(phandle)) अणु
		node = kzalloc(माप(काष्ठा acpi_handle_node), GFP_KERNEL);
		अगर (!node)
			जाओ out;

		INIT_LIST_HEAD(&node->node);
		node->handle = phandle;
		list_add(&node->node, &device_list);

		status = acpi_get_parent(phandle, &phandle);
		अगर (ACPI_FAILURE(status))
			जाओ out;
	पूर्ण

	root = acpi_pci_find_root(phandle);
	अगर (!root)
		जाओ out;

	pbus = root->bus;

	/*
	 * Now, walk back करोwn the PCI device tree until we वापस to our
	 * original handle. Assumes that everything between the PCI root
	 * bridge and the device we're looking क्रम must be a P2P bridge.
	 */
	list_क्रम_each_entry(node, &device_list, node) अणु
		acpi_handle hnd = node->handle;
		status = acpi_evaluate_पूर्णांकeger(hnd, "_ADR", शून्य, &adr);
		अगर (ACPI_FAILURE(status))
			जाओ out;
		dev = (adr >> 16) & 0xffff;
		fn  = adr & 0xffff;

		pdev = pci_get_slot(pbus, PCI_DEVFN(dev, fn));
		अगर (!pdev || hnd == handle)
			अवरोध;

		pbus = pdev->subordinate;
		pci_dev_put(pdev);

		/*
		 * This function may be called क्रम a non-PCI device that has a
		 * PCI parent (eg. a disk under a PCI SATA controller).  In that
		 * हाल pdev->subordinate will be शून्य क्रम the parent.
		 */
		अगर (!pbus) अणु
			dev_dbg(&pdev->dev, "Not a PCI-to-PCI bridge\n");
			pdev = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	list_क्रम_each_entry_safe(node, पंचांगp, &device_list, node)
		kमुक्त(node);

	वापस pdev;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_get_pci_dev);

/**
 * acpi_pci_osc_control_set - Request control of PCI root _OSC features.
 * @handle: ACPI handle of a PCI root bridge (or PCIe Root Complex).
 * @mask: Mask of _OSC bits to request control of, place to store control mask.
 * @req: Mask of _OSC bits the control of is essential to the caller.
 *
 * Run _OSC query क्रम @mask and अगर that is successful, compare the वापसed
 * mask of control bits with @req.  If all of the @req bits are set in the
 * वापसed mask, run _OSC request क्रम it.
 *
 * The variable at the @mask address may be modअगरied regardless of whether or
 * not the function वापसs success.  On success it will contain the mask of
 * _OSC bits the BIOS has granted control of, but its contents are meaningless
 * on failure.
 **/
अटल acpi_status acpi_pci_osc_control_set(acpi_handle handle, u32 *mask, u32 req)
अणु
	काष्ठा acpi_pci_root *root;
	acpi_status status;
	u32 ctrl, capbuf[3];

	अगर (!mask)
		वापस AE_BAD_PARAMETER;

	ctrl = *mask & OSC_PCI_CONTROL_MASKS;
	अगर ((ctrl & req) != req)
		वापस AE_TYPE;

	root = acpi_pci_find_root(handle);
	अगर (!root)
		वापस AE_NOT_EXIST;

	*mask = ctrl | root->osc_control_set;
	/* No need to evaluate _OSC अगर the control was alपढ़ोy granted. */
	अगर ((root->osc_control_set & ctrl) == ctrl)
		वापस AE_OK;

	/* Need to check the available controls bits beक्रमe requesting them. */
	जबतक (*mask) अणु
		status = acpi_pci_query_osc(root, root->osc_support_set, mask);
		अगर (ACPI_FAILURE(status))
			वापस status;
		अगर (ctrl == *mask)
			अवरोध;
		decode_osc_control(root, "platform does not support",
				   ctrl & ~(*mask));
		ctrl = *mask;
	पूर्ण

	अगर ((ctrl & req) != req) अणु
		decode_osc_control(root, "not requesting control; platform does not support",
				   req & ~(ctrl));
		वापस AE_SUPPORT;
	पूर्ण

	capbuf[OSC_QUERY_DWORD] = 0;
	capbuf[OSC_SUPPORT_DWORD] = root->osc_support_set;
	capbuf[OSC_CONTROL_DWORD] = ctrl;
	status = acpi_pci_run_osc(handle, capbuf, mask);
	अगर (ACPI_FAILURE(status))
		वापस status;

	root->osc_control_set = *mask;
	वापस AE_OK;
पूर्ण

अटल व्योम negotiate_os_control(काष्ठा acpi_pci_root *root, पूर्णांक *no_aspm,
				 bool is_pcie)
अणु
	u32 support, control, requested;
	acpi_status status;
	काष्ठा acpi_device *device = root->device;
	acpi_handle handle = device->handle;

	/*
	 * Apple always वापस failure on _OSC calls when _OSI("Darwin") has
	 * been called successfully. We know the feature set supported by the
	 * platक्रमm, so aव्योम calling _OSC at all
	 */
	अगर (x86_apple_machine) अणु
		root->osc_control_set = ~OSC_PCI_EXPRESS_PME_CONTROL;
		decode_osc_control(root, "OS assumes control of",
				   root->osc_control_set);
		वापस;
	पूर्ण

	/*
	 * All supported architectures that use ACPI have support क्रम
	 * PCI करोमुख्यs, so we indicate this in _OSC support capabilities.
	 */
	support = OSC_PCI_SEGMENT_GROUPS_SUPPORT;
	support |= OSC_PCI_HPX_TYPE_3_SUPPORT;
	अगर (pci_ext_cfg_avail())
		support |= OSC_PCI_EXT_CONFIG_SUPPORT;
	अगर (pcie_aspm_support_enabled())
		support |= OSC_PCI_ASPM_SUPPORT | OSC_PCI_CLOCK_PM_SUPPORT;
	अगर (pci_msi_enabled())
		support |= OSC_PCI_MSI_SUPPORT;
	अगर (IS_ENABLED(CONFIG_PCIE_EDR))
		support |= OSC_PCI_EDR_SUPPORT;

	decode_osc_support(root, "OS supports", support);
	status = acpi_pci_osc_support(root, support);
	अगर (ACPI_FAILURE(status)) अणु
		*no_aspm = 1;

		/* _OSC is optional क्रम PCI host bridges */
		अगर ((status == AE_NOT_FOUND) && !is_pcie)
			वापस;

		dev_info(&device->dev, "_OSC: platform retains control of PCIe features (%s)\n",
			 acpi_क्रमmat_exception(status));
		वापस;
	पूर्ण

	अगर (pcie_ports_disabled) अणु
		dev_info(&device->dev, "PCIe port services disabled; not requesting _OSC control\n");
		वापस;
	पूर्ण

	अगर ((support & ACPI_PCIE_REQ_SUPPORT) != ACPI_PCIE_REQ_SUPPORT) अणु
		decode_osc_support(root, "not requesting OS control; OS requires",
				   ACPI_PCIE_REQ_SUPPORT);
		वापस;
	पूर्ण

	control = OSC_PCI_EXPRESS_CAPABILITY_CONTROL
		| OSC_PCI_EXPRESS_PME_CONTROL;

	अगर (IS_ENABLED(CONFIG_PCIEASPM))
		control |= OSC_PCI_EXPRESS_LTR_CONTROL;

	अगर (IS_ENABLED(CONFIG_HOTPLUG_PCI_PCIE))
		control |= OSC_PCI_EXPRESS_NATIVE_HP_CONTROL;

	अगर (IS_ENABLED(CONFIG_HOTPLUG_PCI_SHPC))
		control |= OSC_PCI_SHPC_NATIVE_HP_CONTROL;

	अगर (pci_aer_available())
		control |= OSC_PCI_EXPRESS_AER_CONTROL;

	/*
	 * Per the Downstream Port Containment Related Enhancements ECN to
	 * the PCI Firmware Spec, r3.2, sec 4.5.1, table 4-5,
	 * OSC_PCI_EXPRESS_DPC_CONTROL indicates the OS supports both DPC
	 * and EDR.
	 */
	अगर (IS_ENABLED(CONFIG_PCIE_DPC) && IS_ENABLED(CONFIG_PCIE_EDR))
		control |= OSC_PCI_EXPRESS_DPC_CONTROL;

	requested = control;
	status = acpi_pci_osc_control_set(handle, &control,
					  OSC_PCI_EXPRESS_CAPABILITY_CONTROL);
	अगर (ACPI_SUCCESS(status)) अणु
		decode_osc_control(root, "OS now controls", control);
		अगर (acpi_gbl_FADT.boot_flags & ACPI_FADT_NO_ASPM) अणु
			/*
			 * We have ASPM control, but the FADT indicates that
			 * it's unsupported. Leave existing configuration
			 * पूर्णांकact and prevent the OS from touching it.
			 */
			dev_info(&device->dev, "FADT indicates ASPM is unsupported, using BIOS configuration\n");
			*no_aspm = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		decode_osc_control(root, "OS requested", requested);
		decode_osc_control(root, "platform willing to grant", control);
		dev_info(&device->dev, "_OSC: platform retains control of PCIe features (%s)\n",
			acpi_क्रमmat_exception(status));

		/*
		 * We want to disable ASPM here, but aspm_disabled
		 * needs to reमुख्य in its state from boot so that we
		 * properly handle PCIe 1.1 devices.  So we set this
		 * flag here, to defer the action until after the ACPI
		 * root scan.
		 */
		*no_aspm = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pci_root_add(काष्ठा acpi_device *device,
			     स्थिर काष्ठा acpi_device_id *not_used)
अणु
	अचिन्हित दीर्घ दीर्घ segment, bus;
	acpi_status status;
	पूर्णांक result;
	काष्ठा acpi_pci_root *root;
	acpi_handle handle = device->handle;
	पूर्णांक no_aspm = 0;
	bool hotadd = प्रणाली_state == SYSTEM_RUNNING;
	bool is_pcie;

	root = kzalloc(माप(काष्ठा acpi_pci_root), GFP_KERNEL);
	अगर (!root)
		वापस -ENOMEM;

	segment = 0;
	status = acpi_evaluate_पूर्णांकeger(handle, METHOD_NAME__SEG, शून्य,
				       &segment);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		dev_err(&device->dev,  "can't evaluate _SEG\n");
		result = -ENODEV;
		जाओ end;
	पूर्ण

	/* Check _CRS first, then _BBN.  If no _BBN, शेष to zero. */
	root->secondary.flags = IORESOURCE_BUS;
	status = try_get_root_bridge_busnr(handle, &root->secondary);
	अगर (ACPI_FAILURE(status)) अणु
		/*
		 * We need both the start and end of the करोwnstream bus range
		 * to पूर्णांकerpret _CBA (MMCONFIG base address), so it really is
		 * supposed to be in _CRS.  If we करोn't find it there, all we
		 * can करो is assume [_BBN-0xFF] or [0-0xFF].
		 */
		root->secondary.end = 0xFF;
		dev_warn(&device->dev,
			 FW_BUG "no secondary bus range in _CRS\n");
		status = acpi_evaluate_पूर्णांकeger(handle, METHOD_NAME__BBN,
					       शून्य, &bus);
		अगर (ACPI_SUCCESS(status))
			root->secondary.start = bus;
		अन्यथा अगर (status == AE_NOT_FOUND)
			root->secondary.start = 0;
		अन्यथा अणु
			dev_err(&device->dev, "can't evaluate _BBN\n");
			result = -ENODEV;
			जाओ end;
		पूर्ण
	पूर्ण

	root->device = device;
	root->segment = segment & 0xFFFF;
	म_नकल(acpi_device_name(device), ACPI_PCI_ROOT_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PCI_ROOT_CLASS);
	device->driver_data = root;

	अगर (hotadd && dmar_device_add(handle)) अणु
		result = -ENXIO;
		जाओ end;
	पूर्ण

	pr_info(PREFIX "%s [%s] (domain %04x %pR)\n",
	       acpi_device_name(device), acpi_device_bid(device),
	       root->segment, &root->secondary);

	root->mcfg_addr = acpi_pci_root_get_mcfg_addr(handle);

	is_pcie = म_भेद(acpi_device_hid(device), "PNP0A08") == 0;
	negotiate_os_control(root, &no_aspm, is_pcie);

	/*
	 * TBD: Need PCI पूर्णांकerface क्रम क्रमागतeration/configuration of roots.
	 */

	/*
	 * Scan the Root Bridge
	 * --------------------
	 * Must करो this prior to any attempt to bind the root device, as the
	 * PCI namespace करोes not get created until this call is made (and
	 * thus the root bridge's pci_dev करोes not exist).
	 */
	root->bus = pci_acpi_scan_root(root);
	अगर (!root->bus) अणु
		dev_err(&device->dev,
			"Bus %04x:%02x not present in PCI namespace\n",
			root->segment, (अचिन्हित पूर्णांक)root->secondary.start);
		device->driver_data = शून्य;
		result = -ENODEV;
		जाओ हटाओ_dmar;
	पूर्ण

	अगर (no_aspm)
		pcie_no_aspm();

	pci_acpi_add_bus_pm_notअगरier(device);
	device_set_wakeup_capable(root->bus->bridge, device->wakeup.flags.valid);

	अगर (hotadd) अणु
		pcibios_resource_survey_bus(root->bus);
		pci_assign_unasचिन्हित_root_bus_resources(root->bus);
		/*
		 * This is only called क्रम the hotadd हाल. For the boot-समय
		 * हाल, we need to रुको until after PCI initialization in
		 * order to deal with IOAPICs mapped in on a PCI BAR.
		 *
		 * This is currently x86-specअगरic, because acpi_ioapic_add()
		 * is an empty function without CONFIG_ACPI_HOTPLUG_IOAPIC.
		 * And CONFIG_ACPI_HOTPLUG_IOAPIC depends on CONFIG_X86_IO_APIC
		 * (see drivers/acpi/Kconfig).
		 */
		acpi_ioapic_add(root->device->handle);
	पूर्ण

	pci_lock_rescan_हटाओ();
	pci_bus_add_devices(root->bus);
	pci_unlock_rescan_हटाओ();
	वापस 1;

हटाओ_dmar:
	अगर (hotadd)
		dmar_device_हटाओ(handle);
end:
	kमुक्त(root);
	वापस result;
पूर्ण

अटल व्योम acpi_pci_root_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_pci_root *root = acpi_driver_data(device);

	pci_lock_rescan_हटाओ();

	pci_stop_root_bus(root->bus);

	pci_ioapic_हटाओ(root);
	device_set_wakeup_capable(root->bus->bridge, false);
	pci_acpi_हटाओ_bus_pm_notअगरier(device);

	pci_हटाओ_root_bus(root->bus);
	WARN_ON(acpi_ioapic_हटाओ(root));

	dmar_device_हटाओ(device->handle);

	pci_unlock_rescan_हटाओ();

	kमुक्त(root);
पूर्ण

/*
 * Following code to support acpi_pci_root_create() is copied from
 * arch/x86/pci/acpi.c and modअगरied so it could be reused by x86, IA64
 * and ARM64.
 */
अटल व्योम acpi_pci_root_validate_resources(काष्ठा device *dev,
					     काष्ठा list_head *resources,
					     अचिन्हित दीर्घ type)
अणु
	LIST_HEAD(list);
	काष्ठा resource *res1, *res2, *root = शून्य;
	काष्ठा resource_entry *पंचांगp, *entry, *entry2;

	BUG_ON((type & (IORESOURCE_MEM | IORESOURCE_IO)) == 0);
	root = (type & IORESOURCE_MEM) ? &iomem_resource : &ioport_resource;

	list_splice_init(resources, &list);
	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &list) अणु
		bool मुक्त = false;
		resource_माप_प्रकार end;

		res1 = entry->res;
		अगर (!(res1->flags & type))
			जाओ next;

		/* Exclude non-addressable range or non-addressable portion */
		end = min(res1->end, root->end);
		अगर (end <= res1->start) अणु
			dev_info(dev, "host bridge window %pR (ignored, not CPU addressable)\n",
				 res1);
			मुक्त = true;
			जाओ next;
		पूर्ण अन्यथा अगर (res1->end != end) अणु
			dev_info(dev, "host bridge window %pR ([%#llx-%#llx] ignored, not CPU addressable)\n",
				 res1, (अचिन्हित दीर्घ दीर्घ)end + 1,
				 (अचिन्हित दीर्घ दीर्घ)res1->end);
			res1->end = end;
		पूर्ण

		resource_list_क्रम_each_entry(entry2, resources) अणु
			res2 = entry2->res;
			अगर (!(res2->flags & type))
				जारी;

			/*
			 * I करोn't like throwing away winकरोws because then
			 * our resources no दीर्घer match the ACPI _CRS, but
			 * the kernel resource tree करोesn't allow overlaps.
			 */
			अगर (resource_जोड़(res1, res2, res2)) अणु
				dev_info(dev, "host bridge window expanded to %pR; %pR ignored\n",
					 res2, res1);
				मुक्त = true;
				जाओ next;
			पूर्ण
		पूर्ण

next:
		resource_list_del(entry);
		अगर (मुक्त)
			resource_list_मुक्त_entry(entry);
		अन्यथा
			resource_list_add_tail(entry, resources);
	पूर्ण
पूर्ण

अटल व्योम acpi_pci_root_remap_iospace(काष्ठा fwnode_handle *fwnode,
			काष्ठा resource_entry *entry)
अणु
#अगर_घोषित PCI_IOBASE
	काष्ठा resource *res = entry->res;
	resource_माप_प्रकार cpu_addr = res->start;
	resource_माप_प्रकार pci_addr = cpu_addr - entry->offset;
	resource_माप_प्रकार length = resource_size(res);
	अचिन्हित दीर्घ port;

	अगर (pci_रेजिस्टर_io_range(fwnode, cpu_addr, length))
		जाओ err;

	port = pci_address_to_pio(cpu_addr);
	अगर (port == (अचिन्हित दीर्घ)-1)
		जाओ err;

	res->start = port;
	res->end = port + length - 1;
	entry->offset = port - pci_addr;

	अगर (pci_remap_iospace(res, cpu_addr) < 0)
		जाओ err;

	pr_info("Remapped I/O %pa to %pR\n", &cpu_addr, res);
	वापस;
err:
	res->flags |= IORESOURCE_DISABLED;
#पूर्ण_अगर
पूर्ण

पूर्णांक acpi_pci_probe_root_resources(काष्ठा acpi_pci_root_info *info)
अणु
	पूर्णांक ret;
	काष्ठा list_head *list = &info->resources;
	काष्ठा acpi_device *device = info->bridge;
	काष्ठा resource_entry *entry, *पंचांगp;
	अचिन्हित दीर्घ flags;

	flags = IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_MEM_8AND16BIT;
	ret = acpi_dev_get_resources(device, list,
				     acpi_dev_filter_resource_type_cb,
				     (व्योम *)flags);
	अगर (ret < 0)
		dev_warn(&device->dev,
			 "failed to parse _CRS method, error code %d\n", ret);
	अन्यथा अगर (ret == 0)
		dev_dbg(&device->dev,
			"no IO and memory resources present in _CRS\n");
	अन्यथा अणु
		resource_list_क्रम_each_entry_safe(entry, पंचांगp, list) अणु
			अगर (entry->res->flags & IORESOURCE_IO)
				acpi_pci_root_remap_iospace(&device->fwnode,
						entry);

			अगर (entry->res->flags & IORESOURCE_DISABLED)
				resource_list_destroy_entry(entry);
			अन्यथा
				entry->res->name = info->name;
		पूर्ण
		acpi_pci_root_validate_resources(&device->dev, list,
						 IORESOURCE_MEM);
		acpi_pci_root_validate_resources(&device->dev, list,
						 IORESOURCE_IO);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pci_acpi_root_add_resources(काष्ठा acpi_pci_root_info *info)
अणु
	काष्ठा resource_entry *entry, *पंचांगp;
	काष्ठा resource *res, *conflict, *root = शून्य;

	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &info->resources) अणु
		res = entry->res;
		अगर (res->flags & IORESOURCE_MEM)
			root = &iomem_resource;
		अन्यथा अगर (res->flags & IORESOURCE_IO)
			root = &ioport_resource;
		अन्यथा
			जारी;

		/*
		 * Some legacy x86 host bridge drivers use iomem_resource and
		 * ioport_resource as शेष resource pool, skip it.
		 */
		अगर (res == root)
			जारी;

		conflict = insert_resource_conflict(root, res);
		अगर (conflict) अणु
			dev_info(&info->bridge->dev,
				 "ignoring host bridge window %pR (conflicts with %s %pR)\n",
				 res, conflict->name, conflict);
			resource_list_destroy_entry(entry);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __acpi_pci_root_release_info(काष्ठा acpi_pci_root_info *info)
अणु
	काष्ठा resource *res;
	काष्ठा resource_entry *entry, *पंचांगp;

	अगर (!info)
		वापस;

	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &info->resources) अणु
		res = entry->res;
		अगर (res->parent &&
		    (res->flags & (IORESOURCE_MEM | IORESOURCE_IO)))
			release_resource(res);
		resource_list_destroy_entry(entry);
	पूर्ण

	info->ops->release_info(info);
पूर्ण

अटल व्योम acpi_pci_root_release_info(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा resource *res;
	काष्ठा resource_entry *entry;

	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		res = entry->res;
		अगर (res->flags & IORESOURCE_IO)
			pci_unmap_iospace(res);
		अगर (res->parent &&
		    (res->flags & (IORESOURCE_MEM | IORESOURCE_IO)))
			release_resource(res);
	पूर्ण
	__acpi_pci_root_release_info(bridge->release_data);
पूर्ण

काष्ठा pci_bus *acpi_pci_root_create(काष्ठा acpi_pci_root *root,
				     काष्ठा acpi_pci_root_ops *ops,
				     काष्ठा acpi_pci_root_info *info,
				     व्योम *sysdata)
अणु
	पूर्णांक ret, busnum = root->secondary.start;
	काष्ठा acpi_device *device = root->device;
	पूर्णांक node = acpi_get_node(device->handle);
	काष्ठा pci_bus *bus;
	काष्ठा pci_host_bridge *host_bridge;
	जोड़ acpi_object *obj;

	info->root = root;
	info->bridge = device;
	info->ops = ops;
	INIT_LIST_HEAD(&info->resources);
	snम_लिखो(info->name, माप(info->name), "PCI Bus %04x:%02x",
		 root->segment, busnum);

	अगर (ops->init_info && ops->init_info(info))
		जाओ out_release_info;
	अगर (ops->prepare_resources)
		ret = ops->prepare_resources(info);
	अन्यथा
		ret = acpi_pci_probe_root_resources(info);
	अगर (ret < 0)
		जाओ out_release_info;

	pci_acpi_root_add_resources(info);
	pci_add_resource(&info->resources, &root->secondary);
	bus = pci_create_root_bus(शून्य, busnum, ops->pci_ops,
				  sysdata, &info->resources);
	अगर (!bus)
		जाओ out_release_info;

	host_bridge = to_pci_host_bridge(bus->bridge);
	अगर (!(root->osc_control_set & OSC_PCI_EXPRESS_NATIVE_HP_CONTROL))
		host_bridge->native_pcie_hotplug = 0;
	अगर (!(root->osc_control_set & OSC_PCI_SHPC_NATIVE_HP_CONTROL))
		host_bridge->native_shpc_hotplug = 0;
	अगर (!(root->osc_control_set & OSC_PCI_EXPRESS_AER_CONTROL))
		host_bridge->native_aer = 0;
	अगर (!(root->osc_control_set & OSC_PCI_EXPRESS_PME_CONTROL))
		host_bridge->native_pme = 0;
	अगर (!(root->osc_control_set & OSC_PCI_EXPRESS_LTR_CONTROL))
		host_bridge->native_ltr = 0;
	अगर (!(root->osc_control_set & OSC_PCI_EXPRESS_DPC_CONTROL))
		host_bridge->native_dpc = 0;

	/*
	 * Evaluate the "PCI Boot Configuration" _DSM Function.  If it
	 * exists and वापसs 0, we must preserve any PCI resource
	 * assignments made by firmware क्रम this host bridge.
	 */
	obj = acpi_evaluate_dsm(ACPI_HANDLE(bus->bridge), &pci_acpi_dsm_guid, 1,
				DSM_PCI_PRESERVE_BOOT_CONFIG, शून्य);
	अगर (obj && obj->type == ACPI_TYPE_INTEGER && obj->पूर्णांकeger.value == 0)
		host_bridge->preserve_config = 1;
	ACPI_FREE(obj);

	pci_scan_child_bus(bus);
	pci_set_host_bridge_release(host_bridge, acpi_pci_root_release_info,
				    info);
	अगर (node != NUMA_NO_NODE)
		dev_prपूर्णांकk(KERN_DEBUG, &bus->dev, "on NUMA node %d\n", node);
	वापस bus;

out_release_info:
	__acpi_pci_root_release_info(info);
	वापस शून्य;
पूर्ण

व्योम __init acpi_pci_root_init(व्योम)
अणु
	acpi_hest_init();
	अगर (acpi_pci_disabled)
		वापस;

	pci_acpi_crs_quirks();
	acpi_scan_add_handler_with_hotplug(&pci_root_handler, "pci_root");
पूर्ण
