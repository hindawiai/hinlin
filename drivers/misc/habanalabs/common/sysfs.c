<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/pci.h>

दीर्घ hl_get_frequency(काष्ठा hl_device *hdev, u32 pll_index,
								bool curr)
अणु
	काष्ठा cpucp_packet pkt;
	u32 used_pll_idx;
	u64 result;
	पूर्णांक rc;

	rc = get_used_pll_index(hdev, pll_index, &used_pll_idx);
	अगर (rc)
		वापस rc;

	स_रखो(&pkt, 0, माप(pkt));

	अगर (curr)
		pkt.ctl = cpu_to_le32(CPUCP_PACKET_FREQUENCY_CURR_GET <<
						CPUCP_PKT_CTL_OPCODE_SHIFT);
	अन्यथा
		pkt.ctl = cpu_to_le32(CPUCP_PACKET_FREQUENCY_GET <<
						CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.pll_index = cpu_to_le32((u32)used_pll_idx);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get frequency of PLL %d, error %d\n",
			used_pll_idx, rc);
		वापस rc;
	पूर्ण

	वापस (दीर्घ) result;
पूर्ण

व्योम hl_set_frequency(काष्ठा hl_device *hdev, u32 pll_index,
								u64 freq)
अणु
	काष्ठा cpucp_packet pkt;
	u32 used_pll_idx;
	पूर्णांक rc;

	rc = get_used_pll_index(hdev, pll_index, &used_pll_idx);
	अगर (rc)
		वापस;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_FREQUENCY_SET <<
					CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.pll_index = cpu_to_le32((u32)used_pll_idx);
	pkt.value = cpu_to_le64(freq);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev,
			"Failed to set frequency to PLL %d, error %d\n",
			used_pll_idx, rc);
पूर्ण

u64 hl_get_max_घातer(काष्ठा hl_device *hdev)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_MAX_POWER_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to get max power, error %d\n", rc);
		वापस (u64) rc;
	पूर्ण

	वापस result;
पूर्ण

व्योम hl_set_max_घातer(काष्ठा hl_device *hdev)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_MAX_POWER_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.value = cpu_to_le64(hdev->max_घातer);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev, "Failed to set max power, error %d\n", rc);
पूर्ण

अटल sमाप_प्रकार uboot_ver_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", hdev->asic_prop.uboot_ver);
पूर्ण

अटल sमाप_प्रकार armcp_kernel_ver_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s", hdev->asic_prop.cpucp_info.kernel_version);
पूर्ण

अटल sमाप_प्रकार armcp_ver_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", hdev->asic_prop.cpucp_info.cpucp_version);
पूर्ण

अटल sमाप_प्रकार cpld_ver_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%08x\n",
			hdev->asic_prop.cpucp_info.cpld_version);
पूर्ण

अटल sमाप_प्रकार cpucp_kernel_ver_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s", hdev->asic_prop.cpucp_info.kernel_version);
पूर्ण

अटल sमाप_प्रकार cpucp_ver_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", hdev->asic_prop.cpucp_info.cpucp_version);
पूर्ण

अटल sमाप_प्रकार infineon_ver_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%04x\n",
			hdev->asic_prop.cpucp_info.infineon_version);
पूर्ण

अटल sमाप_प्रकार fuse_ver_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", hdev->asic_prop.cpucp_info.fuse_version);
पूर्ण

अटल sमाप_प्रकार thermal_ver_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s", hdev->asic_prop.cpucp_info.thermal_version);
पूर्ण

अटल sमाप_प्रकार preboot_btl_ver_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", hdev->asic_prop.preboot_ver);
पूर्ण

अटल sमाप_प्रकार soft_reset_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!hdev->supports_soft_reset) अणु
		dev_err(hdev->dev, "Device does not support soft-reset\n");
		जाओ out;
	पूर्ण

	dev_warn(hdev->dev, "Soft-Reset requested through sysfs\n");

	hl_device_reset(hdev, 0);

out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार hard_reset_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ out;
	पूर्ण

	dev_warn(hdev->dev, "Hard-Reset requested through sysfs\n");

	hl_device_reset(hdev, HL_RESET_HARD);

out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार device_type_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	अक्षर *str;

	चयन (hdev->asic_type) अणु
	हाल ASIC_GOYA:
		str = "GOYA";
		अवरोध;
	हाल ASIC_GAUDI:
		str = "GAUDI";
		अवरोध;
	हाल ASIC_GAUDI_SEC:
		str = "GAUDI SEC";
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Unrecognized ASIC type %d\n",
				hdev->asic_type);
		वापस -EINVAL;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल sमाप_प्रकार pci_addr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%04x:%02x:%02x.%x\n",
			pci_करोमुख्य_nr(hdev->pdev->bus),
			hdev->pdev->bus->number,
			PCI_SLOT(hdev->pdev->devfn),
			PCI_FUNC(hdev->pdev->devfn));
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	अक्षर *str;

	अगर (atomic_पढ़ो(&hdev->in_reset))
		str = "In reset";
	अन्यथा अगर (hdev->disabled)
		str = "Malfunction";
	अन्यथा अगर (hdev->needs_reset)
		str = "Needs Reset";
	अन्यथा
		str = "Operational";

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल sमाप_प्रकार soft_reset_cnt_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", hdev->soft_reset_cnt);
पूर्ण

