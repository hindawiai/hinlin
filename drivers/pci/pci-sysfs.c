<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) Copyright 2002-2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * (C) Copyright 2002-2004 IBM Corp.
 * (C) Copyright 2003 Matthew Wilcox
 * (C) Copyright 2003 Hewlett-Packard
 * (C) Copyright 2004 Jon Smirl <jonsmirl@yahoo.com>
 * (C) Copyright 2004 Silicon Graphics, Inc. Jesse Barnes <jbarnes@sgi.com>
 *
 * File attributes क्रम PCI devices
 *
 * Modeled after usb's driverfs.c
 */


#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/export.h>
#समावेश <linux/topology.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/capability.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश "pci.h"

अटल पूर्णांक sysfs_initialized;	/* = 0 */

/* show configuration fields */
#घोषणा pci_config_attr(field, क्रमmat_string)				\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)				\
अणु									\
	काष्ठा pci_dev *pdev;						\
									\
	pdev = to_pci_dev(dev);						\
	वापस sysfs_emit(buf, क्रमmat_string, pdev->field);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

pci_config_attr(venकरोr, "0x%04x\n");
pci_config_attr(device, "0x%04x\n");
pci_config_attr(subप्रणाली_venकरोr, "0x%04x\n");
pci_config_attr(subप्रणाली_device, "0x%04x\n");
pci_config_attr(revision, "0x%02x\n");
pci_config_attr(class, "0x%06x\n");
pci_config_attr(irq, "%u\n");

अटल sमाप_प्रकार broken_parity_status_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	वापस sysfs_emit(buf, "%u\n", pdev->broken_parity_status);
पूर्ण

अटल sमाप_प्रकार broken_parity_status_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	pdev->broken_parity_status = !!val;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(broken_parity_status);

अटल sमाप_प्रकार pci_dev_show_local_cpu(काष्ठा device *dev, bool list,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा cpumask *mask;

#अगर_घोषित CONFIG_NUMA
	mask = (dev_to_node(dev) == -1) ? cpu_online_mask :
					  cpumask_of_node(dev_to_node(dev));
#अन्यथा
	mask = cpumask_of_pcibus(to_pci_dev(dev)->bus);
#पूर्ण_अगर
	वापस cpumap_prपूर्णांक_to_pagebuf(list, buf, mask);
पूर्ण

अटल sमाप_प्रकार local_cpus_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस pci_dev_show_local_cpu(dev, false, attr, buf);
पूर्ण
अटल DEVICE_ATTR_RO(local_cpus);

अटल sमाप_प्रकार local_cpulist_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस pci_dev_show_local_cpu(dev, true, attr, buf);
पूर्ण
अटल DEVICE_ATTR_RO(local_cpulist);

/*
 * PCI Bus Class Devices
 */
अटल sमाप_प्रकार cpuaffinity_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_pcibus(to_pci_bus(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(false, buf, cpumask);
पूर्ण
अटल DEVICE_ATTR_RO(cpuaffinity);

अटल sमाप_प्रकार cpulistaffinity_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_pcibus(to_pci_bus(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask);
पूर्ण
अटल DEVICE_ATTR_RO(cpulistaffinity);

अटल sमाप_प्रकार घातer_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "%s\n", pci_घातer_name(pdev->current_state));
पूर्ण
अटल DEVICE_ATTR_RO(घातer_state);

/* show resources */
अटल sमाप_प्रकार resource_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	पूर्णांक i;
	पूर्णांक max;
	resource_माप_प्रकार start, end;
	माप_प्रकार len = 0;

	अगर (pci_dev->subordinate)
		max = DEVICE_COUNT_RESOURCE;
	अन्यथा
		max = PCI_BRIDGE_RESOURCES;

	क्रम (i = 0; i < max; i++) अणु
		काष्ठा resource *res =  &pci_dev->resource[i];
		pci_resource_to_user(pci_dev, i, res, &start, &end);
		len += sysfs_emit_at(buf, len, "0x%016llx 0x%016llx 0x%016llx\n",
				     (अचिन्हित दीर्घ दीर्घ)start,
				     (अचिन्हित दीर्घ दीर्घ)end,
				     (अचिन्हित दीर्घ दीर्घ)res->flags);
	पूर्ण
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(resource);

अटल sमाप_प्रकार max_link_speed_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "%s\n",
			  pci_speed_string(pcie_get_speed_cap(pdev)));
पूर्ण
अटल DEVICE_ATTR_RO(max_link_speed);

अटल sमाप_प्रकार max_link_width_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "%u\n", pcie_get_width_cap(pdev));
पूर्ण
अटल DEVICE_ATTR_RO(max_link_width);

अटल sमाप_प्रकार current_link_speed_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	u16 linkstat;
	पूर्णांक err;
	क्रमागत pci_bus_speed speed;

	err = pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_LNKSTA, &linkstat);
	अगर (err)
		वापस -EINVAL;

	speed = pcie_link_speed[linkstat & PCI_EXP_LNKSTA_CLS];

	वापस sysfs_emit(buf, "%s\n", pci_speed_string(speed));
पूर्ण
अटल DEVICE_ATTR_RO(current_link_speed);

अटल sमाप_प्रकार current_link_width_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	u16 linkstat;
	पूर्णांक err;

	err = pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_LNKSTA, &linkstat);
	अगर (err)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%u\n",
		(linkstat & PCI_EXP_LNKSTA_NLW) >> PCI_EXP_LNKSTA_NLW_SHIFT);
