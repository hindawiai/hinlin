<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOAPIC/IOxAPIC/IOSAPIC driver
 *
 * Copyright (C) 2009 Fujitsu Limited.
 * (c) Copyright 2009 Hewlett-Packard Development Company, L.P.
 *
 * Copyright (C) 2014 Intel Corporation
 *
 * Based on original drivers/pci/ioapic.c
 *	Yinghai Lu <yinghai@kernel.org>
 *	Jiang Liu <jiang.liu@पूर्णांकel.com>
 */

/*
 * This driver manages I/O APICs added by hotplug after boot.
 * We try to claim all I/O APIC devices, but those present at boot were
 * रेजिस्टरed when we parsed the ACPI MADT.
 */

#घोषणा pr_fmt(fmt) "ACPI: IOAPIC: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <acpi/acpi.h>

काष्ठा acpi_pci_ioapic अणु
	acpi_handle	root_handle;
	acpi_handle	handle;
	u32		gsi_base;
	काष्ठा resource	res;
	काष्ठा pci_dev	*pdev;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(ioapic_list);
अटल DEFINE_MUTEX(ioapic_list_lock);

अटल acpi_status setup_res(काष्ठा acpi_resource *acpi_res, व्योम *data)
अणु
	काष्ठा resource *res = data;
	काष्ठा resource_win win;

	/*
	 * We might assign this to 'res' later, make sure all poपूर्णांकers are
	 * cleared beक्रमe the resource is added to the global list
	 */
	स_रखो(&win, 0, माप(win));

	res->flags = 0;
	अगर (acpi_dev_filter_resource_type(acpi_res, IORESOURCE_MEM))
		वापस AE_OK;

	अगर (!acpi_dev_resource_memory(acpi_res, res)) अणु
		अगर (acpi_dev_resource_address_space(acpi_res, &win) ||
		    acpi_dev_resource_ext_address_space(acpi_res, &win))
			*res = win.res;
	पूर्ण
	अगर ((res->flags & IORESOURCE_PREFETCH) ||
	    (res->flags & IORESOURCE_DISABLED))
		res->flags = 0;

	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल bool acpi_is_ioapic(acpi_handle handle, अक्षर **type)
अणु
	acpi_status status;
	काष्ठा acpi_device_info *info;
	अक्षर *hid = शून्य;
	bool match = false;

	अगर (!acpi_has_method(handle, "_GSB"))
		वापस false;

	status = acpi_get_object_info(handle, &info);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (info->valid & ACPI_VALID_HID)
			hid = info->hardware_id.string;
		अगर (hid) अणु
			अगर (म_भेद(hid, "ACPI0009") == 0) अणु
				*type = "IOxAPIC";
				match = true;
			पूर्ण अन्यथा अगर (म_भेद(hid, "ACPI000A") == 0) अणु
				*type = "IOAPIC";
				match = true;
			पूर्ण
		पूर्ण
		kमुक्त(info);
	पूर्ण

	वापस match;
पूर्ण