अटल sमाप_प्रकार hard_reset_cnt_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", hdev->hard_reset_cnt);
पूर्ण

अटल sमाप_प्रकार max_घातer_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	val = hl_get_max_घातer(hdev);

	वापस प्र_लिखो(buf, "%lu\n", val);
पूर्ण

अटल sमाप_प्रकार max_घातer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ out;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ out;
	पूर्ण

	hdev->max_घातer = value;
	hl_set_max_घातer(hdev);

out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार eeprom_पढ़ो_handler(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr, अक्षर *buf, loff_t offset,
			माप_प्रकार max_size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	अक्षर *data;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	अगर (!max_size)
		वापस -EINVAL;

	data = kzalloc(max_size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	rc = hdev->asic_funcs->get_eeprom_data(hdev, data, max_size);
	अगर (rc)
		जाओ out;

	स_नकल(buf, data, max_size);

out:
	kमुक्त(data);

	वापस max_size;
पूर्ण

अटल DEVICE_ATTR_RO(armcp_kernel_ver);
अटल DEVICE_ATTR_RO(armcp_ver);
अटल DEVICE_ATTR_RO(cpld_ver);
अटल DEVICE_ATTR_RO(cpucp_kernel_ver);
अटल DEVICE_ATTR_RO(cpucp_ver);
अटल DEVICE_ATTR_RO(device_type);
अटल DEVICE_ATTR_RO(fuse_ver);
अटल DEVICE_ATTR_WO(hard_reset);
अटल DEVICE_ATTR_RO(hard_reset_cnt);
अटल DEVICE_ATTR_RO(infineon_ver);
अटल DEVICE_ATTR_RW(max_घातer);
अटल DEVICE_ATTR_RO(pci_addr);
अटल DEVICE_ATTR_RO(preboot_btl_ver);
अटल DEVICE_ATTR_WO(soft_reset);
अटल DEVICE_ATTR_RO(soft_reset_cnt);
अटल DEVICE_ATTR_RO(status);
अटल DEVICE_ATTR_RO(thermal_ver);
अटल DEVICE_ATTR_RO(uboot_ver);

अटल काष्ठा bin_attribute bin_attr_eeprom = अणु
	.attr = अणु.name = "eeprom", .mode = (0444)पूर्ण,
	.size = PAGE_SIZE,
	.पढ़ो = eeprom_पढ़ो_handler
पूर्ण;

अटल काष्ठा attribute *hl_dev_attrs[] = अणु
	&dev_attr_armcp_kernel_ver.attr,
	&dev_attr_armcp_ver.attr,
	&dev_attr_cpld_ver.attr,
	&dev_attr_cpucp_kernel_ver.attr,
	&dev_attr_cpucp_ver.attr,
	&dev_attr_device_type.attr,
	&dev_attr_fuse_ver.attr,
	&dev_attr_hard_reset.attr,
	&dev_attr_hard_reset_cnt.attr,
	&dev_attr_infineon_ver.attr,
	&dev_attr_max_घातer.attr,
	&dev_attr_pci_addr.attr,
	&dev_attr_preboot_btl_ver.attr,
	&dev_attr_soft_reset.attr,
	&dev_attr_soft_reset_cnt.attr,
	&dev_attr_status.attr,
	&dev_attr_thermal_ver.attr,
	&dev_attr_uboot_ver.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *hl_dev_bin_attrs[] = अणु
	&bin_attr_eeprom,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group hl_dev_attr_group = अणु
	.attrs = hl_dev_attrs,
	.bin_attrs = hl_dev_bin_attrs,
पूर्ण;

अटल काष्ठा attribute_group hl_dev_clks_attr_group;

अटल स्थिर काष्ठा attribute_group *hl_dev_attr_groups[] = अणु
	&hl_dev_attr_group,
	&hl_dev_clks_attr_group,
	शून्य,
पूर्ण;

पूर्णांक hl_sysfs_init(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	अगर (hdev->asic_type == ASIC_GOYA)
		hdev->pm_mng_profile = PM_AUTO;
	अन्यथा
		hdev->pm_mng_profile = PM_MANUAL;

	hdev->max_घातer = hdev->asic_prop.max_घातer_शेष;

	hdev->asic_funcs->add_device_attr(hdev, &hl_dev_clks_attr_group);

	rc = device_add_groups(hdev->dev, hl_dev_attr_groups);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add groups to device, error %d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hl_sysfs_fini(काष्ठा hl_device *hdev)
अणु
	device_हटाओ_groups(hdev->dev, hl_dev_attr_groups);
पूर्ण