पूर्ण
अटल DEVICE_ATTR_RO(current_link_width);

अटल sमाप_प्रकार secondary_bus_number_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	u8 sec_bus;
	पूर्णांक err;

	err = pci_पढ़ो_config_byte(pci_dev, PCI_SECONDARY_BUS, &sec_bus);
	अगर (err)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%u\n", sec_bus);
पूर्ण
अटल DEVICE_ATTR_RO(secondary_bus_number);

अटल sमाप_प्रकार subordinate_bus_number_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	u8 sub_bus;
	पूर्णांक err;

	err = pci_पढ़ो_config_byte(pci_dev, PCI_SUBORDINATE_BUS, &sub_bus);
	अगर (err)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%u\n", sub_bus);
पूर्ण
अटल DEVICE_ATTR_RO(subordinate_bus_number);

अटल sमाप_प्रकार ari_enabled_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "%u\n", pci_ari_enabled(pci_dev->bus));
पूर्ण
अटल DEVICE_ATTR_RO(ari_enabled);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "pci:v%08Xd%08Xsv%08Xsd%08Xbc%02Xsc%02Xi%02X\n",
			  pci_dev->venकरोr, pci_dev->device,
			  pci_dev->subप्रणाली_venकरोr, pci_dev->subप्रणाली_device,
			  (u8)(pci_dev->class >> 16), (u8)(pci_dev->class >> 8),
			  (u8)(pci_dev->class));
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार enable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार result = kम_से_अदीर्घ(buf, 0, &val);

	अगर (result < 0)
		वापस result;

	/* this can crash the machine when करोne on the "wrong" device */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	device_lock(dev);
	अगर (dev->driver)
		result = -EBUSY;
	अन्यथा अगर (val)
		result = pci_enable_device(pdev);
	अन्यथा अगर (pci_is_enabled(pdev))
		pci_disable_device(pdev);
	अन्यथा
		result = -EIO;
	device_unlock(dev);

	वापस result < 0 ? result : count;
पूर्ण

अटल sमाप_प्रकार enable_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(dev);
	वापस sysfs_emit(buf, "%u\n", atomic_पढ़ो(&pdev->enable_cnt));
पूर्ण
अटल DEVICE_ATTR_RW(enable);

#अगर_घोषित CONFIG_NUMA
अटल sमाप_प्रकार numa_node_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक node, ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = kstrtoपूर्णांक(buf, 0, &node);
	अगर (ret)
		वापस ret;

	अगर ((node < 0 && node != NUMA_NO_NODE) || node >= MAX_NUMNODES)
		वापस -EINVAL;

	अगर (node != NUMA_NO_NODE && !node_online(node))
		वापस -EINVAL;

	add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
	pci_alert(pdev, FW_BUG "Overriding NUMA node to %d.  Contact your vendor for updates.",
		  node);

	dev->numa_node = node;
	वापस count;
पूर्ण

अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", dev->numa_node);
पूर्ण
अटल DEVICE_ATTR_RW(numa_node);
#पूर्ण_अगर

अटल sमाप_प्रकार dma_mask_bits_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस sysfs_emit(buf, "%d\n", fls64(pdev->dma_mask));
पूर्ण
अटल DEVICE_ATTR_RO(dma_mask_bits);

अटल sमाप_प्रकार consistent_dma_mask_bits_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", fls64(dev->coherent_dma_mask));
पूर्ण
अटल DEVICE_ATTR_RO(consistent_dma_mask_bits);

अटल sमाप_प्रकार msi_bus_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_bus *subordinate = pdev->subordinate;

	वापस sysfs_emit(buf, "%u\n", subordinate ?
			  !(subordinate->bus_flags & PCI_BUS_FLAGS_NO_MSI)
			    : !pdev->no_msi);
पूर्ण

अटल sमाप_प्रकार msi_bus_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_bus *subordinate = pdev->subordinate;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * "no_msi" and "bus_flags" only affect what happens when a driver
	 * requests MSI or MSI-X.  They करोn't affect any drivers that have
	 * alपढ़ोy requested MSI or MSI-X.
	 */
	अगर (!subordinate) अणु
		pdev->no_msi = !val;
		pci_info(pdev, "MSI/MSI-X %s for future drivers\n",
			 val ? "allowed" : "disallowed");
		वापस count;
	पूर्ण

	अगर (val)
		subordinate->bus_flags &= ~PCI_BUS_FLAGS_NO_MSI;
	अन्यथा
		subordinate->bus_flags |= PCI_BUS_FLAGS_NO_MSI;

	dev_info(&subordinate->dev, "MSI/MSI-X %s for future drivers of devices on this bus\n",
		 val ? "allowed" : "disallowed");
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(msi_bus);

अटल sमाप_प्रकार rescan_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा pci_bus *b = शून्य;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val) अणु
		pci_lock_rescan_हटाओ();
		जबतक ((b = pci_find_next_bus(b)) != शून्य)
			pci_rescan_bus(b);
		pci_unlock_rescan_हटाओ();
	पूर्ण
	वापस count;
पूर्ण
अटल BUS_ATTR_WO(rescan);

अटल काष्ठा attribute *pci_bus_attrs[] = अणु
	&bus_attr_rescan.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pci_bus_group = अणु
	.attrs = pci_bus_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *pci_bus_groups[] = अणु
	&pci_bus_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार dev_rescan_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val) अणु
		pci_lock_rescan_हटाओ();
		pci_rescan_bus(pdev->bus);
		pci_unlock_rescan_हटाओ();
	पूर्ण
	वापस count;
