<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dev-path-parser.c - EFI Device Path parser
 * Copyright (C) 2016 Lukas Wunner <lukas@wunner.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License (version 2) as
 * published by the Free Software Foundation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/pci.h>

काष्ठा acpi_hid_uid अणु
	काष्ठा acpi_device_id hid[2];
	अक्षर uid[11]; /* अच_पूर्णांक_उच्च + null byte */
पूर्ण;

अटल पूर्णांक __init match_acpi_dev(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा acpi_hid_uid hid_uid = *(स्थिर काष्ठा acpi_hid_uid *)data;
	काष्ठा acpi_device *adev = to_acpi_device(dev);

	अगर (acpi_match_device_ids(adev, hid_uid.hid))
		वापस 0;

	अगर (adev->pnp.unique_id)
		वापस !म_भेद(adev->pnp.unique_id, hid_uid.uid);
	अन्यथा
		वापस !म_भेद("0", hid_uid.uid);
पूर्ण

अटल दीर्घ __init parse_acpi_path(स्थिर काष्ठा efi_dev_path *node,
				   काष्ठा device *parent, काष्ठा device **child)
अणु
	काष्ठा acpi_hid_uid hid_uid = अणुपूर्ण;
	काष्ठा device *phys_dev;

	अगर (node->header.length != 12)
		वापस -EINVAL;

	प्र_लिखो(hid_uid.hid[0].id, "%c%c%c%04X",
		'A' + ((node->acpi.hid >> 10) & 0x1f) - 1,
		'A' + ((node->acpi.hid >>  5) & 0x1f) - 1,
		'A' + ((node->acpi.hid >>  0) & 0x1f) - 1,
			node->acpi.hid >> 16);
	प्र_लिखो(hid_uid.uid, "%u", node->acpi.uid);

	*child = bus_find_device(&acpi_bus_type, शून्य, &hid_uid,
				 match_acpi_dev);
	अगर (!*child)
		वापस -ENODEV;

	phys_dev = acpi_get_first_physical_node(to_acpi_device(*child));
	अगर (phys_dev) अणु
		get_device(phys_dev);
		put_device(*child);
		*child = phys_dev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init match_pci_dev(काष्ठा device *dev, व्योम *data)
अणु
	अचिन्हित पूर्णांक devfn = *(अचिन्हित पूर्णांक *)data;

	वापस dev_is_pci(dev) && to_pci_dev(dev)->devfn == devfn;
पूर्ण

अटल दीर्घ __init parse_pci_path(स्थिर काष्ठा efi_dev_path *node,
				  काष्ठा device *parent, काष्ठा device **child)
अणु
	अचिन्हित पूर्णांक devfn;

	अगर (node->header.length != 6)
		वापस -EINVAL;
	अगर (!parent)
		वापस -EINVAL;

	devfn = PCI_DEVFN(node->pci.dev, node->pci.fn);

	*child = device_find_child(parent, &devfn, match_pci_dev);
	अगर (!*child)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Insert parsers क्रम further node types here.
 *
 * Each parser takes a poपूर्णांकer to the @node and to the @parent (will be शून्य
 * क्रम the first device path node). If a device corresponding to @node was
 * found below @parent, its reference count should be incremented and the
 * device वापसed in @child.
 *
 * The वापस value should be 0 on success or a negative पूर्णांक on failure.
 * The special वापस values 0x01 (EFI_DEV_END_INSTANCE) and 0xFF
 * (EFI_DEV_END_ENTIRE) संकेत the end of the device path, only
 * parse_end_path() is supposed to वापस this.
 *
 * Be sure to validate the node length and contents beक्रमe commencing the
 * search क्रम a device.
 */

अटल दीर्घ __init parse_end_path(स्थिर काष्ठा efi_dev_path *node,
				  काष्ठा device *parent, काष्ठा device **child)
अणु
	अगर (node->header.length != 4)
		वापस -EINVAL;
	अगर (node->header.sub_type != EFI_DEV_END_INSTANCE &&
	    node->header.sub_type != EFI_DEV_END_ENTIRE)
		वापस -EINVAL;
	अगर (!parent)
		वापस -ENODEV;

	*child = get_device(parent);
	वापस node->header.sub_type;
पूर्ण

/**
 * efi_get_device_by_path - find device by EFI Device Path
 * @node: EFI Device Path
 * @len: maximum length of EFI Device Path in bytes
 *
 * Parse a series of EFI Device Path nodes at @node and find the corresponding
 * device.  If the device was found, its reference count is incremented and a
 * poपूर्णांकer to it is वापसed.  The caller needs to drop the reference with
 * put_device() after use.  The @node poपूर्णांकer is updated to poपूर्णांक to the
 * location immediately after the "End of Hardware Device Path" node.
 *
 * If another Device Path instance follows, @len is decremented by the number
 * of bytes consumed.  Otherwise @len is set to %0.
 *
 * If a Device Path node is malक्रमmed or its corresponding device is not found,
 * @node is updated to poपूर्णांक to this offending node and an ERR_PTR is वापसed.
 *
 * If @len is initially %0, the function वापसs %शून्य.  Thus, to iterate over
 * all instances in a path, the following idiom may be used:
 *
 *	जबतक (!IS_ERR_OR_शून्य(dev = efi_get_device_by_path(&node, &len))) अणु
 *		// करो something with dev
 *		put_device(dev);
 *	पूर्ण
 *	अगर (IS_ERR(dev))
 *		// report error
 *
 * Devices can only be found अगर they're alपढ़ोy instantiated. Most buses
 * instantiate devices in the "subsys" initcall level, hence the earliest
 * initcall level in which this function should be called is "fs".
 *
 * Returns the device on success or
 *	%ERR_PTR(-ENODEV) अगर no device was found,
 *	%ERR_PTR(-EINVAL) अगर a node is malक्रमmed or exceeds @len,
 *	%ERR_PTR(-ENOTSUPP) अगर support क्रम a node type is not yet implemented.
 */
काष्ठा device * __init efi_get_device_by_path(स्थिर काष्ठा efi_dev_path **node,
					      माप_प्रकार *len)
अणु
	काष्ठा device *parent = शून्य, *child;
	दीर्घ ret = 0;

	अगर (!*len)
		वापस शून्य;

	जबतक (!ret) अणु
		अगर (*len < 4 || *len < (*node)->header.length)
			ret = -EINVAL;
		अन्यथा अगर ((*node)->header.type		== EFI_DEV_ACPI &&
			 (*node)->header.sub_type	== EFI_DEV_BASIC_ACPI)
			ret = parse_acpi_path(*node, parent, &child);
		अन्यथा अगर ((*node)->header.type		== EFI_DEV_HW &&
			 (*node)->header.sub_type	== EFI_DEV_PCI)
			ret = parse_pci_path(*node, parent, &child);
		अन्यथा अगर (((*node)->header.type		== EFI_DEV_END_PATH ||
			  (*node)->header.type		== EFI_DEV_END_PATH2))
			ret = parse_end_path(*node, parent, &child);
		अन्यथा
			ret = -ENOTSUPP;

		put_device(parent);
		अगर (ret < 0)
			वापस ERR_PTR(ret);

		parent = child;
		*node  = (व्योम *)*node + (*node)->header.length;
		*len  -= (*node)->header.length;
	पूर्ण

	अगर (ret == EFI_DEV_END_ENTIRE)
		*len = 0;

	वापस child;
पूर्ण