अटल acpi_status handle_ioapic_add(acpi_handle handle, u32 lvl,
				     व्योम *context, व्योम **rv)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ gsi_base;
	काष्ठा acpi_pci_ioapic *ioapic;
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा resource *res = शून्य, *pci_res = शून्य, *crs_res;
	अक्षर *type = शून्य;

	अगर (!acpi_is_ioapic(handle, &type))
		वापस AE_OK;

	mutex_lock(&ioapic_list_lock);
	list_क्रम_each_entry(ioapic, &ioapic_list, list)
		अगर (ioapic->handle == handle) अणु
			mutex_unlock(&ioapic_list_lock);
			वापस AE_OK;
		पूर्ण

	status = acpi_evaluate_पूर्णांकeger(handle, "_GSB", शून्य, &gsi_base);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_warn(handle, "failed to evaluate _GSB method\n");
		जाओ निकास;
	पूर्ण

	ioapic = kzalloc(माप(*ioapic), GFP_KERNEL);
	अगर (!ioapic) अणु
		pr_err("cannot allocate memory for new IOAPIC\n");
		जाओ निकास;
	पूर्ण अन्यथा अणु
		ioapic->root_handle = (acpi_handle)context;
		ioapic->handle = handle;
		ioapic->gsi_base = (u32)gsi_base;
		INIT_LIST_HEAD(&ioapic->list);
	पूर्ण

	अगर (acpi_ioapic_रेजिस्टरed(handle, (u32)gsi_base))
		जाओ करोne;

	dev = acpi_get_pci_dev(handle);
	अगर (dev && pci_resource_len(dev, 0)) अणु
		अगर (pci_enable_device(dev) < 0)
			जाओ निकास_put;
		pci_set_master(dev);
		अगर (pci_request_region(dev, 0, type))
			जाओ निकास_disable;
		pci_res = &dev->resource[0];
		ioapic->pdev = dev;
	पूर्ण अन्यथा अणु
		pci_dev_put(dev);
		dev = शून्य;
	पूर्ण

	crs_res = &ioapic->res;
	acpi_walk_resources(handle, METHOD_NAME__CRS, setup_res, crs_res);
	crs_res->name = type;
	crs_res->flags |= IORESOURCE_BUSY;
	अगर (crs_res->flags == 0) अणु
		acpi_handle_warn(handle, "failed to get resource\n");
		जाओ निकास_release;
	पूर्ण अन्यथा अगर (insert_resource(&iomem_resource, crs_res)) अणु
		acpi_handle_warn(handle, "failed to insert resource\n");
		जाओ निकास_release;
	पूर्ण

	/* try pci resource first, then "_CRS" resource */
	res = pci_res;
	अगर (!res || !res->flags)
		res = crs_res;

	अगर (acpi_रेजिस्टर_ioapic(handle, res->start, (u32)gsi_base)) अणु
		acpi_handle_warn(handle, "failed to register IOAPIC\n");
		जाओ निकास_release;
	पूर्ण
करोne:
	list_add(&ioapic->list, &ioapic_list);
	mutex_unlock(&ioapic_list_lock);

	अगर (dev)
		dev_info(&dev->dev, "%s at %pR, GSI %u\n",
			 type, res, (u32)gsi_base);
	अन्यथा
		acpi_handle_info(handle, "%s at %pR, GSI %u\n",
				 type, res, (u32)gsi_base);

	वापस AE_OK;

निकास_release:
	अगर (dev)
		pci_release_region(dev, 0);
	अगर (ioapic->res.flags && ioapic->res.parent)
		release_resource(&ioapic->res);
निकास_disable:
	अगर (dev)
		pci_disable_device(dev);
निकास_put:
	pci_dev_put(dev);
	kमुक्त(ioapic);
निकास:
	mutex_unlock(&ioapic_list_lock);
	*(acpi_status *)rv = AE_ERROR;
	वापस AE_OK;
पूर्ण

पूर्णांक acpi_ioapic_add(acpi_handle root_handle)
अणु
	acpi_status status, retval = AE_OK;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, root_handle,
				     अच_पूर्णांक_उच्च, handle_ioapic_add, शून्य,
				     root_handle, (व्योम **)&retval);

	वापस ACPI_SUCCESS(status) && ACPI_SUCCESS(retval) ? 0 : -ENODEV;
पूर्ण

व्योम pci_ioapic_हटाओ(काष्ठा acpi_pci_root *root)
अणु
	काष्ठा acpi_pci_ioapic *ioapic, *पंचांगp;

	mutex_lock(&ioapic_list_lock);
	list_क्रम_each_entry_safe(ioapic, पंचांगp, &ioapic_list, list) अणु
		अगर (root->device->handle != ioapic->root_handle)
			जारी;
		अगर (ioapic->pdev) अणु
			pci_release_region(ioapic->pdev, 0);
			pci_disable_device(ioapic->pdev);
			pci_dev_put(ioapic->pdev);
		पूर्ण
	पूर्ण
	mutex_unlock(&ioapic_list_lock);
पूर्ण

पूर्णांक acpi_ioapic_हटाओ(काष्ठा acpi_pci_root *root)
अणु
	पूर्णांक retval = 0;
	काष्ठा acpi_pci_ioapic *ioapic, *पंचांगp;

	mutex_lock(&ioapic_list_lock);
	list_क्रम_each_entry_safe(ioapic, पंचांगp, &ioapic_list, list) अणु
		अगर (root->device->handle != ioapic->root_handle)
			जारी;
		अगर (acpi_unरेजिस्टर_ioapic(ioapic->handle, ioapic->gsi_base))
			retval = -EBUSY;
		अगर (ioapic->res.flags && ioapic->res.parent)
			release_resource(&ioapic->res);
		list_del(&ioapic->list);
		kमुक्त(ioapic);
	पूर्ण
	mutex_unlock(&ioapic_list_lock);

	वापस retval;
पूर्ण