पूर्ण
अटल काष्ठा device_attribute dev_attr_dev_rescan = __ATTR(rescan, 0200, शून्य,
							    dev_rescan_store);

अटल sमाप_प्रकार हटाओ_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val && device_हटाओ_file_self(dev, attr))
		pci_stop_and_हटाओ_bus_device_locked(to_pci_dev(dev));
	वापस count;
पूर्ण
अटल DEVICE_ATTR_IGNORE_LOCKDEP(हटाओ, 0220, शून्य,
				  हटाओ_store);

अटल sमाप_प्रकार bus_rescan_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा pci_bus *bus = to_pci_bus(dev);

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val) अणु
		pci_lock_rescan_हटाओ();
		अगर (!pci_is_root_bus(bus) && list_empty(&bus->devices))
			pci_rescan_bus_bridge_resize(bus->self);
		अन्यथा
			pci_rescan_bus(bus);
		pci_unlock_rescan_हटाओ();
	पूर्ण
	वापस count;
पूर्ण
अटल काष्ठा device_attribute dev_attr_bus_rescan = __ATTR(rescan, 0200, शून्य,
							    bus_rescan_store);

#अगर defined(CONFIG_PM) && defined(CONFIG_ACPI)
अटल sमाप_प्रकार d3cold_allowed_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	pdev->d3cold_allowed = !!val;
	अगर (pdev->d3cold_allowed)
		pci_d3cold_enable(pdev);
	अन्यथा
		pci_d3cold_disable(pdev);

	pm_runसमय_resume(dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार d3cold_allowed_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	वापस sysfs_emit(buf, "%u\n", pdev->d3cold_allowed);
पूर्ण
अटल DEVICE_ATTR_RW(d3cold_allowed);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल sमाप_प्रकार devspec_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा device_node *np = pci_device_to_OF_node(pdev);

	अगर (np == शून्य)
		वापस 0;
	वापस sysfs_emit(buf, "%pOF", np);
पूर्ण
अटल DEVICE_ATTR_RO(devspec);
#पूर्ण_अगर

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अक्षर *driver_override, *old, *cp;

	/* We need to keep extra room क्रम a newline */
	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	device_lock(dev);
	old = pdev->driver_override;
	अगर (म_माप(driver_override)) अणु
		pdev->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		pdev->driver_override = शून्य;
	पूर्ण
	device_unlock(dev);

	kमुक्त(old);

	वापस count;
पूर्ण

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	sमाप_प्रकार len;

	device_lock(dev);
	len = sysfs_emit(buf, "%s\n", pdev->driver_override);
	device_unlock(dev);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

अटल काष्ठा attribute *pci_dev_attrs[] = अणु
	&dev_attr_घातer_state.attr,
	&dev_attr_resource.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_subप्रणाली_venकरोr.attr,
	&dev_attr_subप्रणाली_device.attr,
	&dev_attr_revision.attr,
	&dev_attr_class.attr,
	&dev_attr_irq.attr,
	&dev_attr_local_cpus.attr,
	&dev_attr_local_cpulist.attr,
	&dev_attr_modalias.attr,
#अगर_घोषित CONFIG_NUMA
	&dev_attr_numa_node.attr,
#पूर्ण_अगर
	&dev_attr_dma_mask_bits.attr,
	&dev_attr_consistent_dma_mask_bits.attr,
	&dev_attr_enable.attr,
	&dev_attr_broken_parity_status.attr,
	&dev_attr_msi_bus.attr,
#अगर defined(CONFIG_PM) && defined(CONFIG_ACPI)
	&dev_attr_d3cold_allowed.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
	&dev_attr_devspec.attr,
#पूर्ण_अगर
	&dev_attr_driver_override.attr,
	&dev_attr_ari_enabled.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *pci_bridge_attrs[] = अणु
	&dev_attr_subordinate_bus_number.attr,
	&dev_attr_secondary_bus_number.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *pcie_dev_attrs[] = अणु
	&dev_attr_current_link_speed.attr,
	&dev_attr_current_link_width.attr,
	&dev_attr_max_link_width.attr,
	&dev_attr_max_link_speed.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *pcibus_attrs[] = अणु
	&dev_attr_bus_rescan.attr,
	&dev_attr_cpuaffinity.attr,
	&dev_attr_cpulistaffinity.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcibus_group = अणु
	.attrs = pcibus_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *pcibus_groups[] = अणु
	&pcibus_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार boot_vga_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_dev *vga_dev = vga_शेष_device();

	अगर (vga_dev)
		वापस sysfs_emit(buf, "%u\n", (pdev == vga_dev));

	वापस sysfs_emit(buf, "%u\n",
			  !!(pdev->resource[PCI_ROM_RESOURCE].flags &
			     IORESOURCE_ROM_SHADOW));
पूर्ण
अटल DEVICE_ATTR_RO(boot_vga);

अटल sमाप_प्रकार pci_पढ़ो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	अचिन्हित पूर्णांक size = 64;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;

	/* Several chips lock up trying to पढ़ो undefined config space */
	अगर (file_ns_capable(filp, &init_user_ns, CAP_SYS_ADMIN))
		size = dev->cfg_size;
	अन्यथा अगर (dev->hdr_type == PCI_HEADER_TYPE_CARDBUS)
		size = 128;

	अगर (off > size)
		वापस 0;
	अगर (off + count > size) अणु
		size -= off;
		count = size;
	पूर्ण अन्यथा अणु
		size = count;
	पूर्ण

	pci_config_pm_runसमय_get(dev);

	अगर ((off & 1) && size) अणु
		u8 val;
		pci_user_पढ़ो_config_byte(dev, off, &val);
		data[off - init_off] = val;
		off++;
		size--;
	पूर्ण

	अगर ((off & 3) && size > 2) अणु
		u16 val;
		pci_user_पढ़ो_config_word(dev, off, &val);
		data[off - init_off] = val & 0xff;
		data[off - init_off + 1] = (val >> 8) & 0xff;
		off += 2;
		size -= 2;
	पूर्ण

	जबतक (size > 3) अणु
		u32 val;
		pci_user_पढ़ो_config_dword(dev, off, &val);
		data[off - init_off] = val & 0xff;
		data[off - init_off + 1] = (val >> 8) & 0xff;
		data[off - init_off + 2] = (val >> 16) & 0xff;
		data[off - init_off + 3] = (val >> 24) & 0xff;
		off += 4;
		size -= 4;
		cond_resched();
	पूर्ण

	अगर (size >= 2) अणु
		u16 val;
		pci_user_पढ़ो_config_word(dev, off, &val);
		data[off - init_off] = val & 0xff;
		data[off - init_off + 1] = (val >> 8) & 0xff;
		off += 2;
		size -= 2;
	पूर्ण

	अगर (size > 0) अणु
		u8 val;
		pci_user_पढ़ो_config_byte(dev, off, &val);
		data[off - init_off] = val;
		off++;
		--size;
	पूर्ण

	pci_config_pm_runसमय_put(dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pci_ग_लिखो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	अचिन्हित पूर्णांक size = count;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_PCI_ACCESS);
	अगर (ret)
		वापस ret;

	अगर (off > dev->cfg_size)
		वापस 0;
	अगर (off + count > dev->cfg_size) अणु
		size = dev->cfg_size - off;
		count = size;
	पूर्ण

	pci_config_pm_runसमय_get(dev);

	अगर ((off & 1) && size) अणु
		pci_user_ग_लिखो_config_byte(dev, off, data[off - init_off]);
		off++;
		size--;
	पूर्ण

	अगर ((off & 3) && size > 2) अणु
		u16 val = data[off - init_off];
		val |= (u16) data[off - init_off + 1] << 8;
		pci_user_ग_लिखो_config_word(dev, off, val);
		off += 2;
		size -= 2;
	पूर्ण

	जबतक (size > 3) अणु
		u32 val = data[off - init_off];
		val |= (u32) data[off - init_off + 1] << 8;
		val |= (u32) data[off - init_off + 2] << 16;
		val |= (u32) data[off - init_off + 3] << 24;
		pci_user_ग_लिखो_config_dword(dev, off, val);
		off += 4;
		size -= 4;
	पूर्ण

	अगर (size >= 2) अणु
		u16 val = data[off - init_off];
		val |= (u16) data[off - init_off + 1] << 8;
		pci_user_ग_लिखो_config_word(dev, off, val);
		off += 2;
		size -= 2;
	पूर्ण

	अगर (size) अणु
		pci_user_ग_लिखो_config_byte(dev, off, data[off - init_off]);
		off++;
		--size;
	पूर्ण

	pci_config_pm_runसमय_put(dev);

	वापस count;
पूर्ण
अटल BIN_ATTR(config, 0644, pci_पढ़ो_config, pci_ग_लिखो_config, 0);

अटल काष्ठा bin_attribute *pci_dev_config_attrs[] = अणु
	&bin_attr_config,
	शून्य,
पूर्ण;

अटल umode_t pci_dev_config_attr_is_visible(काष्ठा kobject *kobj,
					      काष्ठा bin_attribute *a, पूर्णांक n)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	a->size = PCI_CFG_SPACE_SIZE;
	अगर (pdev->cfg_size > PCI_CFG_SPACE_SIZE)
		a->size = PCI_CFG_SPACE_EXP_SIZE;

	वापस a->attr.mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group pci_dev_config_attr_group = अणु
	.bin_attrs = pci_dev_config_attrs,
	.is_bin_visible = pci_dev_config_attr_is_visible,
पूर्ण;

#अगर_घोषित HAVE_PCI_LEGACY
/**
 * pci_पढ़ो_legacy_io - पढ़ो byte(s) from legacy I/O port space
 * @filp: खोलो sysfs file
 * @kobj: kobject corresponding to file to पढ़ो from
 * @bin_attr: काष्ठा bin_attribute क्रम this file
 * @buf: buffer to store results
 * @off: offset पूर्णांकo legacy I/O port space
 * @count: number of bytes to पढ़ो
 *
 * Reads 1, 2, or 4 bytes from legacy I/O port space using an arch specअगरic
 * callback routine (pci_legacy_पढ़ो).
 */
अटल sमाप_प्रकार pci_पढ़ो_legacy_io(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				  loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	/* Only support 1, 2 or 4 byte accesses */
	अगर (count != 1 && count != 2 && count != 4)
		वापस -EINVAL;

	वापस pci_legacy_पढ़ो(bus, off, (u32 *)buf, count);
पूर्ण

/**
 * pci_ग_लिखो_legacy_io - ग_लिखो byte(s) to legacy I/O port space
 * @filp: खोलो sysfs file
 * @kobj: kobject corresponding to file to पढ़ो from
 * @bin_attr: काष्ठा bin_attribute क्रम this file
 * @buf: buffer containing value to be written
 * @off: offset पूर्णांकo legacy I/O port space
 * @count: number of bytes to ग_लिखो
 *
 * Writes 1, 2, or 4 bytes from legacy I/O port space using an arch specअगरic
 * callback routine (pci_legacy_ग_लिखो).
 */
अटल sमाप_प्रकार pci_ग_लिखो_legacy_io(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				   loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	/* Only support 1, 2 or 4 byte accesses */
	अगर (count != 1 && count != 2 && count != 4)
		वापस -EINVAL;

	वापस pci_legacy_ग_लिखो(bus, off, *(u32 *)buf, count);
पूर्ण

/**
 * pci_mmap_legacy_mem - map legacy PCI memory पूर्णांकo user memory space
 * @filp: खोलो sysfs file
 * @kobj: kobject corresponding to device to be mapped
 * @attr: काष्ठा bin_attribute क्रम this file
 * @vma: काष्ठा vm_area_काष्ठा passed to mmap
 *
 * Uses an arch specअगरic callback, pci_mmap_legacy_mem_page_range, to mmap
 * legacy memory space (first meg of bus space) पूर्णांकo application भव
 * memory space.
 */
अटल पूर्णांक pci_mmap_legacy_mem(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *attr,
			       काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	वापस pci_mmap_legacy_page_range(bus, vma, pci_mmap_mem);
पूर्ण

/**
 * pci_mmap_legacy_io - map legacy PCI IO पूर्णांकo user memory space
 * @filp: खोलो sysfs file
 * @kobj: kobject corresponding to device to be mapped
 * @attr: काष्ठा bin_attribute क्रम this file
 * @vma: काष्ठा vm_area_काष्ठा passed to mmap
 *
 * Uses an arch specअगरic callback, pci_mmap_legacy_io_page_range, to mmap
 * legacy IO space (first meg of bus space) पूर्णांकo application भव
 * memory space. Returns -ENOSYS अगर the operation isn't supported
 */
अटल पूर्णांक pci_mmap_legacy_io(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *attr,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	वापस pci_mmap_legacy_page_range(bus, vma, pci_mmap_io);
पूर्ण

/**
 * pci_adjust_legacy_attr - adjusपंचांगent of legacy file attributes
 * @b: bus to create files under
 * @mmap_type: I/O port or memory
 *
 * Stub implementation. Can be overridden by arch अगर necessary.
 */
व्योम __weak pci_adjust_legacy_attr(काष्ठा pci_bus *b,
				   क्रमागत pci_mmap_state mmap_type)
अणु
पूर्ण

/**
 * pci_create_legacy_files - create legacy I/O port and memory files
 * @b: bus to create files under
 *
 * Some platक्रमms allow access to legacy I/O port and ISA memory space on
 * a per-bus basis.  This routine creates the files and ties them पूर्णांकo
 * their associated पढ़ो, ग_लिखो and mmap files from pci-sysfs.c
 *
 * On error unwind, but करोn't propagate the error to the caller
 * as it is ok to set up the PCI bus without these files.
 */
व्योम pci_create_legacy_files(काष्ठा pci_bus *b)
अणु
	पूर्णांक error;

	अगर (!sysfs_initialized)
		वापस;

	b->legacy_io = kसुस्मृति(2, माप(काष्ठा bin_attribute),
			       GFP_ATOMIC);
	अगर (!b->legacy_io)
		जाओ kzalloc_err;

	sysfs_bin_attr_init(b->legacy_io);
	b->legacy_io->attr.name = "legacy_io";
	b->legacy_io->size = 0xffff;
	b->legacy_io->attr.mode = 0600;
	b->legacy_io->पढ़ो = pci_पढ़ो_legacy_io;
	b->legacy_io->ग_लिखो = pci_ग_लिखो_legacy_io;
	b->legacy_io->mmap = pci_mmap_legacy_io;
	b->legacy_io->mapping = iomem_get_mapping();
	pci_adjust_legacy_attr(b, pci_mmap_io);
	error = device_create_bin_file(&b->dev, b->legacy_io);
	अगर (error)
		जाओ legacy_io_err;

	/* Allocated above after the legacy_io काष्ठा */
	b->legacy_mem = b->legacy_io + 1;
	sysfs_bin_attr_init(b->legacy_mem);
	b->legacy_mem->attr.name = "legacy_mem";
	b->legacy_mem->size = 1024*1024;
	b->legacy_mem->attr.mode = 0600;
	b->legacy_mem->mmap = pci_mmap_legacy_mem;
	b->legacy_io->mapping = iomem_get_mapping();
	pci_adjust_legacy_attr(b, pci_mmap_mem);
	error = device_create_bin_file(&b->dev, b->legacy_mem);
	अगर (error)
		जाओ legacy_mem_err;

	वापस;

legacy_mem_err:
	device_हटाओ_bin_file(&b->dev, b->legacy_io);
legacy_io_err:
	kमुक्त(b->legacy_io);
	b->legacy_io = शून्य;
kzalloc_err:
	dev_warn(&b->dev, "could not create legacy I/O port and ISA memory resources in sysfs\n");
पूर्ण

व्योम pci_हटाओ_legacy_files(काष्ठा pci_bus *b)
अणु
	अगर (b->legacy_io) अणु
		device_हटाओ_bin_file(&b->dev, b->legacy_io);
		device_हटाओ_bin_file(&b->dev, b->legacy_mem);
		kमुक्त(b->legacy_io); /* both are allocated here */
	पूर्ण
पूर्ण
#पूर्ण_अगर /* HAVE_PCI_LEGACY */

#अगर defined(HAVE_PCI_MMAP) || defined(ARCH_GENERIC_PCI_MMAP_RESOURCE)

पूर्णांक pci_mmap_fits(काष्ठा pci_dev *pdev, पूर्णांक resno, काष्ठा vm_area_काष्ठा *vma,
		  क्रमागत pci_mmap_api mmap_api)
अणु
	अचिन्हित दीर्घ nr, start, size;
	resource_माप_प्रकार pci_start = 0, pci_end;

	अगर (pci_resource_len(pdev, resno) == 0)
		वापस 0;
	nr = vma_pages(vma);
	start = vma->vm_pgoff;
	size = ((pci_resource_len(pdev, resno) - 1) >> PAGE_SHIFT) + 1;
	अगर (mmap_api == PCI_MMAP_PROCFS) अणु
		pci_resource_to_user(pdev, resno, &pdev->resource[resno],
				     &pci_start, &pci_end);
		pci_start >>= PAGE_SHIFT;
	पूर्ण
	अगर (start >= pci_start && start < pci_start + size &&
			start + nr <= pci_start + size)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * pci_mmap_resource - map a PCI resource पूर्णांकo user memory space
 * @kobj: kobject क्रम mapping
 * @attr: काष्ठा bin_attribute क्रम the file being mapped
 * @vma: काष्ठा vm_area_काष्ठा passed पूर्णांकo the mmap
 * @ग_लिखो_combine: 1 क्रम ग_लिखो_combine mapping
 *
 * Use the regular PCI mapping routines to map a PCI resource पूर्णांकo userspace.
 */
अटल पूर्णांक pci_mmap_resource(काष्ठा kobject *kobj, काष्ठा bin_attribute *attr,
			     काष्ठा vm_area_काष्ठा *vma, पूर्णांक ग_लिखो_combine)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	पूर्णांक bar = (अचिन्हित दीर्घ)attr->निजी;
	क्रमागत pci_mmap_state mmap_type;
	काष्ठा resource *res = &pdev->resource[bar];
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_PCI_ACCESS);
	अगर (ret)
		वापस ret;

	अगर (res->flags & IORESOURCE_MEM && iomem_is_exclusive(res->start))
		वापस -EINVAL;

	अगर (!pci_mmap_fits(pdev, bar, vma, PCI_MMAP_SYSFS))
		वापस -EINVAL;

	mmap_type = res->flags & IORESOURCE_MEM ? pci_mmap_mem : pci_mmap_io;

	वापस pci_mmap_resource_range(pdev, bar, vma, mmap_type, ग_लिखो_combine);
पूर्ण

अटल पूर्णांक pci_mmap_resource_uc(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस pci_mmap_resource(kobj, attr, vma, 0);
पूर्ण

अटल पूर्णांक pci_mmap_resource_wc(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस pci_mmap_resource(kobj, attr, vma, 1);
पूर्ण

अटल sमाप_प्रकार pci_resource_io(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *attr, अक्षर *buf,
			       loff_t off, माप_प्रकार count, bool ग_लिखो)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	पूर्णांक bar = (अचिन्हित दीर्घ)attr->निजी;
	अचिन्हित दीर्घ port = off;

	port += pci_resource_start(pdev, bar);

	अगर (port > pci_resource_end(pdev, bar))
		वापस 0;

	अगर (port + count - 1 > pci_resource_end(pdev, bar))
		वापस -EINVAL;

	चयन (count) अणु
	हाल 1:
		अगर (ग_लिखो)
			outb(*(u8 *)buf, port);
		अन्यथा
			*(u8 *)buf = inb(port);
		वापस 1;
	हाल 2:
		अगर (ग_लिखो)
			outw(*(u16 *)buf, port);
		अन्यथा
			*(u16 *)buf = inw(port);
		वापस 2;
	हाल 4:
		अगर (ग_लिखो)
			outl(*(u32 *)buf, port);
		अन्यथा
			*(u32 *)buf = inl(port);
		वापस 4;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार pci_पढ़ो_resource_io(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr, अक्षर *buf,
				    loff_t off, माप_प्रकार count)
अणु
	वापस pci_resource_io(filp, kobj, attr, buf, off, count, false);
पूर्ण

अटल sमाप_प्रकार pci_ग_लिखो_resource_io(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr, अक्षर *buf,
				     loff_t off, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_PCI_ACCESS);
	अगर (ret)
		वापस ret;

	वापस pci_resource_io(filp, kobj, attr, buf, off, count, true);
पूर्ण

/**
 * pci_हटाओ_resource_files - cleanup resource files
 * @pdev: dev to cleanup
 *
 * If we created resource files क्रम @pdev, हटाओ them from sysfs and
 * मुक्त their resources.
 */
अटल व्योम pci_हटाओ_resource_files(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		काष्ठा bin_attribute *res_attr;

		res_attr = pdev->res_attr[i];
		अगर (res_attr) अणु
			sysfs_हटाओ_bin_file(&pdev->dev.kobj, res_attr);
			kमुक्त(res_attr);
		पूर्ण

		res_attr = pdev->res_attr_wc[i];
		अगर (res_attr) अणु
			sysfs_हटाओ_bin_file(&pdev->dev.kobj, res_attr);
			kमुक्त(res_attr);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pci_create_attr(काष्ठा pci_dev *pdev, पूर्णांक num, पूर्णांक ग_लिखो_combine)
अणु
	/* allocate attribute काष्ठाure, piggyback attribute name */
	पूर्णांक name_len = ग_लिखो_combine ? 13 : 10;
	काष्ठा bin_attribute *res_attr;
	अक्षर *res_attr_name;
	पूर्णांक retval;

	res_attr = kzalloc(माप(*res_attr) + name_len, GFP_ATOMIC);
	अगर (!res_attr)
		वापस -ENOMEM;

	res_attr_name = (अक्षर *)(res_attr + 1);

	sysfs_bin_attr_init(res_attr);
	अगर (ग_लिखो_combine) अणु
		pdev->res_attr_wc[num] = res_attr;
		प्र_लिखो(res_attr_name, "resource%d_wc", num);
		res_attr->mmap = pci_mmap_resource_wc;
	पूर्ण अन्यथा अणु
		pdev->res_attr[num] = res_attr;
		प्र_लिखो(res_attr_name, "resource%d", num);
		अगर (pci_resource_flags(pdev, num) & IORESOURCE_IO) अणु
			res_attr->पढ़ो = pci_पढ़ो_resource_io;
			res_attr->ग_लिखो = pci_ग_लिखो_resource_io;
			अगर (arch_can_pci_mmap_io())
				res_attr->mmap = pci_mmap_resource_uc;
		पूर्ण अन्यथा अणु
			res_attr->mmap = pci_mmap_resource_uc;
		पूर्ण
	पूर्ण
	अगर (res_attr->mmap)
		res_attr->mapping = iomem_get_mapping();
	res_attr->attr.name = res_attr_name;
	res_attr->attr.mode = 0600;
	res_attr->size = pci_resource_len(pdev, num);
	res_attr->निजी = (व्योम *)(अचिन्हित दीर्घ)num;
	retval = sysfs_create_bin_file(&pdev->dev.kobj, res_attr);
	अगर (retval)
		kमुक्त(res_attr);

	वापस retval;
पूर्ण

/**
 * pci_create_resource_files - create resource files in sysfs क्रम @dev
 * @pdev: dev in question
 *
 * Walk the resources in @pdev creating files क्रम each resource available.
 */
अटल पूर्णांक pci_create_resource_files(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	पूर्णांक retval;

	/* Expose the PCI resources from this device as files */
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु

		/* skip empty resources */
		अगर (!pci_resource_len(pdev, i))
			जारी;

		retval = pci_create_attr(pdev, i, 0);
		/* क्रम prefetchable resources, create a WC mappable file */
		अगर (!retval && arch_can_pci_mmap_wc() &&
		    pdev->resource[i].flags & IORESOURCE_PREFETCH)
			retval = pci_create_attr(pdev, i, 1);
		अगर (retval) अणु
			pci_हटाओ_resource_files(pdev);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा /* !(defined(HAVE_PCI_MMAP) || defined(ARCH_GENERIC_PCI_MMAP_RESOURCE)) */
पूर्णांक __weak pci_create_resource_files(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
व्योम __weak pci_हटाओ_resource_files(काष्ठा pci_dev *dev) अणु वापस; पूर्ण
#पूर्ण_अगर

/**
 * pci_ग_लिखो_rom - used to enable access to the PCI ROM display
 * @filp: sysfs file
 * @kobj: kernel object handle
 * @bin_attr: काष्ठा bin_attribute क्रम this file
 * @buf: user input
 * @off: file offset
 * @count: number of byte in input
 *
 * writing anything except 0 enables it
 */
अटल sमाप_प्रकार pci_ग_लिखो_rom(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			     loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	अगर ((off ==  0) && (*buf == '0') && (count == 2))
		pdev->rom_attr_enabled = 0;
	अन्यथा
		pdev->rom_attr_enabled = 1;

	वापस count;
पूर्ण

/**
 * pci_पढ़ो_rom - पढ़ो a PCI ROM
 * @filp: sysfs file
 * @kobj: kernel object handle
 * @bin_attr: काष्ठा bin_attribute क्रम this file
 * @buf: where to put the data we पढ़ो from the ROM
 * @off: file offset
 * @count: number of bytes to पढ़ो
 *
 * Put @count bytes starting at @off पूर्णांकo @buf from the ROM in the PCI
 * device corresponding to @kobj.
 */
अटल sमाप_प्रकार pci_पढ़ो_rom(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	व्योम __iomem *rom;
	माप_प्रकार size;

	अगर (!pdev->rom_attr_enabled)
		वापस -EINVAL;

	rom = pci_map_rom(pdev, &size);	/* size starts out as PCI winकरोw size */
	अगर (!rom || !size)
		वापस -EIO;

	अगर (off >= size)
		count = 0;
	अन्यथा अणु
		अगर (off + count > size)
			count = size - off;

		स_नकल_fromio(buf, rom + off, count);
	पूर्ण
	pci_unmap_rom(pdev, rom);

	वापस count;
पूर्ण
अटल BIN_ATTR(rom, 0600, pci_पढ़ो_rom, pci_ग_लिखो_rom, 0);

अटल काष्ठा bin_attribute *pci_dev_rom_attrs[] = अणु
	&bin_attr_rom,
	शून्य,
पूर्ण;

अटल umode_t pci_dev_rom_attr_is_visible(काष्ठा kobject *kobj,
					   काष्ठा bin_attribute *a, पूर्णांक n)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	माप_प्रकार rom_size;

	/* If the device has a ROM, try to expose it in sysfs. */
	rom_size = pci_resource_len(pdev, PCI_ROM_RESOURCE);
	अगर (!rom_size)
		वापस 0;

	a->size = rom_size;

	वापस a->attr.mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group pci_dev_rom_attr_group = अणु
	.bin_attrs = pci_dev_rom_attrs,
	.is_bin_visible = pci_dev_rom_attr_is_visible,
पूर्ण;

अटल sमाप_प्रकार reset_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार result = kम_से_अदीर्घ(buf, 0, &val);

	अगर (result < 0)
		वापस result;

	अगर (val != 1)
		वापस -EINVAL;

	pm_runसमय_get_sync(dev);
	result = pci_reset_function(pdev);
	pm_runसमय_put(dev);
	अगर (result < 0)
		वापस result;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(reset);

अटल काष्ठा attribute *pci_dev_reset_attrs[] = अणु
	&dev_attr_reset.attr,
	शून्य,
पूर्ण;

अटल umode_t pci_dev_reset_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	अगर (!pdev->reset_fn)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group pci_dev_reset_attr_group = अणु
	.attrs = pci_dev_reset_attrs,
	.is_visible = pci_dev_reset_attr_is_visible,
पूर्ण;

पूर्णांक __must_check pci_create_sysfs_dev_files(काष्ठा pci_dev *pdev)
अणु
	अगर (!sysfs_initialized)
		वापस -EACCES;

	वापस pci_create_resource_files(pdev);
पूर्ण

/**
 * pci_हटाओ_sysfs_dev_files - cleanup PCI specअगरic sysfs files
 * @pdev: device whose entries we should मुक्त
 *
 * Cleanup when @pdev is हटाओd from sysfs.
 */
व्योम pci_हटाओ_sysfs_dev_files(काष्ठा pci_dev *pdev)
अणु
	अगर (!sysfs_initialized)
		वापस;

	pci_हटाओ_resource_files(pdev);
पूर्ण

अटल पूर्णांक __init pci_sysfs_init(व्योम)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा pci_bus *pbus = शून्य;
	पूर्णांक retval;

	sysfs_initialized = 1;
	क्रम_each_pci_dev(pdev) अणु
		retval = pci_create_sysfs_dev_files(pdev);
		अगर (retval) अणु
			pci_dev_put(pdev);
			वापस retval;
		पूर्ण
	पूर्ण

	जबतक ((pbus = pci_find_next_bus(pbus)))
		pci_create_legacy_files(pbus);

	वापस 0;
पूर्ण
late_initcall(pci_sysfs_init);

अटल काष्ठा attribute *pci_dev_dev_attrs[] = अणु
	&dev_attr_boot_vga.attr,
	शून्य,
पूर्ण;

अटल umode_t pci_dev_attrs_are_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (a == &dev_attr_boot_vga.attr)
		अगर ((pdev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
			वापस 0;

	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *pci_dev_hp_attrs[] = अणु
	&dev_attr_हटाओ.attr,
	&dev_attr_dev_rescan.attr,
	शून्य,
पूर्ण;

अटल umode_t pci_dev_hp_attrs_are_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (pdev->is_virtfn)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल umode_t pci_bridge_attrs_are_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (pci_is_bridge(pdev))
		वापस a->mode;

	वापस 0;
पूर्ण

अटल umode_t pcie_dev_attrs_are_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (pci_is_pcie(pdev))
		वापस a->mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group pci_dev_group = अणु
	.attrs = pci_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *pci_dev_groups[] = अणु
	&pci_dev_group,
	&pci_dev_config_attr_group,
	&pci_dev_rom_attr_group,
	&pci_dev_reset_attr_group,
	&pci_dev_vpd_attr_group,
#अगर_घोषित CONFIG_DMI
	&pci_dev_smbios_attr_group,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACPI
	&pci_dev_acpi_attr_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pci_dev_hp_attr_group = अणु
	.attrs = pci_dev_hp_attrs,
	.is_visible = pci_dev_hp_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pci_dev_attr_group = अणु
	.attrs = pci_dev_dev_attrs,
	.is_visible = pci_dev_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pci_bridge_attr_group = अणु
	.attrs = pci_bridge_attrs,
	.is_visible = pci_bridge_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcie_dev_attr_group = अणु
	.attrs = pcie_dev_attrs,
	.is_visible = pcie_dev_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pci_dev_attr_groups[] = अणु
	&pci_dev_attr_group,
	&pci_dev_hp_attr_group,
#अगर_घोषित CONFIG_PCI_IOV
	&sriov_pf_dev_attr_group,
	&sriov_vf_dev_attr_group,
#पूर्ण_अगर
	&pci_bridge_attr_group,
	&pcie_dev_attr_group,
#अगर_घोषित CONFIG_PCIEAER
	&aer_stats_attr_group,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCIEASPM
	&aspm_ctrl_attr_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;

स्थिर काष्ठा device_type pci_dev_type = अणु
	.groups = pci_dev_attr_groups,
पूर्ण;
