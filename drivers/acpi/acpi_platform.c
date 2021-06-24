<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI support क्रम platक्रमm bus type.
 *
 * Copyright (C) 2012, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *          Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 *          Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा acpi_device_id क्रमbidden_id_list[] = अणु
	अणु"PNP0000",  0पूर्ण,	/* PIC */
	अणु"PNP0100",  0पूर्ण,	/* Timer */
	अणु"PNP0200",  0पूर्ण,	/* AT DMA Controller */
	अणु"ACPI0009", 0पूर्ण,	/* IOxAPIC */
	अणु"ACPI000A", 0पूर्ण,	/* IOAPIC */
	अणु"SMB0001",  0पूर्ण,	/* ACPI SMBUS भव device */
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *acpi_platक्रमm_device_find_by_companion(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_acpi_dev(&platक्रमm_bus_type, adev);
	वापस dev ? to_platक्रमm_device(dev) : शून्य;
पूर्ण

अटल पूर्णांक acpi_platक्रमm_device_हटाओ_notअगरy(काष्ठा notअगरier_block *nb,
					      अचिन्हित दीर्घ value, व्योम *arg)
अणु
	काष्ठा acpi_device *adev = arg;
	काष्ठा platक्रमm_device *pdev;

	चयन (value) अणु
	हाल ACPI_RECONFIG_DEVICE_ADD:
		/* Nothing to करो here */
		अवरोध;
	हाल ACPI_RECONFIG_DEVICE_REMOVE:
		अगर (!acpi_device_क्रमागतerated(adev))
			अवरोध;

		pdev = acpi_platक्रमm_device_find_by_companion(adev);
		अगर (!pdev)
			अवरोध;

		platक्रमm_device_unरेजिस्टर(pdev);
		put_device(&pdev->dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block acpi_platक्रमm_notअगरier = अणु
	.notअगरier_call = acpi_platक्रमm_device_हटाओ_notअगरy,
पूर्ण;

अटल व्योम acpi_platक्रमm_fill_resource(काष्ठा acpi_device *adev,
	स्थिर काष्ठा resource *src, काष्ठा resource *dest)
अणु
	काष्ठा device *parent;

	*dest = *src;

	/*
	 * If the device has parent we need to take its resources पूर्णांकo
	 * account as well because this device might consume part of those.
	 */
	parent = acpi_get_first_physical_node(adev->parent);
	अगर (parent && dev_is_pci(parent))
		dest->parent = pci_find_resource(to_pci_dev(parent), dest);
पूर्ण

/**
 * acpi_create_platक्रमm_device - Create platक्रमm device क्रम ACPI device node
 * @adev: ACPI device node to create a platक्रमm device क्रम.
 * @properties: Optional collection of build-in properties.
 *
 * Check अगर the given @adev can be represented as a platक्रमm device and, अगर
 * that's the हाल, create and रेजिस्टर a platक्रमm device, populate its common
 * resources and वापसs a poपूर्णांकer to it.  Otherwise, वापस %शून्य.
 *
 * Name of the platक्रमm device will be the same as @adev's.
 */
काष्ठा platक्रमm_device *acpi_create_platक्रमm_device(काष्ठा acpi_device *adev,
					काष्ठा property_entry *properties)
अणु
	काष्ठा platक्रमm_device *pdev = शून्य;
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा resource_entry *rentry;
	काष्ठा list_head resource_list;
	काष्ठा resource *resources = शून्य;
	पूर्णांक count;

	/* If the ACPI node alपढ़ोy has a physical device attached, skip it. */
	अगर (adev->physical_node_count)
		वापस शून्य;

	अगर (!acpi_match_device_ids(adev, क्रमbidden_id_list))
		वापस ERR_PTR(-EINVAL);

	INIT_LIST_HEAD(&resource_list);
	count = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (count < 0) अणु
		वापस शून्य;
	पूर्ण अन्यथा अगर (count > 0) अणु
		resources = kसुस्मृति(count, माप(काष्ठा resource),
				    GFP_KERNEL);
		अगर (!resources) अणु
			dev_err(&adev->dev, "No memory for resources\n");
			acpi_dev_मुक्त_resource_list(&resource_list);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		count = 0;
		list_क्रम_each_entry(rentry, &resource_list, node)
			acpi_platक्रमm_fill_resource(adev, rentry->res,
						    &resources[count++]);

		acpi_dev_मुक्त_resource_list(&resource_list);
	पूर्ण

	स_रखो(&pdevinfo, 0, माप(pdevinfo));
	/*
	 * If the ACPI node has a parent and that parent has a physical device
	 * attached to it, that physical device should be the parent of the
	 * platक्रमm device we are about to create.
	 */
	pdevinfo.parent = adev->parent ?
		acpi_get_first_physical_node(adev->parent) : शून्य;
	pdevinfo.name = dev_name(&adev->dev);
	pdevinfo.id = -1;
	pdevinfo.res = resources;
	pdevinfo.num_res = count;
	pdevinfo.fwnode = acpi_fwnode_handle(adev);
	pdevinfo.properties = properties;

	अगर (acpi_dma_supported(adev))
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
	अन्यथा
		pdevinfo.dma_mask = 0;

	pdev = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	अगर (IS_ERR(pdev))
		dev_err(&adev->dev, "platform device creation failed: %ld\n",
			PTR_ERR(pdev));
	अन्यथा अणु
		set_dev_node(&pdev->dev, acpi_get_node(adev->handle));
		dev_dbg(&adev->dev, "created platform device %s\n",
			dev_name(&pdev->dev));
	पूर्ण

	kमुक्त(resources);

	वापस pdev;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_create_platक्रमm_device);

व्योम __init acpi_platक्रमm_init(व्योम)
अणु
	acpi_reconfig_notअगरier_रेजिस्टर(&acpi_platक्रमm_notअगरier);
पूर्ण
