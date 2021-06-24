<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Export the firmware instance and label associated with a PCI device to
 * sysfs
 *
 * Copyright (C) 2010 Dell Inc.
 * by Narendra K <Narendra_K@dell.com>,
 * Jordan Hargrave <Jordan_Hargrave@dell.com>
 *
 * PCI Firmware Specअगरication Revision 3.1 section 4.6.7 (DSM क्रम Naming a
 * PCI or PCI Express Device Under Operating Systems) defines an instance
 * number and string name. This code retrieves them and exports them to sysfs.
 * If the प्रणाली firmware करोes not provide the ACPI _DSM (Device Specअगरic
 * Method), then the SMBIOS type 41 instance number and string is exported to
 * sysfs.
 *
 * SMBIOS defines type 41 क्रम onboard pci devices. This code retrieves
 * the instance number and string from the type 41 record and exports
 * it to sysfs.
 *
 * Please see https://linux.dell.com/files/biosdevname/ क्रम more
 * inक्रमmation.
 */

#समावेश <linux/dmi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/nls.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci-acpi.h>
#समावेश "pci.h"

अटल bool device_has_acpi_name(काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_ACPI
	acpi_handle handle = ACPI_HANDLE(dev);

	अगर (!handle)
		वापस false;

	वापस acpi_check_dsm(handle, &pci_acpi_dsm_guid, 0x2,
			      1 << DSM_PCI_DEVICE_NAME);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_DMI
क्रमागत smbios_attr_क्रमागत अणु
	SMBIOS_ATTR_NONE = 0,
	SMBIOS_ATTR_LABEL_SHOW,
	SMBIOS_ATTR_INSTANCE_SHOW,
पूर्ण;

अटल माप_प्रकार find_smbios_instance_string(काष्ठा pci_dev *pdev, अक्षर *buf,
					  क्रमागत smbios_attr_क्रमागत attribute)
अणु
	स्थिर काष्ठा dmi_device *dmi;
	काष्ठा dmi_dev_onboard *करोnboard;
	पूर्णांक करोमुख्य_nr = pci_करोमुख्य_nr(pdev->bus);
	पूर्णांक bus = pdev->bus->number;
	पूर्णांक devfn = pdev->devfn;

	dmi = शून्य;
	जबतक ((dmi = dmi_find_device(DMI_DEV_TYPE_DEV_ONBOARD,
				      शून्य, dmi)) != शून्य) अणु
		करोnboard = dmi->device_data;
		अगर (करोnboard && करोnboard->segment == करोमुख्य_nr &&
				करोnboard->bus == bus &&
				करोnboard->devfn == devfn) अणु
			अगर (buf) अणु
				अगर (attribute == SMBIOS_ATTR_INSTANCE_SHOW)
					वापस sysfs_emit(buf, "%d\n",
							  करोnboard->instance);
				अन्यथा अगर (attribute == SMBIOS_ATTR_LABEL_SHOW)
					वापस sysfs_emit(buf, "%s\n",
							  dmi->name);
			पूर्ण
			वापस म_माप(dmi->name);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार smbios_label_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस find_smbios_instance_string(pdev, buf,
					   SMBIOS_ATTR_LABEL_SHOW);
पूर्ण
अटल काष्ठा device_attribute dev_attr_smbios_label = __ATTR(label, 0444,
						    smbios_label_show, शून्य);

अटल sमाप_प्रकार index_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस find_smbios_instance_string(pdev, buf,
					   SMBIOS_ATTR_INSTANCE_SHOW);
पूर्ण
अटल DEVICE_ATTR_RO(index);

अटल काष्ठा attribute *smbios_attrs[] = अणु
	&dev_attr_smbios_label.attr,
	&dev_attr_index.attr,
	शून्य,
पूर्ण;

अटल umode_t smbios_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
				      पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (device_has_acpi_name(dev))
		वापस 0;

	अगर (!find_smbios_instance_string(pdev, शून्य, SMBIOS_ATTR_NONE))
		वापस 0;

	वापस a->mode;
पूर्ण

स्थिर काष्ठा attribute_group pci_dev_smbios_attr_group = अणु
	.attrs = smbios_attrs,
	.is_visible = smbios_attr_is_visible,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
क्रमागत acpi_attr_क्रमागत अणु
	ACPI_ATTR_LABEL_SHOW,
	ACPI_ATTR_INDEX_SHOW,
पूर्ण;

अटल व्योम dsm_label_utf16s_to_utf8s(जोड़ acpi_object *obj, अक्षर *buf)
अणु
	पूर्णांक len;
	len = utf16s_to_utf8s((स्थिर ब_अक्षर_प्रकार *)obj->buffer.poपूर्णांकer,
			      obj->buffer.length,
			      UTF16_LITTLE_ENDIAN,
			      buf, PAGE_SIZE);
	buf[len] = '\n';
पूर्ण

अटल पूर्णांक dsm_get_label(काष्ठा device *dev, अक्षर *buf,
			 क्रमागत acpi_attr_क्रमागत attr)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object *obj, *पंचांगp;
	पूर्णांक len = -1;

	अगर (!handle)
		वापस -1;

	obj = acpi_evaluate_dsm(handle, &pci_acpi_dsm_guid, 0x2,
				DSM_PCI_DEVICE_NAME, शून्य);
	अगर (!obj)
		वापस -1;

	पंचांगp = obj->package.elements;
	अगर (obj->type == ACPI_TYPE_PACKAGE && obj->package.count == 2 &&
	    पंचांगp[0].type == ACPI_TYPE_INTEGER &&
	    (पंचांगp[1].type == ACPI_TYPE_STRING ||
	     पंचांगp[1].type == ACPI_TYPE_BUFFER)) अणु
		/*
		 * The second string element is optional even when
		 * this _DSM is implemented; when not implemented,
		 * this entry must वापस a null string.
		 */
		अगर (attr == ACPI_ATTR_INDEX_SHOW) अणु
			scnम_लिखो(buf, PAGE_SIZE, "%llu\n", पंचांगp->पूर्णांकeger.value);
		पूर्ण अन्यथा अगर (attr == ACPI_ATTR_LABEL_SHOW) अणु
			अगर (पंचांगp[1].type == ACPI_TYPE_STRING)
				scnम_लिखो(buf, PAGE_SIZE, "%s\n",
					  पंचांगp[1].string.poपूर्णांकer);
			अन्यथा अगर (पंचांगp[1].type == ACPI_TYPE_BUFFER)
				dsm_label_utf16s_to_utf8s(पंचांगp + 1, buf);
		पूर्ण
		len = म_माप(buf) > 0 ? म_माप(buf) : -1;
	पूर्ण

	ACPI_FREE(obj);

	वापस len;
पूर्ण

अटल sमाप_प्रकार label_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	वापस dsm_get_label(dev, buf, ACPI_ATTR_LABEL_SHOW);
पूर्ण
अटल DEVICE_ATTR_RO(label);

अटल sमाप_प्रकार acpi_index_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस dsm_get_label(dev, buf, ACPI_ATTR_INDEX_SHOW);
पूर्ण
अटल DEVICE_ATTR_RO(acpi_index);

अटल काष्ठा attribute *acpi_attrs[] = अणु
	&dev_attr_label.attr,
	&dev_attr_acpi_index.attr,
	शून्य,
पूर्ण;

अटल umode_t acpi_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
				    पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	अगर (!device_has_acpi_name(dev))
		वापस 0;

	वापस a->mode;
पूर्ण

स्थिर काष्ठा attribute_group pci_dev_acpi_attr_group = अणु
	.attrs = acpi_attrs,
	.is_visible = acpi_attr_is_visible,
पूर्ण;
#पूर्ण_अगर
